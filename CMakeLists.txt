Project(gUse)
cmake_minimum_required(VERSION 3.14)

set(GUSE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(GUSE_SRC "")
set(GUSE_HSP "")
set(GUSE_INC "")


#-----------------------------------------------------------------------------#
# gLog                                                                        #
#-----------------------------------------------------------------------------#
set(GLOG_ROOT ${GUSE_ROOT}/gLog)

set(GLOG_SRC  
	${GLOG_ROOT}/Src/gLog.c
	)

set(GLOG_INC  
	${GLOG_ROOT}/Inc
	)

set(GLOG_HSP  
	${GLOG_INC}
	)

set(GUSE_SRC ${GUSE_SRC} ${GLOG_SRC})
set(GUSE_HSP ${GUSE_HSP} ${GLOG_HSP})
set(GUSE_INC ${GUSE_INC} ${GLOG_INC})
#-----------------------------------------------------------------------------#
# gAlg                                                                        #
#-----------------------------------------------------------------------------#
set(GALG_ROOT ${GUSE_ROOT}/gAlg)

set(GALG_SRC
		${GALG_ROOT}/Src/dArray.c
		)

set(GALG_INC
		${GALG_ROOT}/Inc
		)

set(GALG_HSP
		${GALG_ROOT}
		)

set(GUSE_SRC ${GUSE_SRC} ${GALG_SRC})
set(GUSE_HSP ${GUSE_HSP} ${GALG_HSP})
set(GUSE_INC ${GUSE_INC} ${GALG_INC})
#-----------------------------------------------------------------------------#
# gStr                                                                        #
#-----------------------------------------------------------------------------#
set(GSTR_ROOT ${GUSE_ROOT}/gStr)

set(GSTR_SRC  
	${GSTR_ROOT}/Src/GString.cpp
	)

set(GSTR_INC  
	${GSTR_ROOT}/Inc
	)

set(GSTR_HSP  
	${GSTR_INC}
	)

set(GUSE_SRC ${GUSE_SRC} ${GSTR_SRC})
set(GUSE_HSP ${GUSE_HSP} ${GSTR_HSP})
set(GUSE_INC ${GUSE_INC} ${GSTR_INC})

add_library(gUse ${GUSE_SRC})
Target_include_directories(gUse PUBLIC  ${GUSE_INC})
Target_include_directories(gUse PRIVATE ${GUSE_HSP})

