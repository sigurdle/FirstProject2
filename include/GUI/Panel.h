namespace System
{
namespace Gui
{

class GUIEXT Panel : public UIElement
{
public:

	CTOR Panel(DependencyClass* depClass);

	virtual size_t GetChildrenCount() override;
	virtual Visual* GetChild(size_t index) override;
	virtual void AddChild(Visual* element) override;

//	virtual void Render(ManagedRenderContext renderContext) override;

	DEPENDENCY_CLASS_ABSTRACT(Panel, UIElement)

	DEPENDENCY_PROPERTY(VisualCollection*, Children)
};

}	// Gui
}	// System
