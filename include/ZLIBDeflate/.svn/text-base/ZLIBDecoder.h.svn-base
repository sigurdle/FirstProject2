#ifndef ZLIBDeflate_Decoder_h
#define ZLIBDeflate_Decoder_h

namespace System
{
namespace IO
{

class ZLIBEXT ZLIBException : public SystemException
{
public:

	CTOR ZLIBException(StringIn reason) : SystemException(reason)
	{
	}
};

class ZLIBEXT ZLIBDecoder : public Stream
{
public:

	CTOR ZLIBDecoder();
	CTOR ZLIBDecoder(Stream* byteStream, uint64 totalSize = ~0);

	void start(IO::Stream* byteStream);

	virtual size_t Read(void* pv, size_t cb) override;
	virtual uint64 Seek(int64 offset, SeekOrigin origin) override;
	virtual uint64 GetSize() override;
	virtual uint64 GetPosition() override;
	virtual size_t Write(const void* pv, size_t nbytes) override;

	virtual ZLIBDecoder* CloneStream();

private:

	CTOR ZLIBDecoder(const ZLIBDecoder&);
	ZLIBDecoder& operator = (const ZLIBDecoder&);

protected:

	virtual ~ZLIBDecoder();

	_Ptr<Inflate> m_inflate;
	uint64 m_totalSize;
};

class ZLIBEncoder : public Stream
{
public:
	CTOR ZLIBEncoder();
	~ZLIBEncoder();

	virtual size_t Read(void* pv, size_t cb) override
	{
		raise(Exception());
		return 0;
	}
	virtual size_t Write(const void* pv, size_t cb) override;
	virtual uint64 Seek(int64 offset, SeekOrigin origin) override;
	virtual uint64 GetSize() override;
//	virtual IO::ISequentialByteStream* Clone() const;

protected:

	size_t m_pos;
	size_t m_totalSize;
	size_t m_n;
};

}	// IO
}	// System

#endif // ZLIBDeflate_Decoder_h
