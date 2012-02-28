namespace System
{
namespace Gui
{

class GUIEXT LinearGradientBrush : public GradientBrush
{
public:

	CTOR LinearGradientBrush();
	CTOR LinearGradientBrush(Point startPoint, Point endPoint, ColorF startColor, ColorF endColor);

	virtual ID2D1LinearGradientBrush* Create(RenderTarget* rt, Visual* refVisual) override;

	virtual ID2D1LinearGradientBrush* GetBrush() override
	{
		return m_spLinearGradientBrush;
	}

	DEPENDENCY_PROPERTY(float, X1)
	DEPENDENCY_PROPERTY(float, Y1)
	DEPENDENCY_PROPERTY(float, X2)
	DEPENDENCY_PROPERTY(float, Y2)

	gm::PointF get_Start();
	gm::PointF get_End();

	DEPENDENCY_CLASS(LinearGradientBrush, GradientBrush)

private:

	ID2D1LinearGradientBrush* m_spLinearGradientBrush;
};

}	// Gui
}	// System
