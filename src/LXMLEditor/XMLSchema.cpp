#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "EElement.h"

#if 0

// There is the same function in DOMCOREMod (TODO)
_bstr_t FindNamespaceURIFromAttributes(IDOMNamedNodeMap* attributes, BSTR prefix)
{
	unsigned long length;
	attributes->get_length(&length);
	for (unsigned long i = 0; i < length; i++)
	{
		CComQIPtr<IDOMAttr> attr;
		attributes->item(i, (IDOMNode**)&attr);

		/*
		BSTR battrName;
		attr->get_nodeName(&battrName);
		_bstr_t attrName = _bstr_t(battrName, false);
		*/

	//	if (!wcsicmp(attrName, L"xmlns", 5))
	//	{

		BSTR battprefix;
		attr->get_prefix(&battprefix);
		_bstr_t attprefix = _bstr_t(battprefix, false);

		if (attprefix.length() && !wcsicmp(attprefix, L"xmlns"))
		{
			BSTR battlocalname;
			attr->get_localName(&battlocalname);
			_bstr_t attlocalname;
			if (battlocalname)
				attlocalname = _bstr_t(battlocalname, false);
			else
				attlocalname = L"";

			if ((SysStringLen(prefix) == 0 && SysStringLen(attlocalname) == 0) ||
				!wcscmp(attlocalname, prefix))
			{
				BSTR bvalue;
				attr->get_value(&bvalue);
				return _bstr_t(bvalue, false);
			}
		}
	}

	return L"";
}

// There is the same function in DOMCOREMod (TODO)
_bstr_t FindNamespaceURI(IDOMNode* parent, IDOMNamedNodeMap* attributes, BSTR prefix)
{
	if (attributes)
	{
		_bstr_t namespaceURI = FindNamespaceURIFromAttributes(attributes, prefix);
		if (namespaceURI.length()) return namespaceURI;
	}

// Try parent element
	if (parent)
	{
		CComQIPtr<IDOMNode> parentParent;
		parent->get_parentNode(&parentParent);

		CComQIPtr<IDOMNamedNodeMap> parentAttributes;
		parent->get_attributes(&parentAttributes);
		return FindNamespaceURI(parentParent, parentAttributes, prefix);
	}

	return L"";//_bstr_t((BSTR)NULL);
}

// There is the same function in DOMCOREMod (TODO)
void ExtractURILocal(IDOMNode* parentElement, BSTR name, _bstr_t& uri, _bstr_t& local)
{
	WCHAR* colon = wcschr(name, L':');
	if (colon)
	{
		_bstr_t prefix = SysAllocStringLen(name, colon-name);
		uri = FindNamespaceURI(parentElement, NULL, prefix);
		local = colon+1;
	}
	else
	{
		local = name;
	}
};

// There is the same function in DOMCOREMod (TODO)
int GetElementAttributeInteger(IDOMNode* node, BSTR name, int defVal)
{
	CComQIPtr<IDOMElement> element = node;
	if (element)
	{
		BSTR bval;
		element->getAttribute(name, &bval);
		_bstr_t val = _bstr_t(bval, false);
		if (val.length()) return atol(val);
	}

	return defVal;
}

#include "XMLSchema.h"

/*
BOOL CDefinition::IsGlobal()
{
	CComQIPtr<IDOMNode> parentNode;
	m_element->get_parentNode(&parentNode);

	CComQIPtr<IDOMDocument> document;
	m_element->get_ownerDocument(&document);

	CComQIPtr<IDOMElement> documentElement;
	document->get_documentElement(&documentElement);

	if (documentElement == parentNode)
		return TRUE;
	else
		return FALSE;
}
*/

CDefinition* CSchema::CreateDefinition(IDOMElement* element)
{
	CDefinition* pDef = NULL;

	BSTR btagName;
	element->get_tagName(&btagName);
	_bstr_t tagName = _bstr_t(btagName, false);

	if (!wcscmp(tagName, L"element"))
	{
		pDef = new CElementDefinition;
	}
	else if (!wcscmp(tagName, L"attribute"))
	{
		pDef = NULL;//new CElementDefinition;
	}
	else if (!wcscmp(tagName, L"simpleType"))
	{
		pDef = new CSimpleTypeDefinition;
	}
	else if (!wcscmp(tagName, L"complexType"))
	{
		pDef = new CComplexTypeDefinition;
	}

	if (pDef)
	{
		pDef->m_element = element;
		pDef->m_pSchema = this;
	}

	return pDef;
}

CDefinition* CSchema::CreateGlobalDefinition(IDOMElement* element)
{
	CDefinition* pDef = NULL;

	BSTR btagName;
	element->get_tagName(&btagName);
	_bstr_t tagName = _bstr_t(btagName, false);

	if (!wcscmp(tagName, L"element"))
	{
		pDef = new CGlobalElementDefinition;
	}
	else if (!wcscmp(tagName, L"attribute"))
	{
		pDef = NULL;//new CElementDefinition;
	}
	else if (!wcscmp(tagName, L"simpleType"))
	{
		pDef = new CSimpleTypeDefinition;
	}
	else if (!wcscmp(tagName, L"complexType"))
	{
		pDef = new CComplexTypeDefinition;
	}

	if (pDef)
	{
		pDef->m_element = element;
		pDef->m_pSchema = this;
	}

	return pDef;
}

void CSchema::IncludeSchema(IDOMElement* mergeDocumentElement)
{
	CComQIPtr<IDOMNode> child;
	mergeDocumentElement->get_firstChild(&child);
	while (child != NULL)
	{
		CComQIPtr<IDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);

		CComQIPtr<IDOMElement> element = child;
		if (element)
		{
			BSTR btagName;
			element->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcscmp(tagName, L"include"))
			{
				CInclude* pEl = new CInclude;
				pEl->m_element = element;
				m_globalElements.Add(pEl);

				BSTR bschemaLocation;
				element->getAttribute(L"schemaLocation", &bschemaLocation);
				_bstr_t schemaLocation = _bstr_t(bschemaLocation, false);

				CComQIPtr<IXMLSchemaDocument> schemadoc;
				schemadoc.CoCreateInstance(CLSID_XMLSchemaDocument);
				VARIANT_BOOL bloadedSchema;
				schemadoc->load(schemaLocation, &bloadedSchema);
				if (bloadedSchema)
				{
					CComQIPtr<IDOMElement> mergeDocumentElement;
					schemadoc->get_documentElement(&mergeDocumentElement);
					if (mergeDocumentElement)
					{
						AddDocument(schemadoc);
						IncludeSchema(mergeDocumentElement);	// Recurse
					}
					else
					{
						MessageBox(NULL, "Failed to include schema", "", MB_OK);
					}
				}
				else
				{
					MessageBox(NULL, "Failed to include schema", "", MB_OK);
				}
			}
			else
			{
				CDefinition* pDef = CreateGlobalDefinition(element);
				if (pDef)
				{
					pDef->BuildDefs();

					m_globalDefs.m_defs.Add(pDef);
					m_globalElements.Add(pDef);
				}
				//m_schemaElement->appendChild(element, NULL);
			}
		}

		child = nextSibling;
	}
}

////////////////////////

CGlobalElementDefinition* CSchema::FindElementElementByName(IDOMNode* parent, BSTR btypename)
{
	_bstr_t targetNamespace = GetTargetNamespace();//_bstr_t(btargetNamespace, false);

	_bstr_t uri;
	_bstr_t local;
	ExtractURILocal(parent, btypename, uri, local);

// Find a 'element' element with name attribute belLocalName
	for (int i = 0; i < m_globalDefs.m_defs.GetSize(); i++)
	{
		CGlobalElementDefinition* pDef = (CGlobalElementDefinition*)m_globalDefs.m_defs[i];
		if (!wcscmp(pDef->GetDefType(), L"element"))
		{
			BSTR bname;
			pDef->m_element->getAttribute(L"name", &bname);
			_bstr_t name = _bstr_t(bname, false);

			if (!wcscmp(name, local))
			{
				return pDef;
			}
		}
	}

	return NULL;
}

CTypeDefinition* CSchema::FindTypeElementByName(IDOMNode* parent, BSTR btypename)
{
	_bstr_t targetNamespace = GetTargetNamespace();

	_bstr_t uri;
	_bstr_t local;
	ExtractURILocal(parent, btypename, uri, local);

// Find a 'complexType'/'simpleType element with name attribute belLocalName
	for (int i = 0; i < m_globalDefs.m_defs.GetSize(); i++)
	{
		CTypeDefinition* pDef = (CTypeDefinition*)m_globalDefs.m_defs[i];

		_bstr_t type = pDef->GetDefType();

		if (!wcscmp(type, L"complexType") ||
			!wcscmp(type, L"simpleType"))
		{
			_bstr_t name = pDef->GetName();

			if (!wcscmp(name, local))
			{
				return pDef;
			}
		}
	}

	return NULL;
}

#endif