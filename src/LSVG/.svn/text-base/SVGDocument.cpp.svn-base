#include "stdafx.h"
#include "LSVG2.h"
#include "SVGDocument.h"

#include "SVGSVGElement.h"

namespace System
{
namespace Web
{

SVGDocument::SVGDocument()
{
//	m_viewCSS = new ViewCSS;
//	m_viewCSS->m_document = this;
}

SVGDocument::~SVGDocument()
{
}

// static
ImmutableString<WCHAR> SVGDocument::s_namespaceURI(L"http://www.w3.org/2000/svg");

String SVGDocument::get_namespaceURI()
{
	return &s_namespaceURI;
}

SVGSVGElement* SVGDocument::get_rootElement()
{
	return dynamic_cast<SVGSVGElement*>(get_documentElement());
}

}	// Web
}	// System
