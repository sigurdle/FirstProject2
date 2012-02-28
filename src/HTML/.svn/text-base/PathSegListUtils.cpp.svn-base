#include "stdafx.h"
#include "HTML2.h"
#include "PathSegListUtils.h"
#include "SVGPathSegList.h"

#include "SVGPathSegMovetoAbs.h"
#include "SVGPathSegMovetoRel.h"
#include "SVGPathSegLinetoRel.h"
#include "SVGPathSegLinetoAbs.h"
#include "SVGPathSegCurvetoCubicAbs.h"
#include "SVGPathSegCurvetoCubicRel.h"
#include "SVGPathSegCurvetoQuadraticAbs.h"
#include "SVGPathSegCurvetoQuadraticRel.h"
#include "SVGPathSegCurvetoCubicSmoothAbs.h"
#include "SVGPathSegCurvetoCubicSmoothRel.h"
#include "SVGPathSegCurvetoQuadraticSmoothAbs.h"
#include "SVGPathSegCurvetoQuadraticSmoothRel.h"
#include "SVGPathSegLinetoHorizontalAbs.h"
#include "SVGPathSegLinetoHorizontalRel.h"
#include "SVGPathSegLinetoVerticalAbs.h"
#include "SVGPathSegLinetoVerticalRel.h"
#include "SVGPathSegArcAbs.h"
#include "SVGPathSegArcRel.h"
#include "SVGPathSegClosePath.h"

namespace System
{

namespace gm
{
void CalcCurveBBox(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double mx[4]);
void CalcCurveBBox(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, const matrix3f& matrix, double mx[4]);

inline void CalcCurveBBox(const vector2d& P0, const vector2d& P1, const vector2d& P2, const vector2d& P3, double mx[4])
{
	CalcCurveBBox(P0[0], P0[1], P1[0], P1[1], P2[0], P2[1], P3[0], P3[1], mx);
}

void CalcCurveBBox(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double mx[4])
{
	double ax, ay, bx, by, cx, cy;

	cx = 3 * (x1 - x0);
	cy = 3 * (y1 - y0);
	bx = 3 * (x2 - x1) - cx;
	by = 3 * (y2 - y1) - cy;
	ax = x3 - x0 - cx - bx;
	ay = y3 - y0 - cy - by;

	double sqrtx = sqrt(4*bx*bx - 4*3*ax*cx);
	double sqrty = sqrt(4*by*by - 4*3*ay*cy);

//	if (fabs(2*3*ax) < 0.000001) throw -1;
//	if (fabs(2*3*ax) < 0.000001) throw -1;

	double tx1 = (-2*bx + sqrtx) / (2*3*ax);
	double tx2 = (-2*bx - sqrtx) / (2*3*ax);
	double ty1 = (-2*by + sqrty) / (2*3*ay);
	double ty2 = (-2*by - sqrty) / (2*3*ay);

	if (tx1 >= 0 && tx1 <= 1)
	{
		double xt1 = ax * tx1*tx1*tx1 + bx * tx1*tx1 + cx * tx1 + x0;

		mx[0] = MIN(mx[0], xt1);
		mx[2] = MAX(mx[2], xt1);
	}

	if (tx2 >= 0 && tx2 <= 1)
	{
		double xt2 = ax * tx2*tx2*tx2 + bx * tx2*tx2 + cx * tx2 + x0;

		mx[0] = MIN(mx[0], xt2);
		mx[2] = MAX(mx[2], xt2);
	}

	if (ty1 >= 0 && ty1 <= 1)
	{
		double yt1 = ay * ty1*ty1*ty1 + by * ty1*ty1 + cy * ty1 + y0;

		mx[1] = MIN(mx[1], yt1);
		mx[3] = MAX(mx[3], yt1);
	}

	if (ty2 >= 0 && ty2 <= 1)
	{
		double yt2 = ay * ty2*ty2*ty2 + by * ty2*ty2 + cy * ty2 + y0;

		mx[1] = MIN(mx[1], yt2);
		mx[3] = MAX(mx[3], yt2);
	}

	mx[0] = MIN(mx[0], MIN(x0, x3));
	mx[1] = MIN(mx[1], MIN(y0, y3));
	mx[2] = MAX(mx[2], MAX(x0, x3));
	mx[3] = MAX(mx[3], MAX(y0, y3));

#if 0
//	double tinc = 1/200.0;

	for (int i = 0; i <= 200; i++)
	{
		double t = i / 200.0;

		double xt = ax * t*t*t + bx * t*t + cx * t + x0;
		double yt = ay * t*t*t + by * t*t + cy * t + y0;

		if (xt < mx[0]) mx[0] = xt;
		if (yt < mx[1]) mx[1] = yt;
		if (xt > mx[2]) mx[2] = xt;
		if (yt > mx[3]) mx[3] = yt;
	}
#endif
}

void CalcCurveBBox(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, const matrix3f& matrix, double mx[4])
{
	CalcCurveBBox(
		matrix.transform(vector2d(x0,y0)),
		matrix.transform(vector2d(x1,y1)),
		matrix.transform(vector2d(x2,y2)),
		matrix.transform(vector2d(x3,y3)),
		mx);
}

}

namespace Web
{

HTMLEXT void GetPathSegListBBox(SVGPathSegList* seglist, const gm::matrix3d& mat, gm::RectD* bbox)
{
	double mx[4] =
	{
		9999999, 9999999,		// minx / miny
		-9999999, -9999999,		// maxx / maxy
	};

	double oldx = 0;
	double oldy = 0;

	uint numberOfItems = seglist->get_numberOfItems();
	for (uint i = 0; i < numberOfItems; i++)
	{
		SVGPathSeg* seg = seglist->getItem(i);

		SVGPathSegType segType = seg->get_pathSegType();
		if (segType == PATHSEG_MOVETO_ABS)
		{
			SVGPathSegMovetoAbs* movetoabs = static_cast<SVGPathSegMovetoAbs*>(seg);

			oldx = movetoabs->get_x();
			oldy = movetoabs->get_y();

			//if (matrix)
			{
				gm::vector2d pt(oldx, oldy);
				gm::vector2d xpt = mat.transform(pt);

				oldx = xpt[0];
				oldy = xpt[1];
			}
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			SVGPathSegLinetoAbs* linetoabs = static_cast<SVGPathSegLinetoAbs*>(seg);

			double x = linetoabs->get_x();
			double y = linetoabs->get_y();

			//if (matrix)
			{
				gm::vector2d pt(x, y);
				gm::vector2d xpt = mat.transform(pt);

				x = xpt[0];
				y = xpt[1];
			}

			if (oldx < mx[0]) mx[0] = oldx;
			if (oldy < mx[1]) mx[1] = oldy;
			if (oldx > mx[2]) mx[2] = oldx;
			if (oldy > mx[3]) mx[3] = oldy;

			if (x < mx[0]) mx[0] = x;
			if (y < mx[1]) mx[1] = y;
			if (x > mx[2]) mx[2] = x;
			if (y > mx[3]) mx[3] = y;

			oldx = x;
			oldy = y;
		}
		else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			SVGPathSegCurvetoCubicAbs* cubictoabs = static_cast<SVGPathSegCurvetoCubicAbs*>(seg);

			double x = cubictoabs->get_x();
			double y = cubictoabs->get_y();
			double x1 = cubictoabs->get_x1();
			double y1 = cubictoabs->get_y1();
			double x2 = cubictoabs->get_x2();
			double y2 = cubictoabs->get_y2();

			//if (matrix)
			{
				{
					gm::vector2d pt(x, y);
					gm::vector2d xpt = mat.transform(pt);

					x = xpt[0];
					y = xpt[1];
				}
				{
					gm::vector2d pt(x1, y1);
					gm::vector2d xpt = mat.transform(pt);

					x1 = xpt[0];
					y1 = xpt[1];
				}
				{
					gm::vector2d pt(x2, y2);
					gm::vector2d xpt = mat.transform(pt);

					x2 = xpt[0];
					y2 = xpt[1];
				}
			}

			gm::CalcCurveBBox(oldx, oldy, x1, y1, x2, y2, x, y, mx);

			oldx = x;
			oldy = y;
		}
	}

	bbox->X = mx[0];
	bbox->Y = mx[1];
	bbox->Width = mx[2]-mx[0];//+1;
	bbox->Height = mx[3]-mx[1];//+1;
}

HTMLEXT void GetPathSegListBBox(SVGPathSegList* seglist, gm::Matrix3f mat, gm::RectD* bbox)
{
	double mx[4] =
	{
		9999999, 9999999,		// minx / miny
		-9999999, -9999999,		// maxx / maxy
	};

	double oldx = 0;
	double oldy = 0;

	uint numberOfItems = seglist->get_numberOfItems();
	for (uint i = 0; i < numberOfItems; i++)
	{
		SVGPathSeg* seg = seglist->getItem(i);

		SVGPathSegType segType = seg->get_pathSegType();
		if (segType == PATHSEG_MOVETO_ABS)
		{
			SVGPathSegMovetoAbs* movetoabs = static_cast<SVGPathSegMovetoAbs*>(seg);

			oldx = movetoabs->get_x();
			oldy = movetoabs->get_y();

			//if (matrix)
			{
				gm::PointD pt(oldx, oldy);
				gm::PointD xpt = mat.Transform(pt);

				oldx = xpt.X;
				oldy = xpt.Y;
			}
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			SVGPathSegLinetoAbs* linetoabs = static_cast<SVGPathSegLinetoAbs*>(seg);

			double x = linetoabs->get_x();
			double y = linetoabs->get_y();

			//if (matrix)
			{
				gm::PointD pt(x, y);
				gm::PointD xpt = mat.Transform(pt);

				x = xpt.X;
				y = xpt.Y;
			}

			if (oldx < mx[0]) mx[0] = oldx;
			if (oldy < mx[1]) mx[1] = oldy;
			if (oldx > mx[2]) mx[2] = oldx;
			if (oldy > mx[3]) mx[3] = oldy;

			if (x < mx[0]) mx[0] = x;
			if (y < mx[1]) mx[1] = y;
			if (x > mx[2]) mx[2] = x;
			if (y > mx[3]) mx[3] = y;

			oldx = x;
			oldy = y;
		}
		else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			SVGPathSegCurvetoCubicAbs* cubictoabs = static_cast<SVGPathSegCurvetoCubicAbs*>(seg);

			double x, y, x1, y1, x2, y2;
			x = cubictoabs->get_x();
			y = cubictoabs->get_y();
			x1 = cubictoabs->get_x1();
			y1 = cubictoabs->get_y1();
			x2 = cubictoabs->get_x2();
			y2 = cubictoabs->get_y2();

			//if (matrix)
			{
				{
					gm::PointD pt(x, y);
					gm::PointD xpt = mat.Transform(pt);

					x = xpt.X;
					y = xpt.Y;
				}
				{
					gm::PointD pt(x1, y1);
					gm::PointD xpt = mat.Transform(pt);

					x1 = xpt.X;
					y1 = xpt.Y;
				}
				{
					gm::PointD pt(x2, y2);
					gm::PointD xpt = mat.Transform(pt);

					x2 = xpt.X;
					y2 = xpt.Y;
				}
			}

			gm::CalcCurveBBox(oldx, oldy, x1, y1, x2, y2, x, y, mx);

			oldx = x;
			oldy = y;
		}
	}

	bbox->X = mx[0];
	bbox->Y = mx[1];
	bbox->Width = mx[2]-mx[0];//+1;
	bbox->Height = mx[3]-mx[1];//+1;
}

HTMLEXT void GetPathSegListBBox(SVGPathSegList* seglist, gm::Matrix3d mat, gm::RectD* bbox)
{
	double mx[4] =
	{
		9999999, 9999999,		// minx / miny
		-9999999, -9999999,		// maxx / maxy
	};

	double oldx = 0;
	double oldy = 0;

	uint numberOfItems = seglist->get_numberOfItems();
	for (int i = 0; i < numberOfItems; i++)
	{
		SVGPathSeg* seg = seglist->getItem(i);

		SVGPathSegType segType = seg->get_pathSegType();
		if (segType == PATHSEG_MOVETO_ABS)
		{
			SVGPathSegMovetoAbs* movetoabs = static_cast<SVGPathSegMovetoAbs*>(seg);

			oldx = movetoabs->get_x();
			oldy = movetoabs->get_y();

			//if (matrix)
			{
				gm::PointD pt(oldx, oldy);
				gm::PointD xpt = mat.Transform(pt);

				oldx = xpt.X;
				oldy = xpt.Y;
			}
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			SVGPathSegLinetoAbs* linetoabs = static_cast<SVGPathSegLinetoAbs*>(seg);

			double x = linetoabs->get_x();
			double y = linetoabs->get_y();

			//if (matrix)
			{
				gm::PointD pt(x, y);
				gm::PointD xpt = mat.Transform(pt);

				x = xpt.X;
				y = xpt.Y;
			}

			if (oldx < mx[0]) mx[0] = oldx;
			if (oldy < mx[1]) mx[1] = oldy;
			if (oldx > mx[2]) mx[2] = oldx;
			if (oldy > mx[3]) mx[3] = oldy;

			if (x < mx[0]) mx[0] = x;
			if (y < mx[1]) mx[1] = y;
			if (x > mx[2]) mx[2] = x;
			if (y > mx[3]) mx[3] = y;

			oldx = x;
			oldy = y;
		}
		else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			SVGPathSegCurvetoCubicAbs* cubictoabs = static_cast<SVGPathSegCurvetoCubicAbs*>(seg);

			double x, y, x1, y1, x2, y2;
			x = cubictoabs->get_x();
			y = cubictoabs->get_y();
			x1 = cubictoabs->get_x1();
			y1 = cubictoabs->get_y1();
			x2 = cubictoabs->get_x2();
			y2 = cubictoabs->get_y2();

			//if (matrix)
			{
				{
					gm::PointD pt(x, y);
					gm::PointD xpt = mat.Transform(pt);

					x = xpt.X;
					y = xpt.Y;
				}
				{
					gm::PointD pt(x1, y1);
					gm::PointD xpt = mat.Transform(pt);

					x1 = xpt.X;
					y1 = xpt.Y;
				}
				{
					gm::PointD pt(x2, y2);
					gm::PointD xpt = mat.Transform(pt);

					x2 = xpt.X;
					y2 = xpt.Y;
				}
			}

			gm::CalcCurveBBox(oldx, oldy, x1, y1, x2, y2, x, y, mx);

			oldx = x;
			oldy = y;
		}
	}

	bbox->X = mx[0];
	bbox->Y = mx[1];
	bbox->Width = mx[2]-mx[0];//+1;
	bbox->Height = mx[3]-mx[1];//+1;
}

HTMLEXT void GetPathSegListBBox(SVGPathSegList* seglist, gm::RectD* bbox)
{
	double mx[4] =
	{
		9999999, 9999999,		// minx / miny
		-9999999, -9999999,		// maxx / maxy
	};

	double oldx = 0;
	double oldy = 0;

	long numberOfItems = seglist->get_numberOfItems();
	for (int i = 0; i < numberOfItems; i++)
	{
		SVGPathSeg* seg = seglist->getItem(i);

		SVGPathSegType segType = seg->get_pathSegType();
		if (segType == PATHSEG_MOVETO_ABS)
		{
			SVGPathSegMovetoAbs* movetoabs = static_cast<SVGPathSegMovetoAbs*>(seg);

			oldx = movetoabs->get_x();
			oldy = movetoabs->get_y();

			/*
			//if (matrix)
			{
				gmVector2 pt(oldx, oldy);
				gmVector2 xpt = mat.transform(pt);

				oldx = xpt[0];
				oldy = xpt[1];
			}
			*/
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			SVGPathSegLinetoAbs* linetoabs = static_cast<SVGPathSegLinetoAbs*>(seg);

			double x = linetoabs->get_x();
			double y = linetoabs->get_y();

			/*
			//if (matrix)
			{
				gmVector2 pt(x, y);
				gmVector2 xpt = mat.transform(pt);

				x = xpt[0];
				y = xpt[1];
			}
			*/

			if (oldx < mx[0]) mx[0] = oldx;
			if (oldy < mx[1]) mx[1] = oldy;
			if (oldx > mx[2]) mx[2] = oldx;
			if (oldy > mx[3]) mx[3] = oldy;

			if (x < mx[0]) mx[0] = x;
			if (y < mx[1]) mx[1] = y;
			if (x > mx[2]) mx[2] = x;
			if (y > mx[3]) mx[3] = y;

			oldx = x;
			oldy = y;
		}
		else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			SVGPathSegCurvetoCubicAbs* cubictoabs = static_cast<SVGPathSegCurvetoCubicAbs*>(seg);

			double x, y, x1, y1, x2, y2;
			x = cubictoabs->get_x();
			y = cubictoabs->get_y();
			x1 = cubictoabs->get_x1();
			y1 = cubictoabs->get_y1();
			x2 = cubictoabs->get_x2();
			y2 = cubictoabs->get_y2();

			/*
			//if (matrix)
			{
				{
					gmVector2 pt(x, y);
					gmVector2 xpt = mat.transform(pt);

					x = xpt[0];
					y = xpt[1];
				}
				{
					gmVector2 pt(x1, y1);
					gmVector2 xpt = mat.transform(pt);

					x1 = xpt[0];
					y1 = xpt[1];
				}
				{
					gmVector2 pt(x2, y2);
					gmVector2 xpt = mat.transform(pt);

					x2 = xpt[0];
					y2 = xpt[1];
				}
			}
			*/

			gm::CalcCurveBBox(oldx, oldy, x1, y1, x2, y2, x, y, mx);

			oldx = x;
			oldy = y;
		}
	}

	bbox->X = mx[0];
	bbox->Y = mx[1];
	bbox->Width = mx[2]-mx[0];//+1;
	bbox->Height = mx[3]-mx[1];//+1;
}

double GetLengthPathSegList(SVGPathSegList* seglist, SVGMatrix* xform)
{
	double length = 0;
#if 0

	double last_movex = 0;
	double last_movey = 0;

	double oldx;
	double oldy;

	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);
	for (int i = 0; i < numberOfItems; i++)
	{
		CComQIPtr<ILSVGPathSeg> seg;
		seglist->getItem(i, &seg);

		LSVGPathSegType segType;
		seg->get_pathSegType(&segType);
		if (segType == PATHSEG_MOVETO_ABS)
		{
			CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;

			double x, y;
			movetoabs->get_x(&x);
			movetoabs->get_y(&y);

			if (xform)
			{
				CComQIPtr<ILSVGPoint> pt;
				pt.CoCreateInstance(CLSID_SVGPoint);

				pt->set_x(x);
				pt->set_y(y);

				CComQIPtr<ILSVGPoint> xpt;
				pt->matrixTransform(xform, &xpt);

				xpt->get_x(&x);
				xpt->get_y(&y);
			}

			last_movex = x;
			last_movey = y;

			oldx = x;
			oldy = y;
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			CComQIPtr<ILSVGPathSegLinetoAbs> linetoabs = seg;

			double x, y;
			linetoabs->get_x(&x);
			linetoabs->get_y(&y);

			if (xform)
			{
				CComQIPtr<ILSVGPoint> pt;
				pt.CoCreateInstance(CLSID_SVGPoint);

				pt->set_x(x);
				pt->set_y(y);

				CComQIPtr<ILSVGPoint> xpt;
				pt->matrixTransform(xform, &xpt);

				xpt->get_x(&x);
				xpt->get_y(&y);
			}

			double dx = x-oldx;
			double dy = y-oldy;

			double l = sqrt(dx*dx + dy*dy);
			length += l;

			oldx = x;
			oldy = y;
		}
		else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubictoabs = seg;

			double x, y, x1, y1, x2, y2;
			cubictoabs->get_x(&x);
			cubictoabs->get_y(&y);
			cubictoabs->get_x1(&x1);
			cubictoabs->get_y1(&y1);
			cubictoabs->get_x2(&x2);
			cubictoabs->get_y2(&y2);

			if (xform)
			{
				CComQIPtr<ILSVGPoint> pt;
				pt.CoCreateInstance(CLSID_SVGPoint);

				{
					pt->set_x(x);
					pt->set_y(y);

					CComQIPtr<ILSVGPoint> xpt;
					pt->matrixTransform(xform, &xpt);

					xpt->get_x(&x);
					xpt->get_y(&y);
				}

				{
					pt->set_x(x1);
					pt->set_y(y1);

					CComQIPtr<ILSVGPoint> xpt;
					pt->matrixTransform(xform, &xpt);

					xpt->get_x(&x1);
					xpt->get_y(&y1);
				}

				{
					pt->set_x(x2);
					pt->set_y(y2);

					CComQIPtr<ILSVGPoint> xpt;
					pt->matrixTransform(xform, &xpt);

					xpt->get_x(&x2);
					xpt->get_y(&y2);
				}
			}

			double l = CalcCurveLength(oldx, oldy, x1, y1, x2, y2, x, y);
			length += l;

			oldx = x;
			oldy = y;
		}
		else if (segType == PATHSEG_CLOSEPATH)
		{
		//	int ix = last_movex;
		//	int iy = last_movey;
		}
	}
#endif
	return length;
}

int GetPointOnLengthPathSegList(SVGPathSegList* seglist, SVGMatrix* xform, double onlength, double* pxt, double* pyt, double* pangle)
{
	double length = 0;

#if 0
	double last_movex = 0;
	double last_movey = 0;

	double oldx;
	double oldy;

	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);
	for (int i = 0; i < numberOfItems; i++)
	{
		CComQIPtr<ILSVGPathSeg> seg;
		seglist->getItem(i, &seg);

		LSVGPathSegType segType;
		seg->get_pathSegType(&segType);
		if (segType == PATHSEG_MOVETO_ABS)
		{
			CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;

			double x, y;
			movetoabs->get_x(&x);
			movetoabs->get_y(&y);

			if (xform)
			{
				CComQIPtr<ILSVGPoint> pt;
				pt.CoCreateInstance(CLSID_SVGPoint);

				pt->set_x(x);
				pt->set_y(y);

				CComQIPtr<ILSVGPoint> xpt;
				pt->matrixTransform(xform, &xpt);

				xpt->get_x(&x);
				xpt->get_y(&y);
			}

			last_movex = x;
			last_movey = y;

			oldx = x;
			oldy = y;
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			CComQIPtr<ILSVGPathSegLinetoAbs> linetoabs = seg;

			double x, y;
			linetoabs->get_x(&x);
			linetoabs->get_y(&y);

			if (xform)
			{
				CComQIPtr<ILSVGPoint> pt;
				pt.CoCreateInstance(CLSID_SVGPoint);

				pt->set_x(x);
				pt->set_y(y);

				CComQIPtr<ILSVGPoint> xpt;
				pt->matrixTransform(xform, &xpt);

				xpt->get_x(&x);
				xpt->get_y(&y);
			}

			double dx = x-oldx;
			double dy = y-oldy;

			double l = sqrt(dx*dx + dy*dy);
			length += l;

			oldx = x;
			oldy = y;
		}
		else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubictoabs = seg;

			double x, y, x1, y1, x2, y2;
			cubictoabs->get_x(&x);
			cubictoabs->get_y(&y);
			cubictoabs->get_x1(&x1);
			cubictoabs->get_y1(&y1);
			cubictoabs->get_x2(&x2);
			cubictoabs->get_y2(&y2);

			if (xform)
			{
				CComQIPtr<ILSVGPoint> pt;
				pt.CoCreateInstance(CLSID_SVGPoint);

				{
					pt->set_x(x);
					pt->set_y(y);

					CComQIPtr<ILSVGPoint> xpt;
					pt->matrixTransform(xform, &xpt);

					xpt->get_x(&x);
					xpt->get_y(&y);
				}

				{
					pt->set_x(x1);
					pt->set_y(y1);

					CComQIPtr<ILSVGPoint> xpt;
					pt->matrixTransform(xform, &xpt);

					xpt->get_x(&x1);
					xpt->get_y(&y1);
				}

				{
					pt->set_x(x2);
					pt->set_y(y2);

					CComQIPtr<ILSVGPoint> xpt;
					pt->matrixTransform(xform, &xpt);

					xpt->get_x(&x2);
					xpt->get_y(&y2);
				}
			}

			double x0 = oldx;
			double y0 = oldy;
			double x3 = x;
			double y3 = y;

			double t = -1;
			double l = GetCurveT(x0, y0, x1, y1, x2, y2, x3, y3, onlength-length, &t);
			if (t >= 0)
			{
				double cx = 3 * (x1 - x0);
				double cy = 3 * (y1 - y0);
				double bx = 3 * (x2 - x1) - cx;
				double by = 3 * (y2 - y1) - cy;
				double ax = x3 - x0 - cx - bx;
				double ay = y3 - y0 - cy - by;

				*pxt = ax * t*t*t + bx * t*t + cx * t + x0;
				*pyt = ay * t*t*t + by * t*t + cy * t + y0;

				// Calculate angle
				{
				// The derivative
					double dx = ax * 3*t*t + bx * 2*t + cx;
					double dy = ay * 3*t*t + by * 2*t + cy;

					{
						double distance = sqrt(dx*dx + dy*dy);
						double distance2 = distance;

						if (distance2 == 0.0) distance2 = 0.00001;
						if (dy < 0) distance2 =-distance2;
						double angle = acos(dx/distance2);
						if (dy < 0) angle += M_PI;

						*pangle = angle * 180/M_PI;
					}
				}

				return 0;
			}

			length += l;

			oldx = x;
			oldy = y;
		}
		else if (segType == PATHSEG_CLOSEPATH)
		{
		//	int ix = last_movex;
		//	int iy = last_movey;
		}
	}
#endif
	return -1;
}

#if 0
void DrawPathSegList(SVGPathSegList* seglist, HDC iDC, SVGMatrix* matrix, LDraw::Rect& xrect, double xsampling, double ysampling)
{
	LDraw::matrix3d mat;
	if (matrix)
	{
		double v;
		mat[0][0] = matrix->get_a(); mat[0][1] = matrix->get_b();
		mat[1][0] = matrix->get_c(); mat[1][1] = matrix->get_d();
		mat[2][0] = matrix->get_e(); mat[2][1] = matrix->get_f();
		mat[0][2] = 0;
		mat[1][2] = 0;
		mat[2][2] = 1;
	}
	else
	{
		mat = LDraw::matrix3d::getIdentity();
	}

	double last_movex = 0;
	double last_movey = 0;

	long numberOfItems = seglist->get_numberOfItems();
	for (int i = 0; i < numberOfItems; i++)
	{
		SVGPathSegImpl* seg = seglist->getItem(i);

		SVGPathSegType segType = seg->get_pathSegType();
		if (segType == PATHSEG_MOVETO_ABS)
		{
			SVGPathSegMovetoAbs* movetoabs = dynamic_cast<SVGPathSegMovetoAbs*>(seg);

			double x, y;
			movetoabs->get_x(&x);
			movetoabs->get_y(&y);

			LDraw::vector2d pt(x, y);
			LDraw::vector2d xpt = mat.transform(pt);
			x = xpt[0];
			y = xpt[1];

			last_movex = x;
			last_movey = y;

			int ix = x;
			int iy = y;
			ix -= xrect.left;
			iy -= xrect.top;

			MoveToEx(iDC, ix, iy, NULL);
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			SVGPathSegLinetoAbs* linetoabs = dynamic_cast<SVGPathSegLinetoAbs*>(seg);

			double x, y;
			linetoabs->get_x(&x);
			linetoabs->get_y(&y);

		/*
			if (xform)
			{
				CComQIPtr<ILSVGPoint> pt;
				pt.CoCreateInstance(CLSID_SVGPoint);

				pt->set_x(x);
				pt->set_y(y);

				CComQIPtr<ILSVGPoint> xpt;
				pt->matrixTransform(xform, &xpt);

				xpt->get_x(&x);
				xpt->get_y(&y);
			}
		*/
			LDraw::vector2d pt(x, y);
			LDraw::vector2d xpt = mat.transform(pt);
			x = xpt[0];
			y = xpt[1];

			int ix = x;
			int iy = y;
			ix -= xrect.left;
			iy -= xrect.top;

			LineTo(iDC, ix, iy);
		}
		else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			SVGPathSegCurvetoCubicAbs* cubictoabs = dynamic_cast<SVGPathSegCurvetoCubicAbs*>(seg);

			double x, y, x1, y1, x2, y2;
			cubictoabs->get_x(&x);
			cubictoabs->get_y(&y);
			cubictoabs->get_x1(&x1);
			cubictoabs->get_y1(&y1);
			cubictoabs->get_x2(&x2);
			cubictoabs->get_y2(&y2);

			{
				LDraw::vector2d pt(x, y);
				LDraw::vector2d xpt = mat.transform(pt);

				x = xpt[0];
				y = xpt[1];
			}
			{
				LDraw::vector2d pt(x1, y1);
				LDraw::vector2d xpt = mat.transform(pt);

				x1 = xpt[0];
				y1 = xpt[1];
			}
			{
				LDraw::vector2d pt(x2, y2);
				LDraw::vector2d xpt = mat.transform(pt);

				x2 = xpt[0];
				y2 = xpt[1];
			}

			POINT pt[3] =
			{
				x1-xrect.left, y1-xrect.top,
				x2-xrect.left, y2-xrect.top,
				x-xrect.left, y-xrect.top,
			};

			PolyBezierTo(iDC, pt, 3);
		}
		else if (segType == PATHSEG_CLOSEPATH)
		{
			int ix = last_movex;
			int iy = last_movey;
			ix -= xrect.left;
			iy -= xrect.top;

			LineTo(iDC, ix, iy);
		}
	}
}
#endif

#if 0
HTMLEXT void DrawPathSegList(SVGPathSegList* seglist, LDraw::GraphicsPathF* path, SVGMatrix* matrix)
{
	ASSERT(0);
#if 0
	gmMatrix3 mat;
	if (matrix)
	{
		double v;
		matrix->get_a(&v); mat[0][0] = v; matrix->get_b(&v); mat[0][1] = v;
		matrix->get_c(&v); mat[1][0] = v; matrix->get_d(&v); mat[1][1] = v;
		matrix->get_e(&v); mat[2][0] = v; matrix->get_f(&v); mat[2][1] = v;
		mat[0][2] = 0;
		mat[1][2] = 0;
		mat[2][2] = 1;
	}
	else
		mat = gmMatrix3::identity();

	double last_movex = 0;
	double last_movey = 0;

	double last_posx = 0;
	double last_posy = 0;

	long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);
	for (int i = 0; i < numberOfItems; i++)
	{
		CComQIPtr<ILSVGPathSeg> seg;
		seglist->getItem(i, &seg);

		LSVGPathSegType segType;
		seg->get_pathSegType(&segType);
		if (segType == PATHSEG_MOVETO_ABS)
		{
			CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;

			double x, y;
			movetoabs->get_x(&x);
			movetoabs->get_y(&y);

			vector2d pt(x, y);
			vector2d xpt = mat.transform(pt);
			x = xpt[0];
			y = xpt[1];

			path->StartFigure();
			last_posx = last_movex = x;
			last_posy = last_movey = y;
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			CComQIPtr<ILSVGPathSegLinetoAbs> linetoabs = seg;

			double x, y;
			linetoabs->get_x(&x);
			linetoabs->get_y(&y);

			vector2d pt(x, y);
			vector2d xpt = mat.transform(pt);
			x = xpt[0];
			y = xpt[1];

			path->AddLine((float)last_posx, (float)last_posy, (float)x, (float)y);
			last_posx = x;
			last_posy = y;
		}
		else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubictoabs = seg;

			double x, y, x1, y1, x2, y2;
			cubictoabs->get_x(&x);
			cubictoabs->get_y(&y);
			cubictoabs->get_x1(&x1);
			cubictoabs->get_y1(&y1);
			cubictoabs->get_x2(&x2);
			cubictoabs->get_y2(&y2);

			{
				vector2d pt(x, y);
				vector2d xpt = mat.transform(pt);

				x = xpt[0];
				y = xpt[1];
			}
			{
				vector2d pt(x1, y1);
				vector2d xpt = mat.transform(pt);

				x1 = xpt[0];
				y1 = xpt[1];
			}
			{
				vector2d pt(x2, y2);
				vector2d xpt = mat.transform(pt);

				x2 = xpt[0];
				y2 = xpt[1];
			}

			POINT pt[3] =
			{
				x1, y1,
				x2, y2,
				x, y,
			};

			path->AddBezier((float)last_posx, (float)last_posy, (float)x1, (float)y1, (float)x2, (float)y2, (float)x, (float)y);

			last_posx = x;
			last_posy = y;
		}
		else if (segType == PATHSEG_CLOSEPATH)
		{
			path->CloseFigure();
		//	path->AddLine((float)last_posx, (float)last_posy, (float)last_movex, (float)last_movey);
		}
	}
#endif
}
#endif

void TransformPathSegList(SVGPathSegList* seglist, SVGMatrix* xform)
{
#if 0
	unsigned long numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);
	for (int i = 0; i < numberOfItems; i++)
	{
		CComQIPtr<ILSVGPathSeg> seg;
		seglist->getItem(i, &seg);

		LSVGPathSegType segType;
		seg->get_pathSegType(&segType);
		if (segType == PATHSEG_MOVETO_ABS)
		{
			CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;

			double x, y;
			movetoabs->get_x(&x);
			movetoabs->get_y(&y);

			if (xform)
			{
				CComQIPtr<ILSVGPoint> pt;
				pt.CoCreateInstance(CLSID_SVGPoint);

				pt->set_x(x);
				pt->set_y(y);

				CComQIPtr<ILSVGPoint> xpt;
				pt->matrixTransform(xform, &xpt);

				xpt->get_x(&x);
				xpt->get_y(&y);

				movetoabs->set_x(x);
				movetoabs->set_y(y);
			}
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			CComQIPtr<ILSVGPathSegLinetoAbs> linetoabs = seg;

			double x, y;
			linetoabs->get_x(&x);
			linetoabs->get_y(&y);

			if (xform)
			{
				CComQIPtr<ILSVGPoint> pt;
				pt.CoCreateInstance(CLSID_SVGPoint);

				pt->set_x(x);
				pt->set_y(y);

				CComQIPtr<ILSVGPoint> xpt;
				pt->matrixTransform(xform, &xpt);

				xpt->get_x(&x);
				xpt->get_y(&y);

				linetoabs->set_x(x);
				linetoabs->set_y(y);
			}
		}
		else if (segType == PATHSEG_CURVETO_CUBIC_ABS)
		{
			CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubictoabs = seg;

			double x, y, x1, y1, x2, y2;
			cubictoabs->get_x(&x);
			cubictoabs->get_y(&y);
			cubictoabs->get_x1(&x1);
			cubictoabs->get_y1(&y1);
			cubictoabs->get_x2(&x2);
			cubictoabs->get_y2(&y2);

			if (xform)
			{
				CComQIPtr<ILSVGPoint> pt;
				pt.CoCreateInstance(CLSID_SVGPoint);

				{
					pt->set_x(x);
					pt->set_y(y);

					CComQIPtr<ILSVGPoint> xpt;
					pt->matrixTransform(xform, &xpt);

					xpt->get_x(&x);
					xpt->get_y(&y);
				}

				{
					pt->set_x(x1);
					pt->set_y(y1);

					CComQIPtr<ILSVGPoint> xpt;
					pt->matrixTransform(xform, &xpt);

					xpt->get_x(&x1);
					xpt->get_y(&y1);
				}

				{
					pt->set_x(x2);
					pt->set_y(y2);

					CComQIPtr<ILSVGPoint> xpt;
					pt->matrixTransform(xform, &xpt);

					xpt->get_x(&x2);
					xpt->get_y(&y2);
				}

				cubictoabs->set_x(x);
				cubictoabs->set_y(y);
				cubictoabs->set_x1(x1);
				cubictoabs->set_y1(y1);
				cubictoabs->set_x2(x2);
				cubictoabs->set_y2(y2);
			}
		}
		else if (segType == PATHSEG_CLOSEPATH)
		{
		}
	}
#endif
}

#include "SVGPathSegMovetoAbs.h"
#include "SVGPathSegCurvetoCubicAbs.h"

void SetPathSegListToLine(SVGPathSegList* seglist, double x1, double y1, double x2, double y2)
{
	{
		SVGPathSegMovetoAbs* seg = new SVGPathSegMovetoAbs;
		seg->set_x(x1);	seg->set_y(y1);
		seglist->appendItem(seg);
	}

	{
		SVGPathSegCurvetoCubicAbs* seg = new SVGPathSegCurvetoCubicAbs;
		seg->set_x(x2);	seg->set_y(y2);
		seg->set_x1(x1);		seg->set_y1(y1);
		seg->set_x2(x2);		seg->set_y2(y2);
		seglist->appendItem(seg);
	}
}

}	// Web
}
