// InsertPagesDlg.h : Declaration of the CInsertPagesDlg

#ifndef __INSERTPAGESDLG_H_
#define __INSERTPAGESDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CInsertPagesDlg
class CInsertPagesDlg : 
	public CAxDialogImpl<CInsertPagesDlg>
{
public:
	CInsertPagesDlg()
	{
		m_numPages = 0;
		m_insert = 0;
		m_insertAt = 0;
	}

	~CInsertPagesDlg()
	{
	}

	CComPtr<IPDDocument> m_document;
	long m_numPages;
	long m_insert;
	long m_insertAt;

	enum { IDD = IDD_INSERTPAGESDLG };

BEGIN_MSG_MAP(CInsertPagesDlg)
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
		::SendMessage(GetDlgItem(IDC_INSERTPAGES_INSERT), CB_ADDSTRING, 0, (LPARAM)"After Page");
		::SendMessage(GetDlgItem(IDC_INSERTPAGES_INSERT), CB_ADDSTRING, 0, (LPARAM)"Before Page");
		::SendMessage(GetDlgItem(IDC_INSERTPAGES_INSERT), CB_ADDSTRING, 0, (LPARAM)"At Start of Document");
		::SendMessage(GetDlgItem(IDC_INSERTPAGES_INSERT), CB_ADDSTRING, 0, (LPARAM)"At End of Document");
		::SendMessage(GetDlgItem(IDC_INSERTPAGES_INSERT), CB_SETCURSEL, (WPARAM)m_insert, (LPARAM)0);

		{
			long index = ::SendMessage(GetDlgItem(IDC_INSERTPAGES_MASTER), CB_ADDSTRING, 0, (LPARAM)"[None]");
			::SendMessage(GetDlgItem(IDC_INSERTPAGES_MASTER), CB_SETITEMDATA, index, (LPARAM)NULL);

			CComPtr<IObjectMap> masters;
			m_document->get_masterSpreads(&masters);

			long nmasters;
			masters->get_length(&nmasters);

			for (int i = 0; i < nmasters; i++)
			{
				CComPtr<IPDSpreadMaster> master;
				masters->item(i, (IUnknown**)&master);

				BSTR bprefix;
				master->get_prefix(&bprefix);
				_bstr_t prefix = _bstr_t(bprefix, false);

				BSTR bname;
				master->get_name(&bname);
				_bstr_t name = _bstr_t(bname, false);

				TCHAR buf[256];
				sprintf(buf, _T("%S-%S"), (BSTR)prefix, (BSTR)name);

				long index = ::SendMessage(GetDlgItem(IDC_INSERTPAGES_MASTER), CB_ADDSTRING, 0, (LPARAM)buf);
				::SendMessage(GetDlgItem(IDC_INSERTPAGES_MASTER), CB_SETITEMDATA, index, (LPARAM)master.p);
			}
		}

		SetDlgItemInt(IDC_INSERTPAGES_PAGES, m_numPages);
		SetDlgItemInt(IDC_INSERTPAGES_INSERTNUMBER, m_insertAt+1);

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CComPtr<IObjectMap> pages;
		m_document->get_pages(&pages);
		long npages;
		pages->get_length(&npages);

		m_numPages = GetDlgItemInt(IDC_INSERTPAGES_PAGES);
		if (m_numPages < 1 || m_numPages > 9999)
		{
			MessageBox("Pages must be between 1..9999", MB_OK);
			::SetFocus(GetDlgItem(IDC_INSERTPAGES_PAGES));
			::SendMessage(GetDlgItem(IDC_INSERTPAGES_PAGES), EM_SETSEL, 0, -1);
			return 0;
		}

		m_insert = ::SendMessage(GetDlgItem(IDC_INSERTPAGES_INSERT), CB_GETCURSEL, 0, 0);
		m_insertAt = GetDlgItemInt(IDC_INSERTPAGES_INSERTNUMBER)-1;

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__INSERTPAGESDLG_H_
