#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(VisualCollection*, GroupVisual, Children, nullptr)

DependencyClass* GroupVisual::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_ChildrenProperty(),
	};

	return &depclass;
}

DependencyClass* GroupVisual::pClass(get_Class());

GroupVisual::GroupVisual() : UIElement(get_Class())
{
}

geometry GroupVisual::GetHitGeometry()
{
	//ASSERT(0);
	return nullptr;
}

void GroupVisual::AddChild(Visual* element)
{
	if (get_Children() == nullptr)
	{
		set_Children(new VisualCollection(this));
	}

	get_Children()->Add(element);
}

void GroupVisual::Render(ManagedRenderContext renderContext)
{
	VisualCollection* children = get_Children();
	if (children)
	{
		for (auto it = children->m_items.begin(); it != children->m_items.end(); ++it)
		{
			Visual* child = *it;
			child->Render_(renderContext);
		}
	}
}

size_t GroupVisual::GetChildrenCount()
{
	VisualCollection* children = get_Children();
	if (children)
	{
		return children->m_items.size();
	}

	return 0;
}

Visual* GroupVisual::GetChild(size_t index)
{
	VisualCollection* children = get_Children();
	if (children == nullptr)
	{
		raise(ArgumentOutOfRangeException());
	}

	if (index >= children->m_items.size())
	{
		raise(ArgumentOutOfRangeException());
	}

	return children->m_items[index];
}

}	// Gui
}	// System
