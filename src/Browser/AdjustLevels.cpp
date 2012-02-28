#include "stdafx.h"
#include "AdjustLevels.h"

namespace System
{

void CalculateLevelsLUT(
	uint8 lut[],
	long inputblack, long inputwhite,
	double gamma,
	long outputblack, long outputwhite)
{
	if (gamma == 0.0) gamma = 0.001;
	double gammaexp = 1/gamma;
	
	int inputrange = inputwhite - inputblack;
	int outputrange = outputwhite - outputblack;
	
	for (int i = 0; i < 256; i++)
	{
		int j = i;
		
		j = (j-inputblack)*(255.0/inputrange);						// Input
		j = (int)(pow((double)j/255, gammaexp)*255);	// Gamma
		j = outputblack + (j*(outputrange/255.0));				// Output
		
		if (j < 0) j = 0;
		else if (j > 255) j = 255;
		
		lut[i] = (uint8)j;
	}
}

AdjustLevels::AdjustLevels()
{
	SetClipMode(false);

	for (int i = 0; i < 5; i++)
	{
		m_inputblack[i] = 0;
		m_inputwhite[i] = 255;
		m_outputblack[i] = 0;
		m_outputwhite[i] = 255;
		m_gamma[i] = 1.0;
	}
}

long AdjustLevels::get_InputBlack()
{
	return m_inputblack[0];
}

void AdjustLevels::put_InputBlack(long value)
{
	m_inputblack[0] = value;
	GetRParent()->InvalidateRender();
}

long AdjustLevels::get_InputWhite()
{
	return m_inputwhite[0];
}

void AdjustLevels::put_InputWhite(long value)
{
	m_inputwhite[0] = value;
	GetRParent()->InvalidateRender();
}

long AdjustLevels::get_OutputBlack()
{
	return m_outputblack[0];
}

void AdjustLevels::put_OutputBlack(long value)
{
	m_outputblack[0] = value;
	GetRParent()->InvalidateRender();
}

long AdjustLevels::get_OutputWhite()
{
	return m_outputwhite[0];
}

void AdjustLevels::put_OutputWhite(long value)
{
	m_outputwhite[0] = value;
	GetRParent()->InvalidateRender();
}

double AdjustLevels::get_Gamma()
{
	return m_gamma[0];
}

void AdjustLevels::put_Gamma(double value)
{
	if (value < 0.0001) value = 0.0001;
	m_gamma[0] = value;
	GetRParent()->InvalidateRender();
}

void AdjustLevels::OnRender(UI::Graphics* pGraphics)
{
	uint8 lut[256];
	/*
	uint8 r_lut[256];
	uint8 g_lut[256];
	uint8 b_lut[256];
	uint8 a_lut[256];
	*/

	LDraw::LookupTables luts;

	CalculateLevelsLUT(lut, m_inputblack[0], m_inputwhite[0], m_gamma[0], m_outputblack[0], m_outputwhite[0]);

	/*
	CalculateLevelsLUT(r_lut, m_inputblack[1], m_inputwhite[1], (m_gamma[1]), m_outputblack[1], m_outputwhite[1]);
	CalculateLevelsLUT(g_lut, m_inputblack[2], m_inputwhite[2], (m_gamma[2]), m_outputblack[2], m_outputwhite[2]);
	CalculateLevelsLUT(b_lut, m_inputblack[3], m_inputwhite[3], (m_gamma[3]), m_outputblack[3], m_outputwhite[3]);
	CalculateLevelsLUT(a_lut, m_inputblack[4], m_inputwhite[3], (m_gamma[4]), m_outputblack[4], m_outputwhite[4]);
	*/
	for (int i = 0; i < 256; i++)
	{
		luts.m[i][0][0] = lut[i];
		luts.m[i][1][1] = lut[i];
		luts.m[i][2][2] = lut[i];
		luts.m[i][3][3] = lut[i];
	}

	pGraphics->SetLookupTables(luts);

	GetRParent()->_OnRender(pGraphics);
}

}
