#pragma once

typedef HANDLE HGLOBAL;

namespace System
{

class HGlobalStream : public System::Object, public System::IO::ISequentialByteStream
{
public:
	//ULONG m_refcount;

	CTOR HGlobalStream();

	CTOR HGlobalStream(HGLOBAL hGlobal);

	~HGlobalStream();

	/*
	ULONG AddRef()
	{
		m_refcount++;
		return m_refcount;
	}

	ULONG Release()
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
	*/

	HGLOBAL Detach()
	{
		HGLOBAL hGlobal = m_hGlobal;
		m_hGlobal = NULL;
		return hGlobal;
	}

	void* GetData();

	virtual ULONG Read(void* pv, ULONG cb)
	{
		ASSERT(0);
		return 0;
	}

	virtual LONGLONG Seek(LONGLONG offset, IO::SeekOrigin origin)
	{
		if (origin == System::IO::STREAM_SEEK_SET)
		{
			m_pos = offset;
		}
		else if (origin == System::IO::STREAM_SEEK_END)
		{
			m_pos = m_size + offset;
		}
		else if (origin == System::IO::STREAM_SEEK_CUR)
		{
			m_pos += offset;
		}

		return m_pos;
	}
	virtual LONGLONG GetSize()
	{
		return m_size;
	}
	virtual System::IO::ISequentialByteStream* Clone() const
	{
		return NULL;
	}

	virtual ULONG Write(const void* pv, ULONG cb);

	HGLOBAL m_hGlobal;
	LONGLONG m_pos;
	ULONG m_size;
};

}
