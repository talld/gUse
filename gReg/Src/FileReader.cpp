#include "FileReader.h"

namespace gReg
{

	///----------------------------------------------------------------------------------------
	std::vector<char> readFile(const std::string &filename)
	{

		std::vector<char> buffer;

		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (file.is_open())
		{
			int64_t fileSize = file.tellg();
			buffer.resize(fileSize);

			file.seekg(0);
			file.read(buffer.data(), fileSize);

			file.close();
		}

		return buffer;
	}

	///----------------------------------------------------------------------------------------
	const char *readFileC(const char *fName, size_t &fSize)
	{
		char *buffer = nullptr;
		FILE *file = fopen(fName, "r");

		if (file)
		{
			fseek(file, 0, SEEK_END);
			fSize = ftell(file);
			fseek(file, 0, SEEK_SET);

			buffer = static_cast<char *>(calloc(1, ++fSize));

			if (!buffer)
			{
				// TODO: mem err
			}

			fread(buffer, fSize, 1, file);
			fclose(file);
		} else
		{
			// TODO: no file err
		}

		return buffer;
	}

}