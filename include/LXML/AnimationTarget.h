#ifndef __ANIMATIONTARGET_H
#define __ANIMATIONTARGET_H

namespace System
{
namespace Web
{

class NodeList;

class AnimationElementImplImpl;

class WEBEXT AnimationTarget
{
public:
	CTOR AnimationTarget()
	{
	}

	list<AnimationElementImplImpl*> m_animationList;

	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		return Success;
	}

	virtual bool DoAnimation() = 0;

public:
	NodeList* get_animationElements();
};

template <class T> class SMILAnimationTargetImpl : public AnimationTarget
{
public:

	virtual ErrorCode OnBeforeAnimations()
	{
		return Success;
	}

	bool DoAnimation()
	{
		unsigned int i;

		// Set animVal to baseVal on all XML attributes
		for (i = 0; i < static_cast<T*>(this)->m_xmlAttrs.GetSize(); i++)
		{
			CATXMLAttr* pAttr = static_cast<T*>(this)->m_xmlAttrs[i];

			CValueType* pBaseVal = pAttr->GetBaseVal();

			CValueType* pAnimVal = pAttr->GetAnimVal();
			if (pAnimVal)
			{
				pAnimVal->CopyFrom(pBaseVal);
			}
		}

		ASSERT(0);
#if 0
		for (i = 0; i < static_cast<T*>(this)->m_pNodes.GetSize(); i++)
		{
			((CPElement*)static_cast<T*>(this)->m_pNodes[i])->OnResetAnimVals();
		}
#endif
		/*
		for (i = 0; i < static_cast<T*>(this)->m_pNodes.GetSize(); i++)
		{
			CPElement* pPElement = (CPElement*)static_cast<T*>(this)->m_pNodes[i];

			pPElement->SetOverrideStyleToBase();
		}
		*/

	// Run through all animations for this element
		bool bAnyAnimations = false;

		ASSERT(0);
#if 0

		UPOSITION pos = m_animationList.GetHeadPosition();
		while (pos)
		{
			AnimationElementImplImpl* pAnimation = (AnimationElementImplImpl*)m_animationList.GetNext(pos);

			pAnimation->DoAnimationForElement(static_cast<T*>(this));

			bAnyAnimations = true;
		}
#endif

		/*
		if (bAnyAnimations)
		{
			for (int i = 0; i < static_cast<T*>(this)->m_pNodes.GetSize(); i++)
			{
				((CPElement*)static_cast<T*>(this)->m_pNodes[i])->GetCSSProperties();
			}
		//	InvalidateRendering();
		}
		*/

		return bAnyAnimations;
	}

	uint get_animatableXMLAttrsCount()
	{
		return  static_cast<T*>(this)->m_xmlAttrs.GetSize();
	}

	ErrorCode animatableXMLAttrItem(unsigned int index, /*[out, retval]*/ ISMILXMLAttr* *pVal)
	{
		ASSERT(pVal != NULL);
		if (pVal == NULL) throw std::exception("Invalid argument");//return E_POINTER;

		if (index >= 0 && index < static_cast<T*>(this)->m_xmlAttrs.GetSize())
		{
			ASSERT(0);
			*pVal = NULL;//static_cast<T*>(this)->m_xmlAttrs[index];
			//(*pVal)->AddRef();
		}
		else
			*pVal = NULL;

		return Success;
	}

	ErrorCode animatableXMLAttrItemByName(System::StringW* name, /*[out, retval]*/ ISMILXMLAttr* *pVal)
	{
		ASSERT(pVal != NULL);
	//	if (pVal == NULL) return E_POINTER;

		for (unsigned int i = 0; i < static_cast<T*>(this)->m_xmlAttrs.GetSize(); i++)
		{
			if (*static_cast<T*>(this)->m_xmlAttrs[i]->m_attributeName == *name)
			{
				ASSERT(0);
				*pVal = NULL;//static_cast<T*>(this)->m_xmlAttrs[i];
			//	(*pVal)->AddRef();
				return Success;
			}
		}

		*pVal = NULL;

		return Success;
	}
};

}	// w3c
}

#endif // __ANIMATIONTARGET_H
