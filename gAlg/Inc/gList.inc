#ifndef GLIST_INC_H
#define GLIST_INC_H

#include "gAlg.h"
#include <stdint.h>
#include <stddef.h>

////////////////////////////////////////////////////////////////////////////////
#define GLIST_TYPE_INC(type, name)                                             \
typedef struct GList##name##_t GList##name##_t;                                \
                                                                               \
GList##name##_t* GList##name##_Create();                                       \
type GList##name##_Front(GList##name##_t* list);                               \
void GList##name##_PushFront(GList##name##_t* list, type toInsert);            \
void GList##name##_PopFront(GList##name##_t* list);                            \
type GList##name##_Back(GList##name##_t* list);                                \
void GList##name##_PushBack(GList##name##_t* list, type toInsert);             \
void GList##name##_PopBack(GList##name##_t* list);                             \
////////////////////////////////////////////////////////////////////////////////
#define GLIST_TYPE_SRC(type, name)                                             \
typedef struct GListNode##name##_t GListNode##name##_t;                        \
struct GListNode##name##_t                                                     \
{                                                                              \
	GListNode##name##_t* next;                                                 \
	GListNode##name##_t* prev;                                                 \
	type value;                                                                \
};                                                                             \
                                                                               \
typedef struct GList##name##_t GList##name##_t;                                \
struct GList##name##_t                                                         \
{                                                                              \
	size_t count;                                                              \
	GListNode##name##_t* front;                                                \
};                                                                             \
                                                                               \
GList##name##_t* GList##name##_Create()                                        \
{                                                                              \
	GList##name##_t* ret = gAlg_malloc(sizeof(*ret));                          \
	ret->count = 0;                                                            \
	ret->front = NULL;                                                         \
	return ret;                                                                \
}                                                                              \
                                                                               \
size_t GList##name##_Count(GList##name##_t* list)                              \
{                                                                              \
	return list->count;                                                        \
}                                                                              \
                                                                               \
type GList##name##_Get(GList##name##_t* list, size_t index)                    \
{                                                                              \
	type ret = (type){0};                                                      \
    GListNode##name##_t* runner = list->front;                                 \
                                                                               \
	while(runner != NULL && index--)                                           \
	{                                                                          \
		runner = runner->next;                                                 \
	}                                                                          \
                                                                               \
	if(runner == NULL)                                                         \
	{                                                                          \
		ret = runner->value;                                                   \
	}                                                                          \
                                                                               \
	return ret;                                                                \
}                                                                              \
                                                                               \
type GList##name##_Front(GList##name##_t* list)                                \
{                                                                              \
	return list->front->value;                                                 \
}                                                                              \
                                                                               \
void GList##name##_PushFront(GList##name##_t* list, type toInsert)             \
{                                                                              \
	GListNode##name##_t* newNode = gAlg_malloc(sizeof(*newNode));              \
	newNode->prev = NULL;                                                      \
	newNode->next = list->front;                                               \
	newNode->value = toInsert;                                                 \
                                                                               \
	if(list->front != NULL)                                                    \
	{                                                                          \
		list->front->prev = newNode;                                           \
		list->front  = newNode;                                                \
	}                                                                          \
	else                                                                       \
	{                                                                          \
		list->front = newNode;                                                 \
	}                                                                          \
	list->count++;                                                             \
}                                                                              \
                                                                               \
void GList##name##_PopFront(GList##name##_t* list)                             \
{                                                                              \
	if(list->front != NULL)                                                    \
	{                                                                          \
        GListNode##name##_t* toDelete = list->front;                           \
		list->front = list->front->next;                                       \
		gAlg_free(toDelete); /*old font is still new fronts prev*/             \
		if(list->front){list->front->prev = NULL;}                             \
		                                                                       \
		list->count--;                                                         \
	}                                                                          \
}                                                                              \
                                                                               \
type GList##name##_Back(GList##name##_t* list)                                 \
{                                                                              \
	size_t count = list->count;                                                \
	GListNode##name##_t* runner = list->front;                                 \
	while(--count)                                                             \
	{                                                                          \
		runner = runner->next;                                                 \
	}                                                                          \
                                                                               \
	return runner->value;                                                      \
}                                                                              \
                                                                               \
void GList##name##_PushBack(GList##name##_t* list, type toInsert)              \
{                                                                              \
	GListNode##name##_t* newNode = gAlg_malloc(sizeof(*newNode));              \
	newNode->next = NULL;                                                      \
	newNode->value = toInsert;                                                 \
                                                                               \
	if(list->front != NULL)                                                    \
	{                                                                          \
		size_t count = list->count;                                            \
		GListNode##name##_t* back = list->front;                               \
		while(--count)                                                         \
		{                                                                      \
			back = back->next;                                                 \
		}                                                                      \
                                                                               \
		back->next = newNode;                                                  \
		newNode->prev = back;                                                  \
	}                                                                          \
	else                                                                       \
	{                                                                          \
		list->front = newNode;                                                 \
	}                                                                          \
	list->count++;                                                             \
}                                                                              \
void GList##name##_PopBack(GList##name##_t* list)                              \
{                                                                              \
	if(list->front)                                                            \
	{                                                                          \
		size_t count = list->count;                                            \
		GListNode##name##_t* back = list->front;                               \
		while(--count)                                                         \
		{                                                                      \
			back = back->next;                                                 \
		}                                                                      \
                                                                               \
		if(back->prev) {back->prev->next = NULL;}                              \
		gAlg_free(back);                                                       \
		list->count--;                                                         \
	}                                                                          \
}                                                                              \
////////////////////////////////////////////////////////////////////////////////
#endif