#include "stdafx.h"
#include "UI.h"
#include "AutoListMembersWindow.h"

int CAutoListMembersWindow::FindMatch(BSTR str, int len)
{
	for (int i = 0; i < m_members.GetSize(); i++)
	{
		if (!wcsncmp(str, m_members[i]->m_name, len))
		{
			return i;
		}
	}

	return -1;
}

void CAutoListMembersWindow::ClearMemberItems()
{
	for (int i = 0; i < m_members.GetSize(); i++)
	{
		delete m_members[i];
	}

	m_members.RemoveAll();
}

void CAutoListMembersWindow::SetDispatch(IDispatch* pDisp)
{
	ClearMemberItems();

	UINT pctinfo;
	pDisp->GetTypeInfoCount(&pctinfo);

	ITypeInfo* pTInfo;
	HRESULT hr = pDisp->GetTypeInfo(0, NULL, &pTInfo);

	TYPEATTR* pType;
	pTInfo->GetTypeAttr(&pType);

	for (int i = 0; i < pType->cFuncs; i++)
	{
		FUNCDESC* pFuncDesc = NULL;
		if (SUCCEEDED(pTInfo->GetFuncDesc(i, &pFuncDesc)))
		{
			BSTR bname;
			UINT pcNames;
			pTInfo->GetNames(pFuncDesc->memid, &bname, 1, &pcNames);

			CMemberItem* pMItem = new CMemberItem;

			pMItem->m_name = _bstr_t(bname, false);
			pMItem->m_dispid = pFuncDesc->memid;

			if (pFuncDesc->invkind == DISPATCH_METHOD)
			{
				pMItem->m_type = 1;
			}
			else/* if (pFuncDesc->invkind == INVOKE_PROPERTYPUT ||
				pFuncDesc->invkind == INVOKE_PROPERTYGET ||
				pFuncDesc->invkind == INVOKE_PROPERTYPUTREF*/
			{
				pMItem->m_type = 0;
			}

			m_members.Add(pMItem);

			pTInfo->ReleaseFuncDesc(pFuncDesc);
		}
	}

	if (m_hWnd)
	{
		OnSize();
		Invalidate();
	}
}

LRESULT CAutoListMembersWindow::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	long scrollposY; m_vert->get_pos(&scrollposY);

	POINT oldOrg;
	dc.SetViewportOrg(0, -scrollposY*16, &oldOrg);

	HFONT hOldFont = dc.SelectFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

	dc.SetBkMode(TRANSPARENT);

	int y = 0;

	for (int i = 0; i < m_members.GetSize(); i++)
	{
		CMemberItem* pMItem = m_members[i];

		CRect itemrect(0, y, m_areaRect.Width(), y+16);

		if (i == m_selectedIndex)
		{
			dc.FillSolidRect(&itemrect, GetSysColor(COLOR_HIGHLIGHT));
			dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
		}
		else
		{
			dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		}

		ImageList_Draw(m_memberImageList, pMItem->m_type, dc.m_hDC, 0, y, ILD_NORMAL);

		CRect trect = itemrect;
		trect.left += 20;
		dc.DrawText(pMItem->m_name, pMItem->m_name.length(), &trect, DT_SINGLELINE | DT_VCENTER);

		y += 16;
	}

	dc.SelectFont(hOldFont);

	dc.SetViewportOrg(oldOrg.x, oldOrg.y);

	return 0;
}

LRESULT CAutoListMembersWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);

	IDispEventImpl<1, CAutoListMembersWindow, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

//	m_memberImageList = ImageList_LoadBitmap(_Module.m_hInstResource, MAKEINTRESOURCE(IDB_MEMBERLISTITEM), 16, 0, CLR_NONE);

	return 0;
}

LRESULT CAutoListMembersWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_memberImageList)
	{
		ImageList_Destroy(m_memberImageList);
		m_memberImageList = NULL;
	}

	IDispEventImpl<1, CAutoListMembersWindow, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	return 0;
}

LRESULT CAutoListMembersWindow::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();

	return 0;
}

void CAutoListMembersWindow::OnSize()
{
	CRect client;
	GetClientRect(&client);

	m_areaRect.left = 0;
	m_areaRect.top = 0;
	m_areaRect.right = client.right-16;
	m_areaRect.bottom = client.bottom;

	m_axvert.MoveWindow(m_areaRect.right, 0, 16, m_areaRect.Height(), TRUE);

	m_vert->SetInfo(0, m_members.GetSize()-1, (m_areaRect.Height())/16);
}

/*
_bstr_t CAutoListMembersWindow::GetString()
{
	HWND hWndFocus = GetFocus();

	_bstr_t str;

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		switch (msg.message)
		{
		case WM_KEYDOWN:
			{
				switch (msg.wParam)
				{
				case VK_DOWN:
				case VK_UP:
					{
						if (msg.wParam == VK_DOWN)
						{
							m_selectedIndex++;
						}
						else
						{
							m_selectedIndex--;
						}

						if (m_selectedIndex < 0)
							m_selectedIndex = 0;
						else if (m_selectedIndex > m_members.GetSize()-1)
							m_selectedIndex = m_members.GetSize()-1;

						InvalidateRect(&m_areaRect);
						continue;
					}
					break;

				case VK_RETURN:
					{
						if (m_selectedIndex >= 0 && m_selectedIndex < m_members.GetSize())
						{
							str = m_members[m_selectedIndex]->m_name;
						}

						goto Exit;
					}
					break;
				}
				break;
			}
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

Exit:

	MessageBeep(-1);

	return str;
}
*/

void CAutoListMembersWindow::SetCurSel(long index)
{
	long scrollposY;
	m_vert->get_pos(&scrollposY);

	if (m_selectedIndex != index)
	{
		m_selectedIndex = index;

		if (m_selectedIndex < 0) m_selectedIndex = 0;
		else if (m_selectedIndex > m_members.GetSize()-1) m_selectedIndex = m_members.GetSize()-1;

		int visibleLines = (m_areaRect.Height()/16);

		if (m_selectedIndex < scrollposY)
		{
			m_vert->put_pos(m_selectedIndex);
		}
		else if (m_selectedIndex > scrollposY+visibleLines-1)
		{
			m_vert->put_pos(m_selectedIndex - (visibleLines-1));
		}

		InvalidateRect(&m_areaRect);
	}
}

void __stdcall CAutoListMembersWindow::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	CRect	rect = m_areaRect;
	
	m_vert->put_pos(pos);
	ScrollWindow(0, (oldPos-pos)*16, &rect, &rect);
}

STDMETHODIMP CAutoListMembersWindow::AddString(long iImage, BSTR string, long *pVal)
{
	ATLASSERT(string != NULL);
	if (string == NULL) return E_INVALIDARG;

	CMemberItem* pMItem = new CMemberItem;
	pMItem->m_name = string;
	m_members.Add(pMItem);

	return S_OK;
}
