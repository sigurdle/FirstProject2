#include "stdafx.h"
#include "PosterizeEffect.h"

namespace System
{

long PosterizeEffect::get_Levels()
{
	return m_levels;
}

void PosterizeEffect::put_Levels(long value)
{
	m_levels = value;
	GetRParent()->InvalidateRender();
}

void PosterizeEffect::OnRender(UI::Graphics* pGraphics)
{
	LDraw::LookupTables luts;

	for (int i = 0; i < 256; i++)
	{
		luts.m[i][0][0] = i*m_levels / 256;
		luts.m[i][1][1] = i*m_levels / 256;
		luts.m[i][2][2] = i*m_levels / 256;
		luts.m[i][3][3] = i*m_levels / 256;
	}

	pGraphics->SetLookupTables(luts);

	GetRParent()->_OnRender(pGraphics);
}

}
