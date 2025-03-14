#pragma once
#include <string>
#include <GlobalConfig.h>
#include <qvtkopenglnativewidget.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageViewer2.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkDICOMImageReader.h>
#include "myVtkInteractorStyleImage.h"
#include "VtkDemoClass.h"
class FileManager {
public:
    
    explicit FileManager();

    
    void processData() const;
    void UpdatePlotFile(const std::string fileaddr);
    void UpdatePlotFiles(const std::string fileaddr);
    void UpdatePlotFiles3D(const std::string fileaddr);
    sysconfig::VtkFileType getFileTypeByExtension(const std::string& extension);
    void GraphicsRendering(sysconfig::VtkFileType filetype);
    void DicomGraphics();
    void CleanupVTKResources();
    void DicomFilesGraphics();
    void DicomFilesGraphics3D();
    void ViewChanged(const std::string viewport);
    QVTKOpenGLNativeWidget* GetVTKopenGLWidget();
    void testVTK();

private:
    std::string m_filename;  // 存储文件名
    sysconfig::VtkFileType m_filtype;
//vtk 成员
private:
    QVTKOpenGLNativeWidget* m_VTKopenGLWidget;
    vtkSmartPointer<vtkRenderWindow> m_renderWindow;
    vtkSmartPointer<vtkRenderer> m_renderer;
    vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;
    vtkSmartPointer<vtkImageViewer2> m_viewer;
    vtkSmartPointer<vtkGPUVolumeRayCastMapper> m_volumeMapper;
    vtkSmartPointer<vtkDICOMImageReader> DICOMreader;
    vtkNew<VtkDemoClass> m_test;
    vtkNew<myVtkInteractorStyleImage> myInteractorStyle;
    vtkSmartPointer<vtkPolyDataMapper> m_mapper;
    vtkSmartPointer<vtkActor> m_actor;
    // 可添加其他私有成员...
};