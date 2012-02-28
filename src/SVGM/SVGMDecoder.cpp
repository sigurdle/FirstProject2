// SVGMDecoder.cpp : Implementation of CSVGMDecoder
#include "stdafx.h"
#include "SVGM.h"
#include "SVGMDecoder.h"

/////////////////////////////////////////////////////////////////////////////
// CSVGMDecoder

// ILMediaLoader
STDMETHODIMP CSVGMDecoder::Open(IStream *stream)
{
	CComPtr<ILDOMBuilder> builder;
	builder.CoCreateInstance(CLSID_LDOMBuilder);

//	builder->parseStream(stream);

	return S_OK;
}

// ILVideo
STDMETHODIMP CSVGMDecoder::GetWidth(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = 0;//m_ihdr.Width;
	return S_OK;
}

STDMETHODIMP CSVGMDecoder::GetHeight(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = 0;//m_ihdr.Height;
	return S_OK;
}

STDMETHODIMP CSVGMDecoder::SetDocument(IUnknown *document)
{
	m_document = document;

	if (m_document)
	{
		CComQIPtr<ILDOMDocumentView> documentView = m_document;

		CComPtr<ILDOMAbstractView> view;
		documentView->createView(&view);
		m_view = view;
	}

	return S_OK;
}

// ILMediaSeeking
STDMETHODIMP CSVGMDecoder::Seek(double seconds)
{
	if (m_document)
	{
		CComPtr<ILDOMElement> documentElement;
		m_document->get_documentElement(&documentElement);

		CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;
		if (svgsvgElement)
		{
			svgsvgElement->setCurrentTime(seconds);
		}
	}

	return S_OK;
}

STDMETHODIMP CSVGMDecoder::GetDuration(double* pVal)
{
	return S_OK;
}
