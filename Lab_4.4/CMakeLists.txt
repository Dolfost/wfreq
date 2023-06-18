cmake_minimum_required(VERSION 3.5)

project(res_tmp LANGUAGES CXX)
get_filename_component(name_of_project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${name_of_project})
project("${name_of_project}_")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


macro(print_all_variables)
	message(STATUS "-------------------Variables-----------------------")
	get_cmake_property(_variableNames VARIABLES)
	foreach (_variableName ${_variableNames})
		message(STATUS "${_variableName}=${${_variableName}}")
	endforeach()
	message(STATUS "\------------------Variables-----------------------")
endmacro()

#
# Removes the specified compile flag from the specified target.
#   _target     - The target to remove the compile flag from
#   _flag       - The compile flag to remove
#
# Pre: apply_global_cxx_flags_to_all_targets() must be invoked.
#
macro(remove_flag_from_target _target _flag)
	get_target_property(_target_cxx_flags ${_target} COMPILE_OPTIONS)
	if(_target_cxx_flags)
		list(REMOVE_ITEM _target_cxx_flags ${_flag})
		set_target_properties(${_target} PROPERTIES COMPILE_OPTIONS "${_target_cxx_flags}")
	endif()
endmacro()


message(STATUS "OS is [${CMAKE_HOST_SYSTEM_NAME}] [${CMAKE_HOST_SYSTEM_VERSION}]")
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
	add_definitions("-D__WIN_DIR_SLASH__")
	add_compile_options("-D__WIN_DIR_SLASH__")
	set(CMAKE_GENERATOR "MinGW Makefiles")
	# SET(CMAKE_CXX_COMPILER_LAUNCHER "ccache.exe")
else()
	set(CMAKE_GENERATOR "Unix Makefiles")
	SET(CMAKE_CXX_COMPILER_LAUNCHER "ccache")
	# SET(CMAKE_C_COMPILER	"/usr/bin/gcc")
	# SET(CMAKE_CXX_COMPILER	"/usr/bin/g++")
endif()

include_directories(${root_SOURCE_DIR}. .)


add_compile_options(
#  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
#  "$<$<CONFIG:DEBUG>:-O0;-ggdb;>" #-H
  "$<$<CONFIG:Debug>:-O0;-ggdb;>" #-H
  "$<$<CONFIG:RELEASE>:-O2;-g>"
)
# -H - get all include hierarchy - debug - anly
#${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES}

find_package(Threads)
set(THREADS_PREFER_PTHREAD_FLAG ON)
add_compile_options("-fpermissive")
# LIST OF FILES:
file(
	GLOB src_st_projects
	 "*.cpp"
	 "*.c"
)

set(CMAKE_VERBOSE_MAKEFILE 1)

add_executable(${name_of_project} ${src_st_projects})
STRING(REGEX REPLACE "\-g" "" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG}) #removing unnoing -g flag

# print_all_variables()
# target_link_libraries (${name_of_project} ${CMAKE_THREAD_LIBS_INIT} -pthread -lstdc++  -lm)
