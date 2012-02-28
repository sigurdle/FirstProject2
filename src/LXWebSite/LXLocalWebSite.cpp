// LXLocalWebSite.cpp : Implementation of CLXLocalWebSite
#include "stdafx.h"
#include "LXWebSite.h"
//#include "LXWebSite2.h"
#include "LXLocalWebSite.h"

#include <direct.h>

#import "..\LHTML\LHTML.tlb" no_namespace, named_guids, raw_interfaces_only

/////////////////////////////////////////////////////////////////////////////
// CLXLocalWebSite

void test()
{
/*		CComQIPtr<IWSSrv> webSite;
		webSite.CoCreateInstance(CLSID_WSSrv);
		webSite->NewDocument(L"");
		PostQuitMessage(0);
*/

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		DispatchMessage(&msg);
		
		if (msg.message == WM_USER+1024)
		{
			//CSiteDir* pDir = (CSiteDir*)msg.lParam;
			//pDir->ScanFiles(TRUE, TRUE, FALSE);
		}
	}
}

/*
{
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
      
	CUString msg;
	msg.Format("\n\tSource :  %s \n\tdescription : %s \n ",(LPCSTR)bstrSource,(LPCSTR)bstrDescription);

	MessageBox(NULL, msg, "WebEditorServer", MB_OK);
}
*/

CString CLXLocalWebSite::CSiteItem::GetFullDisplayName()
{
	CString str = m_wfd.cFileName;

	CSiteDir* pDir = m_parent;
	while (pDir)
	{
		str = pDir->m_wfd.cFileName + CString("/") + str;
		pDir = pDir->m_parent;
	}
	return str;
}

CLXLocalWebSite::CSiteItem* CLXLocalWebSite::CSiteDir::FileExists(LPCTSTR pathname, int type)
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

void CLXLocalWebSite::CSiteDir::BuildFromDatabase()
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

			_makepath(pDir->m_fullPathName.GetBuffer(512), NULL, m_fullPathName, pDir->m_wfd.cFileName, NULL);
			pDir->m_fullPathName.ReleaseBuffer();

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

void CLXLocalWebSite::CSiteDir::ScanFiles(BOOL bCheckExisting/* = FALSE*/, BOOL bUpdateDB /* = FALSE */, CSiteItem** pActive/* = NULL*/)
{
	HANDLE hFindFile;
	WIN32_FIND_DATA	wfd;

	TCHAR	search[MAX_PATH];
	wsprintf(search, "%s\\*.*", m_fullPathName);

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

						_makepath(pDir->m_fullPathName.GetBuffer(512), NULL, m_fullPathName, wfd.cFileName, NULL);
						pDir->m_fullPathName.ReleaseBuffer();

						pDir->m_wfd = wfd;
						pDir->m_bFoundOnDisk = TRUE;

						AddChildTail(pDir);

						pDir->AddSiteItemToDatabase();
						pDir->UpdateOutLinks();
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

						_makepath(pFile->m_fullPathName.GetBuffer(512), NULL, m_fullPathName, wfd.cFileName, NULL);
						pFile->m_fullPathName.ReleaseBuffer();
						pFile->m_bFoundOnDisk = TRUE;
						pFile->m_wfd = wfd;

						AddChildTail(pFile);

						pFile->AddSiteItemToDatabase();
						pFile->UpdateOutLinks();
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

				pItem->RemoveSiteItemFromDatabase();

				pItem->m_parent->m_childList.RemoveAt(pos2);
				delete pItem;
			}
		}
	}
}

void CollectAnchors(ILDOMElement* element, CArray<CAdapt<CComBSTR>, CAdapt<CComBSTR> >& list)
{
	CComBSTR namespaceURI;
	element->get_namespaceURI(&namespaceURI);

	CComBSTR tagName;
	element->get_localName(&tagName);
	if (tagName.Length()==0)
	{
		tagName.Empty();
		element->get_tagName(&tagName);
	}

	CComBSTR href;

	if (namespaceURI.Length() && !wcscmp(namespaceURI, L"http://www.w3.org/2000/svg"))
	{
		if (!wcscmp(tagName, L"a"))
		{
			element->getAttributeNS(L"http://www.w3.org/1999/xlink", L"href", &href);
		}
	}
	else if (namespaceURI.Length() && !wcscmp(namespaceURI, L"http://www.w3.org/1999/xhtml"))
	{
		if (!wcscmp(tagName, L"a"))
		{
			element->getAttribute(L"href", &href);
		}
	}

	if (href.Length())
	{
		list.Add(href);
	}

	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			CollectAnchors(element, list);
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
}

HRESULT CLXLocalWebSite::CSiteFile::UpdateOutLinks()
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
		return E_FAIL;//DbError(e);
	}

	TCHAR ext[_MAX_EXT];
	_splitpath(m_wfd.cFileName, NULL, NULL, NULL, ext);

	/*
	if (!stricmp(ext, ".htm") ||
		!stricmp(ext, ".html") ||
		!stricmp(ext, ".asp") ||
		!stricmp(ext, ".svg"))
		*/
	{
		CSiteDir* pDir = (CSiteDir*)m_parent;

		CUString pathName = GetFullPathName();

		CComPtr<ILDOMBuilder> builder;
		if (SUCCEEDED(builder.CoCreateInstance(CLSID_LDOMBuilder)))
		{
			CComPtr<ILDOMDocument> document;
			builder->parseURI(_bstr_t(pathName), &document);

			if (document)
			{
				{ // Links
					CComPtr<ILDOMElement> documentElement;
					document->get_documentElement(&documentElement);

					if (documentElement)
					{
						CArray<CAdapt<CComBSTR>,CAdapt<CComBSTR> > anchors;

						CollectAnchors(documentElement, anchors);

						for (int i = 0; i < anchors.GetSize(); i++)
						{
							CComBSTR href = anchors[i].m_T;

						//	TCHAR absurl[1024];
						//	DWORD dwLength = sizeof(absurl);

						//	InternetCombineUrl(_bstr_t(pathName), _bstr_t(href), absurl, &dwLength, 0);
							/*
							char oldcwd[_MAX_PATH];
							_getcwd(oldcwd, _MAX_PATH);

							chdir(pDir->m_fullPathName);
							char fullpath[_MAX_PATH];
							_fullpath(fullpath, href, _MAX_PATH);
							/

							chdir(oldcwd);
							*/

							TCHAR tabsDisplayPath[_MAX_PATH];
							_makepath(tabsDisplayPath, NULL, GetFullDisplayName(), _bstr_t(href), NULL);

							_bstr_t absDisplayPath = tabsDisplayPath;
							long dbid = m_pWebSite->GetPathFileNameID(absDisplayPath);

							//CSiteFile* pHrefFile = (CSiteFile*)m_pWebSite->m_pRootDir->FindFilePathName(absurl, 2);

							//if (pHrefFile)
							{
								try
								{
									WCHAR sql[256];
									swprintf(sql, L"INSERT INTO links (file_id, out_link_id, out_display_name) VALUES (%d, %d, '%s')", m_dbid, dbid, (BSTR)absDisplayPath);

									_variant_t va;
									m_pWebSite->m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);
								}
								catch (_com_error &e)
								{
									return E_FAIL;//DbError(e);
								}
							}
						}
					}
				}

			// DOM hierarchy
#if 0
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
						return E_FAIL;//DbError(e);
					}
				}
#endif
			}
		}
	}

#if 0	// Have this
	m_pWebSite->Fire_OutLinksChanged(m_dbid);
#endif

	return S_OK;
}

HRESULT CLXLocalWebSite::CSiteDir::UpdateOutLinks()
{
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CSiteItem* pItem = (CSiteItem*)m_childList.GetNext(pos);
		if (pItem->m_type == 2)
		{
			CSiteFile* pFile = (CSiteFile*)pItem;
			HRESULT hr = pFile->UpdateOutLinks();
		}
		else
		{
			CSiteDir* pDir = (CSiteDir*)pItem;
			HRESULT hr = pDir->UpdateOutLinks();
		}
	}

	return S_OK;
}

HRESULT CLXLocalWebSite::CSiteItem::AddSiteItemToDatabase()
{
	ATLASSERT(m_parent);

	try
	{
		{
			double lastWriteTime;
			SYSTEMTIME systime;
			FileTimeToSystemTime(&m_wfd.ftLastWriteTime, &systime);
			SystemTimeToVariantTime(&systime, &lastWriteTime);

			ADODB::_RecordsetPtr files("ADODB.RecordSet");
			files->Open(
				L"files",
				_variant_t((IDispatch*)m_pWebSite->m_siteDataConnection),
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

		CString fullDisplayName = GetFullDisplayName();
		m_pWebSite->Fire_FileChangeEvent(1, _bstr_t(fullDisplayName));
	}
	catch (_com_error &e)
	{
		//DbError(e);
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CLXLocalWebSite::CSiteItem::RemoveSiteItemFromDatabase()
{
	ATLASSERT(m_parent);

	try
	{
		WCHAR sql[256];
		swprintf(sql, L"DELETE FROM files WHERE id = %d", m_dbid);

		_variant_t	va;

		va.Clear();
		m_pWebSite->m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);

		m_pWebSite->Fire_FileChangeEvent(2, _bstr_t(GetFullDisplayName()));
	}
	catch (_com_error &e)
	{
		return E_FAIL;//DbError(e);
	}

	return S_OK;
}

HRESULT CLXLocalWebSite::CSiteItem::UpdateDatabase()
{
	ATLASSERT(m_parent);

	try
	{
		WCHAR sql[256];
		swprintf(sql, L"UPDATE files SET file_size = %d WHERE id = %d", m_wfd.nFileSizeLow, m_dbid);

		_variant_t	va;

		va.Clear();
		m_pWebSite->m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);

		m_pWebSite->Fire_FileChangeEvent(3, _bstr_t(GetFullDisplayName()));
	}
	catch (_com_error &e)
	{
		return E_FAIL;//DbError(e);
	}

	return S_OK;
}

DWORD __stdcall ChangeNotifyThread(LPVOID param)
{
	CoInitialize(NULL);

	CComQIPtr<ILXLocalWebSite> site = (ILXLocalWebSite*)param;

	CLXLocalWebSite* pSite = ((CLXLocalWebSite*)site.p);
	
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
			pSite->m_cwnd.PostMessage(WM_USER+100, 0, 0);
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
// CLXLocalWebSite

int CLXLocalWebSite::FinalConstruct()
{
	m_cwnd.Create(NULL, CRect(0,0,0,0), NULL, WS_POPUP);
	ATLASSERT(m_cwnd.m_hWnd);
	if (m_cwnd.m_hWnd == NULL)
		return E_FAIL;

	return 0;
}

void CLXLocalWebSite::FinalRelease()
{
	if (m_pRootDir)
	{
		delete m_pRootDir;
		m_pRootDir = NULL;
	}

	if (m_siteDataConnection)
	{
		m_siteDataConnection->Close();
		m_siteDataConnection = NULL;
	}

//	m_pUnkMarshaler.Release();
}

LRESULT CLXLocalWebSite::OnFileChange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_pRootDir->ScanFiles(TRUE, TRUE);
//	Fire_FileTreeChanged();

	return 0;
}

void CLXLocalWebSite::CreateTable_websettings(ADOX::_CatalogPtr catalog)
{
	ADOX::_TablePtr table("ADOX.Table");

	table->ParentCatalog = catalog;
	table->Name = L"websettings";

	table->Columns->Append(L"homepage_fileid", ADOX::adInteger, 0);
//	table->Columns->Append(L"out_link_id", ADOX::adInteger, 0);

	catalog->Tables->Append(_variant_t((IDispatch *)table));
}

void CLXLocalWebSite::CreateTable_files(ADOX::_CatalogPtr catalog)
{
	ADOX::_TablePtr table("ADOX.Table");

	table->ParentCatalog = catalog;
	table->Name = L"files";

	table->Columns->Append(L"id", ADOX::adInteger, 0);
	table->Columns->Item[L"id"]->Properties->Item[L"AutoIncrement"]->Value = _variant_t(VARIANT_TRUE, VT_BOOL);

	table->Columns->Append(L"parent_id", ADOX::adInteger, 0);
	table->Columns->Append(L"filename", ADOX::adVarWChar, 255);
	table->Columns->Append(L"type", ADOX::adInteger, 0);
	table->Columns->Append(L"file_size", ADOX::adInteger, 0);
	table->Columns->Append(L"file_date", ADOX::adDate, 0);

	ADOX::_IndexPtr idx(L"ADOX.Index");
	idx->Name = L"id_index";
	idx->Columns->Append(_bstr_t("id"), ADOX::adInteger, 0);
	idx->PrimaryKey = VARIANT_TRUE;
	idx->Unique = VARIANT_TRUE;
	table->Indexes->Append(_variant_t((IDispatch *)idx));

	catalog->Tables->Append(_variant_t((IDispatch *)table));
}

void CLXLocalWebSite::CreateTable_files_data(ADOX::_CatalogPtr catalog)
{
	ADOX::_TablePtr table("ADOX.Table");

	table->ParentCatalog = catalog;
	table->Name = L"files_data";

	table->Columns->Append(L"id", ADOX::adInteger, 0);
	table->Columns->Item[_variant_t(L"id")]->Properties->Item[_variant_t(L"AutoIncrement")]->Value = _variant_t(VARIANT_TRUE, VT_BOOL);

	table->Columns->Append(L"file_id", ADOX::adInteger, 0);
//	table->Columns->Append(L"filename", ADOX::adVarWChar, 255);
//	table->Columns->Append(L"type", ADOX::adInteger, 0);
	table->Columns->Append(L"file_size", ADOX::adInteger, 0);
	table->Columns->Append(L"file_date", ADOX::adDate, 0);
	table->Columns->Append(L"file_data", ADOX::adLongVarBinary, 0);
//    adDBDate = 133,

	/*
	ADOX::_IndexPtr idx(L"ADOX.Index");
	idx->Name = L"id_index";
	idx->Columns->Append(_bstr_t("id"), ADOX::adInteger, 0);
	idx->PrimaryKey = VARIANT_TRUE;
	idx->Unique = VARIANT_TRUE;
	table->Indexes->Append(_variant_t((IDispatch *)idx));
	*/

	catalog->Tables->Append(_variant_t((IDispatch *)table));
}

void CLXLocalWebSite::CreateTable_links(ADOX::_CatalogPtr catalog)
{
	ADOX::_TablePtr table("ADOX.Table");

	table->ParentCatalog = catalog;
	table->Name = L"links";

	table->Columns->Append(L"file_id", ADOX::adInteger, 0);
	table->Columns->Append(L"out_link_id", ADOX::adInteger, 0);

	catalog->Tables->Append(_variant_t((IDispatch *)table));
}

void CLXLocalWebSite::CreateTable_tasks(ADOX::_CatalogPtr catalog)
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

HRESULT CLXLocalWebSite::GetHomepageFileIdFromDB()
{
	try
	{
		ADODB::_RecordsetPtr recordset("ADODB.RecordSet");
		recordset->Open(
			_bstr_t(L"websettings"),
			_variant_t((IDispatch*)m_siteDataConnection),
			ADODB::adOpenForwardOnly, ADODB::adLockReadOnly, ADODB::adCmdTable);

		recordset->MoveFirst();

		m_homepageFileID = recordset->Fields->Item[_variant_t(L"homepage_fileid")]->Value.lVal;

		recordset->Close();
	}
	catch(_com_error &e)
	{
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CLXLocalWebSite::SetHomepageFileId(unsigned long file_id)
{
	try
	{
		ADODB::_RecordsetPtr recordset("ADODB.RecordSet");
		recordset->Open(
			L"websettings",
			_variant_t((IDispatch*)m_siteDataConnection),
			ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);

		recordset->Fields->Item[_variant_t(L"homepage_fileid")]->Value = (long)file_id;

		recordset->Update();
		recordset->Close();

		m_homepageFileID = file_id;
	}
	catch(_com_error &e)
	{
		ATLTRACE("Error SetHomepageFileId()\n");
	// TODO, better HRESULT
		return E_FAIL;
	}

	return S_OK;
}

long CLXLocalWebSite::GetFileNameID(long parent_id, BSTR filename)
{
	WCHAR sql[512];
	swprintf(sql, L"SELECT id FROM files WHERE parent_id = %d AND filename = '%s'", parent_id, filename);

	_variant_t va;
	ADODB::_RecordsetPtr rs = m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

	rs->MoveFirst();

	return rs->Fields->Item[_bstr_t(L"id")]->Value;
}

long CLXLocalWebSite::GetPathFileNameID(BSTR filePath)
{
	WCHAR pathBuffer[2048];
	wcscpy(pathBuffer, filePath);

	WCHAR* fileName = pathBuffer;
	DWORD file_id = 0;
	while (*fileName)
	{
		WCHAR* pathDel = wcschr(fileName, L'/');
		if (pathDel)
			*pathDel = L'\0';

		if (*fileName)
		{
			file_id = GetFileNameID(file_id, fileName);
		}

		if (pathDel == NULL) break;
		fileName = pathDel+1;
	}
	return file_id;
}

void CLXLocalWebSite::SetElementFromRecordset(ADODB::_RecordsetPtr recordset, ILDOMElement* element)
{
	long file_id = recordset->Fields->Item[_bstr_t("id")]->Value.lVal;

	BYTE type = recordset->Fields->Item[_bstr_t("type")]->Value.lVal;
	_bstr_t filename = recordset->Fields->Item[_bstr_t("filename")]->Value;

	element->setAttribute(L"type", _bstr_t(_variant_t((long)type)));
	element->setAttribute(L"filename", filename);
//	element->setAttribute(L"file_id", _bstr_t(_variant_t(file_id)));
	element->setAttribute(L"file_size", _bstr_t(_variant_t(recordset->Fields->Item[_bstr_t("file_size")]->Value.lVal)));
	element->setAttribute(L"publish", _bstr_t(_variant_t(recordset->Fields->Item[_bstr_t("publish")]->Value.lVal)));

	// lastWriteDate
	double lastWriteTime = recordset->Fields->Item[_bstr_t("file_date")]->Value;
	element->setAttribute(L"file_date", _bstr_t(_variant_t(lastWriteTime)));
	/*
	SYSTEMTIME systime;
	VariantTimeToSystemTime(lastWriteTime, &systime);
	SystemTimeToFileTime(&systime, &pItem->m_wfd.ftLastWriteTime);
	*/

	if (type == 1)
	{
		WCHAR sql[256];
		swprintf(sql, L"SELECT COUNT(*) AS c FROM files WHERE parent_id = %d", file_id);
		_variant_t va;
		ADODB::_RecordsetPtr rs = m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);
		element->setAttribute(L"c", _bstr_t(_variant_t((long)((rs->Fields->Item[_bstr_t(L"c")]->Value.lVal > 0L)? 1: 0))));
	}
}

STDMETHODIMP CLXLocalWebSite::GetItemAttributes(/*[in]*/ BSTR pathName, /*[out,retval]*/ BSTR* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	try
	{
		CComPtr<ILDOMDocument> xmldoc;
		HRESULT hr = xmldoc.CoCreateInstance(CLSID_LDOMDocument);
		if (FAILED(hr))
		{
			throw _com_error(hr);
		}

		long item_id = GetPathFileNameID(pathName);

		VARIANT_BOOL success;
		xmldoc->loadXML(L"<item/>", &success);

		CComPtr<ILDOMElement> documentElement;
		xmldoc->get_documentElement(&documentElement);

		WCHAR sql[256];
		swprintf(sql, L"SELECT id,filename,type,file_size,file_date,publish FROM files WHERE id = %d", item_id);
		_variant_t va;
		ADODB::_RecordsetPtr recordset = m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);

		SetElementFromRecordset(recordset, documentElement);

		xmldoc->saveXML(_variant_t(), pVal);
	}
	catch(_com_error& e)
	{
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CLXLocalWebSite::GetFolderList(/*[in]*/ BSTR pathName, /*[out,retval]*/ BSTR* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	try
	{
		CComPtr<ILDOMDocument> xmldoc;
		HRESULT hr = xmldoc.CoCreateInstance(CLSID_LDOMDocument);
		if (FAILED(hr))
		{
			throw _com_error(hr);
		}

		long folder_id = GetPathFileNameID(pathName);

		VARIANT_BOOL success;
		xmldoc->loadXML(L"<directory/>", &success);

		CComPtr<ILDOMElement> documentElement;
		xmldoc->get_documentElement(&documentElement);

		WCHAR sql[256];
		swprintf(sql, L"SELECT id,filename,type,file_size,file_date,publish FROM files WHERE parent_id = %d", folder_id);
		_variant_t va;
		ADODB::_RecordsetPtr recordset = m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);

		while (recordset->EndOfFile == false)
		{
			CComPtr<ILDOMElement> element;
			xmldoc->createElement(L"item", &element);
			if (element)
			{
				SetElementFromRecordset(recordset, element);
			}

			documentElement->appendChild(element, NULL);

			recordset->MoveNext();
		}

		xmldoc->saveXML(_variant_t(), pVal);
	}
	catch(_com_error& e)
	{
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CLXLocalWebSite::GetFileMoniker(/*[in]*/ BSTR relDisplayName, /*[out,retval]*/ IMoniker* *pVal)
{
	try
	{
//		long item_id = GetPathFileNameID(pathName);

		WCHAR* p = relDisplayName;
		WCHAR relpath[512];
		int n = 0;
		while (*p)
		{
			if (*p == L'/')
				relpath[n] = L'\\';
			else
				relpath[n] = *p;

			n++;
			p++;
		}
		relpath[n] = 0;

		TCHAR url[512];
		strcpy(url, m_rootPath);

		PathAppend(url, _bstr_t(relpath));

		//DWORD dwLength = sizeof(absurl);	// bytes (not characters)
		//InternetCombineUrl(m_rootPath, _bstr_t(pathName), absurl, &dwLength, 0);

		//TCHAR fullPathName[_MAX_PATH];
		//_makepath(fullPathName, NULL, m_rootPath, _bstr_t(pathName), NULL);

		return CreateURLMoniker(NULL, _bstr_t(url), pVal);
	}
	catch(_com_error& e)
	{
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CLXLocalWebSite::GetHomepageFileId(unsigned long *file_id)
{
	if (file_id == NULL) return E_POINTER;
	*file_id = m_homepageFileID;
	return S_OK;
}

STDMETHODIMP CLXLocalWebSite::LoadDocument(BSTR pathName, VARIANT_BOOL *success)
{
	if (success == NULL) return E_POINTER;

	ATLASSERT(m_pRootDir == NULL);

//
	CComQIPtr<ILDOMDocument> document;
	document.CoCreateInstance(CLSID_LDOMDocument);

	VARIANT_BOOL bsuccess;
	document->load(_bstr_t(pathName), &bsuccess);
	if (bsuccess)
	{
		TCHAR drive[_MAX_DRIVE];
		TCHAR dir[_MAX_DIR];
		TCHAR filename[_MAX_FNAME];
		TCHAR ext[_MAX_EXT];
		_splitpath(_bstr_t(pathName), drive, dir, filename, ext);

		TCHAR mdbfullpathname[_MAX_PATH];
		_makepath(mdbfullpathname, drive, dir, "site_data", "mdb");

		TCHAR rootpath[_MAX_PATH];
		_makepath(rootpath, drive, dir, "root", NULL);

		_mkdir(rootpath);	// Make sure it exists

		m_rootPath = rootpath;

		// Open website database data
		if (m_siteDataConnection == NULL)
		{
			try
			{
				swprintf(m_connstr, L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%S", mdbfullpathname);

				m_siteDataConnection.CreateInstance(__uuidof(ADODB::Connection));
				m_siteDataConnection->Open(m_connstr, "", "", /*ADODB::adAsyncConnect*/ADODB::adConnectUnspecified);
			}
			catch (_com_error &e)
			{
				ATLTRACE("Error WebSite Load()\n");
			//	DbError(e);
			}
		}

		GetHomepageFileIdFromDB();	// ReadSettings

		{
			m_pRootDir = new CSiteDir;
			m_pRootDir->m_pWebSite = this;
			m_pRootDir->m_fullPathName = CString((BSTR)m_rootPath);
			//strcpy(m_pRootDir->m_wfd.cFileName, m_rootPath);

			m_pRootDir->BuildFromDatabase();
			m_pRootDir->ScanFiles(TRUE, FALSE);

		//	m_pRootDir->UpdateOutLinks();

			CComQIPtr<ILXLocalWebSite> site = this;

			m_hChangeThread = CreateThread(NULL, 0, ChangeNotifyThread, site.p, 0, &m_dwChangeThreadID);
		}

/*
		m_pRootDir = new CSiteDir;
		m_pRootDir->m_pWebSite = this;
		strcpy(m_pRootDir->m_wfd.cFileName, CUString((BSTR)m_rootPath));

		m_pRootDir->BuildFromDatabase();
*/
/*
		m_rsFiles.CreateInstance(L"ADODB.RecordSet");
		m_rsFiles->Open(
			_bstr_t(L"files"),
			_variant_t(m_connstr),
			ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);
*/
//		m_pRootDir->ScanFiles(TRUE, FALSE, TRUE, NULL);
/*
		m_rsFiles->UpdateBatch(ADODB::adAffectAll);
		m_rsFiles.Release();
*/
//		m_pRootDir->ListenToChanges();

		*success = VARIANT_TRUE;
#if 0
	//	m_pRootDir->UpdateOutLinks();

		CComQIPtr<IWebSite> site = this;

		m_hChangeThread = CreateThread(NULL, 0, ChangeNotifyThread, site.p, 0, &m_dwChangeThreadID);

	// TODO Fire UI Update event

		ShowViews();
#endif
	}

	return S_OK;
}

STDMETHODIMP CLXLocalWebSite::NewDocument(BSTR pathName, BSTR siteName)
{
	try
	{
		TCHAR fullpath[512];
		_makepath(fullpath, NULL, _bstr_t(pathName), _bstr_t(siteName), NULL);

		mkdir(fullpath);
		//DeleteFile("c:\\MySite2\\site_data.mdb");

		{
			TCHAR xmlfilepath[512];
			_makepath(xmlfilepath, NULL, fullpath, _bstr_t(siteName), _T(".lxsite"));

			CComPtr<ILDOMDocument> document;
			document.CoCreateInstance(CLSID_LDOMDocument);
			VARIANT_BOOL bsuccess;
			document->loadXML(_bstr_t(L"<site/>"), &bsuccess);
			document->save(_bstr_t(xmlfilepath), &bsuccess);
		}

		TCHAR dbfilepath[512];
		_makepath(dbfilepath, NULL, fullpath, _T("site_data.mdb"), NULL);

		swprintf(m_connstr, L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%S", dbfilepath);

		ADOX::_CatalogPtr catalog("ADOX.Catalog");
		ATLASSERT(catalog != NULL);
		//catalog->

		catalog->Create(m_connstr);

		ADODB::_ConnectionPtr conn = catalog->GetActiveConnection();
		long attrs = conn->Attributes;

//		conn->BeginTrans();

		CreateTable_websettings(catalog);
		CreateTable_files(catalog);
		CreateTable_files_data(catalog);
		CreateTable_links(catalog);
		CreateTable_tasks(catalog);

//		conn->CommitTrans();

	// Fill database with initial values
		m_siteDataConnection = conn;
	}
	catch (_com_error &e)
   {
		//DbError(e);
		return E_FAIL;
   }

//	try
	{
//		int level = m_siteDataConnection->BeginTrans();
//		ATLASSERT(level == 1);

		if (TRUE)
		{
			ADODB::_RecordsetPtr recordset("ADODB.RecordSet");
			recordset->Open(
				_bstr_t(L"websettings"),
				_variant_t((IDispatch*)m_siteDataConnection),
				ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);

			recordset->AddNew();

			recordset->Fields->Item[_variant_t(L"homepage_fileid")]->Value = (long)0;

			recordset->Update();
		}
		else
		{
			WCHAR sql[256];
			swprintf(sql, L"INSERT INTO websettings (homepage_fileid) VALUES (0);");
			_variant_t	va;
			m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);
			//recordset->Close();
		}
	}
/*	catch (_com_error &e)
   {
		MessageBox(NULL, "Error Set WebSite Settings", "WebEditorServer", MB_OK);
		DbError(e);
   }
*/

//	GetHomepageFileIdFromDB();

#if 0	// ???
	VARIANT_BOOL bsuccess;

	CComQIPtr<ILDOMDocument> document;
	document.CoCreateInstance(CLSID_LDOMDocument);
//	document.CoCreateInstance(L"LDOM.LDOMDocument");
	if (document)
	{
		document->put_async(VARIANT_FALSE);
		document->loadXML(_bstr_t(L"<?xml version=\"1.0\" ?><site></site>"), &bsuccess);
		document->save(_bstr_t(L"c:\\MySite2\\MySite2.site"), &bsuccess);

		return LoadDocument(L"c:\\MySite2\\MySite2.site", &bsuccess);
	}
	else
		return E_FAIL;
#endif

	return S_OK;
}

STDMETHODIMP CLXLocalWebSite::GetDBConnection(IDispatch **pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = m_siteDataConnection;
	(*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CLXLocalWebSite::get_rootPath(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = SysAllocString(m_rootPath);
	return S_OK;
}

/*
 Saves a file from a client to the database
 */

STDMETHODIMP CLXLocalWebSite::SaveArrayAsFile(unsigned long folder_id, BSTR fileName, SAFEARRAY* dataArray, BSTR user, DWORD* pfile_id, VARIANT_BOOL* pSuccess)
{
	if (pSuccess == NULL) return E_POINTER;
	
	*pSuccess = VARIANT_FALSE;
	if (pfile_id) *pfile_id = 0;

	SYSTEMTIME systime;
	GetSystemTime(&systime);
	double lastWriteTime;
	SystemTimeToVariantTime(&systime, &lastWriteTime);

//	char* data;
	DWORD file_size = dataArray->rgsabound[0].cElements;
//	HRESULT hr = SafeArrayAccessData(dataArray, (void**)&data);
//	if (SUCCEEDED(hr))
	{
		long file_id;

		try
		{
			{
				ADODB::_RecordsetPtr rs(L"ADODB.RecordSet");
				rs->Open(
					_bstr_t(L"files"),
					_variant_t((IDispatch*)m_siteDataConnection),
					ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);

				rs->AddNew();
				rs->Fields->Item[_bstr_t(L"parent_id")]->Value = (long)folder_id;
				rs->Fields->Item[_bstr_t(L"type")]->Value = (long)2;
				rs->Fields->Item[_bstr_t(L"filename")]->Value = fileName;
				rs->Fields->Item[_bstr_t(L"file_size")]->Value = (long)file_size;
				rs->Fields->Item[_bstr_t(L"file_date")]->Value = (double)lastWriteTime;

				rs->Update();

				file_id = rs->Fields->Item[_bstr_t(L"id")]->Value.lVal;
			}

			{
				ADODB::_RecordsetPtr rs(L"ADODB.RecordSet");
				rs->Open(
					_bstr_t(L"files_data"),
					_variant_t((IDispatch*)m_siteDataConnection),
					ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);

				rs->AddNew();
				rs->Fields->Item[_bstr_t(L"file_id")]->Value = (long)file_id;
				rs->Fields->Item[_bstr_t(L"file_size")]->Value = (long)file_size;
				rs->Fields->Item[_bstr_t(L"file_date")]->Value = (double)lastWriteTime;

				_variant_t varr;
				varr.vt = VT_ARRAY | VT_UI1;
				varr.parray = dataArray;
				rs->Fields->Item[_bstr_t(L"file_data")]->AppendChunk(varr);

				rs->Update();
			}
		}
		catch(_com_error &e)
		{
			ATLTRACE("Error GetDisplayName()\n");
			return E_FAIL;
		}

//		SafeArrayUnaccessData(dataArray);

		Fire_FileUpdate(folder_id, file_id, 1);

		*pSuccess = VARIANT_TRUE;
	}

	return S_OK;
}

STDMETHODIMP CLXLocalWebSite::OpenFileAsArray(unsigned long file_id, SAFEARRAY** dataArray)
{
	if (dataArray == NULL) return E_POINTER;

	*dataArray = NULL;

	try
	{
		WCHAR sql[512];
		swprintf(sql, L"SELECT file_size,file_data FROM files_data WHERE file_id = %d", file_id);

		_variant_t va;
		ADODB::_RecordsetPtr rs = m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		rs->MoveFirst();

		long file_size = rs->Fields->Item[_bstr_t(L"file_size")]->Value;

		//*dataArray = SafeArrayCreateVector(VT_UI1, 0, file_size);
		_variant_t varr = rs->Fields->Item[_bstr_t(L"file_data")]->GetChunk(file_size);
		*dataArray = varr.parray;
		varr.Detach();////(*dataArray)->pvData
	}
	catch(_com_error &e)
	{
		ATLTRACE("Error OpenFileAsArray()\n");
		return E_FAIL;
	}

	return S_OK;
}

_bstr_t CLXLocalWebSite::GetFolderDisplayPathRecursive(DWORD folder_id, WCHAR* pathDelimiter)
{
	_bstr_t name = L"";

	if (folder_id)
	{
		try
		{
			WCHAR sql[512];
			swprintf(sql, L"SELECT parent_id, filename FROM files WHERE id = %d", folder_id);

			_variant_t va;
			ADODB::_RecordsetPtr rs = m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

			rs->MoveFirst();

			long parent_id = rs->Fields->Item[_bstr_t(L"parent_id")]->Value;
			_bstr_t filename = rs->Fields->Item[_bstr_t(L"filename")]->Value;
			_bstr_t parentname = GetFolderDisplayPathRecursive(parent_id, pathDelimiter);

			name = parentname + filename + pathDelimiter;
		}
		catch(_com_error &e)
		{
			ATLTRACE("Error GetDisplayName()\n");
			return E_FAIL;
		}
	}
	else
	{
		name = pathDelimiter;
	}

	return name;
}

STDMETHODIMP CLXLocalWebSite::GetFolderDisplayPath(DWORD folder_id, BSTR *displayName)
{
	if (displayName == NULL) return E_POINTER;

	_bstr_t name = GetFolderDisplayPathRecursive(folder_id, L"/");
	*displayName = SysAllocString(name);

	return S_OK;
}

STDMETHODIMP CLXLocalWebSite::GetParentFolderId(DWORD folder_id, DWORD *pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = 0;

	try
	{
		WCHAR sql[512];
		swprintf(sql, L"SELECT parent_id FROM files WHERE id = %d", folder_id);

		_variant_t va;
		ADODB::_RecordsetPtr rs = m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		rs->MoveFirst();

		*pVal = (long)rs->Fields->Item[_bstr_t(L"parent_id")]->Value;
	}
	catch(_com_error &e)
	{
		ATLTRACE("Error GetParentFolderId()\n");
	// TODO, better HRESULT
		return E_FAIL;
	}

	return S_OK;
}

DWORD CLXLocalWebSite::AddNewFile(DWORD parent_id, long type, BSTR filename, DWORD file_size, double file_date)
{
	ADODB::_RecordsetPtr files(L"ADODB.RecordSet");
	files->Open(
		_bstr_t(L"files"),
		_variant_t((IDispatch*)m_siteDataConnection),
		ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);

	files->AddNew();
	files->Fields->Item[_bstr_t(L"parent_id")]->Value = (long)parent_id;
	files->Fields->Item[_bstr_t(L"type")]->Value = type;
	files->Fields->Item[_bstr_t(L"filename")]->Value = filename;
	files->Fields->Item[_bstr_t(L"file_size")]->Value = (long)file_size;
	files->Fields->Item[_bstr_t(L"file_date")]->Value = (double)file_date;

	files->Update();

	return (long)files->Fields->Item[_bstr_t(L"id")]->Value.lVal;
}

STDMETHODIMP CLXLocalWebSite::FindOrCreateFolder(DWORD parent_id, BSTR name, BSTR user, DWORD *pfolder_id)
{
	if (pfolder_id == NULL) return E_POINTER;
	*pfolder_id = 0L;

	try
	{
		WCHAR sql[512];
		swprintf(sql, L"SELECT id FROM files WHERE (parent_id = %d AND filename = '%s')", parent_id, name);

		_variant_t va;
		ADODB::_RecordsetPtr rs = m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		if (rs->EndOfFile == false)
		{
			*pfolder_id = (long)rs->Fields->Item[_bstr_t(L"id")]->Value;
		}
		else
		{
			SYSTEMTIME systime;
			GetSystemTime(&systime);
			double lastWriteTime;
			SystemTimeToVariantTime(&systime, &lastWriteTime);

			DWORD id = AddNewFile(parent_id, 1, name, 0, lastWriteTime);

			Fire_FileUpdate(parent_id, id, 1);

			*pfolder_id = id;
		}
	}
	catch(_com_error &e)
	{
		ATLTRACE("Error FindOrCreateFolder()\n");
	// TODO, better HRESULT
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CLXLocalWebSite::CreateFolder(DWORD parent_id, BSTR name, BSTR user, DWORD *pfolder_id)
{
	if (pfolder_id == NULL) return E_POINTER;
	*pfolder_id = 0L;

	try
	{
		WCHAR sql[512];
		swprintf(sql, L"SELECT id FROM files WHERE (parent_id = %d AND filename = '%s')", parent_id, name);

		_variant_t va;
		ADODB::_RecordsetPtr rs = m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		if (rs->EndOfFile == false)
		{
			*pfolder_id = 0L;	// Failed
		}
		else
		{
			SYSTEMTIME systime;
			GetSystemTime(&systime);
			double lastWriteTime;
			SystemTimeToVariantTime(&systime, &lastWriteTime);

			DWORD id = AddNewFile(parent_id, 1, name, 0, lastWriteTime);

			Fire_FileUpdate(parent_id, id, 1);

			*pfolder_id = id;
		}
	}
	catch(_com_error &e)
	{
		// TODO, better HRESULT
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CLXLocalWebSite::RemoveFileFromDatabase(DWORD parent_id, DWORD id)
{
	WCHAR sql[256];
	_variant_t va;

	try
	{
		// Delete children
		swprintf(sql, L"SELECT id FROM files WHERE parent_id = %d", id);

		va.Clear();
		ADODB::_RecordsetPtr rs = m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);
		while (rs->EndOfFile == false)
		{
			long fileid = rs->Fields->Item[_bstr_t(L"id")]->Value;

			RemoveFileFromDatabase(id, fileid);	// Recurse

			rs->MoveNext();
		}

	// Delete this
		swprintf(sql, L"DELETE FROM files WHERE id = %d", id);
		va.Clear();
		m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		swprintf(sql, L"DELETE FROM files_data WHERE file_id = %d", id);
		va.Clear();
		m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);
	}
	catch (_com_error &e)
	{
		// TODO, better HRESULT
		return E_FAIL;
	}

	Fire_FileUpdate(parent_id, id, 2);

	return S_OK;
}

STDMETHODIMP CLXLocalWebSite::DeleteFilePermanently(unsigned long file_id, VARIANT_BOOL *pSuccess)
{
	if (pSuccess == NULL) return E_POINTER;

	WCHAR sql[512];
	swprintf(sql, L"SELECT parent_id FROM files WHERE id = %d", file_id);

	_variant_t va;
	ADODB::_RecordsetPtr rs = m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);
	if (rs->EndOfFile == false)
	{
		long parent_id = rs->Fields->Item[_bstr_t(L"parent_id")]->Value;

		HRESULT hr = RemoveFileFromDatabase(parent_id, file_id);
		if (SUCCEEDED(hr))
			*pSuccess = VARIANT_TRUE;
		else
			*pSuccess = VARIANT_FALSE;
	}
	else
	{
		*pSuccess = VARIANT_FALSE;
	}

	return S_OK;
}

BOOL ValidateFileName(BSTR filename)
{
	if (filename == NULL) return FALSE;

	int len = wcslen(filename);

	if ((len == 0) || (len > 255))
		return FALSE;

	WCHAR* p = filename;
	while (*p)
	{
		if (*p == L':') return FALSE;
		if (*p == L'/') return FALSE;
		if (*p == L'\\') return FALSE;
		if (*p == L'\'') return FALSE;
		if (*p == L'"') return FALSE;

		p++;
	}

	return TRUE;
}

STDMETHODIMP CLXLocalWebSite::RenameFile(DWORD file_id, BSTR name, VARIANT_BOOL *pSuccess)
{
	if (pSuccess == NULL) return E_POINTER;

	*pSuccess = VARIANT_FALSE;

// TODO, validate name

	if (ValidateFileName(name) == FALSE)
		return E_INVALIDARG;//throw _com_error(-1);

	try
	{
		WCHAR sql[512];
		_variant_t va;
		ADODB::_RecordsetPtr rs;

	// Check that the file that is to be renamed exists, and get the parent folder
		swprintf(sql, L"SELECT parent_id FROM files WHERE id = %d", file_id);
		va.Clear();
		rs = m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		if (rs->EndOfFile != false)	// File doesn't exist
			throw _com_error(-1);

		long parent_id = rs->Fields->Item[_bstr_t(L"parent_id")]->Value;

	// Check if a file with same name already exists in that folder
		swprintf(sql, L"SELECT id FROM files WHERE (parent_id = %d AND filename = '%s')", parent_id, name);
		va.Clear();
		rs = m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		if (rs->EndOfFile == false)	// File with that name already exists
			throw _com_error(-1);

		swprintf(sql, L"UPDATE files SET filename='%s' WHERE id=%d", name, file_id);
		va.Clear();
		m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		Fire_FileUpdate(parent_id, file_id, 3);	// Fire file update event

		*pSuccess = VARIANT_TRUE;
	}
	catch(_com_error &e)
	{
		ATLTRACE("Error RenameFile()\n");
		//DbError(e);
		// TODO, better HRESULT
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CLXLocalWebSite::UpdateItem(BSTR pathName, BSTR xmltext)
{
	try
	{
		CComPtr<ILDOMDocument> xmldoc;
		HRESULT hr = xmldoc.CoCreateInstance(CLSID_LDOMDocument);
		if (FAILED(hr))
		{
			throw _com_error(hr);
		}

		VARIANT_BOOL success;
		xmldoc->loadXML(xmltext, &success);
		if (!success)
		{
			throw _com_error(E_FAIL);
		}

		CComPtr<ILDOMElement> element;
		xmldoc->get_documentElement(&element);

		long file_id = GetPathFileNameID(pathName);

		WCHAR sql[512];
		swprintf(sql, L"SELECT publish FROM files WHERE id = %d", file_id);

		//_variant_t va;
//		ADODB::_RecordsetPtr rs = m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);
		ADODB::_RecordsetPtr rs("ADODB.RecordSet");
		rs->Open(
			_bstr_t(sql),
			_variant_t((IDispatch*)m_siteDataConnection),
			ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdText);
		if (rs->EndOfFile == false)
		{
			//rs->
			CComBSTR publish;
			element->getAttribute(L"publish", &publish);
			
			if (publish.Length())
				rs->Fields->Item[_bstr_t(L"publish")]->Value = (long)_variant_t(publish);

			rs->Update();
		}

		/*
		swprintf(sql, L"UPDATE files SET publish='%s' WHERE id=%d", name, file_id);
		va.Clear();
		m_siteDataConnection->Execute(_bstr_t(sql), &va, ADODB::adCmdText);
		*/

		Fire_FileChangeEvent(3/*update*/, pathName);
	}
	catch(_com_error &e)
	{
		ATLTRACE("Error UpdateItem()\n");
		//DbError(e);
		// TODO, better HRESULT
		return E_FAIL;
	}

	return S_OK;
}
