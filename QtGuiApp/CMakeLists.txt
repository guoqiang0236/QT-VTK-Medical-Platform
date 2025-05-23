#设置cmake的最低版本要求
cmake_minimum_required(VERSION 3.20)

#设置c++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置项目名称和版本
project(QtGuiApp LANGUAGES CXX)

# 查找所需要的库
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets Quick QuickWidgets)
find_package(VTK REQUIRED)

if(NOT VTK_FOUND)
    message(FATAL_ERROR "VTK not found!")
endif()

# 启用 AUTOMOC（QT关键！）
set(CMAKE_AUTOMOC ON)   # 自动运行 moc，处理 Q_OBJECT 宏，生成元对象代码（信号槽机制依赖）
set(CMAKE_AUTOUIC ON)   # 自动处理 .ui 文件，生成对应的界面代码
set(CMAKE_AUTORCC ON)   # 自动处理 .qrc 资源文件，生成资源访问代码

# 收集源文件（显式列出头文件）
file(GLOB SRC_FILES CONFIGURE_DEPENDS
    "source/*.cpp"
    "include/*.h"  
)

qt_add_resources(RESOURCES resources.qrc)




# 创建可执行文件，根据构建类型动态设置 WIN32 选项
#add_executable(QtGuiApp WIN32 ${SRC_FILES} ${RESOURCES} res/icon/apprc.rc)  # Release 模式：无控制台
add_executable(QtGuiApp ${SRC_FILES} ${RESOURCES}  res/icon/apprc.rc)

# 添加预编译头支持
target_precompile_headers(QtGuiApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/pch.h")

# 库头文件目录
target_include_directories(QtGuiApp
    PRIVATE 
        ${VTK_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 库lib目录
target_link_directories(QtGuiApp
    PRIVATE
        "${CMAKE_SOURCE_DIR}/lib"
)

# 链接lib库
target_link_libraries(QtGuiApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGLWidgets
    Qt6::Quick
    Qt6::QuickWidgets
    VTK::GUISupportQt  
    VTK::RenderingOpenGL2
    VTK::InteractionStyle
    VTK::CommonCore
    VTK::RenderingImage     
    VTK::IOImage
    VTK::ViewsContext2D
    VTK::RenderingCore
    VTK::CommonColor
    VTK::CommonDataModel
    VTK::ImagingCore
    VTK::InteractionImage
    VTK::RenderingContextOpenGL2
    VTK::RenderingFreeType
    VTK::RenderingGL2PSOpenGL2
    VTK::RenderingVolumeOpenGL2
    VTK::RenderingAnnotation 
    VTK::RenderingVolume
    VTK::FiltersGeneral
    VTK::FiltersGeometry
    VTK::FiltersModeling
    VtkUtil
    DcmtkUtil
    OpenCVUtil
)

# 设置 VTK 模块依赖（确保头文件正确处理）
if(TARGET VTK::moc)
    add_dependencies(QtGuiApp VTK::moc)
endif()

#使用 QT_NO_DEBUG_OUTPUT 宏禁止release模式下的调试输出
if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()
