#include "stdafx.h"
#include "LXUI.h"

#if 0

#include "..\LHTML\LHTML2.h"
//#include "..\LHTML\LHTMLWindow.h"
#include "..\LHTML\PImage.h"
#include "..\LHTML\LDOMElementImpl.h"
#include "..\LHTML\PElement.h"

#include "..\LHTML\HTMContext.h"
#include "..\LHTML\PBlockBox.h"

#include "LXUIDocument.h"
#include "PLXUILXUIElement.h"

//#include "UIMDIFrame.h"

#include "UIDlgSite.h"

#include "DragContext.h"

//////////////////////////////////////////////////////////////////////////
// CUIDlgSite

void CUIDlgSite::FinalRelease()
{
#if 0
	if (m_hWnd)
	{
		DestroyWindow();
		ATLASSERT(m_hWnd == NULL);
	}
#endif
}

STDMETHODIMP CUIDlgSite::GetDlg(IUIDlg* *pVal)
{
	if (pVal == NULL) return E_POINTER;

//	m_dlg = (CUIPageContent*)GetElementByTagNameNS(L"http://www.lerstad.com/2004/lxui", L"content");

	ATLASSERT(0);

#if 0
	*pVal = m_dlg;
	if (*pVal) (*pVal)->AddRef();
#endif
	return S_OK;
}

// virtual
void CUIDlgSite::Show()
{
#if 0
	CUIMDIFrame* pFrame = ((CUIMDIFrame*)m_parent);

	m_pDockSite = pFrame;
	//m_dlg = this;
	//pDlgSite->m_dlg->SetDlgSite(pDlgSite);

	//CMenuItem* pMenuItem = (CMenuItem*)GetElementByTagNameNS(L"http://www.lerstad.com/2004/lxui", L"menuitem");
	//put_menuItem(pFrapMenuItem);

	SetBarStyle(CBRS_TOP | CBRS_SIZE_DYNAMIC | CBRS_STRETCH);

//	pDlgSite->Create(m_hWnd);

	pFrame->FloatControlBar(this, CPoint(0,0), CBRS_SIZE_DYNAMIC);
#endif

	/*
	pDlgSite->m_pDockSite = this;
	pDlgSite->m_dlg = m_menuBar;
	pDlgSite->m_dlg->SetDlgSite(pDlgSite);
*/

	SetBarStyle(CBRS_TOP | CBRS_SIZE_DYNAMIC | CBRS_STRETCH);
/*
	pDlgSite->Create(m_hWnd);

	m_listControlBars[0]->DockControlBar(pDlgSite, &CRect(0, 0, 20, 10));
	*/
}

//#include "UIMenuBar.h"

// CPElement
void CUIDlgSite::CalculateBounds()
{
#if 0
	if (m_pContent == NULL)
	{
		m_dlg = NULL;
		m_pContent = GetElementByTagNameNS(L"http://www.lerstad.com/2004/lxui", L"content", FALSE);

#if 0
		if (m_pContent == NULL)
		{
			m_pContent = GetElementByTagNameNS(L"http://www.lerstad.com/2004/lxui", L"sheet", FALSE);
		}
#endif

		if (m_pContent == NULL)
		{
			m_pContent = GetElementByTagNameNS(L"http://www.lerstad.com/2004/lxui", L"menubar", FALSE);
		}

		if (m_pContent == NULL)
		{
			m_pContent = GetElementByTagNameNS(NULL, L"content", FALSE);
		}

		if (m_pContent)
		{
			m_pContent->CreateBehaviors();

			if (m_pContent->m_behaviors.GetSize() > 0)
			{
				CComQIPtr<IUIDlg> dlg = m_pContent->m_behaviors[0]->m_p;
				if (dlg)
				{
					m_dlg = dlg;
					m_dlg->SetDlgSite(this);
				}
			}
			else
			{
				CComQIPtr<IUIDlg> dlg = m_pContent;
				if (dlg)
				{
					m_dlg = dlg;
					m_dlg->SetDlgSite(this);
				}
			}
		}
		else
		{
			MessageBeep(-1);
		}
	}
#endif
}

/////////

#if 0
STDMETHODIMP CUIDlgSite::GetName(BSTR *pVal)
{
	CComQIPtr<ILXUIPageElement> element(m_pNode);

	VARIANT v;
	element->get_caption(&v);
	if (v.vt == VT_BSTR)
		*pVal = v.bstrVal;
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CUIDlgSite::SetName(BSTR newVal)
{
	CComQIPtr<ILXUIPageElement> element(m_pNode);
	return element->put_caption(_variant_t(newVal));
}
#endif

#if 0
// virtual
void CUIDlgSite::PlaceControls(HWND hWndParent, CHTMFlowBlockContext* pC)
{
	if (m_pBox)	// hmm.. ???
	{
		ATLASSERT(::IsWindow(hWndParent));
		ATLASSERT(m_pBox);

		Gdiplus::RectF rc = m_pBox->GetAbsInnerRect();

		if (m_hWnd == NULL)
		{
			Create(hWndParent);
			ShowWindow(SW_SHOW);
		}
		else
		{
			SetParent(hWndParent);
		}

		MoveWindow((int)rc.X, (int)rc.Y, (int)rc.Width, (int)rc.Height);
	}
}
#endif

#if 0 // Experimental to remove these
CSize CUIDlgSite::CalcLayout(DWORD dwMode, int nLength)
{
	ASSERT_VALID(this);
#if 0	// I removed this
	ASSERT(::IsWindow(m_hWnd));
#endif
	if (dwMode & LM_HORZDOCK)
		ATLASSERT(dwMode & LM_HORZ);

	CSize sizeResult(0,0);

//	ATLASSERT(m_activeIndex >= 0 && m_activeIndex < m_pages.GetSize());

	int length;

	if (dwMode & LM_MRUWIDTH)
		length = GetMRUWidth();
#if 0
	else if (dwMode & LM_HORZDOCK)
		length = 32767;
#endif
	else if (dwMode & LM_VERTDOCK)
		length = 0;
	else
		length = nLength;

	/*
	if (!(m_dwStyle & CBRS_FLOATING))
	{
// For gripper
		if (HORZF(m_dwStyle))
			length -= 8;
		else if (VERTF(m_dwStyle))
			length -= 8;
	}
	*/

	if (m_dlg)
		m_dlg->CalcLayout(dwMode, length, &sizeResult);

#if 0	// Test removing this
	sizeResult.cy += 2;
#endif

#if 0
	if (m_dwStyle & CBRS_FLOATING)
	{
	}
	else
	{
// For gripper
		if (HORZF(m_dwStyle))
			sizeResult.cx += 11;
		else if (VERTF(m_dwStyle))
			sizeResult.cy += 11;
	}
#endif

//	m_nMRUWidth = sizeResult.cx;	// My addition

	return sizeResult;
}

CSize CUIDlgSite::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
//	ATLASSERT(0);
	DWORD dwMode = bStretch ? LM_STRETCH : 0;
	dwMode |= bHorz ? LM_HORZ : 0;

	return CalcLayout(dwMode);
}
#endif

CSize CUIDlgSite::CalcDynamicLayout(int nLength, DWORD dwMode)
{
//	DistributeWithinBlock(nLength);

	ATLASSERT(0);
	return CSize(0,0);
#if 0
	if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
		((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK)))
	{
		return CalcFixedLayout(dwMode & LM_STRETCH, dwMode & LM_HORZDOCK);
	}
	return CalcLayout(dwMode, nLength);
#endif
}

#if 0
LRESULT CUIDlgSite::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);
	int cx = client.right;
	int cy = client.bottom;

	int left = 0;
	int top = 0;

	if (TRUE || !(m_dwStyle & CBRS_FLOATING))
	{
		if (m_dwStyle & CBRS_ORIENT_HORZ)
		{
			left = 10;	// gripper
			cx -= 10+1;

			top = 1;
			cy -= 2;
		}
		else if (m_dwStyle & CBRS_ORIENT_VERT)
		{
			top = 10;	// gripper
			cy -= 10+1;

			left = 1;
			cx -= 2;
		}
	}

	if (m_dlg)
	{
		CWindow wnd;
		m_dlg->get_hwnd(&wnd.m_hWnd);

		if (wnd.m_hWnd)	// TODO ????
		{
			wnd.SetWindowPos(NULL, left, top, cx, cy, SWP_NOZORDER);
		}
	}

	return 0;
}

LRESULT CUIDlgSite::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);
	HDC hDC = dc.m_hDC;

	CRect	client;
	GetClientRect(&client);

	if (TRUE || !(m_dwStyle & CBRS_FLOATING))
	{
		dc.FillSolidRect(&client, GetSysColor(COLOR_MENU));

		dc.Draw3dRect(0, 0, client.right, client.bottom, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
		//DrawLine(hDC, 0, 0, client.right, 0, GetSysColor(COLOR_3DHILIGHT));
		//DrawLine(hDC, 0, client.bottom-1, client.right, client.bottom-1, GetSysColor(COLOR_3DSHADOW));

		//Draw3DRect(hDC, 0, 0, client.right, client.bottom, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));

	// Draw gripper
		if (m_dwStyle & CBRS_ORIENT_HORZ)
		{
			dc.Draw3dRect(2, 2, 4, client.bottom-4, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
			dc.Draw3dRect(6, 2, 4, client.bottom-4, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
		}
		else if (m_dwStyle & CBRS_ORIENT_VERT)
		{
			dc.Draw3dRect(1, 0, client.right, 4, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
			dc.Draw3dRect(1, 4, client.right-2, 4, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
		}
	}

	return 0;
}

LRESULT CUIDlgSite::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	ClientToScreen(&point);

	CDragContext context;
	context.m_pBar = this;

	context.StartDrag(point);

	return 0;
}
#endif

STDMETHODIMP CUIDlgSite::IsVisible()
{
	if (m_visible == FALSE)
		return S_FALSE;
	else if (m_visible == TRUE)
		return S_OK;
	else	// == 2 not visible, but doesn't make parent hidden
		return m_visible;
}

/*
STDMETHODIMP CUIDlgSite::SetVisible(BOOL bVisible)
{
	m_visible = bShow;

	if (m_hWnd)
	{
		SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|
			(bShow == TRUE ? SWP_SHOWWINDOW : SWP_HIDEWINDOW));
	}

	if (m_pDockBar)
	{
		m_pDockBar->RecalcLayout();
	}
}
*/

#if 0
STDMETHODIMP CUIDlgSite::Show(BOOL bShow)
{
	ATLASSERT(0);
#if 0
	m_visible = bShow;

	if (m_hWnd)
	{
		SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|
			(bShow == TRUE ? SWP_SHOWWINDOW : SWP_HIDEWINDOW));
	}

	if (m_pDockBar)
	{
		m_pDockBar->RecalcLayout();
	}
#endif

	return S_OK;
}

#endif

#endif