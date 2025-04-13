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

Viewer3D::Viewer3D(QVTKOpenGLNativeWidget* widget)
    : ViewerBase(widget)
{
    m_marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
    m_smoother = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
    m_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    m_actor = vtkSmartPointer<vtkActor>::New();
    m_volumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
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
        DicomsToVolumeRendering();
        resetCamera();
        m_vtkWidget->renderWindow()->Render();
    }
    catch (const std::exception& e) {
        throw std::runtime_error("3D rendering failed: " + std::string(e.what()));
    }
}

void Viewer3D::loadRawData_Body(const std::string& path)
{
    try {
        initializeImageReader(path);
        RawDataToVolumeRendering();
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
        DicomsToSurfaceRendering();
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
        RawDataToSurfaceRendering();
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
}

void Viewer3D::DicomsToVolumeRendering()
{
   
    // 1. 检查数据有效性
    if (!m_dicomreader->GetOutput()) {
        throw std::runtime_error("DICOM 数据无效: " );
    }
    //m_volumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    if (!m_volumeMapper)
    {
		m_volumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    }
    if (!m_volumeMapper)
        return;
    m_volumeMapper->SetInputConnection(m_dicomreader->GetOutputPort());

    vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
    colorTransferFunction->AddRGBPoint(-1000, 0.0, 0.0, 0.0);
    colorTransferFunction->AddRGBPoint(0, 1.0, 0.5, 0.3);
    colorTransferFunction->AddRGBPoint(500, 1.0, 1.0, 0.9);
    colorTransferFunction->AddRGBPoint(1200, 1.0, 1.0, 1.0);

    vtkSmartPointer<vtkPiecewiseFunction> opacityTransferFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
    opacityTransferFunction->AddPoint(-1000, 0.0);
    opacityTransferFunction->AddPoint(0, 0.0);
    opacityTransferFunction->AddPoint(60, 0.0);
    opacityTransferFunction->AddPoint(200, 0.2);
    opacityTransferFunction->AddPoint(300, 0.4);
    opacityTransferFunction->AddPoint(400, 0.6);
    opacityTransferFunction->AddPoint(500, 0.8);
    opacityTransferFunction->AddPoint(1200, 1.0);

    vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
    volumeProperty->SetColor(colorTransferFunction);
    volumeProperty->SetScalarOpacity(opacityTransferFunction);
    volumeProperty->ShadeOn();
    volumeProperty->SetInterpolationTypeToLinear();

    vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(m_volumeMapper);
    volume->SetProperty(volumeProperty);

    m_renderer->AddVolume(volume);

    vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor = vtkSmartPointer<vtkCubeAxesActor>::New();
    cubeAxesActor->SetBounds(volume->GetBounds());
    cubeAxesActor->SetCamera(m_renderer->GetActiveCamera());
    cubeAxesActor->GetTitleTextProperty(0)->SetColor(1, 1, 1);
    cubeAxesActor->GetLabelTextProperty(0)->SetColor(1, 1, 1);
    cubeAxesActor->GetTitleTextProperty(1)->SetColor(1, 1, 1);
    cubeAxesActor->GetLabelTextProperty(1)->SetColor(1, 1, 1);
    cubeAxesActor->GetTitleTextProperty(2)->SetColor(1, 1, 1);
    cubeAxesActor->GetLabelTextProperty(2)->SetColor(1, 1, 1);
    // 设置轴线颜色
    cubeAxesActor->GetXAxesLinesProperty()->SetColor(1, 0, 0);  // 红色X轴
    cubeAxesActor->GetYAxesLinesProperty()->SetColor(0, 1, 0);  // 绿色Y轴
    cubeAxesActor->GetZAxesLinesProperty()->SetColor(0, 0, 1);  // 蓝色Z轴
    cubeAxesActor->SetFlyModeToStaticTriad();
    
    m_renderer->AddActor(cubeAxesActor);

    // 初始化并配置方向标记
	m_axes = vtkSmartPointer<vtkAxesActor>::New();
    m_orientationMarker = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    m_orientationMarker->SetOrientationMarker(m_axes);
	m_orientationMarker->SetInteractor(m_vtkWidget->renderWindow()->GetInteractor());
	m_orientationMarker->SetViewport(0.0, 0.0, 0.2, 0.2);
	m_orientationMarker->SetEnabled(1);
    m_orientationMarker->InteractiveOff();

    // 设置交互样式
    auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    m_vtkWidget->renderWindow()->GetInteractor()->SetInteractorStyle(style);
    resetCamera();
}

void Viewer3D::RawDataToVolumeRendering()
{
    // 1. 检查数据有效性
    if (!m_imagereader->GetOutput()) {
        throw std::runtime_error("DICOM 数据无效: ");
    }
    //m_volumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    if (!m_volumeMapper)
    {
        m_volumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    }
    if (!m_volumeMapper)
        return;
    m_volumeMapper->SetInputConnection(m_imagereader->GetOutputPort());

    vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
    colorTransferFunction->AddRGBPoint(-1000, 0.0, 0.0, 0.0);
    colorTransferFunction->AddRGBPoint(0, 1.0, 0.5, 0.3);
    colorTransferFunction->AddRGBPoint(500, 1.0, 1.0, 0.9);
    colorTransferFunction->AddRGBPoint(1200, 1.0, 1.0, 1.0);

    vtkSmartPointer<vtkPiecewiseFunction> opacityTransferFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
    opacityTransferFunction->AddPoint(-1000, 0.0);
    opacityTransferFunction->AddPoint(0, 0.0);
    opacityTransferFunction->AddPoint(60, 0.0);
    opacityTransferFunction->AddPoint(200, 0.2);
    opacityTransferFunction->AddPoint(300, 0.4);
    opacityTransferFunction->AddPoint(400, 0.6);
    opacityTransferFunction->AddPoint(500, 0.8);
    opacityTransferFunction->AddPoint(1200, 1.0);

    vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
    volumeProperty->SetColor(colorTransferFunction);
    volumeProperty->SetScalarOpacity(opacityTransferFunction);
    volumeProperty->ShadeOn();
    volumeProperty->SetInterpolationTypeToLinear();

    vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(m_volumeMapper);
    volume->SetProperty(volumeProperty);

    m_renderer->AddVolume(volume);

    vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor = vtkSmartPointer<vtkCubeAxesActor>::New();
    cubeAxesActor->SetBounds(volume->GetBounds());
    cubeAxesActor->SetCamera(m_renderer->GetActiveCamera());
    cubeAxesActor->GetTitleTextProperty(0)->SetColor(1, 1, 1);
    cubeAxesActor->GetLabelTextProperty(0)->SetColor(1, 1, 1);
    cubeAxesActor->GetTitleTextProperty(1)->SetColor(1, 1, 1);
    cubeAxesActor->GetLabelTextProperty(1)->SetColor(1, 1, 1);
    cubeAxesActor->GetTitleTextProperty(2)->SetColor(1, 1, 1);
    cubeAxesActor->GetLabelTextProperty(2)->SetColor(1, 1, 1);
    // 设置轴线颜色
    cubeAxesActor->GetXAxesLinesProperty()->SetColor(1, 0, 0);  // 红色X轴
    cubeAxesActor->GetYAxesLinesProperty()->SetColor(0, 1, 0);  // 绿色Y轴
    cubeAxesActor->GetZAxesLinesProperty()->SetColor(0, 0, 1);  // 蓝色Z轴
    cubeAxesActor->SetFlyModeToStaticTriad();

    m_renderer->AddActor(cubeAxesActor);

    // 初始化并配置方向标记
    m_axes = vtkSmartPointer<vtkAxesActor>::New();
    m_orientationMarker = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    m_orientationMarker->SetOrientationMarker(m_axes);
    m_orientationMarker->SetInteractor(m_vtkWidget->renderWindow()->GetInteractor());
    m_orientationMarker->SetViewport(0.0, 0.0, 0.2, 0.2);
    m_orientationMarker->SetEnabled(1);
    m_orientationMarker->InteractiveOff();

    // 设置交互样式
    auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    m_vtkWidget->renderWindow()->GetInteractor()->SetInteractorStyle(style);
    resetCamera();
}

void Viewer3D::DicomsToSurfaceRendering()
{
     
    vtkSmartPointer<vtkImageThreshold> threshold = vtkSmartPointer<vtkImageThreshold>::New();
    threshold->SetInputConnection(m_dicomreader->GetOutputPort());
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
    m_renderer->SetBackground(0,0,0);
    // 设置交互样式
    auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    m_vtkWidget->renderWindow()->GetInteractor()->SetInteractorStyle(style);
    resetCamera();

}

void Viewer3D::RawDataToSurfaceRendering()
{
    vtkSmartPointer<vtkImageThreshold> threshold = vtkSmartPointer<vtkImageThreshold>::New();
    threshold->SetInputConnection(m_imagereader->GetOutputPort());
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
