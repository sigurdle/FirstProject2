// PDStroke.cpp : Implementation of CPDObjectStroke
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "PDObjectStroke.h"
#include "PDBrush.h"
#include "PDObjectShape.h"

Gdiplus::Brush* GetGdiBrush(IPDBrush* brush, PDBrushType brushType = BRUSH_NONE);

int GetSepNumberArray(CUString str, CArray <double,double>& values, WCHAR sep)
{
	int len = str.GetLength();
	LPCTSTR p = str;
	int i = 0;

	while (i < len)
	{
		CUString str_value;
		while ((i < len) && (p[i] != sep) && (p[i] != ' '))
		{
			str_value += CUString(p[i]);
			i++;
		}

		while (i < len && p[i] == ' ') i++;	// Skip spaces

		if (p[i] == sep) i++;

		while (i < len && p[i] == ' ') i++;	// Skip spaces

		str_value.TrimLeft();
		str_value.TrimRight();

		values.Add(atof(str_value));
	}

	return values.GetSize();
}

/////////////////////////////////////////////////////////////////////////////
// CPDObjectStroke

int CPDObjectStroke::FinalConstruct()
{
	CPDObjectWithBrushImpl<CPDObjectStroke, IPDObjectStroke>::FinalConstruct();
	CPDObjectWithAppearanceImpl<CPDObjectStroke, IPDObjectWithAppearance>::FinalConstruct();

	return S_OK;
}

void CPDObjectStroke::FinalRelease()
{
	CPDObjectWithBrushImpl<CPDObjectStroke, IPDObjectStroke>::FinalRelease();
	CPDObjectWithAppearanceImpl<CPDObjectStroke, IPDObjectWithAppearance>::FinalRelease();
}

Gdiplus::Pen* CPDObjectStroke::GetGdipPen()
{
	Gdiplus::Brush* pBrush = GetGdiBrush(m_brush);
	if (pBrush)
	{
		Gdiplus::Pen* pPen = new Gdiplus::Pen(pBrush, (float)m_strokeWeight);
		if (pPen)
		{
			Gdiplus::LineCap lineCap = (m_strokeCap == 0)? Gdiplus::LineCapFlat: (m_strokeCap == 1)? Gdiplus::LineCapRound: Gdiplus::LineCapSquare;
			Gdiplus::DashCap dashCap = (m_strokeCap == 0)? Gdiplus::DashCapFlat: (m_strokeCap == 1)? Gdiplus::DashCapRound: Gdiplus::DashCapTriangle;
			pPen->SetLineCap(lineCap, lineCap, dashCap);

			pPen->SetLineJoin((m_strokeJoin == 0)? Gdiplus::LineJoinMiter: (m_strokeJoin == 1)? Gdiplus::LineJoinRound: Gdiplus::LineJoinBevel);

			pPen->SetMiterLimit(m_strokeMiterLimit);

			return pPen;
		}
	}
	return NULL;
}
/*
STDMETHODIMP CPDObjectStroke::get_strokeWeight(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_strokeWeight;
	return S_OK;
}

STDMETHODIMP CPDObjectStroke::put_strokeWeight(double newVal)
{
	m_strokeWeight = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

STDMETHODIMP CPDObjectStroke::get_strokeCap(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_strokeCap;
	return S_OK;
}

STDMETHODIMP CPDObjectStroke::put_strokeCap(long newVal)
{
	m_strokeCap = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

STDMETHODIMP CPDObjectStroke::get_strokeJoin(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_strokeJoin;
	return S_OK;
}

STDMETHODIMP CPDObjectStroke::put_strokeJoin(long newVal)
{
	m_strokeJoin = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

STDMETHODIMP CPDObjectStroke::get_strokeMiterLimit(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_strokeMiterLimit;
	return S_OK;
}

STDMETHODIMP CPDObjectStroke::put_strokeMiterLimit(double newVal)
{
	m_strokeMiterLimit = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

STDMETHODIMP CPDObjectStroke::setDashedValue(long index, double value)
{
	m_dashValues[index] = value;

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDObjectStroke::getDashedValue(long index, double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_dashValues[index];
	return S_OK;
}

STDMETHODIMP CPDObjectStroke::get_dashedCount(long *pVal)
{
	if (pVal == NULL) return E_POINTER;

	for (int i = 0; i < 6; i++)
	{
		if (m_dashValues[i] <= 0)
			break;
	}

	*pVal = i;

	return S_OK;
}
*/

//virtual
void CPDObjectStroke::CalculateBounds()
{
	CComQIPtr<IPDObjectFrame> frame = m_parent;
	CPDObjectFrame* pParentFrame = static_cast<CPDObjectFrame*>(frame.p);

	if (pParentFrame)
	{
		if (pParentFrame->m_gdppath == NULL)
		{
			pParentFrame->m_gdppath = new Gdiplus::GraphicsPath(Gdiplus::FillModeWinding);
			pParentFrame->m_path->RenderToGraphicsPath(pParentFrame->m_gdppath);
		}

		ATLASSERT(pParentFrame->m_gdppath);

		m_bounds = pParentFrame->m_bounds;

		Gdiplus::Pen* pPen = GetGdipPen();
		if (pPen)
		{
			Gdiplus::RectF gdiRect;
			pParentFrame->m_gdppath->GetBounds(&gdiRect, NULL, pPen);

			m_filterRect.X = gdiRect.X;
			m_filterRect.Y = gdiRect.Y;
			m_filterRect.Width = gdiRect.Width;
			m_filterRect.Height = gdiRect.Height;

			m_appearance->SetupChildrenLayers(this);

			m_expandedBBox = m_appearance->m_expandedRect;

			delete pPen;
		}
		else
		{
			m_filterRect.X = 999999;
			m_filterRect.Y = 999999;
			m_filterRect.Width = -999999;
			m_filterRect.Height = -999999;

			m_expandedBBox.X = 999999;
			m_expandedBBox.Y = 999999;
			m_expandedBBox.Width = -999999;
			m_expandedBBox.Height = -999999;
		}
	}

	CalculateScale(m_expandedBBox, m_matrix);
}

STDMETHODIMP CPDObjectStroke::Render2(/*[in]*/ DWORD dwBitmap, DWORD dwGraphics, double scaleX, double scaleY)
{
	Gdiplus::Graphics& graphics = *(Gdiplus::Graphics*)dwGraphics;
//	CPDObjectFrame* pParentFrame = (CPDObjectFrame*)m_parent;

	Gdiplus::Bitmap* pBitmap = (Gdiplus::Bitmap*)dwBitmap;

//	Gdiplus::Graphics graphics(pBitmap);
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality/*pGraphics->GetSmoothingMode()*/);

//	graphics.ScaleTransform(scaleX, scaleY);
//	graphics.TranslateTransform(-m_filterRect.X, -m_filterRect.Y);

	CComQIPtr<IPDObjectFrame> frame = m_parent;
	CPDObjectFrame* pParentFrame = static_cast<CPDObjectFrame*>(frame.p);

//	Gdiplus::Graphics* pGraphics = (Gdiplus::Graphics*)dwGraphics;

//	Gdiplus::Matrix oldmat;
//	pGraphics->GetTransform(&oldmat);

//	pGraphics->ScaleTransform(scaleX, scaleY, Gdiplus::MatrixOrderAppend);

//	Gdiplus::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
//	pGraphics->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);

	Gdiplus::Pen* pPen = GetGdipPen();
	if (pPen)
	{
		long dashCount;
		get_dashedCount(&dashCount);
		if (dashCount > 0)
		{
			float dashArray[6] =
			{
				(float)m_dashValues[0],
				(float)m_dashValues[1],
				(float)m_dashValues[2],
				(float)m_dashValues[3],
				(float)m_dashValues[4],
				(float)m_dashValues[5],
			};
			
			pPen->SetDashPattern(dashArray, dashCount);
		}

		graphics.DrawPath(pPen, pParentFrame->m_gdppath);

		delete pPen;
	}

//	pGraphics->SetSmoothingMode(oldSmoothingMode);
//	pGraphics->SetTransform(&oldmat);

	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CPDObjectStroke::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	node->putAttribute(L"stroke-weight", _variant_t(m_strokeWeight));
	node->putAttribute(L"stroke-cap", _variant_t(m_strokeCap));
	node->putAttribute(L"stroke-join", _variant_t(m_strokeJoin));
	node->putAttribute(L"stroke-miter-limit", _variant_t(m_strokeMiterLimit));

// dashes
	long dashCount;
	get_dashedCount(&dashCount);
	_bstr_t s;
	for (int i = 0; i < dashCount; i++)
	{
		if (i > 0)
			s += L",";

		WCHAR buf[64];
		swprintf(buf, L"%g", m_dashValues[i]);
		s += buf;
	}
	node->putAttribute(L"dashes", _variant_t(s));

//
	CPDObjectWithBrushImpl<CPDObjectStroke, IPDObjectStroke>::Serialize(ar, node);

	return S_OK;
}

STDMETHODIMP CPDObjectStroke::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	_variant_t v;

	node->getAttribute(L"stroke-weight", &v);
	m_strokeWeight = v;

	node->getAttribute(L"stroke-cap", &v);
	m_strokeCap = v;

	node->getAttribute(L"stroke-join", &v);
	m_strokeJoin = v;

	node->getAttribute(L"stroke-miter-limit", &v);
	m_strokeMiterLimit = v;

// dashes
	node->getAttribute(L"dashes", &v);
	_bstr_t s = v;

	CArray<double,double> dashArray;
	GetSepNumberArray(CUString((BSTR)s), dashArray, L',');
	for (int i = 0; i < 6; i++)
	{
		if (i < dashArray.GetSize())
			m_dashValues[i] = dashArray[i];
		else
			m_dashValues[i] = 0;
	}

//
	CPDObjectWithBrushImpl<CPDObjectStroke, IPDObjectStroke>::Deserialize(ar, node, pUnkExtra);

	return S_OK;
}

STDMETHODIMP CPDObjectStroke::GetClassID(/*[out,retval]*/ CLSID* pClassID)
{
	*pClassID = CLSID_PDObjectStroke;
	return S_OK;
}
