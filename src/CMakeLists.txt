project (ZAMARA)
cmake_minimum_required (VERSION 2.8)

file (GLOB CPP_SRC
	"mpq/*.cpp"
	"sc2/*.cpp"
	"*.cpp"
	)

include_directories (
	../include
	)

add_library(zamara SHARED ${CPP_SRC})
