namespace System
{
namespace Gui
{

class GUIEXT EllipseGeometry : public Geometry
{
public:
	CTOR EllipseGeometry();
	CTOR EllipseGeometry(float cx, float cy, float rx, float ry);

	virtual ID2D1EllipseGeometry* GetD2DGeometry() override;
	virtual HRGN CreateHRGN() override;
	virtual void RenderFill(ManagedRenderContext renderContext, Brush* brush) override;
	virtual void RenderStroke(ManagedRenderContext renderContext, Brush* brush, float width) override;
	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled) override;

	gm::PointF get_Center();
	gm::PointF get_Radius();

	virtual gm::RectF GetBounds() override;

	DEPENDENCY_CLASS(EllipseGeometry, Geometry)

	DEPENDENCY_PROPERTY(float, CenterX)
	DEPENDENCY_PROPERTY(float, CenterY)
	DEPENDENCY_PROPERTY(float, RadiusX)
	DEPENDENCY_PROPERTY(float, RadiusY)

protected:

	ID2D1EllipseGeometry* m_D2DGeometry;
};

}	// Gui
}	// System
