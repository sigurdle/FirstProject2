// SwatchesDlg.h : Declaration of the CSwatchesDlg

#ifndef __SWATCHESDLG_H_
#define __SWATCHESDLG_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"

/////////////////////////////////////////////////////////////////////////////
// CSwatchesDlg
class ATL_NO_VTABLE CSwatchesDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSwatchesDlg, &CLSID_SwatchesDlg>,
	public IConnectionPointContainerImpl<CSwatchesDlg>,
	public IDispatchImpl<ISwatchesDlg, &IID_ISwatchesDlg, &LIBID_PAGEDESIGNERLib>,
	public CUIDialogImpl<CSwatchesDlg, CWindowImpl<CSwatchesDlg> >,
	public ProcessTargetCommands,
	public CUIEventHandlerImpl,
	public CNotifyGetImpl<CSwatchesDlg>,
	public IDispEventImpl<1, CSwatchesDlg, &DIID__ISwatchesListEvents, &LIBID_PAGEDESIGNERLib, 1, 0>
{
public:
	CSwatchesDlg()
	{
	}

	int FinalConstruct();

	CComPtr<IPDSwatches> m_swatches;

	CAxWindow m_axswatchesList;
	CComPtr<ISwatchesList> m_swatchesList;

//	CArray<IPDObjectFrame*,IPDObjectFrame*> m_targetObjects;
	CArray<IPDObjectWithBrush*,IPDObjectWithBrush*> m_targetObjects;

	void UpdateSwatchesListCtl();

DECLARE_REGISTRY_RESOURCEID(IDR_SWATCHESDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSwatchesDlg)
	COM_INTERFACE_ENTRY(ISwatchesDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(INotifyGet)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSwatchesDlg)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CSwatchesDlg)
   SINK_ENTRY_EX(1, DIID__ISwatchesListEvents, /*dispid*/1, OnClickSwatch)
END_SINK_MAP()

	void __stdcall OnClickSwatch(IPDSwatch* swatch);

BEGIN_MSG_MAP(CSwatchesDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CSwatchesDlg)

	LRESULT OnNewColorSwatch(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnNewGradientSwatch(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnNewTintSwatch(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDeleteSwatch(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSwatchOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnSwatchOptionsUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnDeleteSwatchUpdate(long iid, IUICmdUpdate* pCmdUI);

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID);

// ISwatchesDlg
public:
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Swatches");
		return S_OK;
	}
// ICommandTarget
	STDMETHODIMP OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled);
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

#endif //__SWATCHESDLG_H_
