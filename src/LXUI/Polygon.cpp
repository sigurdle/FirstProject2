#include "stdafx.h"
#include "LXUI2.h"
#include "Polygon.h"

namespace System
{
namespace UI
{
namespace Shapes
{

DependencyProperty* Polygon::s_PointsProperty = RegisterProperty(WSTR("Points"), typeid(PointCollection), typeid(Polygon), NULL, PropertyMetaData(AffectsMeasure));

Polygon::Polygon()
{
//	SetClipMode(false);
}

Polygon::~Polygon()
{
}

LDraw::SizeD Polygon::MeasureOverride(LDraw::SizeD availSize)
{
	PointCollection* Points = get_Points();

	if (Points)
	{
		unsigned int count = Points->GetCount();

		if (count > 0)
		{
			__release<LDraw::GraphicsPathF> path = new LDraw::GraphicsPathF;

			//CLXUIPoint* pOldPoint = static_cast<CLXUIPoint*>(points->m_items[0]);

			Point point = Points->get_Item(0);
			path->AddMove(point.X, point.Y);

			for (unsigned int i = 1; i < count; i++)
			{
				point = Points->get_Item(i);
				path->AddLine(point.X, point.Y);

			//	CLXUIPoint* pPoint = static_cast<CLXUIPoint*>(points->m_items[i]);
			//	path.AddLine(float(pOldPoint->m_X), float(pOldPoint->m_Y), float(pPoint->m_X), float(pPoint->m_Y));
			//	pOldPoint = pPoint;
			}

			LDraw::RectF rect;
			path->GetBounds(&rect, NULL, NULL);

			return LDraw::SizeD(rect.Width, rect.Height);
		}
	}

	return LDraw::SizeD(0, 0);
}

// virtual
void Polygon::OnRender(Graphics* pGraphics)
{
	PointCollection* Points = get_Points();

	if (Points)
	{
		unsigned int count = Points->GetCount();

		if (count > 0)
		{
			__release<LDraw::GraphicsPathF> path = new LDraw::GraphicsPathF;

			Point point = Points->get_Item(0);
			path->AddMove(point.X, point.Y);

			for (unsigned int i = 1; i < count; i++)
			{
				point = Points->get_Item(i);
				path->AddLine(point.X, point.Y);

			//	CLXUIPoint* pPoint = static_cast<CLXUIPoint*>(points->m_items[i]);
			//	path.AddLine(float(pOldPoint->m_X), float(pOldPoint->m_Y), float(pPoint->m_X), float(pPoint->m_Y));
			//	pOldPoint = pPoint;
			}

			Brush* Fill = get_Fill();
			if (Fill)
			{
				__release<LDraw::Brush> brush = Fill->CreateBrush(this, 1, 1);
				if (brush != NULL)
				{
					pGraphics->FillPath(brush, path);
				}
			}

#if 0
			double StrokeThickness;
			if (m_StrokeThickness)
				m_StrokeThickness->get_Value(&StrokeThickness);
			else
				StrokeThickness = 1;

			if (StrokeThickness > 0)
			{
				CComQIPtr<CLXUIElementImplImpl> Stroke(m_Stroke);
				if (Stroke)
				{
					Gdiplus::Brush* pBrush = Stroke->CreateBrush(this, 1, 1);
					if (pBrush)
					{
						Gdiplus::Pen pen(pBrush, StrokeThickness);

						pGraphics->DrawPath(pen, &path);
						delete pBrush;
					}
				}
			}
#endif
		}

	}
}

PointCollection* Polygon::get_Points()
{
	return static_cast<PointCollection*>(GetValue(get_PointsProperty()));
}

void Polygon::set_Points(PointCollection* points)
{
	SetValue(get_PointsProperty(), points);
}

}	// Shapes
}	// UI
}
