// LXSLTemplate.cpp : Implementation of CLXSLTemplate
#include "stdafx.h"
#include "LXML.h"
#include "LXSLTemplate.h"

#include "LXSLProcessor.h"

/////////////////////////////////////////////////////////////////////////////
// CLXSLTemplate


#if 0
MSXML2::IXMLDOMNodePtr Build(MSXML2::IXMLDOMDocument2Ptr msdocument, ILDOMNode* node);
#endif

STDMETHODIMP CLXSLTemplate::get_stylesheet(ILDOMNode **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_stylesheet;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CLXSLTemplate::putref_stylesheet(ILDOMNode *newVal)
{
	m_stylesheet = newVal;

#if 0
	MSXML2::IXMLDOMDocument2Ptr msdocument(L"Msxml2.FreeThreadedDOMDocument.4.0");
	m_msstylesheet = Build(msdocument, m_stylesheet);

	MSXML2::IXMLDOMElementPtr msoutput = msdocument->createNode(_variant_t((long)1), _bstr_t(L"output"), _bstr_t(L"http://www.w3.org/1999/XSL/Transform"));
	msoutput->setAttribute(_bstr_t(L"method"), _bstr_t(L"xml"));

	if (msdocument->documentElement->firstChild != NULL)
		msdocument->documentElement->insertBefore(msoutput, _variant_t((IDispatch*)msdocument->documentElement->firstChild));
	else
		msdocument->documentElement->appendChild(msoutput);

//	MessageBox(NULL, m_msstylesheet->xml, "", MB_OK);

	m_mstemplate->stylesheet = m_msstylesheet;
#endif
	return S_OK;
}

STDMETHODIMP CLXSLTemplate::createProcessor(ILXSLProcessor **pVal)
{
	CComObject<CLXSLProcessor>* pProcessor;
	CComObject<CLXSLProcessor>::CreateInstance(&pProcessor);
	if (pProcessor)
	{
		pProcessor->AddRef();
		pProcessor->m_ownerTemplate = this;
#if 0
		pProcessor->m_msprocessor = m_mstemplate->createProcessor();
#endif
		*pVal = pProcessor;
	}

	return S_OK;
}
