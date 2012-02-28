// PrefsClipboardDlg.h : Declaration of the CPrefsClipboardDlg

#ifndef __PREFSCLIPBOARDDLG_H_
#define __PREFSCLIPBOARDDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CPrefsClipboardDlg
class CPrefsClipboardDlg : 
	public CAxPropertyPageImpl<CPrefsClipboardDlg>
{
public:
	CPrefsClipboardDlg()
	{
	}

	~CPrefsClipboardDlg()
	{
	}

	CComQIPtr<IPDApplicationSettings> m_targetObject;

	enum { IDD = IDD_PREFSCLIPBOARDDLG };

BEGIN_MSG_MAP(CPrefsClipboardDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_ID_HANDLER(IDC_CLIPBOARD_PNG, OnCommandChanged)
	COMMAND_ID_HANDLER(IDC_CLIPBOARD_JPEG, OnCommandChanged)
	COMMAND_ID_HANDLER(IDC_CLIPBOARD_GIF, OnCommandChanged)
	CHAIN_MSG_MAP(CAxPropertyPageImpl<CPrefsClipboardDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnCommandChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		SetModified(TRUE);
		return 0;
	}

	BOOL OnApply()
	{
		m_targetObject->put_clipboardSavePNG(IsDlgButtonChecked(IDC_CLIPBOARD_PNG)? VARIANT_TRUE: VARIANT_FALSE);
		m_targetObject->put_clipboardSaveJPEG(IsDlgButtonChecked(IDC_CLIPBOARD_JPEG)? VARIANT_TRUE: VARIANT_FALSE);
		m_targetObject->put_clipboardSaveGIF(IsDlgButtonChecked(IDC_CLIPBOARD_GIF)? VARIANT_TRUE: VARIANT_FALSE);

		return TRUE;
	}

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		VARIANT_BOOL bPng;
		m_targetObject->get_clipboardSavePNG(&bPng);
		CheckDlgButton(IDC_CLIPBOARD_PNG, bPng != 0);

		VARIANT_BOOL bJpeg;
		m_targetObject->get_clipboardSaveJPEG(&bJpeg);
		CheckDlgButton(IDC_CLIPBOARD_JPEG, bJpeg != 0);

		VARIANT_BOOL bGif;
		m_targetObject->get_clipboardSaveGIF(&bGif);
		CheckDlgButton(IDC_CLIPBOARD_GIF, bGif != 0);

		return 1;  // Let the system set the focus
	}
/*
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
	*/
};

#endif //__PREFSCLIPBOARDDLG_H_
