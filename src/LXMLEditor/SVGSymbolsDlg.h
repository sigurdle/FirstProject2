// SVGSymbolsDlg.h : Declaration of the CSVGSymbolsDlg

#ifndef __SVGSYMBOLSDLG_H_
#define __SVGSYMBOLSDLG_H_

#include "resource.h"       // main symbols

#include "SVGDefinitionsDlgT.h"

namespace System
{
namespace LXmlEdit
{

class CEXMLViewGroup;

class CSVGSymbolsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSVGSymbolsDlg, &CLSID_SVGSymbolsDlg>,
//	public IDispatchImpl<ISVGSymbolsDlg, &IID_ISVGSymbolsDlg, &LIBID_LXMLEDITORLib>,

	public CSVGDefinitionsDlgT<CSVGSymbolsDlg>,
//	public CUIEventHandlerImpl,
	public UI::ProcessTargetCommands	// Web::EventListener
//	public IDropTarget

//	public IDispEventImpl<2, CSVGSymbolsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CSVGSymbolsDlg()
	{
		m_type = 2;
	}

	int FinalConstruct();

	UI::CView* m_view;
	CEXMLViewGroup* m_viewGroup;

	void BuildItems();
	void AddEventListeners();
	void RemoveEventListeners();

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSVGSymbolsDlg)
	COM_INTERFACE_ENTRY(ISVGSymbolsDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(IDropTarget)
	COM_INTERFACE_ENTRY(Web::EventListener)
END_COM_MAP()
*/
#if 0
BEGIN_SINK_MAP(CSVGSymbolsDlg)
//   SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()
#endif

	ErrorCode __stdcall OnDOMEvent(Web::Event* evt);

#if 0
BEGIN_MSG_MAP(CSVGSymbolsDlg)
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
	CHAIN_MSG_MAP(CSVGDefinitionsDlgT<CSVGSymbolsDlg>)
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

DECLARE_CMD_MAP(CSVGSymbolsDlg)

	long OnSymbolDefineSymbol(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnSymbolsNewSymbol(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnSymbolsPlaceSymbol(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnBreakLinkToSymbol(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnBreakLinkToSymbolUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	long OnSymbolSelectAllUnused(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

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

// ISVGSymbolsDlg
public:
#if 0
// IDropTarget
	ErrorCode(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	ErrorCode(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	ErrorCode(DragLeave)();
	ErrorCode(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
#endif
// Web::EventListener
	ErrorCode handleEvent(Web::Event* evt);

// IUIEventHandler
//	ErrorCode(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	ErrorCode(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

}	// LXmlEdit
}

#endif //__SVGSYMBOLSDLG_H_
