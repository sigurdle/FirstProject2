#include "stdafx.h"
#include "HTML2.h"

#include "PSMILElement.h"

namespace System
{
namespace Web
{

#if 0
CPSMILElement* CreatePSMILElement(ILDOMElement* element, CHTMFrame* pFrame)
{
	CPSMILElement* pElement2 = NULL;

	CComBSTR tagName;
	element->get_localName(&tagName);
	if (tagName.Length() == 0)
	{
		element->get_tagName(&tagName);
	}

	if (!wcscmp(tagName, L"root-layout"))
	{
		CComObject<CPSMILRootLayoutElement>* pElement;
		CComObject<CPSMILRootLayoutElement>::CreateInstance(&pElement);
		pElement->AddRef();
		pElement2 = pElement;
	}
	else if (!wcscmp(tagName, L"topLayout"))
	{
		CComObject<CPSMILTopLayoutElement>* pElement;
		CComObject<CPSMILTopLayoutElement>::CreateInstance(&pElement);
		pElement->AddRef();
		pElement2 = pElement;
	}
	else if (!wcscmp(tagName, L"region"))
	{
		CComObject<CPSMILRegionElement>* pElement;
		CComObject<CPSMILRegionElement>::CreateInstance(&pElement);
		pElement->AddRef();
		pElement2 = pElement;
	}
//
	else	// Generic/Unknown svg element
	{
		CComObject<CPSMILElement>* pElement;
		CComObject<CPSMILElement>::CreateInstance(&pElement);
		pElement2 = pElement;
	}

	if (pElement2)
	{
		pElement2->m_pNode = element;
		pElement2->m_pFrame = pFrame;
	}

	return pElement2;
}
#endif

// virtual
void PSMILElement::BuildChildren()
{
	ASSERT(0);
#if 0
	ASSERT(m_pWindow);

// Build children
	CComQIPtr<ILDOMNode> child;
	m_pNode->get_firstChild(&child);

	while (child != NULL)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);

		/*
		if (nodeType == LNODE_TEXT)
		{
			CHTMPText* pItem = new CHTMPText(child);
			pItem->m_pFrame = m_pFrame;
			pItem->BuildWords();
		//	pPElement = pPText;

			pItem->m_pFrame = m_pFrame;

			pItem->m_parent = this;
			m_childList.AddTail(pItem);
		}
		else
		*/
		if (nodeType == LNODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement> element = child;

			//BSTR btagName;
			//element->get_tagName(&btagName);
			//_bstr_t tagName = _bstr_t(btagName, false);

			CPElement* pElement2 = m_pView->CreateElement(element);

			if (pElement2)
			{
				CComQIPtr<CLDOMElementImplImpl>(element)->m_pNodes.Add(pElement2);

				pElement2->BuildChildren();

				pElement2->m_parent = this;
				m_childList.AddTail(pElement2);
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

#if 0
// Build list of renderable children
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CPSVGElementImpl* pElement = (CPSVGElementImpl*)m_childList.GetNext(pos);

		//if (pElement->m_display != Display_none)
		{
			CComQIPtr<ISVGRenderElement> render = pElement->m_pNode;
			if (render)
			{
				m_childListRender.AddTail(pElement);
			}
		}
	}
#endif
#endif
}

}	// Web
}
