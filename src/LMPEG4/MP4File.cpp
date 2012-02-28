#include "stdafx.h"
#include "LMPEG4.h"

#include "MP4File.h"

namespace System
{
namespace Mpeg4
{

StringW* ReadString(IO::CBitStream32* pBitStream)
{
	StringW* str;// = L"";
	int c;
	while ((c = pBitStream->getnbits(8)) != 0)
	{
		ASSERT(0);
#if 0
		str += c;
#endif
	}

	return str;
}

ErrorCode Atom::Seek(Stream& stream)
{
	stream.Seek(m_contentpos, IO::STREAM_SEEK_SET);
	return Success;
}

ErrorCode Atom::Descend(Stream& stream)
{
	m_pos = stream.Seek(0, IO::STREAM_SEEK_CUR);

	ULONG nRead;

	uint32 size;
	nRead = stream.Read(&size, 4);
	size = BigEndian32(size);
	if (nRead == 0)
		return Success_False;

	nRead = stream.Read(&m_atomtype, 4);

	if (size == 1)
	{
		nRead = stream.Read(&m_size, 8);
		// TODO endian
		ASSERT(0);
	}
	else
		m_size = size;

	if (m_atomtype == ID_uuid)
	{
		nRead = stream.Read(&m_usertype, 16);
	}

	m_contentpos = stream.Seek(0, System::IO::STREAM_SEEK_CUR);

	m_contentsize = m_size - (m_contentpos - m_pos);

	return Success;
}

ErrorCode Atom::Ascend(Stream& stream)
{
	LONGLONG curpos = stream.Seek(0, IO::STREAM_SEEK_CUR);

	LONGLONG endpos = m_pos + m_size;

	if (curpos > endpos)
	{
		ASSERT("Read past chunk size\n");
		return Error;
	}

	stream.Seek(endpos, IO::STREAM_SEEK_SET);

	return Success;
}

void AtomCollection::Add(Atom& atom)
{
	m_items.Add(atom);
}

Atom* AtomCollection::GetAtom(uint32 atomtype)
{
	for (int i = 0; i < m_items.GetSize(); i++)
	{
		if (m_items[i].m_atomtype == atomtype)
		{
			return &m_items[i];
		}
	}

	return NULL;
}

BaseDescriptor::BaseDescriptor()
{
	m_tag = 0;
	m_sizeOfInstance = -1;
}

bool BaseDescriptor::More(Stream& stream)
{
	ASSERT(m_tag != 0);
	ASSERT(m_sizeOfInstance != -1);

	LONGLONG curpos = stream.Seek(0, IO::STREAM_SEEK_CUR);

	if ((m_pos+m_sizeOfInstance) > curpos)
		return true;
	else
		return false;
}

ErrorCode BaseDescriptor::Descend(Stream& pStream)
{
//		try	// catch any errors in bitstream calls
	{
		//pBitStream->byte_align();

		//m_tag = pBitStream->getnbits(8);
		pStream.Read(&m_tag, 1);

	//	int nextByte = pBitStream->getbit();
	//	m_sizeOfInstance = pBitStream->getnbits(7);
		uint8 byte;
		pStream.Read(&byte, 1);

		m_sizeOfInstance = byte & 127;

		while (byte & 128)
		{
//				nextByte = pBitStream->getbit();
			pStream.Read(&byte, 1);
			//int sizeByte = pBitStream->getnbits(7);
			m_sizeOfInstance <<= 7;
			m_sizeOfInstance |= byte & 127;
		}

		m_pos = pStream.Seek(0, IO::STREAM_SEEK_CUR);
		return Success;
	}
/*		catch (ErrorCode hr)
	{
		return hr;
	}
*/	}

ErrorCode BaseDescriptor::Ascend(Stream& pStream)
{
	LONGLONG curpos = pStream.Seek(0, IO::STREAM_SEEK_CUR);

	LONGLONG endpos = m_pos + m_sizeOfInstance;

	if (curpos > endpos)
	{
		ASSERT("Read past descriptor size\n");
		ASSERT(0);
		//throw L"Read past descriptor size";
		return Error;
	}

#if 0
	ASSERT(curpos.QuadPart == endpos.QuadPart);	// In debug mode, we make sure we've read all of it
#endif

	pStream.Seek(endpos, IO::STREAM_SEEK_SET);
	return Success;
}

ErrorCode MovieHeader::Read(Stream& stream)
{
	ULONG nRead;

	uint32 verflags;
	nRead = stream.Read(&verflags, 4);
	verflags = BigEndian32(verflags);
	uint8 version = (uint8)(verflags>>24);

	if (version == 1)
	{
		ULONGLONG creationTime;
		nRead = stream.Read(&creationTime, 8);

		ULONGLONG modificationTime;
		nRead = stream.Read(&modificationTime, 8);

		nRead = stream.Read(&m_timeScale, 4);
		m_timeScale = BigEndian32(m_timeScale);

		ULONGLONG duration;
		nRead = stream.Read(&duration, 8);
	}
	else if (version == 0)
	{
		ULONG creationTime;
		nRead = stream.Read(&creationTime, 4);

		ULONG modificationTime;
		nRead = stream.Read(&modificationTime, 4);

		nRead = stream.Read(&m_timeScale, 4);
		m_timeScale = BigEndian32(m_timeScale);

		ULONG duration;
		nRead = stream.Read(&duration, 4);
	}
	else
		ASSERT(0);

	return Success;
}

ErrorCode InitialObjectDescriptor::Read(Stream& stream)
{
	ULONG nRead;

	uint32 verflags;
	nRead = stream.Read(&verflags, 4);
	verflags = BigEndian32(verflags);
	uint8 version = (uint8)(verflags>>24);

	BaseDescriptor descr;
	descr.Descend(stream);

	if (descr.m_tag == 0x01)	// ObjectDescrTag
	{
		VERIFY(0);
	}
	else if (descr.m_tag == 0x02)	// InitialObjectDescrTag
	{
		VERIFY(0);
	}
	else if (descr.m_tag == 0x10)	// MP4_IOD_Tag
	{
	//	System::IO::CBitStream bitstream(new System::IO::CByteStream(stream));
	//	System::IO::CBitStream32* pBitStream = &bitstream;

		uint16 word = ReadByte(stream)<<8;
		word |= ReadByte(stream);

	//	stream->Read(&word, 2);
	//	word = BigEndian16(word);

		m_ObjectDescriptorID = word >> 6;//pBitStream->getnbits(10);
		int bURLFlag = (word>>5) & 1;//pBitStream->getbit();// URL_Flag;
		int includeInlineProfileLevelFlag = (word>>4) & 1;//pBitStream->getbit();
		int reserved = word & 15;//pBitStream->getnbits(4); // reserved=0b1111;
		ASSERT(reserved == 0xf);

		if (bURLFlag)
		{
			uint8 URLlength;
			//= pBitStream->getnbits(8);// URLlength;
			//bit(8) URLstring[URLlength];
			ASSERT(0);
		}
		else
		{
			uint8 ODProfileLevelIndication = ReadByte(stream);
			uint8 sceneProfileLevelIndication = ReadByte(stream);
			uint8 audioProfileLevelIndication = ReadByte(stream);
			uint8 visualProfileLevelIndication = ReadByte(stream);
			uint8 graphicsProfileLevelIndication = ReadByte(stream);

			while (descr.More(stream))
			{
				BaseDescriptor descr2;
				descr2.Descend(stream);

				if (descr2.m_tag == 0x0E)	// ES_ID_IncTag
				{
					uint32 Track_ID;
					stream.Read(&Track_ID, 4);//= pBitStream->getnbits(32);
					Track_ID = BigEndian32(Track_ID);
					m_trackID.Add(Track_ID);
				}
				else
				{
					MessageBeep(-1);
				}

				descr2.Ascend(stream);
			}
			/*
			ES_Descriptor esDescr[1 .. 255];
			OCI_Descriptor ociDescr[0 .. 255];
			IPMP_DescriptorPointer ipmpDescrPtr[0 .. 255];
			*/
		}

		//ExtensionDescriptor extDescr[0 .. 255];
	}
	else
		ASSERT(0);

	descr.Ascend(stream);

	return Success;
}

/////////////////////////////////////////////////////////////////////////////
// Movie

Movie::Movie()
{
	/*
	m_pInputPin = new CInputPin;
	m_pInputPin->m_pFilter = this;
	m_pInputPin->m_id = L"Stream Input";
	AddPin(m_pInputPin);
	*/
}

ErrorCode Movie::ReceiveObjectDescriptorUpdate(Track* pTrack, int ODid, uint16 refIndex)
{
	// Remove any previous
	for (int i = 0; i < m_od.GetSize(); i++)
	{
		if (m_od[i]->m_ObjectDescriptorID == ODid)
		{
			delete m_od[i];
			m_od.RemoveAt(i);
			break;
		}
	}

	ObjectDescriptor* pOD = new ObjectDescriptor;
	pOD->m_pTrack = pTrack;
	pOD->m_ObjectDescriptorID = ODid;
	pOD->m_refIndex = refIndex;

	m_od.Add(pOD);

// TODO wait

	return Success;
}

Track* Movie::GetTrackById(uint32 trackID)
{
	for (int i = 0; i < m_tracks.GetSize(); ++i)
	{
		if (m_tracks[i]->m_trackHeader.m_trackID == trackID)
		{
			return m_tracks[i];
		}
	}

	return NULL;
}

ErrorCode Movie::ReadCompressedMovie(Stream& stream, int64 atomStartPos, int64 atomSize)
{
	uint32 compression = 0;

	while (1)
	{
		// TODO, have it like this
		// while (More())

		{
			LONGLONG pos = stream.Seek(0, System::IO::STREAM_SEEK_CUR);

			if (pos >= (atomStartPos + atomSize))
			{
				ASSERT(pos == (atomStartPos + atomSize));
				return Success_False;
			}
		}

		Atom ck;
		if (ck.Descend(stream) == Success_False)
			return Success_False;

		TRACE("atomType: %4.4s, size: %d\n", &ck.m_atomtype, (uint32)ck.m_size);

		switch (ck.m_atomtype)
		{
		case ID_dcom:	// Data compression atom
			{
				ULONG nRead;

				nRead = stream.Read(&compression, 4);

				if (compression != zlibDataCompressorSubType)
				{
					TRACE("Unknown compression in dcom\n");
					return Error;
				}
			}
			break;

		case ID_cmvd:	// Compressed movie data
			{
				ASSERT(compression != 0);

				ULONG nRead;

				uint32 uncompressedSize;
				nRead = stream.Read(&uncompressedSize, 4);
				uncompressedSize = BigEndian32(uncompressedSize);

#if 0	// TODO
				uint8* source = (uint8*)GlobalAlloc(0, (DWORD)ck.m_contentsize);
				if (source)
				{
					nRead = stream->Read(source, (DWORD)ck.m_contentsize);

					HGLOBAL hGlobal = GlobalAlloc(0, uncompressedSize);
					if (hGlobal)
					{
						ASSERT(0);
						if (compression == zlibDataCompressorSubType)
						{
							LPBYTE dest = (LPBYTE)hGlobal;	// No need to GlobalLock
							DWORD destsize = uncompressedSize;
						//LONG CALLBACK DecodeLZ77(LPVOID dest, DWORD* destsize, LPVOID source, DWORD sourcesize)
							ASSERT(0);//
							int ret = -1;//::uncompress((LPBYTE)dest, &destsize, (LPBYTE)source, (DWORD)ck.m_contentsize);

							if (ret != Z_OK)
							{
								GlobalFree(source);
								GlobalFree(hGlobal);

								switch (ret)
								{
								case Z_MEM_ERROR: return E_OUTOFMEMORY; break;
								case Z_BUF_ERROR: return E_FAIL; break;// not enough room in dest
								case Z_DATA_ERROR: return E_FAIL; break;	// corrupted data
								}
							}
						}

						CComPtr<IStream> stream2;
						CreateStreamOnHGlobal(hGlobal, FALSE/*fDeleteOnRelease*/, &stream2);

						LONGLONG startpos;
						LONGLONG atomsize;
						startpos = 0;
						atomsize = uncompressedSize;

						ErrorCode hr;
						hr = ReadFile(stream2, startpos, atomsize);

						GlobalFree(hGlobal);

						return hr;
					}
					else
						return E_OUTOFMEMORY;

					GlobalFree(source);
				}
				else
					return E_OUTOFMEMORY;
#endif
			}
			break;
		}

		ck.Ascend(stream);
	}

	return Success;
}

ErrorCode Movie::ReadMovie(Stream& stream, int64 atomStartPos, int64 atomSize)
{
	while (1)
	{
		// TODO, have it like this
		// while (More())

		{
			LONGLONG pos = stream.Seek(0, IO::STREAM_SEEK_CUR);

			if (pos >= (atomStartPos + atomSize))
			{
				ASSERT(pos == (atomStartPos + atomSize));
				return Success_False;
			}
		}

		Atom ck;
		if (ck.Descend(stream) == Success_False)
			return Success_False;

		TRACE("atomType: %4.4s, size: %d\n", &ck.m_atomtype, (uint32)ck.m_size);

		switch (ck.m_atomtype)
		{
		case ID_cmov:	// If this is present, it should be the only one present under 'moov'
			{
				ReadCompressedMovie(stream, ck.m_pos, ck.m_size);
			}
			break;

		case ID_mvhd:
			{
				m_movieHeader.Read(stream);
			}
			break;

		case ID_iods:
			{
				m_initialObjectDescriptor.Read(stream);
			}
			break;

		case ID_trak:
			{
				Track* pTrack = new Track;

				pTrack->m_pMovie = this;

				ErrorCode hr = pTrack->Read(stream, ck.m_pos, ck.m_size);
				if (hr >= 0)
				{
					m_tracks.Add(pTrack);

					break;
				}
				else
				{
					delete pTrack;
					ASSERT(0);
				}
			}
			break;
		}

		ck.Ascend(stream);
	}

	return Success;
}

ErrorCode Movie::ReadFile(Stream& stream, int64 atomStartPos, int64 atomSize)
{
	while (1)
	{
		// TODO, have it like this
		// while (More())

		{
			LONGLONG pos = stream.Seek(0, IO::STREAM_SEEK_CUR);

			if (pos >= (atomStartPos + atomSize))
			{
				ASSERT(pos == (atomStartPos + atomSize));
				return Success_False;
			}
		}

		Atom ck;
		if (ck.Descend(stream) == Success_False)
			return Success_False;

		TRACE("atomType: %4.4s, size: %d\n", &ck.m_atomtype, (uint32)ck.m_size);

		switch (ck.m_atomtype)
		{
		case ID_moov:
			{
				ReadMovie(stream, ck.m_pos, ck.m_size);
			}
			break;
		}

		ck.Ascend(stream);
	}
}

bool Movie::ReadFile(StringIn filename)
{
	FileStream stream(filename, 1);
	return ReadFile(stream);
}

bool Movie::ReadFile(Stream& stream)
{
	int64 pos = stream.Seek(0, IO::STREAM_SEEK_CUR);
	int64 size = 0xfffffffffff;
	ReadFile(stream, pos, size);
	return true;
}

#if 0
ErrorCode MPEG4Movie::OpenStream(IStream *stream)
{
	m_stream = stream;

	while (1)
	{
		LONGLONG pos;
		LARGE_INTEGER li;
		li = 0;
		stream->Seek(li, System::IO::STREAM_SEEK_CUR, &pos);

		LONGLONG size;
		size = 0xfffffffffff;
		if (ReadFile(stream, pos, size) != S_OK)
			break;
	}

#if 0
	if (m_initialObjectDescriptor.m_trackID.GetSize() > 0)
	{
		CTrack* pTrack = GetTrackById(m_initialObjectDescriptor.m_trackID[0]);
		if (pTrack)
		{
			*pVal = pTrack->m_sampleDescriptions[0]->m_decoder;
			if (*pVal) (*pVal)->AddRef();
		}
	}
#endif

	return S_OK;
}
#endif

#if 0
ErrorCode MPEG4Movie::CInputPin::CompleteConnect(ILPin* pPin)
{
	ErrorCode hr;
	hr = CLBasePinImpl::CompleteConnect(pPin);
	if (FAILED(hr)) return hr;

	LONGLONG pos = m_pFilter->m_stream->Seek(0, System::IO::STREAM_SEEK_CUR);

	LONGLONG size;
	size = 0xfffffffffff;
	hr = m_pFilter->ReadFile(m_pFilter->m_stream, pos, size);
	if (SUCCEEDED(hr))
		return S_OK;
	else
		return hr;

#if 0
	ASSERT(m_pFilter->m_pVideo == NULL);
	CComObject<CVideoSequence>::CreateInstance(&m_pFilter->m_pVideo);
	m_pFilter->m_pVideo->m_pFilter = m_pFilter;
	m_pFilter->AddPin(m_pFilter->m_pVideo);

	m_pFilter->m_pVideo->m_file = new System::IO::CBitStream(stream);
	m_pFilter->m_pVideo->m_file->next_start_code();

	return m_pFilter->m_pVideo->video_sequence();
#endif
	return -1;
}
#endif

#if 0
// ILBaseFilter
STDMETHODIMP MPEG4Movie::Run(LONGLONG tStart)
{
	m_criticalSection.Lock();

	m_state = LState_Running;
	m_tStart = tStart;

	for (int i = 0; i < m_initialObjectDescriptor.m_trackID.GetSize(); i++)
	{
		CTrack* pTrack = GetTrackById(m_initialObjectDescriptor.m_trackID[i]);
		if (pTrack)
		{
			if (pTrack->m_sampleDescriptions[0]->m_decoder)
			{
				pTrack->m_sampleDescriptions[0]->m_decoder->Run(tStart);
			}
		}
	}

	m_criticalSection.Unlock();

	return S_OK;
}
#endif

}	// Media
}
