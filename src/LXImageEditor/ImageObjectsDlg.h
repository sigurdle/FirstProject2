// ImageObjectsDlg.h : Declaration of the CImageObjectsDlg

#ifndef __IMAGEOBJECTSDLG_H_
#define __IMAGEOBJECTSDLG_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImageObjectsDlg
class ATL_NO_VTABLE CImageObjectsDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CImageObjectsDlg, &CLSID_ImageObjectsDlg>,
//	public IDispatchImpl<IImageObjectsDlg, &IID_IImageObjectsDlg, &LIBID_WEBEDITORLib>,

	public CUIDialogImpl<CImageObjectsDlg, CWindowImpl<CImageObjectsDlg> >,
	public CUIEventHandlerImpl

//	public IDispEventImpl<1, CImageObjectsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_WEBEDITORLib, 1, 0>
{
public:
	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CImageObjectsDlg()
	{
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CImageObjectsDlg)
//	COM_INTERFACE_ENTRY(IImageObjectsDlg)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()

BEGIN_SINK_MAP(CImageObjectsDlg)
  // SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
//   SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/4, OnViewGroupSelectionChanging)
END_SINK_MAP()

BEGIN_MSG_MAP(CImageObjectsDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IImageObjectsDlg
public:
	/*
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Inspector");
		return S_OK;
	}
	*/
	STDMETHODIMP CalcLayout(DWORD dwFlags, long nLength, SIZE* pVal)
	{
		// Fill in sensible default values
		pVal->cx = 210;
		pVal->cy = 180;

		return S_OK;
	}

// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

#endif //__IMAGEOBJECTSDLG_H_
