#include "stdafx.h"
#include "LSVG.h"
#include "SVGAnimationElement.h"

namespace System
{
namespace Web
{

SVGAnimationElement::SVGAnimationElement(PSVGElement* pelement, NamedNodeMap* attributes, CalcModeType calcMode) : SVGElement(pelement, attributes)
{
	m_animateImpl = new ElementAnimate(this, calcMode);
}

bool SVGAnimationElement::dispatchEvent2(Event* evt, bool bCapture)
{
	String type = evt->get_type();

	DOMEventPhaseType phase = evt->get_eventPhase();

	/*
	if (phase == BUBBLING_PHASE)
	{
		if (*type == L"DOMNodeInserted")
		{
			StringW* textContent = get_textContent();

			m_pScript = new ScriptCode;
			m_pScript->AddText(textContent);

			ExecuteScript();
		}
	}
	*/

	if (phase == AT_TARGET)
	{
	// This element is added to the document tree
		if (type == L"DOMNodeInsertedIntoDocument")
		{
			Element* targetElement = dynamic_cast<Element*>(get_parentNode());

			get_ownerDocument()->m_pWindow->m_timelines.push_back(m_animateImpl);

			m_animateImpl->OnSetTargetElement(targetElement);

			get_ownerDocument()->m_animatedElements.push_back(targetElement);

			m_animateImpl->Init();
			m_animateImpl->m_pCurrentInterval = m_animateImpl->GetFirstInterval();

			/*
			StringW* attributeName = m_animateImpl->get_attributeName();

			Attr* attr = targetElement->getAttributeNode(attributeName);
			if (attr)
			{
				attr->m_animations.push_back(m_animateImpl);
			}
			*/

			/*
			StringW* attributeName = m_animateImpl->get_attributeName();

			AnimatedAttr* attr = targetElement->get_animatedAttribute(attributeName);
			if (attr)
			{
				get_ownerDocument()->m_animatedElements.push_back(targetElement);

				attr->m_animations.push_back(m_animateImpl);
			}
			*/

			/*
			LoadStyleSheet();

			if (m_styleSheet)
			{
				DocumentStyleImpl* documentStyle = dynamic_cast<DocumentStyleImpl*>(m_ownerDocument);
				if (documentStyle)
				{
					StyleSheetList* styleSheetList = documentStyle->get_styleSheets();

					styleSheetList->append(m_styleSheet);
				}
			}
			*/
		}
	// This element is removed from the document tree
		else if (type == L"DOMNodeRemovedFromDocument")
		{
			ASSERT(0);
		}
	}

	return EventTarget::dispatchEvent2(evt, bCapture);
}

}
}
