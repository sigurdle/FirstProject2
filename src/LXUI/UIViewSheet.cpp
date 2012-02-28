#include "stdafx.h"
//#include "UITImpl.h"

#if 0

#include "LXUI.h"
#include "LHTML2.h"

#include "UIViewSheet.h"

#include "DragContext.h"

///////////////////////////////////////////////////////////////////////////
// CUIViewSheet

LRESULT CUIViewSheet::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(m_pDlgSite);

	SetProp(m_hWnd, "mmsx_sheet", (HANDLE)static_cast<IUIDockBar*>(this));

	if (TRUE)
	{
		m_font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	}
	else
	{
		m_font.CreateFont(11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Small Fonts");
	}

	LOGFONT lf;
	m_font.GetLogFont(&lf);

	lf.lfWeight = FW_BOLD;
	m_boldfont.CreateFontIndirect(&lf);

	//CalculateTabWidths();

	if (OnCreate())
		return -1;

	if (m_pView)
	{
		HWND hwndview;
		m_pView->get_hwnd(&hwndview);

		::SetActiveWindow(hwndview);
		::SetFocus(hwndview);

	//	m_pView->OnActivate(TRUE, NULL, NULL);
	}

	return 0;
}

LRESULT CUIViewSheet::OnCreate()
{
	if (m_pages.GetSize() > 0)
	{
		ATLASSERT(m_activeIndex > -1);

		if (m_pView)
		{
			CreatePage(m_activeIndex);
//			m_pView->OnActivate(TRUE, NULL, NULL);

			// Menu of view
			//if (MDIFrame)
			{
				CComPtr<IUIFrame> docksite = m_pDlgSite->m_pDockSite;

				CComPtr<IUIMenuBar> menuBar;
				docksite->get_menuBar(&menuBar);

				//CComPtr<IUIDlg> dlg;
				//m_pView->GetDlg(&dlg);

				CComPtr<IMenuItem> menu;
				m_pView->GetMenu(&menu);

				ATLASSERT(0);
#if 0
				menuBar->put_menuItem(menu);
#endif
			}
		}
	}

	return 0;
}

LRESULT CUIViewSheet::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_font.DeleteObject();
	m_boldfont.DeleteObject();

//	baseClass::OnDestroy(uMsg, wParam, lParam, bHandled);
#if 0
// TODO
	for (int i = 0; i < m_pages.GetSize(); i++)
	{
		m_pages[i]->m_dlg->Release();
		m_pages[i]->m_dlg = NULL;
	}
#endif
	return 0;
}

LRESULT CUIViewSheet::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);

	if (m_pages.GetSize() > 0)
	{
		COLORREF clrBtnFace = GetSysColor(COLOR_BTNFACE);

		CRect client;
		GetClientRect(&client);
	//	pDC->FillSolidRect(0, 0, client.right, m_TABHEIGHT+8, clrBtnFace);

		CRect toprect(0, 0, client.right, m_TABHEIGHT+TOGGLEHEIGHT);
		if (FALSE)
			DrawVertGradient(hDC, toprect, RGB(210, 210, 210), RGB(150, 150, 150));
		else
			FillSolidRect(hDC, toprect, GetSysColor(COLOR_MENU));

		//CFont font;
		//font.CreateFont(11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Small Fonts");

		//CFont boldfont;
		//boldfont.CreateFont(11, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Small Fonts");

		CPen	whitePen;
		whitePen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
		
		CPen	blackPen;
		blackPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW));

		CBrush activeTabBrush;
		activeTabBrush.CreateSolidBrush(clrBtnFace);

		CBrush unactiveTabBrush;
		unactiveTabBrush.CreateSolidBrush(RGB(
			GetRValue(clrBtnFace)*100/120,
			GetGValue(clrBtnFace)*100/120,
			GetBValue(clrBtnFace)*100/120));

		HFONT		pOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);
		HPEN		pOldPen = (HPEN)GetCurrentObject(hDC, OBJ_PEN);
		HBRUSH	pOldBrush = (HBRUSH)GetCurrentObject(hDC, OBJ_BRUSH);

		int	oldBk = SetBkMode(hDC, TRANSPARENT);

		if (m_bShowTabs)
		{
			//HRGN	rgn;
		//	CRgn	*pOldRgn;

		//	int nsplits = (m_splitx != -1)? 2: 1;

			int xoffset = 0;//margins.left;

			for (int i = 0; i < m_pages.GetSize(); i++)
			{
				//CComQIPtr<IUIDlg> pView;
				//m_pages[i]->m_dlgSite->GetDlg(&pView);

				int x = xoffset+4;
				int cx = m_pages[i]->m_xlength;
				
				if (i == m_activeIndex)
				{
					SelectObject(hDC, activeTabBrush);
					SelectObject(hDC, m_boldfont);
				}
				else
				{
					SelectObject(hDC, unactiveTabBrush);
					SelectObject(hDC, m_font);
				}
				
				POINT pt[4] =
				{
					x, 0+m_TABHEIGHT,
					x, 0,
					x+cx-m_TABHEIGHT/2, 0,
					x+cx+m_TABHEIGHT/2+1, 0+m_TABHEIGHT
				};
				
				SelectObject(hDC, blackPen);
				Polygon(hDC, pt, 4);
				
				CRect trect(x+4, 0+1, x+cx/*-4*/, 0+m_TABHEIGHT-1);
				if (i == m_activeIndex) trect.right -= 10;
				
				BSTR btitle;
				m_pages[i]->m_dlgSite->GetName(&btitle);
				_bstr_t title = _bstr_t(btitle, FALSE);

				DrawText(hDC, title, title.length(), &trect, DT_END_ELLIPSIS | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);
				
				//	CRect tabrect(x, 1, x+TABWIDTH, m_TABHEIGHT);
				//	DrawVertGradient(pDC->m_hDC, tabrect, RGB(255, 0, 0), RGB(150, 0, 0));
				
				if (i == m_activeIndex)
				{
					SelectObject(hDC, whitePen);
					MoveToEx(hDC, x+1, 0 + m_TABHEIGHT-1, NULL);
					LineTo(hDC, x+1, 0 + 1);
					LineTo(hDC, x+cx-m_TABHEIGHT/2-1, 0 + 1);
					
					// Close button
					if (TRUE)
					{
						int left = x+cx-m_TABHEIGHT/2-8;
						int top = 4;
						
						if (m_bPushRect && m_bWasInside)
						{
							SelectObject(hDC, blackPen);
							
							MoveToEx(hDC, left+1, top+1, NULL);
							LineTo(hDC, left+7, top+7);
							
							MoveToEx(hDC, left+1, top+6, NULL);
							LineTo(hDC, left+7, top+0);
							
							Draw3DRect(hDC, left, top, 8, 8, RGB(100, 100, 100), RGB(255, 255, 255));
						}
						else
						{
							Draw3DRect(hDC, left, top, 8, 8, RGB(100, 100, 100), RGB(255, 255, 255));
							Draw3DRect(hDC, left+1, top+1, 6, 6, RGB(255, 255, 255), RGB(0, 0, 0));
						}
					}
				}
				
				if (i == m_activeIndex)
				{
					pt[2].x++;
					pt[3].x++;
					
					HRGN rgn = CreatePolygonRgn(pt, 4, ALTERNATE);
					
					ExtSelectClipRgn(hDC, rgn, RGN_XOR);

					DeleteObject(rgn);
				}

				xoffset += cx;//TABWIDTH;
			}
		}

		{
			int top = 0;
			if (m_bShowTabs) top += m_TABHEIGHT;

			Draw3DRect(hDC, 0, top, client.right, TOGGLEHEIGHT, RGB(0, 0, 0), RGB(255, 255, 255));
			Draw3DRect(hDC, 0+1, top+1, client.right-2, TOGGLEHEIGHT-2, RGB(80, 80, 80), RGB(200, 200, 200));
		}

		SetBkMode(hDC, oldBk);
		SelectObject(hDC, pOldPen);
		SelectObject(hDC, pOldBrush);
		SelectObject(hDC, pOldFont);

		/*
		DeleteObject(font);
		DeleteObject(boldfont);

		DeleteObject(whitePen);
		DeleteObject(blackPen);

		DeleteObject(activeTabBrush);
		DeleteObject(unactiveTabBrush);
		*/
	}

	EndPaint(&ps);
	return 0;
}

LRESULT CUIViewSheet::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return TRUE;
}

LRESULT CUIViewSheet::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	return 0;
}

LRESULT CUIViewSheet::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (!m_bDraggingTab)
	{
		if (m_bShowTabs)
		{
			if (point.y < m_TABHEIGHT)
			{
				int index;// = (point.x-4) / TABWIDTH;
				
				for (index = 0; index < m_pages.GetSize(); index++)
				{
					if (point.x < m_pages[index]->m_xoffset+m_pages[index]->m_xlength)
						break;
				}

				if (index >= 0 && index < m_pages.GetSize())
				{
					CPage* pPage = m_pages[index];

					BOOL bClose = FALSE;
					
					if (index == m_activeIndex)
					{
						// Close button
						if (TRUE)
						{
							int left = 4+(pPage->m_xoffset+pPage->m_xlength)-m_TABHEIGHT/2-8;
							CRect closeRect(left, 4, left+8, 4+8);
							
							if (closeRect.PtInRect(point))
							{
								m_buttonRect = closeRect;
								bClose = TRUE;
							}
						}
					}
					
					if (bClose)
					{
						InvalidateRect(m_buttonRect, TRUE);
						
						m_bPushRect = TRUE;
						m_bWasInside = TRUE;
						SetCapture();
					}
					else
					{
#if 0
						m_pages[index]->ActivateViews();
#else
						if (m_activeIndex != index)
						{
							/*pFrame->*/SetActiveTabIndex(index);
						}
						ATLASSERT(m_activeIndex == index);
#endif

						// Drag tab
						CPoint pt = point;
						ClientToScreen(&pt);
						CDragContext context;

						context.m_pBar = pPage->m_dlgSite;
						context.StartDrag(pt);

#if 0
						if (FALSE)
						{
							m_bDraggingTab = TRUE;
							SetCapture();
							
							POINT	pt = point;
							ClientToScreen(&pt);
							
							CRect	rect;
							GetWindowRect(&rect);
							
							m_offset.x = pt.x-rect.left;
							m_offset.y = pt.y-rect.top;

#if 0
							m_pWasInsideFrame = NULL;
							m_oldpt = pt;
							DrawBand(m_oldpt, m_activeIndex, (m_pWasInsideFrame == NULL));
#endif							
						}
#endif
					}
				}
			}
		}
	}

	return 0;
}

LRESULT CUIViewSheet::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	ReleaseCapture();

	if (m_bPushRect)	// Close tab
	{
		m_bPushRect = FALSE;

		if (m_bWasInside)
		{
			InvalidateRect(&m_buttonRect);

			CComPtr<IUIDlg> dlg;
			m_pView->GetDlg(&dlg);

			dlg->OnDlgClose();
		}

		m_buttonRect.SetRectEmpty();
	}
	else if (m_bDraggingTab)
	{
		m_bDraggingTab = FALSE;

#if 0
		if (m_pWasInsideFrame)
		{
			m_pWasInsideFrame->DrawRectInFrame();
		}

		DrawBand(m_oldpt, m_activeIndex, (m_pWasInsideFrame == NULL));
#endif

		POINT scrpoint = m_oldpt;
	/*

		CUIMDIView* pDoc = m_pages[m_activeIndex];

		HWND hWnd = WindowFromPoint(scrpoint);
		CUIMDIChild* pFrame = NULL;

		TCHAR classname[256];
		GetClassName(hWnd, classname, sizeof(classname));

		if (!strcmp(classname, "mmschildframe"))
		{
			pFrame = (CUIMDIChild*)GetWindowLong(hWnd, GWL_USERDATA);
		}
		else if (!strcmp(classname, "mmsview"))
		{
			pFrame = (CUIMDIChild*)GetWindowLong(::GetParent(hWnd), GWL_USERDATA);
		}

	//	pDoc->AddRef();
*/


#if 0
		if (m_pWasInsideFrame)	// Put page in this window
		{
			//pFrame = (CUIMDIChild*)TARGETDATA(pFrame->m_targetRef, IID_MDICHILDFRAME);

			HWND hwnddest;
			m_pWasInsideFrame->get_hwnd(&hwnddest);

			if (hwnddest != m_hWnd)
			{
				RemoveTabIndex(m_activeIndex[0]);	// Remove from this page

				long index;
				m_pWasInsideFrame->AddPage(m_pView[0], &index);
				m_pWasInsideFrame->SetActiveTabIndex(index);
			}
		}
		else	// Create new Window
		{
			POINT place;
			place.x = (scrpoint.x-m_offset.x);
			place.y = (scrpoint.y-m_offset.y);

			CRect winrect;
			GetWindowRect(&winrect);

			HWND hMDIClient = GetParent();

#if 0
			// Create MDI child frame
			CComQIPtr<IUIMDIChild> pChild;
			pChild.CoCreateInstance(CLSID_UIMDIChild);
			pChild->AddView(m_pView, NULL);
			RemoveTabIndex(m_activeIndex);
		// From here on 'this' is invalid

			::ScreenToClient(hMDIClient, &place);

			IUIWnd* uiwnd;
			pChild->QueryInterface(IID_IUIWnd, (void**)&uiwnd);
			CreateMDIWindow("mmschildframe", (char*)"",//pChild->m_pView->GetUITitle(),
				WS_CHILD | WS_VISIBLE,
				place.x, place.y, winrect.Width(), winrect.Height(),
				hMDIClient,
				_Module.m_hInst,
				(LPARAM)uiwnd);
			uiwnd->Release();
			pChild.Detach();
#endif
		}
#endif
	}

	return 0;
}

LRESULT CUIViewSheet::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_bPushRect)
	{
		BOOL bInside = m_buttonRect.PtInRect(point);

		if (m_bWasInside != bInside)
		{
			m_bWasInside = bInside;
			InvalidateRect(m_buttonRect, TRUE);
			UpdateWindow();
		}
	}
	else if (m_bDraggingTab)
	{
#if 0
		POINT scrpoint = point;
		ClientToScreen(&scrpoint);

		CRect	winrect;
		GetWindowRect(&winrect);

		HWND pParentWnd = GetParent();
		CRect parentRect;
		::GetWindowRect(pParentWnd, &parentRect);

	// Make sure we don't drop the window outside its parent
		if (scrpoint.x-m_offset.x < parentRect.left-winrect.Width()+20)
			scrpoint.x = parentRect.left+m_offset.x-winrect.Width()+20;
		else if (scrpoint.x-m_offset.x > parentRect.right-20)
			scrpoint.x = parentRect.right+m_offset.x-20;

		if (scrpoint.y-m_offset.y < parentRect.top)
			scrpoint.y = parentRect.top+m_offset.y;
		else if (scrpoint.y-m_offset.y > parentRect.bottom-10)
			scrpoint.y = parentRect.bottom+m_offset.y-10;

		if (m_pWasInsideFrame)
		{
			m_pWasInsideFrame->DrawRectInFrame();
		}

		DrawBand(m_oldpt, m_activeIndex[0], (m_pWasInsideFrame == NULL));
		m_pWasInsideFrame = NULL;

		HWND hWnd = WindowFromPoint(scrpoint);
		CUIMDIChildImpl<T>* pFrame;

		//TCHAR classname[256];
		//GetClassName(hWnd, classname, sizeof(classname));

		while (hWnd)
		{
			pFrame = (CUIMDIChildImpl<T>*)GetProp(hWnd, "mmsx_childframe");
			if (pFrame != NULL) break;
			/*
			GetClassName(hWnd, classname, sizeof(classname));
			if (!strcmp(classname, "mmschildframe"))
			{
				IUIWnd* pUI = (IUIWnd*)GetWindowLong(hWnd, GWL_USERDATA);
				pFrame = pUI;

				if (pFrame != NULL) break;
			}
			*/

			hWnd = ::GetParent(hWnd);
		}

	/*
		if (!strcmp(classname, "mmschildframe"))
		{
			pFrame = (CUIMDIChild*)GetWindowLong(hWnd, GWL_USERDATA);
		}
		else if (!strcmp(classname, "mmsview"))
		{
			pFrame = (CUIMDIChild*)GetWindowLong(::GetParent(hWnd), GWL_USERDATA);
		}
	*/

		if (pFrame/* &&
			(pFrame->m_pTemplate == m_pTemplate)*/)	// Can put in this window
		{
			
		//	pFrame = (CUIMDIChild*)TARGETDATA(pFrame->m_targetRef, IID_MDICHILDFRAME);
		//	if (pFrame->m_hWnd != m_hWnd)	// ?? have this
			{
				m_pWasInsideFrame = pFrame;
			}
		}

		if (m_pWasInsideFrame)
		{
			m_pWasInsideFrame->DrawRectInFrame();
		}

		DrawBand(scrpoint, m_activeIndex[0], (m_pWasInsideFrame == NULL));
		
		m_oldpt = scrpoint;
#endif
	}
	
//	CMDIChildWnd::OnMouseMove(nFlags, point);

	return 0;
}

void CUIViewSheet::SetActivePage(int index)
{
	if (index != m_activeIndex)
	{
		int prevActiveIndex = m_activeIndex;
		m_activeIndex = index;

		if (m_hWnd)
		{
		// Hide/Deactivate previous active pane window
			if ((prevActiveIndex >= 0) && (prevActiveIndex < m_pages.GetSize()))
			{
				if (m_bActive)
				{
					CComPtr<IUIDlg> pDlg;
					m_pages[prevActiveIndex]->m_dlgSite->GetDlg(&pDlg);
					pDlg->OnActivate(FALSE, NULL, NULL);
				}

				m_pages[prevActiveIndex]->m_dlgSite->ShowWindow(SW_HIDE);
			}
		}

		m_activeIndex = index;	// Set it again, in case the above changed it

		if (m_activeIndex >= 0 && m_activeIndex < m_pages.GetSize())
		{
			m_pView = m_pages[m_activeIndex]->m_dlgSite;

			if (m_hWnd)
			{
				CreatePage(m_activeIndex);
				OnSize();

				if (m_bActive)
				{
					CComPtr<IUIDlg> dlg;
					m_pView->GetDlg(&dlg);
					dlg->OnActivate(TRUE, NULL, NULL);
				}
			}
		}
	}
}

void CUIViewSheet::SetActiveTabIndex(long index)
{
	//IUIFrame* MDIFrame = m_pDockSite;//spFrame;

	SetActivePage(index);

	if (m_pView)
	{
		HWND hwndview;
		m_pView->get_hwnd(&hwndview);
		if (hwndview)
		{
			::SetActiveWindow(hwndview);
			::SetFocus(hwndview);
		}

		if (m_hWnd)
		{
			// Menu of view
			//if (MDIFrame)
			{
				CComPtr<IUIFrame> docksite = m_pDlgSite->m_pDockSite;

				CComPtr<IUIMenuBar> menuBar;
				docksite->get_menuBar(&menuBar);

				//CComPtr<IUIDlg> dlg;
				//m_pView->GetDlg(&dlg);

				CComPtr<IMenuItem> menu;
				m_pView->GetMenu(&menu);

				ATLASSERT(0);
#if 0
				menuBar->put_menuItem(menu);
#endif
			}

#if 0
			BSTR btitle;
			m_pView->get_title(&btitle);
			_bstr_t title = _bstr_t(btitle, FALSE);

			::SetWindowText(m_hWnd, title);
#endif

			InvalidateRect(NULL, TRUE);
		//	UpdateWindow();
		}
	}
}

STDMETHODIMP CUIViewSheet::SetActivePage(IUIDlgSite* dlgSite)
{
	if (dlgSite == NULL)
	{
		SetActiveTabIndex(-1);
		return S_OK;
	}

	for (int i = 0; i < m_pages.GetSize(); i++)
	{
		if (m_pages[i]->m_dlgSite == dlgSite)
		{
			if (m_activeIndex != i)
			{
				SetActiveTabIndex(i);
			}

			return S_OK;
		}
	}

	ATLASSERT(0);
	return E_FAIL;
}

STDMETHODIMP CUIViewSheet::RecalcLayout()
{
	if (m_hWnd)
	{
		CalculateTabWidths();
		InvalidateRect(NULL);
	}

	return S_OK;
}

STDMETHODIMP CUIViewSheet::DockControlBar(IUIDlgSite *pSite, RECT *lpRect)
{
	if (pSite->m_pDockBar == this/* && (lpRect == NULL || rectBar == *lpRect)*/)
	{
		// already docked and no change in position
		return S_OK;
	}

	CPage* pPage = new CPage;
	pPage->m_dlgSite = pSite;	// This AddRefs
	//pDlg->AddRef();

	HWND hwnd;
	pSite->get_hwnd(&hwnd);
	if (hwnd)
	{
		::SetParent(hwnd, m_hWnd);
	}
	/*
	else
	{
		pBar->Create(m_hWnd);
	}
	*/

// Remove bar from any previous dockbar
	if (pSite->m_pDockBar)
	{
		ATLASSERT(0);
#if 0	// Had this
		pSite->m_pDockBar->RemoveControlBar(pSite);
#endif
	}

	pPage->m_dlgSite->m_pDockBar = this;

	//pDlg->SetDockSite(m_pDockSite); // ???

	int index = m_pages.Add(pPage);
	//pDlg->put_ownerSheet(this);

	if (index == 0)
		SetActivePage(index);	// Active page if this is the first

	RecalcLayout();

	return S_OK;
}

STDMETHODIMP CUIViewSheet::RemoveControlBar(IUIDlgSite *pBar)
{
	for (int i = 0; i < m_pages.GetSize(); i++)
	{
		if (m_pages[i]->m_dlgSite == pBar)
		{
			RemoveTabIndex(i);
			return S_OK;
		}
	}
	return E_FAIL;
}
#endif