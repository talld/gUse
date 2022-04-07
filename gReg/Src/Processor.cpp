#include "Processor.h"
namespace gReg
{

	EntryMap process(const char *fBuff, size_t buffSize)
	{
		ParseInfo currentParse = {};
		currentParse.fBuff     = fBuff;
		currentParse.buffSize  = buffSize;
		currentParse.offset    = 0;

		EntryMap entryMap           = {};
		entryMap.int64EntryMap      = {};
		entryMap.float64EntryMap    = {};
		entryMap.stringEntryMap     = {};

		while (currentParse.fBuff[currentParse.offset] != EOF)
		{
			skipWhiteSpace(currentParse);

			switch (currentParse.fBuff[currentParse.offset])
			{
				case OPEN_TAG_TOKEN:
					parseOpeningTag(currentParse);
					break;

				case CLOSE_TAG_TOKEN:
					parseClosingTag(currentParse);
					break;

				case INT_TOKEN:
					parseIntEntry(currentParse, entryMap);
					break;

				case FLOAT_TOKEN:
					parseFloatEntry(currentParse, entryMap);
					break;

				case STRING_TOKEN:
					parseStringEntry(currentParse, entryMap);
					break;

				default:
					break;
			}
		}

		return entryMap;
	}

	ParseInfo skipWhiteSpace(ParseInfo &parseInfo)
	{
		// skip whitespace
		while(  parseInfo.fBuff[parseInfo.offset] != EOF
		     && std::isspace(parseInfo.fBuff[++parseInfo.offset]) ) ;

		return parseInfo;
	}

	std::string slurpWord(ParseInfo& parseInfo)
	{
		std::string str;
		skipWhiteSpace(parseInfo);

		do
		{
			str += parseInfo.fBuff[parseInfo.offset];
		}
		while(std::isspace(parseInfo.fBuff[++parseInfo.offset]));

		return str;
	}

	size_t parseOpeningTag(ParseInfo &parseInfo)
	{
		slurpWord(parseInfo);
		return 0;
	}

	size_t parseClosingTag(ParseInfo &parseInfo)
	{
		return 0;
	}

	Int64Entry_t parseIntEntry(ParseInfo &parseInfo, EntryMap& entryMap)
	{
		Int64Entry_t int64Entry = {};

		return int64Entry;
	}

	Float64Entry_t parseFloatEntry(ParseInfo &parseInfo, EntryMap& entryMap)
	{
		Float64Entry_t float64Entry = {};

		return float64Entry;
	}

	StringEntry_t parseStringEntry(ParseInfo &parseInfo, EntryMap& entryMap)
	{
		StringEntry_t stringEntry = {};

		return stringEntry;
	}
}