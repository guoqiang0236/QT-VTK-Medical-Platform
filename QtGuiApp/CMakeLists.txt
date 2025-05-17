cmake_minimum_required(VERSION 3.20)
project(QtGuiApp LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets Quick QuickWidgets)
find_package(VTK REQUIRED)

if(NOT VTK_FOUND)
    message(FATAL_ERROR "VTK not found!")
endif()
# 启用 AUTOMOC（关键！）
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 收集源文件（显式列出头文件）
file(GLOB SRC_FILES CONFIGURE_DEPENDS
    "source/*.cpp"
    "include/*.h"  # 显式包含头文件以触发 moc
)

qt_add_resources(RESOURCES resources.qrc)

# 创建可执行文件
# 根据构建类型动态设置 WIN32 选项
#add_executable(QtGuiApp WIN32 ${SRC_FILES} ${RESOURCES} res/icon/apprc.rc)  # Release 模式：无控制台
add_executable(QtGuiApp ${SRC_FILES} ${RESOURCES}  res/icon/apprc.rc)

# 包含目录（修正路径）
target_include_directories(QtGuiApp PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"  # 头文件路径
    ${VTK_INCLUDE_DIRS}
)
# 添加预编译头支持
target_precompile_headers(QtGuiApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/pch.h")


# 推荐用 target_include_directories
target_include_directories(QtGuiApp
    PRIVATE
        ${DCMTK_ROOT}/include
)

target_link_directories(QtGuiApp
    PRIVATE
        ${DCMTK_ROOT}/lib
        "${CMAKE_SOURCE_DIR}/lib"
)

# 链接库（补充关键 VTK 模块）
target_link_libraries(QtGuiApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGLWidgets
    Qt6::Quick
    Qt6::QuickWidgets
    VTK::GUISupportQt  # 必须链接此模块以支持 QVTKOpenGLNativeWidget
    VTK::RenderingOpenGL2
    VTK::InteractionStyle
    VTK::CommonCore
    VTK::RenderingImage     # vtkImageViewer2 的依赖模块
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
)

# 设置 VTK 模块依赖（确保头文件正确处理）
if(TARGET VTK::moc)
    add_dependencies(QtGuiApp VTK::moc)
endif()


