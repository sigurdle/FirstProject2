#include "stdafx.h"

#include "LXMLEditor.h"

namespace System
{

#if 0
_bstr_t StringFromPathSegList(ILSVGPathSegList* seglist)
{
	_bstr_t str;
	unsigned long int numberOfItems;
	seglist->get_numberOfItems(&numberOfItems);

	for (int i = 0; i < numberOfItems; i++)
	{
		CComQIPtr<ILSVGPathSeg> seg;
		seglist->getItem(i, &seg);

		if (i > 0) str += L" ";
		
		LSVGPathSegType segType;
		seg->get_pathSegType(&segType);
		switch (segType)
		{
		case PATHSEG_MOVETO_ABS:
			{
				CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs = seg;
				
				double x, y;
				movetoabs->get_x(&x);
				movetoabs->get_y(&y);
				
				CUString str2;
				str2.Format("M%g %g", x, y);
				str += _bstr_t(str2);
			}
			break;
			
		case PATHSEG_CURVETO_CUBIC_ABS:
			{
				CComQIPtr<ILSVGPathSegCurvetoCubicAbs> cubictoabs = seg;
				
				double x, y, x1, y1, x2, y2;
				cubictoabs->get_x(&x);
				cubictoabs->get_y(&y);
				cubictoabs->get_x1(&x1);
				cubictoabs->get_y1(&y1);
				cubictoabs->get_x2(&x2);
				cubictoabs->get_y2(&y2);
				
				CUString str2;
				str2.Format("C%g %g %g %g %g %g", x1, y1, x2, y2, x, y);
				str += _bstr_t(str2);
			}
			break;

		case PATHSEG_CLOSEPATH:
			{
				str += L"z";
			}
			break;

		default:
			ATLASSERT(0);
		}
	}

	return str;
}

BOOL ParsePathData(ILSVGPathElement* pathElement, ILSVGPathSegList* segList, CUString str_pathdata)
{
	LPCTSTR ptext = str_pathdata;
	int len = lstrlen(ptext);

	int iCurCurve = -1;

	BOOL success = FALSE;	// Assume error

#if 0
	CComQIPtr<ISVGPathElement> pathElement;
	QueryInterface(IID_ISVGPathElement, (void**)&pathElement);

	CComQIPtr<ISVGPathSegList> segList;
	/*pathElement->*/get_pathSegList(&segList);
#endif

	segList->LockUpdate();

	LPCTSTR p = ptext;
	while (*p)	// Process entire string
	{
		while (*p && isspace(*p)) p++;
		if (*p == 0) break;

		char op = *p++;	// Get operation
		if (!isalpha(op))
		{
			MessageBox(NULL, "illegal path data op", "SVG", MB_OK);
			goto Exit;	// Illegal operation
		}

	// Get values
		CArray <double,double> dbl_values;

		while (*p)
		{
			while (*p && isspace(*p)) p++;

			CUString v;
			while (*p && !isalpha(*p) && !isspace(*p) && (*p != ','))
			{
				v += CUString(*p);
				p++;
			}

			if (v.GetLength() > 0) dbl_values.Add(atof(v));

			if (!*p || isalpha(*p)) break;

			if (*p == ',') p++;
		}

		switch (op)
		{
		case 'm':	// relative moveto
		case 'M':	// absolute moveto
		case 'l':	// relative lineto
		case 'L':	// absolute lineto
		case 'c':	// Relative Cubic bezier
		case 'C':	// Absolute Cubic bezier
		case 's':	// Relative shorthand/smooth curveto
		case 'S':	// Absolute shorthand/smooth curveto
		case 'q':	// Relative quadratic bezier
		case 'Q':	// Absolute quadratic bezier
			{
				if ((dbl_values.GetSize() % 2) != 0)
				{
					goto Exit;
				}

				CArray <DblPOINT,DblPOINT&> points;
				int npoints = dbl_values.GetSize()/2;
				points.SetSize(npoints);

				for (int n = 0; n < npoints; n++)
				{
					points[n].x = dbl_values[n*2+0];
					points[n].y = dbl_values[n*2+1];
				}

				switch (op)
				{
/*
If a moveto is followed by multiple pairs of coordinates, the subsequent
pairs are treated as implicit lineto commands.
*/

				case 'm':	// Relative moveto
					{
						CComQIPtr<ISVGPathSegMovetoRel> seg_movetorel;
						pathElement->createSVGPathSegMovetoRel(points[0].x, points[0].y, &seg_movetorel);
						segList->appendItem(seg_movetorel, NULL);

						for (int i = 1; i < npoints; i++)
						{
							CComQIPtr<ISVGPathSegLinetoAbs> seg_linetoabs;
							pathElement->createSVGPathSegLinetoAbs(points[i].x, points[i].y, &seg_linetoabs);
							segList->appendItem(seg_linetoabs, NULL);
						}
					}
					break;

				case 'M':	// Absolute moveto
					{
						CComQIPtr<ISVGPathSegMovetoAbs> seg_movetoabs;
						pathElement->createSVGPathSegMovetoAbs(points[0].x, points[0].y, &seg_movetoabs);
						segList->appendItem(seg_movetoabs, NULL);

						for (int i = 1; i < npoints; i++)
						{
							CComQIPtr<ISVGPathSegLinetoAbs> seg_linetoabs;
							pathElement->createSVGPathSegLinetoAbs(points[i].x, points[i].y, &seg_linetoabs);
							segList->appendItem(seg_linetoabs, NULL);
						}
					}
					break;

				case 'l':	// Relative lineto
					{
						for (int i = 0; i < npoints; i++)
						{
							CComQIPtr<ISVGPathSegLinetoRel> seg_linetorel;
							pathElement->createSVGPathSegLinetoRel(points[i].x, points[i].y, &seg_linetorel);
							segList->appendItem(seg_linetorel, NULL);
						}
					}
					break;

				case 'L':	// Absolute lineto
					{
						for (int i = 0; i < npoints; i++)
						{
							CComQIPtr<ISVGPathSegLinetoAbs> seg_linetoabs;
							pathElement->createSVGPathSegLinetoAbs(points[i].x, points[i].y, &seg_linetoabs);
							segList->appendItem(seg_linetoabs, NULL);
						}
					}
					break;

				case 'c':	// relative Cubic bezier
					{
						if ((npoints % 3) != 0) goto Exit;

						for (int i = 0; i < npoints; i += 3)
						{
							CComQIPtr<ISVGPathSegCurvetoCubicRel> seg;
							pathElement->createSVGPathSegCurvetoCubicRel(points[i+2].x, points[i+2].y, points[i].x, points[i].y, points[i+1].x, points[i+1].y, &seg);
							segList->appendItem(seg, NULL);
						}
					}
					break;

				case 'C':	// absolute Cubic bezier
					{
						if ((npoints % 3) != 0) goto Exit;

						for (int i = 0; i < npoints; i += 3)
						{
							CComQIPtr<ISVGPathSegCurvetoCubicAbs> seg;
							pathElement->createSVGPathSegCurvetoCubicAbs(points[i+2].x, points[i+2].y, points[i].x, points[i].y, points[i+1].x, points[i+1].y, &seg);
							segList->appendItem(seg, NULL);
						}
					}
					break;

#if 0

				case 'm':	// Relative moveto
				/* If a relative moveto (m) appears as the first element of the
 				  path, then it is treated as a pair of absolute coordinates
				  */
					if (iCurCurve >= 0)
					{
						pLayer->AddLastPoint(iCurCurve);

						CIBezier* pBez = pLayer->GetBezierList()->GetIndex(iCurCurve);
						CAPoint* apoints = pBez->GetPoints();
						int anpoints = pBez->GetNumPoints();

						iCurCurve = pLayer->AddSubCurve();
						if (npoints < 1) goto Exit;

						pLayer->AddPoint(iCurCurve, apoints[anpoints-2].x + points[0].x, apoints[anpoints-2].y + points[0].y);
						pLayer->AddPoint(iCurCurve, apoints[anpoints-2].x + points[0].x, apoints[anpoints-2].y + points[0].y);

						for (int i = 1; i < npoints; i++)
						{
							pLayer->AddPoint(iCurCurve, points[i].x, points[i].y);
							pLayer->AddPoint(iCurCurve, points[i].x, points[i].y);
							pLayer->AddPoint(iCurCurve, points[i].x, points[i].y);
						}

						break;
					}

				case 'M':	// Absolute moveto
					{
						if (iCurCurve >= 0) pLayer->AddLastPoint(iCurCurve);

						iCurCurve = pLayer->AddSubCurve();
						if (npoints < 1) goto Exit;

						pLayer->AddPoint(iCurCurve, points[0].x, points[0].y);
						pLayer->AddPoint(iCurCurve, points[0].x, points[0].y);

						for (int i = 1; i < npoints; i++)
						{
							pLayer->AddPoint(iCurCurve, points[i].x, points[i].y);
							pLayer->AddPoint(iCurCurve, points[i].x, points[i].y);
							pLayer->AddPoint(iCurCurve, points[i].x, points[i].y);
						}
					}
					break;

				case 'c':	// Relative Cubic bezier
					{
						if (iCurCurve < 0) goto Exit;
						if ((npoints % 3) != 0) goto Exit;

						CIBezier* pBez = pLayer->GetBezierList()->GetIndex(iCurCurve);
						CAPoint* apoints = pBez->GetPoints();
						int anpoints = pBez->GetNumPoints();

						double x = apoints[anpoints-1].x;
						double y = apoints[anpoints-1].y;

						for (int i = 0; i < npoints; i += 3)
						{
							pLayer->AddPoint(iCurCurve, x + points[i].x, y + points[i].y);
							pLayer->AddPoint(iCurCurve, x + points[i+1].x, y + points[i+1].y);
							pLayer->AddPoint(iCurCurve, x + points[i+2].x, y + points[i+2].y);

							x = points[i+2].x;
							y = points[i+2].y;
						}
					}
					break;

				case 'C':	// Absolute Cubic bezier
					{
						if (iCurCurve < 0) goto Exit;
						if ((npoints % 3) != 0) goto Exit;

						for (int i = 0; i < npoints; i++)
						{
							pLayer->AddPoint(iCurCurve, points[i].x, points[i].y);
						}
					}
					break;

				case 'q':
					{
						if (iCurCurve < 0) goto Exit;
						if ((npoints % 2) != 0) goto Exit;

						CIBezier* pBez = pLayer->GetBezierList()->GetIndex(iCurCurve);
						CAPoint* apoints = pBez->GetPoints();
						int anpoints = pBez->GetNumPoints();

						CAPoint start = apoints[anpoints-1];

						AppendQuadBSplineToBezier(pBez, start, points.GetData(), npoints, TRUE);
					}
					break;

				case 'Q':
					{
						if (iCurCurve < 0) goto Exit;
						if ((npoints % 2) != 0) goto Exit;

						CIBezier* pBez = pLayer->GetBezierList()->GetIndex(iCurCurve);
						CAPoint* apoints = pBez->GetPoints();
						int anpoints = pBez->GetNumPoints();

						CAPoint start = apoints[anpoints-1];

						AppendQuadBSplineToBezier(pBez, start, points.GetData(), npoints, FALSE);
					}
					break;

		/*
			s and S

			Draws a cubic Bézier curve from the current point to (x,y). The first
			control point is assumed to be the reflection of the second control
			point on the previous command relative to the current point.
			(If there is no previous command or if the previous command was not
			an C, c, S or s, assume the first control point is coincident with
			the current point.) (x2,y2) is the second control point
			(i.e., the control point at the end of the curve). S (uppercase)
			indicates that absolute coordinates will follow; s (lowercase)
			indicates that relative coordinates will follow. Multiple sets of
			coordinates may be specified to draw a polybezier. At the end of
			the command, the new current point becomes the final (x,y) coordinate
			pair used in the polybezier.
		*/

				case 's':
				case 'S':
					{
						if (iCurCurve < 0) goto Exit;
						if ((npoints % 2) != 0) goto Exit;

						CIBezier* pBez = pLayer->GetBezierList()->GetIndex(iCurCurve);
						CAPoint* apoints = pBez->GetPoints();
						int anpoints = pBez->GetNumPoints();

						CDblPoint apt = apoints[anpoints-2];
						CDblPoint ppt = apoints[anpoints-1];

						double prevx, prevy;
						if (op == 's')	// Relative coordinates
						{
							prevx = apoints[anpoints-1].x;
							prevy = apoints[anpoints-1].y;
						}
						else	// Absolute coordinates
						{
							prevx = 0;
							prevy = 0;
						}

						for (int i = 0; i < npoints; i += 2)
						{
						// Compute the 1 control point from the 2 control point of previous curve

							double dx = apt.x-ppt.x;
							double dy = apt.y-ppt.y;
							double distance = sqrt(dx*dx+dy*dy);
							double distance2 = distance;

							if (distance2 == 0.0) distance2 = 0.0001;
							if (dy < 0) distance2 =-distance2;
							double angle = acos(dx/distance2);
							if (dy < 0) angle += M_PI;

							angle += M_PI;	// Add 180 degrees (Reflection)

							CAPoint	pt3;
							pt3.x = (cos(angle)*distance)+ppt.x;
							pt3.y = (sin(angle)*distance)+ppt.y;

							pLayer->AddPoint(iCurCurve, pt3.x, pt3.y);

						// Add second control point
							pLayer->AddPoint(iCurCurve, prevx + points[i].x, prevy + points[i].y);

						// Add last anchor point
							pLayer->AddPoint(iCurCurve, prevx + points[i+1].x, prevy + points[i+1].y);

							apt = points[i];
							ppt = points[i+1];

							if (op == 's')
							{
								prevx = points[i+1].x;
								prevy = points[i+1].y;
							}
						}
					}
					break;

				case 'l':	// Relative lineto
					{
						if (iCurCurve < 0) goto Exit;

						CIBezier* pBez = pLayer->GetBezierList()->GetIndex(iCurCurve);
						CAPoint* apoints = pBez->GetPoints();
						int anpoints = pBez->GetNumPoints();

						double x = apoints[anpoints-2].x;
						double y = apoints[anpoints-2].y;

						if ((anpoints % 3) != 0)
						{
							pLayer->AddPoint(iCurCurve, apoints[anpoints-1].x, apoints[anpoints-1].y);
						}

						for (int i = 0; i < npoints; i++)
						{
							pLayer->AddPoint(iCurCurve, x + points[i].x, y + points[i].y);
							pLayer->AddPoint(iCurCurve, x + points[i].x, y + points[i].y);
							pLayer->AddPoint(iCurCurve, x + points[i].x, y + points[i].y);

							x = points[i].x;
							y = points[i].y;
						}
					}
					break;

				case 'L':	// Absolute lineto
					{
						if (iCurCurve < 0) goto Exit;

						CIBezier* pBez = pLayer->GetBezierList()->GetIndex(iCurCurve);
						CAPoint* apoints = pBez->GetPoints();
						int anpoints = pBez->GetNumPoints();

						if ((anpoints % 3) != 0)
						{
							pLayer->AddPoint(iCurCurve, apoints[anpoints-1].x, apoints[anpoints-1].y);
						}

						for (int i = 0; i < npoints; i++)
						{
							pLayer->AddPoint(iCurCurve, points[i].x, points[i].y);
							pLayer->AddPoint(iCurCurve, points[i].x, points[i].y);
							pLayer->AddPoint(iCurCurve, points[i].x, points[i].y);
						}
					}
					break;
#endif
				}
			}
			break;
			
		case 'h':	// Relative Horizontal line
		case 'H':	// Absolute Horizontal line
		case 'v':	// Relative Vertical line
		case 'V':	// Absolute Vertical line
			{
#if 0
				int npoints = dbl_values.GetSize();
				ATLASSERT(npoints == 1);

				switch (op)
				{
				case 'h':
					{
						if (iCurCurve < 0) goto Exit;
						
						CIBezier* pBez = pLayer->GetBezierList()->GetIndex(iCurCurve);
						CAPoint* apoints = pBez->GetPoints();
						int anpoints = pBez->GetNumPoints();

						double x = apoints[anpoints-2].x;
						double y = apoints[anpoints-2].y;

						if ((anpoints % 3) != 0)
						{
							pLayer->AddPoint(iCurCurve, apoints[anpoints-1].x, apoints[anpoints-1].y);
						}
						
						for (int i = 0; i < npoints; i++)
						{
							pLayer->AddPoint(iCurCurve, x + dbl_values[i], y);
							pLayer->AddPoint(iCurCurve, x + dbl_values[i], y);
							pLayer->AddPoint(iCurCurve, x + dbl_values[i], y);
						}
					}
					break;

				case 'v':
					{
						if (iCurCurve < 0) goto Exit;
						
						CIBezier* pBez = pLayer->GetBezierList()->GetIndex(iCurCurve);
						CAPoint* apoints = pBez->GetPoints();
						int anpoints = pBez->GetNumPoints();

						double x = apoints[anpoints-2].x;
						double y = apoints[anpoints-2].y;

						if ((anpoints % 3) != 0)
						{
							pLayer->AddPoint(iCurCurve, apoints[anpoints-1].x, apoints[anpoints-1].y);
						}

						for (int i = 0; i < npoints; i++)
						{
							pLayer->AddPoint(iCurCurve, x, y + dbl_values[i]);
							pLayer->AddPoint(iCurCurve, x, y + dbl_values[i]);
							pLayer->AddPoint(iCurCurve, x, y + dbl_values[i]);
						}
					}
					break;

				case 'H':
					{
						if (iCurCurve < 0) goto Exit;

						CIBezier* pBez = pLayer->GetBezierList()->GetIndex(iCurCurve);
						CAPoint* apoints = pBez->GetPoints();
						int anpoints = pBez->GetNumPoints();

						double y = apoints[anpoints-2].y;

						if ((anpoints % 3) != 0)
						{
							pLayer->AddPoint(iCurCurve, apoints[anpoints-1].x, apoints[anpoints-1].y);
						}

						for (int i = 0; i < npoints; i++)
						{
							pLayer->AddPoint(iCurCurve, dbl_values[i], y);
							pLayer->AddPoint(iCurCurve, dbl_values[i], y);
							pLayer->AddPoint(iCurCurve, dbl_values[i], y);
						}

						ATLASSERT((pBez->GetNumPoints() % 3) == 0);
					}
					break;

				case 'V':
					{
						if (iCurCurve < 0) goto Exit;

						CIBezier* pBez = pLayer->GetBezierList()->GetIndex(iCurCurve);
						CAPoint* apoints = pBez->GetPoints();
						int anpoints = pBez->GetNumPoints();

						double x = apoints[anpoints-2].x;

						if ((anpoints % 3) != 0)
						{
							pLayer->AddPoint(iCurCurve, apoints[anpoints-1].x, apoints[anpoints-1].y);
						}

						for (int i = 0; i < npoints; i++)
						{
							pLayer->AddPoint(iCurCurve, x, dbl_values[i]);
							pLayer->AddPoint(iCurCurve, x, dbl_values[i]);
							pLayer->AddPoint(iCurCurve, x, dbl_values[i]);
						}

						ATLASSERT((pBez->GetNumPoints() % 3) == 0);
					}
					break;
				}
#endif
			}
			break;

		case 'z':
		case 'Z':	// Close current sub-path (no difference between z/Z)
			{
				if (dbl_values.GetSize() != 0) goto Exit;
//				if (iCurCurve < 0) goto Exit;

				CComQIPtr<ISVGPathSegClosePath> seg_closepath;
				pathElement->createSVGPathSegClosePath(&seg_closepath);
				segList->appendItem(seg_closepath, NULL);

#if 0

				pLayer->AddLastPoint(iCurCurve);
				pLayer->SetSubCurveClosed(iCurCurve, TRUE);
#endif
				iCurCurve = -1;
			}
			break;

		default:
			{
				char msg[256];
				sprintf(msg, "Unsupported operation (yet) '%c'\nReport to author", op);
				MessageBox(NULL, msg, "SVG", MB_OK);
				goto Exit;
			}
			break;
		}
	}

//	if (iCurCurve >= 0) pLayer->AddLastPoint(iCurCurve);

	success = TRUE;

Exit:
	
	if (!success)
	{
		CUString msg;
		msg.Format("Error parsing path data\n\n%s", str_pathdata);
		MessageBox(NULL, msg, "SVG", MB_OK);
	}

	segList->UnlockUpdate();

	return success;
}
#endif

//#include "DrawSession.h"

#if 0
void DrawPathSegList(ILSVGPathSegList* seglist, HDC iDC, ILSVGMatrix* xform)
{
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

			CComQIPtr<ILSVGPoint> pt;
			pt.CoCreateInstance(CLSID_LSVGPoint);
			pt->put_x(x);
			pt->put_y(y);
			CComQIPtr<ILSVGPoint> xpt;
			pt->matrixTransform(xform, &xpt);
			xpt->get_x(&x);
			xpt->get_y(&y);

			int ix = x;
			int iy = y;

			MoveToEx(iDC, ix, iy, NULL);
		}
		else if (segType == PATHSEG_LINETO_ABS)
		{
			CComQIPtr<ILSVGPathSegLinetoAbs> linetoabs = seg;

			double x, y;
			linetoabs->get_x(&x);
			linetoabs->get_y(&y);

			CComQIPtr<ILSVGPoint> pt;
			pt.CoCreateInstance(CLSID_LSVGPoint);
			pt->put_x(x);
			pt->put_y(y);
			CComQIPtr<ILSVGPoint> xpt;
			pt->matrixTransform(xform, &xpt);
			xpt->get_x(&x);
			xpt->get_y(&y);

			int ix = x;
			int iy = y;

			LineTo(iDC, ix, iy);
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

			CComQIPtr<ILSVGPoint> pt;
			pt.CoCreateInstance(CLSID_LSVGPoint);

			{
				pt->put_x(x);
				pt->put_y(y);
				CComQIPtr<ILSVGPoint> xpt;
				pt->matrixTransform(xform, &xpt);
				xpt->get_x(&x);
				xpt->get_y(&y);
			}

			{
				pt->put_x(x1);
				pt->put_y(y1);
				CComQIPtr<ILSVGPoint> xpt;
				pt->matrixTransform(xform, &xpt);
				xpt->get_x(&x1);
				xpt->get_y(&y1);
			}

			{
				pt->put_x(x2);
				pt->put_y(y2);
				CComQIPtr<ILSVGPoint> xpt;
				pt->matrixTransform(xform, &xpt);
				xpt->get_x(&x2);
				xpt->get_y(&y2);
			}

			POINT ipt[3] =
			{
				x1, y1,
				x2, y2,
				x, y,
			};

			PolyBezierTo(iDC, ipt, 3);
		}
	}
}
#endif

void SetPathSegListToEllipse(Web::SVGPathSegList* seglist, double left, double top, double right, double bottom)
{
#if 0
	double width = right-left;
	double height = bottom-top;

    // MAGICAL CONSTANT to map ellipse to beziers
   //  			2/3*(sqrt(2)-1) 
    const double EToBConst =	0.2761423749154; 
    CDblPoint offset;
	 offset.x = width * EToBConst;
	 offset.y = height * EToBConst;

    CDblPoint centre;
	 centre.x = (left + right) / 2;
	 centre.y = (top + bottom) / 2;

	{
		CComQIPtr<ILSVGPathSegMovetoAbs> seg;
		seg.CoCreateInstance(CLSID_LSVGPathSegMovetoAbs);
		seg->put_x(left);	seg->put_y(centre.y);
		seglist->appendItem(seg, NULL);
	}

	{
		CComQIPtr<ILSVGPathSegCurvetoCubicAbs> seg;
		seg.CoCreateInstance(CLSID_LSVGPathSegCurvetoCubicAbs);
		seg->put_x(centre.x);	seg->put_y(top);
		seg->put_x1(left);		seg->put_y1(centre.y-offset.y);
		seg->put_x2(centre.x-offset.x);		seg->put_y2(top);
		seglist->appendItem(seg, NULL);
	}

	{
		CComQIPtr<ILSVGPathSegCurvetoCubicAbs> seg;
		seg.CoCreateInstance(CLSID_LSVGPathSegCurvetoCubicAbs);
		seg->put_x(right);						seg->put_y(centre.y);
		seg->put_x1(centre.x + offset.x);	seg->put_y1(top);
		seg->put_x2(right);						seg->put_y2(centre.y - offset.y);
		seglist->appendItem(seg, NULL);
	}

	{
		CComQIPtr<ILSVGPathSegCurvetoCubicAbs> seg;
		seg.CoCreateInstance(CLSID_LSVGPathSegCurvetoCubicAbs);
		seg->put_x(centre.x);				seg->put_y(bottom);
		seg->put_x1(right);				seg->put_y1(centre.y+offset.y);
		seg->put_x2(centre.x+offset.x);	seg->put_y2(bottom);
		seglist->appendItem(seg, NULL);
	}

	{
		CComQIPtr<ILSVGPathSegCurvetoCubicAbs> seg;
		seg.CoCreateInstance(CLSID_LSVGPathSegCurvetoCubicAbs);
		seg->put_x(left);						seg->put_y(centre.y);
		seg->put_x1(centre.x-offset.x);	seg->put_y1(bottom);
		seg->put_x2(left);					seg->put_y2(centre.y + offset.y);
		seglist->appendItem(seg, NULL);
	}

	{
		CComQIPtr<ILSVGPathSegClosePath> seg;
		seg.CoCreateInstance(CLSID_LSVGPathSegClosePath);
		seglist->appendItem(seg, NULL);
	}
#endif
}

void SetPathSegListToRoundRect(Web::SVGPathSegList* seglist, double left, double top, double right, double bottom, double rx, double ry, bool bOnlyCubic)
{
#if 0
	double width = right-left;
	double height = bottom-top;

	if (rx > width/2) rx = width/2;
	if (ry > height/2) ry = height/2;

    // MAGICAL CONSTANT to map ellipse to beziers
   //  			2/3*(sqrt(2)-1) 
    const double EToBConst =	0.2761423749154; 
    CDblPoint offset;
	 offset.x = rx*2 * EToBConst;
	 offset.y = ry*2 * EToBConst;

	{
		CComQIPtr<ILSVGPathSegMovetoAbs> seg;
		seg.CoCreateInstance(CLSID_LSVGPathSegMovetoAbs);
		seg->put_x(left+rx);	seg->put_y(top);
		seglist->appendItem(seg, NULL);
	}

	// top line
	if (bOnlyCubic)
	{
		CComQIPtr<ISVGPathSegCurvetoCubicAbs> seg;
		seg.CoCreateInstance(CLSID_SVGPathSegCurvetoCubicAbs);
		seg->put_x1(left+rx);		seg->put_y1(top);
		seg->put_x2(right-rx);		seg->put_y2(top);
		seg->put_x(right-rx);		seg->put_y(top);
		seglist->appendItem(seg, NULL);
	}
	else
	{
		CComQIPtr<ISVGPathSegLinetoAbs> seg;
		seg.CoCreateInstance(CLSID_SVGPathSegLinetoAbs);
		seg->put_x(right-rx);	seg->put_y(top);
		seglist->appendItem(seg, NULL);
	}

	{
		CComQIPtr<ISVGPathSegCurvetoCubicAbs> seg;
		seg.CoCreateInstance(CLSID_SVGPathSegCurvetoCubicAbs);
		seg->put_x1(right-rx+offset.x);		seg->put_y1(top);
		seg->put_x2(right);						seg->put_y2(top+ry-offset.y);
		seg->put_x(right);						seg->put_y(top+ry);
		seglist->appendItem(seg, NULL);
	}

// right line
	if (bOnlyCubic)
	{
		CComQIPtr<ISVGPathSegCurvetoCubicAbs> seg;
		seg.CoCreateInstance(CLSID_SVGPathSegCurvetoCubicAbs);
		seg->put_x1(right);		seg->put_y1(top+ry);
		seg->put_x2(right);		seg->put_y2(bottom-ry);
		seg->put_x(right);		seg->put_y(bottom-ry);
		seglist->appendItem(seg, NULL);
	}
	else
	{
		CComQIPtr<ISVGPathSegLinetoAbs> seg;
		seg.CoCreateInstance(CLSID_SVGPathSegLinetoAbs);
		seg->put_x(right);	seg->put_y(bottom-ry);
		seglist->appendItem(seg, NULL);
	}

	{
		CComQIPtr<ISVGPathSegCurvetoCubicAbs> seg;
		seg.CoCreateInstance(CLSID_SVGPathSegCurvetoCubicAbs);
		seg->put_x1(right);						seg->put_y1(bottom-ry+offset.y);
		seg->put_x2(right-rx+offset.x);		seg->put_y2(bottom);
		seg->put_x(right-rx);					seg->put_y(bottom);
		seglist->appendItem(seg, NULL);
	}

// bottom line
	if (bOnlyCubic)
	{
		CComQIPtr<ISVGPathSegCurvetoCubicAbs> seg;
		seg.CoCreateInstance(CLSID_SVGPathSegCurvetoCubicAbs);
		seg->put_x1(right-rx);			seg->put_y1(bottom);
		seg->put_x2(left+rx);		seg->put_y2(bottom);
		seg->put_x(left+rx);			seg->put_y(bottom);
		seglist->appendItem(seg, NULL);
	}
	else
	{
		CComQIPtr<ISVGPathSegLinetoAbs> seg;
		seg.CoCreateInstance(CLSID_SVGPathSegLinetoAbs);
		seg->put_x(left+rx);	seg->put_y(bottom);
		seglist->appendItem(seg, NULL);
	}

	{
		CComQIPtr<ISVGPathSegCurvetoCubicAbs> seg;
		seg.CoCreateInstance(CLSID_SVGPathSegCurvetoCubicAbs);
		seg->put_x1(left+rx-offset.x);	seg->put_y1(bottom);
		seg->put_x2(left);					seg->put_y2(bottom-ry+offset.y);
		seg->put_x(left);						seg->put_y(bottom-ry);
		seglist->appendItem(seg, NULL);
	}

// left line
	if (bOnlyCubic)
	{
		CComQIPtr<ISVGPathSegCurvetoCubicAbs> seg;
		seg.CoCreateInstance(CLSID_SVGPathSegCurvetoCubicAbs);
		seg->put_x1(left);	seg->put_y1(bottom-ry);
		seg->put_x2(left);	seg->put_y2(top+ry);
		seg->put_x(left);		seg->put_y(top+ry);
		seglist->appendItem(seg, NULL);
	}
	else
	{
		CComQIPtr<ISVGPathSegLinetoAbs> seg;
		seg.CoCreateInstance(CLSID_SVGPathSegLinetoAbs);
		seg->put_x(left);	seg->put_y(top+ry);
		seglist->appendItem(seg, NULL);
	}

	{
		CComQIPtr<ISVGPathSegCurvetoCubicAbs> seg;
		seg.CoCreateInstance(CLSID_SVGPathSegCurvetoCubicAbs);
		seg->put_x1(left);					seg->put_y1(top+ry-offset.y);
		seg->put_x2(left+rx-offset.x);	seg->put_y2(top);
		seg->put_x(left+rx);					seg->put_y(top);
		seglist->appendItem(seg, NULL);
	}
#endif
}

}
