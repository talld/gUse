set(GSTR_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(GSTR_INCLUDE_DIR
        ${GSTR_ROOT}/Inc
        )

set(GSTR_SRC
        Src/GString.c
        )

add_library(GSTR STATIC)

target_sources(GSTR
        PRIVATE
        ${GSTR_SRC}
        )

target_include_directories(GSTR
        PUBLIC
        ${GSTR_INCLUDE_DIR}
        )

target_link_libraries(GSTR GLOG)

include_directories(${GSTR_INCLUDE_DIR})