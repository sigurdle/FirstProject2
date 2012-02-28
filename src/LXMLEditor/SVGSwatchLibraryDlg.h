// SVGSwatchLibraryDlg.h : Declaration of the CSVGSwatchLibraryDlg

#ifndef __SVGSWATCHLIBRARYDLG_H_
#define __SVGSWATCHLIBRARYDLG_H_

#include "resource.h"       // main symbols

#include "SVGDefinitionsDlgT.h"

namespace System
{
namespace LXmlEdit
{

class CSVGSwatchLibraryDlg : 
	public CSVGDefinitionsDlgT<CSVGSwatchLibraryDlg>,
		public UI::ProcessTargetCommands	// ILDOMEventListener
{
public:
	CSVGSwatchLibraryDlg()
	{
		m_type = 0;
	}

	int FinalConstruct();

	void BuildItems()
	{
		m_listView.RemoveItems();
		AddItems();
	}

	long OnClicked(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

DECLARE_CMD_MAP(CSVGSwatchLibraryDlg)

	long OnListSmallThumbnails(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(0);
		return 0;
	}

	long OnListLargeThumbnails(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(1);
		return 0;
	}

	long OnListSmallListView(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(2);
		return 0;
	}

	long OnListLargeListView(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(3);
		return 0;
	}

	void OnListSmallThumbnailsUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 0);
	}

	void OnListLargeThumbnailsUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 1);
	}

	void OnListSmallListViewUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 2);
	}

	void OnListLargeListViewUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 3);
	}

// ISVGSwatchLibraryDlg
public:
	ErrorCode Load(/*[in]*/ System::StringW* pathName);
};

}	// LXmlEdit
}

#endif //__SVGSWATCHLIBRARYDLG_H_
