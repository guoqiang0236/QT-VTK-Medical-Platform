// DicomViewer2D.h
#pragma once
#include "DicomViewerBase.h"
#include "myVtkInteractorStyleImage.h"
#include "vtkCamera.h"
enum class SliceOrientation {
    AXIAL = 0,
    CORONAL = 1,
    SAGITTAL = 2
};

class DicomViewer2D : public DicomViewerBase {
public:
    explicit DicomViewer2D(QVTKOpenGLNativeWidget* widget);
    ~DicomViewer2D();

    void loadFile(const std::string& path);
    void loadDirectory(const std::string& path);
    void resetCamera();
    void setViewOrientation(SliceOrientation orientation);
    void cleanup()override;
    void setOrientation(int orientationation) { m_orientation = orientationation; }
private:
    int m_orientation;
    void setupViewer();
    void setupAnnotations();

    void setupInteractor();

    void updateSliceText();
    
    vtkSmartPointer<vtkImageViewer2> m_imageViewer;
    vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;
    vtkSmartPointer<myVtkInteractorStyleImage> m_interactorStyle;
};