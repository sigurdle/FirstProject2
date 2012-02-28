#include "stdafx.h"
#include "LFC.h"
#include "RIFF.h"

namespace System
{
namespace Riff
{

CChunk::CChunk()
{
	m_size = 0;
	m_dwFlags = 0;
}

int CChunk::Descend(IO::Stream& stream)
{
//	int hr;

	ULONG nRead;

	nRead = stream.Read(&m_id, 4);
//	if (FAILED(hr)) return hr;
	if (nRead != 4) return 1;//E_FAIL; End of file

	nRead = stream.Read(&m_size, 4);
	//if (FAILED(hr)) return hr;
	if (nRead != 4) return -1;

	m_pos = stream.Seek(0, IO::STREAM_SEEK_CUR);
	//if (FAILED(hr)) return hr;

	if (m_id == mmioFOURCC('R','I','F','F') || m_id == mmioFOURCC('L','I','S','T'))
	{
		nRead = stream.Read(&m_grpid, 4);
	//	if (FAILED(hr)) return hr;
		if (nRead != 4) return -1;
	}
	else
		m_grpid = 0;

	return 0;
}

int CChunk::Ascend(IO::Stream& stream)
{
//	int hr;

	LONGLONG curpos;
	curpos = stream.Seek(0, IO::STREAM_SEEK_CUR);

	if (m_dwFlags == 0)
	{
	//	if (FAILED(hr)) return hr;

		LONGLONG li = m_pos+m_size;
		if (m_size & 1) li++;	// Word-aligned chunks

		if (curpos > li)
		{
			DebugTrace("Read past chunk");
			ASSERT(0);
			return -1;
		}

		stream.Seek(li, IO::STREAM_SEEK_SET);
	}
	else
	{
		ULONG cksize = (ULONG)(curpos - m_pos);

		if (m_size == 0)	// Unknown size data at time of chunk creation
		{
			m_size = cksize;
			cksize = LittleEndian32(cksize);

			stream.Seek(m_pos-4, IO::STREAM_SEEK_SET);
			stream.Write(&cksize, 4);	// Write the chunk length

			stream.Seek(curpos, System::IO::STREAM_SEEK_SET);
		}

		if (cksize & 1)
		{
			uint8 padbyte = 0;
			stream.Write(&padbyte, 1);
		}
	}

	return 0;
}

int CChunk::Create(IO::Stream& m_stream)
{
	m_dwFlags = 1;	// Created

	ULONG id = LittleEndian32(m_id);
	ULONG size = LittleEndian32(m_size);

	m_stream.Write(&id, 4);
	m_stream.Write(&size, 4);
	m_pos = m_stream.Seek(0, IO::STREAM_SEEK_CUR);

	if (m_id == mmioFOURCC('R','I','F','F') || m_id == mmioFOURCC('L','I','S','T'))
	{
		ULONG grpID = LittleEndian32(m_grpid);
		m_stream.Write(&grpID, 4);
	}

	return 0;
}

}	// Riff
}
