#include <QApplication>
#include "MainWindow.h"
#include <QDir>
#include <vtkOpenGLRenderWindow.h>  // 必须包含
#include <QFile>
#include <windows.h>  
#include "GlobalConfig.h"

int main(int argc, char *argv[]) {
    // 修改配置
    sysconfig::GlobalConfig::get().appDataPath = "data/user_settings";
    sysconfig::GlobalConfig::get().renderQuality = 90;

    // 必须在QApplication之前调用
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
   
    
    QApplication app(argc, argv);
    QFile qss(":/QSS/ElegantDark.qss");

    qss.open(QFile::ReadOnly);
    if (!qss.exists()) {
        qDebug() << "File does not exist.";
        return -1;
    }
    app.setStyleSheet(qss.readAll());
    qss.close();
    MainWindow window;
    window.show();
    return app.exec();
}