// LXFrameworkApp.h : Declaration of the CLXFrameworkApp

#ifndef __LXFRAMEWORKAPP_H_
#define __LXFRAMEWORKAPP_H_

#include "resource.h"       // main symbols

#include "LXFrameworkCP.h"

class CLXFrameworkFrame;
class CWebXMLDocument;

class CFormatColor
{
public:
	_bstr_t m_name;
//	long m_index;
	COLORREF m_fgColor;
	COLORREF m_bgColor;
	int m_fgAutomatic;
	int m_bgAutomatic;
};

class CFormatWindow
{
public:
	_bstr_t m_name;
	LOGFONT m_lf;

	CArray<CFormatColor*,CFormatColor*> m_formatColors;

	void GetFormatColorValues(WCHAR* name, COLORREF *fgColor, COLORREF *bgColor)
	{
		for (int i = 0; i < m_formatColors.GetSize(); i++)
		{
			if (!wcscmp(name, m_formatColors[i]->m_name))
			{
				if (fgColor)
				{
					if (m_formatColors[i]->m_fgColor==-1)
						*fgColor = GetSysColor(m_formatColors[i]->m_fgAutomatic);
					else
						*fgColor = m_formatColors[i]->m_fgColor;
				}

				if (bgColor)
				{
					if (m_formatColors[i]->m_bgColor==-1)
						*bgColor = GetSysColor(m_formatColors[i]->m_bgAutomatic);
					else
						*bgColor = m_formatColors[i]->m_bgColor;
				}

				return;
			}
		}
	}

	long RegisterFormatColor(WCHAR* name, COLORREF fgColor, COLORREF bgColor, int fgAutomatic, int bgAutomatic)
	{
		for (int i = 0; i < m_formatColors.GetSize(); i++)
		{
			if (!wcscmp(name, m_formatColors[i]->m_name))
			{
				return i;
			}
		}

		CFormatColor* pFormatColor = new CFormatColor;
		pFormatColor->m_name = name;
		pFormatColor->m_fgColor = fgColor;
		pFormatColor->m_bgColor = bgColor;
		pFormatColor->m_fgAutomatic = fgAutomatic;
		pFormatColor->m_bgAutomatic = bgAutomatic;

		int index = m_formatColors.Add(pFormatColor);

		return index;
	}
};

CFormatWindow* RegisterFormatWindow(WCHAR* name);

/*
// XSLT documents class, Do I have a class for each kind of document ?
class ATL_NO_VTABLE CXSLTDocuments : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDocumentsClass
{
public:
	CXSLTDocuments()
	{
		m_pActiveDocument = NULL;
	}

	CWebXMLDocument* m_pActiveDocument;

BEGIN_COM_MAP(CXSLTDocuments)
	COM_INTERFACE_ENTRY(IDocumentsClass)
END_COM_MAP()
};
*/

#if 0
class ATL_NO_VTABLE CPluginClass : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPluginClass
{
public:
	_bstr_t m_name;
	CLSID	m_clsid;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPluginClass)
	COM_INTERFACE_ENTRY(IPluginClass)
END_COM_MAP()

	STDMETHOD(GetName)(/*[out,retval]*/ BSTR* pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_name.copy();
		return S_OK;
	}
};
#endif

class CLXFrameworkApp;

class ATL_NO_VTABLE CLXFrameworkAddinSite : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ILXAddinSite
{
public:
	CLXFrameworkAddinSite()
	{
	//	m_frame = NULL;
		m_clsid = GUID_NULL;
	}

	int FinalConstruct()
	{
		/*
		CComObject<CLXFrameworkAddinUIManager>::CreateInstance(&m_uiManager);
		m_uiManager->AddRef();
		m_uiManager->m_pAddinSite = this;
		*/

		return 0;
	}

	CComBSTR m_name;
	CLSID m_clsid;
	CComPtr<ILXAddin> m_p;

	//CLXUIAddinElement* m_pElement;
	CLXFrameworkApp* m_pApp;

	CComPtr<ILXUIDocument> m_document;
//	CComPtr<ILPresentation> m_view;

	STDMETHOD(GetUIDocument)(/*[out,retval]*/ ILXUIDocument* *pVal)
	{
		ATLASSERT(0);
		if (pVal == NULL) return E_POINTER;
		*pVal = m_document;
		(*pVal)->AddRef();
		return S_OK;
	}

#if 0
	CComObject<CLXFrameworkAddinUIManager>* m_uiManager;

	void SetFrame(CLXFrameworkFrame* frame)
	{
		m_frame = frame;

		ATLASSERT(m_p);

		m_uiManager->m_pSite = CComQIPtr<IUIManagerSite>(m_p);
	}
#endif

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXFrameworkAddinSite)
	COM_INTERFACE_ENTRY(ILXAddinSite)
END_COM_MAP()

#if 0
	STDMETHOD(GetFrame)(/*[out,retval]*/ ILXFrameworkFrame* *pVal);
	STDMETHOD(GetUIManager)(/*[out,retval]*/ IUnknown* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_uiManager;
		(*pVal)->AddRef();
		return S_OK;
	}

	STDMETHOD(GetName)(/*[out,retval]*/ BSTR* pVal)
	{
		return m_name.CopyTo(pVal);
	}
#endif
};

/////////////////////////////////////////////////////////////////////////////
// CLXFrameworkApp
class ATL_NO_VTABLE CLXFrameworkApp : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLXFrameworkApp, &CLSID_LXFrameworkApp>,

	public IConnectionPointContainerImpl<CLXFrameworkApp>,
	public IDispatchImpl<ILXFrameworkApp, &IID_ILXFrameworkApp, &LIBID_LXFRAMEWORKLib>,
	public ProcessTargetCommands,

	public IProfferService,

	public IServiceProviderImpl<CLXFrameworkApp>,

	public CProxy_ILXFrameworkAppEvents< CLXFrameworkApp >
{
public:

	class CService
	{
	public:
		GUID m_guid;
		CComPtr<IServiceProvider> m_sp;

		DWORD m_cookie;
	};

	CLXFrameworkApp()
	{
		m_dwServiceCookie = 0;
#if 0
		m_frame = NULL;
#endif
		//m_xsltDocuments = NULL;

//		m_ActiveDocument = NULL;

#if 0
		m_atomApp = NULL;
		m_atomSystemTopic = NULL;
#endif
	}

	~CLXFrameworkApp()
	{
#if 0
		ATLASSERT(m_frame == NULL);
#endif
//		ATLASSERT(m_xsltDocuments == NULL);
	}

	int FinalConstruct();
	void FinalRelease();

	DWORD m_dwServiceCookie;
	CArray<CService*,CService*> m_services;

//	IActiveCntDocument* m_ActiveDocument;

//	CComObject<CXSLTDocuments>* m_xsltDocuments;

	CComPtr<ILXUIDocument> m_document;	// The root document of my application
//

	CComObject<CLXFrameworkAddinSite>* m_pAddinSite;

#if 0
	CComObject<CLXFrameworkFrame>* m_frame;
#endif
//	CComQIPtr<IUIContextManager> m_uiManager;
#if 0
	ATOM m_atomApp;
	ATOM m_atomSystemTopic;

	void EnableShellOpen();
#endif

	CString m_pszFullExeName;
	CString m_pszExeName;// = "C:\\MMStudio\\Extras\\LXFramework\\Debug\\LXFramework.exe";

#if 0
	virtual BOOL OnDDECommand(LPTSTR lpszCommand);
#endif

DECLARE_REGISTRY_RESOURCEID(IDR_LXFRAMEWORKAPP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXFrameworkApp)
	COM_INTERFACE_ENTRY(ILXFrameworkApp)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IDispatch)
//	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(ILDOMEventListener)

	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

	COM_INTERFACE_ENTRY(IProfferService)

	COM_INTERFACE_ENTRY(IServiceProvider)
END_COM_MAP()

BEGIN_SERVICE_MAP(CPLXUIInfoBandElement)

//	LPOLESTR clsidstr;
//	StringFromCLSID(guidService, &clsidstr);
//	CoTaskMemFree(clsidstr);

	if (::InlineIsEqualGUID(guidService, IID_IProfferService))
		return QueryInterface(riid, ppvObject);

	for (int i = 0; i < m_services.GetSize(); i++)
	{
		if (::InlineIsEqualGUID(guidService, m_services[i]->m_guid))
		{
			HRESULT hr = m_services[i]->m_sp->QueryService(guidService, riid, ppvObject);
			if (SUCCEEDED(hr) && (*ppvObject != NULL))
				return hr;
		}
	}

END_SERVICE_MAP()

BEGIN_CONNECTION_POINT_MAP(CLXFrameworkApp)
	CONNECTION_POINT_ENTRY(DIID__ILXFrameworkAppEvents)
END_CONNECTION_POINT_MAP()

DECLARE_CMD_MAP(CLXFrameworkApp)

//	LRESULT OnFilePrefs(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//	LRESULT OnFileNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

//	LRESULT OnNewNewsItem(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

//	LRESULT OnCustomize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnHelp(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// ILXFrameworkApp
public:
	STDMETHOD(get_Document)(/*[in]*/ ILXUIDocument* *pVal);

// IProfferService
	STDMETHOD(ProfferService)(/* [in] */ REFGUID rguidService, /* [in] */ IServiceProvider *psp, /* [out] */ DWORD *pdwCookie);
	STDMETHOD(RevokeService)(/* [in] */ DWORD dwCookie);

//	STDMETHOD(get_ActiveDocument)(/*[out, retval]*/ IActiveCntDocument* *pVal);
//	STDMETHOD(get_tabSize)(/*[out, retval]*/ long *pVal);
//	STDMETHOD(CreateNewDocument)(/*[in]*/ BSTR filename, /*[out,retval]*/ IEDocument** pVal);
//	STDMETHOD(OpenDocument)(/*[in]*/ BSTR pathName, /*[out,retval]*/ VARIANT_BOOL* success);
//	STDMETHOD(OpenDocument)(IUnknown* filesystem, BSTR pathName, VARIANT_BOOL *success);
//	STDMETHOD(get_uiManager)(/*[out, retval]*/ IUnknown* *pVal);
//	STDMETHOD(get_frame)(/*[out, retval]*/ ILXFrameworkFrame* *pVal);
	STDMETHOD(Run)(/*[out,retval]*/ long* result);
};

#endif //__LXFRAMEWORKAPP_H_
