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

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    m_VisualManager(std::make_unique<VisualizationManager>())
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/res/icon/favicon.ico")); // 覆盖可能的默认值
    m_ui->setupUi(this);
    initSlots();
    UpdateGUI();
}

MainWindow::~MainWindow() = default;

void MainWindow::ReadDicomFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, "选择文件", "", "DICOM files (*.dcm);;All files (*.*)");
    if (!fileName.isEmpty() && m_VisualManager)
    { m_VisualManager->loadFile(fileName);
        
    }
}

void MainWindow::ReadDicomFiles()
{
    QString folderPath = QFileDialog::getExistingDirectory(
        this, "选择文件夹", QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!folderPath.isEmpty() && m_VisualManager) 
    {
        m_VisualManager->loadDicomSeries(folderPath);     
    }
}

void MainWindow::ReadDicomFiles3D()
{
    QString folderPath = QFileDialog::getExistingDirectory(
        this, "选择文件夹", QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!folderPath.isEmpty() && m_VisualManager) 
    {
        m_VisualManager->loadVolumeData(folderPath);
    }
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
    int view = std::stoi(viewport.toStdString());
    m_VisualManager->changeViewOrientation(view);
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
    connect(m_ui->pushButton, &QPushButton::clicked, this, &MainWindow::ReadDicomFile);
    connect(m_ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::ReadDicomFiles);
    connect(m_ui->pushButton_12, &QPushButton::clicked, this, &MainWindow::ReadDicomFiles3D);
    connect(m_ui->comboBox, &QComboBox::currentTextChanged, this, &MainWindow::StyleChanged);
    connect(m_ui->pushButton_shutdown, &QPushButton::clicked, this, &MainWindow::ShutDown);
    connect(m_ui->comboBox_2, &QComboBox::currentTextChanged, this, &MainWindow::ViewChange);
}

void MainWindow::UpdateGUI()
{
    if (!m_VisualManager)
        return;
    m_VisualManager->getVTKWidget()->setParent(m_ui->frame_vtkrender);
    m_VisualManager->getVTKWidget()->setObjectName("VTKopenGLWidget");
    m_ui->horizontalLayout_2->addWidget(m_VisualManager->getVTKWidget());
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