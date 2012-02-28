#include "stdafx.h"
#include "LXUI2.h"
#include "SolidColorBrush.h"

namespace System
{
namespace UI
{
namespace Shapes
{

/*
class FillPropertyDefaultValue
{
};
*/

DependencyProperty* Shape::s_FillProperty = RegisterAttached(WSTR("Fill"), typeid(Brush), typeid(Shape), (Brush*)1/* set later new SolidColorBrush(new Color(0,0,0))*/, PropertyMetaData(ChildInherits | AffectsRender));
DependencyProperty* Shape::s_StrokeProperty = RegisterAttached(WSTR("Stroke"), typeid(Brush), typeid(Shape), NULL, PropertyMetaData(ChildInherits | AffectsRender));
DependencyProperty* Shape::s_StrokeThicknessProperty = RegisterAttached(WSTR("StrokeThickness"), typeid(double), typeid(Shape), DoubleObject::GetObject(1), PropertyMetaData(ChildInherits | AffectsRender));

Shape::Shape()
{
	ASSERT(s_FillProperty->m_defaultValue != (Brush*)1);
#if 0
	{
		s_FillProperty->m_defaultValue = new SolidColorBrush(new Color(0,0,0));
	//	printf("FillProperty->m_defaultValue was 1, new is 0x%x\n", s_FillProperty->m_defaultValue);
	}
	else
		;//printf("FillProperty->m_defaultValue: 0x%x\n", s_FillProperty->m_defaultValue);
#endif
}

Shape::~Shape()
{
}

double Shape::get_StrokeThickness()
{
	return static_cast<DoubleObject*>(GetValue(get_StrokeThicknessProperty()))->GetValue();
}

void Shape::set_StrokeThickness(double newVal)
{
	SetValue(get_StrokeThicknessProperty(), DoubleObject::GetObject(newVal));
}

Brush* Shape::get_Stroke()
{
	return static_cast<Brush*>(GetValue(get_StrokeProperty()));
}

void Shape::set_Stroke(Brush* newVal)
{
	SetValue(get_StrokeProperty(), newVal);
}

Brush* Shape::get_Fill()
{
	return static_cast<Brush*>(GetValue(get_FillProperty()));
}

void Shape::set_Fill(Brush* newVal)
{
	SetValue(get_FillProperty(), newVal);
}

}	// Shapes
}	// UI
}
