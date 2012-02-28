#ifndef w3c_GenericDocument_h
#define w3c_GenericDocument_h

#include "DOMDocumentEvent.h"
#include "LDOMDocumentRangeImpl.h"
#include "DOMEventTargetImpl.h"
#include "DocumentASImpl.h"
#include "DocumentEditVALImpl.h"

namespace System
{
namespace Web
{

class WEBEXT GenericDocument : 
	public Document,
	public EventTarget,
	public DocumentEvent,
	public DocumentRangeImpl<GenericDocument>,
	public IDocumentCSS,
//	public DocumentCSSImpl<GenericDocument>,
//	public DocumentViewImpl<GenericDocument>,
	/*
	public CLDocumentASImpl<GenericDocument>,
	public CLDocumentEditVALImpl<GenericDocument>,
	*/
	public XPath::XPathEvaluator//Impl<GenericDocument>,
{
public:
	CTOR GenericDocument();

	Style::IStyleSheetList* get_styleSheets()	// IDocumentStyle
	{
		return Document::get_styleSheets();
	}

	virtual Style::ICSSStyleDeclaration* getOverrideStyle(Element* elt, StringIn pseudoElt)	// IDocumentCSS
	{
		return Document::getOverrideStyle(elt, pseudoElt);
	}

};

}	// Web
}

#endif // w3c_GenericDocument_h
