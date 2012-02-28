#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

Trigger::Trigger()
{
}

DependencyProperty* Trigger::get_Property()
{
	return m_property;
}

void Trigger::set_Property(DependencyProperty* property)
{
	m_property = property;
}

Object* Trigger::get_Value()
{
	return m_value;
}

void Trigger::set_Value(Object* value)
{
	m_value = value;
}

Setters* Trigger::get_Setters()
{
	return m_setters;
}

void Trigger::set_Setters(Setters* setters)
{
	m_setters = setters;
}

}
}
