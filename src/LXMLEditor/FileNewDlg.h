// FileNewDlg.h : Declaration of the CFileNewDlg

#ifndef __FILENEWDLG_H_
#define __FILENEWDLG_H_

#include "resource.h"       // main symbols

#include "SVGElementsListView.h"

namespace System
{
namespace LXmlEdit
{

class CFilesView :
public MSWindows::WindowImpl
//	public IDispEventImpl<1, CFilesView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>
{
public:
	CFilesView()
	{
	}

	UI::TreeControl* m_tree;
	CSVGElementListView m_list;

	System::StringW* m_dir;

	Web::Document* m_filesDocument;

#if 0
	CImageList m_icons;
#endif

	System::StringW* m_pathName;

#if 0
BEGIN_SINK_MAP(CFilesView)
//   SINK_ENTRY_EX(1, DIID__IUITreeControlEvents, /*dispid*/1, OnItemClick)
END_SINK_MAP()

#endif
//	void __stdcall OnItemClick(IUITreeItem* item);

#if 0
BEGIN_MSG_MAP(CFilesView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	COMMAND_HANDLER(10, BN_CLICKED, OnClickFile)
END_MSG_MAP()
#endif

	long OnCreate();
	long OnDestroy();
	long OnSize();

	long OnClickFile(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
};

class CFileNewDlg : 
	public CAxDialogImpl<CFileNewDlg>
{
public:
	CFileNewDlg()
	{
	}

	~CFileNewDlg()
	{
	}

	CFilesView m_view;

	System::StringW* m_pathName;

	enum { IDD = IDD_FILENEWDLG };

	void OnSize();

	/*
BEGIN_MSG_MAP(CFileNewDlg)
//	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
*/
// Handler prototypes:
//  long MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  long CommandHandler(int wNotifyCode, int wID, UI::Control* hWndCtl, BOOL& bHandled);
//  long NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

//	long OnSize();

#if 0
	long OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_view.Create(m_hWnd, CRect(0, 0, 3, 3), NULL, WS_CHILD | WS_VISIBLE);

		OnSize();
		return 1;  // Let the system set the focus
	}
#endif
	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_pathName = m_view.m_pathName;
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

#endif //__FILENEWDLG_H_
