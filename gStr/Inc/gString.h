#ifndef GSTR_GSTRING_H
#define GSTR_GSTRING_H

#include "gStr.h"

#include <stdint.h>

typedef struct GString_t GString_t;

GString_t* GString_Create(const char* string);

void GString_Delete(GString_t* string);

char* GString_CString(GString_t* gString);

size_t GString_Length(GString_t* gString);

GString_t* GString_Copy(GString_t* gString);

GString_t* GString_Append(GString_t* dst, GString_t* src);

int GString_Equals(GString_t* a, GString_t* b);

int GString_IsPath(GString_t* gString);

int GString_IsDirectory(GString_t* gString);

GString_t* GString_PathExtractFilename(GString_t* toStrip);

void GString_StripNewLine(GString_t* toStrip);

GString_t* GString_PathStripFilename(GString_t* toStrip);

#endif // GSTR_GSTRING_H
