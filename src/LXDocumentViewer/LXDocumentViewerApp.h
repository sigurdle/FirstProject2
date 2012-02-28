// LXDocumentViewerApp.h : Declaration of the CLXDocumentViewerApp

#ifndef __LXDOCUMENTVIEWERAPP_H_
#define __LXDOCUMENTVIEWERAPP_H_

#include "resource.h"       // main symbols
#include "../CmdHandler.h"

/////////////////////////////////////////////////////////////////////////////
// CLXDocumentViewerApp
class ATL_NO_VTABLE CLXDocumentViewerApp : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLXDocumentViewerApp, &CLSID_LXDocumentViewerApp>,
	public IDispatchImpl<ILXDocumentViewerApp, &IID_ILXDocumentViewerApp, &LIBID_LXDOCUMENTVIEWERLib>,

#if 0
	public ILXAddin,
	public IUIManagerSite,
#endif
	public ProcessTargetCommands,

//	public ILCustomizable,

	public IServiceProviderImpl<CLXDocumentViewerApp>

//	public ILDOMEventListener,
{
public:
	CLXDocumentViewerApp()
	{
	}

	int FinalConstruct();

	WCHAR m_connstr[256];
	ADODB::_ConnectionPtr m_conn;
	HRESULT AddToLibrary(LPCTSTR dir);

	CComPtr<ILXAddinSite> m_spAddinSite;
	//CComPtr<ILXFrameworkFrame> m_frame;

	HRESULT NewWindow();

DECLARE_REGISTRY_RESOURCEID(IDR_LXDOCUMENTVIEWERAPP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXDocumentViewerApp)
	COM_INTERFACE_ENTRY(ILXDocumentViewerApp)
//	COM_INTERFACE_ENTRY(IDispatch)
#if 0
	COM_INTERFACE_ENTRY(ILXAddin)
	COM_INTERFACE_ENTRY(IUIManagerSite)
#endif
//	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(ILDOMEventListener)

//	COM_INTERFACE_ENTRY(ILCustomizable)

	COM_INTERFACE_ENTRY(IServiceProvider)
END_COM_MAP()

BEGIN_SERVICE_MAP(CLXDocumentViewerApp)
	if (::InlineIsEqualGUID(guidService, IID_IWebBrowserApp))
			return QueryInterface(riid, ppvObject);
END_SERVICE_MAP()

/*
BEGIN_HANDLE_EVENT_MAP(CLXDocumentViewerApp)

END_HANDLE_EVENT_MAP()
*/

DECLARE_CMD_MAP(CLXDocumentViewerApp)

	LRESULT OnFileOpen(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSearchForMedia(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// ILXDocumentViewerApp
public:
// ILXAddin
	STDMETHOD(GetSite)(ILXAddinSite* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_spAddinSite;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(SetSite)(ILXAddinSite* pSite);

	STDMETHOD(Show)(ILXUIElement* element)
	{
		return E_NOTIMPL;
	}

//	STDMETHOD(BindToObjectMoniker)(IMoniker* mk, IBindCtx* ctx, IUnknown* *pVal);
//	STDMETHOD(OnCreateFrame)();
//	STDMETHOD(CreateDlg)(UINT nID, IUIDlg* *pVal);

// ILCustomizable
//	STDMETHOD(LoadDocument)(/*[out,retval]*/ ILDOMDocument **pVal);
};

#endif //__LXDOCUMENTVIEWERAPP_H_
