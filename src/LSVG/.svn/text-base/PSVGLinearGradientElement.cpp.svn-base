#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGLinearGradientElement.h"
#include "SVGStopElement.h"
//#include "SVGURIReferenceImpl.h"

#include "SVGLinearGradientElement.h"

double GetLineAngle(double x1, double y1, double x2, double y2);

namespace System
{
namespace Web
{

PSVGLinearGradientElement::PSVGLinearGradientElement(SVGLinearGradientElement* element) : PSVGGradientElement(element)
{
}

//virtual
Gui::Brush* PSVGLinearGradientElement::CreateBrush(PSVGElement* pReferencingElement, double /*scaleX*/, double /*scaleY*/)
{
	SVGLinearGradientElement* psvgElement = static_cast<SVGLinearGradientElement*>(m_pNode);

	vector<float> offsets;
	vector<Graphics::Color> colors;

	CreateGradientStops(offsets, colors);

	if (colors.GetSize() > 0)
	{
		SVGUnitType gradientUnits = GetGradientUnits();

		SVGSpreadMethodType spreadMethod = GetSpreadMethod();

		SVGLength* pLengthX1 = psvgElement->m_x1->m_animVal;
		SVGLength* pLengthY1 = psvgElement->m_y1->m_animVal;
		SVGLength* pLengthX2 = psvgElement->m_x2->m_animVal;
		SVGLength* pLengthY2 = psvgElement->m_y2->m_animVal;

		gm::RectD rect;

	// Get x1,y1,x2,y2
		double x1;
		double y1;
		double x2;
		double y2;

		if (gradientUnits == SVG_UNIT_TYPE_USERSPACEONUSE)
		{
			rect = pReferencingElement->GetViewportElement()->GetViewBox();
			rect.Translate(-rect.X, -rect.Y);	// ??

			if (pLengthX1->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				x1 = (rect.Width * pLengthX1->get_valueInSpecifiedUnits())/100;
			else
				x1 = pLengthX1->get_value();

			if (pLengthY1->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				y1 = (rect.Height * pLengthY1->get_valueInSpecifiedUnits())/100;
			else
				y1 = pLengthY1->get_value();

			if (pLengthX2->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				x2 = (rect.Width * pLengthX2->get_valueInSpecifiedUnits())/100;
			else
				x2 = pLengthX2->get_value();

			if (pLengthY2->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				y2 = (rect.Height * pLengthY2->get_valueInSpecifiedUnits())/100;
			else
				y2 = pLengthY2->get_value();
		}
		else if (gradientUnits == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
		{
		//	rect = pReferencingElement->m_bounds;

			rect.X = 0;
			rect.Y = 0;
			rect.Width = 1;
			rect.Height = 1;

			if (pLengthX1->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				x1 = (1 * pLengthX1->get_valueInSpecifiedUnits())/100;
			else
				x1 = pLengthX1->get_value();

			if (pLengthY1->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				y1 = (1 * pLengthY1->get_valueInSpecifiedUnits())/100;
			else
				y1 = pLengthY1->get_value();

			if (pLengthX2->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				x2 = (1 * pLengthX2->get_valueInSpecifiedUnits())/100;
			else
				x2 = pLengthX2->get_value();

			if (pLengthY2->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				y2 = (1 * pLengthY2->get_valueInSpecifiedUnits())/100;
			else
				y2 = pLengthY2->get_value();
		}
		else
			ASSERT(0);

	// Get transform
		gm::Matrix3d* lmat = psvgElement->m_gradientTransform->m_animVal->consolidateToMatrix();
		//ASSERT(pMatrix);

		gm::vector2d xy1 = lmat->Transform(gm::vector2d(x1, y1));
		gm::vector2d xy2 = lmat->Transform(gm::vector2d(x2, y2));
		x1 = xy1[0];
		y1 = xy1[1];
		x2 = xy2[0];
		y2 = xy2[1];

		/*
		LDraw::Matrix matrix(
			(float)lmat[0][0], (float)lmat[0][1],
			(float)lmat[1][0], (float)lmat[1][1],
			(float)lmat[2][0], (float)lmat[2][1]);
			*/

		//pMatrix->Release();

		if (spreadMethod == SVG_SPREADMETHOD_PAD)
		{
#if 0
			colors.InsertAt(0, colors[0]);
			colors.Add(colors[colors.GetSize()-1]);

			offsets.InsertAt(0, 0.0);
			offsets.Add(1.0);

			double angle = GetLineAngle(x1, y1, x2, y2);

			LDraw::gmMatrix3d mat = LDraw::gmMatrix3d::identity();

			mat = LDraw::gmMatrix3d::translate(-(rect.X + rect.Width/2), -(rect.Y + rect.Height/2)) *
					LDraw::gmMatrix3d::rotate(gmDegrees(angle)) *
					LDraw::gmMatrix3d::translate(rect.X + rect.Width/2, rect.Y + rect.Height/2);
/*
			mat = gmMatrix3::translate(-rect.Width/2, -rect.Height/2) *
					gmMatrix3::rotate(gmDegrees(angle)) *
					gmMatrix3::translate(rect.Width/2, rect.Height/2);
*/
			LDraw::RectD rect2;
			GetTransformRectBoundingBox(mat, rect, &rect2);

			LDraw::PointD pts[4] =
			{
				LDraw::PointD(rect2.X, rect2.Y),
				LDraw::PointD(rect2.X+rect2.Width, rect2.Y),
				LDraw::PointD(rect2.X+rect2.Width, rect2.Y+rect2.Height),
				LDraw::PointD(rect2.X, rect2.Y+rect2.Height),
			};

			gmVector2 xpts[4];

			for (int i = 0; i < 4; i++)
			{
				xpts[i] = mat.transform(pts[i]);
			}

			gm::vector2d v0 = intersection(xpts[0], xpts[3], LDraw::vector2d(x1, y1), LDraw::vector2d(x2, y2));
			gm::vector2d v2 = intersection(xpts[1], xpts[2], LDraw::vector2d(x1, y1), LDraw::vector2d(x2, y2));

			gmVector2 A = gmVector2(x1, y1);
			gmVector2 B = gmVector2(x2, y2);

			{
				LDraw::vector2d P = v0;

				double L2 = (B[0]-A[0])*(B[0]-A[0]) + (B[1]-A[1])*(B[1]-A[1]);
				double t = ((P[0]-A[0])*(B[0]-A[0]) + (P[1]-A[1])*(B[1]-A[1]))/L2;

				if (t > 0)
				{
					v0 = A;
				}
			}

			{
				LDraw::vector2d P = v2;

				double L2 = (B[0]-A[0])*(B[0]-A[0]) + (B[1]-A[1])*(B[1]-A[1]);
				double t = ((P[0]-A[0])*(B[0]-A[0]) + (P[1]-A[1])*(B[1]-A[1]))/L2;

				if (t < 1)
				{
					v2 = B;
				}
			}

			double d0 = LDraw::distance(v0, LDraw::vector2d(x1, y1));
			double d1 = LDraw::distance(LDraw::vector2d(x1, y1), LDraw::vector2d(x2, y2));
			double d2 = LDraw::distance(v2, LDraw::vector2d(x2, y2));
			double d = d0+d1+d2;

			for (i = 1; i < offsets.GetSize()-1; i++)
			{
				offsets[i] = offsets[i]*(d1/d);
				offsets[i] += d0/d;
			}

			x1 = v0[0];
			y1 = v0[1];
			x2 = v2[0];
			y2 = v2[1];
#endif
		}

		if (spreadMethod == SVG_SPREADMETHOD_PAD)
			;
		else if (spreadMethod == SVG_SPREADMETHOD_REFLECT)
			;//pBrush->SetWrapMode(LDraw::WrapModeTileFlipXY);
		else if (spreadMethod == SVG_SPREADMETHOD_REPEAT)
			;//pBrush->SetWrapMode(LDraw::WrapModeTile);
		else
			ASSERT(0);

		if (m_computedColorInterpolation == ColorInterpolation_sRGB)
			;//pBrush->SetGammaCorrection(FALSE);
		else
			;//pBrush->SetGammaCorrection(TRUE);

		if (gradientUnits == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
		{
			/*
			LDraw::Matrix o2u;
			o2u.Translate(pReferencingElement->m_bounds.X, pReferencingElement->m_bounds.Y);
			o2u.Scale(pReferencingElement->m_bounds.Width, pReferencingElement->m_bounds.Height);

			pBrush->MultiplyTransform(&o2u, LDraw::MatrixOrderAppend);
			*/
		}

		//pBrush->MultiplyTransform(&matrix);

		LDraw::GradientStops* stops = new LDraw::GradientStops(LDraw::PixelFormat_t::RGBAP_32);
		stops->SetInterpolationColors(colors.GetData(), offsets.GetData(), colors.GetSize());

	// Create the brush
		LDraw::LinearGradientBrush* pBrush = new LDraw::LinearGradientBrush(stops, x1, y1, x2, y2);

		return pBrush;
	}

	return NULL;
}

}	// w3c
}
