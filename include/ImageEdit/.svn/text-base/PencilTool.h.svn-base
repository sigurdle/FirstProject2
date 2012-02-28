namespace System
{
namespace ImageEdit
{

class IMAGEEDITEXT PencilTool : public ImageTool
{
public:

	CTOR PencilTool();

	virtual void OnMouseDown(BitmapEditor* view, gm::PointF pos);
	virtual void OnMouseUp(BitmapEditor* view, gm::PointF pos);
	virtual void OnMouseMove(BitmapEditor* view, gm::PointF pos);

	DEPENDENCY_CLASS(PencilTool, ImageTool)

	DEPENDENCY_PROPERTY(float, Size)
	DEPENDENCY_PROPERTY(Gui::Color*, Color)
	DEPENDENCY_PROPERTY(float, Opacity)
	DEPENDENCY_PROPERTY(float, Spacing)

//	gm::PointF m_startpos;
//	gm::PointF m_oldpos;
};

}	// ImageEdit
}	// System
