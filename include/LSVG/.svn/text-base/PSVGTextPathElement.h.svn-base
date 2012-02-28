#ifndef w3c_PSVGTextPathElement_h
#define w3c_PSVGTextPathElement_h

#include "PSVGTextContentElement.h"

namespace System
{
namespace Web
{

//class SVGPathSegList;

class SVGEXT PSVGTextPathElement : public PSVGTextContentElement
{
public:
	CTOR PSVGTextPathElement(SVGTextPathElement* element);

	~PSVGTextPathElement()
	{
		if (m_pPathElement)
		{
			ASSERT(0);
#if 0
			UPOSITION pos = m_pPathElement->m_referencingElements.Find(this);
			ASSERT(pos);
			m_pPathElement->m_referencingElements.RemoveAt(pos);

			m_pPathElement = NULL;
#endif
		}
	}

	PSVGElement* m_pPathElement;

	PSVGElement* GetHrefPathElement();

	void AlignToPath(PSVGTextContentElement* pElement, SVGPathSegList* pSegList);

	virtual void LayoutText(TextLayoutContext* tlc, bool bDoX, bool bDoY);

	//virtual LDraw::Matrix3d* GetLocalAnimatedMatrix();

	void CalculateBounds();

	/*
	virtual void CalculateBoundsAndChildren()
	{
		CalculateBounds();
	}
	*/

	virtual void ReferenceInvalid(PElementBase/*PSVGElement*/ * pPElement);
};

}	// w3c
}

#endif // __Web_PSVGTextPathElement_h__
