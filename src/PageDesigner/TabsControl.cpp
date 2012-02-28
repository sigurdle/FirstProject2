// TabsControl.cpp : Implementation of CTabsControl

#include "stdafx.h"
#include "PageDesigner.h"
#include "TabsControl.h"

/////////////////////////////////////////////////////////////////////////////
// CTabsControl

void GetRulerValues(PDUnit unit, double& pixelInterval, double& numberInterval, double magnify);

HRESULT CTabsControl::OnDraw(ATL_DRAWINFO& di)
{
	if (m_hWnd)
	{
		HDC hDC = di.hdcDraw;
		CRect& rc = *(CRect*)di.prcBounds;

		Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);

		HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);

		CComQIPtr<IFont> font = m_pFont;
		HFONT hFont;
		font->get_hFont(&hFont);
		SelectObject(hDC, hFont);

		if (IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom))
		{
			FillSolidRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.Width(), 12, GetSysColor(COLOR_3DSHADOW));

			CPoint oldOrg;
			SetViewportOrgEx(hDC, m_areaRect.left -m_scrollposX*m_magnify, m_areaRect.top, &oldOrg);

			FillSolidRect(hDC, 0, 0, m_pageWidth, 12, RGB(255, 255, 255));

			if (m_textPara)
			{
				HBRUSH hOldPen = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_PEN));
				HBRUSH hOldBrush = (HBRUSH)GetCurrentObject(hDC, OBJ_BRUSH);

				HBRUSH hBrush = CreateSolidBrush(GetSysColor(COLOR_WINDOWTEXT));
				HBRUSH hBrushSelected = CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHTTEXT));
				HPEN hPen = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWTEXT));
				HPEN hPenSelected = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_HIGHLIGHTTEXT));

				// Draw indents
				{
					float marginLeft;
					m_textPara->GetLeftIndent(&marginLeft);

					float marginRight;
					m_textPara->GetRightIndent(&marginRight);

					float textIndent;
					m_textPara->GetFirstLineIndent(&textIndent);

					{
						POINT pts[3] =
						{
							marginLeft+textIndent, 1,
							marginLeft+textIndent, 6,
							marginLeft+textIndent+5, 6,
						};

						if (m_selected == -2)
						{
							FillSolidRect(hDC, marginLeft+textIndent-1, 0, 7, 7, GetSysColor(COLOR_HIGHLIGHT));
							SelectObject(hDC, hBrushSelected);
						}
						else
							SelectObject(hDC, hBrush);

						Polygon(hDC, pts, 3);
					}

					{
						POINT pts[3] =
						{
							marginLeft, 7,
							marginLeft, 11,
							marginLeft+4, 7,
						};

						if (m_selected == -1)
						{
							FillSolidRect(hDC, marginLeft-1, 6, 7, 7, GetSysColor(COLOR_HIGHLIGHT));
							SelectObject(hDC, hBrushSelected);
						}
						else
							SelectObject(hDC, hBrush);

						Polygon(hDC, pts, 3);
					}

					{
						POINT pts[3] =
						{
							m_pageWidth-marginRight, 1,
							m_pageWidth-marginRight, 11,
							m_pageWidth-marginRight-5, 6,
						};

						if (m_selected == -3)
						{
							FillSolidRect(hDC, m_pageWidth-marginRight-6, 0, 7, 12, GetSysColor(COLOR_HIGHLIGHT));
							SelectObject(hDC, hBrushSelected);
						}
						else
							SelectObject(hDC, hBrush);

						Polygon(hDC, pts, 3);
					}
				}

				// Draw tabs
				{
					long ntabs;
					m_textPara->GetTabCount(&ntabs);

					for (int ntab = 0; ntab < ntabs; ntab++)
					{
						float tbPos;
						long tbAlign;
						long tbLeader;
						m_textPara->GetTab(ntab, &tbPos, &tbAlign, &tbLeader);

						if ((m_selected != ntab+1) || (m_bDeletingTab == false))
						{
							int x = (int)(tbPos);

							if (m_selected == ntab+1)
							{
								FillSolidRect(hDC, x-2, 0, 5, 12, GetSysColor(COLOR_HIGHLIGHT));

								SelectObject(hDC, hPenSelected);
								SelectObject(hDC, hBrushSelected);
							}
							else
							{
								SelectObject(hDC, hPen);
								SelectObject(hDC, hBrush);
							}

						// Draw common stuff for all tab alignment types

						// Arrow
							POINT pts[3] =
							{
								x-2, 7,
								x+2, 7,
								x, 10
							};

							Polygon(hDC, pts, 3);

						// Vertical line
							MoveToEx(hDC, x, 2, NULL);
							LineTo(hDC, x, 7);

							switch (tbAlign)
							{
							case tomAlignLeft:
								{
									MoveToEx(hDC, x, 2, NULL);
									LineTo(hDC, x+3, 2);
								}
								break;

							case tomAlignCenter:
								{
									// Do nothing
								}
								break;

							case tomAlignRight:
								{
									MoveToEx(hDC, x, 2, NULL);
									LineTo(hDC, x-3, 2);
								}
								break;

							case tomAlignDecimal:
								{
									//MoveToEx(hDC, x, 0, NULL);
									//LineTo(hDC, x, 16);
								}
								break;

							default:
								ATLASSERT(0);
							}
						}
					}
				}

				SelectObject(hDC, hOldPen);
				SelectObject(hDC, hOldBrush);

				DeleteObject(hBrush);
				DeleteObject(hBrushSelected);
				DeleteObject(hPen);
				DeleteObject(hPenSelected);
			}

			// Draw ruler
			{
				double valueAdd;
				double numberEveryPx;

				GetRulerValues(UNIT_PT, numberEveryPx, valueAdd, m_magnify);

				DWORD subdivisionsMask = (2<<0) | (2<<4) | (3<<8);

				int start = (m_scrollposX - (0)*m_magnify - (numberEveryPx-1))/ numberEveryPx;
				int end = start + (rc.Width()+numberEveryPx+numberEveryPx-1) / numberEveryPx;

				//POINT oldOrg;
				//SetViewportOrgEx(hDC, -scrollposX + (0)*m_magnify, 0, &oldOrg);

				int y = 12;

				for (int i = start; i < end; i++)
				{
					int x = i * numberEveryPx;

					MoveToEx(hDC, x, y, NULL);
					LineTo(hDC, x, y+16);

					CUString str;
					str.Format("%g", fabs(i * valueAdd));

					TextOut(hDC, x+1, y+1, str, str.GetLength());

				//	DrawSubDivisionLines(hDC, TRUE, x, numberEveryPx, 8, subdivisionsMask);
				}
			}

			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		}

		SelectObject(hDC, hOldFont);
	}

	return S_OK;
}

LRESULT CTabsControl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//			HFONT hFont = CreateFont(11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Small Fonts");

	return 0;
}

LRESULT CTabsControl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_areaRect = client;
	m_areaRect.InflateRect(-1, -1, -1, -1);

	Invalidate();

	return 0;
}

LRESULT CTabsControl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	m_startpoint = point;
	m_oldpoint = point;

	if (m_bEnabled)
	{
		if (!m_dragging)
		{
			if (m_textPara)
			{
				if (point.y <= 12)
				{
					CPoint pt = point;
					pt.x -= m_areaRect.left;
					pt.y -= m_areaRect.top;
					pt.x += m_scrollposX;

					float marginLeft;
					m_textPara->GetLeftIndent(&marginLeft);

					float marginRight;
					m_textPara->GetRightIndent(&marginRight);

					float textIndent;
					m_textPara->GetFirstLineIndent(&textIndent);

					m_selected = 0;

					if (abs(pt.x-(m_pageWidth-marginRight)) < 4)
					{
						m_selected = -3;
					}
					else
					{
						if (pt.y < 6)
						{
							if (fabs(pt.x-(marginLeft+textIndent)) < 4)
							{
								m_selected = -2;
							}
						}
						else if (pt.y < 12)
						{
							if (fabs(point.x-marginLeft) < 4)
							{
								m_selected = -1;
							}
						}
					}

					// Try tabs
					if (m_selected == 0)
					{
						long ntabs;
						m_textPara->GetTabCount(&ntabs);

						for (int ntab = 0; ntab < ntabs; ntab++)
						{
							float tbPos;
							long tbAlign;
							m_textPara->GetTab(ntab, &tbPos, &tbAlign, NULL);

							int x = (int)(tbPos);
							if (fabs(pt.x-x) < 2)
							{
								m_tbAlign = tbAlign;
								m_selected = ntab+1;
								break;
							}
						}
					}

					if (m_selected == 0)	// Add new tab
					{
						float tbPos = (float)pt.x;

						long index;
						m_textPara->AddTabEx(tbPos, m_tbAlign, 0, &index);

						m_selected = index+1;
					}

					Invalidate();

					if (m_selected)
					{
						Fire_OnSelected(m_selected);

						m_bDeletingTab = false;
						m_dragging = 1;
						SetCapture();
					}
				}
				else	// Scroll
				{
					m_dragging = 2;

					m_initialscrollposX = m_scrollposX;

					SetCursor(LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_HAND2)));
					SetCapture();
				}
			}
		}
	}

	return 0;
}

LRESULT CTabsControl::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		ReleaseCapture();

		if (m_dragging == 1)
		{
			if (m_bDeletingTab)
			{
				float tbPos;
				m_textPara->GetTab(m_selected-1, &tbPos, NULL, NULL);
				m_textPara->DeleteTab(tbPos);

				m_selected = 0;
				Fire_OnSelected(0);	
			}
			else
			{
				Fire_OnChanged();
			}
		}

		m_dragging = 0;
	}
	return 0;
}

LRESULT CTabsControl::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_dragging)
	{
		if (m_dragging == 1)
		{
			CPoint pt = point;
			pt.x -= m_areaRect.left;
			pt.y -= m_areaRect.top;
			pt.x += m_scrollposX;

			if (m_selected < 0)
			{
				float marginLeft;
				m_textPara->GetLeftIndent(&marginLeft);

				float marginRight;
				m_textPara->GetRightIndent(&marginRight);

				float textIndent;
				m_textPara->GetFirstLineIndent(&textIndent);

				if (m_selected == -1)
				{
					marginLeft = pt.x;

					if (marginLeft < 0) marginLeft = 0;
					else if (marginLeft > m_pageWidth-marginRight) marginLeft = m_pageWidth-marginRight;
				}
				else if (m_selected == -2)
				{
					textIndent = pt.x-marginLeft;

					if (textIndent < -marginLeft) textIndent = -marginLeft;
				}
				else if (m_selected == -3)
				{
					marginRight = m_pageWidth-pt.x;

					if (marginRight < 0) marginRight = 0;
					else if (marginRight > m_pageWidth-marginLeft) marginRight = m_pageWidth-marginLeft;
				}

				m_textPara->SetIndents(textIndent, marginLeft, marginRight);
			}
			else
			{
				m_bDeletingTab = (point.y < -6) || (point.y > 12+6);

				float tbPos;
				m_textPara->GetTab(m_selected-1, &tbPos, NULL, NULL);

				float newtbPos = pt.x;
				if (newtbPos < 0.01) newtbPos = 0.01;

				if (tbPos != newtbPos)
				{
					long newIndex;
					m_textPara->SetTabPos(m_selected-1, newtbPos, &newIndex);

					m_selected = newIndex+1;
				}
			}

			Invalidate();
			Fire_OnChanging(m_selected);
		}
		else if (m_dragging == 2)	// Scroll
		{
			m_scrollposX = m_initialscrollposX + m_startpoint.x-point.x;
			if (m_scrollposX < 0) m_scrollposX = 0;

			Invalidate();
		}
	}

	m_oldpoint = point;

	return 0;
}

LRESULT CTabsControl::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = (HWND) wParam;       // handle to window with cursor 
	UINT nHittest = LOWORD(lParam);  // hit-test code 
	UINT wMouseMsg = HIWORD(lParam); // mouse-message identifier 

	if (nHittest = HTCLIENT)
	{
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		if (point.y > 12)
		{
			SetCursor(LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_HAND0)));
			return TRUE;
		}
	}

	return DefWindowProc(uMsg, wParam, lParam);
}

STDMETHODIMP CTabsControl::get_pageWidth(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pageWidth;
	return S_OK;
}

STDMETHODIMP CTabsControl::put_pageWidth(double newVal)
{
	m_pageWidth = newVal;
	if (m_hWnd)
	{
		Invalidate();
	}
	return S_OK;
}

STDMETHODIMP CTabsControl::get_textPara(IPDTextPara **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_textPara;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CTabsControl::put_textPara(IPDTextPara *newVal)
{
	m_textPara = newVal;
	return S_OK;
}

STDMETHODIMP CTabsControl::get_selected(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_selected;
	return S_OK;
}

STDMETHODIMP CTabsControl::put_selected(long newVal)
{
	m_selected = newVal;
	if (m_hWnd)
	{
		Invalidate();
	}

	return S_OK;
}

STDMETHODIMP CTabsControl::get_tbAlign(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_tbAlign;
	return S_OK;
}

STDMETHODIMP CTabsControl::put_tbAlign(long newVal)
{
	if (newVal != m_tbAlign)
	{
		m_tbAlign = newVal;

		if (m_selected > 0)
		{
			float tbPos;
			long tbLeader;
			m_textPara->GetTab(m_selected-1, &tbPos, NULL, &tbLeader);

			m_textPara->DeleteTab(tbPos);
			m_textPara->AddTab(tbPos, m_tbAlign, tbLeader);

			if (m_hWnd)
			{
				Invalidate();
			}
		}
	}

	return S_OK;
}
