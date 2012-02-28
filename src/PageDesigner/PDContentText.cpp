#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDContentText.h"

#include "PDDocument.h"

#include "PDMatrix.h"
#include "ObjectMap.h"
#include "PDLayer.h"-
#include "PDObjectGroup.h"
#include "PDObjectShape.h"
#include "PDPath.h"
#include "PDSubPath.h"
#include "PDStory.h"

//////////////////////////////////////
//

Gdiplus::GraphicsPath* GetFramePath(CPDPath* pdpath, CPDMatrix* pdmatrix)
{
	Gdiplus::GraphicsPath* path = new Gdiplus::GraphicsPath;

	pdpath->RenderToGraphicsPath(path);

	if (pdmatrix)
	{
		Gdiplus::Matrix matrix(
			pdmatrix->m_matrix[0][0], pdmatrix->m_matrix[0][1],
			pdmatrix->m_matrix[1][0], pdmatrix->m_matrix[1][1],
			pdmatrix->m_matrix[2][0], pdmatrix->m_matrix[2][1]);

		path->Transform(&matrix);
	}

	return path;
}

/////////////////////////////
// CSpaceBox

void CSpaceBox::CalculateDimensions(CContentTextContext* pC, double sizeFactor)
{
	ATLASSERT(pC->m_pFont);

	Gdiplus::RectF size(0,0,0,0);
	pC->m_pGraphics->MeasureString(&m_ch, 1, pC->m_pFont, Gdiplus::PointF(0,0), /*pStringFormat,*/ &size);

	if (m_ch == L' ')	// space
	{
		m_innerRect.Width = size.Width;
		m_innerRect.Height = size.Height;
	}
	else if (m_ch == L'\t')
	{
		CArray<double,double> m_tabStops;

		{
			double tabpos = 20;
			m_tabStops.Add(tabpos); tabpos += 20;
			m_tabStops.Add(tabpos); tabpos += 20;
			m_tabStops.Add(tabpos); tabpos += 20;
			m_tabStops.Add(tabpos); tabpos += 20;
			m_tabStops.Add(tabpos); tabpos += 20;
			m_tabStops.Add(tabpos); tabpos += 20;
			m_tabStops.Add(tabpos); tabpos += 20;
			m_tabStops.Add(tabpos); tabpos += 20;
			m_tabStops.Add(tabpos); tabpos += 20;
			m_tabStops.Add(tabpos); tabpos += 20;
		}

		for (int ntab = 0; ntab < m_tabStops.GetSize(); ntab++)
		{
			if (m_tabStops[ntab] > pC->m_x) break;
		}

		double tabpos;

		if (ntab < m_tabStops.GetSize())
		{
			tabpos = m_tabStops[ntab];
		}
		else
		{
			double defaultTabpos = 20;
			tabpos = (int)((pC->m_x+defaultTabpos)/defaultTabpos)*defaultTabpos;
		}

		m_innerRect.Width = tabpos - pC->m_x;
		m_innerRect.Height = size.Height;
	}

	m_innerRect.Width *= sizeFactor;
	m_innerRect.Height *= sizeFactor;
}

void CSpaceBox::Render(CContentTextContext* pC)
{
	if (pC->m_pContentText->m_pDocument->m_showHiddenCharacters)
	{
		Gdiplus::RectF rc = GetAbsInnerRect();

		CComPtr<IPDLayer> layer;
		pC->m_pContentText->get_layer(&layer);
		COLORREF clr;
		layer->get_color(&clr);

		Gdiplus::SolidBrush brush(Gdiplus::Color(GetRValue(clr), GetGValue(clr), GetBValue(clr)));

		if (m_ch == L' ')	// space
		{
			Gdiplus::RectF rc2(rc.X+(rc.Width-rc.Width/3)/2, rc.Y+(rc.Height-rc.Height/10)/2, rc.Width/3, rc.Height/10);
			pC->m_pGraphics->FillRectangle(&brush, rc2);
		}
		else if (m_ch == L'\t')	// tab
		{
			Gdiplus::PointF pts[] =
			{
				Gdiplus::PointF(rc.X+rc.Width-rc.Width/4, rc.Y+rc.Height/2-rc.Height/4),
				Gdiplus::PointF(rc.X+rc.Width-rc.Width/4, rc.Y+rc.Height/2+rc.Height/4),
				Gdiplus::PointF(rc.X+rc.Width-rc.Width/16, rc.Y+rc.Height/2),
			};
			pC->m_pGraphics->FillPolygon(&brush, pts, 3);

			Gdiplus::RectF rc2(rc.X+rc.Width/16, rc.Y+(rc.Height-rc.Height/10)/2, rc.Width/16-rc.Width/4, rc.Height/10);
			pC->m_pGraphics->FillRectangle(&brush, rc2);
		}
	}
}

void CSpaceBox::RenderSelection(CContentTextContext* pContext, HDC hDC, IPDMatrix* matrix, ILDOMRange* range)
{
	double charOffsets[2] = {0, m_innerRect.Width };
	CTextContentBox::RenderSelection(pContext, hDC, matrix, range, 1, charOffsets);
}

//////////////////////////////
// CWordBox

void CWordBox::CalculateDimensions(CContentTextContext* pC, double sizeFactor)
{
	ATLASSERT(pC->m_pFont);

	const Gdiplus::StringFormat* pStringFormat = Gdiplus::StringFormat::GenericTypographic();

	m_charOffsets.RemoveAll();

	m_innerRect.Width = 0;
	m_innerRect.Height = 0;

	for (int i = 0; i < m_text.length(); i++)
	{
		m_charOffsets.Add(m_innerRect.Width);

		WCHAR ch2[2] = {((BSTR)m_text)[i], 0};

		Gdiplus::RectF size(0,0,0,0);
		pC->m_pGraphics->MeasureString(ch2, 1, pC->m_pFont, Gdiplus::PointF(0,0), pStringFormat, &size);

		m_innerRect.Width += size.Width;
		m_innerRect.Height = size.Height;
	}

	m_charOffsets.Add(m_innerRect.Width);

	m_innerRect.Width *= sizeFactor;
	m_innerRect.Height *= sizeFactor;
}

Gdiplus::Brush* GetGdiBrush(IPDBrush* brush, PDBrushType brushType = BRUSH_NONE);

//virtual
void CWordBox::Render(CContentTextContext* pC)
{
	CElement* pElement = GetElement();

	Gdiplus::RectF rc = GetAbsInnerRect();

	const Gdiplus::StringFormat* pStringFormat = Gdiplus::StringFormat::GenericTypographic();

	Gdiplus::GraphicsPath path;

	Gdiplus::FontFamily family;
	pC->m_pFont->GetFamily(&family);

	float emHeight = ConvertSpecifiedValueToUserUnit(UNIT_PT, pC->m_pFont->GetSize());

	for (int i = 0; i < m_text.length(); i++)
	{
		path.AddString(
			&((BSTR)m_text)[i], 1,

			&family,
			Gdiplus::FontStyleRegular,
			emHeight,

			Gdiplus::PointF(rc.X+m_charOffsets[i], rc.Y),
			pStringFormat);
	}

//	(pElement->m_fillColor);

	if (pC->m_pFillBrush)
		pC->m_pGraphics->FillPath(pC->m_pFillBrush, &path);

	if (pC->m_pStrokePen)
		pC->m_pGraphics->DrawPath(pC->m_pStrokePen, &path);

	/*
	Gdiplus::Brush *pBrush;
	
	pBrush = GetGdiBrush(pC->m_fillBrush);
	if (pBrush)
	{
		pC->m_pGraphics->FillPath(pBrush, &path);
		delete pBrush;
	}

	pBrush = GetGdiBrush(pC->m_strokeBrush);
	if (pBrush)
	{
		{
			Gdiplus::Pen pen(pBrush, pElement->m_strokeWidth);
			pC->m_pGraphics->StrokePath(&pen, &path);
		}
		delete pBrush;
	}
	*/

	/*
//	pContext->m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(rand()%255, 0, 0)), rc);


	for (int i = 0; i < m_text.length(); i++)
	{
		pC->m_pGraphics->DrawString(&((BSTR)m_text)[i], 1, pC->m_pFont, Gdiplus::PointF(rc.X+m_charOffsets[i], rc.Y), pStringFormat, &blackBrush);
	}
	*/
}

void CTextContentBox::RenderSelection(CContentTextContext* pContext, HDC hDC, IPDMatrix* matrix, ILDOMRange* range, int length, double* m_charOffsets)
{
	CComPtr<ILDOMNode> startContainer;
	long startOffset;

	CComPtr<ILDOMNode> endContainer;
	long endOffset;

	range->get_startContainer(&startContainer);
	range->get_startOffset(&startOffset);

	range->get_endContainer(&endContainer);
	range->get_endOffset(&endOffset);

	int startChar;
	int endChar = -1;

	if (!pContext->m_bInSelection)
	{
		CComQIPtr<ILDOMText> text = m_node;
		BSTR b;
		text->get_data(&b);
		int len = SysStringLen(b);
		SysFreeString(b);

		// Check for start of selection
		if ((startContainer == m_node) &&
				(startOffset >= m_start) &&
				(
					(startOffset < m_start+length) ||
					(m_start+length == len && startOffset == m_start+length)))
		{
			pContext->m_bInSelection = TRUE;
			startChar = startOffset - m_start;
		}
		else
			startChar = -1;
	}
	else
		startChar = 0;

	if (pContext->m_bInSelection)
	{
		// Check for end of selection
		if ((endContainer == m_node) &&
			(endOffset >= m_start && endOffset <= m_start+length))
		{
			ATLASSERT(endOffset >= m_start);

			pContext->m_bInSelection = FALSE;
			endChar = endOffset - m_start;
		}
		else
		{
			endChar = length;
		}
	}

	if (startChar >= 0 && endChar >= 0)
	{
		Gdiplus::RectF rc = GetAbsInnerRect();

		Gdiplus::RectF rect;

		if (startChar == endChar)
		{
			rect.X = rc.X + m_charOffsets[startChar];
			rect.Y = rc.Y;
			rect.Width = 2;
			rect.Height = rc.Height;
		}
		else
		{
			rect.X = rc.X + m_charOffsets[startChar];
			rect.Y = rc.Y;
			rect.Width = m_charOffsets[endChar]-m_charOffsets[startChar];
			rect.Height = rc.Height;
		}

		PointD pt[4] =
		{
			rect.X, rect.Y,
			rect.X+rect.Width, rect.Y,
			rect.X+rect.Width, rect.Y+rect.Height,
			rect.X, rect.Y+rect.Height,
		};

		CComQIPtr<IPDObject> parent = pContext->m_pContentText->m_parent;

		CComPtr<IPDMatrix> ctm0;
		parent->getScreenCTM(&ctm0);

		CComPtr<IPDMatrix> ctm;
		ctm0->multiply(matrix, &ctm);

		POINT xpt[4];

		for (int i = 0; i < 4; i++)
		{
			PointD dxpt;
			ctm->transformPoint(&pt[i], &dxpt);

			xpt[i].x = dxpt.x;
			xpt[i].y = dxpt.y;
		}

		Polygon(hDC, xpt, 4);
	}
}

//
void CWordBox::RenderSelection(CContentTextContext* pContext, HDC hDC, IPDMatrix* matrix, ILDOMRange* range)
{
	CTextContentBox::RenderSelection(pContext, hDC, matrix, range, m_text.length(), m_charOffsets.GetData());
}

//virtual
BOOL CWordBox::getPosUnderPoint(double x, double y, ILDOMNode **pNode, long *pOffset)
{
	Gdiplus::RectF rc = GetAbsInnerRect();
	//if (x >= rc.Contains(x, y))
	{
		double dx = x - rc.X;

		for (long offset = 0; offset < m_charOffsets.GetSize()-1; offset++)
		{
			double mx = m_charOffsets[offset+1]-(m_charOffsets[offset+1]-m_charOffsets[offset])/2;
			if (dx < mx) break;
		}

		(*pNode = m_node)->AddRef();
		*pOffset = m_start+offset;

		return TRUE;
	}

//	return FALSE;
}

/////////////////////////////////
// CObjectBox

//virtual
void CObjectBox::Render(CContentTextContext* pC)
{
	Gdiplus::RectF rect = GetAbsInnerRect();

	Gdiplus::GraphicsState state = pC->m_pGraphics->Save();
	pC->m_pGraphics->TranslateTransform(rect.X, rect.Y);

	m_pObject->Render(NULL, pC->m_pGraphics, 1, 1 /* TODO */);

	pC->m_pGraphics->Restore(state);
}

//////////////////////////////////
// CBox

CLineBox* CBox::GetParentLineBox()
{
	CBox* pParent = m_parent;
	while (pParent)
	{
		if (pParent->m_type == 2) return (CLineBox*)pParent;
		pParent = pParent->m_parent;
	}

	return NULL;
}

CBox* CBox::FindBox(ILDOMNode* container, long offset)
{
	if (m_type == 10 || m_type == 11)
	{
		CTextContentBox* pBox = (CTextContentBox*)this;

		if (pBox->m_node == container)
		{
			if (offset >= pBox->m_start)
			{
				CComQIPtr<ILDOMText> text = pBox->m_node;
				BSTR bdata;
				text->get_data(&bdata);
				int len = SysStringLen(bdata);
				SysFreeString(bdata);

				if (m_type == 10)	// Word
				{
					CWordBox* pWord = (CWordBox*)this;

					if ((offset < pWord->m_start+pWord->m_text.length()) ||
						(pBox->m_start+pWord->m_text.length() == len &&
						offset <= pWord->m_start+pWord->m_text.length()))
					{
						return pBox;
					}
				}
				else if (m_type == 11)	// Space
				{
					if ((offset < pBox->m_start+1) ||
						(pBox->m_start+1 == len &&
						offset <= pBox->m_start+1))
					{
						return pBox;
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < m_children.GetSize(); i++)
		{
			CBox* p = m_children[i]->FindBox(container, offset);
			if (p)
				return p;
		}
	}

	return NULL;
}

BOOL AddCharToSegList(IPDPath* seglist, HDC hdc, int ch, double offsetx, double offsety);

void CopyDefaultProperties(IPDObjectFrame* frame);

void CBox::BuildPaths(CContentTextContext* pC, IPDDocument* pddoc, IPDObjectGroup* pdgroup, IPDPath* pdpath, HDC hDC)
{
	HFONT hFont = NULL;
	HFONT hOldFont = NULL;

	if (m_pElement)
	{
		ATLASSERT(m_pElement);
		m_pElement->SetupFont(pC);

		LOGFONT lf;
		pC->m_pFont->GetLogFontA(pC->m_pGraphics, &lf);
		hFont = CreateFontIndirect(&lf);

		hOldFont = (HFONT)SelectObject(hDC, hFont);
	}

	if (m_type == 10)
	{
		Gdiplus::RectF rc = GetAbsInnerRect();

		CWordBox* pWord = (CWordBox*)this;
		for (int i = 0; i < pWord->m_text.length(); i++)
		{
			AddCharToSegList(pdpath, hDC, ((BSTR)pWord->m_text)[i], rc.X + pWord->m_charOffsets[i], rc.GetBottom());
		}
	}
	else if (m_type == 2)	// Line
	{
		CComPtr<IPDObjectFrame> pdframe;
		pddoc->createObjectFrame(&pdframe);

	{
		//CopyDefaultProperties(pdframe);
			CComPtr<IPDObjectFill> fill;
			fill.CoCreateInstance(CLSID_PDObjectFill);
			if (fill)
			{
//				defaultFillBrush->clone(&brush);

				CComPtr<IPDObjectWithBrush> object = fill;

				CComPtr<IPDBrush> brush;
				object->get_brush(&brush);

				CComPtr<IPDColor> color;
				brush->setColor(&color);
				color->setRGB(0, 0, 0);

				pdframe->appendSubObject(object);
			}
		}

		CComPtr<IPDPath> pdpath;
		pdframe->get_path(&pdpath);

//		AddCharToSegList(pdpath, hDC, 'A', 0, 0);
		for (int i = 0; i < m_children.GetSize(); i++)
		{
			m_children[i]->BuildPaths(pC, pddoc, pdgroup, pdpath, hDC);
		}
/*
		CComQIPtr<IPDObjectLocatable> locatable = pdframe;
		RectD bounds;
		locatable->get_bounds(&bounds);

		if (bounds.Width > 0 && bounds.Height > 0)
*/		{
			pdgroup->appendObject(pdframe);
		}
	}
	else
	{
		for (int i = 0; i < m_children.GetSize(); i++)
		{
			m_children[i]->BuildPaths(pC, pddoc, pdgroup, pdpath, hDC);
		}
	}

	if (hFont)
	{
		SelectObject(hDC, hOldFont);
		DeleteObject(hFont);
	}

	if (m_pElement)
		m_pElement->SetdownFont(pC);
}

//virtual
void CBox::Render(CContentTextContext* pC)
{
	if (m_pElement)
	{
		ATLASSERT(m_pElement);
		m_pElement->SetupFont(pC);
	}

	for (int i = 0; i < m_children.GetSize(); i++)
	{
		m_children[i]->Render(pC);
	}

	if (m_pElement)
		m_pElement->SetdownFont(pC);
}

//virtual
BOOL CBox::getPosUnderPoint(double x, double y, ILDOMNode **pNode, long *pOffset)
{
	Gdiplus::RectF rc = GetAbsInnerRect();
//	if (rc.Contains(x, y))
	{
		for (int i = 0; i < m_children.GetSize(); i++)
		{
			CBox* pBox = m_children[i];

			Gdiplus::RectF boxrc = pBox->GetAbsInnerRect();

			double right;
			if (i < m_children.GetSize()-1)
			{
				Gdiplus::RectF rboxrc = m_children[i+1]->GetAbsInnerRect();
				right = rboxrc.GetLeft()-(rboxrc.GetLeft()-boxrc.GetRight())/2;
			}
			else
				right = boxrc.GetRight();

			if (x < right)
			{
				BOOL b = pBox->getPosUnderPoint(x, y, pNode, pOffset);
				if (b)
				{
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}

//virtual
void CBox::RenderSelection(CContentTextContext* pContext, HDC hDC, IPDMatrix* matrix, ILDOMRange* range)
{
	for (int i = 0; i < m_children.GetSize(); i++)
	{
		m_children[i]->RenderSelection(pContext, hDC, matrix, range);
	}
}

Gdiplus::RectF CBox::GetAbsInnerRect()
{
	Gdiplus::RectF innerRect = m_innerRect;
	innerRect.X += m_outerRect.X;
	innerRect.Y += m_outerRect.Y;

	if (m_parent)
	{
		Gdiplus::RectF parentRect = m_parent->GetAbsInnerRect();
		innerRect.X += parentRect.X;
		innerRect.Y += parentRect.Y;
	}

	return innerRect;
}

//////////////////////////////////
// CLineBox

//virtual
void CLineBox::Render(CContentTextContext* pC)
{
	if (m_pElement)
	{
		ATLASSERT(m_pElement);
		m_pElement->SetupFont(pC);
	}

	Gdiplus::RectF rc = GetAbsInnerRect();

	for (int i = 0; i < m_children.GetSize(); i++)
	{
		m_children[i]->Render(pC);
	}

	//pC->m_pGraphics->DrawRectangle(&Gdiplus::Pen(Gdiplus::Color(255, 0, 0)), rc);

	if (m_pElement)
		m_pElement->SetdownFont(pC);
}

//virtual
BOOL CLineBox::getPosUnderPoint(double x, double y, ILDOMNode **pNode, long *pOffset)
{
	Gdiplus::RectF rc = GetAbsInnerRect();
	if (rc.Contains(x, y))
	{
		for (int i = 0; i < m_children.GetSize(); i++)
		{
			CBox* pBox = m_children[i];

/*			Gdiplus::RectF boxrc = pBox->GetAbsInnerRect();
			if (x < boxrc.GetRight())
			{
				for (int j = 0; j < pBox->m_children.GetSize(); j++)
				{
					CBox* pBox2 = pBox->m_children[j];
					Gdiplus::RectF boxrc2 = pBox2->GetAbsInnerRect();

					if (x < boxrc2.GetRight())
					{
*/						BOOL b = pBox->getPosUnderPoint(x, y, pNode, pOffset);
						if (b)
							return TRUE;
/*						else if (pBox->m_type == 

					}
				}
			}
			*/
		}
	}

	return FALSE;
}

double ConvertSpecifiedValueToUserUnit(short unitType, double specifiedValue);

void CLineBox::OffsetChildren(double dx)
{
	for (int i = 0; i < m_children.GetSize(); i++)
	{
		CBox* pBox = m_children[i];
		pBox->m_outerRect.X += dx;
	}
}

void CLineBox::AdjustBottom()
{
	int i;

	m_maxascent = 0;

	CArray<float,float> ascents;

	for (i = 0; i < m_children.GetSize(); i++)
	{
		CBox* pBox = m_children[i];

		Gdiplus::Font font(pBox->m_pElement->m_fontFamily, pBox->m_pElement->m_fontSize);
		Gdiplus::FontFamily fontFamily;
		font.GetFamily(&fontFamily);
		float ascent = font.GetSize() * fontFamily.GetCellAscent(Gdiplus::FontStyleRegular) / fontFamily.GetEmHeight(Gdiplus::FontStyleRegular);

		float ascentPixel = ConvertSpecifiedValueToUserUnit(UNIT_PT, ascent);

		ascents.Add(ascentPixel);
		m_maxascent = max(m_maxascent, ascentPixel);
	}

	for (i = 0; i < m_children.GetSize(); i++)
	{
		CBox* pBox = m_children[i];
/*
		m_innerRect.Height

		pBox->m_outerRect.Height

		pBox->m_innerRect.Y = m_innerRect.Height - pBox->m_outerRect.Height;
*/
		pBox->m_outerRect.Y = m_maxascent-ascents[i];
	}

	/*
	for (int i = 0; i < m_children.GetSize(); i++)
	{
		CBox* pBox = m_children[i];
		pBox->m_outerRect.Y = m_innerRect.Height - pBox->m_outerRect.Height;
	}
	*/
}

/////////////
// CBlockBox

//virtual
void CBlockBox::Render(CContentTextContext* pC)
{
	CBox::Render(pC);

	if (pC->m_pContentText->m_pDocument->m_showHiddenCharacters)
	{
		if (m_pElement)
		{
			BSTR btagName;
			m_pElement->m_node->get_nodeName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);
			if (!wcscmp(tagName, L"p"))
			{
				CComPtr<IPDLayer> layer;
				pC->m_pContentText->get_layer(&layer);
				COLORREF clr;
				layer->get_color(&clr);

				if (m_children.GetSize() > 0)
				{
					CBox* lastBox = (CBox*)m_children[m_children.GetSize()-1];

					Gdiplus::Font font(L"Symbol", /*lastBox->*/m_pElement->m_fontSize);

					Gdiplus::RectF rc = lastBox->GetAbsInnerRect();

					Gdiplus::SolidBrush brush(Gdiplus::Color(GetRValue(clr), GetGValue(clr), GetBValue(clr)));

					Gdiplus::StringFormat stringFormat;
					stringFormat.SetLineAlignment(Gdiplus::StringAlignmentFar);

					pC->m_pGraphics->DrawString(L"p", 1, &font, Gdiplus::PointF(rc.GetRight(), rc.GetBottom()), &stringFormat, &brush);
				}
			}
		}
	}
}

//virtual
BOOL CBlockBox::getPosUnderPoint(double x, double y, ILDOMNode **pNode, long *pOffset)
{
	Gdiplus::RectF rc = GetAbsInnerRect();
	if (rc.Contains(x, y))
	{
		for (int i = 0; i < m_children.GetSize(); i++)
		{
			BOOL b = m_children[i]->getPosUnderPoint(x, y, pNode, pOffset);
			if (b)
				return TRUE;
		}
	}

	return FALSE;
}

//////////////////////////////////
// CContentTextContext

BOOL CContentTextContext::PlaceInlineBoxInDropCaps(CBox* pCBox)
{
	BOOL bPlaced = FALSE;

	Gdiplus::RectF blockboxrc = m_pBlockBox->GetAbsInnerRect();

	ATLASSERT(m_pContentText);

	do
	{
		Gdiplus::RectF rc = pCBox->m_outerRect;

		if (m_y >= m_framebounds.Height-rc.Height)	// Past bottom of frame
			break;

		rc.X = m_x;
		rc.Y = m_y;

		Gdiplus::RectF absrc = rc;
//		absrc.X += m_absx;
//		absrc.Y += m_absy;

		absrc.X += m_framebounds.X;
		absrc.Y += m_framebounds.Y;

		if (rc.GetRight() > m_pBlockBox->m_innerRect.Width)	// Past right of frame, go down a line
		{
			break;
		}
		else
		{
			BOOL bVisible = !m_iregion->IsVisible(absrc/*, graphics*/);
			if (bVisible)
			{
				if (m_pCurLineBox == NULL)
				{
				// Create new line box
					m_pCurLineBox = new CLineBox;
					m_pCurLineBox->m_outerRect.X = m_x;
					m_pCurLineBox->m_outerRect.Y = m_y;
					m_pCurLineBox->m_outerRect.Width = 0;
					m_pCurLineBox->m_outerRect.Height = 0;

					m_pCurLineBox->m_innerRect.X = 0;
					m_pCurLineBox->m_innerRect.Y = 0;
					m_pCurLineBox->m_innerRect.Width = 0;
					m_pCurLineBox->m_innerRect.Height = 0;

					m_pCurLineBox->m_parent = m_pBlockBox;
					m_pBlockBox->m_children.Add(m_pCurLineBox);
					
					m_pCurBox = NULL;
				}

				if (m_pCurBox == NULL)
				{
					m_pCurBox = new CElementBox;
					m_pCurBox->m_pElement = m_pElement;

					m_pCurBox->m_outerRect.X = m_x - m_pCurLineBox->m_outerRect.X;
					m_pCurBox->m_outerRect.Y = 0;

					m_pCurBox->m_parent = m_pCurLineBox;
					m_pCurLineBox->m_children.Add(m_pCurBox);
				}

				pCBox->m_outerRect.X = m_x-m_pCurBox->m_outerRect.X-m_pCurLineBox->m_outerRect.X;
				pCBox->m_outerRect.Y = 0;

			// Adjust element box containing box
				m_pCurBox->m_innerRect.Width = pCBox->m_outerRect.GetRight();
				m_pCurBox->m_outerRect.Width = m_pCurBox->m_innerRect.Width;

				if (pCBox->m_outerRect.Height > m_pCurBox->m_innerRect.Height)
				{
					m_pCurBox->m_innerRect.Height = pCBox->m_outerRect.Height;
					m_pCurBox->m_outerRect.Height = m_pCurBox->m_innerRect.Height;
				}

				pCBox->m_parent = m_pCurBox;
				m_pCurBox->m_children.Add(pCBox);

			// Adjust line box
				if (m_pCurBox->m_outerRect.Height > m_pCurLineBox->m_innerRect.Height)
				{
					m_pCurLineBox->m_innerRect.Height = m_pCurBox->m_outerRect.Height;
					m_pCurLineBox->m_outerRect.Height = m_pCurLineBox->m_innerRect.Height;
				}

				m_pCurLineBox->m_innerRect.Width = m_pCurBox->m_outerRect.GetRight();
				m_pCurLineBox->m_outerRect.Width = m_pCurLineBox->m_innerRect.Width;

			// Adjust container box
				m_pBlockBox->m_innerRect.Height = m_pCurLineBox->m_outerRect.GetBottom();

				m_x += rc.Width;
			//	m_x += 8;	// TODO
				bPlaced = TRUE;
			}
			else
			{
				m_x += 1;
			}
		}
	}
	while (!bPlaced);

	return bPlaced;
}

BOOL CContentTextContext::PlaceInlineBoxInColumn(CBox* pCBox)
{
	BOOL bPlaced;
	do
	{
		bPlaced = PlaceInlineBox(pCBox);

		if (!bPlaced)
		{
			if (m_pContentText->m_nColumnsSoFar < m_pContentText->m_columnsNumber)
			{
				m_pContentText->m_nColumnsSoFar++;

				//double columnWidth = (m_framebounds.Width-(m_pContentText->m_columnsNumber-1)*m_pContentText->m_columnsGutter)/m_pContentText->m_columnsNumber;
				double columnWidth = m_pContentText->m_columnsWidth;//(m_framebounds.Width-(m_pContentText->m_columnsNumber-1)*m_pContentText->m_columnsGutter)/m_pContentText->m_columnsNumber;

				CBlockBox* pPrevColumnBox = (CBlockBox*)(m_pBlockBox->m_parent);
				ATLASSERT(pPrevColumnBox->m_parent->m_parent == NULL);

				//if (pPrevColumnBox->m_outerRect.GetRight() + 
				// Create new column box
				CBlockBox* pColumnBox = new CBlockBox;

				CElement* pElement = m_pBlockBox->m_pElement;	// Paragraph element

				pColumnBox->m_innerRect.X = 0;
				pColumnBox->m_innerRect.Y = 0;
				pColumnBox->m_innerRect.Width = columnWidth;
				pColumnBox->m_innerRect.Height = m_framebounds.Height;

			// Place it next to previous column
				pColumnBox->m_outerRect = pColumnBox->m_innerRect;
				pColumnBox->m_outerRect.X = pPrevColumnBox->m_outerRect.GetRight() + m_pContentText->m_columnsGutter;

				pColumnBox->m_parent = m_pContentText->m_pBox;
				m_pContentText->m_pBox->m_children.Add(pColumnBox);

				m_pBlockBox = pColumnBox;
				m_x = 0;
				m_y = 0;

				{
					CBlockBox* pBox = new CBlockBox;	// Create new block for this paragraph
					pBox->m_parent = m_pBlockBox;
					m_pBlockBox->m_children.Add(pBox);
					pBox->m_innerRect.Width = m_pBlockBox->m_innerRect.Width;
					pBox->m_pElement = pElement;

					m_pBlockBox = pBox;
				}
			}
			else
				break;	// Give up
		}
	}
	while (!bPlaced);

	return bPlaced;
}

BOOL CContentTextContext::PlaceInlineBox(CBox* pCBox)
{
	BOOL bPlaced = FALSE;

	Gdiplus::RectF blockboxrc = m_pBlockBox->GetAbsInnerRect();

	ATLASSERT(m_pContentText);

	do
	{
		Gdiplus::RectF rc = pCBox->m_outerRect;

		if (m_y >= m_framebounds.Height-rc.Height)	// Past bottom of frame
			break;

		rc.X = m_x;
		rc.Y = m_y;

		Gdiplus::RectF absrc = rc;

	//	absrc.X += m_absx;
	//	absrc.Y += m_absy;

		absrc.X += m_framebounds.X;
		absrc.Y += m_framebounds.Y;

		//absrc.X += 

		//absrc.Offset(blockboxrc.X, blockboxrc.Y);

		if (rc.GetRight() > m_pBlockBox->m_innerRect.Width)	// Past right of column, go down a line
		{
			if (m_pCurLineBox)
			{
				m_pCurLineBox->AdjustBottom();

				if (m_textAlign == PARAALIGN_LEFT)
				{
					// Do nothing
				}
				else if (m_textAlign == PARAALIGN_CENTER)
				{
				}
				else if (m_textAlign == PARAALIGN_RIGHT)
				{
					double linerightEdge = m_pCurLineBox->m_outerRect.GetRight();
					double rightEdge = m_framebounds.Width;

					for (int i = 0; i < 	m_pContentText->m_regionRectsCount; i++)
					{
						Gdiplus::RectF rc = m_pContentText->m_regionRects[i];

					//	ATLASSERT(m_framebounds.Contains(rc));

						rc.Offset(-m_framebounds.X, -m_framebounds.Y);

						if ((rc.Y <= m_y+m_pCurLineBox->m_outerRect.Height) && (rc.Y+rc.Height >= m_y))
						{
							if (rc.X > linerightEdge && rc.X < rightEdge)
							{
								rightEdge = rc.X;
							}
						}
					}

					ATLASSERT(rightEdge >= linerightEdge);
					m_pCurLineBox->OffsetChildren(rightEdge-linerightEdge);
				}
			}

			if (m_pCurLineBox == NULL)
			{
				m_y += 1;
			}
			else
			{
				m_y += m_pCurLineBox->m_outerRect.Height;
			}

			// Go to left
			if (m_y >= m_nDropCapsBottom)
			{
				m_nDropCapsLeft = 0;
				m_x = 0;
			}
			else
			{
				m_x = m_nDropCapsLeft;
			}

			m_pCurBox = NULL;
			m_pCurLineBox = NULL;
		}
		else
		{
			BOOL bVisible = !m_iregion->IsVisible(absrc/*, graphics*/);
			if (bVisible)
			{
				if (m_pCurLineBox == NULL)
				{
				// Create new line box
					m_pCurLineBox = new CLineBox;
					m_pCurLineBox->m_outerRect.X = m_x;
					m_pCurLineBox->m_outerRect.Y = m_y;
					m_pCurLineBox->m_outerRect.Width = 0;
					m_pCurLineBox->m_outerRect.Height = 0;

					m_pCurLineBox->m_innerRect.X = 0;
					m_pCurLineBox->m_innerRect.Y = 0;
					m_pCurLineBox->m_innerRect.Width = 0;
					m_pCurLineBox->m_innerRect.Height = 0;

					m_pCurLineBox->m_parent = m_pBlockBox;
					m_pBlockBox->m_children.Add(m_pCurLineBox);
					
					m_pCurBox = NULL;
				}

				if (m_pCurBox == NULL)
				{
					m_pCurBox = new CElementBox;
					m_pCurBox->m_pElement = m_pElement;

					m_pCurBox->m_outerRect.X = m_x - m_pCurLineBox->m_outerRect.X;
					m_pCurBox->m_outerRect.Y = 0;

					m_pCurBox->m_parent = m_pCurLineBox;
					m_pCurLineBox->m_children.Add(m_pCurBox);
				}

				pCBox->m_outerRect.X = m_x-m_pCurBox->m_outerRect.X-m_pCurLineBox->m_outerRect.X;
				pCBox->m_outerRect.Y = 0;

			// Adjust element box containing box
				m_pCurBox->m_innerRect.Width = pCBox->m_outerRect.GetRight();
				m_pCurBox->m_outerRect.Width = m_pCurBox->m_innerRect.Width;

				if (pCBox->m_outerRect.Height > m_pCurBox->m_innerRect.Height)
				{
					m_pCurBox->m_innerRect.Height = m_pCurBox->m_outerRect.Height = pCBox->m_outerRect.Height;
				}

				pCBox->m_parent = m_pCurBox;
				m_pCurBox->m_children.Add(pCBox);

			// Adjust line box
				if (m_pCurBox->m_outerRect.Height > m_pCurLineBox->m_innerRect.Height)
				{
					m_pCurLineBox->m_innerRect.Height = m_pCurLineBox->m_outerRect.Height = m_pCurBox->m_outerRect.Height;
				}

				m_pCurLineBox->m_innerRect.Width = m_pCurLineBox->m_outerRect.Width = m_pCurBox->m_outerRect.GetRight();

			// Adjust container box
				m_pBlockBox->m_innerRect.Height = m_pCurLineBox->m_outerRect.GetBottom();

				m_x += rc.Width;

				bPlaced = TRUE;
			}
			else
			{
				m_x += 1;
			}
		}
	}
	while (!bPlaced);

	return bPlaced;
}

void CContentTextContext::SetdownElement(CElement* pElement, CTextContext* _pC)
{
	CComQIPtr<ILDOMElement> element = pElement->m_node;

	CContentTextContext* pC = (CContentTextContext*)_pC;

	BSTR btagName;
	element->get_tagName(&btagName);
	_bstr_t tagName = _bstr_t(btagName, false);

	if (!wcscmp(tagName, L"text"))	// End of outermost block
	{
	}
	else if (!wcscmp(tagName, L"p"))	// End of paragraph block
	{
		if (pC->m_pCurLineBox)	// ?? do this here?
		{
			pC->m_pCurLineBox->AdjustBottom();
			pC->m_pCurLineBox = NULL;	// ??
		}

		pC->m_pBlockBox->m_outerRect.Y = pC->m_pBlockBox->m_innerRect.Y;
		pC->m_pBlockBox->m_outerRect.Height = pC->m_pBlockBox->m_innerRect.Height;
		//pC->m_pBlockBox->m_outerRect.X = pC->m_pBlockBox->m_innerRect.X;
		pC->m_pBlockBox->m_outerRect.Offset(0, m_y);

		m_y += pC->m_pBlockBox->m_outerRect.Height;
	}
	else	// End of any other inline box
	{
		m_pCurBox = NULL;
		m_pCurLineBox = pC->m_pCurLineBox;
		m_pContentText = pC->m_pContentText;	// ??
		m_x = pC->m_x;
		m_y = pC->m_y;
	}

	delete pC;
}

CTextContext* CContentTextContext::SetupElement(CElement* pElement)
{
	CComQIPtr<ILDOMElement> element = pElement->m_node;

	BSTR btagName;
	element->get_tagName(&btagName);
	_bstr_t tagName = _bstr_t(btagName, false);

	if (!wcscmp(tagName, L"text"))	// Outermost container block
	{
		CContentTextContext* pC = new CContentTextContext;

		pC->m_framebounds = m_framebounds;

		{
			pC->m_pGraphics = m_pGraphics;
			pC->m_pFont = m_pFont;
			pC->m_iregion = m_iregion;	// TODO, make relative (somehow)
			pC->m_framebounds = m_framebounds;	// TODO, make relative
			pC->m_pContentText = m_pContentText;
		}

		CBlockBox* pBox = new CBlockBox;	// Create new outermost block
		{
			m_pContentText->m_pBox = pBox;

			pBox->m_pElement = pElement;	// ??

			pBox->m_outerRect = m_framebounds;

			pBox->m_innerRect.X = 0;
			pBox->m_innerRect.Y = 0;
			pBox->m_innerRect.Width = m_framebounds.Width;
			pBox->m_innerRect.Height = m_framebounds.Height;
		}

		// Create first column box
		CBlockBox* pColumnBox = new CBlockBox;
		{
			double columnWidth = m_pContentText->m_columnsWidth;//(m_framebounds.Width-(m_pContentText->m_columnsNumber-1)*m_pContentText->m_columnsGutter)/m_pContentText->m_columnsNumber;
		//	double columnWidth = (m_framebounds.Width-(m_pContentText->m_columnsNumber-1)*m_pContentText->m_columnsGutter)/m_pContentText->m_columnsNumber;
			pColumnBox->m_innerRect.X = 0;
			pColumnBox->m_innerRect.Y = 0;
			pColumnBox->m_innerRect.Width = columnWidth;
			pColumnBox->m_innerRect.Height = m_framebounds.Height;
			pColumnBox->m_outerRect = pColumnBox->m_innerRect;

			pColumnBox->m_parent = pBox;
			pBox->m_children.Add(pColumnBox);

			m_pContentText->m_nColumnsSoFar++;
		}

		pC->m_absx = m_absx;
		pC->m_absy = m_absy;

		pC->m_pBlockBox = pColumnBox;

		return pC;
	}
	else if (!wcscmp(tagName, L"p"))	// Paragraph block
	{
		BSTR b;

		CContentTextContext* pC = new CContentTextContext;

		double marginLeft;
		element->getAttribute(L"margin-left", &b);
		if (b)
			marginLeft = atof(_bstr_t(b, false));
		else
			marginLeft = 0;

		double marginRight;
		element->getAttribute(L"margin-right", &b);
		if (b)
			marginRight = atof(_bstr_t(b, false));
		else
			marginRight = 0;

		CBlockBox* pBox = new CBlockBox;	// Create new block for this paragraph
		pBox->m_parent = m_pBlockBox;
		m_pBlockBox->m_children.Add(pBox);
		pBox->m_innerRect.X = marginLeft;
		pBox->m_innerRect.Width = m_pBlockBox->m_innerRect.Width-marginLeft-marginRight;
		pBox->m_pElement = pElement;

		pC->m_pGraphics = m_pGraphics;
		pC->m_pFont = m_pFont;
		pC->m_iregion = m_iregion;	// TODO, make relative (somehow)
		pC->m_framebounds = m_framebounds;	// TODO, make relative

		pC->m_pContentText = m_pContentText;
		pC->m_pElement = pElement;
		pC->m_pBlockBox = pBox;

		CComQIPtr<ILDOMElement> element = pElement->m_node;

		element->getAttribute(L"text-align", &b);
		if (b)
			pC->m_textAlign = atol(_bstr_t(b, false));
		else
			pC->m_textAlign = 0;

		element->getAttribute(L"dropcap-lines", &b);
		if (b)
			pC->m_nDropCapsLines = atol(_bstr_t(b, false));
		else
			pC->m_nDropCapsLines = 0;

		element->getAttribute(L"dropcap-chars", &b);
		if (b)
			pC->m_nDropCapsChars = atol(_bstr_t(b, false));
		else
			pC->m_nDropCapsChars = 0;

		double textIndent;
		element->getAttribute(L"text-indent", &b);
		if (b)
			textIndent = atof(_bstr_t(b, false));
		else
			textIndent = 0;
		pC->m_x = textIndent;

		pC->m_absx = m_absx+0;
		pC->m_absy = m_absy+m_y;

		//pC->m_x = 0;//pC->m_nDropCapsLeft;

		return pC;
	}
	else	// Any other inline element
	{
		CContentTextContext* pC = new CContentTextContext;
		pC->m_pElement = pElement;

		pC->m_pGraphics = m_pGraphics;
		pC->m_pFont = m_pFont;
		pC->m_iregion = m_iregion;	// TODO, make relative (somehow)
		pC->m_framebounds = m_framebounds;	// TODO, make relative

		pC->m_pContentText = m_pContentText;
		pC->m_pCurLineBox = m_pCurLineBox;
		pC->m_pBlockBox = m_pBlockBox;
		pC->m_x = m_x;
		pC->m_y = m_y;
		pC->m_absx = m_absx;
		pC->m_absy = m_absy;

		pC->m_textAlign = m_textAlign;

		pC->m_nDropCapsLines = m_nDropCapsLines;
		pC->m_nDropCapsChars = m_nDropCapsChars;
		pC->m_nDropCapsCharSoFar = m_nDropCapsCharSoFar;
		pC->m_nDropCapsLeft = m_nDropCapsLeft;
		pC->m_nDropCapsBottom = m_nDropCapsBottom;

		return pC;
	}

	return NULL;
}

BOOL CContentTextContext::PlaceWord(CNode* node, int start, _bstr_t data)
{
	if (m_nDropCapsCharSoFar < m_nDropCapsChars)
	{
		ATLASSERT(0);

		BOOL bPlaced = FALSE;

		if (m_nDropCapsCharSoFar+data.length() > m_nDropCapsChars)
		{
			CUString udata = (char*)data;

		// split word
			int splitat = m_nDropCapsChars - m_nDropCapsCharSoFar;

			CWordBox* pWord = new CWordBox;
			pWord->m_node = node->m_node;
			pWord->m_start = start;
			pWord->m_text = udata.Left(splitat);
			pWord->CalculateDimensions(this, m_nDropCapsLines);
			pWord->m_outerRect = pWord->m_innerRect;

			bPlaced = PlaceInlineBoxInDropCaps(pWord);

			m_nDropCapsCharSoFar += splitat;

		// End of drop caps
			{
				m_nDropCapsBottom = m_pCurLineBox->m_outerRect.GetBottom();
				m_nDropCapsLeft = m_pCurLineBox->m_outerRect.GetRight();
				m_x = m_nDropCapsLeft;

				m_pCurLineBox = NULL;
				m_pCurBox = NULL;
			}

			CWordBox* pWord2 = new CWordBox;
			pWord2->m_node = node->m_node;
			pWord2->m_start = start+splitat;
			pWord2->m_text = udata.Right(data.length()-splitat);
			pWord2->CalculateDimensions(this);
			pWord2->m_outerRect = pWord2->m_innerRect;

			bPlaced = PlaceInlineBoxInColumn(pWord2);

			//m_nDropCapsCharSoFar += data.length()-splitat;
		}
		else	// Entire word fits in the drop caps box
		{
			CWordBox* pWord = new CWordBox;

			pWord->m_node = node->m_node;
			pWord->m_start = start;
			pWord->m_text = data;

			pWord->CalculateDimensions(this, m_nDropCapsLines);
			pWord->m_outerRect = pWord->m_innerRect;

			bPlaced = PlaceInlineBoxInDropCaps(pWord);

			m_nDropCapsCharSoFar += data.length();

			if (!(m_nDropCapsCharSoFar < m_nDropCapsChars))
			{
			// End of drop caps
				{
					m_nDropCapsBottom = m_pCurLineBox->m_outerRect.GetBottom();
					m_nDropCapsLeft = m_pCurLineBox->m_outerRect.GetRight();
					m_x = m_nDropCapsLeft;

					m_pCurLineBox = NULL;
					m_pCurBox = NULL;
				}
			}
		}

		return bPlaced;
	}
	else
	{
		CTextContentBox* pBox;
		if (!wcscmp(data, L" ") || !wcscmp(data, L"\t"))
		{
			CSpaceBox* pSpace = new CSpaceBox;
			pSpace->m_ch = ((BSTR)data)[0];

			pBox = pSpace;
		}
		else
		{
			CWordBox* pWord = new CWordBox;

			pWord->m_text = data;

			pBox = pWord;
		}

		pBox->m_start = start;
		pBox->m_node = node->m_node;

		pBox->CalculateDimensions(this);
		pBox->m_outerRect = pBox->m_innerRect;

		BOOL bPlaced = PlaceInlineBoxInColumn(pBox);
		if (!bPlaced)
		{
			delete pBox;
		}

		return bPlaced;
	}
}

BOOL CContentTextContext::PlaceObject(IPDObject* object)
{
	CObjectBox* pBox = new CObjectBox;
	pBox->m_pObject = static_cast<CPDObjectImpl<IPDObject>*>(object);

	CComQIPtr<IPDObjectTransformable> transformable = object;

	RectD rc;
	transformable->get_bounds(&rc);
	transformable->Move(-rc.X, -rc.Y);

	pBox->m_innerRect.X = 0;
	pBox->m_innerRect.Y = 0;
	pBox->m_innerRect.Width = rc.Width;
	pBox->m_innerRect.Height = rc.Height;

	pBox->m_outerRect = pBox->m_innerRect;

	BOOL bPlaced = PlaceInlineBox(pBox);
	if (!bPlaced)
	{
		delete pBox;
	}

  return bPlaced;
}

void AddWrappable(IPDObjectFrame* pShape, IPDObjectGroup* group, CArray<IPDObjectWrappable*,IPDObjectWrappable*> &frames)
{
	CComPtr<IObjectMap> children;
	group->get_children(&children);

	long nchildren;
	children->get_length(&nchildren);

	for (int i = 0; i < nchildren; i++)
	{
		CComPtr<IPDObject> object;
		children->item(i, (IUnknown**)&object);

		if (!IsUnknownEqualUnknown(pShape, object))
		{
			CComQIPtr<IPDObjectWrappable> wrappable = object;
			if (wrappable)
			{
				CComPtr<IPDPath> wrapPath;
				wrappable->get_wrapPath(&wrapPath);

				if (wrapPath)
				{
					frames.Add(wrappable);
				}
			}

			CComQIPtr<IPDObjectGroup> group2 = object;
			if (group2)
			{
				AddWrappable(pShape, group2, frames);
			}
		}
	}

	/*
			CPDObjectImpl<IPDObject>* next = m_parent->m_parent->m_firstChild;
			while (next)
			{
				if ((CPDObjectFrame*)next != pShape)
				{
					if (next->m_textWrap)
					{
						frames.Add((CPDObjectFrame*)next);
					}
				}

			  next = next->m_nextSibling;
			}
			*/
}

/////////////////////////
// CPDContentText

int CPDContentText::FinalConstruct()
{
	HRESULT hr;

	hr = CPDObjectTextImpl<IPDContentText>::FinalConstruct();
	if (FAILED(hr)) return hr;

	return S_OK;
}

void CPDContentText::FinalRelease()
{
	CPDObjectTextImpl<IPDContentText>::FinalRelease();
}

// virtual
CTextContext* CPDContentText::SetupBox(CStoryFlowContext* /*pSC*/)
{
	ATLASSERT(m_pBox == NULL);

	CContentTextContext* pC = new CContentTextContext;

	pC->m_pContentText = this;

	m_overflow = VARIANT_FALSE;
	m_nColumnsSoFar = 0;

	CPDObjectFrame* pFrame = static_cast<CPDObjectFrame*>((IPDObjectFrame*)m_parent);
	Gdiplus::RectF framebounds = pFrame->GetBounds();

//	CArray<CPDObjectFrame*,CPDObjectFrame*> frames;
	CArray<IPDObjectWrappable*,IPDObjectWrappable*> frames;

	if (!m_ignoreTextWrap)
	{
		if (pFrame->m_textWrap)
		{
			// Take into account textwrap of objects overlapping this object

			CComQIPtr<IPDObject> next;
			m_parent->get_nextSibling((IPDObjectUnknown**)&next);
			while (next)
			{
				CComQIPtr<IPDObjectWrappable> wrappable = next;
				PDTextWrap textWrap;
				wrappable->get_textWrap(&textWrap);
				if (textWrap)
				{
					frames.Add(wrappable);
				}

				CComPtr<IPDObjectUnknown> nextSibling;
				next->get_nextSibling(&nextSibling);
				next = nextSibling;
			}
		}
		else
		{
			// Take into account all other objects


			CComPtr<IObjectMap> layergroups;
			m_spread->get_layergroups(&layergroups);

			long nlayergroups;
			layergroups->get_length(&nlayergroups);
			for (int nlayergroup = 0; nlayergroup < nlayergroups; nlayergroup++)
			{
				CComPtr<IPDObjectLayerGroup> layergroup;
				layergroups->item(nlayergroup, (IUnknown**)&layergroup);

				AddWrappable(pFrame, layergroup, frames);
			}

			/*
			CComQIPtr<IPDObject> next;

			CPDObjectImpl<IPDObject>* next = m_parent->m_parent->m_firstChild;
			while (next)
			{
				if ((CPDObjectFrame*)next != pShape)
				{
					if (next->m_textWrap)
					{
						frames.Add((CPDObjectFrame*)next);
					}
				}

			  next = next->m_nextSibling;
			}
			*/
		}
	}

	Gdiplus::Region* region = new Gdiplus::Region(GetFramePath(pFrame->m_path, NULL));

	double strokeWeight = 0;
	// Find max stroke width
	/*
	{
		for (int i = 0; i < pFrame->m_subObjects->m_items.GetSize(); i++)
		{
			CComQIPtr<IPDStroke> stroke = pFrame->m_subObjects->m_items[i];
			if (stroke)
			{
				double strokeWeight2;
				stroke->get_strokeWeight(&strokeWeight2);
				strokeWeight = max(strokeWeight, strokeWeight2);
			}
		}
	}
	*/

	CComPtr<IPDMatrix> imatrix;
	{
		CComPtr<IPDMatrix> matrix;
		pFrame->getScreenCTM(&matrix);
		matrix->inverse(&imatrix);
	}

	for (int i = 0; i < frames.GetSize(); i++)
	{
		CComQIPtr<IPDObject> object = frames[i];

		CComPtr<IPDMatrix> matrix;
		object->getScreenCTM(&matrix);

		CComPtr<IPDMatrix> matrix2;
		imatrix->multiply(matrix, &matrix2);

		CComPtr<IPDPath> wrapPath;
		frames[i]->get_wrapPath(&wrapPath);

		Gdiplus::GraphicsPath* framepath = GetFramePath((CPDPath*)wrapPath.p, (CPDMatrix*)matrix2.p);

		region->Exclude(framepath);

		delete framepath;
	}

	region->Complement(framebounds);

	Gdiplus::Matrix matrix;
	m_regionRectsCount = region->GetRegionScansCount(&matrix);
	m_regionRects = new Gdiplus::RectF[m_regionRectsCount];
	region->GetRegionScans(&matrix, m_regionRects, &m_regionRectsCount);
//	ATLASSERT(n == m_regionRectsCount);

	pC->m_framebounds = framebounds;
	pC->m_iregion = region;

	pC->m_absx = framebounds.X;
	pC->m_absy = framebounds.Y;

	return pC;
}

//virtual
void CPDContentText::SetdownBox(CTextContext* _pC)
{
	CContentTextContext* pC = (CContentTextContext*)_pC;

	delete pC;
}

//virtual
void CPDContentText::Clear()
{
	if (m_regionRects)
	{
		delete m_regionRects;
		m_regionRects = NULL;
		m_regionRectsCount = 0L;
	}

	if (m_pBox)
	{
		delete m_pBox;
		m_pBox = NULL;
	}
}

#include "PDRenderer.h"

void CPDContentText::FindThreadPts(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3)
{
//	CComQIPtr<IPDObjectTransformable> objectTransformable = m_object;

	RectD bounds = m_bounds;
//	objectTransformable->get_bounds(&bounds);

	double ax, ay, bx, by, cx, cy;

	cx = 3 * (x1 - x0);
	cy = 3 * (y1 - y0);
	bx = 3 * (x2 - x1) - cx;
	by = 3 * (y2 - y1) - cy;
	ax = x3 - x0 - cx - bx;
	ay = y3 - y0 - cy - by;

	double tinc = 1/50.0;

	for (double t = 0.0; t <= 1.0; t += tinc)
	{
		double xt = ax * t*t*t + bx * t*t + cx * t + x0;
		double yt = ay * t*t*t + by * t*t + cy * t + y0;

		if (yt < m_topSoFar && yt > bounds.Y+10)
		{
			m_topSoFar = yt;

			m_threadPtLeft.x = xt;
			m_threadPtLeft.y = yt;
		}

		if (yt > m_bottomSoFar  && yt < bounds.Y+bounds.Height-10)
		{
			m_bottomSoFar = yt;

			m_threadPtRight.x = xt;
			m_threadPtRight.y = yt;
		}
	}
}

void CPDContentText::CalculateThreadRects()
{
	CComQIPtr<IPDObjectFrame> frame = m_parent;//object;

	if (frame)
	{
		CComPtr<IPDPath> pdpath;
		frame->get_path(&pdpath);

		m_topSoFar =		9999999;
		m_bottomSoFar = - 9999999;

		long nsubpaths;
		pdpath->get_subPathCount(&nsubpaths);

		for (int i = 0; i < nsubpaths; i++)
		{
			CComPtr<IPDSubPath> subpath;
			pdpath->getSubPath(i, &subpath);

			long npoints;
			subpath->get_pointCount(&npoints);

			if (npoints > 1)
			{
				BezierPoint point;
				subpath->getPoint(0, &point);

				BezierPoint xpoint[2];
				xpoint[0] = point;

				for (int npt = 1; npt < npoints; npt++)
				{
					subpath->getPoint(npt, &point);
					xpoint[1] = point;

					FindThreadPts((float)xpoint[0].x, (float)xpoint[0].y,
						(float)xpoint[0].x2, (float)xpoint[0].y2,
						(float)xpoint[1].x1, (float)xpoint[1].y1,
						(float)xpoint[1].x, (float)xpoint[1].y);

					xpoint[0] = xpoint[1];
				}

				VARIANT_BOOL closed;
				subpath->get_closed(&closed);

				if (closed)
				{
					subpath->getPoint(0, &point);
					xpoint[1] = point;

					FindThreadPts(
						(float)xpoint[0].x, (float)xpoint[0].y,
						(float)xpoint[0].x2, (float)xpoint[0].y2,
						(float)xpoint[1].x1, (float)xpoint[1].y1,
						(float)xpoint[1].x, (float)xpoint[1].y);
				}
			}
		}
/*
		CComPtr<IPDPathText> pathText;
		frame->get_pathText(&pathText);

		if (pathText)
		{
			CComPtr<IPDPath> path;
			frame->get_path(&path);

			CComPtr<IPDSubPath> subpath;
			path->getSubPath(0, &subpath);

			double startOnLength;
			pathText->get_startOnLength(&startOnLength);

			double endOnLength;
			pathText->get_endOnLength(&endOnLength);

			subpath->getPointOnLength(startOnLength, &m_pthreadPtLeft.x, &m_pthreadPtLeft.y, &m_pthreadRotationLeft);
			subpath->getPointOnLength(endOnLength, &m_pthreadPtRight.x, &m_pthreadPtRight.y, &m_pthreadRotationRight);
		}
		*/
	}
}

//virtual
void CPDContentText::CalculateBounds()
{
	CPDObjectFrame* pFrame = static_cast<CPDObjectFrame*>((IPDObjectFrame*)m_parent);
	if (pFrame)
	{
		m_bounds = pFrame->m_bounds;
	// Calculate column with based on width of bounding box
		if (!m_columnsFixedWidth)
		{
			m_columnsWidth = (m_bounds.Width-(m_columnsNumber-1)*m_columnsGutter)/m_columnsNumber;
		}

		CalculateThreadRects();
	}
	else
	{
		m_bounds.X = 999999;
		m_bounds.Y = 999999;
		m_bounds.Width = -999999;
		m_bounds.Height = -999999;

		m_columnsWidth = 0;
	}

	m_filterRect = m_bounds;	// Not used since no appearance on ContentText ??
	m_expandedBBox = m_bounds;

	m_xbounds = m_bounds;
}

//virtual
void CPDContentText::Render(CPDRenderer* pRenderer, Gdiplus::Graphics* pGraphics, double scaleX, double scaleY)
{
	CContentTextContext* pC = new CContentTextContext;
	pC->m_pGraphics = pGraphics;
	pC->m_pContentText = this;

//	pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
	//pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
//	pGraphics->SetTextContrast(99);

	if (pRenderer)
	{
		if (pRenderer->m_customRenderer)
		{
			pRenderer->m_customRenderer->RenderObject(pRenderer, this);
		}
	}

	if (m_pBox)
	{
		m_pBox->Render(pC);
	}

	delete pC;
}

STDMETHODIMP CPDContentText::RenderSelection(HDC hDC, IPDMatrix* matrix, ILDOMRange *range)
{
	if (m_pBox)
	{
		HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));

		CContentTextContext* pC = new CContentTextContext;
		pC->m_pContentText = this;

		m_pBox->RenderSelection(pC, hDC, matrix, range);

		delete pC;

		SelectObject(hDC, hOldPen);
		SelectObject(hDC, hOldBrush);
	}

	return S_OK;
}

STDMETHODIMP CPDContentText::get_objectType(PDObjectType *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = CONTENT_TEXT;
	return S_OK;
}

STDMETHODIMP CPDContentText::getPosUnderPoint(double x, double y, ILDOMNode **pNode, long *pOffset,/* [out,retval]*/ BOOL *bHit)
{
	ATLASSERT(pNode);
	ATLASSERT(pOffset);
	ATLASSERT(bHit);

	if (pNode == NULL) return E_POINTER;
	if (pOffset == NULL) return E_POINTER;
	if (bHit == NULL) return E_POINTER;

	*pNode = NULL;
	*pOffset = 0;

	if (m_pBox)
	{
		*bHit = m_pBox->getPosUnderPoint(x, y, pNode, pOffset);
	}
	else
	{
		*bHit = FALSE;
	}

	return S_OK;
}

void CPDContentText::OnChangedTextFrameOptions()
{
	CalculateBounds();

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
}

#if 0
STDMETHODIMP CPDContentText::saveAsXML(IDOMDocument *document, IDOMNode *node, BOOL saveId)
{
	HRESULT hr;
	hr = CPDObjectTextImpl<IPDContentText>::saveAsXML(document, node, saveId);
	if (FAILED(hr)) return hr;

	return S_OK;
}

STDMETHODIMP CPDContentText::loadXML(/*[in]*/ IDOMNode* node)
{
	HRESULT hr;
	hr = CPDObjectTextImpl<IPDContentText>::loadXML(node);
	if (FAILED(hr)) return hr;

	ATLASSERT(0);
	return S_OK;
}
#endif

/*
STDMETHODIMP CPDContentText::getExpandedBBox(RectD *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
*/

// IPDObjectLocatable
STDMETHODIMP CPDContentText::Move(/*[in]*/ double dx, /*[in]*/ double dy)
{
	ATLASSERT(0);
	return S_OK;
}

STDMETHODIMP CPDContentText::getScreenBBox(/*[out,retval]*/ RectD* pVal)
{
	CPDObjectFrame* pFrame = static_cast<CPDObjectFrame*>((IPDObjectFrame*)m_parent);

	if (pFrame)
		pFrame->getScreenBBox(pVal);
	else
		ATLASSERT(0);

	return S_OK;
}

STDMETHODIMP CPDContentText::setColumns(long ncolumns, double columnGutter, double columnWidth, VARIANT_BOOL fixedWidth)
{
	CPDObjectFrame* pFrame = static_cast<CPDObjectFrame*>((IPDObjectFrame*)m_parent);

	ATLASSERT(pFrame);	// TODO, not always case ??

	if (ncolumns != tomUndefined) m_columnsNumber = ncolumns;
	if (columnGutter != tomUndefined) m_columnsGutter = columnGutter;

	if (columnWidth != tomUndefined)
		m_columnsWidth = columnWidth;
	else
		columnWidth = m_columnsWidth;

	if (fixedWidth != 2) m_columnsFixedWidth = fixedWidth;
	ATLASSERT(m_columnsFixedWidth == VARIANT_TRUE || m_columnsFixedWidth == VARIANT_FALSE);

	if (m_columnsFixedWidth)
	{
		double frameWidth = (m_columnsNumber * columnWidth) + (m_columnsNumber-1)*columnGutter;
		double sx = frameWidth/pFrame->m_bounds.Width;
		if (sx != 1.0)
		{
			pFrame->Scale(pFrame->m_bounds.X, pFrame->m_bounds.Y, sx, 1.0);
		}
	}

//	pFrame->CalculateBounds();	// This will call our CalculateBounds as well

	if (fixedWidth)
	{
		//ATLASSERT(m_columnsWidth == columnWidth);
	}

	OnChangedTextFrameOptions();	// TODO Have this ??

	return S_OK;
}

// Convert degrees to radians for math functions.
#define RAD(x) ((x) * 3.1415927 / 180)

/****************************************************************************
 *  FUNCTION   : FixedFromDouble
 *  RETURNS    : FIXED value representing the given double.
 ****************************************************************************/

FIXED PASCAL NEAR FixedFromDouble(double d)
{
    long l;

    l = (long) (d * 65536L);
    return *(FIXED *)&l;
}

/****************************************************************************
 *  FUNCTION   : IntFromFixed
 *  RETURNS    : int value approximating the FIXED value.
 ****************************************************************************/

int PASCAL NEAR IntFromFixed(FIXED f)
{
    if (f.fract >= 0x8000)
	return(f.value + 1);
    else
	return(f.value);
}

/****************************************************************************
 *  FUNCTION   : fxDiv2
 *  RETURNS    : (val1 + val2)/2 for FIXED values
 ****************************************************************************/

FIXED PASCAL NEAR fxDiv2(FIXED fxVal1, FIXED fxVal2)
{
    long l;

    l = (*((long far *)&(fxVal1)) + *((long far *)&(fxVal2)))/2;
    return(*(FIXED *)&l);
}


/****************************************************************************
 *  FUNCTION   : MakeRotationMat
 *  PURPOSE    : Fill in a rotation matrix based on the given angle.
 *  RETURNS    : none.
 ****************************************************************************/
/*
void MakeRotationMat(LPMAT2 lpMat, double dAngle)
{
    lpMat->eM11 = FixedFromDouble(cos(RAD(dAngle)));
    lpMat->eM12 = FixedFromDouble(sin(RAD(dAngle)));
    lpMat->eM21 = FixedFromDouble(-sin(RAD(dAngle)));
    lpMat->eM22 = FixedFromDouble(cos(RAD(dAngle)));
}
*/
/****************************************************************************
 *  FUNCTION   : ShearMat
 *  PURPOSE    : Fill in a 0.25 horizontal shear matrix.
 *  RETURNS    : none.
 ****************************************************************************/
/*
void ShearMat(LPMAT2 lpMat)
{
    lpMat->eM11 = FixedFromDouble(1);
    lpMat->eM12 = FixedFromDouble(0);
    lpMat->eM21 = FixedFromDouble(0.25);
    lpMat->eM22 = FixedFromDouble(1);
}
*/
/****************************************************************************
 *  FUNCTION   : IdentityMat
 *  PURPOSE    : Fill in matrix to be the identity matrix.
 *  RETURNS    : none.
 ****************************************************************************/
void IdentityMat(LPMAT2 lpMat)
{
    lpMat->eM11 = FixedFromDouble(1);
    lpMat->eM12 = FixedFromDouble(0);
    lpMat->eM21 = FixedFromDouble(0);
    lpMat->eM22 = FixedFromDouble(1);
}

CDblPoint FixedPt2FIX(POINTFX fx)
{
	CDblPoint apt;
//	apt.x = *(long*)&fx.x;// (long)(fx.x.fract/65536.0 + fx.x.value)*65536;
//	apt.y = *(long*)&fx.y;//(long)(fx.y.fract/65536.0 + fx.y.value)*65536;

	apt.x = (fx.x.fract/65536.0 + fx.x.value);
	apt.y = (fx.y.fract/65536.0 + fx.y.value);
	return apt;
}

/****************************************************************************
 *  FUNCTION   : MakeBezierFromQBSpline
 *
 *  PURPOSE    : Converts a quadratic spline in pSline to a four point Bezier
 *               spline in pPts.
 *
 *
 *  RETURNS    : number of Bezier points placed into the pPts POINT array.
 ****************************************************************************/ 
UINT MakeBezierFromQBSpline( CDblPoint* pPts, POINTFX *pSpline )
{
    CDblPoint P0,         // Quadratic on curve start point
            P1,         // Quadratic control point
            P2;         // Quadratic on curve end point
//    UINT    cTotal = 0;

    // Convert the Quadratic points to integer
	/*
    P0.x = IntFromFixed( pSpline[0].x );
    P0.y = IntFromFixed( pSpline[0].y );
    P1.x = IntFromFixed( pSpline[1].x );
    P1.y = IntFromFixed( pSpline[1].y );
    P2.x = IntFromFixed( pSpline[2].x );
    P2.y = IntFromFixed( pSpline[2].y );
*/

	 P0 = FixedPt2FIX(pSpline[0]);
	 P1 = FixedPt2FIX(pSpline[1]);
	 P2 = FixedPt2FIX(pSpline[2]);

    // conversion of a quadratic to a cubic

    // Cubic P0 is the on curve start point
    pPts[0] = P0; // Don't add the first point, already added
    
    // Cubic P1 in terms of Quadratic P0 and P1
    pPts[1] = CDblPoint(
		P0.x + 2*(P1.x - P0.x)/3,
		P0.y + 2*(P1.y - P0.y)/3);

    // Cubic P2 in terms of Qudartic P1 and P2
    pPts[2] = CDblPoint(
		P1.x + 1*(P2.x - P1.x)/3,
		P1.y + 1*(P2.y - P1.y)/3);

    // Cubic P3 is the on curve end point
    pPts[3] = P2;

    return 4;
}

/****************************************************************************
 *  FUNCTION   : AppendQuadBSplineToBezier
 *
 *  PURPOSE    : Converts Quadratic spline segments into their Bezier point 
 *               representation and appends them to a list of Bezier points. 
 *
 *               WARNING - The array must have at least one valid
 *               start point prior to the address of the element passed.
 *
 *  RETURNS    : number of Bezier points added to the POINT array.
 ****************************************************************************/ 
UINT AppendQuadBSplineToBezier( IPDSubPath* subpath/*CArray<CDblPoint,CDblPoint&>& pt*/, POINTFX start, LPTTPOLYCURVE lpCurve, double offsetx, double offsety)
{
	WORD                i;
	UINT                cTotal = 0;
	POINTFX             spline[3];  // a Quadratic is defined by 3 points
	CDblPoint           bezier[4];  // a Cubic by 4
	
	// The initial A point is on the curve.
	spline[0] = start;
	
	BezierPoint bpt;
	
	int j = 0;

	for (i = 0; i < lpCurve->cpfx; j++)
	{
		// The B point.
		spline[1] = lpCurve->apfx[i++];
		
		// Calculate the C point.
		if (i == (lpCurve->cpfx - 1))
		{
			// The last C point is described explicitly
			// i.e. it is on the curve.
			spline[2] = lpCurve->apfx[i++];
		}     
		else
		{
			// C is midpoint between B and next B point
			// because that is the on curve point of 
			// a Quadratic B-Spline.
			spline[2].x = fxDiv2(
				lpCurve->apfx[i-1].x,
				lpCurve->apfx[i].x
				);
			spline[2].y = fxDiv2(
				lpCurve->apfx[i-1].y,
				lpCurve->apfx[i].y
				);
		}
		
		// convert the Q Spline to a Bezier
		MakeBezierFromQBSpline( bezier, spline );
		
		// append the Bezier to the existing ones
		// Point 0 is Point 3 of previous.
		// pt[cTotal++] = bezier[1];   // Point 1
		// pt[cTotal++] = bezier[2];   // Point 2
		// pt[cTotal++] = bezier[3];   // Point 3
		/*
		pt.Add(bezier[1]);   // Point 1
		pt.Add(bezier[2]);   // Point 2
		pt.Add(bezier[3]);   // Point 3
		*/
		
		
		/*
		CComQIPtr<ISVGPathSegCurvetoCubicAbs> cubic;
		cubic.CoCreateInstance(CLSID_SVGPathSegCurvetoCubicAbs);
		cubic->put_x1(bezier[1].x + offsetx); cubic->put_y1(-bezier[1].y + offsety);
		cubic->put_x2(bezier[2].x + offsetx); cubic->put_y2(-bezier[2].y + offsety);
		cubic->put_x(bezier[3].x + offsetx); cubic->put_y(-bezier[3].y + offsety);
		seglist->appendItem(cubic, NULL);
		*/
		if (j == 0)
		{
			bpt.x = bezier[0].x + offsetx;
			bpt.y = -bezier[0].y + offsety;
			bpt.x1 = bezier[0].x + offsetx;
			bpt.y1 = -bezier[0].y + offsety;
		}

		bpt.x2 = bezier[1].x + offsetx;
		bpt.y2 = -bezier[1].y + offsety;
		
		long index;
		subpath->appendPoint(bpt.x, bpt.y, bpt.x1, bpt.y1, bpt.x2, bpt.y2, &index);
		
		bpt.x1 = bezier[2].x + offsetx;
		bpt.y1 = -bezier[2].y + offsety;
		
		bpt.x = bezier[3].x + offsetx;
		bpt.y = -bezier[3].y + offsety;
		
		// New A point for next slice of spline is the 
		// on curve C point of this B-Spline
		spline[0] = spline[2];
	}

	bpt.x2 = bpt.x;
	bpt.y2 = bpt.y;
	long index;
	subpath->appendPoint(bpt.x, bpt.y, bpt.x1, bpt.y1, bpt.x2, bpt.y2, &index);

	return cTotal;
}

BOOL AddCharToSegList(IPDPath* seglist, HDC hdc, int ch, double offsetx, double offsety)
{
	DWORD cbBuffer = 0;
	LPBYTE lpBuffer = NULL;

	GLYPHMETRICS	gm;

	MAT2 mat2;// = {{1,0},{0,0},{0,0},{1,0}};
	IdentityMat(&mat2);

// Get required size
	cbBuffer = GetGlyphOutline(hdc, ch, GGO_NATIVE, &gm, 0, NULL, &mat2);
	if (cbBuffer == -1)
	{
	//	TCHAR buf[256];
	//	wsprintf(buf, "GetGlyphOutline() = %d", GetLastError());
	//	MessageBox(NULL, buf, "", MB_OK);

		return FALSE;
	}

	lpBuffer = (LPBYTE)GlobalAlloc(0, cbBuffer);
	if (GetGlyphOutline(hdc, ch, GGO_NATIVE, &gm, cbBuffer, lpBuffer, &mat2) == -1)
	{
	//	MessageBox(NULL, "Error GetGlyphOutline()", "", MB_OK);
		return FALSE;
	}

	POINTFX	ptStart;

	LPTTPOLYGONHEADER hdr = (LPTTPOLYGONHEADER)lpBuffer;

	int charsubcurves = 0;

	while ((DWORD)hdr < (DWORD)(((LPSTR)lpBuffer) + cbBuffer))
	{
		if (hdr->dwType == TT_POLYGON_TYPE)
		{
			CDblPoint  apt;

			POINTFX	pfx[3];

			pfx[0] = hdr->pfxStart;

			apt = FixedPt2FIX(hdr->pfxStart);

			/*
			CComQIPtr<ISVGPathSegMovetoAbs> moveto;
			moveto.CoCreateInstance(CLSID_SVGPathSegMovetoAbs);
			moveto->put_x(apt.x + offsetx);
			moveto->put_y(-apt.y + offsety);
			seglist->appendItem(moveto, NULL);
			*/
			CComPtr<IPDSubPath> subpath;
			seglist->createSubPath(&subpath);
			seglist->insertSubPath(-1, subpath);

			BezierPoint bpt;
			bpt.x = apt.x + offsetx;
			bpt.y = -apt.y + offsety;
			bpt.x1 = bpt.x;
			bpt.y1 = bpt.y;
			bpt.x2 = bpt.x;
			bpt.y2 = bpt.y;

			long index;
			subpath->appendPoint(bpt.x, bpt.y, bpt.x1, bpt.y1, bpt.x2, bpt.y2, &index);

			LPBYTE p = ((LPBYTE)hdr) + sizeof(TTPOLYGONHEADER);

			while ((DWORD)p < (DWORD)(((LPSTR)hdr) + hdr->cb))
			{
				LPTTPOLYCURVE curve = (LPTTPOLYCURVE)p;
				int size = 4 + curve->cpfx*sizeof(POINTFX);
//**********************************************
             // Format assumption:
             //   The bytes immediately preceding a POLYCURVE
             //   structure contain a valid POINTFX.
             // 
             //   If this is first curve, this points to the 
             //      pfxStart of the POLYGONHEADER.
             //   Otherwise, this points to the last point of
             //      the previous POLYCURVE.
             // 
             //   In either case, this is representative of the
             //      previous curve's last point.
             //**********************************************

             ptStart = *(LPPOINTFX)((LPSTR)curve - sizeof(POINTFX));

				if (curve->wType == TT_PRIM_LINE)
				{
					for (int i = 0; i < curve->cpfx; i++)
					{
						apt = FixedPt2FIX(curve->apfx[i]);

						/*
						CComQIPtr<ISVGPathSegLinetoAbs> lineto;
						lineto.CoCreateInstance(CLSID_SVGPathSegLinetoAbs);
						lineto->put_x(apt.x + offsetx);
						lineto->put_y(-apt.y + offsety);
						seglist->appendItem(lineto, NULL);
						*/
						BezierPoint bpt;
						bpt.x = apt.x + offsetx;
						bpt.y = -apt.y + offsety;
						bpt.x1 = bpt.x;
						bpt.y1 = bpt.y;
						bpt.x2 = bpt.x;
						bpt.y2 = bpt.y;

						long index;
						subpath->appendPoint(bpt.x, bpt.y, bpt.x1, bpt.y1, bpt.x2, bpt.y2, &index);
					}
				}
				else if (curve->wType == TT_PRIM_QSPLINE)
				{
					AppendQuadBSplineToBezier(subpath, ptStart, curve, offsetx, offsety);
				}
#if 0
				else if (curve->wType == TT_PRIM_CSPLINE)
				{
					ASSERT((curve->cpfx % 3) == 0);

					for (int i = 0; i < curve->cpfx; i++)
					{
						apt = FixedPt2FIX(curve->apfx[i]);

						pBez->m_pointArray.Add(apt);
					}
				}
#endif
				else
					ATLASSERT(0);

				p += size;
			}

#if 0
			pBez->m_pointArray.Add(pBez->m_pointArray[pBez->m_pointArray.GetSize()-1]);

			ASSERT((pBez->m_pointArray.GetSize() % 3) == 0);

			for (int i = 0; i < pBez->m_pointArray.GetSize(); i++)
			{
				pBez->m_pointArray[i].y = 0 - pBez->m_pointArray[i].y;
			}

			pBez->MovePoints(TRUE, x, y);

			charsubcurves++;
			pBezList->AddTail(pBez);
#endif
		}
		else
			ATLASSERT(0);

		hdr = (LPTTPOLYGONHEADER)(((LPSTR)hdr) + hdr->cb);
	}

	GlobalFree(lpBuffer);

	return TRUE;
}
