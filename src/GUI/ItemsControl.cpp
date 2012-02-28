#include "stdafx.h"
#include "GUI2.h"

#include <map>

namespace System
{

enum ListSortDirection
{
	ListSortDirection_Ascending,
	ListSortDirection_Descending,
};

class SortDescription : public Object
{
public:
	CTOR SortDescription(StringIn propertyName, ListSortDirection direction) :
	 m_propertyName(propertyName),
		m_direction(direction)
	{
	}

	String m_propertyName;
	ListSortDirection m_direction;
};

namespace Gui
{

/*
class CollectionView : public Object
{
public:

	CTOR CollectionView(IEnumerable*);

	filter_t get_Filter();
	void set_Filter(filter_t);

	IEnumerable* get_SourceCollection();

	typedef bool (*filter_t)(Object*);

	List<SortDescription*> m_sortDescriptions;
};

interface IItemsProvider
{

};

class ItemContainerGenerator : public Object
{
public:
	std::map<Object*, DependencyObject*> m_objectToContainer;
	std::map<DependencyObject*, int> m_containerToIndex;

	Object* ItemFromContainer(DependencyObject* container);
	int IndexFromContainer(DependencyObject* container);

	DependencyObject* ContainerFromIndex(int index);

	vector<DependencyObject*> m_items;
};
*/

/*
Object* ItemContainerGenerator::ItemFromContainer(DependencyObject* container)
{
	return container->GetUserData();
}

DependencyObject* ItemContainerGenerator::ContainerFromIndex(int index)
{
	return m_items[index];
}

int ItemContainerGenerator::IndexFromContainer(DependencyObject* container)
{
	auto it = m_containerToIndex.find(container);
	if (it != m_containerToIndex.end())
		return *it;
	else
		raise(Exception());
}

//ItemsProvider::ItemsProvider(ClassType*

class Properto : public IEnumerable<Property*>
{
public:

};
*/

/*

var lb = new ListBox();
lb.Items = ListOf(Tools);

ItemsTemplate


*/

/*
IEnumerable<Property*>* _properties(ClassType* pClass)
{
	Dispatch* pDispatch = GetDispatch(pClass);

	for (auto it = pDispatch->GetProperties().begin(); it != pDispatch->GetProperties().end(); ++it)
	{
		Property* pProperty = it->second;

		if (pProperty->get_GetMethod() && pProperty->get_GetMethod()->get_IsStatic())
		{
			Variant v = GetPropertyValue(pProperty);

			Std::get_Out() << pProperty->get_PropertyName() << '=';

			if (v.IsString())
			{
				Std::get_Out() << '"' << escape(v.ToString()) << '"' << endl;
			}
			else
			{
				Std::get_Out() << v << endl;
			}
		}
	}
}


IMP_DEPENDENCY_PROPERTY(IItemsProvider*, ItemsControl, Source, NULL)
*/

IMP_DEPENDENCY_PROPERTY(int, ItemsControl, SelectedIndex, -1)
IMP_DEPENDENCY_PROPERTY(Object*, ItemsControl, SelectedItem, nullptr)

DependencyClass* ItemsControl::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_SelectedIndexProperty(),
		get_SelectedItemProperty(),
	};

	return &depclass;
}

ItemsControl::ItemsControl(DependencyClass* depClass) : Control(depClass)
{
}

void ItemsControl::AddItem(StringIn str)
{
	AddItem(String(str).m_stringObject);
}

void ItemsControl::AddItem(Object* item)
{
	UIElement* element = CreateObjectShadowTree(item);

	OnAddElement(element);

	ASSERT(0);
	//LayoutChildren();
}

}	// Gui
}	// System
