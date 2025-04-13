// VtkFileTypeDetector.h
#pragma once
#include <string>

enum class VtkFileType {
    DICOM,
    DICOM_SERIES,
    RAW,
    UNKNOWN
};

class VtkFileTypeDetector {
public:
    VtkFileType detect(const std::string& path) const;
    
private:
    static std::string getExtension(const std::string& path);
    static bool isDicomDirectory(const std::string& path);
};