#ifndef __VCMapFileParser_h__
#define __VCMapFileParser_h__

namespace System
{

interface IMapFileDataReceiver
{
	virtual bool OnLoadAddress(DWORD address) = 0;
	virtual bool OnGroup(uint section, DWORD section_offset, DWORD length, const char* name, const char* classname) = 0;
	virtual bool OnSymbol(uint section, DWORD section_offset, DWORD flat_address, const char* symbolname, const char* objfilename) = 0;
};

class LFCEXT VCMapFileParser
{
public:
	int Parse(StringIn filename, IMapFileDataReceiver* receiver);
};

}

#endif // __VCMapFileParser_h__
