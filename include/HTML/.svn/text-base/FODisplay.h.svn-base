#pragma once

#include "cssunits.h"

class CFOPage
{
public:
	double m_width;
	double m_height;

	CHTMPElement* m_pElement;

	CFOPage()
	{
		m_pElement = NULL;
	}
};

class CFORegion
{
public:
	CComPtr<ILDOMElement> m_domelement;

	CFORegion(ILDOMElement* domelement)
	{
		m_domelement = domelement;
	}

	long GetColumnCount()
	{
		BSTR b;
		m_domelement->getAttribute(L"column-count", &b);
		if (b)
		{
			return max(1, atol(_bstr_t(b, false)));
		}
		else
			return 1;
	}
};

class CFOSimplePageMaster
{
public:
	CComPtr<ILDOMElement> m_domelement;
	double m_pageWidth;
	double m_pageHeight;

	CFORegion* m_regions[4];

	CFOSimplePageMaster(ILDOMElement* domelement)
	{
		m_domelement = domelement;
		m_pageWidth = 0;
		m_pageHeight = 0;

		m_regions[0] = NULL;
		m_regions[1] = NULL;
		m_regions[2] = NULL;
		m_regions[3] = NULL;

		BSTR b;

		m_domelement->getAttribute(L"page-width", &b);
		if (b)
		{
			m_pageWidth = GetCSSValue(b);
			SysFreeString(b);
		}

		m_domelement->getAttribute(L"page-height", &b);
		if (b)
		{
			m_pageHeight = GetCSSValue(b);
			SysFreeString(b);
		}
	}

	void Build()
	{
		CComPtr<ILDOMElement> regionBody = GetElementByTagNameNS(m_domelement, L"http://www.w3.org/1999/XSL/Format", L"region-body", FALSE);
		if (regionBody)
		{
			m_regions[0] = new CFORegion(regionBody);
		}
	}

	_bstr_t GetName()
	{
		BSTR bname;
		m_domelement->getAttribute(L"master-name", &bname);
		return _bstr_t(bname, false);
	}

	double GetPageWidth()
	{
		return m_pageWidth;
	}

	double GetPageHeight()
	{
		return m_pageHeight;
	}
};

class CFOLayoutMasterSet
{
public:
	CArray<CFOSimplePageMaster*,CFOSimplePageMaster*> m_simplePageMasters;

	CFOSimplePageMaster* FindSimplePageMasterByName(BSTR name)
	{
		for (int i = 0; i < m_simplePageMasters.GetSize(); i++)
		{
			if (!wcscmp(m_simplePageMasters[i]->GetName(), name))
			{
				return m_simplePageMasters[i];
			}
		}

		return NULL;
	}

	void Build(ILDOMElement* element)
	{
		CComPtr<ILDOMNode> node;
		element->get_firstChild(&node);
		while (node)
		{
			CComQIPtr<ILDOMElement> element = node;

			BSTR blocalName;
			element->get_localName(&blocalName);
			_bstr_t localName = _bstr_t(blocalName, false);

			if (!wcscmp(localName, L"simple-page-master"))
			{
				CFOSimplePageMaster* pSimplePageMaster = new CFOSimplePageMaster(element);

				m_simplePageMasters.Add(pSimplePageMaster);

				pSimplePageMaster->Build();
			}

			CComQIPtr<ILDOMNode> nextSibling;
			node->get_nextSibling(&nextSibling);
			node = nextSibling;
		}
	}
};

//#include "PreviewItem.h"

class CFODisplay
{
public:
	CFOLayoutMasterSet* m_layoutMasterSet;
	CArray<CFOPage*,CFOPage*> m_pages;
	CHTMLWindow* m_pFrame;

	void Flow()
	{
	}

	// Builds a tree of rendering items (used for rendering) from the HTML DOM
	void BuildFOTree(CHTMPElement* pThis, ILDOMNode* node)
	{
#if 0
	// Build children
		CComQIPtr<ILDOMNode> child;
		node->get_firstChild(&child);

		while (child != NULL)
		{
			//CHTMPNode* pPElement = NULL;

			LDOMNodeType nodeType;
			child->get_nodeType(&nodeType);

			if (nodeType == LNODE_TEXT)
			{
				CHTMPText* pItem = new CHTMPText(child);
				pItem->m_pFrame = m_pFrame;
				pItem->BuildWords();
			//	pPElement = pPText;

				pItem->m_pFrame = pThis->m_pFrame;
				pItem->m_parent = pThis;
				pThis->m_childList.AddTail(pItem);
			}
			else if (nodeType == LNODE_ELEMENT)
			{
				CHTMPElement* pItem = NULL;

				CComQIPtr<ILDOMElement> element = child;

				BSTR bnamespaceURI;
				element->get_namespaceURI(&bnamespaceURI);
				_bstr_t namespaceURI = _bstr_t(bnamespaceURI, false);

				BSTR btagName;
				element->get_localName(&btagName);	// Try local name first
				if (SysStringLen(btagName) == 0)
				{
					SysFreeString(btagName);
					element->get_tagName(&btagName);	// Then try full qualified name
				}
				_bstr_t tagName = _bstr_t(btagName, false);

				if (!wcsicmp(tagName, L"block"))
				{
					pItem = new CHTMPElement(node/*, TRUE*/);
				}
				else
					ASSERT(0);

				if (!pItem)	// Unknown tag, create a default inline element
				{
					pItem = new CHTMPElement(node);
				}

				if (pItem)
				{
					pItem->m_pNode = node;
					pItem->m_pFrame = pThis->m_pFrame;
					pItem->m_parent = pThis;
					pThis->m_childList.AddTail(pItem);

					BuildFOTree(pItem, child);
				}
			}

			CComQIPtr<ILDOMNode> nextSibling;
			child->get_nextSibling(&nextSibling);
			child = nextSibling;
		}
#endif
	}

	void Build(ILDOMElement* element)
	{
#if 0
		CComPtr<ILDOMElement> layoutMasterSet = FindByTagNameNS(element, L"http://www.w3.org/1999/XSL/Format", L"layout-master-set", FALSE);
		if (layoutMasterSet)
		{
			m_layoutMasterSet = new CFOLayoutMasterSet;
			m_layoutMasterSet->Build(layoutMasterSet);
		}

		CComPtr<ILDOMNode> node;
		element->get_firstChild(&node);
		while (node)
		{
			CComQIPtr<ILDOMElement> element = node;

			BSTR blocalName;
			element->get_localName(&blocalName);
			_bstr_t localName = _bstr_t(blocalName, false);

			if (!wcscmp(localName, L"page-sequence"))
			{
				BSTR bmasterName;
				element->getAttribute(L"master-name", &bmasterName);
				_bstr_t masterName = _bstr_t(bmasterName, false);

				CFOSimplePageMaster* pSimplePageMaster = m_layoutMasterSet->FindSimplePageMasterByName(masterName);
				ASSERT(pSimplePageMaster);

				CComPtr<ILDOMElement> flow = FindByTagNameNS(element, L"http://www.w3.org/1999/XSL/Format", L"flow", FALSE);
				ASSERT(flow != NULL);

				CFOPage* pPage = new CFOPage;
				pPage->m_width = pSimplePageMaster->GetPageWidth();
				pPage->m_height = pSimplePageMaster->GetPageHeight();
				m_pages.Add(pPage);

				//Flow(flow);
				pPage->m_pElement = new CHTMPElement(flow/*, TRUE*/);
				pPage->m_pElement->m_pFrame = m_pFrame;
				BuildFOTree(pPage->m_pElement, flow);
			}

			CComPtr<ILDOMNode> nextSibling;
			node->get_nextSibling(&nextSibling);
			node = nextSibling;
		}
#endif
	}
};
