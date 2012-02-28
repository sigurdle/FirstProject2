#include "stdafx.h"
#include "ZIP.h"

namespace System
{
namespace ZIP
{

FileRawStream::FileRawStream(IO::Stream* stream, uint64 beginpos, uint64 size) :
	m_pos(0)
{
	ASSERT(0);
	m_stream = stream;//->Clone();
	m_beginpos = beginpos;
	m_size = size;

	m_stream->Seek(beginpos, IO::STREAM_SEEK_SET);
}

FileRawStream::~FileRawStream()
{
}

uint FileRawStream::Read(void* pv, uint cb)
{
	if (m_pos + cb > m_size)
		cb = m_size-m_pos;

	m_stream->Seek(m_beginpos + m_pos, System::IO::STREAM_SEEK_SET);
	size_t nRead = m_stream->Read(pv, cb);
	m_pos += nRead;

	return nRead;
}

uint FileRawStream::Write(const void* pv, uint cb)
{
	ASSERT(0);
	throw new Exception(WSTR("not implemented"));
	return 0;
}

uint64 FileRawStream::Seek(int64 move, IO::SeekOrigin origin)
{
	if (origin == IO::STREAM_SEEK_CUR)
	{
		m_pos += move;
	}
	else if (origin == IO::STREAM_SEEK_SET)
	{
		m_pos = move;
	}
	else if (origin == IO::STREAM_SEEK_END)
	{
		m_pos = m_size - move;
	}

	return m_pos;
}

uint64 FileRawStream::GetSize()
{
	return m_size;
}

//////////////

Archive::Archive()
{
	m_p = new _Archive;
}

Archive::Archive(IO::Stream* stream)
{
	m_p = new _Archive;
	Open(stream);
}

Archive::~Archive()
{
	delete m_p;
}

short Archive::getshort()
{
	short v;
	if (m_p->m_stream->Read(&v, 2) != 2) raise(IO::IOException("IO Error"));
	return LittleEndian16(v);
}

int32 Archive::getint32()
{
	int32 v;
	if (m_p->m_stream->Read(&v, 4) != 4) raise(IO::IOException("IO Error"));
	return LittleEndian32(v);
}

void Archive::Open(IO::Stream* stream)
{
	m_p->m_stream = stream;

	TRY
	{
		uint32 signature;
		while ((signature = getint32()) == 0x04034b50)
		{
			File* file = new File(this);

			file->m_bytepos = m_p->m_stream->GetPosition();

			uint16 version_needed_to_extract = getshort();//       2 bytes
			uint16 general_purpose_bit_flag = getshort();//        2 bytes
			file->m_compression_method = getshort();//              2 bytes
			uint16 last_mod_file_time = getshort();//              2 bytes
			uint16 last_mod_file_date = getshort();//              2 bytes
			file->m_crc_32 = getint32();//                          4 bytes
			file->m_compressed_size = getint32();//                 4 bytes
			file->m_uncompressed_size = getint32();//               4 bytes
			uint16 file_name_length = getshort();//                2 bytes
			uint16 extra_field_length = getshort();//              2 bytes

			file->m_name = String(string_alloc<char>(file_name_length));
			m_p->m_stream->Read(file->m_name.GetData8(), file_name_length);

			m_p->m_stream->Seek(extra_field_length, IO::STREAM_SEEK_CUR);

			file->m_dataoffset = m_p->m_stream->GetPosition() - file->m_bytepos;
			m_p->m_stream->Seek(file->m_compressed_size, IO::STREAM_SEEK_CUR);

			m_p->m_filesByName[file->m_name] = file;
			m_p->m_files.push_back(file);
		}

		while (signature == 0x02014b50)
		{
			signature = getint32();
		}
	}
	CATCH (Exception* e)
	{
	}
}

File* Archive::FindFile(StringIn pathname)
{
	return m_p->m_filesByName[pathname];
}

bool Archive::Check()
{
	unsigned int nErrors = 0;
	for (unsigned int i = 0; i < m_p->m_files.GetSize(); i++)
	{
		File* file = m_p->m_files[i];

		if (!file->Check())
		{
			nErrors++;
			TRACE("...crc error");
		}
	}

	return nErrors == 0;
}

uint Archive::GetFileCount()
{
	return m_p->m_files.GetSize();
}

File* Archive::GetFile(uint index)
{
	if (index >= m_p->m_files.size())
	{
		raise(ArgumentOutOfRangeException());
	}

	return m_p->m_files[index];
}

File* Archive::OpenFile(StringIn file)
{
	for (uint i = 0; i < m_p->m_files.GetSize(); ++i)
	{
		if (m_p->m_files[i]->m_name == file)
		{
			return m_p->m_files[i];
		}
	}

	return NULL;
}

////////////////

File::File(Archive* ar) : m_ar(ar)
{
}

String File::GetName()
{
	return m_name;
}

bool File::Check()
{
	_Ptr<IO::Stream> stream(GetStream());
	uint32 crc = CalculateCRC32(stream, 0xffffffffL) ^ 0xffffffffL;
	return crc == m_crc_32;
}

_Ptr<IO::Stream> File::GetRawStream()
{
	FileRawStream* rawstream = new FileRawStream(m_ar->m_p->m_stream, m_bytepos+m_dataoffset, m_compressed_size);
	return rawstream;
}

_Ptr<IO::Stream> File::GetStream()
{
	FileRawStream* rawstream = new FileRawStream(m_ar->m_p->m_stream, m_bytepos+m_dataoffset, m_compressed_size);

	if (m_compression_method == 0)	// No compression
	{
		return rawstream;
	}
	else if (m_compression_method == 8)	// Deflate
	{
		IO::Inflate* stream = new IO::Inflate(rawstream, 7/*compressionInfo*/, m_uncompressed_size);
		return stream;
	}
	else
	{
		raise(ZipException("Unknown compression method"));
		return NULL;
	}
}

}	// ZIP
}
