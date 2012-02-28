// SVGMasksDlg.h : Declaration of the CSVGMasksDlg

#ifndef __SVGMASKSDLG_H_
#define __SVGMASKSDLG_H_

#include "resource.h"       // main symbols

#include "SVGDefinitionsDlgT.h"

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CSVGMasksDlg
class CSVGMasksDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSVGMasksDlg, &CLSID_SVGMasksDlg>,
//	public IDispatchImpl<ISVGMasksDlg, &IID_ISVGMasksDlg, &LIBID_LXMLEDITORLib>,

	public CSVGDefinitionsDlgT<CSVGMasksDlg>,
//	public CUIEventHandlerImpl,
public UI::ProcessTargetCommands	// Web::EventListener
//	public IDropTarget,
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CSVGMasksDlg()
	{
		m_type = 3;
	}

	int FinalConstruct();

	CEXMLDocument* m_document;

	void BuildItems();
	void AddEventListeners();
	void RemoveEventListeners();

	long OnCreate();
	long OnDestroy();

	long OnClicked(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

DECLARE_CMD_MAP(CSVGMasksDlg)

//	long OnFiltersNewFilter(int wNotifyCode, int wID, UI::Control* hWndCtl, BOOL& bHandled);
//	long OnFiltersDeleteFilter(int wNotifyCode, int wID, UI::Control* hWndCtl, BOOL& bHandled);
//	long OnSelectAllUnused(int wNotifyCode, int wID, UI::Control* hWndCtl, BOOL& bHandled);

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

// ISVGMasksDlg
public:
// Web::EventListener
	void handleEvent(Web::Event* evt);

// IUIEventHandler
	ErrorCode handleActivateObjectEvent(System::Object* object, long* cookie);
	ErrorCode handleDeactivateObjectEvent(System::Object* object, long cookie, bool* bAllow);
};

}	// LXmlEdit
}

#endif //__SVGMASKSDLG_H_
