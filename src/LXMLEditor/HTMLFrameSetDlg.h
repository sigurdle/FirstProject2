// HTMLFrameSetDlg.h : Declaration of the CHTMLFrameSetDlg

#ifndef __HTMLFRAMESETDLG_H_
#define __HTMLFRAMESETDLG_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHTMLFrameSetDlg
class CHTMLFrameSetDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CHTMLFrameSetDlg, &CLSID_HTMLFrameSetDlg>,
	public IDispatchImpl<IHTMLFrameSetDlg, &IID_IHTMLFrameSetDlg, &LIBID_LXMLEDITORLib>,

	public CUIDialogImpl<CHTMLFrameSetDlg, CAxDialogImpl<CHTMLFrameSetDlg> >,
	public IInspectWebElementDlg,

	public IDispEventImpl<2, CHTMLFrameSetDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CHTMLFrameSetDlg()
	{
		m_bChanging = 0;
	}

	CComPtr<IEElement> m_webElement;

	int m_bChanging;

	enum { IDD = IDD_HTMLFRAMESETDLG };

	void SetControls();

//DECLARE_REGISTRY_RESOURCEID(IDR_HTMLFRAMESETDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHTMLFrameSetDlg)
	COM_INTERFACE_ENTRY(IHTMLFrameSetDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IInspectWebElementDlg)
END_COM_MAP()

BEGIN_SINK_MAP(CHTMLFrameSetDlg)
   SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()

	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);

BEGIN_MSG_MAP(CHTMLFrameSetDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)

	COMMAND_HANDLER(IDC_HTMLFRAMESET_FRAMESPACING, BN_CLICKED, OnClickedFrameSpacing)
	COMMAND_HANDLER(IDC_HTMLFRAMESET_BORDERCOLORVALUE, BN_CLICKED, OnClickedBorderColorValue)

	MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnClickedFrameSpacing(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedBorderColorValue(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// IHTMLFrameSetDlg
public:
	STDMETHOD(SetElement)(/*[in]*/ IEElement* webElement);
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"HTML Frameset");
		return S_OK;
	}
};

#endif //__HTMLFRAMESETDLG_H_
