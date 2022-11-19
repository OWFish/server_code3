cmake_minimum_required (VERSION 2.8.1)
#cmake_policy(SET CMP0015 OLD) 

#头文件
include_directories(
	./
)

# 源文件及头文件
file(GLOB_RECURSE LoggerServer_CODELIST "${PROJECT_SOURCE_DIR}/loggerserver/stdafx.cpp" "${CMAKE_SOURCE_DIR}/loggerserver/*.cc" "${CMAKE_SOURCE_DIR}/loggerserver/*.h")

# 代码分组
group_by_dir(${PROJECT_SOURCE_DIR}/loggerserver ${LoggerServer_CODELIST})

#链接库
link_directories( ${Libs_Dir} )

if(MSVC)
	set(GAME_LIBRARIES
		ws2_32
		srv
		Winmm
		Mswsock
		Dbghelp
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

# 添加指令
if(MSVC)
	add_custom_command(
		OUTPUT ${PROJECT_SOURCE_DIR}/loggerserver/lua_interface.cc
		COMMAND ../3rd/tolua++/tolua++.exe -n server -o lua_interface.cc lua_interface.scp
		WORKING_DIRECTORY "../../loggerserver"
	)
endif(MSVC)

# LoggerServer输出目录
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${Bin_Dir}/loggerserver)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${Bin_Dir}/loggerserver)
#SET(EXECUTABLE_OUTPUT_PATH ${Bin_Dir}/loggerserver)

# 生成可执行文件
add_executable(loggerserver ${LoggerServer_CODELIST})
add_dependencies(loggerserver common)
target_link_libraries(loggerserver ${GAME_LIBRARIES})