#include "stdafx.h"
//#include "LXML.h"
#include "LXML2.h"

#include "PImage.h"
#include "CSSStackingContext.h"
#include "Window.h"
#include "LXMLDocumentView.h"
#include "PBlockBox.h"
#include "PInlineBox.h"
#include "PTextNode.h"
#include "HTMContext.h"
#include "CSSPrimitiveValue.h"
#include "CSSValueList.h"
#include "RGBColor.h"
#include "SVGColor.h"
#include "SVGPaint.h"
//#include "DocumentStyleImpl.h"

#include <stdlib.h>	// exit (TODO remove)

#include <limits.h>

#define bBreakable	0

namespace System
{
namespace Web
{

gm::PointD ControlHost::TransformPointToClient(gm::PointD point)
{
	ASSERT(0);
	return gm::PointD(0,0);
#if 0
	LDraw::PointD pt = GetParentToElementTransformMatrix()->GetInverse()->Transform(point);

	pt = m_pElement->m_pBox->ScreenToClient(pt);

	LDraw::PointD spoint = m_pWindow->ScreenToClient(pt.X, pt.Y);

//	LDraw::RectF outerRect = m_pElement->m_pBox->GetAbsOuterRect();

	return spoint;//LDraw::PointD(spoint->get_X(), spoint->get_Y());
#endif
}

void ControlHost::SetCapture(Gui::UIElement* p)
{
	ASSERT(0);
#if 0
	m_pElementCapture = p;
	m_pWindow->m_pElementCapture = m_pElement;
	m_pWindow->CaptureMouse();
#if 0
	m_bInsideWindow = true;	// TODO Not here
#endif
#endif
}

void ControlHost::ReleaseCapture(Gui::UIElement* p)
{
	ASSERT(0);
#if 0
	if (m_pElementCapture == p)
	{
		m_pWindow->m_pElementCapture = NULL;
		m_pWindow->ReleaseMouseCapture();
	}
	else
		ASSERT(0);
#endif
}

#if 0
// rect is in local space
// virtual
void ControlHost::InvalidateChildRect(const LDraw::RectD& rect, const LDraw::Matrix3f transform)
{
	m_pWindow->Invalidate();
#if 0
	if (get_Visibility() != Visible)
		return;

	if (GetRParent())
	{
		// first clip it to our visible bounds
		LDraw::RectD crect;
		LDraw::RectD::Intersect(crect, rect, m_expandedBBox);

		// convert from local space to parent space
		LDraw::gmMatrix3f transform = GetLocalAnimatedMatrix();

		LDraw::RectD xrect;
		GetTransformRectBoundingBox(transform, crect, &xrect);

		GetRParent()->InvalidateChildRect(xrect);
	}
#endif
}
#endif

int GetCommaSepNumberArray(StringW* str, vector<float>& values);

WCHAR* decimal_characters = L"0123456789";

// U+2160 (1) to ? U+216B (12)

WCHAR* upper_roman_characters[] =
{
	L"I",
	L"II",
	L"III",
	L"IV",
	L"V",
	L"VI",
	L"VII",
	L"VIII",
	L"IX",
	L"X",
	L"XI",
	L"XII",
};

int wltoa(WCHAR* deststring, LONGLONG value, int base, int start, const WCHAR* characters)
{
	ASSERT(value >= 0);

	OLECHAR str[64];
	OLECHAR* d = str;

	do
	{
		value = value-start;
		int n = (value/*-start*/) % base;
		value /= base;

		*d++ = characters[n];
	}
	while (value > 0);

// reverse
	int count = d-str;
	int i;
	for (i = 0; i < count; i++)
	{
		deststring[i] = str[count-i-1];
	}
	deststring[i] = 0;	// null-terminate string

	return count;
}

ImmutableString<WCHAR> DisplayRoleIdents[] =
{
	WSTR("none"),
	WSTR("block"),
	WSTR("inline"),
	WSTR("list-item"),
	WSTR("run-in"),
	WSTR("compact"),
	WSTR("table-row"),
	WSTR("table-cell"),
	WSTR("table-row-group"),
	WSTR("table-header-group"),
	WSTR("table-footer-group"),
	WSTR("table-column"),
	WSTR("table-column-group"),
	WSTR("table-caption"),
	WSTR("ruby-text"),
	WSTR("ruby-base"),
	WSTR("ruby-base-group"),
	WSTR("ruby-text-group"),

	NULL
};

ImmutableString<WCHAR> DisplayModelIdents[] =
{
	WSTR("inline-inside"),
	WSTR("block-inside"),
	WSTR("table"),
	WSTR("ruby"),

// Mozilla compliant XUL display modes
	WSTR("box"),

	NULL
};

CSSPrimitiveValue* CreateCSSUnitValue(int propertyIndex, CSSUnitType unit, double value);
CSSPrimitiveValue* CreateCSSUnitStringValue(int propertyIndex, CSSUnitType unit, StringW* value);
CSSPrimitiveValue* CreateCSSUnitRGBValue(int propertyIndex, Graphics::Color value);
SVGPaint* CreateSVGPaintValue(int propertyIndex, CSVGPaint* pPaint);
SVGColor* CreateSVGColorValue(int propertyIndex, CSVGColor* pColor);

bool BitSet::TestBit(int n)
{
	int ndword = n / 32;
	int nbit = n % 32;

	return (m_data[ndword] & (1<<nbit)) != 0;
}

void BitSet::SetBit(int n, bool value)
{
	int ndword = n / 32;
	int nbit = n % 32;

	if (value)
		m_data[ndword] |= (1<<nbit);
	else
		m_data[ndword] &= ~(1<<nbit);
}

FontDef::FontDef()
{
	m_refcount = 0;
	//m_pFont = NULL;
}

FontDef::~FontDef()
{
	//delete m_pFont;
}

FontFamilyDef::FontFamilyDef()
{
	//m_pFamily = NULL;
	m_refcount = 0;
}

FontFamilyDef::~FontFamilyDef()
{
//	delete m_pFamily;
}

//////////////////////////////////////////////////////////////////////////////////
// CScrollBarObject

#if 0
void __stdcall CScrollBarObject::OnScroll(long code, long pos)
{
#if 0
	CComQIPtr<IUIScrollBar> scroll = m_spUnknown;

	long dir;
	scroll->get_direction(&dir);

	CHTMLWindow* pWindow = m_pPElement->m_pWindow;
	ASSERT(pWindow);

	LDraw::RectF textArea = m_pPElement->m_pBox->GetAbsInnerRect();
	textArea.Offset(pWindow->m_client.left, pWindow->m_client.top);

	CRect rect((int)textArea.X, (int)textArea.Y, (int)textArea.GetRight(), (int)textArea.GetBottom());

	ASSERT(0);
	HWND hwnd = NULL;//pWindow->m_pUI->m_hWnd;

	long oldpos; scroll->get_pos(&oldpos);

	scroll->set_pos(pos);

// Could possibly optimize here, if 'background' is 'scroll'	and
// there are no windowed objects inside the element
	if (FALSE)
	{
		if (dir == 0)
		{
			ScrollWindow(hwnd, (oldpos-pos)*1, 0, &rect, &rect);
		}
		else
		{
			ScrollWindow(hwnd, 0, (oldpos-pos)*1, &rect, &rect);
		}
	}
	else
	{
		::InvalidateRect(hwnd, &rect, TRUE);
		//::UpdateWindow(hwnd);
	}

	m_pPElement->PlaceControls(NULL/*hWndParent*/, NULL);
#endif
}
#endif

////////////////////////////////////////////////////////////////////////////
// PElementBase

PElementBase::PElementBase(Element* element) : PNode(element), m_PropertyValid(CSSPropertyCount), m_PropertyDependantOnParent(CSSPropertyCount)
{
	m_type = NODE_ELEMENT;
	m_pElement = element;	// Same as m_pNode
	m_pNode = m_pElement;

	m_eventTarget = NULL;

	m_pBox = NULL;

	m_bArrangeValid = false;

#if 0
	m_pStackingContext = NULL;
	m_pLocalStackingContext = NULL;
#endif

	m_customBlockTop = 0;
	m_customBlockBottom = 0;

	m_contentSize.Width = 0;
	m_contentSize.Height = 0;

	m_pStartTagBox = NULL;
	m_pEndTagBox = NULL;

	m_pOverrideStyle = NULL;

	m_declMatches = NULL;

	m_bCSSPropertiesValid = false;
	m_bCSSPropertiesValid2 = false;

// Cached CSS values (set to undefined)
	m_computedFontSize = -1;
	m_computedLineHeight = -1;

	m_specifiedLeft = -999999;
	m_specifiedTop = -999999;
	m_specifiedRight = -999999;
	m_specifiedBottom = -999999;
//	m_specifiedWidth = -999999;
//	m_specifiedHeight = -999999;

	m_computedLeft = 0;//-999999;
	m_computedTop = 0;//-999999;
	m_computedRight = -999999;
	m_computedBottom = -999999;
	m_computedWidth = -999999;
	m_computedHeight = -999999;

	m_computedMargin[0] = m_computedMargin[1] = m_computedMargin[2] = m_computedMargin[3] = -999999;
	m_computedBorderWidth[0] = m_computedBorderWidth[1] = m_computedBorderWidth[2] = m_computedBorderWidth[3] = -999999;
	m_computedPadding[0] = m_computedPadding[1] = m_computedPadding[2] = m_computedPadding[3] = -999999;
	m_computedBorderStyle[0] = m_computedBorderStyle[1] = m_computedBorderStyle[2] = m_computedBorderStyle[3] = BorderStyle_none;

	m_computedOverflowX = Overflow_visible;
	m_computedOverflowY = Overflow_visible;

	m_bVScroll = false;
	m_bHScroll = false;

//	m_bProtectBox = false;

	m_bHover = false;
	m_bActive = false;
	m_bFocus = false;
	m_bEnabled = true;
	m_bChecked = false;
	m_bIndeterminate = false;

	m_pBackgroundImage = nullptr;

	m_pColorBrush = nullptr;

#if WIN32
	m_hCursor = nullptr;
#endif

	m_pCursorUriElement = nullptr;

	m_pColorProfile = nullptr;

//
#if 0
	m_pBehaviorViewSite = NULL;
#endif

	m_tableColumns = nullptr;

	m_shadowTree = nullptr;
	m_bindNode = nullptr;
	m_pBindNode = nullptr;

	m_pseudoElementName = nullptr;

//	m_pBeforePseudoElement = NULL;
//	m_pMarkerPseudoElement = NULL;
	m_pseudoElements[0] = nullptr;
	m_pseudoElements[1] = nullptr;
	m_pseudoElements[2] = nullptr;
	m_pseudoElements[3] = nullptr;
	m_pseudoElements[4] = nullptr;
	//m_pseudoElements[5] = NULL;

//	ASSERT(0);
	m_pComputedStyle = nullptr;
#if 0
// TODO, create on demand?
	CComObject<CLCSSComputedStyleDeclaration>::CreateInstance(&m_pComputedStyle);
	//if (FAILED(hr)) return hr;
	m_pComputedStyle->AddRef();
	m_pComputedStyle->m_pPElement = this;

	CComObject<CLCSSStyleDeclaration>::CreateInstance(&m_pOverrideStyle);
	m_pOverrideStyle->AddRef();
#endif


//	m_pC = NULL;
	m_lastindex = 0;

	m_bHasBlockChild = 3/*(unsigned)-1*/;
}

PElementBase::~PElementBase()
{
#if 0
	if (m_pBehaviorViewSite)
	{
		for (int i = m_behaviors.GetSize()-1; i >= 0; i--)
		{
			CPBehavior* pBehavior = m_behaviors[i];

			pBehavior->m_p->Detach();

			delete pBehavior;
			m_behaviors.RemoveAt(i);
		}

		m_pBehaviorViewSite->Release();
		m_pBehaviorViewSite = NULL;
	}
#endif

	if (m_shadowTree)
	{
//		m_shadowTree->Release();
		m_shadowTree = NULL;
	}

#if 0
	if (m_scrollX)
	{
#if 0
		m_scrollX->IDispEventImpl<1, CScrollBarObject, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_scrollX->m_spUnknown);
		m_scrollX->ReleaseAll();
		m_scrollX->Release();
		m_scrollX = NULL;
#endif
	}

	if (m_scrollY)
	{
#if 0
		m_scrollY->IDispEventImpl<1, CScrollBarObject, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_scrollY->m_spUnknown);
		m_scrollY->ReleaseAll();
		m_scrollY->Release();
		m_scrollY = NULL;
#endif
	}
#endif

	if (m_tableColumns)
	{
		delete m_tableColumns;
		m_tableColumns = NULL;
	}

	RemoveBoxes();
	RemoveChildren();

#if 0	// Unused stacking context stuff ??
	// hm...
	if (m_parent)
	{
		if (m_parent->m_pStackingContext)	// ???
		{
			ASSERT(m_parent->m_pStackingContext);
			ASSERT(0);
#if 0
			m_parent->m_pStackingContext->RemoveElement(this);
#endif
		}
	}

	if (m_pLocalStackingContext)
	{
		delete m_pLocalStackingContext;
		m_pLocalStackingContext = NULL;
	}
#endif

	/*
	{
		for (int i = 0; i < m_declMatches.GetSize(); i++)
		{
			delete m_declMatches[i];
		}
		m_declMatches.RemoveAll();
	}
	*/
	//m_declMatches.Release();
//

#if 0
	ASSERT(m_pBox == NULL);
	ASSERT(m_boxList.GetSize()==0);
#endif

	if (m_pBox)
	{
		m_pBox->Release();
		//m_pBox->DeleteChildBoxes();
	}

	for (int i = 0; i < m_boxList.GetSize(); i++)
	{
		m_boxList[i]->Release();
	}

	if (m_pComputedStyle)
	{
		m_pComputedStyle->m_pPElement = NULL;
	//	m_pComputedStyle->Release();
		m_pComputedStyle = NULL;
	}

	if (m_pOverrideStyle)
	{
	//	m_pOverrideStyle->Release();
		m_pOverrideStyle = NULL;
	}

	if (m_pBackgroundImage)
	{
	//	g_Images.RemoveImage(m_pBackgroundImage);
		m_pBackgroundImage = NULL;
	}

	/*
	if (m_pColorBrush)
	{
		delete m_pColorBrush;
		m_pColorBrush = NULL;
	}
	*/

	{
		for (int i = 0; i < m_computedFont.GetSize(); i++)
		{
			m_computedFont[i]->Release();
		}
		m_computedFont.RemoveAll();
	}
}

void PElementBase::SetCapture()
{
}

void PElementBase::ReleaseCapture()
{
}

#if 0
void PElementBase::InvalidateRegion(LDraw::Region* pRgn)
{
	ASSERT(0);
#if 0
	// ???
	//m_pWindow->InvalidateRender();
	m_pWindow->ArrangeOverride(m_pWindow->get_ActualSize());
#endif
}
#endif

PElementBase* PElementBase::HitTestElement(gm::Matrix3d* matrix, gm::PointD pt)
{
	return NULL;
}

String PElementBase::get_typeName()
{
	String nodeName = m_pNode->get_localName();
	if (nodeName == nullptr)//->Length() == 0)
	{
		nodeName = m_pNode->get_nodeName();
	}
	return nodeName;
}

Style::IStyleDeclaration* PElementBase::get_inlineStyle(uint index)
{
	IElementCSSInlineStyle* inlineStyle = dynamic_cast<IElementCSSInlineStyle*>(m_pNode);
	if (inlineStyle)
	{
		return inlineStyle->get_style();
	}

	return NULL;
}

String PElementBase::get_namespaceURI()
{
	return m_pNode->get_namespaceURI();
}

bool PElementBase::hasAttribute(StringIn name)
{
	Element* element = dynamic_cast<Element*>(m_pNode);
	return element->hasAttribute(name);
}

String PElementBase::getAttribute(StringIn name)
{
	Element* element = dynamic_cast<Element*>(m_pNode);
	return element->getAttribute(name);
}

String PElementBase::get_id()
{
	Element* element = dynamic_cast<Element*>(m_pNode);
	return element->getAttribute(WSTR("id"));
}

Style::ICSSElementResolver* PElementBase::get_prevSibling()
{
	Style::ICSSElementResolver* prev = NULL;
	for (int i = 0; i < m_rparent->m_rchildList.GetSize(); i++)
	{
		PNode* pNode = m_rparent->m_rchildList[i];
		if (pNode == this)
			break;

		if (pNode->m_type == NODE_ELEMENT)
			prev = dynamic_cast<PElementBase*>(pNode);
	}

	return prev;
#if 0
	UPOSITION pos = m_rparent->m_childList.Find(this);
	m_rparent->m_childList.GetPrev(pos);
	if (pos)
	{
		*pVal = (PElementBase*)m_rparent->m_childList.GetAt(pos);
		(*pVal)->AddRef();
	}
#endif
	return NULL;
}

Style::ICSSElementResolver* PElementBase::get_nextSibling()
{
	ASSERT(0);
#if 0
	UPOSITION pos = m_rparent->m_childList.Find(this);
	m_rparent->m_childList.GetNext(pos);
	if (pos)
	{
		return (PElementBase*)m_rparent->m_childList.GetAt(pos);
		(*pVal)->AddRef();
	}
#endif

	return NULL;
}

vector<PNode*>& PElementBase::GetChildList()
{
	/*
	if (m_shadowTree)
	{
		return m_shadowTree->m_childList;
	}
	else
		return m_childList;
		*/
	return m_rchildList;
}

//virtual
void PElementBase::ReferenceInvalid(PElementBase/*PSVGElement*/ * pPElement)
{
}

/*
int FinalConstruct()
{
	HRESULT hr;

	return 0;
}

void PElementBase::FinalRelease()
{
	if (m_pComputedStyle)
	{
		m_pComputedStyle->m_pPElement = NULL;
		m_pComputedStyle->Release();
		m_pComputedStyle = NULL;
	}
}
*/
void PElementBase::CreateBehaviors()
{
#if 0
	if (m_pBehaviorViewSite == NULL)
	{
		CComObject<CLElementBehaviorViewSite>::CreateInstance(&m_pBehaviorViewSite);
		if (m_pBehaviorViewSite)
		{
			m_pBehaviorViewSite->AddRef();
			m_pBehaviorViewSite->m_pPElement = this;
			m_pBehaviorViewSite->m_pWindow = m_pWindow;
		}
	}

	CComQIPtr<CLDOMElementImplImpl> pElement = CComQIPtr<CLDOMElementImplImpl>(m_pNode);

	if (m_pBehaviorViewSite)
	{
		for (int i = 0; i < pElement->m_behaviors.GetSize(); i++)
		{
			CComQIPtr<ILElementBehaviorFactory> factory = pElement->m_behaviors[i]->m_factory;
			//ASSERT(factory);
			if (factory)
			{
				if (!wcsncmp(pElement->m_behaviors[i]->m_url, OLESTR("#factory#", 9))
				{
					BSTR name = (BSTR)(pElement->m_behaviors[i]->m_url)+9;

					CComPtr<ILElementBehaviorView> behavior;
					factory->FindBehavior(name, pElement->m_behaviors[i]->m_url, m_pBehaviorViewSite, &behavior);
					if (behavior)
					{
						CPBehavior* pBehavior = new CPBehavior;
						m_behaviors.Add(pBehavior);
						if (SUCCEEDED(behavior->Init(m_pBehaviorViewSite)))
						{
							pBehavior->m_p = behavior;
						}
					}
				}
			}
			else
			{
				CComQIPtr<ILElementBehaviorView> behavior = pElement->m_behaviors[i]->m_factory;
				if (behavior)
				{
					CPBehavior* pBehavior = new CPBehavior;
					m_behaviors.Add(pBehavior);
					if (SUCCEEDED(behavior->Init(m_pBehaviorViewSite)))
					{
						pBehavior->m_p = behavior;
					}
				}
			}
		}
	}
#endif
}

PElementBase* PElementBase::GetElementById(StringIn id)
{
	ASSERT(0);
#if 0
// ?? Use GetChildList() here? (The DOM doesn't, but I think maybe I should do it here)
	UPOSITION pos = GetChildList().GetHeadPosition();
	while (pos)
	{
		PNode* pNode = (PNode*)GetChildList().GetNext(pos);

		//CComQIPtr<ILDOMElement> element = pNode->m_pNode;
		if (pNode->m_type == NODE_ELEMENT)//element)
		{
			PElementBase* pElement = (PElementBase*)pNode;

			sysstring elementid = get_id();

			if (elementid.length() > 0)
			{
				if (elementid == id)
				{
					return pElement;
				}
			}

			PElementBase* pF = pElement->GetElementById(id);
			if (pF)
				return pF;
		}
	}
#endif
	return NULL;
}

WEBEXT PElementBase* GetElementById(PElementBase* p, StringW* id)
{
	ASSERT(0);
#if 0
// ?? Use GetChildList() here? (The DOM doesn't, but I think maybe I should do it here)
	UPOSITION pos = p->m_childList.GetHeadPosition();
	while (pos)
	{
		PNode* pNode = (PNode*)p->m_childList.GetNext(pos);

		//CComQIPtr<ILDOMElement> element = pNode->m_pNode;
		if (pNode->m_type == NODE_ELEMENT)//element)
		{
			PElementBase* pElement = (PElementBase*)pNode;

			sysstring elementid = pElement->get_id();//element->getAttribute(OLESTR("id", &elementid);

			if (elementid.length() > 0)
			{
				if (elementid == id)
				{
					return pElement;
				}
			}

			PElementBase* pF = GetElementById(pElement, id);
			if (pF)
				return pF;
		}
	}
#endif
	return NULL;
}

PElementBase* PElementBase::GetElementByTagNameNS(StringIn namespaceURI, StringIn tagName, bool bDeep/* = TRUE*/)
{
	for (int i = 0; i < m_childList.GetSize(); i++)
	//while (pos)
	{
		PNode* pNode = m_childList[i];//.GetNext(pos);

		//CComQIPtr<ILDOMElement> element = pNode->m_pNode;
		if (pNode->m_type == NODE_ELEMENT)//element)
		{
			PElementBase* pElement = (PElementBase*)pNode;

			String etagName = pElement->get_typeName();
#if 0
			sysstring etagName = element->get_localName(&etagName);	// Try local name first
			if (etagName.length() == 0)
			{
				etagName = element->get_tagName();	// Then try full qualified name
			}
#endif
			if (etagName == tagName)
			{
				String enamespaceURI = pElement->get_namespaceURI();

				if (enamespaceURI == namespaceURI)
				{
					return pElement;
				}
			}

			if (bDeep)
			{
				PElementBase* pF = pElement->GetElementByTagNameNS(namespaceURI, tagName, true);
				if (pF)
					return pF;
			}
		}
	}

	return NULL;
}

#if 0
PNode* PElementBase::FindDOMElement(ILDOMNode* find)
{
	if (m_pNode == find) return this;

	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		PNode* pParent = (PNode*)m_childList.GetNext(pos);

		if (pParent->m_pNode == find) return pParent;

		if (pParent->m_type == NODE_ELEMENT)
		{
			PNode* pFound = ((PElementBase*)pParent)->FindDOMElement(find);
			if (pFound) return pFound;
		}
	}

	return NULL;
}
#endif

int PElementBase::GetLevel()
{
	int level = 0;
	PElementBase* p = m_rparent;
	while (p)
	{
		++level;
		p = p->m_rparent;
	}

	return level;
}

void PElementBase::RemoveChildren()
{
//	m_boxList.RemoveAll();	// ???

	MessageBeep(-1);
	//ASSERT(0);
#if 0
	while (!m_childList.IsEmpty())
	{
		PNode* pItem = (PNode*)m_childList.RemoveHead();
	//	pItem->Release();
	}

	ASSERT(m_childList.IsEmpty());

	m_rchildList.RemoveAll();	// ??
#endif
}

//virtual
void PElementBase::CalculateBoundsAndChildren()
{
	if (m_pStartTagBox)
	{
		delete m_pStartTagBox;
		m_pStartTagBox = NULL;
	}

	if (m_pEndTagBox)
	{
		delete m_pEndTagBox;
		m_pEndTagBox = NULL;
	}

	if (false)//m_pWindow->m_bShowMarkup)
	{
		m_pStartTagBox = new CMarkupBox;
		m_pStartTagBox->m_start = 1;
		m_pStartTagBox->m_pElement = this;
		m_pStartTagBox->AddRef();
		m_pStartTagBox->CalculateDimensions(NULL);

		m_pEndTagBox = new CMarkupBox;
		m_pEndTagBox->m_start = 0;
		m_pEndTagBox->m_pElement = this;
		m_pEndTagBox->AddRef();
		m_pEndTagBox->CalculateDimensions(NULL);
	}

	PNode** pos = m_rchildList.GetData();
	while (pos != m_rchildList.GetData() + m_rchildList.GetSize())
	{
		PNode* pChildElement = *pos++;

		if (pChildElement->m_type == NODE_ELEMENT)
		{
			((PElementBase*)pChildElement)->CalculateBoundsAndChildren();
		}
		else if (pChildElement->m_type == NODE_TEXT)
		{
			((PText*)pChildElement)->CalculateBoundsAndChildren();
		}
	}

	if (m_computedDisplayRole == DisplayRole_table_cell)
	{
		ASSERT(0);
		CalculateMinMaxDimensions();
	}
}

void PElementBase::AddBox(CHTMElementBox/*CHTMBoxItem*/ * pBox)
{
#ifdef _DEBUG
	for (int i = 0; i < m_boxList.size(); i++)
	{
		ASSERT(m_boxList[i] != pBox);
	}
#endif

	m_boxList.Add(pBox);
}

// Just like OnDestroy() for windows ???
// virtual
void PElementBase::OnRemoveBox(CHTMElementBox* pBox)
{
	ASSERT(pBox);

	if (pBox == m_pBox)
	{
#ifdef _DEBUG
#if 0
		if (m_bProtectBox)
		{
			MessageBeep(-1);
		}
#endif
			// m_pBox isn't in the list
		for (int i = 0; i < m_boxList.size(); i++)
		{
			ASSERT(m_boxList[i] != m_pBox);
		}
#endif

		m_pBox = NULL;
	}
	else
	{
		RemoveBox(pBox);
	}
	/*
	if (m_pBox == pBox)
	{
		m_pBox = NULL;
	}
	*/

	// TODO, have this pBox->Release() ??
}

void PElementBase::RemoveBox(CHTMElementBox* pBox)
{
	ASSERT(pBox != m_pBox);	// m_pBox shouldn't be in this list

//	std::vector<CHTMElementBox*, myallocator<CHTMElementBox*> >::iterator it = m_boxList.begin();
//	while (it != m_boxList.end())
	for (int i = 0; i < m_boxList.GetSize(); i++)
	{
		if (m_boxList[i] == pBox)
		{
			m_boxList.RemoveAt(i);//erase(it);
			return;
		}
		//it++;
	}
	/*
	std::
	for (int i = 0; i < m_boxList.size(); i++)
	{
		if (m_boxList[i] == pBox)
		{
			m_boxList.erase(pBox);
			return;
		}
	}
	*/

	MessageBeep(-1);
	//ASSERT(0);
}

void PElementBase::RemoveBoxes()
{
#if 0
	m_pBox = NULL;
#endif

	if (m_pBox)
	{
		CHTMElementBox* pBox = m_pBox;
		pBox->Destroy();
	//	ASSERT(m_pBox == NULL);

		int refcount = pBox->Release();
		ASSERT(refcount == 0);	// ??
	}
}

void PElementBase::RemoveBoxesAndChildren()
{
#if 0	// Had this
	if (m_pBox)
	{
		m_pBox->Destroy();
		ASSERT(m_pBox == NULL);
	}
#endif

	if (m_shadowTree)
	{
#if 1
		m_shadowTree->RemoveBoxesAndChildren();
#endif
	}

	RemoveChildBoxes();

	RemoveBoxes();
}

void PElementBase::RemoveChildBoxes()
{
#if 1
//	std::vector<PNode*, myallocator<PNode*> >::iterator pos = m_rchildList.begin();
//	while (pos != m_rchildList.end())
	{
		for (int i = 0; i < m_rchildList.GetSize(); i++)
		{
			PElementBase* pElement = (PElementBase*)m_rchildList[i];//(PElementBase*)*pos++;//m_rchildList.GetNext(pos);
			if (pElement->m_type == NODE_ELEMENT)
			{
				pElement->RemoveBoxesAndChildren2();
			}
		}
	}

#if 0	// ??
	{
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		PElementBase* pElement = (PElementBase*)m_childList.GetNext(pos);
		if (pElement->m_type == NODE_ELEMENT)
		{
			pElement->RemoveBoxesAndChildren2();
		}
	}
	}
#endif
#endif

	for (int i = m_boxList.GetSize()-1; i >= 0; i--)
	{
		CHTMElementBox* pBox = m_boxList[i];
		ASSERT(pBox != m_pBox);	// m_pBox shouldn't be in this list
		pBox->Destroy();
#if 0
		m_boxList[i]->m_pElement = NULL;

		if (m_boxList[i]->m_parentBox)
		{
			m_boxList[i]->m_parentBox->RemoveChildBox(m_boxList[i]);
		}
#endif
#if 0	// Destroy Above does a release ?
		pBox->Release();
#endif
	}

#if 0
	m_boxList.RemoveAll();
#endif

// ???? Boxes should be removed before element gets destroyed
//	ASSERT(m_boxList.size() == 0);
}

// Called from parent (you may override this to do nothing)
// virtual
void PElementBase::RemoveBoxesAndChildren2()
{
	RemoveBoxesAndChildren();
}

void PElementBase::RecalculateParentBounds()
{
	ASSERT(0);
#if 0
// A child has changed, so we reflow our children, and if we need ro resize ourselves
// we let the parent know, recursively

	if (m_pBox)	// hm.. ??
	{
	//	ASSERT(m_bProtectBox == 0);
	//	m_bProtectBox = true;
		RemoveChildBoxes();
	//	m_bProtectBox = false;

		if (m_pBox == NULL)
		{
			MessageBeep(-1);
		}
		ASSERT(m_pBox);	// Make sure it's still there
		m_pBox->DeleteChildBoxes();	// Delete any remaining child boxes

		if (m_pBox->m_children.size() != 0)
		{
			MessageBeep(-1);
		}

		ASSERT(m_pBox->m_children.size() == 0);

		LDraw::RectF outerRect = m_pBox->m_outerRect;
		LDraw::RectF absouterRect = m_pBox->GetAbsOuterRect();

		m_pBox->m_innerRect.X = 0;
		m_pBox->m_innerRect.Y = 0;
		m_pBox->m_innerRect.Width = 0;
		m_pBox->m_innerRect.Height = 0;
		m_pBox->m_outerRect.X = 0;
		m_pBox->m_outerRect.Y = 0;
		m_pBox->m_outerRect.Width = 0;
		m_pBox->m_outerRect.Height = 0;

		CHTMFlowBlockContext pC;// = new CHTMFlowBlockContext;
		pC.m_pElement = this;
	//	DistributeWithinBlock(
		if (m_parent)
			DistributeBlockChildren(&pC, (m_parent->m_pBox)? m_parent->m_pBox->m_innerRect.Width: 1024/*m_parent->m_computedWidth*/);
		else
			DistributeBlockChildren(&pC, outerRect.Width);

		m_pBox->AdjustOuterRect();

	//	delete pC;

		if (	(outerRect.Width != m_pBox->m_outerRect.Width) ||
				(outerRect.Height != m_pBox->m_outerRect.Height))
		{
		//	ASSERT(0);	// TODO, mark this element as already distributed
			if (m_parent)
			{
				m_parent->RecalculateParentBounds();
			}
		}
		else
		{
			/*
			if (outerRect.Y != 0)
			{
				MessageBeep(-1);
			}
			*/

			// Move to original position
			m_pBox->m_outerRect.Offset(outerRect.X, outerRect.Y);

			//LDraw::RectF::Union(rc, absouterRect, absouterRect2);

			ASSERT(0);
#if 0
			if (m_hWndParent)
			{
				ASSERT(::IsWindow(m_hWndParent));

				LDraw::RectF absouterRect2 = m_pBox->GetAbsOuterRect();

				{
					LDraw::RectF& rc = absouterRect;
					::InvalidateRect(m_hWndParent, &CRect((int)rc.X, (int)rc.Y, (int)ceil(rc.GetRight()), (int)ceil(rc.GetBottom())), TRUE);
				}

				{
					LDraw::RectF& rc = absouterRect2;
					::InvalidateRect(m_hWndParent, &CRect((int)rc.X, (int)rc.Y, (int)ceil(rc.GetRight()), (int)ceil(rc.GetBottom())), TRUE);
				}

				PlaceControls(m_hWndParent, NULL);
			}
#endif
		}
	}
	else
	{
		if (m_parent)
		{
			m_parent->RecalculateParentBounds();
		}
	}
#endif
}

/////////////////////
// element box creation

CHTMBlockBox* PElementBase::CreateBlockBox()
{
	ASSERT(m_pBox == NULL);	// debug for now

	CHTMBlockBox* pBox = new CHTMBlockBox;
//	pBox->AddRef();
	pBox->m_pElement = this;

#if 1	// TODO, remove from here
	pBox->m_computedMargin[0] = m_computedMargin[0];
	pBox->m_computedMargin[1] = m_computedMargin[1];
	pBox->m_computedMargin[2] = m_computedMargin[2];
	pBox->m_computedMargin[3] = m_computedMargin[3];
	
	pBox->m_computedPadding[0] = m_computedPadding[0];
	pBox->m_computedPadding[1] = m_computedPadding[1];
	pBox->m_computedPadding[2] = m_computedPadding[2];
	pBox->m_computedPadding[3] = m_computedPadding[3];

	pBox->m_computedBorderWidth[0] = m_computedBorderWidth[0];
	pBox->m_computedBorderWidth[1] = m_computedBorderWidth[1];
	pBox->m_computedBorderWidth[2] = m_computedBorderWidth[2];
	pBox->m_computedBorderWidth[3] = m_computedBorderWidth[3];

	pBox->m_computedBackgroundColor = m_computedBackgroundColor;
	pBox->m_pBackgroundImage = m_pBackgroundImage;

	pBox->m_opacity = (uint8)(m_computedOpacity*255);
#endif

#if 0	// it could be m_pBox we're creating, and it shouldn't be added to the list
	// so must be explicitly added if that's the intention
	AddBox(pBox);
#endif

	return pBox;
}

CHTMBlockBox* PElementBase::CreateAnonymousBlockBox()
{
	CHTMBlockBox* pBox = new CHTMBlockBox;
//	pBox->AddRef();
	pBox->m_pElement = this;

	AddBox(pBox);

	return pBox;
}

CHTMInlineBox* PElementBase::CreateInlineBox()
{
	CHTMInlineBox* pBox = new CHTMInlineBox;
//	pBox->AddRef();
	pBox->m_pElement = this;

	pBox->m_computedMargin[0] = m_computedMargin[0];
	pBox->m_computedMargin[1] = m_computedMargin[1];
	pBox->m_computedMargin[2] = m_computedMargin[2];
	pBox->m_computedMargin[3] = m_computedMargin[3];
	
	pBox->m_computedPadding[0] = m_computedPadding[0];
	pBox->m_computedPadding[1] = m_computedPadding[1];
	pBox->m_computedPadding[2] = m_computedPadding[2];
	pBox->m_computedPadding[3] = m_computedPadding[3];

	pBox->m_computedBorderWidth[0] = m_computedBorderWidth[0];
	pBox->m_computedBorderWidth[1] = m_computedBorderWidth[1];
	pBox->m_computedBorderWidth[2] = m_computedBorderWidth[2];
	pBox->m_computedBorderWidth[3] = m_computedBorderWidth[3];

	pBox->m_computedBackgroundColor = m_computedBackgroundColor;
#if 0
	pBox->m_pBackgroundImage = pBox->m_pElement->m_pBackgroundImage;
#endif

	AddBox(pBox);

	return pBox;
}

CHTMInlineBox* PElementBase::CreateAnonymousInlineBox()
{
	CHTMInlineBox* pBox = new CHTMInlineBox;
//	pBox->AddRef();
	pBox->m_pElement = this;

	AddBox(pBox);

	return pBox;
}

#if 0
// virtual
int CHTMPElement::GetCachedComputedProperty(int propertyIndex, CSSValue** value)
{
/*	switch (propertyIndex)
	{
	}
*/
	return PElementBase::GetCachedComputedProperty(propertyIndex, value);
}
#endif

#if 0
void ControlHost::OnButtonDown(LDraw::PointD clientpt)
{
	Visual* pVisual = m_Content->HitTestElement(gmMatrix3::identity(), clientpt);
	if (pVisual)
	{
		CLXUIMouseEvent* mouseEvt = new CLXUIMouseEvent;
		mouseEvt->InitMouseEvent(OLESTR("mousedown"), 0, 0);
		pVisual->dispatchEvent(mouseEvt);
	}
}
#endif

void CHTMBlockBox::DrawScrollBars(CHTMRenderContext* pC)
{
	if (m_scrollY || m_scrollX)
	{
	//	HDC hDC = pC->m_pGraphics->GetHDC();

#if 0
		OffsetViewportOrgEx(hDC, -pC->m_clip.X, -pC->m_clip.Y, NULL);
#endif

		if (m_scrollY)
		{
		//	ASSERT(0);
#if 0
			pC->m_pGraphics->PushTransform();
			pC->m_pGraphics->MultiplyTransform(m_scrollY->GetParentToElementTransformMatrix());

			m_scrollY->CreateOpaqueRegionNoTransform(pC->m_pGraphics);

			m_scrollY->m_visibleRegion = new LDraw::Region(m_scrollY->m_expandedBBox, pC->m_pGraphics->GetTransform()->m_matrix, 10, true);
			m_scrollY->m_visibleWithChildrenRegion = m_scrollY->m_visibleRegion;

			pC->m_pGraphics->PopTransform();

			m_scrollY->CreateLayerStuff(pC->m_pGraphics);

			m_scrollY->/*m_pContent->*/Render(pC->m_pGraphics);

#if 0
			if (m_scrollY->m_bWindowless)
			{
				/*
				RECTL	rectl;
				rectl.left = m_scrollBars->m_olescrollY->m_rcPos.left;
				rectl.top = m_scrollBars->m_olescrollY->m_rcPos.top;
				rectl.right = m_scrollBars->m_olescrollY->m_rcPos.right;
				rectl.bottom = m_scrollBars->m_olescrollY->m_rcPos.bottom;
				*/
				/*
				BITMAPINFOHEADER* lpbmi = GlobalAlloc(GMEM_ZEROINIT, sizeof(BITMAPINFOHEADER));
				m_lpbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				m_lpbmi->bmiHeader.biWidth = clip.Width();
				m_lpbmi->bmiHeader.biHeight = -clip.Height();
				m_lpbmi->bmiHeader.biBitCount = 24;
				m_lpbmi->bmiHeader.biPlanes = 1;

				HBITMAP hTBitmap;
				LPBYTE TBits = NULL;

				if (hTBitmap = CreateDIBSection(NULL, m_lpbmi, DIB_RGB_COLORS, (void**)&TBits, NULL, 0))
					long scrollposX; m_horz->get_pos(&scrollposX);
					long scrollposY; m_vert->get_pos(&scrollposY);

					HDC hTDC = CreateCompatibleDC(NULL);
					HBITMAP hOldBitmap = (HBITMAP)SelectObject(hTDC, hTBitmap);
					*/

				

				DVASPECTINFO	dv;
				dv.cb = sizeof(dv);
				dv.dwFlags = 0;

				HRESULT hr = m_scrollY->m_spViewObject->Draw(DVASPECT_CONTENT, -1, &dv, NULL, NULL,
					hDC,
					NULL,//&rectl,
					NULL,//&rectl,
					NULL,//continueDraw,
					0 // value to pass to callback function
					);
			}
#endif
#endif
		}

		if (m_scrollX)
		{
#if 0
			m_scrollX->Render(pC->m_pGraphics);
#endif
#if 0
			if (m_scrollX->m_bWindowless)
			{
				/*
				RECTL	rectl;
				rectl.left = m_scrollBars->m_olescrollY->m_rcPos.left;
				rectl.top = m_scrollBars->m_olescrollY->m_rcPos.top;
				rectl.right = m_scrollBars->m_olescrollY->m_rcPos.right;
				rectl.bottom = m_scrollBars->m_olescrollY->m_rcPos.bottom;
				*/

				DVASPECTINFO	dv;
				dv.cb = sizeof(dv);
				dv.dwFlags = 0;

				HRESULT hr = m_scrollX->m_spViewObject->Draw(DVASPECT_CONTENT, -1, &dv, NULL, NULL,
					hDC,
					NULL,//&rectl,
					NULL,//&rectl,
					NULL,//continueDraw,
					0 // value to pass to callback function
					);
			}
#endif
		}
#if 0
		OffsetViewportOrgEx(hDC, pC->m_clip.X, pC->m_clip.Y, NULL);
#endif

	//	pC->m_pGraphics->ReleaseHDC(hDC);
	}
}

#if 0
void PElementBase::DoScroll(CHTMRenderContext* pC)
{
	POINT org;
	org.x = 0;
	org.y = 0;

	if (m_scrollX)
	{
#if 0
		CComQIPtr<IUIScrollBar> scrollX = m_scrollX->m_spUnknown;
		long pos; scrollX->get_pos(&pos);
		org.x = -pos;
#endif
	}

	if (m_scrollY)
	{
#if 0
		CComQIPtr<IUIScrollBar> scrollY = m_scrollY->m_spUnknown;
		long pos; scrollY->get_pos(&pos);
		org.y = -pos;
#endif
	}

	pC->m_pGraphics->TranslateTransform(org.x, org.y);
//	OffsetViewportOrgEx(pC->m_pGraphics->GetHDC(), org.x, org.y, NULL);

	pC->m_clip.Offset(-org.x, -org.y);
//	LDraw::Rect::Intersect(pC->m_clip, m_oldclip, boxdim);
}
#endif

void PElementBase::Draw(CHTMRenderContext* pC)
{
	if (true)
	{
#if 0
		CComQIPtr<CLDOMElementImplImpl> elementImpl = m_pNode;

		if (elementImpl)	// TODO.. hm.. this should be XAML ILVisual or something
		{
			for (int i = 0; i < elementImpl->m_behaviors.GetSize(); i++)
			{
				CComQIPtr<ILHTMLPainter> htmlPainter = elementImpl->m_behaviors[i]->m_factory;

				if (htmlPainter)
				{
					CComPtr<ILCanvas> canvas;
					canvas.CoCreateInstance(CLSID_LCanvas);

					LDraw::RectF rcf = m_pBox->GetAbsInnerRect();

					pC->m_pGraphics->TranslateTransform(rcf.X, rcf.Y);

					canvas->SetGdip((long)pC->m_pGraphics);

					htmlPainter->Draw(canvas);

					pC->m_pGraphics->TranslateTransform(-rcf.X, -rcf.Y);
				}
			}
		}
#endif
	}

#if 0
	for (int i = 0; i < m_behaviors.GetSize(); i++)
	{
		CComQIPtr<ILHTMLPainter> htmlPainter = m_behaviors[i]->m_p;

		if (htmlPainter)
		{
			CComPtr<ILCanvas> canvas;
			canvas.CoCreateInstance(CLSID_LCanvas);

			canvas->SetGdip((long)pC->m_pGraphics);

			htmlPainter->Draw(canvas);
		}
	}
#endif

#if 0
	{
		CComPtr<ILDOMNode> startContainer;
		long startOffset;

		CComPtr<ILDOMNode> endContainer;
		long endOffset;

		pC->m_range->get_startContainer(&startContainer);
		pC->m_range->get_startOffset(&startOffset);

		pC->m_range->get_endContainer(&endContainer);
		pC->m_range->get_endOffset(&endOffset);

		if (!pC->m_bInSelection)
		{
//			CComPtr<ILDOMNode> parentNode;
//			m_pNode->get_parentNode(&parentNode);

			if (startContainer == m_pNode)
			{
				//int index = GetDOMNodesIndex();

				//if (index == startOffset)
				{
					pC->m_bInSelection++;
				}
			}

			/*
			if (startContainer == m_pNode)
			{
				pC->m_bInSelection = TRUE;
			}
			*/
		}
	}
#endif

	if (m_pBox)
	{

	//	m_hDCState = pC->m_pGraphics->Save();

//		LDraw::Rect boxdim = m_pBox->GetAbsInnerRect();

		// ??
		if (m_computedDisplayRole == DisplayRole_list_item)
		{
			gm::RectF rc = m_pBox->GetAbsInnerRect();
		//	LDraw::RectF rc = m_pBox->m_innerRect;
		//	rc.Offset(pC->m_outerPos.X, pC->m_outerPos.Y);

			ASSERT(0);
#if 0
			pC->m_pGraphics->FillEllipse(new LDraw::SolidBrush(LDraw::Color(0,0,0)), rc.X-8, rc.Y, 6.0, 6.0);
#endif
		}

	// ??
#if 0
		{
			LDraw::Rect rc = m_pBox->m_innerRect;
			rc.Offset(pC->m_outerPos.X, pC->m_outerPos.Y);

			BSTR nodeName;
			m_pNode->get_nodeName(&nodeName);

			TRACE("IntersectClip: %S, %d,%d,%d,%d\n", nodeName, rc.X, rc.Y, rc.Width, rc.Height);

		//	pC->m_pGraphics->IntersectClip(rc/*m_pBox->GetAbsOuterRect()*/);
		}
#endif

	}
}

void PElementBase::EndDraw(CHTMRenderContext* pC)
{
	if (m_pBox)
	{
#if 0
		for (int i = 0; i < m_behaviors.GetSize(); i++)
		{
			CComQIPtr<IHTMLPainter> htmlPainter = m_behaviors[i]->m_p;

			if (htmlPainter)
			{
				CRect rcBounds(0, 0, m_pBox->m_outerRect.Width, m_pBox->m_outerRect.Height);
				CRect rcUpdate(0, 0, m_pBox->m_outerRect.Width, m_pBox->m_outerRect.Height);

				long lDrawFlags = 0;	// HTMLPAINT_DRAW_UPDATEREGION = 0x000001,
									  //  HTMLPAINT_DRAW_USE_XFORM = 0x000002

				HDC hdc = pC->m_pGraphics->GetHDC();
				htmlPainter->Draw(rcBounds, rcUpdate, lDrawFlags, hdc, NULL);
				pC->m_pGraphics->ReleaseHDC(hdc);
			}
		}
#endif
	}

#if 0
	if (pC->m_range)
	{
		CComPtr<ILDOMNode> startContainer;
		long startOffset;

		CComPtr<ILDOMNode> endContainer;
		long endOffset;

		pC->m_range->get_startContainer(&startContainer);
		pC->m_range->get_startOffset(&startOffset);

		pC->m_range->get_endContainer(&endContainer);
		pC->m_range->get_endOffset(&endOffset);

		if (pC->m_bInSelection)
		{
		//	CComPtr<ILDOMNode> parentNode;
		//	m_pNode->get_parentNode(&parentNode);

			if (endContainer == m_pNode)
			{
			//	int index = GetDOMNodesIndex();

				//if (index == endOffset)
				{
					pC->m_bInSelection--;
				}
			}

		/*
			if (endContainer == m_pNode)
			{
				pC->m_bInSelection = FALSE;
			}
			*/
		}
	}
#endif

#if 0
	if (m_hDCState)
	{
//		pC->m_pGraphics->Restore(m_hDCState);
		m_hDCState = 0;
	}
#endif
}

void PElementBase::OnButtonDown(gm::PointD screenpt, gm::PointD point, int nhit)
{
	if (m_pBox)	// TODO, shouldn't have to check for this ???
	{
		point = m_pBox->ScreenToClient(point);

	//	LDraw::RectF trect = m_pBox->GetAbsOuterRect();
	//	point.X -= trect.X;
	//	point.Y -= trect.Y;

		if (nhit == 2)
		{
			ASSERT(0);
			//m_pBox->m_scrollY->OnMouseDown(0, screenpt, point, 0, false);
		}
		else if (nhit == 3)
		{
			ASSERT(0);
			//m_pBox->m_scrollX->OnMouseDown(0, screenpt, point, 0, false);
		}
#if 0
		if (m_computedPosition == Position_absolute)
		{
			if (point.x >= trect.X-8 && point.y >= trect.Y-8 &&
				point.x < trect.X && point.y < trect.Y)
			{
				CComQIPtr<ILDOMElement> element = m_pNode;

				CComQIPtr<ILElementCSSInlineStyle> stylable = element;

				CComPtr<ILCSSStyleDeclaration> style;
				stylable->get_style(&style);

				style->setProperty(OLESTR("left", _bstr_t(_variant_t((long)20)), NULL);
				style->setProperty(OLESTR("top", _bstr_t(_variant_t((long)260)), NULL);

				*pVal = this;
				return TRUE;
			}
		}
#endif

#if 0
		if (trect.Contains(point.X, point.Y))
		{
			COleClientItem* pClientItem = NULL;

			if (m_scrollY)
			{
#if 0
				if (PtInRect(&m_scrollY->m_rcPos, point))
				{
					pClientItem = m_scrollY;
				}
#endif
			}

			if (m_scrollX)
			{
#if 0
				if (PtInRect(&m_scrollX->m_rcPos, point))
				{
					pClientItem = m_scrollX;
				}
#endif
			}

			if (pClientItem &&
				pClientItem->m_spInPlaceObjectWindowless &&
				pClientItem->m_bWindowless)
			{
				WPARAM wparam = 0;
				LPARAM lparam = MAKELPARAM(point.x, point.y);

				LRESULT lresult = 0;

				HRESULT hr = pClientItem->m_spInPlaceObjectWindowless->OnWindowMessage(WM_LBUTTONDOWN, wparam, lparam, &lresult);
				if (hr == S_OK)
					return TRUE;
			}
		}
#endif
	}

#if 0
	if (m_rparent)
		return m_rparent->OnButtonDown(point, pVal);
	else
		return FALSE;
#endif
}

void PElementBase::OnButtonUp(gm::PointD screenpt, gm::PointD point, int nhit)
{
//	LDraw::RectF trect = m_pBox->GetAbsOuterRect();
//	point.X -= trect.X;
//	point.Y -= trect.Y;
	point = m_pBox->ScreenToClient(point);

	if (nhit == 2)
	{
		ASSERT(0);
		//m_pBox->m_scrollY->OnMouseUp(0, screenpt, point, 0);
	}
	else if (nhit == 3)
	{
		ASSERT(0);
		//m_pBox->m_scrollX->OnMouseUp(0, screenpt, point, 0);
	}
}

void PElementBase::OnMouseMove(gm::PointD screenpt, gm::PointD point, int nhit)
{
//	LDraw::RectF trect = m_pBox->GetAbsOuterRect();
//	point.X -= trect.X;
//	point.Y -= trect.Y;
	point = m_pBox->ScreenToClient(point);

	if (nhit == 2)
	{
		ASSERT(0);
		//m_pBox->m_scrollY->OnMouseMove(0, screenpt, point);
	}
	else if (nhit == 3)
	{
		ASSERT(0);
		//m_pBox->m_scrollX->OnMouseMove(0, screenpt, point);
	}
	
#if 0
	CComQIPtr<ILDOMElement> element = m_pNode;

	CComQIPtr<ILElementCSSInlineStyle> stylable = element;

	CComPtr<ILCSSStyleDeclaration> style;
	stylable->get_style(&style);

	long left = point.x;
	long top = point.y;

	style->setProperty(OLESTR("left", _bstr_t(_variant_t(left)), NULL);
	style->setProperty(OLESTR("top", _bstr_t(_variant_t(top)), NULL);
#endif
}

void PElementBase::CreateScrollBars(CHTMFlowBlockContext* pC)
{
	//return;
// Scrollbars are created between padding and borders
	// TODO
	//if (m_pWindow)// && FALSE/*&& m_pWindow->m_pUI*/)
	{
		gm::RectF innerRect = m_pBox->m_innerRect;//m_pBox->GetAbsInnerRect();
		//LDraw::Rect outerRect = m_pBox->GetAbsInnerRect();

		gm::RectD dimrect(innerRect.X, innerRect.Y, innerRect.Width, innerRect.Height);
		dimrect.Inflate(m_computedPadding[0], m_computedPadding[1], m_computedPadding[2], m_computedPadding[3]);

		if (m_bVScroll)
		{
#if 0
			if (m_pBox->m_scrollY == NULL)
			{
				m_pBox->m_scrollY = new UI::ControlHost;
				m_pBox->m_scrollY->m_pWindow = m_pWindow;
				m_pBox->m_scrollY->m_pElement = this;
				m_pBox->m_scrollY->m_pSite = this;
				m_pBox->m_scrollY->set_VisualTree(new UI::ScrollBar(UI::Orientation_Vertical));
			//	m_pBox->m_scrollY->m_VisualTree->SetOwnerWindow(m_pBox->m_scrollY);
			//	m_pBox->m_scrollY->put_VisualTree(m_pBox->m_scrollY->m_pContent);
			//	m_pBox->m_scrollY->m_pContent->SetOwnerWindow(m_pBox->m_scrollY);

				//ASSERT(0);
#if 0
				m_pBox->m_scrollY->addEventListener(WSTR("scroll"), this, false);
#endif
			}

			m_pBox->m_scrollY->get_VisualTree()->Measure(LDraw::SizeD(16, dimrect.Height));
			m_pBox->m_scrollY->get_VisualTree()->Arrange(LDraw::RectD(dimrect.GetRight(), dimrect.GetTop(), 16, dimrect.Height));
			//m_pBox->m_scrollY->SetLayoutOffset(dimrect.GetRight(), dimrect.GetTop());

			//ASSERT(0);
#if 0
			dynamic_cast<UI::ScrollBar*>(m_pBox->m_scrollY->get_VisualTree())->SetInfo(0, m_contentSize.Height, innerRect.Height);
#endif
#endif
		}
		else
		{
			if (m_pBox->m_scrollY)
			{
				ASSERT(0);
#if 0
				m_pBox->m_scrollY->removeEventListener(WSTR("scroll"), this, false);
#endif
				delete m_pBox->m_scrollY;
				m_pBox->m_scrollY = NULL;
			}
		}

		if (m_bHScroll)
		{
#if 0
			if (m_pBox->m_scrollX == NULL)
			{
				m_pBox->m_scrollX = new UI::ControlHost;
				m_pBox->m_scrollX->m_pWindow = m_pWindow;
				m_pBox->m_scrollX->m_pElement = this;
				m_pBox->m_scrollX->m_pSite = this;
				m_pBox->m_scrollX->set_VisualTree(new UI::ScrollBar);
//				m_pBox->m_scrollX->m_pSite = m_pBox->m_scrollX;//m_pWindow;	// CLXUIWindowBase
			//	m_pBox->m_scrollX->m_VisualTree->SetOwnerWindow(m_pBox->m_scrollX);
			//	m_pBox->m_scrollX->put_VisualTree(m_pBox->m_scrollX->m_pContent);
			//	m_pBox->m_scrollX->m_pContent->SetOwnerWindow(m_pBox->m_scrollX);

			//	ASSERT(0);
#if 0
				m_pBox->m_scrollX->addEventListener(WSTR("scroll"), this, false);
#endif
			}

			m_pBox->m_scrollX->get_VisualTree()->Measure(LDraw::SizeD(dimrect.Width, 16));
			m_pBox->m_scrollX->get_VisualTree()->Arrange(LDraw::RectD(dimrect.GetLeft(), dimrect.GetBottom(), dimrect.Width, 16));
			//m_pBox->m_scrollX->SetLayoutOffset(dimrect.GetLeft(), dimrect.GetBottom());

		//	ASSERT(0);
#if 0
			dynamic_cast<UI::ScrollBar*>(m_pBox->m_scrollX->get_VisualTree())->SetInfo(0, m_contentSize.Width, innerRect.Width);
#endif
#endif
		}
		else
		{
			if (m_pBox->m_scrollX)
			{
			//	ASSERT(0);
#if 0
				m_pBox->m_scrollX->removeEventListener(WSTR("scroll"), this, false);
#endif
				delete m_pBox->m_scrollX;
				m_pBox->m_scrollX = NULL;
			}
		}
	}
}

void PElementBase::CreateControls(CHTMContext* pC)
{
// hm.. should create scrollbars in here instead ?
}

void CHTMElementBox::AdjustOuterRect()
{
	m_innerRect.Translate(m_computedBorderWidth[0], m_computedBorderWidth[1]);
	m_innerRect.Translate(m_computedPadding[0], m_computedPadding[1]);
	m_innerRect.Translate(m_computedMargin[0], m_computedMargin[1]);

	m_outerRect.Height += m_computedPadding[1] + m_computedPadding[3];
	m_outerRect.Width += m_computedPadding[0] + m_computedPadding[2];

	m_outerRect.Height += m_computedBorderWidth[1] + m_computedBorderWidth[3];
	m_outerRect.Width += m_computedBorderWidth[0] + m_computedBorderWidth[2];

	m_outerRect.Height += m_computedMargin[1] + m_computedMargin[3];
	m_outerRect.Width += m_computedMargin[0] + m_computedMargin[2];
}

bool PElementBase::HasDistributableChildren()
{
	return true;//!m_childList.IsEmpty();
}

//////////////////////////////////////////
// TABLE

int PElementBase::InsertColumnSpan(PElementBase* pCell, int row, int col, int colspan)
{
	ColumnSpan columnspan;
	columnspan.m_pCell = pCell;
	columnspan.m_row = row;
	columnspan.m_colspan = colspan;

	int col2 = col;

	int i;

	for (i = 0; i < m_columnsSpan.GetSize(); i++)
	{
		ColumnSpan& columnspan2 = m_columnsSpan[i];

		if ((col2+colspan) <= columnspan2.m_col)
		{
			break;
		}
		else if (columnspan2.m_col >= col2)
		{
			col2 = MAX(col2, columnspan2.m_col + columnspan2.m_colspan);
		}
	}

	ASSERT(col2 >= col);

	columnspan.m_col = col2;

	m_columnsSpan.InsertAt(i, columnspan);

#ifdef _DEBUG
	{
		int i;

		for (i = 1; i < m_columnsSpan.GetSize(); i++)
		{
			ASSERT((m_columnsSpan[i].m_col) >= (m_columnsSpan[i-1].m_col+m_columnsSpan[i-1].m_colspan));
		}

		for (i = 0; i < m_columnsSpan.GetSize()-1; i++)
		{
			ASSERT((m_columnsSpan[i].m_col+m_columnsSpan[i].m_colspan) <= (m_columnsSpan[i+1].m_col));
		}
	}
#endif

	return col2;
}


/* From CSS2 spec

1. Each row box occupies one row of grid cells. Together, the row boxes fill the table
	from top to bottom in the order they occur in the source document (i.e., the table
	occupies exactly as many grid rows as there are row elements). 

2. A row group occupies the same grid cells as the rows it contains. 

3. A column box occupies one or more columns of grid cells. Column boxes are placed
	next to each other in the order they occur. The first column box may be either on
	the left or on the right, depending on the value of the 'direction' property of
	the table. 
4. A column group box occupies the same grid cells as the columns it contains. 

5. Cells may span several rows or columns. (Although CSS2 doesn't define how the
	number of spanned rows or columns is determined, a user agent may have special
	knowledge about the source document; a future version of CSS may provide a way to
	express this knowledge in CSS syntax.)
	
	Each cell is thus a rectangular box, one
	or more grid cells wide and high. The top row of this rectangle is in the row
	specified by the cell's parent. The rectangle must be as far to the left as
	possible, but it may not overlap with any other cell box, and must be to the right
	of all cells in the same row that are earlier in the source document.
	(This constraint holds if the 'direction' property of the table is 'ltr'; if
	the 'direction' is 'rtl', interchange "left" and "right" in the previous sentence.) 

6. A cell box cannot extend beyond the last row box of a table or row-group; the
	user agents must shorten it until it fits. 

*/

/*

Column widths are determined as follows:

1. Calculate the minimum content width (MCW) of each cell: the formatted
	content may span any number of lines but may not overflow the cell box.
	If the specified 'width' (W) of the cell is greater than MCW, W is the
	minimum cell width. A value of 'auto' means that MCW is the minimum cell
	width. 

 Also, calculate the "maximum" cell width of each cell: formatting then
 content without breaking lines other than where explicit line breaks occur. 

2. For each column, determine a maximum and minimum column width from the
	cells that span only that column. The minimum is that required by the
	cell with the largest minimum cell width (or the column 'width', whichever
	is larger). The maximum is that required by the cell with the largest
	maximum cell width (or the column 'width', whichever is larger).

3. For each cell that spans more than one column, increase the minimum widths
	of the columns it spans so that together, they are at least as wide as the
	cell. Do the same for the maximum widths. If possible, widen all spanned
	columns by approximately the same amount. 

*/

//#include "LHTMLTableElement.h"

void PElementBase::DistributeTableChildren(CHTMFlowBlockContext* pC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentwidth)
{
	ASSERT(m_pBox);

#if 0
	CComQIPtr<ILDOMElement> element = m_pNode;
#endif
//	CComQIPtr<ILHTMLTableElement> tableElement = element;	// Could be, but not necessarily

	//m_table_border = 0;
	//m_table_cellspacing = 3;
	//m_table_cellpadding = 3;

	/*
	BSTR b;

	element->getAttribute(OLESTR("border", &b);
	if (b)
	{
		m_table_border = str2int(b, 0);
		SysFreeString(b);
	}
	m_table_border = max(m_table_border, 0);
	*/

	/*
	if (tableElement)
	{
		m_table_cellspacing = static_cast<CLHTMLTableElement*>(tableElement.p)->m_pcellspacing->m_animated->m_animVal->m_value->m_value;
	}
	else
	{
		element->getAttribute(OLESTR("cellspacing", &b);
		if (b)
		{
			m_table_cellspacing = str2int(b, 0);
			SysFreeString(b);
		}
	}
	m_table_cellspacing = max(m_table_cellspacing, 0);
	*/

/*	if (tableElement)
	{
		m_table_cellpadding = static_cast<CLHTMLTableElement*>(tableElement.p)->m_pcellspacing->m_animVal.m_value;
	}
	else
*/	{
	/*
		element->getAttribute(OLESTR("cellpadding", &b);
		if (b)
		{
			m_table_cellpadding = str2int(b, 0);
			SysFreeString(b);
		}
		m_table_cellpadding = max(m_table_cellpadding, 0);
		*/
	}

	/*
	m_computedBorderStyle[0] = BorderStyle_solid;
	m_computedBorderStyle[1] = BorderStyle_solid;
	m_computedBorderStyle[2] = BorderStyle_solid;
	m_computedBorderStyle[3] = BorderStyle_solid;
	m_computedBorderWidth[0] = m_table_border;
	m_computedBorderWidth[1] = m_table_border;
	m_computedBorderWidth[2] = m_table_border;
	m_computedBorderWidth[3] = m_table_border;
	*/

	vector<PElementBase*> rowGroups;
	vector<PElementBase*> rows;	// flattened list of rows (use m_rows instead?)

	// Build array of all rows in table
	{
		PNode** pos = GetChildList().GetData();
		while (pos != GetChildList().GetData() + GetChildList().GetSize())
		{
			PNode* pPNode = (*pos);//(PNode*)GetChildList().GetNext(pos);
			if (pPNode->m_type == NODE_ELEMENT)
			{
				PElementBase* pPElement = (PElementBase*)pPNode;

				if (pPElement->m_computedDisplayRole == DisplayRole_table_row_group)
				{
					PElementBase* pRowGroupElement = pPElement;
					rowGroups.Add(pRowGroupElement);

					pRowGroupElement->m_rows.RemoveAll();

				// Traverse the rows in the rowgroup
					PNode** pos2 = pPElement->GetChildList().GetData();
					while (pos2 != pPElement->GetChildList().GetData() + pPElement->GetChildList().GetSize())
					{
						PNode* pPNode = (*pos2);//(PNode*)pPElement->GetChildList().GetNext(pos2);
						if (pPNode->m_type == NODE_ELEMENT)
						{
							PElementBase* pPElement = (PElementBase*)pPNode;
							if (pPElement->m_computedDisplayRole == DisplayRole_table_row)
							{
								pPElement->m_columnsSpan.RemoveAll();

								rows.Add(pPElement);	// add to flattened list of rows for table
								pRowGroupElement->m_rows.Add(pPElement);
							}
						}
						pos2++;
					}
				}
				else if (pPElement->m_computedDisplayRole == DisplayRole_table_row)
				{
					pPElement->m_columnsSpan.RemoveAll();
					rows.Add(pPElement);	// add to flattened list of rows for table
				}
			}

			pos++;
		}
	}

	if (m_tableColumns)
	{
		delete m_tableColumns;
		m_tableColumns = NULL;
		m_ncolumns = 0;
	}

	// Get number of columns
	{
		for (int nrow = 0; nrow < rows.GetSize(); nrow++)
		{
			PElementBase* pPRowElement = rows[nrow];

			pPRowElement->m_cells.RemoveAll();

		// Traverse all cells for this row
		// determine the columnIndex for each cell

			int ncol = 0;
			PNode** pos2 = pPRowElement->GetChildList().GetData();
			while (pos2 != pPRowElement->GetChildList().GetData() + pPRowElement->GetChildList().GetSize())
			{
				PNode* pPNode = (*pos2);//(PNode*)pPRowElement->GetChildList().GetNext(pos2);
				if (pPNode->m_type == NODE_ELEMENT)
				{
					PElementBase* pPElement = (PElementBase*)pPNode;

					if (pPElement->m_computedDisplayRole == DisplayRole_table_cell)
					{
						pPRowElement->m_cells.Add(pPElement);

						pPElement->m_nrow = nrow;

						/*
						pPElement->m_computedBorderStyle[0] = BorderStyle_solid;
						pPElement->m_computedBorderStyle[1] = BorderStyle_solid;
						pPElement->m_computedBorderStyle[2] = BorderStyle_solid;
						pPElement->m_computedBorderStyle[3] = BorderStyle_solid;

						pPElement->m_computedBorderWidth[0] = 1;
						pPElement->m_computedBorderWidth[1] = 1;
						pPElement->m_computedBorderWidth[2] = 1;
						pPElement->m_computedBorderWidth[3] = 1;
						*/

						pPElement->m_minWidth = pPElement->m_minContentWidth +
							pPElement->m_computedBorderWidth[0] +
							pPElement->m_computedMargin[0] +
							pPElement->m_computedPadding[0] +

							pPElement->m_computedBorderWidth[2] +
							pPElement->m_computedMargin[2] +
							pPElement->m_computedPadding[2];

						pPElement->m_maxWidth = pPElement->m_maxContentWidth +
							pPElement->m_computedBorderWidth[0] +
							pPElement->m_computedMargin[0] +
							pPElement->m_computedPadding[0] +

							pPElement->m_computedBorderWidth[2] +
							pPElement->m_computedMargin[2] +
							pPElement->m_computedPadding[2];

						//MessageBeep(-1);
					//	pPElement->m_colspan = 1;
					//	pPElement->m_rowspan = 1;

						Element* element = dynamic_cast<Element*>(pPElement->m_pNode);

						String scolspan = element->getAttribute(WSTR("colspan"));
						{
							pPElement->m_colspan = str2int(CStringw(scolspan), 1);
							if (pPElement->m_colspan < 1) pPElement->m_colspan = 1;
						}

						String srowspan = element->getAttribute(WSTR("rowspan"));
						{
							pPElement->m_rowspan = str2int(CStringw(srowspan), 1);
							if (pPElement->m_rowspan < 1) pPElement->m_rowspan = 1;
						}

						//ASSERT(pPElement->m_colspan > 0);
						//ASSERT(pPElement->m_rowspan > 0);

						ncol = rows[nrow]->InsertColumnSpan(pPElement, nrow, ncol, pPElement->m_colspan);
						pPElement->m_columnIndex = ncol;

						for (int i = 1; i < pPElement->m_rowspan; i++)
						{
							ASSERT(nrow+i < rows.GetSize());
							rows[nrow+i]->InsertColumnSpan(pPElement, nrow, ncol, pPElement->m_colspan);
						}

						ncol += pPElement->m_colspan;
					}
				}
				pos2++;
			}

			m_ncolumns = MAX(m_ncolumns, ncol);
		}
	}

	m_tableColumns = new Column[m_ncolumns];

	// Widen the columns based on cells that span only one column
	{
		for (int ncol = 0; ncol < m_ncolumns; ncol++)
		{
			m_tableColumns[ncol].m_minWidth = 0;
			m_tableColumns[ncol].m_maxWidth = 0;

			for (int nrow = 0; nrow < rows.GetSize(); nrow++)
			{
				PElementBase* pPRowElement = rows[nrow];
				for (int ncell = 0; ncell < pPRowElement->m_cells.GetSize(); ncell++)
				{
					PElementBase* pCell = pPRowElement->m_cells[ncell];
					if (pCell->m_columnIndex == ncol)
					{
						if (pCell->m_colspan == 1)
						{
							m_tableColumns[ncol].m_minWidth = MAX(m_tableColumns[ncol].m_minWidth, pCell->m_minWidth);
							m_tableColumns[ncol].m_maxWidth = MAX(m_tableColumns[ncol].m_maxWidth, pCell->m_maxWidth);

							ASSERT(m_tableColumns[ncol].m_maxWidth >= m_tableColumns[ncol].m_minWidth);
						}
					}
				}
			}
		}
	}

	// Widen the columns based on cells that span several columns
	{
		for (int nrow = 0; nrow < rows.GetSize(); nrow++)
		{
			PElementBase* pRowElement = rows[nrow];

			for (int ncell = 0; ncell < pRowElement->m_cells.GetSize(); ncell++)
			{
				PElementBase* pCell = pRowElement->m_cells[ncell];
				if (pCell->m_colspan > 1)
				{
					double minsum = 0;
					double maxsum = 0;

					int ncol;

					for (ncol = pCell->m_columnIndex; ncol < pCell->m_columnIndex+pCell->m_colspan; ncol++)
					{
						minsum += m_tableColumns[ncol].m_minWidth;
						maxsum += m_tableColumns[ncol].m_maxWidth;
					}

					double maxwidth = pCell->m_maxWidth-(pCell->m_colspan-1)*m_computedBorderSpacing[0];

					if (maxsum <= 0)
					{
						ASSERT(maxwidth >= 0);

						for (ncol = pCell->m_columnIndex; ncol < pCell->m_columnIndex+pCell->m_colspan; ncol++)
						{
							m_tableColumns[ncol].m_maxWidth = maxwidth/*pCell->m_maxWidth*//pCell->m_colspan;
						}
					}
					else if (maxwidth > maxsum)
					{
						double maxf = maxwidth/maxsum;
						ASSERT(maxf > 1);

						for (ncol = pCell->m_columnIndex; ncol < pCell->m_columnIndex+pCell->m_colspan; ncol++)
						{
							m_tableColumns[ncol].m_maxWidth *= maxf;
						}
					}

					{
						double sum = 0;
						int ncol;

						for (ncol = pCell->m_columnIndex; ncol < pCell->m_columnIndex+pCell->m_colspan; ncol++)
						{
							ASSERT(m_tableColumns[ncol].m_maxWidth >= m_tableColumns[ncol].m_minWidth);
							sum += (m_tableColumns[ncol].m_maxWidth - m_tableColumns[ncol].m_minWidth);
						}

						double minwidth = pCell->m_minWidth-(pCell->m_colspan-1)*m_computedBorderSpacing[0];

						if (sum > 0 && minwidth > minsum)
						{
							double reWidth = minwidth-minsum;

							for (ncol = pCell->m_columnIndex; ncol < pCell->m_columnIndex+pCell->m_colspan; ncol++)
							{
								double f = (m_tableColumns[ncol].m_maxWidth-m_tableColumns[ncol].m_minWidth)/sum;
								ASSERT(f >= 0 && f <= 1);

								m_tableColumns[ncol].m_minWidth += f*reWidth;
							}
						}
					}

#ifdef _DEBUG
					{
						for (int ncol = pCell->m_columnIndex; ncol < pCell->m_columnIndex+pCell->m_colspan; ncol++)
						{
							ASSERT(m_tableColumns[ncol].m_maxWidth >= m_tableColumns[ncol].m_minWidth);
						}
					}
#endif
				}
			}
		}
	}

	double tableMinWidth = 0;
	double tableMaxWidth = 0;

	tableMinWidth += m_computedBorderSpacing[0];//m_table_cellspacing;
	tableMaxWidth += m_computedBorderSpacing[0];//m_table_cellspacing;

	{
		for (int ncol = 0; ncol < m_ncolumns; ncol++)
		{
			ASSERT(m_tableColumns[ncol].m_maxWidth >= m_tableColumns[ncol].m_minWidth);

			tableMinWidth += m_tableColumns[ncol].m_minWidth;
			tableMaxWidth += m_tableColumns[ncol].m_maxWidth;

			tableMinWidth += m_computedBorderSpacing[0];//m_table_cellspacing;
			tableMaxWidth += m_computedBorderSpacing[0];//m_table_cellspacing;
		}
	}

	ASSERT(tableMaxWidth >= tableMinWidth);

/*

Column widths influence the final table width as follows:

1. If the 'table' or 'inline-table' element's 'width' property has a specified value
(W) other than 'auto', the property's computed value is the greater of W and the
minimum width required by all the columns plus cell spacing or borders (MIN). If
W is greater than MIN, the extra width should be distributed over the columns. 

2. If the 'table' or 'inline-table' element has 'width: auto', the computed table width
is the greater of the table's containing block width and MIN. However, if the
maximum width required by the columns plus cell spacing or borders (MAX) is
less than that of the containing block, use MAX. 

	*/
	double tableWidth;

#if 0	// TODO, maybe have something like this
	parentwidth -= m_table_border*2;	// ??
#endif
/*
	if (m_specifiedWidth > -1)
	{
		tableWidth = max(tableMinWidth, m_specifiedWidth);
	}
	else
	{
		tableWidth = max(tableMinWidth, parentwidth);
		tableWidth = min(tableWidth, tableMaxWidth);
	}
*/

//	ASSERT(0);
	if (true)//m_specifiedWidth == -1)	// auto
	{
		tableWidth = MAX(tableMinWidth, parentwidth);
		tableWidth = MIN(tableWidth, tableMaxWidth);
	}
	else
	{
		if (tableMinWidth > parentwidth)
		{
#if 0	// ???
			MessageBeep(-1);
#endif
		}
		//tableWidth = m_computedWidth;
		tableWidth = MAX(tableMinWidth, parentwidth);
	}

	{
	// Distribute leftover width among columns, depending on the columns min/max width
	// Give more to those with larger max widths
		double distributableWidth = tableWidth-tableMinWidth;

		if (distributableWidth <= 0)	// Nothing to distribute, set all columns to min width
		{
			for (int ncol = 0; ncol < m_ncolumns; ncol++)
			{
				m_tableColumns[ncol].m_width = m_tableColumns[ncol].m_minWidth;
				ASSERT(m_tableColumns[ncol].m_width >= 0);
			}
			tableWidth = tableMinWidth;
		}
		else// if (tableMaxWidth > tableMinWidth)
		{
			double tableWidth2 = m_computedBorderSpacing[0];//m_table_cellspacing;
			for (int ncol = 0; ncol < m_ncolumns; ncol++)
			{
			//	double f = (double)(m_tableColumns[ncol].m_maxWidth-m_tableColumns[ncol].m_minWidth) / (tableWidth-tableMinWidth);
			//	ASSERT(f >= 0 && f <= 1);

				double width = tableWidth*m_tableColumns[ncol].m_maxWidth/tableMaxWidth;// + distributableWidth*f;

				m_tableColumns[ncol].m_width = width;

				ASSERT(m_tableColumns[ncol].m_width >= 0);

				tableWidth2 += m_tableColumns[ncol].m_width + m_computedBorderSpacing[0];//m_table_cellspacing;
			}
			tableWidth = tableWidth2;
		}
		/*
		else if (tableMaxWidth > tableMinWidth)
		{
			double tableWidth2 = m_computedBorderSpacing[0];//m_table_cellspacing;
			for (int ncol = 0; ncol < m_ncolumns; ncol++)
			{
				double f = (double)(m_tableColumns[ncol].m_maxWidth-m_tableColumns[ncol].m_minWidth) / (tableMaxWidth-tableMinWidth);
				ASSERT(f >= 0 && f <= 1);

				double width = m_tableColumns[ncol].m_minWidth + distributableWidth*f;

				m_tableColumns[ncol].m_width = width;

				ASSERT(m_tableColumns[ncol].m_width >= 0);

				tableWidth2 += m_tableColumns[ncol].m_width + m_computedBorderSpacing[0];//m_table_cellspacing;
			}
			tableWidth = tableWidth2;
		}
		*/
		/*
		else
		{
			for (int ncol = 0; ncol < m_ncolumns; ncol++)
			{
				m_tableColumns[ncol].m_width = m_tableColumns[ncol].m_minWidth;
				ASSERT(m_tableColumns[ncol].m_width >= 0);
			}
		}
		*/
	}

	m_pBox->m_innerRect.Width = tableWidth;

/*

The height of a 'table-row' element's box is calculated once the user agent has all
the cells in the row available:

  it is the maximum of the row's specified 'height'
and the minimum height (MIN) required by the cells. A 'height' value of 'auto' for
a 'table-row' means the computed row height is MIN. MIN depends on cell box heights
and cell box alignment (much like the calculation of a line box height). CSS2 does
not define what percentage values of 'height' refer to when specified for table rows
and row groups.

*/

	// Distribute all the cells content and get minHeight of all the cells
	{
		for (int nrow = 0; nrow < rows.GetSize(); nrow++)
		{
			PElementBase* pPRowElement = rows[nrow];
			for (int ncell = 0; ncell < pPRowElement->m_columnsSpan.GetSize(); ncell++)
			{
				ColumnSpan span = pPRowElement->m_columnsSpan[ncell];

				PElementBase* pPElement = span.m_pCell;

				double cellwidth = 0;
				{
					for (int ncol = 0; ncol < pPElement->m_colspan; ncol++)
					{
						ASSERT(pPElement->m_columnIndex+ncol < m_ncolumns);

						cellwidth +=
							m_tableColumns[pPElement->m_columnIndex+ncol].m_width +
							m_computedBorderSpacing[0];//m_table_cellspacing;
					}
				}

				if (span.m_row == nrow)
				{
#if 0	// TODO have this
					ASSERT(pPElement->m_pBox == NULL);
#endif
					if (pPElement->m_pBox)	// TODO, shouldn't be necessary
					{
						CHTMBlockBox* pBox = pPElement->m_pBox;
						pPElement->m_pBox = NULL;
						//delete pBox;
						pBox->Release();
					}

					double innerWidth = cellwidth - m_computedBorderSpacing[0];//m_table_cellspacing;

					CHTMFlowBlockContext pC2;// = new CHTMFlowBlockContext;

					ASSERT(innerWidth >= 0);

					pPElement->DistributeWithinBlock(&pC2, nearestPositioned, stackingContext, innerWidth);

					ASSERT(pPElement->m_pBox);
					ASSERT(pC2.m_pBlockBox);
					ASSERT(pC2.m_pBlockBox == pPElement->m_pBox);

				//	pC2->m_pBlockBox->m_outerRect = pC2->m_pBlockBox->m_innerRect;	// Maybe I don't need this here

				//	pC2->m_pBlockBox->AdjustOuterRect();

				//	delete pC2;
				}
			}
		}
	}

	// Get temporary minHeight of rows
	// (maximum of the heights of the cells that span only that one row)
	for (int nrow = 0; nrow < rows.GetSize(); nrow++)
	{
		PElementBase* pRowElement = rows[nrow];

		pRowElement->m_minHeight = 0;

		for (int ncell = 0; ncell < pRowElement->m_cells.GetSize(); ncell++)
		{
			PElementBase* pCell = pRowElement->m_cells[ncell];

		//	if (pCell->m_pBox)
			ASSERT(pCell->m_nrow == nrow);
			ASSERT(pCell->m_pBox);

			if (pCell->m_rowspan == 1)
			{
				pRowElement->m_minHeight = MAX(pRowElement->m_minHeight, pCell->m_pBox->m_outerRect.Height/*pCell->m_pBox->m_innerRect.Height*/);
			}
		}
	}

	// Heighten the rows heights based on cells that span several rows
	{
		//for (int ncol = 0; ncol < m_ncolumns; ncol++)
		{

			for (int nrow = 0; nrow < rows.GetSize(); nrow++)
			{
				PElementBase* pRowElement = rows[nrow];

				for (int ncell = 0; ncell < pRowElement->m_cells.GetSize(); ncell++)
				{
					PElementBase* pCellElement = pRowElement->m_cells[ncell];

					if (pCellElement->m_rowspan > 1)
					{
						double sum = 0;

						for (int nrow2 = nrow; nrow2 < nrow+pCellElement->m_rowspan; nrow2++)
						{
							sum += rows[nrow2]->m_minHeight;
						}

						double cellheight = pCellElement->m_pBox->m_outerRect.Height/*pCellElement->m_pBox->m_innerRect.Height*/-(pCellElement->m_rowspan-1)*m_computedBorderSpacing[1];//m_table_cellspacing;

						if (sum <= 0)
						{
							for (int nrow2 = nrow; nrow2 < nrow+pCellElement->m_rowspan; nrow2++)
							{
								rows[nrow2]->m_minHeight = cellheight/pCellElement->m_rowspan;
							}
						}
						else if (cellheight > sum)
						{
							double f = cellheight/sum;
							ASSERT(f > 1);

							for (int nrow2 = nrow; nrow2 < nrow+pCellElement->m_rowspan; nrow2++)
							//for (ncol = pCell->m_columnIndex; ncol < pCell->m_columnIndex+pCell->m_colspan; ncol++)
							{
								rows[nrow2]->m_minHeight *= f;
							}
						}
					}
				}
			}
		}
	}

	int rowgroup = 0;
	double rowTop = m_computedBorderSpacing[1];//m_table_cellspacing;
	{
		for (int nrow = 0; nrow < rows.GetSize(); nrow++)
		{
			PElementBase* pPRowElement = rows[nrow];

			//pPRowElement->m_minHeight = 0;

			int ncell;

			double x = m_computedBorderSpacing[0];//m_table_cellspacing;
			for (ncell = 0; ncell < pPRowElement->m_columnsSpan.GetSize(); ncell++)
			{
				ColumnSpan span = pPRowElement->m_columnsSpan[ncell];

				PElementBase* pPElement = span.m_pCell;

				double cellwidth = 0;
				{
					for (int ncol = 0; ncol < pPElement->m_colspan; ncol++)
					{
						ASSERT(pPElement->m_columnIndex+ncol < m_ncolumns);

						cellwidth +=
							m_tableColumns[pPElement->m_columnIndex+ncol].m_width +
							m_computedBorderSpacing[0];//m_table_cellspacing;
					}
				}

				if (span.m_row == nrow)	// We don't want to add boxes several times for cells that span several rows
				{
					pPElement->m_pBox->m_outerRect.Translate(x, rowTop);

					// Add row group background box
					{
					}

					// Add row background box
					if (pPRowElement->m_pBox == NULL)	// ??
					{
					//	CHTMBlockBox* pBox = pPRowElement->CreateAnonymousBlockBox();
						if (pPRowElement->m_pBox)	// ??
						{
							pPRowElement->m_pBox->Release();
							pPRowElement->m_pBox = NULL;
						}

						pPRowElement->m_pBox = pPRowElement->CreateBlockBox();

						pPRowElement->m_pBox->m_outerRect = pPElement->m_pBox->m_outerRect;
						pPRowElement->m_pBox->m_innerRect = gm::RectF(0, 0, pPRowElement->m_pBox->m_outerRect.Width, pPRowElement->m_pBox->m_outerRect.Height);

						pC->m_pBlockBox->AddChildBox(pPRowElement->m_pBox);
					}

					// Add cell box
					pC->m_pBlockBox->AddChildBox(pPElement->m_pBox);
				}
				else
				{
				}

				x += cellwidth;
			}

		//	pPRowElement->m_size.Height = max(pPRowElement->m_computedHeight, pPRowElement->m_minHeight);
			// TODO have specifiedHeight inside max?
			pPRowElement->m_computedHeight = pPRowElement->m_minHeight;//max(pPRowElement->m_computedHeight, pPRowElement->m_minHeight);

			//ASSERT(pPRowElement->m_size.Height >= 0);

			rowTop += pPRowElement->m_computedHeight;

		// Make all the cells in the row the same height

		// Cells spanning several rows will be adjusted several times, and the last adjustment will count
			for (ncell = 0; ncell < pPRowElement->m_columnsSpan.GetSize(); ncell++)
			{
				ColumnSpan span = pPRowElement->m_columnsSpan[ncell];

				double diffHeight = span.m_pCell->m_pBox->m_outerRect.Height - span.m_pCell->m_pBox->m_innerRect.Height;

				span.m_pCell->m_pBox->m_outerRect.Height = rowTop - span.m_pCell->m_pBox->m_outerRect.Y;//rRect.Height + diffHeight;
				span.m_pCell->m_pBox->m_innerRect.Height = span.m_pCell->m_pBox->m_outerRect.Height-diffHeight;
			}

			rowTop += m_computedBorderSpacing[1];//m_table_cellspacing;

			/*
			if (rowGroups.GetSize())
			{
				if (nrow > rowGroups
			}
			*/
		}
	}

	double y = rowTop;

	pC->m_maxx = MAX(pC->m_maxx, tableWidth);

	m_contentSize.Height = y;
	m_contentSize.Width = pC->m_maxx;

	ASSERT(pC->m_pBlockBox);

	pC->m_pBlockBox->m_innerRect.Height = y;

/*
	if (m_specifiedHeight >= 0)
		pC->m_pBlockBox->m_innerRect.Height = m_specifiedHeight;
	else
		pC->m_pBlockBox->m_innerRect.Height = y;

	if (m_specifiedWidth >= 0)
		pC->m_pBlockBox->m_innerRect.Width = m_specifiedWidth;
	else
		pC->m_pBlockBox->m_innerRect.Width = pC->m_maxx;
  */
	m_pBox->m_outerRect = m_pBox->m_innerRect;
	m_pBox->AdjustOuterRect();
}

void PElementBase::DistributeBoxChildren(CHTMFlowBlockContext* pC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentwidth)
{
	double totalFlex = 0;

	PNode** pos = m_rchildList.GetData();
	while (pos != m_rchildList.GetData() + m_rchildList.GetSize())
	{
		PNode* pNode = (*pos)++;//(PNode*)m_rchildList.GetNext(pos);
		if (pNode->m_type == NODE_ELEMENT)
		{
			PElementBase* pElement = (PElementBase*)pNode;
			if (pElement->m_computedDisplayRole != DisplayRole_none)
			{
				totalFlex += pElement->m_computedBoxFlex;
			}
		}
	}

	bool bHorizontal = (m_computedBoxOrient == BoxOrient_horizontal || m_computedBoxOrient == BoxOrient_inline_axis);
	//if (m_computedBoxOrient == BoxOrient_horizontal || m_computedBoxOrient == BoxOrient_inline_axis)
	double offset;
	offset = 0;

	double offset_opposite;
	offset_opposite = 0;

	pos = m_rchildList.GetData();
	while (pos != m_rchildList.GetData() + m_rchildList.GetSize())
	{
		PNode* pNode = *pos++;//(PNode*)m_rchildList.GetNext(pos);

		PElementBase* pElement = (PElementBase*)pNode;
		if (pNode->m_type == NODE_ELEMENT)
		{
			if (pElement->m_computedDisplayRole != DisplayRole_none)
			{
				double oldm[4];
				double oldp[4];
				double oldbw[4];
				{
					for (int i = 0; i < 4; i++)
					{
						oldm[i] = pElement->m_computedMargin[i];
						oldp[i] = pElement->m_computedPadding[i];
						oldbw[i] = pElement->m_computedBorderWidth[i];
					}
				}

				CHTMFlowBlockContext* pC2 = new CHTMFlowBlockContext;

				/*
				if (m_computedBoxAlign == BoxAlign_stretch)
				{
					pElement->m_specifiedHeight = m_computedHeight;
				}
				else
					ASSERT(0);
					*/

				if (bHorizontal)
				{
					pElement->DistributeWithinBlock(pC2, nearestPositioned, stackingContext, 0x0fffffff/*m_pBox->m_innerRect.Width*/);
					ASSERT(pElement->m_pBox);

					if (true)//pElement->m_specifiedWidth == -1)	// ??
					{
						pElement->m_pBox->m_innerRect.Width = pC2->m_maxx;
					}

					pElement->m_pBox->m_outerRect.Width = pElement->m_pBox->m_innerRect.Width;
				}
				else
				{
					pElement->DistributeWithinBlock(pC2, nearestPositioned, stackingContext, m_pBox->m_innerRect.Width);
				//	pC->m_maxx = max(pC->m_maxx, pC2->m_maxx);
					ASSERT(pElement->m_pBox);
				}

				{
					for (int i = 0; i < 4; i++)
					{
						pElement->m_computedMargin[i] = oldm[i];
						pElement->m_computedPadding[i] = oldp[i];
						pElement->m_computedBorderWidth[i] = oldbw[i];

						pElement->m_pBox->m_computedMargin[i] = oldm[i];
						pElement->m_pBox->m_computedPadding[i] = oldp[i];
						pElement->m_pBox->m_computedBorderWidth[i] = oldbw[i];
					}
				}

				pC2->m_maxx += pElement->m_computedMargin[0] + pElement->m_computedMargin[2] +
						pElement->m_computedBorderWidth[0] + pElement->m_computedBorderWidth[2] +
						pElement->m_computedPadding[0] + pElement->m_computedPadding[2];

				pC->m_maxx = MAX(pC->m_maxx, pC2->m_maxx);

				delete pC2;

			//	pElement->m_pBox->AdjustOuterRect();

				if (bHorizontal)
				{
					offset += pElement->m_pBox->m_outerRect.Width;
					offset_opposite = MAX(offset_opposite, pElement->m_pBox->m_innerRect.Height);
				}
				else
				{
					offset += pElement->m_pBox->m_innerRect.Height;
					offset_opposite = MAX(offset_opposite, pElement->m_pBox->m_outerRect.Width);
				}
			}
		}
	}

	{
		double spaceLeft;

		if (bHorizontal)
			spaceLeft = m_computedWidth - offset;
		else
			spaceLeft = m_computedHeight - offset;

		pos = m_rchildList.GetData();
		while (pos != m_rchildList.GetData() + m_rchildList.GetSize())
		{
			PNode* pNode = *pos++;//(PNode*)m_rchildList.GetNext(pos);
			if (pNode->m_type == NODE_ELEMENT)
			{
				PElementBase* pElement = (PElementBase*)pNode;

				if (pElement->m_computedDisplayRole != DisplayRole_none)
				{
					if (bHorizontal)
					{
						if (totalFlex > 0 && spaceLeft != 0)
						{
							double pcnt = pElement->m_computedBoxFlex / totalFlex;
							double add = spaceLeft * pcnt;

							pElement->m_pBox->m_innerRect.Width += add;
							pElement->m_pBox->m_outerRect.Width += add;
						}
					}
					else
					{
						double width;
						double height;

						if (m_computedBoxAlign == BoxAlign_stretch)
						{
							width = offset_opposite;
						}
						else
							width = pElement->m_pBox->m_outerRect.Width;	// Keep it the same

						if (totalFlex > 0 && spaceLeft != 0)
						{
							double pcnt = pElement->m_computedBoxFlex / totalFlex;
							double add = spaceLeft * pcnt;

							height = pElement->m_pBox->m_innerRect.Height+add;
						}
						else
							height = pElement->m_pBox->m_innerRect.Height;

						//ASSERT(height >= 0);

#if 0
						double old = pElement->m_specifiedHeight;
						double oldm[4];
						double oldp[4];
						double oldbw[4];
						{
							for (int i = 0; i < 4; i++)
							{
								oldm[i] = pElement->m_computedMargin[i];
								oldp[i] = pElement->m_computedPadding[i];
								oldbw[i] = pElement->m_computedBorderWidth[i];
							}
						}

						pElement->m_specifiedHeight = height;
#endif

						pElement->RemoveBoxesAndChildren();

						CHTMFlowBlockContext* pC2 = new CHTMFlowBlockContext;
						pElement->DistributeWithinBlock(pC2, nearestPositioned, stackingContext, width);

#if 0
						{
							for (int i = 0; i < 4; i++)
							{
								pElement->m_computedMargin[i] = oldm[i];
								pElement->m_computedPadding[i] = oldp[i];
								pElement->m_computedBorderWidth[i] = oldbw[i];

								pElement->m_pBox->m_computedMargin[i] = oldm[i];
								pElement->m_pBox->m_computedPadding[i] = oldp[i];
								pElement->m_pBox->m_computedBorderWidth[i] = oldbw[i];
							}
						}
#endif
						pC2->m_maxx += pElement->m_computedMargin[0] + pElement->m_computedMargin[2] +
								pElement->m_computedBorderWidth[0] + pElement->m_computedBorderWidth[2] +
								pElement->m_computedPadding[0] + pElement->m_computedPadding[2];

						pC->m_maxx = MAX(pC->m_maxx, pC2->m_maxx);
						delete pC2;

#if 0
						pElement->m_specifiedHeight = old;
#endif
					//	pElement->m_pBox->AdjustOuterRect();
					}
				}
			}
		}
	}

	if (bHorizontal)
	{
		if (m_computedHeight >= 0)
			offset_opposite = m_computedHeight;//pC->m_pBlockBox->m_innerRect.Height = m_specifiedHeight;
	}
	else
	{
	}
	/*
	else
		pC->m_pBlockBox->m_innerRect.Height = y;
		*/

	pos = m_rchildList.GetData();//GetHeadPosition();
	while (pos != m_rchildList.GetData() + m_rchildList.GetSize())
	{
		PNode* pNode = *pos++;//(PNode*)m_rchildList.GetNext(pos);

		PElementBase* pElement = (PElementBase*)pNode;
		if (pNode->m_type == NODE_ELEMENT)
		{
			if (pElement->m_computedDisplayRole != DisplayRole_none)
			{
				if (m_computedBoxAlign == BoxAlign_stretch)
				{
					if (bHorizontal)
					{
						double oldm[4];
						double oldp[4];
						double oldbw[4];
						{
							for (int i = 0; i < 4; i++)
							{
								oldm[i] = pElement->m_computedMargin[i];
								oldp[i] = pElement->m_computedPadding[i];
								oldbw[i] = pElement->m_computedBorderWidth[i];
							}
						}

						//if (maxy != pElement->m_pBox->m_innerRect.Height)
						{
							double width = pElement->m_pBox->m_outerRect.Width;	// Use same width
							pElement->RemoveBoxesAndChildren();

							ASSERT(0);
#if 0
							double old = pElement->m_specifiedHeight;
							pElement->m_specifiedHeight = offset_opposite;	// Use this height
#endif

							CHTMFlowBlockContext* pC2 = new CHTMFlowBlockContext;
							pElement->DistributeWithinBlock(pC2, nearestPositioned, stackingContext, width);
							pC->m_maxx = MAX(pC->m_maxx, pC2->m_maxx);
							delete pC2;

#if 0
							pElement->m_specifiedHeight = old;
#endif
						}

						{
							for (int i = 0; i < 4; i++)
							{
								pElement->m_computedMargin[i] = oldm[i];
								pElement->m_computedPadding[i] = oldp[i];
								pElement->m_computedBorderWidth[i] = oldbw[i];

								pElement->m_pBox->m_computedMargin[i] = oldm[i];
								pElement->m_pBox->m_computedPadding[i] = oldp[i];
								pElement->m_pBox->m_computedBorderWidth[i] = oldbw[i];
							}
						}

					//	pElement->m_pBox->AdjustOuterRect();
					}
#if 0	// Done above ??
					else
					{
						// TODO improve this ??
						pElement->m_pBox->m_innerRect.Width = offset_opposite;
						pElement->m_pBox->m_outerRect = pElement->m_pBox->m_innerRect;
					}
#endif
				}
				else if (m_computedBoxAlign == BoxAlign_end)
				{
					if (bHorizontal)
					{
						pElement->m_pBox->m_outerRect.Y = offset_opposite - pElement->m_pBox->m_outerRect.Height;
					}
					else
					{
						pElement->m_pBox->m_outerRect.X = offset_opposite - pElement->m_pBox->m_outerRect.Width;
					}
				}
				else if (m_computedBoxAlign == BoxAlign_center)
				{
					// TODO
					ASSERT(0);
				}
			}
		}
	}

	// Position the child boxes one after the other (either horizontally or vertically)
	offset = 0;
	offset_opposite = 0;

	pos = m_rchildList.GetData();//GetHeadPosition();
	while (pos != m_rchildList.GetData() + m_rchildList.GetSize())
	{
		PNode* pNode = *pos++;//(PNode*)m_rchildList.GetNext(pos);
		if (pNode->m_type == NODE_ELEMENT)
		{
			PElementBase* pElement = (PElementBase*)pNode;

			if (pElement->m_computedDisplayRole != DisplayRole_none)
			{
				m_pBox->AddChildBox(pElement->m_pBox);

				if (bHorizontal)
				{
					pElement->m_pBox->m_outerRect.Translate(offset, 0);
					offset += pElement->m_pBox->m_outerRect.Width;
					offset_opposite = MAX(offset_opposite, pElement->m_pBox->m_outerRect.Height);
				}
				else
				{
					pElement->m_pBox->m_outerRect.Translate(0, offset);
					offset += pElement->m_pBox->m_outerRect.Height;
					offset_opposite = MAX(offset_opposite, pElement->m_pBox->m_outerRect.Width);
				}
			}
		}
	}

	if (bHorizontal)
	{
		m_contentSize.Width = offset;

		ASSERT(m_pBox == pC->m_pBlockBox);
		m_pBox->m_innerRect.Width = offset;
		m_pBox->m_innerRect.Height = offset_opposite;

		m_computedHeight = offset_opposite;	// ???
	}
	else
	{
		m_contentSize.Height = offset;

		ASSERT(m_pBox == pC->m_pBlockBox);
	//	m_pBox->m_innerRect.Height = y;

		ASSERT(0);
		if (true)//m_specifiedHeight != -1)
		{
		//	ASSERT(m_specifiedHeight >= 0);

			pC->m_pBlockBox->m_innerRect.Height = m_computedHeight;
			/*
			pC->m_pBlockBox->m_innerRect.Height = m_specifiedHeight;

			// ??
			pC->m_pBlockBox->m_innerRect.Height -= m_computedMargin[1] + m_computedMargin[3];
			pC->m_pBlockBox->m_innerRect.Height -= m_computedBorderWidth[1] + m_computedBorderWidth[3];
			pC->m_pBlockBox->m_innerRect.Height -= m_computedPadding[1] + m_computedPadding[3];
			*/
		}
		else
			pC->m_pBlockBox->m_innerRect.Height = offset;
	}

	m_pBox->m_outerRect = m_pBox->m_innerRect;
	m_pBox->AdjustOuterRect();
}

int z_index_sort(const void *elem1, const void *elem2)
{
	if ((*(CHTMElementBox**)elem1)->m_pElement->m_computedZIndex == (*(CHTMElementBox**)elem2)->m_pElement->m_computedZIndex)
		return 0;
	else if ((*(CHTMElementBox**)elem1)->m_pElement->m_computedZIndex < (*(CHTMElementBox**)elem2)->m_pElement->m_computedZIndex)
		return -1;
	else
		return 1;
}

void PElementBase::DistributeChildBlocksVertically(CHTMFlowBlockContext* pC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentContentWidth)
{
#if 0
	CComQIPtr<ILDOMElement> element = m_pNode;

	CComBSTR tagName;
	m_pNode->get_nodeName(&tagName);

	CComBSTR className;
	element->getAttribute(OLESTR("class", &className);

	if (className.Length() && !tcscmp(className, OLESTR("navBlock"))
	{
	}
#endif
	ASSERT(m_pBox);
#if 0
	if (m_computedFloat == Float_left)
	{
	}
#endif

	vector<PNode*> rchildList;
	// Collect all children except those with DisplayRole none

	PNode** pos = m_rchildList.begin();//GetHeadPosition();
	while (pos != m_rchildList.end())
	{
		PNode* pPNode = *pos++;//(PNode*)m_rchildList.GetNext(pos);

		if (pPNode->m_type == NODE_ELEMENT)	// Element node
		{
			PElementBase* pPElement = (PElementBase*)pPNode;

			if (pPElement->m_computedDisplayRole != DisplayRole_none)
			{
				rchildList.Add(pPElement);
			}
		}
		else
		{
			rchildList.Add(pPNode);
		}
	}

#if 0
	ASSERT(pC->m_curpos.Y == 0);
//	ASSERT(pC->m_linepos.Y == 0);

	pC->m_curpos.Y = 0;

	
//	pC->m_linepos.Y = 0;
	pC->m_linepos.X = pC->m_floatLeft;
	pC->m_maxx = 0;
#endif

	double y = 0;//pC->m_curpos.Y;//m_customBlockTop;

	double curPosXOfLastStatic = 0;

	m_pBox->m_positioned_children.clear();

	vector<PElementBase*> absoluteList;

	CHTMElementBox* pPrevBox = NULL;

	pos = rchildList.GetData();//GetHeadPosition();
	while (pos != rchildList.GetData() + rchildList.GetSize())
	{
		//CHTMPNode* pGetCurXNode = NULL;

		// Collect sequence of inline nodes to wrap into an anonymous block box
		vector<PNode*> inlineList;

		PNode** pos2 = pos;
		while (pos2 != rchildList.GetData() + rchildList.GetSize())
		{
			PNode* pPNode = *pos2++;//(PNode*)rchildList.GetNext(pos2);

			if (pPNode->m_type == NODE_ELEMENT)	// Element node
			{
				PElementBase* pPElement = (PElementBase*)pPNode;

			//	if (pPElement->m_computedDisplayRole != DisplayRole_none)	// Done above
				{
					if (pPElement->m_computedPosition == Position_absolute)
					{
						inlineList.Add(pPNode);	// Not really inline, but we add it

					//	ASSERT(pPElement->m_computedDisplay == Display_block);

					//	pPElement->m_curPosXOfLastStatic = curPosXOfLastStatic;
					//	absoluteList.AddTail(pPNode);
					}
					else
#if 0
					if (	((pPElement->m_computedDisplay != Display_block) &&
							(pPElement->m_computedDisplay != Display_list_item) &&
							(pPElement->m_computedDisplay != Display_table) &&
							(pPElement->m_computedDisplay != Display_box)) ||

							(pPElement->m_computedFloat != Float_none))	// hmmm..
#endif
							// Not sure here
					if (pPElement->m_computedDisplayRole == DisplayRole_inline)
					{
						inlineList.Add(pPNode);
					}
					else
						break;
				}
			}
			else if (pPNode->m_type == NODE_TEXT)	// Text node
			{
				//if (false)
					inlineList.Add(pPNode);
			}
			else
				ASSERT(0);

			pos = pos2;
		}

		CHTMFlowBlockContext* pC2 = NULL;

		if (inlineList.GetSize() > 0)
		{
			PNode** pos = inlineList.GetData();

			CHTMBlockBox* pBox;

			if ((*pos)->m_pSharedBox == NULL)
			{
				(*pos)->m_pSharedBox = CreateAnonymousBlockBox();	// Anynomous block box around these inline elements/text nodes
				(*pos)->m_pSharedBox->AddRef();	// ??
			}

			if ((*pos)->m_pC == NULL)
			{
				(*pos)->m_pC = new CHTMFlowBlockContext;
			}

			pBox = (*pos)->m_pSharedBox;
		//	ASSERT(pBox->m_refcount == 1);
			pC2 = (CHTMFlowBlockContext*)(*pos)->m_pC;

			pC2->m_pElement = this;

			pC2->m_pBlockBox = pBox;

		//	AddBox(pBox);	// ??

			pBox->m_innerRect.X = 0;
			pBox->m_innerRect.Width = parentContentWidth;

			while (pos != inlineList.end())
			{
				PNode* pPNode = *pos++;//(PNode*)inlineList.GetNext(pos);
			//	CComQIPtr<ICSSBoxModelElement> pPNode = (IUnknown/*CHTMPNode*/*)inlineList.GetNext(pos);

				if (pPNode->m_type == NODE_ELEMENT)
				{
					PElementBase* pPElement = (PElementBase*)pPNode;

#if 0
					if (pPElement->m_computedFloat == Float_left)
					{
					}
#endif

					if (pPElement->m_computedPosition == Position_absolute)
					{
						pPElement->m_curPosXOfLastStatic = curPosXOfLastStatic;
						absoluteList.Add(pPElement);

						continue;
					}
				}

				pPNode->m_pC = NULL;//pC2;	// Only on first in group
				pPNode->m_pSharedBox = pBox;

				pPNode->DistributeInline(pC2, nearestPositioned, stackingContext, parentContentWidth);

			//	MSG msg;
			//	if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
				/*
				if (m_pWindow->m_bLayoutComplete == false)
				{
#if bBreakable
					m_pWindow->m_bLayoutComplete = false;
					break;
#endif
				}
				*/

				curPosXOfLastStatic = pC2->m_curpos.X;	// Remember this for later absolutely positioned elements
			}

			ASSERT(pC2->m_pBlockBox == pBox);

			pC2->m_pBlockBox->m_innerRect.Height = pC2->m_linepos.Y;

			pBox->m_outerRect = pBox->m_innerRect;
		}
		else if (pos != (rchildList.end()) /* && (*pos)->m_type == NODE_ELEMENT*/ /*TODO remove*/ )	// block element
		{
			PElementBase* pPElement = (PElementBase*) *pos++;//(PElementBase*)rchildList.GetNext(pos);

			pPElement->m_pSharedBox = NULL;

			if (pPElement->m_pC == NULL)
			{
				pPElement->m_pC = new CHTMFlowBlockContext;

			}
			else
			{
				TRACE("");
			}
			pC2 = (CHTMFlowBlockContext*)pPElement->m_pC;
#if 0	// ??
			pC2->m_floatLeft = pC->m_floatLeft;	//
			pC2->m_floatBottom = pC->m_floatBottom;	//
			pC2->m_curpos.X = pC2->m_floatLeft;//linepos.X;
#endif

			ASSERT(pPElement->m_computedPosition != Position_absolute);

			{

				ASSERT(pPElement->m_type == NODE_ELEMENT);
				pPElement->DistributeWithinBlock(pC2, nearestPositioned, stackingContext, parentContentWidth);
				ASSERT(pC2->m_pBlockBox == pPElement->m_pBox);

				//MSG msg;
				//if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
				/*
				if (m_pWindow->m_bLayoutComplete == false)
				{
#if bBreakable
					m_pWindow->m_bLayoutComplete = false;
					break;
#endif
				}
				*/


				if (pPElement->m_computedClear != Clear_none)
				{
					// TODO
#if 0
					// Adjust top margin so the box is below any previous floating boxes
					pC2->m_pBlockBox->m_computedMargin[1] += pC->m_floatBottom;
					pC2->m_floatLeft = 0;
#endif
				}

				curPosXOfLastStatic = 0;
			}
		}

		if (pC2->m_pBlockBox)
		{
			if (pC2->m_pBlockBox->m_parentBox != m_pBox)
				m_pBox->AddChildBox(pC2->m_pBlockBox);
//			m_pStackingContext->AddElementBox(pC2->m_pBlockBox);	// ???

		// Adjust for padding/border/margins
		//	pC2->m_pBlockBox->AdjustOuterRect();

#if 0
			pC2->m_pBlockBox->m_innerRect.X += pC2->m_pBlockBox->m_computedMargin[0];
			pC2->m_pBlockBox->m_innerRect.X += pC2->m_pBlockBox->m_computedBorderWidth[0];
			pC2->m_pBlockBox->m_innerRect.X += pC2->m_pBlockBox->m_computedPadding[0];
			pC2->m_pBlockBox->m_outerRect.Width += pC2->m_pBlockBox->m_computedMargin[0] + pC2->m_pBlockBox->m_computedMargin[2];
			pC2->m_pBlockBox->m_outerRect.Width += pC2->m_pBlockBox->m_computedBorderWidth[0] + pC2->m_pBlockBox->m_computedBorderWidth[2];
			pC2->m_pBlockBox->m_outerRect.Width += pC2->m_pBlockBox->m_computedPadding[0] + pC2->m_pBlockBox->m_computedPadding[2];

#if 0
			if (pPrevBox)	// Collapse box margin with previous box margin
			{
			}
			else
#endif
			{
				pC2->m_pBlockBox->m_innerRect.Y += pC2->m_pBlockBox->m_computedMargin[1];
				pC2->m_pBlockBox->m_innerRect.Y += pC2->m_pBlockBox->m_computedBorderWidth[1];
				pC2->m_pBlockBox->m_innerRect.Y += pC2->m_pBlockBox->m_computedPadding[1];
				pC2->m_pBlockBox->m_outerRect.Height += pC2->m_pBlockBox->m_computedMargin[1] + pC2->m_pBlockBox->m_computedMargin[3];
				pC2->m_pBlockBox->m_outerRect.Height += pC2->m_pBlockBox->m_computedBorderWidth[1] + pC2->m_pBlockBox->m_computedBorderWidth[3];
				pC2->m_pBlockBox->m_outerRect.Height += pC2->m_pBlockBox->m_computedPadding[1] + pC2->m_pBlockBox->m_computedPadding[3];
			}
#endif

			pC2->m_pBlockBox->m_outerRect.Y = y;

			if (true || pC2->m_pBlockBox->m_pElement->m_computedFloat == Float_none)	// ???
			{
				y += pC2->m_pBlockBox->m_outerRect.Height;
			}
			else
			{
//				MessageBeep(-1);
			}

#if 0
			// ???
			pC2->m_maxx += pC2->m_pBlockBox->m_computedMargin[0] + pC2->m_pBlockBox->m_computedMargin[2] +
								pC2->m_pBlockBox->m_computedBorderWidth[0] + pC2->m_pBlockBox->m_computedBorderWidth[2] +
								pC2->m_pBlockBox->m_computedPadding[0] + pC2->m_pBlockBox->m_computedPadding[2];
#endif
			pPrevBox = pC2->m_pBlockBox;
		}

		pC->m_maxx = MAX(pC->m_maxx, pC2->m_maxx);

		//
		pC->m_floatLeft = pC2->m_floatLeft;
		pC->m_floatBottom = pC2->m_floatBottom;
		//pC->m_linepos.X = pC2->m_linepos.X;
		//

		pC2->done();
	//	delete pC2;
	}

	// = this;

	{
		PElementBase** pos = absoluteList.begin();//GetHeadPosition();
		while (pos != absoluteList.end())
		{
			PElementBase* pPElement = *pos++;//absoluteList.GetNext(pos);
			ASSERT(pPElement->m_type == NODE_ELEMENT);

			ASSERT(pPElement->m_computedPosition == Position_absolute);

			CHTMFlowBlockContext* pC2 = new CHTMFlowBlockContext;

#if 0
			//pPElement->m_computedWidth = -999999;
			pPElement->m_computedWidth = -1;
#endif

			//ASSERT(pPElement->m_pBox == NULL);

			// z-index only applicable to positioned elements

			PElementBase* stackingContextChildren;
			if (pPElement->m_specifiedZIndex != INT_MIN)	// z-index != auto creates a new stacking context
				stackingContextChildren = pPElement;
			else
				stackingContextChildren = stackingContext;

			pPElement->DistributeWithinBlock(pC2, pPElement/*nearestPositioned*/, stackingContextChildren, parentContentWidth);
			ASSERT(pC2->m_pBlockBox == pPElement->m_pBox);

		//	pC2->m_pBlockBox->AdjustOuterRect();

			pC2->m_pBlockBox->m_outerRect.Translate(
				pC2->m_pBlockBox->m_pElement->m_computedLeft,
				pC2->m_pBlockBox->m_pElement->m_computedTop);

#if 0
			m_pBox->AddChildBox(pC2->m_pBlockBox);
#endif
			ASSERT(pPElement->m_pBox);
			pPElement->m_pBox->AddRef();
			pPElement->m_pBox->m_parentBox = nearestPositioned->m_pBox;	// layout parent

			stackingContext->m_pBox->m_positioned_children.push_back(pPElement->m_pBox);

		//	m_pBox->m_positioned_children.push_back(pPElement->m_pBox);

			//m_pStackingContext->AddElementBox(pC2->m_pBlockBox);	// ???
			//AddBox(

		//	y = max(y, pC2->m_pBlockBox->m_outerRect.GetBottom());
		//	pC->m_maxx = max(pC->m_maxx, pC2->m_pBlockBox->m_outerRect.GetRight());

			delete pC2;
		}
	}

	y += m_customBlockBottom;

	m_contentSize.Height = y;
	m_contentSize.Width = pC->m_maxx;

	ASSERT(pC->m_pBlockBox);

//	pC->m_pBlockBox->m_innerRect.Width = m_computedWidth;
//	pC->m_pBlockBox->m_innerRect.Height = y;

/*
	if (m_computedPosition == Position_absolute)
	{
		m_computedWidth = pC->m_maxx;
		//m_computedMargin[2] -= 

		pC->m_pBlockBox->m_innerRect.Width = m_computedWidth;
	}
	else
	{
		pC->m_pBlockBox->m_innerRect.Width = m_computedWidth;
	}

	if (m_computedHeight < 0)
		m_computedHeight = y;

	pC->m_pBlockBox->m_innerRect.Height = m_computedHeight;
*/

///*
	//ASSERT(0);
#if 0
	if (m_specifiedHeight != -1)
		pC->m_pBlockBox->m_innerRect.Height = m_specifiedHeight;
	else
#endif
		pC->m_pBlockBox->m_innerRect.Height = y;

	//ASSERT(0);
//#if 0	// ??
	if (m_computedWidth != -1)
		pC->m_pBlockBox->m_innerRect.Width = m_computedWidth;
	else
//#endif
		pC->m_pBlockBox->m_innerRect.Width = pC->m_maxx;
//*/

	//if (m_computedPosition == Position_absolute)
	{
		//if (m_specifiedZIndex != INT_MIN)	// specified z-index != auto
		{
			qsort(m_pBox->m_positioned_children.begin(), m_pBox->m_positioned_children.size(), sizeof(void*), z_index_sort);

			/*
			for (int i = 1; i < m_pBox->m_positioned_children.size(); i++)
			{
				ASSERT(m_pBox->m_positioned_children[i]->m_pElement->m_computedZIndex >= m_pBox->m_positioned_children[i-1]->m_pElement->m_computedZIndex);
			}
			*/
		}
	}
}

void PElementBase::DistributeChildLinesInBlock(CHTMFlowBlockContext* pC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentContentWidth)
{
#if 0
	ASSERT(pC->m_linepos.Y == 0);
	pC->m_linepos.Y += m_customBlockTop;
#endif

	/*
	if (m_bArrangeValid)
		return;

	m_bArrangeValid = true;
	*/

//	PNode** pos = m_rchildList.GetData();
	//while (pos != m_rchildList.end())
	for (m_lastindex = 0; m_lastindex < m_rchildList.GetSize(); m_lastindex++)
	{
		PNode* pPNode = m_rchildList[m_lastindex];//*pos++;
		ASSERT(pPNode->m_rparent == this);

		if (pPNode->m_type == NODE_ELEMENT)
		{
			PElementBase* pPElement = (PElementBase*)pPNode;
			if (pPElement->m_computedDisplayRole == DisplayRole_none)
				continue;
		}

		pPNode->DistributeInline(pC, nearestPositioned, stackingContext, parentContentWidth);

//		MSG msg;
//		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		/*
		if (m_pWindow->m_bLayoutComplete == false)
		{
#if bBreakable
					m_pWindow->m_bLayoutComplete = false;
					break;
#endif
		}
		*/
	}

#if 0
	pC->m_linepos.Y += m_customBlockBottom;
#endif
	double y = pC->m_linepos.Y;

	m_contentSize.Height = y;
	m_contentSize.Width = pC->m_maxx;

	ASSERT(pC->m_pBlockBox);

/*
	pC->m_pBlockBox->m_innerRect.Width = m_computedWidth;

	if (m_computedHeight < 0)
		m_computedHeight = y;

	pC->m_pBlockBox->m_innerRect.Height = m_computedHeight;
*/

/*
	if (m_specifiedHeight != -1)
		pC->m_pBlockBox->m_innerRect.Height = m_specifiedHeight;
	else
		pC->m_pBlockBox->m_innerRect.Height = y;

	if (m_specifiedWidth >= 0)
		pC->m_pBlockBox->m_innerRect.Width = m_specifiedWidth;
	else
		pC->m_pBlockBox->m_innerRect.Width = pC->m_maxx;
		*/

//	m_pBox->m_outerRect = m_Box->m_innerRect;
//	m_pBox->AdjustOuterRect();
}

// virtual
void PElementBase::DistributeInline(CHTMFlowContext* pParentC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentContentWidth)
{
//	if (m_bArrangeValid)
//		return;

	m_bArrangeValid = true;

#if 0
	CComQIPtr<ILDOMElement> element = m_pNode;

	CComBSTR tagName;
	m_pNode->get_nodeName(&tagName);

	CComBSTR className;
	element->getAttribute(OLESTR("class", &className);

	if (className.Length() && !tcscmp(className, OLESTR("navBlock"))
	{
	}
#endif

//	ASSERT(m_boxList.GetSize()==0);
//	m_boxList.RemoveAll();

	//if (m_computedDisplay == Display_block)
	if (false && m_computedDisplayModel == DisplayModel_block_inside)
	{
//		ASSERT(0);
	//	m_pBox = CreateBlockBox();

#if 0
		if (!tcscmp(tagName, OLESTR("hr"))
		{
		}

		if (m_computedFloat == Float_left)
		{
		}
#endif

#if 0
		double width;

		//ATLTRACE("TODO here\n");
#if 0
		ASSERT(0);
		if (m_specifiedWidth >= 0)
		{
			ASSERT(0);
			width = m_computedWidth;
		}
		else
#endif
		//	ASSERT(0);
		{
	// TODO, calculate maxWidth somewhere else

			//pC->m_floatLeft = pParentC->m_floatLeft;
			//pC->m_floatBottom = pParentC->m_floatBottom;

			double oldm[4];
			double oldp[4];
			double oldbw[4];
			{
				for (int i = 0; i < 4; i++)
				{
					oldm[i] = m_computedMargin[i];
					oldp[i] = m_computedPadding[i];
					oldbw[i] = m_computedBorderWidth[i];
				}
			}

			CHTMFlowBlockContext pC2;// = new CHTMFlowBlockContext;
			DistributeWithinBlock(&pC2, 0xfffffff);
			m_pBox->m_innerRect.Width = pC2.m_maxx;
			//delete pC2;

			m_pBox->m_outerRect = m_pBox->m_innerRect;

			{
				for (int i = 0; i < 4; i++)
				{
					m_computedMargin[i] = oldm[i];
					m_computedPadding[i] = oldp[i];
					m_computedBorderWidth[i] = oldbw[i];

					m_pBox->m_computedMargin[i] = oldm[i];
					m_pBox->m_computedPadding[i] = oldp[i];
					m_pBox->m_computedBorderWidth[i] = oldbw[i];
				}
			}

			m_pBox->AdjustOuterRect();

			width = m_pBox->m_outerRect.Width;

			RemoveBoxesAndChildren();
		}

		double oldm[4];
		double oldp[4];
		double oldbw[4];
		{
			for (int i = 0; i < 4; i++)
			{
				oldm[i] = m_computedMargin[i];
				oldp[i] = m_computedPadding[i];
				oldbw[i] = m_computedBorderWidth[i];
			}
		}

		CHTMFlowBlockContext pC2;// = new CHTMFlowBlockContext;
		DistributeWithinBlock(&pC2, width);
		ASSERT(pC2.m_pBlockBox == m_pBox);
		//delete pC2;

		{
			for (int i = 0; i < 4; i++)
			{
				m_computedMargin[i] = oldm[i];
				m_computedPadding[i] = oldp[i];
				m_computedBorderWidth[i] = oldbw[i];

				m_pBox->m_computedMargin[i] = oldm[i];
				m_pBox->m_computedPadding[i] = oldp[i];
				m_pBox->m_computedBorderWidth[i] = oldbw[i];
			}
		}

		m_pBox->AdjustOuterRect();

#if 0
		CHTMFlowInlineContext* pInlineC = new CHTMFlowInlineContext;
		pInlineC->m_pParentC = pParentC;
		pInlineC->m_pElement = this;
	//	pInlineC->m_floatLeft = pParentC->m_floatLeft;	//
	//	pInlineC->m_floatBottom = pParentC->m_floatBottom;	//

		//pC->Pla
		pInlineC->PlaceInlineBox(m_pBox);
#endif
#endif

		if (m_pC == NULL)
		{
			CHTMFlowBlockContext* pC2 = new CHTMFlowBlockContext;
			m_pC = pC2;
			ASSERT(m_pBox == NULL || m_pBox->m_parentBox == NULL);
		}

		DistributeWithinBlock((CHTMFlowBlockContext*)m_pC, nearestPositioned, stackingContext, 200);

		pParentC->PlaceOnSame(NULL, m_pBox);
		pParentC->PlaceInlineBox2(NULL, m_pBox);

//		pParentC->PlaceInlineBox(m_pBox);
	//	AddBox(m_pBox);	// ??

	//	pParentC->m_floatLeft = pInlineC->m_floatLeft;
	//	pParentC->m_floatBottom = pInlineC->m_floatBottom;

		//pParentC->m_maxx = max(pParentC->m_maxx);//, pInlineC->m_maxx);
	}
	else
	{
		// TODO Here ???
		CSSContext context;
		CSSContext* pCSSContext = &context;

		CalculateComputedCSSProperty(pCSSContext, CSSProperty_width);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_height);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_min_width);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_max_width);

		CalculateComputedCSSProperty(pCSSContext, CSSProperty_left);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_right);

		CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_left_width);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_top_width);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_right_width);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_bottom_width);

		CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_left);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_top);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_right);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_bottom);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_left);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_top);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_right);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_bottom);

		if (HasDistributableChildren())	// inline non-replaced element
		{
			if (m_pC == NULL)
			{
				CHTMFlowInlineContext* pInlineC = new CHTMFlowInlineContext;
				m_pC = pInlineC;
			}
			/*
			else
			{
				if (pParentC->m_curpos.X != 0)
					TRACE("");
				TRACE("");
			}
			*/
			//CHTMFlowInlineContext* pInlineC = new CHTMFlowInlineContext;

			CHTMFlowContext* pInlineC = m_pC;

			pInlineC->m_pParentC = pParentC;
			pInlineC->m_pElement = this;
			pInlineC->m_floatLeft = pParentC->m_floatLeft;	//
			pInlineC->m_floatBottom = pParentC->m_floatBottom;	//
			pInlineC->m_pPseudoFirstLineElement = pParentC->m_pPseudoFirstLineElement;

			if (m_pStartTagBox)
			{
				m_pStartTagBox->m_parentBox = NULL;
				m_pStartTagBox->m_outerRect.X = 0;
				m_pStartTagBox->m_outerRect.Y = 0;
				// Width/Height are aldready set

				pInlineC->PlaceInlineBox(m_pStartTagBox);
			}

			PNode** pos = pInlineC->m_pElement->m_rchildList.GetData();//.GetHeadPosition();
			while (pos != pInlineC->m_pElement->m_rchildList.GetData() + pInlineC->m_pElement->m_rchildList.GetSize())
			{
				PNode* pPNode = *pos++;//(PNode*)pInlineC->m_pElement->m_rchildList.GetNext(pos);

				if (pPNode->m_type == NODE_ELEMENT)
				{
					PElementBase* pPElement = (PElementBase*)pPNode;
					if (pPElement->m_computedDisplayRole == DisplayRole_none)
					{
						continue;	// Skip this one
					}
				}

				pPNode->DistributeInline(pInlineC, nearestPositioned, stackingContext, parentContentWidth);

			//	MSG msg;
			//	if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
				/*
				if (m_pWindow->m_bLayoutComplete == false)
				{
#if bBreakable
					m_pWindow->m_bLayoutComplete = false;
					break;
#endif
				}
				*/
			}

			if (m_pEndTagBox)
			{
				m_pEndTagBox->m_parentBox = NULL;
				m_pEndTagBox->m_outerRect.X = 0;
				m_pEndTagBox->m_outerRect.Y = 0;
				// Width/Height are aldready set

				pInlineC->PlaceInlineBox(m_pEndTagBox);
			}

			//
			pParentC->m_floatLeft = pInlineC->m_floatLeft;
			pParentC->m_floatBottom = pInlineC->m_floatBottom;
			pParentC->m_pPseudoFirstLineElement = pInlineC->m_pPseudoFirstLineElement;
			//

			pInlineC->done();
#if 0
			delete pInlineC;
#endif
		}
		else	// inline replaced element
		{
			CHTMFlowInlineContext* pInlineC = new CHTMFlowInlineContext;
			pInlineC->m_pParentC = pParentC;
			pInlineC->m_pElement = this;
			pInlineC->m_floatLeft = pParentC->m_floatLeft;	//
			pInlineC->m_floatBottom = pParentC->m_floatBottom;	//

			gm::SizeD size = GetIntrinsicSize();
			if (size.Width == -1)
			{
				size.Width = 300;
				size.Height = 300;
			}

			// TODO, intrinsic percentages
			ASSERT(size.Width >= -1);
			ASSERT(size.Height >= -1);

			if (m_computedWidth == -1 && m_computedHeight == -1)
			{
				m_computedWidth = size.Width;
				m_computedHeight = size.Height;
			}
			else if (m_computedWidth == -1 && m_computedHeight != -1)
			{
				double ratio = size.Width / size.Height;
				m_computedWidth = m_computedHeight * ratio;
			}
			else if (m_computedWidth != -1 && m_computedHeight == -1)
			{
				double ratio = size.Height / size.Width;
				m_computedHeight = m_computedWidth * ratio;
			}
			/*
			else
			{
				m_computedWidth = 300;	// px
				m_computedHeight = 300;	// px
			}
			*/
	#if 0
			ASSERT(m_pBox == NULL);
			if (m_pBox)	// TODO, this shouldn't be necessary
			{
				CHTMBlockBox* pBox = m_pBox;
				m_pBox = NULL;
				delete pBox;
			}
	#endif

			if (m_pBox == NULL)
			{
				m_pBox = CreateBlockBox();
				m_pBox->AddRef();
			}

#if 0
			// TODO, don't do this
			if (TRUE)
			{
				pInlineC->m_pElement->m_computedWidth = pInlineC->m_pElement->m_specifiedWidth;
				pInlineC->m_pElement->m_computedHeight = pInlineC->m_pElement->m_specifiedHeight;
			}
#endif

#if 0
			CalculateBoundsAndChildren();	// ??
#endif

			m_pBox->m_outerRect.X = 0;
			m_pBox->m_outerRect.Y = 0;
			m_pBox->m_outerRect.Width = m_computedWidth;
			m_pBox->m_outerRect.Height = m_computedHeight;

			m_pBox->m_innerRect = m_pBox->m_outerRect;

			pInlineC->PlaceInlineBox(m_pBox);

			//
			pParentC->m_floatLeft = pInlineC->m_floatLeft;
			pParentC->m_floatBottom = pInlineC->m_floatBottom;
			//

			delete pInlineC;
		}
	}
}

PElementBase* GetDefinedPseudoElement(PElementBase* pElement, StringIn pseudoEltName)
{
	for (int i = 0; i < 5/*pElement->m_pseudoElements.GetSize()*/; i++)
	{
		if (pElement->m_pseudoElements[i] && pElement->m_pseudoElements[i]->m_pseudoElementName == pseudoEltName)
		{
			return pElement->m_pseudoElements[i];
		}
	}

	return NULL;
}

void PElementBase::DeleteFlow()
{
	PNode** pos = m_rchildList.GetData();
	while (pos != m_rchildList.GetData() + m_rchildList.GetSize())
	{
		PNode* pPNode = *pos++;//(PNode*)m_rchildList.GetNext(pos);

		pPNode->m_bArrangeValid = false;

		if (pPNode->m_pC)
		{
			delete pPNode->m_pC;
			pPNode->m_pC = NULL;
		}

		if (pPNode->m_type == NODE_ELEMENT)	// Element node
		{
			PElementBase* pPElement = (PElementBase*)pPNode;
			pPElement->DeleteFlow();
		}
	}
}

void PElementBase::DistributeBlockInsideChildren(CHTMFlowBlockContext* pC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentContentWidth)
{
	bool bHasBlockChild = false;
	{
		PNode** pos = m_rchildList.GetData();
		while (pos != m_rchildList.GetData() + m_rchildList.GetSize())
		{
			PNode* pPNode = *pos++;//(PNode*)m_rchildList.GetNext(pos);

			if (pPNode->m_type == NODE_ELEMENT)	// Element node
			{
				PElementBase* pPElement = (PElementBase*)pPNode;

				if (pPElement->m_computedDisplayRole != DisplayRole_none)
				{
	#if 0
					if (	((pPElement->m_computedDisplay == Display_block) ||
							(pPElement->m_computedDisplay == Display_list_item) ||
							(pPElement->m_computedDisplay == Display_table) ||
							(pPElement->m_computedDisplay == Display_box)) &&

							// Really block, but treat as inline for now
							(pPElement->m_computedFloat == Float_none))
	#endif
					if (pPElement->m_computedDisplayRole != DisplayRole_inline)
					{
						bHasBlockChild = true;
						break;
					}
				}
			}
		}
	}

	if (m_pBox == NULL)
	{
		m_pBox = CreateBlockBox();	// Principal box
		m_pBox->AddRef();
	}

	m_pBox->m_outerRect.X = 0;
	m_pBox->m_outerRect.Y = 0;

	{	// TODO, put in a function
		m_pBox->m_computedBorderWidth[0] = m_computedBorderWidth[0];
		m_pBox->m_computedBorderWidth[1] = m_computedBorderWidth[1];
		m_pBox->m_computedBorderWidth[2] = m_computedBorderWidth[2];
		m_pBox->m_computedBorderWidth[3] = m_computedBorderWidth[3];

		m_pBox->m_computedPadding[0] = m_computedPadding[0];
		m_pBox->m_computedPadding[1] = m_computedPadding[1];
		m_pBox->m_computedPadding[2] = m_computedPadding[2];
		m_pBox->m_computedPadding[3] = m_computedPadding[3];

		m_pBox->m_computedMargin[0] = m_computedMargin[0];
		m_pBox->m_computedMargin[1] = m_computedMargin[1];
		m_pBox->m_computedMargin[2] = m_computedMargin[2];
		m_pBox->m_computedMargin[3] = m_computedMargin[3];

		m_pBox->m_computedBackgroundColor = m_computedBackgroundColor;
		m_pBox->m_pBackgroundImage = m_pBackgroundImage;

		m_pBox->m_opacity = (uint8)(m_computedOpacity*255);
	}
	/*
	if (m_pBox->m_children.size() != 0)
	{
//		MessageBeep(-1);
	}
	*/

//	ASSERT(m_pBox->m_children.size() == 0);

//	ASSERT(pC->m_pBlockBox == NULL);
	pC->m_pBlockBox = m_pBox;

//	AddBox(m_pBox);

#if 0	// TODO
	if (m_computedDisplay == Display_list_item)
	{
		m_pBox->m_innerRect.Width = m_computedWidth - 10;
	}
	else
#endif

	m_pBox->m_innerRect.X = 0;
	m_pBox->m_innerRect.Y = 0;

	m_pBox->m_innerRect.Width = m_computedWidth;

	m_pBox->m_outerRect.Width = m_pBox->m_innerRect.Width;	// Does this need to be set here

	//m_bVScroll = FALSE;
	m_bHScroll = false;
	if (m_bVScroll)
	{
		m_computedOverflowY = Overflow_scroll;	// hm..
		m_pBox->m_innerRect.Width -= 16;	// Make room for scrollbar
	}

/* From CSS spec:
Block-level elements generate a principal block box that only
contains block boxes. The principal block box establishes the
containing block for descendant boxes and generated content and
is also the box involved in any positioning scheme. Principal
block boxes participate in a block formatting context
*/

	// Block formatting context, all children elements are block boxes and
	// distributed vertically

#if 0
	if (m_bHasBlockChild != 3/*(unsigned)-1*/ && bHasBlockChild != m_bHasBlockChild)
#endif
	{
		DeleteFlow();
		/*
		if (m_pC)
		{
			delete m_pC;
			m_pC = NULL;
		}
		*/
		m_pBox->DeleteChildBoxes();
	}

	m_bHasBlockChild = bHasBlockChild;

	if (bHasBlockChild)
	{
		DistributeChildBlocksVertically(pC, nearestPositioned, stackingContext, m_pBox->m_innerRect.Width);
	}
	else
	{
//		m_pBox->DeleteChildBoxes();
		DistributeChildLinesInBlock(pC, nearestPositioned, stackingContext, m_pBox->m_innerRect.Width);
	}

	ASSERT(m_pBox == pC->m_pBlockBox);
///
	if (m_computedPosition == Position_absolute)
	{
		m_computedWidth = pC->m_maxx;
	//m_computedMargin[2] -= 

		m_pBox->m_innerRect.Width = m_computedWidth;
		m_pBox->m_outerRect.Width = m_pBox->m_innerRect.Width;	// ??
	}
	else
	{
		m_pBox->m_innerRect.Width = m_computedWidth;
	}

	if (m_computedHeight < 0)
		m_computedHeight = m_contentSize.Height;

	m_pBox->m_innerRect.Height = m_computedHeight;

///
	if (m_computedOverflowY == Overflow_scroll &&/* m_specifiedHeight > -1 &&*/ !m_bVScroll)
	{
	// If the contents of the elements exceeds it's height attribute, add a
	// vertical scrollbar and reflow again

		if (m_contentSize.Height > m_computedHeight)
		{
			m_bVScroll = true;
			m_pBox->m_innerRect.Width -= 16;	// Make room for scrollbar

#if 0
		// Delete the generated boxes from previous flow
			//m_pBox->DeleteChildBoxes();
			RemoveBoxesAndChildren();	// TODO, don't delete m_pBox

			pC->m_linepos.X = pC->m_linepos.Y = 0;
			pC->m_curpos.X = pC->m_curpos.Y = 0;
			pC->m_maxx = 0;
			pC->m_pCurLineBox = NULL;

			if (bHasBlockChild)
			{
				DistributeChildBlocksVertically(pC, m_pBox->m_innerRect.Width);
			}
			else
			{
				DistributeChildLinesInBlock(pC, m_pBox->m_innerRect.Width);
			}
#endif
		}
	}
	else if (m_bVScroll)
	{
		m_pBox->m_innerRect.Width -= 16;	// ??
	}

	m_pBox->m_outerRect.Height = m_pBox->m_innerRect.Height;

	if (m_computedOverflowX == Overflow_scroll)
	{
	//	ASSERT(0);
//#if 0
//		if (m_specifiedWidth > -1)
		{
			if (m_contentSize.Width > m_pBox->m_innerRect.Width/*m_width*/)
			{
				m_bHScroll = true;
				m_pBox->m_innerRect.Height -= 16;	// Make room for scrollbar
			}
		}
//#endif
	}

#if 0	// TODO
	if (m_computedDisplay == Display_list_item)
	{
		pC->m_maxx += 10;
		m_pBox->m_innerRect.Offset(10, 0);	// ??
	}
#endif

//	pC2->m_pBlockBox->m_outerRect = pC2->m_pBlockBox->m_innerRect;	// Maybe I don't need this here

	m_pBox->AdjustOuterRect();

	CreateScrollBars(pC);
}

void PElementBase::DistributeBlockChildren(CHTMFlowBlockContext* pC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentwidth)
{
	// text-indent
	/*
	This property specifies the indentation of the first line of text in a block. More precisely, it specifies the indentation of the first box that flows into the block's first line box
	*/
	{
#if 0
		CComQIPtr<ILDOMDocument> document = m_pView->m_document;
		ASSERT(document);

		CComQIPtr<ILDOMDocumentView> documentView = document;
		ASSERT(documentView);
		//document->get_isXML(&m_pWindow->m_isXML);	// TODO, do only once
#endif

#if 0
		DocumentStyleImpl* documentStyle = NULL;//m_pView;
		ASSERT(documentStyle);

		CSSValue* cssValue = NULL;
		CSSPrimitiveValue* cssprimitiveValue = NULL;
		CSSUnitType unitType;
#endif

		m_computedTextIndent = 0;
#if 0
		{
			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_text_indent);
			cssprimitiveValue->get_primitiveType(&m_specifiedTextIndentUnit);

			if (m_specifiedTextIndentUnit == CSS_PERCENTAGE)
			{
				cssprimitiveValue->getFloatValue(CSS_PERCENTAGE, &m_specifiedTextIndent);
			}
			else
			{
				cssprimitiveValue->getFloatValue(CSS_PX, &m_specifiedTextIndent);
			}

			if (m_specifiedTextIndentUnit == CSS_PERCENTAGE)
			{
				// ??
				m_computedTextIndent = parentContentWidth*m_specifiedTextIndent/100;
			}
			else
			{
				m_computedTextIndent = m_specifiedTextIndent;
			}
		}
#endif
	}

#if 0	// TODO, have this somewhere
	pC->m_curpos.X = m_computedTextIndent;
#endif

	if ((m_computedDisplayModel == DisplayModel_block_inside) ||
		(m_computedDisplayModel == DisplayModel_inline_inside))
	{
#if 0	// TODO
		if (m_computedDisplayRole == DisplayRole_list_item)
		{
			if (m_computedContent != NULL)
			{
				if (m_computedListStylePosition == ListStylePosition_outside)
				{
					//CHTMFlowBlockContext* pC = new CHTMFlowBlockContext;

					//pPNode->DistributeInline(pInlineC, parentContentWidth);
					//pC->

#if 0
					m_pMarkerPseudoElement->DistributeInline(pC);
#endif

					//pC->m_linepos.Y;

					//delete pC;
				}
				else
				{
					// TODO
					ASSERT(0);
				}
			}
			else
			{
				// as normal block
				DistributeBlockInsideChildren(pC, parentwidth);
			}
		}
		else
#endif
		{
			DistributeBlockInsideChildren(pC, nearestPositioned, stackingContext, parentwidth);
		}
	}
	else if (m_computedDisplayModel == DisplayModel_table)
	{
		if (m_pBox == NULL)
		{
			m_pBox = CreateBlockBox();	// Principal box
			m_pBox->AddRef();
		}
	
		ASSERT(m_pBox->m_children.size() == 0);

		ASSERT(pC->m_pBlockBox == NULL);
		pC->m_pBlockBox = m_pBox;

	//	AddBox(m_pBox);	// ??

		m_pBox->m_innerRect.Width = m_computedWidth;//parentContentWidth;

		DistributeTableChildren(pC, nearestPositioned, stackingContext, m_pBox->m_innerRect.Width);

		m_pBox->m_outerRect = m_pBox->m_innerRect;
	}
	else if (m_computedDisplayModel == DisplayModel_box)
	{
		if (m_pBox == NULL)
		{
			m_pBox = CreateBlockBox();	// Principal box
			m_pBox->AddRef();
		}

		if (m_pBox->m_children.GetSize() != 0)
		{
			MessageBeep(-1);
		}

		ASSERT(m_pBox->m_children.size() == 0);

		ASSERT(pC->m_pBlockBox == NULL);
		pC->m_pBlockBox = m_pBox;

		m_pBox->m_innerRect.Width = m_computedWidth;//parentContentWidth;

		DistributeBoxChildren(pC, nearestPositioned, stackingContext, m_pBox->m_innerRect.Width);

		m_pBox->m_outerRect = m_pBox->m_innerRect;
	}
	else
		ASSERT(0);
}

void PElementBase::CalculateWidthsAndMarginsStatic(double parentContentWidth, double values[7])
{

//	ASSERT(0);
#if 0
	m_computedWidth = m_specifiedWidth;	// hm..TODO %
	m_computedLeft = m_specifiedLeft;	// hm..TODO %
	m_computedRight = m_specifiedRight;	// hm..TODO %
#endif
#if 0
	// Convert percentages
	for (int i = 0; i < 7; i++)
	{
		if (*values[i] < -1)
		{
			*values[i] = parentContentWidth * -(*values[i]+1) / 100;
		}
	}
#endif

	// If there is exactly one value specified as 'auto', its used value follows from the equality. 
	double sumOfNonAuto = 0;
	int autocount = 0;
	int indexOfOnlyAuto = -1;

	int i;

	for (i = 0; i < 7; i++)
	{
		if (values[i] == -1)
		{
			autocount++;
			indexOfOnlyAuto = i;
		}
		else
			sumOfNonAuto += values[i];
	}

// If all of the above have a computed value other than 'auto', the values are said to be "over-constrained" and one of the used values will have to be different from its computed value. If the 'direction' property has the value 'ltr', the specified value of 'margin-right' is ignored and the value is calculated so as to make the equality true. If the value of 'direction' is 'rtl', this happens to 'margin-left' instead. 
	if (autocount == 0)
	{
		if (true)	// direction == ltr
		{
			values[6] =	parentContentWidth -
								values[3] -
								values[0] -
								values[1] - values[5] -
								values[2] - values[4];
		}
		else
		{
			ASSERT(0);
#if 0
			m_computedMargin[0] =	parentContentWidth -
								m_computedWidth -
								m_computedMargin[2] -
								m_computedBorderWidth[0] - m_computedBorderWidth[2] -
								m_computedPadding[0] - m_computedPadding[2];
#endif
		}
	}
// If there is exactly one value specified as 'auto', its used value follows from the equality. 
	else if (autocount == 1)
	{
		values[indexOfOnlyAuto] = parentContentWidth - sumOfNonAuto;
	}
// If 'width' is set to 'auto', any other 'auto' values become '0' and 'width' follows from the resulting equality. 
	else if (m_computedWidth == -1)
	{
		for (i = 0; i < 7; i++)
		{
			if (values[i] == -1)
			{
				values[i] = 0;
			}
		}

		values[3] =	parentContentWidth -
							values[0] - values[6] -
							values[1] - values[5] -
							values[2] - values[4];
	}
// If both 'margin-left' and 'margin-right' are 'auto', their used values are equal. This horizontally centers the element with respect to the edges of the containing block. 
	else if (values[0] == -1 && values[6] == -1)
	{
		double spaceLeft = parentContentWidth -
							values[3] -
							values[1] - values[5] -
							values[2] - values[4];

		values[0] = spaceLeft/2;
		values[6] = spaceLeft/2;
	}
}

void PElementBase::DistributeWithinBlock(CHTMFlowBlockContext* pC, PElementBase* nearestPositioned, PElementBase* stackingContext, double parentContentWidth)
{
//	ASSERT(m_boxList.GetSize()==0);

//	ASSERT(pC->m_pBlockBox == NULL);	// We should create the box ourselves
	pC->m_pElement = this;

	{
		PElementBase* pPseudoFirstLineElement = GetDefinedPseudoElement(this, WSTR("first-line"));

		pC->m_pPseudoFirstLineElement = pPseudoFirstLineElement;
	}

	PElementBase* pParent = m_rparent;

// 10.3.5 Floating, non-replaced elements
	if (m_computedFloat != Float_none)
	{
		ASSERT(0);
#if 0
// If 'left', 'right', 'width', 'margin-left', or 'margin-right' are specified as 'auto', their computed value is '0'. 
		if (m_specifiedLeft == -1) m_computedLeft = 0;
		if (m_specifiedRight == -1) m_computedRight = 0;

		if (m_specifiedWidth == -1)
			m_computedWidth = 0;
		else
			m_computedWidth = m_specifiedWidth;	// ???

		//if (m_specifiedRight == -1) m_computedRight = 0;
		//if (m_specifiedRight == -1) m_computedRight = 0;

		double* values[9];
		values[0] = &m_computedLeft;
		values[1] = &m_computedMargin[0];
		values[2] = &m_computedBorderWidth[0];
		values[3] = &m_computedPadding[0];
		values[4] = &m_computedWidth;
		values[5] = &m_computedPadding[2];
		values[6] = &m_computedBorderWidth[2];
		values[7] = &m_computedMargin[2];
		values[8] = &m_computedRight;

		{
			// Convert percentages
			for (int i = 0; i < 9; i++)
			{
				if (*values[i] < -1)
				{
					*values[i] = parentContentWidth * -(*values[i]+1) / 100;
				}
			}
		}
#endif
	}
// 10.3.3 Block-level, non-replaced elements in normal flow
	else if (m_computedPosition == Position_static/* || m_computedPosition == Position_absolute*/)
	{
		if (!HasDistributableChildren())	// replaced element
		{
			ASSERT(0);
			exit(1);
		}
	/*
	if (m_specifiedWidth == -1)	// auto
	{
		m_computedWidth =	parentContentWidth -
						m_computedMargin[0] - m_computedMargin[2] -
						m_computedBorderWidth[0] - m_computedBorderWidth[2] -
						m_computedPadding[0] - m_computedPadding[2];
	}
	else
	*/
		/*
		if (m_specifiedWidth < -1)	// % of parent containing block
		{
			double pcnt = -(m_specifiedWidth+1);
			m_computedWidth = parentContentWidth*pcnt/100;
		}
		else	// absolute value specified
			m_computedWidth = m_specifiedWidth;
			*/
		CSSContext context;
		CSSContext* pCSSContext = &context;

		//if (!m_bCSSPropertiesValid2)
		{
			m_bCSSPropertiesValid2 = true;


			CalculateComputedCSSProperty(pCSSContext, CSSProperty_width);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_min_width);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_max_width);

			CalculateComputedCSSProperty(pCSSContext, CSSProperty_left);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_right);

			CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_left_width);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_right_width);

			CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_left);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_right);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_left);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_top);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_right);
		}

		CalculateComputedCSSProperty(pCSSContext, CSSProperty_height);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_top_width);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_bottom_width);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_top);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_bottom);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_bottom);

		//m_computedMargin[2] = -1;

		double values[7];

		values[0] = m_computedMargin[0];
		values[1] = m_computedBorderWidth[0];
		values[2] = m_computedPadding[0];
		values[3] = m_computedWidth;
		values[4] = m_computedPadding[2];
		values[5] = m_computedBorderWidth[2];
		values[6] = m_computedMargin[2];

		/*
			if (m_computedMargin[2] != 0)
			{
				MessageBeep(-1);
			}
			*/

		CalculateWidthsAndMarginsStatic(parentContentWidth, values);
		if (m_computedMaxWidth > -1 && values[3] > m_computedMaxWidth)
		{
			values[0] = m_computedMargin[0];
			values[1] = m_computedBorderWidth[0];
			values[2] = m_computedPadding[0];
			values[3] = m_computedMaxWidth;
			values[4] = m_computedPadding[2];
			values[5] = m_computedBorderWidth[2];
			values[6] = m_computedMargin[2];

			CalculateWidthsAndMarginsStatic(parentContentWidth, values);
		}

		// If the 'width' results in less than a minimum width, substitute 'width'
	// with that minimum with and compute the equation again
		if (values[3] < m_computedMinWidth)
		{
			values[0] = m_computedMargin[0];
			values[1] = m_computedBorderWidth[0];
			values[2] = m_computedPadding[0];
			values[3] = m_computedMinWidth;
			values[4] = m_computedPadding[2];
			values[5] = m_computedBorderWidth[2];
			values[6] = m_computedMargin[2];

			CalculateWidthsAndMarginsStatic(parentContentWidth, values);
		}

		m_computedMargin[0] = values[0];
		m_computedBorderWidth[0] = values[1];
		m_computedPadding[0] = values[2];
		m_computedWidth = values[3];
		m_computedPadding[2] = values[4];
		m_computedBorderWidth[2] = values[5];
		m_computedMargin[2] = values[6];

#if WIN32
		ASSERT(fabs((m_computedMargin[0]+m_computedBorderWidth[0]+m_computedPadding[0]+m_computedWidth+m_computedMargin[2]+m_computedBorderWidth[2]+m_computedPadding[2]) - parentContentWidth) < 0.001);
#endif
	}
	else if (m_computedPosition == Position_fixed)
	{
		ASSERT(0);
	}
	else if (m_computedPosition == Position_absolute)
	{
/* CSS2, boxmodel
10.3.7 Absolutely positioned, non-replaced elements
The constraint that determines the computed values for these elements is: 

'left' + 'margin-left' + 'border-left-width' + 'padding-left' + 'width' + 'padding-right' + 'border-right-width' + 'margin-right' + 'right' = width of containing block 

(If the border style is 'none', use '0' as the border width.) The solution to this constraint is reached through a number of substitutions in the following order:


If 'left', 'right' or 'width' are (still) 'auto', replace any 'auto' on 'margin-left' or 'margin-right' with '0'. 
If at this point both 'margin-left' and 'margin-right' are still 'auto', solve the equation under the extra constraint that the two margins must get equal values. 

*/

		CSSContext context;
		CSSContext* pCSSContext = &context;

		//if (!m_bCSSPropertiesValid2)
		{
			m_bCSSPropertiesValid2 = true;

			CalculateComputedCSSProperty(pCSSContext, CSSProperty_width);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_min_width);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_max_width);

			CalculateComputedCSSProperty(pCSSContext, CSSProperty_left);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_right);

			CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_left_width);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_right_width);

			CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_left);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_right);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_left);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_top);
			CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_right);
		}

		CalculateComputedCSSProperty(pCSSContext, CSSProperty_height);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_top_width);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_bottom_width);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_top);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_bottom);
		CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_bottom);

		m_computedLeft = m_specifiedLeft;
		m_computedRight = m_specifiedRight;

		TRACE("m_computedLeft: %f\n", m_computedLeft);

		double* values[9];
		values[0] = &m_computedLeft;
		values[1] = &m_computedMargin[0];
		values[2] = &m_computedBorderWidth[0];
		values[3] = &m_computedPadding[0];
		values[4] = &m_computedWidth;
		values[5] = &m_computedPadding[2];
		values[6] = &m_computedBorderWidth[2];
		values[7] = &m_computedMargin[2];
		values[8] = &m_computedRight;

/*
The constraint that determines the computed values for these elements is:

'left' + 'margin-left' + 'border-left-width' + 'padding-left' + 'width' + 'padding-right' + 'border-right-width' + 'margin-right' + 'right' = width of containing block 
*/

/* 1.
If 'left' has the value 'auto' while 'direction' is 'ltr', replace 'auto' with the
distance from the left edge of the containing block to the left margin edge of a
hypothetical box that would have been the first box of the element if its 'position'
property had been 'static'. (But rather than actually computing that box, user agents
are free to make a guess at its probable position.) The value is negative if the
hypothetical box is to the left of the containing block. 
*/		
	//	ASSERT(0);
#if 0
		m_computedWidth = m_specifiedWidth;	// hm..TODO %
		m_computedLeft = m_specifiedLeft;	// hm..TODO %
		m_computedRight = m_specifiedRight;	// hm..TODO %
#endif
		{
#if 0
			// Convert percentages
			for (int i = 0; i < 9; i++)
			{
				if (*values[i] < -1)
				{
					*values[i] = parentContentWidth * -(*values[i]+1) / 100;
				}
			}
#endif
		}

		if (m_specifiedRight == -1)	// ??
		{
			if (m_specifiedLeft == -1)
			{
				if (true/*ltr*/)
					m_computedLeft = m_curPosXOfLastStatic;
			}
		}

/*
2. If 'right' has the value 'auto' while 'direction' is 'rtl', replace 'auto' with the
distance from the right edge of the containing block to the right margin edge
of the same hypothetical box as above. The value is positive if the hypothetical
box is to the left of the containing block's edge. 
*/
		if (false)
		{
			ASSERT(0);
		}

		// Now, at least one of left and right are specified
/*
If 'width' is 'auto', replace any remaining 'auto' for 'left' or 'right' with '0'. 
*/
		//ASSERT(0);
#if 1
		if (m_computedWidth == -1)
		{
			if (m_computedLeft == -1)
				m_computedLeft = 0;
			else if (m_computedRight == -1)
				m_computedRight = 0;
			else
				ASSERT(0);
		}
#endif
//

	// 6. If at this point there is only one 'auto' left, solve the equation for that value. 
		int nAuto = -1;
		double totalWidth = 0;
		for (int i = 0; i < 9; i++)
		{
			if (*values[i] == -1)
			{
				ASSERT(nAuto == -1);	// Only one can be auto at this point
				nAuto = i;
			}
			else
			{
				totalWidth += *values[i];
			}
		}

		if (nAuto != -1)
		{
			*values[nAuto] = parentContentWidth - totalWidth;
		}
	// 7. If at this point the values are over-constrained, ignore the value for either 'left' (in case 'direction' is 'rtl') or 'right' (in case 'direction' is 'ltr') and solve for that value. 
		else if (totalWidth > parentContentWidth)
	//	else if (totalWidth != parentContentWidth)
		{
			m_computedRight -= totalWidth-parentContentWidth;
		}

		ASSERT(fabs((	m_computedLeft +
						m_computedMargin[0] +
						m_computedBorderWidth[0] +
						m_computedPadding[0] +
						m_computedWidth +
						m_computedPadding[2] +
						m_computedBorderWidth[2] +
						m_computedMargin[2] +
						m_computedRight) - parentContentWidth) < 0.0001);
	}

// top (TODO)
	if (m_specifiedTop == -1)
		m_computedTop = 0;
	else
		m_computedTop = m_specifiedTop;

// height
#if 0
	if (m_specifiedHeight == -1)	// auto
	{
		m_computedHeight = -1;
	}
	else
#endif
	{
#if 0
		if (m_specifiedHeight < -1)	// %
		{
			PElementBase* pParent = m_rparent;

			// For % to work, height of parent containing block must be known/specified
			if (pParent->m_computedHeight >= 0)
			{
				double pcnt = -(m_specifiedHeight+1);
				m_computedHeight = pParent->m_computedHeight*pcnt/100;

#if 0
			// hm..
				m_computedHeight -=	m_computedMargin[1] + m_computedMargin[3] +
											m_computedBorderWidth[1] + m_computedBorderWidth[3] +
											m_computedPadding[1] + m_computedPadding[3];
#endif
			}
			else	// auto
			{
				// % of auto is auto?
				m_computedHeight = -1;
			}
		}
		else	// absolute value specified
#endif
		{
			//ASSERT(0);
#if 0
			m_computedHeight = m_specifiedHeight;
#endif
		//	m_computedHeight = -1;

#if 0
		// hm..
			m_computedHeight -=	m_computedMargin[1] + m_computedMargin[3] +
										m_computedBorderWidth[1] + m_computedBorderWidth[3] +
										m_computedPadding[1] + m_computedPadding[3];
#endif
		}
	}

	if (!m_bArrangeValid || m_pBox == NULL || m_pBox->m_outerRect.Width != parentContentWidth ||
		m_pBox->m_outerRect.Height != m_computedHeight) // This may be wrong, not tested
	{
		pC->m_pCurLineBox = NULL;
		pC->m_pCurInlineBox = NULL;
		pC->m_curpos.X = 0;
		pC->m_curpos.Y = 0;
		pC->m_linepos.X = 0;
		pC->m_linepos.Y = 0;
		pC->m_maxx = 0;

		m_bArrangeValid = true;
		if (HasDistributableChildren())
		{
			DistributeBlockChildren(pC, nearestPositioned, stackingContext, parentContentWidth);
		}
		else
		{
		// Don't distribute children, just create a block box

			if (m_pBox == NULL)
			{
				m_pBox = CreateBlockBox();	// Principal box
				m_pBox->AddRef();
			}
			ASSERT(pC->m_pBlockBox == NULL);
			pC->m_pBlockBox = m_pBox;

			m_pBox->m_innerRect.Width = m_computedWidth;//parentContentWidth;
			m_pBox->m_innerRect.Height = m_computedHeight;	// ???

			m_pBox->m_outerRect = m_pBox->m_innerRect;

			/*
			if (m_computedWidth > 80000)
			{
				MessageBeep(-1);
			}
			*/

			pC->m_maxx = m_computedWidth;	// ??
		}
	}
	else
		pC->m_pBlockBox = m_pBox;

	/*
	else
	{
	//	if (m_rparent == NULL)
	//		CreateScrollBars(pC);
	}
	*/
}

#if 0
void PElementBase::GetVisibleRect(CRect& rcPos, CRect& rcClip)
{
	if (m_pBox)
	{
		LDraw::RectF innerRect = m_pBox->GetAbsInnerRect();

		if (m_scrollY)
		{
#if 0
			CComQIPtr<IUIScrollBar> scroll = m_scrollY->m_spUnknown;
			long scrollposY;
			scroll->get_pos(&scrollposY);

			rcPos.OffsetRect(0, -scrollposY);
			rcClip.OffsetRect(0, -scrollposY);
#endif
		}

		ASSERT(0);
#if 0
		rcClip.IntersectRect(&CRect(innerRect.X, innerRect.Y, innerRect.GetRight(), innerRect.GetBottom()), rcClip);
#endif
	}

	if (m_rparent)
	{
		((PElementBase*)m_rparent)->GetVisibleRect(rcPos, rcClip);
	}
}
#endif

#if 0//WIN32

// virtual
void PElementBase::PlaceControls(HWND hWndParent, CHTMFlowBlockContext* pC/*TODO: doesn't need this, since only uses m_pBox and will always be valid*/)
{
//	m_hWndParent = hWndParent;

	PNode** pos = m_rchildList.GetData();//GetHeadPosition();
	while (pos != m_rchildList.GetData() + m_rchildList.GetSize())
	{
		PElementBase* pElement = (PElementBase*)*pos++;//m_rchildList.GetNext(pos);
		if (pElement->m_type == NODE_ELEMENT)
		{
			pElement->PlaceControls(hWndParent, pC);
		}
	}
}

#endif

// virtual
void PElementBase::CalculateDimensions(CHTMCalcContext* pC)
{
	if (m_pStartTagBox)
	{
		delete m_pStartTagBox;
		m_pStartTagBox = NULL;
	}

	if (m_pEndTagBox)
	{
		delete m_pEndTagBox;
		m_pEndTagBox = NULL;
	}

	if (false)
	{
#if 0
		if (m_pWindow->m_bShowMarkup)
		{
			m_pStartTagBox = new CMarkupBox;
			m_pStartTagBox->m_start = 1;
			m_pStartTagBox->m_pElement = this;
			m_pStartTagBox->AddRef();
			m_pStartTagBox->CalculateDimensions(pC);

			m_pEndTagBox = new CMarkupBox;
			m_pEndTagBox->m_start = 0;
			m_pEndTagBox->m_pElement = this;
			m_pEndTagBox->AddRef();
			m_pEndTagBox->CalculateDimensions(pC);
		}
#endif
	}

	CalculateChildrenDimensions(pC);

#if 0
	if (m_computedDisplay == Display_table)
	{
		/*
		m_specifiedWidth = -1;

		CComQIPtr<ILDOMElement> element = m_pNode;

		BSTR b;

	// TODO, also look at CSS:width
		element->getAttribute(OLESTR("width", &b);
		if (b)
		{
			m_specifiedWidth = str2int(b, -1);
			SysFreeString(b);
		}
		*/
	}
	else if (m_computedDisplay == Display_table_row)
	{
		/*
		CComQIPtr<ILDOMElement> element = m_pNode;

		BSTR b;

		{
			element->getAttribute(OLESTR("bgcolor", &b);
			if (b)
			{
				COLORREF clr = ConvertColor(_bstr_t(b, false));
				if (clr != -1)
				{
					m_computedBackgroundColor = CRGBColor(GetRValue(clr), GetGValue(clr), GetBValue(clr));
				}
			}
		}

		m_specifiedHeight = -1;
	// TODO, also look at CSS:height
		element->getAttribute(OLESTR("height", &b);
		if (b)
		{
			m_specifiedHeight = str2int(b, -1);
			SysFreeString(b);
		}
		*/
	}
	else
#endif
		if (m_computedDisplayRole == DisplayRole_table_cell)
	{
		/*
		CComQIPtr<ILDOMElement> element = m_pNode;

		BSTR b;

		{
			element->getAttribute(OLESTR("bgcolor", &b);
			if (b)
			{
				COLORREF clr = ConvertColor(_bstr_t(b, false));
				if (clr != -1)
				{
					m_computedBackgroundColor = CRGBColor(GetRValue(clr), GetGValue(clr), GetBValue(clr));
				}
			}
		}

		m_specifiedWidth = -1;
	// TODO, also look at CSS:width
		element->getAttribute(OLESTR("width", &b);
		if (b)
		{
			m_specifiedWidth = str2int(b, -1);
			SysFreeString(b);
		}*/

		CalculateMinMaxDimensions();

		m_minContentWidth = MAX(m_minContentWidth, m_computedWidth);	// ??
		//m_maxContentWidth = max(m_minWidth, m_maxWidth);	// ??
	}
}

void PElementBase::CalculateMinMaxDimensions()
{
	// Get min width
	{
		ASSERT(m_boxList.size()==0);
		ASSERT(m_pBox == NULL);

		// ???
	//	m_pBox = NULL;
	//	m_boxList.RemoveAll();

		CHTMFlowBlockContext pC;// = new CHTMFlowBlockContext;
		DistributeWithinBlock(&pC, this/*nearestPositioned*/, this/*stackingContext*/, 0);
		ASSERT(pC.m_pBlockBox);

		m_minContentWidth = pC.m_maxx;

		//delete pC;

	//	m_pBox = NULL;
	//	m_boxList.RemoveAll();
		RemoveBoxesAndChildren();

		//delete pC->m_pBlockBox;
	}

	// Get max width
	{
		ASSERT(m_boxList.size()==0);
		ASSERT(m_pBox == NULL);

		CHTMFlowBlockContext pC;// = new CHTMFlowBlockContext;
		DistributeWithinBlock(&pC, this, this, 0x0fffffff);
		ASSERT(pC.m_pBlockBox);

		m_maxContentWidth = pC.m_maxx;

		//delete pC;

	//	m_pBox = NULL;
	//	m_boxList.RemoveAll();
		RemoveBoxesAndChildren();
	}

	ASSERT(m_maxContentWidth >= m_minContentWidth);
}

void PElementBase::CalculateChildrenDimensions(CHTMCalcContext* pC)
{
	PNode** pos = m_rchildList.GetData();
	while (pos != m_rchildList.GetData() + m_rchildList.GetSize())
	{
		PNode* pNode = *pos++;
		pNode->CalculateDimensions(pC);
	}
}

uint8 PElementBase::GetSVGPaint(Style::IDocumentStyle* documentStyle, SVGPaint* paint,/*int propertyIndex, BOOL bIncludeOverride,*/ CSVGPaint* pPaint)
{
	SVGPaintType paintType = paint->get_paintType();

	pPaint->m_type = paintType;

	pPaint->m_uri = nullptr;//sysstring();//.Empty();
	pPaint->m_iccColorProfile = nullptr;//sysstring();//.Empty();
	pPaint->m_iccColors.RemoveAll();

	if (paintType == SVG_PAINTTYPE_UNKNOWN)
	{
		// Shouldn't happen, invalid properties is that they get the initial value
		ASSERT(0);
	}
	else
	{
		switch (paintType)
		{
		case SVG_PAINTTYPE_URI:
		case SVG_PAINTTYPE_URI_NONE:
		case SVG_PAINTTYPE_URI_CURRENTCOLOR:
		case SVG_PAINTTYPE_URI_RGBCOLOR:
		case SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR:
			{
				pPaint->m_uri = paint->get_uri();
			}
			break;
		}

		switch (paintType)
		{
		case SVG_PAINTTYPE_CURRENTCOLOR:
		case SVG_PAINTTYPE_URI_CURRENTCOLOR:
			{
				pPaint->m_rgbColor[0] = (uint8)m_computedColor.GetRed();
				pPaint->m_rgbColor[1] = (uint8)m_computedColor.GetGreen();
				pPaint->m_rgbColor[2] = (uint8)m_computedColor.GetBlue();
			}
			break;

		case SVG_PAINTTYPE_RGBCOLOR:
		case SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR:
		case SVG_PAINTTYPE_URI_RGBCOLOR:
		case SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR:
			{
				RGBColor* color = paint->get_rgbColor();

	//			double red, green, blue;

				double red = color->get_red()->getFloatValue(CSS_NUMBER);
				double green = color->get_green()->getFloatValue(CSS_NUMBER);
				double blue = color->get_blue()->getFloatValue(CSS_NUMBER);

				/*
				CComPtr<ILCSSPrimitiveValue> greenv;
				color->get_green(&greenv);
				greenv->getFloatValue(CSS_NUMBER, &green);

				CComPtr<ILCSSPrimitiveValue> bluev;
				color->get_blue(&bluev);
				bluev->getFloatValue(CSS_NUMBER, &blue);
				*/

				if (red < 0) red = 0;
				else if (red > 255) red = 255;

				if (green < 0) green = 0;
				else if (green > 255) green = 255;

				if (blue < 0) blue = 0;
				else if (blue > 255) blue = 255;

				pPaint->m_rgbColor[0] = (uint8)red;
				pPaint->m_rgbColor[1] = (uint8)green;
				pPaint->m_rgbColor[2] = (uint8)blue;
			}
			break;
		}

		switch (paintType)
		{
		case SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR:
		case SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR:
			{
				ASSERT(0);
#if 0
				CComQIPtr<ILSVGICCColor> iccColor;
				paint->get_iccColor(&iccColor);

				iccColor->get_colorProfile(&pPaint->m_iccColorProfile);

				CComPtr<ILSVGNumberList> colors;
				iccColor->get_colors(&colors);

				long numberOfItems;
				colors->get_numberOfItems(&numberOfItems);

				for (int i = 0; i < numberOfItems; i++)
				{
					CComPtr<ILSVGNumber> number;
					colors->getItem(i, &number);

					double fval;
					number->get_value(&fval);

					pPaint->m_iccColors.Add(fval);
				}
#endif
			}
			break;
		}
	}

	return paintType;
}

uint8 PElementBase::GetSVGColor(Style::IDocumentStyle* documentStyle, SVGColor* color,/*int propertyIndex, /*BOOL bIncludeOverride,*/ CSVGColor* pColor)
{
	SVGColorType colorType = color->get_colorType();

	pColor->m_type = colorType;

	pColor->m_iccColorProfile = nullptr;//sysstring();
	pColor->m_iccColors.RemoveAll();

	if (colorType == SVG_COLORTYPE_UNKNOWN)
	{
		ASSERT(0);
	}
	else
	{
		switch (colorType)
		{
		case SVG_COLORTYPE_CURRENTCOLOR:
			{
				pColor->m_rgbColor[0] = (uint8)m_computedColor.GetRed();
				pColor->m_rgbColor[1] = (uint8)m_computedColor.GetGreen();
				pColor->m_rgbColor[2] = (uint8)m_computedColor.GetBlue();
			}
			break;

		case SVG_COLORTYPE_RGBCOLOR:
		case SVG_COLORTYPE_RGBCOLOR_ICCCOLOR:
			{
				RGBColor* rgbcolor = color->get_rgbColor();

				double red, green, blue;

				CSSPrimitiveValue* redv = rgbcolor->get_red();
				red = redv->getFloatValue(CSS_NUMBER);

				CSSPrimitiveValue* greenv = rgbcolor->get_green();
				green = greenv->getFloatValue(CSS_NUMBER);

				CSSPrimitiveValue* bluev = rgbcolor->get_blue();
				blue = bluev->getFloatValue(CSS_NUMBER);

				if (red < 0) red = 0;
				else if (red > 255) red = 255;

				if (green < 0) green = 0;
				else if (green > 255) green = 255;

				if (blue < 0) blue = 0;
				else if (blue > 255) blue = 255;

				pColor->m_rgbColor[0] = (uint8)red;
				pColor->m_rgbColor[1] = (uint8)green;
				pColor->m_rgbColor[2] = (uint8)blue;
			}
			break;
		}

		switch (colorType)
		{
		case SVG_COLORTYPE_RGBCOLOR_ICCCOLOR:
			{
				ASSERT(0);
#if 0
				CComQIPtr<ILSVGICCColor> iccColor;
				color->get_iccColor(&iccColor);

				iccColor->get_colorProfile(&pColor->m_iccColorProfile);

				CComPtr<ILSVGNumberList> colors;
				iccColor->get_colors(&colors);

				long numberOfItems;
				colors->get_numberOfItems(&numberOfItems);

				for (int i = 0; i < numberOfItems; i++)
				{
					CComPtr<ILSVGNumber> number;
					colors->getItem(i, &number);

					double fval;
					number->get_value(&fval);

					pColor->m_iccColors.Add(fval);
				}
#endif
			}
			break;
		}
	}
	return colorType;
}

/*
CComObject<CSSPrimitiveValue>* CreateCSSUnitValue(int propertyIndex, CSSUnitType unit, double value);
CComObject<CSSPrimitiveValue>* CreateCSSUnitStringValue(int propertyIndex, CSSUnitType unit, BSTR value);
CComObject<CSSPrimitiveValue>* CreateCSSUnitRGBValue(int propertyIndex, LDraw::Color value);
CComObject<SVGPaint>* CreateSVGPaintValue(int propertyIndex, CSVGPaint* pPaint);
CComObject<SVGColor>* CreateSVGColorValue(int propertyIndex, CSVGColor* pPaint);
*/

#if 0
CSSPrimitiveValue* CreateCSSUnitValue(int propertyIndex, CSSUnitType unit, double value)
{
	CSSPrimitiveValue* pCSSValue = new CSSPrimitiveValue;
	pCSSValue->m_propertyIndex = propertyIndex;
	pCSSValue->setFloatValue(unit, value);

	return pCSSValue;
}

CSSPrimitiveValue* CreateCSSUnitStringValue(int propertyIndex, CSSUnitType unit, BSTR value)
{
	CSSPrimitiveValue* pCSSValue = new CSSPrimitiveValue;
	pCSSValue->m_propertyIndex = propertyIndex;
	pCSSValue->setStringValue(unit, value);

	return pCSSValue;
}

CSSPrimitiveValue* CreateCSSUnitRGBValue(int propertyIndex, LDraw::Color value)
{
	CSSPrimitiveValue* pCSSValue = new CSSPrimitiveValue;
	pCSSValue->m_propertyIndex = propertyIndex;
	pCSSValue->SetRGBColor(RGB(value.GetRed(), value.GetGreen(), value.GetBlue()));
	pCSSValue->m_colorValue->m_alpha = value.GetAlpha()/255.0;

	return pCSSValue;
}

SVGPaint* CreateSVGPaintValue(int propertyIndex, CSVGPaint* pPaint)
{
	SVGPaint* pCSSValue = new SVGPaint;
//	pCSSValue->m_propertyIndex = propertyIndex;

	/*
	pCSSValue->m_paintType = (LSVGPaintType)paintType;

	pCSSValue->m_rgbColor->m_red->setFloatValue(CSS_NUMBER, clr[0]);
	pCSSValue->m_rgbColor->m_green->setFloatValue(CSS_NUMBER, clr[1]);
	pCSSValue->m_rgbColor->m_blue->setFloatValue(CSS_NUMBER, clr[2]);

	pCSSValue->m_uri = uri;

	pCSSValue->m_bCSSTextUpdated = false;
	*/

	OLECHAR rgbColor[64];
	swprintf(rgbColor, OLESTR("#%2.2X%2.2X%2.2X", pPaint->m_rgbColor[0], pPaint->m_rgbColor[1], pPaint->m_rgbColor[2]);

	OLECHAR iccColor[256] = {0};	// TODO

	pCSSValue->setPaint((LSVGPaintType)pPaint->m_type, pPaint->m_uri, rgbColor, iccColor);

	return pCSSValue;
}

SVGColor* CreateSVGColorValue(int propertyIndex, CSVGColor* pColor)
{
	SVGColor* pCSSValue = new SVGColor;

	OLECHAR rgbColor[64];
	swprintf(rgbColor, OLESTR("#%2.2X%2.2X%2.2X", pColor->m_rgbColor[0], pColor->m_rgbColor[1], pColor->m_rgbColor[2]);

	OLECHAR iccColor[256] = {0};	// TODO

	pCSSValue->setColor((LSVGColorType)pColor->m_type, rgbColor, iccColor);

	return pCSSValue;
}

#endif

ImmutableString<WCHAR> WrapOptionIdents[] =
{
	WSTR("wrap"),
	WSTR("no-wrap"),
	WSTR("soft-wrap"),
	WSTR("emergency"),
	NULL
};

ImmutableString<WCHAR> LineFeedTreatmentIdents[] =
{
	WSTR("auto"),
	WSTR("ignore"),
	WSTR("preserve"),
	WSTR("treat-as-space"),
	WSTR("treat-as-zero-width-space"),
	WSTR("ignore-if-after-linefeed"),
	NULL,
};

ImmutableString<WCHAR> FloatIdents[] =
{
	WSTR("left"),
	WSTR("right"),
	WSTR("top"),
	WSTR("bottom"),
	WSTR("inside"),
	WSTR("outside"),
	WSTR("start"),
	WSTR("end"),
	WSTR("none"),

	NULL
};

ImmutableString<WCHAR> ClearIdents[] =
{
	WSTR("none"),
	WSTR("left"),
	WSTR("right"),
	WSTR("top"),
	WSTR("bottom"),
	WSTR("inside"),
	WSTR("outside"),
	WSTR("start"),
	WSTR("end"),
	WSTR("both"),
	NULL
};

ImmutableString<WCHAR> ListStylePositionIdents[] =
{
	WSTR("inside"),
	WSTR("outside"),
	NULL,
};

ImmutableString<WCHAR> VisibilityIdents[] =
{
	WSTR("visible"),
	WSTR("collapse"),
	WSTR("hidden"),
	NULL,
};

ImmutableString<WCHAR> PointerEventsIdents[] =
{
	WSTR("visiblePainted"),
	WSTR("visibleFill"),
	WSTR("visibleStroke"),
	WSTR("visible"),
	WSTR("painted"),
	WSTR("fill"),
	WSTR("stroke"),
	WSTR("all"),
	WSTR("none"),
	NULL,
};

ImmutableString<WCHAR> FillRuleStrings[] =
{
	WSTR("nonzero"),
	WSTR("evenodd"),
	NULL,
};

ImmutableString<WCHAR> ClipRuleStrings[] =
{
	WSTR("nonzero"),
	WSTR("evenodd"),
	NULL,
};

ImmutableString<WCHAR> ColorInterpolationStrings[] =
{
	WSTR("auto"),
	WSTR("sRGB"),
	WSTR("linearRGB"),
	NULL,
};

ImmutableString<WCHAR> TextAlignStrings[] =
{
	WSTR("left"),
	WSTR("right"),
	WSTR("center"),
	WSTR("justify"),
	NULL,
};

ImmutableString<WCHAR> FontStyleStrings[] =
{
	WSTR("normal"),
	WSTR("italic"),
	WSTR("oblique"),
	NULL,
};

/*
__live_object_ptr<StringW> FontStretchIdents[] =
{
	WSTR("normal"),
	WSTR("wider"),
	WSTR("narrower"),
	WSTR("ultra-condensed"),
	WSTR("extra-condensed"),
	WSTR("condensed"),
	WSTR("semi-condensed"),
	WSTR("semi-expanded"),
	WSTR("expanded"),
	WSTR("extra-expanded"),
	WSTR("ultra-expanded"),
	NULL
};
*/

ImmutableString<WCHAR> TextAnchorStrings[] =
{
	WSTR("start"),
	WSTR("middle"),
	WSTR("end"),
	NULL,
};

extern ImmutableString<WCHAR> BorderStyleIdents[];// =
/*
{
	WSTR("none"),
	WSTR("hidden"),
	WSTR("dotted"),
	WSTR("dashed"),
	WSTR("solid"),
	WSTR("double"),
	WSTR("dot-dash"),
	WSTR("dot-dot-dash"),
	WSTR("wave"),
	WSTR("groove"),
	WSTR("ridge"),
	WSTR("inset"),
	WSTR("outset"),
	NULL
};
*/

ImmutableString<WCHAR> StrokeLineCapStrings[] =
{
	WSTR("butt"),
	WSTR("round"),
	WSTR("square"),
	NULL,
};

ImmutableString<WCHAR> StrokeLineJoinIdents[] =
{
	WSTR("miter"),
	WSTR("round"),
	WSTR("bevel"),
	NULL,
};

ImmutableString<WCHAR> CursorIdents[] =
{
	WSTR("auto"),
	WSTR("crosshair"),
	WSTR("default"),
	WSTR("pointer"),
	WSTR("move"),
	WSTR("e-resize"),
	WSTR("ne-resize"),
	WSTR("nw-resize"),
	WSTR("n-resize"),
	WSTR("se-resize"),
	WSTR("sw-resize"),
	WSTR("s-resize"),
	WSTR("w-resize"),
	WSTR("text"),
	WSTR("wait"),
	WSTR("help"),
	WSTR("progress"),
	WSTR("copy"),
	WSTR("alias"),
	WSTR("context-menu"),
	WSTR("cell"),
	WSTR("all-scroll"),
	WSTR("col-resize"),
	WSTR("row-resize"),
	WSTR("no-drop"),
	WSTR("not-allowed"),
	WSTR("vertical-text"),
	NULL
};

ImmutableString<WCHAR> ShapeRenderingIdents[] =
{
	WSTR("auto"),
	WSTR("optimizeSpeed"),
	WSTR("crispEdges"),
	WSTR("geometricPrecision"),
	NULL
};

ImmutableString<WCHAR> ImageRenderingIdents[] =
{
	WSTR("auto"),
	WSTR("optimizeSpeed"),
	WSTR("optimizeQuality"),
	NULL
};

/*
__live_object_ptr<StringW> BorderCollapseIdents[] =
{
	WSTR("collapse"),
	WSTR("separate"),
	NULL,
};
*/

/*
__live_object_ptr<StringW> EmptyCellsIdents[] =
{
	WSTR("show"),
	WSTR("hide"),
	NULL,
};
*/

ImmutableString<WCHAR> BoxOrientIdents[] =
{
	WSTR("horizontal"),
	WSTR("vertical"),
	WSTR("inline-axis"),
	WSTR("block-axis"),
	NULL,
};

ImmutableString<WCHAR> BoxAlignIdents[] =
{
	WSTR("start"),
	WSTR("end"),
	WSTR("center"),
	WSTR("baseline"),
	WSTR("stretch"),
	NULL,
};

ImmutableString<WCHAR> ListStyleTypeIdents[] =
{
	WSTR("normal"),
	WSTR("none"),

// glyph
	WSTR("box"),
	WSTR("check"),
	WSTR("circle"),
	WSTR("diamond"),
	WSTR("disc"),
	WSTR("hyphen"),
	WSTR("square"),

// algorithmic
	WSTR("armenian"),
	WSTR("cjk-ideographic"),
	WSTR("ethiopic-numeric"),
	WSTR("georgian"),
	WSTR("hebrew"),
	WSTR("japanese-formal"),
	WSTR("japanese-informal"),
	WSTR("lower-armenian"),
	WSTR("lower-roman"),
	WSTR("simp-chinese-formal"),
	WSTR("simp-chinese-informal"),
	WSTR("syriac"),
	WSTR("tamil"),
	WSTR("trad-chinese-formal"),
	WSTR("trad-chinese-informal"),
	WSTR("upper-armenian"),
	WSTR("upper-roman"),

// numeric
	WSTR("arabic-indic"),
	WSTR("binary"),
	WSTR("bengali"),
	WSTR("cambodian"),
	WSTR("decimal"),
	WSTR("decimal-leading-zero"),
	WSTR("devanagari"),
	WSTR("gujarati"),
	WSTR("gurmukhi"),
	WSTR("kannada"),
	WSTR("khmer"),
	WSTR("lao"),
	WSTR("lower-hexadecimal"),
	WSTR("malayalam"),
	WSTR("mongolian"),
	WSTR("myanmar"),
	WSTR("octal"),
	WSTR("oriya"),
	WSTR("persian"),
	WSTR("telugu"),
	WSTR("tibetan"),
	WSTR("thai"),
	WSTR("upper-hexadecimal"),
	WSTR("urdu"),

// alphabetic
	WSTR("afar"),
	WSTR("amharic"),
	WSTR("amharic-abegede"),
	WSTR("cjk-earthly-branch"),
	WSTR("cjk-heavenly-stem"),
	WSTR("ethiopic"),
	WSTR("ethiopic-abegede"),
	WSTR("ethiopic-abegede-am-et"),
	WSTR("ethiopic-abegede-gez"),
	WSTR("ethiopic-abegede-ti-er"),
	WSTR("ethiopic-abegede-ti-et"),
	WSTR("ethiopic-halehame-aa-er"),
	WSTR("ethiopic-halehame-aa-et"),
	WSTR("ethiopic-halehame-am-et"),
	WSTR("ethiopic-halehame-gez"),
	WSTR("ethiopic-halehame-om-et"),
	WSTR("ethiopic-halehame-sid-et"),
	WSTR("ethiopic-halehame-so-et"),
	WSTR("ethiopic-halehame-ti-er"),
	WSTR("ethiopic-halehame-ti-et"),
	WSTR("ethiopic-halehame-tig"),
	WSTR("hangul"),
	WSTR("hangul-consonant"),
	WSTR("hiragana"),
	WSTR("hiragana-iroha"),
	WSTR("katakana"),
	WSTR("katakana-iroha"),
	WSTR("lower-alpha"),
	WSTR("lower-greek"),
	WSTR("lower-norwegian"),
	WSTR("lower-latin"),
	WSTR("oromo"),
	WSTR("sidama"),
	WSTR("somali"),
	WSTR("tigre"),
	WSTR("tigrinya-er"),
	WSTR("tigrinya-er-abegede"),
	WSTR("tigrinya-et"),
	WSTR("tigrinya-et-abegede"),
	WSTR("upper-alpha"),
	WSTR("upper-greek"),
	WSTR("upper-norwegian"),
	WSTR("upper-latin"),

// symbolic
	WSTR("asterisks"),
	WSTR("footnotes"),

	NULL
};

WEBEXT int IdentNameToIndex(StringIn ident, ImmutableString<WCHAR> idents[])
{
	int i = 0;
	while (String(&idents[i]) != "")
	{
		if (!ident.CompareNoCase(&idents[i]))
		{
			return i;
		}

		i++;
	}

	return -1;
}

WEBEXT int IdentNameToIndex(StringIn ident, ImmutableString<WCHAR> idents[], unsigned int count)
{
	unsigned int i = 0;
	while (i < count)
	{
		if (ident.CompareNoCase(&idents[i]))
		{
			return i;
		}

		i++;
	}

	return -1;
}

uint8 GetBorderStyle(CSSPrimitiveValue* cssprimitiveValue)
{
	String ident = cssprimitiveValue->getStringValue();

	return IdentNameToIndex(ident, BorderStyleIdents);
}

void PElementBase::GetCSSPropertiesAndChildren()
{
	CSSContext context;
	GetCSSPropertiesAndChildren(&context);
}

//bool bInSelection = false;

void PElementBase::GetCSSPropertiesAndChildren(CSSContext* pContext)
{
	GetCSSProperties(pContext);

//	if (!m_bArrangeValid)
	if (true)
	{
		for (int i = 0; i < m_rchildList.GetSize(); i++)
		{
			//m_rchildList[i]->m_pNode->Release();
		}
		m_rchildList.RemoveAll();

		/*
		for (int i = 0; i < m_selectionPseudoElements.size(); i++)
		{
			m_pseudoElements[PseudoElementIndex_Selection]->m_rparent = NULL;
			delete m_pseudoElements[PseudoElementIndex_Selection]->m_pNode;
		}
		m_selectionPseudoElements.clear();
		*/

		PNode** pos = m_childList.begin();
		while (pos != m_childList.end())
		{
			PNode* pNode = *pos++;

			ASSERT(pNode->m_parent == this);

			if (pNode->m_type == NODE_ELEMENT)
			{
				PElementBase* pElement = static_cast<PElementBase*>(pNode);

				//pElement->m_pNode->AddRef();
				m_rchildList.Add(pElement);

				ASSERT(pElement->m_pseudoElementName == nullptr);//->Length() == 0);
				pElement->m_pWindow = m_pWindow;	// TODO, not here
				pElement->GetCSSPropertiesAndChildren(pContext);
			}
			else if (pNode->m_type == NODE_TEXT)
			{
				PText* pText = static_cast<PText*>(pNode);
				pText->m_pWindow = m_pWindow;	// TODO, not here

				if (m_pseudoElementName == nullptr)//->Length() == 0)
				{
					Range* pRange = pNode->m_pNode->m_ownerDocument->m_pWindow->m_range;
					if (pRange)
					{
						// If this text node is part of the selected area, wrap that in
						// a selection pseudo element

						if (pRange->get_startContainer() == pText->m_pNode)
							pContext->m_bInSelection = true;

						/*
							pRange->get_endContainer() == pText->m_pNode &&
							pRange->get_startOffset() != pRange->get_endOffset()
							)
							*/

						if (pContext->m_bInSelection)
						{
							int startOffset;
							if (pRange->get_startContainer() == pText->m_pNode)
								startOffset = pRange->get_startOffset();
							else
								startOffset = 0;

							int endOffset;
							if (pRange->get_endContainer() == pText->m_pNode)
								endOffset = pRange->get_endOffset();
							else
								endOffset = dynamic_cast<Text*>(pText->m_pNode)->get_length();

							Text* leftText = dynamic_cast<Text*>(pText->m_pNode->cloneNode(true));
							((PText*)leftText->m_pNode)->m_realNode = pText;

							Text* selectedText = leftText->splitText(startOffset);
							((PText*)selectedText->m_pNode)->m_realNode = pText;
							((PText*)selectedText->m_pNode)->m_realOffset = startOffset;

							Text* rightText = selectedText->splitText(endOffset - startOffset);
							((PText*)rightText->m_pNode)->m_realNode = pText;
							((PText*)rightText->m_pNode)->m_realOffset = endOffset;

							PElementBase* pPseudoElement;// = m_pseudoElements[PseudoElementIndex_Selection];
							//if (pPseudoElement == NULL)
							{
								GenericElement* pPseudo = new GenericElement(nullptr/*TODO namespaceURI*/, nullptr/*TODO localName*/, m_pNode->m_nodeName);
							//	pPseudo->m_nodeName = m_pNode->m_nodeName;
								pPseudo->m_ownerDocument = m_pNode->m_ownerDocument;
								pPseudoElement = dynamic_cast<PElementBase*>(pPseudo->m_pNode);

							//	m_pseudoElements[PseudoElementIndex_Selection] = pPseudoElement;
							//	m_selectionPseudoElements.push_back(pPseudoElement);

								pPseudoElement->m_pseudoElementName = S("selection");
								pPseudoElement->m_pNode->appendChild(selectedText);
							}
							/*
							else
							{
								// Reuse it
								dynamic_cast<Text*>(pPseudoElement->m_pNode->m_firstChild)->m_data = selectedText->m_data;
								delete selectedText;
							}
							*/

						//	CPseudoElement* pPseudoElement = new CPseudoElement;
						//	pPseudoElement->m_pNode = m_pNode;// ???newText;
						//	pPseudoElement->m_parent = this;

						//	selectedText->m_pNode->m_rparent = pPseudoElement;

							leftText->m_pNode->m_rparent = this;
							m_rchildList.Add(leftText->m_pNode);

							pPseudoElement->m_rparent = this;
							m_rchildList.Add(pPseudoElement);

							rightText->m_pNode->m_rparent = this;
							m_rchildList.Add(rightText->m_pNode);

							pPseudoElement->GetCSSPropertiesAndChildren(pContext);

							((PText*)leftText->m_pNode)->CalculateBoundsAndChildren();
							pPseudoElement->CalculateBoundsAndChildren();
							((PText*)rightText->m_pNode)->CalculateBoundsAndChildren();
						}
						else
						{
							/*
							if (m_pseudoElements[PseudoElementIndex_Selection] != NULL)
							{
								m_pseudoElements[PseudoElementIndex_Selection]->m_rparent = NULL;
								MessageBeep(-1);
							//	delete m_pseudoElements[PseudoElementIndex_Selection]->m_pNode;
								m_pseudoElements[PseudoElementIndex_Selection] = NULL;
							}
							*/
						//	pText->m_pNode->AddRef();
							m_rchildList.Add(pText);
						}

						if (pRange->get_endContainer() == pText->m_pNode)
							pContext->m_bInSelection = false;
					}
					else
					{
					//	pText->m_pNode->AddRef();
						m_rchildList.Add(pText);
					}
				}
				else
				{
				//	pText->m_pNode->AddRef();
					m_rchildList.Add(pText);
				}
			}
		}
	}

	// Remove counters that the children have created
#if 0
	{
		std::vector<PNode*>::iterator pos = m_childList.begin();
		while (pos != m_childList.end())
		{
			PElementBase* pElement = (PElementBase*)*pos++;
			if (pElement->m_type == NODE_ELEMENT)
			{
				ASSERT(0);
				for (int i = 0; i < pElement->m_counters.size(); i++)
				{
					pElement->m_counters[i]->m_value.pop_back();
					//pContext->RemoveCounter(pElement->m_counters[i]);
				}

				pElement->m_counters.clear();
			}
		}
	}
#endif
	BuildRenderableChildren();
}

//virtual
void PElementBase::SetValuesFromAttributes()
{
	TRACE("TODO SetValuesFromAttributes()\n");

#if 0
	std::vector<PNode*>::iterator pos = m_childList.begin();
	while (pos != m_childList.end())
	{
		PElementBase* pElement = (PElementBase*)*pos++;
		if (pElement->m_type == NODE_ELEMENT)
		{
			pElement->SetValuesFromAttributes();
		}
	}
#endif
}

#define THICKNESS_THIN		1
#define THICKNESS_MEDIUM	3
#define THICKNESS_THICK		5

double PElementBase::GetBorderWidth(CSSPrimitiveValue* cssprimitiveValue)
{
	CSSUnitType unitType = cssprimitiveValue->get_primitiveType();

	if (unitType == CSS_IDENT)
	{
		String ident = cssprimitiveValue->getStringValue();

		if (!ident.CompareNoCase(L"thin"))
			return THICKNESS_THIN;
		else if (!ident.CompareNoCase(L"medium"))
			return THICKNESS_MEDIUM;
		else if (!ident.CompareNoCase(L"thick"))
			return THICKNESS_THICK;
		else
			return 0;
	}
	else
	{
		return ConvertCSSLength(cssprimitiveValue);
	}
}

double PElementBase::ConvertCSSLength(CSSPrimitiveValue* cssprimitiveValue)
{
	CSSUnitType unitType = cssprimitiveValue->get_primitiveType();

	// TODO, don't have this in ConvertCSSLength, but have a ConvertCSSLengthOrAuto()
	if (unitType == CSS_IDENT)
	{
		return -1;
	}
	else if (unitType == CSS_EMS)
	{
		double em = cssprimitiveValue->getFloatValue(CSS_EMS);
		return m_computedFontSize * em;
	}
	/*
	else if (unitType == CSS_EMX)
	{
		double ex;
		cssprimitiveValue->getFloatValue(CSS_EMX, &ex);

		return m_computedFontSize * ex * 2;	// Was it like this, or was is divide
	}
	*/
	else
	{
		return cssprimitiveValue->getFloatValue(CSS_PX);
	}
}

#if 0
#include "LCSSStyleRule.h"
#endif

CRGBColor PElementBase::GetComputedColorValue(CSSPrimitiveValue* cssvalue)
{
	String cssText = cssvalue->get_cssText();

	if (cssText.CompareNoCase(L"transparent") == 0)
	{
		return CRGBColor(0, 0, 0, 0);
	}
	else if (cssText.CompareNoCase(L"currentColor") == 0)
	{
		// This requires that the color property have been previously calculated
		return m_computedColor;
	}
	else
	{
		return CRGBColor(cssvalue);
	}
}

FontDef* PElementBase::GetFont()
{
	if (m_computedFont.GetSize() > 0)
	{
		return m_computedFont[0];
	}

	uint16 style = 0;
	if (m_computedFontWeight >= 600) style |= 1;
	if (m_computedFontStyle != 0) style |= 2;

	if (m_rparent)
	{
		ASSERT(m_rparent->m_computedFontFamily.GetSize() > 0);

		if ((m_rparent->m_computedFontFamily[0] == m_computedFontFamily[0]) &&
			(m_rparent->m_computedFontWeight == m_computedFontWeight) &&
			(m_rparent->m_computedFontStyle == m_computedFontStyle) &&
			(m_rparent->m_computedFontSize == m_computedFontSize))
		{
			FontDef* pFontDef = m_rparent->GetFont();

			pFontDef->AddRef();
			m_computedFont.Add(pFontDef);
		}
	}

	if (m_computedFont.GetSize() == 0)
	{
		FontDef* pFontDef = new FontDef;
		pFontDef->AddRef();

		ASSERT(m_computedFontFamily.GetSize() > 0);

		ASSERT(0);
#if 0
		if (m_computedFontFamily[0]->m_pFamily)
			pFontDef->m_pFont = new LDraw::Font(m_computedFontFamily[0]->m_pFamily, m_computedFontSize, style);
#endif
		m_computedFont.Add(pFontDef);
	}

	return m_computedFont[0];
}

Gui::Brush* PElementBase::GetColorBrush()
{
	if (m_pColorBrush == NULL)
	{
		ASSERT(0);
#if 0
		m_pColorBrush = new Gui::SolidColorBrush(m_computedColor);
#endif
	}

	return m_pColorBrush;
}

// virtual
void PElementBase::InsertedIntoDocument()
{
	// TODO children ??
}

// virtual
void PElementBase::RemovedFromDocument()
{
	PNode::RemovedFromDocument();
	// TODO children ??
}

// virtual
void PElementBase::BuildChildren()
{
	ASSERT(0);
#if 0
	CComQIPtr<ILDOMNode> child;
	m_pNode->get_firstChild(&child);

	while (child != NULL)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);

		if (nodeType == LNODE_TEXT)
		{
			CComQIPtr<ILDOMText> text = child;

			CComObject<PText>* pItem;
			CComObject<PText>::CreateInstance(&pItem);
			pItem->AddRef();
			pItem->m_pNode = text;
			pItem->m_pView = m_pView;
			pItem->m_pWindow = m_pWindow;

			text->get_length(&pItem->m_dataLength);

			pItem->BuildWords();

			CComQIPtr<CLDOMNodeImplImpl>(child)->m_pNodes.Add(pItem);

			pItem->m_parent = this;
			m_childList.AddTail(pItem);
		}
		else if (nodeType == LNODE_ENTITY_REFERENCE)
		{
			// TODO
			ASSERT(0);
		}
		else if (nodeType == NODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement> element = child;

			PElementBase* pElement2 = m_pView->CreateElement(element);
			if (pElement2)
			{
				CComQIPtr<CLDOMNodeImplImpl>(element)->m_pNodes.Add(pElement2);

				pElement2->BuildChildren();

				pElement2->m_parent = this;
				m_childList.AddTail(pElement2);
			}
		}

		CComQIPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
#endif
}

void PElementBase::AddChildren(PElementBase* pElement)
{
// The m_rchildList of pElement must already have been built
	PNode** pos = pElement->m_rchildList.begin();
	while (pos != pElement->m_rchildList.end())
	{
		PNode* pNode = *pos++;

		if (pNode->m_type == NODE_ELEMENT)
		{
			PElementBase* pElement = (PElementBase*)pNode;
			if (pElement->m_shadowTree)
			{
				AddChildren(pElement->m_shadowTree);
				continue;
			}
		}

		ASSERT(0);
#if 0
		ASSERT(m_rchildList.Find(pNode) == NULL);
#endif
		m_rchildList.Add(pNode);
		pNode->m_rparent = this;
	}
}

void PElementBase::BuildShadowTree(PElementBase* refElement)
{
	ASSERT(0);
#if 0
	m_rchildList.RemoveAll();

	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		PNode* pNode = (PNode*)m_childList.GetNext(pos);

		if (pNode->m_type == NODE_ELEMENT)
		{
			PElementBase* pChildElement = (PElementBase*)pNode;

			CComBSTR tagName;
			pChildElement->m_pNode->get_nodeName(&tagName);
			if (!tcscmp(tagName, OLESTR("refContent"))
			{
				CComQIPtr<ILDOMElement> refContent(pChildElement->m_pNode);

				CComBSTR select;
				refContent->getAttribute(OLESTR("select", &select);

				if (select.Length())
				{
					ASSERT(0);
					PElementBase* p = refElement->GetElementByTagNameNS(NULL, select);
					ASSERT(p);
					if (p)
					{
						/*
						p->BuildRenderChildren();
						if (p->m_shadowTree)
						{
							ASSERT(m_rchildList.Find(p->m_shadowTree) == NULL);
							m_rchildList.AddTail(p->m_shadowTree);
							p->m_shadowTree->m_rparent = this;
						}
						else
						{
							ASSERT(m_rchildList.Find(p) == NULL);
							m_rchildList.AddTail(p);
							p->m_rparent = this;
						}
						*/
					}
				}
				else
				{
					UPOSITION pos = refElement->m_rchildList.GetHeadPosition();
					while (pos)
					{
						PNode* pNode = (PNode*)refElement->m_rchildList.GetNext(pos);

						if (pNode->m_type == NODE_ELEMENT)
						{
							PElementBase* pElement = (PElementBase*)pNode;

							if (pElement->m_shadowTree)
							{
								AddChildren(pElement);
								continue;
							}
						}

						ASSERT(m_rchildList.Find(pNode) == NULL);
						m_rchildList.AddTail(pNode);
						pNode->m_rparent = this;
					}
				}
			}
			else
			{
				pChildElement->BuildShadowTree(refElement);

				ASSERT(m_rchildList.Find(pChildElement) == NULL);
				m_rchildList.AddTail(pChildElement);
				pChildElement->m_rparent = this;
			}
		}
		else
		{
			m_rchildList.AddTail(pNode);
			pNode->m_rparent = this;
		}
	}
#endif
}

// virtual
void PElementBase::BuildRenderChildren()
{
	// hm.. removed this function ??
}

void PElementBase::BuildRenderChildrenInternal()
{
	ASSERT(0);

#if 0
#if 0
	if (m_pBeforePseudoElement)
	{
		m_rchildList.AddHead(m_pBeforePseudoElement);	// Do it like this ??
	}

	if (m_bindNode)
	{
		if (m_pBindNode == NULL)	// TODO remove
		{
			CComObject<CPPElement>::CreateInstance(&m_pBindNode);
			m_pBindNode->AddRef();
			m_pBindNode->m_pNode = m_bindNode;
			m_pBindNode->m_parent = this;
			m_pBindNode->m_pView = m_pView;

			m_pBindNode->BuildChildren();
			m_pBindNode->BuildRenderChildren();

			m_pBindNode->GetCSSPropertiesAndChildren();
		}

		AddChildren(m_pBindNode);
	}
	else
#endif
	{
		std::vector<PNode*>::iterator pos = m_childList.begin();
		while (pos != m_childList.end())
		{
			PNode* pNode = *pos++;//(PNode*)m_childList.GetNext(pos);

			if (pNode->m_type == NODE_ELEMENT)
			{
				PElementBase* pElement = (PElementBase*)pNode;

				pElement->BuildRenderChildren();	// Recurse

				if (pElement->m_shadowTree)
				{
					AddChildren(pElement->m_shadowTree);

					continue;
				}
			}

			// No special treatment
			ASSERT(0);
#if 0
			ASSERT(m_rchildList.Find(pNode) == NULL);
#endif
			m_rchildList.push_back(pNode);
			pNode->m_rparent = this;
		}
	}

#if 0
	// Do this here?
	CComQIPtr<CLSVGShadowableImpl> shadowable = m_pNode;
	if (shadowable && shadowable->m_shadowElement)
	{
		if (m_shadowTree == NULL)
		{
			if (m_shadowTree)
			{
				m_shadowTree->Release();
				m_shadowTree = NULL;
			}

			ASSERT(m_shadowTree == NULL);

			CComObject<CPPElement>::CreateInstance(&m_shadowTree);
			m_shadowTree->AddRef();
			m_shadowTree->m_pView = m_pView;
			m_shadowTree->m_pNode = shadowable->m_shadowElement;

			ASSERT(CComQIPtr<CLDOMNodeImplImpl>(m_shadowTree->m_pNode)->CheckNodeOnFrame(m_pView) == NULL);
			CComQIPtr<CLDOMNodeImplImpl>(m_shadowTree->m_pNode)->m_pNodes.Add(m_shadowTree);

			m_shadowTree->m_parent = this;
			m_shadowTree->BuildChildren();

			m_shadowTree->BuildShadowTree(this/*refElement*/);

			{
				ASSERT(0);
#if 0
			// All this isn't really tested out
				m_shadowTree->GetCSSProperties();
#endif

			// Copy the css properties from the custom element to the shadow tree element?
				m_shadowTree->m_computedBackgroundColor = m_computedBackgroundColor;
				m_shadowTree->m_computedDisplayModel = m_computedDisplayModel;
				m_shadowTree->m_computedDisplayRole = m_computedDisplayRole;

				UPOSITION pos = m_shadowTree->m_childList.GetHeadPosition();
				while (pos)
				{
					PElementBase* pElement = (PElementBase*)m_shadowTree->m_childList.GetNext(pos);
					if (pElement->m_type == NODE_ELEMENT)
					{
						pElement->GetCSSPropertiesAndChildren();
					}
				}

			//	m_shadowTree->BuildRenderChildren();
			//	m_shadowTree->CalculateBoundsAndChildren();
				// What about recalculateparentbounds?
			}
		}
	}
#endif
	// Moved this after also getting any pseudo elements
// 	BuildRenderableChildren();	// SVG only ??
#endif
}

#if 0
HRESULT BindExtension(ILDOMElement* componentElement /*elementDef*/, CLSVGShadowableImpl* shadowable)
{
	CComPtr<ILDOMDocument> document;
	componentElement->get_ownerDocument(&document);

	CComPtr<ILDOMDocument> customElementDocument = CComQIPtr<CLDOMNodeImplImpl>(shadowable)->m_ownerDocument;

	CComQIPtr<ILDOMDocumentEvent> documentEvent = customElementDocument;
	ASSERT(documentEvent);

	CScriptSite* pScriptSite = CComQIPtr<CLDOMDocumentImplImpl>(document.p)->m_pScriptSite;
	CComQIPtr<IActiveScriptParseProcedure> activeScriptParseProcedure = pScriptSite->m_activeScript;

#if 0
	ASSERT(shadowable->m_shadowElement == NULL);
#endif

	CComObject<CLSVGShadowElement>::CreateInstance(&shadowable->m_shadowElement);
	shadowable->m_shadowElement->AddRef();
//	shadowable->m_shadowElement->m_ownerDocument = customElementDocument;
	shadowable->m_shadowElement->m_ownerDocument = document;

	CComPtr<ILDOMNode> node;
	componentElement->get_firstChild(&node);

	while (node)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			CComBSTR namespaceURI;
			element->get_namespaceURI(&namespaceURI);

			CComBSTR tagName;
			element->get_localName(&tagName);
			if (tagName.Length() == 0)
			{
				tagName.Empty();	// in case of "" instead of NULL
				element->get_tagName(&tagName);
			}

			if (!tcscmp(tagName, OLESTR("prototype"))
			{
			// Only the first should be used???prototype is used (should I return an error?)
				//if (bAlready)
				{
					// copy the contents of this element to the shadow tree

					// Fire SVGBindBegin on custom element
					{
						CComPtr<ILDOMEvent> evt;
						documentEvent->createEvent(OLESTR(""/*generic event*/, &evt);
						evt->initEvent(OLESTR("SVGBindBegin", VARIANT_FALSE/*??bubble*/, VARIANT_FALSE/*??cancelable*/);

						CComQIPtr<ILDOMEventTarget> eventTarget = shadowable;
						ASSERT(eventTarget);

						bool bDoDefault;
						eventTarget->dispatchEvent(evt, &bDoDefault);
					}

					//CopyChildren(CComQIPtr<ILDOMElement>(m_pNode), element, shadowable->m_shadowElement);

					CComPtr<ILDOMNode> node;
					element->get_firstChild(&node);
					while (node)
					{
						CComPtr<ILDOMNode> clone;
					//	node->cloneNode(VARIANT_TRUE, &clone);

					// TODO customElementDocument->importNode.. ?? The shadow elements are owned by the document that the custom element is on

						//customElementDocument->importNode(node, VARIANT_TRUE, &clone);
						document->importNode(node, VARIANT_TRUE, &clone);
						shadowable->m_shadowElement->appendChild(clone, NULL);

						CComPtr<ILDOMNode> nextSibling;
						node->get_nextSibling(&nextSibling);
						node = nextSibling;
					}

					// Fire SVGBindEnd on custom element
					{
						CComPtr<ILDOMEvent> evt;
						documentEvent->createEvent(OLESTR(""/*generic event*/, &evt);
						evt->initEvent(OLESTR("SVGBindEnd", VARIANT_FALSE/*??bubble*/, VARIANT_FALSE/*??cancelable*/);

						CComQIPtr<ILDOMEventTarget> eventTarget = shadowable;
						ASSERT(eventTarget);

						bool bDoDefault;
						eventTarget->dispatchEvent(evt, &bDoDefault);
					}
				}
			}
			else if (!cmpbstr(namespaceURI, OLESTR("urn:HTMLComponent") && !tcscmp(tagName, OLESTR("ATTACH"))
			{
				CComBSTR event;
				element->getAttribute(OLESTR("EVENT", &event);

				CComBSTR onevent;
				element->getAttribute(OLESTR("ONEVENT", &onevent);

				{

				//	CComBSTR code;
				//	attr->get_value(&code);

					CComPtr<IDispatch> disp;

#if 0
					if (pScriptSite->m_debugDocumentHelper)
					{
						long charOffset = 0;	// TODO

						DWORD dwSourceContext;
						HRESULT hr = pScriptSite->m_debugDocumentHelper->DefineScriptBlock(charOffset, code.Length(), pScriptSite->m_activeScript, FALSE/*fScriptlet*/, &dwSourceContext);
				#if 0
						CComQIPtr<CLDOMElementImplImpl>(element)->m_dwScriptCookie = dwSourceContext;
				#endif
					}
#endif

					HRESULT hr = activeScriptParseProcedure->ParseProcedureText(
						onevent,	// code
						OLESTR("evt",//OLESTR("",	// formal params
						OLESTR("anonymous",	// procedure name
						NULL,	// item name
						NULL,	// punkContext
						NULL,	// delimiter
						0,	// dwSourceContextCookie
						0,	// start line number
						SCRIPTPROC_IMPLICIT_THIS,//SCRIPTTEXT_ISVISIBLE,// | SCRIPTTEXT_ISPERSISTENT,	// flags
						&disp);

					ASSERT(SUCCEEDED(hr));

					if (SUCCEEDED(hr))
					{
						CComObject<CEventListener>* pListener;
						CComObject<CEventListener>::CreateInstance(&pListener);
						pListener->AddRef();
						pListener->m_listenerElement = CComQIPtr<ILDOMElement>(shadowable);//element;
						pListener->m_handlerElement = NULL;//handlerElement;
						pListener->m_disp = disp;

						//CComQIPtr<CLDOMAttrImplImpl>(attr)->m_pEventListener = pListener;

						CComQIPtr<ILDOMEventTarget> eventTarget = CComQIPtr<ILDOMElement>(shadowable);
						if (eventTarget)
						{
							eventTarget->addEventListener(event, pListener, VARIANT_FALSE/*useCapture*/);
						}
					}
				}
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	return S_OK;
}
#endif

#if 0
HRESULT PElementBase::BindBehavior(ILDOMElement* componentElement)
{
	CComPtr<ILDOMDocument> document;
	componentElement->get_ownerDocument(&document);

	CComPtr<ILDOMDocument> customElementDocument = CComQIPtr<CLDOMNodeImplImpl>(m_pNode)->m_ownerDocument;

	CComQIPtr<ILDOMDocumentEvent> documentEvent = customElementDocument;
	ASSERT(documentEvent);

	CScriptSite* pScriptSite = CComQIPtr<CLDOMDocumentImplImpl>(document.p)->m_pScriptSite;
	CComQIPtr<IActiveScriptParseProcedure> activeScriptParseProcedure = pScriptSite->m_activeScript;

#if 0
	ASSERT(shadowable->m_shadowElement == NULL);
#endif

//	CComObject<CLDOMDocumentFragment>::CreateInstance(&m_bindNode);
	CComObject<CLDOMElement>::CreateInstance(&m_bindNode);
	m_bindNode->AddRef();
	m_bindNode->m_ownerDocument = document;

	CComPtr<ILDOMNode> node;
	componentElement->get_firstChild(&node);

	while (node)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			CComBSTR namespaceURI;
			element->get_namespaceURI(&namespaceURI);

			CComBSTR tagName;
			element->get_localName(&tagName);
			if (tagName.Length() == 0)
			{
				tagName.Empty();	// in case of "" instead of NULL
				element->get_tagName(&tagName);
			}

			if (!tcscmp(tagName, OLESTR("prototype"))
			{
				ASSERT(0);
#if 0
			// Only the first should be used???prototype is used (should I return an error?)
				//if (bAlready)
				{
					// copy the contents of this element to the shadow tree

					// Fire SVGBindBegin on custom element
					{
						CComPtr<ILDOMEvent> evt;
						documentEvent->createEvent(OLESTR(""/*generic event*/, &evt);
						evt->initEvent(OLESTR("SVGBindBegin", VARIANT_FALSE/*??bubble*/, VARIANT_FALSE/*??cancelable*/);

						CComQIPtr<ILDOMEventTarget> eventTarget = shadowable;
						ASSERT(eventTarget);

						bool bDoDefault;
						eventTarget->dispatchEvent(evt, &bDoDefault);
					}

					//CopyChildren(CComQIPtr<ILDOMElement>(m_pNode), element, shadowable->m_shadowElement);

					CComPtr<ILDOMNode> node;
					element->get_firstChild(&node);
					while (node)
					{
						CComPtr<ILDOMNode> clone;
					//	node->cloneNode(VARIANT_TRUE, &clone);

					// TODO customElementDocument->importNode.. ?? The shadow elements are owned by the document that the custom element is on

						//customElementDocument->importNode(node, VARIANT_TRUE, &clone);
						document->importNode(node, VARIANT_TRUE, &clone);
						shadowable->m_shadowElement->appendChild(clone, NULL);

						CComPtr<ILDOMNode> nextSibling;
						node->get_nextSibling(&nextSibling);
						node = nextSibling;
					}

					// Fire SVGBindEnd on custom element
					{
						CComPtr<ILDOMEvent> evt;
						documentEvent->createEvent(OLESTR(""/*generic event*/, &evt);
						evt->initEvent(OLESTR("SVGBindEnd", VARIANT_FALSE/*??bubble*/, VARIANT_FALSE/*??cancelable*/);

						CComQIPtr<ILDOMEventTarget> eventTarget = shadowable;
						ASSERT(eventTarget);

						bool bDoDefault;
						eventTarget->dispatchEvent(evt, &bDoDefault);
					}
				}
#endif
			}
			else if (!tcscmp(tagName, OLESTR("content"))
			{
					// Fire SVGBindBegin on custom element
					{
						CComPtr<ILDOMUIEvent> evt;
						documentEvent->createEvent(OLESTR("UIEvents", (ILDOMEvent**)&evt);
						evt->initUIEvent(OLESTR("SVGBindBegin", VARIANT_FALSE/*??bubble*/, VARIANT_FALSE/*??cancelable*/, m_pWindow, 0);

						CComQIPtr<ILDOMEventTarget> eventTarget = m_pNode;
						ASSERT(eventTarget);

						bool bDoDefault;
						eventTarget->dispatchEvent(evt, &bDoDefault);
					}

					//CopyChildren(CComQIPtr<ILDOMElement>(m_pNode), element, shadowable->m_shadowElement);

					CComPtr<ILDOMNode> node;
					element->get_firstChild(&node);
					while (node)
					{
						CComPtr<ILDOMNode> clone;
					//	node->cloneNode(VARIANT_TRUE, &clone);

					// TODO customElementDocument->importNode.. ?? The shadow elements are owned by the document that the custom element is on

						//customElementDocument->importNode(node, VARIANT_TRUE, &clone);
						document->importNode(node, VARIANT_TRUE, &clone);
						m_bindNode->appendChild(clone, NULL);

						CComPtr<ILDOMNode> nextSibling;
						node->get_nextSibling(&nextSibling);
						node = nextSibling;
					}

					// Fire SVGBindEnd on custom element
					{
						CComPtr<ILDOMUIEvent> evt;
						documentEvent->createEvent(OLESTR("UIEvents", (ILDOMEvent**)&evt);
						evt->initUIEvent(OLESTR("SVGBindEnd", VARIANT_FALSE/*??bubble*/, VARIANT_FALSE/*??cancelable*/, m_pWindow, 0);

						CComQIPtr<ILDOMEventTarget> eventTarget = m_pNode;
						ASSERT(eventTarget);

						bool bDoDefault;
						eventTarget->dispatchEvent(evt, &bDoDefault);
					}
			}
			else if (!cmpbstr(namespaceURI, OLESTR("urn:HTMLComponent") && !tcscmp(tagName, OLESTR("ATTACH"))
			{
				CComBSTR event;
				element->getAttribute(OLESTR("EVENT", &event);

				CComBSTR onevent;
				element->getAttribute(OLESTR("ONEVENT", &onevent);

				{

				//	CComBSTR code;
				//	attr->get_value(&code);

					CComPtr<IDispatch> disp;

#if 0
					if (pScriptSite->m_debugDocumentHelper)
					{
						long charOffset = 0;	// TODO

						DWORD dwSourceContext;
						HRESULT hr = pScriptSite->m_debugDocumentHelper->DefineScriptBlock(charOffset, code.Length(), pScriptSite->m_activeScript, FALSE/*fScriptlet*/, &dwSourceContext);
				#if 0
						CComQIPtr<CLDOMElementImplImpl>(element)->m_dwScriptCookie = dwSourceContext;
				#endif
					}
#endif

					HRESULT hr = activeScriptParseProcedure->ParseProcedureText(
						onevent,	// code
						OLESTR("evt",//OLESTR("",	// formal params
						OLESTR("anonymous",	// procedure name
						NULL,	// item name
						NULL,	// punkContext
						NULL,	// delimiter
						0,	// dwSourceContextCookie
						0,	// start line number
						SCRIPTPROC_IMPLICIT_THIS,//SCRIPTTEXT_ISVISIBLE,// | SCRIPTTEXT_ISPERSISTENT,	// flags
						&disp);

					ASSERT(SUCCEEDED(hr));

					if (SUCCEEDED(hr))
					{
						CComObject<CEventListener>* pListener;
						CComObject<CEventListener>::CreateInstance(&pListener);
						pListener->AddRef();
						pListener->m_listenerElement = CComQIPtr<ILDOMElement>(m_pNode);//element;
						pListener->m_handlerElement = NULL;//handlerElement;
						pListener->m_disp = disp;

						//CComQIPtr<CLDOMAttrImplImpl>(attr)->m_pEventListener = pListener;

						CComQIPtr<ILDOMEventTarget> eventTarget = CComQIPtr<ILDOMElement>(m_pNode);
						if (eventTarget)
						{
							eventTarget->addEventListener(event, pListener, VARIANT_FALSE/*useCapture*/);
						}
					}
				}
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	return S_OK;
}
#endif

IDWriteFontCollection* pFontCollection = NULL;

void PElementBase::CalculateComputedCSSPropertyCore(CSSContext* pCSSContext, int propertyIndex, bool bIncludeOverride)
{
	Style::IDocumentStyle* documentStyle = dynamic_cast<Style::IDocumentStyle*>(m_pNode->m_ownerDocument);
	ASSERT(documentStyle);

//	ViewCSS* m_pWindow = dynamic_cast<ViewCSS*>(dynamic_cast<DocumentView*>(m_pNode->m_ownerDocument)->get_defaultView());
//	ASSERT(m_pWindow);

	CSSValue* cssValue;
	CSSPrimitiveValue* cssprimitiveValue;

	CSSProperty* pProperty = CSSProperties::csspropertyList[propertyIndex];

	switch (propertyIndex)
	{
#if 0
		/*
	case CSSProperty_display:	// TODO remove
		{
			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_display, bIncludeOverride);
			CComBSTR cssText;
			cssprimitiveValue->getStringValue(&cssText);

			m_computedDisplay = IdentNameToIndex(cssText, DisplayStrings);
		}
		break;
		*/
#endif

	case CSSProperty_display_model:
		{
		//	cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, propertyIndex, bIncludeOverride);

			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);

			if (value == Style::Value_Specified)
			{
				String cssText = cssprimitiveValue->getStringValue();
				m_computedDisplayModel = IdentNameToIndex(cssText, DisplayModelIdents);
			}
			else if (value == 1)
			{
				m_computedDisplayModel = m_rparent->m_computedDisplayModel;
			}
			else
			{
				m_computedDisplayModel = DisplayModel_inline_inside;	// ??
			}
		}
		break;

	case CSSProperty_display_role:
		{
			//cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, propertyIndex, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);

			if (value == Style::Value_Specified)
			{
				String cssText = cssprimitiveValue->getStringValue();
				m_computedDisplayRole = IdentNameToIndex(cssText, DisplayRoleIdents);
			}
			else if (value == 1)
			{
				m_computedDisplayRole = m_rparent->m_computedDisplayRole;
			}
			else
			{
				m_computedDisplayRole = DisplayRole_inline;
			}

			/*
			if (m_computedDisplayRole == DisplayRole_inline)
			{
				TRACE("");
			}
			*/
		}
		break;

	case CSSProperty_visibility:
		{
			//cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_visibility, bIncludeOverride);
			CSSPrimitiveValue* cssprimitiveValue;
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);

			if (value == 0)
			{
				String ident = cssprimitiveValue->getStringValue();

				m_computedVisibility = IdentNameToIndex(ident, VisibilityIdents);
			}
			else if (value == 1)	// inherit
			{
				m_computedVisibility = m_rparent->m_computedVisibility;
			}
			else// if (value == 2)	// initial
			{
				m_computedVisibility = Visibility_visible;
			}
		}
		break;
#if 0
	case CSSProperty_list_style_type:
		{
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);

			if (value == 0)
			{
				CComBSTR ident;
				cssprimitiveValue->getStringValue(&ident);

				m_computedListStyleType = IdentNameToIndex(ident, ListStyleTypeIdents);
			}
			else if (value == 1)	// inherit
			{
				m_computedListStyleType = m_rparent->m_computedListStyleType;
			}
			else// if (value == 2)	// initial
			{
				m_computedListStyleType = ListStyleType_disc;
			}
		}
		break;

	case CSSProperty_list_style_position:
		{
			//cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_visibility, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);

			if (value == 0)
			{
				CComBSTR ident;
				cssprimitiveValue->getStringValue(&ident);

				m_computedListStylePosition = IdentNameToIndex(ident, ListStylePositionIdents);
			}
			else if (value == 1)	// inherit
			{
				m_computedListStylePosition = m_rparent->m_computedListStylePosition;
			}
			else// if (value == 2)	// initial
			{
				m_computedListStylePosition = Visibility_visible;
			}
		}
		break;

	case CSSProperty_counter_increment:
		{
			m_computedCounterIncrement.clear();

			CComPtr<CSSValueList> cssvalueList;
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssvalueList);

			if (value == 0)
			{
				long length;
				cssvalueList->get_length(&length);

				for (int i = 0; i < length; i++)
				{
					CComPtr<CSSValue> cssvalue;
					cssvalueList->item(i, &cssvalue);

					LCSSValueType valuetype;
					cssvalue->get_cssValueType(&valuetype);

					if (valuetype == CSS_VALUE_LIST)
					{
						CComQIPtr<CSSValueList> cssvalueList = cssvalue;

						CComPtr<ILCSSPrimitiveValue> cssvalue2;
						cssvalueList->item(0, (CSSValue**)&cssvalue2);

						CComBSTR counterName;
						cssvalue2->getStringValue(&counterName);

						CCounterDef* pCounterDef = new CCounterDef;
						pCounterDef->m_identifier = counterName;
						pCounterDef->m_number = 1;	// Default increment

						m_computedCounterIncrement.push_back(pCounterDef);
					}
					else
					{
						CComQIPtr<ILCSSPrimitiveValue> cssvalue2 = cssvalue;

						CComBSTR counterName;
						cssvalue2->getStringValue(&counterName);

						CCounterDef* pCounterDef = new CCounterDef;
						pCounterDef->m_identifier = counterName;
						pCounterDef->m_number = 1;	// Default increment

						m_computedCounterIncrement.push_back(pCounterDef);
					}
				}
			}
			else if (value == 1)
			{
				ASSERT(0);
			}
			else
			{
			}
		}
		break;

	case CSSProperty_counter_reset:
		{
			m_computedCounterReset.clear();

			CComPtr<CSSValueList> cssvalueList;
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssvalueList);

			if (value == 0)
			{
				long length;
				cssvalueList->get_length(&length);

				for (int i = 0; i < length; i++)
				{
					CComPtr<CSSValue> cssvalue;
					cssvalueList->item(i, &cssvalue);

					LCSSValueType valuetype;
					cssvalue->get_cssValueType(&valuetype);

					if (valuetype == CSS_VALUE_LIST)
					{
						CComQIPtr<CSSValueList> cssvalueList = cssvalue;

						CComPtr<ILCSSPrimitiveValue> cssvalue2;
						cssvalueList->item(0, (CSSValue**)&cssvalue2);

						CComBSTR counterName;
						cssvalue2->getStringValue(&counterName);

						CCounterDef* pCounterDef = new CCounterDef;
						pCounterDef->m_identifier = counterName;
						pCounterDef->m_number = 0;	// Default reset

						m_computedCounterReset.push_back(pCounterDef);
					}
					else
					{
						CComQIPtr<ILCSSPrimitiveValue> cssvalue2 = cssvalue;

						CComBSTR counterName;
						cssvalue2->getStringValue(&counterName);

						CCounterDef* pCounterDef = new CCounterDef;
						pCounterDef->m_identifier = counterName;
						pCounterDef->m_number = 0;	// Default reset

						m_computedCounterReset.push_back(pCounterDef);
					}
				}
			}
			else if (value == 1)
			{
				ASSERT(0);
			}
			else
			{
			}
		}
		break;
#endif
	case CSSProperty_font_size:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);

			if (value == 0)
			{
				CSSUnitType unitType = cssprimitiveValue->get_primitiveType();

				if (unitType == CSS_PERCENTAGE)
				{
					double pcnt = cssprimitiveValue->getFloatValue(CSS_PERCENTAGE);
					m_computedFontSize = m_rparent->m_computedFontSize*pcnt/100;
				}
				else if (unitType == CSS_EMS)
				{
					double em = cssprimitiveValue->getFloatValue(CSS_EMS);

					m_computedFontSize = m_rparent->m_computedFontSize*em;
					//m_parent->m_computedFontFamily[0]->GetHFONT();
					//m_computedFontSize = m_parent->m_computedFontFamily[0]->m_tm.tmHeight * em;
				}
				else
					m_computedFontSize = cssprimitiveValue->getFloatValue(CSS_NUMBER);
			}
			else if (value == 1)	// inherit
			{
				m_computedFontSize = m_rparent->m_computedFontSize;
			}
			else// if (value == 2)	// initial
			{
				m_computedFontSize = 14;	// TODO 12pt
			}
		}
		break;

	// font-style
	case CSSProperty_font_style:
		{
			//cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_font_style, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				String cssText = cssprimitiveValue->getStringValue();

				ASSERT(0);
#if 0
				if (!std::wcscmp(cssText->c_str(), L"italic"))			m_computedFontStyle = FontStyle_italic;
				else if (!std::wcscmp(cssText->c_str(), L"oblique"))	m_computedFontStyle = FontStyle_oblique;
				else /*if (!tcscmp(cssText.c_str(), OLESTR("normaOLESTR("))*/	m_computedFontStyle = FontStyle_normal;
#endif
			}
			else if (value == 1)
			{
				m_computedFontStyle = m_rparent->m_computedFontStyle;
			}
			else
			{
				m_computedFontStyle = FontStyle_normal;
			}
		}
		break;

	// font-weight
	case CSSProperty_font_weight:
		{
		//	cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_font_weight, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);

			if (value == 0)
			{
				String cssText = cssprimitiveValue->getStringValue();

				ASSERT(0);
#if 0

				if (!std::wcscmp(cssText->c_str(), L"100"))				m_computedFontWeight = 100;
				else if (!std::wcscmp(cssText->c_str(), L"200"))		m_computedFontWeight = 200;
				else if (!std::wcscmp(cssText->c_str(), L"300"))		m_computedFontWeight = 300;
				else if (!std::wcscmp(cssText->c_str(), L"400"))		m_computedFontWeight = 400;
				else if (!std::wcscmp(cssText->c_str(), L"500"))		m_computedFontWeight = 500;
				else if (!std::wcscmp(cssText->c_str(), L"600"))		m_computedFontWeight = 600;
				else if (!std::wcscmp(cssText->c_str(), L"700"))		m_computedFontWeight = 700;
				else if (!std::wcscmp(cssText->c_str(), L"800"))		m_computedFontWeight = 800;
				else if (!std::wcscmp(cssText->c_str(), L"900"))		m_computedFontWeight = 900;

				else if (!std::wcscmp(cssText->c_str(), L"normal"))	m_computedFontWeight = 400;
				else if (!std::wcscmp(cssText->c_str(), L"bold"))
				{
					m_computedFontWeight = 700;
				}
				else if (!std::wcscmp(cssText->c_str(), L"bolder"))
				{
					if (m_rparent)
					{
						m_computedFontWeight = MAX(900, m_rparent->m_computedFontWeight+300);
					}
					else
					{
						m_computedFontWeight = 700;
					}
				}
				else if (!std::wcscmp(cssText->c_str(), L"lighter"))
				{
					if (m_rparent)
					{
						m_computedFontWeight = MIN(100, m_rparent->m_computedFontWeight-300);
					}
					else
					{
						m_computedFontWeight = 300;
					}
				}
				else
				{
					m_computedFontWeight = 400;
				}
#endif
			}
			else if (value == 1)
			{
				m_computedFontWeight = m_rparent->m_computedFontWeight;
			}
			else
			{
				m_computedFontWeight = 400;
			}
		}
		break;

	// font-family
	case CSSProperty_font_family:
		{
			if (pFontCollection == NULL)
			{
				// Get the system font collection.
				HRESULT hr = Graphics::Direct10::get_DWriteFactory()->GetSystemFontCollection(&pFontCollection);
			}

			for (int i = 0; i < m_computedFontFamily.GetSize(); ++i)
			{
				m_computedFontFamily[i]->Release();
			}
			m_computedFontFamily.RemoveAll();

#if 0
			{
				for (int i = 0; i < m_computedFontFamily.GetSize(); i++)
				{
					m_pView->ReleaseFontDef(m_computedFontFamily[i]);
				}
				m_computedFontFamily.RemoveAll();
			}
#endif

		//	CComQIPtr<CSSValueList> cssvalue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_font_family, bIncludeOverride);
			CSSValueList* cssvalue;
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssvalue);

			m_ncomputedFontFamily = -1;

			if (value == 0)
			{
				int count = cssvalue->get_length();
				for (uint i = 0; i < count; ++i)
				{
					CSSPrimitiveValue* nvalue = dynamic_cast<CSSPrimitiveValue*>(cssvalue->item(i));

					String name = nvalue->getStringValue();

					ASSERT(name.GetLength() > 0);

					if (name == "sans-serif")
					{
						name = L"Arial";
					}

				//	CFontDef* pFontDef = m_pView->AddFontDef(name, m_computedFontSize, m_computedFontWeight, m_computedFontStyle);
					if (true)
					{
						UINT32 index;
						BOOL exists;
						pFontCollection->FindFamilyName(name.GetData16(), &index, &exists);

						FontFamilyDef* pFontFamilyDef = new FontFamilyDef;
						pFontFamilyDef->AddRef();

						if (exists)
						{
							pFontCollection->GetFontFamily(index, &pFontFamilyDef->m_dwriteFontFamily);

							if (m_ncomputedFontFamily == -1)
								m_ncomputedFontFamily = i;
						}
						m_computedFontFamily.Add(pFontFamilyDef);
					}
					else
					{
						ASSERT(0);
#if 0
						LDraw::FontFamily* pFontFamily = new LDraw::FontFamily(name);
						if (pFontFamily->IsAvailable())
						{
							FontFamilyDef* pFontFamilyDef = new FontFamilyDef;
							pFontFamilyDef->AddRef();
							pFontFamilyDef->m_pFamily = pFontFamily;

							m_computedFontFamily.Add(pFontFamilyDef);
						}
#endif
					}
				//	else
				//		delete pFontFamily;
				}
			//	ASSERT(m_computedFontFamily.GetSize() > 0);
			}
			else if (value == 1)	// inherit
			{
				ASSERT(m_rparent);

				for (uint i = 0; i < m_rparent->m_computedFontFamily.GetSize(); ++i)
				{
					/*
				//	sysstring name = m_rparent->m_computedFontFamily[i]->m_pFamily->m_name;
					CFontDef* pFontDef = new CFontDef;//m_rparent->m_computedFontFamily[i];//m_pView->AddFontDef(name, m_computedFontSize, m_computedFontWeight, m_computedFontStyle);
				//	pFontDef->AddRef();
					pFontDef->m_pFamily = new LDraw::FontFamily(OLESTR("Courier New"));
				//	pFontDef->m_pFamily->LoadFile("c:/windows/fonts/cour.ttf");

			//		pFontDef->m_size = m_computedFontSize;
					m_computedFont.Add(pFontDef);
					*/

					m_rparent->m_computedFontFamily[i]->AddRef();
					m_computedFontFamily.Add(m_rparent->m_computedFontFamily[i]);
				}

				m_ncomputedFontFamily = m_rparent->m_ncomputedFontFamily;
			//	ASSERT(m_ncomputedFontFamily != -1);
			}
			else// if (value == 2)	// initial
			{
/*				CFontDef* pFontDef = new CFontDef;//m_pView->AddFontDef(OLESTR("Times New Roman", m_computedFontSize, m_computedFontWeight, m_computedFontStyle);
			//	pFontDef->m_size = m_computedFontSize;
				pFontDef->m_pFamily = new LDraw::FontFamily(OLESTR("Courier New"));
			//	pFontDef->m_pFamily->LoadFile("c:/windows/fonts/cour.ttf");

				m_computedFont.Add(pFontDef);
*/
				String name = WSTR("Courier New");
				FontFamilyDef* pFontFamilyDef = new FontFamilyDef;//m_pView->AddFontDef(OLESTR("Times New Roman", m_computedFontSize, m_computedFontWeight, m_computedFontStyle);
				pFontFamilyDef->AddRef();
			//	pFontFamilyDef->m_pFamily = new LDraw::FontFamily(name);
			//	pFontDef->m_pFamily->LoadFile("c:/windows/fonts/cour.ttf");

			//	m_computedFontFamily.Add(pFontFamilyDef);

				UINT32 index;
				BOOL exists;
				pFontCollection->FindFamilyName(name.GetData16(), &index, &exists);
				if (exists)
				{
				//	FontFamilyDef* pFontFamilyDef = new FontFamilyDef;
				//	pFontFamilyDef->AddRef();
					pFontCollection->GetFontFamily(index, &pFontFamilyDef->m_dwriteFontFamily);

					m_computedFontFamily.Add(pFontFamilyDef);
					m_ncomputedFontFamily = 0;
				}
				else
				{
					ASSERT(0);
				}
			}
		}
		break;

#if 0
	// cursor
	case CSSProperty_cursor:
		{
		//	cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_cursor, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);

			if (value == 0)
			{
				CSSUnitType unitType;
				cssprimitiveValue->get_primitiveType(&unitType);

				m_computedCursorUrl.Empty();
				m_computedCursor = -1;
				m_hCursor = NULL;
				m_pCursorUriElement = NULL;

				if (unitType == CSS_URI)
				{
					cssprimitiveValue->getStringValue(&m_computedCursorUrl);

					if (((BSTR)m_computedCursorUrl)[0] == L'#')
					{
						BSTR id = &((BSTR)m_computedCursorUrl)[1];

#if 0
						m_pCursorUriElement = (PSVGElement*)m_pWindow->m_htmTree->GetElementById(id);
#endif
					}
					else
					{
						/*	// TODO
						GetTempFileName();
						m_hCursor = LoadCursorFromFile(localFileName);
						*/
					}
				}
				else if (unitType == CSS_IDENT)
				{
					CComBSTR ident;
					cssprimitiveValue->getStringValue(&ident);

					m_computedCursor = IdentNameToIndex(ident, CursorIdents);
				}
			}
			else if (value == 1)
			{
				m_computedCursor = m_rparent->m_computedCursor;
				m_pCursorUriElement = m_rparent->m_pCursorUriElement;
			}
			else
			{
				m_computedCursor = Cursor_auto;
			}
		}
		break;
#endif
	// opacity (CSS3)
	case CSSProperty_opacity:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_opacity, bIncludeOverride);
			CSSPrimitiveValue* cssprimitiveValue;
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedOpacity = cssprimitiveValue->getFloatValue(CSS_NUMBER);
			else if (value == 1)
				m_computedOpacity = m_rparent->m_computedOpacity;
			else
				m_computedOpacity = 1;

			/*
		// Do these checks here, or in CSSPrimitiveValue ?
			if (m_computedOpacity < 0.0)			m_computedOpacity = 0.0;
			else if (m_computedOpacity > 1.0)	m_computedOpacity = 1.0;
			*/
		}
		break;

	// position
	case CSSProperty_position:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_position, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				String cssText = cssprimitiveValue->getStringValue();

				ASSERT(0);
#if 0
				if (!_wcsicmp(cssText->c_str(), L"relative"))			m_computedPosition = Position_relative;
				else if (!_wcsicmp(cssText->c_str(), L"absolute"))	m_computedPosition = Position_absolute;
				else if (!_wcsicmp(cssText->c_str(), L"fixed"))		m_computedPosition = Position_fixed;
				else /*if (!tcscmp(cssText, OLESTR("static"))*/	m_computedPosition = Position_static;
#endif
			}
			else if (value == 1)
			{
				m_computedPosition = m_rparent->m_computedPosition;
			}
			else
			{
				m_computedPosition = Position_static;
			}
		}
		break;

	// float
	case CSSProperty_float:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_float, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				String ident = cssprimitiveValue->getStringValue();

				m_computedFloat = IdentNameToIndex(ident, FloatIdents);

				// TODO remove
				m_computedFloat = Float_none;
			}
			else if (value == 1)
			{
				m_computedFloat = m_rparent->m_computedFloat;
			}
			else
			{
				m_computedFloat = Float_none;
			}
		}
		break;

#if 0
	// clear
	case CSSProperty_clear:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_clear, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				CComBSTR ident;
				cssprimitiveValue->getStringValue(&ident);

				m_computedClear = IdentNameToIndex(ident, ClearIdents);

#if 0
				if (!tcscmp(cssText, OLESTR("left"))			m_computedClear = Clear_left;
				else if (!tcscmp(cssText, OLESTR("right"))	m_computedClear = Clear_right;
				else if (!tcscmp(cssText, OLESTR("top"))		m_computedClear = Clear_top;
				else if (!tcscmp(cssText, OLESTR("bottom"))	m_computedClear = Clear_bottom;
				else if (!tcscmp(cssText, OLESTR("inside"))	m_computedClear = Clear_inside;
				else if (!tcscmp(cssText, OLESTR("outside"))	m_computedClear = Clear_outside;
				else if (!tcscmp(cssText, OLESTR("start"))	m_computedClear = Clear_start;
				else if (!tcscmp(cssText, OLESTR("end"))		m_computedClear = Clear_end;
				else if (!tcscmp(cssText, OLESTR("both"))		m_computedClear = Clear_both;
				else /*if (!tcscmp(cssText, OLESTR("none"))*/m_computedClear = Clear_none;
#endif
			}
			else if (value == 1)
			{
				m_computedClear = m_rparent->m_computedClear;
			}
			else
			{
				m_computedClear = Clear_none;
			}
		}
		break;
#endif

	// line-height
	case CSSProperty_line_height:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_line_height, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				CSSUnitType unitType = cssprimitiveValue->get_primitiveType();

				if (unitType == CSS_IDENT)
			//	if (!tcscmp(((CSSPrimitiveValue*)cssprimitiveValue.p)->m_cssText, OLESTR("normaOLESTR("))
				{
				/* normal 
				Tells user agents to set the computed value to a "reasonable" value based on
				the font size of the element. The value has the same meaning as <number>.
				We recommend a computed value for 'normal' between 1.0 to 1.2. 
				*/
					m_computedLineHeight = m_computedFontSize*1;
				}
				else
				{
					//cssprimitiveValue->get_primitiveType(&unitType);

					if (unitType == CSS_PERCENTAGE)
					{
						double pcnt = cssprimitiveValue->getFloatValue(CSS_PERCENTAGE);
						m_computedLineHeight = m_computedFontSize*pcnt/100;
					}
					/*
					else if (unitType == CSS_EM)
					{
					}
					*/
					else
					{
						m_computedLineHeight = cssprimitiveValue->getFloatValue(CSS_PX);
					}
				}
			}
			else if (value == 1)
			{
				m_computedLineHeight = m_rparent->m_computedLineHeight;
			}
			else
			{
				m_computedLineHeight = m_computedFontSize;	// 'normal', See above
			}
		}
		break;

	// color
	case CSSProperty_color:
		{
			m_pColorBrush = NULL;//LDraw::SolidBrush();

			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				m_computedColor = CRGBColor(255, 0, 0, 0);	// black (in case 'color: currentColor;'
				m_computedColor = GetComputedColorValue(cssprimitiveValue);
			}
			else if (value == 1)
			{
				m_computedColor = m_rparent->m_computedColor;
			}
			else
			{
				m_computedColor = CRGBColor(255, 0, 0, 0);	// black
			}
		}
		break;

	// background-color
	case CSSProperty_background_color:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_background_color, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedBackgroundColor = GetComputedColorValue(cssprimitiveValue);
			else if (value == 1)
				m_computedBackgroundColor = m_rparent->m_computedBackgroundColor;
			else
				m_computedBackgroundColor = CRGBColor(0, 0, 0, 0);	// 'transparent'
		}
		break;

	case CSSProperty_text_underline_color:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedTextUnderlineColor = GetComputedColorValue(cssprimitiveValue);
			else if (value == 1)
				m_computedTextUnderlineColor = m_rparent->m_computedTextUnderlineColor;
			else
				m_computedTextUnderlineColor = m_computedColor;	// 'currentColor'
		}
		break;

	case CSSProperty_text_overline_color:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedTextOverlineColor = GetComputedColorValue(cssprimitiveValue);
			else if (value == 1)
				m_computedTextOverlineColor = m_rparent->m_computedTextOverlineColor;
			else
				m_computedTextOverlineColor = m_computedColor;	// 'currentColor'
		}
		break;

	case CSSProperty_text_line_through_color:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedTextLineThroughColor = GetComputedColorValue(cssprimitiveValue);
			else if (value == 1)
				m_computedTextLineThroughColor = m_rparent->m_computedTextLineThroughColor;
			else
				m_computedTextLineThroughColor = m_computedColor;	// 'currentColor'
		}
		break;

	// border colors
	case CSSProperty_border_left_color:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_border_left_color, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedBorderColor[0] = GetComputedColorValue(cssprimitiveValue);
			else if (value == 1)
				m_computedBorderColor[0] = m_rparent->m_computedBorderColor[0];
			else
				m_computedBorderColor[0] = m_computedColor;	// 'currentColor'

		}
		break;

	case CSSProperty_border_top_color:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_border_top_color, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedBorderColor[1] = GetComputedColorValue(cssprimitiveValue);
			else if (value == 1)
				m_computedBorderColor[1] = m_rparent->m_computedBorderColor[1];
			else
				m_computedBorderColor[1] = m_computedColor;	// 'currentColor'
		}
		break;

	case CSSProperty_border_right_color:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_border_right_color, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedBorderColor[2] = GetComputedColorValue(cssprimitiveValue);
			else if (value == 1)
				m_computedBorderColor[2] = m_rparent->m_computedBorderColor[2];
			else
				m_computedBorderColor[2] = m_computedColor;	// 'currentColor'
		}
		break;

	case CSSProperty_border_bottom_color:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_border_bottom_color, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedBorderColor[3] = GetComputedColorValue(cssprimitiveValue);
			else if (value == 1)
				m_computedBorderColor[3] = m_rparent->m_computedBorderColor[3];
			else
				m_computedBorderColor[3] = m_computedColor;	// 'currentColor'
		}
		break;

	case CSSProperty_text_underline_style:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedTextUnderlineStyle = GetBorderStyle(cssprimitiveValue);
			else if (value == 1)
				m_computedTextUnderlineStyle = m_rparent->m_computedTextUnderlineStyle;
			else
				m_computedTextUnderlineStyle = BorderStyle_none;
		}
		break;

	case CSSProperty_text_overline_style:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedTextOverlineStyle = GetBorderStyle(cssprimitiveValue);
			else if (value == 1)
				m_computedTextOverlineStyle = m_rparent->m_computedTextOverlineStyle;
			else
				m_computedTextOverlineStyle = BorderStyle_none;
		}
		break;

	case CSSProperty_text_line_through_style:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedTextLineThroughStyle = GetBorderStyle(cssprimitiveValue);
			else if (value == 1)
				m_computedTextLineThroughStyle = m_rparent->m_computedTextLineThroughStyle;
			else
				m_computedTextLineThroughStyle = BorderStyle_none;
		}
		break;

	// border styles
	case CSSProperty_border_left_style:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedBorderStyle[0] = GetBorderStyle(cssprimitiveValue);
			else if (value == 1)
				m_computedBorderStyle[0] = m_rparent->m_computedBorderStyle[0];
			else
				m_computedBorderStyle[0] = BorderStyle_none;
		}
		break;

	case CSSProperty_border_top_style:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedBorderStyle[1] = GetBorderStyle(cssprimitiveValue);
			else if (value == 1)
				m_computedBorderStyle[1] = m_rparent->m_computedBorderStyle[1];
			else
				m_computedBorderStyle[1] = BorderStyle_none;
		}
		break;

	case CSSProperty_border_right_style:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedBorderStyle[2] = GetBorderStyle(cssprimitiveValue);
			else if (value == 1)
				m_computedBorderStyle[2] = m_rparent->m_computedBorderStyle[2];
			else
				m_computedBorderStyle[2] = BorderStyle_none;
		}
		break;

	case CSSProperty_border_bottom_style:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedBorderStyle[3] = GetBorderStyle(cssprimitiveValue);
			else if (value == 1)
				m_computedBorderStyle[3] = m_rparent->m_computedBorderStyle[3];
			else
				m_computedBorderStyle[3] = BorderStyle_none;
		}
		break;

	case CSSProperty_min_width:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				if (cssprimitiveValue->get_primitiveType() == CSS_PERCENTAGE)
					m_computedMinWidth = m_rparent->m_computedWidth * cssprimitiveValue->getFloatValue(CSS_PERCENTAGE);
				else
					m_computedMinWidth = cssprimitiveValue->getFloatValue(CSS_PX);
			}
			else if (value == 1)
			{
				m_computedMinWidth = m_rparent->m_computedMinWidth;
			}
			else
				m_computedMinWidth = 0;
		}
		break;

	case CSSProperty_max_width:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				if (cssprimitiveValue->get_primitiveType() == CSS_IDENT)
					m_computedMaxWidth = -1;	// unbounded
				else if (cssprimitiveValue->get_primitiveType() == CSS_PERCENTAGE)
					m_computedMaxWidth = m_rparent->m_computedWidth * cssprimitiveValue->getFloatValue(CSS_PERCENTAGE);
				else
					m_computedMaxWidth = cssprimitiveValue->getFloatValue(CSS_PX);
			}
			else if (value == 1)
			{
				m_computedMaxWidth = m_rparent->m_computedMaxWidth;
			}
			else
				m_computedMaxWidth = -1;
		}
		break;

	// border widths (TODO %)
	case CSSProperty_border_left_width:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedBorderWidth[0] = GetBorderWidth(cssprimitiveValue);
			else if (value == 1)
				m_computedBorderWidth[0] = m_rparent->m_computedBorderWidth[0];
			else
				m_computedBorderWidth[0] = 0;
		}
		break;

	case CSSProperty_border_top_width:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_border_top_width, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedBorderWidth[1] = GetBorderWidth(cssprimitiveValue);
			else if (value == 1)
				m_computedBorderWidth[1] = m_rparent->m_computedBorderWidth[1];
			else
				m_computedBorderWidth[1] = 0;
		}
		break;

	case CSSProperty_border_right_width:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_border_right_width, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedBorderWidth[2] = GetBorderWidth(cssprimitiveValue);
			else if (value == 1)
				m_computedBorderWidth[2] = m_rparent->m_computedBorderWidth[2];
			else
				m_computedBorderWidth[2] = 0;
		}
		break;

	case CSSProperty_border_bottom_width:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_border_bottom_width, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedBorderWidth[3] = GetBorderWidth(cssprimitiveValue);
			else if (value == 1)
				m_computedBorderWidth[3] = m_rparent->m_computedBorderWidth[3];
			else
				m_computedBorderWidth[3] = 0;
		}
		break;

	// padding
	case CSSProperty_padding_left:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_padding_left, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedPadding[0] = ConvertCSSLength(cssprimitiveValue);
			else if (value == 1)
				m_computedPadding[0] = m_rparent->m_computedPadding[0];
			else
				m_computedPadding[0] = 0;
		}
		break;

	case CSSProperty_padding_top:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_padding_top, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedPadding[1] = ConvertCSSLength(cssprimitiveValue);
			else if (value == 1)
				m_computedPadding[1] = m_rparent->m_computedPadding[1];
			else
				m_computedPadding[1] = 0;
		}
		break;

	case CSSProperty_padding_right:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_padding_right, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedPadding[2] = ConvertCSSLength(cssprimitiveValue);
			else if (value == 1)
				m_computedPadding[2] = m_rparent->m_computedPadding[2];
			else
				m_computedPadding[2] = 0;
		}
		break;

	case CSSProperty_padding_bottom:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_padding_bottom, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedPadding[3] = ConvertCSSLength(cssprimitiveValue);
			else if (value == 1)
				m_computedPadding[3] = m_rparent->m_computedPadding[3];
			else
				m_computedPadding[3] = 0;
		}
		break;

	// margin
	case CSSProperty_margin_left:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_margin_left, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == Style::Value_Specified)
				m_computedMargin[0] = ConvertCSSLength(cssprimitiveValue);
			else if (value == 1)
				m_computedMargin[0] = m_rparent->m_computedMargin[0];
			else
				m_computedMargin[0] = 0;
		}
		break;

	case CSSProperty_margin_top:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_margin_top, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == Style::Value_Specified)
				m_computedMargin[1] = ConvertCSSLength(cssprimitiveValue);
			else if (value == 1)
				m_computedMargin[1] = m_rparent->m_computedMargin[1];
			else
				m_computedMargin[1] = 0;
		}
		break;

	case CSSProperty_margin_right:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_margin_right, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == Style::Value_Specified)
				m_computedMargin[2] = ConvertCSSLength(cssprimitiveValue);
			else if (value == 1)
				m_computedMargin[2] = m_rparent->m_computedMargin[2];
			else
				m_computedMargin[2] = 0;
		}
		break;

	case CSSProperty_margin_bottom:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_margin_bottom, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == Style::Value_Specified)
				m_computedMargin[3] = ConvertCSSLength(cssprimitiveValue);
			else if (value == 1)
				m_computedMargin[3] = m_rparent->m_computedMargin[3];
			else
				m_computedMargin[3] = 0;
		}
		break;

	// outline
		// style
	case CSSProperty_outline_style:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_outline_style, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == Style::Value_Specified)
				m_computedOutlineStyle = GetBorderStyle(cssprimitiveValue);
			else if (value == 1)
				m_computedOutlineStyle = m_rparent->m_computedOutlineStyle;
			else
				m_computedOutlineStyle = BorderStyle_none;
		}
		break;

	case CSSProperty_outline_width:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_outline_width, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == Style::Value_Specified)
				m_computedOutlineWidth = GetBorderWidth(cssprimitiveValue);
			else if (value == Style::Value_Inherited)
				m_computedOutlineWidth = m_rparent->m_computedOutlineWidth;
			else
				m_computedOutlineWidth = THICKNESS_MEDIUM;
		}
		break;

	case CSSProperty_width:
		{
		//	cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_width, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				CSSUnitType unitType = cssprimitiveValue->get_primitiveType();

				if (unitType == CSS_IDENT/*!tcscmp(((CSSPrimitiveValue*)cssprimitiveValue.p)->m_cssText, OLESTR("auto")*/)
				{
					// auto
					//m_specifiedWidth = -1;
				//	m_computedWidth = 0;
				}
				else
				{
					if (unitType == CSS_PERCENTAGE)
					{
						double pcnt = cssprimitiveValue->getFloatValue(CSS_PERCENTAGE);

					//	m_specifiedWidth = -(pcnt+1);

					// TODO, containing block
						PElementBase* pPElement = m_rparent;
						while (pPElement->m_pBox == NULL)
						{
							pPElement = pPElement->m_rparent;
						}

						m_computedWidth = pPElement->m_pBox->m_innerRect.Width * pcnt / 100;
					}
					else if (unitType == CSS_EMS)
					{
						double value = cssprimitiveValue->getFloatValue(CSS_EMS);

					//	m_specifiedWidth = value*m_computedFontSize;
						m_computedWidth = value*m_computedFontSize;
					}
					else if (unitType == CSS_EXS)
					{
						double value = cssprimitiveValue->getFloatValue(CSS_EXS);

						// TODO, improve this
					//	m_specifiedWidth = value*m_computedFontSize/2;
						m_computedWidth = value*m_computedFontSize/2;
					}
					else
					{
					//	m_specifiedWidth = cssprimitiveValue->getFloatValue(CSS_PX);
						m_computedWidth = cssprimitiveValue->getFloatValue(CSS_PX);
					}
				}
			}
			else if (value == 1)
			{
//				m_specifiedWidth = m_rparent->m_specifiedWidth;
				m_computedWidth = 0;
			}
			else
			{
			//	m_specifiedWidth = -1;	// 'auto'
				//if (m_rparent)
					m_computedWidth = -1;	// auto ??
			}
		}
		break;

	// height
	case CSSProperty_height:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_height, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				CSSUnitType unitType = cssprimitiveValue->get_primitiveType();

				if (unitType == CSS_IDENT/*!tcscmp(((CSSPrimitiveValue*)cssprimitiveValue.p)->m_cssText, OLESTR("auto")*/)
				{
					//m_computedHeight = 0;
					m_computedHeight = -1;
				}
				else
				{
					if (unitType == CSS_PERCENTAGE)
					{
						double pcnt = cssprimitiveValue->getFloatValue(CSS_PERCENTAGE);

						//m_specifiedHeight = -(pcnt+1);

						// TODO, containing block box
					//	m_computedHeight = m_rparent->m_pBox->m_innerRect.Height * pcnt / 100;
						m_computedHeight = m_rparent->m_computedHeight;//pBox->m_innerRect.Height * pcnt / 100;
					}
					else if (unitType == CSS_EMS)
					{
						double value = cssprimitiveValue->getFloatValue(CSS_EMS);

						m_computedHeight = value*m_computedFontSize;
					}
					else if (unitType == CSS_EXS)
					{
						double value = cssprimitiveValue->getFloatValue(CSS_EXS);

						// TODO, improve this
						m_computedHeight = value*m_computedFontSize/2;
					}
					else
					{
						m_computedHeight = cssprimitiveValue->getFloatValue(CSS_PX);
					}
				}
			}
			else if (value == 1)
			{
				m_computedHeight = m_rparent->m_computedHeight;
			}
			else
			{
				//m_computedHeight = 0;// -1;	// 'auto'
				if (m_rparent)
					m_computedHeight = -1;	// auto ??
			}

			//ASSERT(m_specifiedHeight != -999999);
		}
		break;

	// left
	case CSSProperty_left:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_left, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				CSSUnitType unitType = cssprimitiveValue->get_primitiveType();

				if (unitType == CSS_IDENT/*!tcscmp(((CSSPrimitiveValue*)cssprimitiveValue.p)->m_cssText, OLESTR("auto")*/)
				{
					m_specifiedLeft = -1;
				}
				else
				{
					if (unitType == CSS_PERCENTAGE)
					{
						double pcnt = cssprimitiveValue->getFloatValue(CSS_PERCENTAGE);

						m_specifiedLeft = -(pcnt+1);
					}
					else
					{
						m_specifiedLeft = cssprimitiveValue->getFloatValue(CSS_PX);
					}
				}
			}
			else if (value == 1)
			{
				m_specifiedLeft = m_rparent->m_specifiedLeft;
			}
			else
			{
				m_specifiedLeft = -1;	// 'auto'
			}
		}
		break;

	// right
	case CSSProperty_right:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_right, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				CSSUnitType unitType = cssprimitiveValue->get_primitiveType();

				if (unitType == CSS_IDENT/*!tcscmp(((CSSPrimitiveValue*)cssprimitiveValue.p)->m_cssText, OLESTR("auto")*/)
				{
					m_specifiedRight = -1;
				}
				else
				{
					if (unitType == CSS_PERCENTAGE)
					{
						double pcnt = cssprimitiveValue->getFloatValue(CSS_PERCENTAGE);

						m_specifiedRight = -(pcnt+1);
					}
					else
					{
						m_specifiedRight = cssprimitiveValue->getFloatValue(CSS_PX);
					}
				}
			}
			else if (value == 1)
			{
				m_specifiedRight = m_rparent->m_specifiedRight;
			}
			else
				m_specifiedRight = -1;	// 'auto'
		}
		break;

	// top
	case CSSProperty_top:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_top, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				CSSUnitType unitType = cssprimitiveValue->get_primitiveType();

				if (unitType == CSS_IDENT/*!tcscmp(((CSSPrimitiveValue*)cssprimitiveValue.p)->m_cssText, OLESTR("auto")*/)
				{
					m_specifiedTop = -1;
				}
				else
				{
					if (unitType == CSS_PERCENTAGE)
					{
						double pcnt = cssprimitiveValue->getFloatValue(CSS_PERCENTAGE);

						/*
						m_specifiedHeight = -(pcnt+1);
						*/
					}
					else
					{
						m_specifiedTop = cssprimitiveValue->getFloatValue(CSS_PX);
					}
				}
			}
			else if (value == 1)
			{
				m_specifiedTop = m_rparent->m_specifiedTop;
			}
			else
			{
				m_specifiedTop = -1;	// 'auto'
			}
		}
		break;

	// overflow
	case CSSProperty_overflow:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_overflow, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				String cssText = cssprimitiveValue->getStringValue();

				ASSERT(0);
#if 0
				if (!_wcsicmp(cssText->c_str(), L"visible"))			m_computedOverflowY = Overflow_visible;
				else if (!_wcsicmp(cssText->c_str(), L"hidden"))		m_computedOverflowY = Overflow_hidden;
				else if (!_wcsicmp(cssText->c_str(), L"scroll"))		m_computedOverflowY = Overflow_scroll;
				else /*if (!tcscmp(cssText, OLESTR("auto"))*/	m_computedOverflowY = Overflow_auto;
#endif
			}
			else if (value == 1)
			{
				m_computedOverflowY = m_rparent->m_computedOverflowY;
			}
			else
			{
				m_computedOverflowY = Overflow_auto;
			}

			m_computedOverflowX = m_computedOverflowY;
		}
		break;

	// clip
	case CSSProperty_clip:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_clip, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				CSSUnitType unitType = cssprimitiveValue->get_primitiveType();
				if (unitType == CSS_IDENT)
				{
					m_computedClip[0] = 0;
					m_computedClip[1] = 0;
					m_computedClip[2] = 0;
					m_computedClip[3] = 0;
				}
				else
				{
					ASSERT(unitType == CSS_RECT);

					CSSRect* rect = cssprimitiveValue->getRectValue();

					{
						CSSPrimitiveValue* csstop = rect->get_top();

						CSSUnitType unitType = csstop->get_primitiveType();
						if (unitType == CSS_IDENT)
						{
							m_computedClip[0] = 0;
						}
						else
							m_computedClip[0] = csstop->getFloatValue(CSS_NUMBER);
					}

					{
						CSSPrimitiveValue* cssright = rect->get_right();

						CSSUnitType unitType = cssright->get_primitiveType();
						if (unitType == CSS_IDENT)
						{
							m_computedClip[1] = 0;
						}
						else
							m_computedClip[1] = cssright->getFloatValue(CSS_NUMBER);
					}

					{
						CSSPrimitiveValue* cssbottom = rect->get_bottom();

						CSSUnitType unitType = cssbottom->get_primitiveType();
						if (unitType == CSS_IDENT)
						{
							m_computedClip[2] = 0;
						}
						else
							m_computedClip[2] = cssbottom->getFloatValue(CSS_NUMBER);
					}

					{
						CSSPrimitiveValue* cssleft = rect->get_left();

						CSSUnitType unitType = cssleft->get_primitiveType();
						if (unitType == CSS_IDENT)
						{
							m_computedClip[3] = 0;
						}
						else
							m_computedClip[3] = cssleft->getFloatValue(CSS_NUMBER);
					}
				}
			}
			else if (value == 1)
			{
				m_computedClip[0] = m_rparent->m_computedClip[0];
				m_computedClip[1] = m_rparent->m_computedClip[1];
				m_computedClip[2] = m_rparent->m_computedClip[2];
				m_computedClip[3] = m_rparent->m_computedClip[3];
			}
			else
			{
				m_computedClip[0] = 0;
				m_computedClip[1] = 0;
				m_computedClip[2] = 0;
				m_computedClip[3] = 0;
			}
		}
		break;

	// text-align
	case CSSProperty_text_align:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_text_align, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				String cssText = cssprimitiveValue->getStringValue();

				ASSERT(0);
#if 0
				if (!_wcsicmp(cssText->c_str(), L"right"))				m_computedTextAlign = TextAlign_right;
				else if (!_wcsicmp(cssText->c_str(), L"center"))		m_computedTextAlign = TextAlign_center;
				else if (!_wcsicmp(cssText->c_str(), L"justify"))	m_computedTextAlign = TextAlign_justify;
				else /*if (!tcscmp(cssText, OLESTR("left"))*/	m_computedTextAlign = TextAlign_left;
#endif
			}
			else if (value == 1)
			{
				m_computedTextAlign = m_rparent->m_computedTextAlign;
			}
			else
			{
				m_computedTextAlign = TextAlign_left;
			}
		}
		break;

#if 0
	// background-image
	case CSSProperty_background_image:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_background_image, bIncludeOverride);
			if (m_pBackgroundImage)
			{
				g_Images.RemoveImage(m_pBackgroundImage);
				m_pBackgroundImage = NULL;
			}
			m_computedBackgroundImage.Empty();

			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
		//		CComBSTR cssText;
		//		cssprimitiveValue->getStringValue(&cssText);

			// TODO, none ??
				CComBSTR string;
				cssprimitiveValue->getStringValue(&string);
				//if ((BSTR)string == NULL) string = OLESTR("";

				m_computedBackgroundImage = string;

			}
			else if (value == 1)
			{
				m_computedBackgroundImage = m_rparent->m_computedBackgroundImage;
			}
			else
			{
				m_computedBackgroundImage.Empty();
			}

			if (m_computedBackgroundImage.Length() && tcsicmp(m_computedBackgroundImage, OLESTR("none"))
			{
#if 0
				TCHAR result[2048];
				{
					CComBSTR documentUrl;
					m_pView->m_document->get_url(&documentUrl);

					_bstr_t baseUrl = documentUrl;

					DWORD resultLen = sizeof(result);
					InternetCombineUrl(baseUrl, W2A(m_computedBackgroundImage), result, &resultLen, 0);
				}

			// Load background-image for first time
				m_pBackgroundImage = g_Images.OpenImage(A2W(result));
#endif
			}
		}
		break;

	case CSSProperty_background_repeat:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_background_repeat, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				CComBSTR cssText;
				cssprimitiveValue->getStringValue(&cssText);

				if (!tcsicmp(cssText, OLESTR("repeat"))			m_computedBackgroundRepeat = BackgroundRepeat_repeat;
				else if (!tcsicmp(cssText, OLESTR("repeat-x"))	m_computedBackgroundRepeat = BackgroundRepeat_repeat_x;
				else if (!tcsicmp(cssText, OLESTR("repeat-y"))		m_computedBackgroundRepeat = BackgroundRepeat_repeat_y;
				else /*if (!tcscmp(cssText, OLESTR("no-repeat"))*/m_computedBackgroundRepeat = BackgroundRepeat_no_repeat;
			}
			else if (value == 1)
			{
				m_computedBackgroundRepeat = m_rparent->m_computedBackgroundRepeat;
			}
			else
			{
				m_computedBackgroundRepeat = BackgroundRepeat_no_repeat;
			}
		}
		break;
#endif

	// z-index
	case CSSProperty_z_index:
		{
#if 0
			if (m_pLocalStackingContext)
			{
				delete m_pLocalStackingContext;
				m_pLocalStackingContext = NULL;
			}
#endif
			if (m_parent == NULL)
			{
#if 0
				m_pLocalStackingContext = new CCSSStackingContext;
				m_pStackingContext = m_pLocalStackingContext;
#endif
			}
			else
			{
			//	cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_z_index, bIncludeOverride);
				int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
				if (value == 0)
				{
					CSSUnitType unitType = cssprimitiveValue->get_primitiveType();

					if (unitType == CSS_IDENT/*!tcscmp(((CSSPrimitiveValue*)cssprimitiveValue.p)->m_cssText, OLESTR("auto")*/)
					{
					/* CSS2 : 9.9.1 Specifying the stack level: the 'z-index' property

						auto:
							The stack level of the generated box in the current stacking context is
							the same as its parent's box. The box does not establish a new local
							stacking context. 
					*/
#if 0
						m_pStackingContext = (m_parent)->m_pStackingContext;
#endif
						m_specifiedZIndex = INT_MIN;	// magic value for auto
						m_computedZIndex = 0;

#if 0
						m_pLocalStackingContext = NULL;

						m_parent->m_pStackingContext->AddElement(this);
#endif
					}
					else
					{
					/* CSS2 : 9.9.1 Specifying the stack level: the 'z-index' property
						<integer> 
							This integer is the stack level of the generated box in the current
							stacking context. The box also establishes a local stacking context
							in which its stack level is '0'
					*/

#if 0
						m_pStackingContext = (m_parent)->m_pStackingContext;
#endif
						double zindex = cssprimitiveValue->getFloatValue(CSS_NUMBER);

						m_specifiedZIndex = (int)zindex;
						m_computedZIndex = (int)zindex;

#if 0
						m_parent->m_pStackingContext->AddElement(this);

						m_pLocalStackingContext = new CCSSStackingContext;
						m_pStackingContext = m_pLocalStackingContext;
#endif
					}
				}
				else
				{
					// Same as auto above

				/* CSS2 : 9.9.1 Specifying the stack level: the 'z-index' property

					auto:
						The stack level of the generated box in the current stacking context is
						the same as its parent's box. The box does not establish a new local
						stacking context. 
				*/
#if 0
					m_pStackingContext = (m_parent)->m_pStackingContext;
#endif
					m_specifiedZIndex = INT_MIN;	// magic value for auto
					m_computedZIndex = 0;

#if 0
					m_pLocalStackingContext = NULL;

					m_parent->m_pStackingContext->AddElement(this);
#endif
				}
			}
		}
		break;
#if 0
	case CSSProperty_border_collapse:	// CSS Table
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_border_collapse, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				sysstring ident = cssprimitiveValue->getStringValue();

				m_computedBorderCollapse = IdentNameToIndex(ident, BorderCollapseIdents);
			}
			else if (value == 1)
			{
				m_computedBorderCollapse = m_rparent->m_computedBorderCollapse;
			}
			else
			{
				m_computedBorderCollapse = BorderCollapse_separate;
			}
		}
		break;

	case CSSProperty_empty_cells:	// CSS Table
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_empty_cells, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				CComBSTR ident;
				cssprimitiveValue->getStringValue(&ident);

				m_computedEmptyCells = IdentNameToIndex(ident, EmptyCellsIdents);
			}
			else if (value == 1)
			{
				m_computedEmptyCells = m_rparent->m_computedEmptyCells;
			}
			else
			{
				m_computedEmptyCells = EmptyCells_show;
			}
		}
		break;

	case CSSProperty_border_top_left_radius:
	case CSSProperty_border_top_right_radius:
	case CSSProperty_border_bottom_left_radius:
	case CSSProperty_border_bottom_right_radius:
		{
			CComQIPtr<CSSValueList> cssvalue;// = GetSpecifiedPropertyValue(documentStyle, propertyIndex, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssvalue);
			if (value == 0)
			{
				long count;
				cssvalue->get_length(&count);

				double radius[2];

				if (count == 1)
				{
					CComPtr<ILCSSPrimitiveValue> nvalue;
					cssvalue->item(0, (CSSValue**)&nvalue);

					nvalue->getFloatValue(CSS_NUMBER, &radius[0]);
					radius[1] = radius[0];
				}
				else if (count >= 2)
				{
					{
						CComPtr<ILCSSPrimitiveValue> nvalue;
						cssvalue->item(0, (CSSValue**)&nvalue);

						nvalue->getFloatValue(CSS_NUMBER, &radius[0]);
					}

					{
						CComPtr<ILCSSPrimitiveValue> nvalue;
						cssvalue->item(1, (CSSValue**)&nvalue);

						nvalue->getFloatValue(CSS_NUMBER, &radius[1]);
					}
				}

				switch (propertyIndex)
				{
				case CSSProperty_border_top_left_radius:
					{
						m_computedBorderRadius[0][0] = radius[0];
						m_computedBorderRadius[0][1] = radius[1];
					}
					break;
					
				case CSSProperty_border_top_right_radius:
					{
						m_computedBorderRadius[1][0] = radius[0];
						m_computedBorderRadius[1][1] = radius[1];
					}
					break;
					
				case CSSProperty_border_bottom_left_radius:
					{
						m_computedBorderRadius[2][0] = radius[0];
						m_computedBorderRadius[2][1] = radius[1];
					}
					break;
					
				case CSSProperty_border_bottom_right_radius:
					{
						m_computedBorderRadius[3][0] = radius[0];
						m_computedBorderRadius[3][1] = radius[1];
					}
					break;
				}
			}
			else if (value == 1)
			{
				switch (propertyIndex)
				{
				case CSSProperty_border_top_left_radius:
					{
						m_computedBorderRadius[0][0] = m_rparent->m_computedBorderRadius[0][0];
						m_computedBorderRadius[0][1] = m_rparent->m_computedBorderRadius[0][1];
					}
					break;
					
				case CSSProperty_border_top_right_radius:
					{
						m_computedBorderRadius[1][0] = m_rparent->m_computedBorderRadius[1][0];
						m_computedBorderRadius[1][1] = m_rparent->m_computedBorderRadius[1][1];
					}
					break;
					
				case CSSProperty_border_bottom_left_radius:
					{
						m_computedBorderRadius[2][0] = m_rparent->m_computedBorderRadius[2][0];
						m_computedBorderRadius[2][1] = m_rparent->m_computedBorderRadius[2][1];
					}
					break;
					
				case CSSProperty_border_bottom_right_radius:
					{
						m_computedBorderRadius[3][0] = m_rparent->m_computedBorderRadius[3][0];
						m_computedBorderRadius[3][1] = m_rparent->m_computedBorderRadius[3][1];
					}
					break;
				}
			}
			else
			{
				switch (propertyIndex)
				{
				case CSSProperty_border_top_left_radius:
					{
						m_computedBorderRadius[0][0] = 0;
						m_computedBorderRadius[0][1] = 0;
					}
					break;
					
				case CSSProperty_border_top_right_radius:
					{
						m_computedBorderRadius[1][0] = 0;
						m_computedBorderRadius[1][1] = 0;
					}
					break;
					
				case CSSProperty_border_bottom_left_radius:
					{
						m_computedBorderRadius[2][0] = 0;
						m_computedBorderRadius[2][1] = 0;
					}
					break;
					
				case CSSProperty_border_bottom_right_radius:
					{
						m_computedBorderRadius[3][0] = 0;
						m_computedBorderRadius[3][1] = 0;
					}
					break;
				}
			}
		}
		break;
#endif

	case CSSProperty_border_spacing:	// CSS Table
		{
//			CComQIPtr<CSSValueList> cssvalue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_border_spacing, bIncludeOverride);
			CSSValueList* cssvalue;// = GetSpecifiedPropertyValue(documentStyle, propertyIndex, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssvalue);

			if (value == 0)
			{
				long count = cssvalue->get_length();

				if (count == 1)
				{
					CSSPrimitiveValue* nvalue = dynamic_cast<CSSPrimitiveValue*>(cssvalue->item(0));

					m_computedBorderSpacing[0] = nvalue->getFloatValue(CSS_NUMBER);
					m_computedBorderSpacing[1] = m_computedBorderSpacing[0];
				}
				else if (count >= 2)
				{
					{
						CSSPrimitiveValue* nvalue = dynamic_cast<CSSPrimitiveValue*>(cssvalue->item(0));

						m_computedBorderSpacing[0] = nvalue->getFloatValue(CSS_NUMBER);
					}

					{
						CSSPrimitiveValue* nvalue = dynamic_cast<CSSPrimitiveValue*>(cssvalue->item(1));

						m_computedBorderSpacing[1] = nvalue->getFloatValue(CSS_NUMBER);
					}
				}
			}
			else if (value == 1)
			{
				m_computedBorderSpacing[0] = m_rparent->m_computedBorderSpacing[0];
				m_computedBorderSpacing[1] = m_rparent->m_computedBorderSpacing[1];
			}
			else
			{
				m_computedBorderSpacing[0] = 0;
				m_computedBorderSpacing[1] = 0;
			}
		}
		break;

#if 0
	// enable-background (SVG)
	case CSSProperty_enable_background:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_enable_background, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				CComBSTR ident;
				cssprimitiveValue->getStringValue(&ident);

				if (!tcscmp(ident, OLESTR("accumulate"))		m_computedEnableBackground = 0;
				else	/*new*/	m_computedEnableBackground = 1;
			}
			else if (value == 1)
			{
				m_computedEnableBackground = m_rparent->m_computedEnableBackground;
			}
			else
			{
				m_computedEnableBackground = 0;
			}
		}
		break;
#endif

	// stroke-width (SVG)
	case CSSProperty_stroke_width:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
		// TODO %
				m_computedStrokeWidth = cssprimitiveValue->getFloatValue(CSS_NUMBER);
			}
			else if (value == 1)
			{
				m_computedStrokeWidth = m_rparent->m_computedStrokeWidth;
			}
			else
			{
				m_computedStrokeWidth = 1;
			}
		}
		break;

#if 0
	case CSSProperty_stroke_miterlimit:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_stroke_miterlimit, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
				cssprimitiveValue->getFloatValue(CSS_NUMBER, &m_computedStrokeMiterLimit);
			else if (value == 1)
				m_computedStrokeMiterLimit = m_rparent->m_computedStrokeMiterLimit;
			else
				m_computedStrokeMiterLimit = 4;
		}
		break;
#endif

	// fill-opacity (SVG)
	case CSSProperty_fill_opacity:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_fill_opacity, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedFillOpacity = cssprimitiveValue->getFloatValue(CSS_NUMBER);
			else if (value == 1)
				m_computedFillOpacity = m_rparent->m_computedFillOpacity;
			else
				m_computedFillOpacity = 1;
		}
		break;

	// stroke-opacity (SVG)
	case CSSProperty_stroke_opacity:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_stroke_opacity, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedStrokeOpacity = cssprimitiveValue->getFloatValue(CSS_NUMBER);
			else if (value == 1)
				m_computedStrokeOpacity = m_rparent->m_computedStrokeOpacity;
			else
				m_computedStrokeOpacity = 1;
		}
		break;

#if 0
	case CSSProperty_shape_rendering:	// (SVG)
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, propertyIndex, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				CComBSTR ident;
				cssprimitiveValue->getStringValue(&ident);

				m_computedShapeRendering = IdentNameToIndex(ident, ShapeRenderingIdents);
			}
			else if (value == 1)
			{
				m_computedShapeRendering  = m_rparent->m_computedShapeRendering;
			}
			else
			{
				m_computedShapeRendering = ShapeRendering_auto;
			}
		}
		break;

	case CSSProperty_image_rendering:	// (SVG)
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_image_rendering, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				CComBSTR ident;
				cssprimitiveValue->getStringValue(&ident);

				m_computedImageRendering = IdentNameToIndex(ident, ImageRenderingIdents);
			}
			else if (value == 1)
			{
				m_computedImageRendering = m_rparent->m_computedImageRendering;
			}
			else
			{
				m_computedImageRendering = ImageRendering_auto;
			}
		}
		break;

	// fill-rule (SVG)
	case CSSProperty_fill_rule:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_fill_rule, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				CComBSTR cssText;
				cssprimitiveValue->getStringValue(&cssText);

				m_computedFillRule = IdentNameToIndex(cssText, FillRuleStrings);
			}
			else if (value == 1)
			{
				m_computedFillRule = m_rparent->m_computedFillRule;
			}
			else
			{
				m_computedFillRule = FillRule_nonzero;
			}
		}
		break;

	// clip-rule (SVG)
	case CSSProperty_clip_rule:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_clip_rule, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				CComBSTR cssText;
				cssprimitiveValue->getStringValue(&cssText);

				m_computedClipRule = IdentNameToIndex(cssText, ClipRuleStrings);
			}
			else if (value == 1)
			{
				m_computedClipRule = m_rparent->m_computedClipRule;
			}
			else
				m_computedClipRule = ClipRule_nonzero;
		}
		break;

	// stroke-linecap (SVG)
	case CSSProperty_stroke_linecap:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_stroke_linecap, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				CComBSTR cssText;
				cssprimitiveValue->getStringValue(&cssText);

				if (!tcscmp(cssText, OLESTR("round"))				m_computedStrokeLineCap = StrokeLineCap_round;
				else if (!tcscmp(cssText, OLESTR("square"))		m_computedStrokeLineCap = StrokeLineCap_square;
				else /*if (!tcscmp(cssText, OLESTR("butt"))*/	m_computedStrokeLineCap = StrokeLineCap_butt;
			}
			else if (value == 1)
			{
				m_computedStrokeLineCap = m_rparent->m_computedStrokeLineCap;
			}
			else
			{
				m_computedStrokeLineCap = StrokeLineCap_butt;
			}
		}
		break;

	// stroke-linejoin (SVG)
	case CSSProperty_stroke_linejoin:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_stroke_linejoin, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				CComBSTR cssText;
				cssprimitiveValue->getStringValue(&cssText);

				m_computedStrokeLineJoin = IdentNameToIndex(cssText, StrokeLineJoinIdents);
			}
			else if (value == 1)
			{
				m_computedStrokeLineJoin = m_rparent->m_computedStrokeLineJoin;
			}
			else
			{
				m_computedStrokeLineJoin = StrokeLineJoin_miter;
			}
		}
		break;

	// stroke-dasharray (SVG)
	case CSSProperty_stroke_dasharray:
		{
			m_strokeDashValuesArray.RemoveAll();

			CComQIPtr<CSSValueList> cssvalue;
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssvalue);
			if (value == 0)
			{
				long count;
				cssvalue->get_length(&count);

				for (int i = 0; i < count; i++)
				{
					CComPtr<ILCSSPrimitiveValue> nvalue;
					cssvalue->item(i, (CSSValue**)&nvalue);

					double fvalue;
					nvalue->getFloatValue(CSS_NUMBER, &fvalue);

					m_strokeDashValuesArray.Add(fvalue);
				}
			}
			else if (value == 1)
			{
				for (int i = 0; i < m_strokeDashValuesArray.GetSize(); i++)
				{
					double fvalue = m_rparent->m_strokeDashValuesArray[i];
					m_strokeDashValuesArray.Add(fvalue);
				}
			}
		}
		break;

		// stroke-dashoffset (SVG)
	case CSSProperty_stroke_dashoffset:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_stroke_dashoffset, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				cssprimitiveValue->getFloatValue(CSS_NUMBER, &m_computedStrokeDashOffset);
			// TODO %
			}
			else if (value == 1)
			{
				m_computedStrokeDashOffset = m_rparent->m_computedStrokeDashOffset;
			}
			else
			{
				m_computedStrokeDashOffset = 0;
			}
		}
		break;

	// pointer-events (SVG)
	case CSSProperty_pointer_events:
		{
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
			//	cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_pointer_events, bIncludeOverride);

				CComBSTR ident;
				cssprimitiveValue->getStringValue(&ident);

				m_computedPointerEvents = IdentNameToIndex(ident, PointerEventsIdents);
			}
			else if (value == 1)
			{
				m_computedPointerEvents = m_rparent->m_computedPointerEvents;
			}
			else
			{
				m_computedPointerEvents = PointerEvents_visiblePainted;
			}
		}
		break;
#endif

	// text-anchor (SVG)
	case CSSProperty_text_anchor:
		{
			CSSValue* cssprimitiveValue;
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				String ident = cssprimitiveValue->getStringValue();

				if (ident == "middle")			m_computedTextAnchor = TextAnchor_middle;
				else if (ident == "end")		m_computedTextAnchor = TextAnchor_end;
				else /*if (!tcscmp(ident, OLESTR("start"))*/	m_computedTextAnchor = TextAnchor_start;
			}
			else if (value == 1)	// inherit
			{
				ASSERT(m_rparent);
				m_computedTextAnchor = m_rparent->m_computedTextAnchor;
			}
			else	// initial
			{
				m_computedTextAnchor = TextAnchor_start;
			}
		}
		break;
#if 0
	// color-interpolation (SVG)
	case CSSProperty_color_interpolation:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_color_interpolation, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				CComBSTR cssText;
				cssprimitiveValue->getStringValue(&cssText);

				if (!tcscmp(cssText, OLESTR("sRGB"))		m_computedColorInterpolation = ColorInterpolation_sRGB;
				else m_computedColorInterpolation = ColorInterpolation_linearRGB;
			}
			else if (value == 1)
			{
				m_computedColorInterpolation = m_rparent->m_computedColorInterpolation;
			}
			else
			{
				m_computedColorInterpolation = ColorInterpolation_sRGB;
			}
		}
		break;

	// color-interpolation-filters (SVG)
	case CSSProperty_color_interpolation_filters:
		{
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
			//	cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_color_interpolation_filters, bIncludeOverride);

				CComBSTR cssText;
				cssprimitiveValue->getStringValue(&cssText);

				if (!tcscmp(cssText, OLESTR("sRGB"))		m_computedColorInterpolationFilters = ColorInterpolation_sRGB;
				else m_computedColorInterpolationFilters = ColorInterpolation_linearRGB;
			}
			else if (value == 1)
			{
				m_computedColorInterpolationFilters = m_rparent->m_computedColorInterpolationFilters;
			}
			else
			{
				m_computedColorInterpolationFilters = ColorInterpolation_linearRGB;
			}
		}
		break;
#endif

	// stop-color (SVG)
	case CSSProperty_stop_color:
		{
			SVGColor* svgcolor;
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&svgcolor);
			if (value == 0)
			{
				GetSVGColor(documentStyle, svgcolor, &m_computedStopColor);
			}
			else if (value == 1)
			{
				m_computedStopColor = m_rparent->m_computedStopColor;
			}
			else
			{
				m_computedStopColor.Empty();
				// black
				m_computedStopColor.m_type = SVG_COLORTYPE_RGBCOLOR;
				m_computedStopColor.m_rgbColor[0] = 0;
				m_computedStopColor.m_rgbColor[1] = 0;
				m_computedStopColor.m_rgbColor[2] = 0;
			}
		}
		break;

	// stop-opacity (SVG)
	case CSSProperty_stop_opacity:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedStopOpacity = cssprimitiveValue->getFloatValue(CSS_NUMBER);
			else if (value == 1)
				m_computedStopOpacity = m_rparent->m_computedStopOpacity;
			else
				m_computedStopOpacity = 1;
		}
		break;

#if 0
	case CSSProperty_solid_color:	// SVG
		{
			CComQIPtr<ILSVGColor> svgcolor;
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&svgcolor);
			if (value == 0)
			{
				GetSVGColor(documentStyle, svgcolor, &m_computedSolidColor);
			}
			else if (value == 1)
			{
				m_computedSolidColor = m_rparent->m_computedSolidColor;
			}
			else
			{
				m_computedSolidColor.Empty();
				// black
				m_computedSolidColor.m_type = SVG_COLORTYPE_RGBCOLOR;
				m_computedSolidColor.m_rgbColor[0] = 0;
				m_computedSolidColor.m_rgbColor[1] = 0;
				m_computedSolidColor.m_rgbColor[2] = 0;
			}

#if 0
			CComQIPtr<ILSVGColor> svgcolor = GetSpecifiedPropertyValue(documentStyle, CSSProperty_solid_color, bIncludeOverride);
		
			LSVGColorType colorType;
			svgcolor->get_colorType(&colorType);

			if (colorType == SVG_COLORTYPE_CURRENTCOLOR)
			{
				m_computedSolidColor[0] = m_computedColor.GetRed();
				m_computedSolidColor[1] = m_computedColor.GetGreen();
				m_computedSolidColor[2] = m_computedColor.GetBlue();
			}
			else
			{
				CComPtr<ILRGBColor> rgbColor;

				svgcolor->get_rgbColor(&rgbColor);

				CComPtr<ILCSSPrimitiveValue> red;
				rgbColor->get_red(&red);
				red->getFloatValue(CSS_NUMBER, &m_computedSolidColor[0]);

				CComPtr<ILCSSPrimitiveValue> green;
				rgbColor->get_green(&green);
				green->getFloatValue(CSS_NUMBER, &m_computedSolidColor[1]);

				CComPtr<ILCSSPrimitiveValue> blue;
				rgbColor->get_blue(&blue);
				blue->getFloatValue(CSS_NUMBER, &m_computedSolidColor[2]);
			}
#endif
		}
		break;

	// solid-opacity (SVG)
	case CSSProperty_solid_opacity:
		{
//			cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_solid_opacity, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
				cssprimitiveValue->getFloatValue(CSS_NUMBER, &m_computedSolidOpacity);
			else if (value == 1)
				m_computedSolidOpacity = m_rparent->m_computedSolidOpacity;
			else
				m_computedSolidOpacity = 1;
		}
		break;
#endif

	// lighting-color (SVG)
	case CSSProperty_lighting_color:
		{
			SVGColor* svgcolor;
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&svgcolor);
			if (value == 0)
			{
				GetSVGColor(documentStyle, svgcolor, &m_computedLightingColor);
			}
			else if (value == 1)
			{
				m_computedLightingColor = m_rparent->m_computedLightingColor;
			}
			else
			{
				// white
				m_computedLightingColor.m_type = SVG_COLORTYPE_RGBCOLOR;
				m_computedLightingColor.m_rgbColor[0] = 255;
				m_computedLightingColor.m_rgbColor[1] = 255;
				m_computedLightingColor.m_rgbColor[2] = 255;
			}
		}
		break;

		// flood-color (SVG)
	case CSSProperty_flood_color:
		{
			SVGColor* svgcolor;
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&svgcolor);
			if (value == 0)
			{
				GetSVGColor(documentStyle, svgcolor, &m_computedFloodColor);
			}
			else if (value == 1)
			{
				m_computedFloodColor = m_rparent->m_computedFloodColor;
			}
			else
			{
				m_computedFloodColor.Empty();
				// black
				m_computedFloodColor.m_type = SVG_COLORTYPE_RGBCOLOR;
				m_computedFloodColor.m_rgbColor[0] = 0;
				m_computedFloodColor.m_rgbColor[1] = 0;
				m_computedFloodColor.m_rgbColor[2] = 0;
			}
		}
		break;

	// flood-opacity (SVG)
	case CSSProperty_flood_opacity:
		{
			//cssprimitiveValue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_flood_opacity, bIncludeOverride);
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
				m_computedFloodOpacity = cssprimitiveValue->getFloatValue(CSS_NUMBER);
			else if (value == 1)
				m_computedFloodOpacity = m_rparent->m_computedFloodOpacity;
			else
				m_computedFloodOpacity = 1;
		}
		break;

	// stroke (SVG)
	case CSSProperty_stroke:
		{
			SVGPaint* svgpaint;
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&svgpaint);
			if (value == 0)
			{
				GetSVGPaint(documentStyle, svgpaint, &m_computedStroke);
			}
			else if (value == 1)
			{
				m_computedStroke = m_rparent->m_computedStroke;
			}
			else
			{
				m_computedStroke.Empty();
				m_computedStroke.m_type = SVG_PAINTTYPE_NONE;
			}
		}
		break;

	// fill (SVG)
	case CSSProperty_fill:
		{
			SVGPaint* svgpaint;
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&svgpaint);
			if (value == 0)
			{
				GetSVGPaint(documentStyle, svgpaint, &m_computedFill);
			}
			else if (value == 1)
			{
				m_computedFill = m_rparent->m_computedFill;
			}
			else
			{
				m_computedFill.Empty();
			// black
				m_computedFill.m_type = SVG_COLORTYPE_RGBCOLOR;
				m_computedFill.m_rgbColor[0] = 0;
				m_computedFill.m_rgbColor[1] = 0;
				m_computedFill.m_rgbColor[2] = 0;
			}
		}
		break;

	// filter (SVG)
	case CSSProperty_filter:
		{
			m_computedFilterUri = nullptr;

			CSSPrimitiveValue* cssvalue;
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssvalue);
			if (value == 0)
			{
				if (cssvalue->get_primitiveType() == CSS_URI)
				{
					m_computedFilterUri = cssvalue->getStringValue();
				}
			}
			else if (value == 1)
			{
				m_computedFilterUri = m_rparent->m_computedFilterUri;
			}
		}
		break;

#if 0
	// marker-start (SVG)
	case CSSProperty_marker_start:
		{
			m_computedMarkerStartUri.Empty();

//			CComQIPtr<ILCSSPrimitiveValue> cssvalue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_marker_start, bIncludeOverride);
			CComQIPtr<ILCSSPrimitiveValue> cssvalue;
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssvalue);
			if (value == 0)
			{
				CSSUnitType type;
				cssvalue->get_primitiveType(&type);
				if (type == CSS_URI)
				{
					cssvalue->getStringValue(&m_computedMarkerStartUri);
				}
			}
			else if (value == 1)
			{
				m_computedMarkerStartUri = m_rparent->m_computedMarkerStartUri;
			}
		}
		break;

	// marker-end (SVG)
	case CSSProperty_marker_end:
		{
			m_computedMarkerEndUri.Empty();

//			CComQIPtr<ILCSSPrimitiveValue> cssvalue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_marker_end, bIncludeOverride);
			CComQIPtr<ILCSSPrimitiveValue> cssvalue;
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssvalue);
			if (value == 0)
			{
				CSSUnitType type;
				cssvalue->get_primitiveType(&type);
				if (type == CSS_URI)
				{
					cssvalue->getStringValue(&m_computedMarkerEndUri);
				}
			}
			else if (value == 1)
			{
				m_computedMarkerEndUri = m_rparent->m_computedMarkerEndUri;
			}
		}
		break;

	// marker-mid (SVG)
	case CSSProperty_marker_mid:
		{
			m_computedMarkerMidUri.Empty();

//			CComQIPtr<ILCSSPrimitiveValue> cssvalue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_marker_mid, bIncludeOverride);
			CComQIPtr<ILCSSPrimitiveValue> cssvalue;
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssvalue);
			if (value == 0)
			{
				CSSUnitType type;
				cssvalue->get_primitiveType(&type);
				if (type == CSS_URI)
				{
					cssvalue->getStringValue(&m_computedMarkerMidUri);
				}
			}
			else if (value == 1)
			{
				m_computedMarkerMidUri = m_rparent->m_computedMarkerMidUri;
			}
		}
		break;

	// mask (SVG)
	case CSSProperty_mask:
		{
			m_computedMaskUri.Empty();

//			CComQIPtr<ILCSSPrimitiveValue> cssvalue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_mask, bIncludeOverride);
			CComQIPtr<ILCSSPrimitiveValue> cssvalue;
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssvalue);
			if (value == 0)
			{
				CSSUnitType type;
				cssvalue->get_primitiveType(&type);
				if (type == CSS_URI)
				{
					cssvalue->getStringValue(&m_computedMaskUri);
				}
			}
			else if (value == 1)
			{
				m_computedMaskUri = m_rparent->m_computedMaskUri;
			}
		}
		break;

	// clip-path (SVG)
	case CSSProperty_clip_path:
		{
			m_computedClipPathUri.Empty();

//			CComQIPtr<ILCSSPrimitiveValue> cssvalue = GetSpecifiedPropertyValue(documentStyle, CSSProperty_clip_path, bIncludeOverride);
			CComQIPtr<ILCSSPrimitiveValue> cssvalue;
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssvalue);
			if (value == 1)
			{
				CSSUnitType type;
				cssvalue->get_primitiveType(&type);
				if (type == CSS_URI)
				{
					cssvalue->getStringValue(&m_computedClipPathUri);
				}
			}
			else if (value == 1)
			{
				m_computedClipPathUri = m_rparent->m_computedClipPathUri;
			}
		}
		break;

	// color-profile
	case CSSProperty_color_profile:
		{
			CComQIPtr<ILCSSPrimitiveValue> cssvalue;// = GetSpecifiedPropertyValue(documentStyle, CSSProperty_color_profile, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				cssvalue->get_primitiveType(&m_computedColorProfileType);
				cssvalue->getStringValue(&m_computedColorProfileValue);
			}
			else if (value == 1)
			{
				m_computedColorProfileValue = m_rparent->m_computedColorProfileValue;
				m_computedColorProfileType = m_rparent->m_computedColorProfileType;
			}
			else
			{
				m_computedColorProfileValue = OLESTR("auto";
				m_computedColorProfileType = CSS_IDENT;
			}
		}
		break;

	case CSSProperty_text_shadow:
		{
			m_computedTextShadow.clear();

			CComQIPtr<CSSValueList> cssvalue;// = GetSpecifiedPropertyValue(documentStyle, CSSProperty_text_shadow, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssvalue);
			if (value == 0)
			{
				long nshadows;
				cssvalue->get_length(&nshadows);

				for (int i = 0; i < nshadows; i++)
				{
					CComPtr<CSSValueList> cssshadow;
					cssvalue->item(i, (CSSValue**)&cssshadow);

					long count;
					cssshadow->get_length(&count);

					if (count > 0)
					{
						CComPtr<ILCSSPrimitiveValue> nvalue;
						cssshadow->item(0, (CSSValue**)&nvalue);

						CSSUnitType unitType;
						nvalue->get_primitiveType(&unitType);

						if (unitType == CSS_RGBCOLOR || unitType == CSS_IDENT)
						{
							if (count >= 3)
							{
								CShadow shadow;
								shadow.m_color = GetComputedColorValue(nvalue);

								CComPtr<ILCSSPrimitiveValue> offset0;
								cssshadow->item(1, (CSSValue**)&offset0);
								offset0->getFloatValue(CSS_NUMBER, &shadow.m_offset[0]);

								CComPtr<ILCSSPrimitiveValue> offset1;
								cssshadow->item(2, (CSSValue**)&offset1);
								offset1->getFloatValue(CSS_NUMBER, &shadow.m_offset[1]);

								if (count >= 4)
								{
									CComPtr<ILCSSPrimitiveValue> radius;
									cssshadow->item(3, (CSSValue**)&radius);
									radius->getFloatValue(CSS_NUMBER, &shadow.m_blurRadius);
								}
								else
									shadow.m_blurRadius = 0;

								m_computedTextShadow.push_back(shadow);
							}
						}
						else
						{
							ASSERT(0);
						}
					}
				}
			}
			else if (value == 1)
			{
				for (int i = 0; i < m_rparent->m_computedTextShadow.size(); i++)
				{
					m_computedTextShadow.push_back(m_rparent->m_computedTextShadow[i]);
				}
			}
		}
		break;

	case CSSProperty_box_shadow:
		{
			m_computedBoxShadow.clear();

			CComQIPtr<CSSValueList> cssvalue;// = GetSpecifiedPropertyValue(documentStyle, CSSProperty_box_shadow, bIncludeOverride);
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssvalue);
			if (value == 0)
			{
				long nshadows;
				cssvalue->get_length(&nshadows);

				for (int i = 0; i < nshadows; i++)
				{
					CComPtr<CSSValueList> cssshadow;
					cssvalue->item(i, (CSSValue**)&cssshadow);

					long count;
					cssshadow->get_length(&count);

					// TODO, better error-checking

					if (count >= 2)
					{
						CShadow shadow;
						shadow.m_blurRadius = 0;
						shadow.m_color = m_computedColor;

						CComPtr<ILCSSPrimitiveValue> offset0;
						cssshadow->item(0, (CSSValue**)&offset0);
						offset0->getFloatValue(CSS_NUMBER, &shadow.m_offset[0]);

						CComPtr<ILCSSPrimitiveValue> offset1;
						cssshadow->item(1, (CSSValue**)&offset1);
						offset1->getFloatValue(CSS_NUMBER, &shadow.m_offset[1]);

						if (count >= 3)
						{
							CSSUnitType unitType;
							CComPtr<ILCSSPrimitiveValue> prim;
							cssshadow->item(2, (CSSValue**)&prim);

							prim->get_primitiveType(&unitType);
							if (unitType == CSS_RGBCOLOR)
							{
								shadow.m_color = GetComputedColorValue(prim);
							}
							else
							{
								prim->getFloatValue(CSS_NUMBER, &shadow.m_blurRadius);

								if (count >= 4)
								{
									CComPtr<ILCSSPrimitiveValue> color;
									cssshadow->item(3, (CSSValue**)&color);

									shadow.m_color = GetComputedColorValue(color);
								}
							}
						}

						m_computedBoxShadow.push_back(shadow);
					}
				}
			}
			else if (value == 1)
			{
				for (int i = 0; i < m_rparent->m_computedBoxShadow.size(); i++)
				{
					m_computedBoxShadow.push_back(m_rparent->m_computedBoxShadow[i]);
				}
			}
		}
		break;

	case CSSProperty_box_orient:
		{
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				CComBSTR cssText;
				cssprimitiveValue->getStringValue(&cssText);

				m_computedBoxOrient = IdentNameToIndex(cssText, BoxOrientIdents);
			}
			else if (value == 1)
			{
				m_computedBoxOrient = m_rparent->m_computedBoxOrient;
			}
			else
				m_computedBoxOrient = BoxOrient_inline_axis;
		}
		break;

	case CSSProperty_box_align:
		{
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
			{
				CComBSTR ident;
				cssprimitiveValue->getStringValue(&ident);

				m_computedBoxAlign = IdentNameToIndex(ident, BoxAlignIdents);
			}
			else if (value == 1)
			{
				m_computedBoxAlign = m_rparent->m_computedBoxAlign;
			}
			else
			{
				m_computedBoxAlign = BoxAlign_stretch;
			}
		}
		break;

	case CSSProperty_box_flex:
		{
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, (CSSValue**)&cssprimitiveValue);
			if (value == 0)
				cssprimitiveValue->getFloatValue(CSS_NUMBER, &m_computedBoxFlex);
			else if (value == 1)
				m_computedBoxFlex = m_rparent->m_computedBoxFlex;
			else
				m_computedBoxFlex = 0;
		}
		break;

	case CSSProperty_content:
		{
			CComPtr<CSSValue> cssvalue;
			int value = m_pWindow->GetSpecifiedPropertyValue2(documentStyle, m_declMatches, propertyIndex, bIncludeOverride, &cssvalue);

			m_computedContent.Empty();

			if (value == 0)
			{
				CComQIPtr<CSSValueList> cssvalueList = cssvalue;
				ASSERT(cssvalueList);

				if (!tcscmp(m_pseudoElementName, OLESTR("marker"))
				{
					CComBSTR cssText;
					cssvalue->get_cssText(&cssText);

				// 6. List Content: Generating the computed value of the 'content' property

				// If a ::marker pseudo-element has its 'content' property set to normal,
				// the following algorithm should be used to generate the computed value of
				// the property

					if (!tcsicmp(cssText, OLESTR("normaOLESTR("))
					{
						// If 'list-style-image' is not 'none', and if the image is valid, then the content is the value of the 'list-style-image' property. 

						//if (m_computedListStyleImage
						if (FALSE)
						{
						}
						else
						// Otherwise, if the list-style-type property is not 'none', then the
						// computed value of the 'content' property is
						// counter(list-item, <list-style-type>) followed by a string,
						// where <list-style-type> is the computed value of the 'list-style-type'
						// property, or the default style type for the list-item counter if the
						// 'list-style-type' has the value 'normal', and the string is the suffix
						// for the list style type in question (which may be empty). 
						if (m_computedListStyleType != ListStyleType_none)
						{
						}
						else
						// Otherwise the computed value is inhibit. (Note: This is not the same as the empty string, nor the same as none.) 
						{
							ASSERT(0);
						}
						break;
					}
				}

				std::wstring string;

				long count;
				cssvalueList->get_length(&count);

				for (int i = 0; i < count; i++)
				{
					CComPtr<ILCSSPrimitiveValue> nvalue;
					cssvalueList->item(i, (CSSValue**)&nvalue);

					CSSUnitType primitiveType;
					nvalue->get_primitiveType(&primitiveType);

					if (primitiveType == CSS_STRING)
					{
						CComBSTR s;
						nvalue->getStringValue(&s);

						string += s;
					}
					else if (primitiveType == CSS_ATTR)
					{
						// TODO
						ASSERT(0);
					}
					else if (primitiveType == CSS_COUNTER)
					{
						CComQIPtr<ILCSSCounter> csscounter;
						nvalue->getCounterValue(&csscounter);

						CComBSTR identifier;
						csscounter->get_identifier(&identifier);

						CComBSTR listStyleStr;
						csscounter->get_listStyle(&listStyleStr);

						CComBSTR separator;
						csscounter->get_separator(&separator);

						if (separator.Length())	// counters
						{
							ASSERT(0);
						}
						else	// counter
						{
							WORD listStyle;

							if (listStyleStr.Length())
							{
								listStyle = IdentNameToIndex(listStyleStr, ListStyleTypeIdents);
								ASSERT(listStyle >= 0);	// TODO remove
							}
							else
								listStyle = ListStyleType_decimal;	// ??? default

							CCounter* pCounter = pCSSContext->GetCounter(identifier);
							ASSERT(pCounter);	// TODO remove
							if (pCounter)
							{
								ASSERT(0);
#if 0
								__int64 value = pCounter->m_value.back();

								switch (listStyle)
								{
								// glyph
								case ListStyleType_box:		string += (OLECHAR)0x25A1; break;
								case ListStyleType_circle:	string += (OLECHAR)0x25E6; break;
								case ListStyleType_disc:	string += (OLECHAR)0x2022; break;
								case ListStyleType_hyphen:	string += (OLECHAR)0x2013; break;
								case ListStyleType_square:	string += (OLECHAR)0x25A0; break;

								// symbolic
								case ListStyleType_asterisks:
									{
										for (int i = 0; i < value; i++)
											string += L'*';
									}
									break;

								case ListStyleType_footnotes:
									{
										// TODO
										ASSERT(0);
									}
									break;

								case ListStyleType_lower_roman:
								case ListStyleType_upper_roman:
									{
										// Zero and negative numbers are rendered using the decimal numbering style
										if (value <= 0)
										{
											if (value < 0)
												string += OLESTR("-";

											OLECHAR str[64];
											wltoa(str, -value, 10, 0, decimal_characters);

											string += str;
										}
										else
										{
											if (value <= 1000)
											{
												if (value == 1000)
												{
													string += 0x216F;
													// skip to the end
												}
												else
												{
													if (value >= 900)
													{
														string += 0x216D;
														string += 0x216F;
														value -= 900;
													}
													else if (value >= 500)
													{
														string += 0x216E;
														value -= 500;
													}
													else if (value >= 400)
													{
														string += 0x216D;
														string += 0x216E;
														value -= 400;
													}

													while (value >= 100)
													{
														string += 0x216D;
														value -= 100;
													}

													if (value >= 90)
													{
														string += 0x2169;
														string += 0x216D;
														value -= 90;
													}
													else if (value >= 50)
													{
														string += 0x216C;
														value -= 50;
													}
													else if (value >= 40)
													{
														string += 0x2169;
														string += 0x216C;
														value -= 40;
													}

													while (value > 12)
													{
														string += 0x2169;
														value -= 10;
													}

													if (value > 0)
													{
														string += upper_roman_characters[value-1];
													}
												}
											}
											else
											{
												ASSERT(0);
											}
										}
									}
									break;

								// alphabetic
								case ListStyleType_afar:
								case ListStyleType_amharic:
								case ListStyleType_amharic_abegede:
								case ListStyleType_cjk_earthly_branch:
								case ListStyleType_cjk_heavenly_stem:
								case ListStyleType_ethiopic:
								case ListStyleType_ethiopic_abegede:
								case ListStyleType_ethiopic_abegede_am_et:
								case ListStyleType_ethiopic_abegede_gez:
								case ListStyleType_ethiopic_abegede_ti_er:
								case ListStyleType_ethiopic_abegede_ti_et:
								case ListStyleType_ethiopic_halehame_aa_er:
								case ListStyleType_ethiopic_halehame_aa_et:
								case ListStyleType_ethiopic_halehame_am_et:
								case ListStyleType_ethiopic_halehame_gez:
								case ListStyleType_ethiopic_halehame_om_et:
								case ListStyleType_ethiopic_halehame_sid_et:
								case ListStyleType_ethiopic_halehame_so_et:
								case ListStyleType_ethiopic_halehame_ti_er:
								case ListStyleType_ethiopic_halehame_ti_et:
								case ListStyleType_ethiopic_halehame_tig:
								case ListStyleType_hangul:
								case ListStyleType_hangul_consonant:
								case ListStyleType_hiragana:
								case ListStyleType_hiragana_iroha:
								case ListStyleType_katakana:
								case ListStyleType_katakana_iroha:
								case ListStyleType_lower_alpha:
								case ListStyleType_lower_greek:
								case ListStyleType_lower_norwegian:
								case ListStyleType_lower_latin:
								case ListStyleType_oromo:
								case ListStyleType_sidama:
								case ListStyleType_somali:
								case ListStyleType_tigre:
								case ListStyleType_tigrinya_er:
								case ListStyleType_tigrinya_er_abegede:
								case ListStyleType_tigrinya_et:
								case ListStyleType_tigrinya_et_abegede:
								case ListStyleType_upper_alpha:
								case ListStyleType_upper_greek:
								case ListStyleType_upper_norwegian:
								case ListStyleType_upper_latin:

								// numeric
								case ListStyleType_binary:
								case ListStyleType_octal:
								case ListStyleType_decimal:
								case ListStyleType_lower_hexadecimal:
								case ListStyleType_upper_hexadecimal:
									{
										int base;
										int start;
										OLECHAR* characters;

										switch (listStyle)
										{
											case ListStyleType_binary:
												{
													start = 0;
													base = 2;
													characters = OLESTR("01";
												}
												break;

											case ListStyleType_octal:
												{
													start = 0;
													base = 8;
													characters = OLESTR("01234567";
												}
												break;

											case ListStyleType_decimal:
												{
													start = 0;
													base = 10;
													characters = decimal_characters;
												}
												break;

											case ListStyleType_lower_hexadecimal:
												{
													start = 0;
													base = 16;
													characters = OLESTR("0123456789abcdef";
												}
												break;

											case ListStyleType_upper_hexadecimal:
												{
													start = 0;
													base = 16;
													characters = OLESTR("0123456789ABCDEF";
												}
												break;

											case ListStyleType_lower_latin:
											case ListStyleType_lower_norwegian:
												{
													start = 1;
													base = (listStyle == ListStyleType_lower_latin)? 26: 29;
													characters = OLESTR("abcdefghijklmnopqrstuvwxyzæøå";
												}
												break;

											case ListStyleType_upper_latin:
											case ListStyleType_upper_norwegian:
												{
													start = 1;
													base = (listStyle == ListStyleType_upper_latin)? 26: 29;
													characters = OLESTR("ABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅ";
												}
												break;

											case ListStyleType_lower_greek:
												{
													OLECHAR lower_greek[] =
													{
														0x03B1, 0x03B2, 0x03B3, 0x03B4, 0x03B5, 0x03B6, 0x03B7, 0x03B8, 0x03B9, 0x03BA, 0x03BB, 0x03BC, 0x03BD, 0x03BE, 0x03BF, 0x03C0, 0x03C1, 0x03C3, 0x03C4, 0x03C5, 0x03C6, 0x03C7
													};

													start = 1;
													base = 24;
													characters = lower_greek;
												}
												break;

											case ListStyleType_upper_greek:
												{
													OLECHAR upper_greek[] =
													{
														0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D, 0x039E, 0x039F, 0x03A0, 0x03A1, 0x03A3, 0x03A9
													};

													start = 1;
													base = 24;
													characters = upper_greek;
												}
												break;

											default:
												ASSERT(0);
										}

										OLECHAR str[64];
										wltoa(str, value, base, start, characters);

										string += str;
									}
									break;

								default:
									ASSERT(0);
								}
#endif
							}
						}
					}
				}

				m_computedContent = string.c_str();
			}
			else if (value == 1)
			{
				// ???
				ASSERT(m_rparent);
				m_computedContent = m_rparent->m_computedContent;
			}
			else
			{
				// inhibit
			}
		}
		break;

	case CSSProperty_behavior:
		{
#if 0	// TODO
			m_behaviors.RemoveAll();	// TODO, free

//			CComQIPtr<CLSVGShadowableImpl> shadowable(m_pNode);
//			if (shadowable)
			{
				/*
				if (shadowable->m_shadowElement)
				{
					shadowable->m_shadowElement->Release();
					shadowable->m_shadowElement = NULL;
				}
				*/

				if (m_bindNode)
				{
					m_bindNode->Release();
					m_bindNode = NULL;
				}

				CComQIPtr<CSSValueList> cssvalue = GetSpecifiedPropertyValue(documentStyle, propertyIndex, bIncludeOverride);

				long count;
				cssvalue->get_length(&count);

				for (int i = 0; i < count; i++)
				{
					CComPtr<ILCSSPrimitiveValue> nvalue;
					cssvalue->item(i, (CSSValue**)&nvalue);

					if (static_cast<CSSPrimitiveValue*>(nvalue.p)->m_urlDocument == NULL)
					{
						CComBSTR uri;
						nvalue->getStringValue(&uri);

						TCHAR result[2048];
						{
							CComBSTR documentUrl;
							m_pView->m_document->get_url(&documentUrl);

							_bstr_t baseUrl = documentUrl;

							DWORD resultLen = sizeof(result);
							InternetCombineUrl(baseUrl, W2A(uri), result, &resultLen, 0);
						}

						static_cast<CSSPrimitiveValue*>(nvalue.p)->m_urlDocument.CoCreateInstance(CLSID_LHTMLDocument);

						bool success;
						static_cast<CSSPrimitiveValue*>(nvalue.p)->m_urlDocument->load(_variant_t(result), &success);

						ASSERT(success);

						if (TRUE)
						{
							CComPtr<ILDOMDocument> document = static_cast<CSSPrimitiveValue*>(nvalue.p)->m_urlDocument;
							//componentElement->get_ownerDocument(&document);

							CScriptSite* pScriptSite = CComQIPtr<CLDOMDocumentImplImpl>(document.p)->m_pScriptSite;
							CComQIPtr<IActiveScriptParseProcedure> activeScriptParseProcedure = pScriptSite->m_activeScript;

							HRESULT hr;

							// Start running scripts
							hr = pScriptSite->m_activeScript->SetScriptState(SCRIPTSTATE_STARTED);
							ASSERT(SUCCEEDED(hr));

						// force the engine to connect any outbound interfaces to the 
						// host's objects
							hr = pScriptSite->m_activeScript->SetScriptState(SCRIPTSTATE_CONNECTED);
							ASSERT(SUCCEEDED(hr));
						}
					}

					if (static_cast<CSSPrimitiveValue*>(nvalue.p)->m_urlDocument)
					{
						CPBehavior* pBehavior = new CPBehavior;

						CComPtr<ILDOMElement> componentElement;
						static_cast<CSSPrimitiveValue*>(nvalue.p)->m_urlDocument->get_documentElement(&componentElement);
						ASSERT(componentElement);
						if (componentElement)
						{
							pBehavior->m_elementDef = componentElement;
							m_behaviors.Add(pBehavior);	// hmm.. should probably do after, but that crached
							BindBehavior(componentElement);

	#if 0
							ASSERT(m_shadowTree == NULL);
							CComObject<CPHTMElement>::CreateInstance(&m_shadowTree);
							m_shadowTree->AddRef();
							m_shadowTree->m_pView = m_pView;
							m_shadowTree->m_pNode = shadowable->m_shadowElement;
							CComQIPtr<CLDOMNodeImplImpl>(m_shadowTree->m_pNode)->m_pNodes.Add(m_shadowTree);
							m_shadowTree->m_parent = this;
							m_shadowTree->BuildChildren();
	#endif
						}
					}
				}
			}
#endif
		}
		break;
#endif

	case CSSProperty_wrap_option:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				String ident = cssprimitiveValue->getStringValue();
				m_computedWrapOption = IdentNameToIndex(ident, WrapOptionIdents);
			}
			else if (value == 1)
			{
				m_computedWrapOption = m_rparent->m_computedWrapOption;
			}
			else
			{
				m_computedWrapOption = WrapOption_wrap;
			}
		}
		break;

	case CSSProperty_all_space_treatment:
		{
			m_computedAllSpaceTreatment = AllSpaceTreatment_collapse;
		}
		break;

	case CSSProperty_white_space_treatment:
		{
			m_computedWhiteSpaceTreatment = WhiteSpaceTreatment_ignore_if_surrounding_linefeed;
		}
		break;

	case CSSProperty_linefeed_treatment:
		{
			int value = m_declMatches->GetSpecifiedPropertyValue2(pProperty, bIncludeOverride, (Object**)&cssprimitiveValue);
			if (value == 0)
			{
				String ident = cssprimitiveValue->getStringValue();
				m_computedLineFeedTreatment = IdentNameToIndex(ident, LineFeedTreatmentIdents);
			}
			else if (value == 1)
			{
				m_computedLineFeedTreatment = m_rparent->m_computedLineFeedTreatment;
			}
			else
			{
				m_computedLineFeedTreatment = LineFeedTreatment_auto;
			}
		}
		break;

	default:
		;//ASSERT(0);
	}
}

void PElementBase::CalculateComputedCSSProperty(CSSContext* pCSSContext, int propertyIndex, bool bIncludeOverride)
{
	// Check if property is already computed. If not, compute it
//	if (!m_PropertyValid.TestBit(propertyIndex))
	{
		CalculateComputedCSSPropertyCore(pCSSContext, propertyIndex, bIncludeOverride);
//		m_PropertyValid.SetBit(propertyIndex, true);
	}
}

void PElementBase::GetCSSProperties2(CSSContext* pCSSContext)
{
	for (int i = 0; i < m_computedFont.GetSize(); i++)
	{
		m_computedFont[i]->Release();
	}
	m_computedFont.RemoveAll();

	if (m_shadowTree)
	{
		m_shadowTree->RemoveBoxesAndChildren();
//		m_shadowTree->Release();
		m_shadowTree = NULL;
	}

	// auto
	m_computedWidth = -1;
	m_computedHeight = -1;

// Set some default values here ??
	m_computedBorderRadius[0][0] = 0;
	m_computedBorderRadius[0][1] = 0;
	m_computedBorderRadius[1][0] = 0;
	m_computedBorderRadius[1][1] = 0;
	m_computedBorderRadius[2][0] = 0;
	m_computedBorderRadius[2][1] = 0;
	m_computedBorderRadius[3][0] = 0;
	m_computedBorderRadius[3][1] = 0;

// TODO...
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_behavior);
//	BuildRenderChildrenInternal();

// The order in which these are called is important for some properties

	CalculateComputedCSSProperty(pCSSContext, CSSProperty_display_model);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_display_role);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_visibility);

	CalculateComputedCSSProperty(pCSSContext, CSSProperty_counter_increment);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_counter_reset);

	CalculateComputedCSSProperty(pCSSContext, CSSProperty_list_style_type);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_list_style_position);

	CalculateComputedCSSProperty(pCSSContext, CSSProperty_font_size);	// It's important that 'font-size' is before any other lenght properties
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_font_style);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_font_weight);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_font_family);

	CalculateComputedCSSProperty(pCSSContext, CSSProperty_cursor);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_opacity);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_position);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_float);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_clear);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_line_height);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_color);	// It's important that 'color' is before any other colors
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_background_color);

	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_left_color);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_top_color);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_right_color);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_bottom_color);

	CalculateComputedCSSProperty(pCSSContext, CSSProperty_text_underline_color);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_text_overline_color);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_text_line_through_color);

	CalculateComputedCSSProperty(pCSSContext, CSSProperty_text_underline_style);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_text_overline_style);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_text_line_through_style);

	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_left_style);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_top_style);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_right_style);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_bottom_style);

	/*
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_left_width);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_top_width);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_right_width);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_bottom_width);
	*/

	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_top_left_radius);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_top_right_radius);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_bottom_left_radius);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_bottom_right_radius);

	/*
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_left);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_top);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_right);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_padding_bottom);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_left);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_top);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_right);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_margin_bottom);
	*/
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_outline_style);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_outline_width);
	/*
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_width);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_height);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_left);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_right);
	*/
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_top);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_overflow);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_clip);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_text_align);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_background_image);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_background_repeat);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_z_index);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_collapse);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_border_spacing);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_empty_cells);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_enable_background);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_stroke_width);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_stroke_miterlimit);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_fill_opacity);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_stroke_opacity);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_fill_rule);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_clip_rule);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_stroke_linecap);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_stroke_linejoin);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_stroke_dasharray);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_stroke_dashoffset);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_pointer_events);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_text_anchor);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_color_interpolation);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_color_interpolation_filters);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_shape_rendering);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_image_rendering);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_stop_color);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_stop_opacity);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_solid_color);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_solid_opacity);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_lighting_color);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_flood_color);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_flood_opacity);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_stroke);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_fill);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_filter);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_marker_start);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_marker_end);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_marker_mid);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_mask);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_clip_path);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_color_profile);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_text_shadow);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_box_shadow);

	CalculateComputedCSSProperty(pCSSContext, CSSProperty_wrap_option);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_white_space_treatment);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_all_space_treatment);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty_linefeed_treatment);

	CalculateComputedCSSProperty(pCSSContext, CSSProperty__box_orient);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty__box_align);
	CalculateComputedCSSProperty(pCSSContext, CSSProperty__box_flex);

//	ASSERT(0);
#if 0	// Had this ?
	{
		for (int i = 0; i < m_computedCounterReset.size(); i++)
		{
			CCounter* pCounter = pCSSContext->GetCounter(m_computedCounterReset[i]->m_identifier.c_str());
			m_counters.push_back(pCounter);
			pCounter->m_value.push_back(m_computedCounterReset[i]->m_number);
		}
	}

	{
		for (int i = 0; i < m_computedCounterIncrement.size(); i++)
		{
			CCounter* pCounter = pCSSContext->GetCounter(m_computedCounterIncrement[i]->m_identifier);
			pCounter->m_value.back() += m_computedCounterIncrement[i]->m_number;

//			int* it = pCounter->m_value.end();
//			*it = *it + m_computedCounterIncrement[i]->m_number;///push_back(m_computedCounterReset[i].m_number);
		}
	}
#endif

	CalculateComputedCSSProperty(pCSSContext, CSSProperty_content);

//	ASSERT(0);
#if 0		// Had this ?
// Set override style to computed style
	for (int i = 0; i < m_pOverrideStyle->m_decls.GetSize(); i++)
	{
		CSSDecl* pdecl = m_pOverrideStyle->m_decls[i];

		CSSValue* cssvalue = GetCachedComputedProperty(pdecl->m_propertyIndex);

		ASSERT(cssvalue != NULL);

		CComBSTR cssText;
		cssvalue->get_cssText(&cssText);

		*pdecl->m_pValue = cssText;
	}
#endif

#if 0	// TODO, had this
	CComQIPtr<ILSMILAnimationTarget> animationTarget = m_pNode;
	if (animationTarget)
	{
		CAnimationTarget* pAnimationTarget = static_cast<CAnimationTarget*>(animationTarget.p);

		UPOSITION pos = pAnimationTarget->m_animationList.GetHeadPosition();
		while (pos)
		{
			AnimationElementImplImpl* pAnimation = (AnimationElementImplImpl*)pAnimationTarget->m_animationList.GetNext(pos);

			CComQIPtr<ILDOMElement> animationElement = pAnimation;

			//if (pAnimation->m_animatedAttr == NULL)	// It's a CSS property
			{
				CPAnimationElementImpl* pPAnimation = (CPAnimationElementImpl*)CComQIPtr<CLDOMElementImplImpl>(animationElement)->GetNodeOnFrame(m_pView);

				if (pPAnimation)
				{
					if (pPAnimation->m_pAnimatedCSSAttr)
					{
						pAnimation->DoAnimationForElement(pPAnimation->m_pAnimatedCSSAttr);

					// cascade again, with the override property
						CalculateComputedCSSProperty(pCSSContext, ((CCSSPropertyType*)pAnimation->m_pAttributeType)->m_propertyIndex, TRUE);
					}
				}
			}
		}
	}
#endif

	/*

  Fix up some of the properties

	CSS2,box model

	9.7 Relationships between 'display', 'position', and 'float'
	The three properties that affect box generation and layout -- 'display', 'position', and 'float' -- interact as follows:

	If 'display' has the value 'none', user agents must ignore 'position' and 'float'. In this case, the element generates no box. 
	Otherwise, 'position' has the value 'absolute' or 'fixed', 'display' is set to 'block' and 'float' is set to 'none'. The position of the box will be determined by the 'top', 'right', 'bottom' and 'left' properties and the box's containing block. 
	Otherwise, if 'float' has a value other than 'none', 'display' is set to 'block' and the box is floated. 
	Otherwise, the remaining 'display' properties apply as specified.
	*/
	if (m_computedPosition == Position_absolute ||
		m_computedPosition == Position_fixed)
	{
#if 0
		m_computedDisplay = Display_block;
#endif
		m_computedDisplayRole = DisplayRole_block;
		m_computedFloat = Float_none;
	}
	else if (m_computedFloat != Float_none)
	{
		if (m_computedDisplayRole != DisplayRole_none)
		{
	#if 0
			m_computedDisplay = Display_block;
	#endif
			m_computedDisplayRole = DisplayRole_block;
		}
	}

	if (m_shadowTree)
	{
		ASSERT(m_shadowTree->m_parent == this);
		//PElementBase* oldparent = m_shadowTree->m_parent;
		//ILDOMNode* oldnode = m_shadowTree->m_pNode;

		//m_shadowTree->m_pNode = m_pNode;
		//m_shadowTree->m_parent = m_parent;
		//m_shadowTree->GetCSSPropertiesAndChildren();

		//m_shadowTree->m_pNode = oldnode;
		//m_shadowTree->m_parent = oldparent;

		//m_shadowTree->CalculateBoundsAndChildren();

#if 0
	// All this isn't really tested out
		m_shadowTree->GetCSSProperties();
		m_shadowTree->m_computedBackgroundColor = m_computedBackgroundColor;
		m_shadowTree->m_computedDisplay = m_computedDisplay;

		UPOSITION pos = m_shadowTree->m_childList.GetHeadPosition();
		while (pos)
		{
			PElementBase* pElement = (PElementBase*)m_shadowTree->m_childList.GetNext(pos);
			if (pElement->m_type == NODE_ELEMENT)
			{
				pElement->GetCSSPropertiesAndChildren();
			}
		}

		m_shadowTree->BuildRenderChildren();
		m_shadowTree->CalculateBoundsAndChildren();
		// What about recalculateparentbounds?
#endif
	}
}

//virtual
void PElementBase::GetCSSProperties(CSSContext* pCSSContext)
{
#if 0
	CComQIPtr<ILDOMDocument> document = m_pView->m_document;
	ASSERT(document);
#endif

	if (!m_bArrangeValid)
	{
		m_childList.RemoveAll();
		if (m_pNode)
		{
			for (int i = 0; i < m_pNode->m_childNodes->m_items.size(); i++)
			{
				ChildNode* node = m_pNode->m_childNodes->m_items[i];
				if (node->get_nodeType() == NODE_ELEMENT || node->get_nodeType() == NODE_TEXT)
				{
					node->m_pNode->m_parent = this;
					node->m_pNode->m_rparent = this;
					m_childList.Add(m_pNode->m_childNodes->m_items[i]->m_pNode);
				}
			}
		}
	}

	if (!m_bCSSPropertiesValid)
	{

		// Get all stylerule declarations that matches this element
		if (m_declMatches == NULL)
		{
			Style::IDocumentStyle* documentStyle = dynamic_cast<Style::IDocumentStyle*>(m_pNode->m_ownerDocument);
			ASSERT(documentStyle);

		//	ViewCSS* m_pWindow = NULL;

			m_declMatches = Style::ViewCSS::GetDeclMatches(documentStyle, this);
		}

		/*
		if (m_pseudoElementName.Length() && m_declMatches.GetSize() > 0)
		{
		}
		*/

		GetCSSProperties2(pCSSContext);
		m_bCSSPropertiesValid = true;
	}

//	m_pBeforePseudoElement = NULL;

#if 0
	if (m_pseudoElementName.Length() == 0)	// Don't do more than one level (yet?)
	{
		CComObject<CPseudoElement>* pElement;
		CComObject<CPseudoElement>::CreateInstance(&pElement);
		pElement->AddRef();
		pElement->m_pNode = m_pNode;	// ??
		pElement->m_pView = m_pView;
		pElement->m_pseudoElementName = OLESTR("before";
		pElement->m_parent = this;
		pElement->m_rparent = this;

		pElement->GetCSSProperties(pCSSContext);

		if ((BSTR)pElement->m_computedContent != NULL)
		{
			m_pBeforePseudoElement = pElement;

			CComPtr<ILDOMText> textNode;
			document->createTextNode(pElement->m_computedContent, &textNode);

			CComObject<PText>* pText;
			CComObject<PText>::CreateInstance(&pText);
			pText->AddRef();
			pText->m_pNode = textNode;
			pText->m_pNode->AddRef();

			pText->m_parent = pElement;
			pText->m_rparent = pElement;
			pElement->m_childList.AddTail(pText);
			pElement->m_rchildList.AddTail(pText);

			pText->BuildWords();
		}

		if (m_computedDisplayRole == DisplayRole_list_item)
		{
			CComObject<CPseudoElement>* pElement;
			CComObject<CPseudoElement>::CreateInstance(&pElement);
			pElement->AddRef();
			pElement->m_pNode = m_pNode;	// ??
			pElement->m_pView = m_pView;
			pElement->m_pseudoElementName = OLESTR("marker";
			pElement->m_parent = this;
			pElement->m_rparent = this;

			pElement->GetCSSProperties(pCSSContext);

			if (pElement->m_computedContent != NULL)
			{
				m_pMarkerPseudoElement = pElement;

				CComPtr<ILDOMText> textNode;
				document->createTextNode(pElement->m_computedContent, &textNode);

				CComObject<PText>* pText;
				CComObject<PText>::CreateInstance(&pText);
				pText->AddRef();
				pText->m_pNode = textNode;
				pText->m_pNode->AddRef();

#if 0
				pText->m_parent = pElement;
				pText->m_rparent = pElement;
				pElement->m_childList.AddTail(pText);
				pElement->m_rchildList.AddTail(pText);
#endif

				pText->BuildWords();
			}
		}
	}
#endif

	// Now m_rchildList (the second list) is completely built
	BuildRenderableChildren();	// Overridden, if a third list is to be built, svg does this
}

// virtual
CSSValue* PElementBase::GetCachedComputedProperty(int propertyIndex)
{
	CSSValue* value = NULL;

	ASSERT(0);

#if 0
	switch (propertyIndex)
	{
		case CSSProperty_color_profile:
			{
				value = CreateCSSUnitStringValue(propertyIndex, m_computedColorProfileType, m_computedColorProfileValue.c_str());
			}
			break;

		case CSSProperty_display_model:
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, DisplayModelIdents[m_computedDisplayModel]);
			}
			break;

		case CSSProperty_display_role:
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, DisplayRoleIdents[m_computedDisplayRole]);
			}
			break;

		case CSSProperty_background_image:
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_URI, m_computedBackgroundImage);
			}
			break;

		case CSSProperty_filter:	// SVG
			{
				if (m_computedFilterUri.Length())
					value = CreateCSSUnitStringValue(propertyIndex, CSS_URI, m_computedFilterUri);
				else
					value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, OLESTR("none");
			}
			break;

		case CSSProperty_mask:	// SVG
			{
				if (m_computedMaskUri.Length())
					value = CreateCSSUnitStringValue(propertyIndex, CSS_URI, m_computedMaskUri);
				else
					value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, OLESTR("none");
			}
			break;

		case CSSProperty_clip_path:	// SVG
			{
				if (m_computedClipPathUri.Length())
					value = CreateCSSUnitStringValue(propertyIndex, CSS_URI, m_computedClipPathUri);
				else
					value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, OLESTR("none");
			}
			break;

		case CSSProperty_marker_start:	// SVG
			{
				if (m_computedMarkerStartUri.Length())
					value = CreateCSSUnitStringValue(propertyIndex, CSS_URI, m_computedMarkerStartUri);
				else
					value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, OLESTR("none");
			}
			break;

		case CSSProperty_marker_end:	// SVG
			{
				if (m_computedMarkerEndUri.Length())
					value = CreateCSSUnitStringValue(propertyIndex, CSS_URI, m_computedMarkerEndUri);
				else
					value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, OLESTR("none");
			}
			break;

		case CSSProperty_marker_mid:	// SVG
			{
				if (m_computedMarkerMidUri.Length())
					value = CreateCSSUnitStringValue(propertyIndex, CSS_URI, m_computedMarkerMidUri);
				else
					value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, OLESTR("none");
			}
			break;

		case CSSProperty_font_family:
			{
				CSSValueList* pCSSValue = new CSSValueList;
				pCSSValue->m_propertyIndex = propertyIndex;

				CComBSTR str = OLESTR("";
				for (int i = 0; i < m_computedFontFamily.GetSize(); i++)
				{
					CFontDef* pFontDef = m_computedFontFamily[i];

					if (i > 0) str += OLESTR(",";
					str += pFontDef->m_pFamily->m_name;
				}

				pCSSValue->set_cssText(str);

				value = pCSSValue;
			}
			break;

		case CSSProperty_font_size:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_NUMBER, m_computedFontSize);
			}
			break;

		case CSSProperty_font_style:
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, FontStyleStrings[m_computedFontStyle]);
			}
			break;

		case CSSProperty_text_anchor:
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, TextAnchorStrings[m_computedTextAnchor]);
			}
			break;

		case CSSProperty_font_weight:
			{
				OLECHAR buf[6];
				swprintf(buf, OLESTR("%d", m_computedFontWeight);
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, buf);
			}
			break;

		case CSSProperty_text_indent:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedTextIndent);
			}
			break;

		case CSSProperty_line_height:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedLineHeight);
			}
			break;

		case CSSProperty_text_align:
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, TextAlignStrings[m_computedTextAlign]);
			}
			break;

		case CSSProperty_left:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedLeft);
			}
			break;

		case CSSProperty_top:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedTop);
			}
			break;

		case CSSProperty_width:
			{
			//	ASSERT(m_computedWidth >= 0);	// TODO Have this??
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedWidth);
			}
			break;

		case CSSProperty_height:
			{
			//	ASSERT(m_computedHeight >= 0);	// TODO Have this??
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedHeight);
			}
			break;

		// border styles
		case CSSProperty_border_left_style:
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, BorderStyleIdents[m_computedBorderStyle[0]]);
			}
			break;
		
		case CSSProperty_border_top_style:
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, BorderStyleIdents[m_computedBorderStyle[1]]);
			}
			break;

		case CSSProperty_border_right_style:
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, BorderStyleIdents[m_computedBorderStyle[2]]);
			}
			break;
		
		case CSSProperty_border_bottom_style:
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, BorderStyleIdents[m_computedBorderStyle[3]]);
			}
			break;

		// margin
		case CSSProperty_margin_left:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedMargin[0]);
			}
			break;

		case CSSProperty_margin_top:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedMargin[1]);
			}
			break;

		case CSSProperty_margin_right:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedMargin[2]);
			}
			break;

		case CSSProperty_margin_bottom:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedMargin[3]);
			}
			break;

		// border
		case CSSProperty_border_left_width:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedBorderWidth[0]);
			}
			break;

		case CSSProperty_border_top_width:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedBorderWidth[1]);
			}
			break;

		case CSSProperty_border_right_width:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedBorderWidth[2]);
			}
			break;

		case CSSProperty_border_bottom_width:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedBorderWidth[3]);
			}
			break;

		// padding
		case CSSProperty_padding_left:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedPadding[0]);
			}
			break;

		case CSSProperty_padding_top:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedPadding[1]);
			}
			break;

		case CSSProperty_padding_right:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedPadding[2]);
			}
			break;

		case CSSProperty_padding_bottom:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_PX, m_computedPadding[3]);
			}
			break;
// border-color
		case CSSProperty_border_left_color:
			{
				value = CreateCSSUnitRGBValue(propertyIndex, m_computedBorderColor[0]);
			}
			break;

		case CSSProperty_border_top_color:
			{
				value = CreateCSSUnitRGBValue(propertyIndex, m_computedBorderColor[1]);
			}
			break;

		case CSSProperty_border_right_color:
			{
				value = CreateCSSUnitRGBValue(propertyIndex, m_computedBorderColor[2]);
			}
			break;

		case CSSProperty_border_bottom_color:
			{
				value = CreateCSSUnitRGBValue(propertyIndex, m_computedBorderColor[3]);
			}
			break;

		case CSSProperty_cursor:
			{
				ASSERT(m_computedCursor >= 0);
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, CursorIdents[m_computedCursor]);
			}
			break;

		case CSSProperty_border_collapse:	// CSS Table
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, BorderCollapseIdents[m_computedBorderCollapse]);
			}
			break;

		case CSSProperty_empty_cells:	// CSS Table
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, EmptyCellsIdents[m_computedEmptyCells]);
			}
			break;

		case CSSProperty_border_spacing:	// CSS Table
			{
				CSSValueList* pCSSValue = new CSSValueList;
				pCSSValue->m_propertyIndex = propertyIndex;

				OLECHAR str[256];

				if (m_computedBorderSpacing[1] == m_computedBorderSpacing[0])
				{
					swprintf(str, OLESTR("%gpx", m_computedBorderSpacing[0]);
				}
				else
				{
					swprintf(str, OLESTR("%gpx %gpx", m_computedBorderSpacing[0], m_computedBorderSpacing[1]);
				}

				pCSSValue->set_cssText(str);

				value = pCSSValue;
			}
			break;

		//
		case CSSProperty_clip:
			{
				// TODO
				ASSERT(0);
			}
			break;

		case CSSProperty_direction:
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, (m_computedDirection == Direction_ltr)? OLESTR("ltr": OLESTR("rtOLESTR(");
			}
			break;

		case CSSProperty_color:
			{
				value = CreateCSSUnitRGBValue(propertyIndex, m_computedColor);
			}
			break;

		case CSSProperty_background_color:
			{
				if (m_computedBackgroundColor.GetAlpha() > 0)
					value = CreateCSSUnitRGBValue(propertyIndex, m_computedBackgroundColor);
				else
					value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, OLESTR("transparent");
			}
			break;

		case CSSProperty_stroke:	// SVG
			{
				value = CreateSVGPaintValue(propertyIndex, &m_computedStroke);
			}
			break;

		case CSSProperty_fill:	// SVG
			{
				value = CreateSVGPaintValue(propertyIndex, &m_computedFill);
			}
			break;

		case CSSProperty_opacity:
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_NUMBER, m_computedOpacity);
			}
			break;

		case CSSProperty_stroke_opacity:	// SVG
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_NUMBER, m_computedStrokeOpacity);
			}
			break;

		case CSSProperty_fill_opacity:	// SVG
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_NUMBER, m_computedFillOpacity);
			}
			break;

		case CSSProperty_stroke_width:	// SVG
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_NUMBER, m_computedStrokeWidth);
			}
			break;

		case CSSProperty_stroke_miterlimit:	// SVG
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_NUMBER, m_computedStrokeMiterLimit);
			}
			break;

		case CSSProperty_stroke_dashoffset:	// SVG
			{
				value = CreateCSSUnitValue(propertyIndex, CSS_NUMBER, m_computedStrokeDashOffset);
			}
			break;

		case CSSProperty_shape_rendering:	// SVG
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, ShapeRenderingIdents[m_computedShapeRendering]);
			}
			break;

		case CSSProperty_image_rendering:	// SVG
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, ImageRenderingIdents[m_computedImageRendering]);
			}
			break;

		case CSSProperty_pointer_events:	// SVG
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, PointerEventsIdents[m_computedPointerEvents]);
			}
			break;

		case CSSProperty_fill_rule:	// SVG
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, FillRuleStrings[m_computedFillRule]);
			}
			break;

		case CSSProperty_clip_rule:	// SVG
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, ClipRuleStrings[m_computedClipRule]);
			}
			break;

		case CSSProperty_stroke_linecap:	// SVG
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, StrokeLineCapStrings[m_computedStrokeLineCap]);
			}
			break;

		case CSSProperty_stroke_linejoin:	// SVG
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, StrokeLineJoinIdents[m_computedStrokeLineJoin]);
			}
			break;

		case CSSProperty_stroke_dasharray:	// SVG
			{
				CSSValueList* pCSSValue = new CSSValueList;
				if (pCSSValue)
				{
					pCSSValue->m_propertyIndex = propertyIndex;

					if (m_strokeDashValuesArray.GetSize() == 0)
					{
						pCSSValue->set_cssText(OLESTR("none");
					}
					else
					{
						CComBSTR str;
						for (int i = 0; i < m_strokeDashValuesArray.GetSize(); i++)
						{
							if (i > 0) str += OLESTR(",";
							OLECHAR buf[16];
							swprintf(buf, OLESTR("%d", m_strokeDashValuesArray[i]);
							str += buf;
						}

						pCSSValue->set_cssText(str);
					}

					value = pCSSValue;
				}
			}
			break;

		case CSSProperty_color_interpolation:	// SVG
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, ColorInterpolationStrings[m_computedColorInterpolation]);
			}
			break;

		case CSSProperty_color_interpolation_filters:	// SVG
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, ColorInterpolationStrings[m_computedColorInterpolationFilters]);
			}
			break;

		case CSSProperty_stop_color:	// SVG
			{
				value = CreateSVGColorValue(propertyIndex, &m_computedStopColor);
			}
			break;

		case CSSProperty_visibility:
			{
				value = CreateCSSUnitStringValue(propertyIndex, CSS_IDENT, VisibilityIdents[m_computedVisibility]);
			}
			break;

		default:
			ATLTRACE("%S\n", csstyleList[propertyIndex].m_name);
			ASSERT(0);
			return NULL;
	}
#endif
	return value;
}

#if 0	// Had this
CATAttr* PElementBase::OverrideCSSProperty(BSTR propertyName)
{
	CSSDecl* pdecl = m_pOverrideStyle->FindDecl(propertyName);	// Find already animated attr
	if (pdecl) return pdecl;

	int propertyIndex = GetCSSStyleIndex(propertyName);
	if (propertyIndex >= 0)
	{
		pdecl = m_pOverrideStyle->internalAddLonghandProperty(propertyName, propertyIndex);

		ASSERT(m_pOverrideStyle->m_decls.GetSize() > 0);
	}

	return pdecl;
}

void PElementBase::SetOverrideStyleToBase()
{
	// Set animVal to baseVal on all properties
	// for css properties, baseVal is taken from getComputedStyle

	for (int i = 0; i < m_pOverrideStyle->m_decls.GetSize(); i++)
	{
		CSSDecl* pdecl = m_pOverrideStyle->m_decls[i];

		CComPtr<CSSValue> cssvalue;
		GetCachedComputedProperty(pdecl->m_propertyIndex, &cssvalue);

		ASSERT(cssvalue != NULL);

		CComBSTR cssText;
		cssvalue->get_cssText(&cssText);

		*pdecl->m_pValue = cssText;
	}
}
#endif

void CPAnimationElementImpl::SetValuesFromAttributes()
{
	ASSERT(0);
#if 0
	if (m_pAnimatedCSSAttr)
	{
		//m_pAnimatedCSSAttr->Release();
		m_pAnimatedCSSAttr = NULL;	// The attribute being animated
	}

	CComQIPtr<ILDOMElement> element = m_pNode;
	CComQIPtr<ILAnimationElement> animation = m_pNode;

	CComPtr<ILDOMElement> target;
	animation->get_targetElement(&target);

	if (target)
	{
		CComQIPtr<CLDOMElementImplImpl> elementImpl = target;
		PElementBase* pAnimationTarget = (PElementBase*)elementImpl->GetNodeOnFrame(m_pView);

		CComQIPtr<ILSMILAnimationTarget> animtarget = target;

		CComBSTR attrName;
		element->getAttribute(OLESTR("attributeName", &attrName);

		if (attrName.Length())
		{
			CComBSTR attrType = NULL;
			element->getAttribute(OLESTR("attributeType", &attrType);

			//CAnimationTarget* pAnimationTarget = static_cast<CAnimationTarget*>(animtarget.p);

			if ((attrType.Length() == 0) || !tcscmp(attrType, OLESTR("auto"))
			{
				m_pAnimatedCSSAttr = pAnimationTarget->OverrideCSSProperty(attrName);
			//	if (!m_animatedAttr) m_animatedAttr = static_cast<CLDOMElementImpl<ILDOMElement>*>(target.p)->GetXMLAttribute(attrName);
			}
			else if (!tcscmp(attrType, OLESTR("CSS"))
			{
				m_pAnimatedCSSAttr = pAnimationTarget->OverrideCSSProperty(attrName);
			}
			/*
			else if (!tcscmp(attrType, OLESTR("XMOLESTR("))
			{
				m_animatedAttr = static_cast<CLDOMElementImpl<ILDOMElement>*>(target.p)->GetXMLAttribute(attrName);
			}
			*/
		}
	}
#endif
}

#if 0
// Global function, is that ok?
void WEBEXT CalcDims(PElementBase* pElement)
{
	//PElementBase* pElement = this;

	HDC hDC = CreateCompatibleDC(NULL);
	{
		LDraw::Graphics graphics(hDC);

		CHTMCalcContext pC;
		//I Had this.. ???
		//pC.m_pUI = m_pUI;

		pC.m_pGraphics = &graphics;

		pC.m_pStringFormat = LDraw::StringFormat::GenericTypographic();

	//	graphics.SetTextRenderingHint(LDraw::TextRenderingHintAntiAliasGridFit/*TextRenderingHintAntiAlias*/);	// ??
		graphics.SetTextRenderingHint(LDraw::TextRenderingHintSystemDefault/*TextRenderingHintAntiAlias*/);	// ??

#if 0	// ??
		pElement->RemoveBoxes();
#endif

		pElement->CalculateDimensions(&pC);
	}
	DeleteDC(hDC);
}
#endif

#if 0	// Had this
// virtual
void PElementBase::OnInsertedChild(ILDOMNode* node)
{
	ASSERT(0);	// TODO
}

// virtual
void PElementBase::OnAttrChanged(ILDOMAttr* attr)
{
//	CComQIPtr<ILDOMElement> element = m_pNode;

	GetCSSPropertiesAndChildren();
	BuildRenderChildren();
	SetValuesFromAttributes();	// ??
	CalcDims(this);

		/*	Only do it id style attribute changed (above) ??
//#if 0	// This calculates text stuff ??
		static_cast<CLDOMElement*>(thisNode)->m_pNodes[i]->m_pFrame->CalcDims((PElementBase*)static_cast<CLDOMElement*>(thisNode)->m_pNodes[i]);
//#endif
*/

	CalculateBoundsAndChildren();

	if (m_parent)
		m_parent->RecalculateParentBounds();

	/*
	if (m_pWindow)	// TODO
		m_pWindow->InvalidateRect(&unionrect);
		*/

#if 0
	for (i = 0; i < CComQIPtr<CLDOMDocumentImplImpl>(m_ownerDocument)->m_pViews.GetSize(); i++)
	{
#if 0	// TODO (At least check that the element is attached to a frame yet
		((CLDOMDocument*)ownerDocument.p)->m_pElements[i]->Flow();
#endif

		CComQIPtr<CLDOMDocumentImplImpl>(m_ownerDocument)->m_pViews[i]->InvalidateRect(NULL);
	}
#endif
}
#endif

#if 0	// Didn't have this
// virtual
HRESULT PElementBase::OnChanged(NotifyType type, IUnknown *targetObject, IUnknown *immtargetObject, DISPID dispID)
{
	if (type == (NotifyType)-1) return S_OK;	// Hack

	if (targetObject == m_pWindow->m_range)
	{
		m_pWindow->InvalidateRect(NULL);

#if 0
		m_pUI->m_document->Fire_onselect();
#endif
	}
	else if (m_pWindow->m_pFrameSet == NULL) // ???// if (m_htmTree || m_pFODisplay)
	{
		m_pWindow->m_lockPaint++;

		CComQIPtr<ILDOMNode> targetNode = targetObject;
		if (targetNode)
		{
			LDOMNodeType nodeType;
			targetNode->get_nodeType(&nodeType);
			
			if ((nodeType == LNODE_TEXT/* || nodeType == LNODE_CDATA_SECTION*/) &&
				(type == NOTIFY_MODIFY))
			{
				CComQIPtr<ILDOMCharacterData> charData = targetNode;

				CPTextNode* pText = (CPTextNode*)CComQIPtr<CLDOMNodeImplImpl>(charData)->GetNodeOnFrame(m_pView);
				if (pText)
				{
					pText->OnTextContentChanged();

					{
						HDC hDC = CreateCompatibleDC(NULL);
						{
							LDraw::Graphics graphics(hDC);

							CHTMCalcContext pC;
							// I had this ???
							//pC.m_pUI = m_pWindow->m_pUI;
							pC.m_pGraphics = &graphics;

							pC.m_pStringFormat = LDraw::StringFormat::GenericTypographic();

							graphics.SetTextRenderingHint(LDraw::TextRenderingHintSystemDefault/*TextRenderingHintAntiAliasGridFit*//*TextRenderingHintAntiAlias*/);	// ??

							pText->CalculateDimensions(&pC);
						}
						DeleteDC(hDC);
					}

				// TODO, have common code for both svg and css box model
					if (m_pWindow->m_pSVGElement == NULL)
					{
						PElementBase* pParent = pText->m_parent;

						pParent->RemoveBoxes();

						while (pParent)
						{
							if (pParent->m_computedDisplayRole == DisplayRole_table_cell)
							{
								pParent->CalculateMinMaxDimensions();
							}

							pParent = pParent->m_parent;
						}
					}
					else
					{
						ASSERT(0);
#if 0
						PElementBase* pParent = pText->m_parent;

						while (pParent)
						{
							CComQIPtr<ILSVGTextElement> textElement = pParent->m_pNode;
							if (textElement)
							{
								CPSVGTextElement* pSVGTextElement = (CPSVGTextElement*)pParent;
								pSVGTextElement->CalculateBounds();

								pSVGTextElement->m_parent->RecalculateParentBounds();

								break;
							}

							pParent = pParent->m_parent;
						}
#endif
					}
				}
			}
			else
			{
				if (TRUE)
				{
					m_pWindow->m_curContainer = NULL;	// hm..
					if (m_pWindow->m_range)
					{
						m_pWindow->m_range->setStart(NULL, -1);
						m_pWindow->m_range->setEnd(NULL, -1);
					}
				}

				CComQIPtr<ILDOMElement> element = targetNode;

				CComPtr<ILDOMNode> parentNode;
				targetNode->get_parentNode(&parentNode);

				if (element && type == NOTIFY_ADD)
				{
					CComQIPtr<ILDOMDocument> document = parentNode;

					if (document)
					{
						PElementBase* pPElement = m_pView->CreateElement(element);
						if (pPElement)
						{
							CComQIPtr<CLDOMElementImplImpl>(element)->m_pNodes.Add(pPElement);
							pPElement->BuildChildren();

							m_pView->m_pRootElement = pPElement;

							ASSERT(0);
#if 0
							m_pWindow->m_pSVGElement = (PSVGElement*)m_pWindow->m_htmTree;
							m_pWindow->m_pSVGElement->CreateBehaviors();	// TODO, don't do this here

							pPElement->GetCSSPropertiesAndChildren();
							pPElement->SetValuesFromAttributes();	// ??
							m_pWindow->CalcDims(pPElement);

							m_pWindow->m_element = element;
#endif
						}
					}
					else
					{
						PElementBase* pParentElement = (PElementBase*)CComQIPtr<CLDOMNodeImplImpl>(parentNode)->GetNodeOnFrame(m_pView);

						if (pParentElement)
						{
							PElementBase* pPElement = m_pView->CreateElement(element);
							if (pPElement)
							{
								CComQIPtr<CLDOMElementImplImpl>(element)->m_pNodes.Add(pPElement);
								pPElement->m_parent = pParentElement;
								pPElement->BuildChildren();

								UPOSITION pos = pParentElement->m_childList.GetHeadPosition();

								CComPtr<ILDOMNode> child;
								parentNode->get_firstChild(&child);

								while (child)
								{
									if (child == targetNode)
										break;

									if (pos)
									{
										UPOSITION pos2 = pos;
										PNode* pChild = (PNode*)pParentElement->m_childList.GetNext(pos2);
										ASSERT(pChild->m_pNode != element);
										if (pChild->m_pNode == child)
										{
											pos = pos2;	// Okay, advance pos
										}
									}

									CComPtr<ILDOMNode> nextSibling;
									child->get_nextSibling(&nextSibling);
									child = nextSibling;
								}

								if (pos)
									pParentElement->m_childList.InsertBefore(pos, pPElement);
								else
									pParentElement->m_childList.AddTail(pPElement);

								pParentElement->BuildRenderChildren();

								pPElement->GetCSSPropertiesAndChildren();
								pPElement->SetValuesFromAttributes();	// ??
								CalcDims(pPElement);

								// ??
								pPElement->CalculateBoundsAndChildren();
								pPElement->m_parent->RecalculateParentBounds();

								if (CComQIPtr<ILSVGElement>(pPElement->m_pNode) != NULL)	// TODO remove
								{
									ASSERT(0);
#if 0
									gmMatrix3 ctm = ((PSVGElement*)pPElement)->GetScreenCTM();

									RectD xrect;
									GetTransformRectBoundingBox(ctm.inverse(), ((PSVGElement*)pPElement)->m_expandedBBox, &xrect);

									CRect rect((int)xrect.X, (int)xrect.Y, (int)ceil(xrect.GetRight()), (int)ceil(xrect.GetBottom()));
									m_pWindow->InvalidateRect(&rect);
#endif
								}
							}
						}
					}
				}
				else if (element && type == NOTIFY_REMOVE)
				{
					CComQIPtr<ILDOMDocument> document = parentNode;
					if (document)
					{
						m_pView->m_pRootElement->Release();
						m_pView->m_pRootElement = NULL;
						m_pWindow->m_pSVGElement = NULL;

						m_pWindow->m_element = NULL;
					}
					else
					{
						PElementBase* pParentElement = (PElementBase*)CComQIPtr<CLDOMNodeImplImpl>(parentNode)->GetNodeOnFrame(m_pView);

						if (pParentElement)
						{
							PElementBase* pPElement = NULL;

							for (int i = 0; i < CComQIPtr<CLDOMElementImplImpl>(targetNode)->m_pNodes.GetSize(); i++)
							{
								if (CComQIPtr<CLDOMElementImplImpl>(targetNode)->m_pNodes[i]->m_pView == m_pView)
								{
									pPElement = (PElementBase*)CComQIPtr<CLDOMElementImplImpl>(targetNode)->m_pNodes[i];
									break;
								}
							}

							if (pPElement)
							{
								if (CComQIPtr<ILSVGElement>(pPElement->m_pNode) != NULL)	// TODO remove
								{
									ASSERT(0);
#if 0
									gmMatrix3 ctm = ((PSVGElement*)pPElement)->GetScreenCTM();

									RectD xrect;
									GetTransformRectBoundingBox(ctm.inverse(), ((PSVGElement*)pPElement)->m_expandedBBox, &xrect);

									CRect rect((int)xrect.X, (int)xrect.Y, (int)ceil(xrect.GetRight()), (int)ceil(xrect.GetBottom()));
									m_pWindow->InvalidateRect(&rect);
#endif
								}

								UPOSITION pos;
								
								pos = pParentElement->m_childList.Find(pPElement);
								pParentElement->m_childList.RemoveAt(pos);

								if (CComQIPtr<ILSVGElement>(pParentElement->m_pNode) != NULL)
								{
									ASSERT(0);
#if 0
									pos = ((PSVGElement*)pParentElement)->m_childListRender.Find(pPElement);
									if (pos)
									{
										((PSVGElement*)pParentElement)->m_childListRender.RemoveAt(pos);
									}
#endif
								}

								m_pWindow->RemovingElement(pPElement);
								pPElement->Release();

								pParentElement->RecalculateParentBounds();
							}
						}
					}
				}
				else// if (element)
				{
// TODO, improve this a lot, inserting a text node currently triggers this one

					
					CComQIPtr<ILDOMDocument> document = parentNode;
					if (document)
					{
						/*
						if (type == NOTIFY_REMOVE)
						{
							m_htmTree->Release();
							m_htmTree = NULL;
							m_pSVGElement = NULL;

							m_element = NULL;
						}
						else
						{
						}
						*/
					}
					else
					{
				//		PElementBase* pPElement = (PElementBase*)CComQIPtr<CLDOMNodeImplImpl>(element)->GetNodeOnFrame(this);
						PElementBase* pParentElement = (PElementBase*)CComQIPtr<CLDOMNodeImplImpl>(parentNode)->GetNodeOnFrame(m_pView);

				//		pPElement->SetValuesFromAttributes();
				//		CalcDims(pPElement);

						if (pParentElement)
						{
							//pParentNode->RemoveBoxes();
							pParentElement->RemoveChildren();
							pParentElement->BuildChildren();

							pParentElement->GetCSSPropertiesAndChildren();
							pParentElement->SetValuesFromAttributes();	// ??
							CalcDims(pParentElement);
						}
					}
	//#endif
				}
			}
		}
#if 0	// Not needed on SVG??
		Flow();
#endif

		m_pWindow->m_lockPaint--;

		// Fix selection range
		if (m_pWindow->m_range)
		{
			CComPtr<ILDOMNode> startContainer;
			m_pWindow->m_range->get_startContainer(&startContainer);

			CComPtr<ILDOMNode> endContainer;
			m_pWindow->m_range->get_endContainer(&endContainer);

			//m_startContainer = m_htmTree->FindDOMElement(startContainer);
			//m_endContainer = m_htmTree->FindDOMElement(endContainer);

			//m_curContainer = m_htmTree->FindDOMElement(endContainer);	// ??
			//m_initContainer = m_htmTree->FindDOMElement(endContainer);	// ??

			//m_startContainer = 

		//	m_range->get_startOffset(&m_startOffset);
		//	m_range->get_endOffset(&m_endOffset);
		}

	}
	else if (m_pWindow->m_pFrameSet)
	{
		ASSERT(0);
#if 0
		m_pWindow->m_pFrameSet->PositionFrames();
#endif
	}

//	InvalidateRect(NULL);

	//FireOnChanged(type, targetObject, dispID);
	return S_OK;
}
#endif

}	// Web
}
