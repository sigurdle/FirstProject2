// AddinsDlg.cpp : Implementation of CAddinsDlg
#include "stdafx.h"
#include "LXFramework.h"
#include "LXFramework2.h"
#include "AddinsDlg.h"

#include "LXFrameworkFrame.h"

/////////////////////////////////////////////////////////////////////////////
// CAddinsDlg

LRESULT CAddinsDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_list = GetDlgItem(IDC_ADDINS_LIST);

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;// | LVCF_SUBITEM;//nMask;
	lvc.fmt = LVCFMT_LEFT;//nFmt;
	lvc.pszText = (LPTSTR)_T("Name");
	lvc.cx = 140;//GetStringWidth(lvc.pszText) + 15;
	//if(nMask & LVCF_SUBITEM)
	lvc.iSubItem = 0;//(nSubItem != -1) ? nSubItem : nItem;
	m_list.InsertColumn(0/*nItem*/, &lvc);

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;//nMask;
	lvc.fmt = LVCFMT_LEFT;//nFmt;
	lvc.pszText = (LPTSTR)_T("Vendor");
	lvc.cx = 140;//GetStringWidth(lvc.pszText) + 15;
	//if(nMask & LVCF_SUBITEM)
	lvc.iSubItem = 1;//(nSubItem != -1) ? nSubItem : nItem;
	m_list.InsertColumn(1/*nItem*/, &lvc);

//	m_list.AddColumn("Name", 0);
//	m_list.AddColumn("Vendor", 1);

	FillList();

	return 1;  // Let the system set the focus
}

void CAddinsDlg::FillList()
{
	USES_CONVERSION;

	for (int i = 0; i < m_pFrame->m_addins.GetSize(); i++)
	{
		LVITEM item;
		item.mask = LVIF_TEXT | LVIF_PARAM;
		item.iItem = 0;//nItem;
		item.iSubItem = 0;
	
		TCHAR name[256];
		strcpy(name, W2A(m_pFrame->m_addins[i]->m_name));	// TODO

		item.pszText = (LPTSTR)name;
		//item.state = nState;
		//item.stateMask = nStateMask;
		//item.iImage = nImage;
		item.lParam = (LPARAM)m_pFrame->m_addins[i];
		m_list.InsertItem(&item);
	}
}

#import "..\UICustomizeMod\UICustomizeMod.tlb"

LRESULT CAddinsDlg::OnAddinCustomize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	LVITEM item;
	item.mask = LVIF_PARAM;
	m_list.GetSelectedItem(&item);

	CLXFrameworkAddinSite* pAddinSite = (CLXFrameworkAddinSite*)item.lParam;

	UICUSTOMIZEMODLib::IUICustomizePtr	customize;
	if (SUCCEEDED(customize.CreateInstance(L"UICustomizeMod.UICustomize")))
	{
		ATLASSERT(0);
#if 0
		CComPtr<IUIManager> uiManager = pAddinSite->m_uiManager;

		customize->Show(uiManager, (long)m_hWnd);
#endif
	}
	else
	{
		MessageBox("Couldn' load Customize object", "LXFramework", MB_OK);
	}
#endif

	return 0;
}

#include "RegisteredSnapinsDlg.h"

LRESULT CAddinsDlg::OnAddinAdd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CRegisteredSnapinsDlg dlg;
	dlg.m_pParent = this;

	if (dlg.DoModal() == IDOK)
	{
	}

	return 0;
}
