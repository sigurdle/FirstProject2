namespace System
{
namespace Gui
{

class GUIEXT WindowThumbnailVisual : public UIElement
{
public:
	CTOR WindowThumbnailVisual();
	CTOR WindowThumbnailVisual(HWND hwndSource);

	DEPENDENCY_CLASS(WindowThumbnailVisual, UIElement)

protected:

	virtual void Render(ManagedRenderContext renderContext) override;

	HWND m_hWndSource;
	gm::RectI m_srcRect;

private:

	HTHUMBNAIL m_phThumbnailId;
};

}	// Gui
}	// System
