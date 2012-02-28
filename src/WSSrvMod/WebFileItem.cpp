#include "stdafx.h"
#include "WSSrvMod.h"

#include "WebFileItem.h"

#include "WSSrv.h"


void DbError(_com_error &e);

extern DWORD g_threadId;

DWORD __stdcall ChangeNotifyThread(LPVOID param)
{
   HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	CSiteDir* pDir = (CSiteDir*)param;
	
	HANDLE hChangeHandle;

	hChangeHandle = FindFirstChangeNotification(pDir->GetFullPathName(),
			FALSE,//TRUE,
			FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME |
			FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE
			);

	while (1)
	{
		DWORD nObject = MsgWaitForMultipleObjectsEx(
		  1,          // number of handles in handle array
		  &hChangeHandle,     // pointer to an object-handle array
		  INFINITE,  // time-out interval in milliseconds
		  QS_ALLEVENTS,      // type of input events to wait for
		  0         // wait flags
		);

		if (nObject == WAIT_OBJECT_0)
		{
			PostThreadMessage(g_threadId, WM_USER+1024, 0, (LPARAM)pDir);
		//	pDir->ScanFiles(TRUE, TRUE, FALSE);
		}
		else
		{
			break;
		}

		if (FindNextChangeNotification(hChangeHandle) == 0)
			break;
	}

	FindCloseChangeNotification(hChangeHandle);

	CoUninitialize();

	return 0;
}

CSiteDir::CSiteDir()
{
	m_type = 1;

	m_dwChangeThreadID = 0L;
	m_hChangeThread = NULL;
}

CSiteDir::~CSiteDir()
{
	QuitFileThread();

	while (!m_childList.IsEmpty())
	{
		CSiteItem* pItem = (CSiteItem*)m_childList.RemoveHead();
		delete pItem;
	}
}

void CSiteDir::ListenToChanges()
{
	m_hChangeThread = CreateThread(NULL, 0, ChangeNotifyThread, this, 0, &m_dwChangeThreadID);
}

void CSiteDir::QuitFileThread()
{
	if (m_hChangeThread)
	{
		PostThreadMessage(m_dwChangeThreadID, WM_QUIT, 0, 0);
		WaitForSingleObject(m_hChangeThread, INFINITE);	// Wait 10 seconds for thread to finish

		m_dwChangeThreadID = 0L;
		m_hChangeThread = NULL;
	}
}

CSiteItem* CSiteDir::FileExists(LPCTSTR pathname, int type)
{
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CSiteItem* pItem = (CSiteItem*)m_childList.GetNext(pos);
		if (!strcmp(pItem->m_wfd.cFileName, pathname) && (pItem->m_type == type))
			return pItem;
	}

	return NULL;
}

CSiteItem* CSiteDir::FindFilePathName(LPCTSTR pathName, int type)
{
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CSiteItem* pItem = (CSiteItem*)m_childList.GetNext(pos);
		if (pItem->m_type == 2)
		{
			CUString str = ((CSiteFile*)pItem)->GetFullPathName();
			ATLTRACE("file: %s\n", (LPCSTR)str);

			if (!stricmp(pathName, str))
				return pItem;
		}
		else
		{
			CSiteDir* pDir = (CSiteDir*)pItem;

			CSiteItem* pFItem = pDir->FindFilePathName(pathName, type);	// Recurse
			if (pFItem)
				return pFItem;
		}
	}

	return NULL;
}

CSiteItem* CSiteDir::FindItemByID(DWORD id, int type)
{
	if (m_dbid == id && m_type == type)
		return this;

	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CSiteItem* pItem = (CSiteItem*)m_childList.GetNext(pos);
		if (pItem->m_type == type)
		{
			if (pItem->m_dbid == id)
				return pItem;
		}

		if (pItem->m_type == 1)	// Recurse
		{
			CSiteDir* pDir = (CSiteDir*)pItem;

			CSiteItem* pFItem = pDir->FindItemByID(id, type);
			if (pFItem)
				return pFItem;
		}
	}

	return NULL;
}

void CSiteDir::RemoveFromDatabase()
{
// Remove children
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CSiteItem* pItem = (CSiteItem*)m_childList.GetNext(pos);
		pItem->RemoveFromDatabase();
	}

	CSiteItem::RemoveFromDatabase();
}

void CSiteFile::RemoveFromDatabase()
{
	CSiteItem::RemoveFromDatabase();
}

void CSiteItem::RemoveFromDatabase()
{
	try
	{
		WCHAR sql[256];
		swprintf(sql, L"DELETE FROM files WHERE id = %d", m_dbid);

		_variant_t va;
		m_pWebSite->m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);
	}
	catch (_com_error &e)
	{
		MessageBox(NULL, "Error RemoveFromDatabase()", "WebEditorServer", MB_OK);
		DbError(e);
	}

	m_pWebSite->Fire_FileUpdate(m_parent->m_dbid, m_dbid, 2);
}

void CSiteItem::UpdateDatabase()
{
	ATLASSERT(m_parent);

	try
	{
		double lastWriteTime;
		SYSTEMTIME systime;
		FileTimeToSystemTime(&m_wfd.ftLastWriteTime, &systime);
		SystemTimeToVariantTime(&systime, &lastWriteTime);

		WCHAR sql[256];
		swprintf(sql, L"SELECT file_size, file_date FROM files WHERE id = %d", m_dbid);

		ADODB::_RecordsetPtr recordset(L"ADODB.RecordSet");
		recordset->Open(
			sql,
			_variant_t((IDispatch*)m_pWebSite->m_siteDataConnection),
			ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdText);

		recordset->Fields->Item[_bstr_t(L"file_size")]->Value = (long)m_wfd.nFileSizeLow;
		recordset->Fields->Item[_bstr_t(L"file_date")]->Value = (double)lastWriteTime;

		recordset->Update();
	}
	catch (_com_error &e)
	{
		MessageBox(NULL, "Error UpdateDatabase()", "WebEditorServer", MB_OK);
		DbError(e);
	}

	m_pWebSite->Fire_FileUpdate(m_parent->m_dbid, m_dbid, 3);
}

void CSiteItem::AddSiteItemToDatabase()
{
	ATLASSERT(m_parent);

	try
	{
		double lastWriteTime;
		SYSTEMTIME systime;
		FileTimeToSystemTime(&m_wfd.ftLastWriteTime, &systime);
		SystemTimeToVariantTime(&systime, &lastWriteTime);

		m_dbid = m_pWebSite->AddNewFile(((CSiteDir*)m_parent)->m_dbid, m_type, _bstr_t(m_wfd.cFileName), m_wfd.nFileSizeLow, lastWriteTime);
	}
	catch (_com_error &e)
	{
		MessageBox(NULL, "Error AddSiteItemToDatabase()", "WebEditorServer", MB_OK);
		DbError(e);
	}

	m_pWebSite->Fire_FileUpdate(m_parent->m_dbid, m_dbid, 1);
}

void CollectElementTags(BSTR ftagName, CArray<IDOMElement*,IDOMElement*>& elements, IDOMElement* parent)
{
	CComQIPtr<IDOMNode> child;
	parent->get_firstChild(&child);
	while (child)
	{
		CComQIPtr<IDOMElement> element = child;
		if (element)
		{
			BSTR btagName;
			element->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcsicmp(tagName, ftagName))
			{
				element.p->AddRef();
				elements.Add(element);
			}

			CollectElementTags(ftagName, elements, element);	// Recurse
		}

		CComQIPtr<IDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
}

void CSiteFile::SaveDOMElementToDatabase(IDOMElement* parent, int parentNode_id, int index)
{
	BSTR bnamespaceURI;
	parent->get_namespaceURI(&bnamespaceURI);

	BSTR btagName;
	parent->get_tagName(&btagName);

	DWORD ownerElement_id;

	try
	{
		WCHAR sql[256];
		swprintf(sql, L"INSERT INTO DOMElement (ownerDocument_id, namespaceURI, tagName) VALUES (%d, '%s', '%s')", m_ownerDocument_id, bnamespaceURI, btagName);

		_variant_t	va;

		va.Clear();
		m_pWebSite->m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);

		ADODB::_RecordsetPtr recordset;
		recordset = m_pWebSite->m_siteDataConnection->Execute(L"SELECT MAX(id) AS id FROM DOMElement", &va, ADODB::adCmdText);

		ownerElement_id = recordset->Fields->Item[_bstr_t(L"id")]->Value.lVal;
	}
	catch (_com_error &e)
	{
		MessageBox(NULL, "Error SaveDOMElementToDatabase()", "WebEditorServer", MB_OK);
		DbError(e);
	}

	SysFreeString(bnamespaceURI);
	SysFreeString(btagName);

	unsigned long i;

// Attributes
	CComQIPtr<IDOMNamedNodeMap> attributes;
	parent->get_attributes(&attributes);
	unsigned long length;
	attributes->get_length(&length);

	for (i = 0; i < length; i++)
	{
		CComQIPtr<IDOMAttr> attr;
		attributes->item(i, (IDOMNode**)&attr);

		BSTR bnamespaceURI;
		attr->get_namespaceURI(&bnamespaceURI);

		BSTR bname;
		attr->get_name(&bname);

		BSTR bvalue;
		attr->get_value(&bvalue);

		try
		{
			WCHAR sql[256];
			
			swprintf(sql,
				L"INSERT INTO DOMAttr (ownerElement_id, namespaceURI, attrname, attrvalue, attrindex) VALUES (%d, '%s', '%s', '%s', %d)",
				ownerElement_id, bnamespaceURI?bnamespaceURI:L"", bname, bvalue, i);

			ATLTRACE(L"sql: %s\n", sql); 

			_variant_t	va;
			m_pWebSite->m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);
		}
		catch (_com_error &e)
		{
			MessageBox(NULL, "Error SaveDOMElementToDatabase()", "WebEditorServer", MB_OK);
			DbError(e);
		}

		SysFreeString(bnamespaceURI);
		SysFreeString(bname);
		SysFreeString(bvalue);
	}

// Child nodes
	CComQIPtr<IDOMNodeList> childNodes;
	parent->get_childNodes(&childNodes);

	childNodes->get_length(&length);

	for (i = 0; i < length; i++)
	{
		CComQIPtr<IDOMNode> child;
		childNodes->item(i, &child);

		CComQIPtr<IDOMElement> element = child;
		if (element)
		{
			SaveDOMElementToDatabase(element, ownerElement_id, i);
		}
	}
}

void CSiteFile::UpdateOutLinks()
{
	try
	{
		WCHAR sql[256];
		swprintf(sql, L"DELETE FROM links WHERE file_id = %d", m_dbid);

		//m_pWebSite->m_siteDataConnection->BeginTrans();

		_variant_t	va;
		m_pWebSite->m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);

		//m_pWebSite->m_siteDataConnection->CommitTrans();
	}
	catch (_com_error &e)
	{
		MessageBox(NULL, "Error UpdateOutLinks()", "WebEditorServer", MB_OK);
		DbError(e);
	}

	TCHAR ext[_MAX_EXT];
	_splitpath(m_wfd.cFileName, NULL, NULL, NULL, ext);

	if (!stricmp(ext, ".htm") ||
		!stricmp(ext, ".html") ||
		!stricmp(ext, ".asp") ||
		!stricmp(ext, ".xml") ||
		!stricmp(ext, ".svg"))
	{
		CComQIPtr<IDOMDocumentContainer> documentcnt;
		documentcnt.CoCreateInstance(CLSID_DOMDocumentContainer);

		CSiteDir* pDir = (CSiteDir*)m_parent;

		CUString pathName = GetFullPathName();

		VARIANT_BOOL bsuccess;
		documentcnt->load(_bstr_t(pathName), &bsuccess);

		if (bsuccess)
		{
			CComQIPtr<IDOMDocument> document;
			documentcnt->get_document(&document);
			if (document != NULL)
			{
				{ // Links
					CComQIPtr<IDOMElement> documentElement;
					document->get_documentElement(&documentElement);

					CComQIPtr<IMMSXHTMLDocument> htmldocument;
					CComQIPtr<ISVGDocument> svgdocument;

					CArray<IDOMElement*,IDOMElement*> elements;

					if (htmldocument = document)
					{
						CollectElementTags(L"a", elements, documentElement);
					}
					else if (svgdocument = document)
					{
						CollectElementTags(L"a", elements, documentElement);
					}

					for (int i = 0; i < elements.GetSize(); i++)
					{
						IDOMElement* element = elements[i];

						BSTR bhref;

						if (htmldocument)
						{
							element->getAttribute(L"href", &bhref);
						}
						else if (svgdocument)
						{
							// TODO, use getAttributeNS
							element->getAttribute(L"xlink:href", &bhref);
						}

						_bstr_t href = _bstr_t(bhref, false);
						if (href.length())
						{
							char oldcwd[_MAX_PATH];
							_getcwd(oldcwd, _MAX_PATH);

							chdir(pDir->GetFullPathName());
							char fullpath[_MAX_PATH];
							_fullpath(fullpath, href, _MAX_PATH);

							chdir(oldcwd);

							CSiteFile* pHrefFile = (CSiteFile*)m_pWebSite->m_pRootDir->FindFilePathName(fullpath, 2);

							if (pHrefFile)
							{
								try
								{
									//m_pWebSite->m_siteDataConnection->BeginTrans();

									WCHAR sql[256];
									swprintf(sql, L"INSERT INTO links (file_id, out_link_id) VALUES (%d, %d)", m_dbid, pHrefFile->m_dbid);

									_variant_t	va;
									m_pWebSite->m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);

									//m_pWebSite->m_siteDataConnection->CommitTrans();
								}
								catch (_com_error &e)
								{
									MessageBox(NULL, "Error Insert Into Links()", "WebEditorServer", MB_OK);
									DbError(e);
								}
							}
						}

						element->Release();
					}

					elements.RemoveAll();
				}

			// DOM hierarchy
				if (FALSE)
				{
					try
					{
						m_pWebSite->m_siteDataConnection->BeginTrans();

						WCHAR sql[256];
						swprintf(sql, L"INSERT INTO DOMDocument (file_id) VALUES (%d)", m_dbid);

						_variant_t	va;

						va.Clear();
						m_pWebSite->m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);

						ADODB::_RecordsetPtr recordset;
						recordset = m_pWebSite->m_siteDataConnection->Execute(L"SELECT MAX(id) AS id FROM DOMDocument", &va, ADODB::adCmdText);

						m_ownerDocument_id = recordset->Fields->Item[_bstr_t(L"id")]->Value.lVal;

						CComQIPtr<IDOMElement> documentElement;
						document->get_documentElement(&documentElement);
						if (documentElement)
						{
							SaveDOMElementToDatabase(documentElement, 0, 0);
						}

						m_pWebSite->m_siteDataConnection->CommitTrans();
					}
					catch (_com_error &e)
					{
						MessageBox(NULL, "Error UpdateDOMDatabase()", "WebEditorServer", MB_OK);
						DbError(e);
					}
				}
			}
		}
	}

#if 0
	m_pWebSite->Fire_OutLinksChanged(m_dbid);
#endif
}

CUString CSiteItem::GetFullPathName()
{
	CSiteDir* pDir = (CSiteDir*)m_parent;

	if (pDir)
	{
		TCHAR pathName[_MAX_PATH];
		_makepath(pathName, NULL, pDir->GetFullPathName(), m_wfd.cFileName, NULL);

		return pathName;
	}
	else
	{
		return m_wfd.cFileName;
	}
}

void CSiteDir::BuildFromDatabase()
{
	WCHAR sql[256];
	swprintf(sql, L"SELECT id,filename,type,file_size,file_date FROM files WHERE parent_id = %d", m_dbid);
	_variant_t va;
	ADODB::_ConnectionPtr conn = m_pWebSite->m_siteDataConnection;
	ADODB::_RecordsetPtr recordset = conn->Execute(sql, &va, ADODB::adCmdText);

	CArray<CSiteDir*,CSiteDir*> dirs;

	while (recordset->EndOfFile == false)
	{
		CSiteItem* pItem;

		BYTE type = recordset->Fields->Item[_bstr_t("type")]->Value.lVal;
		if (type == 1)	// Directory
		{
			CSiteDir* pDir = new CSiteDir;
			pItem = pDir;
			dirs.Add(pDir);
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
			pItem->m_pWebSite = m_pWebSite;
			pItem->m_dbid = recordset->Fields->Item[_bstr_t("id")]->Value.lVal;
			pItem->m_wfd.nFileSizeLow = recordset->Fields->Item[_bstr_t("file_size")]->Value.lVal;
			strcpy(pItem->m_wfd.cFileName, _bstr_t(recordset->Fields->Item[_bstr_t("filename")]->Value));

			double lastWriteTime = recordset->Fields->Item[_bstr_t("file_date")]->Value;
			SYSTEMTIME systime;
			VariantTimeToSystemTime(lastWriteTime, &systime);
			SystemTimeToFileTime(&systime, &pItem->m_wfd.ftLastWriteTime);

			AddChildTail(pItem);
		}

		recordset->MoveNext();
	}

	for (int i = 0; i < dirs.GetSize(); i++)
	{
		dirs[i]->BuildFromDatabase();	// Recurse
	}
}

void CSiteDir::ScanFiles(BOOL bCheckExisting/* = FALSE*/, BOOL bUpdateDB /* = FALSE */, BOOL bRecursive /* = TRUE*/, CSiteItem** pActive/* = NULL*/)
{
	HANDLE hFindFile;
	WIN32_FIND_DATA	wfd;

	TCHAR	search[MAX_PATH];
	wsprintf(search, "%s\\*.*", GetFullPathName());

	if (bCheckExisting)
	{
// Assume that all files have been deleted
		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CSiteItem* pItem = (CSiteItem*)m_childList.GetNext(pos);
			pItem->m_bFoundOnDisk = FALSE;
		}
	}

	if ((hFindFile = FindFirstFile(search, &wfd)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (wfd.cFileName[0] != '.')
			{
				CSiteItem* pExistingItem = NULL;

				if (bCheckExisting)
				{
					pExistingItem = FileExists(wfd.cFileName, (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)? 1: 2);
					if (pExistingItem)
					{
						pExistingItem->m_bFoundOnDisk = TRUE;
					}
				}

				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					CSiteDir* pDir;

					if (pExistingItem)
					{
						pDir = (CSiteDir*)pExistingItem;
					}
					else
					{
						pDir = new CSiteDir;
						pDir->m_pWebSite = m_pWebSite;

						pDir->m_wfd = wfd;
						pDir->m_bFoundOnDisk = TRUE;

						AddChildTail(pDir);

						pDir->AddSiteItemToDatabase();
					}

					if (bRecursive)
					{
						pDir->ScanFiles(bCheckExisting, bUpdateDB, bRecursive, pActive);
					}
				}
				else
				{
					if (pExistingItem)
					{
						CSiteFile* pFile = (CSiteFile*)pExistingItem;

						if (pFile->m_wfd.nFileSizeLow != wfd.nFileSizeLow ||
							pFile->m_wfd.nFileSizeHigh != wfd.nFileSizeHigh ||							
							pFile->m_wfd.dwFileAttributes != wfd.dwFileAttributes ||
							memcmp(&pFile->m_wfd.ftLastWriteTime, &wfd.ftLastWriteTime, sizeof(FILETIME)) ||
							memcmp(&pFile->m_wfd.ftCreationTime, &wfd.ftCreationTime, sizeof(FILETIME)))
						{
							pFile->m_wfd = wfd;

							if (bUpdateDB)
							{
								pFile->UpdateDatabase();
								pFile->UpdateOutLinks();
							}
						}
					}
					else
					{
						CSiteFile* pFile = new CSiteFile;
						pFile->m_pWebSite = m_pWebSite;

						pFile->m_bFoundOnDisk = TRUE;
						pFile->m_wfd = wfd;

						AddChildTail(pFile);

						pFile->AddSiteItemToDatabase();
					}
				}
			}
		}
		while (FindNextFile(hFindFile, &wfd));

		FindClose(hFindFile);
	}

	if (bCheckExisting)
	{
	// Traverse all items, and remove the files that no longer exist on disk
		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			UPOSITION pos2 = pos;
			CSiteItem* pItem = (CSiteItem*)m_childList.GetNext(pos);
			if (!pItem->m_bFoundOnDisk)
			{
				pItem->RemoveFromDatabase();

				m_childList.RemoveAt(pos2);
				delete pItem;
			}
		}
	}

	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CSiteDir* pDir = (CSiteDir*)m_childList.GetNext(pos);
		if (pDir->m_type == 1)
		{
			pDir->ListenToChanges();
		}
	}
}
