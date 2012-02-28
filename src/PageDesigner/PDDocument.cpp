#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDDocument.h"
#include "PDDocumentView.h"

#include "PDLayer.h"
//#include "PDSpread.h"
#include "PDSpreadMaster.h"
#include "PDSpreadDocument.h"
#include "PDPage.h"
#include "PDObjectGroup.h"
#include "PDObjectLayerGroup.h"
#include "PDObjectShape.h"
#include "PDImage.h"
#include "PDContentGraphic.h"
#include "PDContentText.h"
#include "PDPathText.h"
#include "PDGuides.h"
#include "PDSwatches.h"
#include "PDStory.h"
#include "PDSection.h"

#include "ObjectMap.h"

// TODO: remove this
#include "PageDesignerApp.h"
#include "PageDesignerFrame.h"
extern CPageDesignerApp* gApp;

COLORREF LayerColors[] =
{
	RGB(79, 153, 255),
	RGB(255, 0, 0),
	RGB(79, 255, 79),
	RGB(0, 0, 255),
	RGB(255, 255, 79),
	RGB(255, 79, 255),
	RGB(0, 255, 255),
	RGB(127, 127, 127),
	RGB(0, 0, 0),
	RGB(255, 102, 0),
	RGB(0, 84, 0),
	RGB(0, 153, 153),
	RGB(204, 153, 102),
	RGB(153, 51, 0),
	RGB(153, 51, 255),
	RGB(255, 153, 0),
	RGB(0, 0, 135),
	RGB(255, 153, 204),
	RGB(153, 153, 255),
	RGB(153, 0, 0),
	RGB(102, 102, 0),
	RGB(255, 153, 153),
	RGB(153, 0, 51),
	RGB(153, 204, 0),
	RGB(153, 102, 0),
	RGB(102, 0, 102),
	RGB(186, 186, 186),
};

#define NUMLAYERCOLORS (sizeof(LayerColors)/sizeof(COLORREF))

/////////////////////////////////////////////////////////////////////////////
// OLE OLE_DATA init structure

#include "ole.h"
#include "..\OleDataObject.h"
#include "OleServerItem.h"

OLE_DATA _oleData;

OLE_DATA::OLE_DATA()
{
	// OLE 1.0 Clipboard formats
	cfNative = ::RegisterClipboardFormat(_T("Native"));
	cfOwnerLink = ::RegisterClipboardFormat(_T("OwnerLink"));
	cfObjectLink = ::RegisterClipboardFormat(_T("ObjectLink"));

	// OLE 2.0 Clipboard formats
	cfEmbeddedObject = ::RegisterClipboardFormat(_T("Embedded Object"));
	cfEmbedSource = ::RegisterClipboardFormat(_T("Embed Source"));
	cfLinkSource = ::RegisterClipboardFormat(_T("Link Source"));
	cfObjectDescriptor = ::RegisterClipboardFormat(_T("Object Descriptor"));
	cfLinkSourceDescriptor = ::RegisterClipboardFormat(_T("Link Source Descriptor"));
	cfFileName = ::RegisterClipboardFormat(_T("FileName"));
	cfFileNameW = ::RegisterClipboardFormat(_T("FileNameW"));
	cfRichTextFormat = ::RegisterClipboardFormat(_T("Rich Text Format"));
	cfRichTextAndObjects = ::RegisterClipboardFormat(_T("RichEdit Text and Objects"));
}

////////////////////////////////////
// CPDDocument

HRESULT CPDDocument::FinalConstruct()
{
	HRESULT hr;

	hr = CComObject<CUndoManager>::CreateInstance(&m_undoManager);
	if (FAILED(hr)) return hr;
	m_undoManager->AddRef();

	hr = CComObject<CObjectMap>::CreateInstance(&m_stories);
	if (FAILED(hr)) return hr;
	m_stories->AddRef();

	hr = CComObject<CObjectMap>::CreateInstance(&m_images);
	if (FAILED(hr)) return hr;
	m_images->AddRef();

	hr = CComObject<CObjectMap>::CreateInstance(&m_symbols);
	if (FAILED(hr)) return hr;
	m_symbols->AddRef();

	hr = CComObject<CObjectMap>::CreateInstance(&m_layers);
	if (FAILED(hr)) return hr;
	m_layers->AddRef();

	hr = CComObject<CObjectMap>::CreateInstance(&m_spreads);
	if (FAILED(hr)) return hr;
	m_spreads->AddRef();

	hr = CComObject<CObjectMap>::CreateInstance(&m_pages);
	if (FAILED(hr)) return hr;
	m_pages->AddRef();

	hr = CComObject<CObjectMap>::CreateInstance(&m_masterSpreads);
	if (FAILED(hr)) return hr;
	m_masterSpreads->AddRef();

	hr = CComObject<CObjectMap>::CreateInstance(&m_masterPages);
	if (FAILED(hr)) return hr;
	m_masterPages->AddRef();

	hr = CComObject<CPDSwatches>::CreateInstance(&m_swatches);
	if (FAILED(hr)) return hr;
	m_swatches->AddRef();

	hr = CComObject<CPDSection>::CreateInstance(&m_firstSection);
	if (FAILED(hr)) return hr;
	m_firstSection->AddRef();

	// Default Appearance
	{
		hr = CPDObjectWithAppearanceAndStrokeFillImpl<CPDDocument>::FinalConstruct();
		if (FAILED(hr)) return hr;

		{
		//	CComPtr<IObjectMap> subObjects;
		//	strokefill->get_subObjects(&subObjects);

			CComPtr<IPDObjectFill> fill;
			fill.CoCreateInstance(CLSID_PDObjectFill);
			if (fill)
			{
				CComPtr<IPDBrush> brush;
				fill->get_brush(&brush);

				CComPtr<IPDColor> color;
				brush->setColor(&color);
				color->setRGB(255, 255, 255);

				m_activeFill = fill;
				appendSubObject(fill);
			}

			CComPtr<IPDObjectStroke> stroke;
			stroke.CoCreateInstance(CLSID_PDObjectStroke);
			if (stroke)
			{
				CComPtr<IPDBrush> brush;
				stroke->get_brush(&brush);

				CComPtr<IPDColor> color;
				brush->setColor(&color);
				color->setRGB(0, 0, 0);

				m_activeStroke = stroke;
				appendSubObject(stroke);
			}
		}
	}

	return S_OK;
}

void CPDDocument::FinalRelease()
{
	CPDObjectWithAppearanceAndStrokeFillImpl<CPDDocument>::FinalRelease();

	if (m_stories)
	{
		for (int i = 0; i < m_stories->m_items.GetSize(); i++)
		{
			CPDStory* pStory = static_cast<CPDStory*>((IPDStory*)m_stories->m_items[i]);
			pStory->Unadvise(this);
		}

		m_stories->Release();
		m_stories = NULL;
	}

	if (m_images)
	{
		/*
		for (int i = 0; i < m_stories->m_items.GetSize(); i++)
		{
			CPDStory* pStory = static_cast<CPDStory*>((IPDStory*)m_stories->m_items[i]);
			pStory->Unadvise(this);
		}
		*/

		m_images->Release();
		m_images = NULL;
	}

	if (m_spreads)
	{
		m_spreads->Release();
		m_spreads = NULL;
	}

	if (m_pages)
	{
		m_pages->Release();
		m_pages = NULL;
	}

	if (m_masterSpreads)
	{
		m_masterSpreads->Release();
		m_masterSpreads = NULL;
	}

	if (m_masterPages)
	{
		m_masterPages->Release();
		m_masterPages = NULL;
	}

	if (m_layers)
	{
		m_layers->Release();
		m_layers = NULL;
	}

	if (m_symbols)
	{
		m_symbols->Release();
		m_symbols = NULL;
	}

	if (m_swatches)
	{
		m_swatches->Release();
		m_swatches = NULL;
	}

	if (m_undoManager)
	{
		m_undoManager->Release();
		m_undoManager = NULL;
	}
}

STDMETHODIMP CPDDocument::NewWindow(IPDDocumentView **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CUIMDIChild>* child;
	CComObject<CUIMDIChild>::CreateInstance(&child);
	child->AddRef();
	gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&child->m_spFrame);

// View
	CComObject<CPDDocumentView>* pView;
	CComObject<CPDDocumentView>::CreateInstance(&pView);
	pView->m_document = this;
	gApp->m_frame->FindMenu(IDR_PDDOCUMENTVIEW, &pView->m_menu);

	child->AddPage(pView, NULL);

	pView->m_activeLayer = m_firstLayer;
	pView->m_activeSpread = m_firstSpread;

	child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);

	pView->m_activeSpread = NULL;
	pView->put_activeSpread(m_firstSpread);

	*pVal = pView;
	(*pVal)->AddRef();

	return S_OK;
}

void CPDDocument::CreateSpreadLayerGroups(IPDSpread* spread)
{
	CPDSpreadImpl<IPDSpread>* pSpread = static_cast<CPDSpreadImpl<IPDSpread>*>(spread);
	// Create layergroups on the spread
	for (int nlayer = 0; nlayer < m_layers->m_items.GetSize(); nlayer++)
	{
		CComObject<CPDObjectLayerGroup>* layergroup;
		CComObject<CPDObjectLayerGroup>::CreateInstance(&layergroup);
		if (layergroup)
		{
			CoCreateGuid(&layergroup->m_uniqId);

			layergroup->m_pDocument = this;
			layergroup->m_layer = static_cast<CPDLayer*>((IPDLayer*)(m_layers->m_items[nlayer]));
			layergroup->m_guides->m_layer = layergroup->m_layer;

			pSpread->insertLayerGroup(layergroup, NULL);
		}
	}
}

void CPDDocument::CreatePages(int npages)
{
	CComObject<CPDSpreadDocument>* pSpread = NULL;
	long spine = 0;

	for (int i = 0; i < npages; i++)
	{
		if (pSpread == NULL || spine == 1)	// New spread
		{
			CComObject<CPDSpreadDocument>::CreateInstance(&pSpread);
			pSpread->m_spine = spine;

			insertSpread(pSpread, NULL);

			CreateSpreadLayerGroups(pSpread);
		}

		spine = !spine;

		ATLASSERT(pSpread != NULL);

		CComObject<CPDPage>* pPage;
		CComObject<CPDPage>::CreateInstance(&pPage);
		if (pPage != NULL)
		{
			pPage->m_pDocument = this;
			pPage->m_ownerSpread = static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)pSpread);

			pPage->m_marginTop = m_marginTop;
			pPage->m_marginBottom = m_marginBottom;
			pPage->m_marginInside = m_marginInside;
			pPage->m_marginOutside = m_marginOutside;
			pPage->m_columnNumber = m_columnNumber;
			pPage->m_columnGutter = m_columnGutter;

			pPage->AddRef();
			pSpread->m_pages->m_items.Add((IPDPage*)pPage);

			pPage->AddRef();
			m_pages->m_items.Add((IPDPage*)pPage);
		}
	}
}

STDMETHODIMP CPDDocument::get_filePath(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_filePath.copy();
	return S_OK;
}

STDMETHODIMP CPDDocument::put_filePath(BSTR newVal)
{
	m_filePath = newVal;

	m_fileTitle = PathFindFileName(m_filePath);

	return S_OK;
}

STDMETHODIMP CPDDocument::get_fileTitle(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_fileTitle.copy();
	return S_OK;
}

STDMETHODIMP CPDDocument::put_fileTitle(BSTR newVal)
{
	m_fileTitle = newVal;
	return S_OK;
}

/*
#include "PDColor.h"
#include "PDSwatchColor.h"
*/

STDMETHODIMP CPDDocument::NewDocument()
{
// Copy app settings to this document

// Swatches
	{
		CComPtr<IPDSwatches> swatches;
		gIApp->get_swatches(&swatches);

		long nswatches;
		swatches->get_length(&nswatches);

		for (int i = 0; i < nswatches; i++)
		{
			CComQIPtr<IPDSwatch> swatch;
			swatches->item(i, &swatch);

			CComPtr<IPDSwatch> swatchClone;
			swatch->clone(&swatchClone);

			if (swatchClone)
			{
				m_swatches->appendSwatch(swatchClone);
			}
		}
	}

	copyDocumentSettingsFrom(gApp);

// Create a default layer
	CComObject<CPDLayer>* pLayer;
	CComObject<CPDLayer>::CreateInstance(&pLayer);
	if (pLayer)
	{
		pLayer->m_color = LayerColors[m_nextLayerIndex];

		WCHAR buf[64];
		swprintf(buf, L"Layer %d", ++m_nextLayerIndex);
		pLayer->m_name = buf;

		DWORD cookie;
		pLayer->Advise(this, &cookie);

		insertLayer(pLayer, NULL);
	}
	else
		return E_FAIL;

// Create a default A-Master
	CComObject<CPDSpreadMaster>* pSpread;
	CComObject<CPDSpreadMaster>::CreateInstance(&pSpread);
	if (pSpread)
	{
	//	pSpread->m_layergroups->m_spread = static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)pSpread);
	//	pSpread->m_layergroups->m_pDocument = this;
		pSpread->m_pDocument = this;
		pSpread->m_prefix = L"A";
		pSpread->m_name = L"Master";
		pSpread->m_spine = 1;

		m_nextMasterPrefix++;

		pSpread->AddRef();
		m_masterSpreads->m_items.Add((IPDSpread*)pSpread);

		CreateSpreadLayerGroups(static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)pSpread));

		ATLASSERT(pSpread->m_layergroups->/*m_children->*/m_items.GetSize() == 1);

		for (int i = 0; i < 2; i++)
		{
			CComObject<CPDPage>* pPage;
			CComObject<CPDPage>::CreateInstance(&pPage);
			if (pPage != NULL)
			{
				pPage->m_pDocument = this;
				pPage->m_ownerSpread = static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)pSpread);

				pPage->m_marginTop = m_marginTop;
				pPage->m_marginBottom = m_marginBottom;
				pPage->m_marginInside = m_marginInside;
				pPage->m_marginOutside = m_marginOutside;
				pPage->m_columnNumber = m_columnNumber;
				pPage->m_columnGutter = m_columnGutter;

				pPage->AddRef();
				pSpread->m_pages->m_items.Add((IPDPage*)pPage);

				pPage->AddRef();
				m_masterPages->m_items.Add((IPDPage*)pPage);
			}
		}
	}
	else
		return E_FAIL;

	return S_OK;
}

STDMETHODIMP CPDDocument::get_undoManager(IOleUndoManager* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_undoManager;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDDocument::ShowViews()
{
	CComPtr<IPDDocumentView> view;
	NewWindow(&view);

	return S_OK;
}

STDMETHODIMP CPDDocument::get_layers(IObjectMap **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_layers;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDDocument::get_stories(IObjectMap **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_stories;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDDocument::get_spreads(IObjectMap **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_spreads;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDDocument::get_pages(IObjectMap **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pages;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDDocument::get_masterSpreads(IObjectMap **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_masterSpreads;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDDocument::get_masterPages(IObjectMap **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_masterPages;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDDocument::get_swatches(IPDSwatches **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_swatches;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDDocument::get_pageWidth(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pageWidth;
	return S_OK;
}

STDMETHODIMP CPDDocument::get_pageHeight(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pageHeight;
	return S_OK;
}

STDMETHODIMP CPDDocument::get_facingPages(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_facingPages;
	return S_OK;
}


STDMETHODIMP CPDDocument::get_symbols(IObjectMap **pVal)
{
	if (pVal == NULL) return E_POINTER;
	(*pVal = m_symbols)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDDocument::get_images(IObjectMap **pVal)
{
	if (pVal == NULL) return E_POINTER;
	(*pVal = m_images)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDDocument::loadImage(BSTR pathName, IPDImage **pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = NULL;

	Gdiplus::Image* gdiimage = new Gdiplus::Image(pathName);
	if (gdiimage)
	{
		CComObject<CPDImage>* image;
		CComObject<CPDImage>::CreateInstance(&image);
		if (image)
		{
			image->m_image = gdiimage;
			image->m_pathName = pathName;

			image->AddRef();
			m_images->m_items.Add((IPDImage*)image);

			*pVal = image;
			(*pVal)->AddRef();

			FireOnChanged(NOTIFY_ADD, image->GetUnknown(), DISPID_UNKNOWN);
		}
	}

	return S_OK;
}

STDMETHODIMP CPDDocument::loadImageFromStream(IStream *stream, IPDImage **pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = NULL;

	Gdiplus::Bitmap* gdiimage = new Gdiplus::Bitmap(stream);
	if (gdiimage)
	{
		CComObject<CPDImage>* image;
		CComObject<CPDImage>::CreateInstance(&image);
		if (image)
		{
			image->m_image = gdiimage;
			image->m_pathName = L"";//pathName;

			image->AddRef();
			m_images->m_items.Add((IPDImage*)image);

			*pVal = image;
			(*pVal)->AddRef();

			FireOnChanged(NOTIFY_ADD, image->GetUnknown(), DISPID_UNKNOWN);
		}
	}

	return S_OK;
}

STDMETHODIMP CPDDocument::createImage(long width, long height, DWORD mode, IPDImage **pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = NULL;

	Gdiplus::Bitmap* gdiimage = new Gdiplus::Bitmap(width, height, mode);
	if (gdiimage)
	{
		CComObject<CPDImage>* image;
		CComObject<CPDImage>::CreateInstance(&image);
		if (image)
		{
			image->m_image = gdiimage;

			image->AddRef();
			m_images->m_items.Add((IPDImage*)image);

			*pVal = image;
			(*pVal)->AddRef();

			FireOnChanged(NOTIFY_ADD, image->GetUnknown(), DISPID_UNKNOWN);
		}
	}

	return S_OK;
}

STDMETHODIMP CPDDocument::get_firstSection(IPDSection **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_firstSection;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDDocument::createSection(IPDSection **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDSection>* pSection;
	CComObject<CPDSection>::CreateInstance(&pSection);
	if (pSection)
	{
		*pVal = pSection;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDDocument::getMasterSpreadByName(BSTR prefix, BSTR name, IPDSpreadMaster **pVal)
{
	if (pVal == NULL) return E_POINTER;

	for (int i = 0; i < m_masterSpreads->m_items.GetSize(); i++)
	{
		CPDSpreadMaster* pMaster = (CPDSpreadMaster*)(IPDSpread*)m_masterSpreads->m_items[i];
		if (!wcsicmp(pMaster->m_prefix, prefix) &&
			!wcsicmp(pMaster->m_name, name))
		{
			*pVal = pMaster;
			(*pVal)->AddRef();
			return S_OK;
		}
	}

	*pVal = NULL;

	return S_OK;
}

HRESULT CPDDocument::insertLayer(IPDLayer* object, IPDLayer* before)
{
	CComObject<CPDLayer>* pObject = static_cast<CComObject<CPDLayer>*>(object);
	CComObject<CPDLayer>* pBefore = static_cast<CComObject<CPDLayer>*>(before);

	/*
	if (pObject->m_pDocument && (pObject->m_pDocument != this))
	{
		MessageBox(GetMainHwnd(), "Cannot move layers across documents", "PageDesigner", MB_OK);
		return E_FAIL;
	}
	*/

	object->AddRef();

// First remove it from previous parent
	if (pObject->m_pDocument)
	{
		pObject->m_pDocument->removeLayer(pObject);
	}

	CComObject<CPDLayer>* pAfter;

	if (pBefore)
		pAfter = pBefore->m_previousSibling;
	else
		pAfter = m_lastLayer;

	pObject->m_nextSibling = pBefore;
	pObject->m_previousSibling = pAfter;

	if (pAfter == NULL)
		m_firstLayer = pObject;
	else
		pAfter->m_nextSibling = pObject;

	if (pBefore == NULL)
		m_lastLayer = pObject;
	else
		pBefore->m_previousSibling = pObject;

//	pObject->m_layergroups->m_spread = static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)pObject);
//	pObject->m_layergroups->m_pDocument = this;
	pObject->m_pDocument = this;//static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)this);//static_cast<CComObject<CPDGradient>*>(this);
	//pObject->attachToSpread(pObject->m_parent);

	HRESULT hr = E_FAIL;

	if (pBefore)
	{
		for (int i = 0; i < m_layers->m_items.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_layers->m_items[i], before))
			{
				m_layers->m_items.InsertAt(i, object);
				hr = S_OK;
				break;
			}
		}
	}
	else
	{
		m_layers->m_items.Add(object);
		hr = S_OK;
	}

	FireOnChanged(NOTIFY_ADD, object, DISPID_UNKNOWN);

	ATLASSERT(SUCCEEDED(hr));
	return hr;
}

HRESULT CPDDocument::insertSpread(IPDSpread* object, IPDSpread* before)
{
	CComObject<CPDSpreadDocument>* pObject = static_cast<CComObject<CPDSpreadDocument>*>(object);
	CComObject<CPDSpreadDocument>* pBefore = static_cast<CComObject<CPDSpreadDocument>*>(before);

	object->AddRef();

/*
	ATLASSERT(pObject->m_pDocument == m_pDocument);
	if (pObject->m_pDocument != m_pDocument)
	{
		MessageBox(NULL, "Cannot insert object across documents", "", MB_OK);
		return E_FAIL;
	}

// First remove it from previous parent
	if (pObject->m_parent)
	{
		pObject->m_parent->removeObject(pObject);
	}
*/
	CComObject<CPDSpreadDocument>* pAfter;

	if (pBefore)
		pAfter = pBefore->m_previousSpread;
	else
		pAfter = m_lastSpread;

	pObject->m_nextSpread = pBefore;
	pObject->m_previousSpread = pAfter;

	if (pAfter == NULL)
		m_firstSpread = pObject;
	else
		pAfter->m_nextSpread = pObject;

	if (pBefore == NULL)
		m_lastSpread = pObject;
	else
		pBefore->m_previousSpread = pObject;

//	pObject->m_layergroups->m_spread = static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)pObject);
//	pObject->m_layergroups->m_pDocument = this;
	pObject->m_pDocument = this;//static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)this);//static_cast<CComObject<CPDGradient>*>(this);
	//pObject->attachToSpread(pObject->m_parent);

	if (pBefore)
	{
		for (int i = 0; i < m_spreads->m_items.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_spreads->m_items[i], before))
			{
				m_spreads->m_items.InsertAt(i, object);
				return S_OK;
			}
		}
	}
	else
	{
		m_spreads->m_items.Add(object);
		return S_OK;
	}

	ATLASSERT(0);
	return E_FAIL;
}

void CPDDocument::ShufflePages(CComObject<CPDSpreadDocument>* pSpread)
{
	while (pSpread)
	{
		CComObject<CPDSpreadDocument>* nextSpread = pSpread->m_nextSpread;

		if (!pSpread->m_keepSpreadTogether)
		{
			int maxPages;

			if (m_facingPages)
			{
				if (pSpread->m_previousSpread)
					maxPages = 2;
				else
					maxPages = 1;
			}
			else
			{
				maxPages = 1;
			}

			int npages = pSpread->m_pages->m_items.GetSize();

			if (npages < maxPages)
			{
				CComObject<CPDSpreadDocument>* nextSpread = pSpread->m_nextSpread;

				// Move maxPages..n from the next spread up to this spread
				for (int i = 0; i < maxPages-npages; i++)
				{
					while (nextSpread && nextSpread->m_pages->m_items.GetSize() == 0)
					{
						nextSpread = nextSpread->m_nextSpread;
					}

					if (nextSpread)
					{
						CPDPage* pPage = (CPDPage*)(IPDPage*)nextSpread->m_pages->m_items[0];

						pPage->AddRef();
						pPage->m_ownerSpread->removePage(pPage);

						pPage->m_ownerSpread = static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)pSpread);
						pSpread->m_pages->m_items.Add((IPDPage*)pPage);
					}
				}
			}
			else if (npages > maxPages)
			{
			// Move the pages maxPages..n down to next spread
				for (int i = npages-1; i >= maxPages; i--)
				{
					CPDPage* pPage = (CPDPage*)(IPDPage*)pSpread->m_pages->m_items[i];

					pPage->AddRef();
					pPage->m_ownerSpread->removePage(pPage);

					if (nextSpread == NULL)
					{
						CComObject<CPDSpreadDocument>::CreateInstance(&nextSpread);
						if (m_facingPages)
							nextSpread->m_spine = 1;
						else
							nextSpread->m_spine = 0;

						insertSpread(nextSpread, NULL);

						CreateSpreadLayerGroups(nextSpread);
					}

					pPage->m_ownerSpread = static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)nextSpread);
					nextSpread->m_pages->m_items.InsertAt(0, (IPDPage*)pPage);
				}

				// Move objects
				{
					double offsetX = - 2 * m_pageWidth;	// Move them
					double x = 2 * m_pageWidth;	// Objects on right of this are moved

					for (int nlayergroup = 0; nlayergroup < pSpread->m_layergroups->/*m_children->*/m_items.GetSize(); nlayergroup++)
					{
						CPDObjectLayerGroup* pLayerGroup = (CPDObjectLayerGroup*)((IPDObjectLayerGroup*)(pSpread->m_layergroups->/*m_children->*/m_items[nlayergroup]));
						CPDObjectLayerGroup* pDestLayerGroup = (CPDObjectLayerGroup*)((IPDObjectLayerGroup*)(nextSpread->m_layergroups->/*m_children->*/m_items[nlayergroup]));

						for (int i = 0; i < pLayerGroup->m_children->m_items.GetSize(); i++)
						{
							CComQIPtr<IPDObject> object = pLayerGroup->m_children->m_items[i];

							CComQIPtr<IPDObjectTransformable> transformable = object;
							if (transformable)
							{
								RectD xbounds;
								transformable->get_xbounds(&xbounds);

								if (xbounds.X+xbounds.Width/2 > x)
								{
									transformable->Move(offsetX, 0);
									pDestLayerGroup->appendObject(object);
								}
							}
						}
					}
				}
			}

			if (m_facingPages)
				pSpread->m_spine = pSpread->m_previousSpread? 1: 0;
			else
				pSpread->m_spine = 0;
		}

		pSpread = nextSpread;
	}
}

STDMETHODIMP CPDDocument::insertPagesBefore(long nPages, long nBeforePage)
{
	CComObject<CPDSpreadDocument>* pSpread = NULL;

	CPDPage* pBeforePage = (CPDPage*)(IPDPage*)m_pages->m_items[nBeforePage];
	pSpread = (CComObject<CPDSpreadDocument>*)pBeforePage->m_ownerSpread;

	for (int nBeforePageOnSpread = 0; nBeforePageOnSpread < pSpread->m_pages->m_items.GetSize(); nBeforePageOnSpread++)
	{
		if (IsUnknownEqualUnknown((IPDPage*)pBeforePage, (IPDPage*)pSpread->m_pages->m_items[nBeforePageOnSpread]))
		{
			break;
		}
	}

	bool leftOfSpine = nBeforePageOnSpread < pSpread->m_spine;

	for (int i = 0; i < nPages; i++)
	{
		CComObject<CPDPage>* pPage;
		CComObject<CPDPage>::CreateInstance(&pPage);
		pPage->m_ownerSpread = static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)pSpread);
		pPage->m_pDocument = this;

		pPage->m_marginTop = m_marginTop;
		pPage->m_marginBottom = m_marginBottom;
		pPage->m_marginInside = m_marginInside;
		pPage->m_marginOutside = m_marginOutside;

		pPage->AddRef();
		pSpread->m_pages->m_items.InsertAt(nBeforePageOnSpread+i, (IPDPage*)pPage);

		pPage->AddRef();
		m_pages->m_items.InsertAt(nBeforePage+i, (IPDPage*)pPage);
	}

	{
		double offsetX = nPages * m_pageWidth;
		double x = nBeforePageOnSpread * m_pageWidth;

		for (int nlayergroup = 0; nlayergroup < pSpread->m_layergroups->/*m_children->*/m_items.GetSize(); nlayergroup++)
		{
			CPDObjectLayerGroup* pLayerGroup = (CPDObjectLayerGroup*)((IPDObjectLayerGroup*)(pSpread->m_layergroups->/*m_children->*/m_items[nlayergroup]));

			for (int i = 0; i < pLayerGroup->m_children->m_items.GetSize(); i++)
			{
				CComQIPtr<IPDObject> object = pLayerGroup->m_children->m_items[i];

				CComQIPtr<IPDObjectTransformable> transformable = object;
				if (transformable)
				{
					RectD xbounds;
					transformable->get_xbounds(&xbounds);

					if (xbounds.X+xbounds.Width/2 > x)
					{
						transformable->Move(offsetX, 0);
					}
				}
/*
				CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>(pLayerGroup->m_children->m_items[i]);

				RectD bounds;
				pObject->get_bounds(&bounds);	// TODO xbounds

				if (bounds.X+bounds.Width/2 > x)
				{
					pObject->Move(offsetX, 0);
				}
				*/
			}
		}
	}

	if (leftOfSpine) pSpread->m_spine += nPages;

	if (m_allowPagesToShuffle)
	{
		ShufflePages(pSpread);
	}

	return S_OK;
}

STDMETHODIMP CPDDocument::insertPagesAfter(long nPages, long nAfterPage)
{
	CComObject<CPDSpreadDocument>* pSpread = NULL;

	CPDPage* pAfterPage = (CPDPage*)(IPDPage*)m_pages->m_items[nAfterPage];
	pSpread = (CComObject<CPDSpreadDocument>*)pAfterPage->m_ownerSpread;

	for (int nAfterPageOnSpread = 0; nAfterPageOnSpread < pSpread->m_pages->m_items.GetSize(); nAfterPageOnSpread++)
	{
		if (IsUnknownEqualUnknown((IPDPage*)pAfterPage, (IPDPage*)pSpread->m_pages->m_items[nAfterPageOnSpread]))
		{
			break;
		}
	}

	bool leftOfSpine = nAfterPageOnSpread < pSpread->m_spine;

	for (int i = 0; i < nPages; i++)
	{
		CComObject<CPDPage>* pPage;
		CComObject<CPDPage>::CreateInstance(&pPage);
		pPage->m_ownerSpread = static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)pSpread);
		pPage->m_pDocument = this;

		pPage->m_marginTop = m_marginTop;
		pPage->m_marginBottom = m_marginBottom;
		pPage->m_marginInside = m_marginInside;
		pPage->m_marginOutside = m_marginOutside;

		pPage->AddRef();
		pSpread->m_pages->m_items.InsertAt(nAfterPageOnSpread+i+1, (IPDPage*)pPage);

		pPage->AddRef();
		m_pages->m_items.InsertAt(nAfterPage+i+1, (IPDPage*)pPage);
	}

	{
		double offsetX = nPages * m_pageWidth;
		double x = (nAfterPageOnSpread+1) * m_pageWidth;

		for (int nlayergroup = 0; nlayergroup < pSpread->m_layergroups->/*m_children->*/m_items.GetSize(); nlayergroup++)
		{
			CPDObjectLayerGroup* pLayerGroup = (CPDObjectLayerGroup*)((IPDObjectLayerGroup*)(pSpread->m_layergroups->/*m_children->*/m_items[nlayergroup]));

			for (int i = 0; i < pLayerGroup->m_children->m_items.GetSize(); i++)
			{
				//CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>(pLayerGroup->m_children->m_items[i]);

				CComQIPtr<IPDObjectTransformable> transformable = pLayerGroup->m_children->m_items[i];
				if (transformable)
				{
					RectD bounds;
					transformable->get_bounds(&bounds);	// TODO xbounds

					if (bounds.X+bounds.Width/2 > x)
					{
						transformable->Move(offsetX, 0);
					}
				}
			}
		}
	}

	if (leftOfSpine) pSpread->m_spine += nPages;

	if (m_allowPagesToShuffle)
	{
		ShufflePages(pSpread);
	}

	return S_OK;
}

STDMETHODIMP CPDDocument::appendSymbol(IPDSymbol *symbol)
{
	if (symbol == NULL) return E_INVALIDARG;

	symbol->AddRef();

	m_symbols->m_items.Add(symbol);

	FireOnChanged(NOTIFY_ADD, symbol, DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDDocument::getSymbolByName(BSTR name, IPDSymbol **pVal)
{
	if (pVal == NULL) return E_POINTER;

	for (int i = 0; i < m_symbols->m_items.GetSize(); i++)
	{
		CComQIPtr<IPDSymbol> symbol = m_symbols->m_items[i];

		BSTR bsymbolname;
		symbol->get_name(&bsymbolname);
		_bstr_t symbolname = _bstr_t(bsymbolname, false);

		if (!wcsicmp(symbolname, name))
		{
			(*pVal = symbol)->AddRef();
			return S_OK;
		}
	}

	*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDDocument::appendStory(IPDStory *story)
{
	if (story == NULL) return E_INVALIDARG;

	CComObject<CPDStory>* pStory = static_cast<CComObject<CPDStory>*>(story);

	pStory->AddRef();

	if (pStory->m_document)
	{
		//pStory->m_document->removeStory(story);
	}

	DWORD cookie;
	pStory->Advise(this, &cookie);

	pStory->m_document = this;
	m_stories->m_items.Add(story);

	DistributeStories();

	return S_OK;
}

STDMETHODIMP CPDDocument::removeStory(IPDStory *story)
{
	if (story == NULL) return E_INVALIDARG;

	for (int i = 0; i < m_stories->m_items.GetSize(); i++)
	{
		if (IsUnknownEqualUnknown(m_stories->m_items[i], story))
		{
			CPDStory* pStory = static_cast<CPDStory*>(story);

			pStory->Unadvise(this);
			pStory->m_document = NULL;

			story->Release();
			m_stories->m_items.RemoveAt(i);

			return S_OK;
		}
	}

	ATLASSERT(0);
	return S_OK;
}

STDMETHODIMP CPDDocument::createStory(IPDStory **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDStory>* pStory;
	CComObject<CPDStory>::CreateInstance(&pStory);
	if (pStory)
	{
		//pStory->m_document = this;

		*pVal = static_cast<IPDStory*>(pStory);
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDDocument::createObjectFrame(IPDObjectFrame **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDObjectFrame>* pObject;
	CComObject<CPDObjectFrame>::CreateInstance(&pObject);
	if (pObject)
	{
		pObject->m_pDocument = this;

		*pVal = static_cast<IPDObjectFrame*>(pObject);
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDDocument::createObjectGroup(GUID guid, IPDObjectGroup **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDObjectGroup>* pObject;
	CComObject<CPDObjectGroup>::CreateInstance(&pObject);
	if (pObject)
	{
		pObject->m_pDocument = this;

		if (guid == GUID_NULL)
			::CoCreateGuid(&pObject->m_uniqId);
		else
			pObject->m_uniqId = guid;

		*pVal = static_cast<IPDObjectGroup*>(pObject);
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDDocument::createContentGraphic(IPDContentGraphic **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDContentGraphic>* pContent;
	CComObject<CPDContentGraphic>::CreateInstance(&pContent);

	pContent->m_pDocument = this;

	*pVal = static_cast<IPDContentGraphic*>(pContent);
	(*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CPDDocument::createContentText(IPDContentText **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDContentText>* pObject;
	CComObject<CPDContentText>::CreateInstance(&pObject);
	if (pObject)
	{
		pObject->m_pDocument = this;

		*pVal = static_cast<IPDContentText*>(pObject);
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDDocument::createPathText(IPDPathText **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDPathText>* pObject;
	CComObject<CPDPathText>::CreateInstance(&pObject);
	if (pObject)
	{
		pObject->m_pDocument = this;

		*pVal = static_cast<IPDPathText*>(pObject);
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDDocument::getStoryById(GUID guid, IPDStory **pVal)
{
	if (pVal == NULL) return E_POINTER;

	for (int i = 0; i < m_stories->m_items.GetSize(); i++)
	{
		CPDStory* pStory = static_cast<CPDStory*>((IPDStory*)m_stories->m_items[i]);
		if (pStory->m_uniqId == guid)
		{
			*pVal = pStory;
			(*pVal)->AddRef();
			return S_OK;
		}
	}

	*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDDocument::getLayerByUniqId(GUID guid, IPDLayer **pVal)
{
	if (pVal == NULL) return E_POINTER;

	int i;

	for (i = 0; i < m_layers->m_items.GetSize(); i++)
	{
		CPDLayer* pLayer = static_cast<CPDLayer*>((IPDLayer*)(m_layers->m_items[i]));

		if (pLayer->m_uniqID == guid)
		{
			*pVal = pLayer;
			(*pVal)->AddRef();
			return S_OK;
		}
	}

	*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDDocument::getSpreadByUniqId(GUID guid, IPDSpread* *pVal)
{
	if (pVal == NULL) return E_POINTER;

	int i;

	for (i = 0; i < m_masterSpreads->m_items.GetSize(); i++)
	{
		IPDSpread* pSpread = (IPDSpread*)m_masterSpreads->m_items[i];

		GUID _guid;
		pSpread->get_uniqId(&_guid);

		if (_guid == guid)
		{
			*pVal = pSpread;
			(*pVal)->AddRef();
			return S_OK;
		}
	}

	for (i = 0; i < m_spreads->m_items.GetSize(); i++)
	{
		IPDSpread* pSpread = (IPDSpread*)m_spreads->m_items[i];

		GUID _guid;
		pSpread->get_uniqId(&_guid);

		if (_guid == guid)
		{
			*pVal = pSpread;
			(*pVal)->AddRef();
			return S_OK;
		}
	}

	*pVal = NULL;

	return S_OK;
}

void CPDDocument::DistributeStories()
{
	if (m_distributingStories == 0)
	{
		m_distributingStories++;

		for (int i = 0; i < m_stories->m_items.GetSize(); i++)
		{
			CPDStory* pStory = static_cast<CPDStory*>((IPDStory*)m_stories->m_items[i]);

			pStory->DistributeStory();
		}

		m_distributingStories--;
	}
}

STDMETHODIMP CPDDocument::get_showTextThreads(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_showTextThreads;
	return S_OK;
}

STDMETHODIMP CPDDocument::put_showTextThreads(VARIANT_BOOL newVal)
{
	if (m_showTextThreads != newVal)
	{
		m_showTextThreads = newVal;
		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	}
	return S_OK;
}

ILDOMElement* FindByTagName(ILDOMElement* parent, BSTR tagName, BOOL bDeep = TRUE);

ILDOMElement* FindByTagName(ILDOMElement* parent, BSTR tagName, BOOL bDeep/* = TRUE*/)
{
	CComQIPtr<ILDOMNode>	child;
	parent->get_firstChild(&child);

	while (child != NULL)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);

		if (nodeType == LNODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement> element = child;
			BSTR etagName;
			element->get_tagName(&etagName);
			_bstr_t ttagName = _bstr_t(etagName, false);

			if (!wcscmp(ttagName, tagName))
			{
				return element.Detach();
			}

		// Recurse
			if (bDeep)
			{
				CComQIPtr<ILDOMElement> element2 = FindByTagName(element, tagName);
				if (element2 != NULL)
					return element2.Detach();
			}
		}

		CComQIPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	return NULL;
}

STDMETHODIMP CPDDocument::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	node->putAttribute(L"pageWidth", variant_t(m_pageWidth));
	node->putAttribute(L"pageHeight", variant_t(m_pageHeight));
	node->putAttribute(L"facingPages", _variant_t(m_facingPages));
	node->putAttribute(L"allowPagesToShuffle", _variant_t(m_allowPagesToShuffle));
	node->putAttribute(L"viewDocumentGrid", _variant_t(m_viewDocumentGrid));
	node->putAttribute(L"showHiddenCharacters", _variant_t(m_showHiddenCharacters));
	node->putAttribute(L"nextLayerIndex", _variant_t(m_nextLayerIndex));
	node->putAttribute(L"nextMasterPrefix", _variant_t(m_nextMasterPrefix));
	node->putAttribute(L"marginTop", _variant_t(m_marginTop));
	node->putAttribute(L"marginBottom", _variant_t(m_marginBottom));
	node->putAttribute(L"marginInside", _variant_t(m_marginInside));
	node->putAttribute(L"marginOutside", _variant_t(m_marginOutside));
	node->putAttribute(L"columnNumber", _variant_t(m_columnNumber));
	node->putAttribute(L"columnGutter", _variant_t(m_columnGutter));

	node->serializeElement(L"swatches", (IPDSwatches*)m_swatches);

	node->putObjectMap(L"layers", m_layers);
	node->putObjectMap(L"stories", m_stories);

	node->putObjectMap(L"symbols", m_symbols);

	node->putObjectMap(L"spreads", m_spreads);
	node->putObjectMap(L"pages", m_pages);

	node->putObjectMap(L"masters", m_masterSpreads);
	node->putObjectMap(L"masterPages", m_masterPages);

	return S_OK;
}

STDMETHODIMP CPDDocument::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	_variant_t v;

	node->getAttribute(L"pageWidth", &v);
	m_pageWidth = v;

	node->getAttribute(L"pageHeight", &v);
	m_pageHeight = v;

	node->getAttribute(L"facingPages", &v);
	m_facingPages = v;

	node->getAttribute(L"allowPagesToShuffle", &v);
	m_allowPagesToShuffle = v;
	
	node->getAttribute(L"viewDocumentGrid", &v);
	m_viewDocumentGrid = v;

	node->getAttribute(L"showHiddenCharacters", &v);
	m_showHiddenCharacters = v;

	node->getAttribute(L"nextLayerIndex", &v);
	m_nextLayerIndex = v;

	node->getAttribute(L"nextMasterPrefix", &v);
	m_nextMasterPrefix = v;

	node->getAttribute(L"marginTop", &v);
	m_marginTop = v;

	node->getAttribute(L"marginBottom", &v);
	m_marginBottom = v;

	node->getAttribute(L"marginInside", &v);
	m_marginInside = v;

	node->getAttribute(L"marginOutside", &v);
	m_marginOutside = v;

	node->getAttribute(L"columnNumber", &v);
	m_columnNumber = v;

	node->getAttribute(L"columnGutter", &v);
	m_columnGutter = v;

	node->deserializeElement(L"swatches", (IPDSwatches*)m_swatches, NULL);

	CComObject<CObjectMap>* pMap;

	CComObject<CObjectMap>::CreateInstance(&pMap);
	if (pMap)
	{
		if (SUCCEEDED(node->getObjectMap(L"layers", pMap, GetUnknown())))
		{
			for (int i = 0; i < pMap->m_items.GetSize(); i++)
			{
				insertLayer((IPDLayer*)pMap->m_items[i], NULL);
			}
		}
		pMap->Release();
	}

	CComObject<CObjectMap>::CreateInstance(&pMap);
	if (pMap)
	{
		if (SUCCEEDED(node->getObjectMap(L"symbols", pMap, GetUnknown())))
		{
			for (int i = 0; i < pMap->m_items.GetSize(); i++)
			{
				appendSymbol((IPDSymbol*)pMap->m_items[i]);
			}
		}
		pMap->Release();
	}

	CComObject<CObjectMap>::CreateInstance(&pMap);
	if (pMap)
	{
		if (SUCCEEDED(node->getObjectMap(L"spreads", pMap, GetUnknown())))
		{
			for (int i = 0; i < pMap->m_items.GetSize(); i++)
			{
				insertSpread((IPDSpread*)pMap->m_items[i], NULL);
			}
		}
		pMap->Release();
	}

	node->getObjectMap(L"pages", m_pages, GetUnknown());

	return S_OK;
}

// ITextDocument
HRESULT STDMETHODCALLTYPE CPDDocument::GetName( 
   /* [retval][out] */ BSTR __RPC_FAR *pName)
{
	if (pName == NULL) return E_POINTER;
	*pName = m_filePath.copy();
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::GetSelection( 
   /* [retval][out] */ ITextSelection __RPC_FAR *__RPC_FAR *ppSel)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::GetStoryCount( 
   /* [retval][out] */ long __RPC_FAR *pCount)
{
	if (pCount == NULL) return E_POINTER;
	*pCount = m_stories->m_items.GetSize();
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocument::GetStoryRanges( 
   /* [retval][out] */ ITextStoryRanges __RPC_FAR *__RPC_FAR *ppStories)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::GetSaved( 
   /* [retval][out] */ long __RPC_FAR *pValue)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::SetSaved( 
   /* [in] */ long Value)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::GetDefaultTabStop( 
   /* [retval][out] */ float __RPC_FAR *pValue)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::SetDefaultTabStop( 
   /* [in] */ float Value)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::New( void)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::Open( 
   /* [in] */ VARIANT __RPC_FAR *pVar,
   /* [in] */ long Flags,
   /* [in] */ long CodePage)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::Save( 
   /* [in] */ VARIANT __RPC_FAR *pVar,
   /* [in] */ long Flags,
   /* [in] */ long CodePage)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::Freeze( 
   /* [retval][out] */ long __RPC_FAR *pCount)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::Unfreeze( 
   /* [retval][out] */ long __RPC_FAR *pCount)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::BeginEditCollection( void)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::EndEditCollection( void)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::Undo( 
   /* [in] */ long Count,
   /* [retval][out] */ long __RPC_FAR *prop)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::Redo( 
   /* [in] */ long Count,
   /* [retval][out] */ long __RPC_FAR *prop)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::Range( 
   /* [in] */ long cp1,
   /* [in] */ long cp2,
   /* [retval][out] */ ITextRange __RPC_FAR *__RPC_FAR *ppRange)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::RangeFromPoint( 
   /* [in] */ long x,
   /* [in] */ long y,
   /* [retval][out] */ ITextRange __RPC_FAR *__RPC_FAR *ppRange)
{
	return E_NOTIMPL;
}

#if 0
// IPersist
HRESULT STDMETHODCALLTYPE CPDDocument::GetClassID(/* [out] */ CLSID __RPC_FAR *pClassID)
{
	return S_OK;
}
#endif

// IPersistFile

HRESULT STDMETHODCALLTYPE CPDDocument::IsDirty( void)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocument::Load( 
   /* [in] */ LPCOLESTR pszFileName,
   /* [in] */ DWORD dwMode)
{
//	MessageBox(NULL, "Load", "", MB_OK);

	HRESULT hr;

	CComPtr<IArchive> ar;
	ar.CoCreateInstance(CLSID_Archive);

	CComPtr<IArchiveElement> node;
	if (SUCCEEDED(ar->Open(_bstr_t(pszFileName), 2, L"pddoc", &node)))
	{
		 hr = Deserialize(ar, node, NULL);
		 if (SUCCEEDED(hr))
		 {
			 m_filePath = pszFileName;
		 }
	}

	return hr;
}

HRESULT STDMETHODCALLTYPE CPDDocument::Save( 
   /* [unique][in] */ LPCOLESTR pszFileName,
   /* [in] */ BOOL fRemember)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocument::SaveCompleted( 
   /* [unique][in] */ LPCOLESTR pszFileName)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocument::GetCurFile( 
   /* [out] */ LPOLESTR __RPC_FAR *ppszFileName)
{
	CComPtr<IMalloc> malloc;
	CoGetMalloc(1, &malloc);
	if (malloc)
	{
		_bstr_t filename;

		if (m_filePath.length())
			filename = m_filePath;
		else
			filename = L"*.pddoc";

		BSTR b = (BSTR)malloc->Alloc((filename.length()+1)*2);
		wcscpy(b, (BSTR)m_filePath);
	}

	return S_OK;
}

// IPersistStorage
STDMETHODIMP CPDDocument::InitNew(/* [unique][in] */ IStorage *pStg)
{
	return S_OK;
}

STDMETHODIMP CPDDocument::Load(/* [unique][in] */ IStorage *pStg)
{
	return S_OK;
}

STDMETHODIMP CPDDocument::Save(/* [unique][in] */ IStorage *pStgSave, /* [in] */ BOOL fSameAsLoad)
{
	return S_OK;
}

STDMETHODIMP CPDDocument::SaveCompleted(/* [unique][in] */ IStorage *pStgNew)
{
	return S_OK;
}

STDMETHODIMP CPDDocument::HandsOffStorage( void)
{
	return S_OK;
}

// IOleDocument
HRESULT STDMETHODCALLTYPE CPDDocument::CreateView( 
		/* [unique][in] */ IOleInPlaceSite __RPC_FAR *pIPSite,
		/* [unique][in] */ IStream __RPC_FAR *pstm,
		/* [in] */ DWORD dwReserved,
		/* [out] */ IOleDocumentView __RPC_FAR *__RPC_FAR *ppView)
{
//	MessageBox(NULL, "CreateView", "", MB_OK);

	CComObject<CPDDocumentView>* pView;
	CComObject<CPDDocumentView>::CreateInstance(&pView);
	if (pView)
	{
		pView->m_document = this;//(CComObject<CMMSXHTMLActiveDocument>*)this;
		if (pIPSite)
		{
			pView->SetInPlaceSite(/*m_spInPlaceSite =*/ pIPSite);
		}

		pView->m_activeLayer = m_firstLayer;
		pView->m_activeSpread = m_firstSpread;

		/*
		if (m_pFrame)
		{
			m_pFrame->m_pUI = pView;
		}
		*/

		/*
		m_view = pView;
		*/

		*ppView = pView;
		(*ppView)->AddRef();
	}

//	MessageBox(NULL, "End CreateView", "", MB_OK);

	return S_OK;
}
		
HRESULT STDMETHODCALLTYPE CPDDocument::GetDocMiscStatus( 
		/* [out] */ DWORD __RPC_FAR *pdwStatus)
{
	if (pdwStatus == NULL) return E_POINTER;
	// Possible values
	/*
	DOCMISC_CANCREATEMULTIPLEVIEWS    =  1, 
    DOCMISC_SUPPORTCOMPLEXRECTANGLES  =  2, 
    DOCMISC_CANTOPENEDIT,             =  4, 
    DOCMISC_NOFILESUPPORT             =  8  
	 */
	*pdwStatus = 0;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocument::EnumViews( 
		/* [out] */ IEnumOleDocumentViews __RPC_FAR *__RPC_FAR *ppEnum,
		/* [out] */ IOleDocumentView __RPC_FAR *__RPC_FAR *ppView)
{
	MessageBox(NULL, "EnumViews", "", MB_OK);
	return S_OK;
}

// IOleObject

HRESULT STDMETHODCALLTYPE CPDDocument::SetClientSite( 
      /* [unique][in] */ IOleClientSite __RPC_FAR *pClientSite)
{
	MessageBox(NULL, "SetClientSite", "", MB_OK);
	m_spClientSite = pClientSite;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocument::GetClientSite( 
      /* [out] */ IOleClientSite __RPC_FAR *__RPC_FAR *ppClientSite)
{
	if (ppClientSite == NULL) return E_POINTER;

	*ppClientSite = m_spClientSite;
	(*ppClientSite)->AddRef();

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocument::SetHostNames( 
      /* [in] */ LPCOLESTR szContainerApp,
      /* [unique][in] */ LPCOLESTR szContainerObj)
{
//	::MessageBox(NULL, "SetHostNames", "", MB_OK);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocument::Close( 
      /* [in] */ DWORD dwSaveOption)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::SetMoniker( 
      /* [in] */ DWORD dwWhichMoniker,
      /* [unique][in] */ IMoniker __RPC_FAR *pmk)
{
	::MessageBox(NULL, "SetMoniker", "", MB_OK);

	LPMONIKER pTempMoniker;
	
	if(m_spClientSite == NULL)
		return E_FAIL;
	
	if(m_spClientSite->GetMoniker(OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, &pTempMoniker) != NOERROR)
		return E_FAIL;
	
	if(m_spOleAdviseHolder)
		m_spOleAdviseHolder->SendOnRename(pTempMoniker);
	
	LPRUNNINGOBJECTTABLE pRot;
	
	if(GetRunningObjectTable(0, &pRot) == NOERROR)
	{
		if(m_dwRegister)
			pRot->Revoke(m_dwRegister);
		
		pRot->Register(0, this->GetUnknown()/*m_pOleDoc*/, pTempMoniker, &m_dwRegister);
		
		pRot->Release();
	}

	return S_OK;
}
  
HRESULT STDMETHODCALLTYPE CPDDocument::GetMoniker( 
      /* [in] */ DWORD dwAssign,
      /* [in] */ DWORD dwWhichMoniker,
      /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppmk)
{
	if (m_spClientSite != NULL)
	{
		// get moniker from client site instead of from document
		//LPMONIKER lpMoniker = NULL;
		return m_spClientSite->GetMoniker(dwAssign, OLEWHICHMK_OBJFULL, ppmk);
		//return lpMoniker;
	}

	*ppmk = NULL;
	return E_FAIL;

	CUString m_strMoniker = "C:\\test_moniker.pddoc";

	return CreateFileMoniker(_bstr_t/*T2COLE*/(m_strMoniker), ppmk);

/*
	// use base class implementation if no registered moniker
	if (m_strMoniker.IsEmpty())
		return COleDocument::GetMoniker(nAssign);

	// return file moniker based on current path name
	LPMONIKER lpMoniker;
	CreateFileMoniker(T2COLE(m_strMoniker), &lpMoniker);
	return lpMoniker;
*/

	//::MessageBox(NULL, "GetMoniker", "", MB_OK);
	return E_FAIL;
}
  
HRESULT STDMETHODCALLTYPE CPDDocument::InitFromData( 
      /* [unique][in] */ IDataObject __RPC_FAR *pDataObject,
      /* [in] */ BOOL fCreation,
      /* [in] */ DWORD dwReserved)
{
	MessageBox(NULL, "InitFromData", "", MB_OK);
	return E_NOTIMPL;
}
  
HRESULT STDMETHODCALLTYPE CPDDocument::GetClipboardData( 
      /* [in] */ DWORD dwReserved,
      /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDataObject)
{
	return E_NOTIMPL;
}

#include "IPFrame.h"

HRESULT CPDDocument::ActivateInPlace()
{
	/*
	MessageBox(NULL, "ActivateInPlace", "", MB_OK);
	ATLASSERT(m_pInPlaceFrame == NULL);

	CComObject<CIPFrame>::CreateInstance(&m_pInPlaceFrame);
	if (m_pInPlaceFrame)
	{
		m_pInPlaceFrame->AddRef();

		CComQIPtr<IOleInPlaceFrame> spInPlaceFrame = m_spClientSite;

		HWND hParent;
		spInPlaceFrame->GetWindow(&hParent);

		m_pInPlaceFrame->Create(hParent, NULL, NULL, WS_VISIBLE | WS_CHILD);
	}

	MessageBox(NULL, "End ActivateInPlace", "", MB_OK);
	*/

	return S_OK;
}
  
HRESULT STDMETHODCALLTYPE CPDDocument::DoVerb( 
      /* [in] */ LONG iVerb,
      /* [unique][in] */ LPMSG lpmsg,
      /* [unique][in] */ IOleClientSite __RPC_FAR *pActiveSite,
      /* [in] */ LONG lindex,
      /* [in] */ HWND hwndParent,
      /* [unique][in] */ LPCRECT lprcPosRect)
{
	HRESULT  hr = E_FAIL;

	CUString msg;
	msg.Format("DoVerb %d", iVerb);
	//MessageBox(NULL, msg, "", MB_OK);
	
	if (pActiveSite != m_spClientSite)
	{
		//MessageBox(NULL, "!!", "", MB_OK);
	}

	switch (iVerb)
	{
	case OLEIVERB_PRIMARY:
	case OLEIVERB_UIACTIVATE:
		{
			CComQIPtr<IOleInPlaceSite> inPlaceSite = pActiveSite;

			CComQIPtr<IOleDocumentView> spView;
			if (m_pInPlaceFrame == NULL)
			{
				CreateView(inPlaceSite, NULL, 0, &spView);
			}
			else
			{
				spView = m_pInPlaceFrame->m_view;
				spView->SetInPlaceSite(inPlaceSite);
			}

		//	MessageBox(NULL, "1", "", MB_OK);

			CPDDocumentView* pView = (CPDDocumentView*)spView.p;

	//		MessageBox(NULL, "2", "", MB_OK);

			//if (iVerb == OLEIVERB_PRIMARY/*OLEIVERB_UIACTIVATE*/)
			pView->ActivateInPlace(hwndParent);

	//		MessageBox(NULL, "3", "", MB_OK);

			pView->UIActivate(TRUE);//ActivateUI();
		//	spView->Show(TRUE);//ActivateUI();

	//		MessageBox(NULL, "4", "", MB_OK);

			spView->SetRect((RECT*)lprcPosRect);

			//MessageBox(NULL, "2", "", MB_OK);

			/*
			if (m_pInPlaceFrame->GetParent() != hwndParent)
			{
				MessageBox(NULL, "parent !!", "", MB_OK);
			}
			*/

			//MessageBox(NULL, "2", "", MB_OK);

			hr = S_OK;
		}
		break;

	case OLEIVERB_SHOW:
		{
			//try to get the IOleDocumentSite pointer
			CComQIPtr<IOleDocumentSite> spOleDocSite = pActiveSite;
			if(spOleDocSite)
			{
				//passing NULL to this will cause the site to call our CreateView method
				hr = spOleDocSite->ActivateMe(NULL);
			}
			else
			{
				CComQIPtr<IOleInPlaceSite> inPlaceSite = m_spClientSite;
				if (inPlaceSite)
				{
#if 0
					CComQIPtr<IOleDocumentView> spView;
					if (m_pInPlaceFrame == NULL)
					{
						CreateView(inPlaceSite, NULL, 0, &spView);
					}
					else
					{
						spView = m_pInPlaceFrame->m_view;
						spView->SetInPlaceSite(inPlaceSite);
					}
#endif
#if 0
					if (spView)
					{
						spView->SetRect((RECT*)lprcPosRect);

						//if (iVerb == OLEIVERB_PRIMARY/*OLEIVERB_UIACTIVATE*/)
						spView->UIActivate(TRUE);//ActivateUI();
						spView->Show(TRUE);//ActivateUI();
					}
#endif
					hr = S_OK;
				}
				else
					MessageBox(NULL, "No inplacesite", "", MB_OK);
			}
		}
		break;
		
	case OLEIVERB_HIDE:
		{
//			MessageBox(NULL, "Hide", "", MB_OK);
			
			if (m_pInPlaceFrame)
			{
				CComQIPtr<IOleInPlaceObject> inPlaceObject = m_pInPlaceFrame->m_view;
				if (inPlaceObject)
				{
					ATLASSERT(inPlaceObject);

				//	inPlaceObject->UIDeactivate();

					inPlaceObject->InPlaceDeactivate();
				//inPlaceObject->Show(FALSE);

					ATLASSERT(m_pInPlaceFrame == NULL);

					/*
					if (m_pInPlaceFrame->m_hWnd)
					{
						::DestroyWindow(m_pInPlaceFrame->m_hWnd);
					}
					*/

				/*
				m_pInPlaceFrame->DestroyWindow();
				m_pInPlaceFrame->m_view.Release();
				m_pInPlaceFrame->Release();
				m_pInPlaceFrame = NULL;
				*/

					hr = S_OK;
				}
				else
				{
					::MessageBox(NULL, "##########", "", MB_OK);
				}
			}
			else
				::MessageBox(NULL, "##########", "", MB_OK);
		}
		break;

	default:
		break;
	}

	return hr;
}
  
HRESULT STDMETHODCALLTYPE CPDDocument::EnumVerbs(
      /* [out] */ IEnumOLEVERB __RPC_FAR *__RPC_FAR *ppEnumOleVerb)
{
	MessageBox(NULL, "EnumVerbs", "", MB_OK);
	return OLE_S_USEREG;
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::Update( void)
{
	return E_NOTIMPL;
}
  
HRESULT STDMETHODCALLTYPE CPDDocument::IsUpToDate( void)
{
	return E_NOTIMPL;
}
  
HRESULT STDMETHODCALLTYPE CPDDocument::GetUserClassID( 
      /* [out] */ CLSID __RPC_FAR *pClsid)
{
	MessageBox(NULL, "GetUserClassID", "", MB_OK);
	*pClsid = CLSID_PDDocument;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocument::GetUserType( 
      /* [in] */ DWORD dwFormOfType,
      /* [out] */ LPOLESTR __RPC_FAR *pszUserType)
{
	return OleRegGetUserType(CLSID_PDDocument, dwFormOfType, pszUserType);
//	MessageBox(NULL, "GetUserType", "", MB_OK);
//	return OLE_S_USEREG;
//	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::SetExtent( 
      /* [in] */ DWORD dwDrawAspect,
      /* [in] */ SIZEL __RPC_FAR *psizel)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::GetExtent( 
      /* [in] */ DWORD dwDrawAspect,
      /* [out] */ SIZEL __RPC_FAR *psizel)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::Advise( 
      /* [unique][in] */ IAdviseSink __RPC_FAR *pAdvSink,
      /* [out] */ DWORD __RPC_FAR *pdwConnection)
{
//	MessageBox(NULL, "Advise", "", MB_OK);

	// if we haven't made an OleAdviseHolder yet, make one.
	if(m_spOleAdviseHolder == NULL)
		CreateOleAdviseHolder(&m_spOleAdviseHolder);
	
	// pass this call onto the OleAdviseHolder.
	return m_spOleAdviseHolder->Advise(pAdvSink, pdwConnection);
}

HRESULT STDMETHODCALLTYPE CPDDocument::Unadvise( 
      /* [in] */ DWORD dwConnection)
{
//	MessageBox(NULL, "Unadvise", "", MB_OK);

	// pass on to OleAdviseHolder.
	return m_spOleAdviseHolder->Unadvise(dwConnection);
}

HRESULT STDMETHODCALLTYPE CPDDocument::EnumAdvise( 
      /* [out] */ IEnumSTATDATA __RPC_FAR *__RPC_FAR *ppenumAdvise)
{
	MessageBox(NULL, "EnumAdvise", "", MB_OK);
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocument::GetMiscStatus( 
      /* [in] */ DWORD dwAspect,
      /* [out] */ DWORD __RPC_FAR *pdwStatus)
{
	return OleRegGetMiscStatus(CLSID_PDDocument, dwAspect, pdwStatus);
//	MessageBox(NULL, "GetMiscStatus", "", MB_OK);
//	*pdwStatus = NULL;
//	return OLE_S_USEREG;
}
  
HRESULT STDMETHODCALLTYPE CPDDocument::SetColorScheme( 
      /* [in] */ LOGPALETTE __RPC_FAR *pLogpal)
{
	return E_NOTIMPL;
}

// IOleWindow
HRESULT STDMETHODCALLTYPE CPDDocument::GetWindow( 
            /* [out] */ HWND __RPC_FAR *phwnd)
{
	MessageBox(NULL, "PDDocument::GetWindow", "", MB_OK);
	if (phwnd == NULL) return E_POINTER;
	*phwnd = NULL;//m_hWnd;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocument::ContextSensitiveHelp( 
            /* [in] */ BOOL fEnterMode)
{
	MessageBox(NULL, "PDDocument::ContextSens", "", MB_OK);
	return S_OK;
}

// IOleInPlaceObject
HRESULT STDMETHODCALLTYPE CPDDocument::InPlaceDeactivate( void)
{
//	MessageBox(NULL, "PDDocument::InPlaceDeactivate", "", MB_OK);
			if (m_pInPlaceFrame)
			{
				CComQIPtr<IOleInPlaceObject> inPlaceObject = m_pInPlaceFrame->m_view;
				if (inPlaceObject)
				{
					ATLASSERT(inPlaceObject);

				//	inPlaceObject->UIDeactivate();

					inPlaceObject->InPlaceDeactivate();
				}
			}

	return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CPDDocument::UIDeactivate( void)
{
//	MessageBox(NULL, "PDDocument::UIDeactivate", "", MB_OK);
			if (m_pInPlaceFrame)
			{
				CComQIPtr<IOleInPlaceObject> inPlaceObject = m_pInPlaceFrame->m_view;
				if (inPlaceObject)
				{
					ATLASSERT(inPlaceObject);

				//	inPlaceObject->UIDeactivate();

					inPlaceObject->UIDeactivate();
				}
			}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocument::SetObjectRects( 
            /* [in] */ LPCRECT lprcPosRect,
            /* [in] */ LPCRECT lprcClipRect)
{
	MessageBox(NULL, "PDDocument::SetObjectRects", "", MB_OK);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocument::ReactivateAndUndo( void)
{
	MessageBox(NULL, "PDDocument::ReactivateAndUndo", "", MB_OK);
	return S_OK;
}

// IOleInPlaceActiveObject
STDMETHODIMP CPDDocument::TranslateAccelerator( 
            /* [in] */ LPMSG lpmsg)
{
	MessageBox(NULL, "PDDocument::TranslateAccelerator", "", MB_OK);

	// no accelerator table, return FALSE
	return S_FALSE;
}

STDMETHODIMP CPDDocument::OnFrameWindowActivate( 
           /* [in] */ BOOL fActivate)
{
	MessageBox(NULL, "PDDocument::OnFrameWindowActivate", "", MB_OK);
	return S_OK;
}

STDMETHODIMP CPDDocument::OnDocWindowActivate( 
            /* [in] */ BOOL fActivate)
{
	//If we are getting activated, merge our menus.
	if(fActivate)
	{
#if 0
		if(m_pOleDoc->m_pOleDocView)
		{
			m_pOleDoc->m_pOleDocView->MergeMenus();
		}
#endif
	}

	return S_OK;
}

STDMETHODIMP CPDDocument::ResizeBorder( 
            /* [in] */ LPCRECT prcBorder,
            /* [unique][in] */ IOleInPlaceUIWindow *pUIWindow,
            /* [in] */ BOOL fFrameWindow)
{
// TODO
	MessageBox(NULL, "PDDocument::ResizeBorder", "", MB_OK);

	return S_OK;
}

STDMETHODIMP CPDDocument::EnableModeless(/* [in] */ BOOL fEnable)
{
//	m_fEnableModeless = fEnable;
	MessageBox(NULL, "PDDocument::EnableModeless", "", MB_OK);

	return S_OK;
}

//IDataObject methods
STDMETHODIMP CPDDocument::DAdvise(  LPFORMATETC pFormatetc, 
											 DWORD advf,
											 LPADVISESINK pAdvSink, 
											 LPDWORD pdwConnection)
{
	//		  MessageBox(NULL, "IDataObject::DAdvise", "", MB_OK);
	
	// if no DataAdviseHolder has been created, then create one.
			if(m_spDataAdviseHolder == NULL)
				CreateDataAdviseHolder(&m_spDataAdviseHolder);
			
			if(m_spDataAdviseHolder)
			{
				// pass on to the DataAdviseHolder
				return m_spDataAdviseHolder->Advise(this, pFormatetc, advf, pAdvSink, pdwConnection);
			}
			
			return E_FAIL;
}
STDMETHODIMP CPDDocument::DUnadvise(DWORD)
{
	MessageBox(NULL, "IDataObject::DUnadvise", "", MB_OK);
	return E_NOTIMPL;
}
STDMETHODIMP CPDDocument::EnumDAdvise(LPENUMSTATDATA*)
{
	MessageBox(NULL, "IDataObject::EnumDAdvise", "", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CPDDocument::EnumFormatEtc(DWORD dwDirection, LPENUMFORMATETC* ppenumFormatetc)
{
			return OleRegEnumFormatEtc(CLSID_PDDocument, dwDirection, ppenumFormatetc);
			//MessageBox(NULL, "IDataObject::EnumFormatEtc", "", MB_OK);
			return E_NOTIMPL;
}

STDMETHODIMP CPDDocument::GetCanonicalFormatEtc(LPFORMATETC, LPFORMATETC)
{
	MessageBox(NULL, "IDataObject::GetCanonicalFormatEtc", "", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CPDDocument::GetData(FORMATETC* pFormatetc, STGMEDIUM* pMedium)
{
	if (pFormatetc->cfFormat == CF_TEXT && pFormatetc->tymed == TYMED_HGLOBAL)
	{
		pMedium->tymed = TYMED_HGLOBAL;
		
		CUString str = "Dette er en test";
		pMedium->hGlobal = (HGLOBAL)GlobalAlloc(GMEM_MOVEABLE, str.GetLength()+1);
		if (pMedium->hGlobal)
		{
			char* p = (char*)GlobalLock(pMedium->hGlobal);
			if (p)
			{
				strcpy(p, str);
				GlobalUnlock(pMedium->hGlobal);
			}
		}
		
		return S_OK;
	}
	else
	{
		//MessageBox(NULL, "IDataObject::GetData", "", MB_OK);
		return DV_E_FORMATETC;
	}
}

STDMETHODIMP CPDDocument::GetDataHere(LPFORMATETC, LPSTGMEDIUM)
{
	MessageBox(NULL, "IDataObject::GetDataHere", "", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CPDDocument::QueryGetData(LPFORMATETC)
{
	MessageBox(NULL, "IDataObject::QueryGetData", "", MB_OK);
	return E_NOTIMPL;
}

STDMETHODIMP CPDDocument::SetData(LPFORMATETC, LPSTGMEDIUM, BOOL)
{
	MessageBox(NULL, "IDataObject::SetData", "", MB_OK);
	return E_NOTIMPL;
}

BEGIN_CMD_MAP(CPDDocument)
// File
	CMD_HANDLER(ID_FILE_SAVE, OnFileSave)
	CMD_HANDLER(ID_FILE_DOCUMENTSETUP, OnDocumentSetup)

	CMD_HANDLER(ID_FILE_EXPORT_SVG, OnFileExportSVG)
	CMD_HANDLER(ID_FILE_EXPORT_PDF, OnFileExportPDF)

// Edit
	CMD_HANDLER(ID_EDIT_PREFERENCES, OnEditPreferences)

// View
	CMD_HANDLER(ID_VIEW_DOCUMENTGRID, OnViewDocumentGrid)
	CMD_UPDATE(ID_VIEW_DOCUMENTGRID, OnViewDocumentGridUpdate)
	CMD_HANDLER(ID_VIEW_SHOWTEXTTHREADS, OnViewShowTextThreads)
	CMD_UPDATE(ID_VIEW_SHOWTEXTTHREADS, OnViewShowTextThreadsUpdate)

// Type
	CMD_HANDLER(ID_TYPE_SHOWHIDDENCHARACTERS, OnTypeShowHiddenCharacters)
	CMD_UPDATE(ID_TYPE_SHOWHIDDENCHARACTERS, OnTypeShowHiddenCharactersUpdate)

// Layer
	CMD_HANDLER(ID_LAYERS_NEWLAYER, OnLayerNew)

// Pages
	CMD_HANDLER(ID_PAGES_NEWMASTER, OnPagesNewMaster)
	CMD_HANDLER(ID_PAGES_ALLOWPAGESTOSHUFFLE, OnAllowPagesToShuffle)
	CMD_UPDATE(ID_PAGES_ALLOWPAGESTOSHUFFLE, OnAllowPagesToShuffleUpdate)

// Edit
	CMD_HANDLER(ID_EDIT_UNDO, OnEditUndo)
	CMD_UPDATE(ID_EDIT_UNDO, OnEditUndoUpdate)
	CMD_HANDLER(ID_EDIT_REDO, OnEditRedo)
	CMD_UPDATE(ID_EDIT_REDO, OnEditRedoUpdate)

	CMD_HANDLER(ID_EDIT_DOCUMENTCOLORSETTINGS, OnDocumentColorSettings)

END_CMD_MAP()

LRESULT CPDDocument::OnViewShowTextThreads(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	put_showTextThreads(m_showTextThreads? VARIANT_FALSE: VARIANT_TRUE);
	return 0;
}

void CPDDocument::OnViewShowTextThreadsUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_showTextThreads? TRUE: FALSE);
}

LRESULT CPDDocument::OnTypeShowHiddenCharacters(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_showHiddenCharacters = (m_showHiddenCharacters)? VARIANT_FALSE: VARIANT_TRUE;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return 0;
}

void CPDDocument::OnTypeShowHiddenCharactersUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_showHiddenCharacters? TRUE: FALSE);
}

#include "MasterOptionsDlg.h"

LRESULT CPDDocument::OnPagesNewMaster(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	WCHAR buf[256];

	CMasterOptionsDlg dlg;
	dlg.m_numPages = 1;
	dlg.m_name = L"Master";

	swprintf(buf, L"%c", L'A'+m_nextMasterPrefix);
	dlg.m_prefix = buf;

	if (dlg.DoModal(GetMainHwnd()) == IDOK)
	{
		m_nextMasterPrefix++;

		CComObject<CPDSpreadMaster>* pSpread;
		CComObject<CPDSpreadMaster>::CreateInstance(&pSpread);
		if (pSpread)
		{
		//	pSpread->m_layergroups->m_spread = static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)pSpread);
		//	pSpread->m_layergroups->m_pDocument = this;
			pSpread->m_pDocument = this;
			pSpread->m_prefix = dlg.m_prefix;
			pSpread->m_name = dlg.m_name;
			pSpread->m_spine = 1;

			pSpread->AddRef();
			m_masterSpreads->m_items.Add((IPDSpread*)pSpread);

			CreateSpreadLayerGroups(static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)pSpread));

			ATLASSERT(pSpread->m_layergroups->/*m_children->*/m_items.GetSize() == 1);

			for (int i = 0; i < dlg.m_numPages; i++)
			{
				CComObject<CPDPage>* pPage;
				CComObject<CPDPage>::CreateInstance(&pPage);
				if (pPage != NULL)
				{
					pPage->m_pDocument = this;
					pPage->m_ownerSpread = static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)pSpread);

					pPage->m_marginTop = m_marginTop;
					pPage->m_marginBottom = m_marginBottom;
					pPage->m_marginInside = m_marginInside;
					pPage->m_marginOutside = m_marginOutside;
					pPage->m_columnNumber = m_columnNumber;
					pPage->m_columnGutter = m_columnGutter;

					pPage->AddRef();
					pSpread->m_pages->m_items.Add((IPDPage*)pPage);

					pPage->AddRef();
					m_masterPages->m_items.Add((IPDPage*)pPage);
				}
			}
		}

	// TODO notify
	}

	return 0;
}

#include "PrefsGridsDlg.h"
#include "PrefsUnitsDlg.h"
#include "PrefsTransparencyDlg.h"
#include "PrefsClipboardDlg.h"

LRESULT CPDDocument::OnEditPreferences(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CPropertySheet* sheet = new CPropertySheet("Preferences", 0, GetMainHwnd());

	CPrefsUnitsDlg	units;

	CPrefsGridsDlg grids;
	grids.m_targetObject = this;

	CPrefsTransparencyDlg transp;
	transp.m_targetObject = this;

	CPrefsClipboardDlg clipboard;
	clipboard.m_targetObject = gIApp;

	sheet->AddPage(grids);
	sheet->AddPage(units);
	sheet->AddPage(transp);
	sheet->AddPage(clipboard);

	sheet->DoModal();

	return 0;
}

#pragma comment(lib, "icmui.lib")

TCHAR monitorProfile[MAX_PATH] = {0};
TCHAR printerProfile[MAX_PATH] = {0};
TCHAR targetProfile[MAX_PATH] = {0};

LRESULT CPDDocument::OnDocumentColorSettings(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	COLORMATCHSETUP cms = {0};
	cms.dwSize = sizeof(cms);
	cms.dwVersion = COLOR_MATCH_VERSION;
	cms.dwFlags = CMS_DISABLEICM;
	cms.hwndOwner = GetMainHwnd();
	cms.pSourceName = NULL;
	cms.pDisplayName = NULL;
	cms.pPrinterName = NULL;
	cms.dwRenderIntent = 0;
	cms.dwProofingIntent = 0;

	cms.pMonitorProfile = monitorProfile;
	cms.ccMonitorProfile = sizeof(monitorProfile);

	cms.pPrinterProfile = printerProfile;
	cms.ccPrinterProfile = sizeof(printerProfile);

	cms.pTargetProfile = targetProfile;
	cms.ccTargetProfile = sizeof(targetProfile);

	cms.lpfnHook = NULL;
	cms.lParam = 0L;
	cms.lpfnApplyCallback = NULL;
	cms.lParamApplyCallback = 0L;

	if (SetupColorMatching(&cms))
	{
		MessageBox(GetMainHwnd(), monitorProfile, "monitor", MB_OK);
		MessageBox(GetMainHwnd(), printerProfile, "printer", MB_OK);
		MessageBox(GetMainHwnd(), targetProfile, "target", MB_OK);
	}

	return 0;
}

LRESULT CPDDocument::OnFileSave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
												"PageDesigner Document (*.pddoc)\0*.pddoc\0"
												);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, "");	// Initial filename

	TCHAR curdir[MAX_PATH];
	GetCurrentDirectory(sizeof(curdir), curdir);

	HWND hwnd = GetMainHwnd();

	OPENFILENAME	ofn = {0};
	ofn.lStructSize = OPENFILENAME_SIZE_VERSION_400A;//sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.hInstance = _Module.m_hInst;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = sizeof(sbuffer);
	ofn.lpstrInitialDir = curdir;
	ofn.lpstrFilter = FilesFilter;
	ofn.lpstrDefExt = ".pddoc";
	
	if (GetSaveFileName(&ofn))
	{
		CComPtr<IArchive> ar;
		ar.CoCreateInstance(CLSID_Archive);

		CComPtr<IArchiveElement> node;
		if (SUCCEEDED(ar->Open(_bstr_t(sbuffer), 1, L"pddoc", &node)))
		{
			Serialize(ar, node);
		}

		/*
		LPTSTR ext = PathFindExtension(sbuffer);

		CComPtr<IDOMDocument> document;
		document.CoCreateInstance(CLSID_LDOMDocument);

		VARIANT_BOOL bloaded;
		document->loadXML(L"<?xml version=\"1.0\" ?><pddoc/>", &bloaded);

		CComPtr<IDOMElement> documentElement;
		document->get_documentElement(&documentElement);

		saveAsXML(document, documentElement);

		VARIANT_BOOL bsaved;
		document->save(_bstr_t(sbuffer), &bsaved);
		*/
	}

	return 0;
}

#include "SVGExport.h"

LRESULT CPDDocument::OnFileExportSVG(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	static LPCTSTR FilesFilter = _T(	"SVG (*.svg)\0*.svg\0"
												);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, "");	// Initial filename

	TCHAR curdir[MAX_PATH];
	GetCurrentDirectory(sizeof(curdir), curdir);

	HWND hwnd = GetMainHwnd();

	OPENFILENAME	ofn = {0};
	ofn.lStructSize = OPENFILENAME_SIZE_VERSION_400A;//sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.hInstance = _Module.m_hInst;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = sizeof(sbuffer);
	ofn.lpstrInitialDir = curdir;
	ofn.lpstrFilter = FilesFilter;
	ofn.lpstrDefExt = ".svg";

	if (GetSaveFileName(&ofn))
	{
#if 0
		CSVGExport* pSVG = new CSVGExport;
		if (pSVG)
		{
			pSVG->Export(_bstr_t(sbuffer), m_firstSpread);

			delete pSVG;
		}
#endif
	}

	return 0;
}

#include "PDFExport.h"

LRESULT CPDDocument::OnFileExportPDF(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	static LPCTSTR FilesFilter = _T(	"PDF (*.pdf)\0*.pdf\0"
												);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, "");	// Initial filename

	TCHAR curdir[MAX_PATH];
	GetCurrentDirectory(sizeof(curdir), curdir);

	HWND hwnd = GetMainHwnd();

	OPENFILENAME	ofn = {0};
	ofn.lStructSize = OPENFILENAME_SIZE_VERSION_400A;//sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.hInstance = _Module.m_hInst;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = sizeof(sbuffer);
	ofn.lpstrInitialDir = curdir;
	ofn.lpstrFilter = FilesFilter;
	ofn.lpstrDefExt = ".pdf";

	if (GetSaveFileName(&ofn))
	{
		CPDFExport* pPDF = new CPDFExport;
		if (pPDF)
		{
			HRESULT hr = pPDF->Export(sbuffer, this);

			delete pPDF;

			if (FAILED(hr))
			{
				CUString msg;
				msg.Format("Couldn't save PDF file\n%s", sbuffer);

				MessageBox(GetMainHwnd(), msg, "PageDesigner", MB_OK);
			}
		}
	}

	return 0;
}

LRESULT CPDDocument::OnAllowPagesToShuffle(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (!m_allowPagesToShuffle)
	{
		CArray<CPDSpreadDocument*,CPDSpreadDocument*> spreadsArr;

		CPDSpreadDocument* pSpread = m_firstSpread;
		while (pSpread)
		{
			if (pSpread->m_pages->m_items.GetSize() > 2)
			{
				spreadsArr.Add(pSpread);
			}

			pSpread = pSpread->m_nextSpread;
		}
		
		if (spreadsArr.GetSize() > 0)
		{
			int id = MessageBox(GetMainHwnd(), "Maintain current number of pages on each spread?", "PageDesigner", MB_YESNOCANCEL);

			if (id == IDYES)
			{
				for (int i = 0; i < spreadsArr.GetSize(); i++)
				{
					spreadsArr[i]->m_keepSpreadTogether = VARIANT_TRUE;
				}
			}
			else if (id == IDCANCEL)
			{
				return S_OK;
			}
		}
	}

	m_allowPagesToShuffle = m_allowPagesToShuffle? VARIANT_FALSE: VARIANT_TRUE;

	if (m_allowPagesToShuffle)
	{
		ShufflePages(m_firstSpread);
	}

	return 0;
}

void CPDDocument::OnAllowPagesToShuffleUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_allowPagesToShuffle);
}

LRESULT CPDDocument::OnViewDocumentGrid(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_viewDocumentGrid = m_viewDocumentGrid? VARIANT_FALSE: VARIANT_TRUE;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return 0;
}

void CPDDocument::OnViewDocumentGridUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_viewDocumentGrid);
}

void CPDDocument::RemoveLayerGroupOnSpreadList(CObjectMap* spreads, IPDLayer* layer)
{
	for (int i = 0; i < spreads->m_items.GetSize(); i++)
	{
		CPDSpreadImpl<IPDSpread>* pSpread = static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)spreads->m_items[i]);

		CComPtr<IPDObjectLayerGroup> layergroup;
		pSpread->getLayerGroupFromLayer(layer, &layergroup);

		pSpread->removeLayerGroup(layergroup);
	}
}

void CPDDocument::InsertLayerGroupOnSpreadList(CObjectMap* spreads, CPDLayer* pLayer)
{
	for (int i = 0; i < spreads->m_items.GetSize(); i++)
	{
		CPDSpreadImpl<IPDSpread>* pSpread = static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)spreads->m_items[i]);

	// Create a layergroup on the spread
		CComObject<CPDObjectLayerGroup>* layergroup;
		CComObject<CPDObjectLayerGroup>::CreateInstance(&layergroup);
		if (layergroup)
		{
			CoCreateGuid(&layergroup->m_uniqId);

			layergroup->m_pDocument = this;
			layergroup->m_layer = pLayer;
			layergroup->m_guides->m_layer = pLayer;

			pSpread->insertLayerGroup(layergroup, NULL);
		}
		else
			ATLASSERT(0);
	}
}

void CPDDocument::ArrangeLayerGroupOnSpreadList(CObjectMap* spreads, IPDLayer* layer, IPDLayer* before)
{
	for (int i = 0; i < spreads->m_items.GetSize(); i++)
	{
		CPDSpreadImpl<IPDSpread>* pSpread = static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)spreads->m_items[i]);

		CComPtr<IPDObjectLayerGroup> layergroup;
		pSpread->getLayerGroupFromLayer(layer, &layergroup);

		CComPtr<IPDObjectLayerGroup> beforelayergroup;
		pSpread->getLayerGroupFromLayer(before, &beforelayergroup);

		pSpread->insertLayerGroup(layergroup, beforelayergroup);
		//static_cast<CPDObjectLayerGroup*>(layergroup.p)->m_layer = static_cast<CPDLayer*>(layer);
	}
}

STDMETHODIMP CPDDocument::insertLayerBefore(IPDLayer *layer, IPDLayer *before)
{
	insertLayer(layer, before);

	ArrangeLayerGroupOnSpreadList(m_spreads, layer, before);
	ArrangeLayerGroupOnSpreadList(m_masterSpreads, layer, before);

	return S_OK;
}

#include "LayerOptionsDlg.h"

LRESULT CPDDocument::OnLayerNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComObject<CPDLayer>* pLayer;
	CComObject<CPDLayer>::CreateInstance(&pLayer);
	if (pLayer)
	{
		pLayer->AddRef();

		pLayer->m_color = LayerColors[m_nextLayerIndex % NUMLAYERCOLORS];

		WCHAR buf[64];
		swprintf(buf, L"Layer %d", ++m_nextLayerIndex);
		pLayer->m_name = buf;

		CLayerOptionsDlg dlg;
		dlg.m_targetObjects.Add(pLayer);

		if (dlg.DoModal(GetMainHwnd()) == IDOK)
		{
			DWORD cookie;
			pLayer->Advise(this, &cookie);

		// Add layer to document
			insertLayer(pLayer, NULL);

		// Add layer to all the spreads
			InsertLayerGroupOnSpreadList(m_masterSpreads, pLayer);
			InsertLayerGroupOnSpreadList(m_spreads, pLayer);

			FireOnChanged(NOTIFY_ADD, pLayer->GetUnknown(), DISPID_UNKNOWN);
		}

		pLayer->Release();
	}
	else
	{
		MessageBox(GetMainHwnd(), "Couldn't create layer", "PageDesigner", MB_OK);
	}

	return 0;
}

HRESULT CPDDocument::removeLayer(IPDLayer *layer)
{
	CComObject<CPDLayer>* pLayer = static_cast<CComObject<CPDLayer>*>(layer);

	for (int i = 0; i < m_layers->m_items.GetSize(); i++)
	{
		if (IsUnknownEqualUnknown(m_layers->m_items[i], layer))
		{
			if (pLayer->m_previousSibling != NULL)
				pLayer->m_previousSibling->m_nextSibling = pLayer->m_nextSibling;
			else
				m_firstLayer = pLayer->m_nextSibling;

			if (pLayer->m_nextSibling != NULL)
				pLayer->m_nextSibling->m_previousSibling = pLayer->m_previousSibling;
			else
				m_lastLayer = pLayer->m_previousSibling;

			pLayer->m_previousSibling = NULL;
			pLayer->m_nextSibling = NULL;
			pLayer->m_pDocument = NULL;

			m_layers->m_items.RemoveAt(i);

			FireOnChanged(NOTIFY_REMOVE, layer, DISPID_UNKNOWN);

			layer->Release();

			return S_OK;
		}
	}

	return E_FAIL;
}

STDMETHODIMP CPDDocument::deleteLayer(IPDLayer *layer)
{
// Remove layer from all the spreads
	RemoveLayerGroupOnSpreadList(m_masterSpreads, layer);
	RemoveLayerGroupOnSpreadList(m_spreads, layer);

	CComQIPtr<INotifySend> cp = layer;
	cp->Unadvise(this);

	return removeLayer(layer);
}

LRESULT CPDDocument::OnEditUndo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_undoManager->UndoTo(NULL);
	return 0;
}

LRESULT CPDDocument::OnEditRedo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_undoManager->RedoTo(NULL);
	return 0;
}

void CPDDocument::OnEditUndoUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	BSTR bdescription;
	HRESULT hr = m_undoManager->GetLastUndoDescription(&bdescription);
	if (hr == S_OK)
	{
		bEnable = TRUE;
		pCmdUI->SetText(bdescription);
		SysFreeString(bdescription);
	}
	else
	{
		pCmdUI->SetText(L"Can't Undo");
	}

	pCmdUI->Enable(bEnable);
}

void CPDDocument::OnEditRedoUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	BSTR bdescription;
	HRESULT hr = m_undoManager->GetLastRedoDescription(&bdescription);
	if (hr == S_OK)
	{
		bEnable = TRUE;
		pCmdUI->SetText(bdescription);
		SysFreeString(bdescription);
	}
	else
	{
		pCmdUI->SetText(L"Can't Redo");
	}

	pCmdUI->Enable(bEnable);
}

#include "PDUndoUnitImpl.h"

class ATL_NO_VTABLE CUndoDocumentSetup : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CPDUndoUnitImpl
{
public:
	CUndoDocumentSetup()
	{
		m_pDocument = NULL;
	}

	CPDDocument*	m_pDocument;

	double m_pageWidth;
	double m_pageHeight;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUndoDocumentSetup)
	COM_INTERFACE_ENTRY(IOleUndoUnit)
END_COM_MAP()

public:

// IOleUndoUnit
	STDMETHOD(GetDescription)(/* [out] */ BSTR __RPC_FAR *pBstr)
	{
		*pBstr = SysAllocString(L"Document Setup");
		return S_OK;
	}

	STDMETHOD(Do)(/* [in] */ IOleUndoManager __RPC_FAR *pUndoManager)
	{
		double oldpageWidth = m_pDocument->m_pageWidth;
		double oldpageHeight = m_pDocument->m_pageHeight;

		m_pDocument->m_pageWidth = m_pageWidth;
		m_pDocument->m_pageHeight = m_pageHeight;

		m_pageWidth = oldpageWidth;
		m_pageHeight = oldpageHeight;

		if (m_bRedo)
		{
		}
		else
		{
		}

		m_pDocument->Fire_DocumentSetupChanged();

		m_bRedo = !m_bRedo;
		pUndoManager->Add(this);

		return S_OK;
	}
};

#include "DocumentSetupDlg.h"

LRESULT CPDDocument::OnDocumentSetup(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CDocumentSetupDlg dlg;

	dlg.m_numPages = m_pages->m_items.GetSize();
	dlg.m_pageWidth = m_pageWidth;
	dlg.m_pageHeight = m_pageHeight;
	dlg.m_facingPages = m_facingPages? TRUE: FALSE;

	if (dlg.DoModal(GetMainHwnd()) == IDOK)
	{
		m_pageWidth = dlg.m_pageWidth;
		m_pageHeight = dlg.m_pageHeight;

		if (m_pages->m_items.GetSize() != dlg.m_numPages)
		{
		}

		if ((m_facingPages == 0) != (dlg.m_facingPages == 0))
		{
			m_facingPages = dlg.m_facingPages? VARIANT_TRUE: VARIANT_FALSE;

		// TODO	ShufflePages
			ShufflePages(m_firstSpread);
		}
	}

#if 0
	HINSTANCE hLib = LoadLibrary("C:\\mmsx\\mmstudioplugins\\DOMCOREMOD.dll");
	if (hLib)
	{
		HTMLModalDialogProc HTMLModalDialog = (HTMLModalDialogProc)GetProcAddress(hLib, "HTMLModalDialog");
		if (HTMLModalDialog)
		{
			CComQIPtr<IDOMDocument> xmldoc;
			xmldoc.CoCreateInstance(CLSID_DOMDocument);
			xmldoc->put_async(VARIANT_FALSE);
			VARIANT_BOOL success;
			xmldoc->loadXML(L"<documentsetup/>", &success);

			CComQIPtr<IDOMElement> element;
			xmldoc->get_documentElement(&element);

			WCHAR buf[64];

			swprintf(buf, L"%g", m_pageWidth);
			element->setAttribute(L"pageWidth", buf);

			swprintf(buf, L"%g", m_pageHeight);
			element->setAttribute(L"pageHeight", buf);

			_variant_t arg = (IDispatch*)element.p;

			_variant_t result;
			HTMLModalDialog(GetMainHwnd(), L"C:\\MMStudio\\pd_documentsetup.html", &arg, L"", &result);
			if (TRUE)
			{
				BOOL bDo = FALSE;

				CComObject<CUndoDocumentSetup>* pUndo;
				CComObject<CUndoDocumentSetup>::CreateInstance(&pUndo);
				if (pUndo)
				{
					pUndo->AddRef();
					pUndo->m_pDocument = this;

					pUndo->m_pageWidth = m_pageWidth;
					pUndo->m_pageHeight = m_pageHeight;

					m_undoManager->Add(pUndo);

					bDo = TRUE;
				}
				else
				{
					int id = MessageBox(GetMainHwnd(), "Out of memory, unable to undo this later, still go ahead?", "PageDesigner", MB_YESNO);
					if (id == IDYES) bDo = TRUE;
				}

				if (bDo)
				{
					BSTR b;

					element->getAttribute(L"pageWidth", &b);
					m_pageWidth = atol(_bstr_t(b, false));

					element->getAttribute(L"pageHeight", &b);
					m_pageHeight = atol(_bstr_t(b, false));

					Fire_DocumentSetupChanged();
				}
			}
		}
		else
		{
			MessageBox(GetMainHwnd(), "Couldn't find proc", "WebEditor", MB_OK);
		}

		FreeLibrary(hLib);
	}
	else
	{
		MessageBox(GetMainHwnd(), "Couldn't load library", "WebEditor", MB_OK);
	}
#endif
	return 0;
}

STDMETHODIMP CPDDocument::GetClassID(CLSID *pClassID)
{
	*pClassID = CLSID_PDDocument;
	return S_OK;
}

STDMETHODIMP CPDDocument::get_firstSpread(IPDSpreadDocument **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_firstSpread;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDDocument::get_lastSpread(IPDSpreadDocument **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_lastSpread;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDDocument::setColumns(long ncolumns, double gutter, double width, VARIANT_BOOL fixedWidth)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDDocument::removeSubObjects()
{
	// TODO: Add your implementation code here

	return S_OK;
}
