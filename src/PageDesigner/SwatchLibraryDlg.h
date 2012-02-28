// SwatchLibraryDlg.h : Declaration of the CSwatchLibraryDlg

#ifndef __SWATCHLIBRARYDLG_H_
#define __SWATCHLIBRARYDLG_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"

/////////////////////////////////////////////////////////////////////////////
// CSwatchLibraryDlg
class ATL_NO_VTABLE CSwatchLibraryDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSwatchLibraryDlg, &CLSID_SwatchLibraryDlg>,
	public ISupportErrorInfo,
	public IDispatchImpl<ISwatchLibraryDlg, &IID_ISwatchLibraryDlg, &LIBID_PAGEDESIGNERLib>
{
public:
	CSwatchLibraryDlg()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SWATCHLIBRARYDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSwatchLibraryDlg)
	COM_INTERFACE_ENTRY(ISwatchLibraryDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISwatchLibraryDlg
public:
};

#endif //__SWATCHLIBRARYDLG_H_
