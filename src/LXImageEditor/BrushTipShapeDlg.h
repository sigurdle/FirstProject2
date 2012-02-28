// BrushTipShapeDlg.h : Declaration of the CBrushTipShapeDlg

#ifndef __BrushTipShapeDlg_H_
#define __BrushTipShapeDlg_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBrushTipShapeDlg
class ATL_NO_VTABLE CBrushTipShapeDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CBrushTipShapeDlg, &CLSID_BrushTipShapeDlg>,
//	public IDispatchImpl<IBrushTipShapeDlg, &IID_IBrushTipShapeDlg, &LIBID_WEBEDITORLib>,

	public CUIDialogImpl<CBrushTipShapeDlg, CDialogImpl<CBrushTipShapeDlg> >,
	public CUIEventHandlerImpl

//	public IDispEventImpl<1, CBrushTipShapeDlg, &DIID__IEXMLViewGroupEvents, &LIBID_WEBEDITORLib, 1, 0>
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CBrushTipShapeDlg()
	{
	}

	enum { IDD = IDD_BRUSHTIPSHAPEDLG };

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBrushTipShapeDlg)
//	COM_INTERFACE_ENTRY(IBrushTipShapeDlg)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()

BEGIN_SINK_MAP(CBrushTipShapeDlg)
  // SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
//   SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/4, OnViewGroupSelectionChanging)
END_SINK_MAP()

BEGIN_MSG_MAP(CBrushTipShapeDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	COMMAND_HANDLER(IDC_BRUSH_SIZE, EN_KILLFOCUS, OnBrushSize)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnBrushSize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// IBrushTipShapeDlg
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

#endif //__BrushTipShapeDlg_H_
