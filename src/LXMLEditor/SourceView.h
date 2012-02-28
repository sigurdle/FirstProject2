// SourceView.h : Declaration of the CSourceView

#ifndef __SOURCEVIEW_H_
#define __SOURCEVIEW_H_

#include "resource.h"       // main symbols

//#include "../LXUI/Visual.h"

#include "TextStatusBar.h"

namespace System
{
class CEDocument;

namespace LXmlEdit
{

class CEXMLDocument;
class CEXMLViewGroup;

class CSourceView : 
//	public IConnectionPointContainerImpl<CSourceView>,
//	public IDispatchImpl<ISourceView, &IID_ISourceView, &LIBID_LXMLEDITORLib>,

public UI::Control,
#if 0
	public CUIDialogImpl<CSourceView, CWindowImpl<CSourceView> >,
#endif
	public UI::ProcessTargetCommands	// ILDOMEventListener
//	public ILElementBehavior

#if 0
	public IDispEventImpl<1, CSourceView, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CSourceView, &DIID__IErrorListCtlEvents, &LIBID_ERRORMODLib, 1, 0>,
	public IDispEventImpl<3, CSourceView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>,
	public IDispEventImpl<4, CSourceView, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>
#endif
{
public:
	CSourceView(CEXMLViewGroup* viewGroup);

//	int FinalConstruct();
//	void FinalRelease();

	UI::CView* m_view;

	bool m_bSelectingElement;

	int m_dragging;

	/*
	CAxWindow m_axerrorListCtl;
	CComPtr<IErrorListCtl> m_errorListCtl;
	*/

#if 0
	CAxWindow m_axedit;
#endif
	UI::TextEdit* m_edit;

//	CTextStatusBar m_statusBar;
//	Ptr<ILHTMLObjectElement> m_editObjectElement;
	UI::Control* m_statusBarElement;

	//IEDocument* m_document;
	//CEXMLDocument* m_document;
	CEXMLViewGroup* m_viewGroup;

	bool m_viewWhitespace;

	bool m_bErrorsExpanded;
#if 0
	int m_splity;

	void OnSize();
#endif

	void SetRange(Web::Range* range);

	void FormatText();
	void FormatNotwellformed(Web::Node* parentNode);
	void FormatJScript(const WCHAR * data, int& pos, unsigned long length, bool bCDATA);
	void FormatVBScript(const WCHAR * data, int& pos, unsigned long length, bool bCDATA);

#if 0
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSourceView)
	COM_INTERFACE_ENTRY(ISourceView)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)

	COM_INTERFACE_ENTRY(ILElementBehavior)
//	COM_INTERFACE_ENTRY(IUIDlg)
//	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSourceView)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CSourceView)
   SINK_ENTRY_EX(1, DIID__IUIEditEvents, /*dispid*/1, OnEditMovedCursor)
   SINK_ENTRY_EX(1, DIID__IUIEditEvents, /*dispid*/2, OnEditChanged)
   SINK_ENTRY_EX(1, DIID__IUIEditEvents, /*dispid*/3, OnEditChar)

   SINK_ENTRY_EX(2, DIID__IErrorListCtlEvents, /*dispid*/1, OnGotoError)

   SINK_ENTRY_EX(3, DIID__IEXMLDocumentEvents, /*dispid*/2, OnDoneParsingDOM)

	SINK_ENTRY_EX(4, DIID__ILXMLEditorAppEvents, /*dispid*/1, OnPrefsChange)
END_SINK_MAP()
#endif

	void __stdcall OnEditMovedCursor(long offset);
	void __stdcall OnEditChanged();
	void __stdcall OnEditChar(WCHAR nchar);

//	void __stdcall OnGotoError(IErrorItem* errorItem);

	void __stdcall OnPrefsChange();

	ErrorCode __stdcall OnDoneParsingDOM();

#if 0
BEGIN_MSG_MAP(CSourceView)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
END_MSG_MAP()
#endif

/*
	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	*/

	long OnCreate();
	void OnDestroy();

DECLARE_CMD_MAP(CSourceView)

	long OnFilePrint(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnFilePageSetup(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnMakeSelectionUppercase(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnMakeSelectionLowercase(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnViewWordWrap(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnViewWordWrapUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	long OnViewLineNumbers(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnViewLineNumbersUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	long OnViewWhitespace(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnViewWhitespaceUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

// ILXUIControlSited
#if 0
	CComPtr<ILElementBehaviorSite> m_behaviorSite;

	STDMETHODIMP Init(/*[in]*/ ILElementBehaviorSite* pBehaviorSite);
	STDMETHODIMP Detach();
#endif
// ISourceView
public:
	CEDocument* get_document();
//	ErrorCode(put_document)(/*[in]*/ IEDocument* newVal);
// IUIDlg
	ErrorCode OnActivate(bool bActivate, UI::Control* pActivateView, UI::Control* pDeactivateView);

	ErrorCode OnDragOut(UI::CUIDockBar* dockBar);

	/*
	ErrorCode(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Source");
		return S_OK;
	}
	*/
// ICommandTarget
//	ErrorCode(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, bool * bHandled);
};

}	// LXmlEdit
}

#endif //__SOURCEVIEW_H_
