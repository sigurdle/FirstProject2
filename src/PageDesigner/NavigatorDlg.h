// NavigatorDlg.h : Declaration of the CNavigatorDlg

#ifndef __NAVIGATORDLG_H_
#define __NAVIGATORDLG_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"

class CPDDocumentView;

/////////////////////////////////////////////////////////////////////////////
// CNavigatorDlg
class ATL_NO_VTABLE CNavigatorDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CNavigatorDlg, &CLSID_NavigatorDlg>,
	public IConnectionPointContainerImpl<CNavigatorDlg>,
	public IDispatchImpl<INavigatorDlg, &IID_INavigatorDlg, &LIBID_PAGEDESIGNERLib>,
	public CUIDialogImpl<CNavigatorDlg, CWindowImpl<CNavigatorDlg> >,
	public CUIEventHandlerImpl,
	public ProcessTargetCommands
//	public IDispEventImpl<1, CNavigatorDlg, &DIID__IUIManagerEvents, &LIBID_UILib, 1, 0>
{
public:
	CNavigatorDlg()
	{
		m_view = NULL;
		m_dragging = 0;

		m_maxpages = 0;
		m_maxspine = 0;
	}

	int FinalConstruct();

	CComObject<CPDDocumentView>* m_view;
	double m_magnify;
	SIZE m_size;

	long m_spine;
	
	long m_maxspine;
	long m_maxpages;

	POINT m_offset;
	BOOL m_dragging;

	void OnSize();

DECLARE_REGISTRY_RESOURCEID(IDR_NAVIGATORDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNavigatorDlg)
	COM_INTERFACE_ENTRY(INavigatorDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(ICommandTarget)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CNavigatorDlg)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CNavigatorDlg)
  // SINK_ENTRY_EX(1, DIID__IUIManagerEvents, /*dispid*/1, OnActivatedObject)
//	SINK_ENTRY_EX(1, DIID__IUIManagerEvents, /*dispid*/2, OnDeactivatedObject)
//   SINK_ENTRY_EX(3, DIID__IPDDocumentEvents, /*dispid*/3, OnLayerOptionsChanged)
END_SINK_MAP()

//	HRESULT __stdcall OnActivatedObject(IUnknown* object);
//	HRESULT __stdcall OnDeactivatedObject(IUnknown* object);

BEGIN_MSG_MAP(CNavigatorDlg)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CNavigatorDlg)

	LRESULT OnNavigatorViewAllSpreads(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// INavigatorDlg
public:
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Navigator");
		return S_OK;
	}
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

#endif //__NAVIGATORDLG_H_
