#include "stdafx.h"
#include "LXUI2.h"
#include "ListBoxItem.h"
#include "ComboBox.h"

namespace System
{
namespace UI
{

__live_object_ptr<Style> ComboBoxItemStyle;

ComboBoxItem::ComboBoxItem()
{
	if (ComboBoxItemStyle == NULL)
	{
		ComboBoxItemStyle = dynamic_cast<Style*>(FindResource(GetType()));
	}

	set_Style(ComboBoxItemStyle);
}

//////////////////////////////////////////////

__live_object_ptr<Style> ComboBoxStyle;

DependencyProperty* ComboBox::s_IsDropDownOpenProperty = RegisterProperty(WSTR("IsDropDownOpen"), typeid(bool), typeid(ComboBox), BoolObject::get_False());
DependencyProperty* ComboBox::s_IsReadOnlyProperty = NULL;

ComboBox::ComboBox()
{
	if (ComboBoxStyle == NULL)
	{
		ComboBoxStyle = dynamic_cast<Style*>(FindResource(GetType()));
	}

	set_Style(ComboBoxStyle);
}

bool ComboBox::get_IsDropDownOpen()
{
	return static_cast<BoolObject*>(GetValue(get_IsDropDownOpenProperty()))->GetValue();
}

void ComboBox::set_IsDropDownOpen(bool isDropDownOpen)
{
	SetValue(get_IsDropDownOpenProperty(), BoolObject::GetObject(isDropDownOpen));
}

bool ComboBox::get_IsReadOnly()
{
	return static_cast<BoolObject*>(GetValue(get_IsReadOnlyProperty()))->GetValue();
}

void ComboBox::set_IsReadOnly(bool isReadOnly)
{
	SetValue(get_IsReadOnlyProperty(), BoolObject::GetObject(isReadOnly));
}

}	// UI
}
