#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(Color*, SolidColorBrush, Color, new Color());

DependencyClass* SolidColorBrush::get_Class()
{
	static DependencyClass depclass(typeid(SolidColorBrush), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_ColorProperty(),
	};

	return &depclass;
}

DependencyClass* SolidColorBrush::pClass(get_Class());

SolidColorBrush::SolidColorBrush() : Brush(get_Class()), m_d2d1brush(NULL)
{
};

SolidColorBrush::SolidColorBrush(ColorF color) : Brush(get_Class()), m_d2d1brush(NULL)
{
	set_Color(new Color(color));
}

SolidColorBrush::SolidColorBrush(Color* pColor) : Brush(get_Class()), m_d2d1brush(NULL)
{
	set_Color(pColor);
}

SolidColorBrush::SolidColorBrush(float r, float g, float b) : Brush(get_Class()), m_d2d1brush(NULL)
{
	set_Color(new Color(r, g, b));
}

SolidColorBrush::SolidColorBrush(float r, float g, float b, float a) : Brush(get_Class(), a), m_d2d1brush(NULL)
{
	set_Color(new Color(r, g, b));
}

ID2D1SolidColorBrush* SolidColorBrush::Create(RenderContext* renderContext, Visual* refVisual)
{
	if (m_d2d1brush == NULL)
	{
		Color* pColor = get_Color();

		D2D1::ColorF d2d1color(pColor->get_Red(), pColor->get_Green(), pColor->get_Blue(), get_BrushOpacity());

		ASSERT(renderContext->GetRT()->m_spRT);
		renderContext->GetRT()->m_spRT->CreateSolidColorBrush(d2d1color, &m_d2d1brush);
	}

	return m_d2d1brush;
}

bool SolidColorBrush::IsFullyOpaque()
{
	/*
	Color* pColor = get_Color();
	if (pColor)
	{
		return o
	return false;
	*/
	return get_BrushOpacity() > 0.9999f;
}

}	// Gui
}	// System
