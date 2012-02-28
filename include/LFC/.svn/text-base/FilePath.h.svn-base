namespace System
{

class LFCEXT Filename : public Object
{
public:

	CTOR Filename();
	CTOR Filename(StringIn filename);
	CTOR Filename(StringIn name, StringIn ext);
	CTOR Filename(const Filename& other);

	String get_Ext() const
	{
		return m_ext;
	}

	String get_Name() const
	{
		return m_name;
	}

	Filename WithExt(StringIn ext) const
	{
		return Filename(m_name, ext);
	}

	Filename& operator = (const Filename& other)
	{
		m_filename = other.m_filename;
		m_name = other.m_name;
		m_ext = other.m_ext;

		return *this;
	}

	operator String () const
	{
		return m_filename;
	}

	operator StringVariant () const
	{
		return m_filename;
	}

	virtual String ToString()
	{
		return m_filename;
	}

#ifndef __LERSTAD__
	friend IO::TextWriter& operator << (IO::TextWriter& stream, const Filename& f)
	{
		stream << f.m_name;
		if (f.m_ext)
		{
			stream << "." << f.m_ext;
		}

		return stream;
	}
#endif

public:

	String m_filename;
	String m_name;
	String m_ext;
};

class LFCEXT FilePath : public Object
{
public:
	CTOR FilePath();
	CTOR FilePath(StringIn filepath);
	CTOR FilePath(StringIn drive, StringIn pathname);
	CTOR FilePath(StringIn drive, StringIn dir, StringIn filenameext);
	CTOR FilePath(StringIn drive, StringIn dir, StringIn filename, StringIn ext);
	CTOR FilePath(const FilePath& other);

	String get_Drive() const
	{
		return m_drive;
	}

	String get_Dir() const
	{
		return m_dir;
	}

	String get_Name() const;
	String get_Ext() const;

	Filename get_NameExt() const;
	void set_NameExt(Filename filename);

	String get_FullPath();
	String get_FullPath() const;

	FilePath WithNameExt(StringIn nameext) const
	{
		return FilePath(get_Drive(), get_Dir(), nameext);
	}

	FilePath WithExt(StringIn ext) const
	{
		return FilePath(get_Drive(), get_Dir(), get_Name(), ext);
	}

	FilePath& operator = (const FilePath& other)
	{
		m_filepath = other.m_filepath;
		m_drive = other.m_drive;
		m_dir = other.m_dir;
		m_name = other.m_name;
		m_ext = other.m_ext;

		return *this;
	}

	operator StringVariant ();

	FilePath operator + (const Filename& fname) const;
	FilePath& operator += (const Filename& fname);

	virtual String ToString()
	{
		return get_FullPath();
	}

public:

	String m_filepath;
	String m_drive;
	String m_dir;
	String m_name;
	String m_ext;
};

LFCEXT IO::TextWriter& WriteToStream(IO::TextWriter& stream, FilePath& filepath);
LFCEXT IO::TextWriter& WriteToStream(IO::TextWriter& stream, const FilePath& filepath);

}	// System
