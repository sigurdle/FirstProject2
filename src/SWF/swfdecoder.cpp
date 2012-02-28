#include "stdafx.h"
#include "swf.h"
#include "swfdecoder.h"
#include "_Movie.h"
//#include "ActionScriptFunction.h"
#include "ActionNames.h"

#include "JFIF/JFIF.h"
#ifdef _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/JFIF")
#else
#pragma comment(lib, "../../lib/Win32/Release/JFIF")
#endif

namespace System
{
namespace SWF
{

void PrintActions(uint8* p, ULONG length)
{
	uint8 ActionCode;
	while ((ActionCode = *p++) != 0)
	{
		TRACE("%s - 0x%x\n", ActionNames[ActionCode], ActionCode);
		uint16 Length = 0;
		if (ActionCode >= 0x80)
		{
			Length = *p++;
			Length |= (long)(*p++)<<8;
		}

		uint8* start = p;
		p = start+Length;
	}

#if 0
				switch (ActionCode)
				{
				case ActionPrevFrame:
					{
						TRACE("ActionPrevFrame\n");
					}
					break;

				case ActionGotoFrame:
					{
						TRACE("ActionGotoFrame\n");
					}
					break;

				case ActionPush:
					{
						TRACE("ActionPush\n");

						uint8 Type = *p++;

						switch (Type)
						{
						case 0:
							{
								std::string value;
								while (*p)
								{
									value += *p++;
								}
								//m_stack.push_back(value);
							}
							break;

						default:
							;//ATLASSERT(0);
						}
					}
					break;

				default:
					TRACE("Unknown Action: 0x%x\n", ActionCode);
				//	Seek(Length);
				}
#endif
}

int TagStream::getnbits(int nbits)
{
	int value = 0;

	for (int i = 0; i < nbits; i++)
	{
		value <<= 1;
		if (getbit()) value |= 1;
	}

	return value;
}

void TagStream::ReadRGBAColorTransform(ColorTransform* p)
{
	byte_align();

	bool bHasAddTerms = getbit();
	bool bHasMulTerms = getbit();
	int nbits = getnbits(4);

	if (bHasMulTerms)
	{
		p->MulR = getsnbits(nbits);
		p->MulG = getsnbits(nbits);
		p->MulB = getsnbits(nbits);
		p->MulA = getsnbits(nbits);
	}
	else
	{
		p->MulR = 1<<8;
		p->MulG = 1<<8;
		p->MulB = 1<<8;
		p->MulA = 1<<8;
	}

	if (bHasAddTerms)
	{
		p->AddR = getsnbits(nbits);
		p->AddG = getsnbits(nbits);
		p->AddB = getsnbits(nbits);
		p->AddA = getsnbits(nbits);
	}
	else
	{
		p->AddR = 0;
		p->AddG = 0;
		p->AddB = 0;
		p->AddA = 0;
	}
}

__release<LDraw::Matrix3f> TagStream::ReadMatrix()
{
	byte_align();

	bool HasScale = getbit();

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

	bool HasRotate = getbit();
	if (HasRotate)
	{
		int NRotateBits = getnbits(5);
		RotateSkew0 = getsnbits(NRotateBits);
		RotateSkew1 = getsnbits(NRotateBits);
	}

	int NTranslateBits = getnbits(5);
	long TranslateX = getsnbits(NTranslateBits);
	long TranslateY = getsnbits(NTranslateBits);

	return new LDraw::Matrix3f(ScaleX/65536.0, RotateSkew0/65536.0, /*0,*/ RotateSkew1/65536.0, ScaleY/65536.0, /*0,*/ TranslateX, TranslateY/*, 1*/);

//	return gmMatrix3::skewX(RotateSkew0) * gmMatrix3::translate(TranslateX, TranslateY);
}

void FormatStream::ReadHeader()
{
	uint8 c[4];
	if (Read(c, 4) != 4) throw -1;

	if (c[0] == 'F')
	{
		m_Compressed = false;
	}
	else if (c[0] == 'C')
	{
		m_Compressed = true;
	}
	else
	{
		throw -1;
	}

	if (c[1] != 'W')
		throw -1;

	if (c[2] != 'S')
		throw -1;

	m_Version = c[3];
	if (Read(&m_FileSize, 4) != 4) throw -1;
	m_FileSize = LittleEndian32(m_FileSize);

//	printf("FileSize %d\n", m_FileSize);

//	printf("Compressed: %d\n", m_Compressed);

	if (m_Compressed)
	{
		m_zlibDecoder = new ZLIBDecoder(m_stream);
	//	m_zlibDecoder->start();
	//	m_zlibDecoder->start_block();
	}
}

FillStyle* TagStream::ReadFillStyle(uint8 level, Movie* movie)
{
	FillStyle* fillStyle;

	uint8 Type = getbyte();

	//fillStyle->m_Type = Type;

	if (Type == 0)	// Solid
	{
		RGBAColor color;

		if (level >= 3)	// Shape3
		{
			ReadRGBAColor(&color);
		}
		else	// Shape1 / Shape2
		{
			ReadRGBColor(&color);
			color.Alpha = 255;
		}

		fillStyle = new FillStyle(Type, color);
	}
	else if (Type & 0x40)	// Bitmap
	{
		uint16 BitmapID = getshort();
		ReadMatrix();

		fillStyle = new FillStyle(Type, (BitmapCharacter*)movie->GetCharacter(BitmapID));
	}
	else
		ASSERT(0);

	return fillStyle;
}

void TagStream::ReadLineStyle(uint8 level)
{
	short Width = getshort();

	RGBAColor color;

	if (level >= 3)	// Shape3
	{
		ReadRGBAColor(&color);
	}
	else	// Shape1 / Shape2
	{
		ReadRGBColor(&color);
		color.Alpha = 255;
	}
}

vector<FillStyle*> TagStream::ReadFillStyleArray(uint8 level, Movie* movie)
{
	vector<FillStyle*> array;

	int count = getbyte();
	if (level >= 2)
	{
		if (count == 0xFF)
		{
			count = getshort();
		}
	}

	for (int i = 0; i < count; i++)
	{
		FillStyle* fillStyle = ReadFillStyle(level, movie);
		fillStyle->m_index = i;
		array.Add(fillStyle);
	}

	return array;
}

void TagStream::ReadLineStyleArray(uint8 level)
{
	int count = getbyte();
	if (level >= 2)
	{
		if (count == 0xFF)
		{
			count = getshort();
		}
	}

	for (int i = 0; i < count; i++)
	{
		ReadLineStyle(level);
	}
}

void TagStream::ReadShapeWithStyle(uint8 level, ShapeCharacter* shape, Movie* movie)
{
	shape->m_fillStyles = ReadFillStyleArray(level, movie);
	ReadLineStyleArray(level);

	ReadShape(level, shape, movie);
}

void TagStream::ReadShape(uint8 level, ShapeData* shape, Movie* movie)
{
	uint8 NumFillBits = getnbits(4);
	uint8 NumLineBits = getnbits(4);

	long CurX = 0;//(shape->m_ShapeBounds.Xmin);// + (shape->m_ShapeBounds.Xmax - shape->m_ShapeBounds.Xmin) / 2);
	long CurY = 0;//(shape->m_ShapeBounds.Ymin);// + (shape->m_ShapeBounds.Ymax - shape->m_ShapeBounds.Ymin) / 2);

	while (1)
	{
		bool TypeFlag = getbit();
		if (TypeFlag)	// Edge record
		{
			bool StraightFlag = getbit();
			int NumBits = getnbits(4) + 2;

			if (StraightFlag)
			{
				bool GeneralLineFlag = getbit();
				if (GeneralLineFlag)
				{
					long DeltaX = getsnbits(NumBits);
					long DeltaY = getsnbits(NumBits);

					CurX += DeltaX;
					CurY += DeltaY;
				}
				else
				{
					bool VertLineFlag = getbit();
					if (VertLineFlag)
					{
						long DeltaY = getsnbits(NumBits);
						CurY += DeltaY;
					}
					else
					{
						long DeltaX = getsnbits(NumBits);
						CurX += DeltaX;
					}
				}

				shape->LineTo(CurX, CurY);
			}
			else
			{
				long ControlX = getsnbits(NumBits) + CurX;
				long ControlY = getsnbits(NumBits) + CurY;
				long AnchorX = getsnbits(NumBits) + ControlX;
				long AnchorY = getsnbits(NumBits) + ControlY;

				shape->CurveTo(ControlX, ControlY, AnchorX, AnchorY);

				CurX = AnchorX;
				CurY = AnchorY;
			}
		}
		else	// Non-edge record
		{
			int state = getbit();
			state |= getbit()<<1;
			state |= getbit()<<2;
			state |= getbit()<<3;
			state |= getbit()<<4;

			if (state == 0)
			{
				break;
			}
			else
			{
				if (state & 16)
				{
					uint8 MoveBits = getnbits(5);
					CurX = getsnbits(MoveBits);
					CurY = getsnbits(MoveBits);

					shape->MoveTo(CurX, CurY);
				}

				if (state & 8)
				{
					int FillStyle0 = getnbits(NumFillBits);
				}

				if (state & 4)
				{
					int FillStyle1 = getnbits(NumFillBits);
				}

				if (state & 2)
				{
					int LineStyle = getnbits(NumLineBits);
				}

				if (state & 1)
				{
					// ???
					ASSERT(0);
					ReadFillStyleArray(level, movie);
					ReadLineStyleArray(level);
				}
			}
		}
	}
}

BitmapCharacter* TagStream::ReadDefineBitsLossless(int level)
{
	BitmapCharacter* bitmap = new BitmapCharacter;
	bitmap->m_CharacterID = getshort();
	TRACE("DefineBitsLossless(2) %d\n", bitmap->m_CharacterID);

	bitmap->m_Format = getbyte();
	bitmap->m_Width = getshort();
	bitmap->m_Height = getshort();
	if (bitmap->m_Format == 3)
	{
		bitmap->m_BitmapColorTableSize = getbyte();
	}

	ZLIBDecoder* zlibDecoder = new ZLIBDecoder(m_stream);
	//zlibDecoder->AddRef();

//	zlibDecoder->start();
//	zlibDecoder->start_block();

	int bitcount;

	if (bitmap->m_Format == 3)	// 8-bit
	{
		bitmap->m_palette = new RGBAColor[(int)bitmap->m_BitmapColorTableSize+1];

		for (int i = 0; i <= bitmap->m_BitmapColorTableSize; i++)
		{
			if (level == 1)
			{
				zlibDecoder->Read(&bitmap->m_palette[i], 3);
				bitmap->m_palette[i].Alpha = 255;
			}
			else
			{
				zlibDecoder->Read(&bitmap->m_palette[i], 4);
			}
		}

		bitcount = 8;
	}
	else if (bitmap->m_Format == 4)	// 16-bit (one bit ignored)
	{
		if (level == 2)	// 15-bit for this is an error
			throw -1;

		bitcount = 16;
	}
	else if (bitmap->m_Format == 5)	// 24-bit or 32-bit
	{
	// 32 bits for both tags, but Alpha is only used for DefineBitsLossless2
		bitcount = 32;
	}
	else
		throw -1;

	bitmap->m_rowbytes = ROWBYTES_DWORD(bitmap->m_Width, bitcount);
//	BYTE* rowbuffer = new BYTE[rowbytes];

	bitmap->m_bits = new uint8[bitmap->m_rowbytes * bitmap->m_Height];

	for (int y = 0; y < bitmap->m_Height; y++)
	{
		uint8* row = bitmap->m_bits + y*bitmap->m_rowbytes;
		zlibDecoder->Read(row, bitmap->m_rowbytes);
	}

	//zlibDecoder->Release();

//	LONGLONG endpos = Seek(0);
//	ULONG length = endpos - startpos;

	return bitmap;
}

BitmapCharacter* TagStream::ReadDefineJPEG(int level)
{
	BitmapCharacter* bitmap = new BitmapCharacter;
	bitmap->m_CharacterID = getshort();

	if (level > 2)
	{
		uint32 AlphaOffset = getlong();
	}

	TRACE("DefineJPEG %d\n", bitmap->m_CharacterID);

	Imaging::JPEGDecoder* pFormat = new Imaging::JPEGDecoder(m_stream);

	pFormat->ReadJPEGMarker();

	// Must call this twice apparently
	pFormat->ReadHeader();
	pFormat->ReadHeader();

	pFormat->StartScans();

	bitmap->m_Width = pFormat->GetWidth();
	bitmap->m_Height = pFormat->GetHeight();

	int bitcount = 32;

	bitmap->m_rowbytes = ROWBYTES_DWORD(bitmap->m_Width, bitcount);

	bitmap->m_bits = new uint8[bitmap->m_rowbytes * bitmap->m_Height];

	for (int y = 0; y < bitmap->m_Height; y++)
	{
		uint8* dst = bitmap->m_bits + bitmap->m_rowbytes*y;

		pFormat->NextScanline();
		pFormat->CopyScanline(dst+offsetof(LDraw::PixelRGBAP_32, r), dst+offsetof(LDraw::PixelRGBAP_32, g), dst+offsetof(LDraw::PixelRGBAP_32, b), 4);

		for (int x = 0; x < bitmap->m_Width; x++)
		{
			*(dst+offsetof(LDraw::PixelRGBAP_32, a)) = 255;
			dst += 4;
		}
	}

	delete pFormat;

	return bitmap;
}

void TagStream::ReadRect(Rect* prect)
{
	int nbits = getnbits(5);
	prect->Xmin = getsnbits(nbits);
	prect->Xmax = getsnbits(nbits);
	prect->Ymin = getsnbits(nbits);
	prect->Ymax = getsnbits(nbits);
}

void Decoder::ReadMovieHeader(Movie* movie)
{
	Rect FrameSize;
	ReadRect(&FrameSize);
	movie->SetFrameSize(FrameSize.Xmax, FrameSize.Ymax);

	//printf("FrameSize: %d, %d\n", movie->m_FrameSize.Xmax, movie->m_FrameSize.Ymax);

	movie->SetFrameRate(getshort());
	movie->SetFrameCount(getshort());

//	printf("FrameRate: %d\n", movie->m_FrameRate);
//	printf("FrameCount: %d\n", movie->m_FrameCount);

	// Prepare for new frame
	Frame* pFrame = new Frame;
	pFrame->m_stream = this;
	pFrame->m_streamPos = Seek(0);
	movie->m_frames.Add(pFrame);
}

void Decoder::DefineShape(uint8 level, Movie* movie)
{
	ShapeCharacter* shape = new ShapeCharacter;
	shape->SetCharacterID(getshort());
	TRACE("DefineShape %d\n", shape->GetCharacterID());

	Rect rect;
	ReadRect(&rect);
	shape->SetBounds(rect);

	ReadShapeWithStyle(level, shape, movie);

	movie->DefineShape(level, shape);
}

void Decoder::DefineText(uint8 level, Movie* movie)
{
	TextCharacter* pText = new TextCharacter;

	pText->m_CharacterID = getshort();
	TRACE("DefineText %d\n", pText->m_CharacterID);

	ReadRect(&pText->m_Bounds);
	byte_align();
	pText->m_Transform = ReadMatrix();

	uint8 glyphBits = getbyte();
	uint8 advanceBits = getbyte();

	uint16 FontID = 0;
	uint16 FontHeight = 0;
	RGBAColor color;

	while (1)
	{
		uint8 flags = getbyte();

		if (flags == 0)
			break;

		if ((flags>>7) == 1)
		{
			bool bHasFont = (flags >> 3) & 1;
			bool bHasColor = (flags >> 2) & 1;
			bool bHasXOffset = (flags >> 1) & 1;
			bool bHasYOffset = (flags) & 1;

			if (bHasFont)
			{
				FontID = getshort();
			}

			if (bHasColor)
			{
				if (level >= 2)
				{
					ReadRGBAColor(&color);
				}
				else
				{
					ReadRGBColor(&color);
					color.Alpha = 255;
				}
			}

			short XOffset = 0;
			short YOffset = 0;

			if (bHasXOffset)
			{
				XOffset = getshort();
			}

			if (bHasYOffset)
			{
				YOffset = getshort();
			}

			if (bHasFont)
			{
				FontHeight = getshort();
			}

			uint8 glyphCount = getbyte();

			GlyphRun* run = new GlyphRun;

			run->m_font = dynamic_cast<FontCharacter*>(movie->GetCharacter(FontID));
			ASSERT(run->m_font);

			run->m_fontHeight = FontHeight;
			run->m_color = color;
			run->m_XOffset = XOffset;
			run->m_YOffset = YOffset;

			for (int i = 0; i < glyphCount; i++)
			{
				int glyphIndex = getnbits(glyphBits);
				int advanceWidth = getnbits(glyphBits);

				run->m_glyphs.Add(glyphIndex);
				run->m_widths.Add(advanceWidth);
			}

			pText->m_runs.Add(run);
		}
		else
			ASSERT(0);
	}

	movie->DefineShape(level, pText);
}

void Decoder::DefineBitsLossless(uint8 level, Movie* movie)
{
	BitmapCharacter* bitmap = ReadDefineBitsLossless(1);

	movie->DefineBitsLossless(level, bitmap);

#if 0
	BMPEncoder* encoder = new BMPEncoder(new ByteStreamWriter("C:/test.bmp"));

	LDraw::BitmapData bmdata;
	bmdata.Width = bitmap->m_Width;
	bmdata.Height = bitmap->m_Height;
	bmdata.Stride = bitmap->m_rowbytes;
	bmdata.Scan0 = bitmap->m_bits;

	encoder->SetFormat(bitmap->m_Width, bitmap->m_Height, bitmap->m_BitmapColorTableSize+1);
	encoder->SetPalette(&bitmap->m_palette->Red, 4, &bitmap->m_palette->Green, 4, &bitmap->m_palette->Blue, 4);
	encoder->WriteHeader();
	encoder->WriteBitmap(&bmdata);

	delete encoder;
#endif
}

void Decoder::DefineBitsJPEG(uint8 level, Movie* movie)
{
	BitmapCharacter* bitmap = ReadDefineJPEG(level);

	movie->DefineBitsLossless(level, bitmap);	// Well
}


void Decoder::DefineButton(uint8 level, Movie* movie)
{
	ButtonCharacter* pButton =  new ButtonCharacter;
	pButton->m_CharacterID = getshort();
	TRACE("DefineButton%d %d\n", level, pButton->m_CharacterID);

	if (level >= 2)
	{
		getnbits(7);
		pButton->m_TrackAsMenu = getbit();

		uint16 ActionOffset = getshort();
	}

	uint8 flags;
	while ((flags = getbyte()) != 0)
	{
		bool bButtonStateUp = flags & 1;
		bool bButtonStateOver = (flags>>1) & 1;
		bool bButtonStateDown = (flags>>2) & 1;
		bool bButtonHitTest = (flags>>3) & 1;

		ButtonRecord* pRecord = new ButtonRecord;

		uint16 CharacterID = getshort();
		pRecord->m_shape = (ShapeCharacter*)movie->GetCharacter(CharacterID);
		pRecord->m_PlaceDepth = getshort();
		pRecord->m_Transform = ReadMatrix();

		if (level >= 2)
		{
			ColorTransform colorTransform;
			ReadRGBAColorTransform(&colorTransform);
		}

		if (bButtonStateUp)
		{
			pButton->m_StateUp.Add(pRecord);
		}

		if (bButtonStateDown)
		{
			pButton->m_StateDown.Add(pRecord);
		}

		if (bButtonStateOver)
		{
			pButton->m_StateOver.Add(pRecord);
		}

		if (bButtonHitTest)
		{
			pButton->m_HitTest.Add(pRecord);
		}
	}

	uint16 CondActionSize;
	while ((CondActionSize = getshort()) != 0)
	{
		LONGLONG start = Seek(0) - 2;

		ButtonActionScript* pScript = new ButtonActionScript;

		pScript->m_cond = getshort();
		/*
		bool CondIdleToOverDown = getbit();
		bool CondOutDownToIdle = getbit();
		bool CondOutDownToOverDown = getbit();
		bool CondOverDownToOutDown = getbit();
		bool CondOverDownToOverUp = getbit();
		bool CondOverUpToOverDown = getbit();
		bool CondOverUpToIdle = getbit();
		bool CondIdleToOverUp = getbit();
		uint8 CondKeyPress = getnbits(7);
		bool CondOverDownToIdle = getbit();
		*/

	//	Instructions code;

		pScript->m_length = CondActionSize - 4;
		pScript->m_data = new uint8[pScript->m_length];

		Read(pScript->m_data, pScript->m_length);

		pButton->m_scripts.Add(pScript);

	//	PrintActions(pScript->m_data, pScript->m_length);

		Seek(start + CondActionSize, System::IO::STREAM_SEEK_SET);
	}

	movie->DefineBitsLossless(0, pButton);	// Well
}

void Decoder::DefineFont(uint8 level, Movie* movie)
{
	FontCharacter* pFont = new FontCharacter;
	pFont->m_CharacterID = getshort();
	TRACE("DefineFont2 %d\n", pFont->m_CharacterID);

	uint8 flags = getbyte();

	bool bFontFlagsWideOffsets = (flags>>3) & 1;

	uint8 LanguageCode = getbyte();
	uint8 FontNameLen = getbyte();
	char FontName[256];
	Read(FontName, FontNameLen);
	FontName[FontNameLen] = 0;
	pFont->m_FontName = new StringA(string_copy(FontName));

	uint16 NumGlyphs = getshort();

	uint32 OffsetTable[256];	// TODO

	uint32 CodeTableOffset;

	LONGLONG start = Seek(0, System::IO::STREAM_SEEK_CUR);

	if (bFontFlagsWideOffsets)
	{
		for (int i = 0; i < NumGlyphs; i++)
		{
			OffsetTable[i] = getlong();
		}

		CodeTableOffset = getlong();
	}
	else
	{
		for (int i = 0; i < NumGlyphs; i++)
		{
			OffsetTable[i] = (uint16)getshort();
		}

		CodeTableOffset = (uint16)getshort();
	}

	for (int i = 0; i < NumGlyphs; i++)
	{
		Seek(start + OffsetTable[i], System::IO::STREAM_SEEK_SET);

		ShapeData* shape = new ShapeData;

		ReadShape(level, shape, movie);

		pFont->m_glyphShapes.Add(shape);
	}

	movie->DefineShape(level, pFont);
}

void Decoder::PlaceObject(uint8 level, Timeline* timeline, Movie* movie)
{
	bool PlaceFlagHasClipActions = getbit();
	bool PlaceFlagHasClipDepth = getbit();
	bool PlaceFlagHasName = getbit();
	bool PlaceFlagHasRatio = getbit();
	bool PlaceFlagHasColorTransform = getbit();
	bool PlaceFlagHasMatrix = getbit();
	bool PlaceFlagHasCharacter = getbit();
	bool PlaceFlagMove = getbit();

	uint16 Depth = getshort();
//	WORD CharacterID;

	PlacedCharacter* placedCharacter = NULL;
	
	if (PlaceFlagHasCharacter)
	{
		if (PlaceFlagMove)
		{
			delete timeline->GetPlacedCharacterAtDepth(Depth);
			timeline->ClearPlacedCharacterAtDepth(Depth);
		}

		placedCharacter = new PlacedCharacter;

		placedCharacter->m_parent = timeline;
		placedCharacter->SetMember(ASTR("_parent"), dynamic_cast<Object*>(timeline));

	//	placedCharacter->m_CharacterID = getshort();
		uint16 characterID = getshort();
		placedCharacter->m_character = movie->GetCharacter(characterID);

		timeline->PlaceCharacterAtDepth(placedCharacter, Depth);

		TRACE("PlaceObject2 %d at Depth %d\n", characterID, Depth);

		// hm...
		Sprite* sprite = dynamic_cast<Sprite*>(placedCharacter->m_character);
		if (sprite != NULL)
		{
			sprite->m_placed = placedCharacter;
		}
	}
	else
	{
		placedCharacter = timeline->GetPlacedCharacterAtDepth(Depth);
		ASSERT(placedCharacter);

		TRACE("PlaceObject2 %d at Depth %d\n", placedCharacter->m_character->GetCharacterID(), Depth);
	}

	if (PlaceFlagHasMatrix)
	{
		placedCharacter->m_transform = ReadMatrix();
	}

	if (PlaceFlagHasColorTransform)
	{
		ReadRGBAColorTransform(&placedCharacter->m_colorTransform);
	}

	if (PlaceFlagHasRatio)
	{
		uint16 Ratio = getshort();
	}

	if (PlaceFlagHasName)
	{
		placedCharacter->m_name = ReadString();
		placedCharacter->SetMember(ASTR("_name"), placedCharacter->m_name);
	}

	if (PlaceFlagHasClipDepth)
	{
		uint16 ClipDepth = getshort();
	}

	if (get_Version() >= 5)
	{
		if (PlaceFlagHasClipActions)
		{
			uint16 reserved = getshort();
			ASSERT(reserved == 0);

			uint32 clipflags;
			if (get_Version() >= 6)
			{
				clipflags = getlong();
			}
			else
			{
				clipflags = getshort();
			}

			while (1)
			{
				uint32 clipflags;
				if (get_Version() >= 6)
				{
					clipflags = getlong();
				}
				else
				{
					clipflags = getshort();
				}

				if (clipflags == 0)
					break;

				uint32 size = getlong();

				/*	TODO
				if (clipflags & 1)
				{
					uint8 charcode = getbyte();
				}
				*/

				//Sprite

				ButtonActionScript* pScript = new ButtonActionScript;

				pScript->m_length = size;
				pScript->m_data = new uint8[size];
				Read(pScript->m_data, pScript->m_length);
				pScript->m_cond = clipflags;	// TODO.. 

			//	Sprite sprite = placedCharacter->m_character;
			//	Sprite::_Sprite* pSprite = (Sprite::_Sprite*)sprite.m_p;
			//	ASSERT(pSprite);

				placedCharacter->m_scripts.Add(pScript);

			//	PrintActions(pScript->m_data, size);
			}
		}
	}

	// Load event
	{
		for (int i = 0; i < placedCharacter->m_scripts.GetSize(); i++)
		{
			ButtonActionScript* pScript = placedCharacter->m_scripts[i];

			if (m_callback)
			{
				m_callback->OnScript(pScript);
			}

			if (pScript->m_cond & 1)	// Load event
			{
				System::ActionScripting::VM vm;
			//	VM2 vm;
				vm.m_flags = movie->m_scriptFlags;
				vm.m_breakpoint = movie->m_scriptBreakpoint;
				vm.m_userobject = movie->m_scriptUserObject;

				vm.m_pFrame = new System::ActionScripting::StackFrame;
				vm.m_pFrame->m_pContext = pScript->m_context;
				vm.m_pFrame->m_instructionsData = pScript->m_data;
				vm.m_pFrame->m_instructionsLength = pScript->m_length;

				vm.m_pc = pScript->m_data;

				vm.m_pFrame->m_variables[ASTR("this")] = System::ActionScripting::StkElt(static_cast<Object*>(placedCharacter));

				while (vm.next())
					;

			//	TRACE("%s\n", vm.m_str.c_str());

				ASSERT(vm.m_stack.GetSize() == 0);
			}
		}
	}
}

void Decoder::RemoveObject(uint8 level, Timeline* timeline, Movie* movie)
{
	uint16 Depth = getshort();

	TRACE("RemoveObject2 depth: %d\n", Depth);

//	ASSERT(timeline->m_depth[Depth] != NULL);
	timeline->ClearPlacedCharacterAtDepth(Depth);
}

void Frame::DoActions(PlacedCharacter* placed)
{
	for (int i = 0; i < m_doActions.GetSize(); i++)
	{
		DoActionScript* pDoAction = m_doActions[i];


		System::ActionScripting::ActionContext* pActionContext = new System::ActionScripting::ActionContext;

		System::ActionScripting::VM vm;
		vm.m_pFrame = new System::ActionScripting::StackFrame;
		vm.m_pFrame->m_pContext = pActionContext;//pScript->m_context;
		vm.m_pFrame->m_instructionsData = pDoAction->m_data;
		vm.m_pFrame->m_instructionsLength = pDoAction->m_length;

		vm.m_pc = pDoAction->m_data;

		vm.m_pFrame->m_variables[ASTR("this")] = System::ActionScripting::StkElt(static_cast<Object*>(placed));

		while (vm.next())
			;

		ASSERT(vm.m_stack.GetSize() == 0);

		delete pDoAction;
	}
}

void Decoder::ExecuteTimelineTag(const Tag& tag, Timeline* timeline, Frame* pFrame, Movie* movie)
{
	switch (tag.Code)
	{
		/*
	case Tag::ShowFrame:
		{
		//	TRACE("ShowFrame %d\n", timeline->m_DecodedFrameCount);

			if (bRun)
			{
				// Perform accumulated DoAction tags for this frame

				timeline->m_frames[timeline->m_DecodedFrameCount]->DoActions(NULL);
			}
			//m_doActions.clear();

			timeline->m_DecodedFrameCount++;
		//	Invalidate();

			// Prepare for new frame
			Frame* pFrame = new Frame;
			pFrame->m_stream = this;
			pFrame->m_streamPos = Seek(0);
			timeline->m_frames.push_back(pFrame);

			TRACE("\n");
		}
		break;
*/
	case Tag::FrameLabel:
		break;

  case Tag::PlaceObject2:
		{
			PlaceObject(2, timeline, movie);
		}
		break;

	case Tag::RemoveObject2:
		{
			RemoveObject(2, timeline, movie);
		}
		break;

	case Tag::DoAction:
		{
			TRACE("DoAction, Length: %d\n", tag.Length);

			DoActionScript* pDoAction = new DoActionScript;

			pDoAction->m_length = tag.Length;
			pDoAction->m_data = new uint8[tag.Length];
			Read(pDoAction->m_data, tag.Length);

			//uint8* p = buffer;

			pFrame->m_doActions.Add(pDoAction);

			//PrintActions(pDoAction->m_codeData, tag.Length);
		}
		break;

	case Tag::SoundStreamHead:
		{
			TRACE("SoundStreamHead\n");
		}
		break;

	case Tag::SoundStreamHead2:
		{
			TRACE("SoundStreamHead2\n");
		}
		break;

	case Tag::DefineEditText:
		{
			TRACE("DefineEditText\n");
		}
		break;

	case Tag::ExportAssets:
		{
			TRACE("ExportAssets\n");
		}
		break;

	default:
		{
			TRACE("Unknown tag code: %d, Length: %d\n", tag.Code, tag.Length);
		}
		break;
	}
}

void Decoder::ParseTimelineTag(const Tag& tag, Timeline* timeline, Movie* movie, bool bRun)
{
	switch (tag.Code)
	{
	case Tag::ShowFrame:
		{
		//	TRACE("ShowFrame %d\n", timeline->m_DecodedFrameCount);

			if (bRun)
			{
				// Perform accumulated DoAction tags for this frame

				timeline->m_frames[timeline->m_DecodedFrameCount]->DoActions(NULL);
			}
			//m_doActions.clear();

			timeline->m_DecodedFrameCount++;
		//	Invalidate();

			// Prepare for new frame
			Frame* pFrame = new Frame;
			pFrame->m_stream = this;
			pFrame->m_streamPos = Seek(0);
			timeline->m_frames.Add(pFrame);

			TRACE("\n");
		}
		break;

	case Tag::FrameLabel:
		{
			StringA* name = ReadString();
			TRACE("FrameLabel %s\n", name->c_str());

			timeline->m_labels[name] = timeline->m_DecodedFrameCount+1;
		}
		break;

	case Tag::PlaceObject2:
		{
			PlaceObject(2, timeline, movie);
		}
		break;

	case Tag::RemoveObject2:
		{
			RemoveObject(2, timeline, movie);
		}
		break;

	case Tag::DoAction:
		{
			TRACE("DoAction, Length: %d\n", tag.Length);

			DoActionScript* pDoAction = new DoActionScript;

			pDoAction->m_length = tag.Length;
			pDoAction->m_data = new uint8[tag.Length];
			Read(pDoAction->m_data, tag.Length);

			//uint8* p = buffer;

			timeline->m_frames[timeline->m_DecodedFrameCount]->m_doActions.Add(pDoAction);

			//PrintActions(pDoAction->m_codeData, tag.Length);
		}
		break;

	case Tag::SoundStreamHead:
		{
			TRACE("SoundStreamHead\n");
		}
		break;

	case Tag::SoundStreamHead2:
		{
			TRACE("SoundStreamHead2\n");
		}
		break;

	case Tag::DefineEditText:
		{
			TRACE("DefineEditText\n");
		}
		break;

	case Tag::ExportAssets:
		{
			TRACE("ExportAssets\n");
		}
		break;

	default:
		{
			TRACE("Unknown tag code: %d, Length: %d\n", tag.Code, tag.Length);
		}
		break;
	}
}

void Decoder::ParseMovieTag(const Tag& tag, Movie* movie)
{
	switch (tag.Code)
	{
		/*
	case Tag::ShowFrame:
		{
			ATLTRACE("ShowFrame\n");

		//	Invalidate();
		}
		break;
		*/

	case Tag::SetBackgroundColor:
		{
			RGBColor color;
			ReadRGBColor(&color);
			movie->SetBackgroundColor(color);
		}
		break;

	case Tag::DefineShape:
		{
			DefineShape(1, movie);
		}
		break;

	case Tag::DefineShape2:
		{
			DefineShape(2, movie);
		}
		break;

	case Tag::DefineShape3:
		{
			DefineShape(3, movie);
		}
		break;

	case Tag::DefineSprite:
		{
			Sprite* sprite = new Sprite;

			sprite->SetCharacterID(getshort());
			sprite->SetFrameCount(getshort());

			Frame* pFrame = new Frame;
			pFrame->m_stream = this;
			pFrame->m_streamPos = Seek(0);

			sprite->m_frames.Add(pFrame);

			TRACE("DefineSprite %d\n", sprite->GetCharacterID());

			while (1)
			{
				Tag tag;
				BeginTag(&tag);

				if (tag.Code == 0)	// End tag
					break;

				LONGLONG startpos = Seek(0);

				switch (tag.Code)
				{
					/*
				case Tag::ShowFrame:
					{
						ATLTRACE("Sprite ShowFrame\n");
					}
					break;
					*/

				default:
					{
						ParseTimelineTag(tag, sprite, movie, false);
					}
					break;
				}

				Seek(startpos + tag.Length, System::IO::STREAM_SEEK_SET);
			}

			TRACE("End of sprite\n");

			movie->DefineShape(0, sprite);
		}
		break;

	case Tag::DefineFont:
		{
			uint16 FontID = getshort();
			TRACE("DefineFont %d\n", FontID);
		}
		break;

	case Tag::DefineFontInfo:
		{
			TRACE("DefineFontInfo\n");
		}
		break;

	case Tag::DefineFont2:
		{
			DefineFont(2, movie);
		}
		break;

	case Tag::DefineText:
		{
			DefineText(1, movie);
		}
		break;

	case Tag::DefineText2:
		{
			DefineText(2, movie);
		}
		break;

	case Tag::DefineButton2:
		{
			DefineButton(2, movie);
		}
		break;

	case Tag::DefineSound:
		{
			TRACE("DefineSound\n");
		}
		break;

	case Tag::DefineBitsLossless:
		{
			TRACE("DefineBitsLossless\n");
			DefineBitsLossless(1, movie);
		}
		break;

	case Tag::DefineBitsLossless2:
		{
			TRACE("DefineBitsLossless2\n");
			DefineBitsLossless(2, movie);
		}
		break;

	case Tag::DefineBitsJPEG2:
		{
			DefineBitsJPEG(2, movie);
		}
		break;

	case Tag::DefineBitsJPEG3:
		{
			DefineBitsJPEG(3, movie);
		}
		break;

	case Tag::DefineVideoStream:
		{
			ASSERT(0);
#if 0
			VideoStreamCharacter* video = new VideoStreamCharacter;
			video->m_CharacterID = getshort();
			TRACE("DefineVideoStream %d\n", video->m_CharacterID);

			video->m_NumFrames = getshort();
			video->m_Width = getshort();
			video->m_Height = getshort();
			getnbits(5);	// Reserved
			int VideoFlagsDeblocking = getnbits(2);
			bool VideoFlagsSmoothing = getbit();
			video->m_CodecID = getbyte();
#endif
		}
		break;

	case Tag::VideoFrame:
		{
			TRACE("VideoFrame\n");
		}
		break;

	case Tag::StartSound:
		{
			TRACE("StartSound\n");
		}
		break;

	case Tag::Protect:
		{
			TRACE("Protect, Length: %d\n", tag.Length);
		}
		break;

	default:
		{
			ParseTimelineTag(tag, movie, movie, true);
		}
		break;
	}
}

}	// LSWF
}
