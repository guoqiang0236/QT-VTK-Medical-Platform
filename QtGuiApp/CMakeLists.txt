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
    LinguistTools
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
# 翻译文件配置
# ============================================================================
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/translations)

set(TS_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/translations/QtGuiApp_zh_CN.ts
    ${CMAKE_CURRENT_SOURCE_DIR}/translations/QtGuiApp_en_US.ts
)

# ✅ 使用 qt_create_translation 从源代码提取翻译字符串并生成 .ts 文件
qt_create_translation(QM_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/source  # 扫描源代码目录
    ${CMAKE_CURRENT_SOURCE_DIR}/ui      # 扫描 UI 文件目录
    ${TS_FILES}
    OPTIONS -no-obsolete
)

# ✅ 修复：使用 qt_add_translation 代替 qt_create_translation（更稳定）
# 如果你需要从源代码提取翻译，手动运行 lupdate
# qt_add_translation(QM_FILES ${TS_FILES})


# ============================================================================
# 创建可执行文件
# ============================================================================
add_executable(QtGuiApp 
    ${SRC_FILES} 
    ${UI_FILES} 
    ${RESOURCES}
    ${QM_FILES}
    res/icon/apprc.rc
)

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
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGLWidgets
    Qt6::Quick
    Qt6::QuickWidgets
    
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


# 调试：输出最终的 QM 文件路径
message(STATUS "🎯 Translation files will be copied after build completes")

# ============================================================================
# 安装翻译文件
# ============================================================================
install(FILES ${QM_FILES} DESTINATION translations)


# ============================================================================
# ✅ 复制翻译文件到输出目录（移到最后）
# ============================================================================
# 等待 QM 文件生成后再复制
foreach(QM_FILE IN LISTS QM_FILES)
    get_filename_component(QM_FILENAME ${QM_FILE} NAME)
    
    # 为每个构建配置复制
    foreach(CONFIG IN ITEMS DEBUG RELEASE)
        string(TOUPPER ${CONFIG} CONFIG_UPPER)
        set(OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER}}/translations)
        
        add_custom_command(TARGET QtGuiApp POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${QM_FILE}
                ${OUTPUT_DIR}/${QM_FILENAME}
            COMMENT "📦 Copying ${QM_FILENAME} to ${OUTPUT_DIR}"
            VERBATIM
        )
    endforeach()
    
endforeach()
