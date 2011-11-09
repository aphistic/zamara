project (ZAMARA)
cmake_minimum_required (VERSION 2.8)

file (GLOB CPP_SRC
	"endian/*.cc"
	"exception/*.cc"
	"mpq/*.cc"
	"sc2/*.cc"
	"*.cc"
	)

include_directories (
	../include
	)

find_package (ZLIB REQUIRED)
find_package (BZip2 REQUIRED)

if (STATIC)
	add_library(zamara STATIC ${CPP_SRC})
else ()
	add_library(zamara SHARED ${CPP_SRC})
endif (STATIC)
