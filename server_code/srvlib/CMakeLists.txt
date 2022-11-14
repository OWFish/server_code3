cmake_minimum_required (VERSION 2.8.1)

#项目名
project (srv)

#头文件
include_directories(
        ./
        ./include
        ./3rd/gtest-1.3.0
        ./3rd/lua
        ./3rd/zlib
        ./3rd/tolua++
)
#源目录
FILE(GLOB_RECURSE H_LIST "*.h")
FILE(GLOB_RECURSE HPP_LIST "*.hpp")
FILE(GLOB_RECURSE CPP_LIST "*.cpp")
FILE(GLOB_RECURSE CC_LIST "*.cc")
FILE(GLOB_RECURSE C_LIST "*.c")
set(SRV_SRCS ${CPP_LIST} ${CC_LIST} ${C_LIST})
set(HEAD_SRCS ${H_LIST} ${HPP_LIST})

if(MSVC)
        # 头文件
        include_directories(
        ./3rd/mysql
        )
        # 编译选项
        ADD_DEFINITIONS(/W3 /wd"4996" /wd"4819" /wd"4091" /wd"4099" /wd"4800" /wd"4996")
        SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /MP4")
        SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
else()
        # 头文件
        include_directories(
        /proj/lib/mysql-5.2/include
        /usr/include/mysql
        /usr/local/include/curl
        )

        # 编译选项
        SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -Wall -Wextra -Wfatal-errors -std=c++11 -fpermissive -D_DEBUG -g -ggdb")
        SET(CMAKE_CXX_FLAGS_RELEASE "-O0 -g -Wall -std=c++11 -fpermissive -DNDEBUG")
        #add_definitions("-O0 -g3 -gdwarf-2 -std=c++11 -Wall -c -fmessage-length=0 -MMD -MP")
endif(MSVC)

if(MSVC)
# 项目内文件分组工具
function(group_by_dir source_dir)
        message(STATUS "${ARGV0}")
    foreach(FILE ${ARGN})
        message(STATUS "${FILE}")

        # 获取文件绝对路径
        get_filename_component(FULL_NAME "${FILE}" ABSOLUTE)
        # 获取文件父路径
        get_filename_component(PARENT_DIR "${FULL_NAME}" PATH)
        # 移除父路径中的源码根路径
        string(REPLACE "${ARGV0}" "" GROUP "${PARENT_DIR}")

        # 确保路径使用windows路径符号
        string(REPLACE "/" "\\" GROUP "${GROUP}")
        # 分组
        source_group("${GROUP}" FILES "${FILE}")
    endforeach()
endfunction(group_by_dir)

# 项目分组
group_by_dir(${PROJECT_SOURCE_DIR} ${SRV_SRCS})
group_by_dir(${PROJECT_SOURCE_DIR} ${HEAD_SRCS})
endif(MSVC)

#生成目标
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/../libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/../libs)
add_library(srv STATIC ${SRV_SRCS} ${HEAD_SRCS})