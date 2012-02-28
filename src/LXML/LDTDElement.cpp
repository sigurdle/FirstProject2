#include "stdafx.h"
#include "LXML2.h"

#include "LDTDElement.h"

#include "DTDParser.h"

namespace System
{
namespace Web
{

CLDTDElement::CLDTDElement()
{
	m_pDTDDocument = nullptr;
	m_pCPChoiceSeq = nullptr;

#if 0
	m_pASElement = NULL;
#endif
//	m_isPCDataOnly = FALSE;
	m_contentType = (ASContentModelType)0;	// Undefined
}

CLDTDElement::~CLDTDElement()
{
	if (m_pCPChoiceSeq)
	{
		delete m_pCPChoiceSeq;
		m_pCPChoiceSeq = nullptr;
	}
}

/*
STDMETHODIMP CLDTDElement::get_nodeType(LDOMNodeType *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = DTD_ELEMENT;
	return S_OK;
}
*/

String CLDTDElement::get_name() const
{
	return m_name;
}

void CLDTDElement::set_name(StringIn name)
{
	m_name = name;
}

}	// Web
}	// System
