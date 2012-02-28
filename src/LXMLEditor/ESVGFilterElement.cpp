#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "ESVGFilterElement.h"

#if 0

CESVGFilterElement::CESVGFilterElement()
{
	m_effectsUI = NULL;
//	m_items = NULL;

	for (int i = 0; i < 6; i++)
	{
		m_cItems[i] = NULL;
	}
}

int CESVGFilterElement::FinalConstruct()
{
	CESVGElementImpl<IESVGFilterElement>::FinalConstruct();

	CComObject<CStdFilterPrimitiveElement>* pItem;

	CComObject<CStdFilterPrimitiveElement>::CreateInstance(&pItem);
	pItem->AddRef();
	pItem->m_name = "Source Graphic";
	pItem->m_result = L"SourceGraphic";
	m_cItems[0] = pItem;

	CComObject<CStdFilterPrimitiveElement>::CreateInstance(&pItem);
	pItem->AddRef();
	pItem->m_name = "Source Alpha";
	pItem->m_result = L"SourceAlpha";
	m_cItems[1] = pItem;

	CComObject<CStdFilterPrimitiveElement>::CreateInstance(&pItem);
	pItem->AddRef();
	pItem->m_name = "Background Graphic";
	pItem->m_result = L"BackgroundGraphic";
	m_cItems[2] = pItem;

	CComObject<CStdFilterPrimitiveElement>::CreateInstance(&pItem);
	pItem->AddRef();
	pItem->m_name = "Background Alpha";
	pItem->m_result = L"BackgroundAlpha";
	m_cItems[3] = pItem;

	return 0;
}

void CESVGFilterElement::FinalRelease()
{
	for (int i = 0; i < 6; i++)
	{
		if (m_cItems[i])
		{
			m_cItems[i]->Release();
			m_cItems[i] = NULL;
		}
	}

	CESVGElementImpl<IESVGFilterElement>::FinalRelease();
}

void CESVGFilterElement::BuildItems()
{
//	delete m_items;
//	m_items = new CChildren;
	m_items.RemoveAll();

	m_items.Add(m_cItems[0]);
//	m_cItems[0]->m_parentNode = this;

	m_items.Add(m_cItems[1]);
//	m_cItems[1]->m_parentNode = this;

	m_items.Add(m_cItems[2]);
//	m_cItems[2]->m_parentNode = this;

	m_items.Add(m_cItems[3]);
//	m_cItems[3]->m_parentNode = this;

	CComPtr<ILDOMNode> node;
	m_domElement->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			CComPtr<IEElement> eElement;
			m_pDocument->GetEElementFromDOMElement(element, &eElement);

			CComQIPtr<IESVGFilterPrimitiveElement> pItem = eElement;
			if (pItem)
			{
				m_items.Add(pItem);
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
	/*
	for (int i = 0; i < m_children.GetSize(); i++)
	{
		CComQIPtr<IESVGFilterPrimitiveElement> pItem = m_children[i];
		if (pItem)
		{
			m_items.Add(pItem);
		}
	}
	*/
}

void CESVGFilterElement::ShowUI()
{
/*
	if (m_effectsUI == NULL)
	{
		m_effectsUI = (CFilterGraphView*)sBasic->CreateCmdTarget(IID_FILTERGRAPHVIEW);
		m_effectsUI->m_pLayer = this;

		m_effectsUI->CreateMDIView(gApp->m_frameUI, g_hInst,
			0,
			IDR_TIMELINE
			);

		CUString title;
		title.Format("%s (Effects)", (char*)m_domElement->tagName);
		m_effectsUI->SetUITitle(title);
	}
*/
}

#endif