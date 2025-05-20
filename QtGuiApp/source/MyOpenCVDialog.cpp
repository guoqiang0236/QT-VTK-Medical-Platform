#include "MyOpenCVDialog.h"
MyOpenCVDialog::MyOpenCVDialog(QWidget* parent)
    : QDialog(parent),
	m_ui(std::make_unique<Ui::OpenCVDialog>()),
	m_opencvImageUtil(std::make_unique<OpenCVImageUtil>())
{
    m_ui->setupUi(this); // 关键：加载UI
	UpdateGUI();
	UpdateSize();
	InitSlots();
}

MyOpenCVDialog::~MyOpenCVDialog()
{
  
}

void MyOpenCVDialog::InitSlots()
{
	disconnect(m_ui->pushButton_openimage, nullptr, this, nullptr);

	connect(m_ui->pushButton_openimage, &QPushButton::clicked, this, &MyOpenCVDialog::on_pushButton_openimage_clicked);

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
