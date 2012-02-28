#include "stdafx.h"

#if 0
#include "HTML2.h"
#include "PreviewItem.h"

//ILDOMElement* getElementById(ILDOMElement* p, BSTR name);

//virtual
void CHTMPSpan::BuildTree(CHTMFrame* pFrame, ILDOMElement* pNode)
{
	CComQIPtr<ILHTMLElement> element = m_pNode;

	BSTR datasrc; element->getAttribute(L"datasrc", &datasrc);
	if (datasrc)
	{
		if (datasrc[0] == L'#')
		{
			_bstr_t datasrcid = datasrc + 1;

			CComQIPtr<ILDOMDocument> document;
			element->get_ownerDocument(&document);

			//CComQIPtr<ILDOMElement> documentElement;
			//document->get_documentElement(&documentElement);

			CComQIPtr<ILDOMElement> datasrcElement;
			document->getElementById(/*documentElement, */datasrcid, &datasrcElement);
			if (datasrcElement)
			{
				BSTR tagName;
				datasrcElement->get_tagName(&tagName);
				if (!wcsicmp(tagName, L"object"))
				{
					ASSERT(0);
					/*
					CHTMPObject* pObject;
					datasrcElement->GetNProp(L"pelement", (DWORD*)&pObject);
					if (pObject->m_pControl)
					{
						CComPtr<IUnknown> datasrcunk = pObject->m_pControl->GetDataSourceUnknown();
						if (datasrcunk)
						{
							CComQIPtr<OLEDBSimpleProvider> odbsp;
							datasrcunk->QueryInterface(IID_OLEDBSimpleProvider, (void**)&odbsp);
							if (odbsp != NULL)
							{
							}
						}
					}
					*/
				}

				SysFreeString(tagName);
			}
		}

		SysFreeString(datasrc);
	}
	else
	{
		ASSERT(0);
		//CHTMPElement::BuildTree(pFrame, pNode);
	}
}

//virtual
void CHTMPSpan::CalculateDimensions(CHTMCalcContext* pC)
{
	CComQIPtr<ILHTMLElement> element = m_pNode;

/*
	BSTR datasrc; element->getAttribute(L"datasrc", &datasrc);
	if (datasrc)
	{
*/

	CHTMPElement::CalculateDimensions(pC);
}

//virtual
void CHTMPSpan::Draw(CHTMRenderContext* pC)
{
	CHTMPElement::Draw(pC);
}

#endif