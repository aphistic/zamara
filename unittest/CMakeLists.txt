cmake_minimum_required (VERSION 2.8)
find_package(GTest REQUIRED)

set (PROJECT_TEST_NAME "ZAMARA_test")
project(${PROJECT_TEST_NAME})

include_directories (
	${GTEST_INCLUDE_DIRS}
	${ZAMARA_INCLUDE_DIRS}
	)

link_directories(
	${ZAMARA_LIBRARY_DIRS}
	)

file (GLOB CPP_SRC
	"tests/*.cpp"
	)

set (TEST_BINARY ${PROJECT_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TEST_BINARY})

add_executable(${PROJECT_TEST_NAME} test.cpp ${CPP_SRC})
target_link_libraries(${PROJECT_TEST_NAME} gtest zamara)

add_test(${PROJECT_TEST_NAME} ${TEST_BINARY}/${PROJECT_TEST_NAME})
