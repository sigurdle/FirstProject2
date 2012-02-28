// ASObjectInspectorDlg.h : Declaration of the CASObjectInspectorDlg

#ifndef __ASOBJECTINSPECTORDLG_H_
#define __ASOBJECTINSPECTORDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CASObjectInspectorDlg
class CASObjectInspectorDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CASObjectInspectorDlg, &CLSID_ASObjectInspectorDlg>,
//	public IConnectionPointContainerImpl<CASObjectInspectorDlg>,
//	public IDispatchImpl<IASObjectInspectorDlg, &IID_IASObjectInspectorDlg, &LIBID_LXMLEDITORLib>,

public UI::Control
//	public CUIDialogImpl<CASObjectInspectorDlg, CWindowImpl<CASObjectInspectorDlg> >,
//	public CUIEventHandlerImpl

//	public IDispEventImpl<2, CASObjectInspectorDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>,
//	public IDispEventImpl<4, CASObjectInspectorDlg, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>
{
public:

	CASObjectInspectorDlg()
	{
		m_app = NULL;
	}

	CLXMLEditorApp* m_app;

	CEXMLViewGroup* m_viewGroup;

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CASObjectInspectorDlg)
	COM_INTERFACE_ENTRY(IASObjectInspectorDlg)
 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()
*/
#if 0
BEGIN_CONNECTION_POINT_MAP(CASObjectInspectorDlg)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CASObjectInspectorDlg)
//   SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()
#endif
//	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);

#if 0
BEGIN_MSG_MAP(CASObjectInspectorDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)

/*
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
//	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
*/
END_MSG_MAP()
#endif

//	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

// IASObjectInspectorDlg
public:
// IUIDlg
// IUIEventHandler
	ErrorCode handleActivateObjectEvent(System::Object* object, long* cookie);
	ErrorCode handleDeactivateObjectEvent(System::Object* object, long cookie, bool* bAllow);
};

}	// LXmlEdit
}

#endif //__ASOBJECTINSPECTORDLG_H_
