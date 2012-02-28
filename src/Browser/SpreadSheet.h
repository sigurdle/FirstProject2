#pragma once

#include "msodrawing.h"

namespace System
{

extern float pixelsPerInch;

namespace Excel
{

struct RECORDHEADER
{
	uint16 id;
	uint16 size;
};

enum
{
	ID_INTERFACEHDR		= 0xe1,
	ID_INTERFACEEND		= 0xe2,
	ID_ADDMENU_DELMENU	= 0xc1,
	ID_EOF					= 0xA,
	ID_BOF					= 0x809,
	ID_SST					= 0xFC,
	ID_EXTSST				= 0xFF,
	ID_DIMENSIONS			= 0x200,
	ID_FORMULA				= 0x6,
	ID_NUMBER				= 0x203,
	ID_RK						= 0x27e,
	ID_FORMAT				= 0x41e,
	ID_XF						= 0xe0,
	ID_WINDOW2				= 0x23e,
	ID_DEFCOLWIDTH			= 0x55,
	ID_STANDARDWIDTH		= 0x99,
	ID_DEFAULTROWHEIGHT	= 0x225,
	ID_MSODRAWING			= 0xec,
	ID_MSODRAWINGGROUP	= 0xeb,
	ID_OBJ					= 0x5d,
	ID_TXO					= 0x1B6,
	ID_CONTINUE				= 0x3c,
	ID_COLINFO				= 0x7d,
	ID_ROW					= 0x208,
	ID_FONT					= 0x31,
	ID_WRITEACCESS			= 0x5c,
	ID_CODENAME				= 0x42,
	ID_DSF					= 0x161,
	ID_TABID					= 0x13d,
	ID_FNGROUPCOUNT		= 0x9c,
	ID_WINDOWPROTECT		= 0x19,
	ID_PROTECT				= 0x12,
	ID_PASSWORD				= 0x13,
	ID_PROT4REV				= 0x1af,
	ID_PROT4REVPASS		= 0x1bc,
	ID_WINDOW1				= 0x3d,
	ID_BOOKBOOL				= 0xda,
	ID_REFRESHALL			= 0x1b7,
	ID_STYLE					= 0x293,
	ID_USESELFS				= 0x160,
	ID_BOUNDSHEET			= 0x85,
	ID_COUNTRY				= 0x8c,
	ID_1904_DATE			= 0x22,
	ID_BACKUP				= 0x40,
	ID_HIDEOBJ				= 0x8d,
	ID_PRECISION			= 0x0e,
	ID_PALETTE				= 0x92,
	ID_LABEL					= 0x204,
	ID_LABELSST				= 0xFD,
};

struct BOF
{
	uint16 Version;
	uint16 Type;
	uint16 BuildIdenifier;
	uint16 BuildYear;
	uint32 FileHistoryFlags;
	uint32 MinVersion;
};

struct WINDOW2
{
	uint16 grbit;
	uint16 rowTop;
	uint16 colLeft;
	uint32 icvHdr;	// Index to color value for row/column headings and gridlines
	uint16 wScaleSLV;	// Zoom magnification in page break preview
	uint16 wScaleNormal;	// Zoom magnification in normal view
	uint32 reserved;
};

struct DEFAULTROWHEIGHT
{
	uint16 grbit;
/*
	0 01h fUnsynced = 1 if all undefined rows have incompatible font height and row height
	1 02h fDyZero = 1 if all undefined rows have 0 (zero) height
	2 04h fExAsc = 1 if all undefined rows have an extra space above
	3 08h fExDsc = 1 if all undefined rows have an extra space below
*/
	uint16 rowHeight;
};

#define fDspFmla	0x1	// = 1 if the window should display formulas = 0 if the window should display value
#define fDspGrid	0x2	// = 1 if the window should display gridlines
#define fDspRwCol	0x4	// = 1 if the window should display row and column headings

enum
{
	ptgAdd = 0x03,
	ptgSub = 0x04,
	ptgMul = 0x05,
	ptgParen = 0x15,
	ptgAttr = 0x19,
	ptgBool = 0x1d,
	ptgInt = 0x1e,
	ptgNumber = 0x1f,
	ptgRefV = 0x44,	// operand, value class
};

enum
{
	VA_Top,
	VA_Center,
	VA_Bottom,
	VA_Justified,// (BIFF5-BIFF8X)
	VA_Distributed,// (BIFF8X)
};

class XF
{
public:

	XF()
	{
		m_pParent = NULL;
	}

	int m_fontIndex;

	uint8 m_leftBorder : 4;
	uint8 m_rightBorder : 4;
	uint8 m_topBorder : 4;
	uint8 m_bottomBorder : 4;

	uint8 m_vertAlign : 3;

	uint8 m_leftColor;
	uint8 m_rightColor;
	uint8 m_topColor;
	uint8 m_bottomColor;

	XF* m_pParent;
};

class FormulaTokens
{
public:
//	StringA toString(uint32 relativeCol, uint32 relativeRow) const;

	uint8* data;
	uint32 size;
};


}	// Excel

class Sheet;
class Workbook;

struct CellRef
{
	uint32 row;
	uint32 col;
};

}

#include "Cell.h"

namespace System
{

class Row : public System::Object
{
public:
	Row()
	{
		m_height = 13.2;
	}

	map<uint32, Cell*> m_cells;

	double GetPointHeight() const
	{
		return m_height;
	}

	void SetPointHeight(double pt)
	{
		m_height = pt;
	}

	double GetPixelHeight() const
	{
		return m_height * (pixelsPerInch / 72.0f);
	}

	void SetPixelHeight(double px)
	{
		m_height = px * (72.0f / pixelsPerInch);
	}

protected:

	double m_height;
};

class Column : public System::Object
{
public:
	Column()
	{
		m_width = 80;
	}

	double GetPointWidth() const
	{
		return m_width;
	}

	void SetPointWidth(double pt)
	{
		m_width = pt;
	}

	double GetPixelWidth() const
	{
		return m_width * (pixelsPerInch / 72.0f);
	}

	void SetPixelWidth(double px)
	{
		m_width = px * (72.0f / pixelsPerInch);
	}

protected:

	double m_width;
};

class Font : public System::Object
{
public:

	Font()// : m_refcount(0)
	{
		m_font = NULL;
		m_ptHeight = 0;
		m_bold = 0;
		m_italic = 0;
		m_bDirty = false;
	}

	System::StringW* m_name;
	double m_ptHeight;
	short m_colorIndex;
	bool m_bold : 1;
	bool m_italic : 1;

	//ULONG m_refcount;

	LDraw::Font* GetFont();

protected:

	LDraw::Font* m_font;
	bool m_bDirty;
};

class Sheet : public System::Object
{
public:
	Sheet()
	{
		m_pWorkbook = NULL;
		m_pDrawingGroup = NULL;

		m_defColumnWidth = 80;
		m_defRowHeight = 22;
	}

	int m_defColumnWidth;
	int m_defRowHeight;

	Workbook* m_pWorkbook;
	UI::UIElement* m_pDrawingGroup;

	map<uint32, Column*> m_columns;
	map<uint32, Row*> m_rows;
};

class PaletteEntry
{
public:
	LDraw::Color m_rgb;
};

class StringEntry
{
public:
	System::StringW* m_str;
	vector<TextRun> m_textRuns;
};

class Workbook : public System::Object
{
public:
	Workbook();

	Blips m_blips;
	vector<Sheet*> m_sheets;

	float m_charWidth;

	PaletteEntry GetColor(int index)
	{
		if (index >= 0 && index < m_palette.GetSize())
		{
			return m_palette[index];
		}
		else
			return PaletteEntry();
	}

	vector<StringEntry*> m_sharedStrings;
	vector<PaletteEntry> m_palette;
	vector<Font*> m_fonts;
	vector<Excel::XF*> m_XF;
};

class SpreadSheetControl : public UI::Control
{
public:
	SpreadSheetControl();

	LDraw::RectI m_selectionRange;

//	BrowserFrame* m_pFrame;

	Sheet* m_pSheet;

	long m_dragging;

	virtual LDraw::SizeD OnMeasure(LDraw::SizeD availSize);

	virtual void OnArrange(LDraw::SizeD finalSize);

	LDraw::RectD GetCellRect(int ncol, int nrow);

	virtual void OnRender(UI::Graphics* pGraphics);

	int m_ncol;
	int m_nrow;
	LDraw::PointD m_offset;

//	void handleEvent(System::Event* evt);
};

}
