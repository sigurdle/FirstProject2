namespace System
{
namespace Gui
{

class GUIEXT CompoundGeometry : public Geometry
{
public:

	CTOR CompoundGeometry();

	PathGeometry* GetCombined();

	virtual ID2D1PathGeometry* GetD2DGeometry() override;
	virtual HRGN CreateHRGN() override;
//	virtual void RenderFill(ManagedRenderContext renderContext, Brush* brush) override;
//	virtual void RenderStroke(ManagedRenderContext renderContext, Brush* brush, float width) override;

	list<Geometry*> m_children;
	CombineOp m_combineOp;

	DEPENDENCY_CLASS(CompoundGeometry, Geometry)

protected:

	ID2D1PathGeometry* m_D2DGeometry;
};

}	// Gui
}	// System
