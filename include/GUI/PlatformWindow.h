#ifdef __LERSTAD__

interface IDropTarget : public IUnknown
{
#if 0
    virtual HRESULT STDMETHODCALLTYPE DragEnter( 
        /* [unique][in] */ __RPC__in_opt IDataObject *pDataObj,
        /* [in] */ DWORD grfKeyState,
        /* [in] */ POINTL pt,
        /* [out][in] */ __RPC__inout DWORD *pdwEffect) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE DragOver( 
        /* [in] */ DWORD grfKeyState,
        /* [in] */ POINTL pt,
        /* [out][in] */ __RPC__inout DWORD *pdwEffect) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE DragLeave( void) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Drop( 
        /* [unique][in] */ __RPC__in_opt IDataObject *pDataObj,
        /* [in] */ DWORD grfKeyState,
        /* [in] */ POINTL pt,
        /* [out][in] */ __RPC__inout DWORD *pdwEffect) = 0;
#endif
};

#endif

namespace System
{
namespace Gui
{

class PlatformWindowProxy;

interface IPlatformWindowSite;

interface IPlatformWindow
{
	virtual IPlatformWindowSite* GetSite() const throw() = 0;

	virtual void Close() = 0;
	virtual gm::RectI get_ActualWindowRect() const throw() = 0;
	virtual PlatformWindowProxy CaptureMouse() = 0;
	virtual void OnOpacityChanged() = 0;
	virtual void OnClipChanged() = 0;
	virtual void OnTitleTextChanged() = 0;
};

interface IPlatformWindowSite
{
	virtual PlatformWindow* GetPlatformWindow() = 0;

	virtual bool get_CanMinimize() = 0;
	virtual bool get_CanMaximize() = 0;
	virtual bool get_Topmost() = 0;
	virtual geometry get_Clip() = 0;
	virtual PopupAnimation get_PopupAnimation() = 0;
	virtual String get_RT() = 0;
	virtual String get_TitleText() = 0;
	virtual Window* get_Owner() = 0;
	virtual float GetOpacity() = 0;
	virtual gm::RectI GetRect() = 0;
	virtual void SetActive(bool isActive) = 0;
	virtual UIElement* GetRootElement() = 0;

	virtual void set_State(int) = 0;

	virtual void OnMouseButtonDown(gm::PointF clientMousePos, int button) = 0;
	virtual void OnMouseButtonDblClk(gm::PointF clientMousePos, int button) = 0;
	virtual void OnMouseButtonUp(gm::PointF clientMousePos, int button) = 0;
	virtual void OnMouseMove(gm::PointF clientMousePos) = 0;
	virtual bool OnSetCursor(UINT hitTest, POINT screenMousePos) = 0;
	virtual void OnKeyDown(UINT wParam, UINT lParam) = 0;
	virtual void OnChar(UINT wParam, UINT lParam) = 0;
	virtual void OnHelp(HELPINFO* helpinfo) = 0;
	virtual void OnLostMouseCapture(PlatformWindowProxy gotCapture) = 0;
	virtual HRESULT DragEnter(__IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) = 0;
	virtual HRESULT DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) = 0;
	virtual HRESULT DragLeave() = 0;
	virtual HRESULT Drop(__IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) = 0;

	virtual void OnSize(gm::RectI r) = 0;
	virtual LRESULT OnSizing(WPARAM edge, RECT* pScreenRect) = 0;
	virtual void set_InSizeMove(bool) = 0;

	virtual void OnWindowPosChanged(float left, float top) = 0;
	virtual void OnWindowSizeChanged(float width, float height) = 0;
//	virtual void OnWindowRectChanged(float left, float top, float width, float height) = 0;
};

class GUIEXT GenericPlatformWindow : public Object
{
public:

	CTOR GenericPlatformWindow();
	CTOR GenericPlatformWindow(HWND hWnd);

	inline HWND get_Handle() const throw()
	{
		return m_hWnd;
	}

	class MyWin
	{
	public:
		CTOR MyWin(GenericPlatformWindow* _pWindow) : pWindow(_pWindow)
		{
		}

		GenericPlatformWindow* pWindow;

#undef new
		void* operator new (size_t size)
		{
			return malloc(size);
		}

		void* operator new (size_t size, const char* filename, int line)
		{
			return malloc(size);
		}
#define new _new

		void operator delete (void* pv)
		{
			free(pv);
		}
	};

protected:

	HWND m_hWnd;
};

class GUIEXT ForeignPlatformWindow : public GenericPlatformWindow
{
public:

	CTOR ForeignPlatformWindow(Window* window, HWND hWnd) : GenericPlatformWindow(hWnd), m_window(window)
	{
	}

	Window* m_window;
};

class GUIEXT PlatformWindow : public GenericPlatformWindow, public IPlatformWindow, public Graphics::OpenGLContext
	//public IRawElementProviderSimple
{
public:

	CTOR PlatformWindow(IPlatformWindowSite* ownerVisual);

	void InvalidateDraw();
	bool Show();
	void Hide();
	virtual void Close();

	virtual gm::RectI get_ActualWindowRect() const throw() override;
	virtual PlatformWindowProxy CaptureMouse() override;
	virtual void OnOpacityChanged() override;
	virtual void OnClipChanged() override;
	virtual void OnTitleTextChanged() override;

	void ChangeTech();

	IPlatformWindowSite* get_OwnerVisual()
	{
		return m_ownerVisual;
	}

	virtual IPlatformWindowSite* GetSite() const throw() override
	{
		return m_ownerVisual;
	}

	Graphics::Bitmap* GetContentBitmap();

	Graphics::GraphicsI* GetGI() const throw()
	{
		return m_gi;
	}

	static void RegisterWndClass(HMODULE hModule);
	static UINT GetWindowStyle(IPlatformWindowSite* windowVisual);
	static UINT GetWindowExStyle(IPlatformWindowSite* windowVisual);
	static PlatformWindow* FromHwnd(HWND hWnd);

protected:

	void Draw();
	void Present();
	void UpdateHBITMAP();

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnNcDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnPrintClient(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnGetText(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnGetTextLength(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnRawInput(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnAppCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnHelp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnRButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnMButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnMButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnMButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnCaptureChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSizing(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnEnterSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnExitSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnGetIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSetIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDwmColorizationColorChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnGetObject(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnTabPacket(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnTabProximity(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#ifndef __LERSTAD__
	class GUIEXT DropTarget : public Object, public ::IDropTarget
#else
	class GUIEXT DropTarget : public Object, public IUnknown
#endif
	{
	public:

		CTOR DropTarget(PlatformWindow* wnd) : m_wnd(wnd), m_refCount(0)
		{
		}

#ifndef __LERSTAD__
        virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
			/* [in] */ REFIID riid,
            /* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject)
		{
			if (riid == __uuidof(IUnknown))
			{
				*ppvObject = static_cast<IUnknown*>(this);
			}
			else if (riid == __uuidof(IDropTarget))
			{
				*ppvObject = static_cast<IDropTarget*>(this);
			}
			else
			{
				*ppvObject = nullptr;
				return E_NOINTERFACE;
			}

			AddRef();
			return S_OK;
		}

        virtual ULONG STDMETHODCALLTYPE AddRef()
		{
			++m_refCount;
			return m_refCount;
		}

        virtual ULONG STDMETHODCALLTYPE Release()
		{
			--m_refCount;
			return m_refCount;
		}

		virtual HRESULT STDMETHODCALLTYPE DragEnter( 
			/* [unique][in] */ __RPC__in_opt ::IDataObject *pDataObj,
			/* [in] */ DWORD grfKeyState,
			/* [in] */ POINTL pt,
			/* [out][in] */ __RPC__inout DWORD *pdwEffect);
        
		virtual HRESULT STDMETHODCALLTYPE DragOver( 
			/* [in] */ DWORD grfKeyState,
			/* [in] */ POINTL pt,
			/* [out][in] */ __RPC__inout DWORD *pdwEffect);
        
		virtual HRESULT STDMETHODCALLTYPE DragLeave();
        
		virtual HRESULT STDMETHODCALLTYPE Drop( 
			/* [unique][in] */ __RPC__in_opt ::IDataObject *pDataObj,
			/* [in] */ DWORD grfKeyState,
			/* [in] */ POINTL pt,
			/* [out][in] */ __RPC__inout DWORD *pdwEffect);
#endif
	protected:

		PlatformWindow* m_wnd;
		long m_refCount;
	};

	DropTarget* m_dropTarget;
	IPlatformWindowSite* m_ownerVisual;
	gm::PointF m_dpi;

private:

	Graphics::GraphicsI* m_gi;
	Graphics::RenderTarget* m_rt;
	ImmediateRenderContext* m_immRenderContext;

	// Direct3D_10

	Graphics::Direct3D10_I* m_d3d10;

	/*
	ID3D10Device* m_device;
	IDXGISwapChain* m_swapChain;
	ID3D10RenderTargetView* m_pRenderTargetView;
	ID3D10Texture2D* m_pDepthStencil;
	ID3D10DepthStencilView* m_pDepthStencilView;
//	ID3D10RasterizerState* m_pRasterizerState;
*/

	// OpenGL
//	HGLRC m_hRC;                         // Rendering context.
//	HDC m_hDC;                           // Device context.
	Graphics::OpenGL_I* m_opengl;
//	Graphics::GLProcs* m_glprocs;

	//
	BITMAPINFOHEADER* m_lpBmi;
	HBITMAP m_hBitmap;
	uint8* m_bmBits;

	HRGN m_hRgn;

//#ifdef WINTAB
// Tablet
	HANDLE/*HCTX*/ t_hTablet;			// Tablet context
	//	current pen statistics
	UINT            t_prsNew;		// Pressure value
	UINT            t_curNew;		// Cursor number
//	ORIENTATION     t_ortNew;		// Varios movement values, direction and tilt
	gm::PointI	m_pntMouseLoc;	// Mouse pointer location, which is also the pen location

	gm::Sizei m_tabletExt;

	HANDLE InitTablet(HWND hWnd);
	BOOL GetTabState(LPARAM lParam, WPARAM wParam, UINT& nTabPressure, int& nTabAltitude, int& nTabTwist, int& nTabCompass, UINT& nTabCursor);

//#endif // WINTAB

	/*
	list<IStylusPlugin*> m_stylusPlugins;

	virtual void AddStylusPlugin(IStylusPlugin* plugin);
	*/

	int m_locked;

	bool m_renderTargetUpdated;

	static const WCHAR* s_wndClassName;
	static const WCHAR* s_wndClassName2;
	static uint16 s_wndClassAtom;	// ATOM
	static uint16 s_wndClassAtom2;	// ATOM
};

class GUIEXT PlatformWindowProxy
{
public:
	CTOR PlatformWindowProxy(HWND hWnd) throw() : m_hWnd(hWnd)
	{
	}

	operator PlatformWindow* ()
	{
		return PlatformWindow::FromHwnd(m_hWnd);
	}

	operator HWND () const throw()
	{
		return m_hWnd;
	}

	PlatformWindow* operator -> ()
	{
		PlatformWindow* p = PlatformWindow::FromHwnd(m_hWnd);
		ASSERT(p);
		return p;
	}

	HWND m_hWnd;
};

}	// Gui
}	// System
