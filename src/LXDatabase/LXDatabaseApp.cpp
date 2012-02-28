// LXDatabaseApp.cpp : Implementation of CLXDatabaseApp
#include "stdafx.h"
#include "LXDatabase.h"
#include "LXDatabaseApp.h"

/////////////////////////////////////////////////////////////////////////////
// CLXDatabaseApp

#if 0

BEGIN_CMD_MAP(CLXFrameworkApp)

	CMD_HANDLER(ID_FILE_OPENDATABASE, OnFileOpenDatabase)

//
//	CMD_HANDLER(ID_CONVERT_IMPORTDATABASEDATA, OnConvertImportDatabaseData)

END_CMD_MAP()

#include "oledb.h"		//OLE DB Header 
#include "oledberr.h"	//OLE DB Errors
#include "msdasc.h"		//OLE DB ServiceComponents
#include "msdaguid.h"	//CLSID_OLEDB_ENUMERATOR
#include <msdadc.h>		//DataConversion library

#import "C:\Program Files\Common Files\System\Ole DB\oledb32.dll"
//#import "C:\Programfiler\Fellesfiler\System\Ole DB\oledb32.dll"

#include "DBView.h"

void DbError(_com_error &e);

LRESULT CLXFrameworkApp::OnFileOpenDatabase(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
NOT_COMPLETE(0);

#if 0
	HRESULT               hr                    = S_OK;
	IDataInitialize *     pIDataInitialize       = NULL;
	
	hr = CoCreateInstance(
      CLSID_DataLinks,
      NULL,
      CLSCTX_INPROC_SERVER,
      IID_IDataInitialize,
      reinterpret_cast<void **>(&pIDataInitialize));
	
	
	// CreateDBInstance to instantiate previously stored provider.
	
	CLSID               clsidProvider     = CLSID_NULL;//GetProviderCLSID();
	IDBProperties *      pIDBProperties   = NULL;
	
	hr = pIDataInitialize->CreateDBInstance(
      clsidProvider,
      NULL,
      CLSCTX_INPROC_SERVER,
      NULL,
      IID_IDBProperties,
      reinterpret_cast<IUnknown **>(&pIDBProperties));
	
	
	// Set some previously stored properties.
	
	ULONG            cPropertySets          = 0;//GetPropertySetsCount();
	DBPROPSET        (*rgPropertySets)      = NULL;//GetPropertySets();
	
	//hr = pIDBProperties->SetProperties(cPropertySets, rgPropertySets);
	
	
	// Prompt the user to view/edit the connection information.
	
	IDBPromptInitialize   *pIDBPromptInitialize   = NULL;
	
	hr = pIDataInitialize ->QueryInterface(
      IID_IDBPromptInitialize,
      reinterpret_cast<void **>(&pIDBPromptInitialize));
	
	hr = pIDBPromptInitialize->PromptDataSource(
      NULL,
      GetMainHwnd(),//m_hWnd,
      DBPROMPTOPTIONS_PROPERTYSHEET,
      0, NULL,
      NULL,
      IID_IDBProperties,
      reinterpret_cast<IUnknown **>(&pIDBProperties));
#endif

	_bstr_t connstr;
	try
	{
		MSDASC::IDataSourceLocatorPtr dl;
		dl.CreateInstance(__uuidof(MSDASC::DataLinks));

		ADODB::_ConnectionPtr conn = dl->PromptNew();
		connstr = conn->ConnectionString;
	}
	catch (_com_error& e)
	{
		DbError(e);
	}

	if (connstr.length())
	{
	// Create DBView
		CComObject<CUIMDIChild>* child;
		CComObject<CUIMDIChild>::CreateInstance(&child);
		child->AddRef();
		gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&child->m_spFrame);

		{
			CComObject<CDBView>* pDBView;
			CComObject<CDBView>::CreateInstance(&pDBView);
			if (pDBView)
			{
				gApp->m_frame->FindMenu(_Module.GetResourceInstance(), IDR_DBVIEW, &pDBView->m_menu);

				pDBView->m_conn.CreateInstance(L"ADODB.Connection"/*__uuidof(ADODB::_Connection)*/);
				pDBView->m_conn->Open(connstr, L"", L"", ADODB::adConnectUnspecified);

#if 0
				{
					WCHAR sql[512];
					swprintf(sql, L"SELECT id,name FROM websites FOR XML AUTO");

					_variant_t va;
					ADODB::_RecordsetPtr rs = pDBView->m_conn->Execute(_bstr_t(sql), &va, ADODB::adCmdText);

					rs->MoveFirst();

					if (rs->EndOfFile == false)
					{
						long n = rs->Fields->Count;

						_variant_t vIndex = (long)0L;
						ADODB::FieldPtr fld = rs->Fields->GetItem(&vIndex);

						ADODB::DataTypeEnum type = fld->Type;

						long size = fld->ActualSize;
						_variant_t varr = fld->GetChunk(size);

						WCHAR* p;
						if (SUCCEEDED(SafeArrayAccessData(varr.parray, (void**)&p)))
						{
							MessageBox(NULL, _bstr_t(p), "", MB_OK);

							SafeArrayUnaccessData(varr.parray);
						}

						//_variant_t xmltext = fld->GetValue();

						//MessageBox(NULL, _bstr_t(xmltext), "", MB_OK);
					}
				}
#endif

				child->AddPage(pDBView, NULL);
			}
		}

		ATLASSERT(0);
	//	child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);
	}

//	::CoCreateInstance(__uuidof(ADODB::Connection),NULL,CLSCTX_ALL,__uuidof(ADODB::_Connection),(void **)&cnxt);
//	dl->PromptEdit((IDispatch **)&cnxt);
//	_bstr_t connstr = dl->PromptNew();

	return 0;
}

#endif