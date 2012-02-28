#include "codegen.h"

#include "../Include/coff.h"

struct _IMAGE_SECTION_HEADER;

namespace System
{

//namespace cpp
//{

class CodeCompExt CCOFFObjectFile : public CObjectFile
{
public:
	CCOFFObjectFile();

	~CCOFFObjectFile();

	vector<_IMAGE_SECTION_HEADER*> m_sectionHeaders;

	int AddSymbol(const char* symbolName, IMAGE_SYMBOL** ppSymbol);

	virtual int AddSymbol(const char* name, FSymbol** ppSymbol);
//	virtual IMAGE_SYMBOL* GetSymbolRef(int index);
	virtual int Create(std::FILE* fp, cpp::CGlobal* pGlobal, System::Scope* pGlobalScope, const vector<T_Declarator*>& globals, CFunctionCode* pCode, int cpu_id);

	int GetTypeInd(System::Type* pType);

	map<System::Type*,int> m_types;

protected:

	uint m_SizeOfStringTable;
	uint m_StringTableBytes;
	char* m_StringTable;

	vector<IMAGE_SYMBOL> m_symbols;
};

//}	// cpp

}
