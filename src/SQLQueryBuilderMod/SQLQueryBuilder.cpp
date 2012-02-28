// SQLQueryBuilder.cpp : Implementation of CSQLQueryBuilder

#include "stdafx.h"
#include "SQLQueryBuilderMod.h"
#include "SQLQueryBuilder.h"

#include "SQLQueryFields.h"
#include "SQLQueryTables.h"
#include "SQLTableWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CSQLQueryBuilder

HRESULT CSQLQueryBuilder::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	return S_OK;
}

LRESULT CSQLQueryBuilder::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);

	CComObject<CSQLQueryTablesScroll>::CreateInstance(&m_tablesWnd);
	m_tablesWnd->AddRef();
	m_tablesWnd->Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE, 0);

	CComObject<CSQLQueryFields>::CreateInstance(&m_fieldsWnd);
	m_fieldsWnd->AddRef();
	m_fieldsWnd->Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE, 0);

	return 0;
}

LRESULT CSQLQueryBuilder::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_tablesWnd)
	{
		m_tablesWnd->DestroyWindow();
		m_tablesWnd->Release();
		m_tablesWnd = NULL;
	}

	if (m_fieldsWnd)
	{
		m_fieldsWnd->DestroyWindow();
		m_fieldsWnd->Release();
		m_fieldsWnd = NULL;
	}

	return 0;
}

LRESULT CSQLQueryBuilder::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	Invalidate();
	OnSize();

	return 0;
}

void CSQLQueryBuilder::OnSize()
{
	CRect client;
	GetClientRect(&client);

	m_tablesWnd->MoveWindow(0, 0, client.right, m_splity-2);
	m_fieldsWnd->MoveWindow(0, m_splity+2, client.right, client.bottom-m_splity-4);
}

LRESULT CSQLQueryBuilder::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (!m_dragging)
	{
		SetCapture();
		m_dragging = 1;
	}

	return 0;
}

LRESULT CSQLQueryBuilder::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		ReleaseCapture();
		m_dragging = 0;
	}

	return 0;
}

LRESULT CSQLQueryBuilder::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CRect client;
	GetClientRect(&client);

	if (m_dragging)
	{
		int splity = point.y;
		if (splity < 2) splity = 2;
		if (splity > client.bottom-2) splity = client.bottom-2;

		if (m_splity != splity)
		{
			m_splity = splity;
			OnSize();
		}
	}

	return 0;
}

STDMETHODIMP CSQLQueryBuilder::get_connstr(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_connstr.copy();
	return S_OK;
}

STDMETHODIMP CSQLQueryBuilder::put_connstr(BSTR newVal)
{
	if (m_catalog != NULL)
	{
		m_catalog.Release();
	}

	if (m_conn != NULL)
	{
		m_conn->Close();
		m_conn.Release();
	}

	m_connstr = newVal;

	HRESULT hr;

//	hr = m_conn.CreateInstance(__uuidof(ADODB::C_ConnectionPtr));
	hr = m_conn.CreateInstance(L"ADODB.Connection");

	m_conn->Open(m_connstr, L"", L"", ADODB::adConnectUnspecified);

	m_catalog.CreateInstance(L"ADOX.Catalog");
	m_catalog->PutActiveConnection(_variant_t((IDispatch*)m_conn));

	for (long i = 0; i < m_catalog->Tables->Count; i++)
	{
		ADOX::_TablePtr table = m_catalog->Tables->Item[_variant_t(i)];

		m_tablesWnd->m_wnd->AddTable(table);//m_tables.Add(pTableWnd);
	}

	return S_OK;
}
