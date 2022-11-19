cmake_minimum_required (VERSION 2.8.12.2)

#项目名
#project (gate)
#cmake_policy(SET CMP0015 OLD) 

#头文件
include_directories(
	./
)

# 源文件及头文件
file(GLOB_RECURSE Gate_CODELIST "${PROJECT_SOURCE_DIR}/gateway/*.cc" "${PROJECT_SOURCE_DIR}/gateway/*.h")

# 代码分组
group_by_dir(${PROJECT_SOURCE_DIR}/gateway ${Gate_CODELIST})

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

# Gate输出目录
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${Bin_Dir}/gateway)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${Bin_Dir}/gateway)

add_executable(gateway ${Gate_CODELIST})
add_dependencies(gateway common)
target_link_libraries(gateway ${GAME_LIBRARIES})

