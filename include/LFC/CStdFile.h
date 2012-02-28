namespace System
{
namespace IO
{

class LFCEXT CStdFile : public Stream
{
public:
	CTOR CStdFile(FILE* fp);
	virtual ~CStdFile();

#ifndef __LERSTAD__
	CTOR CStdFile(CStdFile&& other)
	{
		m_fp = other.m_fp;
		other.m_fp = NULL;
	}

	CStdFile& operator = (CStdFile&& other)
	{
		m_fp = other.m_fp;
		other.m_fp = NULL;
		return *this;
	}
#endif

	void Attach(FILE* fp);
	FILE* Detach();

	virtual bool Close() override;

	virtual size_t Read(void* pv, size_t cb) override
	{
		return fread(pv, 1, cb, m_fp);
	}

	virtual size_t Write(const void* pv, size_t cb) override
	{
		return fwrite(pv, 1, cb, m_fp);
	}

	virtual uint64 Seek(int64 move, SeekOrigin origin) override;
	virtual uint64 GetPosition() override;
	virtual void Flush() override;

	operator FILE* () const
	{
		return m_fp;
	}

// wrapper functions
	int feof()
	{
		return ::feof(m_fp);
	}

	char* fgets(char* str, int n)
	{
		return ::fgets(str, n, m_fp);
	}

	wchar_t* fgetws(wchar_t* str, int n)
	{
		return ::fgetws(str, n, m_fp);
	}

	void rewind()
	{
		::rewind(m_fp);
	}

	/*
#ifndef __LERSTAD__
	_Check_return_opt_ int __cdecl scanf_s(_In_z_ _Scanf_s_format_string_ const char * _Format, ...)
	{
		return ::scanf_s(_Scanf_s_format_string_, _Format, va_list(
	}
#endif

	int scanf(const char *format, argument]... 
	)
	{
		return ::scanf(format, 
	}
	*/

// static wrapper functions
	static int getmaxstdio()
	{
		return ::_getmaxstdio();
	}

	static int setmaxstdio(int _Max)
	{
		return ::_setmaxstdio(_Max);
	}

private:

	FILE* m_fp;
};

}	// IO
}	// System
