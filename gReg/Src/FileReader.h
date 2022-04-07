#ifndef GREG_FILEREADER_H
#define GREG_FILEREADER_H

#include "Entry.h"

#include <string>
#include <fstream>
#include <vector>

namespace gReg
{
	const char *readFileC(const char *fName, size_t &fSize);

	std::vector<char> readFile(const std::string &filename);
}
#endif //GREG_FILEREADER_H
