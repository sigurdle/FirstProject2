#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGSwitchElement.h"
#include "SVGSwitchElement.h"

namespace System
{
namespace Web
{

PSVGSwitchElement::PSVGSwitchElement(SVGSwitchElement* element) : PSVGTransformableElement(element)
{
	m_pSelectedElement = NULL;
}

#if 0
void CPSVGSwitchElement::SelectElement()
{
	UPOSITION pos = m_childListRender.GetHeadPosition();
	while (pos)
	{
		PSVGElement* pElement = (PSVGElement*)m_childListRender.GetNext(pos);

		CComQIPtr<ILSVGTests> tests = pElement->m_pNode;
		if (tests)
		{
			/*
			CComPtr<ILSVGStringList> requiredFeatures;
			tests->get_requiredFeatures(&requiredEFeatures);
			*/

			CComPtr<ILSVGStringList> requiredExtensions;
			tests->get_requiredExtensions(&requiredExtensions);
			if (!MatchesRequiredExtensions(tests, requiredExtensions))
				continue;

			CComPtr<ILSVGStringList> systemLanguage;
			tests->get_systemLanguage(&systemLanguage);
			if (!MatchesLanguage(tests, systemLanguage))
				continue;

			m_pSelectedElement = pElement;
			return;
		}
	}

	m_pSelectedElement = NULL;
}
#endif

/*
//virtual
LDraw::Matrix3d* PSVGSwitchElement::GetLocalAnimatedMatrix()
{
	SVGSwitchElement* pElement = static_cast<SVGSwitchElement*>(m_pNode);
	return pElement->m_transform->m_animVal->consolidateToMatrix();
}
*/

// virtual
bool PSVGSwitchElement::NeedOffscreenBitmap()
{
	if (PSVGElement::NeedOffscreenBitmap())
		return true;

	if (m_computedOpacity < 1)
		return true;

// If the selected child element has partial opacity, this group must
// create an offscreen bitmap

	if (m_pSelectedElement)
	{
		PSVGElement* pElement = m_pSelectedElement;

		if (pElement->m_computedOpacity > 0 && pElement->m_computedOpacity < 1)
			return true;
	}

	return false;
}

//virtual
gm::RectD PSVGSwitchElement::GetScreenBBox()
{
	SVGSwitchElement* psvgElement = static_cast<SVGSwitchElement*>(m_pNode);

	gm::RectD bbox;
	PSVGElement::GetScreenBBoxFromBounds(m_bounds, &bbox);

	return bbox;
}

//virtual
void PSVGSwitchElement::CalculateBounds()
{
//	PSVGElement::FreeCachedBitmap();

	SVGSwitchElement* psvgElement = static_cast<SVGSwitchElement*>(m_pNode);

	gm::Matrix3d* matrix = GetLocalAnimatedMatrix();

//	SelectElement();
	if (psvgElement->m_selectedElement)
	{
		ASSERT(0);//m_pSelectedElement = (PSVGElement*)CComQIPtr<CLDOMElementImplImpl>(psvgElement->m_selectedElement)->GetNodeOnFrame(m_pView);
	}
	else
	{
		m_pSelectedElement = NULL;
	}

	if (m_pSelectedElement)
	{
		m_bounds = m_pSelectedElement->m_xbounds;
	}
	else
	{
		m_bounds = LDraw::RectD(0, 0, 0, 0);
	}

	LDraw::GetTransformRectBoundingBox(matrix, m_bounds, &m_xbounds);

	ASSERT(0);

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
		double minx = 9999999;
		double miny = 9999999;
		double maxx = -9999999;
		double maxy = -9999999;

		if (m_pSelectedElement)
		{
			gm::RectD objectExpandedRect = m_pSelectedElement->m_expandedBBox;

			gm::Matrix3d* elementMatrix = m_pSelectedElement->GetLocalAnimatedMatrix();
			//if (pElementMatrix)
			{
				gm::RectD objectExpandedRectX;
				gm::GetTransformRectBoundingBox(elementMatrix, objectExpandedRect, &objectExpandedRectX);

				//pElementMatrix->Release();

				minx = MIN(objectExpandedRectX.X, minx);
				miny = MIN(objectExpandedRectX.Y, miny);
				maxx = MAX(objectExpandedRectX.X+objectExpandedRectX.Width, maxx);
				maxy = MAX(objectExpandedRectX.Y+objectExpandedRectX.Height, maxy);
			}
			//else
			//	ASSERT(0);	// hm..
		}

		m_filterRect.X = minx;
		m_filterRect.Y = miny;
		m_filterRect.Width = maxx-minx;
		m_filterRect.Height = maxy-miny;
	}

	m_expandedBBox = m_filterRect;

	CalculateScale(matrix);
}

//virtual
void PSVGSwitchElement::Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
//	pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias/*pGraphics->GetSmoothingMode()*/);

// Only render the selected element of the switch
	if (m_pSelectedElement)
	{
		PSVGElement* pElement = m_pSelectedElement;

		if (pElement->m_computedVisibility == Visibility_visible)
		{
			pElement->Render(pC, renderContext, scaleX, scaleY);//Render(dwBitmap, dwGraphics, scaleX, scaleY);
		}
	}

	PSVGElement::Render4(pC, pBitmap, renderContext, scaleX, scaleY, bOffscreen, bDrawBehaviors);
}

// virtual
PSVGElement* PSVGSwitchElement::HitTestElement(LDraw::Matrix3d* matrix, gm::PointD pt)
{
	matrix = *GetLocalAnimatedMatrix() * *matrix;

// Only hit-test the selected element of the switch
	if (m_pSelectedElement)
	{
		PSVGElement* pHitElement = m_pSelectedElement->HitTestElement(matrix, pt);

		if (pHitElement)
			return pHitElement;
	}

	return NULL;
}

}	// w3c
}
