namespace System
{
namespace Gui
{

enum Orientation
{
	Orientation_Horizontal,
	Orientation_Vertical,
};

class GUIEXT Track : public FrameworkElement
{
public:

	CTOR Track();

	virtual void Render(ManagedRenderContext renderContext) override;
	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertValue, bool handled) override;

	virtual void OnMouseLeftButtonDown(MouseButtonEventArgs* args) override;
	virtual void OnMouseLeftButtonUp(MouseButtonEventArgs* args) override;
	virtual void OnMouseMove(MouseEventArgs* args) override;

	DEPENDENCY_PROPERTY(Orientation, Orientation)
	DEPENDENCY_PROPERTY(float, Minimum)
	DEPENDENCY_PROPERTY(float, Maximum)
	DEPENDENCY_PROPERTY(float, ViewportSize)
	DEPENDENCY_PROPERTY(float, Value)
	DEPENDENCY_PROPERTY(float, PreviousValue)

	DEPENDENCY_CLASS(Track, FrameworkElement)

	void SetIt();

	gm::PointF m_mousepos;
	gm::RectF m_slidR;
	gm::RectF m_knobR;

	double m_totalDelta;
};

}	// Gui
}	// System
