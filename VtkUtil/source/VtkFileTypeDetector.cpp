// VtkFileTypeDetector.cpp
#include "VtkFileTypeDetector.h"
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

VtkFileType VtkFileTypeDetector::detect(const std::string& path) const {
    if(fs::is_directory(path)) {
        return isDicomDirectory(path) ? VtkFileType::DICOM_SERIES : VtkFileType::UNKNOWN;
    }
    
    std::string ext = getExtension(path);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    if(ext == ".dcm") return VtkFileType::DICOM;
    if(ext == ".raw") return VtkFileType::RAW;
    
    return VtkFileType::UNKNOWN;
}

std::string VtkFileTypeDetector::getExtension(const std::string& path) {
    size_t lastDot = path.find_last_of('.');
    return (lastDot != std::string::npos) ? path.substr(lastDot) : "";
}

bool VtkFileTypeDetector::isDicomDirectory(const std::string& path) {
    // 实现DICOM目录检测逻辑
    // 示例：检查目录下是否包含DICOM文件
    for(const auto& entry : fs::directory_iterator(path)) {
        if(entry.path().extension() == ".dcm") {
            return true;
        }
    }
    return false;
}