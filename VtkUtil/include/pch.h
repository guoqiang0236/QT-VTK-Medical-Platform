// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// Qt 相关头文件
#include <QObject>
#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QIcon>
#include <QSlider>
#include <QPushButton>
#include <QComboBox>
#include <QVTKOpenGLNativeWidget.h>
#include <QDateTime>
#include <QTimer>
#include <QThreadPool>

// VTK 相关头文件
#include <vtkCamera.h>
#include <vtkImageReslice.h>
#include <vtkMatrix4x4.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkMarchingCubes.h>
#include <vtkRenderer.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkAbstractVolumeMapper.h>  // 抽象基类
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>
#include <vtkTextProperty.h>
#include <vtkGPUVolumeRayCastMapper.h>  
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCubeAxesActor.h>
#include <vtkImageReader.h>
#include <vtkImageViewer2.h>
#include <vtkPolyData.h>
#include <vtkFloatArray.h>


#endif //PCH_H
