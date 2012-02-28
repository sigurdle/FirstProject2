// LXFrameworkApp.cpp : Implementation of CLXFrameworkApp
#include "stdafx.h"
#include "LXFramework.h"
#include "LXFramework2.h"

#include "LXFrameworkApp.h"
#include "LXFrameworkFrame.h"

UINT AFXAPI AfxGetFileName(LPCTSTR lpszPathName, LPTSTR lpszTitle, UINT nMax)
{
	/*
	ASSERT(lpszTitle == NULL ||
		AfxIsValidAddress(lpszTitle, _MAX_FNAME));
	ASSERT(AfxIsValidString(lpszPathName));
	*/

	// always capture the complete file name including extension (if present)
	LPTSTR lpszTemp = (LPTSTR)lpszPathName;
	for (LPCTSTR lpsz = lpszPathName; *lpsz != '\0'; lpsz = _tcsinc(lpsz))
	{
		// remember last directory/drive separator
		if (*lpsz == '\\' || *lpsz == '/' || *lpsz == ':')
			lpszTemp = (LPTSTR)_tcsinc(lpsz);
	}

	// lpszTitle can be NULL which just returns the number of bytes
	if (lpszTitle == NULL)
		return lstrlen(lpszTemp)+1;

	// otherwise copy it into the buffer provided
	lstrcpyn(lpszTitle, lpszTemp, nMax);
	return 0;
}

//////////////////////////////////////////////////

#if 0
typedef HRESULT (*HTMLModalDialogProc)(HWND hParent, BSTR url, VARIANT* pvarArgIn, BSTR pchOptions, VARIANT* pvarArgOut);
typedef HRESULT (*HTMLModelessDialogProc)(HWND hParent, BSTR url, VARIANT* pvarArgIn, BSTR pchOptions);
#endif

CLXFrameworkApp* gApp;

ILXFrameworkApp* gIApp;
//ILXFrameworkFrame* gIFrame;	// TODO remove

inline int bstrlen(WCHAR* p)
{
	if (p == NULL) return 0;
	if (p[0] == 0) return 0;
	return 1;
}

inline int cmpbstr(WCHAR* p1, WCHAR* p2)
{
	if (bstrlen(p1) == 0 && bstrlen(p2) == 0) return 0;
	if (bstrlen(p1) == 0) return -1;	// Not sure
	if (bstrlen(p2) == 0) return 1;	// Not sure

	return wcscmp(p1, p2);
}

ILDOMElement* GetElementByTagNameNS(ILDOMElement* parent, BSTR ns, BSTR tagName, BOOL bDeep/* = TRUE*/)
{
	CComPtr<ILDOMNode>	child;
	parent->get_firstChild(&child);

	while (child != NULL)
	{
		CComQIPtr<ILDOMElement> element = child;
		if (element)
		{
			CComBSTR ens;
			element->get_namespaceURI(&ens);

			if (!cmpbstr(ens, ns))
			{
				CComBSTR etagName;
				element->get_localName(&etagName);
				if (SysStringLen(etagName) == 0)
				{
					etagName.Empty();
					element->get_tagName(&etagName);
				}

				if (!wcscmp(etagName, tagName))
				{
					return element;
				}
			}

		// Recurse
			if (bDeep)
			{
				CComPtr<ILDOMElement> element2 = GetElementByTagNameNS(element, ns, tagName, TRUE);
				if (element2 != NULL)
					return element2;
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	return NULL;
}

extern "C" GUID CATID_LXFrameworkPlugin;

void com_error_Message(_com_error &e)
{
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrMessage(e.ErrorMessage());
	_bstr_t bstrDescription(e.Description());
      
	CUString msg;
	msg.Format("\n\tSource :  %s \n\tMessage : %s\n\tdescription : %s \n ", (LPCSTR)bstrSource, (LPCSTR)bstrMessage, (LPCSTR)bstrDescription);

	MessageBox(NULL, msg, "LXFramework", MB_OK);
}

void ComError(_com_error &e)
{
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());

	CUString msg;
	msg.Format("\n\tSource :  %s \n\tdescription : %s \n ",(LPCSTR)bstrSource,(LPCSTR)bstrDescription);

	MessageBox(NULL, msg, "LXFramework", MB_OK);
}

CArray<CFormatWindow*,CFormatWindow*> m_formatWindows;

#include "FileType.h"

CFormatWindow* RegisterFormatWindow(WCHAR* name)
{
	for (int i = 0; i < m_formatWindows.GetSize(); i++)
	{
		if (!wcscmp(m_formatWindows[i]->m_name, name))
		{
			return m_formatWindows[i];
		}
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CLXFrameworkApp

//#include "ActiveCntDocument.h"

#if 0
// Have on ILXFrameworkApp (or frame)
void AddDocument(IUnknown* spUnknown, IActiveCntDocument* *pVal)
{
	CComObject<CActiveCntDocument>* pDoc;
	CComObject<CActiveCntDocument>::CreateInstance(&pDoc);
	if (pDoc)
	{
		pDoc->AddRef();

		pDoc->m_spUnknown = spUnknown;
		pDoc->m_spOleObject = pDoc->m_spUnknown;

		pDoc->m_spOleObject->SetClientSite(pDoc);

#if 0
		pDoc->Show();
#endif

		gApp->m_documents.Add(pDoc);
	}
}
#endif

int Run(LPTSTR lpstrCmdLine = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	//Sleep(5000);
	//::MessageBox(NULL, "1", "", MB_OK);

	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	//Sleep(5000);
	//::MessageBox(NULL, "2", "", MB_OK);

	int nRet = -1;

	CComObject<CLXFrameworkApp>* app;
	CComObject<CLXFrameworkApp>::CreateInstance(&app);
	if (app)
	{
		app->AddRef();

	//Sleep(5000);
	//::MessageBox(NULL, "2", "", MB_OK);

		gApp = app;
		gIApp = app;

		long result;
		if (SUCCEEDED(app->Run(&result)))
		{
	//	Sleep(5000);
	//	::MessageBox(NULL, "3", "", MB_OK);

			/*
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(5000);
			*/
			/*
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(5000);
			*/

			nRet = theLoop.Run();
			/*
			MSG msg;
			while (GetMessage(&msg, gApp->m_frame->m_hWnd, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			*/
		}
	}

	_Module.RemoveMessageLoop();
	return nRet;
}

int CLXFrameworkApp::FinalConstruct()
{
	HRESULT hr;

	/*
	hr = CComObject<CXSLTDocuments>::CreateInstance(&m_xsltDocuments);
	if (FAILED(hr)) return hr;
	m_xsltDocuments->AddRef();
	*/

//	hr = CPDBrushSettingsImpl<CLXFrameworkApp>::FinalConstruct();
//	if (FAILED(hr)) return hr;

	/*
	{
		CComObject<CImageApp>* pApp;
		CComObject<CImageApp>::CreateInstance(&pApp);
		pApp->AddRef();

		g_pImageApp = pApp;
	}
	*/

	/*
	{
		CComPtr<ICatInformation> catinfo;
		HRESULT hr = S_OK;
 
		hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
			NULL, 
			CLSCTX_INPROC_SERVER, 
			IID_ICatInformation, 
			(LPVOID*)&catinfo);

		if(SUCCEEDED(hr))
		{
			CRegKey clsidkey;
			clsidkey.Open(HKEY_CLASSES_ROOT, "CLSID");

			CATID impl[1];
			impl[0] = CATID_LXFrameworkPlugin;

			CComPtr<IEnumCLSID> enumClsid;
			catinfo->EnumClassesOfCategories(1, impl, 0, NULL, &enumClsid);

			CLSID clsid;
			ULONG fetched;
			while ((enumClsid->Next(1, &clsid, &fetched) == S_OK) && (fetched == 1))
			{
				CComObject<CPluginClass>* pPluginClass;

				CComObject<CPluginClass>::CreateInstance(&pPluginClass);
				if (pPluginClass)
				{
					LPOLESTR clsidstr;
					StringFromCLSID(clsid, &clsidstr);

					CRegKey key;
					key.Open(clsidkey, _bstr_t(clsidstr));

					CoTaskMemFree(clsidstr);

					TCHAR name[256];
					DWORD n = 255;
					key.QueryValue(name, NULL, &n);
					pPluginClass->m_name = name;

					pPluginClass->m_clsid = clsid;
					pPluginClass->AddRef();
					m_plugins.Add(pPluginClass);
				}
			}
		}
	}
*/

	{
		CFormatWindow* pWindow;

		{
			pWindow = new CFormatWindow;

			HDC hDC = GetDC(NULL);

			memset(&pWindow->m_lf, 0, sizeof(pWindow->m_lf));
			strcpy(pWindow->m_lf.lfFaceName, _T("Courier New"));
			pWindow->m_lf.lfHeight = -MulDiv(8, GetDeviceCaps(hDC, LOGPIXELSY), 72);

			ReleaseDC(NULL, hDC);

			pWindow->m_name = L"Source Windows";
			pWindow->RegisterFormatColor(L"Text Selection", -1, -1, COLOR_HIGHLIGHTTEXT, COLOR_HIGHLIGHT);
			pWindow->RegisterFormatColor(L"Text", -1, -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Preprocessing Instruction", RGB(0, 0, 128), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Element Name", RGB(128, 0, 128), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Attribute Name", RGB(192, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Attribute Value", RGB(0, 0, 255), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Tag Delimiter", RGB(128, 0, 128), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Operator", RGB(192, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Comment", RGB(160, 160, 160), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script Keyword", RGB(0, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script String", RGB(192, 0, 0), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script Comment", RGB(0, 192, 0), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);

			m_formatWindows.Add(pWindow);
		}

		{
			pWindow = new CFormatWindow;
			pWindow->m_name = L"XML Grid";

			//HDC hDC = GetDC(NULL);

			HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
			GetObject(hFont, sizeof(pWindow->m_lf), &pWindow->m_lf);
			//memset(&pWindow->m_lf, 0, sizeof(pWindow->m_lf));
			//strcpy(pWindow->m_lf.lfFaceName, _T("Courier New"));
			//pWindow->m_lf.lfHeight = -MulDiv(8, GetDeviceCaps(hDC, LOGPIXELSY), 72);

			//ReleaseDC(NULL, hDC);

			/*
			pWindow->RegisterFormatColor(L"Text Selection", -1, -1, COLOR_HIGHLIGHTTEXT, COLOR_HIGHLIGHT);
			pWindow->RegisterFormatColor(L"Text", -1, -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Element Name", RGB(128, 0, 128), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Attribute Name", RGB(192, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Attribute Value", RGB(0, 0, 255), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Tag Delimiter", RGB(128, 0, 128), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Operator", RGB(192, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Comment", RGB(160, 160, 160), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script Keyword", RGB(0, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script String", RGB(192, 0, 0), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script Comment", RGB(0, 192, 0), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			*/

			m_formatWindows.Add(pWindow);
		}

		{
			pWindow = new CFormatWindow;

			HDC hDC = GetDC(NULL);

			memset(&pWindow->m_lf, 0, sizeof(pWindow->m_lf));
			strcpy(pWindow->m_lf.lfFaceName, _T("Courier New"));
			pWindow->m_lf.lfHeight = -MulDiv(8, GetDeviceCaps(hDC, LOGPIXELSY), 72);

			ReleaseDC(NULL, hDC);

			pWindow->m_name = L"TimeGraph";
			pWindow->RegisterFormatColor(L"Text Selection", -1, -1, COLOR_HIGHLIGHTTEXT, COLOR_HIGHLIGHT);
			pWindow->RegisterFormatColor(L"Text", -1, -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Element Name", RGB(128, 0, 128), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Attribute Name", RGB(192, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Attribute Value", RGB(0, 0, 255), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Tag Delimiter", RGB(128, 0, 128), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Operator", RGB(192, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Comment", RGB(160, 160, 160), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script Keyword", RGB(0, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script String", RGB(192, 0, 0), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script Comment", RGB(0, 192, 0), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);

			m_formatWindows.Add(pWindow);
		}
	}

	return S_OK;
}

void CLXFrameworkApp::FinalRelease()
{
}

STDMETHODIMP CLXFrameworkApp::get_Document(/*[in]*/ ILXUIDocument* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_document;
	(*pVal)->AddRef();
	return S_OK;
}

#include "..\LXUI\LXUIApplication.h"

STDMETHODIMP CLXFrameworkApp::Run(long *result)
{
	USES_CONVERSION;

	{
		// get path of executable
		TCHAR szBuff[_MAX_PATH];
		::GetModuleFileName(NULL/*m_hInstance*/, szBuff, _MAX_PATH);

		m_pszFullExeName = szBuff;

		LPTSTR lpszExt = _tcsrchr(szBuff, '.');
		ATLASSERT(lpszExt != NULL);
		ATLASSERT(*lpszExt == '.');
		*lpszExt = 0;       // no suffix

		TCHAR szExeName[_MAX_PATH];
		//TCHAR szTitle[256];
		// get the exe title from the full path name [no extension]
		AfxGetFileName(szBuff, szExeName, _MAX_PATH);
		//if (m_pszExeName == NULL)
		{
			//BOOL bEnable = AfxEnableMemoryTracking(FALSE);
			m_pszExeName = szExeName; // save non-localized name
		}
	}

#if 0	// Removed this
	CComPtr<ILDOMElement> root;
	m_document->get_documentElement(&root);

	CComObject<CLXFrameworkFrame>* pFrame;
	CComObject<CLXFrameworkFrame>::CreateInstance(&pFrame);
	pFrame->AddRef();
	pFrame->m_app = this;

	CComPtr<ILXUIMDIFrameElement> frame;
//	m_document->createMDIFrame(_variant_t(L"frame"), _variant_t(L"LXFramework"), CComVariant(menu), &frame);
	m_document->getElementById(L"frame", (ILDOMElement**)&frame);

	ATLASSERT(frame);

	pFrame->m_element = frame;

	if (FALSE)
	{
	//	GetModuleFileName(_Module.m_hInst, &filename
		CComPtr<ILXUIMenuElement> menu;
		m_document->loadMenu(_bstr_t(m_pszFullExeName), IDR_MAINFRAME, &menu);
		//menu->setAttribute(L"id", L"frame_menu");

		CComPtr<ILXUIPageElement> page;
		m_document->createMenuBarPage(L"MenuBar", menu, pFrame->GetUnknown(), &page);

		frame->dockBar(page, NULL);
	}
	else

//	frame->appendChild(menu, NULL);

	/*
	frame->setAttribute(L"x", L"0");
	frame->setAttribute(L"y", L"0");
	frame->setAttribute(L"width", L"100%");
	frame->setAttribute(L"height", L"100%");
	*/

	{
		CComQIPtr<ILDOMEventTarget> eventTarget = frame;
		eventTarget->addEventListener(L"command", static_cast<ILDOMEventListener*>(pFrame), VARIANT_FALSE);
	//	eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)pFrame, VARIANT_TRUE);
	}
#endif

//	root->appendChild(frame, NULL);

	/*
			MessageBeep(-1);
			Sleep(50);
			MessageBeep(-1);
			Sleep(50);
			*/

#if 0
	EnableShellOpen();	// DDE
#endif

	//::MessageBox(NULL, ::GetCommandLine(), "", MB_OK);

	LPCTSTR chromeParam = NULL;

	{
		for (int i = 1; i < __argc; i++)
		{
			LPCTSTR pszParam = __targv[i];

			if (pszParam[0] == '-' || pszParam[0] == '/')
			{
				pszParam++;
				if (!strcmp(pszParam, "chrome"))
				{
					i++;
					chromeParam = __targv[i];
				}
			}
			else
			{
				//MessageBox(NULL, pszParam, "", MB_OK);

				ATLASSERT(0);
				VARIANT_BOOL bsuccess;
				//OpenDocument(A2W(pszParam), &bsuccess);
			}
			/*
			BOOL bFlag = FALSE;
			BOOL bLast = ((i + 1) == __argc);
			if (pszParam[0] == '-' || pszParam[0] == '/')
			{
				// remove flag specifier
				bFlag = TRUE;
				++pszParam;
			}
			rCmdInfo.ParseParam(pszParam, bFlag, bLast);
			*/
		}
	}

	if (chromeParam)
	{
		CComObject<CLXUIApplication>* pApp;
		CComObject<CLXUIApplication>::CreateInstance(&pApp);
		pApp->AddRef();

#if 0
		HRESULT hr = m_document.CoCreateInstance(CLSID_LXUIDocument);
		if (FAILED(hr))	// TODO, show message
			return -1;

		VARIANT_BOOL success;
		m_document->load(/*_bstr_t(m_pszFullExeName),*/ _variant_t(_bstr_t(chromeParam)), &success);
		if (success)
#endif
		{
#if 0
			CComPtr<ILDOMElement> documentElement;
			m_document->get_documentElement(&documentElement);

			{
				CComPtr<ILDOMElement> shellElement = ::GetElementByTagNameNS(documentElement, L"http://www.lerstad.com/2004/lxui", L"shell", FALSE);
				if (shellElement)
				{
					/*
					CComPtr<ILDOMElement> iconElement = ::GetElementByTagNameNS(shellElement, L"http://www.lerstad.com/2004/lxui", L"defaulticon", FALSE);
					if (iconElement)
					{
					}
					*/

					CComPtr<ILDOMElement> fileClassesElement = ::GetElementByTagNameNS(shellElement, L"http://www.lerstad.com/2004/lxui", L"fileclasses", FALSE);
					if (fileClassesElement)
					{
						CComPtr<ILDOMNode> node;
						fileClassesElement->get_firstChild(&node);
						while (node)
						{
							CComQIPtr<ILXUIFileClassElement> fileClassElement = node;
							if (fileClassElement)
							{
								fileClassElement->registerFileClass(_bstr_t(m_pszFullExeName));
							}
							CComPtr<ILDOMNode> nextSibling;
							node->get_nextSibling(&nextSibling);
							node = nextSibling;
						}
					}
				}
			}
#endif
			CComObject<CLXFrameworkAddinSite>::CreateInstance(&m_pAddinSite);
			m_pAddinSite->AddRef();

			//m_pAddinSite->m_p.CoCreateInstance(L"LXDocumentViewer.LXDocumentViewerApp");
			m_pAddinSite->m_p.CoCreateInstance(L"LXMLEditor.LXMLEditorApp");

#if 0	// Test remove this
			//CComPtr<ILXUIDocument> document;
			m_pAddinSite->m_document.CoCreateInstance(CLSID_LXUIDocument);

			VARIANT_BOOL success;
			m_pAddinSite->m_document->loadApp(_bstr_t(m_pszFullExeName), _variant_t(_bstr_t(L"C:\\startup.lxapp")), &success);
			//m_document->loadApp(_bstr_t(m_pszFullExeName), _variant_t(_bstr_t(chromeParam)), &success);

			CComQIPtr<ILDOMDocumentView> documentView = m_pAddinSite->m_document;
			documentView->createPresentation(&m_pAddinSite->m_view);
#endif

			m_pAddinSite->m_p->SetSite(m_pAddinSite);

#if 0
			CComQIPtr<ILDOMDocumentView> documentView = m_document;
			documentView->createPresentation(&m_view);

			{
				CComPtr<ILXUIDocument> document;
				document.CoCreateInstance(CLSID_LXUIDocument);

				VARIANT_BOOL success;
				document->load(_variant_t(_bstr_t(L"C:\\dlg_customize.xml")), &success);

				CComPtr<ILDOMElement> element;
				document->get_documentElement(&element);

				CComQIPtr<ILXUIWindowElement> window = element;

				//window->doModal();
			}

			/*
			{
				CComBSTR xml;
				m_document->saveXML(CComVariant(), &xml);

				MessageBox(NULL, _bstr_t(xml), "", MB_OK);
			}
			*/
#endif
		}
#if 0
		else
		{
			MessageBox(NULL, "Failed to load chrome", "LXViewer", MB_OK);
		}
#endif
	}

//	m_frame->ActivateObject(NULL, m_xsltDocuments);	// ??

	*result = 0;

	return S_OK;
}

// IProfferService
STDMETHODIMP CLXFrameworkApp::ProfferService(/* [in] */ REFGUID rguidService, /* [in] */ IServiceProvider *psp, /* [out] */ DWORD *pdwCookie)
{
	CService* pService = new CService;
	pService->m_cookie = ++m_dwServiceCookie;
	pService->m_guid = rguidService;
	pService->m_sp = psp;	// This AddRefs

	m_services.Add(pService);

	return S_OK;
}

STDMETHODIMP CLXFrameworkApp::RevokeService(/* [in] */ DWORD dwCookie)
{
	for (int i = 0; i < m_services.GetSize(); i++)
	{
		if (m_services[i]->m_cookie == dwCookie)
		{
			delete m_services[i];
			m_services.RemoveAt(i);
			return S_OK;
		}
	}

	ATLASSERT(0);
	return E_FAIL;
}

#if 0
void CLXFrameworkApp::EnableShellOpen()
{

//	GetModuleFileName(NULL, m_pszExeName.GetBuffer(512), 512);
//	m_pszExeName.ReleaseBuffer();

//	::MessageBox(NULL, m_pszExeName, "", MB_OK);

	ATLASSERT(m_atomApp == NULL && m_atomSystemTopic == NULL); // do once
	m_atomApp = ::GlobalAddAtom(m_pszExeName);
	m_atomSystemTopic = ::GlobalAddAtom(_T("system"));
}

BOOL CLXFrameworkApp::OnDDECommand(LPTSTR lpszCommand)
{
	USES_CONVERSION;

	CString strCommand = lpszCommand;
//	CDocument* pDoc = NULL;

	// open format is "[open("%s")]" - no whitespace allowed, one per line
	// print format is "[print("%s")]" - no whitespace allowed, one per line
	// print to format is "[printto("%s","%s","%s","%s")]" - no whitespace allowed, one per line
	/*
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileDDE;
	*/

	if (strCommand.Left(7) == _T("[open(\""))
	{
	//	cmdInfo.m_nShellCommand = CCommandLineInfo::FileOpen;
		strCommand = strCommand.Right(strCommand.GetLength() - 7);
	}
#if 0
	else if (strCommand.Left(8) == _T("[print(\""))
	{
		cmdInfo.m_nShellCommand = CCommandLineInfo::FilePrint;
		strCommand = strCommand.Right(strCommand.GetLength() - 8);
	}
	else if (strCommand.Left(10) == _T("[printto(\""))
	{
		cmdInfo.m_nShellCommand = CCommandLineInfo::FilePrintTo;\
		strCommand = strCommand.Right(strCommand.GetLength() - 10);
	}
	else
		return FALSE; // not a command we handle
#endif

	int i = strCommand.Find('"');
	if (i == -1)
		return FALSE; // illegally terminated

	CString/*cmdInfo.*/ m_strFileName = strCommand.Left(i);
	strCommand = strCommand.Right(strCommand.GetLength() - i);

#if 0
	CCommandLineInfo* pOldInfo = NULL;
#endif
	BOOL bRetVal = TRUE;

	// If we were started up for DDE retrieve the Show state
#if 0
	if (AfxGetApp()->m_pCmdInfo != NULL)
	{
		AfxGetApp()->m_nCmdShow = (int)AfxGetApp()->m_pCmdInfo;
		AfxGetApp()->m_pCmdInfo = &cmdInfo;
	}
	else
		pOldInfo = AfxGetApp()->m_pCmdInfo;

	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileOpen)
#endif
	{
		// show the application window
		//CWnd* pMainWnd = AfxGetApp()->m_pMainWnd;
		int nCmdShow = SW_SHOW;//AfxGetApp()->m_nCmdShow;
		/*
		if (nCmdShow == -1 || nCmdShow == SW_SHOWNORMAL)
		{
			if (pMainWnd->IsIconic())
				nCmdShow = SW_RESTORE;
			else
				nCmdShow = SW_SHOW;
		}
		*/
		ATLASSERT(0);
#if 0
		m_frame->ShowWindow(nCmdShow);
		if (nCmdShow != SW_MINIMIZE)
			::SetForegroundWindow(m_frame->m_hWnd);

		// then open the document
	//	AfxGetApp()->OpenDocumentFile(cmdInfo.m_strFileName);
	//	ATLASSERT(0);
	//	VARIANT_BOOL bsuccess;
	//	OpenDocument(A2W(m_strFileName), &bsuccess);

		m_frame->OpenFramework(m_strFileName);
#endif

		// user is now "in control" of the application
#if 0
		if (!AfxOleGetUserCtrl())
			AfxOleSetUserCtrl(TRUE);
#endif

		// next time, show the window as default
#if 0
		AfxGetApp()->m_nCmdShow = -1;
#endif
		goto RestoreAndReturn;
	}

#if 0
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FilePrintTo)
	{
		if (strCommand.Left(3) != _T("\",\""))
		{
			bRetVal = FALSE;
			goto RestoreAndReturn;
		}
		else
		{
			strCommand = strCommand.Right(strCommand.GetLength() - 3);
			i = strCommand.Find('"');
			if (i == -1)
			{
				bRetVal = FALSE;
				goto RestoreAndReturn;
			}
			else
			{
				cmdInfo.m_strPrinterName = strCommand.Left(i);
				strCommand = strCommand.Right(strCommand.GetLength() - i);
			}
		}

		if (strCommand.Left(3) != _T("\",\""))
		{
			bRetVal = FALSE;
			goto RestoreAndReturn;
		}
		else
		{
			strCommand = strCommand.Right(strCommand.GetLength() - 3);
			i = strCommand.Find('"');
			if (i == -1)
			{
				bRetVal = FALSE;
				goto RestoreAndReturn;
			}
			else
			{
				cmdInfo.m_strDriverName = strCommand.Left(i);
				strCommand = strCommand.Right(strCommand.GetLength() - i);
			}
		}

		if (strCommand.Left(3) != _T("\",\""))
		{
			bRetVal = FALSE;
			goto RestoreAndReturn;
		}
		else
		{
			strCommand = strCommand.Right(strCommand.GetLength() - 3);
			i = strCommand.Find('"');
			if (i == -1)
			{
				bRetVal = FALSE;
				goto RestoreAndReturn;
			}
			else
			{
				cmdInfo.m_strPortName = strCommand.Left(i);
				strCommand = strCommand.Right(strCommand.GetLength() - i);
			}
		}
	}
#endif

#if 0
	// get document count before opening it
	int nOldCount; nOldCount = GetDocumentCount();

	// open the document, then print it.
	pDoc = AfxGetApp()->OpenDocumentFile(cmdInfo.m_strFileName);
	AfxGetApp()->m_pCmdInfo = &cmdInfo;
	AfxGetApp()->m_pMainWnd->SendMessage(WM_COMMAND, ID_FILE_PRINT_DIRECT);
	AfxGetApp()->m_pCmdInfo = NULL;

	// close the document if it wasn't open previously (based on doc count)
	if (GetDocumentCount() > nOldCount)
		pDoc->OnCloseDocument();

	 // if the app was only started to process this command then close
	 if (!AfxOleGetUserCtrl())
		AfxGetApp()->m_pMainWnd->PostMessage(WM_CLOSE);
#endif

RestoreAndReturn:
//	AfxGetApp()->m_pCmdInfo = pOldInfo;
	return bRetVal;
}
#endif

BEGIN_CMD_MAP(CLXFrameworkApp)

// File
//	CMD_HANDLER(ID_FILE_NEW, OnFileNew)

//	CMD_HANDLER(ID_FILE_NEW_NEWSITEM, OnNewNewsItem)

// Edit
//	CMD_HANDLER(ID_FILE_CUSTOMIZE, OnCustomize)
	CMD_HANDLER(ID_EDIT_OPTIONS, OnOptions)


//	CMD_HANDLER(ID_FILES_PREFS, OnFilePrefs)

// Edit
//	CMD_HANDLER(ID_EDIT_EMPTYCLIPBOARD, OnEditEmptyClipboard)
//	CMD_UPDATE(ID_EDIT_EMPTYCLIPBOARD, OnEditEmptyClipboardUpdate)

// Help
//	CMD_HANDLER(ID_HELP_TOPICS, OnHelp)
	CMD_HANDLER(ID_APP_ABOUT, OnAbout)
END_CMD_MAP()

#include "AboutDlg.h"

LRESULT CLXFrameworkApp::OnHelp(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	HELPLib::IHelpFramePtr help;
	help.CreateInstance("Help.HelpFrame");

	help->ShowHelp("C:\\mmsx\\2DAnimator\\Help\\TOC.xml");
	help->AddRef();	// ??
#endif

	return 0;
}

LRESULT CLXFrameworkApp::OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CAboutDlg dlg;
	dlg.DoModal();

	return 0;
}

#if 0
LRESULT CLXFrameworkApp::OnFilePrefs(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HINSTANCE hLib = LoadLibrary("C:\\mmsx\\mmstudioplugins\\DOMCOREMOD.dll");
	if (hLib)
	{
		HTMLModalDialogProc HTMLModalDialog = (HTMLModalDialogProc)GetProcAddress(hLib, "HTMLModalDialog");
		if (HTMLModalDialog)
		{
			_variant_t arg;// = (IDispatch*)m_uiManager;

			_variant_t result;
			HTMLModalDialog(NULL, L"C:\\MMStudio\\app_prefs.html", &arg, L"", &result);
		}
		else
		{
			MessageBox(NULL, "Couldn't find proc", "LXFramework", MB_OK);
		}

		FreeLibrary(hLib);
	}
	else
	{
		MessageBox(NULL, "Couldn't load library", "LXFramework", MB_OK);
	}

	return 0;
}
#endif

#if 0
#import "..\UICustomizeMod\UICustomizeMod.tlb"

LRESULT CLXFrameworkApp::OnCustomize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	UICUSTOMIZEMODLib::IUICustomizePtr	customize;
	if (SUCCEEDED(customize.CreateInstance(L"UICustomizeMod.UICustomize")))
	{
		CComPtr<IUIManager> uiManager = m_frame;

		customize->Show(uiManager, (long)NULL);
	}
	else
	{
		MessageBox(NULL, "Couldn' load Customize object", "PageDesigner", MB_OK);
	}

	return 0;
}
#endif

//#include "PrefsTabsDlg.h"
//#include "PrefsFormatDlg.h"
#include "FileTypesDlg.h"

LRESULT CLXFrameworkApp::OnOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CPropertySheet sheet("Options", 0);
	sheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;

//	CPrefsTabsDlg	tabs;
//	tabs.m_tabSize = m_tabSize;

	//CPrefsFormatDlg	format;
	//tabs.m_tabSize = m_tabSize;

	CFileTypesDlg	filetypesdlg;
	{
		CFileTypes* pFileTypes = new CFileTypes;

		{
			CFileType* pFileType = new CFileType;
			pFileType->m_id = "XHTML";
			pFileType->m_descr = "XHTML";
			pFileType->AddFileExtension(".xht");
			pFileType->AddFileExtension(".xhtm");
			pFileType->AddFileExtension(".xhtml");
			pFileTypes->m_fileTypes.Add(pFileType);
		}

		{
			CFileType* pFileType = new CFileType;
			pFileType->m_id = "SVG";
			pFileType->m_descr = "SVG";
			pFileType->AddFileExtension(".svg");
			pFileTypes->m_fileTypes.Add(pFileType);
		}

		{
			CFileType* pFileType = new CFileType;
			pFileType->m_id = "SMIL";
			pFileType->m_descr = "SMIL";
			pFileType->AddFileExtension(".smi");
			pFileType->AddFileExtension(".smil");
			pFileTypes->m_fileTypes.Add(pFileType);
		}

		{
			CFileType* pFileType = new CFileType;
			pFileType->m_id = "XML";
			pFileType->m_descr = "XML";
			pFileType->AddFileExtension(".xml");
			pFileTypes->m_fileTypes.Add(pFileType);
		}

		{
			CFileType* pFileType = new CFileType;
			pFileType->m_id = "NITF";
			pFileType->m_descr = "NITF";
			pFileType->AddFileExtension(".nitf");
			pFileTypes->m_fileTypes.Add(pFileType);
		}

		{
			CFileType* pFileType = new CFileType;
			pFileType->m_id = "DTD";
			pFileType->m_descr = "DTD";
			pFileType->AddFileExtension(".dtd");
			pFileType->AddFileExtension(".ent");
			pFileTypes->m_fileTypes.Add(pFileType);
		}

		{
			CFileType* pFileType = new CFileType;
			pFileType->m_id = "JPEG";
			pFileType->m_descr = "JPEG Image";
			pFileType->AddFileExtension(".jpg");
			pFileType->AddFileExtension(".jpeg");
			pFileType->AddFileExtension(".jfif");
			pFileTypes->m_fileTypes.Add(pFileType);
		}

		{
			CFileType* pFileType = new CFileType;
			pFileType->m_id = "GIF";
			pFileType->m_descr = "GIF Image";
			pFileType->AddFileExtension(".gif");
			pFileTypes->m_fileTypes.Add(pFileType);
		}

		{
			CFileType* pFileType = new CFileType;
			pFileType->m_id = "TIFF";
			pFileType->m_descr = "TIFF Image";
			pFileType->AddFileExtension(".tif");
			pFileType->AddFileExtension(".tiff");
			pFileTypes->m_fileTypes.Add(pFileType);
		}

		{
			CFileType* pFileType = new CFileType;
			pFileType->m_id = "AIFF";
			pFileType->m_descr = "AIFF";
			pFileType->AddFileExtension(".aif");
			pFileType->AddFileExtension(".aiff");
			pFileTypes->m_fileTypes.Add(pFileType);
		}

		pFileTypes->UpdateFromRegistry();

		filetypesdlg.m_fileTypes = pFileTypes;

	}
//	exts.m_app = this;

//	brush.m_brushSettings = this;
//	sheet.AddPage(tabs);
//	sheet.AddPage(format);
	sheet.AddPage(filetypesdlg);

	if (sheet.DoModal() == IDOK)
	{
//		m_tabSize = tabs.m_tabSize;

		TCHAR szPath[_MAX_PATH];

		/*
		SHGetFolderPath(
			NULL,
			CSIDL_LOCAL_APPDATA ,// nFolder,
			NULL,//HANDLE hToken,
			0,//DWORD dwFlags,
			szPath);

		MessageBox(NULL, szPath, "", MB_OK);
		*/

		filetypesdlg.m_fileTypes->UpdateToRegistry();

		Fire_OnPrefsChange();
	}

	return 0;
}

#if 0

STDMETHODIMP CLXFrameworkApp::AddTool(/*[in]*/ IPluginClass* self, /*[in]*/ ISVGToolFactory* factory, /*[in]*/ long toolId, /*[in]*/ BSTR name)
{
	CTool* pTool = new CTool;
	pTool->m_id = toolId;

	factory->FindTool(pTool->m_id, &pTool->m_tool);
	if (pTool->m_tool)
	{
		CComQIPtr<ICommandGroup> group;
		m_frame->CreateCommandGroup(L"SVG Tools", &group);

		m_frame->AddCommandID(pTool->m_id, name, group, NULL);

		m_tools.Add(pTool);
	}

	return S_OK;
}

STDMETHODIMP CLXFrameworkApp::RemoveTool(/*[in]*/ IPluginClass* self, /*[in]*/ long toolId)
{
	return S_OK;
}

STDMETHODIMP CLXFrameworkApp::GetToolID(/*[in]*/ ISVGTool* tool, /*[out,retval]*/ long *pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	if (tool == NULL)
	{
		*pVal = 0;
		return S_OK;
	}

	for (int i = 0; i < m_tools.GetSize(); i++)
	{
		if (m_tools[i]->m_tool == tool)
		{
			*pVal = m_tools[i]->m_id;
			return S_OK;
		}
	}

	*pVal = NULL;
	ATLASSERT(0);
	return S_OK;
}

STDMETHODIMP CLXFrameworkApp::GetActiveTool(VARIANT_BOOL bSelection, ISVGTool **pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = NULL;

	if (bSelection)
	{
		if (m_pActiveSelectionTool)
			*pVal = m_pActiveSelectionTool->m_tool;
	}
	else
	{
		if (m_pActiveTool)
			*pVal = m_pActiveTool->m_tool;
	}

	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}
#endif

/*
STDMETHODIMP CLXFrameworkApp::get_ActiveDocument(IActiveCntDocument **pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_ActiveDocument;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}
*/