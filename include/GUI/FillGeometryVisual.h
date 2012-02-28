namespace System
{
namespace Gui
{

class GUIEXT FillGeometryVisual : public RenderGeometryVisual
{
public:

	CTOR FillGeometryVisual();
	CTOR FillGeometryVisual(const geometry& pgeometry);

	DEFINE_THIS(_FillGeometryVisual)

	virtual void Render(ManagedRenderContext renderContext);
	virtual UIElement* HitTest(gm::PointF point);

	DEPENDENCY_CLASS(FillGeometryVisual, RenderGeometryVisual)
};

class _FillGeometryVisual : public _RenderGeometryVisual
{
public:

};

}	// Gui
}	// System
