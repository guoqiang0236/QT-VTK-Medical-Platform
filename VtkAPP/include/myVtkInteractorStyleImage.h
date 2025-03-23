#ifndef MY_VTK_INTERACTOR_STYLE_IMAGE_H
#define MY_VTK_INTERACTOR_STYLE_IMAGE_H

#include "VtkApp_Export.h"
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageViewer2.h>
#include <vtkTextMapper.h>
#include <functional>
#include <string>
#include <sstream>

class StatusMessage
{
public:
    static std::string Format(int slice, int maxSlice)
    {
        std::stringstream tmp;
        tmp << "Slice Number  " << slice + 1 << "/" << maxSlice + 1;
        return tmp.str();
    }
};

class VTKAPP_API myVtkInteractorStyleImage : public vtkInteractorStyleImage {
public:
    using SliceChangedCallback = std::function<void(int)>;

    static myVtkInteractorStyleImage* New();
    vtkTypeMacro(myVtkInteractorStyleImage, vtkInteractorStyleImage);

    void SetImageViewer(vtkImageViewer2* imageViewer);
    void SetStatusMapper(vtkTextMapper* statusMapper);
    void SetStatusMapper(const std::string& msg);
    void SetSliceChangedCallback(SliceChangedCallback callback);
    void SetCurrentSliceNumberNow(int slice);

    void EnableMouseWheel(bool enable); // �����ķ���
protected:
    vtkImageViewer2* _ImageViewer;
    vtkTextMapper* _StatusMapper;
    int _Slice;
    int _MinSlice;
    int _MaxSlice;
    SliceChangedCallback _SliceChangedCallback;

    void MoveSliceForward();
    void MoveSliceBackward();
   
    void OnKeyDown() override;
    void OnMouseWheelForward() override;
    void OnMouseWheelBackward() override;
    bool _MouseWheelEnabled = true; // �����ı�־
};

#endif // MY_VTK_INTERACTOR_STYLE_IMAGE_H
