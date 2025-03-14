// VtkDemoClass.cpp - 示例类实现
#include "VtkDemoClass.h"
#include <vtkObjectFactory.h>  // VTK对象工厂
#include <vtkOutputWindow.h>  // 确保包含vtkOutputWindow的定义
// 必须使用vtkStandardNewMacro
vtkStandardNewMacro(VtkDemoClass);

void VtkDemoClass::PrintMessage(const char* msg) {
  vtkOutputWindow::GetInstance()->DisplayText(msg);
}