namespace System
{
namespace Gui
{

class GUIEXT Transform : public GeneralTransform
{
protected:

	CTOR Transform(DependencyClass* depClass);

public:

	virtual gm::PointF TransformPoint(gm::PointF point);
	virtual void TransformPoints(gm::PointF* destPoints, const gm::PointF* points, unsigned int count);

	virtual gm::PointF InverseTransformPoint(gm::PointF point);
	virtual void InverseTransformPoints(gm::PointF* destPoints, const gm::PointF* points, unsigned int count);

	virtual gm::matrix3f get_Matrix() abstract;
	virtual gm::matrix3f get_InverseMatrix();

	DEPENDENCY_CLASS_ABSTRACT(Transform, GeneralTransform)
};

class GUIEXT _Transform : public _GeneralTransform
{
public:
};

}	// Gui
}	// System
