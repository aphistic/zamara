cmake_minimum_required (VERSION 2.8)
project (ZAMARA)

set (PROJECT_NAME	Zamara)
set (VERSION_MAJOR 	0)
set (VERSION_MINOR 	0)
set (VERSION_REV 	1)
set (VERSION		${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV})

configure_file (
	${ZAMARA_SOURCE_DIR}/include/config.h.in
	${ZAMARA_SOURCE_DIR}/include/config.h
	)

add_subdirectory(${ZAMARA_SOURCE_DIR}/src)

