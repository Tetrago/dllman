cmake_minimum_required(VERSION 3.8)
project(dllman)

set(dllman_SOURCES)

option(NATIVE "Native support." ON)
if(NATIVE)
	list(APPEND dllman_SOURCES
		"src/native.cpp"
		)
endif()


add_library(dllman STATIC ${dllman_SOURCES})

target_include_directories(dllman PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
