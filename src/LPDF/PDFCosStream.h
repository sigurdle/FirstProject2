#pragma once

#include "PDFCosObj.h"

namespace System
{
namespace PDF
{

class PDFExt CPDFCosStream : 
	public CPDFCosObj//Impl<IPDFCosStream>
{
public:
	CPDFCosStream()
	{
	}

#if 0
	int FinalConstruct()
	{
		// Temporary filename for stream
		TCHAR temppath[512];
		GetTempPath(sizeof(temppath), temppath);

		TCHAR filename[512];
		GetTempFileName(temppath, "pdf", 0, filename);

		m_filename = filename;

		return 0;
	}

	StringA m_filename;
#endif

	long m_start;

	class Stream : public System::IO::ISequentialByteStream
	{
	public:
		Stream()
		{
			m_pos = 0;
			m_length = 0;
		}

		CPDFCosStream* m_pCosStream;

		ULONG AddRef()
		{
			return 1;
		}

		ULONG Release()
		{
			return 1;
		}

		ULONG m_pos;
		ULONG m_length;

		virtual ULONG Read(void* pv, ULONG cb);
		virtual ULONG Write(const void* pv, ULONG cb);
		virtual LONGLONG Seek(LONGLONG move, System::IO::SeekOrigin origin);
		virtual LONGLONG GetSize();
		virtual System::IO::ISequentialByteStream* Clone() const;
	};

	CPDFCosDict* m_attributesDict;

	System::IO::ISequentialByteStream* OpenRawStream();

	System::IO::ISequentialByteStream* OpenStream();

	virtual void WriteToStream(std::FILE* fp);

	CPDFCosDict* CosStreamDict();
};

}
}
