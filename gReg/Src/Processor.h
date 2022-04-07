#ifndef GREG_PROCESSOR_H
#define GREG_PROCESSOR_H

#include "Entry.h"
#include "FileReader.h"

namespace gReg
{
	struct ParseInfo
	{
		const char* fBuff;
		size_t offset;
		size_t buffSize;
	};

	constexpr char OPEN_TAG_TOKEN    = '>';
	constexpr char CLOSE_TAG_TOKEN   = '<';
	constexpr char ASSIGNMENT_TOKEN  = '<';
	constexpr char INT_TOKEN         = 'I';
	constexpr char FLOAT_TOKEN       = 'F';
	constexpr char STRING_TOKEN      = 'S';
	constexpr char LONG_STRING_TOKEN = 'T';


	/***
	 *
	 * @param fBuff
	 * @param buffSize
	 * @return
	 */
	EntryMap process(const char* fBuff, size_t buffSize);

	static ParseInfo skipWhiteSpace(ParseInfo& parseInfo);

	static std::string slurpWord(ParseInfo& parseInfo);

	static size_t parseOpeningTag(ParseInfo& parseInfo);

	static size_t parseClosingTag(ParseInfo& parseInfo);

	static Int64Entry_t parseIntEntry(ParseInfo& parseInfo, EntryMap& entryMap);

	static Float64Entry_t parseFloatEntry(ParseInfo& parseInfo, EntryMap& entryMap);

	static StringEntry_t parseStringEntry(ParseInfo& parseInfo, EntryMap& entryMap);

}

#endif //GREG_PROCESSOR_H
