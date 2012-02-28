#include "stdafx.h"
#include "LXML2.h"

namespace System
{
namespace Web
{

// This version assumes c is a legal hex digit
int Hex2Number(WCHAR c)
{
	ASSERT(isxdigit(c));

	if (c <= '9')
		return c - '0';
	else
		return 10 + tolower(c) - 'a';
}

int strhex2int(const WCHAR* p)
{
	int v = 0;
	while (*p)
	{
		v <<= 4;

		int n = Hex2Number(*p);
		v += n;

		p++;
	}

	return v;
}

}
}

namespace System
{
namespace Web
{

WEBEXT Element* GetElementByTagName(Node* parent, StringIn tagName, bool bDeep/* = TRUE*/)
{
	for (Node* child = parent->get_firstChild(); child != nullptr; child = child->get_nextSibling())
	{
		NodeType nodeType = child->get_nodeType();

		if (nodeType == NODE_ELEMENT)
		{
			Element* element = dynamic_cast<Element*>(child);
			String ttagName = element->get_tagName();

			if (ttagName == tagName)
			{
				return element;
			}

		// Recurse
			if (bDeep)
			{
				Element* element2 = GetElementByTagName(element, tagName, true);
				if (element2 != NULL)
					return element2;
			}
		}
	}

	return nullptr;
}

WEBEXT Element* GetElementByTagNameNS(Node* parent, StringIn ns, StringIn tagName, bool bDeep/* = TRUE*/)
{
	ASSERT(0);
	return nullptr;
#if 0
	CComPtr<ILDOMNode>	child;
	parent->get_firstChild(&child);

	while (child != NULL)
	{
		CComQIPtr<ILDOMElement> element = child;
		if (element)
		{
			CComBSTR ens;
			element->get_namespaceURI(&ens);

			if (!cmpbstr(ens, ns))
			{
				CComBSTR etagName;
				element->get_localName(&etagName);
				if (SysStringLen(etagName) == 0)
				{
					etagName.Empty();
					element->get_tagName(&etagName);
				}

				if (!tcscmp(etagName, tagName))
				{
					return element;
				}
			}

		// Recurse
			if (bDeep)
			{
				CComPtr<ILDOMElement> element2 = GetElementByTagNameNS(element, ns, tagName, TRUE);
				if (element2 != NULL)
					return element2;
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	return NULL;
#endif
}

//void WEBEXT GetElementsByTagNameNSElement(ILDOMElement* element, BSTR namespaceURI, BSTR localName, NodeList *pNodeList);

void WEBEXT GetElementsByTagNameNS(Node* parentNode, StringIn namespaceURI, StringIn localName, NodeList* pNodeList)
{
	Node* child = parentNode->get_firstChild();
	while (child)
	{
		Element* element = dynamic_cast<Element*>(child);
		if (element)
		{
			ASSERT(0);//GetElementsByTagNameNSElement(element, namespaceURI, localName, pNodeList);
		}

		child = child->get_nextSibling();
	}
}

void WEBEXT GetElementsByTagNameNSElement(Element* element, StringIn namespaceURI, StringIn localName, NodeList *pNodeList)
{
	String name = element->get_localName();
	if (name.IsEmpty())
	{
		name = element->get_tagName();
	}

	if (localName == name)
	{
		String ns = element->get_namespaceURI();

		if (namespaceURI == ns)
		{
	//		element->AddRef();
			pNodeList->m_items.Add(element);
		}
	}

// Recurse into children
	GetElementsByTagNameNS(element, namespaceURI, localName, pNodeList);
}

NodeList* GetElementsByTagNameNS(Node* parentNode, StringIn namespaceURI, StringIn localName)
{
	ASSERT(localName != nullptr);
	if (localName == nullptr) raise(ArgumentNullException());

	NodeList* pNodeList = new NodeList;
	Web::GetElementsByTagNameNS(parentNode, namespaceURI, localName, pNodeList);

	return pNodeList;
}

CImage::CImage()
{
	m_loadStatus = 0;
	m_bitmap = nullptr;
	m_refcount = 0;
}

}	// w3c
}
