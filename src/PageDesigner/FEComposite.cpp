// FEComposite.cpp : Implementation of CFEComposite
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "FEComposite.h"

/////////////////////////////////////////////////////////////////////////////
// CFEComposite

// IPluginFilter
STDMETHODIMP CFEComposite::GetInPinCount(long* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = 2;
	return S_OK;
}

STDMETHODIMP CFEComposite::GetInPinType(long n, long* pVal)
{
	*pVal = 1;
	return S_OK;
}

STDMETHODIMP CFEComposite::GetResultType(long* pVal)
{
	*pVal = 1;
	return S_OK;
}

STDMETHODIMP CFEComposite::GetName(BSTR* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = SysAllocString(L"Composite");
	return S_OK;
}

STDMETHODIMP CFEComposite::FrameSetup(DWORD filterRecord)
{
	return S_OK;
}

STDMETHODIMP CFEComposite::FrameSetdown(DWORD filterRecord)
{
	return S_OK;
}

STDMETHODIMP CFEComposite::Filter(DWORD dwFilterRecord)
{
	PFILTERRECORD* r = (PFILTERRECORD*)dwFilterRecord;

	Gdiplus::Bitmap* inImage1 = r->inPinImage[0];
	Gdiplus::Bitmap* inImage2 = r->inPinImage[1];

	if (!inImage2)
	{
		MessageBox(NULL, "No inImage2", "Composite Effect", MB_OK);
		return -1;
	}

	//ASSERT(inImage1 && inImage1->data);
	//ASSERT(inImage2 && inImage2->data);

	Gdiplus::Bitmap* outImage = r->outImage;
//	ASSERT(outImage && outImage->data);

	ASSERT(inImage1->GetWidth() == inImage2->GetWidth());
	ASSERT(inImage1->GetWidth() == outImage->GetWidth());
	ASSERT(inImage1->GetHeight() == inImage2->GetHeight());
	ASSERT(inImage1->GetHeight() == outImage->GetHeight());

	Gdiplus::BitmapData indata1;
	inImage1->LockBits(
		&Gdiplus::Rect(0, 0, inImage1->GetWidth(), inImage1->GetHeight()),
		Gdiplus::ImageLockModeRead,
		PixelFormat32bppARGB, &indata1);

	Gdiplus::BitmapData indata2;
	inImage2->LockBits(
		&Gdiplus::Rect(0, 0, inImage2->GetWidth(), inImage2->GetHeight()),
		Gdiplus::ImageLockModeRead,
		PixelFormat32bppARGB, &indata2);

	Gdiplus::BitmapData outdata;
	outImage->LockBits(
		&Gdiplus::Rect(0, 0, outImage->GetWidth(), outImage->GetHeight()),
		Gdiplus::ImageLockModeWrite,
		PixelFormat32bppARGB, &outdata);

	long op = m_op;

	/*
	BSTR opstr;
	element->getAttribute(L"operator", &opstr);
	if (opstr)
	{
		if (!wcscmp(opstr, L"over")) op = 0;
		else if (!wcscmp(opstr, L"in")) op = 1;
		else if (!wcscmp(opstr, L"out")) op = 2;
		else if (!wcscmp(opstr, L"atop")) op = 3;
		else if (!wcscmp(opstr, L"xor")) op = 4;
		else if (!wcscmp(opstr, L"arithmetic")) op = 5;

		SysFreeString(opstr);
	}
	else
	{
		op = 0;	// default is 'over'
	}
	*/

	long k1 = 0, k2 = 0, k3 = 0, k4 = 0;

	/*
	BSTR k;

	element->getAttribute(L"k1", &k);
	if (k)
	{
		k1 = atol(_bstr_t(k));
		SysFreeString(k);
	}

	element->getAttribute(L"k2", &k);
	if (k)
	{
		k2 = atol(_bstr_t(k));
		SysFreeString(k);
	}

	element->getAttribute(L"k3", &k);
	if (k)
	{
		k3 = atol(_bstr_t(k));
		SysFreeString(k);
	}

	element->getAttribute(L"k4", &k);
	if (k)
	{
		k4 = atol(_bstr_t(k));
		SysFreeString(k);
	}
	*/

	int width = outdata.Width;
	int height = outdata.Height;

	for (int y = 0; y < height; y++)
	{
		ARGBPixel* pin1 = (ARGBPixel*)((BYTE*)indata1.Scan0 + indata1.Stride*y);
		ARGBPixel* pin2 = (ARGBPixel*)((BYTE*)indata2.Scan0 + indata2.Stride*y);
		ARGBPixel* out = (ARGBPixel*)((BYTE*)outdata.Scan0 + outdata.Stride*y);

		for (int x = 0; x < width; x++)
		{
			ARGBPixel in1;
			ARGBPixel in2;

			if (FALSE)// Premultiply
			{
				in1.red = (int)pin1->red * pin1->alpha / 255;
				in1.green = (int)pin1->green * pin1->alpha / 255;
				in1.blue = (int)pin1->blue * pin1->alpha / 255;
				in1.alpha = (int)pin1->alpha;

				in2.red = (int)pin2->red * pin2->alpha / 255;
				in2.green = (int)pin2->green * pin2->alpha / 255;
				in2.blue = (int)pin2->blue * pin2->alpha / 255;
				in2.alpha = (int)pin2->alpha;
			}
			else
			{
				in1 = *pin1;
				in2 = *pin2;
			}

			switch (op)
			{
			case 0:	// Over
				{
					//	Porter-Duff Source Over Destination rule. The source is composited over the destination. 
					//	Fs = 1 and Fd = (1-As), thus: 
					
				//	Cd = Cs + Cd*(1-As)
				//	Ad = As + Ad*(1-As)

					out->red = (in1.red) + ((int)in2.red*(255-in1.alpha)/255);
					out->green = (in1.green) + ((int)in2.green*(255-in1.alpha)/255);
					out->blue = (in1.blue) + ((int)in2.blue*(255-in1.alpha)/255);
					out->alpha = (in1.alpha) + ((int)in2.alpha*(255-in1.alpha)/255);
				}
				break;
				
			case 1:	// In
				{
					//	Porter-Duff Source In Destination rule. The part of the source lying inside of the destination replaces the destination. 
					//	Fs = Ad and Fd = 0, thus: 
					
				//	Cd = Cs*Ad
				//	Ad = As*Ad

					out->red = ((int)in1.red * in2.alpha)/255;
					out->green = ((int)in1.green * in2.alpha)/255;
					out->blue = ((int)in1.blue * in2.alpha)/255;
					out->alpha = ((int)in1.alpha * in2.alpha)/255;
				}
				break;
				
			case 2:	// Out
				{
					//	Porter-Duff Source Held Out By Destination rule. The part of the source lying outside of the destination replaces the destination. 
					//	Fs = (1-Ad) and Fd = 0, thus: 
					
				//	Cd = Cs*(1-Ad)
				//	Ad = As*(1-Ad)
				}
				break;
				
			case 3:	// Atop
				{
				}
				break;
				
			case 4:	// Xor
				{
				}
				break;
				
			case 5:	// Arithmetic
				{
					//	result = k1*i1*i2 + k2*i1 + k3*i2 + k4

					long red = k1*in1.red*in2.red + k2*in1.red + k3*in2.red + k4*255;
					long green= k1*in1.green*in2.green + k2*in1.green + k3*in2.green + k4*255;
					long blue = k1*in1.blue*in2.blue + k2*in1.blue + k3*in2.blue + k4*255;

					long alpha = k1*in1.alpha*in2.alpha + k2*in1.alpha + k3*in2.alpha + k4*255;
				//	long alpha = min(in1.alpha, in2.alpha);

					if (red < 0) red = 0;	// Remove this (can't be < 0)
					else if (red > 255) red = 255;

					if (green < 0) green = 0;// Remove this (can't be < 0)
					else if (green > 255) green = 255;

					if (blue < 0) blue = 0;// Remove this (can't be < 0)
					else if (blue > 255) blue = 255;

					if (alpha < 0) alpha = 0;// Remove this (can't be < 0)
					else if (alpha > 255) alpha = 255;

					out->red = red;
					out->green = green;
					out->blue = blue;
					out->alpha = alpha;
				}
				break;

			default:
				ASSERT(0);
			}

		// Un - premultiply destination
			/*
			if (out->alpha > 0)
			{
				out->red = ((int)out->red * 255) / out->alpha;
				out->green = ((int)out->green * 255) / out->alpha;
				out->blue = ((int)out->blue * 255) / out->alpha;
			}
			*/

			pin1++;
			pin2++;
			out++;
		}
	}

	inImage1->UnlockBits(&indata1);
	inImage2->UnlockBits(&indata2);

	outImage->UnlockBits(&outdata);

	return S_OK;
}

STDMETHODIMP CFEComposite::ShowOptions(HWND hParent)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFEComposite::SetPluginFilterClass(IPluginFilterClass *newVal)
{
	m_pluginFilterClass = newVal;
	return S_OK;
}

STDMETHODIMP CFEComposite::GetPluginFilterClass(IPluginFilterClass **pVal)
{
	*pVal = m_pluginFilterClass;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CFEComposite::get_op(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_op;
	return S_OK;
}

STDMETHODIMP CFEComposite::put_op(long newVal)
{
	m_op = newVal;
	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CFEComposite::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	return S_OK;
}

STDMETHODIMP CFEComposite::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	return S_OK;
}
