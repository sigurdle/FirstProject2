#include "stdafx.h"
#include "HTML2.h"
#include "HTMLElement.h"

#include "PHTMLElement.h"

namespace System
{
namespace Web
{

ImmutableString<WCHAR> HTMLElement::s_className_str(L"class");

HTMLElement::HTMLElement(PElementBase* pelement) : Element(pelement)
{
	/*
	m_classAttr = NULL;

	if (false)
	{
		m_classAttr = new Attr;
		m_classAttr->m_ppAttr.set(this, &m_classAttr);
		m_classAttr->set_nodeName(&class_str);
	}
	//m_attributes->setNamedItemNS(m_classAttr);
*/
	UnspecifiedAttr(inner_ptr<Attr*>(this, &m_classAttr), NULL, &s_className_str);
}

HTMLElement::HTMLElement(PElementBase* pelement, NamedNodeMap* attributes) : Element(pelement, attributes)
{
	m_timeContainerImpl = NULL;	// Create on demand

	UnspecifiedAttr(inner_ptr<Attr*>(this, &m_classAttr), NULL, &s_className_str);
}

String HTMLElement::get_className()
{
	return getAttribute(&s_className_str);
}

void HTMLElement::set_className(StringIn newVal)
{
	setAttribute(&s_className_str, newVal);
}

#if 0

STDMETHODIMP CLHTMLElementImplImpl::get_innerText(BSTR *pVal)
{
	_bstr_t innerText;

	CComQIPtr<IDOMNode, &IID_IDOMNode> child;
	get_firstChild(&child);
	while (child != NULL)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);
		if (nodeType == LNODE_ELEMENT)
		{
			CComQIPtr<IMMSXHTMLElement, &IID_IMMSXHTMLElement> element = child;
			BSTR s;
			element->get_innerText(&s);

			innerText += s;
			SysFreeString(s);
		}
		else if (nodeType == LNODE_TEXT)
		{
			CComQIPtr<IDOMText, &IID_IDOMText> text = child;

			BSTR s;
			text->get_data(&s);
			innerText += s;
			SysFreeString(s);
		}

		CComQIPtr<IDOMNode, &IID_IDOMNode> nextchild;
		child->get_nextSibling(&nextchild);
		child = nextchild;
	}

	*pVal = SysAllocString(innerText);

	return S_OK;
}

STDMETHODIMP CMMSXHTMLElement::put_innerText(BSTR newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CMMSXHTMLElement::get_outerHTML(BSTR *pVal)
{
	_bstr_t xml;

	xml += L"<";

	BSTR tagName;
	get_tagName(&tagName);
	xml += tagName;

// Attributes
	CComQIPtr<IDOMNamedNodeMap> attributes;
	get_attributes(&attributes);
	unsigned long length;
	attributes->get_length(&length);

	for (unsigned long i = 0; i < length; i++)
	{
		CComQIPtr<IDOMAttr> attr;
		attributes->item(i, (IDOMNode**)&attr);

		BSTR name;
		attr->get_name(&name);

		BSTR value;
		attr->get_value(&value);

		xml += L" ";
		xml += name;
		xml += L"=";
		xml += L"\"";
		xml += value;
		xml += L"\"";

		SysFreeString(name);
		SysFreeString(value);
	}

	VARIANT_BOOL bHasChildren;
	hasChildNodes(&bHasChildren);

	if (!bHasChildren)
	{
		xml += L"/>";
	}
	else
	{
		xml += L">";

	// Children
		CComQIPtr<IDOMNode> child;
		get_firstChild(&child);

		while (child != NULL)
		{
			LDOMNodeType nodeType;
			child->get_nodeType(&nodeType);

			if (nodeType == LNODE_ELEMENT)
			{
				CComQIPtr<IMMSXHTMLElement> element = child;
				BSTR s;
				element->get_outerHTML(&s);

				xml += s;
				SysFreeString(s);
			}
			else if (nodeType == LNODE_TEXT)
			{
				CComQIPtr<IDOMText> text = child;

				BSTR s;
				text->get_data(&s);
				xml += s;
				SysFreeString(s);
			}

			CComQIPtr<IDOMNode> nextchild;
			child->get_nextSibling(&nextchild);
			child = nextchild;
		}

		xml += L"</";
		xml += tagName;
		xml += L">";
	}

	SysFreeString(tagName);

	*pVal = SysAllocString(xml);

	return S_OK;
}

STDMETHODIMP CMMSXHTMLElement::put_outerHTML(BSTR newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

#endif

}	// Web
}
