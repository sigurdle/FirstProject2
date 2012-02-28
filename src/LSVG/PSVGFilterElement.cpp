#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGFilterElement.h"
#include "SVGFilterPrimitiveStandardAttributesImpl.h"
#include "SVGFilterElement.h"

#include "PSVGFEElement.h"

#include <windows.h>
#include <d3d9.h>
#include <D3dx9math.h>

namespace System
{
namespace Web
{

SourceGraphic::SourceGraphic(PSVGElement* pPElement)
{
	m_pPElement = pPElement;
}

SourceAlpha::SourceAlpha(SourceGraphic* pSourceGraphic)
{
	m_pSourceGraphic = pSourceGraphic;
}

PSVGFilterElement::PSVGFilterElement(SVGFilterElement* element) : PSVGElement(element)
{
	m_pReferencingElement = NULL;

	m_pSourceGraphic = NULL;
	m_pSourceAlpha = NULL;
	m_pBackgroundImage = NULL;
	m_pBackgroundAlpha = NULL;
}

/*
CPSVGElement::RenderSourceGraphic(
LDraw::Bitmap* pSourceGraphic = new LDraw::Bitmap(scaledWidth, scaledHeight);
{
	LDraw::Graphics graphics(pSourceGraphic);
		
	graphics.ScaleTransform(scaleX, scaleY);
	graphics.TranslateTransform(-sourceBounds.X, -sourceBounds.Y);

	pReferencingElement->Render2((DWORD)pSourceGraphic, (DWORD)&graphics, scaleX, scaleY);
}
*/

// virtual
void PSVGFilterElement::RecalculateParentBounds()
{
	ASSERT(0);
#if 0
	CUPtrList list;
	UPOSITION pos;

// Make a copy of the list first
	pos = m_referencingElements.GetHeadPosition();
	while (pos)
	{
		PSVGElement* pElement = (PSVGElement*)m_referencingElements.GetNext(pos);
		list.AddTail(pElement);
	}

	pos = list.GetHeadPosition();
	while (pos)
	{
		PSVGElement* pElement = (PSVGElement*)list.GetNext(pos);

	// TODO, have a ReferenceChanged(Element) ??
		pElement->CalculateBoundsAndChildren();
		pElement->RecalculateParentBounds();
	}

	// No need to process up to parent
	//PSVGElement::RecalculateParentBounds();
#endif
}

gm::RectD PSVGFilterElement::CalculateFilterRegion(PSVGElement* pReferencingElement)
{
	ASSERT(pReferencingElement != NULL);

	SVGFilterElement* psvgElement = static_cast<SVGFilterElement*>(m_pNode);

	ISVGLength* xLength = psvgElement->get_x()->get_animVal();
	ISVGLength* yLength = psvgElement->get_y()->get_animVal();
	ISVGLength* widthLength = psvgElement->get_width()->get_animVal();
	ISVGLength* heightLength = psvgElement->get_height()->get_animVal();

	gm::RectD filterRegion;

	if (psvgElement->filterUnits_attr().m_animated->m_animVal->m_value == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
	{
		gm::RectD rect = pReferencingElement->m_bounds;

		if (xLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
			filterRegion.X = rect.X + (xLength->get_valueInSpecifiedUnits() * rect.Width/100);
		else
			filterRegion.X = rect.X + (xLength->get_value() * rect.Width);

		if (yLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
			filterRegion.Y = rect.Y + (yLength->get_valueInSpecifiedUnits() * rect.Height/100);
		else
			filterRegion.Y = rect.Y + (yLength->get_value() * rect.Height);

		if (widthLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
			filterRegion.Width = (widthLength->get_valueInSpecifiedUnits() * rect.Width/100);
		else
			filterRegion.Width = (widthLength->get_value() * rect.Width);

		if (heightLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
			filterRegion.Height = (heightLength->get_valueInSpecifiedUnits() * rect.Height/100);
		else
			filterRegion.Height = (heightLength->get_value() * rect.Height);
	}
	else	// SVG_UNIT_TYPE_USERSPACEONUSE
	{
		gm::RectD rect = pReferencingElement->GetViewportElement()->GetViewBox();

		if (xLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
			filterRegion.X = rect.X + (xLength->get_valueInSpecifiedUnits() * rect.Width/100);
		else
			filterRegion.X = xLength->get_value();

		if (yLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
			filterRegion.Y = rect.Y + (yLength->get_valueInSpecifiedUnits() * rect.Height/100);
		else
			filterRegion.Y = yLength->get_value();

		if (widthLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
			filterRegion.Width = (widthLength->get_valueInSpecifiedUnits() * rect.Width/100);
		else
			filterRegion.Width = widthLength->get_value();

		if (heightLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
			filterRegion.Height = (heightLength->get_valueInSpecifiedUnits() * rect.Height/100);
		else
			filterRegion.Height = heightLength->get_value();
	}

//	m_filterRegion = filterRegion;
	return filterRegion;
}

Gui::CEffect* PSVGFilterElement::GetInEffect(Gui::RenderContext* renderContext, StringIn in, int i)
{
	Gui::CEffect* pEffect = NULL;

	ASSERT(0);
#if 0

	if (in == L"SourceGraphic")
	{
#if 0
		if (m_pSourceGraphic->m_outImage == NULL)
		{
			LDraw::RectD sourceBounds = m_pReferencingElement->m_filterRect;

			m_pSourceGraphic->m_outImage = m_pReferencingElement->GetBitmap(pO, m_scaledWidth, m_scaledHeight, m_scaleX, m_scaleY);
			/*
			if (m_pSourceGraphic->m_outImage->m_texture == NULL)
			{
				//m_pSourceGraphic->m_outImage->m_texture = pO->m_device->CreateTexture2D(1, m_pSourceGraphic->m_outImage->GetWidth(), m_pSourceGraphic->m_outImage->GetHeight(), 
				m_pSourceGraphic->m_outImage->m_texture = pO->m_device->CreateTexture2D(0, GL_RGBA, m_bitmap->GetWidth(), m_bitmap->GetHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, m_pSourceGraphic->m_outImage->GetPointer());
			}
			*/

			//	LDraw::Texture texture = device->CreateTexture2D(0, GL_RGBA, m_scaledWidth, m_scaledHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
		//	Direct3D9_I* d3d9

#if 0
			UI::Graphics graphics(new LDraw::GraphicsO(m_pSourceGraphic->m_outImage));

			graphics.ScaleTransform(float(m_scaleX), float(m_scaleY));
			graphics.TranslateTransform(float(-sourceBounds.X), float(-sourceBounds.Y));

			CHTMRenderContext rcontext;
			rcontext.m_clip = LDraw::RectF(0, 0, m_pReferencingElement->m_filterRect.Width, m_pReferencingElement->m_filterRect.Height);

			m_pReferencingElement->Render4(&rcontext, m_pSourceGraphic->m_outImage, &graphics, m_scaleX, m_scaleY, false, false);
#endif
		}
#endif

		pEffect = m_pSourceGraphic;
	}
	else if (in == L"SourceAlpha")
	{
#if 0
		if (m_pSourceAlpha->m_outImage == NULL)
		{
		// We need the SourceGraphic first
			CEffect* pSourceGraphic = GetInEffect(pO, WSTR("SourceGraphic"), 0);

			if (pSourceGraphic->m_outImage)
			{
				LDraw::BitmapData sourceGraphicData;
				if (pSourceGraphic->m_outImage->LockBits(
					&LDraw::RectI(0, 0, pSourceGraphic->m_outImage->GetWidth(), pSourceGraphic->m_outImage->GetHeight()),
					LDraw::ImageLockModeRead/*,
					PixelFormat32bppPARGB*/, &sourceGraphicData) == 0)
				{
					m_pSourceAlpha->m_outImage = new LDraw::Bitmap(pSourceGraphic->m_outImage->GetWidth(), pSourceGraphic->m_outImage->GetHeight(), LDraw::PixelFormat_t::RGBAP_32);
					if (m_pSourceAlpha->m_outImage)
					{
						LDraw::BitmapData sourceAlphaData;
						if (m_pSourceAlpha->m_outImage->LockBits(
							&LDraw::RectI(0, 0, pSourceGraphic->m_outImage->GetWidth(), pSourceGraphic->m_outImage->GetHeight()),
							LDraw::ImageLockModeWrite,
							/*PixelFormat32bppPARGB,*/ &sourceAlphaData) == 0)
						{
						// Copy the alpha only from sourceGraphic
							for (UINT y = 0; y < sourceAlphaData.Height; y++)
							{
								LDraw::PixelRGBAP_32* s = (LDraw::PixelRGBAP_32*)((uint8*)sourceGraphicData.Scan0 + sourceGraphicData.Stride*y);
								LDraw::PixelRGBAP_32* d = (LDraw::PixelRGBAP_32*)((uint8*)sourceAlphaData.Scan0 + sourceAlphaData.Stride*y);

								for (UINT x = 0; x < sourceAlphaData.Width; x++)
								{
									d->r = 0;
									d->g = 0;
									d->b = 0;
									d->a = s->a;

									s++;
									d++;
								}
							}

							m_pSourceAlpha->m_outImage->UnlockBits(&sourceAlphaData);
						}
					}

					pSourceGraphic->m_outImage->UnlockBits(&sourceGraphicData);
				}
			}
		}
#endif
		pEffect = m_pSourceAlpha;
	}
	else if (in == L"BackgroundImage")
	{
		if (m_pBackgroundImage == NULL)
		{
		}

		pEffect = m_pBackgroundImage;
	}
	else if (in == L"BackgroundAlpha")
	{
		if (m_pSourceAlpha->m_outImage == NULL)
		{
		// We need the BackgroundImage first
			Gui::CEffect* pBackgroundImage = GetInEffect(renderContext, WSTR("BackgroundImage"), 0);

			if (pBackgroundImage->m_outImage)
			{
				Graphics::BitmapData sourceGraphicData;
				pBackgroundImage->m_outImage->LockBits(
					&gm::RectI(0, 0, pBackgroundImage->m_outImage->GetWidth(), pBackgroundImage->m_outImage->GetHeight()),
					LDraw::ImageLockModeRead/*,
					PixelFormat32bppPARGB*/, &sourceGraphicData);

					m_pBackgroundAlpha->m_outImage = new Graphics::Bitmap(pBackgroundImage->m_outImage->GetWidth(), pBackgroundImage->m_outImage->GetHeight(), LDraw::PixelFormat_t::RGBAP_32);
				if (m_pBackgroundAlpha->m_outImage)
				{
					Graphics::BitmapData sourceAlphaData;
					m_pBackgroundAlpha->m_outImage->LockBits(
						&gm::RectI(0, 0, pBackgroundImage->m_outImage->GetWidth(), pBackgroundImage->m_outImage->GetHeight()),
						LDraw::ImageLockModeWrite/*,
						PixelFormat32bppPARGB*/, &sourceAlphaData);

				// Copy the alpha only from sourceGraphic
					for (UINT y = 0; y < sourceAlphaData.Height; y++)
					{
						LDraw::PixelRGBAP_32* s = (LDraw::PixelRGBAP_32*)((uint8*)sourceGraphicData.Scan0 + sourceGraphicData.Stride*y);
						LDraw::PixelRGBAP_32* d = (LDraw::PixelRGBAP_32*)((uint8*)sourceAlphaData.Scan0 + sourceAlphaData.Stride*y);

						for (UINT x = 0; x < sourceAlphaData.Width; x++)
						{
							d->r = 0;
							d->g = 0;
							d->b = 0;
							d->a = s->a;

							s++;
							d++;
						}
					}

					m_pBackgroundAlpha->m_outImage->UnlockBits(&sourceAlphaData);
				}

				pBackgroundImage->m_outImage->UnlockBits(&sourceGraphicData);
			}
		}

		pEffect = m_pBackgroundAlpha;
	}
	else
	{
		Gui::CEffect* inputElement = NULL;

		for (int j = i-1; j >= 0; j--)
		{
			ISVGFilterPrimitiveStandardAttributes* svgfeElement = dynamic_cast<ISVGFilterPrimitiveStandardAttributes*>(m_effectElements[j]->m_pNode);
			String result = svgfeElement->get_result()->get_animVal();

			if (result)
			{
				if (result == in)
				{
					inputElement = m_effectElements[j]->m_effect;
					break;
				}
			}
		}

		pEffect = inputElement;
	}
#endif

	return pEffect;
}

// Returns the result image
SVGFilterCommand* PSVGFilterElement::ProcessEffects(Gui::RenderContext* renderContext, PSVGElement* pReferencingElement, double scaleX, double scaleY)
{
	m_pReferencingElement = pReferencingElement;
	m_scaleX = scaleX;
	m_scaleY = scaleY;

	gm::RectD sourceBounds2 = pReferencingElement->m_expandedBBox;
	gm::RectD sourceBounds = pReferencingElement->m_filterRect;

	int sourceWidth = (int)ceil(sourceBounds.Width);
	int sourceHeight = (int)ceil(sourceBounds.Height);

	if (sourceWidth <= 0 || sourceHeight <= 0) return NULL;

	m_scaledWidth = (int)ceil(sourceBounds.Width * scaleX);
	m_scaledHeight = (int)ceil(sourceBounds.Height * scaleY);

//	RectD filterRegion = sourceBounds;	// ???

	m_pSourceGraphic = new SourceGraphic(pReferencingElement);
	m_pSourceGraphic->m_subRegion.X = sourceBounds2.X -sourceBounds.X;
	m_pSourceGraphic->m_subRegion.Y = sourceBounds2.Y -sourceBounds.Y;
	m_pSourceGraphic->m_subRegion.Width = sourceBounds2.Width;
	m_pSourceGraphic->m_subRegion.Height = sourceBounds2.Height;
	m_pSourceGraphic->m_scaledWidth = m_scaledWidth;
	m_pSourceGraphic->m_scaledHeight = m_scaledHeight;

	m_pSourceAlpha = new SourceAlpha(m_pSourceGraphic);
	m_pSourceAlpha->m_subRegion.X = sourceBounds2.X -sourceBounds.X;
	m_pSourceAlpha->m_subRegion.Y = sourceBounds2.Y -sourceBounds.Y;
	m_pSourceAlpha->m_subRegion.Width = sourceBounds2.Width;
	m_pSourceAlpha->m_subRegion.Height = sourceBounds2.Height;
	m_pSourceAlpha->m_scaledWidth = m_scaledWidth;
	m_pSourceAlpha->m_scaledHeight = m_scaledHeight;
	/*
	m_pBackgroundImage = new CEffect();
	m_pBackgroundAlpha = new CEffect();
	*/

// TODO. Fill
	{
	}

// TODO. Stroke
	{
	}

	ASSERT(m_effectElements.GetSize() == 0);
	for (unsigned int i = 0; i < m_rchildList.size(); i++)
	{
		PNode* node = m_childList[i];

		PSVGFEElement* feElement = dynamic_cast<PSVGFEElement*>(node);
		if (feElement)
		{
			m_effectElements.push_back(feElement);
		}
	}

	Gui::CEffect* resultEffect = m_pSourceGraphic;	// Default to this if no filter primitives
//	CEffect* resultEffect = m_pSourceAlpha;	// Default to this if no filter primitives

// Process all filter primitives
	for (int i = 0; i < m_effectElements.GetSize(); i++)
	{
		PSVGFEElement* pPElement = m_effectElements[i];

		/*
		if (pEffect->m_outImage)
		{
			delete pEffect->m_outImage;
			pEffect->m_outImage = NULL;
		}
		*/

		SVGElement* pElement = dynamic_cast<SVGElement*>(pPElement->m_pNode);

		int inpincount = 0;

		String tagName = pElement->get_localName();
		if (tagName == NULL) tagName = pElement->get_tagName();

		Gui::CEffect* pEffect = NULL;

#if 1
		if (tagName == L"feMerge")
		{
			SVGMergeEffect* pMergeEffect = new SVGMergeEffect;
			pEffect = pMergeEffect;

		//	pEffect->m_outImage = new LDraw::Bitmap(m_scaledWidth, m_scaledHeight, LDraw::PixelFormat_t::RGBAP_32);
		//	if (pEffect->m_outImage)
			{
			//	UI::Graphics out(new LDraw::GraphicsO(pEffect->m_outImage));

				Node* n = pElement->get_firstChild();
				while (n)
				{
					SVGFEMergeNodeElement* pMergeNode = dynamic_cast<SVGFEMergeNodeElement*>(n);
					if (pMergeNode)
					{
					//	System::StringW* in = pMergeNode->m_in1->m_animated->m_animVal->m_value->m_value;
						String in = pMergeNode->get_in1()->get_animVal();//m_in1->m_animated->m_animVal->m_value->m_value;

						Gui::CEffect* pInEffect = GetInEffect(renderContext, in, i);
						if (pInEffect/* && pInEffect->m_outImage*/)
						{
							pMergeEffect->m_nodes.push_back(pInEffect);
						//	out.DrawImage(pInEffect->m_outImage, (float)0, (float)0);
						}
					}

					n = n->get_nextSibling();
				}
			}
		//	else
		//		break;
		}
		else
#endif
		{
			inpincount = pPElement->GetInCount();

#if 0
			if (*tagName == L"feGaussianBlur" ||
				*tagName == L"feOffset" ||
				*tagName == L"feMorphology" ||
				*tagName == L"feColorMatrix" ||
				*tagName == L"feConvolveMatrix" ||
				*tagName == L"feComponentTransfer" ||
				*tagName == L"feSpecularLighting" ||
				*tagName == L"feDiffuseLighting")
			{
				inpincount = 1;
			}
			else if (*tagName == L"feBlend" ||
						*tagName == L"feComposite" ||
						*tagName == L"feDisplacementMap")
			{
				inpincount = 2;
			}
			else if (*tagName == L"feFlood")
			{
				inpincount = 0;
			}
			else if (*tagName == L"feImage" ||
						*tagName == L"feTurbulence")
			{
				inpincount = 0;
			}
			else	// Unsupported
				break;//ASSERT(0);
#endif

			Gui::CEffect* pInEffect[6];
			int hadInput = 0;

			for (int pin = 0; pin < inpincount; pin++)
			{
				String instr;
				if (pin == 0)
					instr = WSTR("in");
				else
					instr = WSTR("in2");

				pInEffect[pin] = NULL;

				String in = pElement->getAttribute(instr);
				if (in != NULL)
				{
					pInEffect[pin] = GetInEffect(renderContext, in, i);

				}
				else	// Not specified
				{
				// Use result image of Previous primitive
					if (i > 0)
					{
						pInEffect[pin] = resultEffect;//m_effects[i-1];
					//	pInEffect[pin] = m_effects[i-1];
					}
					else
					{
						// First filter primitive uses "SourceGraphic" by default
						pInEffect[pin] = GetInEffect(renderContext, WSTR("SourceGraphic"), 0);
					}
				}

				if (pInEffect[pin])
				{
					hadInput++;
				}
			}

			if (inpincount == hadInput)
			{
				//RectD subRegionRect;
			// First set as default

				gm::RectF subRegion;

				if (inpincount == 0)
				{
					subRegion.X = sourceBounds.X;
					subRegion.Y = sourceBounds.Y;
					subRegion.Width = sourceBounds.Width;
					subRegion.Height = sourceBounds.Height;
				}
				else
				{
				// x, y, width and height default to the union (i.e., tightest fitting bounding box) of the subregions defined for all referenced nodes

					subRegion = gm::RectF(999999, 999999, -99999, -99999);

					for (int i = 0; i < inpincount; i++)
					{
						if (i == 0)
							subRegion = pInEffect[i]->m_subRegion;
						else
							gm::RectF::Union(subRegion, subRegion, pInEffect[i]->m_subRegion);

							/*
						if (pInEffect[i]->m_pFEElement)
						{
							LDraw::RectD::Union(subRegion, subRegion, pInEffect[i]->m_subRegion);
						}
						else
						{
							subRegion = sourceBounds;
							break;
						}
						*/
					}
				}

			// Then override with specified values
				pPElement->CalculatePrimitiveSubRegion(this, pReferencingElement, /*pEffect->m_*/subRegion);

			//	pEffect->m_subRegion = subRegionRect;

				/*
				if (true)
				{
					pEffect->m_outImage = pInEffect[0]->m_outImage;
				}
				else
				*/
				{
					gm::RectF uRect;
					pEffect = pPElement->Filter(renderContext, pInEffect, this, uRect, scaleX, scaleY);
					pPElement->m_effect = pEffect;

					pEffect->m_subRegion.X = (sourceBounds2.X - sourceBounds.X);
					pEffect->m_subRegion.Y = (sourceBounds2.Y - sourceBounds.Y);
					pEffect->m_subRegion.Width = sourceBounds2.Width;
					pEffect->m_subRegion.Height = sourceBounds2.Height;

					pEffect->m_scaledWidth = m_scaledWidth;
					pEffect->m_scaledHeight = m_scaledHeight;

#if 0
					pEffect->m_outImage = new LDraw::Bitmap(m_scaledWidth, m_scaledHeight, LDraw::PixelFormat_t::RGBAP_32);
					if (pEffect->m_outImage)
					{
						LDraw::RectD::Intersect(pEffect->m_subRegion, pEffect->m_subRegion, sourceBounds);

						LDraw::RectF uRect;
						uRect.X = (pEffect->m_subRegion.X - sourceBounds.X)*scaleX;
						uRect.Y = (pEffect->m_subRegion.Y - sourceBounds.Y)*scaleY;
						uRect.Width = pEffect->m_subRegion.Width*scaleX;
						uRect.Height = pEffect->m_subRegion.Height*scaleY;
						//uRect.right = m_scaledWidth-1;
						//uRect.bottom = m_scaledHeight-1;

						CEffect* pEffect = pEffect->m_pFEElement->Filter(pO, pInEffect, pEffect->m_outImage, uRect, scaleX, scaleY);
						pEffect->m_scaledWidth = m_scaledWidth;
						pEffect->m_scaledHeight = m_scaledHeight;
					//	pEffect->m_outImage = pCommand->m_bitmap;
					}
					else // Couldn't allocate output image
					{
						break;
					}
#endif
				}
			}
		}

	// The result image is the output of the last image processed
		resultEffect = pEffect;//->m_outImage;
	}

#if 0
// Free temporary output images
	for (int i = 0; i < m_effects.GetSize(); i++)
	{
		CEffect* pEffect = m_effects[i];

		if (pEffect->m_outImage == resultImage)
		{
			// Don't delete the bitmap
			pEffect->m_outImage = NULL;
		}

		delete pEffect;
	}
#endif
	m_effectElements.RemoveAll();
#if 0
	if (m_pSourceGraphic->m_outImage == resultImage)
	{
		// Don't delete the bitmap
		m_pSourceGraphic->m_outImage = NULL;
	}
	delete m_pSourceGraphic;
#endif
	m_pSourceGraphic = NULL;
#if 0
	if (m_pSourceAlpha->m_outImage == resultImage)
	{
		// Don't delete the bitmap
		m_pSourceAlpha->m_outImage = NULL;
	}
	delete m_pSourceAlpha;
#endif
	m_pSourceAlpha = NULL;

#if 0
	if (m_pBackgroundImage->m_outImage == resultImage)
	{
		// Don't delete the bitmap
		m_pBackgroundImage->m_outImage = NULL;
	}
	delete m_pBackgroundImage;
	m_pBackgroundImage = NULL;

	if (m_pBackgroundAlpha->m_outImage == resultImage)
	{
		// Don't delete the bitmap
		m_pBackgroundAlpha->m_outImage = NULL;
	}
	delete m_pBackgroundAlpha;
#endif
	m_pBackgroundAlpha = NULL;

	SVGFilterCommand* pCommand = new SVGFilterCommand;
	pCommand->m_effect = resultEffect;
//	LDraw::Bitmap* resultImage = NULL;

	return pCommand;
	//return resultImage;
}

//using namespace LDraw;

void SVGFilterCommand::Render(Gui::RenderContext* renderContext)
{
//	matrix4f modelView;
//	pGraphics->m_device->GetFloatv(GL_MODELVIEW_MATRIX, (float*)modelView);

//	matrix4f projection;
//	pGraphics->m_device->GetFloatv(GL_PROJECTION_MATRIX, (float*)projection);

	ASSERT(0);
#if 0
	m_effect->Render(renderContext, m_destRect, renderContext->m_modelView, renderContext->m_projection);
#endif
}

#if 0
void CEffect::DrawBitmap(LDraw::GraphicsO* pGraphics, RectF destRect)
{
	float x = destRect.X;
	float y = destRect.Y;
	float width = destRect.Width;
	float height = destRect.Height;

	VERTEX_XYZ_T2 vertices[4] =
	{
		{vector3f(x, y, 0), vector2f(0, 0)},
		{vector3f(x+width, y, 0), vector2f(1, 0)},
		{vector3f(x, y+height, 0), vector2f(0, 1)},
		{vector3f(x+width, y+height, 0), vector2f(1, 1)},
	};

	HRESULT hr;

	pGraphics->m_device->SetVertexDeclaration(pGraphics->m_res->m_vertexDeclaration1);
	pGraphics->m_device->SetPrimitiveTopology(GL_TRIANGLE_STRIP);

	UINT nPasses;
	hr = pGraphics->m_res->m_d3d9_effect->Begin(&nPasses, 0);
	ASSERT(SUCCEEDED(hr));
	for (UINT nPass = 0; nPass < nPasses; ++nPass)
	{
		hr = pGraphics->m_res->m_d3d9_effect->BeginPass(nPass);
		ASSERT(SUCCEEDED(hr));

		pGraphics->m_device->DrawUP(4, vertices, sizeof(VERTEX_XYZ_T2));

#if 0
		if (indexBuffer != NULL)
			m_device->DrawIndexed(0, count-1, count/*, GL_UNSIGNED_SHORT, m_indexOffset*/);
		else
			m_device->Draw(0, count);
#endif
		hr = pGraphics->m_res->m_d3d9_effect->EndPass();
		ASSERT(SUCCEEDED(hr));
	}
	hr = pGraphics->m_res->m_d3d9_effect->End();
	ASSERT(SUCCEEDED(hr));
}
#endif

/*
void CEffect::RenderOut(LDraw::GraphicsO* pGraphics, LDraw::RectF destRect)
{
	Render(pGraphics, destRect);
}
*/

void Premultiply(D3DLOCKED_RECT locked_rect, void* srcData, int srcStride, int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		uint8* src = (uint8*)srcData + y * srcStride;
		uint8* dst = (uint8*)locked_rect.pBits + y*locked_rect.Pitch;

		for (int x = 0; x < width; x++)
		{
			dst[0] = src[0] * src[3] / 255;
			dst[1] = src[1] * src[3] / 255;
			dst[2] = src[2] * src[3] / 255;
			dst[3] = src[3];	// Alpha

			src += 4;
			dst += 4;
		}
	}
}

void ToAlpha(D3DLOCKED_RECT locked_rect, void* srcData, int srcStride, int srcComponents, int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		uint8* src = (uint8*)srcData + y * srcStride;
		uint8* dst = (uint8*)locked_rect.pBits + y*locked_rect.Pitch;

		if (srcComponents == 3)
		{
			for (int x = 0; x < width; x++)
			{
				dst[0] = 0;
				dst[1] = 0;
				dst[2] = 0;
				dst[3] = 255;	// Alpha

				src += 3;
				dst += 4;
			}
		}
		else if (srcComponents == 4)
		{
			for (int x = 0; x < width; x++)
			{
				dst[0] = 0;
				dst[1] = 0;
				dst[2] = 0;
				dst[3] = src[3];	// Alpha

				/*
				// Should be premultiplied
				ASSERT(src[0] <= src[3]);
				ASSERT(src[1] <= src[3]);
				ASSERT(src[2] <= src[3]);

				if (dst[3] > 0 && dst[3] < 255)
				{
				//	MessageBeep(-1);
				}
				*/

				src += 4;
				dst += 4;
			}
		}
	}
}

void SourceGraphic::RenderOutput(Gui::RenderContext* renderContext)
{
	m_outImage = m_pPElement->GetBitmap(renderContext, m_subRegion.Width, m_subRegion.Height, 1, 1);
#if 0
	if (m_outImage->m_texture == NULL)
	{
		m_outImage->m_texture = pGraphics->m_device->CreateTexture2D(0, GL_RGBA, m_outImage->GetWidth(), m_outImage->GetHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, m_outImage->GetPointer());
	}
#endif
}

void SourceGraphic::Render(Gui::RenderContext* renderContext, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection)
{
	ASSERT(0);
#if 0
	if (m_outImage == NULL)
	{
		RenderOutput(renderContext);
	}

	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewVariable, (D3DXMATRIX*)&modelView);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_projectionVariable, (D3DXMATRIX*)&projection);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewProjectionVariable, (D3DXMATRIX*)(float*)(projection * modelView));

	pGraphics->m_res->m_d3d9_effect->SetTexture(pGraphics->m_res->m_d3d9_texture0Variable, m_outImage->m_texture.u.d3d);

	D3DXHANDLE technique = pGraphics->m_res->m_d3d9_effect->GetTechniqueByName("RenderLinearGradient");

	pGraphics->m_res->m_d3d9_effect->SetTechnique(technique);

	LDraw::RectF rc;
	rc.X = destRect.X + m_subRegion.X;
	rc.Y = destRect.Y + m_subRegion.Y;
	rc.Width = m_subRegion.Width;
	rc.Height = m_subRegion.Height;

	DrawBitmap(pGraphics, rc);
#endif
}

void SourceAlpha::RenderOutput(Gui::RenderContext* renderContext)
{
	ASSERT(0);
#if 0
	if (m_pSourceGraphic->m_outImage == NULL)
	{
		m_pSourceGraphic->RenderOutput(pGraphics);
	}

	LDraw::Bitmap* pBitmap = m_pSourceGraphic->m_outImage;

	LDraw::Direct3D9_I* pD3D9 = dynamic_cast<LDraw::Direct3D9_I*>(pGraphics->m_device);

	void* srcData;

	int width = pBitmap->GetWidth();
	int height = pBitmap->GetHeight();

	IDirect3DTexture9* pTexture = NULL;
	pD3D9->m_d3dDevice->CreateTexture(width, height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pTexture, NULL);

	IDirect3DSurface9* pSurface;
	pTexture->GetSurfaceLevel(0, &pSurface);

//	IDirect3DSurface9* pSourceSurface = NULL;

	D3DLOCKED_RECT locked_rect;
	pSurface->LockRect(&locked_rect, NULL, 0/*D3DLOCK_DISCARD*/);

	if (pBitmap->GetPointer())	// Source bitmap is available directly in cpu system memory
	{
		srcData = pBitmap->GetPointer();

		ToAlpha(locked_rect, srcData, width*3, 3, width, height);
	}
	else
	{
		// Source texture is a rendertarget texture

		// Create a temporary surface in sysmem to copy the render target data to
		IDirect3DSurface9* pSysMemSurface = NULL;
		pD3D9->m_d3dDevice->CreateOffscreenPlainSurface(width, height, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &pSysMemSurface, NULL);

		// Copy rendertarget texture data to systemmem surface
		IDirect3DSurface9* pSourceSurface = NULL;
		pBitmap->m_texture.u.d3d->GetSurfaceLevel(0, &pSourceSurface);
		pD3D9->m_d3dDevice->GetRenderTargetData(pSourceSurface, pSysMemSurface);
		pSourceSurface->Release();

		D3DLOCKED_RECT sysmem_locked_rect;
		pSysMemSurface->LockRect(&sysmem_locked_rect, NULL, 0);

		ToAlpha(locked_rect, sysmem_locked_rect.pBits, sysmem_locked_rect.Pitch, 4, width, height);

		pSysMemSurface->UnlockRect();
		pSysMemSurface->Release();
	}

	pSurface->UnlockRect();

	m_outImage = new LDraw::Bitmap(width, height, 0, LDraw::PixelFormat_t::RGBAP_32, NULL);
	m_outImage->m_texture = Texture(NULL, pTexture);
#endif
}

void SourceAlpha::Render(Gui::RenderContext* renderContext, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection)
{
	ASSERT(0);
#if 0
	if (m_outImage == NULL)
	{
		RenderOutput(pGraphics);
	}

	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewVariable, (D3DXMATRIX*)&modelView);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_projectionVariable, (D3DXMATRIX*)&projection);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewProjectionVariable, (D3DXMATRIX*)(float*)(projection * modelView));

	pGraphics->m_res->m_d3d9_effect->SetTexture(pGraphics->m_res->m_d3d9_texture0Variable, m_outImage->m_texture.u.d3d);

	D3DXHANDLE technique = pGraphics->m_res->m_d3d9_effect->GetTechniqueByName("RenderLinearGradient");

	pGraphics->m_res->m_d3d9_effect->SetTechnique(technique);

	destRect.X += m_subRegion.X;
	destRect.Y += m_subRegion.Y;
	DrawBitmap(pGraphics, destRect);
#endif
}

#if 0
void CEffect::RenderOutput(LDraw::GraphicsO* pGraphics)
{
	LDraw::Direct3D9_I* pD3D9 = dynamic_cast<LDraw::Direct3D9_I*>(pGraphics->m_device);

	LDraw::matrix4f modelView = LDraw::matrix4f::getIdentity();
	LDraw::matrix4f projection = LDraw::matrix4f::getOrtho(0, m_scaledWidth, m_scaledHeight, 0, -1/*zNear*/, 1/*zFar*/);

	HRESULT hr;

//	D3DMULTISAMPLE_TYPE MultiSample = D3DMULTISAMPLE_4_SAMPLES;
//	D3DMULTISAMPLE_TYPE MultiSample = D3DMULTISAMPLE_NONMASKABLE;
	D3DMULTISAMPLE_TYPE MultiSample = D3DMULTISAMPLE_NONE;
	int quality = 1;

	IDirect3DTexture9* pTexture = NULL;
	IDirect3DSurface9* pTextureSurface = NULL;
	IDirect3DSurface9* pMultiSampleSurface = NULL;
	IDirect3DSurface9* pRenderTargetSurface = NULL;

	hr = pD3D9->m_d3dDevice->CreateTexture(m_scaledWidth, m_scaledHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTexture, NULL);
	ASSERT(pTexture);
	pTexture->GetSurfaceLevel(0, &pTextureSurface);

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

	m_outImage = new LDraw::Bitmap(m_scaledWidth, m_scaledHeight, 0, LDraw::PixelFormat_t::RGBAP_32, NULL);
	m_outImage->m_texture = Texture(pD3D9, pTexture);

	IDirect3DSurface9* pOldRenderTarget;
	pD3D9->m_d3dDevice->GetRenderTarget(0, &pOldRenderTarget);

	pD3D9->m_d3dDevice->SetRenderTarget(0, pRenderTargetSurface);
	pD3D9->m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0x00000000, 0, 0);
	hr = pD3D9->m_d3dDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	ASSERT(SUCCEEDED(hr));

	LDraw::RectF destRect(0, 0, m_scaledWidth, m_scaledHeight);
	Render(pGraphics, destRect, modelView, projection);

	pD3D9->m_d3dDevice->SetRenderTarget(0, pOldRenderTarget);

	if (pMultiSampleSurface)
	{
		HRESULT hr;
		hr = pD3D9->m_d3dDevice->StretchRect(pMultiSampleSurface, NULL, pTextureSurface, NULL, D3DTEXF_POINT);
		ASSERT(SUCCEEDED(hr));

		pMultiSampleSurface->Release();
	}

	pTextureSurface->Release();
}

// virtual
void CEffect::RenderOutputNormalMap(LDraw::GraphicsO* pGraphics)
{
	if (m_outNormalMap)
	{
		return;
	}

// Surface normal is calculated using the Sobel gradient 3x3 filter:



#define I(x,y) (((LDraw::PixelRGBAP_32*)((uint8*)locked_rect.pBits + locked_rect.Pitch*(y) + (x)*4))->a/255.0)

#define Nx(x,y) (-surfaceScale * 1/4* \
						(( I(x+1,y-1) + 2*I(x+1,y) + I(x+1,y+1)) \
						- I(x-1,y-1) - 2*I(x-1,y) - I(x-1,y+1)))

#define Ny(x,y) (-surfaceScale * 1/4* \
						(( I(x-1,y+1) + 2*I(x,y+1) + I(x+1,y+1)) \
						 - I(x-1,y-1) - 2*I(x,y-1) - I(x+1,y-1)))

#define Nz(x,y) 1.0

	if (m_outImage == NULL)
	{
		RenderOutput(pGraphics);
	}

	LDraw::Direct3D9_I* pD3D9 = dynamic_cast<LDraw::Direct3D9_I*>(pGraphics->m_device);

	int width = m_outImage->GetWidth();
	int height = m_outImage->GetHeight();

	IDirect3DSurface9* pTempSurface = NULL;
	pD3D9->m_d3dDevice->CreateOffscreenPlainSurface(width, height, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &pTempSurface, NULL);

	IDirect3DSurface9* pRenderTargetSurface;
	m_outImage->m_texture.u.d3d->GetSurfaceLevel(0, &pRenderTargetSurface);
	pD3D9->m_d3dDevice->GetRenderTargetData(pRenderTargetSurface, pTempSurface);
	pRenderTargetSurface->Release();

	D3DLOCKED_RECT locked_rect;
	pTempSurface->LockRect(&locked_rect, NULL, 0);

	IDirect3DTexture9* pTexture = NULL;
	pD3D9->m_d3dDevice->CreateTexture(width, height, 1, 0/*D3DUSAGE_*/, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pTexture, NULL);

	float surfaceScale = 5;	// TODO

	D3DLOCKED_RECT locked_rect2;
	pTexture->LockRect(0, &locked_rect2, NULL, 0);

	for (int y = 1; y < height-1; y++)
	{
		uint8* src = (uint8*)locked_rect.pBits + y*locked_rect.Pitch;
		uint8* dst = (uint8*)locked_rect2.pBits + y*locked_rect2.Pitch;

		for (int x = 1; x < width-1; x++)
		{
			LDraw::vector3f N(Nx(x, y), Ny(x, y), Nz(x, y));
			N.normalize();

			/*
			ASSERT(N[0] >= 0);
			ASSERT(N[1] >= 0);
			ASSERT(N[2] >= 0);
			*/

			dst[0] = (N[0]*127.5)+127.5;	// -1..1
			dst[1] = (N[1]*127.5)+127.5;	// -1..1
			dst[2] = (N[2]*255);			//  0..1

			dst[3] = src[3];	// Alpha

			src += 4;
			dst += 4;
		}
	}

	pTexture->UnlockRect(0);

	pTempSurface->UnlockRect();
	pTempSurface->Release();

	m_outNormalMap = new LDraw::Bitmap(m_scaledWidth, m_scaledHeight, 0, LDraw::PixelFormat_t::RGBAP_32, NULL);
	m_outNormalMap->m_texture = Texture(pD3D9, pTexture);
}
#endif

unsigned int SVGOffsetEffect::GetInputCount()
{
	return 1;
}

Gui::IEffect* SVGOffsetEffect::GetInput(unsigned int index)
{
	if (index != 0)
	{
		throw std::exception("Index out of bounds");
	}

	return m_inEffect;
}

void SVGOffsetEffect::SetInput(unsigned int index, Gui::IEffect* input)
{
	if (index != 0)
	{
		throw std::exception("Index out of bounds");
	}

	m_inEffect = input;
}

void SVGOffsetEffect::Render(Gui::RenderContext* renderContext, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection)
{
	ASSERT(0);
#if 0
	if (m_inEffect->GetOutputBitmap() == NULL)
	{
		m_inEffect->RenderOutput(pGraphics);
	}

	pGraphics->m_device->SetVertexDeclaration(pGraphics->m_res->m_vertexDeclaration1);

	pGraphics->m_device->SetPrimitiveTopology(GL_TRIANGLE_STRIP);

	/*
	matrix4f modelView;
	pGraphics->m_device->GetFloatv(GL_MODELVIEW_MATRIX, (float*)modelView);

	matrix4f projection;
	pGraphics->m_device->GetFloatv(GL_PROJECTION_MATRIX, (float*)projection);
	*/

	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewVariable, (D3DXMATRIX*)&modelView);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_projectionVariable, (D3DXMATRIX*)&projection);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewProjectionVariable, (D3DXMATRIX*)(float*)(projection * modelView));

	pGraphics->m_res->m_d3d9_effect->SetTexture(pGraphics->m_res->m_d3d9_texture0Variable, m_inEffect->GetOutputBitmap()->m_texture.u.d3d);

	pGraphics->m_res->m_d3d9_effect->SetTechnique(m_technique);

	destRect.X += m_dx;
	destRect.Y += m_dy;

	DrawBitmap(pGraphics, destRect);
#endif
}

unsigned int SVGMergeEffect::GetInputCount()
{
	return m_nodes.size();
}

Gui::IEffect* SVGMergeEffect::GetInput(unsigned int index)
{
	if (index >= m_nodes.size())
	{
		throw new ArgumentOutOfRangeException();
	}

	return m_nodes[index];
}

void SVGMergeEffect::SetInput(unsigned int index, Gui::IEffect* input)
{
	if (index >= m_nodes.size())
	{
		throw std::exception("Index out of bounds");
	}

	m_nodes[index] = input;
}

void SVGMergeEffect::Render(Gui::RenderContext* renderContext, LDraw::RectF destRect, const LDraw::matrix4f& modelView, const LDraw::matrix4f& projection)
{
	for (unsigned int i = 0; i < m_nodes.size(); i++)
	{
		Gui::IEffect* pEffect = m_nodes[i];

	//	pEffect->RenderOutput(pGraphics);
		pEffect->Render(renderContext, destRect, modelView, projection);
	}
}

/*
unsigned int SVGGaussianBlurEffect::GetInputCount()
{
	return 1;
}

Gui::IEffect* SVGGaussianBlurEffect::GetInput(unsigned int index)
{
	if (index != 0)
	{
		throw std::exception("Index out of bounds");
	}

	return m_inEffect;
}

void SVGGaussianBlurEffect::SetInput(unsigned int index, Gui::IEffect* input)
{
	if (index != 0)
	{
		throw std::exception("Index out of bounds");
	}

	m_inEffect = input;
}
*/

#if 0
void SVGGaussianBlurEffect::Render(Gui::RenderContext* renderContext, LDraw::RectF destRect, const LDraw::matrix4f& modelView, const LDraw::matrix4f& projection)
{
#if 0
	if (m_inEffect->GetOutputBitmap() == NULL)
	{
		m_inEffect->RenderOutput(pGraphics);
	}

	D3DXHANDLE hTexelKernel = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "TexelKernel");
	ASSERT(hTexelKernel);

	D3DXHANDLE hKernelSize = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "KernelSize");
	ASSERT(hKernelSize);

	D3DXHANDLE hBlurWeights = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "BlurWeights");
	ASSERT(hBlurWeights);

//	pGraphics->m_device->SetVertexDeclaration(pGraphics->m_vertexDeclaration1);

	/*
	m_stdDeviationX = 6;
	m_stdDeviationY = 6;
	*/

	unsigned int cKernelX = m_stdDeviationX*3+1;
	unsigned int cKernelY = m_stdDeviationY*3+1;

	D3DXVECTOR4* TexelKernel = (D3DXVECTOR4*)alloca(sizeof(D3DXVECTOR4) * max(cKernelX, cKernelY));
	float* BlurWeights = (float*)alloca(sizeof(float) * max(cKernelX, cKernelY));

//	pGraphics->m_device->SetPrimitiveTopology(GL_TRIANGLE_STRIP);

	LDraw::Direct3D9_I* pD3D9 = dynamic_cast<LDraw::Direct3D9_I*>(pGraphics->m_device);

	IDirect3DSurface9* pOldRenderTarget;
	pD3D9->m_d3dDevice->GetRenderTarget(0, &pOldRenderTarget);

	// GaussianBlur Horizontal
	IDirect3DTexture9* tempTexture = NULL;
	pD3D9->m_d3dDevice->CreateTexture(m_scaledWidth, m_scaledHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &tempTexture, NULL);

	IDirect3DSurface9* tempSurface = NULL;
	tempTexture->GetSurfaceLevel(0, &tempSurface);
	pD3D9->m_d3dDevice->SetRenderTarget(0, tempSurface);

//	LDraw::matrix3f textureMatrix = LDraw::matrix3f::getTranslate(40.0, 30.0);
//	LDraw::matrix3f textureMatrix = LDraw::matrix3f::getTranslate(0.5, 0.5);
//	LDraw::matrix3f textureMatrix = LDraw::matrix3f::getRotate(45);
//	pGraphics->m_d3d9_effect->SetMatrix(pGraphics->m_d3d9_textureMatrix0Variable, (D3DXMATRIX*)(float*)LDraw::matrix4f(textureMatrix));

	LDraw::matrix4f textureMatrix =
	//	LDraw::matrix4f::getScale(m_subRegion.Width / m_scaledWidth, m_subRegion.Height / m_scaledHeight, 1) *
		LDraw::matrix4f::getScale(m_scaledWidth / m_subRegion.Width, m_scaledHeight / m_subRegion.Height, 1) *
		LDraw::matrix4f::getTranslate(-m_subRegion.X / m_scaledWidth, -m_subRegion.Y / m_scaledHeight, 0);
	//LDraw::matrix4f textureMatrix = LDraw::matrix4f::getTranslate(-0.5, -0.5, 0);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_textureMatrix0Variable, (D3DXMATRIX*)&textureMatrix);

	{
		LDraw::matrix4f modelView = LDraw::matrix4f::getIdentity();
		LDraw::matrix4f projection = LDraw::matrix4f::getOrtho(0, m_scaledWidth, m_scaledHeight, 0, -1/*zNear*/, 1/*zFar*/);
		pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewVariable, (D3DXMATRIX*)&modelView);
		pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_projectionVariable, (D3DXMATRIX*)&projection);
		pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewProjectionVariable, (D3DXMATRIX*)(float*)(projection * modelView));
	}

#if 0
	pD3D9->SetMatrixMode(GL_PROJECTION);
	pD3D9->PushMatrix();
	pD3D9->SetTransform(LDraw::matrix4f::getOrtho(0, m_bitmap->GetWidth(), m_bitmap->GetHeight(), 0, -1/*zNear*/, 1/*zFar*/));

	pD3D9->SetMatrixMode(GL_MODELVIEW);
	pD3D9->PushMatrix();
	pD3D9->IdentityTransform();
#endif

	float sum = 0;

	for (unsigned int i = 0; i < cKernelX; i++)
	{
		int pixelX = i - cKernelX/2;

		TexelKernel[i].x = (float)pixelX / m_inEffect->GetOutputBitmap()->GetWidth();
		TexelKernel[i].y = 0;

		BlurWeights[i] = exp(-(pixelX*pixelX) / (m_stdDeviationX*m_stdDeviationX)) / sqrt(2 * M_PI * m_stdDeviationX*m_stdDeviationX);

		sum += BlurWeights[i];
	}

	for (unsigned int i = 0; i < cKernelX; i++)
	{
		BlurWeights[i] /= sum;
	}

	pGraphics->m_res->m_d3d9_effect->SetInt(hKernelSize, cKernelX);
	pGraphics->m_res->m_d3d9_effect->SetVectorArray(hTexelKernel, TexelKernel, cKernelX);
	pGraphics->m_res->m_d3d9_effect->SetFloatArray(hBlurWeights, BlurWeights, cKernelX);

	pGraphics->m_res->m_d3d9_effect->SetTexture(pGraphics->m_res->m_d3d9_texture0Variable, m_inEffect->GetOutputBitmap()->m_texture.u.d3d);
	pGraphics->m_res->m_d3d9_effect->SetTechnique(m_techniqueH);
	DrawBitmap(pGraphics, RectF(0, 0, m_scaledWidth, m_scaledHeight));

	/*
	pD3D9->SetMatrixMode(GL_PROJECTION);
	pD3D9->PopMatrix();
	pD3D9->SetMatrixMode(GL_MODELVIEW);
	pD3D9->PopMatrix();
	*/

	// GaussianBlur Vertical
	pD3D9->m_d3dDevice->SetRenderTarget(0, pOldRenderTarget);
	tempSurface->Release();

	/*
	matrix4f modelView;
	pGraphics->m_device->GetFloatv(GL_MODELVIEW_MATRIX, (float*)modelView);

	matrix4f projection;
	pGraphics->m_device->GetFloatv(GL_PROJECTION_MATRIX, (float*)projection);
	*/

	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewVariable, (D3DXMATRIX*)&modelView);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_projectionVariable, (D3DXMATRIX*)&projection);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewProjectionVariable, (D3DXMATRIX*)(float*)(projection * modelView));

	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_textureMatrix0Variable, (D3DXMATRIX*)&LDraw::matrix4f::getIdentity());

	sum = 0;

	for (unsigned int i = 0; i < cKernelY; i++)
	{
		int pixelY = i - cKernelY/2;

		TexelKernel[i].x = 0;
		TexelKernel[i].y = (float)pixelY / m_inEffect->GetOutputBitmap()->GetHeight();

		BlurWeights[i] = exp(-(pixelY*pixelY) / (m_stdDeviationY*m_stdDeviationY)) / sqrt(2 * M_PI * m_stdDeviationY*m_stdDeviationY);

		sum += BlurWeights[i];
	}

	for (unsigned int i = 0; i < cKernelY; i++)
	{
		BlurWeights[i] /= sum;
	}

	/*
	for (unsigned int i = 0; i < cKernelY/2; i++)
	{
		BlurWeights[i] = exp(-pixelY/ (cKernelY)) / sqrt(2* M_PI*cKernelY)
	}
	*/

	pGraphics->m_res->m_d3d9_effect->SetInt(hKernelSize, cKernelY);
	pGraphics->m_res->m_d3d9_effect->SetVectorArray(hTexelKernel, TexelKernel, cKernelY);
	pGraphics->m_res->m_d3d9_effect->SetFloatArray(hBlurWeights, BlurWeights, cKernelY);

	pGraphics->m_res->m_d3d9_effect->SetTexture(pGraphics->m_res->m_d3d9_texture0Variable, tempTexture);
	pGraphics->m_res->m_d3d9_effect->SetTechnique(m_techniqueV);
//	destRect.X += m_subRegion.X;
//	destRect.Y += m_subRegion.Y;
	DrawBitmap(pGraphics, destRect);

	tempTexture->Release();
#endif
}
#endif

ID3D10EffectTechnique* SVGColorMatrixEffect::s_technique;

unsigned int SVGColorMatrixEffect::GetInputCount()
{
	return 1;
}

//virtual
Gui::IEffect* SVGColorMatrixEffect::GetInput(unsigned int index)
{
	if (index != 0)
	{
		throw new ArgumentOutOfRangeException();
	}
	return m_inEffect;
}

//virtual
void SVGColorMatrixEffect::SetInput(unsigned int index, Gui::IEffect* input)
{
	if (index != 0)
	{
		throw new ArgumentOutOfRangeException();
	}
	m_inEffect = input;
}

//virtual
void SVGColorMatrixEffect::Render(Gui::RenderContext* renderContext, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection)
{
	if (s_technique == NULL)
	{
		s_technique = GL::Direct10::s.m_effect->GetTechniqueByName("RenderTextureColorTransform");
	}
#if 0
	/*
	if (m_inBitmap->m_texture == NULL)
	{
		m_inBitmap->m_texture = pGraphics->m_device->CreateTexture2D(0, GL_RGBA, m_bitmap->GetWidth(), m_bitmap->GetHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, m_bitmap->GetPointer());
	}
	*/

	D3DXHANDLE m_colorMatrixVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "colorMatrix");
	D3DXHANDLE m_colorTranslateVariable = pGraphics->m_res->m_d3d9_effect->GetParameterByName(NULL, "colorTranslate");

//	pGraphics->m_device->SetVertexDeclaration(pGraphics->m_vertexDeclaration1);

//	pGraphics->m_d3d9_effect->SetMatrix(pGraphics->m_d3d9_textureMatrix0Variable, (D3DXMATRIX*)(float*)matrix4f::getIdentity());

	LDraw::matrix4f colorMatrix(
		m_colorMatrix.m[0][0], m_colorMatrix.m[0][1], m_colorMatrix.m[0][2], m_colorMatrix.m[0][3],
		m_colorMatrix.m[1][0], m_colorMatrix.m[1][1], m_colorMatrix.m[1][2], m_colorMatrix.m[1][3],
		m_colorMatrix.m[2][0], m_colorMatrix.m[2][1], m_colorMatrix.m[2][2], m_colorMatrix.m[2][3],
		m_colorMatrix.m[3][0], m_colorMatrix.m[3][1], m_colorMatrix.m[3][2], m_colorMatrix.m[3][3]
		);

	pGraphics->m_res->m_d3d9_effect->SetMatrix(m_colorMatrixVariable, (D3DXMATRIX*)&colorMatrix);
	pGraphics->m_res->m_d3d9_effect->SetVector(m_colorTranslateVariable, (D3DXVECTOR4*)&m_colorMatrix.m[4]);

//	pGraphics->m_device->SetPrimitiveTopology(GL_TRIANGLE_STRIP);

	/*
	matrix4f modelView;
	pGraphics->m_device->GetFloatv(GL_MODELVIEW_MATRIX, (float*)modelView);

	matrix4f projection;
	pGraphics->m_device->GetFloatv(GL_PROJECTION_MATRIX, (float*)projection);
	*/

	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewVariable, (D3DXMATRIX*)&modelView);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_projectionVariable, (D3DXMATRIX*)&projection);
	pGraphics->m_res->m_d3d9_effect->SetMatrix(pGraphics->m_res->m_d3d9_modelViewProjectionVariable, (D3DXMATRIX*)(float*)(projection * modelView));

	pGraphics->m_res->m_d3d9_effect->SetTexture(pGraphics->m_res->m_d3d9_texture0Variable, m_inEffect->GetOutputBitmap()->m_texture.u.d3d);
#endif

	GL::Direct10::s.m_texture0Variable->SetResource(m_inEffect->GetOutputBitmap()->m_d3d10_shaderResourceView);

	LDraw::matrix4f modelView2 =
		LDraw::matrix4f::getTranslate(destRect.X, destRect.Y, 0) *
		LDraw::matrix4f::getScale(destRect.Width, destRect.Height, 1);

	GL::Direct10::s.m_modelViewProjectionVariable->SetMatrix((float*)(modelView * modelView2));

	GL::Direct10::s.m_textureMatrix0Variable->SetMatrix((float*)&LDraw::matrix4f::getIdentity());

	GL::Direct10::s.m_colorTransformVariable->SetMatrix((float*)m_colorTransform);
	GL::Direct10::s.m_colorTranslateVariable->SetFloatVector((float*)m_colorTranslate);

	D3D10_TECHNIQUE_DESC techDesc;
	s_technique->GetDesc(&techDesc);

	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		s_technique->GetPassByIndex(p)->Apply(0);

		renderContext->GetRT()->m_d3d10->m_device->Draw(
			4, // VertexCount
			0 // StartVertexLocation
			);
	}

//	GL::Direct10::s.Render(rt, m_inEffect->GetOutputBitmap()->m_d3d10_textureView, destRect);

	/*
	D3D10_TECHNIQUE_DESC techDesc;
	s_eff.m_techniqueV->GetDesc(&techDesc);

	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		s_eff.m_techniqueV->GetPassByIndex(p)->Apply(0);

		rt->m_device->Draw(
			4, // VertexCount
			0 // StartVertexLocation
			);
	}
	*/
}

}	// Web
}
