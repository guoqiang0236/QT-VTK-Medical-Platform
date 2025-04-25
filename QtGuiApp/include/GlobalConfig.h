#pragma once
#include <string>
#include <memory>

namespace sysconfig {

    class GlobalConfig {
    public:

        GlobalConfig(const GlobalConfig&) = delete;
        GlobalConfig& operator=(const GlobalConfig&) = delete;

       
        static GlobalConfig& get();

      
        std::string appDataPath;
        int renderQuality;
        bool useHardwareAcceleration;

    private:
        GlobalConfig();  
    };
}
