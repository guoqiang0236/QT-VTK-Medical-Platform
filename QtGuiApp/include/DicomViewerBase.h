// DicomViewerBase.h
#pragma once
#include <QVTKOpenGLNativeWidget.h>
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <QObject>
class DicomViewerBase:public QObject {
    Q_OBJECT
public:
	void setm_reader(vtkSmartPointer<vtkDICOMImageReader> reader) { m_reader = reader; }
	vtkDICOMImageReader* getm_reader() { return m_reader.Get(); }
    vtkRenderer* GetRenderer() const { return m_renderer; }
protected:
    explicit DicomViewerBase(QVTKOpenGLNativeWidget* widget);
    int GBKToUTF8(unsigned char* lpGBKStr, unsigned char* lpUTF8Str, int nUTF8StrLen);
    virtual ~DicomViewerBase() = default;

    std::string gbk_to_utf8(const char* strGBK);
	
    void initializeReader(const std::string& path);
    void setupRenderWindow();
    virtual void cleanup();

    QVTKOpenGLNativeWidget* m_vtkWidget;
    vtkSmartPointer<vtkDICOMImageReader> m_reader;
    vtkRenderer* m_renderer;
    
};