// EXMLDocumentStyleSheetsView.h : Declaration of the CEXMLDocumentStyleSheetsView

#ifndef __EXMLDOCUMENTSTYLESHEETSVIEW_H_
#define __EXMLDOCUMENTSTYLESHEETSVIEW_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

class CView;

namespace System
{
namespace LXmlEdit
{
class CEXMLViewGroup;

class CEXMLDocumentStyleSheetsView : 
//	public CComCoClass<CEXMLDocumentStyleSheetsView, &CLSID_EXMLDocumentStyleSheetsView>,
//	public IEXMLDocumentStyleSheetsView,

public UI::Control,
//	public CUIDialogImpl<CEXMLDocumentStyleSheetsView, CWindowImpl<CEXMLDocumentStyleSheetsView> >,
//	public CUIEventHandlerImpl,
public UI::ProcessTargetCommands	// ILDOMEventListener

//	public ILCSSStyleSheetHandler,

#if 0
//	public ILDOMEventListener,
	public IDispEventImpl<1, CEXMLDocumentStyleSheetsView, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
//	public IDispEventImpl<4, CEXMLDocumentStyleSheetsView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>
#endif
{
public:
	CEXMLDocumentStyleSheetsView()
	{
		m_app = NULL;
		m_viewGroup = NULL;
	}

	int FinalConstruct();

	CView* m_view;

	ILXMLEditorApp* m_app;

	CEXMLViewGroup* m_viewGroup;

//	CComQIPtr<ICSSStyleSheetViewCtl> m_ctl;
	UI::TreeControl* m_treeCtl;

#if 0
	CImageList m_icons;
#endif

	Web::StyleSheetList* m_styleSheetList;	// TODO remove
	Web::CSSStyleSheet* m_styleSheet;	// TODO remove

#if 0
	void PopulateStyleSheetElements(IUITreeItem* parentItem, Web::Node* parentNode);
#endif

//	void PopulateRules(DWORD newItem, ILCSSRuleList* ruleList);
//	void PopulateStyleSheets(DWORD parentItem, ILStyleSheetList* styleSheetList);
//	void PopulateStyleSheetElements(DWORD parentItem, Web::Node* parentNode);
	bool AnyLinkStyleChildren(Web::Node* parentNode);

//DECLARE_REGISTRY_RESOURCEID(IDR_EXMLDocumentStyleSheetsView)

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEXMLDocumentStyleSheetsView)
	COM_INTERFACE_ENTRY(IEXMLDocumentStyleSheetsView)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
END_COM_MAP()
*/
#if 0
BEGIN_SINK_MAP(CEXMLDocumentStyleSheetsView)
//   SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)

//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/1, OnItemClick)
//	SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/2, OnItemDblClick)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/3, OnContextMenu)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/4, OnItemExpanding)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/6, OnEndLabelEdit)
//   SINK_ENTRY_EX(5, DIID__IWSSrvEvents, /*dispid*/1, OnFileUpdate)
END_SINK_MAP()
#endif

//	HRESULT __stdcall OnFileTreeChanged();

	void __stdcall OnViewGroupSelectionChanged();

#if 0
//	void __stdcall OnItemClick(DWORD item);
	void __stdcall OnItemDblClick(IUITreeItem* item);
//	void __stdcall OnContextMenu(long x, long y);
//	void __stdcall OnItemExpanding(long item, VARIANT_BOOL bExpanding, BOOL* bCancel);
//	void __stdcall OnEndLabelEdit(long item, BSTR text);
#endif

#if 0
	STDMETHOD(handleCSSEvent)(ILCSSStyleSheet* styleSheet, long type);
#endif

	/*
BEGIN_MSG_MAP(CSourceView)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
END_MSG_MAP()
*/
//	long OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	long OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

DECLARE_CMD_MAP(CEXMLDocumentStyleSheetsView)

	long OnEditClear(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnEditClearUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	long OnNewInternalStyleElement(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnNewImportRule(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnNewStyleRule(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnNewRuleUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

	long OnDisabledStylesheet(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnDisabledStylesheetUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

// IEXMLDocumentStyleSheetsView
public:
// IUIDlg
//	STDMETHOD(OnActivate)(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView);
	/*
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"StyleSheets");
		return S_OK;
	}
	*/

#if 0
// ILDOMEventListener
	STDMETHOD(handleEvent)(ILDOMEvent* evt);
#endif

// IUIEventHandler
//	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);

// ICommandTarget
//	STDMETHOD(OnCmdMsg)(long nID, long nCode, UI::IUICmdUpdate * pCmdUI, BOOL * bHandled);
};

}	// LXmlEdit
}

#endif //__EXMLDOCUMENTSTYLESHEETSVIEW_H_
