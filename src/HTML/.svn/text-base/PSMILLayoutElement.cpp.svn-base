#include "stdafx.h"
#include "HTML2.h"

#include "PSMILLayoutElement.h"

#if 0

#include "LSMILRootLayoutElement.h"
#include "LSMILTopLayoutElement.h"

// virtual
void CPSMILLayoutElement::Render(Gdiplus::Graphics* pGraphics, double scaleX, double scaleY)
{
//	CLSMILRegionElement* psmilElement = static_cast<CLSMILRegionElement*>(m_pNode);

	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CPSMILElementImpl* pElement = (CPSMILElementImpl*)m_childList.GetNext(pos);

		pElement->Render(pGraphics, scaleX, scaleY);
	}
}
#endif