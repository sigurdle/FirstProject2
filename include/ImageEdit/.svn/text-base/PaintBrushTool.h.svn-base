namespace System
{
namespace ImageEdit
{

class IMAGEEDITEXT PaintBrushTool : public ImageTool
{
public:

	CTOR PaintBrushTool();

	virtual void OnMouseDown(BitmapEditor* view, gm::PointF pos);
	virtual void OnMouseUp(BitmapEditor* view, gm::PointF pos);
	virtual void OnMouseMove(BitmapEditor* view, gm::PointF pos);

	DEPENDENCY_CLASS(PaintBrushTool, ImageTool)

	DEPENDENCY_PROPERTY(float, Size)
	DEPENDENCY_PROPERTY(Gui::Color*, Color)
	DEPENDENCY_PROPERTY(float, Opacity)
	DEPENDENCY_PROPERTY(float, Spacing)

//	gm::PointF m_startpos;
//	gm::PointF m_oldpos;
};

}	// ImageEdit
}	// System
