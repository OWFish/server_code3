cmake_minimum_required (VERSION 2.8.1)
#cmake_policy(SET CMP0015 OLD) 

#头文件
include_directories(
	./
	./base
	./protocol
	./systems
	./entity
	./redis
)

# 源文件及头文件
file(GLOB_RECURSE GameWorld_CODELIST "${PROJECT_SOURCE_DIR}/gameworld/StdAfx.cpp" "${PROJECT_SOURCE_DIR}/gameworld/*.cc"  "${PROJECT_SOURCE_DIR}/gameworld/*.h")

# 代码分组
group_by_dir(${PROJECT_SOURCE_DIR}/gameworld ${GameWorld_CODELIST})

#链接库
link_directories( ${Libs_Dir} )

if(MSVC)
	set(GAME_LIBRARIES
		libcmtd
		ws2_32
		srv
		Winmm
		Dbghelp
		Mswsock
		libmysql
		mysqlclient
		common
		Win32_Interop
		hiredis
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

# Gameworld输出目录
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${Bin_Dir}/gameworld)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${Bin_Dir}/gameworld)

# log_def.h、auto_protocol.lua、serverInterface.cc输出文件
SET(LOGDEF_OUTPUT ${PROJECT_SOURCE_DIR}/gameworld/script/export/log_def.data)
SET(PROTOCOL_OUTPUT ${Bin_Dir}/GameWorld/data/functions/protocol.lua)
SET(INTERFACE_OUTPUT ${PROJECT_SOURCE_DIR}/gameworld/script/tolua++/serverInterface.cc)

# 添加指令
if(MSVC)
	add_custom_command(
		OUTPUT ${LOGDEF_OUTPUT}
		COMMAND ../3rd/lua514/lua5.1.exe ./plus/log_def.lua
		WORKING_DIRECTORY "../../gameworld"
	)

	add_custom_command(
		OUTPUT ${PROTOCOL_OUTPUT}
		COMMAND ../3rd/lua514/lua5.1.exe ./plus/auto_protocol.lua ./protocol/system_cmd_def.h ${PROTOCOL_OUTPUT}
		DEPENDS ${LOGDEF_OUTPUT}
		WORKING_DIRECTORY "../../gameworld"
	)

	add_custom_command(
		OUTPUT ${INTERFACE_OUTPUT}
		COMMAND ../../../3rd/tolua++/tolua++.exe  -n server -o serverInterface.cc serverInterface.scp
		DEPENDS ${PROTOCOL_OUTPUT}
		WORKING_DIRECTORY "../../gameworld/script/tolua++"
	)
endif(MSVC)

# 生成可执行文件
add_executable(gameworld ${GameWorld_CODELIST})
add_dependencies(gameworld common)
target_link_libraries(gameworld ${GAME_LIBRARIES})