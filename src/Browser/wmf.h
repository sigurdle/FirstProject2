#ifndef __wmf_h__
#define __wmf_h__

#pragma pack(push,1)

namespace System
{
typedef uint32 COLORREF;

namespace wmf
{

inline uint32 wmfRGB(uint8 r, uint8 g, uint8 b)
{
	return ((uint32)(((r)|((uint16)((g))<<8))|(((uint32)(b))<<16)));
}

// TODO, make enums

/* Mapping Modes */
#define MM_TEXT             1
#define MM_LOMETRIC         2
#define MM_HIMETRIC         3
#define MM_LOENGLISH        4
#define MM_HIENGLISH        5
#define MM_TWIPS            6
#define MM_ISOTROPIC        7
#define MM_ANISOTROPIC      8

/* Background Modes */
#define TRANSPARENT         1
#define OPAQUE              2

/* Graphics Modes */

#define GM_COMPATIBLE       1
#define GM_ADVANCED         2

/* Pen Styles */
#define PS_SOLID            0
#define PS_DASH             1       /* -------  */
#define PS_DOT              2       /* .......  */
#define PS_DASHDOT          3       /* _._._._  */
#define PS_DASHDOTDOT       4       /* _.._.._  */
#define PS_NULL             5
#define PS_INSIDEFRAME      6
#define PS_USERSTYLE        7
#define PS_ALTERNATE        8
#define PS_STYLE_MASK       0x0000000F

#define PS_ENDCAP_ROUND     0x00000000
#define PS_ENDCAP_SQUARE    0x00000100
#define PS_ENDCAP_FLAT      0x00000200
#define PS_ENDCAP_MASK      0x00000F00

#define PS_JOIN_ROUND       0x00000000
#define PS_JOIN_BEVEL       0x00001000
#define PS_JOIN_MITER       0x00002000
#define PS_JOIN_MASK        0x0000F000

#define PS_COSMETIC         0x00000000
#define PS_GEOMETRIC        0x00010000
#define PS_TYPE_MASK        0x000F0000

#define AD_COUNTERCLOCKWISE 1
#define AD_CLOCKWISE        2

struct XFORM
{
	float   eM11;
	float   eM12;
	float   eM21;
	float   eM22;
	float   eDx;
	float   eDy;
};

#define MWT_IDENTITY        1
#define MWT_LEFTMULTIPLY    2
#define MWT_RIGHTMULTIPLY   3

struct WMFHEADER
{
	uint16  FileType;       /* Type of metafile (0=memory, 1=disk) */
	uint16  HeaderSize;     /* Size of header in WORDS (always 9) */
	uint16  Version;        /* Version of Microsoft Windows used */
	uint32 FileSize;       /* Total size of the metafile in WORDs */
	uint16  NumOfObjects;   /* Number of objects in the file */
	uint32 MaxRecordSize;  /* The size of largest record in WORDs */
	uint16  NumOfParams;    /* Not Used (always 0) */
};

struct PLACEABLEMETAFILEHEADER
{
	uint32 Key;           /* Magic number (always 9AC6CDD7h) */
	uint16  Handle;        /* Metafile HANDLE number (always 0) */
	int16 Left;          /* Left coordinate in metafile units */
	int16 Top;           /* Top coordinate in metafile units */
	int16 Right;         /* Right coordinate in metafile units */
	int16 Bottom;        /* Bottom coordinate in metafile units */
	uint16  Inch;          /* Number of metafile units per inch */
	uint32 Reserved;      /* Reserved (always 0) */
	uint16  Checksum;      /* Checksum value for previous 10 WORDs */
};

struct EMFHEADER
{
	uint32 RecordType;       /* Record type */
	uint32 RecordSize;       /* Size of the record in bytes */
	int32  BoundsLeft;       /* Left inclusive bounds */
	int32  BoundsTop;      /* Right inclusive bounds */
	int32  BoundsRight;        /* Top inclusive bounds */
	int32  BoundsBottom;     /* Bottom inclusive bounds */
	int32  FrameLeft;        /* Left side of inclusive picture frame */
	int32  FrameTop;       /* Right side of inclusive picture frame */
	int32  FrameRight;         /* Top side of inclusive picture frame */
	int32  FrameBottom;      /* Bottom side of inclusive picture frame */
	uint32 Signature;        /* Signature ID (always 0x464D4520) */
	uint32 Version;          /* Version of the metafile */
	uint32 Size;             /* Size of the metafile in bytes */
	uint32 NumOfRecords;     /* Number of records in the metafile */
	uint16  NumOfHandles;     /* Number of handles in the handle table */
	uint16  Reserved;         /* Not used (always 0) */
	uint32 SizeOfDescrip;    /* Size of description string in WORDs */
	uint32 OffsOfDescrip;    /* Offset of description string in metafile */
	uint32 NumPalEntries;    /* Number of color palette entries */
	int32  WidthDevPixels;   /* Width of reference device in pixels */
	int32  HeightDevPixels;  /* Height of reference device in pixels */
	int32  WidthDevMM;       /* Width of reference device in millimeters */
	int32  HeightDevMM;      /* Height of reference device in millimeters */
};

struct WMFRECORD
{
	uint32	Size;          /* Total size of the record in WORDs */
	uint16	Function;      /* Function number (defined in WINDOWS.H) */
//    WORD  Parameters[];  /* Parameter values passed to function */
};

struct EMFRECORD
{
	uint32 Function;      /* Function number (defined in WINGDI.H) */
	uint32 Size;          /* Total size of the record in WORDs */
//    uint32 Parameters[];   /* Parameter values passed to GDI function */
};

struct LOGPEN_16
{ 
	short	lopnStyle; 
	short		lopnWidth;
	short		lopnWidthY;
	COLORREF	lopnColor; 
};

/* Brush Styles */
#define BS_SOLID            0
#define BS_NULL             1
#define BS_HOLLOW           BS_NULL
#define BS_HATCHED          2
#define BS_PATTERN          3
#define BS_INDEXED          4
#define BS_DIBPATTERN       5
#define BS_DIBPATTERNPT     6
#define BS_PATTERN8X8       7
#define BS_DIBPATTERN8X8    8
#define BS_MONOPATTERN      9

struct LOGBRUSH_16
{
	uint16	lbStyle; 
	COLORREF	lbColor;
	uint16	lbHatch; 
};

/* Logical Pen */
struct LOGPEN
{
    uint32        lopnStyle;
    int32       lopnWidth;
	 int32			lopnWidthY;
    COLORREF    lopnColor;
};

struct EXTLOGPEN
{
    uint32       elpPenStyle;
    uint32       elpWidth;
    uint32        elpBrushStyle;
    COLORREF    elpColor;
    ULONG/*_PTR*/    elpHatch;     //Sundown: elpHatch could take a HANDLE
    uint32       elpNumEntries;
  //  uint32       elpStyleEntry[1];
};

/* Logical Brush (or Pattern) */
struct LOGBRUSH
{
	UINT        lbStyle;
	COLORREF    lbColor;
	ULONG/*_PTR*/    lbHatch;    // Sundown: lbHatch could hold a HANDLE
};

/* Font Weights */
#define FW_DONTCARE         0
#define FW_THIN             100
#define FW_EXTRALIGHT       200
#define FW_LIGHT            300
#define FW_NORMAL           400
#define FW_MEDIUM           500
#define FW_SEMIBOLD         600
#define FW_BOLD             700
#define FW_EXTRABOLD        800
#define FW_HEAVY            900

#define DEFAULT_PITCH           0
#define FIXED_PITCH             1
#define VARIABLE_PITCH          2
#if(WINVER >= 0x0400)
#define MONO_FONT               8
#endif /* WINVER >= 0x0400 */

#define ANSI_CHARSET            0
#define DEFAULT_CHARSET         1
#define SYMBOL_CHARSET          2
#define SHIFTJIS_CHARSET        128
#define HANGEUL_CHARSET         129
#define HANGUL_CHARSET          129
#define GB2312_CHARSET          134
#define CHINESEBIG5_CHARSET     136
#define OEM_CHARSET             255
//#if(WINVER >= 0x0400)
#define JOHAB_CHARSET           130
#define HEBREW_CHARSET          177
#define ARABIC_CHARSET          178
#define GREEK_CHARSET           161
#define TURKISH_CHARSET         162
#define VIETNAMESE_CHARSET      163
#define THAI_CHARSET            222
#define EASTEUROPE_CHARSET      238
#define RUSSIAN_CHARSET         204

#define MAC_CHARSET             77
#define BALTIC_CHARSET          186

#define FS_LATIN1               0x00000001L
#define FS_LATIN2               0x00000002L
#define FS_CYRILLIC             0x00000004L
#define FS_GREEK                0x00000008L
#define FS_TURKISH              0x00000010L
#define FS_HEBREW               0x00000020L
#define FS_ARABIC               0x00000040L
#define FS_BALTIC               0x00000080L
#define FS_VIETNAMESE           0x00000100L
#define FS_THAI                 0x00010000L
#define FS_JISJAPAN             0x00020000L
#define FS_CHINESESIMP          0x00040000L
#define FS_WANSUNG              0x00080000L
#define FS_CHINESETRAD          0x00100000L
#define FS_JOHAB                0x00200000L
#define FS_SYMBOL               0x80000000L
//#endif /* WINVER >= 0x0400 */

#define LF_FACESIZE			32
#define LF_FULLFACESIZE		64
#define ELF_VENDOR_SIZE     4

struct LOGFONT_16
{
   short lfHeight;
   short lfWidth;
   short lfEscapement;
   short lfOrientation;
   short lfWeight;
   uint8 lfItalic;
   uint8 lfUnderline;
   uint8 lfStrikeOut;
   uint8 lfCharSet;
   uint8 lfOutPrecision;
   uint8 lfClipPrecision;
   uint8 lfQuality; 
   uint8 lfPitchAndFamily; 
   char lfFaceName[LF_FACESIZE];
};

struct LOGFONTA
{
    LONG      lfHeight;
    LONG      lfWidth;
    LONG      lfEscapement;
    LONG      lfOrientation;
    LONG      lfWeight;
    uint8      lfItalic;
    uint8      lfUnderline;
    uint8      lfStrikeOut;
    uint8      lfCharSet;
    uint8      lfOutPrecision;
    uint8      lfClipPrecision;
    uint8      lfQuality;
    uint8      lfPitchAndFamily;
    char      lfFaceName[LF_FACESIZE];
};

struct LOGFONTW
{
    LONG      lfHeight;
    LONG      lfWidth;
    LONG      lfEscapement;
    LONG      lfOrientation;
    LONG      lfWeight;
    uint8      lfItalic;
    uint8      lfUnderline;
    uint8      lfStrikeOut;
    uint8      lfCharSet;
    uint8      lfOutPrecision;
    uint8      lfClipPrecision;
    uint8      lfQuality;
    uint8      lfPitchAndFamily;
    WCHAR     lfFaceName[LF_FACESIZE];
};

struct PANOSE
{
    uint8    bFamilyType;
    uint8    bSerifStyle;
    uint8    bWeight;
    uint8    bProportion;
    uint8    bContrast;
    uint8    bStrokeVariation;
    uint8    bArmStyle;
    uint8    bLetterform;
    uint8    bMidline;
    uint8    bXHeight;
};

struct EXTLOGFONTW {
    LOGFONTW    elfLogFont;
    WCHAR       elfFullName[LF_FULLFACESIZE];
    WCHAR       elfStyle[LF_FACESIZE];
    uint32       elfVersion;     /* 0 for the first release of NT */
    uint32       elfStyleSize;
    uint32       elfMatch;
    uint32       elfReserved;
    uint8        elfVendorId[ELF_VENDOR_SIZE];
    uint32       elfCulture;     /* 0 for Latin                   */
    PANOSE      elfPanose;
};

#pragma pack(pop)

enum
{
wmfAbortDoc  = 0x0052 ,
wmfArc  = 0x0817 ,
wmfChord  = 0x0830, 
//wmfDeleteObject  = 0x01f0 ,
wmfEllipse  = 0x0418 ,
wmfEndDoc  = 0x005E ,
wmfEndPage  = 0x0050 ,
wmfExcludeClipRect  = 0x0415 ,
wmfExtFloodFill  = 0x0548 ,
wmfFillRegion  = 0x0228 ,
wmfFloodFill  = 0x0419 ,
wmfFrameRegion  = 0x0429, 
wmfIntersectClipRect  = 0x0416 ,
wmfInvertRegion  = 0x012A ,
wmfLineTo  = 0x0213 ,
wmfMoveTo  = 0x0214 ,
wmfOffsetClipRgn  = 0x0220 ,
wmfOffsetViewportOrg  = 0x0211 ,
wmfOffsetWindowOrg  = 0x020F ,
wmfPaintRegion  = 0x012B ,
wmfPatBlt  = 0x061D ,
wmfPie  = 0x081A ,
wmfRealizePalette  = 0x0035 ,
wmfRectangle  = 0x041B ,
wmfResetDc  = 0x014C ,
wmfResizePalette  = 0x0139 ,
wmfRestoreDC  = 0x0127 ,
wmfRoundRect  = 0x061C ,
wmfSaveDC  = 0x001E ,
wmfScaleViewportExt  = 0x0412 ,
wmfScaleWindowExt  = 0x0410 ,
wmfSelectClipRegion  = 0x012C, 
wmfSelectObject  = 0x012D ,
wmfSelectPalette  = 0x0234 ,
wmfSetBkColor  = 0x0201 ,
wmfSetBkMode  = 0x0102 ,
wmfSetDibToDev  = 0x0d33, 
wmfSetMapMode  = 0x0103 ,
wmfSetMapperFlags  = 0x0231 ,
wmfSetPalEntries  = 0x0037 ,
wmfSetPixel  = 0x041F ,
wmfSetPolyFillMode  = 0x0106 ,
wmfSetRelabs  = 0x0105 ,
wmfSetROP2  = 0x0104 ,
wmfSetStretchBltMode  = 0x0107 ,
wmfSetTextAlign  = 0x012E ,
wmfSetTextCharExtra  = 0x0108 ,
wmfSetTextColor  = 0x0209 ,
wmfSetTextJustification  = 0x020A ,
wmfSetViewportExt  = 0x020E ,
wmfSetViewportOrg  = 0x020D ,
wmfSetWindowExt  = 0x020C ,
wmfSetWindowOrg  = 0x020B ,
wmfStartDoc  = 0x014D ,
wmfStartPage = 0x004F ,

	// Records that don't follow the standard format
wmfAnimatePalette = 0x0436 ,
wmfBitBlt = 0x0922 ,
wmfCreateBitmap = 0x06FE ,
wmfCreateBitmapIndirect = 0x02FD ,
wmfCreateBrush = 0x00F8 ,
wmfCreateBrushIndirect = 0x02FC ,
wmfCreateFontIndirect = 0x02FB ,
wmfCreatePalette = 0x00F7 ,
wmfCreatePatternBrush = 0x01F9 ,
wmfCreatePenIndirect = 0x02FA ,
wmfCreateRegion = 0x06FF ,
wmfDeleteObject = 0x01F0 ,
wmfDibBitblt = 0x0940 ,
wmfDibCreatePatternBrush = 0x0142 ,
wmfDibStretchBlt = 0x0B41 ,
wmfDrawText = 0x062F, 
wmfEscape = 0x0626 ,
wmfExtTextOut = 0x0A32 ,
wmfPolygon = 0x0324 ,
wmfPolyPolygon = 0x0538 ,
wmfPolyline = 0x0325 ,
wmfTextOut = 0x0521 ,
wmfStretchBlt = 0x0B23 ,
wmfStretchDIBits = 0x0F43 ,
};

enum
{
emfABORTPATH =68,
emfPOLYLINE = 4,
emfANGLEARC = 41,
emfPOLYLINE16 = 87,
emfARC = 45,
emfPOLYLINETO = 6 ,
emfARCTO = 55,
emfPOLYLINETO16 = 89 ,
emfBEGINPATH = 59,
emfPOLYPOLYGON = 8 ,
emfBITBLT = 76,
emfPOLYPOLYGON16 = 91 ,
emfCHORD = 46,
emfPOLYPOLYLINE = 7 ,
emfCLOSEFIGURE = 61,
emfPOLYPOLYLINE16 = 90 ,
emfCREATEBRUSHINDIRECT = 39,
emfPOLYTEXTOUTA = 96 ,
emfCREATEDIBPATTERNBRUSHPT = 94,
emfPOLYTEXTOUTW = 97 ,
emfCREATEMONOBRUSH = 93,
emfREALIZEPALETTE = 52, 
emfCREATEPALETTE = 49,
emfRECTANGLE = 43 ,
emfCREATEPEN = 38,
emfRESIZEPALETTE = 51 ,
emfDELETEOBJECT = 40,
emfRESTOREDC = 34 ,
emfELLIPSE = 42,
emfROUNDRECT = 44 ,
emfENDPATH = 60,
emfSAVEDC = 33 ,
emfEOF = 14,
emfSCALEVIEWPORTEXTEX = 31 ,
emfEXCLUDECLIPRECT = 29,
emfSCALEWINDOWEXTEX = 32 ,
emfEXTCREATEFONTINDIRECTW = 82,
emfSELECTCLIPPATH = 67 ,
emfEXTCREATEPEN = 95,
emfSELECTOBJECT = 37 ,
emfEXTFLOODFILL = 53,
emfSELECTPALETTE = 48 ,
emfEXTSELECTCLIPRGN = 75,
emfSETARCDIRECTION = 57, 
emfEXTTEXTOUTA = 83,
emfSETBKCOLOR = 25 ,
emfEXTTEXTOUTW = 84,
emfSETBKMODE = 18 ,
emfFILLPATH = 62,
emfSETBRUSHORGEX = 13 ,
emfFILLRGN = 71,
emfSETCOLORADJUSTMENT = 23 ,
emfFLATTENPATH = 65,
emfSETDIBITSTODEVICE = 80 ,
emfFRAMERGN = 72,
emfSETMAPMODE = 17 ,
emfGDICOMMENT = 70,
emfSETMAPPERFLAGS = 16 ,
emfHEADER = 1,
emfSETMETARGN = 28 ,
emfINTERSECTCLIPRECT = 30,
emfSETMITERLIMIT = 58 ,
emfINVERTRGN = 73,
emfSETPALETTEENTRIES = 50 ,
emfLINETO = 54,
emfSETPIXELV = 15 ,
emfMASKBLT = 78,
emfSETPOLYFILLMODE = 19 ,
emfMODIFYWORLDTRANSFORM = 36,
emfSETROP2 = 20 ,
emfMOVETOEX = 27,
emfSETSTRETCHBLTMODE = 21 ,
emfOFFSETCLIPRGN = 26,
emfSETTEXTALIGN = 22 ,
emfPAINTRGN = 74,
emfSETTEXTCOLOR = 24 ,
emfPIE = 47,
emfSETVIEWPORTEXTEX = 11 ,
emfPLGBLT = 79,
emfSETVIEWPORTORGEX = 12 ,
emfPOLYBEZIER = 2,
emfSETWINDOWEXTEX = 9 ,
emfPOLYBEZIER16 = 85,
emfSETWINDOWORGEX = 10 ,
emfPOLYBEZIERTO = 5,
emfSETWORLDTRANSFORM = 35 ,
emfPOLYBEZIERTO16 = 88,
emfSTRETCHBLT = 77 ,
emfPOLYDRAW = 56,
emfSTRETCHDIBITS = 81 ,
emfPOLYDRAW16 = 92,
emfSTROKEANDFILLPATH = 63 ,
emfPOLYGON = 3,
emfSTROKEPATH = 64 ,
emfPOLYGON16 = 86,
emfWIDENPATH = 66 ,
};

enum
{
wmfOBJ_PEN = 1,
wmfOBJ_BRUSH =  2,
wmfOBJ_FONT = 6,
wmfOBJ_BITMAP = 7,
};

class Object
{
public:

	int m_type;

	virtual ~Object()
	{
	}
};

class ObjectPen : public Object
{
public:
	CTOR ObjectPen()
	{
		m_type = wmfOBJ_PEN;
	}

	LDraw::Pen* m_pPen;
};

class ObjectBrush : public Object
{
public:
	CTOR ObjectBrush()
	{
		m_type = wmfOBJ_BRUSH;
	}
	LDraw::Brush* m_pBrush;
};

class ObjectFont : public Object
{
public:
	CTOR ObjectFont()
	{
		m_type = wmfOBJ_FONT;
	}
	LDraw::Font* m_pFont;
};

class Loader
{
public:
	virtual ~Loader()
	{
	}
};

class Loader2 : public Loader
{
public:
};

class MetafileLoader : public Loader2
{
public:

	MetafileLoader();

	LDraw::Commands* pCommands;

	void Load(System::IO::ISequentialByteStream* pStream);

	void LoadWMF(System::IO::ISequentialByteStream* pStream)
	{
	}

	void GetRect(LDraw::RectD* prect) const
	{
		*prect = m_rect;
	}

	void SetMapMode(int mapmode);
	void SetWindowOrg(int x, int y);
	void SetWindowExt(int cx, int cy);
	void SetViewportOrg(int x, int y);
	void SetViewportExt(int cx, int cy);
	void SetTextColor(COLORREF color);
	void SetTextAlign(uint32 textAlign);
	void SetMiterLimit(float miterLimit);
	void MoveTo(int x, int y);
	void ExtTextOut(int x, int y, System::StringA* string, const int* distances);
	void SelectObject(int n);
	void DeleteObject(int n);
	void CreatePenIndirect(int index, const LOGPEN& lp);
	void CreatePenIndirect(int index, const EXTLOGPEN& lp);
	void CreateBrushIndirect(int index, const LOGBRUSH& lb);
	void CreateFontIndirect(int index, const LOGFONT_16& lf);
	void CreateFontIndirect(int index, const LOGFONTA& lf);
	void CreateFontIndirect(int index, const LOGFONTW& lf);
	void StretchDIBits(int destX, int destY, int destWidth, int destHeight, int srcX, int srcY, int srcWidth, int srcHeight, LDraw::Bitmap* bitmap);
	void FillPath();

protected:

	LDraw::Bitmap* ReadDib(System::IO::ISequentialByteStream* pStream);

	LDraw::RectD m_rect;

	__release<LDraw::GraphicsPathF> m_path;
	ObjectPen* m_pCurPen;
	ObjectBrush* m_pCurBrush;
	ObjectFont* m_pCurFont;
	COLORREF m_textColor;

	LDraw::PointF WO;
	LDraw::SizeF WE;
	LDraw::PointF VO;
	LDraw::SizeF VE;

	uint32 m_textAlign;
	int m_curx;
	int m_cury;
	float m_miterLimit;

	bool m_bBeginPath;

	int m_numOfObjects;
	Object** m_objects;

	LDraw::PointF LPToDP(int Lx, int Ly);
};

}	// wmf
}	// System

#endif // __wmf_h__
