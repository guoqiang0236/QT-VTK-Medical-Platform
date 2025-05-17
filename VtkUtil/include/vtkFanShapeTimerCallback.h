#pragma once

#include "pch.h"
#include "VtkUtil_Export.h"  // 导出宏头文件
#include <vector>
#include <complex>
#include <iostream>
#include <cmath>
#include <vtkCallbackCommand.h>

class VTKUTIL_API vtkFanShapeTimerCallback : public vtkCallbackCommand {
public:
    vtkFanShapeTimerCallback() = default;

    static vtkFanShapeTimerCallback* New();

    virtual void Execute(vtkObject* caller, unsigned long eventId, void* vtkNotUsed(callData)) override;
    void Stop(vtkRenderWindowInteractor* interactor);

        

    vtkSmartPointer<vtkPolyData> polyData;
    vtkSmartPointer<vtkFloatArray> scalars;
    std::vector<std::vector<std::complex<float>>>* allFrames = nullptr;
    int TimerCount = 0;
    int timerId = -1;
    size_t currentFrameIndex = 0;
    float globalMaxValue = 0.0f;
};
