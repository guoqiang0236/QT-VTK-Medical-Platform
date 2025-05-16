// OpencvUtil_Export.h - 动态库导出宏定义
#pragma once


// Windows平台导出/导入宏
#ifdef _WIN32
  #ifdef OPENCVUTIL_EXPORTS
    #define OPENCVUTIL_API __declspec(dllexport)  // 编译DLL时导出
  #else
    #define OPENCVUTIL_API __declspec(dllimport)  // 使用DLL时导入
  #endif
#else
  #define OPENCVUTIL_API  // Linux/macOS不需要特殊声明
#endif

