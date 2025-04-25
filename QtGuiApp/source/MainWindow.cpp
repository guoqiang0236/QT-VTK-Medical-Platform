#include "MainWindow.h"
// 移除不存在的头文件

#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <QDebug>
#include <QIcon>
#include <QFileDialog>
#include <memory>
#include "VisualizationManager.h"
#include "MainWindow-MEDQT.h"
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    m_VisualManager(std::make_unique<VisualizationManager>()),
    m_ui(std::make_unique<Ui::MainWindow_UI>())
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/res/icon/favicon.ico")); // 覆盖可能的默认值
    m_ui->setupUi(this);
    initSlots();
    UpdateGUI();
}

MainWindow::~MainWindow() = default;

void MainWindow::ReadFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, "选择文件", "", "All files (*.*)");
    if (!fileName.isEmpty() && m_VisualManager)
    { 
        m_VisualManager->loadFile(fileName);   
    }

}

void MainWindow::ReadFiles()
{
    QString folderPath = QFileDialog::getExistingDirectory(
        this, "选择文件夹", QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!folderPath.isEmpty() && m_VisualManager) 
    {
        //..m_VisualManager->loadDicomSeries(folderPath);     
        // 方案1: 转换为本地编码
        QByteArray utf8Path = folderPath.toUtf8();
        QString utf8FolderPath = QString::fromUtf8(utf8Path.constData());
        m_VisualManager->setFlieType(VtkFileType::DICOM_SERIES);
        m_VisualManager->loadFiles(utf8FolderPath);
        //m_VisualManager->loadDicomSeries(utf8FolderPath);
    }
}

void MainWindow::ReadRawFile()
{
}



void MainWindow::DataTo3DVolume()
{
	if (!m_VisualManager)
		return;
    switch (m_VisualManager->getFlieType())
    {   
	case VtkFileType::DICOM_SERIES:
    {
        if (m_VisualManager->getDirPath() != "")
        {
            m_VisualManager->DataToVolume(m_VisualManager->getDirPath());
        }
    }
    case VtkFileType::RAW:
        if (m_VisualManager->getRawDataPath() != "")
        {
            m_VisualManager->DataToVolume(m_VisualManager->getRawDataPath());
        }
        break;
    default:
        break;
    }
   
   return;
}

void MainWindow::DataTo3DSurface()
{
    auto test = m_VisualManager->getDirPath();
    switch (m_VisualManager->getFlieType())
    {
    case VtkFileType::DICOM_SERIES:
    {
        if (m_VisualManager->getDirPath() != "")
        {

            m_VisualManager->DataToSurFace(m_VisualManager->getDirPath());

        }
    }
    case VtkFileType::RAW:
        if (m_VisualManager->getRawDataPath() != "")
        {
            m_VisualManager->DataToSurFace(m_VisualManager->getRawDataPath());
        }
        break;
    default:
        break;
    }
    
    return;
}

void MainWindow::StyleChanged(const QString& style)
{
    qDebug() << "当前选中文本：" << style;
    QString styledir = ":/res/QSS/" + style + ".qss";
    loadStyleSheet(styledir);
}

void MainWindow::ViewChange(const QString& viewport)
{
    if (!m_VisualManager)
        return;
	int view = m_ui->comboBox_2->currentIndex();
    m_VisualManager->changeViewOrientation(view);
}

void MainWindow::LoadDicomFinished()
{
    SetCurrentSliderEnable(false);
    m_ui->Slider_AXIAL->setValue(0);
    m_ui->Slider_CORONAL->setValue(0);
    m_ui->Slider_SAGITTAL->setValue(0);
}

void MainWindow::LoadDicomsFinished()
{
    if (!m_ui)
        return;
	m_ui->label_AXIAL_2->setText("1");
    m_ui->label_AXIALMAX->setText(QString::number(m_VisualManager->getm_axial_sliceall()+1));
    m_ui->Slider_AXIAL->setMaximum(m_VisualManager->getm_axial_sliceall());
    m_ui->Slider_AXIAL->setValue(0);

    m_ui->label_CORONALMIN->setText("1");
	m_ui->label_CORONALMAX->setText(QString::number(m_VisualManager->getm_coronal_sliceall()+1));
    m_ui->Slider_CORONAL->setMaximum(m_VisualManager->getm_coronal_sliceall());
    m_ui->Slider_CORONAL->setValue(0);
  
	m_ui->label_SAGITTALMIN->setText("1");
	m_ui->label_SAGITTALMAX->setText(QString::number(m_VisualManager->getm_sagittal_sliceall()+1));
    m_ui->Slider_SAGITTAL->setMaximum(m_VisualManager->getm_sagittal_sliceall());
    m_ui->Slider_SAGITTAL->setValue(0);
    
    SetCurrentSliderEnable(true);
     // 禁止 AXIAL 滑块
    if(!m_VisualManager)
		return;
    disconnect(m_VisualManager->getDicom2DViewer_axial(), &Viewer2D::sliceChanged, this, nullptr);
    disconnect(m_VisualManager->getDicom2DViewer_coronal(), &Viewer2D::sliceChanged, this, nullptr);
    disconnect(m_VisualManager->getDicom2DViewer_sagittal(), &Viewer2D::sliceChanged, this, nullptr);

    connect(m_VisualManager->getDicom2DViewer_axial(), &Viewer2D::sliceChanged, this, &MainWindow::SetCurrentAXIALSliderValue);
    connect(m_VisualManager->getDicom2DViewer_coronal(), &Viewer2D::sliceChanged, this, &MainWindow::SetCurrentCORONALSliderValue);
    connect(m_VisualManager->getDicom2DViewer_sagittal(), &Viewer2D::sliceChanged, this, &MainWindow::SetCurrentSAGITTALSliderValue);
}

void MainWindow::SetCurrentSliderEnable(bool enable)
{
    m_ui->Slider_AXIAL->setEnabled(enable);   // 禁止 AXIAL 滑块
    m_ui->Slider_CORONAL->setEnabled(enable); // 禁止 CORONAL 滑块
    m_ui->Slider_SAGITTAL->setEnabled(enable); // 禁止 SAGITTAL 滑块
}


void MainWindow::SetCurrentAXIALSliderValue(int slice)
{
	if (m_ui->Slider_AXIAL)
	{
		m_ui->Slider_AXIAL->setValue(slice);
	}
}

void MainWindow::SetCurrentCORONALSliderValue(int slice)
{
	if (m_ui->Slider_CORONAL)
	{
		m_ui->Slider_CORONAL->setValue(slice);
	}
}

void MainWindow::SetCurrentSAGITTALSliderValue(int slice)
{
	if (m_ui->Slider_SAGITTAL)
	{
		m_ui->Slider_SAGITTAL->setValue(slice);
	}
}

void MainWindow::ShutDown()
{
    QApplication::quit();
}

void MainWindow::OnAnimationFinished()
{
}

void MainWindow::initSlots()
{
    connect(m_ui->pushButton_rawcompany, &QPushButton::clicked, this, &MainWindow::ReadFile);
    connect(m_ui->pushButton_openfile, &QPushButton::clicked, this, &MainWindow::ReadFile);
    connect(m_ui->pushButton_opendicoms, &QPushButton::clicked, this, &MainWindow::ReadFiles);
    connect(m_ui->pushButton_ti, &QPushButton::clicked, this, &MainWindow::DataTo3DVolume);
	connect(m_ui->pushButton_mian, & QPushButton::clicked, this, & MainWindow::DataTo3DSurface);
    connect(m_ui->comboBox, &QComboBox::currentTextChanged, this, &MainWindow::StyleChanged);
    connect(m_ui->pushButton_shutdown, &QPushButton::clicked, this, &MainWindow::ShutDown);
    connect(m_ui->comboBox_2, &QComboBox::currentTextChanged, this, &MainWindow::ViewChange);
    if (!m_VisualManager)
        return;
    connect(m_VisualManager.get(), &VisualizationManager::loadDicomFileFinish, this, &MainWindow::LoadDicomFinished);
    connect(m_VisualManager.get(), &VisualizationManager::loadDicomSeriesFinish, this, &MainWindow::LoadDicomsFinished);
	connect(m_ui->Slider_AXIAL, &QSlider::valueChanged, m_VisualManager.get(), &VisualizationManager::setAxialSlice);
	connect(m_ui->Slider_CORONAL, &QSlider::valueChanged, m_VisualManager.get(), &VisualizationManager::setCoronalSlice);
	connect(m_ui->Slider_SAGITTAL, &QSlider::valueChanged, m_VisualManager.get(), &VisualizationManager::setSagittalSlice);
}

void MainWindow::UpdateGUI()
{
    if (!m_ui || !m_VisualManager)
        return;

    auto vtkWidget = m_VisualManager->getVTKWidget();
    if (!vtkWidget)
        return;

    // 移除旧的 openGLWidget
    if (m_ui->openGLWidget) {
        m_ui->openGLWidget->setParent(nullptr);
        m_ui->openGLWidget->deleteLater();
    }
    m_VisualManager->getVTKWidget()->setParent(m_ui->frame_vtkrender);
    m_VisualManager->getVTKWidget()->setObjectName("VTKopenGLWidget");
    m_ui->horizontalLayout_2->insertWidget(0,vtkWidget);

    // 移除旧的 openGLWidget_AXIAL
    if (m_ui->openGLWidget_AXIAL) 
    {
        m_ui->openGLWidget_AXIAL->setParent(nullptr);
        m_ui->openGLWidget_AXIAL->deleteLater();
    }
    m_VisualManager->getVTKWidget_Axial()->setParent(m_ui->frame_AXIAL);
    m_VisualManager->getVTKWidget_Axial()->setObjectName("openGLWidget_AXIAL");
    m_VisualManager->getVTKWidget_Axial()->setGeometry(QRect(90, 0, 300, 300));

	// 移除旧的 openGLWidget_CORONAL
	if (m_ui->openGLWidget_CORONAL) 
    {
		m_ui->openGLWidget_CORONAL->setParent(nullptr);
		m_ui->openGLWidget_CORONAL->deleteLater();
	}
    m_VisualManager->getVTKWidget_Coronal()->setParent(m_ui->frame_CORONAL);
    m_VisualManager->getVTKWidget_Coronal()->setObjectName("openGLWidget_CORONAL");
    m_VisualManager->getVTKWidget_Coronal()->setGeometry(QRect(90, 0, 300, 300));

	// 移除旧的 openGLWidget_SAGITTAL
	if (m_ui->openGLWidget_SAGITTAL) {
		m_ui->openGLWidget_SAGITTAL->setParent(nullptr);
		m_ui->openGLWidget_SAGITTAL->deleteLater();
	}
    m_VisualManager->getVTKWidget_Sagittal()->setParent(m_ui->frame_SAGITTAL);
    m_VisualManager->getVTKWidget_Sagittal()->setObjectName("openGLWidget_SAGITTAL");
    m_VisualManager->getVTKWidget_Sagittal()->setGeometry(QRect(90, 0, 300, 300));

}

void MainWindow::loadStyleSheet(const QString& path)
{
    QFile qssFile(path);
    if (!qssFile.exists()) {
        qWarning() << "QSS 文件不存在:" << path;
        return;
    }
    if (qssFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(styleSheet); // 全局应用样式
        qssFile.close();
    }
    else {
        qWarning() << "无法打开 QSS 文件:" << path;
    }
}