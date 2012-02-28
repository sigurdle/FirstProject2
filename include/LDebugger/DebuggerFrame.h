#ifndef DebuggerFrame_h
#define DebuggerFrame_h

#include "resource.h"

#include "DebugSession.h"

#ifdef AMIGA
extern ULONG ret_pc;
#endif

namespace System
{
namespace Debugger
{

#ifdef WIN32

class DebuggerFrame;

class ProjectFile
{
public:
};

typedef map<System::StringA*, ProjectFile*, Ref_Less<System::StringA> > prjfilemap;

class Project
{
public:
	prjfilemap m_files;
};
#endif

class CRegistersWnd : public UI::Control
{
public:
	CTOR CRegistersWnd()
	{
		m_ctx = NULL;
	}

	DebuggerCtx* m_ctx;

	virtual void OnRender(UI::Graphics* pGraphics);
};

class CallStackWnd;
class DisassemblyWnd;
class WatchWnd;
class SourceEditFrame;

class striless// : public std::binary_function<StringA&, StringA&, bool>
{
public:
	bool operator()(System::StringA* x, System::StringA* y) const
	{
		return x->CompareNoCase(y) < 0;
		//return stricmp(x.c_str(), y.c_str()) > 0;
	}
};

class SourceTextDocument : public Object
{
public:
	SourceFile* m_sourceFile;

	TextLines* m_tdp;
	SourceEditFrame* m_edit;	// TODO, can be many
};

typedef map<System::StringA*, SourceTextDocument*, striless> filesmap;

class DebuggerFrame : public UI::CLXUIWindow

#ifdef AMIGA
	,
	public UI::ISignalHandler
#endif

#if 0//_WINDOWS
,
//public CMDIFrameWindowImpl<DebuggerFrame>,

//public CUpdateUI<DebuggerFrame>,
	public CMessageFilter, public CIdleHandler
#endif
{
public:

	CTOR DebuggerFrame();
	~DebuggerFrame();

#ifdef AMIGA
	virtual void handleSignal(uint32 sigmask);
#endif

//	void Init();

	filesmap m_files;

	SourceLocation* m_pLocation;

#if _WINDOWS
	/*
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return FALSE;
	//	return CMDIFrameWindowImpl<DebuggerFrame>::PreTranslateMessage(pMsg);
	}
	*/

	virtual bool OnIdle()
	{
		return false;
	}

#endif

	System::StringA* m_pathName;

	DebuggerCtx* m_ctx;

	UI::TreeControl* m_list;

#if 0
	CEdit m_wndMessages;
#endif
	System::StringA* m_messages;

	CRegistersWnd* m_registersWnd;

	UI::ChildWindowContainer* pCanvas;

	DisassemblyWnd* m_disassemblyWnd;
	CallStackWnd* m_callStackWnd;
	WatchWnd* m_watchWnd;
	UI::TextEdit* m_buildOutputWnd;

//	DWORD m_dwProcessId;

#if WIN32

	//ULONG m_Eip;
	CriticalSection m_bufferCS;

#elif AMIGA

//	ULONG m_Eip;

#elif __APPLE__

//	ULONG m_Eip;

#endif

	/*
	ULONG GetEip() const
	{
#if WIN32
		return m_Eip;
#elif AMIGA
		return m_Eip;
		//return ::ret_pc;
#elif __APPLE__
		return m_Eip;
#endif
	}
	*/

	void OnException();

	void GotoFilePos(System::StringA* filename, int line);

	SourceEditFrame* OpenFile(System::StringA* filename);

	void RemoveAllBreakpoints();

//	virtual void handleEvent(System::Event* evt);

//	virtual void OnRender2(LDraw::Graphics* pGraphics);

	void OnDebugStepInto();

#if 0//_WINDOWS
	virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_USER+2:
			{
				OnLoadFile(uMsg, wParam, lParam);
			}
			break;

		default:
			return CUIFrameImpl::WindowProc(uMsg, wParam, lParam);
		}
		return 0;
	}
#endif

#if 0//_WINDOWS
BEGIN_MSG_MAP(DebuggerFrame)

/*
	CHAIN_MDI_CHILD_COMMANDS()

	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	*/
#if 0
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_USER+2, OnLoadFile)
	MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
#endif
	/*
//		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	COMMAND_ID_HANDLER(ID_DEBUG_GO, OnDebugGo)
	COMMAND_ID_HANDLER(ID_DEBUG_ATTACHTOPROCESS, OnDebugAttachToProcess)
	COMMAND_ID_HANDLER(ID_DEBUG_BREAK, OnDebugBreak)
	COMMAND_ID_HANDLER(ID_DEBUG_STEPINTO, OnDebugStepInto)
	COMMAND_ID_HANDLER(ID_DEBUG_THREADS, OnDebugThreads)
	COMMAND_ID_HANDLER(ID_DEBUG_MODULES, OnDebugModules)
	COMMAND_ID_HANDLER(ID_EDIT_BREAKPOINTS, OnEditBreakpoints)
	COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
	COMMAND_ID_HANDLER(ID_FILE_OPEN, OnFileOpen)
	COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNew)
	COMMAND_ID_HANDLER(ID_FILE_OPENPROGRAM, OnFileOpenProgram)
	COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
	CHAIN_MSG_MAP(CUpdateUI<DebuggerFrame>)
	*/
	CHAIN_MSG_MAP(CLXUIWindowElement)
END_MSG_MAP()
#endif

#if 0
BEGIN_UPDATE_UI_MAP(DebuggerFrame)
	UPDATE_ELEMENT(ID_DEBUG_GO,  UPDUI_MENUPOPUP)
	UPDATE_ELEMENT(ID_DEBUG_THREADS, UPDUI_MENUPOPUP)
END_UPDATE_UI_MAP()
#endif

//	OnWindowMessage

#ifdef WIN32
	MSWindows::LRESULT OnLoadFile(UINT uMsg, MSWindows::WPARAM wParam, MSWindows::LPARAM lParam);
#endif

//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

#if 0
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
#endif

#if 0//_WINDOWS
	LRESULT OnFileExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		PostMessage(WM_CLOSE);
		return 0;
	}
#endif

	void OnFileOpen();
	void OnFileOpenProgram();
	void OnDebugGo();

#if 0
	LRESULT OnFileNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// TODO: add code to initialize document

		return 0;
	}

	LRESULT OnEditBreakpoints(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDebugAttachToProcess(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//	LRESULT OnDebugStepInto(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDebugBreak(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDebugThreads(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDebugModules(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAppAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
#endif
};

}
}

#endif // DebuggerFrame_h
