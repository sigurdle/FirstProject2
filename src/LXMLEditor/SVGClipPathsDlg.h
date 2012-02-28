// SVGClipPathsDlg.h : Declaration of the CSVGClipPathsDlg

#ifndef __SVGCLIPPATHSDLG_H_
#define __SVGCLIPPATHSDLG_H_

#include "resource.h"       // main symbols

#include "SVGDefinitionsDlgT.h"

class CView;

namespace System
{
namespace LXmlEdit
{

class CEXMLViewGroup;

/////////////////////////////////////////////////////////////////////////////
// CSVGClipPathsDlg
class CSVGClipPathsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSVGClipPathsDlg, &CLSID_SVGClipPathsDlg>,
//	public IDispatchImpl<ISVGClipPathsDlg, &IID_ISVGClipPathsDlg, &LIBID_LXMLEDITORLib>,

	public CSVGDefinitionsDlgT<CSVGClipPathsDlg>,
//	public CUIEventHandlerImpl,
	public UI::ProcessTargetCommands	//  Web::EventListener
//	public IDropTarget,
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CSVGClipPathsDlg()
	{
		m_type = 4;
	}

//	CComPtr<IEXMLDocument> m_document;
	CView* m_view;
	CEXMLViewGroup* m_viewGroup;

	void BuildItems();
	void AddEventListeners();
	void RemoveEventListeners();

	long OnCreate();
	long OnDestroy();
	long OnClicked(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnDblClicked(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

DECLARE_CMD_MAP(CSVGSwatchesDlg)

	long OnClipPathsDefinePattern(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

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

// ISVGClipPathsDlg
public:
// Web::EventListener
	void handleEvent(Web::Event* evt);

// IUIEventHandler
//	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

}	// LXmlEdit
}

#endif //__SVGCLIPPATHSDLG_H_
