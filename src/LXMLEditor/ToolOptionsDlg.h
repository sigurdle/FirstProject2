// ToolOptionsDlg.h : Declaration of the CToolOptionsDlg

#ifndef __TOOLOPTIONSDLG_H_
#define __TOOLOPTIONSDLG_H_

#include "resource.h"       // main symbols

class CView;

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CToolOptionsDlg
class CToolOptionsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CToolOptionsDlg, &CLSID_ToolOptionsDlg>,
//	public IDispatchImpl<IToolOptionsDlg, &IID_IToolOptionsDlg, &LIBID_LXMLEDITORLib>,

	public UI::Control
//	public CUIDialogImpl<CToolOptionsDlg, CWindowImpl<CToolOptionsDlg> >
//	public CUIEventHandlerImpl,

//	public IDispEventImpl<2, CToolOptionsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CToolOptionsDlg()
	{
		m_app = NULL;
	}

	int FinalConstruct()
	{
		return 0;
	}

	void FinalRelease()
	{
	}

	CView* m_view;

	CLXMLEditorApp* m_app;

#if 0
	CComPtr<IUIDlgSheet> m_presetsPopup;
	CComPtr<IUIDlgSheet> m_sheet;
#endif

//	CComPtr<IEXMLViewGroup> m_viewGroup;

#if 0
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CToolOptionsDlg)
//	COM_INTERFACE_ENTRY(IToolOptionsDlg)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()
#endif

#if 0
BEGIN_SINK_MAP(CToolOptionsDlg)
//   SINK_ENTRY_EX(2, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
END_SINK_MAP()
#endif

//	void __stdcall OnViewGroupSelectionChanged();

#if 0
BEGIN_MSG_MAP(CToolOptionsDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
/*	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
*/
	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_CLOSE, OnClose)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
END_MSG_MAP()
#endif

	long OnCreate();
	long OnDestroy();
/*
	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/
	long OnSize();
//	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IToolOptionsDlg
public:
// IUIDlg

	/*
	STDMETHODIMP CalcLayout(DWORD dwMode, long nLength, SIZE* pVal)
	{
		pVal->cx = 340;
		pVal->cy = 26;

		return S_OK;
	}
	*/
};

}	// LXmlEdit
}

#endif //__TOOLOPTIONSDLG_H_
