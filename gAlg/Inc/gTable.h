#ifndef GTABLE_H
#define GTABLE_H

#include <gTable.inc>

#include <stddef.h>
#include <stdint.h>

GTABLE_TYPE_INC( void*,    Ptr    );
GTABLE_TYPE_INC( float,    Float  );
GTABLE_TYPE_INC( double,   Double );
GTABLE_TYPE_INC( int64_t,  Int64  );
GTABLE_TYPE_INC( int32_t,  Int32  );
GTABLE_TYPE_INC( int16_t,  Int16  );
GTABLE_TYPE_INC( int8_t,   Int8   );
GTABLE_TYPE_INC( uint64_t, UInt64 );
GTABLE_TYPE_INC( uint32_t, UInt32 );
GTABLE_TYPE_INC( uint16_t, UInt16 );
GTABLE_TYPE_INC( uint8_t,  UInt8  );

#endif // GTABLE_H
