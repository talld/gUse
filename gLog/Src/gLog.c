#include <gLog.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

enum {kOutputBufferMax = 255};
static FILE* sapChannels[255];

static int Glog_InitChannels()
{
	sapChannels[0] = stdin;
	sapChannels[1] = stdout;
	sapChannels[2] = stderr;
	return 0;
}

int Glog_Init()
{
	int ret = Glog_InitChannels();
	return ret;
}



int Glog_AcquireChannel(size_t threadID, uint8_t channel)
{
	return 0;
}



int Glog_ReleaseChannel(uint8_t channel, size_t threadID)
{
	return 0;
}



int Glog_WriteOutputBufferToChannel(uint8_t channel, char* pOutputBuffer, size_t* pOutputBufferUsed)
{
	fwrite(pOutputBuffer, sizeof(char), (*pOutputBufferUsed), sapChannels[channel]);
	fflush(sapChannels[channel]);
	(*pOutputBufferUsed) = 0;
	return 0;
}



int Glog_GetUIntLength(size_t i, size_t radix)
{
	int nDigits = 1; /* zero-th place always populated */

	if(i)
	{
		double logIBaseRadix = log(i) / log(radix);
		nDigits += floor(logIBaseRadix);
	}

	return nDigits;
}



int Glog_GetSIntLength(size_t i, size_t radix)
{
	int nDigits = Glog_GetUIntLength(i, radix);
	return nDigits + 1; /* +1 spot for the '-' */
}



int Glog_WriteUBase10ToChannel(uint8_t channel, size_t i, char* pOutputBuffer, size_t* pOutputBufferUsed)
{
	int nDigits = Glog_GetUIntLength(i, 10);

	if (((*pOutputBufferUsed) + nDigits) >= kOutputBufferMax)
	{
		Glog_WriteOutputBufferToChannel(channel, pOutputBuffer, pOutputBufferUsed);
	}

	ultoa(i, &pOutputBuffer[*pOutputBufferUsed], 10);
	*pOutputBufferUsed += nDigits;
	return 0;
}

int Glog_WriteStringToChannel(uint8_t channel, const char* string, char* pOutputBuffer, size_t* pOutputBufferUsed)
{
	size_t len = strlen(string);

	if (((*pOutputBuffer) + len) >= kOutputBufferMax)
	{
		Glog_WriteOutputBufferToChannel(channel, pOutputBuffer, pOutputBufferUsed);
	}

	memmove(&pOutputBuffer[(*pOutputBufferUsed)], string, len);
	(*pOutputBufferUsed) += len;

	return 0;
}

int Glog_StartRecord(uint8_t channel, size_t threadID, const char* reporter, const char* file, size_t line, char* pOutputBuffer, size_t* pOutputBufferUsed)
{
	Glog_WriteStringToChannel(channel, "{ \"ThreadID\" : ", pOutputBuffer, pOutputBufferUsed);
	Glog_WriteUBase10ToChannel(channel, threadID, pOutputBuffer, pOutputBufferUsed);

	Glog_WriteStringToChannel(channel, ", \"reporter\" : \"", pOutputBuffer, pOutputBufferUsed);
	Glog_WriteStringToChannel(channel, reporter, pOutputBuffer, pOutputBufferUsed);

	Glog_WriteStringToChannel(channel, "\", \"file\" : \"", pOutputBuffer, pOutputBufferUsed);
	Glog_WriteStringToChannel(channel, file, pOutputBuffer, pOutputBufferUsed);

	Glog_WriteStringToChannel(channel, "\", \"line\" : ", pOutputBuffer, pOutputBufferUsed);
	Glog_WriteUBase10ToChannel(channel, line, pOutputBuffer, pOutputBufferUsed);

	return 0;
}

int Glog_WriteFormatToChannel(uint8_t channel, const char* format, va_list argp, char* pOutputBuffer, size_t* pOutputBufferUsed)
{
	/* handle format section */
	enum { kPrintTokenMax = 16 };
	size_t printTokenCount = 0;
	size_t printTokenPositions[kPrintTokenMax];

	/* find all the tokens we gotta work with first */
	/* might as well get some cheeky output to the buffer as well */
	size_t formatLen = 0;
	while (format[formatLen] != '\0')
	{
		if (format[formatLen] == '%')
		{
			printTokenPositions[printTokenCount++] = formatLen;
		}

		if (printTokenCount == 0)
		{
			if ((*pOutputBufferUsed) >= kOutputBufferMax)
			{

				Glog_WriteOutputBufferToChannel(channel, pOutputBuffer, pOutputBufferUsed);
			}

			pOutputBuffer[(*pOutputBufferUsed)++] = format[formatLen];
		}

		formatLen++;
	}

	/* we should have done all the text up to the first print token at this point */
	/* so the next thing should be a print token */
	for(size_t i = 0; i < printTokenCount; i++)
	{

		size_t position = printTokenPositions[i] + 1;
		switch (format[position])
		{
			case ('z'):
			{
				position++;
				if (format[position] == 'u')
				{
					size_t d = va_arg(argp, size_t);
					Glog_WriteUBase10ToChannel(channel, d, pOutputBuffer, pOutputBufferUsed);
					position++;
				}
				break;
			}

			case ('s'):
			{
				position++;
				const char* p = va_arg(argp, char*);
				Glog_WriteStringToChannel(channel, p, pOutputBuffer, pOutputBufferUsed);
				break;
			}

			case ('p'):
			{
				position++;
				size_t p = va_arg(argp, size_t);
				Glog_WriteUBase10ToChannel(channel, p, pOutputBuffer, pOutputBufferUsed);
				break;
			}
		}

		/* go until the next token or end of string */
		size_t nextPosition = formatLen;
		if(i != printTokenCount-1)
		{ /* there is another token to process after this */
			nextPosition = printTokenPositions[i+1];
		}
		while(position < nextPosition)
		{
			if ((*pOutputBufferUsed) >= kOutputBufferMax)
			{

				Glog_WriteOutputBufferToChannel(channel, pOutputBuffer, pOutputBufferUsed);
			}

			pOutputBuffer[(*pOutputBufferUsed)++] = format[position++];
		}
	}

	return 0;
}

int Glog_Info(uint8_t channel, size_t threadID, const char* reporter, const char* file, size_t line, const char* format, ...)
{
	size_t formatProcessed = 0;

	size_t outputBufferUsed = 0;
	char aOutputBuffer[kOutputBufferMax];

	Glog_StartRecord(channel, threadID, reporter, file, line, aOutputBuffer, &outputBufferUsed);

	Glog_WriteStringToChannel(channel, ", \"info\" : \"", (char*)aOutputBuffer, &outputBufferUsed);

	va_list  argp;
	va_start(argp, format);
	Glog_WriteFormatToChannel(channel, format, argp, aOutputBuffer, &outputBufferUsed);
	va_end(argp);

	Glog_WriteStringToChannel(channel, "\" },\r\n", (char*)aOutputBuffer, &outputBufferUsed);
	Glog_WriteOutputBufferToChannel(channel, aOutputBuffer, &outputBufferUsed);

	return 0;
}
