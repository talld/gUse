#include "GString.h"

uint64_t loadGDict(void* gDict, char*** dict)
{
	GHeader_t* gHeader = gDict;

	if(!strncmp(gHeader->ident, "GHDR", 4))
	{
		GLOG_INFO("HEADER HAS INCORRECT IDENT");
		goto FAIL;
	}

	gHeader->headerSize = sizeof(GHeader_t)
		+ gHeader->gStringCount * sizeof(char*);

	for(size_t i = 0; i < gHeader->gStringCount; i++)
	{
		uintptr_t offset = gHeader->gStringOffsetArray[i];
		offset += (uintptr_t)gHeader + (uintptr_t)gHeader->headerSize;
		gHeader->gStringOffsetArray[i] = (char*) offset;
	}

	*dict = gHeader->gStringOffsetArray;

	return GLOG_SUCCESS;
FAIL:
	return GLOG_FAIL;
}

