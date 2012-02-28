#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

Decorator::Decorator()
{
	m_Child = NULL;
}

UIElement* Decorator::get_Child()
{
	return m_Child;
}

void Decorator::set_Child(UIElement* child)
{
	if (child != m_Child)
	{
		if (m_Child)
		{
			RemoveVisualChild(m_Child);
		}

		m_Child = child;

		if (m_Child)
		{
			AddVisualChild(m_Child);
		}
	}
}

unsigned int Decorator::get_VisualChildrenCount()
{
	return m_Child? 1: 0;
}

Visual* Decorator::GetVisualChild(unsigned int index)
{
	if (m_Child == NULL || index != 0)
	{
		throw std::exception("Index out of range");
	}

	return m_Child;
}

/*
void Decorator::AddChild(System::Object* obj)
{
}

void Decorator::AddText(System::StringW* str)
{
}

*/

}
}
