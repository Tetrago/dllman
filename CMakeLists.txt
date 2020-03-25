cmake_minimum_required(VERSION 3.8)
project(dllman)

set(dllman_SOURCES)
set(dllman_DEFINITIONS)

option(INCLUDE_NATIVE "Native support." ON)
option(INCLUDE_CORECLR "CoreClr C# support." ON)

if(INCLUDE_CORECLR)
	list(APPEND dllman_SOURCES "src/coreclr.cpp")
	list(APPEND dllman_DEFINITIONS "DLLMAN_INCLUDE_CS_DNC_CORECLR")

	set(INCLUDE_NATIVE ON)
endif()

if(INCLUDE_NATIVE)
	list(APPEND dllman_SOURCES "src/native.cpp")
	list(APPEND dllman_DEFINITIONS "DLLMAN_INCLUDE_NATIVE")
endif()

add_library(dllman STATIC ${dllman_SOURCES})

set_target_properties(dllman PROPERTIES
	CXX_STANDARD 17
	)

target_include_directories(dllman PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_definitions(dllman PUBLIC ${dllman_DEFINITIONS})