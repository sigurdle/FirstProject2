#include "stdafx.h"
#include "LSVG2.h"
#include "SVGLengthList.h"

namespace System
{
int GetCommaOrSpaceSepLengthArray(StringIn str, vector<double>& values);

namespace Web
{

SVGLengthList::SVGLengthList()
{
	m_p = new SVGLengthListData;
//		m_bLockUpdate = 0;
//		m_nChanges = 0;
	//m_pListener = NULL;
}

SVGLengthList::SVGLengthList(SVGLengthListData* p) : m_p(p)
{
}

SVGLengthList::~SVGLengthList()
{
	RemoveAll();
}

unsigned int SVGLengthList::get_numberOfItems() const
{
	return m_p->m_items.GetSize();
}

void SVGLengthList::clear()
{
	RemoveAll();
}

SVGLength* SVGLengthList::initialize(SVGLength* newItem)
{
	if (newItem == NULL) raise(ArgumentNullException());

	RemoveAll();

	m_p->m_items.Add(newItem);

	return newItem;
}

SVGLength* SVGLengthList::getItem(unsigned int index) const
{
	if (index < m_p->m_items.GetSize())
	{
		return m_p->m_items[index];
	}
	else
		return NULL;
}

SVGLength* SVGLengthList::appendItem(SVGLength* newItem)
{
	if (newItem == NULL) raise(ArgumentNullException());

	if (newItem->m_owner)
	{
	// This should also clear the listener if successful
		if (!newItem->m_owner->OnRemoveItem(newItem))
		{
			raise(Exception("Could not append point, try to make a copy of it first"));
		}
		ASSERT(newItem->m_owner == NULL);
	}

	m_p->m_items.push_back(newItem);
	newItem->m_owner = this;

	if (m_pListener)
		m_pListener->OnChanged(this);

	return newItem;
}

SVGLength* SVGLengthList::removeItem(unsigned int index)
{
	ASSERT(0);
	return NULL;
}

SVGLength* SVGLengthList::replaceItem(SVGLength* newItem, unsigned int index)
{
	ASSERT(0);
	return NULL;
}

SVGLength* SVGLengthList::insertItemBefore(SVGLength* newItem, unsigned int index)
{
	ASSERT(0);
	return NULL;
}

//////////////////////////////////////////////////////////////////////

void SVGLengthList::RemoveAll()
{
	for (uint i = 0; i < m_p->m_items.size(); ++i)
	{
		m_p->m_items[i]->m_owner = NULL;
//		m_items[i]->Release();
	}
	m_p->m_items.RemoveAll();
}

//////////////////////////////////////////////////////////////////////

//virtual
void SVGLengthList::OnChanged(SVGLength* pLength)
{
	if (m_pListener)
	{
		m_pListener->OnChanged(this);
	}
}

bool SVGLengthList::OnRemoveItem(SVGLength* pLength)
{
	ASSERT(0);
	return false;
}

//////////////////////////////////////////////////////////////////////

String SVGLengthList::getStringValue()
{
	IO::StringWriter str;

	for (size_t i = 0; i < m_p->m_items.GetSize(); ++i)
	{
		if (i > 0) str << L" ";
		String s = m_p->m_items[i]->get_valueAsString();
		str << s;
	}

	return str.str();
}

//int GetCommaOrSpaceSepStringArray(BSTR str, CArray<_bstr_t,_bstr_t>& values);

void SVGLengthList::setStringValue(StringIn str)
{
	RemoveAll();

	vector<System::String> values;
	GetCommaOrSpaceSepStringArray(str, values);

	for (uint i = 0; i < values.GetSize(); ++i)
	{
		SVGLengthMutable* pSVGLength = new SVGLengthMutable;
		pSVGLength->set_valueAsString(values[i]);
		pSVGLength->m_owner = this;

		m_p->m_items.Add(pSVGLength);
	}
}

void SVGLengthList::InterpolateValue(const SVGLengthList& a, const SVGLengthList& b, double t)
{
	ASSERT(0);
}

String GetAsString(SVGLengthList* lengthList)
{
	return lengthList->getStringValue();
}

SVGLengthListValueHandler SVGLengthListValueHandler::s_svgLengthListValueHandler;

Object* SVGLengthListValueHandler::Create() const
{
	return new SVGLengthList;
}

void SVGLengthListValueHandler::ParseString(Object* value, StringIn str) const
{
	// ParseString ??

	static_cast<SVGLengthList*>(value)->setStringValue(str);
}

void SVGLengthListValueHandler::InterpolateValue(Object* _dest, Object* _a, Object* _b, double t)
{
	SVGLengthList* dest = static_cast<SVGLengthList*>(_dest);
	SVGLengthList* a = static_cast<SVGLengthList*>(_a);
	SVGLengthList* b = static_cast<SVGLengthList*>(_b);

	ASSERT(0);
	//dest->m_p->m_value = a->m_p->m_value + (b->m_p->m_value - a->m_p->m_value)*t;
}

}	// Web
}	// System
