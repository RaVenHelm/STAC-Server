message("Running CMAKE Module: ThirdParty")

# Boost dependencies
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_STATIC_RUNTIME     OFF)
if(NOT BOOST_ROOT)
  set(BOOST_ROOT "${CMAKE_SOURCE_DIR}")
endif()
find_package(Boost 1.61.0 REQUIRED chrono date_time filesystem system)

if (Boost_FOUND)
  include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
endif()

# MySQL
if(UNIX)
  include_directories(/usr/local/include)
  link_directories(/usr/local/lib)
  set(STAC_MYSQL_LIBS libmysqlcppconn.so)
else()
  include_directories("C:\\Program Files (x86)\\MySQL\\MySQL Connector C 6.1\\include")
  include_directories("C:\\Program Files (x86)\\MySQL\\MySQL Connector C++ 1.1.7\\include")
  link_directories("C:\\Program Files (x86)\\MySQL\\MySQL Connector C 6.1\\lib")
  link_directories("C:\\Program Files (x86)\\MySQL\\MySQL Connector C++ 1.1.7\\lib\\opt")
  set(STAC_MYSQL_LIBS libmysql.lib mysqlcppconn.lib)
endif()

# libmysql.lib
# mysqlcppconn.lib
