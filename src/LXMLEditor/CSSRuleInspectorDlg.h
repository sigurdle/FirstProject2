// CSSRuleInspectorDlg.h : Declaration of the CCSSRuleInspectorDlg

#ifndef __CSSRULEINSPECTORDLG_H_
#define __CSSRULEINSPECTORDLG_H_

#include "resource.h"       // main symbols

class CView;

#include "UIControls.h"

namespace System
{
namespace LXmlEdit
{

class CECSSViewGroup;

/////////////////////////////////////////////////////////////////////////////
// CCSSRuleInspectorDlg
class CCSSRuleInspectorDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CCSSRuleInspectorDlg, &CLSID_CSSRuleInspectorDlg>,
//	public IDispatchImpl<ICSSRuleInspectorDlg, &IID_ICSSRuleInspectorDlg, &LIBID_LXMLEDITORLib>,

public UI::Control
//	public CUIDialogImpl<CCSSRuleInspectorDlg, CWindowImpl<CCSSRuleInspectorDlg> >,
//	public CUIEventHandlerImpl,
//	public ProcessTargetCommands

//	public IDispEventImpl<1, CCSSRuleInspectorDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<2, CCSSRuleInspectorDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>,
#if 0
	public IDispEventImpl<1, CCSSRuleInspectorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
#endif
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CCSSRuleInspectorDlg()
	{
		m_app = NULL;
		m_viewGroup = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	UI::CView* m_view;
	ILXMLEditorApp* m_app;

	CECSSViewGroup* m_viewGroup;

//	CScrollBar m_sizeGrip;

//	CComPtr<IUIDlg> m_dlg;
	IControlsWindow* m_controlWindow;

	void OnSize();

//DECLARE_REGISTRY_RESOURCEID(IDR_CSSRuleInspectorDlg)

#if 0
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCSSRuleInspectorDlg)
//	COM_INTERFACE_ENTRY(ICSSRuleInspectorDlg)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
//	COM_INTERFACE_ENTRY(ICommandTarget)
END_COM_MAP()

BEGIN_SINK_MAP(CCSSRuleInspectorDlg)
//   SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
//   SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/4, OnViewGroupSelectionChanging)
END_SINK_MAP()
#endif

	void __stdcall OnViewGroupSelectionChanged();
	void __stdcall OnViewGroupSelectionChanging();

/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	*/
	/*
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	*/

//DECLARE_CMD_MAP(CCSSRuleInspectorDlg)

/*
	LRESULT OnNewLayer(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnNewSubLayer(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnNewViewport(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDeleteSelection(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnDeleteSelectionUpdate(long wID, IUICmdUpdate* pCmdUI);
	LRESULT OnSelectionOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
*/
// ICSSRuleInspectorDlg
public:
// IUIDlg
	/*
	STDMETHODIMP CalcLayout(DWORD dwFlags, long nLength, SIZE* pVal)
	{
		// Fill in sensible default values
		pVal->cx = 210;
		pVal->cy = 160;

		return S_OK;
	}
	*/
//	STDMETHOD(OnDragOut)(IUIDockBar* dockBar);

// IUIEventHandler
//	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

}	// LXmlEdit
}

#endif //__CSSRULEINSPECTORDLG_H_
