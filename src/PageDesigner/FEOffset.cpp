// FEOffset.cpp : Implementation of CFEOffset
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "FEOffset.h"

/////////////////////////////////////////////////////////////////////////////
// CFEOffset

// IPluginFilter
STDMETHODIMP CFEOffset::GetInPinCount(long* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = 1;
	return S_OK;
}

STDMETHODIMP CFEOffset::GetInPinType(long n, long* pVal)
{
	*pVal = 1;
	return S_OK;
}

STDMETHODIMP CFEOffset::GetResultType(long* pVal)
{
	*pVal = 1;
	return S_OK;
}

STDMETHODIMP CFEOffset::GetName(BSTR* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = SysAllocString(L"Offset");
	return S_OK;
}

STDMETHODIMP CFEOffset::FrameSetup(DWORD dwFilterRecord)
{
	PFILTERRECORD* r = (PFILTERRECORD*)dwFilterRecord;
	/*
	long dx, dy;
	paramID[0]->GetParamTags((PARAM_POINT_X), &dx, (PARAM_POINT_Y), &dy, (TAG_DONE));
	dx /= (long)r->x_sampling;
	dy /= (long)r->y_sampling;
	*/
	long dx = m_dx;
	long dy = m_dy;

// Resize the output buffer and remap origin
	r->out_newwidth = r->inputWidth + abs(dx);
	r->out_newheight = r->inputHeight + abs(dy);
	if (dx >= 0)
		r->out_x_origin = 0;
	else
		r->out_x_origin = -(dx);

	if (dy >= 0)
		r->out_y_origin = 0;
	else
		r->out_y_origin = -(dy);

	return S_OK;
}

STDMETHODIMP CFEOffset::FrameSetdown(DWORD filterRecord)
{
	return S_OK;
}

STDMETHODIMP CFEOffset::Filter(DWORD dwFilterRecord)
{
	PFILTERRECORD* r = (PFILTERRECORD*)dwFilterRecord;

	Gdiplus::Graphics g(r->outImage);
	g.DrawImage(r->inImage, (float)max(0, m_dx), (float)max(0, m_dy));//0, 0, r->inImage->width, r->inImage->height, r->outImage, max(0, dx), max(0, dy));

	return S_OK;
}

STDMETHODIMP CFEOffset::ShowOptions(HWND hParent)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFEOffset::SetPluginFilterClass(IPluginFilterClass *newVal)
{
	m_pluginFilterClass = newVal;
	return S_OK;
}

STDMETHODIMP CFEOffset::GetPluginFilterClass(IPluginFilterClass **pVal)
{
	*pVal = m_pluginFilterClass;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CFEOffset::get_dx(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_dx;
	return S_OK;
}

STDMETHODIMP CFEOffset::get_dy(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_dy;
	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CFEOffset::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	return S_OK;
}

STDMETHODIMP CFEOffset::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	return S_OK;
}
