#include "stdafx.h"

#if 0

//#include "UITImpl.h"
#include "LXUI.h"
#include "..\LHTML\LHTML2.h"
#include "UIDlgSheet.h"

#include "..\LHTML\LHTMLWindow.h"
#include "..\LHTML\PImage.h"
#include "..\LHTML\LDOMElementImpl.h"
#include "..\LHTML\PElement.h"

#include "HTMContext.h"
#include "PBlockBox.h"

#include "DragContext.h"

#include "UIDlgSite.h"

////////////////////////////////////////////////////////////////////////////////
// CUIDlgSheet

void CalcBorders(LPRECT lpClientRect, DWORD dwStyle = WS_THICKFRAME | WS_CAPTION, DWORD dwExStyle = 0);
void GetClientWindowRect(HWND hWnd, LPRECT lpRect);

CUIDlgSheet::CUIDlgSheet()
{
	m_dragging = FALSE;
	m_bInside = FALSE;

	m_menuButton = NULL;

//
	m_bMinimized = FALSE;
	m_bTabbed = TRUE;
	m_bShowTabs = TRUE;
	m_activeIndex = -1;

	m_tabTop = 1;
	m_tabHeight = 13;

	m_bActive = FALSE;
}

CUIDlgSheet::~CUIDlgSheet()
{
	ATLTRACE("~CUIDlgSheet()\n");

	delete m_menuButton;
	m_menuButton = NULL;
}

//virtual
void CUIDlgSheet::DistributeWithinBlock(CHTMFlowBlockContext* pC, double parentwidth)
{
	ATLASSERT(0);
#if 0
	// Don't distribute children, we take care of this ourselves elsewhere

	m_computedDisplay = Display_inline;	// means don't recurse into children

	// Call base class
	CPLXUIElementImpl::DistributeWithinBlock(pC, parentwidth);

	/*
	// ??
	m_computedHeight = m_height;
	m_pBox->m_innerRect.Height = m_height;
	m_pBox->m_outerRect.Height = m_height;
	*/

//	m_pBox = CreateBlockBox();
//	pC->m_pBlockBox = m_pBox;

	m_computedDisplay = Display_block;	// set it back :) (Have a better way, probably as a paremeter to the above function)

/*
	if (m_pOwnedBox)
	{
		m_pOwnedBox->m_innerRect.Width = m_pBox->m_innerRect.Width;
		m_pOwnedBox->m_innerRect.Height = m_pBox->m_innerRect.Height;

		m_pOwnedBox->m_outerRect = m_pOwnedBox->m_innerRect;
	}
	*/
#endif
}

STDMETHODIMP CUIDlgSheet::OnActivate(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView)
{
	m_bActive = bActivate;

	CComQIPtr<ILDOMDocumentEvent> documentEvent = CComQIPtr<CLDOMElementImplImpl>(m_pNode)->m_ownerDocument;
	ATLASSERT(documentEvent != NULL);

	if (bActivate)
	{
		/*
		if (m_viewGroup)
			m_viewGroup->OnDlgActivate(bActivate);
			*/
		CComPtr<ILDOMEvent> evt;
		documentEvent->createEvent(L""/*custom??*/, (ILDOMEvent**)&evt);
		evt->initEvent(L"DLGActivate",
			VARIANT_FALSE,	// bubbles
			VARIANT_FALSE	// cancelable
			);

		CComQIPtr<ILDOMEventTarget> eventTarget = m_pNode;
		VARIANT_BOOL doDefault;
		eventTarget->dispatchEvent(evt, &doDefault);

		if (m_activeIndex >= 0)
		{
			CComPtr<IUIDlg> dlg;
			m_pages[m_activeIndex]->m_dlgSite->GetDlg(&dlg);
			dlg->OnActivate(bActivate, pActivateView, pDeactivateView);
		}
	}
	else
	{
		if (m_activeIndex >= 0)
		{
			CComPtr<IUIDlg> dlg;
			m_pages[m_activeIndex]->m_dlgSite->GetDlg(&dlg);
			dlg->OnActivate(bActivate, pActivateView, pDeactivateView);
		}

	//	if (m_viewGroup)
	//		m_viewGroup->OnDlgActivate(bActivate);
		CComPtr<ILDOMEvent> evt;
		documentEvent->createEvent(L""/*custom??*/, (ILDOMEvent**)&evt);
		evt->initEvent(L"DLGDeactivate",
			VARIANT_FALSE,	// bubbles
			VARIANT_FALSE	// cancelable
			);

		CComQIPtr<ILDOMEventTarget> eventTarget = m_pNode;
		VARIANT_BOOL doDefault;
		eventTarget->dispatchEvent(evt, &doDefault);
	}

	return S_OK;
}

// TODO, what's this used for???
STDMETHODIMP CUIDlgSheet::OnFrameActivate(long fActive)
{
	// Pass on to all pages
	for (int i = 0; i < m_pages.GetSize(); i++)
	{
		CComPtr<IUIDlg> dlg;
		m_pages[i]->m_dlgSite->GetDlg(&dlg);
		dlg->OnFrameActivate(fActive);
	}

	return S_OK;
}

void CUIDlgSheet::CalculateBounds()
{
	//GetShowTabs();

	m_pages.RemoveAll();

	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CPNode* pNode = (CPNode*)m_childList.GetNext(pos);

		if (pNode->m_type == LNODE_ELEMENT)
		{
			CComQIPtr<ILXUIPageElement> page = pNode->m_pNode;
			if (page)
			{
				CPage* pPage = new CPage;
				//pPage->m_pPElement = (CPElement*)pNode;
				pPage->m_dlgSite = (CUIDlgSite*)pNode;

				m_pages.Add(pPage);
			}
		}
	}

	{
		long index = -1;

		CComQIPtr<ILDOMElement> element(m_pNode);
		CComBSTR bstr;
		element->getAttribute(L"selectedIndex", &bstr);
		if (bstr.Length())
		{
			index = atol(_bstr_t(bstr));

			if (!(index >= 0 && index < m_pages.GetSize()))
			{
				index = -1;
			}
		}

		if (index != m_activeIndex)
		{
			SetActivePage(index);
		}
	}

	if (m_hWnd)
	{
		CalculateTabWidths();
		Invalidate();
	}
}

// virtual
void CUIDlgSheet::BuildChildren()
{
	CPLXUIElementImpl::BuildChildren();
}

#include "UIMDIChild.h"

//virtual
void CUIDlgSheet::PlaceControls(HWND hWndParent, CHTMFlowBlockContext* pC)
{
	Gdiplus::RectF rc = m_pBox->GetAbsInnerRect();

	if (m_hWnd == NULL)
	{
		CRect rect((int)rc.X, (int)rc.Y, (int)rc.GetRight(), (int)rc.GetBottom());
		CWindowImpl<CUIDlgSheet>::Create(hWndParent, rect, NULL, WS_CHILD | WS_VISIBLE);
	}
	else
	{
		MoveWindow((int)rc.X, (int)rc.Y, (int)rc.Width, (int)rc.Height);
	}

//	CalculateTabWidths();
}

void CUIDlgSheet::ShowDlg(int index)
{
//	CComPtr<IUIDlg> pDlg;
//	m_pages[index]->m_rdlg->GetDialog(&pDlg);
//	if (pDlg)
	{
//		ATLASSERT(pDlg);

		HWND dlghwnd;
		m_pages[index]->m_dlgSite->get_hwnd(&dlghwnd);
		if (dlghwnd)
		{
			ATLASSERT(::IsWindow(dlghwnd));
		}
		else
		{
			BOOL success;
			m_pages[index]->m_dlgSite->Create(m_hWnd);
		}

		CComPtr<IUIDlg> dlg;
		m_pages[index]->m_dlgSite->GetDlg(&dlg);

		m_menuButton->m_target = dlg;
		//dlg->get_menu(&m_menuButton->m_menu);

		m_pages[index]->m_dlgSite->GetMenu(&m_menuButton->m_menu);

		m_pages[index]->m_dlgSite->ShowWindow(SW_SHOW);
	}

	OnSize();
}

void CUIDlgSheet::CreateDlg(int index)
{
	CPage* pPage = m_pages[index];
	ATLASSERT(pPage->m_dlgSite);

	/*
	CComObject<CUIDlgSite>::CreateInstance(&pPage->m_dlgSite);
		pPage->m_dlgSite->AddRef();
		pPage->m_dlgSite->m_pDockSite = m_pDockSite;
		pPage->m_dlgSite->m_pDockBar = this;
		*/

#if 0
	if (pPage->m_dlgSite->m_dlg)
	{
		pPage->m_dlgSite->m_dlg->SetDlgSite(pPage->m_dlgSite);

		pPage->m_dlgSite->SetBarStyle(CBRS_TOP | CBRS_SIZE_DYNAMIC | CBRS_STRETCH);
	}
#endif
}

void CUIDlgSheet::RemovePage(IUIDlgSite* pRDlg)
{
	for (int i = 0; i < m_pages.GetSize(); i++)
	{
		if (m_pages[i]->m_dlgSite == pRDlg)
		{
			RemovePage(i);
			return;
		}
	}
	ATLASSERT(0);
}

void CUIDlgSheet::RemovePage(int index)
{
	ATLASSERT(index >= 0 && index < m_pages.GetSize());

	CPage* pPage = m_pages[index];

	if (pPage->m_dlgSite)
	{
		//CComPtr<IUIDlg> dlg;
		//pPage->m_dlgSite->GetDlg(&dlg);

		//dlg->SetDlgSite(NULL);	// HUH?? This can't be right

		HWND hWndDlg;
		pPage->m_dlgSite->get_hwnd(&hWndDlg);

		if (::GetParent(hWndDlg) == m_hWnd)	// Destroy window if it's a child of us
		{
			pPage->m_dlgSite->DestroyWindow();
		}

		//pPage->m_dlgSite.Release();
	}

	m_pages.RemoveAt(index);
	delete pPage;

	if (m_pages.GetSize() > 0)	// There are still pages on this sheet
	{
		CalculateTabWidths();

		int newactive = FindVisiblePage(m_activeIndex);
		m_activeIndex = -1;

	//	if (newactive > m_pages.GetSize()-1)
	//		newactive--;
		//newactive = 

		SetActivePage(newactive);
	}
	else	// No more pages on this sheet, remove ourself from where we're docked
	{
		ATLASSERT(0);
#if 0	// Had this
		if (m_pDlgSite->m_pDockBar)
		{
			m_pDlgSite->m_pDockBar->RemoveControlBar(m_pDlgSite);
		}
#endif

	// At this point we may have been released/deleted
	}
}

STDMETHODIMP CUIDlgSheet::SetActivePage(IUIDlgSite* dlgSite)
{
	if (dlgSite == NULL)
	{
		SetActivePage(-1);
		return S_OK;
	}

	for (int i = 0; i < m_pages.GetSize(); i++)
	{
		if (m_pages[i]->m_dlgSite == dlgSite)
		{
			if (m_activeIndex != i)
			{
				SetActivePage(i);
			}

			return S_OK;
		}
	}

	ATLASSERT(0);
	return E_FAIL;
}

LRESULT CUIDlgSheet::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DWORD dwStyle = GetWindowLong(GWL_STYLE);

	LPNCCALCSIZE_PARAMS lpParams = (LPNCCALCSIZE_PARAMS)lParam;

	::InflateRect(lpParams->rgrc,
		-GetSystemMetrics(SM_CXFRAME), -GetSystemMetrics(SM_CYFRAME));

	if (dwStyle & WS_CAPTION)
		lpParams->rgrc[0].top += GetSystemMetrics(SM_CYSMCAPTION);//_afx_sizeMiniSys.cy;

	return 0;
}

LRESULT CUIDlgSheet::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LPMINMAXINFO lpminmax = (LPMINMAXINFO)lParam;

	return 0;
}

void CUIDlgSheet::CalculateTabWidths()
{
	ATLASSERT(m_hWnd);

	HDC hDC = CreateCompatibleDC(NULL);

	HFONT font = CreateFont(11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Small Fonts");
	HFONT pOldFont = (HFONT)SelectObject(hDC, font);

	CRect client;
	GetClientRect(&client);

	client.right -= 16;	// Room for popupmenu button

	int i;

	int x = 0;

	for (i = 0; i < m_pages.GetSize(); i++)
	{
		CPage* pPage = m_pages[i];

		//if (pPage->m_dlgSite->IsVisible() == S_OK)
		{
			BSTR btitle;
			pPage->m_dlgSite->GetName(&btitle);
			_bstr_t title = _bstr_t(btitle, FALSE);

			SIZE size;
			GetTextExtentPoint32(hDC, title, title.length(), &size);

			pPage->m_fullWidth = size.cx+4+7;
			pPage->m_xlength = pPage->m_fullWidth; 
			pPage->m_xoffset = x;
			x += pPage->m_xlength;
		}
	}

	int totalwidth = x;

	if (totalwidth > client.right)
	{
		x = 0;

	// Shrink all tabs proportionally
		for (int i = 0; i < m_pages.GetSize(); i++)
		{
			CPage* pPage = m_pages[i];
			if (pPage->m_dlgSite->IsVisible()==S_OK)
			{
				pPage->m_xlength = client.right*((double)pPage->m_xlength/(totalwidth));

				pPage->m_xoffset = x;
				x += pPage->m_xlength;
			}
		}
	}

	SelectObject(hDC, pOldFont);

	DeleteDC(hDC);
}

void CUIDlgSheet::SetActivePage(int index)
{
	if (index != m_activeIndex)
	{
		//if (m_hWnd)
		{
			m_menuButton->m_menu.Release();
			m_menuButton->m_target.Release();
		}

		int prevActiveIndex = m_activeIndex;
		m_activeIndex = index;

		if (m_hWnd)
		{
		// Hide/Deactivate previous active pane window
			if ((prevActiveIndex >= 0) && (prevActiveIndex < m_pages.GetSize()))
			{
				if (m_pages[prevActiveIndex]->m_dlgSite)//if (pDlg)
				{
					CComPtr<IUIDlg> dlg;
					m_pages[prevActiveIndex]->m_dlgSite->GetDlg(&dlg);
					ATLASSERT(dlg);

					dlg->OnActivate(FALSE, NULL, NULL);

					m_pages[prevActiveIndex]->m_dlgSite->ShowWindow(SW_HIDE);
				}
			}
		}

		m_activeIndex = index;	// Set it again, in case the above changed it

		if (m_activeIndex >= 0 && m_activeIndex < m_pages.GetSize())
		{
			CreateDlg(m_activeIndex);

			//CComPtr<IUIDlg> pDlg;
			//m_pages[m_activeIndex]->m_rdlg->GetDialog(&pDlg);
			if (m_pages[m_activeIndex]->m_dlgSite)//if (pDlg)
			{
				if (m_hWnd)
				{
					ShowDlg(m_activeIndex);

					OnSize();

					CComPtr<IUIDlg> dlg;
					m_pages[m_activeIndex]->m_dlgSite->GetDlg(&dlg);
					dlg->OnActivate(TRUE, NULL, NULL);
				}
			}
		}

		if (m_hWnd)
		{
		// Update the captions
			if (m_bTabbed)
			{
				CRect	client;
				GetClientRect(&client);
				InvalidateRect(&CRect(0, 0, client.right, m_tabTop+15), TRUE);
				UpdateWindow();
			}
			else
			{
				if (m_activeIndex >= 0)
				{
					BSTR title;
					m_pages[m_activeIndex]->m_dlgSite->GetName(&title);

					SetWindowText(_bstr_t(title));

					SysFreeString(title);
				}
			}
		}
	}
}

STDMETHODIMP CUIDlgSheet::AddDialog(IUIDlg *dlg)
{
	CComPtr<IUIDlgSite> site;
	dlg->GetDlgSite(&site);

	return DockControlBar(site, NULL);
}

void CUIDlgSheet::OnSize()
{
	CRect client;
	GetClientRect(&client);
	int cx = client.right;
	int cy = client.bottom;

	int left = 0;
	int top = 0;

	if (m_bTabbed)
	{
		if (m_bShowTabs)
		{
			top += m_tabTop+m_tabHeight+3;
			cy -= m_tabTop+m_tabHeight+3;

			CalculateTabWidths();
		}

		if (m_activeIndex >= 0)
		{
			if (m_pages[m_activeIndex]->m_dlgSite)
			{
				HWND dlghwnd;
				m_pages[m_activeIndex]->m_dlgSite->get_hwnd(&dlghwnd);

				::SetWindowPos(dlghwnd, NULL, left, top, cx, cy, SWP_NOZORDER);
			}
		}
	}
	else if (!m_bTabbed)
	{
		int y = 0;

		for (int i = 0; i < m_pages.GetSize(); i++)
		{
			CPage* pPage = m_pages[i];

			pPage->m_btn[0] = CRect(client.right-14, y+1, 12, 12);
			pPage->m_btn[0].right += pPage->m_btn[0].left;
			pPage->m_btn[0].bottom += pPage->m_btn[0].top;

			pPage->m_btn[1] = CRect(client.right-26, y+1, 12, 12);
			pPage->m_btn[1].right += pPage->m_btn[1].left;
			pPage->m_btn[1].bottom += pPage->m_btn[1].top;

			pPage->m_btn[2] = CRect(client.right-38, y+1, 12, 12);
			pPage->m_btn[2].right += pPage->m_btn[2].left;
			pPage->m_btn[2].bottom += pPage->m_btn[2].top;

			if (pPage->m_dlgSite == NULL)
			{
				CreateDlg(i);
			}

			/*
			CComPtr<IUIDlg> dlg;
			pPage->m_rdlg->GetDialog(&dlg);

			if (dlg == NULL)
			{
				pPage->m_rdlg->CreateDlg(&dlg);
			}
			*/

			if (pPage->m_dlgSite)
			{
				if (pPage->m_dlgSite->IsVisible() == S_OK)
				{
					HWND hwnd;
					pPage->m_dlgSite->get_hwnd(&hwnd);
					if (hwnd)
					{
						y += 16;

						if (pPage->m_expanded)
						{
							::SetWindowPos(hwnd, NULL, 12, y, client.right-12, 17+100, SWP_NOZORDER/* | SWP_NOSIZE*/);

							y += 17+100;//wrect.Height();
						}
						else
						{
							::SetWindowPos(hwnd, NULL, 12, y, client.right-12, 17, SWP_NOZORDER/* | SWP_NOSIZE*/);

							y += 17;//wrect.Height();
						}
					}
				}
			}
		}
	}

	if (m_bTabbed && m_bShowTabs && m_menuButton->m_menu && m_menuButton->m_target)
	{
		m_menuButton->MoveWindow(cx-15, top-15-2, 15, 15);
	}
	else
	{
		m_menuButton->MoveWindow(0, 0, 0, 0);
	}
}

void CUIDlgSheet::DrawBand(HDC dc, CPoint xy, int tab, BOOL bBorder, DWORD m_dwOverDockStyle)
{
	dc = ::GetDC(NULL);

	CRect	rect;
	GetClientWindowRect(m_hWnd, &rect);

	int	x = xy.x;//point.x-m_offset.x;
	int	y = xy.y;//point.y-m_offset.y;

	HPEN pen = CreatePen(PS_SOLID, (m_dwOverDockStyle > 0)? 3: 1, RGB(255, 255, 255));

	int	oldR2 = SetROP2(dc, R2_XORPEN);
	HPEN	pOldPen = (HPEN)SelectObject(dc, pen);

	if (bBorder)
	{
		CRect rcBorders = rect;
		CalcBorders(&rcBorders);
		rcBorders.OffsetRect(x-rect.left, y-rect.top);

		MoveToEx(dc, rcBorders.left, rcBorders.top, NULL);
		LineTo(dc, rcBorders.right, rcBorders.top);
		LineTo(dc, rcBorders.right, rcBorders.bottom);
		LineTo(dc, rcBorders.left, rcBorders.bottom);
		LineTo(dc, rcBorders.left, rcBorders.top);
	}

	int	top = y + 1;
	int	bottom = y+rect.Height();

//	int borderX = 0;//GetSystemMetrics(SM_CXEDGE)+1;
//	int borderY = 0;//GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYEDGE)+1;
	int tableft = 4+m_pages[tab]->m_xoffset;
	int tabwidth = m_pages[tab]->m_fullWidth;

	MoveToEx(dc, x, top+m_tabHeight, NULL);
	LineTo(dc, x+tableft, top+m_tabHeight);
	LineTo(dc, x+tableft, top);
	LineTo(dc, x+tableft+tabwidth-m_tabHeight/2, top);
	LineTo(dc, x+tableft+tabwidth+m_tabHeight/2+1, top+m_tabHeight);
	LineTo(dc, x+rect.Width(), top+m_tabHeight);
	LineTo(dc, x+rect.Width(), bottom-4);
	LineTo(dc, x, bottom-4);
	LineTo(dc, x, top+m_tabHeight);

	SelectObject(dc, pOldPen);

	SetROP2(dc, oldR2);

	DeleteObject(pen);

	::ReleaseDC(NULL, dc);
}

LRESULT CUIDlgSheet::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);
	HDC hDC = dc.m_hDC;

	CRect	client;
	GetClientRect(&client);

#if 0
	if (!(m_dwStyle & CBRS_FLOATING))
	{
		FillSolidRect(hDC, &client, GetSysColor(COLOR_MENU));

		DrawLine(hDC, 0, 0, client.right, 0, GetSysColor(COLOR_3DHILIGHT));
		DrawLine(hDC, 0, client.bottom-1, client.right, client.bottom-1, GetSysColor(COLOR_3DSHADOW));

		//Draw3DRect(hDC, 0, 0, client.right, client.bottom, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));

	// Draw gripper
		if (m_dwStyle & CBRS_ORIENT_HORZ)
		{
			Draw3DRect(hDC, 0, 2, 4, client.bottom-4, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
			Draw3DRect(hDC, 4, 2, 4, client.bottom-4, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
		}
		else if (m_dwStyle & CBRS_ORIENT_VERT)
		{
			Draw3DRect(hDC, 1, 0, client.right, 4, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
			Draw3DRect(hDC, 1, 4, client.right-2, 4, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
		}
	}
#endif

	CFont font;
	font.CreateFont(11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Small Fonts");
	HFONT hOldFont = (HFONT)SelectObject(hDC, font);

	if (m_bTabbed)
	{
		if (m_bShowTabs)
		{
			FillSolidRect(hDC, 0, 0, client.right, m_tabTop+m_tabHeight/*1+14*/, GetSysColor(COLOR_INACTIVECAPTION));

			CPen	whitePen;
			whitePen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));

			CPen	blackPen;
			blackPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW));

			CPen	grayPen;
			grayPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));

			CBrush activeBgBrush;
			activeBgBrush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));

			CBrush inactiveBgBrush;
			inactiveBgBrush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));

			HPEN hOldPen = (HPEN)GetCurrentObject(hDC, OBJ_PEN);
			HBRUSH hOldBrush = (HBRUSH)GetCurrentObject(hDC, OBJ_BRUSH);

			int oldBk = SetBkMode(hDC, TRANSPARENT);

		//	MoveToEx(hDC, 0, 13, NULL);
		//	LineTo(hDC, client.right, 13);

			int top = m_tabTop;

			for (int i = 0; i < m_pages.GetSize(); i++)
			{
				CPage* pPage = m_pages[i];

				if (TRUE)//pPage->m_dlgSite->IsVisible() == S_OK)
				{
					int x = pPage->m_xoffset+4;
					int cx = pPage->m_fullWidth;//xlength;

					SelectObject(hDC, GetStockObject(NULL_PEN));

					if (i == m_activeIndex)
					{
						SelectObject(hDC, activeBgBrush);
					}
					else
					{
						SelectObject(hDC, inactiveBgBrush);
					}

					POINT pt[4] =
					{
						x, top+13,
						x, top,
						x+cx-7, top,
						x+cx+6, top+13
					};

					if (i == m_activeIndex)
					{
						pt[0].y++;
						pt[3].x++;
						pt[3].y++;
					}

					Polygon(hDC, pt, 4);

					SelectObject(hDC, blackPen);
					Polyline(hDC, pt, 4);

					if (i == m_activeIndex)
					{
					// white
						SelectObject(hDC, whitePen);

						MoveToEx(hDC, 0, top+14, NULL);
						LineTo(hDC, x+1, top+14);
						LineTo(hDC, x+1, top+1);
						LineTo(hDC, x+cx-7, top+1);

						// dark pen
						SelectObject(hDC, grayPen);
						LineTo(hDC, x+cx+6, top+14);

						//light pen
						SelectObject(hDC, whitePen);
						LineTo(hDC, client.right, top+14);

						SelectObject(hDC, activeBgBrush);

					// Dividing line
						SelectObject(hDC, blackPen);

						MoveToEx(hDC, 0, top+13, NULL);
						LineTo(hDC, x, top+13);

						MoveToEx(hDC, x+cx+7, top+13, NULL);
						LineTo(hDC, client.right, top+13);
					}

					CComBSTR title;
					pPage->m_dlgSite->GetName(&title);
				//	pPage->m_dlgSite->GetAttribute(L"caption", &title);

					CRect trect(x+4, top+1, x+cx, top+14);
					DrawText(hDC, _bstr_t(title), title.Length(), &trect, DT_VCENTER | DT_SINGLELINE);

					if (i == m_activeIndex)
					{
						pt[2].x++;
						pt[3].x++;

						HRGN rgn = CreatePolygonRgn(pt, 4, ALTERNATE);

						ExtSelectClipRgn(hDC, rgn, RGN_XOR);

						DeleteObject(rgn);
					}
				}
			}

			SetBkMode(hDC, oldBk);
			SelectObject(hDC, hOldPen);
			SelectObject(hDC, hOldBrush);
		}
	}
	else
	{
		int x = 0;
		int y = 0;

		int cx = client.right-16;

		for (int i = 0; i < m_pages.GetSize(); i++)
		{
			CPage* pPage = m_pages[i];

			if (pPage->m_dlgSite->IsVisible() == S_OK)
			{
				COLORREF c1 = GetSysColor(COLOR_ACTIVECAPTION);
				COLORREF c2 = GetSysColor(COLOR_GRADIENTACTIVECAPTION);

				CRgn rgn;
				rgn.CreateRoundRectRgn(0, y, client.right, y+16, 2, 2);
				dc.SelectClipRgn(rgn, RGN_COPY);

				TRIVERTEX v[2];

				v[0].x = 0;
				v[0].y = y;
				v[0].Red = GetRValue(c1)*255;
				v[0].Green = GetGValue(c1)*255;
				v[0].Blue = GetBValue(c1)*255;
				v[0].Alpha = 255*255;

				v[1].x = client.right;
				v[1].y = y+16;
				v[1].Red = GetRValue(c2)*255;
				v[1].Green = GetGValue(c2)*255;
				v[1].Blue = GetBValue(c2)*255;
				v[1].Alpha = 255*255;

				GRADIENT_RECT gr = {0, 1};
				dc.GradientFill(v, 2, &gr, 1, GRADIENT_FILL_RECT_H);

				dc.SelectClipRgn(NULL, RGN_COPY);

				{
					for (int n = 0; n < 3; n++)
					{
						CRect rc = pPage->m_btn[n];

						if (m_activeIndex == i && m_dragging == n+1 && m_bInside)
						{
							dc.Draw3dRect(&rc, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHILIGHT));
							rc.InflateRect(-1,-1);
							dc.Draw3dRect(&rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DLIGHT));
							rc.InflateRect(-1,-1);
						}
						else
						{
							dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
							rc.InflateRect(-1,-1);
							dc.Draw3dRect(&rc, GetSysColor(COLOR_3DLIGHT), GetSysColor(COLOR_3DSHADOW));
							rc.InflateRect(-1,-1);
						}

						dc.FillSolidRect(&rc, GetSysColor(COLOR_BTNFACE));
					}

					// Close
					{
						CRect rc = pPage->m_btn[0];
						if (m_activeIndex == i && m_dragging == 1 && m_bInside)
							rc.OffsetRect(1, 1);

						int midx = rc.left+1 + (rc.Width()-3)/2;
						int midy = rc.top+1 + (rc.Height()-3)/2;

						dc.MoveTo(midx-2, midy-2);
						dc.LineTo(midx+2+1, midy+2+1);
						dc.MoveTo(midx-2+1, midy-2);
						dc.LineTo(midx+2+1+1, midy+2+1);

						dc.MoveTo(midx-2, midy+2);
						dc.LineTo(midx+2+1, midy-2-1);
						dc.MoveTo(midx-2+1, midy+2);
						dc.LineTo(midx+2+1+1, midy-2-1);
					}

					// Minimize/Restore
					{
						CRect rc = pPage->m_btn[1];
						if (m_activeIndex == i && m_dragging == 2 && m_bInside)
							rc.OffsetRect(1, 1);

						if (pPage->m_expanded)
						{
							dc.MoveTo(rc.left+1, rc.top+2);
							dc.LineTo(rc.right-3, rc.top+2);

							dc.MoveTo(rc.left+1, rc.top+3);
							dc.LineTo(rc.right-3, rc.top+3);
						}
						else
						{
							dc.MoveTo(rc.left+2, rc.top+2);
							dc.LineTo(rc.right-3, rc.top+2);

							dc.MoveTo(rc.left+2, rc.top+3);
							dc.LineTo(rc.right-3, rc.top+3);

							dc.MoveTo(rc.left+2, rc.top+2);
							dc.LineTo(rc.left+2, rc.bottom-4);
							dc.LineTo(rc.right-4, rc.bottom-4);
							dc.LineTo(rc.right-4, rc.top+2);
						}
					}
				}

				dc.SetBkMode(TRANSPARENT);
				dc.SetTextColor(GetSysColor(COLOR_CAPTIONTEXT));

				CComBSTR title;
				if (pPage->m_dlgSite)
					pPage->m_dlgSite->GetName(&title);

				CRect trect(x+16, y+1, x+cx, y+14);
				DrawText(hDC, _bstr_t(title), title.Length(), &trect, DT_VCENTER | DT_SINGLELINE);

				y += 16;

				y += 17;

				if (pPage->m_expanded)
				{
					y += 100;
				}
			}
		}
	}

	SelectObject(hDC, hOldFont);

//	if (m_dragging) DrawBand(m_pt);

	return 0;
}

LRESULT CUIDlgSheet::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	return 0;
}

LRESULT CUIDlgSheet::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	/*
	CRect clientrect;
	GetClientRect(&clientrect);

	CRect winrect;
	GetWindowRect(&winrect);
*/
	if (m_dragging)
	{
		BOOL bInside = m_pages[m_activeIndex]->m_btn[m_dragging-1].PtInRect(point);
		if (bInside != m_bInside)
		{
			m_bInside = bInside;
			InvalidateRect(&m_pages[m_activeIndex]->m_btn[m_dragging-1]);
		}

#if 0
		m_ptLast = scrpoint;
#endif
	}

	return 0;
}

LRESULT CUIDlgSheet::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (!m_dragging)
	{
		if (m_bTabbed)
		{
			int index = -1;

			int x = 4;
	
			for (int i = 0; i < m_pages.GetSize(); i++)
			{
				CPage* pPage = m_pages[i];

				if (pPage->m_dlgSite->IsVisible() == S_OK)
				{
					int x2;
					if (m_activeIndex == i)
						x2 = x+pPage->m_fullWidth;
					else
						x2 = x+pPage->m_xlength;

					if (point.x < x2)
					{
						index = i;
						break;
					}

					x += pPage->m_xlength;
				}
			}

			if (index != -1)
			{
				if (index != m_activeIndex)
				{
					WCHAR buf[64];
					swprintf(buf, L"%d", index);
					CComQIPtr<ILXUISheetElement>(m_pNode)->setAttribute(L"selectedIndex", buf);

					ATLASSERT(m_activeIndex == index);
				}

				if (FALSE)
				{
					CPopupDialog* p = new CPopupDialog;
					p->m_dlg = m_pages[index]->m_dlgSite;

					CRect rect;
					GetWindowRect(&rect);
					//CPoint pt;
					p->Popup(m_hWnd, CPoint(rect.left, rect.bottom));
				}
				else
				{
#if 0	// TODO have this
					CPoint pt = point;
					ClientToScreen(&pt);
					CDragContext context;

					context.m_pBar = m_pages[index]->m_dlgSite;

					context.StartDrag(pt);
#endif
				}
			}
		}
		else
		{
			CRect client;
			GetClientRect(&client);

			int y = 0;

			for (int i = 0; i < m_pages.GetSize(); i++)
			{
				CPage* pPage = m_pages[i];

				if (pPage->m_dlgSite->IsVisible() == S_OK)
				{
					y += 16;

					if (point.y < y)
					{
						m_activeIndex = i;	// ???

						if (point.x >= pPage->m_btn[0].left)	// Close
						{
							m_bInside = TRUE;
							m_dragging = 1;
						}
						else if (point.x >= pPage->m_btn[1].left)	// Expand/Unexpand
						{
							m_bInside = TRUE;
							m_dragging = 2;
						}
						else if (point.x >= pPage->m_btn[2].left)	// Toggle showTabs
						{
							ATLASSERT(0);
#if 0
							CComPtr<IUIDlg> dlg;
							m_pages[m_activeIndex]->m_dlgSite->GetDlg(&dlg);

							CComQIPtr<IUIDlgSheet> sheet = dlg;
							if (sheet)
							{
								BOOL bTabbed;
								sheet->GetTabbed(&bTabbed);
								sheet->SetTabbed(!bTabbed);
							}
#endif
						}
						else
						{
							CPoint pt = point;
							ClientToScreen(&pt);
							CDragContext context;

							if (pPage->m_dlgSite == NULL)
							{
								CreateDlg(i);
							}

							if (pPage->m_dlgSite)
							{
								context.m_pBar = pPage->m_dlgSite;
								context.StartDrag(pt);
							}
						}

						if (m_dragging)
						{
							SetCapture();
							InvalidateRect(&pPage->m_btn[m_dragging-1]);
						}
						break;
					}

					y += 17;

					if (pPage->m_expanded)
					{
						y += 100;
					}
				}
			}
		}
#if 0
		else if (!(m_dwStyle & CBRS_FLOATING))
		{
			POINT pt = point;
			ClientToScreen(&pt);

			StartDrag(pt);
		}
#endif
	}

	return 0;
}

LRESULT CUIDlgSheet::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_dragging)
	{
		ReleaseCapture();

		int dragging = m_dragging;
		m_dragging = 0;

		if (m_bInside)
		{
			if (dragging == 1)	// close
			{
				m_pages[m_activeIndex]->m_dlgSite->Show(FALSE);
				/*
				if (m_pages[m_activeIndex]->m_dlgSite->m_hWnd)
				{
					m_pages[m_activeIndex]->m_dlgSite->DestroyWindow();
				}
				Invalidate();
				OnSize();
				*/
			}
			else if (dragging == 2)	// minimize/restore
			{
				m_pages[m_activeIndex]->m_expanded = !m_pages[m_activeIndex]->m_expanded;
				Invalidate();
				OnSize();
			}
			else if (dragging == 3)
			{
			}
		}
	}

	return 0;
}

#if 0	// huh?? what does this have to do with contextmenu
LRESULT CUIDlgSheet::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_bTabbed = !m_bTabbed;

	if (m_bTabbed)
	{
	}
	else
		m_activeIndex = -1;

	OnSize();
	Invalidate();

	return 0;
}
#endif

//virtual
void CUIDlgSheet::OnFinalMessage( HWND hWnd )
{
//	MessageBeep(-1);
	Release();
}

LRESULT CUIDlgSheet::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) 
{
//	SetProp(m_hWnd, "mmsx_sheet", (HANDLE)this);
	SetProp(m_hWnd, "mmsx_sheet", (HANDLE)static_cast<IUIDockBar*>(this));

	CRect rc(0, 0, 0, 0);
	m_menuButton->Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);

	CalculateTabWidths();

	//if (CUIDlgSheetBase<CUIDlgSheet>::OnCreate())
	//	return -1;
	if (m_activeIndex > -1/*m_pView*/)
	{
		//ATLASSERT(m_activeIndex > -1);

		CreateDlg(m_activeIndex);
		ShowDlg(m_activeIndex);
//			m_pView->OnActivate(TRUE, NULL, NULL);
	}

	if (!m_bTabbed)	// Create all windows
	{
		for (int i = 0; i < m_pages.GetSize(); i++)
		{
			CPage* pPage = m_pages[i];

			/*
			CComPtr<IUIDlg> dlg;
			pPage->m_rdlg->GetDialog(&dlg);

			if (dlg == NULL)
			{
				pPage->m_rdlg->CreateDlg(&dlg);
			}
			*/

			if (pPage->m_dlgSite == NULL)
			{
				CreateDlg(i);
			}

			if (pPage->m_dlgSite)
			{
				//dlg->put_ownerSheet(this);

				HWND dlghwnd;
				pPage->m_dlgSite->get_hwnd(&dlghwnd);
				if (dlghwnd)
				{
					ATLASSERT(::IsWindow(dlghwnd));
				}
				else
				{
					BOOL success;
					pPage->m_dlgSite->Create(m_hWnd);
				}
			}
		}
	}

	return 0;
}

int CUIDlgSheet::GetVisiblePagesCount()
{
	int n = 0;
	for (int i = 0; i < m_pages.GetSize(); i++)
	{
		if (m_pages[i]->m_dlgSite->IsVisible() != S_FALSE)
			n++;
	}

	return n;
}

LRESULT CUIDlgSheet::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) 
{
	m_menuButton->m_menu.Release();
	m_menuButton->m_target.Release();
	m_menuButton->DestroyWindow();

//	ATLASSERT(0);
#if 0
	for (int i = m_pages.GetSize()-1; i >= 0; i--)
	{
		CPage* pPage = m_pages[i];

		CComPtr<IUIRegisteredDlg> rdlg;
		pPage->m_dlg->GetRegisteredDlg(&rdlg);

		pPage->m_dlg->DestroyWindow();
		int refcount = pPage->m_dlg->Release();

		if (rdlg)	// This is null for menubar?
		{
			CRegisteredDialog* pRDlg = static_cast<CRegisteredDialog*>(rdlg.p);
			pRDlg->RemoveDlg(pPage->m_dlg);

		//	ATLASSERT(pRDlg->m_dialogs.GetSize() == 1);
		//	pRDlg->m_dialogs.RemoveAll();
		}

		m_pages.RemoveAt(i);
		delete pPage;
	}
#endif

	return 0;
}

STDMETHODIMP CUIDlgSheet::SetTabbed(BOOL newVal)
{
	m_bTabbed = newVal;
	if (m_hWnd)
	{
		Invalidate();
	}

	return S_OK;
}

// IUIDlg

STDMETHODIMP CUIDlgSheet::CalcLayout(DWORD dwFlags, long nLength, SIZE* pVal)
{
	if (m_bTabbed)
	{
		if (m_bMinimized)
		{
			// Try to make same height as menubar etc.
			*pVal = CSize(260, max(m_tabHeight+4, 26));
			m_tabTop = pVal->cy-m_tabHeight-2;
		}
		else
		{
			if (m_bShowTabs)
			{
				m_tabTop = 1;
				*pVal = CSize(260, m_tabHeight+100);
			}
			else
			{
				if (m_activeIndex >= 0)
				{
					CComPtr<IUIDlg> dlg;
					m_pages[m_activeIndex]->m_dlgSite->GetDlg(&dlg);

					return dlg->CalcLayout(dwFlags, nLength, pVal);
				}
				else
				{
					*pVal = CSize(0, 0);
				}
			}
		}
	}
	else
	{
		int y = 0;

		for (int i = 0; i < m_pages.GetSize(); i++)
		{
			CPage* pPage = m_pages[i];

			if (pPage->m_dlgSite->IsVisible() == S_OK)
			{
				y += 16;

				y += 17;

				if (pPage->m_expanded)
				{
					y += 100;
				}
			}
		}

		*pVal = CSize(260, y);
	}

	return S_OK;
}

// IUIDockBar

STDMETHODIMP CUIDlgSheet::DockControlBar(IUIDlgSite *pBar, RECT *lpRect)
{
	if (pBar->m_pDockBar == this/* && (lpRect == NULL || rectBar == *lpRect)*/)
	{
		// already docked and no change in position
		return S_OK;
	}

	ATLASSERT(0);
#if 0

	CPage* pPage = new CPage;
	pPage->m_dlgSite = pBar;	// This AddRefs

	HWND hwnd;
	pBar->get_hwnd(&hwnd);
	if (hwnd)
	{
		::SetParent(hwnd, m_hWnd);
		pBar->ShowWindow(SW_HIDE);
	}

// Remove bar from any previous dockbar
	if (pBar->m_pDockBar)
	{
		pBar->m_pDockBar->RemoveControlBar(pBar);
	}

	int index = m_pages.Add(pPage);

	pBar->m_pDockBar = this;

	if (index == 0)
	{
		if (m_bTabbed && m_bShowTabs)
			SetActivePage(index);	// Active page if this is the first
	}

	if (m_hWnd)
	{
		OnSize();	// ??
		InvalidateRect(NULL);
	}

//	pBar->Release();	TODO have this ???

	RecalcLayout();	// ??
#endif

	return S_OK;
}

STDMETHODIMP CUIDlgSheet::RemoveControlBar(IUIDlgSite *pBar)
{
	for (int i = 0; i < m_pages.GetSize(); i++)
	{
		if (m_pages[i]->m_dlgSite == pBar)
		{
			RemovePage(i);
			return S_OK;
		}
	}
	ATLASSERT(0);
	return E_FAIL;
}

int CUIDlgSheet::FindVisiblePage(int oldindex)
{
	int index;

	// Try to find a visible page forward
	for (index = oldindex; index < m_pages.GetSize(); index++)
	{
		if (m_pages[index]->m_dlgSite->IsVisible() == S_OK)
			break;
	}

	if (index >= m_pages.GetSize())
	{
		// Then try backward
		for (index = oldindex-1; index >= 0; index--)
		{
			if (m_pages[index]->m_dlgSite->IsVisible() == S_OK)
				break;
		}
	}

	return index;
}

/*
STDMETHODIMP CUIDlgSheet::Show(BOOL bShow)
{
	m_pDlgSite->Show(bShow);
}
*/

STDMETHODIMP CUIDlgSheet::RecalcLayout()
{
	if (m_hWnd)
	{
		CalculateTabWidths();
		Invalidate();
	}

#if 0
	if (m_activeIndex >= 0)
	{
		int newactive = FindVisiblePage(m_activeIndex);
		SetActivePage(newactive);
	}
#endif

// Pass it up the chain
	if (GetVisiblePagesCount() == 0)
	{
	//	if (m_visibility == 1)

		ATLASSERT(0);
#if 0
			m_pDlgSite->Show(FALSE);
#endif
	//	else if (m_visibility == 2)
	//		m_pDlgSite->Show(2);
	}
	else
	{
		ATLASSERT(0);
#if 0
		m_pDlgSite->Show(TRUE);
#endif
	}

	return S_OK;
}

#endif