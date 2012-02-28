#ifndef __SWF_Decoder_H_
#define __SWF_Decoder_H_

#ifndef SWFExt
#define SWFExt	DECLSPEC_DLLIMPORT
#endif

#include "Movie.h"

namespace System
{
namespace SWF
{

class SWFExt FormatStream :
	public System::Object,
	public System::IO::ISequentialByteStream
{
public:
	CTOR FormatStream(System::IO::ISequentialByteStream* stream)
	{
		m_zlibDecoder = NULL;
		m_stream = stream;
	}

	typedef System::Object base;

	~FormatStream()
	{
		if (m_zlibDecoder)
		{
//			m_zlibDecoder->Release();
		}
	}

	/*
	ULONG AddRef()
	{
		return base::AddRef();
	}

	ULONG Release()
	{
		return base::Release();
	}
	*/

	bool get_Compressed() const
	{
		return m_Compressed;
	}

	uint8 get_Version() const
	{
		return m_Version;
	}

	void ReadHeader();

	virtual ULONG Read(void* pv, ULONG cb)
	{
		if (m_zlibDecoder)
			return m_zlibDecoder->Read(pv, cb);
		else
			return m_stream->Read(pv, cb);
	}

	virtual ULONG Write(const void* pv, ULONG cb)
	{
		ASSERT(0);
		THROW(-1);
		return 0;
	}

	virtual LONGLONG Seek(LONGLONG offset, IO::SeekOrigin origin)
	{
		if (m_zlibDecoder)
		{
			return m_zlibDecoder->Seek(offset, origin);
		}
		else
		{
			return m_stream->Seek(offset, origin);
		}
	}

	virtual LONGLONG GetSize()
	{
		return m_FileSize;
	}

	virtual System::IO::ISequentialByteStream* Clone() const
	{
		THROW(-1);
		return NULL;
	}

protected:

	System::IO::ISequentialByteStream* m_stream;
	ZLIBDecoder* m_zlibDecoder;

// Header fields
	bool m_Compressed;
	uint8 m_Version;
	ULONG m_FileSize;
};

class SWFExt TagStream : public System::Object
{
public:
	CTOR TagStream(FormatStream* stream)
	{
		m_bitcnt = 0;
		m_stream = stream;

	//	m_FrameCount = 0;
	}

	inline ULONG Read(void* pv, ULONG cb)
	{
		byte_align();
		return m_stream->Read(pv, cb);
	}

	inline LONGLONG Seek(LONGLONG offset, IO::SeekOrigin origin = System::IO::STREAM_SEEK_CUR)
	{
		byte_align();
		return m_stream->Seek(offset, origin);
	}

	bool getbit()
	{
		if (m_bitcnt == 0)
		{
			m_stream->Read(&m_curbyte, 1);
			m_bitcnt = 8;
		}

		m_bitcnt--;

		bool bit = (m_curbyte >> m_bitcnt) & 0x1;

		return bit;
	}

	int getnbits(int nbits);

	int getsnbits(int nbits)
	{
		int value = getnbits(nbits);

		int half_range = 1<<(nbits - 1);

		if (value < half_range)
			return value;
		else
			return (value + 1) - (2 * half_range);
	}

	void byte_align()
	{
		m_bitcnt = 0;
	}

	char getbyte()
	{
		byte_align();

		char value;

		if (m_stream->Read(&value, 1) != 1)
			THROW(-1);

		return value;
	}

	short getshort()
	{
		byte_align();

		uint8 value[2];

		if (m_stream->Read(value, 2) != 2)
			THROW(-1);

		return	(short)value[0] |
					((short)value[1]<<8);
	}

	long getlong()
	{
		byte_align();

		uint8 value[4];

		if (m_stream->Read(value, 4) != 4)
			THROW(-1);

		return	(long)value[0] |
					((long)value[1]<<8) |
					((long)value[2]<<16) |
					((long)value[3]<<24);
	}

	int BeginTag(Tag* ptag)
	{
		uint16 TagCodeAndLength = getshort();

		ptag->Code = TagCodeAndLength>>6;
		ptag->Length = TagCodeAndLength & 0x3F;

		if (ptag->Length == 0x3F)
		{
			ptag->Length = getlong();
		}

		return 0;
	}

	void ReadRGBColor(RGBColor* pcolor)
	{
		if (Read(pcolor, 3) != 3)
			THROW(-1);
	}

	void ReadRGBAColor(RGBAColor* pcolor)
	{
		if (Read(pcolor, 4) != 4)
			THROW(-1);
	}

	void ReadRect(Rect* prect);

	void ReadRGBAColorTransform(ColorTransform* p);

	__release<LDraw::Matrix3f> ReadMatrix();

	System::StringA* ReadString();

#if 0
	std::wstring ReadWString()
	{
		std::wstring value;
		wchar_t c;
		while ((c = getshort()) != 0)
		{
			value += c;
		}

		return value;
	}
#endif

	BitmapCharacter* ReadDefineBitsLossless(int level);

	BitmapCharacter* ReadDefineJPEG(int level);

	FillStyle* ReadFillStyle(uint8 level, Movie* movie);
	void ReadLineStyle(uint8 level);
	vector<FillStyle*> ReadFillStyleArray(uint8 level, Movie* movie);
	void ReadLineStyleArray(uint8 level);
	void ReadShapeWithStyle(uint8 level, ShapeCharacter* shape, Movie* movie);
	void ReadShape(uint8 level, ShapeData* shape, Movie* movie);

	uint8 get_Version() const
	{
		return m_stream->get_Version();
	}

	void ReadHeader()
	{
		m_stream->ReadHeader();
	}

private:

	uint8 m_bitcnt;
	uint8 m_curbyte;
	FormatStream* m_stream;
};

interface ICallback
{
	virtual void OnScript(ActionScript* script) = 0;
};

class SWFExt Decoder : public TagStream
{
public:
	CTOR Decoder(FormatStream* stream) : TagStream(stream)
	{
	}

	void DefineShape(uint8 level, Movie* movie);
	void DefineText(uint8 level, Movie* movie);
	void DefineBitsLossless(uint8 level, Movie* movie);
	void DefineBitsJPEG(uint8 level, Movie* movie);
	void DefineFont(uint8 level, Movie* movie);
	void DefineButton(uint8 level, Movie* movie);
	void PlaceObject(uint8 level, Timeline* timeline, Movie* movie);
	void RemoveObject(uint8 level, Timeline* timeline, Movie* movie);
	void ReadMovieHeader(Movie* movie);
	void ParseTimelineTag(const Tag& tag, Timeline* timeline, Movie* movie, bool bRun);
	void ExecuteTimelineTag(const Tag& tag, Timeline* timeline, Frame* pFrame, Movie* movie);
	void ParseMovieTag(const Tag& tag, Movie* movie);

	ICallback* m_callback;
};

}	// LSWF
}

#endif // __SWF_Decoder_H_
