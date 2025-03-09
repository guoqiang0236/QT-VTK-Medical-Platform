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
    sysconfig::VtkFileType getFileTypeByExtension(const std::string& extension);
    void GraphicsRendering(sysconfig::VtkFileType filetype);
    void DicomGraphics();
    void CleanupVTKResources();
    void DicomFilesGraphics();
    QVTKOpenGLNativeWidget* GetVTKopenGLWidget();
    void testVTK();

private:
    std::string m_filename;  // 存储文件名
    sysconfig::VtkFileType m_filtype;
//vtk 成员
private:
    QVTKOpenGLNativeWidget* m_VTKopenGLWidget;
    vtkNew<vtkRenderer> m_renderer;
    vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;
    vtkSmartPointer<vtkImageViewer2> m_viewer;
    vtkSmartPointer<vtkGPUVolumeRayCastMapper> m_volumeMapper;
    vtkSmartPointer<vtkDICOMImageReader> DICOMreader;
    vtkNew<VtkDemoClass> m_test;
    vtkNew<myVtkInteractorStyleImage> myInteractorStyle;
    // 可添加其他私有成员...
};