// SMILRootLayoutDlg.h : Declaration of the CSMILRootLayoutDlg

#ifndef __SMILROOTLAYOUTDLG_H_
#define __SMILROOTLAYOUTDLG_H_

#include "resource.h"       // main symbols

#if 0
/////////////////////////////////////////////////////////////////////////////
// CSMILRootLayoutDlg
class ATL_NO_VTABLE CSMILRootLayoutDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSMILRootLayoutDlg, &CLSID_SMILRootLayoutDlg>,
	public IDispatchImpl<ISMILRootLayoutDlg, &IID_ISMILRootLayoutDlg, &LIBID_LXMLEDITORLib>,

	public CUIDialogImpl<CSMILRootLayoutDlg, CAxDialogImpl<CSMILRootLayoutDlg> >,
	public IInspectWebElementDlg,

	public IDispEventImpl<2, CSMILRootLayoutDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CSMILRootLayoutDlg()
	{
	}

	CComPtr<IEElement> m_webElement;

	enum { IDD = IDD_SMILROOTLAYOUTDLG };

	void SetControls();

//DECLARE_REGISTRY_RESOURCEID(IDR_SMILROOTLAYOUTDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSMILRootLayoutDlg)
	COM_INTERFACE_ENTRY(ISMILRootLayoutDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IInspectWebElementDlg)
END_COM_MAP()

BEGIN_SINK_MAP(CSMILRootLayoutDlg)
   SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()

	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);

BEGIN_MSG_MAP(CSMILRootLayoutDlg)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_CLOSE, OnClose)
//	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	COMMAND_HANDLER(IDC_SMILANIMATE_TYPE, CBN_SELCHANGE, OnChangeType)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ISMILRootLayoutDlg
public:
	STDMETHOD(SetElement)(/*[in]*/ IEElement* webElement);
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"RootLayout");
		return S_OK;
	}
};

#endif //__SMILROOTLAYOUTDLG_H_

#endif