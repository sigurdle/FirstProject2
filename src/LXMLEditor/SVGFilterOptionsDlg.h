// SVGFilterOptionsDlg.h : Declaration of the CSVGFilterOptionsDlg

#ifndef __SVGFILTEROPTIONSDLG_H_
#define __SVGFILTEROPTIONSDLG_H_

#include "resource.h"       // main symbols

//#include "..\Utils\parsenumber.h"

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CSVGFilterOptionsDlg : 
	public CAxDialogImpl<CSVGFilterOptionsDlg>
{
public:
	CSVGFilterOptionsDlg()
	{
	}

	~CSVGFilterOptionsDlg()
	{
	}

	Web::Document* m_document;
	System::StringW* m_id;

	enum { IDD = IDD_SVGFILTEROPTIONSDLG };

	/*
BEGIN_MSG_MAP(CSVGFilterOptionsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
*/
// Handler prototypes:
//  long MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  long CommandHandler(WORD wNotifyCode, WORD wID, UI::Control* hWndCtl, BOOL& bHandled);
//  long NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	long OnInitDialog()
	{
		SetDlgItemText(IDC_ID, m_id);

		return 1;  // Let the system set the focus
	}

	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		ASSERT(0);
#if 0
		TCHAR buf[256];

		GetDlgItemText(IDC_ID, buf, sizeof(buf));
		_bstr_t id = buf;

		id = stripspaces(id);

		if (id.length() == 0)
		{
			MessageBox("Invalid id", "WebEditor", MB_OK);
			return 0;
		}

		CComPtr<ILDOMElement> element;
		m_document->getElementById(id, &element);
		if (element != NULL)
		{
			MessageBox("An element with that id already exists", "WebEditor", MB_OK);
			return 0;
		}

		m_id = id;
#endif
		EndDialog(wID);

		return 0;
	}

	long OnCancel(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

}
}

#endif //__SVGFILTEROPTIONSDLG_H_
