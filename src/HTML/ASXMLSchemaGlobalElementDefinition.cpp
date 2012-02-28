#include "stdafx.h"
#include "HTML2.h"

#if 0

#include "ASXMLSchemaModel.h"

#include "ASXMLSchemaGlobalElementDefinition.h"

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

STDMETHODIMP CGlobalElementDefinition::BuildDefs()
{
	ATLASSERT(m_pAnynomousTypeDef == NULL);

	CComPtr<ILDOMNode> child;
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
					m_pAnynomousTypeDef = (IASDataTypeDeclaration*)m_pSchema->CreateDefinition(element);
					ATLASSERT(0);
#if 0
					m_pAnynomousTypeDef->BuildDefs();
#endif
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

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	return S_OK;
}

/////////////////////////////

STDMETHODIMP CGlobalElementDefinition::get_asCM(/*[out, retval]*/ IASContentModel* *pVal)
{
	if (pVal == NULL) return E_POINTER;

// hmm...
	*pVal = NULL;

	CComPtr<IASDataTypeDeclaration> dataType;
	get_elementDataType(&dataType);
	if (dataType)
	{
		return dataType->get_asCM(pVal);
	}

	return S_OK;
}

STDMETHODIMP CGlobalElementDefinition::get_elementType(/*[out, retval]*/ ASDataType *pVal)
{
	return S_OK;
}

STDMETHODIMP CGlobalElementDefinition::set_elementType(/*[in]*/ ASDataType newVal)
{
	return S_OK;
}

//IASDataTypeDeclaration* CGlobalElementDefinition::GetTypeDefinition()
STDMETHODIMP CGlobalElementDefinition::get_elementDataType(/*[out, retval]*/ IASDataTypeDeclaration* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	if (m_pAnynomousTypeDef)
	{
		*pVal = m_pAnynomousTypeDef;
		(*pVal)->AddRef();
	}
	else
	{
		CComBSTR type;
		m_element->getAttribute(L"type", &type);
		if (type.Length())
		{
			*pVal = m_pSchema->FindTypeElementByName(m_element, type);
			if (*pVal) (*pVal)->AddRef();
		}
	}

	return S_OK;
}

#endif