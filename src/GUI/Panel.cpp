#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(VisualCollection*, Panel, Children, nullptr)

DependencyClass* Panel::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_ChildrenProperty(),
	};

	return &depclass;
}

Panel::Panel(DependencyClass* depClass) : UIElement(depClass)
{
}

/*
void Panel::Render(ManagedRenderContext renderContext)
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
*/

/*
void Panel::RenderRetained(ManagedRetainedRenderContext renderContext)
{
	for (size_t i = 0; i < m_children.size(); ++i)
	{
		Visual* child = m_children[i];

		child->RenderRetained(renderContext);
	}
}
*/

void Panel::AddChild(Visual* element)
{
	if (get_Children() == nullptr)
	{
		set_Children(new VisualCollection(this));
	}

	get_Children()->Add(element);
}

/*
void Panel::Render(ManagedRenderContext renderContext)
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
*/

size_t Panel::GetChildrenCount()
{
	VisualCollection* children = get_Children();
	if (children)
	{
		return children->m_items.size();
	}

	return 0;
}

Visual* Panel::GetChild(size_t index)
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
