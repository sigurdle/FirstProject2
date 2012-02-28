#include "stdafx.h"
#include "LXUI2.h"
#include "Menu.h"

#include "Popup.h"
#include "MenuItem.h"
#include "DockPanel.h"
#include "LXUIBoxWindow.h"

namespace System
{
namespace UI
{

Menu::Menu()
{
#if 0
	{
		m_pPopupBorder = new Border(new Thickness(2));
		m_pPopupBorder->set_Background(new SolidColorBrush(new Color(255, 255, 255)));

		m_pPopupPanel = new DockPanel;
		m_pPopupBorder->set_Child(m_pPopupPanel);

		m_pMenuPopupElement = new CLXUIMenuPopupElement;
#if 0
		m_pMenuPopupElement->SetRParent(this);
		m_pMenuPopupElement->SetOwnerWindow(m_pMenuPopupElement);
#endif
		m_pMenuPopupElement->set_Content(m_pPopupBorder);
	}

	{
		m_pBorder = NULL;
	}
#endif
}

#if 0
Menu::Menu(UIElement* pVisual)
{
	{
		m_pPopupBorder = new Border(new Thickness(2));
		m_pPopupBorder->set_Background(new SolidColorBrush(new Color(255, 255, 255)));

		m_pPopupPanel = new DockPanel;
		m_pPopupBorder->set_Child(m_pPopupPanel);

		m_pMenuPopupElement = new CLXUIMenuPopupElement;
#if 0
		m_pMenuPopupElement->SetRParent(this);
		m_pMenuPopupElement->SetOwnerWindow(m_pMenuPopupElement);
#endif
		m_pMenuPopupElement->set_Content(m_pPopupBorder);
	}

	{
		m_pBorder = new Border;
		DockPanel* pPanel = new DockPanel;
		{
			Shapes::Polyline* p = new Shapes::Polyline;
			PointCollection* points = new PointCollection;
			points->Add(Point(0, 0));
			points->Add(Point(6, 6));
			points->Add(Point(0, 12));
			p->set_Points(points);

			pPanel->SetDock(p, DockPanel::Right);
			pPanel->get_Children()->Add(p);
		}
		{
			pPanel->SetDock(pVisual, DockPanel::Fill);
			pPanel->get_Children()->Add(pVisual);
		}

		m_pBorder->set_Child(pPanel);
	}

	set_VisualTree(m_pBorder);
}
#endif

Menu::~Menu()
{
	//delete m_pMenuPopupElement;
}

void Menu::AddItem(Object* item)
{
	ASSERT(0);
}

void Menu::AddMenuItem(Menu* pVisual)
{
#if 0
	pVisual->SetOwnerWindow(m_pPopupPanel->get_OwnerWindow());
#endif
	m_pPopupPanel->get_Children()->Add(pVisual);
}

void Menu::AddItem(UIElement* pVisual, long nCmd)
{
	ASSERT(0);

//	MenuItem* pButton = new MenuItem(pVisual, nCmd);
	//pButton->put_Content(pVisual);
#if 0
	pButton->SetOwnerWindow(m_pPopupPanel->get_OwnerWindow());
#endif
//	m_pPopupPanel->get_Children()->Add(pButton);
}

void Menu::AddSeparator()
{
	Border* pBorder = new Border(new Thickness(1));
	/*
	pBorder->m_LeftBrush = new SolidColorBrush(Color(100, 100, 100));
	pBorder->m_TopBrush = new SolidColorBrush(Color(100, 100, 100));
	pBorder->m_RightBrush = new SolidColorBrush(Color(200, 200, 200));
	pBorder->m_BottomBrush = new SolidColorBrush(Color(200, 200, 200));
	*/
#if 0
	pBorder->SetOwnerWindow(m_pPopupPanel->get_OwnerWindow());
#endif
	m_pPopupPanel->get_Children()->Add(pBorder);
}

void Menu::OnMouseDown(MouseButtonEventArgs* args)
{
//	evt->stopPropagation();

	LDraw::RectD bounds = GetScreenBounds();

	if (m_pMenuPopupElement)
	{
#if 0
		Event* evt = new Event;
		evt->InitEvent(WSTR("onpopupshowing"),
			true,	// bubbles
			true	// cancelable
		);

		bool doDefault = m_pMenuPopupElement->dispatchEvent(evt);

		if (doDefault)
#endif
		{
			ASSERT(0);
#if 0
			m_pMenuPopupElement->Popup(this, LDraw::PointI((int)bounds.GetRight()-2, (int)bounds.GetTop()));
#endif
		}
	}
}

#if 0

		}
		else if (type == MouseEvent::mouseover)
		{
			if (m_pBorder)
			{
				evt->stopPropagation();
				m_pBorder->set_Background(new SolidColorBrush(new Color(120, 190, 255)));
				Invalidate();
			}
		}
		else if (type == MouseEvent::mouseout)
		{
			if (m_pBorder)
			{
				evt->stopPropagation();
				m_pBorder->set_Background(NULL);
				Invalidate();
			}
		}
		else if (*type == L"command"/* || type == OLESTR("cancel")*/)
		{
//			evt->stopPropagation();
			ASSERT(m_pMenuPopupElement);

			dynamic_cast<WindowHost*>(m_pMenuPopupElement->GetOwnerWindow()->m_pSite)->Close();
#if 0
			m_pMenuPopupElement->m_pSite->Close();//DestroyWindow();
#endif

			//m_pMenuPopupElement->RemoveBoxesAndChildren();

#if 0
			element->removeAttribute(L"pushed");
#endif
		}
	}
}
#endif

}	// UI
}
