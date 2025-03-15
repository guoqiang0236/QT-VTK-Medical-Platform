cmake_minimum_required(VERSION 3.20)
project(medcical-QT)
# 设置 CMake 编码为 UTF - 8
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /utf-8")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
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
# 现代化输出目录管理（重要！）
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 按构建类型隔离输出目录（VS多配置关键设置）
foreach(OUTPUTCONFIG IN ITEMS DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
    string(TOUPPER ${OUTPUTCONFIG} CONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG} ${CMAKE_BINARY_DIR}/bin/${OUTPUTCONFIG})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG} ${CMAKE_BINARY_DIR}/bin/${OUTPUTCONFIG})
endforeach()

# 查找依赖
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets Quick QuickWidgets)
find_package(VTK REQUIRED)

if(NOT VTK_FOUND)
    message(FATAL_ERROR "VTK not found!")
endif()

# 添加子项目
add_subdirectory(VtkAPP)
add_subdirectory(QtGuiApp)
