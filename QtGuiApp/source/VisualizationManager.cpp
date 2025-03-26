// VisualizationManager.cpp
#include "VisualizationManager.h"
#include "VtkFileTypeDetector.h"
#include "DicomViewer2D.h"
#include "DicomViewer3D.h"
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <QFile>
VisualizationManager::VisualizationManager(QObject* parent)
    : QObject(parent), m_vtkWidget(new QVTKOpenGLNativeWidget()),
      m_mainRenderer(vtkRenderer::New()) , m_orientation(0),
	m_vtkWidget_axial(new QVTKOpenGLNativeWidget()), m_vtkWidget_coronal(new QVTKOpenGLNativeWidget()),
    m_vtkWidget_sagittal(new QVTKOpenGLNativeWidget())
{
  
    m_vtkWidget->renderWindow()->AddRenderer(m_mainRenderer);
    initializeResources();
	dir_path = "";
}

VisualizationManager::~VisualizationManager() {
    cleanupCurrentViewer();
    m_mainRenderer->Delete();
}

void VisualizationManager::initializeResources() {
    m_fileDetector = std::make_unique<VtkFileTypeDetector>();
    m_axial_sliceall = 0;
	m_coronal_sliceall = 0;
	m_sagittal_sliceall = 0;
}

QVTKOpenGLNativeWidget* VisualizationManager::getVTKWidget() const {
    return m_vtkWidget;
}

QVTKOpenGLNativeWidget* VisualizationManager::getVTKWidget_Axial() const
{
    return m_vtkWidget_axial;
}

QVTKOpenGLNativeWidget* VisualizationManager::getVTKWidget_Coronal() const
{
    return m_vtkWidget_coronal;
}

QVTKOpenGLNativeWidget* VisualizationManager::getVTKWidget_Sagittal() const
{
    return m_vtkWidget_sagittal;
}

DicomViewer2D* VisualizationManager::getDicom2DViewer_axial() const
{
	if (m_dicom2DViewer_axial) {
		return m_dicom2DViewer_axial.get();
	}
    return nullptr;
}

DicomViewer2D* VisualizationManager::getDicom2DViewer_coronal() const
{
	if (m_dicom2DViewer_coronal) {
		return m_dicom2DViewer_coronal.get();
	}
    return nullptr;
}

DicomViewer2D* VisualizationManager::getDicom2DViewer_sagittal() const
{
    if (m_dicom2DViewer_sagittal)
    {
		return m_dicom2DViewer_sagittal.get();
    }
    return nullptr;
}

void VisualizationManager::setAxialSlice(int slice)
{
    if (m_dicom2DViewer_axial) {
        m_dicom2DViewer_axial->setSlice(slice);
		//m_dicom2DViewer_axial->getInteractorStyle()->SetCurrentSliceNumberNow(slice);
    }
}

void VisualizationManager::setCoronalSlice(int slice)
{
    if (m_dicom2DViewer_coronal) {
        m_dicom2DViewer_coronal->setSlice(slice);
        //m_dicom2DViewer_coronal->getInteractorStyle()->SetCurrentSliceNumberNow(slice);
    }
}

void VisualizationManager::setSagittalSlice(int slice)
{
    if (m_dicom2DViewer_sagittal) {
        m_dicom2DViewer_sagittal->setSlice(slice);
        //m_dicom2DViewer_coronal->getInteractorStyle()->SetCurrentSliceNumberNow(slice);
    }
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
	dir_path = dirPath;
    // 使用本地编码而不是UTF-8，适应Windows文件系统API
    QByteArray localPath = QFile::encodeName(dirPath);
 
    m_dicom2DViewer = std::make_unique<DicomViewer2D>(m_vtkWidget);
    m_dicom2DViewer->setOrientation(m_orientation);
	m_dicom2DViewer->setmessage("MAIN");
    m_dicom2DViewer->loadDirectory(std::string(localPath.constData()));

    m_dicom2DViewer_axial = std::make_unique<DicomViewer2D>(m_vtkWidget_axial);
    m_dicom2DViewer_axial->setOrientation(0);
	m_dicom2DViewer_axial->setmessage("AXIAL");
    m_dicom2DViewer_axial->loadDirectory(std::string(localPath.constData()));
    m_dicom2DViewer_axial->getInteractorStyle()->EnableMouseWheel(false);

    m_dicom2DViewer_coronal = std::make_unique<DicomViewer2D>(m_vtkWidget_coronal);
    m_dicom2DViewer_coronal->setOrientation(1);
    m_dicom2DViewer_coronal->setmessage("CORONAL");
    m_dicom2DViewer_coronal->loadDirectory(std::string(localPath.constData()));
	m_dicom2DViewer_coronal->getInteractorStyle()->EnableMouseWheel(false);

    m_dicom2DViewer_sagittal = std::make_unique<DicomViewer2D>(m_vtkWidget_sagittal);
    m_dicom2DViewer_sagittal->setOrientation(2);
    m_dicom2DViewer_sagittal->setmessage("SAGITTAL");
    m_dicom2DViewer_sagittal->loadDirectory(std::string(localPath.constData()));
	m_dicom2DViewer_sagittal->getInteractorStyle()->EnableMouseWheel(false);

	//获取每个视图的切片数
	m_axial_sliceall = m_dicom2DViewer_axial->getTotalSlices();
	m_coronal_sliceall = m_dicom2DViewer_coronal->getTotalSlices();
	m_sagittal_sliceall = m_dicom2DViewer_sagittal->getTotalSlices();

    // 初始化信号槽
    initxyzSlots();
    emit loadDicomSeriesFinish();
    // 启动每个视图的交互器
    m_dicom2DViewer->startInteractor();
    m_dicom2DViewer_axial->startInteractor();
    m_dicom2DViewer_coronal->startInteractor();
    m_dicom2DViewer_sagittal->startInteractor();

	
}

void VisualizationManager::loadVolumeData(const QString& dirPath) {
    cleanupMainViewer();
    m_dicom3DViewer = std::make_unique<DicomViewer3D>(m_vtkWidget);
    // 使用本地编码而不是UTF-8，适应Windows文件系统API
    QByteArray localPath = QFile::encodeName(dirPath);
    m_dicom3DViewer->loadDirectory(std::string(localPath.constData()));

}

void VisualizationManager::loadDataVolume(const QString& dirPath)
{
    cleanupMainViewer();
    m_dicom3DViewer = std::make_unique<DicomViewer3D>(m_vtkWidget);
    // 使用本地编码而不是UTF-8，适应Windows文件系统API
    QByteArray localPath = QFile::encodeName(dirPath);
    m_dicom3DViewer->loadDirectory_Body(std::string(localPath.constData()));
    //m_dicom3DViewer->loadDirectory_Body(dirPath.toStdString());
}

void VisualizationManager::loadDataSurFace(const QString& dirPath)
{
    cleanupMainViewer();
    m_dicom3DViewer = std::make_unique<DicomViewer3D>(m_vtkWidget);
    // 使用本地编码而不是UTF-8，适应Windows文件系统API
    QByteArray localPath = QFile::encodeName(dirPath);
    m_dicom3DViewer->loadDirectory_Surface(std::string(localPath.constData()));
    //m_dicom3DViewer->loadDirectory_Surface(dirPath.toStdString());
}

void VisualizationManager::changeViewOrientation(int orientation) {
    m_orientation = orientation;
    if(m_dicom2DViewer) {
        m_dicom2DViewer->setViewOrientation(
            static_cast<SliceOrientation>(m_orientation));
    }
}

void VisualizationManager::initxyzSlots()
{
    if (m_dicom2DViewer_axial) {
        disconnect(m_dicom2DViewer_axial.get(), &DicomViewer2D::sliceChanged, this, nullptr);
        connect(m_dicom2DViewer_axial.get(), &DicomViewer2D::sliceChanged, this, [this](int slice) {
            emit sliceChanged(slice);
            });
    }

    if (m_dicom2DViewer_coronal) {
        disconnect(m_dicom2DViewer_coronal.get(), &DicomViewer2D::sliceChanged, this, nullptr);
        connect(m_dicom2DViewer_coronal.get(), &DicomViewer2D::sliceChanged, this, [this](int slice) {
            emit sliceChanged(slice);
            });
    }

    if (m_dicom2DViewer_sagittal) {
        disconnect(m_dicom2DViewer_sagittal.get(), &DicomViewer2D::sliceChanged, this, nullptr);
        connect(m_dicom2DViewer_sagittal.get(), &DicomViewer2D::sliceChanged, this, [this](int slice) {
            emit sliceChanged(slice);
            });
    }
}


void VisualizationManager::cleanupCurrentViewer() {
    m_mainRenderer->RemoveAllViewProps();
    m_dicom2DViewer.reset();
    m_dicom2DViewer_axial.reset();
    m_dicom2DViewer_coronal.reset();
    m_dicom2DViewer_sagittal.reset();
    m_dicom3DViewer.reset();
    m_vtkWidget->renderWindow()->Render();
	m_vtkWidget_axial->renderWindow()->Render();
	m_vtkWidget_coronal->renderWindow()->Render();
	m_vtkWidget_sagittal->renderWindow()->Render();
}

void VisualizationManager::cleanupMainViewer()
{
    m_mainRenderer->RemoveAllViewProps();
    m_dicom2DViewer.reset();
    m_dicom3DViewer.reset();
    m_vtkWidget->renderWindow()->Render();
}
