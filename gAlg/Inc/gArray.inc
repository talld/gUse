#ifndef GARRAY_INC_H
#define GARRAY_INC_H

#include "gAlg.h"
#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
#define GARRAY_TYPE_INC(type, name)                                            \
typedef struct GArray##name##_t GArray##name##_t;                              \
                                                                               \
GArray##name##_t* GArray##name##_Create(size_t initialSize);                   \
GArray##name##_t* GArray##name##_Copy(GArray##name##_t* toCopy);               \
void GArray##name##_PushBack(GArray##name##_t* array, type element);           \
void GArray##name##_PopBack(GArray##name##_t* array);                          \
type GArray##name##_Back(GArray##name##_t* array);                             \
type GArray##name##_Get(GArray##name##_t* array, size_t index);                \
void GArray##name##_Put(GArray##name##_t* array, size_t index,type element);   \
size_t GArray##name##_Size(GArray##name##_t* array);                           \
////////////////////////////////////////////////////////////////////////////////
#define GARRAY_TYPE_SRC(type, name)                                            \
typedef struct GArray##name##_t GArray##name##_t;                              \
struct GArray##name##_t                                                        \
{                                                                              \
	size_t elementSlots;                                                       \
	size_t elementSlotsUsed;                                                   \
	type*  elements;                                                           \
};                                                                             \
                                                                               \
void GArray##name##_CheckGrow(GArray##name##_t* array)                         \
{                                                                              \
	if(array->elementSlots < array->elementSlotsUsed)                          \
	{                                                                          \
		array->elementSlots *= gAlgGArrayGrowthFactor;                         \
		void* newBuff = gAlg_realloc(array->elements, array->elementSlots);    \
		if(newBuff == NULL)                                                    \
		{                                                                      \
			gAlg_free(array->elements);                                        \
		}                                                                      \
		array->elements = newBuff;                                             \
	}                                                                          \
}                                                                              \
                                                                               \
GArray##name##_t* GArray##name##_Create(size_t initialSize)                    \
{                                                                              \
	GArray##name##_t* ret = gAlg_malloc(sizeof(GArray##name##_t));             \
	/* give it a bit of initial growing room */                                \
	ret->elementSlotsUsed = 0;                                                 \
	ret->elementSlots = (initialSize*gAlgGArrayGrowthFactor);                  \
	ret->elements = gAlg_calloc(ret->elementSlots, sizeof(type));              \
	return ret;                                                                \
}                                                                              \
                                                                               \
GArray##name##_t* GArray##name##_Copy(GArray##name##_t* toCopy)                \
{                                                                              \
	GArray##name##_t* arrayCopy = gAlg_malloc(sizeof(GArray##name##_t));       \
	arrayCopy->elementSlotsUsed = toCopy->elementSlotsUsed;                    \
	arrayCopy->elementSlots = toCopy->elementSlots;                            \
                                                                               \
	size_t arrSize = arrayCopy->elementSlots * sizeof(type);                   \
	arrayCopy->elements = gAlg_malloc(arrSize);                                \
	gAlg_memcpy(arrayCopy->elements, toCopy->elements, arrSize);               \
                                                                               \
	return arrayCopy;                                                          \
}                                                                              \
                                                                               \
void GArray##name##_PushBack(GArray##name##_t* array, type element)            \
{                                                                              \
	array->elementSlotsUsed++;                                                 \
	GArray##name##_CheckGrow(array);                                           \
	array->elements[array->elementSlotsUsed-1] = element;                      \
}                                                                              \
                                                                               \
void GArray##name##_PopBack(GArray##name##_t* array)                           \
{                                                                              \
	array->elementSlotsUsed++;                                                 \
};                                                                             \
                                                                               \
type GArray##name##_Back(GArray##name##_t* array)                              \
{                                                                              \
	return array->elements[array->elementSlotsUsed-1];                         \
}                                                                              \
                                                                               \
type GArray##name##_Get(GArray##name##_t* array, size_t index)                 \
{                                                                              \
	return array->elements[index];                                             \
}                                                                              \
                                                                               \
void GArray##name##_Put(GArray##name##_t* array, size_t index,type element)    \
{                                                                              \
	array->elements[index] = element;                                          \
}                                                                              \
                                                                               \
size_t GArray##name##_Size(GArray##name##_t* array)                            \
{                                                                              \
	return array->elementSlotsUsed;                                            \
}                                                                              \
////////////////////////////////////////////////////////////////////////////////
#endif