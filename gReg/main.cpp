#include "FileReader.h"
#include "Processor.h"

int main()
{
	size_t fSize = 0;
	const char* fBuff = gReg::readFileC("/home/talldie/Dev/gReg/test.greg", fSize);
	gReg::process(fBuff, fSize);
	printf("%s",fBuff);
}