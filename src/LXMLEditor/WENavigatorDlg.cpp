// WENavigatorDlg.cpp : Implementation of CWENavigatorDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "WENavigatorDlg.h"

#include "EXMLDocument.h"
#include "EXMLViewGroup.h"
#include "EXMLLayoutView.h"

#include "LXMLEditorApp.h"

#if 0

/////////////////////////////////////////////////////////////////////////////
// CWENavigatorDlg

/*

The following formula shows the math involved in converting a
point from page space to device space.

Dx = ((Lx - WOx) * VEx / WEx) + VOx 
 
The following variables are involved.

Dx     x value in device units 
Lx     x value in logical units (also known as page space units) 
WOx     window x origin 
VOx     viewport x origin 
WEx     window x-extent 
VEx     viewport x-extent 
 
*/

int CWENavigatorDlg::FinalConstruct()
{
	return S_OK;
}

void CWENavigatorDlg::FinalRelease()
{
}

STDMETHODIMP CWENavigatorDlg::OnActivate(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView)
{
	CEXMLLayoutView* layoutView = static_cast<CEXMLLayoutView*>(m_layoutView.p);

	if (bActivate)
	{
		CComQIPtr<ILHTMLActiveView> htmlview = layoutView->m_pIOleDocView;
		CComPtr<ILHTMLWindow> window;
		htmlview->GetHTMLWindow(&window);
		IDispEventImpl<4, CWENavigatorDlg, &DIID__ILHTMLWindowEvents, &LIBID_LHTMLLib, 1, 0>::DispEventAdvise(window);

		OnChangeViewBox();
	}
	else
	{
		CComQIPtr<ILHTMLActiveView> htmlview = layoutView->m_pIOleDocView;
		CComPtr<ILHTMLWindow> window;
		htmlview->GetHTMLWindow(&window);
		IDispEventImpl<4, CWENavigatorDlg, &DIID__ILHTMLWindowEvents, &LIBID_LHTMLLib, 1, 0>::DispEventUnadvise(window);
	}

	return S_OK;
}

LRESULT CWENavigatorDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	/*
	CComQIPtr<ILXAddin> lxapp = m_app;

	CComQIPtr<ILXAddinSite> site;
	lxapp->GetSite(&site);

	CComPtr<IUIManager> uiManager;
	site->GetUIManager((IUnknown**)&uiManager);
*/

	m_font.CreateFont(11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Small Fonts");

//	m_edit.Create(m_hWnd, CRect(0, 0, 50, 16), NULL, WS_CHILD | WS_BORDER, WS_EX_CLIENTEDGE, 1/*id*/);
//	m_cnedit.SubclassWindow(m_edit);
	m_cnedit.Create(m_hWnd, &CRect(0, 0, 50, 16), NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, WS_EX_CLIENTEDGE, 1/*id*/);
	m_cnedit.SetFont(m_font);

	m_sizeGrip.Create(m_hWnd, CRect(0, 0, 0, 0), NULL, WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP);//, , m_hWnd, 1/*NULL, _Module.m_hInst, NULL*/);

	/*
	ATLASSERT();
	if (m_layoutView)
	{
	// Listen to document events
		CComQIPtr<IEXMLDocument> webDocument;
		m_layoutView->get_ESvgDocument(&webDocument);
		IDispEventImpl<2, CWENavigatorDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(webDocument);
	}
	*/

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->AddEventHandler(this);

	CEXMLLayoutView* layoutView = static_cast<CEXMLLayoutView*>(m_layoutView.p);

	CComPtr<IEXMLDocument> eDocument = layoutView->m_viewGroup->m_pDocument;
	IDispEventImpl<2, CWENavigatorDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(eDocument);

	m_cnedit.ShowWindow(SW_SHOW);

#if 0
	_Module.GetMessageLoop()->AddIdleHandler(this);
#endif

	return 0;
}

LRESULT CWENavigatorDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	_Module.GetMessageLoop()->RemoveIdleHandler(this);
#endif

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->RemoveEventHandler(this);

//	if (m_layoutView)
	{
	// Don't listen to this document events anymore
		CComQIPtr<IEXMLDocument> eDocument;
		m_layoutView->get_ESvgDocument(&eDocument);
		IDispEventImpl<2, CWENavigatorDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(eDocument);
	}

//	m_cnedit.UnsubclassWindow();
	m_cnedit.DestroyWindow();
	m_font.DeleteObject();

	return 0;
}

LRESULT CWENavigatorDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	CPaintDC dc(m_hWnd);
//	HDC hDC = dc.m_hDC;

	CRect client;
	GetClientRect(&client);

	if (m_layoutView)
	{
		/*
		CComQIPtr<IWebXMLDocument> esvgDocument;
		m_layoutView->get_ESvgDocument(&esvgDocument);
		*/

		CEXMLLayoutView* layoutView = static_cast<CEXMLLayoutView*>(m_layoutView.p);
		CComQIPtr<ILHTMLActiveView> htmlview = layoutView->m_pIOleDocView;
		if (htmlview)
		{
			CComPtr<ILHTMLWindow> window;
			htmlview->GetHTMLWindow(&window);

			CEXMLDocument* pDocument = static_cast<CEXMLDocument*>(layoutView->m_viewGroup->m_pDocument);

			CComPtr<ILDOMDocument> doc;
			pDocument->get_DOMDocument(&doc);

			LSVG::SVGDocument* svgdoc = doc;

			if (svgdoc)
			{
				CComQIPtr<ILSVGSVGElement> svg;
				svgdoc->get_documentElement((ILDOMElement**)&svg);
				if (svg)
				{
					int state = dc.SaveDC();

					double docwidth;
					double docheight;
					window->get_contentWidth(&docwidth);//= pDocument->GetWidth();
					window->get_contentHeight(&docheight);//= pDocument->GetHeight();

					/*
					int fullwidth = docwidth+400;
					int fullheight = docheight+100;
					*/

					CRect rect;
					rect.left = 3 + (client.Width()-6-m_size.cx)/2;
					rect.top = 3 + (client.Height()-6-16-m_size.cy)/2;
					rect.right = rect.left + m_size.cx;
					rect.bottom = rect.top + m_size.cy;

					CRect brect = rect;

					//FillSolidRect(hDC, &rect, RGB(255, 255, 255));

					brect.InflateRect(1, 1);
					dc.Draw3dRect(&brect, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DLIGHT));

					brect.InflateRect(1, 1);
					dc.Draw3dRect(&brect, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHILIGHT));

					if (dc.IntersectClipRect(rect.left, rect.top, rect.right, rect.bottom) > NULLREGION)
					{
						if (m_offbm)
						{
							BITMAP bm;
							m_offbm.GetBitmap(&bm);

							if (bm.bmWidth != rect.Width() || bm.bmHeight != rect.Height())
							{
								m_offbm.DeleteObject();
							}
						}

						if (m_offbm == NULL)
						{
							m_offbm.CreateCompatibleBitmap(dc, rect.Width(), rect.Height());
							m_bRedraw = true;
						}


						int x = 100 * m_magnify;
						int y = 100 * m_magnify;

						if (m_bRedraw)
						{
							CDC dc2;
							dc2.CreateCompatibleDC(dc);
							HBITMAP hOldBitmap = (HBITMAP)dc2.SelectBitmap(m_offbm);

							dc2.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));

							CPoint oldOrg = dc2.SetViewportOrg(x, y);

							CRect prect(0, 0, docwidth*m_magnify, docheight*m_magnify);

							HBRUSH hOldBrush = (HBRUSH)SelectObject(dc2.m_hDC, GetStockObject(NULL_BRUSH));
							Rectangle(dc2.m_hDC, prect.left, prect.top, prect.right, prect.bottom);
							SelectObject(dc2.m_hDC, hOldBrush);

							window->DrawToHdc4(dc2.m_hDC, svg, m_magnify);

							dc2.SetViewportOrg(oldOrg.x, oldOrg.y);

							m_bRedraw = false;

							dc2.SelectBitmap(hOldBitmap);
						}

						if (m_offbm)
						{
							CDC dc2;
							dc2.CreateCompatibleDC(dc);
							HBITMAP hOldBitmap = (HBITMAP)dc2.SelectBitmap(m_offbm);

							dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), dc2, 0, 0, SRCCOPY);

							dc2.SelectBitmap(hOldBitmap);
						}

						dc.SetViewportOrg(rect.left+x, rect.top+y);

					// Draw visible viewRect
						{
							CRect viewBox = GetViewBox();

							CRect viewRect = viewBox;
							viewRect.left *= m_magnify;
							viewRect.top *= m_magnify;
							viewRect.right *= m_magnify;
							viewRect.bottom *= m_magnify;

							viewRect.InflateRect(1, 1);

							HPEN hPen = CreatePen(PS_SOLID, 2, m_viewBoxColor);
							HPEN hOldPen = (HPEN)SelectObject(dc.m_hDC, hPen);
							HBRUSH hOldBrush = (HBRUSH)SelectObject(dc.m_hDC, GetStockObject(NULL_BRUSH));

							Rectangle(dc.m_hDC, viewRect.left, viewRect.top, viewRect.right, viewRect.bottom);

							SelectObject(dc.m_hDC, hOldBrush);
							SelectObject(dc.m_hDC, hOldPen);
							DeleteObject(hPen);
						}
					}

					dc.RestoreDC(state);
				}
			}
		}
	}

	m_bUpdate = false;
#endif

	return 0;
}

LRESULT CWENavigatorDlg::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HDC hDC = (HDC)wParam;

	CRect client;
	GetClientRect(&client);

	int state = SaveDC(hDC);

	if (m_layoutView)
	{
		CRect rect;
		rect.left = 3 + (client.Width()-6-m_size.cx)/2;
		rect.top = 3 + (client.Height()-6-16-m_size.cy)/2;
		rect.right = rect.left + m_size.cx;
		rect.bottom = rect.top + m_size.cy;

		rect.InflateRect(2, 2);

		ExcludeClipRect(hDC, rect.left, rect.top, rect.right, rect.bottom);
	}

	FillSolidRect(hDC, &client, GetSysColor(COLOR_BTNFACE));

	RestoreDC(hDC, state);

	return TRUE;
}

LRESULT CWENavigatorDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CRect client;
	GetClientRect(&client);

	if (!m_dragging)
	{
		if (m_layoutView)
		{
			CEXMLLayoutView* layoutView = static_cast<CEXMLLayoutView*>(m_layoutView.p);
			CComQIPtr<ILHTMLActiveView> htmlview = layoutView->m_pIOleDocView;
			CComPtr<ILHTMLWindow> window;
			htmlview->GetHTMLWindow(&window);

		//	if (svgdoc)
			{
				int left = 100*m_magnify + 3 + (client.Width()-6-m_size.cx)/2;
				int top = 100*m_magnify + 3 + (client.Height()-6-16-m_size.cy)/2;
			//	int left = 200*m_magnify + 3 + (client.Width()-6-m_size.cx)/2;
			//	int top = 50*m_magnify + 3 + (client.Height()-6-m_size.cy)/2;

				POINT cpt;
				cpt.x = point.x-left;
				cpt.y = point.y-top;

				CRect viewBox = GetViewBox();

				CRect viewRect = viewBox;

				viewRect.left *= m_magnify;
				viewRect.top *= m_magnify;
				viewRect.right *= m_magnify;
				viewRect.bottom *= m_magnify;

				if (PtInRect(&viewRect, cpt))
				{
					m_offset.x = (cpt.x/m_magnify) - viewBox.left;
					m_offset.y = (cpt.y/m_magnify) - viewBox.top;
				}
				else
				{
					m_offset.x = viewBox.Width()/2;
					m_offset.y = viewBox.Height()/2;

					double currentScale;
					window->get_magnify(&currentScale);

					int cx = ((cpt.x/m_magnify) - m_offset.x) * currentScale;
					int cy = ((cpt.y/m_magnify) - m_offset.y) * currentScale;

					window->setCurrentTranslate(-cx, -cy);
				}

				SetCursor(LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_HAND2)));

				m_dragging = TRUE;
				SetCapture();
			}
		}
	}
#endif

	return 0;
}

LRESULT CWENavigatorDlg::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		ReleaseCapture();
		m_dragging = FALSE;
	}

	return 0;
}

LRESULT CWENavigatorDlg::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CRect client;
	GetClientRect(&client);

	if (m_dragging)
	{
		ATLASSERT(m_layoutView);
		CEXMLLayoutView* layoutView = static_cast<CEXMLLayoutView*>(m_layoutView.p);
		CComQIPtr<ILHTMLActiveView> htmlview = layoutView->m_pIOleDocView;
		CComPtr<ILHTMLWindow> window;
		htmlview->GetHTMLWindow(&window);
		{
			{

				int left = 100*m_magnify + 3 + (client.Width()-6-m_size.cx)/2;
				int top = 100*m_magnify + 3 + (client.Height()-6-16-m_size.cy)/2;

				POINT cpt;
				cpt.x = point.x-left;
				cpt.y = point.y-top;

				double currentScale;
				window->get_magnify(&currentScale);

				int cx = ((cpt.x/m_magnify) - m_offset.x) * currentScale;
				int cy = ((cpt.y/m_magnify) - m_offset.y) * currentScale;

				window->setCurrentTranslate(-cx, -cy);
			}
		}
	}
#endif

	return 0;
}

void CWENavigatorDlg::OnSize()
{
	ATLASSERT(0);
#if 0
	CRect client;
	GetClientRect(&client);

	client.right -= 6;
	client.bottom -= 6+16;

	m_size.cx = 0;
	m_size.cy = 0;

	CEXMLLayoutView* layoutView = static_cast<CEXMLLayoutView*>(m_layoutView.p);

	ATLASSERT(layoutView->m_hWnd);
	if (layoutView->m_hWnd)	// hm.. layoutview isn't activated yet?
	{
		CComQIPtr<ILHTMLActiveView> htmlview = layoutView->m_pIOleDocView;
		CComPtr<ILHTMLWindow> window;
		htmlview->GetHTMLWindow(&window);

		double docwidth;
		double docheight;
		window->get_contentWidth(&docwidth);
		window->get_contentHeight(&docheight);

		int fullwidth = docwidth+200;
		int fullheight = docheight+200;

		m_size.cx = client.Width();
		m_size.cy = (m_size.cx*fullheight)/fullwidth;

		if (m_size.cy > client.Height())
		{
			m_size.cy = client.Height();
			m_size.cx = (m_size.cy*fullwidth)/fullheight;
		}

		m_magnify = (double)m_size.cx/fullwidth;
	}
#endif
}

LRESULT CWENavigatorDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_cnedit.SetWindowPos(NULL, 0, client.bottom-16, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	m_sizeGrip.MoveWindow(client.right-16, client.bottom-16, 16, 16);

	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

LRESULT CWENavigatorDlg::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = (HWND) wParam;       // handle to window with cursor 
	UINT nHittest = LOWORD(lParam);  // hit-test code 
	UINT wMouseMsg = HIWORD(lParam); // mouse-message identifier 
 
	if (nHittest == HTCLIENT)
	{
		CRect client;
		GetClientRect(&client);

		POINT point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		if (m_layoutView)
		{
			CRect rect;
			rect.left = 3 + (client.Width()-6-m_size.cx)/2;
			rect.top = 3 + (client.Height()-6-16-m_size.cy)/2;
			rect.right = rect.left + m_size.cx;
			rect.bottom = rect.top + m_size.cy;

			if (rect.PtInRect(point))
			{
				int left = 100*m_magnify + 3 + (client.Width()-6-m_size.cx)/2;
				int top = 100*m_magnify + 3 + (client.Height()-6-m_size.cy)/2;

				POINT cpt;
				cpt.x = point.x-left;
				cpt.y = point.y-top;

				CRect viewBox = GetViewBox();

				CRect viewRect = viewBox;

				viewRect.left *= m_magnify;
				viewRect.top *= m_magnify;
				viewRect.right *= m_magnify;
				viewRect.bottom *= m_magnify;

				if (PtInRect(&viewRect, cpt))
				{
					SetCursor(LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_HAND0)));
					return TRUE;
				}
				else
				{
					SetCursor(LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_HAND1)));
					return TRUE;
				}
			}
		}
	}

	return DefWindowProc(uMsg, wParam, lParam);
}

LRESULT CWENavigatorDlg::OnEditKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	if ((uMsg == WM_KILLFOCUS) ||
		(uMsg == WM_KEYDOWN && wParam == VK_RETURN))
	{
		if (m_layoutView)
		{
			TCHAR buf[64];
			m_cnedit.GetWindowText(buf, sizeof(buf));

			double newscale = atof(buf) / 100;

			CEXMLLayoutView* layoutView = static_cast<CEXMLLayoutView*>(m_layoutView.p);
			CComQIPtr<ILHTMLActiveView> htmlview = layoutView->m_pIOleDocView;
			CComPtr<ILHTMLWindow> window;
			htmlview->GetHTMLWindow(&window);

			long innerWidth;
			long innerHeight;
			window->get_innerWidth(&innerWidth);
			window->get_innerHeight(&innerHeight);

			double oldscale;
			window->get_magnify(&oldscale);

			window->ZoomToRect(
				innerWidth/2 - innerWidth*oldscale/newscale/2,
				innerHeight/2 - innerHeight*oldscale/newscale/2,
				innerWidth*oldscale/newscale,
				innerHeight*oldscale/newscale,
				VARIANT_TRUE);
		}

		if (uMsg == WM_KEYDOWN)
			return 0;
	}

	return m_cnedit.DefWindowProc(uMsg, wParam, lParam);
#endif
	return 0;
}

CRect CWENavigatorDlg::GetViewBox()
{
	ATLASSERT(0);
#if 0
	if (m_layoutView)
	{
		CEXMLLayoutView* layoutView = static_cast<CEXMLLayoutView*>(m_layoutView.p);
		CComQIPtr<ILHTMLActiveView> htmlview = layoutView->m_pIOleDocView;
		CComPtr<ILHTMLWindow> window;
		htmlview->GetHTMLWindow(&window);

		CRect viewBox;

		double currentTranslateX;
		double currentTranslateY;
		double magnify;
		long innerWidth;
		long innerHeight;

		window->get_currentTranslateX(&currentTranslateX);
		window->get_currentTranslateY(&currentTranslateY);
		window->get_magnify(&magnify);
		window->get_innerWidth(&innerWidth);
		window->get_innerHeight(&innerHeight);

		viewBox.left = -currentTranslateX/magnify;
		viewBox.top = -currentTranslateY/magnify;
		viewBox.right = -currentTranslateX/magnify + innerWidth/magnify;
		viewBox.bottom = -currentTranslateY/magnify + innerHeight/magnify;

		return viewBox;
	}
#endif

	return CRect(0,0,0,0);
}

//virtual
BOOL CWENavigatorDlg::OnIdle()
{
	if (m_bRedraw)
	{
		Invalidate();
	}

#if 0
	if (m_bUpdate)
	{
		Invalidate();
	}
#endif
	return FALSE;
}

HRESULT __stdcall CWENavigatorDlg::OnDOMEvent(ILDOMEvent* evt)
{
//	OnSize();

	m_bRedraw = true;
//	InvalidateRect(NULL, TRUE);

	return S_OK;
}

void CWENavigatorDlg::OnChangeViewBox()
{
	ATLASSERT(0);
#if 0
	if (m_hWnd)
	{
		if (m_layoutView)
		{
			CEXMLLayoutView* layoutView = static_cast<CEXMLLayoutView*>(m_layoutView.p);
			CComQIPtr<ILHTMLActiveView> htmlview = layoutView->m_pIOleDocView;
			CComPtr<ILHTMLWindow> window;
			htmlview->GetHTMLWindow(&window);

			double magnify;
			window->get_magnify(&magnify);

			TCHAR buf[32];
			sprintf(buf, "%g%%", magnify*100);
			m_cnedit.SetWindowText(buf);
		}
	}

	if (m_hWnd)
	{
		OnSize();
		InvalidateRect(NULL, TRUE);
	}
#endif
}

#if 0
// IUIEventHandler
STDMETHODIMP CWENavigatorDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLLayoutView> view = object;
	if (view)
	{
		ATLASSERT(m_layoutView == NULL);
		m_layoutView = view;

		CEXMLLayoutView* layoutView = static_cast<CEXMLLayoutView*>(m_layoutView.p);
		CComQIPtr<ILHTMLActiveView> htmlview = layoutView->m_pIOleDocView;
		if (htmlview)
		{
			CComPtr<ILHTMLWindow> window;
			htmlview->GetHTMLWindow(&window);
			if (window)
			{
				CComPtr<IEXMLDocument> eDocument = layoutView->m_document;
				IDispEventImpl<2, CWENavigatorDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(eDocument);

				IDispEventImpl<4, CWENavigatorDlg, &DIID__ILHTMLWindowEvents, &LIBID_LHTMLLib, 1, 0>::DispEventAdvise(window);

				OnChangeViewBox();

				m_cnedit.ShowWindow(SW_SHOW);

				*cookie = 1;
			}
		}
	}

	return S_OK;
}

STDMETHODIMP CWENavigatorDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ATLASSERT(m_layoutView != NULL);

	CEXMLLayoutView* layoutView = static_cast<CEXMLLayoutView*>(m_layoutView.p);
	CComQIPtr<ILHTMLActiveView> htmlview = layoutView->m_pIOleDocView;
	CComPtr<ILHTMLWindow> window;
	htmlview->GetHTMLWindow(&window);

	CComPtr<IEXMLDocument> eDocument = layoutView->m_document;
	IDispEventImpl<2, CWENavigatorDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(eDocument);

	IDispEventImpl<4, CWENavigatorDlg, &DIID__ILHTMLWindowEvents, &LIBID_LHTMLLib, 1, 0>::DispEventUnadvise(window);

	m_layoutView.Release();

	m_cnedit.ShowWindow(SW_HIDE);

	if (m_hWnd)
	{
		OnSize();
		InvalidateRect(NULL, TRUE);
	}

	return S_OK;
}
#endif

BEGIN_CMD_MAP(CWENavigatorDlg)
	CMD_HANDLER(ID_NAVIGATOR_PALETTEOPTIONS, OnPaletteOptions)
END_CMD_MAP()

#include "NavigatorOptionsDlg.h"

LRESULT CWENavigatorDlg::OnPaletteOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CNavigatorOptionsDlg dlg;
	dlg.m_color = m_viewBoxColor;

	if (dlg.DoModal() == IDOK)
	{
		m_viewBoxColor = dlg.m_color;
		Invalidate();
	}

	return 0;
}

#endif