#include "stdafx.h"
#include "LXMLEditor2.h"
#include "ControlsWindow.h"

#if 0
/////////////////////////////////////////////////////////////////////////
// CControlsContainer

LRESULT CControlsContainer::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	HFONT hOldFont = dc.SelectFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

	dc.SetBkMode(TRANSPARENT);

	CRect client;
	GetClientRect(&client);

	int y = 0;

	for (int i = 0; i < m_controls.GetSize(); i++)
	{
		if (m_controls[i]->m_pControl->m_bVisible)
		{
			CControl* pControl = m_controls[i]->m_pControl;

		//	CXMLAttribute* pAttr = pControl->m_pAttr;

			CRect itemrect(0, y, client.right, y+pControl->m_height);

			CRect trect = itemrect;
			trect.right = 80;

			dc.DrawText(pControl->m_name, pControl->m_name.GetLength(), &trect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);

			CRect vrect = itemrect;
			vrect.left = 82;

			pControl->Draw(dc.m_hDC, vrect);

			y += pControl->m_height;
			y += 1;	// Spacing
		}
	}

	dc.SelectFont(hOldFont);

	return 0;
}

LRESULT CControlsContainer::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_pActiveControl)
	{
		m_pActiveControl->Deactivate();
	}

	CRect m_areaRect;
	GetClientRect(&m_areaRect);

	int m_splitx = 82;

	long scrollposY = 0;

	int y = 0;

	int top;

	for (int i = 0; i < m_controls.GetSize(); i++)
	{
		if (m_controls[i]->m_pControl->m_bVisible)
		{
			CControl* pControl = m_controls[i]->m_pControl;

			top = y;

			y += pControl->m_height;

			if (point.y < y)
			{
				break;
			}

			y += 1;	// Spacing
		}
	}

	if (i < m_controls.GetSize())
	{
		CControl* pControl = m_controls[i]->m_pControl;

		if (point.x >= 82)
		{
			int rctop = m_areaRect.top + top - scrollposY;
			CRect rect(m_splitx, rctop, m_areaRect.right, rctop + pControl->m_height);

			if (pControl->m_bEnabled)
			{
				m_pActiveControl = pControl;

				CPoint pt = point;
				pt.x -= rect.left;
				pt.y -= rect.top;

				BOOL bDoDrag = pControl->Activate(m_hWnd, pt, rect);

				if (bDoDrag)
				{
					SetCapture();

					MSG msg;
					while (GetMessage(&msg, NULL, 0, 0))
					{
						TranslateMessage(&msg);

						switch (msg.message)
						{
						case WM_MOUSEMOVE:
							{
								pt.x = (short)LOWORD(msg.lParam);
								pt.y = (short)HIWORD(msg.lParam);
								pt.x -= rect.left;
								pt.y -= rect.top;

								m_pActiveControl->DoDrag(pt, rect);
							}
							break;

						case WM_LBUTTONUP:
							{
								bDoDrag = FALSE;
							}
							break;

						default:
							DispatchMessage(&msg);
						}

						if (!bDoDrag)
							break;
					}

					ReleaseCapture();
				}
			}
		}
	}

	return 0;
}

STDMETHODIMP CControlsContainer::Redraw()
{
	if (m_hWnd)
	{
		Invalidate();
	}

	return S_OK;
}

#endif