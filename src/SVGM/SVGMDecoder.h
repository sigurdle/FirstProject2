// SVGMDecoder.h : Declaration of the CSVGMDecoder

#ifndef __SVGMDECODER_H_
#define __SVGMDECODER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSVGMDecoder
class ATL_NO_VTABLE CSVGMDecoder : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSVGMDecoder, &CLSID_SVGMDecoder>,
	public ISVGMDecoder,
	public ILMediaLoader,
	public ILVideo,
	public ILMediaSeeking
{
public:
	CSVGMDecoder()
	{
	}

	CComPtr<IStream> m_stream;
	CComPtr<ILVideoSample> m_sample;

	CComQIPtr<ILDOMDocument> m_document;

	CComQIPtr<ILHTMLWindow> m_view;

DECLARE_REGISTRY_RESOURCEID(IDR_SVGMDECODER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSVGMDecoder)
	COM_INTERFACE_ENTRY(ISVGMDecoder)
	COM_INTERFACE_ENTRY(ILMediaLoader)
	COM_INTERFACE_ENTRY(ILVideo)
	COM_INTERFACE_ENTRY(ILMediaSeeking)
END_COM_MAP()

// ISVGMDecoder
public:
	STDMETHOD(SetDocument)(/*[in]*/ IUnknown* document);
// ILMediaLoader
	STDMETHOD(Open)(IStream *stream);

	STDMETHOD(GetStreamType)(LStreamType *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = LStreamType_Video;
		return S_OK;
	}

	STDMETHOD(EnumStreams)(IEnumUnknown* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;
		return S_OK;
	}
	STDMETHOD(GetVideo)(ILVideo* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = this;
		(*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(GetAudio)(ILAudio* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;
		return S_OK;
	}
// ILVideo
	STDMETHOD(GetWidth)(long *pVal);
	STDMETHOD(GetHeight)(long *pVal);
	STDMETHOD(GetSample)(ILVideoSample* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_sample;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}

	STDMETHOD(SetSample)(ILVideoSample* newVal)
	{
		return S_OK;
	}

// ILMediaSeeking
	STDMETHOD(Seek)(double seconds);
	STDMETHOD(GetDuration)(double* pVal);

};

#endif //__SVGMDECODER_H_
