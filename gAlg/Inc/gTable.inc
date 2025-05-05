#ifndef GTABLE_INC_H
#define GTABLE_INC_H

#include <gAlg.h>
#include <stdint.h>

/************************************************************************************/
#define GTABLE_TYPE_INC(type, name)                                                  \
typedef struct GTable##name##_t GTable##name##_t;                                    \
                                                                                     \
GTable##name##_t* GTable##name##_Create(size_t initalSize);                          \
int GTable##name##_Destroy(GTable##name##_t* gTable);                                \
void GTable##name##_Insert(GTable##name##_t* table, size_t hash, type value);        \
void GTable##name##_Remove(GTable##name##_t* table, size_t hash);                    \
int GTable##name##_Contains(GTable##name##_t* table, size_t hash);                   \
type GTable##name##_Get(GTable##name##_t* table, size_t hash);                       \
/************************************************************************************/
#define GTABLE_TYPE_SRC(type, name)                                                  \
typedef struct GTableNode##name##_t GTableNode##name##_t;                            \
struct GTableNode##name##_t                                                          \
{                                                                                    \
	size_t hash;                                                                 \
	type value;                                                                  \
	GTableNode##name##_t* next;                                                  \
};                                                                                   \
                                                                                     \
typedef struct GTable##name##_t GTable##name##_t;                                    \
struct GTable##name##_t                                                              \
{                                                                                    \
	size_t bucketsCount;                                                         \
	GTableNode##name##_t** buckets;                                              \
};                                                                                   \
                                                                                     \
int                                                                                  \
GTable##name##_Place(                                                                \
	GTableNode##name##_t** buckets,                                              \
	size_t bucketIndex,                                                          \
	GTableNode##name##_t* toPlace)                                               \
{                                                                                    \
	if(buckets[bucketIndex] == NULL)                                             \
	{                                                                            \
		buckets[bucketIndex] = toPlace;                                      \
	}                                                                            \
	else                                                                         \
	{                                                                            \
		GTableNode##name##_t* runner = buckets[bucketIndex];                 \
		while(runner->next != NULL)                                          \
		{ /* find free position */                                           \
			runner = runner->next;                                       \
		}                                                                    \
		runner->next = toPlace;                                              \
	}                                                                            \
	return 0;                                                                    \
}                                                                                    \
                                                                                     \
GTable##name##_t*                                                                    \
GTable##name##_Create(                                                               \
size_t initalSize)                                                                   \
{                                                                                    \
	GTable##name##_t* ret = gAlg_malloc(sizeof(GTable##name##_t));               \
	ret->bucketsCount = initalSize;                                              \
	if(initalSize > 0)                                                           \
	{                                                                            \
		ret->buckets = gAlg_calloc(ret->bucketsCount,sizeof(*ret->buckets)); \
	}                                                                            \
	else                                                                         \
	{                                                                            \
		ret->buckets = NULL;                                                 \
	}                                                                            \
	return ret;                                                                  \
}                                                                                    \
                                                                                     \
int                                                                                  \
GTable##name##_Destroy(                                                              \
	GTable##name##_t* gTable)                                                    \
{                                                                                    \
	for(size_t i = 0; i < gTable->bucketsCount; i++)                             \
	{                                                                            \
		GTableNode##name##_t* runner = gTable->buckets[i];                   \
		while(runner != NULL)                                                \
		{                                                                    \
			GTableNode##name##_t* next = runner->next;                   \
			gAlg_free(runner);                                           \
			runner = next;                                               \
		}                                                                    \
	}                                                                            \
	gAlg_free(gTable);                                                           \
	return 0;                                                                    \
}                                                                                    \
                                                                                     \
void                                                                                 \
GTable##name##_Insert(                                                               \
	GTable##name##_t* table,                                                     \
	size_t hash,                                                                 \
	type value)                                                                  \
{                                                                                    \
	size_t index = hash % table->bucketsCount;                                   \
	GTableNode##name##_t* toPlace = gAlg_malloc(sizeof(*toPlace));               \
	toPlace->hash = hash;                                                        \
	toPlace->value = value;                                                      \
	toPlace->next = NULL;                                                        \
	GTable##name##_Place(table->buckets, index, toPlace);                        \
}                                                                                    \
                                                                                     \
void                                                                                 \
GTable##name##_Remove(                                                               \
	GTable##name##_t* table,                                                     \
	size_t hash)                                                                 \
{                                                                                    \
	size_t index = hash % table->bucketsCount;                                   \
	GTableNode##name##_t* toRemove = table->buckets[index];                      \
	if(toRemove && toRemove->hash != hash)                                       \
	{                                                                            \
		while(toRemove->next && toRemove->next->hash != hash)                \
		{                                                                    \
			toRemove = toRemove->next;                                   \
		}                                                                    \
                                                                                     \
		if(toRemove->next)                                                   \
		{                                                                    \
			GTableNode##name##_t* toFree = toRemove->next;               \
			toRemove->next = toRemove->next->next;                       \
			gAlg_free(toFree);                                           \
        }                                                                            \
	}                                                                            \
	else if(toRemove)                                                            \
	{                                                                            \
		table->buckets[index] = toRemove->next;                              \
		gAlg_free(toRemove);                                                 \
	}                                                                            \
}                                                                                    \
                                                                                     \
int                                                                                  \
GTable##name##_Contains(                                                             \
	GTable##name##_t* table,                                                     \
	size_t hash)                                                                 \
{                                                                                    \
	int isFound = 0;                                                             \
	size_t index = hash % table->bucketsCount;                                   \
                                                                                     \
	GTableNode##name##_t* runner = table->buckets[index];                        \
	if(runner && runner->hash != hash)                                           \
	{                                                                            \
		while(runner->next != NULL)                                          \
		{                                                                    \
			runner = runner->next;                                       \
			if(runner->hash == hash) {break;}                            \
		}                                                                    \
	}                                                                            \
                                                                                     \
	isFound = (runner != NULL &&runner->hash == hash);                           \
	return isFound;                                                              \
}                                                                                    \
                                                                                     \
type                                                                                 \
GTable##name##_Get(                                                                  \
	GTable##name##_t* table,                                                     \
	size_t hash)                                                                 \
{                                                                                    \
	int isFound = 0;                                                             \
	size_t index = hash % table->bucketsCount;                                   \
                                                                                     \
	GTableNode##name##_t* runner = table->buckets[index];                        \
	if(runner && runner->hash != hash)                                           \
	{                                                                            \
		while(runner->next != NULL)                                          \
		{                                                                    \
			runner = runner->next;                                       \
			if(runner->hash == hash) {break;}                            \
		}                                                                    \
	}                                                                            \
                                                                                     \
	isFound = (runner && runner->hash == hash);                                  \
	if(isFound)                                                                  \
	{                                                                            \
		return runner->value;                                                \
	}                                                                            \
	else                                                                         \
	{                                                                            \
		return (type){0};                                                    \
	}                                                                            \
}                                                                                    \
                                                                                     \
int                                                                                  \
GTable##name##_Balance(                                                              \
	GTable##name##_t* table)                                                     \
{                                                                                    \
	size_t nodeCount = 0;                                                        \
	for (size_t i = 0; i < table->bucketsCount; i++)                             \
	{                                                                            \
		GTableNode##name##_t* runner = table->buckets[i];                    \
		while (runner)                                                       \
		{                                                                    \
			nodeCount++;                                                 \
			runner = runner->next;                                       \
		}                                                                    \
	}                                                                            \
	size_t newBucketCount = nodeCount;                                           \
	size_t newBucketListSize = sizeof(GTableNode##name##_t*) * newBucketCount;   \
	GTableNode##name##_t** newBuckets = gAlg_malloc(newBucketListSize);          \
	for (size_t i = 0; i < table->bucketsCount; i++)                             \
	{                                                                            \
		GTableNode##name##_t* runner = table->buckets[i];                    \
		while (runner)                                                       \
		{                                                                    \
			size_t newBucketIndex = runner->hash % newBucketCount;       \
			GTable##name##_Place(newBuckets, newBucketIndex, runner);    \
			runner = runner->next;                                       \
		}                                                                    \
	}                                                                            \
	gAlg_free(table->buckets);                                                   \
	table->buckets = newBuckets;                                                 \
	table->bucketsCount = newBucketCount;                                        \
	return 0;                                                                    \
}                                                                                    \
//////////////////////////////////////////////////////////////////////////////////////
#endif