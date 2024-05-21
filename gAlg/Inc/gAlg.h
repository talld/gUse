#ifndef GALG_H
#define GALG_H

// malloc
#ifndef gAlg_malloc

#ifndef gAlg_stdLib
#include "stdlib.h"
#define gAlg_stdLib
#endif

#define	gAlg_malloc malloc
#endif

// calloc
#ifndef gAlg_calloc

#ifndef gAlg_stdLib
#include "stdlib.h"
#define gAlg_stdLib
#endif

#define	gAlg_calloc calloc
#endif

// realloc
#ifndef gAlg_realloc

#ifndef gAlg_stdLib
#include "stdlib.h"
#define gAlg_stdLib
#endif

#define	gAlg_realloc realloc
#endif

// free
#ifndef gAlg_free

#ifndef gAlg_stdLib
#include "stdlib.h"
#define gAlg_stdLib
#endif

#define	gAlg_free free
#endif

// memcpy
#ifndef gAlg_memcpy

#ifndef gAlg_stringLib
#include "string.h"
#define gAlg_stringLib
#endif

#define	gAlg_memcpy memcpy
#endif

#ifndef gAlgGArrayGrowthFactor
#define gAlgGArrayGrowthFactor 2
#endif

int GAlg_DoTests();

#endif // GALG_H
