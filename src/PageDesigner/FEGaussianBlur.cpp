// FEGaussianBlur.cpp : Implementation of CFEGaussianBlur
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "FEGaussianBlur.h"

long BlurARGB(Gdiplus::BitmapData* inImage, Gdiplus::BitmapData* outImage, RECT* rect, int featherx, int feathery)
{
	int	left = rect->left;
	int	top = rect->top;
	int	right = rect->right;//inImage->width-1;//r->uRect.right;
	int	bottom = rect->bottom;//inImage->height-1;//r->uRect.bottom;

	int	width = inImage->Width;//right-left+1;
	int	height = inImage->Height;//bottom-top+1;

	LPBYTE	tmask = (LPBYTE)GlobalAlloc(0, width*height*4);
	if (!tmask) return -1;

	if (left < 0) left = 0;
	if (top < 0) top = 0;
	if (right > width-1) right = width-1;
	if (bottom > height-1) bottom = height-1;

	int* filterx = new int[featherx*2+1];
	int* filtery = new int[feathery*2+1];

	int i;

	for (i = -featherx; i <= featherx; i++)
	{
		filterx[i+featherx] = featherx-abs(i)+1;
	}

	for (i = -feathery; i <= feathery; i++)
	{
		filtery[i+feathery] = feathery-abs(i)+1;
	}

	int m_alphabytesPerRow = width*4;

// Vertical
	for (int x = left; x <= right; x++)
	{
		LPBYTE	dest = (tmask + m_alphabytesPerRow*top + x*4);
		LPBYTE	src = ((BYTE*)inImage->Scan0 + inImage->Stride*top + x*4);

		for (int y = top; y <= bottom; y++)
		{
			int top2 = y-feathery;
			if (top2 < 0) top2 = 0;
			top2 = top2-y;

			int bottom2 = y+feathery;
			if (bottom2 > height-1) bottom2 = height-1;
			bottom2 = bottom2-y;

			LPBYTE	src2 = (src + top2*inImage->Stride);
	
			DWORD	alpha = 0;
			DWORD	red = 0;
			DWORD	green = 0;
			DWORD	blue = 0;

			int	num = 0;

			top2 += feathery;
			bottom2 += feathery;

			for (int y2 = top2; y2 <= bottom2; y2++)
			{
				int	radius2 = filtery[y2];
				num += radius2;

				alpha += src2[0] *radius2;
				red += src2[1] *radius2;
				green += src2[2] *radius2;
				blue += src2[3] *radius2;

				src2 += inImage->Stride;
			}

			dest[0] = (BYTE)(alpha/num);
			dest[1] = (BYTE)(red/num);
			dest[2] = (BYTE)(green/num);
			dest[3] = (BYTE)(blue/num);

			src += inImage->Stride;
			dest += m_alphabytesPerRow;
		}
	}

// Horizontal
	for (int y = top; y <= bottom; y++)
	{
		LPBYTE	src = (tmask + m_alphabytesPerRow*y + left*4);
		LPBYTE	dest = ((BYTE*)outImage->Scan0 + outImage->Stride*y + left*4);

		for (int x = left; x <= right; x++)
		{
			int	left2 = x-featherx;
			if (left2 < 0) left2 = 0;
			left2 = left2-x;

			int	right2 = x+featherx;
			if (right2 > width-1) right2 = width-1;
			right2 = right2-x;

			LPBYTE	src2 = (src + left2*4);

			DWORD	alpha = 0;
			DWORD	red = 0;
			DWORD	green = 0;
			DWORD	blue = 0;

			DWORD	num = 0;

			for (int x2 = left2; x2 <= right2; x2++)
			{
				int	radius2 = filterx[x2+featherx];
				num += radius2;

				alpha += src2[0] *radius2;
				red += src2[1] *radius2;
				green += src2[2] *radius2;
				blue += src2[3] *radius2;

				src2 += 4;
			}

			dest[0] = (BYTE)(alpha/num);
			dest[1] = (BYTE)(red/num);
			dest[2] = (BYTE)(green/num);
			dest[3] = (BYTE)(blue/num);

			src += 4;
			dest += 4;
		}
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CFEGaussianBlur

// IPluginFilter
STDMETHODIMP CFEGaussianBlur::GetInPinCount(long* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = 1;
	return S_OK;
}

STDMETHODIMP CFEGaussianBlur::GetInPinType(long n, long* pVal)
{
	*pVal = 1;
	return S_OK;
}

STDMETHODIMP CFEGaussianBlur::GetResultType(long* pVal)
{
	*pVal = 1;
	return S_OK;
}

STDMETHODIMP CFEGaussianBlur::GetName(BSTR* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = SysAllocString(L"Gaussian Blur");
	return S_OK;
}

STDMETHODIMP CFEGaussianBlur::FrameSetup(DWORD dwFilterRecord)
{
	PFILTERRECORD* r = (PFILTERRECORD*)dwFilterRecord;

	long blurx = m_blurx;
	long blury = m_blury;

//	paramID[0]->GetParamTags((PARAM_SLIDER_Value), &blurx, (TAG_DONE));
//	paramID[1]->GetParamTags((PARAM_SLIDER_Value), &blury, (TAG_DONE));

//	blurx = blurx / (long)r->x_sampling;
//	blury = blury / (long)r->y_sampling;

// Resize the output buffer and remap origin
//	r->out_newwidth = r->inImage->GetWidth() + blurx*2;
//	r->out_newheight = r->inImage->GetHeight() + blury*2;
	r->out_newwidth = r->inputWidth + blurx*2;
	r->out_newheight = r->inputHeight + blury*2;
	r->out_x_origin = blurx;
	r->out_y_origin = blury;

	return S_OK;
}

STDMETHODIMP CFEGaussianBlur::FrameSetdown(DWORD filterRecord)
{
	return S_OK;
}

STDMETHODIMP CFEGaussianBlur::Filter(DWORD dwFilterRecord)
{
	PFILTERRECORD* r = (PFILTERRECORD*)dwFilterRecord;

	int devx = m_blurx;
	int devy = m_blury;

	//r->inImage->CopyImage(0, 0, r->inImage->width, r->inImage->height, r->outImage, r->out_x_origin, r->out_y_origin);

	{
	Gdiplus::Graphics graphics(r->outImage);
	graphics.DrawImage(r->inImage, r->out_x_origin, r->out_y_origin);
	}

/*
	Gdiplus::BitmapData srcdata;
	r->inImage->LockBits(
		&Gdiplus::Rect(0, 0, r->inImage->GetWidth(), r->inImage->GetHeight()),
		Gdiplus::ImageLockModeRead,
		PixelFormat32bppARGB, &srcdata);
*/
	Gdiplus::BitmapData dstdata;
	r->outImage->LockBits(
		&Gdiplus::Rect(0, 0, r->outImage->GetWidth(), r->outImage->GetHeight()),
		Gdiplus::ImageLockModeWrite,
		PixelFormat32bppARGB, &dstdata);

	BlurARGB(&dstdata, &dstdata, &r->uRect, devx, devy);

//	r->inImage->UnlockBits(&srcdata);
	r->outImage->UnlockBits(&dstdata);

	return S_OK;
}

#include "FEGaussianBlurDlg.h"

STDMETHODIMP CFEGaussianBlur::ShowOptions(HWND hParent)
{
	CFEGaussianBlurDlg dlg;
	dlg.m_blurx = m_blurx;
	dlg.m_blury = m_blury;

	if (dlg.DoModal(hParent) == IDOK)
	{
		setStdDeviation(dlg.m_blurx, dlg.m_blury);
		return S_OK;
	}

	return S_FALSE;
}

STDMETHODIMP CFEGaussianBlur::SetPluginFilterClass(IPluginFilterClass *newVal)
{
	m_pluginFilterClass = newVal;
	return S_OK;
}

STDMETHODIMP CFEGaussianBlur::GetPluginFilterClass(IPluginFilterClass **pVal)
{
	*pVal = m_pluginFilterClass;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CFEGaussianBlur::get_stdDeviationX(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_blurx;
	return S_OK;
}

STDMETHODIMP CFEGaussianBlur::get_stdDeviationY(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_blury;
	return S_OK;
}

STDMETHODIMP CFEGaussianBlur::setStdDeviation(double stdDeviationX, double stdDeviationY)
{
	m_blurx = stdDeviationX;
	m_blury = stdDeviationY;

// TODO fire event ?

	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CFEGaussianBlur::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	node->putAttribute(L"devx", _variant_t(m_blurx));
	node->putAttribute(L"devy", _variant_t(m_blury));

	return S_OK;
}

STDMETHODIMP CFEGaussianBlur::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	_variant_t v;

	node->getAttribute(L"devx", &v);
	m_blurx = v;

	node->getAttribute(L"devy", &v);
	m_blury = v;

	return S_OK;
}
