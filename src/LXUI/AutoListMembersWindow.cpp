#include "stdafx.h"
#include "LXUI2.h"
#include "AutoListMembersWindow.h"

namespace System
{
	using namespace MSWindows;

namespace UI
{

CAutoListMembersWindow::CAutoListMembersWindow()
{
//		m_memberImageList = NULL;

	m_selectedIndex = -1;
}

long CAutoListMembersWindow::GetCurSel()
{
	return m_selectedIndex;
}

int CAutoListMembersWindow::GetVisibleLines()
{
	return m_areaRect.GetHeight()/16;
}

StringW* CAutoListMembersWindow::GetStringAt(long index)
{
	return m_members[index]->m_name;
}

int CAutoListMembersWindow::FindMatch(const WCHAR* str, int len)
{
	for (int i = 0; i < m_members.GetSize(); i++)
	{
		if (!std::wcsncmp(str, m_members[i]->m_name->c_str(), len))
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

#if 0
void CAutoListMembersWindow::SetDispatch(IDispatch* pDisp)
{
	ASSERT(0);
#if 0
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

			pMItem->m_name = bname;
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

			m_members.push_back(pMItem);

			pTInfo->ReleaseFuncDesc(pFuncDesc);
		}
	}

	if (m_hWnd)
	{
		OnSize();
		Invalidate();
	}
#endif
}
#endif

LRESULT CAutoListMembersWindow::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ASSERT(0);
#if 0
	CPaintDC dc(m_hWnd);

	long scrollposY = 0;
#if 0
	long scrollposY; m_vert->get_pos(&scrollposY);
#endif

	POINT oldOrg;
	dc.SetViewportOrg(0, -scrollposY*16, &oldOrg);

	HFONT hOldFont = dc.SelectFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

	dc.SetBkMode(TRANSPARENT);

	int y = 0;

	for (int i = 0; i < m_members.size(); i++)
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
		ASSERT(0);
#if 0
		dc.DrawText(pMItem->m_name.c_str(), pMItem->m_name.length(), &trect, DT_SINGLELINE | DT_VCENTER);
#endif

		y += 16;
	}

	dc.SelectFont(hOldFont);

	dc.SetViewportOrg(oldOrg.x, oldOrg.y);
#endif
	return 0;
}

LRESULT CAutoListMembersWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);

	IDispEventImpl<1, CAutoListMembersWindow, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);
#endif

//	m_memberImageList = ImageList_LoadBitmap(_Module.m_hInstResource, MAKEINTRESOURCE(IDB_MEMBERLISTITEM), 16, 0, CLR_NONE);

	return 0;
}

LRESULT CAutoListMembersWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	if (m_memberImageList)
	{
		ImageList_Destroy(m_memberImageList);
		m_memberImageList = NULL;
	}
#endif

#if 0
	IDispEventImpl<1, CAutoListMembersWindow, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);
#endif

	return 0;
}

LRESULT CAutoListMembersWindow::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();

	return 0;
}

void CAutoListMembersWindow::OnSize()
{
	ASSERT(0);
#if 0
	CRect client;
	GetClientRect(&client);

	m_areaRect.left = 0;
	m_areaRect.top = 0;
	m_areaRect.right = client.right-16;
	m_areaRect.bottom = client.bottom;

#if 0
	m_axvert.MoveWindow(m_areaRect.right, 0, 16, m_areaRect.Height(), TRUE);

	m_vert->SetInfo(0, m_members.GetSize()-1, (m_areaRect.Height())/16);
#endif
#endif
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
	ASSERT(0);
#if 0
	long scrollposY;
#if 0
	m_vert->get_pos(&scrollposY);
#endif
	scrollposY = 0;

	if (m_selectedIndex != index)
	{
		m_selectedIndex = index;

		if (m_selectedIndex < 0) m_selectedIndex = 0;
		else if (m_selectedIndex > m_members.size()-1) m_selectedIndex = m_members.size()-1;

		int visibleLines = (m_areaRect.Height()/16);

		if (m_selectedIndex < scrollposY)
		{
#if 0
			m_vert->put_pos(m_selectedIndex);
#endif
		}
		else if (m_selectedIndex > scrollposY+visibleLines-1)
		{
#if 0
			m_vert->put_pos(m_selectedIndex - (visibleLines-1));
#endif
		}

		InvalidateRect(&m_areaRect);
	}
#endif
}

void __stdcall CAutoListMembersWindow::OnVertScroll(long code, long pos)
{
#if 0
	long oldPos; m_vert->get_pos(&oldPos);

	CRect	rect = m_areaRect;
	
	m_vert->put_pos(pos);
	ScrollWindow(0, (oldPos-pos)*16, &rect, &rect);
#endif
}

long CAutoListMembersWindow::AddString(long iImage, StringW* string)
{
	ASSERT(string != NULL);
	if (string == NULL) return -2;

	CMemberItem* pMItem = new CMemberItem;
	pMItem->m_name = string;
	m_members.push_back(pMItem);

	return 0;
}

}	// UI
}
