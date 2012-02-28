#include "stdafx.h"
#include "LDebugger.h"
#include "DebugSession.h"
#include "WatchWnd.h"
#include "DisassemblyWnd.h"
#include "CallStackWnd.h"

#include "LFC/CodeViewDebugInfo.h"

#include "SWF/SWF.h"
#include "SWF/swfdebug.h"


#if __APPLE__

#include <mach-o/dyld_debug.h>
#include <mach-o/dyld.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <errno.h>

#endif

#if AMIGA
#include "../amiga_header.h"
#endif

#if AMIGA

bool ReadProcessMemory(Task* task, const void* lpBaseAddress, void* lpBuffer, uint32 nSize, uint32* lpNumberOfBytesRead)
{
	ASSERT(lpNumberOfBytesRead != NULL);

	memcpy(lpBuffer, lpBaseAddress, nSize);
	*lpNumberOfBytesRead = nSize;
	return TRUE;
}

bool WriteProcessMemory(Task* task, void* lpBaseAddress, const void* lpBuffer, uint32 nSize, uint32* lpNumberOfBytesWritten)
{
	ASSERT(lpNumberOfBytesWritten != NULL);

	memcpy(lpBaseAddress, lpBuffer, nSize);
	*lpNumberOfBytesWritten = nSize;
	return TRUE;
}

#endif

#if __APPLE__

bool ReadProcessMemory(PlatformProcess task, const void* lpBaseAddress, void* lpBuffer, unsigned long nSize, unsigned long* lpNumberOfBytesRead);
bool WriteProcessMemory(PlatformProcess task, void* lpBaseAddress, const void* lpBuffer, unsigned long nSize, unsigned long* lpNumberOfBytesWritten);

#endif

#if WIN32

#include "../include/windows_header.h"

namespace System
{
namespace MSWindows
{
extern "C"
{

#define EXCEPTION_MAXIMUM_PARAMETERS 15 // maximum number of exception parameters

//
// Exception record definition.
//

typedef struct _EXCEPTION_RECORD {
    DWORD    ExceptionCode;
    DWORD ExceptionFlags;
    struct _EXCEPTION_RECORD *ExceptionRecord;
    PVOID ExceptionAddress;
    DWORD NumberParameters;
    ULONG_PTR ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
    } EXCEPTION_RECORD;

typedef EXCEPTION_RECORD *PEXCEPTION_RECORD;

typedef struct _STARTUPINFOA {
    DWORD   cb;
    LPSTR   lpReserved;
    LPSTR   lpDesktop;
    LPSTR   lpTitle;
    DWORD   dwX;
    DWORD   dwY;
    DWORD   dwXSize;
    DWORD   dwYSize;
    DWORD   dwXCountChars;
    DWORD   dwYCountChars;
    DWORD   dwFillAttribute;
    DWORD   dwFlags;
    uint16    wShowWindow;
    uint16    cbReserved2;
    uint8*  lpReserved2;
    HANDLE  hStdInput;
    HANDLE  hStdOutput;
    HANDLE  hStdError;
} STARTUPINFOA, *LPSTARTUPINFOA;

typedef struct _STARTUPINFOW {
    DWORD   cb;
    LPWSTR  lpReserved;
    LPWSTR  lpDesktop;
    LPWSTR  lpTitle;
    DWORD   dwX;
    DWORD   dwY;
    DWORD   dwXSize;
    DWORD   dwYSize;
    DWORD   dwXCountChars;
    DWORD   dwYCountChars;
    DWORD   dwFillAttribute;
    DWORD   dwFlags;
    uint16    wShowWindow;
    uint16    cbReserved2;
    uint8*  lpReserved2;
    HANDLE  hStdInput;
    HANDLE  hStdOutput;
    HANDLE  hStdError;
} STARTUPINFOW, *LPSTARTUPINFOW;

typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef struct _PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId;
    DWORD dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;

/*
#define vector var
#include <windows.h>
#include <psapi.h>
#undef vector
*/

//
// dwCreationFlag values
//

#define DEBUG_PROCESS                     0x00000001
#define DEBUG_ONLY_THIS_PROCESS           0x00000002

#define CREATE_SUSPENDED                  0x00000004

#define DETACHED_PROCESS                  0x00000008

#define CREATE_NEW_CONSOLE                0x00000010

#define NORMAL_PRIORITY_CLASS             0x00000020
#define IDLE_PRIORITY_CLASS               0x00000040
#define HIGH_PRIORITY_CLASS               0x00000080
#define REALTIME_PRIORITY_CLASS           0x00000100

#define CREATE_NEW_PROCESS_GROUP          0x00000200
#define CREATE_UNICODE_ENVIRONMENT        0x00000400

#define CREATE_SEPARATE_WOW_VDM           0x00000800
#define CREATE_SHARED_WOW_VDM             0x00001000
#define CREATE_FORCEDOS                   0x00002000

#define BELOW_NORMAL_PRIORITY_CLASS       0x00004000
#define ABOVE_NORMAL_PRIORITY_CLASS       0x00008000
#define STACK_SIZE_PARAM_IS_A_RESERVATION 0x00010000

#define CREATE_BREAKAWAY_FROM_JOB         0x01000000
#define CREATE_PRESERVE_CODE_AUTHZ_LEVEL  0x02000000

#define CREATE_DEFAULT_ERROR_MODE         0x04000000
#define CREATE_NO_WINDOW                  0x08000000

#define PROFILE_USER                      0x10000000
#define PROFILE_KERNEL                    0x20000000
#define PROFILE_SERVER                    0x40000000

#define CREATE_IGNORE_SYSTEM_DEFAULT      0x80000000

#define THREAD_PRIORITY_LOWEST          THREAD_BASE_PRIORITY_MIN
#define THREAD_PRIORITY_BELOW_NORMAL    (THREAD_PRIORITY_LOWEST+1)
#define THREAD_PRIORITY_NORMAL          0
#define THREAD_PRIORITY_HIGHEST         THREAD_BASE_PRIORITY_MAX
#define THREAD_PRIORITY_ABOVE_NORMAL    (THREAD_PRIORITY_HIGHEST-1)
#define THREAD_PRIORITY_ERROR_RETURN    (MAXLONG)

#define THREAD_PRIORITY_TIME_CRITICAL   THREAD_BASE_PRIORITY_LOWRT
#define THREAD_PRIORITY_IDLE            THREAD_BASE_PRIORITY_IDLE

//
// Debug APIs
//
#define EXCEPTION_DEBUG_EVENT       1
#define CREATE_THREAD_DEBUG_EVENT   2
#define CREATE_PROCESS_DEBUG_EVENT  3
#define EXIT_THREAD_DEBUG_EVENT     4
#define EXIT_PROCESS_DEBUG_EVENT    5
#define LOAD_DLL_DEBUG_EVENT        6
#define UNLOAD_DLL_DEBUG_EVENT      7
#define OUTPUT_DEBUG_STRING_EVENT   8
#define RIP_EVENT                   9

typedef struct _EXCEPTION_DEBUG_INFO {
    EXCEPTION_RECORD ExceptionRecord;
    DWORD dwFirstChance;
} EXCEPTION_DEBUG_INFO, *LPEXCEPTION_DEBUG_INFO;

typedef struct _CREATE_THREAD_DEBUG_INFO {
    HANDLE hThread;
    LPVOID lpThreadLocalBase;
    LPTHREAD_START_ROUTINE lpStartAddress;
} CREATE_THREAD_DEBUG_INFO, *LPCREATE_THREAD_DEBUG_INFO;

typedef struct _CREATE_PROCESS_DEBUG_INFO {
    HANDLE hFile;
    HANDLE hProcess;
    HANDLE hThread;
    LPVOID lpBaseOfImage;
    DWORD dwDebugInfoFileOffset;
    DWORD nDebugInfoSize;
    LPVOID lpThreadLocalBase;
    LPTHREAD_START_ROUTINE lpStartAddress;
    LPVOID lpImageName;
    uint16 fUnicode;
} CREATE_PROCESS_DEBUG_INFO, *LPCREATE_PROCESS_DEBUG_INFO;

typedef struct _EXIT_THREAD_DEBUG_INFO {
    DWORD dwExitCode;
} EXIT_THREAD_DEBUG_INFO, *LPEXIT_THREAD_DEBUG_INFO;

typedef struct _EXIT_PROCESS_DEBUG_INFO {
    DWORD dwExitCode;
} EXIT_PROCESS_DEBUG_INFO, *LPEXIT_PROCESS_DEBUG_INFO;

typedef struct _LOAD_DLL_DEBUG_INFO {
    HANDLE hFile;
    LPVOID lpBaseOfDll;
    DWORD dwDebugInfoFileOffset;
    DWORD nDebugInfoSize;
    LPVOID lpImageName;
    uint16 fUnicode;
} LOAD_DLL_DEBUG_INFO, *LPLOAD_DLL_DEBUG_INFO;

typedef struct _UNLOAD_DLL_DEBUG_INFO {
    LPVOID lpBaseOfDll;
} UNLOAD_DLL_DEBUG_INFO, *LPUNLOAD_DLL_DEBUG_INFO;

typedef struct _OUTPUT_DEBUG_STRING_INFO {
    LPSTR lpDebugStringData;
    uint16 fUnicode;
    uint16 nDebugStringLength;
} OUTPUT_DEBUG_STRING_INFO, *LPOUTPUT_DEBUG_STRING_INFO;

typedef struct _RIP_INFO {
    DWORD dwError;
    DWORD dwType;
} RIP_INFO, *LPRIP_INFO;


typedef struct _DEBUG_EVENT {
    DWORD dwDebugEventCode;
    DWORD dwProcessId;
    DWORD dwThreadId;
    union {
        EXCEPTION_DEBUG_INFO Exception;
        CREATE_THREAD_DEBUG_INFO CreateThread;
        CREATE_PROCESS_DEBUG_INFO CreateProcessInfo;
        EXIT_THREAD_DEBUG_INFO ExitThread;
        EXIT_PROCESS_DEBUG_INFO ExitProcess;
        LOAD_DLL_DEBUG_INFO LoadDll;
        UNLOAD_DLL_DEBUG_INFO UnloadDll;
        OUTPUT_DEBUG_STRING_INFO DebugString;
        RIP_INFO RipInfo;
    } u;
} DEBUG_EVENT, *LPDEBUG_EVENT;

//

//#define STATUS_WAIT_0                    (/*(DWORD   )*/0x00000000L)    
//#define STATUS_ABANDONED_WAIT_0          (/*(DWORD   )*/0x00000080L)    
#define STATUS_USER_APC                  (/*(DWORD   )*/0x000000C0L)    
#define STATUS_TIMEOUT                   (/*(DWORD   )*/0x00000102L)    
#define STATUS_PENDING                   (/*(DWORD   )*/0x00000103L)    
#define DBG_EXCEPTION_HANDLED            (/*(DWORD   )*/0x00010001L)    
#define DBG_CONTINUE                     (/*(DWORD   )*/0x00010002L)    
#define STATUS_SEGMENT_NOTIFICATION      (/*(DWORD   )*/0x40000005L)    
#define DBG_TERMINATE_THREAD             (/*(DWORD   )*/0x40010003L)    
#define DBG_TERMINATE_PROCESS            (/*(DWORD   )*/0x40010004L)    
#define DBG_CONTROL_C                    (/*(DWORD   )*/0x40010005L)    
#define DBG_CONTROL_BREAK                (/*(DWORD   )*/0x40010008L)    
#define DBG_COMMAND_EXCEPTION            (/*(DWORD   )*/0x40010009L)    
#define STATUS_GUARD_PAGE_VIOLATION      (/*(DWORD   )*/0x80000001L)    
#define STATUS_DATATYPE_MISALIGNMENT     (/*(DWORD   )*/0x80000002L)    
#define STATUS_BREAKPOINT                (/*(DWORD   )*/0x80000003L)    
#define STATUS_SINGLE_STEP               (/*(DWORD   )*/0x80000004L)    
#define DBG_EXCEPTION_NOT_HANDLED        (/*(DWORD   )*/0x80010001L)    
#define STATUS_ACCESS_VIOLATION          (/*(DWORD   )*/0xC0000005L)    
#define STATUS_IN_PAGE_ERROR             (/*(DWORD   )*/0xC0000006L)    
#define STATUS_INVALID_HANDLE            (/*(DWORD   )*/0xC0000008L)    
#define STATUS_NO_MEMORY                 (/*(DWORD   )*/0xC0000017L)    
#define STATUS_ILLEGAL_INSTRUCTION       (/*(DWORD   )*/0xC000001DL)    
#define STATUS_NONCONTINUABLE_EXCEPTION  (/*(DWORD   )*/0xC0000025L)    
#define STATUS_INVALID_DISPOSITION       (/*(DWORD   )*/0xC0000026L)    
#define STATUS_ARRAY_BOUNDS_EXCEEDED     (/*(DWORD   )*/0xC000008CL)    
#define STATUS_FLOAT_DENORMAL_OPERAND    (/*(DWORD   )*/0xC000008DL)    
#define STATUS_FLOAT_DIVIDE_BY_ZERO      (/*(DWORD   )*/0xC000008EL)    
#define STATUS_FLOAT_INEXACT_RESULT      (/*(DWORD   )*/0xC000008FL)    
#define STATUS_FLOAT_INVALID_OPERATION   (/*(DWORD   )*/0xC0000090L)    
#define STATUS_FLOAT_OVERFLOW            (/*(DWORD   )*/0xC0000091L)    
#define STATUS_FLOAT_STACK_CHECK         (/*(DWORD   )*/0xC0000092L)    
#define STATUS_FLOAT_UNDERFLOW           (/*(DWORD   )*/0xC0000093L)    
#define STATUS_INTEGER_DIVIDE_BY_ZERO    (/*(DWORD   )*/0xC0000094L)    
#define STATUS_INTEGER_OVERFLOW          (/*(DWORD   )*/0xC0000095L)    
#define STATUS_PRIVILEGED_INSTRUCTION    (/*(DWORD   )*/0xC0000096L)    
#define STATUS_STACK_OVERFLOW            (/*(DWORD   )*/0xC00000FDL)    
#define STATUS_CONTROL_C_EXIT            (/*(DWORD   )*/0xC000013AL)    
#define STATUS_FLOAT_MULTIPLE_FAULTS     (/*(DWORD   )*/0xC00002B4L)    
#define STATUS_FLOAT_MULTIPLE_TRAPS      (/*(DWORD   )*/0xC00002B5L)    
#define STATUS_REG_NAT_CONSUMPTION       (/*(DWORD   )*/0xC00002C9L)    
#if defined(STATUS_SUCCESS) || (_WIN32_WINNT > 0x0500) || (_WIN32_FUSION >= 0x0100) 
#define STATUS_SXS_EARLY_DEACTIVATION    ((DWORD   )0xC015000FL)    
#define STATUS_SXS_INVALID_DEACTIVATION  ((DWORD   )0xC0150010L)    
#endif 

#define EXCEPTION_ACCESS_VIOLATION          STATUS_ACCESS_VIOLATION
#define EXCEPTION_DATATYPE_MISALIGNMENT     STATUS_DATATYPE_MISALIGNMENT
#define EXCEPTION_BREAKPOINT                STATUS_BREAKPOINT
#define EXCEPTION_SINGLE_STEP               STATUS_SINGLE_STEP
#define EXCEPTION_ARRAY_BOUNDS_EXCEEDED     STATUS_ARRAY_BOUNDS_EXCEEDED
#define EXCEPTION_FLT_DENORMAL_OPERAND      STATUS_FLOAT_DENORMAL_OPERAND
#define EXCEPTION_FLT_DIVIDE_BY_ZERO        STATUS_FLOAT_DIVIDE_BY_ZERO
#define EXCEPTION_FLT_INEXACT_RESULT        STATUS_FLOAT_INEXACT_RESULT
#define EXCEPTION_FLT_INVALID_OPERATION     STATUS_FLOAT_INVALID_OPERATION
#define EXCEPTION_FLT_OVERFLOW              STATUS_FLOAT_OVERFLOW
#define EXCEPTION_FLT_STACK_CHECK           STATUS_FLOAT_STACK_CHECK
#define EXCEPTION_FLT_UNDERFLOW             STATUS_FLOAT_UNDERFLOW
#define EXCEPTION_INT_DIVIDE_BY_ZERO        STATUS_INTEGER_DIVIDE_BY_ZERO
#define EXCEPTION_INT_OVERFLOW              STATUS_INTEGER_OVERFLOW
#define EXCEPTION_PRIV_INSTRUCTION          STATUS_PRIVILEGED_INSTRUCTION
#define EXCEPTION_IN_PAGE_ERROR             STATUS_IN_PAGE_ERROR
#define EXCEPTION_ILLEGAL_INSTRUCTION       STATUS_ILLEGAL_INSTRUCTION
#define EXCEPTION_NONCONTINUABLE_EXCEPTION  STATUS_NONCONTINUABLE_EXCEPTION
#define EXCEPTION_STACK_OVERFLOW            STATUS_STACK_OVERFLOW
#define EXCEPTION_INVALID_DISPOSITION       STATUS_INVALID_DISPOSITION
#define EXCEPTION_GUARD_PAGE                STATUS_GUARD_PAGE_VIOLATION
#define EXCEPTION_INVALID_HANDLE            STATUS_INVALID_HANDLE
#define EXCEPTION_POSSIBLE_DEADLOCK         STATUS_POSSIBLE_DEADLOCK

//
// The following flags control the contents of the CONTEXT structure.
//

#define CONTEXT_i386    0x00010000    // this assumes that i386 and
#define CONTEXT_i486    0x00010000    // i486 have identical context records

#define CONTEXT_CONTROL         (CONTEXT_i386 | 0x00000001L) // SS:SP, CS:IP, FLAGS, BP
#define CONTEXT_INTEGER         (CONTEXT_i386 | 0x00000002L) // AX, BX, CX, DX, SI, DI
#define CONTEXT_SEGMENTS        (CONTEXT_i386 | 0x00000004L) // DS, ES, FS, GS
#define CONTEXT_FLOATING_POINT  (CONTEXT_i386 | 0x00000008L) // 387 state
#define CONTEXT_DEBUG_REGISTERS (CONTEXT_i386 | 0x00000010L) // DB 0-3,6,7
#define CONTEXT_EXTENDED_REGISTERS  (CONTEXT_i386 | 0x00000020L) // cpu specific extensions

#define CONTEXT_FULL (CONTEXT_CONTROL | CONTEXT_INTEGER |\
                      CONTEXT_SEGMENTS)

#define CONTEXT_ALL (CONTEXT_CONTROL | CONTEXT_INTEGER | CONTEXT_SEGMENTS | CONTEXT_FLOATING_POINT | CONTEXT_DEBUG_REGISTERS | CONTEXT_EXTENDED_REGISTERS)

typedef struct _MEMORY_BASIC_INFORMATION {
    PVOID BaseAddress;
    PVOID AllocationBase;
    DWORD AllocationProtect;
    SIZE_T RegionSize;
    DWORD State;
    DWORD Protect;
    DWORD Type;
} MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;

typedef struct _MEMORY_BASIC_INFORMATION32 {
    DWORD BaseAddress;
    DWORD AllocationBase;
    DWORD AllocationProtect;
    DWORD RegionSize;
    DWORD State;
    DWORD Protect;
    DWORD Type;
} MEMORY_BASIC_INFORMATION32, *PMEMORY_BASIC_INFORMATION32;

/*
typedef struct DECLSPEC_ALIGN(16) _MEMORY_BASIC_INFORMATION64 {
    ULONGLONG BaseAddress;
    ULONGLONG AllocationBase;
    DWORD     AllocationProtect;
    DWORD     __alignment1;
    ULONGLONG RegionSize;
    DWORD     State;
    DWORD     Protect;
    DWORD     Type;
    DWORD     __alignment2;
} MEMORY_BASIC_INFORMATION64, *PMEMORY_BASIC_INFORMATION64;
*/

#define SECTION_QUERY       0x0001
#define SECTION_MAP_WRITE   0x0002
#define SECTION_MAP_READ    0x0004
#define SECTION_MAP_EXECUTE 0x0008
#define SECTION_EXTEND_SIZE 0x0010

#define SECTION_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SECTION_QUERY|\
                            SECTION_MAP_WRITE |      \
                            SECTION_MAP_READ |       \
                            SECTION_MAP_EXECUTE |    \
                            SECTION_EXTEND_SIZE)
#define PAGE_NOACCESS          0x01     
#define PAGE_READONLY          0x02     
#define PAGE_READWRITE         0x04     
#define PAGE_WRITECOPY         0x08     
#define PAGE_EXECUTE           0x10     
#define PAGE_EXECUTE_READ      0x20     
#define PAGE_EXECUTE_READWRITE 0x40     
#define PAGE_EXECUTE_WRITECOPY 0x80     
#define PAGE_GUARD            0x100     
#define PAGE_NOCACHE          0x200     
#define PAGE_WRITECOMBINE     0x400     
#define MEM_COMMIT           0x1000     
#define MEM_RESERVE          0x2000     
#define MEM_DECOMMIT         0x4000     
#define MEM_RELEASE          0x8000     
#define MEM_FREE            0x10000     
#define MEM_PRIVATE         0x20000     
#define MEM_MAPPED          0x40000     
#define MEM_RESET           0x80000     
#define MEM_TOP_DOWN       0x100000     
#define MEM_WRITE_WATCH    0x200000     
#define MEM_PHYSICAL       0x400000     
#define MEM_LARGE_PAGES  0x20000000     
#define MEM_4MB_PAGES    0x80000000     
#define SEC_FILE           0x800000     
#define SEC_IMAGE         0x1000000     
#define SEC_RESERVE       0x4000000     
#define SEC_COMMIT        0x8000000     
#define SEC_NOCACHE      0x10000000     
#define MEM_IMAGE         SEC_IMAGE     
#define WRITE_WATCH_FLAG_RESET 0x01     

WINBASEAPI
BOOL
WINAPI
GetThreadContext(
    IN HANDLE hThread,
    IN OUT PCONTEXT lpContext
    );

WINBASEAPI
BOOL
WINAPI
SetThreadContext(
    IN HANDLE hThread,
    IN CONST CONTEXT *lpContext
    );

//

WINBASEAPI
VOID
WINAPI
DebugBreak(
    VOID
    );

WINBASEAPI
BOOL
WINAPI
WaitForDebugEvent(
    IN LPDEBUG_EVENT lpDebugEvent,
    IN DWORD dwMilliseconds
    );

WINBASEAPI
BOOL
WINAPI
ContinueDebugEvent(
    IN DWORD dwProcessId,
    IN DWORD dwThreadId,
    IN DWORD dwContinueStatus
    );

WINBASEAPI
BOOL
WINAPI
DebugActiveProcess(
    IN DWORD dwProcessId
    );

WINBASEAPI
BOOL
WINAPI
DebugActiveProcessStop(
    IN DWORD dwProcessId
    );

WINBASEAPI
BOOL
WINAPI
DebugSetProcessKillOnExit(
    IN BOOL KillOnExit
    );

WINBASEAPI
BOOL
WINAPI
DebugBreakProcess (
    IN HANDLE Process
    );

WINBASEAPI
BOOL
WINAPI
CreateProcessA(
    IN LPCSTR lpApplicationName,
    IN LPSTR lpCommandLine,
    IN LPSECURITY_ATTRIBUTES lpProcessAttributes,
    IN LPSECURITY_ATTRIBUTES lpThreadAttributes,
    IN BOOL bInheritHandles,
    IN DWORD dwCreationFlags,
    IN LPVOID lpEnvironment,
    IN LPCSTR lpCurrentDirectory,
    IN LPSTARTUPINFOA lpStartupInfo,
    OUT LPPROCESS_INFORMATION lpProcessInformation
    );
WINBASEAPI
BOOL
WINAPI
CreateProcessW(
    IN LPCWSTR lpApplicationName,
    IN LPWSTR lpCommandLine,
    IN LPSECURITY_ATTRIBUTES lpProcessAttributes,
    IN LPSECURITY_ATTRIBUTES lpThreadAttributes,
    IN BOOL bInheritHandles,
    IN DWORD dwCreationFlags,
    IN LPVOID lpEnvironment,
    IN LPCWSTR lpCurrentDirectory,
    IN LPSTARTUPINFOW lpStartupInfo,
    OUT LPPROCESS_INFORMATION lpProcessInformation
    );

WINBASEAPI
BOOL
WINAPI
VirtualFreeEx(
    IN HANDLE hProcess,
    IN LPVOID lpAddress,
    IN SIZE_T dwSize,
    IN DWORD dwFreeType
    );

WINBASEAPI
BOOL
WINAPI
VirtualProtectEx(
    IN  HANDLE hProcess,
    IN  LPVOID lpAddress,
    IN  SIZE_T dwSize,
    IN  DWORD flNewProtect,
    OUT DWORD* lpflOldProtect
    );

WINBASEAPI
SIZE_T
WINAPI
VirtualQueryEx(
    IN HANDLE hProcess,
    IN LPCVOID lpAddress,
    OUT PMEMORY_BASIC_INFORMATION lpBuffer,
    IN SIZE_T dwLength
    );

WINBASEAPI
BOOL
WINAPI
SetCurrentDirectoryA(
    IN LPCSTR lpPathName
    );
WINBASEAPI
BOOL
WINAPI
SetCurrentDirectoryW(
    IN LPCWSTR lpPathName
    );

WINBASEAPI
DWORD
WINAPI
GetCurrentProcessId(
    VOID
    );

// Directory Entries

#define IMAGE_DIRECTORY_ENTRY_EXPORT          0   // Export Directory

//
// DLL support.
//

//
// Export Format
//

typedef struct _IMAGE_EXPORT_DIRECTORY {
    DWORD   Characteristics;
    DWORD   TimeDateStamp;
    uint16    MajorVersion;
    uint16    MinorVersion;
    DWORD   Name;
    DWORD   Base;
    DWORD   NumberOfFunctions;
    DWORD   NumberOfNames;
    DWORD   AddressOfFunctions;     // RVA from base of image
    DWORD   AddressOfNames;         // RVA from base of image
    DWORD   AddressOfNameOrdinals;  // RVA from base of image
} IMAGE_EXPORT_DIRECTORY, *PIMAGE_EXPORT_DIRECTORY;

}	// extern "C"

}	// MSWindows
}	// System

#endif

#include "../CodeComp/macholoader.h"

#if WIN32

#include "../Include/coff.h"

/*
#include "../include/CodeView.h"
#include "../include/Microsoft/cvinfo.h"
*/

//extern DebugThread* g_pt;

#endif

#if AMIGA

//ULONG trap_number;
uint16 sr;
uint32 ret_pc;
long debugger_regs[16];

extern struct Task* pMonitorTask;
extern ULONG nSig;

//ULONG addr;
struct Task* task;

//void (*ret_pc)();

int nDebugeeSig;

extern "C" void TrapLoop()
{
//	printf("Trap %x\n", ret_pc);
	task = FindTask(NULL);

//	addr = ret_pc;

	nDebugeeSig = AllocSignal(-1);
	Signal(pMonitorTask, 1<<nSig);

	// Wait for the debugger to tell us to continue
	execWait(SysBase, 1<<nDebugeeSig);
	FreeSignal(nDebugeeSig);
}

extern "C" void VTrap0();
extern "C" void VTrace();

__asm(
		
		"xdef _VTrace\n"
	  "xdef _VTrap0\n"
"\n"
"_VTrace:\n"
"	move.w 0(sp),_sr\n"
"	move.l 2(sp),_ret_pc\n"
"	movem.l d0-d7/a0-a6,_debugger_regs\n"
"	jsr _TrapLoop\n"
"	move.w _sr,0(sp)\n"
"	move.l _ret_pc,2(sp)\n"
"	movem.l _debugger_regs,d0-d7/a0-a6\n"
"	rte\n"

"_VTrap0:\n"
"	move.w 0(sp),_sr\n"
"	move.l 2(sp),_ret_pc\n"
"	movem.l d0-d7/a0-a6,_debugger_regs\n"
"	jsr _TrapLoop\n"
"	move.w _sr,0(sp)\n"
"	move.l _ret_pc,2(sp)\n"
"	movem.l _debugger_regs,d0-d7/a0-a6\n"
"	rte\n"

);

/*
_VTrap0:
	move.w 0(sp),_sr
	move.l 2(sp),_ret_pc
	jsr _TrapLoop
	move.w _sr,0(sp)
	move.l _ret_pc,2(sp)
	rte
*/

//	move.l usp,a0
//	move.l a0,_regs+15*4

void OnExit()
{
	printf("Exited\n");
}

	/*
void CMainFrame::OpenProgram(STRPTR filename)
{
	m_ctx = new DebuggerCtx;

}
*/

#endif

namespace System
{
using namespace javavm;
using namespace IO;

namespace Debugger
{
using namespace std;

System::NamedType* DebugRecv::LookupNamedType(System::StringA* name)
{
	return NULL;
}

System::Type* DebugRecv::CreatePointerType(System::Type_type type, System::Type* pPointerTo)
{
	if (type == type_pointer)
	{
		return new PointerType(pPointerTo);
	}
	else if (type == type_reference)
	{
		return new ReferenceType(pPointerTo);
	}
	else
	{
		ASSERT(0);
		return NULL;
	}
}

void DebugRecv::OnSymbol(System::StringA* name, ULONG address, ULONG dwData)
{
	DebugSymbol* pSymbol = new DebugSymbol(name, address);

	if (strstr(name->c_str(), "main"))
	{
		MessageBeep(-1);
	}

	m_ctx->m_pDebugInfo->m_symbols.insert(tysymbolmap_address::value_type(address, pSymbol));
	m_ctx->m_pDebugInfo->m_symbols_name.insert(tysymbolmap_name::value_type(name, pSymbol));

	m_pModule->m_symbols.insert(tysymbolmap_address::value_type(address, pSymbol));
}

void DebugRecv::OnType(System::StringA* name, System::NamedType* type, ULONG dwData)
{
}

System::Scope* DebugRecv::OnProc(System::Scope* pScope, System::StringA* name, System::Type* type, ULONG startAddress, ULONG endAddress, ULONG dwData)
{
	ASSERT(pScope);

	Scope* pProcScope = new Scope;
	pProcScope->m_pParentScope = pScope;
	pProcScope->m_startAddress = startAddress;
	pProcScope->m_endAddress = endAddress;

	pScope->m_subScopes.push_back(pProcScope);

	return pProcScope;
}

System::Scope* DebugRecv::End(System::Scope* pScope)
{
	return pScope->m_pParentScope;
}

void DebugRecv::OnData(System::StringA* name, System::Type* type, ULONG_PTR address, ULONG_PTR dwData)
{
}

System::StringA* DebugRecv::CreateString(System::StringA* str)
{
	return str;
}

#if WIN32

__live_object_ptr<DebugThread> g_pt;
//DWORD WINAPI DebuggerStartProc(LPVOID lpParameter);

#endif

//#include "../ljavac/cppcompiler.h"

Scope* pGlobalScope;

Scope* FindScope(Scope* pScope, ULONG_PTR find_address)
{
	for (uint i = 0; i < pScope->m_subScopes.size(); i++)
	{
		Scope* pScope2 = pScope->m_subScopes[i];
		if (find_address >= pScope2->m_startAddress && find_address <= pScope2->m_endAddress)
		{
			return FindScope(pScope2, find_address);
		}
	}

	return pScope;
}

static SourceLocation* FindSourceLocation2(const vector<SourceFile*> & sourceFiles, ULONG_PTR find_address)
{
	SourceLocation* sourceLocation = NULL;

// Find source file that this location belongs to
	for (uint i = 0; i < sourceFiles.size(); i++)
	{
		SourceFile* sourceFile = sourceFiles[i];

		for (uint j = 0; j < sourceFile->m_segments.GetSize(); j++)
		{
			SourceFile::Segment& segment = sourceFile->m_segments[j];

			if (segment.m_startAddress <= find_address &&
				segment.m_endAddress > find_address)
			{
				ASSERT(sourceLocation == NULL);

				sourceLocation = new SourceLocation;
				sourceLocation->file = sourceFile;

				int last_line = 0;

				for (int n = 0; n < sourceFile->m_lines.GetSize(); n++)
				{
					SourceFile::SourceLine& line = sourceFile->m_lines[n];

					if (line.m_address > find_address)
						break;

					last_line = line.m_line;
				}
#if 0
				DWORD last_fun_address = segment.m_startAddress;

				for (int nstab = 0; nstab < sourceFile->m_stabvec.size(); nstab++)
				{
					nlist* pStab = sourceFile->m_stabvec[nstab];

					if (pStab->n_type == N_FUN)
					{
						last_fun_address = /*sourceFile->startAddress +*/ pStab->n_value;
					}
					else if (pStab->n_type == N_SLINE)
					{
						int line_address = last_fun_address + pStab->n_value;

						if (line_address > find_address)
							break;

						last_line = pStab->n_desc;
					}
				}
#endif

				sourceLocation->line = last_line;
			//	return sourceLocation;
			}
		}
	}

	return sourceLocation;
}

DebuggerCtx::DebuggerCtx()
{
	m_frame = NULL;
	m_cpu = CPU_UNKNOWN;

#if WIN32
	m_pImage = NULL;
#endif

#if WIN32
	m_pJavaVMHost = NULL;
#endif

	m_pDebugInfo = NULL;

#if WIN32

	m_threadId = 0;
	m_hThread = NULL;

	m_dwProcessId = 0;
	m_pDebugProcess = NULL;

#elif __APPLE__

	m_dwProcessId = 0;

#endif
}

ULONG DebuggerCtx::GetEip() const
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

SourceLocation* DebuggerCtx::FindSourceLocation(ULONG_PTR find_address)
{
	if (m_pDebugInfo)
		return FindSourceLocation2(m_pDebugInfo->m_sourceFiles, find_address);
	else
		return NULL;
}

bool DebuggerCtx::ResolveBreakpoint(DebugBreakpoint* pBreakpoint)
{
	for (uint i = 0; i < m_pDebugInfo->m_sourceFiles.size(); i++)
	{
		SourceFile* sourceFile = m_pDebugInfo->m_sourceFiles[i];
		if (!_stricmp(pBreakpoint->m_filename->c_str(), sourceFile->m_filename->c_str()))
		{
		//	DWORD address = 0;//sourceFile->
			uint nlines = sourceFile->m_lines.GetSize();
			for (uint i = 0; i < nlines; i++)
			{
				SourceFile::SourceLine& srcline = sourceFile->m_lines[i];
				if (srcline.m_line >= pBreakpoint->m_line)
				{
					ULONG_PTR address = srcline.m_address;// + pSymbol->n_value;
					AddBreakpoint(address);
					return true;
				}
			}
#if 0
			DWORD last_fun_address = 0;

			for (int j = 0; j < sourceFile->m_stabvec.size(); j++)
			{
				nlist* pSymbol = sourceFile->m_stabvec[j];

				if (pSymbol->n_type == N_FUN)
				{
					last_fun_address = /*sourceFile->startAddress +*/ pSymbol->n_value;
				}
				else if (pSymbol->n_type == N_SLINE)
				{
					int line = pSymbol->n_desc-1;
					if (line >= pBreakpoint->m_line)
					{
						if (line > pBreakpoint->m_line)
						{
							pBreakpoint->m_line = line;

							// TODO
							// MessageBox
						}

						int address = last_fun_address + pSymbol->n_value;
						AddBreakpoint(address);
						return true;
					}
				}
			}
#endif
		}
	}
	return false;
}

bool DebuggerCtx::AddBreakpoint(ULONG_PTR address)
{
	bool bSuccess = false;

#if WIN32

	HANDLE hProcess = NULL;
	if (m_dwProcessId)
	{
		hProcess = MSWindows::OpenProcess(PROCESS_ALL_ACCESS, false, m_dwProcessId);//m_ctx->GetProcessById(m_dwProcessId);
		if (hProcess == NULL)
			return false;
	}

#elif AMIGA

	Task* hProcess = NULL;	// TODO

#elif __APPLE__

	mach_port_t hProcess;	// TODO

#endif

	if (m_cpu == CPU_IX86)
	{
		InstrPlaceholder old_instruction;
		ULONG nRead;
		MSWindows::ReadProcessMemory(hProcess, (LPVOID)address, &old_instruction, 1, &nRead);
		if (nRead == 1)
		{
			InstrPlaceholder int_instruction;
			int_instruction.n[0] = 0xCC;	// int 3

			ULONG nWritten;
			MSWindows::WriteProcessMemory(hProcess, (LPVOID)address, &int_instruction, 1, &nWritten);
			if (nWritten == 1)
			{
				m_breakpoints.insert(tybreakpointmap::value_type(address, Breakpoint(old_instruction)));
				bSuccess = true;
			}
		}
	}
	else if (m_cpu == CPU_M68K)
	{
		if (address & 1)	// address must 2-byte aligned
		{
			ASSERT(0);
		}
		else
		{
			InstrPlaceholder old_instruction;
			MSWindows::DWORD nRead;
			MSWindows::ReadProcessMemory(hProcess, (LPVOID)address, &old_instruction, 2, &nRead);
			if (nRead == 2)
			{
				InstrPlaceholder trap_instruction;
				trap_instruction.n[0] = 0x4E;
				trap_instruction.n[1] = 0x40;	// trap #0

				MSWindows::DWORD nWritten;
				MSWindows::WriteProcessMemory(hProcess, (LPVOID)address, &trap_instruction, 2, &nWritten);
				if (nWritten == 2)
				{
					m_breakpoints.insert(tybreakpointmap::value_type(address, Breakpoint(old_instruction)));
					bSuccess = true;
				}
			}
		}
	}
	else if (m_cpu == CPU_PPC)
	{
		if (address & 3)	// address must be 4-byte aligned
		{
			ASSERT(0);
		}
		else
		{
		}
	}
	else if (m_cpu == CPU_JAVA_IL)
	{
		InstrPlaceholder old_instruction;
		old_instruction.n[0] = *(uint8*)address;

		*(uint8*)address = 0xca;

		m_breakpoints.insert(tybreakpointmap::value_type(address, Breakpoint(old_instruction)));
	}
	else
		ASSERT(0);

#if WIN32
	if (m_dwProcessId)
	{
		MSWindows::CloseHandle(hProcess);
	}
#endif

	return bSuccess;
}

//CodeCompExt cpp::CDeclarator* stab_lsym(char* p, cpp::Scope* pScope);

#if WIN32

MSWindows::DWORD WINAPI DebuggerStartProc(LPVOID lpParameter   // thread data
)
{
//	CoInitialize(NULL);

	__live_object_ptr<DebuggerCtx> ctx = (DebuggerCtx*)lpParameter;

//	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS/* | PROCESS_QUERY_INFORMATION | PROCESS_DUP_HANDLE*/, FALSE, ctx->dwProcessId);

//	if (DebugActiveProcess(ctx->dwProcessId))

	MSWindows::STARTUPINFOA si = {0};
	si.cb = sizeof(si);
	si.lpTitle = "test";
	si.wShowWindow = SW_SHOWDEFAULT;

	char* pathName = (char*)alloca(ctx->m_frame->m_pathName->Length()+1);
	std::memcpy(pathName, ctx->m_frame->m_pathName->c_str(), ctx->m_frame->m_pathName->Length());
	pathName[ctx->m_frame->m_pathName->Length()] = 0;

	MSWindows::PROCESS_INFORMATION pi;
	pi.hProcess = NULL;
	if (MSWindows::CreateProcessA(
		NULL,		// lpApplicationName
		pathName,	// lpCommandLine
		NULL,	// lpProcessAttributes
		NULL,	// lpThreadAttributes
		true,	// bInheritHandles
		DEBUG_PROCESS | DEBUG_ONLY_THIS_PROCESS | CREATE_NEW_CONSOLE,	// dwCreationFlags
		NULL,	// lpEnvironment
		NULL,	// lpCurrentDirectory	
		&si,	// lpStartupInfo
		&pi))	// lpProcessInformation
	{
		if (true)
		{
			ctx->m_dwProcessId = pi.dwProcessId;
			//ctx->frame->m_dwProcessId = pi.dwProcessId;	// TODO remove

			/*
					DebugProcess* pr = new DebugProcess;
					pr->m_hProcess = pi.hProcess;
					pr->m_dwProcessId = pi.dwProcessId;

				// Add first thread
					DebugThread* pt = new DebugThread;
					pt->m_dwThreadId = pi.dwThreadId;
					pt->m_hThread = pi.hThread;
				//	pt->m_lpStartAddress = DebugEv.u.CreateProcessInfo.lpStartAddress;
//					pr->m_hThread = DebugEv.u.CreateProcessInfo.hThread;	// TODO remove
					pr->m_threads.insert(tyhthreadmap::value_type(pt->m_dwThreadId, pt));

					ctx->processes.insert(tyhprocessmap::value_type(pr->m_dwProcessId, pr));
					*/
		}

		//HANDLE hProcess;

		uint dwContinueStatus = DBG_CONTINUE;

		MSWindows::DEBUG_EVENT DebugEv;
		for (;;)
		{
			if (ctx->m_pDebugProcess)
			{
				ctx->m_pDebugProcess->m_bRunning = true;
			}

			if (!MSWindows::WaitForDebugEvent(&DebugEv, INFINITE))
			{
				ASSERT(0);
			}

			if (ctx->m_pDebugProcess)
			{
				ctx->m_pDebugProcess->m_bRunning = false;
			}

			switch (DebugEv.dwDebugEventCode)
			{
			case EXCEPTION_DEBUG_EVENT:
				{
					String str;
					dwContinueStatus = DBG_EXCEPTION_NOT_HANDLED;

					switch (DebugEv.u.Exception.ExceptionRecord.ExceptionCode)
					{            
						//--standard exceptions
					case EXCEPTION_ACCESS_VIOLATION:
						str = L"Access Violation";
						break; 
						
					case EXCEPTION_DATATYPE_MISALIGNMENT:
						str = L"Datatype Misalignment";
						break;
						
					case EXCEPTION_BREAKPOINT:
						{
							str = L"Breakpoint";
							dwContinueStatus = DBG_CONTINUE;
							
							tyhprocessmap::iterator pri = ctx->processes.find(DebugEv.dwProcessId);
							tyhthreadmap::iterator thi = (*pri).second->m_threads.find(DebugEv.dwThreadId);

							g_pt = (*thi).second;

							(*thi).second->m_context.ContextFlags = CONTEXT_INTEGER | CONTEXT_CONTROL;
							MSWindows::GetThreadContext((*thi).second->m_hThread, &(*thi).second->m_context);

							tybreakpointmap::iterator bi = ctx->m_breakpoints.find((ULONG_PTR)DebugEv.u.Exception.ExceptionRecord.ExceptionAddress);
							if (bi != ctx->m_breakpoints.end())
							{
								// Write back the old byte so the real instruction can be executed
								ULONG nWritten;
								uint8 byte = (*bi).second.m_oldbyte.n[0];
								MSWindows::WriteProcessMemory((*pri).second->m_hProcess, (LPVOID)DebugEv.u.Exception.ExceptionRecord.ExceptionAddress, &byte, 1, &nWritten);
							
							// Reset this so the old instruction will be executed
								(*thi).second->m_context.Eip = (ULONG_PTR)DebugEv.u.Exception.ExceptionRecord.ExceptionAddress;
							}

							ctx->m_Eip = (*thi).second->m_context.Eip;//(ULONG)DebugEv.u.Exception.ExceptionRecord.ExceptionAddress;

						//	ASSERT(0);
#if 0
							PostMessage(ctx->frame->GetHwnd(), WM_USER+2, 0, 0);
#endif
							ctx->m_frame->OnException();

							MSWindows::MSG msg;
							MSWindows::GetMessageA(&msg, NULL, 0, 0);

							MessageBeep(-1);
							// Single step trap
						//	context.EFlags |= 1<<8;
							MSWindows::SetThreadContext((*thi).second->m_hThread, &(*thi).second->m_context);
						}
						break;
						
					case EXCEPTION_SINGLE_STEP:
						{
						//	str = "Single Step";
							dwContinueStatus = DBG_CONTINUE;

							tyhprocessmap::iterator pri = ctx->processes.find(DebugEv.dwProcessId);
							tyhthreadmap::iterator thi = (*pri).second->m_threads.find(DebugEv.dwThreadId);

							g_pt = (*thi).second;
							
							(*thi).second->m_context.ContextFlags = CONTEXT_INTEGER | CONTEXT_CONTROL;
							MSWindows::GetThreadContext((*thi).second->m_hThread, &(*thi).second->m_context);
							ctx->m_Eip = (*thi).second->m_context.Eip;//(ULONG)DebugEv.u.Exception.ExceptionRecord.ExceptionAddress;

						//	ASSERT(0);
#if 0
							PostMessage(ctx->frame->GetHwnd(), WM_USER+2, 0, 0);
#endif

							ctx->m_frame->OnException();
							/*
							pLocation = ctx->FindSourceLocation(ctx->frame->m_Eip);
							if (pLocation)
							{
								TRACE("source file: %s # %d\n", pLocation->file->sourceFileName.c_str(), pLocation->line);

								ctx->frame->PostMessage(WM_USER+2, pLocation->line, (LPARAM)strdup(pLocation->file->sourceFileName.c_str()));
								ctx->frame->m_disassemblyWnd->m_linesOffset = pLocation->line;

								//	ctx->frame->m_disassemblyWnd.m_linesOffset = pLocation->line;
								//pLocation
							//	delete pLocation;
							}

						//	DebugEv.u.Exception.ExceptionRecord.ExceptionInformation.ExceptionRecordExceptionRecord.ExceptionRecord->Ebp;

							if (ctx->frame->m_disassemblyWnd)
								ctx->frame->m_disassemblyWnd->SetActive(ctx->frame->m_Eip);

							if (ctx->frame->m_registersWnd)
								ctx->frame->m_registersWnd->Invalidate();

							if (ctx->frame->m_callStackWnd)
								ctx->frame->m_callStackWnd->Update();

							if (ctx->frame->m_watchWnd)
								ctx->frame->m_watchWnd->Update();
								*/

							MSWindows::MSG msg;
							MSWindows::GetMessageA(&msg, NULL, 0, 0);

							MessageBeep(-1);

							/*
							// Single step trap
							context.EFlags |= 1<<8;
							*/
							MSWindows::SetThreadContext((*thi).second->m_hThread, &(*thi).second->m_context);
						}
						break;
						
						//-- Debug exceptions
					case DBG_TERMINATE_THREAD:
						str = L"Terminate Thread";
						break;
						
					case DBG_TERMINATE_PROCESS:
						str = L"Terminate Process";
						break;
						
					case DBG_CONTROL_C:
						str = L"Control+C";
						break;
						
					case DBG_CONTROL_BREAK:
						str = L"Control+Break";
						break;
						
					default:
						str = L"Unknown";
					}
					
					if (str->Length())
					{
						TRACE("%s", str->c_str());
#if 0
						ctx->m_frame->m_messages += "Exception: " + str + "\r\n";
#endif
					}
				}
				break;
				
			case CREATE_THREAD_DEBUG_EVENT:
				{
					char msg[512];
					sprintf_s(msg, "Thread started at %8.8X\r\n", DebugEv.u.CreateThread.lpStartAddress);
				//	ctx->frame->m_messages += msg;

					tyhprocessmap::iterator pri = ctx->processes.find(DebugEv.dwProcessId);
					ASSERT(pri != ctx->processes.end());

					DebugThread* pt = new DebugThread;
					pt->m_dwThreadId = DebugEv.dwThreadId;
					pt->m_hThread = DebugEv.u.CreateThread.hThread;
					pt->m_lpStartAddress = DebugEv.u.CreateThread.lpStartAddress;

					(*pri).second->m_threads.insert(tyhthreadmap::value_type(DebugEv.dwThreadId, pt));
				}
				break;

			case CREATE_PROCESS_DEBUG_EVENT:
				{
					DebugProcess* pr = new DebugProcess;
					pr->m_hProcess = DebugEv.u.CreateProcessInfo.hProcess;
					pr->m_dwProcessId = DebugEv.dwProcessId;

					ASSERT(ctx->m_pDebugProcess == NULL);
					ctx->m_pDebugProcess = pr;

				// Add first thread
					DebugThread* pt = new DebugThread;
					pt->m_dwThreadId = DebugEv.dwThreadId;
					pt->m_hThread = DebugEv.u.CreateProcessInfo.hThread;
					pt->m_lpStartAddress = DebugEv.u.CreateProcessInfo.lpStartAddress;
//					pr->m_hThread = DebugEv.u.CreateProcessInfo.hThread;	// TODO remove
					pr->m_threads.insert(tyhthreadmap::value_type(DebugEv.dwThreadId, pt));

					ctx->processes.insert(tyhprocessmap::value_type(DebugEv.dwProcessId, pr));

				// As as first module
					DebugModule* pModule = new DebugModule;
					pModule->m_base = (ULONG)DebugEv.u.CreateProcessInfo.lpBaseOfImage;

					if (DebugEv.u.CreateProcessInfo.lpImageName)
					{
						tyhprocessmap::iterator hpi = ctx->processes.find(DebugEv.dwProcessId);
						HANDLE hProcess = (*hpi).second->m_hProcess;
						{
							LPVOID p = NULL;
							MSWindows::DWORD nRead;
							MSWindows::ReadProcessMemory(hProcess, DebugEv.u.CreateProcessInfo.lpImageName, &p, 4, &nRead);
							if (p)
							{
								char nameBuffer[281*2];
								int size;
								if (DebugEv.u.CreateProcessInfo.fUnicode)
									size = 280*2;
								else
									size = 280;

								StringW* name;

								MSWindows::ReadProcessMemory(hProcess, p, &nameBuffer, size, &nRead);
								if (DebugEv.u.CreateProcessInfo.fUnicode)
									name = new StringW(string_copy((WCHAR*)nameBuffer));
								else
									name = (new StringA(string_copy((char*)nameBuffer)))->ToStringW();

								/*
								char msg[512];
								sprintf(msg, "Loaded exports for '%S'\r\n", name->c_str());
								TRACE(msg);
								*/
								//ctx->m_frame->m_messages += msg;

								pModule->m_name = name;
							}
						}
					//DebugEv.u.LoadDll.hFile;
					}

					DebugRecv recv;
					recv.m_ctx = ctx;
					recv.m_pModule = pModule;

					{
						FileByteStream* file = FileByteStream::FromHandle(DebugEv.u.CreateProcessInfo.hFile, false);
						ctx->m_pImage = new COFFParser;
						ctx->m_pImage->m_loadAddress = (ULONG)pModule->m_base;//pt->m_lpStartAddress;//(ULONG)hModules[n];

						if (ctx->m_pImage->Read(file) >= 0)
						{
							ctx->m_pDebugInfo = ctx->m_pImage->GetDebugInfo(pGlobalScope);
							if (ctx->m_pDebugInfo)
							{
								ctx->m_pDebugInfo->Parse(ctx->m_pImage, &recv, 0);
							}

#if 0
			Scope* pGlobalScope = new Scope;
			CodeViewDebugInfo* pDebugInfo = (CodeViewDebugInfo*)pImage->GetDebugInfo(NULL/*pGlobalScope*/);
			if (pDebugInfo)
			{
				TRACE("DebugInfo for %s...", filename);

				fprintf(stdout, "DebugInfo for %s...", filename);
				fflush(stdout);

				pDebugInfo->Parse(pImage, pD, n);
				pDebugInfo->Release();
				TRACE("\n");
			}
#endif

							pModule->m_size = ctx->m_pImage->m_windowsHeader->SizeOfImage;

#if 0
							DWORD codeBase;
							codeBase = ctx->m_pImage->windowsHeader->ImageBase + ctx->m_pImage->m_SectionHeader[0].VirtualAddress;
#endif

							unsigned int NumberOfNameSymbols = ctx->m_pImage->m_NumberOfNameSymbols;
							for (unsigned int i = 0; i < NumberOfNameSymbols; i++)
							{
								COFFParser::SYMBOL* pSymbol = &ctx->m_pImage->m_NameSymbols[i];
								if (pSymbol->is->SectionNumber > 0)
								{
									IMAGE_SECTION_HEADER *pSection = &ctx->m_pImage->m_SectionHeader[pSymbol->is->SectionNumber-1];
									ULONG address = pSymbol->is->Value /*- pSection->VirtualAddress*/ + ctx->m_pImage->m_windowsHeader->ImageBase + pSection->VirtualAddress/* + pSection->Misc.PhysicalAddress*/;

									DebugSymbol* pDebugSymbol = new DebugSymbol(new StringA(string_copy(pSymbol->name)), address);

									pModule->m_symbols.insert(tysymbolmap_address::value_type(pDebugSymbol->m_address, pDebugSymbol));

									ctx->m_pDebugInfo->m_symbols.insert(tysymbolmap_address::value_type(pDebugSymbol->m_address, pDebugSymbol));
									ctx->m_pDebugInfo->m_symbols_name.insert(tysymbolmap_name::value_type(pDebugSymbol->m_name, pDebugSymbol));

								//	TRACE("%s - %X\n", pSymbol->name, address);

									if (!strcmp(pSymbol->name, ".text"))
									{
									//	MessageBeep(-1);
									}
								}
							}

							/*
							int numberOfSymbols = pImage->GetNumberOfSymbols();

							for (int i = 0; i  < numberOfSymbols; i++)
							{
							}
							*/
					//		nlist* stab = NULL;
					//		int nstabs = 0;
					//		char* stabstr = NULL;
						
						//	FromStab(ctx);
						//	FromCV(ctx);
						}
					}

					ctx->m_modules.Add(pModule);

					/*
					if (DebugEv.u.CreateProcessInfo.lpImageName)
					{
					//	tyhprocessmap::iterator hpi = processes.find(DebugEv.dwProcessId);
						HANDLE hProcess = pr->hProcess;

						DWORD p;
						DWORD nRead;
						ReadProcessMemory(hProcess, DebugEv.u.CreateProcessInfo.lpImageName, &p, 4, &nRead);
						if (p)
						{
							printf("Process loaded\n");
						}
					//DebugEv.u.LoadDll.hFile;
					}
*/
	//				ctx->frame->m_addr = codeBase;

					if (DebugEv.u.CreateProcessInfo.hThread)
					{
						MSWindows::CONTEXT context;
						context.ContextFlags = CONTEXT_FULL;

						MSWindows::GetThreadContext(DebugEv.u.CreateProcessInfo.hThread, &context);

						ctx->m_frame->m_disassemblyWnd->SetActive(context.Eip);
					//	ctx->frame->m_disassemblyWnd.m_addr = 0x401000;
					//	ctx->frame->m_disassemblyWnd.ReadBuffer();

					//	ctx->AddBreakpoint(0x43BE08);
						ctx->AddBreakpoint(0x401000);
					}

					// Resolve breakpoints
					{
						for (int i = 0; i < ctx->m_userbreakpoints.size(); i++)
						{
							DebugBreakpoint* pBreakpoint = ctx->m_userbreakpoints[i];
							ctx->ResolveBreakpoint(pBreakpoint);
						}
					}

					char msg[512];
					sprintf_s(msg, "Process started with threadId: %x\r\n", DebugEv.dwProcessId);

					TRACE(msg);

					//ASSERT(0);
#if 0
					ctx->m_frame->m_messages += msg;
#endif
				}
				break;

			case EXIT_THREAD_DEBUG_EVENT:
				{
					char msg[512];
					sprintf_s(msg, "The thread %s has exited with code %d (0x%x)\r\n", "(null)", DebugEv.u.ExitThread.dwExitCode, DebugEv.u.ExitThread.dwExitCode);
					ASSERT(0);
#if 0
					ctx->m_frame->m_messages += msg;
#endif

					tyhprocessmap::iterator pri = ctx->processes.find(DebugEv.dwProcessId);
					ASSERT(pri != ctx->processes.end());

					ASSERT(0);
#if 0	// TODO
					(*pri).second->m_threads.erase(DebugEv.dwThreadId);
#endif

					/*
					tyhthreadmap::iterator ti = (*pri).second->m_threads.find(DebugEv.dwThreadId);
					ATLASSERT(ti != (*pri).second->m_threads.end());
					(*pri).second->m_threads.erase(ti, ti);
					*/
				}
				break;

			case EXIT_PROCESS_DEBUG_EVENT:
				{
					tyhprocessmap::iterator pr = ctx->processes.find(DebugEv.dwProcessId);
					ASSERT(pr != ctx->processes.end());

					char msg[512];
					sprintf_s(msg, "The program %s has exited with code %d (0x%x)\r\n", (*pr).second->m_filename->c_str(), DebugEv.u.ExitProcess.dwExitCode, DebugEv.u.ExitProcess.dwExitCode);
					//ASSERT(0);
					TRACE(msg);
#if 0
					ctx->m_frame->m_messages += msg;
#endif
				}
				break;

			case LOAD_DLL_DEBUG_EVENT:
				{
					DebugModule* pModule = new DebugModule;
					pModule->m_base = (ULONG)DebugEv.u.LoadDll.lpBaseOfDll;

					FileByteStream* file = FileByteStream::FromHandle(DebugEv.u.LoadDll.hFile, false);
					COFFParser* pImage = new COFFParser;
					if (pImage->Read(file) >= 0)
					{
						pModule->m_size = pImage->m_windowsHeader->SizeOfImage;

						if (pImage->m_windowsHeader->NumberOfRvaAndSizes > IMAGE_DIRECTORY_ENTRY_EXPORT)
						{
							if (pImage->m_DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress)
							{
								uint fpos = pImage->RVA2FilePos(pImage->m_DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

								MSWindows::IMAGE_EXPORT_DIRECTORY* ied = (MSWindows::IMAGE_EXPORT_DIRECTORY*)(pImage->m_fbuf + fpos);

								uint32 fposFunctions = pImage->RVA2FilePos(ied->AddressOfFunctions);
								uint32 fposNames = pImage->RVA2FilePos(ied->AddressOfNames);
								uint32 fposOrdinals = pImage->RVA2FilePos(ied->AddressOfNameOrdinals);

								uint32* functions = (uint32*)(pImage->m_fbuf + fposFunctions);
								uint32* names = (uint32*)(pImage->m_fbuf + fposNames);
								uint16* ordinals = (uint16*)(pImage->m_fbuf + fposOrdinals);
								for (uint i = 0; i < ied->NumberOfNames; i++)
								{
									uint32 fposName = pImage->RVA2FilePos(names[i]);
									char* name = (char*)(pImage->m_fbuf + fposName);

									uint16 index = ordinals[i] - ied->Base;
									if (index >= 0 && index < ied->NumberOfFunctions)
									{
										uint32 funaddress = functions[index];

										uint32 address = funaddress + (uint32)DebugEv.u.LoadDll.lpBaseOfDll;

										//DWORD fposName = pImage->RVA2FilePos(names[i]);


									//	TRACE("%s - %X\n", name, address);

										// TODO
#if 0
										DebugSymbol* pDebugSymbol = new DebugSymbol(name, address);
										pModule->symbols.insert(tysymbolmap_address::value_type(address, pDebugSymbol));
										ctx->m_pDebugInfo->symbols.insert(tysymbolmap_address::value_type(address, pDebugSymbol));
#endif
									}
								}
							}
						}
					}
					delete pImage;

					ctx->m_modules.Add(pModule);

					if (DebugEv.u.LoadDll.lpImageName)
					{
						tyhprocessmap::iterator hpi = ctx->processes.find(DebugEv.dwProcessId);
						HANDLE hProcess = (*hpi).second->m_hProcess;
						{
							LPVOID p = NULL;
							MSWindows::DWORD nRead;
							MSWindows::ReadProcessMemory(hProcess, DebugEv.u.LoadDll.lpImageName, &p, 4, &nRead);
							if (p)
							{
								char nameBuffer[281*2];
								int size;
								if (DebugEv.u.LoadDll.fUnicode)
									size = 280*2;
								else
									size = 280;

								StringW* name;

								MSWindows::ReadProcessMemory(hProcess, p, &nameBuffer, size, &nRead);
								if (DebugEv.u.LoadDll.fUnicode)
									name = new StringW(string_copy((WCHAR*)nameBuffer));
								else
									name = (new StringA(string_copy(((char*)nameBuffer))))->ToStringW();

								char msg[512];
								sprintf_s(msg, "Loaded exports for '%S'\r\n", name->c_str());
								TRACE(msg);
								//ctx->m_frame->m_messages += msg;

								pModule->m_name = name;
							}
						}
					//DebugEv.u.LoadDll.hFile;
					}
				}
				break;

			case UNLOAD_DLL_DEBUG_EVENT:
				{
				//	ctx->m_frame->m_messages += "UNLOAD_DLL_DEBUG_EVENT\r\n";
				}
				break;

			case OUTPUT_DEBUG_STRING_EVENT:
				{
				//	ctx->m_frame->m_messages += "OUTPUT_DEBUG_STRING_EVENT\r\n";
				}
				break;

			case RIP_EVENT:
				{
				//	ctx->m_frame->m_messages += "RIP_EVENT\r\n";
				}
				break;
			}
// Resume executing the thread that reported the debugging event. 

//				GetThreadContext(DebugEv.dwThreadId, 

			/*
			printf(">");
			char cmd[256];
			gets(cmd);
			*/

#if 0	// TODO
			ctx->frame->m_wndMessages.SetWindowText(ctx->frame->m_messages.c_str());
#endif

			MSWindows::ContinueDebugEvent(DebugEv.dwProcessId, 
				DebugEv.dwThreadId, dwContinueStatus);
		}

		return 0;
	}
	else
	{
		MessageBoxA(NULL, "Failed to create process\n", "LDebugger", MB_OK);
		return -1;
	}
}

#endif // _WINDOWS

//#include "../CodeComp/debug.h"

#if __APPLE__

static void DebugErrorFunc(struct dyld_debug_error_data* e)
{
    printf("dyld error \n");
	fflush(stdout);
}

static void event_routine(struct dyld_event  event)
{
	printf("event routine\n");
	fflush(stdout);
}

#endif

void DebuggerCtx::ReadBuffer(void* m_buffer, LPVOID PMAAddress, ULONG PMASize)
{
	if (m_cpu == CPU_JAVA_IL || m_cpu == CPU_FLASH_IL)
	{
		memcpy(m_buffer, PMAAddress, (PMASize));
		return;
	}

#if WIN32

//	if (m_cpu == CPU_IX86)
	{
		if (m_dwProcessId == 0)
			return;

		HANDLE hProcess = MSWindows::OpenProcess(PROCESS_ALL_ACCESS, false, m_dwProcessId);//m_ctx->GetProcessById(m_dwProcessId);

		//??EnterCriticalSection(&m_pFrame->m_bufferCS);
		
		MSWindows::MEMORY_BASIC_INFORMATION mbi;
		MSWindows::DWORD Protect = 0;

		if (!MSWindows::VirtualQueryEx (hProcess,  
			PMAAddress,  
			&mbi,   
			sizeof (MSWindows::MEMORY_BASIC_INFORMATION)) || 
			mbi.State != MEM_COMMIT)    
		{  
		//	PMASize = 0;
		//	SetEvent (hDbgEvent [ACKNOWLEDGE]);  
		//	break;  
			printf("Error");
		} 
	/* if guarded memory, change protection temporarily */ 
		if (!(mbi.Protect & PAGE_READONLY) &&     !(mbi.Protect & PAGE_READWRITE))
		{
			MSWindows::VirtualProtectEx (hProcess,    
				PMAAddress, 
				PMASize,    
				PAGE_READONLY,  
				&Protect); 
		}

		memset(m_buffer, 0, PMASize);
		MSWindows::DWORD nRead;
		if (!MSWindows::ReadProcessMemory(hProcess, PMAAddress, m_buffer, PMASize, &nRead))
		{
			printf("Error\n");
		}

		if (nRead != PMASize)
		{
		//	MessageBox("0", "0", MB_OK);
		}

	/* reset protection if changed */
		if (Protect)
		{
			MSWindows::VirtualProtectEx (hProcess,
			PMAAddress,
			PMASize,
			Protect,
			&Protect); 
		}

		//??LeaveCriticalSection(&m_pFrame->m_bufferCS);

		MSWindows::CloseHandle(hProcess);
	}

#elif __APPLE__

	if (m_cpu == CPU_PPC
	{
		if (m_dwProcessId == 0)
			return;

	//	ULONG PMASize = numlines * 4;
	//	if (PMASize > 0x1000) PMASize = 0x1000;

		task_t task;
		task_for_pid(mach_task_self(), m_dwProcessId, &task);

	//	printf("task: %d\n", task);
	//	fflush(stdout);

		vm_size_t size = 0x1000;
		int ret = vm_read_overwrite(task, (vm_address_t)PMAAddress, PMASize, (vm_address_t)m_buffer, &size);

		if (ret == 0)
		{
			printf("vm_read_overwrite() = 0, size = %d\n", size);
			fflush(stdout);
		}
		else
		{
			if (ret == KERN_PROTECTION_FAILURE)
			{
				printf("vm_read_overwrite() = KERN_PROTECTION_FAILURE\n");
				fflush(stdout);
			}
			else if (ret == KERN_INVALID_ADDRESS)
			{
				printf("vm_read_overwrite() = KERN_INVALID_ADDRESS\n");
				fflush(stdout);
			}
		}
	}

//	return;

//	memcpy(m_buffer, PMAAddress, PMASize);

#elif AMIGA

//	ULONG PMASize = numlines * 14;
//	if (PMASize > 0x1000) PMASize = 0x1000;

	memcpy(m_buffer, PMAAddress, PMASize);

#endif
}

#if WIN32

class ActiveScriptCallback : public SWF::ICallback
{
public:
	virtual void OnScript(SWF::ActionScript* script);

	DebuggerCtx* m_ctx;
};

void ActiveScriptCallback::OnScript(SWF::ActionScript* script)
{
	SourceFile* pSourceFile = new SourceFile;
	pSourceFile->m_segments.Add(SourceFile::Segment((ULONG)script->m_data, (ULONG)script->m_data + script->m_length));

	SWF::VM2 vm;
	vm.m_pFrame = new SWF::VM2::StackFrame;
	vm.m_pFrame->m_pContext = new SWF::VM2::ActionContext;
	vm.m_pFrame->m_instructionsData = script->m_data;
	vm.m_pFrame->m_instructionsLength = script->m_length;
	vm.pc = script->m_data;

	vm.next();

	std::string str = vm.m_str.str();

	WCHAR* data = new WCHAR[str.length()];
	for (int i = 0; i < str.length(); i++)
	{
		data[i] = str[i];
	}

	TRACE("\n%s\n", str.c_str());

	TextData* textdata = new TextData;
	textdata->SetData(data, str.length());

	TextLines* textdoc = new TextLines(textdata);

	SourceTextDocument* sourceTextDocument = new SourceTextDocument;

	pSourceFile->m_userdata = sourceTextDocument;

	sourceTextDocument->m_tdp = textdoc;

//	textdoc
//	pSourceFile->m_lines.Add(SourceFile::SourceLine(lineNumbers[i].start_pc + (ULONG)pCode->code, lineNumbers[i].line_number-1));
	for (int i = 0; i < vm.lines.size(); i++)
	{
		pSourceFile->m_lines.Add(SourceFile::SourceLine((ULONG)script->m_data + vm.lines[i].pc, vm.lines[i].line));
	}

	m_ctx->m_pDebugInfo->m_sourceFiles.Add(pSourceFile);
}

void DebuggerCtx::JavaVMHost::OnLoadedClass(JavaClass* pClass)
{
	String sourceFileName = pClass->GetSourceFile();
	if (sourceFileName != NULL)
	{
		SourceFile* pSourceFile = new SourceFile;

		char* str = _strdup(pClass->GetName()->c_str());
		char* p = str + strlen(str)-1;

		while (*p != '/')
			p--;

		*p = 0;

		char filename[512];
		sprintf_s(filename, "C:/Program Files/Java/jdk1.6.0_06/src/%s/%s", str, sourceFileName->ToStringA()->c_str());

		pSourceFile->m_filename = new StringA(string_copy(filename));//sourceFileName->ToStringA();

		for (int i = 0; i < pClass->m_methods_count; i++)
		{
			JavaMethod* pMethod = pClass->m_methods[i];

			CodeAttribute* pCode = pMethod->GetCode();
			if (pCode)
			{
				pSourceFile->m_segments.Add(SourceFile::Segment((ULONG)pCode->code, (ULONG)pCode->code + pCode->code_length));

				vector<LineNumber> lineNumbers;
				pCode->GetLineNumbers(lineNumbers);

				for (int i = 0; i < lineNumbers.GetSize(); i++)
				{
					pSourceFile->m_lines.Add(SourceFile::SourceLine(lineNumbers[i].start_pc + (ULONG)pCode->code, lineNumbers[i].line_number-1));
				}
			}
		}

		m_ctx->m_pDebugInfo->m_sourceFiles.Add(pSourceFile);
	}
}
#endif

void DebuggerCtx::RemoveAllBreakpoints()
{
#if 0
	filesmap::iterator fi = m_files.begin();
	while (fi != m_files.end())
	{
		ASSERT(0);
#if 0	// TODO
		(*fi).second->pEdit->m_breakpoints.clear();
#endif
	//	(*fi).second->pEdit->Invalidate();	// TODO, improve

		++fi;
	}
#endif

	m_userbreakpoints.clear();
}

HANDLE m_hJavaStartedEvent;
HANDLE m_hJavaBreakEvent;
HANDLE m_hJavaContinueEvent;

MSWindows::DWORD CALLBACK JavaStart(LPVOID param)
{
	javavm::Thread* thread = (javavm::Thread*)param;
	DebuggerCtx::JavaVMHost* host = (DebuggerCtx::JavaVMHost*)thread->m_vm->m_pHost;

	thread->m_vm->Init();

	{
		JavaClass* pClass = thread->LoadClass(ASTR("java/lang/ThreadGroup"));
		JavaObject* threadGroup = pClass->CreateInstance();
		{
			jmethodID methodID = thread->m_jni->GetMethodID((jclass)(threadGroup->m_pClass), "<init>", "()V");
			thread->m_jni->CallVoidMethod((jobject)threadGroup, methodID);
		}
		//*(jint*)(threadGroup->m_data + pClass->GetFieldByName("maxPriority")->m_offset) = 10;

		{
			JavaClass* pClass = thread->LoadClass(ASTR("java/lang/Thread"));
			thread->m_p = pClass->CreateInstance();
			*(jint*)(thread->m_p->m_data + pClass->GetFieldByName(ASTR("priority"))->m_offset) = 5;
		//	*(jlong*)(thread->m_p->m_data + pClass->GetFieldByName("stackSize")->m_offset) = 65536;
			*(JavaObject**)(thread->m_p->m_data + pClass->GetFieldByName(ASTR("group"))->m_offset) = threadGroup;
		}
	}

	JavaClass* pSystemClass = thread->LoadClass(ASTR("java/lang/System"));
	{
		/*
		{
			JavaClass* pClass = thread->LoadClass("java/lang/SecurityManager");
			JavaObject* pSecurity = pClass->CreateInstance();
			CJavaField* pField = pClass->GetFieldByName("security");
			*(JavaObject**)(pSystemClass->m_staticData + pField->m_offset) = pSecurity;
		}
		*/
	}

	{
		{
			jmethodID methodID = thread->m_jni->GetMethodID((jclass)pSystemClass, "initializeSystemClass", "()V");

			JavaMethod* pMethod = (JavaMethod*)methodID;
			host->m_ctx->m_Eip = (ULONG)pMethod->GetCode()->code;

	MSWindows::SetEvent(m_hJavaStartedEvent);

		//	if (false)
			{
		//	m_frame->OnException();	// Fake a breakpoint hit at start
			host->m_ctx->AddBreakpoint(host->m_ctx->m_Eip);
			//*(uint8*)host->m_ctx->m_frame->m_Eip = 0xca;	// Breakpoint
			}

			thread->m_vm->m_flags |= 1;	// single-step

			thread->m_jni->CallStaticVoidMethod((jclass)pSystemClass, methodID);
		}
	}

	JNIEnv* env = thread->m_jni;

	if (true)
	{
		jclass pClass = env->FindClass("testclass");
	//	JavaObject* obj = pClass->CreateInstance();
		jmethodID pMethod = env->GetStaticMethodID(pClass, "main", "([Ljava/lang/String;)I");//pClass->GetMethodByName(ASTR("main([Ljava/lang/String;)I"));

		jclass pStringArrayClass = env->FindClass("[Ljava/lang/String;");
		jobject pStringArray = env->AllocObject(pStringArrayClass);//pStringArrayClass->CreateInstance();

		int retval = env->CallStaticIntMethod(pClass, pMethod, pStringArray);
	}

	return 0;
}

void JavaBreakpoint(javavm::Thread* c, int cause)
{
	DebuggerCtx::JavaVMHost* host = (DebuggerCtx::JavaVMHost*)c->m_vm->m_pHost;
	DebuggerCtx* ctx = host->m_ctx;
	ctx->m_Eip = (ULONG)c->m_pc;

	if (cause == 1)	// Breakpoint
	{
		// Restore the actual bytecode
		tybreakpointmap::iterator it = ctx->m_breakpoints.find((ULONG)c->m_pc);
		VERIFY(it != ctx->m_breakpoints.end());
		*c->m_pc = it->second.m_oldbyte.n[0];

		// Enable single-stepping so we can restore the breakpoint
	//	c->m_vm->m_flags |= 1;
#if 0
		thread->
#endif
	}
	else
	{
		if (true)	// Restore breakpoint
		{
			// if single-stepping because previous was a breakpoint and single-stepping isn't enabled, just continue
			if (false)
			{
				return;
			}
		}
	}

	ctx->m_frame->OnException();

	MSWindows::SetEvent(m_hJavaBreakEvent);
	MSWindows::WaitForSingleObject(m_hJavaContinueEvent, INFINITE);

//	MSWindows::MSG msg;
//	MSWindows::GetMessageA(&msg, NULL, 0, 0);
}

MSWindows::DWORD CALLBACK ActionScriptStart(LPVOID param)
{
	SWF::Player* player = (SWF::Player*)param;

	player->Play();

	return 0;
}

void ActionScriptBreakpoint(ActionScripting::VM* vm, Object* userobject, int cause)
{
	DebuggerCtx* ctx = static_cast<DebuggerCtx*>(userobject);
	ctx->m_Eip = (ULONG)vm->m_pc;
	ctx->m_actionScriptVM = vm;

	ctx->m_frame->OnException();

	MSWindows::SetEvent(m_hJavaBreakEvent);
	MSWindows::WaitForSingleObject(m_hJavaContinueEvent, INFINITE);
}

/*
MSWindows::DWORD CALLBACK JavaLoop(LPVOID param)
{
	DebuggerCtx* ctx = (DebuggerCtx*)param;

	while (1)
	{
		MSWindows::WaitForSingleObject(m_hJavaStartedEvent, INFINITE);

		MSWindows::PostThreadMessageA(ctx->m_javaThreadId, WM_USER, 0, 0);	// Continue
	}
}
*/

void DebuggerCtx::Start()
{
	printf("DebuggerCtx::Start()\n");

#if __APPLE__
	{
#if 0
		{
			FileByteStream file(m_frame->m_pathName);

			cpp::MachOLoader* ploader;
			ploader->Read(&file);

			m_pDebugInfo = new DebugInfo;

			long numberOfSymbols = ploader->GetNumberOfNameSymbols;

			for (int i = 0; i < numberOfSymbols; i++)
			{
				ObjectSymbol* pSymbol = ploader->GetSymbol(i);
				if (pSymbol->is->SectionNumber > 0)
				{
					SECTIOM section;
					ploader->GetSection(pSymbol->n_desc, &section);//m_pImage->SectionHeader[pSymbol->is->SectionNumber-1];
					DWORD address = pSymbol->is->Value /*- pSection->VirtualAddress*/ + ctx->m_pImage->windowsHeader->ImageBase + section.sectionHeader.VirtualAddress/* + pSection->Misc.PhysicalAddress*/;

					DebugSymbol* pDebugSymbol = new DebugSymbol(pSymbol->name, address);

					pModule->symbols.insert(tysymbolmap_address::value_type(pDebugSymbol->m_address, pDebugSymbol));

					ctx->m_pDebugInfo->symbols.insert(tysymbolmap_address::value_type(pDebugSymbol->m_address, pDebugSymbol));
					ctx->m_pDebugInfo->symbols_name.insert(tysymbolmap_name::value_type(pDebugSymbol->m_name, pDebugSymbol));

				//	TRACE("%s - %X\n", pSymbol->name, address);

					/*
					if (!strcmp(pSymbol->name, ".text"))
					{
					//	MessageBeep(-1);
					}
					*/
				}
			}

			delete ploader;
		}
#endif

		m_cpu = CPU_PPC;

		int pid = vfork();

		if (pid < 0)
			printf("Error");

		if (pid == 0)	// child
		{
			ptrace(PT_TRACE_ME, 0, 0, 0);	// Allow the parent to debug us
			
			{
				char argv0[512];
				strcpy(argv0, m_frame->m_pathName.c_str());
				char* argv[] = {argv0/*"/Users/g3233/test/build/test"*/, NULL};
				printf("Child");
				fflush(stdout);
				//sleep(5);
				execvp(m_frame->m_pathName.c_str()/*"/Users/g3233/test/build/test"*/, argv);
			}
			
			printf("Error executing child\n");
			fflush(stdout);
		}
		else
		{
			//sleep(10);
			printf("Parent continues");
			fflush(stdout);
		}

		m_dwProcessId = pid;

		{
			task_t itask = 0;
			
			thread_array_t thread_list;
			unsigned int thread_count;
			
			task_for_pid(mach_task_self(), pid, &itask);
			printf("task: %d\n", itask);
			fflush(stdout);

		//	_dyld_debug_set_error_func(DebugErrorFunc);

			/*
			{
				mach_port_t port;
				mach_port_allocate(mach_task_self(), MACH_PORT_RIGHT_RECEIVE, &port);
				printf("port: %d", port);
			}
			*/
			
		
			{
				int err = 0;
				
				/*
				err = ptrace(PT_ATTACH, pid, 0, 0);
				
				  if (err != 0)
				  {
				  printf("ptrace attach errno %d, %s", errno, strerror(errno));
				  fflush(stdout);
				  }
				*/
				
				{
					// Wait for messages from the traced program
					int wait_val;
					wait(&wait_val);

					_dyld_debug_subscribe_to_events(itask, 0, 0, true, event_routine);

					{
						task_threads(itask, &thread_list, &thread_count);
						thread_t thread = thread_list[0];
						vm_deallocate(mach_task_self(), (vm_address_t)thread_list, thread_count * sizeof(thread_t));
			
						struct gdb_ppc_thread_state gp_regs;
						unsigned int gp_count = GDB_PPC_THREAD_STATE_COUNT;
						thread_get_state(thread/*mach_thread_self()*/, GDB_PPC_THREAD_STATE, (thread_state_t)&gp_regs, &gp_count);

						m_frame->m_Eip = gp_regs.srr0;
						{
							int i;
							for (i = 0; i < 32; i++)
							{
								printf("r%d=%d, ", i, gp_regs.gpregs[i]);
							}
						}

					//	m_disassemblyWnd->SetActive(m_Eip);
					}
					/*
			dyld_debug_return dylderr;
			dylderr = _dyld_debug_subscribe_to_events(itask, 0, 0, true, event_routine);
			printf("dylderr: %d\n", dylderr);
			fflush(stdout);
			*/

					if (false)
					{
						err = ptrace(PT_CONTINUE, pid, (caddr_t)1, 0);
					}
				}
				if (err != 0)
				{
					printf("ptrace continue err: %d, errno: %s\n", err, strerror(errno));
					fflush(stdout);
				}
				
				/*
				err = ptrace(PT_CONTINUE, pid, (caddr_t)1, 0);
				
				  if (err != 0)
				  {
				  printf("ptrace continue err: %d, errno: %s", err, strerror(errno));
				  fflush(stdout);
				  }
				*/
			}
		}
		return;
	}
#endif

#if WIN32
	if (true)
	{
		if (false)
		{
			m_cpu = CPU_FLASH_IL;

			m_pDebugInfo = new JavaDebugInfo;

			m_activeScriptCallback = new ActiveScriptCallback;
			m_activeScriptCallback->m_ctx = this;

			FileByteStream* file = new FileByteStream(ASTR("C:/mmstudio/test.swf"));

			SWF::Decoder* decoder = new SWF::Decoder(new SWF::FormatStream(file));

			decoder->m_callback = m_activeScriptCallback;

			decoder->ReadHeader();

			SWF::Movie* movie = new SWF::Movie;

			movie->m_scriptFlags |= 1;
			movie->m_scriptBreakpoint = ActionScriptBreakpoint;
			movie->m_scriptUserObject = this;

			decoder->ReadMovieHeader(movie);

			SWF::Player* player = new SWF::Player;
			player->m_decoder = decoder;
			player->SetMovie(movie);

			m_hJavaStartedEvent = MSWindows::CreateEventA(NULL, false, false, NULL);
			m_hJavaBreakEvent = MSWindows::CreateEventA(NULL, false, false, NULL);
			m_hJavaContinueEvent = MSWindows::CreateEventA(NULL, false, false, NULL);
			m_javaThread = MSWindows::CreateThread(NULL, 0, ActionScriptStart, player, 0, &m_javaThreadId);
		//	MSWindows::WaitForSingleObject(m_hJavaStartedEvent, INFINITE);
		}
		else if (true)
		{
			// TODO, improve

			m_cpu = CPU_JAVA_IL;

			m_pDebugInfo = new JavaDebugInfo;

			m_pJavaVMHost = new JavaVMHost;
			m_pJavaVMHost->m_ctx = this;

			m_pJavaVMHost->m_pJavaVM = new javavm::JProcess;
			m_pJavaVMHost->m_pJavaVM->m_pHost = m_pJavaVMHost;
			m_pJavaVMHost->m_pJavaVM->Breakpoint = JavaBreakpoint;
			
			javavm::Thread* thread = new javavm::Thread;
			thread->m_vm = m_pJavaVMHost->m_pJavaVM;

			m_pJavaVMHost->m_pJavaVM->m_threads.Add(thread);
			
			m_hJavaStartedEvent = MSWindows::CreateEventA(NULL, false, false, NULL);
			m_hJavaBreakEvent = MSWindows::CreateEventA(NULL, false, false, NULL);
			m_hJavaContinueEvent = MSWindows::CreateEventA(NULL, false, false, NULL);
			m_javaThread = MSWindows::CreateThread(NULL, 0, JavaStart, thread, 0, &m_javaThreadId);
			MSWindows::WaitForSingleObject(m_hJavaStartedEvent, INFINITE);
		//	MSWindows::CloseHandle(m_hJavaStartedEvent);
		//	m_frame->OnException();	// Fake a breakpoint hit at start

			if (false)
			{
				m_pJavaVMHost->m_pJavaVM->Init();

			//	JavaClass* classfile = new JavaClass;
			//	m_pJavaVM->m_pJavaClass = classfile;
			//	m_pJavaClass = classfile;

			//	classfile->Parse(new FileByteStream(m_frame->m_pathName));

				{
					JavaClass* pClass = thread->LoadClass(ASTR("java/lang/ThreadGroup"));
					JavaObject* threadGroup = pClass->CreateInstance();
					{
						jmethodID methodID = thread->m_jni->GetMethodID((jclass)(threadGroup->m_pClass), "<init>", "()V");
						thread->m_jni->CallVoidMethod((jobject)threadGroup, methodID);
					}
					//*(jint*)(threadGroup->m_data + pClass->GetFieldByName("maxPriority")->m_offset) = 10;

					{
						JavaClass* pClass = thread->LoadClass(ASTR("java/lang/Thread"));
						thread->m_p = pClass->CreateInstance();
						*(jint*)(thread->m_p->m_data + pClass->GetFieldByName(ASTR("priority"))->m_offset) = 5;
					//	*(jlong*)(thread->m_p->m_data + pClass->GetFieldByName("stackSize")->m_offset) = 65536;
						*(JavaObject**)(thread->m_p->m_data + pClass->GetFieldByName(ASTR("group"))->m_offset) = threadGroup;
					}
				}

				JavaClass* pSystemClass = thread->LoadClass(ASTR("java/lang/System"));
				{
					/*
					{
						JavaClass* pClass = thread->LoadClass("java/lang/SecurityManager");
						JavaObject* pSecurity = pClass->CreateInstance();
						CJavaField* pField = pClass->GetFieldByName("security");
						*(JavaObject**)(pSystemClass->m_staticData + pField->m_offset) = pSecurity;
					}
					*/
				}

				{
					{
						jmethodID methodID = thread->m_jni->GetMethodID((jclass)pSystemClass, "initializeSystemClass", "()V");

						JavaMethod* pMethod = (JavaMethod*)methodID;
						m_Eip = (ULONG)pMethod->GetCode()->code;

					//	m_frame->OnException();	// Fake a breakpoint hit at start
						*(uint8*)m_Eip = 0xca;	// Breakpoint

						thread->m_jni->CallStaticVoidMethod((jclass)pSystemClass, methodID);
					}
				}

				MSWindows::SetCurrentDirectoryA("C:\\");
				JavaClass* classfile = thread->LoadClass(ASTR("Test"));
				// Invoke 'main' method
				{
					JavaMethod* pMethod = classfile->GetMethodByName(ASTR("main([Ljava/lang/String;)V"));
					CodeAttribute* pCode = pMethod->GetCode();

					thread->m_pFrame = new javavm::Frame(pMethod, pCode);
					m_pJavaVMHost->m_pJavaVM->m_threads.Add(thread);

					m_Eip = (ULONG)(pCode->code);
				//	thread->pc = (uint8*)m_frame->m_Eip;

					m_CodeLength = pCode->code_length;
				}

				while (thread->next_instruction() == 0)
					;
			}

		}
		else
		{
			m_cpu = CPU_IX86;

			m_hThread = MSWindows::CreateThread(NULL, 0, DebuggerStartProc, this, 0, &m_threadId);
		}
	}
	else
#endif

	if (true)
	{


		AmigaHunkParser* pHunkParser = new AmigaHunkParser;
		{
			FileByteStream file(m_frame->m_pathName);
			pHunkParser->Read(&file);
		}

		m_cpu = CPU_M68K;
		printf("CPU_M68K\n");

		ULONG ret_pc;

#if AMIGA

		BPTR seglist = NewLoadSegTags(m_frame->m_pathName->c_str(), (TAG_DONE));

		if (seglist == 0)
		{
			printf("Failed to load file\n");
			return;
		}

		ret_pc = (uint32)BADDR(seglist) + 4;

#else

		{
			for (int i = 0; i < 1/*pHunkParser->GetNumberOfSections()*/; i++)
			{
				ULONG size = pHunkParser->GetDataSize(i);
				uint8* data = new uint8[4096 + size];
				memcpy(data, pHunkParser->GetData(i), size);

				int nrelocs = pHunkParser->GetNumberOfRelocations(i);
				for (int j = 0; j < nrelocs; j++)
				{
					//data + r_address
				}

				ret_pc = (ULONG)data;// + 0x00330f20;//0x00330f2e;//0x2f60b6;
			}

			m_Eip = ret_pc;
		}


#if WIN32
		m_dwProcessId = MSWindows::GetCurrentProcessId();
#endif

#endif

		if (pHunkParser->stab)
		{
			m_pDebugInfo = pHunkParser->GetDebugInfo(pGlobalScope);

		//	FromStab(m_ctx->sourceFiles, pGlobalScope, ret_pc, pHunkParser->stab, pHunkParser->nstabs);
		}

		printf("Entrypoint: 0x%x\n", ret_pc);

		AddBreakpoint(ret_pc);
#if AMIGA
		uint32 segaddr = ret_pc;//(uint32)BADDR(seglist) + 4;
#else
		uint32 segaddr = m_Eip;
#endif

#if 0	// TODO, have this
		int nsymbols = pHunkParser->GetNumberOfSymbols();
		for (int i = 0; i < nsymbols; i++)
		{
			ObjectSymbol* pSymbol = pHunkParser->GetSymbol(i);
		//	printf("%s - 0x%x\n", pSymbol->n_name, pSymbol->n_value);

		//	printf("segaddr: 0x%x\n", segaddr + pSymbol->n_value);

			DebugSymbol* pDebugSymbol = new DebugSymbol(pSymbol->n_name, segaddr + pSymbol->n_value);

			m_pDebugInfo->symbols.insert(tysymbolmap_address::value_type(pDebugSymbol->m_address, pDebugSymbol));
			m_pDebugInfo->symbols_name.insert(tysymbolmap_name::value_type(pDebugSymbol->m_name, pDebugSymbol));
		}
#endif

		delete pHunkParser;

		SourceLocation* plocation = FindSourceLocation(0x2f60b6);

		m_frame->OnException();	// Fake a breakpoint hit at start

//		m_frame->m_Eip = 2f60b6;//(ULONG)(pCode->code);

#if AMIGA

		{
			//	Forbid();

			struct Process* pr = CreateNewProcTags(
			//	(NP_Entry), (ULONG)testfunc,
				(NP_Seglist), seglist,
		//		(NP_Output), out,
				(NP_ExitCode), (ULONG)OnExit,
				(TAG_DONE));
			if (pr)
			{
			//	task = &pr->pr_Task;
			//	Permit();

				;//printf("created process at %x\n", pr);
			}
			else
			{
				printf("Failed to create process\n");
			}
			//printf("");
		}
#endif
	}
	else
	{
#if WIN32
		m_dwProcessId = MSWindows::GetCurrentProcessId();
#endif

		AOutParser* pParser = new AOutParser;
		{
			FileByteStream file(m_frame->m_pathName);
			pParser->Read(&file);
		}

		m_cpu = pParser->GetCPU();

		// text section

		ULONG size = pParser->GetDataSize(0);
		uint8* data = new uint8[4096 + size];
		memcpy(data, pParser->GetData(0), size);

		ULONG ret_pc = (ULONG)data;
		m_Eip = ret_pc;

		int nsymbols = pParser->GetNumberOfSymbols();
		for (int i = 0; i < nsymbols; i++)
		{
			ObjectSymbol* pSymbol = pParser->GetSymbol(i);
		//	printf("%s - 0x%x\n", pSymbol->n_name, pSymbol->n_value);

		//	printf("segaddr: 0x%x\n", segaddr + pSymbol->n_value);

			DebugSymbol* pDebugSymbol = new DebugSymbol(new StringA(string_copy(pSymbol->n_name)), ret_pc + pSymbol->n_value);

			TRACE("%s\n", pSymbol->n_name);

#if 0	// TODO
			m_pDebugInfo->symbols.insert(tysymbolmap_address::value_type(pDebugSymbol->m_address, pDebugSymbol));
			m_pDebugInfo->symbols_name.insert(tysymbolmap_name::value_type(pDebugSymbol->m_name, pDebugSymbol));
#endif
		}

		m_frame->OnException();	// Fake a breakpoint hit at start
	}
}

void DebuggerCtx::Continue()
{
#if WIN32
	if (m_cpu == CPU_IX86)
	{
		MSWindows::PostThreadMessageA(m_threadId, WM_USER+1, 0, 0);
	}
#endif

	if (m_pJavaVMHost)
	{
		m_pJavaVMHost->m_pJavaVM->m_flags &= ~1;	// clear single-step

		MSWindows::SetEvent(m_hJavaContinueEvent);
#if 0
		m_pJavaVMHost->m_pJavaVM->m_threads[0]->next_instruction();
		m_frame->m_Eip = (ULONG)m_pJavaVMHost->m_pJavaVM->m_threads[0]->m_pFrame->pc;
		m_frame->OnException();
#endif
		return;
	}

#if __APPLE__
	if (m_cpu == CPU_PPC)
	{
		ptrace(PT_CONTINUE, m_dwProcessId, (caddr_t)1, 0);
	}
#endif
}

void DebuggerCtx::StepInto()
{
//	DebugProcess* pr = m_ctx->GetProcessById(m_dwProcessId);
//	DebugThread* pt = pr->GetThreadById(m_threadId);
/*
	CONTEXT context;
	context.ContextFlags = CONTEXT_CONTROL;

	GetThreadContext(pt->m_hThread, &context);
*/

#if WIN32
	if (m_pJavaVMHost)
	{
		MSWindows::SetEvent(m_hJavaContinueEvent);
#if 0
		m_pJavaVMHost->m_pJavaVM->m_threads[0]->next_instruction();
		m_frame->m_Eip = (ULONG)m_pJavaVMHost->m_pJavaVM->m_threads[0]->m_pFrame->pc;
		m_frame->OnException();
#endif
		return;
	}
#endif

#if WIN32

	if (g_pt)
	{
	// Single step trap
		g_pt->m_context.EFlags |= 1<<8;
	//	SetThreadContext(pt->m_hThread, &context);

		MSWindows::PostThreadMessageA(m_threadId, WM_USER+2, 0, 0);
	}

#elif AMIGA

	if (m_cpu == CPU_M68K)
	{
		sr |= 1<<15;	// set trace bit
		Signal(task, 1<<nDebugeeSig);
	}

#elif __APPLE__

	if (m_cpu == CPU_PPC)
	{
		int ret = ptrace(PT_STEP, m_dwProcessId, (caddr_t)1, 0);

		if (ret == -1)
		{
			printf("ptrace() errno: %d\n", errno);
			fflush(stdout);

			// EINVAL;
			// EBUSY
		}

		// Wait for messages from the traced program
		int wait_val;
		wait(&wait_val);

		{
			task_t task;
			task_for_pid(mach_task_self(), m_dwProcessId, &task);

			thread_array_t thread_list;
			unsigned int thread_count;
			task_threads(task, &thread_list, &thread_count);
			thread_t thread = thread_list[0];
			vm_deallocate(mach_task_self(), (vm_address_t)thread_list, thread_count * sizeof(thread_t));

			struct gdb_ppc_thread_state gp_regs;
			unsigned int gp_count = GDB_PPC_THREAD_STATE_COUNT;
			thread_get_state(thread/*mach_thread_self()*/, GDB_PPC_THREAD_STATE, (thread_state_t)&gp_regs, &gp_count);

			m_frame->m_Eip = gp_regs.srr0;
	}

		m_frame->OnException();
	}

#endif
}

}
}
