#ifndef __Archive_h__
#define __Archive_h__

namespace System
{
class LFCEXT Archive
{
public:
	CTOR Archive()
	{
		m_p = NULL;
	}

	CTOR Archive(IO::Stream* p) : m_p(p)
	{
	}

	~Archive()
	{
	}

	inline Archive& operator >> (bool& value)
	{
		Read(&value, 1);
		return *this;
	}

	inline Archive& operator << (bool value)
	{
		Write(&value, 1);
		return *this;
	}

	inline Archive& operator >> (char& value)
	{
		Read(&value, 1);
		return *this;
	}

	inline Archive& operator << (char value)
	{
		Write(&value, 1);
		return *this;
	}

	inline Archive& operator >> (signed char& value)
	{
		Read(&value, 1);
		return *this;
	}

	inline Archive& operator << (signed char value)
	{
		Write(&value, 1);
		return *this;
	}

	inline Archive& operator >> (unsigned char& value)
	{
		Read(&value, 1);
		return *this;
	}

	inline Archive& operator << (unsigned char value)
	{
		Write(&value, 1);
		return *this;
	}

	inline Archive& operator >> (short& value)
	{
		Read(&value, 2);
		value = BigEndian16(value);
		return *this;
	}

	inline Archive& operator << (short value)
	{
		value = BigEndian16(value);
		Write(&value, 2);
		return *this;
	}

	inline Archive& operator >> (unsigned short& value)
	{
		Read(&value, 2);
		value = BigEndian16(value);
		return *this;
	}

	inline Archive& operator << (unsigned short value)
	{
		value = BigEndian16(value);
		Write(&value, 2);
		return *this;
	}

	inline Archive& operator >> (int& value)
	{
		Read(&value, sizeof(int));
		value = BigEndian32(value);
		return *this;
	}

	inline Archive& operator << (int value)
	{
		value = BigEndian32(value);
		Write(&value, sizeof(int));
		return *this;
	}

	inline Archive& operator >> (unsigned int& value)
	{
		Read(&value, sizeof(unsigned int));
		value = BigEndian32(value);
		return *this;
	}

	inline Archive& operator << (unsigned int value)
	{
		value = BigEndian32(value);
		Write(&value, sizeof(unsigned int));
		return *this;
	}

	inline Archive& operator >> (long & value)
	{
		Read(&value, 4);
		value = BigEndian32(value);
		return *this;
	}

	inline Archive& operator << (long value)
	{
		value = BigEndian32(value);
		Write(&value, 4);
		return *this;
	}

	inline Archive& operator >> (unsigned long& value)
	{
		Read(&value, 4);
		value = BigEndian32(value);
		return *this;
	}

	inline Archive& operator << (unsigned long value)
	{
		value = BigEndian32(value);
		Write(&value, 4);
		return *this;
	}

	inline Archive& operator >> (float& value)
	{
		Read(&value, 4);
		BigEndian((uint32*)&value);
		return *this;
	}

	inline Archive& operator << (float value)
	{
		BigEndian((uint32*)&value);
		Write(&value, 4);
		return *this;
	}

	inline Archive& operator >> (double & value)
	{
		Read(&value, 8);
		BigEndian((ULONGLONG*)&value);
		return *this;
	}

	inline Archive& operator << (double value)
	{
		Write(&value, 8);
		BigEndian((ULONGLONG*)&value);
		return *this;
	}

	Archive& operator >> (String& value);
	Archive& operator << (String value);

//	Archive& operator >> (System::StringW* & value);
//	Archive& operator << (System::StringW* value);

	Archive& operator >> (Object* & object);
	Archive& operator << (const Object* object);

	void MapObject(const Object* object);
	void MapClass(System::ClassType* pClass);

	inline void Read(void* data, ULONG count)
	{
		m_p->Read(data, count);
	}

	inline void Write(const void* data, ULONG count)
	{
		m_p->Write(data, count);
	}

	inline bool IsLoading() const
	{
		return !m_bIsStoring;
	}

	inline bool IsStoring() const
	{
		return m_bIsStoring;
	}

	ClassType* ReadClass();
	void WriteClass(ClassType* pClass);

	_Ptr<IO::Stream> m_p;

	map<const void*, uint32> m_objectmapSave;
	map<uint32, void*> m_objectmapLoad;
	map<System::ClassType*, uint16> m_classmapSave;
	map<uint16, System::ClassType*> m_classmapLoad;

	bool m_bIsStoring;
};

class ISerializable
{
public:
	virtual void Load(Archive& ar) = 0;
	virtual void Store(Archive& ar) const = 0;
};

}

#endif // __Archive_h__
