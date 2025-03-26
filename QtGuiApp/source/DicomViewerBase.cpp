#include "DicomViewerBase.h"
#include <filesystem> // �����һ��
#include <windows.h> // �����һ��
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

    if (!lpGBKStr)  //���GBK�ַ���ΪNULL������˳�
        return 0;

    nRetLen = ::MultiByteToWideChar(CP_ACP, 0, (char*)lpGBKStr, -1, NULL, NULL);  //��ȡת����Unicode���������Ҫ���ַ��ռ䳤��
    lpUnicodeStr = new WCHAR[nRetLen + 1];  //ΪUnicode�ַ����ռ�
    nRetLen = ::MultiByteToWideChar(CP_ACP, 0, (char*)lpGBKStr, -1, lpUnicodeStr, nRetLen);  //ת����Unicode����
    if (!nRetLen)  //ת��ʧ��������˳�
        return 0;

    nRetLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, NULL, 0, NULL, NULL);  //��ȡת����UTF8���������Ҫ���ַ��ռ䳤��

    if (!lpUTF8Str)  //���������Ϊ���򷵻�ת������Ҫ�Ŀռ��С
    {
        if (lpUnicodeStr)
            delete[]lpUnicodeStr;
        return nRetLen;
    }

    if (nUTF8StrLen < nRetLen)  //���������������Ȳ������˳�
    {
        if (lpUnicodeStr)
            delete[]lpUnicodeStr;
        return 0;
    }

    nRetLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, (char*)lpUTF8Str, nUTF8StrLen, NULL, NULL);  //ת����UTF8����

    if (lpUnicodeStr)
        delete[]lpUnicodeStr;

    return nRetLen;
}



//gbkתutf-8
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