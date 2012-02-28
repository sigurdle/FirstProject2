namespace System
{
namespace Gui
{

class GUIEXT Visual : public Element
{
protected:

	CTOR Visual(DependencyClass* depClass);

public:

	void Render_(ManagedRenderContext renderContext);
	UIElement* HitTest_(gm::PointF point);

	virtual Visual* FindElement(StringIn id);

	bool IsDescendantOf(Visual* pVisual);
	bool IsAscendantOf(Visual* pVisual);

	virtual void RenderRetained(ManagedRetainedRenderContext renderContext);

	virtual Graphics::Bitmap* GetBitmap(Graphics::RenderTarget* rt, int scaledWidth, int scaledHeight, float scaleX, float scaleY);
	void RenderToTarget(Graphics::RenderTarget* rt, ID3D10Texture2D* tempTexture, ID3D10RenderTargetView* tempRenderTargetView, int scaledWidth, int scaledHeight, float scaleX, float scaleY);

	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled) override;

	virtual geometry GetHitGeometry()
	{
		return nullptr;
	}

	HICON CreateHIcon();
	HCURSOR CreateHCursor(float hotspotX, float hotspotY);

	gm::PointF WindowToElement(float windowX, float windowY);

	virtual size_t GetChildrenCount();
	virtual Visual* GetChild(size_t index);

	virtual void AddChild(Visual* child);
	virtual void RemoveChild(Visual* child);

	D2D1_MATRIX_3X2_F get_TransformMatrix();
	D2D1_MATRIX_3X2_F get_TransformToWindowMatrix();
	D2D1_MATRIX_3X2_F get_TransformToVisualMatrix(Visual* visual);

	void InvalidateMeasure();
	void InvalidateArrange();
	void InvalidateVisual();

	virtual bool NeedOffscreenBitmap()
	{
		return false;
	}

	virtual bool IsFullyOpaque()
	{
		return false;
	}

	virtual geometry MakeVisibleGeometry(geometry clip);

	DEPENDENCY_PROPERTY(bool, IsVisible)
	DEPENDENCY_PROPERTY(float, Opacity)
	DEPENDENCY_PROPERTY(UIElement*, Parent)
	DEPENDENCY_PROPERTY(UIElement*, LogicalParent)	// TODO RO
	DEPENDENCY_PROPERTY(Visual*, NextSibling)	// TODO RO
	DEPENDENCY_PROPERTY(Visual*, PreviousSibling)	// TODO RO
	DEPENDENCY_PROPERTY(Window*, ParentWindow)	// TODO RO
	DEPENDENCY_PROPERTY(UIElement*, TemplatedOwner)
	DEPENDENCY_PROPERTY(Transform*, Transform)
	DEPENDENCY_PROPERTY(geometry, VisibleGeometry)
	DEPENDENCY_PROPERTY(geometry, HitGeometry)
	DEPENDENCY_PROPERTY(Brush*, OpacityMask)
	DEPENDENCY_PROPERTY(geometry, Clip)
	DEPENDENCY_PROPERTY(bool, Antialias)
	DEPENDENCY_PROPERTY(int, ChildPosition)	// TODO RO
	DEPENDENCY_PROPERTY(int, TreeLevel)	// TODO RO

	DEPENDENCY_CLASS_ABSTRACT(Visual, Element)

	DEFINE_THIS(_Visual)

// TODO
//	DEPENDENCY_PROPERTY(DependencyProperty*, InheritProperty)

	D2D1_MATRIX_3X2_F m_transformMatrix;
	D2D1_MATRIX_3X2_F m_transformToWindowMatrix;
	gm::BBoxf m_bounds;

	gm::PointF m_visualOffset;

	GroupVisual* m_visuals;	// The default visual
	Visual* m_visual;

protected:

	virtual UIElement* HitTest(gm::PointF point)
	{
		return nullptr;
	}

	virtual void Render(ManagedRenderContext renderContext) abstract;
	virtual void OnSetParent(Visual* parent);

	void SetTreeLevel(int level);

public:

	Effect* m_effect;

	CriticalSection m_markedSection;	// protecting the m_marked variable

	bool m_transformMatrixValid : 1;
	bool m_transformToWindowMatrixValid : 1;
	bool m_visualValid : 1;
	bool m_visibleGeometryValid : 1;
	bool m_measureValid : 1;
	bool m_arrangeValid : 1;
	bool m_inMeasureList : 1;
	bool m_inArrangeList : 1;
	bool m_inMeasure : 1;
	bool m_inArrange : 1;
	bool m_marked : 1;	// General marking (to find common ancestor)
};

class GUIEXT _Visual : public _DependencyObject
{
public:
	CTOR _Visual(const Expressive::expression& exp) : _DependencyObject(exp)
	{
	}

	Expressive::typed_expression<float> getOpacity() const
	{
		return getProperty(Visual::get_OpacityProperty());
	}
};

}	// Gui
}	// System
