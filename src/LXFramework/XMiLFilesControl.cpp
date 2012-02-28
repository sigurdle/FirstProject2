// XMiLFilesControl.cpp : Implementation of CXMiLFilesControl

#include "stdafx.h"
#include "LXFramework.h"
#include "LXFramework2.h"
#include "XMiLFilesControl.h"

#if 0

void com_error_Message(_com_error &e);
//__int64 GetTotalSizeOfFiles(LPTSTR filepath);

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


_bstr_t CXMiLFilesControl::CSiteItem::GetFullPathName()
{
	CSiteDir* pParentDir = m_parent;

	if (pParentDir)
	{
		WCHAR pathName[1024];
		swprintf(pathName, L"%s/%S", (BSTR)pParentDir->GetFullPathName(), m_wfd.cFileName);

		return pathName;
	}
	else
	{
		return m_wfd.cFileName;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CXMiLFilesControl

#define PANE_NAME		0
#define PANE_STATUS	1
#define PANE_SIZE		2
#define PANE_DATE		3

static int m_titleHeight = 16;

CXMiLFilesControl::CSiteItem * CXMiLFilesControl::FromElement(CSiteDir* pParentDir, ILDOMElement* recordset)
{
	CSiteItem* pItem;

	BSTR b;

	recordset->getAttribute(L"type", &b);
	BYTE type = (long)_variant_t(_bstr_t(b, false));

	recordset->getAttribute(L"filename", &b);
	_bstr_t filename = _bstr_t(b, false);

	if (type == 1)	// Directory
	{
		CSiteDir* pDir = new CSiteDir;
		pItem = pDir;
	}
	else if (type == 2)	// File
	{
		CSiteFile* pFile = new CSiteFile;
		pItem = pFile;
	}
	else
		ATLASSERT(0);

	if (pItem)
	{
		pItem->m_parent = pParentDir;
		//pItem->m_pWebSite = m_pWebSite;

		strcpy(pItem->m_wfd.cFileName, filename);

	//	recordset->getAttribute(L"file_id", &b);
	//	pItem->m_dbid = (long)_variant_t(_bstr_t(b, false));

		recordset->getAttribute(L"file_size", &b);
		pItem->m_wfd.nFileSizeLow = (long)_variant_t(_bstr_t(b, false));

		// lastWriteDate
		recordset->getAttribute(L"file_date", &b);
		double lastWriteTime = _variant_t(_bstr_t(b, false));
		SYSTEMTIME systime;
		VariantTimeToSystemTime(lastWriteTime, &systime);
		SystemTimeToFileTime(&systime, &pItem->m_wfd.ftLastWriteTime);

		SHFILEINFO sfi;
		::SHGetFileInfo(
			pItem->m_wfd.cFileName,
			(pItem->m_type == 1)? FILE_ATTRIBUTE_DIRECTORY: FILE_ATTRIBUTE_NORMAL,
			&sfi,
			sizeof(SHFILEINFO),
			SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES);
		pItem->m_iIcon = sfi.iIcon;

		if (pItem->m_type == 1)
		{
			CSiteDir* pDir = (CSiteDir*)pItem;
			pItem->m_cChildren = _variant_t(_bstr_t(b, false));
		}
	}

	return pItem;
}

void CXMiLFilesControl::PopulateFolder(DWORD parentItem, CSiteDir* pParentDir)
{
//	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	pParentDir->m_bPopulated = VARIANT_TRUE;

//	ADODB::_ConnectionPtr conn = GetDBConnection();

	try
	{
		_bstr_t bstrxml = m_filesystem->GetFolderDirectoryList(pParentDir->GetFullPathName());

		CComPtr<ILDOMDocument> xmldocument;
		xmldocument.CoCreateInstance(CLSID_LDOMDocument);
		VARIANT_BOOL bsuccess;
		xmldocument->loadXML(bstrxml, &bsuccess);

		CComPtr<ILDOMElement> documentElement;
		xmldocument->get_documentElement(&documentElement);

		CComPtr<ILDOMNode> node;
		documentElement->get_firstChild(&node);
		while (node)
		{
			CComQIPtr<ILDOMElement> element = node;
			if (element)
			{
				CSiteItem* pItem = FromElement(pParentDir, element);

				if (pItem)
				{
					m_treeCtl->InsertItem((DWORD)pItem, parentItem, NULL, NULL, pItem->m_iIcon, pItem->m_cChildren, &pItem->m_treeItem);
				}
			}

			CComPtr<ILDOMNode> nextSibling;
			node->get_nextSibling(&nextSibling);
			node = nextSibling;
		}
	}
	catch (_com_error &e)
	{
		com_error_Message(e);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CXMiLFilesControl

CXMiLFilesControl::CXMiLFilesControl()
{
	m_bWindowOnly = TRUE;

//	m_rootFolderId = 0L;
	m_prevDropItem = NULL;
	m_pRootDir = NULL;
}

int CXMiLFilesControl::FinalConstruct()
{
	HRESULT hr;

	hr = m_treeCtl.CoCreateInstance(CLSID_UITreeControl);
	if (FAILED(hr)) return hr;

	IDispEventImpl<4, CXMiLFilesControl, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_treeCtl);

	m_treeCtl->SetSite(this);

	m_treeCtl->InsertColumn(PANE_NAME, L"Name", 120, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_STATUS, L"Status", 80, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_SIZE, L"Size", 60, FALSE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_DATE, L"Date", 80, FALSE, TRUE, NULL);

	return S_OK;
}

void CXMiLFilesControl::FinalRelease()
{
	/*
	if (m_pDocument)
		IDispEventImpl<3, CXMiLFilesControl, &DIID__IWebSiteEvents, &LIBID_LXFrameworkLib, 1, 0>::DispEventUnadvise(m_pDocument);
		*/

	IDispEventImpl<4, CXMiLFilesControl, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_treeCtl);
}

HRESULT CXMiLFilesControl::OnDraw(ATL_DRAWINFO& di)
{
	HDC hDC = di.hdcDraw;

	HFONT hOldFont = (HFONT)SelectObject(hDC, GetStockObject(DEFAULT_GUI_FONT));

	TextOut(hDC, 0, 0, m_rootDisplayPath, m_rootDisplayPath.length());

	SelectObject(hDC, hOldFont);

	return S_OK;
}

long CXMiLFilesControl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	ATLASSERT(0);
#if 0
	if (m_rootFolderId != 0)
	{
		DWORD parent_id = pWebSite->m_webSite->GetParentFolderId(m_rootFolderId);

		SetRootFolderId(parent_id);
		InvalidateRect(NULL, TRUE);
	}
#endif

	return 0;
}

/*
long CXMiLFilesControl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnButtonDown(wParam, point, 0, FALSE);

	return HANDLE_BASE<IUIView>(m_puiwnd, uMsg, wParam, lParam);
}

long CXMiLFilesControl::OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnButtonDown(wParam, point, 1, FALSE);

	return HANDLE_BASE<IUIView>(m_puiwnd, uMsg, wParam, lParam);
}
*/

HGLOBAL CXMiLFilesControl::BuildSelectedFilesClipboard()
{
#if 0
	DWORD active;
	m_treeCtl->GetSelectedItem(&active);

	if (active)
	{
		HGLOBAL hData = NULL;

//		UPOSITION pos;

	// Calculate needed buffer size
		int len = 0;

		DWORD parentitem;
		m_treeCtl->GetParentItem(active, &parentitem);

		DWORD child;

		m_treeCtl->GetFirstChildItem(parentitem, &child);
		while (child)
		{
			DWORD state;
			m_treeCtl->GetItemState(child, &state);

			if (state & 1)
			{
				CSiteItem* pFile;
				m_treeCtl->GetItemInfo(child, (DWORD*)&pFile, NULL);

				len += strlen(pFile->GetFullPathName())+1;
			}

			m_treeCtl->GetNextSiblingItem(child, &child);
		}

		len++;

	// Now put it in the buffer
		hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, sizeof(DROPFILES) + len);
		char* p = (char*)GlobalLock(hData);

		((DROPFILES*)p)->pFiles = sizeof(DROPFILES);
		((DROPFILES*)p)->fWide = FALSE;
		p += sizeof(DROPFILES);

		m_treeCtl->GetFirstChildItem(parentitem, &child);
		while (child)
		{
			DWORD state;
			m_treeCtl->GetItemState(child, &state);

			if (state & 1)
			{
				CSiteItem* pFile;
				m_treeCtl->GetItemInfo(child, (DWORD*)&pFile, NULL);

				CUString pathName = pFile->GetFullPathName();

				strcpy(p, pathName);
				p += strlen(pathName)+1;
			}

			m_treeCtl->GetNextSiblingItem(child, &child);
		}

		*p = 0;	// Null terminated

		GlobalUnlock(hData);

		return hData;
	}
#endif
	return NULL;
}

HRESULT __stdcall CXMiLFilesControl::OnItemClick(DWORD item)
{
#if 0
	HGLOBAL hData = BuildSelectedFilesClipboard();
	if (hData)
	{
		CMyDropSource*  dropSource = new CMyDropSource;
		CMyDataObject* dataObject = new CMyDataObject;

		STGMEDIUM	stg = {0};
		stg.tymed = TYMED_HGLOBAL;
		stg.hGlobal = hData;
		stg.pUnkForRelease = NULL;
		
		FORMATETC	etc = {0};
		etc.cfFormat = CF_HDROP;//CF_UNICODETEXT;//49285;//RegisterClipboardFormat(CFSTR_SHELLURL);//CF_TEXT;
		etc.tymed = TYMED_HGLOBAL;
		etc.ptd = NULL;
		etc.dwAspect = DVASPECT_CONTENT;
		etc.lindex = -1;

		dataObject->SetData(&etc, &stg, TRUE);

		DWORD dropEffect = 0;
		HRESULT hr = ::DoDragDrop(dataObject, dropSource, DROPEFFECT_LINK | DROPEFFECT_COPY | DROPEFFECT_MOVE, &dropEffect);

		if (hr == DRAGDROP_S_DROP)
		{
			if (dropEffect/* & DROPEFFECT_MOVE*/)
			{
			}
		}

		GlobalFree(hData);

	//	delete dataObject;
	//	delete dropSource;

#if 0
		COleDataSource source;
		source.CacheGlobalData(CF_HDROP, hData, NULL);

		if (source.DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE, NULL, NULL) == DROPEFFECT_COPY)
		{
		}

		source.Empty();
#endif
					
		GlobalFree(hData);
	}
#endif

	return S_OK;
}

HRESULT __stdcall CXMiLFilesControl::OnItemDblClick(DWORD item)
{
//	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	DWORD active;
	m_treeCtl->GetSelectedItem(&active);

	if (active)
	{
		CSiteItem* pItem;
		m_treeCtl->GetItemInfo(active, (DWORD*)&pItem, NULL, NULL);
		if (pItem->m_type == 1)	// Double-clicking on folder sets it as new root-folder
		{
			CSiteDir* pDir = (CSiteDir*)pItem;
			SetRootFolderPath(pDir->GetFullPathName());
		}
		else
		{
			DWORD parentitem;
			m_treeCtl->GetParentItem(active, &parentitem);

			DWORD child;

			m_treeCtl->GetFirstChildItem(parentitem, &child);
			while (child)
			{
				DWORD state;
				m_treeCtl->GetItemState(child, &state);

				if (state & 1)
				{
					CSiteItem* pFile;
					m_treeCtl->GetItemInfo(child, (DWORD*)&pFile, NULL, NULL);

					ATLASSERT(0);
#if 0
					VARIANT_BOOL success;
					pWebSite->OpenDocument(pFile->m_dbid, &success);
#endif
				}

				m_treeCtl->GetNextSiblingItem(child, &child);
			}
		}
	}

	return S_OK;
}

HRESULT __stdcall CXMiLFilesControl::OnContextMenu(long x, long y)
{
#if 0
	CComQIPtr<IUIManager> uiManager = gApp->m_frame;//uiManager;

	CComQIPtr<IMenuItem> menu;
	uiManager->FindMenu(IDR_SITEFILES, &menu);
	if (menu)
	{
		POINT scrpoint;
		scrpoint.x = x;
		scrpoint.y = y;

		long selectedID;
		menu->PopupMenu(this, scrpoint, 0, &selectedID);
	}
#endif
	return S_OK;
}

HRESULT __stdcall CXMiLFilesControl::OnItemExpanding(long item, VARIANT_BOOL bExpanding, BOOL* bCancel)
{
	CSiteDir* pDir;
	m_treeCtl->GetItemInfo(item, (DWORD*)&pDir, NULL, NULL);

	if (pDir->m_type == 1)
	{
		if (bExpanding)
		{
			if (!pDir->m_bPopulated)
				PopulateFolder(item, pDir);
		}
	}

	return S_OK;
}

HRESULT __stdcall CXMiLFilesControl::OnEndLabelEdit(long item, BSTR text)
{
//	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	CSiteItem* pItem;
	m_treeCtl->GetItemInfo(item, (DWORD*)&pItem, NULL, NULL);

	if (wcscmp(_bstr_t(pItem->m_wfd.cFileName), text) != 0)
	{
		try
		{
#if 0
			pWebSite->m_webSite->RenameFile(pItem->m_dbid, text);
#endif
		}
		catch(_com_error e)
		{
			com_error_Message(e);
		}
	}

	return S_OK;
}

#if 0
CSiteItem* CXMiLFilesControl::FindFileById(DWORD parentItem, long file_id)
{
	CSiteItem* pItem;
	m_treeCtl->GetItemInfo(parentItem, (DWORD*)&pItem, NULL, NULL);

	if (pItem->m_dbid == file_id)
		return pItem;

	DWORD child;

	m_treeCtl->GetFirstChildItem(parentItem, &child);
	while (child)
	{
		CSiteItem* pFItem = FindFileById(child, file_id);
		if (pFItem) return pFItem;

		m_treeCtl->GetNextSiblingItem(child, &child);
	}

	return NULL;
}
#endif

HRESULT __stdcall CXMiLFilesControl::OnFileUpdate(long parentFolderId, long fileId, long action)
{
//	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	DWORD rootItem;
	m_treeCtl->GetRootItem(&rootItem);

#if 0
	if (action == 1)	// New File
	{
		CSiteDir* pParentDir = (CSiteDir*)FindFileById(rootItem, parentFolderId);
		if (pParentDir && pParentDir->m_bPopulated)
		{
			WCHAR sql[256];
			swprintf(sql, L"SELECT id,filename,type,file_size,file_date FROM files WHERE id = %d", fileId);
			_variant_t va;
			ADODB::_ConnectionPtr conn = GetDBConnection();
			ADODB::_RecordsetPtr recordset = conn->Execute(sql, &va, ADODB::adCmdText);

			CSiteItem* pNewItem = FromElement(pParentDir, recordset);
			if (pNewItem)
			{
				m_treeCtl->InsertItem((DWORD)pNewItem, pParentDir->m_treeItem, NULL, NULL, pNewItem->m_iIcon, pNewItem->m_cChildren, &pNewItem->m_treeItem);
			}
		}
	}
	else if (action == 2)	// Delete File
	{
		CSiteItem* pItem = FindFileById(rootItem, fileId);
		if (pItem)
		{
			m_treeCtl->DeleteItem(pItem->m_treeItem);
			delete pItem;	// TODO, this doesn't delete children
		}
	}
	else if (action == 3)	// Update file
	{
		CSiteItem* pItem = FindFileById(rootItem, fileId);
		if (pItem)
		{
			WCHAR sql[256];
			swprintf(sql, L"SELECT id,filename,type,file_size,file_date FROM files WHERE id = %d", fileId);
			_variant_t va;
			ADODB::_ConnectionPtr conn = GetDBConnection();
			ADODB::_RecordsetPtr recordset = conn->Execute(sql, &va, ADODB::adCmdText);

			CSiteItem* pNewItem = FromRecordSet((CSiteDir*)pItem->m_parent, recordset);
			if (pNewItem)
			{
				pNewItem->m_treeItem = pItem->m_treeItem;
				m_treeCtl->SetItemInfo(pItem->m_treeItem, (DWORD)pNewItem, pNewItem->m_iIcon, pNewItem->m_cChildren);
				delete pItem;
			}
		}
	}
#endif

	return S_OK;
}

/*
long CXMiLFilesControl::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnButtonDown(wParam, point, 0, TRUE);

	return HANDLE_BASE<IUIView>(m_puiwnd, uMsg, wParam, lParam);
}

void CXMiLFilesControl::OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk)
{
}
*/

STDMETHODIMP CXMiLFilesControl::GetItemText(ULONG itemdata, LONG column, BSTR * pVal)
{
	*pVal = NULL;

	CSiteItem* pNode = (CSiteItem*)itemdata;

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

	return S_OK;
}

void CXMiLFilesControl::InitTree()
{
//	CWebSite* pWebSite = (CWebSite*)m_document.p;

	m_treeCtl->ResetContent(NULL);

#if 0
	m_rootDisplayPath = pWebSite->m_webSite->GetFolderDisplayPath(m_rootFolderId);
#endif
//	_bstr_t rootPath = pWebSite->m_webSite->rootPath;

	m_pRootDir = new CSiteDir;
	strcpy(m_pRootDir->m_wfd.cFileName, m_rootFolderPath);
//	pRoot->m_bPopulated = VARIANT_TRUE;
	m_treeCtl->SetRootItem((DWORD)m_pRootDir, &m_pRootDir->m_treeItem);

	PopulateFolder(m_pRootDir->m_treeItem, m_pRootDir);
}

long CXMiLFilesControl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SHFILEINFO	ssfi;	//get a handle to the system small icon list 

	m_hFileIcons = (HIMAGELIST)::SHGetFileInfo(
		(LPCTSTR)_T("C:\\"),
		0,
		&ssfi, sizeof(SHFILEINFO),
		SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

	IUnknown* p;

	CRect rc(0,0,0,0);
	m_axtreeCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axtreeCtl.AttachControl(m_treeCtl, &p);

	m_treeCtl->put_hImageList((DWORD)m_hFileIcons);

//	CWebSite* pWebSite = (CWebSite*)m_document.p;

	InitTree();

#if 0
	HRESULT hr = IDispEventImpl<5, CXMiLFilesControl, &DIID__IWSSrvEvents, &LIBID_WSSRVMODLib, 1, 0>::DispEventAdvise(pWebSite->m_webSite);
	ATLASSERT(SUCCEEDED(hr));
#endif

	::RegisterDragDrop(m_hWnd, (IDropTarget*)this);

	return 0;
}

long CXMiLFilesControl::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	RevokeDragDrop(m_hWnd);

	return 0;
}

long CXMiLFilesControl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

void CXMiLFilesControl::OnSize()
{
	CRect	client;
	GetClientRect(&client);

	int top = m_titleHeight;

	int cx = client.Width();
	int cy = client.Height();

	m_axtreeCtl.MoveWindow(0, top, cx, cy-top, TRUE);
}

#if 0
STDMETHODIMP CXMiLFilesControl::get_webSiteDocument(IWebSite **pVal)
{
	*pVal = m_document;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}
#endif

/*
HRESULT __stdcall CXMiLFilesControl::OnFileTreeChanged()
{
	HWND hwnd;
	get_hwnd(&hwnd);

	if (hwnd)
	{
		OnSize();
		InvalidateRect(NULL, TRUE);
	}

	return S_OK;
}
*/

#if 0
STDMETHODIMP CXMiLFilesControl::put_webSiteDocument(IWebSite *newVal)
{
	/*
	if (m_document)
		IDispEventImpl<3, CXMiLFilesControl, &DIID__IWebSiteEvents, &LIBID_LXFrameworkLib, 1, 0>::DispEventUnadvise(m_pDocument);
*/
	m_document = newVal;
/*
	if (m_document)
		IDispEventImpl<3, CXMiLFilesControl, &DIID__IWebSiteEvents, &LIBID_LXFrameworkLib, 1, 0>::DispEventAdvise(m_pDocument);
*/
	return S_OK;
}
#endif

STDMETHODIMP CXMiLFilesControl::SetRootFolderPath(BSTR folderPath)
{
	m_rootFolderPath = folderPath;

	InitTree();

	if (m_hWnd)
	{
		InvalidateRect(NULL, TRUE);
	}

	return S_OK;
}

STDMETHODIMP CXMiLFilesControl::GetRootFolderPath(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = SysAllocString(m_rootFolderPath);

	return S_OK;
}

STDMETHODIMP CXMiLFilesControl::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	return S_OK;
}

STDMETHODIMP CXMiLFilesControl::DragOver(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
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

	DWORD item;
	DWORD flags;
	m_treeCtl->HitTest(point, &flags, &item);
	if (item)
	{
		DWORD state;
		m_treeCtl->GetItemState(item, &state);
		m_treeCtl->SetItemState(item, state | 2);
		m_prevDropItem = item;
	}

	return S_OK;
}

STDMETHODIMP CXMiLFilesControl::DragLeave()
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

STDMETHODIMP CXMiLFilesControl::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
//	CWebSite* pWebSite = (CWebSite*)m_document.p;

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

	COleDataObjectWrapper dataObject;
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

				long nFilesCopied;
				CopyMoveFiles(pParent->GetFullPathName(), sa, VARIANT_FALSE, &nFilesCopied);

				SafeArrayDestroy(sa);
			}

			GlobalUnlock(hData);

			*pdwEffect = DROPEFFECT_COPY;
		}
	}

	return S_OK;
}

#if 0
BEGIN_CMD_MAP(CXMiLFilesControl)
	CMD_HANDLER(ID_EDIT_CLEAR, OnEditDelete)
	CMD_UPDATE(ID_EDIT_CLEAR, OnEditDeleteUpdate)
/*
	CMD_HANDLER(&ID_FILES_HOMEPAGE, OnFileSetasHomepage)
	CMD_UPDATE(&ID_FILES_HOMEPAGE, OnFileSetasHomepageUpdate)
	CMD_HANDLER(&ID_FILES_NEWFOLDER, OnFileNewFolder)
*/
END_CMD_MAP()

LRESULT CXMiLFilesControl::OnFileNewFolder(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	DWORD parent_id;

	DWORD active;
	m_treeCtl->GetSelectedItem(&active);

	if (active)
	{
		CSiteItem* pItem;
		m_treeCtl->GetItemInfo(active, (DWORD*)&pItem, NULL, NULL);

		if (pItem->m_type == 1)
			parent_id = pItem->m_dbid;
		else
			parent_id = ((CSiteDir*)pItem->m_parent)->m_dbid;
	}
	else
	{
		parent_id = 0;
	}

	DWORD folder_id = pWebSite->m_webSite->CreateFolder(parent_id, L"untitled", L"");
	if (folder_id)
	{
		DWORD rootItem;
		m_treeCtl->GetRootItem(&rootItem);

		CSiteItem* pItem = FindFileById(rootItem, folder_id);
		if (pItem)
		{
			m_treeCtl->EditLabel(pItem->m_treeItem, NULL);
		}
	}

	return 0;
}

LRESULT CXMiLFilesControl::OnEditDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	DWORD active;
	m_treeCtl->GetSelectedItem(&active);

	if (active)
	{
		CSiteItem* pItem;
		m_treeCtl->GetItemInfo(active, (DWORD*)&pItem, NULL, NULL);

		DWORD parentitem;
		m_treeCtl->GetParentItem(active, &parentitem);

		DWORD child;

		m_treeCtl->GetFirstChildItem(parentitem, &child);
		while (child)
		{
			DWORD state;
			m_treeCtl->GetItemState(child, &state);

			DWORD nextSibling;
			m_treeCtl->GetNextSiblingItem(child, &nextSibling);

			if (state & 1)
			{
				CSiteItem* pFile;
				m_treeCtl->GetItemInfo(child, (DWORD*)&pFile, NULL, NULL);

				pWebSite->m_webSite->DeleteFilePermanently(pFile->m_dbid);
			}

			child = nextSibling;
		}
	}

	return 0;
}

void CXMiLFilesControl::OnEditDeleteUpdate(long iid, IUICmdUpdate* pCmdUI)
{
}

LRESULT CXMiLFilesControl::OnFileSetasHomepage(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	DWORD active;
	m_treeCtl->GetSelectedItem(&active);
	if (active)
	{
		CSiteItem* pFile;
		m_treeCtl->GetItemInfo(active, (DWORD*)&pFile, NULL, NULL);
		if (pFile->m_type == 2)
		{
			((CWebSite*)m_document.p)->m_webSite->SetHomepageFileId(pFile->m_dbid);
		}
	}

#if 0
	if (m_pActive && m_pActive->m_type == 2)
	{
		((CWebSite*)m_document.p)->m_pFileHomepage = (CSiteFile*)m_pActive;
	}
#endif

	return 0;
}

void CXMiLFilesControl::OnFileSetasHomepageUpdate(long iid, IUICmdUpdate* pCmdUI)
{
#if 0
	if (m_pActive && m_pActive->m_type == 2)
	{
		pCmdUI->Enable(TRUE);

		if (((CWebSite*)m_document.p)->m_pFileHomepage == m_pActive)
		{
			//pCmdUI->SetCheck(TRUE);
		}
		else
		{
			//pCmdUI->SetCheck(FALSE);
		}
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
#endif
}
#endif

STDMETHODIMP CXMiLFilesControl::SetFileSystemInterface(IUnknown *newVal)
{
	m_filesystem = newVal;
	return S_OK;
}

//#include "ProgressDlg.h"

long CXMiLFilesControl::CopyMoveFile(TCHAR* parentpath/*CSiteDir* pParent*/, _bstr_t filepath, VARIANT_BOOL bSilent, CProgressDlg* dlg)
{
	long nFilesCopied = 0;

	DWORD attributes = GetFileAttributes(filepath);
	TCHAR* filepart = PathFindFileName(filepath);

	TCHAR destpath[1024];
	wsprintf(destpath, "%s/%s", parentpath, filepart);

	if (attributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		long folder_id = m_filesystem->FindOrCreateFolder(_bstr_t(destpath), L"");

		if (folder_id)
		{
			HANDLE hFindFile;
			WIN32_FIND_DATA	wfd;

			char	search[MAX_PATH];
			wsprintf(search, "%S\\*.*", (BSTR)filepath);

			if ((hFindFile = FindFirstFile(search, &wfd)) != INVALID_HANDLE_VALUE)
			{
				do
				{
					if (wfd.cFileName[0] != '.')
					{
						char pathName[_MAX_PATH];
						_makepath(pathName, NULL, filepath, wfd.cFileName, NULL);

						nFilesCopied += CopyMoveFile(destpath /*pParentDir*/, pathName, bSilent, dlg);

#if 0
						if (dlg)
						{
							if (dlg->m_bCancel) break;
						}
#endif
					}
				}
				while (FindNextFile(hFindFile, &wfd));

				FindClose(hFindFile);
			}
		}
		else
		{
			if (!bSilent)
			{
				CUString str;
				str.Format("Couldn't create folder %S", (BSTR)filepath);
				::MessageBox(m_hWnd, str, "LXFramework", MB_OK);
			}
		}
	}
	else
	{
		SAFEARRAY* dataArray = NULL;
		long dataSize = 0;

		FILE* fp = fopen(filepath, "rb");
		if (fp)
		{
			fseek(fp, 0, SEEK_END);
			dataSize = ftell(fp);
			fseek(fp, 0, SEEK_SET);

			dataArray = SafeArrayCreateVector(VT_UI1, 0, dataSize);
			if (dataArray)
			{
				fread((dataArray)->pvData, 1, dataSize, fp);
			}

			fclose(fp);
		}
		else
		{
			if (!bSilent)
			{
				CUString str;
				str.Format("Couldn't open %S", (BSTR)filepath);
				::MessageBox(m_hWnd, str, "LXFramework", MB_OK);
			}
		}

		if (dataArray)
		{
			long file_id;
			try
			{
				m_filesystem->SaveArrayAsFile(_bstr_t(destpath), dataArray, L"", &file_id);

				nFilesCopied++;
			}
			catch (_com_error &e)
			{
				if (!bSilent)
				{
					CUString str;
					str.Format("Failed to copy %s", filepart);
					::MessageBox(m_hWnd, str, "LXFramework", MB_OK);
				}
			}

			SafeArrayDestroy(dataArray);
		}

#if 0
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
#endif
	}

	return nFilesCopied;
}

STDMETHODIMP CXMiLFilesControl::CopyMoveFiles(/*[in]*/ BSTR pathName, /*[in]*/ SAFEARRAY* sa, /*[in]*/ VARIANT_BOOL bSilent, /*[out,retval]*/ long* nFilesCopied)
{
	if (nFilesCopied == NULL) return E_POINTER;

//	CProgressDlg dlg;
//	dlg.Create(NULL, NULL);

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

	for (i = 0; i < sa->rgsabound[0].cElements; i++)
	{
		long ix[1];
		ix[0] = i;

		BSTR bstr;
		SafeArrayGetElement(sa, ix, (void**)&bstr);

		(*nFilesCopied) += CopyMoveFile(_bstr_t(pathName), _bstr_t(bstr), bSilent, NULL/*&dlg*/);
	}

//	dlg.DestroyWindow();

	return S_OK;
}

STDMETHODIMP CXMiLFilesControl::GetTreeControl(IUITreeControl **pVal)
{
	ATLASSERT(pVal);
	if (pVal == NULL) return E_POINTER;
	(*pVal = m_treeCtl)->AddRef();
	return S_OK;
}

STDMETHODIMP CXMiLFilesControl::GetItemFullPathName(DWORD item, BSTR *pVal)
{
	ATLASSERT(item);
	ATLASSERT(pVal);
	if (pVal == NULL) return E_POINTER;
	if (item == NULL) return E_INVALIDARG;

	CSiteItem* pItem = (CSiteItem*)item;
	*pVal = pItem->GetFullPathName().copy();
	return S_OK;
}

#endif