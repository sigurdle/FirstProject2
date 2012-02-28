namespace System
{
namespace Gui
{

class GUIEXT WaveformVisual : public UIElement
{
public:
	CTOR WaveformVisual();

	virtual void Render(ManagedRenderContext renderContext) override;

	virtual void OnMouseLeftButtonDown(MouseButtonEventArgs* args) override;
	virtual void OnMouseLeftButtonUp(MouseButtonEventArgs* args) override;
	virtual void OnMouseMove(MouseEventArgs* args) override;

	virtual void OnMouseLeftButtonDoubleClick(MouseButtonEventArgs* args) override;

	DEPENDENCY_PROPERTY(WaveformData*, Data)
	DEPENDENCY_PROPERTY(int64, AtSample)
	DEPENDENCY_PROPERTY(int64, SelectionStartSample)
	DEPENDENCY_PROPERTY(int64, SelectionEndSample)
	DEPENDENCY_PROPERTY(int64, SelectionInitSample)
	DEPENDENCY_PROPERTY(Brush*, ForegroundBrush)
	DEPENDENCY_PROPERTY(Brush*, SelectionBackgroundBrush)

	DEPENDENCY_CLASS(WaveformVisual, UIElement)
};

}	// Gui
}	// System
