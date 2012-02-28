#include "stdafx.h"
#include "PageDesigner.h"
#include "PathSelection.h"
#include "PDObjectSelected.h"

void DrawThreadRectArrow(Gdiplus::Graphics* pGraphics, Gdiplus::SolidBrush* pBrush, Gdiplus::Rect rc, double rotation)
{
	if (rotation < 45 || rotation >= 315)
	{
		Gdiplus::Point pts[3] =
		{
			Gdiplus::Point(rc.X+3, rc.Y+2),
			Gdiplus::Point(rc.X+3, rc.Y+2+6),
			Gdiplus::Point(rc.X+3+3, rc.Y+2+3),
		};

		pGraphics->FillPolygon(pBrush, pts, 3);
	}
	else if (rotation < 135)
	{
		Gdiplus::Point pts[3] =
		{
			Gdiplus::Point(rc.X+2, rc.Y+3),
			Gdiplus::Point(rc.X+2+6, rc.Y+3),
			Gdiplus::Point(rc.X+2+3, rc.Y+3+3),
		};

		pGraphics->FillPolygon(pBrush, pts, 3);
	}
	else if (rotation < 225)
	{
		Gdiplus::Point pts[3] =
		{
			Gdiplus::Point(rc.X+3+3, rc.Y+2),
			Gdiplus::Point(rc.X+3+3, rc.Y+2+6),
			Gdiplus::Point(rc.X+3, rc.Y+2+3),
		};

		pGraphics->FillPolygon(pBrush, pts, 3);
	}
	else if (rotation < 315)
	{
		Gdiplus::Point pts[3] =
		{
			Gdiplus::Point(rc.X+2, rc.Y+3+3),
			Gdiplus::Point(rc.X+2+6, rc.Y+3+3),
			Gdiplus::Point(rc.X+2+3, rc.Y+3),
		};

		pGraphics->FillPolygon(pBrush, pts, 3);
	}
	else
		ATLASSERT(0);
}

CPDObjectSelected::~CPDObjectSelected()
{
	delete m_wrapPath;
	m_wrapPath = NULL;
}

void CPDObjectSelected::SetWrapPath()
{
	CComQIPtr<IPDObjectWrappable> objectWrappable = m_object;
	if (objectWrappable)
	{
		CComPtr<IPDPath> pdpath;
		objectWrappable->get_wrapPath(&pdpath);
		if (pdpath)
		{
			m_wrapPath = new CPathSelection(pdpath, (IPDObject*)m_object);
		}
		else
		{
			delete m_wrapPath;
			m_wrapPath = NULL;
		}
	}
}

////////////

CPDObjectFrameSelected::CPDObjectFrameSelected(IPDObjectUnknown* object, BOOL bSelectPoints) : CPDObjectSelected(object)
{
	m_path = NULL;

//	CalculateThreadRects();	// ??

	CComQIPtr<IPDObjectFrame> frame = object;
	CComPtr<IPDPath> pdpath;
	frame->get_path(&pdpath);
	m_path = new CPathSelection(pdpath, frame);

	if (bSelectPoints)
	{
		m_path->SelectAllAnchors();
	}
}

CPDObjectFrameSelected::~CPDObjectFrameSelected()
{
	delete m_path;
	m_path = NULL;
}

void CPDObjectFrameSelected::DrawThreadRects(Gdiplus::Graphics* pGraphics, Gdiplus::Color& color, IPDMatrix* matrix)
{
	Gdiplus::Pen pen(color);
	Gdiplus::SolidBrush brush(color);

	CComQIPtr<IPDObjectFrame> frame = m_object;

	if (frame)
	{
		CComPtr<IPDObject> content;
		frame->get_content(&content);

		CComQIPtr<IPDContentText> contentText = content;
		if (contentText)
		{
			PointD m_threadPtLeft;
			PointD m_threadPtRight;

			contentText->get_threadPtIn(&m_threadPtLeft);
			contentText->get_threadPtOut(&m_threadPtRight);

			double rotation;
			matrix->getRotation(&rotation);

			CComPtr<IPDObjectText> previousContentText;
			contentText->get_previousTextThread(&previousContentText);

			CComPtr<IPDObjectText> nextContentText;
			contentText->get_nextTextThread(&nextContentText);

			Gdiplus::SolidBrush whiteBrush(Gdiplus::Color(255, 255, 255));

			{
				PointD xpt;
				matrix->transformPoint(&m_threadPtLeft, &xpt);

				Gdiplus::Rect rc(xpt.x-4, xpt.y-4, 9, 9);
				pGraphics->FillRectangle(&whiteBrush, rc);
				pGraphics->DrawRectangle(&pen, rc);

				if (previousContentText != NULL)
				{
					DrawThreadRectArrow(pGraphics, &brush, rc, rotation);
				}
			}

			{
				PointD xpt;
				matrix->transformPoint(&m_threadPtRight, &xpt);

				Gdiplus::Rect rc(xpt.x-4, xpt.y-4, 9, 9);

				pGraphics->FillRectangle(&whiteBrush, rc);

				VARIANT_BOOL overflow;
				contentText->get_overflow(&overflow);

				if (nextContentText != NULL)
				{
					pGraphics->DrawRectangle(&pen, rc);
					DrawThreadRectArrow(pGraphics, &brush, rc, rotation);
				}
				else
				{
					if (overflow)
					{
						Gdiplus::Pen redPen(Gdiplus::Color(255, 0, 0), 1);
						pGraphics->DrawRectangle(&redPen, rc);

						pGraphics->DrawLine(&redPen, rc.X+rc.Width/2, rc.Y+2, rc.X+rc.Width/2, rc.GetBottom()-1);
						pGraphics->DrawLine(&redPen, rc.X+2, rc.Y+rc.Height/2, rc.GetRight()-1, rc.Y+rc.Height/2);
					}
					else
					{
						pGraphics->DrawRectangle(&pen, rc);
					}
				}
			}
		}

		CComPtr<IPDPathText> pathText;
		frame->get_pathText(&pathText);

		if (pathText)
		{
			CComPtr<IPDMatrix> mat0;
			mat0.CoCreateInstance(CLSID_PDMatrix);

			CComPtr<IPDMatrix> mat1;
			mat0->translate(-m_pthreadPtLeft.x, -m_pthreadPtLeft.y, &mat1);

			CComPtr<IPDMatrix> mat2;
			mat1->rotate(m_pthreadRotationLeft, &mat2);

			CComPtr<IPDMatrix> mat3;
			mat2->translate(m_pthreadPtLeft.x, m_pthreadPtLeft.y, &mat3);

			CComPtr<IPDMatrix> mat;
			mat3->multiply(matrix, &mat);

			double x = m_pthreadPtLeft.x;
			double y = m_pthreadPtLeft.y;
		//
			{
				PointD xpt1;
				mat->transformPoint((PointD*)&CDblPoint(x, y), &xpt1);

				PointD xpt2;
				mat->transformPoint((PointD*)&CDblPoint(x, y+20), &xpt2);

				pGraphics->DrawLine(&pen, (float)xpt1.x, (float)xpt1.y, (float)xpt2.x, (float)xpt2.y);
			}

			{
				PointD pts[4] =
				{
					x, y,
					x-12, y,
					x-12, y+12,
					x, y+12
				};

				PointD xpts[4];
				for (int i = 0; i < 4; i++)
				{
					mat->transformPoint(&pts[i], &xpts[i]);
				}

				pGraphics->DrawLine(&pen, (float)xpts[0].x, (float)xpts[0].y, (float)xpts[1].x, (float)xpts[1].y);
				pGraphics->DrawLine(&pen, (float)xpts[1].x, (float)xpts[1].y, (float)xpts[2].x, (float)xpts[2].y);
				pGraphics->DrawLine(&pen, (float)xpts[2].x, (float)xpts[2].y, (float)xpts[3].x, (float)xpts[3].y);
				pGraphics->DrawLine(&pen, (float)xpts[3].x, (float)xpts[3].y, (float)xpts[0].x, (float)xpts[0].y);
			}
		}
	}
}

#if 0
void CPDObjectFrameSelected::FindThreadPts(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3)
{
	CComQIPtr<IPDObjectTransformable> objectTransformable = m_object;

	RectD bounds;
	objectTransformable->get_bounds(&bounds);

	double ax, ay, bx, by, cx, cy;

	cx = 3 * (x1 - x0);
	cy = 3 * (y1 - y0);
	bx = 3 * (x2 - x1) - cx;
	by = 3 * (y2 - y1) - cy;
	ax = x3 - x0 - cx - bx;
	ay = y3 - y0 - cy - by;

	double tinc = 1/50.0;

	for (double t = 0.0; t <= 1.0; t += tinc)
	{
		double xt = ax * t*t*t + bx * t*t + cx * t + x0;
		double yt = ay * t*t*t + by * t*t + cy * t + y0;

		if (yt < m_topSoFar && yt > bounds.Y+10)
		{
			m_topSoFar = yt;

			m_threadPtLeft.x = xt;
			m_threadPtLeft.y = yt;
		}

		if (yt > m_bottomSoFar  && yt < bounds.Y+bounds.Height-10)
		{
			m_bottomSoFar = yt;

			m_threadPtRight.x = xt;
			m_threadPtRight.y = yt;
		}
	}
}

void CPDObjectFrameSelected::CalculateThreadRects()
{
	CComQIPtr<IPDObjectFrame> frame = m_object;

	if (frame)
	{
		CComPtr<IPDPath> pdpath;
		frame->get_path(&pdpath);

		m_topSoFar =		9999999;
		m_bottomSoFar = - 9999999;

		long nsubpaths;
		pdpath->get_subPathCount(&nsubpaths);

		for (int i = 0; i < nsubpaths; i++)
		{
			CComPtr<IPDSubPath> subpath;
			pdpath->getSubPath(i, &subpath);

			long npoints;
			subpath->get_pointCount(&npoints);

			if (npoints > 1)
			{
				BezierPoint point;
				subpath->getPoint(0, &point);

				BezierPoint xpoint[2];
				xpoint[0] = point;

				for (int npt = 1; npt < npoints; npt++)
				{
					subpath->getPoint(npt, &point);
					xpoint[1] = point;

					FindThreadPts((float)xpoint[0].x, (float)xpoint[0].y,
						(float)xpoint[0].x2, (float)xpoint[0].y2,
						(float)xpoint[1].x1, (float)xpoint[1].y1,
						(float)xpoint[1].x, (float)xpoint[1].y);

					xpoint[0] = xpoint[1];
				}

				VARIANT_BOOL closed;
				subpath->get_closed(&closed);

				if (closed)
				{
					subpath->getPoint(0, &point);
					xpoint[1] = point;

					FindThreadPts(
						(float)xpoint[0].x, (float)xpoint[0].y,
						(float)xpoint[0].x2, (float)xpoint[0].y2,
						(float)xpoint[1].x1, (float)xpoint[1].y1,
						(float)xpoint[1].x, (float)xpoint[1].y);
				}
			}
		}

		CComPtr<IPDPathText> pathText;
		frame->get_pathText(&pathText);

		if (pathText)
		{
			CComPtr<IPDPath> path;
			frame->get_path(&path);

			CComPtr<IPDSubPath> subpath;
			path->getSubPath(0, &subpath);

			double startOnLength;
			pathText->get_startOnLength(&startOnLength);

			double endOnLength;
			pathText->get_endOnLength(&endOnLength);

			subpath->getPointOnLength(startOnLength, &m_pthreadPtLeft.x, &m_pthreadPtLeft.y, &m_pthreadRotationLeft);
			subpath->getPointOnLength(endOnLength, &m_pthreadPtRight.x, &m_pthreadPtRight.y, &m_pthreadRotationRight);
		}
	}
}
#endif
