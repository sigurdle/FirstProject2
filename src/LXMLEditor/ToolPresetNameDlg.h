#ifndef __TOOLPRESETNAMEDLG_H_
#define __TOOLPRESETNAMEDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CToolPresetNameDlg : 
	public CAxDialogImpl<CToolPresetNameDlg>
{
public:
	CToolPresetNameDlg()
	{
	}

	~CToolPresetNameDlg()
	{
	}

	System::StringW* m_name;

	enum { IDD = IDD_TOOLPRESETNAMEDLG };

	long OnInitDialog()
	{
#if 0
		SetDlgItemText(IDC_NAME, m_name);
#endif
		return 1;  // Let the system set the focus
	}

	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
#if 0
		GetDlgItemText(IDC_NAME, m_name.GetBuffer(256), 256);
		m_name.ReleaseBuffer();
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

#endif //__TOOLPRESETNAMEDLG_H_
