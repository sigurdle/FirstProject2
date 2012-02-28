namespace System
{
namespace Gui
{

class GUIEXT PathGeometry : public Geometry
{
public:
	CTOR PathGeometry();
	CTOR PathGeometry(ID2D1PathGeometry* d2d1geometry);

//	virtual void RenderFill(ManagedRenderContext renderContext, Brush* brush) override;
//	virtual void RenderStroke(ManagedRenderContext renderContext, Brush* brush, float width) override;
	virtual ID2D1PathGeometry* GetD2DGeometry() override;
	virtual HRGN CreateHRGN() override;

	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled) override;

//	void MoveTo(LDraw::PointF point);
	void LineTo(gm::PointF point);

	DEPENDENCY_CLASS(PathGeometry, Geometry)

	DEPENDENCY_PROPERTY(FillMode, FillMode)

	list<PathFigure*> m_figures;

protected:

	ID2D1PathGeometry* m_D2DGeometry;
};

}	// Gui
}	// System
