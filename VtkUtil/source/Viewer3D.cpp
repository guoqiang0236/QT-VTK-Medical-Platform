#include "Viewer3D.h"
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkDICOMImageReader.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include <vtkCubeAxesActor.h>
#include <vtkTextProperty.h>
#include <vtkImageThreshold.h>
#include <vtkFlyingEdges3D.h>
#include <QMessageBox>
#include <vtkImageResample.h>
Viewer3D::Viewer3D(QVTKOpenGLNativeWidget* widget)
    : ViewerBase(widget)
{
    m_marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
    m_smoother = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
    m_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    m_actor = vtkSmartPointer<vtkActor>::New();
    m_GPUvolumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
}
void Viewer3D::loadBody(const std::string& path)
{
    try {
        switch (m_fileType)
        {
        case VtkFileType::DICOM:
            break;
        case VtkFileType::DICOM_SERIES:
        {
            initializeReader(path);
            VolumeRendering(getm_dicomreader());
            break;
        }
        case VtkFileType::RAW:
        {
            initializeImageReader(path);
            VolumeRendering(getm_imagereader());
            break;
        }
        case VtkFileType::COMPANYRAW:
            break;
        case VtkFileType::UNKNOWN:
            break;
        default:
            break;
        }
        setupCubeAxes();
        setupOrientationMarker();
        auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
        m_vtkWidget->renderWindow()->GetInteractor()->SetInteractorStyle(style);
		m_vtkWidget->renderWindow()->GetInteractor()->SetDesiredUpdateRate(30);
        resetCamera();
        m_vtkWidget->renderWindow()->Render(); // 建议始终调用，保证渲染刷新
      
    }
    catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "渲染失败", QString("3D渲染失败: %1").arg(e.what()));
    }
}
void Viewer3D::loadDirectory(const std::string& path) {
    try {

        initializeReader(path);
        setupPipeline();
        resetCamera();
        m_vtkWidget->renderWindow()->Render();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "渲染失败", QString("3D渲染失败: %1").arg(e.what()));
    }
}





void Viewer3D::loadSurface(const std::string& path)
{
    try {
        switch (m_fileType)
        {
        case VtkFileType::DICOM:
            break;
        case VtkFileType::DICOM_SERIES:
        {
            initializeReader(path);
            SurfaceRendering(getm_dicomreader());
            break;
        }
        case VtkFileType::RAW:
        {
            initializeImageReader(path);
            SurfaceRendering(getm_imagereader());
            break;
        }
        case VtkFileType::COMPANYRAW:
            // 如有需要可补充COMPANYRAW处理
            break;
        case VtkFileType::UNKNOWN:
            break;
        default:
            break;
        }
        resetCamera();
        m_vtkWidget->renderWindow()->Render();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "渲染失败", QString("3D渲染失败: %1").arg(e.what()));
    }
}


void Viewer3D::setupPipeline() {
    // Marching Cubes提取等值面
    m_marchingCubes->SetInputConnection(m_dicomreader->GetOutputPort());
    m_marchingCubes->SetValue(0, m_threshold);

    // 平滑处理
    m_smoother->SetInputConnection(m_marchingCubes->GetOutputPort());
    m_smoother->SetNumberOfIterations(m_smoothIterations);
    m_smoother->SetRelaxationFactor(m_smoothRelaxation);
    m_smoother->Update();

    // Mapper设置
    m_mapper->SetInputConnection(m_smoother->GetOutputPort());
    m_mapper->ScalarVisibilityOff();

    // Actor设置
    m_actor->SetMapper(m_mapper);
    m_actor->GetProperty()->SetColor(0.9, 0.9, 0.9); // 浅灰色
    m_actor->GetProperty()->SetSpecular(0.3);
    m_actor->GetProperty()->SetSpecularPower(20);

    // 添加Actor到渲染器
    m_renderer->AddActor(m_actor);

    // 设置交互样式
    auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    m_vtkWidget->renderWindow()->GetInteractor()->SetInteractorStyle(style);
}

void Viewer3D::setThreshold(double value) {
    m_threshold = value;
    if (m_marchingCubes) {
        m_marchingCubes->SetValue(0, m_threshold);
        updateRendering();
    }
}

void Viewer3D::setSmoothingFactor(int iterations, double relaxation) {
    m_smoothIterations = iterations;
    m_smoothRelaxation = relaxation;
    if (m_smoother) {
        m_smoother->SetNumberOfIterations(iterations);
        m_smoother->SetRelaxationFactor(relaxation);
        updateRendering();
    }
}

void Viewer3D::updateRendering() {
    m_marchingCubes->Update();
    m_smoother->Update();
    m_vtkWidget->renderWindow()->Render();
}

void Viewer3D::resetCamera() {
    vtkCamera* camera = m_renderer->GetActiveCamera();
    camera->SetPosition(0, 0, -1);  // 初始相机位置
    camera->SetFocalPoint(0, 0, 0);
    camera->SetViewUp(0, 1, 0);
    m_renderer->ResetCamera();
    m_vtkWidget->renderWindow()->Render();
}

void Viewer3D::VolumeRendering(vtkImageAlgorithm* imageReader)
{
    // 1. 检查数据有效性
    if (!imageReader || !imageReader->GetOutput()) {
        QMessageBox::critical(nullptr, "渲染失败", QString("体数据无效"));
    }
	//对体数据进行重采样（可选，通常用于降低分辨率或调整体数据大小）
    if(!m_resample)
        m_resample = vtkSmartPointer<vtkImageResample>::New();

    m_resample->SetInputConnection(imageReader->GetOutputPort());
    m_resample->SetAxisMagnificationFactor(0, 0.5); // X方向
    m_resample->SetAxisMagnificationFactor(1, 0.5); // Y方向
    m_resample->SetAxisMagnificationFactor(2, 0.5); // Z方向
    m_resample->Update();
    // 2. 检查是否支持 GPU 渲染
    bool isGPU = GetIsGPU();
    if (isGPU) {
        if (!m_GPUvolumeMapper)
            m_GPUvolumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
        m_GPUvolumeMapper->SetInputConnection(m_resample->GetOutputPort());
		m_GPUvolumeMapper->SetSampleDistance(0.1f);
    }
    else {
        if (!m_CPUvolumeMapper)
            m_CPUvolumeMapper = vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
        m_CPUvolumeMapper->SetInputConnection(m_resample->GetOutputPort());
        m_GPUvolumeMapper->SetSampleDistance(0.1f);
    }

    // 3. 设置颜色传递函数（决定不同灰度/密度值对应的颜色）
    if (!m_colorTransferFunction)
        m_colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
   
    m_colorTransferFunction->AddRGBPoint(-1000, 0.0, 0.0, 0.0); // -1000: 黑色（通常为空气）
    m_colorTransferFunction->AddRGBPoint(0, 1.0, 0.5, 0.3); // 0: 棕色（可自定义，通常为软组织）
    m_colorTransferFunction->AddRGBPoint(500, 1.0, 1.0, 0.9);  // 500: 浅黄色（如骨骼）
    m_colorTransferFunction->AddRGBPoint(1200, 1.0, 1.0, 1.0);// 1200: 白色（高密度结构）

    // 4. 设置透明度传递函数（决定不同灰度/密度值的透明度）
    if (!m_opacityTransferFunction)
        m_opacityTransferFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
    m_opacityTransferFunction->AddPoint(-1000, 0.0);// -1000: 完全透明
    m_opacityTransferFunction->AddPoint(0, 0.0); // 0: 依然透明
    m_opacityTransferFunction->AddPoint(60, 0.0); // 60: 依然透明
    m_opacityTransferFunction->AddPoint(200, 0.2); // 200: 开始有一点点不透明
    m_opacityTransferFunction->AddPoint(300, 0.4); // 300: 更不透明
    m_opacityTransferFunction->AddPoint(400, 0.6);// 400: 更加不透明
    m_opacityTransferFunction->AddPoint(500, 0.8); // 500: 接近不透明
    m_opacityTransferFunction->AddPoint(1200, 1.0);// 1200: 完全不透明

    // 5. 设置体积属性（VolumeProperty 控制体绘制的光照、插值和材质效果）
    if (!m_volumeProperty)
        m_volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();

    // 设置颜色映射（不同灰度/密度值对应的颜色）
    m_volumeProperty->SetColor(m_colorTransferFunction);

    // 设置透明度映射（不同灰度/密度值对应的透明度）
    m_volumeProperty->SetScalarOpacity(m_opacityTransferFunction);

    // 开启光照（Shading），让体绘制有立体感
    m_volumeProperty->ShadeOn();

    // 设置插值方式为线性插值（提升渲染平滑度，避免马赛克感）
    m_volumeProperty->SetInterpolationTypeToLinear();

    // 设置环境光系数（Ambient）：
    // 环境光是场景中均匀分布的光线，数值越大，整体越亮但缺乏立体感。常用0.1~0.4。
    m_volumeProperty->SetAmbient(0.2);

    // 设置漫反射系数（Diffuse）：
    // 漫反射决定了物体表面受光照后主要的亮度和立体感，数值越大，表面越有立体感。常用0.6~0.9。
    m_volumeProperty->SetDiffuse(0.7);

    // 设置高光系数（Specular）：
    // 高光决定了表面反射光的强度，数值越大，表面越有光泽感。常用0.3~0.7。
    m_volumeProperty->SetSpecular(0.5);

    // 设置高光指数（SpecularPower）：
    // 控制高光的锐利程度，值越大高光越尖锐、越小越柔和。常用10~50。
    m_volumeProperty->SetSpecularPower(20.0);



    vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
    if (isGPU)
        volume->SetMapper(m_GPUvolumeMapper);
    else
        volume->SetMapper(m_CPUvolumeMapper);
    volume->SetProperty(m_volumeProperty);

    m_renderer->AddVolume(volume);

    
}

double Viewer3D::CalculateOptimalResampleFactor(int totalVoxels)
{
    // 定义阈值（根据实际硬件调整）
    const int VOXEL_THRESHOLD_HIGH = 200 * 1024 * 1024;  // 200M体素 (如 512×512×768)
    const int VOXEL_THRESHOLD_MEDIUM = 100 * 1024 * 1024; // 100M体素 (如 512×512×384)
    const int VOXEL_THRESHOLD_LOW = 50 * 1024 * 1024;    // 50M体素 (如 512×512×192)

    // GPU/CPU 性能差异调整
    bool isGPU = GetIsGPU();

    if (totalVoxels > VOXEL_THRESHOLD_HIGH) {
        // 超大数据集：激进降采样
        return isGPU ? 0.4 : 0.3;  // GPU: 40%, CPU: 30%
    }
    else if (totalVoxels > VOXEL_THRESHOLD_MEDIUM) {
        // 大数据集：中度降采样
        return isGPU ? 0.6 : 0.5;  // GPU: 60%, CPU: 50%
    }
    else if (totalVoxels > VOXEL_THRESHOLD_LOW) {
        // 中等数据集：轻度降采样
        return isGPU ? 0.8 : 0.7;  // GPU: 80%, CPU: 70%
    }
    else {
        // 小数据集：保持原始分辨率或轻微降采样
        return isGPU ? 1.0 : 0.9;  // GPU: 100%, CPU: 90%
    }
}


void Viewer3D::SurfaceRendering(vtkImageAlgorithm* imageReader)
{
    vtkSmartPointer<vtkImageThreshold> threshold = vtkSmartPointer<vtkImageThreshold>::New();
    threshold->SetInputConnection(imageReader->GetOutputPort());
    threshold->ThresholdByUpper(100);
    threshold->ReplaceInOn();
    threshold->SetInValue(1);
    threshold->ReplaceOutOn();
    threshold->SetOutValue(0);
    threshold->Update();

    m_marchingCubes->SetInputConnection(threshold->GetOutputPort());
    m_marchingCubes->ComputeNormalsOn();
    m_marchingCubes->SetValue(0, 0.5);

    // 平滑处理
    m_smoother->SetInputConnection(m_marchingCubes->GetOutputPort());
    m_smoother->SetNumberOfIterations(m_smoothIterations);
    m_smoother->SetRelaxationFactor(m_smoothRelaxation);
    m_smoother->Update();

    m_mapper->SetInputConnection(m_marchingCubes->GetOutputPort());
    m_mapper->ScalarVisibilityOff();

    m_actor->SetMapper(m_mapper);
    m_actor->GetProperty()->SetColor(1.0, 0.7, 0.63);

    m_renderer->AddActor(m_actor);
    m_renderer->SetBackground(0, 0, 0);

    // 设置交互样式
    auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    m_vtkWidget->renderWindow()->GetInteractor()->SetInteractorStyle(style);
    resetCamera();
}

void Viewer3D::setupCubeAxes()
{
    if (!m_cubeAxesActor)
        m_cubeAxesActor = vtkSmartPointer<vtkCubeAxesActor>::New();
    m_cubeAxesActor->GetTitleTextProperty(0)->SetColor(1, 1, 1);
    m_cubeAxesActor->GetLabelTextProperty(0)->SetColor(1, 1, 1);
    m_cubeAxesActor->GetTitleTextProperty(1)->SetColor(1, 1, 1);
    m_cubeAxesActor->GetLabelTextProperty(1)->SetColor(1, 1, 1);
    m_cubeAxesActor->GetTitleTextProperty(2)->SetColor(1, 1, 1);
    m_cubeAxesActor->GetLabelTextProperty(2)->SetColor(1, 1, 1);
    m_cubeAxesActor->GetXAxesLinesProperty()->SetColor(1, 0, 0);
    m_cubeAxesActor->GetYAxesLinesProperty()->SetColor(0, 1, 0);
    m_cubeAxesActor->GetZAxesLinesProperty()->SetColor(0, 0, 1);
    m_cubeAxesActor->SetFlyModeToStaticTriad();

    // 设置Bounds和Camera
    double bounds[6];
    m_renderer->ComputeVisiblePropBounds(bounds);
    m_cubeAxesActor->SetBounds(bounds);
    m_cubeAxesActor->SetCamera(m_renderer->GetActiveCamera());

  
    m_renderer->AddActor(m_cubeAxesActor);
}

void Viewer3D::setupOrientationMarker()
{
    m_axes = vtkSmartPointer<vtkAxesActor>::New();
    m_orientationMarker = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    m_orientationMarker->SetOrientationMarker(m_axes);
    m_orientationMarker->SetInteractor(m_vtkWidget->renderWindow()->GetInteractor());
    m_orientationMarker->SetViewport(0.0, 0.0, 0.2, 0.2);
    m_orientationMarker->SetEnabled(1);
    m_orientationMarker->InteractiveOff();
}

Viewer3D::~Viewer3D() {
    if (m_actor) m_renderer->RemoveActor(m_actor);
}
