namespace System
{
namespace Gui
{

class GUIEXT DataFormat : public Object
{
public:

	CTOR DataFormat(DataFormat&& other) :
		m_id(other.m_id),
		m_name(std::move(other.m_name))
	{
	}

	CTOR DataFormat(uint id, StringIn name) : m_id(id), m_name(name)
	{
	}

	uint get_Id() const throw()
	{
		return m_id;
	}

	String get_Name() const throw()
	{
		return m_name;
	}

	virtual String ToString() override
	{
		return get_Name();
	}

	bool operator == (const DataFormat& other) const throw()
	{
		return m_id == other.m_id;
	}

	bool operator != (const DataFormat& other) const throw()
	{
		return m_id != other.m_id;
	}

	bool operator < (const DataFormat& other) const throw()
	{
		return m_id < other.m_id;
	}

private:

	uint m_id;
	String m_name;
};

class GUIEXT DataFormats
{
public:

	static String GetDataFormatString(UINT nFormat);

	static DataFormat GetDataFormat(UINT nFormat)
	{
		return DataFormat(nFormat, GetDataFormatString(nFormat));
	}

	static DataFormat GetDataFormat(StringIn name);

	static DataFormat& get_Bitmap()
	{
#ifndef __LERSTAD__
		static DataFormat f(CF_BITMAP, "Bitmap");
#endif
		return f;
	}

	static DataFormat& get_Dib();
	static DataFormat& get_Dif()
	{
#ifndef __LERSTAD__
		static DataFormat f(CF_DIF, "DataInterchangeFormat");
#endif
		return f;
	}

	static DataFormat& get_EnhancedMetafile();
	static DataFormat& get_FileDrop()
	{
#ifndef __LERSTAD__
		static DataFormat f(CF_HDROP, "FileDrop");
#endif
		return f;
	}

	static DataFormat& get_Html()
	{
#ifndef __LERSTAD__
		static DataFormat f(GetDataFormat("HTML"));
#endif
		return f;
	}

	static DataFormat& get_Jfif()
	{
#ifndef __LERSTAD__
		static DataFormat f(GetDataFormat("JFIF"));
#endif
		return f;
	}

	static DataFormat& get_Locale()
	{
#ifndef __LERSTAD__
		static DataFormat f(CF_LOCALE, "Locale");
#endif
		return f;
	}

	static DataFormat& get_PenData()
	{
#ifndef __LERSTAD__
		static DataFormat f(CF_PENDATA, "PenData");
#endif
		return f;
	}

	static DataFormat& get_Png()
	{
#ifndef __LERSTAD__
		static DataFormat f(GetDataFormat("PNG"));
#endif
		return f;
	}

	static DataFormat& get_Riff()
	{
#ifndef __LERSTAD__
		static DataFormat f(CF_RIFF, "Riff");
#endif
		return f;
	}

	static DataFormat& get_Rtf()
	{
#ifndef __LERSTAD__
		static DataFormat f(GetDataFormat("Rich Text Format"));
#endif
		return f;
	}

	static DataFormat& get_Text()
	{
#ifndef __LERSTAD__
		static DataFormat f(CF_TEXT, "Text");
#endif
		return f;
	}

	static DataFormat& get_Tiff();

	static DataFormat& get_UnicodeText()
	{
#ifndef __LERSTAD__
		static DataFormat f(CF_UNICODETEXT, "UnicodeText");
#endif
		return f;
	}

	static DataFormat& get_WaveAudio();

private:

	CTOR DataFormats();
};

class GUIEXT IDataObjectPtr
{
public:

	CTOR IDataObjectPtr() : m_p(nullptr)
	{
	}

	CTOR IDataObjectPtr(__IDataObject* p) : m_p(p)
	{
		if (p) p->AddRef();
	}

	CTOR IDataObjectPtr(const IDataObjectPtr& other) : m_p(other.m_p)
	{
		if (m_p) m_p->AddRef();
	}

	CTOR IDataObjectPtr(IDataObjectPtr&& other) : m_p(other.m_p)
	{
		other.m_p = nullptr;
	}

	~IDataObjectPtr()
	{
		if (m_p)
		{
			m_p->Release();
			m_p = nullptr;
		}
	}

	operator __IDataObject* () const
	{
		return m_p;
	}

	__IDataObject** operator & ()
	{
		ASSERT(m_p == nullptr);
		return &m_p;
	}

#ifndef __LERSTAD__
	IDataObjectPtr& operator = (IDataObjectPtr&& other)
	{
		m_p = other.m_p;
		other.m_p = nullptr;
		return *this;
	}
#endif

	IDataObjectPtr& operator = (const IDataObjectPtr& other)
	{
		if (other.m_p) other.m_p->AddRef();
		if (m_p) m_p->Release();
		m_p = other.m_p;

		return *this;
	}

	bool operator ! () const throw()
	{
		return m_p == nullptr;
	}

	bool operator == (decltype(nullptr)) const throw()
	{
		return m_p == nullptr;
	}

	bool operator == (const IDataObjectPtr& other) const
	{
		return m_p == other.m_p;
	}

	bool operator != (const IDataObjectPtr& other) const
	{
		return m_p != other.m_p;
	}

	bool operator < (const IDataObjectPtr& other) const
	{
		return m_p < other.m_p;
	}

	Object* GetData(UINT format);
	Object* GetData(StringIn format);
	Object* GetData(Type* format);

	bool GetDataPresent(UINT nFormat);
	bool GetDataPresent(StringIn format);
	bool GetDataPresent(Type* format);

	void SetData(UINT nFormat, Object* data);
	void SetData(StringIn format, Object* data);
	void SetData(Type* format, Object* data);

	vector<String> GetFormats();

	bool ContainsFileDropList();
	List<String>* GetFileDropList();

protected:

	__IDataObject* m_p;
};

#if 0
class GUIEXT DataObject : public Object, public IDataObject
{
public:

	virtual Object* GetData(StringIn format) override;
	virtual Object* GetData(Type* format) override;
	virtual bool GetDataPresent(StringIn format) override;
	virtual bool GetDataPresent(Type* format) override;
	virtual void SetData(StringIn format, Object* data) override;
	virtual void SetData(Type* format, Object* data) override;
	virtual vector<String> GetFormats() override;

	bool ContainsFileDropList();

#ifndef __LERSTAD__
	::IDataObject* m_pDataObject;
#else
	void* m_pDataObject;
#endif
};
#endif

}	// Gui
}	// System
