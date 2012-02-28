// LHTMLHelpWindow.h : Declaration of the CLHTMLHelpWindow

#ifndef __LHTMLHELPWINDOW_H_
#define __LHTMLHELPWINDOW_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"
#include "..\CmdHandler.h"

class CHelpView;

/////////////////////////////////////////////////////////////////////////////
// CLHTMLHelpWindow
class ATL_NO_VTABLE CLHTMLHelpWindow : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLHTMLHelpWindow, &CLSID_LHTMLHelpWindow>,
	public CUIManagerImpl<CLHTMLHelpWindow>,
	public CUIFrameImpl<CLHTMLHelpWindow, CFrameWindowImpl<CLHTMLHelpWindow>, IUIFrame>,
	public ProcessTargetCommands,
	public ILHTMLHelpWindow
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_LHTMLHELPWINDOW)

	CLHTMLHelpWindow()
	{
		m_view = NULL;
	}

	CHelpView* m_view;

	int FinalConstruct();

DECLARE_REGISTRY_RESOURCEID(IDR_LHTMLHELPWINDOW)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLHTMLHelpWindow)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIFrame)
	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(ILHTMLHelpWindow)
END_COM_MAP()

	typedef CUIFrameImpl<CLHTMLHelpWindow, CFrameWindowImpl<CLHTMLHelpWindow>, IUIFrame> baseClass;

BEGIN_MSG_MAP(CLHTMLHelpWindow)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	CHAIN_MSG_MAP(baseClass)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	DECLARE_CMD_MAP(CLHTMLHelpWindow)

// ILHTMLHelpWindow
public:
	STDMETHOD(ShowHelp)(/*[in]*/ BSTR pathName, /*[out,retval]*/ BOOL* success);
};

#endif //__LHTMLHELPWINDOW_H_
