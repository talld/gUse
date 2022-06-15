#ifndef GSTR_GSTRING_H
#define GSTR_GSTRING_H

#include <gStr.h>

uint64_t loadGDict(void* gDictData, GDictionary_t** dict);

uint64_t saveToGDict(std::vector<char*> strings, GDictionary_t** out );

#endif // GSTR_GSTRING_H
