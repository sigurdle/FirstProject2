// PathTypeOptionsDlg.h : Declaration of the CPathTypeOptionsDlg

#ifndef __PATHTYPEOPTIONSDLG_H_
#define __PATHTYPEOPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CPathTypeOptionsDlg
class CPathTypeOptionsDlg : 
	public CAxDialogImpl<CPathTypeOptionsDlg>
{
public:
	CPathTypeOptionsDlg()
	{
	}

	~CPathTypeOptionsDlg()
	{
	}

	CArray<IPDPathText*,IPDPathText*> m_targetObjects;

	CComPtr<IUIComboBox> m_alignCtl;

	enum { IDD = IDD_PATHTYPEOPTIONSDLG };

BEGIN_MSG_MAP(CPathTypeOptionsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		GetDlgControl(IDC_PATHTYPE_ALIGN, IID_IUIComboBox, (void**)&m_alignCtl);

		long index[4];

		m_alignCtl->AddString(L"Ascender", &index[PATHTEXTALIGN_ASCENDER]);
		m_alignCtl->SetItemData(index[PATHTEXTALIGN_ASCENDER], PATHTEXTALIGN_ASCENDER);

		m_alignCtl->AddString(L"Descender", &index[PATHTEXTALIGN_DESCENDER]);
		m_alignCtl->SetItemData(index[PATHTEXTALIGN_DESCENDER], PATHTEXTALIGN_DESCENDER);

		m_alignCtl->AddString(L"Center", &index[PATHTEXTALIGN_CENTER]);
		m_alignCtl->SetItemData(index[PATHTEXTALIGN_CENTER], PATHTEXTALIGN_CENTER);

		m_alignCtl->AddString(L"Baseline", &index[PATHTEXTALIGN_BASELINE]);
		m_alignCtl->SetItemData(index[PATHTEXTALIGN_BASELINE], PATHTEXTALIGN_BASELINE);

		PDPathTextAlign align = (PDPathTextAlign)-1;

		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			PDPathTextAlign align2;
			m_targetObjects[i]->get_pathTextAlign(&align2);

			if (i == 0)
			{
				align = align2;
			}
			else if (align != align2)
			{
				align = (PDPathTextAlign)-1;
				break;
			}
		}

		m_alignCtl->put_cursel(align > (PDPathTextAlign)-1? index[align]: -1);

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		long curalign;
		m_alignCtl->get_cursel(&curalign);
		if (curalign > -1)
		{
			PDPathTextAlign align;
			ATLASSERT(sizeof(align) == sizeof(DWORD));
			m_alignCtl->GetItemData(curalign, (DWORD*)&align);

			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				m_targetObjects[i]->put_pathTextAlign(align);
			}
		}

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__PATHTYPEOPTIONSDLG_H_
