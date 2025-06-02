// Viewer3D.h
#pragma once
#include "pch.h"
#include "VtkUtil_Export.h"  // 导出宏头文件
#include "ViewerBase.h"

class vtkImageResample;
class VTKUTIL_API Viewer3D : public ViewerBase {
    Q_OBJECT
public:
    explicit Viewer3D(QVTKOpenGLNativeWidget* widget);

  
    
    ~Viewer3D();

    void loadDirectory(const std::string& path);
    void loadBody(const std::string& path);
    void loadSurface(const std::string& path);
    void setThreshold(double value);
    void setSmoothingFactor(int iterations, double relaxation);
    void updateRendering();
    void VolumeRendering(vtkImageAlgorithm* imageReader);
    void SurfaceRendering(vtkImageAlgorithm* imageReader);
    void setupCubeAxes();
    void setupOrientationMarker();
private:
    void setupPipeline();
    void resetCamera();

    


    vtkSmartPointer<vtkMarchingCubes> m_marchingCubes;
    vtkSmartPointer<vtkSmoothPolyDataFilter> m_smoother;
    vtkSmartPointer<vtkPolyDataMapper> m_mapper;
    vtkSmartPointer<vtkActor> m_actor;
    vtkSmartPointer<vtkGPUVolumeRayCastMapper> m_GPUvolumeMapper;
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> m_CPUvolumeMapper;
    vtkSmartPointer<vtkOrientationMarkerWidget> m_orientationMarker; 
    vtkSmartPointer<vtkAxesActor> m_axes; 
    vtkSmartPointer<vtkColorTransferFunction> m_colorTransferFunction;
    vtkSmartPointer<vtkImageResample> m_resample;
    vtkSmartPointer<vtkPiecewiseFunction> m_opacityTransferFunction;
    vtkSmartPointer<vtkVolumeProperty> m_volumeProperty;
    vtkSmartPointer<vtkCubeAxesActor> m_cubeAxesActor;
    double m_threshold = 70.0;
    int m_smoothIterations = 50;
    double m_smoothRelaxation = 0.1;
};
