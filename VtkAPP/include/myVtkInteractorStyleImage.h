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
#include <string>

// Needed to easily convert int to std::string.
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
    static myVtkInteractorStyleImage* New();
    vtkTypeMacro(myVtkInteractorStyleImage, vtkInteractorStyleImage);

    void SetImageViewer(vtkImageViewer2* imageViewer);
    void SetStatusMapper(vtkTextMapper* statusMapper);

protected:
    vtkImageViewer2* _ImageViewer;
    vtkTextMapper* _StatusMapper;
    int _Slice;
    int _MinSlice;
    int _MaxSlice;

    void MoveSliceForward();
    void MoveSliceBackward();

    // 重写 VTK 事件处理函数
    void OnKeyDown() override;
    void OnMouseWheelForward() override;
    void OnMouseWheelBackward() override;
};

#endif // MY_VTK_INTERACTOR_STYLE_IMAGE_H