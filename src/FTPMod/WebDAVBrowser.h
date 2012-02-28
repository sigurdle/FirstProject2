// WebDAVBrowser.h : Declaration of the CWebDAVBrowser

#ifndef __WEBDAVBROWSER_H_
#define __WEBDAVBROWSER_H_

#if 0
#include "resource.h"       // main symbols
#include <atlctl.h>


/////////////////////////////////////////////////////////////////////////////
// CWebDAVBrowser
class ATL_NO_VTABLE CWebDAVBrowser : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IWebDAVBrowser, &IID_IWebDAVBrowser, &LIBID_FTPMODLib>,
	public CComControl<CWebDAVBrowser>,
	public IPersistStreamInitImpl<CWebDAVBrowser>,
	public IOleControlImpl<CWebDAVBrowser>,
	public IOleObjectImpl<CWebDAVBrowser>,
	public IOleInPlaceActiveObjectImpl<CWebDAVBrowser>,
	public IViewObjectExImpl<CWebDAVBrowser>,
	public IOleInPlaceObjectWindowlessImpl<CWebDAVBrowser>,
	public IConnectionPointContainerImpl<CWebDAVBrowser>,
	public IPersistStorageImpl<CWebDAVBrowser>,
	public ISpecifyPropertyPagesImpl<CWebDAVBrowser>,
	public IQuickActivateImpl<CWebDAVBrowser>,
	public IDataObjectImpl<CWebDAVBrowser>,
	public IProvideClassInfo2Impl<&CLSID_WebDAVBrowser, &DIID__IWebDAVBrowserEvents, &LIBID_FTPMODLib>,
	public IPropertyNotifySinkCP<CWebDAVBrowser>,
	public CComCoClass<CWebDAVBrowser, &CLSID_WebDAVBrowser>,

	public IUITreeControlSite,
	public IDispEventImpl<3, CWebDAVBrowser, &DIID__IUIToolbarButtonsEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<4, CWebDAVBrowser, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>
{
public:
	class CSiteDir;

	class CSiteItem
	{
	public:
		CSiteDir* m_parent;

		CComBSTR m_displayName;
		DATE	m_creationDate;
		DATE	m_lastModifiedDate;

		int m_iIcon;
		CComPtr<IUITreeItem> m_treeItem;

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

			m_creationDate = 0;
			m_lastModifiedDate = 0;
		}

		CComBSTR GetFullPathName();
	};

	class CSiteDir : public CSiteItem
	{
	public:
		CSiteDir();
		~CSiteDir();

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
	};

	class CSiteFile : public CSiteItem
	{
	public:
		DWORD m_contentLength;

		CSiteFile()
		{
			m_type = 2;
			m_contentLength =  0;
		}
	};

	CWebDAVBrowser()
	{
		m_bWindowOnly = TRUE;

		m_hInternet = NULL;
		m_hInternetHttp = NULL;

		m_pRootDir = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	CSiteDir* m_pRootDir;

	CAxWindow m_axeditCtl;
	CComPtr<IUIEdit> m_editCtl;

	CAxWindow m_axbuttonsCtl;
	CComPtr<IUIToolbarButtons> m_buttonsCtl;

	CAxWindow m_axtreeCtl;
	CComPtr<IUITreeControl> m_treeCtl;

	HBITMAP m_hButtonsBitmap;
	HIMAGELIST	m_hFileIcons;

	HINTERNET m_hInternet;
	HINTERNET m_hInternetHttp;

	_bstr_t m_ServerName;
	CComBSTR m_Directory;
	_bstr_t m_UserName;
	_bstr_t m_Password;

	DWORD m_dwSecureFlag;

	void OnSize();
	void SetDirectory();
	void PopulateFolder(IUITreeItem* parentItem, CSiteDir* pParentDir, bool bCheckExisting);

DECLARE_REGISTRY_RESOURCEID(IDR_WEBDAVBROWSER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CWebDAVBrowser)
	COM_INTERFACE_ENTRY(IWebDAVBrowser)
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

	COM_INTERFACE_ENTRY(IUITreeControlSite)
END_COM_MAP()

BEGIN_PROP_MAP(CWebDAVBrowser)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CWebDAVBrowser)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CWebDAVBrowser)
   SINK_ENTRY_EX(3, DIID__IUIToolbarButtonsEvents, /*dispid*/1, OnToolbarButtonClick)

//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/1, OnItemClick)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/2, OnItemDblClick)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/3, OnContextMenu)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/4, OnItemExpanding)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/6, OnEndLabelEdit)
END_SINK_MAP()

	HRESULT __stdcall OnToolbarButtonClick(long buttonid);

	HRESULT __stdcall OnItemDblClick(IUITreeItem* item);
	HRESULT __stdcall OnItemExpanding(IUITreeItem* item, VARIANT_BOOL bExpanding, BOOL* bCancel);
	HRESULT __stdcall OnEndLabelEdit(IUITreeItem* item, BSTR text);

BEGIN_MSG_MAP(CWebDAVBrowser)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	CHAIN_MSG_MAP(CComControl<CWebDAVBrowser>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IWebDAVBrowser
public:
	STDMETHOD(get_Directory)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Directory)(/*[in]*/ BSTR newVal);
	STDMETHOD(Connect)(/*[out,retval]*/ VARIANT_BOOL* pSuccess);
	STDMETHOD(Disconnect)();

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

		return S_OK;
	}

// IUITreeControlSite
	STDMETHOD(GetItemText)(ULONG itemdata, LONG column, BSTR * pVal);
};

#endif

#endif //__WEBDAVBROWSER_H_
