#include "MainWindow.h"
// 移除不存在的头文件
#include <vtkImageData.h>
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
#include <GlobalConfig.h>
#include <thread>
#include <iostream>
#include <vtkImageFlip.h>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    m_VisualManager(std::make_unique<VisualizationManager>()),
    m_ui(std::make_unique<Ui::MainWindow_UI>()),
    m_thread(new MyThread(this)),
    m_thread_work(new MyThread_work(this)),
	m_thread_runnable(new MyThread_Runnable(this)),
    m_sub(new QThread(this)),
    m_numsub(new QThread(this)),
    m_dcmtkscp(std::make_unique<MyCStoreSCP>())
{
    //setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/res/icon/favicon.ico")); // 覆盖可能的默认值
    m_ui->setupUi(this);
    initSlots();
    UpdateSize();
    UpdateGUI();
    InitThread();
}

MainWindow::~MainWindow() 
{
    if (m_sub)
    {
        if (m_sub->isRunning())
        {
            m_sub->quit();
            m_sub->wait();
        }
    }
    if (m_numsub)
    {
        if (m_numsub->isRunning())
        {
            m_numsub->quit();
            m_numsub->wait();
        }
    }
};

void MainWindow::ReadFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, "选择文件", "", "All files (*.*)");
    if (!fileName.isEmpty() && m_VisualManager)
    { 
        QObject* senderObject = sender();
		m_VisualManager->setm_bcompanyrawdata(false);
        if (senderObject == m_ui->pushButton_rawcompany) {
            m_VisualManager->setm_bcompanyrawdata(true);
        }
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
        // 方案1: 转换为本地编码
        QByteArray utf8Path = folderPath.toUtf8();
        QString utf8FolderPath = QString::fromUtf8(utf8Path.constData());
        m_VisualManager->setFlieType(VtkFileType::DICOM_SERIES);
        m_VisualManager->loadFiles(utf8FolderPath);
        
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

void MainWindow::Change_CurrentTime()
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
	m_ui->label_currenttime->setText(currentTime);
}



void MainWindow::initSlots()
{
	m_current_time = new QTimer(this);
	connect(m_current_time, &QTimer::timeout, this, &MainWindow::Change_CurrentTime);
    m_current_time->start(1000);
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
	m_ui->label_hospital->setText("上海市第六人民医院临港分院");
    // 移除旧的 openGLWidget
    if (m_ui->openGLWidget) {
        m_ui->openGLWidget->setParent(nullptr);
        m_ui->openGLWidget->deleteLater();
    }
    m_VisualManager->getVTKWidget()->setMinimumSize(QSize(400, 500));
    m_VisualManager->getVTKWidget()->setObjectName("VTKopenGLWidget");
    m_ui->gridLayout_8->addWidget(vtkWidget, 1, 0, 1, 1);
    // 移除旧的 openGLWidget_AXIAL
    if (m_ui->openGLWidget_AXIAL) 
    {
        m_ui->openGLWidget_AXIAL->setParent(nullptr);
        m_ui->openGLWidget_AXIAL->deleteLater();
    }
    m_VisualManager->getVTKWidget_Axial()->setParent(m_ui->frame_AXIAL);
    m_VisualManager->getVTKWidget_Axial()->setObjectName("openGLWidget_AXIAL");
    m_VisualManager->getVTKWidget_Axial()->setMinimumSize(QSize(100, 100));
    m_ui->gridLayout_4->addWidget(m_VisualManager->getVTKWidget_Axial(), 0, 1, 1, 1);
	// 移除旧的 openGLWidget_CORONAL
	if (m_ui->openGLWidget_CORONAL) 
    {
		m_ui->openGLWidget_CORONAL->setParent(nullptr);
		m_ui->openGLWidget_CORONAL->deleteLater();
	}
    m_VisualManager->getVTKWidget_Coronal()->setParent(m_ui->frame_CORONAL);
    m_VisualManager->getVTKWidget_Coronal()->setObjectName("openGLWidget_CORONAL");
    m_VisualManager->getVTKWidget_Coronal()->setMinimumSize(QSize(100, 100));
    m_ui->gridLayout_5->addWidget(m_VisualManager->getVTKWidget_Coronal(), 0, 1, 1, 1);

	// 移除旧的 openGLWidget_SAGITTAL
	if (m_ui->openGLWidget_SAGITTAL) {
		m_ui->openGLWidget_SAGITTAL->setParent(nullptr);
		m_ui->openGLWidget_SAGITTAL->deleteLater();
	}
    m_VisualManager->getVTKWidget_Sagittal()->setParent(m_ui->frame_SAGITTAL);
    m_VisualManager->getVTKWidget_Sagittal()->setObjectName("openGLWidget_SAGITTAL");
    m_VisualManager->getVTKWidget_Sagittal()->setMinimumSize(QSize(100, 100));
    m_ui->gridLayout_6->addWidget(m_VisualManager->getVTKWidget_Sagittal(), 0, 1, 1, 1);

    //禁止使用面绘制（卡顿）
    m_ui->pushButton_mian->setEnabled(false);
}

void MainWindow::UpdateSize()
{
	sysconfig::GlobalConfig& config = sysconfig::GlobalConfig::get();
    QSize windowsize = config.getAdjustedSize();
    this->resize(windowsize);
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

void MainWindow::InitThread()
{
    //方式一QThread
    //int idealThreads = MyThread::idealThreadCount(); // 获取硬件支持的最大线程数
    //int activeThreads = MyThread::getActiveThreadCount();
    //qDebug() << "硬件支持的最大线程数: " << idealThreads;
    //qDebug() << "现在活跃的线程数: " << activeThreads;

    //if (!m_thread->isRunning())
    //{
    //    m_thread->setPriority(QThread::LowestPriority); // 设置线程优先级
    //    m_thread->start(); // 启动线程
    //}
    //else
    //{
    //    qWarning() << "线程正在运行，无法启动新任务！";
    //}
  /*  connect(m_thread, &MyThread::numberGenerated, this, [this](int num) {
        m_ui->label_showthreadnum->setText(QString::number(num));
        });*/

    //方式二QObject
     // 创建线程对象
    
    if (m_thread_work)
    {
        m_thread_work->moveToThread(m_numsub);
    }
    m_numsub->start();
	connect(m_thread_work, &MyThread_work::numberGenerated, this, [this](int num) {
		m_ui->label_showthreadnum->setText(QString::number(num));
		});
    connect(this, &MainWindow::numcounttaskstarted, m_thread_work, &MyThread_work::working);
    emit numcounttaskstarted();

    //方式三 线程池
    /*QThreadPool::globalInstance()->setMaxThreadCount(4);
	if (m_thread_runnable)
	{
		QThreadPool::globalInstance()->start(m_thread_runnable);
	}
    connect(m_thread_runnable, &MyThread_Runnable::numberGenerated, this, [this](int num) {

        m_ui->label_showthreadnum->setText(QString::number(num));
        });
    */


    
    //多线程dcmtk接收
    // 设置 SCP 的 AE Title 和监听端口
    m_dcmtkscp->setAETitle("MY_SCP");
    m_dcmtkscp->setPort(11112);

    // 创建一个 OFList<OFString> 并添加传输语法
    OFList<OFString> transferSyntaxes;
    transferSyntaxes.push_back(UID_LittleEndianExplicitTransferSyntax);

    // 调用 addPresentationContext 方法
    m_dcmtkscp->addPresentationContext(UID_CTImageStorage, transferSyntaxes);
    m_dcmtkscp->moveToThread(m_sub);
   
    // 启动监听的槽函数（假设你有 startSCP() 方法）
    QObject::connect(m_sub, &QThread::started, [this]() {
        m_dcmtkscp->start(); // start() 是 DcmSCP 的监听方法
        });

    // 处理信号
    QObject::connect(m_dcmtkscp.get(), &MyCStoreSCP::dicomReceived, this, [this]() {
        
        ViewDataset(m_dcmtkscp.get()->getDataset());
        });


    QObject::connect(m_sub, &QThread::finished, m_sub, &QObject::deleteLater);

    m_sub->start();
}

void MainWindow::ViewDataset(DcmDataset* dataset)
{
    // 1. 获取图像尺寸和像素信息
    Uint16 rows = 0, cols = 0, bitsAllocated = 0;
    dataset->findAndGetUint16(DCM_Rows, rows);
    dataset->findAndGetUint16(DCM_Columns, cols);
    dataset->findAndGetUint16(DCM_BitsAllocated, bitsAllocated);

    // 2. 获取像素数据指针
    const void* pixelData = nullptr;
    dataset->findAndGetUint8Array(DCM_PixelData, (const Uint8*&)pixelData);
    if (!pixelData) {
        qDebug() << "像素数据为空";
        return;
    }

    // 3. 创建 vtkImageData 并填充
    auto imageData = vtkSmartPointer<vtkImageData>::New();
    imageData->SetDimensions(cols, rows, 1);

    if (bitsAllocated == 8) {
        imageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
        memcpy(imageData->GetScalarPointer(), pixelData, rows * cols * sizeof(Uint8));
    }
    else if (bitsAllocated == 16) {
        imageData->AllocateScalars(VTK_UNSIGNED_SHORT, 1);
        memcpy(imageData->GetScalarPointer(), pixelData, rows * cols * sizeof(Uint16));
    }
    else {
        qDebug() << "不支持的像素位数:" << bitsAllocated;
        return;
    }
    // 4. 添加垂直翻转（解决180度倒置问题）
    auto flipFilter = vtkSmartPointer<vtkImageFlip>::New();
    flipFilter->SetFilteredAxis(1);  // 沿Y轴翻转（垂直方向）
    flipFilter->SetInputData(imageData);
    flipFilter->Update();

    // 5. 用 VTK 显示
    auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
    viewer->SetInputConnection(flipFilter->GetOutputPort()); // 使用翻转后的数据
    //viewer->SetInputData(imageData);
    viewer->SetRenderWindow(m_VisualManager->getVTKWidget()->renderWindow());
    viewer->Render();
   
}
