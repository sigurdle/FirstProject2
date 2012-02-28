#include "stdafx.h"
#include "LXUI2.h"
#include "ScrollViewer.h"

namespace System
{
namespace UI
{

ScrollContentPresenter::ScrollContentPresenter()
{
}

void ScrollContentPresenter::OnRender(Graphics* pGraphics)
{
	pGraphics->TranslateTransform(-m_horizontalOffset, -m_verticalOffset);
	ContentPresenter::OnRender(pGraphics);
}

LDraw::SizeD ScrollContentPresenter::MeasureOverride(LDraw::SizeD availSize)
{
	// ??
	return ContentPresenter::MeasureOverride(LDraw::SizeD(99999, 99999));
}

LDraw::SizeD ScrollContentPresenter::ArrangeOverride(LDraw::SizeD finalSize)
{
	// ??
	m_viewportSize = finalSize;
	m_scrollOwner->InvalidateScrollInfo();
	return ContentPresenter::ArrangeOverride(get_DesiredSize());
}

ScrollViewer* ScrollContentPresenter::get_ScrollOwner()
{
	return m_scrollOwner;
}

void ScrollContentPresenter::set_ScrollOwner(ScrollViewer* scrollOwner)
{
	m_scrollOwner = scrollOwner;
}

double ScrollContentPresenter::get_ExtentWidth()
{
	return get_DesiredSize().Width;
}

double ScrollContentPresenter::get_ExtentHeight()
{
	return get_DesiredSize().Height;
}

double ScrollContentPresenter::get_ViewportWidth()
{
	return m_viewportSize.Width;
}

double ScrollContentPresenter::get_ViewportHeight()
{
	return m_viewportSize.Height;
}

double ScrollContentPresenter::get_HorizontalOffset()
{
	return m_horizontalOffset;
}

double ScrollContentPresenter::get_VerticalOffset()
{
	return m_verticalOffset;
}

void ScrollContentPresenter::SetHorizontalOffset(double horizontalOffset)
{
	m_horizontalOffset = horizontalOffset;
	InvalidateRender();
}

void ScrollContentPresenter::SetVerticalOffset(double verticalOffset)
{
	m_verticalOffset = verticalOffset;
	InvalidateRender();
}

}	// UI
}
