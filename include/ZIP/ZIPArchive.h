#ifndef ZIPArchive_h
#define ZIPArchive_h

//#include "crc32.h"

namespace System
{
namespace ZIP
{

class Archive;

class ZIPEXT ZipException : public SystemException
{
public:
	CTOR ZipException(StringIn reason) : SystemException(reason)
	{
	}
};

class ZIPEXT FileRawStream : public IO::Stream
{
public:
	CTOR FileRawStream(IO::Stream* stream, uint64 beginpos, uint64 size);

	virtual size_t Read(void* pv, size_t cb) override;
	virtual size_t Write(const void* pv, size_t cb) override;
	uint64 Seek(int64 move, IO::SeekOrigin origin) override;
	uint64 GetSize() override;

protected:

	~FileRawStream();

	_Ptr<IO::Stream> m_stream;
	uint64 m_size;
	uint64 m_pos;
	uint64 m_beginpos;
};

class ZIPEXT File : public Object
{
public:
	CTOR File(Archive* ar);

	_Ptr<IO::Stream> GetRawStream();
	_Ptr<IO::Stream> GetStream();

	String GetName();

	bool Check();

protected:

	friend class Archive;

	Archive* m_ar;

	uint16 m_compression_method;
	uint32 m_compressed_size;
	uint32 m_uncompressed_size;
	uint32 m_crc_32;
	String m_name;
	int64 m_bytepos;

	uint64 m_dataoffset;
};

class ZIPEXT Archive : public Object
{
public:

	CTOR Archive();
	CTOR Archive(IO::Stream* stream);
	~Archive();

	void Open(IO::Stream* stream);

	uint GetFileCount();
	File* GetFile(uint index);
	File* OpenFile(StringIn filename);

	bool Check();

	File* FindFile(StringIn pathname);

protected:

	int16 getshort();
	int32 getint32();

	friend class File;

	class _Archive
	{
	public:
		vector<File*> m_files;
		map<String, File*> m_filesByName;
		_Ptr<IO::Stream> m_stream;
	};

	_Archive* m_p;
};

}	// ZIP
}	// System

#endif // ZIPArchive_h
