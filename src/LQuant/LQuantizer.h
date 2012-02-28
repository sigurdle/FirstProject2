// LQuantizer.h : Declaration of the CLQuantizer

#ifndef __LQUANTIZER_H_
#define __LQUANTIZER_H_

#include "resource.h"       // main symbols

#define JPEG_INTERNALS
#include "jinclude.h"
#include "jpeglib.h"

typedef struct {
  struct jpeg_color_quantizer pub; /* public fields */

  /* Space for the eventually created colormap is stashed here */
  JSAMPARRAY sv_colormap;	/* colormap allocated at init time */
  int desired;			/* desired # of colors = size of colormap */
} my_cquantizer;

typedef my_cquantizer * my_cquantize_ptr;

#if 0

class CQuantize : public CIQuantize
{
protected:
	jpeg_decompress_struct	info;
	LPBYTE* m_in;
	LPBYTE* m_out;
	int m_height;

public:
	CQuantize();
	~CQuantize();

	IMETHOD BOOL SetupQuantizer(ImageDef* pImage, LPBYTE destBits, int destRowBytes, BYTE palette[256][3], int numcolors, int dither_method);
	IMETHOD void CleanupQuantizer();
	IMETHOD void CalculateOptimizedPalette(ImageDef* pImage);
	IMETHOD void StartOptimizePalette();
	IMETHOD void EndOptimizePalette();
	IMETHOD void StartPass2();
	IMETHOD void Quantize2();
	IMETHOD void GetPalette(PixelDef* pPalette);
};

#endif

class CVideoSample;
class CInputPin;
class COutputPin;

#if 0
class ATL_NO_VTABLE CRGBPalette : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ILPalette
{
public:
	CRGBPalette()
	{
		m_bits = NULL;
	}

	LPBYTE m_bits;
	long m_width;
	long m_height;
	long m_rowbytes;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRGBPalette)
	COM_INTERFACE_ENTRY(ILPalette)
END_COM_MAP()

	STDMETHOD(GetCount)(/*[out,retval]*/ long *pVal)
	{
		return S_OK;
	}
	STDMETHOD(Item)(/*[in]*/ long index, /*[out,retval]*/ OLE_COLOR *pVal)
	{
		return S_OK;
	}
};

class ATL_NO_VTABLE CVideoSample : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ILVideoSample
{
public:
	CVideoSample()
	{
		m_bits = NULL;
	}

	LPBYTE m_bits;
	long m_width;
	long m_height;
	long m_rowbytes;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVideoSample)
	COM_INTERFACE_ENTRY(ILVideoSample)
END_COM_MAP()

public:
	STDMETHOD(GetWidth)(long* pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_width;
		return S_OK;
	}

	STDMETHOD(GetHeight)(long* pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_height;
		return S_OK;
	}

	STDMETHOD(LockBits)(LVideoSampleData* pVal)
	{
		pVal->width = m_width;
		pVal->height = m_height;
		pVal->bitcount = 8;
		pVal->rowbytes = m_rowbytes;
		pVal->idata = (LPBYTE)m_bits;

		return S_OK;
	}

	STDMETHOD(UnlockBits)()
	{
		return S_OK;
	}

	STDMETHOD(GetPalette)(ILPalette* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;
		return S_OK;
	}
};
#endif

#define ROWBYTES(width,bitcount)			((((width)*(bitcount)+31) >> 3) & 0xfffc)

/////////////////////////////////////////////////////////////////////////////
// CLQuantizer
class ATL_NO_VTABLE CLQuantizer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLQuantizer, &CLSID_LQuantizer>,
	public IDispatchImpl<ILQuantizer, &IID_ILQuantizer, &LIBID_LQUANTLib>,
	public CLBaseFilterImpl
{
public:
	class COutputPin;

	class ATL_NO_VTABLE CMediaType :
		public CComObjectRootEx<CComSingleThreadModel>,
		public ILVideoMediaType
	{
	public:
		class ATL_NO_VTABLE CPalette :
			public CComObjectRootEx<CComSingleThreadModel>,
			public ILPalette
		{
		public:
			CPalette()
			{
				m_pMediaType = NULL;
			}

			CMediaType* m_pMediaType;

			BEGIN_COM_MAP(CPalette)
				COM_INTERFACE_ENTRY(ILPalette)
			END_COM_MAP()

			STDMETHOD(GetCount)(long *pVal)
			{
				j_decompress_ptr	cinfo = &m_pMediaType->m_pOutput->m_pFilter->info;
				*pVal = cinfo->actual_number_of_colors;
				return S_OK;
			}

			STDMETHOD(Item)(long index, OLE_COLOR* pVal)
			{
				j_decompress_ptr	cinfo = &m_pMediaType->m_pOutput->m_pFilter->info;
				*pVal = RGB(cinfo->colormap[2][index], cinfo->colormap[1][index], cinfo->colormap[0][index]);
				return S_OK;
			}
		};

		CMediaType()
		{
			m_pOutput = NULL;
			m_pPalette = NULL;
		}

		int FinalConstruct()
		{
			CComObject<CPalette>::CreateInstance(&m_pPalette);
			m_pPalette->AddRef();
			m_pPalette->m_pMediaType = this;

			return 0;
		}

		void FinalRelease()
		{
			if (m_pPalette)
			{
				m_pPalette->Release();
				m_pPalette = NULL;
			}
		}

		COutputPin* m_pOutput;

		CComObject<CPalette>* m_pPalette;

		BEGIN_COM_MAP(CMediaType)
			COM_INTERFACE_ENTRY(ILMediaType)
			COM_INTERFACE_ENTRY(ILVideoMediaType)
		END_COM_MAP()

	public:
		STDMETHOD(GetType)(long *pVal)
		{
			*pVal = 1;	// Video
			return S_OK;
		}
		STDMETHOD(GetWidth)(long *pVal)
		{
			*pVal = m_pOutput->m_pFilter->info.output_width;
			return S_OK;
		}
		STDMETHOD(GetHeight)(long *pVal)
		{
			*pVal = m_pOutput->m_pFilter->m_height;
			return S_OK;
		}
		STDMETHOD(GetBitCount)(long *pVal)
		{
			*pVal = 8;	// TODO //m_pFilter->m_bitcount;
			return S_OK;
		}
		STDMETHOD(GetPalette)(ILPalette* *pVal)
		{
			*pVal = m_pPalette;
			if (*pVal) (*pVal)->AddRef();
			return S_OK;
		}
	};

	class ATL_NO_VTABLE CInputPin : 
		public CComObjectRootEx<CComSingleThreadModel>,
		public CLPinImpl,
		public ILMemInputPin
	{
	public:
		class ATL_NO_VTABLE CMemAllocator : 
			public CComObjectRootEx<CComSingleThreadModel>,
			public ILMemAllocator
		{
		public:
			class ATL_NO_VTABLE CVideoSample : 
				public CComObjectRootEx<CComSingleThreadModel>,
				public CLMediaSampleImpl<ILVideoSample>
			{
			public:
				CVideoSample()
				{
					m_bits = NULL;
					m_mediaType = NULL;
				}

				LPBYTE m_bits;
				long m_width;
				long m_height;
				long m_rowbytes;

				ILVideoMediaType* m_mediaType;

			DECLARE_PROTECT_FINAL_CONSTRUCT()

			BEGIN_COM_MAP(CVideoSample)
				COM_INTERFACE_ENTRY(ILMediaSample)
				COM_INTERFACE_ENTRY(ILVideoSample)
			END_COM_MAP()

			public:
				STDMETHOD(LockBits)(LVideoSampleData* pVal)
				{
					pVal->width = m_width;
					pVal->height = m_height;
					pVal->bitcount = 24;
					pVal->rowbytes = m_rowbytes;
					pVal->idata = (LPBYTE)m_bits;

					return S_OK;
				}

				STDMETHOD(UnlockBits)()
				{
					return S_OK;
				}

				STDMETHOD(GetMediaType)(ILMediaType **pVal)
				{
					*pVal = m_mediaType;
					(*pVal)->AddRef();
					return S_OK;
				}
			};

			CMemAllocator()
			{
				m_pInputPin = NULL;
			}

			CInputPin* m_pInputPin;

		DECLARE_PROTECT_FINAL_CONSTRUCT()

		BEGIN_COM_MAP(CMemAllocator)
			COM_INTERFACE_ENTRY(ILMemAllocator)
		END_COM_MAP()

		public:
			STDMETHOD(GetBuffer)(ILMediaSample* *pVal)
			{
				CComObject<CVideoSample>* pSample;
				CComObject<CVideoSample>::CreateInstance(&pSample);
				pSample->AddRef();

				long width;
				long height;
				m_pInputPin->m_mediaType->GetWidth(&width);
				m_pInputPin->m_mediaType->GetHeight(&height);

				pSample->m_mediaType = m_pInputPin->m_mediaType;
				pSample->m_width = width;
				pSample->m_height = height;
				pSample->m_rowbytes = ROWBYTES(width, 24);
				pSample->m_bits = (LPBYTE)GlobalAlloc(0, pSample->m_rowbytes*height);

				*pVal = pSample;

				return S_OK;
			}
		};

		CInputPin()
		{
			m_pFilter = NULL;
			m_pAllocator = NULL;
		}

		int FinalConstruct()
		{
			CComObject<CMemAllocator>::CreateInstance(&m_pAllocator);
			m_pAllocator->AddRef();
			m_pAllocator->m_pInputPin = this;

			return 0;
		}

		void FinalRelease()
		{
			if (m_pAllocator)
			{
				m_pAllocator->Release();
				m_pAllocator = NULL;
			}
		}

		CLQuantizer* m_pFilter;
		CComPtr<ILVideoMediaType> m_mediaType;
		CComObject<CMemAllocator>* m_pAllocator;

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CInputPin)
		COM_INTERFACE_ENTRY(ILPin)
		COM_INTERFACE_ENTRY(ILMemInputPin)
	END_COM_MAP()

		STDMETHOD(ReceiveConnection)(ILPin *pConnector, ILMediaType* pMediaType);

		STDMETHOD(QueryFilter)(ILBaseFilter* *pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = m_pFilter;
			(*pVal)->AddRef();
			return S_OK;
		}

	// ILMemInputPin
		STDMETHOD(GetAllocator)(ILMemAllocator* *ppAllocator)
		{
			if (ppAllocator == NULL) return E_POINTER;

			/*
			//*ppAllocator = NULL;

			CComQIPtr<ILMemInputPin> memInput = m_pFilter->m_pOutput->m_connectedTo;
			
			return memInput->GetAllocator(ppAllocator);
			*/

			*ppAllocator = m_pAllocator;
			(*ppAllocator)->AddRef();
			return S_OK;
		}

		STDMETHOD(Receive)(ILMediaSample *pSample);
		STDMETHOD(EndOfStream)();
	};

	class ATL_NO_VTABLE COutputPin : 
		public CComObjectRootEx<CComSingleThreadModel>,
		public CLPinImpl
	{
	public:
		COutputPin()
		{
			m_pFilter = NULL;
			m_sample = NULL;
			m_pMediaType = NULL;
		}

		CLQuantizer* m_pFilter;

		CComPtr<ILVideoSample> m_sample;

		CComPtr<ILMemAllocator> m_allocator;

		CComObject<CMediaType>* m_pMediaType;

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(COutputPin)
		COM_INTERFACE_ENTRY(ILPin)
	END_COM_MAP()

		STDMETHOD(QueryFilter)(ILBaseFilter* *pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = m_pFilter;
			(*pVal)->AddRef();
			return S_OK;
		}

		STDMETHOD(Connect)(ILPin* pReceivePin, ILMediaType* mediaType)
		{
			if (pReceivePin == NULL) return E_POINTER;
			if (m_connectedTo != NULL) return E_UNEXPECTED;	// Already connected

			CComQIPtr<ILMemInputPin> memInput = pReceivePin;
			if (memInput)
			{
				memInput->GetAllocator(&m_allocator);
			}

			HRESULT hr = pReceivePin->ReceiveConnection(this, m_pMediaType);
			if (SUCCEEDED(hr))
			{
				m_connectedTo = pReceivePin;
			}

			return hr;
		}
	};

	CLQuantizer()
	{
		m_pInput = NULL;
		m_pOutput = NULL;

		m_in = NULL;
		m_out = NULL;
	}

	int FinalConstruct()
	{
		CComObject<CInputPin>::CreateInstance(&m_pInput);
		m_pInput->m_pFilter = this;
		AddPin(m_pInput);

		CComObject<COutputPin>::CreateInstance(&m_pOutput);
		m_pOutput->m_pFilter = this;
		AddPin(m_pOutput);

		return 0;
	}

	void FinalRelease()
	{
		CLBaseFilterImpl::FinalRelease();
	}

	jpeg_decompress_struct	info;
	LPBYTE* m_in;
	LPBYTE* m_out;
	int m_height;

	CComPtr<ILVideoSample> m_insample;

	CComObject<CVideoSample>* m_pOutputSample;

	CComObject<CInputPin>* m_pInput;
	CComObject<COutputPin>* m_pOutput;

	BOOL SetupQuantizer(ILVideoSample * pImage, BYTE palette[256][3], int numcolors, int dither_method);

DECLARE_REGISTRY_RESOURCEID(IDR_LQUANTIZER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLQuantizer)
	COM_INTERFACE_ENTRY(ILQuantizer)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ILMediaFilter)
	COM_INTERFACE_ENTRY(ILBaseFilter)
END_COM_MAP()

// ILQuantizer
public:
};

#endif //__LQUANTIZER_H_
