#ifndef GTABLE_H
#define GTABLE_H

#include <gTable.inc>

#include <stddef.h>
#include <stdint.h>

GTABLE_TYPE_INC(void* , Ptr);

GTABLE_TYPE_INC(float , Float);
GTABLE_TYPE_INC(double , Double);

GTABLE_TYPE_INC(int64_t, Int64);
GTABLE_TYPE_INC(int32_t, Int32);
GTABLE_TYPE_INC(int16_t, Int16);

#endif // GTABLE_H
