#pragma once

namespace System
{

class StringEntry;
class Sheet;

class Blip : public System::Object
{
public:
	LDraw::Bitmap* m_bitmap;
	LDraw::Commands* m_commands;

	LDraw::SizeD m_originalSize;
};

class Blips : public System::Object
{
public:
	vector<Blip*> m_items;
};

namespace MSODrawing
{

#pragma pack(push,1)

typedef ULONG MSOSPID;

typedef ULONG MSODGID;

struct MSOFBH
{
	ULONG ver : 4;
	ULONG inst: 12;
	ULONG fbt : 16;
   ULONG cbLength;
};

// FDGG - File DGG
struct FDGG
{
   MSOSPID spidMax; // The current maximum shape ID
   ULONG cidcl;     // The number of ID clusters (FIDCLs) 
   ULONG cspSaved;  // The total number of shapes saved
	// (including deleted shapes, if undo
	// information was saved)
   ULONG cdgSaved;  // The total number of drawings saved
};

// File ID Cluster - used to save IDCLs
struct FIDCL
{
	MSODGID dgid;    // DG owning the SPIDs in this cluster
	ULONG cspidCur;  // number of SPIDs used so far
};

// FDG - File DG
struct FDG
{
   ULONG     csp;          // The number of shapes in this drawing
   MSOSPID   spidCur;      // The last MSOSPID given to an SP in this DG
};

struct FSPGR
{
	LDraw::BBoxi	rcgBounds;
};

enum
{
	msofbtDggContainer		= 0xf000,
	msofbtBstoreContainer	= 0xf001,
	msofbtDgContainer			= 0xf002,
	msofbtSpgrContainer		= 0xf003,
	msofbtSpContainer			= 0xf004,
	msofbtDgg					= 0xf006,
	msofbtBSE					= 0xf007,
	msofbtDg						= 0xf008,
	msofbtSpgr					= 0xf009,
	msofbtSp						= 0xf00A,
	msofbtOPT					= 0xf00B,
	msofbtTextbox				= 0xf00C,
	msofbtClientTextbox		= 0xf00D,
	msofbtChildAnchor			= 0xf00F,
	msofbtClientAnchor		= 0xf010,
	msofbtClientData			= 0xf011,
	msofbtColorScheme			= 0xf120,
};

struct FSP
{
	MSOSPID  spid;           // The shape id 
	ULONG    grfPersistent;

/*
struct 
{
   ULONG fGroup : 1;        // This shape is a group shape
   ULONG fChild : 1;        // Not a top-level shape
   ULONG fPatriarch : 1;    // This is the topmost group shape.
                            // Exactly one of these per drawing. 
   ULONG fDeleted : 1;      // The shape has been deleted
   ULONG fOleShape : 1;     // The shape is an OLE object
   ULONG fHaveMaster : 1;   // Shape has a hspMaster property
   ULONG fFlipH : 1;        // Shape is flipped horizontally
   ULONG fFlipV : 1;        // Shape is flipped vertically
   ULONG fConnector : 1;    // Connector type of shape
   ULONG fHaveAnchor : 1;   // Shape has an anchor of some kind
   ULONG fBackground : 1;   // Background shape
   ULONG fHaveSpt : 1;      // Shape has a shape type property
   ULONG reserved : 20;     // Not yet used
}
*/
};

enum MSOSPT
{
	msosptMin = 0,
	msosptNotPrimitive = msosptMin,
	msosptRectangle = 1,
	msosptRoundRectangle = 2,
	msosptEllipse = 3,
	msosptDiamond = 4,
	msosptIsocelesTriangle = 5,
	msosptRightTriangle = 6,
	msosptParallelogram = 7,
	msosptTrapezoid = 8,
	msosptHexagon = 9,
	msosptOctagon = 10,
	msosptPlus = 11,
	msosptStar = 12,
	msosptArrow = 13,
	msosptThickArrow = 14,
	msosptHomePlate = 15,
	msosptCube = 16,
	msosptBalloon = 17,
	msosptSeal = 18,
	msosptArc = 19,
	msosptLine = 20,
	msosptPlaque = 21,
	msosptCan = 22,
	msosptDonut = 23,
	msosptTextSimple = 24,
	msosptTextOctagon = 25,
	msosptTextHexagon = 26,
	msosptTextCurve = 27,
	msosptTextWave = 28,
	msosptTextRing = 29,
	msosptTextOnCurve = 30,
	msosptTextOnRing = 31,
	msosptStraightConnector1 = 32,
	msosptBentConnector2 = 33,
	msosptBentConnector3 = 34,
	msosptBentConnector4 = 35,
	msosptBentConnector5 = 36,
	msosptCurvedConnector2 = 37,
	msosptCurvedConnector3 = 38,
	msosptCurvedConnector4 = 39,
	msosptCurvedConnector5 = 40,
	msosptCallout1 = 41,
	msosptCallout2 = 42,
	msosptCallout3 = 43,
	msosptAccentCallout1 = 44,
	msosptAccentCallout2 = 45,
	msosptAccentCallout3 = 46,
	msosptBorderCallout1 = 47,
	msosptBorderCallout2 = 48,
	msosptBorderCallout3 = 49,
	msosptAccentBorderCallout1 = 50,
	msosptAccentBorderCallout2 = 51,
	msosptAccentBorderCallout3 = 52,
	msosptRibbon = 53,
	msosptRibbon2 = 54,
	msosptChevron = 55,
	msosptPentagon = 56,
	msosptNoSmoking = 57,
	msosptSeal8 = 58,
	msosptSeal16 = 59,
	msosptSeal32 = 60,
	msosptWedgeRectCallout = 61,
	msosptWedgeRRectCallout = 62,
	msosptWedgeEllipseCallout = 63,
	msosptWave = 64,
	msosptFoldedCorner = 65,
	msosptLeftArrow = 66,
	msosptDownArrow = 67,
	msosptUpArrow = 68,
	msosptLeftRightArrow = 69,
	msosptUpDownArrow = 70,
	msosptIrregularSeal1 = 71,
	msosptIrregularSeal2 = 72,
	msosptLightningBolt = 73,
	msosptHeart = 74,
	msosptPictureFrame = 75,
	msosptQuadArrow = 76,
	msosptLeftArrowCallout = 77,
	msosptRightArrowCallout = 78,
	msosptUpArrowCallout = 79,
	msosptDownArrowCallout = 80,
	msosptLeftRightArrowCallout = 81,
	msosptUpDownArrowCallout = 82,
	msosptQuadArrowCallout = 83,
	msosptBevel = 84,
	msosptLeftBracket = 85,
	msosptRightBracket = 86,
	msosptLeftBrace = 87,
	msosptRightBrace = 88,
	msosptLeftUpArrow = 89,
	msosptBentUpArrow = 90,
	msosptBentArrow = 91,
	msosptSeal24 = 92,
	msosptStripedRightArrow = 93,
	msosptNotchedRightArrow = 94,
	msosptBlockArc = 95,
	msosptSmileyFace = 96,
	msosptVerticalScroll = 97,
	msosptHorizontalScroll = 98,
	msosptCircularArrow = 99,
	msosptNotchedCircularArrow = 100,
	msosptUturnArrow = 101,
	msosptCurvedRightArrow = 102,
	msosptCurvedLeftArrow = 103,
	msosptCurvedUpArrow = 104,
	msosptCurvedDownArrow = 105,
	msosptCloudCallout = 106,
	msosptEllipseRibbon = 107,
	msosptEllipseRibbon2 = 108,
	msosptFlowChartProcess = 109,
	msosptFlowChartDecision = 110,
	msosptFlowChartInputOutput = 111,
	msosptFlowChartPredefinedProcess = 112,
	msosptFlowChartInternalStorage = 113,
	msosptFlowChartDocument = 114,
	msosptFlowChartMultidocument = 115,
	msosptFlowChartTerminator = 116,
	msosptFlowChartPreparation = 117,
	msosptFlowChartManualInput = 118,
	msosptFlowChartManualOperation = 119,
	msosptFlowChartConnector = 120,
	msosptFlowChartPunchedCard = 121,
	msosptFlowChartPunchedTape = 122,
	msosptFlowChartSummingJunction = 123,
	msosptFlowChartOr = 124,
	msosptFlowChartCollate = 125,
	msosptFlowChartSort = 126,
	msosptFlowChartExtract = 127,
	msosptFlowChartMerge = 128,
	msosptFlowChartOfflineStorage = 129,
	msosptFlowChartOnlineStorage = 130,
	msosptFlowChartMagneticTape = 131,
	msosptFlowChartMagneticDisk = 132,
	msosptFlowChartMagneticDrum = 133,
	msosptFlowChartDisplay = 134,
	msosptFlowChartDelay = 135,
	msosptTextPlainText = 136,
	msosptTextStop = 137,
	msosptTextTriangle = 138,
	msosptTextTriangleInverted = 139,
	msosptTextChevron = 140,
	msosptTextChevronInverted = 141,
	msosptTextRingInside = 142,
	msosptTextRingOutside = 143,
	msosptTextArchUpCurve = 144,
	msosptTextArchDownCurve = 145,
	msosptTextCircleCurve = 146,
	msosptTextButtonCurve = 147,
	msosptTextArchUpPour = 148,
	msosptTextArchDownPour = 149,
	msosptTextCirclePour = 150,
	msosptTextButtonPour = 151,
	msosptTextCurveUp = 152,
	msosptTextCurveDown = 153,
	msosptTextCascadeUp = 154,
	msosptTextCascadeDown = 155,
	msosptTextWave1 = 156,
	msosptTextWave2 = 157,
	msosptTextWave3 = 158,
	msosptTextWave4 = 159,
	msosptTextInflate = 160,
	msosptTextDeflate = 161,
	msosptTextInflateBottom = 162,
	msosptTextDeflateBottom = 163,
	msosptTextInflateTop = 164,
	msosptTextDeflateTop = 165,
	msosptTextDeflateInflate = 166,
	msosptTextDeflateInflateDeflate = 167,
	msosptTextFadeRight = 168,
	msosptTextFadeLeft = 169,
	msosptTextFadeUp = 170,
	msosptTextFadeDown = 171,
	msosptTextSlantUp = 172,
	msosptTextSlantDown = 173,
	msosptTextCanUp = 174,
	msosptTextCanDown = 175,
	msosptFlowChartAlternateProcess = 176,
	msosptFlowChartOffpageConnector = 177,
	msosptCallout90 = 178,
	msosptAccentCallout90 = 179,
	msosptBorderCallout90 = 180,
	msosptAccentBorderCallout90 = 181,
	msosptLeftRightUpArrow = 182,
	msosptSun = 183,
	msosptMoon = 184,
	msosptBracketPair = 185,
	msosptBracePair = 186,
	msosptSeal4 = 187,
	msosptDoubleWave = 188,
	msosptActionButtonBlank = 189,
	msosptActionButtonHome = 190,
	msosptActionButtonHelp = 191,
	msosptActionButtonInformation = 192,
	msosptActionButtonForwardNext = 193,
	msosptActionButtonBackPrevious = 194,
	msosptActionButtonEnd = 195,
	msosptActionButtonBeginning = 196,
	msosptActionButtonReturn = 197,
	msosptActionButtonDocument = 198,
	msosptActionButtonSound = 199,
	msosptActionButtonMovie = 200,
	msosptHostControl = 201,
	msosptTextBox = 202,
	msosptMax,
	msosptNil = 0x0FFF,
};

struct FOPTE
{
	struct
	{
      unsigned pid : 14;     // Property ID
      unsigned fBid : 1;     // value is a blip ID – only valid if fComplex is FALSE
      unsigned fComplex : 1; // complex property, value is length
   }
	key;
   ULONG   op;  // Value
};

enum
{
	// Transform
	Prop_rotation = 4,

	// Blip
	Prop_pib = 260,
	Prop_pibName = 261,

	// Text
	Prop_lTxid = 128,

	// Geometry
	Prop_pVertices = 325,
	Prop_pSegmentInfo = 326,

	// Fill Style
	Prop_fillType = 384,
	Prop_fillColor = 385,
	Prop_fillOpacity = 386,
	Prop_fillBackColor = 387,
	Prop_fillBackOpacity = 388,

	Prop_fNoFillHitTest = 447,

	// Line Style
	Prop_lineColor = 448,
	Prop_lineOpacity = 449,
	Prop_lineWidth = 459,
	Prop_lineMiterLimit = 460,
	Prop_fLine = 508,
};

typedef ULONG MSOFO;

// FBSE - File Blip Store Entry
struct FBSE
{
	uint8     btWin32;    // Required type on Win32
	uint8     btMacOS;    // Required type on Mac
	uint8     rgbUid[16]; // Identifier of blip
	uint16    tag;        // currently unused
	ULONG     size;       // Blip size in stream
	ULONG     cRef;       // Reference count on the blip
	MSOFO     foDelay;    // File offset in the delay stream
	uint8     usage;      // How this blip is used (MSOBLIPUSAGE)
	uint8     cbName;     // length of the blip name
	uint8     unused2;    // for the future
	uint8     unused3;    // for the future
};

enum MSOBLIPUSAGE
{
	msoblipUsageDefault,  // All non-texture fill blips get this.
	msoblipUsageTexture,
	msoblipUsageMax = 255 // Since this is stored in a byte
};

enum MSOBLIPTYPE
{                          // GEL provided types...
	msoblipERROR = 0,          // An error occured during loading
	msoblipUNKNOWN,            // An unknown blip type
	msoblipEMF,                // Windows Enhanced Metafile
	msoblipWMF,                // Windows Metafile
	msoblipPICT,               // Macintosh PICT
	msoblipJPEG,               // JFIF
	msoblipPNG,                // PNG
	msoblipDIB,                // Windows DIB
	msoblipFirstClient = 32,   // First client defined blip type
	msoblipLastClient  = 255   // Last client defined blip type
};

enum MSOBI                     // Blip signature as encoded in the MSOFBH.inst
{
	msobiUNKNOWN = 0,
	msobiWMF  = 0x216,      // Metafile header then compressed WMF
	msobiEMF  = 0x3D4,      // Metafile header then compressed EMF
	msobiPICT = 0x542,      // Metafile header then compressed PICT
	msobiPNG  = 0x6E0,      // One byte tag then PNG data
	msobiJFIF = 0x46A,      // One byte tag then JFIF data
	msobiJPEG = msobiJFIF,
	msobiDIB  = 0x7A8,      // One byte tag then DIB data
	msobiClient=0x800,      // Clients should set this bit
};

struct ClientAnchor
{
	uint16 flag;

	uint16 col1;
	short dx1;
	uint16 row1;
	short dy1;
	uint16 col2;
	short dx2;
	uint16 row2;
	short dy2;
};

struct METAFILEHEADER
{
	uint32           m_cb;           // Cache of the metafile size
	LDraw::BBoxi   m_rcBounds;     // Boundary of metafile drawing commands
	LDraw::Sizei  m_ptSize;       // Size of metafile in EMUs
	uint32           m_cbSave;       // Cache of saved size (size of m_pvBits)
	uint8          m_fCompression; // MSOBLIPCOMPRESSION
	uint8         m_fFilter;      // always msofilterNone
//	void         *m_pvBits;       // Compressed bits of metafile
};

enum MSOBLIPCOMPRESSION
   {
   msocompressionDeflate = 0,
   msocompressionNone = 254,    // Used only if compression fails
   msocompressionTest = 255,    // For testing only
   };

enum MSOBLIPFILTER
   {
   msofilterAdaptive = 0,       // PNG type - not used/supported for metafile
   msofilterNone = 254,
   msofilterTest = 255,         // For testing only
   }
;

#pragma pack(pop)

class PropertyEntry
{
public:
	long value;
	ULONG offset;
};

class PropertyList
{
public:
	PropertyList()
	{
		m_blobdata = NULL;
		m_blobsize = 0;
	}
	map<uint32,PropertyEntry*> m_entries;
	uint8* m_blobdata;
	uint32 m_blobsize;
};

class TopShape : public UI::UIElement
{
public:
	uint32 col1;
	double dx1;
	uint32 row1;
	double dy1;
	uint32 col2;
	double dx2;
	uint32 row2;
	double dy2;

	/*
	LDraw::SizeD m_originalSize;


	virtual void OnRender(UI::Graphics* pGraphics)
	{
		UIElement::OnRender2(pGraphics);
	}

	virtual void OnArrange(LDraw::SizeD finalSize)
	{
		UIElement::OnArrange(finalSize);
	}
	*/
	Sheet* m_pSheet;
};

class Shape : public TopShape
{
public:
	Shape()
	{
		m_strokeWidth = 1.0f;
		m_pText = NULL;
	}

	StringEntry* m_pText;

	int m_strokeColor;
	int m_fillColor;
	float m_strokeWidth;

	__release<LDraw::GraphicsPathF> m_path;

	virtual void OnRender(UI::Graphics* pGraphics);
};

class PictureFrame : public TopShape
{
public:
	PictureFrame()
	{
		m_pBlip = NULL;
	}

	Blip* m_pBlip;

	virtual void OnRender(UI::Graphics* pGraphics)
	{
		if (m_pBlip)
		{
			pGraphics->ScaleTransform(m_computedSize.Width / m_pBlip->m_originalSize.Width, m_computedSize.Height / m_pBlip->m_originalSize.Height);

			if (m_pBlip->m_bitmap != NULL)
			{
				pGraphics->DrawImage(m_pBlip->m_bitmap, 0, 0);
			}
			else
			{
				pGraphics->RenderCommands(m_pBlip->m_commands);//->Render(->m_p);
			}
		}
	}
};

class DrawingLoader
{
public:

	void Drawing(System::IO::ISequentialByteStream* pStream, ULONG length, UI::UIElement* pVisual);

	Blips* m_blips;

	map<ULONG,ULONG> m_posmap;

	System::IO::ISequentialByteStream* m_pContainerStream;

protected:

	UI::UIElement* SpContainer(System::IO::ISequentialByteStream* pStream, ULONG length);
	void SpgrContainer(System::IO::ISequentialByteStream* pStream, ULONG length, UI::UIElement* pVisual);
	void DgContainer(System::IO::ISequentialByteStream* pStream, ULONG length, UI::UIElement* pVisual);
	void DggContainer(System::IO::ISequentialByteStream* pStream, ULONG length, UI::UIElement* pVisual);
	void BstoreContainer(System::IO::ISequentialByteStream* pStream, ULONG length, ULONG count);
	void BSE(System::IO::ISequentialByteStream* pStream, Blip* pBlip, int blip_instance, ULONG length);

	void ReadOPT(System::IO::ISequentialByteStream* pStream, const MSOFBH& record, PropertyList* options);
};

}	// MSODrawing

}
