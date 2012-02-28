// SiteFilesView.cpp : Implementation of CSiteFilesView
#include "stdafx.h"
#include "WebEditor.h"
#include "WebEditor2.h"
#include "SiteFilesView.h"

#include "WebSite.h"

#include "WebEditorApp.h"
#include "WebEditorFrame.h"

extern CWebEditorApp* gApp;

#define PANE_NAME		0
#define PANE_STATUS	1
#define PANE_SIZE		2
#define PANE_DATE		3

static int m_titleHeight = 16;

CSiteItem * CSiteFilesView::FromRecordSet(CSiteDir* pParentDir, ADODB::_RecordsetPtr recordset)
{
	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	CSiteItem* pItem;

	BYTE type = recordset->Fields->Item[_bstr_t("type")]->Value.lVal;
	_bstr_t filename = recordset->Fields->Item[_bstr_t("filename")]->Value;

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
		pItem->m_dbid = recordset->Fields->Item[_bstr_t("id")]->Value.lVal;
		pItem->m_wfd.nFileSizeLow = recordset->Fields->Item[_bstr_t("file_size")]->Value.lVal;

		// lastWriteDate
		double lastWriteTime = recordset->Fields->Item[_bstr_t("file_date")]->Value;
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

			ADODB::_ConnectionPtr conn = pWebSite->m_webSite->GetDBConnection();

			WCHAR sql[256];
			swprintf(sql, L"SELECT COUNT(*) AS c FROM files WHERE parent_id = %d", pItem->m_dbid);
			_variant_t va;
			ADODB::_RecordsetPtr rs = conn->Execute(sql, &va, ADODB::adCmdText);
			pItem->m_cChildren = (rs->Fields->Item[_bstr_t(L"c")]->Value.lVal > 0L)? 1: 0;
		}
	}

	return pItem;
}

void CSiteFilesView::PopulateFolder(DWORD parentItem, CSiteDir* pParentDir)
{
	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	pParentDir->m_bPopulated = VARIANT_TRUE;

	ADODB::_ConnectionPtr conn = pWebSite->m_webSite->GetDBConnection();

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
}

/////////////////////////////////////////////////////////////////////////////
// CSiteFilesView

CSiteFilesView::CSiteFilesView()
{
	m_rootFolderId = 0L;
	m_prevDropItem = NULL;
}

int CSiteFilesView::FinalConstruct()
{
	HRESULT hr;

	hr = m_treeCtl.CoCreateInstance(CLSID_UITreeControl);
	if (FAILED(hr)) return hr;

	IDispEventImpl<4, CSiteFilesView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_treeCtl);

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

	IDispEventImpl<4, CSiteFilesView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_treeCtl);
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
	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	if (m_rootFolderId != 0)
	{
		DWORD parent_id = pWebSite->m_webSite->GetParentFolderId(m_rootFolderId);

		SetRootFolderId(parent_id);
		InvalidateRect(NULL, TRUE);
	}

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

HRESULT __stdcall CSiteFilesView::OnItemClick(DWORD item)
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

HRESULT __stdcall CSiteFilesView::OnItemDblClick(DWORD item)
{
	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	DWORD active;
	m_treeCtl->GetSelectedItem(&active);

	if (active)
	{
		CSiteItem* pItem;
		m_treeCtl->GetItemInfo(active, (DWORD*)&pItem, NULL, NULL);
		if (pItem->m_type == 1)	// Double-clicking on folder sets it as new root-folder
		{
			CSiteDir* pDir = (CSiteDir*)pItem;
			SetRootFolderId(pDir->m_dbid);
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

					VARIANT_BOOL success;
					pWebSite->OpenDocument(pFile->m_dbid, &success);
				}

				m_treeCtl->GetNextSiblingItem(child, &child);
			}
		}
	}

	return S_OK;
}

HRESULT __stdcall CSiteFilesView::OnContextMenu(long x, long y)
{
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

	return S_OK;
}

HRESULT __stdcall CSiteFilesView::OnItemExpanding(long item, VARIANT_BOOL bExpanding, BOOL* bCancel)
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

/*
void com_error_Message(_com_error &e)
{
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
      
	CUString msg;
	msg.Format("\n\tSource :  %s \n\tdescription : %s \n ",(LPCSTR)bstrSource,(LPCSTR)bstrDescription);

	MessageBox(NULL, msg, "WebEditor", MB_OK);
}
*/

HRESULT __stdcall CSiteFilesView::OnEndLabelEdit(long item, BSTR text)
{
	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	CSiteItem* pItem;
	m_treeCtl->GetItemInfo(item, (DWORD*)&pItem, NULL, NULL);

	if (wcscmp(_bstr_t(pItem->m_wfd.cFileName), text) != 0)
	{
		try
		{
			pWebSite->m_webSite->RenameFile(pItem->m_dbid, text);
		}
		catch(_com_error e)
		{
			com_error_Message(e);
		}
	}

	return S_OK;
}

CSiteItem* CSiteFilesView::FindFileById(DWORD parentItem, long file_id)
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

HRESULT __stdcall CSiteFilesView::OnFileUpdate(long parentFolderId, long fileId, long action)
{
	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	DWORD rootItem;
	m_treeCtl->GetRootItem(&rootItem);

	if (action == 1)	// New File
	{
		CSiteDir* pParentDir = (CSiteDir*)FindFileById(rootItem, parentFolderId);
		if (pParentDir && pParentDir->m_bPopulated)
		{
			WCHAR sql[256];
			swprintf(sql, L"SELECT id,filename,type,file_size,file_date FROM files WHERE id = %d", fileId);
			_variant_t va;
			ADODB::_ConnectionPtr conn = pWebSite->m_webSite->GetDBConnection();
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
			ADODB::_ConnectionPtr conn = pWebSite->m_webSite->GetDBConnection();
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
	CWebSite* pWebSite = (CWebSite*)m_document.p;

	m_treeCtl->ResetContent(NULL);

	m_rootDisplayPath = pWebSite->m_webSite->GetFolderDisplayPath(m_rootFolderId);
//	_bstr_t rootPath = pWebSite->m_webSite->rootPath;

	CSiteDir* pRoot = new CSiteDir;
	pRoot->m_dbid = m_rootFolderId;
//	pRoot->m_bPopulated = VARIANT_TRUE;
	m_treeCtl->SetRootItem((DWORD)pRoot, &pRoot->m_treeItem);

	PopulateFolder(pRoot->m_treeItem, pRoot);
}

long CSiteFilesView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

	CWebSite* pWebSite = (CWebSite*)m_document.p;

	InitTree();

	HRESULT hr = IDispEventImpl<5, CSiteFilesView, &DIID__IWSSrvEvents, &LIBID_WSSRVMODLib, 1, 0>::DispEventAdvise(pWebSite->m_webSite);
	ATLASSERT(SUCCEEDED(hr));

	::RegisterDragDrop(m_hWnd, (IDropTarget*)this);

	return 0;
}

long CSiteFilesView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	RevokeDragDrop(m_hWnd);

	return 0;
}

long CSiteFilesView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

void CSiteFilesView::OnSize()
{
	CRect	client;
	GetClientRect(&client);

	int top = m_titleHeight;

	int cx = client.Width();
	int cy = client.Height();

	m_axtreeCtl.MoveWindow(0, top, cx, cy-top, TRUE);
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

STDMETHODIMP CSiteFilesView::SetRootFolderId(unsigned long folder_id)
{
	m_rootFolderId = folder_id;

	InitTree();
	InvalidateRect(NULL, TRUE);

	return S_OK;
}

STDMETHODIMP CSiteFilesView::GetRootFolderId(unsigned long *folder_id)
{
	if (m_rootFolderId == NULL) return E_POINTER;
	*folder_id = m_rootFolderId;

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

				long nFilesCopied;
				pWebSite->CopyMoveFiles(parent_id, sa, VARIANT_FALSE, &nFilesCopied);

				SafeArrayDestroy(sa);
			}

			GlobalUnlock(hData);

			*pdwEffect = DROPEFFECT_COPY;
		}
	}

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

LRESULT CSiteFilesView::OnEditDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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

void CSiteFilesView::OnEditDeleteUpdate(long iid, IUICmdUpdate* pCmdUI)
{
}

LRESULT CSiteFilesView::OnFileSetasHomepage(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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
