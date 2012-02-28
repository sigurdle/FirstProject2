// LayerOptionsDlg.h : Declaration of the CLayerOptionsDlg

#ifndef __LAYEROPTIONSDLG_H_
#define __LAYEROPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CLayerOptionsDlg
class CLayerOptionsDlg : 
	public CAxDialogImpl<CLayerOptionsDlg>
{
public:
	CLayerOptionsDlg()
	{
	}

	~CLayerOptionsDlg()
	{
	}

	CArray<IPDLayer*,IPDLayer*> m_targetObjects;

	enum { IDD = IDD_LAYEROPTIONSDLG };

BEGIN_MSG_MAP(CLayerOptionsDlg)
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
	// Name
		if (m_targetObjects.GetSize() > 1)
		{
			::EnableWindow(GetDlgItem(IDC_LAYER_NAME), FALSE);
		}
		else
		{
			BSTR bname;
			m_targetObjects[0]->get_name(&bname);
			SetDlgItemText(IDC_LAYER_NAME, _bstr_t(bname, false));
		}

	// Visible
		{
			VARIANT_BOOL visible;

			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				VARIANT_BOOL visible2;
				m_targetObjects[i]->get_visible(&visible2);

				if (i == 0)
				{
					visible = visible2;
				}
				else if (visible != visible2)
				{
					visible = 2;
					break;
				}
			}

			if (visible == 2)
				::SetWindowLong(GetDlgItem(IDC_LAYER_SHOWLAYER), GWL_STYLE, ::GetWindowLong(GetDlgItem(IDC_LAYER_SHOWLAYER), GWL_STYLE) & ~BST_MASK | BS_AUTO3STATE);
			CheckDlgButton(IDC_LAYER_SHOWLAYER, (visible == -1)? BST_CHECKED: (visible == 0)? BST_UNCHECKED: BST_INDETERMINATE);
		}

	// Locked
		{
			VARIANT_BOOL locked;

			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				VARIANT_BOOL locked2;
				m_targetObjects[i]->get_locked(&locked2);

				if (i == 0)
				{
					locked = locked2;
				}
				else if (locked != locked2)
				{
					locked = 2;
					break;
				}
			}

			if (locked == 2)
				::SetWindowLong(GetDlgItem(IDC_LAYER_LOCKLAYER), GWL_STYLE, ::GetWindowLong(GetDlgItem(IDC_LAYER_LOCKLAYER), GWL_STYLE) & ~BST_MASK | BS_AUTO3STATE);
			CheckDlgButton(IDC_LAYER_LOCKLAYER, (locked == -1)? BST_CHECKED: (locked == 0)? BST_UNCHECKED: BST_INDETERMINATE);
		}

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int i;

	// Name
		if (m_targetObjects.GetSize() == 1)
		{
			TCHAR str[256];
			GetDlgItemText(IDC_LAYER_NAME, str, sizeof(str));
			m_targetObjects[0]->put_name(_bstr_t(str));
		}

	// Visible
		{
			UINT isVisible = IsDlgButtonChecked(IDC_LAYER_SHOWLAYER);

			if (isVisible != BST_INDETERMINATE)
			{
				for (i = 0; i < m_targetObjects.GetSize(); i++)
				{
					m_targetObjects[i]->put_visible((isVisible == BST_CHECKED)? VARIANT_TRUE: VARIANT_FALSE);
				}
			}
		}

	// Locked
		{
			UINT isLocked = IsDlgButtonChecked(IDC_LAYER_LOCKLAYER);

			if (isLocked != BST_INDETERMINATE)
			{
				for (i = 0; i < m_targetObjects.GetSize(); i++)
				{
					m_targetObjects[i]->put_locked((isLocked == BST_CHECKED)? VARIANT_TRUE: VARIANT_FALSE);
				}
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

#endif //__LAYEROPTIONSDLG_H_
