#include "stdafx.h"
#include "VOCLoader.h"
#include <stdio.h>

namespace System
{
using namespace IO;

namespace MediaShow
{

int DATABLOCK::Read(IO::Stream* stream)
{
	uint8 data[4];
	size_t nRead = stream->Read(data, 4);
	if (nRead < 4)
		return 0;

	type = (BlockType)data[0];

	size = data[1];
	size |= data[2]<<8;
	size |= data[3]<<16;

	return 4;
}

VOCLoader::VOCLoader()
{
	m_nSamples = 0;
	m_nPos = 0;
}

VOCLoader::~VOCLoader()
{
}

void VOCLoader::Open(IO::Stream* stream)
{
	m_stream = stream;
}

ErrorCode VOCLoader::ReadFormatSignature()
{
	size_t nRead;
	nRead = m_stream->Read(&m_hdr, sizeof(VOCHEADER));
	if (nRead != sizeof(VOCHEADER))
	{
		return Error_Failed;
	}

	m_hdr.offset = LittleEndian16(m_hdr.offset);

	if (strncmp(m_hdr.signature, "Creative Voice File", 19) != 0)
	{
		return Error_Failed;//FORMAT_UNKNOWN;
	}

	return Success;
}

ErrorCode_Bool VOCLoader::ReadHeader()
{
	m_stream->Seek(m_hdr.offset, IO::SeekOrigin_Start);

	size_t nRead;
	bool bFoundHeader = false;

	DATABLOCK block;
	block.Read(m_stream);
	while (block.type != 0)
	{
		DebugTraceLn("block type: " << block.type);

	// Get current file position of block data
		LONGLONG blockdatapos;
		blockdatapos = m_stream->GetPosition();

		switch (block.type)
		{
		case VOC_Sound_Data:
			{
				SOUNDBLOCK1	sound;

				nRead = m_stream->Read(&sound, sizeof(sound));
				if (nRead != sizeof(sound))
				{
					return Error_Failed;	// Complete failure, since we can't do anything without header
				}

				ULONG sampleRate = 1000000/(256-sound.sampleRate);

				if (sound.compression != 0)
				{
					char errorMsg[256];
					sprintf_s(errorMsg, "Unknown compression %d", sound.compression);
				//	MessageBox(NULL, errorMsg, "VOC", MB_OK);
					return Error_Failed;
				}

				m_compression = 4;	// PCM

				m_wfx.wFormatTag = WAVE_FORMAT_PCM;
				m_wfx.nChannels = 1;
				m_wfx.nSamplesPerSec = sampleRate;
				m_wfx.wBitsPerSample = 8;
				m_wfx.nBlockAlign = 1;
				m_wfx.nAvgBytesPerSec = m_wfx.nBlockAlign * m_wfx.nSamplesPerSec;
				m_wfx.cbSize = 0;

				ULONG	nSamples = block.size-sizeof(SOUNDBLOCK1);

				m_nSamples += nSamples;

				/*
			// Get current file position
				LONGLONG pos;
				pos = m_stream->Seek(0, STREAM_SEEK_CUR);

				int nbytesPerSample = 1;

				DWORD countSamples = 0;
				while (countSamples < nSamples)
				{
					CChunk* pChunk = new CChunk;

					pChunk->m_fileOffset = pos + countSamples*nbytesPerSample;

					pChunk->m_nSamples = CHUNKSAMPLES;
					if (countSamples+pChunk->m_nSamples > nSamples)
						pChunk->m_nSamples = nSamples - countSamples;

					countSamples += pChunk->m_nSamples;

					m_chunks.AddTail(pChunk);
				}
					*/
				bFoundHeader = true;
			}
			break;

			case VOC_Extended_Sound_data:
			{
				SOUNDBLOCK9	sound;

				nRead = m_stream->Read(&sound, sizeof(sound));
				if (nRead != sizeof(sound))
				{
					return Error;	// Complete failure, since we can't do anything without header
				}

				sound.sampleRate = LittleEndian16(sound.sampleRate);

				if (sound.channels != 1 && sound.channels != 2)
				{
					char errorMsg[256];
					sprintf_s(errorMsg, "Unsupported number of channels %d", sound.channels);
				//	MessageBox(NULL, errorMsg, "VOC", MB_OK);
					return Error_Failed;
				}

				if (sound.bits != 8 && sound.bits != 16)
				{
					char errorMsg[256];
					sprintf_s(errorMsg, "Unsupported sampledepth %d", sound.bits);
				//	MessageBox(NULL, errorMsg, "VOC", MB_OK);
					return Error_Failed;
				}

				if (sound.compression != 4 && sound.compression != 6 && sound.compression != 7)
				{
					char errorMsg[256];
					sprintf_s(errorMsg, "Unknown compression %d", sound.compression);
				//	MessageBox(NULL, errorMsg, "VOC", MB_OK);
					return Error_Failed;
				}

				m_compression = sound.compression;

				m_wfx.wFormatTag = WAVE_FORMAT_PCM;
				m_wfx.nChannels = sound.channels;
				m_wfx.nSamplesPerSec = sound.sampleRate;
				m_wfx.cbSize = 0;

				int nbytesPerSample;	// As stored in the file

				if (sound.compression == 4)	// PCM
				{
					m_wfx.wBitsPerSample = sound.bits;
					nbytesPerSample = (sound.channels * sound.bits)/8;
				}
				else	// u-law / A-law
				{
					m_wfx.wBitsPerSample = 16;
					nbytesPerSample = sound.channels;
				}

				m_wfx.nBlockAlign = (sound.channels * sound.bits) / 8;
				m_wfx.nAvgBytesPerSec = m_wfx.nBlockAlign * m_wfx.nSamplesPerSec;

				uint size = block.size-12;
				uint nSamples = size / m_wfx.nBlockAlign;

				m_nSamples += nSamples;

				/*
				LONGLONG pos = m_stream->Seek(0, STREAM_SEEK_CUR);

				DWORD countSamples = 0;
				while (countSamples < nSamples)
				{
					CChunk* pChunk = new CChunk;

					pChunk->m_fileOffset = pos + countSamples*nbytesPerSample;

					pChunk->m_nSamples = CHUNKSAMPLES;
					if (countSamples+pChunk->m_nSamples > nSamples)
						pChunk->m_nSamples = nSamples - countSamples;

					countSamples += pChunk->m_nSamples;

					m_chunks.AddTail(pChunk);
				}
				*/

			//	voc->offset = r->GetFilePos(r->file);
				bFoundHeader = true;
			}
			break;

			case VOC_Sound_continue:
			{
				//MessageBox(NULL, "Sound continue block, Notify author", "VOC", MB_OK);
			}
			break;

			case VOC_Silence:
			{
				//MessageBox(NULL, "Silence, Notify author", "VOC", MB_OK);
			}
			break;
		}

		if (bFoundHeader)
			break;

	// Get current file position
		uint64 pos = m_stream->GetPosition();

	// Seek to beginning of next block
		m_stream->Seek(block.size - (pos-blockdatapos), System::IO::STREAM_SEEK_CUR);

// Note: terminator block only has one byte, so nRead will be 1 in that case
//		nRead = m_stream->Read(&block, sizeof(block));	// read next block
		nRead = block.Read(m_stream);
		if (nRead == 0)
			return Success_False;	// Partial success
	}

	return Success_True;
}

size_t VOCLoader::ReadSamples(ubyte* dest, size_t nSamples)
{
	if (m_nPos + nSamples > m_nSamples)
	{
		nSamples = m_nSamples - m_nPos;
	}

	if (m_compression == 4)	// PCM
	{
		size_t nBytesToRead = nSamples * m_wfx.nBlockAlign;

		m_stream->Read(dest, nBytesToRead);

#if 1
		if (m_wfx.wBitsPerSample == 8)	// unsigned -> signed
		{
			ubyte* p = dest;
			while (nBytesToRead--)
			{
				*p += 128;
				p++;
			}
		}
#endif
	}
	else
		ASSERT(0);

	m_nPos += nSamples;

	return nSamples;
}

}	// Media
}	// System
