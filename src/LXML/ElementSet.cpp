#include "stdafx.h"
#include "LXML2.h"

#include "AnimationElement.h"

namespace System
{
namespace Web
{

ElementSet::ElementSet(Element* ownerElement) : ElementAnimation(ownerElement)
{
	m_toValue = NULL;
}

void ElementSet::OnSetTargetElement(Element* targetElement)
{
	ASSERT(0);
}

Object* ElementSet::GetValueObject(Object* prevValue, Object* baseValue)
{
	return NULL;
}

void ElementSet::DoAnimationForElementAttr(CATAttr* pAnimatedAttr)
{
	ASSERT(pAnimatedAttr != NULL);

	bool error = false;

	ASSERT(0);
#if 0
	if (m_toValue)
	{
		m_currentValue->CopyFrom(m_toValue);
	}
	else
	{
		error = true;
	}

	CValueType* pAnimVal = pAnimatedAttr->GetAnimVal();

	pAnimVal->CopyFrom(m_currentValue);
#endif
}

void ElementSet::DoAnimationForElement(Element* target)
{
	if (m_animatedAttr)	// XML Attribute
	{
		DoAnimationForElementAttr(m_animatedAttr);
	}
	/*
	else	// CSS Attribute
	{
	// Do animation on all view elements
		for (int i = 0; i < static_cast<T*>(this)->m_pNodes.GetSize(); i++)
		{
			CPAnimateElement* pAnimateElement = (CPAnimateElement*)static_cast<T*>(this)->m_pNodes[i];

			DoAnimationForElement(pAnimateElement->m_pAnimatedCSSAttr); 
		}
	}
	*/
}

}	// w3c
}
