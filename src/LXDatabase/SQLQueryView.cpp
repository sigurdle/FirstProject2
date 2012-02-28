// SQLQueryView.cpp : Implementation of CSQLQueryView
#include "stdafx.h"
#include "LXFramework.h"
#include "LXFramework2.h"
#include "SQLQueryView.h"

#include "LXFrameworkApp.h"
#include "LXFrameworkFrame.h"

extern CLXFrameworkApp* gApp;

#include "DBView.h"

void DbError(_com_error &e);

/////////////////////////////////////////////////////////////////////////////
// CSQLQueryView

CSQLQueryView::CSQLQueryView()
{
	m_pDBView = NULL;

	m_size[0] = 50;
	m_size[1] = 25;
	m_size[2] = 25;
}

int CSQLQueryView::FinalConstruct()
{
	m_sqlQueryBuilder.CoCreateInstance(CLSID_SQLQueryBuilder);

	m_sqlEdit.CoCreateInstance(CLSID_UIEdit);

	return 0;
}

void CSQLQueryView::FinalRelease()
{
}

LRESULT CSQLQueryView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IUnknown* p;

	CRect rc(0,0,0,0);

	m_axsqlQueryBuilder.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axsqlQueryBuilder.AttachControl(m_sqlQueryBuilder, &p);

	m_axsqlEdit.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axsqlEdit.AttachControl(m_sqlEdit, &p);

	m_dataGrid.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);

	m_sqlQueryBuilder->put_connstr(m_pDBView->m_conn->ConnectionString);

	return 0;
}

LRESULT CSQLQueryView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CSQLQueryView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	int y;
	int height;

	y = 0;
	height = client.bottom*m_size[0]/100;
	m_axsqlQueryBuilder.MoveWindow(0, 0, client.right, height);

	y += height;
	height = client.bottom*m_size[1]/100;
	m_axsqlEdit.MoveWindow(0, y, client.right, height);

	y += height;
	height = client.bottom-y;
	m_dataGrid.MoveWindow(0, y, client.right, height);

	return 0;
}

BEGIN_CMD_MAP(CSQLQueryView)
	CMD_HANDLER(ID_QUERYDESIGN_RUN, OnQueryRun)
#if 0
// File
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

LRESULT CSQLQueryView::OnQueryRun(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	/*
	WCHAR sql[512];
	//swprintf(sql, L"SELECT id,name FROM websites FOR XML AUTO");
	swprintf(sql, L"SELECT id,name FROM websites");
	*/

	BSTR sql;
	m_sqlEdit->GetText(&sql);

	m_dataGrid.m_rs = NULL;

	try
	{
		ADODB::_CommandPtr cmd;
		cmd.CreateInstance(__uuidof(ADODB::Command));
		cmd->CommandText = sql;
		//cmd->CommandType = ADODB::adCmdText;
		cmd->ActiveConnection = m_pDBView->m_conn;

		//_variant_t va;
		ADODB::_RecordsetPtr rs = cmd->Execute(NULL, NULL/*&va*/, ADODB::adCmdText);

			/*
//		_variant_t va;
		ADODB::_RecordsetPtr rs;// = m_pDBView->m_conn->Execute(sql, &va, ADODB::adCmdText);
//		rs.CreateInstance(L"ADODB.Recordset");//__uuidof(ADODB::Recordset21));
		rs.CreateInstance(__uuidof(ADODB::Recordset));
		rs->Open(sql, _variant_t((IDispatch*)m_pDBView->m_conn), ADODB::adOpenStatic, ADODB::adLockReadOnly, ADODB::adCmdText);
		*/

		m_dataGrid.m_rs = rs;
	}
	catch(_com_error &e)
	{
		DbError(e);
	}

	m_dataGrid.OnSize();
	m_dataGrid.Invalidate();

	return 0;
}
