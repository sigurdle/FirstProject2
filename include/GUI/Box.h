namespace System
{
namespace Gui
{
namespace Media3D
{

class GUIEXT Box : public Geometry3D
{
public:

	CTOR Box();

	virtual void Render(ManagedRenderContext renderContext) override;

	BoxShape m_shape;

	DEPENDENCY_PROPERTY(Vector3_F*, Size)

	DEPENDENCY_CLASS(Box, Geometry3D)
};

}	// Media3D
}	// Gui
}	// System
