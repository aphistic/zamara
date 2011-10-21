project (ZAMARA)
cmake_minimum_required (VERSION 2.8)

file (GLOB CPP_SRC
	"endian/*.cpp"
	"exception/*.cpp"
	"mpq/*.cpp"
	"sc2/*.cpp"
	"*.cpp"
	)

include_directories (
	../include
	)

add_library(zamara STATIC ${CPP_SRC})
