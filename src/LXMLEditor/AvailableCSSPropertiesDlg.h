// AvailableCSSPropertiesDlg.h : Declaration of the CAvailableCSSPropertiesDlg

#ifndef __AVAILABLECSSPROPERTIESDLG_H_
#define __AVAILABLECSSPROPERTIESDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CAvailableCSSPropertiesDlg : 
	public UI::Control
{
public:
	CAvailableCSSPropertiesDlg()
	{
	}

	~CAvailableCSSPropertiesDlg()
	{
	}

	IECSSSelection* m_viewGroup;
	Web::CSSStyleDeclaration* m_style;

	enum { IDD = IDD_AVAILABLECSSPROPERTIESDLG };

	/*
BEGIN_MSG_MAP(CAvailableCSSPropertiesDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_HANDLER(IDC_CSSCATEGORY, LBN_SELCHANGE, OnCategoryChange)
	COMMAND_HANDLER(IDC_CSSPROPERTY, LBN_SELCHANGE, OnPropertyChange)
	COMMAND_HANDLER(IDC_CSSPROPERTY, LBN_DBLCLK, OnPropertyDblClk)
END_MSG_MAP()
*/

// Handler prototypes:
//  long MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  long CommandHandler(int wNotifyCode, int wID, UI::Control* hWndCtl, BOOL& bHandled);
//  long NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

//	long OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnCategoryChange(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnPropertyChange(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnPropertyDblClk(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

/*
	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	long OnCancel(int wNotifyCode, int wID, UI::Control* hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
	*/
};

}	// LXmlEdit
}

#endif //__AVAILABLECSSPROPERTIESDLG_H_
