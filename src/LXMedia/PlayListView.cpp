// PlayListView.cpp : Implementation of CPlayListView
#include "stdafx.h"
#include "LXMedia.h"
#include "LXMedia2.h"

#include "PlayListView.h"

#include "EPlayListDocument.h"

#define PANE_TITLE		0
#define PANE_DURATION	1
#define PANE_DATE			2
#define PANE_FILESIZE	3
#define PANE_FILEPATH	4

////////////////////////////////////////////////////////////////////////
// CPlayListView

int CPlayListView::FinalConstruct()
{
	HRESULT hr;

	hr = m_treeCtl.CoCreateInstance(CLSID_UITreeControl);
	if (FAILED(hr)) return hr;

	m_treeCtl->SetSite(this);

	m_treeCtl->InsertColumn(PANE_TITLE, L"Title", 120, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_DURATION, L"Length", 120, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_DATE, L"Date", 80, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_FILESIZE, L"File Size", 60, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_FILEPATH, L"File Location", 200, TRUE, TRUE, NULL);

	return S_OK;
}

void CPlayListView::FinalRelease()
{
}

LRESULT CPlayListView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	/*
	SHFILEINFO	ssfi;	//get a handle to the system small icon list 

	m_hFileIcons = (HIMAGELIST)::SHGetFileInfo(
		(LPCTSTR)_T("C:\\"),
		0,
		&ssfi, sizeof(SHFILEINFO),
		SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
*/
	IUnknown* p;

	CRect rc(0,0,0,0);
	m_axtreeCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axtreeCtl.AttachControl(m_treeCtl, &p);

	UPOSITION pos = m_pDocument->m_items.GetHeadPosition();
	while (pos)
	{
		CPlayListItem* pItem = (CPlayListItem*)m_pDocument->m_items.GetNext(pos);

		m_treeCtl->InsertItem((DWORD)pItem, NULL/*parentItem*/, NULL, NULL, -1/*pItem->m_iIcon*/, 0/*pItem->m_cChildren*/, &pItem->m_treeItem);
	}

	return 0;
}

LRESULT CPlayListView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CPlayListView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect	client;
	GetClientRect(&client);

	int top = 0;//m_titleHeight;

	int cx = client.Width();
	int cy = client.Height();

	m_axtreeCtl.MoveWindow(0, top, cx, cy-top, TRUE);

	return 0;
}

STDMETHODIMP CPlayListView::GetItemText(ULONG itemdata, LONG column, BSTR * pVal)
{
	USES_CONVERSION;

	*pVal = NULL;

	CPlayListItem* pItem = (CPlayListItem*)itemdata;

	switch (column)
	{
	case PANE_TITLE:
		{
			*pVal = SysAllocString(A2W(pItem->m_title));
		}
		break;

	case PANE_DURATION:
		{
			int minutes = pItem->m_duration / 60;
			int seconds = (pItem->m_duration-minutes*60);

			WCHAR s[64];
			swprintf(s, L"%d:%d", minutes, seconds);
			*pVal = SysAllocString(s);
		}
		break;

	case PANE_DATE:
		{
			char buf[64];

			SYSTEMTIME systime;
			FileTimeToSystemTime(&pItem->m_lastModified, &systime);
			int len = GetDateFormat(NULL, DATE_SHORTDATE, &systime, NULL, buf, sizeof(buf));

			*pVal = SysAllocString(_bstr_t(buf));
		}
		break;

	case PANE_FILEPATH:
		{
			*pVal = SysAllocString(A2W(pItem->m_filename));
		}
		break;

	case PANE_FILESIZE:
		{
			WCHAR buf[64];
			int len;

			if (pItem->m_fileSize < 1024)
			{
				len = swprintf(buf, L"%d byte", (DWORD)pItem->m_fileSize);
			}
			else
			{
				len = swprintf(buf, L"%.1f kB", ((DWORD)pItem->m_fileSize) / 1024.0);
			}

			*pVal = SysAllocString(buf);
		}
		break;
	}

	return S_OK;
}

// ICommandTarget

BEGIN_CMD_MAP(CPlayListView)
//	CMD_HANDLER(ID_EDIT_PLAY, OnPlay)
END_CMD_MAP()

STDMETHODIMP CPlayListView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	CComQIPtr<ICommandTarget> target;

// Try document
	target = m_pDocument;
	if (target)
	{
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
	}

	return S_OK;
}
