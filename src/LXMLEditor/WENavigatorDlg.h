#ifndef __WENAVIGATORDLG_H_
#define __WENAVIGATORDLG_H_

#include "resource.h"       // main symbols

class CView;

namespace System
{
namespace LXmlEdit
{

	class CEXMLLayoutView;

class CWENavigatorDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public IConnectionPointContainerImpl<CWENavigatorDlg>,
//	public IWENavigatorDlg,

		public UI::Control,
//	public CUIDialogImpl<CWENavigatorDlg, CWindowImpl<CWENavigatorDlg> >,
//	public CUIEventHandlerImpl,
public UI::ProcessTargetCommands	// Web::EventListener
//	public CIdleHandler

//	public IDispEventImpl<2, CWENavigatorDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>,
//	public IDispEventImpl<4, CWENavigatorDlg, &DIID__ILHTMLWindowEvents, &LIBID_LHTMLLib, 1, 0>
{
public:
//	DECLARE_WND_CLASS_EX(NULL, 0/*CS_DBLCLKS*/, -1/*COLOR_BTNFACE*/)

	CWENavigatorDlg()// : m_cnedit("edit", this, 1)
	{
		m_app = NULL;
		m_layoutView = NULL;
		m_dragging = false;
		m_magnify = 0;

		m_bUpdate = false;
		m_bRedraw = true;

		m_offbm = NULL;
#if 0
		m_viewBoxColor = RGB(255, 74, 74);
#endif
	}

	int FinalConstruct();
	void FinalRelease();

	CView* m_view;

	CLXMLEditorApp* m_app;

	double m_magnify;
	CEXMLLayoutView* m_layoutView;
	LDraw::SizeD m_size;

	LDraw::PointD m_offset;
	bool m_dragging;

	LDraw::Color m_viewBoxColor;

	LDraw::BBoxi GetViewBox();

	LDraw::Bitmap* m_offbm;

	bool m_bUpdate;
	bool m_bRedraw;

//	CFont m_font;

//	CEdit m_edit;
//	CContainedWindow m_cnedit;
//	CScrollBar m_sizeGrip;

	void OnSize();
	virtual bool OnIdle();

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CWENavigatorDlg)
	COM_INTERFACE_ENTRY(IWENavigatorDlg)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(Web::EventListener)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CWENavigatorDlg)
END_CONNECTION_POINT_MAP()
*/

#if 0
BEGIN_SINK_MAP(CWENavigatorDlg)
   SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)

   SINK_ENTRY_EX(4, DIID__ILHTMLWindowEvents, /*dispid*/1, OnScroll)
   SINK_ENTRY_EX(4, DIID__ILHTMLWindowEvents, /*dispid*/2, OnZoom)
   SINK_ENTRY_EX(4, DIID__ILHTMLWindowEvents, /*dispid*/3, OnResize)
END_SINK_MAP()
#endif

	ErrorCode __stdcall OnDOMEvent(Web::Event* evt);

	void __stdcall OnScroll()
	{
		OnChangeViewBox();
	}

	void __stdcall OnZoom()
	{
		OnChangeViewBox();
	}

	void __stdcall OnResize()
	{
		OnChangeViewBox();
	}

	void OnChangeViewBox();

//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

//	long OnEditKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

DECLARE_CMD_MAP(CWENavigatorDlg)

	long OnPaletteOptions(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

// IWENavigatorDlg
public:
// IUIDlg
	ErrorCode OnActivate(bool bActivate, UI::Control* pActivateView, UI::Control* pDeactivateView);

// IUIEventHandler
//	ErrorCode(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	ErrorCode(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

}	// LXmlEdit
}

#endif //__WENAVIGATORDLG_H_
