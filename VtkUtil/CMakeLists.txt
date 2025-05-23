# 设置CMake最低版本
cmake_minimum_required(VERSION 3.20)

#设置c++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找所需要的库
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
find_package(VTK REQUIRED)
if (NOT VTK_FOUND)
  message(FATAL_ERROR "CylinderExample: Unable to find the VTK build folder.")
endif()

# 启用 AUTOMOC（QT关键！）
set(CMAKE_AUTOMOC ON)   # 自动运行 moc，处理 Q_OBJECT 宏，生成元对象代码（信号槽机制依赖）
set(CMAKE_AUTOUIC ON)   # 自动处理 .ui 文件，生成对应的界面代码
set(CMAKE_AUTORCC ON)   # 自动处理 .qrc 资源文件，生成资源访问代码

# 收集源文件（显式列出头文件）
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "source/*.cpp"
    "include/*.h"
)

# 创建动态库目标（SHARED表示生成DLL）
add_library(VtkUtil SHARED ${SRC_FILES})


# 添加预编译头支持
target_precompile_headers(VtkUtil PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/pch.h")

# 设置DLL导出宏（Windows下需要）
if(WIN32)
    target_compile_definitions(VtkUtil PRIVATE VTKUTIL_EXPORTS)
endif()



# 库头文件目录
target_include_directories(VtkUtil 
    PUBLIC 
        ${VTK_INCLUDE_DIRS} 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 库lib目录
target_link_directories(VtkUtil
    PRIVATE
        ${VTK_LIBRARY_DIRS}
)

# 链接lib库
target_link_libraries(VtkUtil 
    PRIVATE 
        ${VTK_LIBRARIES}
        Qt6::Core
)

# 自动初始化VTK模块
vtk_module_autoinit(
    TARGETS VtkUtil
    MODULES ${VTK_LIBRARIES}
)

#使用 QT_NO_DEBUG_OUTPUT 宏禁止release模式下的调试输出
if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()