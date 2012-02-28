// ImageObjectsDlg.cpp : Implementation of CImageObjectsDlg
#include "stdafx.h"
#include "LXImageEditor.h"
#include "Image2.h"
#include "ImageObjectsDlg.h"

/*
#include "WebEditorApp.h"	// TODO remove
#include "WebEditorFrame.h"	// TODO remove
extern CWebEditorApp* gApp;	// TODO remove
*/

/////////////////////////////////////////////////////////////////////////////
// CImageObjectsDlg

LRESULT CImageObjectsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CImageObjectsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CImageObjectsDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

// IUIEventHandler
STDMETHODIMP CImageObjectsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	return S_OK;
}

STDMETHODIMP CImageObjectsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	return S_OK;
}
