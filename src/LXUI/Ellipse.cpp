#include "stdafx.h"
#include "LXUI2.h"
#include "Ellipse.h"

namespace System
{
namespace UI
{
namespace Shapes
{

Ellipse::Ellipse()
{
	/*
	m_CenterX = NULL;
	m_CenterY = NULL;
	m_RadiusX = NULL;
	m_RadiusY = NULL;
	*/

	SetClipMode(false);
}

Ellipse::~Ellipse()
{
}

#if 0
LDraw::SizeD Ellipse::Measure(LDraw::SizeD availSize)
{
	return Shape::OnMeasure(availSize);
	/*
	double CenterX;
	double CenterY;
	double RadiusX;
	double RadiusY;
	CenterX = m_CenterX->get_Value();
	CenterY = m_CenterY->get_Value();
	RadiusX = m_RadiusX->get_Value();
	RadiusY = m_RadiusY->get_Value();

	m_RenderBounds.X = CenterX-RadiusX;
	m_RenderBounds.Y = CenterY-RadiusY;
	m_RenderBounds.Width = RadiusX*2;
	m_RenderBounds.Height = RadiusY*2;

	return LDraw::SizeD(m_RenderBounds.Width, m_RenderBounds.Height);
	*/
}

// TODO ???
void Ellipse::OnArrange(LDraw::SizeD finalSize)
{
	Shape::OnArrange(finalSize);
//	m_expandedBBox = m_RenderBounds;
}
#endif

// virtual
void Ellipse::OnRender(Graphics* pGraphics)
{
	/*
	double CenterX;
	double CenterY;
	double RadiusX;
	double RadiusY;
	CenterX = m_CenterX->get_Value();
	CenterY = m_CenterY->get_Value();
	RadiusX = m_RadiusX->get_Value();
	RadiusY = m_RadiusY->get_Value();
	*/

	/*
	pGraphics->FillEllipse(&Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 0)),
		float(CenterX-RadiusX), float(CenterY-RadiusY), float(RadiusX*2), RadiusY*2);
		*/

	LDraw::SizeD actualSize = get_ActualSize();

	Brush* Fill = get_Fill();
	if (Fill)
	{
		__release<LDraw::Brush> brush = Fill->CreateBrush(this, 1, 1);
		if (brush != NULL)
		{
			pGraphics->FillEllipse(brush, 0, 0, actualSize.Width, actualSize.Height);
#if 0
			pGraphics->Clear(LDraw::Color(255, 0, 0));
		//	pGraphics->FillPath(pBrush, &path);
#endif
		}
	}
}

/*
Length* Ellipse::get_CenterX()
{
	return m_CenterX;
}

void Ellipse::set_CenterX(Length* newVal)
{
	m_CenterX = newVal;
}

Length* Ellipse::get_CenterY()
{
	return m_CenterY;
}

void Ellipse::set_CenterY(Length* newVal)
{
	m_CenterY = newVal;
}

Length* Ellipse::get_RadiusX()
{
	return m_RadiusX;
}

void Ellipse::set_RadiusX(Length* newVal)
{
	m_RadiusX = newVal;
}

Length* Ellipse::get_RadiusY()
{
	return m_RadiusY;
}

void Ellipse::set_RadiusY(Length* newVal)
{
	m_RadiusY = newVal;
}
*/

}	// Shapes
}	// UI
}
