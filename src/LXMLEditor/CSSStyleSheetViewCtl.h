#ifndef __CSSSTYLESHEETVIEWCTL_H_
#define __CSSSTYLESHEETVIEWCTL_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class  CCSSStyleSheetViewCtl : 
/*
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ICSSStyleSheetViewCtl, &IID_ICSSStyleSheetViewCtl, &LIBID_LXMLEDITORLib>,
	public CComControl<CCSSStyleSheetViewCtl>,
	public IPersistStreamInitImpl<CCSSStyleSheetViewCtl>,
	public IOleControlImpl<CCSSStyleSheetViewCtl>,
	public IOleObjectImpl<CCSSStyleSheetViewCtl>,
	public IOleInPlaceActiveObjectImpl<CCSSStyleSheetViewCtl>,
	public IViewObjectExImpl<CCSSStyleSheetViewCtl>,
	public IOleInPlaceObjectWindowlessImpl<CCSSStyleSheetViewCtl>,
	public IConnectionPointContainerImpl<CCSSStyleSheetViewCtl>,
	public IPersistStorageImpl<CCSSStyleSheetViewCtl>,
	public ISpecifyPropertyPagesImpl<CCSSStyleSheetViewCtl>,
	public IQuickActivateImpl<CCSSStyleSheetViewCtl>,
	public IDataObjectImpl<CCSSStyleSheetViewCtl>,
	public IProvideClassInfo2Impl<&CLSID_CSSStyleSheetViewCtl, &DIID__ICSSStyleSheetViewCtlEvents, &LIBID_LXMLEDITORLib>,
	public IPropertyNotifySinkCP<CCSSStyleSheetViewCtl>,
//	public CComCoClass<CCSSStyleSheetViewCtl, &CLSID_CSSStyleSheetViewCtl>,
*/
public UI::Control,
	public Web::ICSSStyleSheetHandler

//	public IUITreeControlSite
//	public Web::EventListener,
//	public IDispEventImpl<1, CCSSStyleSheetView, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>,
//	public IDispEventImpl<4, CCSSStyleSheetViewCtl, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>
//	public CProxy_ICSSStyleSheetViewCtlEvents< CCSSStyleSheetViewCtl >
{
public:
	CCSSStyleSheetViewCtl()
	{
//		m_bWindowOnly = TRUE;
	}

	int FinalConstruct();
	void FinalRelease();

	System::StringW* m_userDataKey;

#if 0
	CImageList m_icons;
#endif

//	CEXMLViewGroup* m_viewGroup;

//	CAxWindow m_axtreeCtl;
	UI::TreeControl* m_treeCtl;

	Web::StyleSheetList* m_styleSheetList;
	Web::CSSStyleSheet* m_styleSheet;

#if 0
	void InsertRule(IUITreeItem* parentItem, IUITreeItem* beforeItem, ILCSSRule* rule, IUITreeItem* *pVal);

	void PopulateRules(IUITreeItem* newItem, ILCSSRuleList* ruleList);
	void PopulateStyleSheets(IUITreeItem* parentItem, ILStyleSheetList* styleSheetList);
	void PopulateStyleSheetElements(IUITreeItem* parentItem, ILDOMNode* parentNode);
	BOOL AnyLinkStyleChildren(ILDOMNode* parentNode);
#endif
#if 0
DECLARE_REGISTRY_RESOURCEID(IDR_CSSSTYLESHEETVIEWCTL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCSSStyleSheetViewCtl)
	COM_INTERFACE_ENTRY(ICSSStyleSheetViewCtl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)

//	COM_INTERFACE_ENTRY(Web::EventListener)
	COM_INTERFACE_ENTRY(IUITreeControlSite)

COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CCSSStyleSheetViewCtl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CCSSStyleSheetViewCtl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__ICSSStyleSheetViewCtlEvents)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CCSSStyleSheetViewCtl)
  // SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)

   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/1, OnItemClick)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/2, OnItemDblClick)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/3, OnContextMenu)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/4, OnItemExpanding)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/6, OnEndLabelEdit)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/7, OnItemStateChange)
//   SINK_ENTRY_EX(5, DIID__IWSSrvEvents, /*dispid*/1, OnFileUpdate)
END_SINK_MAP()
#endif
//	HRESULT __stdcall OnFileTreeChanged();

//	void __stdcall OnViewGroupSelectionChanged();

#if 0
	void __stdcall OnItemClick(IUITreeItem* item);
	void __stdcall OnItemDblClick(IUITreeItem* item);
//	void __stdcall OnContextMenu(long x, long y);
//	void __stdcall OnItemExpanding(long item, VARIANT_BOOL bExpanding, BOOL* bCancel);
	void __stdcall OnEndLabelEdit(IUITreeItem* item, BSTR text);
	void __stdcall OnItemStateChange(IUITreeItem* item, long oldState, long newState);
#endif

//	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

// ICSSStyleSheetViewCtl
public:
	ErrorCode AddStyleSheet(System::Object* newItem, Web::CSSStyleSheet* styleSheet);
	ErrorCode DeleteSelection();
	ErrorCode get_styleSheet(/*[out, retval]*/ Web::CSSStyleSheet* *pVal);
	ErrorCode set_styleSheet(/*[in]*/ Web::CSSStyleSheet* newVal);
#if 0
	ErrorCode(SelectRule)(VARIANT vtrule);
#endif

// Web::EventListener
	ErrorCode handleEvent(Web::Event* evt);

#if 0
	ErrorCode handleCSSEvent(/*[in]*/ Web::LCSSObjectType objectType, /*[in]*/ LCSSEventType eventType, /*[in]*/ ILCSSStyleSheet* styleSheet, /*[in]*/ _ObjectImpl* pObject);
#endif

// IUITreeControlSite
	ErrorCode GetItemText(ULONG_PTR itemdata, LONG column, System::StringW* * pVal);
};

}
}

#endif //__CSSSTYLESHEETVIEWCTL_H_
