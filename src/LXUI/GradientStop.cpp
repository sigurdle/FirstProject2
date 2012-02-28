#include "stdafx.h"
#include "LXUI2.h"
#include "GradientStop.h"

namespace System
{
namespace UI
{

Color Colors::s_Transparent;
Color Colors::s_Black = Color::FromRgb(0,0,0);
Color Colors::s_White = Color::FromRgb(255,255,255);

///
DependencyProperty* GradientStop::s_OffsetProperty = RegisterProperty(WSTR("Offset"), typeid(double), typeid(GradientStop), DoubleObject::GetObject(0.0), PropertyMetaData(None));
DependencyProperty* GradientStop::s_ColorProperty = RegisterProperty(WSTR("Color"), typeid(Color), typeid(GradientStop), &Colors::s_Transparent, PropertyMetaData(None));

GradientStop::GradientStop()
{
//	m_Offset = 0;
//	m_Color = NULL;
//	m_Opacity = 1.0;
}

GradientStop::GradientStop(double offset, Color color)
{
	set_Offset(offset);
	set_Color(color);
}

double GradientStop::get_Offset()
{
	return static_cast<DoubleObject*>(GetValue(get_OffsetProperty()))->GetValue();
}

void GradientStop::set_Offset(double offset)
{
	SetValue(get_OffsetProperty(), DoubleObject::GetObject(offset));
}

Color GradientStop::get_Color()
{
	return *static_cast<Color*>(GetValue(get_ColorProperty()));
}

void GradientStop::set_Color(Color color)
{
	Color* pColor;
	// TODO, not here
	if (color == Colors::s_Transparent)	pColor = &Colors::s_Transparent;
	else if (color == Colors::s_Black)	pColor = &Colors::s_Black;
	else if (color == Colors::s_White)	pColor = &Colors::s_White;
	else
		pColor = new Color(color);

	SetValue(get_ColorProperty(), pColor);
}

}	// UI
}
