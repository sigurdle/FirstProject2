#pragma once

namespace System
{

class HueSaturate : public UI::UIElement
{
public:
	HueSaturate()
	{
		SetClipMode(false);

		m_rotate = 0;
		m_saturate = 1;
	}

	void OnRender(UI::Graphics* pGraphics);

	double get_Rotate();
	void put_Rotate(double value);

	double get_Saturate();
	void put_Saturate(double value);

	double m_rotate;
	double m_saturate;
};

class HueRotateView : public UI::Control
{
public:
	HueRotateView()
	{
		m_dragging = 0;
	}

	virtual LDraw::SizeD OnMeasure(LDraw::SizeD availSize)
	{
		return LDraw::SizeD(110, 110);
	}

	int m_dragging;
	HueSaturate* m_hue;

protected:

	void OnRender(UI::Graphics* pGraphics);
//	void handleEvent(System::Event* evt);
};

}
