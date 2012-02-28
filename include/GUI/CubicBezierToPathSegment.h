namespace System
{
namespace Gui
{

class GUIEXT CubicBezierToPathSegment : public PathSegment
{
public:

	CTOR CubicBezierToPathSegment();
	CTOR CubicBezierToPathSegment(gm::PointF point1, gm::PointF point2, gm::PointF point3);

	virtual PathSegmentType get_Type() const override
	{
		return PathSegmentType_CubicBezierTo;
	}

	virtual void Sink(ID2D1GeometrySink* pGeometrySink) override;

	DEPENDENCY_CLASS(CubicBezierToPathSegment, PathSegment)

	DEPENDENCY_PROPERTY(float, X1)
	DEPENDENCY_PROPERTY(float, Y1)
	DEPENDENCY_PROPERTY(float, X2)
	DEPENDENCY_PROPERTY(float, Y2)
	DEPENDENCY_PROPERTY(float, X3)
	DEPENDENCY_PROPERTY(float, Y3)
};

}	// Gui
}	// System
