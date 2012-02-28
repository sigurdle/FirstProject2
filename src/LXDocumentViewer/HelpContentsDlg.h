// HelpContentsDlg.h : Declaration of the CHelpContentsDlg

#if 0
#ifndef __HELPCONTENTSDLG_H_
#define __HELPCONTENTSDLG_H_

#include "resource.h"       // main symbols
//#import "C:\MMStudio\Extras\UI\UI.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

/////////////////////////////////////////////////////////////////////////////
// CHelpContentsDlg
class ATL_NO_VTABLE CHelpContentsDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public IConnectionPointContainerImpl<CHelpContentsDlg>,
//	public IDispatchImpl<IHelpContentsDlg, &IID_IHelpContentsDlg, &LIBID_WEBEDITORLib>,

	public CUIDialogImpl<CHelpContentsDlg, CWindowImpl<CHelpContentsDlg> >,
//	public CUIEventHandlerImpl,

	public IBindStatusCallback,

	public IDispEventImpl<4, CHelpContentsDlg, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>
//	public IUITreeControlSite
{
public:

	CHelpContentsDlg()
	{
		m_app = NULL;
		m_hIcons = NULL;
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = m_treeCtl.CoCreateInstance(CLSID_UITreeControl);
		if (FAILED(hr)) return hr;

	//	m_treeCtl->SetSite(this);
		m_treeCtl->InsertColumn(0, L"", 160, TRUE, TRUE, NULL);

		return 0;
	}

	void FinalRelease()
	{
	}

	ILXDocumentViewerApp* m_app;

	CComPtr<ILDOMDocument> m_tocDocument;

	CAxWindow m_axtreeCtl;
	CComPtr<IUITreeControl> m_treeCtl;

	HIMAGELIST m_hIcons;

//	CComQIPtr<IEXMLViewGroup> m_viewGroup;

	void BuildItem(IUITreeItem* parentItem, ILDOMElement* element);
	void BuildTree();

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHelpContentsDlg)
//	COM_INTERFACE_ENTRY(IHelpContentsDlg)
//	COM_INTERFACE_ENTRY(IDispatch)
//	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IUIEventHandler)

	COM_INTERFACE_ENTRY(IBindStatusCallback)
END_COM_MAP()

/*
BEGIN_CONNECTION_POINT_MAP(CHelpContentsDlg)
END_CONNECTION_POINT_MAP()
*/
BEGIN_SINK_MAP(CHelpContentsDlg)
   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/1, OnItemClick)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/2, OnItemDblClick)
END_SINK_MAP()

//	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);

	void __stdcall OnItemClick(IUITreeItem* item);
//	void __stdcall OnItemDblClick(DWORD item);

BEGIN_MSG_MAP(CHelpContentsDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)

END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IHelpContentsDlg
public:
// IUIDlg
	/*
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Contents");
		return S_OK;
	}
	*/
	STDMETHODIMP CalcLayout(DWORD dwFlags, long nLength, SIZE* pVal)
	{
		// Fill in sensible default values
		pVal->cx = 200;
		pVal->cy = 300;

		return S_OK;
	}

// IBindStatusCallback
	STDMETHOD(OnStartBinding)(DWORD dwReserved, IBinding __RPC_FAR *pib);
	STDMETHOD(GetPriority)(LONG __RPC_FAR *pnPriority);
	STDMETHOD(OnLowResource)(DWORD reserved);
	STDMETHOD(OnProgress)(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText);
	STDMETHOD(OnStopBinding)(HRESULT hresult, LPCWSTR szError);
	STDMETHOD(GetBindInfo)(DWORD __RPC_FAR *grfBINDF, BINDINFO __RPC_FAR *pbindinfo);
	STDMETHOD(OnDataAvailable)(DWORD grfBSCF, DWORD dwSize, FORMATETC __RPC_FAR *pformatetc, STGMEDIUM __RPC_FAR *pstgmed);
	STDMETHOD(OnObjectAvailable)(REFIID riid, IUnknown __RPC_FAR *punk);

	/*
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
	*/
};

#endif //__HELPCONTENTSDLG_H_

#endif