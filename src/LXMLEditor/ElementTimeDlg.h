// ElementTimeDlg.h : Declaration of the CElementTimeDlg

#ifndef __ELEMENTTIMEDLG_H_
#define __ELEMENTTIMEDLG_H_

#include "resource.h"       // main symbols

#include "ControlsWindow.h"
#include "XMLControlsHandler.h"

class CView;

namespace System
{
namespace LXmlEdit
{

class CElementTimeDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CUIDialogImpl<CElementTimeDlg, CWindowImpl<CElementTimeDlg> >,
public UI::Control,
	public CXMLControlsHandler
//	public IDispEventImpl<1, CElementTimeDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CElementTimeDlg()
	{
	}

	~CElementTimeDlg()
	{
	}

	CView* m_view;

//	CComPtr<IControlsWindow> m_controlWindow;
//	IEXMLViewGroup* m_viewGroup;

//	enum { IDD = IDD_ELEMENTTIMEDLG };

#if 0
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CElementTimeDlg)
//	COM_INTERFACE_ENTRY(IDispatch)
//	COM_INTERFACE_ENTRY(IEntitiesDlg)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
END_COM_MAP()

BEGIN_SINK_MAP(CElementTimeDlg)
   SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
   SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/4, OnViewGroupSelectionChanging)
END_SINK_MAP()
#endif

	void __stdcall OnViewGroupSelectionChanged();
	void __stdcall OnViewGroupSelectionChanging();

//	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
};

}	// LXmlEdit
}

#endif //__ELEMENTTIMEDLG_H_
