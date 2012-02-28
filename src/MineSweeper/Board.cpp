
namespace System
{

void Board::Render(Gui::ManagedRenderContext renderContext)
{
	Gui::Brush* fillBrush1 = new LinearGradientBrush(Gui::Point(0, 0), Gui::Point(0, 32), Gui::ColorF(0.8, 0.8, 0.8), Gui::ColorF(0.5, 0.5, 0.5));
	Gui::Brush* borderBrush1 = new LinearGradientBrush(Gui::Point(0, 0), Gui::Point(0, 32), Gui::ColorF(0.4, 0.4, 0.4), Gui::ColorF(0.1, 0.1, 0.1));

	int gridSizeX = 12;
	int gridSizeY = 12;

	for (int y = 0; y < gridSizeY; ++y)
	{
		for (int x = 0; x < gridSizeX; ++x)
		{
			if (true)
			{
				renderContext.FillRectangle(LDraw::RectF(x*32, y*32, (x+1)*32, (y+1)*32, fillBrush1);
				renderContext.DrawRectangle(LDraw::RectF(x*32, y*32, (x+1)*32, (y+1)*32, borderBrush1, 2);
			}
			else
			{
			}
		}
	}
}

}
}