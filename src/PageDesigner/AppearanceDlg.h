// AppearanceDlg.h : Declaration of the CAppearanceDlg

#ifndef __APPEARANCEDLG_H_
#define __APPEARANCEDLG_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"

#include "item.h"

class CPDDocumentView;

class CAppearanceObject;

/////////////////////////////////////////////////////////////////////////////
// CAppearanceDlg
class ATL_NO_VTABLE CAppearanceDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAppearanceDlg, &CLSID_AppearanceDlg>,
	public IDispatchImpl<IAppearanceDlg, &IID_IAppearanceDlg, &LIBID_PAGEDESIGNERLib>,
	public CUIDialogImpl<CAppearanceDlg, CWindowImpl<CAppearanceDlg> >,
	public CUIEventHandlerImpl,
	public ProcessTargetCommands,
	public CNotifyGetImpl<CAppearanceDlg>,

	public IDispEventImpl<1, CAppearanceDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>
{
public:
	CAppearanceDlg()
	{
		m_view = NULL;

		m_pTree = NULL;
	}

	int FinalConstruct();

	C2Obj* m_pTree;

	CRect m_areaRect;
	CAxWindow m_axvert;
	CComPtr<IUIScrollBar> m_vert;

	CComObject<CPDDocumentView>* m_view;

//	CComPtr<IPDObjectWithAppearance> m_object;
	CComPtr<IUnknown> m_object;

	void BuildItems();
	void DeselectAll();
	void OnSize();

DECLARE_REGISTRY_RESOURCEID(IDR_APPEARANCEDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAppearanceDlg)
	COM_INTERFACE_ENTRY(IAppearanceDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(INotifyGet)
END_COM_MAP()

BEGIN_SINK_MAP(CAppearanceDlg)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()

	HRESULT __stdcall OnVertScroll(long code, long pos);

BEGIN_MSG_MAP(CAppearanceDlg)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CAppearanceDlg)

	LRESULT OnAddNewStroke(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnAddNewStrokeUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnAddNewFill(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnAddNewFillUpdate(long iid, IUICmdUpdate* pCmdUI);

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID);

// IAppearanceDlg
public:
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Appearance");
		return S_OK;
	}
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
// ICommandTarget
	STDMETHOD(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled);
};

#endif //__APPEARANCEDLG_H_
