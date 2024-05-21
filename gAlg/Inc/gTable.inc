#ifndef GTABLE_INC_H
#define GTABLE_INC_H

#include <gAlg.h>
#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
#define GTABLE_TYPE_INC(type, name)                                            \
typedef struct GTable##name##_t GTable##name##_t;                              \
                                                                               \
GTable##name##_t* GTable##name##_Create(size_t initalSize);                    \
void GTable##name##_Insert(GTable##name##_t* table, size_t hash, type value);  \
void GTable##name##_Remove(GTable##name##_t* table, size_t hash);              \
int GTable##name##_Contains(GTable##name##_t* table, size_t hash);             \
type GTable##name##_Get(GTable##name##_t* table, size_t hash);                 \
////////////////////////////////////////////////////////////////////////////////
#define GTABLE_TYPE_SRC(type, name)                                            \
typedef struct GTableNode##name##_t GTableNode##name##_t;                      \
struct GTableNode##name##_t                                                    \
{                                                                              \
	size_t hash;                                                               \
	type value;                                                                \
	GTableNode##name##_t* next;                                                \
};                                                                             \
                                                                               \
typedef struct GTable##name##_t GTable##name##_t;                              \
struct GTable##name##_t                                                        \
{                                                                              \
	size_t bucketsCount;                                                       \
	GTableNode##name##_t** buckets;                                            \
};                                                                             \
                                                                               \
GTable##name##_t* GTable##name##_Create(size_t initalSize)                     \
{                                                                              \
	GTable##name##_t* ret = gAlg_malloc(sizeof(GTable##name##_t));             \
	ret->bucketsCount = initalSize;                                            \
                                                                               \
	if(initalSize > 0)                                                         \
	{                                                                          \
		ret->buckets = gAlg_calloc(ret->bucketsCount,sizeof(*ret->buckets));   \
	}                                                                          \
	else                                                                       \
	{                                                                          \
		ret->buckets = NULL;                                                   \
	}                                                                          \
                                                                               \
	return ret;                                                                \
}                                                                              \
                                                                               \
void GTable##name##_Insert(GTable##name##_t* table, size_t hash, type value)   \
{                                                                              \
	size_t index = hash % table->bucketsCount;                                 \
                                                                               \
	GTableNode##name##_t* toPlace = table->buckets[index];                     \
	if(toPlace == NULL)                                                        \
	{                                                                          \
		table->buckets[index] = gAlg_malloc(sizeof(**table->buckets));         \
		toPlace = table->buckets[index];                                       \
	}                                                                          \
	else                                                                       \
	{                                                                          \
		toPlace = table->buckets[index];                                       \
		while(toPlace->next != NULL)                                           \
		{                                                                      \
			toPlace = toPlace->next;                                           \
		}                                                                      \
                                                                               \
		toPlace->next = gAlg_malloc(sizeof(**table->buckets));                 \
		toPlace = toPlace->next;                                               \
	}                                                                          \
                                                                               \
	toPlace->hash = hash;                                                      \
	toPlace->value = value;                                                    \
	toPlace->next = NULL;                                                      \
}                                                                              \
                                                                               \
void GTable##name##_Remove(GTable##name##_t* table, size_t hash)               \
{                                                                              \
	size_t index = hash % table->bucketsCount;                                 \
	GTableNode##name##_t* toRemove = table->buckets[index];                    \
	if(toRemove && toRemove->hash != hash)                                     \
	{                                                                          \
		while(toRemove->next && toRemove->next->hash != hash)                  \
		{                                                                      \
			toRemove = toRemove->next;                                         \
		}                                                                      \
                                                                               \
		if(toRemove->next)                                                     \
		{                                                                      \
			GTableNode##name##_t* toFree = toRemove->next;                     \
			toRemove->next = toRemove->next->next;                             \
			gAlg_free(toFree);                                                 \
        }                                                                      \
	}                                                                          \
	else if(toRemove)                                                          \
	{                                                                          \
		table->buckets[index] = toRemove->next;                                \
		gAlg_free(toRemove);                                                   \
	}                                                                          \
}                                                                              \
                                                                               \
int GTable##name##_Contains(GTable##name##_t* table, size_t hash)              \
{                                                                              \
	int isFound = 0;                                                           \
	size_t index = hash % table->bucketsCount;                                 \
                                                                               \
	GTableNode##name##_t* runner = table->buckets[index];                      \
	if(runner && runner->hash != hash)                                         \
	{                                                                          \
		while(runner->next != NULL)                                            \
		{                                                                      \
			runner = runner->next;                                             \
			if(runner->hash == hash) {break;}                                  \
		}                                                                      \
	}                                                                          \
                                                                               \
	isFound = (runner != NULL &&runner->hash == hash);                         \
	return isFound;                                                            \
}                                                                              \
                                                                               \
type GTable##name##_Get(GTable##name##_t* table, size_t hash)                  \
{                                                                              \
	int isFound = 0;                                                           \
	size_t index = hash % table->bucketsCount;                                 \
                                                                               \
	GTableNode##name##_t* runner = table->buckets[index];                      \
	if(runner && runner->hash != hash)                                         \
	{                                                                          \
		while(runner->next != NULL)                                            \
		{                                                                      \
			runner = runner->next;                                             \
			if(runner->hash == hash) {break;}                                  \
		}                                                                      \
	}                                                                          \
                                                                               \
	isFound = (runner && runner->hash == hash);                                \
	if(isFound)                                                                \
	{                                                                          \
		return runner->value;                                                  \
	}                                                                          \
	else                                                                       \
	{                                                                          \
		return (type){0};                                                      \
	}                                                                          \
}                                                                              \
////////////////////////////////////////////////////////////////////////////////
#endif