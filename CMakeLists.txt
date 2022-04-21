cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
project(gUse)

set(G_USE_INCLUDE_DIR "")

set(G_LOG_INCLUDE_DIR "")
add_subdirectory(gLog)
set(G_USE_INCLUDE_DIR ${G_USE_INCLUDE_DIR} ${G_LOG_INCLUDE_DIR})


set(G_USE_INCLUDE_DIR ${G_USE_INCLUDE_DIR} PARENT_SCOPE)
