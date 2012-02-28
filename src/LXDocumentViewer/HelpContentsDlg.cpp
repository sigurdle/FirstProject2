// HelpContentsDlg.cpp : Implementation of CHelpContentsDlg
#include "stdafx.h"

#if 0

#include "LXDocumentViewer.h"
#include "LXDocumentViewer2.h"
#include "HelpContentsDlg.h"

//#include "LXFrameworkApp.h"
//#include "LXFrameworkFrame.h"

/////////////////////////////////////////////////////////////////////////////
// CHelpContentsDlg

void CHelpContentsDlg::BuildItem(IUITreeItem* parentItem, ILDOMElement* element)
{
	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node != NULL)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			CComBSTR tagName;
			element->get_tagName(&tagName);

			if (!wcscmp(tagName, L"item"))
			{
				CComBSTR name;
				element->getAttribute(L"name", &name);

				VARIANT_BOOL bHasChildren;
				element->hasChildNodes(&bHasChildren);

				CComPtr<IUITreeItem> newItem;
				m_treeCtl->InsertItem((DWORD)element.p, parentItem, NULL, name, bHasChildren?0: 2, -1, &newItem);
				//m_treeCtl->Expand(pScriptItem->m_TreeItem, TV_EXPAND, NULL);

				BuildItem(newItem, element);	// Recurse
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
}

void CHelpContentsDlg::BuildTree()
{
	m_treeCtl->ResetContent(NULL);

	CComPtr<ILDOMElement> documentElement;
	m_tocDocument->get_documentElement(&documentElement);

	if (documentElement)
	{
		BuildItem(NULL, documentElement);
	}

//	m_treeCtl->InsertItem((DWORD)pItem, NULL, NULL, NULL, 0, 1, &pItem->m_TreeItem);

#if 0
	if (m_viewGroup)
	{
		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

		CComPtr<ILDOMDocument> domdocument;
		edocument->get_DOMDocument(&domdocument);

		CComPtr<ILDOMElement> documentElement;
		domdocument->get_documentElement(&documentElement);

		{
			CItem* pItem = new CItem;
			pItem->m_name = L"Client Scripts";
			m_treeCtl->InsertItem((DWORD)pItem, NULL, NULL, NULL, 0, 1, &pItem->m_TreeItem);
			m_treeCtl->Expand(pItem->m_TreeItem, TV_EXPAND, NULL);

			if (documentElement)
			{
				AddClientScripts(pItem->m_TreeItem, documentElement);
			}
		}
	}
#endif
}

//extern CLXFrameworkApp* gApp;

LRESULT CHelpContentsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->AddEventHandler(this);

//	HWND hwnd = m_hWnd;
	//get_hwnd(&hwnd);

	IUnknown* p;

	CRect rc(0,0,0,0);
	m_axtreeCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axtreeCtl.AttachControl(m_treeCtl, &p);

	m_hIcons = ImageList_LoadBitmap(_Module.m_hInstResource, MAKEINTRESOURCE(IDB_HELPICONS), 16, 0, CLR_NONE);
	m_treeCtl->put_hImageList((DWORD)m_hIcons);

	IDispEventImpl<4, CHelpContentsDlg, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_treeCtl);

//	TCHAR filename[_MAX_PATH];
//	GetModuleFileName(NULL, filename, _countof(filename));

	m_tocDocument.CoCreateInstance(CLSID_LDOMDocument);
	VARIANT_BOOL bsuccess;
	m_tocDocument->load(_variant_t(L"C:\\mmstudio\\extras\\help\\toc.xml"), &bsuccess);

	BuildTree();

	return 0;
}

LRESULT CHelpContentsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->RemoveEventHandler(this);

	IDispEventImpl<4, CHelpContentsDlg, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_treeCtl);
	m_treeCtl.Release();

	m_tocDocument.Release();

	if (m_hIcons)
	{
		ImageList_Destroy(m_hIcons);
		m_hIcons = NULL;
	}

	return 0;
}

LRESULT CHelpContentsDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axtreeCtl.MoveWindow(0, 0, client.right, client.bottom, TRUE);

	return 0;
}

#if 0
STDMETHODIMP CHelpContentsDlg::GetItemText(ULONG itemdata, LONG column, BSTR * pVal)
{
	CItem* pItem = (CItem*)itemdata;
	*pVal = SysAllocString(pItem->m_name);

	return S_OK;
}
#endif

//#include "WebXMLViewGroup.h"	// TODO remove
//#include "SourceView.h"	// TODO remove

void __stdcall CHelpContentsDlg::OnItemClick(IUITreeItem* item)
{
	DWORD itemdata;
	m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

	CComQIPtr<ILDOMElement> element = (IUnknown*)itemdata;

	if (element)
	{
		CComBSTR name;
		element->getAttribute(L"name", &name);

		CComBSTR url;
		element->getAttribute(L"url", &url);

		if (url.Length())
		{
			TCHAR absurl[1024];
			DWORD dwLength = sizeof(absurl);	// bytes instead of characters?
			if (InternetCombineUrl("C:\\mmstudio\\extras\\help\\", _bstr_t(url), absurl, &dwLength, 0))
			{
				HRESULT hr;

				CComQIPtr<IHlinkFrame> hlinkFrame = m_app;//m_pUIManager;//gIFrame;

				CComPtr<IBindCtx> bindctx;
				hr = CreateAsyncBindCtx(NULL, this, NULL, &bindctx);
				//hr = CreateBindCtx(0, &bindctx);

				PSTR rgszTypes[4] =
				{
					"text/html",	// CFSTR_MIME_HTML
					"text/xml",
					"image/svg+xml",
					"text/plain",
				};

				CLSID rgclsID[4];
				rgclsID[0] = CLSID_LHTMLActiveDocument;
				rgclsID[1] = CLSID_LHTMLActiveDocument;
				rgclsID[2] = CLSID_LHTMLActiveDocument;
				rgclsID[3] = CLSID_LHTMLActiveDocument;

				hr = RegisterMediaTypeClass(bindctx, 4, rgszTypes, rgclsID, 0);
				ATLASSERT(SUCCEEDED(hr));

				CComPtr<IMoniker> moniker;
				CreateURLMoniker(NULL, _bstr_t(absurl), &moniker);
				if (moniker)
				{
					CComPtr<IHlink> hlink;

					hr = HlinkCreateFromMoniker(
						moniker,
						url, // pwzLocation
						url,	// friendlyName
						NULL,//this,//&hlsite,
						0,//1,	// siteData
						NULL,
						IID_IHlink,
						(void**)&hlink);

					::HlinkNavigate(hlink, hlinkFrame, 0, bindctx, NULL, NULL);
					//hr = hlink->Navigate(0, bindctx, NULL, NULL/*bc*/);
				}
			}
			else
			{
				MessageBox("Invalid url", "LXDocumentViewer", MB_OK);
			}
		}
	}
}

/// IBindStatusCallback

STDMETHODIMP CHelpContentsDlg::OnStartBinding( 
													/* [in] */ DWORD dwReserved,
													/* [in] */ IBinding __RPC_FAR *pib)
{
	return S_OK;
}

STDMETHODIMP CHelpContentsDlg::GetPriority(/* [out] */ LONG __RPC_FAR *pnPriority)
{
	return S_OK;
}

STDMETHODIMP CHelpContentsDlg::OnLowResource(/* [in] */ DWORD reserved)
{
	return S_OK;
}

STDMETHODIMP CHelpContentsDlg::OnProgress( 
											  /* [in] */ ULONG ulProgress,
											  /* [in] */ ULONG ulProgressMax,
											  /* [in] */ ULONG ulStatusCode,
											  /* [in] */ LPCWSTR szStatusText)
{
	return S_OK;
}

STDMETHODIMP CHelpContentsDlg::OnStopBinding( 
												  /* [in] */ HRESULT hresult,
												  /* [unique][in] */ LPCWSTR szError)
{
	return S_OK;
}

STDMETHODIMP CHelpContentsDlg::GetBindInfo( 
												/* [out] */ DWORD __RPC_FAR *grfBINDF,
												/* [unique][out][in] */ BINDINFO __RPC_FAR *pbindinfo)
{
	DWORD cbSize = pbindinfo->cbSize;        
	memset(pbindinfo,0,cbSize);
	pbindinfo->cbSize = cbSize;

//	*grfBINDF = 0;
	*grfBINDF = 0;//BINDF_ASYNCHRONOUS;	// Default ?

//	*grfBINDF = BINDF_ASYNCHRONOUS;	// Default ?

	return S_OK;
}

STDMETHODIMP CHelpContentsDlg::OnDataAvailable( 
													 /* [in] */ DWORD grfBSCF,
													 /* [in] */ DWORD dwSize,
													 /* [in] */ FORMATETC __RPC_FAR *pformatetc,
													 /* [in] */ STGMEDIUM __RPC_FAR *pstgmed)
{
	return S_OK;
}

//void AddDocument(IUnknown* spUnknown, IActiveCntDocument* *pVal);

STDMETHODIMP CHelpContentsDlg::OnObjectAvailable( 
														/* [in] */ REFIID riid,
														/* [iid_is][in] */ IUnknown __RPC_FAR *punk)
{

	return S_OK;
}

#if 0
STDMETHODIMP CHelpContentsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLViewGroup> viewGroup = object;
	if (viewGroup)
	{
		/*
		if (m_document != NULL)
		{
			IDispEventImpl<2, CHelpContentsDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXFrameworkLib, 1, 0>::DispEventUnadvise(m_document);
		}
		*/

		m_viewGroup = viewGroup;

	//	IDispEventImpl<2, CHelpContentsDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXFrameworkLib, 1, 0>::DispEventAdvise(m_document);

		BuildTree();

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CHelpContentsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
#if 0
	CComQIPtr<IWebXMLDocument> document = object;
	if (document)
	{
		if (document == m_document)
		{
			IDispEventImpl<2, CHelpContentsDlg, &DIID__IWebXMLDocumentEvents, &LIBID_LXFrameworkLib, 1, 0>::DispEventUnadvise(m_document);
			m_document.Release();
		}
	}
#endif
	m_viewGroup.Release();

	return S_OK;
}
#endif

#endif
