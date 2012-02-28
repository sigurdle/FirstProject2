#ifndef __AmigaHunkParser_h__
#define __AmigaHunkParser_h__

#include "objectfileparser.h"

#include "doshunks.h"
#include "stab.h"

#ifndef CodeCompExt
#define CodeCompExt DECLSPEC_DLLIMPORT
#endif

namespace System
{

#define ID_MASK			0x0000FFFF

struct HUNK_Header
{
	uint32 ID;	// HUNK_HEADER signature
	uint32 pad0;
	uint32 num_hunks;
	uint32 first;
	uint32 last;
};

class CodeCompExt AmigaHunkParser : public ObjectFileParser
{
public:
	class Hunk
	{
	public:
		CTOR Hunk()
		{
			m_size = 0;
			m_data = NULL;
		}

		uint32 m_size;
		uint8* m_data;
	};

	CTOR AmigaHunkParser();
	virtual ~AmigaHunkParser();

	virtual long GetFormat()
	{
		return 0;
	}
	virtual long GetCPU()
	{
		return 0;
	}

	virtual uint GetNumberOfSymbols();
	virtual ObjectSymbol* GetSymbol(uint index);

	virtual uint GetNumberOfSections();
	virtual ULONG GetDataSize(uint nSection);
	virtual uint8* GetData(uint nSection);

	virtual long Read(IO::Stream* stream);

	virtual DebugInfo* GetDebugInfo(System::Scope* pGlobalScope);

public:

	typedef vector<Hunk> hunkvector;

	HUNK_Header header;

//	template class CodeCompExt ::vector<Hunk>;
	hunkvector m_hunks;

	nlist* stab;
	int nstabs;
	char* stabstr;

protected:

	StabDebugInfo* m_pDebugInfo;

//	template class LFCEXT ::vector<ObjectSymbol*>;
	vector<ObjectSymbol*> m_symbols;
};

}

#endif	// __AmigaHunkParser_h__
