set(GLOG_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(GLOG_INCLUDE_DIR
        ${GLOG_ROOT}/Inc
        )

set(GLOG_SRC
        Inc/gLog.h
        Src/glog.c
        )

add_library(GLOG STATIC)

target_sources(GLOG
        PUBLIC
        ${GLOG_SRC}
        )

target_include_directories(GLOG
        PUBLIC
        ${GLOG_INCLUDE_DIR}
        )



include_directories(${GSTR_INCLUDE_DIR})