namespace System
{
namespace Gui
{

class GUIEXT RoundedRectangleGeometry : public Geometry
{
public:

	CTOR RoundedRectangleGeometry();
	CTOR RoundedRectangleGeometry(typed<float> left, typed<float> top, typed<float> width, typed<float> height, typed<float> rx, typed<float> ry);

	virtual void RenderFill(ManagedRenderContext renderContext, Brush* brush) override;
	virtual void RenderStroke(ManagedRenderContext renderContext, Brush* brush, float width) override;
	virtual ID2D1RoundedRectangleGeometry* GetD2DGeometry() override;
	virtual HRGN CreateHRGN() override;

	DEPENDENCY_PROPERTY(float, Left)
	DEPENDENCY_PROPERTY(float, Top)
	DEPENDENCY_PROPERTY(float, Width)
	DEPENDENCY_PROPERTY(float, Height)
	DEPENDENCY_PROPERTY(float, RadiusX)
	DEPENDENCY_PROPERTY(float, RadiusY)

	DEPENDENCY_CLASS(RoundedRectangleGeometry, Geometry)

private:

	ID2D1RoundedRectangleGeometry* m_D2DGeometry;
};

}	// Gui
}	// System
