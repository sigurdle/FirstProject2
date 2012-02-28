// FileInspectorDlg.h : Declaration of the CFileInspectorDlg

#ifndef __FILEINSPECTORDLG_H_
#define __FILEINSPECTORDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

class CSiteFilesView;

/////////////////////////////////////////////////////////////////////////////
// CFileInspectorDlg
class CFileInspectorDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CUIDialogImpl<CFileInspectorDlg, CAxDialogImpl<CFileInspectorDlg> >,
	public IDispEventImpl<1, CFileInspectorDlg, &DIID__ISiteFilesViewEvents, &LIBID_LXWEBSITELib, 1, 0>
{
public:
	CFileInspectorDlg()
	{
		m_app = NULL;
		m_filesView = NULL;
	}

	~CFileInspectorDlg()
	{
	}

	ILXWebSiteApp* m_app;

	CSiteFilesView* m_filesView;

	void SetFilesView(CSiteFilesView* pView);

	void UpdateSelectedItems(ILDOMDocument* document);

	CBrush m_bgBrush;

	enum { IDD = IDD_FILEINSPECTORDLG };

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFileInspectorDlg)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
END_COM_MAP()

BEGIN_SINK_MAP(CFileInspectorDlg)
   SINK_ENTRY_EX(1, DIID__ISiteFilesViewEvents, /*dispid*/1, OnFileSelectionChanged)
END_SINK_MAP()

	void __stdcall OnFileSelectionChanged();

BEGIN_MSG_MAP(CFileInspectorDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtlColorStatic)
	COMMAND_HANDLER(IDC_FILE_PUBLISH, CBN_SELENDOK, OnFileChangePublish)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
//	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCtlColorStatic(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnFileChangePublish(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

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

#endif //__FILEINSPECTORDLG_H_
