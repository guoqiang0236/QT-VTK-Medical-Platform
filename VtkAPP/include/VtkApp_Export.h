// VtkApp_Export.h - 动态库导出宏定义
#pragma once
// VTK前置声明（解决类型识别问题）
class vtkRenderer;  // 添加基类声明

// Windows平台导出/导入宏
#ifdef _WIN32
  #ifdef VTKAPP_EXPORTS
    #define VTKAPP_API __declspec(dllexport)  // 编译DLL时导出
  #else
    #define VTKAPP_API __declspec(dllimport)  // 使用DLL时导入
  #endif
#else
  #define VTKAPP_API  // Linux/macOS不需要特殊声明
#endif

