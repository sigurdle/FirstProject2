// WebDAVView.h : Declaration of the CWebDAVView

#ifndef __WEBDAVVIEW_H_
#define __WEBDAVVIEW_H_

#include "resource.h"       // main symbols

class CSiteItem;

#import "..\FTPMod\FTPMod.tlb" no_namespace, named_guids, raw_interfaces_only

/////////////////////////////////////////////////////////////////////////////
// CWebDAVView
class ATL_NO_VTABLE CWebDAVView : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CWebDAVView, &CLSID_WebDAVView>,
	public IConnectionPointContainerImpl<CWebDAVView>,
//	public IDispatchImpl<IWebDAVView, &IID_IWebDAVView, &LIBID_WEBEDITORLib>,
	public ProcessTargetCommands,
	public CUIDialogImpl<CWebDAVView, CWindowImpl<CWebDAVView> >
{
public:

	CWebDAVView()
	{
	}

	int FinalConstruct();
	void FinalRelease();

	CComboBox m_server;
	CButton m_connect;

//	CComQIPtr<IWebSite>	m_document;

	CAxWindow m_axbrowser;
	CComPtr<IWebDAVBrowser> m_browser;

	void OnSize();

//DECLARE_REGISTRY_RESOURCEID(IDR_WebDAVView)
//DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CWebDAVView)
//	COM_INTERFACE_ENTRY(IWebDAVView)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
//	COM_INTERFACE_ENTRY2(IDispatch, IWebDAVView)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ICommandTarget)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CWebDAVView)
END_CONNECTION_POINT_MAP()

DECLARE_CMD_MAP(CWebDAVView)

BEGIN_MSG_MAP(CWebDAVView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
/*
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk);
*/
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

/*
	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/

// IWebDAVView
public:
//	STDMETHOD(get_document)(/*[out, retval]*/ IWebSite* *pVal);
//	STDMETHOD(put_document)(/*[in]*/ IWebSite* newVal);
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"FTP");
		return S_OK;
	}
// ICommandTarget
	STDMETHOD(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
	{
		/*
		CComQIPtr<ICommandTarget> target;
		
	// Try document first
	//	target = m_document;
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
		*/

	// Then try us
		return ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	}
};

#endif //__WEBDAVVIEW_H_
