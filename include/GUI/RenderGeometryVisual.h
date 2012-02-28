namespace System
{
namespace Gui
{

class GUIEXT RenderGeometryVisual : public UIElement
{
protected:

	CTOR RenderGeometryVisual(DependencyClass* depClass);
	CTOR RenderGeometryVisual(DependencyClass* depClass, const geometry& pgeometry);

public:

	DEFINE_THIS(_RenderGeometryVisual)

	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled) override;

	virtual bool IsFullyOpaque() override;

	DEPENDENCY_CLASS_ABSTRACT(RenderGeometryVisual, UIElement)

	DEPENDENCY_PROPERTY(geometry, Geometry)
	DEPENDENCY_PROPERTY(Brush*, Brush)
};

class _RenderGeometryVisual : public _UIElement
{
public:

};

}	// Gui
}	// System
