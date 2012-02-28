#include "stdafx.h"
#include "HTML2.h"

#if 0

#include "ASXMLSchemaModel.h"

#include "ASXMLAttributeDeclaration.h"

/////////////////////////////////////////////////////////////////////////////
// CASXMLAttributeDeclaration

// IASObject
STDMETHODIMP CASXMLAttributeDeclaration::cloneASObject(/*[in]*/ VARIANT_BOOL deep, /*[out,retval]*/ IASObject** pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	CComObject<CASXMLAttributeDeclaration>* p;
	CComObject<CASXMLAttributeDeclaration>::CreateInstance(&p);
	if (p)
	{
		p->AddRef();

		p->m_pSchema = m_pSchema;
		m_pSchema->m_xmlDocument->createElement(L"attribute", &p->m_element);

		CComBSTR nodeName;
		get_nodeName(&nodeName);

		p->set_nodeName(nodeName);

		*pVal = p;
	}

	return S_OK;
}

// IASAttributeDeclaration

STDMETHODIMP CASXMLAttributeDeclaration::get_localName(/*[out, retval]*/ BSTR *pVal)
{
	return E_FAIL;
}

STDMETHODIMP CASXMLAttributeDeclaration::put_localName(/*[in]*/ BSTR newVal)
{
	return E_FAIL;
}

STDMETHODIMP CASXMLAttributeDeclaration::get_prefix(/*[out, retval]*/ BSTR *pVal)
{
	return E_FAIL;
}

STDMETHODIMP CASXMLAttributeDeclaration::put_prefix(/*[in]*/ BSTR newVal)
{
	return E_FAIL;
}

STDMETHODIMP CASXMLAttributeDeclaration::get_nodeName(/*[out, retval]*/ BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	return m_element->getAttribute(L"name", pVal);
}

STDMETHODIMP CASXMLAttributeDeclaration::put_nodeName(/*[in]*/ BSTR newVal)
{
	return m_element->setAttribute(L"name", newVal);
}

STDMETHODIMP CASXMLAttributeDeclaration::get_dataType(ASDataType *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CASXMLAttributeDeclaration::put_dataType(ASDataType newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CASXMLAttributeDeclaration::get_dataValue(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CASXMLAttributeDeclaration::put_dataValue(BSTR newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CASXMLAttributeDeclaration::get_enumAttr(BSTR *pVal)
{
	_bstr_t str = L"";

	for (int i = 0; i < m_enums.GetSize(); i++)
	{
		if (i > 0) str += L"|";
		str += m_enums[i];
	}

	*pVal = str.copy();

	return S_OK;
}

STDMETHODIMP CASXMLAttributeDeclaration::put_enumAttr(BSTR newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CASXMLAttributeDeclaration::get_defaultType(ASValueConstraint *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CASXMLAttributeDeclaration::put_defaultType(ASValueConstraint newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

#endif