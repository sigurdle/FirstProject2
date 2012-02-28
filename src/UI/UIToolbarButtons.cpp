// UIToolbarButtons.cpp : Implementation of CUIToolbarButtons

#include "stdafx.h"
#include "UI.h"
#include "UIToolbarButtons.h"

/////////////////////////////////////////////////////////////////////////////
// CUIToolbarButtons

HRESULT CUIToolbarButtons::OnDraw(ATL_DRAWINFO& di)
{
	HDC hDC = di.hdcDraw;
	RECT& rc = *(RECT*)di.prcBounds;

	FillSolidRect(hDC, &rc, GetSysColor(COLOR_BTNFACE));

	int x = rc.left + 2;
	int y = rc.top + 2;

	for (int i = 0; i < m_buttons.GetSize(); i++)
	{
		CToolbarButton* pButton = m_buttons[i];

		if ((m_dragging-1) == i && m_bInsideRect)
		{
			TransparentBlt(hDC, x+1, y+1, m_nWidth, m_nWidth, m_hBitmap, i*m_nWidth, 0, RGB(192, 192, 192));
			Draw3DRect(hDC, x, y, m_nWidth+1, m_nWidth+1, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DLIGHT));
		}
		else
			TransparentBlt(hDC, x, y, m_nWidth, m_nWidth, m_hBitmap, i*m_nWidth, 0, RGB(192, 192, 192));

		x += m_nWidth + 2;
	}

	return S_OK;
}

STDMETHODIMP CUIToolbarButtons::SetBitmap(HBITMAP hBitmap, long nWidth)
{
	m_hBitmap = hBitmap;
	m_nWidth = nWidth;
	return S_OK;
}

STDMETHODIMP CUIToolbarButtons::AddButton(long id, long bmIndex)
{
	CToolbarButton* pButton = new CToolbarButton;
	pButton->m_id = id;
	pButton->m_bmIndex = bmIndex;

	m_buttons.Add(pButton);

	if (m_spInPlaceSite)
	{
		m_spInPlaceSite->InvalidateRect(NULL, TRUE);
	}

	return S_OK;
}

LRESULT CUIToolbarButtons::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	point.x -= m_rcPos.left;
	point.y -= m_rcPos.top;

	if (m_dragging == 0)
	{
		int x = 2;
		int y = 2;

		for (int i = 0; i < m_buttons.GetSize(); i++)
		{
			CToolbarButton* pButton = m_buttons[i];

			CRect rect(x-2, y-2, x+m_nWidth+2, y+m_nWidth+2);

			if (rect.PtInRect(point))
			{
				m_rect = rect;
				m_dragging = i+1;
				break;
			}

			x += m_nWidth + 2;
		}

		if (m_dragging > 0)
		{
			m_bInsideRect = TRUE;

			m_spInPlaceSite->InvalidateRect(&m_rect, TRUE);
			m_spInPlaceSite->SetCapture(TRUE);
		}
	}

	return 0;
}

LRESULT CUIToolbarButtons::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging > 0)
	{
		m_spInPlaceSite->SetCapture(FALSE);

		int dragging = m_dragging;
		m_dragging = 0;

		if (m_bInsideRect)
		{
			m_spInPlaceSite->InvalidateRect(&m_rect, TRUE);

			long buttonid = m_buttons[dragging-1]->m_id;
			Fire_Click(buttonid);
		}
	}
	return 0;
}

LRESULT CUIToolbarButtons::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	point.x -= m_rcPos.left;
	point.y -= m_rcPos.top;

	BOOL bInsideRect = m_rect.PtInRect(point);
	if (bInsideRect != m_bInsideRect)
	{
		m_bInsideRect = bInsideRect;
		m_spInPlaceSite->InvalidateRect(&m_rect, TRUE);
	}

	return 0;
}
