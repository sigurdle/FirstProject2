#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

ValueBinding<float> Mouse::s_ScreenXBinding;
ValueBinding<float> Mouse::s_ScreenYBinding;
ValueBinding<bool> Mouse::s_LeftButtonDownBinding;
ValueBinding<bool> Mouse::s_MiddleButtonDownBinding;
ValueBinding<bool> Mouse::s_RightButtonDownBinding;

// static
Vector2_F* Mouse::get_Position()
{
	static Vector2_F v;
	/*
	static bool b = false;
	if (!b)
	{
		b = true;
		v.m_value->AddNotify(&v);
	}*/
	return &v;
}

Expressive::typed_expression<float> _Mouse::screenposX()
{
	return new BindingExpression(&Mouse::s_ScreenXBinding);
}

Expressive::typed_expression<float> _Mouse::screenposY()
{
	return new BindingExpression(&Mouse::s_ScreenYBinding);
}

Expressive::typed_expression<bool> _Mouse::leftButtonDown()
{
	return new BindingExpression(&Mouse::s_LeftButtonDownBinding);
}

Expressive::typed_expression<bool> _Mouse::middleButtonDown()
{
	return new BindingExpression(&Mouse::s_MiddleButtonDownBinding);
}

Expressive::typed_expression<bool> _Mouse::rightButtonDown()
{
	return new BindingExpression(&Mouse::s_RightButtonDownBinding);
}

///

ValueBinding<float> Stylus::s_PressureBinding;

Expressive::typed_expression<float> _Stylus::Pressure()
{
	return new BindingExpression(&Stylus::s_PressureBinding);
}

}	// Gui
}	// System
