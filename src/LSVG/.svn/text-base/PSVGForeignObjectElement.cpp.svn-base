#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGForeignObjectElement.h"
#include "SVGForeignObjectElement.h"

namespace System
{
namespace Web
{

PSVGForeignObjectElement::PSVGForeignObjectElement(SVGForeignObjectElement* element) : PSVGTransformableElement(element)
{
}

/*
//virtual
LDraw::Matrix3d* PSVGForeignObjectElement::GetLocalAnimatedMatrix()
{
	SVGForeignObjectElement* psvgElement = static_cast<SVGForeignObjectElement*>(m_pNode);
	return psvgElement->m_transform->m_animVal->consolidateToMatrix();
}
*/

//virtual
void PSVGForeignObjectElement::CalculateBounds()
{
	PSVGElement::FreeCachedBitmap();

	SVGForeignObjectElement* psvgElement = static_cast<SVGForeignObjectElement*>(m_pNode);

	gm::Matrix3d* matrix = GetLocalAnimatedMatrix();

	PSVGElement* pViewportElement = GetViewportElement();
	ASSERT(pViewportElement);

	gm::RectD viewBox = pViewportElement->GetViewBox();

	SVGLength* xLength = psvgElement->m_x->m_animVal;
	SVGLength* yLength = psvgElement->m_y->m_animVal;
	SVGLength* widthLength = psvgElement->m_width->m_animVal;
	SVGLength* heightLength = psvgElement->m_height->m_animVal;

	m_computedX = LengthToUserUnits(xLength, viewBox.Width);
	m_computedY = LengthToUserUnits(yLength, viewBox.Height);
	m_computedWidth = LengthToUserUnits(widthLength, viewBox.Width);
	m_computedHeight = LengthToUserUnits(heightLength, viewBox.Height);

	/*
	if (xLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedX = (xLength->m_valueInSpecifiedUnits * viewBox.Width)/100;
	}
	else
	{
		m_computedX = xLength->m_value;
	}

	if (yLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedY = (yLength->m_valueInSpecifiedUnits * viewBox.Height)/100;
	}
	else
	{
		m_computedY = yLength->m_value;
	}

	if (widthLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedWidth = (widthLength->m_valueInSpecifiedUnits * viewBox.Width)/100;
	}
	else
	{
		m_computedWidth = widthLength->m_value;
	}

	if (heightLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedHeight = (heightLength->m_valueInSpecifiedUnits * viewBox.Height)/100;
	}
	else
	{
		m_computedHeight = heightLength->m_value;
	}
	*/

	m_bounds.X = m_computedX;
	m_bounds.Y = m_computedY;
	m_bounds.Width = m_computedWidth;
	m_bounds.Height = m_computedHeight;

	gm::GetTransformRectBoundingBox(matrix, m_bounds, &m_xbounds);

	m_expandedBBox = m_bounds;

#if 0
	m_filterRect.X = m_bounds.X;
	m_filterRect.Y = m_bounds.Y;
	m_filterRect.Width = m_bounds.Width;
	m_filterRect.Height = m_bounds.Height;

	/*
	CComPtr<ILSVGFilterElement> filter;
	GetFilter(&filter);
	if (filter)
	{
			//m_appearance->SetupChildrenLayers(this);

	//CalculateScale(m_expandedBBox, m_matrix);
	}
	*/

	m_expandedBBox = m_filterRect;//m_appearance->m_expandedRect;

	CalculateScale(/*m_expandedBBox,*/ matrix);
#endif

	//pMatrix->Release();

	/*
	{
		HDC hDC = CreateCompatibleDC(NULL);
		LDraw::Graphics graphics(hDC);

		CHTMCalcContext pC;
		pC.m_pUI = m_pUI;
		pC.m_pGraphics = &graphics;
		pC.m_timeGetCSS = 0;
	//	pC.m_hBrokenImageBitmap = m_hBrokenImageBitmap;
	//		pC.x = pC.y;
	//		pC.maxy = pC.maxx = 0;
		//pC.m_frameClient = m_client;

		pC.m_pStringFormat = LDraw::StringFormat::GenericTypographic();

		graphics.SetTextRenderingHint(LDraw::TextRenderingHintAntiAlias);	// ??

		CalculateDimensions(&pC);

		ATLTRACE("CSS time: %gs\n", pC.m_timeGetCSS/1000.0);

		DeleteDC(hDC);
	}
	*/

	ASSERT(0);

	// TODO, do this in OnLayout() instead

	{
		if (m_pBox)
		{
			CHTMBlockBox* pBox = m_pBox;
			m_pBox = NULL;
			pBox->Release();
		}

		CHTMFlowBlockContext pC;
		//pC.m_frameClient = m_client;

#if 0	// m_specifiedWidth/Height have been removed
		m_specifiedWidth = m_computedWidth;// = cx;
		m_specifiedHeight = m_computedHeight;// = cy;
#endif
//		m_computedOverflowX = Overflow_hidden;
#if 0
		m_computedDisplay = Display_block;	// ??
#endif
	//	m_bVScroll = false;	// Always vertical scrollbar on outer element (TODO unless specified)
/*
		pC.m_pBlockBox = NULL;
		pC.m_pCurLineBox = NULL;
		pC.m_pPrevLeftFloatBox = NULL;

		pC.m_floatBottom = 0;
		pC.m_curpos.X = pC.m_curpos.Y = 0;
		pC.m_linepos.X = pC.m_linepos.Y = 0;
		pC.m_maxx = 0;
*/

		// ??
		PSVGElement::CalculateBoundsAndChildren();

		DistributeWithinBlock(&pC, this/*nearest positioned ancestor*/, this/*stackingContext*/, m_computedWidth);
		//m_pCSSBox = pC.m_pBlockBox;
	}
}

//virtual
void PSVGForeignObjectElement::Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
#if 0
	SVGForeignObjectElement* psvgElement = static_cast<SVGForeignObjectElement*>(m_pNode);

	if (m_pBox)
	{
		CHTMRenderContext pC;

#if 0
		// TODO
		if (m_pWindow)
		{
			// Had this??
			//pC.m_pUI = m_pWindow->m_pUI;
			pC.m_hBrokenImageBitmap = m_pWindow->m_hBrokenImageBitmap;
			pC.m_range = m_pWindow->m_range;
		}
#endif
	//	pC.m_pWindow = m_pWindow;
		pC.m_pGraphics = pGraphics;

	#if 0	// ????TODO, have this
		pC.m_clipBox = //clip;
#endif
		pC.m_clip = LDraw::RectF(0, 0, m_bounds.Width, m_bounds.Height);
		//pC.m_clip.Offset(-m_client.left, -m_client.top);

	#if 0	// ????TODO, have this
		pC.m_clipOrig = pC.m_clip;
	#endif

		pC.m_bInSelection = false;

	//	pC.m_pStringFormat = LDraw::StringFormat::GenericTypographic();

		pC.m_pGraphics->TranslateTransform(float(m_bounds.X), float(m_bounds.Y));

		m_pBox->Draw(&pC);

		pC.m_pGraphics->TranslateTransform(float(-m_bounds.X), float(-m_bounds.Y));
	}
#endif
}

//virtual
bool PSVGForeignObjectElement::HitTest(double x, double y, int pointerEvents)
{
	bool bOver = false;

	if (pointerEvents != PointerEvents_none)
	{
		if (m_bounds.Contains(x, y))
		{
			bOver = true;
		}
	}

	return bOver;
}

// virtual
bool PSVGForeignObjectElement::HitText(gm::matrix3d* matrix, gm::PointD pt, PNode** ppNode, long* poffset)
{
	if (m_pBox)
	{
		//CPNode* pNode = NULL;
		//long offset = -1;

		bool bOver = m_pBox->getPosUnderPoint(pt.X, pt.Y, ppNode, poffset);

		return bOver;
	}

	return false;
}

// virtual
bool PSVGForeignObjectElement::OnButtonDown(gm::PointI point, PElementBase* *pVal)
{
	ASSERT(0);
#if 0
	if (m_pBox)
	{
		CPNode* pNode = NULL;
		long offset = -1;

		BOOL bOver = m_pBox->getPosUnderPoint(point.x, point.y, &pNode, &offset);
		if (bOver)
		{
			m_pWindow->m_initContainer = pNode;
			m_pWindow->m_initOffset = offset;

			m_pWindow->m_curContainer = m_pWindow->m_initContainer;
			m_pWindow->m_curOffset = m_pWindow->m_initOffset;

			m_pWindow->m_range->setStart(m_pWindow->m_initContainer->m_pNode, m_pWindow->m_initOffset);
			m_pWindow->m_range->setEnd(m_pWindow->m_initContainer->m_pNode, m_pWindow->m_initOffset);

			//m_dragging = 1;

#if 0
			m_pWindow->m_pUI->Invalidate();
#endif

			*pVal = this;	// ??
			return 1;
		}
	}
#endif
	return 0;
}

}	// Web
}	// System
