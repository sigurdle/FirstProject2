#include "stdafx.h"
#include "LXUI2.h"
#include "ListBox.h"
#include "ListBoxItem.h"

namespace System
{
namespace UI
{

//void ApplyStyle(Style* style, FrameworkElement* element);
//Object* CreateObjectFromElement(Type* pType, Object* parentObject, XmlData::Node* node, Type** pReturnType);

__live_object_ptr<Style> ListBoxStyle;

ListBox::ListBox()
{
	if (ListBoxStyle == NULL)
	{
		XmlData::Document* document = new XmlData::Document;

		StringW* filename = MakeFilePath(_Module, L"../../../ListBoxStyle.lxui");
		document->load(filename);

		Type* returnType;
		ListBoxStyle = dynamic_cast<Style*>(CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType));
	}

	set_Style(ListBoxStyle);

	/*
	ApplyStyle(get_Style(), this);

	InitScript();
	*/
}

void ListBox::AddItem(Object* item)
{
	ListBoxItem* listboxitem = dynamic_cast<ListBoxItem*>(item);
	if (listboxitem == NULL)
	{
		listboxitem = new ListBoxItem;
		listboxitem->set_Content(item);
	}

//	m_owner->m_itemContainerGenerator->m_containers.push_back(listboxitem);

	m_itemsPresenter->m_panel->AddChild(listboxitem);
}

}	// UI
}
