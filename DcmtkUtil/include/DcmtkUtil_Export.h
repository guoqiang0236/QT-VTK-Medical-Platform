// DcmtkUtil_EXPORTS.h - 动态库导出宏定义
#pragma once



// Windows平台导出/导入宏
#ifdef _WIN32
#ifdef DcmtkUtil_EXPORTS
#define DcmtkUtil_API __declspec(dllexport)  // 编译DLL时导出
#else
#define DcmtkUtil_API __declspec(dllimport)  // 使用DLL时导入
#endif
#else
#define DcmtkUtil_API
#endif
