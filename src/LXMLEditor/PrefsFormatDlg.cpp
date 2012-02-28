// PrefsFormatDlg.cpp : Implementation of CPrefsFormatDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "PrefsFormatDlg.h"

#include "LXMLEditorApp.h"

#if 0

//extern CArray<CFormatWindow*,CFormatWindow*> m_formatWindows;

COLORREF PreColors[] =
{
	RGB(0, 0, 0),	// black
	RGB(255, 255, 255),	// white

	RGB(128, 0, 0),
	RGB(0, 128, 0),
	RGB(128, 128, 0),
	RGB(0, 0, 128),
	RGB(128, 0, 128),
	RGB(0, 128, 128),

	RGB(128, 128, 128),	// gray
	RGB(160, 160, 160),	// gray
	RGB(192, 192, 192),	// gray

	RGB(192, 0, 0),
	RGB(0, 192, 0),
	RGB(192, 192, 0),
	RGB(0, 0, 192),
	RGB(192, 0, 192),
	RGB(0, 192, 192),

	RGB(255, 0, 0),
	RGB(255, 128, 0),	//
	RGB(0, 255, 0),
	RGB(255, 255, 0),
	RGB(0, 0, 255),
	RGB(255, 0, 255),
	RGB(0, 255, 255),
};

#define NPreColors (sizeof(PreColors)/sizeof(COLORREF))

static int CALLBACK FontFamExProc(
  ENUMLOGFONTEX *lpelfe,    // pointer to logical-font data
  NEWTEXTMETRICEX *lpntme,  // pointer to physical-font data
  int FontType,             // type of font
  LPARAM lParam)             // application-defined data
{
	static char prevFont[512] = {0};

//	HWND hWndComboBox = (HWND)lParam;

	CArray<CPrefsFormatDlg::MLOGFONT,CPrefsFormatDlg::MLOGFONT>* fonts = (CArray<CPrefsFormatDlg::MLOGFONT,CPrefsFormatDlg::MLOGFONT>*)lParam;

	//if (FontType & TRUETYPE_FONTTYPE)
	{
		if (stricmp(lpelfe->elfLogFont.lfFaceName, prevFont) != 0)
		{
			strcpy(prevFont, lpelfe->elfLogFont.lfFaceName);

			/*
			long index = ::SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)prevFont);
			*/
			CPrefsFormatDlg::MLOGFONT mlf;
			mlf.lf = lpelfe->elfLogFont;
			mlf.FontType = FontType;
			fonts->Add(mlf);
		}
	}

	return 1;	// Continue enumeration
}

static int CALLBACK EnumFontSizes(
  ENUMLOGFONTEX *lpelfe,    // pointer to logical-font data
  NEWTEXTMETRICEX *lpntme,  // pointer to physical-font data
  int FontType,             // type of font
  LPARAM lParam)             // application-defined data
{
	HWND hWndComboBox = (HWND)lParam;

	HDC hDC = GetDC(NULL);
	int nPtSize = MulDiv(lpelfe->elfLogFont.lfHeight - lpntme->ntmTm.tmInternalLeading, 72, GetDeviceCaps(hDC, LOGPIXELSY));
	ReleaseDC(NULL, hDC);

	int nCount = ::SendMessage(hWndComboBox, CB_GETCOUNT, 0, 0);
	for (int i = 0; i < nCount; i++)
	{
		long height = ::SendMessage(hWndComboBox, CB_GETITEMDATA, i, 0);
		if (nPtSize == height)
			return 1;		// Continue enumeration
		else if (nPtSize < height)
			break;
	}

	TCHAR buf[64];
	sprintf(buf, _T("%d"), nPtSize);

	::SendMessage(hWndComboBox, CB_INSERTSTRING, i, (LPARAM)buf);
	::SendMessage(hWndComboBox, CB_SETITEMDATA, i, nPtSize);

	return 1;	// Continue enumeration
}

/////////////////////////////////////////////////////////////////////////////
// CPrefsFormatDlg

CPrefsFormatDlg::CPrefsFormatDlg()
{
}

CPrefsFormatDlg::~CPrefsFormatDlg()
{
	for (int i = 0; i < m_formatWindows.GetSize(); i++)
	{
		delete m_formatWindows[i];
	}
	m_formatWindows.RemoveAll();
}

void CPrefsFormatDlg::SetFontSizes()
{
	HWND hWndComboBox = GetDlgItem(IDC_PREFSFORMAT_FONTSIZE);

	::SendMessage(hWndComboBox, CB_RESETCONTENT, 0, 0);

	int index = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_FONTFACE), CB_GETCURSEL, 0, 0);
	if (index >= 0)
	{
		MLOGFONT* pLf = (MLOGFONT*)::SendMessage(GetDlgItem(IDC_PREFSFORMAT_FONTFACE), CB_GETITEMDATA, index, 0);

		if (pLf->FontType & TRUETYPE_FONTTYPE)
		{
			int TTFontSizes[] =
			{
				8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72
			};

			int nCount = sizeof(TTFontSizes)/sizeof(int);
			for (int i = 0; i < nCount; i++)
			{
				TCHAR buf[8];
				sprintf(buf, _T("%d"), TTFontSizes[i]);

				int index = ::SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)buf);
				::SendMessage(hWndComboBox, CB_SETITEMDATA, index, TTFontSizes[i]);
			}
		}
		else
		{
			//HDC	hDC = ::GetDC(NULL);
			HDC hDC = CreateCompatibleDC(NULL);
			LOGFONT	lf = {0};
			lf = pLf->lf;////::SendMessage(GetDlgItem(IDC_PREFSFORMAT_FONTFACE), CB_GETLBTEXT, index, (LPARAM)lf.lfFaceName);
			//lf.lfCharSet = DEFAULT_CHARSET;

			int result = EnumFontFamiliesEx(
				hDC,					// handle to device context
				&lf,					// pointer to logical font information
				(FONTENUMPROC)EnumFontSizes,    // pointer to callback function
				(LPARAM)hWndComboBox,						// application-supplied data
				0);					// reserved; must be zero

			//::ReleaseDC(NULL, hDC);
			DeleteDC(hDC);
		}
	}
}

LRESULT CPrefsFormatDlg::OnChangeWindow(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int index = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_WINDOW), LB_GETCURSEL, 0, 0);
	if (index >= 0)
	{
		CFormatWindow* pWindow = (CFormatWindow*)::SendMessage(GetDlgItem(IDC_PREFSFORMAT_WINDOW), LB_GETITEMDATA, index, 0);

		// Set selected fontname
		{
			::SendMessage(GetDlgItem(IDC_PREFSFORMAT_FONTFACE), CB_SETCURSEL, -1, 0);

			int nCount = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_FONTFACE), CB_GETCOUNT, 0, 0);
			for (int i = 0; i < nCount; i++)
			{
				MLOGFONT* pLf = (MLOGFONT*)::SendMessage(GetDlgItem(IDC_PREFSFORMAT_FONTFACE), CB_GETITEMDATA, i, 0);
				if (!stricmp(pLf->lf.lfFaceName, pWindow->m_lf.lfFaceName))
				{
					::SendMessage(GetDlgItem(IDC_PREFSFORMAT_FONTFACE), CB_SETCURSEL, i, 0);
					break;
				}
			}

			SetFontSizes();

			// Set selected font size
			{
				//HWND hWndComboBox = GetDlgItem(IDC_PREFSFORMAT_FONTSIZE);
				//HWND hWndComboBox = (HWND)lParam;

				HDC hDC = ::CreateCompatibleDC(NULL);

				//HFONT hFont = CreateFontIndirect(&pWindow->m_lf);

				//HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

				//TEXTMETRIC ntmTm;
				//GetTextMetrics(hDC, &ntmTm);

				int nPtSize = -MulDiv(pWindow->m_lf.lfHeight/* - lpntme->ntmTm.tmInternalLeading*/, 72, GetDeviceCaps(hDC, LOGPIXELSY));

				SetDlgItemInt(IDC_PREFSFORMAT_FONTSIZE, nPtSize);

				//SelectObject(hDC, hOldFont);
				//DeleteObject(hFont);
				::DeleteDC(hDC);
			}
		}

		// Fill in available color elements
		{
			::SendMessage(GetDlgItem(IDC_PREFSFORMAT_COLORS), LB_RESETCONTENT, 0, 0);
			for (int i = 0; i < pWindow->m_formatColors.GetSize(); i++)
			{
				index = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_COLORS), LB_ADDSTRING, 0, (LPARAM)(TCHAR*)pWindow->m_formatColors[i]->m_name);
				::SendMessage(GetDlgItem(IDC_PREFSFORMAT_COLORS), LB_SETITEMDATA, index, (LPARAM)pWindow->m_formatColors[i]);
			}
		}
	}

	return 0;
}

void SetCColor(HWND hWnd, COLORREF setclr)
{
	int nCount = ::SendMessage(hWnd, CB_GETCOUNT, 0, 0);
	for (int n = 0; n < nCount; n++)
	{
		COLORREF clr = ::SendMessage(hWnd, CB_GETITEMDATA, n, 0);

		if (setclr == clr)
		{
			::SendMessage(hWnd, CB_SETCURSEL, n, 0);
			return;
		}
	}

	::SendMessage(hWnd, CB_SETCURSEL, -1, 0);
}

LRESULT CPrefsFormatDlg::OnChangeColor(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int index = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_COLORS), LB_GETCURSEL, 0, 0);
	if (index >= 0)
	{
		CFormatColor* pColor = (CFormatColor*)::SendMessage(GetDlgItem(IDC_PREFSFORMAT_COLORS), LB_GETITEMDATA, index, 0);

		SetCColor(GetDlgItem(IDC_PREFSFORMAT_FGCOLOR), pColor->m_fgColor);
		SetCColor(GetDlgItem(IDC_PREFSFORMAT_BGCOLOR), pColor->m_bgColor);
	}

	return 0;
}

LRESULT CPrefsFormatDlg::OnChangeFgColor(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int index = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_COLORS), LB_GETCURSEL, 0, 0);
	if (index >= 0)
	{
		CFormatColor* pColor = (CFormatColor*)::SendMessage(GetDlgItem(IDC_PREFSFORMAT_COLORS), LB_GETITEMDATA, index, 0);

		int index = ::SendMessage(hWndCtl, CB_GETCURSEL, 0, 0);
		if (index >= 0)
		{
			COLORREF clr = ::SendMessage(hWndCtl, CB_GETITEMDATA, index, 0);

			pColor->m_fgColor = clr;
		}
	}

	return 0;
}

LRESULT CPrefsFormatDlg::OnChangeBgColor(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int index = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_COLORS), LB_GETCURSEL, 0, 0);
	if (index >= 0)
	{
		CFormatColor* pColor = (CFormatColor*)::SendMessage(GetDlgItem(IDC_PREFSFORMAT_COLORS), LB_GETITEMDATA, index, 0);

		int index = ::SendMessage(hWndCtl, CB_GETCURSEL, 0, 0);
		if (index >= 0)
		{
			COLORREF clr = ::SendMessage(hWndCtl, CB_GETITEMDATA, index, 0);

			pColor->m_bgColor = clr;
		}
	}

	return 0;
}

LRESULT CPrefsFormatDlg::OnChangeFontFace(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int index = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_WINDOW), LB_GETCURSEL, 0, 0);
	if (index >= 0)
	{
		CFormatWindow* pWindow = (CFormatWindow*)::SendMessage(GetDlgItem(IDC_PREFSFORMAT_WINDOW), LB_GETITEMDATA, index, 0);

		int index = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_FONTFACE), CB_GETCURSEL, 0, 0);
		if (index >= 0)
		{
			MLOGFONT* pLf = (MLOGFONT*)::SendMessage(GetDlgItem(IDC_PREFSFORMAT_FONTFACE), CB_GETITEMDATA, index, 0);

			pWindow->m_lf = pLf->lf;

			SetFontSizes();
		}
	}

	return 0;
}

LRESULT CPrefsFormatDlg::OnChangeFontSize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int nwindow = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_WINDOW), LB_GETCURSEL, 0, 0);
	if (nwindow >= 0)
	{
		CFormatWindow* pWindow = (CFormatWindow*)::SendMessage(GetDlgItem(IDC_PREFSFORMAT_WINDOW), LB_GETITEMDATA, nwindow, 0);

		if (wNotifyCode == CBN_CLOSEUP)
		{
			int index = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_FONTSIZE), CB_GETCURSEL, 0, 0);
			if (index >= 0)
			{
				int nPtSize = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_FONTSIZE), CB_GETITEMDATA, index, 0);

				HDC hDC = ::GetDC(NULL);
				pWindow->m_lf.lfHeight = -MulDiv(nPtSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);
				::ReleaseDC(NULL, hDC);
			}
		}
		else if (wNotifyCode == CBN_EDITCHANGE)
		{
			int nPtSize = GetDlgItemInt(IDC_PREFSFORMAT_FONTSIZE);

			HDC hDC = ::GetDC(NULL);
			pWindow->m_lf.lfHeight = -MulDiv(nPtSize, GetDeviceCaps (hDC, LOGPIXELSY), 72);
			::ReleaseDC(NULL, hDC);
		}
	}

	return 0;
}

LRESULT CPrefsFormatDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int index;

	{
		HDC	hDC = ::GetDC(NULL);
		LOGFONT	lf = {0};
		lf.lfCharSet = DEFAULT_CHARSET;
		
		int result = EnumFontFamiliesEx(
			hDC,					// handle to device context
			&lf,					// pointer to logical font information
			(FONTENUMPROC)FontFamExProc,    // pointer to callback function
			(LPARAM)&m_fonts/*hWndComboBox*/,						// application-supplied data
			0);					// reserved; must be zero

		::ReleaseDC(NULL, hDC);

		HWND hWndComboBox = GetDlgItem(IDC_PREFSFORMAT_FONTFACE);
		for (int i = 0; i < m_fonts.GetSize(); i++)
		{
			long index = ::SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)&m_fonts[i]);
			//::SendMessage(hWndComboBox, CB_SETITEMDATA, index, (LPARAM)&m_fonts[i]);
		}
	}

	for (int i = 0; i < m_formatWindows.GetSize(); i++)
	{
		index = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_WINDOW), LB_ADDSTRING, 0, (LPARAM)(TCHAR*)m_formatWindows[i]->m_name);
		::SendMessage(GetDlgItem(IDC_PREFSFORMAT_WINDOW), LB_SETITEMDATA, index, (LPARAM)m_formatWindows[i]);
	}

	{
		index = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_FGCOLOR), CB_ADDSTRING, 0, (LPARAM)-1);
		//::SendMessage(GetDlgItem(IDC_PREFSFORMAT_FGCOLOR), CB_SETITEMDATA, index, (LPARAM)-1);

		index = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_BGCOLOR), CB_ADDSTRING, 0, (LPARAM)-1);
		//::SendMessage(GetDlgItem(IDC_PREFSFORMAT_BGCOLOR), CB_SETITEMDATA, index, (LPARAM)-1);

		for (int i = 0; i < NPreColors; i++)
		{
			index = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_FGCOLOR), CB_ADDSTRING, 0, (LPARAM)PreColors[i]);
			//::SendMessage(GetDlgItem(IDC_PREFSFORMAT_FGCOLOR), CB_SETITEMDATA, index, );

			index = ::SendMessage(GetDlgItem(IDC_PREFSFORMAT_BGCOLOR), CB_ADDSTRING, 0, (LPARAM)PreColors[i]);
			//::SendMessage(GetDlgItem(IDC_PREFSFORMAT_BGCOLOR), CB_SETITEMDATA, index, );
		}
	}

	return 1;  // Let the system set the focus
}

LRESULT CPrefsFormatDlg::OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT idCtl = (UINT) wParam;             // control identifier 
	LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; // item-drawing information 

	CDCHandle dc(lpdis->hDC);

	if (idCtl == IDC_PREFSFORMAT_FONTFACE)
	{
		if (lpdis->itemID != -1)
		{
			CRect& rcItem = *(CRect*)&lpdis->rcItem;

			CRect trect = rcItem;
			trect.InflateRect(-1, -1);
			trect.left += 16;

			HFONT hOldFont = (HFONT)GetCurrentObject(lpdis->hDC, OBJ_FONT);

			LOGFONT lf;
			GetObject(hOldFont, sizeof(LOGFONT), &lf);
			lf.lfWeight = FW_BOLD;
			HFONT hBoldFont = CreateFontIndirect(&lf);

			MLOGFONT* pLf = (MLOGFONT*)lpdis->itemData;

			if (pLf->lf.lfPitchAndFamily & FIXED_PITCH)
			{
				SelectObject(lpdis->hDC, hBoldFont);
			}

			if (lpdis->itemState & ODS_SELECTED)
				dc.FillSolidRect(rcItem, GetSysColor(COLOR_HIGHLIGHT));
			else
				dc.FillSolidRect(rcItem, GetSysColor(COLOR_WINDOW));

			if (pLf->FontType & TRUETYPE_FONTTYPE)
			{
				HBITMAP hTTBitmap = LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_TT));
				TransparentBlt(lpdis->hDC, rcItem.left+2, rcItem.top+2, 12, 12, hTTBitmap, 0, 0, RGB(255, 255, 255));
				DeleteObject(hTTBitmap);
			}

			if (lpdis->itemState & ODS_SELECTED)
				dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
			else
				dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));

			SetBkMode(lpdis->hDC, TRANSPARENT);

			DrawText(lpdis->hDC, pLf->lf.lfFaceName, lstrlen(pLf->lf.lfFaceName), &trect, DT_SINGLELINE | DT_VCENTER);

			SelectObject(lpdis->hDC, hOldFont);
			DeleteObject(hBoldFont);
		}
	}
	else
	{
		if (lpdis->itemID != -1)
		{
			/*
			TCHAR text[256];
			::SendMessage(lpdis->hwndItem, LB_GETTEXT, lpdis->itemID, (LPARAM)text);
			*/
			COLORREF clr = (COLORREF)lpdis->itemData;//::SendMessage(lpdis->hwndItem, CB_GETITEMDATA, lpdis->itemID, 0);

			CRect& rcItem = *(CRect*)&lpdis->rcItem;

			CRect trect = rcItem;
			trect.InflateRect(-2, -2);

			Rectangle(lpdis->hDC, trect.left, trect.top, trect.right, trect.bottom);

			trect.InflateRect(-1, -1);

			if (clr == -1)
			{
				TCHAR* text = _T("Automatic");
				DrawText(lpdis->hDC, text, lstrlen(text), &trect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			}
			else
			{
				FillSolidRect(lpdis->hDC, &trect, clr);
			}

			/*
			FillSolidRect(lpdis->hDC, &rcItem, (lpdis->itemState & ODS_SELECTED)? GetSysColor(COLOR_HIGHLIGHT): GetSysColor(COLOR_WINDOW));

			CRect selectedRect = rcItem;

			CRect cbrect = rcItem;
			cbrect.right = cbrect.left+18;
			cbrect.InflateRect(-1, -1);
			DrawFrameControl(lpdis->hDC, &cbrect, DFC_BUTTON, DFCS_BUTTONCHECK | (dlgclass->GetDialogsCount() > 0?DFCS_CHECKED: 0));

	  */
	//		FillSolidRect(lpdis->hDC, &selectedRect, (lpdis->itemState & ODS_SELECTED)? GetSysColor(COLOR_HIGHLIGHT): GetSysColor(COLOR_BTNFACE));

			/*
			CRect trect = rcItem;
			trect.left += 22;
			SetTextColor(lpdis->hDC, (lpdis->itemState & ODS_SELECTED)? GetSysColor(COLOR_HIGHLIGHTTEXT): GetSysColor(COLOR_WINDOWTEXT));
			DrawText(lpdis->hDC, text, lstrlen(text), &trect, DT_SINGLELINE | DT_VCENTER);
			*/

			/*
			int oldBk = SetBkMode(lpdis->hDC, TRANSPARENT);
			SetBkMode(lpdis->hDC, oldBk);
			*/
		}
	}

	return 0;
}

LRESULT CPrefsFormatDlg::OnCompareItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT idCtl = wParam;                       // control identifier 
	LPCOMPAREITEMSTRUCT lpcis = (LPCOMPAREITEMSTRUCT)lParam; // structure with items 

	if (idCtl == IDC_PREFSFORMAT_FONTFACE)
	{
		MLOGFONT* pLf1 = (MLOGFONT*)lpcis->itemData1;
		MLOGFONT* pLf2 = (MLOGFONT*)lpcis->itemData2;

		/*
		if (pLf1 == NULL && pLf2 == NULL) return 0;
		else if (pLf1 == NULL) return 1;
		else if (pLf2 == NULL) return -1;
		*/

	// First sort by monospace
		if ((pLf1->lf.lfPitchAndFamily & FIXED_PITCH) &&
			(pLf2->lf.lfPitchAndFamily & FIXED_PITCH))
		{
			// pass on to strcmp below
		}
		else if (pLf1->lf.lfPitchAndFamily & FIXED_PITCH)
		{
			return -1;
		}
		else if (pLf2->lf.lfPitchAndFamily & FIXED_PITCH)
		{
			return 1;
		}

	// Then by name
		return strcmp(pLf1->lf.lfFaceName, pLf2->lf.lfFaceName);
	}
	else
	{
		bHandled = FALSE;
	}

	return 0;
}

#endif