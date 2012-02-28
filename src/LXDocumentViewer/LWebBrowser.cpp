// LWebBrowser.cpp : Implementation of CLWebBrowser
#include "stdafx.h"
#include "LXDocumentViewer.h"
#include "LXDocumentViewer2.h"
#include "LWebBrowser.h"

#if _WINDOWS
#include "LXDocumentViewerApp.h"
#endif

#include "../LXML/LXML2.h"

HRESULT getElementByAttribute(ILDOMElement* parent, BSTR name, BSTR value, ILDOMElement **pVal)
{
	CComPtr<ILDOMNode> node;
	parent->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement, &IID_ILDOMElement> element((IUnknown*)node);
		if (element)
		{
			CComBSTR v;
			element->getAttribute(name, &v);
			if (!cmpbstr(value, v))
			{
				*pVal = element;
				(*pVal)->AddRef();
				return S_OK;
			}

			getElementByAttribute(element, name, value, pVal);
			if (*pVal)
				return S_OK;
		}
		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	*pVal = NULL;
	return S_OK;
}

#if _WINDOWS
_variant_t GetProperty(IUnknown* unk, BSTR name)
{
	CComQIPtr<IDispatchEx> dispex = unk;

	DISPID dispid;
	dispex->GetDispID(name, fdexNameEnsure, &dispid);

	DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};

	/*
	putid = DISPID_PROPERTYGET;
//	var.vt = VT_R8;
//	var.dblVal = wpt.X;
	dispparams.rgvarg = &var;
	//dispparams.rgdispidNamedArgs = &putid;
	dispparams.cArgs = 0;
	dispparams.cNamedArgs = 0;
	*/

	VARIANT varres;
	VariantInit(&varres);

	HRESULT hr = dispex->InvokeEx(dispid, LOCALE_USER_DEFAULT, 
		DISPATCH_PROPERTYGET, &dispparamsNoArgs,
		&varres, NULL, NULL);

	ATLASSERT(SUCCEEDED(hr));

	return varres;
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CLWebBrowser

class CLXDocumentViewerApp;

HRESULT CLWebBrowser::Init(CLXDocumentViewerApp* pApp, CLWebBrowser* pOtherView)
{
	m_pApp = pApp;

#if 0
	CComPtr<ILXUIDocument> appdocument;
	m_pApp->m_spAddinSite->GetUIDocument(&appdocument);

	CComPtr<ILDOMDocument> doc;
	doc.CoCreateInstance(CLSID_LDOMDocument);

	VARIANT_BOOL success;
	doc->load(_variant_t(L"C:\\docviewer_layout.xml"), &success);

	CComPtr<ILDOMElement> documentElement;
	doc->get_documentElement(&documentElement);

	CComPtr<ILDOMNode> window;
	appdocument->importNode(documentElement, VARIANT_TRUE/*deep*/, &window);

	m_windowElement = CComQIPtr<ILXUIElement>(window);

	if (TRUE)
	{
		CComPtr<ILDOMElement> explorerBarPopup;
		getElementByAttribute(m_windowElement, L"name", L"id_explorer_bars", &explorerBarPopup);

		CComPtr<ICatInformation> catinfo;
		HRESULT hr = S_OK;
 
		hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_ICatInformation,
			(LPVOID*)&catinfo);

		if (SUCCEEDED(hr))
		{
			CRegKey clsidkey;
			clsidkey.Open(HKEY_CLASSES_ROOT, "CLSID");

			CATID impl[1];
			impl[0] = CATID_InfoBand;

			CComPtr<IEnumCLSID> enumClsid;
			catinfo->EnumClassesOfCategories(1, impl, 0, NULL, &enumClsid);

			CLSID clsid;
			ULONG fetched;
			while ((enumClsid->Next(1, &clsid, &fetched) == S_OK) && (fetched == 1))
			{
				LPOLESTR clsidstr;
				StringFromCLSID(clsid, &clsidstr);

				CRegKey key;
				key.Open(clsidkey, _bstr_t(clsidstr));

				TCHAR name[260];
				DWORD cb = 260;
				key.QueryValue(name, NULL, &cb);

				CoTaskMemFree(clsidstr);

				CComPtr<ILXUIMenuItemElement> menuitem;
				appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"menuitem", (ILDOMElement**)&menuitem);
				menuitem->put_caption(_variant_t(_bstr_t(name)));

				explorerBarPopup->appendChild(menuitem, NULL);
#if 0
				CComPtr<IUnknown> unk;
				unk.CoCreateInstance(clsid);

				if (unk)
				{
					MessageBeep(-1);
				}
#endif
#if 0
				CComQIPtr<ILXMLImplementation> impl = unk;

				if (impl)
				{
					m_implList.Add(impl.Detach());
				}
#endif
			}
		}
	}

	CComPtr<ILDOMElement> appelement;
	appdocument->get_documentElement(&appelement);
	appelement->appendChild(window, NULL);
#endif

	CComPtr<ILXUIDocument> document;
//	document.CoCreateInstance(CLSID_LXUIDocument);
	::CoCreateInstance(CLSID_LXUIDocument, NULL, CLSCTX_ALL, IID_ILXUIDocument, (void**)&document);

	CComPtr<ILXUIElement> element;
	document->loadXAML(CComVariant(L"C:\\docviewer_layout.xml"), &element);

	m_windowElement = CComQIPtr<ILXUIWindowBase, &IID_ILXUIWindowBase>((IUnknown*)element);
	if (m_windowElement)
	{
		m_windowElement->Show();

		CComQIPtr<ILDOMEventTarget, &IID_ILDOMEventTarget>((IUnknown*)m_windowElement)->addEventListener(OLESTR("click"), static_cast<ILDOMEventListener*>(this), VARIANT_FALSE/*bCapture*/);
		CComQIPtr<ILDOMEventTarget, &IID_ILDOMEventTarget>((IUnknown*)m_windowElement)->addEventListener(OLESTR("command"), static_cast<ILDOMEventListener*>(this), VARIANT_FALSE/*bCapture*/);
		CComQIPtr<ILDOMEventTarget, &IID_ILDOMEventTarget>((IUnknown*)m_windowElement)->addEventListener(OLESTR("ddecommand"), static_cast<ILDOMEventListener*>(this), VARIANT_FALSE/*bCapture*/);
	}

	document.Detach();	// TODO remove

	return S_OK;

#if 0
	CComPtr<ILDOMDocument> document;
	document.CoCreateInstance(CLSID_LDOMDocument);

	document->load();

	CComPtr<ILDOMNode> layout;
	appdocument->importNode(documentElement, VARIANT_TRUE/*deep*/, &toolbar);
	

	CComPtr<ILDOMElement>
	appdocument->get_documentElement(&documentElement);
#endif
}

// ILDOMEventListener
STDMETHODIMP CLWebBrowser::handleEvent(ILDOMEvent* evt)
{
//	CComPtr<ILXUIDocument> appdocument;
//	m_pApp->m_spAddinSite->GetUIDocument(&appdocument);

///
	CComBSTR type;
	evt->get_type(&type);

	if (!wcscmp(type, OLESTR("click")))
	{
		// TODO, check id of target
		CComPtr<ILDOMEventTarget> target;
		evt->get_target(&target);

		CComQIPtr<ILXUIElement, &IID_ILXUIElement> element((IUnknown*)target);

		CComBSTR id;
		element->get_ID(&id);

		if (!cmpbstr(id, OLESTR("docviewer_back")))
		{
#if _WINDOWS
			GoBack();
#endif

			return S_OK;
		}
		else if (!cmpbstr(id, OLESTR("docviewer_forward")))
		{
#if _WINDOWS
			GoForward();
#endif
			return S_OK;
		}
		else if (!cmpbstr(id, OLESTR("docviewer_go")))
		{
			ATLASSERT(0);
#if 0
			CComPtr<ILDOMElement> urlElement;
			getElementByAttribute(m_windowElement, L"name", L"docviewer_url", &urlElement);

			CComBSTR url;
			urlElement->getAttribute(L"value", &url);

			Navigate(url, NULL, NULL, NULL, NULL);
#endif
			return S_OK;
		}
	}
	else if (!wcscmp(type, OLESTR("ddecommand")))
	{
#if _WINDOWS
		MessageBox(NULL, "", "", MB_OK);
		_bstr_t value = ::GetProperty(evt, L"value");
#endif
	}

	return ProcessTargetCommands::handleEvent(evt);
}

BEGIN_CMD_MAP(CLWebBrowser)
#if _WINDOWS
// File
	CMD_HANDLER(2, OnNewWindow)
#endif

END_CMD_MAP()

LRESULT CLWebBrowser::OnNewWindow(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComObject<CLWebBrowser>* pBrowser;
	CComObject<CLWebBrowser>::CreateInstance(&pBrowser);
	if (pBrowser)
	{
		pBrowser->AddRef();

		pBrowser->Init(m_pApp, this);
	}

	return 0;
}

HRESULT GetElementByID(ILXUIElement* element, BSTR searchID, ILXUIElement* *pVal)
{
	CComBSTR ID;
	element->get_ID(&ID);

	if (!cmpbstr(ID, searchID))
	{
		*pVal = element;
		(*pVal)->AddRef();
		return S_OK;
	}

	CComPtr<ILXUINode> node;
	element->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILXUIElement, &IID_ILXUIElement> element((IUnknown*)node);
		if (element)
		{
			CComPtr<ILXUIElement> element2;
			GetElementByID(element, searchID, &element2);
			if (element2)
			{
				*pVal = element2.Detach();
				return S_OK;
			}
		}

		CComPtr<ILXUINode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	return S_OK;
}

#if _WINDOWS
// IWebBrowser

/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::GoBack( void)
{
	CComPtr<ILXUIElement> element;
	GetElementByID(m_windowElement, L"docviewer_target", &element);

	CComQIPtr<ILXUIFrame> frameElement = element;

	HRESULT hr = frameElement->GoBack();

	return S_OK;
}

/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::GoForward( void)
{
#if 0
	CComPtr<ILDOMElement> element;
	appdocument->getElementById(L"docviewer_target", &element);

	CComQIPtr<ILHTMLIFrameElement> iframeElement = element;

	iframeElement->goForward();
#endif

	return S_OK;
}
        
/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::GoHome( void)
{
	return E_NOTIMPL;
}
        
/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::GoSearch( void)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::Navigate( 
            /* [in] */ BSTR URL,
            /* [optional][in] */ VARIANT *Flags,
            /* [optional][in] */ VARIANT *TargetFrameName,
            /* [optional][in] */ VARIANT *PostData,
            /* [optional][in] */ VARIANT *Headers)
{
	CComPtr<ILXUIDocument> appdocument;
	m_pApp->m_spAddinSite->GetUIDocument(&appdocument);

	ATLASSERT(0);
#if 0

	CComPtr<ILDOMElement> element;
	getElementByAttribute(m_windowElement, L"name", L"docviewer_target", &element);
	CComQIPtr<ILHTMLIFrameElement> iframeElement = element;
	iframeElement->setAttribute(L"src", URL);
#endif

	return S_OK;
}

/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::Refresh( void)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::Refresh2( 
            /* [optional][in] */ VARIANT *Level)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::Stop( void)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Application( 
            /* [retval][out] */ IDispatch **ppDisp)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Parent( 
            /* [retval][out] */ IDispatch **ppDisp)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Container( 
            /* [retval][out] */ IDispatch **ppDisp)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Document( 
            /* [retval][out] */ IDispatch **ppDisp)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_TopLevelContainer( 
            /* [retval][out] */ VARIANT_BOOL *pBool)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Type( 
            /* [retval][out] */ BSTR *Type)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Left( 
            /* [retval][out] */ long *pl)
{
	return E_NOTIMPL;
}

/* [propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_Left( 
            /* [in] */ long Left)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Top( 
            /* [retval][out] */ long *pl)
{
	return E_NOTIMPL;
}

/* [propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_Top( 
            /* [in] */ long Top)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Width( 
            /* [retval][out] */ long *pl)
{
	return E_NOTIMPL;
}
        
/* [propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_Width( 
            /* [in] */ long Width)
{
	return E_NOTIMPL;
}
        
/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Height( 
            /* [retval][out] */ long *pl)
{
	return E_NOTIMPL;
}
        
/* [propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_Height( 
            /* [in] */ long Height)
{
	return E_NOTIMPL;
}
        
/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_LocationName( 
            /* [retval][out] */ BSTR *LocationName) 
{
	return E_NOTIMPL;
}
        
/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_LocationURL( 
            /* [retval][out] */ BSTR *LocationURL) 
{
	return E_NOTIMPL;
}
        
/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Busy( 
            /* [retval][out] */ VARIANT_BOOL *pBool)
{
	return E_NOTIMPL;
}

// IWebBrowserApp

/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::Quit( void)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::ClientToWindow( 
   /* [out][in] */ int *pcx,
   /* [out][in] */ int *pcy)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::PutProperty( 
   /* [in] */ BSTR Property,
   /* [in] */ VARIANT vtValue)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::GetProperty( 
   /* [in] */ BSTR Property,
   /* [retval][out] */ VARIANT *pvtValue)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Name( 
   /* [retval][out] */ BSTR *Name)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_HWND( 
   /* [retval][out] */ SHANDLE_PTR *pHWND)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_FullName( 
   /* [retval][out] */ BSTR *FullName)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Path( 
   /* [retval][out] */ BSTR *Path)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Visible( 
   /* [retval][out] */ VARIANT_BOOL *pBool)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_Visible( 
   /* [in] */ VARIANT_BOOL Value)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_StatusBar( 
   /* [retval][out] */ VARIANT_BOOL *pBool)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_StatusBar( 
   /* [in] */ VARIANT_BOOL Value)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_StatusText( 
   /* [retval][out] */ BSTR *StatusText)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_StatusText( 
   /* [in] */ BSTR StatusText)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_ToolBar( 
   /* [retval][out] */ int *Value)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_ToolBar( 
   /* [in] */ int Value)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_MenuBar( 
   /* [retval][out] */ VARIANT_BOOL *Value)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_MenuBar( 
   /* [in] */ VARIANT_BOOL Value)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_FullScreen( 
   /* [retval][out] */ VARIANT_BOOL *pbFullScreen)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_FullScreen( 
   /* [in] */ VARIANT_BOOL bFullScreen)
{
	return E_NOTIMPL;
}

// IWebBrowser2
/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::Navigate2( 
   /* [in] */ VARIANT *URL,
   /* [optional][in] */ VARIANT *Flags,
   /* [optional][in] */ VARIANT *TargetFrameName,
   /* [optional][in] */ VARIANT *PostData,
   /* [optional][in] */ VARIANT *Headers)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::QueryStatusWB( 
   /* [in] */ OLECMDID cmdID,
   /* [retval][out] */ OLECMDF *pcmdf)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::ExecWB( 
   /* [in] */ OLECMDID cmdID,
   /* [in] */ OLECMDEXECOPT cmdexecopt,
   /* [optional][in] */ VARIANT *pvaIn,
   /* [optional][in][out] */ VARIANT *pvaOut)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::ShowBrowserBar( 
   /* [in] */ VARIANT *pvaClsid,
   /* [optional][in] */ VARIANT *pvarShow,
   /* [optional][in] */ VARIANT *pvarSize)
{
	return E_NOTIMPL;
}

/* [bindable][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_ReadyState( 
   /* [out][retval] */ READYSTATE *plReadyState)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Offline( 
   /* [retval][out] */ VARIANT_BOOL *pbOffline)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_Offline( 
   /* [in] */ VARIANT_BOOL bOffline)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Silent( 
   /* [retval][out] */ VARIANT_BOOL *pbSilent)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_Silent( 
   /* [in] */ VARIANT_BOOL bSilent)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_RegisterAsBrowser( 
   /* [retval][out] */ VARIANT_BOOL *pbRegister)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_RegisterAsBrowser( 
   /* [in] */ VARIANT_BOOL bRegister)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_RegisterAsDropTarget( 
   /* [retval][out] */ VARIANT_BOOL *pbRegister)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_RegisterAsDropTarget( 
   /* [in] */ VARIANT_BOOL bRegister)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_TheaterMode( 
   /* [retval][out] */ VARIANT_BOOL *pbRegister)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_TheaterMode( 
   /* [in] */ VARIANT_BOOL bRegister)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_AddressBar( 
   /* [retval][out] */ VARIANT_BOOL *Value)
{
	*Value = VARIANT_TRUE;	// TODO
	return S_OK;
}

/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_AddressBar( 
   /* [in] */ VARIANT_BOOL Value)
{
#if 0
	CComPtr<ILDOMElement> siteElement;
	m_pAddinSite->GetElement
	CComPtr<ILDOMElement> element;
	getElementById(L"id_addressbar", &element);
	if (element)
	{
	}
#endif

	return S_OK;
}

/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::get_Resizable( 
   /* [retval][out] */ VARIANT_BOOL *Value)
{
	return E_NOTIMPL;
}

/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE CLWebBrowser::put_Resizable( 
   /* [in] */ VARIANT_BOOL Value)
{
	return E_NOTIMPL;
}
#endif