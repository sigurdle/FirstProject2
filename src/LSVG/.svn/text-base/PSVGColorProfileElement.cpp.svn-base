#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGColorProfileElement.h"
#include "SVGColorProfileElement.h"

namespace System
{
namespace Web
{

PSVGColorProfileElement::PSVGColorProfileElement(SVGColorProfileElement* element) : PSVGElement(element)
{
}

// Slight Misuse of BuildChildren method
// virtual
void PSVGColorProfileElement::BuildChildren()
{
	SVGColorProfileElement* psvgElement = static_cast<SVGColorProfileElement*>(m_pNode);

	CColorProfile* pColorProfile = psvgElement->GetColorProfile();

	if (pColorProfile)
	{
		ASSERT(0);
#if 0
		m_pWindow->m_colorProfiles.Add(pColorProfile);
#endif
	}

	PSVGElement::BuildChildren();
}

}	// w3c
}
