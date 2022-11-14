cmake_minimum_required (VERSION 2.8.1)
#cmake_policy(SET CMP0015 OLD) 

#头文件
include_directories(
	./
)

# 源文件及头文件
file(GLOB_RECURSE DbServer_CODELIST "${PROJECT_SOURCE_DIR}/dbserver/StdAfx.cpp" "${PROJECT_SOURCE_DIR}/dbserver/*.cc"  "${PROJECT_SOURCE_DIR}/dbserver/*.h")

# 代码分组
group_by_dir(${PROJECT_SOURCE_DIR}/dbserver ${DbServer_CODELIST})

# 添加指令
if(MSVC)
	add_custom_command(
		OUTPUT ${PROJECT_SOURCE_DIR}/dbserver/lua_interface.cc
		COMMAND ../3rd/tolua++/tolua++.exe -n server -o lua_interface.cc lua_interface.scp
		WORKING_DIRECTORY "../../dbserver"
	)
endif(MSVC)

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

# Dbserver输出目录
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${Bin_Dir}/dbserver)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${Bin_Dir}/dbserver)

add_executable(dbserver ${DbServer_CODELIST})
add_dependencies(dbserver common)
target_link_libraries(dbserver ${GAME_LIBRARIES})