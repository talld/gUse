#ifndef DARRAY_H
#define DARRAY_H

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct dArray_t dArray_t;

struct dArray_t
{
	size_t elementSize;
	size_t elementCount;
	void*  elementData;
};

dArray_t dArrayCreate(size_t elementSize, size_t initialSize);

void dArrayPushElementBack(dArray_t* array, void* pElement);

void dArrayPopElementBack(dArray_t* array);

void* dArrayElementGet(dArray_t* array, size_t index);

void dArrayElementPut(dArray_t* array, size_t index, void* pElement);

#endif // DARRAY_H
