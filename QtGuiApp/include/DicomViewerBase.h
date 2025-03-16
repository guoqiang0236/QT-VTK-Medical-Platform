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
protected:
    explicit DicomViewerBase(QVTKOpenGLNativeWidget* widget);
    virtual ~DicomViewerBase() = default;

    void initializeReader(const std::string& path);
    void setupRenderWindow();
    virtual void cleanup();

    QVTKOpenGLNativeWidget* m_vtkWidget;
    vtkSmartPointer<vtkDICOMImageReader> m_reader;
    vtkRenderer* m_renderer;
    
};