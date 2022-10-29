set(GALG_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(GALG_INCLUDE_DIR
        ${GALG_ROOT}/Inc
        )

set(GALG_SRC
        ${GALG_ROOT}/Src/dArray.c
        ${GALG_ROOT}/Inc/gAlg.h
        )

add_library(GALG STATIC)

target_sources(GALG
        PUBLIC
        ${GALG_SRC}
        )

target_include_directories(GALG
        PUBLIC
        ${GALG_INCLUDE_DIR}
        )

target_link_libraries(GALG GLOG)

include_directories(${GALG_INCLUDE_DIR})