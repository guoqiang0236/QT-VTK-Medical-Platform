#include <QApplication>
#include <QQmlApplicationEngine>
#include <QWindow>
#include <QTimer>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    // ... 保持全局配置代码 ...

    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    QApplication app(argc, argv);

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