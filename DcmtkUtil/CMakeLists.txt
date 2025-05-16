cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 自动追踪源文件变化（CONFIGURE_DEPENDS是CMake 3.20+特性）
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "source/*.cpp"
    "include/*.h"
)

# 创建动态库目标（SHARED表示生成DLL）
add_library(DcmtkUtil SHARED ${SRC_FILES})



# 设置DLL导出宏（Windows下需要）
if(WIN32)
    target_compile_definitions(DcmtkUtil PRIVATE DcmtkUtil_EXPORTS)
endif()

# 修改点2：替换为动态库必须的宏定义
add_definitions(-DDCMTK_USE_DLL -D_WINDOWS -D_CRT_SECURE_NO_DEPRECATE)

# 路径配置
set(DCMTK_ROOT ${CMAKE_SOURCE_DIR}/Packages/DCMTK3.6.9)


set(DCMTK_LIBS
    iphlpapi
    ws2_32
    wsock32
    netapi32
    ofstd
    oflog
    dcmdata
    dcmnet
)

# 链接DCMTK库
target_include_directories(DcmtkUtil
    PRIVATE
        ${DCMTK_ROOT}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_directories(DcmtkUtil
    PRIVATE
        ${DCMTK_ROOT}/lib
)
target_link_libraries(DcmtkUtil
    PRIVATE
        ${DCMTK_LIBS}
)
