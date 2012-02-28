#include "stdafx.h"
#include "LXUI2.h"
#include "LXUITabsElement.h"

#include "LXUITabElement.h"

#include "DockPanel.h"

namespace System
{
namespace UI
{

CLXUITabsElement::CLXUITabsElement()
{
	m_selectedIndex = -1;

	m_Panel = new DockPanel;
	set_VisualTree(m_Panel);
}

/*
LDraw::SizeD CLXUITabsElement::Measure(LDraw::SizeD availSize)
{
	return Control::MeasureOverride(availSize);
}

void CLXUITabsElement::OnArrange(LDraw::SizeD finalSize)
{
	Control::OnArrange(finalSize);
}
*/

void CLXUITabsElement::AddChild(TabElement* child)
{
	DockPanel::SetDock(child, DockPanel::Left);
	m_Panel->AddChild(child);

	/*
	CLXUITabElement* pTab = new CLXUITabElement;
	pTab->m_pBorder->set_Content(child);

	DockPanel::SetDock(pTab, DockPanel::Left);
	m_Panel->AddRChild(pTab);
	*/
}

#if 0
void CLXUITabsElement::handleEvent(Event* evt)
{
	ASSERT(0);
#if 0

	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (*type == L"click")
		{
			evt->stopPropagation();

			UIElement* target = dynamic_cast<UIElement*>(evt->get_target());

			for (int i = 0; i < m_Panel->get_rchildList()->get_Size(); i++)
			{
				TabElement* tab = static_cast<TabElement*>((*m_Panel->get_rchildList())[i]);
				if (target == tab/*target->IsDescendantOf(tab)*/)
				{
					tab->m_pBorder->set_Background(new SolidColorBrush(new Color(255, 255, 255)));
					// TODO
					m_selectedIndex = i;
				}
				else
				{
					tab->m_pBorder->set_Background(NULL);
				}
			}

			Event* changeEvt = new Event;
			changeEvt->InitEvent(WSTR("selectionChanged"), true, true);
			bool doDefault = dispatchEvent(changeEvt);
			if (doDefault)
			{
				;//m_selectedIndex = i;
			}

		//	CLXUIMouseEvent* mouseEvt = dynamic_cast<CLXUIMouseEvent*>(evt);
		}
	}
#endif
}
#endif

int CLXUITabsElement::get_selectedIndex() const
{
	return m_selectedIndex;

#if 0
	long n = 0;
	for (int i = 0; i < m_childNodes->m_items.GetSize(); i++)
	{
		CComQIPtr<ILDOMElement> tab = m_childNodes->m_items[i];
		if (tab)
		{
			CComBSTR selected;
			tab->getAttribute(L"selected", &selected);
			if (!cmpbstr(selected, L"true"))
			{
				*pVal = n;
				return S_OK;
			}
			n++;
		}
	}
#endif
}

void CLXUITabsElement::set_selectedIndex(int newVal)
{
#if 0
	long n = 0;
	for (int i = 0; i < m_childNodes->m_items.GetSize(); i++)
	{
		CComQIPtr<ILDOMElement> tab = m_childNodes->m_items[i];
		if (tab)
		{
			if (newVal == n)
			{
				ATLASSERT(0);
#if 0
				tab->setAttribute(L"selected", L"true");
#endif
			}
			else
			{
				ATLASSERT(0);
#if 0
				tab->removeAttribute(L"selected");
#endif
			}

			n++;
		}
	}
#endif
}

/*
STDMETHODIMP CLXUITabsElement::get_selectedItem(ILXUIElement **pVal)
{
	ATLASSERT(0);
	return S_OK;
}

STDMETHODIMP CLXUITabsElement::put_selectedItem(ILXUIElement *newVal)
{
	BOOL bFound = FALSE;

	for (int i = 0; i < m_childNodes->m_items.GetSize(); i++)
	{
		CComQIPtr<ILXUIElement> tab = m_childNodes->m_items[i];
		if (tab)
		{
			if (newVal == tab)
			{
				ATLASSERT(0);
#if 0
				tab->setAttribute(L"selected", L"true");
#endif
				bFound = TRUE;
			}
			else
			{
				ATLASSERT(0);
#if 0
				tab->removeAttribute(L"selected");
#endif
			}
		}
	}

	ATLASSERT(bFound);

	if (bFound)
		return S_OK;
	else
		return E_FAIL;
}
*/

}	// UI
}
