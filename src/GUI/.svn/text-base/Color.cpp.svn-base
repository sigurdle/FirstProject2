#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(float, Color, Red, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, Color, Green, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, Color, Blue, 0.0f)

DependencyClass* Color::get_Class()
{
	static DependencyClass depclass(typeid(Color), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_RedProperty(),
		get_GreenProperty(),
		get_BlueProperty(),
	};

	return &depclass;
}

DependencyClass* Color::pClass(get_Class());

Color* Color::get_BlackColor()
{
	static Color color(0,0,0);
	return &color;
}

Color* Color::get_WhiteColor()
{
	static Color color(1.0f, 1.0f, 1.0f);
	return &color;
}

Color* Color::get_GrayColor()
{
	static Color color(0.5f, 0.5f, 0.5f);
	return &color;
}

Color* Color::get_DarkGrayColor()
{
	static Color color(0.25f, 0.25f, 0.25f);
	return &color;
}

Color* Color::get_LightGrayColor()
{
	static Color color(0.75f, 0.75f, 0.75f);
	return &color;
}

Color* Color::get_RedColor()
{
	static Color color(1.0f, 0, 0);
	return &color;
}

Color* Color::get_GreenColor()
{
	static Color color(0, 1.0f, 0);
	return &color;
}

Color* Color::get_BlueColor()
{
	static Color color(0, 0, 1.0f);
	return &color;
}

Color* Color::get_CyanColor()
{
	static Color color(0, 1.0f, 1.0f);
	return &color;
}

Color* Color::get_MagentaColor()
{
	static Color color(1.0f, 0, 1.0f);
	return &color;
}

Color* Color::get_YellowColor()
{
	static Color color(1.0f, 1.0f, 0);
	return &color;
}

Color::Color() : DependencyObject(get_Class())
{
}

Color::Color(float r, float g, float b) : DependencyObject(get_Class())
{
	set_Red(r);
	set_Green(g);
	set_Blue(b);
}

Color::Color(ColorF color) : DependencyObject(get_Class())
{
	set_Red(color.r);
	set_Green(color.g);
	set_Blue(color.b);
}

}	// Gui
}	// System
