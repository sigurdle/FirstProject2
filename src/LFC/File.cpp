#include "stdafx.h"
#include "LFC.h"

//#pragma comment(lib, "FileExtd")

namespace System
{
namespace IO
{

FILETIME File::GetCreationTime(StringIn filename)
{
	HANDLE hFile = CreateFileW(CStringw(filename), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		FILETIME ft;
		ft.dwLowDateTime = 0;
		ft.dwHighDateTime = 0;
		return ft;
	}

	FILETIME creationTime;
	BOOL success = GetFileTime(hFile, &creationTime, NULL, NULL);
	CloseHandle(hFile);
	return creationTime;
}

FILETIME File::GetLastModifiedTime(StringIn filename)
{
	HANDLE hFile = CreateFileW(CStringw(filename), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		FILETIME ft;
		ft.dwLowDateTime = 0;
		ft.dwHighDateTime = 0;
		return ft;
	}

	FILETIME lastWriteTime;
	BOOL success = GetFileTime(hFile, NULL, NULL, &lastWriteTime);
	CloseHandle(hFile);
	return lastWriteTime;
}

bool File::Exists(StringIn filename)
{
	HANDLE hFile = CreateFileW(CStringw(filename), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	CloseHandle(hFile);
	return true;
/*
	WIN32_FIND_DATAA wfd;
	HANDLE hFile = FindFirstFileA(CString(filename), &wfd);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	FindClose(hFile);
	return true;
	*/
}

File::filesize_t File::GetSize(StringIn filename)
{
	HANDLE hFile = CreateFileW(CStringw(filename), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	LARGE_INTEGER li;
	BOOL success = GetFileSizeEx(hFile, &li);
	return li.QuadPart;
}

File::filesize_t File::GetCompressedSize(StringIn filename)
{
	DWORD hi;
	DWORD lo = GetCompressedFileSize(CStringw(filename), &hi);
	if (lo == INVALID_FILE_SIZE)
	{
		if (GetLastError())
		{
			return 0;
		}
	}
	return lo | ((uint64)hi<<32);

}

//static
FILETIME FileTime::Now()
{
	SYSTEMTIME systime;
	GetLocalTime(&systime);

	FILETIME filetime;
	SystemTimeToFileTime(&systime, &filetime);

	return filetime;
}

void File::Touch(StringIn filename, FILETIME fileTime)
{
#if 0
	DWORD creationDisposition = OPEN_ALWAYS;
	HANDLE hFile = CreateFileW(CStringw(filename), GENERIC_READ | GENERIC_WRITE, 0/*share*/, NULL,
		creationDisposition,
		0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		IO::StringWriter str;
		str << "Touch failed for " << filename;
		raise(IOException(str.str()));
	}

	BOOL success;
	FILE_BASIC_INFO info;
	success = GetFileInformationByHandleEx(hFile, FileBasicInfo, &info, sizeof(info));
	if (!success)
	{
		raise_(Exception::FromHResult(HRESULT_FROM_WIN32(GetLastError())));
	}

	info.LastWriteTime.QuadPart = *(uint64*)&fileTime;
	info.LastAccessTime.QuadPart = *(uint64*)&fileTime;
	success = SetFileInformationByHandle(hFile, FileBasicInfo, &info, sizeof(info));
	if (!success)
	{
		raise_(Exception::FromHResult(HRESULT_FROM_WIN32(GetLastError())));
	}

	CloseHandle(hFile);
#endif
}

}	// IO
}	// System
