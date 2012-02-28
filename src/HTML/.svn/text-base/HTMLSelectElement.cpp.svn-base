#include "stdafx.h"
#include "HTML2.h"
#include "HTMLSelectElement.h"

namespace System
{
namespace Web
{

HTMLSelectElement::HTMLSelectElement(NamedNodeMap* attributes) : HTMLElement(new PHTMLElement(this), attributes)
{
}

HTMLSelectElement::~HTMLSelectElement()
{
}

System::StringW* HTMLSelectElement::get_type()
{
	ASSERT(0);
	return NULL;
}

int HTMLSelectElement::get_selectedIndex()
{
	ASSERT(0);
	return 0;
#if 0
	*pVal = -1;

	int index = 0;

	CComPtr<ILDOMNode> child;
	get_firstChild(&child);
	while (child != NULL)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);

		if (nodeType == LNODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement> element = child;

			CComBSTR tagName;
			element->get_tagName(&tagName);
			if (!wcscmp(tagName, L"option"))
			{
				CComPtr<ILDOMAttr> pAttr;
				element->getAttributeNode(L"selected", &pAttr);
				if (pAttr != NULL)
				{
					*pVal = index;
					break;
				}

				index++;
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	return S_OK;
#endif
}

void HTMLSelectElement::set_selectedIndex(int newVal)
{
	int index = 0;
	ASSERT(0);
#if 0
	CComPtr<ILDOMNode> child;
	get_firstChild(&child);
	while (child != NULL)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);

		if (nodeType == LNODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement> element = child;

			CComBSTR tagName;
			element->get_tagName(&tagName);

			if (!wcscmp(tagName, L"option"))
			{
				if (index == newVal)	// Set the selected attribute
				{
					element->setAttribute(L"selected", L"selected");	// ??
				}
				else	// Remove the selected attribute (if any)
				{
					element->removeAttribute(L"selected");
				}

				index++;
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	return S_OK;
#endif
}

System::StringW* HTMLSelectElement::get_value()
{
	ASSERT(0);
	return NULL;
}

void HTMLSelectElement::set_value(System::StringW* newVal)
{
	ASSERT(0);
}

bool HTMLSelectElement::get_multiple()
{
	return hasAttribute(WSTR("multiple"));
}

void HTMLSelectElement::set_multiple(bool newVal)
{
	if (newVal)
	{
		// in XML, all attributes must have values
		setAttribute(WSTR("multiple"), WSTR("multiple"));
	}
	else
	{
		removeAttribute(WSTR("multiple"));
	}
}

int HTMLSelectElement::get_length() const
{
	ASSERT(0);
	return 0;
}

void HTMLSelectElement::set_length(/*[in]*/ int newVal)
{
	THROW(-1);
}

int HTMLSelectElement::get_size()
{
	String size = getAttribute(WSTR("size"));
	if (size.GetLength())
	{
		ASSERT(0);
		//return str2int(size);
		return 0;
	}
	else
		return 0;
}

void HTMLSelectElement::set_size(int newVal)
{
	THROW(-1);
}

void HTMLSelectElement::remove(int index)
{
	THROW(-1);
}

}	// Web
}
