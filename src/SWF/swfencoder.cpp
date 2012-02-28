#include "stdafx.h"
#include "swf.h"
#include "swfdecoder.h"
#include "swfencoder.h"
#include "_Movie.h"

namespace System
{
using namespace IO;

namespace SWF
{

BitStreamO::BitStreamO(ISequentialByteStream* bytestream) : IO::BitStreamO(bytestream)
{
}

BitStreamO::~BitStreamO()
{
}

void BitStreamO::putbyte(char value)
{
	byte_align();
	if (m_bytestream->Write(&value, 1) != 1)
		throw -1;
}

void BitStreamO::putshort(short value)
{
	putbyte(value & 0xff);	// LSB
	putbyte(value>>8);	// MSB
}

/*
void Encoder::byte_align()
{
	if (m_bitcnt > 0)
	{
		m_pStream->Write(&m_curbyte, 1);
		m_bitcnt = 0;
	}
}
*/

/*
void Encoder::putbit(bool bit)
{
	m_curbyte |= bit<<m_bitcnt;
	m_bitcnt++;

	if (m_bitcnt == 8)
	{
		m_pStream->Write(&m_curbyte, 1);
		m_bitcnt = 0;
		m_curbyte = 0;
	}
}

void Encoder::putnbits(int value, int nbits)
{
	for (int i = 0; i < nbits; i++)
	{
		putbit(value & 1);
		value >>= 1;
	}
}
*/
/*
void Encoder::WriteRect(const Rect* prect)
{
	int nbits = 9;
	putnbits(nbits, 5);
	putnbits(prect->Xmin, nbits);
	putnbits(prect->Xmax, nbits);
	putnbits(prect->Ymin, nbits);
	putnbits(prect->Ymax, nbits);
}
*/

Encoder::Encoder()
{
}

void WriteRect(BitStreamO* bitstream, const Rect* rect)
{
	int nbits = 31;
	bitstream->putnbits(5, nbits);
	bitstream->putnbits(nbits, rect->Xmin);
	bitstream->putnbits(nbits, rect->Xmax);
	bitstream->putnbits(nbits, rect->Ymin);
	bitstream->putnbits(nbits, rect->Ymax);
}

void WriteRGBColor(BitStreamO* bitstream, RGBColor color)
{
	bitstream->m_bytestream->Write(&color, 3);
}

void WriteRGBAColor(BitStreamO* bitstream, RGBAColor color)
{
	bitstream->m_bytestream->Write(&color, 4);
}

void WriteFillStyle(BitStreamO* bitstream, uint8 level, FillStyle* fillStyle)
{
	bitstream->putbyte(fillStyle->m_Type);
	if (fillStyle->m_Type == 0)	// Solid
	{
		if (level >= 3)	// Shape3
		{
			WriteRGBAColor(bitstream, fillStyle->m_color);
		}
		else	// Shape1 / Shape2
		{
			WriteRGBColor(bitstream, fillStyle->m_color);
		}
	}
	else
		ASSERT(0);
}

void WriteFillStyleArray(BitStreamO* bitstream, uint8 level, const vector<FillStyle*> & fillStyles)
{
	ASSERT(fillStyles.GetSize() < 255);
	bitstream->putbyte(fillStyles.GetSize());

	for (int i = 0; i < fillStyles.GetSize(); i++)
	{
		WriteFillStyle(bitstream, level, fillStyles[i]);
	}
}

void WriteLineStyleArray(BitStreamO* bitstream, uint8 level, const vector<LineStyle*> & lineStyles)
{
	// TODO
	bitstream->putbyte(0);
}

void Encoder::WriteHeader()
{
	char c[4] = { 'F', 'W', 'S', 7 };
	m_stream->Write(c, 4);

	// Make room for FileSize
	uint32 fileSize = 0;
	m_stream->Write(&fileSize, 4);
}

void Encoder::WriteMovieHeader(const Rect& FrameSize, uint16 FrameRate, uint16 FrameCount)
{
	BitStreamO bitstream(m_stream);

	WriteRect(&bitstream, &FrameSize);
	bitstream.putshort(FrameRate);
	bitstream.putshort(FrameCount);
}

void Encoder::WriteMovieHeader(const Movie* movie)
{
	BitStreamO bitstream(m_stream);

	Rect FrameSize = movie->GetFrameSize();
	WriteRect(&bitstream, &FrameSize);
	bitstream.putshort(movie->GetFrameRate());
	bitstream.putshort(movie->GetFrameCount());
}

void Encoder::WriteSetBackgroundColorTag(RGBColor color)
{
	Tag tag;
	tag.Code = Tag::SetBackgroundColor;
	tag.Length = 3;
	WriteTagHeader(m_stream, tag);
	WriteRGBColor(&BitStreamO(m_stream), color);
}

void Encoder::WriteShowFrameTag()
{
	Tag tag;
	tag.Code = Tag::ShowFrame;
	tag.Length = 0;
	WriteTagHeader(m_stream, tag);
}

void Encoder::WriteEndTag()
{
	Tag tag;
	tag.Code = 0;
	tag.Length = 0;
	WriteTagHeader(m_stream, tag);
}

/*
void Encoder::WriteMovieTag(const Tag& tag)
{
	switch (Code)
	{
	}
}
*/

void WriteDefineShape(ISequentialByteStream* stream, uint8 level, const ShapeCharacter* shape)
{
	BitStreamO bitstream(stream);

//	ShapeCharacter* shape = new ShapeCharacter;
	bitstream.putshort(shape->m_CharacterID);// = getshort();
	//TRACE("DefineShape %d\n", shape->m_CharacterID);

	WriteRect(&bitstream, &shape->m_Bounds);

	WriteShapeWithStyle(&bitstream, level, shape);

	bitstream.byte_align();
	/*
	ASSERT(m_character[shape->m_CharacterID] == NULL);
	m_character[shape->m_CharacterID] = shape;
	*/
}

void WriteShapeWithStyle(BitStreamO* bitstream, uint8 level, const ShapeCharacter* shape)
{
	WriteFillStyleArray(bitstream, level, shape->m_fillStyles);

	//shape->m_fillStyles = WriteFillStyleArray(level);
	WriteLineStyleArray(bitstream, level, shape->m_lineStyles);

	WriteShape(bitstream, shape);
}

void WriteShape(BitStreamO* bitstream, const ShapeCharacter* shape)
{
//	uint8 NumFillBits = getnbits(4);
//	uint8 NumLineBits = getnbits(4);
	bitstream->putnbits(4, 1);
	bitstream->putnbits(4, 1);

	long CurX = 0;
	long CurY = 0;

	for (int i = 0; i < shape->m_points.GetSize(); i++)
	{
		if (shape->m_types[i] == 0)
		{
			bitstream->putbit(0);	// Non-edge record
			bitstream->putbit(0);
			bitstream->putbit(0);

			if (i == 0)	// FillStyles
			{
				bitstream->putbit(1);
				bitstream->putbit(1);
			}
			else
			{
				bitstream->putbit(0);
				bitstream->putbit(0);
			}

			bitstream->putbit(1);	// Move

			int NumBits = 17;
			bitstream->putnbits(5, NumBits);

			long DeltaX = shape->m_points[i].X - CurX;
			long DeltaY = shape->m_points[i].Y - CurY;

			bitstream->putnbits(NumBits, DeltaX);
			bitstream->putnbits(NumBits, DeltaY);

			CurX = shape->m_points[i].X;
			CurY = shape->m_points[i].Y;

			if (i == 0)
			{
				// FillStyle 0
				bitstream->putnbits(1, 1);
				// FillStyle 1
				bitstream->putnbits(1, 0);
			}
		}
		else
		{
			bitstream->putbit(1);	// Edge record

			if (shape->m_types[i] == 1)
			{
				bitstream->putbit(1);	// Straight Line

				int NumBits = 17;
				bitstream->putnbits(4, NumBits-2);

				bitstream->putbit(1);	// General Line

				long DeltaX = shape->m_points[i].X - CurX;
				long DeltaY = shape->m_points[i].Y - CurY;

				bitstream->putnbits(NumBits, DeltaX);
				bitstream->putnbits(NumBits, DeltaY);

				CurX = shape->m_points[i].X;
				CurY = shape->m_points[i].Y;
			}
			else
			{
				ASSERT(0);
			}
		}
	}

	bitstream->putnbits(6, 0);	// End
}

void WriteMatrix(BitStreamO* bitstream, float m11, float m12, float m21, float m22, long TranslateX, long TranslateY)
{
	//byte_align();

	bool HasScale = 0;
	bitstream->putbit(HasScale);

	/*
	long ScaleX = 1<<16;
	long ScaleY = 1<<16;
	long RotateSkew0 = 0;
	long RotateSkew1 = 0;

	if (HasScale)
	{
		int NScaleBits = getnbits(5);
		ScaleX = getnbits(NScaleBits);
		ScaleY = getnbits(NScaleBits);
	}
	*/

	bool HasRotate = 0;
	bitstream->putbit(HasRotate);
	/*
	if (HasRotate)
	{
		int NRotateBits = getnbits(5);
		RotateSkew0 = getsnbits(NRotateBits);
		RotateSkew1 = getsnbits(NRotateBits);
	}
	*/

	int NTranslateBits = 31;
	bitstream->putnbits(5, NTranslateBits);
	bitstream->putnbits(NTranslateBits, TranslateX);
	bitstream->putnbits(NTranslateBits, TranslateY);

//	long TranslateX = getsnbits(NTranslateBits);
//	long TranslateY = getsnbits(NTranslateBits);
//	return LDraw::Matrix(ScaleX/65536.0, RotateSkew0/65536.0, /*0,*/ RotateSkew1/65536.0, ScaleY/65536.0, /*0,*/ TranslateX, TranslateY/*, 1*/);

//	return gmMatrix3::skewX(RotateSkew0) * gmMatrix3::translate(TranslateX, TranslateY);
}

void Encoder::Close()
{
// Update FileLength
	uint32 pos = (uint32)m_stream->Seek(0, System::IO::STREAM_SEEK_CUR);
	m_stream->Seek(4, System::IO::STREAM_SEEK_SET);
	uint32 FileLength = pos;
	m_stream->Write(&FileLength, 4);

//	m_stream->Release();
	m_stream = NULL;
}

void WriteTagHeader(ISequentialByteStream* stream, const Tag& tag)
{
	if (tag.Length >= 63)
	{
		uint16 TagCodeAndLength = (tag.Code<<6) | 0x3F;
		stream->Write(&TagCodeAndLength, 2);
		stream->Write(&tag.Length, 4);
	}
	else
	{
		uint16 TagCodeAndLength = (tag.Code<<6) | tag.Length;
		stream->Write(&TagCodeAndLength, 2);
	}
}

}
}
