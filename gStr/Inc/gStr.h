#ifndef GSTR_H
#define GSTR_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <gLog.h>
#include "../Src/GString.h" //FIXME: find a way to predec structs?

typedef struct GString GString_t;

uint64_t loadGDict(char* gDict, char*** dict);

#endif  // GSTR_H
