#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(bool, PathFigure, Closed, true)

DependencyClass* PathFigure::get_Class()
{
	static DependencyClass depclass(typeid(PathFigure), DependencyObject::get_Class());

	static DependencyProperty* properties[] =
	{
		get_ClosedProperty(),
	};

	return &depclass;
}

DependencyClass* PathFigure::pClass(get_Class());

PathFigure::PathFigure() : DependencyObject(get_Class())
{
}

void PathFigure::LineTo(gm::PointF point)
{
	LineToPathSegment* seg = new LineToPathSegment(point);
	m_segments.push_back(seg);

	/*
	if (m_D2DGeometry)
	{
		m_D2DGeometry->Release();
		m_D2DGeometry = NULL;
	}
	*/

	// TODO, change callback

}

void PathFigure::Sink(ID2D1GeometrySink* pGeometrySink)
{
	if (m_segments.size())
	{
		gm::PointF startPoint;

		auto it = m_segments.begin();

		LineToPathSegment* lineTo = dynamic_cast<LineToPathSegment*>(*it);
		if (lineTo)
		{
			pGeometrySink->BeginFigure(
				cnv(lineTo->get_Point()),
				D2D1_FIGURE_BEGIN_FILLED);

			++it;
		}
		else
		{
			pGeometrySink->BeginFigure(
				D2D1::Point2F(0,0),
				D2D1_FIGURE_BEGIN_FILLED);
		}

		for (; it != m_segments.end(); ++it)
		{
			PathSegment* segment = *it;

			segment->Sink(pGeometrySink);
		}

		pGeometrySink->EndFigure(get_Closed()? D2D1_FIGURE_END_CLOSED : D2D1_FIGURE_END_OPEN);
	}
}

}	// Gui
}	// System
