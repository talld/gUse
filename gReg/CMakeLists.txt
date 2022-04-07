cmake_minimum_required(VERSION 3.19)
project(gReg)

set(CMAKE_CXX_STANDARD 14)

set(GREG_SRC
        Src/FileReader.cpp
        Src/gReg.cpp
        Src/Processor.cpp
        main.cpp)

include_directories(
        Src
)

add_executable(gReg ${GREG_SRC})
