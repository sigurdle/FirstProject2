#pragma once

#ifndef SWFExt
#define SWFExt	DECLSPEC_DLLIMPORT
#endif

//#include "Movie.h"

namespace System
{
namespace SWF
{

class SWFExt BitStreamO : public System::IO::BitStreamO
{
public:
	CTOR BitStreamO(System::IO::ISequentialByteStream* bytestream);
	~BitStreamO();

	void putbyte(char value);
	void putshort(short value);
};

SWFExt void WriteMatrix(BitStreamO* bitstream, float m11, float m12, float m21, float m22, long TranslateX, long TranslateY);
SWFExt void WriteDefineShape(System::IO::ISequentialByteStream* stream, uint8 level, const ShapeCharacter* shape);
SWFExt void WriteRect(BitStreamO* bitstream, const Rect* rect);
SWFExt void WriteRGBColor(BitStreamO* bitstream, RGBColor color);
SWFExt void WriteRGBAColor(BitStreamO* bitstream, RGBAColor color);
SWFExt void WriteShapeWithStyle(BitStreamO* bitstream, uint8 level, const ShapeCharacter* shape);
SWFExt void WriteFillStyle(BitStreamO* bitstream, uint8 level, FillStyle fillStyle);
SWFExt void WriteFillStyleArray(BitStreamO* bitstream, uint8 level, const vector<FillStyle*>& fillStyles);
SWFExt void WriteLineStyleArray(BitStreamO* bitstream, uint8 level, const vector<LineStyle*>& lineStyles);
SWFExt void WriteShape(BitStreamO* bitstream, const ShapeCharacter* shape);

SWFExt void WriteTagHeader(System::IO::ISequentialByteStream* stream, const Tag& tag);

class SWFExt Encoder
{
public:
	CTOR Encoder();

	System::IO::ISequentialByteStream* m_stream;

	void WriteEndTag();
	void WriteShowFrameTag();

	void WriteHeader();

	/*
	void WriteHeader()
	{
		BYTE c[4];
		c[0] = 'F';
		c[1] = 'W';
		c[2] = 'S';
		c[3] = 7;
		if (m_stream->Write(c, 4) != 4)
			throw -1;

		// Make room for FileLength
		m_stream->Seek(4, System::IO::STREAM_SEEK_CUR);
	}
	*/

	void WriteMovieHeader(const Rect& FrameSize, uint16 FrameRate, uint16 FrameCount);
	void WriteMovieHeader(const Movie* movie);

	void WriteSetBackgroundColorTag(RGBColor color);

	void Close();
};

	/*
class SWFExt Encoder
{
public:
	Encoder();

	ISequentialByteStream* m_pStream;

	uint8 m_bitcnt;
	uint8 m_curbyte;

	void byte_align();
	void putbit(bool bit);
	void putnbits(int value, int nbits);

	void WriteRGBColor(const RGBColor* pcolor);
	void WriteRect(const Rect* prect);

	void WriteHeader();
	void WriteMovieHeader(Movie* pMovie);

	void WriteMovieTag(const Tag& tag);
};
*/

}	// SWF
}
