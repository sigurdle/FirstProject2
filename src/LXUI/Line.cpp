#include "stdafx.h"
#include "LXUI2.h"
#include "Line.h"

#include <cfloat>

namespace System
{
namespace UI
{
namespace Shapes
{

DependencyProperty* Line::s_X1Property = RegisterProperty(WSTR("X1"), typeid(double), typeid(Line), DoubleObject::GetObject(0), PropertyMetaData(AffectsMeasure));
DependencyProperty* Line::s_Y1Property = RegisterProperty(WSTR("Y1"), typeid(double), typeid(Line), DoubleObject::GetObject(0), PropertyMetaData(AffectsMeasure));
DependencyProperty* Line::s_X2Property = RegisterProperty(WSTR("X2"), typeid(double), typeid(Line), DoubleObject::GetObject(0), PropertyMetaData(AffectsMeasure));
DependencyProperty* Line::s_Y2Property = RegisterProperty(WSTR("Y2"), typeid(double), typeid(Line), DoubleObject::GetObject(0), PropertyMetaData(AffectsMeasure));

Line::Line()
{
	SetClipMode(false);
}

Line::Line(double x1, double y1, double x2, double y2)
{
	set_X1(x1);
	set_Y1(y1);
	set_X2(x2);
	set_Y2(y2);

	SetClipMode(false);
}

Line::~Line()
{
}

double Line::get_X1()
{
	return static_cast<DoubleObject*>(GetValue(get_X1Property()))->GetValue();
}

void Line::set_X1(double x1)
{
	SetValue(get_X1Property(), DoubleObject::GetObject(x1));
}

double Line::get_Y1()
{
	return static_cast<DoubleObject*>(GetValue(get_Y1Property()))->GetValue();
}

void Line::set_Y1(double y1)
{
	SetValue(get_Y1Property(), DoubleObject::GetObject(y1));
}

double Line::get_X2()
{
	return static_cast<DoubleObject*>(GetValue(get_X2Property()))->GetValue();
}

void Line::set_X2(double x2)
{
	SetValue(get_X2Property(), DoubleObject::GetObject(x2));
}

double Line::get_Y2()
{
	return static_cast<DoubleObject*>(GetValue(get_Y2Property()))->GetValue();
}

void Line::set_Y2(double y2)
{
	SetValue(get_Y2Property(), DoubleObject::GetObject(y2));
}

LDraw::SizeD Line::MeasureOverride(LDraw::SizeD availSize)
{
	LDraw::RectD m_RenderBounds;

	double x1= get_X1();
	double y1 = get_Y1();
	double x2 = get_X2();
	double y2 = get_Y2();

	if (!_isnan(x1) && !_isnan(y1) && !_isnan(x2) && !_isnan(y2))
	{
		m_RenderBounds.X = MIN(x1,x2);
		m_RenderBounds.Y = MIN(y1,y2);
		m_RenderBounds.Width = MAX(x1,x2) - m_RenderBounds.X;
		m_RenderBounds.Height = MAX(y1,y2) - m_RenderBounds.Y;

#if 0
		m_computedLeft = m_RenderBounds.X;
		m_computedTop = m_RenderBounds.Y;
#endif
	}
	else
	{
		m_RenderBounds.X = 0;
		m_RenderBounds.Y = 0;
		m_RenderBounds.Width = 0;
		m_RenderBounds.Height = 0;
	}

	return LDraw::SizeD(m_RenderBounds.Width, m_RenderBounds.Height);
}

/*
// TODO, not here
void Line::Arrange(LDraw::SizeD finalSize)
{
// TODO, not here
//	m_expandedBBox = m_RenderBounds;
	Shape::ArrangeOverride(finalSize);
}
*/

// virtual
void Line::OnRender(Graphics* pGraphics)
{
//	if (!m_X1.IsNull() && !m_Y1.IsNull() && !m_X2.IsNull() && !m_Y2.IsNull())

	double x1= get_X1();
	double y1 = get_Y1();
	double x2 = get_X2();
	double y2 = get_Y2();

	if (!_isnan(x1) && !_isnan(y1) && !_isnan(x2) && !_isnan(y2))
	{
		x1 -= m_computedLeft;
		y1 -= m_computedTop;
		x2 -= m_computedLeft;
		y2 -= m_computedTop;

//		Gdiplus::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
//		pGraphics->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);

		double StrokeThickness = get_StrokeThickness();

		//double StrokeThickness;
	//	if (pStrokeThickness)
		//	StrokeThickness = pStrokeThickness->get_Value();
	//	else
	//		StrokeThickness = 1;

		if (StrokeThickness > 0)
		{
			Brush* pStroke = get_Stroke();
			if (pStroke)
			{
				__release<LDraw::Brush> pBrush = pStroke->CreateBrush(this, 1, 1);
				if (pBrush != NULL)
				{
					__release<LDraw::Pen> pen = new LDraw::Pen(pBrush, StrokeThickness);

					pGraphics->DrawLine(pen, float(x1), float(y1), float(x2), float(y2));
				}
			}
		}

//		pGraphics->SetSmoothingMode(oldSmoothingMode);
	}
}

// static
DependencyProperty* Line::get_X1Property()
{
	return s_X1Property;
}

// static
DependencyProperty* Line::get_Y1Property()
{
	return s_Y1Property;
}

// static
DependencyProperty* Line::get_X2Property()
{
	return s_X2Property;
}

// static
DependencyProperty* Line::get_Y2Property()
{
	return s_Y2Property;
}

}	// Shapes
}	// UI
}
