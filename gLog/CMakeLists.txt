cmake_minimum_required(VERSION 3.20)
project(gLog)

set(CMAKE_CXX_STANDARD 20)

set(G_LOG_INCLUDE_DIR
        ${CMAKE_CURRENT_LIST_DIR}/Inc)

include_directories(${G_LOG_INCLUDE_DIR})

# check if there are actually any srcs set
IF( "${GLOG_SRC}" STREQUAL "" )

ELSE()
    add_library(GLOG-static STATIC ${GLOG_SRC})
ENDIF()

set(G_LOG_INCLUDE_DIR ${G_LOG_INCLUDE_DIR} PARENT_SCOPE)