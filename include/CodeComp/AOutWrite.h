//#include "cppcompiler.h"
#include "codegen.h"
#include "a_out.h"

//namespace cpp
//{

namespace System
{

class CodeCompExt CAOut : public CObjectFile
{
public:
	CAOut()
	{
	//	m_SizeOfStringTable = 0;
	//	m_StringTableBytes = 0;
	//	m_StringTable = NULL;
	}

protected:
//	int m_SizeOfStringTable;
//	int m_StringTableBytes;
//	char* m_StringTable;
	vector<FSymbol*> m_symbols;

public:
	virtual int AddSymbol(const char* name, FSymbol** ppSymbol);
	virtual int Create(std::FILE* fp, cpp::CGlobal* pGlobal, System::Scope* pGlobalScope, const vector<T_Declarator*>& globals, CFunctionCode* pCode, int cpu_id);
};

//}	// cpp
}
