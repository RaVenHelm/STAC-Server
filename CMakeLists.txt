cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(stac-server)

include_directories(include)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include("Platform")
include("ThirdParty")

FILE(GLOB SOURCES "src/*")
message(${STAC_MYSQL_LIBS})

add_executable(stac-server ${SOURCES})
target_link_libraries(stac-server
  ${Boost_LIBRARIES}
  ${STAC_GCC_LIBS}
  ${STAC_MYSQL_LIBS}
)
