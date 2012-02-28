#ifndef __Ole_CompoundFile_h__
#define __Ole_CompoundFile_h__

namespace System
{
namespace OLE
{

#pragma pack(push,1)

struct HEADER
{
	char Signature[8];
	GUID	uniqID;
	uint16 Revision;
	uint16 Version;
	uint16 ByteOrder;
	uint16 SecSize;
	uint16 ShortSecSize;
	char reserved[10];
	uint32 NumSectors;
	uint32 FirstSID;
	uint32 reserved1;
	uint32 MinStreamSize;
	uint32 FirstShortSID;
	uint32 NumShortSectors;
	uint32 FirstMasterSID;
	uint32 NumMasterSectors;
};

struct DIRENTRY
{
	WCHAR Name[32];
	uint16 NameLen;
	uint8 NodeType;
	uint8 NodeColor;
	int LeftChildDID;
	int RightChildDID;
	int RootNodeDID;
	GUID uniqID;
	uint32 UserFlags;
	LONGLONG CreationDate;
	LONGLONG LastModificationDate;
	uint32 FirstSID;
	uint32 StreamSize;
	uint32 Reserved;
};

 
#pragma pack(pop)

class Stream;

class Storage
{
public:
	void Open(System::IO::ISequentialByteStream* byteStream);

	System::IO::ISequentialByteStream* m_data;

	ULONG Read(void* pv, ULONGLONG pos, ULONG cb)
	{
		m_data->Seek(pos, System::IO::STREAM_SEEK_SET);
		return m_data->Read(pv, cb);
	}

	Stream* OpenStream(DIRENTRY* direntry);

	uint32* m_pSID;
};

class Stream : public System::IO::ISequentialByteStream
{
public:
	Stream()
	{
		m_pos = 0;
	}

	Storage* m_pStorage;

	ULONG m_size;
	vector<ULONG> m_sectors;

	ULONG m_pos;

	ULONG AddRef()
	{
		return 1;
	}

	ULONG Release()
	{
		return 1;
	}

	LONGLONG GetSize()
	{
		return m_size;
	}

	LONGLONG Seek(LONGLONG offset, IO::SeekOrigin mode)
	{
		if (mode == System::IO::STREAM_SEEK_SET)
			m_pos = offset;
		else if (mode == System::IO::STREAM_SEEK_END)
			m_pos = m_size - offset;
		else if (mode == System::IO::STREAM_SEEK_CUR)
			m_pos += offset;
		else
			ASSERT(0);

		return m_pos;
	}

	ULONG Read(void *pv, ULONG cb)
	{
		if (m_pos > m_size)
			return 0;

		ULONG count = cb;
		if (m_pos + count > m_size)
			count = m_size - m_pos;

		if (count > 0)
		{
			ULONG nRead = Read(pv, m_pos, count);
			m_pos += nRead;
			return nRead;
		}
		else
			return 0;
	}

	ULONG Read(void *pv, ULONG pos, ULONG cb)
	{
		ULONG nsector = pos >> 9;
		ULONG sectorpos = pos & 511;

		uint8* pb = (uint8*)pv;

		ULONG len = 0;
		while (len < cb)
		{
			ULONG count = cb-len;
			if (sectorpos+count > 512)
			{
				count = 512-sectorpos;
			}

			ULONG fileoffset = 512 + 512*m_sectors[nsector] + sectorpos;
			count = m_pStorage->Read(pb, fileoffset, count);

			pb += count;
			len += count;
			sectorpos = 0;
			nsector++;
		}

		return len;
	}

	ULONG Write(const void* pv, ULONG cb)
	{
		return 0;
	}

	virtual System::IO::ISequentialByteStream* Clone() const
	{
		return NULL;
	}

	/*
	uint8* m_sectorData;
	ULONG m_nsector;
	*/
};

}	// OLE
}

#endif // __Ole_CompoundFile_h__
