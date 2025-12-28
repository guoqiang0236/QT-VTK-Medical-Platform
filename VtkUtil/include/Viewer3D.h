// Viewer3D.h
#pragma once
#include "pch.h"
#include "VtkUtil_Export.h"  // 导出宏头文件
#include "ViewerBase.h"


// 先定义透明度控制点结构
struct OpacityControlPoint {
    double huValue;
    double opacity;
};

// 定义透明度预设枚举
enum class OpacityPreset {
    SOFT_TISSUE_ONLY,   // 仅软组织
    BONE_ONLY,          // 仅骨骼
    COMPREHENSIVE,      // 综合显示
    CT_ANGIO,           // CT血管造影
    CUSTOM              // 自定义
};

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
    double CalculateOptimalResampleFactor(int totalVoxels);

    // 动态控制透明度传递函数的公共接口
    void setOpacityPoint(int index, double huValue, double opacity);
    void updateOpacityTransferFunction();
    void setOpacityPreset(OpacityPreset preset);
private:
    void setupPipeline();
    void resetCamera();

    
public slots:
 

    // 新增: 通过索引控制透明度点
    void setOpacityPointByIndex(int index, double opacity);
private:

    

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

  
    std::vector<OpacityControlPoint> m_opacityPoints;
};
