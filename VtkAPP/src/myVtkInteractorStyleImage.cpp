#include "myVtkInteractorStyleImage.h"
#include <vtkObjectFactory.h>

#include <iostream>
#include <vtkRenderWindowInteractor.h>
vtkStandardNewMacro(myVtkInteractorStyleImage);
//----------------------------------------------------------------------------
void myVtkInteractorStyleImage::SetImageViewer(vtkImageViewer2* imageViewer) {
    _ImageViewer = imageViewer;
    _MinSlice = imageViewer->GetSliceMin();
    _MaxSlice = imageViewer->GetSliceMax();
    _Slice = _MinSlice;
    std::cout << "Slicer: Min = " << _MinSlice << ", Max = " << _MaxSlice << std::endl;
}

//----------------------------------------------------------------------------
void myVtkInteractorStyleImage::SetStatusMapper(vtkTextMapper* statusMapper) {
    _StatusMapper = statusMapper;
}

//----------------------------------------------------------------------------
void myVtkInteractorStyleImage::MoveSliceForward() {
    if (_Slice < _MaxSlice) {
        _Slice += 1;
        std::cout << "MoveSliceForward::Slice = " << _Slice << std::endl;
        _ImageViewer->SetSlice(_Slice);
        std::string msg = StatusMessage::Format(_Slice, _MaxSlice);
        _StatusMapper->SetInput(msg.c_str());
        _ImageViewer->Render();
    }
}

//----------------------------------------------------------------------------
void myVtkInteractorStyleImage::MoveSliceBackward() {
    if (_Slice > _MinSlice) {
        _Slice -= 1;
        std::cout << "MoveSliceBackward::Slice = " << _Slice << std::endl;
        _ImageViewer->SetSlice(_Slice);
        std::string msg = StatusMessage::Format(_Slice, _MaxSlice);
        _StatusMapper->SetInput(msg.c_str());
        _ImageViewer->Render();
    }
}

//----------------------------------------------------------------------------
void myVtkInteractorStyleImage::OnKeyDown() {
    std::string key = this->GetInteractor()->GetKeySym();
    if (key == "Up") {
        MoveSliceForward();
    } else if (key == "Down") {
        MoveSliceBackward();
    }
    vtkInteractorStyleImage::OnKeyDown();
}

//----------------------------------------------------------------------------
void myVtkInteractorStyleImage::OnMouseWheelForward() {
    MoveSliceForward();
}

//----------------------------------------------------------------------------
void myVtkInteractorStyleImage::OnMouseWheelBackward() {
    if (_Slice > _MinSlice) {
        MoveSliceBackward();
    }
}
