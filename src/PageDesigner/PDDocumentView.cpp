#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "ole.h"
#include "..\OleDataObject.h"

// TODO remove this
#include "ObjectMap.h"
#include "PDDocument.h"
#include "PageDesignerApp.h"
#include "PageDesignerFrame.h"
extern CPageDesignerApp* gApp;
////////

#include "PDDocumentView.h"

#include "..\gm\gmMat3.h"	// TODO remove

#include "PathSelection.h"
#include "PDObjectSelected.h"

#include "PDDocumentViewUndo.h"

class ClipboardFormats
{
public:
	ClipboardFormats();

	UINT cfPng;
	UINT cfJpeg;
	UINT cfGif;

	UINT cfRichTextFormat;
};

ClipboardFormats::ClipboardFormats()
{
	cfPng = RegisterClipboardFormat("PNG");
	cfJpeg = RegisterClipboardFormat("JFIF");
	cfGif = RegisterClipboardFormat("GIF");

	cfRichTextFormat = RegisterClipboardFormat("Rich Text Format");
}

ClipboardFormats _clipboardFormats;

#include "PDRenderer.h"
#include "PDMatrix.h"
#include "PDColor.h"
#include "PDObjectWithAppearanceAndStrokeFillImpl.h"

class ATL_NO_VTABLE CPDObjectSelection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPDObjectSelection,
	public CPDObjectWithAppearanceAndStrokeFillImpl<CPDObjectSelection>,
	public CNotifyGetImpl<CPDObjectSelection>,
	public CNotifySendImpl<CPDObjectSelection>
{
public:
	CPDObjectSelection()
	{
		m_matrix = NULL;

		m_view = NULL;
	}

	CPDDocumentView* m_view;

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CPDObjectWithAppearanceAndStrokeFillImpl<CPDObjectSelection>::FinalConstruct();
		if (FAILED(hr)) return hr;

		/*
		// Default
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
				m_subObjects->m_items.Add(fill.Detach());
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
				m_subObjects->m_items.Add(stroke.Detach());
			}
		}
		*/

		return 0;
	}

	void FinalRelease()
	{
		CPDObjectWithAppearanceAndStrokeFillImpl<CPDObjectSelection>::FinalRelease();
	}

// Need the following because of IPDObjectWithAppearance (TODO, remove)
	double m_scaleX, m_scaleY;
	double m_opacity;
	RectD m_filterRect;
	CComObject<CPDMatrix>* m_matrix;
//

	BOOL m_bMixedAppearance;

	long m_objectType;

//	void CopyDefaultProperties(IPDObjectFrame* frame);

DECLARE_PROTECT_FINAL_CONSTRUCT()

	void FromTargets(CPDObjectSelected* *objects, int count)
	{
		m_bMixedAppearance = FALSE;

		{
			RemoveAllSubObjects();//m_subObjects->m_items.RemoveAll();	// TODO, also release
			if (m_appearance)
			{
				m_appearance->Unadvise(this);
				m_appearance->Release();
				m_appearance = NULL;
			}
		}

		if (count == 0)	// Copy from document
		{
			m_objectType = 0;	// No selection

			CComQIPtr<IPDObjectWithAppearance> withappearance = m_view->m_document;

			CComPtr<IPDAppearance> appearance;
			withappearance->get_appearance(&appearance);

			appearance->clone((IPDAppearance**)&m_appearance);
			DWORD cookie;
			m_appearance->Advise(this, &cookie);

			CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> withStrokeFill = withappearance;
			if (withStrokeFill)
			{
				CComPtr<IObjectMap> subObjects;
				withStrokeFill->get_subObjects(&subObjects);

				long nsubObjects;
				subObjects->get_length(&nsubObjects);

				CComPtr<IPDObjectStroke> activeStroke;
				withStrokeFill->get_activeStroke(&activeStroke);

				CComPtr<IPDObjectFill> activeFill;
				withStrokeFill->get_activeFill(&activeFill);

				for (int i = 0; i < nsubObjects; i++)
				{
					CComPtr<IPDObjectWithBrush> withBrush;
					subObjects->item(i, (IUnknown**)&withBrush);

					CComPtr<IPDObjectWithBrush> clonewithBrush;
					withBrush->clone((IPDObject**)&clonewithBrush);

					if (IsUnknownEqualUnknown(withBrush, activeStroke))
						m_activeStroke = (IPDObjectStroke*)clonewithBrush.p;
					else if (IsUnknownEqualUnknown(withBrush, activeFill))
						m_activeFill = (IPDObjectFill*)clonewithBrush.p;

					appendSubObject(clonewithBrush);
				}
			}
		}
		else
		{
			int i;

			// Copy appearance of first object
			{
				CComPtr<IPDObjectUnknown> object = objects[0]->m_object;

				PDObjectType objectType;
				object->get_objectType(&objectType);

				m_objectType = objectType;

				CComQIPtr<IPDObjectWithAppearance> withappearance = object;

				CComPtr<IPDAppearance> appearance;
				withappearance->get_appearance(&appearance);

				appearance->clone((IPDAppearance**)&m_appearance);
				DWORD cookie;
				m_appearance->Advise(this, &cookie);

				CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> withStrokeFill = object;
				if (withStrokeFill)
				{
					CComPtr<IObjectMap> subObjects;
					withStrokeFill->get_subObjects(&subObjects);

					long nsubObjects;
					subObjects->get_length(&nsubObjects);

					CComPtr<IPDObjectStroke> activeStroke;
					withStrokeFill->get_activeStroke(&activeStroke);

					CComPtr<IPDObjectFill> activeFill;
					withStrokeFill->get_activeFill(&activeFill);

					for (int i = 0; i < nsubObjects; i++)
					{
						CComPtr<IPDObjectWithBrush> withBrush;
						subObjects->item(i, (IUnknown**)&withBrush);

						CComPtr<IPDObjectWithBrush> clonewithBrush;
						withBrush->clone((IPDObject**)&clonewithBrush);

						if (IsUnknownEqualUnknown(withBrush, activeStroke))
							m_activeStroke = (IPDObjectStroke*)clonewithBrush.p;
						else if (IsUnknownEqualUnknown(withBrush, activeFill))
							m_activeFill = (IPDObjectFill*)clonewithBrush.p;

						appendSubObject(clonewithBrush.Detach());
					}
				}
			}

		// Stroke
			for (i = 1; i < count; i++)
			{
				CComPtr<IPDObjectUnknown> object = objects[i]->m_object;

				CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> withStrokeFill = object;
				if (withStrokeFill)
				{
					CComPtr<IPDBrush> brush;
					m_activeStroke->get_brush(&brush);

					CComPtr<IPDObjectStroke> activeStroke;
					withStrokeFill->get_activeStroke(&activeStroke);
					CComPtr<IPDBrush> brush2;
					activeStroke->get_brush(&brush2);

					brush->setCommon(brush2);
				}
			}

		// Fill
			for (i = 1; i < count; i++)
			{
				CComPtr<IPDObjectUnknown> object = objects[i]->m_object;

				CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> withStrokeFill = object;
				if (withStrokeFill)
				{
					CComPtr<IPDBrush> brush;
					m_activeFill->get_brush(&brush);

					CComPtr<IPDObjectFill> activeFill;
					withStrokeFill->get_activeFill(&activeFill);
					CComPtr<IPDBrush> brush2;
					activeFill->get_brush(&brush2);

					brush->setCommon(brush2);
				}
			}

#if 0
			for (i = 0; i < count; i++)
			{
				CComPtr<IPDObjectUnknown> object = objects[i]->m_object;

				PDObjectType objectType;
				object->get_objectType(&objectType);

				if (i == 0)
				{
					m_objectType = objectType;

					CComQIPtr<IPDObjectWithAppearance> withappearance = object;

					CComPtr<IPDAppearance> appearance;
					withappearance->get_appearance(&appearance);

					appearance->clone((IPDAppearance**)&m_appearance);

					CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> withStrokeFill = object;
					if (withStrokeFill)
					{
						CComPtr<IObjectMap> subObjects;
						withStrokeFill->get_subObjects(&subObjects);

						long nsubObjects;
						subObjects->get_length(&nsubObjects);

						for (int i = 0; i < nsubObjects; i++)
						{
							CComPtr<IPDObjectWithBrush> withBrush;
							subObjects->item(i, (IUnknown**)&withBrush);

							CComPtr<IPDObjectWithBrush> clonewithBrush;
							withBrush->clone((IPDObject**)&clonewithBrush);

							m_subObjects->m_items.Add(clonewithBrush.Detach());
						}

						CComPtr<IPDObjectStroke> activeStroke;
						withStrokeFill->get_activeStroke(&activeStroke);
						m_activeStroke = activeStroke;

						CComPtr<IPDObjectFill> activeFill;
						withStrokeFill->get_activeFill(&activeFill);
						m_activeFill = activeFill;
					}
				}
				else
				{
					if (objectType != m_objectType)
					{
						m_objectType = tomUndefined;	// Mixed objects
					}

					m_bMixedAppearance = TRUE;

				// Remove all but active stroke/fill
					for (int i = m_subObjects->m_items.GetSize()-1; i >= 0; i--)
					{
						if (!IsUnknownEqualUnknown(m_subObjects->m_items[i], m_activeStroke) &&
							IsUnknownEqualUnknown(m_subObjects->m_items[i], m_activeFill))
						{
							m_subObjects->m_items.RemoveAt(i);
						}
					}

					if (TRUE/*IsEqual(withBrush) == S_FALSE*/)
					{
					// Mixed appearance
						m_appearance = NULL;
	//					m_subObjects->m_items.RemoveAll();
					}
				}
			}
#endif
		}
	}

/*
	HRESULT CreateBrushFromTargets(int strokeOrFill, IPDBrush* *pVal)
	{
		CComObject<CPDBrush>* pBrush;
		CComObject<CPDBrush>::CreateInstance(&pBrush);

		m_activeFill

		*pVal = pBrush;
		(*pVal)->AddRef();
	}
	*/

	HRESULT IsEqual(IPDObjectWithAppearanceAndStrokeFill* withBrush)
	{
	}

BEGIN_COM_MAP(CPDObjectSelection)
	COM_INTERFACE_ENTRY(IPDObjectSelection)
	COM_INTERFACE_ENTRY(IPDObjectWithAppearance)
	COM_INTERFACE_ENTRY(IPDObjectWithAppearanceAndStrokeFill)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}

public:
	STDMETHOD(GetView)(/*[out,retval]*/ IPDDocumentView* *pVal)
	{
		*pVal = m_view;
		(*pVal)->AddRef();
		return S_OK;
	}

	STDMETHODIMP get_objectType(long* pVal)
	{
		*pVal = m_objectType;
		return S_OK;
	}

	STDMETHODIMP appendSubObject(IPDObjectWithBrush *object)
	{
		return CPDObjectWithAppearanceAndStrokeFillImpl<CPDObjectSelection>::appendSubObject(object);
	}

	STDMETHODIMP hasMixedAppearance(VARIANT_BOOL *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_bMixedAppearance? VARIANT_TRUE: VARIANT_FALSE;
		return S_OK;
	}

// IPDObjectWithAppearance
	STDMETHOD(Render2)(/*[in]*/ DWORD dwBitmap, /*[in]*/ DWORD dwGraphics, double scaleX, double scaleY)
	{
		return E_FAIL;
	}
//
};

void CPDDocumentView::SetObjectSelection(IPDObjectSelection* selection)
{
	CPDObjectSelection* pSelection = (CPDObjectSelection*)selection;

#if 0
	if (m_targetObjects.GetSize() == 0)
	{
		// copy to document
		CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokefill = m_document;
		CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokefill2 = selection;
		strokefill->copyAppearanceFrom(VARIANT_TRUE /*newArtHasBasicAppearance*/, strokefill2);
	}
	else
#endif

	{
		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CComQIPtr<IPDObjectWithAppearance> withAppearance = m_targetObjects[i]->m_object;
			if (withAppearance)
			{
				CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> withStrokeFill = withAppearance;
				if (withStrokeFill)
				{
					withStrokeFill->copyAppearanceFrom(VARIANT_FALSE, pSelection);
#if 0
					{
						CComPtr<IPDBrush> brush;
						pSelection->m_activeStroke->get_brush(&brush);

						CComPtr<IPDObjectStroke> activeStroke;
						withStrokeFill->get_activeStroke(&activeStroke);
						CComPtr<IPDBrush> brush2;
						activeStroke->get_brush(&brush2);

						brush2->getCommon(brush);
					}

					{
						CComPtr<IPDBrush> brush;
						pSelection->m_activeFill->get_brush(&brush);

						CComPtr<IPDObjectFill> activeFill;
						withStrokeFill->get_activeFill(&activeFill);
						CComPtr<IPDBrush> brush2;
						activeFill->get_brush(&brush2);

						brush2->getCommon(brush);
					}
#endif
					/*
					withStrokeFill->removeSubObjects();

					CComQIPtr<IPDObjectFrame> frame = withStrokeFill;

					if (pSelection->m_bMixedAppearance)
					{
						ATLASSERT(0);

						CComPtr<IPDObjectStroke> stroke;
						withStrokeFill->get_activeStroke(&stroke);

						CComPtr<IPDObjectFill> fill;
						withStrokeFill->get_activeFill(&fill);
					}
					else
					{

						CComPtr<IObjectMap> subObjects;
						pSelection->get_subObjects(&subObjects);

						long nsubObjects;
						subObjects->get_length(&nsubObjects);

						for (int i = 0; i < nsubObjects; i++)
						{
							CComPtr<IPDObjectWithBrush> withBrush;
							subObjects->item(i, (IUnknown**)&withBrush);

							CComPtr<IPDObjectWithBrush> clonewithBrush;
							withBrush->clone((IPDObject**)&clonewithBrush);

							frame->appendSubObject(clonewithBrush);
						}
					}
					*/
				}
			}
		}
	}
}

static double m_spreadDistance = 80;

bool g_bFastFeedback = true;

extern double GetLineAngle(float x1, float y1, float x2, float y2);

void DrawStippledLineV(HDC hDC, int x, int starty, int endy)
{
	for (int y = starty; y < endy; y += 2)
	{
		MoveToEx(hDC, x, y, NULL);
		LineTo(hDC, x, y+1);
	}
}

void DrawStippledLineH(HDC hDC, int y, int startx, int endx)
{
	for (int x = startx; x < endx; x += 2)
	{
		MoveToEx(hDC, x, y, NULL);
		LineTo(hDC, x+1, y);
	}
}

HRESULT GetTransformRectBoundingBox(IPDMatrix* mat, RectD* bounds, RectD* pVal)
{
	PointD pts[4] =
	{
		bounds->X, bounds->Y,
		bounds->X+bounds->Width, bounds->Y,
		bounds->X+bounds->Width, bounds->Y+bounds->Height,
		bounds->X, bounds->Y+bounds->Height,
	};

	double minx = 9999999;
	double miny = 9999999;
	double maxx = -9999999;
	double maxy = -9999999;

	//Gdiplus::PointF	xpts[4];

	for (int i = 0; i < 4; i++)
	{
		PointD xpt;
		mat->transformPoint(&pts[i], &xpt);

		if (xpt.x < minx) minx = xpt.x;
		if (xpt.y < miny) miny = xpt.y;
		if (xpt.x > maxx) maxx = xpt.x;
		if (xpt.y > maxy) maxy = xpt.y;
	}

	pVal->X = minx;
	pVal->Y = miny;
	pVal->Width = maxx-minx;
	pVal->Height = maxy-miny;

	return S_OK;
}

#if 0
void CPDDocumentView::CopyDefaultProperties(IPDObjectFrame* frame)
{
	CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokefill = frame;

	VARIANT_BOOL newArtHasBasicAppearance;
	gIApp->get_newArtHasBasicAppearance(&newArtHasBasicAppearance);

	if (newArtHasBasicAppearance)
	{
		// Fill
		{
			CComPtr<IPDObjectFill> fill;
			get_activeFill(&fill);
			CComPtr<IPDObjectFill> clonefill;
			fill->clone((IPDObject**)&clonefill);

			frame->appendSubObject(clonefill);
		}

		// Stroke
		{
			CComPtr<IPDObjectStroke> stroke;
			get_activeStroke(&stroke);
			CComPtr<IPDObjectStroke> clonestroke;
			stroke->clone((IPDObject**)&clonestroke);

			frame->appendSubObject(clonestroke);
		}
	}
	else
	{
		ATLASSERT(0);
	}
	/*
	CComPtr<IPDBrush> defaultStrokeBrush;
	gIApp->get_strokeBrush(&defaultStrokeBrush);

	CComPtr<IPDBrush> defaultFillBrush;
	gIApp->get_fillBrush(&defaultFillBrush);

	CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokefill = frame;

	CComPtr<IObjectMap> subObjects;
	strokefill->get_subObjects(&subObjects);

	CComPtr<IPDObjectFill> fill;
	fill.CoCreateInstance(CLSID_PDObjectFill);
	if (fill)
	{
		CComPtr<IPDBrush> brush;
		defaultFillBrush->clone(&brush);

		CComPtr<IPDObjectWithBrush> object = fill;
		object->put_brush(brush);

		frame->appendSubObject(object);
	}

	CComPtr<IPDObjectStroke> stroke;
	stroke.CoCreateInstance(CLSID_PDObjectStroke);
	if (fill)
	{
		CComPtr<IPDBrush> brush;
		defaultStrokeBrush->clone(&brush);

		CComPtr<IPDObjectWithBrush> object = stroke;
		object->put_brush(brush);

		frame->appendSubObject(object);
	}

	/*
	object->put_strokeBrush(strokeBrush);

	CComPtr<IPDBrush> fillBrush;
	defaultFillBrush->clone(&fillBrush);
	object->put_fillBrush(fillBrush);
	*/
}
#endif

ILDOMElement* GetParentParagraph(ILDOMNode* node)
{
	CComPtr<ILDOMNode> parent;
	node->get_parentNode(&parent);

	while (parent)
	{
		CComQIPtr<ILDOMElement> parentElement = parent;
		if (parentElement)
		{
			BSTR btagName;
			parentElement->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcscmp(tagName, L"p"))
			{
				return parentElement.Detach();
			}
		}

		CComPtr<ILDOMNode> parentNode;
		parent->get_parentNode(&parentNode);
		parent = parentNode;
	}

	return NULL;
}

////////////////////////////////
// CPDDocumentView

long CPDDocumentView::GetPageIndexUnderPoint(CDblPoint pt)
{
	ATLASSERT(m_activeSpread);

	double pageWidth;
	m_document->get_pageWidth(&pageWidth);

	CComPtr<IObjectMap> pages;
	m_activeSpread->get_pages(&pages);

	long npages;
	pages->get_length(&npages);

	if (pt.x >= 0 && pt.x < npages*pageWidth)
	{
		return (long)(pt.x/pageWidth);
	}
	else
		return -1;
}

int CPDDocumentView::FinalConstruct()
{
	HRESULT hr;

	hr = m_matrix.CoCreateInstance(CLSID_PDMatrix);
	ATLASSERT(SUCCEEDED(hr));

//	hr = m_range.CoCreateInstance(CLSID_Range);
//	ATLASSERT(SUCCEEDED(hr));

	m_horz.CoCreateInstance(CLSID_UIScrollBar);
	m_horz->put_direction(0);

	m_vert.CoCreateInstance(CLSID_UIScrollBar);
	m_vert->put_direction(1);

	hr = CComObject<CPDObjectSelection>::CreateInstance(&m_objectSelection);
	if (FAILED(hr)) return hr;
	m_objectSelection->AddRef();
	m_objectSelection->m_view = this;

	return S_OK;
}

void CPDDocumentView::FinalRelease()
{
	if (m_objectSelection)
	{
		m_objectSelection->Release();
		m_objectSelection = NULL;
	}
}

STDMETHODIMP CPDDocumentView::OnActivate(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	if (bActivate)
	{
		uiManager->ActivateObject(NULL, m_document);
		uiManager->ActivateObject(m_document, GetUnknown());

		m_objectSelection->FromTargets(m_targetObjects.GetData(), m_targetObjects.GetSize());
		uiManager->ActivateObject(GetUnknown(), m_objectSelection->GetUnknown());
	}
	else
	{
		uiManager->DeactivateObject(GetUnknown());
		uiManager->DeactivateObject(m_document);
	}

	return S_OK;
}

BOOL CPDDocumentView::FindPointUnderPoint(IPDObjectFrame* frame, CDblPoint mousept, long& segindex, long& ctl)
{
	CComQIPtr<IPDObjectTransformable> objectTransformable = frame;

	CComPtr<IPDMatrix> ctm0;
	frame->getScreenCTM(&ctm0);

	CComPtr<IPDMatrix> ctm;
	ctm0->multiply(m_matrix, &ctm);
/*
	CComPtr<IPDPath> seglist;
	frame->get_path(&seglist);
*/
	ctl = 0;
	segindex = ((CPDObjectFrameSelected*)GetPDObjectSelected(frame))->m_path->FindPoint(ctm, mousept.x, mousept.y, ctl);
	if ((segindex >= 0)/* && (ctl == 0)*/)
		return TRUE;

	return FALSE;
}

HRESULT CPDDocumentView::GetObjectUnderPoint(CDblPoint pt, int tool, CHitData* hit, IPDObject** pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	if (m_activeGroup)
	{
		CComPtr<IPDMatrix> ctm;
		m_activeGroup->getScreenCTM(&ctm);

		CComPtr<IPDMatrix> matrix;
		ctm->multiply(m_matrix, &matrix);

		GetObjectUnderPoint(m_activeGroup, matrix, pt, tool, hit, pVal);

		if (*pVal)
		{
			return S_OK;
		}
	}
	else if (m_activeSpread)
	{
		CComPtr<IObjectMap> layergroups;
		m_activeSpread->get_layergroups(&layergroups);

		long nlayergroups;
		layergroups->get_length(&nlayergroups);

		for (long nlayergroup = nlayergroups-1; nlayergroup >= 0; nlayergroup--)
		{
			CComPtr<IPDObjectLayerGroup> layergroup;
			layergroups->item(nlayergroup, (IUnknown**)&layergroup);

			GetObjectUnderPoint(layergroup, m_matrix, pt, tool, hit, pVal);

			if (*pVal)
			{
				return S_OK;
			}
		}
	}

	return S_OK;
}

HRESULT CPDDocumentView::GetObjectUnderPoint(IPDObject* object, IPDMatrix* matrix, CDblPoint pt, int tool, CHitData* hit, IPDObject** pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	CComPtr<IPDObject> parent;
	object->get_parent((IPDObjectUnknown**)&parent);

	PDObjectType objectType;
	object->get_objectType(&objectType);

	CComPtr<IPDObject> fobject;

	hit->hit = 0;

	CComQIPtr<IPDObjectTransformable> objectTransformable = object;

	CComPtr<IPDMatrix> ctm;

	RectD bounds;
	if (objectTransformable)
	{
		objectTransformable->get_bounds(&bounds);

		CComPtr<IPDMatrix> ctm0;
	//	objectTransformable->getScreenCTM(&ctm0);
		objectTransformable->get_transformMatrix(&ctm0);

		ctm0->multiply(matrix, &ctm);
	}
	else
		ctm = matrix;

	if (tool == 4)	// Text tool
	{
		CComPtr<IPDMatrix> ictm;
		ctm->inverse(&ictm);

		PointD xpt;
		ictm->transformPoint((PointD*)&pt, &xpt);

		if (objectType == CONTENT_TEXT)
		{
			CComQIPtr<IPDContentText> text = object;

			BOOL bHit;
			text->getPosUnderPoint(xpt.x, xpt.y, &hit->pNode, &hit->offset, &bHit);
			if (bHit)
			{
				fobject = object;
				hit->hit = 1;
			}
		}
		else if (objectType == OBJECT_FRAME)
		{
			CComQIPtr<IPDObjectFrame> frame = object;

			CComPtr<IPDPathText> pathText;
			frame->get_pathText(&pathText);

			if (pathText)
			{
				BOOL bHit;
				pathText->getPosUnderPoint(xpt.x, xpt.y, &hit->pNode, &hit->offset, &bHit);
				if (bHit)
				{
					fobject = pathText;
					hit->hit = 1;
				}
			}
		}
	}
	else if (tool == 5)
	{
		// TODO, don't use this stuff here
		CComPtr<IPDMatrix> ictm;
		ctm->inverse(&ictm);

		PointD xpt;
		ictm->transformPoint((PointD*)&pt, &xpt);

		if (objectType == OBJECT_FRAME)
		{
			CComQIPtr<IPDObjectFrame> frame = object;

			//CComPtr<IPDPath> pdpath;
			//frame->get_path(&pdpath);

			BOOL bOver;// = IsPointOverPath(*(CDblPoint*)&xpt, pdpath, NULL);
			frame->IsPointOverStrokeOutline(xpt, &bOver);
			if (bOver)
			{
				fobject = object;
				hit->hit = 1;
			}
		}
	}
	else
	{
		CPDObjectSelected* pObject = GetPDObjectSelected(object);
		if (pObject)
		{
			if (hit->hit == 0)
			{
				PointD pts[9] =
				{
					bounds.X+bounds.Width/2, bounds.Y+bounds.Height/2,	// center point

					bounds.X, bounds.Y,
					bounds.X+bounds.Width/2, bounds.Y,
					bounds.X+bounds.Width, bounds.Y,
					bounds.X+bounds.Width, bounds.Y+bounds.Height/2,
					bounds.X+bounds.Width, bounds.Y+bounds.Height,
					bounds.X+bounds.Width/2, bounds.Y+bounds.Height,
					bounds.X, bounds.Y+bounds.Height,
					bounds.X, bounds.Y+bounds.Height/2,
				};

				PointD xpts[9];
				for (int npt = 0; npt < 9; npt++)
				{
					ctm->transformPoint(&pts[npt], &xpts[npt]);
				}

				for (npt = 0; npt < 9; npt++)
				{
					if ((fabs(pt.x-xpts[npt].x) <= 3) && (fabs(pt.y-xpts[npt].y) <= 3))
					{
						hit->hit = npt+1;
						fobject = object;
						break;
					}
				}
			}
		}

		if (hit->hit == 0)
		{
			CComPtr<IPDMatrix> ictm;
			ctm->inverse(&ictm);

			PointD xpt;
			ictm->transformPoint((PointD*)&pt, &xpt);

			if (objectType == OBJECT_FRAME)
			{
				CComQIPtr<IPDObjectFrame> frame = object;

				BOOL bOver;
				frame->IsPointOverStrokeOutline(xpt, &bOver);
				if (bOver)
				{
					fobject = object;
					hit->hit = 1;
				}
			}
			else if (objectType == CONTENT_GRAPHIC ||
						objectType == OBJECT_SYMBOLINSTANCE)
			{
				if (xpt.x >= bounds.X && xpt.y >= bounds.Y &&
					xpt.x < bounds.X+bounds.Width && xpt.y < bounds.Y+bounds.Height)
				{
					fobject = object;
					hit->hit = 1;
				}
			}
		}

		if (tool == 2)	// Direct selection tool
		{
			// check if hit on path
			if (objectType == OBJECT_FRAME)
			{
				CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;
				CComQIPtr<IPDObjectFrame> frame = object;

				CComPtr<IPDPath> pdpath;
				frame->get_path(&pdpath);

				if (pFrame)	// Selected object
				{
					hit->anchor = pFrame->m_path->FindPoint(ctm, pt.x, pt.y, hit->ctl);
					if (hit->anchor >= 0)
					{
						hit->path = pdpath;
					}
				}
				else	// Unselected object
				{
					pdpath->getPointNearAnchorPoint(ctm, pt.x, pt.y, 3, &hit->anchor);
					if (hit->anchor >= 0)
					{
						hit->path = pdpath;
					}
				}

				if (hit->anchor < 0)
				{
					BOOL bHit;
					pdpath->getPointNearPath(ctm, pt.x, pt.y, 2, &hit->segment,&hit->t, &bHit);
					if (bHit)
					{
						hit->path = pdpath;
					}
				}
			}

			if (hit->path == NULL)
			{
				if (pObject)
				{
					if (pObject->m_wrapPath)
					{
						hit->anchor = pObject->m_wrapPath->FindPoint(ctm, pt.x, pt.y, hit->ctl);
						if (hit->anchor >= 0)
						{
							hit->path = pObject->m_wrapPath->GetPDPath();
						}

						if (hit->anchor < 0)
						{
							BOOL bHit;
							pObject->m_wrapPath->GetPDPath()->getPointNearPath(ctm, pt.x, pt.y, 2, &hit->segment,&hit->t, &bHit);
							if (bHit)
							{
								hit->path = pObject->m_wrapPath->GetPDPath();
							}
						}
					}
				}
			}

			if (hit->path)
			{
				hit->hit = -1;
				fobject = object;
			}
		}
	}

// Try children
	if (hit->hit == 0)
	{
		CComPtr<IObjectMap> children;
		object->get_children(&children);

		if (children)
		{
			long length;
			children->get_length(&length);
			for (long n = length-1; n >= 0; n--)
			{
				CComQIPtr<IPDObject> subobject;
				children->item(n, (IUnknown**)&subobject);

			// Recurse
				GetObjectUnderPoint(subobject, ctm, pt, tool, hit, &fobject);
				if (fobject)
				{
					break;
				}
			}
		}
	}

	if (tool == 1)	// Selection tool
	{
		if (fobject)
		{
			if (TRUE)
			{
				if (parent != NULL)
				{
					(*pVal = object)->AddRef();
					return S_OK;//object;
				}
			}
			else
			{
				ATLASSERT(parent);

				CComPtr<IPDObject> parentParent;
				parent->get_parent((IPDObjectUnknown**)&parentParent);

				if (parentParent != NULL)
				{
					(*pVal = object)->AddRef();
					return S_OK;
				}
			}
		}
	}
	else if (tool == 3)	// Group selection tool
	{
		if (fobject)
		{
			if (IsPDObjectSelected(object))
			{
				(*pVal = parent)->AddRef();
				return S_OK;//parent.Detach();
			}
		}
	}

	if (fobject)
		(*pVal = fobject)->AddRef();//.Detach();
	//else
	//	return NULL;

	return S_OK;
}

bool CPDDocumentView::IsGuideSelected(IPDGuide* guide)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		if (IsUnknownEqualUnknown(m_targetObjects[i]->m_object, guide))
			return true;
	}

	return false;
}

CPathSelection* CPDDocumentView::GetPDPathSelected(IPDPath* pdpath)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		if (m_targetObjects[i]->m_wrapPath && IsUnknownEqualUnknown(m_targetObjects[i]->m_wrapPath->GetPDPath(), pdpath))
		{
			return m_targetObjects[i]->m_wrapPath;
		}

		PDObjectType objectType;
		m_targetObjects[i]->m_object->get_objectType(&objectType);

		if (objectType == OBJECT_FRAME)
		{
			if (IsUnknownEqualUnknown(((CPDObjectFrameSelected*)m_targetObjects[i])->m_path->GetPDPath(), pdpath))
			{
				return ((CPDObjectFrameSelected*)m_targetObjects[i])->m_path;
			}
		}
	}

	return NULL;
}

CPDObjectSelected* CPDDocumentView::GetPDObjectSelected(IPDObjectUnknown* object)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		if (m_targetObjects[i]->m_object == object)
			return m_targetObjects[i];
	}

	return NULL;
}

bool CPDDocumentView::IsPDObjectSelected(IPDObjectUnknown* object)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		if (IsUnknownEqualUnknown(m_targetObjects[i]->m_object, object))
			return true;
	}

	return false;
}

void CPDDocumentView::DeselectPDObject(IPDObjectUnknown* object)
{
	CComPtr<IUIManager> uiManager = gApp->m_frame;

	uiManager->DeactivateObject(m_objectSelection->GetUnknown());

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		if (IsUnknownEqualUnknown(m_targetObjects[i]->m_object, object))
		{
			uiManager->DeactivateObject(m_targetObjects[i]->m_object);

			if (m_pActiveObject == m_targetObjects[i])
			{
				m_pActiveObject = NULL;
				m_pActivePath = NULL;
			}

			PDObjectType objectType;
			m_targetObjects[i]->m_object->get_objectType(&objectType);
			if (objectType == OBJECT_GUIDE)
			{
				m_bInvalid = true;
			}

			delete m_targetObjects[i];
			m_targetObjects.RemoveAt(i);

			CalculateObjectsBoundingBox();

			InvalidateRect(&m_areaRect);

		// TODO: Write some comments here, this isn't clear to myself
			m_objectSelection->FromTargets(m_targetObjects.GetData(), m_targetObjects.GetSize());
			uiManager->ActivateObject(GetUnknown(), m_objectSelection->GetUnknown());
			return;
		}
	}

	ATLASSERT(0);
}

CPDObjectSelected* CPDDocumentView::SelectPDObject(IPDObjectUnknown* object, UINT nFlags, BOOL bSelectPoints)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;

	if (object)
	{
		CPDObjectSelected* pObject = GetPDObjectSelected(object);
		if (pObject)	// Already selected
		{
			if (nFlags & MK_SHIFT)
			{
				DeselectPDObject(object);
			}
			else
			{
				PDObjectType objectType;
				object->get_objectType(&objectType);

				if (objectType == OBJECT_FRAME)
				{
					CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;
					if (bSelectPoints)
					{
						pFrame->m_path->SelectAllAnchors();
					}
				}

				m_pActiveObject = pObject;
				return m_pActiveObject;
			}
		}
		else
		{
			if (!(nFlags & MK_SHIFT))
			{
				DeselectAll();
			}

			PDObjectType objectType;
			object->get_objectType(&objectType);

			if (objectType == OBJECT_GROUP)
			{
				pObject = new CPDObjectGroupSelected(object);
			}
			else if (objectType == OBJECT_FRAME)
			{
				pObject = new CPDObjectFrameSelected(object, bSelectPoints);
			}
			else
			{
				pObject = new CPDObjectSelected(object);
			}

			if (pObject)
			{
				m_pActivePath = NULL;	// ??

				m_targetObjects.Add(pObject);
				m_pActiveObject = pObject;

				uiManager->ActivateObject(GetUnknown(), object);

				{
					uiManager->DeactivateObject(m_objectSelection->GetUnknown());
					m_objectSelection->FromTargets(m_targetObjects.GetData(), m_targetObjects.GetSize());
					uiManager->ActivateObject(GetUnknown(), m_objectSelection->GetUnknown());

				}

				CalculateObjectsBoundingBox();

				InvalidateRect(&m_areaRect);

				PDObjectType objectType;
				object->get_objectType(&objectType);
				if (objectType == OBJECT_GUIDE)
				{
					m_bInvalid = true;
				}

				return m_pActiveObject;
			}
		}
	}
	else
	{
		if (!(nFlags & MK_SHIFT))
		{
			DeselectAll();
		}
	}

	return NULL;
}

void CPDDocumentView::DeselectAll()
{
	CComQIPtr<IUIManager> uiManager = gIFrame;

	uiManager->DeactivateObject(m_objectSelection->GetUnknown());

	m_pActivePath = NULL;
	m_pActiveObject = NULL;

	for (int i = m_targetObjects.GetSize()-1; i >= 0; i--)
	{
		uiManager->DeactivateObject(m_targetObjects[i]->m_object);

		PDObjectType objectType;
		m_targetObjects[i]->m_object->get_objectType(&objectType);
		if (objectType == OBJECT_GUIDE)
		{
			m_bInvalid = true;
		}

		delete m_targetObjects[i];
		m_targetObjects.RemoveAt(i);
	}

	ATLASSERT(m_targetObjects.GetSize() == 0);

	CalculateObjectsBoundingBox();

	InvalidateRect(&m_areaRect);

	m_objectSelection->FromTargets(m_targetObjects.GetData(), m_targetObjects.GetSize());
	uiManager->ActivateObject(GetUnknown(), m_objectSelection->GetUnknown());
}

HRESULT CalculateContentsBBox(IPDObject* object, RectD* pVal)
{
	PDObjectType objectType;
	object->get_objectType(&objectType);

	if (objectType == OBJECT_GROUP)
	{
		double minx = 9999999;
		double miny = 9999999;
		double maxx = -9999999;
		double maxy = -9999999;

		CComPtr<IObjectMap> children;
		object->get_children(&children);
		long nchildren;
		children->get_length(&nchildren);

		for (long i = 0; i < nchildren; i++)
		{
			CComPtr<IPDObject> child;
			children->item(i, (IUnknown**)&child);

			RectD bounds;
			CalculateContentsBBox(child, &bounds);

			if (bounds.X < minx) minx = bounds.X;
			if (bounds.Y < miny) miny = bounds.Y;
			if (bounds.X+bounds.Width > maxx) maxx = bounds.X+bounds.Width;
			if (bounds.Y+bounds.Height > maxy) maxy = bounds.Y+bounds.Height;
		}

		pVal->X = minx;
		pVal->Y = miny;
		pVal->Width = maxx-minx;
		pVal->Height = maxy-miny;
	}
	else
	{
		CComQIPtr<IPDObjectLocatable> objectLocatable = object;

		if (objectLocatable)
		{
			objectLocatable->getScreenBBox(pVal);
		}
	}

	return S_OK;
}

HRESULT CalculateContentsExpandedBBox(IPDObject* object, RectD* pVal)
{
	PDObjectType objectType;
	object->get_objectType(&objectType);

	if (objectType == OBJECT_GROUP)
	{
		double minx = 9999999;
		double miny = 9999999;
		double maxx = -9999999;
		double maxy = -9999999;

		CComPtr<IObjectMap> children;
		object->get_children(&children);
		long nchildren;
		children->get_length(&nchildren);

		for (long i = 0; i < nchildren; i++)
		{
			CComPtr<IPDObject> child;
			children->item(i, (IUnknown**)&child);

			RectD bounds;
			CalculateContentsExpandedBBox(child, &bounds);

			if (bounds.X < minx) minx = bounds.X;
			if (bounds.Y < miny) miny = bounds.Y;
			if (bounds.X+bounds.Width > maxx) maxx = bounds.X+bounds.Width;
			if (bounds.Y+bounds.Height > maxy) maxy = bounds.Y+bounds.Height;
		}

		pVal->X = minx;
		pVal->Y = miny;
		pVal->Width = maxx-minx;
		pVal->Height = maxy-miny;
	}
	else
	{
		//CComQIPtr<IPDObjectLocatable> objectLocatable = object;

		CComPtr<IPDMatrix> ctm;
		object->getScreenCTM(&ctm);

		RectD expandedBBox;
		object->getExpandedBBox(&expandedBBox);

		GetTransformRectBoundingBox(ctm, &expandedBBox, pVal);
	}

	return S_OK;
}

void CPDDocumentView::CalculateObjectsBoundingBox()
{
	if (m_targetObjects.GetSize() > 0)
	{
		double minx = 9999999;
		double miny = 9999999;
		double maxx = -9999999;
		double maxy = -9999999;

		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CPDObjectSelected* pObject = m_targetObjects[i];

			CComQIPtr<IPDObject> object = pObject->m_object;
			if (object)
			{
				RectD bounds;
				CalculateContentsBBox(object, &bounds);

				if (bounds.X < minx) minx = bounds.X;
				if (bounds.Y < miny) miny = bounds.Y;
				if (bounds.X+bounds.Width > maxx) maxx = bounds.X+bounds.Width;
				if (bounds.Y+bounds.Height > maxy) maxy = bounds.Y+bounds.Height;
			}
		}

		m_objectsBoundingBox.X = minx;
		m_objectsBoundingBox.Y = miny;
		m_objectsBoundingBox.Width = maxx-minx;
		m_objectsBoundingBox.Height = maxy-miny;
	}
	else
	{
		m_objectsBoundingBox.X = 0;
		m_objectsBoundingBox.Y = 0;
		m_objectsBoundingBox.Width = 0;
		m_objectsBoundingBox.Height = 0;
	}
}

void CPDDocumentView::CalculateObjectsExpandedBoundingBox(RectD* objectsBoundingBox)
{
	if (m_targetObjects.GetSize() > 0)
	{
		double minx = 9999999;
		double miny = 9999999;
		double maxx = -9999999;
		double maxy = -9999999;

		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CPDObjectSelected* pObject = m_targetObjects[i];

			CComQIPtr<IPDObject> object = pObject->m_object;
			if (object)
			{
				RectD bounds;
				CalculateContentsExpandedBBox(object, &bounds);

				if (bounds.X < minx) minx = bounds.X;
				if (bounds.Y < miny) miny = bounds.Y;
				if (bounds.X+bounds.Width > maxx) maxx = bounds.X+bounds.Width;
				if (bounds.Y+bounds.Height > maxy) maxy = bounds.Y+bounds.Height;
			}
		}

		objectsBoundingBox->X = minx;
		objectsBoundingBox->Y = miny;
		objectsBoundingBox->Width = maxx-minx;
		objectsBoundingBox->Height = maxy-miny;
	}
	else
	{
		objectsBoundingBox->X = 0;
		objectsBoundingBox->Y = 0;
		objectsBoundingBox->Width = 0;
		objectsBoundingBox->Height = 0;
	}
}

void CPDDocumentView::SetMatrix()
{
	m_matrix.Release();

	CComQIPtr<IPDMatrix> mat;
	mat.CoCreateInstance(CLSID_PDMatrix);
	/*
	if (FAILED(mat.CoCreateInstance(CLSID_PDMatrix)))
	{
		::MessageBox(GetMainHwnd(), "Couldn't create matrix class\nPageDesigner will terminate.", "PageDesigner", MB_OK);
		PostQuitMessage(-1);
		return;
	}
	*/
//	mat->setTranslate(0, 0);

	mat->setTranslate(m_activeSpreadOffset.x, m_activeSpreadOffset.y);
	mat->scaleNonUniform(m_magnify, m_magnify, &m_matrix);
}

void GetRulerValues(PDUnit unit, double& pixelInterval, double& numberInterval, double magnify)
{
	double pixelsPerPoint = ConvertSpecifiedValueToUserUnit(unit, 1) * magnify;

	double minPixelInterval = 40;

	numberInterval = 6;
	pixelInterval = numberInterval * pixelsPerPoint;

	while (pixelInterval < minPixelInterval)
	{
		if (numberInterval < 24) numberInterval += 6;
		else if (numberInterval == 24) numberInterval = 36;
		else if (numberInterval < 288) numberInterval *= 2;
		else if (numberInterval == 288) numberInterval = 1152;
		else numberInterval *= 4;

		pixelInterval = numberInterval * pixelsPerPoint;
	}

#if 0
	double pixelsPerPoint = ConvertSpecifiedValueToUserUnit(unit, 1) * m_magnify;

	double minEveryPx = 40;
	double valueAdd2 = minEveryPx / pixelsPerPoint;//*pixelsPerPoint;

	numberEveryPx = 6 * pixelsPerPoint;

	valueAdd = 0;//valueAdd2;
	numberEveryPx = valueAdd2 * pixelsPerPoint;

	while (numberEveryPx < minEveryPx)
	{
	}

	int n = 1;
	while (valueAdd == 0/*numberEveryPx < minEveryPx*/)
	{
		if (valueAdd2 <= 6) valueAdd = 6*(n);
		else if (valueAdd2 <= 24) valueAdd = 24*(n);
		else if (valueAdd2 <= 36) valueAdd = 36*(n);
		else if (valueAdd2 <= 72) valueAdd = 72*(n);

		numberEveryPx = valueAdd * pixelsPerPoint;

		valueAdd2 /= 100;
		n *= 100;
	}
#endif
}

void DrawSubDivisionLines(HDC hDC, BOOL bHorizontal, int start, int width, int height, DWORD subdivisionsMask)
{
	int nsubdivisions = subdivisionsMask & 0xf;

	for (int i = 0; i < nsubdivisions; i++)
	{
		int offset = start + i*width/nsubdivisions;

		if (bHorizontal)
		{
			MoveToEx(hDC, offset, 16-height, NULL);
			LineTo(hDC, offset, 16);
		}
		else
		{
			MoveToEx(hDC, 16-height, offset, NULL);
			LineTo(hDC, 16, offset);
		}

		if (subdivisionsMask>>4)
		{
			DrawSubDivisionLines(hDC, bHorizontal, offset, width/nsubdivisions, height-2, subdivisionsMask>>4);
		}
	}
}

// INotifyGet
STDMETHODIMP CPDDocumentView::OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
{
	if (type == NOTIFY_REMOVE)
	{
		for (int i = m_targetObjects.GetSize()-1; i >= 0; i--)
		{
			CComPtr<IPDSpread> spread;
			m_targetObjects[i]->m_object->get_spread(&spread);
			if (spread == NULL)
			{
				DeselectPDObject(m_targetObjects[i]->m_object);
			}
		}

			/*
		CComQIPtr<IPDObjectUnknown> objectUnknown = targetObject;
		if (objectUnknown)
		{
			if (IsPDObjectSelected(objectUnknown))
			{
				DeselectPDObject(objectUnknown);
			}
		}
		*/
	}

	CalculateObjectsBoundingBox();	// TODO, not always necessary

	// TODO, not always necessary
	{
		/*
		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			PDObjectType objectType;
			m_targetObjects[i]->m_object->get_objectType(&objectType);
			if (objectType == OBJECT_FRAME)
			{
				CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)m_targetObjects[i];
				pFrame->CalculateThreadRects();
			}
		}
  */
	}

	m_bInvalid = true;
	Invalidate();
	//FireOnChanged(type, targetObject, targetObjectIID, dispID);
	return S_OK;
}

void CPDDocumentView::RenderGuides(IPDRenderer* renderer, IPDSpread* spread, bool bDrawDeselected, bool bDrawSelected)
{
	COLORREF unselectedClr = RGB(0, 255, 255);

	double pageWidth;
	double pageHeight;
	m_document->get_pageWidth(&pageWidth);
	m_document->get_pageHeight(&pageHeight);

	long spine;
	spread->get_spine(&spine);

	double xoffset = (m_spine-spine)*pageWidth;

	CComPtr<IObjectMap> layergroups;
	spread->get_layergroups(&layergroups);

	long nlayergroups;
	layergroups->get_length(&nlayergroups);

	for (long nlayergroup = 0; nlayergroup < nlayergroups; nlayergroup++)
	{
		CComPtr<IPDObjectLayerGroup> layergroup;
		layergroups->item(nlayergroup, (IUnknown**)&layergroup);

		CComPtr<IPDLayer> layer;
		layergroup->get_layer(&layer);

		OLE_COLOR selectedClr;
		layer->get_color(&selectedClr);

		CComPtr<IPDGuides> guides;
		layergroup->get_guides(&guides);

		long nguides;
		guides->get_length(&nguides);

		for (long i = 0; i < nguides; i++)
		{
			CComPtr<IPDGuide> guide;
			guides->item(i, &guide);
			
			bool bSelected = IsGuideSelected(guide);

			bool bDraw = (bSelected && bDrawSelected) || (!bSelected && bDrawDeselected);

			if (bDraw)
			{
				renderer->RenderGuide(spread, guide, bSelected? selectedClr: unselectedClr,
					-(xoffset+100), -20,
					m_maxPages*pageWidth+200, pageHeight+40);
			}
		}
	}
}

LRESULT CPDDocumentView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	CRect clip;
	GetClipBox(hDC, &clip);

//	Rectangle(hDC, clip.left, clip.top, clip.right, clip.bottom);
//	Sleep(40);

	if (m_bRulers)
	{
		CRect client;
		GetClientRect(&client);

		CRect horRulerRect(16, 0, m_areaRect.right, 16);
		CRect verRulerRect(0, 16, 16, m_areaRect.bottom);

		CRect irect;
		BOOL bIHorRuler = irect.IntersectRect(&horRulerRect, &clip);
		BOOL bIVerRuler = irect.IntersectRect(&verRulerRect, &clip);

		FillSolidRect(hDC, 0, 0, 16, 16, RGB(255, 255, 255));

		if (bIHorRuler)
			FillSolidRect(hDC, &horRulerRect, RGB(255, 255, 255));

		if (bIVerRuler)
			FillSolidRect(hDC, &verRulerRect, RGB(255, 255, 255));

		Draw3DRect(hDC, 0, 0, client.right, 16, RGB(0,0,0), RGB(0,0,0));
		Draw3DRect(hDC, 0, 0, 16, client.bottom, RGB(0,0,0), RGB(0,0,0));

		DrawStippledLineH(hDC, 5, 0, 16);
		DrawStippledLineV(hDC, 5, 0, 16);

		if (bIHorRuler || bIVerRuler)
		{
			HFONT hFont = CreateFont(11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Small Fonts");
			HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

			if (m_activeSpread)
			{
				int state;
				
				state = SaveDC(hDC);

				// Horizontal ruler
				if (IntersectClipRect(hDC, horRulerRect.left, horRulerRect.top, horRulerRect.right, horRulerRect.bottom))
				{
					double valueAdd;
					double numberEveryPx;

					GetRulerValues(UNIT_PT, numberEveryPx, valueAdd, m_magnify);

					DWORD subdivisionsMask = (2<<0) | (2<<4) | (3<<8);

					int start = (scrollposX - (m_activeSpreadOffset.x+m_rulerOffset.x)*m_magnify - (numberEveryPx-1))/ numberEveryPx;
					int end = start + (m_areaRect.Width()+numberEveryPx+numberEveryPx-1) / numberEveryPx;

					POINT oldOrg;
					SetViewportOrgEx(hDC, 16 + -scrollposX + (m_activeSpreadOffset.x+m_rulerOffset.x)*m_magnify, 0, &oldOrg);

					int y = 0;

					for (int i = start; i < end; i++)
					{
						int x = i * numberEveryPx;

						MoveToEx(hDC, x, 0, NULL);
						LineTo(hDC, x, 16);

						CUString str;
						str.Format("%g", fabs(i * valueAdd));

						TextOut(hDC, x+1, y+1, str, str.GetLength());

						DrawSubDivisionLines(hDC, TRUE, x, numberEveryPx, 8, subdivisionsMask);
					}

					SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
				}

				RestoreDC(hDC, state);

				state = SaveDC(hDC);

				// Vertical ruler
				if (IntersectClipRect(hDC, verRulerRect.left, verRulerRect.top, verRulerRect.right, verRulerRect.bottom))
				{
					double valueAdd;
					double numberEveryPx;

					GetRulerValues(UNIT_PT, numberEveryPx, valueAdd, m_magnify);

					DWORD subdivisionsMask = (2<<0) | (2<<4) | (3<<8);

					int start = (scrollposY - (m_activeSpreadOffset.y+m_rulerOffset.y)*m_magnify) / numberEveryPx;
					int end = start + (m_areaRect.Height()+numberEveryPx-1) / numberEveryPx;

					POINT oldOrg;
					SetViewportOrgEx(hDC, 0, 16 + -scrollposY + (m_activeSpreadOffset.y+m_rulerOffset.y)*m_magnify, &oldOrg);

					int x = 0;

					for (int i = start; i < end; i++)
					{
						int y = i * numberEveryPx;

						MoveToEx(hDC, 0, y, NULL);
						LineTo(hDC, 16, y);

						char str[64];
						int len = sprintf(str, "%g", fabs(i * valueAdd));

						for (int j = 0; j < len; j++)
						{
							TextOut(hDC, x+1, y+1+j*11, &str[j], 1);
						}

						DrawSubDivisionLines(hDC, FALSE, y, numberEveryPx, 8, subdivisionsMask);
					}

					SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
				}

				RestoreDC(hDC, state);
			}

			SelectObject(hDC, hOldFont);
			DeleteObject(hFont);

			if (m_bCurPosOnRulerVisible)
			{
				int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
				DrawCurPosOnRuler(hDC, m_point);
				SetROP2(hDC, oldR2);
			}
		}
	}

	CRect irect;
	if (irect.IntersectRect(&clip, &m_areaRect))
	{
		Gdiplus::Bitmap* pClipBitmap = new Gdiplus::Bitmap(irect.Width(), irect.Height(), PixelFormat24bppRGB);

		if (pClipBitmap)
		{
			double pageWidth;
			double pageHeight;
			m_document->get_pageWidth(&pageWidth);
			m_document->get_pageHeight(&pageHeight);

			if (true/*!m_dragging || gApp->m_activeTool == ID_TOOL_HAND*/)	// TODO, should have int m_lockUpdate
			{
				if (m_bInvalid)
				{
				// Render spreads
					Gdiplus::Graphics graphics(m_pBitmap);

					Gdiplus::GraphicsState state = graphics.Save();

					Gdiplus::Rect cliprect(irect.left, irect.top, irect.Width(), irect.Height());
					cliprect.Offset(-m_areaRect.left, -m_areaRect.top);
					graphics.SetClip(cliprect);

					graphics.FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(197, 197, 197)), Gdiplus::Rect(0, 0, m_areaRect.Width(), m_areaRect.Height()));

					graphics.TranslateTransform(-scrollposX, -scrollposY);

					CComQIPtr<IPDRenderer> renderer;
					renderer.CoCreateInstance(CLSID_PDRenderer);
					renderer->AddCustomRenderer(this);

					renderer->put_targetHDC((HDC)&graphics);
					renderer->put_magnify(m_magnify);

					if (m_activeMasterSpread == NULL)
					{
						CComPtr<IObjectMap> spreads;
						m_document->get_spreads(&spreads);

						long nspreads;
						spreads->get_length(&nspreads);

						int y = 0;

						for (int nspread = 0; nspread < nspreads; nspread++)
						{
							CComQIPtr<IPDSpread> spread;
							spreads->item(nspread, (IUnknown**)&spread);

							CComPtr<IObjectMap> pages;
							spread->get_pages(&pages);

							long npages;
							pages->get_length(&npages);

							long spine;
							spread->get_spine(&spine);

							Gdiplus::GraphicsState state = graphics.Save();

							Gdiplus::RectF pasteBoardRect(-100.0*m_magnify, y-20*m_magnify, (float)(m_maxPages*pageWidth+200.0)*m_magnify, (float)(pageHeight+40)*m_magnify);
							{
								Gdiplus::RectF pasteBoardOffsetRect = pasteBoardRect;
								pasteBoardOffsetRect.Offset(3, 3);

								if (m_bViewTransparencyGrid)
								{
									CComQIPtr<IPDDocumentSettings> documentSettings = m_document;
									long gridSizeX;
									long gridSizeY;
									OLE_COLOR gridColor0;
									OLE_COLOR gridColor1;

									documentSettings->get_transpGridSizeX(&gridSizeX);
									documentSettings->get_transpGridSizeY(&gridSizeY);
									documentSettings->get_transpGridColor0(&gridColor0);
									documentSettings->get_transpGridColor1(&gridColor1);

									Gdiplus::SolidBrush brush0(Gdiplus::Color(GetRValue(gridColor0), GetGValue(gridColor0), GetBValue(gridColor0)));
									Gdiplus::SolidBrush brush1(Gdiplus::Color(GetRValue(gridColor1), GetGValue(gridColor1), GetBValue(gridColor1)));

									Gdiplus::Bitmap gridbitmap(gridSizeX*2, gridSizeY*2);
									{
										Gdiplus::Graphics graphics(&gridbitmap);

										graphics.FillRectangle(&brush0, 0, 0, gridSizeX, gridSizeY);
										graphics.FillRectangle(&brush1, gridSizeX, 0, gridSizeX, gridSizeY);
										graphics.FillRectangle(&brush1, 0, gridSizeY, gridSizeX, gridSizeY);
										graphics.FillRectangle(&brush0, gridSizeX, gridSizeY, gridSizeX, gridSizeY);
									}

									Gdiplus::TextureBrush tbrush(&gridbitmap, Gdiplus::WrapModeTile/*, Gdiplus::Rect(0, 0, gridSizeX*2, gridSizeY*2)*/);

									graphics.FillRectangle(&tbrush, pasteBoardRect);
								}
								else
								{
									graphics.FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(0, 0, 0)), pasteBoardOffsetRect);
									graphics.FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 255)), pasteBoardRect);
								}
								graphics.DrawRectangle(&Gdiplus::Pen(Gdiplus::Color(0, 0, 0)), pasteBoardRect);
							}

							pasteBoardRect.Inflate(-1, -1);
							graphics.IntersectClip(pasteBoardRect);

							double xoffset = (m_spine-spine)*pageWidth;

							graphics.TranslateTransform(xoffset*m_magnify, y);

							if (!m_bViewTransparencyGrid)
							{
								renderer->RenderSpreadBackground(spread);
							}

							renderer->RenderSpread(spread,
								-(xoffset+100), -20,
								m_maxPages*pageWidth+200, pageHeight+40);

							RenderGuides(renderer, spread, true, false);

							graphics.Restore(state);

							y += pageHeight*m_magnify + m_spreadDistance*m_magnify;
						}
					}
					else
					{
						Gdiplus::GraphicsState state = graphics.Save();
						graphics.TranslateTransform(0, 0);

						renderer->RenderSpread(m_activeSpread, 0, 0, 0, 0);	// TODO

						graphics.Restore(state);
					}

					graphics.Restore(state);

					m_bInvalid = false;
				}
			}

			{
				Gdiplus::Graphics graphics(pClipBitmap);

				// Render cached spread bitmap to clip bitmap
				graphics.DrawImage(m_pBitmap, m_areaRect.left -irect.left, m_areaRect.top -irect.top);

				Gdiplus::GraphicsState state = graphics.Save();
				graphics.TranslateTransform(m_areaRect.left -irect.left -scrollposX, m_areaRect.top -irect.top -scrollposY);

				if (gApp->m_activeTool == ID_TOOL_FREETRANSFORM)
				{
					if (m_targetObjects.GetSize() > 0)
					{
						CPDObjectSelected* pObject = m_targetObjects[0];

						CComPtr<IPDLayer> layer;
						pObject->m_object->get_layer(&layer);

						OLE_COLOR olelayerColor;
						layer->get_color(&olelayerColor);
						Gdiplus::Color layerColor(GetRValue(olelayerColor), GetGValue(olelayerColor), GetBValue(olelayerColor));

						Gdiplus::Pen pen(layerColor);
						Gdiplus::SolidBrush brush(layerColor);

						RectD bounds = m_objectsBoundingBox;

						PointD pts[8] =
						{
							bounds.X, bounds.Y,
							bounds.X+bounds.Width/2, bounds.Y,
							bounds.X+bounds.Width, bounds.Y,
							bounds.X+bounds.Width, bounds.Y+bounds.Height/2,
							bounds.X+bounds.Width, bounds.Y+bounds.Height,
							bounds.X+bounds.Width/2, bounds.Y+bounds.Height,
							bounds.X, bounds.Y+bounds.Height,
							bounds.X, bounds.Y+bounds.Height/2,
						};

						CComPtr<IPDMatrix> mat;
						if (m_freeTransformMatrix)
							m_freeTransformMatrix->multiply(m_matrix, &mat);
						else
							mat = m_matrix;

						Gdiplus::PointF xpts[8];

						for (int i = 0; i < 8; i++)
						{
							PointD xpt;
							mat->transformPoint(&pts[i], &xpt);
							xpts[i].X = xpt.x;
							xpts[i].Y = xpt.y;
						}

					// Outline
						graphics.DrawLine(&pen, xpts[0], xpts[2]);
						graphics.DrawLine(&pen, xpts[2], xpts[4]);
						graphics.DrawLine(&pen, xpts[4], xpts[6]);
						graphics.DrawLine(&pen, xpts[6], xpts[0]);

						if (!m_dragging)
						{
						// Size handles
							for (i = 0; i < 8; i++)
							{
								graphics.FillRectangle(&brush, (int)(xpts[i].X-2), (int)(xpts[i].Y-2), (4), (4));
							}
						}
					}
				}

			// Show text threads
				VARIANT_BOOL showTextThreads;
				m_document->get_showTextThreads(&showTextThreads);
				if (showTextThreads)
				{
					if (m_pActiveObject)
					{
						CComQIPtr<IPDObjectText> objectText;

						CComQIPtr<IPDObjectFrame> frame = m_pActiveObject->m_object;
						if (frame)
						{
							CComPtr<IPDObject> content;
							frame->get_content(&content);
							objectText = content;
						}
						else
							objectText = m_pActiveObject->m_object;

						if (objectText)
						{
							CComPtr<IPDStory> story;
							objectText->get_story(&story);

							CComPtr<IPDObjectText> textThread;
							story->get_firstTextThread(&textThread);

							while (textThread)
							{
								CComPtr<IPDMatrix> ctm;
								textThread->getScreenCTM(&ctm);

								PointD threadPtOut;
								textThread->get_threadPtOut(&threadPtOut);

								ctm->transformPoint(&threadPtOut, &threadPtOut);

								CComPtr<IPDLayer> layer;
								textThread->get_layer(&layer);

								OLE_COLOR	color;
								layer->get_color(&color);

								Gdiplus::Pen pen(Gdiplus::Color(GetRValue(color), GetGValue(color), GetBValue(color)), 3);

								CComPtr<IPDObjectText> nextTextThread;
								textThread->get_nextTextThread(&nextTextThread);
								if (nextTextThread)
								{
									CComPtr<IPDMatrix> ctm;
									nextTextThread->getScreenCTM(&ctm);
									
									PointD nextThreadPtIn;
									nextTextThread->get_threadPtIn(&nextThreadPtIn);

									ctm->transformPoint(&nextThreadPtIn, &nextThreadPtIn);

									graphics.DrawLine(&pen, (float)threadPtOut.x, (float)threadPtOut.y, (float)nextThreadPtIn.x, (float)nextThreadPtIn.y);
								}

								textThread = nextTextThread;
							}
						}
					}
				}

				for (int i = 0; i < m_targetObjects.GetSize(); i++)
				{
					CPDObjectSelected* pObject = m_targetObjects[i];

					CComQIPtr<IPDObject> object = pObject->m_object;
					if (object)
					{
						CComPtr<IPDLayer> layer;
						pObject->m_object->get_layer(&layer);

						OLE_COLOR olelayerColor;
						layer->get_color(&olelayerColor);
						Gdiplus::Color layerColor(GetRValue(olelayerColor), GetGValue(olelayerColor), GetBValue(olelayerColor));

						Gdiplus::Pen pen(layerColor);
						Gdiplus::SolidBrush brush(layerColor);

						CComPtr<IPDMatrix> ctm0;
						object->getScreenCTM(&ctm0);

						CComPtr<IPDMatrix> freectm;
						if (m_freeTransformMatrix)
						{
							CComPtr<IPDMatrix> ctm1;
							ctm0->multiply(m_freeTransformMatrix, &ctm1);
							ctm1->multiply(m_matrix, &freectm);
						}

						CComPtr<IPDMatrix> ctm;
						ctm0->multiply(m_matrix, &ctm);

						PDObjectType objectType;
						pObject->m_object->get_objectType(&objectType);

						if (pObject->m_wrapPath)
						{
							if (m_dragging &&
								(gApp->m_activeTool == ID_TOOL_BULGE || gApp->m_activeTool == ID_TOOL_TWIRL))
							{
								pObject->m_wrapPath->DrawPolyPoints(ctm, &graphics, &pen);
							}
							else
							{
								Gdiplus::GraphicsPath path;
								pObject->m_wrapPath->DrawPath(ctm, freectm, &path);
								graphics.DrawPath(&pen, &path);
							}

						//	if (!m_dragging)
							{
								pObject->m_wrapPath->DrawSelection(&graphics, layerColor, ctm);
							}
						}

						CComQIPtr<IPDObjectLocatable> objectTransformable = pObject->m_object;

						if ((objectType != OBJECT_FRAME) || (

							(gApp->m_activeSelectionTool == ID_TOOL_SELECT) &&

							(gApp->m_activeTool != ID_TOOL_PATHPEN) &&
							(gApp->m_activeTool != ID_TOOL_PATHCORNER) &&
							(gApp->m_activeTool != ID_TOOL_PATHADDANCHOR) &&
							(gApp->m_activeTool != ID_TOOL_PATHDELETEANCHOR) &&

							(gApp->m_activeTool != ID_TOOL_FREETRANSFORM) &&

							(gApp->m_activeTool != ID_TOOL_BULGE) &&
							(gApp->m_activeTool != ID_TOOL_TWIRL)))
						{
							// Draw bounding box
							if (objectTransformable)
							{
								RectD bounds;
								objectTransformable->get_bounds(&bounds);

								PointD pts[9] =
								{
									bounds.X, bounds.Y,
									bounds.X+bounds.Width/2, bounds.Y,
									bounds.X+bounds.Width, bounds.Y,
									bounds.X+bounds.Width, bounds.Y+bounds.Height/2,
									bounds.X+bounds.Width, bounds.Y+bounds.Height,
									bounds.X+bounds.Width/2, bounds.Y+bounds.Height,
									bounds.X, bounds.Y+bounds.Height,
									bounds.X, bounds.Y+bounds.Height/2,

									bounds.X+bounds.Width/2, bounds.Y+bounds.Height/2,	// center point
								};

								Gdiplus::Point	xpts[9];

								for (int i = 0; i < 9; i++)
								{
									PointD xpt;
									ctm->transformPoint(&pts[i], &xpt);

									if (m_freeTransformMatrix)
									{
										m_freeTransformMatrix->transformPoint(&xpt, &xpt);
									}

									xpts[i].X = xpt.x;
									xpts[i].Y = xpt.y;
								}

							// Outline
								graphics.DrawLine(&pen, xpts[0], xpts[2]);
								graphics.DrawLine(&pen, xpts[2], xpts[4]);
								graphics.DrawLine(&pen, xpts[4], xpts[6]);
								graphics.DrawLine(&pen, xpts[6], xpts[0]);

								if (!m_dragging)
								{
								// Size handles
									for (i = 0; i < 9; i++)
									{
										graphics.FillRectangle(&brush, (xpts[i].X-2), (xpts[i].Y-2), (4), (4));
									}

									CComQIPtr<IPDObjectFrame> frame = pObject->m_object;
									if (frame)
									{
										CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;
										pFrame->DrawThreadRects(&graphics, layerColor, ctm);
									}
								}
								else
								{
								// Center X
									int cx = (int)(xpts[8].X);
									int cy = (int)(xpts[8].Y);

									graphics.DrawLine(&pen, cx-2, cy+2, cx+2, cy-2);
									graphics.DrawLine(&pen, cx-2, cy-2, cx+2, cy+2);
								}
							}
						}
						else
						{
							// Draw path outline
							CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;

							if (m_dragging &&
								(gApp->m_activeTool == ID_TOOL_BULGE || gApp->m_activeTool == ID_TOOL_TWIRL))
							{
								pFrame->m_path->DrawPolyPoints(ctm, &graphics, &pen);
							}
							else
							{
								Gdiplus::GraphicsPath path;
								pFrame->m_path->DrawPath(ctm, freectm, &path);
								graphics.DrawPath(&pen, &path);
							}

							if (!m_dragging || m_freeTransformMatrix == NULL)
							{
								pFrame->m_path->DrawSelection(&graphics, layerColor, ctm);
								pFrame->DrawThreadRects(&graphics, layerColor, ctm);
							}
						}
					}
				}

				// ?
				graphics.TranslateTransform(m_activeSpreadOffset.x*m_magnify, m_activeSpreadOffset.y*m_magnify);

				if (gApp->m_activeTool == ID_TOOL_ROTATE ||
					gApp->m_activeTool == ID_TOOL_SCALE)
				{
					Gdiplus::Pen pen(Gdiplus::Color(0, 0, 0));

					float x = m_pivotPt.x*m_magnify;
					float y = m_pivotPt.y*m_magnify;

					graphics.DrawEllipse(&pen, (float)(x-4.0), (float)(y-4.0), (float)8.0, (float)8.0);
				}

				if (m_activeSpread)
				{
					CComQIPtr<IPDRenderer> renderer;
					renderer.CoCreateInstance(CLSID_PDRenderer);

					renderer->put_targetHDC((HDC)&graphics);
					renderer->put_magnify(m_magnify);

					RenderGuides(renderer, m_activeSpread, FALSE, TRUE);
				}

				if (m_dragging)
				{
					CComPtr<IPDMatrix> imatrix;
					m_matrix->inverse(&imatrix);

					PointD wpt;
					imatrix->transformPoint((PointD*)&m_dpt, &wpt);

					PointD woldpt;
					imatrix->transformPoint((PointD*)&m_doldpt, &woldpt);

					PointD wstartpt;
					imatrix->transformPoint((PointD*)&m_dstartpt, &wstartpt);

					if (m_dragging == 10 || m_dragging == 11)
					{
						CComQIPtr<IPDObjectLayerGroup> activeLayerGroup;
						if (m_activeSpread)
							m_activeSpread->getLayerGroupFromLayer(m_activeLayer, &activeLayerGroup);

						CComPtr<IPDLayer> layer;
						activeLayerGroup->get_layer(&layer);

						OLE_COLOR olelayerColor;
						layer->get_color(&olelayerColor);

						CComQIPtr<IPDRenderer> renderer;
						renderer.CoCreateInstance(CLSID_PDRenderer);

						renderer->put_targetHDC((HDC)&graphics);
						renderer->put_magnify(m_magnify);

						long spine;
						m_activeSpread->get_spine(&spine);

						double xoffset = (m_spine-spine)*pageWidth;

						renderer->RenderGuide(m_activeSpread, m_newGuide,
							olelayerColor,
							-(xoffset+100), -20, m_maxPages*pageWidth+200, pageHeight+40);
					}
					else if (m_activeLayer)
					{
						OLE_COLOR layerColor;
						m_activeLayer->get_color(&layerColor);

						Gdiplus::Pen pen(Gdiplus::Color(GetRValue(layerColor), GetGValue(layerColor), GetBValue(layerColor)));

						switch (m_activeTool)
						{
						case -10:	// Create new text frame
						case -11:
						case ID_TOOL_TEXT:
						case ID_TOOL_LINE:
						case ID_TOOL_RECTANGLE:
						case ID_TOOL_RECTANGLEGRAPHIC:
						case ID_TOOL_ELLIPSE:
						case ID_TOOL_ELLIPSEGRAPHIC:
							{
								double width = wpt.x-wstartpt.x;
								double height = wpt.y-wstartpt.y;

								switch (m_activeTool)
								{
								case -10:	// Create new text frame
									{
										graphics.DrawRectangle(&pen, (float)(m_newObjectBounds.X*m_magnify), (float)(m_newObjectBounds.Y*m_magnify), (float)(m_newObjectBounds.Width*m_magnify), (float)(m_newObjectBounds.Height*m_magnify));
									}
									break;

								case ID_TOOL_TEXT:
									{
										if (m_hit == 0)	// Create new text frame
										{
											graphics.DrawRectangle(&pen, (float)(m_newObjectBounds.X*m_magnify), (float)(m_newObjectBounds.Y*m_magnify), (float)(m_newObjectBounds.Width*m_magnify), (float)(m_newObjectBounds.Height*m_magnify));
										}
										/*
										else	// Selecting Text
										{
										}
										*/
									}
									break;

								case ID_TOOL_LINE:
									{
										float x1 = (float)((m_newObjectBounds.X)*m_magnify);
										float y1 = (float)((m_newObjectBounds.Y)*m_magnify);
										float x2 = (float)((m_newObjectBounds.X+m_newObjectBounds.Width)*m_magnify);
										float y2 = (float)((m_newObjectBounds.Y+m_newObjectBounds.Height)*m_magnify);

										graphics.DrawLine(&pen, x1, y1, x2, y2);
									}
									break;

								case ID_TOOL_RECTANGLE:
								case ID_TOOL_RECTANGLEGRAPHIC:
									{
										graphics.DrawRectangle(&pen, (float)(m_newObjectBounds.X*m_magnify), (float)(m_newObjectBounds.Y*m_magnify), (float)(m_newObjectBounds.Width*m_magnify), (float)(m_newObjectBounds.Height*m_magnify));
									}
									break;
									
								case ID_TOOL_ELLIPSE:
								case ID_TOOL_ELLIPSEGRAPHIC:
									{
										graphics.DrawEllipse(&pen, (float)(m_newObjectBounds.X*m_magnify), (float)(m_newObjectBounds.Y*m_magnify), (float)(m_newObjectBounds.Width*m_magnify), (float)(m_newObjectBounds.Height*m_magnify));
									}
									break;
								}

								int cx = (int)((float)(m_newObjectBounds.X+m_newObjectBounds.Width/2)*m_magnify);
								int cy = (int)((float)(m_newObjectBounds.Y+m_newObjectBounds.Height/2)*m_magnify);

								graphics.DrawLine(&pen, cx-2, cy+2, cx+2, cy-2);
								graphics.DrawLine(&pen, cx-2, cy-2, cx+2, cy+2);
							}
							break;
						}
					}
				}

				graphics.Restore(state);

				// Finally blit bitmap to screen
				{
					Gdiplus::Graphics dcGraphics(hDC);

					dcGraphics.DrawImage(pClipBitmap, irect.left, irect.top);
				}
			}

			delete pClipBitmap;
		}

	//	if (m_pActiveObject)
		{
			DrawTextSelection(hDC);
		}

		if (m_bBrushSizeVisible)
		{
			int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
			DrawBrushOutline(hDC, m_point);
			SetROP2(hDC, oldR2);
		}
	}

	EndPaint(&ps);
	return 0;
}

STDMETHODIMP CPDDocumentView::RenderObject(IPDRenderer* renderer, IPDObject* object)
{
	CComPtr<IPDLayer> layer;
	object->get_layer(&layer);

	OLE_COLOR olelayerColor;
	layer->get_color(&olelayerColor);

	Gdiplus::Graphics* pGraphics;
	renderer->get_targetHDC((HDC*)&pGraphics);

	CComQIPtr<IPDTextFrameOptions> textframe = object;
	if (textframe)
	{
		Gdiplus::Pen pen(Gdiplus::Color(GetRValue(olelayerColor), GetGValue(olelayerColor), GetBValue(olelayerColor)));

		CComPtr<IPDObject> parent;
		object->get_parent((IPDObjectUnknown**)&parent);

		CComQIPtr<IPDObjectTransformable> parentTransformable = parent;

		RectD bounds;
		parentTransformable->get_bounds(&bounds);

		long columns;
		textframe->get_columnsNumber(&columns);

		double columnGutter;
		textframe->get_columnsGutter(&columnGutter);

		if (columns > 1)
		{
			double innerWidth = bounds.Width - 0;// inset.left-inset.right
			double columnWidth = (innerWidth-(columns-1)*columnGutter)/columns;
			double x = bounds.X + columnWidth; // inset.left

			for (int i = 1; i < columns; i++)
			{
				pGraphics->DrawLine(&pen, (float)(x), (float)(bounds.Y), (float)(x), (float)(bounds.Y+bounds.Height));
				x += columnGutter;
				pGraphics->DrawLine(&pen, (float)(x), (float)(bounds.Y), (float)(x), (float)(bounds.Y+bounds.Height));
				x += columnWidth;
			}
		}
	}

	return S_OK;
}

void Normalize(Gdiplus::RectF& rc)
{
	if (rc.Width < 0)
	{
		rc.X += rc.Width;
		rc.Width = -rc.Width;
	}

	if (rc.Height < 0)
	{
		rc.Y += rc.Height;
		rc.Height = -rc.Height;
	}
}

RECT CPDDocumentView::GetWindowRectFromSpreadRect(Gdiplus::RectF& spreadRect)
{
	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	CRect wrc;

	float left = m_areaRect.left -scrollposX + (m_activeSpreadOffset.x + spreadRect.X)*m_magnify;
	float top = m_areaRect.top -scrollposY + (m_activeSpreadOffset.y + spreadRect.Y)*m_magnify;

	wrc.left = left;
	wrc.top = top;
	wrc.right = left + (spreadRect.Width)*m_magnify+0.5 + 1;
	wrc.bottom = top + (spreadRect.Height)*m_magnify+0.5 + 1;

	CRect wrc2;
	wrc2.IntersectRect(&wrc, &m_areaRect);

	return wrc2;
}

void CPDDocumentView::DrawTextSelection(HDC hDC)
{
	if (m_range)
	{
		long scrollposX; m_horz->get_pos(&scrollposX);
		long scrollposY; m_vert->get_pos(&scrollposY);

		POINT org;
		org.x = m_areaRect.left + -scrollposX;
		org.y = m_areaRect.left + -scrollposY;
		POINT oldOrg;
		SetViewportOrgEx(hDC, /*m_activeSpreadOffset.x +*/ org.x, /*m_activeSpreadOffset.y +*/ org.y, &oldOrg);
		int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

		CComPtr<ILDOMRange> range;
		m_range->GetDOMRange(&range);

		CComPtr<IPDStory> story;
		m_range->GetStory(&story);
		ATLASSERT(story);

		CComPtr<IObjectMap> textThreads;
		story->get_textContents(&textThreads);

		long ntextThreads;
		textThreads->get_length(&ntextThreads);

		for (int i = 0; i < ntextThreads; i++)
		{
			CComPtr<IPDObjectText> objectText;
			textThreads->item(i, (IUnknown**)&objectText);

			objectText->RenderSelection(hDC, m_matrix, range);
		}

		SetROP2(hDC, oldR2);
		SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

// TODO, get text story object fomr range, and draw selection over multiple text objects
#if 0
		if (m_pActiveObject)
		{
			CComQIPtr<IPDObjectText> contenttext;
			
			CComQIPtr<IPDObjectFrame> frame = m_pActiveObject->m_object;
			if (frame)
			{
				CComPtr<IPDObject> content;
				frame->get_content(&content);
				contenttext = content;
			}
			else
				contenttext = m_pActiveObject->m_object;
			
			if (contenttext)
			{
				POINT org;
				org.x = m_areaRect.left + /*m_offset.x*/-scrollposX;
				org.y = m_areaRect.left + /*m_offset.y*/-scrollposY;
				POINT oldOrg;
				SetViewportOrgEx(hDC, /*m_activeSpreadOffset.x +*/ org.x, /*m_activeSpreadOffset.y +*/ org.y, &oldOrg);
				int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
				
				CComPtr<IRange> range;
				m_range->GetDOMRange(&range);
				
				contenttext->RenderSelection(hDC, m_matrix, range);
				
				SetROP2(hDC, oldR2);
				SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
			}
		}
#endif
	}
}

LRESULT CPDDocumentView::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return TRUE;
}

LRESULT CPDDocumentView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_axhorz.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axhorz.AttachControl(m_horz, &p);
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);

	IDispEventImpl<1, CPDDocumentView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);
	IDispEventImpl<2, CPDDocumentView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	m_hWndSizeGrip = ::CreateWindow("SCROLLBAR", NULL, WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP, 0, 0, 0, 0, m_hWnd, NULL, _Module.m_hInst, NULL);

//	IDispEventImpl<3, CPDDocumentView, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventAdvise(m_document);

	DWORD cookie;

	CComQIPtr<INotifySend> cp;
	
	cp = m_document;
	cp->Advise(this, &cookie);

	cp = gIApp;
	cp->Advise(this, &cookie);

	m_nIDTimer = SetTimer(1, 200);

	return 0;
}

LRESULT CPDDocumentView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CPDDocumentView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);
	IDispEventImpl<2, CPDDocumentView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	KillTimer(m_nIDTimer);
	m_nIDTimer = 0;

	CComQIPtr<INotifySend> cp;

	cp= m_document;
	cp->Unadvise(this);

	cp = gIApp;
	cp->Unadvise(this);

//	IDispEventImpl<3, CPDDocumentView, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventUnadvise(m_document);
	return 0;
}

LRESULT CPDDocumentView::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CPDDocumentView::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SetFocus();

	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	m_point = point;

	if (!m_dragging)
	{
		long scrollposX; m_horz->get_pos(&scrollposX);
		long scrollposY; m_vert->get_pos(&scrollposY);

		CComQIPtr<IPDObjectLayerGroup> activeLayerGroup;
		if (m_activeSpread)
			m_activeSpread->getLayerGroupFromLayer(m_activeLayer, &activeLayerGroup);

		POINT pt = point;
		pt.x -= m_areaRect.left;
		pt.y -= m_areaRect.top;
		pt.x += scrollposX;
		pt.y += scrollposY;

		CDblPoint dpt;
		dpt.x = pt.x;
		dpt.y = pt.y;

		CComPtr<IPDMatrix> imatrix;
		m_matrix->inverse(&imatrix);

		PointD wpt;
		imatrix->transformPoint((PointD*)&dpt, &wpt);

		PointD woldpt;
		imatrix->transformPoint((PointD*)&m_doldpt, &woldpt);

		PointD wstartpt;
		imatrix->transformPoint((PointD*)&m_dstartpt, &wstartpt);

		m_oldBounds.X = 9999999;
		m_oldBounds.Y = 9999999;
		m_oldBounds.Width = -9999999;
		m_oldBounds.Height = -9999999;

		if (point.y < m_areaRect.top || point.x < m_areaRect.left)
		{
			if (m_bRulers)
			{
				if (activeLayerGroup)
				{
					if (point.x < m_areaRect.left && point.y < m_areaRect.top)	// Corner
					{
						m_dragging = 9;
						::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_CROSSHAIR)));
					}
					else
					{
						CComPtr<IPDGuides> guides;
						activeLayerGroup->get_guides(&guides);

						if (point.y < m_areaRect.top)	// Horizontal guide
						{
							m_dragging = 10;
							guides->createGuide(0, &m_newGuide);
						}
						else if (point.x < m_areaRect.left)	// Vertical guide
						{
							m_dragging = 11;
							guides->createGuide(1, &m_newGuide);
						}
					}
				}
				else
				{
					::MessageBox(GetMainHwnd(), "You must select a layer & spread", "PageDesigner", MB_OK);
				}
			}
		}
		else
		{
			if (!(nFlags & MK_CONTROL))
				m_activeTool = gApp->m_activeTool;
			else
				m_activeTool = gApp->m_activeSelectionTool;

			switch (m_activeTool)
			{
			case -12:
				{
					if (m_objectToPlace)
					{
						CComQIPtr<IPDContentGraphic> contentGraphic = m_objectToPlace;
						if (contentGraphic)
						{
							contentGraphic->setxy(wpt.x, wpt.y);	// Couldn't move be used here?
						}
						else
						{
							CComQIPtr<IPDObjectTransformable> objectTransformable = m_objectToPlace;

							if (objectTransformable)
							{
								objectTransformable->Move(wpt.x, wpt.y);
							}
						}

						activeLayerGroup->appendObject(m_objectToPlace);

						m_objectToPlace.Release();
					}

					gApp->m_activeTool = gApp->m_activeSelectionTool;
				}
				break;

			case ID_TOOL_SELECT:
				{
					CComPtr<IPDGuide> guide = GetGuideUnderPoint(wpt.x, wpt.y);
					if (guide)
					{
						SelectPDObject(guide, nFlags, FALSE);

					//	m_bInvalid = true;
					//	UpdateWindow();

						if (m_pActiveObject)
						{
							m_dragging = 3;
						}
						break;
					}
	
					if (activeLayerGroup)
					{
						CHitData hitdata;
						CComPtr<IPDObject> object;
						GetObjectUnderPoint(dpt, 1, &hitdata, &object);
						m_hit = hitdata.hit;

						SelectPDObject(object, nFlags, TRUE);

						if (m_pActiveObject)
						{
							if (g_bFastFeedback)
							{
								if (m_hit == 1)
								{
									for (int i = 0; i < m_targetObjects.GetSize(); i++)
									{
										CComQIPtr<INotifySend> cp = m_targetObjects[i]->m_object;
										if (cp) cp->LockSend();
									}
								}
								else
								{
									CComQIPtr<INotifySend> cp = m_pActiveObject->m_object;
									if (cp) cp->LockSend();
								}
							}

							m_dragging = 1;
						}
						else
						{
							m_dragging = 2;	// Select rectangle
						}
					}
					else
					{
						::MessageBox(GetMainHwnd(), "You must select a layer and a spread", "PageDesigner", MB_OK);
					}
				}
				break;

			case ID_TOOL_DIRECT:
			case ID_TOOL_PATHPEN:
				//case ID_TOOL_PENFREE:
			case ID_TOOL_PATHADDANCHOR:
			case ID_TOOL_PATHDELETEANCHOR:
			case ID_TOOL_PATHCORNER:
				{
					if (m_activeTool == ID_TOOL_DIRECT)
					{
						if (m_pActiveObject)
						{
							CComQIPtr<IPDObjectFrame> object = m_pActiveObject->m_object;
							if (object)
							{
								CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)m_pActiveObject;
								//CComQIPtr<IPDObjectTransformable> objectTransformable = pFrame->m_object;

								CComPtr<IPDObject> content;
								object->get_content(&content);

								CComQIPtr<IPDContentText> contentText = content;
								if (contentText)
								{
									PointD threadPtIn;
									PointD threadPtOut;

									contentText->get_threadPtIn(&threadPtIn);
									contentText->get_threadPtOut(&threadPtOut);

									CComPtr<IPDMatrix> ctm0;
									object->getScreenCTM(&ctm0);

									CComPtr<IPDMatrix> ctm;
									ctm0->multiply(m_matrix, &ctm);

									PointD xthreadPtOut;
									ctm->transformPoint((PointD*)&threadPtOut, &xthreadPtOut);

									PointD xthreadPtIn;
									ctm->transformPoint((PointD*)&threadPtIn, &xthreadPtIn);

									Gdiplus::RectF rcIn(xthreadPtIn.x-4, xthreadPtIn.y-4, 8, 8);
									Gdiplus::RectF rcOut(xthreadPtOut.x-4, xthreadPtOut.y-4, 8, 8);

									if (rcIn.Contains(dpt.x, dpt.y))
									{
										// TODO remember old tool
										gApp->m_activeTool = -10;
										break;
									}
									else if (rcOut.Contains(dpt.x, dpt.y))
									{
										// TODO remember old tool
										gApp->m_activeTool = -11;
										break;
									}
								}
							}
						}

						CHitData hitdata;
						CComPtr<IPDObject> object;
						GetObjectUnderPoint(dpt, m_bAlt? 3: 2, &hitdata, &object);

					//	m_hit = hitdata.hit;	// ??

					// If didn't hit any path, select normal way
						// Do I need this first if (?)
						if ((hitdata.anchor < 0 && hitdata.segment < 0))
						{
							SelectPDObject(object, nFlags, FALSE);
						}
						else
						{
							if (IsPDObjectSelected(object))
							{
								SelectPDObject(object, 0, FALSE);
							}
							else
							{
								SelectPDObject(object, nFlags, FALSE);
							}
						}

						if (hitdata.path)
						{
							CPathSelection* pPath = GetPDPathSelected(hitdata.path);

							ATLASSERT(pPath);	// hmm.. ??

							if (hitdata.anchor >= 0)
							{
								if (hitdata.ctl == 0)	// Clicked on anchor point
								{
									if (nFlags & MK_SHIFT)
									{
										// Toggle selection of anchor point
										if (pPath->IsAnchorSelected(hitdata.anchor))
										{
											pPath->DeselectAnchor(hitdata.anchor);
										}
										else
										{
											m_pActivePath = pPath;	// ??
											m_curveCp = hitdata.anchor;
											m_curveCtl = hitdata.ctl;

											pPath->SelectAnchor(m_curveCp);

											m_hit = 1;
											m_dragging = 1;
										}
									}
									else
									{
										m_pActivePath = pPath;	// ??
										m_curveCp = hitdata.anchor;
										m_curveCtl = hitdata.ctl;

										if (!pPath->IsAnchorSelected(hitdata.anchor))
										{
											for (int i = 0; i < m_targetObjects.GetSize(); i++)
											{
												CPDObjectSelected* pObject = m_targetObjects[i];

												if (pObject->m_wrapPath)
												{
													pObject->m_wrapPath->DeselectAllPoints();
												}

												CComQIPtr<IPDObjectFrame> frame = pObject->m_object;
												if (frame)
												{
													CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;
													pFrame->m_path->DeselectAllPoints();
												}
											}

											pPath->SelectAnchor(m_curveCp);
										}

										m_hit = 1;
										m_dragging = 1;
									}
								}
								else	// Move control point
								{
									m_pActivePath = pPath;
									m_curveCp = hitdata.anchor;
									m_curveCtl = hitdata.ctl;

									m_hit = 2;
									m_dragging = 1;
								}
							}
							else if (hitdata.segment >= 0)	// Clicked on segment
							{
								if (pPath->IsSegmentSelected(hitdata.segment))
								{
									if (!(nFlags & MK_SHIFT))
									{
										pPath->DeselectSegment(hitdata.segment);
									}
								}
								else
								{
									pPath->SelectSegment(hitdata.segment);
									//m_pActivePath = pPath;	// ??
								}
							}
						}
						else
						{
							// Direct Selection Rectangle
							m_hit = 0;
							m_dragging = 1;
						}
						
						InvalidateRect(&m_areaRect);
					}
					else
					{
						if (activeLayerGroup)
						{
							CPDObjectFrameSelected* pObject = NULL;
							CComQIPtr<IPDObjectFrame> path;

							UINT nResource = 0;

							CHitData hitdata;
							CComPtr<IPDObject> object;
							GetObjectUnderPoint(dpt, 2, &hitdata, &object);

							long subpathcurveCp = -1;
							long nactivesubpathPoints = 0;
							VARIANT_BOOL activesubpathClosed = 0;
							CComPtr<IPDSubPath> activesubpath;
							if (m_pActivePath)
							{
								ATLASSERT(m_curveCp >= 0);
								m_pActivePath->GetPDPath()->getSubPathFromIndex(m_curveCp, &subpathcurveCp, &activesubpath);

								activesubpath->get_closed(&activesubpathClosed);
								activesubpath->get_pointCount(&nactivesubpathPoints);
							}

							if (object)
							{
								CPathSelection* pPath = GetPDPathSelected(hitdata.path);

								if (hitdata.anchor >= 0)
								{
									CComPtr<IPDSubPath> subpath;
									long subpathIndex;
									hitdata.path->getSubPathFromIndex(hitdata.anchor, &subpathIndex, &subpath);

									long nsubpathPoints;
									subpath->get_pointCount(&nsubpathPoints);

									VARIANT_BOOL closed;
									subpath->get_closed(&closed);

									if (nResource == 0)
									{
										if (m_pActivePath && m_pActivePath == pPath && activesubpath == subpath && !closed && hitdata.ctl == 0)
										{
											if ((subpathIndex == 0 && subpathcurveCp == nsubpathPoints-1) ||
												(subpathIndex == nsubpathPoints-1 && subpathcurveCp == 0))
											{
												// Close
												subpath->put_closed(VARIANT_TRUE);

												m_pActivePath = NULL;
												m_curveCp = -1;

												nResource = 1;
											}
											else if ((subpathIndex == 0 && subpathcurveCp == 0) ||
														(subpathIndex == nsubpathPoints-1 && subpathcurveCp == nsubpathPoints-1))
											{
											// Change first/last point on curve
												ATLASSERT(m_pActivePath);

												if (subpathcurveCp == 0)
													m_curveDir = m_curveCtl = -1;
												else
													m_curveDir = m_curveCtl = 1;

												m_curveCp = hitdata.anchor;

												if (!m_pActivePath->IsAnchorSelected(m_curveCp))
													m_pActivePath->SelectAnchor(m_curveCp);

												m_dragging = 1;
												m_hit = 2;

												nResource = 1;
											}
										}
									}

									if (nResource == 0)
									{
										if (m_pActivePath != NULL &&
											hitdata.ctl == 0 &&
											!closed &&
											!activesubpathClosed &&
											subpath != activesubpath &&
											(subpathcurveCp == 0 || subpathcurveCp == nactivesubpathPoints-1) &&
											(subpathIndex == 0 || subpathIndex == nsubpathPoints-1))
										{
											// Connect

											m_pActivePath->DeselectAllPoints();

											m_pActivePath->GetPDPath()->removeSubPath(activesubpath);

											if (subpathcurveCp == nactivesubpathPoints-1)
											{
												activesubpath->reverse();
											}

											if (subpathIndex == 0)
											{
												subpath->reverse();
											}

											subpath->appendSubPathPoints(activesubpath);

											m_pActivePath = NULL;
											m_curveCp = -1;

											nResource = 1;
										}
									}

									if (nResource == 0)
									{
										if (pPath &&
											!closed && hitdata.ctl == 0 &&
											((subpathIndex == 0) || (subpathIndex == nsubpathPoints-1)))
										{
											// Continue
											m_pActivePath = pPath;

											m_pActivePath->DeselectAllPoints();

											if (subpathIndex == nsubpathPoints-1)
												m_curveDir = m_curveCtl = 1;
											else
												m_curveDir = m_curveCtl = -1;

											m_curveCp = hitdata.anchor;

											m_pActivePath->SelectAnchor(m_curveCp);

											nResource = 1;
										}
									}

									if (nResource == 0)
									{
										if (pPath && hitdata.ctl == 0)
										{
										// Delete anchor point
											pPath->DeleteAnchorPoint(hitdata.anchor);
											if (m_curveCp >= hitdata.anchor) m_curveCp--;

											nResource = 1;
										}
									}
								}
								else if (hitdata.segment >= 0)
								{
									if (pPath)
									{
										pPath->DeselectAllPoints();

										m_pActivePath = pPath;
										m_curveCp = hitdata.segment+1;

										pPath->GetPDPath()->insertAnchorPointAt(hitdata.segment, hitdata.t);
										pPath->SelectAnchor(m_curveCp);

										m_curveDir = 1;
										m_curveCtl = 1;
										m_hit = 1;
										m_dragging = 1;

										nResource = 1;
									}
								}
							}

							if (nResource == 0)
							{
								if (m_pActivePath &&
									(subpathcurveCp == 0 || subpathcurveCp == nactivesubpathPoints-1))
								{
									m_pActivePath->DeselectAllPoints();

									if (m_curveDir == 1)	// Insert point at end
									{
										m_pActivePath->InsertPointAfter(m_curveCp, wpt.x, wpt.y, wpt.x, wpt.y, wpt.x, wpt.y);
										m_curveCp++;
									}
									else if (m_curveDir == -1)	// Insert point at beginning
									{
										m_pActivePath->InsertPointBefore(m_curveCp, wpt.x, wpt.y, wpt.x, wpt.y, wpt.x, wpt.y);
										//m_curveCp--;
									}
									else
										ATLASSERT(0);

									m_pActivePath->SelectAnchor(m_curveCp);
									m_curveCtl = m_curveDir;
									m_hit = 1;
									m_dragging = 1;

									nResource = 1;
								}
							}

							if (nResource == 0)
							{
								CPDObjectFrameSelected* pObject = NULL;

								// Create new path element
								CComQIPtr<IPDObjectFrame> path;
								m_document->createObjectFrame(&path);

								//CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill = m_document;
								//path->copyAppearanceFrom(strokeFill);
								CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill2 = m_document;
								CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill = path;
								strokeFill->copyAppearanceFrom(VARIANT_TRUE, strokeFill2);

								CComQIPtr<IPDPath> pathData;
								path->get_path(&pathData);

								CComQIPtr<IPDSubPath> subPath;
								pathData->createSubPath(&subPath);
								pathData->insertSubPath(-1, subPath);

								subPath->appendPoint(wpt.x, wpt.y, wpt.x, wpt.y, wpt.x, wpt.y, &m_curveCp);
								ATLASSERT(m_curveCp == 0);

								m_curveDir = m_curveCtl = 1;

								activeLayerGroup->appendObject(path);
								pObject = (CPDObjectFrameSelected*)SelectPDObject(path, 0, FALSE);

								m_pActivePath = pObject->m_path;

								m_pActivePath->SelectAnchor(m_curveCp);
								m_hit = 1;
								m_dragging = 1;

								nResource = 1;
							}

							InvalidateRect(&m_areaRect);	// Remove this
						}
						else
						{
							::MessageBox(GetMainHwnd(), "You must select a layer and a spread", "PageDesigner", MB_OK);
						}
					}

					if (m_dragging && m_hit != 0)
					{
						if (m_curveCtl == 0)	// Clicked on anchor point
						{
							for (int i = 0; i < m_targetObjects.GetSize(); i++)
							{
								CPDObjectSelected* pObject = m_targetObjects[i];

								PDObjectType objectType;
								pObject->m_object->get_objectType(&objectType);

								if (pObject->m_wrapPath)
								{
									CComQIPtr<INotifySend> cp = pObject->m_wrapPath->GetPDPath();
									cp->LockSend();
								}

								if (objectType == OBJECT_FRAME)
								{
									CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;
									CComQIPtr<INotifySend> cp = pFrame->m_path->GetPDPath();
									cp->LockSend();
								}
							}
						}
						else
						{
							CComQIPtr<INotifySend> cp = m_pActivePath->GetPDPath();
							cp->LockSend();
						}
					}
				}
				break;

			case -10:
				{
					CHitData hitdata;
					CComPtr<IPDObject> object;
					GetObjectUnderPoint(dpt, 2, &hitdata, &object);

					CComQIPtr<IPDObjectFrame> frame = object;

					if (frame)	// Link into existing text frame
					{
					}
					else
					{
						// Create new text frame
						m_dragging = 1;
						m_hit = 0;
					}
				}
				break;

			case ID_TOOL_TEXT:
				{
					if (activeLayerGroup)
					{
						CHitData hitdata;
						CComPtr<IPDObject> object;
						GetObjectUnderPoint(dpt, 4, &hitdata, &object);
						m_hit = hitdata.hit;

						SelectPDObject(object, nFlags, TRUE);

						if (m_hit == 0)
						{
							m_dragging = 1;
						}
						else if (hitdata.pNode)
						{
							CComQIPtr<IUIManager> uiManager = gIFrame;

							CComQIPtr<IPDObjectText> textObject = object;
							ATLASSERT(textObject);

							CComPtr<IPDStory> story;
							textObject->get_story(&story);

							// Dectivate/Release previous range
							if (m_range)
							{
								uiManager->DeactivateObject(m_range);
								m_range.Release();
							}

							story->NewSelection(&m_range);
							if (m_range)
							{
								m_range->Set(hitdata.pNode, hitdata.offset);
								/*
								CComPtr<IRange> domrange;
								m_range->GetDOMRange(&domrange);

								m_initContainer = hitdata.pNode;
								m_initOffset = hitdata.offset;

								m_curContainer = m_initContainer;
								m_curOffset = m_initOffset;

								domrange->setStart(m_initContainer, m_initOffset);
								domrange->setEnd(m_initContainer, m_initOffset);
								*/

								m_dragging = 1;
							}
						}

						Invalidate();	// TODO, remove
					}
					else
					{
						::MessageBox(GetMainHwnd(), "You must select a layer and a spread", "PageDesigner", MB_OK);
					}
				}
				break;

			case ID_TOOL_TEXTPATH:
				{
					if (activeLayerGroup)
					{
					//	CComQIPtr<IPDMatrix> pdmatrix;
					//	activeLayerGroup->getScreenCTM(&pdmatrix);

						//int hit = 0;
						CHitData hitdata;
						CComPtr<IPDObject> object;
						GetObjectUnderPoint(dpt, 5, &hitdata, &object);
						CComQIPtr<IPDObjectFrame> frame = object;

						if (frame)
						{
						// TODO do this in lbuttonup

						// Create new story
							CComPtr<IPDStory> story;
							m_document->createStory(&story);

						// Create PathText
							CComPtr<IPDPathText> content;
							m_document->createPathText(&content);
							frame->put_pathText(content);

							story->appendTextThread(content);

						// Finally append the story to the document
							m_document->appendStory(story);

							SelectPDObject(frame, 0, FALSE);

							Invalidate();
						}
					}
					else
					{
						::MessageBox(GetMainHwnd(), "You must select a layer and a spread", "PageDesigner", MB_OK);
					}
				}
				break;

			case ID_TOOL_SCALE:
			case ID_TOOL_ROTATE:
				{
					if (fabs(wpt.x-m_pivotPt.x) < 8 &&
						fabs(wpt.y-m_pivotPt.y) < 8)
					{
						m_dragging = 2;
					}
					else
					{
						m_dragging = 1;
					}
				}
				break;

			case ID_TOOL_FREETRANSFORM:
				{
					m_dragging = 0;

				// All objects must be transformable
					for (int i = 0; i < m_targetObjects.GetSize(); i++)
					{
						CComQIPtr<IPDObjectTransformable> objectTransformable = m_targetObjects[i]->m_object;
						if (objectTransformable)
						{
							m_dragging = 1;
						}
						else
						{
							m_dragging = 0;
							break;
						}
					}

					if (m_dragging)
					{
						// Remember initial matrix of all objects
						for (int i = 0; i < m_targetObjects.GetSize(); i++)
						{
							CComQIPtr<IPDObjectTransformable> objectTransformable = m_targetObjects[i]->m_object;
							if (objectTransformable)
							{
								CComPtr<IPDMatrix> mat;
								objectTransformable->get_transformMatrix(&mat);

								m_targetObjects[i]->m_initialMatrix.Release();
								m_targetObjects[i]->m_initialMatrix.CoCreateInstance(CLSID_PDMatrix);

								m_targetObjects[i]->m_initialMatrix->copyFrom(mat);
							}
						}

						RectD bounds = m_objectsBoundingBox;

						m_hit = 0;

						{
							PointD pts[8] =
							{
								bounds.X, bounds.Y,
								bounds.X+bounds.Width/2, bounds.Y,
								bounds.X+bounds.Width, bounds.Y,
								bounds.X+bounds.Width, bounds.Y+bounds.Height/2,
								bounds.X+bounds.Width, bounds.Y+bounds.Height,
								bounds.X+bounds.Width/2, bounds.Y+bounds.Height,
								bounds.X, bounds.Y+bounds.Height,
								bounds.X, bounds.Y+bounds.Height/2,
							};

							PointD xpts[8];
							for (int npt = 0; npt < 8; npt++)
							{
								m_matrix->transformPoint(&pts[npt], &xpts[npt]);
							}

							for (int i = 0; i < 8; i++)
							{
								if ((fabs(dpt.x-xpts[i].x) <= 6) && (fabs(dpt.y-xpts[i].y) <= 6))
								{
									m_offsetPt.x = (dpt.x-xpts[i].x)*m_magnify;
									m_offsetPt.y = (dpt.y-xpts[i].y)*m_magnify;

									m_hit = i+2;
									break;
								}
							}

							if (m_hit)
							{
							}
						}

						if (m_hit == 0)
						{
							CComPtr<IPDMatrix> imatrix;
							m_matrix->inverse(&imatrix);

							PointD xpt;
							imatrix->transformPoint((PointD*)&dpt, &xpt);

							if (xpt.x > bounds.X && xpt.y > bounds.Y &&
								xpt.x < bounds.X+bounds.Width && xpt.y < bounds.Y+bounds.Height)
							{
								m_hit = 1;	// Inside
							}
							else	// Outside (Rotate)
							{
								m_pivotPt.x = bounds.X + bounds.Width/2;
								m_pivotPt.y = bounds.Y + bounds.Height/2;

								m_hit = 0;
							}
						}

						ATLASSERT(m_freeTransformMatrix == NULL);
						m_freeTransformMatrix.CoCreateInstance(CLSID_PDMatrix);

					//	ATLASSERT(m_oldfreeTransformMatrix == NULL);
					//	m_oldfreeTransformMatrix.CoCreateInstance(CLSID_PDMatrix);
					}
				}
				break;

			case ID_TOOL_TWIRL:
			case ID_TOOL_BULGE:
				{
					if (m_bAlt)	// Size brush
					{
						CComQIPtr<IPDBrushSettings> brushSettings = gIApp;
						brushSettings->get_brushWidth(&m_brushSize.x);
						brushSettings->get_brushHeight(&m_brushSize.y);

						m_hit = 2;
						m_dragging = 1;
					}
					else
					{
						if (m_targetObjects.GetSize() > 0)
						{
							for (int i = 0; i < m_targetObjects.GetSize(); i++)
							{
								CPDObjectSelected* pObject = m_targetObjects[i];
								if (pObject->m_wrapPath)
								{
									pObject->m_wrapPath->SetPolyPointsFromSegList();
									m_dragging = 1;
								}

								PDObjectType objectType;
								pObject->m_object->get_objectType(&objectType);
								if (objectType == OBJECT_FRAME)
								{
									CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;

									pFrame->m_path->SetPolyPointsFromSegList();
									m_dragging = 1;
								}
							}

							if (m_dragging)
							{
								m_hit = 1;
							}
						}
					}
				}
				break;

			case ID_TOOL_GRADIENT:
				{
					m_dragging = 1;
				}
				break;

			case ID_TOOL_ZOOM:
				{
					m_dragging = 1;
					m_zoomRect.SetRectEmpty();
				}
				break;

			case ID_TOOL_HAND:
				{
					m_scrollpos.x = scrollposX;
					m_scrollpos.y = scrollposY;

					::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_HAND2)));
					m_dragging = 1;
				}
				break;

			case ID_TOOL_ELLIPSE:
			case ID_TOOL_ELLIPSEGRAPHIC:
			case ID_TOOL_RECTANGLE:
			case ID_TOOL_RECTANGLEGRAPHIC:
			case ID_TOOL_LINE:
				{
					if (activeLayerGroup)
					{
						m_dragging = 1;
					}
					else
					{
						::MessageBox(GetMainHwnd(), "You must select a layer and a spread", "PageDesigner", MB_OK);
					}
				}
				break;
			}
		}

		if (m_dragging)
		{
			m_startDragCursor = ::GetCursor();
			SetCapture();

			m_startpoint = point;
			m_oldpoint = point;

			m_startpt = pt;
			m_oldpt = pt;

			m_dstartpt = dpt;
			m_dpt = m_dstartpt;
			m_doldpt = m_dpt;
		}
	}

	return 0;
}

LRESULT CPDDocumentView::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	if (!m_dragging)
	{
		if (point.x < 16 && point.y < 16)
		{
			setRulerOrigin(0, 0);
		}
	}

	return 0;
}

void CPDDocumentView::SelectObjectsWithinRect(IPDObject* object, IPDMatrix* /* matrix*/, Gdiplus::RectF& rect, int tool, int& hit)
{
	CComQIPtr<IPDObjectTransformable> objectTransformable = object;

	CComPtr<IPDObject> parent;
	object->get_parent((IPDObjectUnknown**)&parent);

	PDObjectType objectType;
	object->get_objectType(&objectType);

	RectD bounds;
	objectTransformable->get_bounds(&bounds);

	CComPtr<IPDObject> fobject;

	hit = 0;

	CComPtr<IPDMatrix> ctm0;
	object->getScreenCTM(&ctm0);

	CComPtr<IPDMatrix> ctm;
	ctm0->multiply(m_matrix, &ctm);

	{
		/*
		if (IsPDObjectSelected(object))
		{
			PointD pts[8] =
			{
				bounds.X, bounds.Y,
				bounds.X+bounds.Width/2, bounds.Y,
				bounds.X+bounds.Width, bounds.Y,
				bounds.X+bounds.Width, bounds.Y+bounds.Height/2,
				bounds.X+bounds.Width, bounds.Y+bounds.Height,
				bounds.X+bounds.Width/2, bounds.Y+bounds.Height,
				bounds.X, bounds.Y+bounds.Height,
				bounds.X, bounds.Y+bounds.Height/2,
			};

			PointD xpts[8];
			for (int npt = 0; npt < 8; npt++)
			{
				ctm->transformPoint(&pts[npt], &xpts[npt]);
			}

			for (npt = 0; npt < 8; npt++)
			{
				if ((fabs(pt.x-xpts[npt].x) <= 3) && (fabs(pt.y-xpts[npt].y) <= 3))
				{
					hit = npt+2;
					fobject = object;
					break;
				}
			}
		}
		*/

		if (hit == 0)
		{
			//CComPtr<IPDMatrix> ictm;
			//ctm->inverse(&ictm);

			//PointD xpt;
			//ictm->transformPoint((PointD*)&pt, &xpt);

			if (objectType == OBJECT_FRAME)
			{
				// TODO, the following must be available through IPDObjectFrame object
				/*
				CComQIPtr<IPDObjectFrame> frame = object;

				CComPtr<IPDPath> pdpath;
				frame->get_path(&pdpath);

				double strokeWeight;
				frame->get_strokeWeight(&strokeWeight);

				Gdiplus::GraphicsPath path;
				DrawPath(pdpath, ctm, &path);

				Gdiplus::Pen pen(Gdiplus::Color(255, 255, 255), strokeWeight);

				path.Widen(&pen);
				path.Outline();

				Gdiplus::Region pathrgn(&path);

				//Gdiplus::RectF rgnbounds;
				//pathrgn.GetBounds(&rgnbounds);

				BOOL bOver = pathrgn.IsVisible(rect);

				if (bOver)
				{
					fobject = object;
					hit = 1;
				}
				*/
			}
			/*
			else if (objectType == CONTENT_GRAPHIC)
			{
				if (xpt.x >= bounds.X && xpt.y >= bounds.Y &&
					xpt.x < bounds.X+bounds.Width && xpt.y < bounds.Y+bounds.Height)
				{
					fobject = object;
					hit = 1;
				}
			}
			*/
		}
	}

	if (hit == 0)
	{
		CComPtr<IObjectMap> children;
		object->get_children(&children);

		if (children)
		{
			long length;
			children->get_length(&length);
			for (long n = 0; n < length; n++)
			{
				CComQIPtr<IPDObject> subobject;
				children->item(n, (IUnknown**)&subobject);

			// Recurse
				/*fobject =*/ SelectObjectsWithinRect(subobject, NULL, rect, tool, hit);
				/*if (fobject)
				{
					break;
				}
				*/
			}
		}
	}

	if (tool == 1)	// Selection tool
	{
		if (fobject)
		{
			if (parent != NULL)
			{
				SelectPDObject(object, MK_SHIFT, TRUE);
				//return object;
			}
		}
	}
	else if (tool == 2)	// Direct selection tool
	{
		if (fobject)
			SelectPDObject(fobject, MK_SHIFT, TRUE);//return fobject.Detach();
	}
	else if (tool == 3)	// Group selection tool
	{
		if (fobject)
		{
			if (IsPDObjectSelected(object))
			{
				SelectPDObject(parent, MK_SHIFT, TRUE);
				//return parent.Detach();
			}
		}
	}
}

void CPDDocumentView::SelectObjectsWithinRect(Gdiplus::RectF& rect, int tool, int& hit)
{
	CComPtr<IObjectMap> layergroups;
	m_activeSpread->get_layergroups(&layergroups);

	long nlayergroups;
	layergroups->get_length(&nlayergroups);

	for (int nlayer = 0; nlayer < nlayergroups; nlayer++)
	{
		CComPtr<IPDObject> layergroup;
		layergroups->item(nlayer, (IUnknown**)&layergroup);

		CComQIPtr<IPDMatrix> pdmatrix;
		pdmatrix.CoCreateInstance(CLSID_PDMatrix);

	//	CComQIPtr<IPDObjectTransformable> objectTransformable = layergroup;
	//	layergroup->getScreenCTM(&pdmatrix);

		SelectObjectsWithinRect(layergroup, pdmatrix, rect, tool, hit);
	}
}

#include "RectangleOptionsDlg.h"
#include "EllipseOptionsDlg.h"

LRESULT CPDDocumentView::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_dragging)
	{
		CComQIPtr<IPDObjectLayerGroup> activeLayerGroup;
		if (m_activeSpread)
			m_activeSpread->getLayerGroupFromLayer(m_activeLayer, &activeLayerGroup);

		ReleaseCapture();
		int dragging = m_dragging;
		m_dragging = 0;

		CComPtr<IPDMatrix> imatrix;
		m_matrix->inverse(&imatrix);

		PointD wpt;
		imatrix->transformPoint((PointD*)&m_dpt, &wpt);

		PointD woldpt;
		imatrix->transformPoint((PointD*)&m_doldpt, &woldpt);

		PointD wstartpt;
		imatrix->transformPoint((PointD*)&m_dstartpt, &wstartpt);

		if (dragging == 9)
		{
			{
				HDC hDC = GetDC();

				POINT org;
				org.x = m_areaRect.left + /*m_offset.x*/-scrollposX;
				org.y = m_areaRect.top + /*m_offset.y*/-scrollposY;

				int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

			// Erase old
				if (m_oldpoint.y >= 16) DrawStippledLineH(hDC, m_doldpt.y+org.y, m_areaRect.left, m_areaRect.right);
				if (m_oldpoint.x >= 16) DrawStippledLineV(hDC, m_doldpt.x+org.x, m_areaRect.top, m_areaRect.bottom);

				SetROP2(hDC, oldR2);

				ReleaseDC(hDC);
			}

			double originx = m_rulerOffset.x;
			double originy = m_rulerOffset.y;

			if (point.x >= 16) originx = wpt.x;
			if (point.y >= 16) originy = wpt.y;

			setRulerOrigin(originx, originy);
		}
		else if (dragging == 10 || dragging == 11)
		{
			if (point.x > m_areaRect.left && point.y > m_areaRect.top)
			{
				CComPtr<IPDGuides> guides;
				activeLayerGroup->get_guides(&guides);

				guides->appendGuide(m_newGuide);
			}

			m_newGuide.Release();

			m_bInvalid = true;
			InvalidateRect(NULL);
		}
		else
		{
			switch (m_activeTool)
			{
			case ID_TOOL_SELECT:
				{
					if (dragging == 2)	// Dragged selection rectangle
					{
						DeselectAll();

						Gdiplus::RectF rect;

					// Make sure the rect is Normalized
						if (m_dstartpt.x < m_doldpt.x)
						{
							rect.X = m_dstartpt.x;
							rect.Width = m_doldpt.x - m_dstartpt.x;
						}
						else
						{
							rect.X = m_doldpt.x;
							rect.Width = m_dstartpt.x - m_doldpt.x;
						}

						if (m_dstartpt.y < m_doldpt.y)
						{
							rect.Y = m_dstartpt.y;
							rect.Height = m_doldpt.y - m_dstartpt.y;
						}
						else
						{
							rect.Y = m_doldpt.y;
							rect.Height = m_dstartpt.y - m_doldpt.y;
						}

						int hit = 0;
					//	SelectObjectsWithinRect(rect, 1, hit);

						InvalidateRect(&m_areaRect);	// TODO ??
					}
					else if (dragging == 3)	// Dragged guide(s)
					{
						// TODO, remove this
						m_bInvalid = true;
						InvalidateRect(NULL);
					}
					else if (dragging == 1)	// Moved/Sized object
					{
						if (m_hit != 1)	// Sized horizontally
						{
							// If text content has fixed column with, snap the sized rectangle
							CComQIPtr<IPDObjectFrame> frame = m_pActiveObject->m_object;
							if (frame)
							{
								CComPtr<IPDObject> content;
								frame->get_content(&content);

								CComQIPtr<IPDContentText> contentText = content;
								if (contentText)
								{
									CComQIPtr<IPDTextFrameOptions> tframeopts = content;

									VARIANT_BOOL columnFixedWidth;
									tframeopts->get_columnsFixedWidth(&columnFixedWidth);

									if (columnFixedWidth)
									{
										long ncolumns;
										tframeopts->get_columnsNumber(&ncolumns);

										double columnWidth;
										tframeopts->get_columnsWidth(&columnWidth);

										double columnGutter;
										tframeopts->get_columnsGutter(&columnGutter);

										CComQIPtr<IPDObjectLocatable> locatable = frame;
										RectD bounds;
										locatable->get_bounds(&bounds);

										long newncolumns = 0;
										double x = 0;
										while (x < bounds.Width)
										{
											x += columnWidth;
											x += columnGutter;

											newncolumns++;
										}
										//long newncolumns = bounds.Width 
										//double frameWidth = (m_columnsNumber * columnWidth) + (m_columnsNumber-1)*columnGutter;
										//double sx = frameWidth/bounds.Width;

										//if (ncolumns != newncolumns)
										{
											tframeopts->setColumns(newncolumns, columnGutter, columnWidth, columnFixedWidth);

										}
										/*
										if (sx != 1.0)
										{
											locatable->Scale(bounds.X, bounds.Y, sx, 1.0);
										}
  */
									}
								}
							}
						}

						if (g_bFastFeedback)
						{
							if (m_hit == 1)
							{
								for (int i = 0; i < m_targetObjects.GetSize(); i++)
								{
									CComQIPtr<INotifySend> cp = m_targetObjects[i]->m_object;
									if (cp) cp->UnlockSend();
								}
							}
							else
							{
								CComQIPtr<INotifySend> cp = m_pActiveObject->m_object;
								if (cp) cp->UnlockSend();
							}
						}

						CComObject<CUndoMoveObjects>* pUndo;
						CComObject<CUndoMoveObjects>::CreateInstance(&pUndo);
						if (pUndo)
						{
							pUndo->AddRef();
							pUndo->m_document = m_document;
							m_activeSpread->get_uniqId(&pUndo->m_spreadGUID);

							pUndo->m_dx = wpt.x - wstartpt.x;
							pUndo->m_dy = wpt.y - wstartpt.y;

							for (int i = 0; i < m_targetObjects.GetSize(); i++)
							{
								CPDObjectSelected* pObject = m_targetObjects[i];
								GUID guid;
								pObject->m_object->get_uniqId(&guid);
								pUndo->m_objectGuids.Add(guid);
							}

							CComPtr<IOleUndoManager> undoManager;
							m_document->get_undoManager(&undoManager);

							undoManager->Add(pUndo);
						}

						InvalidateRect(&m_areaRect);	// TODO ??
					}
					else
						ATLASSERT(0);
				}
				break;

			case ID_TOOL_DIRECT:
			case ID_TOOL_PATHPEN:
			case ID_TOOL_PATHADDANCHOR:
			case ID_TOOL_PATHDELETEANCHOR:
			case ID_TOOL_PATHCORNER:
				{
					if (m_hit != 0)
					{
						if (m_curveCtl == 0)	// Clicked on anchor point
						{
							for (int i = 0; i < m_targetObjects.GetSize(); i++)
							{
								CPDObjectSelected* pObject = m_targetObjects[i];

								PDObjectType objectType;
								pObject->m_object->get_objectType(&objectType);

								if (pObject->m_wrapPath)
								{
									if (pObject->m_wrapPath->m_selectedPoints.GetSize() > 0)
									{
										CComQIPtr<IPDObjectWrappable> objectWrappable = pObject->m_object;
										objectWrappable->put_editedWrapPath(TRUE);
									}

									CComQIPtr<INotifySend> cp = pObject->m_wrapPath->GetPDPath();
									cp->UnlockSend();
								}

								if (objectType == OBJECT_FRAME)
								{
									CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;
									CComQIPtr<INotifySend> cp = pFrame->m_path->GetPDPath();
									cp->UnlockSend();
								}
							}
						}
						else
						{
							CComQIPtr<IPDObjectWrappable> objectWrappable = m_pActivePath->m_object;

							if (objectWrappable)
							{
								CComPtr<IPDPath> wrapPath;
								objectWrappable->get_wrapPath(&wrapPath);
								if (IsUnknownEqualUnknown(wrapPath, m_pActivePath->GetPDPath()))
								{
									objectWrappable->put_editedWrapPath(TRUE);
								}
							}

							CComQIPtr<INotifySend> cp = m_pActivePath->GetPDPath();
							cp->UnlockSend();
						}
					}

				//	InvalidateRect(&m_areaRect);
				}
				break;

			case ID_TOOL_GRADIENT:
				{
					HDC hDC = GetDC();
					IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);
					POINT org;
					org.x = m_areaRect.left -scrollposX;
					org.y = m_areaRect.left -scrollposY;
					POINT oldOrg;
					SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);

					int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

				// Erase old line
					MoveToEx(hDC, m_startpt.x, m_startpt.y, NULL);
					LineTo(hDC, m_oldpt.x, m_oldpt.y);

					SetROP2(hDC, oldR2);

					SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
					ReleaseDC(hDC);

					///
					ATLASSERT(0);
					/*
					for (int i = 0; i < m_targetObjects.GetSize(); i++)
					{
						CPDObjectSelected* pObject = m_targetObjects[i];

						CComQIPtr<IPDObjectFrame> frame = pObject->m_object;
						if (frame)
						{
							CComPtr<IPDBrush> brush;
							if (gApp->m_strokeOrFill == 0)
							{
								frame->get_strokeBrush(&brush);
							}
							else
							{
								frame->get_fillBrush(&brush);
							}

							brush->put_x1(wstartpt.x);
							brush->put_y1(wstartpt.y);
							brush->put_x2(wpt.x);
							brush->put_y2(wpt.y);
						}
					}
					*/
				}
				break;

			case ID_TOOL_SCALE:
			case ID_TOOL_ROTATE:
				{
					InvalidateRect(&m_areaRect);
				}
				break;

			case ID_TOOL_ZOOM:
				{
#if 0
					HDC hDC = GetDC(hwnd);
					IntersectClipRect(hDC, m_imageRect.left, m_imageRect.top, m_imageRect.right, m_imageRect.bottom);
					POINT org;
					org.x = m_imageRect.left + m_offset.x-scrollposX;
					org.y = m_imageRect.left + m_offset.y-scrollposY;
					POINT oldOrg;
					SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);

					int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
					HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
#endif

					double aspect = (double)m_areaRect.Height()/m_areaRect.Width();

#if 0
				// Erase old zoomrect
					Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

					SelectObject(hDC, hOldBrush);
					SetROP2(hDC, oldR2);

					SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
					ReleaseDC(hwnd, hDC);
#endif

					m_zoomRect.NormalizeRect();

					if (m_zoomRect.Width() <= 2 || m_zoomRect.Height() <= 2)
					{
						double x = m_startpt.x/m_magnify;
						double y = m_startpt.y/m_magnify;

					//	double docwidth = m_imageRect.Width();///m_magnify;
					//	double docheight = m_imageRect.Height();///m_magnify;

						if (!m_bAlt)	// Zoom in
						{
							ZoomToRect2(
								x-m_areaRect.Width()/m_magnify/4.0,
								y-m_areaRect.Height()/m_magnify/4.0,
								x+m_areaRect.Width()/m_magnify/4.0,
								y+m_areaRect.Height()/m_magnify/4.0);
						}
						else	// Zoom out
						{
							ZoomToRect2(
								x-m_areaRect.Width()/m_magnify,
								y-m_areaRect.Height()/m_magnify,
								x+m_areaRect.Width()/m_magnify,
								y+m_areaRect.Height()/m_magnify);
						}
					}
					else
					{
					//	ZoomToRect(m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);
						ZoomToRect2(
							m_zoomRect.left/m_magnify,
							m_zoomRect.top/m_magnify,
							m_zoomRect.right/m_magnify,
							m_zoomRect.bottom/m_magnify
							);
					}
				}
				break;

			case -10:	// Text create new thread box
			case -11:	// Text create new thread box
				{
					ATLASSERT(m_pActiveObject);

					CComQIPtr<IPDObjectFrame> frame = m_pActiveObject->m_object;
					ATLASSERT(frame != NULL);

					CComPtr<IPDObject> content;
					frame->get_content(&content);

					CComQIPtr<IPDContentText> contentText = content;
					ATLASSERT(contentText != NULL);

					CComPtr<IPDStory> story;
					contentText->get_story(&story);

					CComQIPtr<IPDObjectFrame> newobject;
					m_document->createObjectFrame(&newobject);

					// Set frame path to rectangle
					{
						CComPtr<IPDPath> path;
						newobject->get_path(&path);

						CComPtr<IPDSubPath> subpath;
						path->createSubPath(&subpath);
						subpath->setRectangle(m_newObjectBounds.X, m_newObjectBounds.Y, m_newObjectBounds.X+m_newObjectBounds.Width, m_newObjectBounds.Y+m_newObjectBounds.Height);
						path->insertSubPath(-1, subpath);	
					}

					CComPtr<IPDContentText> newcontentText;
					m_document->createContentText(&newcontentText);
					newobject->put_content(newcontentText);

				// Copy default text frame options
					CComQIPtr<IPDTextFrameOptions> defaultOptions = m_document;
					CComQIPtr<IPDTextFrameOptions> options = newcontentText;
					options->copyFrom(defaultOptions);

					CComPtr<IPDObjectText> beforeText;

					if (m_activeTool == -10)	// in
						beforeText = contentText;
					else if (m_activeTool == -11)	// out
						contentText->get_nextTextThread(&beforeText);

					if (beforeText)
						story->insertTextThreadBefore(newcontentText, beforeText);
					else
						story->appendTextThread(newcontentText);

					// Copy default properties
					//m_objectSelection->CopyDefaultProperties(newobject);
					{
						CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill2 = m_document;
						CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill = newobject;
						strokeFill->copyAppearanceFrom(VARIANT_TRUE, strokeFill2);
					}

					// Append frame
					activeLayerGroup->appendObject(newobject);

					SelectPDObject(newobject, 0, TRUE);

					Invalidate();

					gApp->m_activeTool = ID_TOOL_DIRECT;	// TODO set old tool
				}
				break;

			case ID_TOOL_TEXT:
				{
					if (m_hit == 0)	// Create new text frame
					{
						if (abs(m_startpoint.x-point.x) > 1 && abs(m_startpoint.y-point.y) > 1)
						{
							CComPtr<IPDObjectFrame> object;
							m_document->createObjectFrame(&object);

							if (object)
							{
								// Set frame path to rectangle
								{
									CComPtr<IPDPath> path;
									object->get_path(&path);
									
									CComPtr<IPDSubPath> subpath;
									path->createSubPath(&subpath);
									subpath->setRectangle(m_newObjectBounds.X, m_newObjectBounds.Y, m_newObjectBounds.X+m_newObjectBounds.Width, m_newObjectBounds.Y+m_newObjectBounds.Height);
									path->insertSubPath(-1, subpath);	
								}

							// Create new story
								CComPtr<IPDStory> story;
								m_document->createStory(&story);
								if (story)
								{
								// Create text Content
									CComPtr<IPDContentText> content;
									m_document->createContentText(&content);
									if (content)
									{
										object->put_content(content);

										// Copy default text frame options
										CComQIPtr<IPDTextFrameOptions> defaultOptions = m_document;
										CComQIPtr<IPDTextFrameOptions> options = content;
										options->copyFrom(defaultOptions);

										story->appendTextThread(content);

									// Copy default properties
										//m_objectSelection->CopyDefaultProperties(object);
										//CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill = m_document;
										//object->copyAppearanceFrom(strokeFill);
										CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill2 = m_document;
										CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill = object;
										strokeFill->copyAppearanceFrom(VARIANT_TRUE, strokeFill2);

									// Append frame
										activeLayerGroup->appendObject(object);

									// Finally append the story to the document
										m_document->appendStory(story);

										SelectPDObject(object, 0, TRUE);
									}
								}
								else
								{
									::MessageBox(GetMainHwnd(), "Couldn't create story", "PageDesigner", MB_OK);
								}
							}
						}
					}
					else	// Selected text
					{
						ATLASSERT(m_range);

					//	m_initContainer = NULL;

						CComQIPtr<IUIManager> uiManager = gIFrame;

						uiManager->ActivateObject(GetUnknown(), m_range);
					}
				}
				break;

			case ID_TOOL_RECTANGLE:
			case ID_TOOL_RECTANGLEGRAPHIC:
			case ID_TOOL_ELLIPSE:
			case ID_TOOL_ELLIPSEGRAPHIC:
			case ID_TOOL_LINE:
				{
					CComPtr<IPDObjectGroup> activeGroup;
					if (m_activeGroup)
						activeGroup = m_activeGroup;
					else
						activeGroup = activeLayerGroup;

					CComPtr<IPDObjectFrame> object;

					switch (m_activeTool)
					{
					case ID_TOOL_RECTANGLE:
					case ID_TOOL_RECTANGLEGRAPHIC:
						{
							if (abs(m_startpoint.x-point.x) < 2 || abs(m_startpoint.y-point.y) < 2)
							{
								CRectangleOptionsDlg dlg;
								dlg.m_width = 100;
								dlg.m_height = 100;

								if (dlg.DoModal(GetMainHwnd()) == IDOK)
								{
									m_document->createObjectFrame(&object);

									CComPtr<IPDPath> path;
									object->get_path(&path);

									CComPtr<IPDSubPath> subpath;
									path->createSubPath(&subpath);

									subpath->setRectangle(wstartpt.x, wstartpt.y, wstartpt.x + dlg.m_width, wstartpt.y + dlg.m_height);

									path->insertSubPath(-1, subpath);	
								}
							}
							else
							{
								m_document->createObjectFrame(&object);

								CComPtr<IPDPath> path;
								object->get_path(&path);

								CComPtr<IPDSubPath> subpath;
								path->createSubPath(&subpath);

								subpath->setRectangle(m_newObjectBounds.X, m_newObjectBounds.Y, m_newObjectBounds.X+m_newObjectBounds.Width, m_newObjectBounds.Y+m_newObjectBounds.Height);

								path->insertSubPath(-1, subpath);	
							}
						}
						break;

					case ID_TOOL_ELLIPSE:
					case ID_TOOL_ELLIPSEGRAPHIC:
						{
							if (abs(m_startpoint.x-point.x) < 2 || abs(m_startpoint.y-point.y) < 2)
							{
								CRectangleOptionsDlg dlg;
								dlg.m_width = 100;
								dlg.m_height = 100;

								if (dlg.DoModal(GetMainHwnd()) == IDOK)
								{
									m_document->createObjectFrame(&object);

									CComPtr<IPDPath> path;
									object->get_path(&path);

									CComPtr<IPDSubPath> subpath;
									path->createSubPath(&subpath);

									subpath->setEllipse(wstartpt.x, wstartpt.y, wstartpt.x + dlg.m_width, wstartpt.y + dlg.m_height);

									path->insertSubPath(-1, subpath);	
								}
							}
							else
							{
								m_document->createObjectFrame(&object);

								CComPtr<IPDPath> path;
								object->get_path(&path);

								CComPtr<IPDSubPath> subpath;
								path->createSubPath(&subpath);

								subpath->setEllipse(m_newObjectBounds.X, m_newObjectBounds.Y, m_newObjectBounds.X+m_newObjectBounds.Width, m_newObjectBounds.Y+m_newObjectBounds.Height);

								path->insertSubPath(-1, subpath);	
							}
						}
						break;

					case ID_TOOL_LINE:
						{
							if (abs(m_startpoint.x-point.x) > 1 && abs(m_startpoint.y-point.y) > 1)
							{
								m_document->createObjectFrame(&object);

								CComPtr<IPDPath> path;
								object->get_path(&path);

								CComPtr<IPDSubPath> subpath;
								path->createSubPath(&subpath);
								subpath->setLine(m_newObjectBounds.X, m_newObjectBounds.Y, m_newObjectBounds.X+m_newObjectBounds.Width, m_newObjectBounds.Y+m_newObjectBounds.Height);
								path->insertSubPath(-1, subpath);	
							}
						}
						break;
					}

					if (object)
					{
				// Copy default properties
					//	CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill = m_document;
					//	object->copyAppearanceFrom(strokeFill);
						CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill2 = m_document;
						CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill = object;
						strokeFill->copyAppearanceFrom(VARIANT_TRUE, strokeFill2);
					//	m_objectSelection->CopyDefaultProperties(object);

						CComPtr<IPDMatrix> ctm;		activeGroup->getScreenCTM(&ctm);
						CComPtr<IPDMatrix> ictm;	ctm->inverse(&ictm);

						CComQIPtr<IPDObjectTransformable> objectTransformable = object;
						ATLASSERT(objectTransformable);
						objectTransformable->put_transformMatrix(ictm);

						activeGroup->appendObject(object);

						SelectPDObject(object, 0, TRUE);
					}
				}
				break;

			case ID_TOOL_TWIRL:
			case ID_TOOL_BULGE:
				{
					if (m_hit == 2)
					{
						HDC hDC = GetDC();
						int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

						if (m_bBrushSizeVisible)
						{
							DrawBrushOutline(hDC, m_startpoint);
							m_bBrushSizeVisible = false;
						}

						SetROP2(hDC, oldR2);
						ReleaseDC(hDC);
					}
					else if (m_hit == 1)
					{
						for (int i = 0; i < m_targetObjects.GetSize(); i++)
						{
							CPDObjectSelected* pObject = m_targetObjects[i];
							if (pObject->m_wrapPath)
							{
								pObject->m_wrapPath->ConvertFlatToCurves();
							}

							PDObjectType objectType;
							pObject->m_object->get_objectType(&objectType);
							if (objectType == OBJECT_FRAME)
							{
								CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;

								pFrame->m_path->ConvertFlatToCurves();
							}
						}

						InvalidateRect(&m_areaRect);
					}
				}
				break;

			case ID_TOOL_FREETRANSFORM:
				{
					if (gApp->m_activeSelectionTool == ID_TOOL_SELECT)
					{
						for (int i = 0; i < m_targetObjects.GetSize(); i++)
						{
							CPDObjectSelected* pObject = m_targetObjects[i];

							CComQIPtr<IPDObjectTransformable> objectTransformable = pObject->m_object;
							if (objectTransformable)
							{
								CComPtr<IPDMatrix> mat0;
								pObject->m_initialMatrix->multiply(m_freeTransformMatrix, &mat0);

								objectTransformable->put_transformMatrix(mat0);
							}
						}
					}
					else if (gApp->m_activeSelectionTool == ID_TOOL_DIRECT)
					{
						for (int i = 0; i < m_targetObjects.GetSize(); i++)
						{
							CPDObjectSelected* pObject = m_targetObjects[i];
							PDObjectType objectType;
							pObject->m_object->get_objectType(&objectType);

							if (objectType == OBJECT_FRAME)
							{
								CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;
								pFrame->m_path->TransformSelectedPoint(m_freeTransformMatrix);
							}
						}
					}

					ATLASSERT(m_freeTransformMatrix != NULL);
					m_freeTransformMatrix.Release();

				//	ATLASSERT(m_oldfreeTransformMatrix != NULL);
				//	m_oldfreeTransformMatrix.Release();

					CalculateObjectsBoundingBox();

					Invalidate();
				}
				break;
			}
		}
	}

	return 0;
}

IPDMatrix* CPDDocumentView::GetRotateObjectMatrix(PointD woldpt, PointD wpt, double cx, double cy)
{
	double oldangleX;
	{
		double dx = woldpt.x - cx;
		double dy = woldpt.y - cy;

		double distance = sqrt(dx*dx + dy*dy);
		double distance2 = distance;

		if (distance2 == 0.0) distance2 = 0.00001;
		if (dy < 0) distance2 =-distance2;
		double angle = acos(dx/distance2);
		if (dy < 0) angle += M_PI;

		oldangleX = angle * 180/M_PI;
	}

	double angleX;
	{
		double dx = wpt.x - cx;
		double dy = wpt.y - cy;

		double distance = sqrt(dx*dx + dy*dy);
		double distance2 = distance;

		if (distance2 == 0.0) distance2 = 0.00001;
		if (dy < 0) distance2 =-distance2;
		double angle = acos(dx/distance2);
		if (dy < 0) angle += M_PI;

		angleX = angle * 180/M_PI;
	}

//	transform->setMatrix(transform->matrix->translate(-cx, -cy)->rotate(angleX-oldangleX)->translate(cx, cy));

//	CComQIPtr<IPDMatrix> mat0;
//	object->get_transformMatrix(&mat0);

	CComQIPtr<IPDMatrix> mat1;
	mat1.CoCreateInstance(CLSID_PDMatrix);
	mat1->setTranslate(-cx, -cy);

	CComQIPtr<IPDMatrix> mat2;
	mat1->rotate(angleX-oldangleX, &mat2);

	CComQIPtr<IPDMatrix> mat3;
	mat2->translate(cx, cy, &mat3);
	
	return mat3.Detach();
}

LRESULT CPDDocumentView::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	OnMouseMove(wParam, point);

	return 0;
}

void CPDDocumentView::OnMouseMove()
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	UINT nFlags = 0;
	if (GetAsyncKeyState(VK_SHIFT) & (1<<15)) nFlags |= MK_SHIFT;
	if (GetAsyncKeyState(VK_CONTROL) & (1<<15)) nFlags |= MK_CONTROL;

	OnMouseMove(nFlags, point);
}

// Start at common ancestor, and search for either start or end container,
// the one found first is the first

ILDOMNode* FindCommonAncestor(ILDOMNode* node1, ILDOMNode* node2);

int SearchForNode(ILDOMNode* parent, ILDOMNode* pThis, ILDOMNode* pNode)
{
	CComPtr<ILDOMNode> child;
	parent->get_firstChild(&child);
	while (child)
	{
		if (child == pThis)
			return -1;
		else if (child == pNode)
			return 1;

		int n = SearchForNode(child, pThis, pNode);
		if (n)
			return n;

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	return 0;
}

int CompareTreePosition(ILDOMNode* pThis, ILDOMNode* pNode)
{
	if (pThis == pNode)
	{
		return 0;	// Equal
	}
	else
	{
		ILDOMNode* commonAncestor = FindCommonAncestor(pThis, pNode);
		ATLASSERT(commonAncestor);

		return SearchForNode(commonAncestor, pThis, pNode);
	}
}

void CPDDocumentView::OnMouseMove(UINT nFlags, POINT point)
{
	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	m_point = point;

	POINT pt = point;
	pt.x -= m_areaRect.left;
	pt.y -= m_areaRect.top;
	pt.x += scrollposX;
	pt.y += scrollposY;

	CDblPoint dpt;
	dpt.x = pt.x;
	dpt.y = pt.y;

	m_dpt = dpt;

	if (m_dragging)
	{
		CComPtr<IPDMatrix> imatrix;
		m_matrix->inverse(&imatrix);

		PointD wpt;
		imatrix->transformPoint((PointD*)&m_dpt, &wpt);

		PointD woldpt;
		imatrix->transformPoint((PointD*)&m_doldpt, &woldpt);

		PointD wstartpt;
		imatrix->transformPoint((PointD*)&m_dstartpt, &wstartpt);

		if (m_dragging == 9)
		{
			HDC hDC = GetDC();

			POINT org;
			org.x = m_areaRect.left + /*m_offset.x*/-scrollposX;
			org.y = m_areaRect.top + /*m_offset.y*/-scrollposY;

			int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

		// Erase old
			if (m_oldpoint.y >= 16) DrawStippledLineH(hDC, (int)(m_doldpt.y+org.y), m_areaRect.left, m_areaRect.right);
			if (m_oldpoint.x >= 16) DrawStippledLineV(hDC, (int)(m_doldpt.x+org.x), m_areaRect.top, m_areaRect.bottom);

		// Draw new
			if (point.y >= 16) DrawStippledLineH(hDC, (int)(m_dpt.y+org.y), m_areaRect.left, m_areaRect.right);
			if (point.x >= 16) DrawStippledLineV(hDC, (int)(m_dpt.x+org.x), m_areaRect.top, m_areaRect.bottom);

			SetROP2(hDC, oldR2);

			ReleaseDC(hDC);
		}
		else if (m_dragging == 10 || m_dragging == 11)	// Creating guide
		{
			if (m_dragging == 10)	// Horizontal
			{
				m_newGuide->put_position(wpt.y);
			}
			else	// Vertical
			{
				m_newGuide->put_position(wpt.x);
			}

			m_newGuide->put_pageIndex(GetPageIndexUnderPoint(*(CDblPoint*)&wpt));

			Gdiplus::RectF rc;

			if (m_dragging == 10)
				rc = Gdiplus::RectF(-99999, woldpt.y, 99999*2, wpt.y-woldpt.y);
			else
				rc = Gdiplus::RectF(woldpt.x, -99999, wpt.x-woldpt.x, 99999*2);

			Normalize(rc);

			CRect wrect = GetWindowRectFromSpreadRect(rc);

			InvalidateRect(&wrect);
			UpdateWindow();
		}
		else
		{
			switch (m_activeTool)
			{
			case ID_TOOL_SELECT:
				{
					if (m_dragging == 1)
					{
						if (m_hit >= 2)	// Scale object
						{
							CPDObjectSelected* pObject = m_pActiveObject;

							CComQIPtr<IPDObject> object = pObject->m_object;
							ATLASSERT(object);

							CComQIPtr<IPDObjectTransformable> objectTransformable = object;

							RectD bounds;
							objectTransformable->get_bounds(&bounds);

							CDblPoint origin;
							origin.x = 0;
							origin.y = 0;
							double sx;
							double sy;

							if (m_hit == 2)	// top-left
							{
								origin.x = bounds.X + bounds.Width;
								origin.y = bounds.Y + bounds.Height;
							}
							else if (m_hit == 3)
							{
								origin.y = bounds.Y + bounds.Height;
							}
							else if (m_hit == 4)
							{
								origin.x = bounds.X;
								origin.y = bounds.Y + bounds.Height;
							}
							else if (m_hit == 5)
							{
								origin.x = bounds.X;
							}
							else if (m_hit == 6)
							{
								origin.x = bounds.X;
								origin.y = bounds.Y;
							}
							else if (m_hit == 7)
							{
								origin.y = bounds.Y;
							}
							else if (m_hit == 8)
							{
								origin.x = bounds.X+bounds.Width;
								origin.y = bounds.Y;
							}
							else if (m_hit == 9)
							{
								origin.x = bounds.X+bounds.Width;
							}

							CComQIPtr<IPDMatrix> ctm;
							object->getScreenCTM(&ctm);

							CComQIPtr<IPDMatrix> ictm;
							ctm->inverse(&ictm);

							PointD xpt;
							ictm->transformPoint((PointD*)&wpt, &xpt);

							PointD xoldpt;
							ictm->transformPoint((PointD*)&woldpt, &xoldpt);

							if (m_hit == 2 || m_hit == 4 || m_hit == 6 || m_hit == 8)
							{
								sx = (xpt.x - origin.x)/(xoldpt.x - origin.x);
								sy = (xpt.y - origin.y)/(xoldpt.y - origin.y);
							}
							else if (m_hit == 3 || m_hit == 7)
							{
								sx = 1;
								sy = (xpt.y - origin.y)/(xoldpt.y - origin.y);
							}
							else if (m_hit == 5 || m_hit == 9)
							{
								sx = (xpt.x - origin.x)/(xoldpt.x - origin.x);
								sy = 1;
							}

							objectTransformable->Scale(origin.x, origin.y, sx, sy);

							// Invalidate window
							{
								RectD bounds;
								objectTransformable->get_bounds(&bounds);

								RectD xbounds;
								GetTransformRectBoundingBox(ctm, &bounds, &xbounds);

								Gdiplus::RectF totalrc;

								Gdiplus::RectF rc(xbounds.X, xbounds.Y, xbounds.Width, xbounds.Height);

								Gdiplus::RectF::Union(totalrc, m_oldBounds, rc);

								CRect wrect = GetWindowRectFromSpreadRect(totalrc);
								wrect.InflateRect(4, 4, 4, 4);
								wrect.IntersectRect(&wrect, &m_areaRect);

								InvalidateRect(&wrect);

								m_oldBounds = rc;
							}
						}
						else	// Move object(s)
						{
							Gdiplus::RectF totalrc(999999, 999999, -999999, -999999);

							for (int i = 0; i < m_targetObjects.GetSize(); i++)
							{
								CPDObjectSelected* pObject = m_targetObjects[i];

								CComQIPtr<IPDObject> object = pObject->m_object;
								if (object)
								{
									CComQIPtr<IPDObjectLocatable> objectTransformable = object;

									CComQIPtr<IPDMatrix> ctm;
									object->getScreenCTM(&ctm);

									CComQIPtr<IPDMatrix> ictm;
									ctm->inverse(&ictm);

									PointD xpt;
									ictm->transformPoint((PointD*)&wpt, &xpt);

									PointD xoldpt;
									ictm->transformPoint((PointD*)&woldpt, &xoldpt);

									objectTransformable->Move(xpt.x-xoldpt.x, xpt.y-xoldpt.y);

									// For invalidation
									{
										RectD bounds;
										objectTransformable->get_bounds(&bounds);

										RectD xbounds;
										GetTransformRectBoundingBox(ctm, &bounds, &xbounds);

										Gdiplus::RectF rc(xbounds.X, xbounds.Y, xbounds.Width, xbounds.Height);

										Gdiplus::RectF::Union(totalrc, totalrc, rc);
									}
								}
							}

							// For invalidation
							{
								Gdiplus::RectF totalrc2;

								Gdiplus::RectF::Union(totalrc2, m_oldBounds, totalrc);

								CRect wrect = GetWindowRectFromSpreadRect(totalrc2);
								wrect.InflateRect(4, 4, 4, 4);
								wrect.IntersectRect(&wrect, &m_areaRect);

								InvalidateRect(&wrect);

								m_oldBounds = totalrc;
							}
						}
					}
					else if (m_dragging == 2)	// Select rectangle
					{
						HDC hDC = GetDC();
						POINT org;
						org.x = m_areaRect.left -scrollposX;
						org.y = m_areaRect.top -scrollposY;
						POINT oldOrg;
						SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);

						CRect oldrect(m_dstartpt.x, m_dstartpt.y, m_doldpt.x, m_doldpt.y);
						CRect rect(m_dstartpt.x, m_dstartpt.y, m_dpt.x, m_dpt.y);

						oldrect.NormalizeRect();
						rect.NormalizeRect();

						DrawFocusRect(hDC, &oldrect);
						DrawFocusRect(hDC, &rect);

						ReleaseDC(hDC);
					}
					else if (m_dragging == 3)
					{
						for (int i = 0; i < m_targetObjects.GetSize(); i++)
						{
							CComQIPtr<IPDGuide> guide = m_targetObjects[i]->m_object;
							if (guide)
							{
								long direction;
								guide->get_direction(&direction);

								double position;
								guide->get_position(&position);

								Gdiplus::RectF rc;

								if (direction == 0)
								{
									double delta = wpt.y-woldpt.y;
									rc = Gdiplus::RectF(-99999, position, 99999*2, delta);

									guide->offsetPosition(delta);
								}
								else
								{
									double delta = wpt.x-woldpt.x;
									rc = Gdiplus::RectF(position, -99999, delta, 99999*2);

									guide->offsetPosition(delta);
								}

								Normalize(rc);

								CRect wrect = GetWindowRectFromSpreadRect(rc);

								InvalidateRect(&wrect);
								UpdateWindow();
							}
						}
					}
				}
				break;

			case ID_TOOL_DIRECT:
			case ID_TOOL_PATHPEN:
			case ID_TOOL_PATHCORNER:
				{
					if (m_hit == 0)	// Selection Rectangle
					{
					//	DrawFocusRect(hDC, m_startpt.x, m_startpt.y, m_oldpt.x, m_oldpt.y);
					//	DrawFocusRect(hDC, m_startpt.x, m_startpt.y, pt.x, pt.y);
					}
					else
					{
						ATLASSERT(m_curveCp >= 0);

						PointD oldpt2 = woldpt;
						PointD newpt2 = wpt;

						Gdiplus::RectF totalrc(999999, 999999, -999999, -999999);

						if (m_curveCtl == 0)	// Clicked on anchor point
						{
							for (int i = 0; i < m_targetObjects.GetSize(); i++)
							{
								CPDObjectSelected* pObject = m_targetObjects[i];

								Gdiplus::RectF invalidRc(999999, 999999, -999999, -999999);

								CComQIPtr<IPDObject> object = pObject->m_object;
								if (object)
								{
									PDObjectType objectType;
									object->get_objectType(&objectType);

									CComQIPtr<IPDMatrix> matrix;
									object->getScreenCTM(&matrix);

									CComQIPtr<IPDMatrix> inversematrix;
									matrix->inverse(&inversematrix);

									PointD xnewpt2;
									inversematrix->transformPoint(&newpt2, &xnewpt2);

									PointD xoldpt2;
									inversematrix->transformPoint(&oldpt2, &xoldpt2);

									double xnewpt2x = xnewpt2.x;
									double xnewpt2y = xnewpt2.y;
										
									double xoldpt2x = xoldpt2.x;
									double xoldpt2y = xoldpt2.y;

									if (objectType == OBJECT_FRAME)
									{
										CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;
										pFrame->m_path->MovePoints(xnewpt2x-xoldpt2x, xnewpt2y-xoldpt2y, invalidRc, false);
									}

									if (pObject->m_wrapPath)
									{
										Gdiplus::RectF invalidRc2;
										pObject->m_wrapPath->MovePoints(xnewpt2x-xoldpt2x, xnewpt2y-xoldpt2y, invalidRc2, false);

										Gdiplus::RectF::Union(invalidRc, invalidRc, invalidRc2);
									}

									Gdiplus::RectF::Union(totalrc, totalrc, invalidRc);
								}
							}
						}
						else	// Control point
						{
						//	CPDObjectFrameSelected* pathElement = (CPDObjectFrameSelected*)m_pActiveObject;

							CComQIPtr<IPDObject> object = m_pActiveObject->m_object;

							CComQIPtr<IPDMatrix> matrix;
							object->getScreenCTM(&matrix);

							CComQIPtr<IPDMatrix> inversematrix;
							matrix->inverse(&inversematrix);

							PointD xnewpt2;
							inversematrix->transformPoint(&newpt2, &xnewpt2);

							PointD xoldpt2;
							inversematrix->transformPoint(&oldpt2, &xoldpt2);

							double xnewpt2x = xnewpt2.x;
							double xnewpt2y = xnewpt2.y;

							Gdiplus::RectF invalidRc;

							if (m_hit == 1)	// Same length
							{
								m_pActivePath->SetControlPointsSameLength(m_curveCp, m_curveCtl, xnewpt2x, xnewpt2y, invalidRc);
							}
							else if (m_hit == 2)
							{
								m_pActivePath->SetPathSegControlPoints(m_curveCp, m_curveCtl, xnewpt2x, xnewpt2y, invalidRc);
							}
							else
								ATLASSERT(0);

							Gdiplus::RectF::Union(totalrc, totalrc, invalidRc);
						}

						// For invalidation
						{
							Gdiplus::RectF totalrc2;

							Gdiplus::RectF::Union(totalrc2, m_oldBounds, totalrc);

							CRect wrect = GetWindowRectFromSpreadRect(totalrc2);
							wrect.InflateRect(4, 4, 4, 4);
							wrect.IntersectRect(&wrect, &m_areaRect);

							InvalidateRect(&wrect);

							m_oldBounds = totalrc;
						}
					}
				}
				break;


#if 0		
			case TOOL_PENFREE:
				{
					m_pointArray.Add(CDblPoint(pt.x, pt.y));
					
					int size = m_pointArray.GetSize();
					
				//	MoveToEx(hDC, m_pointArray[size-2].x, m_pointArray[size-2].y, NULL);
				//	LineTo(hDC, m_pointArray[size-1].x, m_pointArray[size-1].y);
				}
				break;
#endif

			case ID_TOOL_GRADIENT:
				{
					HDC hDC = GetDC();
					IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);
					POINT org;
					org.x = m_areaRect.left + /*m_offset.x*/-scrollposX;
					org.y = m_areaRect.top + /*m_offset.y*/-scrollposY;
					POINT oldOrg;
					SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);

					int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

				// Erase old line
					MoveToEx(hDC, m_startpt.x, m_startpt.y, NULL);
					LineTo(hDC, m_oldpt.x, m_oldpt.y);

				// Draw new line
					MoveToEx(hDC, m_startpt.x, m_startpt.y, NULL);
					LineTo(hDC, pt.x, pt.y);

					SetROP2(hDC, oldR2);

					SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
					ReleaseDC(hDC);
				}
				break;

			case ID_TOOL_ZOOM:
				{
					HDC hDC = GetDC();
					IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom);
					POINT org;
					org.x = m_areaRect.left + /*m_offset.x*/-scrollposX;
					org.y = m_areaRect.top + /*m_offset.y*/-scrollposY;
					POINT oldOrg;
					SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);

					int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
					HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

				// Erase old zoomrect
					Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

					double aspect = (double)m_areaRect.Height()/m_areaRect.Width();

					m_zoomRect.left = m_startpt.x;
					m_zoomRect.top = m_startpt.y;
					if ((double)abs(pt.x-m_startpt.x)/m_areaRect.Width() > (double)abs(pt.y-m_startpt.y)/m_areaRect.Height())
					{
						double aspect = (double)m_areaRect.Height()/m_areaRect.Width();
						m_zoomRect.right = pt.x;
						m_zoomRect.bottom = m_startpt.y + (pt.x-m_startpt.x)*aspect;
					}
					else
					{
						double aspect = (double)m_areaRect.Width()/m_areaRect.Height();
						m_zoomRect.right = m_startpt.x + (pt.y-m_startpt.y)*aspect;
						m_zoomRect.bottom = pt.y;
					}

				// Draw new zoomrect
					Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

					SelectObject(hDC, hOldBrush);
					SetROP2(hDC, oldR2);

					SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
					ReleaseDC(hDC);
				}
				break;

			case ID_TOOL_HAND:
				{
					if ((point.x != m_oldpoint.x) || (point.y != m_oldpoint.y))
					{
						m_scrollpos += (m_oldpoint - point);
						setScrollPosXY(m_scrollpos.x, m_scrollpos.y);
					}
				}
				break;

			case ID_TOOL_TEXT:
				if (m_hit == 1)	// Selecting text
				{
					HDC hDC = GetDC();
					
					DrawTextSelection(hDC);	// Erase selection

					if (TRUE)
					{
						CHitData hitdata;
						CComPtr<IPDObject> object;
						GetObjectUnderPoint(dpt, 4, &hitdata, &object);

						CComQIPtr<IPDObjectText> textObject = object;
						if (textObject)
						{
							CComPtr<ILDOMNode> node = hitdata.pNode;
							long offset = hitdata.offset;

							ATLASSERT(node != NULL);

							m_range->MoveDOM(node, offset);
								/*
							CComPtr<IRange> range;
							m_range->GetDOMRange(&range);

							CComPtr<IDOMNode> startContainer;
							long startOffset;

							CComPtr<IDOMNode> endContainer;
							long endOffset;

							if (node == m_initContainer)	// start and end share container
							{
								startContainer = node;
								endContainer = node;

								if (offset < m_initOffset)
								{
									startOffset = offset;
									endOffset = m_initOffset;
								}
								else
								{
									startOffset = m_initOffset;
									endOffset = offset;
								}
							}
							else
							{
								int cmp = CompareTreePosition(node, m_initContainer);
								ATLASSERT(cmp != 0);

								if (cmp == -1)
								{
									startContainer = node;
									startOffset = offset;

									endContainer = m_initContainer;
									endOffset = m_initOffset;
								}
								else
								{
									startContainer = m_initContainer;
									startOffset = m_initOffset;

									endContainer = node;
									endOffset = offset;
								}
							}

							m_curContainer = node;
							m_curOffset = offset;

							range->setStart(startContainer, startOffset);
							range->setEnd(endContainer, endOffset);
							*/
						}
					}
#if 0
					else
					{
						CComQIPtr<IPDObjectText> object = m_pActiveObject->m_object;
						
						//	CComQIPtr<IPDObjectTransformable> objectTransformable;
						//	object->get_parent((IPDObject**)&objectTransformable);
						
						CComPtr<IPDMatrix> ctm0;
						object->getScreenCTM(&ctm0);
						
						CComPtr<IPDMatrix> ctm;
						ctm0->multiply(m_matrix, &ctm);
						
						CComPtr<IPDMatrix> ictm;
						ctm->inverse(&ictm);
						
						PointD xpt;
						ictm->transformPoint((PointD*)&dpt, &xpt);
						
						//CComQIPtr<IPDContentText> text = object;

						//GetObjectUnderPoint(pt, 4, &hit);

						CComPtr<IDOMNode> node;
						long offset;
						BOOL bHit;
						object->getPosUnderPoint(xpt.x, xpt.y, &node, &offset, &bHit);
						if (bHit)
						{
							CComPtr<IRange> range;
							m_range->GetDOMRange(&range);

							CComPtr<IDOMNode> startContainer;
							long startOffset;

							CComPtr<IDOMNode> endContainer;
							long endOffset;

							if (node == m_initContainer)	// start and end share container
							{
								startContainer = node;
								endContainer = node;

								if (offset < m_initOffset)
								{
									startOffset = offset;
									endOffset = m_initOffset;
								}
								else
								{
									startOffset = m_initOffset;
									endOffset = offset;
								}
							}
							else
							{
								int cmp = CompareTreePosition(node, m_initContainer);
								ATLASSERT(cmp != 0);

								if (cmp == -1)
								{
									startContainer = node;
									startOffset = offset;

									endContainer = m_initContainer;
									endOffset = m_initOffset;
								}
								else
								{
									startContainer = m_initContainer;
									startOffset = m_initOffset;

									endContainer = node;
									endOffset = offset;
								}
							}

							m_curContainer = node;
							m_curOffset = offset;

							range->setStart(startContainer, startOffset);
							range->setEnd(endContainer, endOffset);
							//range->setEnd(node, offset);
						}
					}
					#endif
					
					DrawTextSelection(hDC);	// Draw selection
					
					ReleaseDC(hDC);
					break;
				}
			case -10:
			case ID_TOOL_RECTANGLE:
			case ID_TOOL_RECTANGLEGRAPHIC:
			case ID_TOOL_ELLIPSE:
			case ID_TOOL_ELLIPSEGRAPHIC:
			case ID_TOOL_LINE:
				{
					m_newObjectBounds.X = wstartpt.x;
					m_newObjectBounds.Y = wstartpt.y;
					m_newObjectBounds.Width = wpt.x-wstartpt.x;
					m_newObjectBounds.Height = wpt.y-wstartpt.y;

					if (nFlags & MK_SHIFT)
					{
						if (m_activeTool == ID_TOOL_LINE)
						{
							double dx = wpt.x-wstartpt.x;
							double dy = wpt.y-wstartpt.y;

							double length = sqrt(dx*dx+dy*dy);

							double angle = GetLineAngle(wstartpt.x, wstartpt.y, wpt.x, wpt.y);

							double newangle = (int)(angle/(M_PI/4)+0.5)*(M_PI/4);

							double newx = wstartpt.x + cos(newangle)*length;
							double newy = wstartpt.y + sin(newangle)*length;

							m_newObjectBounds.X = wstartpt.x;
							m_newObjectBounds.Y = wstartpt.y;
							m_newObjectBounds.Width = newx-wstartpt.x;
							m_newObjectBounds.Height = newy-wstartpt.y;
						}
						else
						{
							if (m_newObjectBounds.Width > m_newObjectBounds.Height)
							{
								m_newObjectBounds.Width = m_newObjectBounds.Height;
							}
							else if (m_newObjectBounds.Height > m_newObjectBounds.Width)
							{
								m_newObjectBounds.Height = m_newObjectBounds.Width;
							}
						}
					}

					if (m_bAlt)
					{
						m_newObjectBounds.X -= m_newObjectBounds.Width;
						m_newObjectBounds.Y -= m_newObjectBounds.Height;
						m_newObjectBounds.Width *= 2;
						m_newObjectBounds.Height *= 2;
					}

					Gdiplus::RectF rc(m_newObjectBounds.X, m_newObjectBounds.Y, m_newObjectBounds.Width, m_newObjectBounds.Height);
					Normalize(rc);

					Gdiplus::RectF totalrc;
					Gdiplus::RectF::Union(totalrc, m_oldBounds, rc);

					CRect wrect = GetWindowRectFromSpreadRect(totalrc);
					wrect.InflateRect(2, 2);
					wrect.IntersectRect(&wrect, &m_areaRect);

					InvalidateRect(&wrect);

					m_oldBounds = rc;
				}
				break;

			case ID_TOOL_FREETRANSFORM:
				{
					ATLASSERT(m_freeTransformMatrix != NULL);
				//	ATLASSERT(m_oldfreeTransformMatrix != NULL);

				//	m_oldfreeTransformMatrix->copyFrom(m_freeTransformMatrix);

					CComPtr<IPDMatrix> xMat;

					if (m_hit == 0)	// Rotate
					{
						xMat = GetRotateObjectMatrix(wstartpt, wpt, m_pivotPt.x, m_pivotPt.y);
					}
					else if (m_hit == 1)	// Move
					{
						xMat.CoCreateInstance(CLSID_PDMatrix);
						xMat->setTranslate(wpt.x-wstartpt.x, wpt.y-wstartpt.y);
					}
					else if (m_hit >= 2)	// Scale
					{
						double cx = 0;
						double cy = 0;
						double sx;
						double sy;

						RectD bounds = m_objectsBoundingBox;

						if (m_bAlt)
						{
							cy = bounds.Y + bounds.Height/2;
							cx = bounds.X + bounds.Width/2;
						}
						else
						{
							if (m_hit == 2)	// top-left
							{
								cx = bounds.X + bounds.Width;
								cy = bounds.Y + bounds.Height;
							}
							else if (m_hit == 3)
							{
								cx = bounds.X + bounds.Width/2;
								cy = bounds.Y + bounds.Height;
							}
							else if (m_hit == 4)
							{
								cx = bounds.X;
								cy = bounds.Y + bounds.Height;
							}
							else if (m_hit == 5)
							{
								cx = bounds.X;
								cy = bounds.Y + bounds.Height/2;
							}
							else if (m_hit == 6)
							{
								cx = bounds.X;
								cy = bounds.Y;
							}
							else if (m_hit == 7)
							{
								cx = bounds.X + bounds.Width/2;
								cy = bounds.Y;
							}
							else if (m_hit == 8)
							{
								cx = bounds.X+bounds.Width;
								cy = bounds.Y;
							}
							else if (m_hit == 9)
							{
								cx = bounds.X+bounds.Width;
								cy = bounds.Y + bounds.Height/2;
							}
						}

						CComPtr<IPDMatrix> mat0;

						if (nFlags & MK_CONTROL &&
							(m_hit == 3 || m_hit == 7 || m_hit == 5 || m_hit == 9))
						{
							if (m_hit == 3 || m_hit == 7)	// Skew Y
							{
								double angle = 90 - GetLineAngle(wpt.x, wstartpt.y, cx, cy) * (180/M_PI);

								CComPtr<IPDMatrix> mat1;
								mat1.CoCreateInstance(CLSID_PDMatrix);
								mat1->setTranslate(0, -cy);

								CComQIPtr<IPDMatrix> mat2;
								mat1->skewY(angle, &mat2);

								mat2->translate(0, cy, &mat0);
							}
							else	// SkewX
							{
								double angle = GetLineAngle(wstartpt.x, wpt.y, cx, cy) * (180/M_PI);

								CComPtr<IPDMatrix> mat1;
								mat1.CoCreateInstance(CLSID_PDMatrix);
								mat1->setTranslate(-cx, 0);

								CComQIPtr<IPDMatrix> mat2;
								mat1->skewX(angle, &mat2);

								mat2->translate(cx, 0, &mat0);
							}
						}
						else
						{
							mat0.CoCreateInstance(CLSID_PDMatrix);
						}

						// Snap to guides
						{
							CComPtr<IObjectMap> layergroups;
							m_activeSpread->get_layergroups(&layergroups);

							long nlayergroups;
							layergroups->get_length(&nlayergroups);

							for (long nlayergroup = 0; nlayergroup < nlayergroups; nlayergroup++)
							{
								CComPtr<IPDObjectLayerGroup> layergroup;
								layergroups->item(nlayergroup, (IUnknown**)&layergroup);

								CComPtr<IPDGuides> guides;
								layergroup->get_guides(&guides);

								long nguides;
								guides->get_length(&nguides);

								for (long i = 0; i < nguides; i++)
								{
									CComPtr<IPDGuide> guide;
									guides->item(i, &guide);

									long direction;
									guide->get_direction(&direction);

									double position;
									guide->get_position(&position);

									if (direction == 0)
									{
										if (fabs((wpt.y/*+m_offsetPt.y*/)-position) < 8)
										{
											wpt.y = position;//+m_offsetPt.y;
										}
									}
									else
									{
										if (fabs((wpt.x/*+m_offsetPt.x*/)-position) < 8)
										{
											wpt.x = position;//+m_offsetPt.x;
										}
									}
								}
							}
						}

						if (m_hit == 2 || m_hit == 4 || m_hit == 6 || m_hit == 8)
						{
							sx = (wpt.x - cx)/(wstartpt.x-m_offsetPt.x - cx);
							sy = (wpt.y - cy)/(wstartpt.y-m_offsetPt.y - cy);
						}
						else if (m_hit == 3 || m_hit == 7)
						{
							sx = 1;
							sy = (wpt.y - cy)/(wstartpt.y-m_offsetPt.y - cy);
						}
						else if (m_hit == 5 || m_hit == 9)
						{
							sx = (wpt.x - cx)/(wstartpt.x-m_offsetPt.x - cx);
							sy = 1;
						}

						CComPtr<IPDMatrix> mat1;
						mat0->translate(-cx, -cy, &mat1);

						CComQIPtr<IPDMatrix> mat2;
						mat1->scaleNonUniform(sx, sy, &mat2);

						mat2->translate(cx, cy, &xMat);
					}

					ATLASSERT(xMat != NULL);
					ATLASSERT(m_freeTransformMatrix != NULL);

					m_freeTransformMatrix = xMat;

					if (gApp->m_activeSelectionTool == ID_TOOL_SELECT)
					{
						/*
						for (int i = 0; i < m_targetObjects.GetSize(); i++)
						{
							CPDObjectSelected* pObject = m_targetObjects[i];

							CComQIPtr<IPDObjectTransformable> objectTransformable = pObject->m_object;

							CComPtr<IPDMatrix> mat0;
							pObject->m_initialMatrix->multiply(xMat, &mat0);

							objectTransformable->put_transformMatrix(mat0);
						}
						*/
					}
					else if (gApp->m_activeSelectionTool == ID_TOOL_DIRECT)
					{
						for (int i = 0; i < m_targetObjects.GetSize(); i++)
						{
							CPDObjectSelected* pObject = m_targetObjects[i];
							PDObjectType objectType;
							pObject->m_object->get_objectType(&objectType);

							/*
							if (objectType == OBJECT_FRAME)
							{
								CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;

								CComPtr<IPDMatrix> pdmatrix;

								CComPtr<IPDMatrix> ifree;
								m_freeTransformMatrix->inverse(&ifree);

								CComPtr<IPDMatrix> ioldfree;
								m_oldfreeTransformMatrix->inverse(&ioldfree);

								m_freeTransformMatrix->multiply(ioldfree, &pdmatrix);

								pFrame->m_path->TransformSelectedPoint(pdmatrix);
							}
							*/
						}
					}
					else
						ATLASSERT(0);

					InvalidateRect(&m_areaRect);	// TODO ?? remove
				}
				break;

			case ID_TOOL_TWIRL:
			case ID_TOOL_BULGE:
				{
					if (m_hit == 2)	// Size brush
					{
						HDC hDC = GetDC();
						int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

						if (m_bBrushSizeVisible)
						{
							DrawBrushOutline(hDC, m_startpoint);
							m_bBrushSizeVisible = false;
						}

						CComQIPtr<IPDBrushSettings> brushSettings = gIApp;

						double brushAngle;
						brushSettings->get_brushAngle(&brushAngle);

						CComPtr<IPDMatrix> imat;
						imat.CoCreateInstance(CLSID_PDMatrix);
						imat->setRotate(-brushAngle);

					//	double brushWidth;
					//	double brushHeight;
					//	brushSettings->get_brushWidth(&brushWidth);
					//	brushSettings->get_brushHeight(&brushHeight);

						PointD xstartpt;
						imat->transformPoint((PointD*)&wstartpt, &xstartpt);

						PointD xpt;
						imat->transformPoint((PointD*)&wpt, &xpt);

						double brushWidth = m_brushSize.x + (xpt.x-xstartpt.x)*2;
						double brushHeight = m_brushSize.y + (xpt.y-xstartpt.y)*2;

						if (nFlags & MK_SHIFT)
						{
							brushWidth = max(brushWidth, brushHeight);
							brushHeight = brushWidth;
						}

						brushSettings->put_brushWidth(brushWidth);
						brushSettings->put_brushHeight(brushHeight);

						DrawBrushOutline(hDC, m_startpoint);
						m_bBrushSizeVisible = true;

						SetROP2(hDC, oldR2);
						ReleaseDC(hDC);
					}
					else
					{
						CComQIPtr<IPDBrushSettings> brushSettings = gIApp;

						CComPtr<IPDMatrix> brushmat;
						brushSettings->getBrushMatrix(&brushmat);

						CComPtr<IPDMatrix> mat0;
						brushmat->translate(wpt.x, wpt.y, &mat0);

						for (int i = 0; i < m_targetObjects.GetSize(); i++)
						{
							CPDObjectSelected* pObject = m_targetObjects[i];
							CComQIPtr<IPDObject> object = pObject->m_object;

							if (object)
							{
								PDObjectType objectType;
								pObject->m_object->get_objectType(&objectType);

								if (objectType == OBJECT_FRAME)
								{
									CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;
									CPathSelection* pPath = pFrame->m_path;

									CComPtr<IPDMatrix> ctm;		object->getScreenCTM(&ctm);
									CComPtr<IPDMatrix> ictm;	ctm->inverse(&ictm);

									CComPtr<IPDMatrix> mat;
									mat0->multiply(ictm, &mat);

									CComPtr<IPDMatrix> imat;
									mat->inverse(&imat);

									for (int nsubpath = 0; nsubpath < pPath->m_flatSubPaths.GetSize(); nsubpath++)
									{
										CFlatSubPath* subpath = pPath->m_flatSubPaths[nsubpath];

										int pointsIndex = 0;

										for (int nseg = 0; nseg < subpath->m_flatSegments.GetSize(); nseg++)
										{
											CFlatSegment& segment = subpath->m_flatSegments[nseg];

											int numpoints = segment.m_pointCount;
											DblPOINT* points = subpath->m_flatPoints.GetData() + pointsIndex;
											pointsIndex += numpoints;

											if (m_activeTool == ID_TOOL_TWIRL)
											{
												double dangle = 1;

												for (int i = 0; i < numpoints; i++)
												{
													PointD xpt;
													imat->transformPoint((PointD*)&points[i], &xpt);

													double dx = xpt.x-0;
													double dy = xpt.y-0;
													double _distance = dx*dx + dy*dy;

													if (_distance < 1.0)
													{
														double distance = sqrt(_distance);

														if (distance == 0.0) distance = 0.0001;

														double angle = acos(dx/distance);
														if (dy < 0) angle = M_PI*2 - angle;

														double addangle;
														addangle = ((1-distance)/1)*dangle;

														angle += addangle;

														PointD np;
														np.x = cos(angle)*distance;
														np.y = sin(angle)*distance;

														mat->transformPoint(&np, (PointD*)&points[i]);

														segment.m_bRecentAltered = true;
														segment.m_bAltered = true;
													}
													else
													{
													}
												}
											}
											else if (m_activeTool == ID_TOOL_BULGE)
											{
												double dstrength = 0.7;

												for (int i = 0; i < numpoints; i++)
												{
													PointD xpt;
													imat->transformPoint((PointD*)&points[i], &xpt);

													double dx = xpt.x-0;
													double dy = xpt.y-0;
													double _distance = dx*dx + dy*dy;

													if (_distance < 1.0)
													{
														double distance = sqrt(_distance);
														if (distance == 0.0) distance = 0.0001;

														double newdistance = pow(distance/1, dstrength)*1;
														ATLASSERT((newdistance >= 0) && (newdistance <= 1));

														PointD np;
														np.x = (dx * newdistance) / distance;
														np.y = (dy * newdistance) / distance;

														mat->transformPoint(&np, (PointD*)&points[i]);

														segment.m_bRecentAltered = true;
														segment.m_bAltered = true;
													}
													else
													{
													}
												}
											}
										}
									}

									pPath->MoreFlatDetail();
								}
							}
						}

						/*
						VARIANT_BOOL showBrushSize;
						brushSettings->get_showBrushSize(&showBrushSize);
						if (showBrushSize)
						{
							HDC hDC = GetDC();
							int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
							DrawBrushOutline(hDC, m_point);
							SetROP2(hDC, oldR2);
							ReleaseDC(hDC);

							m_bBrushSizeVisible = true;
						}
						*/
						m_bBrushSizeVisible = true;

						InvalidateRect(&m_areaRect);	// TODO ?? remove
					}
				}
				break;

			case ID_TOOL_SCALE:
			case ID_TOOL_ROTATE:
				{
					if (m_dragging == 2)
					{
						m_pivotPt.x = wpt.x;
						m_pivotPt.y = wpt.y;
					}
					else
					{
						if (m_activeTool == ID_TOOL_ROTATE)
						{
							CComPtr<IPDMatrix> rotateMat;
							rotateMat = GetRotateObjectMatrix(woldpt, wpt, m_pivotPt.x, m_pivotPt.y);

							for (int i = 0; i < m_targetObjects.GetSize(); i++)
							{
								CPDObjectSelected* pObject = m_targetObjects[i];

								CComQIPtr<IPDObjectTransformable> objectTransformable = pObject->m_object;

								CComPtr<IPDMatrix> mat0;
								objectTransformable->get_transformMatrix(&mat0);

								CComPtr<IPDMatrix> mat1;
								mat0->multiply(rotateMat, &mat1);

								objectTransformable->put_transformMatrix(mat1);
							}
						}
						else if (m_activeTool == ID_TOOL_SCALE)
						{
							double cx = m_pivotPt.x;
							double cy = m_pivotPt.y;

							for (int i = 0; i < m_targetObjects.GetSize(); i++)
							{
								CPDObjectSelected* pObject = m_targetObjects[i];

								CComQIPtr<IPDObjectTransformable> objectTransformable = pObject->m_object;

								float sx = (wpt.x - cx)/(woldpt.x - cx);
								float sy = (wpt.y - cy)/(woldpt.y - cy);

							//	transform->setMatrix(transform->matrix->translate(-cx, -cy)->scaleNonUniform(sx, sy)->translate(cx, cy));

								CComQIPtr<IPDMatrix> mat0;
								objectTransformable->get_transformMatrix(&mat0);

								CComQIPtr<IPDMatrix> mat1;
								mat0->translate(-cx, -cy, &mat1);

								CComQIPtr<IPDMatrix> mat2;
								mat1->scaleNonUniform(sx, sy, &mat2);

								CComQIPtr<IPDMatrix> mat3;
								mat2->translate(cx, cy, &mat3);

								objectTransformable->put_transformMatrix(mat3);
							}
						}
	#if 0
						else if (m_activeTool == TOOL_SKEW)
						{
							for (int i = 0; i < m_targetObjects.GetSize(); i++)
							{
								CPDObjectSelected* pObject = m_targetObjects[i];
								double oldangleX;
								{
									double dx = m_oldpt.x - m_pivotPt.x;
									double dy = m_startpt.y - m_pivotPt.y;

									double distance = sqrt(dx*dx + dy*dy);
									double distance2 = distance;

									if (distance2 == 0.0) distance2 = 0.00001;
									if (dy < 0) distance2 =-distance2;
									double angle = acos(dx/distance2);
									if (dy < 0) angle += M_PI;

									oldangleX = 90 - (angle * 180/M_PI);
								}

								double angleX;
								{
									double dx = pt.x - m_pivotPt.x;
									double dy = m_startpt.y - m_pivotPt.y;

									double distance = sqrt(dx*dx + dy*dy);
									double distance2 = distance;

									if (distance2 == 0.0) distance2 = 0.00001;
									if (dy < 0) distance2 =-distance2;
									double angle = acos(dx/distance2);
									if (dy < 0) angle += M_PI;

									angleX = 90 - (angle * 180/M_PI);
								}

								/*
								double oldangleY;
								{
									double dx = m_startpt.x - pActiveElement->m_pivot.x;
									double dy = m_oldpt.y - pActiveElement->m_pivot.y;

									double distance = sqrt(dx*dx + dy*dy);
									double distance2 = distance;

									if (distance2 == 0.0) distance2 = 0.00001;
									if (dy < 0) distance2 =-distance2;
									double angle = asin(dy/distance2);
									if (dy < 0) angle += M_PI;

									oldangleY = angle * 180/M_PI;
								}

								double angleY;
								{
									double dx = m_startpt.x - pActiveElement->m_pivot.x;
									double dy = pt.y - pActiveElement->m_pivot.y;

									double distance = sqrt(dx*dx + dy*dy);
									double distance2 = distance;

									if (distance2 == 0.0) distance2 = 0.00001;
									if (dy < 0) distance2 =-distance2;
									double angle = asin(dy/distance2);
									if (dy < 0) angle += M_PI;

									angleY = angle * 180/M_PI;
								}
								*/

							//	TRACE("%g\n", angleX-oldangleX);

								if (transform)
								{
									transform->setMatrix(pElement->m_initialMatrix->translate(0, -m_pivotPt.y)->skewX(angleX)->translate(0, m_pivotPt.y));
								//	transform->setMatrix(transform->matrix->translate(0, -m_pivotPt.y)->skewX((angleX-oldangleX))->translate(0, m_pivotPt.y));

									//	transform->setMatrix(transform->matrix->translate(-m_pivotPt.x, 0)->skewY(oldangleY-angleY)->translate(m_pivotPt.x, 0));
								}
							}
						//	pElement->DrawBBox(hDC, &m_drawSession);
						}
	#endif
					}

					InvalidateRect(&m_areaRect);
				}
				break;
			}
		}
	}
	else
	{
		HDC hDC = GetDC();
		int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

		if (m_bRulers)
		{
			if (m_bCurPosOnRulerVisible) DrawCurPosOnRuler(hDC, m_oldpoint);

			DrawCurPosOnRuler(hDC, m_point);
			m_bCurPosOnRulerVisible = true;
		}

		if (m_bBrushSizeVisible)
		{
			DrawBrushOutline(hDC, m_oldpoint);
			m_bBrushSizeVisible = false;
		}

		if (
			gApp->m_activeTool == ID_TOOL_TWIRL ||
			gApp->m_activeTool == ID_TOOL_BULGE)
		{
			CComQIPtr<IPDBrushSettings> brushSettings = gIApp;

			VARIANT_BOOL showBrushSize;
			brushSettings->get_showBrushSize(&showBrushSize);
			if (showBrushSize)
			{
				DrawBrushOutline(hDC, m_point);
				m_bBrushSizeVisible = true;
			}
		}

		SetROP2(hDC, oldR2);
		ReleaseDC(hDC);
	}

	m_oldpt = pt;
	m_doldpt = m_dpt;
	m_oldpoint = m_point;
}

void CPDDocumentView::DrawCurPosOnRuler(HDC hDC, CPoint point)
{
	if (point.y >= 16) DrawStippledLineH(hDC, point.y, 1, 15);
	if (point.x >= 16) DrawStippledLineV(hDC, point.x, 1, 15);
}

void SetEllipseBezier(BezierPoint* cCtlPt, double left, double top, double right, double bottom);

void CPDDocumentView::DrawBrushOutline(HDC hDC, CDblPoint point)
{
	CComQIPtr<IPDBrushSettings> brushSettings = gIApp;

	CComPtr<IPDMatrix> brushmat;
	brushSettings->getBrushMatrix(&brushmat);

	CComPtr<IPDMatrix> mat0;
	brushmat->translate(point.x, point.y, &mat0);

	CComPtr<IPDMatrix> mat;
	m_matrix->multiply(mat0, &mat);

	BezierPoint bpoints[4];
	SetEllipseBezier(bpoints, -1, -1, 1, 1);

	for (int i = 0; i < 4; i++)
	{
		mat->transformBezierPoint(&bpoints[i], &bpoints[i]);
	}

	POINT points[13];
	int j = 0;

	points[j].x = bpoints[0].x+0.5;
	points[j++].y = bpoints[0].y+0.5;

	for (i = 1; i < 4; i++)
	{
		points[j].x = bpoints[i-1].x2+0.5;
		points[j++].y = bpoints[i-1].y2+0.5;
		points[j].x = bpoints[i].x1+0.5;
		points[j++].y = bpoints[i].y1+0.5;
		points[j].x = bpoints[i].x+0.5;
		points[j++].y = bpoints[i].y+0.5;
	}

	points[j].x = bpoints[i-1].x2+0.5;
	points[j++].y = bpoints[i-1].y2+0.5;
	points[j].x = bpoints[0].x1+0.5;
	points[j++].y = bpoints[0].y1+0.5;
	points[j].x = bpoints[0].x+0.5;
	points[j++].y = bpoints[0].y+0.5;

	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

	PolyBezier(hDC, points, 13);

	SelectObject(hDC, hOldBrush);
}

void CPDDocumentView::EraseBrushOutline()
{
	if (m_bBrushSizeVisible)
	{
		HDC hDC = GetDC();
		int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

		DrawBrushOutline(hDC, m_oldpoint);
		m_bBrushSizeVisible = false;

		SetROP2(hDC, oldR2);
		ReleaseDC(hDC);
	}
}

IPDGuide* CPDDocumentView::GetGuideUnderPoint(double x, double y)
{
	if (m_activeSpread)
	{
		CComPtr<IObjectMap> layergroups;
		m_activeSpread->get_layergroups(&layergroups);

		long nlayergroups;
		layergroups->get_length(&nlayergroups);

		for (long nlayergroup = nlayergroups-1; nlayergroup >= 0; nlayergroup--)
		{
			CComPtr<IPDObjectLayerGroup> layergroup;
			layergroups->item(nlayergroup, (IUnknown**)&layergroup);

			CComPtr<IPDGuides> guides;
			layergroup->get_guides(&guides);

			CComPtr<IPDGuide> guide;
			guides->getGuideUnderPoint(x, y, 3, &guide);

			if (guide)
			{
				return guide.Detach();
			}
		}
	}

	return NULL;
}

LRESULT CPDDocumentView::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = (HWND) wParam;       // handle to window with cursor 
	UINT nHittest = LOWORD(lParam);  // hit-test code 
	UINT wMouseMsg = HIWORD(lParam); // mouse-message identifier 
	if (nHittest = HTCLIENT)
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		if (m_areaRect.PtInRect(point))
		{
			BOOL b = OnSetCursor(point);
			if (b) return TRUE;
		}
	}

	return DefWindowProc(uMsg, wParam, lParam);
}

BOOL CPDDocumentView::OnSetCursor()
{
	POINT point;
	GetCursorPos(&point);

	if (	(::GetCapture() == m_hWnd) ||
			(::WindowFromPoint(point) == m_hWnd))
	{
		ScreenToClient(&point);

		if (m_areaRect.PtInRect(point))
		{
			return OnSetCursor(point);
		}
	}

	return FALSE;
}

BOOL CPDDocumentView::OnSetCursor(POINT point)
{
	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	CComQIPtr<IPDObjectLayerGroup> activeLayerGroup;
	if (m_activeSpread)
		m_activeSpread->getLayerGroupFromLayer(m_activeLayer, &activeLayerGroup);

	POINT pt = point;
	pt.x -= m_areaRect.left;
	pt.y -= m_areaRect.top;
	pt.x += scrollposX;
	pt.y += scrollposY;

	CDblPoint dpt;
	dpt.x = pt.x;
	dpt.y = pt.y;

	CComPtr<IPDMatrix> imatrix;
	m_matrix->inverse(&imatrix);

	PointD wpt;
	imatrix->transformPoint((PointD*)&dpt, &wpt);

	HCURSOR hCursor = NULL;

	LONG bCtrl = (GetAsyncKeyState(VK_CONTROL) & (1<<15));

	long activeTool;

	if (m_dragging)
	{
		activeTool = m_activeTool;
	}
	else
	{
		if (!bCtrl)
			activeTool = gApp->m_activeTool;
		else
			activeTool = gApp->m_activeSelectionTool;
	}

	switch (activeTool)
	{
	case -12:	// Place graphic
		{
			hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_PLACEGRAPHICNEW));
		}
		break;

	case -10:	// Link Text Thread
	case -11:
		{
			CHitData hitdata;
			CComPtr<IPDObject> object;
			GetObjectUnderPoint(dpt, 2, &hitdata, &object);

			CComQIPtr<IPDObjectFrame> frame = object;

			if (frame)
			{
				hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_LINKTEXT));
			}
			else
			{
				hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_PLACETEXT));
			}
		}
		break;

	case ID_TOOL_SELECT:
		{
			UINT nResource = 0;

			CComPtr<IPDGuide> guide = GetGuideUnderPoint(wpt.x, wpt.y);
			if (guide)
			{
				nResource = IDC_SIZE_NS;
			}

			if (nResource == 0 && activeLayerGroup)
			{
				nResource = IDC_SELECT;

			//	CComQIPtr<IPDMatrix> pdmatrix;
			//	activeLayerGroup->getScreenCTM(&pdmatrix);

				//int hit = 0;
				CHitData hitdata;
				CComQIPtr<IPDObject> object;
				GetObjectUnderPoint(dpt, 1, &hitdata, &object);

				if (object)
				{
					//CComQIPtr<IPDObjectTransformable> objectTransformable = object;

					if (hitdata.hit >= 2)
					{
						CComPtr<IPDMatrix> ctm;
						object->getScreenCTM(&ctm);

						double angle;
						ctm->getRotation(&angle);

						switch (hitdata.hit)
						{
						case 2: angle -= 45; break;
						case 3: angle += 0; break;
						case 4: angle += 45; break;
						case 5: angle += 90; break;
						case 6: angle += 135; break;
						case 7: angle += 180; break;
						case 8: angle += 225; break;
						case 9: angle += 270; break;
						}

						if (angle < 0) angle += 360;
						if (angle >= 360) angle -= 360;

						UINT nCursors[8] =
						{
							IDC_SIZE_NS,
							IDC_SIZE_NESW,
							IDC_SIZE_WE,
							IDC_SIZE_NWSE,
							IDC_SIZE_NS,
							IDC_SIZE_NESW,
							IDC_SIZE_WE,
							IDC_SIZE_NWSE,
						};

						if (angle < 22.5)			nResource = nCursors[0];
						else if (angle < 45)		nResource = nCursors[1];
						else if (angle < 67.5)	nResource = nCursors[1];
						else if (angle < 90)		nResource = nCursors[2];
						else if (angle < 112.5)	nResource = nCursors[2];
						else if (angle < 135)	nResource = nCursors[3];
						else if (angle < 157.5)	nResource = nCursors[3];
						else if (angle < 180)	nResource = nCursors[4];
						else if (angle < 202.5)	nResource = nCursors[4];
						else if (angle < 225)	nResource = nCursors[5];
						else if (angle < 247.5)	nResource = nCursors[5];
						else if (angle < 270)	nResource = nCursors[6];
						else if (angle < 292.5)	nResource = nCursors[6];
						else if (angle < 315)	nResource = nCursors[7];
						else if (angle < 337.5)	nResource = nCursors[7];
						else if (angle < 360)	nResource = nCursors[0];
						else
							ATLASSERT(0);
					}
					else if (hitdata.hit == 1)
					{
						if (IsPDObjectSelected(object))
							nResource = IDC_MOVE;
						else
							nResource = IDC_SELECTOVER;
						
					}
					else
					{
						nResource = IDC_SELECT;
					}
				}
			}

			if (nResource)
			{
				hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(nResource));
			}
		}
		break;

	case ID_TOOL_TEXT:
		{
			if (activeLayerGroup)
			{
				CHitData hitdata;
				CComQIPtr<IPDObject> object;
				GetObjectUnderPoint(dpt, 4, &hitdata, &object);

				if (object)
				{
					CComPtr<IPDMatrix> ctm;
					object->getScreenCTM(&ctm);

					double angle;
					ctm->getRotation(&angle);

					UINT nCursors[8] =
					{
						IDC_TEXTTEXTNS,
						IDC_TEXTTEXTNSEW,
						IDC_TEXTTEXTEW,
						IDC_TEXTTEXTSNEW,
						IDC_TEXTTEXTSN,
						IDC_TEXTTEXTSNWE,
						IDC_TEXTTEXTWE,
						IDC_TEXTTEXTNSWE,
					};

					UINT nResource = 0;

					if (angle < 22.5)			nResource = nCursors[0];
					else if (angle < 45)		nResource = nCursors[1];
					else if (angle < 67.5)	nResource = nCursors[1];
					else if (angle < 90)		nResource = nCursors[2];
					else if (angle < 112.5)	nResource = nCursors[2];
					else if (angle < 135)	nResource = nCursors[3];
					else if (angle < 157.5)	nResource = nCursors[3];
					else if (angle < 180)	nResource = nCursors[4];
					else if (angle < 202.5)	nResource = nCursors[4];
					else if (angle < 225)	nResource = nCursors[5];
					else if (angle < 247.5)	nResource = nCursors[5];
					else if (angle < 270)	nResource = nCursors[6];
					else if (angle < 292.5)	nResource = nCursors[6];
					else if (angle < 315)	nResource = nCursors[7];
					else if (angle < 337.5)	nResource = nCursors[7];
					else if (angle < 360)	nResource = nCursors[0];
					else
						ATLASSERT(0);

					hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(nResource));
				}
				else
				{
					hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_TEXTNEW));
				}
			}
		}
		break;

	case ID_TOOL_DIRECT:
		{
			hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_DIRECT));

			if (m_bAlt)
			{
				hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_DIRECTPLUS));
			}
			else
			{
				CHitData hitdata;
				CComPtr<IPDObject> object;
				GetObjectUnderPoint(dpt, 2, &hitdata, &object);
				if (object)
				{
					if (IsPDObjectSelected(object))
						hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_MOVE));
					else
						hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_DIRECTOVER));
				}
			}
		}
		break;

	case ID_TOOL_PATHPEN:
	case ID_TOOL_PATHADDANCHOR:
	case ID_TOOL_PATHDELETEANCHOR:
		{
			UINT nResource = 0;

			if (activeTool == ID_TOOL_PATHPEN)
			{
				CHitData hitdata;
				CComPtr<IPDObject> object;
				GetObjectUnderPoint(dpt, 2, &hitdata, &object);

				long subpathcurveCp = -1;
				long nactivesubpathPoints = 0;
				VARIANT_BOOL activesubpathClosed = 0;
				CComPtr<IPDSubPath> activesubpath;
				if (m_pActivePath)
				{
					ATLASSERT(m_curveCp >= 0);
					m_pActivePath->GetPDPath()->getSubPathFromIndex(m_curveCp, &subpathcurveCp, &activesubpath);

					activesubpath->get_closed(&activesubpathClosed);
					activesubpath->get_pointCount(&nactivesubpathPoints);
				}

				if (object)
				{
					CPathSelection* pPath = GetPDPathSelected(hitdata.path);

					if (hitdata.anchor >= 0)
					{
						CComPtr<IPDSubPath> subpath;
						long subpathIndex;
						hitdata.path->getSubPathFromIndex(hitdata.anchor, &subpathIndex, &subpath);

						long nsubpathPoints;
						subpath->get_pointCount(&nsubpathPoints);

						VARIANT_BOOL closed;
						subpath->get_closed(&closed);

						if (nResource == 0)
						{
							if (m_pActivePath == pPath && activesubpath == subpath && !closed && hitdata.ctl == 0)
							{
								if ((subpathIndex == 0 && subpathcurveCp == nsubpathPoints-1) ||
									(subpathIndex == nsubpathPoints-1 && subpathcurveCp == 0))
								{
									nResource = IDC_PENCLOSE;
								}
								else if ((subpathIndex == 0 && subpathcurveCp == 0) ||
											(subpathIndex == nsubpathPoints-1 && subpathcurveCp == nsubpathPoints-1))
								{
									nResource = IDC_PENCHANGELAST;
								}
							}
						}

						if (nResource == 0)
						{
							if (m_pActivePath != NULL &&
								hitdata.ctl == 0 &&
								!closed &&
								!activesubpathClosed &&
								subpath != activesubpath &&
								(subpathcurveCp == 0 || subpathcurveCp == nactivesubpathPoints-1) &&
								(subpathIndex == 0 || subpathIndex == nsubpathPoints-1))
							{
								nResource = IDC_PENCONNECT;
							}
						}

						if (nResource == 0)
						{
							if (pPath &&
								!closed && hitdata.ctl == 0 &&
								((subpathIndex == 0) || (subpathIndex == nsubpathPoints-1)))
							{
								nResource = IDC_PENCONTINUE;
							}
						}

						if (nResource == 0)
						{
							if (/*m_pActivePath && m_pActivePath ==*/ pPath && hitdata.ctl == 0)
							{
								nResource = IDC_PENDELETE;
							}
						}
					}
					else if (hitdata.segment >= 0)
					{
						if (/*m_pActivePath && m_pActivePath ==*/ pPath)
							nResource = IDC_PENADD;
					}
				}

				if (nResource == 0)
				{
					if (m_pActivePath &&
						(subpathcurveCp == 0 || subpathcurveCp == nactivesubpathPoints-1))
					{
						nResource = IDC_PEN;
					}
				}

				if (nResource == 0)
				{
					nResource = IDC_PENNEW;
				}
			}
			else if (activeTool == ID_TOOL_PATHADDANCHOR)
			{
				nResource = IDC_PENADD;
			}
			else if (activeTool == ID_TOOL_PATHDELETEANCHOR)
			{
				nResource = IDC_PENDELETE;
			}

			if (nResource)
			{
				hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(nResource));
			}
		}
		break;

	case ID_TOOL_TEXTPATH:
		{
			if (activeLayerGroup)
			{
			//	CComQIPtr<IPDMatrix> pdmatrix;
			//	activeLayerGroup->getScreenCTM(&pdmatrix);

			//	int hit = 0;
				CHitData hitdata;
				CComPtr<IPDObject> object;
				GetObjectUnderPoint(dpt, 5, &hitdata, &object);

				if (object)
				{
					hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_TEXTPATHPLUS));
				}
				else
				{
					hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_TEXTPATH));
				}
			}
		}
		break;

	case ID_TOOL_FREETRANSFORM:
		{
			if (m_dragging)
			{
				hCursor = m_startDragCursor;

				if (bCtrl)
				{
					if (m_hit == 3 || m_hit == 7)
					{
						hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_SKEW_X));
					}
					else if (m_hit == 5 || m_hit == 9)
					{
						hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_SKEW_Y));
					}
				}
			}
			else
			{
				UINT nResource = 0;

				if (m_targetObjects.GetSize() > 0)
				{
					RectD bounds = m_objectsBoundingBox;

					if (nResource == 0)
					{
						PointD pts[8] =
						{
							bounds.X, bounds.Y,
							bounds.X+bounds.Width/2, bounds.Y,
							bounds.X+bounds.Width, bounds.Y,
							bounds.X+bounds.Width, bounds.Y+bounds.Height/2,
							bounds.X+bounds.Width, bounds.Y+bounds.Height,
							bounds.X+bounds.Width/2, bounds.Y+bounds.Height,
							bounds.X, bounds.Y+bounds.Height,
							bounds.X, bounds.Y+bounds.Height/2,
						};

						PointD xpts[8];
						for (int npt = 0; npt < 8; npt++)
						{
							m_matrix->transformPoint(&pts[npt], &xpts[npt]);
						}

						UINT nCursors[8] =
						{
							IDC_SIZE_NWSE,
							IDC_SIZE_NS,
							IDC_SIZE_NESW,
							IDC_SIZE_WE,
							IDC_SIZE_NWSE,
							IDC_SIZE_NS,
							IDC_SIZE_NESW,
							IDC_SIZE_WE,
						};

						for (int i = 0; i < 8; i++)
						{
							if ((fabs(dpt.x-xpts[i].x) <= 6) && (fabs(dpt.y-xpts[i].y) <= 6))
							{
								nResource = nCursors[i];
								break;
							}
						}
					}

					if (nResource == 0)
					{
						CComPtr<IPDMatrix> imatrix;
						m_matrix->inverse(&imatrix);

						PointD xpt;
						imatrix->transformPoint((PointD*)&dpt, &xpt);

						if (xpt.x > bounds.X && xpt.y > bounds.Y &&
							xpt.x < bounds.X+bounds.Width && xpt.y < bounds.Y+bounds.Height)
						{
							nResource = IDC_MOVE;	// Inside
						}
						else	// Outside, rotate
						{
							PointD center;
							center.x = bounds.X + bounds.Width/2;
							center.y = bounds.Y + bounds.Height/2;

							double angle = GetLineAngle(center.x, center.y, xpt.x, xpt.y)  * (180/M_PI);

							angle += 90;
							if (angle >= 360) angle -= 360;

							UINT nCursors[8] =
							{
								IDC_ROTATE_N,
								IDC_ROTATE_NE,
								IDC_ROTATE_E,
								IDC_ROTATE_SE,
								IDC_ROTATE_S,
								IDC_ROTATE_SW,
								IDC_ROTATE_W,
								IDC_ROTATE_NW,
							};

							if (angle < 22.5)			nResource = nCursors[0];
							else if (angle < 45)		nResource = nCursors[1];
							else if (angle < 67.5)	nResource = nCursors[1];
							else if (angle < 90)		nResource = nCursors[2];
							else if (angle < 112.5)	nResource = nCursors[2];
							else if (angle < 135)	nResource = nCursors[3];
							else if (angle < 157.5)	nResource = nCursors[3];
							else if (angle < 180)	nResource = nCursors[4];
							else if (angle < 202.5)	nResource = nCursors[4];
							else if (angle < 225)	nResource = nCursors[5];
							else if (angle < 247.5)	nResource = nCursors[5];
							else if (angle < 270)	nResource = nCursors[6];
							else if (angle < 292.5)	nResource = nCursors[6];
							else if (angle < 315)	nResource = nCursors[7];
							else if (angle < 337.5)	nResource = nCursors[7];
							else if (angle < 360)	nResource = nCursors[0];
							else
								ATLASSERT(0);
						}
					}
				}

				if (nResource)
				{
					hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(nResource));
				}
			}
		}
		break;

	case ID_TOOL_RECTANGLE:
	case ID_TOOL_RECTANGLEGRAPHIC:
	case ID_TOOL_ELLIPSE:
	case ID_TOOL_ELLIPSEGRAPHIC:
	case ID_TOOL_LINE:
		{
			hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_CROSSHAIR));
		}
		break;

	case ID_TOOL_ZOOM:
		{
			if (m_bAlt)
				hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_ZOOMOUT));
			else
				hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_ZOOMIN));
		}
		break;

	case ID_TOOL_HAND:
		{
			hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_HAND0));
		}
		break;
	}

	if (hCursor)
	{
		::SetCursor(hCursor);
		return TRUE;
	}

	return FALSE;
}

LRESULT CPDDocumentView::OnSysKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nVirtKey = (int) wParam;    // virtual-key code 
	UINT lKeyData = lParam;          // key data 
 
	m_bAlt = lKeyData & (1<<29);

//	MessageBeep(-1);

	OnSetCursor();

	if (m_dragging)
	{
		OnMouseMove();
	}

	return 0;
	return DefWindowProc(uMsg, wParam, lParam);
}

LRESULT CPDDocumentView::OnSysKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nVirtKey = (int) wParam;    // virtual-key code 
	UINT lKeyData = lParam;          // key data 
 
	m_bAlt = lKeyData & (1<<29);

	OnSetCursor();

	if (m_dragging)
	{
		OnMouseMove();
	}

	return 0;
	return DefWindowProc(uMsg, wParam, lParam);
}


LRESULT CPDDocumentView::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nVirtKey = (int) wParam;    // virtual-key code 
	UINT lKeyData = lParam;          // key data 
 
	OnSetCursor();

	LONG bCtrl = (GetAsyncKeyState(VK_CONTROL) & (1<<15));
	LONG bShift = (GetAsyncKeyState(VK_SHIFT) & (1<<15));

	long activeTool;

	if (m_dragging)
	{
		activeTool = m_activeTool;
	}
	else
	{
		if (!bCtrl)
			activeTool = gApp->m_activeTool;
		else
			activeTool = gApp->m_activeSelectionTool;
	}

	if (m_pActiveObject)
	{
		CComQIPtr<IPDObjectText> contentText;

		if (activeTool == ID_TOOL_TEXT)
		{
			CComQIPtr<IPDObjectFrame> frame = m_pActiveObject->m_object;
			if (frame)
			{
				CComPtr<IPDObject> content;
				frame->get_content(&content);
				contentText = content;
			}
			else
				contentText = m_pActiveObject->m_object;
		}

		if (contentText)
		{
			if (m_range)
			{
				CComPtr<IPDStory> story;
				m_range->GetStory(&story);

				HDC hDC = GetDC();

				DrawTextSelection(hDC);	// Erase

				switch (nVirtKey)
				{
					case VK_LEFT:
					case VK_RIGHT:
					case VK_HOME:
					case VK_END:
					case VK_UP:
					case VK_DOWN:
						{
							CComQIPtr<IUIManager> uiManager = gIFrame;

							// Dectivate previous range
							uiManager->DeactivateObject(m_range);

							switch (nVirtKey)
							{
							case VK_LEFT:
								{
									m_range->MoveLeft(bCtrl? tomWord: tomCharacter, 1, bShift, NULL);
								}
								break;

							case VK_RIGHT:
								{
									m_range->MoveRight(bCtrl? tomWord: tomCharacter, 1, bShift, NULL);
								}
								break;

							case VK_HOME:
								{
									m_range->HomeKey(tomLine, bShift, NULL);
								}
								break;

							case VK_END:
								{
									m_range->EndKey(tomLine, bShift, NULL);
								}
								break;

							case VK_UP:
								{
									m_range->MoveUp(tomLine, 1, bShift, NULL);
								}
								break;

							case VK_DOWN:
								{
									m_range->MoveDown(tomLine, 1, bShift, NULL);
								}
								break;
							}

							// Activate new range
							uiManager->ActivateObject(GetUnknown(), m_range);
						}
						break;

				/*
					case VK_PRIOR:
					case VK_NEXT:
					*/
					case VK_RETURN:
						{
#if 0
							CComPtr<IDOMNode> startContainer;
							long startOffset;

							range->get_startContainer(&startContainer);
							range->get_startOffset(&startOffset);

						//////
							CComPtr<IPDStory> story;
							contentText->get_story(&story);

							CComPtr<IDOMDocument> document;
							story->get_textDocument(&document);

							CComPtr<IDOMElement> parentP = GetParentParagraph(startContainer);
							ATLASSERT(parentP != NULL);

							CComPtr<IRange> nrange;
							nrange.CoCreateInstance(CLSID_Range);

							nrange->selectNodeContents(parentP);
							nrange->setStart(startContainer, startOffset);

							CComPtr<IDOMDocumentFragment> fragment;
							nrange->extractContents(&fragment);

							CComPtr<IDOMNode> parentParentP;
							parentP->get_parentNode(&parentParentP);

							CComPtr<IDOMNode> beforeNode;
							parentP->get_nextSibling(&beforeNode);
							if (beforeNode)
								parentParentP->insertBefore(fragment, beforeNode, NULL);
							else
								parentParentP->appendChild(fragment, NULL);

							//CComPtr<IDOMElement> p;
							//document->createElement(L"p", &p);

							//p->appendChild(fragment, NULL);

							/*
							{
								BSTR b;
								document->saveXML(fragment, &b);
								::MessageBox(GetMainHwnd(), _bstr_t(b), "", MB_OK);
								SysFreeString(b);
							}
							*/
#endif
						}
						break;

				case VK_BACK:
				case VK_DELETE:
					{
						VARIANT_BOOL bCollapsed;
						m_range->IsCollapsed(&bCollapsed);
						if (bCollapsed)
						{
							if (nVirtKey == VK_BACK)
							{
								m_range->Delete(tomCharacter, -1, NULL);
							}
							else
							{
								m_range->Delete(tomCharacter, 1, NULL);
							}

							Invalidate();	// TODO remove
						}
						else
						{
							ClearSelection();
						}
					}
					break;
				}

				DrawTextSelection(hDC);	// Draw new selection

				ReleaseDC(hDC);

				return 0;
			}
		}
		else
		{
			switch (nVirtKey)
			{
				case VK_LEFT:
					{
						//MoveCursorLeft(m_range);
					}
					break;

				case VK_RIGHT:
					{
						//MoveCursorRight(m_range);
					}
					break;

				case VK_UP:
					{
						//MoveCursorLeft(m_range);
					}
					break;

				case VK_DOWN:
					{
						//MoveCursorRight(m_range);
					}
					break;

				case VK_DELETE:
					{
						ClearSelection();
					}
					break;
			}
		}
	}

	if (m_dragging)
	{
		OnMouseMove();
	}

	return DefWindowProc(uMsg, wParam, lParam);
}

LRESULT CPDDocumentView::OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nVirtKey = (int) wParam;    // virtual-key code 
	UINT lKeyData = lParam;          // key data 

	OnSetCursor();

	if (m_dragging)
	{
		OnMouseMove();
	}

	return DefWindowProc(uMsg, wParam, lParam);
}

LRESULT CPDDocumentView::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	BYTE chCharCode = (BYTE) wParam;    // character code 
	UINT lKeyData = lParam;              // key data 
 
	if (chCharCode == 8) return 0;
	if (chCharCode == '\r') return 0;

	if (m_pActiveObject)
	{
		CComQIPtr<IPDObjectText> contentText;

		CComQIPtr<IPDObjectFrame> frame = m_pActiveObject->m_object;
		if (frame)
		{
			CComPtr<IPDObject> content;
			frame->get_content(&content);
			contentText = content;
		}
		else
			contentText = m_pActiveObject->m_object;

		if (contentText)
		{
			if (m_range/* && m_curContainer*/)
			{
/*				CComPtr<IRange> range;
				m_range->GetDOMRange(&range);

				//range->deleteContents();

				CComPtr<IDOMNode> startContainer;
				long startOffset;
				range->get_startContainer(&startContainer);
				range->get_startOffset(&startOffset);

				CComQIPtr<IDOMText> text = startContainer;
				if (text)
				{
*/
					WCHAR c2[2] = {chCharCode, 0};

					m_range->TypeText(c2);
#if 0
				text->insertData(startOffset, c2);

				//	ATLASSERT(0);
					CComPtr<IDOMNode> container;
					long offset;

					m_range->MoveRight(tomCharacter, 1, 0, NULL);
					/*
						MoveCursorRight(startContainer, startOffset, &container, &offset);

					m_initContainer = container;
					m_initOffset = offset;
					m_curContainer = container;
					m_curOffset = offset;

					range->setStart(container, offset);
					range->setEnd(container, offset);
					*/

					Invalidate();	// TODO remove
				}
#endif
			}

			return 0;
		}
	}

	return DefWindowProc(uMsg, wParam, lParam);
}

LRESULT CPDDocumentView::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int wTimerID = wParam;             // timer identifier 
	//tmprc = (TIMERPROC *) lParam;  // address of timer callback 

	if (m_dragging)
	{
		if (m_activeTool == ID_TOOL_TWIRL ||
			m_activeTool == ID_TOOL_BULGE)
		{
			OnMouseMove();
		}
	}

	return 0;
}

LRESULT CPDDocumentView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_bInvalid = true;

	Invalidate();
	OnSize();

	return 0;
}

void CPDDocumentView::OnSize()
{
	CRect client;
	GetClientRect(&client);

	int sbHeight = GetSystemMetrics(SM_CYHSCROLL);
	int sbWidth = GetSystemMetrics(SM_CXVSCROLL);

	BOOL bVertSB = TRUE;
	BOOL bHorzSB = TRUE;

	m_areaRect.left = 0;
	m_areaRect.top = 0;
	m_areaRect.right = client.right;
	m_areaRect.bottom = client.bottom;

	m_areaRect.right -= sbWidth;
	m_areaRect.bottom -= sbHeight;

	if (m_bRulers)
	{
		m_areaRect.left += 16;
		m_areaRect.top += 16;
	}

	double pageWidth;
	double pageHeight;
	m_document->get_pageWidth(&pageWidth);
	m_document->get_pageHeight(&pageHeight);

	/*
	int minx;
	int miny;
	int maxx;
	int maxy;
	*/
	double minx;
	double miny;
	double maxx;
	double maxy;

	if (m_activeMasterSpread == NULL)
	{
		CComPtr<IObjectMap> spreads;
		m_document->get_spreads(&spreads);

		long nspreads;
		spreads->get_length(&nspreads);

		int iminx = 0;
		int imaxx = 0;

		m_spine = 0;
//		m_maxPages = 0;

		for (int nspread = 0; nspread < nspreads; nspread++)
		{
			CComQIPtr<IPDSpread> spread;
			spreads->item(nspread, (IUnknown**)&spread);

			long spine;
			spread->get_spine(&spine);

			CComPtr<IObjectMap> pages;
			spread->get_pages(&pages);

			long npages;
			pages->get_length(&npages);

			m_spine = max(m_spine, spine);

			iminx = min(iminx, -spine);
			imaxx = max(imaxx, npages-spine);
		}

		m_maxPages = -iminx + imaxx;

		imaxx -= iminx;
		iminx = 0;

		minx = (iminx*pageWidth-100)*m_magnify;
		maxx = (imaxx*pageWidth+100)*m_magnify;

		miny = (-100)*m_magnify;
		maxy = ((pageHeight*nspreads + (nspreads-1)*m_spreadDistance)+100)*m_magnify;
	}
	else
	{
		CComPtr<IObjectMap> pages;
		m_activeMasterSpread->get_pages(&pages);

		long npages;
		pages->get_length(&npages);

		minx = (-100)*m_magnify;
		miny = (-100)*m_magnify;
		maxx = (pageWidth*npages+100)*m_magnify;
		maxy = (pageHeight+100)*m_magnify;
	}

	if (bHorzSB)
	{
		double width = maxx-minx;

		if (m_areaRect.Width() > width)
		{
			m_horz->SetInfo(
				(minx -(m_areaRect.Width()-width)/2),
				(minx -(m_areaRect.Width()-width)/2),
				m_areaRect.Width());
		}
		else
		{
			m_horz->SetInfo(minx, maxx, m_areaRect.Width());
		}

		m_axhorz.MoveWindow(0, m_areaRect.bottom, m_areaRect.right, sbHeight);
		m_axhorz.ShowWindow(SW_SHOW);
	}
	else
	{
		m_horz->SetInfo(0, 0, 0);
		m_axhorz.ShowWindow(SW_HIDE);
	}

	if (bVertSB)
	{
		double height = maxy-miny;

		if (m_areaRect.Height() > height)
		{
			m_vert->SetInfo(
				(miny -(m_areaRect.Height()-height)/2),
				(miny -(m_areaRect.Height()-height)/2),
				m_areaRect.Height());
		}
		else
		{
			m_vert->SetInfo(miny, maxy, m_areaRect.Height());
		}

		m_axvert.MoveWindow(m_areaRect.right, 0, sbWidth, m_areaRect.bottom);
		m_axvert.ShowWindow(SW_SHOW);
	}
	else
	{
		m_vert->SetInfo(0, 0, 0);
		m_axvert.ShowWindow(SW_HIDE);
	}

	::MoveWindow(m_hWndSizeGrip, m_areaRect.right, m_areaRect.bottom, client.right-m_areaRect.right, client.bottom-m_areaRect.bottom, TRUE);

	if (m_pBitmap)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}

	m_pBitmap = new Gdiplus::Bitmap(m_areaRect.Width(), m_areaRect.Height()/*, PixelFormat24bppRGB*/);
}

void CPDDocumentView::ZoomToRect2(double left, double top, double right, double bottom)
{
	CDblRect zoomRect;
	zoomRect.left = left;
	zoomRect.top = top;
	zoomRect.right = right;
	zoomRect.bottom = bottom;

//	HWND hwnd = m_hWnd;

	long scrollposX = m_horz->get_pos(&scrollposX);
	long scrollposY = m_vert->get_pos(&scrollposY);

	CDblRect zrect;
	zrect.left = zoomRect.left;
	zrect.top = zoomRect.top;
	zrect.right = zoomRect.right;
	zrect.bottom = zoomRect.bottom;

	double oldmagnify = m_magnify;

//	m_magnify = (double)(pDocument->GetWidth()/**m_magnify*/)/zrect.Width();
	m_magnify = (double)(m_areaRect.Width()/**m_magnify*/)/zrect.Width();
	SetMatrix();

	int cx = zrect.left*m_magnify;
	int cy = zrect.top*m_magnify;

	int animate = 1;

	if (animate == 1)
	{
	/*
		CRect orect;
		orect.left = scrollposX;
		orect.top = scrollposY;
		orect.right = scrollposX + m_imageRect.Width();
		orect.bottom = scrollposY + m_imageRect.Height();

		int total;

		double omagnify = m_magnify;
	*/

		HDC hDC = GetDC();
		int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

		CDblRect imageRect;
		imageRect.left = m_areaRect.left;
		imageRect.top = m_areaRect.top;
		imageRect.right = m_areaRect.right;
		imageRect.bottom = m_areaRect.bottom;

		CDblRect orect;
		CDblRect zRect;

		if (m_magnify > oldmagnify) // Zoom in
		{
			orect = imageRect;
			zRect = zoomRect;

			zRect.left *= oldmagnify;
			zRect.top *= oldmagnify;
			zRect.right *= oldmagnify;
			zRect.bottom *= oldmagnify;
		
			zRect.left -= scrollposX;
			zRect.top -= scrollposY;
			zRect.right -= scrollposX;
			zRect.bottom -= scrollposY;
		}
		else
		{
			zRect = imageRect;
			orect = zoomRect;

			orect.left += scrollposX;
			orect.top += scrollposY;
			orect.right += scrollposX;
			orect.bottom += scrollposY;

			orect.left /= oldmagnify;
			orect.top /= oldmagnify;
			orect.right /= oldmagnify;
			orect.bottom /= oldmagnify;

		/*
			orect.left /= m_magnify;
			orect.top /= m_magnify;
			orect.right /= m_magnify;
			orect.bottom /= m_magnify;
		*/
		}

		CRect zrect2;
		int atotal = 20;

		for (int i = 0; i <= atotal; i++)
		{
			if (i > 0)
				Rectangle(hDC, zrect2.left, zrect2.top, zrect2.right, zrect2.bottom);

			zrect2.left = orect.left + (zRect.left-orect.left)*i/atotal;
			zrect2.top = orect.top + (zRect.top-orect.top)*i/atotal;
			zrect2.right = orect.right + (zRect.right-orect.right)*i/atotal;
			zrect2.bottom = orect.bottom + (zRect.bottom-orect.bottom)*i/atotal;

			Rectangle(hDC, zrect2.left, zrect2.top, zrect2.right, zrect2.bottom);

			Sleep(1);
		}

		SelectObject(hDC, hOldBrush);
		SetROP2(hDC, oldR2);
		ReleaseDC(hDC);
	}

	{
		m_bInvalid = true;
		OnSize();
		InvalidateRect(NULL, TRUE);

		setScrollPosXY(cx, cy);

		UpdateWindow();
	}
}
/*
void __stdcall CPDDocumentView::OnDocumentSetupChanged()
{
	OnSize();
	Invalidate();
}
*/
void __stdcall CPDDocumentView::OnHorzScroll(long code, long pos)
{
	long oldPos; m_horz->get_pos(&oldPos);
	m_horz->put_pos(pos);

	m_bInvalid = true;

	// Scroll bitmap
	{
		Gdiplus::Bitmap* newbm = new Gdiplus::Bitmap(m_areaRect.Width(), m_areaRect.Height()/*, PixelFormat24bppRGB*/);
		{
			Gdiplus::Graphics graphicsbm(newbm);
			graphicsbm.DrawImage(m_pBitmap, oldPos-pos, 0);
		}
		delete m_pBitmap;
		m_pBitmap = newbm;
	}

	EraseBrushOutline();
	
	ScrollWindow(oldPos-pos, 0, &m_areaRect, &m_areaRect);

	CRect rulerRect(16, 0, m_areaRect.right, 16);
	ScrollWindow(oldPos-pos, 0, &rulerRect, &rulerRect);

	Fire_ViewBoxChanged();
}

void __stdcall CPDDocumentView::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);
	m_vert->put_pos(pos);

	m_bInvalid = true;

	// Scroll bitmap
	{
		Gdiplus::Bitmap* newbm = new Gdiplus::Bitmap(m_areaRect.Width(), m_areaRect.Height()/*, PixelFormat24bppRGB*/);
		{
			Gdiplus::Graphics graphicsbm(newbm);
			graphicsbm.DrawImage(m_pBitmap, 0, oldPos-pos);
		}
		delete m_pBitmap;
		m_pBitmap = newbm;
	}

	EraseBrushOutline();

	ScrollWindow(0, oldPos-pos, &m_areaRect, &m_areaRect);

	CRect rulerRect(0, 16, 16, m_areaRect.bottom);
	ScrollWindow(0, oldPos-pos, &rulerRect, &rulerRect);

	Fire_ViewBoxChanged();
}

STDMETHODIMP CPDDocumentView::get_activeSpread(IPDSpread **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_activeSpread;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDDocumentView::put_activeSpread(IPDSpread *newVal)
{
	if (m_activeSpread != newVal)
	{
		if (m_activeSpread == NULL)
		{
			if (m_hWnd)
			{
				Invalidate();
			}
		}

		m_activeSpread = newVal;
		m_activeMasterSpread = newVal;

		DeselectAll();

		double pageWidth;
		double pageHeight;
		m_document->get_pageWidth(&pageWidth);
		m_document->get_pageHeight(&pageHeight);

		m_activeSpreadOffset.x = 0;
		m_activeSpreadOffset.y = 0;

		if (m_activeMasterSpread == NULL)
		{
			CComPtr<IObjectMap> spreads;
			m_document->get_spreads(&spreads);

			long nspreads;
			spreads->get_length(&nspreads);

			for (long nspread = 0; nspread < nspreads; nspread++)
			{
				CComQIPtr<IPDSpread> spread;
				spreads->item(nspread, (IUnknown**)&spread);

				if (spread == m_activeSpread)
					break;

				m_activeSpreadOffset.y += pageHeight + m_spreadDistance;
			}

			long spine;
			m_activeSpread->get_spine(&spine);

			m_activeSpreadOffset.x = (m_spine-spine)*pageWidth;
		}

		SetMatrix();
		OnSize();

		// Scroll spread into view
		setScrollPosXY((long)(m_activeSpreadOffset.x*m_magnify), (long)(m_activeSpreadOffset.y*m_magnify));
	}

	return S_OK;
}

STDMETHODIMP CPDDocumentView::setScrollPosXY(long posx, long posy)
{
	long oldPosX; m_horz->get_pos(&oldPosX);
	long oldPosY; m_vert->get_pos(&oldPosY);

	m_horz->put_pos(posx);
	m_vert->put_pos(posy);

// Retrieve the actual new position, restricted by min/max of scrollbar
	m_horz->get_pos(&posx);
	m_vert->get_pos(&posy);

	m_bInvalid = true;

	// Scroll bitmap
	{
		Gdiplus::Bitmap* newbm = new Gdiplus::Bitmap(m_areaRect.Width(), m_areaRect.Height()/*, PixelFormat24bppRGB*/);
		{
			Gdiplus::Graphics graphicsbm(newbm);
			graphicsbm.DrawImage(m_pBitmap, oldPosX-posx, oldPosY-posy);
		}
		delete m_pBitmap;
		m_pBitmap = newbm;
	}

	if (m_hWnd)
	{
		EraseBrushOutline();

		ScrollWindow(oldPosX-posx, oldPosY-posy, &m_areaRect, &m_areaRect);

		{
			CRect rulerRect(0, 16, 16, m_areaRect.bottom);
			ScrollWindow(0, oldPosY-posy, &rulerRect, &rulerRect);
		}

		{
			CRect rulerRect(16, 0, m_areaRect.right, 16);
			ScrollWindow(oldPosX-posx, 0, &rulerRect, &rulerRect);
		}

		Fire_ViewBoxChanged();
	}

	return S_OK;
}

STDMETHODIMP CPDDocumentView::getViewBox(RECT *pVal)
{
	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	int x = -m_areaRect.left;
	int y = -m_areaRect.top;

//	x -= m_activeSpreadOffset.x;
//	y -= m_activeSpreadOffset.y;

	x += scrollposX;
	y += scrollposY;

	int width = m_areaRect.Width();
	int height = m_areaRect.Height();

	pVal->left = (int)(x / m_magnify);
	pVal->top = (int)(y / m_magnify);
	pVal->right = (int)((x + width) / m_magnify);
	pVal->bottom = (int)((y + height) / m_magnify);

//	OffsetRect(pVal, -m_activeSpreadOffset.x, -m_activeSpreadOffset.y);

	return S_OK;
}

STDMETHODIMP CPDDocumentView::setRulerOrigin(double x, double y)
{
	if (m_rulerOffset.x != x)
	{
		m_rulerOffset.x = x;
		InvalidateRect(&CRect(16, 0, m_areaRect.right, 16));
	}

	if (m_rulerOffset.y != y)
	{
		m_rulerOffset.y = y;
		InvalidateRect(&CRect(0, 16, 16, m_areaRect.bottom));
	}

	return S_OK;
}

STDMETHODIMP CPDDocumentView::get_rulers(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_bRulers? VARIANT_TRUE: VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CPDDocumentView::put_rulers(VARIANT_BOOL newVal)
{
	if ((m_bRulers==0) != (newVal==0))
	{
		m_bRulers = newVal? true: false;

		OnSize();
		Invalidate();
	}

	return S_OK;
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

   Gdiplus::GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

void CPDDocumentView::CopyTargetObjectsToClipboard(IDataObject* dataObject)
{
	RectD objectsBoundingBox;
	CalculateObjectsExpandedBoundingBox(&objectsBoundingBox);

	if (m_pActiveObject && objectsBoundingBox.Width > 0 && objectsBoundingBox.Height > 0)
	{
		Gdiplus::Bitmap* pBitmap = NULL;

		HDC hDC = ::GetDC(NULL);
		long inchesPerPixelX = GetDeviceCaps(hDC, LOGPIXELSX);
		long inchesPerPixelY = GetDeviceCaps(hDC, LOGPIXELSY);
		::ReleaseDC(NULL, hDC);

		long ppi = inchesPerPixelX;
		Gdiplus::Color bgColor = Gdiplus::Color(0, 0, 0, 0);

		int pixelWidth = (int)ceil(objectsBoundingBox.Width*ppi/inchesPerPixelX);
		int pixelHeight = (int)ceil(objectsBoundingBox.Height*ppi/inchesPerPixelY);

		CComPtr<IPDContentGraphic> contentGraphic;
		m_document->createContentGraphic(&contentGraphic);

		double scaleX = (double)inchesPerPixelX/ppi;
		double scaleY = (double)inchesPerPixelY/ppi;

		CComPtr<IPDRenderer> renderer;
		renderer.CoCreateInstance(CLSID_PDRenderer);
		if (renderer)
		{
			pBitmap = new Gdiplus::Bitmap(pixelWidth, pixelHeight, PixelFormat32bppARGB);
			if (pBitmap)
			{
				Gdiplus::Graphics graphics(pBitmap);
				graphics.Clear(bgColor);

				renderer->put_targetHDC((HDC)&graphics);
				renderer->put_magnify(1/scaleX);

				graphics.ScaleTransform(1/scaleX, 1/scaleY);
				graphics.TranslateTransform(-objectsBoundingBox.X, -objectsBoundingBox.Y);

				for (int i = 0; i < m_targetObjects.GetSize(); i++)
				{
					CPDObjectSelected* pObject = m_targetObjects[i];
					CComQIPtr<IPDObject> object = pObject->m_object;
					if (object)
					{
						renderer->RenderObject(object);
					}
				}
			}
		}

		if (pBitmap)
		{
			CComQIPtr<IPDApplicationSettings> appSettings = gIApp;

			VARIANT_BOOL bPng;
			appSettings->get_clipboardSavePNG(&bPng);

			VARIANT_BOOL bJpeg;
			appSettings->get_clipboardSaveJPEG(&bJpeg);

			VARIANT_BOOL bGif;
			appSettings->get_clipboardSaveGIF(&bGif);

			if (bPng)
			{
				STGMEDIUM stgm;
				stgm.tymed = TYMED_ISTREAM;
				stgm.pUnkForRelease = NULL;
				if (SUCCEEDED(CreateStreamOnHGlobal(NULL, TRUE, &stgm.pstm)))
				{
					CLSID pngClsid;
					GetEncoderClsid(L"image/png", &pngClsid);

					Gdiplus::Status stat = pBitmap->Save(stgm.pstm, &pngClsid);
					if(stat == Gdiplus::Ok)
					{
						FORMATETC etc = { _clipboardFormats.cfPng, NULL, DVASPECT_CONTENT, -1, TYMED_ISTREAM};

						dataObject->SetData(&etc, &stgm, TRUE);
					}
				}
			}

			if (bJpeg)
			{
				STGMEDIUM stgm;
				stgm.tymed = TYMED_ISTREAM;
				stgm.pUnkForRelease = NULL;
				if (SUCCEEDED(CreateStreamOnHGlobal(NULL, TRUE, &stgm.pstm)))
				{
					CLSID pngClsid;
					GetEncoderClsid(L"image/jpeg", &pngClsid);

					Gdiplus::Status stat = pBitmap->Save(stgm.pstm, &pngClsid);
					if(stat == Gdiplus::Ok)
					{
						FORMATETC etc = { _clipboardFormats.cfJpeg, NULL, DVASPECT_CONTENT, -1, TYMED_ISTREAM};

						dataObject->SetData(&etc, &stgm, TRUE);
					}
				}
			}

			if (bGif)
			{
				STGMEDIUM stgm;
				stgm.tymed = TYMED_ISTREAM;
				stgm.pUnkForRelease = NULL;
				if (SUCCEEDED(CreateStreamOnHGlobal(NULL, TRUE, &stgm.pstm)))
				{
					CLSID pngClsid;
					GetEncoderClsid(L"image/gif", &pngClsid);

					Gdiplus::Status stat = pBitmap->Save(stgm.pstm, &pngClsid);
					if(stat == Gdiplus::Ok)
					{
						FORMATETC etc = { _clipboardFormats.cfGif, NULL, DVASPECT_CONTENT, -1, TYMED_ISTREAM};

						dataObject->SetData(&etc, &stgm, TRUE);
					}
				}
			}
		}
	}

#if 0
	CArray<IPDObject*,IPDObject*> objects;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObject> object = m_targetObjects[i]->m_object;
		if (object)
		{
			objects.Add(object);
		}
	}

	if (objects.GetSize() > 0)
	{
		CComPtr<IPDObject> symbolObject;

		if (objects.GetSize() == 1)
		{
			CComPtr<IPDObject> object;
			objects[0]->clone(&object);
			if (object)
			{
				symbolObject = object;
			}
		}
		else
		{
			CComPtr<IPDObjectGroup> group;
			m_document->createObjectGroup(GUID_NULL, &group);
			if (group)
			{
				for (int i = 0; i < objects.GetSize(); i++)
				{
					CComPtr<IPDObject> object;
					objects[i]->clone(&object);
					if (object)
					{
						group->appendObject(object);
					}
				}

				symbolObject = group;
			}
		}

		if (symbolObject)
		{
			CComQIPtr<IPDObjectTransformable> transformable = symbolObject;

			RectD bounds;
			transformable->get_bounds(&bounds);

			transformable->Move(-bounds.X, -bounds.Y);

			symbol->put_symbolObject(symbolObject);
		}
	}
#endif

#if 0
	{
		CComPtr<IDOMDocument> document;
		document.CoCreateInstance(CLSID_LDOMDocument);

		VARIANT_BOOL bloaded;
		document->loadXML(L"<group/>", &bloaded);

		CComPtr<IDOMElement> documentElement;
		document->get_documentElement(&documentElement);

		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CPDObjectSelected* pObject = m_targetObjects[i];

			PDObjectType objectType;
			pObject->m_object->get_objectType(&objectType);

			CComPtr<IDOMElement> element;
			if (objectType == OBJECT_FRAME)
				document->createElement(L"frame", &element);
			else if (objectType == OBJECT_GROUP)
				document->createElement(L"group", &element);

			if (element)
			{
				pObject->m_object->saveAsXML(document, element, FALSE);

				documentElement->appendChild(element, NULL);
			}
			else
				ATLASSERT(0);
		}

		BSTR bxml;
		document->saveXML(NULL, &bxml);

		int xmllen = SysStringLen(bxml);

		HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, (xmllen+1)*2);
		if (hData)
		{
			BSTR p = (BSTR)GlobalLock(hData);
			if (p)
			{
				CopyMemory(p, bxml, xmllen*2);
				p[xmllen] = 0;

				GlobalUnlock(hData);

				SetClipboardData(CF_UNICODETEXT, hData);
			}
		}

		SysFreeString(bxml);

		::CloseClipboard();
	}
#endif
}

IPDObjectGroup* CPDDocumentView::GetObjectGroupFromClipboard()
{
	CComPtr<IPDObjectGroup> group;

	ATLASSERT(0);
/*
	if (::OpenClipboard(NULL))
	{
		HANDLE hData = GetClipboardData(CF_UNICODETEXT);
		if (hData)
		{
			DWORD nbytes = GlobalSize(hData);
			BSTR p = (BSTR)GlobalLock(hData);
			if (p)
			{
				CComPtr<IDOMDocument> document;
				document.CoCreateInstance(CLSID_LDOMDocument);
				document->put_async(VARIANT_FALSE);

				VARIANT_BOOL bloaded;
				document->loadXML(p, &bloaded);
				if (bloaded)
				{
					CComPtr<IDOMElement> documentElement;
					document->get_documentElement(&documentElement);
					if (documentElement)
					{
						m_document->createObjectGroup(GUID_NULL, &group);

						group->loadXML(documentElement);
					}
				}

				GlobalUnlock(p);
			}
		}

		::CloseClipboard();
	}

  */

	if (group)
		return group.Detach();
	else
		return NULL;
}

void CPDDocumentView::PasteObjectsFromClipboard()
{
	CComQIPtr<IPDObjectLayerGroup> activeLayerGroup;
	if (m_activeSpread)
		m_activeSpread->getLayerGroupFromLayer(m_activeLayer, &activeLayerGroup);

	if (activeLayerGroup)
	{
		CComPtr<IPDObjectGroup> group = GetObjectGroupFromClipboard();

		CComPtr<IObjectMap> children;
		group->get_children(&children);

		long nchildren;
		children->get_length(&nchildren);

		for (long i = 0; i < nchildren; i++)
		{
			CComPtr<IPDObject> object;
			children->item(0, (IUnknown**)&object);

			activeLayerGroup->appendObject(object);
		}

		Invalidate();
	}
	else
	{
		::MessageBox(GetMainHwnd(), "You must select a spread", "PageDesigner", MB_OK);
	}
}

void CPDDocumentView::PasteObjectsIntoFromClipboard()
{
	if (m_targetObjects.GetSize() == 1)
	{
		CComPtr<IPDObjectGroup> group = GetObjectGroupFromClipboard();
		if (group)
		{
			CComPtr<IObjectMap> children;
			group->get_children(&children);

			long nchildren;
			children->get_length(&nchildren);

			if (nchildren == 1)
			{
				CComQIPtr<IPDObjectFrame> frame;
				CComQIPtr<IPDObjectText> text;

				CComPtr<IPDObject> object;
				children->item(0, (IUnknown**)&object);

				if (frame = m_targetObjects[0]->m_object)
				{
					frame->put_content(object);
				}
				else if (text = m_targetObjects[0]->m_object)
				{
					CComPtr<IPDStory> story;
					text->get_story(&story);

					CComPtr<ILDOMDocument> textDocument;
					story->get_textDocument(&textDocument);

					GUID guid;
					object->get_uniqId(&guid);

					CComPtr<ILDOMElement> elementObject;
					textDocument->createElement(L"object", &elementObject);

					LPOLESTR guidstr;
					StringFromCLSID(guid, &guidstr);
					elementObject->setAttribute(L"guid", guidstr);
					CoTaskMemFree(guidstr);

					story->appendInlineObject(object);

					CComPtr<ILDOMRange> range;
					m_range->GetDOMRange(&range);

					range->insertNode(elementObject);
				}

				Invalidate();	// TODO, remove
			}
		}
	}
}

void CPDDocumentView::CopySelectionToClipboard()
{
	LONG bCtrl = (GetAsyncKeyState(VK_CONTROL) & (1<<15));

	long activeTool;

	if (m_dragging)
	{
		activeTool = m_activeTool;
	}
	else
	{
		if (!bCtrl)
			activeTool = gApp->m_activeTool;
		else
			activeTool = gApp->m_activeSelectionTool;
	}

	CComObject<COleDataObject>* dataObject;
	CComObject<COleDataObject>::CreateInstance(&dataObject);
	if (dataObject)
	{
		dataObject->AddRef();

		if (m_pActiveObject)
		{
			CComQIPtr<IPDObjectText> contentText;

			if (activeTool == ID_TOOL_TEXT)
			{
				CComQIPtr<IPDObjectFrame> frame = m_pActiveObject->m_object;
				if (frame)
				{
					CComPtr<IPDObject> content;
					frame->get_content(&content);
					contentText = content;
				}
				else
					contentText = m_pActiveObject->m_object;
			}

			if (contentText)
			{
				if (m_range)
				{
					CComPtr<ILDOMRange> domrange;
					m_range->GetDOMRange(&domrange);

					CComPtr<ILDOMDocumentFragment> fragment;
					domrange->cloneContents(&fragment);

					BSTR btext;
					fragment->get_textContent(&btext);

					int btextlen = SysStringLen(btext);
					
					HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, (btextlen+1)*2);
					if (h)
					{
						WCHAR* p = (WCHAR*)GlobalLock(h);
						if (p)
						{
							memcpy(p, btext, (btextlen+1)*2);

							STGMEDIUM stgm;
							stgm.tymed = TYMED_HGLOBAL;
							stgm.pUnkForRelease = NULL;
							stgm.hGlobal = h;

							FORMATETC etc = { CF_UNICODETEXT, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
							dataObject->SetData(&etc, &stgm, TRUE);

							GlobalUnlock(h);
						}
					}

					SysFreeString(btext);
				}
			}
			else
			{
				CopyTargetObjectsToClipboard(dataObject);
			}
		}

		OleSetClipboard(dataObject);

		dataObject->Release();
	}
}

void CPDDocumentView::ClearSelection()
{
	LONG bCtrl = (GetAsyncKeyState(VK_CONTROL) & (1<<15));

	long activeTool;

	if (m_dragging)
	{
		activeTool = m_activeTool;
	}
	else
	{
		if (!bCtrl)
			activeTool = gApp->m_activeTool;
		else
			activeTool = gApp->m_activeSelectionTool;
	}

	if (m_pActiveObject)
	{
		CComQIPtr<IPDObjectText> contentText;

		if (activeTool == ID_TOOL_TEXT)
		{
			CComQIPtr<IPDObjectFrame> frame = m_pActiveObject->m_object;
			if (frame)
			{
				CComPtr<IPDObject> content;
				frame->get_content(&content);
				contentText = content;
			}
			else
				contentText = m_pActiveObject->m_object;
		}

		if (contentText)
		{
			if (m_range)
			{
				m_range->Delete(tomCharacter, 0, NULL);
#if 0
				CComPtr<IRange> domrange;
				m_range->GetDOMRange(&domrange);

// TODO here, have a method on m_range
				domrange->deleteContents();

				CComPtr<IDOMNode> startContainer;
				long startOffset;
				domrange->get_startContainer(&startContainer);
				domrange->get_startOffset(&startOffset);

				m_range->Set(startContainer, startOffset);
				/*
				m_curContainer = startContainer;
				m_curOffset = startOffset;
				m_initContainer = startContainer;
				m_initOffset = startOffset;
				*/
#endif
				Invalidate();	// TODO remove this
			}
		}
		else if (activeTool == ID_TOOL_DIRECT)
		{
			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				CPDObjectSelected* pObject = m_targetObjects[i];

				PDObjectType objectType;
				pObject->m_object->get_objectType(&objectType);

				if (pObject->m_wrapPath)
				{
					pObject->m_wrapPath->DeleteSelection();
				}

				if (objectType == OBJECT_FRAME)
				{
					CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;
					pFrame->m_path->DeleteSelection();
				}
			}

			m_pActivePath = NULL;
			m_curveCp = -1;
		}
		else
		{
			ClearTargetObjects();
		}
	}
}

void CPDDocumentView::ClearTargetObjects()
{
	if (m_pActiveObject)
	{
		CComQIPtr<IOleUndoManager> undoManager;
		m_document->get_undoManager(&undoManager);

		CComObject<CUndoClearObjects>* pUndo;
		CComObject<CUndoClearObjects>::CreateInstance(&pUndo);
		if (pUndo)
		{
			pUndo->AddRef();
			pUndo->m_document = m_document;
			m_activeSpread->get_uniqId(&pUndo->m_spreadGUID);
			pUndo->m_pView = this;
			pUndo->m_bRedo = true;

			CComQIPtr<IPDObjectUnknown> objectChild = m_pActiveObject->m_object;

			CComPtr<IPDObjectUnknown> parentUnknown;
			objectChild->get_parent(&parentUnknown);

			CComQIPtr<IPDObjectWithChildren> parent = parentUnknown;

			GUID parentGuid;
			parentUnknown->get_uniqId(&parentGuid);

			CComPtr<IObjectMap> children;
			parent->get_children(&children);

			long length;
			children->get_length(&length);

			for (long i = 0; i < length; i++)
			{
				CComPtr<IPDObjectUnknown> objectUnknown;
				children->item(i, (IUnknown**)&objectUnknown);

				if (IsPDObjectSelected(objectUnknown))
				{
					objectUnknown.p->AddRef();
					int refcount = objectUnknown.p->Release();

					GUID guid;

					//CComQIPtr<IPDObjectChild> objectChild = objectUnknown;

					CComPtr<IPDObjectUnknown> beforeNode;
					objectChild->get_nextSibling(&beforeNode);

					//CComQIPtr<IPDObjectUnknown> beforeNode = beforeNodeChild;

					objectUnknown->get_uniqId(&guid);
					pUndo->m_targetElements.Add(guid);

					pUndo->m_parentElements.Add(parentGuid);

					if (beforeNode != NULL)
					{
						beforeNode->get_uniqId(&guid);
						pUndo->m_beforeElements.Add(guid);
					}
					else
					{
						pUndo->m_beforeElements.Add(GUID_NULL);
					}
				}
			}

			pUndo->Do(undoManager);

			Invalidate();
		}
	}
}

BEGIN_CMD_MAP(CPDDocumentView)
// File
	CMD_HANDLER(ID_FILE_PLACE, OnFilePlace)

// Edit
	CMD_HANDLER(ID_EDIT_CUT, OnEditCut)
	CMD_HANDLER(ID_EDIT_COPY, OnEditCopy)
	CMD_HANDLER(ID_EDIT_PASTE, OnEditPaste)
	CMD_HANDLER(ID_EDIT_PASTE_SPECIAL, OnEditPasteSpecial)
	CMD_HANDLER(ID_EDIT_PASTEINTO, OnEditPasteInto)
	CMD_HANDLER(ID_EDIT_CLEAR, OnEditClear)

	CMD_UPDATE(ID_EDIT_CUT, OnEditCutCopyClearUpdate)
	CMD_UPDATE(ID_EDIT_COPY, OnEditCutCopyClearUpdate)
	CMD_UPDATE(ID_EDIT_CLEAR, OnEditCutCopyClearUpdate)
	CMD_UPDATE(ID_EDIT_PASTE, OnEditPasteUpdate)
	CMD_UPDATE(ID_EDIT_PASTEINTO, OnEditPasteIntoUpdate)
	CMD_UPDATE(ID_EDIT_PASTE_SPECIAL, OnEditPasteSpecialUpdate)

	CMD_HANDLER(ID_EDIT_DEFINEPATTERN, OnEditDefinePattern)
	CMD_UPDATE(ID_EDIT_DEFINEPATTERN, OnEditDefinePatternUpdate)

// View
	CMD_HANDLER(ID_VIEW_ZOOMIN, OnViewZoomIn)
	CMD_HANDLER(ID_VIEW_ZOOMOUT, OnViewZoomOut)
	CMD_HANDLER(ID_VIEW_ACTUALSIZE, OnViewActualSize)
	CMD_UPDATE(ID_VIEW_ACTUALSIZE, OnViewActualSizeUpdate)
	CMD_HANDLER(ID_VIEW_RULERS, OnViewRulers)
	CMD_UPDATE(ID_VIEW_RULERS, OnViewRulersUpdate)
	CMD_HANDLER(ID_VIEW_TRANSPARENCYGRID, OnViewTransparencyGrid)
	CMD_UPDATE(ID_VIEW_TRANSPARENCYGRID, OnViewTransparencyGridUpdate)

// Layout
	CMD_HANDLER(ID_LAYOUT_MARGINSANDCOLUMNS, OnLayoutMarginsAndColumns)
	CMD_HANDLER(ID_LAYOUT_CREATEGUIDES, OnLayoutCreateGuides)

// Type
	CMD_HANDLER(ID_TYPE_FONTFACE, OnCharacterFontface)
	CMD_UPDATE(ID_TYPE_FONTFACE, OnCharacterFontfaceUpdate)
	CMD_HANDLER(ID_CHARACTER_FONTSIZE, OnCharacterFontsize)
	CMD_UPDATE(ID_CHARACTER_FONTSIZE, OnCharacterFontsizeUpdate)
	CMD_UPDATE(ID_CHARACTER_LINEHEIGHT, OnCharacterLineheightUpdate)

	CMD_HANDLER(ID_CHARACTER_BOLD, OnCharacterBold)

	CMD_HANDLER(ID_TYPE_CREATEOUTLINES, OnTypeCreateOutlines)

// Object

	CMD_HANDLER(ID_OBJECT_ARRANGE_BRINGTOFRONT, OnObjectArrangeBringToFront)
	CMD_HANDLER(ID_OBJECT_ARRANGE_BRINGFORWARD, OnObjectArrangeBringForward)
	CMD_HANDLER(ID_OBJECT_ARRANGE_SENDBACKWARD, OnObjectArrangeSendBackward)
	CMD_HANDLER(ID_OBJECT_ARRANGE_SENDTOBACK, OnObjectArrangeSendToBack)

	CMD_UPDATE(ID_OBJECT_ARRANGE_BRINGTOFRONT, OnObjectArrangeHigherUpdate)
	CMD_UPDATE(ID_OBJECT_ARRANGE_BRINGFORWARD, OnObjectArrangeHigherUpdate)
	CMD_UPDATE(ID_OBJECT_ARRANGE_SENDBACKWARD, OnObjectArrangeLowerUpdate)
	CMD_UPDATE(ID_OBJECT_ARRANGE_SENDTOBACK, OnObjectArrangeLowerUpdate)

	CMD_HANDLER(ID_OBJECT_GROUP, OnObjectGroup)
	CMD_UPDATE(ID_OBJECT_GROUP, OnObjectGroupUpdate)
	CMD_HANDLER(ID_OBJECT_UNGROUP, OnObjectUngroup)
	CMD_UPDATE(ID_OBJECT_UNGROUP, OnObjectUngroupUpdate)

	CMD_HANDLER(ID_OBJECT_TEXTFRAMEOPTIONS, OnObjectTextFrameOptions)
	CMD_UPDATE(ID_OBJECT_TEXTFRAMEOPTIONS, OnObjectTextFrameOptionsUpdate)

	CMD_HANDLER(ID_OBJECT_PATHTYPE_OPTIONS, OnObjectPathTypeOptions)
	CMD_UPDATE(ID_OBJECT_PATHTYPE_OPTIONS, OnObjectPathTypeOptionsUpdate)

	CMD_HANDLER(ID_OBJECT_COMPOUNDPATHS_MAKE, OnObjectCompoundPathsMake)
	CMD_HANDLER(ID_OBJECT_COMPOUNDPATHS_RELEASE, OnObjectCompoundPathsRelease)
	CMD_HANDLER(ID_OBJECT_REVERSEPATH, OnObjectReversePath)
	CMD_HANDLER(ID_OBJECT_PATH_ADDANCHORPOINTS, OnObjectPathAddAnchorPoints)
	CMD_UPDATE(ID_OBJECT_PATH_ADDANCHORPOINTS, OnObjectPathAddAnchorPointsUpdate)

	CMD_HANDLER(ID_OBJECT_FITTING_FITCONTENTTOFRAME, OnObjectFitContentToFrame)
	CMD_HANDLER(ID_OBJECT_FITTING_FITFRAMETOCONTENT, OnObjectFitFrameToContent)
	CMD_HANDLER(ID_OBJECT_FITTING_CENTERCONTENT, OnCenterContent)
	CMD_HANDLER(ID_OBJECT_FITTING_FITCONTENTPROPORTIONALLY, OnFitContentProportionally)

	CMD_HANDLER(ID_OBJECT_CONTENT_GRAPHIC, OnObjectContentGraphic)
	CMD_HANDLER(ID_OBJECT_CONTENT_TEXT, OnObjectContentText)
	CMD_HANDLER(ID_OBJECT_CONTENT_UNASSIGNED, OnObjectContentUnassigned)

	CMD_HANDLER(ID_OBJECT_RASTERIZE, OnObjectRasterize)
	CMD_UPDATE(ID_OBJECT_RASTERIZE, OnObjectRasterizeUpdate)

// Symbols
	CMD_HANDLER(ID_SYMBOLS_NEWSYMBOL, OnSymbolsNewSymbol)
	CMD_HANDLER(ID_SYMBOLS_BREAKLINKTOSYMBOL, OnSymbolBreakLinktoSymbol)

// Text Wrap
	CMD_HANDLER(ID_TEXTWRAP_NONE, OnTextWrapNone)
	CMD_UPDATE(ID_TEXTWRAP_NONE, OnTextWrapNoneUpdate)
	CMD_HANDLER(ID_TEXTWRAP_BBOX, OnTextWrapBBox)
	CMD_UPDATE(ID_TEXTWRAP_BBOX, OnTextWrapBBoxUpdate)
	CMD_HANDLER(ID_TEXTWRAP_SHAPE, OnTextWrapShape)
	CMD_UPDATE(ID_TEXTWRAP_SHAPE, OnTextWrapShapeUpdate)
	CMD_HANDLER(ID_TEXTWRAP_OBJECT, OnTextWrapObject)
	CMD_UPDATE(ID_TEXTWRAP_OBJECT, OnTextWrapObjectUpdate)
	CMD_HANDLER(ID_TEXTWRAP_COLUMN, OnTextWrapColumn)
	CMD_UPDATE(ID_TEXTWRAP_COLUMN, OnTextWrapColumnUpdate)
	CMD_HANDLER(ID_TEXTWRAP_TOPOFFSET, OnTextWrapOffset)
	CMD_HANDLER(ID_TEXTWRAP_LEFTOFFSET, OnTextWrapOffset)
	CMD_HANDLER(ID_TEXTWRAP_BOTTOMOFFSET, OnTextWrapOffset)
	CMD_HANDLER(ID_TEXTWRAP_RIGHTOFFSET, OnTextWrapOffset)
	CMD_UPDATE(ID_TEXTWRAP_TOPOFFSET, OnTextWrapOffsetUpdate)
	CMD_UPDATE(ID_TEXTWRAP_LEFTOFFSET, OnTextWrapOffsetUpdate)
	CMD_UPDATE(ID_TEXTWRAP_BOTTOMOFFSET, OnTextWrapOffsetUpdate)
	CMD_UPDATE(ID_TEXTWRAP_RIGHTOFFSET, OnTextWrapOffsetUpdate)

// Paragraph

	CMD_HANDLER(ID_TYPE_CHARACTER, OnCharacter)
	CMD_HANDLER(ID_TYPE_PARAGRAPH, OnParagraph)

	CMD_HANDLER(ID_PARAGRAPH_ALIGNLEFT, OnParagraphAlignLeft)
	CMD_HANDLER(ID_PARAGRAPH_ALIGNCENTER, OnParagraphAlignCenter)
	CMD_HANDLER(ID_PARAGRAPH_ALIGNRIGHT, OnParagraphAlignRight)
	CMD_HANDLER(ID_PARAGRAPH_JUSTIFYLEFT, OnParagraphJustifyLeft)
	CMD_HANDLER(ID_PARAGRAPH_JUSTIFYCENTER, OnParagraphJustifyCenter)
	CMD_HANDLER(ID_PARAGRAPH_JUSTIFYRIGHT, OnParagraphJustifyRight)
	CMD_HANDLER(ID_PARAGRAPH_JUSTIFYALL, OnParagraphJustifyAll)
	CMD_UPDATE(ID_PARAGRAPH_ALIGNLEFT, OnParagraphAlignLeftUpdate)
	CMD_UPDATE(ID_PARAGRAPH_ALIGNCENTER, OnParagraphAlignCenterUpdate)
	CMD_UPDATE(ID_PARAGRAPH_ALIGNRIGHT, OnParagraphAlignRightUpdate)
	CMD_UPDATE(ID_PARAGRAPH_JUSTIFYLEFT, OnParagraphJustifyLeftUpdate)
	CMD_UPDATE(ID_PARAGRAPH_JUSTIFYCENTER, OnParagraphJustifyCenterUpdate)
	CMD_UPDATE(ID_PARAGRAPH_JUSTIFYRIGHT, OnParagraphJustifyRightUpdate)
	CMD_UPDATE(ID_PARAGRAPH_JUSTIFYALL, OnParagraphJustifyAllUpdate)

// Transparency

	CMD_HANDLER(ID_TRANSPARENCY_MAKEOPACITYMASK, OnTransparencyMakeOpacityMask)
	CMD_HANDLER(ID_TRANSPARENCY_RELEASEOPACITYMASK, OnTransparencyReleaseOpacityMask)
	CMD_UPDATE(ID_TRANSPARENCY_RELEASEOPACITYMASK, OnTransparencyReleaseOpacityMaskUpdate)
	CMD_HANDLER(ID_TRANSPARENCY_ENABLEOPACITYMASK, OnTransparencyEnableOpacityMask)
	CMD_UPDATE(ID_TRANSPARENCY_ENABLEOPACITYMASK, OnTransparencyEnableOpacityMaskUpdate)
	CMD_HANDLER(ID_TRANSPARENCY_LINKOPACITYMASK, OnTransparencyLinkOpacityMask)
	CMD_UPDATE(ID_TRANSPARENCY_LINKOPACITYMASK, OnTransparencyLinkOpacityMaskUpdate)

// Window
	CMD_HANDLER(ID_WINDOW_NEW, OnWindowNew)

// hmm...
	CMD_HANDLER(ID_PAGES_COPY, OnPagesCopy)

END_CMD_MAP()


#if 0
class COleClientItem
{
public:
	void GetObjectDescriptorData(LPPOINT lpOffset, LPSIZE lpSize, LPSTGMEDIUM lpStgMedium);
};

void COleClientItem::GetObjectDescriptorData(
	LPPOINT lpOffset, LPSIZE lpSize, LPSTGMEDIUM lpStgMedium)
{
	USES_CONVERSION;

	ASSERT_VALID(this);
	ASSERT(AfxIsValidAddress(lpStgMedium, sizeof(STGMEDIUM)));
	ASSERT(lpOffset == NULL ||
		AfxIsValidAddress(lpOffset, sizeof(CPoint), FALSE));

	POINTL pointT;
	if (lpOffset != NULL)
	{
		pointT.x = lpOffset->x;
		pointT.y = lpOffset->y;
		((CDC*)NULL)->DPtoHIMETRIC((SIZE*)&pointT);
	}
	else
	{
		pointT.x = 0;
		pointT.y = 0;
	}

	SIZE sizeT;
	if (lpSize != NULL)
	{
		sizeT.cx = lpSize->cx;
		sizeT.cy = lpSize->cy;
		((CDC*)NULL)->DPtoHIMETRIC(&sizeT);
	}
	else
	{
		sizeT.cx = 0;
		sizeT.cy = 0;
	}

	COleDocument* pDoc = GetDocument();

	// get the object descriptor for the IOleObject
	InterlockedIncrement(&m_dwRef);
	HGLOBAL hGlobal = _AfxOleGetObjectDescriptorData(
		m_lpObject, T2COLE(pDoc->GetPathName()), m_nDrawAspect, pointT, &sizeT);
	InterlockedDecrement(&m_dwRef);

	if (hGlobal == NULL)
		AfxThrowMemoryException();

	// setup the STGMEDIUM
	lpStgMedium->tymed = TYMED_HGLOBAL;
	lpStgMedium->hGlobal = hGlobal;
	lpStgMedium->pUnkForRelease = NULL;
}
#endif

#include "PDContentText.h"

LRESULT CPDDocumentView::OnTypeCreateOutlines(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComQIPtr<IPDContentText> contentText = m_pActiveObject->m_object;
	CPDContentText* pContentText = static_cast<CPDContentText*>(contentText.p);

	CComQIPtr<IPDObjectLayerGroup> activeLayerGroup;
	if (m_activeSpread)
		m_activeSpread->getLayerGroupFromLayer(m_activeLayer, &activeLayerGroup);

	CComPtr<IPDObjectGroup> group;
	m_document->createObjectGroup(GUID_NULL, &group);

	{
		HDC hDC = CreateCompatibleDC(NULL);

		{
			Gdiplus::Graphics graphics(hDC);

			CContentTextContext* pC = new CContentTextContext;
			pC->m_pContentText = pContentText;
			pC->m_pGraphics = &graphics;

			pContentText->m_pBox->BuildPaths(pC, m_document, group, NULL, hDC);

			delete pC;
		}

		DeleteDC(hDC);

	}

	activeLayerGroup->appendObject(group);

	CComQIPtr<IPDObjectLocatable> locatable = group;
	RectD bounds;
	locatable->get_bounds(&bounds);

	SelectPDObject(group, 0, TRUE);

	return 0;
}

#include "OleServerItem.h"

LRESULT CPDDocumentView::OnPagesCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CPDDocument* pDocument = (CPDDocument*)m_document;

		/*
	HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(GUID));

	if (hData)
	{
		GUID* p = (GUID*)GlobalLock(hData);
		*p = guid;
		GlobalUnlock(hData);

		CMyDataObject* dataObject = new CMyDataObject;

		STGMEDIUM	stg = {0};
		stg.tymed = TYMED_HGLOBAL;
		stg.hGlobal = hData;
		stg.pUnkForRelease = NULL;
		
		FORMATETC	etc = {0};
		etc.cfFormat = RegisterClipboardFormat(_T("PageDesigner-Pages"));
		etc.tymed = TYMED_HGLOBAL;
		etc.ptd = NULL;
		etc.dwAspect = DVASPECT_CONTENT;
		etc.lindex = -1;

		dataObject->SetData(&etc, &stg, TRUE);

		OleSetClipboard(dataObject);
	}
	*/

	pDocument->m_pOleServerItem = new COleServerItem;
	pDocument->m_pOleServerItem->m_spOleObject = pDocument;

	pDocument->m_pOleServerItem->CopyToClipboard();
//	dataObject->SetData(


//	CComQIPtr<IDataObject> dataObject = m_document;
	//OleSetClipboard(dataObject);

	return 0;
}

////

void CPDDocumentView::DefineSymbol(IPDSymbol* symbol)
{
	CArray<IPDObject*,IPDObject*> objects;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObject> object = m_targetObjects[i]->m_object;
		if (object)
		{
			objects.Add(object);
		}
	}

	if (objects.GetSize() > 0)
	{
		CComPtr<IPDObject> symbolObject;

		if (objects.GetSize() == 1)
		{
			CComPtr<IPDObject> object;
			objects[0]->clone(&object);
			if (object)
			{
				symbolObject = object;
			}
		}
		else
		{
			CComPtr<IPDObjectGroup> group;
			m_document->createObjectGroup(GUID_NULL, &group);
			if (group)
			{
				for (int i = 0; i < objects.GetSize(); i++)
				{
					CComPtr<IPDObject> object;
					objects[i]->clone(&object);
					if (object)
					{
						group->appendObject(object);
					}
				}

				symbolObject = group;
			}
		}

		if (symbolObject)
		{
			CComQIPtr<IPDObjectTransformable> transformable = symbolObject;

			RectD bounds;
			transformable->get_bounds(&bounds);

			transformable->Move(-bounds.X, -bounds.Y);

			symbol->put_symbolObject(symbolObject);
		}
	}
}

#include "SymbolOptionsDlg.h"

LRESULT CPDDocumentView::OnSymbolsNewSymbol(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int count = 0;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObject> object = m_targetObjects[i]->m_object;
		if (object)
		{
			count++;
		}
	}

	if (count > 0)
	{
		CComPtr<IPDSymbol> symbol;
		symbol.CoCreateInstance(CLSID_PDSymbol);
		if (symbol)
		{
			symbol->put_name(L"New Symbol");

			CSymbolOptionsDlg dlg;
			dlg.m_targetObjects.Add(symbol);

			if (dlg.DoModal(GetMainHwnd()) == IDOK)
			{
				DefineSymbol(symbol);

				m_document->appendSymbol(symbol);
			}
		}
	}

	return 0;
}

LRESULT CPDDocumentView::OnSymbolBreakLinktoSymbol(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	for (int i = m_targetObjects.GetSize()-1; i >= 0; i--)
	{
		CComQIPtr<IPDObjectSymbolInstance> symbolInstance = m_targetObjects[i]->m_object;
		if (symbolInstance)
		{
			CComQIPtr<IPDObjectTransformable> instanceTransformable = symbolInstance;

			CComPtr<IPDMatrix> mat;
			instanceTransformable->get_transformMatrix(&mat);

			CComPtr<IPDSymbol> symbol;
			symbolInstance->get_symbol(&symbol);

			CComPtr<IPDObject> symbolObject;
			symbol->get_symbolObject(&symbolObject);

			double x, y;
			symbolInstance->get_x(&x);
			symbolInstance->get_y(&y);

			CComPtr<IPDObject> object;
			symbolObject->clone(&object);
			if (object)
			{
				CComQIPtr<IPDObjectTransformable> transformable = object;
				transformable->Move(x, y);
				transformable->put_transformMatrix(mat);

				CComPtr<IPDObjectUnknown> parent;
				symbolInstance->get_parent(&parent);

				CComQIPtr<IPDObjectGroup> parentGroup = parent;
				parentGroup->insertObjectBeforeObject(object, symbolInstance);

				DeselectPDObject(symbolInstance);
				parent->removeObject(symbolInstance);
			}
		}
	}

	return 0;
}

void CPDDocumentView::OnObjectArrangeHigherUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObject> object = m_targetObjects[i]->m_object;
		if (object)
		{
			CComPtr<IPDObjectUnknown> parent;
			object->get_parent(&parent);

			CComQIPtr<IPDObjectGroup> parentGroup = parent;
			if (parentGroup)
			{
				CComPtr<IPDObject> nextSibling;
				object->get_nextSibling((IPDObjectUnknown**)&nextSibling);

				if (nextSibling)
				{
					bEnable = TRUE;
					break;
				}
			}
		}
	}

	pCmdUI->Enable(bEnable);
}

void CPDDocumentView::OnObjectArrangeLowerUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObject> object = m_targetObjects[i]->m_object;
		if (object)
		{
			CComPtr<IPDObjectUnknown> parent;
			object->get_parent(&parent);

			CComQIPtr<IPDObjectGroup> parentGroup = parent;
			if (parentGroup)
			{
				CComPtr<IPDObject> previousSibling;
				object->get_previousSibling((IPDObjectUnknown**)&previousSibling);

				if (previousSibling)
				{
					bEnable = TRUE;
					break;
				}
			}
		}
	}

	pCmdUI->Enable(bEnable);
}

LRESULT CPDDocumentView::OnObjectArrangeBringToFront(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObject> object = m_targetObjects[i]->m_object;
		if (object)
		{
			CComPtr<IPDObjectUnknown> parent;
			object->get_parent(&parent);

			CComQIPtr<IPDObjectGroup> parentGroup = parent;
			if (parentGroup)
			{
				CComPtr<IPDObject> nextSibling;
				object->get_nextSibling((IPDObjectUnknown**)&nextSibling);

				if (nextSibling)
				{
					parentGroup->appendObject(object);
				}
			}
		}
	}

	return 0;
}

LRESULT CPDDocumentView::OnObjectArrangeBringForward(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObject> object = m_targetObjects[i]->m_object;
		if (object)
		{
			CComPtr<IPDObjectUnknown> parent;
			object->get_parent(&parent);

			CComQIPtr<IPDObjectGroup> parentGroup = parent;
			if (parentGroup)
			{
				CComPtr<IPDObject> nextSibling;
				object->get_nextSibling((IPDObjectUnknown**)&nextSibling);

				if (nextSibling)
				{
					CComPtr<IPDObject> nextnextSibling;
					nextSibling->get_nextSibling((IPDObjectUnknown**)&nextnextSibling);

					if (nextnextSibling)
						parentGroup->insertObjectBeforeObject(object, nextnextSibling);
					else
						parentGroup->appendObject(object);
				}
			}
		}
	}

	return 0;
}

LRESULT CPDDocumentView::OnObjectArrangeSendBackward(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObject> object = m_targetObjects[i]->m_object;
		if (object)
		{
			CComPtr<IPDObjectUnknown> parent;
			object->get_parent(&parent);

			CComQIPtr<IPDObjectGroup> parentGroup = parent;
			if (parentGroup)
			{
				CComPtr<IPDObject> previousSibling;
				object->get_previousSibling((IPDObjectUnknown**)&previousSibling);

				if (previousSibling)
				{
					parentGroup->insertObjectBeforeObject(object, previousSibling);
				}
			}
		}
	}

	return 0;
}

LRESULT CPDDocumentView::OnObjectArrangeSendToBack(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObject> object = m_targetObjects[i]->m_object;
		if (object)
		{
			CComPtr<IPDObjectUnknown> parent;
			object->get_parent(&parent);

			CComQIPtr<IPDObjectGroup> parentGroup = parent;
			if (parentGroup)
			{
				CComPtr<IPDObject> firstChild;
				parentGroup->get_firstChild((IPDObjectUnknown**)&firstChild);

				if (firstChild)
				{
					parentGroup->insertObjectBeforeObject(object, firstChild);
				}
			}
		}
	}

	return 0;
}

#include "PatternSwatchOptionsDlg.h"

LRESULT CPDDocumentView::OnEditDefinePattern(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	BOOL bAny = FALSE;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObject> object = m_targetObjects[i]->m_object;
		if (object)
		{
			bAny = TRUE;
			break;
		}
	}

	if (bAny)
	{
		CComPtr<IPDSwatches> swatches;
		m_document->get_swatches(&swatches);

		CComPtr<IPDSwatchPattern> swatchPattern;
		swatches->createSwatchPattern(&swatchPattern);
		if (swatchPattern)
		{
			swatchPattern->put_name(L"New Pattern");

			CPatternSwatchOptionsDlg dlg;
			dlg.m_targetObjects.Add(swatchPattern);

			if (dlg.DoModal(GetMainHwnd()) == IDOK)
			{
				// Serialize
				{
					CComPtr<IArchive> ar;
					ar.CoCreateInstance(CLSID_Archive);

					CComPtr<IArchiveElement> node;
					if (SUCCEEDED(ar->Open(L"c:\\pattern", 1, L"pdgroup", &node)))
					{
						for (int i = 0; i < m_targetObjects.GetSize(); i++)
						{
							CComQIPtr<IPDObject> object = m_targetObjects[i]->m_object;
							if (object)
							{
								node->putObject(object);
							}
						}
					}
				}

				CComPtr<IPDObjectGroup> objectGroup;
				m_document->createObjectGroup(GUID_NULL, &objectGroup);
				// Deserialize
				{
					CComPtr<IArchive> ar;
					ar.CoCreateInstance(CLSID_Archive);

					CComPtr<IArchiveElement> node;
					if (SUCCEEDED(ar->Open(L"c:\\pattern", 2, L"pdgroup", &node)))
					{
						CComObject<CObjectMap>* pMap;
						CComObject<CObjectMap>::CreateInstance(&pMap);
						if (pMap)
						{
							if (SUCCEEDED(node->deserializeObjectMap(pMap, NULL)))
							{
								for (int i = 0; i < pMap->m_items.GetSize(); i++)
								{
									IPDObject* object = static_cast<IPDObject*>(pMap->m_items[i]);
									objectGroup->appendObject(object);
								}
							}
							pMap->Release();
						}
					}
				}


				swatchPattern->put_objectGroup(objectGroup);

				swatches->appendSwatch(swatchPattern);
			}
		}
	}

	return 0;
}

void CPDDocumentView::OnEditDefinePatternUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObject> object = m_targetObjects[i]->m_object;
		if (object)
		{
			bEnable = TRUE;
			break;
		}
	}

	pCmdUI->Enable(bEnable);
}

LRESULT CPDDocumentView::OnViewTransparencyGrid(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_bViewTransparencyGrid = !m_bViewTransparencyGrid;

	m_bInvalid = true;
	InvalidateRect(&m_areaRect);

	return 0;
}

void CPDDocumentView::OnViewTransparencyGridUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_bViewTransparencyGrid);
}

LRESULT CPDDocumentView::OnTransparencyMakeOpacityMask(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_targetObjects.GetSize() == 2)
	{
		CComQIPtr<IPDObjectWithOpacityMask> target = m_targetObjects[0]->m_object;
		CComQIPtr<IPDObject> maskobject = m_targetObjects[1]->m_object;
		if (target && maskobject)
		{
			CComPtr<IPDObjectGroup> opacityMaskGroup;

			GUID groupGuid;
			CoCreateGuid(&groupGuid);
			m_document->createObjectGroup(groupGuid, &opacityMaskGroup);

			opacityMaskGroup->appendObject(maskobject);

			target->put_opacityMaskGroup(opacityMaskGroup);

			DeselectAll();

			m_bInvalid = true;
			Invalidate();
		}
	}

	return 0;
}

LRESULT CPDDocumentView::OnTransparencyReleaseOpacityMask(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObject> object = m_targetObjects[i]->m_object;
		if (object)
		{
			CComPtr<IPDObjectGroup> parentGroup;
			object->get_parent((IPDObjectUnknown**)&parentGroup);

			CComPtr<IPDObject> nextSibling;
			object->get_nextSibling((IPDObjectUnknown**)&nextSibling);

			CComQIPtr<IPDObjectWithOpacityMask> withOpacityMask = object;
			if (withOpacityMask)
			{
				CComPtr<IPDObjectGroup> opacityMaskGroup;
				withOpacityMask->get_opacityMaskGroup(&opacityMaskGroup);

				if (opacityMaskGroup)
				{
					CComPtr<IObjectMap> children;
					opacityMaskGroup->get_children(&children);

					long nchildren;
					children->get_length(&nchildren);

					for (long i = 0; i < nchildren; i++)
					{
						CComPtr<IPDObject> object;
						children->item(i, (IUnknown**)&object);

						if (nextSibling)
							parentGroup->insertObjectBeforeObject(object, nextSibling);
						else
							parentGroup->appendObject(object);
					}
				}

				withOpacityMask->put_opacityMaskGroup(NULL);
			}
		}
	}

	return 0;
}

void CPDDocumentView::OnTransparencyReleaseOpacityMaskUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObjectWithOpacityMask> withOpacityMask = m_targetObjects[i]->m_object;
		if (withOpacityMask)
		{
			CComPtr<IPDObjectGroup> opacityMaskGroup;
			withOpacityMask->get_opacityMaskGroup(&opacityMaskGroup);

			if (opacityMaskGroup)
			{
				bEnable = TRUE;
				break;
			}
		}
	}

	pCmdUI->Enable(bEnable);
}

LRESULT CPDDocumentView::OnTransparencyEnableOpacityMask(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int i;

	VARIANT_BOOL enabled = -2;

	for (i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObjectWithOpacityMask> withOpacityMask = m_targetObjects[i]->m_object;
		if (withOpacityMask)
		{
			VARIANT_BOOL enabled2;
			withOpacityMask->get_opacityMaskEnabled(&enabled2);

			if (i == 0)
			{
				enabled = enabled2;
			}
			else if (enabled != enabled2)
			{
				enabled = -2;
				break;
			}
		}
	}

	for (i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObjectWithOpacityMask> withOpacityMask = m_targetObjects[i]->m_object;
		if (withOpacityMask)
		{
			withOpacityMask->put_opacityMaskEnabled(enabled == VARIANT_FALSE? VARIANT_TRUE: VARIANT_FALSE);
		}
	}

	return 0;
}

void CPDDocumentView::OnTransparencyEnableOpacityMaskUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	int i;

	BOOL bEnable = FALSE;
	VARIANT_BOOL enabled = -2;

	for (i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObjectWithOpacityMask> withOpacityMask = m_targetObjects[i]->m_object;
		if (withOpacityMask)
		{
			CComPtr<IPDObjectGroup> opacityMaskGroup;
			withOpacityMask->get_opacityMaskGroup(&opacityMaskGroup);
			if (opacityMaskGroup)
			{
				bEnable = TRUE;

				VARIANT_BOOL enabled2;
				withOpacityMask->get_opacityMaskEnabled(&enabled2);

				if (i == 0)
				{
					enabled = enabled2;
				}
				else if (enabled != enabled2)
				{
					enabled = -2;
					break;
				}
			}
		}
	}

	pCmdUI->Enable(bEnable);
	pCmdUI->SetCheck(bEnable && (enabled != VARIANT_FALSE));
}

LRESULT CPDDocumentView::OnTransparencyLinkOpacityMask(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int i;

	VARIANT_BOOL linked = -2;

	for (i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObjectWithOpacityMask> withOpacityMask = m_targetObjects[i]->m_object;
		if (withOpacityMask)
		{
			VARIANT_BOOL linked2;
			withOpacityMask->get_opacityMaskLinked(&linked2);

			if (i == 0)
			{
				linked = linked2;
			}
			else if (linked != linked2)
			{
				linked = -2;
				break;
			}
		}
	}

	for (i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObjectWithOpacityMask> withOpacityMask = m_targetObjects[i]->m_object;
		if (withOpacityMask)
		{
			withOpacityMask->put_opacityMaskLinked(linked == VARIANT_FALSE? VARIANT_TRUE: VARIANT_FALSE);
		}
	}

	return 0;
}

void CPDDocumentView::OnTransparencyLinkOpacityMaskUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	int i;

	BOOL bEnable = FALSE;
	VARIANT_BOOL linked = -2;

	for (i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObjectWithOpacityMask> withOpacityMask = m_targetObjects[i]->m_object;
		if (withOpacityMask)
		{
			CComPtr<IPDObjectGroup> opacityMaskGroup;
			withOpacityMask->get_opacityMaskGroup(&opacityMaskGroup);
			if (opacityMaskGroup)
			{
				bEnable = TRUE;

				VARIANT_BOOL linked2;
				withOpacityMask->get_opacityMaskLinked(&linked2);

				if (i == 0)
				{
					linked = linked2;
				}
				else if (linked != linked2)
				{
					linked = -2;
					break;
				}
			}
		}
	}

	pCmdUI->Enable(bEnable);
	pCmdUI->SetCheck(bEnable && (linked != VARIANT_FALSE));
}

#include "RasterizeDlg.h"

LRESULT CPDDocumentView::OnObjectRasterize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	RectD objectsBoundingBox;
	CalculateObjectsExpandedBoundingBox(&objectsBoundingBox);

	if (m_pActiveObject && objectsBoundingBox.Width > 0 && objectsBoundingBox.Height > 0)
	{
		static long ppi = 72;
		static Gdiplus::Color bgColor = Gdiplus::Color(0, 0, 0, 0);

		CComQIPtr<IPDDocumentSettings> documentSettings = m_document;

		CRasterizeDlg dlg;
		dlg.m_ppi = ppi;
		dlg.m_bgColor = bgColor;
		documentSettings->get_rasterResolution(&dlg.m_documentppi);

		if (dlg.DoModal(GetMainHwnd()) == IDOK)
		{
			CComPtr<IPDObjectGroup> parent;
			m_pActiveObject->m_object->get_parent((IPDObjectUnknown**)&parent);

			ppi = dlg.m_ppi;
			bgColor = dlg.m_bgColor;

			HDC hDC = ::GetDC(NULL);
			long inchesPerPixelX = GetDeviceCaps(hDC, LOGPIXELSX);
			long inchesPerPixelY = GetDeviceCaps(hDC, LOGPIXELSY);
			::ReleaseDC(NULL, hDC);

			int pixelWidth = (int)ceil(objectsBoundingBox.Width*ppi/inchesPerPixelX);
			int pixelHeight = (int)ceil(objectsBoundingBox.Height*ppi/inchesPerPixelY);

			CComPtr<IPDContentGraphic> contentGraphic;
			m_document->createContentGraphic(&contentGraphic);

			double scaleX = (double)inchesPerPixelX/ppi;
			double scaleY = (double)inchesPerPixelY/ppi;

			CComPtr<IPDRenderer> renderer;
			renderer.CoCreateInstance(CLSID_PDRenderer);
			if (renderer)
			{
				CComPtr<IPDImage> image;
				m_document->createImage(pixelWidth, pixelHeight, PixelFormat32bppARGB, &image);
				if (image)
				{
					Gdiplus::Bitmap* pBitmap;
					image->get_privateImage((DWORD*)&pBitmap);

					Gdiplus::Graphics graphics(pBitmap);
					graphics.Clear(bgColor);

					renderer->put_targetHDC((HDC)&graphics);
					renderer->put_magnify(1/scaleX);

					graphics.ScaleTransform(1/scaleX, 1/scaleY);
					graphics.TranslateTransform(-objectsBoundingBox.X, -objectsBoundingBox.Y);

					for (int i = 0; i < m_targetObjects.GetSize(); i++)
					{
						CPDObjectSelected* pObject = m_targetObjects[i];
						CComQIPtr<IPDObject> object = pObject->m_object;
						if (object)
						{
							renderer->RenderObject(object);
						}
					}

					contentGraphic->put_image(image);

					contentGraphic->setxy(objectsBoundingBox.X, objectsBoundingBox.Y);

					CComPtr<IPDMatrix> mat0;
					mat0.CoCreateInstance(CLSID_PDMatrix);

					CComPtr<IPDMatrix> mat1;
					mat0->translate(-objectsBoundingBox.X, -objectsBoundingBox.Y, &mat1);

					CComPtr<IPDMatrix> mat2;
					mat1->scaleNonUniform(scaleX, scaleY, &mat2);

					CComPtr<IPDMatrix> mat;
					mat2->translate(objectsBoundingBox.X, objectsBoundingBox.Y, &mat);

					CComQIPtr<IPDObjectTransformable> graphicTransformable = contentGraphic;
					graphicTransformable->put_transformMatrix(mat);

					// Remove the objects
					for (i = m_targetObjects.GetSize()-1; i >= 0; i--)
					{
						CPDObjectSelected* pObject = m_targetObjects[i];
						CComQIPtr<IPDObject> object = pObject->m_object;
						if (object)
						{
							DeselectPDObject(object);

							CComPtr<IPDObjectGroup> parent;
							object->get_parent((IPDObjectUnknown**)&parent);
							parent->removeObject(object);
						}
					}

				// Insert the graphic object
					parent->appendObject(contentGraphic);

					SelectPDObject(contentGraphic, 0, TRUE);
				//	m_document->appendImage(image);
				}
			}
		}
	}

	return 0;
}

void CPDDocumentView::OnObjectRasterizeUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	if (m_pActiveObject && m_objectsBoundingBox.Width > 0 && m_objectsBoundingBox.Height > 0)
	{
		bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}

IPDTextFont* CPDDocumentView::GetActiveStoryRangeTextFont()
{
	if (m_range && m_pActiveObject)
	{
		CComQIPtr<IPDObjectText> text = m_pActiveObject->m_object;
		if (text)
		{
			CComPtr<IPDStory> story;
			text->get_story(&story);

			CComPtr<IPDTextFont> textFont;
			story->GetTextFont(m_range, &textFont);
			return textFont.Detach();
		}
	}

	return NULL;
}

IPDTextPara* CPDDocumentView::GetActiveStoryRangeTextPara()
{
	if (m_range && m_pActiveObject)
	{
		CComQIPtr<IPDObjectText> text = m_pActiveObject->m_object;
		if (text)
		{
			CComPtr<IPDStory> story;
			text->get_story(&story);

			CComPtr<IPDTextPara> textPara;
			story->GetTextPara(m_range, &textPara);
			return textPara.Detach();
		}
	}

	return NULL;
}

LRESULT CPDDocumentView::OnCharacterFontface(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (hWndCtl && wNotifyCode == CBN_SELCHANGE)
	{
		int index = ::SendMessage(hWndCtl, CB_GETCURSEL, 0, 0);
		if (index >= 0)
		{
			TCHAR fontname[512];
			::SendMessage(hWndCtl, CB_GETLBTEXT, index, (LPARAM)fontname);

			if (m_range && m_pActiveObject)
			{
				CComQIPtr<IPDObjectText> text = m_pActiveObject->m_object;
				if (text)
				{
					CComPtr<IPDStory> story;
					text->get_story(&story);

					CComPtr<IPDTextFont> textFont;
					story->GetTextFont(m_range, &textFont);

					textFont->SetName(_bstr_t(fontname));

					story->SetTextFont(m_range, textFont);

					/*
					{
						CComPtr<IDOMDocument> textdocument;
						story->get_textDocument(&textdocument);

						BSTR xml;
						textdocument->saveXML(NULL, &xml);
						MessageBox(_bstr_t(xml), "", MB_OK);
						SysFreeString(xml);
					}
					*/
				}
			}
		}
	}

	return 0;
}

void CPDDocumentView::OnCharacterFontfaceUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	HWND hWnd;
	pCmdUI->get_hwndControl(&hWnd);
	if (hWnd)
	{
		CComPtr<IPDTextFont> textFont = GetActiveStoryRangeTextFont();
		if (textFont)
		{
			BSTR bfontface;
			textFont->GetName(&bfontface);
			_bstr_t fontface = _bstr_t(bfontface, false);

			if (fontface.length())
			{
				TCHAR old[64];
				::GetWindowText(hWnd, old, sizeof(old));

				if (wcscmp(fontface, _bstr_t(old))) ::SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)(char*)fontface);
				return;
			}
		}

		::SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)"");
	}
}

LRESULT CPDDocumentView::OnCharacterFontsize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (hWndCtl &&
		(wNotifyCode == CBN_KILLFOCUS) ||
		(wNotifyCode == CBN_CLOSEUP))
	{
		BOOL bTrans;
		double sizePixel = GetWindowTextValue(hWndCtl, &bTrans);
		if (bTrans)
		{
			double size = ConvertUserUnitToSpecifiedValue(sizePixel, UNIT_PT);

			if (m_range && m_pActiveObject)
			{
				CComQIPtr<IPDObjectText> text = m_pActiveObject->m_object;
				if (text)
				{
					CComPtr<IPDStory> story;
					text->get_story(&story);

					CComPtr<IPDTextFont> textFont;
					story->GetTextFont(m_range, &textFont);

					textFont->SetSize(size);

					story->SetTextFont(m_range, textFont);
				}
			}
		}
	}

	return 0;
}

void CPDDocumentView::OnCharacterFontsizeUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	HWND hWnd;
	pCmdUI->get_hwndControl(&hWnd);
	if (hWnd)
	{
		HWND comboEdit = ::ChildWindowFromPoint(hWnd, CPoint(4,4));
		ATLASSERT(comboEdit);

		if (::GetFocus() != comboEdit)
		{
			CComPtr<IPDTextFont> textFont = GetActiveStoryRangeTextFont();
			if (textFont)
			{
				float fontsize;
				textFont->GetSize(&fontsize);

				if (fontsize != tomUndefined)
				{
					TCHAR buf[64];
					sprintf(buf, _T("%g pt"), fontsize);

					TCHAR old[64];
					::GetWindowText(hWnd, old, sizeof(old));

					if (_tcscmp(buf, old)) ::SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)buf);
					return;
				}
			}

			::SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)"");
		}
	}
}

void CPDDocumentView::OnCharacterLineheightUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	HWND hWnd;
	pCmdUI->get_hwndControl(&hWnd);
	if (hWnd)
	{
		CComPtr<IPDTextFont> textFont = GetActiveStoryRangeTextFont();
		if (textFont)
		{
			float lineheight;
			textFont->GetLineHeight(&lineheight);

			if (lineheight != tomUndefined)
			{
				TCHAR buf[64];
				sprintf(buf, _T("(%g pt)"), lineheight);

				TCHAR old[64];
				::GetWindowText(hWnd, old, sizeof(old));

				if (_tcscmp(buf, old)) ::SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)buf);
				return;
			}
		}

		::SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)"");
	}
}

LRESULT CPDDocumentView::OnCharacterBold(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_range && m_pActiveObject)
	{
		CComQIPtr<IPDObjectText> text = m_pActiveObject->m_object;
		if (text)
		{
			CComPtr<IPDStory> story;
			text->get_story(&story);

			CComPtr<IPDTextFont> textFont;
			story->GetTextFont(m_range, &textFont);
			textFont->SetName(L"Times New Roman");

			story->SetTextFont(m_range, textFont);
		}
	}

	return 0;
}

#include "MarginsAndColumnsDlg.h"

LRESULT CPDDocumentView::OnLayoutMarginsAndColumns(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CMarginsAndColumnsDlg dlg;

	for (int i = 0; i < m_selectedPages.GetSize(); i++)
	{
		dlg.m_targetObjects.Add(m_selectedPages[i]);
	}

	if (dlg.DoModal(GetMainHwnd()) == IDOK)
	{
		InvalidateRect(&m_areaRect);	// TODO remove
	}

	return 0;
}

#include "CreateGuidesDlg.h"

LRESULT CPDDocumentView::OnLayoutCreateGuides(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComQIPtr<IPDObjectLayerGroup> activeLayerGroup;
	if (m_activeSpread)
		m_activeSpread->getLayerGroupFromLayer(m_activeLayer, &activeLayerGroup);

	if (activeLayerGroup)
	{
		CCreateGuidesDlg dlg;

		dlg.m_rowsNumber = 0;
		dlg.m_rowsGutter = 10;
		dlg.m_colsNumber = 0;
		dlg.m_colsGutter = 10;

		dlg.m_fitGuidesTo = 0;
		dlg.m_removeExistingRulerGuides = FALSE;

		if (dlg.DoModal(GetMainHwnd()) == IDOK)
		{
			double pageWidth;
			double pageHeight;
			m_document->get_pageWidth(&pageWidth);
			m_document->get_pageHeight(&pageHeight);

			CComPtr<IPDGuides> guides;
			activeLayerGroup->get_guides(&guides);

			if (dlg.m_removeExistingRulerGuides)
			{
				guides->deleteAllGuides();
			}

			CComPtr<IObjectMap> pages;
			m_activeSpread->get_pages(&pages);

			long npages;
			pages->get_length(&npages);

			{
				double x = 0;

				for (int npage = 0; npage < npages; npage++)
				{
					CComPtr<IPDPage> page;
					pages->item(npage, (IUnknown**)&page);

					double marginTop;
					double marginBottom;
					double marginLeft;
					double marginRight;

					if (dlg.m_fitGuidesTo == 0)
					{
						page->get_marginTop(&marginTop);
						page->get_marginBottom(&marginBottom);
						page->get_marginLeft(&marginLeft);
						page->get_marginRight(&marginRight);
					}
					else
					{
						marginTop = 0;
						marginBottom = 0;
						marginLeft = 0;
						marginRight = 0;
					}

				// Rows
					{
						double y2 = marginTop;

						double innerHeight = pageHeight-marginTop-marginBottom;
						double rowHeight = (innerHeight-(dlg.m_rowsNumber-1)*dlg.m_rowsGutter)/dlg.m_rowsNumber;

						for (int i = 0; i < dlg.m_rowsNumber; i++)
						{
							{
								CComPtr<IPDGuide> guide;
								guides->createGuide(0, &guide);
								guide->put_position(y2);
								guide->put_pageIndex(npage);
								guides->appendGuide(guide);
							}

							y2 += rowHeight;

							{
								CComPtr<IPDGuide> guide;
								guides->createGuide(0, &guide);
								guide->put_position(y2);
								guide->put_pageIndex(npage);
								guides->appendGuide(guide);
							}

							y2 += dlg.m_rowsGutter;
						}
					}

				// Columns
					{
						double x2 = x + marginLeft;

						double innerWidth = pageWidth-marginLeft-marginRight;
						double columnWidth = (innerWidth-(dlg.m_colsNumber-1)*dlg.m_colsGutter)/dlg.m_colsNumber;

						for (int i = 0; i < dlg.m_colsNumber; i++)
						{
							{
								CComPtr<IPDGuide> guide;
								guides->createGuide(1, &guide);
								guide->put_position(x2);
								guides->appendGuide(guide);
							}

							x2 += columnWidth;

							{
								CComPtr<IPDGuide> guide;
								guides->createGuide(1, &guide);
								guide->put_position(x2);
								guides->appendGuide(guide);
							}

							x2 += dlg.m_colsGutter;
						}
					}

					x += pageWidth;
				}
			}
		}
	}
	else
	{
		::MessageBox(GetMainHwnd(), "You must activate a spread and a layer", "PageDesigner", MB_OK);
	}

	return 0;
}

#include "BasicCharacterDlg.h"

#include "ParagraphIndentsDlg.h"
#include "JustificationDlg.h"
#include "DropCapsDlg.h"

LRESULT CPDDocumentView::OnCharacter(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_pActiveObject)
	{
		CComQIPtr<IPDObjectText> contenttext;

		CComQIPtr<IPDObjectFrame> frame = m_pActiveObject->m_object;
		if (frame)
		{
			CComPtr<IPDObject> content;
			frame->get_content(&content);
			contenttext = content;
		}
		else
			contenttext = m_pActiveObject->m_object;

		if (contenttext)
		{
			if (m_range)
			{
				CComPtr<ILDOMRange> range;
				m_range->GetDOMRange(&range);

				CComPtr<ILDOMNode> startContainer;
				range->get_startContainer(&startContainer);

				if (startContainer)
				{
					CPropertySheet* sheet = new CPropertySheet("Character", 0, GetMainHwnd());

					CBasicCharacterDlg basic;

					sheet->AddPage(basic);

					//indents.m_targetObjects.Add(p);
					//dropcaps.m_targetObjects.Add(p);

					sheet->DoModal();

					InvalidateRect(&m_areaRect);	// TODO remove
				}
			}
		}
	}

	return 0;
}

LRESULT CPDDocumentView::OnParagraph(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<IPDTextPara> textPara = GetActiveStoryRangeTextPara();
	if (textPara)
	{
		CPropertySheet* sheet = new CPropertySheet("Paragraph", 0, GetMainHwnd());

		CParagraphIndentsDlg indents;
		CJustificationDlg justification;
		CDropCapsDlg	dropcaps;

		sheet->AddPage(indents);
		sheet->AddPage(justification);
		sheet->AddPage(dropcaps);

		indents.m_para = textPara;
		dropcaps.m_para = textPara;

		sheet->DoModal();

		InvalidateRect(&m_areaRect);	// TODO remove
	}

	return 0;
}

void CPDDocumentView::SetParagraphAlign(int align)
{
	CComPtr<IPDTextPara> textPara = GetActiveStoryRangeTextPara();
	if (textPara)
	{
		textPara->SetAlignment(align);
		//InvalidateRect(&m_areaRect);	// TODO remove
	}
}

LRESULT CPDDocumentView::OnParagraphAlignLeft(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetParagraphAlign(PARAALIGN_LEFT);
	return 0;
}

LRESULT CPDDocumentView::OnParagraphAlignCenter(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetParagraphAlign(PARAALIGN_CENTER);
	return 0;
}

LRESULT CPDDocumentView::OnParagraphAlignRight(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetParagraphAlign(PARAALIGN_RIGHT);
	return 0;
}

LRESULT CPDDocumentView::OnParagraphJustifyLeft(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetParagraphAlign(PARAALIGN_JUSTIFYLEFT);
	return 0;
}

LRESULT CPDDocumentView::OnParagraphJustifyCenter(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetParagraphAlign(PARAALIGN_JUSTIFYCENTER);
	return 0;
}

LRESULT CPDDocumentView::OnParagraphJustifyRight(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetParagraphAlign(PARAALIGN_JUSTIFYRIGHT);
	return 0;
}

LRESULT CPDDocumentView::OnParagraphJustifyAll(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetParagraphAlign(PARAALIGN_JUSTIFYALL);
	return 0;
}

void CPDDocumentView::UpdateParagraphAlign(long align, IUICmdUpdate* pCmdUI)
{
	BOOL bCheck = FALSE;

	CComPtr<IPDTextPara> textPara = GetActiveStoryRangeTextPara();
	if (textPara)
	{
		long alignment;
		textPara->GetAlignment(&alignment);

		if (alignment == align) bCheck = TRUE;
	}

	pCmdUI->SetCheck(bCheck);
}

void CPDDocumentView::OnParagraphAlignLeftUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	UpdateParagraphAlign(PARAALIGN_LEFT, pCmdUI);
}

void CPDDocumentView::OnParagraphAlignCenterUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	UpdateParagraphAlign(PARAALIGN_CENTER, pCmdUI);
}

void CPDDocumentView::OnParagraphAlignRightUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	UpdateParagraphAlign(PARAALIGN_RIGHT, pCmdUI);
}

void CPDDocumentView::OnParagraphJustifyLeftUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	UpdateParagraphAlign(PARAALIGN_JUSTIFYLEFT, pCmdUI);
}

void CPDDocumentView::OnParagraphJustifyCenterUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	UpdateParagraphAlign(PARAALIGN_JUSTIFYCENTER, pCmdUI);
}

void CPDDocumentView::OnParagraphJustifyRightUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	UpdateParagraphAlign(PARAALIGN_JUSTIFYRIGHT, pCmdUI);
}

void CPDDocumentView::OnParagraphJustifyAllUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	UpdateParagraphAlign(PARAALIGN_JUSTIFYALL, pCmdUI);
}

LRESULT CPDDocumentView::OnEditCut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CopySelectionToClipboard();
	ClearSelection();

	return 0;
}

LRESULT CPDDocumentView::OnEditCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CopySelectionToClipboard();
	return 0;
}

LRESULT CPDDocumentView::OnEditPaste(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	PasteObjectsFromClipboard();
	return 0;
}

#include "RdEMF.h"

class IRTFReceiver
{
public:
	virtual HRESULT __stdcall EmitCharacters(BSTR bstr) = 0;
};

class CRTFParser
{
protected:
	IRTFReceiver* m_target;

	char* m_data;
	int m_pos;
	int m_len;

	class CRTFFont
	{
	public:
		int m_fn;
		CUString m_name;
	};

	long m_version;
	CUString m_charset;
	CArray<CRTFFont*,CRTFFont*> m_fonts;
	CArray<RGBTRIPLE, RGBTRIPLE> m_colorTable;

	int getc()
	{
		if (m_pos < m_len)
		{
			return m_data[m_pos++];
		}
		else
			return EOF;
	}

	void eatchar(int c)
	{
		int n = getc();
		if (n != c)
		{
			WCHAR msg[256];
			swprintf(msg, L"Expected character '%c' at position %d", c, m_pos-1);
			throw msg;
		}
	}

	void ungetc()
	{
		if (m_pos > 0)
			m_pos--;
		else
			ATLASSERT(0);
	}

	void skipblanks()
	{
		while (!eof())
		{
			int c = getc();
			if (c != '\n' && c != '\r'/* && c != ' '*/)
			{
				ungetc();
				break;
			}
		}
	}

	void skipspaces()
	{
		while (!eof())
		{
			int c = getc();
			if (c != '\n' && c != '\r' && c != ' ')
			{
				ungetc();
				break;
			}
		}
	}

	bool eof()
	{
		if (m_pos < m_len)
			return false;
		else
			return true;
	}

	CUString GetKeywordString()
	{
		int c = getc();
		if (!isalpha(c))// a control symbol; no delimiter.
		{
			return CUString(c);
		}
		else
		{
			ungetc();

			CUString keyword;
			while (!eof())
			{
				int c = getc();
				if (!isalpha(c))
				{
					ungetc();
					break;
				}

				keyword += CUString(c);
			}

			return keyword;
		}
	}

	long GetValue()
	{
		long lParam = 0;

		bool fNeg = false;
		int c = getc();
		if (c == '-')
		{
			fNeg  = true;
			c = getc();
		}

		ungetc();

		if (isdigit(c))
		{
			CUString sval;

			while (!eof())
			{
				int c = getc();
				if (!isdigit(c))
				{
					ungetc();
					break;
				}

				sval += CUString(c);
			}

			lParam = atol(sval);
			if (fNeg) lParam = -lParam;
		}

		return lParam;
	}

	void parsecolortbl()
	{
		int n = 0;
		while (!eof())
		{
			int c = getc();

			if (c == '}')
			{
				ungetc();
				break;
			}

			RGBTRIPLE rgb;
			rgb.rgbtRed = 0;
			rgb.rgbtGreen = 0;
			rgb.rgbtBlue = 0;

			while (!eof())
			{
				int c = getc();
				if (c == ';')
				{
					ungetc();
					break;
				}

				if (c == '\\')
				{
					CUString keyword = GetKeywordString();
					long value = GetValue();

					if (keyword == "red")
						rgb.rgbtRed = value;
					else if (keyword == "green")
						rgb.rgbtGreen = value;
					else if (keyword == "blue")
						rgb.rgbtBlue = value;
				}
			}

			eatchar(';');

			m_colorTable.Add(rgb);
		}
	}

	void parsefontinfo()
	{
		CRTFFont* pFont = new CRTFFont;

		try
		{
			while (!eof())
			{
				int c = getc();

				if (c == ';')
				{
					ungetc();
					break;
				}
				else if (c == '\\')
				{
					CUString keyword = GetKeywordString();
					long value = GetValue();

					if (keyword == "f")
					{
						pFont->m_fn = value;
					}
				}
				else if (c == '{')
				{
					parsegroup();
					eatchar('}');
				}
				else
				{
					pFont->m_name += CUString(c);
				}
			}

			eatchar(';');
		}
		catch(WCHAR* msg)
		{
			delete pFont;

			throw msg;
		}

		m_fonts.Add(pFont);
	}

	void parsefonttbl()
	{
		skipblanks();

		int c = getc();
		ungetc();

		if (c == '{')
		{
			while (!eof())
			{
				int c = getc();

				if (c == '}')
				{
					ungetc();
					break;
				}
				else if (c == '{')
				{
					parsefontinfo();
					eatchar('}');
				}
			}

			eatchar('}');
		}
		else
		{
			parsefontinfo();
		}
	}

	void parsegroup()
	{
		skipblanks();

		while (!eof())
		{
			int c = getc();
			if (c == '}')
			{
				ungetc();
				break;
			}

			if (c == '{')
			{
				parsegroup();
				eatchar('}');
			}
			else if (c == '\\')	// keyword
			{
				CUString keyword = GetKeywordString();
				long lParam = GetValue();

				if (keyword == "fonttbl")
				{
					parsefonttbl();
				}
				else if (keyword == "colortbl")
				{
					parsecolortbl();
				}

				ATLTRACE("keyword: %s %d\n", keyword, lParam);
			}
			else
			{
				ATLTRACE("%c", c);
			}
		}

		skipblanks();
	}

	void parsertf()
	{
		eatchar('\\');
		CUString rtf = GetKeywordString();
		if (rtf != "rtf") throw L"Not rtf";

		m_version = GetValue();
		if (m_version != 1) throw L"Unsupported rtf version";

		skipspaces();

		eatchar('\\');
		m_charset = GetKeywordString();
		if (m_charset != "ansi" &&
			m_charset != "mac" &&
			m_charset != "pc" &&
			m_charset != "pca")
		{
			throw L"Unknown charset";
		}

		while (!eof())
		{
			int c = getc();

			if (c == '}')
			{
				ungetc();
				break;
			}

			if (c == '{')
			{
				parsegroup();
				eatchar('}');
			}
			else if (c == '\\')
			{
				CUString keyword = GetKeywordString();
				long value = GetValue();
			}
		}
	}

public:

	HRESULT ParseString(IRTFReceiver* target, char* data)
	{
		m_target = target;

		m_data = data;
		m_len = strlen(m_data);
		m_pos = 0;

		try
		{
			eatchar('{');

			parsertf();

		//	parsegroup();

			eatchar('}');

			return S_OK;
		}
		catch (WCHAR* msg)
		{
			ATLTRACE("\nRTF Error: %S\n", msg);
			return E_FAIL;
		}
	}
};

class CRTFLoader :
	public IRTFReceiver
{
public:
	CComPtr<ILDOMDocument> m_document;
	CComPtr<ILDOMDocumentFragment> m_fragment;
	CComPtr<ILDOMText> m_text;

	STDMETHODIMP EmitCharacters(BSTR bstr)
	{
		if (m_text == NULL)
		{
			m_document->createTextNode(bstr, &m_text);
			m_fragment->appendChild(m_text, NULL);
		}
		else
		{
			m_text->appendData(bstr);
		}
		return S_OK;
	}

	HRESULT Load(ILDOMDocument* document, ILDOMDocumentFragment *fragment, char* data)
	{
		HRESULT hr = E_FAIL;

		m_document = document;
		m_fragment = fragment;

		CRTFParser* pRTF = new CRTFParser;
		if (pRTF)
		{
			hr = pRTF->ParseString(this, data);
			delete pRTF;
		}

		return hr;
	}
};

LRESULT CPDDocumentView::OnEditPasteSpecial(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	OLEUIPASTESPECIAL ps = {0};
	ps.cbStruct = sizeof(ps);
	ps.dwFlags = 0;
	ps.hWndOwner = GetMainHwnd();
	ps.hInstance = NULL;//_Module.m_hInst;//GetInstance();

	OLEUIPASTEENTRY pasteEntries[8] = {0};
	ps.arrPasteEntries = pasteEntries;

	ps.cPasteEntries = 0;

	{
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.cfFormat = _clipboardFormats.cfRichTextFormat;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.dwAspect = DVASPECT_CONTENT;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.lindex = -1;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.tymed = TYMED_HGLOBAL;
		ps.arrPasteEntries[ps.cPasteEntries].lpstrFormatName = "Rich Text Format";
		ps.arrPasteEntries[ps.cPasteEntries].lpstrResultText = "Rich Text Format";
		ps.arrPasteEntries[ps.cPasteEntries].dwFlags = 0;
		ps.cPasteEntries++;
	}

	{
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.cfFormat = CF_METAFILEPICT;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.dwAspect = DVASPECT_CONTENT;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.lindex = -1;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.tymed = TYMED_MFPICT;
		ps.arrPasteEntries[ps.cPasteEntries].lpstrFormatName = "Metafile";
		ps.arrPasteEntries[ps.cPasteEntries].lpstrResultText = "Metafile";
		ps.arrPasteEntries[ps.cPasteEntries].dwFlags = 0;
		ps.cPasteEntries++;
	}

	{
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.cfFormat = CF_ENHMETAFILE;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.dwAspect = DVASPECT_CONTENT;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.lindex = -1;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.tymed = TYMED_ENHMF;
		ps.arrPasteEntries[ps.cPasteEntries].lpstrFormatName = "Enhanced Metafile";
		ps.arrPasteEntries[ps.cPasteEntries].lpstrResultText = "Enhanced Metafile";
		ps.arrPasteEntries[ps.cPasteEntries].dwFlags = 0;
		ps.cPasteEntries++;
	}

	{
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.cfFormat = _clipboardFormats.cfPng;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.dwAspect = DVASPECT_CONTENT;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.lindex = -1;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.tymed = TYMED_ISTREAM;
		ps.arrPasteEntries[ps.cPasteEntries].lpstrFormatName = "PNG";
		ps.arrPasteEntries[ps.cPasteEntries].lpstrResultText = "PNG";
		ps.arrPasteEntries[ps.cPasteEntries].dwFlags = 0;
		ps.cPasteEntries++;
	}

	{
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.cfFormat = _clipboardFormats.cfJpeg;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.dwAspect = DVASPECT_CONTENT;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.lindex = -1;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.tymed = TYMED_ISTREAM;
		ps.arrPasteEntries[ps.cPasteEntries].lpstrFormatName = "JPEG";
		ps.arrPasteEntries[ps.cPasteEntries].lpstrResultText = "JPEG";
		ps.arrPasteEntries[ps.cPasteEntries].dwFlags = 0;
		ps.cPasteEntries++;
	}

	{
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.cfFormat = _clipboardFormats.cfGif;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.dwAspect = DVASPECT_CONTENT;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.lindex = -1;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.tymed = TYMED_ISTREAM;
		ps.arrPasteEntries[ps.cPasteEntries].lpstrFormatName = "GIF";
		ps.arrPasteEntries[ps.cPasteEntries].lpstrResultText = "GIF";
		ps.arrPasteEntries[ps.cPasteEntries].dwFlags = 0;
		ps.cPasteEntries++;
	}

	UINT n = OleUIPasteSpecial(&ps);
	
	if (n == OLEUI_OK)
	{
		CComPtr<IEnumFORMATETC> enumfmt;
		ps.lpSrcDataObj->EnumFormatEtc(1, &enumfmt);

		FORMATETC fetc;
		DWORD fetched;
		while ((enumfmt->Next(1, &fetc, &fetched) == S_OK) && fetched)
		{
			TCHAR name[512];
			GetClipboardFormatName(fetc.cfFormat, name, sizeof(name));

			::MessageBox(NULL, name, "clip", MB_OK);
		}

		STGMEDIUM stgm;
		if (SUCCEEDED(ps.lpSrcDataObj->GetData(&ps.arrPasteEntries[ps.nSelectedIndex].fmtetc, &stgm)))
		{
			CComQIPtr<IPDObjectLayerGroup> activeLayerGroup;
			if (m_activeSpread)
				m_activeSpread->getLayerGroupFromLayer(m_activeLayer, &activeLayerGroup);

			if (ps.arrPasteEntries[ps.nSelectedIndex].fmtetc.cfFormat == _clipboardFormats.cfRichTextFormat)
			{
				char* p = (char*)GlobalLock(stgm.hGlobal);
				if (p)
				{
					::MessageBox(NULL, p, "rtf", MB_OK);

					CRTFLoader* pRtf = new CRTFLoader;
					if (pRtf)
					{
						CComPtr<IPDObjectFrame> object;
						m_document->createObjectFrame(&object);

						if (object)
						{
							// Set frame path to rectangle
							{
								CComPtr<IPDPath> path;
								object->get_path(&path);
								
								CComPtr<IPDSubPath> subpath;
								path->createSubPath(&subpath);
								subpath->setRectangle(0, 0, 200, 200);
								path->insertSubPath(-1, subpath);	
							}

						// Create new story
							CComPtr<IPDStory> story;
							m_document->createStory(&story);
							if (story)
							{
								CComPtr<ILDOMDocument> document;
								story->get_textDocument(&document);

								CComPtr<ILDOMDocumentFragment> fragment;
								document->createDocumentFragment(&fragment);

								pRtf->Load(document, fragment, p);

								// Create text Content
								CComPtr<IPDContentText> content;
								m_document->createContentText(&content);
								if (content)
								{
									object->put_content(content);

									// Copy default text frame options
									CComQIPtr<IPDTextFrameOptions> defaultOptions = m_document;
									CComQIPtr<IPDTextFrameOptions> options = content;
									options->copyFrom(defaultOptions);

									story->appendTextThread(content);

								// Copy default properties
									//m_objectSelection->CopyDefaultProperties(object);
									//CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill = m_document;
									//object->copyAppearanceFrom(strokeFill);
									CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill2 = m_document;
									CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill = object;
									strokeFill->copyAppearanceFrom(VARIANT_TRUE, strokeFill2);

								// Append frame
									activeLayerGroup->appendObject(object);

								// Finally append the story to the document
									m_document->appendStory(story);

									SelectPDObject(object, 0, TRUE);
								}
							}
							else
							{
								::MessageBox(GetMainHwnd(), "Couldn't create story", "PageDesigner", MB_OK);
							}
						}

						delete pRtf;
					}

					GlobalUnlock(stgm.hGlobal);
				}
			}
			else if (ps.arrPasteEntries[ps.nSelectedIndex].fmtetc.tymed == TYMED_MFPICT)
			{
				LPMETAFILEPICT pmfp = (LPMETAFILEPICT)GlobalLock(stgm.hMetaFilePict); 
				if (pmfp)
				{
					SIZEL sizeInHiMetric;
					sizeInHiMetric.cx = pmfp->xExt;
					sizeInHiMetric.cy = pmfp->yExt;

					SIZEL sizeInPix;
					AtlHiMetricToPixel(&sizeInHiMetric, &sizeInPix);

					UINT nSize = ::GetMetaFileBitsEx(pmfp->hMF, 0, NULL);
//MM_ISOTROPIC
					LPBYTE buffer = (LPBYTE)malloc(nSize);
					if (buffer)
					{
						::GetMetaFileBitsEx(pmfp->hMF, nSize, buffer);

						HENHMETAFILE hemf = ::SetWinMetaFileBits(nSize, buffer, NULL, NULL);

						free(buffer);

						if (hemf)
						{
							CReadEMF* rdemf = new CReadEMF;
							if (rdemf)
							{
								CComPtr<IPDObjectGroup> group;
								rdemf->ReadEMF(hemf, &sizeInPix, m_document, &group);
								if (group)
								{
									activeLayerGroup->appendObject(group);
								}

								delete rdemf;
							}

							DeleteEnhMetaFile(hemf);
						}
					}

					GlobalUnlock(stgm.hMetaFilePict);
				}
			}
			else if (ps.arrPasteEntries[ps.nSelectedIndex].fmtetc.tymed == TYMED_ENHMF)
			{
				CReadEMF* rdemf = new CReadEMF;
				if (rdemf)
				{
					CComPtr<IPDObjectGroup> group;
					rdemf->ReadEMF(stgm.hEnhMetaFile, NULL, m_document, &group);
					if (group)
					{
						activeLayerGroup->appendObject(group);
					}

					delete rdemf;
				}
			}
			else if (ps.arrPasteEntries[ps.nSelectedIndex].fmtetc.tymed == TYMED_ISTREAM)
			{
				CComPtr<IPDImage> image;
				m_document->loadImageFromStream(stgm.pstm, &image);
				if (image)
				{
					CComQIPtr<IPDContentGraphic> contentGraphic;
					m_document->createContentGraphic(&contentGraphic);
					if (contentGraphic)
					{
						contentGraphic->put_image(image);

						activeLayerGroup->appendObject(contentGraphic);
					}
				}
			}

			ReleaseStgMedium(&stgm);
		}

		ps.lpSrcDataObj->Release();
	}
	else
	{
		ATLTRACE("OleUI error %d\n", n);
	}

	return 0;
}

LRESULT CPDDocumentView::OnEditPasteInto(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	PasteObjectsIntoFromClipboard();
	return 0;
}

LRESULT CPDDocumentView::OnEditClear(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ClearSelection();
	return 0;
}

void CPDDocumentView::OnEditCutCopyClearUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->Enable(m_targetObjects.GetSize() > 0);
}

void CPDDocumentView::OnEditPasteUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->Enable(
						IsClipboardFormatAvailable(_clipboardFormats.cfRichTextFormat) ||
						IsClipboardFormatAvailable(CF_ENHMETAFILE) ||
						IsClipboardFormatAvailable(CF_METAFILEPICT) ||
						IsClipboardFormatAvailable(_clipboardFormats.cfPng) ||
						IsClipboardFormatAvailable(_clipboardFormats.cfJpeg) ||
						IsClipboardFormatAvailable(_clipboardFormats.cfGif)
	);
}

void CPDDocumentView::OnEditPasteSpecialUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->Enable(
						IsClipboardFormatAvailable(_clipboardFormats.cfRichTextFormat) ||
						IsClipboardFormatAvailable(CF_ENHMETAFILE) ||
						IsClipboardFormatAvailable(CF_METAFILEPICT) ||
						IsClipboardFormatAvailable(_clipboardFormats.cfPng) ||
						IsClipboardFormatAvailable(_clipboardFormats.cfJpeg) ||
						IsClipboardFormatAvailable(_clipboardFormats.cfGif)
	);
}

void CPDDocumentView::OnEditPasteIntoUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	if (m_targetObjects.GetSize() == 1)
	{
		if (IsClipboardFormatAvailable(CF_UNICODETEXT))
		{
			CComQIPtr<IPDObjectFrame> frame;
			CComQIPtr<IPDObjectText> text;

			if (frame = m_targetObjects[0]->m_object)
			{
				bEnable = TRUE;
			}
			else if (text = m_targetObjects[0]->m_object)
			{
				bEnable = TRUE;
			}
		}
	}

	pCmdUI->Enable(bEnable);
}

#include "TextFrameOptionsDlg.h"

LRESULT CPDDocumentView::OnObjectTextFrameOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CTextFrameOptionsDlg dlg;

	if (m_targetObjects.GetSize() > 0)
	{
		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CComQIPtr<IPDTextFrameOptions> contentText;

			CComQIPtr<IPDObjectFrame> frame = m_targetObjects[i]->m_object;
			if (frame)
			{
				CComPtr<IPDObject> content;
				frame->get_content(&content);
				contentText = content;
			}
			else
				contentText = m_targetObjects[i]->m_object;

			if (contentText)
			{
				dlg.m_targetObjects.Add(contentText);
			}
		}
	}
	else
	{
		CComQIPtr<IPDTextFrameOptions> textframeOptions = m_document;
		dlg.m_targetObjects.Add(textframeOptions);
	}

	if (dlg.m_targetObjects.GetSize() > 0)
	{
		if (dlg.DoModal(GetMainHwnd(), NULL) == IDOK)
		{
		}
	}

	return 0;
}

void CPDDocumentView::OnObjectTextFrameOptionsUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	if (m_targetObjects.GetSize() > 0)
	{
		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CComQIPtr<IPDContentText> contentText;

			CComQIPtr<IPDObjectFrame> frame = m_targetObjects[i]->m_object;
			if (frame)
			{
				CComPtr<IPDObject> content;
				frame->get_content(&content);
				contentText = content;
			}
			else
				contentText = m_targetObjects[i]->m_object;

			if (contentText)
			{
				bEnable = TRUE;
				break;
			}
		}
	}
	else
	{
		bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}

#include "PathTypeOptionsDlg.h"

LRESULT CPDDocumentView::OnObjectPathTypeOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CPathTypeOptionsDlg dlg;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDPathText> pathText;

		CComQIPtr<IPDObjectFrame> frame = m_targetObjects[i]->m_object;
		if (frame)
			frame->get_pathText(&pathText);
		else
			pathText = m_targetObjects[i]->m_object;

		if (pathText)
		{
			dlg.m_targetObjects.Add(pathText);
		}
	}

	if (dlg.m_targetObjects.GetSize() > 0)
	{
		if (dlg.DoModal(GetMainHwnd(), NULL) == IDOK)
		{
		}
	}

	return 0;
}

void CPDDocumentView::OnObjectPathTypeOptionsUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDPathText> pathText;

		CComQIPtr<IPDObjectFrame> frame = m_targetObjects[i]->m_object;
		if (frame)
			frame->get_pathText(&pathText);
		else
			pathText = m_targetObjects[i]->m_object;

		if (pathText)
		{
			bEnable = TRUE;
			break;
		}
	}

	pCmdUI->Enable(bEnable);
}

LRESULT CPDDocumentView::OnWindowNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
// View
	CComObject<CPDDocumentView>* pView;
	CComObject<CPDDocumentView>::CreateInstance(&pView);
	if (pView)
	{
		long scrollposX; m_horz->get_pos(&scrollposX);
		long scrollposY; m_vert->get_pos(&scrollposY);

		pView->m_document = m_document;
		gApp->m_frame->FindMenu(IDR_PDDOCUMENTVIEW, &pView->m_menu);

		pView->m_activeLayer = m_activeLayer;
		pView->m_activeSpread = m_activeSpread;
		pView->m_activeMasterSpread = m_activeMasterSpread;

		pView->m_rulerOffset = m_rulerOffset;
		pView->m_activeSpreadOffset = m_activeSpreadOffset;
		pView->m_magnify = m_magnify;

		pView->setScrollPosXY(scrollposX, scrollposY);
		pView->SetMatrix();

		{
			CComObject<CUIMDIChild>* child;
			CComObject<CUIMDIChild>::CreateInstance(&child);
			child->AddRef();
			gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&child->m_spFrame);

			child->AddPage(pView, NULL);

			child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);
		}
	}

	return 0;
}

LRESULT CPDDocumentView::OnObjectFitContentToFrame(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CPDObjectSelected* pObject = m_targetObjects[i];

		CComQIPtr<IPDObjectFrame> frame = pObject->m_object;
		if (frame)
		{
/*			RectD frameBounds;
			frame->get_bounds(&frameBounds);

			CComPtr<IPDObject> content;
			frame->get_content(&content);
			if (content)
			{
				RectD contentBounds;
				content->get_bounds(&contentBounds);

				content->Move(frameBounds.X-contentBounds.X, frameBounds.Y-contentBounds.Y);

				double sx = frameBounds.Width / contentBounds.Width;
				double sy = frameBounds.Height / contentBounds.Height;

				CComPtr<IPDMatrix> mat0;
				mat0.CoCreateInstance(CLSID_PDMatrix);

				mat0->setTranslate(-frameBounds.X, -frameBounds.Y);

				CComPtr<IPDMatrix> mat1;
				mat0->scaleNonUniform(sx, sy, &mat1);

				CComPtr<IPDMatrix> mat2;
				mat1->translate(frameBounds.X, frameBounds.Y, &mat2);

				content->put_transformMatrix(mat2);
			}
			*/
		}
	}

	Invalidate();	// TODO remove

	return 0;
}

LRESULT CPDDocumentView::OnObjectFitFrameToContent(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

LRESULT CPDDocumentView::OnCenterContent(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

LRESULT CPDDocumentView::OnFitContentProportionally(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

LRESULT CPDDocumentView::OnObjectCompoundPathsMake(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	if (m_pActiveObject)
	{
		CArray <IPDObjectFrame*, IPDObjectFrame*> layers;

		CComPtr<IPDObjectGroup> parent;
		m_pActiveObject->m_object->get_parent((IPDObject**)&parent);

		{
			CComPtr<IObjectMap> children;
			parent->get_children(&children);

			long length;
			children->get_length(&length);

			for (int i = 0; i < length; i++)
			{
				CComPtr<IPDObject> object;
				children->item(i, (IUnknown**)&object);

				CComQIPtr<IPDObjectFrame> frame = object;
				if (frame)
				{
					if (IsPDObjectSelected(frame))
					{
						layers.Add(frame);
					}
				}
			}
		}

		if (layers.GetSize() >= 2)	// At least two objects must be selected
		{
			IPDObjectFrame* pDestShape = layers[0];

			CComPtr<IPDPath> destpath;
			pDestShape->get_path(&destpath);

			/*
			CDblPoint relto;// = pDestShape->GetLayerPosition();
			relto.x = 0;
			relto.y = 0;
			*/

			for (int j = 1; j < layers.GetSize(); j++)
			{
				CComPtr<IPDPath> path;
				layers[j]->get_path(&path);

				long nsubpaths;
				path->get_subPathCount(&nsubpaths);
				for (long nsubpath = 0; nsubpath < nsubpaths; nsubpath++)
				{
					CComPtr<IPDSubPath> subpath;
					path->getSubPath(nsubpath, &subpath);

					destpath->insertSubPath(-1, subpath);
				}

				DeselectPDObject(layers[j]);
				parent->removeObject(layers[j]);
			}

		/*
		// Build an array of dest bezlists that we will insert the other bezlists into
			CArray<CBezierList*,CBezierList*> bezarray;
			bezarray.Add((CBezierList*)pParam->GetUValue().arbdata);
			int keyframes = pParam->GetKeyFrameCount();

			for (int i = 0; i < keyframes; i++)
			{
				ParamUnion* pu = pParam->GetKeyFrameUValue(i);
				bezarray.Add((CBezierList*)pu->arbdata);
			}

		// Move the bezier coordinates to approximate no visual difference when
		// putting them in destination layer
			for (i = 1; i < layers.GetSize(); i++)
			{
				CPathLayer* pShape = layers[i];
				CDblPoint relfrom = pShape->GetLayerPosition();

				CBezierList* pFromBezList = pShape->GetBezList();
				UPOSITION pos = pFromBezList->GetHeadPosition();
				while (pos)
				{
					CBezier* pBez = (CBezier*)pFromBezList->GetNext(pos);
					pBez->MovePoints(pFromBezList->m_bIsBezier, relfrom.x - relto.x, relfrom.y - relto.y);
				}
			}

		// Now, put the beziers into the destination layer
			for (i = 1; i < layers.GetSize(); i++)
			{
				CPathLayer* pShape = layers[i];
				CBezierList* pFromBezList = pShape->GetBezList();

				for (int j = 0; j < bezarray.GetSize(); j++)
				{
					UPOSITION pos = pFromBezList->GetHeadPosition();
					while (pos)
					{
						CBezier* pBez = (CBezier*)pFromBezList->GetNext(pos);

						bezarray[j]->AddTail(pBez);
					}
				}

				pShape->GetBezList()->RemoveAll();	// So the beziers don't get deleted in the destructor

			// Remove/Delete layer
				pShape->OnDeleting();
				RemoveObject(pShape);
				pShape->Release();
			}

		// ??? TODO: have a simpler (faster way)
		//	pDestShape->SetBezList(pDestShape->GetBezList());	// Add a keyframe on current frame if not there

			pDestShape->TOP()->OnCalculateBounds();

			return pDestShape;
			*/
		}
	}
#endif

	return 0;
}

LRESULT CPDDocumentView::OnObjectCompoundPathsRelease(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

LRESULT CPDDocumentView::OnObjectReversePath(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CPDObjectSelected* pObject = m_targetObjects[i];

		if (pObject->m_wrapPath)
		{
			pObject->m_wrapPath->ReverseSelectedPath();
		}

		PDObjectType objectType;
		pObject->m_object->get_objectType(&objectType);
		if (objectType == OBJECT_FRAME)
		{
			CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;

			pFrame->m_path->ReverseSelectedPath();
		}
	}

	return 0;
}

LRESULT CPDDocumentView::OnObjectPathAddAnchorPoints(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CPDObjectSelected* pObject = m_targetObjects[i];

		if (pObject->m_wrapPath)
		{
			if (pObject->m_wrapPath->m_selectedPoints.GetSize() > 0)
			{
				pObject->m_wrapPath->AddAnchorPoints();
			}
		}

		PDObjectType objectType;
		pObject->m_object->get_objectType(&objectType);
		if (objectType == OBJECT_FRAME)
		{
			CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;
			if (pFrame->m_path->m_selectedPoints.GetSize() > 0)
			{
				pFrame->m_path->AddAnchorPoints();
			}
		}
	}

	return 0;
}

void CPDDocumentView::OnObjectPathAddAnchorPointsUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CPDObjectSelected* pObject = m_targetObjects[i];

		if (pObject->m_wrapPath)
		{
			if (pObject->m_wrapPath->m_selectedPoints.GetSize() > 0)
			{
				bEnable = TRUE;
			}
		}

		PDObjectType objectType;
		pObject->m_object->get_objectType(&objectType);
		if (objectType == OBJECT_FRAME)
		{
			CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)pObject;
			if (pFrame->m_path->m_selectedPoints.GetSize() > 0)
			{
				bEnable = TRUE;
			}
		}
	}

	pCmdUI->Enable(bEnable);
}

LRESULT CPDDocumentView::OnObjectGroup(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_targetObjects.GetSize() >= 2)
	{
		CComObject<CUndoGroupObjects>* pUndo;
		CComObject<CUndoGroupObjects>::CreateInstance(&pUndo);
		if (pUndo)
		{
			pUndo->AddRef();
			pUndo->m_document = m_document;
			m_activeSpread->get_uniqId(&pUndo->m_spreadGUID);

			CComPtr<IOleUndoManager> undoManager;
			m_document->get_undoManager(&undoManager);

			pUndo->DoInitial(this, undoManager);

			undoManager->Add(pUndo);
		}
	}

	return 0;
}

LRESULT CPDDocumentView::OnObjectUngroup(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

void CPDDocumentView::OnObjectGroupUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;
	if (m_targetObjects.GetSize() >= 2)
	{
		bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}

void CPDDocumentView::OnObjectUngroupUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	if (m_pActiveObject)
	{
		CComQIPtr<IPDObjectGroup> group = m_pActiveObject->m_object;
		if (group)
		{
			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
}

#pragma comment(lib, "shlwapi.lib")

class CAILoader
{
public:

	long m_fpos;
	char* m_data;
	long m_len;

	BOOL eof()
	{
		return (m_fpos >= m_len);
	}

	int getc()
	{
		if (m_fpos < m_len)
		{
			return m_data[m_fpos++];
		}
		else
			return EOF;
	}

	void ungetc()
	{
		ATLASSERT(m_fpos > 0);
		m_fpos--;
	}

	void SkipSpaces()
	{
		while (isspace(getc()))
			;

		ungetc();
	}


	void LoadAI(TCHAR* filepath);
	void GetProlog();
	void GetSetup();

	CUString GetLine();
};

CUString CAILoader::GetLine()
{
	CUString str;
	while (!eof())
	{
		int c = getc();
		if (c == '\n' || c == '\r')
			break;

		str += CUString(c);
	}

	return str;
}

void CAILoader::LoadAI(TCHAR* filepath)
{
	FILE* fp;
	if (fp = fopen(filepath, "r"))
	{
		fseek(fp, 0, SEEK_END);
		m_len = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		m_fpos = 0;
		m_data = (char*)malloc(m_len);
		fread(m_data, 1, m_len, fp);

		GetProlog();

		fclose(fp);
		free(m_data);
	}
}

void CAILoader::GetSetup()
{
	CUString line;
	
	GetLine();
	if (strcmp(line, "%%BeginSetup"))
	{
		throw L"Expected %%BeginSetup";
	}




	GetLine();
	if (strcmp(line, "%%EndSetup"))
	{
		throw L"Expected %%EndSetup";
	}
}

void CAILoader::GetProlog()
{
	CUString line;
	
	line = GetLine();
	if (strncmp(line, "%!PS-Adobe-", 11))
	{
		throw L"Not an AI file";
	}

// header

// comments
	while (!eof())
	{
		int c = getc();
		if (c == '%')
		{
			CUString line = GetLine();
			if (!strcmp(line, "%EndComments"))
				break;
		}
	}

	line = GetLine();
	if (strcmp(line, "%%BeginProlog"))
	{
		throw L"Expected %%BeginProlog";
	}
}

class ATL_NO_VTABLE CFileStream : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IStream
{
public:
	CFileStream()
	{
		m_hFile = NULL;
	}

	HANDLE m_hFile;

	void FinalRelease()
	{
		if (m_hFile)
		{
			CloseHandle(m_hFile);
			m_hFile = NULL;
		}
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFileStream)
	COM_INTERFACE_ENTRY(IStream)
	COM_INTERFACE_ENTRY(ISequentialStream)
END_COM_MAP()

public:
	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Read( 
		/* [length_is][size_is][out] */ void *pv,
		/* [in] */ ULONG cb,
		/* [out] */ ULONG *pcbRead)
	{
		DWORD nRead;
		BOOL b = ReadFile(m_hFile, pv, cb, &nRead, NULL);
		if (pcbRead) *pcbRead = nRead;

		if (b)
			return S_OK;
		else
			return E_FAIL;
	}
	
	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Write( 
		/* [size_is][in] */ const void *pv,
		/* [in] */ ULONG cb,
		/* [out] */ ULONG *pcbWritten)
	{
		return S_OK;
	}

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Seek( 
		/* [in] */ LARGE_INTEGER dlibMove,
		/* [in] */ DWORD dwOrigin,
		/* [out] */ ULARGE_INTEGER *plibNewPosition)
	{
		LONG high = dlibMove.HighPart;
		ULARGE_INTEGER newpos;
		newpos.LowPart = SetFilePointer(m_hFile, dlibMove.LowPart, &high, dwOrigin);
		newpos.HighPart = high;

		if (plibNewPosition) *plibNewPosition = newpos;

		return S_OK;
	}
		
		virtual HRESULT STDMETHODCALLTYPE SetSize( 
		/* [in] */ ULARGE_INTEGER libNewSize)
		{
			return E_NOTIMPL;
		}
		
		virtual /* [local] */ HRESULT STDMETHODCALLTYPE CopyTo( 
		/* [unique][in] */ IStream *pstm,
		/* [in] */ ULARGE_INTEGER cb,
		/* [out] */ ULARGE_INTEGER *pcbRead,
		/* [out] */ ULARGE_INTEGER *pcbWritten)
		{
			return E_NOTIMPL;
		}

		
		virtual HRESULT STDMETHODCALLTYPE Commit( 
		/* [in] */ DWORD grfCommitFlags)
		{
			return E_NOTIMPL;
		}

		
		virtual HRESULT STDMETHODCALLTYPE Revert( void)
		{
			return E_NOTIMPL;
		}

	
	virtual HRESULT STDMETHODCALLTYPE LockRegion( 
		/* [in] */ ULARGE_INTEGER libOffset,
		/* [in] */ ULARGE_INTEGER cb,
		/* [in] */ DWORD dwLockType)
		{
			return E_NOTIMPL;
		}

		
		virtual HRESULT STDMETHODCALLTYPE UnlockRegion( 
		/* [in] */ ULARGE_INTEGER libOffset,
		/* [in] */ ULARGE_INTEGER cb,
		/* [in] */ DWORD dwLockType)
		{
			return E_NOTIMPL;
		}

		
		virtual HRESULT STDMETHODCALLTYPE Stat( 
		/* [out] */ STATSTG *pstatstg,
		/* [in] */ DWORD grfStatFlag)
		{
			return E_NOTIMPL;
		}

		
		virtual HRESULT STDMETHODCALLTYPE Clone( 
		/* [out] */ IStream **ppstm)
		{
			return E_NOTIMPL;
		}
		
};

#include "SVGLoader.h"
#include "psd.h"

LRESULT CPDDocumentView::OnFilePlace(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_objectToPlace.Release();

	static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
												"JPEG (*.jpg,*.jpeg)\0*.jpg;*.jpeg\0"
												"GIF (*.gif)\0*.gif\0"
												"TIFF (*.tif,*.tiff)\0*.tif;*.tiff\0"
												"BMP (*.bmp)\0*.bmp\0"
												"PSD (*.psd)\0*.psd\0"
												"SVG (*.svg)\0*.svg\0"
												"WMF/EMF (*.wmf,*.emf)\0*.wmf;*.emf\0"
												"Adobe Illustrator (*.ai)\0*.ai\0"
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
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = sizeof(sbuffer);
	ofn.lpstrInitialDir = curdir;
	ofn.lpstrFilter = FilesFilter;
	
	if (GetOpenFileName(&ofn))
	{
		/*
		CComQIPtr<IPDObjectLayerGroup> activeLayerGroup;
		if (m_activeSpread)
			m_activeSpread->getLayerGroupFromLayer(m_activeLayer, &activeLayerGroup);
			*/

		LPTSTR ext = PathFindExtension(sbuffer);
		if (ext && !stricmp(ext, ".ai"))
		{
			try
			{
				CAILoader* loader = new CAILoader;
				loader->LoadAI(sbuffer);

				::MessageBox(GetMainHwnd(), "successfully loaded AI", "AI", MB_OK);
			}
			catch(WCHAR* msg)
			{
				::MessageBox(GetMainHwnd(), _bstr_t(msg), "AI error", MB_OK);
			}
		}
		else
		{
			HRESULT hr = E_FAIL;

			if (FAILED(hr))
			{
#if 0
				CSVGLoader* pSVG = new CSVGLoader;
				if (pSVG)
				{
					CComPtr<IPDObjectGroup> objectGroup;
					hr = pSVG->Load(m_document, _bstr_t(sbuffer), &objectGroup);

					m_objectToPlace = objectGroup;

					delete pSVG;
				}
#endif
			}

			//URLOpenBlockingStream 

			if (FAILED(hr))
			{
				CComObject<CFileStream>* pFileStream;
				CComObject<CFileStream>::CreateInstance(&pFileStream);
				if (pFileStream)
				{
					pFileStream->AddRef();

					pFileStream->m_hFile = CreateFile(sbuffer, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
					if (pFileStream->m_hFile != INVALID_HANDLE_VALUE)
					{
						CPSDFile* psdfile = new CPSDFile;
						if (psdfile)
						{
							if (SUCCEEDED(psdfile->ParsePSDFile(pFileStream)))
							{
								GUID groupGuid;
								CoCreateGuid(&groupGuid);
								CComPtr<IPDObjectGroup> objectGroup;
								m_document->createObjectGroup(groupGuid, &objectGroup);

								for (int nlayer = 0; nlayer < abs(psdfile->m_numLayers); nlayer++)
								{
									CPSDLayer* pLayer = psdfile->m_layerList[nlayer];

									int layerWidth = pLayer->layerinfo.rect.right-pLayer->layerinfo.rect.left;
									int layerHeight = pLayer->layerinfo.rect.bottom-pLayer->layerinfo.rect.top;

									CComPtr<IPDContentGraphic> objectGraphic;
									m_document->createContentGraphic(&objectGraphic);
									if (objectGraphic)
									{
										objectGraphic->setxy(pLayer->layerinfo.rect.left, pLayer->layerinfo.rect.top);

										CComPtr<IPDImage> image;
										m_document->createImage(layerWidth, layerHeight, PixelFormat32bppARGB, &image);

										if (image)
										{
											Gdiplus::Bitmap* pBitmap;
											image->get_privateImage((DWORD*)&pBitmap);

											Gdiplus::BitmapData bitmapData;
											pBitmap->LockBits(
												&Gdiplus::Rect(0, 0, layerWidth, layerHeight),
												Gdiplus::ImageLockModeWrite,
												PixelFormat32bppARGB,
												&bitmapData);

											// blue
											pLayer->ReadPSDLayerChannel(2, bitmapData.Stride, (LPBYTE)bitmapData.Scan0+0);

											// green
											pLayer->ReadPSDLayerChannel(1, bitmapData.Stride, (LPBYTE)bitmapData.Scan0+1);

											// red
											pLayer->ReadPSDLayerChannel(0, bitmapData.Stride, (LPBYTE)bitmapData.Scan0+2);

											// alpha
											pLayer->ReadPSDLayerChannel(-1, bitmapData.Stride, (LPBYTE)bitmapData.Scan0+3);

											pBitmap->UnlockBits(&bitmapData);

											objectGraphic->put_image(image);
										}

										objectGroup->appendObject(objectGraphic);
									}
								}

								m_objectToPlace = objectGroup;
								//activeLayerGroup->appendObject(objectGroup);

								hr = S_OK;
							}

							delete psdfile;
						}
					}

					pFileStream->Release();
				}
			}

			if (FAILED(hr))
			{
				CComPtr<IPDImage> image;
				m_document->loadImage(_bstr_t(sbuffer), &image);
				if (image)
				{
					CComQIPtr<IPDContentGraphic> contentGraphic;
					m_document->createContentGraphic(&contentGraphic);
					if (contentGraphic)
					{
						contentGraphic->put_image(image);
						m_objectToPlace = contentGraphic;
					}
				}
				else
				{
					CUString msg;
					msg.Format("Couldn't load image\n%s", sbuffer);
					::MessageBox(GetMainHwnd(), msg, "PageDesigner", MB_OK);
				}
			}

			if (m_objectToPlace)
			{
				CComQIPtr<IPDObjectFrame> frame;

				if (m_targetObjects.GetSize() == 1)
				{
					CPDObjectFrameSelected* pFrame = (CPDObjectFrameSelected*)m_targetObjects[0];
					frame = pFrame->m_object;
				}

				if (frame)
				{
					CComPtr<IPDObject> content;
					frame->get_content(&content);
					CComQIPtr<IPDContentGraphic> contentGraphic = content;

					if (content == NULL || contentGraphic != NULL)	// We can place it now
					{
						CComQIPtr<IPDContentGraphic> graphicToPlace = m_objectToPlace;
						if (contentGraphic && graphicToPlace)
						{
							// Use the already existing contentgraphic and just copy the image
							CComPtr<IPDImage> image;
							graphicToPlace->get_image(&image);
							contentGraphic->put_image(image);
						}
						else
						{
							frame->put_content(m_objectToPlace);
						}

						m_objectToPlace.Release();
					}
				}

				if (m_objectToPlace)	// Can't place it now, change tool to 'place graphic tool'
				{
					gApp->m_activeTool = -12;
				}
			}
		}
	}

	return 0;
}

LRESULT CPDDocumentView::OnObjectContentGraphic(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObjectFrame> frame = m_targetObjects[i]->m_object;
		if (frame)
		{
			CComPtr<IPDContentGraphic> content;
			m_document->createContentGraphic(&content);

			frame->put_content(content);
		}
	}

	return 0;
}

LRESULT CPDDocumentView::OnObjectContentText(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObjectFrame> frame = m_targetObjects[i]->m_object;
		if (frame)
		{
			CComPtr<IPDContentText> content;
			m_document->createContentText(&content);

			frame->put_content(content);
		}
	}

	return 0;
}

LRESULT CPDDocumentView::OnObjectContentUnassigned(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObjectFrame> frame = m_targetObjects[i]->m_object;
		if (frame)
		{
			frame->put_content(NULL);
		}
	}

	return 0;
}

LRESULT CPDDocumentView::OnViewZoomIn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_magnify *= 2;
	SetMatrix();

	m_bInvalid = true;
	OnSize();
	Invalidate();

	return 0;
}

LRESULT CPDDocumentView::OnViewZoomOut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_magnify /= 2;
	SetMatrix();

	m_bInvalid = true;
	OnSize();
	Invalidate();

	return 0;
}

LRESULT CPDDocumentView::OnViewActualSize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	long scrollposX = m_horz->get_pos(&scrollposX);
	long scrollposY = m_vert->get_pos(&scrollposY);

	double docwidth = m_areaRect.Width();///m_magnify;
	double docheight = m_areaRect.Height();///m_magnify;

	long x = (long)(scrollposX/m_magnify);
	long y = (long)(scrollposY/m_magnify);

	ZoomToRect2(
		x-docwidth/2,
		y-docheight/2,
		x+docwidth/2,
		y+docheight/2);

	return 0;
}

void CPDDocumentView::OnViewActualSizeUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_magnify == 1.0);
}

LRESULT CPDDocumentView::OnViewRulers(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	put_rulers(m_bRulers? VARIANT_FALSE: VARIANT_TRUE);
	return 0;
}

void CPDDocumentView::OnViewRulersUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_bRulers);
}

void CPDDocumentView::SetTextWrapOnObjects(PDTextWrap textWrap)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CPDObjectSelected* pObject = m_targetObjects[i];

		CComQIPtr<IPDObjectWrappable> objectWrappable = pObject->m_object;
		if (objectWrappable)
		{
			objectWrappable->put_textWrap(textWrap);

			pObject->SetWrapPath();
		}
	}

//	Invalidate();
}

LRESULT CPDDocumentView::OnTextWrapNone(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetTextWrapOnObjects(TEXTWRAP_NONE);
	return 0;
}

LRESULT CPDDocumentView::OnTextWrapBBox(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetTextWrapOnObjects(TEXTWRAP_BBOX);
	return 0;
}

LRESULT CPDDocumentView::OnTextWrapShape(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetTextWrapOnObjects(TEXTWRAP_SHAPE);
	return 0;
}

LRESULT CPDDocumentView::OnTextWrapObject(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetTextWrapOnObjects(TEXTWRAP_JUMPOBJECT);
	return 0;
}

LRESULT CPDDocumentView::OnTextWrapColumn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetTextWrapOnObjects(TEXTWRAP_JUMPCOLUMN);
	return 0;
}

LRESULT CPDDocumentView::OnTextWrapOffset(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wNotifyCode == EN_KILLFOCUS)
	{
		BOOL bTrans;
		double value = GetWindowTextValue(hWndCtl, &bTrans);
		if (bTrans)
		{
			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				CComQIPtr<IPDObjectWrappable> objectWrappable = m_targetObjects[i]->m_object;
				if (objectWrappable)
				{
					if (wID == ID_TEXTWRAP_TOPOFFSET)			objectWrappable->put_topOffset(value);
					else if (wID == ID_TEXTWRAP_LEFTOFFSET)	objectWrappable->put_leftOffset(value);
					else if (wID == ID_TEXTWRAP_BOTTOMOFFSET)	objectWrappable->put_bottomOffset(value);
					else if (wID == ID_TEXTWRAP_RIGHTOFFSET)	objectWrappable->put_rightOffset(value);
				}
			}
		}
	}

	return 0;
}

void CPDDocumentView::OnTextWrapOffsetUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	HWND hWnd;
	pCmdUI->get_hwndControl(&hWnd);
	if (hWnd && ::GetFocus() != hWnd)
	{
		//BOOL bEnable = FALSE;
		double value = tomUndefined;
		VARIANT_BOOL isRectangular = -2;
		BOOL editedWrapPath = tomUndefined;
		PDTextWrap textWrap = (PDTextWrap)tomUndefined;

		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CComQIPtr<IPDObjectWrappable> objectWrappable = m_targetObjects[i]->m_object;
			if (objectWrappable)
			{
				double value2;

				if (iid == ID_TEXTWRAP_TOPOFFSET) objectWrappable->get_topOffset(&value2);
				else if (iid == ID_TEXTWRAP_LEFTOFFSET) objectWrappable->get_leftOffset(&value2);
				else if (iid == ID_TEXTWRAP_BOTTOMOFFSET) objectWrappable->get_bottomOffset(&value2);
				else if (iid == ID_TEXTWRAP_RIGHTOFFSET) objectWrappable->get_rightOffset(&value2);

				VARIANT_BOOL isRectangular2;
				objectWrappable->IsRectangular(&isRectangular2);
				if (i == 0)
				{
					isRectangular = isRectangular2;
				}
				else if (isRectangular != isRectangular2)
				{
					isRectangular = -2;
					break;
				}

				//bEnable = TRUE;

				PDTextWrap textWrap2;
				objectWrappable->get_textWrap(&textWrap2);
				if (i == 0)
				{
					textWrap = textWrap2;
				}
				else if (textWrap != textWrap2)
				{
					textWrap = (PDTextWrap)tomUndefined;
					break;
				}

				BOOL editedWrapPath2;
				objectWrappable->get_editedWrapPath(&editedWrapPath2);
				if (i == 0)
				{
					editedWrapPath = editedWrapPath2;
				}
				else if (editedWrapPath != editedWrapPath2)
				{
					editedWrapPath = tomUndefined;//bEnable = FALSE;
					break;
				}

				if (i == 0)
				{
					value = value2;
				}
				else if (value != value2)
				{
					value = tomUndefined;
					break;
				}
			}
		}

		BOOL bEnable = (	(editedWrapPath == VARIANT_FALSE) &&
								(textWrap == TEXTWRAP_BBOX || textWrap == TEXTWRAP_SHAPE) &&
								(isRectangular != -2) &&
								((iid == ID_TEXTWRAP_TOPOFFSET || isRectangular == VARIANT_TRUE) || textWrap == TEXTWRAP_BBOX));

		::EnableWindow(hWnd, bEnable);

		if (bEnable && value != tomUndefined)
		{
			SetWindowTextValueCheckForSame(hWnd, value, UNIT_PT);
		}
		else
		{
			if (::GetWindowTextLength(hWnd) != 0)
				::SetWindowText(hWnd, "");
		}
	}
}

void CPDDocumentView::OnTextWrapUpdate(PDTextWrap textWrap, IUICmdUpdate* pCmdUI)
{
	BOOL bCheck = FALSE;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CPDObjectSelected* pObject = m_targetObjects[i];

		CComQIPtr<IPDObjectWrappable> objectWrappable = pObject->m_object;
		if (objectWrappable)
		{
			PDTextWrap textWrap2;
			objectWrappable->get_textWrap(&textWrap2);

			if (textWrap2 == textWrap)
			{
				bCheck = TRUE;
			}
			else
			{
				bCheck = FALSE;
				break;
			}
		}
	}

	pCmdUI->SetCheck(bCheck);
}

void CPDDocumentView::OnTextWrapNoneUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	OnTextWrapUpdate(TEXTWRAP_NONE, pCmdUI);
}

void CPDDocumentView::OnTextWrapBBoxUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	OnTextWrapUpdate(TEXTWRAP_BBOX, pCmdUI);
}

void CPDDocumentView::OnTextWrapShapeUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	OnTextWrapUpdate(TEXTWRAP_SHAPE, pCmdUI);
}

void CPDDocumentView::OnTextWrapObjectUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	OnTextWrapUpdate(TEXTWRAP_JUMPOBJECT, pCmdUI);
}

void CPDDocumentView::OnTextWrapColumnUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	OnTextWrapUpdate(TEXTWRAP_JUMPCOLUMN, pCmdUI);
}

#include "IPFrame.h"

/////////// IOleDocumentView helpers

#define ARRAYSIZE(a)    (sizeof(a)/sizeof(a[0]))

HMENU AFXAPI AfxMergeMenus(HMENU hMenuShared, HMENU hMenuSource,
	LONG* lpMenuWidths, int iWidthIndex, BOOL bMergeHelpMenus = FALSE);

HMENU AFXAPI AfxMergeMenus(HMENU hMenuShared, HMENU hMenuSource,
	LONG* lpMenuWidths, int iWidthIndex, BOOL bMergeHelpMenus /* = FALSE */)
{
	ASSERT(hMenuShared != NULL && IsMenu(hMenuShared));
	ASSERT(hMenuSource != NULL && IsMenu(hMenuSource));

	BOOL bHelpMergedAsSubMenu = FALSE;
	HMENU hHelpSubMenu = NULL;

	// copy the popups from the pMenuSource
	int cMenuItems = GetMenuItemCount(hMenuSource);
	int cGroupWidth = 0;
	int nPosition = 0;

	// insert at appropriate spot depending on iWidthIndex
	ASSERT(iWidthIndex == 0 || iWidthIndex == 1);
	if (iWidthIndex == 1)
		nPosition = (int)lpMenuWidths[0];

	for (int i = 0; i < cMenuItems; i++)
	{
		// get the HMENU of the popup
		HMENU hMenuPopup = ::GetSubMenu(hMenuSource, i);

		// separators move us to next group
		UINT state = GetMenuState(hMenuSource, i, MF_BYPOSITION);
		if (hMenuPopup == NULL && (state & MF_SEPARATOR) != 0)
		{
			ASSERT(iWidthIndex <= 5);   // servers should not touch past 5
			lpMenuWidths[iWidthIndex] = cGroupWidth;
			cGroupWidth = 0;
			if (iWidthIndex < 5)
				nPosition += (int)lpMenuWidths[iWidthIndex+1];
			iWidthIndex += 2;
		}
		else
		{
			HMENU hHelpMenu = NULL;

			// are we processing the help menu group?

			if (bMergeHelpMenus && iWidthIndex == 5)
			{
				// if so, see if the container has Help any menu items
				if (lpMenuWidths[iWidthIndex] == 1)
				{
					// get the help menu from the container
					hHelpMenu = GetSubMenu(hMenuShared, nPosition);
				}
			}

			// get the menu item text
			TCHAR szItemText[256];
			int nLen = GetMenuString(hMenuSource, i, szItemText,
				sizeof szItemText, MF_BYPOSITION);

			// popups are handled differently than normal menu items
			if (hMenuPopup != NULL)
			{
				if (hHelpMenu != NULL)
				{
					CUString strTearOff = "PageDesigner";//AfxGetAppName();
					if (!strTearOff.IsEmpty())
						strTearOff += ' ';
					strTearOff += szItemText;

					// container has help items -- add ours to its submenu
					AppendMenu(hHelpMenu, MF_STRING | MF_POPUP,
						(UINT)hMenuPopup, strTearOff);

					// clear the count of Help group items and add
					// the help menu to the window group

					lpMenuWidths[iWidthIndex] = 0;
					lpMenuWidths[iWidthIndex-1]++;

					bHelpMergedAsSubMenu = TRUE;
					hHelpSubMenu = hMenuPopup;
				}
				else if (::GetMenuItemCount(hMenuPopup) != 0)
				{
					// strip the HIBYTE because it contains a count of items
					state = LOBYTE(state) | MF_POPUP;   // must be popup

					// non-empty popup -- add it to the shared menu bar
					InsertMenu(hMenuShared, nPosition, state | MF_BYPOSITION,
						(UINT)hMenuPopup, szItemText);
					++nPosition;
					++cGroupWidth;
				}
			}
			else if (nLen > 0)
			{
				// only non-empty items are added
				ASSERT(szItemText[0] != 0);

				// here the state does not contain a count in the HIBYTE
				InsertMenu(hMenuShared, nPosition, state | MF_BYPOSITION,
					GetMenuItemID(hMenuSource, i), szItemText);
				++nPosition;
				++cGroupWidth;
			}
		}
	}

	// set the last group width

	if (!bHelpMergedAsSubMenu)
	{
		ASSERT(iWidthIndex <= 5);   // servers should not touch past 5
		lpMenuWidths[iWidthIndex] = cGroupWidth;
	}

	return hHelpSubMenu;
}

void CPDDocumentView::MergeMenus()
{
//	::MessageBox(NULL, "MergeMenus", "", MB_OK);

	if(!m_hSharedMenu)
	{
		//  Create the menu resource
		m_hSharedMenu = CreateMenu();
		
		ZeroMemory(&m_mgw, sizeof(m_mgw));
		
		// have the contaner insert its menus
		if(SUCCEEDED(m_spInPlaceFrame->InsertMenus(m_hSharedMenu, &m_mgw)))
		{
			HMENU hMenu;
			hMenu = LoadMenu(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_PDDOCUMENTVIEW));

			// insert our menu popups amongst the container menus
			AfxMergeMenus(m_hSharedMenu, hMenu, &m_mgw.width[0], 1, TRUE);

			/*
			::MessageBox(NULL, "InsertMenus success", "", MB_OK);

			int   nFirstGroup = (int) m_mgw.width[0];
			HMENU hMenu,
				hSubMenu;
			TCHAR szText[MAX_PATH];
			
			hMenu = LoadMenu(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_PDDOCUMENTVIEW));
			hSubMenu = GetSubMenu(hMenu, 0);
			
			//get the menu item's text
			GetMenuString(hMenu, 0, szText, ARRAYSIZE(szText), MF_BYPOSITION);
			
			// insert the server menus
			InsertMenu( m_hSharedMenu, 
				nFirstGroup, 
				MF_BYPOSITION | MF_POPUP, 
				(UINT_PTR)hSubMenu, 
				szText);
			
			//update the OLEMENUGROUPWIDTHS structure
			m_mgw.width[1] += 1;
			m_mgw.width[3] += 0;
			m_mgw.width[5] += 0;
			*/
		}
		else
		{
			::MessageBox(NULL, "InsertMenus failed", "", MB_OK);

			// Destroy the menu resource
			DestroyMenu(m_hSharedMenu);
			m_hSharedMenu = NULL;
		}
	}

	if(!m_hOleMenu)
	{
		// tell OLE to create the menu descriptor
		m_hOleMenu = OleCreateMenuDescriptor(m_hSharedMenu, &m_mgw);
	}
	
	m_spInPlaceFrame->SetMenu(m_hSharedMenu, m_hOleMenu, m_hWnd);
}

HRESULT CPDDocumentView::ActivateInPlace()
{
	//::MessageBox(NULL, "not here", "", MB_OK);
	ActivateInPlace(NULL);
	return S_OK;
}

HRESULT CPDDocumentView::ActivateInPlace(HWND/* hParent*/)
{
//	::MessageBox(NULL, "######### Create window ##########", "", MB_OK);

	m_fInPlaceActive = TRUE;

//	CUString str;
//	str.Format("hParent: %p", hParent);
//	::MessageBox(NULL, str, "", MB_OK);

/*
	if (m_spInPlaceFrame == NULL)
	{
		::MessageBox(NULL, "inplaceframe = NULL", "", MB_OK);
	}
*/
	CPDDocument* pDocument = (CPDDocument*)m_document;

// Create frame
	if (pDocument->m_pInPlaceFrame == NULL)
	{
		CComObject<CIPFrame>::CreateInstance(&pDocument->m_pInPlaceFrame);
		if (pDocument->m_pInPlaceFrame)
		{
			pDocument->m_pInPlaceFrame->AddRef();

			//CComQIPtr<IOleInPlaceFrame> spInPlaceFrame = m_spClientSite;

			HWND hParent;
			m_spInPlaceSite->GetWindow(&hParent);

			if (pDocument->m_pInPlaceFrame->m_hWnd == NULL)
				pDocument->m_pInPlaceFrame->Create(hParent, NULL, NULL, WS_VISIBLE | WS_CHILD);
			else
				pDocument->m_pInPlaceFrame->SetParent(hParent);

			gIFrame = pDocument->m_pInPlaceFrame;	//
		}
	}

	if (pDocument->m_pInPlaceFrame)
	{
		// tell the site we are in-place activating
		m_spInPlaceSite->OnInPlaceActivate();

		if (m_hWnd == NULL)
		{
			CWindowImpl<CPDDocumentView>::Create(pDocument->m_pInPlaceFrame->m_hWnd, m_rect, NULL, WS_CHILD | WS_VISIBLE, 0, 0);
			OnActivate(TRUE, this, NULL);	// ??	// TODO, also deactivate somewhere
		}

		pDocument->m_pInPlaceFrame->m_view = this;
		
		//show the view
		Show(TRUE);
	}

//	::MessageBox(NULL, "######### End Create window ##########", "", MB_OK);

	//	::MessageBox(NULL, "######### Create window ##########", "", MB_OK);
/*	
	if(m_spInPlaceSite) 
	{
		// tell the site we are in-place activating
		m_spInPlaceSite->OnInPlaceActivate();
		
		HWND  hwndParent;
		m_spInPlaceSite->GetWindow(&hwndParent);
	//	SetParent(m_hwndView, hwndParent);

		ATLASSERT(m_hWnd == NULL);
		CWindowImpl<CPDDocumentView>::Create(hwndParent, m_rect, NULL, WS_CHILD | WS_VISIBLE, 0, 0);
		
		//show the view
		Show(TRUE);
	}
*/
	return S_OK;
}

HRESULT CPDDocumentView::DeactivateInPlace()
{
//		::MessageBox(NULL, "Deac", "", MB_OK);
	//UI deactivate, if necessary and hide the view window
	Show(FALSE);// ?????
	
	m_fInPlaceActive = FALSE;
	
	if(m_spInPlaceSite) 
	{
		// tell the site we are in-place deactivating
		m_spInPlaceSite->OnInPlaceDeactivate();
	}
	
	//set the parent to NULL
//	SetParent(m_hwndView, GetDesktopWindow());
		CPDDocument* pDocument = (CPDDocument*)m_document;

//		::MessageBox(NULL, "Destroy Window", "", MB_OK);

// Destroy frame
	pDocument->m_pInPlaceFrame->DestroyWindow();//ShowWindow(SW_HIDE);
	pDocument->m_pInPlaceFrame->Release();
	pDocument->m_pInPlaceFrame = NULL;
	
	return S_OK;
}

HRESULT CPDDocumentView::ActivateUI()
{
//	::MessageBox(NULL, "ActivateUI", "", MB_OK);
//	OutputDebugString(TEXT("COleDocumentView::ActivateUI\n"));
	
/*	if (m_spInPlaceSite)
	{
		RECT  rcClip;
		m_FrameInfo.cb = sizeof(m_FrameInfo);

		CComPtr<IOleInPlaceFrame> spInPlaceFrame;
		CComPtr<IOleInPlaceUIWindow> spInPlaceUIWindow;

		m_spInPlaceSite->GetWindowContext(
			&spInPlaceFrame,
			&spInPlaceUIWindow,
			&m_rect,
			&rcClip,
			&m_FrameInfo);

		m_spInPlaceFrame = spInPlaceFrame;
		m_spInPlaceUIWindow = spInPlaceUIWindow;
	}
*/
	//set the active object
	//either one of these could be good
/*
	if (m_spInPlaceUIWindow)
	{
		m_spInPlaceUIWindow->SetActiveObject(this, NULL);
	}
*/
	if (m_spInPlaceFrame)
	{
		m_spInPlaceFrame->SetActiveObject(this, NULL);
	}

	if (m_spInPlaceUIWindow)
	{
		m_spInPlaceUIWindow->SetActiveObject(this, NULL);
	}

	if(m_spInPlaceSite)
	{
		m_fUIActive = TRUE;
		
		if (!m_fInPlaceActive)
			ActivateInPlace();
	
		m_spInPlaceSite->OnUIActivate();
		
		MergeMenus();
		
		SetFocus(/*m_hwndView*/);
	}
	
	return S_OK;
}

HRESULT CPDDocumentView::DeactivateUI()
{
//	OutputDebugString(TEXT("COleDocumentView::DeactivateUI\n"));
	
	m_fUIActive = FALSE;
	
//	RemoveMenus();

	/*
	if (m_spInPlaceSite)
	{
		RECT  rcClip;
		m_FrameInfo.cb = sizeof(m_FrameInfo);

		CComPtr<IOleInPlaceFrame> spInPlaceFrame;
		CComPtr<IOleInPlaceUIWindow> spInPlaceUIWindow;

		m_spInPlaceSite->GetWindowContext(
			&spInPlaceFrame,
			&spInPlaceUIWindow,
			&m_rect,
			&rcClip,
			&m_FrameInfo);

		m_spInPlaceFrame = spInPlaceFrame;
		m_spInPlaceUIWindow = spInPlaceUIWindow;
	}
	*/

	//remove the active object
	//either one of these could be good
	if (m_spInPlaceFrame)
	{
		m_spInPlaceFrame->SetActiveObject(NULL, NULL);
	}

	if (m_spInPlaceUIWindow)
	{
		m_spInPlaceUIWindow->SetActiveObject(NULL, NULL);
	}

	if (m_spInPlaceSite)
	{
		m_spInPlaceSite->OnUIDeactivate(FALSE);
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Implementation helpers

/*
HRESULT WINAPI myfunc(void* pv, REFIID riid, LPVOID* ppv, DWORD dw)
{
	CPDDocumentView* pView = (CPDDocumentView*)pv;

	::MessageBox(NULL, "func", "", MB_OK);
	return pView->m_document->QueryInterface(riid, ppv);
}
*/

// IOleDocumentView

HRESULT STDMETHODCALLTYPE CPDDocumentView::SetInPlaceSite( 
   /* [unique][in] */ IOleInPlaceSite __RPC_FAR *pIPSite)
{
	m_spInPlaceSite = pIPSite;

	if (m_spInPlaceSite)
	{
		RECT  rcClip;
		m_FrameInfo.cb = sizeof(m_FrameInfo);

		CComPtr<IOleInPlaceFrame> spInPlaceFrame;
		CComPtr<IOleInPlaceUIWindow> spInPlaceUIWindow;

		m_spInPlaceSite->GetWindowContext(
			&spInPlaceFrame,
			&spInPlaceUIWindow,
			&m_rect,
			&rcClip,
			&m_FrameInfo);

		m_spInPlaceFrame = spInPlaceFrame;
		m_spInPlaceUIWindow = spInPlaceUIWindow;
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::GetInPlaceSite( 
   /* [out] */ IOleInPlaceSite __RPC_FAR *__RPC_FAR *ppIPSite)
{
	if (ppIPSite == NULL) return E_POINTER;
	*ppIPSite = m_spInPlaceSite;
	if (*ppIPSite) (*ppIPSite)->AddRef();

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::GetDocument( 
   /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk)
{
	if (ppunk == NULL) return E_POINTER;
	*ppunk = m_document;
	if (*ppunk) (*ppunk)->AddRef();

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::SetRect(/* [in] */ LPRECT prcView)
{
	ATLTRACE("CPDDocumentView::SetRect()...");
	CPDDocument* pDocument = (CPDDocument*)m_document;

	m_rect = *prcView;

	if (pDocument->m_pInPlaceFrame)
	{
	//	::MessageBox(NULL, "size", "", MB_OK);

		pDocument->m_pInPlaceFrame->MoveWindow(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), TRUE);
	}
	/*
	if (m_hWnd)
	{
		MoveWindow(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), TRUE);
	}
	*/

	ATLTRACE("...CPDDocumentView::SetRect()\n");

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::GetRect(/* [out] */ LPRECT prcView)
{
	if (prcView == NULL) return E_POINTER;
	*prcView = m_rect;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::SetRectComplex( 
   /* [unique][in] */ LPRECT prcView,
   /* [unique][in] */ LPRECT prcHScroll,
   /* [unique][in] */ LPRECT prcVScroll,
   /* [unique][in] */ LPRECT prcSizeBox)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::Show(/* [in] */ BOOL bShow)
{
	if(bShow)
	{
		//if the object is not in-place active, make it that way
		if(!m_fInPlaceActive)
			ActivateInPlace();
		
		CPDDocument* pDocument = (CPDDocument*)m_document;
		//show the window
		pDocument->m_pInPlaceFrame->BringWindowToTop(/*m_hwndView*/);
		pDocument->m_pInPlaceFrame->ShowWindow(/*m_hwndView, */SW_SHOW);
		pDocument->m_pInPlaceFrame->UpdateWindow(/*m_hwndView*/);
	}
	else
	{
		//if the object is UI active, make remove that state
		if(m_fUIActive)
			DeactivateUI();
		
		//hide the window
	CPDDocument* pDocument = (CPDDocument*)m_document;
		pDocument->m_pInPlaceFrame->ShowWindow(SW_HIDE);
	}

	return S_OK;
}

STDMETHODIMP CPDDocumentView::UIActivate(/* [in] */ BOOL bActivate)
{
/*
if (fActivate)
    {
    UI activate the view (do menu merging, show frame level tools, process accelerators)
    Take focus, and bring the view window forward.
    }
else
    call IOleInPlaceObject::UIDeactivate on this view

*/
	if(bActivate)
	{
		return ActivateUI();
	}
	else
	{
		return DeactivateUI();
	}
/*
	if (fUIActivate)
	{
		MessageBox("UIActivate", "", MB_OK);

		CComPtr<IOleInPlaceFrame> pFrame;
		CComPtr<IOleInPlaceUIWindow> pDocView;
		CRect rcPos;
		CRect rcClip;
		OLEINPLACEFRAMEINFO fi;
		m_spInPlaceSite->GetWindowContext(&pFrame, &pDocView, &rcPos, &rcClip, &fi);

		HWND hWndParent;
		pDocView->GetWindow(&hWndParent);

		CWindowImpl<CPDDocumentView>::Create(hWndParent, m_rect, NULL, WS_CHILD | WS_VISIBLE, 0, 0);
	}
	else
	{
		UIDeactivate();
	}
*/
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::Open(void)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::CloseView(DWORD dwReserved)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::SaveViewState( 
   /* [in] */ LPSTREAM pstm)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::ApplyViewState( 
   /* [in] */ LPSTREAM pstm)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::Clone( 
   /* [in] */ IOleInPlaceSite __RPC_FAR *pIPSiteNew,
   /* [out] */ IOleDocumentView __RPC_FAR *__RPC_FAR *ppViewNew)
{
	return S_OK;
}

// IOleWindow
HRESULT STDMETHODCALLTYPE CPDDocumentView::GetWindow( 
            /* [out] */ HWND __RPC_FAR *phwnd)
{
	if (phwnd == NULL) return E_POINTER;
	*phwnd = m_hWnd;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::ContextSensitiveHelp( 
            /* [in] */ BOOL fEnterMode)
{
	return S_OK;
}

// IOleInPlaceObject
HRESULT STDMETHODCALLTYPE CPDDocumentView::InPlaceDeactivate( void)
{
//	::MessageBox(NULL, "CPDDocumentView::InPlaceDeactivate", "", MB_OK);
	return DeactivateInPlace();
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::UIDeactivate( void)
{
//	::MessageBox(NULL, "CPDDocumentView::UIDeactivate", "", MB_OK);
	DeactivateUI();
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::SetObjectRects( 
            /* [in] */ LPCRECT lprcPosRect,
            /* [in] */ LPCRECT lprcClipRect)
{
	CPDDocument* pDocument = (CPDDocument*)m_document;

	m_rect = *lprcPosRect;

	if (pDocument->m_pInPlaceFrame)
	{
		pDocument->m_pInPlaceFrame->MoveWindow(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), TRUE);
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::ReactivateAndUndo( void)
{
	return S_OK;
}

// IOleInPlaceActiveObject
STDMETHODIMP CPDDocumentView::TranslateAccelerator( 
            /* [in] */ LPMSG lpmsg)
{
	// no accelerator table, return FALSE
	return S_FALSE;
}

STDMETHODIMP CPDDocumentView::OnFrameWindowActivate( 
           /* [in] */ BOOL fActivate)
{
	return S_OK;
}

STDMETHODIMP CPDDocumentView::OnDocWindowActivate( 
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

STDMETHODIMP CPDDocumentView::ResizeBorder( 
            /* [in] */ LPCRECT prcBorder,
            /* [unique][in] */ IOleInPlaceUIWindow *pUIWindow,
            /* [in] */ BOOL fFrameWindow)
{
// TODO
	return S_OK;
}

STDMETHODIMP CPDDocumentView::EnableModeless(/* [in] */ BOOL fEnable)
{
//	m_fEnableModeless = fEnable;

	return S_OK;
}

// IPrint

HRESULT STDMETHODCALLTYPE CPDDocumentView::SetInitialPageNum( 
   /* [in] */ LONG nFirstPage)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::GetPageInfo( 
   /* [out] */ LONG __RPC_FAR *pnFirstPage,
   /* [out] */ LONG __RPC_FAR *pcPages)
{
	return S_OK;
}

/* [local] */ HRESULT __stdcall CPDDocumentView::Print( 
   /* [in] */ DWORD grfFlags,
   /* [out][in] */ DVTARGETDEVICE __RPC_FAR *__RPC_FAR *pptd,
   /* [out][in] */ PAGESET __RPC_FAR *__RPC_FAR *ppPageSet,
   /* [unique][out][in] */ STGMEDIUM __RPC_FAR *pstgmOptions,
   /* [in] */ IContinueCallback __RPC_FAR *pcallback,
   /* [in] */ LONG nFirstPage,
   /* [out] */ LONG __RPC_FAR *pcPagesPrinted,
   /* [out] */ LONG __RPC_FAR *pnLastPage)
{
	return S_OK;
}

// IOleCommandTarget

HRESULT STDMETHODCALLTYPE CPDDocumentView::QueryStatus( 
   /* [unique][in] */ const GUID __RPC_FAR *pguidCmdGroup,
   /* [in] */ ULONG cCmds,
   /* [out][in][size_is] */ OLECMD __RPC_FAR prgCmds[  ],
   /* [unique][out][in] */ OLECMDTEXT __RPC_FAR *pCmdText)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPDDocumentView::Exec(
   /* [unique][in] */ const GUID __RPC_FAR *pguidCmdGroup,
   /* [in] */ DWORD nCmdID,
   /* [in] */ DWORD nCmdexecopt,
   /* [unique][in] */ VARIANT __RPC_FAR *pvaIn,
   /* [unique][out][in] */ VARIANT __RPC_FAR *pvaOut)
{
	return S_OK;
}

// ICommandTarget
STDMETHODIMP CPDDocumentView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
	static int n = 0;
	if (n == 0)
	{
		n++;

		ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) goto Exit;

	// Try document
		{
			CComQIPtr<ICommandTarget> target = m_document;
			target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
			if (*bHandled) goto Exit;
		}

		if (m_fInPlaceActive)
		{
			CPDDocument* pDocument = (CPDDocument*)m_document;
			if (pDocument->m_pInPlaceFrame)
			{
				CComQIPtr<ICommandTarget> target = pDocument->m_pInPlaceFrame;
				target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
				if (*bHandled) goto Exit;
			}
		}

Exit:
		n--;
	}

	return S_OK;
}
