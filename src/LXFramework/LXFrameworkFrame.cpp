// LXFrameworkFrame.cpp : Implementation of CLXFrameworkFrame
#include "stdafx.h"
#include "LXFramework.h"
#include "LXFramework2.h"

#if 0

#include "LXFrameworkFrame.h"
#include "LXFrameworkApp.h"

/*
#include "..\LHTML\LHTML2.h"
#include "..\LHTML\LHTMLWindow.h"
#include "..\LHTML\PImage.h"
#include "..\LHTML\LDOMElementImpl.h"
#include "..\LHTML\PElement.h"

#pragma comment(lib, "..\\LHTML\\Debug\\LHTML.lib")
*/

extern CLXFrameworkApp* gApp;
extern ILXFrameworkApp* gIApp;

// TODO, make one dialog class for all sheets

//#include "..\UIT\UIDlgSite.h"

//#include "..\UIT\UIViewSheet.h"

STDMETHODIMP CLXFrameworkAddinUIManager::RegisterBar(IUIDlgClass* dlgClass, BSTR name, IUIDlgSite* *pVal)
{
#if 0
	CComObject<CUIDlgSite>* pSite;
	CComObject<CUIDlgSite>::CreateInstance(&pSite);

	pSite->SetBarStyle(CBRS_SIZE_DYNAMIC);
	pSite->m_pDockSite = m_pAddinSite->m_frame;

	pSite->m_name = name;
	pSite->m_dlgClass = dlgClass;

	pSite->AddRef();
	m_dialogs.Add(pSite);

	*pVal = pSite;
	(*pVal)->AddRef();
#endif

	return S_OK;
}

// CLXFrameworkAddinUIManager
STDMETHODIMP CLXFrameworkAddinUIManager::CreateDlgSheet(LPWSTR name, IMenuItem* menu, /*[out,retval]*/ IUIDlgSheet* *pVal)
{
#if 0
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	CComObject<CUIDlgSite>* pSite;
	CComObject<CUIDlgSite>::CreateInstance(&pSite);
	pSite->AddRef();

	pSite->SetBarStyle(CBRS_SIZE_DYNAMIC);
	pSite->m_menu = menu;
	pSite->m_name = name;
	pSite->m_pDockSite = m_pAddinSite->m_frame;

	/*
	CComObject<CUISheetDlgClass>* pDialogClass;
	CComObject<CUISheetDlgClass>::CreateInstance(&pDialogClass);
	if (pDialogClass)
	*/
	{
		//pDialogClass->AddRef();
		//pDialogClass->AddRef();	// TODO remove

	//	pDialogClass->m_uiManager = this;
	//	pDialogClass->m_name = name;
		//pDialogClass->m_nID = 0;//(UINT)nID;

		CComObject<CUIDlgSheet>* sheet;
		CComObject<CUIDlgSheet>::CreateInstance(&sheet);
		if (sheet)
		{
			sheet->AddRef();	// TODO remmve
			//pDialogClass->m_dialogs.Add(sheet);
			//sheet->m_pOwnerRegisteredDlg = pDialogClass;
			pSite->m_dlg = sheet;
			sheet->m_pDlgSite = pSite;

		//	sheet->m_pDockSite = m_pAddinSite->m_frame;//GetFrame();//static_cast<CUIFrame*>((IUIFrame*)static_cast<T*>(m_uiManager));//->m_pDlgManager;

			sheet->m_dwStyle = CBRS_SIZE_DYNAMIC;

			/*
			sheet->AddRef();
			static_cast<T*>(this)->m_pSheets.AddTail(sheet);
			*/
#if 0
			GetFrame()->AddDlgSheet(sheet);
#endif

		//	static_cast<CWindowImpl<CDlgSheet>*>(sheet)->Create(static_cast<T*>(this)->m_hWnd, CRect(0,0,0,0), NULL, WS_CHILD | WS_VISIBLE);

			*pVal = sheet;
			(*pVal)->AddRef();
		}

//		*pVal = pDialogClass;
//		(*pVal)->AddRef();
	}
#endif

	return S_OK;
}

STDMETHODIMP CLXFrameworkAddinUIManager::CreateDlgSite(LPWSTR name, IMenuItem* menu, IUIDlg* dlg, IUIDlgSite* *pVal)
{
#if 0
	if (pVal == NULL) return E_POINTER;
	if (dlg == NULL) return E_INVALIDARG;
	*pVal = NULL;

	CComObject<CUIDlgSite>* pDlgSite;
	CComObject<CUIDlgSite>::CreateInstance(&pDlgSite);
	if (pDlgSite)
	{
		pDlgSite->AddRef();

		pDlgSite->SetBarStyle(CBRS_SIZE_DYNAMIC);

		pDlgSite->m_name = name;
		pDlgSite->m_menu = menu;
		pDlgSite->m_dlg = dlg;
		pDlgSite->m_pDockSite = m_pAddinSite->m_frame;
		dlg->SetDlgSite(pDlgSite);

		*pVal = pDlgSite;
	}
#endif

	return S_OK;
}

STDMETHODIMP CLXFrameworkAddinUIManager::CreateMenuDlg(IUIMenuDlg* *pVal)
{
#if 0
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	CComObject<CUIMenuDlg>* pMenuDlg;
	CComObject<CUIMenuDlg>::CreateInstance(&pMenuDlg);
	if (pMenuDlg)
	{
		pMenuDlg->AddRef();

		*pVal = pMenuDlg;
	}
#endif

	return S_OK;
}

STDMETHODIMP CLXFrameworkFrame::GetWindow(HWND* phwnd)
{
	if (phwnd == NULL) return E_POINTER;
	*phwnd = NULL;	// TODO
	return S_OK;
}

#if 0
STDMETHODIMP CLXFrameworkFrame::CreateViewSheet(BSTR name, IEViewGroup* viewGroup, IUIDlgSheet* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	CComObject<CUIDlgSite>* pSite;
	CComObject<CUIDlgSite>::CreateInstance(&pSite);
	pSite->SetBarStyle(CBRS_SIZE_DYNAMIC);
	pSite->m_pDockSite = this;
	pSite->m_name = name;

	CComObject<CUIViewSheet>* p;
	CComObject<CUIViewSheet>::CreateInstance(&p);
	if (p)
	{
		p->AddRef();
	//	p->m_pDockSite = this;//m_spFrame = this;
		p->m_pDlgSite = pSite;
		pSite->m_dlg = p;
		p->m_viewGroup = viewGroup;

		//p->CreateEx(m_hWndClient);

		*pVal = p;
	}

	return S_OK;
}
#endif

////////////////////////////////////////////////////////////////////
// CLXFrameworkAddinSite

STDMETHODIMP CLXFrameworkAddinSite::GetFrame(/*[out,retval]*/ ILXFrameworkFrame* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_frame;
	(*pVal)->AddRef();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CLXFrameworkFrame

int CLXFrameworkFrame::FinalConstruct()
{

	m_app = NULL;

#if 0
	m_app->SetFrame(this);
	m_app->SetUIManager(this);
#endif

///////

	/*
	CComPtr<IUIDlgSheet> sheet;
	CreateSheet(&sheet);
	sheet->AddPage(
	*/

//////

// Add menu resources
//	AddMenuResource(IDR_MAINFRAME);
	/*
	AddMenuResource(IDR_FILESVIEW);
	AddMenuResource(IDR_XMLSOURCEVIEW);
	AddMenuResource(IDR_XMLGRIDVIEW);
	AddMenuResource(IDR_XMLLAYOUTVIEW);
	AddMenuResource(IDR_CSSSTYLESHEETVIEW);
	AddMenuResource(IDR_FRAMESDESIGNVIEW);
	AddMenuResource(IDR_XMLPREVIEWVIEW);
	AddMenuResource(IDR_XSLTEMPLATESVIEW);
	AddMenuResource(IDR_TEXTVIEW);
	AddMenuResource(IDR_SCHEMAVIEW);
	AddMenuResource(IDR_ASTREEVIEW);
	AddMenuResource(IDR_WORKGROUPFILESVIEW);
	AddMenuResource(IDR_FTPVIEW);
	AddMenuResource(IDR_DBVIEW);
	AddMenuResource(IDR_SQLQUERYVIEW);

	AddMenuResource(IDR_SVGTOOLS);
	AddMenuResource(IDR_FILTERSDLG);
	AddMenuResource(IDR_SYMBOLSDLG);
	AddMenuResource(IDD_HISTORYDLG);
	*/

	//AddMenuResource(IDR_IMAGETOOLS);

// Icons
//	AddToolbarCommands(_Module.GetResourceInstance(), IDR_MAINFRAME);
	//AddToolbarCommands(IDR_SVGTOOLS);
	//AddToolbarCommands(IDR_QUERYDESIGN);

	//AddToolbarCommands(IDR_FORMATTING);
	//AddToolbarCommands(IDR_INSERT);

	//AddToolbarCommands(IDR_IMAGETOOLS);

//
//	Load(L"C:\\MMStudio\\Extras\\LXFramework\\Debug\\LXFramework.xml");

	return S_OK;
}

void CLXFrameworkFrame::FinalRelease()
{
	/*
	if (m_pDlgManager)
	{
		m_pDlgManager->Release();
		m_pDlgManager = NULL;
	}
	*/
}

STDMETHODIMP CLXFrameworkFrame::GetApp(ILXFrameworkApp* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_app;
	(*pVal)->AddRef();
	return S_OK;
}

#if 0
LRESULT CLXFrameworkFrame::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	m_app->m_document->getElementById(L"frame", &m_element);
	CPElement* pPElement = (CPElement*)CComQIPtr<CLDOMElementImplImpl>(m_element)->m_pNodes[0];

	if (pPElement->m_computedOverflowX == Overflow_scroll)
	{
		ModifyStyle(0, WS_HSCROLL);
	}

	if (pPElement->m_computedOverflowY == Overflow_scroll)
	{
		ModifyStyle(0, WS_VSCROLL);
	}

	ATLASSERT(0);
#if 0
	baseClass::OnCreate(uMsg, wParam, lParam, bHandled);

	EnableDocking(CBRS_ALIGN_ANY);
#endif

//	CComQIPtr<CLDOMElementImplImpl>(m_element)->m_pNodes.GetSize();

#if 0
	CComPtr<ILCSSStyleDeclaration> style;
	m_app->m_viewCSS->getComputedStyle(m_element, NULL, &style);

	CComPtr<ILCSSPrimitiveValue> cssvalue;
	style->getPropertyCSSValue(L"background-image", (ILCSSValue**)&cssvalue);
	CComBSTR backgroundImage;
	cssvalue->getStringValue(&backgroundImage);
#endif

// Dialogs

#if 0
	{
		CComPtr<IUIDlgSheet> dlgsheet;
		CreateDlgSheet(NULL, &dlgsheet);
		{
			CComPtr<IUIRegisteredDlg> rdlg;
			RegisterDlg(18, L"Contents", 0, &rdlg);
			dlgsheet->AddPage(rdlg, NULL);
		}

		CComPtr<IUIDlgSite> dlgsite;
		CreateDlgSite(dlgsheet, &dlgsite);
		FloatControlBar(dlgsite, CPoint(0,0), CBRS_SIZE_DYNAMIC);
	}


#if 0
	//
		{
			CComPtr<IUIDlgSheet> sheet;
			CreateDlgSheet(&sheet);
			sheet->put_canGroup(0);

			{
				CComPtr<IUIRegisteredDlg> rdlg;
				RegisterMenuDlg(20, IDR_STANDARD, L"Standard", 0, &rdlg);
				sheet->AddPage(rdlg, NULL);
			}

			sheet->Show();
		}
#endif

	{
		{
			CComPtr<IUIRegisteredDlg> rdlg;
			RegisterMenuDlg(21, IDR_WEB, L"Web", 0, &rdlg);

			CComPtr<IUIDlg> dlg;
			rdlg->CreateDlg(&dlg);

			CComPtr<IUIDlgSite> dlgsite;
			CreateDlgSite(dlg, &dlgsite);

			FloatControlBar(dlgsite, CPoint(0,0), CBRS_SIZE_DYNAMIC);
		}
	}
#endif

//	m_app->OnCreateFrame();

/////////////////
	//RegisterMenuDlg(IDR_STANDARD, L"Standard", 0, &dlg);
//	RegisterMenuDlg(22, IDR_QUERYDESIGN, L"Query Design", 0, NULL);
//	RegisterMenuDlg(23, IDR_HTMLFORMATTING, L"Formatting", 0, NULL);
///// ?
//	RegisterMenuDlg(24, IDR_CSSPARAGRAPH, L"CSS Paragraph", 0, NULL);
////

#if 0
	if (FALSE)
	{
		FILE* fp = fopen("C:\\LXFramework.dlgs", "r");
		if (fp)
		{
			try
			{
				while (!feof(fp))
				{
					int c = fgetc(fp);
					if (c == '(')
					{
						CComObject<CDlgSheet>* pSheet;
						CComObject<CDlgSheet>::CreateInstance(&pSheet);
						if (pSheet)
						{
							pSheet->AddRef();

							pSheet->m_pDockSite = this;

							//m_pSheets.AddTail(pSheet);
						//	AddDlgSheet(pSheet);

							fscanf(fp, "(%d %d)", &pSheet->m_ptMRUFloatPos.x, &pSheet->m_ptMRUFloatPos.y);
							fscanf(fp, "(style:%d)", &pSheet->m_dwStyle);

							BOOL bFloating;
							fscanf(fp, "(floating:%d)", &bFloating);

							fscanf(fp, "(");

							while (!feof(fp))
							{
								int c = fgetc(fp);
								if (c != '(')
								{
									ungetc(c, fp);
									break;
								}

								int nID;//RDlg;
								fscanf(fp, "%d", &nID/*RDlg*/);

								CRegisteredDialog* pRDlg = NULL;
								{
									for (int i = 0; i < m_dialogs.GetSize(); i++)
									{
										if (m_dialogs[i]->m_nID == nID)
										{
											pRDlg = m_dialogs[i];
											break;
										}
									}
								}

								if (pRDlg)
								{
								//CRegisteredDialog* pRDlg = m_dialogs[nRDlg];

									pRDlg->AddRef();

									if (pRDlg->m_pOwnerSheet)
										pRDlg->m_pOwnerSheet->RemovePage(pRDlg);

									pSheet->AddPage(pRDlg, NULL);

									pRDlg->Release();
								}

								fscanf(fp, ")");
							}

							if (pSheet->m_activeIndex >= 0)
							{
								AddDlgSheet(pSheet);

								//::
								static_cast<CWindowImpl<CDlgSheet>*>(pSheet)->Create(m_hWnd, CRect(0,0,0,0), NULL, WS_CHILD | WS_VISIBLE);

								if (bFloating)
								{
									FloatControlBar(pSheet, pSheet->m_ptMRUFloatPos, CBRS_ALIGN_TOP | CBRS_SIZE_DYNAMIC);
								}
								else
								{
									CDockBar* pDockBar = GetControlBar(AFX_IDW_DOCKBAR_TOP);
									pDockBar->DockControlBar(pSheet, NULL);
								}
							}

							pSheet->Release();
							/*
							else
							{
								RemoveDlgSheet(pSheet);
							}
							*/
						}

						c = fgetc(fp);
						if (c != ')')
							throw -1;
					}
				}
			}
			catch (long)
			{
			}

			fclose(fp);
		}
	}

// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
//	pLoop->AddIdleHandler(this);
	pLoop->AddMessageFilter(this);
#endif

#if 0	// TODO, have this in LXDocumentViewer
	{
      HLBWINFO hlbwinfo;
		memset(&hlbwinfo, 0, sizeof(hlbwinfo));
		hlbwinfo.cbSize = sizeof(hlbwinfo);
		hlbwinfo.grfHLBWIF = HLBWIF_HASFRAMEWNDINFO | HLBWIF_HASDOCWNDINFO;
		WINDOWPLACEMENT wp;
		wp.length = sizeof(WINDOWPLACEMENT);
		
		//CWnd* pMainFrame = AfxGetMainWnd();
		/*pMainFrame->*/GetWindowPlacement(&wp);
		hlbwinfo.rcFramePos = wp.rcNormalPosition;
		if (SW_SHOWMAXIMIZED == wp.showCmd)
			hlbwinfo.grfHLBWIF |= HLBWIF_FRAMEWNDMAXIMIZED;
		
	//	CHlinkAxDocView* pView = GetView();
	//	CFrameWnd* pChildFrame = pView->GetParentFrame();
		/*pChildFrame->*/GetWindowPlacement(&wp);
		hlbwinfo.rcDocPos = wp.rcNormalPosition;
		if (SW_SHOWMAXIMIZED == wp.showCmd)
			hlbwinfo.grfHLBWIF |= HLBWIF_DOCWNDMAXIMIZED;
		
		// TODO: Internet Toolbar positioning
		m_hlinkBrowseContext->SetBrowseWindowInfo(&hlbwinfo);    
	}
#endif
#endif

	return 0;
}

LRESULT CLXFrameworkFrame::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	if (FALSE)
	{
		FILE *fp = fopen("C:\\LXFramework.dlgs", "w");
		if (fp)
		{
			UPOSITION pos = m_pSheets.GetHeadPosition();
			while (pos)
			{
				IUIDlgSheet* sheet = (IUIDlgSheet*)m_pSheets.GetNext(pos);
				CDlgSheet* pSheet = (CDlgSheet*)sheet;

				//CPoint t = pSheet->m_lastWindowRect;
				//pSheet->GetWindowRect(&wrect);

				fprintf(fp, "(");

				fprintf(fp, "(%d %d)", pSheet->m_ptMRUFloatPos.x, pSheet->m_ptMRUFloatPos.y);
				fprintf(fp, "(style:%d)", pSheet->m_dwStyle);
				//fprintf(fp, "(%d %d)", pSheet->m_rectMRUDockPos.x, pSheet->m_rectMRUDockPos.y);

				BOOL bFloating = pSheet->GetBarStyle() & CBRS_FLOATING;
				fprintf(fp, "(floating:%d)", bFloating);

				fprintf(fp, "(");

				for (int i = 0; i < pSheet->m_pages.GetSize(); i++)
				{
					CRegisteredDialog* pRDlg = static_cast<CRegisteredDialog*>(pSheet->m_pages[i]->m_dlg);
					for (int i = 0; i < m_dialogs.GetSize(); i++)
					{
						if (m_dialogs[i] == pRDlg)
						{
							break;
						}
					}
					if (i < m_dialogs.GetSize())
					{
						fprintf(fp, "(");

						fprintf(fp, "%d", pRDlg->m_nID/*i*/);

						fprintf(fp, ")");
					}
				}

				fprintf(fp, ")");

				fprintf(fp, ")\n");
			}

			fclose(fp);
		}
	}
#endif

#if 0
	return baseClass::OnDestroy(uMsg, wParam, lParam, bHandled);
#endif
	return 0;
}

LRESULT CLXFrameworkFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	for (int i = m_documents.GetSize()-1; i >= 0; i--)
	{
		IActiveCntDocument* document = m_documents[i];
		m_documents.RemoveAt(i);

		document->CloseDocument();
		document->Release();
	}
#endif

// TODO, do this in App class
	{
		if (gApp->m_atomApp)
		{
			GlobalDeleteAtom(gApp->m_atomApp);// = ::GlobalAddAtom(m_pszExeName);
			gApp->m_atomApp = NULL;
		}

		if (gApp->m_atomSystemTopic)
		{
			GlobalDeleteAtom(gApp->m_atomSystemTopic);// = ::GlobalAddAtom(_T("system"));
			gApp->m_atomSystemTopic = NULL;
		}
	}

	LRESULT lResult = 0;
	ATLASSERT(0);
#if 0
	bHandled = baseClass::ProcessWindowMessage(m_hWnd, uMsg, wParam, lParam, lResult);
#endif
	return lResult;
}

LRESULT CLXFrameworkFrame::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	BOOL fCalcValidRects = (BOOL)wParam;        // valid area flag 

	LPRECT lpncsp = (LPRECT)lParam;               // new window coordinates 

	lpncsp->left += 7;
	lpncsp->top += 28;
	lpncsp->right -= 7;
	lpncsp->bottom -= 7;

	if (fCalcValidRects)
	{
		return WVR_REDRAW;
	}
	else
	{
		return 0;
	}
}

LRESULT CLXFrameworkFrame::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
#if 0
	BOOL bActive = wParam;

	if (TRUE/*(GetStyle() & MFS_SYNCACTIVE) == 0*/)
	{
		/*
		if (afxData.bSmCaption)
			return Default();
			*/

		if (pData->m_bActive != bActive)
		{
			pData->m_bActive = bActive;
			SendMessage(hWnd, WM_NCPAINT, 0, 0);
		}
	}
	/*
	else if (m_nFlags & WF_KEEPMINIACTIVE)
	{
		return FALSE;
	}*/
	return TRUE;
#endif


	CPElement* pPElement = (CPElement*)CComQIPtr<CLDOMElementImplImpl>(m_element)->m_pNodes[0];

	BOOL bActive = (BOOL)wParam;

	if (FALSE)	// Stay active
		bActive = TRUE;

	// but do not stay active if the window is disabled
	if (!IsWindowEnabled())
		bActive = FALSE;

	if (pPElement->m_bFocus != bActive)
	{
		pPElement->m_bFocus = bActive;
		pPElement->GetCSSProperties();

		SendMessage(WM_NCPAINT);
	}
#endif

	return TRUE;
//	return DefWindowProc(uMsg, bActive, 0/*lParam*/);
}

LRESULT CLXFrameworkFrame::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	USES_CONVERSION;

	CWindowDC dc(m_hWnd);

	//Gdiplus::TextureBrush brush(m_pBackgroundBitmap);

	{
		CRect rect;
		GetWindowRect(&rect);
		rect.OffsetRect(-rect.left, -rect.top);

		dc.ExcludeClipRect(7, 28, rect.Width()-7, rect.Height()-7);

		CPElement* pPElement = (CPElement*)CComQIPtr<CLDOMElementImplImpl>(m_element)->m_pNodes[0];

		{
			Gdiplus::Graphics graphics(dc);

			// Draw background color
			{
				Gdiplus::SolidBrush brush(pPElement->m_computedBackgroundColor);
				graphics.FillRectangle(&brush, Gdiplus::Rect(rect.left, rect.top, rect.Width(), rect.Height()));
			}

			// Draw background image
			if (pPElement->m_pBackgroundImage)
			{
				Gdiplus::TextureBrush brush(pPElement->m_pBackgroundImage->m_gdipImage);
				graphics.FillRectangle(&brush, Gdiplus::Rect(rect.left, rect.top, rect.Width(), rect.Height()));
			}
		}

		xThemeDrawEdge(dc, &rect, xTheme_EDGE_RECT, 0);

		// Draw caption
		{
			Gdiplus::Graphics graphics(dc);

			HFONT hFont = pPElement->m_computedFontFamily[0]->GetHintedHFONT();

			HFONT hOldFont = dc.SelectFont(hFont);

			CRect trect = rect;
			trect.bottom = 28;
			trect.left += 7;
			trect.right -= 7;

			trect.InflateRect(-1,-1);

			int textlength = GetWindowTextLength();
			TCHAR text[256];
			GetWindowText(text, 256);

			{
				Gdiplus::Graphics graphics(dc);

				Gdiplus::RectF layoutRect(float(trect.left), float(trect.top), float(trect.Width()), float(trect.Height()));
				graphics.DrawString(A2W(text), textlength, pPElement->m_computedFontFamily[0]->GetGdipFont(), layoutRect, Gdiplus::StringFormat::GenericDefault(), pPElement->GetColorBrush());
			}
		}
	}
#endif

	return 0;
}
#endif


/// IBindStatusCallback

STDMETHODIMP CLXFrameworkFrame::OnStartBinding( 
													/* [in] */ DWORD dwReserved,
													/* [in] */ IBinding __RPC_FAR *pib)
{
	return S_OK;
}

STDMETHODIMP CLXFrameworkFrame::GetPriority(/* [out] */ LONG __RPC_FAR *pnPriority)
{
	return S_OK;
}

STDMETHODIMP CLXFrameworkFrame::OnLowResource(/* [in] */ DWORD reserved)
{
	return S_OK;
}

STDMETHODIMP CLXFrameworkFrame::OnProgress( 
											  /* [in] */ ULONG ulProgress,
											  /* [in] */ ULONG ulProgressMax,
											  /* [in] */ ULONG ulStatusCode,
											  /* [in] */ LPCWSTR szStatusText)
{
	return S_OK;
}

STDMETHODIMP CLXFrameworkFrame::OnStopBinding( 
												  /* [in] */ HRESULT hresult,
												  /* [unique][in] */ LPCWSTR szError)
{
	return S_OK;
}

STDMETHODIMP CLXFrameworkFrame::GetBindInfo( 
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

STDMETHODIMP CLXFrameworkFrame::OnDataAvailable( 
													 /* [in] */ DWORD grfBSCF,
													 /* [in] */ DWORD dwSize,
													 /* [in] */ FORMATETC __RPC_FAR *pformatetc,
													 /* [in] */ STGMEDIUM __RPC_FAR *pstgmed)
{
#if 0
	m_bufferdata = (BYTE*)realloc(m_bufferdata, m_bufferlen + dwSize);
	if (m_bufferdata)
	{
		ULONG dwRead;
		pstgmed->pstm->Read(m_bufferdata+m_bufferlen, dwSize, &dwRead);

		//ATLASSERT(dwRead == dwSize);

		m_bufferlen += dwRead;

		return S_OK;
	}
	else
	{
		return E_OUTOFMEMORY;
	}
#endif
	return S_OK;
}

//void AddDocument(IUnknown* spUnknown, IActiveCntDocument* *pVal);

STDMETHODIMP CLXFrameworkFrame::OnObjectAvailable( 
														/* [in] */ REFIID riid,
														/* [iid_is][in] */ IUnknown __RPC_FAR *punk)
{
//	CComPtr<IActiveCntDocument> document;
	//AddDocument(punk, &document);
	/*
	CComObject<CActiveCntDocument>* document;
	CComObject<CActiveCntDocument>::CreateInstance(&document);
	if (document)
	{
		document->AddRef);
	}
	*/

#if 0
	HRESULT hr;

	m_spUnknown = punk;

	m_spOleObject = m_spUnknown;
	m_spOleDocument = m_spUnknown;

	hr = m_spOleObject->SetClientSite(this);
	hr = m_spOleObject->Advise(this, &m_dwAdvise);

//	hr = OleRun(m_spUnknown);

	CRect rc(0,0,300,300);
	//GetClientRect(&rc);
	hr = m_spOleObject->DoVerb(OLEIVERB_SHOW, NULL, this, 0, m_pUI->m_hWnd, &rc);
#endif

	return S_OK;
}

#if 0
// IHlinkFrame
STDMETHODIMP CLXFrameworkFrame::GetBrowseContext(IHlinkBrowseContext** ppihlbc)
{
	MessageBox("CLXFrameworkFrame::GetBrowseContext()", "", MB_OK);

	if (ppihlbc == NULL) return E_POINTER;
	*ppihlbc = m_hlinkBrowseContext;
	if (*ppihlbc) (*ppihlbc)->AddRef();
	return S_OK;
}

CComObject<CActiveCntDocument>* pActiveDocument = NULL;

STDMETHODIMP CLXFrameworkFrame::Navigate(DWORD grfHLNF, LPBC pbc, IBindStatusCallback* pibsc, IHlink* pihlNavigate)
{
	CComPtr<IHlinkSite> site;
	DWORD data;
	pihlNavigate->GetHlinkSite(&site, &data);
//	CComPtr<IBindCtx> bindctx;
//	hr = CreateAsyncBindCtx(NULL, this, NULL, &bindctx);

//	CComPtr<IBindStatusCallback> pbcPrev;
//	HRESULT hr = RegisterBindStatusCallback(pbc, this, &pbcPrev, 0);

	/*
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

	hr = RegisterMediaTypeClass(pbc, 4, rgszTypes, rgclsID, 0);
	ATLASSERT(SUCCEEDED(hr));
	*/

#if 0
	pihlNavigate->Navigate(grfHLNF, pbc, this/*pibsc*/, m_hlinkBrowseContext);

	/*
	ULONG uHLID;
	m_hlinkBrowseContext->OnNavigateHlink(grfHLNF, NULL, L"Test", L"Test", &uHLID);
	*/

	return S_OK;
#endif

	HRESULT hr;

	CComPtr<IMoniker> moniker;
//	LPWSTR location;
	hr = pihlNavigate->GetMonikerReference(HLINKGETREF_ABSOLUTE, &moniker, NULL/*&location*/);

//	if (pActiveDocument == NULL)
	{
		CComObject<CActiveCntDocument>* pDocSite;
		CComObject<CActiveCntDocument>::CreateInstance(&pDocSite);
		pDocSite->AddRef();

		pActiveDocument = pDocSite;
	}

	//m_app->BindToObjectMoniker(moniker, bindctx, &pDocSite->m_spUnknown);

	/*
	if (pActiveDocument->m_spUnknown)
	{
		pActiveDocument->m_spUnknown.Release
	}
	*/

	pActiveDocument->m_spUnknown.CoCreateInstance(CLSID_LHTMLActiveDocument);
	pActiveDocument->m_spOleObject = pActiveDocument->m_spUnknown;

	pActiveDocument->m_spOleObject->SetClientSite(pActiveDocument);

	/*
	CComPtr<IStream> stream;
	hr = moniker->BindToStorage(pbc, NULL, IID_IStream, (void**)&stream);
	if (SUCCEEDED(hr))
		*/
	{
		//*success = loadBuffer(m_bufferdata, m_bufferlen);

//		CComQIPtr<IEDocument> document;
//		document.CoCreateInstance(CLSID_EXMLDocument);

		CComQIPtr<IHlinkSite> site = pActiveDocument->m_spUnknown;
		pihlNavigate->SetHlinkSite(site, 0);

		CComQIPtr<IPersistMoniker> persistMoniker = pActiveDocument->m_spUnknown;
		persistMoniker->Load(FALSE, moniker, pbc, 0);

		pActiveDocument->Show(this);

		/*
		CComQIPtr<IHlinkTarget> target = pActiveDocument;//->m_spUnknown;

		target->SetBrowseContext(m_hlinkBrowseContext);

		target->Navigate(0, L"");
		*/

		/*
		DWORD dwRegistered;
		hr = m_hlinkBrowseContext->Register(0, target, moniker, &dwRegistered);


		CComQIPtr<IPersistStream> ifile = document;
		if (ifile != NULL)
		{
			HRESULT hr = ifile->Load(stream);
			if (SUCCEEDED(hr))
			{
				gApp->m_documents.Add(document);
				document->ShowViews();
				document.Detach();

			//	m_frame->ActivateObject(NULL, document);
			}
			else
			{
				MessageBox("Error loading file", "LXFramework", MB_OK);
			}
		}
		else
		{
			MessageBox("Document didn't support loading from stream", "LXFramework", MB_OK);
		}
		*/
	}

#if 0
	CComQIPtr<IEDocument> document;

	for (int i = 0; i < m_documents.GetSize(); i++)
	{
		BSTR pathName2;
		m_documents[i]->get_filePath(&pathName2);
		if (!wcsicmp(pathName, pathName2))
		{
			document = m_documents[i];
			break;
		}
	}

	if (document)
	{
		document->Activate();
	}
	else
	{
		TCHAR ext[512];
		_splitpath(_bstr_t(pathName), NULL, NULL, NULL, ext);

		if (
			!strnicmp(_bstr_t(pathName), "http", 4) ||
			!stricmp(ext, ".htm") ||
			!stricmp(ext, ".html") ||
			!stricmp(ext, ".shtml") ||
			!stricmp(ext, ".asp") ||

			!stricmp(ext, ".svg") ||

			!stricmp(ext, ".smil") ||
			!stricmp(ext, ".smi") ||

			!stricmp(ext, ".xslt") ||
			!stricmp(ext, ".xml") ||
			!stricmp(ext, ".xsd")/* ||

			!stricmp(ext, ".wmf") ||
			!stricmp(ext, ".emf")*/)
		{
			document.CoCreateInstance(CLSID_EXMLDocument);
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
			if ((StgIsStorageFile(_bstr_t(pathName)) == S_OK) ||
				!stricmp(ext, ".pddoc"))
			{
				document.CoCreateInstance(CLSID_ActiveCntDocument);
			}
			else
			{
				document.CoCreateInstance(CLSID_TextDocument);
			}
		}

		if (document != NULL)
		{
		//	m_frame->ActivateObject(NULL, document);

			CComQIPtr<IPersistFile> ifile = document;
			if (ifile != NULL)
			{
				HRESULT hr = ifile->Load(pathName, STGM_READ);
				if (SUCCEEDED(hr))
				{
					m_documents.Add(document);
					document->ShowViews();
					document.Detach();

				//	m_frame->ActivateObject(NULL, document);
				}
				else
				{
					MessageBox(NULL, "Error loading file", "LXFramework", MB_OK);
				}
			}
			else
			{
				MessageBox(NULL, "Document didn't support loading from file", "LXFramework", MB_OK);
			}
		}
		else
		{
			MessageBox(NULL, "Couldn't create document object", "LXFramework", MB_OK);
		}
	}
#endif

	return S_OK;
}

STDMETHODIMP CLXFrameworkFrame::OnNavigate(DWORD grfHLNF, IMoniker* pimkTarget, LPCWSTR pwzLocation, LPCWSTR pwzFriendlyName, DWORD dwreserved)
{
#ifdef _DEBUG
	MessageBox("CLXFrameworkFrame::IHlinkFrame::OnNavigate()", "", MB_OK);
#endif
	return S_OK;
}

STDMETHODIMP CLXFrameworkFrame::SetBrowseContext(IHlinkBrowseContext* phlbc)
{
#ifdef _DEBUG
	MessageBox("CLXFrameworkFrame::SetBrowseContext()", "");
#endif

	m_hlinkBrowseContext = phlbc;

	return S_OK;
}

STDMETHODIMP CLXFrameworkFrame::UpdateHlink(ULONG uHLID, IMoniker* pimkTarget, LPCWSTR pwzLocation, LPCWSTR pwzFriendlyName)
{
	ATLASSERT(0);
	return E_NOTIMPL;
}
#endif

STDMETHODIMP CLXFrameworkFrame::OpenDocument(/*[in]*/ IMoniker *pmk)
{
	HRESULT hr;

	CComObject<CLXFrameworkAddinSite>* pAddinSite;
	CComObject<CLXFrameworkAddinSite>::CreateInstance(&pAddinSite);
	if (pAddinSite)
	{
		pAddinSite->AddRef();

		if (SUCCEEDED(pAddinSite->m_p.CoCreateInstance(L"LXMLEditor.LXMLEditorApp")))
		{
			pAddinSite->AddRef();

			pAddinSite->SetFrame(this);

			pAddinSite->m_name = L"LXMLEditorApp";
			m_addins.Add(pAddinSite);

			pAddinSite->m_p->SetSite(pAddinSite);
		}
	}

	CComPtr<IBindCtx> bindctx;
//	hr = CreateAsyncBindCtx(NULL, this, NULL, &bindctx);
	hr = CreateBindCtx(0, &bindctx);
	if (SUCCEEDED(hr))
	{
		CComPtr<IUnknown> document;
		hr = pAddinSite->m_p->BindToObjectMoniker(pmk, bindctx, &document);
	}

	return hr;
}

STDMETHODIMP CLXFrameworkFrame::OpenDocument(BSTR pathName, VARIANT_BOOL *success)
{
#if 0
#if 0
	HRESULT hr;

	hr = HlinkCreateBrowseContext(NULL, IID_IHlinkBrowseContext, (void**)&m_frame->m_hlinkBrowseContext);

	CComPtr<IMoniker> moniker;
	hr = CreateURLMoniker(NULL, pathName, &moniker);
	if (SUCCEEDED(hr))
	{
		CComPtr<IBindCtx> bindctx;
		hr = CreateBindCtx(0, &bindctx);
		if (SUCCEEDED(hr))
		{
			CComPtr<IHlink> hlink;

			hr = HlinkCreateFromMoniker(
				moniker,
				NULL, // pwzLocation
				L"test",	// friendlyName
				NULL,//&hlsite,
				0,	// siteData
				NULL,
				IID_IHlink,
				(void**)&hlink);

			::HlinkNavigate(hlink, m_frame, 0, bindctx, NULL, m_frame->m_hlinkBrowseContext);
		}
	}
#endif

	CComObject<CActiveCntDocument>* pDocSite = NULL;

#if 0
	for (int i = 0; i < m_documents.GetSize(); i++)
	{
		CComBSTR pathName2;
		m_documents[i]->get_filePath(&pathName2);
		if (pathName2.Length())
		{
			if (!wcsicmp(pathName, pathName2))
			{
				document = m_documents[i];
				break;
			}	
		}
	}
#endif

	if (pDocSite)
	{
#if 0
		document->Activate();
#endif
	}
	else
	{
		CComObject<CActiveCntDocument>::CreateInstance(&pDocSite);
		pDocSite->AddRef();

		if (pDocSite != NULL)
		{
		//	m_frame->ActivateObject(NULL, document);

			CComQIPtr<IPersistFile> ifile = pDocSite;
			if (ifile != NULL)
			{
				HRESULT hr = ifile->Load(pathName, STGM_READ);
				if (SUCCEEDED(hr))
				{
					m_documents.Add(pDocSite);
					pDocSite->Show(this);
				//	document.Detach();

				//	m_frame->ActivateObject(NULL, document);
				}
				else
				{
					MessageBox("Error loading file", "LXFramework", MB_OK);
				}
			}
			else
			{
				MessageBox("Document didn't support loading from file", "LXFramework", MB_OK);
			}
		}
		else
		{
			MessageBox("Couldn't create document object", "LXFramework", MB_OK);
		}
	}
#endif

	return S_OK;
}

BEGIN_CMD_MAP(CLXFrameworkFrame)

	CMD_HANDLER(ID_FILE_ADDSNAPIN, OnAddSnapin)

	CMD_HANDLER(ID_FILE_OPEN, OnFileOpen)
	CMD_HANDLER(ID_FILE_SAVEAS, OnFileSaveAs)

	CMD_HANDLER(ID_FILE_OPTIONS, OnFileOptions)

	CMD_HANDLER(ID_APP_EXIT, OnAppExit)
	/*
	CMD_HANDLER(ID_NAVIGATE_BACK, OnNavigateBack)
	CMD_HANDLER(ID_NAVIGATE_FORWARD, OnNavigateForward)
	CMD_UPDATE(ID_NAVIGATE_BACK, OnNavigateBackUpdate)
	CMD_UPDATE(ID_NAVIGATE_FORWARD, OnNavigateForwardUpdate)
	*/
END_CMD_MAP()

#include "AddinsDlg.h"

LRESULT CLXFrameworkFrame::OnAddSnapin(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CAddinsDlg dlg;
	dlg.m_pFrame = this;

	dlg.DoModal();

	return 0;
}

#include "FrameworkOptionsDlg.h"

LRESULT CLXFrameworkFrame::OnFileOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CPropertySheet sheet("Options", 0);
	sheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	CFrameworkOptionsDlg	fopts;
	//fopts.m_app = this;

	sheet.AddPage(fopts);

	if (sheet.DoModal() == IDOK)
	{
	}

	return 0;
}

LRESULT CLXFrameworkFrame::OnFileOpen(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	static LPCTSTR FilesFilter = _T(	
												"LXFramework Files (*.lxf)\0*.lxf\0"
												"All Files (*.*)\0*.*\0"
												);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, "");	// Initial filename
	
	TCHAR curdir[MAX_PATH];
	GetCurrentDirectory(sizeof(curdir), curdir);

	OPENFILENAME	ofn = {0};
	ofn.lStructSize = OPENFILENAME_SIZE_VERSION_400;//sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;//m_hWnd;
	ofn.hInstance = _Module.m_hInst;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = sizeof(sbuffer);
	ofn.lpstrInitialDir = curdir;
	ofn.lpstrFilter = FilesFilter;
	
	if (GetOpenFileName(&ofn))
	{
		HRESULT hr = OpenFramework(sbuffer);

		if (FAILED(hr))
		{
			::MessageBox(NULL, "Couldn't open framework", "LXFramework", MB_OK | MB_ICONERROR);
		}
	}

	return 0;
}

LRESULT CLXFrameworkFrame::OnFileSaveAs(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	static LPCTSTR FilesFilter = _T(	
												"LXFramework Files (*.lxf)\0*.lxf\0"
												"All Files (*.*)\0*.*\0"
												);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, "");	// Initial filename
	
	TCHAR curdir[MAX_PATH];
	GetCurrentDirectory(sizeof(curdir), curdir);

	OPENFILENAME	ofn = {0};
	ofn.lStructSize = OPENFILENAME_SIZE_VERSION_400;//sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;//m_hWnd;
	ofn.hInstance = _Module.m_hInst;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = sizeof(sbuffer);
	ofn.lpstrInitialDir = curdir;
	ofn.lpstrFilter = FilesFilter;
	
	if (GetSaveFileName(&ofn))
	{
		HRESULT hr = SaveFramework(sbuffer);

		if (FAILED(hr))
		{
			::MessageBox(NULL, "Couldn't save framework", "LXFramework", MB_OK | MB_ICONERROR);
		}
	}

	return 0;
}

HRESULT CLXFrameworkFrame::OpenFramework(LPCTSTR filename)
{
	HRESULT hr = E_FAIL;

	HANDLE hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile)
	{
		DWORD nRead;

		DWORD signature;
		ReadFile(hFile, &signature, 4, &nRead, NULL);

		if (signature == 'rfxl')
		{
			DWORD version;
			ReadFile(hFile, &version, 4, &nRead, NULL);
			if (version == 0)
			{
				DWORD nAddins;
				ReadFile(hFile, &nAddins, 4, &nRead, NULL);

				CRegKey clsidkey;
				clsidkey.Open(HKEY_CLASSES_ROOT, "CLSID");

				for (int i = 0; i < nAddins; i++)
				{
					CLSID clsid;
					ReadFile(hFile, &clsid, sizeof(clsid), &nRead, NULL);

					CComObject<CLXFrameworkAddinSite>* pAddinSite;
					CComObject<CLXFrameworkAddinSite>::CreateInstance(&pAddinSite);
					if (pAddinSite)
					{
						pAddinSite->AddRef();

						if (SUCCEEDED(pAddinSite->m_p.CoCreateInstance(clsid)))
						{
							pAddinSite->AddRef();

							pAddinSite->m_clsid = clsid;

							// Get name
							{
								LPOLESTR clsidstr;
								StringFromCLSID(clsid, &clsidstr);

								CRegKey key;
								key.Open(clsidkey, _bstr_t(clsidstr));

								CoTaskMemFree(clsidstr);

								TCHAR name[256];
								DWORD n = 255;
								key.QueryValue(name, NULL, &n);

								pAddinSite->m_name = name;
							}

							pAddinSite->SetFrame(this);

							m_addins.Add(pAddinSite);

							pAddinSite->m_p->SetSite(pAddinSite);
						}
						else
						{
							//MessageBox("Failed to load Add-in", "LXFramework", MB_OK);
						}

						pAddinSite->Release();
					}
				}

				hr = S_OK;
			}
		}

		CloseHandle(hFile);
	}

	return hr;
}

HRESULT CLXFrameworkFrame::SaveFramework(LPCTSTR filename)
{
	CComPtr<IStorage> storage;
	StgCreateDocfile(_bstr_t(filename), STGM_CREATE, 0, &storage);
	if (storage)
	{
		CComPtr<IStream> stream;
		storage->CreateStream(L"Content", STGM_CREATE, 0, 0, &stream);
		if (stream)
		{
			ULONG nWritten;

		// Signature and version
			DWORD signature = 'rfxl';	// lxfr
			DWORD version = 0;
			stream->Write(&signature, 4, &nWritten);
			stream->Write(&version, 4, &nWritten);

		// Addins
			DWORD nAddins = m_addins.GetSize();
			stream->Write(&nAddins, sizeof(nAddins), &nWritten);

			for (int i = 0; i < nAddins; i++)
			{
				stream->Write(&m_addins[i]->m_clsid, sizeof(m_addins[i]->m_clsid), &nWritten);

				ATLASSERT(0);
#if 0
				m_addins[i]->m_uiManager->Save(stream);
#endif
			}

			return S_OK;
		}
	}

	return E_FAIL;
}

STDMETHODIMP CLXFrameworkFrame::get_Element(/*[in]*/ ILXUIMDIFrameElement* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_element;
	(*pVal)->AddRef();
	return S_OK;
}

/*
LRESULT CLXFrameworkFrame::OnNavigateBack(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

LRESULT CLXFrameworkFrame::OnNavigateForward(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

void CLXFrameworkFrame::OnNavigateBackUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	if (m_hlinkBrowseContext)
	{
		if(m_hlinkBrowseContext->QueryHlink(HLQF_ISVALID,HLID_PREVIOUS)==S_OK)
			bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}

void CLXFrameworkFrame::OnNavigateForwardUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	if (m_hlinkBrowseContext)
	{
		if(m_hlinkBrowseContext->QueryHlink(HLQF_ISVALID,HLID_NEXT)==S_OK)
			bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}
*/

#if 0
// ILDOMEventListener
STDMETHODIMP CLXFrameworkFrame::handleEvent(ILDOMEvent* evt)
{
	CComQIPtr<ILDOMUIEvent> uievt = evt;
	if (uievt)
	{
		long cmdid;
		uievt->get_detail(&cmdid);

		{
			WORD nCode = WM_COMMAND;
			WORD nID = (WORD)cmdid;
			const CmdEntry* entry = GetCmdEntries();

		//	if (nCode != -1)
			{
				HWND hWnd = NULL;
#if 0
				if (pCmdUI) pCmdUI->get_hwndControl(&hWnd);

				*bHandled = FALSE;
#endif

				while (entry->iid != 0)
				{
					if (entry->type == 1)
					{
						if (nID == entry->iid)
						{
							BOOL bHandled2 = TRUE;
							(this->*entry->func)((WORD)nCode, (WORD)nID, hWnd, bHandled2);

#if 0
							*bHandled = bHandled2;
#endif
							return S_OK;
						}
					}
					entry++;
				}
			}
		}
	}
	return S_OK;
}
#endif

#if 0
STDMETHODIMP CLXFrameworkFrame::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
	if (bHandled == NULL) return E_POINTER;

// Try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Try base
	ATLASSERT(0);
#if 0
	baseClass::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;
#endif

// Try App
	CComQIPtr<ICommandTarget> app = gIApp;
	app->OnCmdMsg(nID, nCode, pCmdUI, bHandled);

	return S_OK;
}
#endif

LRESULT CLXFrameworkFrame::OnAppExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	PostMessage(WM_CLOSE);
#endif
	return 0;
}

#endif
