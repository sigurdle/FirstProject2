namespace System
{
namespace Gui
{
namespace Media3D
{

class GUIEXT ScaleTransform3D : public Transform3D
{
public:

	CTOR ScaleTransform3D();
	CTOR ScaleTransform3D(typed<float> scaleX, typed<float> scaleY, typed<float> scaleZ);

	virtual D3DXMATRIX GetMatrix() override;

	static DependencyClass* get_Class();
	static DependencyClass* pClass;
	typedef Transform3D baseClass;

	DEPENDENCY_PROPERTY(float, ScaleX)
	DEPENDENCY_PROPERTY(float, ScaleY)
	DEPENDENCY_PROPERTY(float, ScaleZ)
};

}	// Media3D
}	// Gui
}	// System
