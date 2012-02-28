// PageDesignerApp.cpp : Implementation of CPageDesignerApp
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PageDesignerApp.h"
#include "PageDesignerFrame.h"

#include "PDDocument.h"
#include "PDSwatches.h"
#include "PDBrush.h"

//#import "..\Help\Help.tlb"

CPageDesignerApp* gApp;
IPageDesignerApp* gIApp;
IUIFrame* gIFrame;

/*
class CMyIdleHandler : public CIdleHandler
{
public:
	virtual BOOL OnIdle()
	{
		return FALSE;
	}
};
*/

/////////////////////////////////////////////////////////////////////////////
// CPageDesignerApp

int Run(bool bAutomation, LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CComObject<CPageDesignerApp>* app;
	CComObject<CPageDesignerApp>::CreateInstance(&app);
	app->AddRef();
	gApp = app;
	gIApp = app;

	int nRet;

	if (bAutomation)
	{
		CMessageLoop theLoop;
		_Module.AddMessageLoop(&theLoop);	// ??

		nRet = theLoop.Run();

		_Module.RemoveMessageLoop();	// ??
	}
	else
	{
		CMessageLoop theLoop;
		_Module.AddMessageLoop(&theLoop);

		long result;
		app->Run(&result);

		_Module.Lock();

		nRet = theLoop.Run();

		_Module.RemoveMessageLoop();
	}

	app->Release();

	return nRet;
}

#include "PDColor.h"
#include "PDSwatchNone.h"
#include "PDSwatchColor.h"

// {8001A204-F8A9-4773-815B-B9584F2C20B7}
extern "C" GUID CATID_PageDesignerEffects;

int CPageDesignerApp::FinalConstruct()
{
	HRESULT hr;

	hr = CComObject<CPDSwatches>::CreateInstance(&m_swatches);
	if (FAILED(hr)) return hr;
	m_swatches->AddRef();

	// Default swatches
	{
		{
			CComObject<CPDSwatchNone>* pSwatch;
			hr = CComObject<CPDSwatchNone>::CreateInstance(&pSwatch);
			if (FAILED(hr)) return hr;

		//	pSwatch->m_canEdit = VARIANT_FALSE;
		//	pSwatch->m_canDelete = VARIANT_FALSE;

			m_swatches->appendSwatch(pSwatch);
		}

		{
			CComObject<CPDSwatchColor>* pSwatch;

			CComObject<CPDSwatchColor>::CreateInstance(&pSwatch);
			if (pSwatch)
			{
				pSwatch->m_name = "Red";
				pSwatch->m_color->m_colorMode = COLORMODE_RGB;
				pSwatch->m_color->m_channel[0] = 255;
				pSwatch->m_color->m_channel[1] = 0;
				pSwatch->m_color->m_channel[2] = 0;

				m_swatches->appendSwatch(pSwatch);
			}

			CComObject<CPDSwatchColor>::CreateInstance(&pSwatch);
			if (pSwatch)
			{
				pSwatch->m_name = "Green";
				pSwatch->m_color->m_colorMode = COLORMODE_RGB;
				pSwatch->m_color->m_channel[0] = 0;
				pSwatch->m_color->m_channel[1] = 255;
				pSwatch->m_color->m_channel[2] = 0;

				m_swatches->appendSwatch(pSwatch);
			}

			CComObject<CPDSwatchColor>::CreateInstance(&pSwatch);
			if (pSwatch)
			{
				pSwatch->m_name = "Blue";
				pSwatch->m_color->m_colorMode = COLORMODE_RGB;
				pSwatch->m_color->m_channel[0] = 0;
				pSwatch->m_color->m_channel[1] = 0;
				pSwatch->m_color->m_channel[2] = 255;

				m_swatches->appendSwatch(pSwatch);
			}
		}
	}
/*
	hr = CComObject<CPDBrush>::CreateInstance(&m_strokeBrush);
	if (FAILED(hr)) return hr;
	m_strokeBrush->AddRef();

	hr = CComObject<CPDBrush>::CreateInstance(&m_fillBrush);
	if (FAILED(hr)) return hr;
	m_fillBrush->AddRef();

	{
		CComPtr<IPDBrush> brush = m_strokeBrush;

		CComPtr<IPDGradient> gradient;
		brush->setGradient(&gradient);

		CComPtr<IPDGradientStop> stop0;
		gradient->createStop(&stop0);
		stop0->put_offset(0);
		stop0->setColorRGB(0, 0, 0);

		CComPtr<IPDGradientStop> stop1;
		gradient->createStop(&stop1);
		stop1->put_offset(1);
		stop1->setColorRGB(255, 255, 255);

		gradient->append(stop0);
		gradient->append(stop1);
	}

	{
		CComPtr<IPDBrush> brush = m_fillBrush;

		CComPtr<IPDGradient> gradient;
		brush->setGradient(&gradient);

		CComPtr<IPDGradientStop> stop0;
		gradient->createStop(&stop0);
		stop0->put_offset(0);
		stop0->setColorRGB(0, 0, 0);

		CComPtr<IPDGradientStop> stop1;
		gradient->createStop(&stop1);
		stop1->put_offset(1);
		stop1->setColorRGB(255, 255, 255);

		gradient->append(stop0);
		gradient->append(stop1);
	}

	{
		CComPtr<IPDColor> color;
		m_strokeBrush->setColor(&color);
		color->setRGB(0, 0, 0);	// Default stroke brush
	}

	{
		CComPtr<IPDColor> color;
		m_fillBrush->setColor(&color);
		color->setRGB(255, 255, 255);	// Default fill brush
	}
*/
	if (TRUE)
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
			impl[0] = CATID_PageDesignerEffects;

			CComPtr<IEnumCLSID> enumClsid;
			catinfo->EnumClassesOfCategories(1, impl, 0, NULL, &enumClsid);

			CLSID clsid;
			ULONG fetched;
			while ((enumClsid->Next(1, &clsid, &fetched) == S_OK) && (fetched == 1))
			{
				CComObject<CPluginFilterClass>* pPluginFilterClass;

				CComObject<CPluginFilterClass>::CreateInstance(&pPluginFilterClass);
				if (pPluginFilterClass)
				{
					LPOLESTR clsidstr;
					StringFromCLSID(clsid, &clsidstr);

					CRegKey key;
					key.Open(clsidkey, _bstr_t(clsidstr));

					CoTaskMemFree(clsidstr);

					TCHAR name[256];
					DWORD n = 255;
					key.QueryValue(name, NULL, &n);
					pPluginFilterClass->m_name = name;

					pPluginFilterClass->m_clsid = clsid;
					pPluginFilterClass->AddRef();
					m_pluginFilters.Add(pPluginFilterClass);
				}
			}
		}
	}
	else
	{
		CComObject<CPluginFilterClass>* pPluginFilterClass;

		CComObject<CPluginFilterClass>::CreateInstance(&pPluginFilterClass);
		if (pPluginFilterClass)
		{
			pPluginFilterClass->m_name = L"Composite";
			pPluginFilterClass->m_clsid = CLSID_FEComposite;
			pPluginFilterClass->AddRef();
			m_pluginFilters.Add(pPluginFilterClass);
		}

		CComObject<CPluginFilterClass>::CreateInstance(&pPluginFilterClass);
		if (pPluginFilterClass)
		{
			pPluginFilterClass->m_name = L"Offset";
			pPluginFilterClass->m_clsid = CLSID_FEOffset;
			pPluginFilterClass->AddRef();
			m_pluginFilters.Add(pPluginFilterClass);
		}

		CComObject<CPluginFilterClass>::CreateInstance(&pPluginFilterClass);
		if (pPluginFilterClass)
		{
			pPluginFilterClass->m_name = L"Gaussian Blur";
			pPluginFilterClass->m_clsid = CLSID_FEGaussianBlur;
			pPluginFilterClass->AddRef();
			m_pluginFilters.Add(pPluginFilterClass);
		}

		CComObject<CPluginFilterClass>::CreateInstance(&pPluginFilterClass);
		if (pPluginFilterClass)
		{
			pPluginFilterClass->m_name = L"Free Transform";
			pPluginFilterClass->m_clsid = CLSID_FEFreeTransform;
			pPluginFilterClass->AddRef();
			m_pluginFilters.Add(pPluginFilterClass);
		}
	}

	return S_OK;
}

void CPageDesignerApp::FinalRelease()
{
/*
	m_strokeBrush->Release();
	m_strokeBrush = NULL;

	m_fillBrush->Release();
	m_fillBrush = NULL;
*/
	if (m_swatches)
	{
		m_swatches->Release();
		m_swatches = NULL;
	}

	if (m_frame)
	{
		m_frame->Release();
		m_frame = NULL;
	}
}

STDMETHODIMP CPageDesignerApp::get_swatches(IPDSwatches **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_swatches;
	(*pVal)->AddRef();

	return S_OK;
}

/*
STDMETHODIMP CPageDesignerApp::get_strokeBrush(IPDBrush **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_strokeBrush;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPageDesignerApp::get_fillBrush(IPDBrush **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_fillBrush;
	(*pVal)->AddRef();
	return S_OK;
}
*/

STDMETHODIMP CPageDesignerApp::Run(long *result)
{
	CComObject<CPageDesignerFrame>::CreateInstance(&m_frame);
	m_frame->AddRef();

	gIFrame = m_frame;

	if (m_frame->CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	m_frame->ShowWindow(SW_SHOW/*nCmdShow*/);

	CComQIPtr<IUIManager> uiManager = m_frame;
/*
	CComPtr<IUnknown> pThis;
	QueryInterface(IID_IUnknown, (void**)&pThis);
*/
	uiManager->ActivateObject(NULL, GetUnknown());

	*result = 0;

	return S_OK;
}

STDMETHODIMP CPageDesignerApp::get_frame(IPageDesignerFrame **pVal)
{
	*pVal = m_frame;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CPageDesignerApp::get_uiManager(IUnknown **pVal)
{
	ATLASSERT(0);
/*
	*pVal = m_frame;//uiManager;
	(*pVal)->AddRef();
*/
	return S_OK;
}

STDMETHODIMP CPageDesignerApp::OpenDocument(BSTR pathName, VARIANT_BOOL *success)
{
#if 0
	TCHAR ext[512];
	_splitpath(_bstr_t(pathName), NULL, NULL, NULL, ext);

	CComQIPtr<IWebDocument> document;
	
	if (
		!stricmp(ext, ".htm") ||
		!stricmp(ext, ".html") ||
		!stricmp(ext, ".shtml") ||
		!stricmp(ext, ".asp") ||

		!stricmp(ext, ".svg") ||

		!stricmp(ext, ".smil") ||
		!stricmp(ext, ".smi") ||

		!stricmp(ext, ".xml") ||
		!stricmp(ext, ".xsd")/* ||

		!stricmp(ext, ".wmf") ||
		!stricmp(ext, ".emf")*/)
	{
		document.CoCreateInstance(CLSID_ESvgDocument);
	}
	else if (!stricmp(ext, ".dtd"))
	{
		document.CoCreateInstance(CLSID_DTDDocument);
	}
	else if (
		!stricmp(ext, ".js") ||
		!stricmp(ext, ".vbs"))
	{
		document.CoCreateInstance(CLSID_ExtScriptDocument);
	}
/*
	else if (!stricmp(ext, ".css"))
	{
	//	pDocument = new CCSSDocument;
	}
*/
	else
	{
		document.CoCreateInstance(CLSID_TextDocument);
	}

	if (document != NULL)
	{
		CComQIPtr<IPersistFile> ifile = document;
		if (ifile != NULL)
		{
			HRESULT hr = ifile->Load(pathName, STGM_READ);
			if (SUCCEEDED(hr))
			{
				document->ShowViews();

				m_frame->ActivateObject(document);
			}
			else
			{
				MessageBox(GetMainHwnd(), "Error loading file", "WebEditor", MB_OK);
			}
		}
		else
		{
			MessageBox(GetMainHwnd(), "Document didn't support loading from file", "WebEditor", MB_OK);
		}
	}
#endif
	return S_OK;
}

STDMETHODIMP CPluginFilterClass::GetName(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_name.copy();
	return S_OK;
}

STDMETHODIMP CPageDesignerApp::get_clipboardSavePNG(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_clipboardSavePNG;
	return S_OK;
}

STDMETHODIMP CPageDesignerApp::put_clipboardSavePNG(VARIANT_BOOL newVal)
{
	m_clipboardSavePNG = newVal;
	return S_OK;
}

STDMETHODIMP CPageDesignerApp::get_clipboardSaveJPEG(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_clipboardSaveJPEG;
	return S_OK;
}

STDMETHODIMP CPageDesignerApp::put_clipboardSaveJPEG(VARIANT_BOOL newVal)
{
	m_clipboardSaveJPEG = newVal;
	return S_OK;
}

STDMETHODIMP CPageDesignerApp::get_clipboardSaveGIF(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_clipboardSaveGIF;
	return S_OK;
}

STDMETHODIMP CPageDesignerApp::put_clipboardSaveGIF(VARIANT_BOOL newVal)
{
	m_clipboardSaveGIF = newVal;
	return S_OK;
}

STDMETHODIMP CPageDesignerApp::get_newArtHasBasicAppearance(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_newArtHasBasicAppearance;
	return S_OK;
}

STDMETHODIMP CPageDesignerApp::put_newArtHasBasicAppearance(VARIANT_BOOL newVal)
{
	m_newArtHasBasicAppearance = newVal;
	return S_OK;
}

STDMETHODIMP CPageDesignerApp::get_strokeOrFill(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_strokeOrFill;
	return S_OK;
}

STDMETHODIMP CPageDesignerApp::put_strokeOrFill(long newVal)
{
	m_strokeOrFill = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

BEGIN_CMD_MAP(CPageDesignerApp)
// File
	CMD_HANDLER(ID_FILE_NEW, OnFileNew)
	CMD_HANDLER(ID_FILE_OPEN, OnFileOpen)

	CMD_HANDLER(ID_FILE_CUSTOMIZE, OnCustomize)

// Tool
	CMD_HANDLER(ID_TOOL_SELECT, OnSetTool)
	CMD_UPDATE(ID_TOOL_SELECT, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_DIRECT, OnSetTool)
	CMD_UPDATE(ID_TOOL_DIRECT, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_TEXT, OnSetTool)
	CMD_UPDATE(ID_TOOL_TEXT, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_TEXTPATH, OnSetTool)
	CMD_UPDATE(ID_TOOL_TEXTPATH, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_RECTANGLE, OnSetTool)
	CMD_UPDATE(ID_TOOL_RECTANGLE, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_RECTANGLEGRAPHIC, OnSetTool)
	CMD_UPDATE(ID_TOOL_RECTANGLEGRAPHIC, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_ELLIPSE, OnSetTool)
	CMD_UPDATE(ID_TOOL_ELLIPSE, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_ELLIPSEGRAPHIC, OnSetTool)
	CMD_UPDATE(ID_TOOL_ELLIPSEGRAPHIC, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_LINE, OnSetTool)
	CMD_UPDATE(ID_TOOL_LINE, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_PATHPEN, OnSetTool)
	CMD_UPDATE(ID_TOOL_PATHPEN, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_PATHADDANCHOR, OnSetTool)
	CMD_UPDATE(ID_TOOL_PATHADDANCHOR, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_PATHDELETEANCHOR, OnSetTool)
	CMD_UPDATE(ID_TOOL_PATHDELETEANCHOR, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_PATHCORNER, OnSetTool)
	CMD_UPDATE(ID_TOOL_PATHCORNER, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_SCALE, OnSetTool)
	CMD_UPDATE(ID_TOOL_SCALE, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_ROTATE, OnSetTool)
	CMD_UPDATE(ID_TOOL_ROTATE, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_FREETRANSFORM, OnSetTool)
	CMD_UPDATE(ID_TOOL_FREETRANSFORM, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_TWIRL, OnSetTool)
	CMD_UPDATE(ID_TOOL_TWIRL, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_BULGE, OnSetTool)
	CMD_UPDATE(ID_TOOL_BULGE, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_SYMBOLSPRAYER, OnSetTool)
	CMD_UPDATE(ID_TOOL_SYMBOLSPRAYER, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_GRADIENT, OnSetTool)
	CMD_UPDATE(ID_TOOL_GRADIENT, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_ZOOM, OnSetTool)
	CMD_UPDATE(ID_TOOL_ZOOM, OnSetToolUpdate)
	CMD_HANDLER(ID_TOOL_HAND, OnSetTool)
	CMD_UPDATE(ID_TOOL_HAND, OnSetToolUpdate)

	CMD_HANDLER(ID_EDIT_PREFERENCES, OnEditPreferences)

// Edit
//	CMD_HANDLER(ID_EDIT_EMPTYCLIPBOARD, OnEditEmptyClipboard)
//	CMD_UPDATE(ID_EDIT_EMPTYCLIPBOARD, OnEditEmptyClipboardUpdate)

// Help
	CMD_HANDLER(ID_HELP, OnHelp)
	CMD_HANDLER(ID_APP_ABOUT, OnAbout)

	CMD_HANDLER(ID_APPEARANCE_NEWARTHASBASICAPPEARANCE, OnAppearanceNewArtHasBasicAppearance)
	CMD_UPDATE(ID_APPEARANCE_NEWARTHASBASICAPPEARANCE, OnAppearanceNewArtHasBasicAppearanceUpdate)
//
	CMD_UPDATE(ID_TYPE_FONTFACE, OnFontfaceUpdate)

END_CMD_MAP()

LRESULT CPageDesignerApp::OnAppearanceNewArtHasBasicAppearance(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	put_newArtHasBasicAppearance(m_newArtHasBasicAppearance? VARIANT_FALSE: VARIANT_TRUE);
	return 0;
}

void CPageDesignerApp::OnAppearanceNewArtHasBasicAppearanceUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->Enable(m_newArtHasBasicAppearance? TRUE: FALSE);
}

#include "BrushDimensionsDlg.h"

LRESULT CPageDesignerApp::OnSetTool(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_activeTool = wID;

	switch (wID)
	{
	case ID_TOOL_SELECT:
	case ID_TOOL_DIRECT:
		m_activeSelectionTool = wID;
		break;

	case ID_TOOL_TWIRL:
	case ID_TOOL_BULGE:
		{
			if (wNotifyCode == BN_DBLCLK)
			{
				CPropertySheet* sheet = new CPropertySheet("Tool", 0, GetMainHwnd());

				CBrushDimensionsDlg	brush;
				brush.m_brushSettings = this;
				sheet->AddPage(brush);

				sheet->DoModal();
			}
		}
		break;
	}

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return 0;
}

void CPageDesignerApp::OnSetToolUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(iid == m_activeTool);
}

#include "NewDocumentDlg.h"

LRESULT CPageDesignerApp::OnFileNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CNewDocumentDlg dlg;

	dlg.m_numPages = 1;

	dlg.m_pageWidth = ConvertSpecifiedValueToUserUnit(UNIT_PT, 612);
	dlg.m_pageHeight = ConvertSpecifiedValueToUserUnit(UNIT_PT, 792);

	dlg.m_marginLeft = ConvertSpecifiedValueToUserUnit(UNIT_PT, 36);
	dlg.m_marginRight = ConvertSpecifiedValueToUserUnit(UNIT_PT, 36);
	dlg.m_marginTop = ConvertSpecifiedValueToUserUnit(UNIT_PT, 36);
	dlg.m_marginBottom = ConvertSpecifiedValueToUserUnit(UNIT_PT, 36);

	dlg.m_columnNumber = 1;
	dlg.m_columnGutter = ConvertSpecifiedValueToUserUnit(UNIT_PT, 12);

	dlg.m_facingPages = TRUE;

	if (dlg.DoModal(GetMainHwnd(), NULL) == IDOK)
	{
		CComObject<CPDDocument>* pDocument;
		CComObject<CPDDocument>::CreateInstance(&pDocument);
		if (pDocument)
		{
			pDocument->AddRef();

			pDocument->m_pageWidth = dlg.m_pageWidth;
			pDocument->m_pageHeight = dlg.m_pageHeight;

			pDocument->m_marginTop = dlg.m_marginTop;
			pDocument->m_marginBottom = dlg.m_marginBottom;
			pDocument->m_marginInside = dlg.m_marginLeft;
			pDocument->m_marginOutside = dlg.m_marginRight;

			pDocument->m_columnNumber = dlg.m_columnNumber;
			pDocument->m_columnGutter = dlg.m_columnGutter;

			pDocument->m_facingPages = dlg.m_facingPages? VARIANT_TRUE: VARIANT_FALSE;

			WCHAR str[256];
			swprintf(str, L"Untitled%d.pddoc", ++m_nextDocumentIndex);
			pDocument->m_fileTitle = str;

			pDocument->NewDocument();	// Init (?)
			pDocument->CreatePages(dlg.m_numPages);

			pDocument->ShowViews();

		//	CComQIPtr<IUIManager> uiManager = m_frame;
		//	CComQIPtr<IPDDocument> document = pDocument;

		//	CComPtr<IUnknown> _this;
		//	QueryInterface(IID_IUnknown, (void**)&_this);

			//uiManager->ActivateObject(GetUnknown(), document);
		}
	}
#if 0
	HINSTANCE hLib = LoadLibrary("C:\\mmsx\\mmstudioplugins\\DOMCOREMOD.dll");
	if (hLib)
	{
		HTMLModalDialogProc HTMLModalDialog = (HTMLModalDialogProc)GetProcAddress(hLib, "HTMLModalDialog");
		if (HTMLModalDialog)
		{
			CComQIPtr<IDOMDocument> xmldoc;
			xmldoc.CoCreateInstance(CLSID_LDocument);
			xmldoc->put_async(VARIANT_FALSE);
			VARIANT_BOOL success;
			xmldoc->loadXML(L"<newdocument/>", &success);

			CComQIPtr<IDOMElement> element;
			xmldoc->get_documentElement(&element);

			WCHAR buf[64];

			swprintf(buf, L"%d", 1);
			element->setAttribute(L"pagesnum", buf);

			swprintf(buf, L"%d", 1);
			element->setAttribute(L"columnsnum", buf);

			swprintf(buf, L"%dpt", 1);
			element->setAttribute(L"columnsgutter", buf);

			_variant_t arg = (IDispatch*)element.p;

			_variant_t result;
			HTMLModalDialog(GetMainHwnd(), L"C:\\MMStudio\\pd_newdocument.html", &arg, L"", &result);

			CComObject<CPDDocument>* pDocument;
			CComObject<CPDDocument>::CreateInstance(&pDocument);
			if (pDocument)
			{
				pDocument->AddRef();

				pDocument->NewDocument();	// Init (?)

				pDocument->m_pageWidth = 200;
				pDocument->m_pageHeight = 400;
				pDocument->CreatePages(4);

				pDocument->ShowViews();

				CComQIPtr<IUIManager> uiManager = m_frame;
				CComQIPtr<IPDDocument> document = pDocument;

				CComPtr<IUnknown> _this;
				QueryInterface(IID_IUnknown, (void**)&_this);

				uiManager->ActivateObject(_this, document);
			}
		}
		else
		{
			MessageBox(GetMainHwnd(), "Couldn't find proc", "PageDesigner", MB_OK);
		}

		FreeLibrary(hLib);
	}
	else
	{
		MessageBox(GetMainHwnd(), "Couldn't load library", "PageDesigner", MB_OK);
	}
#endif

#if 0
	CComObject<CESvgDocument>* pDocument;
	CComObject<CESvgDocument>::CreateInstance(&pDocument);
	pDocument->AddRef();

	if (pDocument != NULL)
	{
		pDocument->NewDocument();
		pDocument->ShowViews();

		CComPtr<IUnknown> unk;
		pDocument->QueryInterface(IID_IUnknown, (void**)&unk);
		m_frame->ActivateObject(unk);
	}
#endif
	return 0;
}

LRESULT CPageDesignerApp::OnFileOpen(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
												"PageDesigner Document (*.pddoc)\0*.pddoc\0"
												);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, "");	// Initial filename
	
	TCHAR curdir[MAX_PATH];
	GetCurrentDirectory(sizeof(curdir), curdir);

	HWND hwnd = GetMainHwnd();

	OPENFILENAME	ofn = {0};
	ofn.lStructSize = OPENFILENAME_SIZE_VERSION_400A;//sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.hInstance = _Module.m_hInst;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = sizeof(sbuffer);
	ofn.lpstrInitialDir = curdir;
	ofn.lpstrFilter = FilesFilter;
	
	if (GetOpenFileName(&ofn))
	{
		BOOL success = FALSE;

		CComPtr<IArchive> ar;
		ar.CoCreateInstance(CLSID_Archive);

		CComPtr<IArchiveElement> node;
		if (SUCCEEDED(ar->Open(_bstr_t(sbuffer), 2, L"pddoc", &node)))
		{
			CComObject<CPDDocument>* pddocument;
			CComObject<CPDDocument>::CreateInstance(&pddocument);
			if (pddocument)
			{
				pddocument->AddRef();

				HRESULT hr = pddocument->Deserialize(ar, node, NULL);
				success = SUCCEEDED(hr);

				pddocument->ShowViews();
			}
		}


		/*
		LPTSTR ext = PathFindExtension(sbuffer);

		CComPtr<IDOMDocument> document;
		document.CoCreateInstance(CLSID_LDOMDocument);

		VARIANT_BOOL bloaded;
		document->load(_bstr_t(sbuffer), &bloaded);
		if (bloaded)
		{
			CComPtr<IDOMElement> documentElement;
			document->get_documentElement(&documentElement);
			if (documentElement)
			{
				CComObject<CPDDocument>* pddocument;
				CComObject<CPDDocument>::CreateInstance(&pddocument);
				if (pddocument)
				{
					pddocument->AddRef();

					HRESULT hr = pddocument->loadXML(documentElement);
					success = SUCCEEDED(hr);

					pddocument->ShowViews();
				}
			}
		}
		*/

		if (!success)
		{
			MessageBox(GetMainHwnd(), "Failed to load document", "PageDesigner", MB_OK);
		}
	}
	return 0;
}

LRESULT CPageDesignerApp::OnEditEmptyClipboard(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HWND hwnd = GetMainHwnd();

	if (MessageBox(hwnd, "Are you sure you want to empty the clipboard?", "WebEditor", MB_YESNO) == IDYES)
	{
		if (OpenClipboard(NULL))
		{
			EmptyClipboard();
			CloseClipboard();
		}
	}
	return 0;
}

void CPageDesignerApp::OnEditEmptyClipboardUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->Enable(CountClipboardFormats() > 0);
}

void CPageDesignerApp::OnFontfaceUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	/*
	CComQIPtr<IUIComboBox> box;
	pCmdUI->get_controlItem((IUnknown**)&box);

	ScanFonts(box);
	*/
/*	long index;

	box->AddString(L"1", &index);
	box->AddString(L"2", &index);
	box->AddString(L"3", &index);
	box->AddString(L"4", &index);
*/
}

//#import "..\LHTMLHelp\LHTMLHelp.tlb"

LRESULT CPageDesignerApp::OnHelp(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	LHTMLHELPLib::ILHTMLHelpWindowPtr hw;

	if (SUCCEEDED(hw.CreateInstance("LHTMLHelp.LHTMLHelpWindow")))
	{
		hw->ShowHelp("C:\\mmstudio\\Help\\TOC.xml");
		hw->AddRef();
	}

#if 0
	HELPLib::IHelpFramePtr help;
	help.CreateInstance("Help.HelpFrame");

	help->ShowHelp("C:\\mmsx\\2DAnimator\\Help\\TOC.xml");
	help->AddRef();	// ??
#endif
#endif
	return 0;
}

#include "AboutDlg.h"

LRESULT CPageDesignerApp::OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CAboutDlg dlg;
	dlg.DoModal(GetMainHwnd());

	return 0;
}

#include "PrefsGridsDlg.h"
#include "PrefsUnitsDlg.h"
#include "PrefsTransparencyDlg.h"
#include "PrefsClipboardDlg.h"

LRESULT CPageDesignerApp::OnEditPreferences(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CPropertySheet* sheet = new CPropertySheet("Preferences", 0, GetMainHwnd());

	CPrefsUnitsDlg	units;

	CPrefsGridsDlg	grids;
	grids.m_targetObject = this;

	CPrefsTransparencyDlg transp;
	transp.m_targetObject = this;

	CPrefsClipboardDlg clipboard;
	clipboard.m_targetObject = this;

	sheet->AddPage(grids);
	sheet->AddPage(units);
	sheet->AddPage(transp);
	sheet->AddPage(clipboard);

	sheet->DoModal();

	return 0;
}

#import "..\UICustomizeMod\UICustomizeMod.tlb"

LRESULT CPageDesignerApp::OnCustomize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	UICUSTOMIZEMODLib::IUICustomizePtr	customize;
	if (SUCCEEDED(customize.CreateInstance(L"UICustomizeMod.UICustomize")))
	{
		CComQIPtr<IUIManager> uiManager = gIFrame;//m_frame;
		if (uiManager)
		{
			customize->Show(uiManager, (long)GetMainHwnd());
		}
	}
	else
	{
		MessageBox(GetMainHwnd(), "Couldn' load Customize object", "PageDesigner", MB_OK);
	}

	return 0;

#if 0
	HINSTANCE hLib = LoadLibrary("C:\\mmsx\\mmstudioplugins\\DOMCOREMOD.dll");
	if (hLib)
	{
		HTMLModelessDialogProc HTMLModelessDialog = (HTMLModelessDialogProc)GetProcAddress(hLib, "HTMLModelessDialog");
		if (HTMLModelessDialog)
		{
			CComQIPtr<IDispatch> disp = m_frame;
			_variant_t arg = (IDispatch*)disp;

			HTMLModelessDialog(GetMainHwnd(), L"C:\\mmstudio\\customize_toolbars.html", &arg, L"");
		}
		else
		{
			MessageBox(GetMainHwnd(), "Couldn't find proc", "WebEditor", MB_OK);
		}

		FreeLibrary(hLib);
	}
	else
	{
		MessageBox(GetMainHwnd(), "Couldn't load library", "WebEditor", MB_OK);
	}
#endif
}
