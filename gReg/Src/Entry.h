#ifndef GREG_ENTRY_H
#define GREG_ENTRY_H

#include <map>
#include <string>
#include <cstdint>

namespace gReg
{

	template<typename T>
	struct entry
	{
		const char ID[256]; // a single ID shouldn't
		T entry;
	};

	typedef entry<uint64_t>         Int64Entry_t;
	typedef entry<double>           Float64Entry_t;
	typedef entry<std::string>      StringEntry_t;

	typedef std::string Path_t;
	typedef std::map<Path_t, Int64Entry_t>       Int64EntryMap_t;
	typedef std::map<Path_t, Float64Entry_t>     Float64EntryMap_t;
	typedef std::map<Path_t, StringEntry_t>      StringEntryMap_t;


	struct EntryMap
	{
		StringEntryMap_t      stringEntryMap;
		Float64EntryMap_t     float64EntryMap;
		Int64EntryMap_t       int64EntryMap;
	};

	static EntryMap g_EntryMap;
}

#endif //GREG_ENTRY_H
