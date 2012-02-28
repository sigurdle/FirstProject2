#ifndef __LJPEGDECODER_H_
#define __LJPEGDECODER_H_

//#include "resource.h"       // main symbols

#include "JFIF.h"

namespace System
{
namespace MediaShow
{

class JPEGDecoder : 
	public BaseFilterImpl	// IMediaFilter
{
public:
	class CInputPin : 
		public BasePinImpl
	{
	public:
		CInputPin() : BasePinImpl(PINDIR_INPUT)
		{
		}

		inline JPEGDecoder* GetFilter() const
		{
			return (JPEGDecoder*)m_pFilter;
		}

		ByteStreamWrapper* m_stream;

//		float *QT[4]; // quantization tables, no more than 4 quantization tables (QT[0..3])
//		Huffman_table HTDC[4]; //DC huffman tables , no more than 4 (0..3)
//		Huffman_table HTAC[4]; //AC huffman tables                  (0..3)

//		void load_Huffman_table(Huffman_table *HT);
//		void process_Huffman_data_unit(BYTE DC_nr, BYTE AC_nr, short *previous_DC);
/*
	// SOF0
		int YH;
		int YV;
	//	int YQ_nr;

		int CbH;
		int CbV;
	//	int CbQ_nr;

		int CrH;
		int CrV;
	//	int CrQ_nr;

		BYTE YQ_nr,CbQ_nr,CrQ_nr; // quantization table number for Y, Cb, Cr
		BYTE YDC_nr,CbDC_nr,CrDC_nr; // DC Huffman table number for Y,Cb, Cr
		BYTE YAC_nr,CbAC_nr,CrAC_nr; // AC Huffman table number for Y,Cb, Cr

	//	DWORD wordval; // the actual used value in Huffman decoding.

		short DCY, DCCb, DCCr; // Coeficientii DC pentru Y,Cb,Cr
		short DCT_coeff[64]; // Current DCT_coefficients
		BYTE Y[64],Cb[64],Cr[64]; // Y, Cb, Cr of the current 8x8 block for the 1x1 case
		BYTE Y_1[64],Y_2[64],Y_3[64],Y_4[64];
		BYTE tab_1[64],tab_2[64],tab_3[64],tab_4[64]; // tabelele de supraesantionare pt cele 4 blocuri
*/
//		WORD lookKbits(BYTE k);
//		void skipKbits(BYTE k);
//		short getKbits(BYTE nbits);
//		short get_svalue(BYTE nbits);

//		void decode_MCU_1x1(DWORD im_loc);
//		void decode_MCU_2x1(DWORD im_loc);
//		void decode_MCU_1x2(DWORD im_loc);
//		void decode_MCU_2x2(DWORD im_loc);

//		void calculate_tabs();

//		void IDCT_transform(short *incoeff, BYTE *outcoeff,BYTE Q_nr);

//		int d_k;
//		WORD w1, w2;
//		DWORD wordval;

//		BOOL resync();

//		int Restart_markers;
//		WORD MCU_restart;

//		WORD X_round,Y_round; // The dimensions rounded to multiple of Hmax*8 (X_round)
				  // and Ymax*8 (Y_round)

//		WORD Hmax,Vmax;

//		BYTE *im_buffer; // RGBA image buffer
//		DWORD X_image_bytes; // size in bytes of 1 line of the image = X_round * 4
//		DWORD y_inc_value ; // 32*X_round; // used by decode_MCU_1x2,2x1,2x2

//		ErrorCode ReadImage(LSampleData* sampledata);


	//	ErrorCode ReadHeader();
		ErrorCode ReadImage(IMediaSample* sample);
//		void block(short* f, BYTE c);

		virtual ErrorCode CheckConnect(IPin* pPin)
		{
			// Call base class first
			ErrorCode hr = BasePinImpl::CheckConnect(pPin);
			if (hr < 0) return hr;

			IByteData* stream = dynamic_cast<IByteData*>(pPin);
			if (stream == NULL) return Error_NoInterface;

			m_stream = new ByteStreamWrapper(stream);

			return Success;
		}

		virtual void BreakConnect()
		{
			// Release what we obtained in CheckConnect
			m_stream = NULL;
		}

		virtual ErrorCode CheckMediaType(MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Stream)
				return Error;

			return Success;
		}

		virtual ErrorCode CompleteConnect(IPin *pPin);
	};

	class COutputPin :
		public BaseOutputPinImpl
		//public ILMediaSeeking
	{
	public:
		COutputPin()
		{
		//	m_pFilter = NULL;

	//		m_threadId = 0;
	//		m_hThread = NULL;
		}

	//	JPEGDecoder* m_pFilter;

		//WAVEFORMATEX m_wfx;
		//int m_compression;

		//DWORD m_threadId;
		//HANDLE m_hThread;

		virtual ErrorCode CheckMediaType(MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Video)
				return Error;

			return Success;
		}

		virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType);

		virtual ErrorCode Run(LONGLONG tStart);

		//static DWORD WINAPI AudioRunProc(LPVOID lpParameter);

		inline JPEGDecoder* GetFilter() const
		{
			return (JPEGDecoder*)m_pFilter;
		}

#if 0
	// ILMediaSeeking
		STDMETHOD(Seek)(LONGLONG t)
		{
			ATLASSERT(0);
			return E_NOTIMPL;
		}
		STDMETHOD(GetDuration)(LONGLONG* pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = 0;
			return S_OK;
		}
		STDMETHOD(GetCurrentPosition)(LONGLONG* pVal)
		{
			ATLASSERT(0);
			return E_NOTIMPL;
		}
#endif
	};

	JPEGDecoder()
	{
		m_pInputPin = NULL;
		m_pOutputPin = NULL;

		m_pInputPin = new CInputPin;
		m_pInputPin->m_pFilter = this;
		m_pInputPin->m_id = WSTR("Stream Input");
		AddPin(m_pInputPin);

		m_pOutputPin = new COutputPin;
		m_pOutputPin->m_pFilter = this;
		m_pOutputPin->m_id = WSTR("Image Output");
		AddPin(m_pOutputPin);

		m_jfif = NULL;
	}

	~JPEGDecoder()
	{
		delete m_jfif;
	}

	Imaging::JPEGDecoder* m_jfif;

	CInputPin* m_pInputPin;
	COutputPin* m_pOutputPin;
};

}	// LMedia
}

#endif //__LJPEGDECODER_H_
