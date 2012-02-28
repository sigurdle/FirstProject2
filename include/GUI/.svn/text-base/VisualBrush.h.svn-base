namespace System
{
namespace Gui
{

class GUIEXT VisualBrush : public Brush
{
public:

	CTOR VisualBrush();

	virtual ID2D1BitmapBrush* Create(RenderTarget* rt, Visual* refVisual) override;

	virtual ID2D1BitmapBrush* GetBrush() override
	{
		return m_d2d1BitmapBrush;
	}

private:

	ID2D1BitmapBrush* m_d2d1BitmapBrush;
}

}	// Gui
}	// System
