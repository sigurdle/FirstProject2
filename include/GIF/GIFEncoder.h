// GIFEncoder.h : Declaration of the CGIFEncoder

#ifndef __GIFENCODER_H_
#define __GIFENCODER_H_

//#include "resource.h"       // main symbols

#include "giffmt.h"

typedef SHORT	INT16;
//typedef LONG	INT32;

#define	MAX_LZW_BITS	12	/* maximum LZW code size (4096 symbols) */

typedef INT16 code_int;		/* must hold -1 .. 2**MAX_LZW_BITS */

#define LZW_TABLE_SIZE	((code_int) 1 << MAX_LZW_BITS)

#define HSIZE		5003	/* hash table size for 80% occupancy */

typedef int hash_int;		/* must hold -2*HSIZE..2*HSIZE */

#define MAXCODE(n_bits)	(((code_int) 1 << (n_bits)) - 1)


/*
 * The LZW hash table consists of two parallel arrays:
 *   hash_code[i]	code of symbol in slot i, or 0 if empty slot
 *   hash_value[i]	symbol's value; undefined if empty slot
 * where slot values (i) range from 0 to HSIZE-1.  The symbol value is
 * its prefix symbol's code concatenated with its suffix character.
 *
 * Algorithm:  use open addressing double hashing (no chaining) on the
 * prefix code / suffix character combination.  We do a variant of Knuth's
 * algorithm D (vol. 3, sec. 6.4) along with G. Knott's relatively-prime
 * secondary probe.
 *
 * The hash_value[] table is allocated from FAR heap space since it would
 * use up rather a lot of the near data space in a PC.
 */

typedef INT32 hash_entry;	/* must hold (code_int<<8) | byte */

#define HASH_ENTRY(prefix,suffix)  ((((hash_entry) (prefix)) << 8) | (suffix))

//////////
#define ROWBYTES(width,bitcount)			((((width)*(bitcount)+31) >> 3) & 0xfffc)

/////////////////////////////////////////////////////////////////////////////
// CGIFEncoder
class ATL_NO_VTABLE CGIFEncoder : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGIFEncoder, &CLSID_GIFEncoder>,
	public IDispatchImpl<IGIFEncoder, &IID_IGIFEncoder, &LIBID_GIFLib>,

	public CLBaseFilterImpl
{
public:
	BYTE	InitCodeSize;
	int n_bits;			/* current number of bits/code */
	code_int maxcode;		/* maximum code, given n_bits */
	int init_bits;		/* initial n_bits ... restored after clear */
	INT32 cur_accum;		/* holds bits not yet output */
	int cur_bits;			/* # of bits in cur_accum */

	  /* LZW string construction */
	code_int waiting_code;	/* symbol not yet output; may be extendable */
	BOOL first_byte;		/* if TRUE, waiting_code is not valid */

	  /* State for LZW code assignment */
	code_int ClearCode;		/* clear code (doesn't change) */
	code_int EOFCode;		/* EOF code (ditto) */
	code_int free_code;		/* first not-yet-used symbol code */

	  /* LZW hash table */
	code_int *hash_code;		/* => hash table of symbol codes */
	hash_entry FAR *hash_value;	/* => hash table of symbol values */

	  /* GIF data packet construction buffer */
	int bytesinpkt;		/* # of bytes in current packet */
	char packetbuf[256];		/* workspace for accumulating packet */

	void ClearMembers()
	{
		InitCodeSize = 0;
		n_bits = 0;
		maxcode = 0;
		init_bits = 0;
		cur_accum = 0;
		cur_bits = 0;

		  /* LZW string construction */
		waiting_code = 0;
		first_byte = 0;

		  /* State for LZW code assignment */
		ClearCode = 0;		/* clear code (doesn't change) */
		EOFCode = 0;		/* EOF code (ditto) */
		free_code = 0;		/* first not-yet-used symbol code */

		  /* LZW hash table */
		hash_code = NULL;		/* => hash table of symbol codes */
		hash_value = NULL;	/* => hash table of symbol values */

		  /* GIF data packet construction buffer */
		bytesinpkt = 0;		/* # of bytes in current packet */
		memset(packetbuf, 0, sizeof(packetbuf));		/* workspace for accumulating packet */
	}

	void flush_packet ();
	void output (code_int code);
	void clear_hash ();
	void clear_block ();
	void compress_init (int i_bits);
	void compress_byte (int c);
	void compress_term ();

public:
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
					pVal->bitcount = 8;
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
				m_pInputPin->m_videoType->GetWidth(&width);
				m_pInputPin->m_videoType->GetHeight(&height);

				pSample->m_mediaType = m_pInputPin->m_videoType;
				pSample->m_width = width;
				pSample->m_height = height;
				pSample->m_rowbytes = ROWBYTES(width, 8);
				pSample->m_bits = (LPBYTE)GlobalAlloc(0, pSample->m_rowbytes*height);

				*pVal = pSample;

				return S_OK;
			}
		};

		CInputPin()
		{
			m_direction = LPINDIR_INPUT;
			m_pFilter = NULL;
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

		CGIFEncoder* m_pFilter;
		CComQIPtr<ILVideoMediaType> m_videoType;
		CComObject<CMemAllocator>* m_pAllocator;

		GIFSCREENDESCR	m_gsd;

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CInputPin)
		COM_INTERFACE_ENTRY(ILPin)
		COM_INTERFACE_ENTRY(ILMemInputPin)
	END_COM_MAP()

	public:
		STDMETHOD(QueryFilter)(ILBaseFilter* *pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = m_pFilter;
			(*pVal)->AddRef();
			return S_OK;
		}

		STDMETHOD(ReceiveConnection)(ILPin* pConnector, ILMediaType* pMediaType);

	// ILMemInputPin
		STDMETHOD(GetAllocator)(ILMemAllocator* *ppAllocator)
		{
			if (ppAllocator == NULL) return E_POINTER;

			*ppAllocator = NULL;

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
			m_direction = LPINDIR_OUTPUT;
			m_pFilter = NULL;
		}

		int FinalConstruct()
		{
			return 0;
		}

		void FinalRelease()
		{
		}

		CGIFEncoder* m_pFilter;

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(COutputPin)
		COM_INTERFACE_ENTRY(ILPin)
	END_COM_MAP()

	public:
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

			m_connectedTo = pReceivePin;
			CComQIPtr<ISequentialStream> stream = m_connectedTo;
			if (stream == NULL)
				return E_FAIL;

			HRESULT hr = pReceivePin->ReceiveConnection(this, mediaType);

			m_pFilter->m_stream = stream;

			return hr;
		}
	};

	CGIFEncoder()
	{
		m_pInput = NULL;
		m_pOutput = NULL;
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

	CComObject<CInputPin>* m_pInput;
	CComObject<COutputPin>* m_pOutput;

	CComPtr<ISequentialStream> m_stream;

	CComPtr<ILVideoSample> m_prevSample;

	long m_currentFrame;

///////
	void PutScreenHeader();
	void CalcBounds(ILVideoSample* sample, GIFIMAGEDESCR *gid);
	void PutImageBlock(ILVideoSample* sample, BYTE bInterlaced);
	LONG PutControlBlock(ILVideoSample* sample);
	LONG PutLoopBlock(WORD iterations);
	LONG PutCommentBlock(LPTSTR comment);

	ULONG WriteB(BYTE c)
	{
		ULONG cbWritten;
		m_stream->Write(&c, 1, &cbWritten);
		return cbWritten;
	}

	ULONG Write(void* data, ULONG len)
	{
		ULONG cbWritten;
		m_stream->Write(data, len, &cbWritten);
		return cbWritten;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_GIFENCODER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGIFEncoder)
	COM_INTERFACE_ENTRY(IGIFEncoder)
	COM_INTERFACE_ENTRY(ILMediaFilter)
	COM_INTERFACE_ENTRY(ILBaseFilter)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IGIFEncoder
public:
};

#endif //__GIFENCODER_H_
