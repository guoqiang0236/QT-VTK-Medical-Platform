// Viewer2D.h
#pragma once
#include "pch.h"
#include "myVtkInteractorStyleImage.h"
#include "ViewerBase.h"
#include "vtkFanShapeTimerCallback.h"
enum class SliceOrientation {
    AXIAL = 0,
    CORONAL = 1,
    SAGITTAL = 2
};

class Viewer2D : public ViewerBase {
    Q_OBJECT
public:
    explicit Viewer2D(QVTKOpenGLNativeWidget* widget);
    ~Viewer2D();

    void loadDicomFile(const std::string& path);
    void loadDicomDirectory(const std::string& path);
	void loadRawData();
    void loadCompanyRawData(const std::string& path);
    void resetCamera();
    void setViewOrientation(SliceOrientation orientation);
    
    void cleanup()override;
	void setOrientation(int orientationation) { m_orientation = orientationation; }
    void setrawdataViewOrientation(SliceOrientation orientation);
    void startInteractor();
    int getTotalSlices() const;
    void setSlice(int slice);
	void setmessage(const std::string& msg) { message = msg; }
	myVtkInteractorStyleImage* getInteractorStyle() { return m_interactorStyle; }

signals:
    void sliceChanged(int slice);
private:
    int m_orientation;
    void setupViewer();
	void setuprawviewer();
    void setupAnnotations();

    void setupInteractor();

    void updateSliceText();
    
    vtkSmartPointer<vtkImageViewer2> m_imageViewer;
    vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;
    vtkSmartPointer<myVtkInteractorStyleImage> m_interactorStyle;
    vtkSmartPointer<vtkImageReslice> m_reslice;
    vtkSmartPointer<vtkMatrix4x4> m_matrix;
    std::string message;
    vtkSmartPointer<vtkFanShapeTimerCallback> m_fanshapecallback;
};