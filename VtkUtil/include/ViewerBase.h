// ViewerBase.h
#pragma once
#include "pch.h"
#include "VtkUtil_Export.h"  // 导出宏头文件
#include "BasebandReader.h"
#include "VtkFileTypeDetector.h"

class VTKUTIL_API ViewerBase:public QObject {
    Q_OBJECT
public:
    void setm_reader(vtkSmartPointer<vtkDICOMImageReader> reader);
    vtkDICOMImageReader* getm_dicomreader();
    vtkImageReader* getm_imagereader();
    void setm__imagereader(vtkSmartPointer<vtkImageReader> reader);
    vtkRenderer* GetRenderer() const;
    void initializeReader(const std::string& path);
    bool GetIsGPU();
    VtkFileType GetFileType() const;
    void SetFileType(VtkFileType fileType);
protected:
    explicit ViewerBase(QVTKOpenGLNativeWidget* widget);

    int GBKToUTF8(unsigned char* lpGBKStr, unsigned char* lpUTF8Str, int nUTF8StrLen);
    virtual ~ViewerBase() = default;

    std::string gbk_to_utf8(const char* strGBK);
	

    void initializeImageReader(const std::string& path);
    virtual void cleanup();

    QVTKOpenGLNativeWidget* m_vtkWidget;
    vtkSmartPointer<vtkDICOMImageReader> m_dicomreader;
    vtkSmartPointer<vtkImageReader> m_imagereader;
    vtkRenderer* m_renderer;
	std::unique_ptr<RawReader> m_rawreader;
    std::unique_ptr<std::vector<BMFMDataHeader>> m_rawdataheaders = std::make_unique<std::vector<BMFMDataHeader>>();
    std::unique_ptr<std::vector<std::vector<std::complex<float>>>> m_rawdata_allData = std::make_unique<std::vector<std::vector<std::complex<float>>>>();
    VtkFileType m_fileType;
  
};