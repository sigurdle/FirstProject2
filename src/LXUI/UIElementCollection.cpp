#include "stdafx.h"
#include "LXUI.h"

namespace System
{
namespace UI
{

UIElementCollection::UIElementCollection()
{
}

void UIElementCollection::Add(UIElement* element)
{
	m_items.push_back(element);

//	element->SetRParent(m_owner);
	m_owner->AddVisualChild(element);
	m_owner->InvalidateMeasure();
}

bool UIElementCollection::Contains(UIElement* element)
{
	for (unsigned int i = 0; i < m_items.size(); i++)
	{
		if (m_items[i] == element)
			return true;
	}

	return false;
}

int UIElementCollection::IndexOf(UIElement* element)
{
	for (int i = 0; i < m_items.size(); i++)
	{
		if (m_items[i] == element)
			return i;
	}

	return -1;
}

}	// UI
}
