namespace System
{

class LFCEXT Guid : public ValueType
{
public:

	CTOR Guid() : m_guid(GUID_NULL)
	{
	}

	CTOR Guid(const GUID& guid) : m_guid(guid)
	{
	}

	CTOR Guid(uint32 data1, uint16 data2, uint16 data3, ubyte data4[8])
	{
		m_guid.Data1 = data1;
		m_guid.Data2 = data2;
		m_guid.Data3 = data3;
		*(uint64*)m_guid.Data4 = *(uint16*)data4;
	}

	CTOR Guid(uint32 data1, uint16 data2, uint16 data3, ubyte data4_0, ubyte data4_1, ubyte data4_2, ubyte data4_3, ubyte data4_4, ubyte data4_5,  ubyte data4_6, ubyte data4_7)
	{
		m_guid.Data1 = data1;
		m_guid.Data2 = data2;
		m_guid.Data3 = data3;
		m_guid.Data4[0] = data4_0;
		m_guid.Data4[1] = data4_1;
		m_guid.Data4[2] = data4_2;
		m_guid.Data4[3] = data4_3;
		m_guid.Data4[4] = data4_4;
		m_guid.Data4[5] = data4_5;
		m_guid.Data4[6] = data4_6;
		m_guid.Data4[7] = data4_7;
	}

	CTOR Guid(StringIn str);

	operator GUID () const throw()
	{
		return m_guid;
	}

	bool operator ! () const throw()
	{
#ifdef _M_X64
		if (((const uint64*)&m_guid)[0] != 0) return false;
		if (((const uint64*)&m_guid)[1] != 0) return false;
#else
		if (((const uint32*)&m_guid)[0] != 0) return false;
		if (((const uint32*)&m_guid)[1] != 0) return false;
		if (((const uint32*)&m_guid)[2] != 0) return false;
		if (((const uint32*)&m_guid)[3] != 0) return false;
#endif

		return true;
	}

	bool operator == (const GUID& other) const throw()
	{
		return memcmp(&m_guid, &other, sizeof(GUID)) == 0;
	}

	bool operator == (const Guid& other) const throw()
	{
		return memcmp(&m_guid, &other.m_guid, sizeof(GUID)) == 0;
	}

	bool operator != (const Guid& other) const throw()
	{
		return memcmp(&m_guid, &other.m_guid, sizeof(GUID)) != 0;
	}

	bool operator < (const Guid& other) const throw()
	{
		return memcmp(&m_guid, &other.m_guid, sizeof(GUID)) < 0;
	}

	void CopyTo(ubyte p[16]) const
	{
		memcpy(p, &m_guid, 16);
	}

	virtual String ToString() override;
	virtual uint32 GetHashCode() override;

	static Guid NewGuid();
	static Guid Parse(StringIn str);

	static Guid Empty()
	{
		return GUID_NULL;
	}

	GUID m_guid;
};

}	// System
