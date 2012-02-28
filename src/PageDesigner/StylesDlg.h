// StylesDlg.h : Declaration of the CStylesDlg

#ifndef __STYLESDLG_H_
#define __STYLESDLG_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStylesDlg
class ATL_NO_VTABLE CStylesDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStylesDlg, &CLSID_StylesDlg>,
	public ISupportErrorInfo,
	public IDispatchImpl<IStylesDlg, &IID_IStylesDlg, &LIBID_PAGEDESIGNERLib>
{
public:
	CStylesDlg()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STYLESDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStylesDlg)
	COM_INTERFACE_ENTRY(IStylesDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IStylesDlg
public:
};

#endif //__STYLESDLG_H_
