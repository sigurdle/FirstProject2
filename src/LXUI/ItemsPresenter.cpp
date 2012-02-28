#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

ItemsPresenter::ItemsPresenter()
{
}

LDraw::SizeD ItemsPresenter::MeasureOverride(LDraw::SizeD availSize)
{
	m_visualTree->Measure(availSize);
	return m_visualTree->get_DesiredSize();
}

LDraw::SizeD ItemsPresenter::ArrangeOverride(LDraw::SizeD finalSize)
{
	m_visualTree->Arrange(LDraw::RectD(0, 0, finalSize.Width, finalSize.Height));
	return finalSize;
}

unsigned int ItemsPresenter::get_VisualChildrenCount()
{
	return m_visualTree? 1: 0;
}

Visual* ItemsPresenter::GetVisualChild(unsigned int index)
{
	return m_visualTree;
}

void ItemsPresenter::set_VisualTree(UIElement* visualTree)
{
	if (m_visualTree)
	{
		RemoveVisualChild(visualTree);
		/*
		m_visualTree->SetRParent(NULL);
		m_visualTree->SetOwnerWindow(NULL);
		*/
	}

	m_visualTree = visualTree;

	if (m_visualTree)
	{
		AddVisualChild(m_visualTree);
	//	m_visualTree->SetRParent(this);
	//	m_visualTree->SetOwnerWindow(GetOwnerWindow());
	}
}

}	// UI
}
