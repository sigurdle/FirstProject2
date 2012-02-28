namespace System
{
namespace Gui
{

class GUIEXT TreeView : public FrameworkElement
{
public:

	CTOR TreeView(ITreeViewController* controller);

	virtual void Render(ManagedRenderContext renderContext) override;
	virtual void OnMouseLeftButtonDown(MouseButtonEventArgs* args) override;

	ROUTEDEVENT_IMP0(TreeView, RoutedEventArgs, ClickedItem)

	TreeItem m_item;

	DEPENDENCY_CLASS(TreeView, FrameworkElement)

	DEPENDENCY_PROPERTY(Brush*, BackgroundBrush)

protected:

	float RenderItem(ManagedRenderContext renderContext, TreeItem item, float x, float y, float width);
	float RenderItemChildren(ManagedRenderContext renderContext, TreeItem item, float x, float y, float width);

	float ClickItem(TreeItem item, float x, float y, float width, gm::PointF clickpos);
	float ClickItemChildren(TreeItem item, float x, float y, float width, gm::PointF clickpos);
};

}	// Gui
}	// System
