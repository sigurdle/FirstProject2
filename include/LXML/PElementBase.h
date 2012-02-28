#ifndef Web_PElementBase_h
#define Web_PElementBase_h

//#include "OleClientItem.h"

#if 0
#include "ColorProfile.h"
#endif

//#include "cssproperty.h"

namespace System
{
namespace Web
{
//class Element;

class WEBEXT CRGBColor : public Graphics::Color
{
public:
	CTOR CRGBColor() : Graphics::Color()
	{
	}
	
	CTOR CRGBColor(uint8 r, uint8 g, uint8 b)
	{
		Argb = MakeARGB(255, r, g, b);
	}
	
   CTOR  CRGBColor(uint8 a, uint8 r, uint8 g, uint8 b)
	{
		Argb = MakeARGB(a, r, g, b);
	}
/*
    CRGBColor(IN ARGB argb)
    {
        Argb = argb;
    }
*/
	 /*
	 CRGBColor(ILRGBColor* rgbColor)
	{
		*this = rgbColor;
	}
	*/

	CTOR CRGBColor(CSSPrimitiveValue* cssprimitiveValue)
	{
		*this = cssprimitiveValue;
	}

	CRGBColor& operator = (CSSPrimitiveValue* cssprimitiveValue)
	{
		CSSUnitType unitType = cssprimitiveValue->get_primitiveType();

		if (unitType == CSS_RGBCOLOR)
		{
			*this = cssprimitiveValue->getRGBColorValue();
		}
		else
		{
			*this = CRGBColor(0, 0, 0, 0);	// transparent
		}

		return *this;
	}

	CRGBColor& operator = (RGBColor* rgbColor)
	{
		CSSPrimitiveValue* cssred = rgbColor->get_red();
		CSSPrimitiveValue* cssgreen = rgbColor->get_green();
		CSSPrimitiveValue* cssblue = rgbColor->get_blue();

		double red = cssred->getFloatValue(CSS_NUMBER);
		double green = cssgreen->getFloatValue(CSS_NUMBER);
		double blue = cssblue->getFloatValue(CSS_NUMBER);

		double alpha = rgbColor->get_alpha();
		if (alpha < 0) alpha = 0;
		else if (alpha > 1) alpha = 1;

		SetValue(Graphics::Color::MakeARGB((uint8)(alpha*255), (uint8)red, (uint8)green, (uint8)blue));

		return *this;
	}
};
}
}

#include "LBoxes.h"

namespace System
{
namespace Web
{
class CColorProfile;

//class DocumentStyleImpl;
//class CSSElementMatches;

class Element;
class PElementBase;

//class CPPElement;
class PGenericElement;

class CHTMLineBox;

#if 0
class CScrollBarObject :
	public CComObjectRootEx<CComSingleThreadModel>
#if 0
		,
	public COleClientItem
	public IDispEventImpl<1, CScrollBarObject, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>
#endif
{
public:

	CPElementBase* m_pPElement;

	CScrollBarObject()
	{
		m_pPElement = NULL;
	}

	~CScrollBarObject()
	{
	}

BEGIN_COM_MAP(CScrollBarObject)
//	COM_INTERFACE_ENTRY(IDispatch)
#if 0
	COM_INTERFACE_ENTRY(IOleClientSite)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY2(IOleInPlaceSite, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY2(IOleInPlaceSiteEx, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceSiteWindowless)
#endif
END_COM_MAP()

#if 0
BEGIN_SINK_MAP(CScrollBarObject)
//   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnScroll)
END_SINK_MAP()
#endif

	void __stdcall OnScroll(long code, long pos);
};
#endif

#if 0
enum
{
	Display_inline = 0,
	Display_block,
	Display_list_item,
	Display_run_in,
	Display_compact,
	Display_marker,
	Display_table,
	Display_inline_table,
	Display_table_row_group,
	Display_table_header_group,
	Display_table_footer_group,
	Display_table_row,
	Display_table_column_group,
	Display_table_column,
	Display_table_cell,
	Display_table_caption,
	Display_none,

// Mozilla compliant XUL display modes
	Display_inline_box,
	Display_box,
};
#endif

enum DisplayModel : unsigned char
{
	DisplayModel_inline_inside,
	DisplayModel_block_inside,
	DisplayModel_table,
	DisplayModel_ruby,

// Mozilla compliant XUL display modes
	DisplayModel_box
};

enum DisplayRole : unsigned char
{
	DisplayRole_none,
	DisplayRole_block,
	DisplayRole_inline,
	DisplayRole_list_item,
	DisplayRole_run_in,
	DisplayRole_compact,
	DisplayRole_table_row,
	DisplayRole_table_cell,
	DisplayRole_table_row_group,
	DisplayRole_table_header_group,
	DisplayRole_table_footer_group,
	DisplayRole_table_column,
	DisplayRole_table_column_group,
	DisplayRole_table_caption,
	DisplayRole_ruby_text,
	DisplayRole_ruby_base,
	DisplayRole_ruby_base_group,
	DisplayRole_ruby_text_group
};

/*
enum
{
	BackgroundRepeat_repeat = 0,
	BackgroundRepeat_repeat_x,
	BackgroundRepeat_repeat_y,
	BackgroundRepeat_no_repeat,
};
*/

enum Visibility : unsigned char
{
	Visibility_visible = 0,
	Visibility_hidden,
	Visibility_collapse	// For tables
};

enum TextAlign : unsigned char
{
	TextAlign_left = 0,
	TextAlign_right,
	TextAlign_center,
	TextAlign_justify,

	TextAlign_String
};

enum StrokeLineCap : unsigned char
{
	StrokeLineCap_butt,
	StrokeLineCap_round,
	StrokeLineCap_square,
};

enum StrokeLineJoin : unsigned char
{
	StrokeLineJoin_miter,
	StrokeLineJoin_round,
	StrokeLineJoin_bevel,
};

enum FontStyle : unsigned char
{
	FontStyle_normal = 0,
	FontStyle_italic,
	FontStyle_oblique
};

/*
enum
{
	TextDecoration_none = 0,
	TextDecoration_underline,
	TextDecoration_overline,
	TextDecoration_lineThrough,
	TextDecoration_blink
};
*/

enum Position : unsigned char
{
	Position_static = 0,
	Position_relative,
	Position_absolute,
	Position_fixed,
};

enum ListStylePosition : unsigned char
{
	ListStylePosition_inside,
	ListStylePosition_outside,
};

enum //Float : unsigned char
{
	Float_left = 0,
	Float_right,

	Float_top,
	Float_bottom,

	Float_inside,
	Float_outside,
	Float_start,
	Float_end,
	Float_none
};

enum Clear : unsigned char
{
	Clear_none = 0,
	Clear_left,
	Clear_right,
	Clear_top,
	Clear_bottom,
	Clear_inside,
	Clear_outside,
	Clear_start,
	Clear_end,
	Clear_both
};

enum Direction : unsigned char
{
	Direction_ltr = 0,
	Direction_rtl,
};

enum TextAnchor : unsigned char
{
	TextAnchor_start = 0,
	TextAnchor_middle,
	TextAnchor_end
};

enum Overflow : unsigned char
{
	Overflow_visible = 0,
	Overflow_hidden,
	Overflow_scroll,
	Overflow_auto,
};

/*
enum
{
	BorderStyle_none = 0,
	BorderStyle_hidden,			// CSS3
	BorderStyle_dotted,
	BorderStyle_dashed,
	BorderStyle_solid,
	BorderStyle_double,
	BorderStyle_dot_dash,		// CSS3
	BorderStyle_dot_dot_dash,	// CSS3
	BorderStyle_wave,				// CSS3
	BorderStyle_groove,
	BorderStyle_ridge,
	BorderStyle_inset,
	BorderStyle_outset,
};
*/

enum PointerEvents : unsigned char
{
	PointerEvents_visiblePainted = 0,
	PointerEvents_visibleFill,
	PointerEvents_visibleStroke,
	PointerEvents_visible,
	PointerEvents_painted,
	PointerEvents_fill,
	PointerEvents_stroke,
	PointerEvents_all,
	PointerEvents_none
};

enum FillRule : unsigned char
{
	FillRule_nonzero = 0,
	FillRule_evenodd
};

enum ClipRule : unsigned char
{
	ClipRule_nonzero = 0,
	ClipRule_evenodd
};

enum ColorInterpolation : unsigned char
{
	ColorInterpolation_auto = 0,
	ColorInterpolation_sRGB,
	ColorInterpolation_linearRGB,
};

enum Cursor : unsigned char
{
	Cursor_auto,
	Cursor_crosshair,
	Cursor_default,
	Cursor_pointer,
	Cursor_move,
	Cursor_e_resize,
	Cursor_ne_resize,
	Cursor_nw_resize,
	Cursor_n_resize,
	Cursor_se_resize,
	Cursor_sw_resize,
	Cursor_s_resize,
	Cursor_w_resize,
	Cursor_text,
	Cursor_wait,
	Cursor_help,
	Cursor_progress,
	Cursor_copy,
	Cursor_alias,
	Cursor_context_menu,
	Cursor_cell,
	Cursor_all_scroll,
	Cursor_col_resize,
	Cursor_row_resize,
	Cursor_no_drop,
	Cursor_not_allowed,
	Cursor_vertical_text,
};

enum RenderingIntent : unsigned char
{
	RenderingIntent_auto,
	RenderingIntent_perceptual,
	RenderingIntent_relative_colorimetric,
	RenderingIntent_saturation,
	RenderingIntent_absolute_colorimetric,
};

enum ShapeRendering : unsigned char
{
	ShapeRendering_auto,
	ShapeRendering_optimizeSpeed,
	ShapeRendering_crispEdges,
	ShapeRendering_geometricPrecision
};

enum ImageRendering : unsigned char
{
	ImageRendering_auto,
	ImageRendering_optimizeSpeed,
	ImageRendering_optimizeQuality
};

enum	// CSS Tables
{
	BorderCollapse_collapse,
	BorderCollapse_separate,
};

enum	// CSS Tables
{
	EmptyCells_show,
	EmptyCells_hide,
};

enum
{
	AllSpaceTreatment_preserve,
	AllSpaceTreatment_collapse,
};

enum
{
	LineFeedTreatment_auto,
	LineFeedTreatment_ignore,
	LineFeedTreatment_preserve,
	LineFeedTreatment_treat_as_space,
	LineFeedTreatment_treat_as_zero_width_space,
	LineFeedTreatment_ignore_if_after_linefeed,
};

enum
{
	WhiteSpaceTreatment_ignore,
	WhiteSpaceTreatment_preserve,
	WhiteSpaceTreatment_ignore_if_before_linefeed,
	WhiteSpaceTreatment_ignore_if_after_linefeed,
	WhiteSpaceTreatment_ignore_if_surrounding_linefeed,
};

enum
{
	WrapOption_wrap,
	WrapOption_no_wrap,
	WrapOption_soft_wrap,
	WrapOption_emergency,
};

enum	// Mozilla compliant XUL
{
	BoxOrient_horizontal,
	BoxOrient_vertical,
	BoxOrient_inline_axis,
	BoxOrient_block_axis,
};

enum	// Mozilla compliant XUL
{
	BoxAlign_start,
	BoxAlign_end,
	BoxAlign_center,
	BoxAlign_baseline,
	BoxAlign_stretch,
};

enum
{
	ListStyleType_normal,
	ListStyleType_none,

// glyph
	ListStyleType_box,
	ListStyleType_check,
	ListStyleType_circle,
	ListStyleType_diamond,
	ListStyleType_disc,
	ListStyleType_hyphen,
	ListStyleType_square,

// algorithmic
	ListStyleType_armenian,
	ListStyleType_cjk_ideographic,
	ListStyleType_ethiopic_numeric,
	ListStyleType_georgian,
	ListStyleType_hebrew,
	ListStyleType_japanese_formal,
	ListStyleType_japanese_informal,
	ListStyleType_lower_armenian,
	ListStyleType_lower_roman,
	ListStyleType_simp_chinese_formal,
	ListStyleType_simp_chinese_informal,
	ListStyleType_syriac,
	ListStyleType_tamil,
	ListStyleType_trad_chinese_formal,
	ListStyleType_trad_chinese_informal,
	ListStyleType_upper_armenian,
	ListStyleType_upper_roman,

// numeric
	ListStyleType_arabic_indic,
	ListStyleType_binary,
	ListStyleType_bengali,
	ListStyleType_cambodian,
	ListStyleType_decimal,
	ListStyleType_decimal_leading_zero,
	ListStyleType_devanagari,
	ListStyleType_gujarati,
	ListStyleType_gurmukhi,
	ListStyleType_kannada,
	ListStyleType_khmer,
	ListStyleType_lao,
	ListStyleType_lower_hexadecimal,
	ListStyleType_malayalam,
	ListStyleType_mongolian,
	ListStyleType_myanmar,
	ListStyleType_octal,
	ListStyleType_oriya,
	ListStyleType_persian,
	ListStyleType_telugu,
	ListStyleType_tibetan,
	ListStyleType_thai,
	ListStyleType_upper_hexadecimal,
	ListStyleType_urdu,

// alphabetic
	ListStyleType_afar,
	ListStyleType_amharic,
	ListStyleType_amharic_abegede,
	ListStyleType_cjk_earthly_branch,
	ListStyleType_cjk_heavenly_stem,
	ListStyleType_ethiopic,
	ListStyleType_ethiopic_abegede,
	ListStyleType_ethiopic_abegede_am_et,
	ListStyleType_ethiopic_abegede_gez,
	ListStyleType_ethiopic_abegede_ti_er,
	ListStyleType_ethiopic_abegede_ti_et,
	ListStyleType_ethiopic_halehame_aa_er,
	ListStyleType_ethiopic_halehame_aa_et,
	ListStyleType_ethiopic_halehame_am_et,
	ListStyleType_ethiopic_halehame_gez,
	ListStyleType_ethiopic_halehame_om_et,
	ListStyleType_ethiopic_halehame_sid_et,
	ListStyleType_ethiopic_halehame_so_et,
	ListStyleType_ethiopic_halehame_ti_er,
	ListStyleType_ethiopic_halehame_ti_et,
	ListStyleType_ethiopic_halehame_tig,
	ListStyleType_hangul,
	ListStyleType_hangul_consonant,
	ListStyleType_hiragana,
	ListStyleType_hiragana_iroha,
	ListStyleType_katakana,
	ListStyleType_katakana_iroha,
	ListStyleType_lower_alpha,
	ListStyleType_lower_greek,
	ListStyleType_lower_norwegian,
	ListStyleType_lower_latin,
	ListStyleType_oromo,
	ListStyleType_sidama,
	ListStyleType_somali,
	ListStyleType_tigre,
	ListStyleType_tigrinya_er,
	ListStyleType_tigrinya_er_abegede,
	ListStyleType_tigrinya_et,
	ListStyleType_tigrinya_et_abegede,
	ListStyleType_upper_alpha,
	ListStyleType_upper_greek,
	ListStyleType_upper_norwegian,
	ListStyleType_upper_latin,

// symbolic
	ListStyleType_asterisks,
	ListStyleType_footnotes,
};

//class PSVGElement;
class CATAttr;
class CHTMFlowBlockContext;
class CHTMBoxItem;
class CHTMBlockBox;
class CHTMInlineBox;
class CHTMElementBox;
class CMarkupBox;
class CCSSStackingContext;
class CHTMLWindow;

class CImage;

#if 0	// TODO, had this
// TODO: ??? Have same class for binary and htc behaviors ??
class CPBehavior
{
public:
//	CComQIPtr<ILElementBehaviorFactory> m_factory;
	CComPtr<ILElementBehaviorView> m_p;

	CComPtr<ILDOMElement> m_elementDef;

	StringW* m_url;

	//CComPtr<ILHTMLDocument> m_htcDocument;

	CTOR CPBehavior()
	{
	}

	~CPBehavior()
	{
#ifdef _DEBUG
		m_p.p->AddRef();
		int refcount = m_p.p->Release();
#endif

		m_p.Release();
	}
};
#endif

#if 0	// TODO, had this
class CLElementBehaviorViewSite :
	public CComObjectRootEx<CComSingleThreadModel>,

	public ILElementBehaviorViewSite,
	public IHTMLPaintSite
{
public:
	CLElementBehaviorViewSite()
	{
		m_pPElement = NULL;
	}

	//CComQIPtr<ILDOMElement> m_element;
	CPElementBase* m_pPElement;

	CHTMLWindow* m_pWindow;

BEGIN_COM_MAP(CLElementBehaviorViewSite)
	COM_INTERFACE_ENTRY(ILElementBehaviorViewSite)
	COM_INTERFACE_ENTRY(IHTMLPaintSite)
END_COM_MAP()

public:
// ILElementBehaviorViewSite
	STDMETHOD(GetDocumentView)(/*[out,retval]*/ IUnknown* *pVal);
//	STDMETHOD(GetView)(/*[out,retval]*/ ILDOMAbstractView* *pVal);
#if 0
	STDMETHOD(GetWindow)(/*[out,retval]*/ ILHTMLWindow* *pVal);
#endif
	STDMETHOD(GetViewNode)(/*[out,retval]*/ ILViewNode** pVal);
	STDMETHOD(GetElement)(ILDOMElement** ppElement);

// IHTMLPaintSite
     virtual HRESULT STDMETHODCALLTYPE InvalidatePainterInfo( void)
	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE InvalidateRect(
         /* [in] */ RECT *prcInvalid);

     virtual HRESULT STDMETHODCALLTYPE InvalidateRegion(
         /* [in] */ HRGN rgnInvalid)
	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE GetDrawInfo(
         /* [in] */ LONG lFlags,
         /* [out] */ HTML_PAINT_DRAW_INFO *pDrawInfo)
	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE TransformGlobalToLocal(
         /* [in] */ POINT ptGlobal,
         /* [out] */ POINT *pptLocal)
	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE TransformLocalToGlobal(
         /* [in] */ POINT ptLocal,
         /* [out] */ POINT *pptGlobal)
	  {
		  return E_NOTIMPL;
	  }

     virtual HRESULT STDMETHODCALLTYPE GetHitTestCookie(
         /* [out] */ LONG *plCookie)
	  {
		  return E_NOTIMPL;
	  }
};
#endif

class FontDef;
class CSSStyleDeclaration;
class CSSComputedStyleDeclaration;

class PseudoElement;

/*
class CSelector;

class CStyleDeclarationMatch
{
public:
	CStyleDeclarationMatch()
	{
		//m_specificity = 0;
		m_selector = NULL;
		m_style = NULL;
	}

	DWORD GetSpecificity();

	//DWORD m_specificity;
	CSelector* m_selector;
	CLCSSStyleDeclaration* m_style;
};
*/
class WEBEXT CSVGColor
{
public:
	CTOR CSVGColor()
	{
		m_iccColorProfile = nullptr;
	}

	String m_iccColorProfile;
	vector<double> m_iccColors;
	uint8 m_type;
	uint8 m_rgbColor[3];

	void Empty()
	{
		m_iccColorProfile = nullptr;
		m_iccColors.clear();
	}

	CSVGColor& operator = (CSVGColor& other)
	{
		m_type = other.m_type;
		m_rgbColor[0] = other.m_rgbColor[0];
		m_rgbColor[1] = other.m_rgbColor[1];
		m_rgbColor[2] = other.m_rgbColor[2];
		ASSERT(0);
#if 0
		m_iccColors.Copy(other.m_iccColors);
#endif

		return *this;
	}
};

class WEBEXT CSVGPaint : public CSVGColor
{
public:
	CTOR CSVGPaint()
	{
		m_uri = nullptr;
	}

	void Empty()
	{
		CSVGColor::Empty();
		m_uri = nullptr;
	}

	CSVGPaint& operator = (CSVGPaint& other)
	{
		m_type = other.m_type;
		m_rgbColor[0] = other.m_rgbColor[0];
		m_rgbColor[1] = other.m_rgbColor[1];
		m_rgbColor[2] = other.m_rgbColor[2];
		m_iccColors = other.m_iccColors;
		m_uri = other.m_uri;

		return *this;
	}

	String m_uri;
};

class WEBEXT PEntityReference :
	public PNode
{
};

class WEBEXT CounterDef
{
public:
	CTOR CounterDef()
	{
		m_number = 0;
	}

//	/*std::*/ wstring m_identifier;	// Try to use a pointer to the string ?
	System::StringW* m_identifier;
	int m_number;
};

class Counter
{
public:
//	std::wstring m_identifier;
	System::StringW* m_identifier;
//	std::vector<int> m_value;
	vector<int, __gc_allocator> m_value;
};

class CSSContext
{
public:
	CTOR CSSContext()
	{
		m_bInSelection = false;
	}

	bool m_bInSelection;

//	std::vector<CCounter*> m_counters;
	vector<Counter*> m_counters;

	void RemoveCounter(Counter* pCounter)
	{
		ASSERT(0);
		//m_counters.erase(&pCounter);
	}

	Counter* GetCounter(System::StringW* identifier)
	{
		for (unsigned int i = 0; i < m_counters.GetSize(); i++)
		{
			if (m_counters[i]->m_identifier->CompareNoCase(identifier) == 0)
			{
				return m_counters[i];
			}
		}

		Counter* pCounter = new Counter;
		pCounter->m_identifier = identifier;

		m_counters.Add(pCounter);

		return pCounter;
	}
};

class WEBEXT FontFamilyDef : public Object
{
public:
	CTOR FontFamilyDef();
	~FontFamilyDef();

//	Gui::FontFamily* m_pFamily;
	String m_pFamily;
	IDWriteFontFamily* m_dwriteFontFamily;

	ULONG AddRef()
	{
		++m_refcount;
		return m_refcount;
	}

	ULONG Release()
	{
		ASSERT(m_refcount > 0);
		if (--m_refcount == 0)
		{
			delete this;
			return 0;
		}
		return m_refcount;
	}

private:
	ULONG m_refcount;
};

class WEBEXT FontDef : public Object
{
public:
	CTOR FontDef();
	~FontDef();

#if 0
	Gui::Font* m_pFont;
#endif
	IDWriteFontFace* m_dwriteFontFace;
//	CFontDataFile* m_dataFile;
//	CPSVGFontElement* m_pSVGFontElement;	// SVG Font

	ULONG AddRef()
	{
		++m_refcount;
		return m_refcount;
	}

	ULONG Release()
	{
		ASSERT(m_refcount > 0);
		if (--m_refcount == 0)
		{
			delete this;
			return 0;
		}
		return m_refcount;
	}

private:
	ULONG m_refcount;
};

#if 0
class WEBEXT CFontDef
{
protected:
	int m_refcount;

#if _WINDOWS
//	HFONT m_hFont;
//	HFONT m_hFontHinted;
	LDraw::Font* m_gdipFont;
#endif

//	CHTMLWindow* m_pWindow; (Obtain through m_pFamily instead)

public:
//	CPSVGFontElement* m_pSVGFontElement;	// SVG Font

	/*
#if _WINDOWS
	CFontFamilyDef* m_pFamily;
#endif
	double m_size;
	int m_weight;
	int m_style;

	double m_descent;
	*/

	CFontDef();
	~CFontDef();

	int AddRef()
	{
		m_refcount++;
		return m_refcount;
	}

	LDraw::Font* GetGdipFont();
};
#endif

class BitSet
{
public:
	CTOR BitSet(int count)
	{
		int ndwords = ((count + 31) & ~31) / 32;
#ifndef __LERSTAD__
		m_data = new uint32[ndwords];
#endif
		std::memset(m_data, 0, ndwords*4);
	}

	~BitSet()
	{
		delete [] m_data;
	}

	uint32* m_data;

	bool TestBit(int n);
	void SetBit(int n, bool value);
};

class WEBEXT PElementBase :
	public PNode,
	public Style::ICSSElementResolver
{
public:
	CTOR PElementBase(Element* element);
	~PElementBase();

//	Node* m_pNode;	// ???

	int GetLevel();

// CLXUIWindowBase
	virtual void SetCapture();
	virtual void ReleaseCapture();
#if 0
	virtual void InvalidateRegion(LDraw::Region* pRgn);
#endif
// System::IEventListener
//	virtual void handleEvent(System::Event* evt);

// ICSSElementResolver
	virtual Style::ICSSElementResolver* get_rparent() override
	{
		return m_rparent;
	}

	virtual String get_typeName() override;
	virtual String get_namespaceURI() override;

	virtual String get_pseudoElementName() override
	{
		return m_pseudoElementName;
	}

	virtual void InvalidateBounds()
	{
	}

	virtual bool hasAttribute(StringIn name) override;
	virtual String getAttribute(StringIn name) override;
	virtual String get_id() override;
	virtual Style::ICSSElementResolver* get_prevSibling() override;
	virtual Style::ICSSElementResolver* get_nextSibling() override;

	virtual Style::IStyleDeclaration* get_inlineStyle(uint index) override;

	virtual bool IsInherited(Object* pProperty) override	// TODO not here
	{
		return dynamic_cast<CSSProperty*>(pProperty)->m_bInherited;
	}

	virtual bool IsValueInherit(Object* value) override	// TODO not here
	{
		return false;
	}

//
	virtual PElementBase* HitTestElement(gm::Matrix3d* matrix, gm::PointD pt);

	Element* m_pElement;

	EventTarget* m_eventTarget;	// often the same as m_pNode, but not always

	vector<PNode*> m_childList;
	vector<PNode*> m_rchildList;	// render children, entity references, shadow trees etc. taken into account
//	std::vector<CPNode*> m_pseudoChildList;	// Including pseudo elements

	void DeleteFlow();

//	CHTMFlowBlockContext* m_pC;
	int m_lastindex;
	uint8 m_bHasBlockChild;// : 2;	// -1=not yet set

	uint8 m_computedOutlineStyle;
	bool m_bCSSPropertiesValid : 1;
	bool m_bCSSPropertiesValid2 : 1;

//	CPPElement* m_shadowTree;
	PGenericElement* m_shadowTree;

//	CComObject<CLDOMDocumentFragment>* m_bindNode;
	Element* m_bindNode;
	PGenericElement* m_pBindNode;
	//CPPElement* m_pBindNode;
#if 0
	HRESULT BindBehavior(ILDOMElement* componentElement);
#endif

	vector<PNode*>& GetChildList();

//	CArray<CStyleDeclarationMatch*, CStyleDeclarationMatch*> m_declMatches;
	Style::CSSElementMatches* m_declMatches;

	String m_pseudoElementName;////	// If this is a pseudoElement
//	CArray<CPseudoElement*,CPseudoElement*> m_pseudoElements;	// Pseudo elements defined for this element
	enum
	{
		//PseudoElementIndex_Selection,
		PseudoElementIndex_Before,
		PseudoElementIndex_After,
		PseudoElementIndex_FirstLine,
		PseudoElementIndex_FirstLetter,
		PseudoElementIndex_Marker,
	};
	PElementBase* m_pseudoElements[5];

	// There can be more than one of selection pseudo elements
	//std::vector<CPElementBase*> m_selectionPseudoElements;

//	CPseudoElement* m_pBeforePseudoElement;
//	CPseudoElement* m_pMarkerPseudoElement;

	vector<CounterDef*> m_computedCounterIncrement;
	vector<CounterDef*> m_computedCounterReset;

	vector<Counter*> m_counters;

//	CHTMBlockBox*	m_pBox; // TODO Have this here instead of above

	vector<CHTMElementBox*> m_boxList;

#if 0
	CSSStackingContext* m_pStackingContext;	// stacking context that boxes generated by this element belong to
	CSSStackingContext* m_pLocalStackingContext;	// This element defined new local stacking context
#endif

	CSSComputedStyleDeclaration* m_pComputedStyle;

	CSSStyleDeclaration* m_pOverrideStyle;	// List of animated css attributes

	virtual gm::SizeD GetIntrinsicSize()
	{
		return gm::SizeD(-1, -1);
	}

	short m_customBlockTop;
	short m_customBlockBottom;

	//left,top,right,bottom
	uint8 m_computedBorderStyle[4];
	CRGBColor m_computedBorderColor[4];

	double m_computedOutlineWidth;

	virtual void Draw(CHTMRenderContext* pC);
	virtual void EndDraw(CHTMRenderContext* pC);
	virtual void OnRemoveBox(CHTMElementBox* pBox);
//	virtual void OnButtonDown(LDraw::PointD point, int nhit);

//	void DrawScrollBars(CHTMRenderContext* pC);

// TODO, manage to not have these here
	CHTMBlockBox*	m_pBox;

	double m_computedLeft;
	double m_computedTop;

	double m_computedBorderRadius[4][2];

	gm::SizeF m_contentSize;

	Gui::SolidColorBrush* m_pColorBrush;

	double m_curPosXOfLastStatic;	// for absolutely positioned element

	CMarkupBox* m_pStartTagBox;
	CMarkupBox* m_pEndTagBox;

/////////////////////////////////////////////////////
// Table (TODO, allocate a struct just for table elements)
	struct Column
	{
		double m_minWidth;
		double m_maxWidth;
		double m_width;
	};

//	long m_table_border;
//	long m_table_cellspacing;
//	long m_table_cellpadding;

	int m_ncolumns;
	Column* m_tableColumns;

/////////////////////////////////////////////////////
// Table-Row
	struct ColumnSpan
	{
		PElementBase* m_pCell;
		int m_row;
		int m_col;
		int m_colspan;
	};

	vector<PElementBase*> m_cells;
	vector<ColumnSpan> m_columnsSpan;	// for tr
	double m_minHeight;	// The rows MIN height, based on the cells it contains

	vector<PElementBase*> m_rows;	// for tbody (and flattened list of rows for table?)

	int InsertColumnSpan(PElementBase* pCell, int row, int col, int colspan);

/////////////////////////////////////////////////////
// Table-Cell	// TODO allocate a struct just for cell elements
	double m_minWidth;
	double m_maxWidth;
	double m_minContentWidth;
	double m_maxContentWidth;

//	double m_heightLeft;

	int m_rowspan;
	int m_colspan;
	int m_columnIndex;

	int m_nrow;
//

	Gui::Brush* GetColorBrush();
	FontDef* GetFont();

//	CHTMBlockBox* CreateBlockBox();
	CHTMBlockBox* CreateAnonymousBlockBox();
//	CHTMInlineBox* CreateInlineBox();
	CHTMInlineBox* CreateAnonymousInlineBox();

#if 0//WIN32
	void RenderBehavior(UI::Graphics* pGraphics);
#endif

	virtual void CalculateDimensions(CHTMCalcContext* pC);

#if 0//WIN32
	virtual void PlaceControls(MSWindows::HWND hWndParent, CHTMFlowBlockContext* pC);
#endif
	virtual void CreateControls(CHTMContext* pC);

// Interface to boxes (Moved to ILBoxHandler)
//	virtual void OnRemoveBox(CHTMElementBox* pBox);

////////////////////////////////

	void Adjust(CHTMLineBox* pBox);

	void DoScroll(CHTMRenderContext* pC);

#if 0	// ??
	void GetVisibleRect(CRect& rcPos, CRect& rcClip);
#endif

	void DrawScrollBars(CHTMRenderContext* pC);

	virtual bool HasDistributableChildren();

	void AddBox(CHTMElementBox* pBox);
	void RemoveBox(CHTMElementBox* pBox);

	void RemoveBoxes();
	void RemoveChildBoxes();

	void RemoveBoxesAndChildren();

	virtual void RemoveBoxesAndChildren2();	// Called from parent

	void DistributeChildLinesInBlock(CHTMFlowBlockContext* pC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentwidth);

	void CalculateMinMaxDimensions();
	void CreateScrollBars(CHTMFlowBlockContext* pC);
	void CalculateChildrenDimensions(CHTMCalcContext* pC);

	void DistributeBoxChildren(CHTMFlowBlockContext* pParentC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentwidth);
	void DistributeTableChildren(CHTMFlowBlockContext* pParentC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentwidth);
	void DistributeBlockInsideChildren(CHTMFlowBlockContext* pC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentwidth);
	void DistributeChildBlocksVertically(CHTMFlowBlockContext* pC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentwidth);
	void DistributeChildLines(CHTMFlowBlockContext* pC, double parentwidth);

	virtual void DistributeInline(CHTMFlowContext* pParentC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentwidth);
	virtual void DistributeBlockChildren(CHTMFlowBlockContext* pC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentwidth);
	virtual void DistributeWithinBlock(CHTMFlowBlockContext* pC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentwidth);

	virtual void OnResetAnimVals()
	{
	}

	CHTMBlockBox* CreateBlockBox();
	CHTMInlineBox* CreateInlineBox();

	BitSet m_PropertyValid;
	BitSet m_PropertyDependantOnParent;

	void InvalidateCSSProperty(int nProperty);

// Cached CSS values
	double m_computedLineHeight;
	double m_computedFontSize;

	vector<FontFamilyDef*> m_computedFontFamily;
	vector<FontDef*> m_computedFont;
	short m_ncomputedFontFamily;

	unsigned m_computedListStyleType : 10;
	unsigned m_computedBackgroundRepeat : 2;
	unsigned m_computedListStylePosition : 1;
	unsigned m_computedAllSpaceTreatment : 1;

	unsigned m_computedLineFeedTreatment : 3;
	unsigned m_computedWhiteSpaceTreatment : 3;
	unsigned m_computedWrapOption : 2;

	unsigned m_computedDisplayModel : 3;
	unsigned m_computedDisplayRole : 5;

	unsigned m_computedFontStyle : 2;

	// 32bits
	unsigned m_computedTextAlign : 3;

	unsigned m_computedTextUnderlineMode : 1;
	unsigned m_computedTextUnderlineStyle : 4;
	unsigned m_computedTextOverlineMode : 1;
	unsigned m_computedTextOverlineStyle : 4;
	unsigned m_computedTextLineThroughMode : 1;
	unsigned m_computedTextLineThroughStyle : 4;

	unsigned m_computedDirection : 1;

	unsigned m_computedBorderCollapse : 1;	// CSS Tables
	unsigned m_computedEmptyCells : 1;	// CSS Tables

	unsigned m_computedBoxOrient	: 2;	// Mozilla compliant XUL
	unsigned m_computedBoxAlign	: 3;	// Mozilla compliant XUL

	unsigned m_computedStrokeLineCap : 2;	// SVG
	unsigned m_computedStrokeLineJoin : 2;	// SVG
	unsigned m_computedTextAnchor : 2;	// SVG

	// 32bits
	unsigned m_computedShapeRendering : 2;	// SVG
	unsigned m_computedImageRendering : 2;	// SVG
	unsigned m_computedColorInterpolation : 2;	// SVG
	unsigned m_computedColorInterpolationFilters : 2;	// SVG
	unsigned m_computedPointerEvents : 4;	// SVG
	unsigned m_computedFillRule : 1;	// SVG
	unsigned m_computedClipRule : 1;	// SVG
	unsigned m_computedRenderingIntent : 3;	// SVG
	unsigned m_computedEnableBackground : 1;	// SVG		// accumulate | new

	unsigned m_computedFloat : 4;
	unsigned m_computedClear : 4;
	unsigned m_computedPosition : 2;
	unsigned m_computedVisibility : 2;
	unsigned m_computedOverflowX : 2;
	unsigned m_computedOverflowY : 2;

	// Some pseudoclass states of this element
	unsigned m_bHover : 1;
	unsigned m_bActive : 1;
	unsigned m_bFocus : 1;
	unsigned m_bEnabled : 1;
	unsigned m_bChecked : 1;
	unsigned m_bIndeterminate : 1;

		//
	unsigned m_bHScroll : 1;
	unsigned m_bVScroll : 1;

	double m_computedTextUnderlineWidth;
	double m_computedTextOverlineWidth;
	double m_computedTextLineThroughWidth;
	CRGBColor m_computedTextUnderlineColor;
	CRGBColor m_computedTextOverlineColor;
	CRGBColor m_computedTextLineThroughColor;

	double m_computedBorderSpacing[2];	// CSS Tables

	System::StringW* m_computedContent;

// text-shadow / box-shadow property
	class Shadow
	{
	public:
		double m_offset[2];
		double m_blurRadius;
		CRGBColor m_color;
	};

	vector<Shadow> m_computedTextShadow;
	vector<Shadow> m_computedBoxShadow;

//
	String m_computedCursorUrl;
	uint8 m_computedCursor;

	HCURSOR m_hCursor;

	PElementBase* /*PSVGElement* */ m_pCursorUriElement;

	double m_computedBoxFlex;

	double m_computedKerning;
	double m_computedLetterSpacing;
	double m_computedWordSpacing;

	double m_computedStrokeMiterLimit;
	double m_computedStrokeDashOffset;
//	CComBSTR m_computedStrokeDashArray;
	vector<double> m_strokeDashValuesArray;

	double m_computedOpacity;

	CSSUnitType m_specifiedTextIndentUnit;
	double m_specifiedTextIndent;
	double m_computedTextIndent;

	//left,top,right,bottom
	double m_computedMargin[4];	// draw as transparent
	double m_computedBorderWidth[4];
	double m_computedPadding[4];

	CRGBColor m_computedBackgroundColor;

//	double m_computedBorderRadius[4][2];	// TODO have this here instead of above

	//CRGBColor m_computed

	double m_computedClip[4];

	String m_computedBackgroundImage;
	CImage* m_pBackgroundImage;

	double m_specifiedLeft;
	double m_specifiedTop;
	double m_specifiedRight;
	double m_specifiedBottom;

//	double m_computedLeft;
//	double m_computedTop;
	double m_computedRight;
	double m_computedBottom;
	double m_computedWidth;
	double m_computedHeight;

	double m_computedMinWidth;
	double m_computedMinHeight;
	double m_computedMaxWidth;
	double m_computedMaxHeight;

	short	m_computedFontWeight;
//	short m_computedFontStyle;

//	double m_specifiedWidth;	// -1 = auto, < -1 == - +1 %
//	double m_specifiedHeight;	// -1 = auto, < -1 == - +1 %

	int m_specifiedZIndex;
	int m_computedZIndex;

	CRGBColor m_computedColor;

	double m_computedStrokeWidth;
	double m_computedStrokeOpacity;
	double m_computedFillOpacity;

	/*
	BYTE m_computedStrokePaintType;
	BYTE m_computedFillPaintType;
	BYTE m_computedStrokeColor[3];
	BYTE m_computedFillColor[3];
	CComBSTR m_computedStrokeUri;
	CComBSTR m_computedFillUri;
	*/

	CSVGPaint m_computedFill;
	CSVGPaint m_computedStroke;

	String m_computedFilterUri;
	String m_computedMaskUri;
	String m_computedClipPathUri;
	String m_computedMarkerStartUri;
	String m_computedMarkerEndUri;
	String m_computedMarkerMidUri;

	double m_computedSolidOpacity;	// For solidColor elements
	//double m_computedSolidColor[3];
	CSVGColor m_computedSolidColor;

	double m_computedStopOpacity;	// For stop elements
	//double m_computedStopColor[3];
	CSVGColor m_computedStopColor;

	double m_computedFloodOpacity;	// For feFlood element
	//double m_computedFloodColor[3];
	CSVGColor m_computedFloodColor;

	//double m_computedLightingColor[3]; // For feSpecularLighting element
	CSVGColor m_computedLightingColor;

	CSSUnitType m_computedColorProfileType;
	String m_computedColorProfileValue;
	CColorProfile* m_pColorProfile;

	//BYTE GetPaint(ILDocumentStyle* documentStyle, int propertyIndex, BYTE clr[3], CPSVGElementImpl* *pUrlElement);
	uint8 GetSVGPaint(Style::IDocumentStyle* documentStyle, /*int propertyIndex, BOOL bIncludeOverride,*/ SVGPaint* paint, CSVGPaint* pPaint);
	uint8 GetSVGColor(Style::IDocumentStyle* documentStyle, /*int propertyIndex, BOOL bIncludeOverride,*/ SVGColor* color, CSVGColor* pColor);

//	CComPtr<ILCSSValue> GetSpecifiedPropertyValue(ILDocumentStyle* documentStyle, int propertyIndex, BOOL bIncludeOverride);

	void CalculateWidthsAndMarginsStatic(double parentContentWidth, double values[7]);

	virtual void ReferenceInvalid(PElementBase/*PSVGElement*/ * pPElement);

	void AddChildren(PElementBase* pElement);
	void BuildShadowTree(PElementBase* refElement);

	virtual void InsertedIntoDocument();
	virtual void RemovedFromDocument();

	virtual void BuildChildren();
	void BuildRenderChildrenInternal();

	virtual void BuildRenderChildren();
	virtual void BuildRenderableChildren()	// For SVG
	{
	}
	virtual void RemoveChildren();

	/*
//////////////////////
// ILBoxHandler
	virtual void Draw(CHTMRenderContext* pC);
	virtual void EndDraw(CHTMRenderContext* pC);
	virtual void OnRemoveBox(CHTMElementBox* pBox);
	*/

/////
	virtual void OnButtonDown(gm::PointD screenpt, gm::PointD point, int nhit);
	virtual void OnButtonUp(gm::PointD screenpt, gm::PointD point, int nhit);
	virtual void OnMouseMove(gm::PointD screenpt, gm::PointD point, int nhit);

	PElementBase* GetElementById(StringIn id);
	PElementBase* GetElementByTagNameNS(StringIn namespaceURI, StringIn tagName, bool bDeep = true);

	double ConvertCSSLength(CSSPrimitiveValue* cssprimitiveValue);
	double GetBorderWidth(CSSPrimitiveValue* cssprimitiveValue);
	CRGBColor GetComputedColorValue(CSSPrimitiveValue* cssvalue);

	virtual gm::RectD GetViewBox()	// Should be on PSVGElementImpl ??
	{
		// It can be called when there's no outer <svg> in an svg fragment
		//ASSERT(0);	// Should never be called on base class
		return gm::RectD(0,0,0,0);
	}

	virtual void RecalculateParentBounds();
	virtual void CalculateBoundsAndChildren();

#if 0
	virtual void OnInsertedChild(ILDOMNode* node);
	virtual void OnAttrChanged(ILDOMAttr* attr);
#endif

	/*public*/ void GetCSSPropertiesAndChildren();

	void CalculateComputedCSSProperty(CSSContext* pCSSContext, int propertyIndex, bool bIncludeOverride = false);
	void GetCSSProperties2(CSSContext* pCSSContext);
	virtual void GetCSSProperties(CSSContext* pCSSContext);
	void GetCSSPropertiesAndChildren(CSSContext* pCSSContext);

	virtual void SetValuesFromAttributes();

	virtual CSSValue* GetCachedComputedProperty(int propertyIndex);

	CATAttr* OverrideCSSProperty(const System::StringW& propertyName);
	void SetOverrideStyleToBase();

//	virtual void CalculateDimensions(CHTMCalcContext* pC) = 0;

#if 0
//
	CComObject<CLElementBehaviorViewSite>* m_pBehaviorViewSite;
	CArray<CPBehavior*,CPBehavior*> m_behaviors;
#endif

	void CreateBehaviors();

protected:

	virtual void CalculateComputedCSSPropertyCore(CSSContext* pCSSContext, int propertyIndex, bool bIncludeOverride = false);
};

class WEBEXT CPAnimationElementImpl : public PElementBase
{
public:
	CTOR CPAnimationElementImpl(Element* element) : PElementBase(element)
	{
		m_pAnimatedCSSAttr = NULL;
	}

	CATAttr* m_pAnimatedCSSAttr;

	virtual void SetValuesFromAttributes();
};

class PseudoElement :
	public PElementBase
{
public:
	CTOR PseudoElement(Element* element) : PElementBase(element)
	{
	}

	virtual void BuildChildren()
	{
	}
};

// Read-only style declaration

class CSSComputedStyleDeclaration :
	public Object,
	public ICSSStyleDeclaration
{
public:
	CTOR CSSComputedStyleDeclaration()
	{
		m_pPElement = nullptr;
	}

	~CSSComputedStyleDeclaration()
	{
	}

// ICSSStyleDeclaration
	String item(unsigned int index)
	{
		// TODO ??
		ASSERT(0);
		return nullptr;
	}
	unsigned int get_length() const
	{
		// TODO ??
		ASSERT(0);
		return 0;
	}

	String get_cssText()
	{
		// TODO ??
		ASSERT(0);
		return nullptr;
	}

	void set_cssText(StringIn newVal)
	{
		THROW(-1);	// Read-only
	}

	Style::CSSRule* get_parentRule()
	{
		return nullptr;
	}

	CSSValue* getPropertyCSSValue(StringIn propertyName)
	{
		if (m_pPElement)
		{
			int propertyIndex = GetCSSPropertyIndex(propertyName);
			return m_pPElement->GetCachedComputedProperty(propertyIndex);
		}

		// The element has been deleted
		raise(Exception(L"The element has been deleted"));
		return nullptr;
	}

	void setProperty(StringIn propertyName, StringIn value, StringIn priority)
	{
		raise(Exception(L"read only"));
	}

	String removeProperty(StringIn propertyName)
	{
		raise(Exception(L"read only"));
		return nullptr;
	}

	String getPropertyValue(StringIn propertyName)
	{
		if (m_pPElement)
		{
			int propertyIndex = GetCSSPropertyIndex(propertyName);
			// TODO, check propertyIndex ???
			CSSValue* cssvalue = m_pPElement->GetCachedComputedProperty(propertyIndex);

			return cssvalue->get_cssText();
		}

		// The element has been deleted
		raise(Exception(L"The element has been deleted"));
	}

	String getPropertyPriority(StringIn propertyName)
	{
		ASSERT(0);
		raise(Exception(L"not implemented"));
		return nullptr;
	}

public:

	PElementBase* m_pPElement;
};

}	// Web
}	// System

#endif	// Web_PElementBase_h
