#ifndef GARRAY_H
#define GARRAY_H

#include <gArray.inc>

#include <stdint.h>

GARRAY_TYPE_INC(void* , Ptr);

GARRAY_TYPE_INC(float , Float);
GARRAY_TYPE_INC(double , Double);

GARRAY_TYPE_INC(uint64_t, Int64);
GARRAY_TYPE_INC(uint32_t, Int32);
GARRAY_TYPE_INC(uint16_t, Int16);

#endif // GARRAY_H
