# ============================================================================
# 项目配置
# ============================================================================
cmake_minimum_required(VERSION 3.20)
project(QtGuiApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================
# 查找依赖库
# ============================================================================
find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Gui 
    Widgets 
    OpenGLWidgets 
    Quick 
    QuickWidgets
)

find_package(VTK REQUIRED)
if(NOT VTK_FOUND)
    message(FATAL_ERROR "VTK not found!")
endif()

# ============================================================================
# Qt 自动化工具
# ============================================================================
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

# ============================================================================
# 源文件收集
# ============================================================================
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "source/*.cpp"
    "source/*.h"
)

file(GLOB UI_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui)

qt_add_resources(RESOURCES resources.qrc)

# ============================================================================
# 创建可执行文件
# ============================================================================
add_executable(QtGuiApp 
    ${SRC_FILES} 
    ${UI_FILES} 
    ${RESOURCES}
    res/icon/apprc.rc
)

# 仅在 Release 配置下设置为 WIN32 应用程序(无控制台)
set_target_properties(QtGuiApp PROPERTIES
    WIN32_EXECUTABLE $<CONFIG:Release>
)

target_precompile_headers(QtGuiApp PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/source/pch.h"
)

# ============================================================================
# 包含目录
# ============================================================================
target_include_directories(QtGuiApp PRIVATE 
    ${VTK_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ============================================================================
# 链接目录
# ============================================================================
target_link_directories(QtGuiApp PRIVATE 
    "${CMAKE_SOURCE_DIR}/lib"
)

# ============================================================================
# 链接库
# ============================================================================
target_link_libraries(QtGuiApp PRIVATE
    # Qt6 库
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGLWidgets
    Qt6::Quick
    Qt6::QuickWidgets
    
    # VTK 库
    VTK::GUISupportQt
    VTK::RenderingOpenGL2
    VTK::RenderingCore
    VTK::RenderingImage
    VTK::RenderingAnnotation
    VTK::RenderingVolume
    VTK::RenderingContextOpenGL2
    VTK::RenderingFreeType
    VTK::RenderingGL2PSOpenGL2
    VTK::RenderingVolumeOpenGL2
    VTK::InteractionStyle
    VTK::InteractionImage
    VTK::CommonCore
    VTK::CommonColor
    VTK::CommonDataModel
    VTK::IOImage
    VTK::ImagingCore
    VTK::ViewsContext2D
    VTK::FiltersGeneral
    VTK::FiltersGeometry
    VTK::FiltersModeling
    
    # 自定义库
    VtkUtil
    DcmtkUtil
    OpenCVUtil
    singleton
)

# ============================================================================
# VTK 依赖配置
# ============================================================================
if(TARGET VTK::moc)
    add_dependencies(QtGuiApp VTK::moc)
endif()

# ============================================================================
# 编译选项
# ============================================================================
if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()