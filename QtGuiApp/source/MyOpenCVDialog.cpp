#include "MyOpenCVDialog.h"
MyOpenCVDialog::MyOpenCVDialog(QWidget* parent)
    : QDialog(parent),
	m_ui(std::make_unique<Ui::OpenCVDialog>()),
	m_opencvImageUtil(std::make_unique<OpenCVImageUtil>()),
	m_thread(new QThread(this)),
	m_thread_scpwork(new MyThread_DCMTK_SCP_Work(this))
{
    m_ui->setupUi(this); // 关键：加载UI
	UpdateGUI();
	UpdateSize();
	InitSlots();
}

MyOpenCVDialog::~MyOpenCVDialog()
{
	if (m_thread->isRunning())
	{
		m_thread->quit();
		m_thread->wait();
	}
	if (m_thread_scpwork) {
		m_thread_scpwork->deleteLater();
		m_thread_scpwork = nullptr;
	}
  
}

void MyOpenCVDialog::InitSlots()
{
	disconnect(m_ui->pushButton_openimage, nullptr, this, nullptr);

	connect(m_ui->pushButton_openimage, &QPushButton::clicked, this, &MyOpenCVDialog::on_pushButton_openimage_clicked);
	connect(m_ui->pushButton_SCU, &QPushButton::clicked, this, &MyOpenCVDialog::StartOrStop_SCU);
}

void MyOpenCVDialog::UpdateGUI()
{
}

void MyOpenCVDialog::UpdateSize()
{
    sysconfig::GlobalConfig& config = sysconfig::GlobalConfig::get();
    QSize windowsize = config.getAdjustedSize();
    this->resize(windowsize);
}



void MyOpenCVDialog::StartOrStop_SCU()
{
	if (!bthreadrun)
	{
		// 启动
		if (m_thread) {
			delete m_thread;
			m_thread = nullptr;
		}
		if (m_thread_scpwork) {
			delete m_thread_scpwork;
			m_thread_scpwork = nullptr;
		}
		m_thread = new QThread(this);
		m_thread_scpwork = new MyThread_DCMTK_SCP_Work();
		m_thread_scpwork->moveToThread(m_thread);

		connect(m_thread, &QThread::started, m_thread_scpwork, &MyThread_DCMTK_SCP_Work::Working);
		connect(m_thread, &QThread::finished, m_thread_scpwork, &QObject::deleteLater);

		m_thread->start();
		bthreadrun = true;
	}
//	else
//	{
//		// 停止
//		if (m_thread_scpwork) {
//			QMetaObject::invokeMethod(m_thread_scpwork, "StopWorking", Qt::QueuedConnection);
//		}
//		if (m_thread) {
//			m_thread->quit();
//			m_thread->wait();
//			delete m_thread;
//			m_thread = nullptr;
//		}
//		m_thread_scpwork = nullptr; // 已经在 finished 信号中 deleteLater
//	}
}



void MyOpenCVDialog::on_pushButton_openimage_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.png *.xpm *.jpg *.bmp)"));
	if (fileName.isEmpty())
		return;
	bool status = m_opencvImageUtil->openImage(fileName.toStdString());
	//status = m_opencvImageUtil->convertColor(2);
	if (!status)
		return;
	
	QImage image = m_opencvImageUtil->getCurrentImage();
	QPixmap pixmap = QPixmap::fromImage(image);

	// 创建或获取 scene
	QGraphicsScene* scene = new QGraphicsScene(this);
	scene->addPixmap(pixmap);
	scene->setSceneRect(pixmap.rect());
	
	// 设置 scene 到 graphicsView
	m_ui->graphicsView->setScene(scene);
}
