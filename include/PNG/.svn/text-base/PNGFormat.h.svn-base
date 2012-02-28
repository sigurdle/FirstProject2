#ifndef __PNGFORMAT_H_
#define __PNGFORMAT_H_

namespace System
{
namespace Imaging
{

#define CK_IHDR	0x49484452
#define CK_JHDR	0x4A484452
#define CK_PLTE	0x504C5445
#define CK_IDAT	0x49444154
#define CK_JDAT	0x4a444154
#define CK_IEND	0x49454e44

class PNGEXT NGFormat : public Object
{
public:

	struct HDR	// Common header fields
	{
		int32 Width;
		int32 Height;
	};

	struct IHDR : public HDR
	{
		uint8 BitDepth;
		uint8 ColorType;
		uint8 Compression;
		uint8 Filter;
		uint8 Interlace;
	};

	struct JHDR : public HDR
	{
		uint8 Color_type;
		uint8 Image_sample_depth;
		uint8 Image_compression_method;
		uint8 Image_interlace_method;
		uint8 Alpha_sample_depth;
		uint8 Alpha_compression_method;
		uint8 Alpha_filter_method;
		uint8 Alpha_interlace_method;
	};

	struct MHDR
	{
		uint32 Frame_width;//:         4 bytes (unsigned integer).
		uint32 Frame_height;//:        4 bytes (unsigned integer).
		uint32 Ticks_per_second;//:    4 bytes (unsigned integer).
		uint32 Nominal_layer_count;//: 4 bytes (unsigned integer).
		uint32 Nominal_frame_count;//: 4 bytes (unsigned integer).
		uint32 Nominal_play_time;//:   4 bytes (unsigned integer).
		uint32 Simplicity_profile;//:  4 bytes:(unsigned integer).
	};

	struct PaletteEntry
	{
		uint8 r;
		uint8 g;
		uint8 b;
	};

	class PNGEXT DATStream : public IO::Stream
	{
	public:
		CTOR DATStream(uint32 chunkID, IO::Stream* stream);

		virtual size_t Read(void* pv, size_t cb) override;
		virtual uint64 Seek(int64 move, IO::SeekOrigin origin) override;
		virtual uint64 GetSize() override;
		virtual size_t Write(const void* pv, size_t cb) override;
		virtual uint64 GetPosition() override
		{
			return m_pos;
		}

		virtual bool CanRead() override
		{
			return true;
		}

	protected:

		_Ptr<IO::Stream> m_stream;
		uint32 m_pos;
		uint32 m_chunkID;

		uint32 m_idata_offset;
		uint32 m_idata_length;

		bool NextDAT();
	};

	interface INGImageStream
	{
		virtual int DecodeScanline() = 0;
		virtual const uint8* GetScanlinePtr() = 0;
	};

	interface INGImage
	{
		virtual void StartScan() = 0;
		virtual int ReadScanline(uint8* dest) = 0;
	};

	class PNGEXT PNGImageStream : public Object, public INGImageStream
	{
	public:

		CTOR PNGImageStream(DATStream* stream);
		~PNGImageStream();

		void Start();
		int DecodeScanline();

		const ubyte* GetScanlinePtr()
		{
			return m_scanlinePtr[!m_curscan];
		}

		unsigned int GetScanlineBytes() const
		{
			return m_scanlineBytes;
		}

		unsigned int m_passwidth;
		unsigned int m_width;
		uint8 m_filter;
		uint8 m_colorType;
		uint8 m_interlace;
		PaletteEntry* m_paletteEntry;

		int m_npass;
		int m_w;

	protected:

		IO::ZLIBDecoder* m_decoder;

		uint8 m_curscan;

		unsigned int m_pixelBytes;
		unsigned int m_scanlineBytes;
		ubyte* m_scanlineBuffer[2];
		ubyte* m_scanlinePtr[2];
	};

	class PNGEXT JPEGImageStream : public Object, public INGImageStream
	{
	public:
		CTOR JPEGImageStream(DATStream* stream);

		int DecodeScanline();

		const uint8* GetScanlinePtr()	// TODO
		{
			ASSERT(0);
	#if 0
			return m_jpeg->GetScanlinePtr();
	#endif
			return 0;
		}

		void Start()
		{
			m_jpeg->StartScans();
		}

		DATStream* GetStream()
		{
			return m_stream;
		}

	protected:

		DATStream* m_stream;
		JPEGDecoder* m_jpeg;
	};

	class PNGEXT PNGImage :
		public Object,
		public INGImage
	{
	public:
		PaletteEntry* m_paletteEntry;

		CTOR PNGImage(const IHDR* ihdr, PaletteEntry* paletteEntry, IO::Stream* stream);

		virtual ~PNGImage()
		{
		}

		void StartScan()
		{
			m_imageStream->Start();
		}

		int ReadScanline(uint8* dest);

	//protected:
		PNGImageStream* m_imageStream;
	};

	class PNGEXT JPEGAImage :
		public Object,
		public INGImage
	{
	public:
		CTOR JPEGAImage(const JHDR* jhdr, IO::Stream* stream);

		void StartScan();
		int ReadScanline(uint8* dest);

		JPEGImageStream* m_jpegStream;
		PNGImageStream* m_alphaStream;

	protected:

		JHDR m_hdr;
	};

	CTOR NGFormat();

	virtual void SetStream(IO::Stream* stream);

	virtual _Ptr<IO::Stream> GetStream() const
	{
		return m_stream;
	}

	virtual void ReadSignature() = 0;
	virtual int ReadHeader() = 0;
	virtual void CreateImage() = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual uint8 GetColorType() const = 0;
	virtual INGImage* GetImage() = 0;

protected:

	_Ptr<IO::Stream> m_stream;
};

class PNGEXT PNGDecoder : public NGFormat, public IBitmapFormatDecoder
{
public:
	CTOR PNGDecoder();
	~PNGDecoder();

	static ErrorCode ReadMarker(IO::Stream* stream);

	virtual int ReadHeader(IO::Stream* stream, BitmapFormat* bitmapFormat) override;
	virtual int ReadBitmap(IO::Stream* stream, void* data, int rowbytes) override;

	virtual void ReadSignature();
	virtual int ReadHeader();
	virtual void CreateImage();

	virtual int GetWidth() const
	{
		return m_ihdr.Width;
	}

	virtual int GetHeight() const
	{
		return m_ihdr.Height;
	}

	virtual uint8 GetColorType() const
	{
		return m_ihdr.ColorType;
	}

	virtual INGImage* GetImage()
	{
		return m_image;
	}

	IHDR m_ihdr;

	void NextPass();

//protected:

	PaletteEntry* m_paletteEntry;

	PNGImage* m_image;
};

class PNGEXT JNGDecoder : public NGFormat
{
public:
	CTOR JNGDecoder();
	~JNGDecoder();

	virtual void ReadSignature();
	virtual int ReadHeader();
	virtual void CreateImage();

	virtual int GetWidth() const
	{
		return m_jhdr.Width;
	}

	virtual int GetHeight() const
	{
		return m_jhdr.Height;
	}

	virtual uint8 GetColorType() const;

	virtual INGImage* GetImage()
	{
		return m_image;
	}

protected:

	JHDR m_jhdr;
	JPEGAImage* m_image;
};

inline int PaethPredictor(int a, int b, int c)
{
	int p = a + b - c;
	int pa = abs(p - a);
	int pb = abs(p - b);
	int pc = abs(p - c);

	if (pa <= pb && pa <= pc)
		return a;
	else if (pb <= pc)
		return b;
	else
		return c;
}

}	// Imaging
}	// System

#endif // __PNGFORMAT_H_
