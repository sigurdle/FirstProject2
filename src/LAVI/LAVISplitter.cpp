#include "stdafx.h"
#include "LAVI.h"
#include "LAVISplitter.h"

#include "AVIDec.h"

#include "CinepakDec.h"
#include "MSVideo1Dec.h"

using namespace System;
using namespace System::IO;

namespace System
{
namespace Media
{

#if 0
class MemoryByteData : 
	public IByteData
{
public:
	MemoryByteData()
	{
	//	m_bytestream = NULL;
	//	m_byteLength = 0;

		m_pos = 0;
		m_buffer = NULL;
		m_size = NULL;
	}

	//ULONGLONG m_byteLength;
	ULONGLONG m_pos;
	LPBYTE m_buffer;
	ULONGLONG m_size;

public:
	STDMETHOD(Read)( 
					/* [length_is][size_is][out] */ void *pv,
					/* [in] */ ULONG cb,
					/* [out] */ ULONG *pcbRead)
	{
		ULONG bytesToRead = cb;
		if (m_pos+cb > m_size)
			bytesToRead = m_size-m_pos;

		CopyMemory(pv, m_buffer + m_pos, bytesToRead);
		m_pos += bytesToRead;
		if (pcbRead)
			*pcbRead = bytesToRead;
		return S_OK;
	}

	STDMETHOD(Seek)(
					/* [in] */ LARGE_INTEGER dlibMove,
					/* [in] */ DWORD dwOrigin,
					/* [out] */ ULARGE_INTEGER *plibNewPosition)
	{
		if (dwOrigin == STREAM_SEEK_SET)
			m_pos = dlibMove.QuadPart;
		else if (dwOrigin == STREAM_SEEK_CUR)
			m_pos += dlibMove.QuadPart;
		else
			m_pos = m_size + dlibMove.QuadPart;

		if (plibNewPosition)
			(*plibNewPosition).QuadPart = m_pos;

		return S_OK;
	}
	/*
	STDMETHOD(Clone)(ILByteStream* *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	*/
};

ErrorCode CreateByteStreamOnHGlobal(HGLOBAL hGlobal, BOOL fDeleteOnRelease, IByteStream* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	ASSERT(0);
#if 0

	CComObject<CLByteMemoryStream>* p;
	CComObject<CLByteMemoryStream>::CreateInstance(&p);
	if (p)
	{
		p->AddRef();

		p->m_buffer = (LPBYTE)hGlobal;
		p->m_size = GlobalSize(hGlobal);

		*pVal = p;
		return S_OK;
	}
#endif

	return E_OUTOFMEMORY;
}
#endif

class CVideoStream :
	public BaseOutputPinImpl,
	public IMediaSeeking
{
public:

static MSWindows::DWORD WINAPI VideoRunProc(LPVOID lpParameter)
{
	CVideoStream* p = (CVideoStream*)(IPin*)lpParameter;

	ErrorCode hr = Success;

	for (int i = 0; i < p->m_pAVIStream->m_aviStreamHeader.dwLength; i++)
	{
		p->m_currentFrame = i;

		/*
		if (i == 1471)
			TRACE("");
			*/

		IMediaSample* sample;
		hr = p->m_pAVIStream->GetSample(i, &sample);
		if (hr < 0)
			break;

		ASSERT(sample);

		LONGLONG sampleDuration = TIME_SCALE * p->m_pAVIStream->m_aviStreamHeader.dwScale / p->m_pAVIStream->m_aviStreamHeader.dwRate;

		LONGLONG timeStart = sampleDuration*i;//p->m_currentFrame;
		LONGLONG timeEnd = timeStart+sampleDuration;

		sample->SetTime(&timeStart, &timeEnd);

		hr = p->m_pInputPin->Receive(sample);
		if (hr != true/*S_OK*/)
			break;

		sample->Release();
	}

	if (hr >= 0)
		p->m_connectedTo->EndOfStream();	

//	CoUninitialize();

	return 0;
}

	CVideoStream()
	{
		m_threadId = 0;
		m_hThread = NULL;

		m_pAVIStream = NULL;
		m_pBitmapInfoHeader = NULL;

		m_currentFrame = -1;
	}

	//CComObject<CVideoMediaType>* m_pMediaType;

	CAVIStream* m_pAVIStream;
	WIN_BITMAPINFOHEADER * m_pBitmapInfoHeader;
	//int m_streamNumber;

	long m_currentFrame;

	MSWindows::DWORD m_threadId;
	HANDLE m_hThread;

	virtual ErrorCode CheckMediaType(MediaType * mt)
	{
		if (mt->GetMajorType() != LMEDIATYPE_Video)
			return E_FAIL;

		/* Have this ??
		if (FOURCCMap(&m_mt->subtype) != m_mt->subtype)	// Not a fourcc guid
			return E_FAIL;
			*/

		return Success;
	}

	virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType)
	{
		if (iPosition == 0)
		{
			VideoInfoHeader* vih = new VideoInfoHeader(m_pBitmapInfoHeader->biClrUsed);

		//	mediaType.Create(sizeof(LVIDEOINFOHEADER2)+m_pBitmapInfoHeader->biClrUsed*sizeof(RGBQUAD));
	//		memcpy(&((LVIDEOINFOHEADER2*)mediaType.pbFormat)->bmiHeader, m_pBitmapInfoHeader, sizeof(BITMAPINFOHEADER)+m_pBitmapInfoHeader->biClrUsed*sizeof(RGBQUAD));
			vih->vih->bmiHeader.biWidth = m_pBitmapInfoHeader->biWidth;
			vih->vih->bmiHeader.biHeight = m_pBitmapInfoHeader->biHeight;
			vih->vih->bmiHeader.biBitCount = m_pBitmapInfoHeader->biBitCount;
			vih->vih->bmiHeader.biPlanes = m_pBitmapInfoHeader->biPlanes;
			vih->vih->bmiHeader.biClrUsed = m_pBitmapInfoHeader->biClrUsed;
			vih->vih->bmiHeader.biCompression = m_pBitmapInfoHeader->biCompression;

			MediaType* mediaType = new MediaType(LMEDIATYPE_Video, FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler), GUID_NULL, vih);
			//mediaType.m_p->subtype = ;

			*pMediaType = mediaType;

			return Success_True;
		}
		else
		{
		//	pMediaType = NULL;
			return Success_False;
		}
	}

	virtual ErrorCode Run(LONGLONG tStart)
	{
		ASSERT(0);
#if 0
		m_hThread = CreateThread(NULL, NULL, VideoRunProc, (LPVOID)(IPin*)this, 0, &m_threadId);
#endif
		if (m_hThread == NULL)
			return Error;

		return Success;
	}

// ILPin
	inline AVISplitter* GetFilter() const
	{
		return (AVISplitter*)m_pFilter;
	}

#if 0
	STDMETHOD(Connect)(ILPin* pReceivePin, LMediaType* pmt)
	{
		if (pReceivePin == NULL) return E_POINTER;

		if (m_connectedTo != NULL)
		{
			ASSERT(0);
			return E_UNEXPECTED;	// Already connected
		}

		//CComPtr<ILMediaType> mediaType;
		//GetMediaType(&mediaType);

		{ // TODO, maybe not do this here
		// Create video media type

			ASSERT(0);
			/*
			ASSERT(m_pMediaType == NULL);

			CComObject<CVideoMediaType>::CreateInstance(&m_pMediaType);
			m_pMediaType->AddRef();
			m_pMediaType->m_pVideoOut = this;
			m_pMediaType->m_mt.majortype = LMEDIATYPE_Video;
			m_pMediaType->m_mt.fourcc = m_pAVIStream->m_aviStreamHeader.fccHandler;
			m_pMediaType->m_mt.pformat = (void*)m_pBitmapInfoHeader;
			*/
		}

		CComQIPtr<ILMemInputPin> memInput = pReceivePin;
		if (memInput)
		{
			memInput->GetAllocator(&m_pAVIStream->m_allocator);
		}

		ErrorCode hr = pReceivePin->ReceiveConnection(this, m_mt);
		if (SUCCEEDED(hr))
		{
			m_connectedTo = pReceivePin;
		}

		return hr;
	}
#endif

	void SeekFrame(long frame)
	{
		TRACE("%d\n", frame);

		long from;

		if (frame >= m_currentFrame)
		{
			for (from = frame; from > m_currentFrame; from--)
			{
				if (m_pAVIStream->m_sampleEntries[from].m_flags & AVIIF_KEYFRAME)
				{
					/*
					if (m_pCurrentVOP)
					{
						delete m_pCurrentVOP;
						m_pCurrentVOP = NULL;
					}
					*/
					break;
				}
			}
		}
		else
		{
			/*
			if (m_pCurrentVOP)
			{
				delete m_pCurrentVOP;
				m_pCurrentVOP = NULL;
			}
			*/

			for (from = frame; from > 0; from--)
			{
				if (m_pAVIStream->m_sampleEntries[from].m_flags & AVIIF_KEYFRAME)
//				if (m_pTrack->m_sampleflags[from])
					break;
			}
		}

		for (ULONG i = from; i <= frame; i++)
		{
			if (i == m_currentFrame)
				continue;

			IMediaSample* sample;
			ErrorCode hr = m_pAVIStream->GetSample(i, &sample);

			hr = m_pInputPin->Receive(sample);
		//	if (hr != true/*S_OK*/)
		//		break;

			sample->Release();
		}

		m_currentFrame = frame;
	}

// IMediaSeeking
	ErrorCode Seek(TimeUnit unit, LONGLONG t)
	{
		if (unit == TimeFormat_ref)
		{
			long frame = (t * m_pAVIStream->m_aviStreamHeader.dwRate) / (TIME_SCALE * m_pAVIStream->m_aviStreamHeader.dwScale);
			SeekFrame(frame);
		}
		else if (unit == TimeFormat_frame)
		{
			SeekFrame(t);
		}
		else
		{
			ASSERT(0);
			return Error;
		}

		return Success;
	}
	ErrorCode GetDuration(TimeUnit unit, LONGLONG* pVal)
	{
		if (pVal == NULL) return Error_InvalidArgument;

		if (unit == TimeFormat_ref)
		{
			*pVal = (m_pAVIStream->m_aviStreamHeader.dwLength * TIME_SCALE / m_pAVIStream->m_aviStreamHeader.dwRate) * m_pAVIStream->m_aviStreamHeader.dwScale;
		}
		else if (unit == TimeFormat_frame)
		{
			*pVal = m_pAVIStream->m_aviStreamHeader.dwLength;
		}
		else
		{
			ASSERT(0);
			return Error;
		}

		return Success;
	}
	ErrorCode GetCurrentPosition(TimeUnit unit, LONGLONG* pVal)
	{
		if (pVal == NULL) return Error_InvalidArgument;

		if (unit == TimeFormat_ref)
		{
			*pVal = (m_currentFrame * TIME_SCALE / m_pAVIStream->m_aviStreamHeader.dwRate) * m_pAVIStream->m_aviStreamHeader.dwScale;
		}
		else if (unit == TimeFormat_frame)
		{
			*pVal = m_currentFrame;
		}
		else
		{
			ASSERT(0);
			return Error;
		}

		return Success;
	}
};

class CAudioStream :
	public BaseOutputPinImpl,
	public IMediaSeeking
{
public:

static MSWindows::DWORD WINAPI AudioRunProc(LPVOID lpParameter)
{
	CAudioStream* p = (CAudioStream*)(IPin*)lpParameter;

	ErrorCode hr = Success;

	for (int i = 0; i < p->m_pAVIStream->m_aviStreamHeader.dwLength; i++)
	{
		IMediaSample* sample;
		hr = p->m_pAVIStream->GetSample(i, &sample);
		if (hr < 0)
			break;

		if (sample == NULL)
			break;

		ASSERT(sample);

		LONGLONG sampleDuration = TIME_SCALE * p->m_pAVIStream->m_aviStreamHeader.dwScale / p->m_pAVIStream->m_aviStreamHeader.dwRate;

		LONGLONG timeStart = sampleDuration*i;//p->m_currentFrame;
		LONGLONG timeEnd = timeStart+sampleDuration;

		sample->SetTime(&timeStart, &timeEnd);

		hr = p->m_pInputPin->Receive(sample);
		if (hr != Success)
			break;
	}

	if (hr >= 0)
		p->m_connectedTo->EndOfStream();	

	return 0;
}

	CAudioStream()
	{
	//	m_pMediaType = NULL;

		m_pAVIStream = NULL;
		m_pWaveFormat = NULL;

		m_threadId = 0;
		m_hThread = NULL;
	}

	int FinalConstruct()
	{
		return 0;
	}

	void FinalRelease()
	{
		/*
		if (m_pMediaType)
		{
			m_pMediaType->Release();
			m_pMediaType = NULL;
		}

		if (m_pWaveFormat)
		{
			GlobalFree(m_pWaveFormat);
			m_pWaveFormat = NULL;
		}
		*/
	}

	//CComObject<CMediaType>* m_pMediaType;
	//CComPtr<ILMemAllocator> m_allocator;

	CAVIStream* m_pAVIStream;
	MSWindows::LPWAVEFORMATEX m_pWaveFormat;
	//int m_streamNumber;

	MSWindows::DWORD m_threadId;
	HANDLE m_hThread;

	virtual ErrorCode CheckMediaType(const MediaType& mt)
	{
		if (mt.GetMajorType() != LMEDIATYPE_Audio)
			return Error;

		return Success;
	}

	virtual ErrorCode GetMediaType(int iPosition, MediaType* pMediaType)
	{
		if (iPosition == 0)
		{
			ASSERT(0);
#if 0
			MediaType mediaType;
			mediaType.Create(sizeof(WAVEFORMATEX)+m_pWaveFormat->cbSize);

			memcpy(mediaType.pbFormat, m_pWaveFormat, sizeof(WAVEFORMATEX)+m_pWaveFormat->cbSize);

			mediaType.majortype = LMEDIATYPE_Audio;
			mediaType.subtype = FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);

			*pMediaType = mediaType;
#endif
			return Success_True;
		}
		else
		{
			pMediaType = NULL;
			return Success_False;
		}
	}

	virtual ErrorCode Run(LONGLONG tStart)
	{
		ASSERT(0);
#if 0
		m_hThread = CreateThread(NULL, NULL, AudioRunProc, (LPVOID)(IPin*)this, 0, &m_threadId);
#endif
		if (m_hThread == NULL)
			return E_FAIL;

		return Success;
	}

// ILPin
	inline AVISplitter* GetFilter() const
	{
		return (AVISplitter*)m_pFilter;
	}

// IMediaSeeking
	ErrorCode Seek(TimeUnit unit, LONGLONG t)
	{
		ASSERT(0);
		return Error_NotImplemented;
	}
	ErrorCode GetDuration(TimeUnit unit, LONGLONG* pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = ((LONGLONG)m_pAVIStream->m_aviStreamHeader.dwLength * m_pAVIStream->m_aviStreamHeader.dwScale / m_pAVIStream->m_aviStreamHeader.dwRate);
		return Success;
	}
	ErrorCode GetCurrentPosition(TimeUnit unit, LONGLONG* pVal)
	{
		ASSERT(0);
		return Error_NotImplemented;
	}
};

/////////////////////////////////////////////////////////////////////////////
// AVISplitter

ErrorCode AVISplitter::CInputPin::CompleteConnect(IPin *pPin)
{
	ErrorCode hr;
	hr = BasePinImpl::CompleteConnect(pPin);	// Call base class
	if (hr < 0) return hr;

	Riff::CChunk ck;
	ck.Descend(GetFilter()->m_stream);

	if (ck.m_id == mmioFOURCC('R','I','F','F'))
	{
		if (ck.m_grpid == formtypeAVI)
		{
			return GetFilter()->ReadAVI();
		}
		/*
		else if (ck.m_grpid == mmioFOURCC('W','A','V','E'))
		{
			return m_pFilter->ReadWAVE();
		}
		else
		*/
			return E_FAIL;	// Unknown formtype
	}
	else
		return E_FAIL;	// Not a RIFF file

// Don't ascend out of this one, as that would require a Seek to the end of this chunk //	ck.Ascend(m_pFilter->m_stream);

	return -1;
}

LONGLONG GetPos(ISequentialByteStream* stream)
{
	return stream->Seek(0, System::IO::STREAM_SEEK_CUR);
}

ErrorCode AVISplitter::ReadAVI()
{
	ULONG nRead;

	while (1)
	{
		Riff::CChunk ck;
		if (ck.Descend(m_stream) != Success)
			break;

		if (ck.m_id == mmioFOURCC('L','I','S','T'))
		{
			ULONGLONG parentStart = ck.m_pos;
			ULONG parentSize = ck.m_size;

			if (ck.m_grpid == listtypeAVIHEADER)
			{
				uint32 streamNumber = 0;

				while (1)
				{
					ULONGLONG pos = GetPos(m_stream);
					if (pos >= (parentStart + parentSize))
					{
						ASSERT(pos == (parentStart + parentSize));
						break;
					}

					Riff::CChunk ck;
					if (ck.Descend(m_stream) != Success)
						break;

					if (ck.m_id == ckidAVIMAINHDR)
					{
						if (ck.m_size != sizeof(MainAVIHeader))
						{
							TRACE("Unexpected size of chunk");
							return Error;
						}

						nRead = m_stream->Read(&m_mainAVIHeader, sizeof(MainAVIHeader));
						if (nRead != sizeof(MainAVIHeader))
						{
							return Error;
						}
					}
					else if (ck.m_id == mmioFOURCC('L','I','S','T'))
					{
						if (ck.m_grpid == listtypeSTREAMHEADER)
						{
							ULONGLONG parentStart = ck.m_pos;
							ULONG parentSize = ck.m_size;

							CAVIStream* pAVIStream = NULL;

							while (1)
							{
								ULONGLONG pos = GetPos(m_stream);
								if (pos >= (parentStart + parentSize))
								{
									ASSERT(pos == (parentStart + parentSize));
									break;
								}

								Riff::CChunk ck;
								if (ck.Descend(m_stream) != Success)
									break;

								if (ck.m_id == ckidSTREAMHEADER)
								{
									if (ck.m_size < 56 || ck.m_size > sizeof(AVIStreamHeader))
									{
										TRACE("Unexpected size of chunk");
										return Error;
									}

									pAVIStream = new CAVIStream;
									pAVIStream->m_pavifile = this;

									nRead = m_stream->Read(&pAVIStream->m_aviStreamHeader, ck.m_size);

									if (pAVIStream->m_aviStreamHeader.fccType == streamtypeVIDEO)
									{
										ErrorCode hr;

										CVideoStream* pVideoStream = new CVideoStream;
									//	pVideoStream->AddRef();
										pVideoStream->m_pFilter = this;
										pVideoStream->m_id = WSTR("Video Output");
										pVideoStream->m_pAVIStream = pAVIStream;
										//pVideoStream->m_streamNumber = streamNumber;

										// TODO
//#if 0
										AddPin(pVideoStream);
//#endif
										pAVIStream->m_outputPin = pVideoStream;
									}
									else if (pAVIStream->m_aviStreamHeader.fccType == streamtypeAUDIO)
									{
#if 0
										ErrorCode hr;

										CAudioStream* pAudioStream = new CAudioStream;
									//	pAudioStream->AddRef();
										pAudioStream->m_pFilter = this;
										pAudioStream->m_id = L"Audio Output";
										pAudioStream->m_pAVIStream = pAVIStream;
								//		pAudioStream->m_streamNumber = streamNumber;

										// TODO
#if 0
										AddPin(pAudioStream);
#endif
										pAVIStream->m_outputPin = pAudioStream;
#endif
									}

									m_streams.Add(pAVIStream);
								}
								else if (ck.m_id == ckidSTREAMFORMAT)
								{
									if (pAVIStream == NULL)
									{
										TRACE("Expected stream header before stream format");
										return Error;
									}

									if (pAVIStream->m_aviStreamHeader.fccType == streamtypeVIDEO)
									{
										if (ck.m_size < sizeof(WIN_BITMAPINFOHEADER))
										{
											TRACE("Unexpected size of chunk");
											return Error;
										}

										if (pAVIStream->m_outputPin)
										{
											CVideoStream* pVideoStream = static_cast<CVideoStream*>(pAVIStream->m_outputPin);

										//	CLMediaType mt;
										//	mt->subtype = FOURCCMap(pAVIStream->m_aviStreamHeader.fccHandler);

											pVideoStream->m_pBitmapInfoHeader = (WIN_BITMAPINFOHEADER *)new uint8[ck.m_size];
											nRead = m_stream->Read(pVideoStream->m_pBitmapInfoHeader, ck.m_size);
											if (nRead != ck.m_size)
											{
												TRACE("Read error");
												return Error;
											}
										}
									}
									else if (pAVIStream->m_aviStreamHeader.fccType == streamtypeAUDIO)
									{
										if (ck.m_size < sizeof(MSWindows::PCMWAVEFORMAT))
										{
											TRACE("Unexpected size of chunk");
											return Error;
										}

										if (pAVIStream->m_outputPin)
										{
											CAudioStream* pAudioStream = static_cast<CAudioStream*>(pAVIStream->m_outputPin);

											pAudioStream->m_pWaveFormat = (MSWindows::LPWAVEFORMATEX)new uint8[MAX(ck.m_size, sizeof(MSWindows::WAVEFORMATEX))];
											nRead = m_stream->Read(pAudioStream->m_pWaveFormat, ck.m_size);
											if (nRead != ck.m_size)
											{
												TRACE("Read error");
												return Error;
											}

											if (pAudioStream->m_pWaveFormat->wFormatTag == WAVE_FORMAT_PCM)
											{
												pAudioStream->m_pWaveFormat->cbSize = 0;
											}
										}
									}
								}
								else if (ck.m_id == ckidSTREAMHANDLERDATA)
								{
									MessageBeep(-1);
								}

								ck.Ascend(m_stream);
							}

							if (pAVIStream->m_aviStreamHeader.fccType == streamtypeVIDEO)
							{
								TRACE("fccHandler: %4.4s\n", &pAVIStream->m_aviStreamHeader.fccHandler);

								// Stream header data and stream format has been read, if the data is compressed, connect to a decoder
								if (pAVIStream->m_aviStreamHeader.fccHandler != mmioFOURCC('D','I','B',' '))
								{
									if (pAVIStream->m_aviStreamHeader.fccHandler == mmioFOURCC('c','v','i','d'))
									{
										IBaseFilter* decoder = new CinepakDec;
									//	decoder.CoCreateInstance(L"LAVI.AVIDec");
										if (decoder)
										{
											m_pFilterGraph->AddFilter(decoder);

											IPin* pin = decoder->FindPin(WSTR("Video Input"));
											pAVIStream->m_outputPin->Connect(pin, NULL);
										}
									}
									else if (pAVIStream->m_aviStreamHeader.fccHandler == mmioFOURCC('M','S','V','C'))
									{
										IBaseFilter* decoder = new MSVideo1Dec;
										if (decoder)
										{
											m_pFilterGraph->AddFilter(decoder);

											IPin* pin = decoder->FindPin(WSTR("Video Input"));
											pAVIStream->m_outputPin->Connect(pin, NULL);
										}
									}
									else
									{
										IBaseFilter* decoder = new CAVIDec;
										if (decoder)
										{
											m_pFilterGraph->AddFilter(decoder);

											IPin* pin = decoder->FindPin(WSTR("Video Input"));
											pAVIStream->m_outputPin->Connect(pin, NULL);
										}
									}
								}
							}
							else
							{
							}

							streamNumber++;
							if (streamNumber > m_mainAVIHeader.dwStreams)
							{
								TRACE("Found more streams in the file than that specified in the header");
							}
						}
					}
					else
					{
						MessageBeep(-1);
					}

					ck.Ascend(m_stream);
				}
			}
			else if (ck.m_grpid == listtypeAVIMOVIE)
			{
				m_movieOffset = GetPos(m_stream);

				// Don't ascend from this one, as that would force a seek to the end of this chunk
				// Also, now the stream pointer is ready to read the first sample data chunk
#if 0
				break;
#endif

#if 0
				while (1)
				{
					CChunk ck;
					if (ck.Descend(m_stream) != Success)
						break;

					if (ck.m_id == listtypeAVIRECORD)
					{
						// Read the entire record chunk at once

						HGLOBAL h = GlobalAlloc(0/*GMEM_MOVEABLE*/, ck.m_size);
						if (h)
						{
							LPBYTE p = (LPBYTE)GlobalLock(h);
							if (p)
							{
								ULONG nRead;
								pavifile->m_stream->Read(p, ck.m_size, &nRead);
								if (nRead != ck.m_size)
								{
									GlobalUnlock(h);
									GlobalFree(h);

									ASSERT(0);
									return Error;
								}

								GlobalUnlock(h);

								CComPtr<ILByteStream> stream;
								CreateByteStreamOnHGlobal(h, FALSE/*fDeleteOnRelease*/, &stream);
								if (stream)
								{
									ULONGLONG parentStart = 0;//ck.m_pos.QuadPart;
									ULONG parentSize = ck.m_size;

									while (1)
									{
										ULONGLONG pos = GetPos(stream);
										if (pos >= (parentStart + parentSize))
										{
											ASSERT(pos == (parentStart + parentSize));
											break;
										}

										CChunk ck;
										if (ck.Descend(stream) != Success)
											break;

										if ((TWOCCFromFOURCC(ck.m_id) == cktypeDIBbits))
										{
											int streamNumber = StreamFromFOURCC(ck.m_id);
											if (streamNumber < pavifile->m_streams.GetSize())
											{
											}
										}
										else if (TWOCCFromFOURCC(ck.m_id) == cktypeDIBcompressed)
										{
											MessageBeep(-1);
										}
										else if (TWOCCFromFOURCC(ck.m_id) == cktypeWAVEbytes)
										{
											MessageBeep(-1);
										}
									}
								}
							}

							GlobalFree(h);
						}
					}
					else if ((TWOCCFromFOURCC(ck.m_id) == cktypeDIBbits) ||
								(TWOCCFromFOURCC(ck.m_id) == cktypeDIBcompressed))
					{
					}
					else if (TWOCCFromFOURCC(ck.m_id) == cktypeWAVEbytes)
					{
						break;
					}
				}
#endif
			}
			/*
			else if (ck.m_grpid == ckidAVINEWINDEX)
			{
				//AVIINDEXENTRY
				MessageBeep(-1);
			}
			*/
		}
		else if (ck.m_id == ckidAVINEWINDEX)
		{
			//ULONG vi = 0;

			ULONG count = ck.m_size / sizeof(AVIINDEXENTRY);
			for (ULONG i = 0; i < count; i++)
			{
				AVIINDEXENTRY entry;
				m_stream->Read(&entry, sizeof(entry));

				int streamNumber = StreamFromFOURCC(entry.ckid);
				if (streamNumber < m_streams.GetSize())
				{
					CAVIStream* paviStream = m_streams[streamNumber];

					if ((TWOCCFromFOURCC(entry.ckid) == cktypeDIBbits) ||
						(TWOCCFromFOURCC(entry.ckid) == cktypeDIBcompressed))
					{
				//	ASSERT(TWOCCFromFOURCC(ck.m_id) == cktypeDIBcompressed);

						CVideoStream* pVideoStream = static_cast<CVideoStream*>(paviStream->m_outputPin);

						if (entry.dwFlags & AVIIF_KEYFRAME)
						{
							TRACE("%d\n", paviStream->m_sampleEntries.GetSize());
						}

						CChunkEntry ckentry;
						ckentry.m_chunkOffset = m_movieOffset + entry.dwChunkOffset + 4;
						ckentry.m_chunkLength = entry.dwChunkLength;
						ckentry.m_flags = entry.dwFlags;

						paviStream->m_sampleEntries.Add(ckentry);

						//vi++;
					}
				}
			}
		}

		ck.Ascend(m_stream);
	}

	return Success;
}

#if 0
ErrorCode CVideoStream::ReadDIB(ILByteStream* stream, ULONG cksize, ILMediaSample* *ppsample)
{
	ErrorCode hr;

	CComPtr<ILVideoSample> m_sample;
	ASSERT(m_sample == NULL);

	m_allocator->GetBuffer(0, (ILMediaSample**)&m_sample);
	if (m_sample)
	{
		LSampleData sampledata;
		if (SUCCEEDED(m_sample->LockBits(&sampledata)))
		{
			// TODO, read entire chunk at once
			ULONG rowbytes = ROWBYTES_DWORD(m_pBitmapInfoHeader->biWidth, m_pBitmapInfoHeader->biBitCount);
			ULONG real_rowbytes = (m_pBitmapInfoHeader->biWidth*m_pBitmapInfoHeader->biBitCount+7)/8;
			ASSERT(rowbytes >= real_rowbytes);

			LPBYTE buffer = (LPBYTE)malloc(rowbytes);

			for (int y = 0; y < sampledata.height; y++)
			{
				LPBYTE dest = sampledata.idata + sampledata.rowbytes*(sampledata.height-y-1);

				ULONG nRead;
				//p->m_stream->Read(dest, real_rowbytes, &nRead);
				stream->Read(buffer, real_rowbytes, &nRead);
				if (nRead != real_rowbytes)
				{
					hr = E_FAIL;
					return hr;
				}

				LPBYTE d = dest;
				LPBYTE s = buffer;
				for (int x = 0; x < sampledata.width; x++)
				{
					d[0] = s[0];
					d[1] = s[1];
					d[2] = s[2];

					d += sampledata.bitcount/8;
					s += m_pBitmapInfoHeader->biBitCount/8;
				}

				LARGE_INTEGER li;
				li.QuadPart = rowbytes - real_rowbytes;
				stream->Seek(li, STREAM_SEEK_CUR, NULL);
			}

			free(buffer);

			m_sample->UnlockBits();
		}
		else
		{
			hr = E_FAIL;
			return hr;
		}

		double sampleDuration = (double)m_pAVIStream->m_aviStreamHeader.dwScale / (double)m_pAVIStream->m_aviStreamHeader.dwRate;

		double timeStart = sampleDuration*m_currentFrame;
		double timeEnd = timeStart+sampleDuration;

		m_sample->SetTime(&timeStart, &timeEnd);

		m_currentFrame++;
	}

	*ppsample = m_sample;
	(*ppsample)->AddRef();

	return S_OK;
}

#endif

#if 0
// Interleaved only
static DWORD WINAPI RunningThreadProc(
  LPVOID lpParameter   // thread data
)
{
	CoInitialize(NULL);//, COINIT_MULTITHREADED);

//	ErrorCode hr;

//	EnterCriticalSection(&pFilter->m_pLock);

	AVISplitter* pavifile = (AVISplitter*)lpParameter;

	LARGE_INTEGER li;
	li.QuadPart = pavifile->m_movieOffset;
	pavifile->m_stream->Seek(li, STREAM_SEEK_SET, NULL);

	/*
	CComQIPtr<ILMemInputPin> memInput = p->m_connectedTo;
	if (memInput)
	{
	*/
		ErrorCode hr = S_OK;

		//double sampleDuration = (double)p->m_pAVIStream->m_aviStreamHeader.dwScale / (double)p->m_pAVIStream->m_aviStreamHeader.dwRate;

		//double t = 0;

		while (1)
		{
			CChunk ck;
			if (ck.Descend(pavifile->m_stream) != S_OK)
				break;

			if (ck.m_id == listtypeAVIRECORD)
			{
				// Read the entire record chunk at once

				HGLOBAL h = GlobalAlloc(0/*GMEM_MOVEABLE*/, ck.m_size);
				if (h)
				{
					LPBYTE p = (LPBYTE)GlobalLock(h);
					if (p)
					{
						ULONG nRead;
						pavifile->m_stream->Read(p, ck.m_size, &nRead);
						if (nRead != ck.m_size)
						{
							GlobalUnlock(h);
							GlobalFree(h);

							ASSERT(0);
							return E_FAIL;
						}

						GlobalUnlock(h);

						CComPtr<ILByteStream> stream;
						CreateByteStreamOnHGlobal(h, FALSE/*fDeleteOnRelease*/, &stream);
						if (stream)
						{
							ULONGLONG parentStart = 0;//ck.m_pos.QuadPart;
							ULONG parentSize = ck.m_size;

							while (1)
							{
								ULONGLONG pos = GetPos(stream);
								if (pos >= (parentStart + parentSize))
								{
									ASSERT(pos == (parentStart + parentSize));
									break;
								}

								CChunk ck;
								if (ck.Descend(stream) != S_OK)
									break;

								if ((TWOCCFromFOURCC(ck.m_id) == cktypeDIBbits))
								{
									int streamNumber = StreamFromFOURCC(ck.m_id);
									if (streamNumber < pavifile->m_streams.GetSize())
									{
										CVideoStream* pVideoStream = static_cast<CVideoStream*>(pavifile->m_streams[streamNumber]->m_outputPin);

										if (pVideoStream->m_sample)
										{
											WaitForSingleObject(pVideoStream->m_hEvent2, INFINITE);
										}

										pVideoStream->ReadDIB(pavifile->m_stream, ck.m_size, &pVideoStream->m_sample);
										ASSERT(pVideoStream->m_sample);

										SetEvent(pVideoStream->m_hEvent);
									}
									else
										hr = E_FAIL;
								}
								else if (TWOCCFromFOURCC(ck.m_id) == cktypeDIBcompressed)
								{
									MessageBeep(-1);
								}
								else if (TWOCCFromFOURCC(ck.m_id) == cktypeWAVEbytes)
								{
									MessageBeep(-1);
								}
							}
						}
					}

					GlobalFree(h);
				}
			}
#if 0
			else if (TWOCCFromFOURCC(ck.m_id) == cktypeDIBbits)
			{
				int streamNumber = StreamFromFOURCC(ck.m_id);
				if (streamNumber < pavifile->m_streams.GetSize())
				{
					CVideoStream* pVideoStream = static_cast<CVideoStream*>(pavifile->m_streams[streamNumber]->m_outputPin);

					if (pVideoStream->m_sample)
					{
						WaitForSingleObject(pVideoStream->m_hEvent2, INFINITE);
					}

					pVideoStream->ReadDIB(pavifile->m_stream, ck.m_size, &pVideoStream->m_sample);
					ASSERT(pVideoStream->m_sample);

					SetEvent(pVideoStream->m_hEvent);
				}
				else
					hr = E_FAIL;
			}
#endif
			else if ((TWOCCFromFOURCC(ck.m_id) == cktypeDIBbits) ||
						(TWOCCFromFOURCC(ck.m_id) == cktypeDIBcompressed))
			{
			//	ASSERT(TWOCCFromFOURCC(ck.m_id) == cktypeDIBcompressed);

				int streamNumber = StreamFromFOURCC(ck.m_id);
				if (streamNumber < pavifile->m_streams.GetSize())
				{
					CVideoStream* pVideoStream = static_cast<CVideoStream*>(pavifile->m_streams[streamNumber]->m_outputPin);

					if (pVideoStream->m_sample)
					{
						WaitForSingleObject(pVideoStream->m_hEvent2, INFINITE);
					}

					pVideoStream->ReadCompressedDIB(pavifile->m_stream, ck.m_size, &pVideoStream->m_sample);
					ASSERT(pVideoStream->m_sample);

					SetEvent(pVideoStream->m_hEvent);

					//if (pVideoStream->m_currentFrame == 1)
					//	break;	// TODO remove
				}
				else
					hr = E_FAIL;
			}
			else if (TWOCCFromFOURCC(ck.m_id) == cktypeWAVEbytes)
			{
				int streamNumber = StreamFromFOURCC(ck.m_id);
				if (streamNumber < pavifile->m_streams.GetSize())
				{
					CAudioStream* pAudioStream = static_cast<CAudioStream*>(pavifile->m_streams[streamNumber]->m_outputPin);
				}
			}

			ck.Ascend(pavifile->m_stream);
		}
/*
		if (SUCCEEDED(hr))	// Don't send this if the downstream filter failed in Receive?
			p->m_connectedTo->EndOfStream();
	}
*/

	CoUninitialize();

	return 0;
}
#endif

ErrorCode CAVIStream::GetSample(long n, IMediaSample* *pVal)
{
	ASSERT(pVal != NULL);
	*pVal = NULL;

	// Is it already buffered
	for (int i = 0; i < m_bufferedSamples.GetSize(); i++)
	{
		if (m_bufferedSamples[i]->m_nSample == n)
		{
			*pVal = m_bufferedSamples[i]->m_sample;
			//(*pVal)->AddRef();

			// Remove the sample from the list of buffered samples
			delete m_bufferedSamples[i];
			m_bufferedSamples.RemoveAt(i);

			return Success;
		}
	}

	// Read from the file until 
	while (m_sampleEntries.GetSize() < m_aviStreamHeader.dwLength)
	{
		ErrorCode hr = m_pavifile->ReadNext(this, n);
		if (hr < 0)
			return hr;

		for (int i = 0; i < m_bufferedSamples.GetSize(); i++)
		{
			if (m_bufferedSamples[i]->m_nSample == n)
			{
				*pVal = m_bufferedSamples[i]->m_sample;
				//(*pVal)->AddRef();

				// Remove the sample from the list of buffered samples
				delete m_bufferedSamples[i];
				m_bufferedSamples.RemoveAt(i);

				return Success;
			}
		}
	}

	// The sample wasn't buffered, we need to seek back in the file and read it
	{
		m_pavifile->m_criticalSection.Lock();

		// Remember current pos
		LONGLONG curpos = m_pavifile->m_stream->Seek(0, System::IO::STREAM_SEEK_CUR);

		// Seek to chunk start
		m_pavifile->m_stream->Seek(m_sampleEntries[n].m_chunkOffset, System::IO::STREAM_SEEK_SET);
	//	TRACE("%d\n", m_sampleEntries[n].m_chunkOffset);

		// Create and read the sample
		IMediaSample* sample;
		m_outputPin->m_pAllocator->GetBuffer(m_sampleEntries[n].m_chunkLength, &sample);
		ASSERT(sample);
		if (sample)
		{
			m_pavifile->ReadChunkData(sample, m_sampleEntries[n].m_chunkLength);

			*pVal = sample;
		//	(*pVal)->AddRef();
		}

		// Reset stream position
		m_pavifile->m_stream->Seek(curpos, System::IO::STREAM_SEEK_SET);

		m_pavifile->m_criticalSection.Unlock();
	}

	return Success;
}

ErrorCode AVISplitter::ReadNext(CAVIStream* p, int n/*sample number to always buffer*/)
{
	m_criticalSection.Lock();

	Riff::CChunk ck;
	if (ck.Descend(m_stream) != Success)
	{
		m_criticalSection.Unlock();
		return Error;
	}

	if (ck.m_id == mmioFOURCC('L','I','S','T'))
	{
		ASSERT(0);
		if (ck.m_grpid == listtypeAVIRECORD)
		{
		}
	}
	else if ((TWOCCFromFOURCC(ck.m_id) == cktypeDIBbits) ||
				(TWOCCFromFOURCC(ck.m_id) == cktypeDIBcompressed) ||
				(TWOCCFromFOURCC(ck.m_id) == cktypeWAVEbytes))
	{
		ErrorCode hr = Error;

		int streamNumber = StreamFromFOURCC(ck.m_id);
		if (streamNumber < m_streams.GetSize())
		{
			CAVIStream* pAVIStream = m_streams[streamNumber];

			bool bBuffer = false;

			if (p == pAVIStream && n == pAVIStream->m_sampleEntries.GetSize())
			{
				bBuffer = true;
			}

			CChunkEntry chunkEntry;
			chunkEntry.m_chunkOffset = GetPos(m_stream);
			chunkEntry.m_chunkLength = ck.m_size;

		//	TRACE("%d\n", chunkEntry.m_chunkOffset);

			pAVIStream->m_sampleEntries.Add(chunkEntry);

			// If the file is interleaved, we always buffer and read the data
			// in the expectation that it will soon be played, and then released

			if (m_mainAVIHeader.dwFlags & AVIF_ISINTERLEAVED)
			{
				// TODO, check that the output pin is connected, no need to buffer
				// sample if it's not going to be sent downstream

				// But have a limit on the number of buffered samples, in case
				// the file isn't interleaved after all (wrong info in mainHeader)
				if (pAVIStream->m_bufferedSamples.GetSize() < 4)
					bBuffer = true;
			}

			if (bBuffer && pAVIStream->m_outputPin)
			{
				IMediaSample* sample;
				pAVIStream->m_outputPin->m_pAllocator->GetBuffer(ck.m_size, &sample);
				ASSERT(sample);
				if (sample)
				{
					CBufferedSample* pBufferedSample = new CBufferedSample;
					pBufferedSample->m_nSample = pAVIStream->m_sampleEntries.GetSize()-1;
					pBufferedSample->m_sample = sample;

					pAVIStream->m_bufferedSamples.Add(pBufferedSample);

					if (sample)
					{
						ReadChunkData(sample, ck.m_size);
					}
				}
			}
		}
	}

	ck.Ascend(m_stream);

	m_criticalSection.Unlock();

	return Success;
}

ErrorCode AVISplitter::ReadChunkData(IMediaSample* sample, ULONG size)
{
// The file already has critical section lock when entering this function

	ErrorCode hr = Error;	// Assume failure at first

	LSampleData sampledata;
	if (sample->LockBits(&sampledata) >= 0)
	{
		ULONG nRead;
		nRead = m_stream->Read(sampledata.idata, size);
		if (nRead == size)
		{
			sample->SetActualDataLength(size);
			hr = Success;	// Success
		}

		sample->UnlockBits();
	}

	return hr;
}

}	// Media
}
