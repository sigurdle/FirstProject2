#include "stdafx.h"
#include "LXUI2.h"

#include "Cursor.h"
/*
namespace std
{
#include <stdlib.h>	// rand
}
*/

//#undef _INC_WINDOWS
//#include <ddraw.h>

//#undef _INC_WINDOWS
#include <windows.h>
#undef DefWindowProc

//#include <d3d8.h>
#include <d3d9.h>
#include <D3dx9math.h>

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>

#include <gl/wglext.h>

#include <ctime>

#if WIN32

//#include <windows.h>

#if 0
#pragma comment(lib, "dwmapi.lib")
#endif

//extern "C" IDirectDrawSurface* DoDirect(void* hWnd, int width, int height);

namespace System
{
	/*
	namespace LDraw
	{
DrawExt void MakeCurrent(GraphicsO* current);
}
*/

	namespace MSWindows
	{

IDirect3DDevice9* D3D_CreateDevice(HWND hWnd, D3DPRESENT_PARAMETERS9* d3dpp);
void D3D_ResetDevice(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS9* d3dpp);
void D3D_ReleaseDevice(IDirect3DDevice9* pDevice);
HRESULT D3D_CreateAdditionalSwapChain(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS9* d3dpp, IDirect3DSwapChain9** pSwapChain);
extern "C" void* D3D_CreateImageSurface(IDirect3DDevice9* pDevice, int width, int height);
extern "C" void D3D_ReleaseSurface(void* pSurface);
extern "C" void D3D_CopyRect(IDirect3DDevice9* pDevice, int dstx, int dsty, void* pSurface, int srcx, int srcy, int width, int height);
void D3D_Present(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect);
void D3D_Present(IDirect3DSwapChain9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND destWindowOverride);
void D3D_Clear(IDirect3DDevice9* pDevice);
void D3D_BeginScene(IDirect3DDevice9* pDevice);
void D3D_EndScene(IDirect3DDevice9* pDevice);

extern "C" void ReleaseDDSurface(void* dds);
extern "C" System::LDraw::Bitmap* D3D_GetBitmap(void* d3dSurface);
extern "C" void D3D_UnlockBitmap(void* d3dSurface, System::LDraw::Bitmap* bitmap);
extern "C" void BltPrimary(int window_x, int window_y, void* srcSurface, int x, int y, int width, int height);

	}
}

bool UseDWM = false;
bool UseDirectDraw = true;

namespace System
{

namespace MSWindows
{

extern "C"
{

	typedef DWORD COLORREF;

#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

typedef ULONG HPEN;

DECLSPEC_DLLIMPORT int __stdcall GetDeviceCaps(
  HDC hdc,     // handle to the device context
  int nIndex   // index of capability to query
);
 
WINGDIAPI HPEN    WINAPI CreatePen( IN int, IN int, IN COLORREF);

WINGDIAPI HBRUSH  WINAPI CreateSolidBrush( IN COLORREF);

WINGDIAPI HGDIOBJ WINAPI GetStockObject( IN int);

/* Pen Styles */
#define PS_SOLID            0
#define PS_DASH             1       /* -------  */
#define PS_DOT              2       /* .......  */
#define PS_DASHDOT          3       /* _._._._  */
#define PS_DASHDOTDOT       4       /* _.._.._  */
#define PS_NULL             5
#define PS_INSIDEFRAME      6
#define PS_USERSTYLE        7
#define PS_ALTERNATE        8
#define PS_STYLE_MASK       0x0000000F

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

/* Device Parameters for GetDeviceCaps() */
#define DRIVERVERSION 0     /* Device driver version                    */
#define TECHNOLOGY    2     /* Device classification                    */
#define HORZSIZE      4     /* Horizontal size in millimeters           */
#define VERTSIZE      6     /* Vertical size in millimeters             */
#define HORZRES       8     /* Horizontal width in pixels               */
#define VERTRES       10    /* Vertical height in pixels                */
#define BITSPIXEL     12    /* Number of bits per pixel                 */
#define PLANES        14    /* Number of planes                         */
#define NUMBRUSHES    16    /* Number of brushes the device has         */
#define NUMPENS       18    /* Number of pens the device has            */
#define NUMMARKERS    20    /* Number of markers the device has         */
#define NUMFONTS      22    /* Number of fonts the device has           */
#define NUMCOLORS     24    /* Number of colors the device supports     */
#define PDEVICESIZE   26    /* Size required for device descriptor      */
#define CURVECAPS     28    /* Curve capabilities                       */
#define LINECAPS      30    /* Line capabilities                        */
#define POLYGONALCAPS 32    /* Polygonal capabilities                   */
#define TEXTCAPS      34    /* Text capabilities                        */
#define CLIPCAPS      36    /* Clipping capabilities                    */
#define RASTERCAPS    38    /* Bitblt capabilities                      */
#define ASPECTX       40    /* Length of the X leg                      */
#define ASPECTY       42    /* Length of the Y leg                      */
#define ASPECTXY      44    /* Length of the hypotenuse                 */

#define LOGPIXELSX    88    /* Logical pixels/inch in X                 */
#define LOGPIXELSY    90    /* Logical pixels/inch in Y                 */

#define SIZEPALETTE  104    /* Number of entries in physical palette    */
#define NUMRESERVED  106    /* Number of reserved entries in palette    */
#define COLORRES     108    /* Actual color resolution                  */

DECLSPEC_DLLIMPORT BOOL __stdcall Rectangle(
  HDC hdc,         // handle to device context
  int nLeftRect,   // x-coord of bounding rectangle's upper-left corner
  int nTopRect,    // y-coord of bounding rectangle's upper-left corner
  int nRightRect,  // x-coord of bounding rectangle's lower-right corner
  int nBottomRect  // y-coord of bounding rectangle's lower-right corner
);

DECLSPEC_DLLIMPORT int __stdcall ToAscii(
  UINT uVirtKey,     // virtual-key code
  UINT uScanCode,    // scan code
  uint8* lpKeyState,  // key-state array
  uint16* lpChar,     // buffer for translated key
  UINT uFlags        // active-menu flag
);

}	// extern "C"
}	// MSWindows
}	// System

#endif

#ifdef WINTAB

#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef int * LPINT;
typedef BYTE * LPBYTE;

//#define DECLARE_HANDLE(x)	typedef struct ##x__ * x;

#include "Tablet.h"

namespace System
{
namespace UI
{

extern bool g_bTabletInstalled;
extern int g_nTabletMinPressure;
extern int g_nTabletMaxPressure;

int g_redrawCount = 0;
}
}

#endif

namespace System
{

extern DECLSPEC_DLLIMPORT Heap* heap;

//using namespace MSWindows;

namespace UI
{

MSWindows::WindowImpl* g_wnd;
UIEXT IDirect3DDevice9* g_d3dDevice9;	// The one and only
MSWindows::D3DPRESENT_PARAMETERS9 g_d3dpp9;

LDraw::BufferData* g_bufferData;
__live_object_ptr<LDraw::GraphicsO::Resources> g_resources;

UIEXT IDirect3DDevice9* GetD3DDevice9()
{
	if (g_d3dDevice9 == NULL)
	{
		g_wnd = new MSWindows::WindowImpl;
		AddPersistentLiveRoot((void**)&g_wnd);

		g_wnd->Create(NULL, LDraw::RectI(0, 0, 1, 1), NULL, WS_POPUP, 0);

		g_d3dDevice9 = D3D_CreateDevice(g_wnd->m_hWnd, &g_d3dpp9);
		if (g_d3dDevice9 == NULL)
		{
			throw new Exception(WSTR("Couldn't create Direct3D 9 device"));
		}
	}

	return g_d3dDevice9;
}

UIEXT signal1<Object*> g_presented;

UIEXT HANDLE g_PresentEvent;
HANDLE g_MyEvent;

int g_uiLocked = 0;

//UIEXT LDraw::DrawImageRectCommand* g_pDrawCommand;

#if WIN32
/*__declspec(thread)*/ __live_object_ptr<TimerWindow> g_timerWindow;

TimerWindow::TimerWindow()
{
	m_nTimerID = 0;
}

bool TimerWindow::ProcessWindowMessage(MSWindows::Hwnd hWnd, UINT uMsg, MSWindows::WPARAM wParam, MSWindows::LPARAM lParam, MSWindows::LRESULT& lResult/*, DWORD dwMsgMapID*/ )
{
	bool bHandled = true;
	switch (uMsg)
	{
	case WM_TIMER:
		{
			UINT wTimerID = wParam;
			TimerTarget* p = m_timerListeners[wTimerID];

			p->OnTimer(wTimerID);
#if 0
			System::Event* evt = new System::Event;
			evt->InitEvent(WSTR("timer"), false, false);

			/*bool bDefault =*/ p->m_target->dispatchEvent(evt);
			return true;
#endif
		}
		break;
	}
	return false;
}

UINT SetTimer(UINT ms, const signal1<UINT>::slot_function_type& ontimer)
{
	if (g_timerWindow == NULL)
	{
		g_timerWindow = new TimerWindow;
		g_timerWindow->Create(NULL, LDraw::RectI(), NULL, WS_POPUP);
	}

//	if (target == NULL) return 0;

	++g_timerWindow->m_nTimerID;

	TimerWindow::TimerTarget* p = new TimerWindow::TimerTarget;
	p->m_ms = ms;
//	p->m_target = target;
	p->OnTimer.connect(ontimer);

	g_timerWindow->m_timerListeners[g_timerWindow->m_nTimerID] = p;

#if WIN32
	if (g_timerWindow->m_hWnd)
	{
		MSWindows::SetTimer(g_timerWindow->m_hWnd, g_timerWindow->m_nTimerID, ms, NULL);
	}
#endif

	return g_timerWindow->m_nTimerID;
}

void KillTimer(UINT nID)
{
	MSWindows::KillTimer(g_timerWindow->m_hWnd, nID);
	g_timerWindow->m_timerListeners.erase(nID);
}

#endif

#if AMIGA

UINT SetTimer(UINT ms, System::IEventTarget* target)
{
	ASSERT(0);
	return 0;
}

void KillTimer(UINT nID)
{
	ASSERT(0);
//	g_timerWindow->m_timerListeners.erase(nID);
}
#endif

	MSWindows::DWM_TIMING_INFO m_timing_info = {0};

}	// UI
}	// System

/*
struct BITMAPINFOHEADER
{
	uint32      biSize;
	LONG       biWidth;
	LONG       biHeight;
	uint16       biPlanes;
	uint16       biBitCount;
	uint32      biCompression;
	uint32      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	uint32      biClrUsed;
	uint32      biClrImportant;
};
*/

#ifdef WINTAB
/////////////////////////////////////////////////////////////////////////////
//TABLET: setup required here
//
//
//    define what packet data is required here.  A PACKET structure
//    will be created by pktdef.h  Only the required information
//    will be returned in each packet, so some of the members will
//    not be available, depending on your choices here.  Change your code as appropriate.
//    For multiple packet types refer to the WinTab API reference.
//
//#define PACKETDATA	(PK_Z | PK_NORMAL_PRESSURE | PK_ORIENTATION | PK_TANGENT_PRESSURE)
//#define PACKETDATA	(PK_Z | PK_NORMAL_PRESSURE)
//#define PACKETDATA	(PK_X | PK_Y | PK_BUTTONS | PK_NORMAL_PRESSURE | PK_ORIENTATION | PK_CURSOR)
//#define PACKETDATA	(PK_Z | PK_NORMAL_PRESSURE | PK_ORIENTATION | PK_CURSOR)
#define PACKETDATA	(PK_X | PK_Y | PK_NORMAL_PRESSURE | PK_ORIENTATION | PK_CURSOR)
#define PACKETMODE      0
namespace System
{
	namespace MSWindows
	{
#include "../WinTab/include/pktdef.h"
	}
}
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "HwndSource.h"
#include "VisualContentSource.h"

#define USE_CLIPPING	1

#if __APPLE__
#define LDraw carbonLDraw
#include <Carbon/Carbon.h>
#undef LDraw
#endif

#if WIN32

extern HANDLE g_hEvent;

#define DECLSPEC_SELECTANY  __declspec(selectany)

extern "C" const DECLSPEC_SELECTANY System::GUID IID_IDirectDraw2 = {                  0xB3A6F3E0,0x2B43,0x11CF,0xA2,0xDE,0x00,0xAA,0x00,0xB9,0x33,0x56 };

#endif

namespace System
{
namespace UI
{

#if 0//WIN32

class OleDropTarget :
//	public CComObjectRootEx<CComSingleThreadModel>,
	public IDropTarget
{
public:
	OleDropTarget()
	{
		m_pOwner = NULL;

		m_dwRef = 0;
	}

	HwndSource* m_pOwner;

	virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
	{
		if (riid == IID_IUnknown)
		{
			*ppvObject = reinterpret_cast<void*>(static_cast<IUnknown*>(this));
		}
		else if (riid == IID_IDropTarget)
		{
			*ppvObject = reinterpret_cast<void*>(static_cast<IDropTarget*>(this));
		}
		else
			return E_NOINTERFACE;
		
		AddRef();
		return S_OK;
	}

	virtual ULONG STDMETHODCALLTYPE AddRef( void)
	{
		InterlockedIncrement((long*)&m_dwRef);
		return m_dwRef;
	}

	virtual ULONG STDMETHODCALLTYPE Release( void)
	{
		m_dwRef--;
		if (m_dwRef == 0)
		{
			delete this;
			return 0;
		}
		return m_dwRef;
	}

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(OleDropTarget)
	COM_INTERFACE_ENTRY(IDropTarget)
END_COM_MAP()
*/

	ULONG m_dwRef;

public:
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
};

#endif

extern UIEXT __live_object_ptr<LayoutManager> pLayoutManager;
UIEXT int g_nWindows = 0;

unsigned long renderThreadId;

ULONG WINAPI CALLBACK RenderThread(void* lParam)
{
	/*
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		while (PeekMessage(&msg, NULL, 0, 0, 0))
			;

		UI::pLayoutManager->MeasureAll();
		UI::pLayoutManager->RenderAll();
	}
	*/
	while (1)
	{
		MSWindows::WaitForSingleObject(g_MyEvent, INFINITE);
		UI::pLayoutManager->RenderAll();
	}

	return 0;
}

#if __APPLE__

OSStatus EventHandler(EventHandlerCallRef inHandlerCallRef, EventRef inEvent, void *inUserData)
{
	HwndSource* pWindow = (HwndSource*)inUserData;

	switch (GetEventClass(inEvent))
	{
	case kEventClassMouse:
		{
			switch (GetEventKind(inEvent))
			{
			case kEventMouseDown:
				{
					::Rect bounds;
					GetWindowBounds(pWindow->m_hWnd, kWindowStructureRgn, &bounds);
					
					::Point qdpoint;
					GetEventParameter(inEvent, kEventParamMouseLocation, typeQDPoint, NULL, sizeof(qdpoint), NULL, &qdpoint);
					LDraw::PointI screenpoint;
					screenpoint.X = qdpoint.h;
					screenpoint.Y = qdpoint.v;
					
					LDraw::PointI point = screenpoint;
					point.X -= bounds.left;
					point.Y -= bounds.top;
					//	GetEventParameter(inEvent, kEventParamWindowMouseLocation, typeQDPoint, NULL, 8, NULL, &point);
					
					//	printf("MouseDown screen(%d,%d) window(%d,%d)\n", screenpoint.X, screenpoint.Y, point.X, point.Y);
					//	fflush(stdout);
					
					UINT nFlags = 0;
					pWindow->m_pClient->OnButtonDown(nFlags, screenpoint, point, 0, false);
					
					pLayoutManager->MeasureAll();
					pLayoutManager->RenderAll();
					
					return CallNextEventHandler(inHandlerCallRef, inEvent);
				}
				break;
				
			case kEventMouseUp:
				{
					::Rect bounds;
					GetWindowBounds(pWindow->m_hWnd, kWindowStructureRgn, &bounds);
					
					::Point qdpoint;
					GetEventParameter(inEvent, kEventParamMouseLocation, typeQDPoint, NULL, sizeof(qdpoint), NULL, &qdpoint);
					LDraw::PointI screenpoint;
					screenpoint.X = qdpoint.h;
					screenpoint.Y = qdpoint.v;
					
					LDraw::PointI point = screenpoint;
					point.X -= bounds.left;
					point.Y -= bounds.top;
					
					//	printf("MouseUp screen(%d,%d) window(%d,%d)\n", screenpoint.X, screenpoint.Y, point.X, point.Y);
					//	fflush(stdout);
					
					UINT nFlags = 0;
					pWindow->m_pClient->OnButtonUp(nFlags, screenpoint, point, 0);
					
					pLayoutManager->MeasureAll();
					pLayoutManager->RenderAll();
				}
				break;
				
			case kEventMouseMoved:
			case kEventMouseDragged:
				{
					::Rect bounds;
					GetWindowBounds(pWindow->m_hWnd, kWindowStructureRgn, &bounds);
					
					::Point qdpoint;
					GetEventParameter(inEvent, kEventParamMouseLocation, typeQDPoint, NULL, sizeof(qdpoint), NULL, &qdpoint);
					LDraw::PointI screenpoint;
					screenpoint.X = qdpoint.h;
					screenpoint.Y = qdpoint.v;
					
					LDraw::PointI point = screenpoint;
					point.X -= bounds.left;
					point.Y -= bounds.top;
					
					//	printf("MouseMoved screen(%d,%d) window(%d,%d)\n", screenpoint.X, screenpoint.Y, point.X, point.Y);
					//	fflush(stdout);
					
					pWindow->m_pClient->m_bInsideWindow = true;	// ??
					
					UINT nFlags = 0;
					pWindow->m_pClient->OnMouseMove(nFlags, screenpoint, point);
					
					pLayoutManager->MeasureAll();
					pLayoutManager->RenderAll();
				}
				break;
			}
		}
		break;

	case kEventClassWindow:
		{
			switch (GetEventKind(inEvent))
			{
			case kEventWindowActivated:
				{
					printf("Activate\n");
					pWindow->m_pClient->OnActivate(true);
				}
				break;

			case kEventWindowDeactivated:
				{
					printf("Deactivate\n");
					pWindow->m_pClient->OnActivate(false);
				}
				break;
			}
		}
		break;
	}
}

#endif

#if AMIGA

/* remove and reply all IntuiMessages on a port that
* have been sent to a particular window
* (note that we don't rely on the ln_Succ pointer
*  of a message after we have replied it)
*/
void StripIntuiMessages(struct MsgPort * mp, struct Window *win )
{
	struct IntuiMessage *msg;
	struct Node *succ;
	
	msg = (struct IntuiMessage *) mp->mp_MsgList.lh_Head;
	
	while( succ =  msg->ExecMessage.mn_Node.ln_Succ ) {
		
		if( msg->IDCMPWindow ==  win ) {
			
		    /* Intuition is about to free this message.
			 * Make sure that we have politely sent it back.
			*/
			execRemove((struct Node*)msg);
			
			ReplyMsg((struct Message*) msg );
		}
		    
		msg = (struct IntuiMessage *) succ;
	}
}

void CleanupWindow(struct Window * win )
{
	/* we forbid here to keep out of race conditions with Intuition */
	Forbid();
	
	/* send back any messages for this window 
	* that have not yet been processed
	*/
	StripIntuiMessages( win->UserPort, win );
	
	/* clear UserPort so Intuition will not free it */
	win->UserPort = NULL;
	
	/* tell Intuition to stop sending more messages */
	ModifyIDCMP( win, 0L );
	
	/* turn multitasking back on */
	Permit();
}

void CloseWindowSafely(struct Window * win )
{
	CleanupWindow(win);
	
	/* and really close the window */
	intuiCloseWindow( win );
}

#endif

#if 0//WIN32


/////////////////////////////////////////////////////////////////////////
// OleDropTarget

STDMETHODIMP OleDropTarget::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	*pdwEffect = DROPEFFECT_COPY;
	return S_OK;
}

STDMETHODIMP OleDropTarget::DragOver(DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
	POINT pt;
	pt.x = ptl.x;
	pt.y = ptl.y;
	::ScreenToClient(m_pOwner->GetHwnd(), &pt);
	LDraw::PointI point(pt.x, pt.y);

	ASSERT(0);
#if 0

	UIElement* pPElement;
	pPElement = m_pOwner->m_pClient->m_VisualTree->HitTestElement(m_pOwner->m_pClient->GetViewMatrix(), LDraw::PointD(point.X, point.Y));

	if (pPElement == NULL)
	{
		pPElement = m_pOwner->m_pClient->m_VisualTree;///m_pSVGElement;
	}

	if (pPElement)
	{
		Event* evt = new Event;
		evt->initEvent(OLESTR("DragOver"), true, true);

		EventTargetImpl* eventTarget = dynamic_cast<EventTargetImpl*>(pPElement);
		if (eventTarget)
		{
			bool doDefault = eventTarget->dispatchEvent(evt);
		}
	}
#endif

	return S_OK;
}

STDMETHODIMP OleDropTarget::DragLeave()
{
	return S_OK;
}

STDMETHODIMP OleDropTarget::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	return S_OK;
}

#endif	// _WINDOWS

HwndSource::HwndSource()
{
	m_locked = false;

	//m_bInvalidated = false;

	m_depthBuffer = NULL;
	m_stencilBuffer = NULL;

	m_pOwnerScreen = NULL;

//	m_pClient = NULL;
	m_pClient = NULL;

#if WIN32

	m_hWnd = NULL;

	m_lpBmi = NULL;
	m_hBitmap = NULL;
	m_bmBits = NULL;

	m_lpBmi = (MSWindows::BITMAPINFOHEADER*)new uint8[sizeof(MSWindows::BITMAPV4HEADER) + sizeof(RGBQUAD)*256];
	std::memset(m_lpBmi, 0, sizeof(MSWindows::BITMAPV4HEADER));
	m_lpBmi->biSize = sizeof(MSWindows::BITMAPV4HEADER);
	m_lpBmi->biPlanes = 1;
	m_lpBmi->biCompression = BI_RGB;

	if (false)
	{
		MSWindows::RGBQUAD* quads = (MSWindows::RGBQUAD*)((uint8*)m_lpBmi + m_lpBmi->biSize);

		{
			for (int i = 0; i < 256; i++)
			{
				quads[i].rgbRed = 0;
				quads[i].rgbGreen = 0;
				quads[i].rgbBlue = 0;
			}
		}

		/*
		for (int i = 0; i < 256; i++)
		{
			quads[i].rgbRed = rand() * 255 / RAND_MAX;
			quads[i].rgbGreen = rand() * 255 / RAND_MAX;
			quads[i].rgbBlue = rand() * 255 / RAND_MAX;
		}
		*/
		{
			int i = 0;

			for (int r = 0; r < 6; r++)
			{
				for (int g = 0; g < 6; g++)
				{
					for (int b = 0; b < 6; b++)
					{
						quads[i].rgbRed = r * 255 / 5;
						quads[i].rgbGreen = g * 255 / 5;
						quads[i].rgbBlue = b * 255 / 5;

						i++;
					}
				}
			}
		}
	}

	m_pDropTarget = NULL;
#if 0
	m_pDropTarget = new OleDropTarget;
	m_pDropTarget->AddRef();
	m_pDropTarget->m_pOwner = this;
#endif

#elif AMIGA

	m_hWnd = NULL;

	//m_layerInfo = NULL;

	m_WindowUserData = NULL;

	m_pBitmap = NULL;

	m_pGraphicsRP = NULL;

	m_areainfo = NULL;
	m_tmpras = NULL;

#elif __APPLE__

	m_hWnd = NULL;
 
#endif

#if WIN32
;//	m_hCursor = NULL;
#elif AMIGA
	m_pPointer = NULL;
#endif

//	m_pContent = NULL;

	m_bAlpha = false;
//	m_bInvalidated = false;
//		m_pTitlebarElement = NULL;
//		m_pStatusElement = NULL;
//		m_pBorderElement = NULL;

#if 0
	m_pIOleIPActiveObject = NULL;
	m_hwndActiveObject = NULL;

	m_fHide = FALSE;
#endif

#if 0
	m_menuBar = NULL;
#endif
#if 0//_WINDOWS
	m_pMenuItem = NULL;
#endif

#if AMIGA
	m_pMenu = NULL;
#endif

#ifdef WINTAB
//TABLET: Graphics Tablet
	t_hTablet = NULL;		// Tablet context handle, required.
	t_prsNew = 0;
	t_curNew = 0;
	/*
	t_ortNew.orAzimuth = 0;		// 0 = north
	t_ortNew.orAltitude = 900;	// 900 = vertical
	t_ortNew.orTwist = 0;
	*/
	m_pntMouseLoc.X = 0;	//JCB initialise to zero
	m_pntMouseLoc.Y = 0;

	/*
	//EXAMPLE: extra tablet adjustments, used for this example,
	//	they may be useful in some other applications
	t_bTiltSupport = TRUE;	// Table. Is tilt supported
	t_dblAltAdjust = 1;		// Tablet Altitude zero adjust
	t_dblAltFactor = 1;		// Tablet Altitude factor
	t_dblAziFactor = 1;		// Table Azimuth factor
	*/
#endif // WINTAB

#if 0
	m_pClient = new WindowBase2;
//	m_pClient->m_pFrame = this;
	m_pClient->m_pSite = this;
#endif

	if (g_resources == NULL)
	{
		g_resources = new LDraw::GraphicsO::Resources;
	}

	if (g_bufferData == NULL)
	{
		g_bufferData = new LDraw::BufferData;
	}

	m_pGraphicsO = new LDraw::GraphicsO(g_resources);
	m_pGraphicsO->m_bufferData = g_bufferData;

//	m_crit.Init();
}

HwndSource::~HwndSource()
{
	delete[] m_depthBuffer;

#if 0//WIN32
	if (m_pDropTarget)
	{
		m_pDropTarget->Release();
		m_pDropTarget = NULL;
	}
#endif

#ifdef WINTAB
	ASSERT(t_hTablet == NULL);	// OnDestroy must have been called
#endif // WINTAB
}

void HwndSource::SetAlpha(bool bAlpha)
{
	m_bAlpha = bAlpha;
}

void HwndSource::AddStylusPlugin(IStylusPlugin* plugin)
{
	m_stylusPlugins.insert(m_stylusPlugins.end(), plugin);
}

PlatformWindow HwndSource::GetHwnd()
{
	return m_hWnd;
}

/*
void HwndSource::SetContent(UIElement* pVisual)
{
	m_pClient->put_VisualTree(pVisual);
}
*/

void SetupPixelFormat(HDC hDC)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),   // size of structure.
		1,                               // always 1.
		PFD_DRAW_TO_WINDOW |             // support window
		PFD_SUPPORT_OPENGL |             // support OpenGl
		PFD_DOUBLEBUFFER,                // support double buffering
		PFD_TYPE_RGBA,                   // support RGBA
		24,                              // bit color mode
		0, 0, 0, 0, 0, 0,                // ignore color bits
		0,                               // no alpha buffer
		0,                               // ignore shift bit
		0,                               // no accumulation buffer
		0, 0, 0, 0,                      // ignore accumulation bits.
		16,                              // number of depth buffer bits.
		0,                               // number of stencil buffer bits.
		0,                               // 0 means no auxiliary buffer
		PFD_MAIN_PLANE,                  // The main drawing plane
		0,                               // this is reserved
		0, 0, 0                       // layer masks ignored.
	};
	
	int nPixelFormat;
	// This chooses the best pixel format and returns index.
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);

	// This set pixel format to device context.
	SetPixelFormat(hDC, nPixelFormat, &pfd);
}

double pixelsPerInch;

void HwndSource::Show(LDraw::RectI* location, PresentationSource* hParent)
{
	HDC hDC = GetDC(NULL);
	pixelsPerInch = (double)GetDeviceCaps(hDC, LOGPIXELSX);
	ReleaseDC(NULL, hDC);

	pixelsPerInch = 96;	// TODO remove

	//std::printf("HwndSource::Show()\n");
//	sysstring titlebarText = GetTitlebarText();
	if (m_hWnd == NULL)
	{
	//	CRect rect(m_computedLeft, m_computedTop, m_computedLeft+m_computedSize.Width, m_computedTop+m_computedSize.Height);

		PlatformWindow hWndParent = NULL;
		if (hParent)
		{
			hWndParent = dynamic_cast<HwndSource*>(hParent)->GetHwnd();
		}

#if 0	
		if (m_pClient->GetRParent())
		{
			HwndSource* pHwndSite = dynamic_cast<HwndSource*>(m_pClient->GetRParent()->get_OwnerWindow()->m_pSite);
			if (pHwndSite)
			{
				hWndParent = pHwndSite->GetHwnd();

				// If the parent window isn't created yet, we delay creating this window also
				if (hWndParent == NULL)
					return;
			}
		}
#endif

		UIElement* clientContent = m_pClient->GetVisualTree();
		clientContent->m_windowToElementTransform = LDraw::Matrix3f::GetIdentity();

#if 0
		clientContent->Measure(LDraw::SizeD(0, 0));

		LDraw::SizeD desiredSize = clientContent->get_DesiredSize();
		LDraw::SizeD size(ceil(desiredSize.Width), ceil(desiredSize.Height));
		clientContent->Arrange(LDraw::RectD(LDraw::PointD(0, 0), size));
#endif
		LDraw::SizeD desiredSize = m_pClient->Measure(LDraw::SizeD(0, 0));
		m_minSize = LDraw::SizeI(ceil(desiredSize.Width), ceil(desiredSize.Height));
		LDraw::SizeD size(ceil(desiredSize.Width), ceil(desiredSize.Height));
		m_pClient->Arrange(size);

#if WIN32
		Visual* p = m_pClient->GetVisualTree();
		if (p)
		{
			if (p->m_expandedBBox.Width != p->m_computedSize.Width || p->m_expandedBBox.Height != p->m_computedSize.Height)
			{
			//	m_bAlpha = true;
			}
		}

	//	CreateRegions();

	//	m_pClient->m_bRedraw = true;
	//	m_redrawList = m_pClient;

		ASSERT((hWndParent == NULL) || MSWindows::IsWindow(hWndParent));

		StringW* windowName = m_pClient->GetTitle();
#if 0
//		FrameWindow* pFrame = dynamic_cast<FrameWindow*>(static_cast<WindowBase*>(m_pClient)->get_VisualTree());
		Window* pFrame = dynamic_cast<Window*>(m_pClient->GetVisualTree());
		if (pFrame)
		{
			windowName = dynamic_cast<StringW*>(pFrame->get_Title());
		}
#endif

		uint32 windowStyle = WS_CLIPCHILDREN;

		windowStyle = m_pClient->GetWindowStyle(windowStyle);

		/*
		// TODO, windowStyles should be customizable
		windowStyle |= WS_OVERLAPPED;
		windowStyle |= WS_CAPTION;
		windowStyle |= WS_SYSMENU;
		windowStyle |= WS_THICKFRAME;
		windowStyle |= WS_MINIMIZEBOX;
		windowStyle |= WS_MAXIMIZEBOX;
		*/

		uint32 dwExStyle = 0;

		int opacity = m_pClient->GetVisualTree()->get_Opacity()*255;
		if (opacity < 0) opacity = 0;
		else if (opacity > 255) opacity = 255;
		if (opacity < 255)
		{
			dwExStyle |= WS_EX_LAYERED;
		//	m_layered = true;
		}

		float scale = pixelsPerInch / 96;
		LDraw::RectD expandedBBox = m_pClient->GetVisualTree()->m_expandedBBox * scale;

		int x = 0;
		int y = 0;

		if (location)
		{
			x = location->X;
			y = location->Y;
		}

		GetD3DDevice9();	// Make sure it's created

		if (g_MyEvent == NULL)
		{
			g_MyEvent = MSWindows::CreateEventW(NULL, false, false, NULL);
			MSWindows::CreateThread(NULL, NULL, RenderThread, NULL , 0, &renderThreadId);
		}

		if (true)
		{
			m_d3dDevice9 = g_d3dDevice9;

		//	LDraw::RectI rect;
		//	GetWindowRect(&rect);

			m_d3dpp9 = g_d3dpp9;
			m_d3dpp9.hDeviceWindow = NULL;
#if 0	// Created in OnSize
			m_d3dpp9.BackBufferWidth = rect.Width;
			m_d3dpp9.BackBufferHeight = rect.Height;

			D3D_CreateAdditionalSwapChain(g_d3dDevice9, &m_d3dpp9, &m_d3dSwapChain9);
			if (m_d3dSwapChain9 == NULL)
			{
				throw std::exception("Couldn't create Direct3D 9 SwapChain");
			}
#endif
			/*
			m_d3dDevice = D3D_CreateDevice(m_hWnd, &m_d3dpp);
			if (m_d3dDevice == NULL)
			{
				throw std::exception("Couldn't create Direct3D device");
			}
			*/

			LDraw::Direct3D9_I* device = new LDraw::Direct3D9_I(m_d3dDevice9);
			m_pGraphicsO->m_device = device;

		//	LDraw::Graphics3DImmediate* p3D = new LDraw::Graphics3DImmediate(new LDraw::GLState, new LDraw::ClientState, m_pGraphicsO/*(IDirect3DDevice9*)m_d3dDevice*/);
		//	p3D->m_pG->m_pGraphics = m_pGraphicsO;
		//	m_pGraphics3D = p3D;
		}

		LDraw::Graphics3D* p3D = new LDraw::Graphics3D(m_pGraphicsO);
		m_pGraphics3D = p3D;

		HWND hWnd;
		hWnd = MSWindows::CreateWindowExW(dwExStyle, L"lxui_window_class", windowName? windowName->c_str(): NULL, windowStyle,
			x + expandedBBox.X, y + expandedBBox.Y, expandedBBox.Width, expandedBBox.Height,
//			hWndParent, NULL, _Module.m_hInstance, (CLXUIWindowBase*)this);
			hWndParent, NULL, _Module.m_hInstance, (HwndSource*)this);

		if (m_hWnd)
		{
			if (false)
			{
				m_hDC = GetDC(m_hWnd);				// This gets the device context for our window
				SetupPixelFormat(m_hDC);			// Call the pixel format function

				m_hRC = wglCreateContext(m_hDC);	// Creates the rendering context
				if (m_hRC == NULL)
				{
					throw std::exception("Couldn't create OpenGL context");
				}

				LDraw::OpenGL_I* device = new LDraw::OpenGL_I(m_hDC, m_hRC);
				m_pGraphicsO->m_device = device;
			}
			else if (false)
			{
				m_d3dDevice9 = g_d3dDevice9;

				LDraw::RectI rect;
				GetPhysicalWindowRect(&rect);

				m_d3dpp9 = g_d3dpp9;
			//	m_d3dpp9.hDeviceWindow = m_hWnd;
#if 0	// Created in OnSize
				m_d3dpp9.BackBufferWidth = rect.Width;
				m_d3dpp9.BackBufferHeight = rect.Height;

				D3D_CreateAdditionalSwapChain(g_d3dDevice9, &m_d3dpp9, &m_d3dSwapChain9);
				if (m_d3dSwapChain9 == NULL)
				{
					throw std::exception("Couldn't create Direct3D 9 SwapChain");
				}
#endif
				/*
				m_d3dDevice = D3D_CreateDevice(m_hWnd, &m_d3dpp);
				if (m_d3dDevice == NULL)
				{
					throw std::exception("Couldn't create Direct3D device");
				}
				*/

				LDraw::Direct3D9_I* device = new LDraw::Direct3D9_I(m_d3dDevice9);
				m_pGraphicsO->m_device = device;

			//	LDraw::Graphics3DImmediate* p3D = new LDraw::Graphics3DImmediate(new LDraw::GLState, new LDraw::ClientState, m_pGraphicsO/*(IDirect3DDevice9*)m_d3dDevice*/);
			//	p3D->m_pG->m_pGraphics = m_pGraphicsO;
			//	m_pGraphics3D = p3D;
			}
			else if (false)
			{
				LDraw::Direct3D10_I* device = LDraw::Direct3D10_I::Create(m_hWnd);
				device->CreateRenderTargetView();
				m_pGraphicsO->m_device = device;
			}

		//	LDraw::Graphics3D* p3D = new LDraw::Graphics3D(m_pGraphicsO);
		//	m_pGraphics3D = p3D;

			if (m_pClient->GetWindowAnimate())
			{
				AnimateWindow(m_hWnd, 200, AW_ACTIVATE | AW_BLEND);
			}
			else
			{
				MSWindows::ShowWindow(m_hWnd, SW_SHOW/*nCmdShow*/);
			}

			if (true)
			{
				InitPresent();
			}
		}
		else
		{
			// TODO, mark this as already failed, so we don't pop it up all time
			MessageBoxA(NULL, "Failed to create window", "", MB_OK);
			THROW(-1);
		}

#elif __APPLE__

		::Rect wRect;
		wRect.left = 20;
		wRect.top = 30;
		wRect.right = (int)m_pClient->m_computedSize.Width;
		wRect.bottom = (int)m_pClient->m_computedSize.Height;

		CreateNewWindow(kPlainWindowClass, kWindowNoAttributes, &wRect, &m_hWnd);
		if (m_hWnd == NULL)
		{
			TRACE("Failed to create window");
			THROW(-1);
		}

		{
			EventTypeSpec spec[] =
			{
				{kEventClassMouse, kEventMouseDown},
				{kEventClassMouse, kEventMouseUp},
				{kEventClassMouse, kEventMouseMoved},
				{kEventClassMouse, kEventMouseDragged},
				{kEventClassWindow, kEventWindowActivated},
				{kEventClassWindow, kEventWindowDeactivated},
			};
			OSStatus status = InstallWindowEventHandler(m_hWnd, NewEventHandlerUPP(EventHandler), 6, spec, (HwndSource*)this, NULL);
			ASSERT(status == noErr);
		}

#if 0
		HwndSource* pThis = this;
		SetWindowProperty(m_hWnd, 0/*creator*/, 0/*tag*/, sizeof(pThis), &pThis);
#endif
		m_invalidRegion.From(LDraw::RectI(0, 0, wRect.right-wRect.left, wRect.bottom-wRect.top));

		m_pClient->m_bRedraw = true;
		m_redrawList = m_pClient;

		ShowWindow(m_hWnd);

		Render();

#elif AMIGA

		m_windowRect.X = 16;
		m_windowRect.Y = 16;
		m_windowRect.Width = (int)m_pClient->m_computedSize.Width;
		m_windowRect.Height = (int)m_pClient->m_computedSize.Height;

		m_areainfo = new AreaInfo;
		m_tmpras = new TmpRas;

		InitArea(m_areainfo, new uint8[(800+1)*5], 800+1);
		InitTmpRas(m_tmpras, (uint8*)execAllocMem(SysBase, 20000, MEMF_CHIP), 20000);

		m_hWnd = OpenWindowTags(NULL,
			(WA_Left), m_windowRect.X,
			(WA_Top), m_windowRect.Y,
			(WA_Width), m_windowRect.Width,
			(WA_Height), m_windowRect.Height,
			(WA_Flags), WFLG_REPORTMOUSE |
							WFLG_BORDERLESS |
							WFLG_ACTIVATE |
							WFLG_SIMPLE_REFRESH/* |
							WFLG_NOCAREREFRESH*/,
			(WA_IDCMP), 0,	// Set later
			(WA_MinWidth), 64,
			(WA_MinHeight), 24,
			(WA_MaxWidth), ~0,
			(WA_MaxHeight), ~0,
			(TAG_DONE));

		if (m_hWnd)
		{
			m_WindowUserData = new WindowUserData;

			m_hWnd->RPort->AreaInfo = m_areainfo;
			m_hWnd->RPort->TmpRas = m_tmpras;

			m_pGraphicsRP = new LDraw::GraphicsRP(GetHwnd()->WScreen->ViewPort.ColorMap, GetHwnd()->RPort);

			m_hWnd->UserPort = pUserPort;

#if 0
			m_invalidRect = LDraw::RectI(0, 0, m_windowRect.Width, m_windowRect.Height);
#else
			m_invalidRegion = new LDraw::Region(LDraw::RectI(0, 0, m_windowRect.Width, m_windowRect.Height));
#endif
			CreateRegions();

			m_pClient->m_bRedraw = true;
			m_redrawList = m_pClient;

	// Apparently these aren't automatically done after opening window
			if (false)
			{
				SetBitmapSize(m_windowRect.Width, m_windowRect.Height);
			}

			Render();

			m_WindowUserData->pHandler = staticIntuiMsgHandler;
		//	m_WindowUserData.pData = reinterpret_cast<void*>(static_cast<HwndSource*>(this));
			m_WindowUserData->pData = this;//(static_cast<HwndSource*>(this));

			m_hWnd->UserData = reinterpret_cast<signed char*>(m_WindowUserData);

			AddPersistentLiveRoot(&m_WindowUserData->pData);

			ModifyIDCMP(m_hWnd,	IDCMP_REFRESHWINDOW |
										IDCMP_MOUSEMOVE |
										IDCMP_MOUSEBUTTONS |
										IDCMP_RAWKEY |
										//IDCMP_VANILLAKEY |
										IDCMP_ACTIVEWINDOW |
										IDCMP_INACTIVEWINDOW |
										IDCMP_CHANGEWINDOW/* |
										IDCMP_NEWSIZE |
										IDCMP_CLOSEWINDOW*/);
		}
#endif
	}
	else
	{
#if WIN32
		MSWindows::ShowWindow(m_hWnd, SW_SHOW);
		MSWindows::BringWindowToTop(m_hWnd);
#elif AMIGA
		intuiWindowToFront(m_hWnd);
#endif
	}

	std::printf("...done...HwndSource::Show()\n");
}

bool HwndSource::IsDoubleBuffered() const
{
#if AMIGA
	return false;
#else
	return true;
#endif
}

void HwndSource::CreateRegions()
{
#if 0

//	Graphics* graphics = new Graphics(m_pGraphicsO);
	Graphics* graphics = new Graphics(new LDraw::GraphicsO);

	if (m_pClient == NULL)
	{
		MessageBeep(-1);
		ASSERT(0);
	}

	m_pClient->get_VisualTree()->CreateOpaqueRegion(graphics);
	m_pClient->get_VisualTree()->m_visibleRegion = new LDraw::Region(LDraw::RectI(0, 0, m_pClient->get_VisualTree()->m_expandedBBox.Width, m_pClient->get_VisualTree()->m_expandedBBox.Height));	// infinite //m_pClient->OnGetRegion(graphics->GetTransform());
	m_pClient->get_VisualTree()->m_visibleWithChildrenRegion = new LDraw::Region(LDraw::RectI(0, 0, m_pClient->get_VisualTree()->m_expandedBBox.Width, m_pClient->get_VisualTree()->m_expandedBBox.Height));	// infinite //m_pClient->OnGetRegion(graphics->GetTransform());
	m_pClient->get_VisualTree()->m_bRenderValid = false;
	m_pClient->get_VisualTree()->CreateLayerStuff(graphics);
#else

	m_pClient->GetVisualTree()->m_bRenderValid = false;
	m_pClient->GetVisualTree()->m_bDrawsOutsideOpaqueRegion = false;

#endif
}

void HwndSource::Close()
{
	if (m_hWnd)
	{
		// Fake a mouseleave
		if (m_bInsideWindow)
		{
			OnMouseLeave();
		}

	//	MessageBeep(-1);
#if 0	// TODO, have this

		m_pClient->m_pHitElement = NULL;
		m_pClient->m_pElementCapture = NULL;
		m_pClient->m_pElementHover = NULL;
#endif

		DestroyWindow();
		ASSERT(m_hWnd == NULL);
	}

	if (m_pClient)
	{
		Redraw();	// Flush (This must be done)

		m_pClient->Close();
		m_pClient = NULL;
	}

	g_nWindows--;
}

#if __APPLE__

BOOL HwndSource::DestroyWindow()
{
	ASSERT(m_hWnd);

	printf("DestroyWindow\n");
	fflush(stdout);

	if (m_hWnd == NULL)
		return FALSE;

	OnDestroy();
	DisposeWindow(m_hWnd);
	OnDestroyed();

	return TRUE;
}

#endif

#if AMIGA

bool HwndSource::DestroyWindow()
{
	ASSERT(m_hWnd);

	if (m_hWnd == NULL)
		return FALSE;

	CleanupWindow(m_hWnd);

	OnDestroy();

	intuiCloseWindow(m_hWnd);

	OnDestroyed();

	return TRUE;
}

#endif

void HwndSource::OnClose()
{
	Close();
}

LRESULT HwndSource::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	OnDestroy();
	return 0;
}

void HwndSource::OnDestroy()
{
#if 0//WIN32
	RevokeDragDrop(m_hWnd);
#endif

#ifdef WINTAB
	if (t_hTablet)
	{
		_WTClose((MSWindows::HCTX)t_hTablet);
		t_hTablet = NULL;
	}
#endif // WINTAB

#if AMIGA
	if (m_pBitmap)
	{
		p96FreeBitMap(m_pBitmap);
		m_pBitmap = NULL;
	}
#endif
}

void HwndSource::OnDestroyed()
{
	m_hWnd = NULL;
}

#if AMIGA
extern MsgPort* pUserPort;
#endif

#if 0
void HwndSource::InvalidateRect(const LDraw::RectD& rect)
{
	if (rect.IsEmptyArea())
		return;

	LDraw::RectD xrect = rect;
	xrect.Offset(-m_pClient->m_expandedBBox.X, -m_pClient->m_expandedBBox.Y);

	if (!m_bInvalidated)
	{
		m_bInvalidated = true;
		pLayoutManager->m_windowList.push_back(this);

#if WIN32
	//	if (GetCurrentThreadId() != m_threadId)
		{
			// Post a message to the thread that created this window
			PostThreadMessage(m_threadId, WM_USER+100, 0, 0);
		//	SetEvent(g_hEvent);
		}
#elif AMIGA
		Signal(m_pTask, 1<<pUserPort->mp_SigBit);
#endif
	}

	/*
	if (m_invalidRect.IsEmptyArea())
		m_invalidRect = xrect;
	else
		LDraw::RectD::Union(m_invalidRect, m_invalidRect, xrect);
		*/
	m_invalidRegion.Union(xrect);

#if 0
	if (m_lockUpdate == 0)
	{
		if (!m_invalidRect.IsEmptyArea())
		{
			Render(m_invalidRect);
			m_invalidRect = LDraw::RectD();	// empty
		}
	}
#endif
}
#endif

#if 0//AMIGA

void HwndSource::InvalidateRect(LDraw::RectI rect)
{
	if (rect.IsEmptyArea())
		return;

	if (m_hWnd == NULL)
		return;

	m_crit.Lock();

	if (!m_bInvalidated)
	{
		m_bInvalidated = true;
		//pLayoutManager->m_windowList.push_back(this);

		m_pNextWindow = pLayoutManager->m_windowList;
		pLayoutManager->m_windowList = this;

#if WIN32
	//	if (GetCurrentThreadId() != m_threadId)
		{
			// Post a message to the thread that created this window
			PostThreadMessageA(m_threadId, WM_USER+100, 0, 0);

		//	FlushToScreen(NULL);
		}
#elif AMIGA
	//	printf("InvalidateRegion\n");
		Signal(m_pTask, 1<<pUserPort->mp_SigBit);
#endif
	}

	//else
	//		FlushToScreen(NULL);

	LDraw::RectI windowrect;
	GetPhysicalWindowRect(&windowrect);

#if USE_CLIPPING
	if (m_invalidRect.IsEmptyArea())
		m_invalidRect = rect;
	else
		LDraw::RectI::Union(m_invalidRect, m_invalidRect, rect);

	LDraw::RectI::Intersect(m_invalidRect, m_invalidRect, LDraw::RectI(0, 0, windowrect.Width, windowrect.Height));
#endif

	m_crit.Unlock();

	//Render();
}

#else

void HwndSource::InvalidateRegion(LDraw::Region* pRgn)
{
//	TRACE("Union...");

	ASSERT(this);

	if (true)
	{
//	m_crit.Lock();
//	pLayoutManager->m_renderCritSec.Lock();

	if (!m_bInvalidated)
	{
		m_renderTargetUpdated = false;

//		pLayoutManager->m_windowList.push_back(this);
#if 0	// ??
		ASSERT(pLayoutManager->m_windowList == NULL);
#endif
		m_bInvalidated = true;
		m_pNextWindow = pLayoutManager->m_windowList;
		pLayoutManager->m_windowList = this;

#if WIN32
	//	if (GetCurrentThreadId() != m_threadId)
		{
			if (g_PresentEvent)
			{
				SetEvent(g_MyEvent);
			}
			else
			{
				// Post a message to the thread that created this window
				int success = PostThreadMessageW(m_threadId, WM_USER+100, 0, 0);
			//	int success = PostThreadMessageW(renderThreadId, WM_USER+100, 0, 0);

				VERIFY(success);
			}

		//	FlushToScreen(NULL);
		}
#elif AMIGA
	//	printf("InvalidateRegion\n");
		Signal(m_pTask, 1<<pUserPort->mp_SigBit);
#endif
	}
	else
	{
#if 0	// TODO, have this
		ASSERT(m_renderTargetUpdated == false);
#endif
	}

//	pLayoutManager->m_renderCritSec.Unlock();
//	m_crit.Unlock();

		return;
	}

#if 0
	//printf("HwndSource::InvalidateRegion\n");

	if (pRgn == NULL)
		return;

	if (pRgn->IsEmpty())
		return;

	if (m_hWnd == NULL)
		return;

	/*
	if (!m_crit.Try())
	{
	//	MessageBeep(-1);
		return;
	}
	*/
	m_crit.Lock();

	if (!m_bInvalidated)
	{
		m_bInvalidated = true;
//		pLayoutManager->m_windowList.push_back(this);
		m_pNextWindow = pLayoutManager->m_windowList;
		pLayoutManager->m_windowList = this;

#if WIN32
	//	if (GetCurrentThreadId() != m_threadId)
		{
			// Post a message to the thread that created this window
			PostThreadMessageA(m_threadId, WM_USER+100, 0, 0);

		//	FlushToScreen(NULL);
		}
#elif AMIGA
	//	printf("InvalidateRegion\n");
		Signal(m_pTask, 1<<pUserPort->mp_SigBit);
#endif
	}

	//Render();

	//else
	//		FlushToScreen(NULL);

	LDraw::RectI windowrect = m_windowRect;
//	GetPhysicalWindowRect(&windowrect);

	//
//	m_invalidRegion = new LDraw::Region(LDraw::RectI(0, 0, windowrect.Width, windowrect.Height));

#if USE_CLIPPING
	if (m_invalidRegion->IsEmpty())
	{
		m_invalidRegion = pRgn;
	}
	else
	{
		if (m_invalidRegion->m_refcount > 1)
			m_invalidRegion = m_invalidRegion->GetUnion(pRgn);
		else
			m_invalidRegion->Union(pRgn);
	}

//	m_invalidRegion = m_invalidRegion->GetUnion(pRgn);
	//m_invalidRegion->Union(pRgn);
	if (m_invalidRegion->m_refcount > 1) m_invalidRegion = m_invalidRegion->Clone();
	m_invalidRegion->Intersect(LDraw::RectI(0, 0, m_d3dpp9.BackBufferWidth/*windowrect.Width*/, m_d3dpp9.BackBufferHeight/*windowrect.Height*/));
#endif

//	const LDraw::RegionRect* rc = m_invalidRegion.GetFirstRect();

	m_crit.Unlock();

	//printf("done\n\n");
#endif
}
#endif

void HwndSource::SetBitmapSize(int width, int height)
{
	if (m_depthBuffer)
	{
		delete[] m_depthBuffer;
	}

	if (m_stencilBuffer)
	{
		delete[] m_stencilBuffer;
	}

#if WIN32
	if (m_hBitmap)
	{
		DeleteObject((void*)m_hBitmap);
		m_hBitmap = NULL;
	}

	m_lpBmi->biWidth = width;
	m_lpBmi->biHeight = height;

	if (false)
	{
		m_lpBmi->biBitCount = 8;
	}
	else
	{
		m_lpBmi->biBitCount = 32;
	}

	if (width > 0 && height > 0)
	{
#if 0
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = true;	// Inheritable by child processes
		HANDLE hFileMap = CreateFileMapping((HANDLE)0xFFFFFFFF, &sa, PAGE_READWRITE, 0, width*4*height, "lxui_window_buffer");
		ASSERT(hFileMap != INVALID_HANDLE_VALUE);
		m_hBitmap = ::CreateDIBSection(NULL, (BITMAPINFO*)m_lpBmi, DIB_RGB_COLORS, (void**)&m_bmBits, hFileMap, 0);

#else
		m_hBitmap = MSWindows::CreateDIBSection(NULL, (MSWindows::BITMAPINFO*)m_lpBmi, DIB_RGB_COLORS, (void**)&m_bmBits, NULL, 0);

		/*
		ASSERT((uint8*)m_hBitmap < heap->m_data || (uint8*)m_hBitmap >= heap->m_data + heap->m_size*2);

		if ((uint8*)m_hBitmap >= heap->m_data && (uint8*)m_hBitmap < heap->m_data + heap->m_size*2)		// within gc heap
		{
			MessageBoxA(NULL, "bitmap inside gc heap", "", MB_OK);
			THROW(-1);
		}
		*/

#endif
	}

#elif AMIGA

	printf("SetBitmapSize(%d,%d)", width, height);
	fflush(stdout);

	if (m_pBitmap)
	{
		p96FreeBitMap(m_pBitmap);
		m_pBitmap = NULL;
	}

	if (width > 0 && height > 0)
	{
		m_pBitmap = p96AllocBitMap(width, height, 32, BMF_USERPRIVATE, NULL, RGBFB_R8G8B8A8);
	}

#endif

#if 0
	if (true)	// TODO, don't have this here
	{
		m_computedWidth = width;
		m_computedHeight = height;

		if (get_VisualTree())
		{
			m_VisualTree->Measure(LDraw::SizeD(m_computedWidth, m_computedHeight));
			m_VisualTree->Arrange(LDraw::SizeD(m_computedWidth, m_computedHeight));
		}
	}
#endif

	m_depthBuffer = new float[width*height];
	m_stencilBuffer = new uint8[width*height];

	std::printf("done\n");
}

void HwndSource::OnActivate(bool bActive)
{
	if (!m_locked && g_uiLocked == 0)
	{
		m_pClient->OnActivate(bActive);
	}
}

#if WIN32

bool HwndSource::IsWindowEnabled()
{
	ASSERT(MSWindows::IsWindow(m_hWnd));
	return MSWindows::IsWindowEnabled(m_hWnd) != 0;
}

HWND HwndSource::GetTopLevelParent() const
{
	ASSERT(MSWindows::IsWindow(m_hWnd));

	HWND hWndParent = m_hWnd;
	HWND hWndTmp;
	while((hWndTmp = MSWindows::GetParent(hWndParent)) != NULL)
		hWndParent = hWndTmp;

	return hWndParent;
}

#endif

/*
void HwndSource::Render()
{
	Render(LDraw::RectD(0, 0, m_pClient->m_expandedBBox.Width, m_pClient->m_expandedBBox.Height));
}
*/
#if 0
void PresentationContentSource::OnChildDesiredSizeChanged(UIElement* child)
{
	ASSERT(0);
#if 0
//	Control::OnChildDesiredSizeChanged(child);
	dynamic_cast<IWindowHost*>(m_pSite)->SetWindowRect(0, 0, child->get_DesiredSize().Width, child->get_DesiredSize().Height);
#endif
}

void WindowBase2::SetPos(double X, double Y)
{
	MessageBeep(-1);
//	::SetWindowPos(dynamic_cast<WindowHost*>(m_pFrame)->m_hWnd, NULL, X + m_expandedBBox.X, Y + m_expandedBBox.Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}
#endif

/*
unsigned int DitherPattern[8][8] =
{
0,  32,   8,  40,   2,  34,  10,  42,
 16,  48,  24,  58,  18,  50,  26,  58,
  4,  36,  12,  44,   6,  38,  14,  46,
 20,  52,  28,  60,  22,  54,  30,  62,
  1,  33,   9,  41,   3,  35,  11,  43,
 17,  49,  25,  57,  19,  51,  27,  59,
  5,  37,  13,  45,   7,  39,  15,  47,
 21,  53,  29,  61,  23,  55,  31,  63,
};
*/

unsigned int DitherPattern[16][16] =
{
   0, 192,  48, 240,  12, 204,  60, 252,   3, 195,  51, 243,  15, 207,  63, 255,
 128,  64, 176, 112, 140,  76, 188, 124, 131,  67, 179, 115, 143,  79, 191, 127,
  32, 224,  16, 208,  44, 236,  28, 220,  35, 227,  19, 211,  47, 239,  31, 223,
 160,  96, 144,  80, 172, 108, 156,  92, 163,  99, 147,  83, 175, 111, 159,  95,
   8, 200,  56, 248,   4, 196,  52, 244,  11, 203,  59, 251,   7, 199,  55, 247,
 136,  72, 184, 120, 132,  68, 180, 116, 139,  75, 187, 123, 135,  71, 183, 119,
  40, 232,  24, 216,  36, 228,  20, 212,  43, 235,  27, 219,  39, 231,  23, 215,
 168, 104, 152,  88, 164, 100, 148,  84, 171, 107, 155,  91, 167, 103, 151,  87,
   2, 194,  50, 242,  14, 206,  62, 254,   1, 193,  49, 241,  13, 205,  61, 253,
 130,  66, 178, 114, 142,  78, 190, 126, 129,  65, 177, 113, 141,  77, 189, 125,
  34, 226,  18, 210,  46, 238,  30, 222,  33, 225,  17, 209,  45, 237,  29, 221,
 162,  98, 146,  82, 174, 110, 158,  94, 161,  97, 145,  81, 173, 109, 157,  93,
  10, 202,  58, 250,   6, 198,  54, 246,   9, 201,  57, 249,   5, 197,  53, 245,
 138,  74, 186, 122, 134,  70, 182, 118, 137,  73, 185, 121, 133,  69, 181, 117,
  42, 234,  26, 218,  38, 230,  22, 214,  41, 233,  25, 217,  37, 229,  21, 213,
 170, 106, 154,  90, 166, 102, 150,  86, 169, 105, 153,  89, 165, 101, 149,  85,
 };

int dithervalue(int x, int y, int size)
{
	int d = 0;
	while (size-- > 0)
	{
		d = (d<<1 | (x&1 ^ y&1))<<1 | y&1;
		x >>= 1;
		y >>= 1;
	}

	return d;
}

void printdither(int size, int range)
{
	int l = (1<<size);
	int i;

	range = range / (l*l);
	for (i = 0; i < l*l; i++)
	{
		/*
		if (i % l == 0)
		{
			TRACE("\n");
		}
		*/

		TRACE("%4d", dithervalue(i/l, i%l, size));
		TRACE(",");

		if ((i+1) % l == 0)
			TRACE("\n");
	}
}

#define DISPLAY_DITHER					1024
#define DISPLAY_GRAYSCALE				0
#define DISPLAY_RGB						256
#define DISPLAYMODE_BITS_MASK			0xFF

#define DISPLAYMODE_GRAYSCALE_1		1
#define DISPLAYMODE_GRAYSCALE_2		2
#define DISPLAYMODE_GRAYSCALE_3		3
#define DISPLAYMODE_GRAYSCALE_4		4
#define DISPLAYMODE_GRAYSCALE_5		5
#define DISPLAYMODE_GRAYSCALE_6		6
#define DISPLAYMODE_GRAYSCALE_7		7
#define DISPLAYMODE_GRAYSCALE_8		8

#define DISPLAYMODE_RGB_8				(1 | DISPLAY_RGB)
#define DISPLAYMODE_RGB_16				(2 | DISPLAY_RGB)
#define DISPLAYMODE_RGB_27				(3 | DISPLAY_RGB)
#define DISPLAYMODE_RGB_64				(4 | DISPLAY_RGB)
#define DISPLAYMODE_RGB_125			(5 | DISPLAY_RGB)
#define DISPLAYMODE_RGB_216			(6 | DISPLAY_RGB)
#define DISPLAYMODE_RGB_252			(7 | DISPLAY_RGB)
#define DISPLAYMODE_RGB_HAM6			(4 | 128 | DISPLAY_RGB)
#define DISPLAYMODE_RGB_HAM8			(6 | 128 | DISPLAY_RGB)
#define DISPLAYMODE_RGB_HICOLOR		(15 | DISPLAY_RGB)
#define DISPLAYMODE_RGB_TRUECOLOR	(24 | DISPLAY_RGB)

void HwndSource::UpdateHBITMAP()
{
	if (!m_hBitmapUpdated)
	{
		m_hBitmapUpdated = true;

		if (m_hBitmap == NULL)
		{
			m_lpBmi->biBitCount = 32;
			m_hBitmap = MSWindows::CreateDIBSection(NULL, (MSWindows::BITMAPINFO*)m_lpBmi, DIB_RGB_COLORS, (void**)&m_bmBits, NULL, 0);
		}

		if (m_hBitmap)
		{
			IDirect3DSurface9* pSurface = NULL;
			m_d3dDevice9->CreateOffscreenPlainSurface(m_d3dpp9.BackBufferWidth, m_d3dpp9.BackBufferHeight, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &pSurface, NULL);
			if (pSurface)
			{
				IDirect3DSurface9* pRenderTargetSurface;
				m_d3dSwapChain9->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pRenderTargetSurface);

				HRESULT hr = m_d3dDevice9->GetRenderTargetData(pRenderTargetSurface, pSurface);
				ASSERT(SUCCEEDED(hr));

				D3DLOCKED_RECT locked_rect;
				pSurface->LockRect(&locked_rect, NULL, D3DLOCK_READONLY);

				int width = m_d3dpp9.BackBufferWidth;
				int height = m_d3dpp9.BackBufferHeight;

				const uint32* src = (const uint32*)locked_rect.pBits;
				uint32* dst = (uint32*)m_bmBits;	// DIB rows are always aligned on 4 bytes

				int srcAlign = (locked_rect.Pitch - width*4)>>2;
				if (srcAlign == 0)
				{
					int size = width*height;

					while (size--)
					{
						*dst++ = *src++;
					}
				}
				else
				{
					for (int y = 0; y < height; y++)
					{
						for (int x = 0; x < width; x++)
						{
							*dst = *src;

							src++;
							dst++;
						}
						src += srcAlign;
					}
				}

				pSurface->UnlockRect();

			//	MSWindows::SetWindowLongW(m_hWnd, GWL_EXSTYLE, MSWindows::GetWindowLongW(GetHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
			//	MSWindows::SetLayeredWindowAttributes(m_hWnd, 0, opacity, LWA_ALPHA);

				pRenderTargetSurface->Release();
				pSurface->Release();
			}
		}
	}
}

uint32 HwndSource::GetStyle()
{
	return MSWindows::GetWindowLongA(m_hWnd, GWL_STYLE);
}

uint32 HwndSource::GetExStyle()
{
	return MSWindows::GetWindowLongA(m_hWnd, GWL_EXSTYLE);
}

uint32 HwndSource::ModifyStyle(uint32 mask, uint32 newStyle)
{
	uint32 oldStyle = MSWindows::GetWindowLongA(m_hWnd, GWL_STYLE);
	MSWindows::SetWindowLongA(m_hWnd, GWL_STYLE, (oldStyle & ~mask) | newStyle);
	return oldStyle;
}

uint32 HwndSource::ModifyExStyle(uint32 mask, uint32 newStyle)
{
	uint32 oldStyle = MSWindows::GetWindowLongA(m_hWnd, GWL_EXSTYLE);
	MSWindows::SetWindowLongA(m_hWnd, GWL_EXSTYLE, (oldStyle & ~mask) | newStyle);
	return oldStyle;
}

void HwndSource::FlushToScreen(LDraw::Region* pRgn)
{
	LDraw::Direct3D10_I* d3d10 = dynamic_cast<LDraw::Direct3D10_I*>(m_pGraphicsO->m_device);

	int opacity = m_pClient->GetVisualTree()->get_Opacity()*255;

	if (opacity < 0) opacity = 0;
	else if (opacity > 255) opacity = 255;

	if (opacity < 255)
	{
	//	if (!m_layered)
	//	{
		//	m_layered = true;

			// Set WS_EX_LAYERED
			//MSWindows::SetWindowLongA(m_hWnd, GWL_EXSTYLE, MSWindows::GetWindowLongA(GetHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
			ModifyExStyle(WS_EX_LAYERED, WS_EX_LAYERED);
	//	}

		UpdateHBITMAP();
		SetLayeredWindowBitmap();
	}
	else
	{
	//	if (m_layered)
		{
			// Clear WS_EX_LAYERED
		//	MSWindows::SetWindowLongW(m_hWnd, GWL_EXSTYLE, MSWindows::GetWindowLongW(GetHwnd(), GWL_EXSTYLE) & ~WS_EX_LAYERED);
#if 0
			ModifyExStyle(WS_EX_LAYERED, 0);
#endif
	//		m_layered = false;
		}

		if (d3d10)
		{
			d3d10->Present();
		}
		else
		{
			//LDraw::Direct3D9_I* d3d9 = dynamic_cast<LDraw::Direct3D9_I*>(m_pGraphicsO->m_device);
		//	MSWindows::D3D_Present(m_d3dDevice9, NULL, NULL);

			if (g_PresentEvent)
			{
				WaitForSingleObject(g_PresentEvent, INFINITE);
			}
			//MessageBeep(-1);
			MSWindows::D3D_Present(m_d3dSwapChain9, NULL, NULL, m_hWnd);
			if (g_PresentEvent)
				g_presented(NULL);
		}
	}
	return;

	if (false)
	{
		int size = 4;
		int range = (1<<size) * (1<<size);
		printdither(size, range);
	}

	ASSERT(pRgn);

#if WIN32

	if (m_hWnd)
	{
		LDraw::RectI wrect;
		GetPhysicalWindowRect(&wrect);

		if (m_bAlpha)
		{
			SetLayeredWindowBitmap();
		}
		else
		{
			int opacity = m_pClient->GetVisualTree()->get_Opacity()*255;
			if (opacity < 0) opacity = 0;
			else if (opacity > 255) opacity = 255;
			if (opacity < 255)
			{
				MSWindows::SetWindowLongA(m_hWnd, GWL_EXSTYLE, MSWindows::GetWindowLongA(GetHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
				MSWindows::SetLayeredWindowAttributes(m_hWnd, 0, opacity, LWA_ALPHA);
			}

			{
				ASSERT(m_hWnd);
				HDC dc = NULL;
				if (!UseDirectDraw)
				{
					dc = GetDC(m_hWnd);
				}

#if !USE_CLIPPING
				if (true)	// Blit one large bitmap
				{
#if 1
//					::Rectangle(dc, rect.X, rect.Y, rect.GetRight(), rect.GetBottom());
//					Sleep(15);
					{
						HDC offdc = CreateCompatibleDC(dc);
						HBITMAP hOldBitmap = (HBITMAP)SelectObject(offdc, m_hBitmap);
	
						LDraw::RectI rect(0, 0, 600, 600);
						BitBlt(dc, rect.X, rect.Y, rect.Width, rect.Height, offdc, rect.X, rect.Y, SRCCOPY);
						
						SelectObject(offdc, hOldBitmap);
						DeleteDC(offdc);
					}

					//::UpdateWindow(GetHwnd());
#endif
				}
				else	// Blit the updated bitmap regions
#endif
				{
			//		const LDraw::RegionRect_old* pRect;

#if 0
					ASSERT(pRgn->m_data);

//					pRect = rgn->GetFirstRect();
//					while (pRect)
					{
						LDraw::Span* span = pRgn->m_data->m_spans;
						while (span)
						{
							LDraw::Span* spannext = span->next;

							LDraw::Segment* segment = span->x;

							while (segment)
							{
								LDraw::Segment* segmentnext = segment->next;
								ASSERT(segmentnext != NULL);
								LDraw::BBoxi bbox(segment->x, span->y, segmentnext->x, spannext->y);

								MSWindows::Rectangle(dc, bbox.left, bbox.top, bbox.right, bbox.bottom);

								segment = segmentnext->next;
							}

							span = spannext;
						}
//						pRect = pRect->m_next;
						Sleep(20);
					}
#endif
					HDC offdc = NULL;
					HBITMAP hOldBitmap = NULL;

					if (!UseDirectDraw)
					{
						offdc = CreateCompatibleDC(dc);
						hOldBitmap = (HBITMAP)SelectObject(offdc, (void*)m_hBitmap);
					}

				//	TRACE("GetFirstRect...");
				//	pRect = m_invalidRegion.GetFirstRect();
				//	TRACE("done\n");
				//	while (pRect)

				//	uint32 displayMode = 15 | DISPLAY_RGB | DISPLAY_DITHER;
				//	uint32 displayMode = DISPLAYMODE_RGB_216 | DISPLAY_DITHER;
					uint32 displayMode = DISPLAYMODE_RGB_TRUECOLOR;
				//	uint32 displayMode = DISPLAYMODE_RGB_HAM8;

					LDraw::PixelRGB_32 palette[256];

					if (((displayMode>>8)&3) == 0)
					{
						int displayBits = displayMode & DISPLAYMODE_BITS_MASK;
						if (displayBits == 1)
						{
							palette[0].r = 0;
							palette[0].g = 0;
							palette[0].b = 0;

							palette[1].r = 255;
							palette[1].g = 255;
							palette[1].b = 255;
						}
						else if (displayBits == 2)
						{
							for (int i = 0; i < 4; i++)
							{
								palette[i].r = (i<<6) | (i<<4) | (i<<2) | i;
								palette[i].g = (i<<6) | (i<<4) | (i<<2) | i;
								palette[i].b = (i<<6) | (i<<4) | (i<<2) | i;
							}
						}
						else if (displayBits == 4)
						{
							for (int i = 0; i < 16; i++)
							{
								palette[i].r = (i<<4) | i;
								palette[i].g = (i<<4) | i;
								palette[i].b = (i<<4) | i;
							}
						}
						else if (displayBits == 6)
						{
							for (int i = 0; i < 64; i++)
							{
								palette[i].r = (i<<6) | (i<<4) | (i<<2) | i;
								palette[i].g = (i<<6) | (i<<4) | (i<<2) | i;
								palette[i].b = (i<<6) | (i<<4) | (i<<2) | i;
							}
						}
						else if (displayBits == 8)
						{
							for (int i = 0; i < 256; i++)
							{
								palette[i].r = i;
								palette[i].g = i;
								palette[i].b = i;
							}
						}
						else
							ASSERT(0);
					}
					else
					{
						int displayBits = displayMode & DISPLAYMODE_BITS_MASK;

						if (displayBits == 1)
						{
							int i = 0;
							for (int b = 0; b < 2; b++)
							{
								for (int g = 0; g < 2; g++)
								{
									for (int r = 0; r < 2; r++)
									{
										palette[i].r = (r<<7) | (r<<6) | (r<<5) | (r<<4) | (r<<3) | (r<<2) | (r<<1) | r;
										palette[i].g = (g<<7) | (g<<6) | (g<<5) | (g<<4) | (g<<3) | (g<<2) | (g<<1) | r;
										palette[i].b = (b<<7) | (b<<6) | (b<<5) | (b<<4) | (b<<3) | (b<<2) | (b<<1) | b;

										i++;
									}
								}
							}
							ASSERT(i == 8);
						}
						else if (displayBits == 2)
						{
							int i = 0;
							for (int b = 0; b < 2; b++)
							{
								for (int g = 0; g < 4; g++)
								{
									for (int r = 0; r < 2; r++)
									{
										palette[i].r = (r<<7) | (r<<6) | (r<<5) | (r<<4) | (r<<3) | (r<<2) | (r<<1) | r;
										palette[i].g = (g<<6) | (g<<4) | (g<<2) | g;
										palette[i].b = (b<<7) | (b<<6) | (b<<5) | (b<<4) | (b<<3) | (b<<2) | (b<<1) | b;

										i++;
									}
								}
							}
							ASSERT(i == 16);
						}
						else if (displayBits == 3)
						{
							int i = 0;
							for (int b = 0; b < 3; b++)
							{
								for (int g = 0; g < 3; g++)
								{
									for (int r = 0; r < 3; r++)
									{
										palette[i].r = r*255/2;
										palette[i].g = g*255/2;
										palette[i].b = b*255/2;

										i++;
									}
								}
							}
							ASSERT(i == 27);
						}
						else if (displayBits == 4 || displayBits == (6 | 128))
						{
							int i = 0;
							for (int b = 0; b < 4; b++)
							{
								for (int g = 0; g < 4; g++)
								{
									for (int r = 0; r < 4; r++)
									{
										palette[i].r = (r<<6) | (r<<4) | (r<<2) | r;
										palette[i].g = (g<<6) | (g<<4) | (g<<2) | g;
										palette[i].b = (b<<6) | (b<<4) | (b<<2) | b;

										i++;
									}
								}
							}
							ASSERT(i == 64);
						}
						else if (displayBits == 5)
						{
							int i = 0;
							for (int b = 0; b < 5; b++)
							{
								for (int g = 0; g < 5; g++)
								{
									for (int r = 0; r < 5; r++)
									{
										palette[i].r = r*255/4;
										palette[i].g = g*255/4;
										palette[i].b = b*255/4;

										i++;
									}
								}
							}
							ASSERT(i == 125);
						}
						else if (displayBits == 6)
						{
							int i = 0;
							for (int b = 0; b < 6; b++)
							{
								for (int g = 0; g < 6; g++)
								{
									for (int r = 0; r < 6; r++)
									{
										palette[i].r = r*255/5;
										palette[i].g = g*255/5;
										palette[i].b = b*255/5;

										i++;
									}
								}
							}
							ASSERT(i == 216);
						}
						else if (displayBits == 7)
						{
							int i = 0;
							for (int b = 0; b < 6; b++)
							{
								for (int g = 0; g < 7; g++)
								{
									for (int r = 0; r < 6; r++)
									{
										palette[i].r = r*255/5;
										palette[i].g = g*255/6;
										palette[i].b = b*255/5;

										i++;
									}
								}
							}
							ASSERT(i == 252);
						}
						else if (displayBits == 15)
						{
						}
					}

					int rowbytes = ROWBYTES_DWORD(m_lpBmi->biWidth, 32);
					uint8* bits = m_bmBits + (m_lpBmi->biHeight-1)*rowbytes;
					rowbytes = -rowbytes;
					{
						ASSERT(pRgn->m_data);

						LDraw::Span* span = pRgn->m_data->m_spans;
						while (span)
						{
							LDraw::Span* spannext = span->next;

							LDraw::Segment* segment = span->x;

							if (segment)
							{
								int top = span->y;
								int height = spannext->y - top;
								if (true)
								{
									do
									{
										LDraw::Segment* segmentnext = segment->next;
										ASSERT(segmentnext != NULL);
										int left = segment->x;
										int width = segmentnext->x - left;

										if (displayMode != DISPLAYMODE_RGB_TRUECOLOR)
										{
											uint8* prow = bits + top * rowbytes + left * 4;

											int bottom = top+height;
											int right = left+width;
											for (int y = top; y < bottom; y++)
											{
												LDraw::PixelRGB_32* pixel = (LDraw::PixelRGB_32*)prow;
												unsigned int* pattern = DitherPattern[y&15];

												for (int x = left; x < right; x++)
												{
													if (displayMode & DISPLAY_DITHER)
													{
														int mode = displayMode & ~DISPLAY_DITHER;
														if (mode == DISPLAYMODE_GRAYSCALE_1)
														{
															int v = pattern[x&15];

															int gray = (((int)pixel->r + pixel->g + pixel->b) / 3);
															if (gray < v)
															{
																pixel->r = 0;
																pixel->g = 0;
																pixel->b = 0;
															}
															else
															{
																pixel->r = 255;
																pixel->g = 255;
																pixel->b = 255;
															}
														}
														else if (mode == DISPLAYMODE_GRAYSCALE_2)
														{
															int v = pattern[x&15]>>2;

															int gray = (((int)pixel->r + pixel->g + pixel->b) / 3);

															int g = MIN(gray + v, 255);

															int index = g>>6;
															*pixel = palette[index];
														}
														else if (mode == DISPLAYMODE_GRAYSCALE_3)
														{
															int v = pattern[x&15]>>2;

															int gray = (((int)pixel->r + pixel->g + pixel->b) / 3);

															int g = MIN(gray + v, 255);

															int index = g>>5;
															*pixel = palette[index];
														}
														else if (mode == DISPLAYMODE_GRAYSCALE_4)
														{
															int v = pattern[x&15]>>2;

															int gray = (((int)pixel->r + pixel->g + pixel->b) / 3);

															int g = MIN(gray + v, 255);

															int index = g>>4;
															*pixel = palette[index];
														}
														else if (mode == DISPLAYMODE_GRAYSCALE_5)
														{
															int v = pattern[x&15]>>2;

															int gray = (((int)pixel->r + pixel->g + pixel->b) / 3);

															int g = MIN(gray + v, 255);

															int index = g>>3;
															*pixel = palette[index];
														}
														else if (mode == DISPLAYMODE_GRAYSCALE_6)
														{
															int v = pattern[x&15]>>2;

															int gray = (((int)pixel->r + pixel->g + pixel->b) / 3);

															int g = MIN(gray + v, 255);

															int index = g>>2;
															*pixel = palette[index];
														}
														else if (mode == DISPLAYMODE_GRAYSCALE_7)
														{
															int v = pattern[x&15]>>2;

															int gray = (((int)pixel->r + pixel->g + pixel->b) / 3);

															int g = MIN(gray + v, 255);

															int index = g>>1;
															*pixel = palette[index];
														}
														else if (mode == DISPLAYMODE_RGB_8)
														{
															int v = pattern[x&15]>>2;

															int index;
															{
																int gray = pixel->r;

																int g = MIN(gray + v, 255);

																g >>= 7;
																index = g;
															}

															{
																int gray = pixel->g;

																int g = MIN(gray + v, 255);

																g >>= 7;
																index |= g<<1;
															}

															{
																int gray = pixel->b;

																int g = MIN(gray + v, 255);

																g >>= 7;
																index |= g<<2;
															}

															*pixel = palette[index];
														}
														else if (mode == DISPLAYMODE_RGB_16)
														{
															int v = pattern[x&15]>>2;

															int index;
															{
																int gray = pixel->r;

																int g = MIN(gray + v, 255);

																g >>= 7;
																index = g;
															}

															{
																int gray = pixel->g;

																int g = MIN(gray + v, 255);

																g >>= 6;
																index |= g<<1;
															}

															{
																int gray = pixel->b;

																int g = MIN(gray + v, 255);

																g >>= 7;
																index |= g<<3;
															}

															*pixel = palette[index];
														}
														else if (mode == DISPLAYMODE_RGB_27)
														{
															int v = pattern[x&15]>>2;

															int r;
															{
																int gray = MIN(pixel->r + v, 255);

																r = gray*2 / 255;
															}

															int g;
															{
																int gray = MIN(pixel->g + v, 255);

																g = gray*2 / 255;
															}

															int b;
															{
																int gray = MIN(pixel->b + v, 255);

																b = gray*2 / 255;
															}

															int index = r + g*3 + b*9;
															*pixel = palette[index];
														}
														else if (mode == DISPLAYMODE_RGB_64)
														{
															int v = pattern[x&15]>>2;

															int index;
															{
																int gray = pixel->r;

																int g = MIN(gray + v, 255);

																g >>= 6;
																index = g;
															}

															{
																int gray = pixel->g;

																int g = MIN(gray + v, 255);

																g >>= 6;
																index |= g<<2;
															}

															{
																int gray = pixel->b;

																int g = MIN(gray + v, 255);

																g >>= 6;
																index |= g<<4;
															}

															*pixel = palette[index];
														}
														else if (mode == DISPLAYMODE_RGB_125)
														{
															int v = pattern[x&15]>>2;

															int r;
															{
																int gray = MIN(pixel->r + v, 255);

																r = gray*4 / 255;
															}

															int g;
															{
																int gray = MIN(pixel->g + v, 255);

																g = gray*4 / 255;
															}

															int b;
															{
																int gray = MIN(pixel->b + v, 255);

																b = gray*4 / 255;
															}

															int index = r + g*5 + b*25;
															*pixel = palette[index];
														}
														else if (mode == DISPLAYMODE_RGB_8)
														{
															int v = pattern[x&15]>>2;

															int index;
															{
																int gray = MIN(pixel->r + v, 255);

																gray >>= 6;
																index = gray;
															}

															{
																int gray = MIN(pixel->g + v, 255);

																gray >>= 5;
																index |= gray<<2;
															}

															{
																int gray = MIN(pixel->b + v, 255);

																gray >>= 5;
																index |= gray<<5;
															}

															*pixel = palette[index];
														}
														else if (mode == DISPLAYMODE_RGB_216)
														{
															int v = pattern[x&15]>>2;

															int r;
															{
																int gray = MIN(pixel->r + v, 255);

																r = gray*5 / 255;
															}

															int g;
															{
																int gray = MIN(pixel->g + v, 255);

																g = gray*5 / 255;
															}

															int b;
															{
																int gray = MIN(pixel->b + v, 255);

																b = gray*5 / 255;
															}

															int index = r + g*6 + b*36;
															*pixel = palette[index];
														}
														else if (mode == DISPLAYMODE_RGB_252)
														{
															int v = pattern[x&15]>>2;

															int r;
															{
																int gray = MIN(pixel->r + v, 255);

																r = gray*5 / 255;
															}

															int g;
															{
																int gray = MIN(pixel->g + v, 255);

																g = gray*6 / 255;
															}

															int b;
															{
																int gray = MIN(pixel->b + v, 255);

																b = gray*5 / 255;
															}

															int index = r + g*6 + b*42;
															*pixel = palette[index];
														}
														else if (mode == DISPLAYMODE_RGB_HICOLOR)
														{
															int v = pattern[x&15]>>2;

															int r;
															{
																int gray = MIN(pixel->r + v, 255);
																r = gray >> 3;
															}

															int g;
															{
																int gray = MIN(pixel->g + v, 255);
																g = gray >> 3;
															}

															int b;
															{
																int gray = MIN(pixel->b + v, 255);
																b = gray >> 3;
															}

															pixel->r = (r<<3) | (r>>2);
															pixel->g = (g<<3) | (g>>2);
															pixel->b = (b<<3) | (b>>2);
														}
														else
															ASSERT(0);
													}
													else
													{
														int displayBits = displayMode & DISPLAYMODE_BITS_MASK;

														if (((displayMode>>8)&3) == 0)
														{
															int gray = (((int)pixel->r + pixel->g + pixel->b) / 3);

															int index = gray>>(8-displayBits);
															*pixel = palette[index];
														}
														else
														{
															if (displayBits == 3)
															{
																int index = (pixel->r >> 7);
																index |= (pixel->g >> 7) << 1;
																index |= (pixel->b >> 7) << 2;

																*pixel = palette[index];
															}
															else if (displayBits == 4)
															{
																int index = (pixel->r >> 7);
																index |= (pixel->g >> 6) << 1;
																index |= (pixel->b >> 7) << 3;

																*pixel = palette[index];
															}
															else if (displayBits == 5)
															{
																int index = (pixel->r >> 7);
																index |= (pixel->g >> 6) << 1;
																index |= (pixel->b >> 6) << 3;

																*pixel = palette[index];
															}
															else if (displayBits == 6)
															{
																int index = (pixel->r >> 6);
																index |= (pixel->g >> 6) << 2;
																index |= (pixel->b >> 6) << 4;

																*pixel = palette[index];
															}
															else if (displayBits == 7)
															{
																int index = (pixel->r >> 6);
																index |= (pixel->g >> 5) << 2;
																index |= (pixel->b >> 6) << 5;

																*pixel = palette[index];
															}
															else if (displayBits == 8)
															{
																int index = (pixel->r >> 6);
																index |= (pixel->g >> 5) << 2;
																index |= (pixel->b >> 5) << 5;

																*pixel = palette[index];
															}
															else if (displayBits == 15)
															{
																pixel->r = (pixel->r & ~7) | (pixel->r>>5);
																pixel->g = (pixel->g & ~7) | (pixel->g>>5);
																pixel->b = (pixel->b & ~7) | (pixel->b>>5);
															}
															else
																ASSERT(0);
														}
													}

													pixel++;
												}

												prow += rowbytes;
											}
										}

										if (UseDirectDraw)
										{
											if (false)
											{
											//	MSWindows::D3D_CopyRect(m_d3dDevice9, left, top, m_d3dSurface, left, top, width, height);
											}
										}
										else
										{
											BitBlt(dc, left, top, width, height, offdc, left, top, SRCCOPY);
										}

										segment = segmentnext->next;
									}
									while (segment);

								}
								else
								{
									// Convert RGB24 to HAM

									int width = m_lpBmi->biWidth;

									int bottom = top+height;
									uint8 scanline[2000];

									for (int y = top; y < bottom; y++)
									{
										int r = 0;
										int g = 0;
										int b = 0;

										{
											LDraw::PixelRGB_32* pixel = (LDraw::PixelRGB_32*)(bits + rowbytes*y);
											uint8* dest = scanline;

											for (int x = 0; x < width; x++)
											{
												int pr = pixel->r >> 2;
												int pg = pixel->g >> 2;
												int pb = pixel->b >> 2;

												// how many pixels does it take to reach the target color, 1,2 or 3

												int n = -1;
												if (r != pr) n++;
												if (g != pg) n++;
												if (b != pb) n++;

												int rdiff = abs(r - pr);
												int gdiff = abs(g - pg);
												int bdiff = abs(b - pb);

												if (rdiff > gdiff)
												{
													if (rdiff > bdiff)
													{
														// change r
														*dest = pr | (1<<6);
														r = pr;
													}
													else
													{
														// change b
														*dest = pb | (3<<6);
														b = pb;
													}
												}
												else if (gdiff > bdiff)
												{
													// change g
													*dest = pg | (2<<6);
													g = pg;
												}
												else
												{
													// change b
													*dest = pb | (3<<6);
													b = pb;
												}

												pixel++;
												dest++;
											}
										}

										// Convert HAM back to RGB24

										{
											LDraw::PixelRGB_32* pixel = (LDraw::PixelRGB_32*)(bits + rowbytes*y);
											uint8* src = scanline;

											r = 0;
											g = 0;
											b = 0;

											for (int x = 0; x < width; x++)
											{
												uint8 m = *src >> 6;
												uint8 c = *src & 63;
												if (m == 0)
												{
													r = palette[c].r;
													g = palette[c].g;
													b = palette[c].b;
												}
												else if (m == 1)
												{
													r = (c<<2) | (c>>4);
												}
												else if (m == 2)
												{
													g = (c<<2) | (c>>4);
												}
												else
												{
													b = (c<<2) | (c>>4);
												}

												pixel->r = r;
												pixel->g = g;
												pixel->b = b;

												pixel++;
												src++;
											}
										}
									}

									BitBlt(dc, 0, top, m_lpBmi->biWidth, height, offdc, 0, top, SRCCOPY);
								}
							}

							span = spannext;
						}

						if (false)
						{
							if (UseDirectDraw)
							{
#if 0
								MSWindows::D3D_CopyRect(m_d3dDevice9, 0, 0, m_d3dSurface, 0, 0, m_d3dpp9.BackBufferWidth, m_d3dpp9.BackBufferHeight);
#endif
							//	Present(m_d3dDevice);
								//BltPrimary(wrect.X, wrect.Y, m_dds, left, top, width, height);
							}
						}

						if (m_hRC)
						{
							glFinish();

							BOOL success = SwapBuffers(m_hDC);
							ASSERT(success);
						}
						else if (UseDirectDraw)
						{
							/*
							if (true)
							{
								HRESULT hr;

							}
							*/

							int fps = 16;
							if (m_timing_info.rateRefresh.uiDenominator > 0)
							{
#if 0
								HRESULT hr = MSWindows::DwmSetDxFrameDuration(m_hWnd, m_timing_info.rateRefresh.uiNumerator/(m_timing_info.rateRefresh.uiDenominator*fps));
								ASSERT(hr >= 0);
#endif
							}
							MSWindows::RECT rect;
							pRgn->GetBounds((LDraw::BBoxi*)&rect);

							if (true)
							{
								LDraw::Direct3D10_I* d3d10 = dynamic_cast<LDraw::Direct3D10_I*>(m_pGraphicsO->m_device);

								d3d10->Present();
							}
							else
							{
							//	D3D_Present(m_d3dDevice, &rect, &rect);
								MSWindows::D3D_Present(m_d3dDevice9, NULL, NULL);
							}
						}
					}

					if (offdc)
					{
						SelectObject(offdc, (void*)hOldBitmap);
						DeleteDC(offdc);
					}
				}

				if (dc)
				{
					ReleaseDC(m_hWnd, dc);
				}
			}
		}
	}

#elif AMIGA

#if 0
	if (m_hWnd)
	{
		//LDraw::RectI rect;
		//rgn->GetRegionRect(&rect);


		/*
		LDraw::RectI rect(0, 0, 600, 600);

		// Adjust for windowRect outside visible screen area
	//	int destX = rect.X - (m_hWnd->LeftEdge - m_windowRect.X);
	//	int destY = rect.Y - (m_hWnd->TopEdge - m_windowRect.Y);

		BltBitMapRastPort(m_pBitmap, 0, 0, m_hWnd->RPort, 0, 0, rect.Width, rect.Height, 0xC0);

		return;
		*/

		{
			LDraw::Span* span = pRgn->m_spans;
			while (span)
			{
				LDraw::Span* spannext = span->next;

				LDraw::Segment* segment = span->x;

				if (segment)
				{
					int top = span->y;
					int height = spannext->y - top;

					// Adjust for windowRect outside visible screen area
					int destY = top - (m_hWnd->TopEdge - m_windowRect.Y);

				//	printf("destY: %d\n", destY);
					do
					{
						LDraw::Segment* segmentnext = segment->next;
						ASSERT(segmentnext != NULL);
						int left = segment->x;
						int width = segmentnext->x - left;

					// Adjust for windowRect outside visible screen area
						int destX = left - (m_hWnd->LeftEdge - m_windowRect.X);

					//	BitBlt(dc, left, top, width, height, offdc, left, top, SRCCOPY);
						BltBitMapRastPort(m_pBitmap, left, top, m_hWnd->RPort, destX, destY, width, height, 0xC0);

						segment = segmentnext->next;
					}
					while (segment);
				}

				span = spannext;
			}
		}
	}
#endif

#elif __APPLE__

	if (m_hWnd)
	{
		LDraw::RectI rect;
		rgn->GetRegionRect(&rect);

		::RgnHandle hrgn = NewRgn();
		SetRectRgn(hrgn, rect.X, rect.Y, rect.GetRight(), rect.GetBottom());

		GrafPtr port = GetWindowPort(m_hWnd);
		::QDFlushPortBuffer(port, hrgn);

		DisposeRgn(hrgn);
	}

#endif
}

void HwndSource::Render()
{
//	LDraw::RectI rect;
//	m_invalidRegion.GetRegionRect(&rect);


#if AMIGA

	UIElement* p = m_pClient->get_VisualTree();

	//LDraw::GraphicsRP* pGraphicsRP = new LDraw::GraphicsRP(GetHwnd()->WScreen->ViewPort.ColorMap, GetHwnd()->RPort);
	Graphics* graphics = new Graphics(m_pGraphicsRP);

	/*
#if 0

//	printf("%d,%d,%d,%d\n", m_invalidRect.X, m_invalidRect.Y, m_invalidRect.Width, m_invalidRect.Height);

	LDraw::RectI bounds = m_invalidRect;
	graphics->m_p->SetClip(m_invalidRect);//&m_invalidRegion;
#else
	LDraw::RectI bounds;
	m_invalidRegion->GetRegionRect(&bounds);
	graphics->m_p->SetClip(m_invalidRegion);//&m_invalidRegion;
#endif

	bounds.X += GetHwnd()->RPort->Layer->bounds.MinX;
	bounds.Y += GetHwnd()->RPort->Layer->bounds.MinY;

//	::Region* rgn = NewRegion();
	::gfxRectangle rect;
	rect.MinX = bounds.X;
	rect.MinY = bounds.Y;
	rect.MaxX = bounds.X + bounds.Width - 1;
	rect.MaxY = bounds.Y + bounds.Height - 1;

	::gfxRectangle oldrect = GetHwnd()->RPort->Layer->ClipRect->bounds;

//	gfxOrRectRegion(rgn, &rect);
//	::Region* oldrgn = InstallClipRegion(GetHwnd()->RPort->Layer, rgn);
	GetHwnd()->RPort->Layer->ClipRect->bounds = rect;

	graphics->Clear(LDraw::Color(0, 0, 0, 0));
	*/

	//ComputeVisible(m_pClient);

	//char buf[6];

//	printf("1\n");
//	Delay(10);
//	gets(buf);

	//m_pClient->m_visibleRegion = m_pClient->OnGetRegion(graphics->GetTransform());

//	printf("2\n");
//	Delay(10);
//	gets(buf);

	/*
	m_pClient->CreateOpaqueRegion(graphics);

	m_pClient->m_visibleRegion = new LDraw::Region(LDraw::RectI(0, 0, m_pClient->m_expandedBBox.Width, m_pClient->m_expandedBBox.Height));	// infinite //m_pClient->OnGetRegion(graphics->GetTransform());
	ASSERT(m_pClient->m_visibleRegion.m_p != NULL);
	m_pClient->CreateLayerStuff(graphics);
	*/

//	printf("3\n");
//	Delay(10);
//	gets(buf);

//	graphics->m_invalidRegion = m_invalidRegion;

	graphics->PushClip();
	graphics->m_p->SetClip(m_invalidRegion);
//	graphics->m_p->SetClip(m_pClient->m_visibleRegion);

//	printf("4\n");
//	Delay(10);
//	gets(buf);

	//graphics->TranslateTransform(-p->m_expandedBBox.X, -p->m_expandedBBox.Y);	// ???
//	m_pClient->_OnRender(graphics);

	{
		D3D_Clear(m_d3dDevice);
		D3D_BeginScene(m_d3dDevice);

		UIElement* current = m_redrawList;
		while (current)
		{
			printf("Drawing an element\n");

			ASSERT(current->m_bRedraw);

			graphics->PushTransform();

			/*
			LDraw::Matrix3f* mat = new LDraw::Matrix3f(current->GetParentToElementTransformMatrix()->m_matrix);
			UIElement* parent = current->GetRParent();
			while (parent)
			{
				mat->m_matrix = mat->m_matrix * parent->GetLocalAnimatedMatrix()->m_matrix;

				parent = parent->GetRParent();
			}
			*/
			if (!current->m_bRenderValid)
			{
				__release<LDraw::Matrix3f> transform = current->GetWindowToElementTransformMatrix();
				ASSERT(transform.m_p);


				graphics->PushTransform();
				graphics->m_p->SetTransform(transform);

				current->RenderNoTransform(graphics);

				graphics->PopTransform();
			}

			current->m_bRedraw = false;

			UIElement* next = current->m_redrawNext;
			current->m_redrawNext = NULL;

			current = next;
			m_redrawList = next;
		}

		D3D_EndScene(m_d3dDevice);
	}

	graphics->PopClip();

//	graphics->m_invalidRegion = NULL;

//	printf("5\n");
//	Delay(10);
//	gets(buf);

//	InstallClipRegion(GetHwnd()->RPort->Layer, oldrgn);
//	GetHwnd()->RPort->Layer->ClipRect->bounds = oldrect;

#else

	//m_crit.Lock();

	if (!m_renderTargetUpdated)
	{
		RenderToTarget();

//	m_bInvalidated = false;

	//m_crit.Unlock();

		FlushToScreen(m_invalidRegion);

#endif

#if 0//AMIGA
	m_invalidRect.X = 0;
	m_invalidRect.Y = 0;
	m_invalidRect.Width = 0;
	m_invalidRect.Height = 0;
#else

	m_invalidRegion = LDraw::Region::GetEmptyRegion();
	/*
	if (m_invalidRegion->m_refcount > 1)
	{
		m_invalidRegion = new LDraw::Region;
		m_invalidRegion->MakeEmpty();
	}
	else
	{
		m_invalidRegion->MakeEmpty();
	}
	*/

#endif
	}
}

void HwndSource::GetPhysicalWindowRect(LDraw::RectI* lpRect) const
{
#if WIN32

	ASSERT(m_hWnd);

	MSWindows::RECT w;
	MSWindows::GetWindowRect(m_hWnd, &w);

//	lpRect->X -= m_pClient->m_expandedBBox.X;
//	lpRect->Y -= m_pClient->m_expandedBBox.Y;

	lpRect->X = w.left;
	lpRect->Y = w.top;
	lpRect->Width = w.right - w.left;
	lpRect->Height = w.bottom - w.top;

#elif AMIGA

	ASSERT(m_hWnd);
	*lpRect = m_windowRect;

#elif __APPLE__

	ASSERT(m_hWnd);

	::Rect bounds;
	GetWindowBounds(m_hWnd, kWindowStructureRgn, &bounds);

	lpRect->X = bounds.left;
	lpRect->Y = bounds.top;
	lpRect->Width = bounds.right - bounds.left;
	lpRect->Height = bounds.bottom - bounds.top;

#else

#error "Unknown OS"

#endif
}

void HwndSource::GetLogicalWindowRect(LDraw::RectD* lpRect) const
{
	LDraw::RectI physRect;
	GetPhysicalWindowRect(&physRect);

	float scale = 96 / pixelsPerInch;

	lpRect->X = physRect.X * scale;
	lpRect->Y = physRect.Y * scale;
	lpRect->Width = physRect.Width * scale;
	lpRect->Height = physRect.Height * scale;
}

void HwndSource::GetClientRect(LDraw::RectI* lpRect) const
{
#if WIN32
	ASSERT(m_hWnd);

	MSWindows::RECT client;
	MSWindows::GetClientRect(m_hWnd, &client);
	lpRect->X = client.left;
	lpRect->Y = client.top;
	lpRect->Width = client.right - client.left;
	lpRect->Height = client.bottom - client.top;

#elif AMIGA

	ASSERT(m_hWnd);

	lpRect->X = 0;
	lpRect->Y = 0;
	lpRect->Width = m_hWnd->Width;
	lpRect->Height = m_hWnd->Height;
#endif
}

void HwndSource::SetClient(PresentationContentSource* pClient)
{
	m_pClient = pClient;
	m_pClient->SetSite(this);

#if 0
	m_pClient = pClient;
	m_pClient = dynamic_cast<UIElement*>(m_pClient);
	if (m_pClient == NULL)
		THROW(-1);

	pClient->SetSite(this);
#endif
}

void HwndSource::SetLogicalWindowRect(double X, double Y, double Width, double Height)
{
#if _WINDOWS

	// TODO scale

	MSWindows::SetWindowPos(m_hWnd, NULL, X+m_pClient->GetVisualTree()->m_expandedBBox.X, Y+m_pClient->GetVisualTree()->m_expandedBBox.Y, Width, Height, SWP_NOZORDER | SWP_NOACTIVATE);

#elif AMIGA

	// On the Amiga (OS3.9) we keep track of our own windowRect, which may be
	// different from the real intuition windows size and position. This is to
	// support off-screen windows

	LDraw::RectI rect(X, Y, Width, Height);

	if (X < 0)
	{
		Width += X;
		X = 0;
	}

	if (Y < 0)
	{
		Height += Y;
		Y = 0;
	}

	if (rect.GetRight() > m_hWnd->WScreen->Width)
	{
		Width -= rect.GetRight() - m_hWnd->WScreen->Width;
	}

	if (rect.GetBottom() > m_hWnd->WScreen->Height)
	{
		Height -= rect.GetBottom() - m_hWnd->WScreen->Height;
	}

	m_windowRect.X = rect.X;
	m_windowRect.Y = rect.Y;
	if (m_windowRect.Width != rect.Width || m_windowRect.Height != rect.Height)
	{
		m_windowRect.Width = rect.Width;
		m_windowRect.Height = rect.Height;

		if (false)
		{
			SetBitmapSize(m_windowRect.Width, m_windowRect.Height);
			UpdateBitmap();
		}
	}

	/* When calling ChangeWindowBox, intuition will sometimes move the contents of the window
	to the new location, since we support off-screen windows, we will need to redraw the
	entire window anyway, and it looks better to clear the window first.
*/
	SetAPen(m_hWnd->RPort, 0);
	RectFill(m_hWnd->RPort, 0, 0, m_hWnd->Width, m_hWnd->Height);
	ChangeWindowBox(m_hWnd, X, Y, Width, Height);

#endif
}

void HwndSource::OnMouseLeave()
{
	m_bInsideWindow = false;

	if (!m_locked && g_uiLocked == 0)
	{
#if WIN32

		MSWindows::POINT screenpoint;
		MSWindows::GetCursorPos(&screenpoint);

		MSWindows::POINT point = screenpoint;
		MSWindows::ScreenToClient(m_hWnd, &point);

		float rscale = 96 / pixelsPerInch;

		m_pClient->OnMouseLeave(LDraw::PointD(screenpoint.x*rscale, screenpoint.y*rscale), LDraw::PointD(point.x, point.y));
	//	m_pClient->OnMouseMove(0/*nFlags*/, LDraw::PointD(screenpoint.x, screenpoint.y), LDraw::PointI(point.x, point.y));

#elif AMIGA

		LDraw::PointI point(m_hWnd->GZZMouseX, m_hWnd->GZZMouseY);
		LDraw::PointI screenpoint;
		screenpoint.X += m_hWnd->LeftEdge;
		screenpoint.Y += m_hWnd->TopEdge;

		m_pClient->OnMouseMove(0/*nFlags*/, LDraw::PointD(screenpoint.X, screenpoint.Y), point);

#elif __APPLE__

		::Point qdpoint;
		::GetGlobalMouse(&qdpoint);

		::Rect bounds;
		GetWindowBounds(m_hWnd, kWindowStructureRgn, &bounds);

		LDraw::PointI screenpoint(qdpoint.h, qdpoint.v);
		LDraw::PointI point(screenpoint.X - bounds.left, screenpoint.Y - bounds.top);

		m_pClient->OnMouseMove(0/*nFlags*/, LDraw::PointD(screenpoint.X, screenpoint.Y), point);

#else

#error "Unknown OS"

#endif
	}
}

int HwndSource::InitPresent()
{
	HRESULT hr;

#if 0
	m_timing_info.cbSize = sizeof(m_timing_info);
	hr = DwmGetCompositionTimingInfo(m_hWnd, &m_timing_info);
	ASSERT(hr >= 0);
	if (hr >= 0)
	{
	//	TRACE("cFrameDisplayed: %lld\n", timing_info.cFrameDisplayed);

		DWM_PRESENT_PARAMETERS dwm_pp;
		dwm_pp.cbSize = sizeof(DWM_PRESENT_PARAMETERS);
		dwm_pp.fQueue = true;
		dwm_pp.cRefreshStart = m_timing_info.cRefresh+60;
		dwm_pp.cBuffer = 3;	// The number of frames the app would like the DWM to queue. Range: 2-8
		dwm_pp.fUseSourceRate = true;
		dwm_pp.rateSource.uiNumerator = 16;
		dwm_pp.rateSource.uiDenominator = 1;
		//timing_info.rateRefresh.uiNumerator / timing_info.rateRefresh.uiDenominator;
		//dwm_pp.cRefreshesPerFrame = 2;
		dwm_pp.eSampling = DWM_SOURCE_FRAME_SAMPLING_POINT;
								// DWM_SOURCE_FRAME_SAMPLING_COVERAGE

		hr = DwmSetPresentParameters(m_hWnd, &dwm_pp);
		ASSERT(hr >= 0);
	}
#endif
	return 0;
}

void HwndSource::Redraw()
{
	Graphics* graphics = new Graphics(NULL);//pGraphicsO);
	graphics->m_pO = m_pGraphicsO;
	graphics->m_p3D = m_pGraphics3D;
#if 0
	graphics->m_invalidRegion = m_invalidRegion;
#endif

//	m_pGraphicsO->m_clipRect = LDraw::RectF(0, 0, m_windowRect.Width, m_windowRect.Height);

//	MessageBeep(-1);
//	TRACE("Redraw %d\n", g_redrawCount);
	g_redrawCount++;

	//if (g_PresentEvent == NULL)
	{
		m_pClient->Redraw(graphics);
	}
}

void HwndSource::RenderToTarget()
{
	ASSERT(!m_renderTargetUpdated);
	m_renderTargetUpdated = true;

#ifndef AMIGA
//	std::printf("UpdateBitmap()...");
//	std::fflush(stdout);
	/*
	_CrtMemState startState;
	_CrtMemCheckpoint(&startState);
	*/

	LDraw::Bitmap* bitmap = NULL;

#if WIN32

	HDC hDC = NULL;
	HBITMAP hOldBitmap = NULL;

	if (UseDirectDraw)
	{
		if (m_d3dDevice9)
		{
		//	bitmap = MSWindows::D3D_GetBitmap(m_d3dSurface);
		}
	}
	else
	{
		if (m_hBitmap)
		{
			ASSERT(0);
			bitmap = new LDraw::Bitmap(m_hBitmap, NULL);
			hDC = MSWindows::CreateCompatibleDC(NULL);
			hOldBitmap = (HBITMAP)MSWindows::SelectObject(hDC, (HGDIOBJ)m_hBitmap);
		}
	}

	if (bitmap)
	{
		if (m_bAlpha)
		{
			bitmap->SetPixelFormat(LDraw::PixelFormat_t::RGBAP_32);
		}
	}

#elif AMIGA

	if (m_pBitmap)
	{
		bitmap = new LDraw::Bitmap(m_pBitmap);
	}

#elif __APPLE__

	GrafPtr port = GetWindowPort(m_hWnd);
	if (LockPortBits(port) == noErr)
	{
		PixMapHandle pixmap = GetPortPixMap(port);
		if (pixmap)
		{
			bitmap = new LDraw::Bitmap(pixmap);
		}
	}

#endif

	if (true || bitmap)
	{
		IDirect3DSurface9* surface = NULL;
		m_d3dSwapChain9->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &surface);

		m_d3dDevice9->SetRenderTarget(0, surface);
		m_d3dDevice9->SetDepthStencilSurface(m_depthStencilSurface9);

		{
			D3DVIEWPORT9 viewport;
			viewport.X = 0;
			viewport.Y = 0;
			viewport.Width = m_d3dpp9.BackBufferWidth;
			viewport.Height = m_d3dpp9.BackBufferHeight;
			viewport.MinZ = 0;
			viewport.MaxZ = 1;
			HRESULT hr = m_d3dDevice9->SetViewport(&viewport);
			ASSERT(SUCCEEDED(hr));
		}

	//	LDraw::GraphicsO* pGraphicsO = m_pGraphicsO;//new LDraw::GraphicsO(bitmap);
#if 0
		if (false)
		{
			pGraphicsO->m_p->m_hDC = hDC;
		//	ASSERT((uint8*)hDC < heap->m_data || (uint8*)hDC >= heap->m_data + heap->m_size*2);
			pGraphicsO->SetBitmap(bitmap);
			pGraphicsO->SetDepthBuffer((uint8*)m_depthBuffer);
			pGraphicsO->SetStencilBuffer((uint8*)m_stencilBuffer);
		}
#endif

		Redraw();

	//	Graphics* graphics = new Graphics(NULL);//pGraphicsO);
	//	graphics->m_pO = m_pGraphicsO;
		m_pGraphicsO->m_clipRect = LDraw::RectF(0, 0, m_windowRect.Width, m_windowRect.Height);

		/*
		Graphics* graphics = new Graphics(NULL);//pGraphicsO);
		graphics->m_pO = m_pGraphicsO;
#if 0
		graphics->m_invalidRegion = m_invalidRegion;
#endif

		m_pGraphicsO->m_clipRect = LDraw::RectF(0, 0, m_windowRect.Width, m_windowRect.Height);
		*/

	//	graphics.FillRectangle(&LDraw::SolidBrush(LDraw::Color(0, 0, 255)), 0, 0, 400, 1);

	//	LDraw::RectI bounds;
	//	m_invalidRegion->GetRegionRect(&bounds);

#if 0
	//	LDraw::Region pOldRgn;
	//	graphics.GetClip(&pOldRgn);
#if USE_CLIPPING
		graphics->PushClip();
	//	graphics->m_p->SetClip(m_invalidRegion);
#if 1	// TODO, had this
		if (false)
		graphics->m_p->SetClip(m_invalidRegion);
#endif
#endif
#endif
	//	graphics.SetClip(clip, LDraw::CombineModeIntersect);
	//	graphics.m_clip.m_p = CreateRectRgn(clip.X, clip.Y, clip.GetRight(), clip.GetBottom());

//		graphics.FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 0, 0, 255)), 0, 0, 80, 80);

#if 0
		if (m_bAlpha)
		{
			/*
			graphics.SetCompositingMode(LDraw::CompositingModeSourceCopy);
			graphics.FillRectangle(&LDraw::SolidBrush(LDraw::Color(0, 0, 0, 0)), bounds);
			graphics.SetCompositingMode(LDraw::CompositingModeSourceOver);
			*/
			graphics->Clear(LDraw::Color(0, 0, 0, 0));
		}
#endif

#if 0
		graphics.SetSmoothingMode(LDraw::SmoothingModeAntiAlias);
#endif

		Visual* p = m_pClient->GetVisualTree();

		HRESULT hr;

		float scale = pixelsPerInch / 96;

		if (m_hRC)
		{
		//	LDraw::MakeCurrent(m_pGraphicsO);

		//	glClearColor(0, 0, 0, 0);
		//	m_pGraphics3D->DepthMask(true);
		//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//	glDisable(GL_DEPTH_TEST);
		//	glDepthMask(false);

			m_pGraphics3D->SetMatrixMode(GL_PROJECTION);
			m_pGraphics3D->LoadIdentity();
			glOrtho(0, m_windowRect.Width, m_windowRect.Height, 0, -1/*zNear*/, 1/*zFar*/);

			m_pGraphics3D->SetMatrixMode(GL_MODELVIEW);
			m_pGraphics3D->LoadIdentity();

			//glCullFace(GL_CULL_NONE);
		}
		else// if (m_d3dDevice)
		{
			if (false)
			{
				/*
				if (true)
				{
					MSWindows::D3D_Clear(m_d3dDevice);
				}
				*/

			//	m_d3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);

				D3DXMATRIX mat;

				MSWindows::D3D_BeginScene(m_d3dDevice9);

				//D3DXMatrixOrthoLH(&mat, 800, 600, 0.1, 2);
				D3DXMatrixOrthoOffCenterLH(&mat, 0, m_windowRect.Width, m_windowRect.Height, 0, -1/*zNear*/, 1/*zFar*/);
				hr = m_d3dDevice9->SetTransform(D3DTS_PROJECTION, &mat);
				ASSERT(SUCCEEDED(hr));

				D3DXMatrixIdentity(&mat);
				hr = m_d3dDevice9->SetTransform(D3DTS_VIEW, &mat);
				ASSERT(SUCCEEDED(hr));

				D3DXMatrixIdentity(&mat);
				hr = m_d3dDevice9->SetTransform(D3DTS_WORLD, &mat);
				ASSERT(SUCCEEDED(hr));
			}
			else
			{
				m_d3dDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

				m_pGraphics3D->SetMatrixMode(GL_PROJECTION);
				//m_pGraphics3D->LoadIdentity();
				m_pGraphics3D->LoadMatrixf(LDraw::matrix4f::getOrtho(0, m_windowRect.Width, m_windowRect.Height, 0, -1/*zNear*/, 1/*zFar*/));

				m_pGraphics3D->SetMatrixMode(GL_MODELVIEW);
			//	m_pGraphics3D->LoadIdentity();
				m_pGraphics3D->LoadMatrixf(LDraw::matrix4f::getScale(scale, scale, 1));
			}
		}

		uint clearFlags = GL_COLOR_BUFFER_BIT;
		if (m_depthStencilSurface9) clearFlags |= GL_DEPTH_BUFFER_BIT;
	//	m_pGraphics3D->Clear(clearFlags);

		m_pGraphics3D->DepthMask(false);
		m_pGraphics3D->Disable(GL_DEPTH_TEST);

		if (p)
		{
#if 0
			if (false)
			graphics->TranslateTransform(-p->m_expandedBBox.X, -p->m_expandedBBox.Y);	// ???
#endif
		}

	//	graphics->ScaleTransform(scale, scale);

#if 0
		if (false)
		{
		LDraw::PointF points[4] =
		{
			LDraw::PointF(0, 0),
			LDraw::PointF(300, 0),
			LDraw::PointF(300, 200),
			LDraw::PointF(0, 200),
		};

		LDraw::Color colors[2] =
		{
			LDraw::Color(255, 255, 0, 0),
			LDraw::Color(255, 255, 255, 0),
		};

		float positions[2] =
		{
			0,
			1,
		};

		LDraw::LinearGradientBrush* brush = new LDraw::LinearGradientBrush(LDraw::PixelFormat_t::RGBAP_32, LDraw::PointF(40, 40), LDraw::PointF(100, 40));
		brush->SetInterpolationColors(colors, positions, 2);

	//	graphics->RotateTransform(30);
		graphics->TranslateTransform(200, 50);
		graphics->FillPolygon(brush, points, 4);
	//	graphics->FillPolygon(new LDraw::SolidBrush(LDraw::Color(255, 0, 0, 255)), points, 3);
		}
#endif

//		m_pClient->get_VisualTree()->RenderNoTransform(graphics);

#if 1

#if 0
		Visual* current = m_redrawList;
		while (current)
		{
			ASSERT(current->m_bRedraw);

			/*
			LDraw::Matrix3f* mat = new LDraw::Matrix3f(current->GetParentToElementTransformMatrix()->m_matrix);
			UIElement* parent = current->GetRParent();
			while (parent)
			{
				mat->m_matrix = mat->m_matrix * parent->GetParentToElementTransformMatrix()->m_matrix;

				parent = parent->GetRParent();
			}
			*/

			if (!current->m_bRenderValid)
			{
				__release<LDraw::Matrix3f> transform = current->GetWindowToElementTransformMatrix();
				ASSERT(transform.m_p);

			if (false)
				graphics->PushTransform();
			if (false)
				graphics->m_p->SetTransform(transform);
			
			graphics->m_pO->SetTransform(transform);

				current->RenderNoTransform(graphics);

				graphics->PopTransform();
			}

			current->m_bRedraw = false;

			Visual* next = current->m_redrawNext;
			current->m_redrawNext = NULL;

			current = next;
			m_redrawList = next;
		}
#else

		/*
		LDraw::Commands* m_pDrawCommands = new LDraw::Commands;
		LDraw::GraphicsMetafile* pMetafile = new LDraw::GraphicsMetafile(graphics->m_pO->m_device, graphics->m_pO->m_bufferData, m_pDrawCommands);
		{
			Graphics* graphics2 = new Graphics(pMetafile);
			graphics2->m_pO = graphics->m_pO;

			m_pClient->get_VisualTree()->RenderNoTransform(graphics2);

		}
		*/

		if (m_d3dDevice9)
		{
			MSWindows::D3D_BeginScene(m_d3dDevice9);
		}

		// TODO: m_pClient->GetDrawCommands();

	//	int t1 = GetTickCount();

		/*
		if (g_PresentEvent)
		{
			g_pDrawCommand->Render(m_pGraphicsO);
		}
		else
		*/
		{
			ASSERT(m_pClient->GetVisualTree()->m_pDrawCommands);
			m_pGraphicsO->SetTransform(LDraw::Matrix3f::GetScale(scale, scale));
			m_pGraphicsO->RenderCommands(m_pClient->GetVisualTree()->m_pDrawCommands);
		}

	//	int t2 = GetTickCount();
	//	TRACE("UpdateBitmap: %f s\n", (double)(t2-t1)/1000);

		if (m_d3dDevice9)
		{
			MSWindows::D3D_EndScene(m_d3dDevice9);
		}

		m_hBitmapUpdated = false;

#endif

	//	MessageBeep(-1);
	//	int vertices = graphics->m_p->m_bufferData->m_vertexOffsetInBytes / (8*4);
	//	TRACE("vertices: %d\n", vertices);

#endif

	//	m_pClient->_OnRender(graphics);

#if 0
		graphics->m_invalidRegion = NULL;
#endif
#if 0
		graphics->PopClip();
#endif

		surface->Release();
	}

	if (UseDirectDraw)
	{
		if (bitmap)
		{
			ASSERT(0);
		//	MSWindows::D3D_UnlockBitmap(m_d3dSurface, bitmap);
		//	m_dds->Unlock(sd.lpSurfacePointer, 0, NULL);
		}
	}

	if (hDC)
	{
		SelectObject(hDC, (HGDIOBJ)hOldBitmap);
		DeleteDC(hDC);
	}

#if __APPLE__
	UnlockPortBits(port);
	}
#endif

	/*
	_CrtMemState endState;
	_CrtMemCheckpoint(&endState);

	_CrtMemState diffState;
	int bIsDifferent = _CrtMemDifference(&diffState, &startState, &endState);

	if (bIsDifferent)
	{
	//	_CrtMemDumpStatistics(&diffState);
	}
	*/

#endif
}

	/*
void HwndSource::OnArrange(LDraw::SizeD finalSize)
{
//	Control::OnArrange(finalSize);

	int intWidth = ceil(finalSize.Width);
	int intHeight = ceil(finalSize.Height);

#if WIN32
	SetWindowPos(m_hWnd, NULL, 0, 0, intWidth, intHeight, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
#elif AMIGA
	ChangeWindowBox(m_hWnd, m_hWnd->LeftEdge, m_hWnd->TopEdge, intWidth, intHeight);
#endif
}
*/

/*
UINT HwndSource::SetTimer(UINT ms, System::IEventTarget* target)
{
	//ASSERT(m_hWnd);

	if (target == NULL) return 0;

	++m_nTimerID;

	TimerTarget* p = new TimerTarget;
	p->m_ms = ms;
	p->m_target = target;

	m_timerListeners[m_nTimerID] = p;

#if WIN32
	if (m_hWnd)
	{
		::SetTimer(m_hWnd, m_nTimerID, ms, NULL);
	}
#endif

	return m_nTimerID;
}
*/

#if WIN32

LRESULT HwndSource::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	bool bHandled = true;
	switch (uMsg)
	{
#if 0
	case WM_TIMER:
		{
			UINT wTimerID = wParam;
			TimerTarget* p = m_timerListeners[wTimerID];

			System::Event* evt = new System::Event;
			evt->InitEvent(WSTR("timer"), false, false);

			/*bool bDefault =*/ p->m_target->dispatchEvent(evt);
		}
		break;
#endif

	case WM_CREATE:
		return OnCreate(uMsg, wParam, lParam, bHandled);

	case WM_DESTROY:
		OnDestroy(uMsg, wParam, lParam, bHandled);
		break;

	case WM_NCDESTROY:
		OnNcDestroy(uMsg, wParam, lParam, bHandled);
		break;

	case WM_CLOSE:
		OnClose();
		break;

	case WM_NCACTIVATE:
		{
			MSWindows::BOOL fActive = (MSWindows::BOOL)wParam;
			if (!fActive)
			{
				if (UseDWM)
				{
					// paint the non-client area
					DefWindowProc(uMsg, wParam, lParam);
				}
				else
				{
				// Don't repaint the non-client area
				}

				return true;	// Proceed with default processing
			}
			//return MSWindows::DefWindowProcA(hWnd, uMsg, wParam, lParam);

			return 0;	// Return value doesn't matter
		}
		break;

	case WM_NCPAINT:
		{
			MSWindows::HRGN hrgn = (MSWindows::HRGN) wParam;   // handle of update region 

			if (UseDWM)
			{
				return DefWindowProc(uMsg, wParam, lParam);
			}
			else
			{
				// Don't paint anything in the non-client area
				return 0;
			}
		}
		break;

	case WM_NCCALCSIZE:
		{
		//	return DefWindowProc(uMsg, wParam, lParam);

		//	BOOL fCalcValidRects = (BOOL) wParam;        // valid area flag 
		//	LPNCCALCSIZE_PARAMS lpncsp = (LPNCCALCSIZE_PARAMS) lParam;  // size calculation data 
			MSWindows::BOOL fCalcValidRects = (MSWindows::BOOL)wParam;        // valid area flag 

			MSWindows::LPRECT lpncsp = (MSWindows::LPRECT)lParam;               // new window coordinates 

			// Client Area covers entire window area

			if (fCalcValidRects)
			{
				return WVR_REDRAW;
			}
			else
			{
				return 0;
			}
		}
		break;

	case WM_PAINT:
		return OnPaint(uMsg, wParam, lParam, bHandled);

	case WM_PRINTCLIENT:
		return OnPrintClient(uMsg, wParam, lParam, bHandled);

	case WM_GETTEXT:
		return OnGetText(uMsg, wParam, lParam, bHandled);

	case WM_GETTEXTLENGTH:
		return OnGetTextLength(uMsg, wParam, lParam, bHandled);

	case WM_GETMINMAXINFO:
		return OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled);

	case WM_MOVE:
		return OnMove(uMsg, wParam, lParam, bHandled);

	case WM_SIZE:
		return OnSize(uMsg, wParam, lParam, bHandled);

	case WM_SIZING:
		return OnSizing(uMsg, wParam, lParam, bHandled);

	case WM_CONTEXTMENU:
		return OnContextMenu(uMsg, wParam, lParam, bHandled);

	case WM_LBUTTONDOWN:
		return OnLButtonDown(uMsg, wParam, lParam, bHandled);

	case WM_RBUTTONDOWN:
		return OnRButtonDown(uMsg, wParam, lParam, bHandled);

	case WM_LBUTTONDBLCLK:
		return OnLButtonLDblClk(uMsg, wParam, lParam, bHandled);

	case WM_LBUTTONUP:
		return OnLButtonUp(uMsg, wParam, lParam, bHandled);

	case WM_RBUTTONUP:
		return OnRButtonUp(uMsg, wParam, lParam, bHandled);

	case WM_MOUSEMOVE:
		return OnMouseMove(uMsg, wParam, lParam, bHandled);

	case WM_SETCURSOR:
		return OnSetCursor(uMsg, wParam, lParam, bHandled);

	case WM_SYSKEYDOWN:
		// TODO, do more here
		return OnKeyDown(uMsg, wParam, lParam, bHandled);

	case WM_KEYDOWN:
		return OnKeyDown(uMsg, wParam, lParam, bHandled);

	case WM_CHAR:
		return OnChar(uMsg, wParam, lParam, bHandled);

	case WM_MOUSELEAVE:
		OnMouseLeave();
		break;

	case WM_CAPTURECHANGED:
		OnCaptureChanged(uMsg, wParam, lParam, bHandled);
		break;

	case WM_ACTIVATE:
		OnActivate(uMsg, wParam, lParam, bHandled);
		break;

	case WM_ACTIVATEAPP:
		OnActivateApp(uMsg, wParam, lParam, bHandled);
		break;

#ifdef WINTAB
	case WT_PACKET:
		OnTabPacket(uMsg, wParam, lParam, bHandled);
		break;

	case WT_PROXIMITY:
		OnTabProximity(uMsg, wParam, lParam, bHandled);
		break;
#endif

		// Vista
	case WM_DWMCOMPOSITIONCHANGED:
		OnDwmCompositionChanged();
		break;

	default:
		return DefWindowProc(uMsg, wParam, lParam);
	}
	return 0;
}

LRESULT HwndSource::DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return MSWindows::DefWindowProcW(m_hWnd, uMsg, wParam, lParam);
}

LRESULT HwndSource::OnNcDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	OnDestroyed();

	if (m_d3dSwapChain9)
	{
		m_d3dSwapChain9->Release();
		m_d3dSwapChain9 = NULL;
	}

	/*
	if (m_d3dSurface)
	{
		MSWindows::D3D_ReleaseSurface(m_d3dSurface);
		m_d3dSurface = NULL;
	}
	*/

	/*
	if (m_d3dDevice9)
	{
		MSWindows::D3D_ReleaseDevice(m_d3dDevice9);
		m_d3dDevice9 = NULL;
	}
	*/

	// Remove us from windowlist
	pLayoutManager->RemoveWindow(this);
	/*
	WindowObject** ppPrevWindow = &pLayoutManager->m_windowList;
	WindowObject* pWindow = pLayoutManager->m_windowList;
	while (pWindow)
	{
		if (pWindow == this)
		{
			(*ppPrevWindow)->m_pNextWindow = pWindow->m_pNextWindow;
			break;
		}

		ppPrevWindow = pWindow->m_pNextWindow;
		pWindow = pWindow->m_pNextWindow;
	}
	*/

	return 0;
}

void HwndSource::OnDwmCompositionChanged()
{
}

void HwndSource::SetLayeredWindowBitmap()
{
	MSWindows::HDC hDCScreen = MSWindows::GetDC(NULL);

	MSWindows::HDC hDC = MSWindows::CreateCompatibleDC(hDCScreen);

	HBITMAP hOldBitmap = (HBITMAP)MSWindows::SelectObject(hDC, (void*)m_hBitmap);

	int opacity = m_pClient->GetVisualTree()->get_Opacity()*255;
	if (opacity < 0) opacity = 0;
	else if (opacity > 255) opacity = 255;

	MSWindows::BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = opacity;
	bf.AlphaFormat = AC_SRC_ALPHA;

	MSWindows::RECT wrect;
	MSWindows::GetWindowRect(m_hWnd, &wrect);

	MSWindows::POINT ptDest;
	ptDest.x = wrect.left;
	ptDest.y = wrect.top;

	MSWindows::SIZE size;
	size.cx = wrect.right-wrect.left;
	size.cy = wrect.bottom-wrect.top;

	MSWindows::POINT ptSrc;
	ptSrc.x = 0;
	ptSrc.y = 0;

	if (!MSWindows::UpdateLayeredWindow(m_hWnd,
		hDCScreen,//HDC hdcDst,
		&ptDest,
		&size,
		hDC,
		&ptSrc,
		0,//COLORREF crKey,
		&bf,//BLENDFUNCTION* pblend,
		ULW_ALPHA//DWORD dwFlags
		))
	{
		TRACE("UpdateLayeredWindow() failed\n");
	}

//	offdc.SelectBitmap(hOldBitmap);

	MSWindows::SelectObject(hDC, (void*)hOldBitmap);
	MSWindows::DeleteDC(hDC);

	MSWindows::ReleaseDC(NULL, hDCScreen);
}

LRESULT HwndSource::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	HDC hDC;
	if (!GetUpdateRect(m_hWnd, NULL, false))
	{
		ASSERT(0);
		return 0;
	}

	MSWindows::PAINTSTRUCT ps;
	MSWindows::BeginPaint(m_hWnd, &ps);
	hDC = ps.hdc;

	if (!m_locked && g_uiLocked == 0)
	{
		if (!m_renderTargetUpdated)
		{
		//	m_renderTargetUpdated = false;
			RenderToTarget();

		//	MSWindows::D3D_Present(m_d3dSwapChain9, &ps.rcPaint, &ps.rcPaint, m_hWnd);
			MSWindows::D3D_Present(m_d3dSwapChain9, NULL, NULL, m_hWnd);
		//	g_presented(NULL);
		}
	}

#if 0
	/*
	int bitspixel = GetDeviceCaps(offdc, BITSPIXEL);
	int numcolors = GetDeviceCaps(offdc, NUMCOLORS);

	SelectObject(offdc, GetStockObject(NULL_PEN));

	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			int r = y;
			int g = x;
			int b = 0;

			HBRUSH hBrush = CreateSolidBrush(RGB(r, g, b));

			HBRUSH hOldBrush = (HBRUSH)SelectObject(offdc, hBrush);

		//	int success = ::Rectangle(offdc, x, m_lpBmi->biHeight - y - 1, x+1, m_lpBmi->biHeight - y - 1 + 1);
			int success = ::Rectangle(offdc, 0, 0, 1000, 1000);

			numcolors = GetDeviceCaps(offdc, NUMCOLORS);

			SelectObject(offdc, hOldBrush);
			DeleteObject(hBrush);
		}
	}

	numcolors = GetDeviceCaps(offdc, NUMCOLORS);

	SelectObject(offdc, (void*)hOldBitmap);
	DeleteDC(offdc);

	DWORD value = *(DWORD*)m_bmBits;
	*/

	if (UseDirectDraw)
	{
		/*
		LDraw::RectI wrect;
		GetWindowRect(&wrect);

		BltPrimary(wrect.X, wrect.Y, m_dds, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top);
		*/
	}
	else
	{
	//	CPaintDC dc(m_hWnd);
		//m_hdc = dc;
		HDC dc = ps.hdc;

		HDC offdc;
		offdc = CreateCompatibleDC(dc);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(offdc, (void*)m_hBitmap);

		BitBlt(dc, 0, 0, m_lpBmi->biWidth, m_lpBmi->biHeight, offdc, 0, 0, SRCCOPY);

		SelectObject(offdc, (void*)hOldBitmap);
		DeleteDC(offdc);
	}
#endif

	EndPaint(m_hWnd, &ps);

	return 0;
}

LRESULT HwndSource::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	// Do everything in OnPaint
	return false;
}

LRESULT HwndSource::OnPrintClient(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	HDC hDC = (HDC)wParam;

	if (!m_renderTargetUpdated)
	{
		RenderToTarget();
	}
	UpdateHBITMAP();

	if (m_hBitmap)
	{
		MSWindows::HDC hSrcDC = MSWindows::CreateCompatibleDC(hDC);
		HBITMAP hOldBitmap = (HBITMAP)MSWindows::SelectObject(hSrcDC, (void*)m_hBitmap);

		BitBlt(hDC, 0, 0, m_windowRect.Width, m_windowRect.Height, hSrcDC, 0, 0, SRCCOPY);

		SelectObject(hSrcDC, hOldBitmap);
		DeleteDC(hSrcDC);
	}

	return 0;
}

LRESULT HwndSource::OnGetText(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	int maxlen = wParam-1;
	WCHAR* buffer = (WCHAR*)lParam;
	
	StringW* title = m_pClient->GetTitle();
	if (title)
	{
		wcsncpy(buffer, title->c_str(), maxlen);
		buffer[maxlen] = 0;
	}
	else
		buffer[0] = 0;

	return wcslen(buffer);
}

LRESULT HwndSource::OnGetTextLength(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	StringW* title = m_pClient->GetTitle();
	if (title)
	{
		return title->Length();	// TODO, c_length
	}
	else
		return 0;
}

LRESULT HwndSource::OnDDEExecute(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{

#if 0
	//::MessageBox(NULL, "OnDDExecute", "", MB_OK);

	// unpack the DDE message
	UINT unused;
	HGLOBAL hData;
	UnpackDDElParam(WM_DDE_EXECUTE, lParam, &unused, (UINT*)&hData);

	// get the command string
	TCHAR szCommand[_MAX_PATH * 2];
	LPCTSTR lpsz = (LPCTSTR)GlobalLock(hData);
	lstrcpyn(szCommand, lpsz, _countof(szCommand));
	GlobalUnlock(hData);

	// acknowledge now - before attempting to execute
	::PostMessageA((HWND)wParam, WM_DDE_ACK, (WPARAM)m_hWnd,
		ReuseDDElParam(lParam, WM_DDE_EXECUTE, WM_DDE_ACK,
		(UINT)0x8000, (UINT)hData));

	// don't execute the command when the window is disabled
	if (!IsWindowEnabled())
	{
		TRACE("Warning: DDE command '%s' ignored because window is disabled.\n",
			szCommand);
		return 0;
	}

// dispatch dom event

	ASSERT(0);
#if 0
	ILXUIDocument* document;
	static_cast<T*>(this)->get_ownerDocument(&document);

	ILDOMDocumentEvent* documentEvent = dynamic_cast<ILDOMDocumentEvent*>(document);
	ASSERT(documentEvent != NULL);

	ILDOMEvent* evt;
	documentEvent->createEvent(L"", &evt);

	evt->initEvent(L"ddecommand",
		true,	// bubbles
		true	// cancelable
		);
#endif

	ASSERT(0);
#if 0
	SetProperty(evt, L"value", _variant_t(_bstr_t(szCommand)));
#endif

	ASSERT(0);
#if 0
	CComQIPtr<ILDOMEventTarget> eventTarget(static_cast<T*>(this));

	VARIANT_BOOL doDefault;
	eventTarget->dispatchEvent(evt, &doDefault);
	if (doDefault)
	{
#if 0
		// execute the command
		if (!gApp->OnDDECommand(szCommand))
			TRACE("Error: failed to execute DDE command '%s'.\n", szCommand);
#endif
	}
#endif
#endif

	return 0;
}

LRESULT HwndSource::OnDDETerminate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	//::MessageBox(NULL, "OnDDETerminate", "", MB_OK);

#if 0
	::PostMessageA((HWND)wParam, WM_DDE_TERMINATE, (WPARAM)m_hWnd, lParam);
#endif
	return 0;
}

#ifdef WINTAB

HANDLE HwndSource::InitTablet(HWND hWnd)
{
	if (g_bTabletInstalled)
	{
		MSWindows::LOGCONTEXT lcMine;           // The context of the tablet

		//TABLET: get current settings as a starting point for this context of the tablet.
		//WTInfo(WTI_DEFCONTEXT, 0, &lcMine);	// default settings may be different to current settings
		_WTInfo(WTI_DEFSYSCTX, 0, &lcMine);	// current settings as set in control panel

		lcMine.lcOptions |= CXO_MESSAGES;	// keep existing options and make sure message handling is on for this context
		//TABLET: PACKETDATA must be defined FIRST before including pktdef.h. See the header file of this class for more details
		lcMine.lcPktData = PACKETDATA;	// these settings MUST be defined in the pktdef.h file, see notes
		lcMine.lcPktMode = PACKETMODE;
		lcMine.lcMoveMask = PACKETDATA;

		// We want to receive in full resolution
		lcMine.lcOutExtX = lcMine.lcInExtX;
		lcMine.lcOutExtY = lcMine.lcInExtY;

		m_tabletExt.Width = lcMine.lcOutExtX;
		m_tabletExt.Height = lcMine.lcOutExtY;

		return _WTOpen(hWnd, &lcMine, true);
	}
	return NULL;
}

BOOL HwndSource::GetTabState(LPARAM lParam, WPARAM wParam, UINT& nTabPressure, int& nTabAltitude, int& nTabTwist, int& nTabCompass, UINT& nTabCursor)
{
	//	if (! _WTPacket) return FALSE;
	
	//TABLET: Only return TRUE if something has changed
	MSWindows::BOOL bReturn = false;
	MSWindows::PACKET	pkt;	// the current packet
	int nMaxPkts = 1;
	
	if (_WTPacket((MSWindows::HCTX)lParam, wParam, &pkt))
	{
		UINT  		prsOld = t_prsNew;
		UINT  		curOld = t_curNew;
	//	ORIENTATION ortOld = t_ortNew;

		t_curNew = pkt.pkCursor;
		t_prsNew = pkt.pkNormalPressure;
	//	t_ortNew = pkt.pkOrientation;
		pkt.pkY = m_tabletExt.Height - pkt.pkY - 1;

		TRACE("Tablet xy: %d, %d\n", pkt.pkX, pkt.pkY);
		
		nTabPressure = t_prsNew;
//		nTabCompass = t_ortNew.orAzimuth ;	//Clockwise rotation about z-azis, 0 is north, 900 is east, 1800 is south and 2700 is west, 3599 is nearly north again.
//		nTabAltitude = t_ortNew.orAltitude ;	//Tilt.  If Wacom then Positive = normal tip, negative = eraser tip
//		nTabTwist = t_ortNew.orTwist ;	//I don't think it's used on Wacom pen tablets
		nTabCursor = t_curNew;	//1=normal 2=eraser.
		
		// If any state changes return TRUE
		if (t_prsNew != prsOld ||
		//	t_ortNew.orAzimuth != ortOld.orAzimuth ||
		//	t_ortNew.orAltitude != ortOld.orAltitude ||
		//	t_ortNew.orTwist != ortOld.orTwist ||
			//t_curNew != curOld ||
			m_pntMouseLoc.X != pkt.pkX ||
			m_pntMouseLoc.Y != pkt.pkY)
		{
			bReturn = true;
		}

		m_pntMouseLoc.X = pkt.pkX;
		m_pntMouseLoc.Y = pkt.pkY;
	}

//	_WTPacket((HCTX)lParam, wParam, NULL);	// Flush queue

	return bReturn;
}

LRESULT HwndSource::OnTabProximity(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (!m_locked && g_uiLocked == 0)
	{
		/*
		wParam
	 Contains the handle of the context that the cursor is entering or leaving.
	 
	  lParam
	 The low-order word is non-zero when the cursor is entering the context and zero when it
	 is leaving the context. The high-order word is non-zero when the cursor is leaving or
	 entering hardware proximity.
	 */

		BOOL isEnteringContext = LOWORD(lParam);
		BOOL isEnteringHardwareProximity = HIWORD(lParam);
	}

	return 0;
}

LRESULT HwndSource::OnTabPacket(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (!m_locked && g_uiLocked == 0)
	{
	//	WTQueuePackets(
		UINT nTabPressure = 0;	// 0 = nothing
		int nTabAlt = 0;	// Which way up for Wacom pens, negative = eraser, positive = normal tip
		int nTabTwist = 0;	// Spin about x axis, I don't think this is used on Wacom pens
		int nTabCompass = 0;	// 0 = North, 900 = east etc.
		UINT nTabCursor = 0;	// A number for the selected cursor or pointer, Wacom 1=normal, 2=eraser

		if (GetTabState(lParam, wParam, nTabPressure, nTabAlt, nTabTwist, nTabCompass, nTabCursor))
		{
			int gPressure = ((nTabPressure-g_nTabletMinPressure) * 1023)/(g_nTabletMaxPressure-g_nTabletMinPressure);
			int g_tabCursor = nTabCursor;

			LDraw::PointD screenpt(m_pntMouseLoc.X * 1600.0 / m_tabletExt.Width, m_pntMouseLoc.Y * 1200.0 / m_tabletExt.Height);

	#if 0
			POINT point;
			point.x = screenpt.X;
			point.y = screenpt.Y;
			::ScreenToClient(m_hWnd, &point);

			m_pClient->OnMouseMove(0/*nFlags*/, screenpt, point);
	#endif
			StylusPacket packet;
			packet.m_screenX = screenpt.X;
			packet.m_screenY = screenpt.Y;
			packet.m_pressure = (double)((nTabPressure-g_nTabletMinPressure))/(g_nTabletMaxPressure-g_nTabletMinPressure);

			list<IStylusPlugin*>::iterator it = m_stylusPlugins.begin();
			while (it != m_stylusPlugins.end())
			{
				(*it)->OnPacket(&packet);
				++it;
			}

	//		TRACE("Tab Packet, pressure: %d\n", gPressure);
		}
	}

	return 0;
}

#endif // WINTAB

#elif AMIGA

void HwndSource::SetMenu(struct Menu* pMenu)
{
	if (m_hWnd)
	{
		SetMenuStrip(m_hWnd, pMenu);

		if (m_pMenu)
			FreeMenus(m_pMenu);

		m_pMenu = pMenu;
	}
	else
	{
		if (m_pMenu)
			FreeMenus(m_pMenu);

		m_pMenu = pMenu;
	}
}

// static
bool HwndSource::staticIntuiMsgHandler(const struct IntuiMessage* pMsg, Object* userdata)
{
//	return reinterpret_cast<HwndSource*>(userdata)->IntuiMsgHandler(pMsg);
	return static_cast<HwndSource*>(userdata)->IntuiMsgHandler(pMsg);
}

bool HwndSource::IntuiMsgHandler(const struct IntuiMessage* pMsg)
{
	switch (pMsg->aos_Class)
	{
	case IDCMP_MOUSEBUTTONS:
		{
			UINT nFlags = 0;

			LDraw::PointD screenpt;
			screenpt.X = m_hWnd->MouseX + m_hWnd->LeftEdge;
			screenpt.Y = m_hWnd->MouseY + m_hWnd->TopEdge;

			LDraw::PointI point;
			point.X = screenpt.X - m_windowRect.X;
			point.Y = screenpt.Y - m_windowRect.Y;

			if (pMsg->Code == SELECTDOWN)
			{
			//	printf("down\n");
				m_pClient->OnButtonDown(nFlags, screenpt, point, 0, false);
			}
			else if (pMsg->Code == SELECTUP)
			{
			//	printf("up\n");
				m_pClient->OnButtonUp(nFlags, screenpt, point, 0);
			}
		//	else
		//		printf("IDCMP_MOUSEBUTTONS: %d\n", pMsg->Code);
		}
		break;

	case IDCMP_MOUSEMOVE:
		{
		//	printf("IDCMP_MOUSEMOVE...");
		//	fflush(stdout);

		/*
			LDraw::PointI point;
			point.X = m_hWnd->MouseX;
			point.Y = m_hWnd->MouseY;
			*/
			UINT nFlags = 0;

			LDraw::PointD screenpt;
			screenpt.X = m_hWnd->MouseX + m_hWnd->LeftEdge;
			screenpt.Y = m_hWnd->MouseY + m_hWnd->TopEdge;

			LDraw::PointI point;
			point.X = screenpt.X - m_windowRect.X;
			point.Y = screenpt.Y - m_windowRect.Y;

			bool bInsideWindow = point.X >= 0 && point.Y >= 0 && point.X < m_windowRect.Width && point.Y < m_windowRect.Height;
			if (bInsideWindow != m_pClient->m_bInsideWindow)
			{
				m_pClient->m_bInsideWindow = bInsideWindow;
			}

			/*
			LDraw::PointI screenpt = point;
			screenpt.X += m_hWnd->LeftEdge;// + m_hWnd->BorderLeft;
			screenpt.Y += m_hWnd->TopEdge;// + m_hWnd->BorderTop;
			*/

			m_pClient->OnMouseMove(nFlags, screenpt, point);

		//	OnSetCursor(point);

		//	printf("done\n");
		}
		break;

#if 0
	case IDCMP_VANILLAKEY:
		{
			OnVanillaKey(pMsg);
		}
		break;
#endif

	case IDCMP_RAWKEY:
		{
			OnRawKey(pMsg);
		}
		break;

#if 0
	case IDCMP_NEWSIZE:
		{
		//	printf("NEWSIZE %d, %d\n", m_hWnd->GZZWidth, m_hWnd->GZZHeight);

//			Render();
//			Draw();
		}
		break;
#endif

	case IDCMP_CHANGEWINDOW:
		{
			if (false)
			{
				if (m_pBitmap)
				{
					int destX = (m_windowRect.X - m_hWnd->LeftEdge);
					int destY = (m_windowRect.Y - m_hWnd->TopEdge);
					BltBitMapRastPort(m_pBitmap, 0, 0, m_hWnd->RPort, destX, destY, m_windowRect.Width, m_windowRect.Height, 0xC0);
				}
			}
			else
			{
				Render();
			}
		}
		break;

	case IDCMP_ACTIVEWINDOW:
		{
			OnActivate(true);
		}
		break;

	case IDCMP_INACTIVEWINDOW:
		{
			OnActivate(false);
		}
		break;

	case IDCMP_REFRESHWINDOW:
		{
			BeginRefresh(m_hWnd);

			if (false)
			{
				if (m_pBitmap)
				{
					int destX = (m_windowRect.X - m_hWnd->LeftEdge);
					int destY = (m_windowRect.Y - m_hWnd->TopEdge);
					BltBitMapRastPort(m_pBitmap, 0, 0, m_hWnd->RPort, destX, destY, m_windowRect.Width, m_windowRect.Height, 0xC0);
				}
			}
			else
			{
			//	Render();
				/*
				gfxMove(m_hWnd->RPort, 10, 10);
				const char* str = "Failed to allocate bitmap";
				gfxText(m_hWnd->RPort, str, strlen(str));
				*/
			}

			EndRefresh(m_hWnd, TRUE);
		}
		break;
	}

	return false;
}

#endif

#if WIN32

class Tablet
{
public:
	Tablet()
	{
		SetupWinTab();
	}
};

Tablet tablet;

LRESULT HwndSource::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	// Why oh why is this necessary ??
	StringW* title = m_pClient->GetTitle();
	if (title)
	{
		MSWindows::SetWindowTextW(m_hWnd, title->c_str());
	}

//	if (baseClass::OnCreate(uMsg, wParam, lParam, bHandled))
//		return -1;

	/*
	if (true)
	{
		MSWindows::BOOL value = false;
		MSWindows::DwmSetWindowAttribute(m_hWnd, MSWindows::DWMWA_FORCE_ICONIC_REPRESENTATION, &value, sizeof(MSWindows::BOOL));
	}
	*/

#if 0
	if (false)
	{
		MSWindows::DWMNCRENDERINGPOLICY value = DWMNCRP_DISABLED;
		HRESULT hr = MSWindows::DwmSetWindowAttribute(m_hWnd, MSWindows::DWMWA_NCRENDERING_POLICY, &value, sizeof(value));
		ASSERT(hr >= 0);
	}

	if (true)
	{
		MSWindows::HRESULT hr = MSWindows::DwmEnableMMCSS(true);
		ASSERT(hr >= 0);
	}

	if (true)
	{
// Negative margins have special meaning to DwmExtendFrameIntoClientArea.
   // Negative margins create the "sheet of glass" effect, where the client area
   //  is rendered as a solid surface with no window border.
		MSWindows::MARGINS margins = {-1};
		MSWindows::DwmExtendFrameIntoClientArea(m_hWnd, &margins);
	}
#endif

// Set up this at window creation
	MSWindows::GetCursorPos((MSWindows::POINT*)&m_oldpoint);
	MSWindows::ScreenToClient(m_hWnd, (MSWindows::POINT*)&m_oldpoint);

#ifdef WINTAB
	if (true)
	{
		t_hTablet = InitTablet(m_hWnd);
		if (t_hTablet)
		{
			_WTQueueSizeSet((MSWindows::HCTX)t_hTablet, 1);
		}
	}
#endif // WINTAB

#if 0
	::RegisterDragDrop(m_hWnd, m_pDropTarget);
#endif

#if 0
	EnableDocking(CBRS_ALIGN_TOP);	// Must have at least this for menu bar
#endif

	//TRACE("TODO, have this\n");
#if 0
	for (int i = 0; i < m_pClient->m_rchildList.size(); i++)
	{
		HwndSource* p = dynamic_cast<HwndSource*>(m_pClient->m_rchildList[i]);
		if (p)
		{
			p->Show();
		}
	}
#endif

	/*
	{
		map<UINT_PTR, TimerTarget*, less<UINT_PTR>, __gc_allocator>::iterator it = m_timerListeners.begin();
		while (it != m_timerListeners.end())
		{
			UINT_PTR nTimerID = (*it).first;

#if WIN32
			::SetTimer(m_hWnd, nTimerID, (*it).second->m_ms, NULL);
#endif

			++it;
		}
	}
	*/

	/*
	for (int i = 0; i < m_popups.size(); i++)
	{
		m_popups[i]->Show();
	}
	*/

	return 0;
}

LRESULT HwndSource::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (!m_locked && g_uiLocked == 0)
	{
		MSWindows::POINT point;
		point.x = (short)MSWindows::LoWORD(lParam);
		point.y = (short)MSWindows::HiWORD(lParam);
		UINT nFlags = wParam;
	//	if (wParam & MK_SHIFT) nFlags |= 1;
	//	if (wParam & MK_CONTROL) nFlags |= 2;

		MSWindows::POINT screenpt = point;
		MSWindows::ClientToScreen(m_hWnd, &screenpt);

		float rscale = 96 / pixelsPerInch;

		m_pClient->OnMouseDown(nFlags, LDraw::PointD(screenpt.x*rscale, screenpt.y*rscale), LDraw::PointD(point.x*rscale, point.y*rscale), 0, false);
	}

	return 0;
}

LRESULT HwndSource::OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (!m_locked && g_uiLocked == 0)
	{
		MSWindows::POINT point;
		point.x = (short)MSWindows::LoWORD(lParam);
		point.y = (short)MSWindows::HiWORD(lParam);
		UINT nFlags = wParam;
	//	if (wParam & MK_SHIFT) nFlags |= 1;
	//	if (wParam & MK_CONTROL) nFlags |= 2;

		MSWindows::POINT screenpt = point;
		MSWindows::ClientToScreen(m_hWnd, &screenpt);

		float rscale = 96 / pixelsPerInch;

		m_pClient->OnMouseDown(nFlags, LDraw::PointD(screenpt.x*rscale, screenpt.y*rscale), LDraw::PointD(point.x*rscale, point.y*rscale), 1, false);
	}

	return 0;
}

LRESULT HwndSource::OnLButtonLDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (!m_locked && g_uiLocked == 0)
	{
		MSWindows::POINT point;
		point.x = (short)MSWindows::LoWORD(lParam);
		point.y = (short)MSWindows::HiWORD(lParam);
		UINT nFlags = wParam;
	//	if (wParam & MK_SHIFT) nFlags |= 1;
	//	if (wParam & MK_CONTROL) nFlags |= 2;

		MSWindows::POINT screenpt = point;
		MSWindows::ClientToScreen(m_hWnd, &screenpt);

		float rscale = 96 / pixelsPerInch;

		m_pClient->OnMouseDown(nFlags, LDraw::PointD(screenpt.x*rscale, screenpt.y*rscale), LDraw::PointD(point.x*rscale, point.y*rscale), 0, true);
	}

	return 0;
}

LRESULT HwndSource::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (!m_locked && g_uiLocked == 0)
	{
		MSWindows::POINT point;
		point.x = (short)MSWindows::LoWORD(lParam);
		point.y = (short)MSWindows::HiWORD(lParam);
		UINT nFlags = wParam;
	//	if (wParam & MK_SHIFT) nFlags |= 1;
	//	if (wParam & MK_CONTROL) nFlags |= 2;

		MSWindows::POINT screenpt = point;
		MSWindows::ClientToScreen(m_hWnd, &screenpt);

		float rscale = 96 / pixelsPerInch;

		m_pClient->OnMouseUp(nFlags, LDraw::PointD(screenpt.x*rscale, screenpt.y*rscale), LDraw::PointD(point.x*rscale, point.y*rscale), 0);

		/*
		if (m_hWnd)	// Maybe it's been closed by the above function
		{
			Invalidate();	// TODO remove
		}
		*/
	}

	return 0;
}

LRESULT HwndSource::OnRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (!m_locked && g_uiLocked == 0)
	{
		MSWindows::POINT point;
		point.x = (short)MSWindows::LoWORD(lParam);
		point.y = (short)MSWindows::HiWORD(lParam);
		UINT nFlags = wParam;
	//	if (wParam & MK_SHIFT) nFlags |= 1;
	//	if (wParam & MK_CONTROL) nFlags |= 2;

		MSWindows::POINT screenpt = point;
		MSWindows::ClientToScreen(m_hWnd, &screenpt);

		float rscale = 96 / pixelsPerInch;
		/*
		screenpt.x *= rscale;
		screenpt.y *= rscale;
		point.x *= rscale;
		point.y *= rscale;
		*/

		m_pClient->OnMouseUp(nFlags, LDraw::PointD(screenpt.x*rscale, screenpt.y*rscale), LDraw::PointD(point.x*rscale, point.y*rscale), 1);

		/*
		if (m_hWnd)	// Maybe it's been closed by the above function
		{
			Invalidate();	// TODO remove
		}
		*/
	}

	return 0;
}

LRESULT HwndSource::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	int nHittest = MSWindows::LoWORD(lParam);  // hit-test code 
	int wMouseMsg = MSWindows::HiWORD(lParam); // mouse-message identifier 

	MSWindows::POINT point;
	MSWindows::GetCursorPos(&point);
	MSWindows::ScreenToClient(m_hWnd, &point);

	float rscale = 96 / pixelsPerInch;
	point.x *= rscale;
	point.y *= rscale;

	bHandled = OnSetCursor(LDraw::PointI(point.x, point.y));

	return bHandled;
}

void HwndSource::OnKeyDown(int vk)
{
	bool bControl = (GetAsyncKeyState(VK_CONTROL)>>15) & 1;
	bool bShift = (GetAsyncKeyState(VK_SHIFT)>>15) & 1;

	m_pClient->OnKeyDown(vk, bControl, bShift);
}

bool HwndSource::PreTranslateMessage(const MSWindows::MSG* msg)
{
	if (msg->message == WM_KEYDOWN || msg->message == WM_SYSKEYDOWN)
	{
#if 1
		IInputElement* p = dynamic_cast<VisualContentSource*>(m_pClient)->m_pElementFocus;
	//	if (p == NULL)
	//		p = m_pClient->get_VisualTree();

		if (p)
		{
		//	ASSERT(0);
#if 0
			KeyEvent* evt = new KeyEvent;
			evt->InitEvent(WSTR("accelerator"), true, true);
			evt->vk = msg->wParam;

			//int scancode = MapVirtualKey(msg->wParam, 0);
			uint8 scancode = (msg->wParam>>16) & 0xFF;
			uint16 ascii[2] = {0};
			uint8 keystate[256] = {0};
			ToAscii(msg->wParam, scancode, keystate, ascii, 0);
			evt->ascii = ascii[0];
			evt->bControl = (GetAsyncKeyState(VK_CONTROL)>>15) & 1;
			evt->bShift = (GetAsyncKeyState(VK_SHIFT)>>15) & 1;

	//		MessageBeep(-1);

			bool doDefault = p->dispatchEvent(evt);

			delete evt;

			return !doDefault;
#endif
		}
#endif
	}

	return false;
}

LRESULT HwndSource::OnCaptureChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	HWND hwndNewCapture = (HWND)lParam;    // handle of window to gain mouse capture

	if (hwndNewCapture != m_hWnd)
	{
		m_pClient->OnLostMouseCapture();
	}

	return 0;
}

LRESULT HwndSource::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	OnKeyDown(wParam);
	return 0;
}

LRESULT HwndSource::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	bool bControl = (GetAsyncKeyState(VK_CONTROL)>>15) & 1;
	bool bShift = (GetAsyncKeyState(VK_SHIFT)>>15) & 1;

	m_pClient->OnChar(wParam, bControl, bShift);
#if 0
	// TODO, not here
	if (m_pClient->m_pElementFocus)
	{
		CharEvent* evt = new CharEvent;
		evt->initEvent(OLESTR("char"), true, true);
		evt->cCharCode = wParam;    // character code 
		evt->bControl = (GetAsyncKeyState(VK_CONTROL)>>15) & 1;
		evt->bShift = (GetAsyncKeyState(VK_SHIFT)>>15) & 1;

		m_pClient->m_pElementFocus->dispatchEvent(evt);

		delete evt;
	}
#endif
	return 0;
}

#elif AMIGA

#if 0
void HwndSource::OnVanillaKey(const struct IntuiMessage* pMsg)
{
//	printf("Vanillakey %d\n", pMsg->Code);

	if (m_pClient->m_pElementFocus)
	{
		if (pMsg->Code == 127)	// Delete
		{
			KeyEvent* evt = new KeyEvent;
			evt->initEvent(OLESTR("keydown"), true, true);
			evt->vk = VKEY_DELETE;

			m_pClient->m_pElementFocus->dispatchEvent(evt);

			delete evt;
		}
		else
		{
			if (pMsg->Code == 8)	// Backspace
			{
				// Backspace is first sent as 'keydown', and then as 'char'
				KeyEvent* evt = new KeyEvent;
				evt->initEvent(OLESTR("keydown"), true, true);
				evt->vk = VKEY_BACK;

				m_pClient->m_pElementFocus->dispatchEvent(evt);

				delete evt;
			}

			CharEvent* evt = new CharEvent;
			evt->initEvent(OLESTR("char"), true, true);
			evt->cCharCode = pMsg->Code;

			m_pClient->m_pElementFocus->dispatchEvent(evt);

			delete evt;
		}
	}
}
#endif

void HwndSource::OnRawKey(const struct IntuiMessage* pMsg)
{
//	printf("Rawkey %d\n", pMsg->Code);

#if 1

	int vk;

	switch (pMsg->Code)
	{
	case 65: vk = VKEY_BACK; break;
	case 70: vk = VKEY_DELETE; break;
	case 80: vk = VKEY_F1; break;
	case 81: vk = VKEY_F2; break;
	case 82: vk = VKEY_F3; break;
	case 83: vk = VKEY_F4; break;
	case 84: vk = VKEY_F5; break;
	case 85: vk = VKEY_F6; break;
	case 86: vk = VKEY_F7; break;
	case 87: vk = VKEY_F8; break;
	case 88: vk = VKEY_F9; break;
	case 89: vk = VKEY_F10; break;
	case CURSORLEFT:	vk = VKEY_LEFT; break;
	case CURSORRIGHT: vk = VKEY_RIGHT; break;
	case CURSORUP: vk = VKEY_UP; break;
	case CURSORDOWN: vk = VKEY_DOWN; break;
	default:
		vk = 0;
	}

	UIElement* p = dynamic_cast<WindowBase*>(m_pClient)->m_pElementFocus;
	if (p == NULL)
		p = m_pClient;

//	printf("Code: %d, Qualifier: %d\n", pMsg->Code, pMsg->Qualifier);

	if (!(pMsg->Code & IECODE_UP_PREFIX))
	{
		bool bControl = (pMsg->Qualifier>>IEQUALIFIERB_CONTROL) & 1;
		bool bShift = (pMsg->Qualifier & (IEQUALIFIER_LSHIFT | IEQUALIFIER_RSHIFT)) != 0;

#if 1
		KeyEvent* evt = new KeyEvent;
		evt->InitEvent(new StringW(L"accelerator"), true, true);
		evt->vk = vk;

		evt->bControl = (pMsg->Qualifier>>IEQUALIFIERB_CONTROL) & 1;
		evt->bShift = (pMsg->Qualifier & (IEQUALIFIER_LSHIFT | IEQUALIFIER_RSHIFT)) != 0;
#endif

		InputEvent ie;
		ie.ie_Class = IECLASS_RAWKEY;
		ie.ie_SubClass = 0;
		ie.ie_Code = pMsg->Code;
		ie.ie_Qualifier = 0;

//		printf("Qualifier: %d\n", pMsg->Qualifier);

	/* recover dead key codes & qualifiers */
		ie.ie_EventAddress = (APTR *) *((ULONG *)pMsg->IAddress);
		char buffer[64];
		int actual = MapRawKey(&ie, buffer, 64, 0);

		evt->ascii = buffer[0];

		bool doDefault = p->dispatchEvent(evt);

		delete evt;

		if (doDefault)
		
		{
			/*
			KeyEvent* evt = new KeyEvent;
			evt->initEvent(OLESTR("keydown"), true, true);
			evt->vk = vk;
			evt->bControl = (pMsg->Qualifier>>IEQUALIFIERB_CONTROL) & 1;
			evt->bShift = (pMsg->Qualifier & (IEQUALIFIER_LSHIFT | IEQUALIFIER_RSHIFT)) != 0;

		//	printf("bControl: %d, bShift: %d\n", evt->bControl, evt->bShift);

			p->dispatchEvent(evt);

			delete evt;
			*/
			m_pClient->OnKeyDown(vk, bControl, bShift);

	// We don't send these as an ascii character (MSWindows automatically never does this)
			if (vk != VKEY_DELETE &&
				vk != VKEY_LEFT &&
				vk != VKEY_RIGHT &&
				vk != VKEY_UP &&
				vk != VKEY_DOWN)
			{
				ie.ie_Qualifier = pMsg->Qualifier;
				int actual = MapRawKey(&ie, buffer, 64, 0);

			//	printf("actual:%d: ", actual);

				//if (actual > 0)
				{
					for (int i = 0; i < actual; i++)
					{
						/*
						CharEvent* evt = new CharEvent;
						evt->initEvent(OLESTR("char"), true, true);
						evt->cCharCode = (uint8)buffer[i];
						evt->bControl = (pMsg->Qualifier>>IEQUALIFIERB_CONTROL) & 1;
						evt->bShift = (pMsg->Qualifier & (IEQUALIFIER_LSHIFT | IEQUALIFIER_RSHIFT)) != 0;

					//	printf("ascii: %d\n", evt->cCharCode);

						p->dispatchEvent(evt);

						delete evt;
						*/
					//	evt->bControl = (pMsg->Qualifier>>IEQUALIFIERB_CONTROL) & 1;
					//	evt->bShift = (pMsg->Qualifier & (IEQUALIFIER_LSHIFT | IEQUALIFIER_RSHIFT)) != 0;
						m_pClient->OnChar((uint8)buffer[i], bControl, bShift);
					}
				}
			//	printf("\n");
			}
		}
	}
	else
	{
//		printf("keyup\n");

		/*
		KeyEvent* evt = new KeyEvent;
		evt->initEvent(OLESTR("keyup"), true, true);
		evt->vk = vk;
		evt->bControl = (pMsg->Qualifier>>IEQUALIFIERB_CONTROL) & 1;
		evt->bShift = (pMsg->Qualifier & (IEQUALIFIER_LSHIFT | IEQUALIFIER_RSHIFT)) != 0;

		p->dispatchEvent(evt);

		delete evt;
		*/
		bool bControl = (pMsg->Qualifier>>IEQUALIFIERB_CONTROL) & 1;
		bool bShift = (pMsg->Qualifier & (IEQUALIFIER_LSHIFT | IEQUALIFIER_RSHIFT)) != 0;

		m_pClient->OnKeyUp(vk, bControl, bShift);
	}

#endif
}

#endif

bool HwndSource::OnSetCursor(LDraw::PointI point)
{
	if (!m_locked && g_uiLocked == 0)
	{

#if WIN32

#elif AMIGA
		if (m_pPointer)
		{
		//	DisposeObject(m_pPointer);
			m_pPointer = NULL;
		}
#endif

		float rscale = 96 / pixelsPerInch;

		Cursor* pCursor = m_pClient->OnSetCursor(LDraw::PointD(point.X*rscale, point.Y*rscale));
		if (pCursor)
		{
	#if WIN32

			HCURSOR hCursor = pCursor->GetHCursor();
			MSWindows::SetCursor(hCursor);

	#elif AMIGA

			// TODO
	#if 0
			pCursor->m_Visual->Measure(LDraw::SizeD(0, 0));
			pCursor->m_Visual->Arrange(pCursor->m_Visual->get_DesiredSize());
			int width  = pCursor->m_Visual->m_expandedBBox.Width;
			int height = pCursor->m_Visual->m_expandedBBox.Height;

			BitMap* pBitmap = p96AllocBitMap(width, height, 32, BMF_USERPRIVATE, NULL, RGBFB_R8G8B8A8);

			LDraw::Bitmap bitmap(pBitmap);
			{
				Graphics graphics(new LDraw::GraphicsO(&bitmap));
				graphics.TranslateTransform(-pCursor->m_Visual->m_expandedBBox.X, -pCursor->m_Visual->m_expandedBBox.Y);
				pCursor->m_Visual->Render(&graphics);
			}

			m_pPointer = NewObject(NULL, "pointerclass",
				(POINTERA_BitMap), (ULONG)pBitmap,
				(TAG_DONE));

			SetWindowPointer(m_hWnd,
				(WA_Pointer), (ULONG)m_pPointer,
				(TAG_DONE));

			p96FreeBitMap(pBitmap);
	#endif

	#elif __APPLE__

			ASSERT(0);

	#endif

	#if 0
			pCursor->Release();
	#endif
			return true;
		}
	}

	return false;
}

void HwndSource::SetCapture()
{
#if WIN32
	MSWindows::SetCapture(m_hWnd);
#endif
}

void HwndSource::ReleaseCapture()
{
	#if WIN32
		MSWindows::ReleaseCapture();
	#endif
}

#if WIN32

LRESULT HwndSource::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	MSWindows::POINT screenpt;
	screenpt.x = (short)MSWindows::LoWORD(lParam);
	screenpt.y = (short)MSWindows::HiWORD(lParam);

	MSWindows::POINT clientpt = screenpt;
	MSWindows::ScreenToClient(m_hWnd, &clientpt);

	float rscale = 96 / pixelsPerInch;
	/*
	screenpt.x *= rscale;
	screenpt.y *= rscale;
	clientpt.x *= rscale;
	clientpt.y *= rscale;
	*/

	m_pClient->OnContextMenu(LDraw::PointD(screenpt.x*rscale, screenpt.y*rscale), LDraw::PointD(clientpt.x*rscale, clientpt.y*rscale));

	return 0;
}

void HwndSource::ShowWindow(UINT nCmdShow)
{
	MSWindows::ShowWindow(m_hWnd, nCmdShow);
}

bool HwndSource::DestroyWindow()
{
	return MSWindows::DestroyWindow(m_hWnd) != 0;
}

LRESULT HwndSource::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	LPMINMAXINFO lpmmi = (LPMINMAXINFO) lParam;

	if (false)
	{
		lpmmi->ptMinTrackSize.x = max(lpmmi->ptMinTrackSize.x, m_minSize.Width);
		lpmmi->ptMinTrackSize.y = max(lpmmi->ptMinTrackSize.y, m_minSize.Height);
	}

	return 0;
}

LRESULT HwndSource::OnMouseActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	HWND hwndTopLevel = (HWND)wParam;       // handle of top-level parent 
	int nHittest = (int)MSWindows::LoWORD(lParam);    // hit-test value 
	UINT mouseMsg = (UINT)MSWindows::HiWORD(lParam);    // mouse message 

#if 0
	ILXUIDocument* document;
	static_cast<T*>(this)->get_ownerDocument(&document);

	CComQIPtr<ILDOMDocumentEvent> documentEvent = document;
	ATLASSERT(documentEvent);

	CComPtr<ILDOMEvent> evt;
	documentEvent->createEvent(L"", (ILDOMEvent**)&evt);

	evt->initEvent(L"mouseactivate",
		VARIANT_TRUE,	// bubbles ???
		VARIANT_TRUE);//,	// cancelable
	//	m_pOwnedWindow,	// viewArg
	//	0		// detail
	//	);

	ATLASSERT(0);
#if 0
	CComQIPtr<ILDOMEventTarget> target = static_cast<T*>(this);

	VARIANT_BOOL doDefault;
	target->dispatchEvent(evt, &doDefault);

	if (!doDefault)
	{
		return MA_NOACTIVATE;
	}
#endif
	/*
	// ???
	{
		CComPtr<ILDOMNode> parentNode;
		static_cast<T*>(this)->m_pNode->get_parentNode(&parentNode);

		parentNode->removeChild(static_cast<T*>(this)->m_pNode, NULL);
		//DestroyWindow();
	}
	*/
#endif

	return DefWindowProc(uMsg, wParam, lParam);
}

LRESULT HwndSource::OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	BOOL fActive = MSWindows::LoWORD(wParam);           // activation flag 
//#define     WA_INACTIVE     0
//#define     WA_ACTIVE       1
//#define     WA_CLICKACTIVE  2

	BOOL fMinimized = (BOOL)MSWindows::HiWORD(wParam); // minimized flag 
	HWND hwndPrevious = (HWND)lParam;       // window handle 

	OnActivate(fActive != WA_INACTIVE);

	return 0;
}

LRESULT HwndSource::OnActivateApp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	BOOL activate = wParam;
	DWORD threadId = lParam;

	Application* app = Application::get_Current();
	if (app)
	{
		EventArgs* e = new EventArgs;
		if (activate)
			app->OnActivated(e);
		else
			app->OnDeactivated(e);
	}

	return 0;
}

LRESULT HwndSource::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	MSWindows::POINT point;
	point.x = (short)MSWindows::LoWORD(lParam);
	point.y = (short)MSWindows::HiWORD(lParam);
	UINT nFlags = 0;
	if (wParam & MK_SHIFT) nFlags |= 1;
	if (wParam & MK_CONTROL) nFlags |= 2;

	// Some mouse drivers keep sending mousemoves even if the mouse position hasn't changed
	if (point.x != m_oldpoint.X || point.y != m_oldpoint.Y)
	{
		m_oldpoint.X = point.x;
		m_oldpoint.Y = point.y;

		MSWindows::POINT screenpt = point;
		MSWindows::ClientToScreen(m_hWnd, &screenpt);

		MSWindows::RECT client;
		MSWindows::GetClientRect(m_hWnd, &client);

		bool bInsideWindow = point.x >= 0 && point.y >= 0 && point.x < client.right && point.y < client.bottom;
		if (bInsideWindow != m_bInsideWindow)
		{
			m_bInsideWindow = bInsideWindow;
			if (m_bInsideWindow)
			{
				TRACKMOUSEEVENT tme;
				tme.cbSize = sizeof(tme);
				tme.hwndTrack = m_hWnd;
				tme.dwFlags = TME_LEAVE;
				tme.dwHoverTime = 0;
				TrackMouseEvent(&tme);
			}
		}

		if (!m_locked && g_uiLocked == 0)
		{
			float rscale = 96 / pixelsPerInch;

			m_pClient->OnMouseMove(nFlags, LDraw::PointD(screenpt.x*rscale, screenpt.y*rscale), LDraw::PointD(point.x*rscale, point.y*rscale));
		}
	}

	return 0;
}

LRESULT HwndSource::OnSizing(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	LPRECT lprc = (LPRECT) lParam;  // screen coordinates of drag rectangle

	return 0;
}

LRESULT HwndSource::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	WPARAM fwSizeType = wParam;      // resizing flag 

	if (fwSizeType == SIZE_MINIMIZED)
		return 0;

	MSWindows::RECT client;
	MSWindows::GetClientRect(m_hWnd, &client);

	GetPhysicalWindowRect(&m_windowRect);

	m_invalidRegion = new LDraw::Region(LDraw::RectI(0, 0, client.right, client.bottom));

	if (UseDirectDraw)
	{
		if (m_hBitmap)
		{
			DeleteObject((void*)m_hBitmap);
			m_hBitmap = NULL;
		}

		if (m_depthBuffer)
		{
			delete[] m_depthBuffer;
		}

		if (m_stencilBuffer)
		{
			delete[] m_stencilBuffer;
		}

		/*
		if (m_d3dSurface)
		{
			MSWindows::D3D_ReleaseSurface(m_d3dSurface);
		}
		*/

		///

		int width = client.right;
		int height = client.bottom;

		m_lpBmi->biWidth = width;
		m_lpBmi->biHeight = -height;	// Negative means top-down

		m_d3dpp9.BackBufferWidth = width;
		m_d3dpp9.BackBufferHeight = height;

		if (m_d3dDevice9 == NULL)//m_hRC)
		{
			if (height == 0) height = 1;

		//	wglMakeCurrent(m_hDC, m_hRC);
		//	LDraw::MakeCurrent(m_pGraphicsO);
		//	glViewport(0, 0, width, height); // resets the viewport to new dimensions.
			m_pGraphics3D->Viewport(0, 0, width, height); // resets the viewport to new dimensions.
		}
		else if (m_d3dDevice9)
		{
		//	m_d3dSurface = MSWindows::D3D_CreateImageSurface(m_d3dDevice, width, height);

			if (m_depthStencilSurface9)
			{
				m_depthStencilSurface9->Release();
				m_depthStencilSurface9 = NULL;
			}

			if (m_d3dSwapChain9)
			{
				m_d3dSwapChain9->Release();
				m_d3dSwapChain9 = NULL;
			}

			if (true)	// TODO, only if need alpha
				m_d3dpp9.BackBufferFormat = MSWindows::D3DFMT_A8R8G8B8;
			else
				m_d3dpp9.BackBufferFormat = MSWindows::D3DFMT_X8R8G8B8;

			D3D_CreateAdditionalSwapChain(g_d3dDevice9, &m_d3dpp9, &m_d3dSwapChain9);
			if (m_d3dSwapChain9 == NULL)
			{
				ASSERT(0);
				throw new Exception(WSTR("Couldn't create Direct3D 9 SwapChain"));
			}

			if (false)
			{
				g_d3dDevice9->CreateDepthStencilSurface(m_d3dpp9.BackBufferWidth, m_d3dpp9.BackBufferHeight, D3DFMT_D24X8, (::D3DMULTISAMPLE_TYPE)m_d3dpp9.MultiSampleType, 0, true, &m_depthStencilSurface9, NULL);
				if (m_depthStencilSurface9 == NULL)
				{
					ASSERT(0);
					throw new Exception(WSTR("Couldn't create Direct3D 9 DepthStencil surface"));
				}
			}

#if 0
			if (m_pGraphicsO->m_d3d9_effect)
			{
				m_pGraphicsO->m_d3d9_effect->OnLostDevice();

			//	m_pGraphicsO->m_d3d9_effect->Release();
			//	m_pGraphicsO->m_d3d9_effect = NULL;
			}

			/*
			if (m_pGraphicsO->m_vertexDeclaration0 != NULL)
			{
				m_pGraphicsO->m_d3d9_effect->Release();
				m_pGraphicsO->m_d3d9_effect = NULL;
			}
			*/

		//	MSWindows::D3D_ResetDevice(m_d3dDevice9, &g_d3dpp9);

			if (m_pGraphicsO->m_d3d9_effect)
			{
				m_pGraphicsO->m_d3d9_effect->OnResetDevice();
			}
#endif
		}
		else
		{
			m_depthBuffer = new float[width*height];
			m_stencilBuffer = new uint8[width*height];
		}

	//	InitPresent();

		/*
		if (m_dds)	// TODO, destroy previous
		{
			ReleaseDDSurface(m_dds);
		}
		m_dds = DoDirect(m_hWnd, client.right, client.bottom);
		*/
	}
	else
	{
		SetBitmapSize(client.right, client.bottom);
	}

#if 0
	m_pClient->m_width = new Length(client.right);
	m_pClient->m_height = new Length(client.bottom);

	/*
	m_pClient->Measure(LDraw::SizeD(0, 0));
	m_pClient->Arrange(LDraw::RectD(0, 0, client.right, client.bottom));
	m_pClient->m_windowTransform = LDraw::Matrix3f::GetIdentity();

	CreateRegions();

	m_pClient->m_bRedraw = true;
	m_redrawList = m_pClient;

	Render();
	*/
	m_pClient->InvalidateMeasure();
#else

	/*
	m_pClient->m_width = new Length(client.right);
	m_pClient->m_height = new Length(client.bottom);
	*/

	float scale = 96 / pixelsPerInch;
	LDraw::SizeD size(ceil(client.right * scale), ceil(client.bottom * scale));

	m_pClient->Measure(size);
	m_pClient->Arrange(size);
	/*
	m_pClient->GetVisualTree()->Measure(size);
	m_pClient->GetVisualTree()->Arrange(LDraw::RectD(0, 0, size.Width, size.Height));
	*/
	m_pClient->GetVisualTree()->m_windowToElementTransform = LDraw::Matrix3f::GetIdentity();

	if (true)
	{
	//	CreateRegions();

		m_pClient->GetVisualTree()->m_bRenderValid = false;
		m_pClient->GetVisualTree()->m_bDrawsOutsideOpaqueRegion = false;
	}

	m_pClient->OnSized();

	m_renderTargetUpdated = false;

	if (GetExStyle() & WS_EX_LAYERED)
	{
		RenderToTarget();
		UpdateHBITMAP();
		SetLayeredWindowBitmap();
	}

	if (false)
	{
		Render();
	}

#endif

	if (true)
	{
		MSWindows::HRGN hRgn = MSWindows::CreateRectRgn(0, 0, client.right, client.bottom);
	
		MSWindows::SetWindowRgn(m_hWnd, hRgn, false/*true*/);
	}

#if 0	// TODO, have this
	if (m_pIOleIPActiveObject)
	{
		CRect rectBorder;
		GetBorder(&rectBorder);

		m_pIOleIPActiveObject->ResizeBorder(&rectBorder, static_cast<IOleInPlaceUIWindow*>(this), TRUE/*fFrameWindow*/);
	}
#endif

	if (!UseDirectDraw)
	{
		MSWindows::InvalidateRect(m_hWnd, NULL, true);
	}

//	UpdateWindowSize();

	return 0;
}

#endif

extern UIEXT int g_nWindows;

list<PresentationSource*> g_windows;

PresentationSource* DesktopScreen::OpenWindow()
{
	HwndSource* frame = new HwndSource;
	frame->m_pOwnerScreen = this;

	//	pClient->m_pScreen = this;
	//	pClient->m_pSite = frame;
	//	frame->m_pClient = pClient;//SetContent(dynamic_cast<UIElement*>(pWindowClient));
	//	frame->Show();

	g_windows.push_back(frame);
	g_nWindows++;

	return frame;
}

}	// UI
}
