// XPathQueryDlg.h : Declaration of the CXPathQueryDlg

#ifndef __XPATHQUERYDLG_H_
#define __XPATHQUERYDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CXPathQueryDlg : 
	public CAxDialogImpl<CXPathQueryDlg>
{
public:
	CXPathQueryDlg()
	{
	}

	~CXPathQueryDlg()
	{
	}

	CEXMLDocument* m_document;

	enum { IDD = IDD_XPATHQUERYDLG };

	/*
BEGIN_MSG_MAP(CXPathQueryDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDC_XPATH_EVALUATE, OnEvaluate)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
*/
// Handler prototypes:
//  long MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  long CommandHandler(int wNotifyCode, int wID, UI::Control* hWndCtl, BOOL& bHandled);
//  long NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	long OnEvaluate(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnInitDialog(bool& bHandled)
	{
		return 1;  // Let the system set the focus
	}

	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	long OnCancel(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

}	// LXmlEdit
}

#endif //__XPATHQUERYDLG_H_
