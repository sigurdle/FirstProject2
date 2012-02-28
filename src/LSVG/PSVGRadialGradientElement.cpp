#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGRadialGradientElement.h"
#include "SVGRadialGradientElement.h"

#include "SVGStopElement.h"

namespace System
{

//namespace Math
//{
double GetLineAngle(double x1, double y1, double x2, double y2);
//}

namespace Web
{

PSVGRadialGradientElement::PSVGRadialGradientElement(SVGRadialGradientElement* element) : PSVGGradientElement(element)
{
}

//virtual
LDraw::Brush* PSVGRadialGradientElement::CreateBrush(PSVGElement* pReferencingElement, double scaleX, double scaleY)
{
	ASSERT(0);
#if 0
	CLSVGRadialGradientElement* psvgElement = static_cast<CLSVGRadialGradientElement*>(m_pNode);

	CArray<float,float> offsets2;
	CArray<LDraw::Color,LDraw::Color> colors2;

	CreateGradientStops(offsets2, colors2);

	if (colors2.GetSize() > 0)
	{
		CArray<LDraw::REAL,LDraw::REAL> offsets;
		CArray<LDraw::Color,LDraw::Color> colors;

		for (int i = 0; i < colors2.GetSize(); i++)
		{
			colors.Add(colors2[colors2.GetSize()-i-1]);
			offsets.Add(1-offsets2[offsets2.GetSize()-i-1]);
		}

		RectD rect;

	// Get spread method
		LSVGSpreadMethodType spreadMethod = psvgElement->m_spreadMethod->m_animated->m_animVal->m_value;

	//
		LSVGUnitType gradientUnits = psvgElement->m_gradientUnits->m_animated->m_animVal->m_value->m_value;

		if (gradientUnits == SVG_UNIT_TYPE_USERSPACEONUSE)
		{
			rect = pReferencingElement->GetViewportElement()->GetViewBox();
			rect.Offset(-rect.X, -rect.Y);	// ??
		}
		else if (gradientUnits == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
		{
			rect = pReferencingElement->m_bounds;
		}
		else
			ASSERT(0);

		double cx;
		double cy;
		double rx;
		double ry;
		double fx;
		double fy;

		CLSVGLength* pLengthCX = psvgElement->m_cx->m_animated->m_animVal->m_value;
		CLSVGLength* pLengthCY = psvgElement->m_cy->m_animated->m_animVal->m_value;
		CLSVGLength* pLengthR = psvgElement->m_r->m_animated->m_animVal->m_value;
		CLSVGLength* pLengthFX = psvgElement->m_fx->m_animated->m_animVal->m_value;
		CLSVGLength* pLengthFY = psvgElement->m_fy->m_animated->m_animVal->m_value;

		if (pLengthCX->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
			cx = rect.X + (rect.Width * pLengthCX->m_valueInSpecifiedUnits)/100;
		else
			cx = pLengthCX->m_value;

		if (pLengthCY->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
			cy = rect.Y + (rect.Height * pLengthCY->m_valueInSpecifiedUnits)/100;
		else
			cy = pLengthCY->m_value;

		if (pLengthR->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
		{
		//	double viewBoxSize = sqrt(rect.Width*rect.Width + rect.Height*rect.Height)/M_SQRT2;
		//	r = (pLengthR->m_valueInSpecifiedUnits * viewBoxSize)/100;
			rx = (rect.Width * pLengthR->m_valueInSpecifiedUnits)/100;
			ry = (rect.Height * pLengthR->m_valueInSpecifiedUnits)/100;
		}
		else
		{
			rx = ry = pLengthR->m_value;
		}

		{
			PointD pts[4] =
			{
				PointD(rect.X, rect.Y),
				PointD(rect.X+rect.Width, rect.Y),
				PointD(rect.X+rect.Width, rect.Y+rect.Height),
				PointD(rect.X, rect.Y+rect.Height),
			};

			int n = -1;
			double nd = 0;

			for (int i = 0; i < 4; i++)
			{
				double d = (pts[i].X - cx)*(pts[i].X - cx) + (pts[i].Y - cy)*(pts[i].Y - cy);
				if (d > nd)
				{
					n = i;
					nd = d;
				}
			}

			double radian = GetLineAngle(cx, cy, pts[n].X, pts[n].Y);

			double px = cos(radian)*rx;
			double py = sin(radian)*ry;

		//	double pd = sqrt(px*px + py*py);

			double dx = fabs(pts[n].X-cx);
			double dy = fabs(pts[n].Y-cy);

			//double d1 = dx/px;

		// New rx,ry

			double m = max(dx/px, dy/py);

			//rx = dx*rx/px;

			rx = m*rx;
			ry = m*ry;
			/*
			}
			else
			{
				double m = dy/py;

				rx = m*rx;
				ry = m*ry;
			}
			*/

			//rx = rx* (nd/pd);
			//ry = ry* (nd/pd);

			/*
			rx = rx * (fabs(px)/fabs(pts[n].X-cx));
			ry = ry * (fabs(py)/fabs(pts[n].Y-cy));
			*/

			if (spreadMethod == SVG_SPREADMETHOD_PAD)
			{
				colors.InsertAt(0, colors[0]/*colors[colors.GetSize()-1]*/);
				//colors.Add(colors[0]);

				offsets.InsertAt(0, 0.0);
				//offsets.Add(1.0);

				//double d0 = distance(v0, gmVector2(x1, y1));
				//double d1 = distance(gmVector2(x1, y1), gmVector2(x2, y2));
				//double d2 = distance(v2, gmVector2(x2, y2));
				//double d = d0+d1+d2;

				for (i = 1; i < offsets.GetSize(); i++)
				{
					if (dx/px > dy/py)
					{
						offsets[i] *= fabs(px)/fabs(dx);
						offsets[i] += (fabs(dx)-fabs(px))/fabs(dx);
					}
					else
					{
						offsets[i] *= fabs(py)/fabs(dy);
						offsets[i] += (fabs(dy)-fabs(py))/fabs(dy);
					}
				}
			}
		}

		bool b;

		psvgElement->hasAttribute(L"fx", &b);
		if (b)
		{
			if (pLengthFX->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
				fx = rect.X + (rect.Width * pLengthFX->m_valueInSpecifiedUnits)/100;
			else
				fx = pLengthFX->m_value;
		}
		else
			fx = cx;

		psvgElement->hasAttribute(L"fy", &b);
		if (b)
		{
			if (pLengthFY->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
				fy = rect.Y + (rect.Height * pLengthFY->m_valueInSpecifiedUnits)/100;
			else
				fy = pLengthFY->m_value;
		}
		else
			fy = cy;

	//
		LDraw::GraphicsPath path;
		path.AddEllipse(float(cx-rx), float(cy-ry), float(rx*2), float(ry*2));

		LDraw::PathGradientBrush* pBrush = new LDraw::PathGradientBrush(&path);

		pBrush->SetCenterPoint(LDraw::PointF(float(fx), float(fy)));

		pBrush->SetInterpolationColors(colors.GetData(), offsets.GetData(), colors.GetSize());
//		pBrush->SetWrapMode(LDraw::WrapModeClamp);

		if (spreadMethod == SVG_SPREADMETHOD_PAD)
			;
		else if (spreadMethod == SVG_SPREADMETHOD_REFLECT)
			pBrush->SetWrapMode(LDraw::WrapModeTileFlipXY);
		else if (spreadMethod == SVG_SPREADMETHOD_REPEAT)
			pBrush->SetWrapMode(LDraw::WrapModeTile);
		else
			ASSERT(0);

		return pBrush;
	}
#endif	
	return NULL;
}

}	// Web
}
