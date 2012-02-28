#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGAElement.h"
#include "SVGAElement.h"
#include "PSVGFilterElement.h"

namespace System
{
namespace Web
{

PSVGAElement::PSVGAElement(SVGAElement* element) : PSVGTransformableElement(element)
{
}

/*
//virtual
LDraw::Matrix3d* PSVGAElement::GetLocalAnimatedMatrix()
{
	SVGAElement* pElement = static_cast<SVGAElement*>(m_pNode);
	return pElement->m_transform->m_animVal->consolidateToMatrix();
}
*/

//virtual
void PSVGAElement::CalculateBounds()
{
	PSVGElement::FreeCachedBitmap();

//	SVGAElement* pElement = static_cast<SVGAElement*>(m_pNode);

	LDraw::Matrix3d* matrix = GetLocalAnimatedMatrix();

	m_bounds = CalculateRenderableChildrenBoundingBox();
	LDraw::GetTransformRectBoundingBox(matrix, m_bounds, &m_xbounds);

	GetFillUriElement();
	GetStrokeUriElement();
	GetFilterElement();
	GetMaskElement();
	GetClipPathElement();

	if (m_pFilterElement)
	{
		m_filterRect = m_pFilterElement->CalculateFilterRegion(this);
	}
	else
	{
		m_filterRect = CalculateRenderableChildrenFilterRect();
	}

	m_expandedBBox = m_filterRect;

	CalculateScale(matrix);

#if 0
	ASSERT(0);
	{
		double minx = 9999999;
		double miny = 9999999;
		double maxx = -9999999;
		double maxy = -9999999;

		UPOSITION pos = m_childListRender.GetHeadPosition();
		while (pos)
		{
			PSVGElement* pElement = (PSVGElement*)m_childListRender.GetNext(pos);

			RectD objectExpandedRect = pElement->m_expandedBBox;
		//	object->getExpandedBBox(&objectExpandedRect);

			//CComQIPtr<ILSVGTransformable> objectTransformable = pElement->m_pNode;
			//ATLASSERT(objectTransformable != NULL);

			gmMatrix3 elementMatrix = pElement->GetLocalAnimatedMatrix();
			//if (pElementMatrix)
			{
				RectD objectExpandedRectX;
				GetTransformRectBoundingBox(elementMatrix, objectExpandedRect, &objectExpandedRectX);

				//pElementMatrix->Release();

				minx = min(objectExpandedRectX.X, minx);
				miny = min(objectExpandedRectX.Y, miny);
				maxx = max(objectExpandedRectX.X+objectExpandedRectX.Width, maxx);
				maxy = max(objectExpandedRectX.Y+objectExpandedRectX.Height, maxy);
			}
			//else
			//	ATLASSERT(0);	// hm..
		}

		m_filterRect.X = minx;
		m_filterRect.Y = miny;
		m_filterRect.Width = maxx-minx;
		m_filterRect.Height = maxy-miny;
	}

	LDraw::GetTransformRectBoundingBox(matrix, m_bounds, &m_xbounds);
#endif
}

//virtual
void PSVGAElement::Render4(CHTMRenderContext* pC, LDraw::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
//	pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias/*pGraphics->GetSmoothingMode()*/);

	RenderTextChildren(pC, pBitmap, renderContext, scaleX, scaleY, bOffscreen);

	RenderChildren(pC, renderContext, scaleX, scaleY);

	PSVGElement::Render4(pC, pBitmap, renderContext, scaleX, scaleY, bOffscreen, bDrawBehaviors);
}

}	// Web
}
