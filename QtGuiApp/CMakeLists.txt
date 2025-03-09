cmake_minimum_required(VERSION 3.20)
project(QtGuiApp LANGUAGES CXX)

# 启用 AUTOMOC（关键！）
set(CMAKE_AUTOMOC ON)

# 收集源文件（显式列出头文件）
file(GLOB SRC_FILES CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.h"  # 显式包含头文件以触发 moc
)

qt_add_resources(RESOURCES resources.qrc)

# 创建可执行文件
# 根据构建类型动态设置 WIN32 选项
# if (CMAKE_BUILD_TYPE STREQUAL "Release")
#     add_executable(QtGuiApp WIN32 ${SRC_FILES} ${RESOURCES})  # Release 模式：无控制台
# else()
#     add_executable(QtGuiApp ${SRC_FILES} ${RESOURCES})     # Debug 模式：有控制台
# endif()
#add_executable(QtGuiApp WIN32 ${SRC_FILES} ${RESOURCES})  # Release 模式：无控制台
add_executable(QtGuiApp ${SRC_FILES} ${RESOURCES}  icon/apprc.rc)

# 包含目录（修正路径）
target_include_directories(QtGuiApp PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"  # 头文件路径
    ${VTK_INCLUDE_DIRS}
)

# 链接库（补充关键 VTK 模块）
target_link_libraries(QtGuiApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGLWidgets
    VTK::GUISupportQt  # 必须链接此模块以支持 QVTKOpenGLNativeWidget
    VTK::RenderingOpenGL2
    VTK::InteractionStyle
    VTK::CommonCore
)

# 设置 VTK 模块依赖（确保头文件正确处理）
if(TARGET VTK::moc)
    add_dependencies(QtGuiApp VTK::moc)
endif()


