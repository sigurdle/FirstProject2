namespace System
{
namespace Gui
{

class GUIEXT RotateTransform : public Transform
{
public:

	CTOR RotateTransform();
	CTOR RotateTransform(FloatRadians angle);

//	float get_AngleDegrees();

//	FloatRadians get_AngleRadians();
//	void set_AngleRadians(FloatRadians angle);

	virtual gm::matrix3f get_Matrix() override;

	DEFINE_THIS(_RotateTransform)

	DEPENDENCY_CLASS(RotateTransform, Transform)

	DEPENDENCY_PROPERTY(float, AngleRadians)
	DEPENDENCY_PROPERTY(float, AngleDegrees)	// Computed
};

class GUIEXT _RotateTransform : public _Transform
{
public:

	Expressive::typed_expression<float> getAngleRadians() const
	{
		return getProperty(RotateTransform::get_AngleRadiansProperty());
	}

	Expressive::typed_expression<float> getAngleDegress() const
	{
		return getProperty(RotateTransform::get_AngleDegreesProperty());
	}
};

}	// Gui
}	// System
