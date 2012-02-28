#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGTRefElement.h"
#include "SVGTRefElement.h"

namespace System
{
namespace Web
{

PSVGTRefElement::PSVGTRefElement(SVGTRefElement* element) : PSVGTextPositioningElement(element)
{
}

/*
//virtual
LDraw::Matrix3d* PSVGTRefElement::GetLocalAnimatedMatrix()
{
	SVGTRefElement* psvgElement = static_cast<SVGTRefElement*>(m_pNode);
	return psvgElement->m_transform->m_animVal->consolidateToMatrix();
}
*/

//virtual
void PSVGTRefElement::CalculateDimensions(CHTMCalcContext* pC)
{
	ASSERT(0);
#if 0
	CLSVGTRefElement* psvgElement = static_cast<CLSVGTRefElement*>(m_pNode);


#if 0	// Had this
	m_pFont = m_pFrame->AddFont(m_computedFontFamily, m_computedFontSize, 0);
#endif

	RemoveChildren();

	_bstr_t href = psvgElement->m_href->m_animated->m_animVal->m_value.m_value;
	if (href.length())
	{
		if (((BSTR)href)[0] == L'#')
		{
			BSTR id = &((BSTR)href)[1];

			CPElement* pPElement = m_pWindow->m_htmTree->GetElementById(id);
			if (pPElement)
			{
				CComQIPtr<ILDOMElement> element = pPElement->m_pNode;

				CComBSTR textContent;
				element->get_textContent(&textContent);

				if (textContent.Length())
				{
					// Not really a text node
					CComObject<CPSVGText>* pText;
					CComObject<CPSVGText>::CreateInstance(&pText);
					pText->AddRef();

					pText->m_parent = this;
					m_childList.AddTail(pText);

					pText->CalculateTextDimensions(pC, textContent, textContent.Length());
				}
			}
		}
	}
#endif
}

}	// w3c
}
