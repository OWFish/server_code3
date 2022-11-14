cmake_minimum_required (VERSION 2.8.1)
#cmake_policy(SET CMP0015 OLD) 

#头文件
include_directories(
	./
)

# 源文件及头文件
file(GLOB_RECURSE Center_CODELIST "${PROJECT_SOURCE_DIR}/centerserver/StdAfx.cpp" "${PROJECT_SOURCE_DIR}/centerserver/*.cc"  "${PROJECT_SOURCE_DIR}/centerserver/*.h")

# 代码分组
group_by_dir(${PROJECT_SOURCE_DIR}/centerserver ${Center_CODELIST})

#设置参数
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Debug)
set(CMAKE_C_FLAGS "-O0 -g3 -std=c++0x -Wall -c -fmessage-length=0 -MMD -MP")
#上面的貌似不管用
add_definitions(-std=c++11)


#链接库
link_directories( ${Libs_Dir} )

if(MSVC)
	set(GAME_LIBRARIES
		ws2_32
		srv
		Mswsock
		Dbghelp
		Winmm
		libmysql
		mysqlclient
		common
	)
else()
	set(GAME_LIBRARIES
		rt
		pthread
		mysqlclient
		#lua
		srv
		common
	)
endif(MSVC)

# CenterServer输出目录
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${Bin_Dir}/CenterServer)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${Bin_Dir}/CenterServer)

add_executable(centerserver ${Center_CODELIST})
add_dependencies(centerserver common)
target_link_libraries(centerserver ${GAME_LIBRARIES})

