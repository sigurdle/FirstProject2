#include "stdafx.h"
#include "HTML2.h"

#if 0

#include "ASXMLSchemaModel.h"

#include "ASXMLAttributeDeclaration.h"

void CComplexContentType::BuildDefs(ILDOMElement* parent)
{
	ASSERT(m_pModelGroup == NULL);
	ASSERT(m_pSchema);

	CComPtr<ILDOMNode> child;
	parent->get_firstChild(&child);
	while (child != NULL)
	{
		CComQIPtr<ILDOMElement> element = child;
		if (element)
		{
			CComBSTR tagName;
			element->get_tagName(&tagName);

			if (!wcscmp(tagName, L"sequence") ||
				!wcscmp(tagName, L"choice"))
			{
				if (m_pModelGroup == NULL)
				{
					CComObject<CModelGroup>::CreateInstance(&m_pModelGroup);
					m_pModelGroup->AddRef();
					m_pModelGroup->m_pSchema = m_pSchema;
					m_pModelGroup->m_element = element;
				}
				else	// Only one allowed
				{
					WCHAR msg[256];
					swprintf(msg, L"Unexpected element <%s>", (BSTR)tagName);

					throw msg;
				}
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	if (m_pModelGroup)
	{
		m_pModelGroup->BuildDefs();
	}

}

///////////////////////////////////////
// CComplexTypeDefinition

void CComplexTypeDefinition::BuildAttributes(ILDOMElement* parent)
{
	CComPtr<ILDOMNode> child;
	parent->get_firstChild(&child);

	while (child != NULL)
	{
		CComQIPtr<ILDOMElement> element = child;
		if (element)
		{
			CComBSTR tagName;
			element->get_tagName(&tagName);

			if (!wcscmp(tagName, L"attribute"))
			{
				CComObject<CASXMLAttributeDeclaration>* p;
				CComObject<CASXMLAttributeDeclaration>::CreateInstance(&p);
				if (p)
				{
					p->AddRef();
					p->m_pSchema = m_pSchema;
					p->m_element = element;

					m_attributeDecls->m_items.Add(p);
				}
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
}

// virtual
STDMETHODIMP CComplexTypeDefinition::BuildDefs()
{
	ASSERT(m_pContent == NULL);

// Search for complexContent or simpleContent
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

			if (!wcscmp(tagName, L"complexContent") ||
				!wcscmp(tagName, L"simpleContent"))
			{
				if (m_pContent == NULL)
				{
					if (!wcscmp(tagName, L"complexContent"))
					{
						m_pContent = new CComplexContentType;
					}
					else
					{
						m_pContent = new CSimpleContentType;
					}

//					m_pContent->m_pBaseType = this;
					m_pContent->m_pSchema = m_pSchema;
					m_pContent->m_element = element;

					CComPtr<ILDOMNode> child;
					element->get_firstChild(&child);

					if (child)
					{
						CComQIPtr<ILDOMElement> element = child;
						if (element)
						{
							CComBSTR tagName;
							element->get_tagName(&tagName);

							if (!wcscmp(tagName, L"extension") ||
								!wcscmp(tagName, L"restriction"))
							{
								if (!wcscmp(tagName, L"extension"))
								{
									m_pContent->m_derivationMethod = L"extension";
								}
								else if (!wcscmp(tagName, L"restriction"))
								{
									m_pContent->m_derivationMethod = L"restriction";

									BSTR bbase;
									element->getAttribute(L"base", &bbase);
									m_pContent->m_base = _bstr_t(bbase, false);
									if (m_pContent->m_base.length() == 0)
									{
										WCHAR msg[256];
										swprintf(msg, L"restriction element is missing base attribute");

									}
								}

								m_deepElement = element;
								m_pContent->BuildDefs(element);
								BuildAttributes(element);
							}
							else
							{
								WCHAR msg[256];
								swprintf(msg, L"Unexpected element");

							}
						}
					}

					if (m_pContent->m_derivationMethod.length() == 0)
					{
						WCHAR msg[256];
						swprintf(msg, L"Expected either <restriction> or <extension> element");

						throw msg;
					}
				}
				else
				{
					WCHAR msg[256];
					swprintf(msg, L"Can only have one of complexContent/simpleContent");

					throw msg;
				}
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

// If there is no complexContent or simpleContent then
// defaults to restricted complexContent
	if (m_pContent == NULL)
	{
		CComplexContentType* pComplexContent = new CComplexContentType;
		pComplexContent->m_derivationMethod = L"restriction";

		m_pContent = pComplexContent;
		m_pContent->m_pSchema = m_pSchema;
		m_pContent->m_element = NULL;
		m_deepElement = m_element;

		m_pContent->BuildDefs(m_element);
		BuildAttributes(m_element);
	}

	return S_OK;
}

STDMETHODIMP CComplexTypeDefinition::get_asCM(/*[out, retval]*/ IASContentModel* *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
// TODO
	*pVal = ((CComplexContentType*)m_pContent)->m_pModelGroup;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CComplexTypeDefinition::addASAttributeDecl(/*[in]*/ IASAttributeDeclaration* attributeDecl)
{
	if (attributeDecl == NULL) return E_INVALIDARG;

	attributeDecl->AddRef();

	CComPtr<ILDOMElement> element;
	attributeDecl->GetElement(&element);
	ASSERT(element);

	ASSERT(m_deepElement);
	m_deepElement->appendChild(element, NULL);

	m_attributeDecls->m_items.Add(attributeDecl);

	return S_OK;
}

STDMETHODIMP CComplexTypeDefinition::removeASAttributeDecl(/*[in]*/ IASAttributeDeclaration* attributeDecl, /*[out,retval]*/ IASAttributeDeclaration** pVal)
{
	return S_OK;
}

#endif