// VtkFileTypeDetector.h
#pragma once
#include <string>
#include "VtkUtil_Export.h"  // 导出宏头文件

enum class VTKUTIL_API VtkFileType {
    DICOM,
    DICOM_SERIES,
    RAW,
    COMPANYRAW,
    UNKNOWN
};

class  VTKUTIL_API VtkFileTypeDetector {
public:
    VtkFileType detect(const std::string& path) const;
    
private:
    static std::string getExtension(const std::string& path);
    static bool isDicomDirectory(const std::string& path);
};