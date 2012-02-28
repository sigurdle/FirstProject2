#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGTextContentElement.h"
//#include "PSVGFilterElement.h"
#include "PSVGFontElement.h"
#include "SVGFontElement.h"

#include "PSVGGlyphElement.h"
#include "SVGGlyphAttributesImpl.h"

namespace System
{
namespace Web
{

//void DrawPathSegList(CLSVGPathSegList* seglist, LDraw::GraphicsPathF* path, CLSVGMatrix* matrix);
//void GetPathSegListBBox(CLSVGPathSegList* seglist, CLSVGMatrix* matrix, LDraw::RectD* bbox);

PSVGElement* CloneRenderTree(PSVGElement* pParent, PSVGElement* pElement);

/////////////////////////////////////////////////////////////////////////////////
// CPSVGText

void PSVGText::CalculateTextDimensions(CHTMCalcContext* pC, String data2, int length2/*Use this ??*/)
{
	RemoveGlyphs();	// hm..

	ASSERT(m_glyphs.GetSize() == 0);

	String data;

	if (TRUE)	// xml:space=default
	{
/*
default (the initial/default value for xml:space) -
When xml:space="default", the SVG user agent will do the following using a copy of
the original character data content. First, it will remove all newline characters.
Then it will convert all tab characters into space characters. Then, it will strip
off all leading and trailing space characters. Then, all contiguous space characters
will be consolidated. 

*/

		int i = 0;
		int len = data2.GetLength();

		WCHAR* p = data2.GetData16();

		while (i < len && iswspace(p[i])) i++;	// Skip leading space characters

		while (i < len)
		{
			if (p[i] == '\n')	// Skip newline
			{
				i++;
			}
			else
			{
				if (iswspace(p[i]))	// Concatenate white space into one space
				{
					i++;
					while (i < len && iswspace(p[i]))
					{
						i++;
					}

					if (i < len)	// don't include trailing whitespace
					{
						data += L" ";
					}
				}
				else
				{
					data += p[i];
					++i;
				}
			}
		}
	}
	else	// xml:space=preserve
	{
	/*
preserve -
When xml:space="preserve", the SVG user agent will do the following using a copy of
the original character data content. It will convert all newline and tab characters
into space characters. Then, it will draw all space characters, including leading,
trailing and multiple contiguous space characters. Thus, when drawn with
xml:space="preserve", the string "a   b" (three spaces between "a" and "b") will
produce a larger separation between "a" and "b" than "a b"
(one space between "a" and "b"). 
	*/
	}

	int length = data.GetLength();

	WCHAR* p = data.GetData16();

	vector<int> words;
	{
		int i = 0;
		while (i < length)
		{
			int start = i;
			while (i < length && !iswspace(p[i]))
			{
				i++;
			}

			while (i < length && iswspace(p[i]))
			{
				i++;
			}

			words.Add(i-start);
		}
	}

	m_owner->m_parent->GetFont();

// CGlyphGroup* pGlyphGroup = new CGlyphGroup;

// Build glyphs

	/*
	CPSVGFontElement* pSVGFont = m_parent->m_computedFontFamily[0]->m_pSVGFontElement;//((PSVGElement*)m_parent)->m_pSVGFont;
	if (pSVGFont)
	{
		CLSVGFontElement* psvgFontElement = static_cast<CLSVGFontElement*>(pSVGFont->m_pNode);
		m_fontHeight = 0;

		double descent = pSVGFont->GetDescent();
		double ascent = pSVGFont->GetAscent();

		double scale = m_parent->m_computedFontSize / pSVGFont->GetUnitsPerEm();

		m_fontHeight = (ascent-descent)*scale;//max(m_fontHeight, bounds.Height*scale);

		int i = 0;
		while (i < length)
		{
			CPSVGGlyphElement* pSVGGlyphElement;
			int ncount = pSVGFont->FindGlyph(&((BSTR)data)[i], &pSVGGlyphElement);

			CGlyph* pGlyph = new CGlyph;

			pGlyph->m_scale = scale;

			pGlyph->m_descent = -descent*scale;

			if (pSVGGlyphElement)
			{
				CComQIPtr<ILSVGGlyphAttributes> glyphAttributes = pSVGGlyphElement->m_pNode;

				CLSVGGlyphAttributesImpl* psvgGlyphElement = static_cast<CLSVGGlyphAttributesImpl*>(glyphAttributes.p);

				if (psvgGlyphElement->m_d->m_value->m_value->m_normalizedseglist->m_items.GetSize())
				{
					pGlyph->m_seglist = psvgGlyphElement->m_d->m_value->m_value->m_normalizedseglist;
					pGlyph->m_seglist->AddRef();

				//	RectD bounds;
				//	GetPathSegListBBox(pGlyph->m_seglist, NULL, &bounds);

					//pGlyph->m_charWidth = bounds.Width;//(pGlyph->m_pGlyphRoot->m_bounds.X+pGlyph->m_pGlyphRoot->m_bounds.Width)*scale;
					if (psvgGlyphElement->m_horiz_adv_x->m_specified)
						pGlyph->m_charWidth = psvgGlyphElement->m_horiz_adv_x->m_value->m_value->m_value;
					else
						pGlyph->m_charWidth = psvgFontElement->m_horiz_adv_x->m_value->m_value->m_value;

					pGlyph->m_charWidth *= scale;

				//	m_fontHeight = max(m_fontHeight, bounds.Height*scale);

					DrawPathSegList(pGlyph->m_seglist, &pGlyph->m_GraphicsPathF, NULL);
				}

				if (FALSE)
				//if (!iswspace(ch))
				{
					pGlyph->m_pGlyphRoot = CloneRenderTree((PSVGElement*)m_parent, pSVGGlyphElement);

					pGlyph->m_charWidth = (pGlyph->m_pGlyphRoot->m_bounds.X+pGlyph->m_pGlyphRoot->m_bounds.Width)*scale;

			// TODO
					m_fontHeight = max(m_fontHeight, pGlyph->m_pGlyphRoot->m_bounds.Height);
				}
			}

			m_glyphs.Add(pGlyph);

			i += ncount;
		}

	// Add one empty glyph after
		CGlyph* pGlyph = new CGlyph;
		m_glyphs.Add(pGlyph);
	}
	else
	*/
	{
		m_fontHeight = m_owner->m_parent->m_computedFontSize;//m_parent->m_pFont->GetSize();

	//	HDC hDC = CreateCompatibleDC(NULL);

		//ASSERT(m_parent->m_pFont != NULL);
		//if (m_parent->m_pFont->GetLastStatus() == LDraw::Ok)
			//LDraw::Graphics graphics(hDC);

			/*
			LOGFONT lf;
			m_parent->m_pFont->GetLogFontA(&graphics, &lf);
			lf.lfCharSet = SHIFTJIS_CHARSET;
			HFONT hFont = CreateFontIndirect(&lf);
			*/

	//	HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);

		IDWriteFont* hFont[32] = {0};
	//	SCRIPT_FONTPROPERTIES sfp[32] = {0};
		int* idx[32] = {0};
		WORD* glyphs[32] = {0};

		PSVGGlyphElement* pDefault[32] = {0};
		PSVGGlyphElement* pCurrentGlyph[32] = {0};

		int nfont = 0;

	// We always add one glyph after the text

		CGlyphGroup* glyphGroup = new CGlyphGroup;
		m_glyphGroups.Add(glyphGroup);

		IDWriteFont* font;
		m_owner->m_parent->GetFont();
		m_owner->m_parent->m_computedFontFamily[m_owner->m_parent->m_ncomputedFontFamily]->m_dwriteFontFamily->GetFirstMatchingFont(DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_FONT_STYLE_NORMAL, &font);

		DWRITE_FONT_METRICS fontMetrics;
		font->GetMetrics(&fontMetrics);

		IDWriteFontFace* fontFace;
		font->CreateFontFace(&fontFace);

		int nch = 0;
		while (nch < length/*+1*/)
		{
			CGlyph* pGlyph = new CGlyph;
			UINT codepoint = p[nch];
			uint16 glyphIndex;
			fontFace->GetGlyphIndices(&codepoint, 1, &glyphIndex);
			pGlyph->m_glyphIndex = glyphIndex;
			pGlyph->m_emSize = m_fontHeight;

			DWRITE_GLYPH_METRICS glyphMetrics;
			fontFace->GetDesignGlyphMetrics(&glyphIndex, 1, &glyphMetrics, FALSE);

			pGlyph->m_charWidth = (float)glyphMetrics.advanceWidth * (pGlyph->m_emSize / fontMetrics.designUnitsPerEm);

			pGlyph->m_dwriteFontFace = fontFace;
			fontFace->AddRef();

			m_glyphs.Add(pGlyph);
			++nch;
		}
#if 0

		int nCurrentWord = 0;
		int nWordCh = 0;
		int nch = 0;
		while (nch < length+1)
		{
			int ncount;

		// Traverse the fontset and get the first font that supports the glyph
			uint nfont;
			for (nfont = 0; nfont < m_owner->m_parent->m_computedFontFamily.GetSize(); ++nfont)
			{
#if 0
				PSVGFontElement* pSVGFont = m_owner->m_parent->m_computedFontFamily[nfont]->m_pFamily->m_pSVGFontElement;

				if (pSVGFont)
				{
					if (pDefault[nfont] == NULL)	// First time on this font (TODO, that could be NULL)
					{
						pSVGFont->FindMissingGlyph(&pDefault[nfont]);
					}

					ncount = pSVGFont->FindGlyph(&((BSTR)data)[nch], &pCurrentGlyph[nfont]);
				}
				else	// Windows font
#endif

				{
					CGlyph* pGlyph = new CGlyph;

					if (hFont[nfont] == NULL)	// First time on this font
					{
						IDWriteFont* font;
						m_owner->m_parent->m_computedFontFamily[nfont]->m_dwriteFontFamily->GetFirstMatchingFont(DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_FONT_STYLE_NORMAL, &font);
						IDWriteFontFace* fontFace;
						font->CreateFontFace(&fontFace);

						UINT codepoint = p[nch];
						fontFace->GetGlyphIndices(&codepoint, 1, &pGlyph->m_glyphIndex);
						/*
						FontDef* pFont = new FontDef;
						pFont->m_dwriteFontFace = fontFace;
						pFont->AddRef();
						m_owner->m_parent->m_computedFont = pFont;
						*/

						hFont[nfont] = font;
					}

				//	hFont[nfont]->HasCharacter(p[nch], &exists);
				//	pGlyph->

					/*
					BOOL exists;
					hFont[nfont]->HasCharacter(p[nch], &exists);
					if (exists)
					{
						break;
					}
					*/

					//	hFont[nfont] = m_owner->m_parent->m_computedFontFamily[nfont]->GetHFONT();

					/*
						LOGFONT lf = {0};
						lf.lfHeight = -m_parent->m_computedFontSize;
						lf.lfWeight = m_parent->m_computedFontWeight;
						lf.lfItalic = m_parent->m_computedFontStyle != FontStyle_normal;
						strcpy(lf.lfFaceName, _bstr_t(m_parent->m_computedFontFamily[nfont]->m_pFamily->m_name));

						hFont[nfont] = CreateFontIndirect(&lf);
						*/

#if 0
						if (hFont[nfont])
						{
							SelectObject(hDC, hFont[nfont]);

							if (length > 0)
							{
								BYTE inClass = GCPCLASS_LATIN;

								SCRIPT_STRING_ANALYSIS ssa = NULL;

								HRESULT hr = ScriptStringAnalyse(hDC,
									(BSTR)data,//(char*)_bstr_t(m_text),
									length,
									length	*	(3/2+1)*2,
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

								idx[nfont] = new int[*pcChars/*length * (3/2+1)*2*/];
								hr = ScriptStringGetLogicalWidths(ssa, idx[nfont]);
								ASSERT(SUCCEEDED(hr));

								SCRIPT_CACHE sc = NULL;

								sfp[nfont].cBytes = sizeof(sfp[nfont]);
								hr = ScriptGetFontProperties(hDC, &sc, &sfp[nfont]);
								ASSERT(SUCCEEDED(hr));

								glyphs[nfont] = new WORD[length * 2];
								hr = ScriptGetCMap(hDC, &sc, data, length, 0, glyphs[nfont]);
								ASSERT(SUCCEEDED(hr));

								ScriptStringFree(&ssa);
							}
						}
#endif
					}

					ncount = 1;	// ??
				}

#if 0
				if (pSVGFont)	// Font is created
				{
					if (nch < length)
					{
						if (pCurrentGlyph[nfont] != pDefault[nfont])	// font supports this glyph, so use this font
						{
							break;
						}
					}
					else
					{
					// Text of length 0, we just use the first font that could be created
						break;
					}
				}
				else
#endif
					/*
				if (hFont[nfont])	// Font is created
				{
					if (nch < length)
					{
						if (glyphs[nfont][nch] != sfp[nfont].wgDefault)	// font supports this glyph, so use this font
						{
							break;
						}
					}
					else
					{
					// Text of length 0, we just use the first font that could be created
						break;
					}
				}
				*/
			}

			if (nfont == m_owner->m_parent->m_computedFontFamily.GetSize())
			{
			// None of the fonts supported the glyph, so we use the first fonts 'missing glyph' glyph
				nfont = 0;
			}

#if 0
			PSVGFontElement* pSVGFont = m_parent->m_computedFontFamily[nfont]->m_pFamily->m_pSVGFontElement;

			if (pSVGFont)
			{

				SVGFontElement* psvgFontElement = static_cast<SVGFontElement*>(pSVGFont->m_pNode);

				CGlyph* pGlyph = new CGlyph;
				pGlyph->m_group = glyphGroup;
				glyphGroup->m_glyphs.Add(pGlyph);

				double descent = pSVGFont->GetDescent();

				double scale = m_parent->m_computedFontSize / pSVGFont->GetUnitsPerEm();

				pGlyph->m_scale = scale;
				pGlyph->m_descent = -descent*scale;

				if (nch < length)
				{
					CPSVGGlyphElement* pSVGGlyphElement = pCurrentGlyph[nfont];

					CComQIPtr<ILSVGGlyphAttributes> glyphAttributes = pSVGGlyphElement->m_pNode;

					CLSVGGlyphAttributesImpl* psvgGlyphElement = static_cast<CLSVGGlyphAttributesImpl*>(glyphAttributes.p);

					if (psvgGlyphElement->m_d->m_value->m_value->m_normalizedseglist->m_items.GetSize())
					{
						pGlyph->m_seglist = psvgGlyphElement->m_d->m_value->m_value->m_normalizedseglist;
						pGlyph->m_seglist->AddRef();

						// Use adv_x on glyph if specified or use the one from font
						if (psvgGlyphElement->m_horiz_adv_x->m_specified)
							pGlyph->m_charWidth = psvgGlyphElement->m_horiz_adv_x->m_value->m_value->m_value;
						else
							pGlyph->m_charWidth = psvgFontElement->m_horiz_adv_x->m_value->m_value->m_value;

						pGlyph->m_charWidth *= scale;
					}
				}

				m_glyphs.Add(pGlyph);
			}
			else
#endif
				if (hFont[nfont])
			{
				double scale = m_owner->m_parent->m_computedFontSize / 2048;

			//	SelectObject(hDC, hFont[nfont]);

				/*
				TEXTMETRIC tm;
				GetTextMetrics(hDC, &tm);
				*/

				CGlyph* pGlyph = new CGlyph;
				pGlyph->m_group = glyphGroup;
				glyphGroup->m_glyphs.Add(pGlyph);

				pGlyph->m_scale = scale;

			//	pGlyph->m_descent = tm.tmDescent*scale;

				if (nch < length)
				{
			//		pGlyph->m_charWidth = idx[nfont][nch]*scale;

				//	pGlyph->m_seglist = new SVGPathSegList;
					//pGlyph->m_seglist->AddRef();

				//	pGlyph->m_seglist->AddCharToSegList(hDC, glyphs[nfont][nch], 0, 0);

				//	DrawPathSegList(pGlyph->m_seglist, &pGlyph->m_GraphicsPathF, NULL);

					/*
					if (TRUE)
					{
						LDraw::Matrix matrix;
						matrix.Scale(pGlyph->m_scale, -pGlyph->m_scale);
						pGlyph->m_GraphicsPathF.Transform(&matrix);
					}
					*/
				}

				m_glyphs.Add(pGlyph);
			}
			else
				ASSERT(0);

			nch += ncount;
			nWordCh += ncount;
			if (words[nCurrentWord] < nWordCh)
			{
				nWordCh -= words[nCurrentWord];
				nCurrentWord++;

				glyphGroup = new CGlyphGroup;
				m_glyphGroups.Add(glyphGroup);
			}
		}

	//	ASSERT(m_glyphs.GetSize() == length+1);	// TODO remove

	//	SelectObject(hDC, hOldFont);

		{
			for (uint i = 0; i < 32; ++i)
			{
				// NOTE: Do NOT Delete the HFONT, as it is cached in m_pView

				delete idx[i];
				delete glyphs[i];
			}
		}
#endif

	//	DeleteDC(hDC);
	}
}

// virtual
void PSVGText::OnTextContentChanged()
{
	RemoveGlyphs();

//	basCPTextNodeBase::OnTextContentChanged();	// Call base class
}

//virtual
void PSVGText::CalculateDimensions(CHTMCalcContext* pC)
{
	CharacterData* chardata = dynamic_cast<CharacterData*>(m_owner->m_pNode);

	uint length = chardata->get_length();
//	if (length > 0)
	{
		String data = chardata->get_data();

		CalculateTextDimensions(pC, data, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
// CPSVGTextContentElement

void PSVGElement::TransformGlyphs()
{
//	ASSERT(0);
#if 0
	double minx = 999999;
	double miny = 999999;
	double maxx = -999999;
	double maxy = -999999;

	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CPNode* pNode = (CPNode*)m_childList.GetNext(pos);
		if (pNode->m_type == LNODE_ELEMENT)
		{
			CComQIPtr<ILSVGElement> textContent = pNode->m_pNode;
			if (textContent)
			{
				PSVGElement* pSVGTextContent = (PSVGElement*)pNode;

				pSVGTextContent->TransformGlyphs();

				if (pSVGTextContent->m_bounds.Width > 0 && pSVGTextContent->m_bounds.Height > 0)
				{
					minx = min(minx, pSVGTextContent->m_bounds.X);
					miny = min(miny, pSVGTextContent->m_bounds.Y);
					maxx = max(maxx, pSVGTextContent->m_bounds.X+pSVGTextContent->m_bounds.Width);
					maxy = max(maxy, pSVGTextContent->m_bounds.Y+pSVGTextContent->m_bounds.Height);
				}
			}
		}
		else
		{
			CPSVGText* pTextNode = (CPSVGText*)pNode;

			for (int i = 0; i < pTextNode->m_glyphs.GetSize(); i++)
			{
				CGlyph* pGlyph = pTextNode->m_glyphs[i];

				if (pGlyph->m_seglist)
				{
					pGlyph->m_GraphicsPathF.Reset();
					DrawPathSegList(pGlyph->m_seglist, &pGlyph->m_GraphicsPathF, NULL);

					LDraw::Matrix matrix;

					matrix.RotateAt(pGlyph->m_rotation, pGlyph->m_position);
					matrix.Translate(pGlyph->m_position.X, pGlyph->m_position.Y);
					matrix.Scale(pGlyph->m_scale, -pGlyph->m_scale);

					pGlyph->m_GraphicsPathF.Transform(&matrix);

				// bounding box
					LDraw::Pen pen(LDraw::Color(0,0,0), (float)m_computedStrokeWidth);

					LDraw::RectF bounds;
					pGlyph->m_GraphicsPathF.GetBounds(&bounds, NULL, &pen);

					if (bounds.Width > 0 && bounds.Height > 0)
					{
						minx = min(minx, bounds.X);
						miny = min(miny, bounds.Y);
						maxx = max(maxx, bounds.X+bounds.Width);
						maxy = max(maxy, bounds.Y+bounds.Height);
					}
				}
			}
		}
	}

	RectD bounds;
	bounds.X = minx;
	bounds.Y = miny;
	bounds.Width = maxx-minx;
	bounds.Height = maxy-miny;

	m_bounds = bounds;	// TODO

	GetFillUriElement();
	GetStrokeUriElement();
	GetFilterElement();

	if (m_pFilterElement)
	{
		m_filterRect = m_pFilterElement->CalculateFilterRegion(this);
	}
	else
	{
		m_filterRect.X = bounds.X;
		m_filterRect.Y = bounds.Y;
		m_filterRect.Width = bounds.Width;
		m_filterRect.Height = bounds.Height;
	}

	m_expandedBBox = m_filterRect;

	gmMatrix3 matrix = GetLocalAnimatedMatrix();

	CalculateScale(matrix);
#endif
}

int PSVGElement::GetNumberOfGlyphs()
{
	ASSERT(0);
	long n = 0;
#if 0

	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CPNode* pNode = (CPNode*)m_childList.GetNext(pos);
		if (pNode->m_type == LNODE_ELEMENT)
		{
			CComQIPtr<ILSVGElement> textContent = pNode->m_pNode;
			if (textContent)
			{
				PSVGElement* pSVGTextContent = (PSVGElement*)pNode;

				n += pSVGTextContent->GetNumberOfGlyphs();
			}
		}
		else
		{
			CPSVGText* pTextNode = (CPSVGText*)pNode;

			n += pTextNode->m_glyphs.GetSize();
		}
	}
#endif
	return n;
}

CGlyph* PSVGElement::GetGlyphAtIndex(int& glyphnum)
{
	ASSERT(0);
#if 0
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CPNode* pNode = (CPNode*)m_childList.GetNext(pos);
		if (pNode->m_type == LNODE_ELEMENT)
		{
			CComQIPtr<ILSVGElement> textContent = pNode->m_pNode;
			if (textContent)
			{
				PSVGElement* pSVGTextContent = (PSVGElement*)pNode;

				CGlyph* pGlyph = pSVGTextContent->GetGlyphAtIndex(glyphnum);
				if (pGlyph)
				{
					return pGlyph;
				}
			}
		}
		else
		{
			CPSVGText* pTextNode = (CPSVGText*)pNode;

			if (glyphnum < pTextNode->m_glyphs.GetSize())
			{
				return pTextNode->m_glyphs[glyphnum];
			}

			glyphnum -= pTextNode->m_glyphs.GetSize();
		}
	}
#endif
	return NULL;
}

//virtual
bool PSVGText::GetCursorPosition(int cursorPos, gm::PointD* pos, double* pHeight, LDraw::matrix3d* pMat3)
{
	ASSERT(0);
#if 0
	*pHeight = m_fontHeight;

	if (cursorPos < m_glyphs.GetSize())
	{
		CGlyph* pGlyph = m_glyphs[cursorPos];

	//	CComPtr<ILSVGMatrix> ctm;
	//	m_pWindow->svgGetScreenCTM((ILSVGElement*)m_parent->m_pNode, &ctm);

		gmMatrix3 mat = m_pWindow->svgGetScreenCTM((PSVGElement*)m_parent);

//		gmMatrix3 mat = static_cast<CLSVGMatrix*>(ctm.p)->m_matrix;

		*pMat3 = gmMatrix3::translate(-pGlyph->m_position.X, -pGlyph->m_position.Y) *
					gmMatrix3::rotate(pGlyph->m_rotation) *
					gmMatrix3::translate(pGlyph->m_position.X, pGlyph->m_position.Y) *
					mat;

		pos->X = pGlyph->m_position.X;
		pos->Y = pGlyph->m_position.Y - m_fontHeight + pGlyph->m_descent;

		return TRUE;
	}
/*
	else if (cursorPos == m_glyphs.GetSize())
	{
		if (m_glyphs.GetSize() > 0)
		{
			CGlyph* pGlyph = m_glyphs[cursorPos-1];

			pos->X = pGlyph->m_position.X+pGlyph->m_charWidth;
			pos->Y = pGlyph->m_position.Y - m_fontHeight + pGlyph->m_descent;
		}
		else
		{
			ASSERT(0);
			pos->X = ((PSVGElement*)m_parent)->m_bounds.X;
			pos->Y = ((PSVGElement*)m_parent)->m_bounds.Y;
		}
	}
*/

	ASSERT(0);
#endif
	return false;
}


/*
//virtual
void CPSVGTextContentElement::CalculateDimensions(CHTMCalcContext* pC)
{
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CPNode* pNode = (CPNode*)m_childList.GetNext(pos);

		pNode->CalculateDimensions(pC);
	}
}
*/

//virtual
void PSVGTextContentElement::Render4(CHTMRenderContext* pC, LDraw::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
//	pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias/*pGraphics->GetSmoothingMode()*/);

//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 0, 0)), m_bounds);

	RenderTextChildren(pC, pBitmap, renderContext, scaleX, scaleY, bOffscreen);

	RenderChildren(pC, renderContext, scaleX, scaleY);
}

}	// Web
}	// System
