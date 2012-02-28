namespace System
{
namespace Gui
{

interface IPostMessage
{
	virtual void PostMessage(const MSG* msg) abstract;
};

/*
interface IWindow
{
	virtual void OnMouseButtonDown(gm::PointF clientMousePos, int button) abstract;
	virtual void OnMouseButtonDblClk(gm::PointF clientMousePos, int button) abstract;
	virtual void OnMouseButtonUp(gm::PointF clientMousePos, int button) abstract;
	virtual void OnMouseMove(gm::PointF clientMousePos) abstract;
	virtual bool OnSetCursor(UINT hitTest, POINT screenMousePos) abstract;
	virtual void OnKeyDown(UINT wParam, UINT lParam) abstract;
	virtual void OnChar(UINT wParam, UINT lParam) abstract;
	virtual void OnWindowPosChanged(float left, float top) abstract;
	virtual void OnWindowSizeChanged(float width, float height) abstract;
	virtual void OnWindowRectChanged(float left, float top, float width, float height) abstract;
	virtual void OnHelp(HELPINFO* helpinfo) abstract;
#ifndef __LERSTAD__
	virtual HRESULT DragEnter(::IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) abstract;
	virtual HRESULT DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) abstract;
	virtual HRESULT DragLeave() abstract;
	virtual HRESULT Drop(::IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) abstract;
#else
	virtual HRESULT DragEnter(__IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) abstract;
	virtual HRESULT DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) abstract;
	virtual HRESULT DragLeave() abstract;
	virtual HRESULT Drop(__IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) abstract;
#endif
};
*/

class VisualPair
{
public:

	CTOR VisualPair(UIElement* _pVisual, int _level) : pVisual(_pVisual), level(_level)
	{
	}

	bool operator < (const VisualPair& other) const
	{
		return level < other.level;
	}

	bool operator < (int _level) const
	{
		return level < _level;
	}

	UIElement* pVisual;
	int level;
	//IVisualChild* pVisual;	// TODO
};

class GUIEXT PlatformWindowSite : public IPlatformWindowSite
{
public:

	virtual ~PlatformWindowSite()
	{
	}

	bool Show();
	void Hide();

	virtual void OnMouseButtonDown(gm::PointF clientMousePos, int button) override;
	virtual void OnMouseButtonDblClk(gm::PointF clientMousePos, int button) override;
	virtual void OnMouseButtonUp(gm::PointF clientMousePos, int button) override;
	virtual void OnMouseMove(gm::PointF clientMousePos) override;
	virtual bool OnSetCursor(UINT hitTest, POINT screenMousePos) override;
	virtual void OnKeyDown(UINT wParam, UINT lParam) override;
	virtual void OnChar(UINT wParam, UINT lParam) override;
	virtual void OnHelp(HELPINFO* helpinfo) override;
	virtual HRESULT DragEnter(__IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override;
	virtual HRESULT DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override;
	virtual HRESULT DragLeave() override;
	virtual HRESULT Drop(__IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override;

	/*
	virtual void OnWindowPosChanged(float left, float top) override;
	virtual void OnWindowSizeChanged(float width, float height) override;
	virtual void OnWindowRectChanged(float left, float top, float width, float height) override;
	*/

	virtual PopupAnimation get_PopupAnimation() override
	{
		return PopupAnimation_None;
	}

	virtual void OnSize(gm::RectI r) override;
	virtual LRESULT OnSizing(WPARAM edge, RECT* pScreenRect) override;

	virtual UIElement* GetRootWindow() = 0;

	virtual PlatformWindow* GetPlatformWindow() override
	{
		return m_platformWindow;
	}

	inline PlatformWindow* get_PWindow() const throw()
	{
		return m_platformWindow;
	}

	gm::RectI get_ActualWindowRect()
	{
		return m_platformWindow->get_ActualWindowRect();
	}

	OleContainer* m_oleContainer;

	UIElement* m_MouseOverElement;
	UIElement* m_FocusElement;
	UIElement* m_MouseCaptureElement;
	UIElement* m_DragOverElement;

	list<VisualPair> m_measureList;
	list<VisualPair> m_arrangeList;

protected:

	PlatformWindow* m_platformWindow;
	ComPtr<IDropTargetHelper> m_dropTargetHelper;
	__IDataObject* m_pDataObject;

	bool m_inSizeMove;
};

class GUIEXT Window : public ContentControl, public IRootVisual, public IPostMessage, /*public IWindow,*/ public PlatformWindowSite
{
public:

	CTOR Window();
	CTOR Window(Object* content);
	CTOR Window(Object* content, gm::SizeF size);

	virtual String ToString() override;

	virtual void InvalidateRender() override;	// IRootVisual
	virtual OleContainer* GetOleContainer() override;	// IRootVisual
	virtual Graphics::GraphicsI* GetGI() override;	// IRootVisual
	virtual bool ElementCaptureMouse(UIElement* element) override;	// IRootVisual
	virtual bool ElementReleaseMouseCapture(UIElement* element) override;	// IRootVisual
	virtual void ElementSetMouseCursor(UIElement* element) override;	// IRootVisual
	virtual void ElementSetFocus(UIElement* element) override;	// IRootVisual

	virtual void OnWindowPosChanged(float left, float top) override;
	virtual void OnWindowSizeChanged(float width, float height) override;
//	virtual void OnWindowRectChanged(float left, float top, float width, float height) override;

	virtual void OnLostMouseCapture(PlatformWindowProxy) override;	// PlatformWindowSite

	virtual gm::SizeF GetSize();
	virtual gm::RectI GetRect();

	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled) override;
	virtual void OnComputedPropertyValueChanging(PropertyValue* pPropertyVal, const Variant& oldValue, const Variant& newValue, bool handled) override;
	virtual Variant GetLocalPropertyValue(PropertyValue* pPropertyVal) override;

	virtual UIElement* GetRootWindow() override
	{
		return this;
	}

	virtual UIElement* GetRootElement() override
	{
		return get_ShadowTree();
	}

	virtual float GetOpacity() override
	{
		return get_Opacity();
	}

	virtual void SetActive(bool isActive) override
	{
		set_IsActive(isActive);
	}

	void Minimize();
	void Maximize();
	void Restore();

	void AddMeasure(UIElement* pVisual, int level);
	void AddArrange(UIElement* pVisual, int level);

	void MeasureAll();
	void ArrangeAll();

	Graphics::Bitmap* GetContentBitmap();
	Graphics::Bitmap* GetDepthBitmap();

	RectBorder GetBorders();

	float GetBorderLeft();
	float GetBorderTop();
	float GetBorderRight();
	float GetBorderBottom();
	float GetBorderLeftRight();
	float GetBorderTopBottom();

	DEFINE_THIS(_WindowVisual)

	DEPENDENCY_CLASS(Window, ContentControl)

	DEPENDENCY_PROPERTY_RW(float, Left)
	DEPENDENCY_PROPERTY_RW(float, Top)
//	DEPENDENCY_PROPERTY_RW(float, Width)
//	DEPENDENCY_PROPERTY_RW(float, Height)
	DEPENDENCY_PROPERTY_RW(bool, Topmost)
	DEPENDENCY_PROPERTY_RW(String, TitleText)
	DEPENDENCY_PROPERTY_RW(Element*, Icon)
	DEPENDENCY_PROPERTY_RW(geometry, Clip)
//	DEPENDENCY_PROPERTY_RW(UIElement*, Child)
	DEPENDENCY_PROPERTY_RW(Window*, Owner)
	DEPENDENCY_PROPERTY_RW(gm::RectI, RestoreBounds)
	DEPENDENCY_PROPERTY_RW(int, State)
	DEPENDENCY_PROPERTY_RW(bool, ShowInTaskbar)

	DEPENDENCY_PROPERTY_RW(bool, CanMinimize)
	DEPENDENCY_PROPERTY_RW(bool, CanMaximize)
	DEPENDENCY_PROPERTY_RW(bool, CanClose)
	DEPENDENCY_PROPERTY_RW(bool, HasContextHelp)
	DEPENDENCY_PROPERTY_RW(bool, InSizeMove)
#ifndef __LERSTAD__
	DEPENDENCY_PROPERTY_RW(MS::Windows::Shell::TaskbarItemInfo*, TaskbarItemInfo)
#endif
	DEPENDENCY_PROPERTY_RW(String, RT)

// Computed properties
	DEPENDENCY_PROPERTY_RW(float, Right)
	DEPENDENCY_PROPERTY_RW(float, Bottom)
	DEPENDENCY_PROPERTY_RW(float, ClientLeft)
	DEPENDENCY_PROPERTY_RW(float, ClientTop)
	DEPENDENCY_PROPERTY_RW(float, ClientRight)
	DEPENDENCY_PROPERTY_RW(float, ClientBottom)
	DEPENDENCY_PROPERTY_RW(float, ClientWidth)
	DEPENDENCY_PROPERTY_RW(float, ClientHeight)

#ifndef __LERSTAD__
	class GUIEXT ElementProviderRoot : public ElementProviderFragment, public ::IRawElementProviderFragmentRoot
#else
	class GUIEXT ElementProviderRoot : public ElementProviderFragment, public IUnknown
#endif
	{
	public:

		CTOR ElementProviderRoot(Window* owner) : ElementProviderFragment(owner)
		{
		}

#ifndef __LERSTAD__

		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override;

		virtual ULONG STDMETHODCALLTYPE AddRef() override
		{
			++m_refCount;
			return m_refCount;
		}

		virtual ULONG STDMETHODCALLTYPE Release() override
		{
			--m_refCount;
			return m_refCount;
		}

		virtual HRESULT STDMETHODCALLTYPE get_ProviderOptions(ProviderOptions *pRetVal) override;
		virtual HRESULT STDMETHODCALLTYPE GetPatternProvider(PATTERNID patternId, IUnknown **pRetVal) override;
		virtual HRESULT STDMETHODCALLTYPE GetPropertyValue(PROPERTYID propertyId, VARIANT *pRetVal) override;
		virtual HRESULT STDMETHODCALLTYPE get_HostRawElementProvider(IRawElementProviderSimple **pRetVal) override;

		virtual HRESULT STDMETHODCALLTYPE get_FragmentRoot(IRawElementProviderFragmentRoot** pRetVal) override;

	// IRawElementProviderFragmentRoot
		virtual HRESULT STDMETHODCALLTYPE ElementProviderFromPoint(double x, double y, IRawElementProviderFragment **pRetVal) override;
		virtual HRESULT STDMETHODCALLTYPE GetFocus(IRawElementProviderFragment **pRetVal) override;

#endif

		Window* GetOwner()
		{
			return (Window*)m_owner;
		}
	};

	virtual ElementProviderRoot* GetElementProvider() override;

	ElementProviderRoot* GetElementProviderRoot()
	{
		return (ElementProviderRoot*)m_elementProvider;
	}

	static Window* FromHwnd(HWND hWnd);

	static ValueBinding<Window*> ActiveWindowBinding;
	static ValueBinding<Window*> ForegroundWindowBinding;
	static ValueBinding<Window*> FocusWindowBinding;

	static List<Window*>& get_All()
	{
		return s_windows;
	}

	static List<Window*> s_windows;

	static unordered_map<HWND,Window*> m_windows;

public:

	virtual void PostMessage(const MSG* msg) override;	// IPostMessage

protected:


public:

	// TODO, this should follow same node input/output as everything else??
	list<Window*> m_popups;
	list<Window*>::iterator m_owner_it;

	Event1<Window*> OnMove;
	Event1<Window*> OnSize;
	Event1<Window*> OnSizing;
	Event1<Window*> OnEnterSize;
	Event1<Window*> OnExitSize;

private:

	void Init();
};

class GUIEXT _WindowVisual : public _UIElement
{
public:

	CTOR _WindowVisual(const Expressive::expression& exp) : _UIElement(exp)
	{
	}

	Expressive::methodcall0<float> getBorderLeft() const
	{
		return new Expressive::MethodCall0Expression<float>(*this, GetDispatch(typeid(Window).GetType()->AsClass())->GetMethod(S("GetBorderLeft")));
	}

	Expressive::methodcall0<float> getBorderTop() const
	{
		return new Expressive::MethodCall0Expression<float>(*this, GetDispatch(typeid(Window).GetType()->AsClass())->GetMethod(S("GetBorderTop")));
	}

	Expressive::methodcall0<float> getBorderRight() const
	{
		return new Expressive::MethodCall0Expression<float>(*this, GetDispatch(typeid(Window).GetType()->AsClass())->GetMethod(S("GetBorderRight")));
	}

	Expressive::methodcall0<float> getBorderBottom() const
	{
		return new Expressive::MethodCall0Expression<float>(*this, GetDispatch(typeid(Window).GetType()->AsClass())->GetMethod(S("GetBorderBottom")));
	}

	Expressive::methodcall0<float> getBorderLeftRight() const
	{
		return new Expressive::MethodCall0Expression<float>(*this, GetDispatch(typeid(Window).GetType()->AsClass())->GetMethod(S("GetBorderLeftRight")));
	}

	Expressive::methodcall0<float> getBorderTopBottom() const
	{
		return new Expressive::MethodCall0Expression<float>(*this, GetDispatch(typeid(Window).GetType()->AsClass())->GetMethod(S("GetBorderTopBottom")));
	}

	Expressive::typed_expression<float> getWidth() const
	{
		return getProperty(Window::get_WidthProperty());
	}

	Expressive::typed_expression<float> getHeight() const
	{
		return getProperty(Window::get_HeightProperty());
	}

	Expressive::typed_expression<float> getLeft() const
	{
		return getProperty(Window::get_LeftProperty());
	}

	Expressive::typed_expression<float> getTop() const
	{
		return getProperty(Window::get_TopProperty());
	}

	Expressive::typed_expression<float> getRight() const
	{
		return getProperty(Window::get_RightProperty());
	}

	Expressive::typed_expression<float> getBottom() const
	{
		return getProperty(Window::get_BottomProperty());
	}

	Expressive::typed_expression<float> getClientWidth() const
	{
		return getProperty(Window::get_ClientWidthProperty());
	}

	Expressive::typed_expression<float> getClientHeight() const
	{
		return getProperty(Window::get_ClientHeightProperty());
	}

	Expressive::typed_expression<float> getClientLeft() const
	{
		return getProperty(Window::get_ClientLeftProperty());
	}

	Expressive::typed_expression<float> getClientTop() const
	{
		return getProperty(Window::get_ClientTopProperty());
	}

	Expressive::typed_expression<float> getClientRight() const
	{
		return getProperty(Window::get_ClientRightProperty());
	}

	Expressive::typed_expression<float> getClientBottom() const
	{
		return getProperty(Window::get_ClientBottomProperty());
	}

	_String getTitleText() const
	{
		return getProperty(Window::get_TitleTextProperty());
	}

	Expressive::typed_expression<bool> getTopmost() const
	{
		return getProperty(Window::get_TopmostProperty());
	}

	_WindowVisual getOwner() const
	{
		return getProperty(Window::get_OwnerProperty());
	}

	/*
	_Visual getChild() const
	{
		return getProperty(Window::get_ChildProperty());
	}
	*/

	Expressive::typed_expression<geometry> getClip() const
	{
		return getProperty(Window::get_ClipProperty());
	}
};

}	// Gui
}	// System
