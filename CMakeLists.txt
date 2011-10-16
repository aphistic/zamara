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

configure_file (
	${ZAMARA_SOURCE_DIR}/include/config_test.h.in
	${ZAMARA_SOURCE_DIR}/include/config_test.h
	)

set (ZAMARA_INCLUDE_DIRS ${ZAMARA_SOURCE_DIR}/include)
set (ZAMARA_LIBRARY_DIRS ${ZAMARA_SOURCE_DIR}/lib)

enable_testing()

add_subdirectory(src)
add_subdirectory(unittest)
