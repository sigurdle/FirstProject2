// SMILTransitionsDlg.h : Declaration of the CSMILTransitionsDlg

#ifndef __SMILTRANSITIONSDLG_H_
#define __SMILTRANSITIONSDLG_H_

#include "resource.h"       // main symbols

#include "SVGDefinitionsDlgT.h"

namespace System
{
namespace UI
{
class CView;
}

namespace LXmlEdit
{

class CEXMLViewGroup;

class CSMILTransitionsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSMILTransitionsDlg, &CLSID_SMILTransitionsDlg>,

	public CSVGDefinitionsDlgT<CSMILTransitionsDlg>,
//	public CUIEventHandlerImpl,
public UI::ProcessTargetCommands	// Web::EventListener
//	public IDropTarget
#if 0
	public IDispEventImpl<1, CSMILTransitionsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
#endif
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CSMILTransitionsDlg()
	{
		m_type = 6;

		m_bAnimate = false;
		m_nTimer = 0;
	}

	~CSMILTransitionsDlg()
	{
		TRACE("~CSMILTransitionsDlg()\n");
	}

	int FinalConstruct();

	bool m_bAnimate;
	UINT m_nTimer;

	UI::CView* m_view;

	//CComPtr<IWebXMLDocument> m_document;
	//CComPtr<IEXMLViewGroup> m_viewGroup;
	CEXMLViewGroup* m_viewGroup;

	void BuildItems();
	void AddEventListeners();
	void RemoveEventListeners();

//DECLARE_REGISTRY_RESOURCEID(IDR_SMILTransitionsDlg)

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSMILTransitionsDlg)
	COM_INTERFACE_ENTRY(ISMILTransitionsDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(IDropTarget)
	COM_INTERFACE_ENTRY(Web::EventListener)
END_COM_MAP()
*/

#if 0
BEGIN_SINK_MAP(CSMILTransitionsDlg)
//	SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/3, OnSelectionStyleChanged)
END_SINK_MAP()
#endif

	void __stdcall OnSelectionStyleChanged();

	long OnCreate();
	long OnDestroy();
	long OnTimer();

	long OnClicked(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnDblClicked(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

DECLARE_CMD_MAP(CSMILTransitionsDlg)

	long OnTransitionsNewTransition(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnTransitionsDelete(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnTransitionsPlace(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnTransitionsPlaceUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	long OnSelectAllUnused(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnTransitionsAnimate(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnTransitionsAnimateUpdate(long id, UI::IUICmdUpdate* pCmdUI);

	long OnSmallThumbnails(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(0);
		return 0;
	}

	long OnLargeThumbnails(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(1);
		return 0;
	}

	long OnSmallListView(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(2);
		return 0;
	}

	long OnLargeListView(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(3);
		return 0;
	}

	void OnSmallThumbnailsUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 0);
	}

	void OnLargeThumbnailsUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 1);
	}

	void OnSmallListViewUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 2);
	}

	void OnLargeListViewUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 3);
	}

// ISMILTransitionsDlg
public:
// IDropTarget
#if 0
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
#endif

// Web::EventListener
	void handleEvent(Web::Event* evt);

// IUIEventHandler
//	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

}	// LXmlEdit

}

#endif //__SMILTRANSITIONSDLG_H_
