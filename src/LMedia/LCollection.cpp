#include "stdafx.h"
#include "LMediaImpl.h"
#include "LCollection.h"

namespace System
{
namespace MediaShow
{

unsigned int CDispLCollection::get_Count()
{
	return m_items.GetSize();
}

IBaseFilter* CDispLCollection::Item(unsigned int index)
{
	if (index < m_items.GetSize())
	{
		return m_items[index];
		//(*pVal)->AddRef();
	}
	else
		return NULL;
}

}	// MediaShow
}
