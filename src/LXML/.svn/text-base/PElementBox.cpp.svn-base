#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"

#include "PElementBox.h"

#include "LBoxes.h"

namespace System
{
namespace Web
{

CHTMElementBox::CHTMElementBox()
{
	m_pElement = NULL;

// non-inherited CSS properties take on initial values
// for anonymous boxes

	m_computedMargin[0] = 0;
	m_computedMargin[1] = 0;
	m_computedMargin[2] = 0;
	m_computedMargin[3] = 0;
	
	m_computedPadding[0] = 0;
	m_computedPadding[1] = 0;
	m_computedPadding[2] = 0;
	m_computedPadding[3] = 0;

	m_computedBorderWidth[0] = 0;
	m_computedBorderWidth[1] = 0;
	m_computedBorderWidth[2] = 0;
	m_computedBorderWidth[3] = 0;

	m_computedBackgroundColor = CRGBColor(0, 0, 0, 0);	// transparent
	m_pBackgroundImage = NULL;
}

CHTMElementBox::~CHTMElementBox()
{
	// ?? TODO, have this when detaching box from parent instead of in destructor
#if 0
	if (m_pElement)
	{
		m_pElement->OnRemoveBox(this);

		//m_pElement->RemoveBox(this);
		m_pElement = NULL;
	}
#endif
	ASSERT(m_pElement);	// Should not destroy twice

	m_pElement->OnRemoveBox(this);
	m_pElement = NULL;
}

/*
// virtual
void CHTMElementBox::SetParentNULL()
{
	m_parentBox = NULL;
}
*/

/*
// virtual
void CHTMElementBox::Destroy()
{

	CHTMParentBox::Destroy();
}
*/

// virtual
bool CHTMElementBox::getPosUnderPoint(double x, double y, PNode **pNode, long *pOffset)
{
	for (int i = 0; i < m_children.GetSize(); i++)
	{
		CHTMBoxItem* pBox = m_children[i];

		bool b = pBox->getPosUnderPoint(x, y, pNode, pOffset);
		if (b)
			return true;
	}

	return false;
}

void CHTMElementBox::DrawBoxShadow(CHTMRenderContext* pC)
{
	ASSERT(m_pElement != NULL);

	gm::RectF rect = GetAbsOuterRect();

	rect.X += m_computedMargin[0];
	rect.Y += m_computedMargin[1];
	rect.Width -= m_computedMargin[0]+m_computedMargin[2];
	rect.Height -= m_computedMargin[1]+m_computedMargin[3];

#if 0	// TODO Have something like this
	for (int i = 0; i < m_pElement->m_computedBoxShadow.size(); i++)
	{
		LDraw::RectF srect = rect;

		srect.Offset(m_pElement->m_computedBoxShadow[i].m_offset[0], m_pElement->m_computedBoxShadow[i].m_offset[1]);

		pC->m_pGraphics->FillRectangle(&LDraw::SolidBrush(m_pElement->m_computedBoxShadow[i].m_color), srect);
	}
#endif
}

void CHTMElementBox::DrawBackground(CHTMRenderContext* pC)
{
	ASSERT(0);
#if 0
	ASSERT(m_pElement != NULL);

// content rect
//	LDraw::RectF conRect = m_innerRect;
//	conRect.Offset(pC->m_outerPos.X, pC->m_outerPos.Y);
	LDraw::RectF conRect = m_innerRect;//GetAbsInnerRect();

// padding rect
	LDraw::RectF padRect = conRect;
	padRect.X -= m_computedPadding[0];
	padRect.Y -= m_computedPadding[1];
	padRect.Width += m_computedPadding[0] + m_computedPadding[2];
	padRect.Height += m_computedPadding[1] + m_computedPadding[3];

// ?? Also draw below the border
	padRect.X -= m_computedBorderWidth[0];
	padRect.Y -= m_computedBorderWidth[1];
	padRect.Width += m_computedBorderWidth[0] + m_computedBorderWidth[2];
	padRect.Height += m_computedBorderWidth[1] + m_computedBorderWidth[3];

#if 0
	padRect.X = (int)padRect.X;
	padRect.Y = (int)padRect.Y;
	padRect.Width = (int)padRect.Width;
	padRect.Height = (int)padRect.Height;
#endif

	if (m_computedBackgroundColor.GetAlpha() > 0)
	{
		LDraw::GraphicsPathF* path = new LDraw::GraphicsPathF;
		LDraw::RoundRect(path, padRect.X, padRect.Y, padRect.Width, padRect.Height, m_pElement->m_computedBorderRadius);

//		pC->m_pGraphics->FillRectangle(&LDraw::SolidBrush(m_computedBackgroundColor), padRect);
		pC->m_pGraphics->FillPath(new LDraw::SolidBrush(m_computedBackgroundColor), path);
	}

// Draw background-image
	if (m_pBackgroundImage &&
		m_pBackgroundImage->m_bitmap != NULL
#if 0
		&&
		m_pBackgroundImage->m_gdipImage->GetLastStatus() == LDraw::Ok
#endif
		)
	{
			ASSERT(0);
#if 0
		if (TRUE)
		{

			LDraw::TextureBrush textureBrush(&m_pBackgroundImage->m_bitmap);

			textureBrush.TranslateTransform(padRect.X, padRect.Y);

			pC->m_pGraphics->FillRectangle(&textureBrush, padRect);
		}
		else
		{
			LDraw::GraphicsState graphicsState = pC->m_pGraphics->Save();
		
			pC->m_pGraphics->IntersectClip(padRect);

			int nx;
			int ny;

			if (m_pElement->m_computedBackgroundRepeat == BackgroundRepeat_repeat)
			{
				nx = (padRect.Width+m_pBackgroundImage->m_gdipImage->GetWidth()-1)/m_pBackgroundImage->m_gdipImage->GetWidth();
				ny = (padRect.Height+m_pBackgroundImage->m_gdipImage->GetHeight()-1)/m_pBackgroundImage->m_gdipImage->GetHeight();
			}
			else if (m_pElement->m_computedBackgroundRepeat == BackgroundRepeat_repeat_x)
			{
				nx = (padRect.Width+m_pBackgroundImage->m_gdipImage->GetWidth()-1)/m_pBackgroundImage->m_gdipImage->GetWidth();
				ny = 1;
			}
			else if (m_pElement->m_computedBackgroundRepeat == BackgroundRepeat_repeat_y)
			{
				nx = 1;
				ny = (padRect.Height+m_pBackgroundImage->m_gdipImage->GetHeight()-1)/m_pBackgroundImage->m_gdipImage->GetHeight();
			}
			else
			{
				nx = 1;
				ny = 1;
			}

			int y = 0;

			for (int iy = 0; iy < ny; iy++)
			{
				int x = 0;

				for (int ix = 0; ix < nx; ix++)
				{
					pC->m_pGraphics->DrawImage(m_pBackgroundImage->m_gdipImage, padRect.X+x, padRect.Y+y);

					x += m_pBackgroundImage->m_gdipImage->GetWidth();
				}

				y += m_pBackgroundImage->m_gdipImage->GetHeight();
			}

			ASSERT(0);
#if 0
			pC->m_pGraphics->Restore(graphicsState);
#endif
		}
#endif
	}
#endif
}

void DrawDotsH(Gui::ManagedRetainedRenderContext pGraphics, double x1, double y1, double x2, double size)
{
	for (int x = x1; x < x2; x += size*2)
	{
		//if (size <= 1)
		//	Rectangle(hDC, x, y1, x+2, y1+2);
		//else
		ASSERT(0);
#if 0
		pGraphics->FillEllipse(new LDraw::SolidBrush(LDraw::Color::White), x-size/2, y1-size/2, size, size);
#endif
	}
}

void DrawDotsV(Gui::ManagedRetainedRenderContext pGraphics, double x1, double y1, double y2, double size)
{
	for (int y = y1; y < y2; y += size*2)
	{
		/*
		if (size <= 1)
			Rectangle(hDC, x1, y, x1+2, y+2);
		else
			Ellipse(hDC, x1-size/2, y-size/2, x1+size/2+1, y+size/2+1);
			*/
		ASSERT(0);
#if 0
		pGraphics->FillEllipse(new LDraw::SolidBrush(LDraw::Color::White), x1-size/2, y-size/2, size, size);
#endif
	}
}

void CHTMElementBox::DrawBorder(CHTMRenderContext* pC)
{
	ASSERT(m_pElement != NULL);

// content rect
	gm::RectF conRect = m_innerRect;
//	LDraw::RectF conRect = m_outerRect;
//	conRect.X -= conRect.X;
//	conRect.Y -= conRect.Y;

	gm::RectF padRect = conRect;
	padRect.X -= m_computedPadding[0];
	padRect.Y -= m_computedPadding[1];
	padRect.Width += m_computedPadding[0] + m_computedPadding[2];
	padRect.Height += m_computedPadding[1] + m_computedPadding[3];

	ASSERT(0);
#if 0
	LDraw::SmoothingMode oldSmoothingMode = pC->m_pGraphics->GetSmoothingMode();

//	pC->m_pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

	/*
	pC->m_pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 0, 0)), padRect);
	pC->m_pGraphics->SetSmoothingMode(oldSmoothingMode);
	return;
	*/


	/*
	padRect.X = padRect.X;
	padRect.Y = padRect.Y;
	padRect.Width = padRect.Width;
	padRect.Height = padRect.Height;
	*/

	/*
	if (m_scrollX)
	{
		padRect.Height += 16;
	}

	if (m_scrollY)
	{
		padRect.Width += 16;
	}
	*/

// border rect
	LDraw::RectF borRect = padRect;
	borRect.X -= m_computedBorderWidth[0];
	borRect.Y -= m_computedBorderWidth[1];
	borRect.Width += m_computedBorderWidth[0] + m_computedBorderWidth[2];
	borRect.Height += m_computedBorderWidth[1] + m_computedBorderWidth[3];

// Draw left border
//	if (this == m_pElement->m_content[0])
	if (m_computedBorderWidth[0])
	{
		switch (m_pElement->m_computedBorderStyle[0])
		{
		case BorderStyle_solid:
			{
				LDraw::Color c = m_pElement->m_computedBorderColor[0];

				LDraw::PointF pt[4] =
				{
					LDraw::PointF(borRect.GetLeft(), borRect.GetTop()),
					LDraw::PointF(padRect.GetLeft(), padRect.GetTop()),
					LDraw::PointF(padRect.GetLeft(), padRect.GetBottom()),
					LDraw::PointF(borRect.GetLeft(), borRect.GetBottom())
				};
				
				pC->m_pGraphics->FillPolygon(
					new LDraw::SolidBrush(c),
					pt, 4);
			}
			break;

#if 0
		case BorderStyle_ridge:
			{
				COLORREF c1 = RGB(GetRValue(m_pElement->m_borderColor[0])*80/100, GetGValue(m_pElement->m_borderColor[0])*80/100, GetBValue(m_pElement->m_borderColor[0])*80/100);
				COLORREF c2 = RGB(min(GetRValue(m_pElement->m_borderColor[0])*100/80, 255), min(GetGValue(m_pElement->m_borderColor[0])*100/80, 255), min(GetBValue(m_pElement->m_borderColor[0])*100/80, 255));
				
				int mx = brect.left + (prect.left-brect.left)/2;
				int tmy = brect.top + (prect.top-brect.top)/2;
				int bmy = brect.bottom + (prect.bottom-brect.bottom)/2;
				
				//
				LDraw::Point pt1[4] =
				{
					LDraw::Point(mx, tmy),
					LDraw::Point(prect.left, prect.top),
					LDraw::Point(prect.left, prect.bottom),
					LDraw::Point(mx, bmy),
				};
				
				pC->m_pGraphics->FillPolygon(
					LDraw::SolidBrush(LDraw::Color(GetRValue(c1), GetGValue(c1), GetBValue(c1))),
					pt1, 4);
				
				//
				LDraw::Point pt2[4] =
				{
					LDraw::Point(mx, tmy),
					LDraw::Point(brect.left, brect.top),
					LDraw::Point(brect.left, brect.bottom),
					LDraw::Point(mx, bmy),
				};
				
				pC->m_pGraphics->FillPolygon(
					LDraw::SolidBrush(LDraw::Color(GetRValue(c2), GetGValue(c2), GetBValue(c2))),
					pt2, 4);
			}
			break;
#endif
		}
	}
	
	// Draw right border
//	if (this == m_pElement->m_content[m_pElement->m_content.GetSize()-1])
	{
		switch (m_pElement->m_computedBorderStyle[2])
		{
		case BorderStyle_solid:
			{
				LDraw::Color c = m_pElement->m_computedBorderColor[2];

				LDraw::PointF pt[4] =
				{
					LDraw::PointF(borRect.GetRight(), borRect.GetTop()),
					LDraw::PointF(padRect.GetRight(), padRect.GetTop()),
					LDraw::PointF(padRect.GetRight(), padRect.GetBottom()),
					LDraw::PointF(borRect.GetRight(), borRect.GetBottom()),
				};

				pC->m_pGraphics->FillPolygon(
					new LDraw::SolidBrush(c),
					pt, 4);
			}
			break;

#if 0
		case BorderStyle_ridge:
			{
				COLORREF c2 = RGB(GetRValue(m_pElement->m_borderColor[2])*80/100, GetGValue(m_pElement->m_borderColor[2])*80/100, GetBValue(m_pElement->m_borderColor[2])*80/100);
				COLORREF c1 = RGB(min(GetRValue(m_pElement->m_borderColor[2])*100/80, 255), min(GetGValue(m_pElement->m_borderColor[2])*100/80, 255), min(GetBValue(m_pElement->m_borderColor[2])*100/80, 255));
				
				int mx = brect.right + (prect.right-brect.right)/2;
				int tmy = brect.top + (prect.top-brect.top)/2;
				int bmy = brect.bottom + (prect.bottom-brect.bottom)/2;
				
				//
				LDraw::Point pt1[4] =
				{
					LDraw::Point(mx, tmy),
					LDraw::Point(prect.right, prect.top),
					LDraw::Point(prect.right, prect.bottom),
					LDraw::Point(mx, bmy),
				};

				pC->m_pGraphics->FillPolygon(
					&LDraw::SolidBrush(LDraw::Color(GetRValue(c1), GetGValue(c1), GetBValue(c1))),
					pt1, 4);

				//
				LDraw::Point pt2[4] =
				{
					LDraw::Point(mx, tmy),
					LDraw::Point(brect.right, brect.top),
					LDraw::Point(brect.right, brect.bottom),
					LDraw::Point(mx, bmy),
				};
				
				pC->m_pGraphics->FillPolygon(
					&LDraw::SolidBrush(LDraw::Color(GetRValue(c2), GetGValue(c2), GetBValue(c2))),
					pt2, 4);
			}
			break;
#endif
		}
	}

	// Draw top border
	switch (m_pElement->m_computedBorderStyle[1])
	{
		case BorderStyle_solid:
			{
				LDraw::Color c = m_pElement->m_computedBorderColor[1];

				LDraw::PointF pt[4] =
				{
					LDraw::PointF(borRect.GetLeft(), borRect.GetTop()),
					LDraw::PointF(padRect.GetLeft(), padRect.GetTop()),
					LDraw::PointF(padRect.GetRight(), padRect.GetTop()),
					LDraw::PointF(borRect.GetRight(), borRect.GetTop()),
				};

				pC->m_pGraphics->FillPolygon(
					new LDraw::SolidBrush(c),
					pt, 4);
			}
			break;
			
#if 0
		case BorderStyle_ridge:
			{
				COLORREF c1 = RGB(GetRValue(m_pElement->m_borderColor[1])*80/100, GetGValue(m_pElement->m_borderColor[1])*80/100, GetBValue(m_pElement->m_borderColor[1])*80/100);
				COLORREF c2 = RGB(min(GetRValue(m_pElement->m_borderColor[1])*100/80, 255), min(GetGValue(m_pElement->m_borderColor[1])*100/80, 255), min(GetBValue(m_pElement->m_borderColor[1])*100/80, 255));
				
				int my = brect.top + (prect.top-brect.top)/2;
				int tmx = brect.left + (prect.left-brect.left)/2;
				int bmx = brect.right + (prect.right-brect.right)/2;
				
				//
				LDraw::Point pt1[4] =
				{
					LDraw::Point(prect.left, prect.top),
					LDraw::Point(tmx, my),
					LDraw::Point(bmx, my),
					LDraw::Point(prect.right, prect.top),
				};
				
				pC->m_pGraphics->FillPolygon(
					&LDraw::SolidBrush(LDraw::Color(GetRValue(c1), GetGValue(c1), GetBValue(c1))),
					pt1, 4);
				
				//
				LDraw::Point pt2[4] =
				{
					LDraw::Point(brect.left, brect.top),
					LDraw::Point(tmx, my),
					LDraw::Point(bmx, my),
					LDraw::Point(brect.right, brect.top),
				};
				
				pC->m_pGraphics->FillPolygon(
					&LDraw::SolidBrush(LDraw::Color(GetRValue(c2), GetGValue(c2), GetBValue(c2))),
					pt2, 4);
			}
			break;
#endif
	}
	
	// Draw bottom border
	switch (m_pElement->m_computedBorderStyle[3])
	{
		case BorderStyle_solid:
			{
				LDraw::Color c = m_pElement->m_computedBorderColor[3];

				LDraw::PointF pt[4] =
				{
					LDraw::PointF(borRect.GetLeft(), borRect.GetBottom()),
					LDraw::PointF(padRect.GetLeft(), padRect.GetBottom()),
					LDraw::PointF(padRect.GetRight(), padRect.GetBottom()),
					LDraw::PointF(borRect.GetRight(), borRect.GetBottom()),
				};
				
				pC->m_pGraphics->FillPolygon(
					new LDraw::SolidBrush(c),
					pt, 4);
			}
			break;

#if 0
	case BorderStyle_ridge:
		{
			COLORREF c2 = RGB(GetRValue(m_pElement->m_borderColor[3])*80/100, GetGValue(m_pElement->m_borderColor[3])*80/100, GetBValue(m_pElement->m_borderColor[3])*80/100);
			COLORREF c1 = RGB(min(GetRValue(m_pElement->m_borderColor[3])*100/80, 255), min(GetGValue(m_pElement->m_borderColor[3])*100/80, 255), min(GetBValue(m_pElement->m_borderColor[3])*100/80, 255));
			
			int my = brect.bottom + (prect.bottom-brect.bottom)/2;
			int tmx = brect.left + (prect.left-brect.left)/2;
			int bmx = brect.right + (prect.right-brect.right)/2;
			
			//
			LDraw::Point pt1[4] =
			{
				LDraw::Point(prect.left, prect.bottom),
				LDraw::Point(tmx, my),
				LDraw::Point(bmx, my),
				LDraw::Point(prect.right, prect.bottom),
			};
			
			pC->m_pGraphics->FillPolygon(
				&LDraw::SolidBrush(LDraw::Color(GetRValue(c1), GetGValue(c1), GetBValue(c1))),
				pt1, 4);
			
			//
			LDraw::Point pt2[4] =
			{
				LDraw::Point(brect.left, brect.bottom),
				LDraw::Point(tmx, my),
				LDraw::Point(bmx, my),
				LDraw::Point(brect.right, brect.bottom),
			};
			
			pC->m_pGraphics->FillPolygon(
				&LDraw::SolidBrush(LDraw::Color(GetRValue(c2), GetGValue(c2), GetBValue(c2))),
				pt2, 4);
		}
		break;
#endif
	}

	pC->m_pGraphics->SetSmoothingMode(oldSmoothingMode);
#endif
}

void CHTMElementBox::DrawOutline(CHTMRenderContext* pC)
{
	ASSERT(m_pElement != NULL);

	gm::RectF conRect = GetAbsInnerRect();

// padding rect
	gm::RectF padRect = conRect;
	padRect.X -= m_computedPadding[0];
	padRect.Y -= m_computedPadding[1];
	padRect.Width += m_computedPadding[0] + m_computedPadding[2];
	padRect.Height += m_computedPadding[1] + m_computedPadding[3];

	padRect.X = (int)padRect.X;
	padRect.Y = (int)padRect.Y;
	padRect.Width = (int)padRect.Width;
	padRect.Height = (int)padRect.Height;

// border rect
	gm::RectF borRect = padRect;
	borRect.X -= m_computedBorderWidth[0];
	borRect.Y -= m_computedBorderWidth[1];
	borRect.Width += m_computedBorderWidth[0] + m_computedBorderWidth[2];
	borRect.Height += m_computedBorderWidth[1] + m_computedBorderWidth[3];

	if (m_pElement->m_computedOutlineStyle != BorderStyle_none)
	{
		if (m_pElement->m_computedOutlineWidth >= 1)
		{
			ASSERT(0);
#if 0
			LDraw::CompositingMode oldmode = pC->m_pGraphics->GetCompositingMode();
			pC->m_pGraphics->SetCompositingMode(LDraw::CompositingModeBitwiseXor);

			if (m_pElement->m_computedOutlineStyle == BorderStyle_dotted)
			{
				int width = m_pElement->m_computedOutlineWidth;

				LDraw::RectF rc = borRect;
			//	rc.Inflate(-1,-1);

				DrawDotsH(pC->m_pGraphics, rc.X, rc.Y, rc.X+rc.Width, width);
				DrawDotsH(pC->m_pGraphics, rc.X, rc.Y+rc.Height, rc.X+rc.Width, width);
				DrawDotsV(pC->m_pGraphics, rc.X, rc.Y, rc.Y+rc.Height, width);
				DrawDotsV(pC->m_pGraphics, rc.X+rc.Width, rc.Y, rc.Y+rc.Height, width);

			}

			pC->m_pGraphics->SetCompositingMode(oldmode);
#endif
		}
	}
}

void CHTMElementBox::DrawChildren(CHTMRenderContext* pC)
{
#if 0	// Have this ??
	if (1)
	{
		UPOSITION pos = m_pElement->m_childList.GetHeadPosition();
		while (pos)
		{
			CPNode* pChild = (CPNode*)m_pElement->m_childList.GetNext(pos);
			pChild->m_selected = 0;
		}
	}

	if (pC->m_range)
	{
		CComPtr<ILDOMNode> startContainer;
		long startOffset;

		CComPtr<ILDOMNode> endContainer;
		long endOffset;

		pC->m_range->get_startContainer(&startContainer);
		pC->m_range->get_startOffset(&startOffset);

		pC->m_range->get_endContainer(&endContainer);
		pC->m_range->get_endOffset(&endOffset);

	//	CComPtr<ILDOMNode> parentNode;
	//	m_pElement->m_pNode->get_parentNode(&parentNode);

		if (m_pElement->m_selected & 1)
		{
			pC->m_bInSelection = TRUE;
		}

		//if (!pC->m_bInSelection)
		{
			if (startContainer == m_pElement->m_pNode)
			{
				ASSERT(startOffset < m_pElement->m_childList.GetCount());

				UPOSITION pos = m_pElement->m_childList.FindIndex(startOffset);
				CPNode* pNode = (CPNode*)m_pElement->m_childList.GetAt(pos);

				pNode->m_selected |= 1;

				/*
				int index = GetDOMNodesIndex();

				if (index == startOffset)
				{
					pC->m_bInSelection++;
				}
				*/
			}
		}

		//if (pC->m_bInSelection)
		{
			if (endContainer == m_pElement->m_pNode)
			{
	//			int index = GetDOMNodesIndex();

	//			if (index == startOffset)
				ASSERT(endOffset <= m_pElement->m_childList.GetCount());

	#if 0
				if (endOffset < m_pElement->m_childList.GetCount())
				{
					UPOSITION pos = m_pElement->m_childList.FindIndex(endOffset);
					CPNode* pNode = (CPNode*)m_pElement->m_childList.GetAt(pos);

					pNode->m_selected = -1;
					{
					//	pC->m_bInSelection--;
					}
				}
	#endif
				if (endOffset > 0)
				{
					UPOSITION pos = m_pElement->m_childList.FindIndex(endOffset-1);
					CPNode* pNode = (CPNode*)m_pElement->m_childList.GetAt(pos);

					pNode->m_selected |= 2;
					{
					//	pC->m_bInSelection--;
					}
				}
			}
		}
	}
#endif

#if 1

//	LDraw::RectF clipBounds;
//	pC->m_pGraphics->GetClipBounds(&clipBounds);

	for (int i = 0; i < m_renderChildren.GetSize(); i++)
	{
		CHTMBoxItem* pBox = m_renderChildren[i];

	//	if (clipBounds.IntersectsWith(pBox->m_outerRect))
		{
			pBox->Draw(pC);
		}
	}
#endif

#if 0	// Have this
	if (m_pElement->m_selected & 2)
	{
		pC->m_bInSelection = FALSE;
	}
#endif

	/*
	if (endContainer == m_pElement->m_pNode)
	{
		if (endOffset == m_pElement->m_childList.GetCount())
			pC->m_bInSelection = FALSE;
	}
	*/
}

/*
// virtual
CPElement* CHTMElementBox::HitTestElementBox(double x, double y)
{
	LDraw::RectF rc = GetAbsOuterRect();
	if (rc.Contains(x, y))
	{
		for (int i = 0; i < m_renderChildren.GetSize(); i++)
		{
			CHTMBoxItem* pBox = (CHTMBoxItem*)m_renderChildren[i];

			CPElement* pElement = pBox->HitTestElementBox(x, y);
			if (pElement)
				return pElement;
		}

		return m_pElement;
	}

	return NULL;
}
*/

#if 0
// TODO, returns box instead of element
bool CHTMElementBox::OnButtonDown(LDraw::PointD point, CPElementBase* *pVal)
{
	LDraw::RectF rect = GetAbsOuterRect();

	//if (rect.Contains(point.x, point.y))
	{
		for (int i = 0; i < m_children.size(); i++)
		{
			CHTMBoxItem* pBox = m_children[i];

			bool b = pBox->OnButtonDown(point, pVal);
			if (b) return b;
		}

		if (m_pElement)
		{
			BOOL b = m_pElement->OnButtonDown(point, pVal);
			return b;
		}
	}

	return FALSE;
}
#endif

}	// Web
}
