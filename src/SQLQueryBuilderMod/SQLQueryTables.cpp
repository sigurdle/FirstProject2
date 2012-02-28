#include "stdafx.h"
#include "SQLQueryBuilderMod.h"

#include "SQLQueryTables.h"

#include "SQLTableWnd.h"

///////////////////////////////////////
//

LRESULT CSQLQueryTablesScroll::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);

	CComObject<CSQLQueryTables>::CreateInstance(&m_wnd);
	m_wnd->AddRef();
	m_wnd->Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE, 0);

	IUnknown* p;

	m_axhorz.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axhorz.AttachControl(m_horz, &p);
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);

	IDispEventImpl<1, CSQLQueryTablesScroll, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);
	IDispEventImpl<2, CSQLQueryTablesScroll, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	return 0;
}

LRESULT CSQLQueryTablesScroll::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CSQLQueryTablesScroll, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);
	IDispEventImpl<2, CSQLQueryTablesScroll, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	if (m_wnd)
	{
		m_wnd->DestroyWindow();
		m_wnd->Release();
		m_wnd = NULL;
	}

	return 0;
}

LRESULT CSQLQueryTablesScroll::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();

	return 0;
}

void CSQLQueryTablesScroll::OnSize()
{
	CRect client;
	GetClientRect(&client);

	CRect m_areaRect;

	int sbHeight = GetSystemMetrics(SM_CYHSCROLL);
	int sbWidth = GetSystemMetrics(SM_CXVSCROLL);

	m_areaRect.left = 0;
	m_areaRect.top = 0;
	m_areaRect.right = client.right-sbWidth;
	m_areaRect.bottom = client.bottom-sbHeight;

	int maxx = 5000;
	int maxy = 5000;

#if 0

	long xpos; m_horz->get_pos(&xpos);
	long ypos; m_vert->get_pos(&ypos);

	int minx = 0;
	int miny = 0;
	int maxx = 0;
	int maxy = 0;

	for (int i = 0; i < m_wnd->m_tables.GetSize(); i++)
	{
		CRect wrect;
		m_wnd->m_tables[i]->GetWindowRect(&wrect);
		m_wnd->ScreenToClient(&wrect);

		//minx = min(minx, wrect.left);
		//miny = min(miny, wrect.top);
		maxx = max(maxx, xpos+wrect.right);
		maxy = max(maxy, ypos+wrect.bottom);
	}

	m_areaRect.left = 0;
	m_areaRect.top = 0;
	m_areaRect.right = client.right;
	m_areaRect.bottom = client.bottom;

	BOOL bVertSB = FALSE;
	BOOL bHorzSB = FALSE;

	if (maxx-minx > m_areaRect.right)
	{
		m_areaRect.bottom -= sbHeight;
		bHorzSB = TRUE;
	}

	if (maxy-miny > m_areaRect.bottom)
	{
		m_areaRect.right -= sbWidth;
		bVertSB = TRUE;
	}

	if (!bHorzSB)
	{
		if (maxx-minx > m_areaRect.right)
		{
			m_areaRect.bottom -= sbHeight;
			bHorzSB = TRUE;
		}
	}

	if (bVertSB)
	{
		m_vert->SetInfo(0, maxy, m_areaRect.Height());

		m_axvert.MoveWindow(m_areaRect.right, 0, sbWidth, m_areaRect.Height());
		m_axvert.ShowWindow(SW_SHOW);
	}
	else
	{
		m_vert->SetInfo(0, 0, 0);
		m_axvert.ShowWindow(SW_HIDE);
	}

	if (bHorzSB)
	{
		m_horz->SetInfo(0, maxx, m_areaRect.Width());

		m_axhorz.MoveWindow(0, m_areaRect.bottom, m_areaRect.Width(), sbHeight);
		m_axhorz.ShowWindow(SW_SHOW);
	}
	else
	{
		m_horz->SetInfo(0, 0, 0);
		m_axhorz.ShowWindow(SW_HIDE);
	}
#endif

	m_vert->SetInfo(0, maxy, m_areaRect.Height());
	m_axvert.MoveWindow(m_areaRect.right, 0, sbWidth, m_areaRect.Height());
	m_axvert.ShowWindow(SW_SHOW);

	m_horz->SetInfo(0, maxx, m_areaRect.Width());
	m_axhorz.MoveWindow(0, m_areaRect.bottom, m_areaRect.Width(), sbHeight);
	m_axhorz.ShowWindow(SW_SHOW);

	m_wnd->MoveWindow(0, 0, m_areaRect.right, m_areaRect.bottom);
}

HRESULT __stdcall CSQLQueryTablesScroll::OnHorzScroll(long code, long pos)
{
	long oldPos; m_horz->get_pos(&oldPos);

	m_wnd->Invalidate();

	HWND hwnd = m_wnd->GetWindow(GW_CHILD);
	while (hwnd)
	{
		CRect rc;
		::GetWindowRect(hwnd, &rc);
		m_wnd->ScreenToClient(&rc);

		::SetWindowPos(hwnd, NULL, rc.left + (oldPos-pos), rc.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

		hwnd = ::GetWindow(hwnd, GW_HWNDNEXT);
	}

	m_horz->put_pos(pos);

	return S_OK;
}

HRESULT __stdcall CSQLQueryTablesScroll::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	m_wnd->Invalidate();

	HWND hwnd = m_wnd->GetWindow(GW_CHILD);
	while (hwnd)
	{
		CRect rc;
		::GetWindowRect(hwnd, &rc);
		m_wnd->ScreenToClient(&rc);

		::SetWindowPos(hwnd, NULL, rc.left, rc.top + (oldPos-pos), 0, 0, SWP_NOZORDER | SWP_NOSIZE);

		hwnd = ::GetWindow(hwnd, GW_HWNDNEXT);
	}

	m_vert->put_pos(pos);

	return S_OK;
}

///////////////////////////////////////
// CSQLQueryTables

LRESULT CSQLQueryTables::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);

	CRect cl(0,0,0,0);
	AdjustWindowRect(&cl, WS_CHILD | WS_CAPTION | WS_SIZEBOX, FALSE);
	cl.left = -cl.left;
	cl.top = -cl.top;
	cl.right = cl.right;
	cl.bottom = cl.bottom;

	for (int i = 0; i < m_tables.GetSize(); i++)
	{
		CSQLTableWnd* pTable = m_tables[i];

		ADOX::_TablePtr table = pTable->GetTable();

		for (long nkey = 0; nkey < table->Keys->Count; nkey++)
		{
			ADOX::_KeyPtr key = table->Keys->Item[nkey];

			if (key->Type == ADOX::adKeyForeign)
			{
				_bstr_t relatedTableName = key->RelatedTable;

				CSQLTableWnd* pRelatedTable = NULL;
				for (int j = 0; j < m_tables.GetSize(); j++)
				{
					if (m_tables[j]->GetTable()->Name == relatedTableName)
					{
						pRelatedTable = m_tables[j];
						break;
					}
				}

				if (pRelatedTable)
				{
					for (long col = 0; col < key->Columns->Count; col++)
					{
						ADOX::_ColumnPtr column = key->Columns->Item[col];

						_bstr_t thisColumn = column->Name;
						_bstr_t relatedColumn = column->RelatedColumn;

						long k;

						long thisColumnIndex = -1;
						for (k = 0; k < pTable->GetTable()->Columns->Count; k++)
						{
							if (pTable->GetTable()->Columns->Item[k]->Name == thisColumn)
							{
								thisColumnIndex = k;
							}
						}

						long relatedColumnIndex = -1;
						for (k = 0; k < pRelatedTable->GetTable()->Columns->Count; k++)
						{
							if (pRelatedTable->GetTable()->Columns->Item[k]->Name == relatedColumn)
							{
								relatedColumnIndex = k;
								break;
							}
						}

						if (thisColumnIndex >= 0 && relatedColumnIndex >= 0)
						{
							CRect thisTableRect;
							CRect relatedTableRect;

							pTable->GetWindowRect(&thisTableRect);
							pRelatedTable->GetWindowRect(&relatedTableRect);

							ScreenToClient(&thisTableRect);
							ScreenToClient(&relatedTableRect);

							if (thisTableRect.left < relatedTableRect.left)	// From this-right to related-left
							{
								thisTableRect.OffsetRect(0, cl.top);
								relatedTableRect.OffsetRect(0, cl.top);

								MoveToEx(hDC, thisTableRect.right, thisTableRect.top + thisColumnIndex*16+16/2, NULL);
								LineTo(hDC, thisTableRect.right+15, thisTableRect.top + thisColumnIndex*16+16/2);

								LineTo(hDC, relatedTableRect.left-15, relatedTableRect.top + relatedColumnIndex*16+16/2);
								LineTo(hDC, relatedTableRect.left, relatedTableRect.top + relatedColumnIndex*16+16/2);
							}
							else	// From this-left to related-right
							{
								thisTableRect.OffsetRect(0, cl.top);
								relatedTableRect.OffsetRect(0, cl.top);

								MoveToEx(hDC, thisTableRect.left, thisTableRect.top + thisColumnIndex*16+16/2, NULL);
								LineTo(hDC, thisTableRect.left-15, thisTableRect.top + thisColumnIndex*16+16/2);

								LineTo(hDC, relatedTableRect.right+15, relatedTableRect.top + relatedColumnIndex*16+16/2);
								LineTo(hDC, relatedTableRect.right, relatedTableRect.top + relatedColumnIndex*16+16/2);
							}
						}
					}
				}
			}
		}
	}

	EndPaint(&ps);
	return 0;
}

LRESULT CSQLQueryTables::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HDC hDC = (HDC)wParam;
	CRect client;
	GetClientRect(&client);

	FillSolidRect(hDC, &client, GetSysColor(COLOR_BTNFACE));

	return TRUE;
}

void CSQLQueryTables::AddTable(ADOX::_TablePtr table)
{
	ATLASSERT(m_hWnd);

	CComObject<CSQLTableWnd>* pTableWnd;
	CComObject<CSQLTableWnd>::CreateInstance(&pTableWnd);
	pTableWnd->AddRef();

	pTableWnd->SetTable(table);

	_bstr_t tableName = table->Name;

	CRect rc(0, 0, 100, 100);
	pTableWnd->Create(m_hWnd, rc, tableName, WS_CHILD | WS_VISIBLE | WS_CAPTION | WS_SIZEBOX);

	m_tables.Add(pTableWnd);
}
