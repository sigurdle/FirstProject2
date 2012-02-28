#include "stdafx.h"
#include "LXMLEditor.h"

#if 0

int GetElementAttributeInteger(ILDOMNode* node, BSTR name, int defVal);

#include "XMLSchema.h"

int CElementDefinition::GetMinOccurs()
{
	return GetElementAttributeInteger(m_element, L"minOccurs", 1);
}

DWORD CElementDefinition::GetMaxOccurs()
{
	BSTR bval;
	m_element->getAttribute(L"maxOccurs", &bval);
	_bstr_t val = _bstr_t(bval, false);
	if (val.length() == 0) return 1;

	if (!wcscmp(val, L"unbounded"))
		return (DWORD)-1;
	else
		return atol(val);
}

void CElementDefinition::BuildDefs()
{
	ATLASSERT(m_pAnynomousTypeDef == NULL);

	CComQIPtr<IDOMNode> child;
	m_element->get_firstChild(&child);
	while (child != NULL)
	{
		CComQIPtr<ILDOMElement> element = child;
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

bool CElementDefinition::IsRef()
{
	BSTR bref;
	m_element->getAttribute(L"ref", &bref);
	_bstr_t ref = _bstr_t(bref, false);
	if (ref.length())
	{
		return true;
	}
	else
		return false;
}

_bstr_t CElementDefinition::GetElementName()
{
	BSTR bname;
	m_element->getAttribute(L"name", &bname);
	if (bname)
	{
		return _bstr_t(bname, false);
	}
	else
	{
		BSTR bref;
		m_element->getAttribute(L"ref", &bref);
		_bstr_t ref = _bstr_t(bref, false);
		if (ref.length())
		{
			CGlobalElementDefinition* elementdef = m_pSchema->FindElementElementByName(m_element, ref);
			if (elementdef)
			{
				return elementdef->GetElementName();
			}
			else
			{
			// Error
			}
		}
	}

// Error

	return L"";
}

CTypeDefinition* CElementDefinition::GetTypeDefinition()
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