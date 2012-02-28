#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGPathElement.h"
#include "SVGPathElement.h"

#include "../HTML/PathSegListUtils.h"

//void GetPathSegListBBox(ILSVGPathSegList* seglist, gmMatrix3& matrix, RectD* bbox);

namespace System
{
namespace Web
{

PSVGPathElement::PSVGPathElement(SVGPathElement* element) : PSVGShapeElement(element)
{
	m_pGdipGraphicsPathF = NULL;
}

PSVGPathElement::~PSVGPathElement()
{
	if (m_pGdipGraphicsPathF)
	{
		delete m_pGdipGraphicsPathF;
		m_pGdipGraphicsPathF = NULL;
	}
}

/*
//virtual
LDraw::Matrix3d* PSVGPathElement::GetLocalAnimatedMatrix()
{
	SVGPathElement* psvgElement = static_cast<SVGPathElement*>(m_pNode);

	LDraw::Matrix3d* matrix = psvgElement->m_transform->m_animVal->consolidateToMatrix();
	matrix = *matrix * *m_animateMotionMatrix;

	return matrix;
}
*/

//virtual
LDraw::RectD PSVGPathElement::GetScreenBBox()
{
	SVGPathElement* psvgElement = static_cast<SVGPathElement*>(m_pNode);

	gm::RectD bbox;

	SVGPathSegList* seglist = psvgElement->m_d->m_animated->m_animVal->m_value->m_normalizedseglist;

	PSVGElement::GetScreenBBoxFromPath(seglist, &bbox);

	return bbox;
}

// virtual
void PSVGPathElement::RecalculateParentBounds()
{
	ASSERT(0);

#if 0
	UPOSITION pos = m_referencingElements.GetHeadPosition();
	while (pos)
	{
		PSVGElement* pElement = (PSVGElement*)m_referencingElements.GetNext(pos);

	// TODO, have a ReferenceChanged(Element) ??
		pElement->CalculateBoundsAndChildren();
		pElement->RecalculateParentBounds();
	}

	// No need to process up to parent
	PSVGElement::RecalculateParentBounds();
#endif
}

//virtual
void PSVGPathElement::CalculateBounds()
{
	PSVGElement::FreeCachedBitmap();

	if (m_pGdipGraphicsPathF)
	{
		delete m_pGdipGraphicsPathF;
		m_pGdipGraphicsPathF = NULL;
	}

	SVGPathElement* psvgElement = static_cast<SVGPathElement*>(m_pNode);

	gm::Matrix3d* matrix = GetLocalAnimatedMatrix();

//	CComPtr<ILSVGPathSegList> seglist;
//	pElement->get_normalizedPathSegList(&seglist);
	SVGPathSegList* seglist = psvgElement->m_d->m_animated->m_animVal->m_value->m_normalizedseglist;

	if (seglist)
	{
		if (true)
		{
			m_pGdipGraphicsPathF = new LDraw::GraphicsPathF(m_computedFillRule == FillRule_nonzero? LDraw::FillModeWinding: LDraw::FillModeAlternate);

			//LDraw::GraphicsPathF GraphicsPathF;
			DrawPathSegList(seglist, m_pGdipGraphicsPathF, NULL);
		}
		else
		{
		}

		gm::RectF bounds;

		LDraw::Pen pen(LDraw::Color(0,0,0), (float)m_computedStrokeWidth);
		m_pGdipGraphicsPathF/*GraphicsPathF.*/->GetBounds(&bounds, NULL, &pen);

		/*
		if (TRUE)	// Just testing how much faster this is
		{
			m_bounds.X = bounds.X;
			m_bounds.Y = bounds.Y;
			m_bounds.Width = bounds.Width;
			m_bounds.Height = bounds.Height;
			m_xbounds = m_bounds;
		}
		else
		*/
		{
			GetPathSegListBBox(seglist, &m_bounds);
			GetPathSegListBBox(seglist, matrix->m_matrix, &m_xbounds);
		}

		GetFillUriElement();
		GetStrokeUriElement();
		GetFilterElement();
		GetMarkerStartElement();
		GetMarkerEndElement();
		GetMarkerMidElement();
		GetMaskElement();
		GetClipPathElement();

		if (m_pFilterElement)
		{
			m_filterRect = m_pFilterElement->CalculateFilterRegion(this);
		}
		else
		{
			m_filterRect.X = bounds.X;
			m_filterRect.Y = bounds.Y;
			m_filterRect.Width = bounds.Width;
			m_filterRect.Height = bounds.Height;
		}

		if (m_pMaskElement)
		{
			LDraw::RectD maskRegion = m_pMaskElement->CalculateMaskRegion(this);
	
			LDraw::RectD::Intersect(m_expandedBBox, maskRegion, m_filterRect);
		}
		else
		{
			m_expandedBBox = m_filterRect;
		}

		//m_expandedBBox = m_filterRect;//m_appearance->m_expandedRect;

		CalculateScale(/*m_expandedBBox,*/ matrix);
	}

	//pMatrix->Release();
}

double GetLineAngle(double x1, double y1, double x2, double y2);
//PSVGElement* CloneRenderTree(PSVGElement* pParent, PSVGElement* pElement);

//virtual
void PSVGPathElement::Render4(CHTMRenderContext* pC, LDraw::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
	ASSERT(0);
#if 0
	SVGPathElement* psvgElement = static_cast<SVGPathElement*>(m_pNode);

	pGraphics->SetSmoothingMode(LDraw::SmoothingModeHighQuality/*pGraphics->GetSmoothingMode()*/);

	SVGPathSegList* seglist = psvgElement->m_d->m_animated->m_animVal->m_value->m_normalizedseglist;

#if 0

	if (seglist)
#endif
	if (m_pGdipGraphicsPathF)
	{
		//LDraw::GraphicsPathF GraphicsPathF(m_computedFillRule == FillRule_nonzero? LDraw::FillModeWinding: LDraw::FillModeAlternate);
		//DrawPathSegList(seglist, &GraphicsPathF, NULL);

		double fillOpacity = m_computedFillOpacity;
		double strokeOpacity = m_computedStrokeOpacity;

		if (!bOffscreen)
		{
			fillOpacity *= m_computedOpacity;
			strokeOpacity *= m_computedOpacity;
		}

		CManagedBrush pFillBrush = GetFillBrush(fillOpacity, scaleX, scaleY);
		CManagedBrush pStrokeBrush = GetStrokeBrush(strokeOpacity, scaleX, scaleY);

		if (pFillBrush != NULL)
		{
			pGraphics->FillPath(pFillBrush, m_pGdipGraphicsPathF/*&GraphicsPathF*/);
		}

		if (pStrokeBrush != NULL)
		{
			LDraw::Pen* pPen = GetGdipPen(pStrokeBrush);
			if (pPen)
			{
				pGraphics->DrawPath(pPen, m_pGdipGraphicsPathF/*&GraphicsPathF*/);
				delete pPen;
			}
		}

		// Draw markers
		{
			if (m_pMarkerStartElement || m_pMarkerEndElement || m_pMarkerMidElement)
			{
				double tangentIn;
				double tangentOut;

				double x, y;
				double x0, y0;

				CArray<MarkerVertex,MarkerVertex&> vertices;

				int numberOfItems = seglist->m_items.GetSize();

				int istartOfSubPath = 0;
			//	int isubpath = 0;
				for (int i = 0; i < numberOfItems; i++)
				{
					CLSVGPathSegImpl* seg = seglist->m_items[i];

					LSVGPathSegType segType = seg->get_pathSegType();

					if (segType == PATHSEG_MOVETO_ABS)
					{
						CComQIPtr<ILSVGPathSegMovetoAbs> typeseg = seg;
						typeseg->get_x(&x);
						typeseg->get_y(&y);

						istartOfSubPath = i;
					//	isubpath = 0;

						MarkerVertex vertex;
						vertex.x = x;
						vertex.y = y;
						vertex.tangent = 0;	// tangent isn't known at this point
						vertices.Add(vertex);
					}
					else if (segType == PATHSEG_LINETO_ABS)
					{
						CComQIPtr<ILSVGPathSegLinetoAbs> typeseg = seg;
						typeseg->get_x(&x);
						typeseg->get_y(&y);

						tangentIn = GetLineAngle(x0, y0, x, y)*180/M_PI;

					//	isubpath++;

					// Adjust the tangent of previous vertex
						if (i > 0)
						{
							double tangent = (vertices[i-1].tangent + tangentIn)/2;
							vertices[i-1].tangent = tangent;
						}

					// Add new vertex
						MarkerVertex vertex;
						vertex.x = x;
						vertex.y = y;
						vertex.tangent = tangentIn;	// tangentOut isn't yet accounted for
						vertices.Add(vertex);
					}
					else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
					{
						CComQIPtr<ILSVGPathSegCurvetoCubicAbs> typeseg = seg;

						double x1, y1;
						double x2, y2;
						double x3, y3;

						typeseg->get_x(&x3);
						typeseg->get_y(&y3);
						typeseg->get_x1(&x1);
						typeseg->get_y1(&y1);
						typeseg->get_x2(&x2);
						typeseg->get_y2(&y2);

						double t = 1;

						double cx = 3 * (x1 - x0);
						double cy = 3 * (y1 - y0);
						double bx = 3 * (x2 - x1) - cx;
						double by = 3 * (y2 - y1) - cy;
						double ax = x3 - x0 - cx - bx;
						double ay = y3 - y0 - cy - by;

						// Calculate angle
						{
							double dx = ax * 3*t*t + bx * 2*t + cx;
							double dy = ay * 3*t*t + by * 2*t + cy;

							{
								double distance = sqrt(dx*dx + dy*dy);
								double distance2 = distance;

								if (distance2 == 0.0) distance2 = 0.00001;
								if (dy < 0) distance2 =-distance2;
								double angle = acos(dx/distance2);
								if (dy < 0) angle += M_PI;

								tangentIn = angle * 180/M_PI;
							}
						}

						x = x3;
						y = y3;

					// Adjust the tangent of previous vertex
						if (i > 0)
						{
							vertices[i-1].tangent = (vertices[i-1].tangent + tangentIn)/2;
						}

					// Add new vertex
						MarkerVertex vertex;
						vertex.x = x;
						vertex.y = y;
						vertex.tangent = tangentIn;	// tangentOut isn't yet accounted for
						vertices.Add(vertex);
					}
					else if (segType == PATHSEG_CLOSEPATH)
					{
						// Adjust the tangent of the first vertex of the subpath
						vertices[istartOfSubPath].tangent = (vertices[istartOfSubPath].tangent+tangentOut)/2;

						istartOfSubPath = i+1;
					}
					else
						ASSERT(0);

					tangentOut = tangentIn;
					x0 = x;
					y0 = y;
				}

				int count = vertices.GetSize();
				if (count > 0)
				{
					if (m_pMarkerStartElement)
					{
						m_pMarkerStartElement->DrawMarker(pC, pGraphics, this, &vertices[0]);
					}

					if (m_pMarkerMidElement)
					{
						for (int i = 1; i < count-1; i++)
						{
							m_pMarkerMidElement->DrawMarker(pC, pGraphics, this, &vertices[i]);
						}
					}

					if (m_pMarkerEndElement)
					{
						m_pMarkerEndElement->DrawMarker(pC, pGraphics, this, &vertices[count-1]);
					}
				}
			}
		}
	}
#endif
}

//virtual
void PSVGPathElement::RenderPath(Gui::Geometry* pGraphicsPathF)
{
	SVGPathElement* psvgElement = static_cast<SVGPathElement*>(m_pNode);

	SVGPathSegList* seglist = psvgElement->m_d->m_animated->m_animVal->m_value->m_normalizedseglist;

	if (seglist)
	{
		ASSERT(0);
		//DrawPathSegList(seglist, pGraphicsPathF, NULL);
	}
}

//virtual
bool PSVGPathElement::HitTest(double x, double y, int pointerEvents)
{
	SVGPathElement* psvgElement = static_cast<SVGPathElement*>(m_pNode);

	bool bOver = false;
#if 0

	SVGPathSegList* seglist = psvgElement->m_d->m_animated->m_animVal->m_value->m_normalizedseglist;

	if (seglist)
	{
		LDraw::GraphicsPathF GraphicsPathF(m_computedFillRule == FillRule_nonzero? LDraw::FillModeWinding: LDraw::FillModeAlternate);
		DrawPathSegList(seglist, &GraphicsPathF, NULL);

		bOver = HitTestPath(this, &GraphicsPathF, x, y, pointerEvents);
	}
#endif
	return bOver;
}

}	// Web
}	// System
