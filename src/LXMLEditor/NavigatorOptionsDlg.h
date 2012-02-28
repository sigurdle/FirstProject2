#ifndef __NAVIGATOROPTIONSDLG_H_
#define __NAVIGATOROPTIONSDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CNavigatorOptionsDlg : 
	public CAxDialogImpl<CNavigatorOptionsDlg>
{
public:
	CNavigatorOptionsDlg()
	{
	}

	~CNavigatorOptionsDlg()
	{
	}

	LDraw::Color m_color;

	void SetColorIndex();

	enum { IDD = IDD_NAVIGATOROPTIONSDLG };

	long OnColor(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnChangeColorList(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	//long OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	long OnInitDialog();

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

}
}

#endif //__NAVIGATOROPTIONSDLG_H_
