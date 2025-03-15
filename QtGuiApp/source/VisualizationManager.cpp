// VisualizationManager.cpp
#include "VisualizationManager.h"
#include "VtkFileTypeDetector.h"
#include "DicomViewer2D.h"
#include "DicomViewer3D.h"
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>

VisualizationManager::VisualizationManager(QObject* parent)
    : QObject(parent), m_vtkWidget(new QVTKOpenGLNativeWidget()),
      m_mainRenderer(vtkRenderer::New()) , m_orientation(0)
{
    m_vtkWidget->renderWindow()->AddRenderer(m_mainRenderer);
    initializeResources();
}

VisualizationManager::~VisualizationManager() {
    cleanupCurrentViewer();
    m_mainRenderer->Delete();
}

void VisualizationManager::initializeResources() {
    m_fileDetector = std::make_unique<VtkFileTypeDetector>();
}

QVTKOpenGLNativeWidget* VisualizationManager::getVTKWidget() const {
    return m_vtkWidget;
}

void VisualizationManager::loadFile(const QString& filePath) {
    cleanupCurrentViewer();
    
    auto fileType = m_fileDetector->detect(filePath.toStdString());
    
    switch(fileType) {
    case VtkFileType::DICOM:
        m_dicom2DViewer = std::make_unique<DicomViewer2D>(m_vtkWidget);
        m_dicom2DViewer->loadFile(filePath.toStdString());
        break;
    // 添加其他文件类型处理
    default:
        //emit errorOccurred("Unsupported file format");
        break;
    }
}

void VisualizationManager::loadDicomSeries(const QString& dirPath) {
    cleanupCurrentViewer();
    m_dicom2DViewer = std::make_unique<DicomViewer2D>(m_vtkWidget);
    m_dicom2DViewer->setOrientation(m_orientation);
    m_dicom2DViewer->loadDirectory(dirPath.toStdString());
}

void VisualizationManager::loadVolumeData(const QString& dirPath) {
    cleanupCurrentViewer();
    m_dicom3DViewer = std::make_unique<DicomViewer3D>(m_vtkWidget);
    m_dicom3DViewer->loadDirectory(dirPath.toStdString());
}

void VisualizationManager::changeViewOrientation(int orientation) {
    m_orientation = orientation;
    if(m_dicom2DViewer) {
        m_dicom2DViewer->setViewOrientation(
            static_cast<SliceOrientation>(m_orientation));
    }
}

void VisualizationManager::cleanupCurrentViewer() {
    m_mainRenderer->RemoveAllViewProps();
    m_dicom2DViewer.reset();
    m_dicom3DViewer.reset();
    m_vtkWidget->renderWindow()->Render();
}