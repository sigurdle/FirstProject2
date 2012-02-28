// UICustomize.cpp : Implementation of CUICustomize
#include "stdafx.h"
#include "UICustomizeMod.h"
#include "UICustomize.h"

/////////////////////////////////////////////////////////////////////////////
// CUICustomize

STDMETHODIMP CUICustomize::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUICustomize
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

#include "ToolbarsDlg.h"
#include "CommandsDlg.h"
#include "KeyboardDlg.h"

STDMETHODIMP CUICustomize::Show(IUnknown *uiManager, long hParent)
{
	CPropertySheet* sheet = new CPropertySheet(_T("Customize"), 0, (HWND)hParent);
	sheet->m_psh.dwFlags |= PSH_NOAPPLYNOW;

/*
	CComObject<CToolbarsDlg>*	pToolbars;
	CComObject<CToolbarsDlg>::CreateInstance(&pToolbars);
	pToolbars->AddRef();
	pToolbars->m_uiManager = uiManager;

	CComObject<CCommandsDlg>*	pCommands;
	CComObject<CCommandsDlg>::CreateInstance(&pCommands);
	pCommands->AddRef();
	pCommands->m_uiManager = uiManager;
*/

	CToolbarsDlg* pToolbars = new CToolbarsDlg;
	pToolbars->m_uiManager = CComQIPtr<IUIManager>(uiManager);

	CCommandsDlg* pCommands = new CCommandsDlg;
	pCommands->m_uiManager = CComQIPtr<IUIManager>(uiManager);

	CKeyboardDlg* pKeyboard = new CKeyboardDlg;
	pKeyboard->m_uiManager = CComQIPtr<IUIManager>(uiManager);

	sheet->AddPage(*pToolbars);
	sheet->AddPage(*pCommands);
	sheet->AddPage(*pKeyboard);

	sheet->Create((HWND)hParent);

	return S_OK;
}
