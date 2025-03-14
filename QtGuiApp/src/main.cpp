#include <QApplication>
#include <QQmlApplicationEngine>
#include <QWindow>
#include <QTimer>
#include "MainWindow.h"
#include<vtkAutoInit.h>
#include <vtkOutputWindow.h>
//VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);

int main(int argc, char* argv[]) {
    // ... 保持全局配置代码 ...

    //QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 3);
    //format.setRenderableType(QSurfaceFormat::OpenGL);
    
    //format.setProfile(QSurfaceFormat::NoProfile);
    format.setProfile(QSurfaceFormat::CoreProfile);
    //QSurfaceFormat format;
    //format.setRenderableType(QSurfaceFormat::OpenGL);
    //format.setVersion(2, 1);  // 回退到OpenGL 2.1
    //format.setProfile(QSurfaceFormat::NoProfile);  // 不使用Core Profile
    //format.setSamples(0);  // 关闭多重采样
    QSurfaceFormat::setDefaultFormat(format);
    QSurfaceFormat::setDefaultFormat(format);
    QApplication app(argc, argv);
    vtkOutputWindow::SetGlobalWarningDisplay(0);
    // 加载样式表
    QFile qss(":/QSS/ElegantDark.qss");
    if (qss.open(QFile::ReadOnly)) {
        app.setStyleSheet(qss.readAll());
        qss.close();
    }

    // 使用智能指针管理主窗口
    MainWindow* mainWindow = new MainWindow();
    
    mainWindow->show();
    return app.exec();
}