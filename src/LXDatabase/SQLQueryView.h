// SQLQueryView.h : Declaration of the CSQLQueryView

#ifndef __SQLQUERYVIEW_H_
#define __SQLQUERYVIEW_H_

#include "resource.h"       // main symbols

#import "..\SQLQueryBuilderMod\SQLQueryBuilderMod.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids

class CDBView;

#include "DataGrid.h"

/////////////////////////////////////////////////////////////////////////////
// CSQLQueryView
class ATL_NO_VTABLE CSQLQueryView : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSQLQueryView, &CLSID_SQLQueryView>,
//	public IConnectionPointContainerImpl<CSQLQueryView>,
//	public IDispatchImpl<ISQLQueryView, &IID_ISQLQueryView, &LIBID_WEBEDITORLib>,

//	public IDispEventImpl<4, CSQLQueryView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<5, CSQLQueryView, &DIID__IWSSrvEvents, &LIBID_WSSRVMODLib, 1, 0>,

	public ProcessTargetCommands,
//	public IUITreeControlSite,

//	public IDropTarget,
	public CUIDialogImpl<CSQLQueryView, CWindowImpl<CSQLQueryView> >
{
public:
	CSQLQueryView();

	int FinalConstruct();
	void FinalRelease();

	int m_size[2];

	CAxWindow m_axsqlQueryBuilder;
	CComPtr<ISQLQueryBuilder> m_sqlQueryBuilder;

	CAxWindow m_axsqlEdit;
	CComPtr<IUIEdit> m_sqlEdit;

	CDataGrid m_dataGrid;

	CDBView* m_pDBView;

//	CComQIPtr<IWebSite>	m_document;

//	CAxWindow	m_axtreeCtl;
//	CComQIPtr<IUITreeControl> m_treeCtl;

//	DWORD m_rootFolderId;
//	_bstr_t m_rootDisplayPath;

//	HIMAGELIST	m_hFileIcons;

//	DWORD m_prevDropItem;

//	void InitTree();
//	void PopulateFolder(DWORD parentItem, CSiteDir* pParentDir);

//	void OnSize();

//	HGLOBAL BuildSelectedFilesClipboard();

//	CSiteItem * FromRecordSet(CSiteDir* pParentDir, ADODB::_RecordsetPtr recordset);
//	CSiteItem* FindFileById(DWORD parentItem, long file_id);

//	void OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk);

//DECLARE_REGISTRY_RESOURCEID(IDR_SQLQueryView)
//DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSQLQueryView)
//	COM_INTERFACE_ENTRY(ISQLQueryView)
//	COM_INTERFACE_ENTRY(IConnectionPointContainer)
//	COM_INTERFACE_ENTRY2(IDispatch, ISQLQueryView)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ICommandTarget)

//	COM_INTERFACE_ENTRY(IUITreeControlSite)
//	COM_INTERFACE_ENTRY(IDropTarget)
END_COM_MAP()

/*
BEGIN_CONNECTION_POINT_MAP(CSQLQueryView)
END_CONNECTION_POINT_MAP()
*/

#if 0
BEGIN_SINK_MAP(CSQLQueryView)
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
#endif

BEGIN_MSG_MAP(CSQLQueryView)
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
//	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CSQLQueryView)

	LRESULT OnQueryRun(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	/*

	LRESULT OnFileSetasHomepage(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnFileSetasHomepageUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnEditDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnEditDeleteUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnFileNewFolder(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
*/
// ISQLQueryView
public:
#if 0
	STDMETHOD(GetRootFolderId)(/*[out,retval]*/ unsigned long* folder_id);
	STDMETHOD(SetRootFolderId)(/*[in]*/ unsigned long folder_id);
	STDMETHOD(get_webSiteDocument)(/*[out, retval]*/ IWebSite* *pVal);
	STDMETHOD(put_webSiteDocument)(/*[in]*/ IWebSite* newVal);
#endif

// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"SQL Query");
		return S_OK;
	}
#if 0
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
#endif
};

#endif //__SQLQUERYVIEW_H_
