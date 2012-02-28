#ifndef __FileByteStream_h_
#define __FileByteStream_h_

#if AMIGA

typedef long  BPTR;

#endif

namespace System
{
namespace IO
{

enum FileStatus
{
	FileStatus_Ok = 0,
	FileStatus_Error = -100,
	FileStatus_FileNotFound = FileStatus_Error - 1,//ERROR_FILE_NOT_FOUND
	FileStatus_PathNotFound = FileStatus_Error - 2,
	FileStatus_SharingViolation = FileStatus_Error - 32,//ERROR_SHARING_VIOLATION
};

/*
enum FileMode
{
	FileMode_Read = 1,
	FileMode_Write,
	FileMode_ReadWrite,
};
*/

//LFCEXT Stream& operator << (Stream& stream, FileMode mode);

#if 0
class LFCEXT FileByteStream : public Object, public ISequentialByteStream
{
public:

	CTOR FileByteStream();
#if WIN32
	//FileByteStream(HANDLE hFile, bool bOwnHandle);
#elif AMIGA
	CTOR FileByteStream(BPTR hFile, bool bOwnHandle);
#endif
	CTOR FileByteStream(StringIn filename, FileMode mode = FileMode_Read);

	~FileByteStream();

//	ULONG m_refcount;

//	ULONG AddRef();
//	ULONG Release();

	void Open(StringIn filename, FileMode mode);
	//void Open(const char* filename);
	virtual ULONG Read(void* pv, ULONG cb);
	virtual LONGLONG Seek(LONGLONG offset, SeekOrigin origin);
	virtual LONGLONG GetSize();
//	virtual LONGLONG GetSize() const;
	virtual ISequentialByteStream* Clone() const;

	virtual ULONG Write(const void* pv, ULONG cb);

	long GetLastStatus() const;

	void Close();

#ifdef WIN32
	static FileByteStream* FromHandle(HANDLE hFile, bool bOwnHandle);
#endif

protected:

	String m_filename;

#if WIN32

	HANDLE m_hFile;

#elif AMIGA

	BPTR m_hFile;
//	struct DosLibrary* m_DOSBase;
	ULONG reserved;

#elif __APPLE__

	short m_forkRefNum;

#endif

	long m_lastStatus;
	bool m_bOwnHandle;
};
#endif

}	// IO
}	// System

#endif // __FileByteStream_h_
