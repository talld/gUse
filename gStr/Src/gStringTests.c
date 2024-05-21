#include <gStr.h>
#include <gString.h>

int GString_DoStripTest()
{
	GString_t* blank = GString_Create("");

	GString_t* pathWithFile = GString_Create("Some/Path/To/Afile.txt");
	GString_t* justFile = GString_Create("Afile.txt");
	GString_t* justPath = GString_Create("Some/Path/To/");

	GString_t* extractedFilename = GString_PathExtractFilename(pathWithFile);
	if(GString_Equals(extractedFilename, justFile) != 1){ goto FAIL;}

	GString_t* extractedFilename2 = GString_PathExtractFilename(justPath);
	if(GString_Equals(extractedFilename2, blank) != 1){ goto FAIL;}

	GString_t* stripped = GString_PathStripFilename(pathWithFile);
	if(GString_Equals(stripped, justPath) != 1){ goto FAIL;}

	return 0;

	FAIL:
	return 1;
}


int GString_DoTests()
{
	int err;
	err = GString_DoStripTest(); if(err) { goto FAIL;}

	return 0;

	FAIL:
	return 1;
}