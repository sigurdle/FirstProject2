#include "stdafx.h"
#include "LXUI2.h"
#include "LinearGradientBrush.h"
#include "GradientStop.h"
#include "GradientStopCollection.h"

namespace LDraw
{
double GetLineAngle(double x1, double y1, double x2, double y2);
}

namespace System
{
namespace UI
{

DependencyProperty* LinearGradientBrush::s_StartPointProperty = RegisterProperty(WSTR("StartPoint"), typeid(Point), typeid(LinearGradientBrush), new Point(0,0), PropertyMetaData(None));
DependencyProperty* LinearGradientBrush::s_EndPointProperty = RegisterProperty(WSTR("EndPoint"), typeid(Point), typeid(LinearGradientBrush), new Point(1,1), PropertyMetaData(None));

LinearGradientBrush::LinearGradientBrush()
{
}

LinearGradientBrush::LinearGradientBrush(Color StartColor, Color EndColor, Point startPoint, Point endPoint, double Opacity/* = 1*/)
{
	GradientStopCollection* gradientStops = new GradientStopCollection;
	gradientStops->Add(new GradientStop(0, StartColor));
	gradientStops->Add(new GradientStop(1, EndColor));

	set_StartPoint(startPoint);
	set_EndPoint(endPoint);
//	m_Opacity = Opacity;

	set_GradientStops(gradientStops);
}

#if 0
LinearGradientBrush::LinearGradientBrush(/*CLGradientStopCollection* GradientStops,*/ Point* StartPoint, Point* EndPoint, double Opacity/* = 1*/)
{
	//m_GradientStops = GradientStops;

	m_GradientStops = new CLGradientStopCollection;
	m_GradientStops->m_items.push_back(new CLGradientStop(0, new CLColor(240, 240, 240)));
	m_GradientStops->m_items.push_back(new CLGradientStop(1, new CLColor(180, 180, 180)));

	m_StartPoint = StartPoint;
	m_EndPoint = EndPoint;
	m_Opacity = Opacity;
}
#endif

__release<LDraw::Brush> LinearGradientBrush::CreateBrush(UIElement* pReferencingElement, double scaleX, double scaleY)
{
	double x1, y1;
	double x2, y2;

	Point startPoint = get_StartPoint();
	Point endPoint = get_EndPoint();

	x1 = startPoint.get_X();
	y1 = startPoint.get_Y();
	x2 = endPoint.get_X();
	y2 = endPoint.get_Y();

	x1 = pReferencingElement->m_expandedBBox.X + x1*pReferencingElement->m_expandedBBox.Width;
	y1 = pReferencingElement->m_expandedBBox.Y + y1*pReferencingElement->m_expandedBBox.Height;
	x2 = pReferencingElement->m_expandedBBox.X + x2*pReferencingElement->m_expandedBBox.Width;
	y2 = pReferencingElement->m_expandedBBox.Y + y2*pReferencingElement->m_expandedBBox.Height;

	if (m_stops == NULL)
	{
		GradientStopCollection* pStopCollection = get_GradientStops();

		if (pStopCollection)
		{
			vector<float> offsets;
			vector<LDraw::Color> colors;

			pStopCollection->CreateGradientStops(offsets, colors);

			m_stops = new LDraw::GradientStops(LDraw::PixelFormat_t::RGBAP_32);
			m_stops->SetInterpolationColors(colors.GetData(), offsets.GetData(), colors.GetSize());
		}
	}

	if (m_stops)
	{
		return new LDraw::LinearGradientBrush(m_stops, x1, y1, x2, y2);
	}

	return NULL;
}

__release<LDraw::Brush> LinearGradientBrush::CreateBrush(const LDraw::RectD& refRect, LDraw::Matrix3f* transform, double scaleX, double scaleY)
{
	Point startPoint = get_StartPoint();
	Point endPoint = get_EndPoint();

	LDraw::PointF start;
	LDraw::PointF end;
	start.X = startPoint.get_X();
	start.Y = startPoint.get_Y();
	end.X = endPoint.get_X();
	end.Y = endPoint.get_Y();

	start = transform->Transform(start);
	end = transform->Transform(end);

	start.X = refRect.X + start.X*refRect.Width;
	start.Y = refRect.Y + start.Y*refRect.Height;
	end.X = refRect.X + end.X*refRect.Width;
	end.Y = refRect.Y + end.Y*refRect.Height;

	if (m_stops == NULL)
	{
		GradientStopCollection* pStopCollection = get_GradientStops();

		if (pStopCollection)
		{
			vector<float> offsets;
			vector<LDraw::Color> colors;

			pStopCollection->CreateGradientStops(offsets, colors);

			m_stops = new LDraw::GradientStops(LDraw::PixelFormat_t::RGBAP_32);
			m_stops->SetInterpolationColors(colors.GetData(), offsets.GetData(), colors.GetSize());
		}
	}

	if (m_stops)
	{
		return new LDraw::LinearGradientBrush(m_stops, start, end);
	}

	return NULL;
}

Point LinearGradientBrush::get_StartPoint()
{
	return *static_cast<Point*>(GetValue(get_StartPointProperty()));
}

void LinearGradientBrush::set_StartPoint(Point startPoint)
{
	SetValue(get_StartPointProperty(), new Point(startPoint));
}

Point LinearGradientBrush::get_EndPoint()
{
	return *static_cast<Point*>(GetValue(get_EndPointProperty()));
}

void LinearGradientBrush::set_EndPoint(Point endPoint)
{
	SetValue(get_EndPointProperty(), new Point(endPoint));
}

}	// UI
}
