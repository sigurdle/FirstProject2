#include "stdafx.h"
#include "PageDesigner.h"

#if 0
#include "ObjectMap.h"
#include "PDDocument.h"
#include "PDSpread.h"
#include "PDPage.h"
#include "PDLayer.h"
#include "PDObjectGroup.h"
#include "PDGuides.h"

/////////////////////////
// CPDSpread

HRESULT CPDSpread::FinalConstruct()
{
	CPDSpreadImpl<IPDSpread>::FinalConstruct();
	return S_OK;
}

void CPDSpread::FinalRelease()
{
	CPDSpreadImpl<IPDSpread>::FinalRelease();
}

STDMETHODIMP CPDSpread::saveAsXML(/*[in]*/ IDOMDocument* document, /*[in]*/ IDOMNode* node)
{
	CComQIPtr<IDOMElement> element = node;
	if (element)
	{
		WCHAR str[256];

		swprintf(str, L"%d", m_spine);
		element->setAttribute(L"spine", str);

		// Pages
		{
			CComPtr<IDOMElement> elementPages;
			document->createElement(L"pages", &elementPages);

			element->appendChild(elementPages, NULL);

			for (int i = 0; i < m_pages->m_items.GetSize(); i++)
			{
				CPDPage* pPage = (CPDPage*)m_pages->m_items[i];

				CComPtr<IDOMElement> elementPage;
				document->createElement(L"page", &elementPage);

				//pPage->saveAsXML(document, elementPage);

				elementPages->appendChild(elementPage, NULL);
			}
		}

		// Layergroups
		{
			CComPtr<IDOMElement> elementLayers;
			document->createElement(L"layergroups", &elementLayers);

			element->appendChild(elementLayers, NULL);

			for (int i = 0; i < m_layergroups->m_items.GetSize(); i++)
			{
				CPDObjectGroup* pGroup = (CPDObjectGroup*)m_layergroups->m_items[i];

				CComPtr<IDOMElement> elementGroup;
				document->createElement(L"layergroup", &elementGroup);
				if (elementGroup)
				{
					pGroup->saveAsXML(document, elementGroup, TRUE);

					elementLayers->appendChild(elementGroup, NULL);
				}
			}
		}

		return S_OK;
	}
	else
		return E_FAIL;
}

IDOMElement* FindByTagName(IDOMElement* parent, BSTR tagName, BOOL bDeep = TRUE);

STDMETHODIMP CPDSpread::loadXML(IDOMNode *node)
{
	CComQIPtr<IDOMElement> element = node;
	if (element)
	{
		{
			BSTR bstr;

			element->getAttribute(L"spine", &bstr);
			m_spine = atol(_bstr_t(bstr, false));
		}

		CComPtr<IDOMElement> elementPages = FindByTagName(element, L"pages", FALSE);
		if (elementPages)
		{
			CComPtr<IDOMNode> child;
			elementPages->get_firstChild(&child);
			while (child)
			{
				CComQIPtr<IDOMElement> elementPage = child;
				if (elementPage)
				{
					CComObject<CPDPage>* pPage;
					CComObject<CPDPage>::CreateInstance(&pPage);
					if (pPage)
					{
						pPage->AddRef();

						pPage->m_pDocument = m_pDocument;
						pPage->m_ownerSpread = this;

						pPage->AddRef();
						m_pages->m_items.Add(pPage);

						pPage->AddRef();
						m_pDocument->m_pages->m_items.Add(pPage);

						pPage->Release();
					}
				}

				CComPtr<IDOMNode> nextSibling;
				child->get_nextSibling(&nextSibling);
				child = nextSibling;
			}
		}

		CComPtr<IDOMElement> elementLayergroups = FindByTagName(element, L"layergroups", FALSE);
		if (elementLayergroups)
		{
			int ngroup = 0;
			CComPtr<IDOMNode> child;
			elementLayergroups->get_firstChild(&child);
			while (child)
			{
				CComQIPtr<IDOMElement> elementLayergroup = child;
				if (elementLayergroup)
				{
					CComObject<CPDObjectGroup>* pGroup;
					CComObject<CPDObjectGroup>::CreateInstance(&pGroup);

					if (pGroup)
					{
						pGroup->AddRef();

						pGroup->m_spread = this;
						pGroup->m_pDocument = m_pDocument;
						pGroup->m_layer = (CPDLayer*)m_pDocument->m_layers->m_items[ngroup];

						HRESULT hr = pGroup->loadXML(elementLayergroup);
						if (FAILED(hr))
							return hr;

						pGroup->AddRef();
						m_layergroups->m_items.Add(pGroup);
					}

					pGroup->Release();
				}

				CComPtr<IDOMNode> nextSibling;
				child->get_nextSibling(&nextSibling);
				child = nextSibling;

				ngroup++;
			}
		}
	}

	return S_OK;
}

#endif