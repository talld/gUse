#include "GString.h"

#include <cstring>

uint64_t loadGDict(void* rawDict, GDictionary_t** dict)
{
	uint64_t err = GLOG_SUCCESS;

	*dict = (GDictionary_t*) rawDict;
	GDictionary_t*& header = *dict;

	for(size_t i = 0; i < header->gStringCount; i++)
	{
		uintptr_t nativeAddr = (uintptr_t)(header->strings[i]) + (uintptr_t)header;
		header->strings[i] = (GString_t *) nativeAddr;
	}

	return err;
}

uint64_t saveToGDict(std::vector<char*> strings, GDictionary_t** out )
{
	uint64_t err = GLOG_SUCCESS;

	GDictionary_t*& header = *out;
	size_t stringCount = strings.size();

	size_t gStringTableSize = 0;
	std::vector<size_t> stringLengths;

	for( char* s : strings )
	{
		size_t len = strlen(s);
		stringLengths.push_back(len);

		gStringTableSize += sizeof(GString_t) + len;
	}

	GLOG_INFO("string table size: %zu", gStringTableSize);

	size_t headerSize = sizeof(GDictionary_t) + (sizeof(GString_t*) * stringCount);
	GLOG_INFO("header size: %zu", headerSize);

	size_t totalSize = headerSize + gStringTableSize;
	header = (GDictionary_t *) malloc(totalSize);
	auto* gString = (GString_t*) ((char*)header + headerSize);

	header->headerSize   = headerSize;
	header->totalSize    = totalSize;
	header->gStringCount = stringCount;

	for( size_t i = 0; i < strings.size(); i++ )
	{
		gString->g = stringLengths[i];
		strncpy(gString->str, strings[i], gString->g );

		ptrdiff_t offset = (char*)gString - (char*)header;
		header->strings[i] = (GString_t *)offset;
		GLOG_INFO("String created: %p %p %zu, %s",
				  header->strings[i],
				  gString,
				  gString->g,
				  gString->str);

		gString = (GString_t*) ( gString->str + gString->g );
	}

	return err;
}

