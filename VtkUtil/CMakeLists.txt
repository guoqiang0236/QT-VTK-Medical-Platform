# 设置CMake最低版本
cmake_minimum_required(VERSION 3.20)

# 找到Vtk库
find_package(VTK REQUIRED)
if (NOT VTK_FOUND)
  message(FATAL_ERROR "CylinderExample: Unable to find the VTK build folder.")
endif()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "source/*.cpp"
    "include/*.h"
)



# 创建动态库目标（SHARED表示生成DLL）
add_library(VtkUtil SHARED ${SRC_FILES})

# 设置DLL导出宏（Windows下需要）
if(WIN32)
    target_compile_definitions(VtkUtil PRIVATE VTKUTIL_EXPORTS)
endif()

# 包含头文件目录
target_include_directories(VtkUtil PUBLIC ${VTK_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)


# message(STATUS "VTK_VERSION: ${VTK_VERSION}")
# message(STATUS "VTK_LIBRARIES: ${VTK_LIBRARIES}")
# message(STATUS "VTK_INCLUDE_DIRS: ${VTK_INCLUDE_DIRS}")
target_link_libraries(VtkUtil PRIVATE ${VTK_LIBRARIES})




# 自动初始化VTK模块
vtk_module_autoinit(
    TARGETS VtkUtil
    MODULES ${VTK_LIBRARIES}
)

