#include "myVtkInteractorStyleImage.h"
#include <vtkObjectFactory.h>
#include <iostream>
#include <vtkRenderWindowInteractor.h>

vtkStandardNewMacro(myVtkInteractorStyleImage);

void myVtkInteractorStyleImage::SetImageViewer(vtkImageViewer2* imageViewer) {
    _ImageViewer = imageViewer;
    _MinSlice = imageViewer->GetSliceMin()+1;
    _MaxSlice = imageViewer->GetSliceMax()+1;
    _Slice = _MinSlice;
}

void myVtkInteractorStyleImage::SetStatusMapper(vtkTextMapper* statusMapper) {
    _StatusMapper = statusMapper;
}

void myVtkInteractorStyleImage::SetSliceChangedCallback(SliceChangedCallback callback) {
    _SliceChangedCallback = callback;
}

void myVtkInteractorStyleImage::MoveSliceForward() {
    if (_Slice < _MaxSlice) {
        _Slice += 1;
        _ImageViewer->SetSlice(_Slice-1);
        std::string msg = StatusMessage::Format(_Slice, _MaxSlice);
        _StatusMapper->SetInput(msg.c_str());
        _ImageViewer->Render();
        if (_SliceChangedCallback) {
            _SliceChangedCallback(_Slice);
        }
    }
}

void myVtkInteractorStyleImage::MoveSliceBackward() {
    if (_Slice > _MinSlice) {
        _Slice -= 1;
        _ImageViewer->SetSlice(_Slice-1);
        std::string msg = StatusMessage::Format(_Slice, _MaxSlice);
        _StatusMapper->SetInput(msg.c_str());
        _ImageViewer->Render();
        if (_SliceChangedCallback) {
            _SliceChangedCallback(_Slice);
        }
    }
}
void myVtkInteractorStyleImage::SetCurrentSliceNumberNow(int slice)
{
    _Slice -= slice;
}

void myVtkInteractorStyleImage::OnKeyDown() {
    std::string key = this->GetInteractor()->GetKeySym();
    if (key == "Up") {
        MoveSliceForward();
    }
    else if (key == "Down") {
        MoveSliceBackward();
    }
    vtkInteractorStyleImage::OnKeyDown();
}

void myVtkInteractorStyleImage::EnableMouseWheel(bool enable) {
    _MouseWheelEnabled = enable;
}

void myVtkInteractorStyleImage::OnMouseWheelForward() {
    if (_MouseWheelEnabled) {
        MoveSliceForward();
    }
}

void myVtkInteractorStyleImage::OnMouseWheelBackward() {
    if (_MouseWheelEnabled) {
        if (_Slice > _MinSlice) {
            MoveSliceBackward();
        }
    }
}

void myVtkInteractorStyleImage::SetStatusMapper(const std::string& msg) {
    if (_StatusMapper) {
        _StatusMapper->SetInput(msg.c_str());
    }
}
