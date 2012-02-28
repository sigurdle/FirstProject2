// SiteFilesView.h : Declaration of the CSiteFilesView

#ifndef __SITEFILESVIEW_H_
#define __SITEFILESVIEW_H_

#include "resource.h"       // main symbols

class CSiteItem;
class CSiteDir;
class CWebSite;

class CSiteItem
{
public:
	BYTE m_type;
	BYTE m_bFoundOnDisk;
	DWORD	m_dbid;
	CSiteDir* m_parent;
	CWebSite* m_pWebSite;
	WIN32_FIND_DATA	m_wfd;
	int m_iIcon;
	long m_cChildren;
	DWORD m_treeItem;

	CSiteItem()
	{
		m_pWebSite = NULL;
		m_dbid = 0;
		m_treeItem = NULL;
		m_iIcon = 0;
		m_cChildren = 0;
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

};

#include "..\CmdHandler.h"

/////////////////////////////////////////////////////////////////////////////
// CSiteFilesView
class ATL_NO_VTABLE CSiteFilesView : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSiteFilesView, &CLSID_SiteFilesView>,
	public IConnectionPointContainerImpl<CSiteFilesView>,
	public IDispatchImpl<ISiteFilesView, &IID_ISiteFilesView, &LIBID_WEBEDITORLib>,

	public IDispEventImpl<4, CSiteFilesView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<5, CSiteFilesView, &DIID__IWSSrvEvents, &LIBID_WSSRVMODLib, 1, 0>,

	public ProcessTargetCommands,
	public IUITreeControlSite,

	public IDropTarget,

	public CUIDialogImpl<CSiteFilesView, CWindowImpl<CSiteFilesView> >
{
public:
	CSiteFilesView();

	int FinalConstruct();
	void FinalRelease();

	CComQIPtr<IWebSite>	m_document;

	CAxWindow	m_axtreeCtl;
	CComQIPtr<IUITreeControl> m_treeCtl;

	DWORD m_rootFolderId;
	_bstr_t m_rootDisplayPath;

	HIMAGELIST	m_hFileIcons;

	DWORD m_prevDropItem;

	void InitTree();
	void PopulateFolder(DWORD parentItem, CSiteDir* pParentDir);

	void OnSize();

	HGLOBAL BuildSelectedFilesClipboard();

	CSiteItem * FromRecordSet(CSiteDir* pParentDir, ADODB::_RecordsetPtr recordset);
	CSiteItem* FindFileById(DWORD parentItem, long file_id);

//	void OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk);

DECLARE_REGISTRY_RESOURCEID(IDR_SITEFILESVIEW)
DECLARE_GET_CONTROLLING_UNKNOWN()
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
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSiteFilesView)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CSiteFilesView)
//   SINK_ENTRY_EX(3, DIID__IWebSiteEvents, /*dispid*/1, OnFileTreeChanged)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/1, OnItemDblClick)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/2, OnItemClick)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/3, OnContextMenu)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/4, OnItemExpanding)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/6, OnEndLabelEdit)
   SINK_ENTRY_EX(5, DIID__IWSSrvEvents, /*dispid*/1, OnFileUpdate)
END_SINK_MAP()

//	HRESULT __stdcall OnFileTreeChanged();

	HRESULT __stdcall OnItemClick(DWORD item);
	HRESULT __stdcall OnItemDblClick(DWORD item);
	HRESULT __stdcall OnContextMenu(long x, long y);
	HRESULT __stdcall OnItemExpanding(long item, VARIANT_BOOL bExpanding, BOOL* bCancel);
	HRESULT __stdcall OnEndLabelEdit(long item, BSTR text);

	HRESULT __stdcall OnFileUpdate(long parentFolderId, long fileId, long action);

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
	STDMETHOD(put_webSiteDocument)(/*[in]*/ IWebSite* newVal);

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
	STDMETHOD(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
	{
		CComQIPtr<ICommandTarget> target;
		
	// Try document first
		target = m_document;
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;

	// Then try us
		return ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	}
// IUITreeControlSite
	STDMETHOD(GetItemText)(ULONG itemdata, LONG column, BSTR * pVal);
};

#endif //__SITEFILESVIEW_H_
