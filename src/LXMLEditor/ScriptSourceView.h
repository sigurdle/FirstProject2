// ScriptSourceView.h : Declaration of the CScriptSourceView

#ifndef __SCRIPTSOURCEVIEW_H_
#define __SCRIPTSOURCEVIEW_H_

#include "resource.h"       // main symbols

//class CEXMLViewGroup;

#include "TextStatusBar.h"

namespace System
{
namespace LXmlEdit
{
class CEScriptDocument;

class CScriptSourceView : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public IConnectionPointContainerImpl<CScriptSourceView>,
//	public IDispatchImpl<IScriptSourceView, &IID_IScriptSourceView, &LIBID_LXMLEDITORLib>,

	public UI::Control,
//	public CUIDialogImpl<CScriptSourceView, CWindowImpl<CScriptSourceView> >,
	public UI::ProcessTargetCommands	// ILDOMEventListener

//	public IDispEventImpl<1, CScriptSourceView, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<2, CScriptSourceView, &DIID__IErrorListCtlEvents, &LIBID_ERRORMODLib, 1, 0>
//	public IDispEventImpl<3, CScriptSourceView, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>,
//	public IDispEventImpl<4, CScriptSourceView, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CScriptSourceView()
	{
		m_bErrorsExpanded = false;
		m_splity = 60;
		m_dragging = 0;

//		m_viewGroup = NULL;
		m_document = NULL;

		m_viewWhitespace = false;

	//	m_bSelectingElement = FALSE;
	}

	int FinalConstruct();
	void FinalRelease();

	UI::CView* m_view;

	bool m_bSelectingElement;

	int m_dragging;

#if 0
	CAxWindow m_axerrorListCtl;
	CComPtr<IErrorListCtl> m_errorListCtl;
#endif

	UI::TextEdit* m_edit;

	CTextStatusBar m_statusBar;

	//IEDocument* m_document;
	CEScriptDocument* m_document;
//	CEXMLViewGroup* m_viewGroup;

	bool m_viewWhitespace;

	bool m_bErrorsExpanded;
	int m_splity;

	void OnSize();

//	void SetRange(ILDOMRange* range);

	void FormatText();
	void FormatJScript(const WCHAR * data, int& pos, unsigned long length, bool bCDATA);
	void FormatVBScript(const WCHAR * data, int& pos, unsigned long length, bool bCDATA);

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CScriptSourceView)
//	COM_INTERFACE_ENTRY(IScriptSourceView)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CScriptSourceView)
END_CONNECTION_POINT_MAP()
*/

	void __stdcall OnEditMovedCursor(long offset);
	void __stdcall OnEditChanged();
	void __stdcall OnEditChar(WCHAR nchar);

//	void __stdcall OnGotoError(IErrorItem* errorItem);

	void __stdcall OnPrefsChange();

	ErrorCode __stdcall OnDoneParsingDOM();

	/*
	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	long OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	*/

DECLARE_CMD_MAP(CScriptSourceView)

	long OnFilePrint(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnFilePageSetup(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnMakeSelectionUppercase(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnMakeSelectionLowercase(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnViewWordWrap(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnViewintWrapUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	long OnViewLineNumbers(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnViewLineNumbersUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	long OnViewWhitespace(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnViewWhitespaceUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

// IScriptSourceView
public:
	ErrorCode get_document(/*[out, retval]*/ IEDocument* *pVal);
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
	ErrorCode OnCmdMsg(long nID, long nCode, UI::IUICmdUpdate * pCmdUI, bool * bHandled);
};

}	// LXmlEdit
}

#endif //__SCRIPTSOURCEVIEW_H_
