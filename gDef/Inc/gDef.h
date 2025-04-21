#ifndef GDEF_H
#define GDEF_H

#define GDEF_FUNCTION_POINTER_DECL(returnType, Name, ...) typedef returnType (*Name)(__VA_ARGS__)

#define GDEF_BIT_SET(val,nbit)   ((val) |=  (1<<(nbit)))
#define GDEF_BIT_CLEAR(val,nbit) ((val) &= ~(1<<(nbit)))
#define GDEF_BIT_FLIP(val,nbit)  ((val) ^=  (1<<(nbit)))
#define GDEF_BIT_CHECK(val,nbit) ((val) &   (1<<(nbit)))

#endif //GDEF_H
