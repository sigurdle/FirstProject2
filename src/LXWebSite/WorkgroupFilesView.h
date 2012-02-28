// WorkgroupFilesView.h : Declaration of the CWorkgroupFilesView

#ifndef __WORKGROUPFILESVIEW_H_
#define __WORKGROUPFILESVIEW_H_

#include "resource.h"       // main symbols

class CWorkgroupDocument;

/////////////////////////////////////////////////////////////////////////////
// CWorkgroupFilesView
class ATL_NO_VTABLE CWorkgroupFilesView : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWorkgroupFilesView, &CLSID_WorkgroupFilesView>,
	public IConnectionPointContainerImpl<CWorkgroupFilesView>,
	public IDispatchImpl<IWorkgroupFilesView, &IID_IWorkgroupFilesView, &LIBID_LXFRAMEWORKLib>,

	public CUIDialogImpl<CWorkgroupFilesView, CWindowImpl<CWorkgroupFilesView> >,
	public ProcessTargetCommands,

	public IDispEventImpl<4, CWorkgroupFilesView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>
{
public:
	CWorkgroupFilesView()
	{
		m_document = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	CWorkgroupDocument* m_document;

	CAxWindow m_axctl;
	CComPtr<IXMiLFilesControl> m_ctl;

DECLARE_REGISTRY_RESOURCEID(IDR_WORKGROUPFILESVIEW)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CWorkgroupFilesView)
	COM_INTERFACE_ENTRY(IWorkgroupFilesView)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ICommandTarget)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CWorkgroupFilesView)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CWorkgroupFilesView)
//   SINK_ENTRY_EX(3, DIID__IWebSiteEvents, /*dispid*/1, OnFileTreeChanged)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/1, OnItemDblClick)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/2, OnItemClick)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/3, OnContextMenu)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/4, OnItemExpanding)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/6, OnEndLabelEdit)
  // SINK_ENTRY_EX(5, DIID__IWSSrvEvents, /*dispid*/1, OnFileUpdate)
END_SINK_MAP()

//	HRESULT __stdcall OnItemClick(DWORD item);
	HRESULT __stdcall OnItemDblClick(DWORD item);
//	HRESULT __stdcall OnContextMenu(long x, long y);
//	HRESULT __stdcall OnItemExpanding(long item, VARIANT_BOOL bExpanding, BOOL* bCancel);
//	HRESULT __stdcall OnEndLabelEdit(long item, BSTR text);

BEGIN_MSG_MAP(CWorkgroupFilesView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CWorkgroupFilesView)

	LRESULT OnFileProperties(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// IWorkgroupFilesView
public:
// IUIDlg
//	STDMETHOD(OnActivate)(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView);
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Files");
		return S_OK;
	}
};

#endif //__WORKGROUPFILESVIEW_H_
