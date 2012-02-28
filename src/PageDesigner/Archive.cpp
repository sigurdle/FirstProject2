// Archive.cpp : Implementation of CArchive
#include "stdafx.h"
#include "PageDesigner.h"
#include "Archive.h"

#include "ObjectMap.h"

ILDOMElement* FindByTagName(ILDOMElement* parent, BSTR tagName, BOOL bDeep = TRUE);

//////////////////
// CArchiveElement

STDMETHODIMP CArchiveElement::putObject(IUnknown* pUnk)
{
	//CComQIPtr<IDOMElement> m_element = m_node;

	CComQIPtr<IObjectSerializable> object = pUnk;
	if (object)
	{
		CLSID classID;
		object->GetClassID(&classID);

		LPOLESTR progid;
		ProgIDFromCLSID(classID, &progid);
		if (progid)
		{
			CComPtr<ILDOMElement> element;
			m_pAr->m_xmldoc->createElement(progid, &element);
			if (element)
			{
		//		CMappedObject* pMapped;

				long iOb;
				if ((iOb = m_pAr->LookupObject(object)) != 0)
				{
					//CMappedObject* pMapped = &m_pAr->m_writeTable[iOb-1];

					// save out id of already stored object

					/*
					long id;
					if (pMapped->m_id == 0)
						id = ++m_pAr->m_nextID;
					else
						id = pMapped->m_id;
						*/

					WCHAR buf[16];
					swprintf(buf, L"%d", iOb);

					/*
					if (pMapped->m_id == 0)
					{
						pMapped->m_element->setAttribute(L"id", buf);
						pMapped->m_id = id;
					}
					*/

					element->setAttribute(L"href", buf);
				}
				else
				{
					// Add to map of objects
					m_pAr->MapObject(object);

					// Serialize object
					CComObject<CArchiveElement>* node;
					CComObject<CArchiveElement>::CreateInstance(&node);
					if (node)
					{
						node->AddRef();
						node->m_pAr = m_pAr;
						node->m_node = element;

						object->Serialize(m_pAr, node);

						node->Release();
					}
				}

				m_node->appendChild(element, NULL);
			}
		}
	}

	return S_OK;
}

STDMETHODIMP CArchiveElement::getObject(IUnknown *pUnkExtra, IUnknown **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComQIPtr<ILDOMElement> element = m_node;

	BSTR btagName;
	element->get_tagName(&btagName);
	_bstr_t tagName = _bstr_t(btagName, false);

//	CComQIPtr<IDOMElement> m_element = m_node;

	BSTR bhref;
	element->getAttribute(L"href", &bhref);
	_bstr_t href = _bstr_t(bhref, false);
	if (href.length())
	{
		long index = atol(href)-1;

		(*pVal = m_pAr->m_writeTable[index].m_spUnknown)->AddRef();
		/*
		CComPtr<IDOMElement> hrefElement;
		m_pAr->m_xmldoc->getElementById(href, &hrefElement);
		if (hrefElement)
		{
			CMappedObject* pMapped = m_pAr->LookupElement(hrefElement);
			if (!pMapped) throw;

			pMapped->m_spUnknown->AddRef();
			(*pVal = pMapped->m_spUnknown)->AddRef();
		}
		*/
	}
	else
	{
		CLSID classID;
		if (SUCCEEDED(CLSIDFromProgID(tagName, &classID)))
		{
			CComPtr<IUnknown> spUnknown;
			spUnknown.CoCreateInstance(classID);
			if (spUnknown)
			{
				deserializeObject(element, spUnknown, pUnkExtra);

				(*pVal = spUnknown)->AddRef();
			}
		}
	}

	return S_OK;
}

HRESULT CArchiveElement::deserializeObject(ILDOMElement* element, IUnknown *pUnk, IUnknown* pUnkExtra)
{
	CComObject<CArchiveElement>* pArNode;
	CComObject<CArchiveElement>::CreateInstance(&pArNode);
	if (pArNode)
	{
		pArNode->AddRef();
		pArNode->m_pAr = m_pAr;
		pArNode->m_node = element;

		CComQIPtr<IObjectSerializable> spSerializable = pUnk;
		if (spSerializable)
		{
			m_pAr->MapObject(pUnk);

			spSerializable->Deserialize(m_pAr, pArNode, pUnkExtra);
		}

		pArNode->Release();
	}

	return S_OK;
}

/////

STDMETHODIMP CArchiveElement::serializeElement(BSTR name, IUnknown *pUnk)
{
	CComQIPtr<ILDOMElement> m_element = m_node;

	CComQIPtr<IObjectSerializable> object = pUnk;
	if (object)
	{
		CComPtr<ILDOMElement> element;
		m_pAr->m_xmldoc->createElement(name, &element);
		if (element)
		{
			// Add to map of objects
			m_pAr->MapObject(/*element, */object);

			// Serialize object
			CComObject<CArchiveElement>* node;
			CComObject<CArchiveElement>::CreateInstance(&node);
			if (node)
			{
				node->AddRef();
				node->m_pAr = m_pAr;
				node->m_node = element;

				object->Serialize(m_pAr, node);

				node->Release();
			}

			m_element->appendChild(element, NULL);
		}
	}

	return S_OK;
}

STDMETHODIMP CArchiveElement::deserializeElement(BSTR name, IUnknown *pUnk, IUnknown* pUnkExtra)
{
	CComQIPtr<ILDOMElement> parent = m_node;
	CComQIPtr<ILDOMElement> element = FindByTagName(parent, name, FALSE);
	if (element)
	{
		return deserializeObject(element, pUnk, pUnkExtra);
	}

	return E_FAIL;
}

STDMETHODIMP CArchiveElement::putElement(BSTR name, IUnknown* pUnk)
{
	CComPtr<ILDOMElement> element;
	m_pAr->m_xmldoc->createElement(name, &element);
	if (element)
	{
		CComObject<CArchiveElement>* node;
		CComObject<CArchiveElement>::CreateInstance(&node);
		if (node)
		{
			node->AddRef();
			node->m_pAr = m_pAr;
			node->m_node = element;

			node->putObject(pUnk);

			node->Release();
		}

		m_node->appendChild(element, NULL);
	}

	return S_OK;
}

STDMETHODIMP CArchiveElement::getElement(BSTR name, IUnknown* pUnkExtra, IUnknown **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	CComQIPtr<ILDOMElement> parent = m_node;
	CComQIPtr<ILDOMElement> element = FindByTagName(parent, name, FALSE);
	if (element)
	{
		CComPtr<ILDOMNode> firstChild;
		element->get_firstChild(&firstChild);

		CComQIPtr<ILDOMElement> firstElement = firstChild;
		if (firstElement)
		{
			CComObject<CArchiveElement>* pArNode;
			CComObject<CArchiveElement>::CreateInstance(&pArNode);
			if (pArNode)
			{
				pArNode->AddRef();
				pArNode->m_pAr = m_pAr;
				pArNode->m_node = firstElement;

				pArNode->getObject(pUnkExtra, pVal);

				pArNode->Release();
			}
		}
	}

	return S_OK;
}

STDMETHODIMP CArchiveElement::putAttribute(BSTR name, VARIANT value)
{
	CComPtr<ILDOMAttr> attr;
	m_pAr->m_xmldoc->createAttribute(name, &attr);

	_variant_t v = value;

	if (v.vt == VT_UNKNOWN)
	{
		CComQIPtr<IObjectSerializable> object = v;
		if (object)
		{
			CComObject<CArchiveElement>* node;
			CComObject<CArchiveElement>::CreateInstance(&node);
			node->AddRef();
			node->m_pAr = m_pAr;
			node->m_node = attr;

			object->Serialize(m_pAr, node);

			node->Release();
		}
	}
	else
	{
		attr->put_value(_bstr_t(v));
	}

// Add the attribute node to the element
	CComQIPtr<ILDOMElement> element = m_node;
	ATLASSERT(element != NULL);
	CComPtr<ILDOMNamedNodeMap> attributes;
	element->get_attributes(&attributes);
	attributes->setNamedItem(attr, NULL);

	return S_OK;
}

STDMETHODIMP CArchiveElement::getAttribute(BSTR name, VARIANT *pVal)
{
	CComQIPtr<ILDOMElement> element = m_node;
	ATLASSERT(element != NULL);

	BSTR b;
	element->getAttribute(name, &b);
	_variant_t v = b;
	*pVal = v;

	return S_OK;
}

STDMETHODIMP CArchiveElement::getAttributeNode(BSTR name, IArchiveElement **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	CComQIPtr<ILDOMElement> element = m_node;
	ATLASSERT(element != NULL);
	CComPtr<ILDOMNamedNodeMap> attributes;
	element->get_attributes(&attributes);

	CComPtr<ILDOMAttr> attr;
	attributes->getNamedItem(name, (ILDOMNode**)&attr);
	if (attr)
	{
		CComObject<CArchiveElement>* pArNode;
		CComObject<CArchiveElement>::CreateInstance(&pArNode);
		if (pArNode)
		{
			pArNode->AddRef();
			pArNode->m_pAr = m_pAr;
			pArNode->m_node = attr;

			*pVal = pArNode;
		}
	}

	return S_OK;
}

STDMETHODIMP CArchiveElement::putData(VARIANT value)
{
	_variant_t v = value;

	CComQIPtr<ILDOMElement> element = m_node;
	if (element)
	{
		CComPtr<ILDOMText> text;
		m_pAr->m_xmldoc->createTextNode(_bstr_t(v), &text);
		element->appendChild(text, NULL);
	}
	else
	{
		CComQIPtr<ILDOMAttr> attr = m_node;
		attr->put_value(_bstr_t(v));
	}

	return S_OK;
}

STDMETHODIMP CArchiveElement::getData(VARIANT *pVal)
{
	CComQIPtr<ILDOMElement> element = m_node;
	if (element)
	{
		/*
		CComPtr<IDOMText> text;
		m_pAr->m_xmldoc->createTextNode(_bstr_t(v), &text);
		element->appendChild(text, NULL);
		*/
	}
	else
	{
		CComQIPtr<ILDOMAttr> attr = m_node;

		BSTR b;
		attr->get_value(&b);
		_variant_t v = _bstr_t(b, false);

		*pVal = v;
	}

	return S_OK;
}

STDMETHODIMP CArchiveElement::putObjectMap(BSTR name, IObjectMap *objectmap)
{
	CComObject<CArchiveElement>* node;
	CComObject<CArchiveElement>::CreateInstance(&node);
	if (node)
	{
		node->AddRef();
		node->m_pAr = m_pAr;

		CComPtr<ILDOMElement> element;
		m_pAr->m_xmldoc->createElement(name, &element);
		node->m_node = element;

		node->serializeObjectMap(objectmap);

		m_node->appendChild(element, NULL);

		node->Release();
	}

	return S_OK;
}

STDMETHODIMP CArchiveElement::getObjectMap(BSTR name, IObjectMap *objectmap, IUnknown* pUnkExtra)
{
//	CObjectMap* pMap = static_cast<CObjectMap*>(objectmap);

	CComQIPtr<ILDOMElement> parent = m_node;
	CComQIPtr<ILDOMElement> element = FindByTagName(parent, name, FALSE);
	if (element)
	{
		CComObject<CArchiveElement>* node;
		CComObject<CArchiveElement>::CreateInstance(&node);
		if (node)
		{
			node->AddRef();
			node->m_pAr = m_pAr;
			node->m_node = element;

			node->deserializeObjectMap(objectmap, pUnkExtra);

			node->Release();
		}
	}

	return S_OK;
}

STDMETHODIMP CArchiveElement::serializeObjectMap(IObjectMap *objectmap)
{
	CObjectMap* pMap = static_cast<CObjectMap*>(objectmap);

	for (int i = 0; i < pMap->m_items.GetSize(); i++)
	{
		CComQIPtr<IObjectSerializable> object = pMap->m_items[i];
		if (object)
		{
			putObject(object);
		}
	}

	return S_OK;
}

STDMETHODIMP CArchiveElement::deserializeObjectMap(IObjectMap *objectmap, IUnknown* pUnkExtra)
{
	CObjectMap* pMap = static_cast<CObjectMap*>(objectmap);

	CComQIPtr<ILDOMElement> element = m_node;

	// Read all the children elements
	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			CComObject<CArchiveElement>* pArNode;
			CComObject<CArchiveElement>::CreateInstance(&pArNode);
			if (pArNode)
			{
				pArNode->AddRef();
				pArNode->m_pAr = m_pAr;
				pArNode->m_node = element;

				CComPtr<IUnknown> spUnknown;
				if (SUCCEEDED(pArNode->getObject(pUnkExtra, &spUnknown)))
				{
					pMap->m_items.Add(spUnknown.Detach());
				}

				pArNode->Release();
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CArchive

void CArchive::FinalRelease()
{
	if (m_dwMode == 1)
	{
		VARIANT_BOOL bsaved;
		m_xmldoc->save(m_pathName, &bsaved);
	}
}

/*
void CArchive::MapObject(IDOMElement* element, IUnknown* p)
{
	CMappedObject mapped;
	mapped.m_element = element;
	mapped.m_spUnknown = p;
	mapped.m_id = 0;

	m_writeTable.Add(mapped);
}
*/

/*
CMappedObject* CArchive::LookupObject(IUnknown* p)
{
	for (int i = 0; i < m_writeTable.GetSize(); i++)
	{
		if (IsUnknownEqualUnknown(m_writeTable[i].m_spUnknown, p))
		{
			return &m_writeTable[i];
		}
	}

	return 0;
}
*/

long CArchive::LookupObject(IUnknown* p)
{
	for (int i = 0; i < m_writeTable.GetSize(); i++)
	{
		if (IsUnknownEqualUnknown(m_writeTable[i].m_spUnknown, p))
		{
			return i+1;
		}
	}

	return 0;
}

/*
CMappedObject* CArchive::LookupElement(IDOMElement* p)
{
	for (int i = 0; i < m_writeTable.GetSize(); i++)
	{
		if (IsUnknownEqualUnknown(m_writeTable[i].m_element, p))
		{
			return &m_writeTable[i];
		}
	}

	return 0;
}
*/

STDMETHODIMP CArchive::MapObject(IUnknown *pUnk)
{
//	CComQIPtr<IObjectSerializable> object = pUnk;
//	ATLASSERT(object);

	CMappedObject mapped;
//	mapped.m_element = NULL;
	mapped.m_spUnknown = pUnk;
//	mapped.m_id = 0;

	m_writeTable.Add(mapped);

	return S_OK;
}

STDMETHODIMP CArchive::Open(BSTR pathName, DWORD dwMode, BSTR rootName, IArchiveElement** pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	if (SUCCEEDED(m_xmldoc.CoCreateInstance(CLSID_LDOMDocument)))
	{
		m_dwMode = dwMode;
		m_pathName = pathName;

		if (dwMode == 2)	// Read
		{
			VARIANT_BOOL b;
			m_xmldoc->load(pathName, &b);

			if (b)
			{
				CComObject<CArchiveElement>* node;
				CComObject<CArchiveElement>::CreateInstance(&node);
				node->AddRef();
				node->m_pAr = this;

				CComPtr<ILDOMElement> element;
				m_xmldoc->get_documentElement(&element);
				node->m_node = element;

				*pVal = node;
			}
		}
		else if (dwMode == 1)	// Write
		{
			if (rootName)
			{
				VARIANT_BOOL b;

				m_xmldoc->loadXML(L"<?xml version=\"1.0\" ?><pddoc/>", &b);

				if (true)
				{
					CComObject<CArchiveElement>* node;
					CComObject<CArchiveElement>::CreateInstance(&node);
					node->AddRef();
					node->m_pAr = this;

					CComPtr<ILDOMElement> element;
					m_xmldoc->get_documentElement(&element);
					node->m_node = element;

					*pVal = node;
				}
			}
			else
			{
				VARIANT_BOOL b;

				m_xmldoc->loadXML(L"<?xml version=\"1.0\" ?>", &b);

				if (b)
				{
					CComObject<CArchiveElement>* node;
					CComObject<CArchiveElement>::CreateInstance(&node);
					node->AddRef();
					node->m_pAr = this;

					node->m_node = m_xmldoc;

					*pVal = node;
				}
			}
		}
		else
			ATLASSERT(0);

		return S_OK;
	}

	return E_FAIL;
}
