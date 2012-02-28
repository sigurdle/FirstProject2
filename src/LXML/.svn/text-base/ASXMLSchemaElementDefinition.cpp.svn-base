#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"
#include "ASXMLSchemaModel.h"
#include "ASXMLSchemaElementDefinition.h"

#if 0

namespace LXML
{

#if 0

int GetElementAttributeInteger(ILDOMNode* node, BSTR name, int defVal);
#endif

struct ASDataTypeString
{
	ASDataType dataType;
	WCHAR* dataTypeString;
};

ASDataTypeString dataTypeStrings[] =
{
	STRING_DATATYPE, L"string",
	NOTATION_DATATYPE, L"",
	ID_DATATYPE, L"",
	IDREF_DATATYPE, L"",
	IDREFS_DATATYPE, L"",
	ENTITY_DATATYPE, L"",
	ENTITIES_DATATYPE, L"",
	NMTOKEN_DATATYPE, L"",
	NMTOKENS_DATATYPE, L"",
	BOOLEAN_DATATYPE, L"",
	FLOAT_DATATYPE, L"",
	DOUBLE_DATATYPE, L"",
	DECIMAL_DATATYPE, L"",
	HEXBINARY_DATATYPE, L"",
	BASE64BINARY_DATATYPE, L"",
	ANYURI_DATATYPE, L"",
	QNAME_DATATYPE, L"",
	DURATION_DATATYPE, L"",
	DATETIME_DATATYPE, L"",
	DATE_DATATYPE, L"",
	TIME_DATATYPE, L"",
	GYEARMONTH_DATATYPE, L"",
	GYEAR_DATATYPE, L"",
	GMONTHDAY_DATATYPE, L"",
	GDAY_DATATYPE, L"",
	GMONTH_DATATYPE, L"",
	INTEGER, L"",
	NAME_DATATYPE, L"",
	NCNAME_DATATYPE, L"",
	NORMALIZEDSTRING_DATATYPE, L"",
	TOKEN_DATATYPE, L"",
	LANGUAGE_DATATYPE, L"",
	NONPOSITIVEINTEGER_DATATYPE, L"",
	NEGATIVEINTEGER_DATATYPE, L"",
	LONG_DATATYPE, L"",
	INT_DATATYPE, L"",
	SHORT_DATATYPE, L"",
	BYTE_DATATYPE, L"",
	NONNEGATIVEINTEGER_DATATYPE, L"",
	UNSIGNEDLONG_DATATYPE, L"",
	UNSIGNEDINT_DATATYPE, L"",
	UNSIGNEDSHORT_DATATYPE, L"",
	UNSIGNEDBYTE_DATATYPE, L"",
	POSITIVEINTEGER_DATATYPE, L"",
};

#define NDATATYPES (sizeof(dataTypeStrings)/sizeof(ASDataTypeString))

ASDataType SimpleDataTypeFromString(const OLECHAR* s)
{
	for (int i = 0; i < NDATATYPES; i++)
	{
		if (!wcscmp(s, dataTypeStrings[i].dataTypeString))
		{
			return dataTypeStrings[i].dataType;
		}
	}

	return (ASDataType)-1;
}

#if 0
/////////////////////////////////////////////////////////////////////////////
// CElementDefinition

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
#endif

void CElementDefinition::BuildDefs(Element* m_element)
{
//	ASSERT(m_pAnynomousTypeDef == NULL);
	m_nodeName = m_element->getAttribute(OLESTR("name"));

	sysstring type = m_element->getAttribute(L"type");
	if (type != NULL)
	{
		ASDataType dataType = SimpleDataTypeFromString(type.c_str());
		if (dataType != (ASDataType)-1)
		{
			m_pType = new CSimpleTypeDefinition;
			m_pType->m_pSchema = m_pSchema;
		}
		else
		{
		}
	}

	Node* child = m_element->get_firstChild();
	while (child != NULL)
	{
		Element* element = dynamic_cast<Element*>(child);
		if (element)
		{
			sysstring tagName = element->get_tagName();

			if ((tagName == L"complexType") ||
				(tagName == L"simpleType"))
			{
				m_pType = (CTypeDefinition*)m_pSchema->CreateDefinition(element);
				m_pType->BuildDefs(element);
#if 0
				if (m_pAnynomousTypeDef == NULL)
				{
					m_pAnynomousTypeDef = (IASDataTypeDeclaration*)/*(CTypeDefinition*)*/m_pSchema->CreateDefinition(element);
					m_pAnynomousTypeDef->BuildDefs();
				}
				else
				{
					// Error
				}
#endif
			}
			else
			{
				// Error
				THROW(-1);
			}
		}

		child = child->get_nextSibling();
	}
}

#if 0
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

////////////////////////////////
//

STDMETHODIMP CElementDefinition::get_nodeName(/*[out, retval]*/ BSTR *pVal)
{
	return m_element->getAttribute(L"name", pVal);
}

STDMETHODIMP CElementDefinition::set_nodeName(/*[in]*/ BSTR newVal)
{
	m_element->setAttribute(L"name", newVal);

// Notify userhandlers
	{
		for (int i = 0; i < m_userdataList.GetSize(); i++)
		{
			CUserData* userdata = m_userdataList[i];
			userdata->m_handler->_handle((ASUserDataHandleType)ASNODE_RENAMED/*operation*/, userdata->m_key, userdata->m_data, NULL, NULL);
		}
	}

	return S_OK;
}

STDMETHODIMP CElementDefinition::cloneASObject(/*[in]*/ bool deep, /*[out,retval]*/ IASObject** pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	CComObject<CElementDefinition>* pElement;
	CComObject<CElementDefinition>::CreateInstance(&pElement);
	if (pElement)
	{
		pElement->AddRef();

		CComBSTR nodeName;
		get_nodeName(&nodeName);

		pElement->m_pSchema = m_pSchema;
		m_pSchema->m_xmlDocument->createElement(L"element", &pElement->m_element);
		pElement->set_nodeName(nodeName);

		*pVal = pElement;
	}

	return S_OK;
}

STDMETHODIMP CElementDefinition::get_asCM(/*[out, retval]*/ IASContentModel* *pVal)
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

STDMETHODIMP CElementDefinition::get_elementType(/*[out, retval]*/ ASDataType *pVal)
{
	CComBSTR type;
	m_element->getAttribute(L"type", &type);

	ASDataType dataType = SimpleDataTypeFromString(type);

	*pVal = dataType;

	return S_OK;
}

STDMETHODIMP CElementDefinition::set_elementType(/*[in]*/ ASDataType newVal)
{
	return S_OK;
}

//CTypeDefinition* CElementDefinition::GetTypeDefinition()
STDMETHODIMP CElementDefinition::get_elementDataType(/*[out, retval]*/ IASDataTypeDeclaration* *pVal)
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
		BSTR btype;
		m_element->getAttribute(L"type", &btype);
		_bstr_t type = _bstr_t(btype, false);
		if (type.length())
		{
			*pVal = m_pSchema->FindTypeElementByName(m_element, type);
			if (*pVal) (*pVal)->AddRef();
		}
	}

	return S_OK;
}

#endif

}	// LXML

#endif