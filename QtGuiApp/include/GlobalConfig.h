#pragma once
#include <string>
#include <memory>

namespace sysconfig {

    enum class VtkFileType {
        VTK_LEGACY,   // .vtk 
        VTK_XML,      // .vti/.vtu/.vtp 
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
        VTK_JSON,     // .vtk.json 
        UNKNOWN
    };

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
