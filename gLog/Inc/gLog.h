#ifndef GLOG_H
#define GLOG_H

#include <stdio.h>


///////////////////////////////////////////////////////////////////////////////
/// Handy return codes                                                      ///
///////////////////////////////////////////////////////////////////////////////


#define GLOG_SUCCESS 0
#define GLOG_FAIL    1


///////////////////////////////////////////////////////////////////////////////
/// Debug traps                                                             ///
///////////////////////////////////////////////////////////////////////////////


#if __clang__
	#define GLOG_DEBUG_BREAK __builtin_debugtrap
#elif __GNUC__
	#define GLOG_DEBUG_BREAK __builtin_trap
#endif


///////////////////////////////////////////////////////////////////////////////
/// Logging                                                                 ///
///////////////////////////////////////////////////////////////////////////////


#if GLOG_LOGGING_ENABLED

#if GLOG_DEBUG
	#define GLOG_DEBUG(...)  fprintf(stderr, "%s::%u ",__FILE__, __LINE__); \
	fprintf(stderr, __VA_ARGS__); \
	fprintf(stderr,"\n"); \
	fflush(stderr)
#else
	#define GLOG_DEBUG(...)
#endif

	#define GLOG_ERR(...)  fprintf(stderr, "%s::%u ",__FILE__, __LINE__); \
	fprintf(stderr, __VA_ARGS__); \
	fprintf(stderr,"\n"); \
	fflush(stderr)

	#define GLOG_INFO(...) fprintf(stdout, "%s::%u ",__FILE__, __LINE__); \
	fprintf(stdout, __VA_ARGS__); \
	fprintf(stdout,"\n"); \
	fflush(stdout)

#else  // GLOG_LOGGING_ENABLED
	#define GLOG_ERR(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)
	#define GLOG_INFO(...)
#endif // GLOG_LOGGING_ENABLED


///////////////////////////////////////////////////////////////////////////////
/// Assertions                                                              ///
///////////////////////////////////////////////////////////////////////////////


// an assert will just log an error but not kill
#define GLOG_ASSERT(con, msg) \
do \
	if ( !(con) ) \
	{ \
		GLOG_ERR(msg); \
	} \
while(0)

// the do while is so a semi-colon can be added at the end when in use

// whereas require will kill the app if the conditions aren't met

#define GLOG_REQUIRE(con, msg) \
do  \
	if ( !(con) ) \
	{ \
		GLOG_ERR(msg); \
		GLOG_DEBUG_BREAK(); \
	} \
while(0)


#endif  // GLOG_H
