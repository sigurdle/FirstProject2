namespace System
{
namespace Gui
{

class GUIEXT DrawBitmapVisual : public UIElement
{
public:

	CTOR DrawBitmapVisual();
	CTOR DrawBitmapVisual(Graphics::Bitmap* bitmap);
	CTOR DrawBitmapVisual(Graphics::Bitmap* bitmap, gm::PointF topleft);
	CTOR DrawBitmapVisual(Graphics::Bitmap* bitmap, gm::RectF dstRect);
	CTOR DrawBitmapVisual(Graphics::Bitmap* bitmap, gm::RectF dstRect, float opacity);
	CTOR DrawBitmapVisual(Graphics::Bitmap* bitmap, gm::RectF dstRect, float opacity, gm::RectF srcRect);

	virtual UIElement* HitTest(gm::PointF point);

	gm::RectF get_DestRect();
	void set_DestRect(gm::RectF destRect);

	DEPENDENCY_PROPERTY(Graphics::Bitmap*, Bitmap)
	DEPENDENCY_PROPERTY(float, DestLeft)
	DEPENDENCY_PROPERTY(float, DestTop)
	DEPENDENCY_PROPERTY(float, DestWidth)
	DEPENDENCY_PROPERTY(float, DestHeight)

	// Computed
//	static TypedDependencyProperty<float> DestRightProperty;
//	static TypedDependencyProperty<float> DestBottomProperty;

	DEPENDENCY_CLASS(DrawBitmapVisual, UIElement)

protected:

	virtual void Render(ManagedRenderContext renderContext) override;
	virtual Graphics::Bitmap* GetBitmap(Graphics::RenderTarget* rt, int scaledWidth, int scaledHeight, float scaleX, float scaleY) override;
};

class GUIEXT BitmapVisual : public UIElement
{
public:

	CTOR BitmapVisual();

	virtual UIElement* HitTest(gm::PointF point) override;

	DEFINE_THIS(_BitmapVisual)

	DEPENDENCY_CLASS(BitmapVisual, Visual)

	DEPENDENCY_PROPERTY(IBitmapSource*, Bitmap)
	DEPENDENCY_PROPERTY(RectangleGeometry*, DestRect)

	// computed
	DEPENDENCY_PROPERTY(float, DestLeft)
	DEPENDENCY_PROPERTY(float, DestTop)
	DEPENDENCY_PROPERTY(float, DestWidth)
	DEPENDENCY_PROPERTY(float, DestHeight)
	DEPENDENCY_PROPERTY(float, DestRight)
	DEPENDENCY_PROPERTY(float, DestBottom)

protected:

	virtual void Render(ManagedRenderContext renderContext) override;
	virtual Graphics::Bitmap* GetBitmap(Graphics::RenderTarget* rt, int scaledWidth, int scaledHeight, float scaleX, float scaleY) override;
};

class GUIEXT _BitmapVisual : public _Visual
{
public:
	CTOR _BitmapVisual(const Expressive::expression& exp) : _Visual(exp)
	{
	}

	/*
	_Bitmap getBitmap() const
	{
		return getProperty(BitmapVisual::BitmapProperty);
	}
	*/

	_RectangleGeometry getDestRect() const
	{
		return getProperty(BitmapVisual::get_DestRectProperty());
	}

	Expressive::typed_expression<float> getDestLeft() const
	{
		return getProperty(BitmapVisual::get_DestLeftProperty());
	}

	Expressive::typed_expression<float> getDestTop() const
	{
		return getProperty(BitmapVisual::get_DestTopProperty());
	}

	Expressive::typed_expression<float> getDestWidth() const
	{
		return getProperty(BitmapVisual::get_DestWidthProperty());
	}

	Expressive::typed_expression<float> getDestHeight() const
	{
		return getProperty(BitmapVisual::get_DestHeightProperty());
	}
};

}
}
