#include "ViewerBase.h"
#include <filesystem> // 添加这一行
#include <windows.h> 
#include <vtkFloatArray.h>
// 添加这一行
ViewerBase::ViewerBase(QVTKOpenGLNativeWidget* widget)
    : m_vtkWidget(widget),
    m_renderer(vtkRenderer::New()),
	m_rawreader(std::make_unique<RawReader>()),
	m_rawdataheaders(std::make_unique<std::vector<BMFMDataHeader>>()),
	m_rawdata_allData(std::make_unique<std::vector<std::vector<std::complex<float>>>>())
{
    m_vtkWidget->renderWindow()->AddRenderer(m_renderer);
}


int ViewerBase::GBKToUTF8(unsigned char* lpGBKStr, unsigned char* lpUTF8Str, int nUTF8StrLen)
{
    wchar_t* lpUnicodeStr = NULL;
    int nRetLen = 0;

    if (!lpGBKStr)  //如果GBK字符串为NULL则出错退出
        return 0;

    nRetLen = ::MultiByteToWideChar(CP_ACP, 0, (char*)lpGBKStr, -1, NULL, NULL);  //获取转换到Unicode编码后所需要的字符空间长度
    lpUnicodeStr = new WCHAR[nRetLen + 1];  //为Unicode字符串空间
    nRetLen = ::MultiByteToWideChar(CP_ACP, 0, (char*)lpGBKStr, -1, lpUnicodeStr, nRetLen);  //转换到Unicode编码
    if (!nRetLen)  //转换失败则出错退出
        return 0;

    nRetLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, NULL, 0, NULL, NULL);  //获取转换到UTF8编码后所需要的字符空间长度

    if (!lpUTF8Str)  //输出缓冲区为空则返回转换后需要的空间大小
    {
        if (lpUnicodeStr)
            delete[]lpUnicodeStr;
        return nRetLen;
    }

    if (nUTF8StrLen < nRetLen)  //如果输出缓冲区长度不够则退出
    {
        if (lpUnicodeStr)
            delete[]lpUnicodeStr;
        return 0;
    }

    nRetLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, (char*)lpUTF8Str, nUTF8StrLen, NULL, NULL);  //转换到UTF8编码

    if (lpUnicodeStr)
        delete[]lpUnicodeStr;

    return nRetLen;
}



//gbk转utf-8
std::string ViewerBase::gbk_to_utf8(const char* strGBK)
{
    int nRetLen = 0;
    char* lpUTF8Str = NULL;

    nRetLen = GBKToUTF8((unsigned char*)strGBK, NULL, NULL);
    lpUTF8Str = new char[nRetLen + 1];
    nRetLen = GBKToUTF8((unsigned char*)strGBK, (unsigned char*)lpUTF8Str, nRetLen);
    if (nRetLen) {
        return std::string(lpUTF8Str);
    }
    else {
        if (lpUTF8Str)
            delete[]lpUTF8Str;
    }
    return "";
}
void ViewerBase::initializeReader(const std::string& path) {
    if(!m_dicomreader)
        m_dicomreader = vtkSmartPointer<vtkDICOMImageReader>::New();
    if (std::filesystem::is_directory(path)) {
        m_dicomreader->SetDirectoryName(gbk_to_utf8(path.c_str()).c_str());

    }
    else {
        m_dicomreader->SetFileName(gbk_to_utf8(path.c_str()).c_str());

    }
    m_dicomreader->Update();
}

bool ViewerBase::GetIsGPU()
{
    if (!m_vtkWidget)
        return false;
    if (!m_vtkWidget->renderWindow())
        return false;

    vtkSmartPointer<vtkGPUVolumeRayCastMapper> tempMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    return tempMapper->IsRenderSupported(m_vtkWidget->renderWindow(), nullptr);
  
}

void ViewerBase::initializeImageReader(const std::string& path)
{
	m_imagereader = vtkSmartPointer<vtkImageReader>::New();
    m_imagereader->SetFileName(gbk_to_utf8(path.c_str()).c_str());
    m_imagereader->SetFileDimensionality(3);
    m_imagereader->SetDataScalarType(VTK_UNSIGNED_CHAR);
    m_imagereader->SetDataExtent(0, 255, 0, 255, 0, 255);
    m_imagereader->SetDataSpacing(0.9, 0.9, 0.9);
	m_imagereader->Update(); 
}

void ViewerBase::cleanup() {
    if (m_renderer) {
        m_renderer->RemoveAllViewProps();
        m_vtkWidget->renderWindow()->RemoveRenderer(m_renderer);
        m_renderer->Delete();
    }
    m_renderer = vtkRenderer::New();
    m_dicomreader = nullptr;
}