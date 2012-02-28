// LFilterMapper.h : Declaration of the CLFilterMapper

#ifndef __LFILTERMAPPER_H_
#define __LFILTERMAPPER_H_

#include "resource.h"       // main symbols

namespace LMedia
{

/////////////////////////////////////////////////////////////////////////////
// CLFilterMapper
class CLFilterMapper : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CLFilterMapper, &CLSID_LFilterMapper>,
	public ILFilterMapper,
	public ILFilterMapper2
{
public:
	CLFilterMapper()
	{
	}

	/*
DECLARE_REGISTRY_RESOURCEID(IDR_LFILTERMAPPER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLFilterMapper)
	COM_INTERFACE_ENTRY(ILFilterMapper)
	COM_INTERFACE_ENTRY(ILFilterMapper2)
END_COM_MAP()
*/

// ILFilterMapper
public:
	STDMETHOD(RegisterFilter)(REFCLSID clsidFilter, LPCWSTR name, HINSTANCE hInst, long resID);
};

}	// LMedia

#endif //__LFILTERMAPPER_H_
