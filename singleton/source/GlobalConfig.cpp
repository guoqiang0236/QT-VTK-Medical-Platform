#include "GlobalConfig.h"
#include <QGuiApplication>
#include <QScreen>
// 实现单例获取方法
sysconfig::GlobalConfig& sysconfig::GlobalConfig::get() {
    static GlobalConfig instance;
    return instance;
}

QSize sysconfig::GlobalConfig::getAdjustedSize()
{
    // 获取主屏幕分辨率
    QScreen* screen = QGuiApplication::primaryScreen();
    if (!screen) {
        return QSize(800, 600); // 默认尺寸
    }

    QSize resolution = screen->size();
    int width = resolution.width();
    int height = resolution.height();

    // 根据分辨率映射到目标尺寸
    if (width >= 3840 && height >= 2160) { // 4K
        return QSize(2560, 1440);
    }
    else if (width >= 2560 && height >= 1440) { // 2K
        return QSize(1600, 900);
    }
    else if (width >= 1920 && height >= 1080) { // 1080p
        return QSize(1600, 900);
    }
    else if (width >= 1600 && height >= 900) { // 1080p
        return QSize(1280, 720);
    }
    else {
        return QSize(800, 600); // 默认尺寸
    }
}

// 构造函数初始化默认值
sysconfig::GlobalConfig::GlobalConfig() {
    renderQuality = 100;
    useHardwareAcceleration = true;
    appDataPath = "default/path";  // 可在此初始化其他默认值
}