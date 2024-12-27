#ifndef GLOG_H
#define GLOG_H

#include <stdio.h>
#include <stdint.h>


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
/// attr macro                                                              ///
///////////////////////////////////////////////////////////////////////////////

#define GLOG_UNUSED __attribute__((unused))

///////////////////////////////////////////////////////////////////////////////
/// Logging                                                                 ///
///////////////////////////////////////////////////////////////////////////////

int Glog_Init();

#define GLOG_ERR(...)  fprintf(stderr, "%s::%u ",__FILE__, __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr,"\n");

int Glog_Info(uint8_t channel, size_t threadID, const char* reporter, const char* file, size_t line, const char* format, ...);

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define GLOG_INFO(channel, threadID, reporter, ...)                                                   \
	do                                                                                            \
	{                                                                                             \
		if(channel)                                                                           \
		{                                                                                     \
			Glog_Info(channel, threadID, reporter, __FILE__, __LINE__, __VA_ARGS__, NULL); \
		}                                                                                     \
	}                                                                                             \
	while(0)                                                                                      \
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Assertions                                                              ///
///////////////////////////////////////////////////////////////////////////////


/* an assert will just log an error but not kill */
#define GLOG_ASSERT(con, msg) \
do \
	if ( !(con) ) \
	{ \
		GLOG_ERR(msg); \
	} \
while(0)

/* whereas require will kill the app if the conditions aren't met */

#define GLOG_REQUIRE(con, ...) \
do  \
	if ( !(con) ) \
	{ \
		GLOG_ERR(__VA_ARGS__); \
		GLOG_DEBUG_BREAK(); \
	} \
while(0)


#endif  // GLOG_H
