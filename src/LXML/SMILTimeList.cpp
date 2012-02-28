#include "stdafx.h"
#include "LXML2.h"
#include "SMILTimeList.h"

#include "SMILTime.h"

namespace System
{
namespace Web
{

SMILTimeList::~SMILTimeList()
{
	ASSERT(m_pListener == NULL);
	RemoveAll();
}

void SMILTimeList::RemoveAll()
{
	for (int i = 0; i < m_items.GetSize(); i++)
	{
		m_items[i]->m_pListener = NULL;
	//	m_items[i]->Release();
	}
	m_items.RemoveAll();
}

unsigned int SMILTimeList::get_length() const
{
	return m_items.size();
}

unsigned int SMILTimeList::get_numberOfItems() const
{
	return m_items.size();
}

SMILTime* SMILTimeList::item(unsigned int index) const
{
	if (index < m_items.GetSize())
	{
		return m_items[index];
	}
	else
		return NULL;
}

void SMILTimeList::clear()
{
	VERIFY(0);
}

SMILTime* SMILTimeList::initialize(/*[in]*/ SMILTime* newItem)
{
	VERIFY(0);
	return NULL;
}

SMILTime* SMILTimeList::insertItemBefore(/*[in]*/ SMILTime* newItem, /*[in]*/ unsigned int index)
{
	VERIFY(0);
	return NULL;
}

SMILTime* SMILTimeList::replaceItem(/*[in]*/ SMILTime* newItem, /*[in]*/ unsigned int index)
{
	VERIFY(0);
	return NULL;
}

SMILTime* SMILTimeList::removeItem(/*[in]*/ unsigned int index)
{
	ASSERT(0);
#if 0
	if (index >= 0 && index < m_items.GetSize())
	{
		if (pVal)
		{
			*pVal = m_items[index];
			(*pVal)->AddRef();
		}

		m_items[index]->m_pListener = NULL;
	//	m_items[index]->Release();
		m_items.RemoveAt(index);

		if (m_pListener)
			m_pListener->OnChanged(this);
	}

#endif
	return NULL;
}

SMILTime* SMILTimeList::appendItem(SMILTime* newItem)
{
	if (newItem == NULL) THROW(-1);

// TODO, check if already added to some list

	m_items.Add(newItem);
	newItem->m_pListener = this;

	if (m_pListener)
		m_pListener->OnChanged(this);

	return newItem;
}

#if 0
void SMILTimeList::Sort()
{
// Sort
	int i;
	
	for (i = 0; i < m_items.GetSize(); i++)
	{
		int min_index = i;
		
		for (int j = i+1; j < m_items.GetSize(); j++)
		{
			if (*m_items[j] > *m_items[min_index])
			{
				min_index = j;
			}
		}

		if (i != min_index)	// Swap
		{
			CComObject<SMILTime>* temp = m_items[i];
			m_items[i] = m_items[min_index];
			m_items[min_index] = temp;
		}
	}
}
#endif

bool SMILTimeList::parseString(StringIn s)
{
	vector<String> times;

ASSERT(0);
#if 0

	if (s)
	{
		GetSemicolonSepStringArray(s, times);
	}

	RemoveAll();

	for (unsigned int i = 0; i < times.size(); i++)
	{
		SMILTime* time = new SMILTime;
		if (time)
		{
			// TODO, only one
			time->m_pListener = this;
			time->m_ownerElement = m_ownerElement;

			time->parseString(times[i]);	// ??

			m_items.push_back(time);
		}
	}
#endif
	return true;
}

/*
SMILTimeList& SMILTimeList::operator = (const SMILTimeList& value)
{
	ASSERT(0);
	return *this;
}

SMILTimeList& SMILTimeList::operator += (const SMILTimeList& value)
{
	ASSERT(0);
	return *this;
}
*/

void SMILTimeList::setStringValue(StringIn str)
{
	parseString(/*m_ownerDocument,*/ str);
}

String SMILTimeList::getStringValue()
{
	ASSERT(0);
	return nullptr;
#if 0
	sysstring str;
	for (int i = 0; i < m_items.GetSize(); i++)
	{
		if (i > 0) str += OLESTR(";");
		str += sysstring(*m_items[i]);
	}
	return str;
#endif
}

void SMILTimeList::InterpolateValue(SMILTimeList* a, SMILTimeList* b, double t)
{
	ASSERT(0);
}

}	// Web
}
