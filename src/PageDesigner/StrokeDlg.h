// StrokeDlg.h : Declaration of the CStrokeDlg

#ifndef __STROKEDLG_H_
#define __STROKEDLG_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"

/////////////////////////////////////////////////////////////////////////////
// CStrokeDlg
class ATL_NO_VTABLE CStrokeDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStrokeDlg, &CLSID_StrokeDlg>,
	public IConnectionPointContainerImpl<CStrokeDlg>,
	public IDispatchImpl<IStrokeDlg, &IID_IStrokeDlg, &LIBID_PAGEDESIGNERLib>,
	public CUIDialogImpl<CStrokeDlg, CAxDialogImpl<CStrokeDlg> >,
	public CUIEventHandlerImpl
{
public:
	CStrokeDlg()
	{
	}

//	CComPtr<IUIEditUnitValue> m_strokeWeightCtl;

	enum { IDD = IDD_STROKEDLG };

	CArray<IPDStrokeSettings*,IPDStrokeSettings*> m_targetObjects;

	void GetControlValues();
	void SetControlValues();

DECLARE_REGISTRY_RESOURCEID(IDR_STROKEDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStrokeDlg)
	COM_INTERFACE_ENTRY(IStrokeDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CStrokeDlg)
END_CONNECTION_POINT_MAP()

#if 0
BEGIN_SINK_MAP(CStrokeDlg)
	SINK_ENTRY_EX(1, DIID__IUIEditUnitValueEvents, /*dispid*/1, OnChangeStrokeWeight)
END_SINK_MAP()

	void __stdcall OnChangeStrokeWeight();
#endif

BEGIN_MSG_MAP(CLayersDlg)
//	MESSAGE_HANDLER(WM_NCCREATE, OnNcCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDC_STROKE_WEIGHT, CBN_SELCHANGE, OnStrokeWeightChanged)
	COMMAND_HANDLER(IDC_STROKE_CAP0, BN_CLICKED, OnStrokeCapChanged)
	COMMAND_HANDLER(IDC_STROKE_CAP1, BN_CLICKED, OnStrokeCapChanged)
	COMMAND_HANDLER(IDC_STROKE_CAP2, BN_CLICKED, OnStrokeCapChanged)
	COMMAND_HANDLER(IDC_STROKE_JOIN0, BN_CLICKED, OnStrokeJoinChanged)
	COMMAND_HANDLER(IDC_STROKE_JOIN1, BN_CLICKED, OnStrokeJoinChanged)
	COMMAND_HANDLER(IDC_STROKE_JOIN2, BN_CLICKED, OnStrokeJoinChanged)
	COMMAND_HANDLER(IDC_STROKE_MITERLIMIT, EN_KILLFOCUS, OnStrokeMiterLimitChanged)
	COMMAND_HANDLER(IDC_STROKE_DASHED0, EN_KILLFOCUS, OnStrokeDashChanged)
	COMMAND_HANDLER(IDC_STROKE_DASHED1, EN_KILLFOCUS, OnStrokeDashChanged)
	COMMAND_HANDLER(IDC_STROKE_DASHED2, EN_KILLFOCUS, OnStrokeDashChanged)
	COMMAND_HANDLER(IDC_STROKE_DASHED3, EN_KILLFOCUS, OnStrokeDashChanged)
	COMMAND_HANDLER(IDC_STROKE_DASHED4, EN_KILLFOCUS, OnStrokeDashChanged)
	COMMAND_HANDLER(IDC_STROKE_DASHED5, EN_KILLFOCUS, OnStrokeDashChanged)
END_MSG_MAP()

	LRESULT OnStrokeWeightChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnStrokeCapChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnStrokeJoinChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnStrokeDashChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnStrokeMiterLimitChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

//	LRESULT OnNcCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IStrokeDlg
public:
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Stroke");
		return S_OK;
	}
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

#endif //__STROKEDLG_H_
