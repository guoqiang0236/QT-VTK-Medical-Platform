// VisualizationManager.cpp
#include "VisualizationManager.h"
#include "VtkFileTypeDetector.h"
#include "Viewer2D.h"
#include "Viewer3D.h"
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <QFile>
#include <vtkRendererCollection.h>
#include <QMessageBox>
#include <vtkImageReader.h>
VisualizationManager::VisualizationManager(QObject* parent)
    : QObject(parent), m_vtkWidget(new QVTKOpenGLNativeWidget()),
      m_mainRenderer(vtkRenderer::New()) , m_orientation(0),
	m_vtkWidget_axial(new QVTKOpenGLNativeWidget()), m_vtkWidget_coronal(new QVTKOpenGLNativeWidget()),
    m_vtkWidget_sagittal(new QVTKOpenGLNativeWidget()),
	m_fileType(VtkFileType::UNKNOWN) ,
	m_bcompanyrawdata(false)
{
  
    m_vtkWidget->renderWindow()->AddRenderer(m_mainRenderer);
    initializeResources();
	dir_path = "";
    rawdata_path = "";
    
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

Viewer2D* VisualizationManager::getDicom2DViewer_axial() const
{
	if (m_dicom2DViewer_axial) {
		return m_dicom2DViewer_axial.get();
	}
    return nullptr;
}

Viewer2D* VisualizationManager::getDicom2DViewer_coronal() const
{
	if (m_dicom2DViewer_coronal) {
		return m_dicom2DViewer_coronal.get();
	}
    return nullptr;
}

Viewer2D* VisualizationManager::getDicom2DViewer_sagittal() const
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

    m_fileType = m_fileDetector->detect(filePath.toStdString());
	if (m_fileType == VtkFileType::RAW && m_bcompanyrawdata)
	{
		m_fileType = VtkFileType::COMPANYRAW;
	}
    switch (m_fileType) {
    case VtkFileType::DICOM:
        loadDicomSingleFile(filePath);
        break;
    case VtkFileType::RAW:
        loadRawData(filePath);
        break;
    case VtkFileType::COMPANYRAW:
        loadCompanyRawData(filePath);
        break;
    case VtkFileType::UNKNOWN: {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Error");
        msgBox.setText("不支持此数据类型");
        msgBox.setStyleSheet("QLabel { color: black; }"); // 将警告文字设置为红色  
        msgBox.exec();
        break;
    }
    default:
        // Handle other file types if necessary  
        break;
    }
}

void VisualizationManager::loadFiles(const QString& filePath)
{
    cleanupCurrentViewer();
    switch (m_fileType)
    {
    case VtkFileType::DICOM_SERIES:
		loadDicomSeries(filePath);
        break;
    case VtkFileType::UNKNOWN:
        break;
    default:
        break;
    }
}

void VisualizationManager::loadRawData(const QString& filePath)
{
    // 读取 RAW 文件
	rawdata_path = filePath;
    vtkSmartPointer<vtkImageReader> reader = vtkSmartPointer<vtkImageReader>::New();
    reader->SetFileName(filePath.toStdString().c_str());
    reader->SetFileDimensionality(3);
    reader->SetDataScalarType(VTK_UNSIGNED_CHAR);
    reader->SetDataExtent(0, 255, 0, 255, 0, 255);
    reader->SetDataSpacing(0.9, 0.9, 0.9);
    reader->Update();
    m_dicom2DViewer = std::make_unique<Viewer2D>(m_vtkWidget);
    m_dicom2DViewer->setm__imagereader(reader);
    m_dicom2DViewer->setOrientation(m_orientation);
    m_dicom2DViewer->loadRawData();

    m_dicom2DViewer_axial = std::make_unique<Viewer2D>(m_vtkWidget_axial);
    m_dicom2DViewer_axial->setm__imagereader(reader);
    m_dicom2DViewer_axial->setOrientation(0);
    m_dicom2DViewer_axial->loadRawData();
    m_dicom2DViewer_axial->setmessage("AXIAL");
    m_dicom2DViewer_axial->getInteractorStyle()->EnableMouseWheel(false);

    m_dicom2DViewer_coronal = std::make_unique<Viewer2D>(m_vtkWidget_coronal);
    m_dicom2DViewer_coronal->setm__imagereader(reader);
    m_dicom2DViewer_coronal->setOrientation(1);
    m_dicom2DViewer_coronal->loadRawData();
    m_dicom2DViewer_coronal->setmessage("CORONAL");
    m_dicom2DViewer_coronal->getInteractorStyle()->EnableMouseWheel(false);

    m_dicom2DViewer_sagittal = std::make_unique<Viewer2D>(m_vtkWidget_sagittal);
    m_dicom2DViewer_sagittal->setm__imagereader(reader);
    m_dicom2DViewer_sagittal->setOrientation(2);
    m_dicom2DViewer_sagittal->loadRawData();
    m_dicom2DViewer_sagittal->setmessage("SAGITTAL");
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



void VisualizationManager::loadCompanyRawData(const QString& filePath)
{
    m_dicom2DViewer = std::make_unique<Viewer2D>(m_vtkWidget);
    m_dicom2DViewer->loadCompanyRawData(filePath.toStdString());

    if (m_dicom2DViewer_axial)
        m_dicom2DViewer_axial->cleanup();
    if (m_dicom2DViewer_coronal)
        m_dicom2DViewer_coronal->cleanup();
    if (m_dicom2DViewer_sagittal)
        m_dicom2DViewer_sagittal->cleanup();
}

void VisualizationManager::loadDicomSingleFile(const QString& filePath)
{
    m_dicom2DViewer = std::make_unique<Viewer2D>(m_vtkWidget);
	m_dicom2DViewer->initializeReader(filePath.toStdString());

    m_dicom2DViewer->loadDicomFile(filePath.toStdString());
    emit loadDicomFileFinish();
}

void VisualizationManager::loadDicomSeries(const QString& dirPath) {

	dir_path = dirPath;
    // 使用本地编码而不是UTF-8，适应Windows文件系统API
    QByteArray localPath = QFile::encodeName(dirPath);
 
    m_dicom2DViewer = std::make_unique<Viewer2D>(m_vtkWidget);
    m_dicom2DViewer->initializeReader(std::string(localPath.constData()));
    m_dicom2DViewer->setOrientation(m_orientation);
	m_dicom2DViewer->setmessage("MAIN");
    m_dicom2DViewer->loadDicomDirectory(std::string(localPath.constData()));


    auto reader = m_dicom2DViewer->getm_dicomreader();
    m_dicom2DViewer_axial = std::make_unique<Viewer2D>(m_vtkWidget_axial);
    m_dicom2DViewer_axial->setm_reader(reader);
    m_dicom2DViewer_axial->setOrientation(0);
	m_dicom2DViewer_axial->setmessage("AXIAL");
    m_dicom2DViewer_axial->loadDicomDirectory(std::string(localPath.constData()));
    m_dicom2DViewer_axial->getInteractorStyle()->EnableMouseWheel(false);

    m_dicom2DViewer_coronal = std::make_unique<Viewer2D>(m_vtkWidget_coronal);
    m_dicom2DViewer_coronal->setm_reader(reader);
    m_dicom2DViewer_coronal->setOrientation(1);
    m_dicom2DViewer_coronal->setmessage("CORONAL");
    m_dicom2DViewer_coronal->loadDicomDirectory(std::string(localPath.constData()));
	m_dicom2DViewer_coronal->getInteractorStyle()->EnableMouseWheel(false);

    m_dicom2DViewer_sagittal = std::make_unique<Viewer2D>(m_vtkWidget_sagittal);
    m_dicom2DViewer_sagittal->setm_reader(reader);
    m_dicom2DViewer_sagittal->setOrientation(2);
    m_dicom2DViewer_sagittal->setmessage("SAGITTAL");
    m_dicom2DViewer_sagittal->loadDicomDirectory(std::string(localPath.constData()));
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


void VisualizationManager::DataToVolume(const QString& dirPath)
{
    cleanupMainViewer();
    switch (m_fileType)
    {
    case VtkFileType::DICOM:
        break;
    case VtkFileType::DICOM_SERIES:
        VolumeDicomSeries(dirPath);
        break;
    case VtkFileType::RAW:
        VolumeRawData(dirPath);
        break;
    case VtkFileType::UNKNOWN:
        break;
    default:
        break;
    }

}

void VisualizationManager::VolumeDicomSeries(const QString& dirPath)
{
    m_dicom3DViewer = std::make_unique<Viewer3D>(m_vtkWidget);
    // 使用本地编码而不是UTF-8，适应Windows文件系统API
    QByteArray localPath = QFile::encodeName(dirPath);
    m_dicom3DViewer->loadDirectory_Body(std::string(localPath.constData()));
}

void VisualizationManager::VolumeRawData(const QString& dirPath)
{
    m_dicom3DViewer = std::make_unique<Viewer3D>(m_vtkWidget);
    // 使用本地编码而不是UTF-8，适应Windows文件系统API
    QByteArray localPath = QFile::encodeName(dirPath);
    m_dicom3DViewer->loadRawData_Body(std::string(localPath.constData()));
}

void VisualizationManager::SurFaceDicomSeries(const QString& dirPath)
{
    m_dicom3DViewer = std::make_unique<Viewer3D>(m_vtkWidget);
    // 使用本地编码而不是UTF-8，适应Windows文件系统API
    QByteArray localPath = QFile::encodeName(dirPath);
    m_dicom3DViewer->loadDirectory_Surface(std::string(localPath.constData()));
}

void VisualizationManager::SurFaceRawData(const QString& dirPath)
{
    m_dicom3DViewer = std::make_unique<Viewer3D>(m_vtkWidget);
    // 使用本地编码而不是UTF-8，适应Windows文件系统API
    QByteArray localPath = QFile::encodeName(dirPath);
    m_dicom3DViewer->loadRawData_Surface(std::string(localPath.constData()));
}



void VisualizationManager::DataToSurFace(const QString& dirPath)
{
    cleanupMainViewer();
    switch (m_fileType)
    {
    case VtkFileType::DICOM:
        break;
    case VtkFileType::DICOM_SERIES:
        SurFaceDicomSeries(dirPath);
        break;
    case VtkFileType::RAW:
		SurFaceRawData(dirPath);
        break;
    case VtkFileType::UNKNOWN:
        break;
    default:
        break;
    }
    
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
        disconnect(m_dicom2DViewer_axial.get(), &Viewer2D::sliceChanged, this, nullptr);
        connect(m_dicom2DViewer_axial.get(), &Viewer2D::sliceChanged, this, [this](int slice) {
            emit sliceChanged(slice);
            });
    }

    if (m_dicom2DViewer_coronal) {
        disconnect(m_dicom2DViewer_coronal.get(), &Viewer2D::sliceChanged, this, nullptr);
        connect(m_dicom2DViewer_coronal.get(), &Viewer2D::sliceChanged, this, [this](int slice) {
            emit sliceChanged(slice);
            });
    }

    if (m_dicom2DViewer_sagittal) {
        disconnect(m_dicom2DViewer_sagittal.get(), &Viewer2D::sliceChanged, this, nullptr);
        connect(m_dicom2DViewer_sagittal.get(), &Viewer2D::sliceChanged, this, [this](int slice) {
            emit sliceChanged(slice);
            });
    }
}


void VisualizationManager::cleanupCurrentViewer() {
    m_mainRenderer->RemoveAllViewProps();
    if (m_dicom2DViewer_axial) {
        m_dicom2DViewer_axial->cleanup();
    }

    if (m_dicom2DViewer_coronal) {
        m_dicom2DViewer_coronal->cleanup();
    }

    if (m_dicom2DViewer_sagittal) {
        m_dicom2DViewer_sagittal->cleanup();
    }
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
