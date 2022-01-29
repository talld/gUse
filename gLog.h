#ifndef GLOG_H
#define GLOG_H

#include <cstdio>

// compiler specific built in's
#ifdef __GNUC__
	#define GLOG_DEBUG_BREAK __builtin_trap
#endif // __GNUC__

#ifdef __clang__
	#define GLOG_DEBUG_BREAK __builtin_debugtrap
#endif // __clang__

// logging
#ifdef GLOG_LOGGING_ENABLED
#define GLOG_ERR(...)  fprintf(stderr, " %s::%lu ",__FILE__, __LINE__);  fprintf(stderr, __VA_ARGS__)
#define GLOG_INFO(...) fprintf(stderr, " %s::%lu ",__FILE__, __LINE__);  fprintf(stdout, __VA_ARGS__)
#endif

// an assert will just log an error but not kill
#define GLOG_ASSERT(con, msg)         \
do                                    \
	if ( !(con) )                 \
	{                             \
		GLOG_ERR(msg)         \
	}                             \
while(0)
// the do while is so a semi-colon can be added at the end when in use

// whereas require will kill the app if the conditions aren't met
#define GLOG_REQUIRE(con, msg) \
do                                    \
	if ( !(con) )                 \
	{                             \
		GLOG_ERR(msg);        \
                GLOG_DEBUG_BREAK();   \
	}                             \
while(0)


#endif  // GLOG_H
