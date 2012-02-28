// SceneGraphDlg.h : Declaration of the CSceneGraphDlg

#ifndef __SCENEGRAPHDLG_H_
#define __SCENEGRAPHDLG_H_

#include "resource.h"       // main symbols

namespace System
{

class CESceneDocument;

class CSceneGraphDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public IConnectionPointContainerImpl<CSceneGraphDlg>,
//	public IDispatchImpl<ISceneGraphDlg, &IID_ISceneGraphDlg, &LIBID_LXMLEDITORLib>,

public UI::Control
//	public CUIDialogImpl<CSceneGraphDlg, CWindowImpl<CSceneGraphDlg> >,
//	public ILElementBehavior,
//	public ProcessTargetCommands
//	public IDispEventImpl<1, CSceneGraphDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>

{
public:
	CSceneGraphDlg()
	{
	}

	int FinalConstruct();
	void FinalRelease();

	LDraw::BBoxi m_areaRect;

//	CAxWindow m_axvert;
//	CComPtr<IUIScrollBar> m_vert;

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

BEGIN_COM_MAP(CSceneGraphDlg)
//	COM_INTERFACE_ENTRY(ISceneGraphDlg)
	COM_INTERFACE_ENTRY(ILElementBehavior)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(ICommandTarget)
//	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSceneGraphDlg)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CSceneGraphDlg)
//   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()
#endif

	void __stdcall OnVertScroll(long code, long pos);

#if 0
BEGIN_MSG_MAP(CSceneGraphDlg)
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
	long OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	long OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
*/

//DECLARE_CMD_MAP(CSceneGraphDlg)

// ISceneGraphDlg
public:

};
}

#endif //__SCENEGRAPHDLG_H_
