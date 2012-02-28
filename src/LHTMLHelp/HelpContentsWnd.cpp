// HelpContentsWnd.cpp : Implementation of CHelpContentsWnd
#include "stdafx.h"
#include "LHTMLHelp.h"
#include "HelpContentsWnd.h"

#include "HelpView.h"

/////////////////////////////////////////////////////////////////////////////
// CHelpContentsWnd

void CTocEntry::BuildNode(ILDOMElement* xmlnode)
{
	CComQIPtr<ILDOMElement>	child;
	xmlnode->get_firstChild((ILDOMNode**)&child);
	while (child != NULL)
	{
		//if (child->nodeType == SVGLib::NODE_ELEMENT)
		{
			BSTR name; child->getAttribute(L"name", &name);
			BSTR url; child->getAttribute(L"url", &url);

			CTocEntry* pEntry = new CTocEntry;
			pEntry->m_name = name;
			pEntry->m_url = url;

			SysFreeString(name);
			SysFreeString(url);

			pEntry->BuildNode(child);

			AddChildTail(pEntry);
		}

		CComQIPtr<ILDOMElement> nextSibling;
		child->get_nextSibling((ILDOMNode**)&nextSibling);
		child = nextSibling;
	}
}

STDMETHODIMP CHelpContentsWnd::LoadTOC(BSTR pathName, BOOL *success)
{
	m_tocFilePathName = pathName;

	TCHAR dir[256];
	TCHAR path[256];
	_splitpath(m_tocFilePathName, dir, path, NULL, NULL);

	_makepath(m_tocPathName.GetBuffer(256), dir, path, NULL, NULL);
	m_tocPathName.ReleaseBuffer();

	CComQIPtr<ILDOMDocument> xmldoc;
	xmldoc.CoCreateInstance(CLSID_LDOMDocument);
	ATLASSERT(xmldoc != NULL);
	xmldoc->put_async(VARIANT_FALSE);

	VARIANT_BOOL bsuccess;
	xmldoc->load(_bstr_t(m_tocFilePathName), &bsuccess);
	m_pTreeItem = new CTocEntry;

	CComQIPtr<ILDOMElement> documentElement;
	xmldoc->get_documentElement(&documentElement);
	if (documentElement)
	{
		m_pTreeItem->BuildNode(documentElement);
	}

	if (success)
		*success = TRUE;

	return S_OK;
}

long CHelpContentsWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	if (HANDLE_BASE<IUIControl>(m_puiwnd, uMsg, wParam, lParam) != 0)
//		return -1;

//	m_horz->CreateControl(m_hWnd, 0, 0, SBS_HORZ | WS_VISIBLE, 0, 0, 0, 0, NULL);
//	m_vert->CreateControl(m_hWnd, 0, 0, SBS_VERT | WS_VISIBLE, 0, 0, 0, 0, NULL);

	m_hIconsBitmap = LoadBitmap(_Module.m_hInst, MAKEINTRESOURCE(IDB_HELPICONS));

	return 0;
}

long CHelpContentsWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DeleteObject(m_hIconsBitmap);

	return 0;
}

long CHelpContentsWnd::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	BeginPaint(&ps);
	HDC hDC = ps.hdc;

	RECT client;
	GetClientRect(&client);

	FillSolidRect(hDC, 0, 0, client.right, client.bottom, RGB(255, 255, 255));

	HFONT hOldFont = (HFONT)SelectObject(hDC, GetStockObject(DEFAULT_GUI_FONT));

	long scrollposX = 0;// m_horz->get_pos(&scrollposX);
	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

	POINT oldOrg;
	SetViewportOrgEx(hDC, -scrollposX, -scrollposY, &oldOrg);

	HDC hBmDC = CreateCompatibleDC(NULL);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hBmDC, m_hIconsBitmap);

	int y = 0;

	C2Obj* pParentItem = m_pTreeItem;
	if (pParentItem)
	{
		UPOSITION pos = pParentItem->GetHeadPosition();
		int	nextlevel = 0;

		while (pos)
		{
			int level = nextlevel;
			CTocEntry* pItem = (CTocEntry*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

			int x = level*16;

			int bmindex;
			if (pItem->HasChildren())
			{
				if (!pItem->m_expanded)
					bmindex = 0;
				else
					bmindex = 1;
			}
			else
				bmindex = 2;

			BitBlt(hDC, x, y, 16, 15, hBmDC, bmindex*16, 0, SRCCOPY);

			TextOut(hDC, x+18, y, pItem->m_name, pItem->m_name.length());

			y += 16;
		}
	}

	SelectObject(hBmDC, hOldBitmap);
	DeleteObject(hBmDC);

	SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
	SelectObject(hDC, hOldFont);

	EndPaint(&ps);
	return 0;
}

long CHelpContentsWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

void CHelpContentsWnd::OnSize()
{
	RECT client;
	GetClientRect(&client);
	int cx = client.right;
	int cy = client.bottom;
	int sbHeight = GetSystemMetrics(SM_CYHSCROLL);
	int sbWidth = GetSystemMetrics(SM_CXVSCROLL);

	client.right -= sbWidth;
	client.bottom -= sbHeight;

	int height = 0;
	int width = 0;

	if (m_pTreeItem)
	{
		HDC hDC = CreateCompatibleDC(NULL);
		HFONT hOldFont = (HFONT)SelectObject(hDC, GetStockObject(DEFAULT_GUI_FONT));

		C2Obj* pParentItem = m_pTreeItem;
		UPOSITION pos = pParentItem->GetHeadPosition();
		int	nextlevel = 0;

		while (pos)
		{
			int level = nextlevel;
			CTocEntry* pItem = (CTocEntry*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

			int x = level*16;

			SIZE size;
			GetTextExtentPoint32(hDC, pItem->m_name, pItem->m_name.length(), &size);

			width = max(width, x + 18 + size.cx);
			height += 16;
		}

		SelectObject(hDC, hOldFont);
		DeleteDC(hDC);
	}

#if 0
	m_horz->MoveWindow(0, cy-sbHeight, cx-sbWidth, sbHeight, TRUE);
	m_vert->MoveWindow(cx-sbWidth, 0, sbWidth, cy-sbHeight, TRUE);

	m_vert->SetInfo(0, height, client.bottom);
	m_horz->SetInfo(0, width, client.right);
#endif
}

long CHelpContentsWnd::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposX = 0;// m_horz->get_pos(&scrollposX);
	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

	POINT pt = point;
	pt.x += scrollposX;
	pt.y += scrollposY;

	C2Obj* pParentItem = m_pTreeItem;
	UPOSITION pos = pParentItem->GetHeadPosition();
	int nextlevel = 0;
	int level;

	int y = 0;

	CTocEntry* pFItem = NULL;

	while (pos)
	{
		level = nextlevel;
		CTocEntry* pItem = (CTocEntry*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

		y += 16;
		
		if (pt.y < y)
		{
			pFItem = pItem;
			break;
		}
	}

	if (pFItem)
	{
		int x = level*16;

		if ((pt.x >= x) && (pt.x < x+16))
		{
			pFItem->m_expanded = !pFItem->m_expanded;
			InvalidateRect(NULL, TRUE);
			OnSize();
		}
		else
		{
			if (!pFItem->m_url.IsEmpty())
			{
				TCHAR cpath[512];

				if ((((LPCTSTR)pFItem->m_url)[1] == ':') ||
					pFItem->m_url.Left(4) == "http")	// Absolute path
				{
					strcpy(cpath, pFItem->m_url);
				}
				else
				{
					_makepath(cpath, NULL, m_tocPathName, pFItem->m_url, NULL);
				}

				/*
				CComQIPtr<IUIWnd> parent;
				get_parent(&parent);

				CComQIPtr<IHelpView> view = parent;

				CComQIPtr<IHTMLControl> html;
				view->get_html(&html);

				BOOL success;
				html->GotoLocation(_bstr_t(cpath), &success);
				*/

				VARIANT_BOOL success;
				m_view->m_html->GotoLocation(_bstr_t(cpath), &success);
			}
		}
	}

	return 0;
}

HRESULT __stdcall CHelpContentsWnd::OnHorzScroll(long code, long pos)
{
	return S_OK;
}

HRESULT __stdcall CHelpContentsWnd::OnVertScroll(long code, long pos)
{
	return S_OK;
}
