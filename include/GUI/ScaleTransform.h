namespace System
{
namespace Gui
{

class GUIEXT ScaleTransform : public Transform
{
public:

	CTOR ScaleTransform();
	CTOR ScaleTransform(typed<float> scaleX, typed<float> scaleY);

	virtual gm::matrix3f get_Matrix() override;

	DEPENDENCY_CLASS(ScaleTransform, Transform)
//	static DependencyClass* get_Class();
	//static DependencyClass* pClass;

	DEPENDENCY_PROPERTY(float, ScaleX)
	DEPENDENCY_PROPERTY(float, ScaleY)
};

}	// Gui
}	// System
