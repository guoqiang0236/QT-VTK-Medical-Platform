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
    "${CMAKE_SOURCE_DIR}/Packages/VTK9.4.1"
)

# 现代化输出目录管理（重要！）
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

# 按构建类型隔离输出目录（VS多配置关键设置）
foreach(OUTPUTCONFIG IN ITEMS DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
    string(TOUPPER ${OUTPUTCONFIG} CONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG} ${CMAKE_CURRENT_LIST_DIR}/bin/${OUTPUTCONFIG})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG} ${CMAKE_CURRENT_LIST_DIR}/bin/${OUTPUTCONFIG})
endforeach()

# 添加子项目
add_subdirectory(VtkUtil)
add_subdirectory(QtGuiApp)
#add_subdirectory(QtGuiAppTests)
add_subdirectory(DcmtkUtil)
add_subdirectory(OpenCVUtil)

# 设置 QtGuiApp 为 Visual Studio 的启动项目
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT QtGuiApp)