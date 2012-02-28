#include "stdafx.h"
#include "LXUI2.h"
#include "ListBoxItem.h"

namespace System
{
namespace UI
{

DependencyProperty* ListBoxItem::s_IsSelectedProperty = RegisterProperty(WSTR("IsSelected"), typeid(bool), typeid(ListBoxItem), BoolObject::get_False(), PropertyMetaData(None));

//void ApplyStyle(Style* style, FrameworkElement* element);
//Object* CreateObjectFromElement(Type* pType, Object* parentObject, XmlData::Node* node, Type** pReturnType);

__live_object_ptr<Style> ListBoxItemStyle;

ListBoxItem::ListBoxItem()
{
	if (ListBoxItemStyle == NULL)
	{
		XmlData::Document* document = new XmlData::Document;

		StringW* filename = MakeFilePath(_Module, L"../../../ListBoxItemStyle.lxui");
		document->load(filename);

		Type* returnType;
		ListBoxItemStyle = dynamic_cast<Style*>(CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType));
	}

	set_Style(ListBoxItemStyle);

	ApplyStyle(get_Style(), this);

	InitScript();
}

bool ListBoxItem::get_IsSelected()
{
	return static_cast<BoolObject*>(GetValue(get_IsSelectedProperty()))->GetValue();
}

void ListBoxItem::set_IsSelected(bool selected)
{
	SetValue(get_IsSelectedProperty(), BoolObject::GetObject(selected));
}

}	// UI
}
