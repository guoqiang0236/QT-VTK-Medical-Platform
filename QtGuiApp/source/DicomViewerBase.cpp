#include "DicomViewerBase.h"
#include <filesystem> // 添加这一行
#include <windows.h> // 添加这一行
DicomViewerBase::DicomViewerBase(QVTKOpenGLNativeWidget* widget)
    : m_vtkWidget(widget),
    m_renderer(vtkRenderer::New())
{
    m_vtkWidget->renderWindow()->AddRenderer(m_renderer);
}

int DicomViewerBase::GBKToUTF8(unsigned char* lpGBKStr, unsigned char* lpUTF8Str, int nUTF8StrLen)
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
std::string DicomViewerBase::gbk_to_utf8(const char* strGBK)
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
void DicomViewerBase::initializeReader(const std::string& path) {
    m_reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    if (std::filesystem::is_directory(path)) {
        //m_reader->SetDirectoryName(path.c_str());
        m_reader->SetDirectoryName(gbk_to_utf8(path.c_str()).c_str());

    }
    else {
        //m_reader->SetFileName(path.c_str());
        m_reader->SetFileName(gbk_to_utf8(path.c_str()).c_str());

    }
    m_reader->Update();
}

void DicomViewerBase::cleanup() {
    if (m_renderer) {
        m_renderer->RemoveAllViewProps();
        m_vtkWidget->renderWindow()->RemoveRenderer(m_renderer);
        m_renderer->Delete();
    }
    m_renderer = vtkRenderer::New();
    m_reader = nullptr;
}