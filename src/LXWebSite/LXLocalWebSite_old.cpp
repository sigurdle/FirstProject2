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
// CLXLocalWebSite

void CLXLocalWebSite::FinalRelease()
{
/*
	if (m_pRootDir)
	{
		delete m_pRootDir;
		m_pRootDir = NULL;
	}
*/
	if (m_siteDataConnection)
	{
		m_siteDataConnection->Close();
		m_siteDataConnection = NULL;
	}

//	m_pUnkMarshaler.Release();
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

STDMETHODIMP CLXLocalWebSite::GetHomepageFileId(unsigned long *file_id)
{
	if (file_id == NULL) return E_POINTER;
	*file_id = m_homepageFileID;
	return S_OK;
}

STDMETHODIMP CLXLocalWebSite::LoadDocument(BSTR pathName, VARIANT_BOOL *success)
{
	if (success == NULL) return E_POINTER;

//	ATLASSERT(m_pRootDir == NULL);

//	pathName = L"C:\\MySite2\\MySite2.site";

//
	CComQIPtr<ILDOMDocument> document;
	document.CoCreateInstance(CLSID_LDOMDocument);

	VARIANT_BOOL bsuccess;
	document->load(_bstr_t(pathName), &bsuccess);
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

//		m_rootPath = rootpath;

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
	ATLASSERT(0);
/*
	if (pVal == NULL) return E_POINTER;
	*pVal = SysAllocString(m_rootPath);
*/
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
