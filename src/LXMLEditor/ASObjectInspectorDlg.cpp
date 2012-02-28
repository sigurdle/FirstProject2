// ASObjectInspectorDlg.cpp : Implementation of CASObjectInspectorDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "ASObjectInspectorDlg.h"

#if 0

/////////////////////////////////////////////////////////////////////////////
// CASObjectInspectorDlg

LRESULT CASObjectInspectorDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
	uiActiveManager->AddEventHandler(this);

	return 0;
}

LRESULT CASObjectInspectorDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
	uiActiveManager->RemoveEventHandler(this);

	return 0;
}

LRESULT CASObjectInspectorDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

// IUIEventHandler
STDMETHODIMP CASObjectInspectorDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	return S_OK;
}

STDMETHODIMP CASObjectInspectorDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	return S_OK;
}

#endif