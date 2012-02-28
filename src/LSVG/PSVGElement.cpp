#include "stdafx.h"
#include "LSVG2.h"

#include "../../include/LXUI/ColorProfile.h"

#include "PSVGTextContentElement.h"
#include "PSVGMaskElement.h"
#include "PSVGClipPathElement.h"
#include "PSVGMarkerElement.h"

#include "PSVGFontElement.h"
#include "SVGFontElement.h"

#include "SVGClipPathElement.h"

/*
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
*/

namespace System
{

HTMLEXT uint8 linear_to_sRGB[256];
HTMLEXT uint8 sRGB_to_linear[256];

namespace Web
{

GlyphRun::GlyphRun() : m_dwriteFontFace(NULL)
{
//	m_pFontDef = NULL;
//	m_seglist = NULL;
	m_pGlyphRoot = NULL;
	m_charWidth = 0;
	m_rotation = 0;
}

GlyphRun::~GlyphRun()
{
	if (m_dwriteFontFace)
	{
		m_dwriteFontFace->Release();
	}

	/*
	if (m_seglist)
	{
	//	m_seglist->Release();
		m_seglist = NULL;
	}
	*/

	if (m_pGlyphRoot)
	{
	//	((ILViewNode*)m_pGlyphRoot)->Release();
		m_pGlyphRoot = NULL;
	}
}

void CGlyph::Render(CHTMRenderContext* pC, LDraw::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, PSVGFontElement* /*pSVGFont*/, double /*m_computedFontSize*/, LDraw::Brush* pFillBrush, LDraw::Pen* pStrokePen)
{
//	LDraw::Matrix oldtransform;
//	pGraphics->GetTransform(&oldtransform);

#if 0
	if (m_seglist)
	{
		/*
		LDraw::Matrix matrix;

		matrix.RotateAt(m_rotation, m_position);
		matrix.Translate(m_position.X, m_position.Y);
		matrix.Scale(m_scale, -m_scale);

		m_GraphicsPathF.Transform(&matrix);

		//pGraphics->MultiplyTransform(&matrix);
		*/

#if 0
		if (pFillBrush != NULL)
		{
			pGraphics->FillPath(pFillBrush, &m_GraphicsPathF);
		}

		if (pStrokePen != NULL)
		{
			pGraphics->DrawPath(pStrokePen, &m_GraphicsPathF);
		}
#endif
		/*
		matrix.Invert();

		m_GraphicsPathF.Transform(&matrix);
		*/

//		pGraphics->SetTransform(&oldtransform);
	}

	if (m_pGlyphRoot)
	{
		double scale = m_scale;//m_computedFontSize / pSVGFont->GetUnitsPerEm();

		LDraw::matrix3d matrix;

		ASSERT(0);
#if 0

		matrix.RotateAt(m_rotation, m_position);
		//matrix.Translate(-pGlyph->m_pGlyphRoot->m_bounds.X, -pGlyph->m_pGlyphRoot->m_bounds.Y);
		matrix.Translate(m_position.X, m_position.Y);

		matrix.Scale(scale, -scale);
		//matrix.Translate(-pGlyph->m_pGlyphRoot->m_bounds.X, -pGlyph->m_pGlyphRoot->m_bounds.Y);

		gmMatrix3 oldmat =  pGraphics->m_transform;

		pGraphics->MultiplyTransform(&matrix);

		m_pGlyphRoot->Render4(pC, pBitmap, pGraphics, scaleX, scaleY, FALSE, FALSE/*bDrawBehaviors*/);

		//pGraphics->TranslateTransform(pGlyph->m_pGlyphRoot->m_bounds.X, -pGlyph->m_pGlyphRoot->m_bounds.Y);

		pGraphics->SetTransform(oldmat);
#endif
	}
#endif
}

////////////////////////////////////////////////////////////////////
// PSVGElement

PSVGElement::PSVGElement(SVGElement* element) : PElementBase(element)
{
// Rendering stuff (uninitialized)
	m_backgroundBitmap = NULL;

	m_pCachedBitmap = NULL;
//	m_pStrokeBrush = NULL;
//	m_pFillBrush = NULL;

	m_expandedBBox.X = 0xacacacac;	// garbage
	m_expandedBBox.Y = 0xacacacac;
	m_expandedBBox.Width = 0xacacacac;
	m_expandedBBox.Height = 0xacacacac;
	m_filterRect.X = 0xacacacac;	// garbage
	m_filterRect.Y = 0xacacacac;
	m_filterRect.Width = 0xacacacac;
	m_filterRect.Height = 0xacacacac;

	m_scaleX = 1;
	m_scaleY = 1;
	//m_scaleX = 0;
	//m_scaleY = 0;
//

	m_pFilterElement = NULL;
	m_pMaskElement = NULL;
	m_pClipPathElement = NULL;
	m_pStrokeElement = NULL;
	m_pFillElement = NULL;
	m_pMarkerStartElement = NULL;
	m_pMarkerEndElement = NULL;
	m_pMarkerMidElement = NULL;

	m_animateMotionMatrix = LDraw::Matrix3d::GetIdentity();
}

PSVGElement::~PSVGElement()
{
	RemoveGlyphs();
	FreeCachedBitmap();

	ASSERT(0);
#if 0
	UPOSITION pos = m_referencingElements.GetHeadPosition();
	while (pos)
	{
		CPElement* pElement = (CPElement*)m_referencingElements.GetNext(pos);

		pElement->ReferenceInvalid(this);
	}
#endif
}

void PSVGElement::FreeCachedBitmap()
{
	if (m_pCachedBitmap)
	{
	//	delete m_pCachedBitmap;
		m_pCachedBitmap = NULL;
	}

	m_pStrokeBrush = NULL;
	m_pFillBrush = NULL;

	/*
	if (m_pStrokeBrush)
	{
		m_pStrokeBrush->Release();
		m_pStrokeBrush = NULL;
	}

	if (m_pFillBrush)
	{
		m_pFillBrush->Release();
		m_pFillBrush = NULL;
	}
	*/
}

double PSVGElement::LengthToUserUnits(ISVGLength* length, double percentageOf)
{
	if (length->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
	{
		return (length->get_valueInSpecifiedUnits() * percentageOf)/100;
	}
	else if (length->get_unitType() == SVG_LENGTHTYPE_EMS)
	{
		return length->get_valueInSpecifiedUnits()*m_computedFontSize;
	}
	else if (length->get_unitType() == SVG_LENGTHTYPE_EXS)
	{
		// TODO, improve this
		return length->get_valueInSpecifiedUnits()*m_computedFontSize/2;
	}
	else
	{
		return length->get_value();
	}
}

//virtual
void PSVGElement::ReferenceInvalid(PElementBase/*PSVGElement*/ * pPElement)
{
	if (pPElement == m_pStrokeElement)
	{
		m_pStrokeElement = NULL;
	}
	else if (pPElement == m_pFillElement)
	{
		m_pFillElement = NULL;
	}
	else if (pPElement == m_pMarkerStartElement)
	{
		m_pMarkerStartElement = NULL;
	}
	else if (pPElement == m_pMarkerEndElement)
	{
		m_pMarkerEndElement = NULL;
	}
	else if (pPElement == m_pMarkerMidElement)
	{
		m_pMarkerMidElement = NULL;
	}
	else if (pPElement == m_pFilterElement)
	{
		m_pFilterElement = NULL;
	// TODO
	}
	else if (pPElement == m_pMaskElement)
	{
		m_pMaskElement = NULL;
	}
	else if (pPElement == m_pClipPathElement)
	{
		m_pClipPathElement = NULL;
	}
	else
	{
		PElementBase::ReferenceInvalid(pPElement);
	}
}

//virtual
void PSVGElement::BuildChildren()
{
	ASSERT(0);
#if 0
// Build children
	CComQIPtr<ILDOMNode> child;
	m_pNode->get_firstChild(&child);

	while (child != NULL)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);

		if (nodeType == LNODE_TEXT)
		{
			CComQIPtr<ILDOMText> text = child;

			CComObject<CPSVGText>* pItem;
			CComObject<CPSVGText>::CreateInstance(&pItem);
			pItem->AddRef();
			pItem->m_pNode = text;
			pItem->m_pView = m_pView;
			pItem->m_pWindow = m_pWindow;

			CComQIPtr<CLDOMNodeImplImpl>(child)->m_pNodes.Add(pItem);

			pItem->m_parent = this;
			m_childList.AddTail(pItem);
		}
		else if (nodeType == LNODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement> element = child;

			CPElement* pElement2 = m_pView->CreateElement(element);
			if (pElement2)
			{
				CComQIPtr<CLDOMNodeImplImpl>(element)->m_pNodes.Add(pElement2);

				pElement2->BuildChildren();

				pElement2->m_parent = this;
				m_childList.AddTail(pElement2);
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
#endif
}

void PSVGElement::CalculateBounds()
{
}

void PSVGElement::CalculateBoundsAndChildren()
{
//	ISVGTransformable* transformable = dynamic_cast<ISVGTransformable*>(m_pNode);
//	LDraw::Matrix3d* matrix = transformable->get_transform()->get_animVal()->psvgElement->m_transform->m_animated->m_animVal->m_value->consolidateToMatrix();
//	LDraw::Matrix3d* matrix = psvgElement->m_transform->m_animated->m_animVal->m_value->consolidateToMatrix();

	if (!m_boundsValid)	// TODO, and if nearest viewport box has changed
	{
		LDraw::matrix3d transform = LDraw::matrix3d::getIdentity();

		FreeCachedBitmap();

		m_boundsValid = true;
		CalculateBounds();

		GetFillUriElement();
		GetStrokeUriElement();
		GetFilterElement();
		GetMaskElement();
		GetClipPathElement();

		if (m_pFilterElement)
		{
			m_filterRect = m_pFilterElement->CalculateFilterRegion(this);
		}
		else
		{
			m_filterRect = m_expandedBBox;
		}

		CalculateScaleXY(transform, &m_scaleX, &m_scaleY);
	}
}

// virtual
void PSVGElement::BuildRenderableChildren()
{
	m_childListRender.clear();

	ISVGFitToViewBox* viewport = dynamic_cast<ISVGFitToViewBox*>(m_pNode);

// Build list of renderable children
	PNode** pos = m_rchildList.begin();
	while (pos != m_rchildList.end())
	{
		PNode* pNode = *pos;
		++pos;

		PSVGElement* pElement = dynamic_cast<PSVGElement*>(pNode);

		if (pElement)
		{
			if (viewport)
				pElement->m_nearestViewportElement = this;
			else
				pElement->m_nearestViewportElement = m_nearestViewportElement;

			CSVGRenderElement* render = dynamic_cast<CSVGRenderElement*>(pElement->m_pNode);
			if (render)
			{
				m_childListRender.Add(pElement);
			}
		}
	}
}

void PSVGElement::SetViewportElement(PSVGElement* nearestViewportElement)
{
	/*
	if (m_nearestViewportElement != nearestViewportElement)
	{
	}
	*/
	m_nearestViewportElement = nearestViewportElement;

	SetViewportElementChildren(nearestViewportElement);
}

void PSVGSVGElement::SetViewportElement(PSVGElement* nearestViewportElement)
{
	m_nearestViewportElement = nearestViewportElement;

	SetViewportElementChildren(this);
}

void PSVGElement::SetViewportElementChildren(PSVGElement* nearestViewportElement)
{
	PSVGElement** pos = m_childListRender.begin();
	while (pos != m_childListRender.end())
	{
		PSVGElement* pElement = *pos;
		++pos;

		pElement->SetViewportElement(nearestViewportElement);
	}
}

PSVGElement* PSVGElement::GetViewportElement()
{
	return m_nearestViewportElement;
}

//////////////////////////////////
// Rendering

LDraw::Pen* PSVGElement::GetPen(LDraw::Brush* pBrush)
{
	if (m_computedStrokeWidth > 0)
	{
		LDraw::Pen* pPen = new LDraw::Pen(pBrush, (float)m_computedStrokeWidth);
		//if (pPen)
		{
#if 0
			LDraw::LineCap lineCap;

			if (m_computedStrokeLineCap == StrokeLineCap_butt)
				lineCap = LDraw::LineCapFlat;
			else if (m_computedStrokeLineCap == StrokeLineCap_round)
				lineCap = LDraw::LineCapRound;
			else if (m_computedStrokeLineCap == StrokeLineCap_square)
				lineCap = LDraw::LineCapSquare;
			else
				ASSERT(0);

			LDraw::DashCap dashCap;

			if (m_computedStrokeLineCap == StrokeLineCap_butt)
				dashCap = LDraw::DashCapFlat;
			else if (m_computedStrokeLineCap == StrokeLineCap_round)
				dashCap = LDraw::DashCapRound;
			else if (m_computedStrokeLineCap == StrokeLineCap_square)
				dashCap = LDraw::DashCapFlat;
			else
				ASSERT(0);

			pPen->SetLineCap(lineCap/*start*/, lineCap/*end*/, dashCap);

			pPen->SetLineJoin((m_computedStrokeLineJoin == 0)? LDraw::LineJoinMiterClipped: (m_computedStrokeLineJoin == 1)? LDraw::LineJoinRound: LDraw::LineJoinBevel);

			if (m_computedStrokeLineJoin == 0)
				pPen->SetMiterLimit(m_computedStrokeMiterLimit);
			//else
				//pPen->SetMiterLimit(0);

			if (m_strokeDashValuesArray.GetSize() > 0)
			{
				pPen->SetDashOffset(m_computedStrokeDashOffset/m_computedStrokeWidth);

				int nvalues = m_strokeDashValuesArray.GetSize();

				int tvalues;
				if (nvalues & 1)
					tvalues = nvalues*2;
				else
					tvalues = nvalues;

				double* dvalues = new double[tvalues];
				for (int i = 0; i < nvalues; i++)
				{
					dvalues[i] = m_strokeDashValuesArray[i];
					if (nvalues & 1) dvalues[nvalues+i] = dvalues[i];
				}

				float* fvalues = new float[tvalues];

				if (m_computedStrokeLineCap == StrokeLineCap_butt)
				{
					for (int i = 0; i < tvalues; i++)
					{
						fvalues[i] = (float)(dvalues[i]/m_computedStrokeWidth);
					}
				}
				else if (m_computedStrokeLineCap == StrokeLineCap_round)
				{
					for (int i = 0; i < tvalues; i += 2)
					{
						fvalues[i+0] =	(float)((dvalues[i+0]+m_computedStrokeWidth*1)/m_computedStrokeWidth);
						fvalues[i+1] = (float)((dvalues[i+1]-m_computedStrokeWidth)/m_computedStrokeWidth);
					}
				}
				else if (m_computedStrokeLineCap == StrokeLineCap_square)
				{
					pPen->SetDashOffset(pPen->GetDashOffset()+0.5);

					for (int i = 0; i < tvalues; i += 2)
					{
						fvalues[i+0] =	(float)((dvalues[i+0]+m_computedStrokeWidth)/m_computedStrokeWidth);
						fvalues[i+1] = (float)((dvalues[i+1]-m_computedStrokeWidth)/m_computedStrokeWidth);
					}
				}

				pPen->SetDashPattern(fvalues, tvalues);

				delete fvalues;
				delete dvalues;
			}
#endif
			return pPen;
		}
	}
	return NULL;
}

LDraw::Brush* PSVGElement::GetStrokeBrush(double opacity, double scaleX, double scaleY)
{
	if (m_pStrokeBrush == NULL)
	{
		m_pStrokeBrush = GetBrush(&m_computedStroke, m_pStrokeElement, opacity, scaleX, scaleY);
	}

	return m_pStrokeBrush;
}

LDraw::Brush* PSVGElement::GetFillBrush(double opacity, double scaleX, double scaleY)
{
	if (m_pFillBrush == NULL)
	{
		m_pFillBrush = GetBrush(&m_computedFill, m_pFillElement, opacity, scaleX, scaleY);
	}

	//m_pFillBrush.AddRef();
	return m_pFillBrush;
}

Gui::Brush* PSVGElement::GetBrush(Gui::RenderTarget* rt, CSVGPaint* pPaint, PSVGElement* pUriElement, double opacity, double scaleX, double scaleY)
{
	Gui::Brush* pBrush = NULL;

	if (	pPaint->m_type == SVG_PAINTTYPE_URI ||
			pPaint->m_type == SVG_PAINTTYPE_URI_NONE ||
			pPaint->m_type == SVG_PAINTTYPE_URI_CURRENTCOLOR ||
			pPaint->m_type == SVG_PAINTTYPE_URI_RGBCOLOR ||
			pPaint->m_type == SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR)
	{
#if 0
		if (pUriElement)
		{
			pBrush = pUriElement->CreateBrush(this, scaleX, scaleY);
		}
		else
		{
			if (pPaint->m_type == SVG_PAINTTYPE_URI_CURRENTCOLOR)
			{
				// color property
				LDraw::Color color(opacity*255, m_computedColor.GetRed(), m_computedColor.GetGreen(), m_computedColor.GetBlue());
				pBrush = new LDraw::SolidBrush(color);
			}
			else if (pPaint->m_type == SVG_PAINTTYPE_URI_RGBCOLOR ||
						pPaint->m_type == SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR)
			{
				pBrush = new LDraw::SolidBrush(LDraw::Color(opacity*255, pPaint->m_rgbColor[0], pPaint->m_rgbColor[1], pPaint->m_rgbColor[2]));
			}
			else
			{
				pBrush = NULL;
			}
		}
#endif
	}
	else if (pPaint->m_type == SVG_PAINTTYPE_RGBCOLOR)
	{
		/*
		ID2D1SolidColorBrush* p;
		rt->GetRT()->m_spRT->CreateSolidColorBrush(D2D1::ColorF(pPaint->m_rgbColor[0]/255.0f, pPaint->m_rgbColor[1]/255.0f, pPaint->m_rgbColor[2]/255.0f, opacity), &p);
		*/

		Gui::SolidColorBrush* p = new Gui::SolidColorBrush(pPaint->m_rgbColor[0]/255.0f, pPaint->m_rgbColor[1]/255.0f, pPaint->m_rgbColor[2]/255.0f, opacity);
		pBrush = p;
	}
	else if (pPaint->m_type == SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR)
	{
#if 0
		pBrush = NULL;

		CColorProfile* pProfile = NULL;
		if (pPaint->m_iccColorProfile->Length())
		{
			ASSERT(0);
#if 0
			pProfile = m_pWindow->GetColorProfileByName(pPaint->m_iccColorProfile);
#endif
		}

		if (pProfile)
		{
			ASSERT(0);
#if 0

			/*
			{
				PROFILE profile;
				profile.dwType = PROFILE_FILENAME;
				profile.pProfileData = pProfile->m_lcs.lcsFilename;
				profile.cbDataSize = (_tcslen(pProfile->m_lcs.lcsFilename)+1)*sizeof(TCHAR);

				HPROFILE hProfile = ::OpenColorProfile(&profile, PROFILE_READ, FILE_SHARE_READ, OPEN_EXISTING);

				PROFILEHEADER ph;
				GetColorProfileHeader(hProfile, &ph);
			}
			*/

			int nChannels = pPaint->m_iccColors.GetSize();
			ASSERT(nChannels <= 8);

			if (nChannels <= 8)
			{
				COLORTYPE inColorType = (COLORTYPE)0;
				COLOR inColor;

				switch (nChannels)
				{
				case 1: inColorType = COLOR_GRAY; break;
			//	case 2: inColorType = COLOR_2_CHANNEL; break;
				case 3: inColorType = COLOR_RGB; break;
				case 4: inColorType = COLOR_CMYK; break;
				case 5: inColorType = COLOR_5_CHANNEL; break;
				case 6: inColorType = COLOR_6_CHANNEL; break;
				case 7: inColorType = COLOR_7_CHANNEL; break;
				case 8: inColorType = COLOR_8_CHANNEL; break;
				}

				if (nChannels < 5)
				{
				// WORD
					for (int i = 0; i < nChannels; i++)
					{
						((WORD*)&inColor)[i] = pPaint->m_iccColors[i]*65535;
					}
				}
				else
				{
				// BYTE
					for (int i = 0; i < nChannels; i++)
					{
						((BYTE*)&inColor)[i] = pPaint->m_iccColors[i]*255;
					}
				}

				/*
				LOGCOLORSPACE& lcs = pProfile->m_lcs;
				lcs.lcsSignature = LCS_SIGNATURE;
				lcs.lcsVersion = 0x400;
				lcs.lcsSize = sizeof(lcs);
				lcs.lcsCSType = LCS_CALIBRATED_RGB;
// Set endpoints to sRGB values.
				lcs.lcsEndpoints.ciexyzRed.ciexyzX = __FXPT2DOT30(1);//(.64);
				lcs.lcsEndpoints.ciexyzRed.ciexyzY = __FXPT2DOT30(0);//(.33);
				lcs.lcsEndpoints.ciexyzRed.ciexyzZ = __FXPT2DOT30(0);//(.03);
				lcs.lcsEndpoints.ciexyzGreen.ciexyzX = __FXPT2DOT30(0);//(.3);
				lcs.lcsEndpoints.ciexyzGreen.ciexyzY = __FXPT2DOT30(1);//(.6);
				lcs.lcsEndpoints.ciexyzGreen.ciexyzZ = __FXPT2DOT30(0);//(.1);
				lcs.lcsEndpoints.ciexyzBlue.ciexyzX   =   __FXPT2DOT30(0);//(  .15);
				lcs.lcsEndpoints.ciexyzBlue.ciexyzY = __FXPT2DOT30(0);//(.06);
				lcs.lcsEndpoints.ciexyzBlue.ciexyzZ = __FXPT2DOT30(1);//(.79);
				lcs.lcsGammaRed = __FXPT16DOT16(1);//(0.45);
				lcs.lcsGammaGreen = __FXPT16DOT16(1);//(0.45);
				lcs.lcsGammaBlue = __FXPT16DOT16(1);//(0.45);

				lcs.lcsIntent = LCS_GM_IMAGES;//LCS_GM_GRAPHICS;

				HPROFILE sRGBProfile = Get_sRGBProfile();
				*/

				HTRANSFORM hTransform = pProfile->GetProfile2sRGB();
				if (hTransform)
				{
					COLOR outColor;
					BOOL bSuccess = ::TranslateColors(hTransform, &inColor, 1, inColorType, &outColor, COLOR_RGB);

					if (bSuccess)
					{
						pBrush = LDraw::SolidBrush(LDraw::Color(opacity*255,
							outColor.rgb.red>>8, outColor.rgb.green>>8, outColor.rgb.blue>>8));
					}
				}
			}
#endif
		}

		if (pBrush == NULL)	// fall back to rgbColor
		{
			pBrush = new LDraw::SolidBrush(LDraw::Color(opacity*255, pPaint->m_rgbColor[0], pPaint->m_rgbColor[1], pPaint->m_rgbColor[2]));
		}
#endif
	}
	else if (pPaint->m_type == SVG_PAINTTYPE_CURRENTCOLOR)
	{
		Gui::SolidColorBrush* p = new Gui::SolidColorBrush(m_computedColor.GetRed()/255.0f, m_computedColor.GetGreen()/255.0f, m_computedColor.GetBlue()/255.0f, m_computedColor.GetAlpha()/255.0f*opacity);
		pBrush = p;

#if 0
		LDraw::Color color(opacity*255, m_computedColor.GetRed(), m_computedColor.GetGreen(), m_computedColor.GetBlue());
//		pBrush = new LDraw::SolidBrush(color);
		ID2D1SolidColorBrush* p;
		rt->GetRT()->m_spRT->CreateSolidColorBrush(D2D1::ColorF(m_computedColor.GetRed()/255.0f, m_computedColor.GetGreen()/255.0f, m_computedColor.GetBlue()/255.0f, opacity), &p);
		pBrush = p;
#endif
	}
	else // SVG_PAINTTYPE_NONE
	{
		pBrush = NULL;
	}

	return pBrush;
}

LDraw::Brush* PSVGElement::GetBrush(CSVGPaint* pPaint, PSVGElement* pUriElement, double opacity, double scaleX, double scaleY)
{
	LDraw::Brush* pBrush = NULL;

	if (	pPaint->m_type == SVG_PAINTTYPE_URI ||
			pPaint->m_type == SVG_PAINTTYPE_URI_NONE ||
			pPaint->m_type == SVG_PAINTTYPE_URI_CURRENTCOLOR ||
			pPaint->m_type == SVG_PAINTTYPE_URI_RGBCOLOR ||
			pPaint->m_type == SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR)
	{
		if (pUriElement)
		{
			pBrush = pUriElement->CreateBrush(this, scaleX, scaleY);
		}
		else
		{
			if (pPaint->m_type == SVG_PAINTTYPE_URI_CURRENTCOLOR)
			{
				// color property
				LDraw::Color color(opacity*255, m_computedColor.GetRed(), m_computedColor.GetGreen(), m_computedColor.GetBlue());
				pBrush = new LDraw::SolidBrush(color);
			}
			else if (pPaint->m_type == SVG_PAINTTYPE_URI_RGBCOLOR ||
						pPaint->m_type == SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR)
			{
				pBrush = new LDraw::SolidBrush(LDraw::Color(opacity*255, pPaint->m_rgbColor[0], pPaint->m_rgbColor[1], pPaint->m_rgbColor[2]));
			}
			else
			{
				pBrush = NULL;
			}
		}
	}
	else if (pPaint->m_type == SVG_PAINTTYPE_RGBCOLOR)
	{
		pBrush = new LDraw::SolidBrush(LDraw::Color(opacity*255, pPaint->m_rgbColor[0], pPaint->m_rgbColor[1], pPaint->m_rgbColor[2]));
	}
	else if (pPaint->m_type == SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR)
	{
		pBrush = NULL;

		CColorProfile* pProfile = NULL;
		if (pPaint->m_iccColorProfile.GetLength())
		{
			ASSERT(0);
#if 0
			pProfile = m_pWindow->GetColorProfileByName(pPaint->m_iccColorProfile);
#endif
		}

		if (pProfile)
		{
			ASSERT(0);
#if 0

			/*
			{
				PROFILE profile;
				profile.dwType = PROFILE_FILENAME;
				profile.pProfileData = pProfile->m_lcs.lcsFilename;
				profile.cbDataSize = (_tcslen(pProfile->m_lcs.lcsFilename)+1)*sizeof(TCHAR);

				HPROFILE hProfile = ::OpenColorProfile(&profile, PROFILE_READ, FILE_SHARE_READ, OPEN_EXISTING);

				PROFILEHEADER ph;
				GetColorProfileHeader(hProfile, &ph);
			}
			*/

			int nChannels = pPaint->m_iccColors.GetSize();
			ASSERT(nChannels <= 8);

			if (nChannels <= 8)
			{
				COLORTYPE inColorType = (COLORTYPE)0;
				COLOR inColor;

				switch (nChannels)
				{
				case 1: inColorType = COLOR_GRAY; break;
			//	case 2: inColorType = COLOR_2_CHANNEL; break;
				case 3: inColorType = COLOR_RGB; break;
				case 4: inColorType = COLOR_CMYK; break;
				case 5: inColorType = COLOR_5_CHANNEL; break;
				case 6: inColorType = COLOR_6_CHANNEL; break;
				case 7: inColorType = COLOR_7_CHANNEL; break;
				case 8: inColorType = COLOR_8_CHANNEL; break;
				}

				if (nChannels < 5)
				{
				// WORD
					for (int i = 0; i < nChannels; i++)
					{
						((WORD*)&inColor)[i] = pPaint->m_iccColors[i]*65535;
					}
				}
				else
				{
				// BYTE
					for (int i = 0; i < nChannels; i++)
					{
						((BYTE*)&inColor)[i] = pPaint->m_iccColors[i]*255;
					}
				}

				/*
				LOGCOLORSPACE& lcs = pProfile->m_lcs;
				lcs.lcsSignature = LCS_SIGNATURE;
				lcs.lcsVersion = 0x400;
				lcs.lcsSize = sizeof(lcs);
				lcs.lcsCSType = LCS_CALIBRATED_RGB;
// Set endpoints to sRGB values.
				lcs.lcsEndpoints.ciexyzRed.ciexyzX = __FXPT2DOT30(1);//(.64);
				lcs.lcsEndpoints.ciexyzRed.ciexyzY = __FXPT2DOT30(0);//(.33);
				lcs.lcsEndpoints.ciexyzRed.ciexyzZ = __FXPT2DOT30(0);//(.03);
				lcs.lcsEndpoints.ciexyzGreen.ciexyzX = __FXPT2DOT30(0);//(.3);
				lcs.lcsEndpoints.ciexyzGreen.ciexyzY = __FXPT2DOT30(1);//(.6);
				lcs.lcsEndpoints.ciexyzGreen.ciexyzZ = __FXPT2DOT30(0);//(.1);
				lcs.lcsEndpoints.ciexyzBlue.ciexyzX   =   __FXPT2DOT30(0);//(  .15);
				lcs.lcsEndpoints.ciexyzBlue.ciexyzY = __FXPT2DOT30(0);//(.06);
				lcs.lcsEndpoints.ciexyzBlue.ciexyzZ = __FXPT2DOT30(1);//(.79);
				lcs.lcsGammaRed = __FXPT16DOT16(1);//(0.45);
				lcs.lcsGammaGreen = __FXPT16DOT16(1);//(0.45);
				lcs.lcsGammaBlue = __FXPT16DOT16(1);//(0.45);

				lcs.lcsIntent = LCS_GM_IMAGES;//LCS_GM_GRAPHICS;

				HPROFILE sRGBProfile = Get_sRGBProfile();
				*/

				HTRANSFORM hTransform = pProfile->GetProfile2sRGB();
				if (hTransform)
				{
					COLOR outColor;
					BOOL bSuccess = ::TranslateColors(hTransform, &inColor, 1, inColorType, &outColor, COLOR_RGB);

					if (bSuccess)
					{
						pBrush = LDraw::SolidBrush(LDraw::Color(opacity*255,
							outColor.rgb.red>>8, outColor.rgb.green>>8, outColor.rgb.blue>>8));
					}
				}
			}
#endif
		}

		if (pBrush == NULL)	// fall back to rgbColor
		{
			pBrush = new LDraw::SolidBrush(LDraw::Color(opacity*255, pPaint->m_rgbColor[0], pPaint->m_rgbColor[1], pPaint->m_rgbColor[2]));
		}
	}
	else if (pPaint->m_type == SVG_PAINTTYPE_CURRENTCOLOR)
	{
		LDraw::Color color(opacity*255, m_computedColor.GetRed(), m_computedColor.GetGreen(), m_computedColor.GetBlue());
		pBrush = new LDraw::SolidBrush(color);
	}
	else // SVG_PAINTTYPE_NONE
	{
		pBrush = NULL;
	}

	return pBrush;
}

void PSVGElement::GetScreenBBoxFromPath(SVGPathSegList* seglist, LDraw::RectD* bbox)
{
//	CComPtr<ILSVGMatrix> matrix;
//	CComQIPtr<ILSVGTransformable> transformable = m_pNode;
//	transformable->getScreenCTM(&matrix);
//	m_pWindow->svgGetScreenCTM((ILSVGElement*)m_pNode, &matrix);

	ASSERT(0);
#if 0
	gmMatrix3 matrix = m_pWindow->svgGetScreenCTM(this);	// TODO?: Should be GetScreenCTM2() ?

	GetPathSegListBBox(seglist, matrix, bbox);
#endif
}

void PSVGElement::GetScreenBBoxFromBounds(const LDraw::RectD& bounds, LDraw::RectD* bbox)
{
	SVGMatrix* matrix;
//	CComQIPtr<ILSVGTransformable> transformable = m_pNode;
//	transformable->getScreenCTM(&matrix);
	ASSERT(0);
#if 0
	m_pWindow->svgGetScreenCTM((ILSVGElement*)m_pNode, &matrix);
#endif

	LDraw::GetTransformRectBoundingBox(matrix->GetM(), bounds, bbox);
}

void PSVGElement::CalculateScale(LDraw::Matrix3d* matrix)
{
	CalculateScaleXY(matrix, &m_scaleX, &m_scaleY);
}

LDraw::RectD PSVGElement::CalculateRenderableChildrenBoundingBox()
{
	double minx = 999999999;
	double miny = 999999999;
	double maxx = -999999999;
	double maxy = -999999999;

	PSVGElement** pos = m_childListRender.begin();
	while (pos != m_childListRender.end())
	{
		PSVGElement* pElement = *pos;
		++pos;

		pElement->CalculateBoundsAndChildren();

		LDraw::RectD xbounds = pElement->m_xbounds;
		if (xbounds.Width >= 0 && xbounds.Height >= 0)
		{
			if (xbounds.X < minx) minx = xbounds.X;
			if (xbounds.Y < miny) miny = xbounds.Y;
			if (xbounds.X+xbounds.Width > maxx) maxx = xbounds.X+xbounds.Width;
			if (xbounds.Y+xbounds.Height > maxy) maxy = xbounds.Y+xbounds.Height;
		}
	}
#if 0

	UPOSITION pos = m_childListRender.GetHeadPosition();
	while (pos)
	{
		PSVGElement* pElement = (PSVGElement*)m_childListRender.GetNext(pos);

		LDraw::RectD xbounds = pElement->m_xbounds;
		if (xbounds.Width >= 0 && xbounds.Height >= 0)
		{
			if (xbounds.X < minx) minx = xbounds.X;
			if (xbounds.Y < miny) miny = xbounds.Y;
			if (xbounds.X+xbounds.Width > maxx) maxx = xbounds.X+xbounds.Width;
			if (xbounds.Y+xbounds.Height > maxy) maxy = xbounds.Y+xbounds.Height;
		}
	}
#endif

	return LDraw::RectD(minx, miny, maxx-minx, maxy-miny);
}

LDraw::RectD PSVGElement::CalculateRenderableChildrenFilterRect()
{
	double minx = 999999999;
	double miny = 999999999;
	double maxx = -999999999;
	double maxy = -999999999;

	TRACE("TODO: CalculateRenderableChildrenFilterRect\n");
#if 0

	UPOSITION pos = m_childListRender.GetHeadPosition();
	while (pos)
	{
		PSVGElement* pElement = (PSVGElement*)m_childListRender.GetNext(pos);

		RectD objectExpandedRect = pElement->m_expandedBBox;
		gmMatrix3 elementMatrix = pElement->GetLocalAnimatedMatrix();

		RectD objectExpandedRectX;
		LDraw::GetTransformRectBoundingBox(elementMatrix, objectExpandedRect, &objectExpandedRectX);

		if (objectExpandedRect.Width >= 0 && objectExpandedRect.Height >= 0)
		{
			minx = min(objectExpandedRectX.X, minx);
			miny = min(objectExpandedRectX.Y, miny);
			maxx = max(objectExpandedRectX.X+objectExpandedRectX.Width, maxx);
			maxy = max(objectExpandedRectX.Y+objectExpandedRectX.Height, maxy);
		}
	}
#endif
	return LDraw::RectD(minx, miny, maxx-minx, maxy-miny);
}

void PSVGElement::RenderChildren(CHTMRenderContext* pC, Gui::RenderContext* renderContext, double scaleX, double scaleY)
{
	PSVGElement** pos = m_childListRender.begin();
	while (pos != m_childListRender.end())
	{
		PSVGElement* pElement = *pos++;

		// TODO
	//	if (pElement->m_computedDisplayRole != DisplayRole_none)
		{
			if (pElement->m_computedVisibility == Visibility_visible)
			{
				pElement->Render(pC, renderContext, scaleX, scaleY);
			}
		}
	}
}

/*
For text elements, hit detection is performed on a character cell basis:
*/
bool PSVGElement::HitTestCharacters(LDraw::PointD pt, int pointerEvents, PNode** ppNode, long* poffset)
{
	bool bProcess = false;

	switch (pointerEvents)
	{
	case PointerEvents_visiblePainted:
		{
			if (m_computedVisibility == Visibility_visible &&

				(m_computedStroke.m_type != SVG_PAINTTYPE_NONE ||
				m_computedFill.m_type != SVG_PAINTTYPE_NONE))
			{
				bProcess = true;
			}
		}
		break;

	case PointerEvents_visibleFill:
	case PointerEvents_visibleStroke:
	case PointerEvents_visible:
		{
			if (m_computedVisibility == Visibility_visible)
			{
				bProcess = true;
			}
		}
		break;

	case PointerEvents_painted:
		{
			if (m_computedStroke.m_type != SVG_PAINTTYPE_NONE ||
				m_computedFill.m_type != SVG_PAINTTYPE_NONE)
			{
				bProcess = true;
			}
		}
		break;

	case PointerEvents_fill:
	case PointerEvents_stroke:
	case PointerEvents_all:
		{
			bProcess = true;
		}
		break;
	}

	if (bProcess)
	{
		ASSERT(0);
#if 0
		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CPNode* pNode = (CPNode*)m_childList.GetNext(pos);
			if (pNode->m_type == LNODE_ELEMENT)
			{
				ASSERT(0);
#if 0
				CComQIPtr<ILSVGElement> textContent = pNode->m_pNode;
				if (textContent)
				{
					PSVGElement* pSVGTextContent = (PSVGElement*)pNode;

					BOOL b = pSVGTextContent->HitTestCharacters(pt, pointerEvents, ppNode, poffset);
					if (b)
						return b;
				}
#endif
			}
			else
			{
				CPSVGText* pTextNode = (CPSVGText*)pNode;

				for (int i = 0; i < pTextNode->m_glyphs.GetSize(); i++)
				{
					CGlyph* pGlyph = pTextNode->m_glyphs[i];

					/*
					RectD charCell(
						pGlyph->m_position.X,
						pGlyph->m_position.Y-pTextNode->m_fontHeight + pGlyph->m_descent, // y
						pGlyph->m_charWidth,
						pTextNode->m_fontHeight);
					*/

					LDraw::RectD charCell(
						0,
						-pTextNode->m_fontHeight + pGlyph->m_descent,
						pGlyph->m_charWidth,
						pTextNode->m_fontHeight);

					gmMatrix3 mat = gmMatrix3::rotate(pGlyph->m_rotation) *
						gmMatrix3::translate(pGlyph->m_position.X, pGlyph->m_position.Y);

					PointD pt2 = mat.inverse().transform(pt);

					if (charCell.Contains(pt2.X, pt2.Y))
					{
						*ppNode = pTextNode;
						*poffset = i;
						return TRUE;
					}
				}
			}
		}
#endif
	}

	return false;
}

bool PSVGElement::GetTextUnderPoint(LDraw::matrix3d matrix, LDraw::PointD pt, PNode** ppNode, long* poffset, double& distance)
{
	ASSERT(0);
#if 0
	PointD xpt = matrix.inverse().transform(pt);


#if 0
	gmMatrix3 matrix = GetScreenCTM/*2*/();

	pt2 = matrix.inverse().transform(pt);
#endif

	if (m_glyphs.GetSize())
	{
		// TODO
	}
	else
	{
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

					BOOL b = pSVGTextContent->GetTextUnderPoint(matrix * pSVGTextContent->GetLocalAnimatedMatrix(), pt, ppNode, poffset, distance);
				}
			}
			else
			{
				CPSVGText* pTextNode = (CPSVGText*)pNode;

				for (int i = 0; i < pTextNode->m_glyphs.GetSize(); i++)
				{
					CGlyph* pGlyph = pTextNode->m_glyphs[i];

					// TODO gmMatrix3::rotate(pGlyph->m_rotation);

					PointD center;
					center.X = pGlyph->m_position.X;// + pGlyph->m_charWidth/2;
					center.Y = pGlyph->m_position.Y;// - (pTextNode->m_fontHeight - pGlyph->m_descent)/2;

					double d = distanceSquared(center, xpt);

					if (d < distance)
					{
						distance = d;

						*ppNode = pTextNode;
						*poffset = i;
					}
				}
			}
		}
	}
#endif
	return true;
}

/*
BOOL PSVGElement::GetTextUnderPoint2(PointD pt, CPNode** ppNode, long* poffset, double& distance)
{
}
*/

//virtual
void PSVGElement::RenderSelection(CHTMRenderContext* pC)
{
	ASSERT(0);
#if 0
	/*LDraw::Matrix3f oldmat =*/ pC->m_pGraphics->PushTransform();

	LDraw::Matrix3d* matrix = GetLocalAnimatedMatrix();
	//if (pMatrix)
	{
		/*
		LDraw::Matrix matrix(
			(float)matrix[0][0], (float)matrix[0][1],
			(float)matrix[1][0], (float)matrix[1][1],
			(float)matrix[2][0], (float)matrix[2][1]);
		*/
		ASSERT(0);
#if 0
		pC->m_pGraphics->MultiplyTransform(matrix);
#endif

	//	pMatrix->Release();
	}

	RenderSelection2(pC);

	pC->m_pGraphics->PopTransform();//oldmat);
#endif
}

void PSVGElement::RenderSelection2(CHTMRenderContext* pC)
{
	ASSERT(0);
#if 0
	COLORREF bgClr = GetSysColor(COLOR_HIGHLIGHT);
	COLORREF fgClr = GetSysColor(COLOR_HIGHLIGHTTEXT);

	LDraw::SolidBrush fgBrush(LDraw::Color(GetRValue(fgClr), GetGValue(fgClr), GetBValue(fgClr)));
	LDraw::SolidBrush bgBrush(LDraw::Color(GetRValue(bgClr), GetGValue(bgClr), GetBValue(bgClr)));

//	pC->m_pGraphics->FillRectangle(&fgBrush, 0, 0, 40, 40);

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

				pSVGTextContent->RenderSelection(pC);
			}
		}
		else
		{
			CPSVGText* pText = (CPSVGText*)pNode;

			int length = pText->m_glyphs.GetSize();

			int startChar;
			int endChar = -1;
			int m_start = 0;

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
					int len = length;//m_pTextNode->m_dataLength;

					// Check for start of selection
					if ((startContainer == pText->m_pNode) &&
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
					if ((endContainer == pText->m_pNode) &&
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

			//CPSVGFontElement* pSVGFont = m_computedFontFamily[0]->m_pSVGFontElement;//((PSVGElement*)m_parent)->m_pSVGFont;

			for (int i = 0; i < pText->m_glyphs.GetSize()-1; i++)
			{
				CGlyph* pGlyph = pText->m_glyphs[i];

				if (i >= startChar && i < endChar)
				{
					LDraw::Matrix oldmat;
					pC->m_pGraphics->GetTransform(&oldmat);

					//pGlyph->Render(pC, NULL, pC->m_pGraphics, 1, 1, m_pSVGFont, m_computedFontSize, &fgBrush, NULL);

					LDraw::Matrix matrix;
					matrix.RotateAt(pGlyph->m_rotation, pGlyph->m_position);
					matrix.Translate(pGlyph->m_position.X, pGlyph->m_position.Y);

					pC->m_pGraphics->MultiplyTransform(&matrix);

					LDraw::RectF rect(0, -pText->m_fontHeight+pGlyph->m_descent, pGlyph->m_charWidth/*+1*/, pText->m_fontHeight/*+1*/);
					pC->m_pGraphics->FillRectangle(&bgBrush, rect);

					pC->m_pGraphics->SetTransform(&oldmat);

					/*
					if (pSVGFont)
					{
						double scale = m_computedFontSize / pSVGFont->GetUnitsPerEm();

						//matrix.Scale(scale, -scale);
						pC->m_pGraphics->ScaleTransform(scale, -scale);
					}
					*/
					//pC->m_pGraphics->ScaleTransform(pGlyph->m_scale, -pGlyph->m_scale);

					pC->m_pGraphics->FillPath(&fgBrush, &pGlyph->m_GraphicsPathF);

					/*
					*/
				}
			}
		}
	}
#endif
}

void PSVGElement::RenderTextChildren(CHTMRenderContext* pC, LDraw::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen)
{
	double fillOpacity = m_computedFillOpacity;
	double strokeOpacity = m_computedStrokeOpacity;

	if (!bOffscreen)
	{
		fillOpacity *= m_computedOpacity;
		strokeOpacity *= m_computedOpacity;
	}

	Gui::Brush* pFillBrush = GetBrush(renderContext, &m_computedFill, m_pFillElement, fillOpacity, scaleX, scaleY);
	Gui::Brush* pStrokeBrush = GetBrush(renderContext, &m_computedStroke, m_pStrokeElement, strokeOpacity, scaleX, scaleY);

	/*
	LDraw::Pen* pPen;
	if (pStrokeBrush != NULL)
		pPen = GetPen(pStrokeBrush);
*/

	if (m_glyphs.GetSize())
	{
		//CPSVGFontElement* pSVGFont = m_computedFontFamily[0]->m_pSVGFontElement;//((PSVGElement*)m_parent)->m_pSVGFont;

		DWRITE_GLYPH_RUN glyphRun;
		glyphRun.fontFace = m_glyphs[0]->m_dwriteFontFace;

		uint16* indices = (uint16*)_alloca(sizeof(uint16)*m_glyphs.GetSize());
		float* advances = (float*)_alloca(sizeof(float)*m_glyphs.GetSize());
		DWRITE_GLYPH_OFFSET* offsets = (DWRITE_GLYPH_OFFSET*)_alloca(sizeof(DWRITE_GLYPH_OFFSET)*m_glyphs.GetSize());

		for (uint i = 0; i < m_glyphs.GetSize(); ++i)
		{
			CGlyph* pGlyph = m_glyphs[i];

			indices[i] = pGlyph->m_glyphIndex;
			advances[i] = 0;//pGlyph->m_charWidth;
			offsets[i].advanceOffset = pGlyph->m_position.X;
			offsets[i].ascenderOffset = -pGlyph->m_position.Y;
		}

		glyphRun.glyphIndices = indices;
		glyphRun.glyphCount = m_glyphs.GetSize();//pGlyph->m_glyphIndices.size();
		glyphRun.fontEmSize = m_computedFontSize;//pGlyph->m_emSize;
		glyphRun.isSideways = false;
		glyphRun.glyphOffsets = offsets;//pGlyph->m_glyphOffsets.begin();
		glyphRun.glyphAdvances = advances;

		renderContext->GetRT()->m_spRT->DrawGlyphRun(D2D1::Point2F(0,0), &glyphRun, pFillBrush->Create(renderContext, NULL));
	}
	else
	{
		vector<PNode*>::iterator pos = m_childList.begin();
		while (pos != m_childList.end())
		{
			PNode* pNode = *pos;
			++pos;

			if (pNode->m_type == NODE_TEXT)
			{
				PSVGText* pText = dynamic_cast<PSVGText*>(dynamic_cast<PText*>(pNode)->m_ext);

				DWRITE_GLYPH_RUN glyphRun;
				glyphRun.fontFace = pText->m_glyphs[0]->m_dwriteFontFace;

				uint16* indices = (uint16*)_alloca(sizeof(uint16)*pText->m_glyphs.GetSize());
				float* advances = (float*)_alloca(sizeof(float)*pText->m_glyphs.GetSize());
				DWRITE_GLYPH_OFFSET* offsets = (DWRITE_GLYPH_OFFSET*)_alloca(sizeof(DWRITE_GLYPH_OFFSET)*pText->m_glyphs.GetSize());

				for (uint i = 0; i < pText->m_glyphs.GetSize(); ++i)
				{
					CGlyph* pGlyph = pText->m_glyphs[i];

					indices[i] = pGlyph->m_glyphIndex;
					advances[i] = 0;//pGlyph->m_charWidth;
					offsets[i].advanceOffset = pGlyph->m_position.X;
					offsets[i].ascenderOffset = -pGlyph->m_position.Y;
				}

				glyphRun.glyphIndices = indices;
				glyphRun.glyphCount = pText->m_glyphs.GetSize();
				glyphRun.fontEmSize = m_computedFontSize;//pGlyph->m_emSize;
				glyphRun.isSideways = false;
				glyphRun.glyphOffsets = offsets;//pGlyph->m_glyphOffsets.begin();
				glyphRun.glyphAdvances = advances;

				renderContext->GetRT()->m_spRT->DrawGlyphRun(D2D1::Point2F(0,0), &glyphRun, pFillBrush->Create(renderContext, NULL));

#if 0
				for (uint i = 0; i < pText->m_glyphs.GetSize(); ++i)
				{
					CGlyph* pGlyph = pText->m_glyphs[i];

				//	pGlyph->

					DWRITE_GLYPH_RUN glyphRun;
					glyphRun.fontFace = pGlyph->m_dwriteFontFace;
					glyphRun.glyphIndices = pGlyph->m_glyphIndices.begin();
					glyphRun.glyphCount = pGlyph->m_glyphIndices.size();
					glyphRun.fontEmSize = pGlyph->m_emSize;
					glyphRun.isSideways = false;
					glyphRun.glyphOffsets = pGlyph->m_glyphOffsets.begin();
					glyphRun.glyphAdvances = pGlyph->m_glyphAdvances.begin();
					renderContext->GetRT()->m_spRT->DrawGlyphRun(D2D1::Point2F(0,0), &glyphRun, pFillBrush->Create(renderContext, NULL));

				//	pGlyph->Render(pC, pBitmap, renderContext, scaleX, scaleY, NULL/*pSVGFont*/, 0/*m_computedFontSize*/, pFillBrush, pPen);
				}
#endif
			// TODO
			//	CPSVGFontElement* pSVGFont = m_computedFontFamily[0]->m_pSVGFontElement;//((PSVGElement*)m_parent)->m_pSVGFont;

#if 0
				for (uint i = 0; i < pText->m_glyphs.GetSize(); ++i)
				{
					CGlyph* pGlyph = pText->m_glyphs[i];
			
					pGlyph->Render(pC, pBitmap, pGraphics, scaleX, scaleY, NULL/*pSVGFont*/, 0/*m_computedFontSize*/, pFillBrush, pPen);
				}
#endif
			}
		}
	}

	/*
	if (pPen)
		delete pPen;

	if (pFillBrush)
		delete pFillBrush;

	if (pStrokeBrush)
		delete pStrokeBrush;
		*/
}

// virtual
bool PSVGElement::NeedOffscreenBitmap() const
{
	if (m_pFilterElement) return true;
	if (m_pMaskElement) return true;
	if (m_pClipPathElement) return true;

	return false;
}

void ProcessMaskBitmap(LDraw::Bitmap* pMask, LDraw::Bitmap* pBitmap);

void Premultiply(D3DLOCKED_RECT locked_rect, void* srcData, int srcStride, int width, int height);

void PSVGElement::InvalidateBounds()
{
	if (m_boundsValid)
	{
		m_boundsValid = false;

//		PSVGElement* pViewportElement = GetViewportElement();
//		if (pViewportElement)
		{
			CHTMLWindow* pWindow = GetWindow();
			VERIFY(pWindow);
			pWindow->m_recalcBoundsList.push_back(this);

			pWindow->m_ownerVisual->InvalidateVisual();
		//	pWindow->m_ownerVisual->GetRoot()->InvalidateRender();

//			pWindow->InvalidateArrange();

			/*
			CalculateBoundsAndChildren();	// TODO not yet
			if (m_pWindow)
			{
				m_pWindow->InvalidateRender();
			}
			*/
		}
	}
}

LDraw::Bitmap* PSVGElement::GetBitmap(Gui::RenderContext* renderContext, int scaledWidth, int scaledHeight, double scaleX, double scaleY)
{
	UINT numOldViewports = 8;
	D3D10_VIEWPORT pOldViewports[8];
	renderContext->GetRT()->m_d3d10->m_device->RSGetViewports(&numOldViewports, pOldViewports);

	ID3D10RenderTargetView* pOldRenderTarget;
	renderContext->GetRT()->m_d3d10->m_device->OMGetRenderTargets(1, &pOldRenderTarget, NULL);

	ID3D10Texture2D* tempTexture = NULL;
	ID3D10ShaderResourceView* tempShaderResourceView = NULL;
	ID3D10RenderTargetView* tempRenderTargetView = NULL;


	// Create the render target texture and view
	D3D10_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = scaledWidth;
	desc.Height = scaledHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D10_USAGE_DEFAULT;
	desc.BindFlags = D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;
	renderContext->GetRT()->m_d3d10->m_device->CreateTexture2D(&desc, NULL, &tempTexture);

	IDXGISurface* dxgiSurface;
	tempTexture->QueryInterface(__uuidof(IDXGISurface), reinterpret_cast<void**>(&dxgiSurface));
	ASSERT(dxgiSurface);

	D3D10_RENDER_TARGET_VIEW_DESC rtDesc;
	rtDesc.Format = desc.Format;
	rtDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
	rtDesc.Texture2D.MipSlice = 0;
	renderContext->GetRT()->m_d3d10->m_device->CreateRenderTargetView(tempTexture, &rtDesc, &tempRenderTargetView);

	D3D10_SHADER_RESOURCE_VIEW_DESC srDesc;
	srDesc.Format = desc.Format;
	srDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	srDesc.Texture2D.MostDetailedMip = 0;
	srDesc.Texture2D.MipLevels = 1;
	renderContext->GetRT()->m_d3d10->m_device->CreateShaderResourceView(tempTexture, &srDesc, &tempShaderResourceView);

	renderContext->GetRT()->m_d3d10->m_device->OMSetRenderTargets(1, &tempRenderTargetView, NULL);

	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; // RGBA
	renderContext->GetRT()->m_d3d10->m_device->ClearRenderTargetView(tempRenderTargetView, ClearColor);

	D3D10_VIEWPORT vp;
	vp.Width = scaledWidth;
	vp.Height = scaledHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	renderContext->GetRT()->m_d3d10->m_device->RSSetViewports(1, &vp);

	LDraw::Bitmap* outImage = new LDraw::Bitmap(scaledWidth, scaledHeight, 0, LDraw::PixelFormat_t::RGBAP_32, NULL);

	outImage->m_d3d10_texture = tempTexture;
	outImage->m_d3d10_texture->AddRef();

	outImage->m_d3d10_shaderResourceView = tempShaderResourceView;
	outImage->m_d3d10_shaderResourceView->AddRef();

	{
		Gui::ImmediateRenderContext rcontext(renderContext->GetRT());
	//	rcontext.m_device1 = renderContext->GetRT()->m_device1;
		rcontext.m_rt->m_projection = LDraw::matrix4f::getOrtho2D(0, scaledWidth, scaledHeight, 0);
		rcontext.m_rt->m_modelView = LDraw::matrix4f::getIdentity();

		HRESULT hr = GL::Direct10::get_D2DFactory()->CreateDxgiSurfaceRenderTarget(dxgiSurface, 
			D2D1::RenderTargetProperties(
				D2D1_RENDER_TARGET_TYPE_HARDWARE,//D2D1_RENDER_TARGET_TYPE_DEFAULT,
				D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM/*DXGI_FORMAT_UNKNOWN*/, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96),
			&rcontext.m_rt->m_spRT);
		ASSERT(SUCCEEDED(hr));

		rcontext.GetRT()->m_spRT->BeginDraw();

		D2D1_MATRIX_3X2_F transform =
		{
			1, 0,
			0, 1,
			-m_expandedBBox.X, -m_expandedBBox.Y
		};
		rcontext.GetRT()->m_spRT->SetTransform(transform);//pO->SetTransform(LDraw::Matrix3f::GetTranslate(-m_expandedBBox.X, -m_expandedBBox.Y));

		Render4(NULL/*pC*/, outImage, &rcontext, scaleX, scaleY, false, false);

		rcontext.GetRT()->m_spRT->EndDraw();
		rcontext.GetRT()->m_spRT->Flush();
		rcontext.GetRT()->m_spRT->Release();
	}

	renderContext->GetRT()->m_d3d10->m_device->RSSetViewports(numOldViewports, pOldViewports);

	renderContext->GetRT()->m_d3d10->m_device->OMSetRenderTargets(1, &pOldRenderTarget, NULL);
	pOldRenderTarget->Release();

//	tempShaderResourceView->Release();
	tempRenderTargetView->Release();
	tempTexture->Release();
	dxgiSurface->Release();
	tempShaderResourceView->Release();

	return outImage;

#if 0
	LDraw::Direct3D9_I* pD3D9 = dynamic_cast<LDraw::Direct3D9_I*>(pO->m_device);

	HRESULT hr;

	IDirect3DTexture9* pTexture = NULL;
	IDirect3DSurface9* pTextureSurface = NULL;
	IDirect3DSurface9* pMultiSampleSurface = NULL;
	IDirect3DSurface9* pRenderTargetSurface = NULL;

	hr = pD3D9->m_d3dDevice->CreateTexture(m_scaledWidth, m_scaledHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTexture, NULL);
//	pD3D9->m_d3dDevice->CreateTexture(m_scaledWidth, m_scaledHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8, D3DPOOL_DEFAULT, &pTexture, NULL);
	ASSERT(pTexture);
	pTexture->GetSurfaceLevel(0, &pTextureSurface);

	outImage->m_texture = LDraw::Texture(pO->m_device, pTexture);

	D3DMULTISAMPLE_TYPE MultiSample = D3DMULTISAMPLE_4_SAMPLES;
//	D3DMULTISAMPLE_TYPE MultiSample = D3DMULTISAMPLE_NONMASKABLE;
	int quality = 0;

	if (MultiSample == D3DMULTISAMPLE_NONE)	// Create texture directly as RenderTarget
	{
		pRenderTargetSurface = pTextureSurface;
	}
	else	 // Create multisample RenderTarget
	{
		hr = pD3D9->m_d3dDevice->CreateRenderTarget(m_scaledWidth, m_scaledHeight, D3DFMT_A8R8G8B8, MultiSample, quality, FALSE/*lockable*/, &pMultiSampleSurface, NULL);
		ASSERT(pMultiSampleSurface);

		pRenderTargetSurface = pMultiSampleSurface;
	}

	IDirect3DSurface9* pOldRenderTarget;
	pD3D9->m_d3dDevice->GetRenderTarget(0, &pOldRenderTarget);

	pD3D9->m_d3dDevice->SetRenderTarget(0, pRenderTargetSurface);

	pD3D9->m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0x00000000, 0, 0);

//	LDraw::Direct3D9_I* device2 = new LDraw::Direct3D9_I(m_d3dDevice);
//	m_pGraphicsO->m_device = device2;

	if (true)
	{
		LDraw::Commands* commands = new LDraw::Commands;
		LDraw::GraphicsMetafile* pMetafile = new LDraw::GraphicsMetafile(pO->m_device, pO->m_bufferData, commands);
		UI::Graphics graphics(pMetafile);

		CHTMRenderContext rcontext;
		rcontext.m_clip = LDraw::RectF(0, 0, /*m_pReferencingElement->*/m_filterRect.Width, /*m_pReferencingElement->*/m_filterRect.Height);
		/*m_pReferencingElement->*/Render4(&rcontext, outImage, &graphics, m_scaleX, m_scaleY, false, false);

		pD3D9->SetMatrixMode(GL_PROJECTION);
		pD3D9->PushMatrix();
		pD3D9->SetTransform(LDraw::matrix4f::getOrtho(0, m_scaledWidth, m_scaledHeight, 0, -1/*zNear*/, 1/*zFar*/));

		pD3D9->SetMatrixMode(GL_MODELVIEW);
		pD3D9->PushMatrix();
		pD3D9->IdentityTransform();

		pO->PushTransform();
	//	pO->SetTransform(LDraw::Matrix3f::GetIdentity());
		pO->SetTransform(LDraw::Matrix3f::GetTranslate(-m_expandedBBox.X, -m_expandedBBox.Y));

	//	pD3D9->m_d3dDevice->BeginScene();
		pO->RenderCommands(commands);
	//	pD3D9->m_d3dDevice->EndScene();

		pO->PopTransform();

		pD3D9->SetMatrixMode(GL_PROJECTION);
		pD3D9->PopMatrix();
		pD3D9->SetMatrixMode(GL_MODELVIEW);
		pD3D9->PopMatrix();
	}
	else
	{
	//	Direct3D9_I
		LDraw::BufferData* bufferData = new LDraw::BufferData;
		LDraw::Direct3D9_I* device2 = new LDraw::Direct3D9_I(pD3D9->m_d3dDevice);

		LDraw::Commands* commands = new LDraw::Commands;
		LDraw::GraphicsMetafile* pMetafile = new LDraw::GraphicsMetafile(device2, bufferData, commands);
		UI::Graphics graphics(pMetafile);

		CHTMRenderContext rcontext;
		rcontext.m_clip = LDraw::RectF(0, 0, /*m_pReferencingElement->*/m_filterRect.Width, /*m_pReferencingElement->*/m_filterRect.Height);
		/*m_pReferencingElement->*/Render4(&rcontext, outImage, &graphics, m_scaleX, m_scaleY, false, false);

		LDraw::GraphicsO gO;
		
		gO.m_res = pO->m_res;
		/*
		gO.m_d3d9_effect = pO->m_d3d9_effect;
		gO.m_d3d9_technique0 = pO->m_d3d9_technique0;
		gO.m_d3d9_technique1 = pO->m_d3d9_technique1;
		gO.m_d3d9_technique2 = pO->m_d3d9_technique2;
		gO.m_d3d9_technique4 = pO->m_d3d9_technique4;

		gO.m_vertexDeclaration0 = pO->m_vertexDeclaration0;
		gO.m_vertexDeclaration1 = pO->m_vertexDeclaration1;

		gO.m_d3d9_modelViewVariable = pO->m_d3d9_modelViewVariable;
		gO.m_d3d9_projectionVariable = pO->m_d3d9_projectionVariable;
		gO.m_d3d9_modelViewProjectionVariable = pO->m_d3d9_modelViewProjectionVariable;
		gO.m_d3d9_textureMatrix0Variable = pO->m_d3d9_textureMatrix0Variable;
		gO.m_d3d9_solidColorVariable = pO->m_d3d9_solidColorVariable;
		gO.m_d3d9_texture0Variable = pO->m_d3d9_texture0Variable;
		*/

		gO.m_device = device2;
		gO.m_bufferData = bufferData;

		pD3D9->SetMatrixMode(GL_PROJECTION);
		pD3D9->PushMatrix();
		pD3D9->SetTransform(LDraw::matrix4f::getOrtho(0, m_scaledWidth, m_scaledHeight, 0, -1/*zNear*/, 1/*zFar*/));

		pD3D9->SetMatrixMode(GL_MODELVIEW);
		pD3D9->PushMatrix();
		pD3D9->IdentityTransform();

		device2->SetMatrixMode(GL_PROJECTION);
		device2->SetTransform(LDraw::matrix4f::getOrtho(0, m_scaledWidth, m_scaledHeight, 0, -1/*zNear*/, 1/*zFar*/));
		device2->SetMatrixMode(GL_MODELVIEW);
		device2->IdentityTransform();

	//	pD3D9->m_d3dDevice->BeginScene();
		gO.RenderCommands(commands);
	//	pD3D9->m_d3dDevice->EndScene();

		pD3D9->SetMatrixMode(GL_PROJECTION);
		pD3D9->PopMatrix();
		pD3D9->SetMatrixMode(GL_MODELVIEW);
		pD3D9->PopMatrix();
	}

	pD3D9->m_d3dDevice->SetRenderTarget(0, pOldRenderTarget);

	if (pMultiSampleSurface)
	{
		HRESULT hr;
		hr = pD3D9->m_d3dDevice->StretchRect(pMultiSampleSurface, NULL, pTextureSurface, NULL, D3DTEXF_POINT);
		ASSERT(SUCCEEDED(hr));

		pMultiSampleSurface->Release();
	}

	pTextureSurface->Release();
#endif
	return outImage;
}

void PSVGElement::Render(CHTMRenderContext* pC, Gui::RenderContext* renderContext, double scaleX, double scaleY)
{
	float opacity = m_computedOpacity;
	if (opacity < 0) opacity = 0;
	else if (opacity > 1) opacity = 1;

	if (m_pFilterElement)
	{
		double finalScaleX = scaleX;
		double finalScaleY = scaleY;

		// If the filter processing takes a lot of time, we cache the bitmap for later
	//	DWORD startTime = GetTickCount();

	//	pGraphics->m_pO->EnsureEffectLoaded();

		Gui::ImmediateRenderContext rc(pC->m_renderContext->GetRT());
		//rc.GetRT()->m_spRT->AddRef();

		rc.m_colorTransform = LDraw::matrix4f(	1, 0, 0, 0,
														0, 1, 0, 0,
														0, 0, 1, 0,
														0, 0, 0, opacity);

		LDraw::RectD irect;
		irect = m_filterRect;//m_expandedBBox;	// We Process the entire thing
		SVGFilterCommand* pCommand = m_pFilterElement->ProcessEffects(&rc, this, finalScaleX, finalScaleY);

		if (pCommand)
		{
			LDraw::RectD destRect = m_filterRect;
			pCommand->m_destRect.X = (float)destRect.X;
			pCommand->m_destRect.Y = (float)destRect.Y;
			pCommand->m_destRect.Width = (float)destRect.Width;
			pCommand->m_destRect.Height = (float)destRect.Height;

		// TODO, not like this

			pCommand->Render(&rc);
		}

	//	DWORD endTime = GetTickCount();

		/*
		if (endTime-startTime > 100) // milliseconds
		{
			m_pCachedBitmap = pBitmap;
		}
		*/
	}
	else
	{
		double finalScaleX = scaleX;
		double finalScaleY = scaleY;
		Render4(pC, NULL, renderContext, finalScaleX, finalScaleY, false, true);
	}
	return;

#if 0
	ASSERT(pC != NULL);

	pGraphics->PushTransform();

	LDraw::Matrix3f* oldMatrixToView = pC->m_matrixToView;

	// TODO local relative to the nearest offscreen bitmap
	LDraw::Matrix3d* mat = this->GetLocalAnimatedMatrix();

	LDraw::Matrix3f* matf = new LDraw::Matrix3f(
											float(mat->m_matrix[0][0]), float(mat->m_matrix[0][1]),
											float(mat->m_matrix[1][0]), float(mat->m_matrix[1][1]),
											float(mat->m_matrix[2][0]), float(mat->m_matrix[2][1]));

	pGraphics->MultiplyTransform(matf);

#if 0
	pC->m_matrixToView = mat * pC->m_matrixToView;
#endif

	bool bDraw;

//	if (pC)
//	{
		/*
		LDraw::Matrix cmat;
		pGraphics->GetTransform(&cmat);
		float m[6]; cmat.GetElements(m);
		gmMatrix3 cmat3(m[0], m[1], 0,
							m[2], m[3], 0,
							m[4], m[5], 1);
							*/

	//gmMatrix3 cmat3 = pC->m_matrixToView;
	//RectD cliprect = pC->m_clip;
	LDraw::RectD xcliprect;
	LDraw::GetTransformRectBoundingBox(pC->m_matrixToView->GetInverse(), pC->m_clip, &xcliprect);

	LDraw::RectD irect;
	bDraw = LDraw::RectD::Intersect(irect, m_filterRect, xcliprect);
	//bDraw = !irect.IsEmptyArea();//m_expandedBBox.IntersectsWith(xcliprect);
	/*
	}
	else
	{
		bDraw = TRUE;
	}
	*/

	if (true || bDraw)	// TODO, have this
	{
	//	pGraphics->SetClip(m_expandedBBox);

		double finalScaleX = m_scaleX * scaleX;
		double finalScaleY = m_scaleY * scaleY;

		if (!NeedOffscreenBitmap())
		{
			Render4(pC, NULL, renderContext, finalScaleX, finalScaleY, false, true);
		}
		else
		{
		//	MessageBeep(-1);

			double opacity = m_computedOpacity;
			if (opacity < 0) opacity = 0;
			else if (opacity > 1) opacity = 1;

#if 0
			// opacity
			LDraw::ColorMatrix colorMatrix = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
												0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
												0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
												0.0f, 0.0f, 0.0f, opacity, 0.0f,
												0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

		// Create an ImageAttributes object and set its color matrix.
			LDraw::ImageAttributes imageAtt;
			imageAtt.SetColorMatrix(&colorMatrix, LDraw::ColorMatrixFlagsDefault, LDraw::ColorAdjustTypeBitmap);
#endif

			SVGFilterCommand* pCommand = NULL;
		//	LDraw::Bitmap* pBitmap = NULL;

			//if (m_pCachedBitmap == NULL)
			{
				//RectD filterRect = m_expandedBBox;

				if (m_pFilterElement)
				{
					// If the filter processing takes a lot of time, we cache the bitmap for later
				//	DWORD startTime = GetTickCount();

					pGraphics->m_pO->EnsureEffectLoaded();

					irect = m_filterRect;//m_expandedBBox;	// We Process the entire thing
					pCommand = m_pFilterElement->ProcessEffects(pC->m_rt, this, finalScaleX, finalScaleY);

				//	DWORD endTime = GetTickCount();

					/*
					if (endTime-startTime > 100) // milliseconds
					{
						m_pCachedBitmap = pBitmap;
					}
					*/
				}
				else
				{
					int scaledWidth = ceil(irect.Width * finalScaleX);
					int scaledHeight = ceil(irect.Height * finalScaleY);

					ASSERT(0);
#if 0
					pBitmap = new LDraw::Bitmap(scaledWidth, scaledHeight, LDraw::PixelFormat_t::RGBAP_32);
					if (pBitmap)
					{
						UI::Graphics* graphics = new UI::Graphics(new LDraw::GraphicsO(pBitmap));

						graphics->ScaleTransform((float)finalScaleX, (float)finalScaleY);
						graphics->TranslateTransform((float)(m_expandedBBox.X-irect.X), (float)(m_expandedBBox.Y-irect.Y));
						graphics->TranslateTransform((float)-m_expandedBBox.X, (float)-m_expandedBBox.Y);

						Render4(pC, pBitmap, graphics, finalScaleX, finalScaleY, true, true);
					}
#endif
				}

				if (pCommand)
				{
#if 0	// TODO, have this
				//	if (m_computedColorInterpolation == ColorInterpolation_sRGB)
					{
						LDraw::BitmapData bitmapData;
						if (pBitmap->LockBits(
							&LDraw::Rect(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight()),
							LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite,
							PixelFormat32bppARGB, &bitmapData) == 0)
						{
							int width = bitmapData.Width;
							int height = bitmapData.Height;

							for (int y = 0; y < height; y++)
							{
								ARGBPixel* p = (ARGBPixel*)((BYTE*)bitmapData.Scan0 + bitmapData.Stride*y);

								for (int x = 0; x < width; x++)
								{
									p->red = linear_to_sRGB[p->red];
									p->green = linear_to_sRGB[p->green];
									p->blue = linear_to_sRGB[p->blue];

									p++;
								}
							}

							pBitmap->UnlockBits(&bitmapData);
						}
					}
#endif
				}

#if 0	// TODO, have this
				if (m_pClipPathElement)
				{
					CLSVGClipPathElement* psvgElement = static_cast<CLSVGClipPathElement*>(m_pClipPathElement->m_pNode);

					long scaledWidth = ceil(irect.Width * finalScaleX);
					long scaledHeight = ceil(irect.Height * finalScaleY);

					LDraw::Bitmap* pClipPathBitmap = new LDraw::Bitmap(scaledWidth, scaledHeight, PixelFormat24bppRGB);
					if (pClipPathBitmap)
					{
						PSVGElement* pReferencingElement = this;
						double scaleX = finalScaleX;
						double scaleY = finalScaleY;
						RectD rect = pReferencingElement->m_bounds;//expandedBBox;

						LDraw::Graphics graphics(pClipPathBitmap);

						graphics.SetSmoothingMode(LDraw::SmoothingModeHighQuality/*pGraphics->GetSmoothingMode()*/);

						if (psvgElement->m_clipPathUnits->m_animated->m_animVal->m_value->m_value == SVG_UNIT_TYPE_USERSPACEONUSE)
						{
							graphics.ScaleTransform(float(scaleX), float(scaleY));
							graphics.TranslateTransform(float(-m_expandedBBox.X), float(-m_expandedBBox.Y));
						}
						else if (psvgElement->m_clipPathUnits->m_animated->m_animVal->m_value->m_value == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
						{
							//pReferencingElement->m_bounds.
							graphics.ScaleTransform((float)scaleX, (float)scaleY);
							graphics.ScaleTransform((float)pReferencingElement->m_bounds.Width, (float)pReferencingElement->m_bounds.Height);
							//graphics.TranslateTransform((float)-rect.X, (float)-rect.Y);
							graphics.TranslateTransform((float)pReferencingElement->m_bounds.X, (float)pReferencingElement->m_bounds.Y);
							graphics.TranslateTransform((float)-rect.X, (float)-rect.Y);
						}
						else
							ASSERT(0);

						graphics.TranslateTransform((float)(m_expandedBBox.X-irect.X), (float)(m_expandedBBox.Y-irect.Y));

						UPOSITION pos = m_pClipPathElement->m_childListRender.GetHeadPosition();
						while (pos)
						{
							PSVGElement* pElement = (PSVGElement*)m_pClipPathElement->m_childListRender.GetNext(pos);

							if (pElement->m_computedDisplayRole != DisplayRole_none && pElement->m_computedVisibility != Visibility_hidden)
							{
								LDraw::Matrix oldmat;
								graphics.GetTransform(&oldmat);

								Matrix mat = pElement->GetLocalAnimatedMatrix();

								LDraw::GraphicsPathF path(pElement->m_computedClipRule == ClipRule_nonzero? LDraw::FillModeWinding: LDraw::FillModeAlternate);
								pElement->RenderPath(&path);

								LDraw::Matrix gdipMatrix;
								mat.GetGdipMatrix(gdipMatrix);
								graphics.MultiplyTransform(&gdipMatrix);

								graphics.FillPath(&LDraw::SolidBrush(LDraw::Color(255, 255, 255)), &path);

								graphics.SetTransform(&oldmat);
							}
						}

						ProcessMaskBitmap(pClipPathBitmap, pBitmap);

						delete pClipPathBitmap;
						pClipPathBitmap = NULL;
					}
				}
#endif
			}

			/*
			else
			{
				MessageBeep(-1);
				pBitmap = m_pCachedBitmap;	// No need to do anything, use cached bitmap
			}
			*/

	#if 0
			if (pBitmap)
			{
			// Reversed
				if (m_computedColorInterpolation == ColorInterpolation_sRGB)
					pGraphics->SetCompositingQuality(LDraw::CompositingQualityAssumeLinear/*CompositingQualityHighQuality*/);
				else
					pGraphics->SetCompositingQuality(LDraw::CompositingQualityGammaCorrected);
			}
	#endif

			if (pCommand)
			{
				LDraw::RectD destRect = irect;//m_expandedBBox;

			//	LDraw::RectF srcRect(0, 0, (float)(m_expandedBBox.Width*finalScaleX), (float)(m_expandedBBox.Height*finalScaleY));
				LDraw::RectF srcRect(0, 0, (float)(irect.Width*finalScaleX), (float)(irect.Height*finalScaleY));

				LDraw::GraphicsMetafile* pMetafile = dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p);

				pCommand->m_destRect.X = (float)destRect.X;
				pCommand->m_destRect.Y = (float)destRect.Y;
				pCommand->m_destRect.Width = (float)destRect.Width;
				pCommand->m_destRect.Height = (float)destRect.Height;

			//	pMetafile->m_pCommands->AddCommand(pCommand);
#if 0
				pGraphics->DrawImage(
					pBitmap,
					destRect,
					srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height/*,
					LDraw::UnitPixel,
					&imageAtt*/);
#endif

#if 0
				if (pBitmap != m_pCachedBitmap)
					;//delete pBitmap;
#endif
			}
		}
	}

	pGraphics->PopTransform();
	pC->m_matrixToView = oldMatrixToView;
#endif
}

// virtual
void PSVGElement::Render4(CHTMRenderContext* pC, LDraw::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
	if (bDrawBehaviors)
	{
		ASSERT(0);
#if 0
		for (int i = 0; i < m_behaviors.GetSize(); i++)
		{
			CComQIPtr<IHTMLPainter> htmlPainter = m_behaviors[i]->m_p;

			if (htmlPainter)
			{
				CRect rcBounds(0, 0, 400, 400);	// TODO
				CRect rcUpdate(0, 0, 400, 400);	// TODO

				long lDrawFlags = 0;	// HTMLPAINT_DRAW_UPDATEREGION = 0x000001,
									  //  HTMLPAINT_DRAW_USE_XFORM = 0x000002

				HDC hDC = pGraphics->GetHDC();
		
				//CPoint oldOrg;
				//OffsetViewportOrgEx(hDC, -pC->m_clipBox.left, -pC->m_clipBox.top, &oldOrg);

				ATLTRACE("clipBox: left%d\n", pC->m_clipBox.left);

				htmlPainter->Draw(rcBounds, rcUpdate, lDrawFlags, hDC, NULL);

				//SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

				pGraphics->ReleaseHDC(hDC);
			}
		}
#endif
	}
}

//virtual
LDraw::Matrix3d* PSVGElement::GetScreenCTM()
{
	LDraw::Matrix3d* p = GetViewBoxMatrix();

	return *p * *GetScreenCTM2();
}

//virtual
LDraw::Matrix3d* PSVGElement::GetScreenCTM2()
{
	LDraw::Matrix3d* p = GetLocalAnimatedMatrix();

	if (m_parent)
	{
		ASSERT(0);
#if 0
		if (CComQIPtr<ILSVGElement>(m_parent->m_pNode))
		{
			gmMatrix3 p2 = ((PSVGElement*)m_parent)->GetScreenCTM();

			p = p * p2;
		}
#endif
	}

	return p;
}

list<PElementBase*>::iterator PSVGElement::AddReferencingElement(PElementBase* pPElement)
{
#if 0
#ifdef _DEBUG
	ASSERT(m_referencingElements.Find(pPElement) == NULL);
#endif
#endif

	return m_referencingElements.insert(m_referencingElements.end(), pPElement);
}

////////////////////
// CSS

void PSVGElement::GetFillUriElement()
{
	if (m_pFillElement)
	{
		ASSERT(0);
#if 0
		UPOSITION pos = m_pFillElement->m_referencingElements.Find(this);
		ASSERT(pos);
		m_pFillElement->m_referencingElements.RemoveAt(pos);
#endif
		m_pFillElement = NULL;
	}

	if (m_computedFill.m_uri && m_computedFill.m_uri.GetLength())
	{
		ASSERT(0);
#if 0
		if (m_computedFill.m_uri->c_str()[0] == L'#')
		{
			String uri = string_copy(m_computedFill.m_uri->c_str()+1, m_computedFill.m_uri->Length()-1);

			Element* element = m_pNode->m_ownerDocument->getElementById(uri);
			m_pFillElement = dynamic_cast<PSVGElement*>(element->m_pNode);//m_pView->m_pRootElement->GetElementById(uri);
			if (m_pFillElement)
			{
				m_pFillElement->AddReferencingElement(this);
			}
		}
#endif
	}
}

void PSVGElement::GetStrokeUriElement()
{
	if (m_pStrokeElement)
	{
		ASSERT(0);
#if 0
		UPOSITION pos = m_pStrokeElement->m_referencingElements.Find(this);
		ASSERT(pos);
		m_pStrokeElement->m_referencingElements.RemoveAt(pos);
#endif
		m_pStrokeElement = NULL;
	}

	if (m_computedStroke.m_uri && m_computedStroke.m_uri.GetLength())
	{
			ASSERT(0);
#if 0
		if (m_computedStroke.m_uri->c_str()[0] == L'#')
		{
			String uri = string_copy(m_computedStroke.m_uri->c_str()+1, m_computedStroke.m_uri->Length()-1);

			Element* element = m_pNode->m_ownerDocument->getElementById(uri);
			m_pStrokeElement = dynamic_cast<PSVGElement*>(element->m_pNode);
			if (m_pStrokeElement)
			{
				m_pStrokeElement->AddReferencingElement(this);
			}
		}
#endif
	}
}

void PSVGElement::GetMarkerStartElement()
{
	ASSERT(0);
#if 0
	if (m_pMarkerStartElement)
	{
		UPOSITION pos = m_pMarkerStartElement->m_referencingElements.Find(this);
		ASSERT(pos);
		m_pMarkerStartElement->m_referencingElements.RemoveAt(pos);
		m_pMarkerStartElement = NULL;
	}

	if (m_computedMarkerStartUri.Length())
	{
		if (((BSTR)m_computedMarkerStartUri)[0] == L'#')
		{
			BSTR uri = ((BSTR)m_computedMarkerStartUri)+1;

			PSVGMarkerElement* pMarkerElement = (PSVGMarkerElement*)m_pView->m_pRootElement->GetElementById(uri);
			if (pMarkerElement)
			{
				CComQIPtr<ILSVGMarkerElement> markerElement = pMarkerElement->m_pNode;
				if (markerElement)
				{
					m_pMarkerStartElement = pMarkerElement;
					m_pMarkerStartElement->AddReferencingElement(this);
				}
			}
		}
	}
#endif
}

void PSVGElement::GetMarkerEndElement()
{
	ASSERT(0);
#if 0
	if (m_pMarkerEndElement)
	{
		UPOSITION pos = m_pMarkerEndElement->m_referencingElements.Find(this);
		ASSERT(pos);
		m_pMarkerEndElement->m_referencingElements.RemoveAt(pos);
		m_pMarkerEndElement = NULL;
	}

	if (m_computedMarkerEndUri.Length())
	{
		if (((BSTR)m_computedMarkerEndUri)[0] == L'#')
		{
			BSTR uri = ((BSTR)m_computedMarkerEndUri)+1;

			PSVGMarkerElement* pMarkerElement = (PSVGMarkerElement*)m_pView->m_pRootElement->GetElementById(uri);
			if (pMarkerElement)
			{
				CComQIPtr<ILSVGMarkerElement> markerElement = pMarkerElement->m_pNode;
				if (markerElement)
				{
					m_pMarkerEndElement = pMarkerElement;
					m_pMarkerEndElement->AddReferencingElement(this);
				}
			}
		}
	}
#endif
}

void PSVGElement::GetMarkerMidElement()
{
	ASSERT(0);
#if 0
	if (m_pMarkerMidElement)
	{
		UPOSITION pos = m_pMarkerMidElement->m_referencingElements.Find(this);
		ASSERT(pos);
		m_pMarkerMidElement->m_referencingElements.RemoveAt(pos);
		m_pMarkerMidElement = NULL;
	}

	if (m_computedMarkerMidUri.Length())
	{
		if (((BSTR)m_computedMarkerMidUri)[0] == L'#')
		{
			BSTR uri = ((BSTR)m_computedMarkerMidUri)+1;

			PSVGMarkerElement* pMarkerElement = (PSVGMarkerElement*)m_pView->m_pRootElement->GetElementById(uri);
			if (pMarkerElement)
			{
				CComQIPtr<ILSVGMarkerElement> markerElement = pMarkerElement->m_pNode;
				if (markerElement)
				{
					m_pMarkerMidElement = pMarkerElement;
					m_pMarkerMidElement->AddReferencingElement(this);
				}
			}
		}
	}
#endif
}

void PSVGElement::GetFilterElement()
{
	if (m_pFilterElement)
	{
#if 0
		UPOSITION pos = m_pFilterElement->m_referencingElements.Find(this);
		ASSERT(pos);
		m_pFilterElement->m_referencingElements.RemoveAt(pos);
#endif
		m_pFilterElement->m_referencingElements.erase(m_pFilterElementIt);
		m_pFilterElement = NULL;
	}

	if (m_computedFilterUri && m_computedFilterUri.GetLength())
	{
	ASSERT(0);
#if 0
		if (m_computedFilterUri->c_str()[0] == L'#')
		{
			String uri = string_copy(m_computedFilterUri->c_str()+1, m_computedFilterUri->Length()-1));

			Element* element = m_pNode->m_ownerDocument->getElementById(uri);
			if (element)
			{
				PSVGFilterElement* pFilterElement = dynamic_cast<PSVGFilterElement*>(element->m_pNode);
				if (pFilterElement)
				{
					m_pFilterElement = pFilterElement;
					m_pFilterElementIt = m_pFilterElement->AddReferencingElement(this);
				}
			}
		}
#endif
	}
}

void PSVGElement::GetClipPathElement()
{
#if 0
	if (m_pClipPathElement)
	{
		UPOSITION pos = m_pClipPathElement->m_referencingElements.Find(this);
		ASSERT(pos);
		m_pClipPathElement->m_referencingElements.RemoveAt(pos);
		m_pClipPathElement = NULL;
	}

	if (m_computedClipPathUri.Length())
	{
		if (((BSTR)m_computedClipPathUri)[0] == L'#')
		{
			BSTR uri = ((BSTR)m_computedClipPathUri)+1;

			CPSVGClipPathElement* pClipPathElement = (CPSVGClipPathElement*)m_pView->m_pRootElement->GetElementById(uri);
			if (pClipPathElement)
			{
				CComQIPtr<ILSVGClipPathElement> clipPathElement = pClipPathElement->m_pNode;
				if (clipPathElement)
				{
					m_pClipPathElement = pClipPathElement;
					m_pClipPathElement->AddReferencingElement(this);
				}
			}
		}
	}
#endif
}

void PSVGElement::GetMaskElement()
{
#if 0
	if (m_pMaskElement)
	{
		UPOSITION pos = m_pMaskElement->m_referencingElements.Find(this);
		ASSERT(pos);
		m_pMaskElement->m_referencingElements.RemoveAt(pos);
		m_pMaskElement = NULL;
	}

	if (m_computedMaskUri.Length())
	{
		if (((BSTR)m_computedMaskUri)[0] == L'#')
		{
			BSTR uri = ((BSTR)m_computedMaskUri)+1;

			ASSERT(0);
#if 0
			CPSVGMaskElement* pMaskElement = (CPSVGMaskElement*)m_pWindow->m_htmTree->GetElementById(uri);
			if (pMaskElement)
			{
				CComQIPtr<ILSVGMaskElement> maskElement = pMaskElement->m_pNode;
				if (maskElement)
				{
					m_pMaskElement = pMaskElement;
					m_pMaskElement->AddReferencingElement(this);
				}
			}
#endif
		}
	}
#endif
}

//virtual
PSVGElement* PSVGElement::HitTestElement(LDraw::Matrix3d* matrix, LDraw::PointD pt)
{
	matrix = *GetLocalAnimatedMatrix() * *matrix;

	LDraw::PointD xpt = matrix->GetInverse()->Transform(pt);

	if (m_expandedBBox.Contains(xpt.X, xpt.Y))
	{
		PSVGElement* pHitElement = HitTestChildren(matrix, pt);
		if (pHitElement)
		{
			return pHitElement;
		}

		if (HitTest(xpt.X, xpt.Y))
		{
			return this;
		}
	}

	return NULL;
}

PSVGElement* PSVGElement::HitTestChildren(LDraw::Matrix3d* matrix2, LDraw::PointD pt)
{
	LDraw::Matrix3d* matrix = *GetViewBoxMatrix() * *matrix2;

	for (int i = m_childListRender.size()-1; i >= 0; i--)
	{
		PSVGElement* pChildElement = m_childListRender[i];

		if (pChildElement->m_computedDisplayRole != DisplayRole_none)
		{
			PSVGElement* pHitElement = pChildElement->HitTestElement(matrix, pt);

			if (pHitElement)
				return pHitElement;
		}
	}

	return NULL;

}

//virtual
void PSVGElement::CalculateDimensions(CHTMCalcContext* pC)
{
	CalculateChildrenDimensions(pC);
}

// virtual
void PSVGElement::OnAttrChanged(Attr* attr)
{
	ASSERT(0);
#if 0
	CRect unionrect;

	{
		gmMatrix3 ctm = GetScreenCTM();

		LDraw::RectD xrect;
		GetTransformRectBoundingBox(ctm, m_expandedBBox, &xrect);

		CRect rect((int)xrect.X, (int)xrect.Y, (int)ceil(xrect.GetRight()), (int)ceil(xrect.GetBottom()));
		unionrect = rect;//pPElement->m_pWindow->InvalidateRect(&rect);
	}

	ASSERT(0);
#if 0
	CPElement::OnAttrChanged(attr);
#endif

	{
		gmMatrix3 ctm = GetScreenCTM();

		LDraw::RectD xrect;
		GetTransformRectBoundingBox(ctm, m_expandedBBox, &xrect);

		ASSERT(0);
#if 0
		CRect rect((int)xrect.X, (int)xrect.Y, (int)ceil(xrect.GetRight()), (int)ceil(xrect.GetBottom()));

		unionrect.UnionRect(&rect, &unionrect);
#endif
	}

	// TODO
	// Invalidate(unionrect);
#endif
}

///////////////////////////

PSVGTransformableElement::PSVGTransformableElement(SVGTransformableElement* element) : PSVGElement(element)
{
}

LDraw::Matrix3d* PSVGTransformableElement::GetLocalAnimatedMatrix()
{
	SVGTransformableElement* psvgElement = static_cast<SVGTransformableElement*>(m_pNode);
	LDraw::Matrix3d* matrix = psvgElement->transform_attr()->m_animVal->consolidateToMatrix();
	if (m_animateMotionMatrix)
	{
		matrix = *matrix * *m_animateMotionMatrix;
	}

	return matrix;
}

///////////////////////////

PSVGShapeElement::PSVGShapeElement(SVGTransformableElement* element) : PSVGTransformableElement(element)
{
}
/*
void PSVGShapeElement::CalculateBounds()
{
	CalculateBounds2();
}

void PSVGShapeElement::CalculateBounds2()
{
}
*/

Style::IStyleDeclaration* PSVGElement::get_inlineStyle(uint index)
{
	if (index == 1)
	{
		SVGElement* svgelement = dynamic_cast<SVGElement*>(m_pNode);
		if (svgelement)
		{
			return svgelement->m_presentationAttributes;
		}
	}
	else
	{
		IElementCSSInlineStyle* inlineStyle = dynamic_cast<IElementCSSInlineStyle*>(m_pNode);
		if (inlineStyle)
		{
			return inlineStyle->get_style();
		}
	}

	return NULL;
}

}	// Web
}	// System
