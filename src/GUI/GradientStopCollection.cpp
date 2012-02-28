#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

DependencyClass* GradientStopCollection::get_Class()
{
	static DependencyClass depclass(typeid(GradientStopCollection), Brush::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_StopsProperty(),
	};
	*/

	return &depclass;
}

DependencyClass* GradientStopCollection::pClass(get_Class());

GradientStopCollection::GradientStopCollection() : DependencyObject(get_Class())
{
}

GradientStopCollection::GradientStopCollection(ColorF color1, ColorF color2) : DependencyObject(get_Class())
{
	m_colors.reserve(2);
	m_colors.push_back(color1);
	m_colors.push_back(color2);

	m_offsets.reserve(2);
	m_offsets.push_back(0.0f);
	m_offsets.push_back(1.0f);
}

}
}
