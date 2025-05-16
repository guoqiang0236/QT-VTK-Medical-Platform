// VtkDemoClass.h - VTK动态库示例类
#pragma once
#include "VtkUtil_Export.h"  // 导出宏头文件
#include <vtkObject.h>       // VTK基础类

// 导出的VTK示例类（必须继承自vtkObjectBase子类）
class VTKUTIL_API VtkDemoClass : public vtkObject {
public:
  // VTK标准类型和New()宏
  vtkTypeMacro(VtkDemoClass, vtkObject);
  static VtkDemoClass* New();

  // 示例方法（导出方法）
  void PrintMessage(const char* msg);

protected:
  VtkDemoClass() = default;
  ~VtkDemoClass() override = default;

private:
  // 禁用拷贝和赋值
  VtkDemoClass(const VtkDemoClass&) = delete;
  void operator=(const VtkDemoClass&) = delete;
};