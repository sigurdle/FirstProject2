#include "stdafx.h"
#include "LXMLEditor.h"

#include "XMLSchema.h"

#if 0

_bstr_t CGlobalElementDefinition::GetElementName()
{
	BSTR bname;
	m_element->getAttribute(L"name", &bname);
	if (bname)
	{
		return _bstr_t(bname, false);
	}

	ATLASSERT(0);
	return L"";
}

void CGlobalElementDefinition::BuildDefs()
{
	ATLASSERT(m_pAnynomousTypeDef == NULL);

	CComQIPtr<IDOMNode> child;
	m_element->get_firstChild(&child);
	while (child != NULL)
	{
		CComQIPtr<IDOMElement> element = child;
		if (element)
		{
			BSTR btagName;
			element->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcscmp(tagName, L"complexType") ||
				!wcscmp(tagName, L"simpleType"))
			{
				if (m_pAnynomousTypeDef == NULL)
				{
					m_pAnynomousTypeDef = (CTypeDefinition*)m_pSchema->CreateDefinition(element);
					m_pAnynomousTypeDef->BuildDefs();
				}
				else
				{
					// Error
				}
			}
			else
			{
				// Error
			}
		}

		CComQIPtr<IDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
}

CTypeDefinition* CGlobalElementDefinition::GetTypeDefinition()
{
	if (m_pAnynomousTypeDef)
	{
		return m_pAnynomousTypeDef;
	}
	else
	{
		BSTR btype;
		m_element->getAttribute(L"type", &btype);
		_bstr_t type = _bstr_t(btype, false);
		if (type.length())
		{
			return m_pSchema->FindTypeElementByName(m_element, type);
		}
	}

	return NULL;
}

#endif