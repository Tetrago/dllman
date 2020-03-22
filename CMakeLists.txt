cmake_minimum_required(VERSION 3.8)
project(dllman)

set(dllman_SOURCES "src/dllman.c")
set(dllman_DEFINITIONS)

option(NATIVE "Native support." ON)
if(NATIVE)
	list(APPEND dllman_SOURCES
		"src/native.c"
		)
	list(APPEND dllman_DEFINITIONS "DLLMAN_INCLUDE_NATIVE")
endif()


add_library(dllman STATIC ${dllman_SOURCES})

target_include_directories(dllman PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_definitions(dllman PUBLIC ${dllman_DEFINITIONS})