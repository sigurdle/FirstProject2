#pragma once

namespace System
{

class MinimumEffect : public UI::UIElement
{
public:
	MinimumEffect();

	void OnRender(UI::Graphics* pGraphics);

	double get_Radius();
	void put_Radius(double value);

	double m_radius;
};

}
