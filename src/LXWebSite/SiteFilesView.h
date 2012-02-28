// SiteFilesView.h : Declaration of the CSiteFilesView

#ifndef __SITEFILESVIEW_H_
#define __SITEFILESVIEW_H_

//#include "resource.h"       // main symbols

#include "LXWebSiteCP.h"
class CWebSite;

/////////////////////////////////////////////////////////////////////////////
// CSiteFilesView
class ATL_NO_VTABLE CSiteFilesView : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IConnectionPointContainerImpl<CSiteFilesView>,
	public IDispatchImpl<ISiteFilesView, &IID_ISiteFilesView, &LIBID_LXWEBSITELib>,

	public IDispEventImpl<4, CSiteFilesView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<5, CSiteFilesView, &DIID__ILXLocalWebSiteEvents, &LIBID_LXWEBSITELib, 1, 0>,

	public ProcessTargetCommands,
	public IUITreeControlSite,

	public IDropTarget,

	public CUIDialogImpl<CSiteFilesView, CWindowImpl<CSiteFilesView> >,
	public CProxy_ISiteFilesViewEvents< CSiteFilesView >
{
public:

	class CSiteItem;
	class CSiteDir;

	class CSiteItem
	{
	public:
		BYTE m_type;
		CSiteDir* m_parent;
		CWebSite* m_pWebSite;
		WIN32_FIND_DATA m_wfd;
		int m_iIcon;
		long m_cChildren;
		CComPtr<IUITreeItem> m_treeItem;

		CString GetFullDisplayName();

		CSiteItem()
		{
			m_pWebSite = NULL;
			m_treeItem = NULL;
			m_iIcon = 0;
			m_cChildren = 0;
			m_parent = NULL;
			memset(&m_wfd, 0, sizeof(m_wfd));
		}
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

		int m_publish;
	};

	CComPtr<IUIDlg> m_inspectorDlg;

	CSiteFilesView();

	int FinalConstruct();
	void FinalRelease();

	CWebSite*	m_document;

	CAxWindow m_axtreeCtl;
	CComPtr<IUITreeControl> m_treeCtl;

//	DWORD m_rootFolderId;
	_bstr_t m_rootDisplayPath;

	HIMAGELIST	m_hFileIcons;

	IUITreeItem* m_prevDropItem;

	void InitTree();
	void PopulateFolder(IUITreeItem* parentItem, CSiteDir* pParentDir);

	void OnSize();

	HGLOBAL BuildSelectedFilesClipboard();

	CSiteItem * FromElement(CSiteDir* pParentDir, ILDOMElement* element);
	CSiteItem* FindFileById(IUITreeItem* parentItem, long file_id);
	CSiteItem* FindFileByName(IUITreeItem* parentItem, TCHAR* pathName);

//	void OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk);

//DECLARE_REGISTRY_RESOURCEID(IDR_SITEFILESVIEW)
//DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSiteFilesView)
	COM_INTERFACE_ENTRY(ISiteFilesView)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY2(IDispatch, ISiteFilesView)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ICommandTarget)

	COM_INTERFACE_ENTRY(IUITreeControlSite)
	COM_INTERFACE_ENTRY(IDropTarget)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSiteFilesView)
	CONNECTION_POINT_ENTRY(DIID__ISiteFilesViewEvents)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CSiteFilesView)
//   SINK_ENTRY_EX(3, DIID__IWebSiteEvents, /*dispid*/1, OnFileTreeChanged)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/1, OnItemClick)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/2, OnItemDblClick)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/3, OnContextMenu)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/4, OnItemExpanding)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/6, OnEndLabelEdit)
   SINK_ENTRY_EX(5, DIID__ILXLocalWebSiteEvents, /*dispid*/1, OnFileUpdate)
   SINK_ENTRY_EX(5, DIID__ILXLocalWebSiteEvents, /*dispid*/2, OnFileChangeEvent)
END_SINK_MAP()

//	HRESULT __stdcall OnFileTreeChanged();

	HRESULT __stdcall OnItemClick(IUITreeItem* item);
	HRESULT __stdcall OnItemDblClick(IUITreeItem* item);
	HRESULT __stdcall OnContextMenu(long x, long y);
	HRESULT __stdcall OnItemExpanding(IUITreeItem* item, VARIANT_BOOL bExpanding, BOOL* bCancel);
	HRESULT __stdcall OnEndLabelEdit(IUITreeItem* item, BSTR text);

	HRESULT __stdcall OnFileUpdate(long parentFolderId, long fileId, long action);
	void __stdcall OnFileChangeEvent(long action, BSTR pathName);

BEGIN_MSG_MAP(CSiteFilesView)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk);
//	MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
END_MSG_MAP()

	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CSiteFilesView)

	LRESULT OnFileSetasHomepage(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnFileSetasHomepageUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnEditDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnEditDeleteUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnFileNewFolder(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// ISiteFilesView
public:
	STDMETHOD(GetRootFolderId)(/*[out,retval]*/ unsigned long* folder_id);
	STDMETHOD(SetRootFolderId)(/*[in]*/ unsigned long folder_id);
	STDMETHOD(get_webSiteDocument)(/*[out, retval]*/ IWebSite* *pVal);
//	STDMETHOD(put_webSiteDocument)(/*[in]*/ IWebSite* newVal);

// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Files");
		return S_OK;
	}
// IDropTarget
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);

// ICommandTarget
	STDMETHOD(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled);
// IUITreeControlSite
	STDMETHOD(GetItemText)(ULONG itemdata, LONG column, BSTR * pVal);
};

#endif //__SITEFILESVIEW_H_
