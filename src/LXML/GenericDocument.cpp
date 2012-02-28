#include "stdafx.h"
#include "LXML2.h"
#include "GenericDocument.h"

namespace System
{
namespace Web
{

GenericDocument::GenericDocument()
{
}

#if 0
void GenericDocument::elementDone(IDOMElement* element)
{
	BSTR btagName;
	element->get_tagName(&btagName);
	_bstr_t tagName = _bstr_t(btagName);
	if (!wcsicmp(tagName, L"style"))
	{
		CComQIPtr<IDOMNode> child;
		element->get_firstChild(&child);

		CComQIPtr<IDOMText> text = child;
		if (text)
		{
			BSTR btextdata;
			text->get_data(&btextdata);
			_bstr_t textdata = _bstr_t(btextdata, false);

			CComQIPtr<IDOMCSSStyleSheet> stylesheet;
			stylesheet.CoCreateInstance(CLSID_DOMCSSStyleSheet);

			CComQIPtr<IDocumentStyle> documentStyle = GetControllingUnknown();
			if (documentStyle)
			{
				CComQIPtr<IStyleSheetList> stylesheetList;
				documentStyle->get_styleSheets(&stylesheetList);

				stylesheetList->append(stylesheet);

				CComQIPtr<IHTMLStyleSheet> htmlstylesheet = stylesheet;
				htmlstylesheet->set_cssText(textdata);	// The stylesheet will parse the text
			}
		}
	}
}
#endif

}	// w3c
}
