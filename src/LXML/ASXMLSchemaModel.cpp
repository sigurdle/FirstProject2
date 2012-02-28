#include "stdafx.h"
#include "LXML2.h"
#include "ASXMLSchemaModel.h"
#include "ASXMLSchemaElementDefinition.h"
#include "ASXMLComplexTypeDeclaration.h"

namespace System
{
namespace Web
{

int GetElementAttributeInteger(Node* node, StringIn name, int defVal)
{
	Element* element = dynamic_cast<Element*>(node);
	if (element)
	{
		String val = element->getAttribute(name);
		if (val.GetLength()) return str2int(CString(val));
	}

	return defVal;
}

/////////////////////////////////////////////////////////////
IASModel* CSchemaNode::get_ownerASModel_()
{
	return m_pSchema;
}

///////////////////////////////////////////////////////////////////////////////

CASXMLSchemaModel::CASXMLSchemaModel()
{
	m_globalElements = new CASXMLNamedObjectMap;
}

IASNamedObjectMap* CASXMLSchemaModel::get_contentModelDeclarations()
{
	return NULL;
}
IASNamedObjectMap* CASXMLSchemaModel::get_entityDeclarations()
{
	return NULL;
}

IASNamedObjectMap* CASXMLSchemaModel::get_notationDeclarations()
{
	return NULL;
}

IASNamedObjectMap* CASXMLSchemaModel::get_attributeDeclarations()
{
	return NULL;
}

#if 0

/////////////////////////////////////////////////////////////////////////////
// CASXMLSchemaModel

CComBSTR FindNamespaceURIFromAttributes(ILDOMNamedNodeMap* attributes, BSTR prefix);

CComBSTR FindNamespaceURI(ILDOMNode* parent, ILDOMNamedNodeMap* attributes, BSTR prefix);

void ExtractURILocal(ILDOMNode* parentElement, BSTR name, _bstr_t& uri, _bstr_t& local)
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

//#include "XMLSchema.h"

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
#endif

CDefinition* /*CDefinition* */ CASXMLSchemaModel::CreateDefinition(Element* element)
{

	CDefinition* pDef = NULL;
	ASSERT(0);
#if 0

	StringW* tagName = element->get_tagName();

	if (*tagName == L"element")
	{
		ASSERT(0);
		CElementDefinition* p = NULL;//new CElementDefinition;
		//p->AddRef();

	//	p->m_element = element;
		p->m_pSchema = this;
		pDef = p;
	}
	else if (*tagName == L"attribute")
	{
		ASSERT(0);
		pDef = NULL;//new CElementDefinition;
	}
	else if (*tagName == L"simpleType")
	{
		ASSERT(0);
		CSimpleTypeDefinition* p = NULL;//new CSimpleTypeDefinition;

//		p->m_element = element;
		p->m_pSchema = this;
		pDef = p;
	}
	else if (*tagName == L"complexType")
	{
		ASSERT(0);
		CComplexTypeDefinition* p = NULL;//new CComplexTypeDefinition;

//		p->m_element = element;
		p->m_pSchema = this;
		pDef = p;
	}

	if (pDef)
	{
	}
#endif
	return pDef;
}

#if 0
IASDeclaration* CASXMLSchemaModel::CreateGlobalDefinition(ILDOMElement* element)
{
	IASDeclaration* pDef = NULL;

	BSTR btagName;
	element->get_tagName(&btagName);
	_bstr_t tagName = _bstr_t(btagName, false);

	if (!wcscmp(tagName, L"element"))
	{
		CComObject<CGlobalElementDefinition>* p;
		CComObject<CGlobalElementDefinition>::CreateInstance(&p);
		p->AddRef();
		p->m_element = element;
		p->m_pSchema = this;

		pDef = p;
	}
	else if (!wcscmp(tagName, L"attribute"))
	{
		pDef = NULL;//new CElementDefinition;
	}
	else if (!wcscmp(tagName, L"simpleType"))
	{
		CComObject<CSimpleTypeDefinition>* p;
		CComObject<CSimpleTypeDefinition>::CreateInstance(&p);
		p->AddRef();
		p->m_element = element;
		p->m_pSchema = this;

		pDef = p;
	}
	else if (!wcscmp(tagName, L"complexType"))
	{
		CComObject<CComplexTypeDefinition>* p;
		CComObject<CComplexTypeDefinition>::CreateInstance(&p);
		p->AddRef();
		p->m_element = element;
		p->m_pSchema = this;

		pDef = p;
	}

	if (pDef)
	{
	}

	return pDef;
}
#endif

void CASXMLSchemaModel::BuildFromDocument(Document* document)
{
	IncludeSchema(document->get_documentElement());
}

void CASXMLSchemaModel::IncludeSchema(Element* mergeDocumentElement)
{
//	CComPtr<ILDOMDocument> ownerDocument;
//	mergeDocumentElement->get_ownerDocument(&ownerDocument);

	Node* child = mergeDocumentElement->get_firstChild();
	while (child != NULL)
	{
		Node* nextSibling = child->get_nextSibling();

		Element* element = dynamic_cast<Element*>(child);
		if (element)
		{
			String tagName = element->get_tagName();

			if (tagName == L"include")
			{
				ASSERT(0);
#if 0
				CComObject<CASXMLInclude>* pEl;
				CComObject<CASXMLInclude>::CreateInstance(&pEl);
				if (pEl)
				{
					pEl->AddRef();
					pEl->m_pSchema = this;
					pEl->m_element = element;

					CComObject<CASXMLSchemaModel>::CreateInstance(&pEl->m_asModel);
					if (pEl->m_asModel)
					{
						pEl->m_asModel->AddRef();

						m_globalElements->m_items.Add(pEl);

						CComBSTR schemaLocation;
						element->getAttribute(L"schemaLocation", &schemaLocation);

						TCHAR absSchemaLocation[2048];
						{
							CComBSTR documentUrl;
							ownerDocument->get_url(&documentUrl);

							_bstr_t baseUrl = documentUrl;

							DWORD resultLen = sizeof(absSchemaLocation);
							InternetCombineUrl(baseUrl, _bstr_t(schemaLocation), absSchemaLocation, &resultLen, 0);
						}

						bool bloadedSchema;
						pEl->m_asModel->m_xmlDocument.CoCreateInstance(CLSID_LDOMDocument);
						pEl->m_asModel->m_xmlDocument->load(_variant_t(absSchemaLocation), &bloadedSchema);
						if (bloadedSchema)
						{
							CComPtr<ILDOMElement> mergeDocumentElement;
							pEl->m_asModel->m_xmlDocument->get_documentElement(&mergeDocumentElement);
							if (mergeDocumentElement)
							{
								m_asModels->m_items.Add(pEl->m_asModel);

							//	AddDocument(schemadoc);
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
				}
#endif
			}
			else
			{
				CDefinition/*CDefinition*/ * pDef = CreateDefinition(element);
				if (pDef)
				{
					pDef->BuildDefs(element);

					m_globalDefs.m_defs.Add(pDef);
					m_globalElements->m_items.Add(dynamic_cast<IASDeclaration*>(pDef));
				}
				//m_schemaElement->appendChild(element, NULL);
			}
		}

		child = nextSibling;
	}
}

#if 0
////////////////////////

CGlobalElementDefinition* CASXMLSchemaModel::FindElementElementByName(ILDOMNode* parent, BSTR btypename)
{
	_bstr_t targetNamespace = GetTargetNamespace();//_bstr_t(btargetNamespace, false);

	_bstr_t uri;
	_bstr_t local;
	ExtractURILocal(parent, btypename, uri, local);

// Find a 'element' element with name attribute belLocalName
	for (int i = 0; i < m_globalDefs.m_defs.GetSize(); i++)
	{
		CGlobalElementDefinition* pDef = (CGlobalElementDefinition*)m_globalDefs.m_defs[i];

		CComBSTR deftype;
		pDef->GetDefType(&deftype);

		if (!wcscmp(deftype, L"element"))
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

IASDataTypeDeclaration* /*CTypeDefinition* */ CASXMLSchemaModel::FindTypeElementByName(ILDOMNode* parent, BSTR btypename)
{
	_bstr_t targetNamespace = GetTargetNamespace();

	_bstr_t uri;
	_bstr_t local;
	ExtractURILocal(parent, btypename, uri, local);

// Find a 'complexType'/'simpleType element with name attribute belLocalName
	for (int i = 0; i < m_globalDefs.m_defs.GetSize(); i++)
	{
		IASDeclaration* pDef = /*(CTypeDefinition*)*/m_globalDefs.m_defs[i];

		CComBSTR type;
		pDef->GetDefType(&type);

		if (!wcscmp(type, L"complexType") ||
			!wcscmp(type, L"simpleType"))
		{
			CComQIPtr<IASDataTypeDeclaration> typedecl = pDef;

			CComBSTR name;
			typedecl->GetName(&name);

			if (!wcscmp(name, local))
			{
				return typedecl.p;
			}
		}
	}

	return NULL;
}

/////////////////////////
//////

#include "ASXMLAttributeDeclaration.h"

STDMETHODIMP CASXMLSchemaModel::createASAttributeDeclaration(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR name, /*[out,retval]*/ IASAttributeDeclaration** pVal)
{
	CComObject<CASXMLAttributeDeclaration>* pAttDecl;
	CComObject<CASXMLAttributeDeclaration>::CreateInstance(&pAttDecl);
	if (pAttDecl)
	{
		pAttDecl->AddRef();
		pAttDecl->m_pSchema = this;

		*pVal = pAttDecl;
	}

	return S_OK;
}

STDMETHODIMP CASXMLSchemaModel::createASContentModel(/*[in]*/ unsigned long minOccurs, /*[in]*/ unsigned long maxOccurs, /*[in]*/ ASContentModelTypeOp Operator, /*[out,retval]*/ IASContentModel** pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	CComObject<CModelGroup>* pCM;
	CComObject<CModelGroup>::CreateInstance(&pCM);
	if (pCM)
	{
		pCM->AddRef();
		pCM->m_pSchema = this;

		if (Operator == AS_SEQUENCE)
			m_xmlDocument->createElement(L"sequence", &pCM->m_element);
		else if (Operator == AS_CHOICE)
			m_xmlDocument->createElement(L"choice", &pCM->m_element);
		else if (Operator == AS_ALL)
			m_xmlDocument->createElement(L"all", &pCM->m_element);

		pCM->set_minOccurs(minOccurs);
		pCM->set_maxOccurs(maxOccurs);

		*pVal = pCM;
	}

	return S_OK;
}

STDMETHODIMP CASXMLSchemaModel::get_xmlDocument(ILDOMDocument **pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_xmlDocument;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CASXMLSchemaModel::put_xmlDocument(ILDOMDocument *newVal)
{
	if (newVal == NULL) return E_INVALIDARG;

	CComPtr<ILDOMDocument> schemadoc = newVal;

	m_xmlDocument = newVal;

	CComPtr<ILDOMElement> mergeDocumentElement;
	schemadoc->get_documentElement(&mergeDocumentElement);

	if (mergeDocumentElement)
	{
	// Copy the targetNamespace attribute (hm..)
		{
			BSTR b;
			mergeDocumentElement->getAttribute(L"targetNamespace", &b);
			if (b)
			{
				m_targetNamespace = b;
				//pSchema->m_schemaElement->setAttribute(L"targetNamespace", b);
				SysFreeString(b);
			}
		}

		{
			BSTR b;
			mergeDocumentElement->getAttribute(L"elementFormDefault", &b);
			if (b)
			{
				m_elementFormDefault = b;
				//pSchema->m_schemaElement->setAttribute(L"elementFormDefault", b);
				SysFreeString(b);
			}
		}

		{
			BSTR b;
			mergeDocumentElement->getAttribute(L"attributeFormDefault", &b);
			if (b)
			{
				m_attributeFormDefault = b;
				//pSchema->m_schemaElement->setAttribute(L"attributeFormDefault", b);
				SysFreeString(b);
			}
		}

		IncludeSchema(mergeDocumentElement);
	}

	return S_OK;
}

/////////////////////////////////////////////////
// CASXMLInclude

STDMETHODIMP CASXMLInclude::get_asModel(/*[out, retval]*/ IASModel* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_asModel;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CASXMLInclude::get_abslocation(/*[out, retval]*/ BSTR *pVal)
{
	return m_asModel->m_xmlDocument->get_url(pVal);
}

#endif

}	// Web
}
