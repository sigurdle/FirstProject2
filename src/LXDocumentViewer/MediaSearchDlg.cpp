// MediaSearchDlg.cpp : Implementation of CMediaSearchDlg
#include "stdafx.h"
#include "LXDocumentViewer.h"
#include "LXDocumentViewer2.h"
#include "MediaSearchDlg.h"

#include "LXDocumentViewerApp.h"

/// GDI Plus
#include <GdiPlus.h>
#pragma comment(lib, "GdiPlus.lib")

void ComErrorMsg(HWND hWnd, _com_error &e)
{
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrMessage(e.ErrorMessage());
	_bstr_t bstrDescription(e.Description());

	CString msg;
	msg.Format("\n\tSource :  %s \n\tMessage : %s\n\tdescription : %s \n ", (LPCSTR)bstrSource, (LPCSTR)bstrMessage, (LPCSTR)bstrDescription);

	MessageBox(hWnd, msg, "LXWebSite", MB_OK);
}

/////////////////////////////////////////////////////////////////////////////
// CMediaSearchDlg

HRESULT CLXDocumentViewerApp::AddToLibrary(LPCTSTR dir)
{
	HANDLE hFindFile;
	WIN32_FIND_DATA	wfd;

	CString search;
	search.Format("%s\\*.*", dir);

//	std::list<std::string> dirs;

	if ((hFindFile = FindFirstFile(search, &wfd)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (wfd.cFileName[0] != '.')
			{
				CString fullPathName;
				fullPathName.Format("%s\\%s", dir, wfd.cFileName);

				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					AddToLibrary(fullPathName);
				}
				else
				{
					try
					{
						WCHAR fullpath[256];
						swprintf(fullpath, L"%S\\%S", dir, wfd.cFileName);

						Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(fullpath);

						if (pBitmap->GetLastStatus() == Gdiplus::Ok)
						{
							double lastWriteTime;
							SYSTEMTIME systime;
							FileTimeToSystemTime(&wfd.ftLastWriteTime, &systime);
							SystemTimeToVariantTime(&systime, &lastWriteTime);

							ADODB::_RecordsetPtr files("ADODB.RecordSet");
							files->Open(
								L"files",
								_variant_t((IDispatch*)m_conn),
								ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);

							files->AddNew();
						//	files->Fields->Item[_variant_t(L"parent_id")]->Value = (long)((CSiteDir*)m_parent)->m_dbid;
						//	files->Fields->Item[_variant_t(L"type")]->Value = (long)m_type;
							files->Fields->Item[_variant_t(L"filename")]->Value = fullpath;
							files->Fields->Item[_variant_t(L"file_size")]->Value = (long)wfd.nFileSizeLow;
							files->Fields->Item[_variant_t(L"file_date")]->Value = (double)lastWriteTime;

							files->Update();
							files->Close();

							_variant_t	va;

							va.Clear();
							ADODB::_RecordsetPtr recordset;
							recordset = m_conn->Execute(L"SELECT MAX(id) AS id FROM files", &va, ADODB::adCmdText);
						//	recordset = m_pWebSite->m_siteDataConnection->Execute(L"SELECT @@IDENTITY AS id", &va, ADODB::adCmdText);

#if 0
							m_dbid = recordset->Fields->Item[_bstr_t(L"id")]->Value.lVal;
#endif
						}

						delete pBitmap;

					//	CString fullDisplayName = GetFullDisplayName();
					//	m_pWebSite->Fire_FileChangeEvent(1, _bstr_t(fullDisplayName));
					}
					catch (_com_error &e)
					{
						ComErrorMsg(NULL, e);
						return E_FAIL;
					}

					ATLTRACE("%s\n", fullPathName);
				}
			}
		}
		while (FindNextFile(hFindFile, &wfd));

		FindClose(hFindFile);
	}

	return S_OK;
}

LRESULT CMediaSearchDlg::OnSearch(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CString fullpath = "C:\\";
	TCHAR dbfilepath[256];
	_makepath(dbfilepath, NULL, fullpath, _T("LXMyLibrary.mdb"), NULL);

	swprintf(m_app->m_connstr, L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%S", dbfilepath);

	ADOX::_CatalogPtr catalog("ADOX.Catalog");
	ATLASSERT(catalog != NULL);
	//catalog->

	catalog->Create(m_app->m_connstr);

	m_app->m_conn = catalog->GetActiveConnection();

	{
		ADOX::_TablePtr table("ADOX.Table");

		table->ParentCatalog = catalog;
		table->Name = L"files";

		table->Columns->Append(L"id", ADOX::adInteger, 0);
		table->Columns->Item[L"id"]->Properties->Item[L"AutoIncrement"]->Value = _variant_t(VARIANT_TRUE, VT_BOOL);

		//table->Columns->Append(L"parent_id", ADOX::adInteger, 0);
		table->Columns->Append(L"filename", ADOX::adVarWChar, 255);
		//table->Columns->Append(L"type", ADOX::adInteger, 0);
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

	m_app->AddToLibrary("C:");

	return 0;
}
