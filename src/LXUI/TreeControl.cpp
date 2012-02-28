#include "stdafx.h"
#include "LXUI2.h"
#include "TreeControl.h"

#include "DockPanel.h"
#include "SolidColorBrush.h"
#include "ScrollViewer.h"

namespace System
{
namespace UI
{

#if 0
void TreeControl::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (*type == L"splitter")
		{
			evt->stopPropagation();

			list<TreeItem*, __gc_allocator>::iterator it = m_treeItems.begin();
			while (it != m_treeItems.end())
			{
				(*it)->InvalidateArrange();
				++it;
			}

				/*
		//	m_Children->InvalidateArrange();
			for (int i = 0; i < m_Children->get_rchildList().get_Size(); i++)
			{
				dynamic_cast<UIElement*>(m_Children->get_rchildList()[i])->InvalidateArrange();
			}
			*/
			/*
			Measure(m_availSize);
			Arrange(m_availSize);
			Invalidate();
			*/
		//	InvalidateMeasure();
		//	InvalidateArrange();
		//	m_Children->put_Width(m_treeHeader->get_ActualSize().Width);
		//	m_Children->InvalidateMeasure();
		}
		else if (*type == L"click")
		{
			evt->stopPropagation();

			MouseEvent* mouseEvt = static_cast<MouseEvent*>(evt);

			//UIElement* visual = dynamic_cast<UIElement*>();
			TreeItem* treeitem = dynamic_cast<TreeItem*>(evt->get_target());
			/*
			while (visual)
			{
				treeitem = dynamic_cast<TreeItem*>(visual);
				if (treeitem) break;

				visual = dynamic_cast<UIElement*>(visual->GetRParent());
			}
			*/

			if (treeitem)
			{
				if (m_pSingleSelection != treeitem)
				{

					MouseEvent* evt2 = new MouseEvent;
					evt2->InitMouseEvent(WSTR("ItemStateChanging"), mouseEvt->GetOwnerWindow(), mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY(), mouseEvt->m_bShift, mouseEvt->m_bCtrl);
					bool doDefault = dispatchEvent(evt2);
					if (doDefault)
					{
						if (m_pSingleSelection)
						{
							Event* evt = new Event;
							evt->InitEvent(WSTR("DeactivateItem"), true, false);
							m_pSingleSelection->dispatchEvent(evt);
						//	delete evt;
						}

						m_pSingleSelection = treeitem;

						if (m_pSingleSelection)
						{
							Event* evt = new Event;
							evt->InitEvent(WSTR("ActivateItem"), true, false);
							m_pSingleSelection->dispatchEvent(evt);
						//	delete evt;
						}
					}
				}
			}
		}
	}
}
#endif

//UIElement* RecalculateParent(UIElement* pThis);

////////////////////////////////////////////////////////////////////////////
// GroupHeader

/*
UIElement* GroupHeader::get_Content()
{
	return m_Content;
}
*/

void GroupHeader::EnsureVisual()
{
	//m_Content = Content;

	Border* pBorder = new Border(new Thickness(1));
	/*
	pBorder->m_LeftBrush = new SolidColorBrush(Color(255, 255, 255));
	pBorder->m_TopBrush = new SolidColorBrush(Color(255, 255, 255));
	pBorder->m_RightBrush = new SolidColorBrush(Color(90, 90, 90));
	pBorder->m_BottomBrush = new SolidColorBrush(Color(90, 90, 90));
	*/

	Border* pBorder2 = new Border(new Thickness(2));
	pBorder2->set_Background(new SolidColorBrush(Color::FromRgb(236, 233, 216)));
	pBorder2->set_Child(new TextString(dynamic_cast<TextString*>(m_def->m_visual)->get_TextContent()));
	pBorder->set_Child(pBorder2);

	set_VisualTree(pBorder);
}

#if 0
void GroupHeader::handleEvent(Event* evt)
{
}
#endif

////////////////////////////////////////////////////////////////////////////
// ColumnHeader

/*
UIElement* ColumnHeader::get_Content()
{
	return m_Content;
}
*/

void ColumnHeader::EnsureVisual()
{
	//m_Content = Content;

	Border* pBorder = new Border(new Thickness(1.0));
/*	pBorder->m_LeftBrush = new SolidColorBrush(Color(255, 255, 255));
	pBorder->m_TopBrush = new SolidColorBrush(Color(255, 255, 255));
	pBorder->m_RightBrush = new SolidColorBrush(Color(90, 90, 90));
	pBorder->m_BottomBrush = new SolidColorBrush(Color(90, 90, 90));
*/
	Border* pBorder2 = new Border(new Thickness(2.0));
	pBorder2->set_Background(new SolidColorBrush(Color::FromRgb(236, 233, 216)));
	pBorder2->set_Child(new TextString(dynamic_cast<TextString*>(m_def->m_visual)->get_TextContent()));//m_def->m_visual);
	pBorder->set_Child(pBorder2);

	set_VisualTree(pBorder);
}

#if 0
class DragOverEvent : public Event
{
public:
	LDraw::RectI m_rect;
};

class DragDropEvent : public Event
{
public:
	Object* m_element;
};

void ColumnHeader::handleEvent(Event* evt)
{
	if (evt->get_eventPhase() != CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"mousedown")
		{
			evt->stopPropagation();
			if (false)
			{
				MouseEvent* mouseEvt = static_cast<MouseEvent*>(evt);

				IScreen* pScreen = dynamic_cast<WindowHost*>(mouseEvt->GetOwnerWindow()->m_pSite)->GetScreen();
				//LDraw::PointD ScreenToClient(
				LDraw::RectD rect = GetWindowToElementBounds();
				LDraw::PointI offset(mouseEvt->get_ScreenX() - rect.X, mouseEvt->get_ScreenY() - rect.Y);

				WindowBase* pBase = new WindowBase;
			//	pBase->SetRParent(m_pAttachedToMenuElement);
	#if 0
				m_pAttachedToMenuElement->AddRChild(pBase);
	#endif
				ColumnHeader* pClone = new ColumnHeader;
				pClone->m_def = m_def;
				pClone->EnsureVisual();
				pClone->Measure(LDraw::SizeD(0, 0));
				pClone->Arrange(LDraw::RectD(LDraw::PointD(0, 0), get_ActualSize()));

				ASSERT(0);
#if 0
				pBase->set_VisualTree(pClone);
				pBase->set_Opacity(0.75);
#endif

				WindowHost* pSite = pScreen->OpenWindow();
				pSite->SetClient(pBase);
				pSite->Show();

				LDraw::SizeD size = get_ActualSize();

				pSite->SetWindowRect(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY(), size.Width, size.Height);

				Visual* pElementOver = NULL;

	#if WIN32
				MSWindows::MSG msg;
				while (MSWindows::GetMessageA(&msg, NULL, 0, 0))
				{
					if (msg.message == WM_MOUSEMOVE)
					{
						MSWindows::POINT point;
						MSWindows::GetCursorPos(&point);
						int x = point.x - offset.X;
						int y = point.y - offset.Y;

						Visual* pElement = NULL;

						WindowBase* pBase = static_cast<WindowBase*>(mouseEvt->GetOwnerWindow());

						/*
						if (m_pElementCapture)
							pElement = pBase->m_pElementCapture;
						else
						*/
						LDraw::PointD clientpt;
						clientpt.X = point.x;
						clientpt.Y = point.y;
						//::ScreenToClient(

						pElement = pBase->get_VisualTree()->HitTestElement(pBase->get_VisualTree()->GetParentToElementTransformMatrix(), LDraw::PointD(clientpt.X, clientpt.Y));

						if (pElement)
						{
							DragOverEvent* dragOverEvt = new DragOverEvent;
							dragOverEvt->InitEvent(WSTR("dragover"), true, true);
							dragOverEvt->m_rect = LDraw::RectI(x, y, size.Width, size.Height); 

							pElement->dispatchEvent(dragOverEvt);

							x = dragOverEvt->m_rect.X;
							y = dragOverEvt->m_rect.Y;

							pElementOver = pElement;
						}

						pSite->SetWindowRect(x, y, size.Width, size.Height);
					}
					else if (msg.message == WM_LBUTTONUP)
					{
						break;
					}
					MSWindows::TranslateMessage(&msg);
					MSWindows::DispatchMessageA(&msg);
				}
	#else
				VERIFY(0);
	#endif

				pSite->Close();

				if (pElementOver)
				{
					DragDropEvent* dragDropEvt = new DragDropEvent;
					dragDropEvt->InitEvent(WSTR("dragdrop"), true, true);
					dragDropEvt->m_element = m_def;
					//dragOverEvt->m_rect = LDraw::RectI(x, y, size.Width, size.Height); 

					pElementOver->dispatchEvent(dragDropEvt);
				}
			}
		}
	}
}
#endif

////////////////////////////////////////////////////////////////////////////
// HeaderControl

/*
class UIEXT HeaderControl : public Control
{
public:

	virtual void OnRender2(Graphics* pGraphics);

	virtual void handleEvent(UI::Event* evt);
};

void HeaderControl::OnRender2(Graphics* pGraphics)
{
}
*/

/////////////////////////////////////////////////////////////////////////////
//

Cursor* Splitter::DefaultCursor = NULL;

Splitter::Splitter()
{
	m_dragging = 0;
	m_pPrevSibling = NULL;

	{
		Border* pBorder2 = new Border(new Thickness(2.0, 3.0, 2.0, 3.0));
		{
			Border* pBorder = new Border(new Thickness(1.0));
			/*
			pBorder->put_LeftBrush(new SolidColorBrush(Color(130, 130, 130)));
			pBorder->put_TopBrush(new SolidColorBrush(Color(255, 255, 255)));
			pBorder->put_RightBrush(new SolidColorBrush(Color(255, 255, 255)));
			pBorder->put_BottomBrush(new SolidColorBrush(Color(255, 255, 255)));
			*/

			pBorder2->set_Child(pBorder);
		}
		set_VisualTree(pBorder2);
	}

#if WIN32
	if (DefaultCursor == NULL)
	{
		/*
		DefaultCursor = new Cursor;
#if 0
		DefaultCursor->AddRef();
#endif

		DefaultCursor->set_HotspotX(8);
		DefaultCursor->set_HotspotY(8);
		Image* pImage = new Image(new FileImageSource(WSTR("C:/splitter.png")));
		DefaultCursor->set_Visual(pImage);
		*/
	}

	set_Cursor(DefaultCursor);
#endif
}

#if 0
void Splitter::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (type == MouseEvent::mousedown)
		{
			evt->stopPropagation();
			MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);

			if (GetRParent())
			{
				LDraw::PointD point = dynamic_cast<UIElement*>(GetRParent())->ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

				m_startpt = point;

				m_pPrevSibling = NULL;
				
				ASSERT(0);
#if 0
				for (int i = 0; i < GetRParent()->get_rchildList()->get_Size(); i++)
				{
					if ((*GetRParent()->get_rchildList())[i] == this)
						break;
					m_pPrevSibling = (*GetRParent()->get_rchildList())[i];
				}

				if (m_pPrevSibling)
				{
					m_originalWidth = m_pPrevSibling->get_ActualSize().Width;

					m_dragging = true;
					SetCapture();
				}
#endif
			}
		}
		else if (type == MouseEvent::mouseup)
		{
			evt->stopPropagation();
			if (m_dragging)
			{
				m_dragging = false;
				ReleaseMouseCapture();
			}
		}
		else if (type == MouseEvent::mousemove)
		{
			evt->stopPropagation();

			MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);

			if (m_dragging)
			{
				LDraw::PointD point = dynamic_cast<UIElement*>(GetRParent())->ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

				if (m_pPrevSibling)
				{
				//	MessageBeep(-1);
					double newWidth = m_originalWidth + point.X - m_startpt.X;
					if (newWidth < 0) newWidth = 0;
					ASSERT(0);
#if 0
					m_pPrevSibling->set_Width(new Length(newWidth));
#endif
				//	pPrevSibling->Measure(LDraw::SizeD(0, 0));
				//	pPrevSibling->Arrange(LDraw::SizeD(pPrevSibling->m_desiredSize.Width, pPrevSibling->m_desiredSize.Height));
#if 0	// Should be done in put_Width
					m_pPrevSibling->InvalidateMeasure();
#endif

					/*
					pPrevSibling->GetRParent()->Measure(LDraw::SizeD(0, 0));
					pPrevSibling->GetRParent()->Arrange(LDraw::SizeD(pPrevSibling->GetRParent()->m_desiredWidth, pPrevSibling->GetRParent()->m_desiredHeight));

					pPrevSibling->GetRParent()->Invalidate();
					*/
				}

				//m_oldpt.X = screenX;

				Event* splitterEvt = new Event;
				splitterEvt->InitEvent(WSTR("splitter"), true, true);
				dispatchEvent(splitterEvt);
			}
		}
	}
}
#endif

#if 0
void TreeHeader::OnChildDesiredSizeChanged(UIElement* child)
{
	TreeControl* treeControl = NULL;
	Control::OnChildDesiredSizeChanged(child);
	UIElement* p = GetRParent();
	while (p)
	{
		treeControl = dynamic_cast<TreeControl*>(p);
		if (treeControl)
			break;

		p = p->GetRParent();
	}

	/*
	if (treeControl)
	{
		for (int i = 0; i < treeControl->get_Children()->m_childList.size(); i++)
		{
			treeControl->get_Children()->m_childList[i]->InvalidateMeasure();
		}
	}
	*/
}
#endif

void ColumnHeaderList::AddColumn(ColumnDefinition* pColumnDef)
{
	ColumnHeader* pColumn = new ColumnHeader;
	pColumn->m_def = pColumnDef;
	pColumn->EnsureVisual();
	//pColumn->put_Content(pColumnContent);

	m_columns.Add(pColumn);

	EnsureVisuals();
}

void ColumnHeaderList::EnsureVisuals()
{
	DockPanel* pPanel = new DockPanel;
	for (int i = 0; i < m_columns.GetSize(); i++)
	{
		if (m_columns[i]->GetRParent())
		{
			m_columns[i]->GetRParent()->RemoveRChild(m_columns[i]);
		}

		DockPanel::SetDock(m_columns[i], DockPanel::Left);
		pPanel->get_Children()->Add(m_columns[i]);

		Splitter* p = new Splitter;
		DockPanel::SetDock(p, DockPanel::Left);
		pPanel->get_Children()->Add(p);
	}

	set_VisualTree(pPanel);
}

#if 0
void ColumnHeaderList::handleEvent(Event* evt)
{
	if (evt->get_eventPhase() != CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"dragover")
		{
			evt->stopPropagation();

			DragOverEvent* dragOverEvt = static_cast<DragOverEvent*>(evt);

			LDraw::RectD rect = GetWindowToElementBounds();

			dragOverEvt->m_rect.Y = rect.Y;
		}
	}
}
#endif

/////////////////////////////
// GroupHeaderList

GroupHeaderList::GroupHeaderList()
{
	EnsureVisuals();
}

LDraw::SizeD GroupHeaderList::Content::OnMeasure(LDraw::SizeD availSize)
{
	/*
	if (m_columns.size() == 0)
	{
		return Control::OnMeasure(availSize);
	}
	*/

	LDraw::SizeD desiredSize;
	double y = 0;

	ASSERT(0);
#if 0

	int count = get_Children()->get_Size();

	for (int i = 0; i < count; i++)
	{
		UIElement* pChild = (*get_rchildList())[i];

		pChild->Measure(LDraw::SizeD(0, 0));

		desiredSize.Width += pChild->get_DesiredSize().Width;
		desiredSize.Height = MAX(desiredSize.Height, pChild->get_DesiredSize().Height+y);;
		y += 9;
	}
#endif

	return desiredSize;
}

void GroupHeaderList::Content::OnArrange(LDraw::SizeD finalSize)
{
	/*
	if (m_columns.size() == 0)
	{
		Control::OnArrange(finalSize);
		return;
	}
	*/

	ASSERT(0);
#if 0

	double x = 0;
	double y = 0;

	int count = get_rchildList()->get_Size();

//	DockPanel* pPanel = new DockPanel;
	for (int i = 0; i < count; i++)
	{
		UIElement* pChild = (*get_rchildList())[i];

		/*
		if (pChild->GetRParent())
		{
			pChild->GetRParent()->RemoveRChild(m_columns[i]);
		}
		*/

		//DockPanel::put_Dock(m_columns[i], DockPanel::Left);
		pChild->Arrange(LDraw::RectD(LDraw::PointD(x, y), pChild->get_DesiredSize()));
	//	pChild->SetLayoutOffset(x, y);

		///*pPanel->*/AddRChild(m_columns[i]);

		x += pChild->get_ActualSize().Width + 4;
		y += 9;
	}
#endif
}

void GroupHeaderList::Content::OnRender(Graphics* pGraphics)
{
	ASSERT(0);
#if 0
	int count = get_rchildList()->get_Size();


	if (count > 0)
	{
		pGraphics->TranslateTransform(0.5, 0.5);

		double x = 0;
		double y = 0;

		UIElement* pChild = (*get_rchildList())[0];

		for (int i = 0; i < count-1; i++)
		{
			UIElement* pNextChild = (*get_rchildList())[i+1];

			double x1 = x + pChild->get_ActualSize().Width - 8;
			double y1 = y + pChild->get_ActualSize().Height;
			double x2 = x + pChild->get_ActualSize().Width + 4;
			double y2 = y + 9 +  pNextChild->get_ActualSize().Height-4;
			LDraw::PointF points[] =
			{
				LDraw::PointF(x1, y1),
				LDraw::PointF(x1, y2),
				LDraw::PointF(x2, y2)
			};
		
			pGraphics->DrawPolygon(new LDraw::Pen(LDraw::Color(0,0,0), 1), points, 3);

			x = x2;
			y += 9;

			pChild = pNextChild;
		}

		pGraphics->TranslateTransform(-0.5, -0.5);
	}
#endif
	Control::OnRender(pGraphics);
}

void GroupHeaderList::EnsureVisuals()
{
	if (m_columns.GetSize())
	{
		Border* pBorder = new Border(new Thickness(4));
		pBorder->set_Background(new SolidColorBrush(Color::FromRgb(160, 160, 160)));

		Content* pPanel = new Content;
		for (int i = 0; i < m_columns.GetSize(); i++)
		{
			if (m_columns[i]->GetRParent())
			{
				m_columns[i]->GetRParent()->RemoveRChild(m_columns[i]);
			}

			ASSERT(0);
			//pPanel->AddChild(m_columns[i]);
		}

		pBorder->set_Child(pPanel);

		set_VisualTree(pBorder);
	}
	else
	{
		Border* pBorder = new Border(new Thickness(4));
		pBorder->set_Background(new SolidColorBrush(Color::FromRgb(160, 160, 160)));
		{
			Border* pBorder2 = new Border(new Thickness(2));
			pBorder2->set_Background(new SolidColorBrush(Color::FromRgb(236, 233, 216)));
			{
				TextString* pText = new TextString(WSTR("Drag a column header here to group by that column."));
				pText->set_TextFill(new SolidColorBrush(Color::FromRgb(160, 160, 160)));
				pBorder2->set_Child(pText);
			}
			pBorder->set_Child(pBorder2);
		}
		set_VisualTree(pBorder);
	}
}

#if 0
void GroupHeaderList::handleEvent(Event* evt)
{
	if (evt->get_eventPhase() != CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"dragdrop")
		{
			evt->stopPropagation();

			DragDropEvent* dragDropEvt = static_cast<DragDropEvent*>(evt);

			/*
			Event* groupByEvt = new Event;
			groupByEvt->initEvent(L"groupby", true, true);

			bool doDefault = dispatchEvent(groupByEvt);
			if (doDefault)
			*/
			{
				ColumnDefinition* columnDef = dynamic_cast<ColumnDefinition*>(dragDropEvt->m_element);
				ASSERT(columnDef);

				GroupHeader* pGroupHeader = new GroupHeader;
				pGroupHeader->m_def = columnDef;
				//pGroupHeader->put_Content(columnHeader->get_Content());

				pGroupHeader->EnsureVisual();

				m_columns.Add(pGroupHeader);

				EnsureVisuals();
				InvalidateMeasure();

				Event* groupByEvt = new Event;
				groupByEvt->InitEvent(WSTR("groupby"), true, true);

				bool doDefault = dispatchEvent(groupByEvt);
			}
		}
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////
// TreeControl

TreeControl::TreeControl()
{
	m_pSingleSelection = NULL;

	m_Children = new TreeItemChildren(this);

//	AddRChild(m_pTree);

	m_Indentation = MinIndent;

//	m_pActive = NULL;

	/*
	COLORREF m_clrBack = RGB(255, 255, 255);

	m_clrLines = RGB(
		(255-GetRValue(m_clrBack))/2,
		(255-GetGValue(m_clrBack))/2,
		(255-GetBValue(m_clrBack))/2);
*/

#if 0
	m_hUxThemeLib = NULL;
	m_hHeaderTheme = NULL;
	m_hTreeViewTheme = NULL;
#endif

#if 0
//	put_VisualTree(m_pTree);
	DockPanel* p = new DockPanel;
	{
		ScrollViewer* pScroller = new ScrollViewer;
		{
			m_pTree->get_Children()->GetRParent()->RemoveRChild(m_pTree->get_Children());
			pScroller->put_Content(m_pTree->get_Children());

			p->put_Dock(pScroller, DockPanel::Fill);
		}
		p->AddRChild(pScroller);
	}
	put_VisualTree(p);
#endif

	Border* p = new Border;
	p->set_Background(new SolidColorBrush(Color::FromRgb(255, 255, 255)));
	{
		DockPanel* pPanel = new DockPanel;

		{
		//	Border* p2 = new Border(Thickness(Length(0, Length::UnitAbsolute)));
		//	p2->put_BackgroundBrush(new SolidColorBrush(Color(236, 233, 216)));
		//	{
				m_groupHeaderList = new GroupHeaderList;
			//	p2->put_Content(m_groupHeader);
		//	}
#if 1
			DockPanel::SetDock(m_groupHeaderList, DockPanel::Top);
			pPanel->get_Children()->Add(m_groupHeaderList);
#endif
		}

		{
			Border* p2 = new Border(new Thickness(0.0, 1.0, 0.0, 1.0));
		//	p2->put_TopBrush(new SolidColorBrush(Color(255, 255, 255)));
		//	p2->put_BottomBrush(new SolidColorBrush(Color(130, 130, 130)));
			
			p2->set_Background(new SolidColorBrush(Color::FromRgb(236, 233, 216)));
			{
				m_columnHeaderList = new ColumnHeaderList;
				p2->set_Child(m_columnHeaderList);
			}
			DockPanel::SetDock(p2, DockPanel::Top);
			pPanel->get_Children()->Add(p2);
		}

		{
		//	m_pTree->get_Children()->GetRParent()->RemoveRChild(m_pTree->get_Children());
			DockPanel::SetDock(get_Children(), DockPanel::Top);
			pPanel->get_Children()->Add(get_Children());
		}
//		put_VisualTree(pPanel);
		p->set_Child(pPanel);
	}
	set_VisualTree(p);
}

TreeControl::~TreeControl()
{
}

void TreeControl::AddColumn(UIElement* visual)
{
	ColumnDefinition* pDef = new ColumnDefinition;
	pDef->m_index = m_columns.GetSize();
	pDef->m_visual = visual;
	m_columns.Add(pDef);

	get_ColumnHeaderList()->AddColumn(pDef);
}

#if 0
void TreeControl::OnRender2(Graphics* pGraphics)
{
	if (m_hWnd == NULL) return 0;

	HDC hDC = di.hdcDraw;
	CDCHandle dc(hDC);

	CRect& client = *(CRect*)di.prcBounds;

	CRect	clip;
	GetClipBox(hDC, &clip);

//	FillSolidRect(hDC, 0, 0, client.right, m_headerHeight, RGB(255, 0, 0));

	CComQIPtr<IFont> font = m_pFont;
	HFONT hFont;
	font->get_hFont(&hFont);

	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	//FillSolidRect(hDC, &client, RGB(255, 0, 0));

	Draw3DRect(hDC, &client, RGB(0,0,0), RGB(0,0,0));	// Black frame

	OffsetViewportOrgEx(hDC, 1, 0, NULL);

	SetBkMode(hDC, TRANSPARENT);

	if (TRUE)	// Header
	{
		{
			CRect	headerRect;
			headerRect.top = 1;
			headerRect.bottom = headerRect.top+m_headerHeight-2;
			headerRect.left = 0;

			for (int n = 0; n < m_column.GetSize(); n++)
			{
				if (m_column[n].m_bVisible)
				{
					headerRect.right = headerRect.left + m_column[n].m_width;

					CRect rc = headerRect;

					if (m_hHeaderTheme)
					{
						uxDrawThemeBackground(m_hHeaderTheme,
							 dc.m_hDC,
							 HP_HEADERITEM,
							 HIS_NORMAL,
							 &rc,
							 NULL);
					}
					else
					{
						dc.FillSolidRect(rc.right-1, rc.top, 1, rc.Height(), RGB(0,0,0));
						rc.right--;

						dc.FillSolidRect(rc.left, rc.top, 1, rc.Height(), GetSysColor(COLOR_3DHILIGHT));
						dc.FillSolidRect(rc.left+1, rc.top, rc.Width()-1, 1, GetSysColor(COLOR_3DHILIGHT));

						dc.FillSolidRect(rc.left+1, rc.bottom-1, rc.Width()-1, 1, GetSysColor(COLOR_3DSHADOW));
						dc.FillSolidRect(rc.right-1, rc.top+1, 1, rc.Height()-1, GetSysColor(COLOR_3DSHADOW));

				//	dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
						rc.InflateRect(-1,-1);

		/*
					Draw3DRect(hDC, &rc, GetSysColor(COLOR_3DLIGHT), GetSysColor(COLOR_3DSHADOW));
					rc.InflateRect(-1,-1);
		*/

						dc.FillSolidRect(&rc, GetSysColor(COLOR_BTNFACE));
						rc.InflateRect(-1,-1);

						rc.left += 4;
						rc.right -= 4;
					}

					DrawColumnHeader(hDC, rc, n);

					headerRect.left += m_column[n].m_width;
				}
			}

		// Draw an empty column to the right of window
			headerRect.right = client.right;
		//	dc.FillSolidRect(&headerRect, GetSysColor(COLOR_BTNFACE)/*grayColor*/);
		//	dc.Draw3dRect(headerRect.left, headerRect.top, headerRect.Width(), headerRect.Height(), GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW)/*darkGrayColor*/);
			//Draw3DRect(hDC, headerRect.left+1, headerRect.top+1, headerRect.Width()-2, headerRect.Height()-2, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW)/*darkGrayColor*/);

			CRect rc = headerRect;
			if (m_hHeaderTheme)
			{
				uxDrawThemeBackground(m_hHeaderTheme,
					 dc.m_hDC,
					 HP_HEADERITEM,
					 HIS_NORMAL,
					 &rc,
					 NULL);
			}
			else
			{
				dc.FillSolidRect(rc.left, rc.top, 1, rc.Height(), GetSysColor(COLOR_3DHILIGHT));
				dc.FillSolidRect(rc.left+1, rc.top, rc.Width()-1, 1, GetSysColor(COLOR_3DHILIGHT));

				dc.FillSolidRect(rc.left+1, rc.bottom-1, rc.Width()-1, 1, GetSysColor(COLOR_3DSHADOW));
				dc.FillSolidRect(rc.right-1, rc.top+1, 1, rc.Height()-1, GetSysColor(COLOR_3DSHADOW));

				rc.InflateRect(-1,-1);

				dc.FillSolidRect(&rc, GetSysColor(COLOR_BTNFACE));

			// dividing black line at bottom
				dc.FillSolidRect(0, m_headerHeight-1, client.right, 1, RGB(0,0,0));
			}
		}
	}

	dc.FillSolidRect(0, m_headerHeight, client.right, client.bottom- m_headerHeight, RGB(255, 255, 255)/*lightColor*/);

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	int state = SaveDC(hDC);

	int icon_cx;
	int icon_cy;
	ImageList_GetIconSize(m_hImageList, &icon_cx, &icon_cy);

	BOOL bHasButtons = TRUE;
	BOOL bHasLines = TRUE;
	BOOL bLinesAtRoot = TRUE;

	IntersectClipRect(hDC,
		0, m_headerHeight,
		client.right -  GetSystemMetrics(SM_CXVSCROLL),
		client.bottom-16);

	POINT oldOrg;
	OffsetViewportOrgEx(hDC, -scrollposX, m_headerHeight -scrollposY, &oldOrg);

	if (bLinesAtRoot && bHasLines)
	{
	// TODO, draw this in right column
		int count = m_pTree->CountExpanded(1);
		int height = count*m_ItemHeight;

		DrawVStippledLine(hDC, 3+4, m_ItemHeight/2, height-m_ItemHeight/2, m_clrLines);
	}

	int y = 0;

	C2Obj* pParentItem = m_pTree;
	UPOSITION pos = pParentItem->GetHeadPosition();

	int nextlevel = 0;
	while (pos)
	{
		int level = nextlevel;
		TreeItem* pItem = (TreeItem*)(C2Obj*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

		SetTextColor(hDC, RGB(0,0,0));
		SetBkMode(hDC, TRANSPARENT);

		CRect columnClip;
		columnClip.top = y;
		columnClip.bottom = y+m_ItemHeight;
		columnClip.left = 0;

		for (int n = 0; n < m_column.GetSize(); n++)
		{
			SetTextColor(hDC, RGB(0,0,0));
			SetBkMode(hDC, TRANSPARENT);

			if (m_column[n].m_bVisible)
			{
				columnClip.right = columnClip.left + m_column[n].m_width;

				_bstr_t itemColumnText;
				if (m_pSite)
				{
					BSTR b;
					m_pSite->GetItemText(pItem->m_itemData, n, &b);
					if (b) itemColumnText = _bstr_t(b, false);
				}

				if (n == 0 && itemColumnText.length() == 0)
				{
					itemColumnText = pItem->m_name;
				}

				CRect trect = columnClip;
				if (n == 0)
				{
					trect.left += (level-1)*m_Indentation;
					if (bLinesAtRoot) trect.left += m_Indentation;

					if (bHasLines)
					{
						if (pItem->CanExpand() && pItem->m_expanded)
						{
							int count = pItem->CountExpanded(1);
							int height = count*m_ItemHeight;

						//	int height = pItem->m_childList.GetCount()*m_ItemHeight;


							int x = trect.left + 3+4;
							x += m_Indentation;
							DrawVStippledLine(hDC, x, y+m_ItemHeight, y+height+m_ItemHeight/2, m_clrLines);
						}

						DrawHStippledLine(hDC, y+m_ItemHeight/2, trect.left+3+4+1, trect.left+m_Indentation, m_clrLines);
					}

					if (bHasButtons)
					{
						if (pItem->CanExpand())
						{
							CRect rc;
							rc.left = trect.left + 3;
							rc.top = trect.top + (m_ItemHeight-8)/2;
							rc.right = rc.left + 8+1;
							rc.bottom = rc.top + 8+1;

							if (m_hTreeViewTheme)
							{
								uxDrawThemeBackground(m_hTreeViewTheme,
									 dc.m_hDC,
									 TVP_GLYPH,
									 (pItem->m_expanded)? GLPS_OPENED: GLPS_CLOSED,
									 &rc,
									 NULL);
							}
							else
							{
								int l = trect.left + 3;
								int t = trect.top + (m_ItemHeight-8)/2;
								Rectangle(hDC, l, t, l+8+1, t+8+1);

								if (pItem->m_expanded)
								{
									MoveToEx(hDC, l+2, t+4, NULL);
									LineTo(hDC, l+6+1, t+4);
								}
								else
								{
									MoveToEx(hDC, l+2, t+4, NULL);
									LineTo(hDC, l+6+1, t+4);

									MoveToEx(hDC, l+4, t+2, NULL);
									LineTo(hDC, l+4, t+6+1);
								}
							}
						}
					}

					trect.left += m_Indentation;

					if (m_hImageList)
					{
						if (pItem->m_iIndex >= 0)
						{
							ImageList_Draw(m_hImageList, pItem->m_iIndex, hDC, trect.left, trect.top + (trect.Height()-icon_cy)/2, ((pItem->m_selected & 1)? ILD_SELECTED: 0) | ILD_TRANSPARENT);
						}

						trect.left += 18;
					}
				}

				if (itemColumnText.length())
				{
					int oldBk = SetBkMode(hDC, TRANSPARENT);
					COLORREF oldTextClr = GetTextColor(hDC);

					if (n == 0)
					{
						BOOL bHilight = FALSE;

						if (pItem != m_pActive || m_axedit.m_hWnd == NULL)
						{
							if ((pItem->m_selected & 1) || (pItem->m_selected & 2))	// selected
							{
								bHilight = TRUE;
							}

							SIZE size;
							GetTextExtentPoint32(hDC, itemColumnText, itemColumnText.length(), &size);

							CRect trect2 = trect;
							trect2.right = trect.left+size.cx+4;
							if (trect2.right > trect.right) trect2.right = trect.right;

							if (bHilight)	// selected
							{
								SetTextColor(hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
								FillSolidRect(hDC, &trect2, GetSysColor(COLOR_HIGHLIGHT));
							}
							else if (pItem->m_selected & 2)	// drop hilight
							{
								SetTextColor(hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
								FillSolidRect(hDC, &trect2, GetSysColor(COLOR_HIGHLIGHT));
							}
							else
							{
								SetTextColor(hDC, RGB(0, 0, 0));
							}

							DrawText(hDC, itemColumnText, itemColumnText.length(), &trect2, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);

							if (pItem == m_pActive)
							{
								DrawFocusRect(hDC, &trect2);
							}
						}
					}
					else
					{
						DrawText(hDC, itemColumnText, itemColumnText.length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
					}

					SetBkMode(hDC, oldBk);
					SetTextColor(hDC, oldTextClr);
				}

				columnClip.left += m_column[n].m_width;
			}
		}

		y += m_ItemHeight;
	}

	SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

	RestoreDC(hDC, state);

	SelectObject(hDC, hOldFont);
}
#endif

void TreeControl::EndEdit(bool bReturn)
{
#if 0
	if (m_axedit)
	{
		sysstring text;
		if (bReturn)
		{
			BSTR btext;
			m_edit->GetText(&btext);
			text = _bstr_t(btext, false);
		}

		IDispEventImpl<3, TreeControl, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_edit);
		m_axedit.DestroyWindow();

		if (bReturn)
		{
			Fire_EndLabelEdit(m_pActive, text);
		}
	}
#endif
}

#if 0
void TreeControl::SizeEdit()
{
	BSTR btext;
	m_edit->GetText(&btext);
	_bstr_t text = _bstr_t(btext, false);

	HDC hDC = CreateCompatibleDC(NULL);

	CComQIPtr<IFont> font = m_pFont;
	HFONT hFont;
	font->get_hFont(&hFont);

	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	SIZE size;
	GetTextExtentPoint32(hDC, text, text.length(), &size);

	SIZE charsize;
	GetTextExtentPoint32(hDC, " ", 1, &charsize);

	SelectObject(hDC, hOldFont);
	DeleteDC(hDC);

	int width = 2 + size.cx + charsize.cx*3;

	m_axedit.SetWindowPos(NULL, 0, 0, width, 16+2, SWP_NOZORDER | SWP_NOMOVE);
}

HRESULT __stdcall TreeControl::OnEditChange()
{
	SizeEdit();
	return S_OK;
}

HRESULT __stdcall TreeControl::OnEditChar(WCHAR ch)
{
	if (ch == '\n')
	{
	//MessageBeep(-1);
		EndEdit(TRUE);
	}

	return S_OK;
}
#endif

#if 0
LRESULT TreeControl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SetFocus();

	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnButtonDown(wParam, point, 0, FALSE);

	return 0;
}

LRESULT TreeControl::OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SetFocus();

	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnButtonDown(wParam, point, 1, FALSE);

//	return DefWindowProc(uMsg, wParam, lParam);
	return 0;
}

LRESULT TreeControl::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

//	Fire_ContextMenu(point.x, point.y);
	return 0;
}

LRESULT TreeControl::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnButtonDown(wParam, point, 0, TRUE);

	return 0;
}

void TreeControl::OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk)
{
#if 0
	EndEdit(TRUE);

//	point.x -= 1;

	if (!m_dragging)
	{
		/*
		if (point.y < m_thumbHeight)
		{
		}
		else
		*/
		{
			m_pane = -1;
			
			long scrollposY; m_vert->get_pos(&scrollposY);
			long scrollposX = 0;

			int x = 0;

			CRect paneRect;
			paneRect.left = 0;
			
			for (int i = 0; i < m_column.GetSize(); i++)
			{
				if (m_column[i].m_bVisible)
				{
					x += m_column[i].m_width;
					
					if (point.y >= 0 && point.y < m_headerHeight)
					{
						if (m_column[i].m_bSizeable)
						{
							if (abs(point.x - x) < 4)
							{
								m_dragging = 1;
								m_pane = i;
								break;
							}
						}
					}

					if (point.x < x)
					{
						m_pane = i;
						break;
					}

					paneRect.left = x;
				}
			}
			
			if (m_pane >= 0)
			{
				paneRect.right = paneRect.left + m_column[m_pane].m_width;

				if (point.y < m_headerHeight)
				{
					m_oldpt = point;
					m_oldwidth = m_column[m_pane].m_width;
				}
				else
				{
					DWORD bInsideExpand;
					CComPtr<TreeItem> pIFNode;
					HitTest(point, &bInsideExpand, &pIFNode);
					TreeItem* pFNode = static_cast<TreeItem*>(pIFNode.p);

					if (pFNode)
					{
						if (bInsideExpand)
						{
							if (pFNode->CanExpand())
							{
								long bCancel = VARIANT_FALSE;
								Fire_ItemExpanding(pFNode, !pFNode->m_expanded, &bCancel);

								if (TRUE)
								{
									Expand(pFNode, TV_TOGGLE, NULL);
								}
							}
						}
						else
						{
							DWORD oldstate = pFNode->m_selected;
							pFNode->m_selected = FALSE;	// Temporarily set it to deselected

							if (!(nFlags & MK_SHIFT) && m_pActive)
							{
								((TreeItem*)m_pActive->m_parent)->DeselectAll();
							}

							pFNode->m_selected |= 1;	// Set it (back) to selected
							if ((oldstate & 1) == 0)	// previously deselected
							{
								Fire_ItemStateChange(pFNode, oldstate, pFNode->m_selected);
							}

							if (bDblClk)
							{
								if (iButton == 0)
								{
									m_pActive = pFNode;

									InvalidateRect(NULL, TRUE);
									UpdateWindow();

									Fire_DblClick(m_pActive);
								}
							}
							else
							{
								if (pFNode != m_pActive)
								{
									m_pActive = pFNode;

									InvalidateRect(NULL, TRUE);
									UpdateWindow();

									Fire_Click(m_pActive);
								}
								else
								{
									if (m_pane == 0)
									{
										if (iButton == 0)
										{
											bool val;
											Fire_BeginLabelEdit(m_pActive, &val);

											if (TRUE)
											{
												EditLabel(m_pActive, NULL);
											}
										}
									}
								}
							}
	#if 0
							if (iButton == 0)
							{
								if (pFNode->m_type == 2)
								{
									CSiteFile* pFile = (CSiteFile*)pFNode;
									CSiteDir* pDir = (CSiteDir*)pFile->m_parent;

									if (bDblClk)
									{
										/*
										TCHAR pathName[512];
										_makepath(pathName, NULL, pDir->m_pathName, pFile->m_name, NULL);

										BOOL success;
										gApp->OpenDocument(_bstr_t(pathName), &success);
										*/
									}
									else
									{
	#if 0
										HGLOBAL hData = BuildSelectedFilesClipboard();
										if (hData)
										{
											CMyDropSource*  dropSource = new CMyDropSource;
											CMyDataObject* dataObject = new CMyDataObject;

											STGMEDIUM	stg = {0};
											stg.tymed = TYMED_HGLOBAL;
											stg.hGlobal = hData;
											stg.pUnkForRelease = NULL;
											
											FORMATETC	etc = {0};
											etc.cfFormat = CF_HDROP;//CF_UNICODETEXT;//49285;//RegisterClipboardFormat(CFSTR_SHELLURL);//CF_TEXT;
											etc.tymed = TYMED_HGLOBAL;
											etc.ptd = NULL;
											etc.dwAspect = DVASPECT_CONTENT;
											etc.lindex = -1;

											dataObject->SetData(&etc, &stg, TRUE);

											DWORD dropEffect = 0;
											HRESULT hr = ::DoDragDrop(dataObject, dropSource, DROPEFFECT_LINK | DROPEFFECT_COPY | DROPEFFECT_MOVE, &dropEffect);

											if (hr == DRAGDROP_S_DROP)
											{
												if (dropEffect/* & DROPEFFECT_MOVE*/)
												{
												}
											}

											GlobalFree(hData);

										//	delete dataObject;
										//	delete dropSource;

		#if 0
											COleDataSource source;
											source.CacheGlobalData(CF_HDROP, hData, NULL);

											if (source.DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE, NULL, NULL) == DROPEFFECT_COPY)
											{
											}

											source.Empty();
		#endif
														
											GlobalFree(hData);
										}
	#endif
									}
								}
							}
							else	// right-button
							{
								CComQIPtr<IUIContextManager> uiManager;
								gApp->get_uiManager(&uiManager);

								CComQIPtr<IMenuItem> menu;
								uiManager->FindMenu(ID_SITEFILES, &menu);
								if (menu)
								{
									CComQIPtr<IUIWnd> uiwnd;
									QueryInterface(IID_IUIWnd, (void**)&uiwnd);

									POINT scrpoint = point;
									ClientToScreen(&scrpoint);

									IID selectedID;
									menu->PopupMenu(uiwnd, NULL, scrpoint, 0, &selectedID);
								}
							}
	#endif
						}
					}
					else
					{
						if (!(nFlags & MK_SHIFT) && m_pActive)
						{
							((TreeItem*)m_pActive->m_parent)->DeselectAll();
						}

						m_pActive = NULL;

						InvalidateRect(NULL, TRUE);
					}
				}
			}
		}

		if (m_dragging)
		{
			SetCapture();
			
			if (m_dragging == 100)
			{
			//	m_bWasInside = FALSE;
			//	OnMouseMove(nFlags, point);
			}
			else
			{
			//	if (m_dragging == 10)
			//		OnMouseMove(nFlags, point);
			//	SetTimer(1, 50, NULL);
			}
		}
	}
#endif
}

LRESULT TreeControl::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	if (m_hWnd)
	{
		POINT point;
		point.x = (short)LOWORD(lParam);
		point.y = (short)HIWORD(lParam);

	//	point.x -= 1;

		if (m_dragging)
		{
			int width = m_oldwidth + (point.x-m_oldpt.x);
			m_oldwidth = width;

			if (width < 4) width = 4;
			else if (width > 800) width = 800;

			if (width != m_column[m_pane].m_width)
			{
				m_column[m_pane].m_width = width;
				Invalidate();
			}

			m_oldpt = point;
		}
	}
#endif
	return 0;
}

LRESULT TreeControl::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		ReleaseCapture();
		m_dragging = 0;
	}

	return 0;
}

LRESULT TreeControl::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	HWND hwnd = (HWND) wParam;       // handle to window with cursor 
	int nHittest = LOWORD(lParam);  // hit-test code 
	UINT wMouseMsg = HIWORD(lParam); // mouse-message identifier 

	if (nHittest == HTCLIENT)
	{
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		if (point.y < m_headerHeight)
		{
			int pane = -1;
			
			long scrollposY; m_vert->get_pos(&scrollposY);
			long scrollposX = 0;

			int x = 0;

			CRect paneRect;
			paneRect.left = 0;

			for (int i = 0; i < m_column.GetSize(); i++)
			{
				if (m_column[i].m_bVisible)
				{
					x += m_column[i].m_width;
					
					if (m_column[i].m_bSizeable)
					{
						if (abs(point.x - x) < 4)
						{
							pane = i;
							break;
						}
					}

					paneRect.left = x;
				}
			}

			if (pane >= 0)
			{
			//	::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZECOLUMN)));
				return TRUE;
			}
		}
	}

	return DefWindowProc(uMsg, wParam, lParam);
#endif
	return 0;
}

LRESULT TreeControl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	CRect	client;
	GetClientRect(&client);

	int cx = client.Width();
	int cy = client.Height();

	int sbWidth = GetSystemMetrics(SM_CYHSCROLL);
	int sbHeight = GetSystemMetrics(SM_CXVSCROLL);

	int top = m_headerHeight;

	::MoveWindow(m_axhorz.m_hWnd, 0, cy-sbHeight, cx-sbWidth, sbHeight, TRUE);
	::MoveWindow(m_axvert.m_hWnd, cx-sbWidth, top, sbWidth, cy-top-sbHeight, TRUE);

	::ShowWindow(m_axhorz.m_hWnd, SW_SHOW);
	::ShowWindow(m_axvert.m_hWnd, SW_SHOW);

	OnSize();
	InvalidateRect(NULL, TRUE);
#endif
	return 0;
}
#endif

#if 0

void TreeControl::InsertColumn(long index, BSTR name, long width, bool bSizeable, bool bVisible, long *pVal)
{
	CTreeColumn* column = new CTreeColumn;
	column->m_name = name;
	column->m_width = width;
	column->m_bSizeable = bSizeable;
	column->m_bVisible = bVisible;

	if (index >= 0)
		ASSERT(0);//m_column.InsertAt(index, column);
	else
		m_column.push_back(column);

#if 0
	if (m_hWnd)
	{
		OnSize();
		InvalidateRect(NULL, TRUE);
	}
#endif
}
#endif

#if 0
void TreeControl::CreateItem(/*[in]*/ DWORD itemData, /*[in]*/ BSTR name, /*[in]*/ long iIndex, /*[in]*/ long cChildren, /*[out,retval]*/ TreeItem* *pVal)
{
	ASSERT(pVal != NULL);

	TreeItem* pItem = new TreeItem(this);
	
	pItem->m_ownerCtl = this;
	ASSERT(0);
#if 0
	pItem->m_itemData = itemData;
	pItem->m_name = name;
	pItem->m_iIndex = iIndex;
#endif
	pItem->m_cChildren = cChildren;

	*pVal = pItem;

}
#endif

UIElement/*TreeItemChildren*/ * TreeControl::get_Children() const
{
	return m_Children;
}

void TreeControl::set_Children(UIElement/*TreeItemChildren*/ * Children)
{
	ASSERT(m_Children);
	Visual* pParent = m_Children->GetRParent();
	if (m_Children)	// First remove any previous child
	{
		pParent->RemoveRChild(m_Children);
	}

	m_Children = Children;
	if (m_Children)
	{
		ASSERT(0);
		//dynamic_cast<UIElement*>(pParent)->AddChild(m_Children);
		// TODO, had this ??
	#if 0
		pParent->InvalidateMeasure();
	#endif

	//	pParent->Measure(pParent->m_availSize);

	//	InvalidateMeasure();
		//pLayoutManager->MeasureAll();
	//	Measure(m_availSize);
	//	Arrange(m_desiredSize);
	//	Invalidate();
	}
}

#if 0
void TreeControl::InsertItem(DWORD itemData, TreeItem* parentItem, TreeItem* beforeItem, BSTR name, long iIndex, long cChildren, TreeItem* *pVal)
{
	ASSERT(0);
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	TreeItem* pParent = (TreeItem*)parentItem;
	if (pParent == NULL)
		pParent = m_pTree;

	TreeItem* pBefore = (TreeItem*)beforeItem;

	UPOSITION beforepos = NULL;
#if 0
	if (pBefore)
	{
		beforepos = pParent->m_childList.find((C2Obj*)pBefore);
		if (beforepos == NULL)
			return E_INVALIDARG;
	}
#endif

	CComObject<TreeItem>* pItem;
	CComObject<TreeItem>::CreateInstance(&pItem);
	pItem->AddRef();
	
	pItem->m_ownerCtl = this;
	pItem->m_itemData = itemData;
	pItem->m_name = name;
	pItem->m_iIndex = iIndex;
	pItem->m_cChildren = cChildren;

	pItem->m_parent = pParent;
	if (beforepos)
		pParent->m_childList.InsertBefore(beforepos, (C2Obj*)pItem);
	else
		pParent->m_childList.AddTail((C2Obj*)pItem);

	*pVal = pItem;
	(*pVal)->AddRef();

	if (m_hWnd)
	{
		OnSize();
		InvalidateRect(NULL, TRUE);
	}
}
#endif

#if 0
void TreeControl::FreeItem(TreeItem* pItem)
{
	if (m_pActive == pItem) m_pActive = NULL;

	ASSERT(0);
#if 0
	while (!pItem->m_childList.IsEmpty())
	{
		TreeItem* pChild = (TreeItem*)pItem->m_childList.RemoveHead();
		FreeItem(pChild);
	}

	pItem->Release();
#endif
}
#endif

void TreeControl::DeleteItem(TreeItem* item)
{
	ASSERT(0);
#if 0
	if (item == NULL) return E_INVALIDARG;

	TreeItem* pItem = (TreeItem*)item;

	UPOSITION pos = pItem->m_parent->m_childList.Find((C2Obj*)pItem);
	ASSERT(pos);

	pItem->m_parent->m_childList.RemoveAt(pos);

	FreeItem(pItem);

	if (m_hWnd)
	{
		OnSize();
		InvalidateRect(NULL, TRUE);
	}
#endif
}

/*
void TreeControl::SetSite(IUITreeControlSite *pSite)
{
	m_pSite = pSite;

	return S_OK;
}
*/
#if 0

void TreeControl::get_hImageList(DWORD *pVal)
{
	*pVal = (DWORD)m_hImageList;
}

void TreeControl::put_hImageList(HIMAGELIST newVal)
{
	m_hImageList = newVal;
}
#endif

void TreeControl::get_Indentation(long *pVal)
{
	*pVal = m_Indentation;
}

void TreeControl::set_Indentation(long newVal)
{
	if (m_Indentation != newVal)
	{
		m_Indentation = newVal;
		if (m_Indentation < MinIndent) m_Indentation = MinIndent;

		/*
		if (m_hWnd)
		{
			OnSize();	// TODO, only size horizontally
			InvalidateRect(NULL, TRUE);
		}
		*/
	}

}

void TreeControl::GetItemInfo(TreeItem* item, ULONG_PTR *itemdata, long *iIndex, long *cChildren)
{
	TreeItem* pItem = (TreeItem*)item;
	ASSERT(0);
#if 0
	if (itemdata) *itemdata = pItem->m_itemData;
	if (iIndex) *iIndex = pItem->m_iIndex;
#endif
	if (cChildren) *cChildren = pItem->m_cChildren;

}

void TreeControl::SetItemInfo(TreeItem* item, ULONG_PTR itemdata, long iIndex, long cChildren)
{
	TreeItem* pItem = (TreeItem*)item;
	ASSERT(0);
#if 0
	pItem->m_itemData = itemdata;
	pItem->m_iIndex = iIndex;
#endif
	pItem->m_cChildren = cChildren;

	InvalidateRender();

}

void TreeControl::SetSelectedItem(TreeItem* item)
{
	if (m_pSingleSelection != item)
	{
/*		if (m_pActive)	// Deselect all
		{
			((TreeItem*)m_pActive->m_parent)->DeselectAll();
		}

		m_pActive = (TreeItem*)item;

		if (m_pActive)
		{
			if (!(m_pActive->m_selected & 1))
			{
				m_pActive->m_selected |= 1;
				Fire_ItemStateChange(m_pActive, 0, m_pActive->m_selected);
			}
		}

		Invalidate();
*/	}

}

void TreeControl::SetItemState(TreeItem* item, uint state)
{

	TreeItem* pItem = (TreeItem*)item;
	if (pItem->m_selected != state)
	{
		uint oldState = pItem->m_selected;
		pItem->m_selected = state;
#if 0
		Fire_ItemStateChange(pItem, oldState, state);
#endif
		InvalidateRender();
	}

}

void TreeControl::GetItemState(TreeItem* item, ULONG_PTR *pVal)
{

	TreeItem* pItem = (TreeItem*)item;
	*pVal = pItem->m_selected;

}

#if 0
void TreeControl::SetExpanded(DWORD item, bool bExpanded)
{
	TreeItem* pItem = (TreeItem*)item;
	if ((pItem->m_expanded == 0) != (bExpanded == 0))
	{
		pItem->m_expanded = bExpanded;

		OnSize();
		Invalidate();
	}

	return S_OK;
}
#endif

#if 0
TreeItem* TreeControl::SetRootItem(DWORD itemdata)
{
	ASSERT(m_pTree != NULL);

	ASSERT(0);
#if 0
	m_pTree->m_itemData = itemdata;
#endif
	return m_pTree;
}
#endif

#if 0
void TreeControl::HitTest(POINT point, DWORD* flags, TreeItem* *pItem)
{

#if 0
	long scrollposY; m_vert->get_pos(&scrollposY);
	long scrollposX = 0;

	*pItem = NULL;
	if (flags) *flags = 0;

	if (point.y < m_headerHeight)
	{
	}
	else
	{
		POINT pt;
		pt.y = (point.y - (m_headerHeight)) + scrollposY;
		pt.x = point.x;

		C2Obj* pParentItem = m_pTree;//((CWebSite*)m_pDocument.p)->m_pRootDir;
		UPOSITION pos = pParentItem->GetHeadPosition();

		int topy;
		int y = 0;

		TreeItem* pFNode = NULL;

		int levelx;

		int	nextlevel = 0;
		while (pos)
		{
			int level = nextlevel;
			TreeItem* pItem = (TreeItem*)(C2Obj*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

			levelx = level*m_Indentation;

			topy = y;

			y += m_ItemHeight;

			if (pt.y < y)
			{
				pFNode = pItem;
				break;
			}
		}

		if (pFNode)
		{
			BOOL bInsideExpand = ((pt.x >= levelx && pt.x < levelx+16)/* || bDblClk*/);
			if (flags) *flags = bInsideExpand;

			*pItem = pFNode;
			(*pItem)->AddRef();
		}
	}
#endif
}
#endif

#if 0
void TreeControl::GetEditControl(IUIEdit **pEdit)
{
	if (pEdit == NULL) return E_POINTER;

	*pEdit = m_edit;
	if (*pEdit) (*pEdit)->AddRef();

	return S_OK;
}

void TreeControl::GetItemRect(TreeItem* item, long pane, bool bTextOnly, RECT *pRect)
{
	if (pRect == NULL) return E_POINTER;

	SetRectEmpty(pRect);

	long scrollposY; m_vert->get_pos(&scrollposY);
	
	BOOL bHasButtons = TRUE;
	BOOL bLinesAtRoot = TRUE;

	int y = m_headerHeight;
	y -= scrollposY;

	C2Obj* pParentItem = m_pTree;
	UPOSITION pos = pParentItem->GetHeadPosition();

	int nextlevel = 0;
	while (pos)
	{
		int level = nextlevel;
		TreeItem* pItem = (TreeItem*)(C2Obj*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

		if ((TreeItem*)item == pItem)
		{
			CRect columnClip;
			columnClip.top = y;
			columnClip.bottom = y+m_ItemHeight;
			columnClip.left = 0;

			if (pane == -1)
			{
			}
			else
			{
				_bstr_t itemColumnText;
				if (m_pSite)
				{
					BSTR b;
					m_pSite->GetItemText(pItem->m_itemData, pane, &b);
					itemColumnText = _bstr_t(b, false);
				}

				if (pane == 0 && itemColumnText.length() == 0)
				{
					itemColumnText = pItem->m_name;
				}

				for (int n = 0; n <= pane; n++)
				{
					columnClip.right = columnClip.left + m_column[n].m_width;
					if (n < pane)
						columnClip.left += m_column[n].m_width;
				}

				*pRect = columnClip;

				if (pane == 0)
				{
					pRect->left += (level-1)*m_Indentation;
					if (bLinesAtRoot) pRect->left += m_Indentation;

					pRect->left += m_Indentation;

					//if (bHasButtons) pRect->left += 18;
					if (m_hImageList) pRect->left += 18;
				}
			}

			break;
		}

		y += m_ItemHeight;
	}

	return S_OK;
}

void TreeControl::EditLabel(TreeItem* item, IUIEdit **ppEdit)
{
	if (m_pActive)
	{
		((TreeItem*)m_pActive->m_parent)->DeselectAll();
	}

	m_pActive = (TreeItem*)item;

	_bstr_t text;
	if (m_pSite)
	{
		BSTR btext;
		m_pSite->GetItemText(m_pActive->m_itemData, m_pane, &btext);
		text = _bstr_t(btext, false);
	}

	if (m_pane == 0 && text.length() == 0)
	{
		text = m_pActive->m_name;
	}

	CRect itemrect;
	GetItemRect(m_pActive, 0, FALSE, &itemrect);

	IUnknown* p;
	CRect rc = itemrect;
	rc.InflateRect(1, 1);
	m_axedit.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axedit.AttachControl(m_edit, &p);

	SizeEdit();

	IDispEventImpl<3, TreeControl, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_edit);

	m_edit->put_font(m_pFont);
	m_edit->SetText(text);

	m_axedit.SetFocus();
	m_edit->SetSel(0, -1, VARIANT_FALSE);
	
	if (ppEdit)
	{
		*ppEdit = m_edit;
		(*ppEdit)->AddRef();
	}

	return S_OK;
}

void TreeControl::Expand(TreeItem* item, TVExpandCode code, bool *pSuccess)
{
	TreeItem* pItem = (TreeItem*)item;
	if (pItem == NULL)
	{
		if (pSuccess) *pSuccess = VARIANT_FALSE;
		return S_OK;
	}

	switch (code)
	{
	case TV_COLLAPSE:
		pItem->m_expanded = VARIANT_FALSE;
		break;

	case TV_EXPAND:
		pItem->m_expanded = VARIANT_TRUE;
		break;

	case TV_TOGGLE:
		pItem->m_expanded = !pItem->m_expanded;
		break;

	case TV_COLLAPSERESET:
		{
			pItem->m_expanded = VARIANT_FALSE;

		// Remove children
			while (!pItem->m_childList.IsEmpty())
			{
				TreeItem* pChild = (TreeItem*)(C2Obj*)pItem->m_childList.RemoveHead();
				FreeItem(pChild);
			}
		}
		break;

	default:
		if (pSuccess) *pSuccess = VARIANT_FALSE;
		return S_OK;
	}

	if (m_hWnd)
	{
		OnSize();
		InvalidateRect(NULL, TRUE);
	}

	if (pSuccess) *pSuccess = VARIANT_TRUE;

	return S_OK;
}

void TreeControl::get_ItemHeight(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_ItemHeight;
	return S_OK;
}

void TreeControl::put_ItemHeight(long newVal)
{
	if (m_ItemHeight != newVal)
	{
		m_ItemHeight = newVal;
		if (m_ItemHeight <= 0) m_ItemHeight = 18;

		if (m_hWnd)
		{
			OnSize();
			InvalidateRect(NULL, TRUE);
		}
	}

	return S_OK;
}

void TreeControl::UpdateItem(TreeItem *item)
{
	// TODO, invalidate only items rect

	if (m_hWnd)
	{
		Invalidate();
	}

	return S_OK;
}
#endif

}	// UI
}
