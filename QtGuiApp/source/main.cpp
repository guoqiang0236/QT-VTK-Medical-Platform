#include <QApplication>
#include <QQmlApplicationEngine>
#include <QWindow>
#include <QTimer>
#include "MainWindow.h"
#include "CustomSplashScreen.h"
#include<vtkAutoInit.h>
#include <vtkOutputWindow.h>
#include <QFile>
//VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);

int main(int argc, char* argv[]) {
    

    // ... 保持全局配置代码 ...
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);
    QApplication app(argc, argv);
    vtkOutputWindow::SetGlobalWarningDisplay(0);
    //loading加载界面
    CustomSplashScreen loadingflash;
    loadingflash.init();
    // 加载样式表
    QFile qss(":/res/QSS/ElegantDark.qss");
    if (qss.open(QFile::ReadOnly)) {
        app.setStyleSheet(qss.readAll());
        qss.close();
    }
    auto mainWindow = std::make_unique<MainWindow>();

    
    mainWindow->show();

    loadingflash.finish(mainWindow.get());
    return app.exec();
}