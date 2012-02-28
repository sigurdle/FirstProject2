#ifndef __DebugSession_h__
#define __DebugSession_h__

//#include "../CodeComp/debug.h"

namespace System
{

#ifdef WIN32

typedef struct STACK_FRAME
{
    STACK_FRAME*   Ebp;   //address of the calling function frame
    uint8*   Ret_Addr;      //return address
//    DWORD   Param[0];      //parameter list - could be empty
}
STACK_FRAME, * PSTACK_FRAME;

#endif // WIN32

#ifdef __APPLE__

struct gdb_ppc_thread_state
{
unsigned int srr0;
unsigned int srr1;

unsigned int gpregs[32];

unsigned int cr;
unsigned int xer;
unsigned int lr;
unsigned int ctr;
unsigned int mq;

unsigned int pad;
};

#define GDB_PPC_THREAD_STATE	1
#define GDB_PPC_THREAD_STATE_COUNT (sizeof(struct gdb_ppc_thread_state)/sizeof(int)) 

#endif

#ifdef WIN32

//#ifndef _WINNT_

namespace MSWindows
{

#define MAXIMUM_SUPPORTED_EXTENSION     512

//
//  Define the size of the 80387 save area, which is in the context frame.
//

#define SIZE_OF_80387_REGISTERS      80

typedef struct _FLOATING_SAVE_AREA {
    DWORD   ControlWord;
    DWORD   StatusWord;
    DWORD   TagWord;
    DWORD   ErrorOffset;
    DWORD   ErrorSelector;
    DWORD   DataOffset;
    DWORD   DataSelector;
    uint8    RegisterArea[SIZE_OF_80387_REGISTERS];
    DWORD   Cr0NpxState;
} FLOATING_SAVE_AREA;

typedef FLOATING_SAVE_AREA *PFLOATING_SAVE_AREA;

//
// Context Frame
//
//  This frame has a several purposes: 1) it is used as an argument to
//  NtContinue, 2) is is used to constuct a call frame for APC delivery,
//  and 3) it is used in the user level thread creation routines.
//
//  The layout of the record conforms to a standard call frame.
//

typedef struct _CONTEXT {

    //
    // The flags values within this flag control the contents of
    // a CONTEXT record.
    //
    // If the context record is used as an input parameter, then
    // for each portion of the context record controlled by a flag
    // whose value is set, it is assumed that that portion of the
    // context record contains valid context. If the context record
    // is being used to modify a threads context, then only that
    // portion of the threads context will be modified.
    //
    // If the context record is used as an IN OUT parameter to capture
    // the context of a thread, then only those portions of the thread's
    // context corresponding to set flags will be returned.
    //
    // The context record is never used as an OUT only parameter.
    //

    DWORD ContextFlags;

    //
    // This section is specified/returned if CONTEXT_DEBUG_REGISTERS is
    // set in ContextFlags.  Note that CONTEXT_DEBUG_REGISTERS is NOT
    // included in CONTEXT_FULL.
    //

    DWORD   Dr0;
    DWORD   Dr1;
    DWORD   Dr2;
    DWORD   Dr3;
    DWORD   Dr6;
    DWORD   Dr7;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_FLOATING_POINT.
    //

    FLOATING_SAVE_AREA FloatSave;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_SEGMENTS.
    //

    DWORD   SegGs;
    DWORD   SegFs;
    DWORD   SegEs;
    DWORD   SegDs;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_INTEGER.
    //

    DWORD   Edi;
    DWORD   Esi;
    DWORD   Ebx;
    DWORD   Edx;
    DWORD   Ecx;
    DWORD   Eax;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_CONTROL.
    //

    DWORD   Ebp;
    DWORD   Eip;
    DWORD   SegCs;              // MUST BE SANITIZED
    DWORD   EFlags;             // MUST BE SANITIZED
    DWORD   Esp;
    DWORD   SegSs;

    //
    // This section is specified/returned if the ContextFlags word
    // contains the flag CONTEXT_EXTENDED_REGISTERS.
    // The format and contexts are processor specific
    //

    uint8    ExtendedRegisters[MAXIMUM_SUPPORTED_EXTENSION];

} CONTEXT;

typedef CONTEXT *PCONTEXT;

}	// MSWindows

#endif // WIN32

namespace Debugger
{

class DebugBreakpoint : public Object
{
public:
	ULONG_PTR m_address;	// Resolved address

	// Unresolved location of breakpoint
	System::StringA* m_filename;
	int m_line;
};

struct InstrPlaceholder
{
	uint8 n[2];
};

//typedef std::map<ULONG,Breakpoint> tydbreakpointmap;

class Breakpoint
{
public:
	CTOR Breakpoint(InstrPlaceholder oldbyte)	// x86 needs 1 bytes, m68k needs 2 bytes, what does ppc need ?
	{
		m_oldbyte = oldbyte;
		m_enabled = true;
		m_count = 0;
	}

	//
//	std::string m_filename;
//	int m_line;

	uint32 m_count;	// Number of times this breakpoint has been hit

	InstrPlaceholder m_oldbyte;

	bool m_enabled : 1;
};

typedef map<uint32, Breakpoint> tybreakpointmap;

typedef map<System::StringA*, uint32, Ref_Less<System::StringA> > typrocessmap;

//#endif

class DebugThread : public Object
{
public:
	CTOR DebugThread()
	{
		m_dwThreadId = NULL;
		m_hThread = NULL;
		m_lpStartAddress = NULL;
		m_dwSuspendCount = -1;
	}

	MSWindows::DWORD m_dwThreadId;
	HANDLE m_hThread;
	LPVOID m_lpStartAddress;
	uint m_dwSuspendCount;
#if WIN32
	MSWindows::CONTEXT m_context;
#endif

	/*
	operator HANDLE ()
	{
		return m_hThread;
	}
	*/
};

typedef map<MSWindows::DWORD, DebugThread*> tyhthreadmap;

class DebugModule : public Object
{
public:
	CTOR DebugModule()
	{
		m_name = NULL;
	}

	System::StringW* m_name;
	ULONG_PTR m_base;
	ULONG_PTR m_size;
	tysymbolmap_address m_symbols;
};

class DebugProcess : public Object
{
public:
	CTOR DebugProcess()
	{
		m_hProcess = NULL;
		m_filename = ASTR("(unknown)");
		m_bRunning = true;
	}

	System::StringA* m_filename;
	MSWindows::DWORD m_dwProcessId;
	HANDLE m_hProcess;
//	HANDLE m_hThread;	// TODO remove

	tyhthreadmap m_threads;

	DebugThread* GetThreadById(MSWindows::DWORD dwThreadId)
	{
		tyhthreadmap::iterator ti = m_threads.begin();
		while (ti != m_threads.end())
		{
			if ((*ti).second->m_dwThreadId == dwThreadId)
			{
				return (*ti).second;//->m_hThread;
			}
			++ti;
		}

		return NULL;
	}

	bool m_bRunning;

	/*
	operator HANDLE ()
	{
		return m_hProcess;
	}
	*/
};

typedef map<MSWindows::DWORD, DebugProcess*> tyhprocessmap;

/*
class Stab
{
public:
	std::string m_name;
	long m_offset;
};

typedef std::map<std::string, Stab*> declmap;

*/

#if 0
class SourceFile
{
public:

	class SourceLine
	{
	public:
		CTOR SourceLine(uint32 address, uint16 line)
		{
			m_address = address;
			m_line = line;
		}

		uint32 m_address;
		uint16 m_line;
	};

	class Segment
	{
	public:
		CTOR Segment(uint32 startAddress = 0, uint32 endAddress = 0)
		{
			m_startAddress = startAddress;
			m_endAddress = endAddress;
		}

		uint32 m_startAddress;
		uint32 m_endAddress;
	};

	CTOR SourceFile()
	{
	//	startAddress = 0;
	//	endAddress = 0;
		m_pParentFile = NULL;
	}

	SourceFile* m_pParentFile;
	//std::vector<SourceFile*> sourceFiles;

	StringA m_filename;
	std::vector<StringA> sourceLines;

	std::vector<Segment> m_segments;

	std::vector<SourceLine> m_lines;

	/*
#if _WINDOWS
	std::vector<nlist*> m_stabvec;
	declmap m_stab;
#endif
	*/
};
#endif

class DebuggerCtx;

class DebugRecv : public Object, public ICodeViewReceiver
{
public:
	virtual System::NamedType* LookupNamedType(System::StringA* name);
	virtual System::Type* CreatePointerType(System::Type_type type, System::Type* pPointerTo);
	virtual void OnSymbol(System::StringA* name, ULONG address, ULONG dwData);
	virtual void OnType(System::StringA* name, System::NamedType* type, ULONG dwData);
	virtual System::Scope* OnProc(System::Scope* pScope, System::StringA* name, System::Type* type, ULONG startAddress, ULONG endAddress, ULONG dwData);
	virtual System::Scope* End(System::Scope* pScope);
	virtual void OnData(System::StringA* name, System::Type* type, ULONG address, ULONG dwData);
	virtual System::StringA* CreateString(System::StringA* str);

	DebuggerCtx* m_ctx;
	DebugModule* m_pModule;
};

class JavaDebugInfo : public DebugInfo
{
public:
	Scope* GetScope()
	{
		ASSERT(0);
		return NULL;
	}

	virtual int Parse(ObjectFileParser* pImage, ICodeViewReceiver* receiver, ULONG dwData)
	{
		ASSERT(0);
		return 0;
	}

};

class ActiveScriptCallback;

class DebuggerCtx : public System::Object
{
public:
#if WIN32
	class JavaVMHost : public Object, public javavm::IHost
	{
	public:
		virtual void OnLoadedClass(javavm::JavaClass* pClass);

		DebuggerCtx* m_ctx;
		javavm::JProcess* m_pJavaVM;
	};

	JavaVMHost* m_pJavaVMHost;
#endif

	ActionScripting::VM* m_actionScriptVM;

	ActiveScriptCallback* m_activeScriptCallback;

	CTOR DebuggerCtx();

	void Start();
	void Continue();
	void StepInto();

	void ReadBuffer(void* m_buffer, LPVOID addr, ULONG len);

	ULONG GetEip() const;

	void RemoveAllBreakpoints();

	vector<DebugBreakpoint*, __gc_allocator> m_userbreakpoints;

	ULONG m_Eip;

	DebuggerFrame* m_frame;

	//// TODO Improve
//	JavaClass* m_pJavaClass;
	ULONG m_CodeLength;
	////

	int m_cpu;

	MSWindows::DWORD m_javaThreadId;
	HANDLE m_javaThread;

#if WIN32

	DebugProcess* m_pDebugProcess;

	tyhprocessmap processes;

	vector<DebugModule*> m_modules;

#endif

	tybreakpointmap m_breakpoints;

#if WIN32
//#if _WINDOWS
	COFFParser* m_pImage;

#endif
//	nlist* stab;
//	int nstabs;
//	char* stabstr;
//#endif

//	std::vector<SourceFile*> sourceFiles;

	DebugInfo* m_pDebugInfo;

	SourceLocation* FindSourceLocation(ULONG_PTR find_address);

	bool AddBreakpoint(ULONG_PTR address);
	bool ResolveBreakpoint(DebugBreakpoint* pBreakpoint);

#if WIN32

	DebugProcess* GetProcessById(MSWindows::DWORD dwProcessId)
	{
		tyhprocessmap::iterator pi = processes.begin();
		while (pi != processes.end())
		{
			if ((*pi).second->m_dwProcessId == dwProcessId)
			{
				return (*pi).second;//->m_hProcess;
			}
			++pi;
		}

		return NULL;
	}

	MSWindows::DWORD m_dwProcessId;

#elif __APPLE__

	int m_dwProcessId;

#endif

protected:

#if WIN32
	MSWindows::DWORD m_threadId;
	HANDLE m_hThread;
#endif
};

}
}

#endif // __DebugSession_h__
