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
Viewer3D::Viewer3D(QVTKOpenGLNativeWidget* widget)
    : ViewerBase(widget)
{
    m_marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
    m_smoother = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
    m_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    m_actor = vtkSmartPointer<vtkActor>::New();
    m_GPUvolumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
}

void Viewer3D::loadDirectory(const std::string& path) {
    try {
        //const char* ss = path.c_str();

        initializeReader(path);
        setupPipeline();
        resetCamera();
        m_vtkWidget->renderWindow()->Render();
    }
    catch (const std::exception& e) {
        throw std::runtime_error("3D rendering failed: " + std::string(e.what()));
    }
}

void Viewer3D::loadDirectory_Body(const std::string& path)
{
    try {
        initializeReader(path);
        VolumeRendering(getm_dicomreader());
        resetCamera();
       
    }
    catch (const std::exception& e) {
        throw std::runtime_error("3D rendering failed: " + std::string(e.what()));
    }
}

void Viewer3D::loadRawData_Body(const std::string& path)
{
    try {
        initializeImageReader(path);
        VolumeRendering(getm_imagereader());
        resetCamera();
        m_vtkWidget->renderWindow()->Render();
    }
    catch (const std::exception& e) {
        throw std::runtime_error("3D rendering failed: " + std::string(e.what()));
    }
}

void Viewer3D::loadDirectory_Surface(const std::string& path)
{
    try {
        initializeReader(path);
        SurfaceRendering(getm_dicomreader());
        resetCamera();
        m_vtkWidget->renderWindow()->Render();
    }
    catch (const std::exception& e) {
        throw std::runtime_error("3D rendering failed: " + std::string(e.what()));
    }
}

void Viewer3D::loadRawData_Surface(const std::string& path)
{
    try {
        initializeImageReader(path);
        SurfaceRendering(getm_imagereader());
        resetCamera();
        m_vtkWidget->renderWindow()->Render();
    }
    catch (const std::exception& e) {
        throw std::runtime_error("3D rendering failed: " + std::string(e.what()));
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
        throw std::runtime_error("体数据无效: ");
    }
    // 2. 检查是否支持 GPU 渲染
    bool isGPU = GetIsGPU();
    if (isGPU) {
        if (!m_GPUvolumeMapper)
            m_GPUvolumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
        m_GPUvolumeMapper->SetInputConnection(imageReader->GetOutputPort());
    }
    else {
        if (!m_CPUvolumeMapper)
            m_CPUvolumeMapper = vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
        m_CPUvolumeMapper->SetInputConnection(imageReader->GetOutputPort());
    }

    // 3. 设置颜色传递函数
    if (!m_colorTransferFunction)
        m_colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
    m_colorTransferFunction->AddRGBPoint(-1000, 0.0, 0.0, 0.0);
    m_colorTransferFunction->AddRGBPoint(0, 1.0, 0.5, 0.3);
    m_colorTransferFunction->AddRGBPoint(500, 1.0, 1.0, 0.9);
    m_colorTransferFunction->AddRGBPoint(1200, 1.0, 1.0, 1.0);

    // 4. 设置透明度传递函数
    if (!m_opacityTransferFunction)
        m_opacityTransferFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
    m_opacityTransferFunction->AddPoint(-1000, 0.0);
    m_opacityTransferFunction->AddPoint(0, 0.0);
    m_opacityTransferFunction->AddPoint(60, 0.0);
    m_opacityTransferFunction->AddPoint(200, 0.2);
    m_opacityTransferFunction->AddPoint(300, 0.4);
    m_opacityTransferFunction->AddPoint(400, 0.6);
    m_opacityTransferFunction->AddPoint(500, 0.8);
    m_opacityTransferFunction->AddPoint(1200, 1.0);

    // 5. 设置体积属性
    if (!m_volumeProperty)
        m_volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
    m_volumeProperty->SetColor(m_colorTransferFunction);
    m_volumeProperty->SetScalarOpacity(m_opacityTransferFunction);
    m_volumeProperty->ShadeOn();
    m_volumeProperty->SetInterpolationTypeToLinear();

    vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
    if (isGPU)
        volume->SetMapper(m_GPUvolumeMapper);
    else
        volume->SetMapper(m_CPUvolumeMapper);
    volume->SetProperty(m_volumeProperty);

    m_renderer->AddVolume(volume);

    // 6. 设置坐标轴
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
    m_renderer->AddActor(m_cubeAxesActor);

    // 7. 初始化并配置方向标记
    m_axes = vtkSmartPointer<vtkAxesActor>::New();
    m_orientationMarker = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    m_orientationMarker->SetOrientationMarker(m_axes);
    m_orientationMarker->SetInteractor(m_vtkWidget->renderWindow()->GetInteractor());
    m_orientationMarker->SetViewport(0.0, 0.0, 0.2, 0.2);
    m_orientationMarker->SetEnabled(1);
    m_orientationMarker->InteractiveOff();

    // 8. 设置交互样式
    auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    m_vtkWidget->renderWindow()->GetInteractor()->SetInteractorStyle(style);
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

Viewer3D::~Viewer3D() {
    if (m_actor) m_renderer->RemoveActor(m_actor);
}
