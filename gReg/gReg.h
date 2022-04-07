#ifndef GREG_H
#define GREG_H

#include <cstdint>
#include <string>

long gReg_createRegFile(const char * fName);

long gReg_openRegFile(const char * fName);

bool gReg_addInt64Value(const char * eleName, uint64_t val);

uint64_t gReg_getInt64Value(const char * eleName);

bool gReg_addFloat64Value(const char * eleName, double val);

double gReg_getFloat64Value(const char * eleName);

bool gReg_Exit();

bool gReg_saveAndExit();

#endif  // GREG_H
