// SVGSwatchesDlg.h : Declaration of the CSVGSwatchesDlg

#ifndef __SVGSWATCHESDLG_H_
#define __SVGSWATCHESDLG_H_

#include "resource.h"       // main symbols

#include "SVGDefinitionsDlgT.h"

namespace System
{
namespace LXmlEdit
{

class CEXMLViewGroup;

class CSVGSwatchesDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSVGSwatchesDlg, &CLSID_SVGSwatchesDlg>,

	public CSVGDefinitionsDlgT<CSVGSwatchesDlg>,
//	public CUIEventHandlerImpl,
	public UI::ProcessTargetCommands	// Web::EventListener
//	public IDropTarget

#if 0
	public IDispEventImpl<1, CSVGSwatchesDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
#endif
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CSVGSwatchesDlg()
	{
		m_type = 0;
	}

	int FinalConstruct();

	UI::CView* m_view;

	CEXMLViewGroup* m_viewGroup;

	void BuildItems();
	void AddEventListeners();
	void RemoveEventListeners();

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSVGSwatchesDlg)
	COM_INTERFACE_ENTRY(ISVGSwatchesDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(IDropTarget)
	COM_INTERFACE_ENTRY(Web::EventListener)
END_COM_MAP()
*/
#if 0
BEGIN_SINK_MAP(CSVGSwatchesDlg)
//	SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/3, OnSelectionStyleChanged)
END_SINK_MAP()
#endif
	void __stdcall OnSelectionStyleChanged();

#if 0
BEGIN_MSG_MAP(CSVGSwatchesDlg)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_CLOSE, OnClose)
//	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	COMMAND_HANDLER(1, BN_CLICKED, OnClicked)
	COMMAND_HANDLER(1, BN_DBLCLK, OnDblClicked)
	CHAIN_MSG_MAP(CSVGDefinitionsDlgT<CSVGSwatchesDlg>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
#endif

//	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnCreate();
	long OnDestroy();
//	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	long OnClicked(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnDblClicked(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

DECLARE_CMD_MAP(CSVGSwatchesDlg)

	long OnSwatchesNewSolidColor(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnSwatchesNewLinearGradient(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnSwatchesDefinePattern(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnSwatchesDeleteSwatch(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnSelectAllUnused(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

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

// ISVGSwatchesDlg
public:
#if 0
// IDropTarget
	STDMETHOD(DragEnter)(IDataObject * pDataObject, Dint grfKeyState, POINTL pt, Dint * pdwEffect);
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

#endif //__SVGSWATCHESDLG_H_
