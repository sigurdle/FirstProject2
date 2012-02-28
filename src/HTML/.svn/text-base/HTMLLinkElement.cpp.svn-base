#include "stdafx.h"
#include "HTML2.h"
#include "HTMLLinkElement.h"

//#include "PHTMLElement.h"

namespace System
{
namespace Web
{

HTMLLinkElement::HTMLLinkElement(NamedNodeMap* attributes) : HTMLElement(new PHTMLElement(this), attributes)
{
}

bool HTMLLinkElement::dispatchEvent2(Event* evt, bool bCapture)
{
	String type = evt->get_type();

	DOMEventPhaseType phase = evt->get_eventPhase();
	if (phase == AT_TARGET)
	{
	// This element is added to the document tree
		if (type == L"DOMNodeInsertedIntoDocument")
		{
			LoadStyleSheet();

			if (m_styleSheet)
			{
			//	IDocumentStyle* documentStyle = dynamic_cast<DocumentStyleImpl*>(m_ownerDocument);
			//	if (documentStyle)
				{
					StyleSheetList* styleSheetList = m_ownerDocument->get_styleSheets();

					styleSheetList->append(m_styleSheet);
				}
			}
		}
	// This element is removed from the document tree
		else if (type == L"DOMNodeRemovedFromDocument")
		{
			if (m_styleSheet)
			{
				ASSERT(0);
				// TODO remove stylesheet from document
			}
		}
	}

	return EventTarget::dispatchEvent2(evt, bCapture);
}

void HTMLLinkElement::LoadStyleSheet()
{
	String rel = get_rel();

	if (rel.CompareNoCase(L"stylesheet") == 0)
	{
		if (m_styleSheet == NULL)
		{
			m_styleSheet = new CSSStyleSheet(this, NULL/*ownerRule*/);
			if (m_styleSheet)
			{

				/*
				{
					CComQIPtr<INotifySend> cp = m_styleSheet;
					DWORD cookie;
					cp->Advise(this, &cookie);
				}
				*/
			}
		}

		if (m_styleSheet)
		{
			String href = get_href();

			String documentUrl = m_ownerDocument->get_url();

			ASSERT(0);
#if 0
			WCHAR result[2048];
			DWORD resultLenBytes = sizeof(result) - sizeof(result[0]);
#if WIN32
			InternetCombineUrlW(CStringw(documentUrl).c_str(), CStringw(href).c_str(), result, &resultLenBytes, 0);
#else
			ASSERT(0);
#endif

			{
				String media = getAttribute(WSTR("media"));
				m_styleSheet->m_media->set_mediaText(media);
			}

			m_styleSheet->load(string_copy(result));
#endif
		}
	}
	else
	{
		if (m_styleSheet)
		{
			// TODO, remove stylesheet from documents stylesheet list
			m_styleSheet->m_ownerNode = NULL;
			m_styleSheet->m_pListener = NULL;
			delete m_styleSheet;//->Release();
			m_styleSheet = NULL;
		}
	}
}

///////////////////////////

String HTMLLinkElement::get_href()
{
	return getAttribute(WSTR("href"));
}

void HTMLLinkElement::set_href(StringIn newVal)
{
	setAttribute(WSTR("href"), newVal);
	LoadStyleSheet();
}

String HTMLLinkElement::get_rel()
{
	return getAttribute(WSTR("rel"));
}

void HTMLLinkElement::set_rel(StringIn newVal)
{
	ASSERT(0);
}

String HTMLLinkElement::get_type()
{
	return getAttribute(WSTR("type"));
}

void HTMLLinkElement::set_type(StringIn newVal)
{
	ASSERT(0);
}

}	// Web
}
