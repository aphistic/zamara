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

file (GLOB CPP_SRC
	"tests/*.cpp"
	)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/unittest/bin)

add_executable(${PROJECT_TEST_NAME} test.cpp ${CPP_SRC})
target_link_libraries(${PROJECT_TEST_NAME} gtest zamara)

add_test(${PROJECT_TEST_NAME} ${PROJECT_TEST_NAME})
