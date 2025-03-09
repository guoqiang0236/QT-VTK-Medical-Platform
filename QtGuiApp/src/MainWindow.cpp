#include "MainWindow.h"
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <Qdebug.h>
#include <QIcon>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) 
{
    // 设置无边框窗口
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/icon/favicon.ico")); // 覆盖可能的默认值
    ui.setupUi(this);
    initsolt();
    test();
}

MainWindow::~MainWindow() = default;

void MainWindow::test()
{
    // ========== VTK 初始化 =====


    auto m_render_window = ui.VTKopenGLWidget->renderWindow();
    // 3. 创建渲染器
    m_render_window->AddRenderer(m_renderer);

    // 4. 设置渲染器背景色
    m_renderer->SetBackground(0.2, 0.3, 0.4);

    // ===== 添加一个示例三维对象（球体）=====
    // 1. 创建数据源
    auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetRadius(2.0);

    // 2. 创建映射器
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    // 3. 创建演员
    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // 4. 将演员添加到渲染器
    m_renderer->AddActor(actor);

    // 5. 重置相机视角
    m_renderer->ResetCamera();

    // 6. 触发渲染
    m_render_window->Render();
}

void MainWindow::ReadDicomFile()
{
    std::cout << "test click" << std::endl;
}

void MainWindow::StyleChanged(const QString &style)
{
    qDebug() << "当前选中文本：" << style;
    QString styledir = ":/QSS/" + style + ".qss";
    loadStyleSheet(styledir);
}

void MainWindow::ShutDown()
{
    QApplication::quit();
}

void MainWindow::initsolt()
{
    QObject::connect(ui.pushButton, &QPushButton::clicked, this, &MainWindow::ReadDicomFile);
    QObject::connect(ui.comboBox, &QComboBox::currentTextChanged,this, &MainWindow::StyleChanged);
    QObject::connect(ui.pushButton_shutdown, &QPushButton::clicked, this, &MainWindow::ShutDown);
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

