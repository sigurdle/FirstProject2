namespace System
{
namespace Gui
{

class GUIEXT PathFigure : public DependencyObject
{
public:

	CTOR PathFigure();
//	CTOR MoveToPathSegment(LDraw::PointF point);

	/*
	virtual PathSegmentType get_Type() const override
	{
		return PathSegmentType_MoveTo;
	}
	*/

	virtual void LineTo(gm::PointF point);

	virtual void Sink(ID2D1GeometrySink* pGeometrySink);

	vector<PathSegment*> m_segments;	// TODO a property

	static DependencyClass* get_Class();
	static DependencyClass* pClass;

	DEPENDENCY_PROPERTY(bool, Closed)
//	static TypedDependencyProperty<float> YProperty;
};

}	// Gui
}	// System
