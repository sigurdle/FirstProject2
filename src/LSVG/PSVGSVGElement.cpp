#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGSVGElement.h"
#include "SVGSVGElement.h"

namespace System
{
namespace Web
{

PSVGSVGElement::PSVGSVGElement(SVGSVGElement* element) : PSVGElement(element)
{
// <svg> cannot be transformed, so it's rendering scale is always 1,1
	m_scaleX = 1;
	m_scaleY = 1;
}

//virtual
gm::Matrix3d* PSVGSVGElement::GetLocalAnimatedMatrix()
{
	//SVGSVGElement* psvgElement = static_cast<SVGSVGElement*>(m_pNode);

	/*
	CComObject<CLSVGMatrix>* p;
	CComObject<CLSVGMatrix>::CreateInstance(&p);
	p->AddRef();
	*/
// identity matrix

	return gm::Matrix3d::GetIdentity();

	//return p;
}

#if 0
//virtual
CComObject<CLSVGMatrix>* CPSVGSVGElement::GetGlobalAnimatedMatrix()
{
	SVGSVGElement* psvgElement = static_cast<SVGSVGElement*>(m_pNode);

	CComObject<CLSVGMatrix>* p;
	CComObject<CLSVGMatrix>::CreateInstance(&p);
	p->AddRef();

	if (m_parent)
	{
		CComObject<CLSVGMatrix>* p2 = ((PSVGElement*)m_parent)->GetGlobalAnimatedMatrix2();
		p->m_matrix = p->m_matrix * p2->m_matrix;

		p2->Release();
	}

	return p;
}
#endif

//virtual
void PSVGSVGElement::DistributeWithinBlock(CHTMFlowBlockContext* pC, double parentwidth)
{
	ASSERT(m_parent == NULL);	// top-level <svg>

	CalculateBoundsAndChildren();
}

#if 0
//virtual
void PSVGSVGElement::CalculateBoundsAndChildren()
{
	CalculateBounds();
	PSVGElement::CalculateBoundsAndChildren();
}
#endif

//virtual
void PSVGSVGElement::CalculateBounds()
{
//	PSVGElement::FreeCachedBitmap();

	SVGSVGElement* psvgElement = static_cast<SVGSVGElement*>(m_pNode);

	ISVGLength* xLength = psvgElement->get_x()->get_animVal();
	ISVGLength* yLength = psvgElement->get_y()->get_animVal();
	ISVGLength* widthLength = psvgElement->get_width()->get_animVal();
	ISVGLength* heightLength = psvgElement->get_height()->get_animVal();

// hmm. this isn't called for the root svg

	gm::RectD parentViewBox;

	PSVGElement* pViewportElement = GetViewportElement();
	if (pViewportElement)
	{
		ASSERT(pViewportElement);

		parentViewBox = pViewportElement->GetViewBox();
	}
	else
	{
		CHTMLWindow* pWindow = psvgElement->get_ownerDocument()->m_pWindow;
		if (pWindow)
		{
			parentViewBox = gm::RectD(0, 0, pWindow->m_ownerVisual->get_ActualWidth(), pWindow->m_ownerVisual->get_ActualHeight());
		}
#if 0
		else	// TODO
		{
			if (m_parent)
				parentViewBox = RectD(0, 0, m_parent->m_computedWidth, m_specifiedHeight);
			else
				parentViewBox = RectD(0, 0, 300, 300);

		}
#endif
	}

	if (m_parent != NULL)
	{
		/*
		if (xLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
		{
			m_computedX = (xLength->m_valueInSpecifiedUnits * parentViewBox.Width)/100;
		}
		else
		{
			m_computedX = xLength->m_value;
		}

		if (yLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
		{
			m_computedY = (yLength->m_valueInSpecifiedUnits * parentViewBox.Height)/100;
		}
		else
		{
			m_computedY = yLength->m_value;
		}
		*/
		m_computedX = LengthToUserUnits(xLength, parentViewBox.Width);
		m_computedY = LengthToUserUnits(yLength, parentViewBox.Height);
	}
	else
	{
		m_computedX = 0;
		m_computedY = 0;
	}

	if (true)
	{
		PSVGElement** pos = m_childListRender.begin();
		while (pos != m_childListRender.end())
		{
			PSVGElement* pElement = *pos++;

			pElement->CalculateBoundsAndChildren();
		}
	}

	/*
	if (widthLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedWidth = (widthLength->m_valueInSpecifiedUnits * parentViewBox.Width)/100;
	}
	else
	{
		m_computedWidth = widthLength->m_value;
	}

	if (heightLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedHeight = (heightLength->m_valueInSpecifiedUnits * parentViewBox.Height)/100;
	}
	else
	{
		m_computedHeight = heightLength->m_value;
	}
	*/

	m_computedWidth = LengthToUserUnits(widthLength, parentViewBox.Width);
	m_computedHeight = LengthToUserUnits(heightLength, parentViewBox.Height);

	m_bounds.X = m_computedX;
	m_bounds.Y = m_computedY;
	m_bounds.Width = m_computedWidth;
	m_bounds.Height = m_computedHeight;

	m_xbounds = m_bounds;	// svg doesn't support 'transform' attribute
	// GetTransformRectBoundingBox(matrix, m_bounds, &m_xbounds);

	/*
	GetFilterElement();
	GetMaskElement();
	GetClipPathElement();
	*/

#if 0
	m_filterRect = m_bounds;		// ??
	m_expandedBBox = m_filterRect;	// ??
#endif

	m_viewboxMatrix = CalculateViewBoxMatrix();	// Matrix applied to children

#if 1
	m_expandedBBox = m_bounds;
#else
	if (m_computedOverflowX == Overflow_hidden || m_computedOverflowX == Overflow_scroll)
	{
		m_filterRect = m_bounds;		// ??
		m_expandedBBox = m_filterRect;	// ??
	}
	else
	{

		if (m_pFilterElement)
		{
			m_filterRect = m_pFilterElement->CalculateFilterRegion(this);
		}
		else
		{
			m_filterRect = CalculateRenderableChildrenFilterRect();
		}

		LDraw::GetTransformRectBoundingBox(mat, m_filterRect, &m_filterRect);

		m_expandedBBox = m_filterRect;
	}

	CalculateScale(mat);
#endif
}

// CSS Box model
//virtual
void PSVGSVGElement::CalculateDimensions(CHTMCalcContext* pC)
{
	PElementBase::CalculateDimensions(pC);
	// TODO something here
}

//virtual
void PSVGSVGElement::Draw(CHTMRenderContext* pC)
{
	ASSERT(0);
#if 0
	LDraw::RectF rc = m_pBox->m_innerRect;//GetAbsInnerRect();

	//pC->m_pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 0, 0)), rc);

	pC->m_pGraphics->TranslateTransform(rc.X, rc.Y);
	Render4(pC, NULL, pC->m_rt, 1, 1, false, false);

//	RenderChildren(pC, pC->m_pGraphics, 1, 1);
	pC->m_pGraphics->TranslateTransform(-rc.X, -rc.Y);
#endif
}

//virtual
bool PSVGSVGElement::HasDistributableChildren()
{
	return false;
}

/////////////////////

//virtual
gm::RectD PSVGSVGElement::GetViewBox()
{
	SVGSVGElement* psvgElement = static_cast<SVGSVGElement*>(m_pNode);

// TODO (take viewBox attribute into consideration)
	return m_bounds;
	/*
	return RectD(
		0,
		0,
		psvgElement->m_width->m_animated->m_animVal->m_object->m_value,
		psvgElement->m_height->m_animated->m_animVal->m_object->m_value);
		*/
}

gm::RectD GetViewBoxRect(gm::RectD viewBox, gm::RectD viewPort, SVGPreserveAspectRatioAlignType align, SVGMeetOrSliceType meetOrSlice)
{
	gm::RectD rect;

	if (align == SVG_PRESERVEASPECTRATIO_NONE)
	{
		rect.X = viewBox.X;
		rect.Y = viewBox.Y;
		rect.Width = viewBox.Width;
		rect.Height = viewBox.Height;
	}
	else
	{
		// Preserve aspect ratio

		if (meetOrSlice == SVG_MEETORSLICE_SLICE)
		{
			rect.Width = viewBox.Width;
			rect.Height = (rect.Width*viewPort.Height)/viewPort.Width;

			if (rect.Height < viewBox.Height)
			{
				rect.Height = viewBox.Height;
				rect.Width = (rect.Height*viewPort.Width)/viewPort.Height;
			}
		}
		else if (meetOrSlice == SVG_MEETORSLICE_MEET)
		{
			rect.Width = viewBox.Width;
			rect.Height = (rect.Width*viewPort.Height)/viewPort.Width;

			if (rect.Height > viewBox.Height)
			{
				rect.Height = viewBox.Height;
				rect.Width = (rect.Height*viewPort.Width)/viewPort.Height;
			}
		}
		else
			ASSERT(0);

		switch (align)
		{
		case SVG_PRESERVEASPECTRATIO_XMINYMIN:
		case SVG_PRESERVEASPECTRATIO_XMINYMID:
		case SVG_PRESERVEASPECTRATIO_XMINYMAX:
			{
				rect.X = viewBox.X;
			}
			break;

		case SVG_PRESERVEASPECTRATIO_XMIDYMIN:
		case SVG_PRESERVEASPECTRATIO_XMIDYMID:
		case SVG_PRESERVEASPECTRATIO_XMIDYMAX:
			{
				rect.X = viewBox.X + (viewBox.Width-rect.Width)/2;
			}
			break;

		case SVG_PRESERVEASPECTRATIO_XMAXYMIN:
		case SVG_PRESERVEASPECTRATIO_XMAXYMID:
		case SVG_PRESERVEASPECTRATIO_XMAXYMAX:
			{
				rect.X = viewBox.X + (viewBox.Width-rect.Width);
			}
			break;
		}

		switch (align)
		{
	///////////////////////////////////////////////////
		case SVG_PRESERVEASPECTRATIO_XMINYMIN:
		case SVG_PRESERVEASPECTRATIO_XMIDYMIN:
		case SVG_PRESERVEASPECTRATIO_XMAXYMIN:
			{
				rect.Y = viewBox.Y;
			}
			break;

		case SVG_PRESERVEASPECTRATIO_XMINYMID:
		case SVG_PRESERVEASPECTRATIO_XMIDYMID:
		case SVG_PRESERVEASPECTRATIO_XMAXYMID:
			{
				rect.Y = viewBox.Y + (viewBox.Height-rect.Height)/2;
			}
			break;

	////////////////////////////////////////////////
		case SVG_PRESERVEASPECTRATIO_XMINYMAX:
		case SVG_PRESERVEASPECTRATIO_XMIDYMAX:
		case SVG_PRESERVEASPECTRATIO_XMAXYMAX:
			{
				rect.Y = viewBox.Y + (viewBox.Height-rect.Height);
			}
			break;
		}
	}

	return rect;
}

gm::RectD GetViewBoxRect(gm::RectD viewBox, ISVGPreserveAspectRatio* preserveAspectRatio, LDraw::RectD viewPort)
{
	SVGPreserveAspectRatioAlignType align = preserveAspectRatio->get_align();
	SVGMeetOrSliceType meetOrSlice = preserveAspectRatio->get_meetOrSlice();

	return GetViewBoxRect(viewBox, viewPort, align, meetOrSlice);
}

gm::RectD GetViewBoxRect(SVGRectViewBox* _viewBox, ISVGPreserveAspectRatio* preserveAspectRatio, LDraw::RectD viewPort)
{
	return GetViewBoxRect(gm::RectD(_viewBox->m_x, _viewBox->m_y, _viewBox->m_width, _viewBox->m_height), preserveAspectRatio, viewPort);
}

gm::matrix3d GetViewBoxMatrix(gm::RectD rect, gm::RectD viewPort)
{
	gm::matrix3d mat;// = gmMatrix3::identity();

	mat = gm::matrix3d::getTranslate(rect.X, rect.Y);// * mat;
	mat = gm::matrix3d::getScale(rect.Width/viewPort.Width, rect.Height/viewPort.Height) * mat;

	return mat;
}

// virtual
gm::matrix3f PSVGSVGElement::CalculateViewBoxMatrix()
{
	SVGSVGElement* psvgElement = static_cast<SVGSVGElement*>(m_pNode);

	gm::matrix3f mat;

	if (psvgElement->viewBox_attr().m_attr->get_specified())
	{
		gm::RectD viewBox(m_computedX, m_computedY, m_computedWidth, m_computedHeight);

		gm::RectD viewPort = LDraw::RectD(
			psvgElement->get_viewBox()->get_animVal()->get_x(),
			psvgElement->get_viewBox()->get_animVal()->get_y(),
			psvgElement->get_viewBox()->get_animVal()->get_width(),
			psvgElement->get_viewBox()->get_animVal()->get_height());

		gm::RectD rect = GetViewBoxRect(
			viewBox,
			psvgElement->get_preserveAspectRatio()->get_animVal(),
			viewPort);

		mat = LDraw::matrix3f::getTranslate(-viewPort.X, -viewPort.Y);
		mat = mat * LDraw::matrix3f::getScale(rect.Width/viewPort.Width, rect.Height/viewPort.Height);
		mat = mat * LDraw::matrix3f::getTranslate(rect.X, rect.Y);
	}
	else
	{
		mat = LDraw::matrix3f::getTranslate(m_computedX, m_computedY);
	}

	mat = (mat * LDraw::matrix3f::getScale(psvgElement->m_currentScale, psvgElement->m_currentScale)) * LDraw::matrix3f::getTranslate(psvgElement->m_currentTranslate->m_x, psvgElement->m_currentTranslate->m_y);

	return mat;
}

//virtual
void PSVGSVGElement::RenderSelection(CHTMRenderContext* pC)
{
	ASSERT(0);
#if 0
	/*LDraw::Matrix3f* oldmat =*/ pC->m_pGraphics->PushTransform();

	LDraw::Matrix3d* mat = GetViewBoxMatrix();

	/*
	LDraw::Matrix matrix(
		(float)mat[0][0], (float)mat[0][1],
		(float)mat[1][0], (float)mat[1][1],
		(float)mat[2][0], (float)mat[2][1]);
		*/

	ASSERT(0);
#if 0
	pC->m_pGraphics->MultiplyTransform(mat);
#endif

	RenderSelection2(pC);

	pC->m_pGraphics->PopTransform();//oldmat);
#endif
}

//virtual
void PSVGSVGElement::Render4(CHTMRenderContext* pC, LDraw::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
	SVGSVGElement* psvgElement = static_cast<SVGSVGElement*>(m_pNode);

	//LDraw::Matrix3d* mat = GetViewBoxMatrix();	// Matrix applied to children

	renderContext = renderContext->PushTransform(m_viewboxMatrix);

	RenderChildren(pC, renderContext, scaleX, scaleY);

	return;

#if 0
#if 0
	LDraw::GraphicsState state = pGraphics->Save();
#endif

	if (m_computedOverflowX == Overflow_hidden || m_computedOverflowX == Overflow_scroll)
	{
		LDraw::RectI/*D*/ clipRect;

		clipRect.X = m_bounds.X + m_computedClip[3];
		clipRect.Y = m_bounds.Y + m_computedClip[0];
		clipRect.Width = m_bounds.Width - m_computedClip[1] - m_computedClip[3];
		clipRect.Height = m_bounds.Height - m_computedClip[2] - m_computedClip[0];

		/*
		clipRect.X = 0 + m_computedClip[3];
		clipRect.Y = 0 + m_computedClip[0];
		clipRect.Width = m_bounds.Width - m_computedClip[1] - m_computedClip[3];
		clipRect.Height = m_bounds.Height - m_computedClip[2] - m_computedClip[0];
		*/

		pGraphics->IntersectClip(clipRect);
	}

	LDraw::Matrix3d* mat = GetViewBoxMatrix();

//	LDraw::Matrix gdipMatrix;
//	mat.GetGdipMatrix(gdipMatrix);

	LDraw::Matrix3f* oldMatrixToView;

	// ??
	if (false)
	{
		ASSERT(0);
	#if 0
		pGraphics->MultiplyTransform(mat/*&gdipMatrix*/);
	#endif

		oldMatrixToView = pC->m_matrixToView;
		ASSERT(0);
	#if 0
		pC->m_matrixToView = mat * pC->m_matrixToView;
	#endif
	}

	RenderChildren(pC, pGraphics, scaleX, scaleY);

	if (false)
	{
	#if 0
		pGraphics->Restore(state);
	#endif
		pC->m_matrixToView = oldMatrixToView;
	}
//	PSVGElement::Render4(pC, pBitmap, pGraphics, scaleX, scaleY, bOffscreen, bDrawBehaviors);
#endif
}

}	// Web
}
