#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{
namespace Media3D
{

Point3DCollection::Point3DCollection()
{
}

const Type_Info& Point3DCollection::GetItemType() const
{
	return typeid(Point3D);
}

unsigned int Point3DCollection::GetCount()
{
	return m_items.size();
}

void Point3DCollection::Clear()
{
	// TODO, check freezed status
	m_items.clear();
	Changed();
}

Point3D Point3DCollection::get_Item(unsigned int index)
{
	if (index < m_items.size())
		return m_items[index];
	else
		throw new ArgumentOutOfRangeException();
}

void Point3DCollection::set_Item(unsigned int index, Point3D element)
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

void Point3DCollection::Add(Point3D element)
{
	m_items.push_back(element);
	Changed();
}

void Point3DCollection::AddObject(Object* element)
{
	Point3D* pPoint = dynamic_cast<Point3D*>(element);
	if (pPoint == NULL) throw std::exception("Wrong type");

	Add(*pPoint);
}

}	// Media3D
}	// UI
}
