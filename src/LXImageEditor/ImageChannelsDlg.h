// ImageChannelsDlg.h : Declaration of the CImageChannelsDlg

#ifndef __IMAGECHANNELSDLG_H_
#define __IMAGECHANNELSDLG_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImageChannelsDlg
class ATL_NO_VTABLE CImageChannelsDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CImageChannelsDlg, &CLSID_ImageChannelsDlg>,
//	public IDispatchImpl<IImageChannelsDlg, &IID_IImageChannelsDlg, &LIBID_WEBEDITORLib>,

	public CUIDialogImpl<CImageChannelsDlg, CWindowImpl<CImageChannelsDlg> >,
	public CUIEventHandlerImpl,

	public IDispEventImpl<1, CImageChannelsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_WEBEDITORLib, 1, 0>
{
public:
	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CImageChannelsDlg()
	{
	}

	CComPtr<IImageView> m_view;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CImageChannelsDlg)
//	COM_INTERFACE_ENTRY(IImageChannelsDlg)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()

BEGIN_SINK_MAP(CImageChannelsDlg)
  // SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
//   SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/4, OnViewGroupSelectionChanging)
END_SINK_MAP()

BEGIN_MSG_MAP(CImageChannelsDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IImageChannelsDlg
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

#endif //__IMAGECHANNELSDLG_H_
