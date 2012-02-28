// FileNewDlg.cpp : Implementation of CFileNewDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "FileNewDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CFilesView

#if 0

class CFileItem
{
public:
	CString m_pathName;
};

void FillFolders(IUITreeControl* tree, IUITreeItem* parentItem, TCHAR* filepath)
{
	HANDLE hFindFile;
	WIN32_FIND_DATA wfd;

	char	search[MAX_PATH];
	wsprintf(search, "%s\\*.*", filepath);

	if ((hFindFile = FindFirstFile(search, &wfd)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (wfd.cFileName[0] != '.')
			{
				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					char pathName[_MAX_PATH];
					_makepath(pathName, NULL, filepath, wfd.cFileName, NULL);

					CFileItem* pItem = new CFileItem;
					pItem->m_pathName = pathName;

					CComPtr<IUITreeItem> item;
					tree->InsertItem((DWORD)pItem, parentItem, NULL, _bstr_t(wfd.cFileName), 0/*iindex*/, -1, &item);

					FillFolders(tree, item, pathName);
				}
			}
		}
		while (FindNextFile(hFindFile, &wfd));

		FindClose(hFindFile);
	}
}

LRESULT CFilesView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CBitmap bmIcons;
	bmIcons.LoadBitmap(MAKEINTRESOURCE(IDB_CSSSTYLESHEETS));

	m_icons.Create(16, 16, ILC_COLOR8 | ILC_MASK, 1, 5);
	m_icons.Add(bmIcons, RGB(255, 255, 255));

//	m_tree.CoCreateInstance(CLSID_UITreeControl);
	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axtree.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axtree.AttachControl(m_tree, &p);
	IDispEventImpl<1, CFilesView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_tree);

	m_tree->put_hImageList((long)(HIMAGELIST)m_icons);

	m_list.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE, 0, 10/*nID*/);

	m_tree->InsertColumn(0, L"", 200, TRUE, TRUE, NULL);

	{
		TCHAR appdata[MAX_PATH];
		SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, appdata);

		TCHAR pathname[MAX_PATH];
		_makepath(pathname, NULL, appdata, "LXFramework", NULL);

		TCHAR templatesdir[MAX_PATH];
		_makepath(templatesdir, NULL, pathname, "templates", NULL);

		FillFolders(m_tree, NULL, templatesdir);
	}

	m_list.SetView(2);

	return 0;
}

LRESULT CFilesView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CFilesView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_tree);
	return 0;
}

LRESULT CFilesView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axtree.MoveWindow(0, 0, 130, client.bottom);
	m_list.MoveWindow(130+2, 0, client.right-132, client.bottom);

	return 0;
}

void __stdcall CFilesView::OnItemClick(IUITreeItem* item)
{
	m_list.RemoveItems();

	m_filesDocument.Release();

	m_filesDocument.CoCreateInstance(CLSID_LDOMDocument);
	VARIANT_BOOL success;
	m_filesDocument->loadXML(L"<files/>", &success);

	CComPtr<ILDOMElement> documentElement;
	m_filesDocument->get_documentElement(&documentElement);

	m_list.m_xmlDocument = m_filesDocument;

	CFileItem* pItem;
	m_tree->GetItemInfo(item, (DWORD*)&pItem, NULL, NULL);

	m_dir = pItem->m_pathName;

	HANDLE hFindFile;
	WIN32_FIND_DATA wfd;

	char search[MAX_PATH];
	wsprintf(search, "%s\\*.*", m_dir);

	if ((hFindFile = FindFirstFile(search, &wfd)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (wfd.cFileName[0] != '.')
			{
				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
				}
				else
				{
					CComPtr<ILDOMElement> element;
					m_filesDocument->createElement(L"file", &element);

					element->setAttribute(L"id", _bstr_t(wfd.cFileName));
					documentElement->appendChild(element, NULL);

					m_list.AddItem((DWORD)element.p, _bstr_t(wfd.cFileName));
				}
			}
		}
		while (FindNextFile(hFindFile, &wfd));

		FindClose(hFindFile);
	}

//	m_list.OnSize();
//	m_list.Invalidate();
//	CComBSTR text;
//	item->GetText(&text);
}

LRESULT CFilesView::OnClickFile(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_list.m_selectedItemIndex >= 0 && m_list.m_selectedItemIndex < m_list.m_items.GetSize())
	{
		CComPtr<ILDOMElement> element = (ILDOMElement*)m_list.m_items[m_list.m_selectedItemIndex]->m_element;

		CComBSTR name;
		element->getAttribute(L"id", &name);

		TCHAR filename[MAX_PATH];
		_makepath(filename, NULL, m_dir, _bstr_t(name), NULL);

		m_pathName = filename;
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CFileNewDlg

LRESULT CFileNewDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();

	return 0;
}

void CFileNewDlg::OnSize()
{
	CRect client;
	GetClientRect(&client);

	m_view.MoveWindow(0, 0, client.right, client.bottom-40);

	::MoveWindow(GetDlgItem(IDOK), client.right-160, client.bottom-30, 70, 22, TRUE);
	::MoveWindow(GetDlgItem(IDCANCEL), client.right-80, client.bottom-30, 70, 22, TRUE);
}

#endif