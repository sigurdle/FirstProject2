namespace System
{

namespace Gui
{

template<class class_type, class arg0_type, class arg1_type> class mem_funo : public Object, public IFunction2<void, arg0_type, arg1_type>
{
public:

#ifndef __LERSTAD__
	CTOR mem_funo(void (class_type::*memf)(arg1_type)) : m_memf(memf)
	{
	}
#endif

	virtual size_t get_NumArgs() override
	{
		return 2;
	}

	virtual void Call(arg0_type arg0, arg1_type arg1)
	{
#ifndef __LERSTAD__
		((static_cast<class_type*>(arg0))->*m_memf)(arg1);
	//	(arg0->*m_memf)(arg1);
#endif
	}

	void (class_type::*m_memf)(arg1_type);
};

typedef Event2<Object*, MouseEventArgs*> type1_;
typedef Event2<Object*, MouseButtonEventArgs*> type2_;
typedef Event2<Object*, KeyEventArgs*> type3_;
typedef Event2<Object*, TextCompositionEventArgs*> type4_;
typedef Event2<Object*, DragEventArgs*> type5_;
typedef Event2<Object*, ContextMenuEventArgs*> type6_;
typedef Event2<Object*, QueryCursorEventArgs*> type7_;
typedef Event2<Object*, RoutedEventArgs*> type8_;

typedef mem_funo<UIElement, Object*, MouseEventArgs*> type1;
typedef mem_funo<UIElement, Object*, MouseButtonEventArgs*> type2;
typedef mem_funo<UIElement, Object*, KeyEventArgs*> type3;
typedef mem_funo<UIElement, Object*, TextCompositionEventArgs*> type4;
typedef mem_funo<UIElement, Object*, DragEventArgs*> type5;
typedef mem_funo<UIElement, Object*, ContextMenuEventArgs*> type6;
typedef mem_funo<UIElement, Object*, QueryCursorEventArgs*> type7;
typedef mem_funo<UIElement, Object*, RoutedEventArgs*> type8;

class GUIEXT UIElement : public Visual, public IInputElement
{
protected:
	CTOR UIElement(DependencyClass* depClass);
	CTOR UIElement(DependencyClass* depClass, gm::SizeF size);

public:

	virtual ~UIElement();

	virtual geometry GetHitGeometry() override;
	virtual geometry MakeVisibleGeometry(geometry clip) override;

	virtual void Render(ManagedRenderContext renderContext) override;
	virtual void RenderRetained(ManagedRetainedRenderContext renderContext) override;

	virtual size_t GetChildrenCount() override;
	virtual Visual* GetChild(size_t index) override;
	virtual size_t GetLogicalChildrenCount();
	virtual Object* GetLogicalChild(size_t position);
	virtual Object* ReplaceChild(size_t position, Object* newChild);	// Logical

//	void InsertChild(UIElement* before, UIElement* child);

	UIElement* FindCommonAncestor(UIElement* element1);

	void Measure(gm::SizeF availSize);
	void Arrange(gm::RectF finalRect);

	virtual void OnChildDesiredSizeChanged(UIElement* child);

//	virtual void AddHandler(RoutedEvent* routedEvent, Ev::EventHandler handler);
//	virtual void RemoveHandler(RoutedEvent* routedEvent, Ev::EventHandler handler);
	virtual bool CaptureMouse() override;
	virtual void ReleaseMouseCapture() override;

	Event* get_RoutedEvent(RoutedEvent* routedEvent);

//	virtual void AddHandler(RoutedEvent* routedEvent, stub_interface_base* handler);
	virtual void RaiseEvent(RoutedEventArgs* args);

	Layout* get_Layout();
	void set_Layout(Layout* layout);

	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled) override;
	virtual void OnComputedPropertyValueChanging(PropertyValue* pPropertyVal, const Variant& oldValue, const Variant& newValue, bool handled) override;

	DEFINE_THIS(_UIElement)

	DEPENDENCY_CLASS_ABSTRACT(UIElement, Visual)

	DEPENDENCY_PROPERTY_RW(float, Width)
	DEPENDENCY_PROPERTY_RW(float, Height)
	DEPENDENCY_PROPERTY_RW(float, MinWidth)
	DEPENDENCY_PROPERTY_RW(float, MinHeight)
	DEPENDENCY_PROPERTY_RW(float, MaxWidth)
	DEPENDENCY_PROPERTY_RW(float, MaxHeight)
	DEPENDENCY_PROPERTY_RO(float, ActualWidth)
	DEPENDENCY_PROPERTY_RO(float, ActualHeight)
	DEPENDENCY_PROPERTY_RW(bool, AllowDrop)
	DEPENDENCY_PROPERTY_RW(bool, IsActive)
	DEPENDENCY_PROPERTY_RW(bool, IsActivatable)
	DEPENDENCY_PROPERTY_RW(bool, IsEnabled)
	DEPENDENCY_PROPERTY_RO(bool, IsMouseCaptured)
	DEPENDENCY_PROPERTY_RW(bool, HasFocus)
	DEPENDENCY_PROPERTY_RW(bool, IsFocusable)
	DEPENDENCY_PROPERTY_RO(bool, IsMouseOver)
	DEPENDENCY_PROPERTY_RO(bool, IsMouseDirectlyOver)
	DEPENDENCY_PROPERTY_RO(bool, IsStylusOver)
	DEPENDENCY_PROPERTY_RO(bool, IsStylusDirectlyOver)
	DEPENDENCY_PROPERTY_RW(Cursor*, Cursor)
	DEPENDENCY_PROPERTY_RO(UIElement*, ShadowTree)

	DEPENDENCY_PROPERTY_RW(Thickness, BorderThickness)
	DEPENDENCY_PROPERTY_RW(Thickness, Padding)
	DEPENDENCY_PROPERTY_RW(Thickness, Margin)

	DEPENDENCY_PROPERTY_RW(HorizontalAlignment, HorizontalAlignment)
	DEPENDENCY_PROPERTY_RW(HorizontalAlignment, HorizontalContentAlignment)

	DEPENDENCY_PROPERTY_RW(Visual*, FirstChild)	// TODO RO
	DEPENDENCY_PROPERTY_RW(Visual*, LastChild)	// TODO RO

	// Routed Events

	ROUTEDEVENT(MouseButtonEventArgs, MouseButtonDown) {}
	ROUTEDEVENT(MouseButtonEventArgs, MouseButtonDownPreview) {}

	ROUTEDEVENT(MouseButtonEventArgs, MouseButtonUp) {}
	ROUTEDEVENT(MouseButtonEventArgs, MouseButtonUpPreview) {}

//	ROUTEDEVENT_IMP0(UIElement, MouseButtonEventArgs, MouseButtonDown)
//	ROUTEDEVENT_IMP0(UIElement, MouseButtonEventArgs, MouseButtonUp)
	ROUTEDEVENT_IMP0(UIElement, MouseButtonEventArgs, MouseLeftButtonDown)
	ROUTEDEVENT_IMP0(UIElement, MouseButtonEventArgs, MouseRightButtonDown)
	ROUTEDEVENT_IMP0(UIElement, MouseButtonEventArgs, MouseMiddleButtonDown)
	ROUTEDEVENT_IMP0(UIElement, MouseButtonEventArgs, MouseLeftButtonUp)
	ROUTEDEVENT_IMP0(UIElement, MouseButtonEventArgs, MouseRightButtonUp)
	ROUTEDEVENT_IMP0(UIElement, MouseButtonEventArgs, MouseMiddleButtonUp)
	ROUTEDEVENT_IMP0(UIElement, MouseButtonEventArgs, MouseLeftButtonDoubleClick)
	ROUTEDEVENT_IMP0(UIElement, MouseButtonEventArgs, MouseRightButtonDoubleClick)
	ROUTEDEVENT_IMP0(UIElement, MouseButtonEventArgs, MouseMiddleButtonDoubleClick)

	ROUTEDEVENT_IMP0(UIElement, MouseEventArgs, MouseMove)
	ROUTEDEVENT_IMP0(UIElement, KeyEventArgs, Key)
	ROUTEDEVENT_IMP0(UIElement, TextCompositionEventArgs, TextComposition)

	ROUTEDEVENT_IMP0(UIElement, DragEventArgs, DragEnter)
	ROUTEDEVENT_IMP0(UIElement, DragEventArgs, DragLeave)
	ROUTEDEVENT_IMP0(UIElement, DragEventArgs, DragOver)
	ROUTEDEVENT_IMP0(UIElement, DragEventArgs, DragDrop)
	ROUTEDEVENT_IMP0(UIElement, ContextMenuEventArgs, ContextMenuOpening)
	ROUTEDEVENT_IMP1(UIElement, QueryCursorEventArgs, QueryCursor)

	ROUTEDEVENT_IMP0(UIElement, RoutedEventArgs, Activate)

public:

	gm::SizeF get_ActualSize()
	{
		return gm::SizeF(get_ActualWidth(), get_ActualHeight());
	}

	gm::SizeF get_DesiredSize()
	{
		return m_desiredSize;
	}

	virtual void SetCaptureMouse(bool b) override;
	virtual void Focus();
	virtual void OnAddChild(VisualCollection* collection, Visual* element);
	virtual void OnSetRoot(IRootVisual* root) override;

	void UpdateLayout();

	friend class Window;
	friend class PlatformWindow;
	friend class PlatformWindowSite;

	gm::SizeF m_desiredSize;
	gm::SizeF m_availSize;

#ifndef __LERSTAD__
	class GUIEXT ElementProvider : public Object, public ::IRawElementProviderSimple
#else
	class GUIEXT ElementProvider : public Object, public IUnknown
#endif
	{
	public:

		CTOR ElementProvider(UIElement* owner) : m_owner(owner), m_refCount(0)
		{
		}

		UIElement* GetOwner()
		{
			return m_owner;
		}

	protected:

		UIElement* m_owner;
		long m_refCount;
	};


#ifndef __LERSTAD__
	class GUIEXT ElementProviderFragment : public ElementProvider, public ::IRawElementProviderFragment
#else
	class GUIEXT ElementProviderFragment : public ElementProvider, public IUnknown
#endif
	{
	public:

		CTOR ElementProviderFragment(UIElement* owner) : ElementProvider(owner)
		{
		}

#ifndef __LERSTAD__
		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override;

		virtual ULONG STDMETHODCALLTYPE AddRef() override
		{
			++m_refCount;
			return m_refCount;
		}

		virtual ULONG STDMETHODCALLTYPE Release() override
		{
			ASSERT(m_refCount > 0);
			--m_refCount;
			return m_refCount;
		}

		virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ProviderOptions(ProviderOptions *pRetVal) override;
		virtual HRESULT STDMETHODCALLTYPE GetPatternProvider(PATTERNID patternId, __RPC__deref_out_opt IUnknown **pRetVal) override;
		virtual HRESULT STDMETHODCALLTYPE GetPropertyValue(PROPERTYID propertyId, __RPC__out VARIANT *pRetVal) override;
		virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_HostRawElementProvider(__RPC__deref_out_opt IRawElementProviderSimple **pRetVal) override;

	//
		virtual HRESULT STDMETHODCALLTYPE Navigate(NavigateDirection direction, IRawElementProviderFragment **pRetVal) override;
        
		virtual HRESULT STDMETHODCALLTYPE GetRuntimeId(SAFEARRAY** pRetVal) override;
		virtual HRESULT STDMETHODCALLTYPE get_BoundingRectangle(UiaRect* pRetVal) override;
		virtual HRESULT STDMETHODCALLTYPE GetEmbeddedFragmentRoots(SAFEARRAY** pRetVal) override;
		virtual HRESULT STDMETHODCALLTYPE SetFocus() override;
		virtual HRESULT STDMETHODCALLTYPE get_FragmentRoot(IRawElementProviderFragmentRoot** pRetVal) override;
#endif
	};

	virtual ElementProviderFragment* GetElementProvider();

protected:

	virtual UIElement* HitTest(gm::PointF point) override;

	virtual void MeasureCore(gm::SizeF availSize);
	virtual void ArrangeCore(gm::RectF finalRect);

	virtual gm::SizeF ArrangeOverride(gm::SizeF size);
	virtual gm::SizeF MeasureOverride(gm::SizeF availSize);

	bool IsMeasureValid()
	{
		return m_measureValid;
	}

	bool IsArrangeValid()
	{
		return m_arrangeValid;
	}

	ElementProviderFragment* m_elementProvider;

	/*
protected:


	class Init
	{
	public:
		CTOR Init();
	};

	static Init init;
	*/

private:

	Layout* m_layout;	// TODO dep property

	Event* m_events[22];	// TODO
};

class GUIEXT _UIElement : public _Element
{
public:

	CTOR _UIElement(const Expressive::expression& exp) : _Element(exp)
	{
	}

	Expressive::typed_expression<float> getWidth() const
	{
		return getProperty(UIElement::get_WidthProperty());
	}

	Expressive::typed_expression<float> getHeight() const
	{
		return getProperty(UIElement::get_HeightProperty());
	}
};

#ifndef __LERSTAD__

template<class class_type, class arg1_type> mem_funo<class_type, Object*, arg1_type>* mem_fun(void (class_type::*memf)(arg1_type))
{
	return new mem_funo<class_type, Object*, arg1_type>(memf);
}

#endif

}	// Gui
}	// System
