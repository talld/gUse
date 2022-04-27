#ifndef GSTR_GSTRING_H
#define GSTR_GSTRING_H

#include <gStr.h>
#include <string.h>


typedef struct GHeader
{
	char     ident[4];
	uint64_t id;
	size_t   headerSize;
	size_t   totalSize;
	uint64_t gStringCount;
	char* gStringOffsetArray[0];
} GHeader_t;


typedef struct GString
{
	size_t g; // girth
	char str[0];
} GString_t;

uint64_t loadGDict(void* gDict, char*** dict);

#endif // GSTR_GSTRING_H
