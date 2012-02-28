#include "stdafx.h"
#include "LXML2.h"

#include "AnimationElement.h"

namespace System
{
namespace Web
{

ElementAnimation::ElementAnimation(Element* ownerElement) : ElementTime(ownerElement)
{
	m_fill = FILL_REMOVE;	// TODO, default

	m_reentrance = 0;

	m_bInError = false;

	m_pAttributeType = NULL;
	m_animatedAttr = NULL;

	m_currentValue = NULL;
}

ElementAnimation::~ElementAnimation()
{
	/*
	// TODO, have in FinalRelease()
	if (m_currentValue)
	{
		m_currentValue->m_pListener = NULL;
	//	m_currentValue->Release();
		m_currentValue = NULL;
	}

	ASSERT(m_currentValue == NULL);
	*/
}

Element* ElementAnimation::get_targetElement()
{
	return m_targetElement;
#if 0
// Try targetElement attribute
	CComBSTR targetElement;
	static_cast<T*>(this)->getAttribute(L"targetElement", &targetElement);
	if (targetElement.Length() > 0)
	{
		static_cast<T*>(this)->m_ownerDocument->getElementById(targetElement, pVal);
		if (*pVal) return S_OK;
	}

// Try href:xlink attribute
	CComBSTR href;
	static_cast<T*>(this)->getAttributeNS(WSTR("http://www.w3.org/1999/xlink"), WSTR("href"), &href);
	if (href.Length())
	{
		if (((BSTR)href)[0] == L'#')
		{
			BSTR id = &((BSTR)href)[1];
			static_cast<T*>(this)->m_ownerDocument->getElementById(id, pVal);
			if (*pVal) return S_OK;
		}
	}

// Try parent element
	CComPtr<ILDOMNode> parentNode;
	static_cast<T*>(this)->get_parentNode(&parentNode);

	CComQIPtr<Element, &IID_Element> parentElement((IUnknown*)parentNode);
	*pVal = parentElement.Detach();
	return NULL;
#endif
}

Attr* ElementAnimation::get_xmlAttribute()
{
	return m_xmlAttribute;
}

void ElementAnimation::InactiveToActive()
{
// We shouldn't already be in the sandwich model
//	ASSERT(pAnimationTarget->m_animationList.Find(static_cast<CLElementAnimation*>(this)) == NULL);

// Add to sandwich model (highest priority)
//	pAnimationTarget->m_animationList.push_back(static_cast<CLElementAnimation*>(this));
	m_inlist = m_xmlAttribute->m_animations.insert(m_xmlAttribute->m_animations.end(), this);

#if 0
	CComQIPtr<ILSMILAnimationTarget, &IID_ILSMILAnimationTarget> animationTarget((IUnknown*)targetElement);

	if (animationTarget)
	{
		CAnimationTarget* pAnimationTarget = static_cast<CAnimationTarget*>(animationTarget.p);

	// We shouldn't already be in the sandwich model
		ASSERT(pAnimationTarget->m_animationList.Find(static_cast<CLElementAnimation*>(this)) == NULL);

	// Add to sandwich model (highest priority)
		pAnimationTarget->m_animationList.AddTail(static_cast<CLElementAnimation*>(this));
	}
#endif
}

void ElementAnimation::ActiveToInactive()
{
	if (m_targetElement)
	{
		if (m_fill == FILL_REMOVE)
		{
		// Remove from sandwich model
			m_xmlAttribute->m_animations.erase(m_inlist);
		}
	}
}

}	// w3c
}
