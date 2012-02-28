// PluginFiltersDlg.h : Declaration of the CPluginFiltersDlg

#ifndef __PLUGINFILTERSDLG_H_
#define __PLUGINFILTERSDLG_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"

/////////////////////////////////////////////////////////////////////////////
// CPluginFiltersDlg
class ATL_NO_VTABLE CPluginFiltersDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPluginFiltersDlg, &CLSID_PluginFiltersDlg>,
	public ISupportErrorInfo,
	public IDispatchImpl<IPluginFiltersDlg, &IID_IPluginFiltersDlg, &LIBID_PAGEDESIGNERLib>,
	public CUIDialogImpl<CPluginFiltersDlg, CWindowImpl<CPluginFiltersDlg> >
{
public:
	CPluginFiltersDlg()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PLUGINFILTERSDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPluginFiltersDlg)
	COM_INTERFACE_ENTRY(IPluginFiltersDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
END_COM_MAP()

BEGIN_MSG_MAP(CPluginFiltersDlg)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_CREATE, OnCreate)
//	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

public:
// IPluginFiltersDlg
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Filters");
		return S_OK;
	}
};

#endif //__PLUGINFILTERSDLG_H_
