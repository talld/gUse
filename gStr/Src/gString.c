#include "gString.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct GString_t GString_t;
struct GString_t
{
	size_t n;
	char* str;
};

GString_t* GString_Create(const char* string)
{
	GString_t* ret = malloc(sizeof(GString_t));

	size_t strLen = strlen(string);

	ret->str = malloc(sizeof(char) * strLen);
	ret->n = strLen;

	memcpy(ret->str, string, strLen);

	return ret;
}

void GString_Delete(GString_t* gString)
{
	free(gString->str);
	free(gString);
}

char* GString_ToCString(GString_t* gString)
{
	char* str = malloc(gString->n + 1);
	str[gString->n] = '\0';

	memcpy(str, gString->str, gString->n);

	return str;
}

GString_t* GString_Copy(GString_t* gString)
{
	GString_t* ret = malloc(sizeof(GString_t));

	ret->str = malloc(sizeof(char) * gString->n);
	memcpy(ret, gString, sizeof(char) * gString->n);

	return ret;
}

GString_t* GString_Append(GString_t* dst, GString_t* src)
{
	size_t dstSize = (sizeof(char) * dst->n);
	size_t srcSize = (sizeof(char) * src->n);

	GString_t* newStr = malloc(sizeof(*newStr));

	if(newStr)
	{
		newStr->n = dstSize + srcSize;
		newStr->str =  malloc(newStr->n);

		memcpy(newStr->str, dst->str, dstSize);
		memcpy(newStr->str + dstSize, src->str, srcSize);
	}

	return newStr;
}

int GString_Equals(GString_t* a, GString_t* b)
{
	int matches = 1;

	size_t minLen = (a->n < b->n)? a->n : b->n;
	for (size_t i = 0; i < minLen; ++i)
	{
		if (a->str[i] != b->str[i])
		{
			matches = 0;
			break;
		}
	}

	return matches;
}

int GString_IsPath(GString_t* gString)
{
	static char illegalChars[] = {
			':', '?', '*', '+', '%', ';', '<', '>', '|', '\"', '\'', '\n',
			EOF
	};

	int isValidPath = 1;

	for(size_t i = 0; i < gString->n; i++)
	{
		for(size_t j = 0; illegalChars[j] != EOF; j++)
		{
			if (gString->str[i] == illegalChars[j])
			{
				isValidPath = 0;
				break;
			}
		}
	}

	return isValidPath;
}

int GString_IsDirectory(GString_t* gString)
{
	int isValidPath = GString_IsPath(gString);
	char end = gString->str[gString->n-1];
	int endsInSlash = (end == '/');

	return isValidPath && endsInSlash;
}

GString_t* GString_PathExtractFilename(GString_t* toStrip)
{
	GString_t* ret = NULL;

	size_t strLen = toStrip->n;

	while(strLen > 0 && toStrip->str[strLen] != '/') strLen--;

	// the last char we just saw was a '/' so step over it
	strLen++;

	ret = malloc(sizeof(*ret));
	ret->n = toStrip->n - strLen;
	ret->str = malloc(strLen);

	memcpy(ret->str, toStrip->str + strLen, ret->n);

	return ret;
}

void GString_StripNewLine(GString_t* toStrip)
{
	for(size_t i = 0; i < toStrip->n; i++)
	{
		while(toStrip->str[i] == '\n' || toStrip->str[i] == '\r')
		{
			size_t distToEnd = (toStrip->n - i);
			if(distToEnd != 0)
			{
				memcpy(&toStrip->str[i], &toStrip->str[i + 1], distToEnd * sizeof(*toStrip->str));
				toStrip->n--;
			}
			else
			{
				toStrip->str[toStrip->n] = '\0';
			}

		}
	}
}

GString_t* GString_PathStripFilename(GString_t* toStrip)
{
	GString_t* ret = NULL;

	size_t strLen = toStrip->n;

	while(strLen > 0 && toStrip->str[strLen] != '/') strLen--;

	// the last char we just saw was a '/' so step over it
	strLen++;

	ret = malloc(sizeof(*ret));
	ret->n = strLen;
	ret->str = malloc(strLen);

	memcpy(ret->str, toStrip->str, strLen);

	return ret;
}

void GString_TranslatePath(GString_t* toTranslate)
{
	for(size_t i = 0; i < toTranslate->n; i++)
	{
		if(toTranslate->str[i] == '\\')
		{
			toTranslate->str[i] = '/';
		}
	}
}