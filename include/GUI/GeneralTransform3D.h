namespace System
{
namespace Gui
{
namespace Media3D
{

class GUIEXT GeneralTransform3D : public DependencyObject
{
protected:
	CTOR GeneralTransform3D(DependencyClass* depClass);

public:

	virtual D3DXVECTOR4 Transform(D3DXVECTOR3 v) abstract;

	DEPENDENCY_CLASS_ABSTRACT(GeneralTransform3D, DependencyObject)
};

}	// Media3D
}	// Gui
}	// System
