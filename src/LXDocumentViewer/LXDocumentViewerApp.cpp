// LXDocumentViewerApp.cpp : Implementation of CLXDocumentViewerApp
#include "stdafx.h"
#include "LXDocumentViewer.h"
#include "LXDocumentViewer2.h"
#include "LXDocumentViewerApp.h"

#include "LWebBrowser.h"

/////////////////////////////////////////////////////////////////////////////
// CLXDocumentViewerApp

int CLXDocumentViewerApp::FinalConstruct()
{
	return 0;
}

STDMETHODIMP CLXDocumentViewerApp::SetSite(ILXAddinSite* pSite)
{
	m_spAddinSite = pSite;

	CComQIPtr<IServiceProvider> sp = m_spAddinSite;
	if (sp)
	{
		CComPtr<IProfferService> ps;
		sp->QueryService(IID_IProfferService, &ps);

		if (ps)
		{
			DWORD cookie;
			ps->ProfferService(IID_IWebBrowserApp, static_cast<IServiceProvider*>(this), &cookie);
		}
	}

	HRESULT hr;

	hr = NewWindow();

#if 0
	if (m_spAddinSite)
	{
		m_spAddinSite->GetFrame(&m_frame);

		TCHAR filename[512];
		GetModuleFileName(_Module.m_hInstResource, filename, 512);

		CComPtr<ILXFrameworkFrame> frame;
		m_spAddinSite->GetFrame(&frame);

		CComPtr<ILXFrameworkApp> app;
		frame->GetApp(&app);

		CComPtr<ILXUIMDIFrameElement> frameelement;
		frame->get_Element(&frameelement);

		CComPtr<ILXUIDocument> appdocument;
		app->get_Document(&appdocument);

		{
			CComPtr<ILXUIMenuElement> menu;
			appdocument->loadMenu(_bstr_t(filename), IDR_MAINFRAME, &menu);

			CComPtr<ILXUIPageElement> page;
			appdocument->createMenuBarPage(L"MenuBar", menu, GetUnknown(), &page);

			frameelement->floatBar(page, 40, 40);
		}

		{
			CComPtr<ILDOMDocument> doc;
			doc.CoCreateInstance(CLSID_LDOMDocument);

			VARIANT_BOOL success;
			doc->load(_variant_t(L"C:\\docviewer_layout.xml"), &success);

			CComPtr<ILDOMElement> documentElement;
			doc->get_documentElement(&documentElement);

			CComPtr<ILDOMNode> toolbar;
			appdocument->importNode(documentElement, VARIANT_TRUE/*deep*/, &toolbar);

			frameelement->dockBar(CComQIPtr<ILXUIPageElement>(toolbar), NULL);

			CComQIPtr<ILDOMEventTarget>(toolbar)->addEventListener(L"click", static_cast<ILDOMEventListener*>(this), VARIANT_FALSE/*bCapture*/);
		}

		{
			CComPtr<ILDOMDocument> doc;
			doc.CoCreateInstance(CLSID_LDOMDocument);

			VARIANT_BOOL success;
			doc->load(_variant_t(L"C:\\docviewer_layout2.xml"), &success);

			CComPtr<ILDOMElement> documentElement;
			doc->get_documentElement(&documentElement);

			CComPtr<ILDOMNode> layout;
			appdocument->importNode(documentElement, VARIANT_TRUE/*deep*/, &layout);

			CComPtr<ILXUIElement> mdiclient;
			frameelement->getMDIClient(&mdiclient);
			if (mdiclient)
			{
				mdiclient->appendChild(layout, NULL);
			}
		}
	}
#endif

	return hr;
}

#if 0
STDMETHODIMP CLXDocumentViewerApp::BindToObjectMoniker(IMoniker* moniker, IBindCtx* bindctx, IUnknown* *pVal)
{
	return S_OK;
}
#endif

HRESULT CLXDocumentViewerApp::NewWindow()
{
	CComObject<CLWebBrowser>* pBrowser;
	CComObject<CLWebBrowser>::CreateInstance(&pBrowser);
	if (pBrowser)
	{
		pBrowser->AddRef();

		pBrowser->Init(this, NULL);
	}

	return S_OK;
}

BEGIN_CMD_MAP(CLXDocumentViewerApp)
// File
	CMD_HANDLER(ID_FILE_OPEN, OnFileOpen)
//	CMD_HANDLER(ID_FILE_OPENURL, OnFileOpenURL)

	CMD_HANDLER(ID_TOOLS_SEARCHFORMEDIAFILES, OnSearchForMedia)

END_CMD_MAP()

#include "LMoviePlayer.h"

LRESULT CLXDocumentViewerApp::OnFileOpen(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	CFileDialog dlg(TRUE/*bOpen*/);

	if (dlg.DoModal() == IDOK)
	{
		_bstr_t pathName = dlg.m_szFileName;

		if (TRUE)
		{
			CComObject<CLMoviePlayer>* pDocument;
			CComObject<CLMoviePlayer>::CreateInstance(&pDocument);
			pDocument->AddRef();

			CComPtr<IMoniker> imkName;

			HRESULT hr;

			CComPtr<IBindCtx> ctx;
			hr = CreateBindCtx(0/*reserved*/, &ctx);
			if (SUCCEEDED(hr))
			{
				hr = CreateURLMoniker(NULL, pathName, &imkName);
				if (SUCCEEDED(hr))
				{
					hr = pDocument->m_filterGraph.CoCreateInstance(CLSID_LFilterGraph);
					if (SUCCEEDED(hr))
					{
						pDocument->m_app = this;

						hr = pDocument->m_filterGraph->AddSourceFilterForMoniker(imkName, ctx, L"", NULL);

						if (SUCCEEDED(hr))
						{
							CComPtr<ILXFrameworkFrame> lxframe;
							m_spAddinSite->GetFrame(&lxframe);

							pDocument->Show(lxframe);

							if (TRUE)
							{
								pDocument->m_filterGraph->Run();
								pDocument->m_cwnd.SetTimer(1, 80);
							}
						}
					}
				}
			}

			//pDocument->NewWindow();
		}
		else
		{
			HRESULT hr;

			CComQIPtr<IHlinkFrame> hlinkFrame = this;//m_app;//m_pUIManager;//gIFrame;

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
			CreateURLMoniker(NULL, pathName, &moniker);
			if (moniker)
			{
				CComPtr<IHlink> hlink;

				hr = HlinkCreateFromMoniker(
					moniker,
					pathName, // pwzLocation
					pathName,	// friendlyName
					NULL,//this,//&hlsite,
					0,//1,	// siteData
					NULL,
					IID_IHlink,
					(void**)&hlink);

				::HlinkNavigate(hlink, hlinkFrame, 0, bindctx, NULL, NULL);
				//hr = hlink->Navigate(0, bindctx, NULL, NULL/*bc*/);
			}
		}
	}
#endif

	return 0;
}

#include "MediaSearchDlg.h"

LRESULT CLXDocumentViewerApp::OnSearchForMedia(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CMediaSearchDlg dlg;
	dlg.m_app = this;

	if (dlg.DoModal() == IDOK)
	{
	}

	return 0;
}

#if 0
// ILCustomizable
STDMETHODIMP CLXDocumentViewerApp::LoadDocument(/*[out,retval]*/ ILDOMDocument **pVal)
{
	CComPtr<ILXUIDocument> document;
	document.CoCreateInstance(CLSID_LXUIDocument);

	VARIANT_BOOL success;
	document->load(_variant_t(_bstr_t(L"C:\\MMStudio\\LXUIDocumentViewer\\LXUIDocumentViewerApp.xml")), &success);

	*pVal = document.Detach();

	return S_OK;
}
#endif