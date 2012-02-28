#include "stdafx.h"
#include "LFC.h"

namespace System
{
namespace IO
{

CStdFile::CStdFile(FILE* fp) : m_fp(fp)
{
	if (fp == NULL)
	{
		raise(ArgumentNullException());
	}
}

CStdFile::~CStdFile()
{
	Close();
}

bool CStdFile::Close()
{
	if (m_fp)
	{
		fclose(m_fp);
		m_fp = NULL;
	}
	return true;
}

void CStdFile::Attach(FILE* fp)
{
	Close();
	m_fp = fp;
}

FILE* CStdFile::Detach()
{
	FILE* fp = m_fp;
	m_fp = NULL;
	return fp;
}

void CStdFile::Flush()
{
	fflush(m_fp);
}

uint64 CStdFile::Seek(int64 move, SeekOrigin origin)
{
	int orig;
	switch (origin)
	{
	case SeekOrigin_Start: orig = SEEK_SET; break;
	case SeekOrigin_Current: orig = SEEK_CUR; break;
	default: orig = SEEK_END; break;
	}

	if (_fseeki64(m_fp, move, orig) != 0)
	{
		raise(IOException("Seek error"));
	}

	long long pos = _ftelli64(m_fp);
	if (pos == -1LL)
	{
		raise(IOException("Seek error"));
	}

	return pos;
}

uint64 CStdFile::GetPosition()
{
	long long pos = _ftelli64(m_fp);
	if (pos == -1LL)
	{
		char* msg;

		switch (errno)
		{
		case EBADF: msg = "Handle is not a valid file pointer or the file is not open";
			break;

		case EINVAL: msg = "Handle is not a valid file stream";
			break;

		default:
			msg = "IO error";
		}

		raise(IOException(msg));
	}

	return (uint64)pos;
}

}	// IO
}	// System
