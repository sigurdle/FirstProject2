// ImageLayersDlg.h : Declaration of the CImageLayersDlg

#ifndef __IMAGELAYERSDLG_H_
#define __IMAGELAYERSDLG_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImageLayersDlg
class ATL_NO_VTABLE CImageLayersDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CImageLayersDlg, &CLSID_ImageLayersDlg>,
//	public IDispatchImpl<IImageLayersDlg, &IID_IImageLayersDlg, &LIBID_WEBEDITORLib>,

	public CUIDialogImpl<CImageLayersDlg, CWindowImpl<CImageLayersDlg> >,
	public CUIEventHandlerImpl

//	public IDispEventImpl<1, CImageLayersDlg, &DIID__IEXMLViewGroupEvents, &LIBID_WEBEDITORLib, 1, 0>
{
public:
	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CImageLayersDlg()
	{
		m_app = NULL;
	}

	ILXImageApp* m_app;

	CComPtr<IImageView> m_view;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CImageLayersDlg)
//	COM_INTERFACE_ENTRY(IImageLayersDlg)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()

BEGIN_SINK_MAP(CImageLayersDlg)
  // SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
//   SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/4, OnViewGroupSelectionChanging)
END_SINK_MAP()

BEGIN_MSG_MAP(CImageLayersDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IImageLayersDlg
public:
// IUIDlg
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

#endif //__IMAGELAYERSDLG_H_
