// WebSite.cpp : Implementation of CWebSite
#include "stdafx.h"
#include "WebEditor.h"
#include "WebSite.h"

extern IWebEditorApp* gApp;

void DbError(_com_error &e)
{
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
      
	CUString msg;
	msg.Format("\n\tSource :  %s \n\tdescription : %s \n ",(LPCSTR)bstrSource,(LPCSTR)bstrDescription);

	MessageBox(NULL, msg, "", MB_OK);
}

void WinError(DWORD lastError)
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
	MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
	// Free the buffer.
	LocalFree( lpMsgBuf );
}

/*
void CSiteItem::DeselectAll()
{
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CSiteItem* pItem = (CSiteItem*)m_childList.GetNext(pos);
		pItem->m_selected = FALSE;
	}
}
*/

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

void CSiteFile::RemoveFromDatabase()
{
}

void CSiteItem::UpdateDatabase()
{
	ATLASSERT(m_parent);

	try
	{
		WCHAR sql[256];
		swprintf(sql, L"UPDATE files SET file_size = %d WHERE id = %d", m_wfd.nFileSizeLow, m_dbid);

		_variant_t	va;

		va.Clear();
		m_pWebSite->m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);
	}
	catch (_com_error &e)
	{
		DbError(e);
	}
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

		ADODB::_RecordsetPtr files("ADODB.RecordSet");
		files->Open(
			L"files",
			_variant_t(m_pWebSite->m_connstr),
			ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);

		files->AddNew();
		files->Fields->Item[_variant_t(L"parent_id")]->Value = (long)((CSiteDir*)m_parent)->m_dbid;
		files->Fields->Item[_variant_t(L"type")]->Value = (long)m_type;
		files->Fields->Item[_variant_t(L"filename")]->Value = m_wfd.cFileName;
		files->Fields->Item[_variant_t(L"file_size")]->Value = (long)m_wfd.nFileSizeLow;
		files->Fields->Item[_variant_t(L"file_date")]->Value = (double)lastWriteTime;

		files->Update();
		files->Close();

		_variant_t	va;

		va.Clear();
		ADODB::_RecordsetPtr recordset;
		recordset = m_pWebSite->m_siteDataConnection->Execute(L"SELECT MAX(id) AS id FROM files", &va, ADODB::adCmdText);
	//	recordset = m_pWebSite->m_siteDataConnection->Execute(L"SELECT @@IDENTITY AS id", &va, ADODB::adCmdText);

		m_dbid = recordset->Fields->Item[_bstr_t(L"id")]->Value.lVal;
	}
	catch (_com_error &e)
	{
		DbError(e);
	}
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

		_variant_t	va;
		m_pWebSite->m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);
	}
	catch (_com_error &e)
	{
		DbError(e);
	}

	TCHAR ext[_MAX_EXT];
	_splitpath(m_wfd.cFileName, NULL, NULL, NULL, ext);

	if (!stricmp(ext, ".htm") ||
		!stricmp(ext, ".html") ||
		!stricmp(ext, ".asp") ||
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

							chdir(pDir->m_pathName);
							char fullpath[_MAX_PATH];
							_fullpath(fullpath, href, _MAX_PATH);

							chdir(oldcwd);

							CSiteFile* pHrefFile = (CSiteFile*)m_pWebSite->m_pRootDir->FindFilePathName(fullpath, 2);

							if (pHrefFile)
							{
								try
								{
									WCHAR sql[256];
									swprintf(sql, L"INSERT INTO links (file_id, out_link_id) VALUES ('%d', %d)", m_dbid, pHrefFile->m_dbid);

									_variant_t	va;
									m_pWebSite->m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);
								}
								catch (_com_error &e)
								{
									DbError(e);
								}
							}
						}

						element->Release();
					}

					elements.RemoveAll();
				}

			// DOM hierarchy
				{
					try
					{
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
					}
					catch (_com_error &e)
					{
						DbError(e);
					}
				}
			}
		}
	}

	m_pWebSite->Fire_OutLinksChanged(m_dbid);
}

void CSiteDir::UpdateOutLinks()
{
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CSiteItem* pItem = (CSiteItem*)m_childList.GetNext(pos);
		if (pItem->m_type == 2)
		{
			CSiteFile* pFile = (CSiteFile*)pItem;
			pFile->UpdateOutLinks();
		}
		else
		{
			CSiteDir* pDir = (CSiteDir*)pItem;
			pDir->UpdateOutLinks();
		}
	}
}

void CSiteDir::BuildFromDatabase()
{
	WCHAR sql[256];
	swprintf(sql, L"SELECT id,filename,type,file_size,file_date FROM files WHERE parent_id = %d", m_dbid);
	_variant_t va;
	ADODB::_RecordsetPtr recordset = m_pWebSite->m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);

	CArray<CSiteDir*,CSiteDir*> dirs;

	while (recordset->EndOfFile == false)
	{
		CSiteItem* pItem;

		BYTE type = recordset->Fields->Item[_bstr_t("type")]->Value.lVal;
		if (type == 1)	// Directory
		{
			CSiteDir* pDir = new CSiteDir;
			pItem = pDir;

			strcpy(pDir->m_wfd.cFileName, _bstr_t(recordset->Fields->Item[_bstr_t("filename")]->Value));

			_makepath(pDir->m_pathName.GetBuffer(512), NULL, m_pathName, pDir->m_wfd.cFileName, NULL);
			pDir->m_pathName.ReleaseBuffer();

			dirs.Add(pDir);
		}
		else if (type == 2)	// File
		{
			CSiteFile* pFile = new CSiteFile;
			pItem = pFile;

			strcpy(pFile->m_wfd.cFileName, _bstr_t(recordset->Fields->Item[_bstr_t("filename")]->Value));
			pFile->m_wfd.nFileSizeLow = recordset->Fields->Item[_bstr_t("file_size")]->Value.lVal;
		}
		else
			ATLASSERT(0);

		if (pItem)
		{
			pItem->m_pWebSite = m_pWebSite;
			pItem->m_dbid = recordset->Fields->Item[_bstr_t("id")]->Value.lVal;
		//	pItem->m_name = pItem->m_wfd.cFileName;	// ??

			// lastWriteDate
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

void CSiteDir::ScanFTPFiles(BOOL bCheckExisting/* = FALSE*/)
{
	HINTERNET hFindFile;
	WIN32_FIND_DATA	wfd;

	TCHAR	search[MAX_PATH];
	wsprintf(search, "*.*", m_pathName);

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

	if ((hFindFile = FtpFindFirstFile(
		m_pWebSite->m_hInternetFtp,
		search,
		&wfd,
		INTERNET_FLAG_RELOAD,
		0/*dwContext*/)) != NULL/*INVALID_HANDLE_VALUE*/)
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

						_makepath(pDir->m_pathName.GetBuffer(512), NULL, m_pathName, wfd.cFileName, NULL);
						pDir->m_pathName.ReleaseBuffer();
//						pDir->m_name = wfd.cFileName;
						pDir->m_wfd = wfd;
						pDir->m_bFoundOnDisk = TRUE;

						AddChildTail(pDir);

						pDir->AddSiteItemToDatabase();
					}

				//	pDir->ScanFiles(bCheckExisting);
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
						}
					}
					else
					{
						CSiteFile* pFile = new CSiteFile;
						pFile->m_pWebSite = m_pWebSite;

						pFile->m_bFoundOnDisk = TRUE;
//						pFile->m_name = wfd.cFileName;	// ??
						pFile->m_wfd = wfd;

						AddChildTail(pFile);
					}
				}
			}
		}
		while (InternetFindNextFile(hFindFile, &wfd));

		InternetCloseHandle(hFindFile);
	}

//	DWORD lastError = GetLastError();
//	if (lastError) WinError(lastError);

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
			//	if (*pActive == pItem) *pActive = NULL;

				//pItem->RemoveFromDatabase();

				pItem->m_parent->m_childList.RemoveAt(pos2);
				delete pItem;
			}
		}
	}
}

void CSiteDir::ScanFiles(BOOL bCheckExisting/* = FALSE*/, BOOL bUpdateDB /* = FALSE */, CSiteItem** pActive/* = NULL*/)
{
	HANDLE hFindFile;
	WIN32_FIND_DATA	wfd;

	TCHAR	search[MAX_PATH];
	wsprintf(search, "%s\\*.*", m_pathName);

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

						_makepath(pDir->m_pathName.GetBuffer(512), NULL, m_pathName, wfd.cFileName, NULL);
						pDir->m_pathName.ReleaseBuffer();
						pDir->m_wfd = wfd;
						pDir->m_bFoundOnDisk = TRUE;

						AddChildTail(pDir);

						pDir->AddSiteItemToDatabase();
					}

					pDir->ScanFiles(bCheckExisting, bUpdateDB, pActive);
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
							if (bUpdateDB)
							{
								pFile->UpdateDatabase();
								pFile->UpdateOutLinks();
							}

							pFile->m_wfd = wfd;
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
			//	if (*pActive == pItem) *pActive = NULL;

				//pItem->RemoveFromDatabase();

				pItem->m_parent->m_childList.RemoveAt(pos2);
				delete pItem;
			}
		}
	}
}

DWORD __stdcall ChangeNotifyThread(LPVOID param)
{
	CoInitialize(NULL);

	CComQIPtr<IWebSite> site = (IWebSite*)param;

	CWebSite* pSite = ((CWebSite*)site.p);
	
	BSTR rootPath;
	site->get_rootPath(&rootPath);

	HANDLE m_hChangeHandle;

	m_hChangeHandle = FindFirstChangeNotification(_bstr_t(rootPath),
			TRUE,
			FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME |
			FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE
			);

	SysFreeString(rootPath);

	while (1)
	{
		DWORD nObject = MsgWaitForMultipleObjectsEx(
		  1,          // number of handles in handle array
		  &m_hChangeHandle,     // pointer to an object-handle array
		  INFINITE,  // time-out interval in milliseconds
		  QS_ALLEVENTS,      // type of input events to wait for
		  0         // wait flags
		);

		if (nObject == WAIT_OBJECT_0)
		{
			pSite->m_pRootDir->ScanFiles(TRUE, TRUE);
			pSite->Fire_FileTreeChanged();
		}
		else
		{
			break;
		}

		FindNextChangeNotification(m_hChangeHandle);
	}

	FindCloseChangeNotification(m_hChangeHandle);

	CoUninitialize();

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CWebSite

void CWebSite::FinalRelease()
{
	QuitFileThread();
}

void CWebSite::QuitFileThread()
{
	if (m_hChangeThread)
	{
		PostThreadMessage(m_dwChangeThreadID, WM_QUIT, 0, 0);
		WaitForSingleObject(m_hChangeThread, 10*1000);	// Wait 10 seconds for thread to finish

		m_dwChangeThreadID = 0L;
		m_hChangeThread = NULL;
	}
}

STDMETHODIMP CWebSite::get_rootPath(BSTR *pVal)
{
	*pVal = SysAllocString(m_rootPath);
	return S_OK;
}

STDMETHODIMP CWebSite::put_rootPath(BSTR newVal)
{
	ATLASSERT(0);
	return S_OK;
}

void CWebSite::CreateTable_websettings(ADOX::_CatalogPtr catalog)
{
	ADOX::_TablePtr table("ADOX.Table");

	table->ParentCatalog = catalog;
	table->Name = L"websettings";

	table->Columns->Append(L"homepage_fileid", ADOX::adInteger, 0);
//	table->Columns->Append(L"out_link_id", ADOX::adInteger, 0);

	catalog->Tables->Append(_variant_t((IDispatch *)table));
}

void CWebSite::CreateTable_files(ADOX::_CatalogPtr catalog)
{
	ADOX::_TablePtr table("ADOX.Table");

	table->ParentCatalog = catalog;
	table->Name = L"files";

	table->Columns->Append(L"id", ADOX::adInteger, 0);
	table->Columns->Item[_variant_t(L"id")]->Properties->Item[_variant_t(L"AutoIncrement")]->PutValue(VARIANT_TRUE);

	table->Columns->Append(L"parent_id", ADOX::adInteger, 0);
	table->Columns->Append(L"filename", ADOX::adVarWChar, 255);
	table->Columns->Append(L"type", ADOX::adInteger, 0);
	table->Columns->Append(L"file_size", ADOX::adInteger, 0);
	table->Columns->Append(L"file_date", ADOX::adDate, 0);
//    adDBDate = 133,

	ADOX::_IndexPtr idx(L"ADOX.Index");
	idx->Name = L"id_index";
	idx->Columns->Append(_bstr_t("id"), ADOX::adInteger, 0);
	idx->PrimaryKey = VARIANT_TRUE;
	idx->Unique = VARIANT_TRUE;
	table->Indexes->Append(_variant_t((IDispatch *)idx));

	catalog->Tables->Append(_variant_t((IDispatch *)table));
}

void CWebSite::CreateTable_links(ADOX::_CatalogPtr catalog)
{
	ADOX::_TablePtr table("ADOX.Table");

	table->ParentCatalog = catalog;
	table->Name = L"links";

	table->Columns->Append(L"file_id", ADOX::adInteger, 0);
	table->Columns->Append(L"out_link_id", ADOX::adInteger, 0);

	catalog->Tables->Append(_variant_t((IDispatch *)table));
}

void CWebSite::CreateTable_tasks(ADOX::_CatalogPtr catalog)
{
	ADOX::_TablePtr table("ADOX.Table");

	table->ParentCatalog = catalog;
	table->Name = L"tasks";

	table->Columns->Append(L"status", ADOX::adInteger, 0);
	table->Columns->Append(L"name", ADOX::adVarWChar, 255);
	table->Columns->Append(L"assoc_file_id", ADOX::adInteger, 0);
	table->Columns->Append(L"priority", ADOX::adInteger, 0);
	table->Columns->Append(L"descr", ADOX::adLongVarWChar, 0);

	catalog->Tables->Append(_variant_t((IDispatch *)table));
}

STDMETHODIMP CWebSite::LoadDocument(BSTR pathName, BOOL *success)
{
	ATLASSERT(m_pRootDir == NULL);

//
	CComQIPtr<IDOMDocument> document;
	document.CoCreateInstance(CLSID_DOMDocument);

	VARIANT_BOOL bsuccess;
	document->load(pathName, &bsuccess);
	if (bsuccess)
	{
		char dir[_MAX_PATH];
		char path[_MAX_PATH];
		char filename[_MAX_PATH];
		char ext[_MAX_PATH];
		_splitpath(_bstr_t(pathName), dir, path, filename, ext);

		TCHAR mdbfullpathname[260];
		_makepath(mdbfullpathname, dir, path, "site_data", "mdb");

		TCHAR rootpath[_MAX_PATH];
		_makepath(rootpath, dir, path, "root", NULL);

		m_rootPath = rootpath;

		// Open website database data
		if (m_siteDataConnection == NULL)
		{
			try
			{
				swprintf(m_connstr, L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%S", mdbfullpathname);

				m_siteDataConnection.CreateInstance(__uuidof(ADODB::Connection));
				m_siteDataConnection->Open(m_connstr, "", "", ADODB::adConnectUnspecified);
			}
			catch (_com_error &e)
			{
				DbError(e);
			}
		}

		GetHomepageFileIdFromDB();	// ReadSettings

		m_pRootDir = new CSiteDir;
		m_pRootDir->m_pWebSite = this;
		m_pRootDir->m_pathName = CUString((BSTR)m_rootPath);

		m_pRootDir->BuildFromDatabase();
		m_pRootDir->ScanFiles(TRUE, FALSE);

	//	m_pRootDir->UpdateOutLinks();

		CComQIPtr<IWebSite> site = this;

		m_hChangeThread = CreateThread(NULL, 0, ChangeNotifyThread, site.p, 0, &m_dwChangeThreadID);

	// TODO Fire UI Update event

		ShowViews();
	}

	return S_OK;
}

STDMETHODIMP CWebSite::ShowViews()
{
	CComQIPtr<IWebEditorFrame> frame;
	gApp->get_frame(&frame);

	CComQIPtr<IUIContextManager> uiManager;
	gApp->get_uiManager(&uiManager);

	{
		CComQIPtr<IUIMDIChild> child;
		child.CoCreateInstance(CLSID_UIMDIChild);

		// Files
		{
			CComQIPtr<ISiteFilesView> filesView;
			filesView.CoCreateInstance(CLSID_SiteFilesView);
			filesView->Create(uiManager, L"Files", (IID*)&CLSID_SiteFilesView, NULL);
			filesView->put_webSiteDocument(this);
			child->AddView(filesView, NULL);
		}

		// Links
		{
			CComQIPtr<ISiteLinksView> linksView;
			linksView.CoCreateInstance(CLSID_SiteLinksView);
			linksView->Create(uiManager, L"Links", (IID*)&CLSID_SiteFilesView, NULL);
			linksView->put_document(this);
			child->AddView(linksView, NULL);
		}

		// FTP
		{
			CComQIPtr<ISiteFTPView> ftpView;
			ftpView.CoCreateInstance(CLSID_SiteFTPView);
			ftpView->Create(uiManager, L"FTP", (IID*)&CLSID_SiteFilesView, NULL);
			ftpView->put_document(this);
			child->AddView(ftpView, NULL);
		}

		child->CreateMDIChild(frame, NULL);
		child.Detach();	// Keep it open
	}

	return S_OK;
}

STDMETHODIMP CWebSite::get_ftpServerName(BSTR *pVal)
{
	*pVal = SysAllocString(m_ftpServerName);
	return S_OK;
}

STDMETHODIMP CWebSite::put_ftpServerName(BSTR newVal)
{
	m_ftpServerName = newVal;
	return S_OK;
}

STDMETHODIMP CWebSite::get_ftpDirectory(BSTR *pVal)
{
	*pVal = SysAllocString(m_ftpDirectory);
	return S_OK;
}

STDMETHODIMP CWebSite::put_ftpDirectory(BSTR newVal)
{
	m_ftpDirectory = newVal;
	return S_OK;
}

STDMETHODIMP CWebSite::get_ftpUsername(BSTR *pVal)
{
	*pVal = SysAllocString(m_ftpUsername);
	return S_OK;
}

STDMETHODIMP CWebSite::put_ftpUsername(BSTR newVal)
{
	m_ftpUsername = newVal;
	return S_OK;
}

STDMETHODIMP CWebSite::get_ftpPassword(BSTR *pVal)
{
	*pVal = SysAllocString(m_ftpPassword);
	return S_OK;
}

STDMETHODIMP CWebSite::put_ftpPassword(BSTR newVal)
{
	m_ftpPassword = newVal;
	return S_OK;
}

#include "IIDCommands.h"

BEGIN_CMD_MAP(CWebSite)
	CMD_HANDLER(&ID_SITE_RESCAN, OnRescan)

	CMD_HANDLER(&ID_SITE_FTP_CONNECT, OnFTPConnect)
	CMD_HANDLER(&ID_SITE_FTP_DISCONNECT, OnFTPDisconnect)
END_CMD_MAP()

void CWebSite::OnFTPConnect(GUID* iid)
{
	if (!m_pFTPRootDir)
	{
		m_ftpServerName = L"ftp.bredband.no";
		m_ftpUsername = L"sigler";
		m_ftpPassword = L"9pmbi238";
		
		m_hInternet = InternetOpen(
			"WebEditor",//LPCTSTR lpszAgent,
			INTERNET_OPEN_TYPE_DIRECT,//DWORD dwAccessType,
			NULL,//LPCTSTR lpszProxyName,
			NULL,//LPCTSTR lpszProxyBypass,
			0//INTERNET_FLAG_ASYNC,//DWORD dwFlags
			);
		
		if (m_hInternet)
		{
			m_hInternetFtp = InternetConnect(
				m_hInternet,
				m_ftpServerName,
				21,//INTERNET_PORT nServerPort,
				m_ftpUsername,//LPCTSTR lpszUsername,
				m_ftpPassword,//LPCTSTR lpszPassword,
				INTERNET_SERVICE_FTP,//DWORD dwService,
				0,//INTERNET_FLAG_PASSIVE,//DWORD dwFlags,
				(DWORD)this// dwContext
				);
			if (m_hInternetFtp)
			{
				m_pFTPRootDir = new CSiteDir;
				m_pFTPRootDir->m_pWebSite = this;

				m_pFTPRootDir->ScanFTPFiles(FALSE);
			}
		}
	}
}

void CWebSite::OnFTPDisconnect(GUID* iid)
{
}

void CWebSite::OnRescan(GUID* iid)
{
	ATLASSERT(0);
	try
	{
		WCHAR sql[256];
		swprintf(sql, L"INSERT INTO files (filename) VALUES ('%s')", L"test.htm");

		_variant_t	va;
		m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);

		m_siteDataConnection->Close();
	}
	catch (_com_error &e)
   {
      _bstr_t bstrSource(e.Source());
      _bstr_t bstrDescription(e.Description());
      
		CUString msg;
      msg.Format("\n\tSource :  %s \n\tdescription : %s \n ",(LPCSTR)bstrSource,(LPCSTR)bstrDescription);

		MessageBox(NULL, msg, "", MB_OK);
   }
}

void CWebSite::GetHomepageFileIdFromDB()
{
	try
	{
		ADODB::_RecordsetPtr recordset("ADODB.RecordSet");
		recordset->Open(
			L"websettings",
			_variant_t(m_connstr),
			ADODB::adOpenForwardOnly, ADODB::adLockReadOnly, ADODB::adCmdTable);

		m_homepageFileID = recordset->Fields->Item[_variant_t(L"homepage_fileid")]->Value.lVal;

		recordset->Close();
	}
	catch(_com_error e)
	{
		DbError(e);
	}
}

STDMETHODIMP CWebSite::SetHomepageFileId(unsigned long file_id)
{
	try
	{
		ADODB::_RecordsetPtr recordset("ADODB.RecordSet");
		recordset->Open(
			L"websettings",
			_variant_t(m_connstr),
			ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);

		recordset->Fields->Item[_variant_t(L"homepage_fileid")]->Value = (long)file_id;

		recordset->Update();
		recordset->Close();

		m_homepageFileID = file_id;
	}
	catch(_com_error e)
	{
		DbError(e);
	}

	return S_OK;
}

STDMETHODIMP CWebSite::GetHomepageFileId(unsigned long *file_id)
{
	if (file_id == NULL) return E_POINTER;
	*file_id = m_homepageFileID;
	return S_OK;
}
