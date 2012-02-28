#ifndef __PREFSFORMATDLG_H_
#define __PREFSFORMATDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CFormatWindow;

class CPrefsFormatDlg : 
	public CAxPropertyPageImpl<CPrefsFormatDlg>
{
public:
	struct MLOGFONT
	{
//		LOGFONT lf;
		int FontType;
	};

	CPrefsFormatDlg();
	~CPrefsFormatDlg();

	Array<MLOGFONT> m_fonts;

	Array<CFormatWindow*> m_formatWindows;

	enum { IDD = IDD_PREFSFORMATDLG };

	void SetFontSizes();

	long OnChangeWindow(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnChangeColor(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnChangeFgColor(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnChangeBgColor(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnChangeFontFace(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnChangeFontSize(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

//	long OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	long OnCompareItem(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	long OnInitDialog();

	bool OnApply()
	{
//		m_tabSize = GetDlgItemInt(IDC_TABS_TABSIZE);

		return true;
	}

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

}
}

#endif //__PREFSFORMATDLG_H_
