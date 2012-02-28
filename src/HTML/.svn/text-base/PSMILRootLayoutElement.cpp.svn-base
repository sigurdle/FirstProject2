#include "stdafx.h"
#include "HTML2.h"

#include "PSMILRootLayoutElement.h"

#include "SMILRootLayoutElement.h"

#include "PSMILRegionElement.h"

namespace System
{
namespace Web
{

void SortRegions(vector<PSMILRegionElement*>& regions, PSMILElement* parent)
{
	ASSERT(0);
#if 0
	UPOSITION pos = parent->m_childList.GetHeadPosition();
	while (pos)
	{
		CPSMILElementImpl* pElement = (CPSMILElementImpl*)parent->m_childList.GetNext(pos);

		CComQIPtr<ILSMILRegionElement> region = pElement->m_pNode;
		if (region)
		{
			CPSMILRegionElement* pRegionElement = (CPSMILRegionElement*)pElement;

			CComBSTR bstrZIndex;
			region->getAttribute(L"z-index", &bstrZIndex);
			if (bstrZIndex.Length())
			{
				pRegionElement->m_computedZIndex = (long)_variant_t(bstrZIndex);
			}
			else
			{
				pRegionElement->m_computedZIndex = 0;	// ? that of parent
			}

		// Insert sorted
			for (int i = 0; i < regions.GetSize(); i++)
			{
				if (pRegionElement->m_computedZIndex < regions[i]->m_computedZIndex)
				{
					//regions.InsertAt(i, pRegionElement);
					break;
				}
			/*
				the rule concerning time priority is maintained, meaning that in the case
				of a z-index conflict, the media visible in the overlap will be determined
				by the region that is rendering the media that has most recently begun in
				time. If the conflicting media began at the same time, then the rule using
				the textual order of the media elements in the SMIL document is applied
				*/
				else if (pRegionElement->m_computedZIndex == regions[i]->m_computedZIndex)
				{
					//static_cast<SMILRegionElement*>(region.p)->m_p
				}
			}

			regions.InsertAt(i, pRegionElement);
		}
	}
#endif
}

// virtual
void PSMILRootLayoutElement::Render(Graphics::Bitmap* pBgBitmap, Gui::ManagedRetainedRenderContext, double scaleX, double scaleY)
{
	SMILRootLayoutElement* psmilElement = static_cast<SMILRootLayoutElement*>(m_pNode);

	m_computedWidth = psmilElement->m_width->m_animated->m_animVal->m_value->m_value;
	m_computedHeight = psmilElement->m_height->m_animated->m_animVal->m_value->m_value;

// hm.. set it on <layout>, since the regions are children of that, instead
// of children of this <root-layout>

	m_parent->m_computedWidth = m_computedWidth;
	m_parent->m_computedHeight = m_computedHeight;

	gm::RectI rgnRect(
		(int)0,
		(int)0,
		(int)m_computedWidth,
		(int)m_computedHeight);

	ASSERT(0);
#if 0
	pGraphics->FillRectangle(
		new LDraw::SolidBrush(
		LDraw::Color(
			psmilElement->m_backgroundColor->m_animated->m_animVal->m_value->m_alpha,
			psmilElement->m_backgroundColor->m_animated->m_animVal->m_value->ClampRed(),
			psmilElement->m_backgroundColor->m_animated->m_animVal->m_value->ClampGreen(),
			psmilElement->m_backgroundColor->m_animated->m_animVal->m_value->ClampBlue())),

		rgnRect);

// Draw sibling regions
	vector<PSMILRegionElement*> regions;

	SortRegions(regions, (PSMILElement*)m_parent);

	for (int i = 0; i < regions.GetSize(); i++)
	{
		regions[i]->Render(pBgBitmap, pGraphics, scaleX, scaleY);
	}

	/*
	UPOSITION pos = m_parent->m_childList.GetHeadPosition();
	while (pos)
	{
		CPSMILElementImpl* pElement = (CPSMILElementImpl*)m_parent->m_childList.GetNext(pos);

		CComQIPtr<ILSMILRegionElement> region = pElement->m_pNode;
		if (region)
		{
			pElement->Render(pGraphics, scaleX, scaleY);
		}
	}
	*/

	bool bDrawBehaviors = true;

	if (bDrawBehaviors)
	{
	//	RenderBehavior(pGraphics);
	}
#endif
}

}	// Web
}

#if 0
void CPElement::RenderBehavior(Gdiplus::Graphics* pGraphics)
{
	for (int i = 0; i < m_behaviors.GetSize(); i++)
	{
		CComQIPtr<IHTMLPainter> htmlPainter = m_behaviors[i]->m_p;

		if (htmlPainter)
		{
			CRect rcBounds(0, 0, 400, 400);	// TODO
			CRect rcUpdate(0, 0, 400, 400);	// TODO

			long lDrawFlags = 0;	// HTMLPAINT_DRAW_UPDATEREGION = 0x000001,
								  //  HTMLPAINT_DRAW_USE_XFORM = 0x000002

			HDC hDC = pGraphics->GetHDC();
	
			//CPoint oldOrg;
			//OffsetViewportOrgEx(hDC, -pC->m_clipBox.left, -pC->m_clipBox.top, &oldOrg);

			htmlPainter->Draw(rcBounds, rcUpdate, lDrawFlags, hDC, NULL);

			//SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

			pGraphics->ReleaseHDC(hDC);
		}
	}
}
#endif
