namespace System
{
namespace Gui
{

class GUIEXT PathSegment : public DependencyObject
{
public:

	enum PathSegmentType
	{
//		PathSegmentType_MoveTo = 1,
		PathSegmentType_LineTo,
		PathSegmentType_CubicBezierTo,
	};

	CTOR PathSegment(DependencyClass* depClass);

	virtual PathSegmentType get_Type() const = 0;
	virtual void Sink(ID2D1GeometrySink* pGeometrySink) = 0;

	static DependencyClass* get_Class();
	static DependencyClass* pClass;
	typedef DependencyObject baseClass;

//	DEPENDENCY_CLASS(PathSegment, DependencyObject)
};

}	// Gui
}	// System
