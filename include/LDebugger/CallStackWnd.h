#ifndef Debugger_CallStackWnd_h
#define Debugger_CallStackWnd_h

namespace System
{
namespace Debugger
{

class DebugFrame : public Object
{
public:
	CTOR DebugFrame()
	{
		m_str = NULL;
	}

	System::StringW* m_str;
	ULONG m_eip;
};

class CallStackWnd : public UI::Control
{
public:
	CTOR CallStackWnd();

	void Update();

	void set_Context(DebuggerCtx* ctx);

#if 0
	void ActivateTopParent()
	{
		// special activate logic for floating toolbars and palettes
		HWND pTopLevel = GetTopLevelParent();
		HWND pActiveWnd = GetForegroundWindow();
		if (pActiveWnd == NULL ||
			!(pActiveWnd == m_hWnd || ::IsChild(pActiveWnd, m_hWnd)))
		{
			// clicking on floating frame when it does not have
			// focus itself -- activate the toplevel frame instead.
			::SetForegroundWindow(pTopLevel);
		}
	}

BEGIN_MSG_MAP(CallStackWnd)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	MESSAGE_HANDLER(WM_MOUSEACTIVATE, OnMouseActivate)
END_MSG_MAP()

	LRESULT OnMouseActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	//	MessageBeep(-1);
		HWND hwndTopLevel = (HWND)wParam;       // handle of top-level parent 
		int nHittest = (INT)LOWORD(lParam);    // hit-test value 
		UINT mouseMsg = (UINT)HIWORD(lParam);    // mouse message 

		ActivateTopParent();

		return MA_NOACTIVATE;
	}

	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
#endif

	virtual void OnRender(UI::Graphics* pGraphics);
	virtual LDraw::SizeD OnMeasure(LDraw::SizeD availSize);

//	DebuggerFrame* m_pFrame;
	DebuggerCtx* m_ctx;

	int m_selected;
	vector<DebugFrame*, __gc_allocator> m_callstack;
};

}
}

#endif // Debugger_CallStackWnd_h
