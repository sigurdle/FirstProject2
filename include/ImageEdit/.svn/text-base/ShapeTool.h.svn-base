namespace System
{
namespace ImageEdit
{

class IMAGEEDITEXT ShapeTool : public ImageTool
{
public:
	virtual void OnMouseDown(BitmapEditor* view, gm::PointF pos) override;
	virtual void OnMouseUp(BitmapEditor* view, gm::PointF pos) override;
	virtual void OnMouseMove(BitmapEditor* view, gm::PointF pos) override;

	DEPENDENCY_CLASS_ABSTRACT(ShapeTool, ImageTool)

//	gm::PointF m_startpos;
//	gm::PointF m_oldpos;

//	int m_dragging;

protected:

	CTOR ShapeTool(Gui::DependencyClass* depClass);
};

class IMAGEEDITEXT EllipseTool : public ShapeTool
{
public:
	CTOR EllipseTool();

	DEPENDENCY_CLASS(EllipseTool, ShapeTool)
};

class IMAGEEDITEXT RectangleTool : public ShapeTool
{
public:
	CTOR RectangleTool();

	DEPENDENCY_CLASS(RectangleTool, ShapeTool)
};

class IMAGEEDITEXT RoundedRectangleTool : public ShapeTool
{
public:
	CTOR RoundedRectangleTool();

	DEPENDENCY_CLASS(RoundedRectangleTool, ShapeTool)
};

class LineTool : public ShapeTool
{
public:
	CTOR LineTool();
};

}	// ImageEdit
}	// System
