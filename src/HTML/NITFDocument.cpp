#include "stdafx.h"
#include "HTML2.h"
#include "NITFDocument.h"

namespace System
{
namespace Web
{

String NITFDocument::get_title()
{
	ASSERT(0);
#if 0
	if (pVal == NULL) return E_POINTER;

	if (m_documentElement)
	{
		ILDOMElement* head = GetElementByTagName(m_documentElement, L"head", FALSE);
		if (head)
		{
			ILDOMElement* title = GetElementByTagName(head, L"title", FALSE);
			if (title)
			{
				return title->get_textContent(pVal);
			}
		}
	}

#endif
	return NULL;
}

void NITFDocument::set_title(StringIn newVal)
{
	ASSERT(0);
#if 0
	if (m_documentElement)
	{
		CComPtr<ILDOMElement> head = GetElementByTagName(m_documentElement, L"head", FALSE);
		if (head == NULL)
		{
			createElement(L"head", &head);

			if (head)
			{
				CComPtr<ILDOMNode> beforeNode;
				m_documentElement->get_firstChild(&beforeNode);

				m_documentElement->insertBefore(head, CComVariant(beforeNode), NULL);
			}
		}

		if (head)
		{
			CComPtr<ILDOMElement> title = GetElementByTagName(head, L"title", FALSE);
			if (title == NULL)
			{
				createElement(L"title", &title);

				if (title)
				{
					CComPtr<ILDOMNode> beforeNode;
					head->get_firstChild(&beforeNode);

					head->insertBefore(title, CComVariant(beforeNode), NULL);
				}
			}

			if (title)
			{
				return title->set_textContent(newVal);
			}
		}
	}
#endif
}

}	// Web
}
