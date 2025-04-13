#include "ViewerBase.h"
#include <filesystem> // �����һ��
#include <windows.h> // �����һ��
ViewerBase::ViewerBase(QVTKOpenGLNativeWidget* widget)
    : m_vtkWidget(widget),
    m_renderer(vtkRenderer::New())
{
    m_vtkWidget->renderWindow()->AddRenderer(m_renderer);
}

int ViewerBase::GBKToUTF8(unsigned char* lpGBKStr, unsigned char* lpUTF8Str, int nUTF8StrLen)
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
    m_dicomreader = vtkSmartPointer<vtkDICOMImageReader>::New();
    if (std::filesystem::is_directory(path)) {
        //m_dicomreader->SetDirectoryName(path.c_str());
        m_dicomreader->SetDirectoryName(gbk_to_utf8(path.c_str()).c_str());

    }
    else {
        //m_dicomreader->SetFileName(path.c_str());
        m_dicomreader->SetFileName(gbk_to_utf8(path.c_str()).c_str());

    }
    m_dicomreader->Update();
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