#include "stdafx.h"
#include "LXMLEditor.h"
#include "XMLSchemaAttributesView.h"

namespace System
{
namespace LXmlEdit
{

#define PANE_NAME		0
#define PANE_TYPE		1
#define PANE_USE		2
#define PANE_DEFAULT	3
#define PANE_FIXED	4

/////////////////////////////////////////////////////////////////////////////
// CXMLSchemaAttributesView

#if 0
int CXMLSchemaAttributesView::FinalConstruct()
{
	ErrorCode hr;

//	m_treeCtl.CoCreateInstance(CLSID_UITreeControl);
//	IDispEventImpl<4, CXMLSchemaAttributesView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_treeCtl);

//	m_treeCtl->SetSite(this);

	m_treeCtl->InsertColumn(PANE_NAME, L"Name", 120, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_TYPE, L"Type", 80, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_USE, L"Use", 60, FALSE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_DEFAULT, L"Default", 80, FALSE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_FIXED, L"Fixed", 80, FALSE, TRUE, NULL);

	return S_OK;
}

LRESULT CXMLSchemaAttributesView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IUnknown* p;

	CRect rc(0,0,0,0);
	m_axtreeCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axtreeCtl.AttachControl(m_treeCtl, &p);

	return 0;
}

LRESULT CXMLSchemaAttributesView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CXMLSchemaAttributesView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axtreeCtl.MoveWindow(0, 0, client.right, client.bottom);

	return 0;
}
#endif

ErrorCode __stdcall CXMLSchemaAttributesView::OnItemClick(ULONG_PTR item)
{
	return Success;
}

ErrorCode __stdcall CXMLSchemaAttributesView::OnItemDblClick(ULONG_PTR item)
{
	return Success;
}

ErrorCode CXMLSchemaAttributesView::GetItemText(ULONG_PTR itemdata, LONG column, System::StringW* * pVal)
{
	*pVal = NULL;

//	CSiteItem* pNode = (CSiteItem*)itemdata;

	switch (column)
	{
	case PANE_NAME:
		//*pVal = SysAllocString(_bstr_t(pNode->m_wfd.cFileName));
	break;

	case PANE_TYPE:
		break;

	case PANE_USE:
		{
		}
		break;
	}

	return Success;
}

}	// LXmlEdit
}
