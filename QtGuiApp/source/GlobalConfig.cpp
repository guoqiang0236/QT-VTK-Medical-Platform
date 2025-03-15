#include "GlobalConfig.h"

// 实现单例获取方法
sysconfig::GlobalConfig& sysconfig::GlobalConfig::get() {
    static GlobalConfig instance;
    return instance;
}

// 构造函数初始化默认值
sysconfig::GlobalConfig::GlobalConfig() {
    renderQuality = 100;
    useHardwareAcceleration = true;
    appDataPath = "default/path";  // 可在此初始化其他默认值
}