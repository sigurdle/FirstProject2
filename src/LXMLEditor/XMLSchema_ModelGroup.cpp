#include "stdafx.h"
#include "LXMLEditor.h"

#include "XMLSchema.h"

#if 0

int GetElementAttributeInteger(IDOMNode* node, BSTR name, int defVal);

void CModelGroup::BuildDefs()
{
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

			CSchemaNode* pNode = NULL;

			if (!wcscmp(tagName, L"element"))
			{
				CElementDefinition* pDef = new CElementDefinition;
				pDef->m_pParentModelGroup = this;
				pNode = pDef;

				pNode->m_element = element;
				pNode->m_pSchema = m_pSchema;

				pNode->BuildDefs();

				m_defs.m_defs.Add(pDef);
			}
			else if (!wcscmp(tagName, L"sequence") ||
						!wcscmp(tagName, L"choice"))
			{
				pNode = new CModelGroup;
				pNode->m_element = element;
				pNode->m_pSchema = m_pSchema;

				pNode->BuildDefs();	// Recurse
			}

			if (!pNode)
			{
				WCHAR msg[256];
				swprintf(msg, L"Unsupported element %s", tagName);
			}

//			m_nodes.Add(pNode);
		}

		CComQIPtr<IDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
}

#endif