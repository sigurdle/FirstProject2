namespace System
{
namespace Gui
{

class GUIEXT ListBox : public ItemsControl
{
public:
	CTOR ListBox();

	DEPENDENCY_CLASS(ListBox, ItemsControl)

	virtual gm::SizeF ArrangeOverride(gm::SizeF size) override;

protected:

	virtual void OnAddElement(UIElement* element) override;
	virtual void OnMouseLeftButtonDown(MouseButtonEventArgs* args) override;

	UIElement* m_contentContainer;
};

}	// Gui
}	// System
