cmake_minimum_required(VERSION 3.20)
project(gLog)

set(CMAKE_CXX_STANDARD 20)

include_directories(inc)

# check if there are actually any srcs set
IF( "${GLOG_SRC}" STREQUAL "" )

ELSE()
    add_library(gLog-static STATIC ${GLOG_SRC})
ENDIF()
