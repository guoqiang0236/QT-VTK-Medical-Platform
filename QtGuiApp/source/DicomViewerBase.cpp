#include "DicomViewerBase.h"
#include <filesystem> // 添加这一行

DicomViewerBase::DicomViewerBase(QVTKOpenGLNativeWidget* widget)
    : m_vtkWidget(widget),
    m_renderer(vtkRenderer::New())
{
    m_vtkWidget->renderWindow()->AddRenderer(m_renderer);
}

void DicomViewerBase::initializeReader(const std::string& path) {
    m_reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    if (std::filesystem::is_directory(path)) {
        m_reader->SetDirectoryName(path.c_str());
    }
    else {
        m_reader->SetFileName(path.c_str());
    }
    m_reader->Update();
}

void DicomViewerBase::cleanup() {
    if (m_renderer) {
        m_renderer->RemoveAllViewProps();
        m_vtkWidget->renderWindow()->RemoveRenderer(m_renderer);
        m_renderer->Delete();
    }
    m_renderer = vtkRenderer::New();
    m_reader = nullptr;
}