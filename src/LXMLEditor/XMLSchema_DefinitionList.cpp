#include "stdafx.h"
#include "LXMLEditor.h"

#include "XMLSchema.h"

#if 0

CElementDefinition* CDefList::FindElementDefinition(IDOMElement* element)
{
	ATLASSERT(0);
#if 0
	BSTR belLocalName;
	element->get_localName(&belLocalName);
	_bstr_t elLocalName;
	if (SysStringLen(belLocalName) == 0) element->get_tagName(&belLocalName);
	elLocalName = _bstr_t(belLocalName, false);

	BSTR belNamespace;
	element->get_namespaceURI(&belNamespace);
	_bstr_t elNamespace = _bstr_t(belNamespace, false);

	_bstr_t targetNamespace = m_pSchema->GetTargetNamespace();

	for (int i = 0; i < m_defs.GetSize(); i++)
	{
		CElementDefinition* def = (CElementDefinition*)m_defs[i];

		if (!wcscmp(def->GetDefType(), L"element"))
		{
			BSTR bname;
			def->m_element->getAttribute(L"name", &bname);
			_bstr_t name = _bstr_t(bname, false);
			if (!wcscmp(name, belLocalName))
			{
				BOOL mustbequalified = def->GetMustBeQualified(element);

				if (mustbequalified)
				{
					if (!wcscmp(elNamespace, targetNamespace))
					{
						return def;
					}
				}
				else
				{
					if (SysStringLen(elNamespace) == 0)
						return def;
				}
			}
		}
	}
#endif

	return NULL;
}


#endif