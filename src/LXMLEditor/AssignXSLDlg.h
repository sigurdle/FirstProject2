// AssignXSLDlg.h : Declaration of the CAssignXSLDlg

#ifndef __ASSIGNXSLDLG_H_
#define __ASSIGNXSLDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CAssignXSLDlg : 
	public CAxDialogImpl<CAssignXSLDlg>
{
public:
	CAssignXSLDlg()
	{
	}

	~CAssignXSLDlg()
	{
	}

	System::StringW* m_filepath;

	enum { IDD = IDD_ASSIGNXSLDLG };

	long OnInitDialog()
	{
		SetDlgItemText(IDC_ASSIGNXSL_FILE, m_filepath);

		return 1;  // Let the system set the focus
	}

	long OnLocalBrowse(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
													"Stylesheets (*.xsl,*.xslt)\0*.xsl;*.xslt\0"
													);

		TCHAR sbuffer[4096];
		::strcpy(sbuffer, "");	// Initial filename

		ASSERT(0);
#if 0
		TCHAR curdir[MAX_PATH];
		GetCurrentDirectory(sizeof(curdir), curdir);

		OPENFILENAME	ofn = {0};
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = m_hWnd;
		ofn.hInstance = _Module.m_hInst;
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
		ofn.lpstrFile = sbuffer;
		ofn.nMaxFile = sizeof(sbuffer);
		ofn.lpstrInitialDir = curdir;
		ofn.lpstrFilter = FilesFilter;
		ofn.nFilterIndex = 2;
		
		if (GetOpenFileName(&ofn))
		{
			SetDlgItemText(IDC_ASSIGNXSL_FILE, sbuffer);
		}
#endif
		return 0;
	}

	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		WCHAR buf[4096];
		GetDlgItemText(IDC_ASSIGNXSL_FILE, buf, sizeof(buf));

		m_filepath = new System::StringW(string_copy(buf));

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

#endif //__ASSIGNXSLDLG_H_
