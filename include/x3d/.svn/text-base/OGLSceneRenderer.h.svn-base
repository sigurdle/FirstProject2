#ifndef __x3d_OGLSCENERENDERER_H__
#define __x3d_OGLSCENERENDERER_H__

namespace System
{
namespace x3d
{

class CState
{
public:
	CTOR CState()
	{
		V = gm::vector3f(0, 0, 3);
		_position = gm::vector3f(0, 15, 1);
	}

	gm::vector3f V;	// initial velocity
	gm::vector3f _position;	// initial position
	//gmVector3t<float> _torque;
	gm::matrix3f Orientation;
	gm::vector3f AngularMomentum;	// angular momentum
};

#if 0
class X3DEXT COGLSceneRenderer : 

#if 0

	public ILBasicVideo,
#endif

#if WIN32//USE_GL
//	public MSWindows::WindowImpl,//<COGLSceneRenderer>,
#endif

	public Gui::FrameworkElement
{
public:

	CTOR COGLSceneRenderer();
	~COGLSceneRenderer();

	LDraw::GLState* m_glState;
	LDraw::ClientState* m_clientState;

	double m_currentVideoTime;

	void Integrate(double deltaTime);
	void CheckForCollision(CState* state);

	void Run();

//	virtual void SetOwnerWindow(UI::VisualContentSource* pWindow);

#if 0

BEGIN_MSG_MAP(COGLSceneRenderer)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
/*
	MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
	*/

	MESSAGE_HANDLER(WM_TIMER, OnTimer)

//	MESSAGE_HANDLER(WM_USER+200, OnSoundPlay)
END_MSG_MAP()
#endif

#if USE_GL
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
#endif

	/*
	LRESULT OnSoundPlay(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
	{
		IDSoundBuffer8* dsBuffer8 = (IDSoundBuffer8*)lParam;
		dsBuffer8->Play(0, 0, DSBPLAY_LOOPING);

		return 0;
	}
	*/

	long OnKeyDown();
	long OnKeyUp();

	void/*LRESULT*/ OnTimer(UINT/*UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled*/);

#if 0
	void FireViewChange()
	{
			// ??// TODO
#if !USE_GL
		{
			Invalidate();
		}
#else
		{
			Window::InvalidateRect(NULL);
		}
#endif
	}
#endif

public:
	void BeginMove();
	void Move(int dragging, LDraw::PointI offset);
	void SetScene(Scene* pScene);

#if 0
	virtual void OnRender(UI::Graphics* pGraphics);
#endif
	virtual void OnArrange(LDraw::SizeD finalSize);

//	virtual void handleEvent(System::Event* evt);

	void hittest(float winx, float winy);

#if WIN32
//	virtual bool ProcessWindowMessage( MSWindows::Hwnd hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult/*, DWORD dwMsgMapID*/ );
#endif

#if USE_GL
	virtual bool ProcessWindowMessage( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult/*, DWORD dwMsgMapID*/ )
	{
		bool bHandled = true;

		switch (uMsg)
		{
		case WM_CREATE:
			lResult = OnCreate(uMsg, wParam, lParam, bHandled);
			break;

		case WM_DESTROY:
			lResult = OnDestroy(uMsg, wParam, lParam, bHandled);
			break;

		case WM_SIZE:
			lResult = OnSize(uMsg, wParam, lParam, bHandled);
			break;

		case WM_PAINT:
			lResult = OnPaint(uMsg, wParam, lParam, bHandled);
			break;

		default:
			bHandled = false;
		}

		return bHandled;
	}

// IBasicVideo
	STDMETHOD(set_WindowStyle)(/*[in]*/ long newVal)
	{
		m_style = newVal;
		if (m_hWnd)
		{
			SetWindowLong(GWL_STYLE, m_style);
		}
		return S_OK;
	}

	STDMETHOD(set_Owner)(/*[in]*/ ULONG_PTR newVal)
	{
		if (newVal)
		{
			if (!::IsWindow((HWND)newVal))
				return E_FAIL;
		}

		m_hOwner = (HWND)newVal;

		if (m_hWnd == NULL)
		{
			HWND hWnd = Create(m_hOwner, m_rect, NULL, m_style, 0);
			if (hWnd == NULL)
				return E_FAIL;
		}
		else
		{
			::SetParent(m_hWnd, m_hOwner);
		}

		return S_OK;
	}

	STDMETHOD(SetRect)(/*[in]*/ RECT rect)
	{
		m_rect = rect;
		if (m_hWnd)
		{
			MoveWindow(&m_rect, TRUE);
			return S_OK;
		}
		return S_OK;
	}

#endif

protected:

	int m_dragging;
	LDraw::PointI m_startpoint;

	LDraw::vector3f m_initialPosition;
	AxisAngle m_initialOrientation;

	LDraw::vector3f m_newPosition;
	AxisAngle m_newOrientation;

	int m_display;
	double m_currentSpeed;
	int m_nKeyRepeat;

	Scene* m_scene;

	static Gui::DependencyClass s_Class;

	void InitStacks();

private:

#if USE_GL

	HGLRC  m_hrc;
	DWORD m_style;
	RECT m_rect;
	HWND m_hOwner;
	BOOL bSetupPixelFormat(HDC hdc);
	void CreateContext(HDC hdc, RECT& rc);

#endif

};
#endif

}	// x3d
}

#endif //__x3d_OGLSCENERENDERER_H__
