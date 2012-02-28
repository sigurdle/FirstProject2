// FileInspectorDlg.cpp : Implementation of CFileInspectorDlg
#include "stdafx.h"
#include "LXWebSite.h"
#include "LXWebSite2.h"
#include "FileInspectorDlg.h"

#include "SiteFilesView.h"
#include "WebSite.h"

/////////////////////////////////////////////////////////////////////////////
// CFileInspectorDlg

LRESULT CFileInspectorDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_bgBrush.CreateSolidBrush(GetSysColor(COLOR_WINDOW));

	SendDlgItemMessage(IDC_FILE_PUBLISH, CB_ADDSTRING, 0, (LPARAM)_T("Never"));
	SendDlgItemMessage(IDC_FILE_PUBLISH, CB_ADDSTRING, 0, (LPARAM)_T("Always"));
	SendDlgItemMessage(IDC_FILE_PUBLISH, CB_ADDSTRING, 0, (LPARAM)_T("If Referenced"));

	return 1;  // Let the system set the focus
}

LRESULT CFileInspectorDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_bgBrush.DeleteObject();

	SetFilesView(NULL);

	return 0;
}

LRESULT CFileInspectorDlg::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CDCHandle dc((HDC)wParam);

	CRect client;
	GetClientRect(&client);

	dc.FillRect(&client, m_bgBrush);

	return TRUE;
}

LRESULT CFileInspectorDlg::OnCtlColorStatic(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return (LRESULT)(HBRUSH)m_bgBrush;
}

void CFileInspectorDlg::SetFilesView(CSiteFilesView* pView)
{
	if (m_filesView)
	{
		IDispEventImpl<1, CFileInspectorDlg, &DIID__ISiteFilesViewEvents, &LIBID_LXWEBSITELib, 1, 0>::DispEventUnadvise(m_filesView->GetUnknown());
	}

	m_filesView = pView;

	if (m_filesView)
	{
		IDispEventImpl<1, CFileInspectorDlg, &DIID__ISiteFilesViewEvents, &LIBID_LXWEBSITELib, 1, 0>::DispEventAdvise(m_filesView->GetUnknown());
	}
}

void __stdcall CFileInspectorDlg::OnFileSelectionChanged()
{
	int nselected = 0;
	CString filename;
	DWORD fileSize = 0;

	int publish = -1;

	CComPtr<IUITreeItem> active;
	m_filesView->m_treeCtl->GetSelectedItem(&active);

	if (active)
	{
		CComPtr<IUITreeItem> parentitem;
		m_filesView->m_treeCtl->GetParentItem(active, &parentitem);

		CComPtr<IUITreeItem> child;

		m_filesView->m_treeCtl->GetFirstChildItem(parentitem, &child);
		while (child)
		{
			DWORD state;
			m_filesView->m_treeCtl->GetItemState(child, &state);

			if (state & 1)
			{
				CSiteFilesView::CSiteItem* pItem;
				m_filesView->m_treeCtl->GetItemInfo(child, (DWORD*)&pItem, NULL, NULL);

				nselected++;

				if (nselected == 1)
				{
					filename = pItem->m_wfd.cFileName;
				}
				else
					filename.Empty();

				if (pItem->m_type == 2)
				{
					CSiteFilesView::CSiteFile* pFile = (CSiteFilesView::CSiteFile*)pItem;

					if (nselected == 1)
					{
						publish = pFile->m_publish;
					}
					else if (publish != pFile->m_publish)
					{
						publish = -1;
					}
				}
				else
					publish = -1;

				fileSize += pItem->m_wfd.nFileSizeLow;
			}

			CComPtr<IUITreeItem> next;
			m_filesView->m_treeCtl->GetNextSiblingItem(child, &next);
			child = next;
		}
	}

	if (nselected == 1)
	{
		SetDlgItemText(IDC_FILE_NAME, filename);
	}
	else
	{
		TCHAR buf[256];
		sprintf(buf, "%d items selected", nselected);
		SetDlgItemText(IDC_FILE_NAME, buf);
	}

	SendDlgItemMessage(IDC_FILE_PUBLISH, CB_SETCURSEL, publish);

	{
		TCHAR buf[64];
		int len;

		if (fileSize < 1024)
		{
			len = sprintf(buf, "%d byte", fileSize);
		}
		else
		{
			len = sprintf(buf, "%.1f kB", fileSize / 1024.0);
		}

		SetDlgItemText(IDC_FILE_SIZE, buf);
	}
}

void CFileInspectorDlg::UpdateSelectedItems(ILDOMDocument* document)
{
	CComBSTR xmltext;
	document->saveXML(_variant_t(), &xmltext);

	CComPtr<IUITreeItem> active;
	m_filesView->m_treeCtl->GetSelectedItem(&active);

	if (active)
	{
		CComPtr<IUITreeItem> parentitem;
		m_filesView->m_treeCtl->GetParentItem(active, &parentitem);

		CComPtr<IUITreeItem> child;

		m_filesView->m_treeCtl->GetFirstChildItem(parentitem, &child);
		while (child)
		{
			DWORD state;
			m_filesView->m_treeCtl->GetItemState(child, &state);

			if (state & 1)
			{
				CSiteFilesView::CSiteItem* pItem;
				m_filesView->m_treeCtl->GetItemInfo(child, (DWORD*)&pItem, NULL, NULL);

				HRESULT hr = m_filesView->m_document->m_webSite->UpdateItem(_bstr_t(pItem->GetFullDisplayName()), xmltext);
				if (FAILED(hr))
				{
					MessageBox("Failed to update item", "LXWebSite", MB_OK);
				}
			}

			CComPtr<IUITreeItem> next;
			m_filesView->m_treeCtl->GetNextSiblingItem(child, &next);
			child = next;
		}
	}
}

LRESULT CFileInspectorDlg::OnFileChangePublish(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int cursel = SendDlgItemMessage(IDC_FILE_PUBLISH, CB_GETCURSEL);
	if (cursel >= 0)
	{
		CComPtr<ILDOMDocument> document;
		if (SUCCEEDED(document.CoCreateInstance(CLSID_LDOMDocument)))
		{
			VARIANT_BOOL success;
			document->loadXML(L"<item/>", &success);

			CComPtr<ILDOMElement> element;
			document->get_documentElement(&element);

			CComBSTR publish;
			if (cursel == 0) publish = L"0";
			else if (cursel == 1) publish = L"1";
			else if (cursel == 2) publish = L"2";

			element->setAttribute(L"publish", publish);

			UpdateSelectedItems(document);
		}
		else
		{
			MessageBox("Failed to create dom document", "LXWebSite", MB_OK);
		}
	}

	return 0;
}
