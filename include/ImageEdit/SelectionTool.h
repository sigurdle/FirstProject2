namespace System
{
namespace ImageEdit
{

class IMAGEEDITEXT SelectionTool : public ImageTool
{
public:

	virtual void OnTimer(BitmapEditor* view)
	{
	}

	DEPENDENCY_CLASS_ABSTRACT(SelectionTool, ImageTool)

	int m_marchingOffset;

protected:

	CTOR SelectionTool(Gui::DependencyClass* depClass);
};

class IMAGEEDITEXT RectangularSelectionTool : public SelectionTool
{
public:
	CTOR RectangularSelectionTool();

	virtual void OnMouseDown(BitmapEditor* view, gm::PointF pos);
	virtual void OnMouseUp(BitmapEditor* view, gm::PointF pos);
	virtual void OnMouseMove(BitmapEditor* view, gm::PointF pos);
	virtual void OnRender(BitmapEditor* view, Gui::ManagedRetainedRenderContext pGraphics);

	DEPENDENCY_CLASS_ABSTRACT(RectangularSelectionTool, SelectionTool)

//	gm::PointF m_startpos;
//	gm::PointF m_oldpos;

//	int m_dragging;
};

}
}
