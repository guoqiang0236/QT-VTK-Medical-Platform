#pragma once

//--------------------------------------------------
// QT 6.8.2 核心模块
//--------------------------------------------------
#include <QObject>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QMutexLocker>
#include <QMutex>
// QT GUI 模块
#include <QWidget>
#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

// QT 图形相关
#include <QPainter>
#include <QImage>
#include <QPixmap>

// QT 高级模块（按需启用）
//#include <QtCharts>     // 图表模块
//#include <QOpenGLWidget> // OpenGL支持

//--------------------------------------------------
// VTK 9.4.1 核心模块
//--------------------------------------------------
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkConeSource.h>

// VTK 可视化扩展
#include <vtkChartXY.h>
#include <vtkContextView.h>
#include <vtkPlot.h>
#include <vtkFloatArray.h>
#include <vtkTable.h>

// VTK IO 模块
#include <vtkPNGWriter.h>
#include <vtkXMLPolyDataWriter.h>

// VTK 高级模块（按需启用）
//#include <vtkDICOMImageReader.h>  // 医学图像
//#include <vtkPointCloudFilter.h>  // 点云处理


//自建模块
#include "GlobalConfig.h"
//--------------------------------------------------
// 防止 QT/VTK 宏冲突（可选）
//--------------------------------------------------
#ifdef slots
#undef slots  // 解决 QT slots 与 VTK/Python 的冲突
#endif