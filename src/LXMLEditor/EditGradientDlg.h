#ifndef __EDITGRADIENTDLG_H_
#define __EDITGRADIENTDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CSVGGradientEditCtl;
class CEXMLViewGroup;

class CEditGradientDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CEditGradientDlg, &CLSID_EditGradientDlg>,
//	public IConnectionPointContainerImpl<CEditGradientDlg>,
//	public IDispatchImpl<IEditGradientDlg, &IID_IEditGradientDlg, &LIBID_LXMLEDITORLib>,

public UI::Control
//	public CUIDialogImpl<CEditGradientDlg, CAxDialogImpl<CEditGradientDlg> >,
//	public CUIEventHandlerImpl,
#if 0
	public IDispEventImpl<1, CEditGradientDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>,
	public IDispEventImpl<3, CEditGradientDlg, &DIID__ISVGGradientEditCtlEvents, &LIBID_LXMLEDITORLib, 1, 0>,
	public IDispEventImpl<6, CEditGradientDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>
#endif
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CEditGradientDlg()
	{
		m_app = NULL;
		m_pElement = NULL;
	}

	CLXMLEditorApp* m_app;

	UI::CView* m_view;

	CSVGGradientEditCtl* m_GradCtl;

	Web::SVGGradientElement*	m_gradient;
	Web::SVGStopElement* m_activeStop;

	CEXMLViewGroup* m_viewGroup;
	Element* m_pElement;

	void __stdcall OnViewGroupSelectionChanged();
	ErrorCode __stdcall OnDOMEvent(Web::Event* evt);
	void __stdcall OnEndDragStopElement(Web::SVGStopElement* stopElement);

#if 0
BEGIN_MSG_MAP(CEditGradientDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_MOUSEACTIVATE, OnMouseActivate)
	COMMAND_HANDLER(IDC_GRADIENT_TYPE, CBN_SELENDOK, OnGradientType)
END_MSG_MAP()
#endif

//	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	/*
	LRESULT OnMouseActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		HWND hwndTopLevel = (HWND)wParam;       // handle of top-level parent 
		int nHittest = (INT)LOWORD(lParam);    // hit-test value 
		UINT mouseMsg = (UINT)HIWORD(lParam);    // mouse message 

		return MA_NOACTIVATE;
	}
	*/

	long OnGradientType(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

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

// IEditGradientDlg
public:
// IUIEventHandler
//	ErrorCode(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	ErrorCode(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

}	// LXmlEdit
}

#endif //__EDITGRADIENTDLG_H_
