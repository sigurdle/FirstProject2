#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

DependencyProperty* HeaderedItemsControl::s_HeaderProperty = RegisterProperty(WSTR("Header"), typeid(Object), typeid(HeaderedItemsControl), NULL, PropertyMetaData(None));
DependencyProperty* HeaderedItemsControl::s_HeaderTemplateProperty = RegisterProperty(WSTR("HeaderTemplate"), typeid(DataTemplate), typeid(HeaderedItemsControl), NULL, PropertyMetaData(None));
DependencyProperty* HeaderedItemsControl::s_HasHeaderProperty = RegisterProperty(WSTR("HasHeader"), typeid(bool), typeid(HeaderedItemsControl), BoolObject::get_False(), PropertyMetaData(None));

HeaderedItemsControl::HeaderedItemsControl()
{
}

Object* HeaderedItemsControl::get_Header()
{
	return GetValue(get_HeaderProperty());
}

void HeaderedItemsControl::set_Header(Object* header)
{
	SetValue(get_HeaderProperty(), header);
}

DataTemplate* HeaderedItemsControl::get_HeaderTemplate()
{
	return static_cast<DataTemplate*>(GetValue(get_HeaderTemplateProperty()));
}

void HeaderedItemsControl::set_HeaderTemplate(DataTemplate* headerTemplate)
{
	SetValue(get_HeaderTemplateProperty(), headerTemplate);
}

}	// UI
}
