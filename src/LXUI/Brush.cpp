#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

DependencyProperty* Brush::s_OpacityProperty = RegisterProperty(WSTR("Opacity"), typeid(double), typeid(Brush), DoubleObject::GetObject(1.0), PropertyMetaData(None));

Brush::Brush()
{
}

double Brush::get_Opacity()
{
	return static_cast<DoubleObject*>(GetValue(get_OpacityProperty()))->GetValue();
}

void Brush::set_Opacity(double newVal)
{
	SetValue(get_OpacityProperty(), DoubleObject::GetObject(newVal));
}

/*
// virtual
DependencyObject* Brush::GetDependencyParent()
{
	return NULL;
}
*/

	/*
DependencyObject* Brush::GetDependencyParent()
{
	return NULL;
}
*/

}	// UI
}
