#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

Int32Collection::Int32Collection()
{
}

const Type_Info& Int32Collection::GetItemType() const
{
	return typeid(int);
}

unsigned int Int32Collection::GetCount()
{
	return m_items.size();
}

void Int32Collection::Clear()
{
	// TODO, check freezed status
	m_items.clear();
	Changed();
}

void Int32Collection::Add(int32 element)
{
	// TODO, check freezed status
	m_items.push_back(element);
	Changed();
}

void Int32Collection::AddObject(Object* element)
{
	Add(unbox_cast<int32>(element));
}

int32 Int32Collection::get_Item(unsigned int index)
{
	if (index < m_items.size())
		return m_items[index];
	else
		throw new ArgumentOutOfRangeException();
}

void Int32Collection::set_Item(unsigned int index, int32 element)
{
	if (index < m_items.size())
	{
	// TODO, check freezed status
		m_items[index] = element;
		Changed();
	}
	else
		throw new ArgumentOutOfRangeException();
}

}	// UI
}
