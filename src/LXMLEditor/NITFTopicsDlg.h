// NITFTopicsDlg.h : Declaration of the CNITFTopicsDlg

#ifndef __NITFTOPICSDLG_H_
#define __NITFTOPICSDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CNITFTopicsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
	public CAxDialogImpl<CNITFTopicsDlg>
//	public IUITreeControlSite
{
public:
	CNITFTopicsDlg()
	{
	}

	~CNITFTopicsDlg()
	{
	}

	UI::TreeControl* m_subjectsTreeCtl;

	enum { IDD = IDD_NITFTOPICSDLG };

#if 0
	void AddSubjects(ILDOMElement* documentElement, IUITreeItem* parentItem, int topicType, int matchSubject, int matchSubjectMatter);
#endif

	/*
BEGIN_COM_MAP(CNITFTopicsDlg)
//	COM_INTERFACE_ENTRY(IUITreeControlSite)
END_COM_MAP()

BEGIN_MSG_MAP(CNITFTopicsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
*/
// Handler prototypes:
//  long MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  long CommandHandler(int wNotifyCode, int wID, UI::Control* hWndCtl, BOOL& bHandled);
//  long NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	long OnInitDialog(bool& bHandled);

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

// IUITreeControlSite
	ErrorCode GetItemText(ULONG_PTR itemdata, LONG column, System::StringW* * pVal);
};

}
}

#endif //__NITFTOPICSDLG_H_
