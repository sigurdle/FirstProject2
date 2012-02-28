#include "stdafx.h"
#include "LXUI2.h"
#include "ScrollViewer.h"

namespace System
{
namespace UI
{

void InvalidateRenderChildren(Visual* visual)
{
	//visual->m_windowTransform = NULL;
	//visual->m_bRenderValid = false;

#if 0	// TODO, not sure
	if (visual->get_VisualTree())
	{
		visual->get_VisualTree()->m_windowToElementTransform = NULL;
		visual->get_VisualTree()->m_bRenderValid = false;
		InvalidateRenderChildren(visual->get_VisualTree());
	}
#endif

	int ncount = visual->get_VisualChildrenCount();
	for (int i = 0; i < ncount; i++)
	{
		Visual* child = visual->GetVisualChild(i);

		child->m_windowToElementTransform = NULL;
		child->m_bRenderValid = false;

		InvalidateRenderChildren(child);
	}
}

Viewbox::Viewbox()
{
	m_Transform = NULL;
}

void Viewbox::set_Transform(Transform* transform)
{
	/*
	if (m_Transform)
	{
		m_Transform->Release();
	}
	*/
	m_Transform = transform;
	m_childrenTransformMatrix = m_Transform->get_Value();
	/*
	if (m_Transform)
	{
		m_Transform->AddRef();
	}
	*/
	//Invalidate();
}

void Viewbox::OnChildDesiredSizeChanged(UIElement* child)
{
	UIElement::OnChildDesiredSizeChanged(child);

	ASSERT(0);
#if 0
	m_pScroller->OnChildDesiredSizeChanged(child);
#endif
}

LDraw::SizeD Viewbox::OnMeasure(LDraw::SizeD availSize)
{
	UIElement* child = get_Child();//(*get_rchildList())[0];
	child->Measure(availSize);

	return child->get_DesiredSize();//OnMeasure(availSize);
}

void Viewbox::OnArrange(LDraw::SizeD finalSize)
{
	InvalidateRenderChildren(this);

	//UIElement::OnArrange(finalSize);
	UIElement* child = get_Child();//(*get_rchildList())[0];

	child->Arrange(LDraw::RectD(0, 0, child->get_DesiredSize().Width, child->get_DesiredSize().Height));

//	m_Content->Arrange(LDraw::SizeD(m_Content->m_desiredWidth, m_Content->m_desiredHeight));

	// Must override this so we can clip, the default is to calculate expandedBBox also based on children
	// TODO, change things so this is unecessary ??
	m_expandedBBox.X = 0;
	m_expandedBBox.Y = 0;
	m_expandedBBox.Width = m_computedSize.Width;
	m_expandedBBox.Height = m_computedSize.Height;
}

LDraw::PointD Viewbox::TransformPointToClient(LDraw::PointD point)
{
	if (m_Transform)
	{
		return (*GetParentToElementTransformMatrix() * *m_Transform->get_Value())->GetInverse()->Transform(point);
//		return (GetParentToElementTransformMatrix())->GetInverse()->Transform(point);
	}
	else
	{
		return GetParentToElementTransformMatrix()->GetInverse()->Transform(point);
	}
}

Visual* Viewbox::HitTestChildren(LDraw::Matrix3f* transform, LDraw::PointD pt)
{
	if (m_Transform)
	{
		return UIElement::HitTestChildren(*transform * *m_Transform->get_Value(), pt);
	}
	else
	{
		return UIElement::HitTestChildren(transform, pt);
	}
}

#if 0
void Viewbox::InvalidateChildRect(const LDraw::RectD & rect, LDraw::Matrix3f* transform)
{
	if (m_Transform)
	{
		UIElement::InvalidateChildRect(rect, *transform * *m_Transform->get_Value());
	}
	else
	{
		UIElement::InvalidateChildRect(rect, transform);
	}
}
#endif

void Viewbox::_OnRender(Graphics* pGraphics)
{
	UIElement::_OnRender(pGraphics);
//	return;

#if 0
#if 0
		OnRender(pGraphics);
#else
	m_crit.Lock();

	if (!m_bRenderValid)
	{
		m_pDrawCommands = new LDraw::Commands;
		LDraw::GraphicsMetafile* pMetafile = new LDraw::GraphicsMetafile(m_pDrawCommands);

		LDraw::RectF clipBounds(m_expandedBBox.X, m_expandedBBox.Y, m_expandedBBox.Width, m_expandedBBox.Height);

		pMetafile->m_clip = new LDraw::Region(clipBounds);

	// should I?
		// LDraw::GetTransformRectBoundingBox(pGraphics->GetTransform().Inverse(), clip, &clip);

		Graphics* graphics = new Graphics(pMetafile);
		graphics->m_clip2 = clipBounds;

		OnRender(graphics);
		m_bRenderValid = true;
	}

	m_crit.Unlock();

//	LDraw::Matrix oldTransform = pGraphics->GetTransform();
//	LDraw::Region oldClip;
//	pGraphics->GetClip(&oldClip);
	pGraphics->PushTransform();
	pGraphics->PushClip();

	/*
	m_crit.Lock();

	LDraw::_Commands commands = m_pDrawCommands;	// This AddRefs

	m_crit.Unlock();
	*/

	pGraphics->RenderCommands(m_pDrawCommands);

//	pGraphics->SetTransform(oldTransform);
//	pGraphics->SetClip(&oldClip);
	pGraphics->PopTransform();
	pGraphics->PopClip();

#endif
#endif
}

void Viewbox::OnRender(Graphics* pGraphics)
{

//	UIElement::OnRender(pGraphics);
//	return;

//	LDraw::Clip oldClip = pGraphics->m_clip;
//	pGraphics->SetClip(LDraw::RectF(0, 0, m_computedWidth, m_computedHeight), LDraw::CombineModeIntersect);
	/*LDraw::Matrix3f oldTransform =*/ pGraphics->PushTransform();
//	pGraphics->TranslateTransform(-m_horz->get_pos() * m_Content->m_computedWidth, -m_vert->get_pos() * m_Content->m_computedHeight);

	if (m_Transform)
		pGraphics->MultiplyTransform(m_Transform->get_Value());
	
	//MessageBeep(-1);

	/*
	long size = get_rchildList().get_Size();
	for (int i = 0; i < size; i++)
	{
		IVisualChild* pElement = get_rchildList()[i];

		pElement->Render(pGraphics);
	}
	*/
	get_Child()->Render(pGraphics);

	pGraphics->PopTransform();//oldTransform);
//	pGraphics->m_clip = oldClip;
}

//void ApplyStyle(Style* style, FrameworkElement* element);
//Object* CreateObjectFromElement(Type* pType, Object* parentObject, XmlData::Node* node, Type** pReturnType);

__live_object_ptr<Style> ScrollViewerStyle;

DependencyProperty* ScrollViewer::s_ExtentWidthProperty = RegisterProperty(WSTR("ExtentWidth"), typeid(double), typeid(ScrollViewer), NULL, PropertyMetaData(None));
DependencyProperty* ScrollViewer::s_ExtentHeightProperty = RegisterProperty(WSTR("ExtentHeight"), typeid(double), typeid(ScrollViewer), NULL, PropertyMetaData(None));
DependencyProperty* ScrollViewer::s_ScrollableWidthProperty = RegisterProperty(WSTR("ScrollableWidth"), typeid(double), typeid(ScrollViewer), NULL, PropertyMetaData(None));
DependencyProperty* ScrollViewer::s_ScrollableHeightProperty = RegisterProperty(WSTR("ScrollableHeight"), typeid(double), typeid(ScrollViewer), NULL, PropertyMetaData(None));
DependencyProperty* ScrollViewer::s_ViewportWidthProperty = RegisterProperty(WSTR("ViewportWidth"), typeid(double), typeid(ScrollViewer), NULL, PropertyMetaData(None));
DependencyProperty* ScrollViewer::s_ViewportHeightProperty = RegisterProperty(WSTR("ViewportHeight"), typeid(double), typeid(ScrollViewer), NULL, PropertyMetaData(None));
DependencyProperty* ScrollViewer::s_HorizontalOffsetProperty = RegisterProperty(WSTR("HorizontalOffset"), typeid(double), typeid(ScrollViewer), NULL, PropertyMetaData(None));
DependencyProperty* ScrollViewer::s_VerticalOffsetProperty = RegisterProperty(WSTR("VerticalOffset"), typeid(double), typeid(ScrollViewer), NULL, PropertyMetaData(None));

ScrollViewer::ScrollViewer()
{
	m_horz = NULL;
	m_vert = NULL;
//	m_Content = NULL;
//	m_viewBox = NULL;

	if (ScrollViewerStyle == NULL)
	{
		XmlData::Document* document = new XmlData::Document;

		StringW* filename = MakeFilePath(_Module, L"../../../ScrollViewerStyle.lxui");
		document->load(filename);

		Type* returnType;
		ScrollViewerStyle = dynamic_cast<Style*>(CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType));
	}

	set_Style(ScrollViewerStyle);
/*
	ApplyStyle(get_Style(), this);
	//	UpdatedVisualTree();	// ??
	InitScript();
	*/
}

ScrollViewer::~ScrollViewer()
{
}

void ScrollViewer::OnPropertyChanged(DependencyPropertyChangedEventArgs args)
{
	if (args.get_Property() == get_HorizontalOffsetProperty())
	{
		m_scrollInfo->SetHorizontalOffset(get_HorizontalOffset());
	}
	else if (args.get_Property() == get_VerticalOffsetProperty())
	{
		m_scrollInfo->SetVerticalOffset(get_VerticalOffset());
	}

	ContentControl::OnPropertyChanged(args);
}

void ScrollViewer::OnApplyTemplate()
{
	ContentControl::OnApplyTemplate();

	m_scrollInfo = dynamic_cast<IScrollInfo*>(get_VisualTree()->FindByType((ClassType*)typeid(IScrollInfo).GetType()));
	if (m_scrollInfo == NULL)
	{
		ASSERT(0);
		throw std::exception("m_scollInfo = NULL");
	}

	m_scrollInfo->set_ScrollOwner(this);

	InvalidateScrollInfo();
}

void ScrollViewer::InvalidateScrollInfo()
{
	VERIFY(m_scrollInfo);

	double extentWidth = m_scrollInfo->get_ExtentWidth();
	double extentHeight = m_scrollInfo->get_ExtentHeight();

	double viewportWidth = m_scrollInfo->get_ViewportWidth();
	double viewportHeight = m_scrollInfo->get_ViewportHeight();

//	double horizontalOffset = m_scrollInfo->get_HorizontalOffset();
//	double verticalOffset = m_scrollInfo->get_VerticalOffset();

	SetValue(get_ExtentWidthProperty(), DoubleObject::GetObject(extentWidth));
	SetValue(get_ExtentHeightProperty(), DoubleObject::GetObject(extentHeight));
	SetValue(get_ScrollableWidthProperty(), DoubleObject::GetObject(extentWidth));
	SetValue(get_ScrollableHeightProperty(), DoubleObject::GetObject(extentHeight));
	SetValue(get_ViewportWidthProperty(), DoubleObject::GetObject(viewportWidth));
	SetValue(get_ViewportHeightProperty(), DoubleObject::GetObject(viewportHeight));
}

double ScrollViewer::get_ScrollableWidth()
{
	Object* value = GetValue(get_ScrollableWidthProperty());
	if (value == NULL) return 0;
	return static_cast<DoubleObject*>(value)->GetValue();
}

double ScrollViewer::get_ScrollableHeight()
{
	Object* value = GetValue(get_ScrollableHeightProperty());
	if (value == NULL) return 0;
	return static_cast<DoubleObject*>(value)->GetValue();
}

double ScrollViewer::get_ViewportWidth()
{
	Object* value = GetValue(get_ViewportWidthProperty());
	if (value == NULL) return 0;
	return static_cast<DoubleObject*>(value)->GetValue();
}

double ScrollViewer::get_ViewportHeight()
{
	Object* value = GetValue(get_ViewportHeightProperty());
	if (value == NULL) return 0;
	return static_cast<DoubleObject*>(value)->GetValue();
}

double ScrollViewer::get_HorizontalOffset()
{
	Object* value = GetValue(get_HorizontalOffsetProperty());
	if (value == NULL) return 0;
	return static_cast<DoubleObject*>(value)->GetValue();
}

void ScrollViewer::set_HorizontalOffset(double horizontalOffset)
{
	SetValue(get_HorizontalOffsetProperty(), DoubleObject::GetObject(horizontalOffset));
}

double ScrollViewer::get_VerticalOffset()
{
	Object* value = GetValue(get_VerticalOffsetProperty());
	if (value == NULL) return 0;
	return static_cast<DoubleObject*>(value)->GetValue();
}

void ScrollViewer::set_VerticalOffset(double verticalOffset)
{
	SetValue(get_VerticalOffsetProperty(), DoubleObject::GetObject(verticalOffset));
}

/*
void ScrollViewer::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (*type == L"scroll")
		{
			OnScroll(static_cast<SliderEvent*>(evt));
			evt->stopPropagation();
		}
	}
}
*/

#if 0
void ScrollViewer::OnScroll(SliderEvent* evt)
{
	//MessageBeep(-1);
#if 0

	IScrollContent* scrollContent = dynamic_cast<IScrollContent*>(m_Content);

	if (evt->get_target() == m_horz)
	{
		LDraw::PointD pos = LDraw::PointD(evt->m_pos, m_vert->get_pos());
		if (scrollContent)
		{
			pos = scrollContent->OnSetPos(pos);
		}

		m_viewBox->set_Transform(new TranslateTransform(-pos.X, -pos.Y));
	//	m_viewBox->m_bRenderValid = false;
		InvalidateRenderChildren(m_viewBox);
		m_viewBox->InvalidateRender();
		get_OwnerWindow()->m_pSite->InvalidateRegion(m_viewBox->m_visibleWithChildrenRegion);

		if (false)
		{
			m_Content->m_bRenderValid = false;
			InvalidateRenderChildren(m_Content);
			m_Content->InvalidateRender();
		}

//		InvalidateRender();
	//	get_OwnerWindow()->m_pSite->InvalidateRegion(m_viewBox->m_visibleRegion);
	}
	else if (evt->get_target() == m_vert)
	{
		LDraw::PointD pos = LDraw::PointD(m_horz->get_pos(), evt->m_pos);
		if (scrollContent)
		{
			pos = scrollContent->OnSetPos(pos);
		}

		m_viewBox->set_Transform(new TranslateTransform(-pos.X, -pos.Y));
	//	m_viewBox->m_bRenderValid = false;
		InvalidateRenderChildren(m_viewBox);
		m_viewBox->InvalidateRender();
		get_OwnerWindow()->m_pSite->InvalidateRegion(m_viewBox->m_visibleWithChildrenRegion);

		if (false)
		{
			m_Content->m_bRenderValid = false;
			InvalidateRenderChildren(m_Content);
			m_Content->InvalidateRender();
		}

	//	InvalidateRender();
	}
	else
		ASSERT(0);
#endif
}
#endif

#if 0
LDraw::SizeD ScrollViewer::get_InnerSize() const
{
	ASSERT(this);

	if (m_viewBox == NULL)
		THROW(std::exception("error"));

	return m_viewBox->get_ActualSize();
}
#endif

#if 0
LDraw::SizeD ScrollViewer::OnMeasure(LDraw::SizeD availSize)
{
	if (get_Content())
	{
		m_horz->Measure(LDraw::SizeD(availSize.Width-16, 16));
		m_vert->Measure(LDraw::SizeD(16, availSize.Height-16));
		m_viewBox->Measure(LDraw::SizeD(availSize.Width-16, availSize.Height-16));

		// Return minimum size
		return LDraw::SizeD(m_vert->get_DesiredSize().Width, m_horz->get_DesiredSize().Height);
	}
	else
		return LDraw::SizeD(0, 0);
}

void ScrollViewer::OnArrange(LDraw::SizeD finalSize)
{
	ASSERT(0);
	if (get_Content())
	{
		m_viewBox->Arrange(LDraw::RectD(0, 0, finalSize.Width-16, finalSize.Height-16));
		//m_viewBox->SetLayoutOffset(0, 0);

		m_horz->SetInfo(0, m_Content->m_computedSize.Width, (finalSize.Width-16));
		m_vert->SetInfo(0, m_Content->m_computedSize.Height, (finalSize.Height-16));

		m_horz->Arrange(LDraw::RectD(0, finalSize.Height-16, finalSize.Width-16, 16));
		//m_horz->SetLayoutOffset(0, finalSize.Height-16);

		m_vert->Arrange(LDraw::RectD(finalSize.Width-16, 0, 16, finalSize.Height-16));
		//m_vert->SetLayoutOffset(finalSize.Width-16, 0);
	}
}
#endif

/*
void ScrollViewer::OnChildDesiredSizeChanged(UIElement* child)
{
	ASSERT(this);
	InvalidateArrange();
//	m_horz->SetInfo(0, m_Content->m_computedSize.Width, (m_computedSize.Width-16));
//	m_vert->SetInfo(0, m_Content->m_computedSize.Height, (m_computedSize.Height-16));
}
*/

#if 0
UIElement* ScrollViewer::get_Content() const
{
	ASSERT(this);
	return m_Content;
}

void ScrollViewer::set_Content(UIElement* pContent)
{
	ASSERT(this);

	if (m_Content)
	{
	//	RemoveRChild(m_Content);
		RemoveRChild(m_vert);
		RemoveRChild(m_horz);
		RemoveRChild(m_viewBox);

	}
	m_Content = pContent;

	//Canvas* pCanvas = new Canvas;
	{
		m_horz = new HorizontalScrollBar;
		/*pCanvas->*/AddRChild(m_horz);

		m_vert = new VerticalScrollBar;
		/*pCanvas->*/AddRChild(m_vert);

		m_viewBox = new Viewbox;
		m_viewBox->m_pScroller = this;
		{
			m_viewBox->AddRChild(m_Content);
		//	m_viewBox->m_Content = m_Content;
		}
		/*pCanvas->*/AddRChild(m_viewBox);
	}
	//put_VisualTree(pCanvas);

	InvalidateArrange();
}
#endif

void ScrollViewer::MakeVisible(LDraw::RectD rect)
{
	//ASSERT(0);
#if 0

	double scrollposX = m_horz->get_pos();
	double scrollposY = m_vert->get_pos();

	if (true)
	{
		if (rect.GetTop() < m_vert->get_pos())	// scroll up
		{
			scrollposY = rect.GetTop();
		}
		else if (rect.GetBottom() > m_vert->get_pos()+m_vert->get_visible())	// scroll down
		{
			scrollposY = rect.GetBottom() - m_vert->get_visible();
		}
		else
			scrollposY = m_vert->get_pos();

		m_vert->set_pos(scrollposY);
	}

	if (true)
	{
		if (rect.GetLeft() < m_horz->get_pos())	// scroll left
		{
			scrollposX = rect.GetLeft();
		}
		else if (rect.GetRight() > m_horz->get_pos()+m_horz->get_visible())	// scroll right
		{
			scrollposX = rect.GetRight() - m_horz->get_visible();
		}
		else
			scrollposX = m_horz->get_pos();

		m_horz->set_pos(scrollposX);
	}

	m_viewBox->set_Transform(new TranslateTransform(-scrollposX, -scrollposY));
	m_viewBox->InvalidateRender();
#endif
}

}	// UI
}
