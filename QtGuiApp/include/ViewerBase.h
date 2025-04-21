// ViewerBase.h
#pragma once



#include "pch.h"

class ViewerBase:public QObject {
    Q_OBJECT
public:
	void setm_reader(vtkSmartPointer<vtkDICOMImageReader> reader) { m_dicomreader = reader; }
	vtkDICOMImageReader* getm_dicomreader() { return m_dicomreader.Get(); }
	vtkImageReader* getm_imagereader() { return m_imagereader.Get(); }
	void setm__imagereader(vtkSmartPointer<vtkImageReader> reader) { m_imagereader = reader; }
    vtkRenderer* GetRenderer() const { return m_renderer; }
	
protected:
    explicit ViewerBase(QVTKOpenGLNativeWidget* widget);
    int GBKToUTF8(unsigned char* lpGBKStr, unsigned char* lpUTF8Str, int nUTF8StrLen);
    virtual ~ViewerBase() = default;

    std::string gbk_to_utf8(const char* strGBK);
	
    void initializeReader(const std::string& path);
    void initializeImageReader(const std::string& path);
    void setupRenderWindow();
    virtual void cleanup();

    QVTKOpenGLNativeWidget* m_vtkWidget;
    vtkSmartPointer<vtkDICOMImageReader> m_dicomreader;
    vtkSmartPointer<vtkImageReader> m_imagereader;
    vtkRenderer* m_renderer;
    
};