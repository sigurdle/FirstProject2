#include "stdafx.h"
#include "LXUI2.h"
#include "DropShadow.h"

/*
namespace LDraw
{
	extern DrawExt uint8 multab[256][256];
}
*/

namespace System
{
namespace UI
{

void InvalidateRenderChildren(Visual* visual);

using namespace System;

FillToStroke::FillToStroke()
{
	m_Content = NULL;
}

void FillToStroke::set_Content(UIElement* Content)
{
	if (m_Content != Content)
	{
		if (m_Content)
		{
			RemoveVisualChild(m_Content);
		}

		m_Content = Content;

		if (m_Content)
		{
			AddVisualChild(m_Content);
		}
	}
}

LDraw::SizeD FillToStroke::OnMeasure(LDraw::SizeD availSize)
{
	m_Content->Measure(availSize);
	return m_Content->get_DesiredSize();
}

void FillToStroke::OnArrange(LDraw::SizeD finalSize)
{
	m_Content->Arrange(LDraw::RectD(LDraw::PointD(0, 0), finalSize));
}

void FillToStroke::OnRender(Graphics* pGraphics)
{
	ASSERT(0);
#if 0
	Graphics graphics(new LDraw::GraphicsFillToStroke(pGraphics));
	m_Content->Render(&graphics);
#endif
}

void EditTransform::set_Content(UIElement* Content)
{
	m_Content = Content;
	ASSERT(0);
//	AddRChild(m_Content);
}

LDraw::SizeD EditTransform::OnMeasure(LDraw::SizeD availSize)
{
	m_Content->Measure(availSize);
	return m_Content->get_DesiredSize();
}

void EditTransform::OnArrange(LDraw::SizeD finalSize)
{
	ASSERT(0);
#if 0

	m_Content->Arrange(finalSize);

	m_expandedBBox = m_Content->m_expandedBBox;

	LDraw::GetTransformRectBoundingBox(m_ChildTransform, m_expandedBBox, &m_expandedBBox);

//	MessageBeep(-1);

//	m_childTransform = m_ChildTransform;

	m_expandedBBox.X -= 4;
	m_expandedBBox.Y -= 4;
	m_expandedBBox.Width += 4*2;
	m_expandedBBox.Height += 4*2;
#endif
}

void EditTransform::OnRender(Graphics* pGraphics)
{
	pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(255, 0, 160, 0)), m_expandedBBox);

	/*LDraw::Matrix3f oldTransform = */pGraphics->PushTransform();
	pGraphics->MultiplyTransform(m_ChildTransform);
	m_Content->Render(pGraphics);
	pGraphics->PopTransform();//oldTransform);
}

__release<LDraw::Matrix3f> GetRotateObjectMatrix(LDraw::PointD woldpt, LDraw::PointD wpt, double cx, double cy)
{
	double oldangleX;
	{
		double dx = woldpt.X - cx;
		double dy = woldpt.Y - cy;

		double distance = sqrt(dx*dx + dy*dy);
		double distance2 = distance;

		if (distance2 == 0.0) distance2 = 0.00001;
		if (dy < 0) distance2 =-distance2;
		double angle = acos(dx/distance2);
		if (dy < 0) angle += M_PI;

		oldangleX = angle * 180/M_PI;
	}

	double angleX;
	{
		double dx = wpt.X - cx;
		double dy = wpt.Y - cy;

		double distance = sqrt(dx*dx + dy*dy);
		double distance2 = distance;

		if (distance2 == 0.0) distance2 = 0.00001;
		if (dy < 0) distance2 =-distance2;
		double angle = acos(dx/distance2);
		if (dy < 0) angle += M_PI;

		angleX = angle * 180/M_PI;
	}

//	transform->setMatrix(transform->matrix->translate(-cx, -cy)->rotate(angleX-oldangleX)->translate(cx, cy));

//	CComQIPtr<IPDMatrix> mat0;
//	object->get_transformMatrix(&mat0);

	__release<LDraw::Matrix3f> mat1 = LDraw::Matrix3f::GetTranslate(-cx, -cy);

	__release<LDraw::Matrix3f> mat2 = *mat1 * *LDraw::Matrix3f::GetRotate(angleX-oldangleX);

	__release<LDraw::Matrix3f> mat3 = *mat2 * *LDraw::Matrix3f::GetTranslate(cx, cy);
	
	return mat3;
}

#if 0
void EditTransform::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (type == MouseEvent::mousedown)
		{
			MouseEvent* mouseEvt = static_cast<MouseEvent*>(evt);
			m_startpt = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());
		//	m_startpt.X = point->get_X();
		//	m_startpt.Y = point->get_Y();

			m_offsetPt.X = 0;
			m_offsetPt.Y = 0;

			CaptureMouse();
			m_dragging = 1;
		}
		else if (type == MouseEvent::mouseup)
		{
			ReleaseMouseCapture();
			m_dragging = 0;
		}
		else if (type == MouseEvent::mousemove)
		{
			if (m_dragging)
			{
				MouseEvent* mouseEvt = static_cast<MouseEvent*>(evt);
				LDraw::PointD pt = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

				__release<LDraw::Matrix3f> xMat;

				if (true)	// Rotate
				{
					LDraw::PointD m_pivotPt;
		//			m_pivotPt.X = bounds.X + bounds.Width/2;	// Center
		//			m_pivotPt.Y = bounds.Y + bounds.Height/2;
					m_pivotPt.X = m_computedSize.Width/2;	// Center
					m_pivotPt.Y = m_computedSize.Height/2;

					xMat = GetRotateObjectMatrix(/*w*/m_startpt, /*w*/pt, m_pivotPt.X, m_pivotPt.Y);
				}
				else	// Scale
				{
					double cx = 0;
					double cy = 0;

					double sx;
					double sy;

					sx = (/*w*/pt.X - cx)/(/*w*/m_startpt.X-m_offsetPt.X - cx);
					sy = (/*w*/pt.Y - cy)/(/*w*/m_startpt.Y-m_offsetPt.Y - cy);

					__release<LDraw::Matrix3f> mat1 = LDraw::Matrix3f::GetTranslate(-cx, -cy);

					__release<LDraw::Matrix3f> mat2 = *mat1 * *LDraw::Matrix3f::GetScale(sx, sy);

					xMat = *mat2 * *LDraw::Matrix3f::GetTranslate(cx, cy);
				}

				m_ChildTransform = xMat;
				m_childrenTransformMatrix = m_ChildTransform;

				InvalidateRender();
				InvalidateRenderChildren(this);

				((CUIFrameImpl*)GetOwnerWindow()->m_pSite)->InvalidateRegion(m_visibleWithChildrenRegion);

				((CUIFrameImpl*)GetOwnerWindow()->m_pSite)->CreateRegions();

				((CUIFrameImpl*)GetOwnerWindow()->m_pSite)->InvalidateRegion(m_visibleWithChildrenRegion);
			//	InvalidateMeasure();
				//m_Content->Invalidate();
			}
		}
	}
}
#endif

long BlurAlpha(LDraw::BitmapData* inImage, LDraw::BitmapData* outImage, int m_alphabytesPerRow, uint8* tmask, const LDraw::RectI& rect, int featherx, int feathery)
{
	ASSERT(featherx < 32);
	ASSERT(feathery < 32);

	int left = rect.X;
	int top = rect.Y;
	int right = rect.GetRight();//inImage->width-1;//r->uRect.right;
	int bottom = rect.GetBottom();//inImage->height-1;//r->uRect.bottom;

	int width = inImage->Width;//right-left+1;
	int height = inImage->Height;//bottom-top+1;

//	int m_alphabytesPerRow = width;
//	uint8* tmask = new uint8[m_alphabytesPerRow*height];

	if (left < 0) left = 0;
	if (top < 0) top = 0;
	if (right > width) right = width;
	if (bottom > height) bottom = height;

	int* filterx = new int[featherx*2+1];
	int* filtery = new int[feathery*2+1];

	int i;

	for (i = -featherx; i <= featherx; i++)
	{
		filterx[i+featherx] = featherx-abs(i)+1;
	}

	for (i = -feathery; i <= feathery; i++)
	{
		filtery[i+feathery] = feathery-abs(i)+1;
	}

// Vertical
	for (int x = left; x < right; x++)
	{
		uint8* dest = (tmask + m_alphabytesPerRow*top + x);
		uint8* src = ((uint8*)inImage->Scan0 + inImage->Stride*top + x*4 + 3);

		for (int y = top; y < bottom; y++)
		{
			int top2 = y-feathery;
			if (top2 < 0) top2 = 0;
			top2 = top2-y;

			int bottom2 = y+feathery;
			if (bottom2 > height-1) bottom2 = height-1;
			bottom2 = bottom2-y;

			uint8* src2 = (src + top2*inImage->Stride);
			uint32	blue = 0;
			uint32 num = 0;

			top2 += feathery;
			bottom2 += feathery;

#define BlurY 	{		int radius2 = *pfiltery++;	num += radius2;	blue += *src2 * radius2;	src2 += inImage->Stride;	}

			int n = bottom2 - top2;
			int* pfiltery = filtery + top2;

			switch (n)
			{
			case 31: BlurY;
			case 30: BlurY;
			case 29: BlurY;
			case 28: BlurY;
			case 27: BlurY;
			case 26: BlurY;
			case 25: BlurY;
			case 24: BlurY;
			case 23: BlurY;
			case 22: BlurY;
			case 21: BlurY;
			case 20: BlurY;
			case 19: BlurY;
			case 18: BlurY;
			case 17: BlurY;
			case 16: BlurY;
			case 15: BlurY;
			case 14: BlurY;
			case 13: BlurY;
			case 12: BlurY;
			case 11: BlurY;
			case 10: BlurY;
			case 9: BlurY;
			case 8: BlurY;
			case 7: BlurY;
			case 6: BlurY;
			case 5: BlurY;
			case 4: BlurY;
			case 3: BlurY;
			case 2: BlurY;
			case 1: BlurY;
			}
			BlurY;

			/*
			for (int y2 = top2; y2 <= bottom2; y2++)
			{
				BlurY
			}
			*/

			*dest = (uint8)(blue/num);

			src += inImage->Stride;
			dest += m_alphabytesPerRow;
		}
	}

// Horizontal
	for (int y = top; y < bottom; y++)
	{
		uint8* src = (tmask + m_alphabytesPerRow*y + left);
		uint8* dest = ((uint8*)outImage->Scan0 + outImage->Stride*y + left*4 + 3);

		for (int x = left; x < right; x++)
		{
			int left2 = x-featherx;
		//	ASSERT(left2 >= 0);
			if (left2 < 0) left2 = 0;
			left2 = left2-x;

			int right2 = x+featherx;	// +featherx ??
		//	ASSERT(right2 < width);
			if (right2 > width-1) right2 = width-1;
			right2 = right2-x;

			uint8* src2 = (src + left2);
			uint32	blue = 0;
			uint32 num = 0;

			/*
			for (int x2 = left2; x2 <= right2; x2++)
			{
				int radius2 = filterx[x2+featherx];
				num += radius2;

				blue += src2[3] *radius2;

				src2 += 4;
			}
			*/
#define BlurX	{	int radius2 = *pfilterx++; 	num += radius2;	blue += *src2 * radius2;	src2 += 1;	}

			int n = right2 - left2;
			int* pfilterx = filterx + left2 + featherx;

			switch (n)
			{
			case 31: BlurX;
			case 30: BlurX;
			case 29: BlurX;
			case 28: BlurX;
			case 27: BlurX;
			case 26: BlurX;
			case 25: BlurX;
			case 24: BlurX;
			case 23: BlurX;
			case 22: BlurX;
			case 21: BlurX;
			case 20: BlurX;
			case 19: BlurX;
			case 18: BlurX;
			case 17: BlurX;
			case 16: BlurX;
			case 15: BlurX;
			case 14: BlurX;
			case 13: BlurX;
			case 12: BlurX;
			case 11: BlurX;
			case 10: BlurX;
			case 9: BlurX;
			case 8: BlurX;
			case 7: BlurX;
			case 6: BlurX;
			case 5: BlurX;
			case 4: BlurX;
			case 3: BlurX;
			case 2: BlurX;
			case 1: BlurX;
			}
			BlurX;

			*dest = (uint8)(blue/num);

			src += 1;
			dest += 4;
		}
	}

//	delete [] tmask;

	return 0;
}

long BlurAlphaY(LDraw::BitmapData* inImage, /*LDraw::BitmapData* outImage,*/ int m_alphabytesPerRow, uint8* tmask, const LDraw::RectI& rect, /*int featherx,*/ int feathery)
{
//	ASSERT(featherx < 32);
	ASSERT(feathery <= 15);

	int left = rect.X;
	int top = rect.Y;
	int right = rect.GetRight();//inImage->width-1;//r->uRect.right;
	int bottom = rect.GetBottom();//inImage->height-1;//r->uRect.bottom;

	int width = inImage->Width;//right-left+1;
	int height = inImage->Height;//bottom-top+1;

//	int m_alphabytesPerRow = width;
//	uint8* tmask = new uint8[m_alphabytesPerRow*height];

	if (left < 0) left = 0;
	if (top < 0) top = 0;
	if (right > width) right = width;
	if (bottom > height) bottom = height;

//	int* filterx = new int[featherx*2+1];
	int* filtery = new int[feathery*2+1];

	int i;

	/*
	for (i = -featherx; i <= featherx; i++)
	{
		filterx[i+featherx] = featherx-abs(i)+1;
	}
	*/

	for (i = -feathery; i <= feathery; i++)
	{
		filtery[i+feathery] = feathery-abs(i)+1;
	}

// Vertical
	for (int x = left; x < right; x++)
	{
		uint8* dest = (tmask + m_alphabytesPerRow*top + x);
		uint8* src = ((uint8*)inImage->Scan0 + inImage->Stride*top + x*4 + 3);

		for (int y = top; y < bottom; y++)
		{
			int top2 = y-feathery;
			if (top2 < 0) top2 = 0;
			top2 = top2-y;

			int bottom2 = y+feathery;
			if (bottom2 > height-1) bottom2 = height-1;
			bottom2 = bottom2-y;

			uint8* src2 = (src + top2*inImage->Stride);
			uint32	blue = 0;
			uint32 num = 0;

			top2 += feathery;
			bottom2 += feathery;

#define BlurY 	{		int radius2 = *pfiltery++;	num += radius2;	blue += *src2 * radius2;	src2 += inImage->Stride;	}

			int n = bottom2 - top2;
			int* pfiltery = filtery + top2;

			switch (n)
			{
			case 31: BlurY;
			case 30: BlurY;
			case 29: BlurY;
			case 28: BlurY;
			case 27: BlurY;
			case 26: BlurY;
			case 25: BlurY;
			case 24: BlurY;
			case 23: BlurY;
			case 22: BlurY;
			case 21: BlurY;
			case 20: BlurY;
			case 19: BlurY;
			case 18: BlurY;
			case 17: BlurY;
			case 16: BlurY;
			case 15: BlurY;
			case 14: BlurY;
			case 13: BlurY;
			case 12: BlurY;
			case 11: BlurY;
			case 10: BlurY;
			case 9: BlurY;
			case 8: BlurY;
			case 7: BlurY;
			case 6: BlurY;
			case 5: BlurY;
			case 4: BlurY;
			case 3: BlurY;
			case 2: BlurY;
			case 1: BlurY;
			}
			BlurY;

			/*
			for (int y2 = top2; y2 <= bottom2; y2++)
			{
				BlurY
			}
			*/

			*dest = (uint8)(blue/num);

			src += inImage->Stride;
			dest += m_alphabytesPerRow;
		}
	}


//	delete [] tmask;

	return 0;
}

long BlurAlphaX(/*LDraw::BitmapData* inImage,*/ LDraw::BitmapData* outImage, int m_alphabytesPerRow, uint8* tmask, const LDraw::RectI& rect, int featherx/*, int feathery*/)
{
	ASSERT(featherx <= 15);
//	ASSERT(feathery < 32);

	int left = rect.X;
	int top = rect.Y;
	int right = rect.GetRight();//inImage->width-1;//r->uRect.right;
	int bottom = rect.GetBottom();//inImage->height-1;//r->uRect.bottom;

	int width = outImage->Width;//right-left+1;
	int height = outImage->Height;//bottom-top+1;

//	int m_alphabytesPerRow = width;
//	uint8* tmask = new uint8[m_alphabytesPerRow*height];

	if (left < 0) left = 0;
	if (top < 0) top = 0;
	if (right > width) right = width;
	if (bottom > height) bottom = height;

	int* filterx = new int[featherx*2+1];
//	int* filtery = new int[feathery*2+1];

	int i;

	for (i = -featherx; i <= featherx; i++)
	{
		filterx[i+featherx] = featherx-abs(i)+1;
	}

	/*
	for (i = -feathery; i <= feathery; i++)
	{
		filtery[i+feathery] = feathery-abs(i)+1;
	}
	*/

// Horizontal
	for (int y = top; y < bottom; y++)
	{
		uint8* src = (tmask + m_alphabytesPerRow*y + left);
		uint8* dest = ((uint8*)outImage->Scan0 + outImage->Stride*y + left*4 + 3);

		for (int x = left; x < right; x++)
		{
			int left2 = x-featherx;
		//	ASSERT(left2 >= 0);
			if (left2 < 0) left2 = 0;
			left2 = left2-x;

			int right2 = x+featherx;	// +featherx ??
		//	ASSERT(right2 < width);
			if (right2 > width-1) right2 = width-1;
			right2 = right2-x;

			uint8* src2 = (src + left2);
			uint32	blue = 0;
			uint32 num = 0;

			/*
			for (int x2 = left2; x2 <= right2; x2++)
			{
				int radius2 = filterx[x2+featherx];
				num += radius2;

				blue += src2[3] *radius2;

				src2 += 4;
			}
			*/
#define BlurX	{	int radius2 = *pfilterx++; 	num += radius2;	blue += *src2 * radius2;	src2 += 1;	}

			int n = right2 - left2;
			int* pfilterx = filterx + left2 + featherx;

			switch (n)
			{
			case 31: BlurX;
			case 30: BlurX;
			case 29: BlurX;
			case 28: BlurX;
			case 27: BlurX;
			case 26: BlurX;
			case 25: BlurX;
			case 24: BlurX;
			case 23: BlurX;
			case 22: BlurX;
			case 21: BlurX;
			case 20: BlurX;
			case 19: BlurX;
			case 18: BlurX;
			case 17: BlurX;
			case 16: BlurX;
			case 15: BlurX;
			case 14: BlurX;
			case 13: BlurX;
			case 12: BlurX;
			case 11: BlurX;
			case 10: BlurX;
			case 9: BlurX;
			case 8: BlurX;
			case 7: BlurX;
			case 6: BlurX;
			case 5: BlurX;
			case 4: BlurX;
			case 3: BlurX;
			case 2: BlurX;
			case 1: BlurX;
			}
			BlurX;

			*dest = (uint8)(blue/num);

			src += 1;
			dest += 4;
		}
	}

//	delete [] tmask;

	return 0;
}

/////////////////////////////////////////////////////////////////////////
// DropShadow

DropShadow::DropShadow()
{
	m_BlurRadius = 12;
	m_OffsetX = 3;
	m_OffsetY = 3;

	m_ShadowOpacity = 1;
	m_Color = Color::FromRgb(0, 0, 0);

/*
	m_BlurRadius = 0;
	m_OffsetX = 0;
	m_OffsetY = 0;
	*/
}

void DropShadow::set_OffsetX(double offsetX)
{
	m_OffsetX = offsetX;
	InvalidateMeasure();
}

void DropShadow::set_OffsetY(double offsetY)
{
	m_OffsetY = offsetY;
	InvalidateMeasure();
}

void DropShadow::set_Content(UIElement* Content)
{
	ASSERT(0);
/*
	m_Content = Content;
	AddRChild(m_Content);
	*/
}

#if 0
void DropShadow::InvalidateChildRect(const LDraw::RectD& rect, LDraw::Matrix3f* transform)
{
	/*
	LDraw::RectD xrect = rect;

	xrect.X -= m_OffsetX-m_BlurRadius;
	xrect.Y -= m_OffsetY-m_BlurRadius;
	xrect.Width += m_BlurRadius*2;
	xrect.Height += m_BlurRadius*2;
	*/

	LDraw::RectD shadowRect = rect;
	shadowRect.X -= m_OffsetX - m_BlurRadius;
	shadowRect.Y -= m_OffsetY - m_BlurRadius;
	shadowRect.Width += m_BlurRadius*2;
	shadowRect.Height += m_BlurRadius*2;

	LDraw::RectD xrect;
	LDraw::RectD::Union(xrect, rect, shadowRect);

	GetRParent()->InvalidateChildRect(xrect, *transform * *GetParentToElementTransformMatrix());
}
#endif

void DropShadow::InvalidateRect(const LDraw::RectD& rect)
{
	LDraw::RectD shadowRect = rect;
	shadowRect.X -= m_OffsetX - m_BlurRadius;
	shadowRect.Y -= m_OffsetY - m_BlurRadius;
	shadowRect.Width += m_BlurRadius*2;
	shadowRect.Height += m_BlurRadius*2;

	LDraw::RectD xrect;
	LDraw::RectD::Union(xrect, rect, shadowRect);

	/*
	xrect.X -= m_OffsetX-m_BlurRadius;
	xrect.Y -= m_OffsetY-m_BlurRadius;
	xrect.Width += m_BlurRadius*2;
	xrect.Height += m_BlurRadius*2;
	*/

	//if (GetRParent())
	{
		/*
		LDraw::RectD xrect = rect;
		xrect.X -= 6;
		xrect.Y -= 6;
		xrect.Width += 16;
		xrect.Height += 16;
		*/

		UIElement::InvalidateRect(xrect);
	}
}

Visual* DropShadow::HitTestElement(LDraw::Matrix3f* matrix, LDraw::PointD pt)
{
//	pt.X += m_expandedBBox.X;
//	pt.Y += m_expandedBBox.Y;

	return UIElement::HitTestElement(matrix, pt);
}

LDraw::SizeD DropShadow::OnMeasure(LDraw::SizeD availSize)
{
	m_Content->Measure(availSize);
	return m_Content->get_DesiredSize();
}

void DropShadow::OnArrange(LDraw::SizeD finalSize)
{
	ASSERT(0);
#if 0

	m_Content->Arrange(finalSize);

	LDraw::RectD imageRect;
	imageRect.X = 0;
	imageRect.Y = 0;
	imageRect.Width = m_computedSize.Width;
	imageRect.Height = m_computedSize.Height;

	LDraw::RectD shadowRect;
	shadowRect.X = m_OffsetX - m_BlurRadius;
	shadowRect.Y = m_OffsetY - m_BlurRadius;
	shadowRect.Width = m_computedSize.Width + m_BlurRadius*2;
	shadowRect.Height = m_computedSize.Height + m_BlurRadius*2;

	LDraw::RectD::Union(m_expandedBBox, imageRect, shadowRect);
	/*
	m_expandedBBox = 
	m_expandedBBox.Y = -m_BlurRadius;
	m_expandedBBox.Width = m_computedSize.Width+16;
	m_expandedBBox.Height = m_computedSize.Height+16;
	*/
#endif
}

void DropShadow::OnRender(Graphics* pGraphics)
{
	LDraw::RectD bounds;
	pGraphics->GetClipBounds(&bounds);

/*
	bounds.X = 0;
	bounds.Y = 0;
	bounds.Width = m_computedSize.Width + m_BlurRadius*2;
	bounds.Height = m_computedSize.Height + m_BlurRadius*2;
*/
	TRACE("bounds: %g, %g, %g, %g\n", bounds.X, bounds.Y, bounds.Width, bounds.Height);
	TRACE("expandedBBox: %g, %g, %g, %g\n", m_expandedBBox.X, m_expandedBBox.Y, m_expandedBBox.Width, m_expandedBBox.Height);


	/*
	if (bounds.X < -m_BlurRadius)
		bounds.X = 0;

	if (bounds.Y < 0)
		bounds.Y = 0;

	if (bounds.Width > m_computedSize.Width)
		bounds.Width = m_computedSize.Width;

	if (bounds.Height > m_computedSize.Height)
		bounds.Height = m_computedSize.Height;
		*/

#if 1	// Have this
	bounds.X -= m_BlurRadius;
	bounds.Y -= m_BlurRadius;
	bounds.Width += m_BlurRadius*2;
	bounds.Height += m_BlurRadius*2;
#endif
	LDraw::RectD::Intersect(bounds, bounds, LDraw::RectD(0, 0, m_computedSize.Width+m_BlurRadius*2, m_computedSize.Height+m_BlurRadius*2));

	__release<LDraw::Region> rgn = new LDraw::Region(LDraw::RectI(bounds.X, bounds.Y, bounds.Width, bounds.Height));
	//rgn.From();
	{
#if 0	// Have this
		Graphics* graphics(new LDraw::GraphicsO());
		graphics.TranslateTransform(m_BlurRadius, m_BlurRadius);
		m_Content->Clip(&graphics, rgn);
#endif
	}

#if 0	// TODO, have this
	if (rgn.IsEmpty())
	{
		m_Content->Render(pGraphics);
		MessageBeep(-1);
	}
	else
#endif
	{
		if (m_computedSize.Width <= 0 || m_computedSize.Height <= 0)
			return;

		LDraw::Bitmap* alphaBitmap = new LDraw::Bitmap(m_computedSize.Width+m_BlurRadius*2, m_computedSize.Height+m_BlurRadius*2, LDraw::PixelFormat_t::RGBAP_32);
		{
			ASSERT(0);
#if 0
			Graphics* graphics = new Graphics(new LDraw::GraphicsO(alphaBitmap));
			graphics->TranslateTransform(m_BlurRadius, m_BlurRadius);
			m_Content->Render(graphics);
#endif
		}

		LDraw::Bitmap* bitmap = alphaBitmap->Clone(LDraw::RectI(m_BlurRadius, m_BlurRadius, m_computedSize.Width, m_computedSize.Height));

		LDraw::BitmapData in;
		alphaBitmap->LockBits(NULL, LDraw::ImageLockModeRead, &in);
		/*
		in.Scan0 = pAlphaBitmap->GetBitmapData();
		in.Stride = pAlphaBitmap->GetRowBytes();
		in.Width = pAlphaBitmap->GetWidth();
		in.Height = pAlphaBitmap->GetHeight();
		*/

		ASSERT(0);
#if 0
		{
			uint8* tmask = new uint8[in.Width*in.Height];

			{
				LDraw::Span* span = rgn.m_p->m_spans;
				while (span)
				{
					LDraw::Span* spannext = span->next;

					LDraw::Segment* segment = span->x;

					if (segment)
					{
						LDraw::BBox bbox;
						int top = span->y;
						int height = spannext->y - top;
						do
						{
							LDraw::Segment* segmentnext = segment->next;
							ASSERT(segmentnext != NULL);
							int left = segment->x;
							int width = segmentnext->x - left;

//							BitBlt(dc, left, top, width, height, offdc, left, top, SRCCOPY);
							BlurAlphaY(&in, in.Width, tmask, LDraw::RectI(left-m_BlurRadius*1, top-m_BlurRadius*1, width+m_BlurRadius*2, height+m_BlurRadius*2), m_BlurRadius);

							segment = segmentnext->next;
						}
						while (segment);
					}

					span = spannext;
				}
			}

			{
				LDraw::Span* span = rgn->m_spans;
				while (span)
				{
					LDraw::Span* spannext = span->next;

					LDraw::Segment* segment = span->x;

					if (segment)
					{
						LDraw::BBox bbox;
						int top = span->y;
						int height = spannext->y - top;
						do
						{
							LDraw::Segment* segmentnext = segment->next;
							ASSERT(segmentnext != NULL);
							int left = segment->x;
							int width = segmentnext->x - left;

						//	BitBlt(dc, left, top, width, height, offdc, left, top, SRCCOPY);
							BlurAlphaX(&in, in.Width, tmask, LDraw::RectI(left-m_BlurRadius*1, top-m_BlurRadius*1, width+m_BlurRadius*2, height+m_BlurRadius*2), m_BlurRadius);

							segment = segmentnext->next;
						}
						while (segment);
					}

					span = spannext;
				}
			}

			//ASSERT(0);
#if 0	// TODO
			{
				for (LDraw::RegionRect* pRect = rgn.m_p->m_rect; pRect; pRect = pRect->m_next)
				{
					BlurAlphaY(&in, in.Width, tmask, LDraw::RectI(pRect->m_bbox.left-m_BlurRadius*1, pRect->m_bbox.top-m_BlurRadius*1, pRect->m_bbox.Width()+m_BlurRadius*2, pRect->m_bbox.Height()+m_BlurRadius*2), m_BlurRadius);
				}
			}

			{
				for (LDraw::RegionRect* pRect = rgn.m_p->m_rect; pRect; pRect = pRect->m_next)
				{
					BlurAlphaX(&in, in.Width, tmask, LDraw::RectI(pRect->m_bbox.left-m_BlurRadius*1, pRect->m_bbox.top-m_BlurRadius*1, pRect->m_bbox.Width()+m_BlurRadius*2, pRect->m_bbox.Height()+m_BlurRadius*2), m_BlurRadius);
				}
			}
#endif

			delete[] tmask;
		}
#endif

		{
			uint8 opacity = MAX(0, MIN(255, (int)(m_ShadowOpacity*255)));

			uint8 r = m_Color.get_R();
			uint8 g = m_Color.get_G();
			uint8 b = m_Color.get_B();
			uint8 a = m_Color.get_A() * opacity/255;

//			LDraw::RectI bo(0, 0, m_expandedBBox.Width, m_expandedBBox.Height);
//			rgn.Intersect(bo);

			/*
			for (LDraw::RegionRect* pRect = rgn.m_p->m_rect; pRect; pRect = pRect->m_next)
			{
				LDraw::BBox bbox = pRect->m_bbox;
				bbox.left -= m_expandedBBox.X;
				bbox.top -= m_expandedBBox.Y;
				bbox.right -= m_expandedBBox.X;
				bbox.bottom -= m_expandedBBox.Y;
				*/

				uint8* rowptr = in.Scan0;// + in.Stride * bbox.top + (bbox.left*4);
				for (int y = 0/*bbox.top*/; y < in.Height/*bbox.bottom*/; y++)
				{
					uint8* p = rowptr;
					for (int x = 0/*bbox.left*/; x < in.Width/*bbox.right*/; x++)
					{
						p[3] = LDraw::multab[p[3]][a];
						p[2] = LDraw::multab[p[3]][r];
						p[1] = LDraw::multab[p[3]][g];
						p[0] = LDraw::multab[p[3]][b];

						ASSERT(p[3] >= p[0]);
						ASSERT(p[3] >= p[1]);
						ASSERT(p[3] >= p[2]);
						p += 4;
					}
					rowptr += in.Stride;
				}
		//	}
		}

		alphaBitmap->UnlockBits(&in);

		{
		//	pGraphics->SetCompositingMode(LDraw::CompositingModeMultiply);

			pGraphics->PushClip();

			__release<LDraw::Region> pOldRgn = pGraphics->GetClip();

			LDraw::Region* rgn = pOldRgn;
		//	rgn.From(&pOldRgn);
			ASSERT(0);
#if 0
		//	rgn.From(LDraw::RectI(bounds.X, bounds.Y, bounds.Width, bounds.Height));
			m_Content->Clip(pGraphics, rgn);
#endif
			// TODO , Intersect instead of Set ??
			//pGraphics->SetClip(rgn);
			pGraphics->IntersectClip(rgn);

			pGraphics->DrawImage(alphaBitmap, m_OffsetX - m_BlurRadius, m_OffsetY - m_BlurRadius);
			pGraphics->PopClip();//&pOldRgn);

		//	pGraphics->SetCompositingMode(LDraw::CompositingModeSourceOver);
		}

		pGraphics->DrawImage(bitmap, 0, 0);

		//delete pAlphaBitmap;

		//delete pBitmap;
	}
}

}	// UI
}
