// UIShellTree.h : Declaration of the CUIShellTree

#ifndef __UISHELLTREE_H_
#define __UISHELLTREE_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

#include <winsock.h>
#include <winnetwk.h>
#include <nspapi.h>
#include <shlobj.h>

// STRUCTURES
typedef struct tagLVID
{
   LPSHELLFOLDER lpsfParent;
   LPITEMIDLIST  lpi;
   ULONG         ulAttribs;
} LVITEMDATA, *LPLVITEMDATA;

typedef struct tagID
{
   LPSHELLFOLDER lpsfParent;
   LPITEMIDLIST  lpi;
   LPITEMIDLIST  lpifq;
} TVITEMDATA, *LPTVITEMDATA;

/////////////////////////////////////////////////////////////////////////////
// CUIShellTree
class ATL_NO_VTABLE CUIShellTree : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CUIShellTree, IUIShellTree, &IID_IUIShellTree, &LIBID_UILib>,
	public CComControl<CUIShellTree>,
	public IPersistStreamInitImpl<CUIShellTree>,
	public IOleControlImpl<CUIShellTree>,
	public IOleObjectImpl<CUIShellTree>,
	public IOleInPlaceActiveObjectImpl<CUIShellTree>,
	public IViewObjectExImpl<CUIShellTree>,
	public IOleInPlaceObjectWindowlessImpl<CUIShellTree>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CUIShellTree>,
	public IPersistStorageImpl<CUIShellTree>,
	public ISpecifyPropertyPagesImpl<CUIShellTree>,
	public IQuickActivateImpl<CUIShellTree>,
	public IDataObjectImpl<CUIShellTree>,
	public IProvideClassInfo2Impl<&CLSID_UIShellTree, &DIID__IUIShellTreeEvents, &LIBID_UILib>,
	public IPropertyNotifySinkCP<CUIShellTree>,
	public CComCoClass<CUIShellTree, &CLSID_UIShellTree>
{
public:
	CUIShellTree()
	{
		m_bWindowOnly = TRUE;
	}

	CTreeViewCtrl m_t;

protected:
	void	FillTreeView(LPSHELLFOLDER lpsf, LPITEMIDLIST  lpifq, HTREEITEM     hParent);
	int		GetIcon(LPITEMIDLIST lpi, UINT uFlags);
	void	GetNormalAndSelectedIcons(LPITEMIDLIST lpifq, LPTV_ITEM lptvitem);
	BOOL	DoTheMenuThing(HWND hwnd, LPSHELLFOLDER lpsfParent, LPITEMIDLIST  lpi, LPPOINT lppt);

    // Functions that deal with PIDLs
    LPITEMIDLIST	ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2);
    LPITEMIDLIST	GetFullyQualPidl(LPSHELLFOLDER lpsf, LPITEMIDLIST lpi);
    LPITEMIDLIST	CopyITEMID(LPMALLOC lpMalloc, LPITEMIDLIST lpi);
    BOOL			GetName(LPSHELLFOLDER lpsf, LPITEMIDLIST  lpi, DWORD dwFlags, LPSTR lpFriendlyName);
    LPITEMIDLIST	CreatePidl(UINT cbSize);
    UINT			GetSize(LPCITEMIDLIST pidl);
    LPITEMIDLIST	Next(LPCITEMIDLIST pidl);

// Attributes
public:
    BOOL m_bOutaHere;

// Operations
public:
 	static int CALLBACK TreeViewCompareProc(LPARAM, LPARAM, LPARAM);
	STDMETHODIMP	PopulateTree();
	void	FolderExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	void	FolderPopup(NMHDR* pNMHDR, LRESULT* pResult);
	BOOL	FolderSelected(NMHDR* pNMHDR, LRESULT* pResult, CString &szFolderPath);
	void	EnableImages();
	BOOL	GetSelectedFolderPath(CString &szFolderPath);

DECLARE_REGISTRY_RESOURCEID(IDR_UISHELLTREE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUIShellTree)
	COM_INTERFACE_ENTRY(IUIShellTree)
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
END_COM_MAP()

BEGIN_PROP_MAP(CUIShellTree)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
//	PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL)	// It's a bug in ATL that this is inserted here?
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CUIShellTree)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CUIShellTree)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	NOTIFY_HANDLER(1, TVN_ITEMEXPANDING, OnItemExpanding)
	CHAIN_MSG_MAP(CComControl<CUIShellTree>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnItemExpanding(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		LRESULT lresult = 0;
		FolderExpanding(pnmh, &lresult);
		return lresult;
	}

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IUIShellTree,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (ATL::InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IUIShellTree
public:

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		/*
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("ATL 3.0 : UIShellTree");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));
			*/

		return S_OK;
	}
	OLE_COLOR m_clrBackColor;
	BOOL m_bEnabled;
	CComPtr<IFontDisp> m_pFont;
};

#endif //__UISHELLTREE_H_
