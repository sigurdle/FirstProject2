// SiteFilesView.cpp : Implementation of CSiteFilesView
#include "stdafx.h"
#include "LXWebSite.h"
#include "LXWebSite2.h"
#include "SiteFilesView.h"

#include "WebSite.h"

#include "LXWebSiteApp.h"

//#include "WebEditorApp.h"
//#include "WebEditorFrame.h"

#define PANE_NAME		0
#define PANE_STATUS	1
#define PANE_SIZE		2
#define PANE_DATE		3

CString CSiteFilesView::CSiteItem::GetFullDisplayName()
{
	CString full = m_wfd.cFileName;

	CSiteFilesView::CSiteDir* pItem = m_parent;
	while (pItem)
	{
		full = pItem->m_wfd.cFileName + CString("/") + full;
		pItem = pItem->m_parent;
	}

	return full;
}

CSiteFilesView::CSiteDir::CSiteDir()
{
	m_type = 1;
	m_bPopulated = FALSE;
}

CSiteFilesView::CSiteDir::~CSiteDir()
{
/*
	while (!m_childList.IsEmpty())
	{
		CSiteItem* pItem = (CSiteItem*)m_childList.RemoveHead();
		delete pItem;
	}
*/
}

static int m_titleHeight = 16;

CSiteFilesView::CSiteItem * CSiteFilesView::FromElement(CSiteDir* pParentDir, ILDOMElement* element)
{
	CWebSite* pWebSite = ((CWebSite*)m_document);

	CSiteItem* pItem;

	CComBSTR type;
	element->getAttribute(L"type", &type);

	CComBSTR filename;
	element->getAttribute(L"filename", &filename);

	if (!wcscmp(type, L"1"))	// Directory
	{
		CSiteDir* pDir = new CSiteDir;
		pItem = pDir;
	}
	else if (!wcscmp(type, L"2"))	// File
	{
		CSiteFile* pFile = new CSiteFile;
		pItem = pFile;

		CComBSTR publish;
		element->getAttribute(L"publish", &publish);

		pFile->m_publish = (long)_variant_t(publish);
	}
	else
		ATLASSERT(0);

	if (pItem)
	{
		pItem->m_parent = pParentDir;
		//pItem->m_pWebSite = m_pWebSite;

		strcpy(pItem->m_wfd.cFileName, _bstr_t(filename));
		//pItem->m_dbid = recordset->Fields->Item[_bstr_t("id")]->Value.lVal;

		CComBSTR file_size;
		element->getAttribute(L"file_size", &file_size);
		pItem->m_wfd.nFileSizeLow = (long)_variant_t(file_size);

		CComBSTR file_date;
		element->getAttribute(L"file_date", &file_date);

		// lastWriteDate
		double lastWriteTime;
		VarDateFromStr(file_date, 0, 0, &lastWriteTime);
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

			CComBSTR c;
			element->getAttribute(L"c", &c);

			if (!wcscmp(c, L"0"))
				pItem->m_cChildren = 0;
			else
				pItem->m_cChildren = 1;
		}
	}

	return pItem;
}

void CSiteFilesView::PopulateFolder(IUITreeItem* parentItem, CSiteDir* pParentDir)
{
	CWebSite* pWebSite = ((CWebSite*)m_document);

	pParentDir->m_bPopulated = VARIANT_TRUE;

	CComBSTR dirlist;
	pWebSite->m_webSite->GetFolderList(_bstr_t(pParentDir->GetFullDisplayName()), &dirlist);

	CComPtr<ILDOMDocument> document;
	document.CoCreateInstance(CLSID_LDOMDocument);
	VARIANT_BOOL success;
	document->loadXML(dirlist, &success);

	CComPtr<ILDOMElement> documentElement;
	document->get_documentElement(&documentElement);

	if (documentElement)
	{
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

#if 0
	ADODB::_ConnectionPtr conn;
	pWebSite->m_webSite->GetDBConnection((IDispatch**)&conn);

	WCHAR sql[256];
	swprintf(sql, L"SELECT id,filename,type,file_size,file_date FROM files WHERE parent_id = %d", pParentDir->m_dbid);
	_variant_t va;
	ADODB::_RecordsetPtr recordset = conn->Execute(sql, &va, ADODB::adCmdText);

	while (recordset->EndOfFile == false)
	{
		CSiteItem* pItem = FromRecordSet(pParentDir, recordset);

		if (pItem)
		{
			m_treeCtl->InsertItem((DWORD)pItem, parentItem, NULL, NULL, pItem->m_iIcon, pItem->m_cChildren, &pItem->m_treeItem);
		}

		recordset->MoveNext();
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////
// CSiteFilesView

CSiteFilesView::CSiteFilesView()
{
//	m_rootFolderId = 0L;
	m_prevDropItem = NULL;
}

int CSiteFilesView::FinalConstruct()
{
	HRESULT hr;

	hr = m_treeCtl.CoCreateInstance(CLSID_UITreeControl);
	if (FAILED(hr)) return hr;

	m_treeCtl->SetSite(this);

	m_treeCtl->InsertColumn(PANE_NAME, L"Name", 120, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_STATUS, L"Status", 80, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_SIZE, L"Size", 60, FALSE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_DATE, L"Date", 80, FALSE, TRUE, NULL);

	return S_OK;
}

void CSiteFilesView::FinalRelease()
{
	/*
	if (m_pDocument)
		IDispEventImpl<3, CSiteFilesView, &DIID__IWebSiteEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_pDocument);
		*/
}

long CSiteFilesView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	HWND hwnd = m_hWnd;// get_hwnd(&hwnd);
//	ATLASSERT(IsWindow(hwnd));

	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);

	HFONT hOldFont = (HFONT)SelectObject(hDC, GetStockObject(DEFAULT_GUI_FONT));

	TextOut(hDC, 0, 0, m_rootDisplayPath, m_rootDisplayPath.length());

	SelectObject(hDC, hOldFont);

	EndPaint(&ps);
	return 0;
}

long CSiteFilesView::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CWebSite* pWebSite = ((CWebSite*)m_document);

#if 0
	if (m_rootFolderId != 0)
	{
		DWORD parent_id;
		pWebSite->m_webSite->GetParentFolderId(m_rootFolderId, &parent_id);

		SetRootFolderId(parent_id);
		InvalidateRect(NULL, TRUE);
	}
#endif

	return 0;
}

/*
long CSiteFilesView::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnButtonDown(wParam, point, 0, FALSE);

	return HANDLE_BASE<IUIView>(m_puiwnd, uMsg, wParam, lParam);
}

long CSiteFilesView::OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnButtonDown(wParam, point, 1, FALSE);

	return HANDLE_BASE<IUIView>(m_puiwnd, uMsg, wParam, lParam);
}
*/

HGLOBAL CSiteFilesView::BuildSelectedFilesClipboard()
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

HRESULT __stdcall CSiteFilesView::OnItemClick(IUITreeItem* item)
{
	Fire_SelectionChanged();
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

HRESULT __stdcall CSiteFilesView::OnItemDblClick(IUITreeItem* item)
{
	CWebSite* pWebSite = ((CWebSite*)m_document);

	CComPtr<IUITreeItem> active;
	m_treeCtl->GetSelectedItem(&active);

	if (active)
	{
		CSiteItem* pItem;
		m_treeCtl->GetItemInfo(active, (DWORD*)&pItem, NULL, NULL);
		if (pItem->m_type == 1)	// Double-clicking on folder sets it as new root-folder
		{
			CSiteDir* pDir = (CSiteDir*)pItem;
#if 0
			SetRootFolderId(pDir->m_dbid);
#endif
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

					VARIANT_BOOL success;

					CComPtr<IMoniker> moniker;
					pWebSite->m_webSite->GetFileMoniker(_bstr_t(pFile->GetFullDisplayName()), &moniker);
					if (moniker)
					{
						CComQIPtr<ILXAddin> addin = pWebSite->m_app;
						CComPtr<ILXAddinSite> addinSite;
						addin->GetSite(&addinSite);

						CComPtr<ILXFrameworkFrame> lxframe;
						addinSite->GetFrame(&lxframe);

						lxframe->OpenDocument(moniker);
					}
					else
					{
						MessageBox("Failed to obtain file from website", "LXWebSite", MB_OK);
					}

					//pWebSite->OpenDocument(pFile->m_dbid, &success);
				}

				CComPtr<IUITreeItem> next;
				m_treeCtl->GetNextSiblingItem(child, &next);
				child = next;
			}
		}
	}

	return S_OK;
}

HRESULT __stdcall CSiteFilesView::OnContextMenu(long x, long y)
{
	ATLASSERT(0);
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

HRESULT __stdcall CSiteFilesView::OnItemExpanding(IUITreeItem* item, VARIANT_BOOL bExpanding, BOOL* bCancel)
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

#if 0
void com_error_Message(_com_error &e)
{
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
      
	CUString msg;
	msg.Format("\n\tSource :  %s \n\tdescription : %s \n ",(LPCSTR)bstrSource,(LPCSTR)bstrDescription);

	MessageBox(NULL/*GetMainHwnd()*/, msg, "WebEditor", MB_OK);
}
#endif

HRESULT __stdcall CSiteFilesView::OnEndLabelEdit(IUITreeItem* item, BSTR text)
{
	CWebSite* pWebSite = ((CWebSite*)m_document);

	CSiteItem* pItem;
	m_treeCtl->GetItemInfo(item, (DWORD*)&pItem, NULL, NULL);

	if (wcscmp(_bstr_t(pItem->m_wfd.cFileName), text) != 0)
	{
		try
		{
			ATLASSERT(0);
#if 0
			pWebSite->m_webSite->RenameFile(pItem->m_dbid, text);
#endif
		}
		catch(_com_error e)
		{
			ComErrorMsg(m_hWnd, e);
		}
	}

	return S_OK;
}

#if 0
CSiteItem* CSiteFilesView::FindFileById(IUITreeItem* parentItem, long file_id)
{
	CSiteItem* pItem;
	m_treeCtl->GetItemInfo(parentItem, (DWORD*)&pItem, NULL, NULL);

	if (pItem->m_dbid == file_id)
		return pItem;

	CComPtr<IUITreeItem> child;

	m_treeCtl->GetFirstChildItem(parentItem, &child);
	while (child)
	{
		CSiteItem* pFItem = FindFileById(child, file_id);
		if (pFItem) return pFItem;

		CComPtr<IUITreeItem> next;
		m_treeCtl->GetNextSiblingItem(child, &next);
		child = next;
	}

	return NULL;
}
#endif

CSiteFilesView::CSiteItem* CSiteFilesView::FindFileByName(IUITreeItem* parentItem, TCHAR* path)
{
	CSiteItem* pItem;
	m_treeCtl->GetItemInfo(parentItem, (DWORD*)&pItem, NULL, NULL);

	TCHAR cFileName[260];
	int n = 0;
	while (*path && *path != '/')
		cFileName[n++] = *path++;
	cFileName[n] = 0;

	if (!stricmp(cFileName, pItem->m_wfd.cFileName))
	{
		if (path[0] == 0 || (path[0] == '/' && path[1] == 0))
		{
			return pItem;
		}
		else
		{
			ATLASSERT(*path == '/');
			path++;

			CComPtr<IUITreeItem> child;

			m_treeCtl->GetFirstChildItem(parentItem, &child);
			while (child)
			{
				CSiteItem* pFItem = FindFileByName(child, path);
				if (pFItem) return pFItem;

				CComPtr<IUITreeItem> next;
				m_treeCtl->GetNextSiblingItem(child, &next);
				child = next;
			}
		}
	}

	return NULL;
}

void __stdcall CSiteFilesView::OnFileChangeEvent(long action, BSTR pathName)
{
	CWebSite* pWebSite = ((CWebSite*)m_document);

	CComPtr<IUITreeItem> rootItem;
	m_treeCtl->GetRootItem(&rootItem);

	if (action == 1)	// New File
	{
		_bstr_t fullpath = pathName;
		TCHAR drive[_MAX_DRIVE];
		TCHAR dir[_MAX_DIR];
		_splitpath(fullpath, drive, dir, NULL, NULL);

		TCHAR pathpart[_MAX_PATH];
		_makepath(pathpart, drive, dir, NULL, NULL);

		CSiteDir* pParentDir = (CSiteDir*)FindFileByName(rootItem, pathpart);
		if (pParentDir && pParentDir->m_bPopulated)
		{
			CComBSTR xml;
			pWebSite->m_webSite->GetItemAttributes(pathName, &xml);

			CComPtr<ILDOMDocument> document;
			document.CoCreateInstance(CLSID_LDOMDocument);
			VARIANT_BOOL success;
			document->loadXML(xml, &success);

			CComPtr<ILDOMElement> documentElement;
			document->get_documentElement(&documentElement);
			if (documentElement)
			{
				CSiteItem* pNewItem = FromElement(pParentDir, documentElement);
				if (pNewItem)
				{
					m_treeCtl->InsertItem((DWORD)pNewItem, pParentDir->m_treeItem, NULL, NULL, pNewItem->m_iIcon, pNewItem->m_cChildren, &pNewItem->m_treeItem);
				}
			}
		}
	}
	else if (action == 2)	// Delete File
	{
		CSiteItem* pItem = FindFileByName(rootItem, _bstr_t(pathName));
		if (pItem)
		{
			m_treeCtl->DeleteItem(pItem->m_treeItem);
			delete pItem;	// TODO, this doesn't delete children
		}
	}
	else if (action == 3)	// Update file
	{
		CSiteItem* pItem = FindFileByName(rootItem, _bstr_t(pathName));
		if (pItem)
		{
			CComBSTR xml;
			pWebSite->m_webSite->GetItemAttributes(pathName, &xml);

			CComPtr<ILDOMDocument> document;
			document.CoCreateInstance(CLSID_LDOMDocument);
			VARIANT_BOOL success;
			document->loadXML(xml, &success);

			CComPtr<ILDOMElement> documentElement;
			document->get_documentElement(&documentElement);
			if (documentElement)
			{
				CSiteItem* pNewItem = FromElement(pItem->m_parent, documentElement);
				if (pNewItem)
				{
					pNewItem->m_treeItem = pItem->m_treeItem;
					m_treeCtl->SetItemInfo(pItem->m_treeItem, (DWORD)pNewItem, pNewItem->m_iIcon, pNewItem->m_cChildren);
					delete pItem;

					m_treeCtl->UpdateItem(pNewItem->m_treeItem);
				}
			}
		}
	}
}

HRESULT __stdcall CSiteFilesView::OnFileUpdate(long parentFolderId, long fileId, long action)
{
#if 0
	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	CComPtr<IUITreeItem> rootItem;
	m_treeCtl->GetRootItem(&rootItem);

	if (action == 1)	// New File
	{
		CSiteDir* pParentDir = (CSiteDir*)FindFileById(rootItem, parentFolderId);
		if (pParentDir && pParentDir->m_bPopulated)
		{
			WCHAR sql[256];
			swprintf(sql, L"SELECT id,filename,type,file_size,file_date FROM files WHERE id = %d", fileId);
			_variant_t va;

			ADODB::_ConnectionPtr conn;
			pWebSite->m_webSite->GetDBConnection((IDispatch**)&conn);

			ADODB::_RecordsetPtr recordset = conn->Execute(sql, &va, ADODB::adCmdText);

			CSiteItem* pNewItem = FromRecordSet(pParentDir, recordset);
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

			ADODB::_ConnectionPtr conn;
			pWebSite->m_webSite->GetDBConnection((IDispatch**)&conn);

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
long CSiteFilesView::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnButtonDown(wParam, point, 0, TRUE);

	return HANDLE_BASE<IUIView>(m_puiwnd, uMsg, wParam, lParam);
}

void CSiteFilesView::OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk)
{
}
*/

STDMETHODIMP CSiteFilesView::GetItemText(ULONG itemdata, LONG column, BSTR * pVal)
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

void CSiteFilesView::InitTree()
{
	CWebSite* pWebSite = (CWebSite*)m_document;

	m_treeCtl->ResetContent(NULL);

	CComBSTR rootPath;
	pWebSite->m_webSite->get_rootPath(&rootPath);

//	CComBSTR m_rootDisplayPath;
//	pWebSite->m_webSite->GetFolderDisplayPath(m_rootFolderId, &m_rootDisplayPath);
//	_bstr_t rootPath = pWebSite->m_webSite->rootPath;

	CSiteDir* pRoot = new CSiteDir;
//	pRoot->m_dbid = m_rootFolderId;
	pRoot->m_bPopulated = VARIANT_TRUE;
	m_treeCtl->SetRootItem((DWORD)pRoot, &pRoot->m_treeItem);

//	strcpy(pRoot->m_wfd.cFileName, _bstr_t(rootPath));

	PopulateFolder(pRoot->m_treeItem, pRoot);
}

#include "FileInspectorDlg.h"

LRESULT CSiteFilesView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SHFILEINFO	ssfi;	//get a handle to the system small icon list 

	/*
	{
		static_cast<CLXWebSiteApp*>(m_document->m_app.p)->CreateDlg(71, &m_inspectorDlg);
		m_inspectorDlg->Create(m_hWnd);
		m_inspectorDlg->ShowWindow(SW_SHOW);

		static_cast<CFileInspectorDlg*>(m_inspectorDlg.p)->SetFilesView(this);
	}
	*/
	{
		CComObject<CFileInspectorDlg>* p;
		CComObject<CFileInspectorDlg>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			ATLASSERT(0);
			//p->m_app = m_app;
			p->SetFilesView(this);
		}

		m_inspectorDlg = p;
		if (m_inspectorDlg)
		{
			m_inspectorDlg->Create(m_hWnd);
			m_inspectorDlg->ShowWindow(SW_SHOW);
		}
	}

	m_hFileIcons = (HIMAGELIST)::SHGetFileInfo(
		(LPCTSTR)_T("C:\\"),
		0,
		&ssfi, sizeof(SHFILEINFO),
		SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

	IUnknown* p;

	CRect rc(0,0,0,0);
	m_axtreeCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axtreeCtl.AttachControl(m_treeCtl, &p);

	IDispEventImpl<4, CSiteFilesView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_treeCtl);

	m_treeCtl->put_hImageList((DWORD)m_hFileIcons);

	CWebSite* pWebSite = (CWebSite*)m_document;

	InitTree();

	HRESULT hr = IDispEventImpl<5, CSiteFilesView, &DIID__ILXLocalWebSiteEvents, &LIBID_LXWEBSITELib, 1, 0>::DispEventAdvise(pWebSite->m_webSite);
	ATLASSERT(SUCCEEDED(hr));

	::RegisterDragDrop(m_hWnd, (IDropTarget*)this);

	return 0;
}

LRESULT CSiteFilesView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<4, CSiteFilesView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_treeCtl);

	RevokeDragDrop(m_hWnd);

	return 0;
}

LRESULT CSiteFilesView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

void CSiteFilesView::OnSize()
{
	CRect	client;
	GetClientRect(&client);

	int cx = client.Width();
	int cy = client.Height();

	int top = m_titleHeight;

	int left;
	if (TRUE)
	{
		left = 140;
		HWND hwnd;
		m_inspectorDlg->get_hwnd(&hwnd);

		::MoveWindow(hwnd, 0, top, left, cy-top, TRUE);
	}
	else
		left = 0;

	m_axtreeCtl.MoveWindow(left, top, cx-left, cy-top, TRUE);
}

STDMETHODIMP CSiteFilesView::get_webSiteDocument(IWebSite **pVal)
{
	*pVal = m_document;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

/*
HRESULT __stdcall CSiteFilesView::OnFileTreeChanged()
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
STDMETHODIMP CSiteFilesView::put_webSiteDocument(IWebSite *newVal)
{
	/*
	if (m_document)
		IDispEventImpl<3, CSiteFilesView, &DIID__IWebSiteEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_pDocument);
*/
	m_document = newVal;
/*
	if (m_document)
		IDispEventImpl<3, CSiteFilesView, &DIID__IWebSiteEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventAdvise(m_pDocument);
*/
	return S_OK;
}
#endif

STDMETHODIMP CSiteFilesView::SetRootFolderId(unsigned long folder_id)
{
#if 0
	m_rootFolderId = folder_id;

	InitTree();
	InvalidateRect(NULL, TRUE);
#endif

	return S_OK;
}

STDMETHODIMP CSiteFilesView::GetRootFolderId(unsigned long *folder_id)
{
#if 0
	if (m_rootFolderId == NULL) return E_POINTER;
	*folder_id = m_rootFolderId;
#endif

	return S_OK;
}

STDMETHODIMP CSiteFilesView::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	return S_OK;
}

STDMETHODIMP CSiteFilesView::DragOver(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
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

	return S_OK;
}

STDMETHODIMP CSiteFilesView::DragLeave()
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

STDMETHODIMP CSiteFilesView::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
#if 0
	CWebSite* pWebSite = (CWebSite*)m_document.p;

	DWORD parent_id;

	if (m_prevDropItem)
	{
		DWORD state;
		m_treeCtl->GetItemState(m_prevDropItem, &state);
		m_treeCtl->SetItemState(m_prevDropItem, state &~ 2);

		CSiteItem* pItem;
		m_treeCtl->GetItemInfo(m_prevDropItem, (DWORD*)&pItem, NULL, NULL);

		if (pItem->m_type == 1)	// Dropped on directory
			parent_id = pItem->m_dbid;
		else
			parent_id = ((CSiteItem*)pItem->m_parent)->m_dbid;

		m_prevDropItem = NULL;
	}
	else
	{
		parent_id = m_rootFolderId;
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
				pWebSite->CopyMoveFiles(parent_id, sa, VARIANT_FALSE, &nFilesCopied);

				SafeArrayDestroy(sa);
			}

			GlobalUnlock(hData);

			*pdwEffect = DROPEFFECT_COPY;
		}
	}
#endif

	return S_OK;
}

// ICommandTarget
STDMETHODIMP CSiteFilesView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// Try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	CComQIPtr<ICommandTarget> target;

// Try document
	target = m_document;
	target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	return S_OK;
}

BEGIN_CMD_MAP(CSiteFilesView)
	CMD_HANDLER(ID_EDIT_CLEAR, OnEditDelete)
	CMD_UPDATE(ID_EDIT_CLEAR, OnEditDeleteUpdate)
/*
	CMD_HANDLER(&ID_FILES_HOMEPAGE, OnFileSetasHomepage)
	CMD_UPDATE(&ID_FILES_HOMEPAGE, OnFileSetasHomepageUpdate)
	CMD_HANDLER(&ID_FILES_NEWFOLDER, OnFileNewFolder)
*/
END_CMD_MAP()

LRESULT CSiteFilesView::OnFileNewFolder(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	DWORD parent_id;

	CComPtr<IUITreeItem> active;
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

	DWORD folder_id;
	pWebSite->m_webSite->CreateFolder(parent_id, L"untitled", L"", &folder_id);
	if (folder_id)
	{
		CComPtr<IUITreeItem> rootItem;
		m_treeCtl->GetRootItem(&rootItem);

		CSiteItem* pItem = FindFileById(rootItem, folder_id);
		if (pItem)
		{
			m_treeCtl->EditLabel(pItem->m_treeItem, NULL);
		}
	}
#endif

	return 0;
}

LRESULT CSiteFilesView::OnEditDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CWebSite* pWebSite = ((CWebSite*)m_document);

	CComPtr<IUITreeItem> active;
	m_treeCtl->GetSelectedItem(&active);

	if (active)
	{
		CSiteItem* pItem;
		m_treeCtl->GetItemInfo(active, (DWORD*)&pItem, NULL, NULL);

		CComPtr<IUITreeItem> parentitem;
		m_treeCtl->GetParentItem(active, &parentitem);

		CComPtr<IUITreeItem> child;
		m_treeCtl->GetFirstChildItem(parentitem, &child);
		while (child)
		{
			DWORD state;
			m_treeCtl->GetItemState(child, &state);

			CComPtr<IUITreeItem> nextSibling;
			m_treeCtl->GetNextSiblingItem(child, &nextSibling);

			if (state & 1)
			{
				CSiteItem* pFile;
				m_treeCtl->GetItemInfo(child, (DWORD*)&pFile, NULL, NULL);

				ATLASSERT(0);
#if 0
				pWebSite->m_webSite->DeleteFilePermanently(pFile->m_dbid);
#endif
			}

			child = nextSibling;
		}
	}

	return 0;
}

void CSiteFilesView::OnEditDeleteUpdate(long iid, IUICmdUpdate* pCmdUI)
{
}

LRESULT CSiteFilesView::OnFileSetasHomepage(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	CComPtr<IUITreeItem> active;
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
#endif

#if 0
	if (m_pActive && m_pActive->m_type == 2)
	{
		((CWebSite*)m_document.p)->m_pFileHomepage = (CSiteFile*)m_pActive;
	}
#endif

	return 0;
}

void CSiteFilesView::OnFileSetasHomepageUpdate(long iid, IUICmdUpdate* pCmdUI)
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
