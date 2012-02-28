#include "stdafx.h"
#include "LXUI2.h"
#include "Border.h"
#include "LinearGradientBrush.h"

//#include "SolidColorBrush.h"	// TODO remove

namespace System
{
namespace UI
{

DependencyProperty* Border::s_BackgroundProperty = RegisterProperty(WSTR("Background"), typeid(Brush), typeid(Border), NULL, PropertyMetaData(AffectsRender));
DependencyProperty* Border::s_BorderBrushProperty = RegisterProperty(WSTR("BorderBrush"), typeid(Brush), typeid(Border), NULL, PropertyMetaData(AffectsRender));
DependencyProperty* Border::s_BorderThicknessProperty = RegisterProperty(WSTR("BorderThickness"), typeid(Thickness), typeid(Border), NULL, PropertyMetaData(AffectsMeasure | AffectsRender));
DependencyProperty* Border::s_CornerRadiusProperty = RegisterProperty(WSTR("CornerRadius"), typeid(CornerRadius), typeid(Border), NULL, PropertyMetaData(AffectsMeasure));
DependencyProperty* Border::s_PaddingProperty = RegisterProperty(WSTR("Padding"), typeid(Thickness), typeid(Border), NULL, PropertyMetaData(AffectsMeasure | AffectsRender));

CornerRadius::CornerRadius()
{
	m_TopLeft = 0;
	m_TopRight = 0;
	m_BottomLeft = 0;
	m_BottomRight = 0;
}

CornerRadius::CornerRadius(double value)
{
	m_TopLeft = value;
	m_TopRight = value;
	m_BottomLeft = value;
	m_BottomRight = value;
}

CornerRadius::CornerRadius(double topleft, double topright, double bottomleft, double bottomright)
{
	m_TopLeft = topleft;
	m_TopRight = topright;
	m_BottomLeft = bottomleft;
	m_BottomRight = bottomright;
}

CornerRadius::~CornerRadius()
{
}

double CornerRadius::get_TopLeft()
{
	return m_TopLeft;
}

/*
void CornerRadius::put_TopLeft(double newVal)
{
}
*/

double CornerRadius::get_TopRight()
{
	return m_TopRight;
}

/*
void CornerRadius::put_TopRight(double newVal)
{
}
*/

double CornerRadius::get_BottomLeft()
{
	return m_BottomLeft;
}

/*
void CornerRadius::put_BottomLeft(double newVal)
{
}
*/

double CornerRadius::get_BottomRight()
{
	return m_BottomRight;
}

/*
void CornerRadius::put_BottomRight(double newVal)
{
}
*/

Border::Border()
{
//	m_Content = NULL;
//	m_BorderBrush = NULL;
//	m_Padding = NULL;
//	m_CornerRadius = NULL;
//	m_BorderThickness = NULL;

//	SetClipMode(false);
}

Border::Border(Thickness* thickness)
{
//	m_Content = NULL;
//	m_BorderBrush = NULL;
//	m_Padding = NULL;
//	m_CornerRadius = NULL;

	set_BorderThickness(thickness);

//	SetClipMode(false);
}

Brush* Border::get_Background()
{
	return static_cast<Brush*>(GetValue(get_BackgroundProperty()));
}

void Border::set_Background(Brush* pBrush)
{
	SetValue(get_BackgroundProperty(), pBrush);
}

Brush* Border::get_BorderBrush()
{
	return static_cast<Brush*>(GetValue(get_BorderBrushProperty()));
}

void Border::set_BorderBrush(Brush* newVal)
{
	SetValue(get_BorderBrushProperty(), newVal);
}

CornerRadius* Border::get_CornerRadius()
{
	return static_cast<CornerRadius*>(GetValue(get_CornerRadiusProperty()));
}

void Border::set_CornerRadius(CornerRadius* newVal)
{
	SetValue(get_CornerRadiusProperty(), newVal);
}

// virtual
LDraw::SizeD Border::MeasureOverride(LDraw::SizeD availSize)
{
	double computedBorderLeft = 0;
	double computedBorderTop = 0;
	double computedBorderRight = 0;
	double computedBorderBottom = 0;

	Thickness* m_BorderThickness = get_BorderThickness();

	if (m_BorderThickness != NULL)
	{
		double Left = m_BorderThickness->get_Left();
		//if (Left != NULL)
		{
			computedBorderLeft = Left;//->get_Value();
		}

		double Top = m_BorderThickness->get_Top();
		//if (Top != NULL)
		{
			computedBorderTop = Top;//->get_Value();
		}

		double Right = m_BorderThickness->get_Right();
		//if (Right != NULL)
		{
			computedBorderRight = Right;//->get_Value();
		}

		double Bottom = m_BorderThickness->get_Bottom();
		//if (Bottom != NULL)
		{
			computedBorderBottom = Bottom;//->get_Value();
		}
	}

	availSize.Width -= computedBorderLeft + computedBorderRight;
	availSize.Height -= computedBorderTop + computedBorderBottom;

	if (availSize.Width < 0) availSize.Width = 0;
	if (availSize.Height < 0) availSize.Height = 0;

	double width = computedBorderLeft + computedBorderRight;
	double height = computedBorderTop + computedBorderBottom;

	UIElement* pChild = get_Child();

	if (pChild)
	{
		pChild->Measure(availSize);

		width += pChild->get_DesiredSize().Width;
		height += pChild->get_DesiredSize().Height;
	}

	return LDraw::SizeD(width, height);
}

LDraw::SizeD Border::ArrangeOverride(LDraw::SizeD finalSize)
{
	m_computedBorderLeft = 0;
	m_computedBorderTop = 0;
	m_computedBorderRight = 0;
	m_computedBorderBottom = 0;

	Thickness* m_BorderThickness = get_BorderThickness();

	if (m_BorderThickness != NULL)
	{
		double Left = m_BorderThickness->get_Left();
		//if (Left != NULL)
		{
			m_computedBorderLeft = Left;//->get_Value();
		}

		double Top = m_BorderThickness->get_Top();
		//if (Top != NULL)
		{
			m_computedBorderTop = Top;//->get_Value();
		}

		double Right = m_BorderThickness->get_Right();
		//if (Right != NULL)
		{
			m_computedBorderRight = Right;//->get_Value();
		}

		double Bottom = m_BorderThickness->get_Bottom();
		//if (Bottom != NULL)
		{
			m_computedBorderBottom = Bottom;//->get_Value();
		}
	}

//	finalSize.Width -= m_computedBorderLeft + m_computedBorderRight;
//	finalSize.Height -= m_computedBorderTop + m_computedBorderBottom;

	UIElement* pChild = get_Child();

	if (pChild)
	{
		double width = finalSize.Width - m_computedBorderLeft - m_computedBorderRight;
		double height = finalSize.Height - m_computedBorderTop - m_computedBorderBottom;

	//	pChild->Arrange(LDraw::RectD(m_computedBorderLeft, m_computedBorderTop, finalSize.Width - m_computedBorderLeft - m_computedBorderRight, finalSize.Height - m_computedBorderTop - m_computedBorderBottom));
		pChild->Arrange(LDraw::RectD(m_computedBorderLeft, m_computedBorderTop, width, height));
		//m_Content->SetLayoutOffset(m_computedBorderLeft, m_computedBorderTop);
	}

	return finalSize;
}

/*
void Border::put_LeftBrush(Brush* pBrush)
{
	m_LeftBrush = pBrush;
}

void Border::put_TopBrush(Brush* pBrush)
{
	m_TopBrush = pBrush;
}

void Border::put_RightBrush(Brush* pBrush)
{
	m_RightBrush = pBrush;
}

void Border::put_BottomBrush(Brush* pBrush)
{
	m_BottomBrush = pBrush;
}
*/

#if 0
UIElement* Border::get_Content()
{
	return m_Content;
}

void Border::set_Content(UIElement* Content)
{
	printf("UI::Border::set_Content(%p)\n", Content);

	if (m_Content != Content)
	{
		if (m_Content)
		{
			//ASSERT(0);
			RemoveRChild(m_Content);
		}

		m_Content = Content;

		if (m_Content)
		{
			if (m_Content->GetRParent())
			{
				ASSERT(0);
				m_Content->GetRParent()->RemoveRChild(m_Content);
			}
			AddRChild(m_Content);
		}

		InvalidateMeasure();
	}
}
#endif

#if 0
// virtual
void Border::Clip(LDraw::Graphics* pGraphics, LDraw::Rgn& rgn)
{
	Control::Clip(pGraphics, rgn);
#if 0
	gmMatrix3 oldTransform = pGraphics->m_transform;
	pGraphics->MultiplyTransform(m_transformMatrix);

	// The default is not to clip
//	if (m_computedRectangleWidth > 0 && m_computedRectangleHeight > 0)
	//if (get_BackgroundBrush())
	{
		gmVector2 xpt = pGraphics->m_transform.transform(gmVector2(m_expandedBBox.X, m_expandedBBox.Y));
		HRGN rect = CreateRectRgn(xpt[0], xpt[1], xpt[0]+m_expandedBBox.Width, xpt[1]+m_expandedBBox.Height);
		CombineRgn(hRgn, hRgn, rect, RGN_DIFF);
		DeleteObject(rect);
	}

	pGraphics->m_transform = oldTransform;
#endif
}
#endif

void Border::OnRenderBackground(Graphics* pGraphics)
{
	LDraw::SizeD actualSize = get_ActualSize();
/*
	if (actualSize.Width <= 0 || actualSize.Height <= 0)
		return;
	*/

	ASSERT(actualSize.Width > 0 && actualSize.Height > 0);

	Brush* pBackgroundBrush = get_Background();
	if (pBackgroundBrush)
	{
		LDraw::SizeD actualSize = get_ActualSize();
		__release<LDraw::Brush> brush = pBackgroundBrush->CreateBrush(this, 1, 1);
		pGraphics->FillRectangle(brush, 0, 0, actualSize.Width, actualSize.Height);
	}

//	OnRender(pGraphics);

	//OnRender3(pGraphics);
}

// virtual
void Border::OnRender(Graphics* pGraphics)
{
	LDraw::SizeD actualSize = get_ActualSize();

	Brush* m_BorderBrush = get_BorderBrush();
	CornerRadius* cornerRadius = get_CornerRadius();
	Thickness* borderThickness = get_BorderThickness();

	/*
	{
		//Brush* bg = get_Background();

		SolidColorBrush* bg = dynamic_cast<SolidColorBrush*>(get_Background());
		if (bg)
		{
			TRACE("rgba(%d,%d,%d,%d)\n", bg->get_Color()->get_R(), bg->get_Color()->get_G(), bg->get_Color()->get_G(), bg->get_Color()->get_A());
		}
	}
	*/

//	if (actualSize.Width <= 5 || actualSize.Height <= 5)
//		return;

	ASSERT(actualSize.Width > 0 && actualSize.Height > 0);

	if (cornerRadius)
	{
		LDraw::Brush* pBrush = m_BorderBrush->CreateBrush(this, 1, 1);

		LDraw::SizeD actualSize = get_ActualSize();

		__release<LDraw::GraphicsPathF> outerPath = new LDraw::GraphicsPathF;
		outerPath->AddRoundRect(
			0, 0, actualSize.Width, actualSize.Height,
			cornerRadius->get_TopLeft(), cornerRadius->get_TopRight(), cornerRadius->get_BottomLeft(), cornerRadius->get_BottomRight());

		__release<LDraw::GraphicsPathF> innerPath = new LDraw::GraphicsPathF;
		innerPath->AddRectangle(
			borderThickness->get_Left(),
			borderThickness->get_Top(),
			actualSize.Width - borderThickness->get_Left() - borderThickness->get_Right(),
			actualSize.Height - borderThickness->get_Top() - borderThickness->get_Bottom());

		innerPath->Reverse();

		outerPath->AddPath(innerPath, false/*bConnect*/);
		pGraphics->FillPath(pBrush, outerPath);
	}
	else if (m_BorderBrush)
	{
		LDraw::Brush* pBrush = m_BorderBrush->CreateBrush(this, 1, 1);

		LinearGradientBrush* pLinearGBrush = dynamic_cast<LinearGradientBrush*>(m_BorderBrush);

		LDraw::Brush* pBrush2;

		if (pLinearGBrush)
		{
			pBrush2 = pLinearGBrush->CreateBrush(m_expandedBBox, LDraw::Matrix3f::GetRotate(-90), 1, 1);
		}
		else
		{
			pBrush2 = pBrush;
		}

		// left
		{
			LDraw::PointF points[] =
			{
				LDraw::PointF(0, 0),
				LDraw::PointF(m_computedBorderLeft, m_computedBorderTop),
				LDraw::PointF(m_computedBorderLeft, m_computedSize.Height-m_computedBorderBottom),
				LDraw::PointF(0, m_computedSize.Height),
			};

			pGraphics->FillPolygon(pBrush2, points, 4);
		}

		// right
		{
			LDraw::PointF points[] =
			{
				LDraw::PointF(m_computedSize.Width, m_computedSize.Height),
				LDraw::PointF(m_computedSize.Width-m_computedBorderRight, m_computedSize.Height-m_computedBorderTop),
				LDraw::PointF(m_computedSize.Width-m_computedBorderRight, m_computedBorderTop),
				LDraw::PointF(m_computedSize.Width, 0),
			};

			pGraphics->FillPolygon(pBrush2, points, 4);
		}

		// top
		{
			LDraw::PointF points[] =
			{
				LDraw::PointF(m_computedSize.Width, 0),
				LDraw::PointF(m_computedSize.Width-m_computedBorderRight, m_computedBorderTop),
				LDraw::PointF(m_computedBorderLeft, m_computedBorderTop),
				LDraw::PointF(0, 0),
			};

			pGraphics->FillPolygon(pBrush, points, 4);
		}

		// bottom
		{
			LDraw::PointF points[] =
			{
				LDraw::PointF(m_computedBorderLeft, m_computedSize.Height-m_computedBorderBottom),
				LDraw::PointF(m_computedSize.Width-m_computedBorderRight, m_computedSize.Height-m_computedBorderBottom),
				LDraw::PointF(m_computedSize.Width, m_computedSize.Height),
				LDraw::PointF(0, m_computedSize.Height),

				/*
				LDraw::PointF(0, m_computedHeight),
				LDraw::PointF(m_computedBorderLeft, m_computedHeight-m_computedBorderBottom),
				LDraw::PointF(m_computedWidth-m_computedBorderRight, m_computedHeight-m_computedBorderBottom),
				LDraw::PointF(m_computedWidth, m_computedHeight),
				*/
			};

			pGraphics->FillPolygon(pBrush, points, 4);
		}

#if 0
	if (m_LeftBrush)
	{
		LDraw::Brush pBrush = m_LeftBrush->CreateBrush(this, 1, 1);

		LDraw::PointF points[] =
		{
			LDraw::PointF(0, 0),
			LDraw::PointF(m_computedBorderLeft, m_computedBorderTop),
			LDraw::PointF(m_computedBorderLeft, m_computedSize.Height-m_computedBorderBottom),
			LDraw::PointF(0, m_computedSize.Height),
		};

		pGraphics->FillPolygon(&pBrush, points, 4);

	}

	if (m_TopBrush)
	{
		LDraw::Brush pBrush = m_TopBrush->CreateBrush(this, 1, 1);

		LDraw::PointF points[] =
		{
			LDraw::PointF(m_computedSize.Width, 0),
			LDraw::PointF(m_computedSize.Width-m_computedBorderRight, m_computedBorderTop),
			LDraw::PointF(m_computedBorderLeft, m_computedBorderTop),
			LDraw::PointF(0, 0),
		};

		pGraphics->FillPolygon(&pBrush, points, 4);
	}

	if (m_RightBrush)
	{
		LDraw::Brush pBrush = m_RightBrush->CreateBrush(this, 1, 1);

		LDraw::PointF points[] =
		{
			LDraw::PointF(m_computedSize.Width, m_computedSize.Height),
			LDraw::PointF(m_computedSize.Width-m_computedBorderRight, m_computedSize.Height-m_computedBorderTop),
			LDraw::PointF(m_computedSize.Width-m_computedBorderRight, m_computedBorderTop),
			LDraw::PointF(m_computedSize.Width, 0),
		};

		pGraphics->FillPolygon(&pBrush, points, 4);
	}

	if (m_BottomBrush)
	{
		LDraw::Brush pBrush = m_BottomBrush->CreateBrush(this, 1, 1);

		LDraw::PointF points[] =
		{
			LDraw::PointF(m_computedBorderLeft, m_computedSize.Height-m_computedBorderBottom),
			LDraw::PointF(m_computedSize.Width-m_computedBorderRight, m_computedSize.Height-m_computedBorderBottom),
			LDraw::PointF(m_computedSize.Width, m_computedSize.Height),
			LDraw::PointF(0, m_computedSize.Height),

			/*
			LDraw::PointF(0, m_computedHeight),
			LDraw::PointF(m_computedBorderLeft, m_computedHeight-m_computedBorderBottom),
			LDraw::PointF(m_computedWidth-m_computedBorderRight, m_computedHeight-m_computedBorderBottom),
			LDraw::PointF(m_computedWidth, m_computedHeight),
			*/
		};

		pGraphics->FillPolygon(&pBrush, points, 4);
	}
#endif
	}

	UIElement::OnRender(pGraphics);

	/*
	if (m_Content)
	{
		m_Content->Render(pGraphics);
	}
	*/

#if 0
#if _WINDOWS
	Gdiplus::Matrix oldMatrix;
	pGraphics->GetTransform(&oldMatrix);

#if 0
	pGraphics->TranslateTransform(float(m_computedBorderLeft), float(m_computedBorderTop));
#endif
#if 0
	if (m_Transform)
	{
		CComPtr<ILSVGMatrix> Value;
		m_Transform->get_Value(&Value);

		gmMatrix3& mat = static_cast<SVGMatrix*>(Value.p)->m_matrix;

		Gdiplus::Matrix gdipm(
			(float)mat[0][0], (float)mat[0][1],
			(float)mat[1][0], (float)mat[1][1],
			(float)mat[2][0], (float)mat[2][1]);

		pGraphics->MultiplyTransform(&gdipm);
	}
#endif

	ASSERT(0);
#if 0
	UPOSITION pos = m_rchildList.GetHeadPosition();
	while (pos)
	{
		UIElement* pElement = (UIElement*)m_rchildList.GetNext(pos);

		pElement->Render(pGraphics);
	}
#endif

	pGraphics->SetTransform(&oldMatrix);
#else
	ASSERT(0);
#endif // _WINDOWS
#endif
}

Thickness* Border::get_BorderThickness()
{
	return static_cast<Thickness*>(GetValue(get_BorderThicknessProperty()));
}

void Border::set_BorderThickness(Thickness* newVal)
{
	SetValue(get_BorderThicknessProperty(), newVal);
}

Thickness* Border::get_Padding()
{
	return static_cast<Thickness*>(GetValue(get_PaddingProperty()));
}

void Border::set_Padding(Thickness* newVal)
{
	SetValue(get_PaddingProperty(), newVal);

	/*
	//printf("UI::Border::put_Padding(%p)\n", newVal.m_p);

	m_Padding = newVal;
	InvalidateMeasure();
	*/

//	printf("done\n");
}

}	// UI
}
