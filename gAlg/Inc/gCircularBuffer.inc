#include "gCircularBuffer.h"

#include "gAlg.h"
#include <stdint.h>

/****************************************************************************************************/
#define GCIRCULAR_BUFFER_TYPE_INC(type, name)                                                        \
typedef struct GCircularBuffer##name##_t GCircularBuffer##name##_t;                                  \
GCircularBuffer##name##_t* GCircularBuffer##name##_Create(size_t capacity);                          \
void GCircularBuffer##name##_Destroy(GCircularBuffer##name##_t* pGCircularBuffer);                   \
int GCircularBuffer##name##_Write(GCircularBuffer##name##_t* pGCircularBuffer, type toInsert);       \
type GCircularBuffer##name##_Read(GCircularBuffer##name##_t* pGCircularBuffer);                      \
int GCircularBuffer##name##_Reset(GCircularBuffer##name##_t* pGCircularBuffer);                      \
size_t GCircularBuffer##name##_Pending(GCircularBuffer##name##_t* pGCircularBuffer);                 \
type* GCircularBuffer##name##_Last(GCircularBuffer##name##_t* pGCircularBuffer);                     \
/****************************************************************************************************/
#define GCIRCULAR_BUFFER_TYPE_SRC(type, name)                                                        \
typedef struct GCircularBuffer##name##_t GCircularBuffer##name##_t;                                  \
struct GCircularBuffer##name##_t                                                                     \
{                                                                                                    \
	size_t capacity;                                                                                 \
	size_t used;                                                                                     \
	size_t readHead;                                                                                 \
	size_t writeHead;                                                                                \
	type aElements[44];                                                                              \
};                                                                                                   \
                                                                                                     \
GCircularBuffer##name##_t* GCircularBuffer##name##_Create(size_t capacity)                           \
{                                                                                                    \
	size_t trueSize = sizeof(GCircularBuffer##name##_t) + (sizeof(type) * capacity);                 \
	GCircularBuffer##name##_t* pGCircularBuffer = gAlg_malloc(trueSize);                             \
	*pGCircularBuffer = (GCircularBuffer##name##_t){                                                 \
		.capacity = capacity,                                                                        \
		.used = 0,                                                                                   \
		.readHead = 0,                                                                               \
		.writeHead = 0,                                                                              \
	};                                                                                               \
                                                                                                     \
	return pGCircularBuffer;                                                                         \
}                                                                                                    \
                                                                                                     \
void GCircularBuffer##name##_Destroy(GCircularBuffer##name##_t* pGCircularBuffer)                    \
{                                                                                                    \
	gAlg_free(pGCircularBuffer);                                                                     \
}                                                                                                    \
                                                                                                     \
int GCircularBuffer##name##_Write(GCircularBuffer##name##_t* pGCircularBuffer, type toInsert)        \
{                                                                                                    \
	pGCircularBuffer->aElements[pGCircularBuffer->writeHead] = toInsert;                             \
	size_t capacity = pGCircularBuffer->capacity;                                                    \
	size_t used = pGCircularBuffer->used;                                                            \
	pGCircularBuffer->writeHead = (pGCircularBuffer->writeHead + 1) % capacity;                      \
	pGCircularBuffer->used = (used < capacity)? used+1 : capacity;                                   \
	return 0;                                                                                        \
}                                                                                                    \
                                                                                                     \
type GCircularBuffer##name##_Read(GCircularBuffer##name##_t* pGCircularBuffer)                       \
{                                                                                                    \
	type retVal = pGCircularBuffer->aElements[pGCircularBuffer->readHead];                           \
	pGCircularBuffer->readHead= (pGCircularBuffer->readHead + 1) % pGCircularBuffer->capacity;       \
	pGCircularBuffer->used = (pGCircularBuffer->used > 0)? pGCircularBuffer->used-1 : 0;             \
	return retVal;                                                                                   \
}                                                                                                    \
                                                                                                     \
int GCircularBuffer##name##_Reset(GCircularBuffer##name##_t* pGCircularBuffer)                       \
{                                                                                                    \
	pGCircularBuffer->used = 0;                                                                      \
	pGCircularBuffer->readHead = 0;                                                                  \
	pGCircularBuffer->writeHead = 0;                                                                 \
	return 0;                                                                                        \
}                                                                                                    \
                                                                                                     \
size_t GCircularBuffer##name##_Pending(GCircularBuffer##name##_t* pGCircularBuffer)                  \
{                                                                                                    \
	return pGCircularBuffer->used;                                                                   \
}                                                                                                    \
                                                                                                     \
type* GCircularBuffer##name##_Last(GCircularBuffer##name##_t* pGCircularBuffer)                      \
{                                                                                                    \
	size_t capacity = pGCircularBuffer->capacity;                                                    \
	size_t lastWriteIndex = ((capacity + pGCircularBuffer->writeHead) - 1) % capacity;               \
	return &pGCircularBuffer->aElements[lastWriteIndex];                                             \
}                                                                                                    \
/****************************************************************************************************/