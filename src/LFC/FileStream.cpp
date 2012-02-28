#include "stdafx.h"
#include "LFC.h"

namespace System
{

__declspec(thread) IO::FileError lastError;

namespace IO
{

// static
FileError FileStream::GetLastError()
{
	return lastError;
}

LFCEXT TextWriter& WriteToStream(TextWriter& writer, const FileError& err)
{
	switch (err.code)
	{
	case ERROR_SHARING_VIOLATION:
		writer << "The process cannot access the file because it is being used by another process";
		break;

	case ERROR_LOCK_VIOLATION:
		writer << "Lock Violation";
		break;

	case ERROR_PATH_NOT_FOUND:
		writer << "Path Not Found";
		break;

	case ERROR_FILE_NOT_FOUND:
		writer << "The system cannot find the file specified";
		break;

	case ERROR_SHARING_BUFFER_EXCEEDED:
		writer << "Too many files opened for sharing";
		break;

	default:
		writer << "Unknown file error";
	}

	return writer;
}

/*
FileStream::FileStream() :
	m_hFile(INVALID_HANDLE_VALUE),
	m_closeFile(false)
{
	m_state = 0;
}
*/

FileStream::FileStream(Stream* sync) :
	m_hFile(INVALID_HANDLE_VALUE),
	m_closeFile(false)
{
//	m_sync = sync;
	m_state = 0;
}

FileStream::FileStream(StringIn filename, FileMode mode, FileAccess access, FileShare share) :
	m_closeFile(true)
{
	DWORD open = 0;
	DWORD dwDesiredAccess = 0;
	DWORD dwShareMode = 0;

	switch (mode)
	{
	case FileMode_Open:
		open = OPEN_EXISTING;
		break;

	case FileMode_Create:
		open = CREATE_ALWAYS;
		break;

	case FileMode_CreateNew:
		open = CREATE_NEW;
		break;

	case FileMode_OpenOrCreate:
		open = OPEN_ALWAYS;
		break;

	case FileMode_TruncateExisting:
		open = TRUNCATE_EXISTING;
		break;
	}

	if (access & 1)
	{
		dwDesiredAccess |= GENERIC_READ;
	}

	if (access & 2)
	{
		dwDesiredAccess |= GENERIC_WRITE;
	}

	if (share & 1)
	{
		dwShareMode = FILE_SHARE_READ;
	}

	if (share & 2)
	{
		dwShareMode = FILE_SHARE_WRITE;
	}

	m_filename = filename;
	m_hFile = CreateFileW(filename.c_strw(), dwDesiredAccess, dwShareMode, NULL, open, FILE_ATTRIBUTE_NORMAL, NULL);

	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		wchar_t fullpath[1024];
		_wfullpath(fullpath, filename.c_strw(), _countof(fullpath));

		lastError.code = ::GetLastError();
		raise_(Exception::FromHResult("'" + filename + "' - '"  + fullpath + "' not found", HRESULT_FROM_WIN32(lastError.code)));
		raise(FileNotFoundException("'" + filename + "' - '"  + fullpath + "' not found"));
	}
	else
		lastError.code = 0;

	m_isConsole = !!GetConsoleMode(m_hFile, &m_consoleMode);

	m_state = 0;
}

FileStream::FileStream(StringIn filename, FileMode mode, FileAccess access) :
	m_closeFile(true)
{
	FileShare share;
	if (access == FileAccess_Read)
	{
		share = FileShare_Read;
	}
	else
	{
		share = FileShare_None;
	}

	/*
	FileStreamObject* f = new FileStreamObject(filename, mode, access, share);
	f->IncRef();
	m_streamObject = f;
	*/

	DWORD open = 0;
	DWORD dwDesiredAccess = 0;
	DWORD dwShareMode = 0;

	switch (mode)
	{
	case FileMode_Open:
		open = OPEN_EXISTING;
		break;

	case FileMode_Create:
		open = CREATE_ALWAYS;
		break;

	case FileMode_CreateNew:
		open = CREATE_NEW;
		break;

	case FileMode_OpenOrCreate:
		open = OPEN_ALWAYS;
		break;

	case FileMode_TruncateExisting:
		open = TRUNCATE_EXISTING;
		break;
	}

	if (access & 1)
	{
		dwDesiredAccess |= GENERIC_READ;
	}

	if (access & 2)
	{
		dwDesiredAccess |= GENERIC_WRITE;
	}

	if (share & 1)
	{
		dwShareMode = FILE_SHARE_READ;
	}

	if (share & 2)
	{
		dwShareMode = FILE_SHARE_WRITE;
	}

	m_filename = filename;
	m_hFile = CreateFileW(filename.c_strw(), dwDesiredAccess, dwShareMode, NULL, open, FILE_ATTRIBUTE_NORMAL, NULL);

	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		wchar_t fullpath[1024];
		_wfullpath(fullpath, filename.c_strw(), _countof(fullpath));

		lastError.code = ::GetLastError();
		raise_(Exception::FromHResult("'" + filename + "' - '"  + fullpath + "' not found", HRESULT_FROM_WIN32(lastError.code)));
		raise(FileNotFoundException("'" + filename + "' - '"  + fullpath + "' not found"));
	}
	else
		lastError.code = 0;

	m_isConsole = !!GetConsoleMode(m_hFile, &m_consoleMode);

	m_state = 0;
}

FileStream::FileStream(HANDLE hFile, bool closeFile) : m_hFile(hFile), m_closeFile(closeFile)
{
	m_isConsole = !!GetConsoleMode(m_hFile, &m_consoleMode);
	if (hFile == NULL)
	{
		hFile = INVALID_HANDLE_VALUE;
	}
}

FileStream::~FileStream()
{
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		if (m_closeFile)
		{
			CloseHandle(m_hFile);
		}
	}
}

bool FileStream::Reopen(FileAccess access, FileShare share)
{
	DWORD dwDesiredAccess = 0;
	DWORD dwShareMode = 0;

	if (access & 1)
	{
		dwDesiredAccess |= GENERIC_READ;
	}

	if (access & 2)
	{
		dwDesiredAccess |= GENERIC_WRITE;
	}

	if (share & 1)
	{
		dwShareMode = FILE_SHARE_READ;
	}

	if (share & 2)
	{
		dwShareMode = FILE_SHARE_WRITE;
	}

	ASSERT(0);
#if 0
	DWORD dwFlagsAndAttributes = 0;
	HANDLE hFile = ReOpenFile(m_hFile, dwDesiredAccess, dwShareMode, dwFlagsAndAttributes);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		m_hFile = hFile;
		m_isConsole = !!GetConsoleMode(m_hFile, &m_consoleMode);

		return true;
	}
	else
#endif
		return false;
}

bool FileStream::Close()
{
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		return false;
		//raise(Exception(L"INVALID_HANDLE_VALUE"));
	}

	BOOL success = CloseHandle(m_hFile);
	m_hFile = INVALID_HANDLE_VALUE;
	return !!success;
}

bool FileStream::CanSeek()
{
	return true;
}

bool FileStream::CanRead()
{
	return true;
}

bool FileStream::CanWrite()
{
	return true;
}

int FileStream::Peek()
{
	return m_buffer[m_bufferpos+1];
}

/*
void FileStreamObject::FlushWrite()
{
//	DWORD nBytesWritten;
//	BOOL success = WriteFile(m_hFile, m_buffer, m_nWriteBytes, &nBytesWritten, NULL);
//	m_nWriteBytes = 0;
}
*/

size_t FileStream::Write(const void* pv, size_t _len)
{
	DWORD nBytesWritten;
	BOOL success = WriteFile(m_hFile, pv, _len, &nBytesWritten, NULL);
	if (!success)
	{
		DWORD win32Error = GetLastError();
		raise_(Exception::FromHResult(HRESULT_FROM_WIN32(win32Error)));
	}

	return nBytesWritten;

#if 0
	/*
	if (len >= m_buffersize)
	{
		FlushWrite();

		DWORD nBytesWritten;
		BOOL success = WriteFile(m_hFile, pv, len, &nBytesWritten, NULL);

		return nBytesWritten;
	}
	*/

	byte* pb = (byte*)pv;

	size_t len = _len;

	while (len > 0)
	{
		size_t cb = len;
		if (cb > m_buffersize - m_bufferpos)
		{
			cb = m_buffersize - m_bufferpos;
		}

		memcpy(m_buffer, pb, cb);
		pb += cb;
		m_bufferpos += cb;
		len -= cb;

		if (m_bufferpos == m_buffersize)
		{
			DWORD nBytesWritten;
			BOOL success = WriteFile(m_hFile, m_buffer, m_buffersize, &nBytesWritten, NULL);
			m_bufferpos = 0;
		}
	}

	/*
	if (

	DWORD nBytesWritten;
	BOOL success = WriteFile(m_hFile, pv, len, &nBytesWritten, NULL);

	m_nWriteBytes += len;
	*/

	return _len;
#endif
}

size_t FileStream::_WriteChars(const char* p, size_t len)
{
	/*
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		raise(Exception(L"INVALID_HANDLE_VALUE"));
	}
	*/

	if (m_isConsole)
	{
		DWORD nCharsWritten;
		BOOL success = WriteConsoleA(m_hFile, p, len, &nCharsWritten, NULL);
		if (!success)
		{
			DWORD win32Error = GetLastError();
			raise_(Exception::FromHResult(HRESULT_FROM_WIN32(win32Error)));
		}

		return nCharsWritten;
	}
	else
	{
		DWORD nBytesWritten;
		BOOL success = WriteFile(m_hFile, p, len, &nBytesWritten, NULL);
		if (!success)
		{
			DWORD win32Error = GetLastError();
			raise_(Exception::FromHResult(HRESULT_FROM_WIN32(win32Error)));
		}

		return nBytesWritten;
	}	
}

size_t FileStream::_WriteChars(const wchar_t* p, size_t len)
{
	/*
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		raise(Exception(L"INVALID_HANDLE_VALUE"));
		return 0;
	}
	*/

	if (m_isConsole)
	{
		ULONG nCharsWritten;
		BOOL success = WriteConsoleW(m_hFile, p, len, &nCharsWritten, NULL);
		if (!success)
		{
			raise_(Exception::FromHResult(HRESULT_FROM_WIN32(::GetLastError())));
		}

		return nCharsWritten;
	}
	else
	{
	//	WideCharToMultiByte(
		for (size_t i = 0;  i < len; ++i)
		{
			char c = (char)p[i];

			DWORD nWritten;
			BOOL success = WriteFile(m_hFile, &c, 1, &nWritten, NULL);
			if (!success)
			{
				raise_(Exception::FromHResult(HRESULT_FROM_WIN32(::GetLastError())));
			}
		}

		return 0;
	}
}

size_t FileStream::Read(void* pv, size_t _len)
{
	if (m_isConsole)
	{
		ASSERT(0);
		return 0;
	}
	else
	{
		DWORD nBytesRead;
		BOOL success = ReadFile(m_hFile, pv, _len, &nBytesRead, NULL);
		if (!success)
		{
			lastError.code = ::GetLastError();
			raise_(Exception::FromHResult(HRESULT_FROM_WIN32(::GetLastError())));
		}

		if (nBytesRead < _len)
		{
			m_state |= 1;
		}

		return nBytesRead;

		/*
		byte* pb = (byte*)pv;

		size_t len = _len;

		while (len)
		{
			size_t cb = len;
			if (cb > m_buffersize)
				cb = m_buffersize;
			memcpy(pb, bufferptr, cb);

			pb += 

			if (m_filepos bufferpos
		}

		DWORD nBytesRead;
		ReadFile(m_hFile, pv, len, &nBytesRead, NULL);
		return nBytesRead;
		*/
	}
}

size_t FileStream::ReadChars(char* p, size_t len)
{
	if (m_isConsole)
	{
		DWORD nCharsRead;
		ReadConsoleA(m_hFile, p, len, &nCharsRead, NULL);

		return nCharsRead;
	}
	else
	{
		DWORD nRead;
		ReadFile(m_hFile, p, len, &nRead, NULL);
		if (nRead < len)
		{
			m_state |= 1;
		}

		return nRead;
	}
}

size_t FileStream::ReadChars(wchar_t* p, size_t len)
{
	/*
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		ASSERT(0);
		raise(Exception(L"INVALID_HANDLE_VALUE"));
		return 0;
	}
	*/

	if (m_isConsole)
	{
		DWORD nCharsRead;
		BOOL success = ReadConsoleW(m_hFile, p, len, &nCharsRead, NULL);
		if (!success)
		{
			lastError.code = ::GetLastError();
			raise_(Exception::FromHResult(HRESULT_FROM_WIN32(::GetLastError())));
		}

		return nCharsRead;
	}
	else
	{
		size_t i;
		for (i = 0; i < len; ++i)
		{
			char c;
			DWORD nRead;
			ReadFile(m_hFile, &c, 1, &nRead, NULL);
			if (nRead == 0)
			{
				m_state |= 1;
				break;
			}
			p[i] = c;
		}

		return i;
	}
}

int FileStream::state()
{
	int state = 0;

	if (GetFilePos() >= GetSize())
		state |= 1;

	return state;
}

void FileStream::SetFileHandle(HANDLE hFile, bool closeFile)
{
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		if (m_closeFile)
		{
			CloseHandle(m_hFile);
		}
	}

	m_hFile = hFile;
	m_closeFile = closeFile;
	m_isConsole = !!GetConsoleMode(m_hFile, &m_consoleMode);
}

uint64 FileStream::GetSize()
{
	uint64 size;
	BOOL success = ::GetFileSizeEx(m_hFile, (LARGE_INTEGER*)&size);
	if (!success)
	{
		lastError.code = ::GetLastError();
		raise_(Exception::FromHResult(HRESULT_FROM_WIN32(::GetLastError())));
	}

	return size;
}

uint64 FileStream::GetFilePos()
{
	LONG high = 0;
	DWORD low = SetFilePointer(m_hFile, 0, &high, FILE_CURRENT);

	return (uint64)low | ((uint64)high<<32);
}

uint64 FileStream::GetPosition()
{
	LONG high = 0;
	DWORD low = SetFilePointer(m_hFile, 0, &high, FILE_CURRENT);

	return (uint64)low | ((uint64)high<<32);

//	return m_position;
}

uint64 FileStream::Seek(int64 offset, SeekOrigin origin)
{
#if _WIN32

	LONG low = (int32)offset;
	LONG high = (int32)(offset >> 32);

	DWORD newlow;

	if (origin == SeekOrigin_Set)
	{
		newlow = SetFilePointer(m_hFile, low, &high, FILE_BEGIN);
	}
	else if (origin == SeekOrigin_Current)
	{
		newlow = SetFilePointer(m_hFile, low, &high, FILE_CURRENT);
	}
	else if (origin == SeekOrigin_End)
	{
		newlow = SetFilePointer(m_hFile, low, &high, FILE_END);
	}
	else
		raise(ArgumentException());

	if (newlow == INVALID_SET_FILE_POINTER)
	{
		DWORD err = ::GetLastError();
		if (err != NO_ERROR)
		{
			if (err == ERROR_NEGATIVE_SEEK)
			{
				raise(IOException(L"Negative Seek"));
			}
			else
			{
				raise(IOException(L"Error Seeking"));
			}
		}
	}

//	m_bufferpos

	return (uint64)newlow | ((uint64)high<<32);

#elif AMIGA

	LONG low = (LONG)offset;
//	LONG high = (LONG)(offset >> 32);
//	if (high != 0)
//		THROW(-1);

	int mode;
	if (origin == SeekOrigin_Set)
		mode = OFFSET_BEGINNING;
	else if (origin == SeekOrigin_Current)
		mode = OFFSET_CURRENT;
	else if (origin == SeekOrigin_End)
		mode = OFFSET_END;
	else
	{
		raise(ArgumentException());
	}

	dosSeek(DOSBase, m_hFile, low, mode);

	return dosSeek(DOSBase, m_hFile, 0, OFFSET_CURRENT);

#elif __APPLE__

	UInt16 mode;
	if (origin == SeekOrigin_Set)
		mode = fsFromStart;
	else if (origin == SeekOrigin_Current)
		mode = fsFromMark;
	else if (origin == SeekOrigin_End)
		mode = fsFromLEOF;
	else
		raise(ArgumentException());

	FSSetForkPosition(m_forkRefNum, mode, offset);

	LONGLONG position;
	FSGetForkPosition(m_forkRefNum, &position);
	return position;

#else

#error "Unknown OS"

#endif
}

uint32 FileStream::Read(void* pv, uint64 offset, uint32 len)
{
	OVERLAPPED overlapped;
	overlapped.Offset = (DWORD)offset;
	overlapped.OffsetHigh = offset>>32;

	DWORD nRead;
	BOOL success = ReadFile(GetFileHandle(), pv, len, &nRead, &overlapped);
	if (!success)
	{
		DWORD win32Error = GetLastError();
		raise_(Exception::FromHResult(HRESULT_FROM_WIN32(win32Error)));
	}

	return nRead;
}

uint32 FileStream::Write(const void* pv, uint64 offset, uint32 len)
{
	OVERLAPPED overlapped;
	overlapped.Offset = (DWORD)offset;
	overlapped.OffsetHigh = offset>>32;

	DWORD nWritten;
	BOOL success = WriteFile(GetFileHandle(), pv, len, &nWritten, &overlapped);
	if (!success)
	{
		DWORD win32Error = GetLastError();
		raise_(Exception::FromHResult(HRESULT_FROM_WIN32(win32Error)));
	}

	return nWritten;
}

}	// IO
}	// System
