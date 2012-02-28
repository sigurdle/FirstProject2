// InspectorDlg.h : Declaration of the CInspectorDlg

#ifndef __INSPECTORDLG_H_
#define __INSPECTORDLG_H_

#include "resource.h"       // main symbols

#include "UIControls.h"

class CView;

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CInspectorDlg
class CInspectorDlg : 

	//public CUIDialogImpl<CInspectorDlg, CWindowImpl<CInspectorDlg> >,
//	public CUIEventHandlerImpl,
	//public ILElementBehavior,
public UI::Control,
	public Web::IEventListener

//	public IDispEventImpl<1, CInspectorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CInspectorDlg()
	{
		m_app = NULL;

		m_controlWindow = NULL;
	//	m_reentrancy = 0;
	}

	CLXMLEditorApp* m_app;
	CView* m_view;

	CEXMLViewGroup* m_viewGroup;
	Web::Element* m_targetElement;

	IControlsWindow* m_controlWindow;
//	CComPtr<IUIDlg> m_dlg;

//	int m_reentrancy;
//	virtual void UpdateData(CXMLData* pData);

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CInspectorDlg)
	COM_INTERFACE_ENTRY(IInspectorDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ILElementBehavior)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(LXML::EventListener)
END_COM_MAP()
*/

	void __stdcall OnViewGroupSelectionChanged();
	void __stdcall OnViewGroupSelectionChanging();

	/*
BEGIN_MSG_MAP(CInspectorDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/

// IInspectorDlg
public:

// IUIEventHandler
//	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);

// LXML::EventListener
	void handleEvent(Web::Event* evt);
};

}	// LXmlEdit
}

#endif //__INSPECTORDLG_H_
