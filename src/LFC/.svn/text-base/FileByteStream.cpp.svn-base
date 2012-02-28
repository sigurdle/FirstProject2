#include "stdafx.h"

#if AMIGA

//#define renameDOSBase DOSBase

#include "../amiga_header.h"
#include <stdio.h>

//BPTR dosOpen(struct DosLibrary* DOSBase, const char* filename, int mode)

#endif

#include "LFC.h"

/*
#if WIN32
#include "../include/windows_header.h"
#endif
*/
#if __APPLE__
#include <Carbon/Carbon.h>
#endif

//using namespace System;
//using namespace System::IO;

namespace System
{
namespace IO
{

#if 0
LFCEXT Stream& operator << (Stream& stream, FileMode mode)
{
	switch (mode)
	{
	case FileMode_Read: stream << "Read";break;
	case FileMode_Write: stream << "Write";break;
	case FileMode_ReadWrite: stream << "ReadWrite";break;
	default:
		ASSERT(0);
	}
	return stream;
}


FileByteStream::FileByteStream()// : m_refcount(0)
{
#if WIN32
	m_hFile = INVALID_HANDLE_VALUE;
#elif AMIGA
	m_hFile = 0;
#elif __APPLE__
	m_forkRefNum = 0;
#endif
	m_bOwnHandle = true;
	m_lastStatus = 0;
}

#if WIN32

FileByteStream* FileByteStream::FromHandle(HANDLE hFile, bool bOwnHandle)
{
	FileByteStream* p = new FileByteStream;

	p->m_bOwnHandle = bOwnHandle;
	p->m_hFile = hFile;
	p->m_lastStatus = 0;

	return p;
}

#elif AMIGA

FileByteStream::FileByteStream(BPTR hFile, bool bOwnHandle)/* : m_refcount(0)*/
{
	m_bOwnHandle = bOwnHandle;
	m_hFile = hFile;
	m_lastStatus = 0;
}

#endif

FileByteStream::FileByteStream(StringIn filename, FileMode mode)
{
	Open(filename, mode);
}

/*
FileByteStream::FileByteStream(const char* filename) : m_refcount(0)
{
	Open(filename);
}
*/

FileByteStream::~FileByteStream()
{
//	Close();
}

void FileByteStream::Close()
{
	if (m_bOwnHandle)
	{
	#if WIN32

		if (m_hFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
		}

	#elif AMIGA

		if (m_hFile != 0)
		{
			dosClose(DOSBase, m_hFile);
			m_hFile = 0;
		}

		/*
		if (DOSBase)
		{
			execCloseLibrary(*(ExecBase**)4, (struct Library*)DOSBase);
		}
		*/

	#elif __APPLE__

		if (m_forkRefNum)
		{
			FSCloseFork(m_forkRefNum);
			m_forkRefNum = 0;
		}

	#endif
	}
}

#if 0
ULONG FileByteStream::AddRef()
{
	return _Object::AddRef();
//	return InterlockedIncrement((long*)&m_refcount);
}

ULONG FileByteStream::Release()
{
	return _Object::Release();
	/*
	ASSERT(m_refcount > 0);
	m_refcount--;
	if (m_refcount == 0)
	{
		delete this;
		return 0;
	}
	return m_refcount;
	*/
}
#endif

void FileByteStream::Open(StringIn filename, FileMode mode)
{
	/*
	int len = filename->Length();
	for (int n = 0; n < len; n++)
	{
		char s[2];
		s[0] = filename->c_str()[n];
		s[1] = 0;
		printf("%s", s);
	}
	printf("..\n");
	*/

#if WIN32

	m_bOwnHandle = true;
	m_filename = filename;
	m_lastStatus = 0;

	CStringw cfilename = filename;
//	std::memcpy(cfilename, filename.GetData16(), filename.GetLength()*sizeof(WCHAR));
//	cfilename[filename.GetLength()] = 0;

	if (mode == FileMode_Read)
		m_hFile = CreateFileW(cfilename, GENERIC_READ, FILE_SHARE_READ/* | FILE_SHARE_WRITE*/, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	else if (mode == FileMode_Write)
		m_hFile = CreateFileW(cfilename, GENERIC_WRITE, 0/*FILE_SHARE_READ | FILE_SHARE_WRITE*/, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	else
		m_hFile = INVALID_HANDLE_VALUE;

	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		int error = GetLastError();

		switch (error)
		{
		case ERROR_SHARING_VIOLATION:
			m_lastStatus = FileStatus_SharingViolation;
			break;

		case ERROR_PATH_NOT_FOUND:
			m_lastStatus = FileStatus_PathNotFound;
			break;

		case ERROR_FILE_NOT_FOUND:
			m_lastStatus = FileStatus_FileNotFound;
			break;

		default:
			m_lastStatus = FileStatus_Error;
			break;
		}
	}

#else
	Open(filename->ToStringA(), mode);
#endif
}

#if 0
void FileByteStream::Open(String filename, FileMode mode)
{
	DebugTraceLn("FileByteStream::Open(" << filename << ", " << mode << ")");

#if WIN32

	Open(filename->ToStringW(), mode);

#if 0
	char* cfilename = (char*)alloca(filename->Length()+1);
	memcpy(cfilename, filename->begin(), filename->Length());
	cfilename[filename->Length()] = 0;

	if (mode == FileMode_Read)
		m_hFile = MSWindows::CreateFileA(cfilename, GENERIC_READ, FILE_SHARE_READ/* | FILE_SHARE_WRITE*/, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	else if (mode == FileMode_Write)
		m_hFile = MSWindows::CreateFileA(cfilename, GENERIC_WRITE, 0/*FILE_SHARE_READ | FILE_SHARE_WRITE*/, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	else
		m_hFile = INVALID_HANDLE_VALUE;

	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		int error = MSWindows::GetLastError();

		switch (error)
		{
		case ERROR_SHARING_VIOLATION:
			m_lastStatus = FileStatus_SharingViolation;
			break;

		case ERROR_FILE_NOT_FOUND:
			m_lastStatus = FileStatus_FileNotFound;
			break;

		default:
			m_lastStatus = FileStatus_Error;
			break;
		}
	}
#endif

#elif AMIGA

	m_bOwnHandle = true;
	m_filename = filename;
	m_lastStatus = 0;

//	DOSBase = (struct DosLibrary*)execOpenLibrary(*(ExecBase**)4, "dos.library", 36);
//	ASSERT(DOSBase != NULL);

	m_hFile = dosOpen(DOSBase, filename->c_str(), MODE_OLDFILE);
	if (m_hFile == 0)
	{
		m_lastStatus = FileStatus_Error;

//		ASSERT(0);
		printf("Failed to open file %s\n", filename->c_str());
		//THROW(-1);
		ASSERT(0);
	}

#elif __APPLE__

	m_bOwnHandle = true;
	m_filename = filename;
	m_lastStatus = 0;

	FSRef fsref;
	FSPathMakeRef((UInt8*)filename->c_str(), &fsref, NULL);

	HFSUniStr255 forkname;
	FSGetDataForkName(&forkname);

	FSOpenFork(&fsref, forkname.length, forkname.unicode, fsRdPerm, &m_forkRefNum);

#endif
}
#endif

ULONG FileByteStream::Read(void* pv, ULONG cb)
{
#if WIN32

	ULONG nRead;
	BOOL success = ReadFile(m_hFile, pv, cb, &nRead, NULL);
	VERIFY(success);
	return nRead;

#elif AMIGA

	return dosRead(DOSBase, m_hFile, pv, cb);

#elif __APPLE__

	ByteCount actualCount;
	FSReadFork(m_forkRefNum, fsAtMark, 0, cb, pv, &actualCount);

	return actualCount;

#endif
}

LONGLONG FileByteStream::Seek(LONGLONG offset, SeekOrigin origin)
{
#if WIN32

	LONG low = (LONG)offset;
	LONG high = (LONG)(offset >> 32);

	if (origin == STREAM_SEEK_SET)
	{
		low = SetFilePointer(m_hFile, low, &high, FILE_BEGIN);
	}
	else if (origin == STREAM_SEEK_CUR)
	{
		low = SetFilePointer(m_hFile, low, &high, FILE_CURRENT);
	}
	else if (origin == STREAM_SEEK_END)
	{
		low = SetFilePointer(m_hFile, low, &high, FILE_END);
	}
	else
		raise(Exception(L"failed write"));

	return (LONGLONG)low | ((LONGLONG)high<<32);

#elif AMIGA

	LONG low = (LONG)offset;
//	LONG high = (LONG)(offset >> 32);
//	if (high != 0)
//		THROW(-1);

	int mode;
	if (origin == STREAM_SEEK_SET)
		mode = OFFSET_BEGINNING;
	else if (origin == STREAM_SEEK_CUR)
		mode = OFFSET_CURRENT;
	else if (origin == STREAM_SEEK_END)
		mode = OFFSET_END;
	else
	{
		ASSERT(0);
	//	THROW(-1);
	}

	dosSeek(DOSBase, m_hFile, low, mode);

	return dosSeek(DOSBase, m_hFile, 0, OFFSET_CURRENT);

#elif __APPLE__

	UInt16 mode;
	if (origin == STREAM_SEEK_SET)
		mode = fsFromStart;
	else if (origin == STREAM_SEEK_CUR)
		mode = fsFromMark;
	else if (origin == STREAM_SEEK_END)
		mode = fsFromLEOF;

	FSSetForkPosition(m_forkRefNum, mode, offset);

	LONGLONG position;
	FSGetForkPosition(m_forkRefNum, &position);
	return position;

#else

#error "Unknown OS"

#endif
}

LONGLONG FileByteStream::GetSize()
{
#if WIN32

	DWORD high;
	DWORD low = ::GetFileSize(m_hFile, &high);
	return (LONGLONG)low | ((LONGLONG)high<<32);

#elif AMIGA

	//__aligned FileInfoBlock fib;
	__attribute__((aligned(8))) FileInfoBlock fib;
	if (dosExamineFH(DOSBase, m_hFile, &fib))
	{
		return fib.fib_Size;
	}
	else
		ASSERT(0);//THROW(-1);

#elif __APPLE__

	SInt64 size;
	if (FSGetForkSize(m_forkRefNum, &size) == 0)
	{
		return size;
	}
	else
		THROW(-1);
#endif
}

ISequentialByteStream* FileByteStream::Clone() const
{
	return new FileByteStream(m_filename);
}

ULONG FileByteStream::Write(const void* pv, ULONG cb)
{
	//m_lastStatus = FileStatus_Error;

#if WIN32
	ULONG nWritten;
	WriteFile(m_hFile, pv, cb, &nWritten, NULL);
	return nWritten;
#elif AMIGA
	return dosWrite(DOSBase, m_hFile, pv, cb);
#else
	ASSERT(0);
#endif
}

long FileByteStream::GetLastStatus() const
{
	return m_lastStatus;
}

// BufferedByteStream (TODO, in its own file)

BufferedByteStream::BufferedByteStream(ISequentialByteStream * stream, ULONG buffersize)
{
	m_stream = stream;
//	m_stream->AddRef();

	m_pos = 0;
	m_buffersize = buffersize;
//	m_buffer = new uint8[buffersize];
//	m_bufferpos = 0xfffffffffffff;
}

BufferedByteStream::~BufferedByteStream()
{
//	m_stream->Release();
	//delete[] m_buffer;

	map<uint32,uint8*>::iterator it = m_buffers.begin();
	while (it != m_buffers.end())
	{
		delete[] (*it).second;
		++it;
	}
}

/*
ULONG BufferedByteStream::AddRef()
{
	return _Object::AddRef();
}

ULONG BufferedByteStream::Release()
{
	return _Object::Release();
}
*/

ULONG BufferedByteStream::Read(void* pv, ULONG cb)
{
	uint8* pb = (uint8*)pv;

	/*
	if (m_pos < m_bufferpos + m_buffersize && m_pos+cb > m_bufferpos)
	{
		LONGLONG pos = m_pos;
		if (pos < m_bufferpos)
			pos = m_bufferpos;

		uint8* pb2 = pb + pos - 

		memcpy()
	}
	*/
	ULONG nbuffer = m_pos / m_buffersize;

	ULONG n = 0;

	while (n < cb)
	{
		map<uint32,uint8*>::iterator it = m_buffers.find(nbuffer);
		if (it == m_buffers.end())
		{
			uint8* buffer = new uint8[m_buffersize];
			m_stream->Seek(nbuffer * m_buffersize, System::IO::STREAM_SEEK_SET);
			m_stream->Read(buffer, m_buffersize);
			it = m_buffers.insert(map<uint32,uint8*>::value_type(nbuffer, buffer)).first;
		}

		ULONG nbytes = cb - n;

		ULONGLONG bufferpos = (ULONGLONG)nbuffer * m_buffersize;

		if (m_pos + nbytes > bufferpos + m_buffersize)
		{
			nbytes = bufferpos + m_buffersize - m_pos;
		}

		std::memcpy(pb, (*it).second + m_pos - bufferpos, nbytes);

		n += nbytes;
		pb += nbytes;
		m_pos += nbytes;
		nbuffer++;
	}

	return n;
}

LONGLONG BufferedByteStream::Seek(LONGLONG offset, SeekOrigin origin)
{
	if (origin == System::IO::STREAM_SEEK_CUR)
	{
		m_pos += offset;
	}
	else if (origin == System::IO::STREAM_SEEK_SET)
	{
		m_pos = offset;
	}
	else if (origin == System::IO::STREAM_SEEK_END)
	{
		m_pos = m_stream->GetSize() + offset;
	}

	return m_pos;
}

LONGLONG BufferedByteStream::GetSize()
{
	return m_stream->GetSize();
}


LONGLONG BufferedByteStream::GetSize() const
{
	return m_stream->GetSize();
}

ISequentialByteStream* BufferedByteStream::Clone() const
{
	return NULL;
}

ULONG BufferedByteStream::Write(const void* pv, ULONG cb)
{
	ASSERT(0);
	return -1;
}

// MemoryByteStream (TODO, in its own file)

MemoryStream::MemoryStream(const void* buffer, ULONG size)
{
	m_buffer = (const uint8*)buffer;
	m_size = size;
	m_pos = 0;
}

uint64 MemoryStream::GetSize()
{
	return m_size;
}

MemoryStream* MemoryStream::Clone() const
{
	return new MemoryStream(m_buffer, m_size);
}

size_t MemoryStream::Write(const void* pv, size_t cb)
{
	return -1;
}

size_t MemoryStream::Read(void* pv, size_t cb)
{
	if (m_pos+cb >= m_size)
		cb = m_size - m_pos;

	std::memcpy(pv, m_buffer+m_pos, cb);
	m_pos += cb;

	return cb;
}

uint64 MemoryStream::Seek(int64 offset, SeekOrigin origin)
{
	if (origin == IO::STREAM_SEEK_SET)
	{
		m_pos = offset;
	}
	else if (origin == IO::STREAM_SEEK_CUR)
	{
		m_pos += offset;
	}
	else if (origin == IO::STREAM_SEEK_END)
	{
		m_pos = m_size + offset;
	}
	else
		raise(ArgumentException());

//	if (m_pos < 0)	m_pos = 0;
	if (m_pos > m_size) m_pos = m_size;

	return m_pos;
}

////////////////////////////////
// ByteStreamWriter

ByteStreamWriter::ByteStreamWriter(StringIn filename) : m_refcount(0)
{
	ASSERT(0);
#if 0
//	m_filename = filename;
#if WIN32
	m_hFile = MSWindows::CreateFileA(filename->c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (m_hFile == MSWindows::Invalid_Handle_Value)
	{
		int err = MSWindows::GetLastError();

		if (err == ERROR_SHARING_VIOLATION)
			throw (int)ERROR_SHARING_VIOLATION;
		else
			THROW(-1);
	}
#else
	ASSERT(0);
#endif
#endif
}

ByteStreamWriter::~ByteStreamWriter()
{
	Close();
}

void ByteStreamWriter::Close()
{
#if WIN32
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}
#endif
}

ULONG ByteStreamWriter::AddRef()
{
	m_refcount++;
	return m_refcount;
}

ULONG ByteStreamWriter::Release()
{
	ASSERT(m_refcount > 0);
	m_refcount--;
	if (m_refcount == 0)
	{
		delete this;
		return 0;
	}
	return m_refcount;
}

ULONG ByteStreamWriter::Read(void* pv, ULONG cb)
{
	return -1;
}

ULONG ByteStreamWriter::Write(const void* pv, ULONG cb)
{
	ULONG nWritten;
#if WIN32
	WriteFile(m_hFile, pv, cb, &nWritten, NULL);
#endif
	return nWritten;
}

LONGLONG ByteStreamWriter::Seek(LONGLONG offset, SeekOrigin origin)
{
	LONG low = (LONG)offset;
	LONG high = (LONG)(offset >> 32);

#if WIN32
	if (origin == System::IO::STREAM_SEEK_SET)
	{
		low = SetFilePointer(m_hFile, low, &high, FILE_BEGIN);
	}
	else if (origin == System::IO::STREAM_SEEK_CUR)
	{
		low = SetFilePointer(m_hFile, low, &high, FILE_CURRENT);
	}
	else if (origin == System::IO::STREAM_SEEK_END)
	{
		low = SetFilePointer(m_hFile, low, &high, FILE_END);
	}
	else
		raise(Exception(L"invalid origin"));
#endif
	return (LONGLONG)low | ((LONGLONG)high<<32);
}

LONGLONG ByteStreamWriter::GetSize()
{
	return -1;
}

ISequentialByteStream* ByteStreamWriter::Clone() const
{
	return NULL;
}
#endif

///////////////////////////////
// BitStreamWriter

BitStreamO::BitStreamO(Stream* bytestream) : m_bytestream(bytestream)
{
	m_bitcnt = 0;
	m_curbyte = 0;
}

BitStreamO::~BitStreamO()
{
}

void BitStreamO::putbit(bool bit)
{
	if (m_bitcnt == 0)
	{
		m_bitcnt = 8;
		m_curbyte = 0;
	}

	m_bitcnt--;

	m_curbyte |= bit<<m_bitcnt;

	if (m_bitcnt == 0)
	{
		if (m_bytestream->Write(&m_curbyte, 1) != 1)
			raise(Exception(L"failed write"));
	}
}

void BitStreamO::putnbits(int nbits, int value)
{
	while (nbits--)
	{
		putbit((value>>nbits) & 1);
		//value >>= 1;
	}
}

void BitStreamO::byte_align()
{
	if (m_bitcnt > 0)
	{
		if (m_bytestream->Write(&m_curbyte, 1) != 1)
			raise(Exception(L"failed write"));

		m_bitcnt = 0;
		m_curbyte = 0;
	}
}

}	// IO
}	// System
