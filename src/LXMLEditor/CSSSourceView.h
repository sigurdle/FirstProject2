#ifndef __CSSSOURCEVIEW_H_
#define __CSSSOURCEVIEW_H_

#include "resource.h"       // main symbols

namespace System
{
namespace UI
{
class CView;
}

namespace LXmlEdit
{
class CECSSViewGroup;

class CCSSSourceView : 
//	public CComObjectRootEx<CComSingleThreadModel>,
	//public CComCoClass<CCSSSourceView, &CLSID_CSSSourceView>,
//	public IConnectionPointContainerImpl<CCSSSourceView>,
//	public IDispatchImpl<ICSSSourceView, &IID_ICSSSourceView, &LIBID_LXMLEDITORLib>,

public UI::Control,
#if 0
	public CUIDialogImpl<CCSSSourceView, CWindowImpl<CCSSSourceView> >,
#endif
	public UI::ProcessTargetCommands	// ILDOMEventListener
//	public ILElementBehavior,

#if 0
	public IDispEventImpl<1, CCSSSourceView, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CCSSSourceView, &DIID__IErrorListCtlEvents, &LIBID_ERRORMODLib, 1, 0>
#endif
//	public IDispEventImpl<3, CCSSSourceView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>,
//	public IDispEventImpl<4, CCSSSourceView, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>,
//	public IDispEventImpl<5, CCSSSourceView, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CCSSSourceView()
	{
		m_bErrorsExpanded = false;
		m_splity = 60;
		m_dragging = 0;

		m_viewGroup = NULL;
//		m_document = NULL;

		m_viewWhitespace = false;

//		m_pAutoListMembersWindow = NULL;
		m_bSelectingElement = false;
	}

	int FinalConstruct();
	void FinalRelease();

	UI::CView* m_view;

	bool m_bSelectingElement;

	int m_dragging;

#if 0
	CAxWindow m_axerrorListCtl;
	CComQIPtr<IErrorListCtl> m_errorListCtl;
#endif

//	CAxWindow m_axedit;
	UI::TextEdit* m_edit;

//	IEDocument* m_document;
	CECSSViewGroup* m_viewGroup;

	bool m_viewWhitespace;

	bool m_bErrorsExpanded;
	int m_splity;

//	CComPtr<ILHTMLObjectElement> m_editObjectElement;
//	CComPtr<ILDOMElement> m_statusBarElement;

	void OnSize();

	void SetRange(Web::Range* range);

	void FormatText();
	void FormatCSSBlock(System::StringW* data, int& pos, unsigned long length, bool bCDATA);

	/*
//DECLARE_REGISTRY_RESOURCEID(IDR_CSSSourceView)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCSSSourceView)
	COM_INTERFACE_ENTRY(ICSSSourceView)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)

//	COM_INTERFACE_ENTRY(IUIDlg)
//	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ILElementBehavior)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
END_COM_MAP()


BEGIN_CONNECTION_POINT_MAP(CCSSSourceView)
END_CONNECTION_POINT_MAP()

*/
#if 0
BEGIN_SINK_MAP(CCSSSourceView)
   SINK_ENTRY_EX(1, DIID__IUIEditEvents, /*dispid*/1, OnEditMovedCursor)
   SINK_ENTRY_EX(1, DIID__IUIEditEvents, /*dispid*/2, OnEditChanged)
   SINK_ENTRY_EX(1, DIID__IUIEditEvents, /*dispid*/3, OnEditChar)

   SINK_ENTRY_EX(2, DIID__IErrorListCtlEvents, /*dispid*/1, OnGotoError)

   SINK_ENTRY_EX(3, DIID__IEXMLDocumentEvents, /*dispid*/2, OnDoneParsingDOM)

	SINK_ENTRY_EX(4, DIID__ILXMLEditorAppEvents, /*dispid*/1, OnPrefsChange)

   SINK_ENTRY_EX(5, DIID__IEXMLViewGroupEvents, /*dispid*/1, OnViewGroupSelectionChanged)
END_SINK_MAP()
#endif

	void __stdcall OnEditMovedCursor(long offset);
	void __stdcall OnEditChanged();
	void __stdcall OnEditChar(WCHAR nchar);
	void __stdcall OnDoneParsingDOM();
//	void __stdcall OnGotoError(IErrorItem* errorItem);
	void __stdcall OnPrefsChange();
	void __stdcall OnViewGroupSelectionChanged();

#if 0
BEGIN_MSG_MAP(CCSSSourceView)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
END_MSG_MAP()
#endif

#if 0
	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
#endif

	long OnCreate();
	long OnDestroy();

DECLARE_CMD_MAP(CCSSSourceView)

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

// ILElementBehavior
//	CComPtr<ILElementBehaviorSite> m_behaviorSite;

#if 0
	STDMETHODIMP Init(/*[in]*/ ILElementBehaviorSite* pBehaviorSite);
	STDMETHODIMP Detach();
#endif
// ICSSSourceView
public:

	ErrorCode get_document(/*[out, retval]*/ IEDocument* *pVal);
// IUIDlg
	ErrorCode OnActivate(bool bActivate, UI::Control* pActivateView, UI::Control* pDeactivateView);
	/*
	ErrorCode(get_title)(StringW* pVal)
	{
		*pVal = SysAllocString(L"Source");
		return S_OK;
	}
	*/
	ErrorCode OnDragOut(UI::CUIDockBar* dockBar);

// ICommandTarget
//	ErrorCode(OnCmdMsg)(long nID, long nCode, UI::IUICmdUpdate * pCmdUI, BOOL * bHandled);
};

}
}

#endif //__CSSSOURCEVIEW_H_
