namespace System
{
namespace Gui
{
namespace Media3D
{

class GUIEXT PointLight : public Light
{
public:
	CTOR PointLight();

	virtual void SetLight(ImmediateRenderContext*) override;

	DEPENDENCY_PROPERTY(Vector3_F*, Location)
	DEPENDENCY_PROPERTY(Vector3_F*, Attenuation)

	DEPENDENCY_CLASS(PointLight, Light)
};

}	// Media3D
}	// Gui
}	// System
