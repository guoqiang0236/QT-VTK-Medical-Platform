#pragma once
#include <string>
#include <memory>
#include <QSize>

namespace sysconfig {

    class GlobalConfig {
    public:

        GlobalConfig(const GlobalConfig&) = delete;
        GlobalConfig& operator=(const GlobalConfig&) = delete;

       
        static GlobalConfig& get();

      
        std::string appDataPath;
        int renderQuality;
        bool useHardwareAcceleration;

        // 新增：获取调整后的尺寸
        static QSize getAdjustedSize();
    private:
        GlobalConfig();  
    };
}
