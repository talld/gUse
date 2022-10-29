#include <dArray.h>





dArray_t
dArrayCreate(size_t elementSize, size_t initialSize)
{
	dArray_t ret = {.elementSize  = elementSize,
					.elementCount = initialSize,
					.elementData  = NULL};

	if(initialSize)
	{
		ret.elementData = malloc(elementSize * initialSize);
	}

	return ret;
}





void
dArrayPushElementBack(dArray_t* array, void* pElement)
{
	size_t backOffset = array->elementSize * array->elementCount;

	array->elementCount++;
	size_t newDataSize = array->elementSize * array->elementCount;
	array->elementData = realloc(array->elementData, newDataSize);

	memmove(array->elementData + backOffset, pElement, array->elementSize);
}





void
dArrayPopElementBack(dArray_t* array)
{
	array->elementCount--;
	size_t newDataSize = array->elementSize * array->elementCount;
	array->elementData = realloc(array->elementData, newDataSize);
}





void*
dArrayElementGet(dArray_t* array, size_t index)
{
	size_t offset = array->elementSize * index;
	return &array->elementData[offset];
}






void dArrayElementPut(dArray_t* array, size_t index, void* pElement)
{
	size_t offset = array->elementSize * index;
	memmove(array->elementData + offset, pElement, array->elementSize);
}