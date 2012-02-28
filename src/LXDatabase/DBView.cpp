// DBView.cpp : Implementation of CDBView
#include "stdafx.h"
#include "LXFramework.h"
#include "LXFramework2.h"
#include "DBView.h"

#include "LXFrameworkApp.h"
#include "LXFrameworkFrame.h"

extern CLXFrameworkApp* gApp;


/////////////////////////////////////////////////////////////////////////////
// CDBView

CDBView::CDBView()
{
}

int CDBView::FinalConstruct()
{
	HRESULT hr;

	hr = m_treeCtl.CoCreateInstance(CLSID_UITreeControl);
	if (FAILED(hr)) return hr;

	m_treeCtl->InsertColumn(0, L"Name", 200, true, true, NULL);

	m_catalog.CreateInstance(L"ADOX.Catalog");

	return 0;
}

void CDBView::FinalRelease()
{
}

LRESULT CDBView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<4, CDBView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_treeCtl);

	IUnknown* p;

	CRect rc(0,0,0,0);
	m_axtreeCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axtreeCtl.AttachControl(m_treeCtl, &p);

	{
		m_catalog->PutActiveConnection(_variant_t((IDispatch*)m_conn));

		for (long i = 0; i < m_catalog->Tables->Count; i++)
		{
			ADOX::_TablePtr table = m_catalog->Tables->Item[_variant_t(i)];

			DWORD item;
			m_treeCtl->InsertItem((DWORD)table.GetInterfacePtr()/*itemdata*/, NULL, NULL, table->Name, -1, 0, &item);
		}
	}

	return 0;
}

LRESULT CDBView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<4, CDBView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_treeCtl);

	return 0;
}

LRESULT CDBView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axtreeCtl.MoveWindow(100, 0, client.right-100, client.bottom);

	return 0;
}

#include "SQLQueryView.h"

HRESULT __stdcall CDBView::OnItemDblClick(DWORD item)
{
	DWORD active;
	m_treeCtl->GetSelectedItem(&active);

	if (active)
	{
		ADOX::_Table* p;
		m_treeCtl->GetItemInfo(active, (DWORD*)&p, NULL, NULL);

		ADOX::_TablePtr table = p;

	// Create SQLQueryView
		CComObject<CUIMDIChild>* child;
		CComObject<CUIMDIChild>::CreateInstance(&child);
		child->AddRef();
		gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&child->m_spFrame);

		{
			CComObject<CSQLQueryView>* pSQLQueryView;
			CComObject<CSQLQueryView>::CreateInstance(&pSQLQueryView);
			if (pSQLQueryView)
			{
				pSQLQueryView->m_pDBView = this;

				WCHAR sql[512];
				swprintf(sql, L"SELECT * FROM %s", (BSTR)table->Name);

				pSQLQueryView->m_sqlEdit->SetText(SysAllocString(sql));

				gApp->m_frame->FindMenu(_Module.GetResourceInstance(), IDR_SQLQUERYVIEW, &pSQLQueryView->m_menu);
				child->AddPage(pSQLQueryView, NULL);
			}
		}

		ATLASSERT(0);
	//	child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);
	}

#if 0
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
#endif

	return S_OK;
}

BEGIN_CMD_MAP(CDBView)
#if 0
// File
	CMD_HANDLER(ID_FILE_NEW, OnFileNew)
	CMD_HANDLER(ID_FILE_OPEN, OnFileOpen)
	CMD_HANDLER(ID_FILE_OPENURL, OnFileOpenURL)

	CMD_HANDLER(ID_FILE_NEWSITE, OnFileNewSite)
	CMD_HANDLER(ID_FILE_OPENSITE, OnFileOpenSite)
	CMD_HANDLER(ID_FILE_MOUNTWORKGROUPSITE, OnFileMountWorkgroupSite)

	CMD_HANDLER(ID_FILE_NEW_NEWSITEM, OnNewNewsItem)

	CMD_HANDLER(ID_FILE_FTPBROWSER, OnFileFTPBrowser)

	CMD_HANDLER(ID_FILE_OPENDATABASE, OnFileOpenDatabase)

// Edit
	CMD_HANDLER(ID_FILE_CUSTOMIZE, OnCustomize)
	CMD_HANDLER(ID_EDIT_OPTIONS, OnOptions)

	CMD_HANDLER(ID_CONVERT_IMPORTDATABASEDATA, OnConvertImportDatabaseData)

// SVGTool
	CMD_HANDLER(ID_SVGTOOL_SELECT, OnSVGTool)
	CMD_UPDATE(ID_SVGTOOL_SELECT, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_DIRECT, OnSVGTool)
	CMD_UPDATE(ID_SVGTOOL_DIRECT, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_CIRCLE, OnSVGTool)
	CMD_UPDATE(ID_SVGTOOL_CIRCLE, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_ELLIPSE, OnSVGTool)
	CMD_UPDATE(ID_SVGTOOL_ELLIPSE, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_RECTANGLE, OnSVGTool)
	CMD_UPDATE(ID_SVGTOOL_RECTANGLE, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_LINE, OnSVGTool)
	CMD_UPDATE(ID_SVGTOOL_LINE, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_PATHPEN, OnSVGTool)
	CMD_UPDATE(ID_SVGTOOL_PATHPEN, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_FREETRANSFORM, OnSVGTool)
	CMD_UPDATE(ID_SVGTOOL_FREETRANSFORM, OnSVGToolUpdate)

//	CMD_HANDLER(ID_FILES_PREFS, OnFilePrefs)

// Edit
//	CMD_HANDLER(ID_EDIT_EMPTYCLIPBOARD, OnEditEmptyClipboard)
//	CMD_UPDATE(ID_EDIT_EMPTYCLIPBOARD, OnEditEmptyClipboardUpdate)

// Help
//	CMD_HANDLER(ID_HELP_TOPICS, OnHelp)
//	CMD_HANDLER(ID_HELP_ABOUT, OnAbout)

//
//	CMD_UPDATE(&ID_TEXT_FACE, OnFontfaceUpdate)
// Window

	CMD_HANDLER(ID_WINDOW_SWATCHLIBRARIES_OPEN, OnSwatchLibrariesOpen)
	CMD_HANDLER(ID_WINDOW_SYMBOLLIBRARIES_OPEN, OnSymbolLibrariesOpen)
	CMD_HANDLER(ID_WINDOW_FILTERLIBRARIES_OPEN, OnFilterLibrariesOpen)
#endif
END_CMD_MAP()
