#pragma once

#include "objectfileparser.h"
#include "a_out.h"
#include "stab.h"

namespace System
{

class CodeCompExt AOutParser : public ObjectFileParser
{
public:
	CTOR AOutParser();
	virtual ~AOutParser();

	virtual long GetFormat();
	virtual long GetCPU();

	virtual uint8* GetData(uint nSection);
	virtual ULONG GetDataSize(uint nSection);

	virtual uint GetNumberOfSections();

	virtual uint GetNumberOfSymbols();
	virtual ObjectSymbol* GetSymbol(uint index);

	virtual uint GetNumberOfRelocations(uint nSection);
	virtual Relocation* GetRelocation(uint nSection, int index);

	virtual long Read(IO::Stream* stream);

	DebugInfo* GetDebugInfo(System::Scope* pGlobalScope);

	exec exec_header;

	int m_TextOffset;
	int m_DataOffset;
	int m_TextRelocOffset;
	int m_DataRelocOffset;
	int m_SymbolTableOffset;
	int m_StringTableOffset;
	char* m_StringData;

	nlist* m_nlistSymbols;
	Relocation* m_tr;
	Relocation* m_dr;

protected:

	StabDebugInfo* m_pDebugInfo;

	_Ptr<IO::Stream> m_pStream;

	uint m_nsymbols;
	uint m_numberOfSections;
	int m_Sections[3];
};

}	// System
