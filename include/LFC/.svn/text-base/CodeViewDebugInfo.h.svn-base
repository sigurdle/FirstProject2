#ifndef CodeViewDebugInfo_h
#define CodeViewDebugInfo_h

#include "coff.h"
#include "CodeView.h"
#include "Microsoft/cvinfo.h"

namespace System
{

class LFCEXT CodeViewDebugInfo : public DebugInfo
{
public:
	CTOR CodeViewDebugInfo(uint8* data, System::Scope* _pGlobalScope);

//	virtual ULONG Release();
	virtual System::Scope* GetScope();
	virtual int Parse(ObjectFileParser* pImage, IDebugInfoReceiver* receiver, ULONG_PTR dwData);

//	System::Scope* LookupProc(StringIn name);

protected:

	System::Type* GetType(int typind, ULONG_PTR dwData);
	void FieldList(CodeView::TYPTYPE* typ, System::ClassType* pClass, ULONG_PTR dwData);

	CodeView::OMFGlobalTypes* m_pOMFGlobalTypes;
	vector<System::Type*> m_pTypes;
	System::Scope* m_pGlobalScope;

	ubyte* m_data;
	System::IDebugInfoReceiver* m_pReceiver;
};

}	// System

#endif // CodeViewDebugInfo_h
