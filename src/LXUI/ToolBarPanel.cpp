#include "stdafx.h"
#include "LXUI2.h"
#include "ToolBarPanel.h"

namespace System
{
namespace UI
{

enum TBState
{
	TBSTATE_HIDDEN = 0x8,
	TBSTYLE_SEP = 0x20,
	TBSTATE_WRAP = 0x1,
};

/*
#if AMIGA || __APPLE__
// these are currently included in commctrl.h	// TODO fix this

#define TBSTATE_HIDDEN          0x08
#define TBSTATE_WRAP            0x20
#define TBSTYLE_SEP             0x0001  // obsolete; use BTNS_SEP instead
#endif
  */

DependencyProperty* ToolBarPanel::s_WrapProperty = RegisterAttached(WSTR("Wrap"), typeid(bool), typeid(ToolBarPanel), BoolObject::get_False(), PropertyMetaData(None));

ToolBarPanel::ToolBarPanel()
{
	m_dragging = 0;
	m_nTimer = 0;
//	m_selectedID = 0L;
//	m_result = 0;
	m_popupFlags = 0;
	m_orientation = -1;//0;

//	m_pActiveItem = NULL;
//	m_pPrevActiveItem = NULL;
//	m_parentMenuDlg = NULL;
//	m_activeSubDlg = NULL;

	m_dragInsertIndex = -1;

//	m_bParentMsgLoop = FALSE;
//	m_bDestroy = FALSE;

#if 0
	m_menuItem = NULL;
#endif

//	m_bInsideWindow = FALSE;

//	itemHeight = 18;
//	floatHeight = 8;
	iBitmap = 12;
//	bAnimate = 0;
}

// static
bool ToolBarPanel::GetWrap(UIElement* pObject)
{
	return dynamic_cast<System::BoolObject*>(pObject->GetValue(s_WrapProperty))->GetValue();
}

// static
void ToolBarPanel::SetWrap(UIElement* pObject, bool newVal)
{
	pObject->SetValue(s_WrapProperty, BoolObject::GetObject(newVal));
}

// static
void ToolBarPanel::ClearWrap(UIElement* pObject)
{
	pObject->ClearValue(s_WrapProperty);
}

#if 0

#include "PLXUIMenuItemElement.h"

#include "LXUIBoxWindow.h"
#include "..\LHTML\PImage.h"
#include "..\LHTML\LDOMElementImpl.h"
#include "..\LHTML\PElement.h"
#include "..\LHTML\HTMPElement.h"

#include "HTMContext.h"
#include "PBlockBox.h"

/////////////////////////////////////////////////////////////
// CToolbarButton

#if 0
void CToolbarButton::OnDraw(HDC hDC, RECT rect, long orientation, DWORD flags)
{
	CRect itemrect = rect;

	int itemheight = itemrect.Height();

//	DWORD type;
//	get_type(&type);

//	DWORD state;
//	get_state(&state);

	SetBkMode(hDC, TRANSPARENT);

	HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);

	HFONT hVerticalFont = NULL;

	if (orientation == 2)
	{
		//LOGFONT lf;
		//GetObject(hDC, sizeof(lf), &lf);
	//	strcpy(lf.lfFaceName, "Courier New");
	//	lf.lfEscapement = 0;//-90*10;
	//	lf.lfOrientation = 0;//-90*10;
	//	lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;
		//lf.lfWeight = FW_BOLD;

		//hVerticalFont = CreateFontIndirect(&lf);

		hVerticalFont = CreateFont(16, 0, -90*10, -90*10, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Verdana");

		ASSERT(hVerticalFont != NULL);

		SelectObject(hDC, hVerticalFont);

		SetTextAlign(hDC, TA_BOTTOM);
	}

	HIMAGELIST hBitmap = m_menuDlg->m_hBitmap;
	long bitmapIndex = m_bitmapIndex;
	int cx, cy;

	/*
	CComQIPtr<IUICommand> command;
	get_command(&command);
	if (command != NULL)
	{
		command->get_bitmap((DWORD*)&hBitmap);
		command->get_bitmapIndex(&bitmapIndex);
	}
	*/

	ImageList_GetIconSize(hBitmap, &cx, &cy);

	CComBSTR fulltext = m_text;
	//get_text(&fulltext);

	CRect iconrect(0,0,0,0);
	CRect trect(0,0,0,0);

	if (orientation == 0)
	{
		if (flags & 1)	// hilight
		{
			CRect hilightrect = itemrect;
			if (hBitmap || (fsState & TBSTATE_CHECKED)) hilightrect.left += 18;

			FillSolidRect(hDC, &hilightrect, GetSysColor(COLOR_HIGHLIGHT));
			SetTextColor(hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
		}
		else
		{
			SetTextColor(hDC, GetSysColor(COLOR_MENUTEXT));
		}
	}
	else// if (orientation >= 1)	// 1 || 2
	{
		if (flags & 2)	// pushed
		{
			Draw3DRect(hDC, &itemrect, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
		}
		else if (flags & 1)	// hilight
		{
			Draw3DRect(hDC, &itemrect, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
		}
	}

	// Draw Text
	if (bitmapIndex == -1 || orientation >= 0)
	{
		if (fulltext.Length())
		{
			CUString text;
			CUString shortcuttext;

			WCHAR* tab = wcschr(fulltext, L'\t');

			if (tab)
			{
				text = CUString(fulltext).Left((tab-fulltext)/2);
				shortcuttext = CUString(tab+1);
			}
			else
			{
				text = fulltext;
			}

			RECT trect = itemrect;
			if (orientation == 0)	// top-bottom
			{
				trect.left += 20;
			}
			else// if (orientation == 1)	// left-right
			{
				trect.left += 2;

				if (flags & 2)	// Pushed
				{
					trect.left++;
					trect.top++;
				}
			}

			unsigned long itemChildren = 0;
#if 0
			CountItems(&itemChildren);
#endif

			if (itemChildren > 0 ||	// Popupmenus are always enabled
				!(fsState & TBSTATE_INDETERMINATE))
			{
				/*
				if (orientation == 2)
				{
					TextOut(hDC, trect.left, trect.top, text, text.GetLength());
				}
				else
					*/
				{
					DrawText(hDC, text, text.GetLength(), &trect, DT_SINGLELINE | DT_VCENTER);
				}
			//	DrawText(hDC, shortcuttext, shortcuttext.GetLength(), &screct, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);
			}
			else
			{
				SetTextColor(hDC, RGB(200, 200, 200));
				DrawText(hDC, text, text.GetLength(), &trect, DT_SINGLELINE | DT_VCENTER);
			//	DrawText(hDC, shortcuttext, shortcuttext.GetLength(), &screct, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);

				OffsetRect(&trect, -1, -1);
			//	OffsetRect(&screct, -1, -1);

				SetTextColor(hDC, RGB(140, 140, 140));
				DrawText(hDC, text, text.GetLength(), &trect, DT_SINGLELINE | DT_VCENTER);
			//	DrawText(hDC, shortcuttext, shortcuttext.GetLength(), &screct, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);
			}
		}
	}

// Draw icon
	if (orientation >= 0)
	{
		iconrect.left = itemrect.left;
		iconrect.top = itemrect.top+(itemrect.Height()-18)/2;
		iconrect.right = iconrect.left+18;
		iconrect.bottom = iconrect.top+18;

		if (fsState & TBSTATE_CHECKED)
		{
			if (!(flags & 1)) FillSolidRect(hDC, &iconrect, RGB(240, 240, 240));
			Draw3DRect(hDC, &iconrect, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHILIGHT));
		}

		if (hBitmap)
		{
			POINT iconpos;
			iconpos.x = iconrect.left + (iconrect.Width()-cx)/2;
			iconpos.y = iconrect.top + (iconrect.Height()-cy)/2;

			if (fsState & TBSTATE_INDETERMINATE)
			{
				HICON hIcon = ImageList_ExtractIcon(NULL, hBitmap, bitmapIndex);
				if (hIcon)
				{
					DrawState(hDC, NULL, NULL, (LPARAM)hIcon, 0, iconpos.x+1, iconpos.y+1, cx, cy, DST_ICON | DSS_DISABLED); 
					DestroyIcon(hIcon);
				}
			}
			else
			{
				if (fsState & TBSTATE_CHECKED)
				{
					ImageList_Draw(hBitmap, bitmapIndex, hDC, iconpos.x+1, iconpos.y+1, ILD_TRANSPARENT);
				}
				else
				{
					if (flags & 1) Draw3DRect(hDC, &iconrect, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
					ImageList_Draw(hBitmap, bitmapIndex, hDC, iconpos.x, iconpos.y, ILD_TRANSPARENT);
				}
			}
		}
		else
		{
			if (fsState & TBSTATE_CHECKED)
			{
				int xmiddle = iconrect.left + iconrect.Width()/2;
				int ymiddle = iconrect.top + iconrect.Height()/2;

				MoveToEx(hDC, xmiddle-6, ymiddle, NULL);
				LineTo(hDC, xmiddle-2, ymiddle+4);
				LineTo(hDC, xmiddle+6, ymiddle-4);

				MoveToEx(hDC, xmiddle-6-1, ymiddle, NULL);
				LineTo(hDC, xmiddle-2-1, ymiddle+4);
				LineTo(hDC, xmiddle+6-1, ymiddle-4);
			}
		}

	}
	else
	{
		CRect iconrect = itemrect;

		if (hBitmap)
		{
			POINT iconpos;
			iconpos.x = iconrect.left + (iconrect.Width()-cx)/2;
			iconpos.y = iconrect.top + (iconrect.Height()-cy)/2;

			if (fsState & TBSTATE_INDETERMINATE)
			{
				HICON hIcon = ImageList_ExtractIcon(NULL, hBitmap, bitmapIndex);
				if (hIcon)
				{
					DrawState(hDC, NULL, NULL, (LPARAM)hIcon, 0, iconpos.x+1, iconpos.y+1, cx, cy, DST_ICON | DSS_DISABLED); 
					DestroyIcon(hIcon);
				}
			}
			else
			{
				if (fsState & TBSTATE_CHECKED)
				{
					if (!(flags & 1)) FillSolidRect(hDC, &iconrect, RGB(240, 240, 240));
					Draw3DRect(hDC, &iconrect, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));

					ImageList_Draw(hBitmap, bitmapIndex, hDC, iconpos.x+1, iconpos.y+1, ILD_TRANSPARENT);
				}
				else
				{
					ImageList_Draw(hBitmap, bitmapIndex, hDC, iconpos.x, iconpos.y, ILD_TRANSPARENT);
					if (flags & 1) Draw3DRect(hDC, &itemrect, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
				}
			}
		}

#if 0
		if (type & MF_POPUP)
		{
			POINT pt[3] =
			{
				iconrect.right-1, iconrect.bottom-5,
				iconrect.right-1, iconrect.bottom-1,
				iconrect.right-5, iconrect.bottom-1,
			};

			HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));

			Polygon(hDC, pt, 3);

			SelectObject(hDC, hOldPen);
			SelectObject(hDC, hOldBrush);
		}
#endif
	}

	if (orientation == 0)
	{
		unsigned long itemchildren = 0;
#if 0
		CountItems(&itemchildren);
#endif
		if (itemchildren > 0)	// It's a nested popup menu
		{
			int cy = itemrect.top + itemheight/2;
			
			POINT pt[3] =
			{
				itemrect.right - 12, cy-4,
				itemrect.right - 12, cy+4,
				itemrect.right - 4, cy
			};
			
			Polygon(hDC, pt, 3);
		}
	}

	SelectObject(hDC, hOldFont);
	if (hVerticalFont)
	{
		DeleteObject(hVerticalFont);
	}
}
#endif

///////////////////////////////////////////////////////////////////////////////////
// ToolBarPanel


/*
int ToolBarPanel::FinalConstruct()
{
	CComObject<CLXUIWindowImplImpl>::CreateInstance(&m_pOwnedWindow);
	m_pOwnedWindow->AddRef();

	m_pOwnedWindow->m_htmTree = this;

	return S_OK;
}

void ToolBarPanel::FinalRelease()
{
	RemoveDispItems();
}
*/

#if 0
STDMETHODIMP ToolBarPanel::InitMenu(IMenuItem* menuItem, ICommandTarget* target, int orientation)
{
	m_menuItem = static_cast<CMenuItem*>(menuItem);
	m_orientation = orientation;
	m_pCmdWnd = target;

	CreateSizeDispItemsArray(m_orientation, m_items);

	return S_OK;
}
#endif
#endif

LDraw::SizeD ToolBarPanel::MeasureOverride(LDraw::SizeD availSize)
{
	//GetShowTabs();

//	m_items.RemoveAll();

//	RemoveBoxesAndChildren();

	//CArray<UIElement*, UIElement*>::const_iterator pos = get_rchildList().m_items.begin();
	unsigned int ncount = get_InternalChildren()->GetCount();
	for (unsigned int i = 0; i < ncount; i++)
	{
		UIElement* pNode = get_InternalChildren()->get_Item(i);//(*get_rchildList())[i];//*pos++;

	//	if (pNode->m_type == LNODE_ELEMENT)
		{
	//		CComQIPtr<ILXUIElement> button = pNode->m_pNode;
	//		if (button)
			{
				/*
				CToolbarButton* pItem = (CToolbarButton*)pNode;
				pItem->m_menuDlg = this;

				button->get_textContent(&pItem->m_text);
				//pItem->idCommand = idCommand;
				pItem->m_bitmapIndex = -1;//bitmapIndex;

				m_items.Add(pItem);

				SizeDispItem(m_orientation, pItem);
				*/
			//	m_items.Add(pNode);
				pNode->Measure(LDraw::SizeD(0,0));

				/*
				CPage* pPage = new CPage;
				//pPage->m_pPElement = (CPElement*)pNode;
				pPage->m_dlgSite = (CUIDlgSite*)pNode;

				m_pages.Add(pPage);
				*/
			}
		}
	}

	double length;
//	if (availSize.Width == 0 && availSize.Height == 0)
	{
		length = 99999;
	}
/*	else
	{
		length = availSize.Width;
	}
*/
	LDraw::SizeD size;
	CalcLayout(0, length, &size);

	return size;
}

LDraw::SizeD ToolBarPanel::ArrangeOverride(LDraw::SizeD finalSize)
{
	LDraw::SizeD size;
	CalcLayout(LM_COMMIT, finalSize.Width, &size);

	PlaceItems();

	return finalSize;
}

LDraw::SizeD ToolBarPanel::CalcSize(_TBBUTTON* pData, int nCount)
{
	ASSERT(pData != NULL && nCount > 0);

	LDraw::PointD cur(0,0);
	LDraw::SizeD sizeResult(0,0);

	//DWORD dwExtendedStyle = DefWindowProc(TB_GETEXTENDEDSTYLE, 0, 0);

	for (int i = 0; i < nCount; i++)
	{
		LDraw::SizeD m_sizeButton = LDraw::SizeD(pData[i].cx, pData[i].cy);

		int cySep = 12;//pData[i].iBitmap;
			cySep = cySep * 2 / 3;

		if (pData[i].fsState & TBSTATE_HIDDEN)
			continue;

		double cx = m_sizeButton.Width;
		if (pData[i].fsStyle & TBSTYLE_SEP)
		{
			// a separator represents either a height or width
			if (pData[i].fsState & TBSTATE_WRAP)
				sizeResult.Height = MAX(cur.Y + m_sizeButton.Height + cySep, sizeResult.Height);
			else
				sizeResult.Width = MAX(cur.X + /*pData[i].*/iBitmap, sizeResult.Width);
		}
		else
		{
			/*
			// check for dropdown style, but only if the buttons are being drawn
			if ((pData[i].fsStyle & TBSTYLE_DROPDOWN) &&
				(dwExtendedStyle & TBSTYLE_EX_DRAWDDARROWS))
			{
				// add size of drop down
				ASSERT(_afxDropDownWidth != -1);
				cx += _afxDropDownWidth;
			}
			*/
			sizeResult.Width = MAX(cur.X + cx, sizeResult.Width);
			sizeResult.Height = MAX(cur.Y + /*itemHeight+4*/m_sizeButton.Height, sizeResult.Height);
		}

		if (pData[i].fsStyle & TBSTYLE_SEP)
			cur.X += /*pData[i].*/iBitmap;
		else
			cur.X += cx - CX_OVERLAP;

		if (pData[i].fsState & TBSTATE_WRAP)
		{
			cur.X = 0;
			cur.Y += /*itemHeight+4;*/m_sizeButton.Height;

			if (pData[i].fsStyle & TBSTYLE_SEP)
				cur.Y += cySep;
		}
	}
	return sizeResult;
}

int ToolBarPanel::WrapToolBar(_TBBUTTON* pData, int nCount, double width)
{
	ASSERT(pData != NULL && nCount > 0);

	int nResult = 0;
	double x = 0;
	for (int i = 0; i < nCount; i++)
	{
		pData[i].fsState &= ~TBSTATE_WRAP;

		if (pData[i].fsState & TBSTATE_HIDDEN)
			continue;

		double dx, dxNext;
		if (pData[i].fsStyle & TBSTYLE_SEP)
		{
			dx = /*pData[i].*/iBitmap;
			dxNext = dx;
		}
		else
		{
			dx = pData[i].cx;//m_sizeButton.cx;
			dxNext = dx - CX_OVERLAP;
		}

		if (x + dx > width)
		{
			bool bFound = false;
			for (int j = i; j >= 0  &&  !(pData[j].fsState & TBSTATE_WRAP); j--)
			{
				// Find last separator that isn't hidden
				// a separator that has a command ID is not
				// a separator, but a custom control.
				if ((pData[j].fsStyle & TBSTYLE_SEP) &&
					(pData[j].idCommand == 0) &&
					!(pData[j].fsState & TBSTATE_HIDDEN))
				{
					bFound = true;
					i = j;
					x = 0;
					pData[j].fsState |= TBSTATE_WRAP;
					nResult++;
					break;
				}
			}
			if (!bFound)
			{
				for (int j = i - 1; j >= 0 && !(pData[j].fsState & TBSTATE_WRAP); j--)
				{
					// Never wrap anything that is hidden,
					// or any custom controls
					
					if ((pData[j].fsState & TBSTATE_HIDDEN) ||
						((pData[j].fsStyle & TBSTYLE_SEP) &&
						(pData[j].idCommand != 0)))
						continue;
					
					bFound = true;
					i = j;
					x = 0;
					pData[j].fsState |= TBSTATE_WRAP;
					nResult++;
					break;
				}
				if (!bFound)
					x += dxNext;
			}
		}
		else
			x += dxNext;
	}
	return nResult + 1;
}

void ToolBarPanel::SizeToolBar(_TBBUTTON* pData, int nCount, double length, bool bVert/* = FALSE*/)
{
	ASSERT(pData != NULL && nCount > 0);

	if (!bVert)
	{
		/*
		double minLength;
		double maxLength;
		double midLength;
		*/

		int minLength;
		int maxLength;
		int midLength;

		int nTarget;
		int nCurrent;

		// Wrap ToolBar as specified
		maxLength = length;
		nTarget = WrapToolBar(pData, nCount, maxLength);

		// Wrap ToolBar vertically
		minLength = 0;
		nCurrent = WrapToolBar(pData, nCount, minLength);

		if (nCurrent != nTarget)
		{
			while (minLength < maxLength)
			{
				midLength = (minLength + maxLength) / 2;
				nCurrent = WrapToolBar(pData, nCount, midLength);

				if (nCurrent == nTarget)
				{
					maxLength = midLength;
				}
				else
				{
					if (minLength == midLength)
					{
						WrapToolBar(pData, nCount, maxLength);
						break;
					}
					minLength = midLength;
				}
			}
		}
		LDraw::SizeD size = CalcSize(pData, nCount);
		WrapToolBar(pData, nCount, size.Width);
	}
	else
	{
		LDraw::SizeD sizeMax, sizeMin, sizeMid;

		// Wrap ToolBar vertically
		WrapToolBar(pData, nCount, 0);
		sizeMin = CalcSize(pData, nCount);

		// Wrap ToolBar horizontally
		WrapToolBar(pData, nCount, 32767);
		sizeMax = CalcSize(pData, nCount);

		while (sizeMin.Width < sizeMax.Width)
		{
			sizeMid.Width = (sizeMin.Width + sizeMax.Width) / 2;
			WrapToolBar(pData, nCount, sizeMid.Width);
			sizeMid = CalcSize(pData, nCount);

			if (length < sizeMid.Height)
			{
				if (sizeMin == sizeMid)
				{
					WrapToolBar(pData, nCount, sizeMax.Width);
					return;
				}
				sizeMin = sizeMid;
			}
			else if (length > sizeMid.Height)
			{
				sizeMax = sizeMid;
			}
			else
				return;
		}
	}
}

// virtual
bool ToolBarPanel::OnIdle()
{
//	UpdateItems();
	InvalidateRender();
	return false;
}

void ToolBarPanel::GetButtonInfo(_TBBUTTON* p, int start, int count)
{
	for (int i = 0; i < count; i++)
	{
		p[i].fsState = 0;//m_items[i+start]->fsState;
		p[i].fsStyle = 0;//m_items[i+start]->fsStyle;
	//	p[i].cx = m_items[i+start]->m_size.cx;
		p[i].cx = get_InternalChildren()->get_Item(i+start)->get_DesiredSize().Width;
		p[i].cy = get_InternalChildren()->get_Item(i+start)->get_DesiredSize().Height;
	//	p[i].idCommand = m_items[i+start]->idCommand;
	//	p[i].
	}
}

void ToolBarPanel::CalcLayout(uint dwMode, double length, LDraw::SizeD* pVal)
{
	int orientation;

	if (m_orientation == -1)
		orientation = -1;
	else
		orientation = (dwMode & LM_VERTDOCK)? 2: 1;

	unsigned int nCount = get_InternalChildren()->GetCount();//Item(m_items.GetSize();
	_TBBUTTON* items = new _TBBUTTON[nCount];// CArray<CComObject<CToolbarButton>*,CComObject<CToolbarButton>*> items;
	GetButtonInfo(items, 0, nCount);

	//CreateSizeDispItemsArray(orientation, items);

	_TBBUTTON* pData = items;//.GetData();

	uint m_dwStyle = CBRS_FLOATING;

	LDraw::SizeD sizeResult(0,0);

	if (nCount > 0)
	{
		{
			bool bDynamic = true;//m_dwStyle & CBRS_SIZE_DYNAMIC;

#if 0
			if (bDynamic && (dwMode & LM_MRUWIDTH))
			{
				SizeToolBar(pData, nCount, nLength/*m_nMRUWidth*/);
			}
			else if (bDynamic && (dwMode & LM_HORZDOCK))
			{
				SizeToolBar(pData, nCount, /*nLength > 0? nLength-8:*/ 32767);
			}
			else if (bDynamic && (dwMode & LM_VERTDOCK))
			{
				SizeToolBar(pData, nCount, 0);//nLength-8/*0*/);
			}
			else
#endif
				if (bDynamic && /*(nLength > 0)*/(length != -1))
			{
#if 0
				CRect rect; rect.SetRectEmpty();
				CalcInsideRect(rect, (dwMode & LM_HORZ));
#endif
				bool bVert = (dwMode & LM_LENGTHY) == LM_LENGTHY;
				double len = length/* + (bVert ? rect.Height() : rect.Width())*/;

				SizeToolBar(pData, nCount, len, bVert);
			}
			else if (length == 0)
			{
				SizeToolBar(pData, nCount, length);
			}
#if 0
			else if (bDynamic && (m_dwStyle & CBRS_FLOATING))
			{
				SizeToolBar(pData, nCount, 32767/*m_nMRUWidth*/);
			}
#endif
			else
				SizeToolBar(pData, nCount, (dwMode & LM_HORZ) ? 32767 : 0);
		}

		sizeResult = CalcSize(pData, nCount);
	}

	//
	// Stretch out to fill ?
	if ((dwMode & LM_HORZDOCK)/* && !(m_dwStyle & CBRS_FLOATING)*/)
	{
		if (length > 0)
			sizeResult.Width = length-8;//max(nLength-8, sizeResult.cx);
	}
	//

	//BLOCK: Adjust Margins
#if 0
	{
		CRect rect; rect.SetRectEmpty();
		CalcInsideRect(rect, (dwMode & LM_HORZ));
		sizeResult.Height -= rect.Height();
		sizeResult.Width -= rect.Width();

		/*
		CSize size = CControlBar::CalcFixedLayout((dwMode & LM_STRETCH), (dwMode & LM_HORZ));
		sizeResult.cx = max(sizeResult.cx, size.cx);
		sizeResult.cy = max(sizeResult.cy, size.cy);
		*/
	}
#endif

	*pVal = sizeResult;

	if (dwMode & LM_COMMIT)
	{
		for (int i = 0; i < nCount; i++)
		{
			if (pData[i].fsState & TBSTATE_WRAP)
			{
				SetWrap(get_InternalChildren()->get_Item(i), true);
			}
			else
			{
				SetWrap(get_InternalChildren()->get_Item(i), false);
			}
		//	m_items[i]->fsState = pData[i].fsState;
		//	m_items[i]->fsStyle = pData[i].fsStyle;
			//m_items[i]->fsState = pData[i].fsState;
			//m_items[i]->fsState = pData[i].fsState;
		}
		/*
		m_items.RemoveAll();

		for (i = 0; i < nCount; i++)
		{
			m_items.Add(items[i]);
		}
		*/

		m_orientation = orientation;
	}
	else
	{
		/*
	// Cleanup
		for (int i = 0; i < items.GetSize(); i++)
		{
			items[i]->Release();
		}
		*/
	}
	//items.RemoveAll();
	delete items;
}

#if 0


long ToolBarPanel::TrackMenu()
{
	ASSERT(0);
	return 0;
}

#if 0
long ToolBarPanel::TrackMenu2()
{
//	ASSERT(m_bParentMsgLoop == FALSE);

//	m_bParentMsgLoop = TRUE;

//		m_pPrevActiveItem = NULL;

//		PopupActiveItem();

//		if (m_activeSubDlg)
	{
		m_bParentMsgLoop = TRUE;
		long result = 0;
		m_result = 0;

		MSG lastMsg;
		bool bLastMsg = FALSE;

#ifdef _DEBUG
		//MessageBeep(-1);
#endif

		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			if (msg.message == WM_MOUSEMOVE ||
				msg.message == WM_LBUTTONDOWN ||
				msg.message == WM_RBUTTONDOWN)
			{
				HWND hWnd2 = WindowFromPoint(msg.pt);
				HWND hWnd = hWnd2;

				ToolBarPanel* pMenu = NULL;
				do
				{
					pMenu = (ToolBarPanel*)GetProp(hWnd, "menudlg");
					if (pMenu)
						break;

					hWnd = ::GetParent(hWnd);
				}
				while (hWnd);

				ToolBarPanel* pTest = this;
				while (pTest)
				{
					if (pMenu == pTest)
						break;

					pTest = pTest->m_activeSubDlg;
				}
				if (pTest == NULL)
					pMenu = NULL;

				if (pMenu)
				{
					pMenu->SetCapture();
				}
				else
				{
					if (msg.message == WM_LBUTTONDOWN ||
						msg.message == WM_RBUTTONDOWN)
					{
						bLastMsg = TRUE;
						lastMsg = msg;
						//lastMsg.hwnd = hWnd2;

						result = -2;	// Cancel
						if (result != 0) break;
					}
				}
			}

			ToolBarPanel* pMenu = NULL;

			if (msg.hwnd)
			{
				HWND hWnd = msg.hwnd;
				do
				{
					pMenu = (ToolBarPanel*)GetProp(hWnd, "menudlg");
					if (pMenu)
						break;

					hWnd = ::GetParent(hWnd);
				}
				while (hWnd);
			}

			if (pMenu)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				result = m_result;
/*	// Had this previously instead of above
					{
						if (m_activeSubDlg)	// ?? When is this NULL ?
							m_activeSubDlg->get_result(&result);
					}
					*/
			}
			else
			{
				switch (msg.message)
				{
				case WM_PAINT:
				case WM_ERASEBKGND:
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					break;

				case WM_ACTIVATE:
				case WM_NCACTIVATE:
				case WM_MOUSEACTIVATE:
					TranslateMessage(&msg);
					DispatchMessage(&msg);

				case WM_NCLBUTTONDOWN:
				case WM_NCLBUTTONDBLCLK:

					/*
				case WM_LBUTTONDOWN:
				case WM_LBUTTONDBLCLK:

				case WM_RBUTTONDOWN:
				case WM_RBUTTONDBLCLK:
				*/
					result = -2;	// Cancel

					bLastMsg = TRUE;
					lastMsg = msg;

					break;

				//	/*
				default:	// TODO remove
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				//	*/
				}
			}

			if (result > 0 && m_selectedID)
			{
#if 0	// TODO, have this
				ASSERT(m_pActiveItem);
#endif
			}
			if (result != 0) break;
		}

		ReleaseCapture();

		//long selectedID = 0;

		if (m_activeSubDlg)
		{
			//m_activeSubDlg->get_selectedID(&selectedID);

			if (m_activeSubDlg->m_pDlgSite/*->m_pDockBar*/ == NULL)
				m_activeSubDlg->DestroyWindow();

			m_activeSubDlg->Release();
			m_activeSubDlg = NULL;
		}

#if 1
		MessageBeep(-1);
#endif

		if (result > 0 && m_selectedID)
		{
			ASSERT(m_pActiveItem);

			DWORD menuType;
			m_pActiveItem->m_menuItem->get_type(&menuType);
			if (menuType & MF_POPUP)
			{
			// Set this menu items command to the selected command
				CComPtr<IUICommand> command;
				m_menuItem->m_uiManager->FindCommand(m_selectedID, &command);
				if (command)
				{
					m_pActiveItem->m_menuItem->put_command(command);
				}
			}
		}

		m_pPrevActiveItem = NULL;
		SetActiveItem(NULL);

		if (m_bDestroy)//if (m_parentMenuDlg/*m_bParentMsgLoop*/)
		{
			DestroyWindow();
			//m_parentMenuDlg = NULL;//m_bParentMsgLoop = FALSE;
		}

		if (result > 0)
		{
		/*
			if (flags & TPM_RETURNCMD)
			{
				*iid = selectedID;
			}
			else if (pWnd || pTarget)
			*/
			{
				if (m_selectedID == 0L)
				{
					/*
					HWND hWnd;
					m_pCmdWnd->get_hwnd(&hWnd);
					*/

				/*
					if (m_selectedID >= 0xF000)	// System menu
					{
						SendMessage(hWnd, WM_SYSCOMMAND,
							MAKEWPARAM(m_selectedID, 0), (LPARAM)NULL);
					}
				*/
				}
				else
				{
					CComQIPtr<ICommandTarget> target = m_pCmdWnd;

					if (target)
					{
						bool bHandled = FALSE;
						target->OnCmdMsg(m_selectedID, (result==1)? 0: BN_DBLCLK, NULL, &bHandled);
					}

				//	SendMessage(hWnd, WM_COMMAND,
				//		MAKEWPARAM(m_selectedID, 0), (LPARAM)NULL);
				}
			}
		}
		else if (bLastMsg)
		{
			TranslateMessage(&lastMsg);
			DispatchMessage(&lastMsg);
		}

		return result;
	}
	return 0;
}

STDMETHODIMP ToolBarPanel::put_result(long newVal)
{
	m_result = newVal;

	if (m_parentMenuDlg)
	{
		m_parentMenuDlg->put_result(m_result);
	}
	return S_OK;
}
#endif

void ToolBarPanel::SizeDispItem(int m_orientation, CToolbarButton* pItem)
{
	HDC hDC = CreateCompatibleDC(NULL);

	/*
	LOGFONT lf;
	GetObject(hDC, sizeof(lf), &lf);
	lf.lfEscapement = 90*10;
	lf.lfOrientation = 90*10;

	HFONT hVerticalFont = CreateFontIndirect(&lf);
	ASSERT(hVerticalFont != NULL);
	*/

	HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);

	HFONT hVerticalFont;
	
	if (m_orientation == 2)
	{
		hVerticalFont = CreateFont(16, 0, -90*10, -90*10, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Verdana");
		SelectObject(hDC, hVerticalFont);
	}
	else
	{
		SelectObject(hDC, (HFONT)GetStockObject(DEFAULT_GUI_FONT));
	}

	_bstr_t text = pItem->m_text;

//	DWORD type;
//	pItem->m_menuItem->get_type(&type);

	//pItem->idCommand = ID;

	if (m_orientation == 2)
	{
		CRect rc(0,0,0,0);
		DrawText(hDC, text, text.length(), &rc, DT_CALCRECT | DT_SINGLELINE);
	//	CRect rc(0,0,40,80);

		pItem->m_size.cx = 2+rc.Height()+2;
		pItem->m_size.cy = 4+rc.Width()+4;
	}
	else if (m_orientation == 0)
	{
		// nothing to do, use m_textWidth, m_itemHeight
	//	pItem->m_size.cx = m_textWidth;
		pItem->m_size.cy = itemHeight;
	}
	else if (m_orientation == 1)
	{
		CRect rc(0,0,0,0);
		DrawText(hDC, text, text.length(), &rc, DT_CALCRECT | DT_SINGLELINE);

		pItem->m_size.cx = 4+rc.Width()+4;
		pItem->m_size.cy = 2+itemHeight+2;
	}
	else if (m_orientation == -1)
	{
		if (pItem->fsStyle & TBSTYLE_SEP)
		{
			pItem->m_size.cx = iBitmap;
			pItem->m_size.cy = 2+18+2;
		}
		else
		{
			// Get max width
			{
				ASSERT(pItem->m_boxList.GetSize()==0);
				ASSERT(pItem->m_pBox == NULL);

	// Force this one, TODO, should allow table also
				pItem->m_computedDisplayModel = DisplayModel_block_inside;

				CHTMFlowBlockContext* pC = new CHTMFlowBlockContext;
				pItem->DistributeWithinBlock(pC, 0x0fffffff);
				ASSERT(pC->m_pBlockBox);

				pItem->m_maxContentWidth = pC->m_maxx;	// ??
				pItem->m_size.cx = pC->m_maxx;
				pItem->m_size.cy = 2+18+2;	// TODO

				delete pC;

			//	m_pBox = NULL;
			//	m_boxList.RemoveAll();
				pItem->RemoveBoxesAndChildren();
			}

#if 0
			long itemWidth = -1;
			long bitmapIndex = pItem->m_bitmapIndex;
			/*
			if (cmd)
			{
				cmd->get_bitmapIndex(&bitmapIndex);
				cmd->get_itemWidth(&itemWidth);
			}
			*/

			pItem->m_size.cx = 0;
			pItem->m_size.cy = 0;

			pItem->m_size.cy = 2+18+2;

			if (bitmapIndex >= 0)	// icon
			{
				pItem->m_size.cx = 2+18+2;
			}
			else if (itemWidth < 0) // Display as text
			{
				SIZE size;
				GetTextExtentPoint32(hDC, text, text.length(), &size);

				pItem->m_size.cx = 2+size.cx+2;
			}

			if (itemWidth > -1)
			{
				pItem->m_controlWidth = itemWidth;
				pItem->m_size.cx += itemWidth;
			}
#endif
		}
	}

#if 0
	if (m_orientation == 0)
	{
		m_textwidth = 0;
		m_shortcutwidth = 0;

		unsigned long nchildren;
		m_menuItem->CountItems(&nchildren);

		m_size.cx = 0;
		m_size.cy = 0;
		int x = 0;
		int y = 0;

		for (unsigned long i = 0; i < nchildren; i++)
		{
			CComQIPtr<IMenuItem> pItem;
			m_menuItem->GetSubMenu(i, &pItem);

			SIZE size;
			BSTR text;
			pItem->get_text(&text);

			if (m_orientation == 0)
			{
				if (text)
				{
					WCHAR* tab = wcschr(text, L'\t');
					if (tab)
					{
						GetTextExtentPoint32(hDC, _bstr_t(text), (tab-text)/2, &size);
						if (size.cx > m_textwidth) m_textwidth = size.cx;

						GetTextExtentPoint32(hDC, _bstr_t(tab+1), wcslen(tab+1), &size);
						if (size.cx > m_shortcutwidth) m_shortcutwidth = size.cx;
					}
					else
					{
						GetTextExtentPoint32(hDC, _bstr_t(text), wcslen(text), &size);
						if (size.cx > m_textwidth) m_textwidth = size.cx;
					}
				}

				y += itemHeight;
			}

			SysFreeString(text);
		}
	}
#endif

	SelectObject(hDC, hOldFont);
	DeleteDC(hDC);

	if (hVerticalFont)
		DeleteObject(hVerticalFont);
}

#if 0
void ToolBarPanel::CreateSizeDispItemsArray(int m_orientation, CArray<CComObject<CToolbarButton>*,CComObject<CToolbarButton>*>& m_items)
{
	//if (m_menuItem)
	{
		{
			for (int i = 0; i < m_items.GetSize(); i++)
			{
				m_items[i]->Release();
			}
			m_items.RemoveAll();
		}
		ASSERT(m_items.GetSize() == 0);

		HDC hDC = CreateCompatibleDC(NULL);

		/*
		LOGFONT lf;
		GetObject(hDC, sizeof(lf), &lf);
		lf.lfEscapement = 90*10;
		lf.lfOrientation = 90*10;

		HFONT hVerticalFont = CreateFontIndirect(&lf);
		ASSERT(hVerticalFont != NULL);
		*/

		HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);

		HFONT hVerticalFont;
		
		if (m_orientation == 2)
		{
			hVerticalFont = CreateFont(16, 0, -90*10, -90*10, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Verdana");
			SelectObject(hDC, hVerticalFont);
		}
		else
		{
			SelectObject(hDC, (HFONT)GetStockObject(DEFAULT_GUI_FONT));
		}

	// Create controls/calculate size of items
		unsigned long nchildren;
		m_menuItem->CountItems(&nchildren);

		for (unsigned long i = 0; i < nchildren; i++)
		{
			CComPtr<IMenuItem> item;
			m_menuItem->GetSubMenu(i, &item);

			CComObject<CToolbarButton>* pItem;
			CComObject<CToolbarButton>::CreateInstance(&pItem);
			pItem->AddRef();
			pItem->m_menuDlg = this;//static_cast<T*>(this);
			pItem->m_menuItem = item;

			item->get_ID(&pItem->idCommand);

			CComPtr<IUICommand> cmd;
			item->get_command(&cmd);

			long ID = 0;
			if (cmd)
			{
				cmd->get_ID(&ID);
			}

			BSTR btext;
			pItem->m_menuItem->get_text(&btext);
			_bstr_t text = _bstr_t(btext, false);

			DWORD type;
			pItem->m_menuItem->get_type(&type);

			if (type & MF_SEPARATOR) pItem->fsStyle |= TBSTYLE_SEP;

			//pItem->idCommand = ID;

			if (m_orientation == 2)
			{
				CRect rc(0,0,0,0);
				DrawText(hDC, text, text.length(), &rc, DT_CALCRECT | DT_SINGLELINE);
			//	CRect rc(0,0,40,80);

				pItem->m_size.cx = 2+rc.Height()+2;
				pItem->m_size.cy = 4+rc.Width()+4;
			}
			else if (m_orientation == 0)
			{
				// nothing to do, use m_textWidth, m_itemHeight
			//	pItem->m_size.cx = m_textWidth;
				pItem->m_size.cy = itemHeight;
			}
			else if (m_orientation == 1)
			{
				CRect rc(0,0,0,0);
				DrawText(hDC, text, text.length(), &rc, DT_CALCRECT | DT_SINGLELINE);

				pItem->m_size.cx = 4+rc.Width()+4;
				pItem->m_size.cy = 2+itemHeight+2;
			}
			else if (m_orientation == -1)
			{
				if (pItem->fsStyle & TBSTYLE_SEP)
				{
					pItem->m_size.cx = iBitmap;
					pItem->m_size.cy = 2+18+2;
				}
				else
				{
					long itemWidth = -1;
					long bitmapIndex = -1;
					if (cmd)
					{
						cmd->get_bitmapIndex(&bitmapIndex);
						cmd->get_itemWidth(&itemWidth);
					}

					pItem->m_size.cx = 0;
					pItem->m_size.cy = 0;

					pItem->m_size.cy = 2+18+2;

					if (bitmapIndex >= 0)	// icon
					{
						pItem->m_size.cx = 2+18+2;
					}
					else if (itemWidth < 0) // Display as text
					{
						SIZE size;
						GetTextExtentPoint32(hDC, text, text.length(), &size);

						pItem->m_size.cx = 2+size.cx+2;
					}

					if (itemWidth > -1)
					{
						pItem->m_controlWidth = itemWidth;
						pItem->m_size.cx += itemWidth;
					}
				}
			}

			m_items.Add(pItem);
		}

		if (m_orientation == 0)
		{
			m_textwidth = 0;
			m_shortcutwidth = 0;

			unsigned long nchildren;
			m_menuItem->CountItems(&nchildren);

			m_size.cx = 0;
			m_size.cy = 0;
			int x = 0;
			int y = 0;

			for (unsigned long i = 0; i < nchildren; i++)
			{
				CComQIPtr<IMenuItem> pItem;
				m_menuItem->GetSubMenu(i, &pItem);

				SIZE size;
				BSTR text;
				pItem->get_text(&text);

				if (m_orientation == 0)
				{
					if (text)
					{
						WCHAR* tab = wcschr(text, L'\t');
						if (tab)
						{
							GetTextExtentPoint32(hDC, _bstr_t(text), (tab-text)/2, &size);
							if (size.cx > m_textwidth) m_textwidth = size.cx;

							GetTextExtentPoint32(hDC, _bstr_t(tab+1), wcslen(tab+1), &size);
							if (size.cx > m_shortcutwidth) m_shortcutwidth = size.cx;
						}
						else
						{
							GetTextExtentPoint32(hDC, _bstr_t(text), wcslen(text), &size);
							if (size.cx > m_textwidth) m_textwidth = size.cx;
						}
					}

					y += itemHeight;
				}

				SysFreeString(text);
			}
		}

		SelectObject(hDC, hOldFont);
		DeleteDC(hDC);

		if (hVerticalFont)
			DeleteObject(hVerticalFont);
	}
}
#endif

void ToolBarPanel::UpdateItems()
{
	if (m_pCmdWnd)
	{
	// First build an array of items to update (in case the target adds/deletes items dynamically)
	/*
		CArray <CMenuItem*, CMenuItem*> items;

		unsigned long nchildren;
		m_menuItem->CountItems(&nchildren);

		for (int i = 0; i < nchildren; i++)
		{
			CComQIPtr<IMenuItem> pItem;
			m_menuItem->GetSubMenu(i, &pItem);
			items.Add(pItem);
		}
*/

#if 0
	// Now update the items
		CComObject<CUICmdUpdate>* pCmdUI;
		CComObject<CUICmdUpdate>::CreateInstance(&pCmdUI);
		if (pCmdUI)
		{
			pCmdUI->AddRef();
#if 0
			pCmdUI->m_dlg = this;
#endif

			unsigned long nchildren;
			m_menuItem->CountItems(&nchildren);

			for (unsigned long i = 0; i < nchildren; i++)
			{
				CComQIPtr<IMenuItem> item;
				m_menuItem->GetSubMenu(i, &item);

				pCmdUI->m_menuItem = item;
				//pCmdUI->m_controlItem = m_items[i]->m_control;
				pCmdUI->m_hwndControl = m_items[i]->m_hWnd;

				//CComPtr<IUICommand> command;
				//item->get_command(&command);
				//if (command)
				{
					long id;
					item->get_ID(&id);

					if (id)
					{
						CComQIPtr<ICommandTarget> target = m_pCmdWnd;
						if (target)
						{
							BOOL bHandled;
							target->OnCmdMsg(id, -1, pCmdUI, &bHandled);
						}
					}
				}
			}

			pCmdUI->Release();
			pCmdUI = NULL;
		}
#endif
	}
}

RECT ToolBarPanel::GetItemRect(CToolbarButton* pItem)
{
	return CRect(pItem->m_pBox->m_outerRect.X, pItem->m_pBox->m_outerRect.Y, pItem->m_pBox->m_outerRect.GetRight(), pItem->m_pBox->m_outerRect.GetBottom());
}

void ToolBarPanel::DrawInsertBar(HDC hDC, int insertIndex)
{
	CRect client;
	GetClientRect(&client);

	int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));
	HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));

	if (m_orientation == 0)
	{
		int y = 4 + floatHeight;
		if (insertIndex > 0)
			y = m_items[insertIndex-1]->m_pBox->m_outerRect.GetBottom();

		POINT pt[] =
		{
			3, y-4,
			3, y+4,
			6, y+1,
			client.right-6, y+1,
			client.right-3, y+4,
			client.right-3, y-4,
			client.right-6, y-1,
			6, y-1,
		};

		Polygon(hDC, pt, 8);
	}
	else
	{
		int x = 4;
		if (insertIndex > 0)
			x = m_items[insertIndex-1]->m_pBox->m_outerRect.GetRight();

		POINT pt[] =
		{
			x-4, 2,
			x+4, 2,
			x+1, 5,
			x+1, client.bottom-7,
			x+4, client.bottom-3,
			x-4, client.bottom-3,
			x-1, client.bottom-7,
			x-1, 5
		};

		Polygon(hDC, pt, 8);
	}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	SetROP2(hDC, oldR2);
}

void ToolBarPanel::SetActiveItem(CToolbarButton* pItem)
{
	ASSERT(m_hWnd);

	if (pItem != m_pActiveItem)
	{
		if (m_pActiveItem)
		{
			RECT rect = GetItemRect(m_pActiveItem);
			InvalidateRect(&rect, TRUE);
		}

		m_pActiveItem = pItem;
		if (m_pActiveItem)
		{
			RECT rect = GetItemRect(m_pActiveItem);
			InvalidateRect(&rect, TRUE);
		}
		else
		{
			ATLTRACE("m_pActiveItem=NULL\n");
		}

		UpdateWindow();
	}
}

void ToolBarPanel::PopupActiveItem()
{
#if 0
	if (m_nTimer)
	{
		KillTimer(m_nTimer);
		m_nTimer = 0;
	}

	if (m_pPrevActiveItem != m_pActiveItem)
	{
		// Destroy any previous child popup menu
		if (m_activeSubDlg != NULL)
		{
			if (m_activeSubDlg->m_pDlgSite/*->m_pDockBar*/ == NULL)
				m_activeSubDlg->DestroyWindow();

			m_activeSubDlg->Release();
			m_activeSubDlg = NULL;
		}

		m_pPrevActiveItem = m_pActiveItem;

		if (m_pActiveItem)
		{
			unsigned long childrencount;
			m_pActiveItem->m_menuItem->CountItems(&childrencount);

			if (childrencount > 0)	// Bring up sub-menu
			{
				DWORD menuType;
				m_pActiveItem->m_menuItem->get_type(&menuType);
				if (menuType & MF_POPUP)
				{
				}

				int index = GetItemIndex(m_pActiveItem);

				RECT client;
				GetClientRect(&client);

				POINT point;

				if (m_orientation == 0)
				{
					point.x = m_items[index]->m_rc.right-4;
					point.y = m_items[index]->m_rc.top;
				}
				else if (m_orientation == 2)
				{
					point.x = m_items[index]->m_rc.right;
					point.y = m_items[index]->m_rc.top;
				}
				else
				{
					point.x = m_items[index]->m_rc.left-4;
					point.y = m_items[index]->m_rc.bottom+2;
				}

				ClientToScreen(&point);

				ASSERT(m_activeSubDlg == NULL);
				CComObject<ToolBarPanel>::CreateInstance(&m_activeSubDlg);
				if (m_activeSubDlg)
				{
					m_activeSubDlg->AddRef();

					//if (m_orientation == 1)	// Menu bar
					{
					// Make it look pushed right away
						InvalidateRect(&GetItemRect(m_pActiveItem), TRUE);
					//	Invalidate();
						UpdateWindow();
					}

					m_activeSubDlg->m_bParentMsgLoop = m_bParentMsgLoop;

					DWORD menuType;
					m_pActiveItem->m_menuItem->get_type(&menuType);

					if (menuType & MF_POPUP)
					{
						m_activeSubDlg->m_orientation = -1;
					}

					m_activeSubDlg->PopupMenu2(m_pActiveItem->m_menuItem, this, m_pCmdWnd, point, m_popupFlags);
				}
			}
		}
	}
#endif
}

#if 0
STDMETHODIMP ToolBarPanel::PopupMenu2(IMenuItem* menuItem, ToolBarPanel* pParentMenuDlg, ICommandTarget *pCmdWnd, POINT point, DWORD flags)
{
	ASSERT(pCmdWnd);

	m_menuItem = static_cast<CMenuItem*>(menuItem);
	m_parentMenuDlg = pParentMenuDlg;

	m_pCmdWnd = pCmdWnd;
	m_popupFlags = flags;

	CreateSizeDispItemsArray(m_orientation, m_items);

	CSize size;
	CalcLayout(LM_MRUWIDTH, 32767, &size);	// TODO, optimize this to work directly on the above m_items ??

	int width;
	int height;
	
	if (m_orientation == 0)
	{
		unsigned long count;
		m_menuItem->CountItems(&count);

		width = 4 + (20 + m_textwidth + 4 + m_shortcutwidth + 20) + 4;
		height = floatHeight + 4 + count*itemHeight + 4;
	}
	else
	{
		width = size.cx;
		height = size.cy;
	}

	RECT screenRect;
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &screenRect, 0);

	RECT menuRect = {point.x, point.y, point.x + width, point.y + height };

	if (menuRect.right > screenRect.right) OffsetRect(&menuRect, -(menuRect.right - screenRect.right), 0);
	if (menuRect.bottom > screenRect.bottom) OffsetRect(&menuRect, 0, -(menuRect.bottom - screenRect.bottom));
	if (menuRect.left < screenRect.left) OffsetRect(&menuRect, (screenRect.left - menuRect.left), 0);
	if (menuRect.top < screenRect.top) OffsetRect(&menuRect, 0, (screenRect.top - menuRect.top));

	HWND ownerHWnd = NULL;

//	m_bParentMsgLoop = TRUE;

	CWindowImpl<ToolBarPanel>::
		Create(
		ownerHWnd,
		CRect(menuRect.left, menuRect.top, menuRect.left+width, menuRect.top+height),
		NULL,
		WS_POPUP,
		WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
		0);

	UpdateItems();

	if (FALSE)
	{
		if (!AnimateWindow(m_hWnd, 150, AW_BLEND/*AW_HOR_POSITIVE | AW_VER_POSITIVE*/))
		{
			ASSERT(0);
		}
	}
	else
	{
		SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
	}

	SetCapture();

	return S_OK;
}
#endif

#if 0
STDMETHODIMP ToolBarPanel::CreateForMenuItem(IMenuItem *menuItem, HWND hParent, ICommandTarget *pCmdWnd, DWORD orientation)
{
	if (m_hWnd)
	{
		ASSERT(IsWindow());
		ASSERT(0);
		return E_FAIL;
	}

	ASSERT(hParent != NULL);
	ASSERT(menuItem != NULL);

	m_menuItem = static_cast<CMenuItem*>(menuItem);
	m_parentMenuDlg = NULL;//pParentMenuDlg;

	m_pCmdWnd = pCmdWnd;
	ASSERT(m_pCmdWnd);
//	m_popupFlags = flags;

	m_orientation = orientation;

//	CalculateMaxWidth((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	RemoveDispItems();
	CreateSizeDispItemsArray(m_orientation, m_items);

//	m_bParentMsgLoop = FALSE;

	CWindowImpl<ToolBarPanel>::Create(hParent, CRect(0,0,0,0), NULL, WS_CHILD, 0, 0);

	UpdateItems();

	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);

	return S_OK;
}
#endif

void ToolBarPanel::SetCommand(CToolbarButton* pItem)
{
	/*
	m_selectedID = pItem->GetCommandID();
	m_result = 1;	// Ok
	*/

	m_selectedID = pItem->idCommand;
#if 0
	put_selectedID(pItem->GetCommandID());

	if (m_bParentMsgLoop)
	{
		put_result(1);	// Ok
	}
	else
#endif
	{
		BOOL bHandled = FALSE;
		CComObject<CUICmdUpdate>* pCmdUI;
		CComObject<CUICmdUpdate>::CreateInstance(&pCmdUI);
		if (pCmdUI)
		{
			pCmdUI->AddRef();
#if 0
			pCmdUI->m_dlg = this;
#endif

//			pCmdUI->m_menuItem = pItem->m_menuItem;
			pCmdUI->m_hwndControl = pItem->m_hWnd;

			m_pCmdWnd->OnCmdMsg(m_selectedID, 0, pCmdUI, &bHandled);

			pCmdUI->Release();
			pCmdUI = NULL;
		}
	}
}

// Same as in CUIMenuDlg
void ToolBarPanel::Draw(HDC hDC)
{
	CDCHandle dc(hDC);

	//Gdiplus::TextureBrush brush(m_pBackgroundBitmap);

	{
		CRect rect;
		GetClientRect(&rect);
		/*
		CRect rect;
		GetWindowRect(&rect);

		//dc.ExcludeClipRect(7, 28, rect.Width()-7, m_pCaptionElement->m_pBox->m_outerRect.Height);

		CRect client;
		GetClientRect(&client);
		ClientToScreen(&client);
		client.OffsetRect(-rect.left, -rect.top);
		dc.ExcludeClipRect(client.left, client.top, client.Width(), client.Height());

		rect.OffsetRect(-rect.left, -rect.top);
		*/

	//	CPElement* pPElement = (CPElement*)CComQIPtr<CLDOMElementImplImpl>(m_element)->m_pNodes[0];

		{
			Gdiplus::Graphics graphics(dc);

			/*
			// Draw background color
			{
				Gdiplus::SolidBrush brush(m_computedBackgroundColor);
				graphics.FillRectangle(&brush, Gdiplus::Rect(rect.left, rect.top, rect.Width(), rect.Height()));
			}
			*/

			/*
			// Draw background image
			if (m_pBackgroundImage)
			{
				Gdiplus::TextureBrush brush(m_pBackgroundImage->m_gdipImage);
				graphics.FillRectangle(&brush, Gdiplus::Rect(rect.left, rect.top, rect.Width(), rect.Height()));
			}
			*/

		//	xThemeDrawEdge(dc, &rect, xTheme_EDGE_RECT, 0);

			CHTMRenderContext pC;
		//	pC.m_pUI = NULL;//m_pWindow->m_pUI;
			pC.m_pWindow = NULL;//m_pWindow;
			pC.m_pGraphics = &graphics;

		#if 0	// ????TODO, have this
			pC.m_clipBox = //clip;
	#endif
			pC.m_clip = Gdiplus::RectF(rect.left, rect.top, rect.Width(), rect.Height());
			//pC.m_clip.Offset(-m_client.left, -m_client.top);

		#if 0	// ????TODO, have this
			pC.m_clipOrig = pC.m_clip;
		#endif

			pC.m_hBrokenImageBitmap = NULL;//m_pWindow->m_hBrokenImageBitmap;

			pC.m_bInSelection = FALSE;
			pC.m_range = NULL;//m_pWindow->m_range;

			pC.m_pStringFormat = Gdiplus::StringFormat::GenericTypographic();

			if (/*m_shadowTree->*/m_pBox)
			{

				//pC.m_pGraphics->TranslateTransform(float(m_bounds.X), float(m_bounds.Y));

				/*m_shadowTree->*/m_pBox->Draw(&pC);

				//pC.m_pGraphics->TranslateTransform(float(-m_bounds.X), float(-m_bounds.Y));
			}
			else
			{
				ASSERT(0);
				//Render4(&pC, NULL, pC.m_pGraphics, m_scaleX/* *magnify*/, m_scaleY/* *magnify*/, FALSE, TRUE);
			}

		//	graphics.Flush(Gdiplus::FlushIntentionSync);
		}
	}
}

LRESULT ToolBarPanel::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	CRect client;
	GetClientRect(&client);

	Draw(dc);

	if (m_dragInsertIndex >= 0)
	{
		DrawInsertBar(dc, m_dragInsertIndex);
	}

	return 0;
}

LRESULT ToolBarPanel::OnPrintClient(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HDC hDC = (HDC)wParam;

	Draw(hDC);

	return 0;
}

LRESULT ToolBarPanel::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
/*		HDC hDC = (HDC)wParam;

	Draw(hDC);
*/
// Do nothing with the background to avoid flickering
	return TRUE;
}

LRESULT ToolBarPanel::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	CPoint screenpt = point;
	ClientToScreen(&screenpt);

	if (m_pOwnedWindow)
	{
		m_pOwnedWindow->OnButtonDown(nFlags, screenpt, point, 0, FALSE, NULL);
	}

#if 0
	int index = IndexFromPoint(point);

	CToolbarButton* pItem = (index >= 0)?m_items[index]: NULL;
	
	SetActiveItem(pItem);

#if 0




	//HWND hWnd = WindowFromPoint(screenpt);
	//if (m_hWnd == hWnd)
	{
		if (m_orientation == 0 && !m_dragging && point.y < 4+floatHeight)
		{
			// Detach the menu

			CComQIPtr<IUIFrame> frame = m_pCmdWnd;
			if (frame)
			{
#if 0
				CComQIPtr<IDlgManager> dlgman;
				frame->get_dlgManager(&dlgman);

				m_selectedID = 0L;
				m_result = ID_CANCEL;

				CRect wrect;
				GetWindowRect(&wrect);

				DestroyWindow();

				{
					m_parentMenuDlg = NULL;
					m_bParentMsgLoop = FALSE;

					ASSERT(0);
					// The following
#if 0
					// Create sheet
					CComObject<CDlgSheet>* sheet;
					CComObject<CDlgSheet>::CreateInstance(&sheet);
					sheet->AddRef();
					sheet->m_dlgManager = dlgman;

					static_cast<CDlgManager*>(dlgman.p)->m_pSheets.AddTail(sheet);

				// Add us to the sheet
					sheet->AddPage(this);

				// Show sheet
					BOOL b;
					sheet->Create(CRect(0,0,200, 20), &b);

					sheet->SetWindowPos(NULL, wrect.left, wrect.top, wrect.Width()+8, wrect.Height()+20, SWP_NOZORDER);
#endif
				}

				BSTR text;
				m_menuItem->get_text(&text);

				CComPtr<IUIRegisteredDlg> dlgclass;
				m_menuItem->m_uiManager->RegisterMenuDlg(0, text, 0, &dlgclass);

				SysFreeString(text);

			//	SendMessage(hwndsheet, WM_NC
#endif
			}
		}
		else
		{
			int index = IndexFromPoint(point);

			CToolbarButton* pItem = (index >= 0)?m_items[index]: NULL;

			if (pItem)
				m_dragging = 1;

			if (/*m_parentMenuDlg == NULL*/m_bParentMsgLoop == FALSE)	// top-level menu
			{
				if (m_activeSubDlg == NULL)
				{
					SetActiveItem(pItem);	// ??
					if (pItem)
					{
						m_bParentMsgLoop = TRUE;

						m_pPrevActiveItem = NULL;

						PopupActiveItem();

						if (m_activeSubDlg)
						{
							long result = TrackMenu2();
						}

						m_bParentMsgLoop = FALSE;
						//long result = TrackMenu();
					}
				}
				else
				{
					if (m_pActiveItem == pItem)	// Toggle off
					{
#if 0
						SetActiveItem(pItem);	// ??
#endif
						/*m_activeSubDlg->*/put_result(-2);	// Cancel

						// Destroy any previous child popup menu
						if (m_activeSubDlg != NULL)
						{
							if (m_activeSubDlg->m_pDlgSite/*->m_pDockBar*/ == NULL)
								m_activeSubDlg->DestroyWindow();

							m_activeSubDlg->Release();
							m_activeSubDlg = NULL;
						}

						SetActiveItem(NULL);
					//	m_activeSubDlg->m_result = -2;	// Cancel
						//m_selectedID = -1;	// Cancel
					}
					else
					{
						if (pItem)
						{
							PopupActiveItem();
						}
						else
						{
							/*m_activeSubDlg->*/put_result(-2);	// Cancel
						}
					}
				}
			}
			else	// Clicked on Submenu->item
			{
				SetActiveItem(pItem);
				PopupActiveItem();
			}

			if (pItem)
			{
				/*
				unsigned long childrencount;
				m_pActiveItem->m_menuItem->CountItems(&childrencount);

				CComPtr<IUIManager> uiManager;
				m_menuItem->get_uiManager(&uiManager);

				BOOL bDesignMode = FALSE;
				if (uiManager)
					uiManager->get_DesignMode(&bDesignMode);

				if (bDesignMode)
				{
					PopupActiveItem();
				}
				else
				*/
			}
		}
	}
	/*
	else
	{
		//ReleaseCapture();
		m_selectedID = -2;
	}
	*/
#endif
#endif

	return 0;
}

LRESULT ToolBarPanel::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

#if 0
	if (m_dragging)
#endif
	{
		m_dragging = 0;

		//CComQIPtr<IMenuItem> pItem;// = NULL;
		//if (m_pActiveItem) pItem = m_pActiveItem;

		if (m_pActiveItem)
		{
#if 0
			unsigned long childrencount;
			m_pActiveItem->m_menuItem->CountItems(&childrencount);
			if (childrencount == 0)
#endif
			{
				SetCommand(m_pActiveItem);
			}
		}
	}

	return 0;
}

LRESULT ToolBarPanel::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	CPoint screenpt = point;
	ClientToScreen(&screenpt);

	CRect client;
	GetClientRect(&client);

	bool bInsideWindow = point.x >= 0 && point.y >= 0 && point.x < client.right && point.y < client.bottom;
	if (bInsideWindow != m_bInsideWindow)
	{
		m_bInsideWindow = bInsideWindow;
		if (m_bInsideWindow)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = m_hWnd;
			tme.dwFlags = TME_LEAVE;
			tme.dwHoverTime = 0;
			TrackMouseEvent(&tme);
		}
	}

	if (m_pOwnedWindow)
	{
		m_pOwnedWindow->OnMouseMove(nFlags, screenpt, point);
	}

	Invalidate();	// TODO remove

#if 0
	int index = IndexFromPoint(point);

	if (index >= 0)
	{
		CToolbarButton* pItem = m_items[index];

		if (pItem != m_pActiveItem)
		{
			//DWORD type;
			//pItem->m_menuItem->get_type(&type);

			if (!(pItem->fsStyle & TBSTYLE_SEP))
			{
				if (m_nTimer)
				{
					KillTimer(m_nTimer);
					m_nTimer = 0;
				}

				SetActiveItem(pItem);

				m_nTimer = SetTimer(1, 500);

				if (m_parentMenuDlg == NULL)
				{
					if (m_activeSubDlg != NULL)
					{
						PopupActiveItem();
					}
				}
			}
		}
	}
	else
	{
		if (m_activeSubDlg == NULL)
			SetActiveItem(NULL);
	}
#endif

	return 0;
}

LRESULT ToolBarPanel::OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_bInsideWindow = FALSE;

	if (m_activeSubDlg == NULL)
		SetActiveItem(NULL);

	return 0;
}

LRESULT ToolBarPanel::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ASSERT(0);
#if 0
	CToolbarButton* pItem = m_pActiveItem;

	if (pItem)
	{
		/*
		put_selectedID(pItem->GetCommandID());
		put_result(2);	// Ok double click
		*/

		//if (m_bParentMsgLoop)
		{
			ReleaseCapture();
			//DestroyWindow();
			//m_bParentMsgLoop = FALSE;
		}

		put_result(-2);	// Cancel

		BOOL bHandled = FALSE;
		CComObject<CUICmdUpdate>* pCmdUI;
		CComObject<CUICmdUpdate>::CreateInstance(&pCmdUI);
		if (pCmdUI)
		{
			pCmdUI->AddRef();

#if 0
			pCmdUI->m_dlg = this;
			pCmdUI->m_menuItem = pItem->m_menuItem;
#endif
			pCmdUI->m_hwndControl = pItem->m_hWnd;

			m_pCmdWnd->OnCmdMsg(pItem->GetCommandID(), BN_DBLCLK, pCmdUI, &bHandled);

			pCmdUI->Release();
			pCmdUI = NULL;
		}
	}
#endif

	return 0;
}
#endif

void ToolBarPanel::PlaceItems()
{
	LDraw::PointD cur(0,0);

	unsigned int ncount = get_InternalChildren()->GetCount();

	for (unsigned int i = 0; i < ncount; i++)
	{
		UIElement* pItem = get_InternalChildren()->get_Item(i);

		LDraw::SizeD size;

		int cySep = 12;//pData[i].iBitmap;
		cySep = cySep * 2 / 3;

		/*
		CHTMFlowBlockContext* pC2 = new CHTMFlowBlockContext;

		pPElement->DistributeWithinBlock(pC2, pItem->m_size.cx);

		ASSERT(pPElement->m_pBox);
		ASSERT(pC2->m_pBlockBox);
		ASSERT(pC2->m_pBlockBox == pPElement->m_pBox);

		//pPElement->m_heightLeft = pC2->m_pBlockBox->m_innerRect.Height;

		pC2->m_pBlockBox->m_outerRect = pC2->m_pBlockBox->m_innerRect;
		//pC2->m_pBlockBox->m_outerRect.Offset(x, rowTop);

		pC2->m_pBlockBox->AdjustOuterRect();

		delete pC2;

		pItem->CreateBlockBox();
		*/
		/*
		ASSERT(pItem->m_boxList.GetSize()==0);
		ASSERT(pItem->m_pBox == NULL);

		pItem->m_computedDisplayModel = DisplayModel_block_inside;

		CHTMFlowBlockContext* pC = new CHTMFlowBlockContext;
		pItem->DistributeWithinBlock(pC, 0x0fffffff);
		ASSERT(pC->m_pBlockBox);
		ASSERT(pItem->m_pBox == pC->m_pBlockBox);
		*/

		Size desiredSize = pItem->get_DesiredSize();
	//size;// = pItem->m_size;
		size.Width = desiredSize.Width;
		size.Height = desiredSize.Height;

		LDraw::RectD rc;
		rc.X = cur.X;
		rc.Y = cur.Y;
		rc.Width = /*2+cur.x+*/size.Width;
		rc.Height = /*2+cur.y+*/size.Height;

		pItem->Arrange(rc/*size*/);
	//	pItem->SetLayoutOffset(rc.X, rc.Y);

		//	pItem->m_pBox->m_outerRect.X = rc.left;
		//	pItem->m_pBox->m_outerRect.Y = rc.top;

		//	m_pBox->AddChildBox(pItem->m_pBox);

		/*
		cur.x += size.cx;

		if (pItem->fsState & TBSTATE_WRAP)
		{
			cur.x = 0;
			cur.y += 2+18+2;
		}
		*/
		if (false/*pItem->fsStyle & TBSTYLE_SEP*/)
			cur.X += /*pData[i].*/iBitmap;
		else
			cur.X += pItem->get_ActualSize().Width/*m_pBox->m_outerRect.Width*/ - CX_OVERLAP;

		// TODO
		if (GetWrap(pItem)/*pItem->fsState & TBSTATE_WRAP*/)
		{
		//	ASSERT(0);

			int itemHeight = 18;
			cur.X = 0;
			cur.Y += itemHeight+2;//m_sizeButton.cy;

			if (false/*pItem->fsStyle & TBSTYLE_SEP*/)
				cur.Y += cySep;
		}
	}

#if 0
	ASSERT(::IsWindow(m_hWnd));

	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

	HDC hDC = CreateCompatibleDC(NULL);
	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	CRect client;
	GetClientRect(&client);

	unsigned long nchildren = m_items.GetSize();

	CPoint cur(0,0);

	CHTMFlowBlockContext pC;
	//pC.m_frameClient = m_client;

	/*m_shadowTree->*/m_specifiedWidth = client.Width();//m_computedWidth;// = cx;
	/*m_shadowTree->*/m_specifiedHeight = client.Height();//lpncsp->bottom-lpncsp->top;//m_computedHeight;// = cy;
//		m_computedOverflowX = Overflow_hidden;
	/*m_shadowTree->*/m_computedDisplayModel = DisplayModel_block_inside;	// ??
//	m_bVScroll = false;	// Always vertical scrollbar on outer element (TODO unless specified)

	pC.m_pBlockBox = NULL;
	pC.m_pCurLineBox = NULL;
	pC.m_pPrevLeftFloatBox = NULL;

	pC.m_floatBottom = 0;
	pC.m_curpos.X = pC.m_curpos.Y = 0;
	pC.m_linepos.X = pC.m_linepos.Y = 0;
	pC.m_maxx = 0;

	m_pBox = CreateBlockBox();	// Principal box
	ASSERT(pC.m_pBlockBox == NULL);
	pC.m_pBlockBox = m_pBox;

	m_pBox->m_innerRect.Width = m_specifiedWidth;
	m_pBox->m_innerRect.Height = m_specifiedHeight;
	m_pBox->m_outerRect.Width = m_pBox->m_innerRect.Width;
	m_pBox->m_outerRect.Height = m_pBox->m_innerRect.Height;

//	/*m_shadowTree->*/DistributeWithinBlock(&pC, client.Width());

	for (unsigned long i = 0; i < nchildren; i++)
	{
		CToolbarButton* pItem = m_items[i];
		//CComQIPtr<IMenuItem> item = pItem->m_menuItem;

		SIZE size;
		BSTR text = pItem->m_text;
		//item->get_text(&text);

		if (m_orientation == 2)	// top to bottom - vertical text
		{
			ASSERT(0);
#if 0
			size = pItem->m_size;

			pItem->m_rc.left = 2+cur.x;
			pItem->m_rc.top = 2+cur.y;
			pItem->m_rc.bottom = 2+cur.y+size.cy;
			pItem->m_rc.right = 2+cur.x+size.cx;

			cur.y += size.cy;
#endif
		}
		else if (m_orientation == 0)	// top to bottom
		{
			ASSERT(0);
#if 0
			pItem->m_rc.top = floatHeight + 4 + cur.y;
			pItem->m_rc.left = 4;
			pItem->m_rc.right = 4 + 20 + m_textwidth + 4 + m_shortcutwidth + 20;

			cur.y += pItem->m_size.cy;//itemHeight;

			pItem->m_rc.bottom = floatHeight + 4 + cur.y;
#endif
		}
		else if (m_orientation == 1)	// left to right
		{
			ASSERT(0);
#if 0
			if (pItem->fsStyle & TBSTYLE_SEP)
			{
			}
			else
			{
			}

			size = pItem->m_size;

			pItem->m_rc.left = 2+cur.x;
			pItem->m_rc.top = 2+cur.y;
			pItem->m_rc.bottom = 2+cur.y+size.cy;
			pItem->m_rc.right = 2+cur.x+size.cx;

			cur.x += size.cx;

			if (pItem->fsState & TBSTATE_WRAP)
			{
				cur.x = 0;
				cur.y += itemHeight+2;
			}
#endif
		}
		else if (m_orientation == -1)	// rows and columns
		{
			int cySep = 12;//pData[i].iBitmap;
			cySep = cySep * 2 / 3;

			/*
			CHTMFlowBlockContext* pC2 = new CHTMFlowBlockContext;

			pPElement->DistributeWithinBlock(pC2, pItem->m_size.cx);

			ASSERT(pPElement->m_pBox);
			ASSERT(pC2->m_pBlockBox);
			ASSERT(pC2->m_pBlockBox == pPElement->m_pBox);

			//pPElement->m_heightLeft = pC2->m_pBlockBox->m_innerRect.Height;

			pC2->m_pBlockBox->m_outerRect = pC2->m_pBlockBox->m_innerRect;
			//pC2->m_pBlockBox->m_outerRect.Offset(x, rowTop);

			pC2->m_pBlockBox->AdjustOuterRect();

			delete pC2;

			pItem->CreateBlockBox();
			*/
			{
				ASSERT(pItem->m_boxList.GetSize()==0);
				ASSERT(pItem->m_pBox == NULL);

				pItem->m_computedDisplayModel = DisplayModel_block_inside;

				CHTMFlowBlockContext* pC = new CHTMFlowBlockContext;
				pItem->DistributeWithinBlock(pC, 0x0fffffff);
				ASSERT(pC->m_pBlockBox);
				ASSERT(pItem->m_pBox == pC->m_pBlockBox);

			//size;// = pItem->m_size;
				size.cx = pItem->m_pBox->m_outerRect.Width;
				size.cy = pItem->m_pBox->m_outerRect.Height;

				CRect rc;
				rc.left = 2+cur.x;
				rc.top = 2+cur.y;
				rc.bottom = 2+cur.y+size.cy;
				rc.right = 2+cur.x+size.cx;

				pItem->m_pBox->m_outerRect.X = rc.left;
				pItem->m_pBox->m_outerRect.Y = rc.top;

				m_pBox->AddChildBox(pItem->m_pBox);
			}

			/*
			cur.x += size.cx;

			if (pItem->fsState & TBSTATE_WRAP)
			{
				cur.x = 0;
				cur.y += 2+18+2;
			}
			*/
			if (pItem->fsStyle & TBSTYLE_SEP)
				cur.x += /*pData[i].*/iBitmap;
			else
				cur.x += pItem->m_pBox->m_outerRect.Width - CX_OVERLAP;

			if (pItem->fsState & TBSTATE_WRAP)
			{
				cur.x = 0;
				cur.y += itemHeight+2;//m_sizeButton.cy;

				if (pItem->fsStyle & TBSTYLE_SEP)
					cur.y += cySep;
			}

			// Set tool rect
			if (pItem->GetCommandID())
			{
#if 0
				m_toolTipCtrl.SetToolRect(m_hWnd, pItem->GetCommandID(), &pItem->m_rc);
#endif
			}
		}

		/*
		if (pItem->m_axcontrol)
		{
			pItem->m_axcontrol->MoveWindow(&pItem->m_rc, TRUE);
		}
		*/
		if (pItem->m_hWnd)
		{
#if 0
			CComPtr<IUICommand> cmd;
			item->get_command(&cmd);

			BSTR bwindowClassname;
			cmd->get_windowClassname(&bwindowClassname);
			_bstr_t windowClassname = _bstr_t(bwindowClassname, false);

			int height = pItem->m_rc.Height();

			if (!wcsicmp(windowClassname, L"combobox"))
				height += 260;

			::SetWindowPos(pItem->m_hWnd, NULL, pItem->m_rc.left+(pItem->m_rc.Width()-pItem->m_controlWidth), pItem->m_rc.top, pItem->m_controlWidth, height, SWP_NOZORDER | SWP_NOACTIVATE);
#endif
		}
	}
#endif
}

#if 0
int ToolBarPanel::IndexFromPoint(POINT point)
{
	/*
	if (m_orientation == 0)
	{
		return (point.y-4-floatHeight)/itemHeight;
	}
	else if (m_orientation == 1)
	{
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			if (point.x < m_items[i]->m_rc.right)
				return i;
		}
	}
	else
		*/
	{
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			if (m_items[i]->m_pBox->m_outerRect.Contains(point.x, point.y))
				return i;
		}
	}

	return -1;
}

LRESULT ToolBarPanel::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (TRUE)	// ??
	{
		RemoveBoxesAndChildren();
		PlaceItems();
	}

	ASSERT(m_pBox);

	InvalidateRect(NULL, TRUE);

	return 0;
}

// IDropTarget
STDMETHODIMP ToolBarPanel::DragOver(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
#if 0
	POINT point;
	point.x = pt.x;
	point.y = pt.y;
	ScreenToClient(&point);

	HDC hDC = GetDC();

// Erase previous insert bar
	if (m_dragInsertIndex >= 0)
	{
		DrawInsertBar(hDC, m_dragInsertIndex);
		m_dragInsertIndex = -1;
	}

	BOOL bHandled;
	OnMouseMove(WM_MOUSEMOVE, 0, MAKELPARAM(point.x, point.y), bHandled);
	PopupActiveItem();

	unsigned long subitems;
	m_menuItem->CountItems(&subitems);

	if (m_orientation == 0)
	{
		m_dragInsertIndex = ((point.y-4-floatHeight) + itemHeight/2)/itemHeight;
	}
	else
	{
		m_dragInsertIndex = m_items.GetSize();

		for (int i = 0; i < m_items.GetSize(); i++)
		{
			if (point.x+m_items[i]->m_rc.Width()/2 < m_items[i]->m_rc.right)
			{
				m_dragInsertIndex = i;
				break;
			}
		}
	}

	if (m_dragInsertIndex < 0) m_dragInsertIndex = 0;
	else if (m_dragInsertIndex > (int)subitems) m_dragInsertIndex = (int)subitems;
	
// Draw new insert bar
	if (m_dragInsertIndex >= 0)
	{
		DrawInsertBar(hDC, m_dragInsertIndex);
	}

	ReleaseDC(hDC);

	*pdwEffect = DROPEFFECT_COPY | DROPEFFECT_MOVE;
#endif
	return S_OK;
}

STDMETHODIMP ToolBarPanel::DragLeave()
{
	HWND hwnd;
	get_hwnd(&hwnd);

	HDC hDC = GetDC();

// Erase previous insert bar
	if (m_dragInsertIndex >= 0)
	{
		DrawInsertBar(hDC, m_dragInsertIndex);
		m_dragInsertIndex = -1;
	}

	ReleaseDC(hDC);

	return S_OK;
}

STDMETHODIMP ToolBarPanel::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
#if 0
	HDC hDC = GetDC();

// Erase previous insert bar
	if (m_dragInsertIndex >= 0)
	{
		DrawInsertBar(hDC, m_dragInsertIndex);
	}

	//ReleaseDC(hDC);

/*
	POINT point;
	point.x = pt.x;
	point.y = pt.y;
	ScreenToClient(&point);
*/

#if 0
	ReleaseCapture();
#endif

	COleDataObjectWrapper dataObject;
	dataObject.Attach(pDataObject);

	HGLOBAL hData;

	if (hData = dataObject.GetGlobalData(CF_HDROP))
	{
#if 0
		DROPFILES* dp = (DROPFILES*)GlobalLock(hData);
		if (dp)
		{
			char* p = (char*)(dp+1);

			int i = 0;
			TCHAR filename[512];
			while (*p)
			{
				filename[i++] = *p++;
			}
			filename[i] = 0;
		}

		GlobalUnlock(hData);
#endif

		*pdwEffect = DROPEFFECT_COPY;
	}
	else if (hData = dataObject.GetGlobalData(RegisterClipboardFormat("MMStudio-Command")))
	{
		long* pguid = (long*)GlobalLock(hData);
		long guid = *pguid;

		//CComQIPtr<IUIContextManager> uiManager;
		//m_menuItem->get_uiManager(&uiManager);

		//m_uiManager

		CComQIPtr<IUICommand> command;
		m_menuItem->m_uiManager->FindCommand(guid, &command);
		if (command)
		{
			CComObject<CMenuItem>* item;
			CComObject<CMenuItem>::CreateInstance(&item);

			item->put_type(MF_STRING);
			item->put_command(command);

			m_menuItem->InsertBefore(m_dragInsertIndex, item);

			if (m_pDlgSite/*->m_pDockBar*/ == NULL)
			{
				RemoveDispItems();
				CreateSizeDispItemsArray(m_orientation, m_items);

				PlaceItems();

				int width;
				int height;
	
				if (m_orientation == 0)
				{
					unsigned long count;
					m_menuItem->CountItems(&count);

					width = 4 + (20 + m_textwidth + 4 + m_shortcutwidth + 20) + 4;
					height = floatHeight + 4 + count*itemHeight + 4;
				}
				else
				{
					CSize size;
					CalcLayout(LM_MRUWIDTH/* | LM_COMMIT*/, 32767, &size);

					width = size.cx;
					height = size.cy;
				}

				SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
			}
			else
			{
				ASSERT(0);
			}
#if 0
			CalculateMaxWidth((HFONT)GetStockObject(DEFAULT_GUI_FONT));

			unsigned long count;
			m_menuItem->CountItems(&count);

		// Resize window
			int width = m_textwidth + 30 + m_shortcutwidth + 24;

			int endWidth = width;
			int endHeight = floatHeight + 4 + count*itemHeight + 4;

			SetWindowPos(hwnd, NULL, 0, 0, endWidth, endHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
#endif
		}
		else
		{
			::MessageBox(NULL, "This command is not registered in the UIManager", "MMStudio", MB_OK);
		}

		GlobalUnlock(hData);

		*pdwEffect = DROPEFFECT_COPY;
	}

	m_dragInsertIndex = -1;
#endif

	return S_OK;
}
#endif

}	// UI
}
