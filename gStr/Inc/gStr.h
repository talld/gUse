#ifndef GSTR_H
#define GSTR_H

#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <vector>

#include <gLog.h>

struct GString
{
	size_t g; // girth
	char str[0];
};
typedef struct GString GString_t;

struct GDictionary
{
	size_t   headerSize;
	size_t   totalSize;
	uint64_t gStringCount;
	GString_t* strings[0];
};
typedef struct GDictionary GDictionary_t;

uint64_t loadGDict(void* rawDict, GDictionary_t** dict );

uint64_t saveToGDict(std::vector<char*> strings, GDictionary_t** out );

#endif  // GSTR_H
