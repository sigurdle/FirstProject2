// XMiLFilesControl.h : Declaration of the CXMiLFilesControl

#if 0
#ifndef __XMILFILESCONTROL_H_
#define __XMILFILESCONTROL_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

//class CSiteItem;
//class CSiteDir;
//class CWebSite;

class CProgressDlg;

/////////////////////////////////////////////////////////////////////////////
// CXMiLFilesControl
class ATL_NO_VTABLE CXMiLFilesControl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CXMiLFilesControl, IXMiLFilesControl, &IID_IXMiLFilesControl, &LIBID_LXFRAMEWORKLib>,
	public CComControl<CXMiLFilesControl>,
	public IPersistStreamInitImpl<CXMiLFilesControl>,
	public IOleControlImpl<CXMiLFilesControl>,
	public IOleObjectImpl<CXMiLFilesControl>,
	public IOleInPlaceActiveObjectImpl<CXMiLFilesControl>,
	public IViewObjectExImpl<CXMiLFilesControl>,
	public IOleInPlaceObjectWindowlessImpl<CXMiLFilesControl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CXMiLFilesControl>,
	public IPersistStorageImpl<CXMiLFilesControl>,
	public ISpecifyPropertyPagesImpl<CXMiLFilesControl>,
	public IQuickActivateImpl<CXMiLFilesControl>,
	public IDataObjectImpl<CXMiLFilesControl>,
	public IProvideClassInfo2Impl<&CLSID_XMiLFilesControl, &DIID__IXMiLFilesControlEvents, &LIBID_LXFRAMEWORKLib>,
	public IPropertyNotifySinkCP<CXMiLFilesControl>,
	public CComCoClass<CXMiLFilesControl, &CLSID_XMiLFilesControl>,

	public IUITreeControlSite,
	public IDropTarget,

	public IDispEventImpl<4, CXMiLFilesControl, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>
{
public:
	class CSiteDir;

class CSiteItem
{
public:
	BYTE m_type;
//	BYTE m_bFoundOnDisk;
	CSiteDir* m_parent;
	WIN32_FIND_DATA	m_wfd;
	int m_iIcon;
	long m_cChildren;
	DWORD m_treeItem;

	CSiteItem()
	{
		m_parent = NULL;
		memset(&m_wfd, 0, sizeof(m_wfd));
		m_treeItem = NULL;
		m_iIcon = -1;
		m_cChildren = 0;
	}
	virtual ~CSiteItem()
	{
	}

	_bstr_t GetFullPathName();
};

class CSiteDir : public CSiteItem
{
public:
	CSiteDir()
	{
		m_type = 1;
		m_bPopulated = VARIANT_FALSE;
	}

//	~CSiteDir();

	VARIANT_BOOL m_bPopulated;

/*
	CUPtrList m_childList;
	UPOSITION AddChildTail(CSiteItem* pChild)
	{
		pChild->m_parent = this;
		UPOSITION pos = m_childList.AddTail(pChild);
		return pos;
	}
*/
//	void ScanFTPFiles(BOOL bCheckExisting = FALSE);
};

class CSiteFile : public CSiteItem
{
public:
//	DWORD m_ownerDocument_id;

	CSiteFile()
	{
		m_type = 2;
//		m_ownerDocument_id = 0;
	}

};

	CXMiLFilesControl();

	int FinalConstruct();
	void FinalRelease();

	CAxWindow	m_axtreeCtl;
	CComQIPtr<IUITreeControl> m_treeCtl;

	//DWORD m_rootFolderId;
	_bstr_t m_rootFolderPath;
	_bstr_t m_rootDisplayPath;

	HIMAGELIST	m_hFileIcons;

	DWORD m_prevDropItem;

	CSiteDir* m_pRootDir;

	XMILLWEBLib::ILFileSystemPtr m_filesystem;

	void InitTree();
	void PopulateFolder(DWORD parentItem, CSiteDir* pParentDir);

	void OnSize();

	HGLOBAL BuildSelectedFilesClipboard();

	CSiteItem * FromElement(CSiteDir* pParentDir, ILDOMElement* element);
	CSiteItem* FindFileById(DWORD parentItem, long file_id);

	long CopyMoveFile(TCHAR* parentpath/*CSiteDir* pParent*/, _bstr_t filepath, VARIANT_BOOL bSilent, CProgressDlg* dlg);

DECLARE_REGISTRY_RESOURCEID(IDR_XMILFILESCONTROL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CXMiLFilesControl)
	COM_INTERFACE_ENTRY(IXMiLFilesControl)
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

	COM_INTERFACE_ENTRY(IUITreeControlSite)
	COM_INTERFACE_ENTRY(IDropTarget)

END_COM_MAP()

BEGIN_PROP_MAP(CXMiLFilesControl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CXMiLFilesControl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CXMiLFilesControl)
//   SINK_ENTRY_EX(3, DIID__IWebSiteEvents, /*dispid*/1, OnFileTreeChanged)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/1, OnItemDblClick)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/2, OnItemClick)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/3, OnContextMenu)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/4, OnItemExpanding)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/6, OnEndLabelEdit)
//   SINK_ENTRY_EX(5, DIID__IWSSrvEvents, /*dispid*/1, OnFileUpdate)
END_SINK_MAP()

	HRESULT __stdcall OnItemClick(DWORD item);
	HRESULT __stdcall OnItemDblClick(DWORD item);
	HRESULT __stdcall OnContextMenu(long x, long y);
	HRESULT __stdcall OnItemExpanding(long item, VARIANT_BOOL bExpanding, BOOL* bCancel);
	HRESULT __stdcall OnEndLabelEdit(long item, BSTR text);

	HRESULT __stdcall OnFileUpdate(long parentFolderId, long fileId, long action);

BEGIN_MSG_MAP(CXMiLFilesControl)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	CHAIN_MSG_MAP(CComControl<CXMiLFilesControl>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IXMiLFilesControl,
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

// IXMiLFilesControl
public:
	STDMETHOD(GetItemFullPathName)(/*[in]*/ DWORD item, /*[out,retval]*/ BSTR* pVal);
	STDMETHOD(GetTreeControl)(/*[out,retval]*/ IUITreeControl* *pVal);
	STDMETHOD(SetFileSystemInterface)(/*[in]*/ IUnknown* newVal);
	STDMETHOD(GetRootFolderPath)(/*[out,retval]*/ BSTR* folderPath);
	STDMETHOD(SetRootFolderPath)(/*[in]*/ BSTR folderPath);

	STDMETHOD(CopyMoveFiles)(/*[in]*/ BSTR pathName, /*[in]*/ SAFEARRAY* filepaths, /*[in]*/ VARIANT_BOOL bSilent, /*[out,retval]*/ long* nFilesCopied);

	HRESULT OnDraw(ATL_DRAWINFO& di);
	OLE_COLOR m_clrBackColor;
	BOOL m_bEnabled;
	CComPtr<IFontDisp> m_pFont;

// IDropTarget
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
// IUITreeControlSite
	STDMETHOD(GetItemText)(ULONG itemdata, LONG column, BSTR * pVal);
};

#endif //__XMILFILESCONTROL_H_

#endif