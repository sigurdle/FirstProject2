#include "stdafx.h"
#include "LXML2.h"
#include "EntityReference.h"

#include "Entity.h"

namespace System
{
namespace Web
{

EntityReference::EntityReference()
{
	m_entity = nullptr;
}

EntityReference::~EntityReference()
{
	ASSERT(m_entity == nullptr);
}

String EntityReference::get_nodeName()
{
	if (m_entity)
	{
		return m_entity->get_nodeName();
	}
	else
	{
		return nullptr;
	}
}

#if 0
STDMETHODIMP EntityReference::get_textContent(/*[out, retval]*/ BSTR *pVal)
{
	ASSERT(pVal != nullptr);
	if (pVal == nullptr) return E_POINTER;

	/*
	if (m_entity)
	{
		*pVal = m_entity->m_value.Copy();
	}
	else
	{
		*pVal = NULL;
	}
	*/

	return S_OK;
}
#endif

}	// Web
}	// System
