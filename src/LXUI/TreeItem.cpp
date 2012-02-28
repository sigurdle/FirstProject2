#include "stdafx.h"
#include "LXUI2.h"
#include "TreeControl.h"
#include "TreeItem.h"

//#include "ScrollViewer.h"

namespace System
{
namespace UI
{

TreeItem::TreeItem(TreeControl* ownerTree)
{
	ASSERT(0);
#if 0
	m_itemData = NULL;
//	m_iIndex = -1;
	m_cChildren = -1;

	m_userdata = NULL;
	//m_expanded = false;

	m_Span = new Border;

//	m_Content = NULL;

//	DockPanel* pPanel = new DockPanel;

	m_ownerCtl = ownerTree;

	if (ownerTree)
		m_pos = ownerTree->m_treeItems.insert(ownerTree->m_treeItems.end(), this);

	m_Children = NULL;
#if 0
	m_Children = new TreeItemChildren(ownerTree);
	m_Children->put_Visibility(Collapsed);
#endif
	//m_Button = new Canvas;
	{
		m_ExpandButton = new Border(new Thickness(new Length(1)));
	//	m_ExpandButton->put_Width(Length(22));
	//	m_ExpandButton->put_Height(Length(22));

		/*
			m_ExpandButton->m_LeftBrush = new SolidColorBrush(Color(0,0,0));
			m_ExpandButton->m_TopBrush = new SolidColorBrush(Color(0,0,0));
			m_ExpandButton->m_RightBrush = new SolidColorBrush(Color(0,0,0));
			m_ExpandButton->m_BottomBrush = new SolidColorBrush(Color(0,0,0));
			*/

		//Border* pRect = new Border(Thickness(Length(1), Length(1), Length(1), Length(1)));
	//	m_ExpandButton->put_Visibility(Hidden);
		{
			Border* pRect = new Border(new Thickness(new Length(1)));
			pRect->set_Width(new Length(14));
			pRect->set_Height(new Length(14));
			pRect->set_BorderBrush(new SolidColorBrush(new Color(90,90,90)));

			/*
			pRect->put_Fill(new SolidColorBrush(new Color(0, 0, 0)));
			pRect->put_RectangleWidth(new Length(14, Length::UnitAbsolute));
			pRect->put_RectangleHeight(new Length(14, Length::UnitAbsolute));
			*/
			{
				pRect->set_Content(new TextString(WSTR("-")));
			}
			m_ExpandButton->set_Content(pRect);
		}

		m_ExpandButton->set_Visibility(Hidden);

		//DockPanel::put_Dock(m_ExpandButton, DockPanel::Left);
		/*m_Button->*/AddRChild(m_ExpandButton);
	}

	AddRChild(m_Span);
	/*
	{
		m_ContentBorder = new CLXUICanvas;
	//	m_ContentBorder->put_Content(m_Content);
		DockPanel::put_Dock(m_ContentBorder, DockPanel::Fill);
		m_Button->AddRChild(m_ContentBorder);
	}
	*/
	//AddRChild(m_Button);
#if 0
	AddRChild(m_Children);
#endif
/*
	pPanel->AddRChild(m_Button);
	pPanel->AddRChild(m_Children);

	put_VisualTree(pPanel);
*/

//	m_pFont = m_ownerCtl->m_pFont;

//	m_ownerCtl->m_items.push_back(this);
#endif
}

bool TreeItem::HasExpandButton() const
{
	return m_cChildren == 1;
}

void TreeItem::SetExpandButton(int cChildren)
{
	m_cChildren = cChildren;
	m_ExpandButton->set_Visibility(m_cChildren? Visible: Hidden);
}

bool TreeItem::CanExpand()
{
	if (m_cChildren == -1)
		return m_Children != NULL;//!m_Children->m_childList.empty();
	else
		return m_cChildren != 0;
}

#if 0
void TreeItem::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (type == MouseEvent::mousedown)
		{
			OnLButtonDown(static_cast<MouseEvent*>(evt));
			evt->stopPropagation();
		}
		else if (*type == L"ActivateItem")
		{
			m_Span->set_Background(new SolidColorBrush(new Color(120, 140, 200)));
			InvalidateRender();	// TODO, shouldn't be necessary
		}
		else if (*type == L"DeactivateItem")
		{
			m_Span->set_Background(NULL);
			InvalidateRender();	// TODO, shouldn't be necessary
		}
	}
}
#endif

void TreeItem::OnLButtonDown(MouseButtonEventArgs* evt)
{
//	m_ContentBorder->put_BackgroundBrush(new SolidColorBrush(new Color(80, 160, 220)));

	ASSERT(0);
#if 0

	if (dynamic_cast<UIElement*>(evt->get_target())->IsDescendantOf(m_ExpandButton))
	{
		if (CanExpand())
		{
			Event* evt2 = new Event;
			evt2->InitEvent(WSTR("ItemExpanding"), true, true);
			bool doDefault = dispatchEvent(evt2);
			if (doDefault)
			{
				bool m_expanded = m_Children->get_Visibility() != Collapsed;
				m_expanded = !m_expanded;

				if (m_expanded)
					dynamic_cast<Border*>(m_ExpandButton->get_Child())->set_Child(new TextString(WSTR("-")));
				else
					dynamic_cast<Border*>(m_ExpandButton->get_Child())->set_Child(new TextString(WSTR("+")));

				m_Children->set_Visibility(m_expanded? Visible: Collapsed);
				m_Children->InvalidateMeasure();

				InvalidateMeasure();
			}
		}
		/*
		else
		{
			InvalidateRender();
		}
		*/
	}
	else
	{
		MouseEvent* evt2 = new MouseEvent;
		evt2->InitMouseEvent(WSTR("click"), evt->GetOwnerWindow(), evt->get_ScreenX(), evt->get_ScreenY(), evt->m_bShift, evt->m_bCtrl);
		bool doDefault = dispatchEvent(evt2);
	}
#endif
}

void TreeItem::OnRender(Graphics* pGraphics)
{
	Control::OnRender(pGraphics);

}

/*
void TreeItem::BuildVisualTree()
{
	for (int i = 0; i < m_childList.size(); i++)
	{
		UIElement* pChild = m_childList[i];
	}
}
*/

void TreeItem::AppendColumnCell(UIElement* Content)
{
	m_cells.Add(Content);
	ASSERT(0);
//	/*m_Button->*/AddChild(Content);

//	AddRChild(m_Button);
}

/*
void TreeItem::AppendItem(TreeItem* pItem)
{
	m_Children->AppendItem(pItem);
}
*/

LDraw::SizeD TreeItem::OnMeasure(LDraw::SizeD availSize)
{
	double height = 0;
	double width = 0;

	if (true)//m_Button->get_Visibility() != Collapsed)
	{
	//	m_Button->Measure(LDraw::SizeD(availSize.Width, 0));
	//	height = MAX(height, m_Button->m_desiredSize.Height);

		m_ExpandButton->Measure(LDraw::SizeD(0, 0));
		height = m_ExpandButton->get_DesiredSize().Height;
/*
		double totalWidth = m_ownerCtl->get_ActualSize().Width;
		{
			ColumnHeader* pColumn = m_ownerCtl->get_ColumnHeaderList()->m_columns[0];
		//	if (pColumn->get_Visibility() != Collapsed)
			totalWidth -= pColumn->get_ActualSize().Width;
		}
*/
		if (m_Span)
		{
			m_Span->Measure(LDraw::SizeD(0, 0));	// TODO??
		}
		for (int i = 0; i < m_cells.GetSize(); i++)
		{
			ColumnHeader* pColumn = m_ownerCtl->get_ColumnHeaderList()->m_columns[i];
			UIElement* pCell = m_cells[i];

			double columnWidth;
			if (pColumn->get_Visibility() != Collapsed)
			{
				/*
				if (i == 0)
					columnWidth = availSize.Width - totalWidth - 16;
				else
				*/
					columnWidth = pColumn->get_ActualSize().Width;
			}
			else
			{
				columnWidth = 0;
			}

			pCell->Measure(LDraw::SizeD(0/*columnWidth-16*/, 0));
			if (pColumn->get_Visibility() != Collapsed)
			{
				height = MAX(height, pCell->get_DesiredSize().Height);
			}
		}

		width = MAX(width, m_ExpandButton->get_DesiredSize().Width);
	}

	if (m_Children)
	{
		if (m_Children->get_Visibility() != Collapsed)
		{
			m_Children->Measure(LDraw::SizeD(availSize.Width-16, availSize.Height - height));
			height += m_Children->get_DesiredSize().Height;
			width = MAX(width, m_Children->get_DesiredSize().Width+16);
		}
	}

	return LDraw::SizeD(width, height);
}

void TreeItem::OnArrange(LDraw::SizeD finalSize)
{
	m_ExpandButton->Arrange(LDraw::RectD(LDraw::PointD(0, 0), m_ExpandButton->get_DesiredSize()/*LDraw::SizeD(1, 14)*/));
	//m_ExpandButton->SetLayoutOffset(0, 0);
	//	pCell->m_computedLeft = x;
	double height = m_ExpandButton->m_computedSize.Height;
	double x = m_ExpandButton->m_computedSize.Width;

	if (m_Span)
	{
		m_Span->Arrange(LDraw::RectD(x, 0, finalSize.Width-x, height/*m_Span->get_DesiredSize().Height*/));
		//m_Span->SetLayoutOffset(x, 0);
		m_Span->m_computedLeft = x;
		height = MAX(height, m_Span->get_ActualSize().Height);
	}

	if (m_cells.GetSize())
	{
		double totalWidth = m_ownerCtl->get_ActualSize().Width;
		{
			ColumnHeader* pColumn = m_ownerCtl->get_ColumnHeaderList()->m_columns[0];
		//	if (pColumn->get_Visibility() != Collapsed)
			totalWidth -= pColumn->get_ActualSize().Width;
		}

		for (int i = 0; i < m_cells.GetSize(); i++)
		{
			ColumnHeader* pColumn = m_ownerCtl->get_ColumnHeaderList()->m_columns[i];
			UIElement* pCell = m_cells[i];

			double columnWidth;

			if (pColumn->get_Visibility() != Collapsed)
			{
				if (i == 0)
					columnWidth = finalSize.Width - totalWidth - 16;
				else
					columnWidth = pColumn->get_ActualSize().Width;
			}
			else
				columnWidth = 0;

			pCell->Arrange(LDraw::RectD(x, 0, columnWidth/*pCell->m_availSize.Width*/, pCell->get_DesiredSize().Height));
			//pCell->SetLayoutOffset(x, 0);
			pCell->m_computedLeft = x;
			if (pColumn->get_Visibility() != Collapsed)
			{
				height = MAX(height, pCell->get_ActualSize().Height);
			}

			x += columnWidth;
		}
	}

#if 0
	m_Button->m_expandedBBox.Width = finalSize.Width;
	m_Button->m_expandedBBox.Height = finalSize.Height;
#endif

//	m_VisualTree->Arrange(finalSize);
	//Control::OnArrange(finalSize);

	if (m_Children)
	{
		//double x, y;

		if (m_Children->get_Visibility() != Collapsed)
		{
			//m_Children->SetLayoutOffset(16, height);
		//	x = 16;
		//	y = height;
			//m_Children->m_transformMatrix *= gmMatrix3::translate(16, 0);

			m_Children->Arrange(LDraw::RectD(16, height, finalSize.Width-16, m_Children->get_DesiredSize().Height));
		}
	}
}

void TreeItem::DeselectAll()
{
	ASSERT(0);
#if 0
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		TreeItem* pItem = (TreeItem*)(C2Obj*)m_childList.GetNext(pos);
		if (pItem->m_selected)
		{
			pItem->m_selected = FALSE;
			m_ownerCtl->Fire_ItemStateChange(pItem, 1, pItem->m_selected);
		}
	}
#endif
}

UIElement/*TreeItemChildren*/ * TreeItem::get_Children() const
{
	return m_Children;
}

void TreeItem::set_Children(UIElement/*TreeItemChildren*/ * Children)
{
	if (m_Children)
	{
		RemoveRChild(m_Children);
		delete m_Children;
	}
	m_Children = Children;
	if (m_Children)
	{
		ASSERT(0);
		//AddChild(m_Children);

		m_ExpandButton->set_Visibility(/*Children->get_Visibility() != Collapsed?*/ Visible/*: Hidden*/);

		bool m_expanded = m_Children->get_Visibility() != Collapsed;
	//	m_expanded = !m_expanded;

		if (m_expanded)
			dynamic_cast<Border*>(m_ExpandButton->get_Child())->set_Child(new TextString(WSTR("-")));
		else
			dynamic_cast<Border*>(m_ExpandButton->get_Child())->set_Child(new TextString(WSTR("+")));
	}
	else
	{
		m_ExpandButton->set_Visibility(Hidden);
	}
}

}	// UI
}
