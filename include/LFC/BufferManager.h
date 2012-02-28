
#if 0

#pragma once

namespace System
{

class IBuffer
{
public:
	virtual ULONG Read(void* pv, ULONGLONG pos, ULONG cb) = 0;
	virtual ULONG Write(const void* pv, ULONGLONG pos, ULONG cb) = 0;
	virtual ULONGLONG GetSize() = 0;
	virtual ULONGLONG GetIdentity() = 0;
	virtual void Close() = 0;
};

class IBufferManager
{
public:
//	virtual IBuffer* GetSysBuffer() = 0;
	virtual IBuffer* OpenBuffer(ULONGLONG identity) = 0;
	virtual IBuffer* AllocateBuffer(ULONGLONG size) = 0;
	virtual void FreeBuffer(IBuffer* buffer) = 0;
};

template<class T> class LFCEXT ValueRef
{
public:
	ValueRef(IBuffer* buffer, ULONG pos)
	{
		m_buffer = buffer;
		m_pos = pos;
		m_bDirty = false;
	}

	~ValueRef()
	{
		if (m_bDirty)
		{
			m_buffer->Write(&m_value, m_pos, sizeof(T));
		}
	}

	operator T ()
	{
		return m_value;
	}

	ValueRef& operator = (const ValueRef& other)
	{
		m_value = other.m_value;
		m_bDirty = true;
		return *this;
	}

	ValueRef& operator = (const T& other)
	{
		m_value = other;
		m_bDirty = true;
		return *this;
	}

	IBuffer* m_buffer;
	ULONG m_pos;
	T m_value;
	bool m_bDirty;
};

template<class T> class Ptr
{
public:

	Ptr(IBuffer* buffer, ULONG pos) : m_value(buffer, pos)
	{
		m_bDirty = true;
	}

	~Ptr()
	{
	}


	template<class T2> operator T2 ()
	{
		return Ptr<T2>(buffer, m_value.m_pos);
	}

	ValueRef<T> operator * ()
	{
		if (m_bDirty)
		{
			m_value.m_buffer->Read(&m_value.m_value, m_value.m_pos, sizeof(T));
			m_bDirty = false;
		}
		return m_value;
	}

	Ptr operator + (int n)
	{
		Ptr<T> ptr(m_buffer);
		ptr.m_value.m_pos = m_value.m_pos + n;
		return ptr;
	}

	Ptr& operator += (int n)
	{
		m_value.m_pos += n;
		return *this;
	}

	int operator - (const Ptr& other) const
	{
		return m_value.m_pos - other.m_value.m_pos;
	}

	bool m_bDirty;
	ValueRef<T> m_value;
};

class LFCEXT BufferStream
{
public:

// Write

	ULONG Write(const void* pv, ULONG cb)
	{
		ULONG n = m_buffer->Write(pv, m_pos, cb);
		m_pos += n;
		return n;
	}

	BufferStream(IBuffer* buffer, ULONG pos = 0)
	{
		m_buffer = buffer;
		m_pos = pos;
	}

	BufferStream& operator << (char val)
	{
		m_buffer->Write(&val, m_pos, 1);
		m_pos += 1;
		return *this;
	}

	BufferStream& operator << (signed char val)
	{
		m_buffer->Write(&val, m_pos, 1);
		m_pos += 1;
		return *this;
	}

	BufferStream& operator << (unsigned char val)
	{
		m_buffer->Write(&val, m_pos, 1);
		m_pos += 1;
		return *this;
	}

	BufferStream& operator << (int val)
	{
		m_buffer->Write(&val, m_pos, sizeof(int));
		m_pos += sizeof(int);
		return *this;
	}

	BufferStream& operator << (unsigned int val)
	{
		m_buffer->Write(&val, m_pos, sizeof(unsigned int));
		m_pos += sizeof(unsigned int);
		return *this;
	}

	BufferStream& operator << (short val)
	{
		m_buffer->Write(&val, m_pos, 2);
		m_pos += 2;
		return *this;
	}

	BufferStream& operator << (unsigned short val)
	{
		m_buffer->Write(&val, m_pos, 2);
		m_pos += 2;
		return *this;
	}

	BufferStream& operator << (long val)
	{
		m_buffer->Write(&val, m_pos, 4);
		m_pos += 4;
		return *this;
	}

	BufferStream& operator << (unsigned long val)
	{
		m_buffer->Write(&val, m_pos, 4);
		m_pos += 4;
		return *this;
	}

	BufferStream& operator << (LONGLONG val)
	{
		m_buffer->Write(&val, m_pos, 8);
		m_pos += 8;
		return *this;
	}

	BufferStream& operator << (ULONGLONG val)
	{
		m_buffer->Write(&val, m_pos, 8);
		m_pos += 8;
		return *this;
	}

	BufferStream& operator << (float val)
	{
		m_buffer->Write(&val, m_pos, 4);
		m_pos += 4;
		return *this;
	}

	BufferStream& operator << (double val)
	{
		m_buffer->Write(&val, m_pos, 8);
		m_pos += 8;
		return *this;
	}

	BufferStream& operator << (String val)
	{
		ASSERT(0);
#if 0
		long size = val->Length();
		*this << size;
		Write(val->c_str(), size*2);
#endif
		return *this;
	}

	// Read

	ULONG Read(void* pv, ULONG cb)
	{
		ULONG n = m_buffer->Read(pv, m_pos, cb);
		m_pos += n;
		return n;
	}

	BufferStream& operator >> (char& val)
	{
		m_buffer->Read(&val, m_pos, 1);
		m_pos += 1;
		return *this;
	}

	BufferStream& operator >> (signed char& val)
	{
		m_buffer->Read(&val, m_pos, 1);
		m_pos += 1;
		return *this;
	}

	BufferStream& operator >> (unsigned char& val)
	{
		m_buffer->Read(&val, m_pos, 1);
		m_pos += 1;
		return *this;
	}

	BufferStream& operator >> (int& val)
	{
		m_buffer->Read(&val, m_pos, sizeof(int));
		m_pos += sizeof(int);
		return *this;
	}

	BufferStream& operator >> (unsigned int& val)
	{
		m_buffer->Read(&val, m_pos, sizeof(unsigned int));
		m_pos += sizeof(unsigned int);
		return *this;
	}

	BufferStream& operator >> (short& val)
	{
		m_buffer->Read(&val, m_pos, 2);
		m_pos += 2;
		return *this;
	}

	BufferStream& operator >> (unsigned short& val)
	{
		m_buffer->Read(&val, m_pos, 2);
		m_pos += 2;
		return *this;
	}

	BufferStream& operator >> (long& val)
	{
		m_buffer->Read(&val, m_pos, 4);
		m_pos += 4;
		return *this;
	}

	BufferStream& operator >> (unsigned long& val)
	{
		m_buffer->Read(&val, m_pos, 4);
		m_pos += 4;
		return *this;
	}

	BufferStream& operator >> (LONGLONG& val)
	{
		m_buffer->Read(&val, m_pos, 8);
		m_pos += 8;
		return *this;
	}

	BufferStream& operator >> (ULONGLONG& val)
	{
		m_buffer->Read(&val, m_pos, 8);
		m_pos += 8;
		return *this;
	}

	BufferStream& operator >> (String& val)
	{
		ASSERT(0);
#if 0
		long len;
		*this >> len;

		__live_object_ptr<System::StringW> str = new System::StringW((WCHAR*)NULL, len);
		//str.MakeRoom(len);
		m_buffer->Read(str->begin(), m_pos, len*2);
		m_pos += len*2;

		val = str;
#endif
		return *this;
	}

	IBuffer* m_buffer;
	ULONG m_pos;
};

template<class T> void ptrmemcpy(Ptr<T> dst, Ptr<T> src, int n)
{
	for (int i = 0; i < n; i++)
	{
		*dst = *src;
		dst += 1;
		src += 1;
	}
}

class LFCEXT MemBuffer : public IBuffer
{
public:
	MemBuffer(const void* pv, ULONG cb)
	{
		m_pb = (uint8*)pv;
		m_cb = cb;
	}

	ULONG Read(void* pv, ULONGLONG pos, ULONG cb)
	{
		return 0;
	}

	ULONG Write(const void* pv, ULONGLONG pos, ULONG cb)
	{
		return 0;
	}

	ULONGLONG GetSize()
	{
		return m_cb;
	}

	const uint8* m_pb;
	ULONG m_cb;
};

class Block;
class Buffer;
class BufferManager;

class LFCEXT BufferManager : public System::Object, public IBufferManager
{
public:

	BufferManager(const char* filename, const char* accessmode);

	IBuffer* GetSysBuffer();
	IBuffer* OpenBuffer(ULONGLONG identity);
	IBuffer* AllocateBuffer(ULONGLONG size);
	void FreeBuffer(IBuffer* buffer);

protected:

	ULONGLONG m_nbuffers;

	Block* AllocateBlock();
	void FreeBlock(Block* useblock);

	void WriteBlockHeader(Block* block);
	ULONG ReadFromBlock(Block* block, void* pv, ULONG pos, ULONG cb);
	ULONG WriteToBlock(Block* block, const void* pv, ULONG pos, ULONG cb);

	Buffer* _OpenBuffer(ULONGLONG identity);
	Buffer* _AllocateBuffer(ULONGLONG size);
	void _FreeBuffer(Buffer* buffer);
	Buffer* _OpenBufferAtAddress(ULONGLONG address);
	Buffer* _AllocateBufferAtAddress(ULONGLONG size);

	Buffer* m_sysBuffer;

//	IT((EXPORT_MAP(ULONGLONG, Block*, ::less<ULONGLONG>, std_allocator)))
	map<ULONGLONG, Block*> m_blocks;

	HANDLE m_fp;

	Block* m_firstFree;
	Block* m_lastFree;

	Block* m_firstUsed;
	Block* m_lastUsed;

	ULONG m_actualBlockSize;
	ULONG m_blocksize;

	ULONGLONG m_totalsize;

	friend class Buffer;
};

// A Wrapper around a buffer, that prepends an 64-bit size

class LFCEXT File : public System::Object, public IBuffer
{
public:
	File()
	{
		m_size = 0;
		m_pBuffer = NULL;
	}

	void Create(IBuffer* pBuffer)
	{
		m_pBuffer = pBuffer;
		m_size = 0;
		BufferStream(m_pBuffer, 0) << m_size;
	}

	void Open(IBuffer* pBuffer)
	{
		m_pBuffer = pBuffer;
		BufferStream(m_pBuffer, 0) >> m_size;
	}

	IBuffer* m_pBuffer;

	ULONGLONG m_size;

	ULONG Read(void* pv, ULONGLONG pos, ULONG cb)
	{
		return m_pBuffer->Read(pv, pos+8, cb);
	}

	ULONG Write(const void* pv, ULONGLONG pos, ULONG cb)
	{
		if (m_size < pos+cb)
			m_size = pos+cb;

		BufferStream(m_pBuffer, 0) << m_size;

		return m_pBuffer->Write(pv, pos+8, cb);
	}

	ULONGLONG GetIdentity()
	{
		return m_pBuffer->GetIdentity();
	}

	ULONGLONG GetSize()
	{
		return m_size;
		/*
		ULONGLONG size;
		return size;
		*/
	}

	void Close()
	{
		m_pBuffer->Close();
	}
};

}

#endif
