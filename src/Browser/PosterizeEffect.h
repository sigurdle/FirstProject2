#pragma once

namespace System
{

class PosterizeEffect : public UI::UIElement
{
public:
	PosterizeEffect()
	{
		SetClipMode(false);

		m_levels = 255;
	}

	void OnRender(UI::Graphics* pGraphics);

	long get_Levels();
	void put_Levels(long value);

	long m_levels;
};

}
