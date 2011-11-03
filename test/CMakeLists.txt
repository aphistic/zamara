cmake_minimum_required (VERSION 2.8)

include (TestBigEndian)

find_package (GTest REQUIRED)
find_package (Threads)

set (PROJECT_TEST_NAME "ZAMARA_test")
project (${PROJECT_TEST_NAME})

include_directories (
	${GTEST_INCLUDE_DIRS}
	${ZAMARA_INCLUDE_DIRS}
	)

link_directories(
	${ZAMARA_LIBRARY_DIRS}
	)

file (GLOB CPP_SRC
	"tests/*.cc"
	)

set (TEST_BINARY ${PROJECT_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TEST_BINARY})
test_big_endian (IS_BIG_ENDIAN)

configure_file (
	${PROJECT_SOURCE_DIR}/../include/config_test.h.in
	${PROJECT_SOURCE_DIR}/../include/config_test.h
	)


add_executable (${PROJECT_TEST_NAME} ${CPP_SRC})
target_link_libraries (${PROJECT_TEST_NAME} 
				gtest
				gtest_main
				${CMAKE_THREAD_LIBS_INIT}
				zamara
				)

add_test (${PROJECT_TEST_NAME} ${TEST_BINARY}/${PROJECT_TEST_NAME})
