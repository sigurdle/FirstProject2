#include "stdafx.h"
#include "LSVG2.h"

#include "SVGSymbolElement.h"

namespace System
{
namespace Web
{

//////// ??

//virtual
void SVGSymbolElement::PSVGSymbolElement::CalculateBounds()
{
	PSVGElement::FreeCachedBitmap();

	m_bounds = CalculateRenderableChildrenBoundingBox();

	m_xbounds = m_bounds;
#if 0
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

			CComObject<SVGMatrix>* pElementMatrix = pElement->GetLocalAnimatedMatrix();
			if (pElementMatrix)
			{
				RectD objectExpandedRectX;
				GetTransformRectBoundingBox(pElementMatrix->m_matrix, &objectExpandedRect, &objectExpandedRectX);

				pElementMatrix->Release();

				minx = min(objectExpandedRectX.X, minx);
				miny = min(objectExpandedRectX.Y, miny);
				maxx = max(objectExpandedRectX.X+objectExpandedRectX.Width, maxx);
				maxy = max(objectExpandedRectX.Y+objectExpandedRectX.Height, maxy);
			}
			else
				ATLASSERT(0);	// hm..
		}

		m_filterRect.X = minx;
		m_filterRect.Y = miny;
		m_filterRect.Width = maxx-minx;
		m_filterRect.Height = maxy-miny;
	}
#endif

	m_filterRect = m_bounds;	// ??

	m_expandedBBox = m_filterRect;	// ??
}

//virtual
void SVGSymbolElement::PSVGSymbolElement::Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
	PSVGElement::RenderChildren(pC, renderContext, scaleX, scaleY);
}

}	// Web
}
