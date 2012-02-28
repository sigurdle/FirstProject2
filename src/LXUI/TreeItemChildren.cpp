#include "stdafx.h"
#include "LXUI2.h"
#include "TreeItemChildren.h"

namespace System
{
namespace UI
{

TreeItemChildren::TreeItemChildren(TreeControl* ownerCtl)
{
	m_userdata = NULL;
	m_ownerCtl = ownerCtl;
}

void TreeItemChildren::AppendItem(TreeItem* pItem)
{
	m_childList.Add(pItem);

	ASSERT(0);
	/*
	DockPanel::put_Dock(pItem, DockPanel::Top);
	m_Panel->*/
	//AddChild(pItem);
	InvalidateMeasure();
}

LDraw::SizeD TreeItemChildren::OnMeasure(LDraw::SizeD availSize)
{
	double y = 0;

	long size = m_childList.size();

	for (int i = 0; i < size; i++)
	{
		UIElement* p = m_childList[i];
		p->Measure(LDraw::SizeD(availSize.Width, 0));
		y += p->get_DesiredSize().Height;
	}

//	double width = m_ownerCtl->m_treeHeader->get_ActualSize().Width;
	return LDraw::SizeD(0, y);
	//return LDraw::SizeD(width, y);
}

void TreeItemChildren::OnArrange(LDraw::SizeD finalSize)
{
	double y = 0;

	long size = m_childList.size();

	for (int i = 0; i < size; i++)
	{
		UIElement* p = m_childList[i];
		p->Arrange(LDraw::RectD(0, y, m_computedSize.Width, p->get_DesiredSize().Height));
		//p->SetLayoutOffset(0, y);
		y += p->get_ActualSize().Height;
	}
}

}	// UI
}
