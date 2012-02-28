// TestAttributesDlg.h : Declaration of the CTestAttributesDlg

#ifndef __TESTATTRIBUTESDLG_H_
#define __TESTATTRIBUTESDLG_H_

#include "resource.h"       // main symbols

#include "ControlsWindow.h"
#include "XMLControlsHandler.h"

namespace System
{
namespace LXmlEdit
{

class CTestAttributesDlg : 
public UI::Control,
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CUIDialogImpl<CTestAttributesDlg, CWindowImpl<CTestAttributesDlg> >,
//	public CAxDialogImpl<CTestAttributesDlg>,
	public CXMLControlsHandler
#if 0
	public IDispEventImpl<1, CTestAttributesDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
#endif
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CTestAttributesDlg()
	{
	}

	~CTestAttributesDlg()
	{
	}

	UI::CView* m_view;

//	CComPtr<IControlsWindow> m_controlWindow;
//	IEXMLViewGroup* m_viewGroup;

//	enum { IDD = IDD_TESTATTRIBUTESDLG };

#if 0
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTestAttributesDlg)
//	COM_INTERFACE_ENTRY(IDispatch)
//	COM_INTERFACE_ENTRY(IEntitiesDlg)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
END_COM_MAP()
BEGIN_SINK_MAP(CTestAttributesDlg)
//   SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
//   SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/4, OnViewGroupSelectionChanging)
END_SINK_MAP()
#endif

	void __stdcall OnViewGroupSelectionChanged();
	void __stdcall OnViewGroupSelectionChanging();

#if 0
BEGIN_MSG_MAP(CTestAttributesDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()
#endif
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	*/
};

}	// LXmlEdit
}

#endif //__TESTATTRIBUTESDLG_H_
