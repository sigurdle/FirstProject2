// CustomShapeToolOptionsDlg.h : Declaration of the CCustomShapeToolOptionsDlg

#ifndef __CUSTOMSHAPETOOLOPTIONSDLG_H_
#define __CUSTOMSHAPETOOLOPTIONSDLG_H_

#include "resource.h"       // main symbols

class CListPopup :
	public CWindowImpl
{
};

/////////////////////////////////////////////////////////////////////////////
// CCustomShapeToolOptionsDlg
class ATL_NO_VTABLE CCustomShapeToolOptionsDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CCustomShapeToolOptionsDlg, &CLSID_CustomShapeToolOptionsDlg>,
//	public IDispatchImpl<ICustomShapeToolOptionsDlg, &IID_ICustomShapeToolOptionsDlg, &LIBID_LXMLEDITORLib>,

	public CUIDialogImpl<CCustomShapeToolOptionsDlg, CAxDialogImpl<CCustomShapeToolOptionsDlg> >
//	public CUIEventHandlerImpl,

//	public IDispEventImpl<2, CCustomShapeToolOptionsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CCustomShapeToolOptionsDlg()
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

	ILXMLEditorApp* m_app;

	enum { IDD = IDD_CUSTOMSHAPETOOLOPTIONSDLG };

//	CComPtr<IEXMLViewGroup> m_viewGroup;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCustomShapeToolOptionsDlg)
//	COM_INTERFACE_ENTRY(ICustomShapeToolOptionsDlg)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()

BEGIN_SINK_MAP(CCustomShapeToolOptionsDlg)
//   SINK_ENTRY_EX(2, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
END_SINK_MAP()

//	void __stdcall OnViewGroupSelectionChanged();

BEGIN_MSG_MAP(CCustomShapeToolOptionsDlg)
/*
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	*/
//	MESSAGE_HANDLER(WM_CLOSE, OnClose)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
END_MSG_MAP()

/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/

// ICustomShapeToolOptionsDlg
public:
};

#endif //__CUSTOMSHAPETOOLOPTIONSDLG_H_
