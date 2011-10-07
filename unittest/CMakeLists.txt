cmake_minimum_required (VERSION 2.8)
find_package(GTest REQUIRED)

set (PROJECT_TEST_NAME "ZAMARA_test")

include_directories (
	${GTEST_INCLUDE_DIRS}
	${ZAMARA_INCLUDE_DIRS}
	)

link_directories(
	${ZAMARA_LIBRARY_DIRS}
	)

add_executable(${PROJECT_TEST_NAME} test.cpp)
target_link_libraries(${PROJECT_TEST_NAME} gtest zamara)

add_test(${PROJECT_TEST_NAME} ${PROJECT_TEST_NAME})
