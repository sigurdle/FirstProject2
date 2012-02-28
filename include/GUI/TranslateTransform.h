namespace System
{
namespace Gui
{

class GUIEXT TranslateTransform : public Transform
{
public:

	CTOR TranslateTransform();
	CTOR TranslateTransform(float x, float y);
	CTOR TranslateTransform(gm::PointF point);
	CTOR TranslateTransform(const Expressive::typed_expression<float>& x, const Expressive::typed_expression<float>& y);

	virtual gm::PointF TransformPoint(gm::PointF point) override;
	virtual void TransformPoints(gm::PointF* destPoints, const gm::PointF* points, unsigned int count) override;

	virtual gm::PointF InverseTransformPoint(gm::PointF point) override;
	virtual void InverseTransformPoints(gm::PointF* destPoints, const gm::PointF* points, unsigned int count) override;

	virtual gm::matrix3f get_Matrix() override;
	virtual gm::matrix3f get_InverseMatrix() override;

	DEPENDENCY_PROPERTY(float, TranslateX)
	DEPENDENCY_PROPERTY(float, TranslateY)

	DEPENDENCY_CLASS(TranslateTransform, Transform)
};

}	// Gui
}	// System
