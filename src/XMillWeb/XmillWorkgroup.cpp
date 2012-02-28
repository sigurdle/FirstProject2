// XmillWorkgroup.cpp : Implementation of CXmillWorkgroup
#include "stdafx.h"
#include "XMillWeb.h"
#include "XmillWorkgroup.h"

/////////////////////////////////////////////////////////////////////////////
// CXmillWorkgroup

HRESULT CXmillWorkgroup::Activate()
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

BOOL CXmillWorkgroup::CanBePooled()
{
	return TRUE;
}

void CXmillWorkgroup::Deactivate()
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

STDMETHODIMP CXmillWorkgroup::TestMethod(BSTR testString, BSTR *pVal)
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

//		ADODB::_ConnectionPtr m_conn;
//		WCHAR m_connstr[512];
//		swprintf(m_connstr, L"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=%s;Data Source=%s", L"xmillenium", L"MMSTUDIO-PROJ");
//		m_conn.CreateInstance(__uuidof(ADODB::Connection));
//		m_conn->Open(m_connstr, "", "", /*ADODB::adAsyncConnect*/ADODB::adConnectUnspecified);

		*pVal = SysAllocString(name);
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CXmillWorkgroup::GetWebSiteList(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	try
	{
		WCHAR sql[256];
		swprintf(sql, L"SELECT id,name,created_date FROM websites");
		_variant_t va;
		ADODB::_RecordsetPtr recordset = m_conn->Execute(sql, &va, ADODB::adCmdText);

		LHTMLLib::ILDOMDocumentPtr xmldocument(__uuidof(LHTMLLib::LDOMDocument));
		xmldocument->loadXML(L"<websites/>");

		while (recordset->EndOfFile == false)
		{
			long id = recordset->Fields->Item[_bstr_t("id")]->Value;
			_bstr_t name = recordset->Fields->Item[_bstr_t("name")]->Value;
			double createDate = recordset->Fields->Item[_bstr_t("created_date")]->Value;

			LHTMLLib::ILDOMElementPtr element = xmldocument->createElement(L"website");

			element->setAttribute(L"id", _bstr_t(id));
			element->setAttribute(L"name", name);
			element->setAttribute(L"createDate", _bstr_t(_variant_t(createDate)));

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

DWORD CXmillWorkgroup::AddNewFile(DWORD parent_id, long type, BSTR filename, DWORD file_size, double file_date)
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
		ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

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

STDMETHODIMP CXmillWorkgroup::NewWebSite(BSTR websitexml, long* pVal)
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

STDMETHODIMP CXmillWorkgroup::GetFolderDirectoryList(BSTR pathName, BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	try
	{
		LHTMLLib::ILDOMDocumentPtr xmldoc;
		xmldoc.CreateInstance(__uuidof(LHTMLLib::LDOMDocument));

		long folder_id = GetPathFileNameID(pathName);

		xmldoc->loadXML(L"<directory/>");

		WCHAR sql[256];
		swprintf(sql, L"SELECT id,filename,type,file_size,file_date FROM files WHERE parent_id = %d", folder_id);
		_variant_t va;
		ADODB::_RecordsetPtr recordset = m_conn->Execute(sql, &va, ADODB::adCmdText);

		while (recordset->EndOfFile == false)
		{
			BYTE type = recordset->Fields->Item[_bstr_t("type")]->Value.lVal;
			_bstr_t filename = recordset->Fields->Item[_bstr_t("filename")]->Value;
			long file_id = recordset->Fields->Item[_bstr_t("id")]->Value.lVal;

			LHTMLLib::ILDOMElementPtr element = xmldoc->createElement(L"item");
			if (element)
			{
				element->setAttribute(L"type", _bstr_t(_variant_t((long)type)));
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

			xmldoc->documentElement->appendChild(element);

			recordset->MoveNext();
		}

		*pVal = xmldoc->saveXML(NULL).copy();

		m_spObjectContext->SetComplete();
	}
	catch (_com_error& e)
	{
		m_spObjectContext->SetAbort();
		return E_FAIL;
	}

	return S_OK;
}

// ILFileSystem

long CXmillWorkgroup::GetFileNameID(long parent_id, BSTR filename)
{
	WCHAR sql[512];
	swprintf(sql, L"SELECT id FROM files WHERE parent_id = %d AND filename = '%s'", parent_id, filename);

	_variant_t va;
	ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

	rs->MoveFirst();

	return rs->Fields->Item[_bstr_t(L"id")]->Value;
}

long CXmillWorkgroup::GetPathFileNameID(BSTR filePath)
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

HRESULT CXmillWorkgroup::AddLogAction(LogActionType type, LHTMLLib::ILDOMElementPtr element)
{
	long log_action_id;
	{
		ADODB::_RecordsetPtr rs(L"ADODB.RecordSet");
		rs->Open(
			_bstr_t(L"log_actions"),
			_variant_t((IDispatch*)m_conn),
		//	ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);
			ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdTable);

		SYSTEMTIME systime;
		GetSystemTime(&systime);
		double date;
		SystemTimeToVariantTime(&systime, &date);

		rs->AddNew();
		rs->Fields->Item[_bstr_t(L"type")]->Value = _variant_t((short)type, VT_I2);
		rs->Fields->Item[_bstr_t(L"log_date")]->Value = date;

		rs->Update();
		rs->MoveLast();

		log_action_id = rs->Fields->Item[_bstr_t(L"id")]->Value;
	}

	LHTMLLib::ILDOMElementPtr child = element->firstChild;
	while (child)
	{
		ADODB::_RecordsetPtr rs(L"ADODB.RecordSet");
		rs->Open(
			_bstr_t(L"log_properties"),
			_variant_t((IDispatch*)m_conn),
		//	ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);
			ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdTable);

		rs->AddNew();
		rs->Fields->Item[_bstr_t(L"log_id")]->Value = log_action_id;
		rs->Fields->Item[_bstr_t(L"property_id")]->Value = (long)_variant_t(child->getAttribute(L"type"));
		rs->Fields->Item[_bstr_t(L"stringValue")]->Value = child->getAttribute(L"value");
		try
		{
			rs->Fields->Item[_bstr_t(L"intValue")]->Value = (long)_variant_t(child->getAttribute(L"value"));
		}
		catch (_com_error)
		{
		}

		rs->Update();

		child = child->nextSibling;
	}

	return S_OK;
}

long CXmillWorkgroup::SaveNodeName(BSTR nodeName)
{
	WCHAR sql[512];
	swprintf(sql, L"SELECT id FROM xmldom_nodenames WHERE nodeName = '%s'", nodeName);

	_variant_t va;
	ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

	if (rs->EndOfFile == false)
	{
		return rs->Fields->Item[_bstr_t(L"id")]->Value;
	}
	else
	{
		ADODB::_RecordsetPtr rs(L"ADODB.RecordSet");
		rs->Open(
			_bstr_t(L"xmldom_nodenames"),
			_variant_t((IDispatch*)m_conn),
		//	ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);
			ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdTable);

		rs->AddNew();
		rs->Fields->Item[_bstr_t(L"nodeName")]->Value = nodeName;

		rs->Update();
		rs->MoveLast();

		return rs->Fields->Item[_bstr_t(L"id")]->Value;
	}

	return 0;
}

long CXmillWorkgroup::SaveNamespaceURI(BSTR namespaceURI)
{
	WCHAR sql[512];
	swprintf(sql, L"SELECT id FROM xmldom_namespaces WHERE namespaceURI = '%s'", namespaceURI);

	_variant_t va;
	ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

	if (rs->EndOfFile == false)
	{
		return rs->Fields->Item[_bstr_t(L"id")]->Value;
	}
	else
	{
		ADODB::_RecordsetPtr rs(L"ADODB.RecordSet");
		rs->Open(
			_bstr_t(L"xmldom_namespaces"),
			_variant_t((IDispatch*)m_conn),
		//	ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);
			ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdTable);

		rs->AddNew();
		rs->Fields->Item[_bstr_t(L"namespaceURI")]->Value = namespaceURI;

		rs->Update();
		rs->MoveLast();

		return rs->Fields->Item[_bstr_t(L"id")]->Value;
	}

	return 0;
}

HRESULT CXmillWorkgroup::SaveXMLNode(long document_id, long parentNode_id, long nodeIndex, LHTMLLib::ILDOMNodePtr node)
{
	long node_id;
	{
		ADODB::_RecordsetPtr rs(L"ADODB.RecordSet");
		rs->Open(
			_bstr_t(L"xmldom_nodes"),
			_variant_t((IDispatch*)m_conn),
		//	ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);
			ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdTable);

		rs->AddNew();
		rs->Fields->Item[_bstr_t(L"document_id")]->Value = document_id;
		rs->Fields->Item[_bstr_t(L"nodeIndex")]->Value = nodeIndex;
		rs->Fields->Item[_bstr_t(L"nodeType")]->Value = (short)node->nodeType;

		if (node->nodeType != LHTMLLib::LNODE_ATTRIBUTE)
			rs->Fields->Item[_bstr_t(L"parentNode_id")]->Value = parentNode_id;

		rs->Update();
		rs->MoveLast();

		node_id = rs->Fields->Item[_bstr_t(L"id")]->Value;
	}

	if (node->nodeType == LHTMLLib::LNODE_ELEMENT)
	{
		LHTMLLib::ILDOMElementPtr element = node;

		ADODB::_RecordsetPtr rs(L"ADODB.RecordSet");
		rs->Open(
			_bstr_t(L"xmldom_elements"),
			_variant_t((IDispatch*)m_conn),
		//	ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);
			ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdTable);

		rs->AddNew();
		rs->Fields->Item[_bstr_t(L"node_id")]->Value = node_id;
		rs->Fields->Item[_bstr_t(L"nodeName_id")]->Value = SaveNodeName(node->nodeName);

		rs->Update();
		rs->MoveLast();

		rs->Close();

		LHTMLLib::ILDOMNamedNodeMapPtr attributes = element->attributes;
		for (int i = 0; i < attributes->length; i++)
		{
			LHTMLLib::ILDOMAttrPtr attr = attributes->item(i);
			SaveXMLNode(document_id, node_id, i, attr);
		}

		int n = 0;
		LHTMLLib::ILDOMNodePtr child = node->firstChild;
		while (child)
		{
			SaveXMLNode(document_id, node_id, n, child);

			child = child->nextSibling;
			n++;
		}
	}
	else if (node->nodeType == LHTMLLib::LNODE_ATTRIBUTE)
	{
		LHTMLLib::ILDOMAttrPtr attr = node;

		ADODB::_RecordsetPtr rs(L"ADODB.RecordSet");
		rs->Open(
			_bstr_t(L"xmldom_attributes"),
			_variant_t((IDispatch*)m_conn),
		//	ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);
			ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdTable);

		rs->AddNew();
		rs->Fields->Item[_bstr_t(L"node_id")]->Value = node_id;
		rs->Fields->Item[_bstr_t(L"nodeName_id")]->Value = SaveNodeName(node->nodeName);
		rs->Fields->Item[_bstr_t(L"attrValue")]->Value = attr->value;
		rs->Fields->Item[_bstr_t(L"element_id")]->Value = parentNode_id;

		rs->Update();
	}
	else if (node->nodeType == LHTMLLib::LNODE_TEXT ||
				node->nodeType == LHTMLLib::LNODE_COMMENT ||
				node->nodeType == LHTMLLib::LNODE_CDATA_SECTION)
	{
		LHTMLLib::ILDOMCharacterDataPtr chardata = node;

		ADODB::_RecordsetPtr rs(L"ADODB.RecordSet");
		rs->Open(
			_bstr_t(L"xmldom_characterdata"),
			_variant_t((IDispatch*)m_conn),
		//	ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);
			ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdTable);

		_bstr_t data = chardata->data;
		rs->AddNew();
		rs->Fields->Item[_bstr_t(L"node_id")]->Value = node_id;
		rs->Fields->Item[_bstr_t(L"text_data")]->Value = data;

		rs->Update();
	}

	return S_OK;
}

HRESULT CXmillWorkgroup::SaveXMLDocument(long file_id, LHTMLLib::ILDOMDocumentPtr document)
{
	ADODB::_RecordsetPtr rs(L"ADODB.RecordSet");
	rs->Open(
		_bstr_t(L"xmldom_documents"),
		_variant_t((IDispatch*)m_conn),
	//	ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);
		ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdTable);

	rs->AddNew();
	rs->Fields->Item[_bstr_t(L"file_id")]->Value = file_id;
	rs->Fields->Item[_bstr_t(L"version")]->Value = document->_version;
	rs->Fields->Item[_bstr_t(L"standalone")]->Value = document->standalone;
	rs->Fields->Item[_bstr_t(L"encoding")]->Value = document->encoding;

	rs->Update();
	rs->MoveLast();

	long document_id = rs->Fields->Item[_bstr_t(L"id")]->Value.lVal;

	int n = 0;
	LHTMLLib::ILDOMNodePtr child = document->firstChild;
	while (child)
	{
		SaveXMLNode(document_id, 0, n, child);

		child = child->nextSibling;
		n++;
	}

	return S_OK;
}

_bstr_t CXmillWorkgroup::GetNodeName(long id)
{
	WCHAR sql[512];
	swprintf(sql, L"SELECT nodeName FROM xmldom_nodenames WHERE id = %d", id);

	_variant_t va;
	ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

	return rs->Fields->Item[_bstr_t(L"nodeName")]->Value;
}

_bstr_t CXmillWorkgroup::GetNamespaceURI(long id)
{
	WCHAR sql[512];
	swprintf(sql, L"SELECT namespaceURI FROM xmldom_namespaces WHERE id = %d", id);

	_variant_t va;
	ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

	return rs->Fields->Item[_bstr_t(L"namespaceURI")]->Value;
}

LHTMLLib::ILDOMNodePtr CXmillWorkgroup::LoadXMLNode(ADODB::_RecordsetPtr nodeRs, LHTMLLib::ILDOMDocumentPtr document)
{
	LHTMLLib::ILDOMNodePtr node;

	long node_id = nodeRs->Fields->Item[_bstr_t(L"id")]->Value;
	short nodeType = nodeRs->Fields->Item[_bstr_t(L"nodeType")]->Value;

	if (nodeType == LHTMLLib::LNODE_ELEMENT)
	{
		WCHAR sql[512];
		swprintf(sql, L"SELECT id, nodeType, nodeName_id, namespaceURI_id, FROM xmldom_elements WHERE node_id = %d", node_id);

		_variant_t va;
		ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		LHTMLLib::ILDOMElementPtr element = document->createElementNS(
			GetNamespaceURI(rs->Fields->Item[_bstr_t(L"namespaceURI_id")]->Value),
			GetNodeName(rs->Fields->Item[_bstr_t(L"nodeName_id")]->Value));

		if (element)
		{
			// attributes
			{
				WCHAR sql[512];
				swprintf(sql, L"SELECT nodeName_id, attrValue FROM xmldom_attributes WHERE element_id = %d", node_id);

				_variant_t va;
				ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

				LHTMLLib::ILDOMNamedNodeMapPtr attributes = element->attributes;

				while (rs->EndOfFile == false)
				{
					LHTMLLib::ILDOMAttrPtr attr = LoadXMLNode(rs, document);
					if (attr)
					{
						attributes->setNamedItem(attr);
					}

					rs->MoveNext();
				}
			}

			// child nodes
			{
				WCHAR sql[512];
				swprintf(sql, L"SELECT id, namespaceURI_id, FROM xmldom_nodes WHERE parentNode_id = %d SORT BY nodeIndex", node_id);

				_variant_t va;
				ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

				while (rs->EndOfFile == false)
				{
					LHTMLLib::ILDOMNodePtr child = LoadXMLNode(rs, document);
					if (child)
					{
						element->appendChild(child);
					}

					rs->MoveNext();
				}
			}

			node = element;
		}
	}
	else if (nodeType == LHTMLLib::LNODE_ATTRIBUTE)
	{
	}
	else if (nodeType == LHTMLLib::LNODE_TEXT ||
				nodeType == LHTMLLib::LNODE_COMMENT ||
				nodeType == LHTMLLib::LNODE_CDATA_SECTION)
	{
		WCHAR sql[512];
		swprintf(sql, L"SELECT text_data FROM xmldom_characterdata WHERE node_id = %d", node_id);

		_variant_t va;
		ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		_bstr_t text_data = rs->Fields->Item[_bstr_t(L"text_data")]->Value;

		if (nodeType == LHTMLLib::LNODE_TEXT)
		{
			LHTMLLib::ILDOMTextPtr text = document->createTextNode(text_data);
			node = text;
		}
		else if (nodeType == LHTMLLib::LNODE_COMMENT)
		{
			LHTMLLib::ILDOMCommentPtr comment = document->createComment(text_data);
			node = comment;
		}
		else if (nodeType == LHTMLLib::LNODE_CDATA_SECTION)
		{
			LHTMLLib::ILDOMCDATASectionPtr cdata = document->createCDATASection(text_data);
			node = cdata;
		}
	}

	return node;
}

/*
HRESULT CXmillWorkgroup::LoadXMLDocument(long document_id, LHTMLLib::ILDOMDocumentPtr document)
{
}
*/

/*
 Saves a file from a client to the database
 */

STDMETHODIMP CXmillWorkgroup::SaveArrayAsFile(/*long folder_id,*/ BSTR filePath, SAFEARRAY* dataArray, BSTR user, long* pfile_id, VARIANT_BOOL* pSuccess)
{
	if (pSuccess == NULL) return E_POINTER;

	*pSuccess = VARIANT_FALSE;
	if (pfile_id) *pfile_id = 0;

	SYSTEMTIME systime;
	GetSystemTime(&systime);
	double lastWriteTime;
	SystemTimeToVariantTime(&systime, &lastWriteTime);

	DWORD file_size = dataArray->rgsabound[0].cElements;

	try
	{
		WCHAR pathBuffer[1024];
		wcscpy(pathBuffer, filePath);

		int len = wcslen(pathBuffer);
		int n = len-1;
		while (n >= 0)
		{
			if (pathBuffer[n] == L'/')
			{
				pathBuffer[n] = L'\0';
				break;
			}
			n--;
		}

		WCHAR* fileName = &pathBuffer[n+1];

		long folder_id = GetPathFileNameID(pathBuffer);

		long file_id;
		{
			ADODB::_RecordsetPtr rs(L"ADODB.RecordSet");
			rs->Open(
				_bstr_t(L"files"),
				_variant_t((IDispatch*)m_conn),
			//	ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);
				ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdTable);

			rs->AddNew();
			rs->Fields->Item[_bstr_t(L"parent_id")]->Value = (long)folder_id;
			rs->Fields->Item[_bstr_t(L"type")]->Value = (long)2;
			rs->Fields->Item[_bstr_t(L"filename")]->Value = _bstr_t(fileName);
			rs->Fields->Item[_bstr_t(L"file_size")]->Value = (long)file_size;
			rs->Fields->Item[_bstr_t(L"file_date")]->Value = (double)lastWriteTime;

			rs->Update();
			rs->MoveLast();

			file_id = rs->Fields->Item[_bstr_t(L"id")]->Value.lVal;
		}

		{
			ADODB::_RecordsetPtr rs(L"ADODB.RecordSet");
			rs->Open(
				_bstr_t(L"files_data"),
				_variant_t((IDispatch*)m_conn),
				ADODB::adOpenForwardOnly, ADODB::adLockOptimistic, ADODB::adCmdTable);

			rs->AddNew();
			rs->Fields->Item[_bstr_t(L"file_id")]->Value = (long)file_id;
			rs->Fields->Item[_bstr_t(L"file_size")]->Value = (long)file_size;
			rs->Fields->Item[_bstr_t(L"file_date")]->Value = (double)lastWriteTime;

			_variant_t varr;
			varr.vt = VT_ARRAY | VT_UI1;
			varr.parray = dataArray;
			rs->Fields->Item[_bstr_t(L"file_data")]->AppendChunk(varr);

			varr.parray = NULL;

			rs->Update();
		}

		{
			LHTMLLib::ILDOMBuilderPtr builder;
			builder.CreateInstance(__uuidof(LHTMLLib::LDOMBuilder));

			LHTMLLib::ITextDataPtr textData;
			textData.CreateInstance(__uuidof(TEXTDATAMODLib::TextData));
			textData->loadByteArray(dataArray);

			LHTMLLib::ILDOMDocumentPtr document = builder->parseTextData(textData);

			if (document)
			{
				SaveXMLDocument(file_id, document);
			}
		}

		{
			LHTMLLib::ILDOMDocumentPtr xmldoc;
			xmldoc.CreateInstance(__uuidof(LHTMLLib::LDOMDocument));
			xmldoc->loadXML(L"<action/>");

			LHTMLLib::ILDOMElementPtr element;
			
			element = xmldoc->createElement(L"property");
			element->setAttribute(L"type", _bstr_t(_variant_t(1L)));
			element->setAttribute(L"value", _bstr_t(_variant_t(file_id)));
			xmldoc->documentElement->appendChild(element);

			AddLogAction(LTSaveFile, xmldoc->documentElement);
		}

		*pSuccess = VARIANT_TRUE;

		m_spObjectContext->SetComplete();

#if 0
		Fire_FileUpdate(folder_id, file_id, 1);
#endif
	}
	catch (_com_error& e)
	{
		m_spObjectContext->SetAbort();
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CXmillWorkgroup::OpenFileAsArray(/*long file_id*/ BSTR filePath, SAFEARRAY** dataArray)
{
	if (dataArray == NULL) return E_POINTER;

	*dataArray = NULL;

	try
	{
		long file_id = GetPathFileNameID(filePath);

		WCHAR sql[512];
		swprintf(sql, L"SELECT file_size,file_data FROM files_data WHERE file_id = %d", file_id);

		_variant_t va;
		ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		rs->MoveFirst();

		long file_size = rs->Fields->Item[_bstr_t(L"file_size")]->Value;

		_variant_t varr = rs->Fields->Item[_bstr_t(L"file_data")]->GetChunk(file_size);
		*dataArray = varr.parray;
		varr.Detach();

		m_spObjectContext->SetComplete();
	}
	catch (_com_error& e)
	{
		m_spObjectContext->SetAbort();
		return E_FAIL;
	}

	return S_OK;
}

_bstr_t CXmillWorkgroup::GetFolderDisplayPathRecursive(long folder_id, WCHAR* pathDelimiter)
{
	_bstr_t name = L"";

	if (folder_id)
	{
		try
		{
			WCHAR sql[512];
			swprintf(sql, L"SELECT parent_id, filename FROM files WHERE id = %d", folder_id);

			_variant_t va;
			ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

			rs->MoveFirst();

			long parent_id = rs->Fields->Item[_bstr_t(L"parent_id")]->Value;
			_bstr_t filename = rs->Fields->Item[_bstr_t(L"filename")]->Value;
			_bstr_t parentname = GetFolderDisplayPathRecursive(parent_id, pathDelimiter);

			name = parentname + filename + pathDelimiter;
		}
		catch(_com_error e)
		{
		//	MessageBox(NULL, "Error GetDisplayName()", "WebEditorServer", MB_OK);
		//	DbError(e);
			return E_FAIL;
		}
	}
	else
	{
		name = pathDelimiter;
	}

	return name;
}

STDMETHODIMP CXmillWorkgroup::GetFolderDisplayPath(long folder_id, BSTR *displayName)
{
	if (displayName == NULL) return E_POINTER;

	_bstr_t name = GetFolderDisplayPathRecursive(folder_id, L"/");
	*displayName = SysAllocString(name);

	return S_OK;
}

STDMETHODIMP CXmillWorkgroup::GetParentFolderId(long folder_id, long *pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = 0;

	try
	{
		WCHAR sql[512];
		swprintf(sql, L"SELECT parent_id FROM files WHERE id = %d", folder_id);

		_variant_t va;
		ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		rs->MoveFirst();

		*pVal = (long)rs->Fields->Item[_bstr_t(L"parent_id")]->Value;
	}
	catch(_com_error e)
	{
	//	MessageBox(NULL, "Error GetParentFolderId()", "WebEditorServer", MB_OK);
	//	DbError(e);
		return E_FAIL;
	}

	return S_OK;
}

/*
DWORD CXmillWorkgroup::AddNewFile(DWORD parent_id, long type, BSTR filename, DWORD file_size, double file_date)
{
	ADODB::_RecordsetPtr files(L"ADODB.RecordSet");
	files->Open(
		_bstr_t(L"files"),
		_variant_t((IDispatch*)m_conn),
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
*/

STDMETHODIMP CXmillWorkgroup::FindOrCreateFolder(BSTR pathName, BSTR user, long *pfolder_id)
{
	if (pfolder_id == NULL) return E_POINTER;
	*pfolder_id = 0L;

	try
	{
		WCHAR pathBuffer[1024];
		wcscpy(pathBuffer, pathName);

		int len = wcslen(pathBuffer);
		int n = len-1;
		while (n >= 0)
		{
			if (pathBuffer[n] == L'/')
			{
				pathBuffer[n] = L'\0';
				break;
			}
			n--;
		}

		WCHAR* fileName = &pathBuffer[n];

		long folder_id = GetPathFileNameID(pathBuffer);

		long file_id = GetFileNameID(folder_id, fileName);
		if (file_id)
		{
			*pfolder_id = file_id;
		}
		else
		{
			SYSTEMTIME systime;
			GetSystemTime(&systime);
			double lastWriteTime;
			SystemTimeToVariantTime(&systime, &lastWriteTime);

			DWORD id = AddNewFile(folder_id, 1, fileName, 0, lastWriteTime);

#if 0
			Fire_FileUpdate(parent_id, id, 1);
#endif

			*pfolder_id = id;
		}

		m_spObjectContext->SetComplete();
	}
	catch (_com_error& e)
	{
		m_spObjectContext->SetAbort();
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CXmillWorkgroup::CreateFolder(long parent_id, BSTR name, BSTR user, long *pfolder_id)
{
	if (pfolder_id == NULL) return E_POINTER;
	*pfolder_id = 0L;

	try
	{
		WCHAR sql[512];
		swprintf(sql, L"SELECT id FROM files WHERE (parent_id = %d AND filename = '%s')", parent_id, name);

		_variant_t va;
		ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

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

#if 0
			Fire_FileUpdate(parent_id, id, 1);
#endif

			*pfolder_id = id;
		}
	}
	catch(_com_error e)
	{
	//	MessageBox(NULL, "Error CreateFolder()", "WebEditorServer", MB_OK);
	//	DbError(e);
		return E_FAIL;
	}

	return S_OK;
}

void CXmillWorkgroup::RemoveFileFromDatabase(long parent_id, long id)
{
	WCHAR sql[256];
	_variant_t va;

	try
	{
		// Delete children
		swprintf(sql, L"SELECT id FROM files WHERE parent_id = %d", id);

		va.Clear();
		ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);
		while (rs->EndOfFile == false)
		{
			long fileid = rs->Fields->Item[_bstr_t(L"id")]->Value;

			RemoveFileFromDatabase(id, fileid);	// Recurse

			rs->MoveNext();
		}

	// Delete this
		swprintf(sql, L"DELETE FROM files WHERE id = %d", id);
		va.Clear();
		m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		swprintf(sql, L"DELETE FROM files_data WHERE file_id = %d", id);
		va.Clear();
		m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);
	}
	catch (_com_error &e)
	{
	//	MessageBox(NULL, "Error RemoveFromDatabase()", "WebEditorServer", MB_OK);
	//	DbError(e);
		//return E_FAIL;
	}

#if 0
	Fire_FileUpdate(parent_id, id, 2);
#endif
}

STDMETHODIMP CXmillWorkgroup::DeleteFilePermanently(long file_id, VARIANT_BOOL *pSuccess)
{
	if (pSuccess == NULL) return E_POINTER;

	WCHAR sql[512];
	swprintf(sql, L"SELECT parent_id FROM files WHERE id = %d", file_id);

	_variant_t va;
	ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);
	if (rs->EndOfFile == false)
	{
		long parent_id = rs->Fields->Item[_bstr_t(L"parent_id")]->Value;

		RemoveFileFromDatabase(parent_id, file_id);

		*pSuccess = VARIANT_TRUE;
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

STDMETHODIMP CXmillWorkgroup::RenameFile(long file_id, BSTR name, VARIANT_BOOL *pSuccess)
{
	if (pSuccess == NULL) return E_POINTER;

	*pSuccess = VARIANT_FALSE;

// TODO, validate name

	if (ValidateFileName(name) == FALSE)
		throw _com_error(-1);

	try
	{
		WCHAR sql[512];
		_variant_t va;
		ADODB::_RecordsetPtr rs;

	// Check that the file that is to be renamed exists, and get the parent folder
		swprintf(sql, L"SELECT parent_id FROM files WHERE id = %d", file_id);
		va.Clear();
		rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		if (rs->EndOfFile != false)	// File doesn't exist
			throw _com_error(-1);

		long parent_id = rs->Fields->Item[_bstr_t(L"parent_id")]->Value;

	// Check if a file with same name already exists in that folder
		swprintf(sql, L"SELECT id FROM files WHERE (parent_id = %d AND filename = '%s')", parent_id, name);
		va.Clear();
		rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		if (rs->EndOfFile == false)	// File with that name already exists
			throw _com_error(-1);

		swprintf(sql, L"UPDATE files SET filename='%s' WHERE id=%d", name, file_id);
		va.Clear();
		m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

#if 0
		Fire_FileUpdate(parent_id, file_id, 3);	// Fire file update event
#endif

		*pSuccess = VARIANT_TRUE;
	}
	catch(_com_error e)
	{
		//MessageBox(NULL, "Error RenameFile()", "WebEditorServer", MB_OK);
		//DbError(e);
		throw e;
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CXmillWorkgroup::SetPathSecurityDescriptor(BSTR pathName, SAFEARRAY* sdArray)
{
	try
	{
		long file_id = GetPathFileNameID(pathName);

		WCHAR sql[512];
		swprintf(sql, L"SELECT sd FROM files WHERE id = %d", file_id);

//		_variant_t va;
//		ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);
		ADODB::_RecordsetPtr rs(L"ADODB.RecordSet");
		rs->Open(
			_bstr_t(sql),
			_variant_t((IDispatch*)m_conn),
			ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdText);
//		rs->MoveFirst();

		if (rs->EndOfFile == false)
		{
			_variant_t varr;
			varr.vt = VT_ARRAY | VT_UI1;
			varr.parray = sdArray;
			rs->Fields->Item[_bstr_t(L"sd")]->AppendChunk(varr);

			varr.parray = NULL;
		}

		rs->Update();

		m_spObjectContext->SetComplete();
	}
	catch (_com_error& e)
	{
		m_spObjectContext->SetAbort();
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CXmillWorkgroup::GetPathSecurityDescriptor(BSTR pathName, VARIANT *pVal)
{
	try
	{
		long file_id = GetPathFileNameID(pathName);

		WCHAR sql[512];
		swprintf(sql, L"SELECT sd FROM files WHERE id = %d", file_id);

		_variant_t va;
		ADODB::_RecordsetPtr rs = m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

		long size = rs->Fields->Item[_bstr_t(L"sd")]->ActualSize;
		_variant_t varr = rs->Fields->Item[_bstr_t(L"sd")]->GetChunk(size);
		*pVal = varr;
		varr.Detach();

		m_spObjectContext->SetComplete();
	}
	catch (_com_error& e)
	{
		m_spObjectContext->SetAbort();
		return E_FAIL;
	}

	return S_OK;
}
