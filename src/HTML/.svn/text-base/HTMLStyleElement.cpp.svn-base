#include "stdafx.h"
#include "HTML2.h"
#include "HTMLStyleElement.h"
#include "PHTMLElement.h"

namespace System
{
namespace Web
{

HTMLStyleElement::HTMLStyleElement(NamedNodeMap* attributes) : HTMLElement(new PHTMLElement(this), attributes), LinkStyleStyleImpl(this)
{
	m_typeAttr = NULL;
	m_mediaAttr = NULL;

	if (false)
	{
		m_typeAttr = new Attr;
		m_typeAttr->m_ppAttr.set(this, &m_typeAttr);
		m_typeAttr->set_nodeName(WSTR("type"));

		m_mediaAttr = new Attr;
		m_mediaAttr->m_ppAttr.set(this, &m_mediaAttr);
		m_mediaAttr->set_nodeName(WSTR("media"));

		m_attributes->setNamedItemNS(m_typeAttr);
		m_attributes->setNamedItemNS(m_mediaAttr);
	}
}

bool HTMLStyleElement::get_disabled() const
{
	return m_styleSheet->get_disabled();
}

void HTMLStyleElement::set_disabled(bool newVal)
{
	m_styleSheet->set_disabled(newVal);
}

String HTMLStyleElement::get_type()
{
	return getAttribute(WSTR("type"));
}

void HTMLStyleElement::set_type(StringIn newVal)
{
	setAttribute(WSTR("type"), newVal);
}

String HTMLStyleElement::get_media()
{
	return getAttribute(WSTR("media"));
}

void HTMLStyleElement::set_media(StringIn newVal)
{
	setAttribute(WSTR("media"), newVal);
}

CSSStyleSheet* HTMLStyleElement::get_styleSheet()
{
	return get_sheet();
}

void HTMLStyleElement::OnChanged()
{
	if (m_cssreentrancy == 0)
	{
		m_cssreentrancy++;

		// TODO don't always do this
		{
			String media = getAttribute(WSTR("media"));
			m_styleSheet->get_media()->set_mediaText(media);
		}

	// If the textnode's text changed, update the stylesheet
		{
		// The first text child contains the source of the stylesheet
		//	CComPtr<ILDOMNode> firstchild;
		//	get_firstChild(&firstchild);
		//	CComQIPtr<ILDOMCharacterData> chardata = firstchild;
		//	if (chardata)
			{
				String data = get_textContent();

				m_styleSheet->set_cssText(data);
			}
		}

		m_cssreentrancy--;
	}
}

// EventTarget
bool HTMLStyleElement::dispatchEvent2(Event* evt, bool bCapture)
{
	String type = evt->get_type();

	DOMEventPhaseType phase = evt->get_eventPhase();

	if (phase == BUBBLING_PHASE)
	{
		if (type == L"DOMNodeInserted")
		{
			OnChanged();
		}
	}

	if (phase == AT_TARGET)
	{
		if (type == L"DOMNodeInsertedIntoDocument")
		{
			if (m_styleSheet)
			{
			//	DocumentStyleImpl* documentStyle = dynamic_cast<DocumentStyleImpl*>(m_ownerDocument);
			//	if (documentStyle)
			//	{
				StyleSheetList* styleSheetList = m_ownerDocument->get_styleSheets();

				ASSERT(0);
				//	styleSheetList->append(m_styleSheet);
			//	}
			}
		}
		else if (type == L"DOMNodeRemovedFromDocument")
		{
			ASSERT(0);
		}
	}

	return CLDOMEventTargetImpl::dispatchEvent2(evt, bCapture);
}

}	// Web
}
