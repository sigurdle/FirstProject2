namespace System
{
namespace Gui
{
namespace Media3D
{

class GUIEXT Object3DVisual : public UIElement
{
public:

	CTOR Object3DVisual();

	virtual void Render(ManagedRenderContext renderContext) override;
	virtual void OnSetRoot(IRootVisual* root) override;

	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyValue, bool handled) override;

	// TODO, separate Camera / Viewpoint

	DEPENDENCY_CLASS(Object3DVisual, UIElement)

	DEPENDENCY_PROPERTY(Camera*, Camera)
	DEPENDENCY_PROPERTY(Visual3D*, Object3D)
};

}	// Media3D
}	// Gui
}	// System
