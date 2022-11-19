cmake_minimum_required (VERSION 2.8.1)

#头文件
include_directories(
	./
)

# 源文件及头文件
file(GLOB_RECURSE Common_LIST "${PROJECT_SOURCE_DIR}/common/*.cc" "${PROJECT_SOURCE_DIR}/common/*.h")

# 项目文件分组
group_by_dir( ${PROJECT_SOURCE_DIR}/common ${Common_LIST} )

# 输出目录
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${Root_Dir}/libs)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${Root_Dir}/libs)

#生成目标
add_library(common STATIC ${Common_LIST})