namespace System
{
namespace ImageEdit
{

class IMAGEEDITEXT TransformTool : public ImageTool
{
public:
	CTOR TransformTool();

	virtual void OnMouseDown(BitmapEditor* view, gm::PointF pos) override;
	virtual void OnMouseUp(BitmapEditor* view, gm::PointF pos) override;
	virtual void OnMouseMove(BitmapEditor* view, gm::PointF pos) override;
	virtual void OnRender(BitmapEditor* view, Gui::ManagedRetainedRenderContext pGraphics) override;

	DEPENDENCY_CLASS(TransformTool, ImageTool)

	gm::matrix3f m_startTransform;

	gm::PointF m_startpos;
	gm::PointF m_oldpos;
	gm::PointF m_pivot;
	gm::PointF m_offset;

	int m_hit;
//	int m_dragging;
};

}
}
