#include "stdafx.h"
#include "LXUI2.h"
#include "PointCollection.h"

namespace System
{
namespace UI
{

PointCollection::PointCollection()
{
//	m_pListener = NULL;
}

const Type_Info& PointCollection::GetItemType() const
{
	return typeid(Point);
}

unsigned int PointCollection::GetCount()
{
	return m_items.size();
}

void PointCollection::Clear()
{
	// TODO, check freezed status
	m_items.clear();
	Changed();
}

Point PointCollection::get_Item(unsigned int index)
{
	if (index < m_items.size())
		return m_items[index];
	else
		throw new ArgumentOutOfRangeException();
}

void PointCollection::set_Item(unsigned int index, Point element)
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

/*
Point& PointCollection::Item(unsigned int index)
{
	throw exception("Not supported");
//	return m_items[index];
}
*/

void PointCollection::Add(Point element)
{
	m_items.push_back(element);
	Changed();
}

void PointCollection::AddObject(Object* element)
{
	Point* pPoint = dynamic_cast<Point*>(element);
	if (pPoint == NULL) throw new Exception(WSTR("Wrong type"));

	Add(*pPoint);
}

/*
const Type_Info& PointCollection::GetItemType() const
{
	return typeid(Point);
}

unsigned int PointCollection::GetCount()
{
	return m_items.GetSize();
}

Object* PointCollection::GetItem(unsigned int index)
{
	if (index < m_items.GetSize())
	{
		return m_items[index];
	}
	else
	{
		THROW(-1);
		return NULL;
	}
}

Point* PointCollection::Item(unsigned int index) const
{
	if (index < m_items.GetSize())
	{
		return m_items[index];
	}
	else
	{
		THROW(-1);
		return NULL;
	}
}
*/

/*
void PointCollection::Add(Point* point)
{
	if (point != NULL)
	{
		m_items.Add(point);
	}
	else
		THROW(-1);
}

void PointCollection::AddChild(Object* child)
{
	Point* point = dynamic_cast<Point*>(child);
	if (point != NULL)
	{
		m_items.Add(point);
	}
	else
		THROW(-1);
}

void PointCollection::AddText(StringW* text)
{
	THROW(-1);
}
*/

}	// UI
}
