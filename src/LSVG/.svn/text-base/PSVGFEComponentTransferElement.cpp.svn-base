#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGFEComponentTransferElement.h"
#include "SVGFEComponentTransferElement.h"

#include "SVGComponentTransferFunctionElementImpl.h"

namespace System
{
namespace Web
{

PSVGFEComponentTransferElement::PSVGFEComponentTransferElement(SVGFEComponentTransferElement* element) : PSVGFEElement(element)
{
}

// virtual
int PSVGFEComponentTransferElement::GetInCount()
{
	return 1;
}

//virtual
Gui::CEffect* PSVGFEComponentTransferElement::Filter(Gui::RenderContext* renderContext, Gui::CEffect* inImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY)
{
	ASSERT(0);
#if 0
	CLSVGFEComponentTransferElement* psvgElement = static_cast<CLSVGFEComponentTransferElement*>(m_pNode);

	LDraw::BitmapData indata;
	if (inImage[0]->m_outImage->LockBits(
		&LDraw::Rect(0, 0, inImage[0]->m_outImage->GetWidth(), inImage[0]->m_outImage->GetHeight()),
		LDraw::ImageLockModeRead,
		PixelFormat32bppARGB, &indata) != 0)
	{
		ASSERT(0);
		return -1;
	}

	LDraw::BitmapData outdata;
	if (outImage->LockBits(
		&LDraw::Rect(0, 0, outImage->GetWidth(), outImage->GetHeight()),
		LDraw::ImageLockModeWrite,
		PixelFormat32bppPARGB, &outdata) != 0)
	{
		inImage[0]->m_outImage->UnlockBits(&indata);

		ASSERT(0);
		return -1;
	}

	WCHAR* feFuncName[] =
	{
		L"feFuncB",
		L"feFuncG",
		L"feFuncR",
		L"feFuncA",
	};

	int width = outdata.Width;
	int height = outdata.Height;

	for (int ch = 0; ch < 4; ch++)
	{
		LSVGComponentTransferType type;
		double amplitude;
		double exponent;
		double offset;
		double slope;
		double intercept;

		CPElementBase* pFuncElement = GetElementByTagNameNS(L"http://www.w3.org/2000/svg", feFuncName[ch], FALSE);
		if (pFuncElement)
		{
			CComQIPtr<CLSVGComponentTransferFunctionElementImplImpl> psvgfuncElement = pFuncElement->m_pNode;

			type = psvgfuncElement->m_type->m_animated->m_animVal->m_value;
			amplitude = psvgfuncElement->m_amplitude->m_animated->m_animVal->m_value;
			exponent = psvgfuncElement->m_exponent->m_animated->m_animVal->m_value;
			offset = psvgfuncElement->m_offset->m_animated->m_animVal->m_value;
			slope = psvgfuncElement->m_slope->m_animated->m_animVal->m_value;
			intercept = psvgfuncElement->m_intercept->m_animated->m_animVal->m_value;
		}
		else
		{
			type = SVG_FECOMPONENTTRANSFER_TYPE_IDENTITY;
		}

		for (int y = 0; y < height; y++)
		{
			BYTE* in = (BYTE*)((BYTE*)indata.Scan0 + indata.Stride*y + ch);
			BYTE* out = (BYTE*)((BYTE*)outdata.Scan0 + outdata.Stride*y + ch);

			for (int x = 0; x < width; x++)
			{
				switch (type)
				{
				case SVG_FECOMPONENTTRANSFER_TYPE_IDENTITY:
					{
					//	C' = C

						*out = *in;
					}
					break;

				case SVG_FECOMPONENTTRANSFER_TYPE_TABLE:
					{
					}
					break;

				case SVG_FECOMPONENTTRANSFER_TYPE_DISCRETE:
					{
					}
					break;

				case SVG_FECOMPONENTTRANSFER_TYPE_LINEAR:
					{
					// C' = slope * C + intercept

						*out = slope * (*in) + intercept;
					}
					break;

				case SVG_FECOMPONENTTRANSFER_TYPE_GAMMA:
					{
					// C' = amplitude * pow(C, exponent) + offset

						*out = amplitude * pow((*in), exponent)/255 + offset;
					}
					break;

				default:
					ASSERT(0);
				}

				in += 4;
				out += 4;
			}
		}
	}

	inImage[0]->m_outImage->UnlockBits(&indata);
	outImage->UnlockBits(&outdata);
#endif
	return 0;
}

}	// Web
}	// System
