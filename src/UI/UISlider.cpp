// UISlider.cpp : Implementation of CUISlider

#include "stdafx.h"
#include "UI.h"
#include "UISlider.h"

/////////////////////////////////////////////////////////////////////////////
// CUISlider

HRESULT CUISlider::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;
//	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	CDCHandle dc(di.hdcDraw);

	dc.FillSolidRect(&rc, GetSysColor(COLOR_BTNFACE));

	CRect client = rc;
	client.right -= 10;

	double range = m_maxValue-m_minValue;

	int y = client.top + client.Height()/2;

	dc.Draw3dRect(client.left+5, y-3, client.Width()+1, 3, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHILIGHT));

	int x = client.left + 5+(client.Width()*(m_value-m_minValue))/range;

	CBrush brush;
	brush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
	HBRUSH hOldBrush = dc.SelectBrush(brush);

	POINT pt[] =
	{
		x, y+0,
		x-5, y+5,
		x+5, y+5,
	};

	dc.Polygon(pt, 3);
	dc.SelectBrush(hOldBrush);

	return S_OK;
}

LRESULT CUISlider::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	point.x -= m_rcPos.left;
	point.y -= m_rcPos.top;

	CRect client = m_rcPos;
	client.right -= 10;

	if (!m_dragging)
	{
		m_dragging = 1;
		m_spInPlaceSite->SetCapture(TRUE);

		double range = m_maxValue-m_minValue;
		int x = client.left + 5+(client.Width()*(m_value-m_minValue))/range;

		if (point.x >= x-5 && point.x < x+5)
		{
			m_xoffset = x-point.x;
		}
		else
		{
			point.x -= 5;
			m_xoffset = 0;

			m_value = (point.x*range + m_minValue) / client.Width();

			if (m_value < m_minValue) m_value = m_minValue;
			else if (m_value > m_maxValue) m_value = m_maxValue;

			Fire_SetPos(0, m_value);
			m_spInPlaceSite->InvalidateRect(NULL, TRUE);
		}
	}

	return 0;
}

LRESULT CUISlider::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		m_dragging = 0;
		m_spInPlaceSite->SetCapture(FALSE);
	}

	return 0;
}

LRESULT CUISlider::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	point.x -= m_rcPos.left;
	point.y -= m_rcPos.top;

	CRect client = m_rcPos;
	client.right -= 10;

	if (m_dragging)
	{
		point.x -= 5;
		point.x += m_xoffset;

		double range = m_maxValue-m_minValue;

		m_value = (point.x*range + m_minValue) / client.Width();

		if (m_value < m_minValue) m_value = m_minValue;
		else if (m_value > m_maxValue) m_value = m_maxValue;

		Fire_SetPos(0, m_value);
		m_spInPlaceSite->InvalidateRect(NULL, TRUE);
	}

	return 0;
}

STDMETHODIMP CUISlider::get_minValue(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_minValue;
	return S_OK;
}

STDMETHODIMP CUISlider::put_minValue(long newVal)
{
	if (m_minValue != newVal)
	{
		m_minValue = newVal;

		if (m_spInPlaceSite)
		{
			m_spInPlaceSite->InvalidateRect(NULL, TRUE);
		}
	}
	return S_OK;
}

STDMETHODIMP CUISlider::get_maxValue(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_maxValue;
	return S_OK;
}

STDMETHODIMP CUISlider::put_maxValue(long newVal)
{
	if (m_maxValue != newVal)
	{
		m_maxValue = newVal;

		if (m_spInPlaceSite)
		{
			m_spInPlaceSite->InvalidateRect(NULL, TRUE);
		}
	}

	return S_OK;
}

STDMETHODIMP CUISlider::get_value(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_value;
	return S_OK;
}

STDMETHODIMP CUISlider::put_value(long newVal)
{
	if (m_value != newVal)
	{
		m_value = newVal;

		if (m_spInPlaceSite)
		{
			m_spInPlaceSite->InvalidateRect(NULL, TRUE);
		}
	}

	return S_OK;
}
