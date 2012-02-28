#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDAppearance.h"
#include "PDFilterPrimitive.h"
#include "ObjectMap.h"

void CPDFilterPrimitive::SetupEffectRecord()
{
#if 0
//	ASSERT(IsValid());

	ASSERT(m_effectRecord);
/*
	CComposition* pComp = NULL;

	if (GetLayerComp())
	{
		pComp = (CComposition*)TARGETDATA(GetLayerComp()->m_targetRef, IID_2DCOMP);
	}

	if (pComp)
*/	{
		ASSERT(pComp->IsValid());

//		m_effectRecord->currentFrame = (pComp->GetAbsFrame()-1);
//		m_effectRecord->frameRate = (long)(pComp->GetFrameRate()*65536);

//		m_effectRecord->currentLayerFrame = (pComp->GetAbsFrame()-1 - GetAbsStartFrame(NULL));

//		m_effectRecord->totalFrames = (pComp->GetAbsFrame()-1);

	//	CComposition* pComp = (CComposition*)GetComposition();
		long x_sampling = 65536;//pComp->m_XSampling;
		long y_sampling = 65536;//pComp->m_YSampling;
		double xsampling = x_sampling/65536.0;
		double ysampling = y_sampling/65536.0;

		int width = GetWidth();
		int height = GetHeight();
	//	m_effectRecord->sourceWidth = width;	// Don't set this here ?
		m_effectRecord->sourceHeight = height;	// Don't set this here ?

		m_effectRecord->x_sampling = x_sampling;
		m_effectRecord->y_sampling = y_sampling;
	}
//	else
	{
//		AfxMessageBox("No comp");
	}

//	m_effectRecord->quality = GetQuality();
//	m_effectRecord->bTransferTo = GetTransferTo();
#endif
}

//////////////////
// CPDAppearance

int CPDAppearance::FinalConstruct()
{
	HRESULT hr;

	hr = CComObject<CObjectMap>::CreateInstance(&m_children);
	if (FAILED(hr)) return hr;
	m_children->AddRef();

	CComObject<CPDFilterPrimitive>::CreateInstance(&m_cItems[0]);
	m_cItems[0]->AddRef();
	m_cItems[0]->m_name = L"Source Graphic";
	m_cItems[0]->m_type = IN_SOURCEGRAPHIC;

	CComObject<CPDFilterPrimitive>::CreateInstance(&m_cItems[1]);
	m_cItems[1]->AddRef();
	m_cItems[1]->m_name = L"Source Alpha";
	m_cItems[1]->m_type = IN_SOURCEALPHA;

	CComObject<CPDFilterPrimitive>::CreateInstance(&m_cItems[2]);
	m_cItems[2]->AddRef();
	m_cItems[2]->m_name = L"Background Graphic";
	m_cItems[2]->m_type = IN_BACKGROUNDGRAPHIC;

	CComObject<CPDFilterPrimitive>::CreateInstance(&m_cItems[3]);
	m_cItems[3]->AddRef();
	m_cItems[3]->m_name = L"Background Alpha";
	m_cItems[3]->m_type = IN_BACKGROUNDALPHA;

	CComObject<CPDFilterPrimitive>::CreateInstance(&m_cItems[4]);
	m_cItems[4]->AddRef();
	m_cItems[4]->m_name = L"Source Path";
	m_cItems[4]->m_type = -5;

	return S_OK;
}

void CPDAppearance::FinalRelease()
{
	if (m_children)
	{
		m_children->Release();
		m_children = NULL;
	}
}

/*
 
RULE: (??)
	If an effect takes more than 1 input, all input images are of
	same size and have same origin in coordinate space

  The output however is different size/origin than input(s) only if
  effect sets r->out_newwidth/newheight

*/

/*
class CFilter
{
public:
	IPDFilterPrimitive* pLayer;
};
*/

BOOL CPDAppearance::SetupChildrenLayers(IPDObjectWithAppearance* refObject)
{
	RectD sourceBounds;
	refObject->get_filterRect(&sourceBounds);

	double sourceWidth = ceil(sourceBounds.Width);
	double sourceHeight = ceil(sourceBounds.Height);

	m_expandedRect = sourceBounds;

// Go through effect children to see if anyone of them wants to expand
// this layers image

	m_cItems[0]->m_effectRecord->out_newwidth = sourceWidth;
	m_cItems[0]->m_effectRecord->out_newheight = sourceHeight;
	m_cItems[0]->m_out_origin_x = 0;
	m_cItems[0]->m_out_origin_y = 0;

	m_cItems[1]->m_effectRecord->out_newwidth = sourceWidth;
	m_cItems[1]->m_effectRecord->out_newheight = sourceHeight;
	m_cItems[1]->m_out_origin_x = 0;
	m_cItems[1]->m_out_origin_y = 0;

	m_cItems[2]->m_effectRecord->out_newwidth = sourceWidth;
	m_cItems[2]->m_effectRecord->out_newheight = sourceHeight;
	m_cItems[2]->m_out_origin_x = 0;
	m_cItems[2]->m_out_origin_y = 0;

//	int in_pre_effect_source_origin_x = 0;	// Keep a running value of this
//	int in_pre_effect_source_origin_y = 0;

	CComPtr<IPDFilterPrimitive> layer = m_firstChild;
	while (layer)
	{
		CComPtr<IPDFilterPrimitive> nextLayer;
		layer->get_nextSibling(&nextLayer);

		CPDFilterPrimitive* pLayer = static_cast<CPDFilterPrimitive*>(layer.p);

		if (TRUE/*pLayer->TOP()->HasImage() && pLayer->IsVideoEnabled()*/)
		{
			LPPFILTERRECORD r = pLayer->m_effectRecord;
			ASSERT(r);

			int inputWidth = 0;
			int inputHeight = 0;

			pLayer->m_in_origin_x = 0;
			pLayer->m_in_origin_y = 0;

			pLayer->m_out_origin_x = 0;
			pLayer->m_out_origin_y = 0;

			int hadInput = 0;

		// Get the input size for this effect, which is the maximum of all
		// the input pins (?)

			for (int pin = 0; pin < pLayer->GetInPinCount(); pin++)
			{
				CComPtr<IPDFilterPrimitive> inLayer = pLayer->GetInPin(pin);
				CPDFilterPrimitive* pInLayer = static_cast<CPDFilterPrimitive*>(inLayer.p);
				if (pInLayer)
				{
					int inWidth = 0;
					int inHeight = 0;

						// Takes as input image the output of another effect
					{		// which must already have been processed 
						inWidth = pInLayer->m_effectRecord->out_newwidth;
						inHeight = pInLayer->m_effectRecord->out_newheight;

						pLayer->m_in_origin_x = min(pLayer->m_in_origin_x, pInLayer->m_out_origin_x);
						pLayer->m_in_origin_y = min(pLayer->m_in_origin_y, pInLayer->m_out_origin_y);
					}

					inputWidth = max(inputWidth, inWidth);
					inputHeight = max(inputHeight, inHeight);

					hadInput++;
				}
			}

		// Go on if either the effect doesn't need any input
		// or we actually found some input for it
			if (pLayer->GetInPinCount() == hadInput)
			{
				pLayer->SetupEffectRecord();

				r->sourceWidth = sourceWidth;	// This never changes
				r->sourceHeight = sourceHeight;

				r->inputWidth = inputWidth;
				r->inputHeight = inputHeight;
			//	r->inputWidth = m_expandedRect.right-m_expandedRect.left+1;
			//	r->inputHeight = m_expandedRect.right-m_expandedRect.left+1;

			// The effect can reset these, but defaults to same size as input
			// Set a default origin based on input images origins ??
				r->out_x_origin = 0;
				r->out_y_origin = 0;
				r->out_newwidth = r->inputWidth;
				r->out_newheight = r->inputHeight;

			//  DO IT!!!
				pLayer->m_pluginFilter->FrameSetup((DWORD)pLayer->m_effectRecord);

				/*
				m_expandedRect.right += r->out_newwidth - r->inputWidth;
				m_expandedRect.bottom += r->out_newheight - r->inputHeight;
				m_expandedRect.OffsetRect(-r->out_x_origin, -r->out_y_origin);
				*/
				m_expandedRect.Width += r->out_newwidth - r->inputWidth;
				m_expandedRect.Height += r->out_newheight - r->inputHeight;
				m_expandedRect.X += -r->out_x_origin;
				m_expandedRect.Y += -r->out_y_origin;

				pLayer->m_out_origin_x = pLayer->m_in_origin_x - r->out_x_origin;
				pLayer->m_out_origin_y = pLayer->m_in_origin_y - r->out_y_origin;
			}
		}

		layer = nextLayer;
	}

	return TRUE;
}

#include "PDLayer.h"
#include "PDObjectImpl.h"

int AddFlatCurve(CArray<CDblPoint,CDblPoint>& pointsArr, double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double& oldxt, double& oldyt);

// Returns the result image

Gdiplus::Bitmap* CPDAppearance::ProcessEffects(IPDObjectWithAppearance* refObjectWithAppearance, double scaleX, double scaleY)
{
	RectD sourceBounds;
	refObjectWithAppearance->get_filterRect(&sourceBounds);

	long sourceWidth = ceil(sourceBounds.Width);
	long sourceHeight = ceil(sourceBounds.Height);

	if (sourceWidth <= 0 || sourceHeight <= 0) return NULL;

	long scaledWidth = ceil(sourceBounds.Width * scaleX);
	long scaledHeight = ceil(sourceBounds.Height * scaleY);

	if (m_cItems[0]->m_effectRecord->outImage)
	{
		delete m_cItems[0]->m_effectRecord->outImage;
		m_cItems[0]->m_effectRecord->outImage = NULL;
	}

	m_cItems[0]->m_effectRecord->outImage = new Gdiplus::Bitmap(scaledWidth, scaledHeight);
	if (m_cItems[0]->m_effectRecord->outImage)
	{
		Gdiplus::Graphics graphics(m_cItems[0]->m_effectRecord->outImage);
		
	//	graphics.TranslateTransform(-sourceBounds.X, -sourceBounds.Y);
		graphics.ScaleTransform(scaleX, scaleY);
		graphics.TranslateTransform(-sourceBounds.X, -sourceBounds.Y);

		refObjectWithAppearance->Render2((DWORD)m_cItems[0]->m_effectRecord->outImage, (DWORD)&graphics, scaleX, scaleY);
	}

	Gdiplus::BitmapData sourceGraphicData;
	m_cItems[0]->m_effectRecord->outImage->LockBits(
		&Gdiplus::Rect(0, 0, scaledWidth, scaledHeight),
		Gdiplus::ImageLockModeRead,
		PixelFormat32bppARGB, &sourceGraphicData);

// Source Alpha
	if (m_cItems[1]->m_effectRecord->outImage)
	{
		delete m_cItems[1]->m_effectRecord->outImage;
		m_cItems[1]->m_effectRecord->outImage = NULL;
	}

	m_cItems[1]->m_effectRecord->outImage = new Gdiplus::Bitmap(scaledWidth, scaledHeight);
	if (m_cItems[1]->m_effectRecord->outImage)
	{
		Gdiplus::BitmapData sourceAlphaData;
		m_cItems[1]->m_effectRecord->outImage->LockBits(
			&Gdiplus::Rect(0, 0, scaledWidth, scaledHeight),
			Gdiplus::ImageLockModeWrite,
			PixelFormat32bppARGB, &sourceAlphaData);

	// Copy the alpha only from sourceGraphic
		for (int y = 0; y < scaledHeight; y++)
		{
			ARGBPixel* s = (ARGBPixel*)((BYTE*)sourceGraphicData.Scan0 + sourceGraphicData.Stride*y);
			ARGBPixel* d = (ARGBPixel*)((BYTE*)sourceAlphaData.Scan0 + sourceAlphaData.Stride*y);

			for (int x = 0; x < scaledWidth; x++)
			{
				d->red = 0;
				d->green = 0;
				d->blue = 0;
				d->alpha = s->alpha;

				s++;
				d++;
			}
		}

		m_cItems[1]->m_effectRecord->outImage->UnlockBits(&sourceAlphaData);
	}

	m_cItems[0]->m_effectRecord->outImage->UnlockBits(&sourceGraphicData);

// TODO. Background-Image
	{
		CComQIPtr<IPDObject> refObject = refObjectWithAppearance;

		CComQIPtr<IPDObject> objectWithBg;

		CComQIPtr<IPDObjectUnknown> parent = refObject;
		do
		{
			CComPtr<IPDObjectUnknown> parent2;
			parent->get_parent(&parent2);
			parent = parent2;

			CComQIPtr<IPDObjectGroup> parentGroup = parent;
			if (parentGroup)
			{
				long enableBackground;
				parentGroup->get_enableBackground(&enableBackground);
				if (enableBackground == 1)	// New
				{
					objectWithBg = parent;
					break;
				}
			}
		}
		while (parent);

		if (objectWithBg)
		{
			CPDObjectImpl<IPDObject>* pObjectWithBg = static_cast<CPDObjectImpl<IPDObject>*>(objectWithBg.p);

			m_cItems[2]->m_effectRecord->outImage = new Gdiplus::Bitmap(scaledWidth, scaledHeight);
			if (m_cItems[2]->m_effectRecord->outImage)
			{
				Gdiplus::Graphics graphics(m_cItems[2]->m_effectRecord->outImage);

				Gdiplus::RectF destRect(0, 0, scaledWidth, scaledHeight);

			//	graphics.TranslateTransform();

				
				graphics.DrawImage(
					pObjectWithBg->m_backgroundBitmap,

					destRect,
					(float)(sourceBounds.X-pObjectWithBg->m_filterRect.X), (float)(sourceBounds.Y-pObjectWithBg->m_filterRect.Y),
					destRect.Width, destRect.Height,
					Gdiplus::UnitPixel);
			}
		}
	}

// TODO. Background-Alpha
	{
	}

// TODO. Fill
	{
	}

// TODO. Stroke
	{
	}

// Source Path
	{
		if (FALSE)
		{
			CComQIPtr<IPDObjectFrame> objectFrame = refObjectWithAppearance;
			if (objectFrame)
			{
				CComPtr<IPDPath> path;
				objectFrame->get_path(&path);

				long nsubpaths;
				path->get_subPathCount(&nsubpaths);

				int ntotalpoints = 0;

				for (long nsubpath = 0; nsubpath < nsubpaths; nsubpath++)
				{
					CComPtr<IPDSubPath> subpath;
					path->getSubPath(nsubpath, &subpath);

					VARIANT_BOOL closed;
					subpath->get_closed(&closed);

					long npoints;
					subpath->get_pointCount(&npoints);

					int count = 0;

					if (npoints > 0)
					{
						double oldxt = -99999;
						double oldyt = -99999;

						BezierPoint seg0;
						subpath->getPoint(0, &seg0);

						BezierPoint _seg0 = seg0;
						for (long i = 1; i < npoints; i++)
						{
							BezierPoint seg;
							subpath->getPoint(i, &seg);

							count += AddFlatCurve(
								m_cItems[4]->m_flatPoints,
								seg0.x, seg0.y,
								seg0.x2, seg0.y2,
								seg.x1, seg.y1,
								seg.x, seg.y,
								oldxt, oldyt);

							seg0 = seg;
						}

						if (closed)
						{
							count += AddFlatCurve(
								m_cItems[4]->m_flatPoints,
								seg0.x, seg0.y,
								seg0.x2, seg0.y2,
								_seg0.x1, _seg0.y1,
								_seg0.x, _seg0.y,
								oldxt, oldyt);
						}

						m_cItems[4]->m_subPoints.Add(count);
					}
				}

				m_cItems[4]->m_effectRecord->numSubPoints = m_cItems[4]->m_subPoints.GetSize();
				m_cItems[4]->m_effectRecord->subPoints = m_cItems[4]->m_subPoints.GetData();
				m_cItems[4]->m_effectRecord->numPoints = m_cItems[4]->m_flatPoints.GetSize();
				m_cItems[4]->m_effectRecord->pointData = m_cItems[4]->m_flatPoints.GetData();
			}
		}
	}

	Gdiplus::Bitmap* resultImage = m_cItems[0]->m_effectRecord->outImage;	// Default to this if no effects

// Process all effects
	CComPtr<IPDFilterPrimitive> layer = m_firstChild;
	while (layer)
	{
		CComPtr<IPDFilterPrimitive> nextLayer;
		layer->get_nextSibling(&nextLayer);

		CPDFilterPrimitive* pLayer = static_cast<CPDFilterPrimitive*>(layer.p);

		if (TRUE/*pLayer->TOP()->HasImage()*/)
		{
			LPPFILTERRECORD r = pLayer->m_effectRecord;
			ASSERT(r);

			CPDFilterPrimitive* pEffectIn[4];

			int newWidth = r->out_newwidth;
			int newHeight = r->out_newheight;

			int hadInput = 0;

			for (int pin = 0; pin < pLayer->GetInPinCount(); pin++)
			{
				pEffectIn[pin] = static_cast<CPDFilterPrimitive*>(pLayer->GetInPin(pin));
				CPDFilterPrimitive* pInLayer = pEffectIn[pin];

				r->inPinImage[pin] = NULL;

				if (pEffectIn[pin])
				{
					int origin_x = 0;
					int origin_y = 0;

					Gdiplus::Bitmap* pInImage = NULL;

						// Takes as input image the output of another effect
					{		// which must already have been processed 
						//ASSERT(pEffectIn[pin]->IsValid());

						pInImage = pEffectIn[pin]->m_effectRecord->outImage;

						if (pInImage)
						{
							ASSERT(pInImage);

							ASSERT(pEffectIn[pin]->m_effectRecord);

							origin_x = pEffectIn[pin]->m_out_origin_x;
							origin_y = pEffectIn[pin]->m_out_origin_y;
						}
					}

					if (pInImage)
					{
					// Input width/height was calculated in SetupChildrenLayers()
					// All inputs must have equal size

						Gdiplus::Bitmap* pPinInImage = new Gdiplus::Bitmap(r->inputWidth, r->inputHeight, PixelFormat32bppARGB);
						int srcx = origin_x - pLayer->m_in_origin_x;
						int srcy = origin_y - pLayer->m_in_origin_y;

						ASSERT(srcx >= 0);
						ASSERT(srcy >= 0);

					// All inputs must be aligned
						// Translate the input image to correct origin
						/*
						pInImage->CopyImage(
							0, 0, pInImage->width, pInImage->height,
							pPinInImage,
							srcx, srcy);
						*/

						{
							Gdiplus::Graphics graphics(pPinInImage);
							graphics.DrawImage(pInImage, srcx, srcy);
						}

						r->inPinImage[pin] = pPinInImage;

						hadInput++;
					}
				}
			}

			if (r->outImage)
			{
				delete r->outImage;
				//r->outImage->Release();
				r->outImage = NULL;
			}

			ASSERT(r->outImage == NULL);

			if (pLayer->GetInPinCount() == hadInput)
			{
				r->outImage = new Gdiplus::Bitmap(newWidth, newHeight, PixelFormat32bppARGB);
				if (r->outImage)
				{
					pLayer->SetupEffectRecord();

					int width = newWidth;
					int height = newHeight;
					int sampledWidth = width;//GetSampledValue(width, xsampling);
					int sampledHeight = height;//GetSampledValue(height, ysampling);

					r->sourceWidth = sourceWidth;
					r->sourceHeight = sourceHeight;

					//r->imode = IMODE_ARGB8;

					r->inImage = r->inPinImage[0];
					if (r->inImage)
					{
					// should have this for each inputimage, not just first

					// we can save some time here, only do if filter wants it
					// (in case of AEEffects, this means always, but that's
					// the AEAdapter's work to let us know...
						/*
						if (pLayer->m_pFilter->TOP()->GetVideoFlags() & EFFECT_FLG_I_USE_ALPHA)
						{
							r->inImage->GetAlphaBounds(&r->aRect);// = pLayer->m_effectRecord->uRect;
						}
						*/
					}

					int destleft = 0;
					int desttop = 0;
					int destright = r->outImage->GetWidth()-1;
					int destbottom = r->outImage->GetHeight()-1;

					r->boffset_x = destleft;
					r->boffset_y = desttop;

					r->uRect.left = destleft;
					r->uRect.top = desttop;
					r->uRect.right = destright;
					r->uRect.bottom = destbottom;

					//DWORD starttick = GetTickCount();
					pLayer->m_pluginFilter->Filter((DWORD)r);
					//pLayer->m_processTime = GetTickCount() - starttick;

				// The result image is the output of the last image processed
					resultImage = r->outImage;
				}
				else
				{
				//	r->outImage->Release();
				//	r->outImage = NULL;
					break;
				}
			}
		}
		layer = nextLayer;
	}
/*
// Free temporary output images
	pos = GetEffects()->GetFirstChildPos();
	while (pos)
	{
		CAdjustLayer* pLayer = (CAdjustLayer*)GetEffects()->GetNextChild(&pos);
		pLayer = (CAdjustLayer*)TARGETDATA(pLayer->m_targetRef, "EffectContainer");
		ASSERT(pLayer);
		if (pLayer)
		{
			LPPFILTERRECORD r = pLayer->m_effectRecord;
			ASSERT(r);

			if (r->outImage)
			{
				if (r->outImage != resultImage)	// Don't release the result image
				{
					r->outImage->Release();
				}

				r->outImage = NULL;
			}
		}
	}

	pSourceAlpha->Release();
*/
//	resultImage->AddRef();

	layer = m_firstChild;
	while (layer)
	{
		CPDFilterPrimitive* pLayer = static_cast<CPDFilterPrimitive*>(layer.p);

		if (pLayer->m_effectRecord->outImage == resultImage)
		{
			pLayer->m_effectRecord->outImage = NULL;
		}

		CComPtr<IPDFilterPrimitive> nextLayer;
		layer->get_nextSibling(&nextLayer);
		layer = nextLayer;
	}

	if (m_cItems[0]->m_effectRecord->outImage == resultImage)
	{
		m_cItems[0]->m_effectRecord->outImage = NULL;
	}

	if (m_cItems[0]->m_effectRecord->outImage)
	{
		delete m_cItems[0]->m_effectRecord->outImage;
		m_cItems[0]->m_effectRecord->outImage = NULL;
	}

	if (m_cItems[1]->m_effectRecord->outImage)
	{
		delete m_cItems[1]->m_effectRecord->outImage;
		m_cItems[1]->m_effectRecord->outImage = NULL;
	}

	if (m_cItems[2]->m_effectRecord->outImage)
	{
		delete m_cItems[2]->m_effectRecord->outImage;
		m_cItems[2]->m_effectRecord->outImage = NULL;
	}

	if (m_cItems[3]->m_effectRecord->outImage)
	{
		delete m_cItems[3]->m_effectRecord->outImage;
		m_cItems[3]->m_effectRecord->outImage = NULL;
	}

	return resultImage;
}

STDMETHODIMP CPDAppearance::get_filterEffects(IObjectMap* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	(*pVal = m_children)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDAppearance::get_firstChild(IPDFilterPrimitive* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_firstChild;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDAppearance::get_lastChild(IPDFilterPrimitive* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_lastChild;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDAppearance::insertEffect(IPDFilterPrimitive* object, IPDFilterPrimitive* before)
{
//	CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>(object);
//	CPDObjectImpl<IPDObject>* pBefore = static_cast<CPDObjectImpl<IPDObject>*>(before);

	object->AddRef();

	/*
	ATLASSERT(pObject->m_pDocument == m_pDocument);
	if (pObject->m_pDocument != m_pDocument)
	{
		MessageBox(NULL, "Cannot insert object across documents", "", MB_OK);
		return E_FAIL;
	}
	*/

/*
	CComPtr<IPDObjectUnknown> parent;
	object->get_parent(&parent);

// First remove it from previous parent
	if (parent)
	{
		parent->removeObject(object);
	}
*/
	CComPtr<IPDFilterPrimitive> after;

	if (before)
		before->get_previousSibling(&after);
	else
		get_lastChild(&after);

	object->put_nextSibling(before);
	object->put_previousSibling(after);

	if (after == NULL)
		m_firstChild = object;
	else
		after->put_nextSibling(object);

	if (before == NULL)
		m_lastChild = object;
	else
		before->put_previousSibling(object);

	/*
	{
		CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>(object);
		pObject->m_parent = static_cast<CPDObjectUnknownImpl<IPDObjectUnknown>*>((IPDObjectUnknown*)this);//static_cast<CComObject<CPDGradient>*>(this);
		pObject->attachToSpread(pObject->m_parent);
	}
	*/

	if (before)
	{
		for (int i = 0; i < m_children->m_items.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_children->m_items[i], before))
			{
				m_children->m_items.InsertAt(i, object);
				break;
			}
		}
	}
	else
	{
		m_children->m_items.Add(object);
	}

	{
		CComQIPtr<INotifySend> cp = object;
		DWORD cookie;
		cp->Advise(this, &cookie);
	}

	FireOnChanged(NOTIFY_ADD, object, DISPID_UNKNOWN);
/*
	CalculateBounds();
	if (m_pDocument)
	{
		m_pDocument->DistributeStories();

		m_pDocument->FireOnChanged(NOTIFY_ADD, object, IID_IPDObject, DISPID_UNKNOWN);
	}
*/
	return S_OK;
}

STDMETHODIMP CPDAppearance::removeEffect(/*[in]*/ IPDFilterPrimitive* object)
{
	if (object == NULL)
	{
		ATLASSERT(0);
		return E_POINTER;
	}

	for (int i = 0; i < m_children->m_items.GetSize(); i++)
	{
		if (IsUnknownEqualUnknown(m_children->m_items[i], object))
		{
			CComPtr<IPDFilterPrimitive> previousSibling;
			object->get_previousSibling(&previousSibling);

			CComPtr<IPDFilterPrimitive> nextSibling;
			object->get_nextSibling(&nextSibling);

			if (previousSibling != NULL)
				previousSibling->put_nextSibling(nextSibling);
			else
				m_firstChild = nextSibling;

			if (nextSibling != NULL)
				nextSibling->put_previousSibling(previousSibling);
			else
				m_lastChild = previousSibling;

			object->put_previousSibling(NULL);
			object->put_nextSibling(NULL);

			/*
			{
				CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>(object);
				pObject->m_parent = NULL;
				pObject->detachFromSpread();
			}
			*/

			object->Release();

			m_children->m_items.RemoveAt(i);
/*
			CalculateBounds();
			if (m_pDocument)
			{
				m_pDocument->DistributeStories();
			}
*/
			return S_OK;
		}
	}

	ATLASSERT(0);
	return E_FAIL;
}

// IObjectSerializable
STDMETHODIMP CPDAppearance::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	node->putObjectMap(L"filters", m_children);
	return S_OK;
}

STDMETHODIMP CPDAppearance::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	return S_OK;
}

STDMETHODIMP CPDAppearance::IsEqual(IPDAppearance *appearance)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDAppearance::clone(IPDAppearance **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDAppearance>* pAppearance;
	CComObject<CPDAppearance>::CreateInstance(&pAppearance);

	*pVal = pAppearance;
	(*pVal)->AddRef();

	return S_OK;
}
