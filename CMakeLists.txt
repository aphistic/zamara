cmake_minimum_required (VERSION 2.8)
project (ZAMARA)

set (VERSION_MAJOR 	0)
set (VERSION_MINOR 	0)
set (VERSION_REV 	1)
set (VERSION		${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV})

set (BUILD_DIR		${ZAMARA_BINARY_DIR})

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ZAMARA_BINARY_DIR}/lib)

configure_file (
	${ZAMARA_SOURCE_DIR}/include/config.h.in
	${ZAMARA_SOURCE_DIR}/include/config.h
	)

set (ZAMARA_INCLUDE_DIRS ${ZAMARA_SOURCE_DIR}/include)
set (ZAMARA_LIBRARY_DIRS ${ZAMARA_SOURCE_DIR}/lib)

if (DEBUG)
	set (CMAKE_CXX_FLAGS "-g -Wall")
endif (DEBUG)

if (USE_CLANG)
	set (CC	"clang")
	set (CXX "clang++")
	set (CMAKE_C_FLAGS_INIT                "-Wall -std=c99")
	set (CMAKE_C_FLAGS_DEBUG_INIT          "-g")
	set (CMAKE_C_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
	set (CMAKE_C_FLAGS_RELEASE_INIT        "-O4 -DNDEBUG")
	set (CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

	set (CMAKE_CXX_FLAGS_INIT                "-Wall")
	set (CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
	set (CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
	set (CMAKE_CXX_FLAGS_RELEASE_INIT        "-O4 -DNDEBUG")
	set (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")
endif (USE_CLANG)

if (NOT NO_TESTS)
	enable_testing ()
	add_subdirectory (test)
endif (NOT NO_TESTS)

add_subdirectory (src)
