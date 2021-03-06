namespace System
{
namespace Gui
{

class GUIEXT StrokeGeometryVisual : public RenderGeometryVisual
{
public:

	CTOR StrokeGeometryVisual();
	CTOR StrokeGeometryVisual(const geometry& pgeometry);

	DEPENDENCY_CLASS(StrokeGeometryVisual, RenderGeometryVisual)

	DEFINE_THIS(_StrokeGeometryVisual)

	virtual void Render(ManagedRenderContext renderContext) override;
	virtual UIElement* HitTest(gm::PointF point) override;

	DEPENDENCY_PROPERTY(float, Width)
};

class _StrokeGeometryVisual : public _RenderGeometryVisual
{
public:

	Expressive::typed_expression<float> getWidth() const
	{
		return getProperty(StrokeGeometryVisual::get_WidthProperty());
	}
};

}	// Gui
}	// System
