#include "vtkFanShapeTimerCallback.h"
#include "vtkPointData.h" 
vtkFanShapeTimerCallback* vtkFanShapeTimerCallback::New() {
    vtkFanShapeTimerCallback* cb = new vtkFanShapeTimerCallback;
    cb->TimerCount = 0;
    return cb;
}

void vtkFanShapeTimerCallback::Execute(vtkObject* caller, unsigned long eventId, void* vtkNotUsed(callData)) {
    if (vtkCommand::TimerEvent == eventId) {
        ++this->TimerCount;

        auto interactor = dynamic_cast<vtkRenderWindowInteractor*>(caller);
        if (!allFrames || allFrames->empty()) {
            std::cerr << "Frame data not available!" << std::endl;
            return;
        }

        const size_t nx = 66;
        const size_t nz = 1056;

        // 获取当前帧数据
        const auto& frameData = (*allFrames)[currentFrameIndex];

        scalars->Reset();
        for (size_t x = 0; x < nx; ++x) {
            for (size_t z = 0; z < nz; ++z) {
                const size_t index = x * nz + z;
                float magnitude = std::abs(frameData[index]) / globalMaxValue;
                float dB = 20.0f * std::log10(magnitude + 1e-10f);
                dB = std::max(-80.0f, dB); // 限制动态范围
                scalars->InsertNextValue(dB);
            }
        }

        polyData->GetPointData()->SetScalars(scalars);
        polyData->Modified();

        currentFrameIndex = (currentFrameIndex + 1) % allFrames->size();

        interactor->GetRenderWindow()->Render();
    }
}

void vtkFanShapeTimerCallback::Stop(vtkRenderWindowInteractor* interactor)
{
    if (timerId > -1) {
        interactor->DestroyTimer(timerId); // 停止定时器
        timerId = -1; // 重置定时器 ID
    }
}
