// DBView.h : Declaration of the CDBView

#ifndef __DBVIEW_H_
#define __DBVIEW_H_

#include "resource.h"       // main symbols

//class CSiteItem;
//class CSiteDir;
//class CWebSite;

/////////////////////////////////////////////////////////////////////////////
// CDBView
class ATL_NO_VTABLE CDBView : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CDBView, &CLSID_DBView>,
//	public IConnectionPointContainerImpl<CDBView>,
//	public IDispatchImpl<IDBView, &IID_IDBView, &LIBID_WEBEDITORLib>,

	public IDispEventImpl<4, CDBView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<5, CDBView, &DIID__IWSSrvEvents, &LIBID_WSSRVMODLib, 1, 0>,

	public ProcessTargetCommands,
//	public IUITreeControlSite,

//	public IDropTarget,

	public CUIDialogImpl<CDBView, CWindowImpl<CDBView> >
{
public:
	CDBView();

	int FinalConstruct();
	void FinalRelease();

//	CComQIPtr<IWebSite>	m_document;
	ADODB::_ConnectionPtr m_conn;
	ADOX::_CatalogPtr m_catalog;

	CAxWindow	m_axtreeCtl;
	CComQIPtr<IUITreeControl> m_treeCtl;

	DWORD m_rootFolderId;
	_bstr_t m_rootDisplayPath;


//	HIMAGELIST	m_hFileIcons;

//	DWORD m_prevDropItem;

//	void InitTree();
//	void PopulateFolder(DWORD parentItem, CSiteDir* pParentDir);

	void OnSize();

//	HGLOBAL BuildSelectedFilesClipboard();

//	CSiteItem * FromRecordSet(CSiteDir* pParentDir, ADODB::_RecordsetPtr recordset);
//	CSiteItem* FindFileById(DWORD parentItem, long file_id);

//	void OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk);

//DECLARE_REGISTRY_RESOURCEID(IDR_DBView)
//DECLARE_GET_CONTROLLING_UNKNOWN()
//DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDBView)
//	COM_INTERFACE_ENTRY(IDBView)
//	COM_INTERFACE_ENTRY(IConnectionPointContainer)
//	COM_INTERFACE_ENTRY2(IDispatch, IDBView)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ICommandTarget)

//	COM_INTERFACE_ENTRY(IUITreeControlSite)
//	COM_INTERFACE_ENTRY(IDropTarget)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDBView)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CDBView)
//   SINK_ENTRY_EX(3, DIID__IWebSiteEvents, /*dispid*/1, OnFileTreeChanged)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/1, OnItemDblClick)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/2, OnItemClick)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/3, OnContextMenu)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/4, OnItemExpanding)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/6, OnEndLabelEdit)
//   SINK_ENTRY_EX(5, DIID__IWSSrvEvents, /*dispid*/1, OnFileUpdate)
END_SINK_MAP()

//	HRESULT __stdcall OnFileTreeChanged();
	HRESULT __stdcall OnItemDblClick(DWORD item);
/*
	HRESULT __stdcall OnItemClick(DWORD item);
	HRESULT __stdcall OnContextMenu(long x, long y);
	HRESULT __stdcall OnItemExpanding(long item, VARIANT_BOOL bExpanding, BOOL* bCancel);
	HRESULT __stdcall OnEndLabelEdit(long item, BSTR text);

	HRESULT __stdcall OnFileUpdate(long parentFolderId, long fileId, long action);
*/

BEGIN_MSG_MAP(CDBView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
/*
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	*/
//	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk);
//	MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
END_MSG_MAP()

//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CDBView)

// IDBView
public:

// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Database");
		return S_OK;
	}
	/*
// IDropTarget
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
*/
// ICommandTarget
	STDMETHOD(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
	{
		CComQIPtr<ICommandTarget> target;
		
	// Try document first
		/*
		target = m_document;
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
		*/

	// Then try us
		return ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	}
// IUITreeControlSite
//	STDMETHOD(GetItemText)(ULONG itemdata, LONG column, BSTR * pVal);
};

#endif //__DBVIEW_H_
