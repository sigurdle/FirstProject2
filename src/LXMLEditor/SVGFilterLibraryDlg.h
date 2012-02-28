// SVGFilterLibraryDlg.h : Declaration of the CSVGFilterLibraryDlg

#ifndef __SVGFILTERLIBRARYDLG_H_
#define __SVGFILTERLIBRARYDLG_H_

#include "resource.h"       // main symbols

#include "SVGDefinitionsDlgT.h"

namespace System
{
namespace LXmlEdit
{

class CSVGFilterLibraryDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSVGFilterLibraryDlg, &CLSID_SVGFilterLibraryDlg>,

//	public IDispatchImpl<ISVGFilterLibraryDlg, &IID_ISVGFilterLibraryDlg, &LIBID_LXMLEDITORLib>,

	public CSVGDefinitionsDlgT<CSVGFilterLibraryDlg>,
	public UI::ProcessTargetCommands	// ILDOMEventListener
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CSVGFilterLibraryDlg()
	{
		m_type = 1;
	}

	int FinalConstruct();

	void BuildItems()
	{
		m_listView.RemoveItems();
		AddItems();
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_SVGFILTERLIBRARYDLG)

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSVGFilterLibraryDlg)
	COM_INTERFACE_ENTRY(ISVGFilterLibraryDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
END_COM_MAP()
*/

#if 0
BEGIN_MSG_MAP(CSVGFilterLibraryDlg)
	COMMAND_HANDLER(1, BN_CLICKED, OnClicked)
//	COMMAND_HANDLER(1, BN_DBLCLK, OnDblClicked)
	CHAIN_MSG_MAP(CSVGDefinitionsDlgT<CSVGFilterLibraryDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
#endif
	long OnClicked(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

DECLARE_CMD_MAP(CSVGFilterLibraryDlg)

	long OnFiltersSmallThumbnails(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(0);
		return 0;
	}

	long OnFiltersLargeThumbnails(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(1);
		return 0;
	}

	long OnFiltersSmallListView(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(2);
		return 0;
	}

	long OnFiltersLargeListView(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(3);
		return 0;
	}

	void OnFiltersSmallThumbnailsUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 0);
	}

	void OnFiltersLargeThumbnailsUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 1);
	}

	void OnFiltersSmallListViewUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 2);
	}

	void OnFiltersLargeListViewUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 3);
	}

// ISVGFilterLibraryDlg
public:
	ErrorCode Load(System::StringW* pathName);
};

}	// LXmlEdit
}

#endif //__SVGFILTERLIBRARYDLG_H_
