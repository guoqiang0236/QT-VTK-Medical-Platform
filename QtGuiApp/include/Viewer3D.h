// Viewer3D.h
#pragma once
#include "pch.h"
#include "ViewerBase.h"
class Viewer3D : public ViewerBase {
    Q_OBJECT
public:
    explicit Viewer3D(QVTKOpenGLNativeWidget* widget);
    ~Viewer3D();

    void loadDirectory(const std::string& path);
    void loadDirectory_Body(const std::string& path);
    void loadRawData_Body(const std::string& path);
    void loadDirectory_Surface(const std::string& path);
    void loadRawData_Surface(const std::string& path);
    void setThreshold(double value);
    void setSmoothingFactor(int iterations, double relaxation);
    void updateRendering();
    void DicomsToVolumeRendering();
    void RawDataToVolumeRendering();
    void DicomsToSurfaceRendering();
    void RawDataToSurfaceRendering();

private:
    void setupPipeline();
    void resetCamera();


    vtkSmartPointer<vtkMarchingCubes> m_marchingCubes;
    vtkSmartPointer<vtkSmoothPolyDataFilter> m_smoother;
    vtkSmartPointer<vtkPolyDataMapper> m_mapper;
    vtkSmartPointer<vtkActor> m_actor;
    vtkSmartPointer<vtkGPUVolumeRayCastMapper> m_volumeMapper;
    vtkSmartPointer<vtkOrientationMarkerWidget> m_orientationMarker; 
    vtkSmartPointer<vtkAxesActor> m_axes; 
    double m_threshold = 70.0;
    int m_smoothIterations = 50;
    double m_smoothRelaxation = 0.1;
};
