message("Running CMAKE Module: ThirdParty")

# Boost dependencies
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_STATIC_RUNTIME     OFF)
if(NOT BOOST_ROOT)
  set(BOOST_ROOT "${CMAKE_SOURCE_DIR}")
endif()
find_package(Boost 1.61.0 REQUIRED thread chrono)

if (Boost_FOUND)
  include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
endif()

# MySQL
if(UNIX)
  include_directories(/usr/local/include)
  link_directories(/usr/local/lib)
endif()
