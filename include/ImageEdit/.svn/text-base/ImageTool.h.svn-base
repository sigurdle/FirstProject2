namespace System
{
namespace ImageEdit
{

class IMAGEEDITEXT ImageTool : public Gui::DependencyObject
{
public:

	virtual void OnMouseDown(BitmapEditor* view, gm::PointF pos) abstract;
	virtual void OnMouseUp(BitmapEditor* view, gm::PointF pos) abstract;
	virtual void OnMouseMove(BitmapEditor* view, gm::PointF pos) abstract;

	virtual void OnRender(BitmapEditor* view, Gui::ManagedRetainedRenderContext pGraphics)
	{
	}

	virtual void OnTimer(BitmapEditor* view)
	{
	}

	DEPENDENCY_CLASS_ABSTRACT(ImageTool, Gui::DependencyObject)

protected:

	CTOR ImageTool(Gui::DependencyClass* depClass) : Gui::DependencyObject(depClass)
	{
	}
};

class PenTool : public ImageTool
{
public:

	CTOR PenTool();

	virtual void OnMouseDown(BitmapEditor* view, gm::PointF pos);
	virtual void OnMouseUp(BitmapEditor* view, gm::PointF pos);
	virtual void OnMouseMove(BitmapEditor* view, gm::PointF pos);

	gm::PointF m_startpos;
	gm::PointF m_oldpos;

//	int m_dragging;
};

}	// ImageEdit
}	// System
