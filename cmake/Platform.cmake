message("Running CMake Platform Module")
enable_language(CXX)
include(CheckCXXSourceRuns)

if(APPLE OR UNIX)
	set(STAC_PLATFORM_POSIX TRUE CACHE BOOL "Posix Platform")
	if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		set(STAC_PLATFORM_LINUX TRUE CACHE BOOL "Linux Platform")
	endif()
elseif(WIN32)
	set(STAC_PLATFORM_WINDOWS TRUE CACHE BOOL "Windows Platform")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	# TODO: Separate Debug/Release Flags
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wconversion -Wcast-align -Wformat=2 -fno-common -Wstrict-overflow -Wtrampolines -Woverloaded-virtual -Wreorder -Wsign-promo -ggdb")
	set(STAC_GCC_LIBS dl pthread)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	# Visual Studio settings
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

message("STAC_GCC_LIBS ${STAC_GCC_LIBS}")
message("CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}")
