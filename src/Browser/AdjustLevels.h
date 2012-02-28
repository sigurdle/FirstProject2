#pragma once

namespace System
{

class AdjustLevels : public UI::UIElement
{
public:
	CTOR AdjustLevels();

	void OnRender(UI::Graphics* pGraphics);

	long get_InputBlack();
	void put_InputBlack(long value);
	long get_InputWhite();
	void put_InputWhite(long value);
	long get_OutputBlack();
	void put_OutputBlack(long value);
	long get_OutputWhite();
	void put_OutputWhite(long value);
	double get_Gamma();
	void put_Gamma(double value);

	long m_inputblack[5];
	long m_inputwhite[5];
	long m_outputblack[5];
	long m_outputwhite[5];
	double m_gamma[5];
};

}
