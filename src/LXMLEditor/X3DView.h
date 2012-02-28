#ifndef __X3DVIEW_H_
#define __X3DVIEW_H_

#include "resource.h"       // main symbols

namespace System
{

class CESceneDocument;

class CX3DView : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public IConnectionPointContainerImpl<CX3DView>,
//	public IDispatchImpl<IX3DView, &IID_IX3DView, &LIBID_LXMLEDITORLib>,

public UI::Control
//	public CUIDialogImpl<CX3DView, CWindowImpl<CX3DView> >,
//	public ILElementBehavior
//	public ProcessTargetCommands
//	public IDispEventImpl<1, CX3DView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>

{
public:
	CX3DView()
	{
	}

	int FinalConstruct();
	void FinalRelease();

	LDraw::BBoxi m_areaRect;

//	CAxWindow m_axviewer;
#if 0
	x3d::X3DViewer* m_viewer;
#endif

	CESceneDocument* m_pDocument;

// ILElementBehavior
#if 0
	CComPtr<ILElementBehaviorSite> m_behaviorSite;

	STDMETHODIMP Init(/*[in]*/ ILElementBehaviorSite* pBehaviorSite)
	{
		m_behaviorSite = pBehaviorSite;
		return S_OK;
	}
	STDMETHODIMP Detach()
	{
		m_behaviorSite.Release();
		return S_OK;
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CX3DView)
//	COM_INTERFACE_ENTRY(IX3DView)
	COM_INTERFACE_ENTRY(ILElementBehavior)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(ICommandTarget)
//	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
#endif

/*
BEGIN_CONNECTION_POINT_MAP(CX3DView)
END_CONNECTION_POINT_MAP()
*/

#if 0
BEGIN_SINK_MAP(CX3DView)
//   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()
#endif

//	void __stdcall OnVertScroll(long code, long pos);

#if 0
BEGIN_MSG_MAP(CX3DView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
//	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_VSCROLL, OnVScroll)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
END_MSG_MAP()
#endif
/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	LRESULT OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
*/
//DECLARE_CMD_MAP(CX3DView)

};

}

#endif //__X3DVIEW_H_
