#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

Setter::Setter()
{
	m_targetName = NULL;
	m_property = NULL;
	m_value = NULL;
//	m_computedValue = NULL;
}

StringW* Setter::get_TargetName()
{
	return m_targetName;
}

void Setter::set_TargetName(StringW* targetName)
{
	m_targetName = targetName;
}

DependencyProperty* Setter::get_Property()
{
	return m_property;
}

void Setter::set_Property(DependencyProperty* property)
{
	m_property = property;
}

Object* Setter::get_Value()
{
	return m_value;
}

void Setter::set_Value(Object* value)
{
	m_value = value;
}

/*
void Setter::AddChild(System::Object* child)
{
	if (m_value)
		throw exception("child already added");

	m_value = child;
}

void Setter::AddText(System::StringW* text)
{
	throw exception("Text not allowed as child");
}
*/

Setters::Setters()
{
}

#if 0
void Setters::Add(Setter* setter)
{
	int depPropertyIndex = setter->get_Property()->gindex;
	ASSERT(depPropertyIndex != -1);

//	setter->m_depPropertyIndex = depPropertyIndex;

	m_items.push_back(setter);
#if 0
	m_depproperties[depPropertyIndex] = setter;
#endif
}
#endif

/*
void Setters::Add(System::Object* child)
{
	Setter* setter = dynamic_cast<Setter*>(child);
	if (setter == NULL) throw exception("child is not a Setter");

	Add(setter);
}
*/

/*
void Setters::AddText(System::StringW* text)
{
	throw exception("Text not allowed as child");
}
*/

}	// UI
}
