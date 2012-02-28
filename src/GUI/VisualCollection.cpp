#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

VisualCollection::VisualCollection()
{
}

VisualCollection::VisualCollection(Object* owner) : m_owner(owner)
{
}

const Type_Info& VisualCollection::GetItemType() const
{
	return typeid(Visual);
}

size_t VisualCollection::GetCount()
{
	return m_items.size();
}

void VisualCollection::Clear()
{
	m_items.clear();
}

void VisualCollection::AddObject(Object* element)
{
	Visual* item = dynamic_cast<Visual*>(element);
	if (item == NULL)
	{
		ASSERT(0);
		raise(ArgumentException(WSTR("Not a Visual")));
	}

	Add(item);
}

Object* VisualCollection::get_ObjectItem(size_t index)
{
	ASSERT(0);
	/*
	if (index >= m_items.size())
	{
		raise(ArgumentOutOfRangeException());
	}
	return m_items[index];
	*/
	return NULL;
}

void VisualCollection::Insert(UIElement* before, UIElement* child)
{
	if (child == nullptr)
	{
		raise(ArgumentNullException());
	}

	UIElement* elementOwner = dynamic_cast<UIElement*>(m_owner);

	if (before == nullptr)	// at end
	{
		m_items.push_back(child);
		child->set_ChildPosition(m_items.size());

		child->set_PreviousSibling(elementOwner->get_LastChild());
		if (elementOwner) elementOwner->set_LastChild(child);
	}
	else
	{
		ASSERT(before->get_Parent() == elementOwner);

		before->set_PreviousSibling(child);
		child->set_NextSibling(before);

		Visual* prev = before->get_PreviousSibling();

		if (prev)
			prev->set_NextSibling(child);
		else
			elementOwner->set_FirstChild(child);

		int position = before->get_ChildPosition();

		m_items.insert(m_items.begin() + position, child);

		for (; position < m_items.size(); ++position)
		{
			m_items[position]->set_ChildPosition(position);
		}
	}

	elementOwner->OnAddChild(this, child);
}

void VisualCollection::Add(Visual* element)
{
	if (element == nullptr)
	{
		raise(ArgumentNullException());
	}

	size_t position = m_items.size();
	UIElement* elementOwner = dynamic_cast<UIElement*>(m_owner);
	element->set_ChildPosition(position);
	m_items.push_back(element);

	if (elementOwner)
	{
		Visual* lastChild = elementOwner->get_LastChild();
		if (lastChild) lastChild->set_NextSibling(element);
		element->set_PreviousSibling(lastChild);

		elementOwner->OnAddChild(this, element);
	}
}

String VisualCollection::ToString()
{
	for (auto it = m_items.begin(); it != m_items.end(); ++it)
	{
		Visual* item = *it;
	}
	return "TODO";
}

}	// Gui
}	// System
