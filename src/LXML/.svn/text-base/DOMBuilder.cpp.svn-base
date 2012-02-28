#include "stdafx.h"
#include "LXML.h"
#include "DOMBuilder.h"

#include "DOMParser.h"

namespace System
{
namespace Web
{

/////////////////////////////////////////////////////////////////////////////
// CLLSParser

#if 0
STDMETHODIMP CLLSParser::parseURI(BSTR uri, ILDOMDocument **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CDOMParser parser;
	parser.m_errorHandler = m_errorHandler;

	bool success;
	parser.load(CComVariant(uri), &success);

	*pVal = parser.m_document;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CLLSParser::parseTextData(ITextData *textData, ILDOMDocument **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CDOMParser parser;

	parser.m_errorHandler = m_errorHandler;
	parser.m_textDoc = textData;
	parser.loadXML2();

	*pVal = parser.m_document;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

#if 0
STDMETHODIMP CLLSParser::parseASURI(BSTR uri, BSTR schemaType, IASModel **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComPtr<IASDTDModel> model;
	model.CoCreateInstance(L"ASDTDMod.ASDTDModel");
	if (model)
	{
		bool success;
		model->load(uri, &success);

		*pVal = model;
		(*pVal)->AddRef();
	}

	return S_OK;
}
#endif

STDMETHODIMP CLLSParser::get_errorHandler(ILDOMErrorHandler **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_errorHandler;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CLLSParser::set_errorHandler(ILDOMErrorHandler *newVal)
{
	m_errorHandler = newVal;
	return S_OK;
}
#endif

}	// Web
}
