namespace System
{
namespace Gui
{

class GUIEXT GeneralTransform : public DependencyObject
{
public:
	CTOR GeneralTransform(DependencyClass* depClass);

	DEFINE_THIS(_GeneralTransform)

	virtual gm::PointF TransformPoint(gm::PointF point) abstract;
	virtual void TransformPoints(gm::PointF* destPoints, const gm::PointF* points, unsigned int count) abstract;

	DEPENDENCY_CLASS_ABSTRACT(GeneralTransform, DependencyObject)
};

class GUIEXT _GeneralTransform : public _DependencyObject
{
public:

};

}	// Gui
}	// System
