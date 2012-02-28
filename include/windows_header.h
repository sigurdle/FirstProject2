#ifndef windows_header_h
#define windows_header_h

#include "windows_types.h"

#define NEAR
#define FAR

#include <windows_waveformat.h>

#ifdef __cplusplus
extern "C" {
#endif

#define WINBASEAPI DECLSPEC_IMPORT
#define WINGDIAPI DECLSPEC_IMPORT
#define WINUSERAPI DECLSPEC_IMPORT

#define IN
#define OUT
#define CONST const
#define CALLBACK __stdcall
#define WINAPI __stdcall

#define NEAR
#define FAR

typedef int (FAR WINAPI *FARPROC)();

typedef struct HWND__* HWND;
typedef struct HICON__* HICON;
typedef struct HBRUSH__* HBRUSH;
typedef struct HMENU__* HMENU;

typedef struct HDC__* HDC;
typedef struct HRGN__* HRGN;
typedef struct HGLRC__* HGLRC;

typedef void * HGDIOBJ;
typedef HWND__* HWND;
typedef HICON__ *HICON;
typedef HICON HCURSOR;
typedef HBRUSH__* HBRUSH;
typedef HMENU__* HMENU;
typedef HRGN__* HRGN;

typedef HDC__* HDC;

// due to garbage collection, TODO, rather have __nogc__ attribute on declarator
#if 0
typedef struct HBITMAP__ * HBITMAP;
#else
typedef ULONG_PTR HBITMAP;
#endif

typedef long HRESULT;
typedef wchar_t* BSTR;

struct IDropTargetHelper;

typedef struct _POINTL      /* ptl  */
{
    LONG  x;
    LONG  y;
} POINTL, *PPOINTL;

struct HELPINFO;

// Shobjidl.h
struct ITaskbarList;
struct ITaskbarList2;
struct ITaskbarList3;

//
// Success codes
//
#define S_OK                                   ((HRESULT)0x00000000L)
#define S_FALSE                                ((HRESULT)0x00000001L)

// Error codes
#define E_INVALIDARG                     _HRESULT_TYPEDEF_(0x80070057L)
#define E_FAIL                           _HRESULT_TYPEDEF_(0x80004005L)
#define E_UNEXPECTED                     _HRESULT_TYPEDEF_(0x8000FFFFL)
#define E_NOINTERFACE                    _HRESULT_TYPEDEF_(0x80004002L)
#define E_POINTER                        _HRESULT_TYPEDEF_(0x80004003L)
#define E_NOTIMPL                        _HRESULT_TYPEDEF_(0x80004001L)

static const HRESULT S_Ok = 0;
static const HRESULT S_False = 1;

static const HRESULT E_InvalidArg = 0x80070057;
static const HRESULT E_Fail = 0x80004005;
static const HRESULT E_Unexpected = 0x8000FFFF;
static const HRESULT E_NoInterface = 0x80004002;
static const HRESULT E_Pointer = 0x80004003;
static const HRESULT E_NotImpl = 0x80004001;

typedef void* PRTL_CRITICAL_SECTION_DEBUG;

typedef struct _RTL_CRITICAL_SECTION {
    PRTL_CRITICAL_SECTION_DEBUG DebugInfo;

    //
    //  The following three fields control entering and exiting the critical
    //  section for the resource
    //

    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;        // from the thread's ClientId->UniqueThread
    HANDLE LockSemaphore;
    ULONG_PTR SpinCount;        // force size on 64-bit systems when packed
} RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;

typedef RTL_CRITICAL_SECTION CRITICAL_SECTION;

WINBASEAPI
VOID
WINAPI
InitializeCriticalSection(CRITICAL_SECTION*);

WINBASEAPI
VOID
WINAPI
EnterCriticalSection(CRITICAL_SECTION*);

WINBASEAPI
VOID
WINAPI
LeaveCriticalSection(CRITICAL_SECTION*);

WINBASEAPI
int
WINAPI
TryEnterCriticalSection(CRITICAL_SECTION*);

WINBASEAPI
VOID
WINAPI
DeleteCriticalSection(CRITICAL_SECTION*);

/*
 * MessageBox() Flags
 */
#define MB_OK                       0x00000000L
#define MB_OKCANCEL                 0x00000001L
#define MB_ABORTRETRYIGNORE         0x00000002L
#define MB_YESNOCANCEL              0x00000003L
#define MB_YESNO                    0x00000004L
#define MB_RETRYCANCEL              0x00000005L

#define MB_ICONHAND                 0x00000010L
#define MB_ICONQUESTION             0x00000020L
#define MB_ICONEXCLAMATION          0x00000030L
#define MB_ICONASTERISK             0x00000040L

//#if(WINVER >= 0x0400)
#define MB_USERICON                 0x00000080L
#define MB_ICONWARNING              MB_ICONEXCLAMATION
#define MB_ICONERROR                MB_ICONHAND
//#endif /* WINVER >= 0x0400 */

WINBASEAPI int WINAPI MessageBoxW(
  HWND hWnd,          // handle of owner window
  LPCWSTR lpText,     // address of text in message box
  LPCWSTR lpCaption,  // address of title of message box
  UINT uType          // style of message box
);

WINBASEAPI int WINAPI MessageBoxA(
  HWND hWnd,          // handle of owner window
  LPCSTR lpText,     // address of text in message box
  LPCSTR lpCaption,  // address of title of message box
  UINT uType          // style of message box
);

//#define MessageBox MessageBoxA

WINBASEAPI int WINAPI MessageBeep(/*IN*/ UINT uType);

WINBASEAPI
LPVOID
WINAPI
HeapAlloc(
    IN HANDLE hHeap,
    IN DWORD dwFlags,
    IN SIZE_T dwBytes
    );

WINBASEAPI
HANDLE
WINAPI
GetProcessHeap( VOID );

WINBASEAPI
BOOL
WINAPI
HeapFree(
    IN HANDLE hHeap,
    IN DWORD dwFlags,
    IN LPVOID lpMem
    );

WINBASEAPI
BOOL
WINAPI
IsBadReadPtr(
    IN CONST VOID *lp,
    IN UINT_PTR ucb
    );

typedef struct HINSTANCE__ * HINSTANCE;
typedef HINSTANCE HMODULE;      /* HMODULEs can be used in place of HINSTANCEs */

typedef DWORD* LPDWORD;

#define APIENTRY    WINAPI

#define DLL_PROCESS_ATTACH   1
#define DLL_THREAD_ATTACH    2
#define DLL_THREAD_DETACH    3
#define DLL_PROCESS_DETACH   0
#define DLL_PROCESS_VERIFIER 4

WINBASEAPI
BOOL WINAPI
EnumProcessModules(
  HANDLE hProcess,      // handle to the process
  HMODULE * lphModule,  // array to receive the module handles
  DWORD cb,             // size of the array
  LPDWORD lpcbNeeded    // receives the number of bytes returned
);

WINBASEAPI
HANDLE
WINAPI
GetCurrentProcess(
    VOID
    );

WINBASEAPI
DWORD
WINAPI
GetModuleFileNameA(
    IN HMODULE hModule,
    OUT LPSTR lpFilename,
    IN DWORD nSize
    );

WINBASEAPI
DWORD
WINAPI
GetModuleFileNameW(
    IN HMODULE hModule,
    OUT LPWSTR lpFilename,
    IN DWORD nSize
    );

WINBASEAPI BOOL WINAPI GetUserNameA(
  LPSTR lpBuffer,  // address of name buffer
  LPDWORD nSize     // address of size of name buffer
);

WINBASEAPI BOOL WINAPI GetUserNameW(
  LPWSTR lpBuffer,  // address of name buffer
  LPDWORD nSize     // address of size of name buffer
);

typedef LRESULT (CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

typedef struct tagRECT
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} RECT, *PRECT, NEAR *NPRECT, FAR *LPRECT;

typedef const RECT* LPCRECT;

typedef struct tagWNDCLASSEXA {
    UINT        cbSize;
    /* Win 3.x */
    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCSTR      lpszMenuName;
    LPCSTR      lpszClassName;
    /* Win 4.0 */
    HICON       hIconSm;
} WNDCLASSEXA, *PWNDCLASSEXA;//, NEAR *NPWNDCLASSEXA, FAR *LPWNDCLASSEXA;

typedef struct tagWNDCLASSEXW {
    UINT        cbSize;
    /* Win 3.x */
    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCWSTR     lpszMenuName;
    LPCWSTR     lpszClassName;
    /* Win 4.0 */
    HICON       hIconSm;
} WNDCLASSEXW, *PWNDCLASSEXW;//, NEAR *NPWNDCLASSEXW, FAR *LPWNDCLASSEXW;

typedef struct tagPAINTSTRUCT {
    HDC         hdc;
    BOOL        fErase;
    RECT        rcPaint;
    BOOL        fRestore;
    BOOL        fIncUpdate;
    BYTE        rgbReserved[32];
} PAINTSTRUCT, *PPAINTSTRUCT, *NPPAINTSTRUCT, *LPPAINTSTRUCT;

typedef struct tagCREATESTRUCT {
   LPVOID    lpCreateParams;
   HANDLE    hInstance;
   HMENU     hMenu;
   HWND      hwndParent;
   int       cy;
   int       cx;
   int       y;
   int       x;
   LONG      style;
   LPCSTR    lpszName;
   LPCSTR    lpszClass;
   DWORD     dwExStyle;
} CREATESTRUCT;

WINUSERAPI LONG WINAPI GetWindowLongA(HWND hWnd, int nIndex);
WINUSERAPI LONG WINAPI GetWindowLongW(HWND hWnd, int nIndex);

WINUSERAPI HWND WINAPI
CreateWindowExA(
    /*IN*/ DWORD dwExStyle,
    /*IN*/ LPCSTR lpClassName,
    /*IN*/ LPCSTR lpWindowName,
    /*IN*/ DWORD dwStyle,
    /*IN*/ int X,
    /*IN*/ int Y,
    /*IN*/ int nWidth,
    /*IN*/ int nHeight,
    /*IN*/ HWND hWndParent,
    /*IN*/ HMENU hMenu,
    /*IN*/ HINSTANCE hInstance,
    /*IN*/ LPVOID lpParam);

WINUSERAPI HWND WINAPI
CreateWindowExW(
    /*IN*/ DWORD dwExStyle,
    /*IN*/ LPCWSTR lpClassName,
    /*IN*/ LPCWSTR lpWindowName,
    /*IN*/ DWORD dwStyle,
    /*IN*/ int X,
    /*IN*/ int Y,
    /*IN*/ int nWidth,
    /*IN*/ int nHeight,
    /*IN*/ HWND hWndParent,
    /*IN*/ HMENU hMenu,
    /*IN*/ HINSTANCE hInstance,
    /*IN*/ LPVOID lpParam);

WINUSERAPI LRESULT WINAPI DefWindowProcA(
  HWND hWnd,      // handle to window
  UINT Msg,       // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
);

WINUSERAPI LRESULT WINAPI DefWindowProcW(
  HWND hWnd,      // handle to window
  UINT Msg,       // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
);

WINUSERAPI
VOID
WINAPI
PostQuitMessage(
    IN int nExitCode);

WINUSERAPI HCURSOR WINAPI LoadCursorA(
  HINSTANCE hInstance,  // handle to application instance
  LPCSTR lpCursorName  // name string or cursor resource identifier
);

WINUSERAPI HCURSOR WINAPI LoadCursorW(
  HINSTANCE hInstance,  // handle to application instance
  LPCWSTR lpCursorName  // name string or cursor resource identifier
);

#define _MAKEINTRESOURCEA(i) (LPSTR)((ULONG_PTR)((uint16)(i)))
#define _MAKEINTRESOURCEW(i) (LPWSTR)((ULONG_PTR)((uint16)(i)))
#ifdef UNICODE
#define _MAKEINTRESOURCE  _MAKEINTRESOURCEW
#else
#define _MAKEINTRESOURCE  _MAKEINTRESOURCEA
#endif // !UNICODE

/*
 * Standard Cursor IDs
 */
#define _IDC_ARROW           _MAKEINTRESOURCE(32512)
#define _IDC_IBEAM           _MAKEINTRESOURCE(32513)
#define _IDC_WAIT            _MAKEINTRESOURCE(32514)
#define _IDC_CROSS           _MAKEINTRESOURCE(32515)
#define _IDC_UPARROW         _MAKEINTRESOURCE(32516)
#define _IDC_SIZE            _MAKEINTRESOURCE(32640)  /* OBSOLETE: use IDC_SIZEALL */
#define _IDC_ICON            _MAKEINTRESOURCE(32641)  /* OBSOLETE: use IDC_ARROW */
#define _IDC_SIZENWSE        _MAKEINTRESOURCE(32642)
#define _IDC_SIZENESW        _MAKEINTRESOURCE(32643)
#define _IDC_SIZEWE          _MAKEINTRESOURCE(32644)
#define _IDC_SIZENS          _MAKEINTRESOURCE(32645)
#define _IDC_SIZEALL         _MAKEINTRESOURCE(32646)
#define _IDC_NO              _MAKEINTRESOURCE(32648) /*not in win3.1 */
#if(WINVER >= 0x0500)
#define _IDC_HAND            _MAKEINTRESOURCE(32649)
#endif /* WINVER >= 0x0500 */
#define _IDC_APPSTARTING     _MAKEINTRESOURCE(32650) /*not in win3.1 */
#if(WINVER >= 0x0400)
#define _IDC_HELP            _MAKEINTRESOURCE(32651)
#endif /* WINVER >= 0x0400 */

#define _IDC_ARROW_W           _MAKEINTRESOURCEW(32512)

// WINBASE

typedef struct _OVERLAPPED {
    ULONG_PTR Internal;
    ULONG_PTR InternalHigh;
	 /*
    union {
        struct {
		  */
            DWORD Offset;
            DWORD OffsetHigh;
				/*
        };

        PVOID Pointer;
    };
	 */

    HANDLE  hEvent;
} OVERLAPPED, *LPOVERLAPPED;

//  File System time stamps are represented with the following structure:
//

#ifndef _FILETIME_
#define _FILETIME_
typedef struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;
#endif

//
// System time is represented with the following structure:
//

typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

typedef DWORD (WINAPI *PTHREAD_START_ROUTINE)(
    LPVOID lpThreadParameter
    );
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

WINBASEAPI
HMODULE
WINAPI
LoadLibraryA(
    IN LPCSTR lpLibFileName
    );
WINBASEAPI
HMODULE
WINAPI
LoadLibraryW(
    IN LPCWSTR lpLibFileName
    );

WINBASEAPI
HANDLE
WINAPI
GetCurrentThread(
    VOID
    );

WINBASEAPI
DWORD
WINAPI
GetCurrentThreadId(
    VOID
    );

WINBASEAPI
HANDLE WINAPI CreateFileA(
  LPCSTR lpFileName,          // pointer to name of the file
  DWORD dwDesiredAccess,       // access (read-write) mode
  DWORD dwShareMode,           // share mode
  void * /*LPSECURITY_ATTRIBUTES*/ lpSecurityAttributes,
                               // pointer to security attributes
  DWORD dwCreationDisposition,  // how to create
  DWORD dwFlagsAndAttributes,  // file attributes
  HANDLE hTemplateFile         // handle to file with attributes to 
                               // copy
);

WINBASEAPI
HANDLE WINAPI CreateFileW(
  LPCWSTR lpFileName,          // pointer to name of the file
  DWORD dwDesiredAccess,       // access (read-write) mode
  DWORD dwShareMode,           // share mode
  void * /*LPSECURITY_ATTRIBUTES*/ lpSecurityAttributes,
                               // pointer to security attributes
  DWORD dwCreationDisposition,  // how to create
  DWORD dwFlagsAndAttributes,  // file attributes
  HANDLE hTemplateFile         // handle to file with attributes to 
                               // copy
);

WINBASEAPI
BOOL
WINAPI
WriteFile(
    IN HANDLE hFile,
    IN LPCVOID lpBuffer,
    IN DWORD nNumberOfBytesToWrite,
    OUT LPDWORD lpNumberOfBytesWritten,
    IN LPOVERLAPPED lpOverlapped
    );

WINBASEAPI
BOOL
WINAPI
ReadFile(
    IN HANDLE hFile,
    OUT LPVOID lpBuffer,
    IN DWORD nNumberOfBytesToRead,
    OUT LPDWORD lpNumberOfBytesRead,
    IN LPOVERLAPPED lpOverlapped
    );

WINBASEAPI
DWORD
WINAPI
SetFilePointer(
    IN HANDLE hFile,
    IN LONG lDistanceToMove,
    IN PLONG lpDistanceToMoveHigh,
    IN DWORD dwMoveMethod
    );

WINBASEAPI
DWORD
WINAPI
GetFileSize(
    IN HANDLE hFile,
    OUT LPDWORD lpFileSizeHigh
    );

WINBASEAPI
DWORD
WINAPI
GetFileAttributesA(IN LPCSTR lpFileName);

WINBASEAPI
DWORD
WINAPI
GetFileAttributesW(IN LPCWSTR lpFileName);

/*
WINBASEAPI
BOOL
WINAPI
SetFilePointerEx(
    HANDLE hFile,
    LARGE_INTEGER liDistanceToMove,
    PLARGE_INTEGER lpNewFilePointer,
    DWORD dwMoveMethod
    );
*/

WINBASEAPI
BOOL
WINAPI
FlushFileBuffers(
    IN HANDLE hFile
    );

WINBASEAPI
BOOL
WINAPI
CloseHandle(
    IN OUT HANDLE hObject
    );

WINBASEAPI
DWORD
WINAPI
GetLastError(
    VOID
    );

WINBASEAPI
VOID
WINAPI
SetLastError(
    IN DWORD dwErrCode
    );

WINBASEAPI
BOOL
WINAPI
SetEvent(
    IN HANDLE hEvent
    );

WINBASEAPI
HANDLE
WINAPI
CreateEventA(
    IN void* /*LPSECURITY_ATTRIBUTES*/ lpEventAttributes,
    IN BOOL bManualReset,
    IN BOOL bInitialState,
    IN LPCSTR lpName
    );
WINBASEAPI
HANDLE
WINAPI
CreateEventW(
    IN void* /*LPSECURITY_ATTRIBUTES*/ lpEventAttributes,
    IN BOOL bManualReset,
    IN BOOL bInitialState,
    IN LPCWSTR lpName
    );

WINBASEAPI
HANDLE
WINAPI
CreateThread(
    IN void* /*LPSECURITY_ATTRIBUTES*/ lpThreadAttributes,
    IN SIZE_T dwStackSize,
    IN LPTHREAD_START_ROUTINE lpStartAddress,
    IN LPVOID lpParameter,
    IN DWORD dwCreationFlags,
    OUT LPDWORD lpThreadId
    );

WINBASEAPI
DWORD
WINAPI
WaitForSingleObject(
    IN HANDLE hHandle,
    IN DWORD dwMilliseconds
    );

WINBASEAPI
DWORD
WINAPI
WaitForMultipleObjects(
	DWORD nCount,             // number of handles in the handle array
  CONST HANDLE *lpHandles,  // pointer to the object-handle array
  BOOL fWaitAll,            // wait flag
  DWORD dwMilliseconds      // time-out interval in milliseconds
   );

WINUSERAPI
SHORT
WINAPI
GetAsyncKeyState(
    IN int vKey);

/*
 * Virtual Keys, Standard Set
 */
#define VK_LBUTTON        0x01
#define VK_RBUTTON        0x02
#define VK_CANCEL         0x03
#define VK_MBUTTON        0x04    /* NOT contiguous with L & RBUTTON */

#if(_WIN32_WINNT >= 0x0500)
#define VK_XBUTTON1       0x05    /* NOT contiguous with L & RBUTTON */
#define VK_XBUTTON2       0x06    /* NOT contiguous with L & RBUTTON */
#endif /* _WIN32_WINNT >= 0x0500 */

/*
 * 0x07 : unassigned
 */

#define VK_BACK           0x08
#define VK_TAB            0x09

/*
 * 0x0A - 0x0B : reserved
 */

#define VK_CLEAR          0x0C
#define VK_RETURN         0x0D

#define VK_SHIFT          0x10
#define VK_CONTROL        0x11
#define VK_MENU           0x12
#define VK_PAUSE          0x13
#define VK_CAPITAL        0x14

#define VK_KANA           0x15
//#define VK_HANGEUL        0x15  /* old name - should be here for compatibility */
#define VK_HANGUL         0x15
#define VK_JUNJA          0x17
#define VK_FINAL          0x18
#define VK_HANJA          0x19
#define VK_KANJI          0x19

#define VK_ESCAPE         0x1B

#define VK_CONVERT        0x1C
#define VK_NONCONVERT     0x1D
#define VK_ACCEPT         0x1E
#define VK_MODECHANGE     0x1F

#define VK_SPACE          0x20
#define VK_PRIOR          0x21
#define VK_NEXT           0x22
#define VK_END            0x23
#define VK_HOME           0x24
#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28
#define VK_SELECT         0x29
#define VK_PRINT          0x2A
#define VK_EXECUTE        0x2B
#define VK_SNAPSHOT       0x2C
#define VK_INSERT         0x2D
#define VK_DELETE         0x2E
#define VK_HELP           0x2F

/*
 * Key State Masks for Mouse Messages
 */
#define MK_LBUTTON          0x0001
#define MK_RBUTTON          0x0002
#define MK_SHIFT            0x0004
#define MK_CONTROL          0x0008
#define MK_MBUTTON          0x0010

typedef struct tagPOINT
{
    LONG  x;
    LONG  y;
} POINT, *PPOINT, NEAR *NPPOINT, FAR *LPPOINT;

typedef struct tagSIZE
{
    LONG        cx;
    LONG        cy;
} SIZE, *PSIZE, *LPSIZE;

// WINUSER

/*
 * Message structure
 */
typedef struct tagMSG {
    HWND        hwnd;
    UINT        message;
    WPARAM      wParam;
    LPARAM      lParam;
    DWORD       time;
    POINT       pt;
#ifdef _MAC
    DWORD       lPrivate;
#endif
} MSG, *PMSG;//, NEAR *NPMSG, FAR *LPMSG;

/*
#define MAKEWORD(a, b)      ((uint16)(((uint8)((ULONG_PTR)(a) & 0xff)) | ((uint16)((uint8)((ULONG_PTR)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((uint16)((ULONG_PTR)(a) & 0xffff)) | ((ULONG_PTR)((uint16)((ULONG_PTR)(b) & 0xffff))) << 16))
#define LOWORD(l)           ((uint16)((ULONG_PTR)(l) & 0xffff))
#define HIWORD(l)           ((uint16)((ULONG_PTR)(l) >> 16))
#define LOBYTE(w)           ((uint8)((ULONG_PTR)(w) & 0xff))
#define HIBYTE(w)           ((uint8)((ULONG_PTR)(w) >> 8))

#define MAKEWPARAM(l, h)      ((System::MSWindows::WPARAM)MAKELONG(l, h))
#define MAKELPARAM(l, h)      ((System::MSWindows::LPARAM)MAKELONG(l, h))
#define MAKELRESULT(l, h)     ((System::MSWindows::LRESULT)MAKELONG(l, h))
*/

inline WORD LoWORD(DWORD l)
{
	return l & 0xffff;
}

inline WORD HiWORD(DWORD h)
{
	return h >> 16;
}

inline WORD MakeWORD(BYTE a, BYTE b)
{
	return a | (b<<8);
}

inline LONG MakeLONG(WORD a, WORD b)
{
	return a | (b<<16);
}

inline WPARAM MakeWPARAM(WORD l, WORD h)
{
	return l | (h<<16);
}

inline LPARAM MakeLPARAM(WORD l, WORD h)
{
	return l | (h<<16);
}

inline LRESULT MakeLRESULT(WORD l, WORD h)
{
	return l | (h<<16);
}

/*
 * Window Messages
 */

#define WM_NULL                         0x0000
#define WM_CREATE                       0x0001
#define WM_DESTROY                      0x0002
#define WM_MOVE                         0x0003

#define WM_SIZE                         0x0005
/*
 * WM_SIZE message wParam values
 */
#define SIZE_RESTORED       0
#define SIZE_MINIMIZED      1
#define SIZE_MAXIMIZED      2
#define SIZE_MAXSHOW        3
#define SIZE_MAXHIDE        4

#define WM_PAINT                        0x000F

#define WM_ACTIVATE                     0x0006
/*
 * WM_ACTIVATE state values
 */
#define     WA_INACTIVE     0
#define     WA_ACTIVE       1
#define     WA_CLICKACTIVE  2

#define WM_SETFOCUS                     0x0007
#define WM_KILLFOCUS                    0x0008
#define WM_CLOSE                        0x0010
#define WM_QUIT                         0x0012
#define WM_SETCURSOR                    0x0020
#define WM_GETMINMAXINFO                0x0024
/*
 * Struct pointed to by WM_GETMINMAXINFO lParam
 */
typedef struct tagMINMAXINFO {
    POINT ptReserved;
    POINT ptMaxSize;
    POINT ptMaxPosition;
    POINT ptMinTrackSize;
    POINT ptMaxTrackSize;
} MINMAXINFO, *PMINMAXINFO, *LPMINMAXINFO;

#define WM_CONTEXTMENU                  0x007B

#define WM_NCCREATE                     0x0081
#define WM_NCDESTROY                    0x0082
#define WM_NCCALCSIZE                   0x0083
#define WM_NCPAINT                      0x0085
#define WM_NCACTIVATE                   0x0086
#define WM_NCLBUTTONDOWN                0x00A1

#define WM_KEYDOWN                      0x0100
#define WM_KEYUP                        0x0101
#define WM_CHAR                         0x0102
#define WM_SYSKEYDOWN                   0x0104
#define WM_SYSKEYUP                     0x0105
#define WM_SYSCHAR                      0x0106

#define WM_TIMER                        0x0113

#define WM_MOUSEMOVE                    0x0200
#define WM_LBUTTONDOWN                  0x0201
#define WM_LBUTTONUP                    0x0202
#define WM_LBUTTONDBLCLK                0x0203
#define WM_RBUTTONDOWN                  0x0204
#define WM_RBUTTONUP                    0x0205
#define WM_RBUTTONDBLCLK                0x0206
#define WM_MBUTTONDOWN                  0x0207
#define WM_MBUTTONUP                    0x0208
#define WM_MBUTTONDBLCLK                0x0209
//#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
#define WM_MOUSEWHEEL                   0x020A
//#endif

#define WM_SIZING                       0x0214
#define WM_CAPTURECHANGED               0x0215

#define WM_MOUSELEAVE                   0x02A3

//#if(_WIN32_WINNT >= 0x0501)
#define WM_THEMECHANGED                 0x031A
//#endif /* _WIN32_WINNT >= 0x0501 */

//#if(_WIN32_WINNT >= 0x0501)
#define WM_CLIPBOARDUPDATE              0x031D
//#endif /* _WIN32_WINNT >= 0x0501 */

//#if(_WIN32_WINNT >= 0x0600)
#define WM_DWMCOMPOSITIONCHANGED        0x031E
#define WM_DWMNCRENDERINGCHANGED        0x031F
#define WM_DWMCOLORIZATIONCOLORCHANGED  0x0320
#define WM_DWMWINDOWMAXIMIZEDCHANGE     0x0321
//#endif /* _WIN32_WINNT >= 0x0600 */

//#if(WINVER >= 0x0600)
#define WM_GETTITLEBARINFOEX            0x033F
//#endif /* WINVER >= 0x0600 */

#define WM_APP                          0x8000

/*
 * NOTE: All Message Numbers below 0x0400 are RESERVED.
 *
 * Private Window Messages Start Here:
 */
#define WM_USER                         0x0400

//typedef struct HWND__ * HWND;
//typedef struct HMENU__ * HMENU;

/*
 * WM_WINDOWPOSCHANGING/CHANGED struct pointed to by lParam
 */
typedef struct tagWINDOWPOS {
    HWND    hwnd;
    HWND    hwndInsertAfter;
    int     x;
    int     y;
    int     cx;
    int     cy;
    UINT    flags;
} WINDOWPOS, *LPWINDOWPOS, *PWINDOWPOS;

/*
 * WM_NCCALCSIZE parameter structure
 */
typedef struct tagNCCALCSIZE_PARAMS {
    RECT       rgrc[3];
    PWINDOWPOS lppos;
} NCCALCSIZE_PARAMS, *LPNCCALCSIZE_PARAMS;

/*
 * WM_NCCALCSIZE "window valid rect" return values
 */
#define WVR_ALIGNTOP        0x0010
#define WVR_ALIGNLEFT       0x0020
#define WVR_ALIGNBOTTOM     0x0040
#define WVR_ALIGNRIGHT      0x0080
#define WVR_HREDRAW         0x0100
#define WVR_VREDRAW         0x0200
#define WVR_REDRAW         (WVR_HREDRAW | \
                            WVR_VREDRAW)
#define WVR_VALIDRECTS      0x0400

/*
 * Class styles
 */
#define CS_VREDRAW          0x0001
#define CS_HREDRAW          0x0002
#define CS_DBLCLKS          0x0008
#define CS_OWNDC            0x0020
#define CS_CLASSDC          0x0040
#define CS_PARENTDC         0x0080
#define CS_NOCLOSE          0x0200
#define CS_SAVEBITS         0x0800
//#define CS_BYTEALIGNCLIENT  0x1000
//#define CS_BYTEALIGNWINDOW  0x2000
#define CS_GLOBALCLASS      0x4000

/* Window Styles */
#define WS_OVERLAPPED       0x00000000L
#define WS_CLIPSIBLINGS     0x04000000L
#define WS_CLIPCHILDREN     0x02000000L
#define WS_POPUP            0x80000000L
#define WS_CHILD            0x40000000L
#define WS_MINIMIZE         0x20000000L
#define WS_VISIBLE          0x10000000L
#define WS_DISABLED         0x08000000L
#define WS_CAPTION          0x00C00000L     /* WS_BORDER | WS_DLGFRAME  */
#define WS_SYSMENU          0x00080000L
#define WS_THICKFRAME       0x00040000L

#define WS_MINIMIZEBOX      0x00020000L
#define WS_MAXIMIZEBOX      0x00010000L

/*
 * Extended Window Styles
 */

#define WS_EX_LAYERED           0x00080000

/*
 * Window field offsets for GetWindowLong()
 */
#define GWL_WNDPROC         (-4)
#define GWL_HINSTANCE       (-6)
#define GWL_HWNDPARENT      (-8)
#define GWL_STYLE           (-16)
#define GWL_EXSTYLE         (-20)
#define GWL_USERDATA        (-21)
#define GWL_ID              (-12)

/*
 * WM_NCHITTEST and MOUSEHOOKSTRUCT Mouse Position Codes
 */
#define HTERROR             (-2)
#define HTTRANSPARENT       (-1)
#define HTNOWHERE           0
#define HTCLIENT            1
#define HTCAPTION           2
#define HTSYSMENU           3
#define HTGROWBOX           4
#define HTSIZE              HTGROWBOX
#define HTMENU              5
#define HTHSCROLL           6
#define HTVSCROLL           7
#define HTMINBUTTON         8
#define HTMAXBUTTON         9
#define HTLEFT              10
#define HTRIGHT             11
#define HTTOP               12
#define HTTOPLEFT           13
#define HTTOPRIGHT          14
#define HTBOTTOM            15
#define HTBOTTOMLEFT        16
#define HTBOTTOMRIGHT       17
#define HTBORDER            18
#define HTREDUCE            HTMINBUTTON
#define HTZOOM              HTMAXBUTTON
#define HTSIZEFIRST         HTLEFT
#define HTSIZELAST          HTBOTTOMRIGHT
//#if(WINVER >= 0x0400)
#define HTOBJECT            19
#define HTCLOSE             20
#define HTHELP              21
//#endif /* WINVER >= 0x0400 */

#ifdef _WIN64

#undef GWL_WNDPROC
#undef GWL_HINSTANCE
#undef GWL_HWNDPARENT
#undef GWL_USERDATA

#endif /* _WIN64 */

typedef unsigned int UINT_PTR;
typedef long LONG_PTR;

typedef int BOOL;

/* Types use for passing & returning polymorphic values */
typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;

typedef struct HRGN__ * HRGN;

typedef HANDLE              HGLOBAL;

typedef struct _BLENDFUNCTION
{
    BYTE   BlendOp;
    BYTE   BlendFlags;
    BYTE   SourceConstantAlpha;
    BYTE   AlphaFormat;
}BLENDFUNCTION,*PBLENDFUNCTION;

//
// currentlly defined blend function
//

#define AC_SRC_OVER                 0x00

//
// alpha format flags
//

#define AC_SRC_ALPHA                0x01

//

WINUSERAPI
HWND
WINAPI
GetCapture(
    VOID);

WINUSERAPI
HWND
WINAPI
SetCapture(
    IN HWND hWnd);

WINUSERAPI
BOOL
WINAPI
ReleaseCapture(
    VOID);

WINUSERAPI
int
WINAPI
GetSystemMetrics(
    IN int nIndex);

/*
 * GetSystemMetrics() codes
 */

#define SM_CXSCREEN             0
#define SM_CYSCREEN             1
#define SM_CXFRAME              32
#define SM_CYFRAME              33

WINUSERAPI
BOOL
WINAPI
SystemParametersInfoA(
    IN UINT uiAction,
    IN UINT uiParam,
    IN OUT PVOID pvParam,
    IN UINT fWinIni);

WINUSERAPI
BOOL
WINAPI
SystemParametersInfoW(
    IN UINT uiAction,
    IN UINT uiParam,
    IN OUT PVOID pvParam,
    IN UINT fWinIni);

/*
 * Parameter for SystemParametersInfo.
 */

#define SPI_GETBEEP                 0x0001
#define SPI_SETBEEP                 0x0002
#define SPI_GETMOUSE                0x0003
#define SPI_SETMOUSE                0x0004
#define SPI_GETBORDER               0x0005
#define SPI_SETBORDER               0x0006
#define SPI_GETKEYBOARDSPEED        0x000A
#define SPI_SETKEYBOARDSPEED        0x000B
#define SPI_LANGDRIVER              0x000C
#define SPI_ICONHORIZONTALSPACING   0x000D
#define SPI_GETSCREENSAVETIMEOUT    0x000E
#define SPI_SETSCREENSAVETIMEOUT    0x000F
#define SPI_GETSCREENSAVEACTIVE     0x0010
#define SPI_SETSCREENSAVEACTIVE     0x0011
#define SPI_GETGRIDGRANULARITY      0x0012
#define SPI_SETGRIDGRANULARITY      0x0013
#define SPI_SETDESKWALLPAPER        0x0014
#define SPI_SETDESKPATTERN          0x0015
#define SPI_GETKEYBOARDDELAY        0x0016
#define SPI_SETKEYBOARDDELAY        0x0017
#define SPI_ICONVERTICALSPACING     0x0018
#define SPI_GETICONTITLEWRAP        0x0019
#define SPI_SETICONTITLEWRAP        0x001A
#define SPI_GETMENUDROPALIGNMENT    0x001B
#define SPI_SETMENUDROPALIGNMENT    0x001C
#define SPI_SETDOUBLECLKWIDTH       0x001D
#define SPI_SETDOUBLECLKHEIGHT      0x001E
#define SPI_GETICONTITLELOGFONT     0x001F
#define SPI_SETDOUBLECLICKTIME      0x0020
#define SPI_SETMOUSEBUTTONSWAP      0x0021
#define SPI_SETICONTITLELOGFONT     0x0022
#define SPI_GETFASTTASKSWITCH       0x0023
#define SPI_SETFASTTASKSWITCH       0x0024
#if(WINVER >= 0x0400)
#define SPI_SETDRAGFULLWINDOWS      0x0025
#define SPI_GETDRAGFULLWINDOWS      0x0026
#define SPI_GETNONCLIENTMETRICS     0x0029
#define SPI_SETNONCLIENTMETRICS     0x002A
#define SPI_GETMINIMIZEDMETRICS     0x002B
#define SPI_SETMINIMIZEDMETRICS     0x002C
#define SPI_GETICONMETRICS          0x002D
#define SPI_SETICONMETRICS          0x002E
#define SPI_SETWORKAREA             0x002F
#define SPI_GETWORKAREA             0x0030
#define SPI_SETPENWINDOWS           0x0031

#define SPI_GETHIGHCONTRAST         0x0042
#define SPI_SETHIGHCONTRAST         0x0043
#define SPI_GETKEYBOARDPREF         0x0044
#define SPI_SETKEYBOARDPREF         0x0045
#define SPI_GETSCREENREADER         0x0046
#define SPI_SETSCREENREADER         0x0047
#define SPI_GETANIMATION            0x0048
#define SPI_SETANIMATION            0x0049
#define SPI_GETFONTSMOOTHING        0x004A
#define SPI_SETFONTSMOOTHING        0x004B
#define SPI_SETDRAGWIDTH            0x004C
#define SPI_SETDRAGHEIGHT           0x004D
#define SPI_SETHANDHELD             0x004E
#define SPI_GETLOWPOWERTIMEOUT      0x004F
#define SPI_GETPOWEROFFTIMEOUT      0x0050
#define SPI_SETLOWPOWERTIMEOUT      0x0051
#define SPI_SETPOWEROFFTIMEOUT      0x0052
#define SPI_GETLOWPOWERACTIVE       0x0053
#define SPI_GETPOWEROFFACTIVE       0x0054
#define SPI_SETLOWPOWERACTIVE       0x0055
#define SPI_SETPOWEROFFACTIVE       0x0056
#define SPI_SETCURSORS              0x0057
#define SPI_SETICONS                0x0058
#define SPI_GETDEFAULTINPUTLANG     0x0059
#define SPI_SETDEFAULTINPUTLANG     0x005A
#define SPI_SETLANGTOGGLE           0x005B
#define SPI_GETWINDOWSEXTENSION     0x005C
#define SPI_SETMOUSETRAILS          0x005D
#define SPI_GETMOUSETRAILS          0x005E
#define SPI_SETSCREENSAVERRUNNING   0x0061
#define SPI_SCREENSAVERRUNNING     SPI_SETSCREENSAVERRUNNING
#endif /* WINVER >= 0x0400 */
#define SPI_GETFILTERKEYS          0x0032
#define SPI_SETFILTERKEYS          0x0033
#define SPI_GETTOGGLEKEYS          0x0034
#define SPI_SETTOGGLEKEYS          0x0035
#define SPI_GETMOUSEKEYS           0x0036
#define SPI_SETMOUSEKEYS           0x0037
#define SPI_GETSHOWSOUNDS          0x0038
#define SPI_SETSHOWSOUNDS          0x0039
#define SPI_GETSTICKYKEYS          0x003A
#define SPI_SETSTICKYKEYS          0x003B
#define SPI_GETACCESSTIMEOUT       0x003C
#define SPI_SETACCESSTIMEOUT       0x003D
#if(WINVER >= 0x0400)
#define SPI_GETSERIALKEYS          0x003E
#define SPI_SETSERIALKEYS          0x003F
#endif /* WINVER >= 0x0400 */
#define SPI_GETSOUNDSENTRY         0x0040
#define SPI_SETSOUNDSENTRY         0x0041
#if(_WIN32_WINNT >= 0x0400)
#define SPI_GETSNAPTODEFBUTTON     0x005F
#define SPI_SETSNAPTODEFBUTTON     0x0060
#endif /* _WIN32_WINNT >= 0x0400 */
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
#define SPI_GETMOUSEHOVERWIDTH     0x0062
#define SPI_SETMOUSEHOVERWIDTH     0x0063
#define SPI_GETMOUSEHOVERHEIGHT    0x0064
#define SPI_SETMOUSEHOVERHEIGHT    0x0065
#define SPI_GETMOUSEHOVERTIME      0x0066
#define SPI_SETMOUSEHOVERTIME      0x0067
#define SPI_GETWHEELSCROLLLINES    0x0068
#define SPI_SETWHEELSCROLLLINES    0x0069
#define SPI_GETMENUSHOWDELAY       0x006A
#define SPI_SETMENUSHOWDELAY       0x006B

#if (_WIN32_WINNT >= 0x0600)
#define SPI_GETWHEELSCROLLCHARS   0x006C
#define SPI_SETWHEELSCROLLCHARS   0x006D
#endif

#define SPI_GETSHOWIMEUI          0x006E
#define SPI_SETSHOWIMEUI          0x006F
#endif


#if(WINVER >= 0x0500)
#define SPI_GETMOUSESPEED         0x0070
#define SPI_SETMOUSESPEED         0x0071
#define SPI_GETSCREENSAVERRUNNING 0x0072
#define SPI_GETDESKWALLPAPER      0x0073
#endif /* WINVER >= 0x0500 */

#if(WINVER >= 0x0600)
#define SPI_GETAUDIODESCRIPTION   0x0074
#define SPI_SETAUDIODESCRIPTION   0x0075

#define SPI_GETSCREENSAVESECURE   0x0076
#define SPI_SETSCREENSAVESECURE   0x0077
#endif /* WINVER >= 0x0600 */

#if(_WIN32_WINNT >= 0x0601)
#define SPI_GETHUNGAPPTIMEOUT           0x0078
#define SPI_SETHUNGAPPTIMEOUT           0x0079
#define SPI_GETWAITTOKILLTIMEOUT        0x007A
#define SPI_SETWAITTOKILLTIMEOUT        0x007B
#define SPI_GETWAITTOKILLSERVICETIMEOUT 0x007C
#define SPI_SETWAITTOKILLSERVICETIMEOUT 0x007D
#define SPI_GETMOUSEDOCKTHRESHOLD       0x007E
#define SPI_SETMOUSEDOCKTHRESHOLD       0x007F
#define SPI_GETPENDOCKTHRESHOLD         0x0080
#define SPI_SETPENDOCKTHRESHOLD         0x0081
#define SPI_GETWINARRANGING             0x0082
#define SPI_SETWINARRANGING             0x0083
#define SPI_GETMOUSEDRAGOUTTHRESHOLD    0x0084
#define SPI_SETMOUSEDRAGOUTTHRESHOLD    0x0085
#define SPI_GETPENDRAGOUTTHRESHOLD      0x0086
#define SPI_SETPENDRAGOUTTHRESHOLD      0x0087
#define SPI_GETMOUSESIDEMOVETHRESHOLD   0x0088
#define SPI_SETMOUSESIDEMOVETHRESHOLD   0x0089
#define SPI_GETPENSIDEMOVETHRESHOLD     0x008A
#define SPI_SETPENSIDEMOVETHRESHOLD     0x008B
#define SPI_GETDRAGFROMMAXIMIZE         0x008C
#define SPI_SETDRAGFROMMAXIMIZE         0x008D
#define SPI_GETSNAPSIZING               0x008E
#define SPI_SETSNAPSIZING               0x008F
#define SPI_GETDOCKMOVING               0x0090
#define SPI_SETDOCKMOVING               0x0091
#endif /* _WIN32_WINNT >= 0x0601 */


#if(WINVER >= 0x0500)
#define SPI_GETACTIVEWINDOWTRACKING         0x1000
#define SPI_SETACTIVEWINDOWTRACKING         0x1001
#define SPI_GETMENUANIMATION                0x1002
#define SPI_SETMENUANIMATION                0x1003
#define SPI_GETCOMBOBOXANIMATION            0x1004
#define SPI_SETCOMBOBOXANIMATION            0x1005
#define SPI_GETLISTBOXSMOOTHSCROLLING       0x1006
#define SPI_SETLISTBOXSMOOTHSCROLLING       0x1007
#define SPI_GETGRADIENTCAPTIONS             0x1008
#define SPI_SETGRADIENTCAPTIONS             0x1009
#define SPI_GETKEYBOARDCUES                 0x100A
#define SPI_SETKEYBOARDCUES                 0x100B
#define SPI_GETMENUUNDERLINES               SPI_GETKEYBOARDCUES
#define SPI_SETMENUUNDERLINES               SPI_SETKEYBOARDCUES
#define SPI_GETACTIVEWNDTRKZORDER           0x100C
#define SPI_SETACTIVEWNDTRKZORDER           0x100D
#define SPI_GETHOTTRACKING                  0x100E
#define SPI_SETHOTTRACKING                  0x100F
#define SPI_GETMENUFADE                     0x1012
#define SPI_SETMENUFADE                     0x1013
#define SPI_GETSELECTIONFADE                0x1014
#define SPI_SETSELECTIONFADE                0x1015
#define SPI_GETTOOLTIPANIMATION             0x1016
#define SPI_SETTOOLTIPANIMATION             0x1017
#define SPI_GETTOOLTIPFADE                  0x1018
#define SPI_SETTOOLTIPFADE                  0x1019
#define SPI_GETCURSORSHADOW                 0x101A
#define SPI_SETCURSORSHADOW                 0x101B
#if(_WIN32_WINNT >= 0x0501)
#define SPI_GETMOUSESONAR                   0x101C
#define SPI_SETMOUSESONAR                   0x101D
#define SPI_GETMOUSECLICKLOCK               0x101E
#define SPI_SETMOUSECLICKLOCK               0x101F
#define SPI_GETMOUSEVANISH                  0x1020
#define SPI_SETMOUSEVANISH                  0x1021
#define SPI_GETFLATMENU                     0x1022
#define SPI_SETFLATMENU                     0x1023
#define SPI_GETDROPSHADOW                   0x1024
#define SPI_SETDROPSHADOW                   0x1025
#define SPI_GETBLOCKSENDINPUTRESETS         0x1026
#define SPI_SETBLOCKSENDINPUTRESETS         0x1027
#endif /* _WIN32_WINNT >= 0x0501 */

#define SPI_GETUIEFFECTS                    0x103E
#define SPI_SETUIEFFECTS                    0x103F

#if(_WIN32_WINNT >= 0x0600)
#define SPI_GETDISABLEOVERLAPPEDCONTENT     0x1040
#define SPI_SETDISABLEOVERLAPPEDCONTENT     0x1041
#define SPI_GETCLIENTAREAANIMATION          0x1042
#define SPI_SETCLIENTAREAANIMATION          0x1043
#define SPI_GETCLEARTYPE                    0x1048
#define SPI_SETCLEARTYPE                    0x1049
#define SPI_GETSPEECHRECOGNITION            0x104A
#define SPI_SETSPEECHRECOGNITION            0x104B
#endif /* _WIN32_WINNT >= 0x0600 */

#define SPI_GETFOREGROUNDLOCKTIMEOUT        0x2000
#define SPI_SETFOREGROUNDLOCKTIMEOUT        0x2001
#define SPI_GETACTIVEWNDTRKTIMEOUT          0x2002
#define SPI_SETACTIVEWNDTRKTIMEOUT          0x2003
#define SPI_GETFOREGROUNDFLASHCOUNT         0x2004
#define SPI_SETFOREGROUNDFLASHCOUNT         0x2005
#define SPI_GETCARETWIDTH                   0x2006
#define SPI_SETCARETWIDTH                   0x2007

#if(_WIN32_WINNT >= 0x0501)
#define SPI_GETMOUSECLICKLOCKTIME           0x2008
#define SPI_SETMOUSECLICKLOCKTIME           0x2009
#define SPI_GETFONTSMOOTHINGTYPE            0x200A
#define SPI_SETFONTSMOOTHINGTYPE            0x200B

/* constants for SPI_GETFONTSMOOTHINGTYPE and SPI_SETFONTSMOOTHINGTYPE: */
#define FE_FONTSMOOTHINGSTANDARD            0x0001
#define FE_FONTSMOOTHINGCLEARTYPE           0x0002

#define SPI_GETFONTSMOOTHINGCONTRAST           0x200C
#define SPI_SETFONTSMOOTHINGCONTRAST           0x200D

#define SPI_GETFOCUSBORDERWIDTH             0x200E
#define SPI_SETFOCUSBORDERWIDTH             0x200F
#define SPI_GETFOCUSBORDERHEIGHT            0x2010
#define SPI_SETFOCUSBORDERHEIGHT            0x2011

#define SPI_GETFONTSMOOTHINGORIENTATION           0x2012
#define SPI_SETFONTSMOOTHINGORIENTATION           0x2013

/* constants for SPI_GETFONTSMOOTHINGORIENTATION and SPI_SETFONTSMOOTHINGORIENTATION: */
#define FE_FONTSMOOTHINGORIENTATIONBGR   0x0000
#define FE_FONTSMOOTHINGORIENTATIONRGB   0x0001
#endif /* _WIN32_WINNT >= 0x0501 */

#if(_WIN32_WINNT >= 0x0600)
#define SPI_GETMINIMUMHITRADIUS             0x2014
#define SPI_SETMINIMUMHITRADIUS             0x2015
#define SPI_GETMESSAGEDURATION              0x2016
#define SPI_SETMESSAGEDURATION              0x2017
#endif /* _WIN32_WINNT >= 0x0600 */

#endif /* WINVER >= 0x0500 */

WINUSERAPI
BOOL
WINAPI
IsWindow(
    IN HWND hWnd);

WINUSERAPI
BOOL
WINAPI
GetClientRect(
    IN HWND hWnd,
    OUT LPRECT lpRect);

WINUSERAPI
BOOL
WINAPI
GetWindowRect(
    IN HWND hWnd,
    OUT LPRECT lpRect);

WINUSERAPI
BOOL
WINAPI
GetMessageA(
    OUT PMSG lpMsg,
    IN HWND hWnd,
    IN UINT wMsgFilterMin,
    IN UINT wMsgFilterMax);

WINUSERAPI
BOOL
WINAPI
GetMessageW(
    OUT PMSG lpMsg,
    IN HWND hWnd,
    IN UINT wMsgFilterMin,
    IN UINT wMsgFilterMax);

WINUSERAPI
BOOL
WINAPI
TranslateMessage(
    IN CONST MSG *lpMsg);

WINUSERAPI
LRESULT
WINAPI
DispatchMessageA(
    IN CONST MSG *lpMsg);

WINUSERAPI
LRESULT
WINAPI
DispatchMessageW(
    IN CONST MSG *lpMsg);

WINUSERAPI
BOOL
WINAPI
PeekMessageA(
    OUT MSG* lpMsg,
    IN HWND hWnd,
    IN UINT wMsgFilterMin,
    IN UINT wMsgFilterMax,
    IN UINT wRemoveMsg);

WINUSERAPI
BOOL
WINAPI
PeekMessageW(
    OUT MSG* lpMsg,
    IN HWND hWnd,
    IN UINT wMsgFilterMin,
    IN UINT wMsgFilterMax,
    IN UINT wRemoveMsg);

/*
 * PeekMessage() Options
 */
#define PM_NOREMOVE         0x0000
#define PM_REMOVE           0x0001
#define PM_NOYIELD          0x0002

WINUSERAPI LONG WINAPI GetMessageTime();

#if(WINVER >= 0x0500)
/*
#define PM_QS_INPUT         (QS_INPUT << 16)
#define PM_QS_POSTMESSAGE   ((QS_POSTMESSAGE | QS_HOTKEY | QS_TIMER) << 16)
#define PM_QS_PAINT         (QS_PAINT << 16)
#define PM_QS_SENDMESSAGE   (QS_SENDMESSAGE << 16)
*/
#endif /* WINVER >= 0x0500 */

WINUSERAPI
/*ATOM*/int WINAPI
RegisterClassExA(
  CONST WNDCLASSEXA *lpwcx  // address of structure with class data
);

WINUSERAPI
/*ATOM*/int WINAPI
RegisterClassExW(
  CONST WNDCLASSEXW *lpwcx  // address of structure with class data
);

WINUSERAPI
LRESULT
WINAPI
SendMessageA(
    IN HWND hWnd,
    IN UINT Msg,
    IN WPARAM wParam,
    IN LPARAM lParam);

WINUSERAPI
LRESULT
WINAPI
SendMessageW(
    IN HWND hWnd,
    IN UINT Msg,
    IN WPARAM wParam,
    IN LPARAM lParam);

WINUSERAPI
BOOL
WINAPI
PostMessageA(
    IN HWND hWnd,
    IN UINT Msg,
    IN WPARAM wParam,
    IN LPARAM lParam);

WINUSERAPI
BOOL
WINAPI
PostMessageW(
    IN HWND hWnd,
    IN UINT Msg,
    IN WPARAM wParam,
    IN LPARAM lParam);

WINUSERAPI
BOOL
WINAPI
PostThreadMessageA(
    IN DWORD idThread,
    IN UINT Msg,
    IN WPARAM wParam,
    IN LPARAM lParam);

WINUSERAPI
BOOL
WINAPI
PostThreadMessageW(
    IN DWORD idThread,
    IN UINT Msg,
    IN WPARAM wParam,
    IN LPARAM lParam);

WINUSERAPI
BOOL
WINAPI
EnableWindow(
    IN HWND hWnd,
    IN BOOL bEnable);

WINUSERAPI
BOOL
WINAPI
IsWindowEnabled(
    IN HWND hWnd);

WINUSERAPI
BOOL
WINAPI
SetWindowTextA(
    IN HWND hWnd,
    IN LPCSTR lpString);

WINUSERAPI
BOOL
WINAPI
SetWindowTextW(
    IN HWND hWnd,
    IN LPCWSTR lpString);

WINUSERAPI
UINT WINAPI
SetTimer(
  HWND hWnd,              // handle of window for timer messages
  UINT nIDEvent,          // timer identifier
  UINT uElapse,           // time-out value
  void* /*TIMERPROC*/ lpTimerFunc   // address of timer procedure
);

WINUSERAPI
BOOL
WINAPI
KillTimer(
    IN HWND hWnd,
    IN UINT_PTR uIDEvent);

WINUSERAPI
BOOL
WINAPI
CloseWindow(
    IN HWND hWnd);

WINUSERAPI
BOOL
WINAPI
BringWindowToTop(
    IN HWND hWnd);

WINUSERAPI
BOOL WINAPI MoveWindow(
  HWND hWnd,      // handle to window
  int X,          // horizontal position
  int Y,          // vertical position
  int nWidth,     // width
  int nHeight,    // height
  BOOL bRepaint   // repaint flag
);

WINUSERAPI
BOOL
WINAPI
SetWindowPos(
    IN HWND hWnd,
    IN HWND hWndInsertAfter,
    IN int X,
    IN int Y,
    IN int cx,
    IN int cy,
    IN UINT uFlags);

/*
 * SetWindowPos Flags
 */
#define SWP_NOSIZE          0x0001
#define SWP_NOMOVE          0x0002
#define SWP_NOZORDER        0x0004
#define SWP_NOREDRAW        0x0008
#define SWP_NOACTIVATE      0x0010
#define SWP_FRAMECHANGED    0x0020  /* The frame changed: send WM_NCCALCSIZE */
#define SWP_SHOWWINDOW      0x0040
#define SWP_HIDEWINDOW      0x0080
#define SWP_NOCOPYBITS      0x0100
#define SWP_NOOWNERZORDER   0x0200  /* Don't do owner Z ordering */
#define SWP_NOSENDCHANGING  0x0400  /* Don't send WM_WINDOWPOSCHANGING */

#define SWP_DRAWFRAME       SWP_FRAMECHANGED
#define SWP_NOREPOSITION    SWP_NOOWNERZORDER

//#if(WINVER >= 0x0400)
#define SWP_DEFERERASE      0x2000
#define SWP_ASYNCWINDOWPOS  0x4000
//#endif /* WINVER >= 0x0400 */

#define HWND_TOP        ((HWND)0)
#define HWND_BOTTOM     ((HWND)1)
#define HWND_TOPMOST    ((HWND)-1)
#define HWND_NOTOPMOST  ((HWND)-2)

WINUSERAPI
BOOL
WINAPI
DestroyWindow(
    IN HWND hWnd);

WINUSERAPI
BOOL
WINAPI
ShowWindow(
    IN HWND hWnd,
    IN int nCmdShow);

/*
 * ShowWindow() Commands
 */
#define SW_HIDE             0
#define SW_SHOWNORMAL       1
#define SW_NORMAL           1
#define SW_SHOWMINIMIZED    2
#define SW_SHOWMAXIMIZED    3
#define SW_MAXIMIZE         3
#define SW_SHOWNOACTIVATE   4
#define SW_SHOW             5
#define SW_MINIMIZE         6
#define SW_SHOWMINNOACTIVE  7
#define SW_SHOWNA           8
#define SW_RESTORE          9
#define SW_SHOWDEFAULT      10
#define SW_FORCEMINIMIZE    11
#define SW_MAX              11

WINUSERAPI
BOOL
WINAPI
UpdateLayeredWindow(
    HWND hWnd,
    HDC hdcDst,
    POINT *pptDst,
    SIZE *psize,
    HDC hdcSrc,
    POINT *pptSrc,
	 /*COLORREF*/DWORD crKey,
    BLENDFUNCTION *pblend,
    DWORD dwFlags);

WINUSERAPI
LONG WINAPI SetWindowLongA(
  HWND hWnd,       // handle of window
  int nIndex,      // offset of value to set
  LONG dwNewLong   // new value
);

WINUSERAPI
LONG WINAPI SetWindowLongW(
  HWND hWnd,       // handle of window
  int nIndex,      // offset of value to set
  LONG dwNewLong   // new value
);

WINUSERAPI
HWND
WINAPI
GetDesktopWindow(
    VOID);

WINUSERAPI
HWND
WINAPI
GetParent(
    IN HWND hWnd);

WINUSERAPI
HWND WINAPI SetParent(
  HWND hWndChild,      // handle to window whose parent is changing
  HWND hWndNewParent   // handle to new parent window
);

WINUSERAPI
BOOL
WINAPI
ClientToScreen(
    IN HWND hWnd,
    IN OUT LPPOINT lpPoint);

WINUSERAPI
BOOL
WINAPI
ScreenToClient(
    IN HWND hWnd,
    IN OUT LPPOINT lpPoint);

WINUSERAPI
BOOL WINAPI SetPropA(
  HWND hWnd,         // handle of window
  LPCSTR lpString,  // atom or address of string
  HANDLE hData       // handle of data
);

WINUSERAPI
BOOL WINAPI SetPropW(
  HWND hWnd,         // handle of window
  LPCWSTR lpString,  // atom or address of string
  HANDLE hData       // handle of data
);

WINUSERAPI
HANDLE WINAPI GetPropA(
  HWND hWnd,         // handle of window
  LPCSTR lpString  // atom or address of string
);

WINUSERAPI
HANDLE WINAPI GetPropW(
  HWND hWnd,         // handle of window
  LPCWSTR lpString  // atom or address of string
);

WINUSERAPI
BOOL
WINAPI
SetLayeredWindowAttributes(
    HWND hwnd,
    DWORD/*COLORREF*/ crKey,
    BYTE bAlpha,
    DWORD dwFlags);

#define LWA_COLORKEY            0x00000001
#define LWA_ALPHA               0x00000002

#define ULW_COLORKEY            0x00000001
#define ULW_ALPHA               0x00000002
#define ULW_OPAQUE              0x00000004

WINUSERAPI
BOOL
WINAPI
LockWindowUpdate(
    IN HWND hWndLock);

WINUSERAPI
BOOL
WINAPI
InflateRect(
    IN OUT LPRECT lprc,
    IN int dx,
    IN int dy);

WINUSERAPI
BOOL
WINAPI
IntersectRect(
    OUT LPRECT lprcDst,
    IN CONST RECT *lprcSrc1,
    IN CONST RECT *lprcSrc2);

WINUSERAPI
HDC
WINAPI
GetDC(
    IN HWND hWnd);

WINUSERAPI
HDC
WINAPI
GetDCEx(
    IN HWND hWnd,
    IN HRGN hrgnClip,
    IN DWORD flags);

/*
 * GetDCEx() flags
 */
#define DCX_WINDOW           0x00000001L
#define DCX_CACHE            0x00000002L
#define DCX_NORESETATTRS     0x00000004L
#define DCX_CLIPCHILDREN     0x00000008L
#define DCX_CLIPSIBLINGS     0x00000010L
#define DCX_PARENTCLIP       0x00000020L
#define DCX_EXCLUDERGN       0x00000040L
#define DCX_INTERSECTRGN     0x00000080L
#define DCX_EXCLUDEUPDATE    0x00000100L
#define DCX_INTERSECTUPDATE  0x00000200L
#define DCX_LOCKWINDOWUPDATE 0x00000400L

#define DCX_VALIDATE         0x00200000L

WINUSERAPI
BOOL
WINAPI
InvalidateRect(
    IN HWND hWnd,
    IN CONST RECT *lpRect,
    IN BOOL bErase);

WINUSERAPI
int
WINAPI
SetWindowRgn(
    IN HWND hWnd,
    IN HRGN hRgn,
    IN BOOL bRedraw);

WINUSERAPI
HDC
WINAPI
GetWindowDC(
    IN HWND hWnd);

WINUSERAPI
int
WINAPI
ReleaseDC(
    IN HWND hWnd,
    IN HDC hDC);

WINUSERAPI
HDC
WINAPI
BeginPaint(
    IN HWND hWnd,
    OUT LPPAINTSTRUCT lpPaint);

WINUSERAPI
BOOL
WINAPI
EndPaint(
    IN HWND hWnd,
    IN CONST PAINTSTRUCT *lpPaint);

WINUSERAPI
HCURSOR
WINAPI
SetCursor(
    IN HCURSOR hCursor);

WINUSERAPI
BOOL
WINAPI
GetCursorPos(
    OUT LPPOINT lpPoint);

#define TME_HOVER       0x00000001
#define TME_LEAVE       0x00000002

typedef struct tagTRACKMOUSEEVENT {
    DWORD cbSize;
    DWORD dwFlags;
    HWND  hwndTrack;
    DWORD dwHoverTime;
} TRACKMOUSEEVENT, *LPTRACKMOUSEEVENT;

WINUSERAPI
BOOL
WINAPI
TrackMouseEvent(
    IN OUT LPTRACKMOUSEEVENT lpEventTrack);

/*
 * Clipboard Manager Functions
 */

WINUSERAPI
BOOL
WINAPI
OpenClipboard(
    IN HWND hWndNewOwner);

WINUSERAPI
BOOL
WINAPI
CloseClipboard(
    VOID);

WINUSERAPI
BOOL
WINAPI
EmptyClipboard(
    VOID);

WINUSERAPI
BOOL
WINAPI
IsClipboardFormatAvailable(
    IN UINT format);

WINUSERAPI
HANDLE
WINAPI
SetClipboardData(
    IN UINT uFormat,
    IN HANDLE hMem);

WINUSERAPI
HANDLE
WINAPI
GetClipboardData(
    IN UINT uFormat);

WINUSERAPI
UINT
WINAPI
RegisterClipboardFormatA(
    IN LPCSTR lpszFormat);

WINUSERAPI
UINT
WINAPI
RegisterClipboardFormatW(
    IN LPCWSTR lpszFormat);

/*
 * Predefined Clipboard Formats
 */
#define CF_TEXT             1
#define CF_BITMAP           2
#define CF_METAFILEPICT     3
#define CF_SYLK             4
#define CF_DIF              5
#define CF_TIFF             6
#define CF_OEMTEXT          7
#define CF_DIB              8
#define CF_PALETTE          9
#define CF_PENDATA          10
#define CF_RIFF             11
#define CF_WAVE             12
#define CF_UNICODETEXT      13
#define CF_ENHMETAFILE      14
//#if(WINVER >= 0x0400)
#define CF_HDROP            15
#define CF_LOCALE           16
//#endif /* WINVER >= 0x0400 */
//#if(WINVER >= 0x0500)
#define CF_DIBV5            17
//#endif /* WINVER >= 0x0500 */

WINBASEAPI
BOOL
WINAPI
FreeLibrary(
    IN OUT HMODULE hLibModule
    );

/*
WINBASEAPI
DECLSPEC_NORETURN
VOID
WINAPI
FreeLibraryAndExitThread(
    IN HMODULE hLibModule,
    IN DWORD dwExitCode
    );
*/

WINBASEAPI
BOOL
WINAPI
DisableThreadLibraryCalls(
    IN HMODULE hLibModule
    );

WINBASEAPI
FARPROC
WINAPI
GetProcAddress(
    IN HMODULE hModule,
    IN LPCSTR lpProcName
    );

WINBASEAPI
DWORD
WINAPI
GetVersion( VOID );

WINBASEAPI
HGLOBAL
WINAPI
GlobalAlloc(
    IN UINT uFlags,
    IN SIZE_T dwBytes
    );

WINBASEAPI
HGLOBAL
WINAPI
GlobalReAlloc(
    IN HGLOBAL hMem,
    IN SIZE_T dwBytes,
    IN UINT uFlags
    );

WINBASEAPI
SIZE_T
WINAPI
GlobalSize(
    IN HGLOBAL hMem
    );

WINBASEAPI
UINT
WINAPI
GlobalFlags(
    IN HGLOBAL hMem
    );


WINBASEAPI
LPVOID
WINAPI
GlobalLock(
    IN HGLOBAL hMem
    );

/*
//!!!MWH My version  win31 = DWORD WINAPI GlobalHandle(UINT)
WINBASEAPI
HGLOBAL
WINAPI
GlobalHandle(
    IN LPCVOID pMem
    );
*/

WINBASEAPI
BOOL
WINAPI
GlobalUnlock(
    IN HGLOBAL hMem
    );


WINBASEAPI
HGLOBAL
WINAPI
GlobalFree(
    IN HGLOBAL hMem
    );

/* Global Memory Flags */
#define GMEM_FIXED          0x0000
#define GMEM_MOVEABLE       0x0002
#define GMEM_NOCOMPACT      0x0010
#define GMEM_NODISCARD      0x0020
#define GMEM_ZEROINIT       0x0040
#define GMEM_MODIFY         0x0080
#define GMEM_DISCARDABLE    0x0100
#define GMEM_NOT_BANKED     0x1000
#define GMEM_SHARE          0x2000
#define GMEM_DDESHARE       0x2000
#define GMEM_NOTIFY         0x4000
#define GMEM_LOWER          GMEM_NOT_BANKED
#define GMEM_VALID_FLAGS    0x7F72
#define GMEM_INVALID_HANDLE 0x8000

// WINGDI

typedef struct tagRGBQUAD {
        BYTE    rgbBlue;
        BYTE    rgbGreen;
        BYTE    rgbRed;
        BYTE    rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFOHEADER{
        DWORD      biSize;
        LONG       biWidth;
        LONG       biHeight;
        WORD       biPlanes;
        WORD       biBitCount;
        DWORD      biCompression;
        DWORD      biSizeImage;
        LONG       biXPelsPerMeter;
        LONG       biYPelsPerMeter;
        DWORD      biClrUsed;
        DWORD      biClrImportant;
} BITMAPINFOHEADER, FAR *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagBITMAPINFO {
    BITMAPINFOHEADER    bmiHeader;
    RGBQUAD             bmiColors[1];
} BITMAPINFO, FAR *LPBITMAPINFO, *PBITMAPINFO;

typedef long            FXPT2DOT30, FAR *LPFXPT2DOT30;

typedef struct tagCIEXYZ
{
        FXPT2DOT30 ciexyzX;
        FXPT2DOT30 ciexyzY;
        FXPT2DOT30 ciexyzZ;
} CIEXYZ;
typedef CIEXYZ  FAR *LPCIEXYZ;

typedef struct tagICEXYZTRIPLE
{
        CIEXYZ  ciexyzRed;
        CIEXYZ  ciexyzGreen;
        CIEXYZ  ciexyzBlue;
} CIEXYZTRIPLE;
typedef CIEXYZTRIPLE    FAR *LPCIEXYZTRIPLE;

typedef struct {
        DWORD        bV4Size;
        LONG         bV4Width;
        LONG         bV4Height;
        WORD         bV4Planes;
        WORD         bV4BitCount;
        DWORD        bV4V4Compression;
        DWORD        bV4SizeImage;
        LONG         bV4XPelsPerMeter;
        LONG         bV4YPelsPerMeter;
        DWORD        bV4ClrUsed;
        DWORD        bV4ClrImportant;
        DWORD        bV4RedMask;
        DWORD        bV4GreenMask;
        DWORD        bV4BlueMask;
        DWORD        bV4AlphaMask;
        DWORD        bV4CSType;
        CIEXYZTRIPLE bV4Endpoints;
        DWORD        bV4GammaRed;
        DWORD        bV4GammaGreen;
        DWORD        bV4GammaBlue;
} BITMAPV4HEADER, FAR *LPBITMAPV4HEADER, *PBITMAPV4HEADER;

typedef struct {
        DWORD        bV5Size;
        LONG         bV5Width;
        LONG         bV5Height;
        WORD         bV5Planes;
        WORD         bV5BitCount;
        DWORD        bV5Compression;
        DWORD        bV5SizeImage;
        LONG         bV5XPelsPerMeter;
        LONG         bV5YPelsPerMeter;
        DWORD        bV5ClrUsed;
        DWORD        bV5ClrImportant;
        DWORD        bV5RedMask;
        DWORD        bV5GreenMask;
        DWORD        bV5BlueMask;
        DWORD        bV5AlphaMask;
        DWORD        bV5CSType;
        CIEXYZTRIPLE bV5Endpoints;
        DWORD        bV5GammaRed;
        DWORD        bV5GammaGreen;
        DWORD        bV5GammaBlue;
        DWORD        bV5Intent;
        DWORD        bV5ProfileData;
        DWORD        bV5ProfileSize;
        DWORD        bV5Reserved;
} BITMAPV5HEADER, FAR *LPBITMAPV5HEADER, *PBITMAPV5HEADER;

// Values for bV5CSType
#define PROFILE_LINKED          'LINK'
#define PROFILE_EMBEDDED        'MBED'
//#endif

/* constants for the biCompression field */
#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L
#define BI_JPEG       4L
#define BI_PNG        5L

WINGDIAPI BOOL WINAPI PatBlt(IN HDC, IN int, IN int, IN int, IN int, IN DWORD);
WINGDIAPI HBITMAP WINAPI CreateDIBSection( IN HDC, IN CONST BITMAPINFO *, IN UINT, OUT VOID **, IN HANDLE, IN DWORD);
WINGDIAPI HBITMAP WINAPI CreateBitmap( IN int, IN int, IN UINT, IN UINT, IN CONST VOID *);
WINGDIAPI HBRUSH  WINAPI CreatePatternBrush( IN HBITMAP);
WINGDIAPI HRGN    WINAPI CreateRectRgn( IN int, IN int, IN int, IN int);
WINGDIAPI HRGN    WINAPI CreateRectRgnIndirect( IN CONST RECT *);
WINGDIAPI int     WINAPI CombineRgn( IN HRGN, IN HRGN, IN HRGN, IN int);
WINGDIAPI BOOL   WINAPI SetRectRgn(IN HRGN, IN int, IN int, IN int, IN int);
WINGDIAPI int   WINAPI GetClipBox( IN HDC,  OUT LPRECT);
WINGDIAPI int  WINAPI SelectClipRgn(IN HDC, IN HRGN);
WINGDIAPI HGDIOBJ WINAPI SelectObject(IN HDC, IN HGDIOBJ);
WINGDIAPI BOOL WINAPI DeleteDC( IN HDC);
WINGDIAPI BOOL WINAPI DeleteObject( IN void* /*HGDIOBJ*/);
WINGDIAPI HGDIOBJ WINAPI GetStockObject( IN int);
WINGDIAPI HDC     WINAPI CreateCompatibleDC( IN HDC);
WINGDIAPI BOOL  WINAPI BitBlt( IN HDC, IN int, IN int, IN int, IN int, IN HDC, IN int, IN int, IN DWORD);

/* Stock Logical Objects */
#define WHITE_BRUSH         0
#define LTGRAY_BRUSH        1
#define GRAY_BRUSH          2
#define DKGRAY_BRUSH        3
#define BLACK_BRUSH         4
#define NULL_BRUSH          5
#define HOLLOW_BRUSH        NULL_BRUSH
#define WHITE_PEN           6
#define BLACK_PEN           7
#define NULL_PEN            8
#define OEM_FIXED_FONT      10
#define ANSI_FIXED_FONT     11
#define ANSI_VAR_FONT       12
#define SYSTEM_FONT         13
#define DEVICE_DEFAULT_FONT 14
#define DEFAULT_PALETTE     15
#define SYSTEM_FIXED_FONT   16

/* Binary raster ops */
#define R2_BLACK            1   /*  0       */
#define R2_NOTMERGEPEN      2   /* DPon     */
#define R2_MASKNOTPEN       3   /* DPna     */
#define R2_NOTCOPYPEN       4   /* PN       */
#define R2_MASKPENNOT       5   /* PDna     */
#define R2_NOT              6   /* Dn       */
#define R2_XORPEN           7   /* DPx      */
#define R2_NOTMASKPEN       8   /* DPan     */
#define R2_MASKPEN          9   /* DPa      */
#define R2_NOTXORPEN        10  /* DPxn     */
#define R2_NOP              11  /* D        */
#define R2_MERGENOTPEN      12  /* DPno     */
#define R2_COPYPEN          13  /* P        */
#define R2_MERGEPENNOT      14  /* PDno     */
#define R2_MERGEPEN         15  /* DPo      */
#define R2_WHITE            16  /*  1       */
#define R2_LAST             16

/* Ternary raster operations */
#define SRCCOPY             (DWORD)0x00CC0020 /* dest = source                   */
#define SRCPAINT            (DWORD)0x00EE0086 /* dest = source OR dest           */
#define SRCAND              (DWORD)0x008800C6 /* dest = source AND dest          */
#define SRCINVERT           (DWORD)0x00660046 /* dest = source XOR dest          */
#define SRCERASE            (DWORD)0x00440328 /* dest = source AND (NOT dest )   */
#define NOTSRCCOPY          (DWORD)0x00330008 /* dest = (NOT source)             */
#define NOTSRCERASE         (DWORD)0x001100A6 /* dest = (NOT src) AND (NOT dest) */
#define MERGECOPY           (DWORD)0x00C000CA /* dest = (source AND pattern)     */
#define MERGEPAINT          (DWORD)0x00BB0226 /* dest = (NOT source) OR dest     */
#define PATCOPY             (DWORD)0x00F00021 /* dest = pattern                  */
#define PATPAINT            (DWORD)0x00FB0A09 /* dest = DPSnoo                   */
#define PATINVERT           (DWORD)0x005A0049 /* dest = pattern XOR dest         */
#define DSTINVERT           (DWORD)0x00550009 /* dest = (NOT dest)               */
#define BLACKNESS           (DWORD)0x00000042 /* dest = BLACK                    */
#define WHITENESS           (DWORD)0x00FF0062 /* dest = WHITE                    */

/* CombineRgn() Styles */
#define RGN_AND             1
#define RGN_OR              2
#define RGN_XOR             3
#define RGN_DIFF            4
#define RGN_COPY            5

/* DIB color table identifiers */

#define DIB_RGB_COLORS      0 /* color table in RGBs */
#define DIB_PAL_COLORS      1 /* color table in palette indices */

#if 0
#define STATUS_WAIT_0                    ((MSWindows::DWORD   )0x00000000L)    
#define STATUS_ABANDONED_WAIT_0          ((MSWindows::DWORD   )0x00000080L)    

#define WAIT_FAILED ((DWORD)0xFFFFFFFF)
#define WAIT_OBJECT_0       ((STATUS_WAIT_0 ) + 0 )

#endif

static const DWORD Status_Wait_0 = 0x00000000;
static const DWORD Status_Abandoned_Wait_0 = 0x00000080;
static const DWORD Wait_Failed = 0xFFFFFFFF;
static const DWORD Wait_Object_0 = Status_Wait_0 + 0;

#define INFINITE            0xFFFFFFFF  // Infinite timeout

//

//#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
static const HANDLE Invalid_Handle_Value = (HANDLE)-1;

#define FILE_BEGIN           0
#define FILE_CURRENT         1
#define FILE_END             2

//
//  These are the generic rights.
//

#define GENERIC_READ                     (0x80000000L)
#define GENERIC_WRITE                    (0x40000000L)
#define GENERIC_EXECUTE                  (0x20000000L)
#define GENERIC_ALL                      (0x10000000L)

//

#define CREATE_NEW          1
#define CREATE_ALWAYS       2
#define OPEN_EXISTING       3
#define OPEN_ALWAYS         4
#define TRUNCATE_EXISTING   5

//

#define FILE_SHARE_READ                 0x00000001  
#define FILE_SHARE_WRITE                0x00000002  
#define FILE_SHARE_DELETE               0x00000004  
#define FILE_ATTRIBUTE_READONLY             0x00000001  
#define FILE_ATTRIBUTE_HIDDEN               0x00000002  
#define FILE_ATTRIBUTE_SYSTEM               0x00000004  
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010  
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020  
//#define FILE_ATTRIBUTE_ENCRYPTED            0x00000040  
#define FILE_ATTRIBUTE_DEVICE               0x00000040  
#define FILE_ATTRIBUTE_NORMAL               0x00000080  
#define FILE_ATTRIBUTE_TEMPORARY            0x00000100  
#define FILE_ATTRIBUTE_SPARSE_FILE          0x00000200  
#define FILE_ATTRIBUTE_REPARSE_POINT        0x00000400  
#define FILE_ATTRIBUTE_COMPRESSED           0x00000800  
#define FILE_ATTRIBUTE_OFFLINE              0x00001000  
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000  
#define FILE_ATTRIBUTE_ENCRYPTED            0x00004000  

//
// Define the severity codes
//


//
// MessageId: ERROR_SUCCESS
//
// MessageText:
//
//  The operation completed successfully.
//
#define ERROR_SUCCESS                    0L

#define NO_ERROR 0L                                                 // dderror
//#define SEC_E_OK                         ((HRESULT)0x00000000L)

//

//
// MessageId: ERROR_FILE_NOT_FOUND
//
// MessageText:
//
//  The system cannot find the file specified.
//
#define ERROR_FILE_NOT_FOUND             2L

//
// MessageId: ERROR_PATH_NOT_FOUND
//
// MessageText:
//
//  The system cannot find the path specified.
//
#define ERROR_PATH_NOT_FOUND             3L

//
// MessageId: ERROR_TOO_MANY_OPEN_FILES
//
// MessageText:
//
//  The system cannot open the file.
//
#define ERROR_TOO_MANY_OPEN_FILES        4L

//
// MessageId: ERROR_ACCESS_DENIED
//
// MessageText:
//
//  Access is denied.
//
#define ERROR_ACCESS_DENIED              5L

//
// MessageId: ERROR_INVALID_HANDLE
//
// MessageText:
//
//  The handle is invalid.
//
#define ERROR_INVALID_HANDLE             6L

//
// MessageId: ERROR_SHARING_VIOLATION
//
// MessageText:
//
//  The process cannot access the file because it is being used by another process.
//
#define ERROR_SHARING_VIOLATION          32L

//
// MessageId: ERROR_LOCK_VIOLATION
//
// MessageText:
//
//  The process cannot access the file because another process has locked a portion of the file.
//
#define ERROR_LOCK_VIOLATION             33L

#define MAX_PATH          260

typedef struct _WIN32_FIND_DATAA {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD dwReserved0;
    DWORD dwReserved1;
    char   cFileName[ MAX_PATH ];
    char   cAlternateFileName[ 14 ];
#ifdef _MAC
    DWORD dwFileType;
    DWORD dwCreatorType;
    WORD  wFinderFlags;
#endif
} WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;

typedef struct _WIN32_FIND_DATAW {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD dwReserved0;
    DWORD dwReserved1;
    WCHAR   cFileName[ MAX_PATH ];
    WCHAR   cAlternateFileName[ 14 ];
#ifdef _MAC
    DWORD dwFileType;
    DWORD dwCreatorType;
    WORD  wFinderFlags;
#endif
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;

WINBASEAPI
HANDLE
WINAPI
FindFirstFileA(
    IN LPCSTR lpFileName,
    OUT LPWIN32_FIND_DATAA lpFindFileData
    );

WINBASEAPI
HANDLE
WINAPI
FindFirstFileW(
    IN LPCWSTR lpFileName,
    OUT LPWIN32_FIND_DATAW lpFindFileData
    );

WINBASEAPI
BOOL
WINAPI
FindNextFileA(
    IN HANDLE hFindFile,
    OUT LPWIN32_FIND_DATAA lpFindFileData
    );

WINBASEAPI
BOOL
WINAPI
FindNextFileW(
    IN HANDLE hFindFile,
    OUT LPWIN32_FIND_DATAW lpFindFileData
    );

WINBASEAPI
BOOL
WINAPI
FindClose(
    IN OUT HANDLE hFindFile
    );

WINBASEAPI
VOID
WINAPI
Sleep(
    IN DWORD dwMilliseconds
    );

WINBASEAPI
BOOL
WINAPI
FileTimeToSystemTime(
    IN CONST FILETIME *lpFileTime,
    OUT LPSYSTEMTIME lpSystemTime
    );

WINBASEAPI
BOOL
WINAPI
SystemTimeToFileTime(
  CONST SYSTEMTIME *lpSystemTime,
  LPFILETIME lpFileTime
);

WINBASEAPI
LONG
WINAPI
CompareFileTime(
  CONST FILETIME *lpFileTime1,  // pointer to first file time
  CONST FILETIME *lpFileTime2   // pointer to second file time
);

WINBASEAPI VOID WINAPI GetLocalTime(
  LPSYSTEMTIME lpSystemTime   // address of system time structure
);

WINBASEAPI ULONG WINAPI GetTickCount();

// mmsystem

#define WINMMAPI        DECLSPEC_IMPORT
typedef UINT        MMRESULT;   /* error return code, 0 means no error */

/* timer data types */
typedef void (CALLBACK TIMECALLBACK)(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

typedef TIMECALLBACK FAR *LPTIMECALLBACK;

#ifdef _WIN32
#define TIME_CALLBACK_FUNCTION      0x0000  /* callback is function */
#define TIME_CALLBACK_EVENT_SET     0x0010  /* callback is event - use SetEvent */
#define TIME_CALLBACK_EVENT_PULSE   0x0020  /* callback is event - use PulseEvent */
#endif

/* flags for fuEvent parameter of timeSetEvent() function */
#define TIME_ONESHOT    0x0000   /* program timer for single event */
#define TIME_PERIODIC   0x0001   /* program for continuous periodic event */

WINMMAPI MMRESULT WINAPI timeSetEvent( IN UINT uDelay, IN UINT uResolution,
    IN LPTIMECALLBACK fptc, IN DWORD_PTR dwUser, IN UINT fuEvent);
WINMMAPI MMRESULT WINAPI timeKillEvent( IN UINT uTimerID);


	typedef union _LARGE_INTEGER {
    struct {
        DWORD LowPart;
        LONG HighPart;
    };
    struct {
        DWORD LowPart;
        LONG HighPart;
    } u;
} LARGE_INTEGER;

	typedef LARGE_INTEGER *PLARGE_INTEGER;

//
// Performance counter API's
//
WINBASEAPI
BOOL
WINAPI
QueryPerformanceCounter(
    OUT LARGE_INTEGER *lpPerformanceCount
    );

WINBASEAPI
BOOL
WINAPI
QueryPerformanceFrequency(
    OUT LARGE_INTEGER *lpFrequency
    );

//
WINBASEAPI BOOL WINAPI AllocConsole();
WINBASEAPI HANDLE WINAPI GetStdHandle(DWORD nStdHandle);

/*
#define STD_INPUT_HANDLE    ((UINT)-10)
#define STD_OUTPUT_HANDLE   ((UINT)-11)
#define STD_ERROR_HANDLE    ((UINT)-12)
*/

static const DWORD Std_Input_Handle = (DWORD)-10;
static const DWORD Std_Output_Handle = (DWORD)-11;
static const DWORD Std_Error_Handle = (DWORD)-12;

struct SYSTEM_INFO
{
	union
	{
		DWORD dwOemId;
		struct
		{
			WORD wProcessorArchitecture;
			WORD wReserved;
		};
	};
	DWORD dwPageSize;
	LPVOID lpMinimumApplicationAddress;
	LPVOID lpMaximumApplicationAddress;
	DWORD_PTR dwActiveProcessorMask;
	DWORD dwNumberOfProcessors;
	DWORD dwProcessorType;
	DWORD dwAllocationGranularity;
	WORD wProcessorLevel;
	WORD wProcessorRevision;
};

WINBASEAPI void WINAPI GetSystemInfo(SYSTEM_INFO* pSystemInfo);

BOOL WINAPI InternetCombineUrlA(
    /*IN*/ LPCSTR lpszBaseUrl,
    /*IN*/ LPCSTR lpszRelativeUrl,
    /*OUT*/ LPSTR lpszBuffer,
    /*IN OUT*/ DWORD * lpdwBufferLength,
    /*IN*/ DWORD dwFlags
    );
BOOL WINAPI InternetCombineUrlW(
    /*IN*/ LPCWSTR lpszBaseUrl,
    /*IN*/ LPCWSTR lpszRelativeUrl,
    /*OUT*/ LPWSTR lpszBuffer,
    /*IN OUT*/ DWORD * lpdwBufferLength,
    /*IN*/ DWORD dwFlags
    );

// DWM

typedef struct _MARGINS {
    int cxLeftWidth;
    int cxRightWidth;
    int cyTopHeight;
    int cyBottomHeight;
} MARGINS, *PMARGINS;

#define STDAPICALLTYPE __stdcall

#define DWMAPI          EXTERN_C DECLSPEC_IMPORT HRESULT STDAPICALLTYPE
#define DWMAPI_(type)   EXTERN_C DECLSPEC_IMPORT type STDAPICALLTYPE

// dwmapi.dll

#include <pshpack1.h>

DWMAPI DwmIsCompositionEnabled(/*__out*/ BOOL *pfEnabled);

DWMAPI DwmEnableMMCSS(BOOL fEnableMMCSS);

DWMAPI DwmSetDxFrameDuration(HWND hwnd,
    int cRefreshes
);

DWMAPI DwmGetWindowAttribute(HWND hwnd,
    DWORD dwAttribute,
    PVOID pvAttribute,
    DWORD cbAttribute
);

DWMAPI DwmSetWindowAttribute(HWND hwnd,
    DWORD dwAttribute,
    LPCVOID pvAttribute,
    DWORD cbAttribute
);

DWMAPI DwmExtendFrameIntoClientArea(HWND hWnd,
    const MARGINS *pMarInset
);

typedef enum _DWMWINDOWATTRIBUTE {
    DWMWA_NCRENDERING_ENABLED = 1,
    DWMWA_NCRENDERING_POLICY,
    DWMWA_TRANSITIONS_FORCEDISABLED,
    DWMWA_ALLOW_NCPAINT,
    DWMWA_CAPTION_BUTTON_BOUNDS,
    DWMWA_NONCLIENT_RTL_LAYOUT,
    DWMWA_FORCE_ICONIC_REPRESENTATION,
    DWMWA_FLIP3D_POLICY,
    DWMWA_EXTENDED_FRAME_BOUNDS,
    DWMWA_LAST
} DWMWINDOWATTRIBUTE;

typedef enum _DWMNCRENDERINGPOLICY {
    DWMNCRP_USEWINDOWSTYLE,
    DWMNCRP_DISABLED,
    DWMNCRP_ENABLED,
    DWMNCRP_LAST
} DWMNCRENDERINGPOLICY;

// Video enabling apis

typedef ULONGLONG DWM_FRAME_COUNT;
typedef ULONGLONG QPC_TIME;

typedef  struct _UNSIGNED_RATIO
{
    UINT32 uiNumerator;
    UINT32 uiDenominator;
} UNSIGNED_RATIO;

typedef  struct _DWM_TIMING_INFO
{
    UINT32          cbSize;

    // Data on DWM composition overall
    
    // Monitor refresh rate
    UNSIGNED_RATIO  rateRefresh;

    // Actual period
    QPC_TIME        qpcRefreshPeriod;

    // composition rate     
    UNSIGNED_RATIO  rateCompose;

    // QPC time at a VSync interupt
    QPC_TIME        qpcVBlank;

    // DWM refresh count of the last vsync
    // DWM refresh count is a 64bit number where zero is
    // the first refresh the DWM woke up to process
    DWM_FRAME_COUNT cRefresh;

    // DX refresh count at the last Vsync Interupt
    // DX refresh count is a 32bit number with zero 
    // being the first refresh after the card was initialized
    // DX increments a counter when ever a VSync ISR is processed
    // It is possible for DX to miss VSyncs
    //
    // There is not a fixed mapping between DX and DWM refresh counts
    // because the DX will rollover and may miss VSync interupts
    UINT cDXRefresh;

    // QPC time at a compose time.  
    QPC_TIME        qpcCompose;

    // Frame number that was composed at qpcCompose
    DWM_FRAME_COUNT cFrame;

    // The present number DX uses to identify renderer frames
    UINT            cDXPresent;

    // Refresh count of the frame that was composed at qpcCompose
    DWM_FRAME_COUNT cRefreshFrame;


    // DWM frame number that was last submitted
    DWM_FRAME_COUNT cFrameSubmitted;

    // DX Present number that was last submitted
    UINT cDXPresentSubmitted;

    // DWM frame number that was last confirmed presented
    DWM_FRAME_COUNT cFrameConfirmed;

    // DX Present number that was last confirmed presented
    UINT cDXPresentConfirmed;

    // The target refresh count of the last
    // frame confirmed completed by the GPU
    DWM_FRAME_COUNT cRefreshConfirmed;

    // DX refresh count when the frame was confirmed presented
    UINT cDXRefreshConfirmed;

    // Number of frames the DWM presented late
    // AKA Glitches
    DWM_FRAME_COUNT          cFramesLate;
    
    // the number of composition frames that 
    // have been issued but not confirmed completed
    UINT          cFramesOutstanding;


    // Following fields are only relavent when an HWND is specified
    // Display frame


    // Last frame displayed
    DWM_FRAME_COUNT cFrameDisplayed;

    // QPC time of the composition pass when the frame was displayed
    QPC_TIME        qpcFrameDisplayed; 

    // Count of the VSync when the frame should have become visible
    DWM_FRAME_COUNT cRefreshFrameDisplayed;

    // Complete frames: DX has notified the DWM that the frame is done rendering

    // ID of the the last frame marked complete (starts at 0)
    DWM_FRAME_COUNT cFrameComplete;

    // QPC time when the last frame was marked complete
    QPC_TIME        qpcFrameComplete;

    // Pending frames:
    // The application has been submitted to DX but not completed by the GPU
 
    // ID of the the last frame marked pending (starts at 0)
    DWM_FRAME_COUNT cFramePending;

    // QPC time when the last frame was marked pending
    QPC_TIME        qpcFramePending;

    // number of unique frames displayed
    DWM_FRAME_COUNT cFramesDisplayed;

    // number of new completed frames that have been received
    DWM_FRAME_COUNT cFramesComplete;

     // number of new frames submitted to DX but not yet complete
    DWM_FRAME_COUNT cFramesPending;

    // number of frames available but not displayed, used or dropped
    DWM_FRAME_COUNT cFramesAvailable;

    // number of rendered frames that were never
    // displayed because composition occured too late
    DWM_FRAME_COUNT cFramesDropped;
    
    // number of times an old frame was composed 
    // when a new frame should have been used
    // but was not available
    DWM_FRAME_COUNT cFramesMissed;
    
    // the refresh at which the next frame is
    // scheduled to be displayed
    DWM_FRAME_COUNT cRefreshNextDisplayed;

    // the refresh at which the next DX present is 
    // scheduled to be displayed
    DWM_FRAME_COUNT cRefreshNextPresented;

    // The total number of refreshes worth of content
    // for this HWND that have been displayed by the DWM
    // since DwmSetPresentParameters was called
    DWM_FRAME_COUNT cRefreshesDisplayed;
	
    // The total number of refreshes worth of content
    // that have been presented by the application
    // since DwmSetPresentParameters was called
    DWM_FRAME_COUNT cRefreshesPresented;


    // The actual refresh # when content for this
    // window started to be displayed
    // it may be different than that requested
    // DwmSetPresentParameters
    DWM_FRAME_COUNT cRefreshStarted;

    // Total number of pixels DX redirected
    // to the DWM.
    // If Queueing is used the full buffer
    // is transfered on each present.
    // If not queuing it is possible only 
    // a dirty region is updated
    ULONGLONG  cPixelsReceived;

    // Total number of pixels drawn.
    // Does not take into account if
    // if the window is only partial drawn
    // do to clipping or dirty rect management 
    ULONGLONG  cPixelsDrawn;

    // The number of buffers in the flipchain
    // that are empty.   An application can 
    // present that number of times and guarantee 
    // it won't be blocked waiting for a buffer to 
    // become empty to present to
    DWM_FRAME_COUNT      cBuffersEmpty;

} DWM_TIMING_INFO;

DWMAPI DwmGetCompositionTimingInfo(HWND hwnd,
    DWM_TIMING_INFO *pTimingInfo
);

typedef enum 
{
    // Use the first source frame that 
    // includes the first refresh of the output frame
    DWM_SOURCE_FRAME_SAMPLING_POINT,

    // use the source frame that includes the most 
    // refreshes of out the output frame
    // in case of multiple source frames with the 
    // same coverage the last will be used
    DWM_SOURCE_FRAME_SAMPLING_COVERAGE,

       // Sentinel value
    DWM_SOURCE_FRAME_SAMPLING_LAST
} DWM_SOURCE_FRAME_SAMPLING;

static const UINT c_DwmMaxQueuedBuffers = 8;
static const UINT c_DwmMaxMonitors = 16;
static const UINT c_DwmMaxAdapters = 16;

typedef struct _DWM_PRESENT_PARAMETERS {
    UINT32 cbSize;
    BOOL fQueue;
    DWM_FRAME_COUNT cRefreshStart;
    UINT cBuffer;
    BOOL fUseSourceRate;
    UNSIGNED_RATIO rateSource;
    UINT cRefreshesPerFrame;
    DWM_SOURCE_FRAME_SAMPLING eSampling;
} DWM_PRESENT_PARAMETERS;

DWMAPI DwmSetPresentParameters(HWND hwnd,
    DWM_PRESENT_PARAMETERS *pPresentParams
);

#define GetRValue(rgb)      ((uint8)(rgb))
#define GetGValue(rgb)      ((uint8)(((uint16)(rgb)) >> 8))
#define GetBValue(rgb)      ((uint8)((rgb)>>16))

#include <poppack.h>

typedef WORD ATOM;

struct IUnknown
{
	virtual HRESULT QueryInterface(const void* guid, void** pv) = 0;
	virtual ULONG AddRef() = 0;
	virtual ULONG Release() = 0;
};

struct IDispatch : public IUnknown
{
};

#define __in

typedef DWORD LCID;
typedef WORD LANGID;

typedef long GEOID;

typedef /* [wire_marshal] */ struct tagVARIANT VARIANT;
typedef /* [wire_marshal] */ struct tagVARIANT PROPVARIANT;
struct tagVARIANT
{
	WORD vt;
	WORD reserved0;
	WORD reserved1;
	WORD reserved2;
	union
	{
		long long llVal;
		long long* pllVal;
	};
};

struct SAFEARRAY;

typedef double DATE;

typedef struct _PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId;
    DWORD dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;

#define ALL_PROCESSOR_GROUPS        0xffff

//
// Structure to represent a system wide processor number. It contains a
// group number and relative processor number within the group.
//

typedef struct _PROCESSOR_NUMBER {
    WORD   Group;
    BYTE  Number;
    BYTE  Reserved;
} PROCESSOR_NUMBER, *PPROCESSOR_NUMBER;

//
// Legacy thread affinity.
//

typedef ULONG_PTR KAFFINITY;
typedef KAFFINITY *PKAFFINITY;

//
// Structure to represent a group-specific affinity, such as that of a
// thread.  Specifies the group number and the affinity within that group.
//

typedef struct _GROUP_AFFINITY {
    KAFFINITY Mask;
    WORD   Group;
    WORD   Reserved[3];
} GROUP_AFFINITY, *PGROUP_AFFINITY;

#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name

DECLARE_HANDLE(HKEY);
typedef HKEY *PHKEY;

#ifdef __cplusplus
}
#endif

#endif // windows_header_h
