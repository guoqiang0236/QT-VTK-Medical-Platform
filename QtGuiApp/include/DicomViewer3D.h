// DicomViewer3D.h
#pragma once
#include "DicomViewerBase.h"
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkMarchingCubes.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkGPUVolumeRayCastMapper.h>  
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCubeAxesActor.h>
#include <vtkCamera.h>
#include <vtkTextProperty.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkAbstractVolumeMapper.h>  // ³éÏó»ùÀà
class DicomViewer3D : public DicomViewerBase {
    Q_OBJECT
public:
    explicit DicomViewer3D(QVTKOpenGLNativeWidget* widget);
    ~DicomViewer3D();

    void loadDirectory(const std::string& path);
    void loadDirectory_Body(const std::string& path);
    void loadDirectory_Surface(const std::string& path);
    void setThreshold(double value);
    void setSmoothingFactor(int iterations, double relaxation);
    void updateRendering();
    void loadVolumeRendering(const std::string& path);
    void loadSurfaceRendering(const std::string& path);

private:
    void setupPipeline();
    void resetCamera();


    vtkSmartPointer<vtkMarchingCubes> m_marchingCubes;
    vtkSmartPointer<vtkSmoothPolyDataFilter> m_smoother;
    vtkSmartPointer<vtkPolyDataMapper> m_mapper;
    vtkSmartPointer<vtkActor> m_actor;
    vtkSmartPointer<vtkGPUVolumeRayCastMapper> m_volumeMapper;
    double m_threshold = 70.0;
    int m_smoothIterations = 50;
    double m_smoothRelaxation = 0.1;
};
