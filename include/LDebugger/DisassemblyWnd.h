#ifndef Debugger_DisassemblyWnd_h
#define Debugger_DisassemblyWnd_h

namespace System
{
namespace Debugger
{

class DisassemblyWnd : public UI::Control
{
public:

	class Line : public Object
	{
	public:
		enum Kind
		{
			K_INSTR,
			K_TEXT,
		};

		virtual Kind GetKind() = 0;
	};

	class InstrLine : public Line
	{
	public:

		virtual Kind GetKind()
		{
			return K_INSTR;
		}

		ULONG address;
		uint8 nbytes;
		union
		{
			void* pv;
			//instr* xxx;
			x86instr* x86;
			m68kinstr* m68k;
			ppcinstr* ppc;
			java::javainstr* java;
			ActionScripting::Instruction* actionScript;
		}
		cpu;
	};

	class TextLine : public Line
	{
	public:
		CTOR TextLine()
		{
			str = NULL;
		}

		virtual Kind GetKind()
		{
			return K_TEXT;
		}

		StringA* str;
		int lineNumber;
	};

	CTOR DisassemblyWnd(DebuggerCtx* ctx);
	virtual ~DisassemblyWnd();

	int get_LinesOffset() const
	{
		return m_linesOffset;
	}

	void set_LinesOffset(int linesOffset)
	{
		m_linesOffset = linesOffset;
	}

	DebuggerCtx* get_Ctx()
	{
		return m_ctx;
	}

	void SetActive(ULONG addr);
	void ScrollUp(int nlines);
	void ScrollDown(int nlines);

protected:

	virtual void OnRender(UI::Graphics* pGraphics);
	virtual void OnArrange(LDraw::SizeD finalSize);
	virtual LDraw::SizeD OnMeasure(LDraw::SizeD availSize);
//	virtual void handleEvent(System::Event* evt);

	void MakeVisible2(ULONG addr);
	void MakeVisible(ULONG addr);
	void ReadBuffer();

	DebuggerCtx* m_ctx;

	bool m_bViewCodeBytes;

	int m_lineHeight;

	vector<Line*, __gc_allocator> m_lines;
	int m_linesOffset;

	uint8* m_buffer;
	ULONG m_addr;
	ULONG m_topaddr;
	ULONG m_addroffset;
	ULONG m_lenbytes;

	ULONG m_active;

#if 0

BEGIN_MSG_MAP(DisassemblyWnd)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_VSCROLL, OnVScroll)
	COMMAND_ID_HANDLER(ID_DEBUG_TOGGLEBREAKPOINT, OnToggleBreakpoint)
	COMMAND_ID_HANDLER(ID_DISASM_CODEBYTES, OnViewCodeBytes)
	CHAIN_MSG_MAP(CUpdateUI<DisassemblyWnd>)
	CHAIN_MSG_MAP(CMDIChildWindowImpl<DisassemblyWnd>)
END_MSG_MAP()

BEGIN_UPDATE_UI_MAP(DisassemblyWnd)
	UPDATE_ELEMENT(ID_DISASM_CODEBYTES, UPDUI_MENUPOPUP)
END_UPDATE_UI_MAP()
#endif

#if 0//_WINDOWS
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnViewCodeBytes(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnToggleBreakpoint(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
#else
//	virtual long OnCommand(long nCommand);
#endif

//	LDraw::GraphicsPath m_path;
//	LDraw::PointF m_oldPoint;
//	float m_penWidth;
//	int m_dragging;
//	int m_npt;

};

}
}

#endif // Debugger_DisassemblyWnd_h
