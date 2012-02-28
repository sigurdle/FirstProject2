namespace System
{
namespace ImageEdit
{

class IMAGEEDITEXT HandTool : public ImageTool
{
public:
	CTOR HandTool();

	virtual void OnMouseDown(BitmapEditor* view, gm::PointF pos);
	virtual void OnMouseUp(BitmapEditor* view, gm::PointF pos);
	virtual void OnMouseMove(BitmapEditor* view, gm::PointF pos);

	DEPENDENCY_CLASS(HandTool, ImageTool)

	vector<gm::matrix3f> m_startTransform;

	gm::PointF m_startpos;
	gm::PointF m_oldpos;

//	int m_dragging;
};

}
}
