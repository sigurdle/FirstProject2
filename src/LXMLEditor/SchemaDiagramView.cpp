// SchemaDiagramView.cpp : Implementation of CSchemaDiagramView
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "SchemaDiagramView.h"

#if 0

//#include "AutoListMembersWindow.h"

//#include "WebXMLViewGroup.h"	// TODO remove
//#include "WebEditorApp.h"	// TODO remove

/////////////////////////////////////////////////////////////////////////////
// CSchemaDiagramView

int CSchemaDiagramView::FinalConstruct()
{
	return 0;
}

void CSchemaDiagramView::FinalRelease()
{
}

LRESULT CSchemaDiagramView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_wndGlobals.m_pSchema = this;
	m_wndGlobals.Create(m_hWnd, CRect(0,0,0,0), NULL, WS_CHILD | WS_VISIBLE);

	CComObject<CXMLSchemaDesignCtl>::CreateInstance(&m_pWndGraph);
	if (m_pWndGraph)
	{
		m_pWndGraph->AddRef();
		m_pWndGraph->m_pSchema = this;
		m_pWndGraph->Create(m_hWnd, CRect(0,0,0,0), NULL, WS_CHILD | WS_VISIBLE);
	}

	return 0;
}

LRESULT CSchemaDiagramView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_pWndGraph)
	{
		m_pWndGraph->DestroyWindow();
		m_pWndGraph->Release();
		m_pWndGraph = NULL;
	}

	return 0;
}

LRESULT CSchemaDiagramView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_wndGlobals.MoveWindow(0, 0, client.right, m_splity-2);
	m_pWndGraph->MoveWindow(0, m_splity+2, client.right, client.bottom-m_splity-2);

	return 0;
}

BEGIN_CMD_MAP(CSchemaDiagramView)
END_CMD_MAP()

#if 0
// ICommandTarget
STDMETHODIMP CSchemaDiagramView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// Then try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	CComQIPtr<ICommandTarget> target;
	
// Try viewgroup
	target = m_viewGroup;
	if (target)
	{
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
	}

	return S_OK;
}

#endif

#endif