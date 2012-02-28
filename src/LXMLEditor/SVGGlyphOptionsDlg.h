// SVGGlyphOptionsDlg.h : Declaration of the CSVGGlyphOptionsDlg

#ifndef __SVGGLYPHOPTIONSDLG_H_
#define __SVGGLYPHOPTIONSDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CSVGGlyphOptionsDlg : 
	public CAxDialogImpl<CSVGGlyphOptionsDlg>
{
public:
	CSVGGlyphOptionsDlg()
	{
	}

	~CSVGGlyphOptionsDlg()
	{
	}

	System::StringW* m_unicode;

	enum { IDD = IDD_SVGGLYPHOPTIONSDLG };

	long OnInitDialog(bool& bHandled)
	{
		SetDlgItemText(IDC_GLYPH_UNICODE, m_unicode);

		return 1;  // Let the system set the focus
	}

	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		WCHAR buf[512];

		GetDlgItemText(IDC_GLYPH_UNICODE, buf, sizeof(buf));
		m_unicode = new System::StringW(string_copy(buf));

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

#endif //__SVGGLYPHOPTIONSDLG_H_
