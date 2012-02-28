namespace System
{
namespace Gui
{
namespace Media3D
{

class GUIEXT TranslateTransform3D : public Transform3D
{
public:

	CTOR TranslateTransform3D();
	CTOR TranslateTransform3D(typed<float> translateX, typed<float> translateY, typed<float> translateZ);

	virtual D3DXMATRIX GetMatrix() override;

	DEPENDENCY_PROPERTY(float, TranslateX)
	DEPENDENCY_PROPERTY(float, TranslateY)
	DEPENDENCY_PROPERTY(float, TranslateZ)

	DEPENDENCY_CLASS(TranslateTransform3D, Transform3D)
};

}	// Media3D
}	// Gui
}	// System
