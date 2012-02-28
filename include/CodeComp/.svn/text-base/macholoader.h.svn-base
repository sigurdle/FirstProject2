#include "../Include/objectfileparser.h"
#include "../Include/stab.h"
#include "../Include/mach_o.h"

namespace System
{
namespace MachO
{

class CodeCompExt MachOLoader : public ObjectFileParser
{
public:
	CTOR MachOLoader()
	{
		m_nsymbols = 0;
		m_symbols = NULL;
	}

	virtual long GetFormat()
	{
		return -1;
	}
	virtual long GetCPU();
	virtual uint GetNumberOfSymbols();
	virtual ObjectSymbol* GetSymbol(uint index);

	virtual long Read(IO::Stream* stream);

	virtual uint GetNumberOfSections();
	virtual int GetSection(uint nSection, SECTION* pSection);

	DebugInfo* GetDebugInfo(System::Scope* pGlobalScope);

public:

	mach_header m_header;
	int m_nsymbols;
	nlist* m_symbols;
	vector<section*> m_sections;
};

}	// MachO
}	// System
