// DicomViewer3D.cpp
#include "DicomViewer3D.h"
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkProperty.h>
#include <vtkCamera.h>

DicomViewer3D::DicomViewer3D(QVTKOpenGLNativeWidget* widget)
    : DicomViewerBase(widget)
{
    m_marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
    m_smoother = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
    m_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    m_actor = vtkSmartPointer<vtkActor>::New();
}

void DicomViewer3D::loadDirectory(const std::string& path) {
    try {
        initializeReader(path);
        setupPipeline();
        resetCamera();
        m_vtkWidget->renderWindow()->Render();
    } catch (const std::exception& e) {
        throw std::runtime_error("3D rendering failed: " + std::string(e.what()));
    }
}

void DicomViewer3D::setupPipeline() {
    // Marching Cubes提取等值面
    m_marchingCubes->SetInputConnection(m_reader->GetOutputPort());
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

void DicomViewer3D::setThreshold(double value) {
    m_threshold = value;
    if(m_marchingCubes) {
        m_marchingCubes->SetValue(0, m_threshold);
        updateRendering();
    }
}

void DicomViewer3D::setSmoothingFactor(int iterations, double relaxation) {
    m_smoothIterations = iterations;
    m_smoothRelaxation = relaxation;
    if(m_smoother) {
        m_smoother->SetNumberOfIterations(iterations);
        m_smoother->SetRelaxationFactor(relaxation);
        updateRendering();
    }
}

void DicomViewer3D::updateRendering() {
    m_marchingCubes->Update();
    m_smoother->Update();
    m_vtkWidget->renderWindow()->Render();
}

void DicomViewer3D::resetCamera() {
    vtkCamera* camera = m_renderer->GetActiveCamera();
    camera->SetPosition(0, 0, -1);  // 初始相机位置
    camera->SetFocalPoint(0, 0, 0);
    camera->SetViewUp(0, 1, 0);
    m_renderer->ResetCamera();
}

DicomViewer3D::~DicomViewer3D() {
    if(m_actor) m_renderer->RemoveActor(m_actor);
}