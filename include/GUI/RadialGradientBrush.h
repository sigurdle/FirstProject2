namespace System
{
namespace Gui
{

class GUIEXT RadialGradientBrush : public GradientBrush
{
public:

	CTOR RadialGradientBrush();

	virtual ID2D1RadialGradientBrush* Create(RenderTarget* rt, Visual* refVisual) override;

	virtual ID2D1RadialGradientBrush* GetBrush() override
	{
		return m_spRadialGradientBrush;
	}

	DEPENDENCY_PROPERTY(float, RadiusX)
	DEPENDENCY_PROPERTY(float, RadiusY)
	DEPENDENCY_PROPERTY(float, CenterX)
	DEPENDENCY_PROPERTY(float, CenterY)
	DEPENDENCY_PROPERTY(float, OriginOffsetX)
	DEPENDENCY_PROPERTY(float, OriginOffsetY)

	gm::PointF get_Center()
	{
		return gm::PointF(get_CenterX(), get_CenterY());
	}

	gm::PointF get_OriginOffset()
	{
		return gm::PointF(get_OriginOffsetX(), get_OriginOffsetY());
	}

	DEPENDENCY_CLASS(RadialGradientBrush, GradientBrush)

private:

	ID2D1RadialGradientBrush* m_spRadialGradientBrush;
};

}	// Gui
}	// System
