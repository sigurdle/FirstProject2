#include "stdafx.h"
#include "LXML2.h"

#include "Window.h"
#include "LXMLDocumentView.h"

#include "PWord.h"
#include "PTextNode.h"
#include "PElementBase.h"
#include "PElementBox.h"

#include "HTMContext.h"

namespace System
{
namespace Web
{

CHTMPCharacterBox::CHTMPCharacterBox(PText* pTextNode)
{
	m_pTextNode = pTextNode;
}

#if 0
void CHTMPCharacterBox::GetSel(CHTMRenderContext* pC, int& startChar, int& endChar, int length)
{
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

		if (!pC->m_bInSelection)
		{
			int len = m_pTextNode->m_dataLength;

			// Check for start of selection
			if ((startContainer == m_pTextNode->m_pNode) &&
					(startOffset >= m_start) &&
					(
						(startOffset < m_start+length) ||
						(m_start+length == len && startOffset == m_start+length)))
			{
				pC->m_bInSelection = TRUE;
				startChar = startOffset - m_start;
			}
			else
				startChar = -1;
		}
		else
			startChar = 0;

		if (pC->m_bInSelection)
		{
			// Check for end of selection
			if ((endContainer == m_pTextNode->m_pNode) &&
				(endOffset >= m_start && endOffset <= m_start+length))
			{
				ASSERT(endOffset >= m_start);

				pC->m_bInSelection = FALSE;
				endChar = endOffset - m_start;
			}
			else
			{
				endChar = length;
			}
		}
	}
	else
#endif
	{
		startChar = -1;
		endChar = -1;
	}
}
#endif

void CHTMPCharacterBox::DrawTextDecoration(CHTMRenderContext* pC, gm::RectF& trect)
{
	ASSERT(0);
#if 0
	if (m_parentBox == NULL)
		return;

	LDraw::Font* pFont = m_pTextNode->m_rparent->GetFont()->m_pFont;
	PElementBase* pElement = (PElementBase*)((CHTMElementBox*)m_parentBox)->m_pElement;

	if (pElement->m_computedTextUnderlineStyle != BorderStyle_none)//& 1/*underline*/)
	{
	//	LDraw::FontFamily* fontFamily = pFont->GetFamily();

		double ascentPixel = pFont->GetCellAscent();

	//	double ascentPixel = pFont->GetSize() * ascent / pFont->GetEmHeight();

		/*
		pC->m_pGraphics->DrawLine(&LDraw::Pen(pElement->m_computedTextUnderlineColor, 1),
			LDraw::PointF(trect.X, trect.Y+ascentPixel+1),
			LDraw::PointF(trect.GetRight(), trect.Y+ascentPixel+1));
			*/

		LDraw::SmoothingMode oldSmoothingMode = pC->m_pGraphics->GetSmoothingMode();
	//	pC->m_pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

		pC->m_pGraphics->FillRectangle(new LDraw::SolidBrush(pElement->m_computedTextUnderlineColor),
			trect.X, trect.Y+ascentPixel, trect.Width, 1);

		pC->m_pGraphics->SetSmoothingMode(oldSmoothingMode);
	}
#endif
}

//////////////////////////////////////////////////
// CHTMSpace

//virtual
bool CHTMPSpace::getPosUnderPoint(double x, double y, PNode **pNode, long *pOffset)
{
/*
	LDraw::Rect rc = GetAbsOuterRect();

	double dx = x - rc.X;

	for (long offset = 0; offset < m_charOffsets.GetSize()-1; offset++)
	{
		double mx = m_charOffsets[offset+1]-(m_charOffsets[offset+1]-m_charOffsets[offset])/2;
		if (dx < mx) break;
	}
*/
	if (m_pTextNode->m_realNode)
	{
		*pNode = m_pTextNode->m_realNode;
		*pOffset = m_pTextNode->m_realOffset + m_start;
	}
	else
	{
		*pNode = m_pTextNode;
		*pOffset = m_start;//+offset;
	}

// Note, we always returns TRUE, so caller must make sure that the point is
// over the word
	return true;
}

// virtual
void CHTMPSpace::CalculateDimensions(CHTMCalcContext* pC)
{
	//return;
	ASSERT(m_pTextNode->m_rparent->GetFont());
#if 0
	gm::Font* pFont = m_pTextNode->m_rparent->GetFont()->m_pFont;//m_computedFontFamily[0]->GetGdipFont();

#if 0
	HFONT hFont = m_pTextNode->m_rparent->m_computedFontFamily[0]->GetHintedHFONT();
	ASSERT(pFont);

	LDraw::Unit unit = pFont->GetUnit();

	HDC hDC = pC->m_pGraphics->GetHDC();

	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	TEXTMETRIC tm;
	GetTextMetrics(hDC, &tm);

	tm.tmHeight;

	SelectObject(hDC, hOldFont);

	pC->m_pGraphics->ReleaseHDC(hDC);
#endif

//	LDraw::GraphicsO graphics;

	gm::RectF size(0,0,0,0);
	ASSERT(0);
#if 0
	size.Width = LDraw::Graphics2D::MeasureString(" ", 1, pFont, LDraw::SmoothingModeNone);
	//size = LDraw::RectF(0,0,10,10);
#endif

//	double h = pFont->GetHeight(pC->m_pGraphics);

	m_chars.Add(Char(0));
	m_chars.Add(Char(size.Width));

	m_outerRect.Width = size.Width;
//	m_outerRect.Height = size.Height;

	m_outerRect.Height = pFont->GetSize();

#if 0
	m_outerRect.Height = tm.tmHeight;//m_pTextNode->m_rparent->m_computedFontSize;	//
#endif
#endif
}

void CHTMPSpace::Draw(CHTMRenderContext* pC)
{
	ASSERT(0);
#if 0
	LDraw::Font* pFont = m_pTextNode->m_rparent->GetFont()->m_pFont;//m_computedFontamily[0]->GetGdipFont();

//	int startChar = -1;
//	int endChar = -1;
	int length = 1;

//	GetSel(pC, startChar, endChar, length);

//	LDraw::SolidBrush textbrush(LDraw::Color(0,0,0));	// TODO

	LDraw::RectF trect = m_outerRect;
#if 0
	trect.Offset(pC->m_outerPos.X, pC->m_outerPos.Y);
#endif

#if 0
	if (startChar >= 0 && endChar >= 0 && startChar != endChar)
	{
	//	LDraw::Rect trect = GetAbsOuterRect();

		LDraw::RectF selrect = trect;//m_outerRect;

		/*
		selrect.X = trect.X + m_charOffsets[startChar];
		selrect.Y = trect.Y;
		selrect.Width = m_charOffsets[endChar]-m_charOffsets[startChar];
		selrect.Height = trect.Height;
		*/

		COLORREF clrbg = GetSysColor(COLOR_HIGHLIGHT);
		COLORREF clrfg = GetSysColor(COLOR_HIGHLIGHTTEXT);

		LDraw::SolidBrush bgbrush(LDraw::Color(GetRValue(clrbg), GetGValue(clrbg), GetBValue(clrbg)));
		LDraw::SolidBrush fgbrush(LDraw::Color(GetRValue(clrfg), GetGValue(clrfg), GetBValue(clrfg)));
/*
		pC->m_pGraphics->DrawString(&((BSTR)m_text)[0],
			startChar, pC->m_pFont,
			LDraw::PointF(trect.X, trect.Y),
			pStringFormat,
			&textbrush);
*/
		pC->m_pGraphics->FillRectangle(&bgbrush, selrect);
/*
		pC->m_pGraphics->DrawString(&((BSTR)m_text)[startChar],
			(endChar-startChar),
			pC->m_pFont,
			LDraw::PointF(trect.X+m_charOffsets[startChar], trect.Y),
			pStringFormat,
			&fgbrush);

		pC->m_pGraphics->DrawString(&((BSTR)m_text)[endChar],
			length-endChar,
			pC->m_pFont,
			LDraw::PointF(trect.X+m_charOffsets[endChar], trect.Y),
			pStringFormat,
			&textbrush);
  */
	}
	else
#endif
	{
/*		pC->m_pGraphics->DrawString(
			m_text,
			m_text.length(),
			pC->m_pFont,
			LDraw::PointF(trect.X, trect.Y),
			pStringFormat,
			&textbrush);
*/	}

	DrawTextDecoration(pC, trect);
#endif
}

//////////////////////////////////////////////////
// CHTMWord

//virtual
bool CHTMPWord::getPosUnderPoint(double x, double y, PNode **pNode, long *pOffset)
{
	gm::RectF rc = GetAbsOuterRect();

	double dx = x - rc.X;

	uint offset;

	for (offset = 0; offset < m_chars.GetSize()-1; ++offset)
	{
		double mx = m_chars[offset+1].offset-(m_chars[offset+1].offset-m_chars[offset].offset)/2;
		if (dx < mx) break;
	}

	if (m_pTextNode->m_realNode)
	{
		*pNode = m_pTextNode->m_realNode;
		*pOffset = m_pTextNode->m_realOffset + m_start+offset;
	}
	else
	{
		*pNode = m_pTextNode;
		*pOffset = m_start+offset;
	}

// Note, we always returns TRUE, so caller must make sure that the point is
// over the word
	return true;
}

// virtual
void CHTMPWord::CalculateDimensions(CHTMCalcContext* pC)
{
	ASSERT(0);
#if 0
	m_chars.RemoveAll();

#if 0	// TODO
	HDC hDC = pC->m_pGraphics->GetHDC();
	//HDC hDC = CreateCompatibleDC(NULL);
	HFONT hFont = m_pTextNode->m_rparent->m_computedFontFamily[0]->GetHintedHFONT();

	/*
	LOGFONT lf;

	{
		LDraw::Graphics graphics(hDC);
		pFont->GetLogFontA(&graphics, &lf);
	}
	*/

//	SetMapMode(hDC, MM_ANISOTROPIC);
//	SetWindowExtEx(hDC, 1, 1, NULL);
//	SetViewportExtEx(hDC, 10, 10, NULL);

	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	TEXTMETRIC tm;
	GetTextMetrics(hDC, &tm);

//	int* pidx = new int(m_len	*	(3/2+1)*2);

	BYTE inClass = GCPCLASS_LATIN;

	SCRIPT_STRING_ANALYSIS ssa = NULL;

	HRESULT hr = ScriptStringAnalyse(hDC,
		(BSTR)m_text,//(char*)_bstr_t(m_text),
		m_len,
		m_len	*	(3/2+1)*2,
		-1,//lf.lfCharSet,//-1,	// unicode
		SSA_GLYPHS,	// dwFlags
		0,	// iReqWidth
		NULL,	// psControl
		NULL, // psState
		NULL,//pidx,	// pidx
		NULL,	// pTabDef
		&inClass, // pbInClass
		&ssa);
	ASSERT(SUCCEEDED(hr));

	const int* pcChars = ScriptString_pcOutChars(ssa);

	int* idx = new int[m_len * (3/2+1)*2];
	hr = ScriptStringGetLogicalWidths(ssa, idx);
	ASSERT(SUCCEEDED(hr));

	double sizex = 0;

	for (int i = 0; i < m_len; i++)
	{
		m_charOffsets.Add(sizex);

		sizex += (double)idx[i];///10;
	}

	m_charOffsets.Add(sizex);
	m_outerRect.Width = sizex;

	ScriptStringFree(&ssa);

	SelectObject(hDC, hOldFont);
	//DeleteDC(hDC);
	pC->m_pGraphics->ReleaseHDC(hDC);

	delete [] idx;

//	ASSERT(tm.tmHeight == m_pTextNode->m_rparent->m_computedFontSize);

	m_outerRect.Height = tm.tmHeight;//m_pTextNode->m_rparent->m_computedFontSize;//m_computedFontFamily[0]->size.Height;
#else

//	return;	// TODO remove
	ASSERT(m_pTextNode->m_rparent->GetFont());
	LDraw::Font* pFont = m_pTextNode->m_rparent->GetFont()->m_pFont;//m_computedFontFamily[0]->GetGdipFont();

	CharacterData* charData = static_cast<CharacterData*>(m_pTextNode->m_pNode);
	const WCHAR* m_text = charData->get_data()->c_str() + m_start;

	double sizex = 0;

	int unit = 0;
	while (unit < m_len)
	{
		m_chars.Add(Char(sizex));

		LDraw::RectF size(0,0,0,0);

	//	LDraw::GraphicsO graphics;
#if 1

		unsigned int n;
		WCHAR w1 = m_text[unit];
		if (w1 < 0xD800 || w1 > 0xDFFF)
			n = 1;
		else
			n = 2;

		size.Width = LDraw::Graphics2D::MeasureString(&m_text[unit], n, pFont/*, LDraw::PointF(0,0), pC->m_pStringFormat, &size*/, LDraw::SmoothingModeNone);
//		size = LDraw::RectF(0,0,10,10);
		sizex += size.Width;

		unit += n;
#else
		size.Width = pC->m_pGraphics->MeasureString(m_text, i+1, pFont/*, LDraw::PointF(0,0), pC->m_pStringFormat, &size*/);
		sizex = size.Width;
#endif
	}

	m_chars.Add(Char(sizex));
	m_outerRect.Width = sizex;

	{
		LDraw::RectF size(0,0,0,0);
		//ASSERT(0);
		size.Height = pFont->GetSize();	// ??
#if 0
		size.Height = pC->m_pGraphics->MeasureString(L" ", 1, pFont/*, LDraw::PointF(0,0), &size*/);
	//	size = LDraw::RectF(0,0,10,10);
#endif

		m_outerRect.Height = size.Height;
	}
#endif
#endif
}

void CHTMPWord::Draw(CHTMRenderContext* pC)
{
#if 0
	if (m_chars.GetSize() == 0)	// TODO remove
		return;

//	pC->m_pGraphics->PushTransform();
//	pC->m_pGraphics->TranslateTransform(innerRect.X, innerRect.Y);

//	CFontDef* pFontDef = m_pTextNode->m_rparent->m_computedFontFamily[0];

	LDraw::Font* pFont = m_pTextNode->m_rparent->GetFont()->m_pFont;//pFontDef->GetGdipFont();

	PElementBase* pElement = (PElementBase*)((CHTMElementBox*)m_parentBox)->m_pElement;

//	int startChar = -1;
//	int endChar = -1;
//	GetSel(pC, startChar, endChar, m_len);

//	LDraw::Rect trect = GetAbsOuterRect();

//	LDraw::RectF trect = m_outerRect;
//	trect.Offset(pC->m_outerPos.X, pC->m_outerPos.Y);
	LDraw::RectF trect = GetAbsOuterRect();//m_outerRect;//GetAbsOuterRect();

	LDraw::Brush* pColorBrush = pElement->GetColorBrush();

#if 0
	if (startChar >= 0 && endChar >= 0 && startChar != endChar)
	{
		LDraw::RectF selrect;

	/*
		if (startChar == endChar)
		{
			rect.X = rc.X + m_charOffsets[startChar];
			rect.Y = rc.Y;
			rect.Width = 2;
			rect.Height = rc.Height;
		}
		else
		*/
		{
			selrect.X = trect.X + m_chars[startChar].offset;
			selrect.Y = trect.Y;// + pFontDef->m_descent;
			selrect.Width = m_chars[endChar].offset-m_chars[startChar].offset;
			selrect.Height = trect.Height;
		}

		COLORREF clrbg = GetSysColor(COLOR_HIGHLIGHT);
		COLORREF clrfg = GetSysColor(COLOR_HIGHLIGHTTEXT);

		LDraw::SolidBrush bgbrush(LDraw::Color(GetRValue(clrbg), GetGValue(clrbg), GetBValue(clrbg)));
		LDraw::SolidBrush fgbrush(LDraw::Color(GetRValue(clrfg), GetGValue(clrfg), GetBValue(clrfg)));

		/*
		pC->m_pGraphics->DrawString(&m_text[0],
			startChar, pFont,
			LDraw::PointF(trect.X, trect.Y),
			pC->m_pStringFormat,
			pTextBrush);
			*/

		pC->m_pGraphics->FillRectangle(&bgbrush, selrect);

	// Draw each character
		for (int i = 0; i < m_len; i++)
		{
			pC->m_pGraphics->DrawString(
				(char*)&m_text[i],
				1,
				pFont,
				LDraw::PointF((trect.X+m_chars[i].offset), (trect.Y)),
				//pC->m_pStringFormat,
				(i >= startChar && i < endChar)? &fgbrush: pColorBrush);
		}

		/*
		pC->m_pGraphics->DrawString(&m_text[startChar],
			(endChar-startChar),
			pFont,
			LDraw::PointF(trect.X+m_charOffsets[startChar], trect.Y),
			pC->m_pStringFormat,
			&fgbrush);

		pC->m_pGraphics->DrawString(&m_text[endChar],
			m_len-endChar,
			pFont,
			LDraw::PointF(trect.X+m_charOffsets[endChar], trect.Y),
			pC->m_pStringFormat,
			pTextBrush);
			*/
	}
	else
#endif
	{
		DrawTextDecoration(pC, trect);

		CharacterData* charData = static_cast<CharacterData*>(m_pTextNode->m_pNode);
		const WCHAR* m_text = charData->get_data()->c_str() + m_start;

#if 0
		HDC hDC = pC->m_pGraphics->GetHDC();
		HFONT hOldFont = (HFONT)SelectObject(hDC, pFontDef->GetHFONT());

		for (int i = 0; i < m_len; i++)
		{
			TCHAR ch = m_text[i];
			TextOut(hDC, trect.X+m_charOffsets[i], trect.Y, &ch, 1);
		}

		SelectObject(hDC, hOldFont);
		pC->m_pGraphics->ReleaseHDC(hDC);
#else

	// Draw each character
		int nchar = 0;
		int unit = 0;
		while (unit < m_len)
		{
			WCHAR w1 = m_text[unit];
			unsigned int n;
			if (w1 < 0xD800 || w1 > 0xDFFF)
				n = 1;
			else
				n = 2;

			pC->m_pGraphics->DrawString(
				&m_text[unit],
				n,
				pFont,
				gm::PointF(trect.X+m_chars[nchar].offset, trect.Y),
			//	pC->m_pStringFormat,
				pColorBrush);

			unit += n;
			nchar++;
		}
			/*
		pC->m_pGraphics->DrawString(
			m_text,
			m_len,
			pFont,
			LDraw::PointF(trect.X, trect.Y),
			pC->m_pStringFormat,
			pTextBrush);
			*/
#endif
	}

//	pC->m_pGraphics->PopTransform();//oldtransform);
#endif
}

}	// Web
}	// System
