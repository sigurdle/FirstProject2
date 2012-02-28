#include "stdafx.h"
#include "LXMLEditor.h"

#include "XMLSchema.h"

#if 0

void CComplexContentType::BuildDefs(IDOMElement* parent)
{
	ATLASSERT(m_pModelGroup == NULL);

	CComQIPtr<ILDOMNode> child;
	parent->get_firstChild(&child);
	while (child != NULL)
	{
		CComQIPtr<ILDOMElement> element = child;
		if (element)
		{
			BSTR btagName;
			element->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcscmp(tagName, L"sequence") ||
				!wcscmp(tagName, L"choice"))
			{
				if (m_pModelGroup == NULL)
				{
					m_pModelGroup = new CModelGroup;
					m_pModelGroup->m_element = element;
					m_pModelGroup->m_pSchema = m_pSchema;
				}
				else	// Only one allowed
				{
					WCHAR msg[256];
					swprintf(msg, L"Unexpected element <%s>", (BSTR)tagName);

				}
			}
		}

		CComQIPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	if (m_pModelGroup)
	{
		m_pModelGroup->BuildDefs();
	}

// Attributes
/*
	while (child != NULL)
	{
		CComQIPtr<IDOMElement> element = child;
		if (element)
		{
			CDefinition* pDef = m_pSchema->CreateDefinition(element);
			if (pDef)
			{
				pDef->BuildDefs();	// Recurse
				m_defs.Add(pDef);
			}
		}

		CComQIPtr<IDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
*/
}

// virtual
void CComplexTypeDefinition::BuildDefs()
{
	ATLASSERT(m_pContent == NULL);

// Search for complexContent or simpleContent
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

					m_pContent->m_pSchema = m_pSchema;
					m_pContent->m_element = element;

					CComQIPtr<IDOMNode> child;
					element->get_firstChild(&child);

					if (child)
					{
						CComQIPtr<IDOMElement> element = child;
						if (element)
						{
							BSTR btagName;
							element->get_tagName(&btagName);
							_bstr_t tagName = _bstr_t(btagName, false);

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

								m_pContent->BuildDefs(element);
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

					}
				}
				else
				{
					WCHAR msg[256];
					swprintf(msg, L"Can only have one of complexContent/simpleContent");

				}
			}
		}

		CComQIPtr<IDOMNode> nextSibling;
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

		m_pContent->BuildDefs(m_element);
	}
}

#endif