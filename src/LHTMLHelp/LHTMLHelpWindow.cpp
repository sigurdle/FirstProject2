// LHTMLHelpWindow.cpp : Implementation of CLHTMLHelpWindow
#include "stdafx.h"
#include "LHTMLHelp.h"
#include "LHTMLHelpWindow.h"

/// TODO, put this somewhere else
HGLOBAL COleDataObject::GetGlobalData(UINT nClipboardFormat)
{
	FORMATETC fetc = {0};
	fetc.cfFormat = nClipboardFormat;
	fetc.tymed = TYMED_HGLOBAL;
	fetc.dwAspect = DVASPECT_CONTENT;
	fetc.lindex = -1;			//	give me all

	STGMEDIUM medium = {0};
	medium.tymed = TYMED_HGLOBAL;

	HRESULT hr = m_pDataObject->GetData(&fetc, &medium);
	if (SUCCEEDED(hr))
	{
		return medium.hGlobal;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CLHTMLHelpWindow

int CLHTMLHelpWindow::FinalConstruct()
{
	AddMenuResource(IDR_LHTMLHELPWINDOW);

	return 0;
}

#include "HelpView.h"
#include "HelpContentsWnd.h"

LRESULT CLHTMLHelpWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	baseClass::OnCreate(uMsg, wParam, lParam, bHandled);

	EnableDocking(CBRS_ALIGN_ANY);

	m_view = new CHelpView;

	m_hWndClient = m_view->Create(m_hWnd, CRect(0,0,0,0), NULL, WS_VISIBLE | WS_CHILD);

	return 0;
}

STDMETHODIMP CLHTMLHelpWindow::ShowHelp(BSTR pathName, BOOL *success)
{
	CreateEx(this, NULL);

	m_view->m_contents->LoadTOC(pathName, success);

	ShowWindow(SW_SHOW);

#if 0
	m_view.CoCreateInstance(CLSID_HelpView);

	BOOL bsuccess;
	CreateSDIFrame((long)_Module.m_hInst, 0/*IDR_MAINHELP*/, L"Help", m_view, &bsuccess);

	CComQIPtr<IHelpContentsWnd> contents;
	m_view->get_contents(&contents);
	contents->LoadTOC(pathName, NULL);

	if (success)
		*success = TRUE;
#endif

	return S_OK;
}

BEGIN_CMD_MAP(CLHTMLHelpWindow)

END_CMD_MAP()
