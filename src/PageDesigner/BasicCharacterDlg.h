// BasicCharacterDlg.h : Declaration of the CBasicCharacterDlg

#ifndef __BASICCHARACTERDLG_H_
#define __BASICCHARACTERDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CBasicCharacterDlg
class CBasicCharacterDlg : 
	public CAxPropertyPageImpl<CBasicCharacterDlg>
{
public:
	CBasicCharacterDlg()
	{
	}

	~CBasicCharacterDlg()
	{
	}

	static int CALLBACK FontFamExProc(
	  ENUMLOGFONTEX *lpelfe,    // pointer to logical-font data
	  NEWTEXTMETRICEX *lpntme,  // pointer to physical-font data
	  int FontType,             // type of font
	  LPARAM lParam)             // application-defined data
	{
		static char prevFont[512];

		HWND hWndComboBox = (HWND)lParam;

		if (FontType & TRUETYPE_FONTTYPE)
		{
			if (stricmp(lpelfe->elfLogFont.lfFaceName, prevFont) != 0)
			{
				strcpy(prevFont, lpelfe->elfLogFont.lfFaceName);

				long index = ::SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)prevFont);
			}
		}

		return 1;	// Continue enumeration
	}

	void ScanFonts(HWND hWndComboBox)
	{
		if (TRUE /*!bScannedFonts*/)
		{
			HDC	hDC = ::GetDC(NULL);
			LOGFONT	lf = {0};
			lf.lfCharSet = DEFAULT_CHARSET;
			
			int result = EnumFontFamiliesEx(
				hDC,					// handle to device context
				&lf,					// pointer to logical font information
				(FONTENUMPROC)FontFamExProc,    // pointer to callback function
				(LPARAM)hWndComboBox,						// application-supplied data
				0);					// reserved; must be zero

			::ReleaseDC(NULL, hDC);
		}
	}

	enum { IDD = IDD_BASICCHARACTERDLG };

BEGIN_MSG_MAP(CBasicCharacterDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ScanFonts(GetDlgItem(IDC_CHARACTER_FONT));

		::SendMessage(GetDlgItem(IDC_CHARACTER_SIZE), CB_ADDSTRING, 0, (LPARAM)"6 pt");
		::SendMessage(GetDlgItem(IDC_CHARACTER_SIZE), CB_ADDSTRING, 0, (LPARAM)"8 pt");
		::SendMessage(GetDlgItem(IDC_CHARACTER_SIZE), CB_ADDSTRING, 0, (LPARAM)"9 pt");
		::SendMessage(GetDlgItem(IDC_CHARACTER_SIZE), CB_ADDSTRING, 0, (LPARAM)"10 pt");
		::SendMessage(GetDlgItem(IDC_CHARACTER_SIZE), CB_ADDSTRING, 0, (LPARAM)"11 pt");
		::SendMessage(GetDlgItem(IDC_CHARACTER_SIZE), CB_ADDSTRING, 0, (LPARAM)"12 pt");
		::SendMessage(GetDlgItem(IDC_CHARACTER_SIZE), CB_ADDSTRING, 0, (LPARAM)"14 pt");
		::SendMessage(GetDlgItem(IDC_CHARACTER_SIZE), CB_ADDSTRING, 0, (LPARAM)"18 pt");
		::SendMessage(GetDlgItem(IDC_CHARACTER_SIZE), CB_ADDSTRING, 0, (LPARAM)"24 pt");
		::SendMessage(GetDlgItem(IDC_CHARACTER_SIZE), CB_ADDSTRING, 0, (LPARAM)"30 pt");
		::SendMessage(GetDlgItem(IDC_CHARACTER_SIZE), CB_ADDSTRING, 0, (LPARAM)"36 pt");
		::SendMessage(GetDlgItem(IDC_CHARACTER_SIZE), CB_ADDSTRING, 0, (LPARAM)"48 pt");
		::SendMessage(GetDlgItem(IDC_CHARACTER_SIZE), CB_ADDSTRING, 0, (LPARAM)"60 pt");
		::SendMessage(GetDlgItem(IDC_CHARACTER_SIZE), CB_ADDSTRING, 0, (LPARAM)"72 pt");

		return 1;  // Let the system set the focus
	}
};

#endif //__BASICCHARACTERDLG_H_
