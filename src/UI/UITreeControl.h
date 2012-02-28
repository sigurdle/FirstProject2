// UITreeControl.h : Declaration of the CUITreeControl

#ifndef __UITREECONTROL_H_
#define __UITREECONTROL_H_

#include "resource.h"       // main symbols

#include "item.h"
#include "UICP.h"

#define MinIndent	18

/////////////////////////////////////////////////////////////////////////////
// CUITreeControl
class ATL_NO_VTABLE CUITreeControl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComControl<CUITreeControl>,

	public IConnectionPointContainerImpl<CUITreeControl>,
	public IDispatchImpl<IUITreeControl, &IID_IUITreeControl, &LIBID_UILib>,

	public IPersistStreamInitImpl<CUITreeControl>,
	public IOleControlImpl<CUITreeControl>,
	public IOleObjectImpl<CUITreeControl>,
	public IOleInPlaceActiveObjectImpl<CUITreeControl>,
	public IViewObjectExImpl<CUITreeControl>,
	public IOleInPlaceObjectWindowlessImpl<CUITreeControl>,
	public ISupportErrorInfo,
	public IPersistStorageImpl<CUITreeControl>,
	public ISpecifyPropertyPagesImpl<CUITreeControl>,
	public IQuickActivateImpl<CUITreeControl>,
	public IDataObjectImpl<CUITreeControl>,
	public IProvideClassInfo2Impl<&CLSID_UITreeControl, &DIID__IUITreeControlEvents, &LIBID_UILib>,
	public IPropertyNotifySinkCP<CUITreeControl>,

	public IDispEventImpl<1, CUITreeControl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CUITreeControl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<3, CUITreeControl, &DIID__IUIEditEvents	, &LIBID_UILib, 1, 0>,

	public CComCoClass<CUITreeControl, &CLSID_UITreeControl>,
	public CProxy_IUITreeControlEvents< CUITreeControl >
{
public:

	class CTreeColumn
	{
	public:
		_bstr_t m_name;
		int m_width;
		BOOL m_bVisible;
		BOOL	m_bSizeable;
	};

	//class CUITreeControl;

	class CTreeItem :
		public CComObjectRootEx<CComSingleThreadModel>,
		public IDispatchImpl<IUITreeItem, &IID_IUITreeItem, &LIBID_UILib>,
		public C2Obj
	{
	public:
		CTreeItem()
		{
			m_itemData = NULL;
			m_iIndex = -1;
			m_cChildren = 0;

			m_ownerCtl = NULL;
		}

		int FinalConstruct()
		{
			return 0;
		}

		void FinalRelease()
		{
			UPOSITION pos = m_childList.GetHeadPosition();
			while (pos)
			{
				CTreeItem* pItem = (CTreeItem*)(C2Obj*)m_childList.GetNext(pos);
				pItem->Release();
			}
			m_childList.RemoveAll();
		}

		CUITreeControl* m_ownerCtl;

		DWORD m_itemData;
		int m_iIndex;
		long m_cChildren;

		bool CanExpand()
		{
			if (m_cChildren == -1)
				return !m_childList.IsEmpty();
			else
				return m_cChildren != 0;
		}

		int CountExpanded(BOOL bExceptLast)
		{
			int count = 0;
			int nChildren = m_childList.GetCount();

			UPOSITION pos = m_childList.GetHeadPosition();
			for (int i = 0; i < nChildren; i++)
			{
				CTreeItem* pItem = (CTreeItem*)(C2Obj*)m_childList.GetNext(pos);
				count += 1;

				if (i < nChildren-bExceptLast)
				{
					if (pItem->m_expanded && !pItem->m_childList.IsEmpty())
					{
						count += pItem->CountExpanded(FALSE);
					}
				}
			}

			return count;
		}

		void DeselectAll();

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CTreeItem)
		COM_INTERFACE_ENTRY(IUITreeItem)
	END_COM_MAP()

		STDMETHOD(ChildItem)(/*[in]*/ long index, /*[out,retval]*/ IUITreeItem* *pVal)
		{
			if (pVal == NULL) return E_POINTER;

			UPOSITION pos = m_childList.FindIndex(index);
			if (pos)
			{
				CTreeItem* pItem = (CTreeItem*)(C2Obj*)m_childList.GetAt(pos);
				*pVal = pItem;
				(*pVal)->AddRef();
			}
			else
				*pVal = NULL;

			return S_OK;
		}

		STDMETHOD(AppendItem)(/*[in]*/ IUITreeItem* item)
		{
			CTreeItem* pItem = (CTreeItem*)item;

			item->AddRef();
			pItem->m_parent = this;
			m_childList.AddTail((C2Obj*)pItem);

			return S_OK;
		}

		STDMETHOD(GetText)(/*[out,retval]*/ BSTR* pVal);
	};

	CUITreeControl()
	{
		m_bWindowOnly = TRUE;

		m_pTree = NULL;

		m_pSite = NULL;
		m_hImageList = NULL;
		m_Indentation = MinIndent;

		m_dragging = 0;
		m_pane = -1;
		//m_sizeColumn = -1;

		m_ItemHeight = 18;

		m_pActive = NULL;

		COLORREF m_clrBack = RGB(255, 255, 255);
	
		m_clrLines = RGB(
			(255-GetRValue(m_clrBack))/2,
			(255-GetGValue(m_clrBack))/2,
			(255-GetBValue(m_clrBack))/2);

		m_hUxThemeLib = NULL;
		m_hHeaderTheme = NULL;
		m_hTreeViewTheme = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	HINSTANCE m_hUxThemeLib;
	HTHEME m_hHeaderTheme;
	HTHEME m_hTreeViewTheme;

	CComObject<CTreeItem>* m_pTree;
	
	CTreeItem* m_pActive;

	IUITreeControlSite* m_pSite;

	CAxWindow m_axvert;
	CAxWindow m_axhorz;
	CComQIPtr<IUIScrollBar> m_vert;
	CComQIPtr<IUIScrollBar> m_horz;

	HIMAGELIST m_hImageList;
	CArray<CTreeColumn,CTreeColumn&> m_column;
	CArray<int,int> m_columnOrder;

	long m_Indentation;
	long m_ItemHeight;

	int m_dragging;
	int m_oldwidth;
	int m_pane;
//	int m_sizeColumn;
	POINT m_oldpt;

	COLORREF m_clrLines;

	CAxWindow m_axedit;
	CComQIPtr<IUIEdit> m_edit;

	CComPtr<IFontDisp> m_pFont;

	void EndEdit(BOOL bReturn);
	void SizeEdit();

	void DrawColumnHeader(HDC hDC, CRect& rect, int nColumn);
	void ResetVScrollSize();
	void OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk);
	void OnSize();
	void FreeItem(CTreeItem* pItem);

DECLARE_REGISTRY_RESOURCEID(IDR_UITREECONTROL)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUITreeControl)
	COM_INTERFACE_ENTRY(IUITreeControl)
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
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CUITreeControl)
	CONNECTION_POINT_ENTRY(DIID__IUITreeControlEvents)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_PROP_MAP(CUITreeControl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_SINK_MAP(CUITreeControl)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
   SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
   SINK_ENTRY_EX(3, DIID__IUIEditEvents, /*dispid*/2, OnEditChange)
   SINK_ENTRY_EX(3, DIID__IUIEditEvents, /*dispid*/3, OnEditChar)
END_SINK_MAP()

	HRESULT __stdcall OnVertScroll(long code, long pos);
	HRESULT __stdcall OnHorzScroll(long code, long pos);

	HRESULT __stdcall OnEditChange();
	HRESULT __stdcall OnEditChar(WCHAR ch);

BEGIN_MSG_MAP(CUITreeControl)
	CHAIN_MSG_MAP(CComControl<CUITreeControl>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
	MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	MESSAGE_HANDLER(WM_TIMER, OnTimer)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IUITreeControl,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (::InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

	HRESULT OnDraw(ATL_DRAWINFO& di);

// IUITreeControl
public:
	STDMETHOD(UpdateItem)(/*[in]*/ IUITreeItem* item);
	STDMETHOD(get_ItemHeight)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ItemHeight)(/*[in]*/ long newVal);
	STDMETHOD(Expand)(/*[in]*/ IUITreeItem* item, /*[in]*/ TVExpandCode code, /*[out,retval]*/ VARIANT_BOOL* pSuccess);
	STDMETHOD(EditLabel)(/*[in]*/ IUITreeItem* item, /*[out,retval]*/ IUIEdit** ppEdit);
	STDMETHOD(GetItemRect)(/*[in]*/ IUITreeItem* item, /*[in]*/ long pane, /*[in]*/ VARIANT_BOOL bTextOnly, /*[out,retval]*/ RECT* pRect);
	STDMETHOD(GetEditControl)(/*[out,retval]*/ IUIEdit** pEdit);
	STDMETHOD(SetItemState)(/*[in]*/ IUITreeItem* item, /*[in]*/ DWORD state);
	STDMETHOD(HitTest)(/*[in]*/ POINT point, /*[out]*/ DWORD* flags, /*[out,retval]*/ IUITreeItem* *pItem);
	STDMETHOD(DeleteItem)(/*[in]*/ IUITreeItem* item);
	STDMETHOD(SetRootItem)(/*[in]*/ DWORD itemdata, /*[out,retval]*/ IUITreeItem* *pItem);
	STDMETHOD(SetItemInfo)(/*[in]*/ IUITreeItem* item, /*[in]*/ DWORD itemdata, /*[in]*/ long iIndex, /*[in]*/ long cChildren);
	STDMETHOD(GetItemState)(/*[in]*/ IUITreeItem* item, /*[out,retval]*/ DWORD* pVal);
	STDMETHOD(GetLastChildItem)(/*[in]*/ IUITreeItem* item, /*[out,retval]*/ IUITreeItem* * pVal);
	STDMETHOD(GetFirstChildItem)(/*[in]*/ IUITreeItem* item, /*[out,retval]*/ IUITreeItem* *pVal);
	STDMETHOD(GetRootItem)(/*[out,retval]*/ IUITreeItem* *pVal);
	STDMETHOD(GetSelectedItem)(/*[out,retval]*/ IUITreeItem* *pVal);
	STDMETHOD(SetSelectedItem)(/*[in]*/ IUITreeItem* item);
	STDMETHOD(GetPrevSiblingItem)(/*[in]*/ IUITreeItem* item, /*[out,retval]*/ IUITreeItem* *pVal);
	STDMETHOD(GetNextSiblingItem)(/*[in]*/ IUITreeItem* item, /*[out,retval]*/ IUITreeItem* *pVal);
	STDMETHOD(ResetContent)(/*[in]*/ IUITreeItem* item);
	STDMETHOD(GetParentItem)(/*[in]*/ IUITreeItem* item, /*[out,retval]*/ IUITreeItem* *pParent);
	STDMETHOD(GetItemInfo)(/*[in]*/ IUITreeItem* item, /*[out]*/ DWORD* itemdata, /*[out]*/ long* iIndex, /*[out]*/ long* cChildren);
	STDMETHOD(get_Indentation)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Indentation)(/*[in]*/ long newVal);
	STDMETHOD(get_hImageList)(/*[out, retval]*/ DWORD *pVal);
	STDMETHOD(put_hImageList)(/*[in]*/ DWORD newVal);
	STDMETHOD(SetSite)(/*[in]*/ IUITreeControlSite* pSite);
	STDMETHOD(InsertItem)(/*[in]*/ DWORD itemData, /*[in]*/ IUITreeItem* parentItem, /*[in]*/ IUITreeItem* beforeItem, /*[in]*/ BSTR name, long iIndex, /*[in]*/ long cChildren, /*[out,retval]*/ IUITreeItem* *item);
	STDMETHOD(CreateItem)(/*[in]*/ DWORD itemData, /*[in]*/ BSTR name, /*[in]*/ long iIndex, /*[in]*/ long cChildren, /*[out,retval]*/ IUITreeItem* *item);
	STDMETHOD(InsertColumn)(/*[in]*/ long index, /*[in]*/ BSTR name, /*[in]*/ long width, /*[in]*/ BOOL bSizeable, /*[in]*/ BOOL bVisible, /*[out,retval]*/ long* pVal);
};

#endif //__UITREECONTROL_H_
