#include "stdafx.h"
#include "HTML2.h"

#include "PSMILRegionElement.h"
#include "SMILRegionElement.h"

#include "SMILDocument.h"
#include "SMILMediaElement.h"

#include "../LSMILTransitions/LSMILTransitions.h"

namespace System
{

LFCEXT int GetSemicolonSepStringArray(StringW* str, vector<StringW*>& values);

namespace Web
{

void SortRegions(vector<PSMILRegionElement*>& regions, PSMILElement* parent);

void CalcRegion(CLengthValue* pLeftValue, CLengthValue* pRightValue, CLengthValue* pWidthValue, double parentComputedWidth, double& m_computedLeft, double& m_computedWidth)
{
	ASSERT(0);
#if 0
	double specifiedLeft;
	double specifiedRight;
	double specifiedWidth;

	if (pLeftValue->m_unitType == CSS_PERCENTAGE)
		specifiedLeft = (parentComputedWidth * pLeftValue->m_value) / 100;
	else
		specifiedLeft = pLeftValue->m_value;

	if (pRightValue->m_unitType == CSS_PERCENTAGE)
		specifiedRight = (parentComputedWidth * pRightValue->m_value) / 100;
	else
		specifiedRight = pRightValue->m_value;

	if (pWidthValue->m_unitType == CSS_PERCENTAGE)
		specifiedWidth = (parentComputedWidth * pWidthValue->m_value) / 100;
	else
		specifiedWidth = pWidthValue->m_value;

// Calculate left/width
	if (pLeftValue->m_unitType == -1 && pWidthValue->m_unitType == -1 && pRightValue->m_unitType == -1)
	{
		m_computedLeft = 0;
		m_computedWidth = parentComputedWidth;
	}
	else if (pLeftValue->m_unitType == -1 && pWidthValue->m_unitType == -1 && pRightValue->m_unitType != -1)
	{
		m_computedLeft = 0;
		m_computedWidth = parentComputedWidth-specifiedRight;
	}
	else if (pLeftValue->m_unitType == -1 && pWidthValue->m_unitType != -1 && pRightValue->m_unitType == -1)
	{
		m_computedLeft = 0;
		m_computedWidth = specifiedWidth;
	}
	else if (pLeftValue->m_unitType == -1 && pWidthValue->m_unitType != -1 && pRightValue->m_unitType != -1)
	{
		m_computedLeft = parentComputedWidth - specifiedRight - specifiedWidth;
		m_computedWidth = specifiedWidth;
	}
	else if (pLeftValue->m_unitType != -1 && pWidthValue->m_unitType == -1 && pRightValue->m_unitType == -1)
	{
		m_computedLeft = specifiedLeft;
		m_computedWidth = parentComputedWidth-specifiedLeft;
	}
	else if (pLeftValue->m_unitType != -1 && pWidthValue->m_unitType == -1 && pRightValue->m_unitType != -1)
	{
		m_computedLeft = specifiedLeft;
		m_computedWidth = parentComputedWidth-specifiedLeft-specifiedRight;
	}
	else if (pLeftValue->m_unitType != -1 && pWidthValue->m_unitType != -1 && pRightValue->m_unitType == -1)
	{
		m_computedLeft = specifiedLeft;
		m_computedWidth = specifiedWidth;
	}
	else if (pLeftValue->m_unitType != -1 && pWidthValue->m_unitType == -1 && pRightValue->m_unitType != -1)
	{
		m_computedLeft = specifiedLeft;
		m_computedWidth = specifiedWidth;
	}
	else
		ASSERT(0);
#endif
}

void FindFirstSupportedTransition(Document* document,
											 SMILTransitionFactory* transitionFactory,
											 SVGStringList* stringList, Element* & transitionElement, ISMILTransition*& transition)
{
	unsigned int i = 0;
	while (i < stringList->m_items.size())
	{
		Element* element = document->getElementById(stringList->m_items[i]);
		if (element)
		{
			transitionElement = element;
			if (transitionElement)
			{
				String type = transitionElement->getAttribute(WSTR("type"));
				String subtype = transitionElement->getAttribute(WSTR("subtype"));

				ASSERT(0);
#if 0

				transitionFactory->FindTransition(type.c_str(), subtype.c_str(), &transition);
				if (transition)
					break;
#endif
			}
		}

		i++;
	}
}

bool ProcessTransition(Gui::ManagedRetainedRenderContext pGraphics, Graphics::Bitmap* pMediaBitmap, Graphics::Bitmap* pABitmap, gm::RectD& mediaRect, gm::RectD& fittedRect, Element* transitionElement, ISMILTransition* transition, SMILTransitionFactory* transitionFactory, double progress)
{
	String bstr_borderColor = transitionElement->getAttribute(WSTR("borderColor"));

	String bstr_borderWidth = transitionElement->getAttribute(WSTR("borderWidth"));
	long borderWidth = 0;
	if (bstr_borderWidth != NULL)
		borderWidth = str2int(CStringw(bstr_borderWidth).c_str());

	String bstr_direction = transitionElement->getAttribute(WSTR("direction"));

	Graphics::Bitmap* pResultBitmap = new Graphics::Bitmap(mediaRect.Width, mediaRect.Height, Graphics::PixelFormat_t::RGBAP_32);
	if (pResultBitmap)
	{
		/*
		_RectD rectA;
		rectA.X = 0;
		rectA.Y = 0;
		rectA.Width = pMediaBitmap->GetWidth();
		rectA.Height = pMediaBitmap->GetHeight();

		_RectD rectB;
		rectB.X = 0;
		rectB.Y = 0;
		rectB.Width = pMediaBitmap->GetWidth();
		rectB.Height = pMediaBitmap->GetHeight();

		_RectD rect;
		rect.X = 0;
		rect.Y = 0;
		rect.Width = mediaRect.Width;
		rect.Height = mediaRect.Height;
		*/

		// Reverse is accomplished by swapping A and B and setting progress to 1-progress

		// reverse
		if (bstr_direction.GetLength()==0 || bstr_direction != L"reverse")
		{
			ASSERT(0);
#if 0
			transitionFactory->ProcessTransition(transition,
				NULL, NULL, borderWidth, bstr_borderColor,
				progress,
				/*rectA,*/ (long)pABitmap,
				/*rectB,*/ (long)pMediaBitmap,
				/*rect,*/ (long)pResultBitmap);
#endif
		}
		// forward
		else
		{
			ASSERT(0);
#if 0
			transitionFactory->ProcessTransition(transition,
				NULL, NULL, borderWidth, bstr_borderColor,
				1-progress,
				/*rectB,*/ (long)pMediaBitmap,
				/*rectA,*/ (long)pABitmap,
				/*rect,*/ (long)pResultBitmap);
#endif
		}

		ASSERT(0);
#if 0
		pGraphics->DrawImage(pResultBitmap,
			fittedRect,
			0, 0, pResultBitmap->GetWidth(), pResultBitmap->GetHeight()/*,
			LDraw::UnitPixel*/);
#endif
	//	delete pResultBitmap;
		return true;
	}

	return false;
}

// virtual
void PSMILRegionElement::Render(Graphics::Bitmap* pBgBitmap, /*LDraw::Bitmap* pBackgroundBitmap,*/ Gui::ManagedRetainedRenderContext, double scaleX, double scaleY)
{
	ASSERT(0);
#if 0
	CLSMILRegionElement* psmilElement = static_cast<CLSMILRegionElement*>(m_pNode);

	CLengthValue* pLeftValue = psmilElement->m_left->m_animated->m_animVal->m_value;
	CLengthValue* pRightValue = psmilElement->m_right->m_animated->m_animVal->m_value;
	CLengthValue* pWidthValue = psmilElement->m_width->m_animated->m_animVal->m_value;

	CLengthValue* pTopValue = psmilElement->m_top->m_animated->m_animVal->m_value;
	CLengthValue* pBottomValue = psmilElement->m_bottom->m_animated->m_animVal->m_value;
	CLengthValue* pHeightValue = psmilElement->m_height->m_animated->m_animVal->m_value;

	CalcRegion(pLeftValue, pRightValue, pWidthValue, m_parent->m_computedWidth, m_computedLeft, m_computedWidth);
	CalcRegion(pTopValue, pBottomValue, pHeightValue, m_parent->m_computedHeight, m_computedTop, m_computedHeight);

// Should it be converted to integers ?
	RectD rgnRect(
		m_computedLeft,
		m_computedTop,
		m_computedWidth,
		m_computedHeight);

	/*
	LDraw::Bitmap* pBitmap = new LDraw::Bitmap(rgnRect.Width, rgnRect.Height);
	if (pBitmap)
	{
		LDraw::Graphics graphics(pBitmap);
		*/

		//CComBSTR showBackground;
		//psmilElement->getAttribute(L"showBackground", &showBackground);

		BOOL bShowBackground = TRUE;	// defaults to always
		if (psmilElement->m_showBackground->m_animated->m_animVal->m_value == SHOWBACKGROUND_WHEN_ACTIVE)
		{
			if (psmilElement->m_mediaElements.GetSize() == 0)
				bShowBackground = FALSE;
		}

		if (bShowBackground)
		{
			pGraphics->FillRectangle(
				&LDraw::SolidBrush(
				LDraw::Color(
					psmilElement->m_backgroundColor->m_animated->m_animVal->m_value->m_alpha,
					psmilElement->m_backgroundColor->m_animated->m_animVal->m_value->ClampRed(),
					psmilElement->m_backgroundColor->m_animated->m_animVal->m_value->ClampGreen(),
					psmilElement->m_backgroundColor->m_animated->m_animVal->m_value->ClampBlue())),

				rgnRect);
		}

		// Draw children
	//	Render2(pBitmap, &graphics, scaleX, scaleY);

		{
			// Draw the media objects that are active in this region

			for (int i = 0; i < psmilElement->m_mediaElements.GetSize(); i++)
			{
				CLSMILMediaElement* psmilMedia = static_cast<CLSMILMediaElement*>(psmilElement->m_mediaElements[i]);

				LDraw::Bitmap* pMediaBitmap;
				psmilMedia->GetBitmap(&pMediaBitmap);

				if (pMediaBitmap)
				{
					RectD subRect = psmilMedia->GetSubRegion(m_computedWidth, m_computedHeight);
					subRect.X += rgnRect.X;
					subRect.Y += rgnRect.Y;

					long mediaWidth = pMediaBitmap->GetWidth();
					long mediaHeight = pMediaBitmap->GetHeight();
					//psmilMedia->GetWidth(&mediaWidth);
					//psmilMedia->GetHeight(&mediaHeight);

					LDraw::RectD fittedRect;

					switch (psmilElement->m_fit->m_animated->m_animVal->m_value->m_value)
					{
					case Fit_fill:
						{
							fittedRect.X = 0;
							fittedRect.Y = 0;
							fittedRect.Width = subRect.Width;
							fittedRect.Height = subRect.Height;
						}
						break;

					case Fit_hidden:
						{
							fittedRect.X = 0;
							fittedRect.Y = 0;
							fittedRect.Width = mediaWidth;
							fittedRect.Height = mediaHeight;
						}
						break;

					case Fit_meet:
						{
						}
						break;

					case Fit_slice:
						{
						}
						break;
					}

					fittedRect.X += subRect.X;
					fittedRect.Y += subRect.Y;

					//pGraphics->TranslateTransform(subRect.X, subRect.Y);

					//////

				// Find the absolute rect in screen coordinates
					RectD mediaRect = fittedRect;
					CPElement* pParent = m_parent;
					while (pParent)
					{
						mediaRect.X += pParent->m_computedLeft;
						mediaRect.Y += pParent->m_computedTop;
						pParent = pParent->m_parent;
					}

					BOOL bTransIn = FALSE;
					BOOL bTransOut = FALSE;

					if (psmilMedia->m_transIn->m_value->m_value->m_items.GetSize() ||
						psmilMedia->m_transOut->m_value->m_value->m_items.GetSize())
					{
						CComPtr<ILSMILTransitionFactory> transitionFactory;
						transitionFactory.CoCreateInstance(CLSID_LSMILTransitionFactory);
						if (transitionFactory)
						{
							CComPtr<ILSMILTransition> transitionIn;
							CComQIPtr<ILDOMElement> transitionElementIn;

							CComPtr<ILSMILTransition> transitionOut;
							CComQIPtr<ILDOMElement> transitionElementOut;

							if (psmilMedia->m_transIn->m_value->m_value->m_items.GetSize())
							{
								FindFirstSupportedTransition(psmilMedia->m_ownerDocument, transitionFactory, psmilMedia->m_transIn->m_value->m_value, transitionElementIn, transitionIn);
							}

							if (psmilMedia->m_transOut->m_value->m_value->m_items.GetSize())
							{
								FindFirstSupportedTransition(psmilMedia->m_ownerDocument, transitionFactory, psmilMedia->m_transOut->m_value->m_value, transitionElementOut, transitionOut);
							}

							double transInDur;
							double transOutDur;

							if (transitionIn)
							{
								CComBSTR bstr_dur;
								transitionElementIn->getAttribute(L"dur", &bstr_dur);
								if (bstr_dur != NULL)
									transInDur = ParseClockValue(bstr_dur);
								else
									transInDur = 1;	// default

								if (psmilMedia->m_tau < transInDur)
								{
									bTransIn = TRUE;
								}
							}

							if (transitionOut)
							{
								CComBSTR bstr_dur;
								transitionElementOut->getAttribute(L"dur", &bstr_dur);
								if (bstr_dur != NULL)
									transOutDur = ParseClockValue(bstr_dur);
								else
									transOutDur = 1;	// default

								if (psmilMedia->m_tau >= (psmilMedia->m_AD-transOutDur))
								{
									bTransOut = TRUE;
								}
							}

							if (bTransIn || bTransOut)
							{
								LDraw::Bitmap* pABitmap = new LDraw::Bitmap(pMediaBitmap->GetWidth(), pMediaBitmap->GetHeight());
								if (pABitmap)
								{
									{	// BLOCK
										LDraw::Graphics gfx(pABitmap);

										gfx.DrawImage(pBgBitmap, LDraw::RectF(0, 0, mediaRect.Width, mediaRect.Height),
											mediaRect.X, mediaRect.Y, mediaRect.Width, mediaRect.Height, LDraw::UnitPixel);
									}

									if (bTransIn)
									{
										double progress = psmilMedia->m_tau / transInDur;

										bTransIn = ProcessTransition(pGraphics, pMediaBitmap, pABitmap, mediaRect, fittedRect, transitionElementIn, transitionIn, transitionFactory, progress);
									}
								// NOTE: Maybe process both if they overlap ??
									else if (bTransOut)
									{
										// Not sure about this one
										double progress = (psmilMedia->m_tau-(psmilMedia->m_AD-transOutDur)) / transOutDur;

										bTransOut = ProcessTransition(pGraphics, pMediaBitmap, pABitmap, mediaRect, fittedRect, transitionElementOut, transitionOut, transitionFactory, progress);
									}

									delete pABitmap;
								}
							}
						}
					}

					BOOL bTrans = bTransIn || bTransOut;

					if (!bTrans)
					{
						pGraphics->DrawImage(pMediaBitmap,
							fittedRect,
							0, 0, pMediaBitmap->GetWidth(), pMediaBitmap->GetHeight(),
							LDraw::UnitPixel);
					}
				}

			//	pGraphics->TranslateTransform(-subRect.X, -subRect.Y);
			}
		}

		//pGraphics->TranslateTransform(rgnRect.X, rgnRect.Y);

		{
			// Draw child regions

			CArray<CPSMILRegionElement*,CPSMILRegionElement*> regions;
			SortRegions(regions, this);

			for (int i = 0; i < regions.GetSize(); i++)
			{
				regions[i]->Render(pBgBitmap, pGraphics, scaleX, scaleY);
			}
		}

		/*
		pGraphics->DrawImage(pBitmap,
			rgnRect,	// destination rect
			0, 0, pBitmap->GetWidth(), pBitmap->GetHeight(),
			LDraw::UnitPixel);
			*/

		//pGraphics->TranslateTransform(-rgnRect.X, -rgnRect.Y);
	//}
#endif
}

/*
void CPSMILRegionElement::Render2(LDraw::Bitmap* pBitmap, LDraw::Graphics* pGraphics, double scaleX, double scaleY)
{
}
*/

}	// Web
}
