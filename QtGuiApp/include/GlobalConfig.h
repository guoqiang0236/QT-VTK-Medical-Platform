#pragma once
#include <string>
namespace sysconfig {

    enum class VtkFileType {
        VTK_LEGACY,   // .vtk (传统格式)
        VTK_XML,      // .vti/.vtu/.vtp 等
        STL,          // .stl
        PLY,          // .ply
        OBJ,          // .obj
        CSV,          // .csv
        DICOM,        // .dcm
        DICOMS,       // .dcm files
        DICOMS3D,     // .dcm files3D
        NIFTI,        // .nii/.nii.gz
        META_IMAGE,   // .mhd/.mha
        JPEG,         // .jpg/.jpeg
        PNG,          // .png
        BMP,          // .bmp
        TIFF,         // .tiff/.tif
        VTK_JSON,     // .vtk.json (新式数据集
        UNKNOWN
    };

    class GlobalConfig {
    public:
        // 删除拷贝构造和赋值操作
        GlobalConfig(const GlobalConfig&) = delete;
        GlobalConfig& operator=(const GlobalConfig&) = delete;

        // 获取单例实例（Meyers' Singleton）
        static GlobalConfig& get();

        // 直接访问的配置项
        std::string appDataPath;
        int renderQuality = 100;
        bool useHardwareAcceleration = true;

    private:
        GlobalConfig();  // 私有构造函数
    };
}