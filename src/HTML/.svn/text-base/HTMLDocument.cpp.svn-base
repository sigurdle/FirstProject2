#include "stdafx.h"
#include "HTML2.h"
#include "HTMLDocument.h"

//#include "HTMLElement.h"

namespace System
{
namespace Web
{

HTMLDocument::HTMLDocument()
{
//	m_viewCSS = new ViewCSS;
//	m_viewCSS->m_document = this;

	m_frames = new HTMLFramesCollection;
}

#if 0
LXML::Element* HTMLDocument::createElementNS(const sysstring& namespaceURI, const sysstring& qualifiedName)
{
	sysstring ns = namespaceURI != NULL? namespaceURI: L"http://www.w3.org/1999/xhtml";

	if (ns == L"http://www.w3.org/1999/xhtml")
	{
		LXML::Element* element;
		if (qualifiedName == L"frameset")
		{
			element = new CLHTMLFrameSetElement;
		}
		else if (qualifiedName == L"frame")
		{
			element = new CLHTMLFrameElement;
		}
		else
		{
			element = new CLHTMLElement;
		}

		element->set_ownerDocument(this);
		element->set_namespaceURI(namespaceURI);
		element->set_nodeName(qualifiedName);

		return element;
	}
	else
		return Document::createElementNS(namespaceURI, qualifiedName);

	return NULL;
#if 0
//	CComQIPtr<ILDOMDocument> document = m_pDocument;
	if (namespaceURI == NULL || wcslen(namespaceURI) == 0)
		return CLDOMDocumentImpl<HTMLDocument>::createElementNS(L"http://www.w3.org/1999/xhtml", qualifiedName, ppElement);
	else
		return CLDOMDocumentImpl<HTMLDocument>::createElementNS(namespaceURI, qualifiedName, ppElement);
#endif
}
#endif

// TODO, use common code for this
void HTMLDocument::Seek(double seconds)
{
	ASSERT(0);
#if 0
	if (m_documentElement)
	{
		CComPtr<ILDOMElement> body = GetElementByTagName(m_documentElement, L"body", FALSE);

	//	m_tau = seconds;
		if (seconds != CComQIPtr<CLElementTimeImplImpl>(body)->m_tau)
		{
			CComQIPtr<CLElementTimeImplImpl>(body)->Seek(seconds);

			//ILSVGElement* svgElement = this;//reinterpret_cast<ISVGElement*>(this/*GetControllingUnknown()*/);
			bool bAny = DoAnimationsForAllElements(body, /*m_currentTimeSeconds,*/ seconds);

			//if (bAny)
			{
			// TODO, fix up here
				//CComQIPtr<CLDOMDocumentImplImpl> pDocument(m_ownerDocument);

				for (int n = 0; n < /*pDocument->*/m_pViews.GetSize(); n++)
				{
					ASSERT(0);
#if 0
					m_pViews[n]->m_htmTree->GetCSSPropertiesAndChildren();
					m_pViews[n]->Flow();

					if (m_pViews[n]->m_pUI)
					{
						m_pViews[n]->m_pUI->InvalidateRect(
							&m_pViews[n]->m_client, FALSE);
					}
#endif
				}
			}
		}
	}
#endif
}

void HTMLDocument::seekElement(double seekTo)
{
	Seek(seekTo/1000);
}

String HTMLDocument::get_title()
{
	ASSERT(0);
	return NULL;
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

	*pVal = NULL;

	return S_OK;
#endif
}

void HTMLDocument::set_title(StringIn newVal)
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

				m_documentElement->insertBefore(head, _variant_t(beforeNode), NULL);
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

					head->insertBefore(title, _variant_t(beforeNode), NULL);
				}
			}

			if (title)
			{
				return title->set_textContent(newVal);
			}
		}
	}

	return S_OK;
#endif
}

HTMLElement* HTMLDocument::get_body()
{
	ASSERT(0);
#if 0
	if (m_documentElement)
	{
		LXML::Element* body = LXML::GetElementByTagName(m_documentElement, L"body", false);
		if (body)
		{
			return dynamic_cast<CLHTMLElementImpl*>(body);
		}
		else
		{
			Element* frameset = GetElementByTagName(m_documentElement, L"frameset", false);
			if (frameset)
			{
				return dynamic_cast<CLHTMLElementImpl*>(frameset);
			}
		}
	}
#endif
	return NULL;
}

static ImmutableString<WCHAR> namespaceURI(WSTR("http://www.w3.org/1999/xhtml"));

String HTMLDocument::get_namespaceURI()
{
	return &namespaceURI;
}

}	// Web
}
