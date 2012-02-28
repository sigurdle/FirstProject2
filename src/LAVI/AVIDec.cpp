#include "stdafx.h"
#include "LAVI.h"
#include "AVIDec.h"

#if 0
#include "C:\\DevDownloads\\xvidcore-1.1.0-beta2\\xvidcore-1.1.0-beta2\src\\xvid.h"
#pragma comment(lib, "C:\\DevDownloads\\xvidcore-1.1.0-beta2\\xvidcore-1.1.0-beta2\\build\\win32\\bin\\libxvidcore.lib")
#endif

namespace System
{
namespace Media
{

uint8 toR[256][256];
uint8 toB[256][256];
short CrCb[256][256];
short YTab[256];
bool bInitedTabs;

void /*CAVIDec::*/SetSampleRGBData(Mpeg4::VideoObjectPlane* pPic, IMediaSample* m_sample)
{
	if (!bInitedTabs)
	{
		bInitedTabs = true;

		{
			for (int i = 0; i < 256; i++)
			{
				YTab[i] = 1.164*(i - 16);
			}
		}

		{
			for (int Y = 0; Y < 256; Y++)
			{
				for (int Cr = 0; Cr < 256; Cr++)
				{
					int value = YTab[Y] + 1.596*(Cr - 128);

					if (value < 0) value = 0;
					else if (value > 255) value = 255;

					toR[Y][Cr] = value;
				}
			}
		}

		{
			for (int Y = 0; Y < 256; Y++)
			{
				for (int Cb = 0; Cb < 256; Cb++)
				{
					int value = YTab[Y] + 2.017*(Cb - 128);

					if (value < 0) value = 0;
					else if (value > 255) value = 255;

					toB[Y][Cb] = value;
				}
			}
		}

		for (int Cr = 0; Cr < 256; Cr++)
		{
			for (int Cb = 0; Cb < 256; Cb++)
			{
				CrCb[Cr][Cb] = - 0.813*(Cr - 128) - 0.392*(Cb - 128);
			}
		}
	}

	int vertical_size = pPic->m_config->m_video_object_layer_height;
	int horizontal_size = pPic->m_config->m_video_object_layer_width;

//	if (m_currentFrame >= 0)
	{
		LSampleData sampledata;
		m_sample->LockBits(&sampledata);

	//	UPOSITION pos = m_pictures.FindIndex(m_currentFrame);
	//	PictureDecoder* pPic = (PictureDecoder*)m_pictures.GetAt(pos);

		for (int y = 0; y < vertical_size; y++)
		{
			uint8* pY = pPic->m_ybuf + pPic->m_mb_cols*16*y;

			uint8* pCr;
			uint8* pCb;

			if (true)//m_mpeg_video->m_chroma_format == 1)
			{
				pCr = pPic->m_crbuf + pPic->m_mb_cols*8*(y/2);
				pCb = pPic->m_cbbuf + pPic->m_mb_cols*8*(y/2);
			}
			/*
			else if (m_mpeg_video->m_chroma_format == 2)
			{
				pCr = pPic->m_crbuf + horizontal_size*y;
				pCb = pPic->m_cbbuf + horizontal_size/2*y/2;
			}
			else if (m_mpeg_video->m_chroma_format == 3)
			{
				pCr = pPic->m_crbuf + horizontal_size*y;
				pCb = pPic->m_cbbuf + horizontal_size*y;
			}
			*/

			uint8* out = sampledata.idata + sampledata.rowbytes*y;

			for (int x = 0; x < horizontal_size; x++)
			{
				if (false)
				{
					uint8 Y = *pY;

					uint8 R_ = Y;
					uint8 G_ = Y;
					uint8 B_ = Y;

					/*
					if (R_ < 0) R_ = 0;
					else if (R_ > 255) R_ = 255;

					if (G_ < 0) G_ = 0;
					else if (G_ > 255) G_ = 255;

					if (B_ < 0) B_ = 0;
					else if (B_ > 255) B_ = 255;
					*/

					out[0] = R_;
					out[1] = G_;
					out[2] = B_;
				}
				else
				{
					uint8 Y = *pY;
					int Cr = *pCr;
					uint8 Cb = *pCb;

					uint8 R_ = toR[Y][Cr];//YTab[Y] + 1.596*(Cr - 128);
					int G_ = YTab[Y] + CrCb[Cr][Cb];//- 0.813*(Cr - 128) - 0.392*(Cb - 128);
					uint8 B_ = toB[Y][Cb];//int B_ = YTab[Y] + 2.017*(Cb - 128);

					/*
					if (R_ < 0) R_ = 0;
					else if (R_ > 255) R_ = 255;
					*/

					if (G_ < 0) G_ = 0;
					else if (G_ > 255) G_ = 255;

					/*
					if (B_ < 0) B_ = 0;
					else if (B_ > 255) B_ = 255;
					*/

					out[0] = R_;
					out[1] = G_;
					out[2] = B_;
				}

				out += 3;
				pY++;

			//	if (m_mpeg_video->m_chroma_format == 1)
				{
					if (x & 1)
					{
						pCr++;
						pCb++;
					}
				}
				/*
				else if (m_mpeg_video->m_chroma_format == 2)
				{
					pCr++;

					if (x & 1)
					{
						pCb++;
					}
				}
				else
				{
					pCr++;
					pCb++;
				}
				*/
			}
		}

		m_sample->UnlockBits();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAVIDec

ErrorCode CAVIDec::CInputPin::CheckMediaType(MediaType * mt)
{
	if (mt->GetMajorType() != LMEDIATYPE_Video)
		return E_FAIL;

	/*
	if (FOURCCMap(&mt.subtype) != mt.subtype)	// Not a fourcc guid
		return E_FAIL;
		*/

	return Success;
}

ErrorCode CAVIDec::CInputPin::CompleteConnect(IPin* pPin)
{
	ErrorCode hr;
	hr = BasePinImpl::CompleteConnect(pPin);
	if (hr < 0) return hr;

	uint32 fccHandler = FOURCCMap(&m_mt->m_subtype).GetFOURCC();
	VideoInfoHeader* vih = (VideoInfoHeader*)m_mt->GetFormat();
	if (vih == NULL)
		return Error;

#if 0
	{
		xvid_gbl_init_t   xvid_gbl_init;
		xvid_dec_create_t xvid_dec_create;

		/* Reset the structure with zeros */
		memset(&xvid_gbl_init, 0, sizeof(xvid_gbl_init_t));
		memset(&xvid_dec_create, 0, sizeof(xvid_dec_create_t));

		/*------------------------------------------------------------------------
		 * XviD core initialization
		 *----------------------------------------------------------------------*/

		/* Version */
		xvid_gbl_init.version = XVID_VERSION;

		/* Assembly setting */
		if(false)
	#ifdef ARCH_IS_IA64
			xvid_gbl_init.cpu_flags = XVID_CPU_FORCE | XVID_CPU_IA64;
	#else
		xvid_gbl_init.cpu_flags = 0;
	#endif
		else
			xvid_gbl_init.cpu_flags = XVID_CPU_FORCE;

		xvid_gbl_init.debug = 0;//debug_level;

		xvid_global(NULL, 0, &xvid_gbl_init, NULL);

		/*------------------------------------------------------------------------
		 * XviD encoder initialization
		 *----------------------------------------------------------------------*/

		/* Version */
		xvid_dec_create.version = XVID_VERSION;

		/*
		 * Image dimensions -- set to 0, xvidcore will resize when ever it is
		 * needed
		 */
		xvid_dec_create.width = 0;
		xvid_dec_create.height = 0;

		int ret = xvid_decore(NULL, XVID_DEC_CREATE, &xvid_dec_create, NULL);

		m_dec_handle = xvid_dec_create.handle;
	}
#endif

//	ASSERT(0);
#if 0
	m_hic = ::ICDecompressOpen(ICTYPE_VIDEO, fccHandler, &vih->bmiHeader, NULL);
	if (m_hic == NULL)
		return E_FAIL;
#endif

//	DWORD size = sizeof(BITMAPINFOHEADER);//ICDecompressGetFormatSize(m_hic, m_pFilter->m_lpbiIn);

	m_pFilter->m_lpbiIn = &vih->vih->bmiHeader;
	m_pFilter->m_lpbiOut = new BitmapInfoHeader;//*)CoTaskMemAlloc(size);
	*m_pFilter->m_lpbiOut = *m_pFilter->m_lpbiIn;

	if (m_pFilter->m_lpbiIn->biBitCount == 12)	// ??
	{
		m_pFilter->m_lpbiOut->biBitCount = 24;
	}

//	uint r;

#if 0
	r = -1;//ICDecompressGetFormat(m_hic, m_pFilter->m_lpbiIn, m_pFilter->m_lpbiOut);
	if (r != ICERR_OK)
		return E_FAIL;

	r = -1;/*ICDecompressBegin(
		m_hic,
		m_pFilter->m_lpbiIn,
		m_pFilter->m_lpbiOut
		);*/
	if (r != ICERR_OK)
		return E_FAIL;
#endif

	m_outRowbytes = ROWBYTES_DWORD(m_pFilter->m_lpbiOut->biWidth, m_pFilter->m_lpbiOut->biBitCount);
	m_lpOutBits = (uint8 *)new uint8[m_outRowbytes*m_pFilter->m_lpbiOut->biHeight];

	return Success;
}

void CAVIDec::CInputPin::BreakConnect()
{
#if 0
	if (m_hic)
	{
		DWORD r = -1;//ICClose(m_hic);
		ASSERT(r == ICERR_OK);

		m_hic = NULL;
	}
#endif

	if (m_lpOutBits)
	{
		delete m_lpOutBits;
		m_lpOutBits = NULL;
	}

	m_pFilter->m_lpbiIn = NULL;
	m_pFilter->m_lpbiOut = NULL;
}

ErrorCode CAVIDec::CInputPin::EndOfStream()
{
//	ASSERT(m_hic);
	;//ICDecompressEnd(m_hic);

	return Success;
}

bool CAVIDec::CInputPin::Receive(IMediaSample *pBuffer)
{
//	CComQIPtr<ILMemInputPin> memInput = m_pFilter->m_pOutputPin->m_connectedTo;
//	if (memInput)
	{
		ULONG length;
		length = pBuffer->GetActualDataLength();

		LONGLONG timeStart;
		LONGLONG timeEnd;
		pBuffer->GetTime(&timeStart, &timeEnd);

		IMediaSample* videoSample;
		m_pFilter->m_pOutputPin->m_pAllocator->GetBuffer(0, &videoSample);
		if (videoSample)
		{
			videoSample->SetTime(&timeStart, &timeEnd);

		//	LSampleData videosampledata;
		//	if (SUCCEEDED(videoSample->LockBits(&videosampledata)))
			{
				int r;

				LSampleData buffersampledata;
				if (pBuffer->LockBits(&buffersampledata) >= 0)
				{

#if 0
					{
						xvid_dec_stats_t xvid_dec_stats;

					xvid_dec_frame_t xvid_dec_frame;

					/* Reset all structures */
					memset(&xvid_dec_frame, 0, sizeof(xvid_dec_frame_t));
					memset(&xvid_dec_stats, 0, sizeof(xvid_dec_stats_t));

					/* Set version */
					xvid_dec_frame.version = XVID_VERSION;
					xvid_dec_stats.version = XVID_VERSION;

					/* No general flags to set */
					xvid_dec_frame.general          = 0;

					/* Input stream */
					xvid_dec_frame.bitstream        = buffersampledata.idata;
					xvid_dec_frame.length           = length;//istream_size;

					uint8* ostream = new uint8[10000000];

					/* Output frame structure */
					xvid_dec_frame.output.plane[0]  = ostream;
					xvid_dec_frame.output.stride[0] = 10000;//XDIM*BPP;
					xvid_dec_frame.output.csp = XVID_CSP_I420;

					int ret = xvid_decore(m_dec_handle, XVID_DEC_DECODE, &xvid_dec_frame, &xvid_dec_stats);

					xvid_dec_frame.bitstream        = buffersampledata.idata + ret;
					xvid_dec_frame.length           = length - ret;//istream_size;

					ret += xvid_decore(m_dec_handle, XVID_DEC_DECODE, &xvid_dec_frame, &xvid_dec_stats);

					delete[] ostream;
					
#else
					{
						ASSERT(0);
					System::IO::CBitStream32* pBitStream = NULL;//new System::IO::BitStream(new System::IO::CByteStream(new MemoryByteStream(buffersampledata.idata, length)));
					pBitStream->m_bitstreamSize = length*8;

					try
					{
				//		pBitStream->getnbits(16);
				//		pBitStream->ungetbits(15);


						int start_code = Mpeg4::next_start_code(pBitStream);
						if (start_code >= 0x100 && start_code <= 0x11F)	// //	video_object_start_code 32 bslbf
						{
							if (m_config == NULL)
								m_config = new Mpeg4::MP4VConfig;

						//	TRACE("video_object\n");
							start_code = Mpeg4::next_start_code(pBitStream);
							start_code = m_config->VideoObjectLayer(pBitStream, start_code);

							start_code = Mpeg4::next_start_code(pBitStream);

							while (start_code == 0x1b2/* next_bits()== user_data_start_code*/)
							{
								start_code = Mpeg4::user_data(pBitStream, start_code);
							}
						}

						//	TRACE("left: %d\n", ((pBitStream->m_bitstreamSize+7)/8) - ((pBitStream->m_countBits+7)/8));

						if (start_code == 0x1b0)	// visual_object_sequence
						{
							// TODO
						}
						else if (start_code == 0x1b6)	// vop_start_code (Video Object Plane)
						{
							ASSERT(m_config != NULL);

							Mpeg4::VideoObjectPlane* vop = new Mpeg4::VideoObjectPlane;
							vop->m_pPrevVOP = m_pPrevVOP;
							vop->m_config = m_config;
							vop->m_mb_cols = (m_config->m_video_object_layer_width+15)/16;
							vop->m_mb_rows = (m_config->m_video_object_layer_height+15)/16;
							vop->m_macroblocks = new Mpeg4::MacroBlock[vop->m_mb_cols*vop->m_mb_rows];
							vop->m_ybuf = (uint8*)calloc(1, (vop->m_mb_rows*16)*(vop->m_mb_cols*16));
							vop->m_crbuf = (uint8*)calloc(1, (vop->m_mb_rows*8)*(vop->m_mb_cols*8));
							vop->m_cbbuf = (uint8*)calloc(1, (vop->m_mb_rows*8)*(vop->m_mb_cols*8));
							vop->mb_address = 0;

							if (m_pPrevVOP)
							{
								memcpy(vop->m_ybuf, m_pPrevVOP->m_ybuf, vop->m_mb_cols*vop->m_mb_rows*16*16);
								memcpy(vop->m_crbuf, m_pPrevVOP->m_crbuf, vop->m_mb_cols*vop->m_mb_rows*8*8);
								memcpy(vop->m_cbbuf, m_pPrevVOP->m_cbbuf, vop->m_mb_cols*vop->m_mb_rows*8*8);
							}

							try
							{
							//	vop->VideoObjectPlane(pBitStream);
								vop->ReadVideoObjectPlane(pBitStream);
							}
							catch(int)
							{
								TRACE("error\n");
							}

							SetSampleRGBData(vop, videoSample);

							if (m_pPrevVOP)
							{
								delete m_pPrevVOP;
							}
							m_pPrevVOP = vop;

						//	sample->SetTime(&timeStart, &timeEnd);

						//	hr = p->m_pVideo->m_pInputPin->Receive(sample);
						//	if (hr != S_OK)	// Stop if FAILED or S_FALSE
						//		break;
						}
						else
							ASSERT(0);
					}
					catch(int)
					{
					}
					}
#endif
				//	r = -1;
					/*ICDecompress(
						m_hic,
						0,//DWORD dwFlags,
						m_pFilter->m_lpbiIn,
						buffersampledata.idata,
						m_pFilter->m_lpbiOut,
						m_lpOutBits
						);
						*/

					pBuffer->UnlockBits();
				}
				else
					r = -1;

#if 0
				if (r == ICERR_OK)
				{
					for (int y = 0; y < videosampledata.height; y++)
					{
						LPBYTE src = m_lpOutBits + m_outRowbytes*y;
						LPBYTE dest = videosampledata.idata + videosampledata.rowbytes*(videosampledata.height-y-1);

						LPBYTE d = dest;
						LPBYTE s = src;

						if (m_pFilter->m_lpbiOut->biBitCount == 8)
						{
							for (int x = 0; x < videosampledata.width; x++)
							{
								d[0] = ((BITMAPINFO*)m_pFilter->m_lpbiOut)->bmiColors[*s].rgbRed;
								d[1] = ((BITMAPINFO*)m_pFilter->m_lpbiOut)->bmiColors[*s].rgbGreen;
								d[2] = ((BITMAPINFO*)m_pFilter->m_lpbiOut)->bmiColors[*s].rgbBlue;

								s += 1;
								d += videosampledata.bitcount/8;
							}
						}
						else if (m_pFilter->m_lpbiOut->biBitCount == 24)
						{
							for (int x = 0; x < videosampledata.width; x++)
							{
								d[0] = *s++;
								d[1] = *s++;
								d[2] = *s++;

								d += videosampledata.bitcount/8;
							}
						}
						else if (m_pFilter->m_lpbiOut->biBitCount == 32)
						{
							for (int x = 0; x < videosampledata.width; x++)
							{
								d[0] = s[0];
								d[1] = s[1];
								d[2] = s[2];

								s += m_pFilter->m_lpbiOut->biBitCount/8;
								d += videosampledata.bitcount/8;
							}
						}
					}
				}
				else
				{
				}
#endif

			//	videoSample->UnlockBits();

				m_pFilter->m_pOutputPin->m_pInputPin->Receive(videoSample);

				videoSample->Release();
			}
		}
	}

	return true;//S_OK;
}

}	// Media
}

#if 0
		r = ICDecompressExBegin(
			m_hic,                     
			0,//DWORD dwFlags,               
			m_pFilter->m_lpbiIn,//LPBITMAPINFOHEADER lpbiSrc,  
			pSample->m_pBuffer->m_pointer,                
			0,//int xSrc,                    
			0,//int ySrc,                    
			m_pFilter->m_lpbiIn->biWidth,//int dxSrc,                   
			abs(m_pFilter->m_lpbiIn->biHeight),//int dySrc,                   
			m_pFilter->m_lpbiOut,//LPBITMAPINFOHEADER lpbiDst,  
			sampledata.idata,//LPVOID lpDst,                
			0,//int xDst,                    
			0,//int yDst,                    
			m_pFilter->m_lpbiOut->biWidth,//int dxDst,                   
			abs(m_pFilter->m_lpbiOut->biHeight)//int dyDst                    
			);
#endif

#if 0
				ICDecompressEx(
					m_hic,                     
					0,//DWORD dwFlags,               
					m_pFilter->m_lpbiIn,//LPBITMAPINFOHEADER lpbiSrc,  
					pSample->m_pBuffer->m_pointer,                
					0,//int xSrc,                    
					0,//int ySrc,                    
					m_pFilter->m_lpbiIn->biWidth,//int dxSrc,                   
					abs(m_pFilter->m_lpbiIn->biHeight),//int dySrc,                   
					m_pFilter->m_lpbiOut,//LPBITMAPINFOHEADER lpbiDst,  
					sampledata.idata,//LPVOID lpDst,                
					0,//int xDst,                    
					0,//int yDst,                    
					m_pFilter->m_lpbiOut->biWidth,//int dxDst,                   
					abs(m_pFilter->m_lpbiOut->biHeight)//int dyDst                    
					);
#endif
