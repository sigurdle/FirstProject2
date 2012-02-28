// FTPBrowser.h : Declaration of the CFTPBrowser

#ifndef __FTPBROWSER_H_
#define __FTPBROWSER_H_

#include "resource.h"       // main symbols
//#include "FTPModCP.h"

#include <wininet.h>

/*
class CSiteItem;
class CSiteDir;
class CFTPBrowser;
*/

class CProgressDlg;

#include "../LXUI/TreeControl.h"

/////////////////////////////////////////////////////////////////////////////
// CFTPBrowser
class FTPEXT CFTPBrowser : public Control
/*
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CFTPBrowser, IFTPBrowser, &IID_IFTPBrowser, &LIBID_FTPMODLib>,
	public CComControl<CFTPBrowser>,
	public IPersistStreamInitImpl<CFTPBrowser>,
	public IOleControlImpl<CFTPBrowser>,
	public IOleObjectImpl<CFTPBrowser>,
	public IOleInPlaceActiveObjectImpl<CFTPBrowser>,
	public IViewObjectExImpl<CFTPBrowser>,
	public IOleInPlaceObjectWindowlessImpl<CFTPBrowser>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CFTPBrowser>,
	public IPersistStorageImpl<CFTPBrowser>,
	public ISpecifyPropertyPagesImpl<CFTPBrowser>,
	public IQuickActivateImpl<CFTPBrowser>,
	public IDataObjectImpl<CFTPBrowser>,
	public IProvideClassInfo2Impl<&CLSID_FTPBrowser, &DIID__IFTPBrowserEvents, &LIBID_FTPMODLib>,
	public IPropertyNotifySinkCP<CFTPBrowser>,
	public CComCoClass<CFTPBrowser, &CLSID_FTPBrowser>,
	public IUITreeControlSite,

	public IDropTarget,

	public IDispEventImpl<3, CFTPBrowser, &DIID__IUIToolbarButtonsEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<4, CFTPBrowser, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>,
	public CProxy_IFTPBrowserEvents< CFTPBrowser >
	*/
{
public:

class CSiteDir;

class CSiteItem : public Object
{
public:
	CSiteDir* m_parent;
	WIN32_FIND_DATA	m_wfd;
	int m_iIcon;
	TreeItem* m_treeItem;

	unsigned m_type : 2,
				m_bFoundOnDisk : 1,
				m_bNew : 1;

	CSiteItem()
	{
		m_treeItem = NULL;
		m_parent = NULL;
		m_type = 0;
		m_bNew = false;
		m_bFoundOnDisk = true;
		memset(&m_wfd, 0, sizeof(m_wfd));
	}

	sysstring GetFullPathName();
};

class CSiteDir : public CSiteItem
{
public:
	CSiteDir();
	~CSiteDir();

	bool m_bPopulated;
/*
	CUPtrList m_childList;
	UPOSITION AddChildTail(CSiteItem* pChild)
	{
		pChild->m_parent = this;
		UPOSITION pos = m_childList.AddTail(pChild);
		return pos;
	}
*/
};

class CSiteFile : public CSiteItem
{
public:
	CSiteFile()
	{
		m_type = 2;
	}
};

	CFTPBrowser();

//	int FinalConstruct();
//	void FinalRelease();

#if 0
	CAxWindow m_axeditCtl;
	CComPtr<IUIEdit> m_editCtl;

	CAxWindow m_axbuttonsCtl;
	CComPtr<IUIToolbarButtons> m_buttonsCtl;
#endif

	TreeControl* m_treeCtl;

	HBITMAP m_hButtonsBitmap;
	HIMAGELIST	m_hFileIcons;

	CSiteDir* m_pRootDir;
	HINTERNET m_hInternet;
	HINTERNET m_hInternetFtp;

	TreeItem* m_prevDropItem;

	sysstring m_ServerName;
	sysstring m_Directory;
	sysstring m_UserName;
	sysstring m_Password;

	INTERNET_PORT m_nPort;
	sysstring m_strServer;

	void OnSize();
	void SetDirectory();
	void PopulateFolder(TreeItem* parentItem, CSiteDir* pParentDir, bool bCheckExisting);

	CSiteItem* FindFileByFileName(TreeItem* parentItem, LPCTSTR filename, int type);
	long CopyMoveFile(CSiteDir* pParentDir, LPCTSTR parentpath , LPCTSTR filepath, bool bSilent, CProgressDlg* dlg);
	long CopyMoveFiles(CSiteDir* pParent, SAFEARRAY* sa, bool bSilent);

	virtual void handleEvent(Event* evt);

	/*
DECLARE_REGISTRY_RESOURCEID(IDR_FTPBROWSER)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFTPBrowser)
	COM_INTERFACE_ENTRY(IFTPBrowser)
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

	COM_INTERFACE_ENTRY(IDropTarget)
	COM_INTERFACE_ENTRY(IUITreeControlSite)
	
COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CFTPBrowser)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
	PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CFTPBrowser)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IFTPBrowserEvents)
END_CONNECTION_POINT_MAP()
*/

#if 0
BEGIN_SINK_MAP(CFTPBrowser)
   SINK_ENTRY_EX(3, DIID__IUIToolbarButtonsEvents, /*dispid*/1, OnToolbarButtonClick)

   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/1, OnItemClick)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/2, OnItemDblClick)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/3, OnContextMenu)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/4, OnItemExpanding)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/6, OnEndLabelEdit)
END_SINK_MAP()
#endif

	void __stdcall OnToolbarButtonClick(long buttonid);

	void __stdcall OnItemClick(TreeItem* item);
	void __stdcall OnItemDblClick(TreeItem* item);
	void __stdcall OnContextMenu(long x, long y);
	void OnItemExpanding(Event* evt);
	void __stdcall OnEndLabelEdit(TreeItem* item, BSTR text);

	/*
BEGIN_MSG_MAP(CFTPBrowser)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	CHAIN_MSG_MAP(CComControl<CFTPBrowser>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
*/
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


	/*
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IFTPBrowser,
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
	*/

// IFTPBrowser
public:
	sysstring get_Directory();
	STDMETHOD(put_Directory)(/*[in]*/ BSTR newVal);
	sysstring get_Password();
	STDMETHOD(put_Password)(/*[in]*/ BSTR newVal);
	sysstring get_UserName();
	STDMETHOD(put_UserName)(/*[in]*/ BSTR newVal);
	sysstring get_ServerName();
	STDMETHOD(put_ServerName)(/*[in]*/ BSTR newVal);
	bool Connect();
	void Disconnect();

	/*
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

		return S_OK;
	}
	OLE_COLOR m_clrBackColor;
	CComPtr<IFontDisp> m_pFont;
	*/

// IDropTarget
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);

// IUITreeControlSite
//	STDMETHOD(GetItemText)(ULONG itemdata, LONG column, BSTR * pVal);
};

#endif //__FTPBROWSER_H_
