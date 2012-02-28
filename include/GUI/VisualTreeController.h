namespace System
{
namespace Gui
{

class GUIEXT VisualTreeController : public ITreeViewController
{
public:
	CTOR VisualTreeController(Visual* visual);

	virtual float GetItemHeight(TreeItem item) override;
	virtual int GetItemState(TreeItem item) override;
	virtual void RenderItem(TreeItem item, ManagedRenderContext renderContext, gm::RectF bounds) override;
	virtual int ClickItem(TreeItem item, gm::RectF bounds, gm::PointF pos) override;
	virtual size_t GetChildrenCount(TreeItem item) override;
	virtual TreeItem GetChild(TreeItem item, size_t index) override;
	virtual TreeItem GetRoot() override;

	Visual* m_root;
};

}	// Gui
}	// System
