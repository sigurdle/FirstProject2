// XmillWebSite.cpp : Implementation of CXmillWebSite
#include "stdafx.h"
#include "XMillWeb.h"
#include "XmillWebSite.h"

/////////////////////////////////////////////////////////////////////////////
// CXmillWebSite

HRESULT CXmillWebSite::Activate()
{
	HRESULT hr = GetObjectContext(&m_spObjectContext);
	if (FAILED(hr)) return hr;

//	ADODB::_ConnectionPtr m_conn;
	WCHAR m_connstr[512];

	swprintf(m_connstr, L"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=%s;Data Source=%s", L"xmillenium", L"MMSTUDIO-PROJ");

	m_spObjectContext->CreateInstance(__uuidof(ADODB::Connection), __uuidof(ADODB::_Connection), (void**)&m_conn);
//	m_conn.CreateInstance(__uuidof(ADODB::Connection));
	m_conn->Open(m_connstr, "", "", /*ADODB::adAsyncConnect*/ADODB::adConnectUnspecified);

	return S_OK;
}

BOOL CXmillWebSite::CanBePooled()
{
	return TRUE;
}

void CXmillWebSite::Deactivate()
{
	if (m_conn)
	{
		m_conn->Close();
		m_conn.Release();
	}

	m_spObjectContext.Release();
}

#if 0
long CXmillWebSite::NewUser(BSTR name)
{
	long userfolder_id = AddNewFile(0, 1, name, 0, date);

}
#endif

#if 0
STDMETHODIMP CXmillWebSite::TestMethod(BSTR testString, BSTR *pVal)
{
	CComPtr<ISecurityCallContext> securityContext;
	CoGetCallContext(IID_ISecurityCallContext, (void**)&securityContext);

	VARIANT_BOOL bIsSecurityEnabled;
	securityContext->IsSecurityEnabled(&bIsSecurityEnabled);
	if (bIsSecurityEnabled)
	{
		_variant_t v;
		securityContext->get_Item(L"OriginalCaller", &v);

		CComQIPtr<ISecurityIdentityColl> identity = v;

		identity->get_Item(L"AccountName", &v);
		_bstr_t name = v;

		//DWORD cbSize = LookupAccountName(NULL, name, NULL, NULL, NULL, NULL, NULL);

		SID* sid = (SID*)GlobalAlloc(0, 8000);
		DWORD cbSid = 8000;
		TCHAR domain[512];
		DWORD cbDomain = sizeof(domain);
		SID_NAME_USE name_use;
		LookupAccountName(NULL, name, sid, &cbSid, domain, &cbDomain, &name_use);

//		ADODB::_ConnectionPtr m_siteDataConnection;
//		WCHAR m_connstr[512];
//		swprintf(m_connstr, L"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=%s;Data Source=%s", L"xmillenium", L"MMSTUDIO-PROJ");
//		m_siteDataConnection.CreateInstance(__uuidof(ADODB::Connection));
//		m_siteDataConnection->Open(m_connstr, "", "", /*ADODB::adAsyncConnect*/ADODB::adConnectUnspecified);

		*pVal = SysAllocString(name);
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CXmillWebSite::GetWebSiteList(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	try
	{
		WCHAR sql[256];
		swprintf(sql, L"SELECT id,name FROM websites");
		_variant_t va;
		ADODB::_RecordsetPtr recordset = m_conn->Execute(sql, &va, ADODB::adCmdText);

		LHTMLLib::ILDOMDocumentPtr xmldocument;

		xmldocument->loadXML(L"<websites/>");

		while (recordset->EndOfFile == false)
		{
			_variant_t id = recordset->Fields->Item[_bstr_t("id")]->Value;
			_bstr_t name = recordset->Fields->Item[_bstr_t("name")]->Value;

			LHTMLLib::ILDOMElementPtr element = xmldocument->createElement(L"website");

			element->setAttribute(L"id", _bstr_t(id));
			element->setAttribute(L"name", name);

			xmldocument->documentElement->appendChild(element);

			recordset->MoveNext();
		}

		*pVal = xmldocument->saveXML(NULL).copy();

		m_spObjectContext->SetComplete();
	}
	catch (_com_error& e)
	{
		m_spObjectContext->SetAbort();
		return E_FAIL;
	}

	return S_OK;
}

DWORD CXmillWebSite::AddNewFile(DWORD parent_id, long type, BSTR filename, DWORD file_size, double file_date)
{
	ADODB::_RecordsetPtr files(L"ADODB.RecordSet");

/*	files->Open(
		_bstr_t(L"files"),
		_variant_t((IDispatch*)m_conn),
		ADODB::adOpenKeyset, ADODB::adLockBatchOptimistic, ADODB::adCmdTable);
*/
	files->Open(
		_bstr_t(L"files"),
		_variant_t((IDispatch*)m_conn),
		ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdTable);

	long id;

	files->AddNew();
	files->Fields->Item[_bstr_t(L"parent_id")]->Value = (long)parent_id;
	files->Fields->Item[_bstr_t(L"type")]->Value = type;
	files->Fields->Item[_bstr_t(L"filename")]->Value = filename;
	files->Fields->Item[_bstr_t(L"file_size")]->Value = (long)file_size;
	files->Fields->Item[_bstr_t(L"file_date")]->Value = (double)file_date;

	files->Update();

	files->MoveLast();
	//files->MoveNext();
//	files->MovePrevious();

	id = (long)files->Fields->Item[_bstr_t(L"id")]->Value.lVal;

//	files->Requery(0);
//	files->Close();

//	id = (long)files->Fields->Item[_bstr_t(L"id")]->Value.lVal;

#if 0
	{
		WCHAR sql[512];
		swprintf(sql, L"SELECT @@IDENTITY AS id");
//		swprintf(sql, L"SELECT SCOPE_IDENTITY() AS id");
//		swprintf(sql, L"SELECT IDENT_CURRENT('files') AS id");

		_variant_t va;
		ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);
		_variant_t varid = rs->Fields->Item[_bstr_t(L"id")]->Value;

		id = varid;
	}
#endif
	//files->UpdateBatch(ADODB::adAffectCurrent);
//	return (long)files->Fields->Item[_bstr_t(L"id")]->Value.lVal;

	return id;
}

/*
STDMETHODIMP CXmillWebSite::FindOrCreateFolder(DWORD parent_id, BSTR name, BSTR user, DWORD *pfolder_id)
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
	catch(_com_error e)
	{
		MessageBox(NULL, "Error FindOrCreateFolder()", "WebEditorServer", MB_OK);
		DbError(e);
	}

	return S_OK;
}
*/

STDMETHODIMP CXmillWebSite::NewWebSite(BSTR websitexml, long* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = 0L;

	try
	{
		LHTMLLib::ILDOMDocumentPtr xmldoc;
		xmldoc.CreateInstance(__uuidof(LHTMLLib::LDOMDocument));

		xmldoc->loadXML(websitexml);

		_bstr_t name = xmldoc->documentElement->getAttribute(L"name");

		WCHAR sql[512];
		swprintf(sql, L"SELECT id FROM websites WHERE (name = '%s')", (BSTR)name);

		_variant_t va;
		ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);
/*
		if (rs->EndOfFile == false)
		{
			// Website with this name already exists
			throw _com_error(E_FAIL);
		}
		else
*/		{
			SYSTEMTIME systime;
			GetSystemTime(&systime);
			double date;
			SystemTimeToVariantTime(&systime, &date);

			long rootfolder_id = AddNewFile(0, 1, name, 0, date);

			ADODB::_RecordsetPtr websites(L"ADODB.RecordSet");
			websites->Open(
				_bstr_t(L"websites"),
				_variant_t((IDispatch*)m_conn),
				ADODB::adOpenDynamic/*adOpenForwardOnly*/, ADODB::adLockOptimistic, ADODB::adCmdTable);

			websites->AddNew();
			websites->Fields->Item[_bstr_t(L"name")]->Value = name;
			websites->Fields->Item[_bstr_t(L"rootfolder_id")]->Value = rootfolder_id;
			websites->Fields->Item[_bstr_t(L"created_date")]->Value = (double)date;

			websites->Update();
			websites->MoveLast();

			*pVal = (long)websites->Fields->Item[_bstr_t(L"id")]->Value.lVal;
		}

		m_spObjectContext->SetComplete();
	}
	catch(_com_error& e)
	{
		m_spObjectContext->SetAbort();
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CXmillWebSite::GetFolderDirectoryList(long folder_id, BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	try
	{
		LHTMLLib::ILDOMDocumentPtr xmldocument;

		xmldocument->loadXML(L"<directory/>");

		WCHAR sql[256];
		swprintf(sql, L"SELECT id,filename,type,file_size,file_date FROM files WHERE parent_id = %d", folder_id);
		_variant_t va;
		ADODB::_RecordsetPtr recordset = m_conn->Execute(sql, &va, ADODB::adCmdText);

		while (recordset->EndOfFile == false)
		{
			BYTE type = recordset->Fields->Item[_bstr_t("type")]->Value.lVal;
			_bstr_t filename = recordset->Fields->Item[_bstr_t("filename")]->Value;
			long file_id = recordset->Fields->Item[_bstr_t("id")]->Value.lVal;

			LHTMLLib::ILDOMElementPtr element = xmldocument->createElement(L"item");
			if (element)
			{
				element->setAttribute(L"filename", filename);
				element->setAttribute(L"file_id", _bstr_t(_variant_t(file_id)));
				element->setAttribute(L"file_size", _bstr_t(_variant_t(recordset->Fields->Item[_bstr_t("file_size")]->Value.lVal)));

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
					ADODB::_RecordsetPtr rs = m_conn->Execute(sql, &va, ADODB::adCmdText);
					element->setAttribute(L"c", _bstr_t(_variant_t((long)((rs->Fields->Item[_bstr_t(L"c")]->Value.lVal > 0L)? 1: 0))));
				}
			}

			xmldocument->documentElement->appendChild(element);

			recordset->MoveNext();
		}

		*pVal = xmldocument->saveXML(NULL).copy();
	}
	catch (_com_error& e)
	{
		m_spObjectContext->SetAbort();
		return E_FAIL;
	}

	return S_OK;
}

#endif