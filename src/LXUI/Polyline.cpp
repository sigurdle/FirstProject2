#include "stdafx.h" 
#include "LXUI2.h"
#include "Polyline.h"

namespace System
{
namespace UI
{
namespace Shapes
{

DependencyProperty* Polyline::s_PointsProperty = RegisterProperty(WSTR("Points"), typeid(PointCollection), typeid(Polyline), NULL, PropertyMetaData(AffectsMeasure));

Polyline::Polyline()
{
//	SetClipMode(false);
}

Polyline::~Polyline()
{
}

LDraw::SizeD Polyline::MeasureOverride(LDraw::SizeD availSize)
{
	PointCollection* points = get_Points();

	if (points)
	{
		int count = points->GetCount();

		if (count > 0)
		{
			__release<LDraw::GraphicsPathF> path = new LDraw::GraphicsPathF;

			//CLXUIPoint* pOldPoint = static_cast<CLXUIPoint*>(points->m_items[0]);

			Point point = points->get_Item(0);
			path->AddMove(point.X, point.Y);

			for (int i = 1; i < count; i++)
			{
				point = points->get_Item(i);
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
void Polyline::OnRender(Graphics* pGraphics)
{
	PointCollection* points = get_Points();

	if (points)
	{
		unsigned int count = points->GetCount();
		if (count > 0)
		{
			__release<LDraw::GraphicsPathF> path = new LDraw::GraphicsPathF;

			Point point = points->get_Item(0);
			path->AddMove(point.X, point.Y);

			for (unsigned int i = 1; i < count; i++)
			{
				point = points->get_Item(i);
				path->AddLine(point.X, point.Y);
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

PointCollection* Polyline::get_Points()
{
	return static_cast<PointCollection*>(GetValue(get_PointsProperty()));
}

void Polyline::set_Points(PointCollection* newVal)
{
	SetValue(get_PointsProperty(), newVal);
}

}	// Shapes
}	// UI
}
