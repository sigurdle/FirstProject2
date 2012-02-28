#ifndef SWF_Movie_h
#define SWF_Movie_h

#ifndef SWFExt
#define SWFExt	DECLSPEC_DLLIMPORT
#endif

namespace System
{
namespace SWF
{

enum
{
	CondIdleToOverDown = 128,
	CondOutDownToIdle = 64,
	CondOutDownToOverDown = 32,
	CondOverDownToOutDown = 16,
	CondOverDownToOverUp = 8,
	CondOverUpToOverDown = 4,
	CondOverUpToIdle = 2,
	CondIdleToOverUp = 1,
	//uint8 CondKeyPress = getnbits(7);
	CondOverDownToIdle = 256,
};


#if 0
//class VM2;


#endif

class Tag
{
public:
	uint32 Length;
	uint16 Code;

	enum
	{
		ShowFrame = 1,
		DefineShape = 2,
		SetBackgroundColor = 9,
		DefineFont = 10,
		DefineText = 11,
		DoAction = 12,
		DefineFontInfo = 13,
		DefineSound = 14,
		StartSound = 15,
		SoundStreamHead = 18,
		DefineBitsLossless = 20,
		DefineBitsJPEG2 = 21,
		DefineShape2 = 22,
		Protect = 24,
		PlaceObject2 = 26,
		RemoveObject2 = 28,
		DefineShape3 = 32,
		DefineText2 = 33,
		DefineButton2 = 34,
		DefineBitsJPEG3 = 35,
		DefineBitsLossless2 = 36,
		DefineEditText = 37,
		DefineSprite = 39,
		FrameLabel = 43,
		SoundStreamHead2 = 45,
		DefineFont2 = 48,
		ExportAssets = 56,
		DefineVideoStream = 60,
		VideoFrame = 61,
	};
};

class Movie;

class RGBColor
{
public:
	inline CTOR RGBColor()
	{
	}

	inline CTOR RGBColor(uint8 red, uint8 green, uint8 blue)
	{
		Red = red;
		Green = green;
		Blue = blue;
	}

	inline operator LDraw::Color() const
	{
		return LDraw::Color(Red, Green, Blue);
	}

	uint8 Red;
	uint8 Green;
	uint8 Blue;
};

class RGBAColor : public RGBColor
{
public:
	inline CTOR RGBAColor()
	{
	}

	inline CTOR RGBAColor(uint8 red, uint8 green, uint8 blue, uint8 alpha) : RGBColor(red, green, blue)
	{
		Alpha = alpha;
	}

	inline operator LDraw::Color() const
	{
		return LDraw::Color(Alpha, Red, Green, Blue);
	}

	uint8 Alpha;
};

struct Rect
{
	CTOR Rect()
	{
		Xmin = 0;
		Xmax = 0;
		Ymin = 0;
		Ymax = 0;
	}

	CTOR Rect(int32 xmin, int32 xmax, int32 ymin, int32 ymax)
	{
		Xmin = xmin;
		Xmax = xmax;
		Ymin = ymin;
		Ymax = ymax;
	}

	int32 Xmin;
	int32 Xmax;
	int32 Ymin;
	int32 Ymax;
};

class ColorTransform
{
public:
	CTOR ColorTransform()
	{
		MulR = 1<<8;
		MulG = 1<<8;
		MulB = 1<<8;
		MulA = 1<<8;

		AddR = 0;
		AddG = 0;
		AddB = 0;
		AddA = 0;
	}

	uint16 MulR;
	uint16 MulG;
	uint16 MulB;
	uint16 MulA;

	short AddR;
	short AddG;
	short AddB;
	short AddA;

	ColorTransform operator * (const ColorTransform& other) const
	{
		ColorTransform x;
		x.MulR = MulR * other.MulR / 256;
		x.MulG = MulG * other.MulG / 256;
		x.MulB = MulB * other.MulB / 256;
		x.MulA = MulA * other.MulA / 256;

		x.AddR = AddR + other.AddR;
		x.AddG = AddG + other.AddG;
		x.AddB = AddB + other.AddB;
		x.AddA = AddA + other.AddA;

		return x;
	}
};

//class _FillStyle;
class BitmapCharacter;

class SWFExt FillStyle : public Object
{
public:

	/*
	FillStyle()
	{
		m_p = NULL;
	}

	FillStyle(const FillStyle& other);
	FillStyle(RGBAColor color);
	~FillStyle();
	FillStyle& operator = (const FillStyle& other);
	*/

	CTOR FillStyle(RGBAColor color);
	CTOR FillStyle(uint8 filltype, RGBAColor color);
	CTOR FillStyle(uint8 filltype, BitmapCharacter* bitmap);

	uint8 GetFillType() const;
	RGBAColor GetColor() const;
	BitmapCharacter* GetBitmapCharacter() const;

	int m_index;

	//ULONG m_refcount;

	uint8 m_Type;

	RGBAColor m_color;
	BitmapCharacter* m_bitmap;

//	_FillStyle* m_p;
};

class SWFExt LineStyle : public System::Object
{
public:

	/*
	LineStyle()
	{
		m_p = NULL;
	}

	LineStyle(const LineStyle& other)
	{
		m_p = other.m_p;
		if (m_p)
			m_p->AddRef();
	}

	~LineStyle()
	{
		if (m_p)
			m_p->Release();
	}

	LineStyle& operator = (const LineStyle& other)
	{
		_LineStyle* old = m_p;
		m_p = other.m_p;
		if (m_p) m_p->AddRef();
		if (old) old->Release();

		return *this;
	}
	*/

	/*
	class _LineStyle : public System::Object
	{
	public:
		_LineStyle() : m_refcount(0)
		{
		}
		*/

		int m_index;

		/*
		ULONG m_refcount;
	};
	*/

	//_LineStyle* m_p;
};

class SWFExt TagObject : public System::Object
{
public:
	/*
	class _TagObject : virtual public System::Object
	{
	public:
	*/
		Movie* m_parentMovie;
		uint16 m_Code;
		/*
	};
	*/

	CTOR TagObject()
	{
		m_parentMovie = NULL;
		//m_p = NULL;
	}

	/*
	TagObject(_TagObject* p)
	{
		m_p = p;
		if (m_p) m_p->AddRef();
	}

	TagObject(const TagObject& other)
	{
		m_p = other.m_p;
		if (m_p) m_p->AddRef();
	}

	~TagObject()
	{
		if (m_p) m_p->Release();
	}

	_TagObject* m_p;

	operator System::Object() const
	{
		return System::Object(m_p);
	}

	TagObject& operator = (const TagObject& other)
	{
		_TagObject* old = m_p;
		m_p = other.m_p;
		if (m_p) m_p->AddRef();
		if (old) old->Release();

		return *this;
	}

	bool operator == (const TagObject& other) const
	{
		return m_p == other.m_p;
	}

	inline bool operator != (const TagObject& other) const
	{
		return !(*this == other);
	}
	*/
};

class SWFExt Character : public TagObject
{
public:
	/*
	class _Character : public TagObject::_TagObject
	{
	public:
	*/
		uint16 m_CharacterID;
		/*
	};
	*/


	CTOR Character()
	{
	}

	/*
	Character(_Character* p)
	{
		m_p = p;
		if (m_p) m_p->AddRef();
	}

	Character(const Character& other)
	{
		m_p = other.m_p;
		if (m_p) m_p->AddRef();
	}

	Character(const System::Object& other)
	{
		m_p = dynamic_cast<_Character*>(other.m_p);
		if (m_p) m_p->AddRef();
	}
	*/

	uint16 GetCharacterID() const
	{
		return m_CharacterID;
	}

	void SetCharacterID(uint16 CharacterID)
	{
		//ASSERT(m_p->m_refcount == 1);

		m_CharacterID = CharacterID;
	}
};

class ShapeData
{
public:
	vector<uint8> m_types;
	vector<LDraw::PointI> m_points;
	vector<FillStyle*> m_fillStyles;
	vector<LineStyle*> m_lineStyles;

	void MoveTo(long x, long y)
	{
		m_types.Add(0);
		m_points.Add(LDraw::PointI(x, y));
	}

	void LineTo(long x, long y)
	{
		m_types.Add(1);
		m_points.Add(LDraw::PointI(x, y));
	}

	void CurveTo(long x1, long y1, long x2, long y2)
	{
		m_types.Add(2);
		m_points.Add(LDraw::PointI(x1, y1));
		m_points.Add(LDraw::PointI(x2, y2));
	}
};

class SWFExt ShapeCharacter : public Character, public ShapeData
{
public:

	/*
	class _ShapeCharacter : public Character::_Character, public ShapeData
	{
	public:
	*/
		Rect m_Bounds;
		/*
	};

	ShapeCharacter()
	{
	}

	ShapeCharacter(_ShapeCharacter* p)
	{
		m_p = p;
		if (m_p) m_p->AddRef();
	}

	ShapeCharacter(const ShapeCharacter& other)
	{
		m_p = other.m_p;
		if (m_p) m_p->AddRef();
	}

	ShapeCharacter(const System::Object& other)
	{
		m_p = dynamic_cast<_ShapeCharacter*>(other.m_p);
		if (m_p) m_p->AddRef();
	}

	_ShapeCharacter* get_p() const
	{
		return (_ShapeCharacter*)m_p;
	}
	*/

	void GetBounds(Rect* rect) const
	{
		*rect = m_Bounds;
	}

	void SetBounds(const Rect& rect)
	{
		m_Bounds = rect;
	}

	/*
	void MoveTo(long x, long y)
	{
		MoveTo(x, y);
	}

	void LineTo(long x, long y)
	{
		((_ShapeCharacter*)m_p)->LineTo(x, y);
	}

	void CurveTo(long x1, long y1, long x2, long y2)
	{
		((_ShapeCharacter*)m_p)->CurveTo(x1, y1, x2, y2);
	}
	*/
};

class SWFExt BitmapCharacter : public Character
{
public:
	/*
	class _BitmapCharacter : public Character::_Character
	{
	public:
		_BitmapCharacter()
		{

		}
		*/

		uint16 m_Width;
		uint16 m_Height;
		uint8 m_Format;
		uint8 m_BitmapColorTableSize;	// one less than the number of colors, only valid when Format=3

		RGBAColor* m_palette;
		uint8* m_bits;
		uint32 m_rowbytes;
		/*
	};
*/
	CTOR BitmapCharacter()
	{
			m_palette = NULL;
			m_bits = NULL;
	}

	/*
	BitmapCharacter(_BitmapCharacter* p)
	{
		m_p = p;
		if (m_p) m_p->AddRef();
	}

	BitmapCharacter(const BitmapCharacter& other)
	{
		m_p = other.m_p;
		if (m_p) m_p->AddRef();
	}

	BitmapCharacter(const System::Object& other)
	{
		m_p = dynamic_cast<_BitmapCharacter*>(other.m_p);
		if (m_p) m_p->AddRef();
	}

	BitmapCharacter& operator = (const System::Object& other)
	{
		_BitmapCharacter* old = (_BitmapCharacter*)m_p;
		m_p = dynamic_cast<_BitmapCharacter*>(other.m_p);
		if (m_p) m_p->AddRef();
		if (old) old->Release();

		return *this;
	}
	*/

	unsigned int GetWidth() const
	{
		return m_Width;
	}

	unsigned int GetHeight() const
	{
		return m_Height;
	}

	int GetRowBytes() const
	{
		return m_rowbytes;
	}

	uint8* GetBits() const
	{
		return m_bits;
	}
};

class ButtonRecord
{
public:
	ShapeCharacter* m_shape;
	uint16 m_PlaceDepth;
	__release<LDraw::Matrix3f> m_Transform;
};

class ActionScript
{
public:
	uint8* m_data;
	ULONG m_length;
};

class ButtonActionScript : public ActionScript
{
public:

	CTOR ButtonActionScript()
	{
		m_context = new System::ActionScripting::ActionContext;
	}

	~ButtonActionScript()
	{
		delete m_context;
	}


	uint16 m_cond;

	ActionScripting::ActionContext* m_context;
};

class SWFExt ButtonCharacter : public Character
{
public:

	/*
	class _ButtonCharacter : public Character::_Character
	{
	public:
		_ButtonCharacter()
		{
			m_TrackAsMenu = false;
		}
*/
		bool m_TrackAsMenu : 1;

		vector<ButtonRecord*> m_StateDown;
		vector<ButtonRecord*> m_StateUp;
		vector<ButtonRecord*> m_StateOver;
		vector<ButtonRecord*> m_HitTest;

		vector<ButtonActionScript*> m_scripts;
//	};


	CTOR ButtonCharacter()
	{
			m_TrackAsMenu = false;
	}

	/*
	ButtonCharacter(_ButtonCharacter* p)
	{
		m_p = p;
		if (m_p) m_p->AddRef();
	}

	ButtonCharacter(const ButtonCharacter& other)
	{
		m_p = other.m_p;
		if (m_p) m_p->AddRef();
	}

	ButtonCharacter(const System::Object& other)
	{
		m_p = dynamic_cast<_ButtonCharacter*>(other.m_p);
		if (m_p) m_p->AddRef();
	}
	*/
};

class SWFExt FontCharacter : public Character
{
public:
	/*
	class _FontCharacter : public Character::_Character
	{
	public:
		_FontCharacter()
		{
		}
*/
		String m_FontName;

		vector<ShapeData*> m_glyphShapes;
//	};

	CTOR FontCharacter()
	{
		m_FontName = NULL;
	}

	/*
	FontCharacter(_FontCharacter* p)
	{
		m_p = p;
		if (m_p) m_p->AddRef();
	}

	FontCharacter(const FontCharacter& other)
	{
		m_p = other.m_p;
		if (m_p) m_p->AddRef();
	}

	FontCharacter(const System::Object& other)
	{
		m_p = dynamic_cast<_FontCharacter*>(other.m_p);
		if (m_p) m_p->AddRef();
	}

	FontCharacter& operator = (const System::Object& other)
	{
		_FontCharacter* old = (_FontCharacter*)m_p;
		m_p = dynamic_cast<_FontCharacter*>(other.m_p);
		if (m_p) m_p->AddRef();
		if (old) old->Release();

		return *this;
	}
	*/

	System::StringA* GetFontName() const
	{
		return m_FontName;
	}

	ShapeData* GetGlyph(int index) const
	{
		return m_glyphShapes[index];
	}
};

class GlyphRun
{
public:

	FontCharacter* m_font;
	RGBAColor m_color;
	short m_XOffset;
	short m_YOffset;
	uint16 m_fontHeight;
	uint16 m_reserved;

	vector<int> m_glyphs;
	vector<int> m_widths;
};

class SWFExt TextCharacter : public Character
{
public:
	/*
	class _TextCharacter : public Character::_Character
	{
	public:
	*/
		Rect m_Bounds;
		LDraw::Matrix3f* m_Transform;

		vector<GlyphRun*> m_runs;
	//};

	CTOR TextCharacter()
	{
		m_Transform = NULL;
	}

	/*
	TextCharacter(_TextCharacter* p)
	{
		m_p = p;
		if (m_p) m_p->AddRef();
	}

	TextCharacter(const TextCharacter& other)
	{
		m_p = other.m_p;
		if (m_p) m_p->AddRef();
	}

	TextCharacter(const System::Object& other)
	{
		m_p = dynamic_cast<_TextCharacter*>(other.m_p);
		if (m_p) m_p->AddRef();
	}
	*/
};

class VideoStreamCharacter : public Character
{
public:
	/*
	class _VideoStreamCharacter : public Character::_Character
	{
	public:
	*/
		uint16 m_Width;
		uint16 m_Height;
		uint16 m_NumFrames;
		uint8 m_CodecID;
		/*
	};

	VideoStreamCharacter(_VideoStreamCharacter* p)
	{
		m_p = p;
		if (m_p) m_p->AddRef();
	}
	*/
};

class Timeline;

class PlacedCharacter : public Object, public ActionScripting::MembersMap
{
public:

	class gotoAndPlay : public ActionScripting::Function
	{
	public:
		CTOR gotoAndPlay(PlacedCharacter* placed)
		{
			m_placed = placed;
		}

		virtual void dispatch(System::ActionScripting::VM* vm, System::ActionScripting::StackFrame* pStackFrame, int numargs);

		PlacedCharacter* m_placed;
	};

	CTOR PlacedCharacter()
	{
		m_gotoFrame = 0;
		m_currentFrame = 0;
		m_transform = LDraw::Matrix3f::GetIdentity();
	}

	virtual System::Variant GetMember(StringIn name);

//	virtual void gotoAndPlay(StringA label);

	virtual long get__currentframe() const
	{
		return m_currentFrame;
	}

	Character* m_character;
//	uint16 m_CharacterID;
	String m_name;

	LDraw::Matrix3f* m_transform;
	ColorTransform m_colorTransform;

	long m_currentFrame;
	long m_gotoFrame;

	Timeline* m_parent;

	vector<ButtonActionScript*> m_scripts;
};

interface ITimeline
{
	virtual int GetFrameCount() const = 0;
	virtual void SetFrameCount(int FrameCount) = 0;
};

class DoActionScript : public ActionScript
{
public:
};

/*
class FrameTag
{
public:

	int kind;

	int CharacterID;
	int Depth;
};
*/

class Decoder;

class Frame
{
public:
	Decoder* m_stream;
	LONGLONG m_streamPos;
	//ULONG m_
	vector<DoActionScript*> m_doActions;
//	std::vector<FrameTag*> m_tags;
	void DoActions(PlacedCharacter* placed);
};

class SWFExt Timeline : public ITimeline
{
public:
	CTOR Timeline();

	virtual int GetFrameCount() const 
	{
		return m_FrameCount;
	}

	virtual void SetFrameCount(int FrameCount)
	{
		ASSERT(FrameCount >= 0 && FrameCount < 65536);
		m_FrameCount = FrameCount;
	}

	uint16 m_DecodedFrameCount;

	map<String, int> m_labels;

	vector<Frame*> m_frames;

	virtual long get__framesloaded() const
	{
		return m_DecodedFrameCount;
	}

	virtual long get__totalframes() const
	{
		return m_FrameCount;
	}

	virtual void gotoAndPlay(StringIn label);

	void PlaceCharacterAtDepth(PlacedCharacter* placed, uint16 Depth)
	{
		m_depth[Depth] = placed;
	}

	PlacedCharacter* GetPlacedCharacterAtDepth(uint16 Depth)
	{
		return m_depth[Depth];
	}

	void ClearPlacedCharacterAtDepth(uint16 Depth)
	{
		m_depth[Depth] = NULL;
	}

protected:

	uint16 m_FrameCount;
	PlacedCharacter** m_depth;
};

class _Sprite;

class SWFExt Sprite : public Character, public Timeline, public System::ActionScripting::MembersMap
{
public:

	/*
	Sprite();
	Sprite(const Sprite& other);
	Sprite(_Sprite* p);
	Sprite(const System::Object& other);
	int GetFrameCount() const ;
	void SetFrameCount(int FrameCount);
*/

	virtual System::Variant GetMember(StringIn name);

	PlacedCharacter* m_placed;	// ?? sprite can only be placed once ?
};

class SWFExt Movie : public System::Object, public Timeline, public System::ActionScripting::MembersMap
{
public:

	CTOR Movie();

	//class _Movie* m_p;

	/*
	Movie()
	{
		m_p = NULL;
	}

	Movie(const Movie& other);
	~Movie();

	Movie& operator = (const Movie& other);

	bool IsSame(const Movie& other) const
	{
		return m_p == other.m_p;
	}
*/
//	Movie& New();

	bool HasBackgroundColor() const;
	RGBColor GetBackgroundColor() const;
	Rect GetFrameSize() const;

	void SetFrameSize(long Width, long Height);
	void SetFrameRate(uint16 FrameRate);
	uint16 GetFrameRate() const;
	void SetBackgroundColor(RGBColor color);

	virtual void DefineShape(uint8 level, Character* character);
	virtual void DefineBitsLossless(uint8 level, Character* character);
	Character* GetCharacter(int index) const;

	int GetFrameCount() const;
	void SetFrameCount(int FrameCount);

#if 0
	uint16 GetFreeDefinitionID()
	{
		WORD newID = 1;
		tydefmap::iterator it;;
		while ((it = m_definitions.find(newID)) == m_definitions.end())
		{
			newID++;
			if (newID == 0)	// Wrapped around to 0
				break;
		}

		return newID;
	}
#endif

	ShapeCharacter* CreateShape()
	{
		ShapeCharacter* shape = new ShapeCharacter;

		ASSERT(0);
#if 0
		uint16 newID = ++m_lastDefinitionID;
		shape->SetCharacterID(newID);
#endif
//		m_definitions.insert(

		return shape;
	}

	bool m_bBackground;
	RGBColor m_BackgroundColor;
	Rect m_FrameSize;
	uint16 m_FrameRate;

//	typedef map<uint16, Character*> tydefmap;
//	tydefmap m_definitions;

	uint16 m_lastDefinitionID;

	Character** m_character;

	ULONG m_scriptFlags;
	ActionScripting::VM::BreakpointFunction m_scriptBreakpoint;
	Object* m_scriptUserObject;
};

}	// SWF
}

#endif // SWF_Movie_h
