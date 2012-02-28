#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"

#include "PBlockBox.h"

#include "PElementBase.h"

namespace System
{
namespace Web
{

CHTMBlockBox::CHTMBlockBox()
{
	m_type = boxTypeBlock;

	m_opacity = 255;

	m_scrollX = NULL;
	m_scrollY = NULL;
}

CHTMBlockBox::~CHTMBlockBox()
{
	if (m_pElement)
	{
#if 0	// Removed this, TODO: not sure about all implications 
		// Maybe not very elegant, maybe find another solution
		if (this == m_pElement->m_pBox)
		{
			m_pElement->m_pBox = NULL;
		}
#endif
	}
}

gm::PointD CHTMParentBox::ParentToChild(gm::PointD point)
{
	if (m_parentBox)
		point = m_parentBox->ParentToChild(point);

	point.X -= m_innerRect.X;
	point.Y -= m_innerRect.Y;
	point.X -= m_outerRect.X;
	point.Y -= m_outerRect.Y;

	return point;
}

gm::PointD CHTMBlockBox::ParentToChild(gm::PointD point)
{
	if (m_parentBox)
		point = m_parentBox->ParentToChild(point);

	if (m_scrollY)
		point.Y += dynamic_cast<Gui::ScrollBar*>(m_scrollY->GetVisualTree())->get_Value();

	if (m_scrollX)
		point.X += dynamic_cast<Gui::ScrollBar*>(m_scrollX->GetVisualTree())->get_Value();

	point.X -= m_innerRect.X;
	point.Y -= m_innerRect.Y;
	point.X -= m_outerRect.X;
	point.Y -= m_outerRect.Y;

	return point;
}

gm::PointD CHTMElementBox::ScreenToClient(gm::PointD point)
{
	if (m_parentBox)
		point = m_parentBox->ParentToChild(point);

	point.X -= m_outerRect.X;
	point.Y -= m_outerRect.Y;

	return point;
}

void CHTMBlockBox::Draw2(CHTMRenderContext* pC)
{
//	pC->m_outerPos.X += m_outerRect.X;
//	pC->m_outerPos.Y += m_outerRect.Y;

	gm::RectF outerRect = GetAbsOuterRect();

	ASSERT(0);
#if 0
//	pC->m_pGraphics->PushClip();
	pC->m_pGraphics->PushTransform();
	pC->m_pGraphics->TranslateTransform(outerRect.X, outerRect.Y);

	DrawBackground(pC);

	DrawBorder(pC);

#if 1	// TODO, have this
	DrawScrollBars(pC);
#endif

	if (this == m_pElement->m_pBox)
	{
	//	pC->m_pGraphics->TranslateTransform(outerRect.X, outerRect.Y);
	//	pC->m_pGraphics->m_transform = oldtransform;

		LDraw::RectF innerRect = m_innerRect;
	//	innerRect.Offset(outerRect.X, outerRect.Y);

		//LDraw::RectF clipRect = innerRect;
		//clipRect.Offset(-pC->m_clipOrig.X, -pC->m_clipOrig.Y);
		//clipRect.Offset(-pC->m_clip.X, -pC->m_clip.Y);

		if (m_pElement->m_computedOverflowY == Overflow_hidden ||
			m_pElement->m_computedOverflowY == Overflow_scroll)
		{
		//	pC->m_pGraphics->IntersectClip(LDraw::RectI(innerRect.X, innerRect.Y, innerRect.Width, innerRect.Height));
		}
	}

	LDraw::RectF oldclip = pC->m_clip;

	double offsetx = 0;
	double offsety = 0;

	if (m_scrollY)
		offsety = dynamic_cast<UI::ScrollBar*>(m_scrollY->GetVisualTree())->get_Value();

	if (m_scrollX)
		offsetx = dynamic_cast<UI::ScrollBar*>(m_scrollX->GetVisualTree())->get_Value();

	pC->m_pGraphics->TranslateTransform(-offsetx, -offsety);

//#if 0
	if (this == m_pElement->m_pBox)
	{
		m_pElement->Draw(pC);
	}

	pC->m_pGraphics->PopTransform();//oldtransform);

//	pC->m_outerPos.X += m_innerRect.X;
//	pC->m_outerPos.Y += m_innerRect.Y;
//	pC->m_pGraphics->TranslateTransform(m_innerRect.X, m_innerRect.Y);

	{
		for (int i = 0; i < m_positioned_children.size(); i++)
		{
			CHTMElementBox* pBox = m_positioned_children[i];

			if (pBox->m_pElement->m_computedZIndex < 0)
			{
			//	if (clipBounds.IntersectsWith(pBox->m_outerRect))
				{
					pBox->Draw(pC);
				}
			}
		}
	}

	DrawChildren(pC);

	/*
	{
		for (int i = 0; i < m_positioned_children.size(); i++)
		{
			CHTMElementBox* pBox = m_positioned_children[i];

			if (pBox->m_pElement->m_computedZIndex == 0)
			{
			//	if (clipBounds.IntersectsWith(pBox->m_outerRect))
				{
					pBox->Draw(pC);
				}
			}
		}
	}
	*/

	{
		for (int i = 0; i < m_positioned_children.size(); i++)
		{
			CHTMElementBox* pBox = m_positioned_children[i];

			if (pBox->m_pElement->m_computedZIndex >= 0)
			{
			//	if (clipBounds.IntersectsWith(pBox->m_outerRect))
				{
					pBox->Draw(pC);
				}
			}
		}
	}

	/*
#if 1
	for (int i = 0; i < m_renderChildren.GetSize(); i++)
	{
		CHTMBoxItem* pBox = m_renderChildren[i];

		pBox->Draw(pC);
	}
#endif
	*/

//	pC->m_outerPos.X -= m_innerRect.X;
//	pC->m_outerPos.Y -= m_innerRect.Y;
//#if 0

	if (this == m_pElement->m_pBox)
	{
		m_pElement->EndDraw(pC);
	}
//#endif
	pC->m_clip = oldclip;

#if 0
	pC->m_pGraphics->Restore(graphicsState);
#endif
//	pC->m_pGraphics->PopClip();//&oldgclip);

// restore
//	pC->m_outerPos.X -= m_outerRect.X;
//	pC->m_outerPos.Y -= m_outerRect.Y;
#endif
}

void CHTMBlockBox::Draw(CHTMRenderContext* pC)
{
	ASSERT(0);
#if 0
	ASSERT(m_pElement);
	//if (pC->m_clip.IntersectsWith(outerRect))
	{
		if (m_pElement->m_computedVisibility == Visibility_visible)
		{
		//	Gdiplus::RectF outerRect = m_outerRect;
		//	outerRect.Offset(pC->m_outerPos.X, pC->m_outerPos.Y);
			LDraw::Rectf outerRect = GetAbsOuterRect();

			if (false)	// Editing
			{
				if (m_pElement->m_computedPosition == Position_absolute)
				{
					// Move knob
					pC->m_pGraphics->FillRectangle(
						new LDraw::SolidBrush(LDraw::Color(255, 255, 255)),
						LDraw::RectI(outerRect.X-8+1, outerRect.Y-8+1, 6, 6));

					pC->m_pGraphics->DrawRectangle(
						new LDraw::Pen(LDraw::Color(0, 100, 255)),
						LDraw::RectI(outerRect.X-8, outerRect.Y-8, 8, 8));
				}
			}

			if (m_opacity < 255)
			{
				ASSERT(0);
#if 0
				LDraw::Bitmap* pBitmap = new LDraw::Bitmap(m_outerRect.Width+0.5, m_outerRect.Height+0.5);
				if (pBitmap)
				{
					LDraw::Graphics graphics(pBitmap);
					graphics.TranslateTransform(-pC->m_outerPos.X, -pC->m_outerPos.Y);

					LDraw::Graphics* pOldGraphics = pC->m_pGraphics;
					pC->m_pGraphics = &graphics;

					Draw2(pC, outerRect);

					pC->m_pGraphics = pOldGraphics;

					ASSERT(0);
#if 0
				// Draw offscreen bitmap to background
					// opacity
					Gdiplus::ColorMatrix colorMatrix = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
														0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
														0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
														0.0f, 0.0f, 0.0f, (float)m_opacity/255, 0.0f,
														0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

				// Create an ImageAttributes object and set its color matrix.
					Gdiplus::ImageAttributes imageAtt;
					imageAtt.SetColorMatrix(&colorMatrix, Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

					double bitmapWidth = outerRect.Width;
					double bitmapHeight = outerRect.Height;

					Gdiplus::RectF destRect = outerRect;
					pC->m_pGraphics->DrawImage(
						pBitmap,
						destRect,
						(float)0, (float)0, (float)bitmapWidth, (float)bitmapHeight,
						Gdiplus::UnitPixel,
						&imageAtt);
#endif
					delete pBitmap;
				}
#endif
			}
			else
			{
				Draw2(pC/*, outerRect*/);
			}
		}
	}
#endif
}

// virtual
int CHTMBlockBox::HitTestElementBox(double x, double y, PElementBase** ppElement)
{
	gm::RectF rc = GetAbsOuterRect();
	if (rc.Contains(x, y))	// ???
	{
	//	x -= m_outerRect.X;
	//	y -= m_outerRect.Y;
		x -= rc.X;
		y -= rc.Y;

#if 0
		if (m_scrollY && m_scrollY->m_expandedBBoxParent.Contains(x, y))
		{
/*
			Visual* pVisual = m_pElement->m_scrollY->HitTestElement(gmMatrix3::identity(), LDraw::PointD(x, y));
			*/
			*ppElement = (PElementBase*)m_pElement;
			return 2;
		}
		
		if (m_scrollX && m_scrollX->m_expandedBBoxParent.Contains(x, y))
		{
			*ppElement = (PElementBase*)m_pElement;
			return 3;
		}

		x -= m_innerRect.X;
		y -= m_innerRect.Y;

		if (m_scrollX)
		{
			x += dynamic_cast<UI::ScrollBar*>(m_scrollX->get_VisualTree())->get_pos();
		}

		if (m_scrollY)
		{
			y += dynamic_cast<UI::ScrollBar*>(m_scrollY->get_VisualTree())->get_pos();
		}
#endif

		//PSVGElement* svgElement = dynamic_cast<PSVGElement*>(m_pElement);//->m_pNode;
		//if (svgElement)
		//{
		//	PointD pt2(x-rc.X, y-rc.Y);
			gm::PointD pt2(x, y);
			PElementBase* pHitElement = m_pElement->HitTestElement(gm::Matrix3d::GetIdentity(), pt2);

			if (pHitElement)
			{
				*ppElement = pHitElement;
				return 1;
			}

		//	return svgElement->HitTestElement(gmMatrix3::identity(), pt2);
		//}
		//else
		{

			for (int i = 0; i < m_renderChildren.size(); i++)
			{
				CHTMBoxItem* pBox = m_renderChildren[i];

				int nhit = pBox->HitTestElementBox(x, y, ppElement);
				if (nhit)
					return nhit;
			}
		}

		*ppElement = (PElementBase*)m_pElement;
		return 1;//(CPElementBase*)m_pElement;	// TODO
	}

	return 0;
}

}	// Web
}
