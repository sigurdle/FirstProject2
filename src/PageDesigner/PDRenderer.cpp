// PDRenderer.cpp : Implementation of CPDRenderer
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDRenderer.h"

#include "ObjectMap.h"

#include "PDDocument.h"
#include "PDObjectGroup.h"
#include "PDObjectLayerGroup.h"
#include "PDLayer.h"
#include "PDPage.h"
#include "PDGuides.h"
#include "PDSpreadMaster.h"

/////////////////////////////////////////////////////////////////////////////
// CPDRenderer


STDMETHODIMP CPDRenderer::get_targetHDC(HDC *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = (HDC)m_pGraphics;
	return S_OK;
}

STDMETHODIMP CPDRenderer::put_targetHDC(HDC newVal)
{
	m_pGraphics = (Gdiplus::Graphics*)newVal;

	return S_OK;
}

#include "PDSpreadImpl.h"

STDMETHODIMP CPDRenderer::RenderGuide(IPDSpread* spread, IPDGuide *guide, DWORD color, double left, double top, double width, double height)
{
	CComPtr<IPDDocument> document;
	spread->get_ownerDocument(&document);

	double pageWidth;
	double pageHeight;
	document->get_pageWidth(&pageWidth);
	document->get_pageHeight(&pageHeight);

	CComPtr<IObjectMap> pages;
	spread->get_pages(&pages);

	long npages;
	pages->get_length(&npages);

	long direction;
	guide->get_direction(&direction);

	double position;
	guide->get_position(&position);

	Gdiplus::Pen pen(Gdiplus::Color(GetRValue(color), GetGValue(color), GetBValue(color)));

	if (direction == 0)	// Horizontal
	{
		long pageIndex;
		guide->get_pageIndex(&pageIndex);

		float y = position;
		float x1;
		float x2;

		if (y < 0 || y > pageHeight || pageIndex < 0)	// Outside of spread
		{
			x1 = left;
			x2 = (left+width);
		}
		else
		{
			x1 = (pageWidth*pageIndex);
			x2 = (x1+pageWidth);
		}

		m_pGraphics->DrawLine(&pen, (float)(x1*m_magnify), (float)(y*m_magnify), (float)(x2*m_magnify), (float)(y*m_magnify));
	}
	else	// Vertical
	{
		float x = position;
		float y1;
		float y2;

		if (x < 0 || x > pageWidth*npages)	// Outside of spread
		{
			y1 = top;
			y2 = (top+height);
		}
		else
		{
			y1 = 0;
			y2 = pageHeight;
		}

		m_pGraphics->DrawLine(&pen, (float)(x*m_magnify), (float)(y1*m_magnify), (float)(x*m_magnify), (float)(y2*m_magnify));
	}

	return S_OK;
}

void CPDRenderer::RenderGuides(CPDSpreadImpl<IPDSpread>* spread, double left, double top, double width, double height)
{
//	Gdiplus::GraphicsState state = m_pGraphics->Save();
	ATLASSERT(0);
#if 0
	CComPtr<IPDGuides> guides;
	spread->get_guides(&guides);

	long nguides;
	guides->get_length(&nguides);
	for (long nguide = 0; nguide < nguides; nguide++)
	{
		CComPtr<IPDGuide> guide;
		guides->item(nguide, &guide);

		RenderGuide(spread, guide, RGB(0, 0, 200), left, top, width, height);
	}
#endif

//	m_pGraphics->Restore(state);
}

void CPDRenderer::RenderDocumentGrid(CPDSpreadImpl<IPDSpread>* spread, double left, double top, double width, double height)
{
	CPDDocument* pDocument = spread->m_pDocument;

	double pageWidth;
	double pageHeight;
	pDocument->get_pageWidth(&pageWidth);
	pDocument->get_pageHeight(&pageHeight);

	Gdiplus::GraphicsState state = m_pGraphics->Save();

	Gdiplus::Pen pen(Gdiplus::Color(160, 160, 160), 1);
	Gdiplus::Pen pensub(Gdiplus::Color(200, 200, 200), 1);

	// Horizontal subdivisions
	{
		int start = (left-pDocument->m_horizontalGridlineEvery-1)/pDocument->m_horizontalGridlineEvery;
		int end = (left+width)/pDocument->m_horizontalGridlineEvery;

		for (int i = start; i <= end; i++)
		{
			for (int j = 1; j < pDocument->m_horizontalGridSubdivisions; j++)
			{
				float x = (i*pDocument->m_horizontalGridlineEvery + (pDocument->m_horizontalGridlineEvery/pDocument->m_horizontalGridSubdivisions*j)) *m_magnify;

				m_pGraphics->DrawLine(&pensub, (float)x, (float)top*m_magnify, (float)x, (float)(top+height)*m_magnify);
			}
		}
	}

	// Vertical subdivisions
	{
		int start = (top-pDocument->m_verticalGridlineEvery-1)/pDocument->m_verticalGridlineEvery;
		int end = (top+height)/pDocument->m_verticalGridlineEvery;

		for (int i = start; i <= end; i++)
		{
			for (int j = 1; j < pDocument->m_verticalGridSubdivisions; j++)
			{
				float y = (i*pDocument->m_verticalGridlineEvery + (pDocument->m_verticalGridlineEvery/pDocument->m_verticalGridSubdivisions*j)) *m_magnify;

				m_pGraphics->DrawLine(&pensub, (float)left*m_magnify, (float)y, (float)(left+width)*m_magnify, (float)y);
			}
		}
	}

	// Horizontal grid
	{
		int start = left/pDocument->m_horizontalGridlineEvery;
		int end = (left+width)/pDocument->m_horizontalGridlineEvery;

		for (int i = start; i <= end; i++)
		{
			float x = i*pDocument->m_horizontalGridlineEvery*m_magnify;

			m_pGraphics->DrawLine(&pen, (float)x, (float)top*m_magnify, (float)x, (float)(top+height)*m_magnify);
		}
	}

	// Vertical grid
	{
		int start = top/pDocument->m_verticalGridlineEvery;
		int end = (top+height)/pDocument->m_verticalGridlineEvery;

		for (int i = start; i <= end; i++)
		{
			float y = i*pDocument->m_verticalGridlineEvery*m_magnify;

			m_pGraphics->DrawLine(&pen, (float)left*m_magnify, (float)y, (float)(left+width)*m_magnify, (float)y);
		}
	}

	m_pGraphics->Restore(state);
}

STDMETHODIMP CPDRenderer::RenderSpreadBackground(IPDSpread *ispread)
{
	CPDSpreadImpl<IPDSpread>* spread = static_cast<CPDSpreadImpl<IPDSpread>*>(ispread);

	CPDDocument* pDocument = spread->m_pDocument;

	double pageWidth;
	double pageHeight;
	pDocument->get_pageWidth(&pageWidth);
	pDocument->get_pageHeight(&pageHeight);

	CComPtr<IObjectMap> pages;
	spread->get_pages(&pages);

	long npages;
	pages->get_length(&npages);

	Gdiplus::SolidBrush shadowBrush(Gdiplus::Color(0, 0, 0));
	Gdiplus::SolidBrush pageBrush(Gdiplus::Color(255, 255, 255));

	m_pGraphics->FillRectangle(
		&shadowBrush,
		Gdiplus::RectF(4, 4, npages*pageWidth*m_magnify, pageHeight*m_magnify));

	m_pGraphics->FillRectangle(
		&pageBrush,
		Gdiplus::RectF(0, 0, npages*pageWidth*m_magnify, pageHeight*m_magnify));

	return S_OK;
}

STDMETHODIMP CPDRenderer::RenderObject(IPDObject *object)
{
	CPDObject* pObject = (CPDObject*)static_cast<CPDObjectImpl<IPDObject>*>(object);
	pObject->Render(this, m_pGraphics, m_magnify, m_magnify);
	return S_OK;
}

STDMETHODIMP CPDRenderer::RenderSpread(IPDSpread *ispread, double left, double top, double width, double height)
{
	double magnify = m_magnify;

	CPDSpreadImpl<IPDSpread>* spread = static_cast<CPDSpreadImpl<IPDSpread>*>(ispread);

	Gdiplus::GraphicsState state = m_pGraphics->Save();

	Gdiplus::Pen blackPen(Gdiplus::Color(0, 0, 0));
	Gdiplus::Pen marginsPen(Gdiplus::Color(255, 79, 255));
	Gdiplus::Pen columnsPen(Gdiplus::Color(153, 51, 255));

	Gdiplus::SolidBrush blackBrush(Gdiplus::Color(0, 0, 0));
	Gdiplus::SolidBrush whiteBrush(Gdiplus::Color(255, 255, 255));

	CPDDocument* pDocument = spread->m_pDocument;

	double pageWidth;
	double pageHeight;
	pDocument->get_pageWidth(&pageWidth);
	pDocument->get_pageHeight(&pageHeight);

//	long columns = 4;
//	double columnGutter = 8;

	CComPtr<IObjectMap> pages;
	spread->get_pages(&pages);

	long npages;
	pages->get_length(&npages);

	if (pDocument->m_gridsInBack)
	{
		if (pDocument->m_viewDocumentGrid)
		{
			RenderDocumentGrid(spread, left, top, width, height);
		}
	}

	// Render margins & columns
	{
		double x = 0;
		double y = 0;

		for (int npage = 0; npage < npages; npage++)
		{
			Gdiplus::GraphicsState state = m_pGraphics->Save();

			CComQIPtr<IPDPage> page;
			pages->item(npage, (IUnknown**)&page);

			//CComObject<CPDPage>* pPage = static_cast<CComObject<CPDPage>*>(page.p);

			double marginTop;
			double marginBottom;
			double marginLeft;
			double marginRight;
			page->get_marginTop(&marginTop);
			page->get_marginBottom(&marginBottom);
			page->get_marginLeft(&marginLeft);
			page->get_marginRight(&marginRight);

			long columnNumber;
			double columnGutter;
			page->get_columnNumber(&columnNumber);
			page->get_columnGutter(&columnGutter);

			m_pGraphics->TranslateTransform(x, y);

			m_pGraphics->DrawRectangle(&blackPen, Gdiplus::RectF(0, 0, pageWidth*magnify, pageHeight*magnify));

			{
				m_pGraphics->DrawRectangle(&marginsPen, Gdiplus::RectF(marginLeft*magnify, marginTop*magnify, (pageWidth-marginLeft-marginRight)*magnify, (pageHeight-marginTop-marginBottom)*magnify));

				double innerWidth = pageWidth-marginLeft-marginRight;
				double columnWidth = (innerWidth-(columnNumber-1)*columnGutter)/columnNumber;
				double x = marginLeft;

				for (int i = 0; i < columnNumber; i++)
				{
					m_pGraphics->DrawLine(&columnsPen, (float)(x*magnify), (float)(marginTop*magnify), (float)(x*magnify), (float)((pageHeight-marginBottom)*magnify));
					x += columnWidth;
					m_pGraphics->DrawLine(&columnsPen, (float)(x*magnify), (float)(marginTop*magnify), (float)(x*magnify), (float)((pageHeight-marginBottom)*magnify));
					x += columnGutter;
				}
			}

			x += pageWidth*magnify;

			m_pGraphics->Restore(state);
		}
	}

// Draw objects

	{
		Gdiplus::GraphicsState state = m_pGraphics->Save();

		m_pGraphics->ScaleTransform(magnify, magnify);

		m_pGraphics->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);

		// Draw Layergroups
		{
			for (int layergroup = 0; layergroup < spread->m_layergroups->/*m_children->*/m_items.GetSize(); layergroup++)
			{
				CPDLayer* pLayer = static_cast<CPDLayer*>((IPDLayer*)(spread->m_pDocument->m_layers->m_items[layergroup]));
				CPDObjectLayerGroup* pLayerGroup = (CPDObjectLayerGroup*)((IPDObjectLayerGroup*)(spread->m_layergroups->/*m_children->*/m_items[layergroup]));

				if (pLayer->m_visible)
				{
			// Draw master
					for (int npage = 0; npage < npages; npage++)
					{
						CPDPage* pPage = (CPDPage*)(IPDPage*)spread->m_pages->m_items[npage];

						if (pPage->m_baseMaster)
						{
							CPDObjectLayerGroup* pMasterLayerGroup = (CPDObjectLayerGroup*)((IPDObjectLayerGroup*)(pPage->m_baseMaster->m_layergroups->/*m_children->*/m_items[layergroup]));

							pMasterLayerGroup->Render(this, m_pGraphics, m_magnify, m_magnify);
						}
					}

					pLayerGroup->Render(this, m_pGraphics, m_magnify, m_magnify);
				}
			}
		}

		m_pGraphics->Restore(state);
	}

	{
//		RenderGuides(spread, left, top, width, height);
	}

	m_pGraphics->Restore(state);

	return S_OK;
}

STDMETHODIMP CPDRenderer::get_magnify(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_magnify;
	return S_OK;
}

STDMETHODIMP CPDRenderer::put_magnify(double newVal)
{
	m_magnify = newVal;
	return S_OK;
}

STDMETHODIMP CPDRenderer::AddCustomRenderer(IPDCustomRenderer *customRenderer)
{
	m_customRenderer = customRenderer;
	return S_OK;
}
