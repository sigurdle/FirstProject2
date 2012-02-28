// LXUINodeList.cpp : Implementation of CLXUINodeList
#include "stdafx.h"

#if 0

#ifdef AMIGA
#define new DEBUG_NEW
#endif

#include "LXUI.h"
#include "LXUI2.h"
#include "LXUINodeList.h"

namespace UI
{

/////////////////////////////////////////////////////////////////////////////
// CLXUINodeList

long CLXUINodeList::get_length()
{
	return m_items.size();
}

CLXUINodeImpl* CLXUINodeList::item(long index)
{
	if (index >= 0 && index < m_items.size())
	{
		return m_items[index];
	}
	else
	{
		return NULL;
	}
}

}	// UI

#endif