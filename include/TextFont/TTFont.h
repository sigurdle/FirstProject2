#ifndef __TTFONT_H_
#define __TTFONT_H_

#ifndef TextFontExt
#define TextFontExt DECLSPEC_DLLIMPORT
#endif

namespace System
{
namespace LDraw
{
	class GraphicsPathF;
}
}

namespace System
{
namespace TextFont
{

typedef float REAL;

typedef uint32 ottag;
typedef long Fixed;
typedef long fixed32;
typedef short FWord;
typedef unsigned short uFWord;
typedef int32 StkElt;
typedef long F26Dot6;
typedef long Euint16;

struct longDateTime
{
	uint32 low;
	uint32 high;
};

#if WIN32
#pragma pack(push,2)

#endif

struct OTFTable
{
	ottag tag;// 4 -byte identifier. 
	uint32 checkSum;// CheckSum for this table. 
	uint32 offset;// Offset from beginning of TrueType font file. 
	uint32 length;// Length of this table. 
};

struct OTF_HORMETRIC
{
	uint16 advanceWidth;
	int16 leftSideBearing;
};

struct OTF_HEAD
{
	Fixed version;// 0x00010000 if (version 1.0) 
	Fixed fontRevision;// set by font manufacturer 
	uint32 checkSumAdjustment;// To compute: set it to 0, calculate the checksum for the 'head' table and put it in the table directory, sum the entire font as uint32, then store B1B0AFBA - sum. The checksum for the 'head' table will not be wrong. That is OK. 
	uint32 magicNumber;// set to 0x5F0F3CF5 
	uint16 flags;/* bit 0 - y value of 0 specifies baseline
						bit 1 - x position of left most black bit is LSB
						bit 2 - scaled point size and actual point size will differ (i.e. 24 point glyph differs from 12 point glyph scaled by factor of 2)
						bit 3 - use integer scaling instead of fractional
						bit 4 - (used by the Microsoft implementation of the TrueType scaler)
						bit 5 - This bit should be set in fonts that are intended to e laid out vertically, and in which the glyphs have been drawn such that an x-coordinate of 0 corresponds to the desired vertical baseline.
						bit 6 - This bit must be set to zero.
						bit 7 - This bit should be set if the font requires layout for correct linguistic rendering (e.g. Arabic fonts).
						bit 8 - This bit should be set for a GX font which has one or more metamorphosis effects designated as happening by default.
						bit 9 - This bit should be set if the font contains any strong right-to-left glyphs.
						bit 10 - This bit should be set if the font contains Indic-style rearrangement effects.
						bits 11-12 - Defined by Adobe. 
	*/
	uint16 unitsPerEm;// range from 64 to 16384 
	longDateTime created;// international date 
	longDateTime modified;// international date 
	FWord xMin;// for all glyph bounding boxes 
	FWord yMin;// for all glyph bounding boxes 
	FWord xMax;// for all glyph bounding boxes 
	FWord yMax;// for all glyph bounding boxes 
	uint16 macStyle;/* bit 0 bold
	bit 1 italic
	bit 2 underline
	bit 3 outline
	bit 4 shadow
	bit 5 condensed (narrow)
	bit 6 extended 
	*/
	uint16 lowestRecPPEM;// smallest readable size in pixels 
	int16 fontDirectionHint;/* 0 Mixed directional glyphs
										1 Only strongly left to right glyphs
										2 Like 1 but also contains neutrals
										-1 Only strongly right to left glyphs
										-2 Like -1 but also contains neutrals 
	*/
	int16 indexToLocFormat;// 0 for short offsets, 1 for long 
	int16 glyphDataFormat;// 0 for current format 
};

struct OTFMaxProfileHeader
{
	Fixed version;// 0x00010000 (1.0) 
	uint16 numGlyphs;// the number of glyphs in the font 
	uint16 maxPoints;// points in non-compound glyph 
	uint16 maxContours;// contours in non-compound glyph 
	uint16 maxComponentPoints;// points in compound glyph 
	uint16 maxComponentContours;// contours in compound glyph 
	uint16 maxZones;// set to 2 
	uint16 maxTwilightPoints;// points used in Twilight Zone (Z0) 
	uint16 maxStorage;// number of Storage Area locations 
	uint16 maxFunctionDefs;// number of FDEFs 
	uint16 maxInstructionDefs;// number of IDEFs 
	uint16 maxStackElements;// maximum stack depth 
	uint16 maxSizeOfInstructions;// byte count for glyph instructions 
	uint16 maxComponentElements;// number of glyphs referenced at top level 
	uint16 maxComponentDepth;// levels of recursion, set to 0 if font has only simple glyphs 
};

struct OTFBaseline
{
	fixed32 version;// Version number of the Baseline table (0x00010000 for the current version). 
	uint16 format;// Format of the baseline table. Only one baseline format may be selected for the font. 
	uint16 defaultBaseline;// Default baseline value for all glyphs. This value can be from 0 through 31. 
};

struct OTF_HHEA
{
	Fixed version;// 0x00010000 (1.0) 
	FWord ascent;// Distance from baseline of highest ascender 
	FWord descent;// Distance from baseline of lowest descender 
	FWord lineGap;// typographic line gap 
	uFWord advanceWidthMax;// must be consistent with horizontal metrics 
	FWord minLeftSideBearing;// must be consistent with horizontal metrics 
	FWord minRightSideBearing;// must be consistent with horizontal metrics 
	FWord xMaxExtent;// max(lsb + (xMax-xMin)) 
	int16 caretSlopeRise;// used to calculate the slope of the caret (rise/run) set to 1 for vertical caret 
	int16 caretSlopeRun;// 0 for vertical 
	FWord caretOffset;// set value to 0 for non-slanted fonts 
	int16 reserved0;// set value to 0 
	int16 reserved1;// set value to 0 
	int16 reserved2;// set value to 0 
	int16 reserved3;// set value to 0 
	int16 metricDataFormat;// 0 for current format 
	uint16 numOfLongHorMetrics;// number of advance widths in metrics table 
};

struct OTF_NAME
{
	uint16 format;// Format selector. Set to 0. 
	uint16 count;// The number of nameRecords in this name table. 
	uint16 stringOffset;// Offset in bytes to the beginning of the name character strings. 
//	NameRecord nameRecord[count] The name records array. 
//	variable name character strings The character strings of the names. Note that these are not necessarily ASCII! 
};

struct OTFNameRecord
{
	uint16 platformID;// Platform identifier code. 
	uint16 platformSpecificID;// Platform-specific encoding identifier. 
	uint16 languageID;// Language identifier. 
	uint16 nameID;// Name identifiers. 
	uint16 length;// Name string length in bytes. 
	uint16 offset;// Name string offset in bytes from stringOffset 
};

struct OTFGlyphDesc
{
	int16 numberOfContours;// If the number of contours is positive or zero, it is a single glyph;
	//If the number of contours is -1, the glyph is compound 
	FWord xMin;// Minimum x for coordinate data 
	FWord yMin;// Minimum y for coordinate data 
	FWord xMax;// Maximum x for coordinate data 
	FWord yMax;// Maximum y for coordinate data 
};

#if WIN32
#pragma pack(pop)

#endif

class TTFun //: public System::Object
{
public:
	inline CTOR TTFun()
	{
		m_data = NULL;
		m_size = 0;
	}

	ubyte* m_data;
	uint32 m_size;
};

typedef map<int, TTFun*> tyfunmap;

class TextFontExt GlyphData : public Object
{
public:
	CTOR GlyphData();
	~GlyphData();

	uint8* flags;
	LDraw::PointI* points;
	uint16* endPtsOfContours;
};

class TextFontExt Glyph2
{
public:
	OTFGlyphDesc Desc;

	/*
	uint16* endPtsOfContours2;
	uint8* flags2;
	LDraw::PointI* points2;
	*/
	GlyphData data;
	uint16 npoints;
	uint16 instructionsLength;
	ubyte* instructionsData;
};

class TextFontExt State
{
public:
	CTOR State();
	int round(int n);

	bool bAutoFlip;

	int deltaBase;
	int deltaShift;

	int roundThreshold;
	int roundPhase;
	int roundPeriod;

	F26Dot6 controlValueCutIn;

	F26Dot6 singleWidthCutIn;

	F26Dot6 minDistance;

	uint32 rp0;
	uint32 rp1;
	uint32 rp2;

	uint32 zp0;
	uint32 zp1;
	uint32 zp2;

	gm::PointI freedom;
	gm::PointI project;
	gm::PointI dualproject;
};

class VM;
class TTFontFile;
class TTFont;

class TextFontExt VM : public System::Object
{
public:
	CTOR VM(TTFontFile* pFile, TTFont* pFont);

	typedef void (VM::*tyttfunc)();

	FWord* m_cvt;
	int32* m_pStorage;

	int m_iflevel;

	const OTFGlyphDesc* glyphDesc;
	const uint16* endPtsOfContours;
	uint8* bpoints[2];
	int gpointsCount[2];
	uint8* flags;

	State m_state;

	TTFontFile* m_pFile;
	TTFont* m_pFont;
//	Glyph2* m_pGlyph;

	uint8* pc;

	class Caller
	{
	public:

		inline CTOR Caller()
		{
			pCaller = NULL;
		}
		Caller* pCaller;
		uint8* instructionsData;
		uint32 instructionsLength;
		uint8* return_pc;
	};

	void callfun(TTFun* f);

	bool next();

	Caller* m_ctx;

	vector<StkElt> m_stack;
	int m_loop;

	int32 ReadStorage(uint32 loc);
	void WriteStorage(uint32 loc, int32 val);
	void push(StkElt value);
	StkElt pop();
	void SetPoint(int zone, int npoint, gm::PointI point);

	const gm::PointI& get_orgpoint(int zone, int p) const;
	const gm::PointI& get_newpoint(int zone, int p) const;
	gm::PointI& orgpoint(int zone, int p);
	gm::PointI& newpoint(int zone, int p);

	static tyttfunc ttfuncs[256];

	gm::PointI* orgpoints[2];
	gm::PointI* newpoints[2];

protected:

	void tt_notimpl();
	void tt_gpv();
	void tt_sfvtpv();
	void tt_sdpvtl();
	void tt_alignrp();
	void tt_jmpr();
	void tt_jrof();
	void tt_sdb();
	void tt_wcvtp();
	void tt_mppem();
	void tt_npushb();
	void tt_npushw();
	void tt_pushb();
	void tt_pushw();
	void tt_pop();
	void tt_spvtl();
	void tt_sfvtl();
	void tt_sfvtca();
	void tt_svtca();
	void tt_spvfs();
	void tt_spvtca();
	void tt_scanctrl();
	void tt_call();
	void tt_loopcall();
	void tt_fdef();
	void tt_endf();
	void tt_gteq();
	void tt_lteq();
	void tt_eq();
	void tt_neq();
	void tt_lt();
	void tt_gt();
	void tt_and();
	void tt_or();
	void tt_div();
	void tt_mul();
	void tt_add();
	void tt_sub();
	void tt_max();
	void tt_min();
	void tt_swap();
	void tt_ws();
	void tt_rs();
	void tt_abs();
	void tt_fliprgon();
	void tt_rtg();
	void tt_rthg();
	void tt_rutg();
	void tt_rdtg();
	void tt_rtdg();
	void tt_mdrp();
	void tt_msirp();
	void tt_mirp();
	void tt_if();
	void tt_rcvt();
	void tt_md();
	void tt_gc();
	void tt_dup();
	void tt_cindex();
	void tt_mindex();
	void tt_roll();
	void tt_smd();
	void tt_scfs();
	void tt_isect();
	void tt_wcvtf();
	void tt_srp0();
	void tt_srp1();
	void tt_srp2();
	void tt_szp0();
	void tt_szp1();
	void tt_szp2();
	void tt_szps();
	void tt_else();
	void tt_eif();
	void tt_sfvfs();
	void tt_neg();
	void tt_not();
	void tt_scantype();
	void tt_miap();
	void tt_mdap();
	void tt_ip();
	void tt_iup();
	void tt_scvtci();
	void tt_getinfo();
	void tt_roff();
	void tt_sround();
	void tt_round();
	void tt_instctrl();
	void tt_sloop();
	void tt_flipoff();
	void tt_flipon();
	void tt_deltap1();
	void tt_deltap2();
	void tt_deltap3();
	void tt_deltac1();
	void tt_deltac2();
	void tt_deltac3();
	void tt_shp();
	void tt_shc();
	void tt_shpix();
};

class TextFontExt TTFontFile : public Object
{
public:

	CTOR TTFontFile();
	~TTFontFile();

//	Family* m_pFamily;

	typedef map<ottag, OTFTable*> tytablemap;
	OTFTable* FindTable(uint32 tag) const;

	uint32 CharToGlyph(uint32 c) const;
	Glyph2* GetGlyph(uint32 glyphIndex);
	Glyph2* ParseGlyph(uint32 glyphIndex);

	// head
	uint16 m_unitsPerEm;
	uint16 m_macStyle;

	// name
	String m_familyName;

//
	OTFMaxProfileHeader m_maxp;
	uint32 m_cvtSize;
	FWord* m_cvt;

	uint8* m_fontPrgData;
	uint32 m_fontPrgLength;

	uint8* m_prepData;
	uint32 m_prepLength;
	OTF_HHEA hhea;
	OTF_HORMETRIC* m_horMetrics;

	tyfunmap m_functions;
	tytablemap m_tablemap;

	uint8* m_glyfTabData;
	uint32* m_glyphOffsets;

	typedef map<uint32, Glyph2*> tyglyphmap;
	tyglyphmap m_glyphs;

	inline uint16 GetCellAscent() const
	{
		ASSERT(this);
		return hhea.ascent;
	}

	inline uint16 GetCellDescent() const
	{
		ASSERT(this);
		return -hhea.descent;
	}

	inline uint16 GetEmHeight() const
	{
		ASSERT(this);
		return m_unitsPerEm;
	}

//	sysstring GetName(uint16 nameID);

	void Init(IO::Stream* m_fp);
	void Init2(IO::Stream* m_fp);

private:

	typedef map<uint32, uint32> tycmap;
	tycmap m_cmap;

	bool ReadHeader(IO::Stream* m_fp);
};

class TextFontExt Glyph : public Object
{
public:
	CTOR Glyph();
	~Glyph();

	REAL minX;
	REAL minY;
	REAL maxX;
	REAL maxY;

	__release<LDraw::GraphicsPathF> pPath;
};

class TextFontExt TTFont : public Object
{
public:
	CTOR TTFont(TTFontFile* fontFile, REAL emSize);
	~TTFont();

	FWord* m_cvt;

	gm::PointI* m_twilightPoints;
	gm::PointI* m_twilightPoints2;

	void ScalePoints(const Glyph2* glyph2, const gm::PointI* orgpoints, gm::PointI* newpoints) const;
	VM* SetupGlyphVM(const Glyph2* glyph);

	inline REAL GetSize() const
	{
		return m_emSize;
	}

	inline TTFontFile* GetFile() const
	{
		return m_fontFile;
	}

	//Glyph* NormalizeGlyph(const LType::VM* vm);
	Glyph* NormalizeGlyph(const Glyph2* pGlyph2, const uint8* flags, const gm::PointI* points, const uint16* endPtsOfContours, int numberOfContours);

protected:
	friend class VM;

	TTFontFile* m_fontFile;
	REAL m_emSize;

	int32* m_pStorage;
};

}	// TextFont
}	// System

#endif // __TTFONT_H_
