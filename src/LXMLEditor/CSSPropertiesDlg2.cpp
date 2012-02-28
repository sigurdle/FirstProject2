// CSSPropertiesDlg.cpp : Implementation of CCSSPropertiesDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "CSSPropertiesDlg.h"

//#include "WebEditorApp.h"	// TODO remove
//#include "WebEditorFrame.h"	// TODO remove

#include "EXMLDocument.h"	// TODO remove
#include "EXMLViewGroup.h"	// TODO remove

void DrawPopupArrow(HDC hDC, int midx, int topy, int size)
{
	CDCHandle dc(hDC);

	CBrush brush;
	brush.CreateSolidBrush(GetSysColor(COLOR_3DDKSHADOW));

	HPEN hOldPen = dc.SelectPen((HPEN)GetStockObject(NULL_PEN));
	HBRUSH hOldBrush = dc.SelectBrush(brush);

	POINT pt[3] =
	{
		midx-size, topy,
		midx+size, topy,
		midx, topy+size,
	};

	dc.Polygon(pt, 3);

	dc.SelectPen(hOldPen);
	dc.SelectBrush(hOldBrush);
}

#if 0
LRESULT CALLBACK EditNumberWndProc(
  HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
	switch (uMsg)
	{
	case WM_NCCREATE:
		{
			CEditNumberWnd* p = new CEditNumberWnd;
			SetProp(hwnd, "implementation", (HANDLE)p);
			p->SubclassWindow(hwnd);

			return TRUE;
		}
		break;

		/*
	case WM_NCDESTROY:
		{
		//	CEditNumberWnd* p = (CEditNumberWnd*)GetProp(hwnd, "implementation");
		//	p->Detach();
		}
		break;
		*/

		/*
	default:
		{
			CEditNumberWnd* p = (CEditNumberWnd*)GetProp(hwnd, "implementation");
			return p->ProcessWindowMessage(hwnd, WindowProc(uMsg, wParam, lParam);
		}
		*/
	}
	MessageBeep(-1);
	return 0;
};
#endif

#include "CSSProperty.h"

static WCHAR* CSSCategories[] =
{
	L"General",
	L"Text",
	L"Background",
	L"Border",
	L"List",
	L"Position",
	L"SVG-General",
	L"SVG-Stroke",
	L"SVG-Fill",
	L"SVG-Text",
};

enum
{
	Cat_General = 0,
	Cat_Text,
	Cat_Background,
	Cat_Border,
	Cat_List,
	Cat_Position,

	Cat_SVG,
	Cat_SVGStroke,
	Cat_SVGFill,
	Cat_SVGText,
};

static WCHAR* BorderStyleEnum = L"none|hidden|dotted|dashed|solid|double|dot-dash|dot-dot-dash|wave|groove|ridge|inset|outset";

CSSProperty CSSProperties[] =
{
	{L"alignment-baseline",					Cat_Text, FALSE,	L"auto", TYPE_ENUM(L"auto|baseline|before-edge|text-before-edge|middle|central|after-edge|text-after-edge|ideographic|alphabetic|hanging|mathematical")},

	{L"background",							Cat_Background, NULL, },	// shorthand
	{L"background-attachment",				Cat_Background, FALSE,	L"scroll", TYPE_ENUM(L"scroll|fixed") },
	{L"background-color",					Cat_Background, FALSE,	L"transparent", TYPE_COLOR() },
	{L"background-fill",						Cat_SVG, FALSE,	L"none"/*, TYPE_COLOR()*/ },
	{L"background-image",					Cat_Background, FALSE,	L"none", TYPE_URI() },
	{L"background-position",				Cat_Background, FALSE,	L"0% 0%"},
	{L"background-repeat",					Cat_Background, FALSE,	L"repeat", TYPE_ENUM(L"repeat|repeat-x|repeat-y|no-repeat")},
	{L"baseline-shift",						Cat_Text, FALSE,	L"baseline"},
	{L"border",									Cat_Border, 0, NULL, }, // shorthand
	{L"border-bottom",						Cat_Border, 0, NULL, }, // shorthand
	{L"border-bottom-color",				Cat_Border, FALSE,	NULL, TYPE_COLOR()},
	{L"border-bottom-style",				Cat_Border, FALSE,	L"none", TYPE_ENUM(BorderStyleEnum) },
	{L"border-bottom-width",				Cat_Border, FALSE,	L"0", CSSType_Length},
	{L"border-collapse",						Cat_General, TRUE,	L"separate", TYPE_ENUM(L"collapse|separate")},
	{L"border-color",							Cat_Border, 0,	NULL, },	// shorthand
	{L"border-left",							Cat_Border, 0, NULL, }, // shorthand
	{L"border-left-color",					Cat_Border, FALSE,	NULL, TYPE_COLOR()},
	{L"border-left-style",					Cat_Border, FALSE,	L"none", TYPE_ENUM(BorderStyleEnum)},
	{L"border-left-width",					Cat_Border, FALSE,	L"0", TYPE_LENGTH() },
	{L"border-right",							Cat_Border, 0, NULL, }, // shorthand
	{L"border-right-color",					Cat_Border, FALSE,	NULL, TYPE_COLOR()},
	{L"border-right-style",					Cat_Border, FALSE,	L"none", TYPE_ENUM(BorderStyleEnum)},
	{L"border-right-width",					Cat_Border, FALSE,	L"0", TYPE_LENGTH()},
	{L"border-spacing",						Cat_General, TRUE,	L"0", TYPE_LENGTH()},
	{L"border-style",							Cat_Border, 0,	NULL, },	// shorthand 
	{L"border-top",							Cat_Border, 0, NULL, }, // shorthand
	{L"border-top-color",					Cat_Border, FALSE,	NULL, TYPE_COLOR()},
	{L"border-top-style",					Cat_Border, FALSE,	L"none", TYPE_ENUM(BorderStyleEnum)},
	{L"border-top-width",					Cat_Border, FALSE,	L"0", TYPE_LENGTH()},
	{L"border-width",							Cat_Border, 0,	NULL,	},	// shorthand
	{L"bottom",									Cat_Position, FALSE,	L"auto", TYPE_LENGTH()},

	{L"clear",									Cat_Position, FALSE,	L"none", TYPE_ENUM(L"none|left|right|top|bottom|inside|outside|start|end|both")},
	{L"clip",									0, FALSE,	L"auto"},
	{L"clip-path",								Cat_SVG, FALSE,	L"none"},
	{L"clip-rule",								Cat_SVG, TRUE,		L"nonzero", TYPE_ENUM_IMAGE(L"nonzero|evenodd", IDB_FILLRULE)},
	{L"color",									Cat_Text, TRUE,	L"black", TYPE_COLOR() },// ?
	{L"color-interpolation",				Cat_SVG, TRUE,		L"sRGB", TYPE_ENUM(L"auto|sRGB|linearRGB") },
	{L"color-interpolation-filters",		Cat_SVG, TRUE,		L"linearRGB", TYPE_ENUM(L"auto|sRGB|linearRGB") },
	{L"color-profile",						Cat_SVG, TRUE, L"auto"},
	{L"color-rendering",						Cat_SVG, TRUE, L"auto", TYPE_ENUM(L"auto|optimizeSpeed|optimizeQuality")},
	{L"cursor",									0, TRUE, L"auto"},

	{L"direction",								Cat_Text, TRUE, L"ltr", TYPE_ENUM(L"ltr|rtl|inherit")},
	{L"display",								0, FALSE, L"inline", TYPE_ENUM(L"inline|block|list-item|run-in|compact|marker|table|inline-table|table-row-group|table-header-group|table-footer-group|table-row|table-column-group|table-column|table-cell|table-caption|none") },
	{L"dominant-baseline",					Cat_Text, FALSE, L"auto", TYPE_ENUM(L"auto|use-script|no-change|reset-size|ideographic|alphabetic|hanging|mathematical|central|middle|text-after-edge|text-before-edge")},

	{L"empty-cells",							Cat_General, TRUE,	L"show", TYPE_ENUM(L"show|hide")},
	{L"enable-background",					Cat_SVG, FALSE, L"accumulate"},

	{L"fill",									Cat_SVGFill, TRUE, L"#000000"},
	{L"fill-opacity",							Cat_SVGFill, TRUE, L"1", TYPE_NUMBER(0, 1, 100) },	// ?
	{L"fill-rule",								Cat_SVGFill, TRUE, L"nonzero", TYPE_ENUM_IMAGE(L"nonzero|evenodd", IDB_FILLRULE) },
	{L"filter",									Cat_SVG, FALSE, L"none"},
	{L"float",									Cat_Position, FALSE,	L"none", TYPE_ENUM(L"left|right|top|bottom|inside|outside|start|end|none")},
	{L"flood-color",							Cat_SVG, FALSE, L"black"},
	{L"flood-opacity",						Cat_SVG, FALSE, L"1"},
	{L"font",									Cat_Text, TRUE, L""},
	{L"font-family",							Cat_Text, TRUE, L"Times New Roman"/*, TYPE_STRING()*/},
	{L"font-size",								Cat_Text, TRUE, L"16"},
	{L"font-size-adjust",					Cat_Text, TRUE, L""},
	{L"font-stretch",							Cat_Text, TRUE,  L""},
	{L"font-style",							Cat_Text, TRUE, L"normal", TYPE_ENUM(L"normal|italic|oblique")},
	{L"font-variant",							Cat_Text, TRUE, L""},
	{L"font-weight",							Cat_Text, TRUE, L"normal", TYPE_ENUM(L"normal|bold||100|200|300|400|500|600|700|800|900||bolder|lighter")},

	{L"glyph-orientation-horizontal",	Cat_SVG, TRUE, L""},
	{L"glyph-orientation-vertical",		Cat_SVG, TRUE, L""},

	{L"height",									Cat_Position, FALSE, L"auto", TYPE_LENGTH() },

	{L"image-rendering",						Cat_SVG, TRUE, L""},

	{L"kerning",								Cat_Text, TRUE, L"auto", TYPE_LENGTH()},

	{L"left",									Cat_Position, FALSE,	L"auto", TYPE_LENGTH() },
	{L"letter-spacing",						Cat_Text, TRUE, L"normal", TYPE_LENGTH()},
	{L"lighting-color",						Cat_SVG, FALSE, L"white"},
	{L"line-height",							Cat_Text, TRUE,	L"normal", TYPE_LENGTH() },

	{L"margin",									Cat_Border, FALSE,	NULL}, // shorthand
	{L"margin-bottom",						Cat_Border, FALSE,	L"0"},
	{L"margin-left",							Cat_Border, FALSE,	L"0"},
	{L"margin-right",							Cat_Border, FALSE,	L"0"},
	{L"margin-top",							Cat_Border, FALSE,	L"0"},
	{L"marker",									Cat_SVG, FALSE, L""},	// ?
	{L"marker-end",							Cat_SVG, TRUE, L"none"},	// ?
	{L"marker-mid",							Cat_SVG, TRUE, L"none"},	// ?
	{L"marker-start",							Cat_SVG, TRUE, L"none"},	// ?
	{L"mask",									Cat_SVG, FALSE, L"none"},

	{L"opacity",								Cat_SVG, FALSE, L"1", TYPE_NUMBER(0, 1, 100) },
	{L"overflow",								Cat_General, FALSE, L"visible"/*see prose*/, TYPE_ENUM(L"visible|hidden|scroll|auto")},

	{L"padding",								Cat_Border, FALSE,	NULL},	// shorthand
	{L"padding-bottom",						Cat_Border, FALSE,	L"0"},
	{L"padding-left",							Cat_Border, FALSE,	L"0"},
	{L"padding-right",						Cat_Border, FALSE,	L"0"},
	{L"padding-top",							Cat_Border, FALSE,	L"0"},
	{L"pointer-events",						Cat_SVG, TRUE, L"visiblePainted", TYPE_ENUM(L"none|visiblePainted|visibleFill|visibleStroke|visible|painted|fill|stroke|all") },
	{L"position",								Cat_Position, FALSE,	L"static", TYPE_ENUM(L"static|relative|absolute|fixed")},

	{L"right",									Cat_Position, FALSE,	L"auto", TYPE_LENGTH() },

	{L"shape-rendering",						Cat_SVG, TRUE, L"auto", TYPE_ENUM(L"auto|optimizeSpeed|crispEdges|geometricPrecision")},
	{L"solid-color",							Cat_SVG, FALSE, L"black", TYPE_SVGCOLOR() },
	{L"solid-opacity",						Cat_SVG, FALSE, L"1", TYPE_NUMBER(0, 1, 100) },
	{L"stop-color",							Cat_SVG, FALSE, L"black", TYPE_SVGCOLOR()},
	{L"stop-opacity",							Cat_SVG, FALSE, L"1", TYPE_NUMBER(0, 1, 100) },
	{L"stroke",									Cat_SVGStroke, TRUE, L"none"},// ?
	{L"stroke-dasharray",					Cat_SVGStroke, TRUE, L"none"},
	{L"stroke-dashoffset",					Cat_SVGStroke, TRUE, L"0", TYPE_LENGTH()},
	{L"stroke-linecap",						Cat_SVGStroke, TRUE, L"butt", TYPE_ENUM_IMAGE(L"butt|round|square", IDB_STROKECAP) },
	{L"stroke-linejoin",						Cat_SVGStroke, TRUE, L"miter", TYPE_ENUM_IMAGE(L"miter|round|bevel", IDB_STROKEJOIN) },
	{L"stroke-miterlimit",					Cat_SVGStroke, TRUE, L"4", CSSType_Number},
	{L"stroke-opacity",						Cat_SVGStroke, TRUE, L"1", TYPE_NUMBER(0, 1, 100) },
	{L"stroke-width",							Cat_SVGStroke, TRUE, L"1", TYPE_LENGTH() },

	{L"text-align",							Cat_Text, TRUE, L"left", TYPE_ENUM_IMAGE(L"left|center|right|justify", IDB_TEXTALIGN) },
	{L"text-anchor",							Cat_SVGText, TRUE, L"start", TYPE_ENUM(L"start|middle|end") },
	{L"text-decoration",						Cat_Text, FALSE, L"none"},
	{L"text-indent",							Cat_Text, TRUE, L"0px", TYPE_LENGTH() },
	{L"text-rendering",						Cat_Text, TRUE, L"auto", TYPE_ENUM(L"auto|optimizeSpeed|optimizeLegibility|geometricPrecision") },
	{L"text-shadow",							Cat_Text, FALSE, L"none"},
	{L"top",										Cat_Position, FALSE,	L"auto", TYPE_LENGTH()},

	{L"unicode-bidi",							Cat_SVGText, FALSE, L"normal", TYPE_ENUM(L"normal|embed|bidi-override|inherit")},

	{L"vertical-align",						Cat_Text, FALSE, L"baseline", TYPE_ENUM(L"baseline|sub|super|top|text-top|middle|bottom|text-bottom")},
	{L"visibility",							0, FALSE, L"visible", TYPE_ENUM(L"visible|hidden|collapse") },

	{L"width",									Cat_Position, FALSE, L"auto", TYPE_LENGTH() },
	{L"word-spacing",							Cat_Text, TRUE, L"normal", TYPE_LENGTH()},
	{L"writing-mode",							Cat_SVGText, TRUE, L"lr-tb", TYPE_ENUM(L"lr-tb|rl-tb|tb-rl|lr|rl|tb|inherit")},
	{L"z-index",								Cat_Position, FALSE, L"auto"},
};

#define MAX_PROPERTIES (sizeof(CSSProperties)/sizeof(CSSProperty))

int g_nCSSProperties = MAX_PROPERTIES;

int GetCSSPropertyIndex(const WCHAR* propertyName)
{
#ifdef _DEBUG
//#if 0
// Assert that the properties are sorted
	for (int i = 1; i < MAX_PROPERTIES; i++)
	{
		ASSERT(wcscmp(CSSProperties[i-1].m_name, CSSProperties[i].m_name) < 0);
	}
//#endif
#endif

	int min = 0;        // beginning of search range 
	int max = MAX_PROPERTIES;   // end of search range 
	
	int n = max / 2;
	while (min < max)
	{ 
		int cmp = wcscmp(CSSProperties[n].m_name, propertyName);
		if (cmp > 0)
			max = n;
		else if (cmp < 0)
			min = n+1;
		else
			return n;

		n = (min + max) / 2; 
	} 

//	ASSERT(0);
	return -1;
}

class CCSSItem : public C2Obj
{
public:
	int m_type;
};

/*
class CCSSCategory : public CCSSItem
{
public:
	CCSSCategory()
	{
		m_type = 1;
		//m_width = 0;
	}
	int m_category;
	//int m_width;
};
*/

class CCSSProperty : public CCSSItem
{
public:
	CCSSProperty()
	{
		m_type = 2;
		m_hImageList = NULL;
	}

	CSSProperty* m_pType;
	HIMAGELIST m_hImageList;
	CArray<_bstr_t,_bstr_t> m_enumStrings;
};

class CCSSValue : public CCSSItem
{
public:
	CCSSValue()
	{
		m_type = 3;
	}
};

/////////////////////////////////////////////////////////////////////////////

#if 0
class ATL_NO_VTABLE CCSSPropertyColor : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IEColor
{
public:
	CCSSPropertyColor()
	{
	}

	CComPtr<ILCSSPrimitiveValue> m_cssvalue;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCSSPropertyColor)
	COM_INTERFACE_ENTRY(IEColor)
END_COM_MAP()

public:
	STDMETHOD(get_red)(long *pVal)
	{
		CComPtr<ILRGBColor> rgbColor;
		m_cssvalue->getRGBColorValue(&rgbColor);

		CComPtr<ILCSSPrimitiveValue> cssred;
		rgbColor->get_red(&cssred);

		double red;
		cssred->getFloatValue(CSS_NUMBER, &red);
		*pVal = (BYTE)red;

		return S_OK;
	}
	STDMETHOD(get_green)(long *pVal)
	{
		CComPtr<ILRGBColor> rgbColor;
		m_cssvalue->getRGBColorValue(&rgbColor);

		CComPtr<ILCSSPrimitiveValue> cssgreen;
		rgbColor->get_green(&cssgreen);

		double green;
		cssgreen->getFloatValue(CSS_NUMBER, &green);
		*pVal = (BYTE)green;

		return S_OK;
	}
	STDMETHOD(get_blue)(long *pVal)
	{
		CComPtr<ILRGBColor> rgbColor;
		m_cssvalue->getRGBColorValue(&rgbColor);

		CComPtr<ILCSSPrimitiveValue> cssblue;
		rgbColor->get_blue(&cssblue);

		double blue;
		cssblue->getFloatValue(CSS_NUMBER, &blue);
		*pVal = (BYTE)blue;

		return S_OK;
	}
	STDMETHOD(setRGBValue)(long red, long green, long blue)
	{
		/*
		CComPtr<ILCSSPrimitiveValue> cssred;
		m_rgbColor->get_red(&cssred);

		CComPtr<ILCSSPrimitiveValue> cssgreen;
		m_rgbColor->get_green(&cssgreen);

		CComPtr<ILCSSPrimitiveValue> cssblue;
		m_rgbColor->get_blue(&cssblue);

		cssred->setFloatValue(CSS_NUMBER, red);
		cssgreen->setFloatValue(CSS_NUMBER, green);
		cssblue->setFloatValue(CSS_NUMBER, blue);
		*/

		WCHAR buf[32];
		swprintf(buf, L"#%2.2X%2.2X%2.2X", red, green, blue);
		m_cssvalue->set_cssText(buf);

		return S_OK;
	}
};
#endif

/////////////////////////////////////////////////////////////////////////////
// CCSSPropertiesDlg

CCSSPropertiesDlg::CCSSPropertiesDlg() :
	m_wndEdit(NULL, this, 1),
	m_comboBoxWnd("COMBOBOX", this, 2)
{
	m_pTree = NULL;

	m_splitx = 110;

	m_hWndEdit = NULL;
	m_expandedBitmap = NULL;

//	m_bTabbedView = FALSE;

	m_activeCategory = 0;

	m_pActiveProperty = NULL;
}

int CCSSPropertiesDlg::FinalConstruct()
{
	HRESULT hr;

//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->FindMenu(IDR_CSSPROPERTIESDLG, &m_menu);

	hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
	if (FAILED(hr)) return hr;
	m_vert->put_direction(1);

	return S_OK;
}

void CCSSPropertiesDlg::FinalRelease()
{
}

LRESULT CCSSPropertiesDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	{
		WNDCLASS wc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = NULL;
		wc.hCursor = NULL;
		wc.hIcon = NULL;
		wc.hInstance = _Module.GetModuleInstance();
		wc.lpfnWndProc = EditNumberWndProc;
		wc.lpszClassName = "EditNumber";
		wc.lpszMenuName = NULL;
		wc.style = 0;

		RegisterClass(&wc);
	}
#endif

	m_expandedBitmap = LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_EXPANDED));

	m_pTree = new C2Obj;

	for (int i = 0; i < MAX_PROPERTIES; i++)
	{
		if (CSSProperties[i].m_category == m_category)
		{
			CCSSProperty* pProperty = new CCSSProperty;
			pProperty->m_name = CSSProperties[i].m_name;
			pProperty->m_pType = &CSSProperties[i];
			pProperty->m_itemHeight = 20+1;

			if (!wcscmp(pProperty->m_name, L"font-family"))
			{
				CCSSValue* pValue = new CCSSValue;
				pProperty->AddChildTail(pValue);
			}
			else if (!wcscmp(pProperty->m_name, L"stroke-dasharray"))
			{
				CCSSValue* pValue = new CCSSValue;
				pProperty->AddChildTail(pValue);
			}
			else if (!wcscmp(pProperty->m_name, L"clip"))
			{
				CCSSValue* pValue = new CCSSValue;
				pProperty->AddChildTail(pValue);
			}

			if (pProperty->m_pType->d.m_type == CSSType_Enum)
			{
				WCHAR* p = (BSTR)pProperty->m_pType->d.m_enums;

				while (*p)
				{
					TCHAR v[512];
					int n = 0;

					while (*p && *p != L'|')
					{
						v[n] = *p;
						n++;
						p++;
					}

					v[n] = 0;	// null-terminate

					pProperty->m_enumStrings.Add(v);

					if (*p)	// Skip |
						p++;
				}
			}

			if (CSSProperties[i].d.m_nResource)
			{
				pProperty->m_hImageList = ImageList_Create(18, 18, ILC_COLOR8 | ILC_MASK, 0, 10);

				HBITMAP hBitmap = LoadBitmap((HINSTANCE)_Module.GetResourceInstance(), MAKEINTRESOURCE(CSSProperties[i].d.m_nResource));
				if (hBitmap)
				{
					ImageList_AddMasked(pProperty->m_hImageList, hBitmap, RGB(192, 192, 192));

					DeleteObject(hBitmap);
				}
			}

			/*
			CCSSCategory* pCategory = NULL;
			UPOSITION pos = m_pTree->m_childList.GetHeadPosition();
			while (pos)
			{
				CCSSCategory* p = (CCSSCategory*)m_pTree->m_childList.GetNext(pos);
				if (p->m_category == pProperty->m_pType->m_category)
				{
					pCategory = p;
					break;
				}
			}

			if (pCategory == NULL)
			{
				pCategory = new CCSSCategory;
				pCategory->m_category = pProperty->m_pType->m_category;
				pCategory->m_name = CSSCategories[pCategory->m_category];
				pCategory->m_itemHeight = 16;
				m_pTree->AddChildTail(pCategory);
			}

			pCategory->AddChildTail(pProperty);
			*/

			m_pTree->AddChildTail(pProperty);
		}
	}

	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axvert.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<1, CCSSPropertiesDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	CComQIPtr<IUIActiveManager> uiManager = m_app;
	uiManager->AddEventHandler(this);

// register object for message filtering and idle updates
#if 0
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ASSERT(pLoop != NULL);
//	pLoop->AddIdleHandler(this);
	pLoop->AddMessageFilter(this);
#endif

	return 0;
}

LRESULT CCSSPropertiesDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
#endif

	CComQIPtr<IUIActiveManager> uiManager = m_app;
	uiManager->RemoveEventHandler(this);

	IDispEventImpl<1, CCSSPropertiesDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	if (m_expandedBitmap)
	{
		DeleteObject(m_expandedBitmap);
		m_expandedBitmap = NULL;
	}

	return 0;
}

LRESULT CCSSPropertiesDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	USES_CONVERSION;

	CPaintDC dc(m_hWnd);

	CRect client;
	GetClientRect(&client);

	long scrollposY; m_vert->get_pos(&scrollposY);

	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	LOGFONT lf;
	GetObject(hFont, sizeof(lf), &lf);
	lf.lfWeight = FW_BOLD;
	HFONT hBoldFont = CreateFontIndirect(&lf);

	HFONT hOldFont = dc.GetCurrentFont();

	dc.SetBkMode(TRANSPARENT);

	if (m_style && m_pTree)
	{
		/*
		if (m_bTabbedView)
		{
			int x = 0;
			int n = 0;

			UPOSITION pos = m_pTree->m_childList.GetHeadPosition();
			while (pos)
			{
				CCSSCategory* pCategory = (CCSSCategory*)m_pTree->m_childList.GetNext(pos);

				CRect rc(x, 0, x+pCategory->m_width+4, 18);
				dc.FillSolidRect(&rc, GetSysColor(COLOR_BTNFACE));
				if (n == m_activeCategory)
				{
					dc.Draw3dRect(&rc, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHILIGHT));
				}
				else
				{
					dc.Draw3dRect(&rc, GetSysColor(COLOR_3DLIGHT), GetSysColor(COLOR_3DSHADOW));
				}

				rc.InflateRect(-2, -2);
				dc.DrawText(pCategory->m_name, pCategory->m_name.length(), &rc, DT_SINGLELINE | DT_VCENTER);

				x += pCategory->m_width+4;
				n++;
			}
		}
		*/

		{
			if (dc.IntersectClipRect(m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom) > NULLREGION)
			{
#if 0
				CPen splitPen;
				splitPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_INACTIVECAPTION)/*RGB(60, 60, 60)*/);
#endif

				HPEN hOldPen = dc.GetCurrentPen();

				dc.SetViewportOrg(m_areaRect.left, m_areaRect.top -scrollposY);

				C2Obj* pParentItem;

				/*
				if (m_bTabbedView)
				{
					UPOSITION pos = m_pTree->m_childList.FindIndex(m_activeCategory);
					pParentItem = (C2Obj*)m_pTree->m_childList.GetAt(pos);
				}
				else
				*/
				{
					pParentItem = m_pTree;
				}

				UPOSITION pos = pParentItem->GetHeadPosition();
				int nextlevel = 0;

				int y = 0;

				while (pos)
				{
					int level = nextlevel;
					CCSSItem* pItem = (CCSSItem*)(C2Obj*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

					int x = level*14;

					CRect itemrect(x, y, m_areaRect.Width(), y+pItem->m_itemHeight);

					dc.FillSolidRect(&itemrect, GetSysColor(COLOR_BTNFACE));
					dc.SetTextColor(GetSysColor(COLOR_BTNTEXT));

					if (pItem->m_type == 1)
					{
						dc.SelectFont(hBoldFont);
					}
					else
					{
						dc.SelectFont(hFont);
					}

					dc.FillSolidRect(
						&CRect(itemrect.left, itemrect.bottom-1,
								itemrect.right, itemrect.bottom),
								(pItem->m_type == 1)? RGB(0, 0, 0): GetSysColor(COLOR_INACTIVECAPTION));

					/*
					dc.SelectPen(splitPen);

					dc.MoveTo(itemrect.left, itemrect.bottom-1);
					dc.LineTo(itemrect.right, itemrect.bottom-1);
					*/

					if (pItem->m_type == 2)
					{
						dc.FillSolidRect(m_splitx, itemrect.top, 1, itemrect.Height(), GetSysColor(COLOR_INACTIVECAPTION));
						/*
						dc.MoveTo(m_splitx, itemrect.top);
						dc.LineTo(m_splitx, itemrect.bottom);
						*/
					}

					if (pItem->HasChildren())
					{
						TransparentBlt(dc.m_hDC, x+2, y+2, 10, 14, m_expandedBitmap, pItem->m_expanded*10, 0, RGB(192, 192, 192));
						x += 12;
					}

					if (pItem->m_type == 1)
					{
						CRect namerect(x, y, m_areaRect.Width(), y+pItem->m_itemHeight-1);
						dc.DrawText(pItem->m_name, pItem->m_name.length(), &namerect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

						CSize size;
						dc.GetTextExtent(pItem->m_name, pItem->m_name.length(), &size);

						/*
						dc.FillSolidRect(
							&CRect(namerect.left+size.cx+2, namerect.top+namerect.Height()/2,
									namerect.right-2, namerect.top+namerect.Height()/2+1),
							RGB(0, 0, 0));
							*/

					//	dc.MoveTo(namerect.left+size.cx+2, namerect.top+namerect.Height()/2);
					//	dc.LineTo(namerect.right, itemrect.top+namerect.Height()/2);
					}
					else if (pItem->m_type == 2)
					{
						CCSSProperty* pProperty = (CCSSProperty*)pItem;

						CRect namerect(x, y, m_splitx-1, y+pItem->m_itemHeight-1);
						dc.DrawText(pItem->m_name, pItem->m_name.length(), &namerect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

						CRect valuerect(m_splitx+1, y, m_areaRect.Width(), y+pItem->m_itemHeight-1);

						if (pProperty->m_hImageList)
						{
							CComBSTR value;
							m_style->getPropertyValue(pProperty->m_pType->m_name, &value);

							dc.FillSolidRect(&valuerect, GetSysColor(COLOR_BTNFACE));

							int ncount = ImageList_GetImageCount(pProperty->m_hImageList);

							int ix = valuerect.left;
							int iy = valuerect.top;
							for (int i = 0; i < ncount; i++)
							{
								CRect rc(ix, iy, ix+20, iy+20);

								int o = 0;
								if (value.Length() &&
									!wcscmp(value, pProperty->m_enumStrings[i]))
								{
									dc.Draw3dRect(&rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));

									rc.InflateRect(-1, -1);
									dc.FillSolidRect(&rc, RGB(255, 255, 255));
									o++;
								}

								ImageList_Draw(pProperty->m_hImageList, i, dc.m_hDC, ix+1+o, iy+1+o, ILD_TRANSPARENT);

								ix += 18;
								ix += 2;
							}
						}
						else
						{
							switch (pProperty->m_pType->d.m_type)
							{
							case 0:
								{
									if (!wcscmp(pProperty->m_pType->m_name, L"clip"))
									{
										//if (!pItem->m_expanded)
										{
											CComPtr<ILCSSPrimitiveValue> cssvalue;
											m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);

											CRect valuerect(m_splitx+1, y, m_areaRect.Width(), y+pItem->m_itemHeight-1);

											CRect trect = valuerect;
											trect.InflateRect(-1,-1);

											LCSSUnitType unitType = (LCSSUnitType)0;

											if (cssvalue)
											{
												cssvalue->get_primitiveType(&unitType);
											}

											CUString str;

											if (unitType == CSS_IDENT)
											{
												str = "auto";
											}
											else if (unitType == CSS_RECT)
											{
												str = "rect";
											}

											if (str.GetLength())
											{
												dc.DrawText(str, str.GetLength(), &trect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
											}
										}
									}
									else if (!wcscmp(pProperty->m_pType->m_name, L"font-family"))
									{
										if (!pItem->m_expanded)
										{
											CComPtr<ILCSSValueList> cssvalue;
											m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);

											if (cssvalue != NULL)
											{
												long count;
												cssvalue->get_length(&count);

											// Draw first item only
												if (count > 0)
												{
													CComPtr<ILCSSPrimitiveValue> nvalue;
													cssvalue->item(0, (ILCSSValue**)&nvalue);

													CComBSTR value;
													nvalue->getStringValue(&value);

													CRect valuerect(m_splitx+1, y, m_areaRect.Width(), y+pItem->m_itemHeight-1);

													CRect trect = valuerect;
												//	trect.right -= 16;
													trect.InflateRect(-1,-1);

													dc.DrawText(_bstr_t(value), value.Length(), &trect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
												}
											}
										}
									}
									else if (!wcscmp(pProperty->m_pType->m_name, L"stroke-dasharray"))
									{
										if (!pItem->m_expanded)
										{
											CComPtr<ILCSSValueList> cssvalue;
											m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);

											CRect valuerect(m_splitx+1, y, m_areaRect.Width(), y+pItem->m_itemHeight-1);

											CRect trect = valuerect;
											trect.InflateRect(-1,-1);

											if (cssvalue != NULL)
											{
												long count;
												cssvalue->get_length(&count);

												CUString str;
												str.Format("%d values", count);

												dc.DrawText(str, str.GetLength(), &trect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
											}
											else
											{
												CUString str = "none";
												dc.DrawText(str, str.GetLength(), &trect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
											}
										}
									}
									else if (!wcscmp(pProperty->m_pType->m_name, L"font-size"))
									{
										// Draw combobox arrow
										{
											DrawPopupArrow(dc, valuerect.right-8, valuerect.top+(valuerect.Height()-4)/2, 4);
											dc.Draw3dRect(valuerect.right-16, valuerect.top+2, 2, valuerect.Height()-4, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
										}

										CRect trect = valuerect;
										trect.right -= 16;
										trect.InflateRect(-1,-1);

										{
											CComBSTR value;
											m_style->getPropertyValue(pProperty->m_pType->m_name, &value);

											if ((BSTR)value != NULL)
											{
												dc.FillSolidRect(&trect, RGB(255, 255, 255));

												dc.DrawText(_bstr_t(value), value.Length(), &trect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
											}
										}
									}
									else
									{
										CComBSTR value;
										m_style->getPropertyValue(pProperty->m_pType->m_name, &value);

										CRect trect = valuerect;

										if ((BSTR)value != NULL)
										{
											dc.FillSolidRect(&trect, RGB(255, 255, 255));
											dc.DrawText(_bstr_t(value), value.Length(), &trect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
										}
									}
								}
								break;

							case CSSType_Enum:
								{
									CRect rc = valuerect;

									//dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
									//rc.InflateRect(-1,-1);

									dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
									rc.InflateRect(-1,-1);

									CRect trect = rc;
									trect.right -= 16;

									dc.Draw3dRect(trect.right+1, trect.top+2, 2, trect.Height()-4, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));

									DrawPopupArrow(dc, valuerect.right-8, valuerect.top+(valuerect.Height()-4)/2, 4);
									/*
									POINT pt[3] =
									{
										valuerect.right-12, valuerect.top+(valuerect.Height()-4)/2,
										valuerect.right-4, valuerect.top+(valuerect.Height()-4)/2,
										valuerect.right-8, valuerect.top+(valuerect.Height()-4)/2+4,
									};

									HPEN hOldPen = dc.SelectPen((HPEN)GetStockObject(NULL_PEN));
									HBRUSH hOldBrush = dc.SelectBrush((HBRUSH)GetStockObject(BLACK_BRUSH));

									dc.Polygon(pt, 3);

									dc.SelectPen(hOldPen);
									dc.SelectBrush(hOldBrush);
									*/

									CComPtr<ILCSSPrimitiveValue> cssvalue;
									m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);
									if (cssvalue)
									{
										CComBSTR value;
										cssvalue->getStringValue(&value);

										if (value.Length())
										{
											dc.DrawText(_bstr_t(value), value.Length(), &trect, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS);
										}
									}
								}
								break;

							case CSSType_Uri:
								{
									CRect trect = valuerect;
									trect.right -= 16;

									CComPtr<ILCSSPrimitiveValue> cssvalue;
									m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);
									if (cssvalue)
									{
										CComBSTR value;
										cssvalue->getStringValue(&value);

										if (value.Length())
										{
											dc.DrawText(_bstr_t(value), value.Length(), &trect, DT_VCENTER | DT_SINGLELINE | DT_PATH_ELLIPSIS);
										}
									}

									CRect brect(trect.right, valuerect.top, valuerect.right, valuerect.bottom);
									dc.Draw3dRect(&brect, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
									dc.DrawText("...", 3, &brect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
								}
								break;

							default:
								{
									CComBSTR value;
									m_style->getPropertyValue(pProperty->m_pType->m_name, &value);

									CRect trect = valuerect;

									if ((BSTR)value != NULL)
									{
										dc.FillSolidRect(&trect, RGB(255, 255, 255));
										dc.DrawText(_bstr_t(value), value.Length(), &trect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
									}
								}
								break;
							}
						}
					}
					else if (pItem->m_type == 3)	// Value
					{
						CCSSProperty* pProperty = (CCSSProperty*)pItem->m_parent;

						if (!wcscmp(pProperty->m_pType->m_name, L"clip"))
						{
							long count = 4;

							pItem->m_itemHeight = count*18;

							CComPtr<ILCSSPrimitiveValue> cssvalue;
							m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);

							CComBSTR values[4];

							if (cssvalue)
							{
								LCSSUnitType unitType;
								cssvalue->get_primitiveType(&unitType);

								if (unitType == CSS_RECT)
								{
									CComPtr<ILCSSRect> rect;
									cssvalue->getRectValue(&rect);

									CComPtr<ILCSSPrimitiveValue> csstop;
									rect->get_top(&csstop);
									csstop->get_cssText(&values[0]);

									CComPtr<ILCSSPrimitiveValue> cssright;
									rect->get_right(&cssright);
									cssright->get_cssText(&values[1]);

									CComPtr<ILCSSPrimitiveValue> cssbottom;
									rect->get_bottom(&cssbottom);
									cssbottom->get_cssText(&values[2]);

									CComPtr<ILCSSPrimitiveValue> cssleft;
									rect->get_left(&cssleft);
									cssleft->get_cssText(&values[3]);
								}
							}

							TCHAR* name[4] =
							{
								_T("top"),
								_T("right"),
								_T("bottom"),
								_T("left")
							};

							int y2 = y;
							CRect valuerect(x+1, y2, m_areaRect.Width(), y2+18-1);

							for (int i = 0; i < 4; i++)
							{
								{
									CRect trect = valuerect;
									trect.right = trect.left + 40;
									trect.InflateRect(-1,-1);
									dc.DrawText(name[i], strlen(name[i]), &trect, DT_VCENTER | DT_SINGLELINE);
								}

								// Draw combobox arrow
								{
									DrawPopupArrow(dc, valuerect.right-8, valuerect.top+(valuerect.Height()-4)/2, 4);
									/*
									CBrush brush;
									brush.CreateSolidBrush(GetSysColor(COLOR_3DDKSHADOW));

									HPEN hOldPen = dc.SelectPen((HPEN)GetStockObject(NULL_PEN));
									HBRUSH hOldBrush = dc.SelectBrush(brush);

									POINT pt[3] =
									{
										valuerect.right-12, valuerect.top+(valuerect.Height()-4)/2,
										valuerect.right-4, valuerect.top+(valuerect.Height()-4)/2,
										valuerect.right-8, valuerect.top+(valuerect.Height()-4)/2+4,
									};

									dc.Polygon(pt, 3);

									dc.SelectPen(hOldPen);
									dc.SelectBrush(hOldBrush);
									*/

									dc.Draw3dRect(valuerect.right-16, valuerect.top+2, 2, valuerect.Height()-4, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
								}

								{
									CRect trect = valuerect;
									trect.left += 40;
									trect.right -= 16;

									dc.FillSolidRect(&trect, RGB(255, 255, 255));

									trect.InflateRect(-1,-1);

									dc.DrawText(_bstr_t(values[i]), values[i].Length(), &trect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
								}

								valuerect.OffsetRect(0, 18);
							}
						}
						else if (!wcscmp(pProperty->m_pType->m_name, L"font-family"))
						{
							CComPtr<ILCSSValueList> cssvalue;
							m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);

							long count = 0;

							if (cssvalue != NULL)
							{
								cssvalue->get_length(&count);
							}

							pItem->m_itemHeight = count*18+18;

							CRect valuerect(x+1, y, m_areaRect.Width(), y+pItem->m_itemHeight-1);

							dc.FillSolidRect(&valuerect, RGB(255, 255, 255));

							int y2 = y;

							for (int i = 0; i < count; i++)
							{
								CComPtr<ILCSSPrimitiveValue> nvalue;
								cssvalue->item(i, (ILCSSValue**)&nvalue);

								CComBSTR value;
								nvalue->getStringValue(&value);

								CRect valuerect(x+1, y2, m_areaRect.Width(), y2+18-1);

								CRect trect = valuerect;
								trect.right -= 16;
								trect.InflateRect(-1,-1);

								dc.DrawText(_bstr_t(value), value.Length(), &trect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

								y2 += 18;
							}
						}
						else if (!wcscmp(pProperty->m_pType->m_name, L"stroke-dasharray"))
						{
							CComPtr<ILCSSValueList> cssvalue;
							m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);

							long count = 0;

							if (cssvalue != NULL)
							{
								cssvalue->get_length(&count);
							}

							pItem->m_itemHeight = count*18+18;

							CRect valuerect(x+1, y, m_areaRect.Width(), y+pItem->m_itemHeight-1);

							//dc.FillSolidRect(&valuerect, RGB(255, 255, 255));

							int y2;
							int i;
/*
							y2 = y;
							for (i = 0; i <= count; i++)
							{
								CRect valuerect(x+1, y2, m_areaRect.Width(), y2+18-1);

								CRect trect = valuerect;
								trect.right = 32;
								trect.InflateRect(-1,-1);

								TCHAR* str;
								if (i & 1)
									str = _T("gap");
								else
									str = _T("dash");

								dc.FillSolidRect(&trect, RGB(255, 255, 255));
								dc.DrawText(str, strlen(str), &trect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

								y2 += 18;
							}
*/
							y2 = y;
							for (i = 0; i <= count; i++)
							{
								CRect valuerect(x+1, y2, m_areaRect.Width(), y2+18-1);

								{
									CRect trect = valuerect;
									trect.right = trect.left + 32;
									trect.InflateRect(-1,-1);

									TCHAR* str;
									if (i & 1)
										str = _T("gap");
									else
										str = _T("dash");

									dc.DrawText(str, strlen(str), &trect, DT_VCENTER | DT_SINGLELINE);
								}

								{
									CRect trect = valuerect;
									trect.left += 32;
									trect.right -= 16;

									dc.FillSolidRect(&trect, RGB(255, 255, 255));

									trect.InflateRect(-1,-1);

									if (i < count)
									{
										CComPtr<ILCSSPrimitiveValue> nvalue;
										cssvalue->item(i, (ILCSSValue**)&nvalue);

										CComBSTR value;
										nvalue->get_cssText(&value);
					
										dc.DrawText(_bstr_t(value), value.Length(), &trect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
									}
								}

								y2 += 18;
							}
						}
					}

					y += pItem->m_itemHeight;
				}

				dc.SelectPen(hOldPen);
			}
		}
	}

	dc.SelectFont(hOldFont);

	DeleteObject(hFont);
	DeleteObject(hBoldFont);

	return 0;
}

void CCSSPropertiesDlg::EndEdit()
{
	TCHAR buf[512];
	m_wndEdit.GetWindowText(buf, sizeof(buf));
	CComBSTR value = buf;

	CCSSItem* pItem = (CCSSItem*)m_pActiveProperty;//m_wndEdit.GetWindowLong(GWL_USERDATA);
	if (pItem->m_type == 2)
	{
		CCSSProperty* pProperty = (CCSSProperty*)pItem;

		CComBSTR oldvalue;
		m_style->getPropertyValue(pProperty->m_pType->m_name, &oldvalue);
		if (oldvalue.Length()==0) oldvalue = L"";

		if (wcscmp(oldvalue, value))
		{
			m_style->setProperty(pProperty->m_pType->m_name, value, NULL);

			Apply();
		}
	}
	else if (pItem->m_type == 3)
	{
		CCSSProperty* pProperty = (CCSSProperty*)pItem->m_parent;

		if (!wcscmp(pProperty->m_pType->m_name, L"font-family"))
		{
			CComPtr<ILCSSValueList> cssvalue;
			m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);
		}
	}

	m_wndEdit.DestroyWindow();
	m_hWndEdit = NULL;
}

LRESULT CCSSPropertiesDlg::OnEditKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//if (m_webElement)
	{
		if ((uMsg == WM_KILLFOCUS) ||
			(uMsg == WM_KEYDOWN && wParam == VK_RETURN))
		{
			EndEdit();

			//if (uMsg == WM_KEYDOWN)
				return 0;
		}
	}

	return m_wndEdit.DefWindowProc(uMsg, wParam, lParam);
}

LRESULT CCSSPropertiesDlg::OnSetNumber(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	double value = lParam/65536.0;

	WCHAR buf[32];
	swprintf(buf, L"%g", value);

	m_style->setProperty(m_pActiveProperty->m_pType->m_name, buf, NULL);
	Apply();

	return 0;
}

static int CALLBACK FontFamExProc(
  ENUMLOGFONTEX *lpelfe,    // pointer to logical-font data
  NEWTEXTMETRICEX *lpntme,  // pointer to physical-font data
  int FontType,             // type of font
  LPARAM lParam)             // application-defined data

{
	static char prevFont[512] = {0};

	HWND hWndComboBox = (HWND)lParam;

//	CArray<MLOGFONT,MLOGFONT>* fonts = (CArray<MLOGFONT,MLOGFONT>*)lParam;

	//if (FontType & TRUETYPE_FONTTYPE)
	{
		if (stricmp(lpelfe->elfLogFont.lfFaceName, prevFont) != 0)
		{
			strcpy(prevFont, lpelfe->elfLogFont.lfFaceName);

			long index = ::SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)prevFont);
			/*
			MLOGFONT mlf;
			mlf.lf = lpelfe->elfLogFont;
			mlf.FontType = FontType;
			fonts->Add(mlf);
			*/
		}
	}

	return 1;	// Continue enumeration
}

LRESULT CCSSPropertiesDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	USES_CONVERSION;

	SetFocus();

	if (m_wndEdit.m_hWnd)
	{
		EndEdit();
	}

	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_style && m_pTree)
	{
		C2Obj* pParentItem = NULL;

		/*
		if (m_bTabbedView)
		{
			if (point.y < 18)
			{
				int x = 0;
				int n = 0;

				UPOSITION pos = m_pTree->m_childList.GetHeadPosition();
				while (pos)
				{
					CCSSCategory* pCategory = (CCSSCategory*)m_pTree->m_childList.GetNext(pos);

					x += pCategory->m_width+4;

					if (point.x < x)
					{
						break;
					}

					n++;
				}

				if (m_activeCategory != n)
				{
					m_activeCategory = n;
					OnSize();
					Invalidate();
				}
			}
			else
			{
				UPOSITION pos = m_pTree->m_childList.FindIndex(m_activeCategory);
				pParentItem = (C2Obj*)m_pTree->m_childList.GetAt(pos);
			}
		}
		else
		*/
		{
			pParentItem = m_pTree;
		}

		if (pParentItem)
		{
			CPoint pt = point;
			pt.y -= m_areaRect.top;
			pt.y += scrollposY;

			CCSSItem* pFItem = NULL;

			UPOSITION pos = pParentItem->GetHeadPosition();
			int nextlevel = 0;

			int y = 0;
			int top;
			int left;

			while (pos)
			{
				int level = nextlevel;
				CCSSItem* pItem = (CCSSItem*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

				left = level*14;
				top = y;

				y += pItem->m_itemHeight;

				if (pt.y < y)
				{
					pFItem = pItem;
					break;
				}
			}

			if (pFItem)
			{
				if (pt.x >= left && pt.x < left+12)	// Expand/Unexpand
				{
					if (pFItem->HasChildren())
					{
						pFItem->m_expanded = !pFItem->m_expanded;

						OnSize();
						InvalidateRect(NULL, TRUE);
					}
				}
				else
				{
					if (pFItem->m_type == 2)
					{
						if (pt.x < m_splitx)
						{
						}
						else
						{
							pt.x -= m_splitx;
	
							CCSSProperty* pProperty = (CCSSProperty*)pFItem;

							switch (pProperty->m_pType->d.m_type)
							{
							case 0:
								{
									if (!wcscmp(pProperty->m_pType->m_name, L"clip"))
									{
										HMENU hMenu;
										hMenu = CreatePopupMenu();
		
										AppendMenu(hMenu, MF_STRING, 255, _T("Unchanged"));
								//		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
										AppendMenu(hMenu, MF_STRING, CSS_IDENT, _T("auto"));

										/*
										LCSSUnitType unitType = (LCSSUnitType)0;
										if (cssvalues[index])
											cssvalues[index]->get_primitiveType(&unitType);

										CheckMenuItem(hMenu, unitType, MF_BYCOMMAND | MF_CHECKED);
										*/

										CPoint point(m_areaRect.right, m_areaRect.top + top - scrollposY);
										::ClientToScreen(m_hWnd, &point);

										UINT nID = ::TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_LEFTBUTTON, point.x, point.y, 0, m_hWnd, NULL);

										DestroyMenu(hMenu);

										if (nID > 0)
										{
											if (nID == 255)
												m_style->removeProperty(pProperty->m_pType->m_name, NULL);
											else
												m_style->setProperty(pProperty->m_pType->m_name, L"auto", NULL);

											Apply();
										}
									}
									else if (!wcscmp(pProperty->m_pType->m_name, L"font-family"))
									{
										if (!pFItem->m_expanded)
										{
											pFItem->m_expanded = !pFItem->m_expanded;

											OnSize();
											InvalidateRect(NULL, TRUE);
										}
#if 0

										m_comboBox.Create(m_hWnd,
											CRect(m_splitx, m_areaRect.top + top - scrollposY, m_areaRect.right, m_areaRect.top + top - scrollposY+200),
											NULL,
											WS_BORDER | WS_VISIBLE | WS_CHILD | /*CBS_SORT |*/ WS_VSCROLL | CBS_AUTOHSCROLL | CBS_DROPDOWN,
											0, 2);
										/*
										m_wndEdit.SubclassWindow(m_hWndEdit);

										m_wndEdit.SetWindowLong(GWL_USERDATA, (long)pFItem);
										*/
										m_comboBox.SetFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

										{
											{
												HDC	hDC = ::GetDC(NULL);
												LOGFONT	lf = {0};
												lf.lfCharSet = DEFAULT_CHARSET;
												
												int result = EnumFontFamiliesEx(
													hDC,					// handle to device context
													&lf,					// pointer to logical font information
													(FONTENUMPROC)FontFamExProc,    // pointer to callback function
													(LPARAM)m_wndEdit.m_hWnd,//&m_fonts/*hWndComboBox*/,						// application-supplied data
													0);					// reserved; must be zero

												::ReleaseDC(NULL, hDC);

												/*
												HWND hWndComboBox = GetDlgItem(IDC_PREFSFORMAT_FONTFACE);
												for (int i = 0; i < m_fonts.GetSize(); i++)
												{
													long index = ::SendMessage(hWndComboBox, CB_ADDSTRING, 0, 0);
													::SendMessage(hWndComboBox, CB_SETITEMDATA, index, (LPARAM)&m_fonts[i]);
												}
												*/
											}
										}
										/*
										for (int i = 0; i < pProperty->m_enumStrings.GetSize(); i++)
										{
											m_wndEdit.SendMessage(CB_ADDSTRING, 0, (LPARAM)(TCHAR*)pProperty->m_enumStrings[i]);
										}
										*/

										CComBSTR value;
										m_style->getPropertyValue(pProperty->m_pType->m_name, &value);

										//m_wndEdit.SetWindowText(_bstr_t(value));

										m_wndEdit.SendMessage(CB_SELECTSTRING, -1, (LPARAM)(TCHAR*)_bstr_t(value));
										//m_wndEdit.SendMessage(EM_SETSEL, 0, -1);
										m_wndEdit.SetFocus();
#endif
									}
									else
										if (!wcscmp(pProperty->m_pType->m_name, L"font-size"))
									{
										//if (point.x < m_areaRect.right-16)
										{
											/*
											m_hWndEdit = CreateWindowEx(0, "edit", NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
												m_splitx, m_areaRect.top + top - scrollposY, m_areaRect.right - m_splitx-16, pFItem->m_itemHeight-1, m_hWnd, (HMENU)1, _Module.m_hInst, NULL);
											m_wndEdit.SubclassWindow(m_hWndEdit);

											m_wndEdit.SetFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));
											m_wndEdit.SetWindowLong(GWL_USERDATA, (long)pFItem);

											CComBSTR value;
											m_style->getPropertyValue(pProperty->m_pType->m_name, &value);

											m_wndEdit.SetWindowText(_bstr_t(value));

											m_wndEdit.SendMessage(EM_SETSEL, 0, -1);
											m_wndEdit.SetFocus();
											*/

											int presets[] =
											{
												6,
												7,
												8,
												9,
												10,
												11,
												12,
												14,
												18,
												21,
												24,
												36,
												48,
												60,
												72,
											};

											m_pActiveProperty = pProperty;

											m_comboBoxWnd.Create(m_hWnd,
												CRect(m_splitx, m_areaRect.top + top - scrollposY, m_areaRect.right, m_areaRect.top + top - scrollposY+200),
												NULL,
												WS_BORDER | WS_VISIBLE | WS_CHILD | /*CBS_SORT |*/ WS_VSCROLL | CBS_AUTOHSCROLL | CBS_DROPDOWN,
												0, 2);

#if 0
											m_hWndEdit = CreateWindowEx(0, "combobox", NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | CBS_AUTOHSCROLL | CBS_DROPDOWN,
												m_splitx, m_areaRect.top + top - scrollposY, m_areaRect.right - m_splitx, 200/*pFItem->m_itemHeight-1*/, m_hWnd, (HMENU)1, _Module.m_hInst, NULL);
											m_wndEdit.SubclassWindow(m_hWndEdit);

											m_wndEdit.SetWindowLong(GWL_USERDATA, (long)pFItem);
#endif
											m_comboBoxWnd.SetFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

											int npresets = sizeof(presets)/sizeof(int);

											for (int i = 0; i < npresets; i++)
											{
												TCHAR buf[32];
												sprintf(buf, _T("%dpt"), presets[i]);

												m_comboBoxWnd.SendMessage(CB_ADDSTRING, 0, (LPARAM)buf);
											}

											CComBSTR value;
											m_style->getPropertyValue(pProperty->m_pType->m_name, &value);

											m_comboBoxWnd.SetWindowText(_bstr_t(value));

											//m_wndEdit.SendMessage(EM_SETSEL, 0, -1);
											m_comboBoxWnd.SetFocus();

											if (point.x > m_areaRect.right-16)
											{
												m_comboBoxWnd.SendMessage(CB_SHOWDROPDOWN, TRUE, 0);
											}
										}
#if 0
										else
										{
											HMENU hMenu;
											hMenu = CreatePopupMenu();
			
											static WCHAR* strings[] =
											{
												L"xx-small",
												L"x-small",
												L"small",
												L"medium",
												L"large",
												L"x-large",
												L"xx-large",
												L"smaller",
												L"larger",
											};

											AppendMenu(hMenu, MF_STRING, 1, _T("Unchanged"));
											AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
											AppendMenu(hMenu, MF_STRING, CSS_PT, _T("Point"));
											AppendMenu(hMenu, MF_STRING, CSS_PC, _T("Pica"));
											AppendMenu(hMenu, MF_STRING, CSS_PX, _T("Pixel"));
											AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
											AppendMenu(hMenu, MF_STRING, CSS_EMS, _T("em"));
											AppendMenu(hMenu, MF_STRING, CSS_EXS, _T("ex"));
											AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
											AppendMenu(hMenu, MF_STRING, CSS_MM, _T("mm"));
											AppendMenu(hMenu, MF_STRING, CSS_CM, _T("cm"));
											AppendMenu(hMenu, MF_STRING, CSS_IN, _T("Inch"));
											AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
											AppendMenu(hMenu, MF_STRING, CSS_PERCENTAGE, _T("%"));
											AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
											AppendMenu(hMenu, MF_STRING, 100, _T("XX Small"));
											AppendMenu(hMenu, MF_STRING, 101, _T("X Small"));
											AppendMenu(hMenu, MF_STRING, 102, _T("Small"));
											AppendMenu(hMenu, MF_STRING, 103, _T("Medium"));
											AppendMenu(hMenu, MF_STRING, 104, _T("Large"));
											AppendMenu(hMenu, MF_STRING, 105, _T("X Large"));
											AppendMenu(hMenu, MF_STRING, 106, _T("XX Large"));
											AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
											AppendMenu(hMenu, MF_STRING, 107, _T("Smaller"));
											AppendMenu(hMenu, MF_STRING, 108, _T("Larger"));

											CComPtr<ILCSSPrimitiveValue> cssvalue;
											m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);
											if (cssvalue)
											{
												CComBSTR value;
												cssvalue->get_cssText(&value);

												for (int i = 0; i < sizeof(strings)/sizeof(WCHAR*); i++)
												{
													if (!wcscmp(strings[i], value))
													{
														break;
													}
												}

												if (i < sizeof(strings)/sizeof(WCHAR*))
												{
													CheckMenuItem(hMenu, 100+i, MF_BYCOMMAND | MF_CHECKED);
												}
												else
												{
													LCSSUnitType unitType;
													cssvalue->get_primitiveType(&unitType);

													switch (unitType)
													{
														case CSS_PERCENTAGE:
														case CSS_EMS:
														case CSS_EXS:
														case CSS_PX:
														case CSS_CM:
														case CSS_MM:
														case CSS_IN:
														case CSS_PT:
														case CSS_PC:
															{
																CheckMenuItem(hMenu, unitType, MF_BYCOMMAND | MF_CHECKED);
															}
															break;
													}
												}
											}
											else
											{
												CheckMenuItem(hMenu, 1, MF_BYCOMMAND | MF_CHECKED);
											}

											CPoint point(m_areaRect.right, m_areaRect.top + top - scrollposY);
											::ClientToScreen(m_hWnd, &point);

											UINT nID = ::TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_LEFTBUTTON, point.x, point.y, 0, m_hWnd, NULL);

											DestroyMenu(hMenu);

											if (nID > 0)
											{
												if (nID == 1)
												{
													m_style->removeProperty(pProperty->m_pType->m_name, NULL);
													Apply();
												}
												else if (nID >= 100)
												{
												}
												else
												{
												}
											}
										}
#endif
									}
									else if (!wcscmp(pProperty->m_pType->m_name, L"text-decoration"))
									{
										HMENU hMenu;
										hMenu = CreatePopupMenu();
		
										AppendMenu(hMenu, MF_STRING, 1, _T("Unchanged"));
										AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
										AppendMenu(hMenu, MF_STRING, 2, _T("none"));
										AppendMenu(hMenu, MF_STRING, 3, _T("underline"));
										AppendMenu(hMenu, MF_STRING, 4, _T("overline"));
										AppendMenu(hMenu, MF_STRING, 5, _T("line-through"));
										AppendMenu(hMenu, MF_STRING, 6, _T("blink"));

										CComPtr<ILCSSPrimitiveValue> cssvalue;
										m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);
										if (cssvalue)
										{
											CComBSTR value;
											cssvalue->get_cssText(&value);

											if (!wcscmp(value, L"none"))
											{
												CheckMenuItem(hMenu, 2, MF_BYCOMMAND | MF_CHECKED);
											}
											else
											{
												if (wcsstr(value, L"underline")) CheckMenuItem(hMenu, 3, MF_BYCOMMAND | MF_CHECKED);
												if (wcsstr(value, L"overline")) CheckMenuItem(hMenu, 4, MF_BYCOMMAND | MF_CHECKED);
												if (wcsstr(value, L"line-through")) CheckMenuItem(hMenu, 5, MF_BYCOMMAND | MF_CHECKED);
												if (wcsstr(value, L"blink")) CheckMenuItem(hMenu, 6, MF_BYCOMMAND | MF_CHECKED);
											}
										}
										else
										{
											CheckMenuItem(hMenu, 1, MF_BYCOMMAND | MF_CHECKED);
										}

										CPoint point(m_areaRect.right, m_areaRect.top + top - scrollposY);
										::ClientToScreen(m_hWnd, &point);

										UINT nID = ::TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_LEFTBUTTON, point.x, point.y, 0, m_hWnd, NULL);

										DestroyMenu(hMenu);

										if (nID > 0)
										{
#if 0
											MENUITEMINFO mii;
											mii.cbSize = sizeof(MENUITEMINFO);
											mii.fMask = MIIM_STATE;

											GetMenuItemInfo(hMenu, 1, MF_BYPOSITION, &mii);
											if (mii.fState & MFS_CHECKED)	// Unchanged
											{
												m_style->removeProperty(pProperty->m_pType->m_name, NULL);
												Apply();
											}
											else
											{
												_bstr_t value = L"";
											}
#endif
										}
									}
								}
								break;

							case CSSType_Enum:
								{
									if (pProperty->m_hImageList)
									{
										int index = pt.x/20;
										if (index >= 0 && index < pProperty->m_enumStrings.GetSize())
										{
											m_style->setProperty(pProperty->m_pType->m_name, pProperty->m_enumStrings[index], NULL);
											Apply();
										}
										Invalidate();	// TODO remove
									}
									else
									{
										if (TRUE)
										{
											CComBSTR value;
											m_style->getPropertyValue(pProperty->m_pType->m_name, &value);

											HMENU hMenu;
											hMenu = CreatePopupMenu();

											for (int i = 0; i < pProperty->m_enumStrings.GetSize(); i++)
											{
												if (pProperty->m_enumStrings[i].length()==0)
												{
													AppendMenu(hMenu, MF_SEPARATOR, i+1, NULL);
												}
												else
												{
													UINT nFlags = MF_STRING;
													if (value.Length() && !wcscmp(value, pProperty->m_enumStrings[i])) nFlags |= MF_CHECKED;
													AppendMenu(hMenu, nFlags, i+1, pProperty->m_enumStrings[i]);
												}
											}

											CPoint point(m_splitx, m_areaRect.top + top - scrollposY + pFItem->m_itemHeight);
											::ClientToScreen(m_hWnd, &point);

											UINT nID = ::TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_LEFTBUTTON, point.x, point.y, 0, m_hWnd, NULL);

											DestroyMenu(hMenu);

											if (nID > 0)
											{
												_bstr_t newvalue = pProperty->m_enumStrings[nID-1];

												if (value.Length()==0 || wcscmp(value, newvalue))
												{
													m_style->setProperty(pProperty->m_pType->m_name, newvalue, NULL/*priority*/);
													Apply();
												}
											}
										}
										else
										{
											m_hWndEdit = CreateWindowEx(0, "combobox", NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | /*CBS_SORT |*/ CBS_AUTOHSCROLL | CBS_DROPDOWN,
												m_splitx, m_areaRect.top + top - scrollposY, m_areaRect.right - m_splitx, 200/*pFItem->m_itemHeight-1*/, m_hWnd, (HMENU)1, _Module.m_hInst, NULL);
											m_wndEdit.SubclassWindow(m_hWndEdit);

											m_wndEdit.SetWindowLong(GWL_USERDATA, (long)pFItem);
											m_wndEdit.SetFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

											for (int i = 0; i < pProperty->m_enumStrings.GetSize(); i++)
											{
												m_wndEdit.SendMessage(CB_ADDSTRING, 0, (LPARAM)(TCHAR*)pProperty->m_enumStrings[i]);
											}

											CComBSTR value;
											m_style->getPropertyValue(pProperty->m_pType->m_name, &value);

											//m_wndEdit.SetWindowText(_bstr_t(value));

											m_wndEdit.SendMessage(CB_SELECTSTRING, -1, (LPARAM)(TCHAR*)_bstr_t(value));
											//m_wndEdit.SendMessage(EM_SETSEL, 0, -1);
											m_wndEdit.SetFocus();
										}
									}
								}
								break;

							case CSSType_Uri:
								{
									static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
																				"Images (*.jpg;*.jpeg;*.png;*.gif)\0*.jpg;*.jpeg;*.png;*.gif\0"
																				"SVG (*.svg)\0*.svg\0"
																				);

									TCHAR sbuffer[4096];
									strcpy(sbuffer, "");	// Initial filename

									CComPtr<ILCSSPrimitiveValue> cssvalue;
									m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);
									if (cssvalue)
									{
										CComBSTR value;
										cssvalue->getStringValue(&value);
										if (value.Length())
											strcpy(sbuffer, W2A(value));	// Initial filename
									}

									TCHAR curdir[MAX_PATH];
									GetCurrentDirectory(sizeof(curdir), curdir);

									ASSERT(0);
									HWND hWnd = NULL;//GetMainHwnd();

									OPENFILENAME	ofn = {0};
									ofn.lStructSize = sizeof(OPENFILENAME);
									ofn.hwndOwner = hWnd;
									ofn.hInstance = _Module.m_hInst;
									ofn.Flags = OFN_EXPLORER |/* OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST |*/ OFN_HIDEREADONLY;
									ofn.lpstrFile = sbuffer;
									ofn.nMaxFile = sizeof(sbuffer);
									ofn.lpstrInitialDir = curdir;
									ofn.lpstrFilter = FilesFilter;
									ofn.nFilterIndex = 1;
									
									if (GetOpenFileName(&ofn))
									{
										_bstr_t value = L"url('" + _bstr_t(sbuffer) + L"')";
										m_style->setProperty(pProperty->m_pType->m_name, value, NULL);
										Apply();

										Invalidate();	// TODO remove
									}
								}
								break;

							case CSSType_Number:
								{
									CComPtr<ILCSSPrimitiveValue> cssvalue;
									m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);

									m_pActiveProperty = pProperty;

									m_editNumberWnd.Create(m_hWnd,
										CRect(m_splitx, m_areaRect.top + top - scrollposY, m_areaRect.right, m_areaRect.top + top-scrollposY+20),
										NULL,
										WS_CHILD | WS_VISIBLE, 0, 3);
#if 0
									m_wnd.Create("EditNumber", m_hWnd,
										&CRect(m_splitx, m_areaRect.top + top - scrollposY, m_areaRect.right, m_areaRect.top + top-scrollposY+20), NULL, WS_CHILD | WS_VISIBLE);
#if 0
									m_hWndEdit = CreateWindowEx(0, "PopupSlider", NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | CBS_SORT | CBS_AUTOHSCROLL | CBS_DROPDOWN,
										m_splitx, m_areaRect.top + top - scrollposY, m_areaRect.right - m_splitx, 200/*pFItem->m_itemHeight-1*/, m_hWnd, (HMENU)1, _Module.m_hInst, NULL);
#endif
#endif
									m_editNumberWnd.SetFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));
									m_editNumberWnd.SendMessage(SBM_SETRANGE, 0, 1<<16);

									double value = 0;
									if (cssvalue)
									{
										cssvalue->getFloatValue(CSS_NUMBER, &value);
									}
									else
									{
									}

									m_editNumberWnd.SendMessage(SBM_SETPOS, 0, (int)(value*65536));

									/*
									CPopupSlider slider;

									CPoint scrpt;

									scrpt.x = m_splitx;
									scrpt.y = top+pProperty->m_itemHeight + m_areaRect.top - scrollposY;
									ClientToScreen(&scrpt);

									value = slider.GetValue(
										pProperty->m_pType->d.m_numberMinValue,
										pProperty->m_pType->d.m_numberMaxValue,
										0,	// value
										scrpt.y, 120);

									WCHAR buf[32];
									swprintf(buf, L"%g", value);

									m_style->setProperty(pProperty->m_pType->m_name, buf, NULL);
									Apply();
									*/
								}
								break;

							case CSSType_Length:
							case CSSType_String:
								{
									m_hWndEdit = CreateWindowEx(0, "edit", NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
										m_splitx, m_areaRect.top + top - scrollposY, m_areaRect.right - m_splitx, pFItem->m_itemHeight-1, m_hWnd, (HMENU)1, _Module.m_hInst, NULL);
									m_wndEdit.SubclassWindow(m_hWndEdit);

									m_wndEdit.SetFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));
									//m_wndEdit.SetWindowLong(GWL_USERDATA, (long)pFItem);

									m_pActiveProperty = pProperty;

									CComBSTR value;
									m_style->getPropertyValue(pProperty->m_pType->m_name, &value);

									m_wndEdit.SetWindowText(_bstr_t(value));

									m_wndEdit.SendMessage(EM_SETSEL, 0, -1);
									m_wndEdit.SetFocus();
								}
								break;

							case CSSType_Color:
								{
									if (point.x < m_areaRect.right-16)	// Edit color
									{
										static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_colorEditing = pProperty->m_pType->m_name;

										static_cast<CEXMLViewGroup*>(m_viewGroup.p)->SetCurrentSelectionColor();
										static_cast<CEXMLViewGroup*>(m_viewGroup.p)->Fire_ColorChanged();
									}
									else
									{
										HMENU hMenu;
										hMenu = CreatePopupMenu();
		
										AppendMenu(hMenu, MF_STRING, 1, _T("transparent"));
										AppendMenu(hMenu, MF_STRING, 2, _T("currentColor"));
										AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
										AppendMenu(hMenu, MF_STRING, 3, _T("hex ###"));
										AppendMenu(hMenu, MF_STRING, 4, _T("hex ######"));
										AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
										AppendMenu(hMenu, MF_STRING, 5, _T("rgb"));
										AppendMenu(hMenu, MF_STRING, 6, _T("rgb %"));
										AppendMenu(hMenu, MF_STRING, 7, _T("rgba"));
										AppendMenu(hMenu, MF_STRING, 8, _T("rgba %"));
										AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
										AppendMenu(hMenu, MF_STRING, 9, _T("hsl"));
										AppendMenu(hMenu, MF_STRING, 10, _T("hsl %"));
										AppendMenu(hMenu, MF_STRING, 11, _T("hsla"));
										AppendMenu(hMenu, MF_STRING, 12, _T("hsla %"));
										AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
										AppendMenu(hMenu, MF_STRING, 13, _T("Named color"));

										/*
										LCSSUnitType unitType = (LCSSUnitType)0;
										if (cssvalues[index])
											cssvalues[index]->get_primitiveType(&unitType);

										CheckMenuItem(hMenu, unitType, MF_BYCOMMAND | MF_CHECKED);
										*/

										CPoint point(m_areaRect.right, m_areaRect.top + top - scrollposY);
										::ClientToScreen(m_hWnd, &point);

										UINT nID = ::TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_LEFTBUTTON, point.x, point.y, 0, m_hWnd, NULL);

										DestroyMenu(hMenu);

										if (nID > 0)
										{
											switch (nID)
											{
											case 1:
												m_style->setProperty(pProperty->m_pType->m_name, L"transparent", NULL);
												break;

											case 2:
												m_style->setProperty(pProperty->m_pType->m_name, L"currentColor", NULL);
												break;
											}

											Apply();

											static_cast<CEXMLViewGroup*>(m_viewGroup.p)->SetCurrentSelectionColor();	// ??
											static_cast<CEXMLViewGroup*>(m_viewGroup.p)->Fire_ColorChanged();
										}
									}

#if 0
									CComPtr<ILCSSPrimitiveValue> cssvalue;
									m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);
									if (cssvalue == NULL)
									{
										m_style->setProperty(pProperty->m_pType->m_name, L"#000000"/*pFItem->m_pType->m_initialCSS*/, NULL);
										m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);
									}

									if (cssvalue)
									{
										static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_colorEditing = pProperty->m_pType->m_name;
										/*
										CComPtr<ILRGBColor> rgbColor;
										cssvalue->getRGBColorValue(&rgbColor);
										if (rgbColor)
										*/
										
									// TODO

										/*
										{
											CComObject<CCSSPropertyColor>* pEColor;
											CComObject<CCSSPropertyColor>::CreateInstance(&pEColor);
											if (pEColor)
											{
											//	pEColor->m_rgbColor = rgbColor;
												pEColor->m_cssvalue = cssvalue;

												gApp->m_frame->EditColor(pEColor);
											}
										}
										*/
									}
#endif
								}
								break;
							}
						}
					}
					else if (pFItem->m_type == 3)
					{
						CCSSProperty* pProperty = (CCSSProperty*)pFItem->m_parent;

						if (!wcscmp(pProperty->m_pType->m_name, L"clip"))
						{
							CComPtr<ILCSSPrimitiveValue> cssvalue;
							m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);

							long index = (pt.y-top)/18;

							if (index >= 0 && index < 4)
							{
								CComPtr<ILCSSPrimitiveValue> cssvalues[4];
								CComBSTR values[4];

								LCSSUnitType clipUnitType;

								if (cssvalue)
								{
									cssvalue->get_primitiveType(&clipUnitType);

									if (clipUnitType == CSS_RECT)
									{
										CComPtr<ILCSSRect> rect;
										cssvalue->getRectValue(&rect);
										ASSERT(rect);

										rect->get_top(&cssvalues[0]);
										cssvalues[0]->get_cssText(&values[0]);

										rect->get_right(&cssvalues[1]);
										cssvalues[1]->get_cssText(&values[1]);

										rect->get_bottom(&cssvalues[2]);
										cssvalues[2]->get_cssText(&values[2]);

										rect->get_left(&cssvalues[3]);
										cssvalues[3]->get_cssText(&values[3]);
									}
									else
									{
										if (index != 0) values[0] = L"auto";
										if (index != 1) values[1] = L"auto";
										if (index != 2) values[2] = L"auto";
										if (index != 3) values[3] = L"auto";
									}
								}
								else
								{
									if (index != 0) values[0] = L"auto";
									if (index != 1) values[1] = L"auto";
									if (index != 2) values[2] = L"auto";
									if (index != 3) values[3] = L"auto";
								}

								if (pt.x < m_areaRect.right-16)
								{
									CEdit wndEdit;
									int wtop = m_areaRect.top + top - scrollposY + index*18;
									wndEdit.Create(
										m_hWnd,
										CRect(left+40, wtop, m_areaRect.right-16, wtop+18-1),
										NULL,
										WS_BORDER | WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
										0/*exstyle*/,
										1/*id*/);

									//wndEdit.SetWindowLong(GWL_USERDATA, (long)pFItem);
									wndEdit.SetFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

									//CComPtr<ILCSSPrimitiveValue> nvalue;
									//CComBSTR oldvalue;

									//if (index < count)
									{
										//cssvalue->item(index, (ILCSSValue**)&nvalue);
										//nvalue->getStringValue(&oldvalue);

										wndEdit.SetWindowText(_bstr_t(values[index]));
										wndEdit.SetSel(0, -1);
									}

									wndEdit.SetFocus();

									m_bModal = TRUE;

									MSG msg;
									while (GetMessage(&msg, NULL, 0, 0))
									{
										if (msg.message == WM_KEYDOWN && msg.wParam == VK_RETURN)
										{
											break;
										}

										TranslateMessage(&msg);
										DispatchMessage(&msg);

										if (!m_bModal)
											break;
									}

									{
										TCHAR buf[512];
										wndEdit.GetWindowText(buf, sizeof(buf));
										values[index] = buf;
									}

									wndEdit.DestroyWindow();

									{
										WCHAR buf[256];
										swprintf(buf, L"rect(%s,%s,%s,%s)", (BSTR)values[0], (BSTR)values[1], (BSTR)values[2], (BSTR)values[3]);

										m_style->setProperty(pProperty->m_pType->m_name, buf, NULL/*priority*/);
										Apply();
									}
								}
								else
								{
									HMENU hMenu;
									hMenu = CreatePopupMenu();
	
									AppendMenu(hMenu, MF_STRING, CSS_IDENT, _T("auto"));
									AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
									AppendMenu(hMenu, MF_STRING, CSS_NUMBER, _T("Number"));
									AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
									AppendMenu(hMenu, MF_STRING, CSS_PT, _T("Point"));
									AppendMenu(hMenu, MF_STRING, CSS_PC, _T("Pica"));
									AppendMenu(hMenu, MF_STRING, CSS_PX, _T("Pixel"));
									AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
									AppendMenu(hMenu, MF_STRING, CSS_EMS, _T("em"));
									AppendMenu(hMenu, MF_STRING, CSS_EXS, _T("ex"));
									AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
									AppendMenu(hMenu, MF_STRING, CSS_MM, _T("mm"));
									AppendMenu(hMenu, MF_STRING, CSS_CM, _T("cm"));
									AppendMenu(hMenu, MF_STRING, CSS_IN, _T("Inch"));
							//		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
							//		AppendMenu(hMenu, MF_STRING, CSS_PERCENTAGE, _T("%"));
							//		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

									LCSSUnitType unitType = (LCSSUnitType)0;
									if (cssvalues[index])
										cssvalues[index]->get_primitiveType(&unitType);

									CheckMenuItem(hMenu, unitType, MF_BYCOMMAND | MF_CHECKED);

									CPoint point(m_areaRect.right, m_areaRect.top + top - scrollposY + index*18);
									::ClientToScreen(m_hWnd, &point);

									UINT nID = ::TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_LEFTBUTTON, point.x, point.y, 0, m_hWnd, NULL);

									DestroyMenu(hMenu);

									if (nID > 0)
									{
										if (cssvalue == NULL || clipUnitType != CSS_RECT)
										{
											m_style->setProperty(pProperty->m_pType->m_name, L"rect(auto,auto,auto,auto)", NULL);

										// Fetch the css values again
											CComPtr<ILCSSPrimitiveValue> cssvalue;
											m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);

											CComPtr<ILCSSRect> rect;
											cssvalue->getRectValue(&rect);
											ASSERT(rect);

											rect->get_top(&cssvalues[0]);
											cssvalues[0]->get_cssText(&values[0]);

											rect->get_right(&cssvalues[1]);
											cssvalues[1]->get_cssText(&values[1]);

											rect->get_bottom(&cssvalues[2]);
											cssvalues[2]->get_cssText(&values[2]);

											rect->get_left(&cssvalues[3]);
											cssvalues[3]->get_cssText(&values[3]);

											unitType = CSS_IDENT;
										}

										if (nID == CSS_IDENT)
										{
											cssvalues[index]->setStringValue(CSS_IDENT, L"auto");
										}
										else
										{
											if (unitType == CSS_IDENT)	// from auto to number
											{
												cssvalues[index]->setFloatValue((LCSSUnitType)nID, 0);
											}
											else
											{
										// Convert the unit
												double fvalue;
												cssvalues[index]->getFloatValue((LCSSUnitType)nID, &fvalue);
												cssvalues[index]->setFloatValue((LCSSUnitType)nID, fvalue);
											}
										}

										Apply();
									}
								}
							}
						}
						else if (!wcscmp(pProperty->m_pType->m_name, L"font-family"))
						{
							CComPtr<ILCSSValueList> cssvalue;
							m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);

							long count = 0;

							if (cssvalue != NULL)
							{
								cssvalue->get_length(&count);
							}

							long index = (pt.y-top)/18;
							if (index >= 0 && index <= count)
							{
								CComboBox wndEdit;
								int wtop = m_areaRect.top + top - scrollposY + index*18;
								wndEdit.Create(
									m_hWnd,
									CRect(left, wtop, m_areaRect.right, wtop+300),
									NULL,
									WS_BORDER | WS_VISIBLE | WS_CHILD | CBS_SORT | WS_VSCROLL | CBS_AUTOHSCROLL | CBS_DROPDOWN,
									0/*exstyle*/,
									1/*id*/);

								//wndEdit.SetWindowLong(GWL_USERDATA, (long)pFItem);
								wndEdit.SetFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

								{
									HDC	hDC = ::GetDC(NULL);
									LOGFONT	lf = {0};
									lf.lfCharSet = DEFAULT_CHARSET;

									int result = EnumFontFamiliesEx(
										hDC,					// handle to device context
										&lf,					// pointer to logical font information
										(FONTENUMPROC)FontFamExProc,    // pointer to callback function
										(LPARAM)wndEdit.m_hWnd,//&m_fonts/*hWndComboBox*/,						// application-supplied data
										0);					// reserved; must be zero

									::ReleaseDC(NULL, hDC);
								}

								CComPtr<ILCSSPrimitiveValue> nvalue;

								if (index < count)
								{
									cssvalue->item(index, (ILCSSValue**)&nvalue);

									CComBSTR value;
									nvalue->getStringValue(&value);

									wndEdit.SendMessage(CB_SELECTSTRING, -1, (LPARAM)(TCHAR*)_bstr_t(value));
								}

								wndEdit.SetFocus();

								m_bModal = TRUE;

								MSG msg;
								while (GetMessage(&msg, NULL, 0, 0))
								{
									/*
									if (msg.message == WM_KILLFOCUS)
									{
										break;
									}
									*/

									if (msg.message == WM_KEYDOWN && msg.wParam == VK_RETURN)
									{
										break;
									}

									/*
									if (msg.hwnd != wndEdit.m_hWnd)
									{
										if (msg.message == WM_LBUTTONDOWN ||
											msg.message == WM_RBUTTONDOWN ||
											msg.message == WM_MBUTTONDOWN ||

											msg.message == WM_NCLBUTTONDOWN ||
											msg.message == WM_NCRBUTTONDOWN ||
											msg.message == WM_NCMBUTTONDOWN)
										{
											break;
										}
									}
									*/

									TranslateMessage(&msg);
									DispatchMessage(&msg);

									/*
									if (msg.message == WM_KILLFOCUS)
									{
										break;
									}
									*/

									/*
									if (msg.message == WM_COMMAND &&
										HIWORD(msg.wParam) == CBN_SELENDOK)
									{
										break;
									}
									*/

									/*
									if (msg.message == WM_COMMAND)
									{
										if (HIWORD(msg.wParam) == CBN_SELENDOK)
										{
											break;
										}
									}
									*/

									if (!m_bModal)
										break;
								}

								TCHAR buf[512];
								wndEdit.GetWindowText(buf, sizeof(buf));
								CComBSTR value = buf;

								wndEdit.DestroyWindow();

								if (nvalue)
								{
									if (value.Length() == 0)
									{
										cssvalue->deleteValue(index);
									}
									else
									{
										nvalue->setStringValue(CSS_STRING, value);
									}

									Apply();
								}
								else	// Append value
								{
									if (value.Length() > 0)
									{
										if (cssvalue)
										{
											cssvalue->insertValue(value, count, NULL);
										}
										else
										{
											m_style->setProperty(pProperty->m_pType->m_name, value, NULL/*priority*/);
										}

										Apply();
									}
								}
							}
						}
						else if (!wcscmp(pProperty->m_pType->m_name, L"stroke-dasharray"))
						{
							CComPtr<ILCSSValueList> cssvalue;
							m_style->getPropertyCSSValue(pProperty->m_pType->m_name, (ILCSSValue**)&cssvalue);

							long count = 0;

							if (cssvalue != NULL)
							{
								cssvalue->get_length(&count);
							}

							long index = (pt.y-top)/18;
							if (index >= 0 && index <= count)
							{
								CEdit wndEdit;
								int wtop = m_areaRect.top + top - scrollposY + index*18;
								wndEdit.Create(
									m_hWnd,
									CRect(left+32, wtop, m_areaRect.right-16, wtop+18-1),
									NULL,
									WS_BORDER | WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
									0/*exstyle*/,
									1/*id*/);

								//wndEdit.SetWindowLong(GWL_USERDATA, (long)pFItem);
								wndEdit.SetFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

								CComPtr<ILCSSPrimitiveValue> nvalue;
								CComBSTR oldvalue;

								if (index < count)
								{
									cssvalue->item(index, (ILCSSValue**)&nvalue);

									nvalue->get_cssText(&oldvalue);

									wndEdit.SetWindowText(_bstr_t(oldvalue));
									wndEdit.SetSel(0, -1);
								}

								wndEdit.SetFocus();

								m_bModal = TRUE;

								MSG msg;
								while (GetMessage(&msg, NULL, 0, 0))
								{
									if (msg.message == WM_KEYDOWN && msg.wParam == VK_RETURN)
									{
										break;
									}

									TranslateMessage(&msg);
									DispatchMessage(&msg);

									if (!m_bModal)
										break;
								}

								TCHAR buf[512];
								wndEdit.GetWindowText(buf, sizeof(buf));
								CComBSTR value = buf;

								wndEdit.DestroyWindow();

								if (nvalue)
								{
									if (value.Length() == 0)
									{
										cssvalue->deleteValue(index);
										Apply();
									}
									else
									{
										if (oldvalue.Length() == 0 || wcscmp(oldvalue, value))
										{
											nvalue->set_cssText(value);
											Apply();
										}
									}
								}
								else	// Append value
								{
									if (value.Length() > 0)
									{
										if (cssvalue)
										{
											cssvalue->insertValue(value, count, NULL);
										}
										else
										{
											m_style->setProperty(pProperty->m_pType->m_name, value, NULL/*priority*/);
										}

										Apply();
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return 0;
}

void CCSSPropertiesDlg::SetPropertyValue(BSTR value)
{
	CCSSProperty* pProperty = m_pActiveProperty;

	CComBSTR oldvalue;
	m_style->getPropertyValue(pProperty->m_pType->m_name, &oldvalue);
	if (oldvalue.Length()==0) oldvalue = L"";

	if (wcscmp(oldvalue, value))
	{
		m_style->setProperty(pProperty->m_pType->m_name, value, NULL);
		Apply();
	}
}

LRESULT CCSSPropertiesDlg::OnKillFocus(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_bModal = FALSE;

	return 0;
}

LRESULT CCSSPropertiesDlg::OnGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MessageBeep(-1);
	return 0;
}

//virtual
BOOL CCSSPropertiesDlg::PreTranslateMessage(MSG* pMsg)
{
	if(IsDialogMessage(pMsg))
		return TRUE;

	return FALSE;
}

LRESULT CCSSPropertiesDlg::OnCbGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CCSSPropertiesDlg::OnCbKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MessageBeep(-1);

	return m_comboBoxWnd.DefWindowProc(uMsg, wParam, lParam);
}

LRESULT CCSSPropertiesDlg::OnCbnKillFocus(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	USES_CONVERSION;

	TCHAR buf[512];
	m_comboBoxWnd.GetWindowText(buf, sizeof(buf));
	m_comboBoxWnd.DestroyWindow();

	SetPropertyValue(A2W(buf));

	return 0;
}

LRESULT CCSSPropertiesDlg::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	USES_CONVERSION;

	if (m_comboBoxWnd.m_hWnd)
	{
		TCHAR buf[512];
		m_comboBoxWnd.GetWindowText(buf, sizeof(buf));
		m_comboBoxWnd.DestroyWindow();

		SetPropertyValue(A2W(buf));
	}

	return 0;
}

LRESULT CCSSPropertiesDlg::OnCbnSelendOk(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	USES_CONVERSION;

	int cursel = m_comboBoxWnd.SendMessage(CB_GETCURSEL, 0, 0);
	if (cursel >= 0)
	{
		TCHAR text[256];
		m_comboBoxWnd.SendMessage(CB_GETLBTEXT, cursel, (LPARAM)text);

		CComBSTR value = A2W(text);

		SetPropertyValue(value);
	}

	return 0;
}

LRESULT CCSSPropertiesDlg::OnEditNumberKillFocus(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_editNumberWnd.DestroyWindow();
	return 0;
}

LRESULT CCSSPropertiesDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CRect client;
//	GetClientRect(&client);

	OnSize();

	return 0;
}

void CCSSPropertiesDlg::OnSize()
{
	CRect client;
	GetClientRect(&client);

	/*
	if (m_bTabbedView)
	{
		m_areaRect.left = 0;
		m_areaRect.top = 18;
		m_areaRect.right = client.right-16;
		m_areaRect.bottom = client.bottom;

		m_axvert.MoveWindow(client.right-16, 18, 16, m_areaRect.Height());
	}
	else
	*/
	{
		m_areaRect.left = 0;
		m_areaRect.top = 0;
		m_areaRect.right = client.right-16;
		m_areaRect.bottom = client.bottom;

		m_axvert.MoveWindow(client.right-16, 0, 16, m_areaRect.Height());
	}

	if (m_pTree)
	{
#if 0
		{
			HDC hDC = CreateCompatibleDC(NULL);
			HFONT hOldFont = (HFONT)SelectObject(hDC, GetStockObject(DEFAULT_GUI_FONT));

			UPOSITION pos = m_pTree->m_childList.GetHeadPosition();
			while (pos)
			{
				CCSSCategory* pCategory = (CCSSCategory*)m_pTree->m_childList.GetNext(pos);

				CSize size;
				GetTextExtentPoint32(hDC, pCategory->m_name, pCategory->m_name.length(), &size);
				pCategory->m_width = size.cx;
			}

			int count = m_pTree->m_childList.GetCount();

			int totalwidth = 0;
			pos = m_pTree->m_childList.GetHeadPosition();
			while (pos)
			{
				CCSSCategory* pCategory = (CCSSCategory*)m_pTree->m_childList.GetNext(pos);

				totalwidth += pCategory->m_width+4;
			}

			if (totalwidth > client.right)
			{
				//int totalReduceBy = totalwidth-client.right;

				pos = m_pTree->m_childList.GetHeadPosition();
				while (pos)
				{
					CCSSCategory* pCategory = (CCSSCategory*)m_pTree->m_childList.GetNext(pos);

					pCategory->m_width = client.right*((double)pCategory->m_width/(totalwidth));

						/*
					double pcntOfTotal = (double)(pCategory->m_width+4)/totalwidth;
					int reduceBy = totalReduceBy*pcntOfTotal;
					pCategory->m_width -= reduceBy;
					*/
					//totalwidth += pCategory->m_width+4;
				}
			}

			SelectObject(hDC, hOldFont);
			DeleteDC(hDC);
		}
#endif

		int height = 0;
		C2Obj* pParentItem;

		/*
		if (m_bTabbedView)
		{
			UPOSITION pos = m_pTree->m_childList.FindIndex(m_activeCategory);
			pParentItem = (C2Obj*)m_pTree->m_childList.GetAt(pos);
		}
		else
		*/
		{
			pParentItem = m_pTree;
		}

		UPOSITION pos = pParentItem->GetHeadPosition();
		int nextlevel = 0;

		while (pos)
		{
			int level = nextlevel;
			CCSSProperty* pItem = (CCSSProperty*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);
			height += pItem->m_itemHeight;
		}

		m_vert->SetInfo(0, height, m_areaRect.Height());
	}

	if (m_viewGroup)
	{
		m_axvert.ShowWindow(SW_SHOW);
	}
	else
	{
		m_axvert.ShowWindow(SW_HIDE);
	}
}

void __stdcall CCSSPropertiesDlg::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	/*
	if (m_edit)
	{
		CRect wrect;
		::GetWindowRect(m_edit, &wrect);
		ScreenToClient((LPPOINT)&wrect.left);
		ScreenToClient((LPPOINT)&wrect.right);
		::SetWindowPos(m_edit, NULL, wrect.left, wrect.top + (oldPos-pos), 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOREDRAW);
	}
	*/

	CRect	rect = m_areaRect;
	
	m_vert->put_pos(pos);

	ScrollWindow(0, oldPos-pos, &rect, &rect);
}

// TODO ??
//HRESULT ApplyStyle(IWebXMLViewGroup* viewGroup);
/*
{
	CComPtr<IWebXMLDocument> eDocument;
	viewGroup->get_document(&eDocument);

	long n;
	viewGroup->GetSelectedCount(&n);

	for (int i = 0; i < n; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		viewGroup->GetSelectedElementN(i, &selectedElement);

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> element;
		eElement->get_domElement(&element);

	// TODO
		CComBSTR cssText;
		static_cast<CEXMLDocument*>(eDocument.p)->m_defaultStyle->get_cssText(&cssText);

		element->setAttribute(L"style", cssText);
	}

	return S_OK;
}
*/

void CCSSPropertiesDlg::Apply()
{
//	MessageBeep(-1);
#if 0	// Had this
	CComQIPtr<IEXMLViewGroup> xmlviewgroup = m_viewGroup;
	CComPtr<IEXMLDocument> eDocument;
	m_viewGroup->get_eXMLDocument(&eDocument);

	static_cast<CEXMLDocument*>(eDocument.p)->m_defaultStyle->set_cssText(L"");

	long length;
	m_style->get_length(&length);
	for (int i = 0; i < length; i++)
	{
		CComBSTR propertyName;
		m_style->item(i, &propertyName);

		CComBSTR value;
		m_style->getPropertyValue(propertyName, &value);

		if (value.Length())
		{
			static_cast<CEXMLDocument*>(eDocument.p)->m_defaultStyle->setProperty(propertyName, value, NULL);
		}
	}
#endif

	/*
	CComBSTR cssText;
	m_style->get_cssText(&cssText);

	static_cast<CEXMLDocument*>(eDocument.p)->m_defaultStyle->set_cssText(cssText);
	*/

// Not sure about this
	m_viewGroup->ApplyCurrentSelectionCSSStyle();
}

// ILCSSStyleDeclarationHandler
STDMETHODIMP CCSSPropertiesDlg::handleCSSEvent(/*[in]*/ long type, /*[in]*/ BSTR propertyName)
{
	if (m_hWnd)
	{
		InvalidateRect(&m_areaRect);
	}
	return S_OK;
}

void __stdcall CCSSPropertiesDlg::OnViewGroupSelectionChanged()
{
#if 0
	if (m_style)
	{
		m_style->removeHandler(this);
		m_style.Release();
	}

	m_style.CoCreateInstance(CLSID_LCSSStyleDeclaration);

	long ncount;
	m_viewGroup->GetSelectedCount(&ncount);

	for (int j = 0; j < g_nCSSProperties; j++)
	{
		CSSProperty* pProperty = &CSSProperties[j];

		if (pProperty->m_initialCSS != NULL)
		{
			for (int i = 0; i < ncount; i++)
			{
				CComPtr<IESelectedElement> selectedElement;
				m_viewGroup->GetSelectedElementN(i, &selectedElement);

				CComPtr<IEElement> eElement;
				selectedElement->get_eElement(&eElement);

				CComPtr<ILDOMElement> domElement;
				eElement->get_domElement(&domElement);

				CComQIPtr<ILElementCSSInlineStyle> stylable = domElement;
				if (stylable)
				{
					CComPtr<ILCSSStyleDeclaration> style;
					stylable->get_style(&style);

					CComBSTR value2;
					style->getPropertyValue(pProperty->m_name, &value2);

					if (i == 0)	// first element
					{
						if ((BSTR)value2 != NULL)
						{
							m_style->setProperty(pProperty->m_name, value2, NULL);
						}
					}
					else
					{
						CComBSTR value;
						m_style->getPropertyValue(pProperty->m_name, &value);
						if (value2.Length() > 0 && (value.Length() != value2.Length() ||
							wcscmp(value, value2)))
						{
							m_style->removeProperty(pProperty->m_name, NULL);
							break;
						}
					}
				}
				else	// element isn't CSS stylable
				{
					// Disable style editing all together
					m_style.Release();

					j = g_nCSSProperties;
					break;
				}
			}
		}
	}

	if (m_style)
	{
		m_style->addHandler(this);
	}
#endif

	if (m_hWnd)
	{
		InvalidateRect(&m_areaRect);
	}
}

STDMETHODIMP CCSSPropertiesDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IECSSSelection> viewGroup = object;

	if (viewGroup)
	{
		ASSERT(m_viewGroup == NULL);

		m_viewGroup = viewGroup;

		IDispEventImpl<2, CCSSPropertiesDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

		m_viewGroup->GetCurrentSelectionCSSStyle(&m_style);
		//m_style = static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionStyle;

		if (m_style)
		{
			m_style->addHandler(this);
		}

		OnViewGroupSelectionChanged();

		if (m_hWnd)
		{
			OnSize();
		}

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CCSSPropertiesDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ASSERT(m_viewGroup);

	if (m_style)
	{
		m_style->removeHandler(this);
		m_style.Release();
	}

	IDispEventImpl<2, CCSSPropertiesDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);
	m_viewGroup.Release();

	if (m_hWnd)
	{
		OnSize();
		Invalidate();
	}

	return S_OK;
}

BEGIN_CMD_MAP(CCSSPropertiesDlg)
//	CMD_HANDLER(ID_CSSPROPERTIES_TABBEDVIEW, OnTabbedView)
//	CMD_UPDATE(ID_CSSPROPERTIES_TABBEDVIEW, OnTabbedViewUpdate)
END_CMD_MAP()

/*
LRESULT CCSSPropertiesDlg::OnTabbedView(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_bTabbedView = !m_bTabbedView;
	OnSize();
	Invalidate();

	return 0;
}

void CCSSPropertiesDlg::OnTabbedViewUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_bTabbedView);
}
*/