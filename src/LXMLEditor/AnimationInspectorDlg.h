// AnimationInspectorDlg.h : Declaration of the CAnimationInspectorDlg

#ifndef __ANIMATIONINSPECTORDLG_H_
#define __ANIMATIONINSPECTORDLG_H_

#include "resource.h"       // main symbols

//class CXMLControlWindow;

#include "UIControls.h"

namespace System
{
namespace LXmlEdit
{

//class CXMLAttributesListWnd;

class CAnimationInspectorDlg :
//	public IAnimationInspectorDlg,
//	public CUIDialogImpl<CAnimationInspectorDlg, CWindowImpl<CAnimationInspectorDlg> >,
public UI::Control,
	public Web::IEventListener
//	public CUIEventHandlerImpl

//	public IDispEventImpl<1, CAnimationInspectorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CAnimationInspectorDlg()
	{
		m_app = NULL;

		m_pControlWindow = NULL;
	}

	CLXMLEditorApp* m_app;

	CEXMLViewGroup* m_viewGroup;

//	CComPtr<IEElement> m_element;

//	CComPtr<IUIDlg> m_dlg;
	IControlsWindow* m_pControlWindow;

//DECLARE_REGISTRY_RESOURCEID(IDR_ANIMATIONINSPECTORDLG)


#if 0
BEGIN_SINK_MAP(CAnimationInspectorDlg)
   SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
   SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/4, OnViewGroupSelectionChanging)
END_SINK_MAP()
#endif
	void __stdcall OnViewGroupSelectionChanged();
	void __stdcall OnViewGroupSelectionChanging();

//	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

// IAnimationInspectorDlg
public:
// Web::EventListener
	void handleEvent(Web::Event* evt);

// IUIEventHandler
	ErrorCode handleActivateObjectEvent(System::Object* object, long* cookie);
	ErrorCode handleDeactivateObjectEvent(System::Object* object, long cookie, bool* bAllow);
};

}	// LXmlEdit
}

#endif //__ANIMATIONINSPECTORDLG_H_
