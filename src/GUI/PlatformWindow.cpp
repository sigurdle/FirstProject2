#include "stdafx.h"
#include "GUI2.h"

#include "Tablet.h"

#include <dwmapi.h>

#include <D3D10_1.h>
#include <D3DX10Async.h>

#include "Graphics/openglext.h"

#undef NO_SHLWAPI_STRFCNS
#include <Shlwapi.h>
#include <Shellapi.h>
#include <Propvarutil.h>
#include <Propkey.h>

//extern HINSTANCE g_hInstance;

//#ifdef WINTAB
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
#define PACKETDATA	(PK_X | PK_Y | PK_NORMAL_PRESSURE | PK_ORIENTATION | PK_CURSOR | PK_TANGENT_PRESSURE | PK_ROTATION)
#define PACKETMODE      0
//namespace System
//{
//	namespace MSWindows
//	{
#include "../WinTab/include/pktdef.h"
//	}
//}
//#endif

namespace MS
{
namespace Windows
{
namespace Shell
{

ITaskbarList* Private::pTaskbarList;
ITaskbarList3* Private::pTaskbarList3;

}	// Shell
}	// Windows
}	// MS

namespace System
{

extern Module _Module;

namespace Gui
{

class Tablet
{
private:
	CTOR Tablet()
	{
		SetupWinTab();
	}

	static Tablet tablet;
};

Tablet Tablet::tablet;

int g_uiLocked = 0;
//extern int g_appLockCount;

extern bool g_bTabletInstalled;
extern int g_nTabletMinPressure;
extern int g_nTabletMaxPressure;

#if _WINDOWS

uint16 PlatformWindow::s_wndClassAtom = 0;
const WCHAR* PlatformWindow::s_wndClassName = L"GUI_window_class";

uint16 PlatformWindow::s_wndClassAtom2 = 0;
const WCHAR* PlatformWindow::s_wndClassName2 = L"GUI_window_class2";

// static
void PlatformWindow::RegisterWndClass(HMODULE hModule)
{
	{
		WNDCLASSEXW wc = {0};
		wc.cbSize = sizeof(wc);
		wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wc.hInstance = hModule;
		wc.lpszClassName = s_wndClassName;
		wc.lpfnWndProc = WndProc;
		wc.hCursor = nullptr;
		s_wndClassAtom = ::RegisterClassExW(&wc);
	}
	{
		WNDCLASSEXW wc = {0};
		wc.cbSize = sizeof(wc);
		wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;
		wc.hInstance = hModule;
		wc.lpszClassName = s_wndClassName2;
		wc.lpfnWndProc = WndProc;
		wc.hCursor = nullptr;
		s_wndClassAtom2 = ::RegisterClassExW(&wc);
	}
}

// static
UINT PlatformWindow::GetWindowStyle(IPlatformWindowSite* window)
{
	UINT windowStyle = 	WS_CAPTION |
		WS_SYSMENU |
		WS_THICKFRAME;

//	windowStyle |= WS_OVERLAPPED;
	windowStyle |= WS_POPUP;

	if (window->get_CanMinimize())
	{
		windowStyle |= WS_MINIMIZEBOX;
	}

	if (window->get_CanMaximize())
	{
		windowStyle |= WS_MAXIMIZEBOX;
	}

	/*
	if (m_owner == NULL)
		windowStyle = WS_OVERLAPPEDWINDOW;
	else
		windowStyle = WS_POPUP;
		*/

	return windowStyle;
}

// static
UINT PlatformWindow::GetWindowExStyle(IPlatformWindowSite* window)
{
	UINT windowExStyle = WS_EX_COMPOSITED;

	if (window->get_Topmost())
	{
		windowExStyle |= WS_EX_TOPMOST;
	}

	return windowExStyle;
}

// static
PlatformWindow* PlatformWindow::FromHwnd(HWND hWnd)
{
	if (hWnd == nullptr) return nullptr;

	DWORD processId;
	DWORD threadId = GetWindowThreadProcessId(hWnd, &processId);
	if (processId == GetCurrentProcessId())
	{
		PlatformWindow::MyWin* win =(PlatformWindow::MyWin*)GetPropW(hWnd, L"sigurd_lerstad_gui_window");
		if (win)
		{
			return dynamic_cast<PlatformWindow*>(win->pWindow);
		}
	}

	return nullptr;
}

void PlatformWindow::OnTitleTextChanged()
{
	String titleText = m_ownerVisual->get_TitleText();
	::SetWindowTextW(get_Handle(), titleText.c_strw_flen<128>());
}

void PlatformWindow::OnOpacityChanged()
{
	float opacity = m_ownerVisual->GetOpacity();
	if (opacity < 1.0f)
	{
		::SetWindowLongW(m_hWnd, GWL_EXSTYLE, GetWindowLongW(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		::SetLayeredWindowAttributes(m_hWnd, 0, BYTE(opacity*255), LWA_ALPHA);
	}
	else
	{
		// opaque - remove WS_EX_LAYERED flag
		::SetWindowLongW(m_hWnd, GWL_EXSTYLE, GetWindowLongW(m_hWnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
	}
}

void PlatformWindow::OnClipChanged()
{
	geometry clip = m_ownerVisual->get_Clip();
	if (clip != nullptr)
	{
		ASSERT(0);
	//	Gdi::Rgn rgn = clip.CreateHRGN();
	//	SetWindowRgn(m_hWnd, rgn.Detach(), TRUE);	// The window now owns the region
	}
	else
	{
		::SetWindowRgn(m_hWnd, nullptr, TRUE);
	}
}

PlatformWindowProxy PlatformWindow::CaptureMouse()
{
	HWND hWnd = get_Handle();
	if (hWnd)
	{
		HWND hWndPrev = ::SetCapture(hWnd);
		return hWndPrev;
	}
	return nullptr;
}

gm::RectI PlatformWindow::get_ActualWindowRect() const throw()
{
	HWND hWnd = get_Handle();
	if (hWnd == nullptr) return gm::RectI();

	RECT rect;
	BOOL success = ::GetWindowRect(hWnd, &rect);
	return rect;
}

void PlatformWindow::Close()
{
	if (m_hWnd)
	{
		SendMessageW(m_hWnd, WM_CLOSE, 0, 0);
	}
}

void PlatformWindow::Hide()
{
	HWND hWnd = get_Handle();
	if (hWnd)
	{
		::ShowWindow(m_hWnd, SW_HIDE);
	}
}

#if 0
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

	// Get the full description of this pixel format
	DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
}
#endif

bool PlatformWindow::Show()
{

	HWND hWnd = get_Handle();
	if (hWnd)
	{
		ASSERT(IsWindow(hWnd));
		/*
		TODO:
		*/

	//	int state = m_ownerVisual->get_State();
	//	if (state == 0)

		BOOL success = ::ShowWindow(m_hWnd, SW_SHOWNA);
		return !!success;
	}

	if (m_ownerVisual->get_RT() == L"Direct3D")
	{
		Graphics::Direct10::s.Init();

		/*
		m_device = GL::Direct10::get_D3DDevice();
		if (m_device == NULL)
		{
			return false;
		}
		*/
	}

	PopupAnimation animation = m_ownerVisual->get_PopupAnimation();
	String titleText = m_ownerVisual->get_TitleText();
	UINT dwStyle = GetWindowStyle(m_ownerVisual);
	UINT dwExStyle = GetWindowExStyle(m_ownerVisual);

	HWND hWndParent = nullptr;

	Window* owner = m_ownerVisual->get_Owner();

	if (owner && owner->get_PWindow() != nullptr)
	{
		hWndParent = owner->get_PWindow()->get_Handle();
	}

	if (owner == nullptr || hWndParent != nullptr)
	{
		gm::RectI rect = m_ownerVisual->GetRect();

		/*
		// ??
		if (rect.Width <= 0) rect.Width = 1;
		if (rect.Height <= 0) rect.Height = 1;
		*/

		/*
		RECT rect;
		bool hasMenu = false;
		AdjustWindowRectEx(&rect, windowStyle, hasMenu, windowExStyle);
		*/

		// Do this so the values are set correctly at start (not 100% sure if this is the best place)
		POINT screenmousepos;
		GetCursorPos(&screenmousepos);
		Mouse::s_ScreenXBinding.SetValue(screenmousepos.x);
		Mouse::s_ScreenYBinding.SetValue(screenmousepos.y);

		Mouse::get_Position()->set_X(screenmousepos.x);
		Mouse::get_Position()->set_Y(screenmousepos.y);

		HWND hWnd;
		hWnd = ::CreateWindowExW(dwExStyle, (LPCWSTR)s_wndClassAtom, titleText.c_strw_flen<128>(), dwStyle,
			rect.X, rect.Y, rect.Width, rect.Height, hWndParent, nullptr, _Module.GetHandle(), reinterpret_cast<void*>(this));

		if (hWnd == nullptr)
		{
			return false;
		}

		/*
		if (true)
		{
			ComPtr<IPropertyStore> pps;
			SHGetPropertyStoreForWindow(m_hWnd, IID_PPV_ARGS(&pps));

			PROPVARIANT pv;
			InitPropVariantFromString(L"MyAppID", &pv);

			VERIFY(pps->SetValue(PKEY_AppUserModel_ID, pv));
		//	VERIFY(pps->Commit());
		}
		*/

		if (MS::Windows::Shell::Private::pTaskbarList3 == nullptr)
		{
			HRESULT hr = CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_ALL, IID_ITaskbarList3, (void**)&MS::Windows::Shell::Private::pTaskbarList3);
			MS::Windows::Shell::Private::pTaskbarList = MS::Windows::Shell::Private::pTaskbarList3;
		}

		RECT clientRect;
		GetClientRect(hWnd, &clientRect);

		int clientWidth = clientRect.right;
		int clientHeight = clientRect.bottom;

		m_dpi.X = 96;
		m_dpi.Y = 96;

		Graphics::WindowSurfDesc desc;
		desc.m_depthBits = 24;

		if (m_ownerVisual->get_RT() == L"Direct3D")	// Direct10
		{
			m_d3d10 = Graphics::Direct3D10_I::GetCurrent();
			m_gi = m_d3d10;
		}
		else if (m_ownerVisual->get_RT() == L"OpenGL")
		{
		//	m_opengl = new LDraw::OpenGL_I(get_Handle(), desc);
			m_gi = m_opengl;

			/*
			// Create a Direct2D render target.
			g_spD2DFactory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(hWnd, size),
				&m_spRT
				);

			m_spRT->GetDpi(&m_dpi.X, &m_dpi.Y);
			*/
		}
		else
		{
			ASSERT(0);
		}

		m_rt = new Graphics::RenderTarget(m_gi, get_Handle(), desc);
		m_immRenderContext = new ImmediateRenderContext(m_rt);

#if 0
		if (true)
		{
			HRESULT hr = Direct3DCreate9Ex(D3D_SDK_VERSION, &m_D3DEx);
			m_D3D = m_D3DEx;

			HWindow* win = new HWindow();
			win->CreateOverlapped(L"OpenGL");
			HWND m_hWnd = win->get_Hwnd();

			if (true)
			{
				m_D3DDev = NULL;
				D3DDISPLAYMODE dm;
				hr = m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);

			//	D3DDISPLAYMODEEX dmex;
				//dmex.Size = sizeof(D3DDISPLAYMODEEX);

				D3DPRESENT_PARAMETERS pp;
				ZeroMemory(&pp, sizeof(pp));
				pp.BackBufferWidth = 8;
				pp.BackBufferHeight = 8;
				pp.Windowed = TRUE;
				pp.hDeviceWindow = m_hWnd;
				pp.SwapEffect = D3DSWAPEFFECT_COPY;

				if (m_D3DEx)
				{
				//	hr = m_D3DEx->GetAdapterDisplayModeEx(D3DADAPTER_DEFAULT, &dmex, NULL);
				//pp.BackBufferFormat = dmex.Format;

					hr = m_D3DEx->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
						D3DCREATE_MIXED_VERTEXPROCESSING |
						//D3DCREATE_SOFTWARE_VERTEXPROCESSING |
						D3DCREATE_MULTITHREADED,
						&pp,
						NULL,	// must be NULL for windowed mode
						&m_D3DDevEx);

					m_D3DDev = m_D3DDevEx;
				}

				if (m_D3DDev == NULL)
				{
					hr = m_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
						D3DCREATE_MIXED_VERTEXPROCESSING |
						//D3DCREATE_SOFTWARE_VERTEXPROCESSING |
						D3DCREATE_MULTITHREADED,
						&pp, &m_D3DDev);
				}

				if (FAILED(hr))
				{
					switch (hr)
					{
					case D3DERR_DEVICELOST:
						raise(Exception("D3D9: Device lost", NULL, hr));

					case D3DERR_INVALIDCALL:
						raise(Exception("D3D9: Invalid Call", NULL, hr));

					case D3DERR_NOTAVAILABLE:
						raise(Exception("D3D9: Not available", NULL, hr));

					case D3DERR_OUTOFVIDEOMEMORY:
						raise(Exception("D3D9: Out of video memory", NULL, hr));

					default:
						raise_(Exception::FromHResult(hr));
					}
				}
			}


	// create the Direct3D render targets
	//	IDirect3DTexture9 *dxTexBuffer;
		IDirect3DTexture9* dxColorBuffer = NULL;
		HANDLE hShared = NULL;

		IDirect3DSurface9* dxDepthBuffer;

		hr = m_D3DDevEx->CreateTexture(
				400, 400, 1, D3DUSAGE_RENDERTARGET,
				D3DFMT_A8R8G8B8,
			//	D3DFMT_X8B8G8R8,//lpAllocInfo->Format,
				D3DPOOL_DEFAULT,
				&dxColorBuffer,
				&hShared
				);
/*
		IDirect3DSurface9 *dxColorBuffer = NULL;
		hr = m_D3DDev->CreateRenderTarget(400, 400,
								   D3DFMT_A8R8G8B8,
								   D3DMULTISAMPLE_NONE, 0,
								   FALSE,	// locked
								   &dxColorBuffer,
								  &hShared);
								  */
		ID3D10Texture2D* texture10 = NULL;
		Graphics::Direct10::get_D3DDevice1()->OpenSharedResource(hShared, __uuidof(ID3D10Texture2D), (void**)&texture10);
		ASSERT(texture10);

			HWindow* win2 = new HWindow();
			win2->CreateOverlapped(L"OpenGL");
			HWND m_hWnd2 = win->get_Hwnd();
			m_hDC = ::GetDC(m_hWnd2);				// This gets the device context for our window

			SetupPixelFormat(m_hDC);			// Call the pixel format function

			m_hRC = wglCreateContext(m_hDC);	// Creates the rendering context
			if (m_hRC == NULL)
			{
				ASSERT(0);
				//throw std::exception("Couldn't create OpenGL context");
			}

			BOOL success = wglMakeCurrent(m_hDC, m_hRC);

			const char* m_glExtensions = (const char*)::glGetString(GL_EXTENSIONS);

		//	Init(m_hDC, m_hRC);

			m_glprocs = new Graphics::GLProcs();

			if (m_glprocs->wglDXOpenDeviceNVX)
			{
				HANDLE gl_handleD3D = m_glprocs->wglDXOpenDeviceNVX(m_D3DDev);
				if (gl_handleD3D)
				{
					DebugTrace("Successfully shared device");
				}

			//	ID3D10Texture2D* dxgiSurface;
				//HRESULT hr = m_rt->m_swapChain->GetBuffer(0, __uuidof(dxgiSurface), reinterpret_cast<void**>(&dxgiSurface));

		//		IDXGISurface* dxgiSurface;
			//	HRESULT hr = m_rt->m_swapChain->GetBuffer(0, __uuidof(dxgiSurface), reinterpret_cast<void**>(&dxgiSurface));

			// register the Direct3D color and depth/stencil buffers as
				// 2D multisample textures in opengl
				GLuint gl_names[2];
				HANDLE gl_handles[2];

				BOOL success = m_glprocs->wglDXSetResourceShareHandleNVX(dxColorBuffer, hShared);

				glGenTextures(2, gl_names);

				gl_handles[0] = m_glprocs->wglDXRegisterObjectNVX(gl_handleD3D, dxColorBuffer,
													  gl_names[0],
													  GL_TEXTURE_2D,
													  WGL_ACCESS_READ_WRITE_NVX);


				uint fbo;
				m_glprocs->glGenFramebuffers(1, &fbo);

			// attach the Direct3D buffers to an FBO
				m_glprocs->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
				m_glprocs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gl_names[0], 0);
			}
		}
#endif

		OnOpacityChanged();
		OnClipChanged();

		/*
		IPlatformWindowSite* visual = m_ownerVisual;
		if (visual)
		{
			Geometry* clip = visual->get_Clip();
			if (clip)
			{
				Gdi::Rgn rgn = clip->CreateHRGN();
				SetWindowRgn(m_hWnd, rgn.Detach(), false);	// The window now owns the region
			}
		}
		*/

#if 0
		if (m_device)
		{
			m_device->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

			D3D10_VIEWPORT vp;
			vp.Width = clientWidth;
			vp.Height = clientHeight;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			vp.TopLeftX = 0;
			vp.TopLeftY = 0;
			m_device->RSSetViewports(1, &vp);
		}
		else
		{
			glViewport(0, 0, clientWidth, clientHeight);
		}
#endif

		Draw();	// WM_SIZE is not called when using direct3d surface

		m_lpBmi->biWidth = -clientWidth;
		m_lpBmi->biHeight = clientHeight;

		// TODO
#if 0
		// Create popups
		for (auto it = m_ownerVisual->m_popups.begin(); it != m_ownerVisual->m_popups.end(); ++it)
		{
			Window* popup = *it;
			popup->Show();
		}
#endif

		if (false)
		{
			::DwmEnableComposition(DWM_EC_ENABLECOMPOSITION);

			MARGINS margins = { -1 };

			HRESULT result = ::DwmExtendFrameIntoClientArea(m_hWnd, &margins);
		}

		PopupAnimation animation = m_ownerVisual->get_PopupAnimation();
		if (animation != PopupAnimation_None)
		{
			DWORD dwFlags;

			switch (animation)
			{
			case PopupAnimation_Fade:
				{
					dwFlags = AW_BLEND;
				}
				break;

			case PopupAnimation_Center:
				{
					dwFlags = AW_CENTER;
				}
				break;

			case PopupAnimation_Slide:
				{
					dwFlags = AW_SLIDE | AW_VER_POSITIVE;
				}
				break;

			case PopupAnimation_Scroll:
				{
					dwFlags = AW_VER_POSITIVE;
				}
				break;
			}

			DWORD dwTime = 200;
			AnimateWindow(hWnd, dwTime, AW_ACTIVATE | dwFlags);
		}
		else
		{
			ShowWindow(hWnd, SW_SHOWNA/*nCmdShow*/);
		}
		//UpdateWindow(hWnd);
		//Present();
	}

	return true;
}

HANDLE PlatformWindow::InitTablet(HWND hWnd)
{
	if (g_bTabletInstalled)
	{
		LOGCONTEXTW lcMine;           // The context of the tablet

		//TABLET: get current settings as a starting point for this context of the tablet.
		//WTInfo(WTI_DEFCONTEXT, 0, &lcMine);	// default settings may be different to current settings
		_WTInfoW(WTI_DEFSYSCTX, 0, &lcMine);	// current settings as set in control panel

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

		return _WTOpenW(hWnd, &lcMine, true);
	}
	return NULL;
}

BOOL PlatformWindow::GetTabState(LPARAM lParam, WPARAM wParam, UINT& nTabPressure, int& nTabAltitude, int& nTabTwist, int& nTabCompass, UINT& nTabCursor)
{
	//	if (! _WTPacket) return FALSE;
	
	//TABLET: Only return TRUE if something has changed
	BOOL bReturn = false;
	PACKET	pkt;	// the current packet
	int nMaxPkts = 1;
	
	if (_WTPacket((HCTX)lParam, wParam, &pkt))
	{
		UINT  		prsOld = t_prsNew;
		UINT  		curOld = t_curNew;
	//	ORIENTATION ortOld = t_ortNew;

		t_curNew = pkt.pkCursor;
		t_prsNew = pkt.pkNormalPressure;
	//	t_ortNew = pkt.pkOrientation;
		pkt.pkY = m_tabletExt.Height - pkt.pkY - 1;

	//	TRACE("Tablet xy: %d, %d\n", pkt.pkX, pkt.pkY);
		
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

LRESULT PlatformWindow::OnTabProximity(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (m_locked == 0 && g_uiLocked == 0)
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

LRESULT PlatformWindow::OnTabPacket(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
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

			gm::PointD screenpt(m_pntMouseLoc.X * 1600.0 / m_tabletExt.Width, m_pntMouseLoc.Y * 1200.0 / m_tabletExt.Height);

			Stylus::s_PressureBinding.SetValue(gPressure);

	#if 0
			POINT point;
			point.x = screenpt.X;
			point.y = screenpt.Y;
			::ScreenToClient(m_hWnd, &point);

			m_pClient->OnMouseMove(0/*nFlags*/, screenpt, point);
	#endif

			/*
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
			*/

	//		TRACE("Tab Packet, pressure: %d\n", gPressure);
		}
	}

	return 0;
}

GenericPlatformWindow::GenericPlatformWindow()
{
}

GenericPlatformWindow::GenericPlatformWindow(HWND hWnd) : m_hWnd(hWnd)
{
}

PlatformWindow::PlatformWindow(IPlatformWindowSite* ownerVisual) : m_ownerVisual(ownerVisual)
{
	m_lpBmi = (BITMAPINFOHEADER*)new uint8[sizeof(BITMAPV4HEADER) + sizeof(RGBQUAD)*256];
	memset(m_lpBmi, 0, sizeof(BITMAPV4HEADER));
	m_lpBmi->biSize = sizeof(BITMAPV4HEADER);
	m_lpBmi->biPlanes = 1;
	m_lpBmi->biCompression = BI_RGB;
}

// static
LRESULT CALLBACK PlatformWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCCREATE:
		{
			CREATESTRUCT* lpcs = (CREATESTRUCT*)lParam;

			PlatformWindow* pWindow = (PlatformWindow*)lpcs->lpCreateParams;
			ASSERT(pWindow);

			PlatformWindow::MyWin* p = new PlatformWindow::MyWin(pWindow);
			p->pWindow = pWindow;

			pWindow->m_hWnd = hWnd;
			SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)p);	// This is faster to retrieve if we know we own the HWND
			SetPropW(hWnd, L"sigurd_lerstad_gui_window", (HANDLE)p);	// This must be used if we don't know if we own the HWND

		//	return true;
			return DefWindowProcW(hWnd, uMsg, wParam, lParam);
		}
		break;

	case WM_GETMINMAXINFO:	// This is the first message we receive (go figure) so we must special case it
		{
			LPMINMAXINFO lpmmi = (LPMINMAXINFO) lParam;

			PlatformWindow::MyWin* p = (PlatformWindow::MyWin*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
			if (p == nullptr)
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
		}
		// Fall through

	default:
		{
			PlatformWindow::MyWin* p = (PlatformWindow::MyWin*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
			if (p != nullptr)
			{
				PlatformWindow* pWindow = static_cast<PlatformWindow*>(p->pWindow/*.m_p*/);//(PlatformWindow*)::GetWindowLongA(hWnd, GWL_USERDATA);

				return pWindow->WindowProc(uMsg, wParam, lParam);
			}
		}
		break;
	}
	return 0;
}

LRESULT PlatformWindow::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		return OnDestroy(uMsg, wParam, lParam, bHandled);

	case WM_NCDESTROY:
		OnNcDestroy(uMsg, wParam, lParam, bHandled);
		break;

#if 0
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
			MSWindows::HRGN hrgn = (MSWindows::HRGN)wParam;   // handle of update region 

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
#endif
	case WM_CLIPBOARDUPDATE:
		MessageBeep(-1);
		break;

	case WM_PAINT:
		return OnPaint(uMsg, wParam, lParam, bHandled);

	case WM_PRINTCLIENT:
		return OnPrintClient(uMsg, wParam, lParam, bHandled);
#if 0
	case WM_GETTEXT:
		return OnGetText(uMsg, wParam, lParam, bHandled);

	case WM_GETTEXTLENGTH:
		return OnGetTextLength(uMsg, wParam, lParam, bHandled);

	case WM_GETMINMAXINFO:
		return OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled);
#endif

	case WM_MOVE:
		return OnMove(uMsg, wParam, lParam, bHandled);

	case WM_SIZE:
		return OnSize(uMsg, wParam, lParam, bHandled);

	case WM_ENTERSIZEMOVE:
		return OnEnterSizeMove(uMsg, wParam, lParam, bHandled);

	case WM_EXITSIZEMOVE:
		return OnExitSizeMove(uMsg, wParam, lParam, bHandled);

	case WM_SIZING:
		return OnSizing(uMsg, wParam, lParam, bHandled);
#if 0

	case WM_CONTEXTMENU:
		return OnContextMenu(uMsg, wParam, lParam, bHandled);
#endif

	case WM_APPCOMMAND:
		return OnAppCommand(uMsg, wParam, lParam, bHandled);

	case WM_GETOBJECT:
		return OnGetObject(uMsg, wParam, lParam, bHandled);

	case WM_ACTIVATE:
		{
			WORD active = LOWORD(wParam);
			WORD minimized = HIWORD(wParam);

			if (t_hTablet)
			{
				BOOL success = _WTOverlap((HCTX) t_hTablet, !(active == WA_INACTIVE));
				ASSERT(success);
			}

			if (active == WA_INACTIVE)
			{
				m_ownerVisual->SetActive(false);
			}
			else
			{
				m_ownerVisual->SetActive(true);
			}

			// TODO, have this
#if 0
		//	if (wParam == WA_INACTIVE)
			{
			//	HWND hWnd = ::GetActiveWindow();
				HWND hWnd = (HWND)lParam;//::GetActiveWindow();
				Window* window = Window::FromHwnd(hWnd);
				Window::ActiveWindowBinding.SetValue(window);
			}
			/*
			else
			{
				Window* window = dynamic_cast<Window*>(m_ownerVisual->get_TemplatedOwner());
				ASSERT(window);
				Window::ActiveWindowBinding.SetValue(window);
			}
			*/
#endif
		}
		return DefWindowProc(uMsg, wParam, lParam);

		/*
	case 0:
		{
			HWND hWnd = ::GetForegroundWindow();
			Window* window = ForeignWindow::FromHwnd(hWnd);
			Window::ForegroundWindowBinding.SetValue(window);
		}
		break;
		*/

	case WM_LBUTTONDOWN:
		return OnLButtonDown(uMsg, wParam, lParam, bHandled);

	case WM_LBUTTONDBLCLK:
		return OnLButtonDblClk(uMsg, wParam, lParam, bHandled);

	case WM_LBUTTONUP:
		return OnLButtonUp(uMsg, wParam, lParam, bHandled);

	case WM_RBUTTONDOWN:
		return OnRButtonDown(uMsg, wParam, lParam, bHandled);

	case WM_RBUTTONUP:
		return OnRButtonUp(uMsg, wParam, lParam, bHandled);

	case WM_MBUTTONDOWN:
		return OnMButtonDown(uMsg, wParam, lParam, bHandled);

	case WM_MBUTTONUP:
		return OnMButtonUp(uMsg, wParam, lParam, bHandled);

	case WM_MOUSEMOVE:
		return OnMouseMove(uMsg, wParam, lParam, bHandled);

	case WM_SETCURSOR:
		return OnSetCursor(uMsg, wParam, lParam, bHandled);

#if 0

	case WM_SYSKEYDOWN:
		// TODO, do more here
		return OnKeyDown(uMsg, wParam, lParam, bHandled);
#endif

	case WM_KEYDOWN:
		return OnKeyDown(uMsg, wParam, lParam, bHandled);

	case WM_CHAR:
		return OnChar(uMsg, wParam, lParam, bHandled);
#if 0
	case WM_MOUSELEAVE:
		OnMouseLeave();
		break;
#endif
	case WM_CAPTURECHANGED:
		return OnCaptureChanged(uMsg, wParam, lParam, bHandled);
#if 0
	case WM_ACTIVATE:
		OnActivate(uMsg, wParam, lParam, bHandled);
		break;

	case WM_ACTIVATEAPP:
		OnActivateApp(uMsg, wParam, lParam, bHandled);
		break;

		// Vista
	case WM_DWMCOMPOSITIONCHANGED:
		OnDwmCompositionChanged();
		break;
#endif

//#ifdef 1//WINTAB
	case WT_PACKET:
		OnTabPacket(uMsg, wParam, lParam, bHandled);
		break;

	case WT_PROXIMITY:
		OnTabProximity(uMsg, wParam, lParam, bHandled);
		break;
//#endif

	case WM_DWMCOLORIZATIONCOLORCHANGED:
		return OnDwmColorizationColorChanged(uMsg, wParam, lParam, bHandled);

	case WM_GETICON:
		break;

	case WM_INPUT:
		return OnRawInput(uMsg, wParam, lParam, bHandled);

	default:
		return DefWindowProc(uMsg, wParam, lParam);
	}
	return 0;
}

LRESULT PlatformWindow::DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(m_hWnd, uMsg, wParam, lParam);
}

void PlatformWindow::Draw()
{
	ASSERT(m_rt);

	if (m_renderTargetUpdated)
		return;

	m_renderTargetUpdated = true;

	// TODO: not like this
	Visual* shadowTree = m_ownerVisual->GetRootElement();
	if (shadowTree)
	{
		/*
		shadowTree->SetRoot(m_ownerVisual);

		if (shadowTree->get_Parent() != m_ownerVisual)
		{
			shadowTree->set_Parent(m_ownerVisual);
		}
		*/
	}

	RECT clientSize;
	GetClientRect(m_hWnd, &clientSize);

	// TODO
	Visual* visual = dynamic_cast<Visual*>(m_ownerVisual);
	if (visual)
	{
		if (Graphics::Direct10::get_D2DFactory())
		{
			if (!visual->m_visibleGeometryValid)
			{
				geometry geom(gm::RectF(0, 0, float(clientSize.right), float(clientSize.bottom)));
				visual->MakeVisibleGeometry(geom);
			}
		}
	}

	//if (m_spRT)
	{
		//if (!(m_spRT->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
		{
			clientSize.right = int(clientSize.right * 96 / m_dpi.X);
			clientSize.bottom = int(clientSize.bottom * 96 / m_dpi.Y);

		//	m_rt->m_gi = m_gi;
		//	m_rt->m_d3d10 = m_d3d10;
		//	m_rt->m_opengl = m_opengl;

			//GL::RenderTarget rt;
			m_rt->m_projection = gm::matrix4f::getOrtho2D(0, clientSize.right, clientSize.bottom, 0);
			m_rt->m_modelView = gm::matrix4f::getIdentity();
			m_rt->m_modelViewProjection = m_rt->m_projection * m_rt->m_modelView;

			float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // RGBA
		//	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // RGBA

		//	ImmediateRenderContext immRenderContext(m_rt);

			Graphics::RenderTargetStoreState rtstate;
			m_rt->BeginDraw(&rtstate);

			if (m_rt->m_d3d10)
			{
				m_rt->m_d3d10->m_device->ClearRenderTargetView(m_rt->m_pRenderTargetView, clearColor);
				if (m_rt->m_pDepthStencilView)
				{
					m_rt->m_d3d10->m_device->ClearDepthStencilView(m_rt->m_pDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
				}
			}
			else
			{
				glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				glFrontFace(GL_CCW);

				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
			}

			if (visual)
			{
				visual->Render_(m_immRenderContext);
			}

			m_rt->EndDraw(&rtstate);
		}
	}
}

void PlatformWindow::Present()
{
	ASSERT(m_rt);
	m_rt->Present();
}

void PlatformWindow::InvalidateDraw()
{
	if (m_hWnd)
	{
		DWORD threadId = gui_threadId;/*GetCurrentThreadId()/*TODO*/
		PostThreadMessage(threadId, WM_USER+2, 0, 0);

		if (m_renderTargetUpdated)
		{
			m_renderTargetUpdated = false;
			InvalidateRect(m_hWnd, NULL, false);
		}
	}
}

HRESULT STDMETHODCALLTYPE PlatformWindow::DropTarget::DragEnter(
	::IDataObject *pDataObj,
    /* [in] */ DWORD grfKeyState,
    /* [in] */ POINTL pt,
    /* [out][in] */ __RPC__inout DWORD *pdwEffect)
{
	return m_wnd->get_OwnerVisual()->DragEnter(pDataObj, grfKeyState, pt, pdwEffect);
}

HRESULT STDMETHODCALLTYPE PlatformWindow::DropTarget::DragOver( 
    /* [in] */ DWORD grfKeyState,
    /* [in] */ POINTL pt,
    /* [out][in] */ __RPC__inout DWORD *pdwEffect)
{
	return m_wnd->get_OwnerVisual()->DragOver(grfKeyState, pt, pdwEffect);
}

HRESULT STDMETHODCALLTYPE PlatformWindow::DropTarget::DragLeave( void)
{
	return m_wnd->get_OwnerVisual()->DragLeave();
}

HRESULT STDMETHODCALLTYPE PlatformWindow::DropTarget::Drop( 
	/* [unique][in] */ __RPC__in_opt ::IDataObject *pDataObj,
    /* [in] */ DWORD grfKeyState,
    /* [in] */ POINTL pt,
    /* [out][in] */ __RPC__inout DWORD *pdwEffect)
{
	return m_wnd->get_OwnerVisual()->Drop(pDataObj, grfKeyState, pt, pdwEffect);
}

LRESULT PlatformWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
#if 0
	AddClipboardFormatListener(get_Handle());
#endif

//#ifdef WINTAB
	if (true)
	{
		t_hTablet = InitTablet(m_hWnd);
		if (t_hTablet)
		{
			_WTQueueSizeSet((HCTX)t_hTablet, 1);
		}
	}
//#endif // WINTAB

	m_dropTarget = new DropTarget(this);
	RegisterDragDrop(m_hWnd, m_dropTarget);

	IncAppLockCount();

	return 0;
}

LRESULT PlatformWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	RevokeDragDrop(m_hWnd);

	if (m_rt)
	{
		m_rt->Destroy();
	}

	return 0;
}

LRESULT PlatformWindow::OnNcDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	ASSERT(IsWindow(m_hWnd));
	m_hWnd = nullptr;
	DecAppLockCount();
	return 0;
}

LRESULT PlatformWindow::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (false)
		// Use a trick with blurbehind to get out alpha direct3d texture be composited with the rest
		{
		//Create and populate the BlurBehind structure
		   DWM_BLURBEHIND bb = {0};
		   //Disable Blur Behind and Blur Region;
		   bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
		   bb.fEnable = true;
		   bb.hRgnBlur = CreateRectRgn(0, 0, 100, 100);	// Outside the client rect

		   //Enable Blur Behind
		   HRESULT hr = DwmEnableBlurBehindWindow(m_hWnd, &bb);
		   ASSERT(SUCCEEDED(hr));
		}

	if (false)
	{
		if (m_rt)
		{
			Draw();
			Present();
		}

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hWnd, &ps);

		EndPaint(m_hWnd, &ps);
	}
	else
	{
		if (m_rt)
		{
			Draw();
			Present();
		}

		ValidateRect(m_hWnd, NULL );
	}

	return 0;
}

LRESULT PlatformWindow::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	UINT hitTest = LOWORD(lParam);
	UINT mouseMsg = HIWORD(lParam);

	POINT screenmousepos;
	GetCursorPos(&screenmousepos);

	if (m_ownerVisual->OnSetCursor(hitTest, screenmousepos))
		return true;
	else
		return DefWindowProc(uMsg, wParam, lParam);
}

LRESULT PlatformWindow::OnCaptureChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	HWND hWndNew = (HWND)lParam;
	m_ownerVisual->OnLostMouseCapture(hWndNew);
	return 0;
}

LRESULT PlatformWindow::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	short clientX = (short)LOWORD(lParam);
	short clientY = (short)HIWORD(lParam);

//	DebugTrace("mouse" << clientX << "," << clientY << "\n");

	m_ownerVisual->OnMouseMove(gm::PointF(clientX, clientY));

	return 0;
}

LRESULT PlatformWindow::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	short clientX = (short)LOWORD(lParam);
	short clientY = (short)HIWORD(lParam);

	m_ownerVisual->OnMouseButtonDown(gm::PointF(clientX, clientY), 0);

	return 0;
}

LRESULT PlatformWindow::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	short clientX = (short)LOWORD(lParam);
	short clientY = (short)HIWORD(lParam);

	m_ownerVisual->OnMouseButtonDblClk(gm::PointF(clientX, clientY), 0);

	return 0;
}

LRESULT PlatformWindow::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	short clientX = (short)LOWORD(lParam);
	short clientY = (short)HIWORD(lParam);

	m_ownerVisual->OnMouseButtonUp(gm::PointF(clientX, clientY), 0);

	return 0;
}

LRESULT PlatformWindow::OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	short clientX = (short)LOWORD(lParam);
	short clientY = (short)HIWORD(lParam);

	m_ownerVisual->OnMouseButtonDown(gm::PointF(clientX, clientY), 2);

	return 0;
}

LRESULT PlatformWindow::OnRButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	short clientX = (short)LOWORD(lParam);
	short clientY = (short)HIWORD(lParam);

	m_ownerVisual->OnMouseButtonDblClk(gm::PointF(clientX, clientY), 2);

	return 0;
}

LRESULT PlatformWindow::OnRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	short clientX = (short)LOWORD(lParam);
	short clientY = (short)HIWORD(lParam);

	m_ownerVisual->OnMouseButtonUp(gm::PointF(clientX, clientY), 2);

	return 0;
}

LRESULT PlatformWindow::OnMButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	short clientX = (short)LOWORD(lParam);
	short clientY = (short)HIWORD(lParam);

	m_ownerVisual->OnMouseButtonDown(gm::PointF(clientX, clientY), 1);

	return 0;
}

LRESULT PlatformWindow::OnMButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return 0;
}

LRESULT PlatformWindow::OnMButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	short clientX = (short)LOWORD(lParam);
	short clientY = (short)HIWORD(lParam);

	m_ownerVisual->OnMouseButtonUp(gm::PointF(clientX, clientY), 1);

	return 0;
}

LRESULT PlatformWindow::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	m_ownerVisual->OnKeyDown(wParam, lParam);

	return 0;
}

LRESULT PlatformWindow::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	m_ownerVisual->OnChar(wParam, lParam);

	return 0;
}

Graphics::Bitmap* PlatformWindow::GetContentBitmap()
{
	HRESULT hr;

	ComPtr<ID3D10Texture2D> pBackBuffer;
	hr = m_rt->m_swapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr))
	{
		return nullptr;
	}
	D3D10_TEXTURE2D_DESC desc;
	pBackBuffer->GetDesc(&desc);

//	D3D10_RENDER_TARGET_VIEW_DESC rtd;
//	rtd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	rtd.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
//	rtd.Texture2D.MipSlice = 0;

	Graphics::Bitmap* bitmap = new Graphics::Bitmap(m_d3d10->m_device,
		Graphics::D3D10Texture2D(m_d3d10->m_device,
		desc.Width, desc.Height,
		DXGI_FORMAT_R8G8B8A8_UNORM, D3D10_USAGE_STAGING));

	m_d3d10->m_device->CopyResource(bitmap->m_d3d10_texture, pBackBuffer);
//	hr = m_d3d10->m_device->CreateRenderTargetView(pBackBuffer, &rtd, &bitmap->m_d3d10_renderTargetView);

	return bitmap;
}

void PlatformWindow::UpdateHBITMAP()
{
	if (m_hBitmap == nullptr)
	{
		m_lpBmi->biBitCount = 32;
		m_hBitmap = CreateDIBSection(nullptr,	// hDC
			(BITMAPINFO*)m_lpBmi,
			DIB_RGB_COLORS,
			(void**)&m_bmBits,
			nullptr, //hSection
			0	//sectionOffset
			);
	}
}

LRESULT PlatformWindow::OnPrintClient(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	HDC hDC = (HDC)wParam;

	/*
	if (!m_renderTargetUpdated)
	{
		RenderToTarget();
	}
	*/
	Draw();
	UpdateHBITMAP();

	if (m_hBitmap)
	{
		HDC hSrcDC = CreateCompatibleDC(hDC);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hSrcDC, (void*)m_hBitmap);

		RECT clientRect;
		GetClientRect(m_hWnd, &clientRect);

		BitBlt(hDC, 0, 0, clientRect.right, clientRect.bottom, hSrcDC, 0, 0, SRCCOPY);

		SelectObject(hSrcDC, hOldBitmap);
		DeleteDC(hSrcDC);
	}

	return 0;
}

void PlatformWindow::ChangeTech()
{
	if (m_gi)
	{
		m_gi->Shutdown();
		m_opengl = nullptr;
		m_d3d10 = nullptr;
	}

	ASSERT(0);

	Graphics::WindowSurfDesc desc;
	desc.m_depthBits = 24;

	//
	if (m_ownerVisual->get_RT() == L"OpenGL")
	{
	//	m_opengl = new LDraw::OpenGL_I(get_Handle(), desc);
		m_gi = m_opengl;
	}
	else if (m_ownerVisual->get_RT() == L"Direct3D")
	{
	//	m_d3d10 = new LDraw::Direct3D10_I(get_Handle(), desc);
		m_gi = m_d3d10;
	}
	else
	{
		ASSERT(0);
	}

	InvalidateRect(get_Handle(), nullptr, false);
}

LRESULT PlatformWindow::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	HRESULT hr;

	if (wParam == SIZE_MAXHIDE)
	{
		// Message is sent to all pop-up windows when some other window is maximized
	}
	else if (wParam == SIZE_MAXSHOW)
	{
		// Message is sent to all pop-up windows when some other window has been restored to its former size
	}
	else if (wParam == SIZE_MINIMIZED)
	{
		m_ownerVisual->set_State(1);

		// NOTE: I'm not sure, but I don't think i want to resize render target etc.
	}
	else
	{
		// SIZE_MAXIMIZED || SIZE_RESTORED

		RECT clientRect;
		GetClientRect(m_hWnd, &clientRect);
		int clientWidth = clientRect.right;
		int clientHeight = clientRect.bottom;

		RECT windowRect;
		GetWindowRect(m_hWnd, &windowRect);
		int windowWidth = windowRect.right - windowRect.left;
		int windowHeight = windowRect.bottom - windowRect.top;

		if (m_rt)
		{
			m_rt->WindowResized();
		}

		m_renderTargetUpdated = false;

		InvalidateRect(m_hWnd, nullptr, true);

		m_ownerVisual->OnSize(windowRect);


		if (wParam == SIZE_MAXIMIZED)
		{
			m_ownerVisual->set_State(2);
		}
	}
	//	Draw();
	//	Present();
		/*
		// If we couldn't resize, release it and we'll recreate it
		// during the next render pass.
		if (FAILED(hr))
		{
		//	DiscardDeviceResources();
			InvalidateRect(m_hWnd, NULL, FALSE);
		}
		*/

	return 0;
}

LRESULT PlatformWindow::OnSizing(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	WPARAM edge = wParam;
	RECT* pScreenRect = (RECT*)lParam;
	return m_ownerVisual->OnSizing(edge, pScreenRect);
}

LRESULT PlatformWindow::OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	RECT windowRect;
	GetWindowRect(m_hWnd, &windowRect);

	m_ownerVisual->OnWindowPosChanged(windowRect.left, windowRect.top);

	// TODO, event
#if 0
	m_ownerVisual->OnMove(m_ownerVisual);
#endif

	return 0;
}

LRESULT PlatformWindow::OnEnterSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	m_ownerVisual->set_InSizeMove(true);
	return 0;
}

LRESULT PlatformWindow::OnExitSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	m_ownerVisual->set_InSizeMove(false);
	return 0;
}

LRESULT PlatformWindow::OnGetIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return 0;
}

LRESULT PlatformWindow::OnSetIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return 0;
}

LRESULT PlatformWindow::OnDwmColorizationColorChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return 0;
}

LRESULT PlatformWindow::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return 0;
}

LRESULT PlatformWindow::OnAppCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return 0;
}

LRESULT PlatformWindow::OnGetObject(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
// If lParam matches UiaRootObjectId, return IRawElementProviderSimple.
	if (static_cast<long>(lParam) == static_cast<long>(UiaRootObjectId))
	{
		ASSERT(0);
#if 0
		// Return the IRawElementProviderSimple pointer to UI Automation.
		return UiaReturnRawElementProvider(get_Handle(), wParam, lParam, m_ownerVisual->GetElementProvider());
#endif
	}
	return DefWindowProc(uMsg, wParam, lParam);
}

LRESULT PlatformWindow::OnHelp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	HELPINFO* helpinfo = (HELPINFO*)lParam;
	m_ownerVisual->OnHelp(helpinfo);
	return 0;
}

LRESULT PlatformWindow::OnRawInput(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	/*
wParam
Input code. This parameter can be one of the following values. 
RIM_INPUT
Input occurred while the application was in the foreground. The application must call DefWindowProc so the system can perform cleanup.
RIM_INPUTSINK
Input occurred while the application was not in the foreground. The application must call DefWindowProc so the system can perform the cleanup.
*/

	UINT dwSize;

    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
    LPBYTE lpb = (BYTE*)_alloca(dwSize);
    if (lpb == nullptr)
    {
        return 0;
    } 

    if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize,  sizeof(RAWINPUTHEADER)) != dwSize)
	{
         DebugTraceLn("GetRawInputData doesn't return correct size !"); 
	}

    RAWINPUT* raw = (RAWINPUT*)lpb;

    if (raw->header.dwType == RIM_TYPEKEYBOARD) 
    {
		/*
		hResult = StringCchPrintf(szTempOutput, STRSAFE_MAX_CCH, TEXT(" Kbd: make=%04x Flags:%04x Reserved:%04x ExtraInformation:%08x, msg=%04x VK=%04x \n"), 
            raw->data.keyboard.MakeCode, 
            raw->data.keyboard.Flags, 
            raw->data.keyboard.Reserved, 
            raw->Data.keyboard.ExtraInformation, 
            raw->data.keyboard.Message, 
            raw->data.keyboard.VKey);
		if (FAILED(hResult))
		{
		// TODO: write error handler
		}
        OutputDebugString(szTempOutput);
		*/
    }
    else if (raw->header.dwType == RIM_TYPEMOUSE) 
    {
		if (raw->data.mouse.usFlags == MOUSE_MOVE_RELATIVE)
		{
		//	TRACE("rel: %d,%d\n", raw->data.mouse.lLastX, raw->data.mouse.lLastY);
		}
		else if (raw->data.mouse.usFlags == MOUSE_MOVE_ABSOLUTE)
		{
		//	TRACE("abs: %d,%d\n", raw->data.mouse.lLastX, raw->data.mouse.lLastY);
		}
		else
			;//ASSERT(0);

		POINT screenmousepos;
		GetCursorPos(&screenmousepos);

		Mouse::s_ScreenXBinding.SetValue(screenmousepos.x);
		Mouse::s_ScreenYBinding.SetValue(screenmousepos.y);
		Mouse::get_Position()->set_X(screenmousepos.x);
		Mouse::get_Position()->set_Y(screenmousepos.y);

		/*
		hResult = StringCchPrintf(szTempOutput, STRSAFE_MAX_CCH, TEXT("Mouse: usFlags=%04x ulButtons=%04x usButtonFlags=%04x usButtonData=%04x ulRawButtons=%04x lLastX=%04x lLastY=%04x ulExtraInformation=%04x\r\n"), 
            raw->data.mouse.usFlags, 
            raw->data.mouse.ulButtons, 
            raw->data.mouse.usButtonFlags, 
            raw->data.mouse.usButtonData, 
            raw->data.mouse.ulRawButtons, 
            raw->data.mouse.lLastX, 
            raw->data.mouse.lLastY, 
            raw->data.mouse.ulExtraInformation);

		if (FAILED(hResult))
		{
		// TODO: write error handler
		}
        OutputDebugString(szTempOutput);
		*/
    } 

    //delete[] lpb; 

	// ??
	return 0;
//	return DefWindowProc(uMsg, wParam, lParam);
}

#endif	// _WINDOWS

}	// Gui
}	// System
