namespace System
{
namespace Gui
{

class GUIEXT SolidColorBrush : public Brush
{
public:

	CTOR SolidColorBrush();
	CTOR SolidColorBrush(ColorF color);
	CTOR SolidColorBrush(Color* pColor);
	CTOR SolidColorBrush(float r, float g, float b);
	CTOR SolidColorBrush(float r, float g, float b, float a);

	virtual ID2D1SolidColorBrush* Create(RenderContext* renderContext, Visual* refVisual) override;

	virtual ID2D1SolidColorBrush* GetBrush() override
	{
		return m_d2d1brush;
	}

	virtual bool IsFullyOpaque() override;

	DEPENDENCY_PROPERTY(Color*, Color)

	DEPENDENCY_CLASS(SolidColorBrush, Brush)

private:

	ID2D1SolidColorBrush* m_d2d1brush;
};

}	// Gui
}	// System
