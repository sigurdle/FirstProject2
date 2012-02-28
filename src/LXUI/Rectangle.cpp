#include "stdafx.h"
#include "LXUI2.h"
#include "Rectangle.h"

namespace System
{
namespace UI
{
namespace Shapes
{

DependencyProperty* Rectangle::s_RadiusXProperty = RegisterProperty(WSTR("RadiusX"), typeid(double), typeid(Rectangle), DoubleObject::GetObject(0), PropertyMetaData(AffectsRender));
DependencyProperty* Rectangle::s_RadiusYProperty = RegisterProperty(WSTR("RadiusY"), typeid(double), typeid(Rectangle), DoubleObject::GetObject(0), PropertyMetaData(AffectsRender));

Rectangle::Rectangle()
{
//	m_RadiusX = NULL;
//	m_RadiusY = NULL;

	SetClipMode(false);

	/*
	m_RectangleLeft = NULL;
	m_RectangleTop = NULL;
	m_RectangleWidth = NULL;
	m_RectangleHeight = NULL;
	m_RadiusX = NULL;
	m_RadiusY = NULL;
	*/
}

Rectangle::~Rectangle()
{
}

DependencyProperty* Rectangle::get_RadiusXProperty()
{
	return s_RadiusXProperty;
}

DependencyProperty* Rectangle::get_RadiusYProperty()
{
	return s_RadiusYProperty;
}

#if 0
LDraw::SizeD Rectangle::MeasureOverride(LDraw::SizeD availSize)
{
	if (m_RadiusX != NULL)
	{
		double Value = m_RadiusX->get_Value();
		if (m_RadiusX->get_UnitType() == LengthUnits::Percentage)
		{
			m_computedRadiusX = Value * availSize.Width;
		}
		else
		{
			m_computedRadiusX = Value;
		}
	}
	else
	{
		m_computedRadiusX = 0;
	}

	if (m_RadiusY != NULL)
	{
		double Value = m_RadiusY->get_Value();
		if (m_RadiusY->get_UnitType() == LengthUnits::Percentage)
		{
			m_computedRadiusY = Value * availSize.Height;
		}
		else
		{
			m_computedRadiusY = Value;
		}
	}
	else
	{
		m_computedRadiusY = 0;
	}

	return Shape::MeasureOverride(availSize);

	/*
	if (!m_RectangleLeft.IsNull())
	{
		double Value = m_RectangleLeft.get_Value();
		if (m_RectangleLeft.get_UnitType() == Length::UnitPercentage)
		{
			m_computedRectangleLeft = Value * availSize.Width;
		}
		else
		{
			m_computedRectangleLeft = Value;
		}
	}
	else
	{
		m_computedRectangleLeft = 0;
	}

	if (!m_RectangleTop.IsNull())
	{
		double Value = m_RectangleTop.get_Value();
		if (m_RectangleTop.get_UnitType() == Length::UnitPercentage)
		{
			m_computedRectangleTop = Value * availSize.Height;
		}
		else
		{
			m_computedRectangleTop = Value;
		}
	}
	else
	{
		m_computedRectangleTop = 0;
	}

	if (!m_RectangleWidth.IsNull())
	{
		double Value = m_RectangleWidth.get_Value();
		if (m_RectangleWidth.get_UnitType() == Length::UnitPercentage)
		{
			m_computedRectangleWidth = Value * availSize.Width;
		}
		else
		{
			m_computedRectangleWidth = Value;
		}
	}
	else
	{
		m_computedRectangleWidth = 0;
	}

	if (!m_RectangleHeight.IsNull())
	{
		double Value = m_RectangleHeight.get_Value();
		if (m_RectangleHeight.get_UnitType() == Length::UnitPercentage)
		{
			m_computedRectangleHeight = Value * availSize.Height;
		}
		else
		{
			m_computedRectangleHeight = Value;
		}
	}
	else
	{
		m_computedRectangleHeight = 0;
	}
	*/

/*
	m_RenderBounds.X = m_computedRectangleLeft;
	m_RenderBounds.Y = m_computedRectangleTop;
	m_RenderBounds.Width = m_computedRectangleWidth;
	m_RenderBounds.Height = m_computedRectangleHeight;

	m_expandedBBox = m_RenderBounds;

	return LDraw::SizeD(m_computedRectangleWidth, m_computedRectangleHeight);
	*/
}
#endif

LDraw::SizeD Rectangle::ArrangeOverride(LDraw::SizeD finalSize)
{
	m_computedRadiusX = get_RadiusX();
	m_computedRadiusY = get_RadiusY();

	return finalSize;
//	Shape::OnArrange(finalSize);
	//m_expandedBBox = m_RenderBounds;
}

// virtual
bool Rectangle::HitTest(double x, double y/*, long pointerEvents*/)
{
	// TODO
	return true;
}

// virtual
__release<LDraw::Region> Rectangle::OnGetOpaqueRegion(LDraw::Matrix3f* transform)
{
	LDraw::PointD xpt = transform->Transform(LDraw::PointD(m_expandedBBox.X, m_expandedBBox.Y));

	m_bDrawsOutsideOpaqueRegion = false;
	return new LDraw::Region(LDraw::RectI(xpt.X, xpt.Y, m_expandedBBox.Width, m_expandedBBox.Height));
}

#if 0
// virtual
void Rectangle::Clip(Graphics* pGraphics, LDraw::Region * rgn)
{
	//LDraw::Matrix3f oldTransform = pGraphics->GetTransform();
	pGraphics->PushTransform();//m_transformMatrix);

	{
		LDraw::PointD xpt = pGraphics->GetTransform()->Transform(LDraw::PointD(m_expandedBBox.X, m_expandedBBox.Y));

		ASSERT(0);
#if 0
		rgn->Exclude(LDraw::RectI(xpt.X, xpt.Y, m_expandedBBox.Width, m_expandedBBox.Height));
#endif

		/*
		HRGN rect = CreateRectRgn(xpt[0], xpt[1], xpt[0]+m_expandedBBox.Width, xpt[1]+m_expandedBBox.Height);
		CombineRgn(rgn.m_hRgn, rgn.m_hRgn, rect, RGN_DIFF);
		DeleteObject(rect);
		*/
	}

	pGraphics->PopTransform();//oldTransform);
/*
	// The default is not to clip
	if (m_computedRectangleWidth > 0 && m_computedRectangleHeight > 0)
	{
		HRGN rect = CreateRectRgn(m_computedRectangleLeft, m_computedRectangleTop, m_computedRectangleWidth, m_computedRectangleHeight);
		CombineRgn(hRgn, hRgn, rect, RGN_DIFF);
		DeleteObject(rect);
	}
	*/
}
#endif

// virtual
void Rectangle::OnRender(Graphics* pGraphics)
{
	LDraw::SizeD actualSize = get_ActualSize();

	//if (m_computedRectangleWidth > 0 && m_computedRectangleHeight > 0)
	{
//		LDraw::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
	//	pGraphics->SetSmoothingMode(LDraw::SmoothingModeHighQuality);

//		__release<LDraw::GraphicsPathF> path = new LDraw::GraphicsPathF;
//#if _WINDOWS
//		RoundRect(&path, m_computedRectangleLeft, m_computedRectangleTop, m_computedRectangleWidth, m_computedRectangleHeight, m_computedRadiusX, m_computedRadiusY);
//#else
//		path->AddRoundRect(0, 0, actualSize.Width, actualSize.Height, m_computedRadiusX, m_computedRadiusY);
//#endif

//		pGraphics->FillPath(&LDraw::SolidBrush(LDraw::Color(255, 0, 0)), &path);

		Brush* Fill = get_Fill();
		if (Fill)
		{
			__release<LDraw::Brush> brush = Fill->CreateBrush(this, 1, 1);
			if (brush != NULL)
			{
				pGraphics->FillRectangle(brush, 0, 0, actualSize.Width, actualSize.Height);
#if 0
				pGraphics->FillRectangle(pBrush, m_computedRectangleLeft, m_computedRectangleTop, m_computedRectangleWidth, m_computedRectangleHeight);
				pGraphics->Clear(LDraw::Color(255, 0, 0));
				pGraphics->FillPath(brush, path);
#endif
			}
		}

#if 0//_WINDOWS
		double StrokeThickness;
		if (m_StrokeThickness)
			StrokeThickness = m_StrokeThickness->get_Value();
		else
			StrokeThickness = 1;

		if (StrokeThickness > 0)
		{
			CLXUIElementImpl* Stroke = m_Stroke;
			if (Stroke)
			{
				LDraw::Brush* pBrush = Stroke->CreateBrush(this, 1, 1);
				if (pBrush)
				{
					LDraw::Pen pen(pBrush, StrokeThickness);

					pGraphics->DrawPath(pen, &path);
					delete pBrush;
				}
			}
		}
#endif

	//	pGraphics->SetSmoothingMode(oldSmoothingMode);
//#elif AMIGA
//		pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 0, 0)), m_computedRectangleLeft, m_computedRectangleTop, m_computedRectangleWidth, m_computedRectangleHeight);
//#endif
	}
}

/*
Length Rectangle::get_RectangleLeft()
{
	return m_RectangleLeft;
}

void Rectangle::put_RectangleLeft(Length newVal)
{
	m_RectangleLeft = newVal;
}

Length Rectangle::get_RectangleTop()
{
	return m_RectangleTop;
}

void Rectangle::put_RectangleTop(Length newVal)
{
	m_RectangleTop = newVal;
}

Length Rectangle::get_RectangleWidth()
{
	return m_RectangleWidth;
}

void Rectangle::put_RectangleWidth(Length newVal)
{
	m_RectangleWidth = newVal;
}

Length Rectangle::get_RectangleHeight()
{
	return m_RectangleHeight;
}

void Rectangle::put_RectangleHeight(Length newVal)
{
	m_RectangleHeight = newVal;
}
*/

double Rectangle::get_RadiusX()
{
	return static_cast<DoubleObject*>(GetValue(get_RadiusXProperty()))->GetValue();
}

void Rectangle::set_RadiusX(double newVal)
{
	SetValue(get_RadiusXProperty(), DoubleObject::GetObject(newVal));
}

double Rectangle::get_RadiusY()
{
	return static_cast<DoubleObject*>(GetValue(get_RadiusYProperty()))->GetValue();
}

void Rectangle::set_RadiusY(double newVal)
{
	SetValue(get_RadiusYProperty(), DoubleObject::GetObject(newVal));
}

}	// Shapes
}	// UI
}
