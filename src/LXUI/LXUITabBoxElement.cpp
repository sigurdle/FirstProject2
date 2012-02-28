#include "stdafx.h"
#include "LXUI2.h"
#include "LXUITabBoxElement.h"
#include "DockPanel.h"

namespace System
{
namespace UI
{

#if 0
//////////////////////////////////////////////////////////////////////
// CLXUITab

STDMETHODIMP CLXUITab::get_contentElement(ILXUIElement **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_contentElement;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}
#endif

//////////////////////////////////////////////////////////////////////
// CLXUITabBoxElement

CLXUITabBoxElement::CLXUITabBoxElement()
{
	m_Panel = new DockPanel;
	set_VisualTree(m_Panel);
}

#if 0
void CLXUITabBoxElement::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (*type == L"selectionChanged")
		{
			evt->stopPropagation();

			CLXUITabsElement* pTabs = dynamic_cast<CLXUITabsElement*>(m_Panel->get_Children()->GetItem(0));

			Panel* panel = dynamic_cast<Panel*>(m_Panel->get_Children()->GetItem(1));

			for (int i = 0; i < panel->get_Children()->GetCount(); i++)
			{
				panel->get_Children()->GetItem(i)->set_Visibility(Collapsed);
			}

			int selectedIndex = pTabs->get_selectedIndex();
			if (selectedIndex >= 0)
			{
				UIElement* tab = panel->get_Children()->GetItem(selectedIndex);

				//tab->InvalidateMeasure();
				tab->Measure(LDraw::SizeD(0, 0));
				tab->set_Visibility(Visible);
			}
		}
	}
}
#endif

#if 0
STDMETHODIMP CLXUITabBoxElement::createPage(/*[out,retval]*/ ILXUITab* *pVal)
{
	ATLASSERT(0);
#if 0
	if (pVal == NULL) return E_POINTER;

	CComObject<CLXUITab>* pPage;
	CComObject<CLXUITab>::CreateInstance(&pPage);
	if (pPage)
	{
		pPage->AddRef();

		m_ownerDocument->createObjectNS(L"http://www.lerstad.com/2004/lxui", L"tab", &pPage->m_captionElement);

		m_ownerDocument->createObjectNS(L"http://www.lerstad.com/2004/lxui", L"vbox", &pPage->m_contentElement);
		ATLASSERT(0);
#if 0
		pPage->m_contentElement->setAttribute(L"style",	L"-moz-box-flex: 1;");
#endif

		*pVal = pPage;
	}
#endif
	return S_OK;
}

STDMETHODIMP CLXUITabBoxElement::insertPage(/*[in]*/ long index, /*[in]*/ ILXUITab* page)
{
	ATLASSERT(0);
#if 0
	CLXUITab* pPage = static_cast<CLXUITab*>(page);

	CComPtr<ILXUIElement> tabs = ::GetElementByTagNameNS(this, L"http://www.lerstad.com/2004/lxui", L"tabs");
	if (tabs == NULL)
	{
		m_ownerDocument->createObjectNS(L"http://www.lerstad.com/2004/lxui", L"tabs", &tabs);
		appendChild(tabs, NULL);
	}

	CComPtr<ILXUIElement> tabpanels = ::GetElementByTagNameNS(this, L"http://www.lerstad.com/2004/lxui", L"tabpanels");
	if (tabpanels == NULL)
	{
		m_ownerDocument->createObjectNS(L"http://www.lerstad.com/2004/lxui", L"tabpanels", &tabpanels);
		appendChild(tabpanels, NULL);
	}

	//CComPtr<ILDOMElement> element;
	//m_ownerDocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"page", &element);

	tabs->appendChild(pPage->m_captionElement, NULL);
	tabpanels->appendChild(pPage->m_contentElement, NULL);

	//appendChild(element, NULL);
#endif
	return S_OK;
}

STDMETHODIMP CLXUITabBoxElement::removePage(/*[in]*/ long index, /*[out,retval]*/ ILXUITab* *pVal)
{
	ATLASSERT(0);
	return S_OK;
}

STDMETHODIMP CLXUITabBoxElement::setActivePage(/*[in]*/ VARIANT vpage)
{
	ATLASSERT(0);
#if 0
	if (vpage.vt == VT_NULL || vpage.vt == VT_EMPTY)
	{
		return removeAttribute(L"selectedIndex");
	}
	else if (vpage.vt == VT_UNKNOWN || vpage.vt == VT_DISPATCH)
	{
		CComQIPtr<ILXUIPageElement> page = vpage.punkVal;
		if (page == NULL)
			return E_INVALIDARG;

		for (int i = 0; i < m_childNodes->m_items.GetSize(); i++)
		{
			if (m_childNodes->m_items[i] == page)
			{
				WCHAR buf[64];
				swprintf(buf, L"%d", i);
				return setAttribute(L"selectedIndex", buf);
			}
		}
	}
#endif
	return E_INVALIDARG;
}

// EventTarget
// virtual
HRESULT CLXUITabBoxElement::dispatchEvent2(/*[in]*/ ILDOMEvent * evt, /*[in]*/ VARIANT_BOOL bCapture, /*[out,retval]*/ VARIANT_BOOL * doDefault)
{
	CComBSTR type;
	evt->get_type(&type);

	LDOMEventPhaseType phase;
	evt->get_eventPhase(&phase);
	if (phase != CAPTURING_PHASE)
	{
#if 0
		if (!wcscmp(type, L"DOMAttrModified"))
		{
			CComQIPtr<ILDOMMutationEvent> mutEvt(evt);

			CComBSTR attrName;
			mutEvt->get_attrName(&attrName);

			if (!wcscmp(L"selected", attrName))
			{
				CComQIPtr<ILXUITabsElement> tabs = GetElementByTagNameNS(this, L"http://www.lerstad.com/2004/lxui", L"tabs");
				CComPtr<ILDOMElement> tabpanels = GetElementByTagNameNS(this, L"http://www.lerstad.com/2004/lxui", L"tabpanels");

				if (tabs && tabpanels)
				{
					long selectedIndex;
					tabs->get_selectedIndex(&selectedIndex);

					CComPtr<ILDOMNodeList> childNodes;
					tabpanels->get_childNodes(&childNodes);

					long length;
					childNodes->get_length(&length);

					for (int i = 0; i < length; i++)
					{
						CComPtr<ILDOMNode> node;
						childNodes->item(i, &node);

						CComQIPtr<ILElementCSSInlineStyle> stylable = node;
						ATLASSERT(stylable);
						if (stylable)
						{
							CComPtr<ILCSSStyleDeclaration> style;
							stylable->get_style(&style);

							if (i == selectedIndex)
								style->removeProperty(L"display-role", NULL);
							else
								style->setProperty(L"display-role", L"none", NULL/*priority*/);
						}
					}
				}
			}
		}
#endif
	}
	return CEventTargetImpl<CLXUITabBoxElement>::dispatchEvent2(evt, bCapture, doDefault);
}

#if 0
STDMETHODIMP CLXUITabBoxElement::OnChanged(NotifyType type, IUnknown *targetObject, IUnknown *immtargetObject, DISPID dispID)
{
	CComQIPtr<ILXUITabsElement> tabs = GetElementByTagNameNS(this, L"http://www.lerstad.com/2004/lxui", L"tabs");
	CComPtr<ILDOMElement> tabpanels = GetElementByTagNameNS(this, L"http://www.lerstad.com/2004/lxui", L"tabpanels");

	if (tabs && tabpanels)
	{
		long selectedIndex;
		tabs->get_selectedIndex(&selectedIndex);

		CComPtr<ILDOMNodeList> childNodes;
		tabpanels->get_childNodes(&childNodes);

		long length;
		childNodes->get_length(&length);

		for (int i = 0; i < length; i++)
		{
			CComPtr<ILDOMNode> node;
			childNodes->item(i, &node);

			CComQIPtr<ILElementCSSInlineStyle> stylable = node;
			ATLASSERT(stylable);
			if (stylable)
			{
				CComPtr<ILCSSStyleDeclaration> style;
				stylable->get_style(&style);

				if (i == selectedIndex)
					style->removeProperty(L"display-role", NULL);
				else
					style->setProperty(L"display-role", L"none", NULL/*priority*/);
			}
		}
	}

	FireOnChanged(type, targetObject, dispID);
	return S_OK;
}
#endif

#endif

}	// UI
}
