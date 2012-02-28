// EditFilterDlg.h : Declaration of the CEditFilterDlg

#ifndef __EDITFILTERDLG_H_
#define __EDITFILTERDLG_H_

#include "resource.h"       // main symbols
//#import "C:\MMStudio\Extras\UI\UI.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

namespace System
{
namespace UI
{
class CView;
}

namespace LXmlEdit
{

class CEditFilterGraph;

class CEditFilterDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CEditFilterDlg, &CLSID_EditFilterDlg>,
//	public IConnectionPointContainerImpl<CEditFilterDlg>,

public UI::Control,
//	public CUIDialogImpl<CEditFilterDlg, CWindowImpl<CEditFilterDlg> >,
//	public CUIEventHandlerImpl,
public UI::ProcessTargetCommands	// ILDOMEventListener

#if 0
	public IDispEventImpl<1, CEditFilterDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
#endif
{
public:
	CEditFilterDlg()
	{
		m_app = NULL;
		m_pElement = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	CLXMLEditorApp* m_app;
	UI::CView* m_view;

//	CAxWindow m_axeditGraph;
	CEditFilterGraph * m_editGraph;

	CEXMLViewGroup* m_viewGroup;

	Element* m_pElement;

	/*
//DECLARE_REGISTRY_RESOURCEID(IDR_EDITFILTERDLG)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEditFilterDlg)
	COM_INTERFACE_ENTRY(IEditFilterDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CEditFilterDlg)
END_CONNECTION_POINT_MAP()
*/
#if 0
BEGIN_SINK_MAP(CEditFilterDlg)
   SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
//   SINK_ENTRY_EX(6, DIID__IESvgDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()
#endif
	void __stdcall OnViewGroupSelectionChanged();

#if 0
BEGIN_MSG_MAP(CEditFilterDlg)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_CLOSE, OnClose)
//	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
END_MSG_MAP()
#endif
/*
	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/
//	long OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	long OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

DECLARE_CMD_MAP(CEditFilterDlg)

	long OnFilterDeletePrimitive(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnFilterPrimitive(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnFilterPrimitiveUpdate(long wID, UI::IUICmdUpdate* pCmdUI);

// IEditFilterDlg
public:
// IUIDlg
	ErrorCode OnFrameActivate(long fActive)
	{
		if (fActive == 0)
		{
			ASSERT(0);
#if 0
			m_pDlgSite->Show(FALSE);
#endif
		}
		return Success;
	}

	/*
	ErrorCode(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Filter Graph");
		return S_OK;
	}*/
// IUIEventHandler
//	ErrorCode(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	ErrorCode(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

}	// LXmlEdit
}

#endif //__EDITFILTERDLG_H_
