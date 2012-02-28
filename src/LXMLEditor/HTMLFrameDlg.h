// HTMLFrameDlg.h : Declaration of the CHTMLFrameDlg

#ifndef __HTMLFRAMEDLG_H_
#define __HTMLFRAMEDLG_H_

#include "resource.h"       // main symbols

#if 0
/////////////////////////////////////////////////////////////////////////////
// CHTMLFrameDlg
class ATL_NO_VTABLE CHTMLFrameDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CHTMLFrameDlg, &CLSID_HTMLFrameDlg>,
	public IDispatchImpl<IHTMLFrameDlg, &IID_IHTMLFrameDlg, &LIBID_LXMLEDITORLib>,

	public CUIDialogImpl<CHTMLFrameDlg, CAxDialogImpl<CHTMLFrameDlg> >,
	public IInspectWebElementDlg,

	public IDispEventImpl<2, CHTMLFrameDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CHTMLFrameDlg() : m_wndName(NULL, this, 1),
							m_wndSrc(NULL, this, 2)
	{
		m_bChanging = 0;
	}

	CComPtr<IEElement> m_webElement;

	CContainedWindow m_wndName;
	CContainedWindow m_wndSrc;

	int m_bChanging;

	enum { IDD = IDD_HTMLFRAMEDLG };

	void SetControls();

//DECLARE_REGISTRY_RESOURCEID(IDR_HTMLFRAMEDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHTMLFrameDlg)
	COM_INTERFACE_ENTRY(IHTMLFrameDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IInspectWebElementDlg)
END_COM_MAP()

BEGIN_SINK_MAP(CHTMLFrameDlg)
   SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()

	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);

BEGIN_MSG_MAP(CHTMLFrameDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)

	COMMAND_HANDLER(IDC_HTMLFRAME_SCROLLING, CBN_SELCHANGE, OnChangeScrolling)
	COMMAND_HANDLER(IDC_HTMLFRAME_NORESIZE, BN_CLICKED, OnClickedNoResize)

	ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_KEYDOWN, OnNameKeydown)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnNameKeydown)

	ALT_MSG_MAP(2)
		MESSAGE_HANDLER(WM_KEYDOWN, OnSrcKeydown)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnSrcKeydown)

END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnNameKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSrcKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnChangeScrolling(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedNoResize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// IHTMLFrameDlg
public:
	STDMETHOD(SetElement)(/*[in]*/ IEElement* webElement);
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"HTML Frame");
		return S_OK;
	}
};

#endif //__HTMLFRAMEDLG_H_

#endif