// CSSStyleSheetView.h : Declaration of the CCSSStyleSheetView

#ifndef __CSSSTYLESHEETVIEW_H_
#define __CSSSTYLESHEETVIEW_H_

#include "resource.h"       // main symbols

namespace System
{
namespace UI
{
class CView;
}

namespace LXmlEdit
{

class CECSSViewGroup;

class CCSSStyleSheetView :
//	public CComCoClass<CCSSStyleSheetView, &CLSID_CSSStyleSheetView>,
//	public ICSSStyleSheetView,

#if 0
	public CUIDialogImpl<CCSSStyleSheetView, CWindowImpl<CCSSStyleSheetView> >,
#endif
		public UI::ProcessTargetCommands	// ILDOMEventListener
//	public ILElementBehavior

//	public ILCSSStyleSheetHandler,
//	public ILDOMEventListener,

//	public IDispEventImpl<1, CCSSStyleSheetView, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>,
//	public IDispEventImpl<2, CCSSStyleSheetView, &DIID__ICSSStyleSheetViewCtlEvents, &LIBID_LXMLEDITORLib, 1, 0>
//	public IDispEventImpl<4, CCSSStyleSheetView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>
{
public:
	CCSSStyleSheetView()
	{
		m_viewGroup = NULL;
		m_bSelectingElement = false;
	}

	int FinalConstruct();

	UI::CView* m_view;

	bool m_bSelectingElement;

	CECSSViewGroup* m_viewGroup;

#if 0
	CAxWindow m_axctl;
	CComQIPtr<ICSSStyleSheetViewCtl> m_ctl;
#endif

	UI::TreeControl* m_treeElement;

//	CComPtr<ILStyleSheetList> m_styleSheetList;
//	CComPtr<ILCSSStyleSheet> m_styleSheet;

#if 0
	void InsertRule(ILXUITreeChildrenElement* treeChildren, ILXUIElement* beforeItem, ILCSSRule* rule, ILXUITreeItemElement* *pVal);
	void PopulateRules(ILXUITreeChildrenElement* parentItem, ILCSSRuleList* ruleList);
#endif

	ErrorCode GetItemText(Web::CSSRule* itemdata, LONG column, System::StringW* * pVal);

	/*
	void PopulateRules(DWORD newItem, ILCSSRuleList* ruleList);
	void PopulateStyleSheets(DWORD parentItem, ILStyleSheetList* styleSheetList);
	void PopulateStyleSheetElements(DWORD parentItem, ILDOMNode* parentNode);
	BOOL AnyLinkStyleChildren(ILDOMNode* parentNode);
	*/

	void __stdcall OnRuleStateChange(Web::CSSRule* rule, long oldState, long newState);
	void __stdcall OnViewGroupSelectionChanged();

#if 0
	void __stdcall OnItemClick(DWORD item);
	void __stdcall OnItemDblClick(DWORD item);
//	void __stdcall OnContextMenu(long x, long y);
//	void __stdcall OnItemExpanding(long item, VARIANT_BOOL bExpanding, BOOL* bCancel);
	void __stdcall OnEndLabelEdit(long item, BSTR text);
#endif

	long OnCreate();
	long OnDestroy();
	//long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

DECLARE_CMD_MAP(CCSSStyleSheetView)

	long OnEditClear(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnEditClearUpdate(long id, UI::IUICmdUpdate* pCmdUI);
	long OnNewImportRule(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnNewStyleRule(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnNewMediaRule(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnNewColorProfile(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnNewRuleUpdate(long id, UI::IUICmdUpdate* pCmdUI);

	long OnDisabledStylesheet(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnDisabledStylesheetUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

// ICSSStyleSheetView
public:
// ILElementBehavior
//	CComPtr<ILElementBehaviorSite> m_behaviorSite;
//	ErrorCode Init(/*[in]*/ ILElementBehaviorSite* pBehaviorSite);
//	ErrorCode Detach();

// IUIDlg
//	ErrorCode(OnActivate)(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView);
	/*
	ErrorCode(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"CSS Declarations");
		return S_OK;
	}
	*/

	ErrorCode OnDragOut(UI::CUIDockBar* dockBar);

#if 0
// ILDOMEventListener
	ErrorCode(handleEvent)(ILDOMEvent* evt);

	ErrorCode(handleCSSEvent)(ILCSSStyleSheet* styleSheet, long type);
#endif

// ICommandTarget
//	ErrorCode(OnCmdMsg)(long nID, long nCode, UI::IUICmdUpdate * pCmdUI, BOOL * bHandled);
};

}	// LXmlEdit
}

#endif //__CSSSTYLESHEETVIEW_H_
