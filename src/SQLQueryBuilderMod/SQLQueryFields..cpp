#include "stdafx.h"
#include "SQLQueryBuilderMod.h"

#include "SQLQueryFields.h"

///////////////////////////////////////
// CSQLQueryTables

LRESULT CSQLQueryFields::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);

	CRect client;
	GetClientRect(&client);

	HFONT hOldFont = (HFONT)SelectObject(hDC, GetStockObject(DEFAULT_GUI_FONT));

	SetBkMode(hDC, TRANSPARENT);

	{
		CRect rc(6, 16, 60-6, 16+16);

		DrawText(hDC, "Field:", 6, &rc, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);
		rc.OffsetRect(0, 16);

		DrawText(hDC, "Table:", 6, &rc, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);
		rc.OffsetRect(0, 16);

		DrawText(hDC, "Sort:", 5, &rc, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);
		rc.OffsetRect(0, 16);

		DrawText(hDC, "Show:", 5, &rc, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);
		rc.OffsetRect(0, 16);

		DrawText(hDC, "Criteria:", 9, &rc, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);
		rc.OffsetRect(0, 16);
	}

	{
		Rectangle(hDC, 60, 18, client.right, client.bottom);
		Draw3DRect(hDC, 60, 9, client.right, 9, RGB(0, 0, 0), RGB(0, 0, 0));

		POINT oldOrg;
		SetViewportOrgEx(hDC, 60, 18, &oldOrg);

		int x = 0;

		for (int i = 0; i < m_columns.GetSize(); i++)
		{
			CColumn* column = m_columns[i];

			Draw3DRect(hDC, x+1, -8, column->m_width, 8, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));

			MoveToEx(hDC, x, 0, NULL);
			LineTo(hDC, x, client.bottom);

			CRect rc(x+2, 1, x+column->m_width-2, 16-1);

			DrawText(hDC, column->m_fieldName, column->m_fieldName.length(), &rc, DT_SINGLELINE | DT_VCENTER);
			rc.OffsetRect(0, 16);

			DrawText(hDC, column->m_tableName, column->m_tableName.length(), &rc, DT_SINGLELINE | DT_VCENTER);
			rc.OffsetRect(0, 16);

//			DrawText(hDC, column->m_fieldName, column->m_fieldName.length(), &rc, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);
			rc.OffsetRect(0, 16);

//			DrawText(hDC, column->m_fieldName, column->m_fieldName.length(), &rc, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);
			rc.OffsetRect(0, 16);

//			DrawText(hDC, column->m_fieldName, column->m_fieldName.length(), &rc, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);
			rc.OffsetRect(0, 16);

			if (i >= m_startSel && i <= m_endSel)
			{
				int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

				CRect rc(x, -8, x+column->m_width, client.bottom);
				FillSolidRect(hDC, &rc, RGB(0,0,0));

				SetROP2(hDC, oldR2);
			}

			x += column->m_width;
		}

		SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
	}

	SelectObject(hDC, hOldFont);

	EndPaint(&ps);
	return 0;
}

LRESULT CSQLQueryFields::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HDC hDC = (HDC)wParam;
	CRect client;
	GetClientRect(&client);

	FillSolidRect(hDC, &client, GetSysColor(COLOR_BTNFACE));

	return TRUE;
}

LRESULT CSQLQueryFields::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::RegisterDragDrop(m_hWnd, static_cast<IDropTarget*>(this));
	return 0;
}

LRESULT CSQLQueryFields::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::RevokeDragDrop(m_hWnd);
	return 0;
}

LRESULT CSQLQueryFields::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (!(wParam & MK_SHIFT))
	{
		if (m_curSel != -1)
		{
			m_curSel = -1;
			m_startSel = -1;
			m_endSel = -1;

			Invalidate();
		}
	}

	if (point.x >= 60 && point.y >= 8 && point.y <= 20)
	{
		point.x -= 60;

		m_npane = -1;
		int x = 0;

		for (int i = 0; i < m_columns.GetSize(); i++)
		{
			CColumn* column = m_columns[i];

			x += column->m_width;

			if (abs(x-point.x) < 8)
			{
				m_dragging = 1;
				m_npane = i;
				break;
			}
			else if (point.x < x)
			{
				m_dragging = 2;
				m_npane = i;
				break;
			}
		}

		if (m_dragging)
		{
			SetCapture();

			if (m_dragging == 1)
			{
				m_oldwidth = m_columns[m_npane]->m_width;
			}
			else if (m_dragging == 2)
			{
				if (!(wParam & MK_SHIFT))
				{
					m_curSel = m_npane;
					m_startSel = m_npane;
					m_endSel = m_npane;
				}
				else
				{
					if (m_npane < m_curSel)
					{
						m_startSel = m_npane;
						m_endSel = m_curSel;
					}
					else
					{
						m_startSel = m_curSel;
						m_endSel = m_npane;
					}
				}

				Invalidate();
			}

			m_oldpt = point;
		}
	}

	return 0;
}

LRESULT CSQLQueryFields::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		m_dragging = 0;
		ReleaseCapture();
	}

	return 0;
}

LRESULT CSQLQueryFields::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_dragging)
	{
		point.x -= 60;

		if (m_dragging == 1)
		{
			int width = m_oldwidth + (point.x-m_oldpt.x);
			m_oldwidth = width;

			if (width < 4) width = 4;
			else if (width > 800) width = 800;

			if (width != m_columns[m_npane]->m_width)
			{
				m_columns[m_npane]->m_width = width;
				Invalidate();
			}
		}
		else if (m_dragging == 2)
		{
			int npane = m_columns.GetSize()-1;
			int x = 0;

			for (int i = 0; i < m_columns.GetSize(); i++)
			{
				CColumn* column = m_columns[i];

				x += column->m_width;

				if (point.x < x)
				{
					npane = i;
					break;
				}
			}

			if (npane != m_npane)
			{
				if (npane < m_curSel)
				{
					m_startSel = npane;
					m_endSel = m_curSel;
				}
				else
				{
					m_startSel = m_curSel;
					m_endSel = npane;
				}
	
				m_npane = npane;

				Invalidate();
			}
		}

		m_oldpt = point;
	}

	return 0;
}

LRESULT CSQLQueryFields::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = (HWND) wParam;       // handle to window with cursor 
	int nHittest = LOWORD(lParam);  // hit-test code 
	int wMouseMsg = HIWORD(lParam); // mouse-message identifier 
 
	if (nHittest == HTCLIENT)
	{
		POINT point;
		::GetCursorPos(&point);
		ScreenToClient(&point);

		if (point.x >= 60 && point.y >= 8 && point.y <= 20)
		{
			point.x -= 60;

			int npane = -1;
			int x = 0;

			for (int i = 0; i < m_columns.GetSize(); i++)
			{
				CColumn* column = m_columns[i];

				x += column->m_width;

				if (abs(x-point.x) < 8)
				{
					npane = i;
					break;
				}
			}

			if (npane >= 0)
			{
				::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
				return TRUE;
			}
		}
	}

	return DefWindowProc(uMsg, wParam, lParam);
}

STDMETHODIMP CSQLQueryFields::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_COPY;
	return S_OK;
}

STDMETHODIMP CSQLQueryFields::DragOver(DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_NONE;

	POINT point;
	point.x = ptl.x;
	point.y = ptl.y;
	ScreenToClient(&point);

	if (point.x >= 60 && point.y >= 18)
	{
		point.x -= 60;

		int npane = -1;
		int x = 0;
		for (int i = 0; i < m_columns.GetSize(); i++)
		{
			x += m_columns[i]->m_width;
			if (point.x < x)
			{
				npane = i;
				break;
			}
		}

		if (npane >= 0)
		{
			*pdwEffect = DROPEFFECT_COPY;
		}
	}

	return S_OK;
}

STDMETHODIMP CSQLQueryFields::DragLeave()
{
	return S_OK;
}

STDMETHODIMP CSQLQueryFields::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_NONE;

	POINT point;
	point.x = ptl.x;
	point.y = ptl.y;
	ScreenToClient(&point);

	if (point.x >= 60 && point.y >= 18)
	{
		point.x -= 60;

		int npane = -1;
		int x = 0;
		for (int i = 0; i < m_columns.GetSize(); i++)
		{
			x += m_columns[i]->m_width;
			if (point.x < x)
			{
				npane = i;
				break;
			}
		}

		if (npane >= 0)
		{
			COleDataObject dataObject;
			dataObject.Attach(pDataObject);

			HGLOBAL hData;

			if (hData = dataObject.GetGlobalData(CF_UNICODETEXT))
			{
				WCHAR* p = (WCHAR*)GlobalLock(hData);

				CComQIPtr<ILDOMDocument> document;
				document.CoCreateInstance(CLSID_LDOMDocument);

				VARIANT_BOOL success;
				document->loadXML(p, &success);
				if (success)
				{
					CComQIPtr<ILDOMElement> documentElement;
					document->get_documentElement(&documentElement);
					if (documentElement)
					{
						BSTR btagName;
						documentElement->get_tagName(&btagName);
						if (!wcscmp(btagName, L"columns"))
						{
							BSTR btablename;
							documentElement->getAttribute(L"fromtable", &btablename);
							_bstr_t tablename = _bstr_t(btablename, false);

							CComQIPtr<ILDOMNode> node;
							documentElement->get_firstChild(&node);
							while (node)
							{
								CComQIPtr<ILDOMElement> element = node;
								if (element)
								{
									BSTR bname;
									element->getAttribute(L"name", &bname);
									_bstr_t name = _bstr_t(bname, false);

									CColumn* column = new CColumn;
									column->m_bApply = true;
									column->m_fieldName = name;
									column->m_tableName = tablename;
									column->m_bShow = true;

									m_columns.InsertAt(npane, column);
								}

								CComQIPtr<ILDOMNode> nextSibling;
								node->get_nextSibling(&nextSibling);
								node = nextSibling;
							}


							*pdwEffect = DROPEFFECT_COPY;

							Invalidate();
						}
						SysFreeString(btagName);
					}
				}

				GlobalUnlock(hData);
			}
		}
	}

	return S_OK;
}
