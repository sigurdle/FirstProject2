// GradientDlg.h : Declaration of the CGradientDlg

#ifndef __GRADIENTDLG_H_
#define __GRADIENTDLG_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"

/////////////////////////////////////////////////////////////////////////////
// CGradientDlg
class ATL_NO_VTABLE CGradientDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGradientDlg, &CLSID_GradientDlg>,
	public IConnectionPointContainerImpl<CGradientDlg>,
	public IDispatchImpl<IGradientDlg, &IID_IGradientDlg, &LIBID_PAGEDESIGNERLib>,
	public CUIDialogImpl<CGradientDlg, CWindowImpl<CGradientDlg> >,
	public CUIEventHandlerImpl,
	public IDispEventImpl<1, CGradientDlg, &DIID__IGradientEditEvents, &LIBID_PAGEDESIGNERLib, 1, 0>
{
public:
	CGradientDlg()
	{
	}

	CAxWindow m_axgradientEdit;
	CComPtr<IGradientEdit> m_gradientEdit;

	CArray<IPDObjectFrame*,IPDObjectFrame*> m_targetObjects;

DECLARE_REGISTRY_RESOURCEID(IDR_GRADIENTDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGradientDlg)
	COM_INTERFACE_ENTRY(IGradientDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CGradientDlg)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CGradientDlg)
   SINK_ENTRY_EX(1, DIID__IGradientEditEvents, /*dispid*/1, OnClickGradientEmpty)
   SINK_ENTRY_EX(1, DIID__IGradientEditEvents, /*dispid*/2, OnClickStop)
END_SINK_MAP()

	void __stdcall OnClickGradientEmpty();
	void __stdcall OnClickStop(IPDGradientStop* stop);

BEGIN_MSG_MAP(CGradientDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IGradientDlg
public:
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Gradient");
		return S_OK;
	}
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

#endif //__GRADIENTDLG_H_
