cmake_minimum_required(VERSION 3.20)
project(medcical-QT)

# 全局设置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置路径优先级
list(APPEND CMAKE_PREFIX_PATH
    "D:/QT/6.8.2/msvc2022_64"
    "D:/vtk9.4.1/VTK-QT/VTK-INSTALL"
)
set(VTK_COMPONENTS
    CommonCore
    RenderingCore
    GUISupportQt
    RenderingOpenGL2
    InteractionStyle
    FiltersCore
    FiltersSources
    FiltersParallel
    IOGeometry
)

# 查找依赖
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets Quick QuickWidgets)
find_package(VTK REQUIRED)

if(NOT VTK_FOUND)
    message(FATAL_ERROR "VTK not found!")
endif()

# 添加子项目
add_subdirectory(VtkAPP)
add_subdirectory(QtGuiApp)
