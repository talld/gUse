#ifndef GSTR_GSTRING_H
#define GSTR_GSTRING_H

#include <gStr.h>

typedef struct GHeader
{
	uint64_t version;
	uint64_t id;
	uint64_t gStringCount;
	char* gStringOffsetArray[];
} GHeader_t;


typedef struct GString
{
	size_t g; // girth
	char str[0];
} GString_t;

#endif // GSTR_GSTRING_H
