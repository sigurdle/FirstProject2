#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGGlyphElement.h"
#include "SVGGlyphElement.h"

namespace System
{
namespace Web
{

PSVGGlyphElement::PSVGGlyphElement(SVGGlyphElement* element) : PSVGElement(element)
{
	m_scaleX = 1;
	m_scaleY = 1;
}

#if 0

//virtual
	void CPSVGGlyphElement::DistributeWithinBlock(LXML::CHTMFlowBlockContext* pC, double parentwidth)
{
	ATLASSERT(NULL);
	ATLASSERT(m_parent == NULL);	// top-level <svg>

	CLSVGGlyphElement* psvgElement = static_cast<CLSVGGlyphElement*>(m_pNode);

#if 0
	CLSVGLength* widthLength = psvgElement->m_width->m_animated->m_animVal->m_value;
	CLSVGLength* heightLength = psvgElement->m_height->m_animated->m_animVal->m_value;

	if (widthLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedWidth = (widthLength->m_valueInSpecifiedUnits * m_specifiedWidth)/100;
	}
	else
	{
		m_computedWidth = widthLength->m_value;
	}

	if (heightLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedHeight = (heightLength->m_valueInSpecifiedUnits * m_specifiedHeight)/100;
	}
	else
	{
		m_computedHeight = heightLength->m_value;
	}

	m_bounds.X = 0;
	m_bounds.Y = 0;
	m_bounds.Width = m_computedWidth;
	m_bounds.Height = m_computedHeight;

	//CalculateBounds();

	/*
// Changed to m_childListRender (not fully tested)
	UPOSITION pos = m_childListRender.GetHeadPosition();
	while (pos)
	{
		PSVGElement* pChildElement = (PSVGElement*)m_childListRender.GetNext(pos);
		pChildElement->CalculateBoundsAndChildren();
	}
	*/
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		PSVGElement* pChildElement = (PSVGElement*)m_childList.GetNext(pos);
		pChildElement->CalculateBoundsAndChildren();
	}

	m_filterRect = m_bounds;		// ??
	m_expandedBBox = m_filterRect;	// ??

	/*
	ChildrenDimensions(pC);

	CalculateBounds();
	*/
#endif
}
#endif

void PSVGGlyphElement::CalculateBounds()
{
	PSVGElement::FreeCachedBitmap();

	m_bounds = CalculateRenderableChildrenBoundingBox();

	if (m_bounds.Width <= 0 || m_bounds.Height <= 0)
	{
		m_bounds.X = 0;
		m_bounds.Y = 0;
		m_bounds.Width = 0;
		m_bounds.Height = 0;
	}
}

#if 0
//virtual
void PSVGGlyphElement::Render4(CHTMRenderContext* pC, Gdiplus::Bitmap* pBitmap, Gdiplus::Graphics* pGraphics, double scaleX, double scaleY, BOOL bOffscreen, BOOL bDrawBehaviors)
{
//	CLSVGSVGElement* svgElement = static_cast<CLSVGSVGElement*>(m_pNode);

	Gdiplus::Matrix oldmat;
	pGraphics->GetTransform(&oldmat);

	/*
	CComObject<CLSVGMatrix>* pMatrix;

	{
		double width = *svgElement->m_width->m_animated->m_animVal->m_object;
		double height = *svgElement->m_height->m_animated->m_animVal->m_object;

		double viewMinX = svgElement->m_viewBox->m_animated->m_animVal->m_object->m_x;
		double viewMinY = svgElement->m_viewBox->m_animated->m_animVal->m_object->m_x;
		double viewWidth = svgElement->m_viewBox->m_animated->m_animVal->m_object->m_width;
		double viewHeight = svgElement->m_viewBox->m_animated->m_animVal->m_object->m_height;

		CComPtr<ILSVGMatrix> mat0;
		mat0.CoCreateInstance(CLSID_LSVGMatrix);

		CComPtr<ILSVGMatrix> mat1;
		mat0->translate(-viewMinX, -viewMinY, &mat1);

		CComPtr<ILSVGMatrix> mat2;
		mat1->scaleNonUniform(width/viewWidth, height/viewHeight, &mat2);

		pMatrix = static_cast<CComObject<CLSVGMatrix>*>(mat2.p);
		pMatrix->AddRef();
		//CComQIPtr<ILSVGMatrix> mat = ;
		//mat2->multiply(matrix, &mat);
	}

  Gdiplus::Matrix matrix(
		(float)pMatrix->m_matrix[0][0], (float)pMatrix->m_matrix[0][1],
		(float)pMatrix->m_matrix[1][0], (float)pMatrix->m_matrix[1][1],
		(float)pMatrix->m_matrix[2][0], (float)pMatrix->m_matrix[2][1]);
	pGraphics->MultiplyTransform(&matrix);
*/
	/*
	UPOSITION pos = m_childListRender.GetHeadPosition();
	while (pos)
	{
		CPSVGElement* pElement = (CPSVGElement*)m_childListRender.GetNext(pos);

		pElement->Render(pGraphics, scaleX, scaleY);//Render(dwBitmap, dwGraphics, scaleX, scaleY);
	}
	*/
	RenderChildren(pC, pGraphics, scaleX, scaleY);

	pGraphics->SetTransform(&oldmat);

//	pMatrix->Release();

	PSVGElement::Render4(pC, pBitmap, pGraphics, scaleX, scaleY, bOffscreen, bDrawBehaviors);
}
#endif

}	// LSVG
}
