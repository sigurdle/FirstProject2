// PDFill.cpp : Implementation of CPDObjectFill
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "PDObjectFill.h"
#include "PDBrush.h"
#include "PDObjectShape.h"

Gdiplus::Brush* GetGdiBrush(IPDBrush* brush, PDBrushType brushType = BRUSH_NONE);

/////////////////////////////////////////////////////////////////////////////
// CPDObjectFill

int CPDObjectFill::FinalConstruct()
{
	CPDObjectWithBrushImpl<CPDObjectFill, IPDObjectFill>::FinalConstruct();
	CPDObjectWithAppearanceImpl<CPDObjectFill, IPDObjectWithAppearance>::FinalConstruct();

	return S_OK;
}

void CPDObjectFill::FinalRelease()
{
	CPDObjectWithBrushImpl<CPDObjectFill, IPDObjectFill>::FinalRelease();
	CPDObjectWithAppearanceImpl<CPDObjectFill, IPDObjectWithAppearance>::FinalRelease();
}

//virtual
void CPDObjectFill::CalculateBounds()
{
	CPDObjectFrame* pParentFrame = static_cast<CPDObjectFrame*>((IPDObjectUnknown*)m_parent);
	if (pParentFrame)
	{
		m_filterRect = pParentFrame->m_bounds;

		m_appearance->SetupChildrenLayers(this);

		m_expandedBBox = m_appearance->m_expandedRect;
	}

	CalculateScale(m_expandedBBox, m_matrix);
}

STDMETHODIMP CPDObjectFill::Render2(/*[in]*/ DWORD dwBitmap, DWORD dwGraphics, double scaleX, double scaleY)
{
	Gdiplus::Graphics& graphics = *(Gdiplus::Graphics*)dwGraphics;
//	Gdiplus::Bitmap* pBitmap = (Gdiplus::Bitmap*)dwBitmap;
//	Gdiplus::Graphics graphics(pBitmap);
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality/*pGraphics->GetSmoothingMode()*/);

//	graphics.ScaleTransform(scaleX, scaleY);
//	graphics.TranslateTransform(-m_filterRect.X, -m_filterRect.Y);

//	Gdiplus::Matrix oldmat;
//	pGraphics->GetTransform(&oldmat);

//	pGraphics->ScaleTransform(scaleX, scaleY, Gdiplus::MatrixOrderAppend);

//	Gdiplus::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
//	pGraphics->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);

	Gdiplus::Brush* pBrush = GetGdiBrush(m_brush);
	if (pBrush)
	{
		graphics.FillPath(pBrush, static_cast<CPDObjectFrame*>((IPDObjectUnknown*)m_parent)->m_gdppath);
		delete pBrush;
	}

//	pGraphics->SetSmoothingMode(oldSmoothingMode);
//	pGraphics->SetTransform(&oldmat);

	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CPDObjectFill::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	CPDObjectWithBrushImpl<CPDObjectFill, IPDObjectFill>::Serialize(ar, node);
	return S_OK;
}

STDMETHODIMP CPDObjectFill::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	CPDObjectWithBrushImpl<CPDObjectFill, IPDObjectFill>::Deserialize(ar, node, pUnkExtra);
	return S_OK;
}

STDMETHODIMP CPDObjectFill::GetClassID(/*[out,retval]*/ CLSID* pClassID)
{
	*pClassID = CLSID_PDObjectFill;
	return S_OK;
}
