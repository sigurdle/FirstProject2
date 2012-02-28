namespace System
{
namespace Gui
{
namespace Media3D
{

class GUIEXT Sphere : public Geometry3D
{
public:

	CTOR Sphere();

	virtual void Render(ManagedRenderContext renderContext) override;

	DEPENDENCY_PROPERTY(float, Radius)

	DEPENDENCY_CLASS(Sphere, Geometry3D)
};

}	// Media3D
}	// Gui
}	// System
