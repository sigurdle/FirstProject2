#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGFEConvolveMatrixElement.h"
#include "SVGFEConvolveMatrixElement.h"

namespace System
{
namespace Web
{

PSVGFEConvolveMatrixElement::PSVGFEConvolveMatrixElement(SVGFEConvolveMatrixElement* element) : PSVGFEElement(element)
{
}

// virtual
int PSVGFEConvolveMatrixElement::GetInCount()
{
	return 1;
}

//virtual
Gui::CEffect* PSVGFEConvolveMatrixElement::Filter(Gui::RenderContext* renderContext, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY)
{
	ASSERT(0);
#if 0
	CLSVGFEConvolveMatrixElement* psvgElement = static_cast<CLSVGFEConvolveMatrixElement*>(m_pNode);

	bool preserveAlpha = psvgElement->m_preserveAlpha->m_animated->m_animVal->m_value->m_value;
	CComObject<CLSVGNumberList>* kernelMatrix = psvgElement->m_kernelMatrix->m_animated->m_animVal->m_value.m_object;

	long orderX = psvgElement->m_order->m_animated->m_animVal->m_value->m_value[0];
	long orderY = psvgElement->m_order->m_animated->m_animVal->m_value->m_value[1];

	long targetX;
	if (psvgElement->m_targetX->m_specified)
		targetX = psvgElement->m_targetX->m_animated->m_animVal->m_value->m_value;
	else
		targetX = orderX/2;

	long targetY;
	if (psvgElement->m_targetY->m_specified)
		targetY = psvgElement->m_targetY->m_animated->m_animVal->m_value->m_value;
	else
		targetY = orderY/2;

	double bias = psvgElement->m_bias->m_animated->m_animVal->m_value;

	double divisor;
	if (psvgElement->m_divisor->m_specified)
	{
		divisor = psvgElement->m_divisor->m_animated->m_animVal->m_value;
		if (divisor == 0) return -1;	// Error
	}
	else
	{
/*
	The default value is the sum of all values in kernelMatrix, with the
	exception that if the sum is zero, then the divisor is set to 1
*/
		divisor = 0;
		for (int i = 0; i < kernelMatrix->m_items.GetSize(); i++)
		{
			divisor += kernelMatrix->m_items[i]->m_value;
		}
		if (divisor == 0)
			divisor = 1;
	}

	LDraw::BitmapData indata;
	inPinImage[0]->m_outImage->LockBits(
		&LDraw::Rect(0, 0, inPinImage[0]->m_outImage->GetWidth(), inPinImage[0]->m_outImage->GetHeight()),
		LDraw::ImageLockModeRead,
		(preserveAlpha)? PixelFormat32bppARGB: PixelFormat32bppPARGB, &indata);

	LDraw::BitmapData dstdata;
	outImage->LockBits(
		&LDraw::Rect(0, 0, outImage->GetWidth(), outImage->GetHeight()),
		LDraw::ImageLockModeWrite,
		(preserveAlpha)? PixelFormat32bppARGB: PixelFormat32bppPARGB, &dstdata);

	int width = dstdata.Width;
	int height = dstdata.Height;

	for (int y = targetY; y < height-targetY; y++)
	{
		BYTE* out = (BYTE*)((BYTE*)dstdata.Scan0 + dstdata.Stride*y + targetX*4);
		BYTE* in2 = (BYTE*)((BYTE*)dstdata.Scan0 + dstdata.Stride*y + targetX*4);

		for (int x = targetX; x < width-targetX; x++)
		{
			double result[4] = {0,0,0,0};

			BYTE* in = (BYTE*)((BYTE*)indata.Scan0 + indata.Stride*(y-targetY) + (x-targetX)*4);

			for (int i = orderY-1; i >= 0; i--)
			{
				BYTE* in2 = in;

				for (int j = orderX-1; j >= 0; j--)
				{
				//	double value = kernelMatrix->m_items[orderY*(orderY-i-1) + (orderX-j-1)]->m_value;
					double value = kernelMatrix->m_items[orderX*i + j]->m_value;

					result[0] += (in2[0]/255.0)*value;
					result[1] += (in2[1]/255.0)*value;
					result[2] += (in2[2]/255.0)*value;
					if (!preserveAlpha) result[3] += (in2[3]/255)*value;

					in2 += 4;
				}

				in += indata.Stride;
			}

			long v0 = (result[0] / divisor + bias)*255;
			long v1 = (result[1] / divisor + bias)*255;
			long v2 = (result[2] / divisor + bias)*255;

			if (v0 < 0) v0 = 0; else if (v0 > 255) v0 = 255;
			if (v1 < 0) v1 = 0; else if (v1 > 255) v1 = 255;
			if (v2 < 0) v2 = 0; else if (v2 > 255) v2 = 255;

			out[0] = v0;
			out[1] = v1;
			out[2] = v2;

			if (!preserveAlpha)
			{
				long v3 = (result[3] / divisor + bias)*255;
				if (v3 < 0) v3 = 0; else if (v3 > 255) v3 = 255;
				out[3] = v3;
			}
			else
				out[3] = in2[3];

			out += 4;
			in2 += 4;
		}
	}

	inPinImage[0]->m_outImage->UnlockBits(&indata);
	outImage->UnlockBits(&dstdata);
#endif
	return 0;
}

}	// Web
}
