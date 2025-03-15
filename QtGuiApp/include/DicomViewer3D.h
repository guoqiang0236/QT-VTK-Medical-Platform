// DicomViewer3D.h
#pragma once
#include "DicomViewerBase.h"
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkMarchingCubes.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
class DicomViewer3D : public DicomViewerBase {
public:
    explicit DicomViewer3D(QVTKOpenGLNativeWidget* widget);
    ~DicomViewer3D();

    void loadDirectory(const std::string& path);
    void setThreshold(double value);
    void setSmoothingFactor(int iterations, double relaxation);
    void updateRendering();

private:
    void setupPipeline();
    void resetCamera();
    
    vtkSmartPointer<vtkMarchingCubes> m_marchingCubes;
    vtkSmartPointer<vtkSmoothPolyDataFilter> m_smoother;
    vtkSmartPointer<vtkPolyDataMapper> m_mapper;
    vtkSmartPointer<vtkActor> m_actor;
    
    double m_threshold = 70.0;
    int m_smoothIterations = 50;
    double m_smoothRelaxation = 0.1;
};