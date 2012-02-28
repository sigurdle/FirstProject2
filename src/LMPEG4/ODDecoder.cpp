#include "stdafx.h"
#include "LMPEG4.h"
#include "ODDecoder.h"

namespace System
{
namespace MediaShow
{

/////////////////////////////////////////////////////////////////////////////
// ODDecoder

// ILMediaFilter

static DWORD WINAPI RunningThreadProc(
  LPVOID lpParameter   // thread data
)
{
//	CoInitialize(NULL);

	ODDecoder* p = (ODDecoder*)lpParameter;

#if 0
	HRESULT hr;

//	EnterCriticalSection(&pFilter->m_pLock);

	CComQIPtr<ILMemInputPin> memInput = p->m_pOutputPin->m_connectedTo;
	if (memInput)
	{
		CComObject<CBIFSDecoder::CLBIFSSample>* sample;
		CComObject<CBIFSDecoder::CLBIFSSample>::CreateInstance(&sample);
		sample->AddRef();

#if 0
		if (pVideo->m_sample == NULL)
		{
			pVideo->m_allocator->GetBuffer(0, (ILMediaSample**)&pVideo->m_sample);
		}
#endif
#endif

		p->m_stream.Seek(p->m_pTrack->m_chunks[0].m_offset, System::IO::STREAM_SEEK_SET);

		double t = 0;

		for (uint i = 0; i < p->m_pTrack->m_samples.GetSize(); i++)
		{
			//System::IO::CBitStream bitstream(p->m_stream);

			Mpeg4::BaseDescriptor descr;
			descr.Descend(p->m_stream);

			if (descr.m_tag == 0x01)	// ObjectDescrUpdateTag
			{
				//OD[1..255]
				while (descr.More(p->m_stream))
				{
					Mpeg4::BaseDescriptor descr2;
					descr2.Descend(p->m_stream);

					if (descr2.m_tag == 0x11)	// MP4_OD_Tag
					{
						//System::IO::CBitStream* pBitStream = &bitstream;

						uint16 word = ReadByte(p->m_stream)<<8;
						word |= ReadByte(p->m_stream);

						int ObjectDescriptorID = word >> 6;//pBitStream->getnbits(10);
						int URL_Flag = (word>>7) & 1;//pBitStream->getbit();
						int reserved = word>>11;//pBitStream->getnbits(5);//
						if (reserved != 0x1f)	// 0b1111.1;
						{
							ASSERT(0);
							return Error;// throw L"Error in bitstream"
						}

						if (URL_Flag)
						{
							ASSERT(0);
							return Error;	// throw L"Currently Unsupported"
		#if 0
							bit(8) URLlength;
							bit(8) URLstring[URLlength];
		#endif
						}
						else
						{
							while (descr2.More(p->m_stream))
							{
								Mpeg4::BaseDescriptor descr3;
								descr3.Descend(p->m_stream);

								if (descr3.m_tag == 0x0F)	// ES_ID_RefTag
								{
									uint16 ref_index = ReadByte(p->m_stream)<<8;//pBitStream->getnbits(16);	// Index of track to use
									ref_index |= ReadByte(p->m_stream);

									p->m_pTrack->m_pMovie->ReceiveObjectDescriptorUpdate(p->m_pTrack, ObjectDescriptorID, ref_index);
								}
								else
								{
									ASSERT(0);
									return Error;	// throw L"Unsupported"
								}

								descr3.Ascend(p->m_stream);
							}

		#if 0
							CBaseDescriptor d;
							d.Descend(pBitStream);

							CESDescriptor esdescriptor;
							esdescriptor.Read(stream, &d, this);

							d.Ascend(pBitStream);

							ES_Descriptor esDescr[1 .. 255];
							OCI_Descriptor ociDescr[0 .. 255];
							IPMP_DescriptorPointer ipmpDescrPtr[0 .. 255];
		#endif
							while (descr2.More(p->m_stream))
							{
								Mpeg4::BaseDescriptor descr3;
								descr3.Descend(p->m_stream);

								if (descr3.m_tag == 0x0E)	// ES_ID_IncTag
								{
									uint32 Track_ID = ReadByte(p->m_stream)<<24;
									Track_ID |= ReadByte(p->m_stream)<<16;
									Track_ID |= ReadByte(p->m_stream)<<8;
									Track_ID |= ReadByte(p->m_stream);
								}
								else
								{
									ASSERT(0);
									return Error;	// throw L"Unsupported"
								}

								descr3.Ascend(p->m_stream);
							}

						}
		#if 0
						ExtensionDescriptor extDescr[0 .. 255];
		#endif
					}
					else
						ASSERT(0);

					descr2.Ascend(p->m_stream);
				}
			}
			else
			{
				ASSERT(0);
				return Error;	// throw L"Currently unsupported"
			}

			descr.Ascend(p->m_stream);

			//p->ReadBIFSCommandFrame(p->m_stream);
			//sample->m_scene = p->m_scene;

			double duration = (double)p->m_pTrack->m_samples[i].m_duration / p->m_pTrack->m_pMovie->m_movieHeader.m_timeScale;

			double timeStart = t;
			double timeEnd = t+duration;
			//sample->SetTime(&timeStart, &timeEnd);

			t += duration;

			/*
			hr = memInput->Receive(sample);
			if (FAILED(hr) || hr == S_FALSE)
			{
				break;
			}
			*/
		}
#if 0
	}

	if (SUCCEEDED(hr))	// Don't send this if the downstream filter failed in Receive?
		p->m_pOutputPin->m_connectedTo->EndOfStream();
#endif

//	CoUninitialize();

	return 0;
}

ErrorCode ODDecoder::Run(LONGLONG tStart)
{
	m_criticalSection.Lock();

	m_state = State_Running;
	m_tStart = tStart;

	m_criticalSection.Unlock();

	ASSERT(m_hThread == NULL);
	ASSERT(0);
#if 0
	m_hThread = CreateThread(NULL, NULL, RunningThreadProc, (LPVOID)(ODDecoder*)this, 0, &m_threadId);
#endif

	return Success;
}

}	// Media
}
