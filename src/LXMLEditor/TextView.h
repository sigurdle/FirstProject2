// TextView.h : Declaration of the CTextView

#ifndef __TEXTVIEW_H_
#define __TEXTVIEW_H_

#include "resource.h"       // main symbols

#include "TextStatusBar.h"

namespace System
{
namespace LXmlEdit
{

class CETextDocument;

class CTextView : 

public UI::Control,
//	public CUIDialogImpl<CTextView, CWindowImpl<CTextView> >,
public UI::ProcessTargetCommands	// ILDOMEventListener

//	public IDispEventImpl<1, CTextView, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<4, CTextView, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CTextView()
	{
		m_document = NULL;
		m_viewWhitespace = false;
	}

	int FinalConstruct();
	void FinalRelease();

	UI::TextEdit* m_edit;

	CTextStatusBar m_statusBar;

	CETextDocument* m_document;

	bool m_viewWhitespace;

	void OnSize();

//DECLARE_REGISTRY_RESOURCEID(IDR_TEXTVIEW)

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTextView)
	COM_INTERFACE_ENTRY(ITextView)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
END_COM_MAP()
*/

	void __stdcall OnEditMovedCursor(long offset);
	void __stdcall OnPrefsChange();

#if 0
BEGIN_MSG_MAP(CTextView)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
//	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
//	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
END_MSG_MAP()
#endif
//	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnCreate();
//	long OnSize();
	long OnDestroy();
//	long OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CTextView)

	long OnMakeSelectionUppercase(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	long OnMakeSelectionLowercase(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);

	long OnWindowNew(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);

	long OnViewWordWrap(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	void OnViewWordWrapUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	long OnViewLineNumbers(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	void OnViewLineNumbersUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	long OnViewWhitespace(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	void OnViewWhitespaceUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

// ITextView
public:
// IUIDlg
	ErrorCode OnActivate(bool bActivate, UI::Control* pActivateView, UI::Control* pDeactivateView);
// ICommandTarget
	ErrorCode OnCmdMsg(long nID, long nCode, UI::IUICmdUpdate * pCmdUI, bool * bHandled);
};

}	// LXmlEdit
}

#endif //__TEXTVIEW_H_
