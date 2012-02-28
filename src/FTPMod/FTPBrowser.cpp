// FTPBrowser.cpp : Implementation of CFTPBrowser

#include "stdafx.h"
#include "FTPMod.h"
#include "FTPBrowser.h"

#define PANE_NAME		0
#define PANE_STATUS	1
#define PANE_SIZE		2
#define PANE_DATE		3

static int m_titleHeight = 20;

#include "../LXUI/LXUIDockPanel.h"
#include "../LXUI/LXUIImage.h"
#include "../LXUI/ScrollViewer.h"

BOOL AfxParseURL(LPCTSTR pstrURL, DWORD& dwServiceType,
	CString& strServer, CString& strObject, INTERNET_PORT& nPort);

void WinError(HWND hParent, DWORD lastError)
{
	LPVOID lpMsgBuf;

	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		lastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
		);
	// Process any inserts in lpMsgBuf.
	// ...
	// Display the string.
	MessageBox(hParent, (LPCTSTR)lpMsgBuf, "FTP", MB_OK | MB_ICONINFORMATION );
	// Free the buffer.
	LocalFree( lpMsgBuf );
}

CFTPBrowser::CSiteDir::CSiteDir()
{
	m_type = 1;
	m_bPopulated = FALSE;
}

CFTPBrowser::CSiteDir::~CSiteDir()
{
	/*
	while (!m_childList.IsEmpty())
	{
		CSiteItem* pItem = (CSiteItem*)m_childList.RemoveHead();
		delete pItem;
	}
	*/
}

sysstring CFTPBrowser::CSiteItem::GetFullPathName()
{
	USES_CONVERSION;

	CSiteDir* pParentDir = m_parent;

	if (pParentDir)
	{
		TCHAR pathName[_MAX_PATH];
		//if (pParentDir->m_parent)
		{
			wsprintf(pathName, "%s/%s", W2A(pParentDir->GetFullPathName().c_str()), m_wfd.cFileName);
		}
		/*
		else
		{
			wsprintf(pathName, "%s", m_wfd.cFileName);
		}
		*/
		wsprintf(pathName, "%s", m_wfd.cFileName);

//		_makepath(pathName, NULL, pDir->GetFullPathName(), m_wfd.cFileName, NULL);

		return A2W(pathName);
	}
	else
	{
		return A2W(m_wfd.cFileName);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFTPBrowser
/*
int CFTPBrowser::FinalConstruct()
{
	HRESULT hr;

	hr = m_editCtl.CoCreateInstance(CLSID_UIEdit);
	if (FAILED(hr)) return hr;

	hr = m_buttonsCtl.CoCreateInstance(CLSID_UIToolbarButtons);
	if (FAILED(hr)) return hr;

	hr = m_treeCtl.CoCreateInstance(CLSID_UITreeControl);
	if (FAILED(hr)) return hr;
	m_treeCtl->SetSite(this);
	m_treeCtl->InsertColumn(PANE_NAME, L"Name", 140, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_STATUS, L"Status", 80, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_SIZE, L"Size", 60, FALSE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_DATE, L"Date", 80, FALSE, TRUE, NULL);

	return S_OK;
}

void CFTPBrowser::FinalRelease()
{
}
*/

CFTPBrowser::CFTPBrowser()
{
	m_hButtonsBitmap = NULL;

	m_hInternet = NULL;
	m_hInternetFtp = NULL;

	m_pRootDir = NULL;
	m_prevDropItem = NULL;

	m_UserName = L"anonymous";
	m_Directory = L"";

	SHFILEINFO	ssfi;	//get a handle to the system small icon list 

	m_hFileIcons = (HIMAGELIST)::SHGetFileInfo(
		(LPCTSTR)_T("C:\\"),
		0,
		&ssfi, sizeof(SHFILEINFO),
		SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

	ScrollViewer* pScroller = new ScrollViewer;
	{
		m_treeCtl = new TreeControl;
		m_treeCtl->m_treeHeader->AddColumn(new TextString(OLESTR("Filename")));
		m_treeCtl->m_treeHeader->AddColumn(new TextString(OLESTR("Filesize")));
//		m_treeCtl->put_hImageList(m_hFileIcons);

		pScroller->put_Content(m_treeCtl);
	}
	put_VisualTree(pScroller);
}

void CFTPBrowser::handleEvent(LXUIEvent* evt)
{
	sysstring type = evt->get_type();

	if (evt->get_eventPhase() != CAPTURING_PHASE)
	{
		if (type == OLESTR("ItemExpanding"))
		{
			OnItemExpanding(evt);
			evt->stopPropagation();
		}
		else if (type == OLESTR("DragOver"))
		{
			MessageBeep(-1);
		}
	}
}

LRESULT CFTPBrowser::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SHFILEINFO	ssfi;	//get a handle to the system small icon list 

	m_hFileIcons = (HIMAGELIST)::SHGetFileInfo(
		(LPCTSTR)_T("C:\\"),
		0,
		&ssfi, sizeof(SHFILEINFO),
		SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

	m_hButtonsBitmap = LoadBitmap(_Module.m_hInstResource, MAKEINTRESOURCE(IDB_FTPBROWSER_BUTTONS));

	/*
	IUnknown* p;
	CRect rc(0,0,0,0);

	m_axeditCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED);
	m_axeditCtl.AttachControl(m_editCtl, &p);

	m_axbuttonsCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED);
	m_axbuttonsCtl.AttachControl(m_buttonsCtl, &p);
	m_buttonsCtl->SetBitmap((struct _userHBITMAP *)m_hButtonsBitmap, 16);
	m_buttonsCtl->AddButton(1, 0);
	m_buttonsCtl->AddButton(2, 1);
	IDispEventImpl<3, CFTPBrowser, &DIID__IUIToolbarButtonsEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_buttonsCtl);

	m_axtreeCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED);
	m_axtreeCtl.AttachControl(m_treeCtl, &p);
	*/
//	m_treeCtl->put_hImageList(m_hFileIcons);
	/*
	IDispEventImpl<4, CFTPBrowser, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_treeCtl);

	::RegisterDragDrop(m_hWnd, this);
*/

	return 0;
}

LRESULT CFTPBrowser::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	IDispEventImpl<3, CFTPBrowser, &DIID__IUIToolbarButtonsEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_buttonsCtl);
//	IDispEventImpl<4, CFTPBrowser, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_treeCtl);

	if (m_hButtonsBitmap)
	{
		DeleteObject(m_hButtonsBitmap);
		m_hButtonsBitmap = NULL;
	}

//	::RevokeDragDrop(m_hWnd);

	return 0;
}

LRESULT CFTPBrowser::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
//	InvalidateRect(NULL, TRUE);
	return 0;
}

void CFTPBrowser::OnSize()
{
	/*
	CRect	client;
	GetClientRect(&client);

	int top = m_titleHeight;

	int cx = client.Width();
	int cy = client.Height();

	m_axeditCtl.MoveWindow(0, 1, cx-38, top-2, TRUE);
	m_axbuttonsCtl.MoveWindow(cx-38, 0, 38, top, TRUE);
	m_axtreeCtl.MoveWindow(0, top, cx, cy-top, TRUE);
	*/
}

#if 0
void __stdcall CFTPBrowser::OnToolbarButtonClick(long buttonid)
{
	switch (buttonid)
	{
	case 1:	// One level up
		{
			if (m_pRootDir)
			{
			// Get parent directory path
				TCHAR newpath[1024];
				strcpy(newpath, m_pRootDir->GetFullPathName());

				int len = strlen(newpath);

				TCHAR* p = newpath + len-1;
				while (len >= 0)
				{
					if (*p == '/')
					{
						*p = 0;	// End the string here
						break;
					}

					p--;
					len--;
				}

				put_Directory(_bstr_t(newpath));
			}
		}
		break;

	case 2:	// New Folder
		{
			if (m_hInternetFtp)
			{
				CSiteDir* pParent;

				CComPtr<IUITreeItem> active;
				m_treeCtl->GetSelectedItem(&active);

				if (active)
				{
					CSiteItem* pItem;
					m_treeCtl->GetItemInfo(active, (DWORD*)&pItem, NULL, NULL);

					if (pItem->m_type == 1)
						pParent = (CSiteDir*)pItem;
					else
						pParent = pItem->m_parent;
				}
				else
				{
					pParent = m_pRootDir;
				}

				ATLASSERT(pParent);

				CSiteDir* pNewDir = new CSiteDir;
				pNewDir->m_wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
				lstrcpy(pNewDir->m_wfd.cFileName, _T("New Folder"));
				pNewDir->m_parent = pParent;
				pNewDir->m_bNew = true;

				SHFILEINFO sfi;
				::SHGetFileInfo(
					pNewDir->m_wfd.cFileName,
					(pNewDir->m_type == 1)? FILE_ATTRIBUTE_DIRECTORY: FILE_ATTRIBUTE_NORMAL,
					&sfi,
					sizeof(SHFILEINFO),
					SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES);
				pNewDir->m_iIcon = sfi.iIcon;

				m_treeCtl->InsertItem((DWORD)pNewDir, pParent->m_treeItem, NULL, NULL/*name*/, pNewDir->m_iIcon, (pNewDir->m_type == 1)? 1: 0, &pNewDir->m_treeItem);
				m_treeCtl->EditLabel(pNewDir->m_treeItem, NULL);
			}
		}
		break;
	}
}

STDMETHODIMP CFTPBrowser::GetItemText(ULONG itemdata, LONG column, BSTR *pVal)
{
	*pVal = NULL;

	CSiteItem* pNode = (CSiteItem*)itemdata;

	if (pNode->m_bNew)
	{
		switch (column)
		{
			case PANE_NAME:
				*pVal = SysAllocString(_bstr_t(pNode->m_wfd.cFileName));
			break;

			default:
				*pVal = SysAllocString(L"");
		}
	}
	else
	{
		switch (column)
		{
		case PANE_NAME:
			*pVal = SysAllocString(_bstr_t(pNode->m_wfd.cFileName));
		break;

		case PANE_SIZE:
			if (pNode->m_type == 2)
			{
				WCHAR buf[64];
				int len;
				CSiteFile* pFile = (CSiteFile*)pNode;

				if (pFile->m_wfd.nFileSizeLow < 1024)
				{
					len = swprintf(buf, L"%d byte", pFile->m_wfd.nFileSizeLow);
				}
				else
				{
					len = swprintf(buf, L"%.1f kB", pFile->m_wfd.nFileSizeLow / 1024.0);
				}

				*pVal = SysAllocString(buf);
			}
			break;

		case PANE_DATE:
			{
				CSiteFile* pFile = (CSiteFile*)pNode;
				char buf[64];

				SYSTEMTIME systime;
				FileTimeToSystemTime(&pFile->m_wfd.ftLastWriteTime, &systime);
				int len = GetDateFormat(NULL, DATE_SHORTDATE, &systime, NULL, buf, sizeof(buf));

				*pVal = SysAllocString(_bstr_t(buf));
			}
			break;
		}
	}

	return S_OK;
}
#endif

#if 0
void __stdcall CFTPBrowser::OnItemClick(IUITreeItem* item)
{
}

void __stdcall CFTPBrowser::OnItemDblClick(IUITreeItem* item)
{
	CComPtr<IUITreeItem> active;
	m_treeCtl->GetSelectedItem(&active);

	if (active)
	{
		CSiteItem* pItem;
		m_treeCtl->GetItemInfo(active, (DWORD*)&pItem, NULL, NULL);
		if (pItem->m_type == 1)	// Double-clicking on folder sets it as new root-folder
		{
			CSiteDir* pDir = (CSiteDir*)pItem;
			put_Directory(_bstr_t(pDir->GetFullPathName()));
		}
		else
		{
			CComPtr<IUITreeItem> parentitem;
			m_treeCtl->GetParentItem(active, &parentitem);

			CComPtr<IUITreeItem> child;

			m_treeCtl->GetFirstChildItem(parentitem, &child);
			while (child)
			{
				DWORD state;
				m_treeCtl->GetItemState(child, &state);

				if (state & 1)
				{
					CSiteItem* pFile;
					m_treeCtl->GetItemInfo(child, (DWORD*)&pFile, NULL, NULL);

					/*
					VARIANT_BOOL success;
					pWebSite->OpenDocument(pFile->m_dbid, &success);
					*/
					TCHAR urlpath[512];
					strcpy(urlpath, pFile->GetFullPathName());

					URL_COMPONENTS url_components = {0};
					url_components.dwStructSize = sizeof(url_components);
					url_components.nScheme = INTERNET_SCHEME_FTP;
					url_components.nPort = m_nPort;
					url_components.lpszUserName = m_UserName;
					url_components.dwUserNameLength = m_UserName.length();
					url_components.lpszPassword = m_Password;
					url_components.dwPasswordLength = m_Password.length();
					url_components.lpszHostName = (char*)(LPCSTR)m_strServer;
					url_components.dwHostNameLength = m_strServer.GetLength();
					url_components.lpszUrlPath = urlpath;
					url_components.dwUrlPathLength = strlen(url_components.lpszUrlPath);

					TCHAR url[1024];
					DWORD urlLength = _countof(url);
					InternetCreateUrl(&url_components, 0, url, &urlLength);

					//CComBSTR url = (BSTR)m_ServerName;
					//url += (BSTR)_bstr_t(pFile->GetFullPathName());

					Fire_DblClick(_bstr_t(url));
				}

				CComPtr<IUITreeItem> next;
				m_treeCtl->GetNextSiblingItem(child, &next);
				child = next;
			}
		}
	}
}

void __stdcall CFTPBrowser::OnContextMenu(long x, long y)
{
}
#endif

void CFTPBrowser::OnItemExpanding(LXUIEvent* evt)
{
	TreeItem* item = dynamic_cast<TreeItem*>(evt->get_target());//, VARIANT_BOOL bExpanding, BOOL* bCancel
	bool bExpanding = true;

	CSiteDir* pDir = (CSiteDir*)item->m_itemData;
//	m_treeCtl->GetItemInfo(item, (DWORD*)&pDir, NULL, NULL);

	if (pDir->m_type == 1)	// Expanding Folder
	{
		if (bExpanding)
		{
			if (!pDir->m_bPopulated)
				PopulateFolder(item, pDir, false);
		}
	}
}

#if 0
void __stdcall CFTPBrowser::OnEndLabelEdit(IUITreeItem* item, BSTR text)
{
	if (m_hInternetFtp)
	{
		CSiteItem* pItem;
		m_treeCtl->GetItemInfo(item, (DWORD*)&pItem, NULL, NULL);

		if (pItem->m_bNew)
		{
			pItem->m_bNew = false;
			strcpy(pItem->m_wfd.cFileName, _bstr_t(text));

			if (pItem->m_type == 1)
			{
				BOOL success = FtpCreateDirectory(m_hInternetFtp, pItem->GetFullPathName());
				if (!success)
				{
					DWORD dw;
					TCHAR msg[1024];
					DWORD len = 1024;
					InternetGetLastResponseInfo(&dw, msg, &len);

					CUString str;
					str.Format("Couldn't create directory \"%s\"\n\n%s", pItem->GetFullPathName(), msg);
					MessageBox(str, "FTP", MB_OK);
				}

				PopulateFolder(pItem->m_parent->m_treeItem, pItem->m_parent, true);
			}
			else
			{
			}
		}
		else
		{
			if (wcscmp(_bstr_t(pItem->m_wfd.cFileName), text) != 0)
			{
				CUString parentPath = pItem->m_parent->GetFullPathName();
				_bstr_t atext = text;

				char newPathName[_MAX_PATH];
				_makepath(newPathName, NULL, parentPath, atext, NULL);

				BOOL bSuccess = FtpRenameFile(m_hInternetFtp, pItem->GetFullPathName(), newPathName);
				if (!bSuccess)
				{
					WinError(m_hWnd, GetLastError());
				}
			}
		}
	}
}
#endif

sysstring CFTPBrowser::get_ServerName()
{
	return m_ServerName;
}

STDMETHODIMP CFTPBrowser::put_ServerName(BSTR newVal)
{
	m_ServerName = newVal;
	return S_OK;
}

sysstring CFTPBrowser::get_UserName()
{
	return m_UserName;
}

STDMETHODIMP CFTPBrowser::put_UserName(BSTR newVal)
{
	m_UserName = newVal;
	return S_OK;
}

sysstring CFTPBrowser::get_Password()
{
	return m_Password;
}

STDMETHODIMP CFTPBrowser::put_Password(BSTR newVal)
{
	m_Password = newVal;
	return S_OK;
}

sysstring CFTPBrowser::get_Directory()
{
	return m_Directory;
}

STDMETHODIMP CFTPBrowser::put_Directory(BSTR newVal)
{
	m_Directory = newVal;
	if (m_hInternetFtp)
	{
		SetDirectory();
	}

	return S_OK;
}

void CFTPBrowser::PopulateFolder(TreeItem* parentItem, CSiteDir* pParentDir, bool bCheckExisting)
{
	USES_CONVERSION;

	ATLASSERT(pParentDir);

	pParentDir->m_bPopulated = true;

	if (bCheckExisting)
	{
		ATLASSERT(0);
#if 0
	// Mark all files as not found on disk (yet)
		TreeItem* child;
		m_treeCtl->GetFirstChildItem(parentItem, &child);
		while (child)
		{
			CSiteItem* pItem;
			m_treeCtl->GetItemInfo(child, (DWORD*)&pItem, NULL, NULL);
			pItem->m_bFoundOnDisk = false;

			CComPtr<IUITreeItem> next;
			m_treeCtl->GetNextSiblingItem(child, &next);
			child = next;
		}
#endif
	}

	HINTERNET hFindFile;
	WIN32_FIND_DATA	wfd;

	TCHAR search[1024];
//	DWORD len = 1024;
//	InternetCanonicalizeUrl(pParentDir->GetFullPathName(), search, &len, 0);

//	strcpy(search, "\"" + pParentDir->GetFullPathName() + "\"");

	sysstring pathname = pParentDir->GetFullPathName();
	const OLECHAR* p = pathname.c_str();
	TCHAR* d = search;
	while (*p)
	{
		if (*p == ' ')
		{
			*d++ = '%';
			*d++ = '2';
			*d++ = '0';
			p++;
		}
		else
		{
			*d++ = *p++;
		}
	}

	*d = 0;

//	strcpy(search, pParentDir->GetFullPathName());

//	MessageBox(search, "", MB_OK);

	if ((hFindFile = FtpFindFirstFile(
		m_hInternetFtp,
		search,
		&wfd,
		INTERNET_FLAG_RELOAD,
		0/*dwContext*/)) != NULL/*INVALID_HANDLE_VALUE*/)
	{
		do
		{
			if (wfd.cFileName[0] != '.')
			{
				CSiteItem* pItem = NULL;
				CSiteItem* pExistingItem;

				if (bCheckExisting)
					pExistingItem = FindFileByFileName(parentItem, wfd.cFileName, (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)? 1: 2);
				else
					pExistingItem = NULL;

				if (pExistingItem == NULL)
				{
					if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						CSiteDir* pDir = new CSiteDir;
						pItem = pDir;
					}
					else
					{
						CSiteFile* pFile = new CSiteFile;
						pItem = pFile;
					}
				}
				else
				{
					pItem = pExistingItem;
				}

				if (pItem)
				{
					pItem->m_parent = pParentDir;
					pItem->m_wfd = wfd;
					pItem->m_bFoundOnDisk = true;

					SHFILEINFO sfi;
					::SHGetFileInfo(
						pItem->m_wfd.cFileName,
						(pItem->m_type == 1)? FILE_ATTRIBUTE_DIRECTORY: FILE_ATTRIBUTE_NORMAL,
						&sfi,
						sizeof(SHFILEINFO),
						SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES);
					pItem->m_iIcon = sfi.iIcon;

					if (pExistingItem == NULL)
					{
						pItem->m_treeItem = new TreeItem(m_treeCtl);
					//	pItem->m_treeItem->m_iIndex = sfi.iIcon;
						{
							{
								DockPanel* pContent = new DockPanel;
								{
									int cx;
									int cy;
									ImageList_GetIconSize(m_hFileIcons, &cx, &cy);

									HICON hIcon = ImageList_GetIcon(m_hFileIcons, sfi.iIcon, ILD_NORMAL);

									ICONINFO iconinfo;
									GetIconInfo(hIcon, &iconinfo);

									LDraw::Bitmap* pBitmap = new LDraw::Bitmap(iconinfo.hbmColor, NULL);

									if (iconinfo.hbmColor)
										DeleteObject(iconinfo.hbmColor);

									if (iconinfo.hbmMask)
										DeleteObject(iconinfo.hbmMask);

									DestroyIcon(hIcon);

									CLXUIImage* pImage = new CLXUIImage(pBitmap);
									DockPanel::put_Dock(pImage, DockPanel::Left);
									pContent->AddRChild(pImage);
								}
								{
									TextString* pLabel = new TextString(A2W(pItem->m_wfd.cFileName));
									DockPanel::put_Dock(pLabel, DockPanel::Fill);
									pContent->AddRChild(pLabel);
								}

								pItem->m_treeItem->AppendColumnCell(pContent);
							}

							{
								OLECHAR buf[32];
								if (pItem->m_wfd.nFileSizeLow < 1024)
								{
									swprintf(buf, L"%d byte", pItem->m_wfd.nFileSizeLow);
								}
								else
								{
									swprintf(buf, L"%.1f kB", pItem->m_wfd.nFileSizeLow / 1024.0);
								}

								pItem->m_treeItem->AppendColumnCell(new TextString(buf));
							}
						}

						pItem->m_treeItem->SetExpandButton((pItem->m_type == 1)? 1: 0);
						pItem->m_treeItem->m_itemData = pItem;
						parentItem->AppendItem(pItem->m_treeItem);
						//m_treeCtl->InsertItem((DWORD)pItem, parentItem, NULL, NULL/*name*/, pItem->m_iIcon, (pItem->m_type == 1)? 1: 0, &pItem->m_treeItem);
					}
					else
						m_treeCtl->SetItemInfo(pItem->m_treeItem, (DWORD)pItem, pItem->m_iIcon, (pItem->m_type == 1)? 1: 0);
				}
			}
		}
		while (InternetFindNextFile(hFindFile, &wfd));

		InternetCloseHandle(hFindFile);
	}

	if (bCheckExisting)
	{
		ATLASSERT(0);
#if 0
	// Remove from the tree control the files which no longer exist
		TreeItem* child;
		m_treeCtl->GetFirstChildItem(parentItem, &child);
		while (child)
		{
			CComPtr<IUITreeItem> nextSibling;
			m_treeCtl->GetNextSiblingItem(child, &nextSibling);

			CSiteItem* pItem;
			m_treeCtl->GetItemInfo(child, (DWORD*)&pItem, NULL, NULL);
			if (pItem->m_bFoundOnDisk == false)
			{
				m_treeCtl->DeleteItem(child);
			}

			child = nextSibling;
		}
#endif
	}

	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		;//WinError(m_hWnd, GetLastError());
	}
}

void CFTPBrowser::SetDirectory()
{
	USES_CONVERSION;

	m_treeCtl->ResetContent(NULL);
//	m_axtreeCtl.EnableWindow(TRUE);

//	m_axbuttonsCtl.EnableWindow(TRUE);

//	m_axeditCtl.EnableWindow(TRUE);
#if 0
	m_editCtl->SetText(m_Directory);
#endif

	m_pRootDir = new CSiteDir;
	strcpy(m_pRootDir->m_wfd.cFileName, W2A(m_Directory.c_str()));
	m_pRootDir->m_treeItem = m_treeCtl->SetRootItem((DWORD)m_pRootDir);

	PopulateFolder(m_pRootDir->m_treeItem, m_pRootDir, false);
}

bool CFTPBrowser::Connect()
{
	USES_CONVERSION;

	if (!m_pRootDir)
	{
		m_hInternet = InternetOpen(
			"WebEditor",//LPCTSTR lpszAgent,
			INTERNET_OPEN_TYPE_DIRECT,//DWORD dwAccessType,
			NULL,//LPCTSTR lpszProxyName,
			NULL,//LPCTSTR lpszProxyBypass,
			0//INTERNET_FLAG_ASYNC,//DWORD dwFlags
			);
		
		if (m_hInternet)
		{
			//INTERNET_PORT nPort;
			DWORD dwServiceType;
			//CString strServer;
			CString strObject;

			CString m_Url = W2A(m_ServerName.c_str());
			ATLASSERT(0);
#if 0
			AfxParseURL(m_Url, dwServiceType, m_strServer.c_str(), strObject, m_nPort);
#endif

			m_hInternetFtp = InternetConnect(
				m_hInternet,
				W2A(m_strServer.c_str()),//m_ServerName,
				m_nPort,//21,//INTERNET_PORT nServerPort,
				W2A(m_UserName.c_str()),//LPCTSTR lpszUsername,
				W2A(m_Password.c_str()),//LPCTSTR lpszPassword,
				dwServiceType,//INTERNET_SERVICE_FTP,//DWORD dwService,
				0,//INTERNET_FLAG_PASSIVE,//DWORD dwFlags,
				(DWORD)this// dwContext
				);

			if (m_hInternetFtp)
			{
				SetDirectory();

				return true;
			}

			InternetCloseHandle(m_hInternet);
			m_hInternet = NULL;
		}
	}

	return false;
}

void CFTPBrowser::Disconnect()
{
	/*
	m_editCtl->SetText(L"");
	m_axeditCtl.EnableWindow(FALSE);

	m_axbuttonsCtl.EnableWindow(FALSE);
	*/

	m_treeCtl->ResetContent(NULL);
//	m_axtreeCtl.EnableWindow(FALSE);

	m_pRootDir = NULL;

	if (m_hInternetFtp)
	{
		InternetCloseHandle(m_hInternetFtp);
		m_hInternetFtp = NULL;
	}

	if (m_hInternet)
	{
		InternetCloseHandle(m_hInternet);
		m_hInternet = NULL;
	}
}

CFTPBrowser::CSiteItem* CFTPBrowser::FindFileByFileName(TreeItem* parentItem, LPCTSTR filename, int type)
{
	ATLASSERT(0);
#if 0
	CSiteItem* pItem;
	m_treeCtl->GetItemInfo(parentItem, (DWORD*)&pItem, NULL, NULL);

	if ((pItem->m_type == type) && (_tcscmp(pItem->m_wfd.cFileName, filename) == 0))
		return pItem;

	TreeItem* child;
	m_treeCtl->GetFirstChildItem(parentItem, &child);
	while (child)
	{
		CSiteItem* pFItem = FindFileByFileName(child, filename, type);
		if (pFItem) return pFItem;

		CComPtr<IUITreeItem> next;
		m_treeCtl->GetNextSiblingItem(child, &next);
		child = next;
	}
#endif
	return NULL;
}

__int64 GetTotalSizeOfFiles(LPTSTR filepath)
{
	__int64 nSize = 0;

	DWORD attributes = GetFileAttributes(filepath);
	char* filepart = PathFindFileName(filepath);

	if (attributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		HANDLE hFindFile;
		WIN32_FIND_DATA	wfd;

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

						nSize += GetTotalSizeOfFiles(pathName);
					}
					else
					{
						nSize += wfd.nFileSizeLow;
					}
				}
			}
			while (FindNextFile(hFindFile, &wfd));

			FindClose(hFindFile);
		}
	}
	else
	{
		nSize += GetFileSize(filepath, NULL);
	}

	return nSize;
}

//#include "ProgressDlg.h"

/*
parentpath - FTP parent directory to copy to
filepath - Local path tp copy from
*/
long CFTPBrowser::CopyMoveFile(CSiteDir* pParentDir, LPCTSTR parentpath , LPCTSTR filepath, bool bSilent, CProgressDlg* dlg)
{
	ATLASSERT(0);
	return 0;
#if 0
	long nFilesCopied = 0;

	DWORD attributes = GetFileAttributes(filepath);
	TCHAR* filepart = PathFindFileName(filepath);

	TCHAR destpath[1024];
	wsprintf(destpath, "%s/%s", parentpath, filepart);

	if (attributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		if (pParentDir)
			pParentDir = (CSiteDir*)FindFileByFileName(pParentDir->m_treeItem, filepath, 1);

		if (pParentDir)
		{
			pParentDir->m_bPopulated = false;
		}

		FtpCreateDirectory(m_hInternetFtp, destpath);

		if (TRUE)
		{
			HANDLE hFindFile;
			WIN32_FIND_DATA	wfd;

			TCHAR	search[MAX_PATH];
			wsprintf(search, "%s\\*.*", filepath);

			if ((hFindFile = FindFirstFile(search, &wfd)) != INVALID_HANDLE_VALUE)
			{
				do
				{
					if (wfd.cFileName[0] != '.')
					{
						TCHAR pathName[_MAX_PATH];
						_makepath(pathName, NULL, filepath, wfd.cFileName, NULL);

						nFilesCopied += CopyMoveFile(pParentDir, destpath, pathName, bSilent, dlg);

						/*
						if (dlg)
						{
							if (dlg->m_bCancel) break;
						}
						*/
					}
				}
				while (FindNextFile(hFindFile, &wfd));

				FindClose(hFindFile);
			}

			if (pParentDir)
			{
				PopulateFolder(pParentDir->m_treeItem, pParentDir, true);
			}
		}
		else
		{
			if (!bSilent)
			{
				DWORD dw;
				TCHAR msg[1024];
				DWORD len = 1024;
				InternetGetLastResponseInfo(&dw, msg, &len);

				CUString str;
				str.Format("Couldn't create folder \"%s\"\n\n", filepath, msg);
				MessageBox(str, "FTP", MB_OK);
			}
		}
	}
	else
	{
		BOOL success = FtpPutFile(
			m_hInternetFtp,
			filepath, destpath,
			INTERNET_FLAG_TRANSFER_BINARY, 0L/*dwContext*/);
		
		if (success)
		{
			nFilesCopied++;
				/*
			dlg->m_pos += dataSize/10;
			dlg->Invalidate();

			GetFileSize(filepath, NULL);
			*/
		}
		else
		{
			if (!bSilent)
			{
				DWORD dw;
				TCHAR msg[1024];
				DWORD len = 1024;
				InternetGetLastResponseInfo(&dw, msg, &len);

				CUString str;
				str.Format("Couldn't upload \"%s\"\n\n%s", filepath, msg);
				MessageBox(str, "FTP", MB_OK);
			}
		}

		/*

		if (dlg)
		{
			dlg->m_pos += dataSize/10;
			dlg->Invalidate();

			MSG msg;
			while (PeekMessage(&msg, dlg->m_hWnd, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		*/
	}

	return nFilesCopied;
#endif
}

/*
STDMETHODIMP CWebSite::CopyMoveFile(DWORD folder_id, BSTR filepath, VARIANT_BOOL bSilent, long *nFilesCopied)
{
	SAFEARRAYBOUND rgsabound[1];
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = 1;
   SAFEARRAY* sa = SafeArrayCreate(VT_BSTR, 1, rgsabound);
	if (sa)
	{
		long ix[1];
		ix[0] = 0;
		SafeArrayPutElement(sa, ix, filepath);

		CopyMoveFiles(folder_id, sa, bSilent, nFilesCopied);

		SafeArrayDestroy(sa);
	}

	return S_OK;
}
*/

long CFTPBrowser::CopyMoveFiles(CSiteDir* pParent, SAFEARRAY* sa, bool bSilent)
{
	ATLASSERT(0);
	return 0;
#if 0
//	CProgressDlg dlg;
//	dlg.Create(GetMainHwnd(), NULL);

	int i;

	__int64 nSize = 0;
	for (i = 0; i < sa->rgsabound[0].cElements; i++)
	{
		long ix[1];
		ix[0] = i;

		BSTR bstr;
		SafeArrayGetElement(sa, ix, (void**)&bstr);

		nSize += GetTotalSizeOfFiles(_bstr_t(bstr));
	}

//	dlg.m_min = 0;
//	dlg.m_max = nSize/10;
//	dlg.m_pos = 0;

	pParent->m_bPopulated = false;

	for (i = 0; i < sa->rgsabound[0].cElements; i++)
	{
		long ix[1];
		ix[0] = i;

		BSTR bstr;
		SafeArrayGetElement(sa, ix, (void**)&bstr);

		CopyMoveFile(pParent, pParent->GetFullPathName(), _bstr_t(bstr), bSilent, NULL/*&dlg*/);
	}

	PopulateFolder(pParent->m_treeItem, pParent, true);

//	dlg.DestroyWindow();

	return S_OK;
#endif
}

STDMETHODIMP CFTPBrowser::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	return S_OK;
}

STDMETHODIMP CFTPBrowser::DragOver(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	ATLASSERT(0);
#if 0
	if (m_prevDropItem)
	{
		DWORD state;
		m_treeCtl->GetItemState(m_prevDropItem, &state);
		m_treeCtl->SetItemState(m_prevDropItem, state &~ 2);
		m_prevDropItem = NULL;
	}

	*pdwEffect = DROPEFFECT_COPY;

	POINT point;
	point.x = pt.x;
	point.y = pt.y;
	::ScreenToClient(m_axtreeCtl.m_hWnd, &point);

	CComPtr<IUITreeItem> item;
	DWORD flags;
	m_treeCtl->HitTest(point, &flags, &item);
	if (item)
	{
		DWORD state;
		m_treeCtl->GetItemState(item, &state);
		m_treeCtl->SetItemState(item, state | 2);
		m_prevDropItem = item;
	}
#endif
	return S_OK;
}

STDMETHODIMP CFTPBrowser::DragLeave()
{
	if (m_prevDropItem)
	{
		DWORD state;
		m_treeCtl->GetItemState(m_prevDropItem, &state);
		m_treeCtl->SetItemState(m_prevDropItem, state &~ 2);
		m_prevDropItem = NULL;
	}

	return S_OK;
}

STDMETHODIMP CFTPBrowser::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	ATLASSERT(0);
#if 0
	CSiteDir* pParent;

	if (m_prevDropItem)
	{
		DWORD state;
		m_treeCtl->GetItemState(m_prevDropItem, &state);
		m_treeCtl->SetItemState(m_prevDropItem, state &~ 2);

		CSiteItem* pItem;
		m_treeCtl->GetItemInfo(m_prevDropItem, (DWORD*)&pItem, NULL, NULL);

		if (pItem->m_type == 1)	// Dropped on directory
			pParent = (CSiteDir*)pItem;
		else
			pParent = pItem->m_parent;

		m_prevDropItem = NULL;
	}
	else
	{
		pParent = m_pRootDir;
	}

	COleDataObject dataObject;
	dataObject.Attach(pDataObject);

	HGLOBAL hData;

	if (hData = dataObject.GetGlobalData(CF_HDROP))
	{
		DROPFILES* dp = (DROPFILES*)GlobalLock(hData);
		if (dp)
		{
			CArray<_bstr_t,_bstr_t&> filenames;

			if (dp->fWide)
			{
				WCHAR* p = (WCHAR*)(dp+1);
				while (*p)
				{
					_bstr_t file = p;
					p += file.length() + 1;
					filenames.Add(file);
				}
			}
			else
			{
				char* p = (char*)(dp+1);
				while (*p)
				{
					_bstr_t file = p;
					p += file.length() + 1;
					filenames.Add(file);
				}
			}

			SAFEARRAYBOUND rgsabound[1];
			rgsabound[0].lLbound = 0;
			rgsabound[0].cElements = filenames.GetSize();
    		SAFEARRAY* sa = SafeArrayCreate(VT_BSTR, 1, rgsabound);
			if (sa)
			{
				for (int i = 0; i < filenames.GetSize(); i++)
				{
					_bstr_t& filepath = filenames[i];

					long ix[1];
					ix[0] = i;
					SafeArrayPutElement(sa, ix, (BSTR)filepath/*.copy()*/);
				}

				long nFilesCopied = CopyMoveFiles(pParent, sa, VARIANT_FALSE);

				SafeArrayDestroy(sa);
			}

			GlobalUnlock(hData);

			*pdwEffect = DROPEFFECT_COPY;
		}
	}
#endif
	return S_OK;
}
