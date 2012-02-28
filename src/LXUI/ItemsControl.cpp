#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

namespace Data
{

CollectionView::CollectionView()
{
}

CollectionView::CollectionView(IObjectCollection* sourceCollection)
{
	m_sourceCollection = sourceCollection;
}

unsigned int CollectionView::GetCount()
{
	return m_items.size();
}

Object* CollectionView::GetItemAt(unsigned int index)
{
	return m_items[index];
}

bool CollectionView::Contains(Object* object)
{
	ASSERT(0);
	return false;
}

int CollectionView::IndexOf(Object* item)
{
	ASSERT(0);
	return -1;
}

bool CollectionView::PassesFilter(Object* object)
{
	// TODO
	return true;
}

IObjectCollection* CollectionView::get_SourceCollection()
{
	return m_sourceCollection;
}

}	// Data

ItemCollection::ItemCollection()
{
	m_sourceCollection = new Vector<Object*>;
}

void ItemCollection::Add(Object* item)
{
	m_sourceCollection->AddObject(item);

	// TODO, improve
	m_owner->SetValue(m_owner->get_HasItemsProperty(), BoolObject::get_True());
	m_owner->AddItem(item);
}

DependencyObject* ItemContainerGenerator::ContainerFromIndex(unsigned int index)
{
	return m_panel->get_Children()->get_Item(index);
//	return m_containers[index];
}

DependencyObject* ItemContainerGenerator::ContainerFromItem(Object* object)
{
	ASSERT(0);
	return NULL;
}

Object* ItemContainerGenerator::ItemFromContainer(DependencyObject* object)
{
	return dynamic_cast<ContentControl*>(object)->get_Content();
}

DependencyProperty* ItemsControl::s_ItemsPanelProperty = RegisterProperty(WSTR("ItemsPanel"), typeid(ItemsPanelTemplate), typeid(ItemsControl), NULL, PropertyMetaData(None));
DependencyProperty* ItemsControl::s_HasItemsProperty = RegisterProperty(WSTR("HasItems"), typeid(bool), typeid(ItemsControl), BoolObject::get_False(), PropertyMetaData(None));

ItemsControl::ItemsControl()
{
	m_items = new ItemCollection;
	m_items->m_owner = this;
}

bool ItemsControl::get_HasItems()
{
	return static_cast<BoolObject*>(GetValue(get_HasItemsProperty()))->GetValue();
}

void ItemsControl::OnApplyTemplate()
{
	Control::OnApplyTemplate();

	m_itemsPresenter = dynamic_cast<ItemsPresenter*>(get_VisualTree()->FindByType((ClassType*)typeid(ItemsPresenter).GetType()));

//	if (m_itemsPresenter == NULL)
//	m_itemsPresenter = dynamic_cast<ItemsPresenter*>(get_VisualTree()->FindByType((ClassType*)typeid(ItemsPresenter).GetType()));

	if (m_itemsPresenter)
	{
		ItemsPanelTemplate* itemsPanelTemplate = get_ItemsPanel();

		ASSERT(m_objectpropertymap.size() == 0);
		Type* pRealType;
		Object* obj = itemsPanelTemplate->get_VisualTree()->Create4(NULL, &pRealType, this/*???*/, m_objectpropertymap);
		m_itemsPresenter->m_panel = dynamic_cast<Panel*>(obj);

		m_itemContainerGenerator = new ItemContainerGenerator;	// hm..
		m_itemContainerGenerator->m_panel = m_itemsPresenter->m_panel;

		m_itemsPresenter->set_VisualTree(m_itemsPresenter->m_panel);
	}
}

ItemCollection* ItemsControl::get_Items()
{
	return m_items;
}

ItemsPanelTemplate* ItemsControl::get_ItemsPanel()
{
	return static_cast<ItemsPanelTemplate*>(GetValue(get_ItemsPanelProperty()));
}

void ItemsControl::set_ItemsPanel(ItemsPanelTemplate* itemsPanel)
{
	SetValue(get_ItemsPanelProperty(), itemsPanel);
}

// Default implementation, override if this isn't what you want
void ItemsControl::AddItem(Object* item)
{
	ContentControl* contentItem = dynamic_cast<ContentControl*>(item);
	if (contentItem == NULL)
	{
		contentItem = new ContentControl;
		contentItem->set_Content(item);
	}

//	m_owner->m_itemContainerGenerator->m_containers.push_back(listboxitem);

	if (m_itemsPresenter)
	{
		m_itemsPresenter->m_panel->AddChild(contentItem);
	}
}

}	// UI
}
