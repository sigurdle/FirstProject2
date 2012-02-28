#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "ObjectMap.h"
#include "PDLayer.h"
#include "PDObjectShape.h"
#include "PDObjectGroup.h"
#include "PDDocument.h"
#include "PDPath.h"
#include "PDSubPath.h"
#include "PDContentGraphic.h"
#include "PDContentText.h"
#include "PDGradient.h"
#include "PDBrush.h"
#include "PDSpreadImpl.h"
#include "PDPathText.h"

#include "PDAppearance.h"

void CreateGradient(CArray<Gdiplus::REAL, Gdiplus::REAL>& offsets, CArray<Gdiplus::Color,Gdiplus::Color&>& colors, IPDGradient* gradient);

Gdiplus::Brush* GetSwatchGdiBrush(IPDSwatch* swatch)
{
	PDSwatchType swatchType;
	swatch->get_swatchType(&swatchType);

	Gdiplus::Brush* pBrush;

	if (swatchType == SWATCH_COLOR)
	{
		CComQIPtr<IPDSwatchColor> swatchColor = swatch;
		CComPtr<IPDColor> color;
		swatchColor->get_color(&color);
		double red; color->getChannel(0, &red);
		double green; color->getChannel(1, &green);
		double blue; color->getChannel(2, &blue);

		pBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, red, green, blue));
	}

	return pBrush;
}

Gdiplus::Brush* GetGdiBrush(IPDBrush* brush, PDBrushType brushType = BRUSH_NONE)
{
	Gdiplus::Brush* pBrush = NULL;

	if (brushType == BRUSH_NONE)
	{
		if (brush) brush->get_brushType(&brushType);
	}

	if (brushType == (PDBrushType)tomUndefined)
	{
	}
	else if (brushType == BRUSH_COLOR)
	{
		CComPtr<IPDColor> color;
		brush->get_tintedRGBColor(&color);
		if (color)
		{
			double red; color->getChannel(0, &red);
			double green; color->getChannel(1, &green);
			double blue; color->getChannel(2, &blue);

			pBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, red, green, blue));
		}
	}
	else if (brushType == BRUSH_GRADIENT)
	{
		CComPtr<IPDGradient> gradient;
		brush->get_gradient(&gradient);

		if (gradient)
		{
			PDGradientType gradientType;
			gradient->get_type(&gradientType);

			double x1; brush->get_x1(&x1);
			double y1; brush->get_y1(&y1);
			double x2; brush->get_x2(&x2);
			double y2; brush->get_y2(&y2);

			CArray<Gdiplus::REAL, Gdiplus::REAL> offsets;
			CArray<Gdiplus::Color,Gdiplus::Color&> colors;

			CreateGradient(offsets, colors, gradient);

			if (gradientType == GRADIENT_LINEAR)
			{
				Gdiplus::LinearGradientBrush* pGradBrush = new Gdiplus::LinearGradientBrush(
						Gdiplus::Point(x1, y1),
						Gdiplus::Point(x2, y2),
						Gdiplus::Color(0,0,0,0), Gdiplus::Color(0,0,0,0));
				pGradBrush->SetInterpolationColors(colors.GetData(), offsets.GetData(), colors.GetSize());

				pBrush = pGradBrush;
			}
			else if (gradientType == GRADIENT_RADIAL)
			{
				double dx = x2-x1;
				double dy = y2-y1;
				double radius = sqrt(dx*dx+dy*dy);

				Gdiplus::GraphicsPath path;
				path.AddEllipse((float)(x1-radius), (float)(y1-radius), (float)(x1+radius), (float)(y1+radius));

				Gdiplus::PathGradientBrush* pGradBrush = new Gdiplus::PathGradientBrush(&path);
				pGradBrush->SetInterpolationColors(colors.GetData(), offsets.GetData(), colors.GetSize());

				pBrush = pGradBrush;
			}
			else
				ATLASSERT(0);
		}
	}
	else if (brushType == BRUSH_PATTERN)
	{
		CComPtr<IPDSwatch> swatch;
		brush->get_swatch(&swatch);

		CComQIPtr<IPDSwatchPattern> swatchPattern = swatch;

		CComPtr<IPDObjectGroup> objectGroup;
		swatchPattern->get_objectGroup(&objectGroup);

		if (objectGroup)
		{
			CPDObjectGroup* pGroup = static_cast<CPDObjectGroup*>(objectGroup.p);

			RectD bounds;
			pGroup->get_bounds(&bounds);

			Gdiplus::Bitmap bitmap(bounds.Width, bounds.Height);
			{
				Gdiplus::Graphics graphics(&bitmap);
				//graphics.ScaleTransform(swatchRect.Width()/bounds.Width, swatchRect.Height()/bounds.Height);
				graphics.TranslateTransform(-bounds.X, -bounds.Y);

				pGroup->Render(NULL, &graphics, 1, 1/*TODO*/);
			}

			Gdiplus::TextureBrush* pTexBrush = new Gdiplus::TextureBrush(&bitmap);

			pBrush = pTexBrush;
		}
	}

	return pBrush;
}

#include "PDObjectStroke.h"
#include "PDObjectFill.h"

/////////////////////////
// CPDObjectShape

int CPDObjectFrame::FinalConstruct()
{
	HRESULT hr;

	hr = CPDObjectImpl<IPDObjectFrame>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CPDObjectWrappableImpl<CPDObjectFrame>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CPDObjectTransformableImpl<CPDObjectFrame>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CPDObjectWithAppearanceAndStrokeFillImpl<CPDObjectFrame>::FinalConstruct();
	if (FAILED(hr)) return hr;

	hr = CoCreateGuid(&m_uniqId);
	if (FAILED(hr)) return hr;

	DWORD cookie;

	hr = CComObject<CPDPath>::CreateInstance(&m_path);
	if (FAILED(hr)) return hr;
	m_path->AddRef();
	m_path->Advise(this, &cookie);

	return S_OK;
}

void CPDObjectFrame::FinalRelease()
{
	if (m_content)
	{
		CComQIPtr<INotifySend> cp = m_content;
		cp->Unadvise(this);
		// Release is done in CPDObjectImpl<IPDObjectFrame>::FinalRelease()

		CComQIPtr<IPDObjectText> objectText = m_content;
		if (objectText)
		{
			CComPtr<IPDStory> story;
			objectText->get_story(&story);

			story->removeTextThread(objectText);
		}
		
		m_content = NULL;
	}

	if (m_path)
	{
		m_path->Unadvise(this);
		m_path->Release();
		m_path = NULL;
	}

	CPDObjectWithAppearanceAndStrokeFillImpl<CPDObjectFrame>::FinalRelease();
	CPDObjectWrappableImpl<CPDObjectFrame>::FinalRelease();
	CPDObjectTransformableImpl<CPDObjectFrame>::FinalRelease();
	CPDObjectImpl<IPDObjectFrame>::FinalRelease();
}

STDMETHODIMP CPDObjectFrame::get_path(IPDPath **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_path;
	(*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CPDObjectFrame::put_path(IPDPath *newVal)
{
// possible (?)
	ATLASSERT(0);
	return E_FAIL;
	return S_OK;
}

Gdiplus::RectF	CPDObjectFrame::GetBounds()
{
	return Gdiplus::RectF(m_bounds.X, m_bounds.Y, m_bounds.Width, m_bounds.Height);
}

STDMETHODIMP CPDObjectFrame::IsPointOverStrokeOutline(PointD pt, BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = FALSE;

	Gdiplus::GraphicsPath path(Gdiplus::FillModeWinding);
	m_path->RenderToGraphicsPath(&path);

// Try all the strokes
	for (int i = 0; i < m_subObjects->m_items.GetSize(); i++)
	{
		CComQIPtr<IPDObjectStroke> stroke = m_subObjects->m_items[i];
		if (stroke)
		{
			CComQIPtr<IPDStrokeSettings> stroke2 = stroke;
			double strokeWeight;
			stroke2->get_strokeWeight(&strokeWeight);

			Gdiplus::Pen pen(Gdiplus::Color(255, 255, 255), strokeWeight);

			*pVal = path.IsOutlineVisible((float)pt.x, (float)pt.y, &pen, NULL /* graphics*/);
			if (*pVal)
			{
				break;
			}
		}
	}

	return S_OK;
}

void CPDObjectFrame::CalculateBounds()
{
	m_path->calculateBBox(NULL, &m_bounds);
	m_path->calculateBBox(m_matrix, &m_xbounds);

	for (int i = 0; i < m_subObjects->m_items.GetSize(); i++)
	{
		CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)m_subObjects->m_items[i]);

		pObject->CalculateBounds();
	}

// TODO This is a Hack
	CComQIPtr<IPDContentText> contentText = m_content;
	if (contentText)
	{
		CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)m_content);

		pObject->CalculateBounds();
	}
/*
	double left = 9999999;
	double top = 9999999;
	double right = -9999999;
	double bottom = -9999999;
*/
	double left = m_bounds.X;
	double top = m_bounds.Y;
	double right = m_bounds.X+m_bounds.Width;
	double bottom = m_bounds.Y+m_bounds.Height;

	for (i = 0; i < m_subObjects->m_items.GetSize(); i++)
	{
		CComQIPtr<IPDObject> object = m_subObjects->m_items[i];

		RectD objectExpandedRect;
		object->getExpandedBBox(&objectExpandedRect);

		if (objectExpandedRect.X < left) left = objectExpandedRect.X;
		if (objectExpandedRect.Y < top) top = objectExpandedRect.Y;
		if (objectExpandedRect.X+objectExpandedRect.Width > right) right = objectExpandedRect.X+objectExpandedRect.Width;
		if (objectExpandedRect.Y+objectExpandedRect.Height > bottom) bottom = objectExpandedRect.Y+objectExpandedRect.Height;
	}

	m_filterRect.X = left;
	m_filterRect.Y = top;
	m_filterRect.Width = right - left;
	m_filterRect.Height = bottom - top;

	m_appearance->SetupChildrenLayers(this);

	m_expandedBBox = m_appearance->m_expandedRect;

	CalculateScale(m_expandedBBox, m_matrix);

	/*
	if (m_opacityMaskGroup)
	{
		static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)m_opacityMaskGroup.p)->CalculateBounds();
	}
	*/

	if (m_parent)
	{
		// TODO Have this ???
		static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)m_parent)->CalculateBounds();
	}
}

STDMETHODIMP CPDObjectFrame::Render2(/*[in]*/ DWORD dwBitmap, DWORD dwGraphics, double scaleX, double scaleY)
{
	Gdiplus::Graphics& graphics = *(Gdiplus::Graphics*)dwGraphics;
	Gdiplus::Bitmap* pBitmap = (Gdiplus::Bitmap*)dwBitmap;
	//Gdiplus::Graphics* pGraphics = (Gdiplus::Graphics*)dwGraphics;

//	Gdiplus::Graphics graphics = Gdiplus::Graphics(pBitmap);

	if (m_gdppath) delete m_gdppath;
	m_gdppath = new Gdiplus::GraphicsPath(Gdiplus::FillModeWinding);
	m_path->RenderToGraphicsPath(m_gdppath);

	//m_backgroundBitmap = new Gdiplus::Bitmap((int)ceil(m_filterRect.Width*scaleX), (int)ceil(m_filterRect.Height*scaleY), PixelFormat32bppARGB);
	m_backgroundBitmap = pBitmap;
	//if (m_backgroundBitmap)
	{
		//Gdiplus::Graphics graphics(m_backgroundBitmap);
		graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality/*pGraphics->GetSmoothingMode()*/);

//		graphics.ScaleTransform(scaleX, scaleY);
//		graphics.TranslateTransform(-m_filterRect.X, -m_filterRect.Y);

	// Draw strokes & fills
		for (int i = 0; i < m_subObjects->m_items.GetSize(); i++)
		{
			CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)m_subObjects->m_items[i]);

			pObject->Render(NULL, &graphics, scaleX, scaleY);
		}

	// Draw content
		if (m_content)
		{
			Gdiplus::GraphicsState state = graphics.Save();

			CPDObjectImpl<IPDObject>* pContent = static_cast<CPDObjectImpl<IPDObject>*>(m_content);

			pContent->Render(NULL, &graphics, scaleX, scaleY);

			graphics.Restore(state);
		}

	// Draw text along our path
		if (m_pathText)
		{
			Gdiplus::GraphicsState state = graphics.Save();

			CPDObjectImpl<IPDPathText>* pContent = static_cast<CPDObjectImpl<IPDPathText>*>(m_pathText);

			pContent->Render(NULL, &graphics, scaleX, scaleY);

			graphics.Restore(state);
		}

		Mask(m_backgroundBitmap, m_filterRect, scaleX, scaleY, Gdiplus::SmoothingModeHighQuality/*pGraphics->GetSmoothingMode()*/);

		//pGraphics->DrawImage(m_backgroundBitmap, (float)m_filterRect.X, (float)m_filterRect.Y);

	//	delete m_backgroundBitmap;
		m_backgroundBitmap = NULL;
	}

	delete m_gdppath;
	m_gdppath = NULL;

	return S_OK;
}

STDMETHODIMP CPDObjectFrame::get_content(IPDObject **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_content;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDObjectFrame::removeObject(/*[in]*/ IPDObjectUnknown* object)
{
	if (object == m_content)
	{
		ATLASSERT(m_children->m_items.GetSize() == 1);
		ATLASSERT(object == m_children->m_items[0]);

		{
			CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>(object);
			pObject->m_parent = NULL;
			pObject->detachFromSpread();
		}

		object->Release();

		m_content = NULL;
		m_children->m_items.RemoveAll();

		FireOnChanged(NOTIFY_REMOVE, object, DISPID_UNKNOWN);
	}

	return S_OK;
}

STDMETHODIMP CPDObjectFrame::put_content(IPDObject *object)
{
	object->AddRef();

// First remove it from previous parent
	if (object)
	{
		CComPtr<IPDObjectUnknown> parent;
		object->get_parent(&parent);

		if (parent)
		{
			parent->removeObject(object);
		}
	}

	// Remove previous content
	if (m_content)
	{
		ATLASSERT(m_children->m_items.GetSize() == 1);
		ATLASSERT(m_content == m_children->m_items[0]);

		CComQIPtr<INotifySend> cp = m_content;
		cp->Unadvise(this);

		m_children->m_items.RemoveAll();

		FireOnChanged(NOTIFY_REMOVE, m_content, DISPID_UNKNOWN);

		m_content->Release();
		m_content = NULL;
	}
	else
		ATLASSERT(m_children->m_items.GetSize() == 0);

	m_content = object;

	if (m_content)
	{
		{
			CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>(m_content);
			pObject->m_parent = static_cast<CPDObjectUnknownImpl<IPDObjectUnknown>*>((IPDObjectUnknown*)this);
			pObject->attachToSpread(pObject->m_parent);
		}

		m_children->m_items.Add(m_content);

		{
			CComQIPtr<INotifySend> cp = m_content;
			DWORD cookie;
			cp->Advise(this, &cookie);
		}

		FireOnChanged(NOTIFY_ADD, m_content, DISPID_UNKNOWN);
	}

	//pObject->CalculateBounds();	// TODO Have this ???

	return S_OK;
}

STDMETHODIMP CPDObjectFrame::get_pathText(IPDPathText **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pathText;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDObjectFrame::put_pathText(IPDPathText *newVal)
{
	if (newVal == NULL) return E_INVALIDARG;

	CComPtr<IPDPathText> pathText = m_pathText;	// for AddRef purpose

// Deatch any previos path text on this frame
	if (m_pathText)
	{
		CComObject<CPDPathText>* pPathText = static_cast<CComObject<CPDPathText>*>(m_pathText);

		pPathText->m_layer = NULL;
		pPathText->m_spread = NULL;
		pPathText->m_parentFrame = NULL;
	}

	m_pathText = newVal;

	if (m_pathText)
	{
		CComObject<CPDPathText>* pPathText = static_cast<CComObject<CPDPathText>*>(newVal);

	// If the path text is already attached to a another frame, detach it
		if (pPathText->m_parentFrame)
		{
			pPathText->m_parentFrame->m_pathText = NULL;
			pPathText->m_spread = NULL;
			pPathText->m_layer = NULL;
		}

		pPathText->m_parentFrame = this;
		pPathText->m_spread = m_spread;
		pPathText->m_layer = m_layer;
	}

	return S_OK;
}

STDMETHODIMP CPDObjectFrame::Move(double dx, double dy)
{
	CComQIPtr<IPDObjectTransformable> contentTransformable = m_content;
	if (contentTransformable)
	{
		CComPtr<IPDMatrix> matrix;
		contentTransformable->get_transformMatrix(&matrix);

		CComPtr<IPDMatrix> imatrix;
		matrix->inverse(&imatrix);

		PointD pt0;
		pt0.x = 0;
		pt0.y = 0;

		PointD pt1;
		pt1.x = dx;
		pt1.y = dy;

		imatrix->transformPoint(&pt0, &pt0);
		imatrix->transformPoint(&pt1, &pt1);

		contentTransformable->Move(pt1.x-pt0.x, pt1.y-pt0.y);

		//contentTransformable->Move(dx, dy);
	}

	m_path->Move(dx, dy);
//	if (m_wrapPath) m_wrapPath->Move(dx, dy);	// Done in OnChanged

	if (m_opacityMaskGroup)
	{
		if (m_opacityMaskLinked)
		{
			CComQIPtr<IPDObjectTransformable> objectTransformable = m_opacityMaskGroup;
			objectTransformable->Move(dx, dy);
		}
	}

	/*
	m_strokeBrush->m_x1 += dx;
	m_strokeBrush->m_y1 += dy;
	m_strokeBrush->m_x2 += dx;
	m_strokeBrush->m_y2 += dy;

	m_fillBrush->m_x1 += dx;
	m_fillBrush->m_y1 += dy;
	m_fillBrush->m_x2 += dx;
	m_fillBrush->m_y2 += dy;
	*/

	return S_OK;
}

STDMETHODIMP CPDObjectFrame::Scale(double originx, double originy, double sx, double sy)
{
	CComPtr<IPDMatrix> mat0;
	mat0.CoCreateInstance(CLSID_PDMatrix);
	CComPtr<IPDMatrix> mat1;	mat0->translate(-originx, -originy, &mat1);
	CComPtr<IPDMatrix> mat2;	mat1->scaleNonUniform(sx, sy, &mat2);
	CComPtr<IPDMatrix> mat;		mat2->translate(originx, originy, &mat);

	m_path->transformPoints(mat);
	//if (m_wrapPath) m_wrapPath->transformPoints(mat);	???

	return S_OK;
}

void CPDObjectFrame::RecreateWrapPath()
{
	if (m_textWrap == TEXTWRAP_SHAPE)
	{
		VARIANT_BOOL isRectangular;
		m_path->IsRectangular(&isRectangular);

		if (isRectangular)
		{
			m_wrapPath->setRectangle(
				m_bounds.X-m_leftOffset,
				m_bounds.Y-m_topOffset,
				m_bounds.X+m_bounds.Width+m_rightOffset,
				m_bounds.Y+m_bounds.Height+m_bottomOffset);
		}
		else
		{
			m_wrapPath->offset(m_topOffset, 1, m_path);
		}
	}
	else if (m_textWrap == TEXTWRAP_BBOX)
	{
		m_wrapPath->setRectangle(
			m_bounds.X-m_leftOffset,
			m_bounds.Y-m_topOffset,
			m_bounds.X+m_bounds.Width+m_rightOffset,
			m_bounds.Y+m_bounds.Height+m_bottomOffset);
	}
}

STDMETHODIMP CPDObjectFrame::IsRectangular(VARIANT_BOOL *pVal)
{
	return m_path->IsRectangular(pVal);
}

// TODO, move this code into CPDObjectWrappableImpl
STDMETHODIMP CPDObjectFrame::put_textWrap(/*[in]*/ PDTextWrap newVal)
{
	if (m_textWrap != newVal)
	{
		m_textWrap = newVal;

		if (m_wrapPath)
		{
			CComQIPtr<INotifySend> cp = m_wrapPath;
			cp->Unadvise(this);
			m_wrapPath->Release();
			m_wrapPath = NULL;
		}

		m_editedWrapPath = FALSE;

		if (m_textWrap == TEXTWRAP_SHAPE || m_textWrap == TEXTWRAP_BBOX)
		{
			CComObject<CPDPath>::CreateInstance(&m_wrapPath);
			m_wrapPath->AddRef();

			RecreateWrapPath();

			CComQIPtr<INotifySend> cp = m_wrapPath;
			DWORD cookie;
			cp->Advise(this, &cookie);
		}

		// TODO notify ??
		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	}

	return S_OK;
}

STDMETHODIMP CPDObjectFrame::FireOnChanged(NotifyType type, IUnknown* targetObject, /*IUnknown* immtargetObject,*/ DISPID dispID)
{
	CalculateBounds();	// TODO, not always necessary (necessary when path changes, and some of the stroke attributes changes)

	return CNotifySendImpl<CPDObjectFrame>::FireOnChanged(type, targetObject, dispID);
}

// INotifyGet
STDMETHODIMP CPDObjectFrame::OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
{
	CalculateBounds();

	CComQIPtr<IPDPath> path = immtargetObject;
	if (path)
	{
		if (IsUnknownEqualUnknown(path, m_path->GetUnknown()))
		{
			if (m_gdppath)
			{
				delete m_gdppath;
				m_gdppath = NULL;
			}

			if (m_wrapPath)
			{
				if (m_editedWrapPath == FALSE)
				{
					CComQIPtr<INotifySend> cp = m_wrapPath;
					cp->LockSend();

					RecreateWrapPath();

					cp->UnlockSend();
				}
			}
		}
	}

	CNotifySendImpl<CPDObjectFrame>::FireOnChanged(type, targetObject, dispID);
	return S_OK;
}

STDMETHODIMP CPDObjectFrame::get_objectType(PDObjectType *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = OBJECT_FRAME;
	return S_OK;
}

STDMETHODIMP CPDObjectFrame::getScreenBBox(RectD *pVal)
{
	Gdiplus::GraphicsPath path;
	m_path->RenderToGraphicsPath(&path);

	CComPtr<IPDMatrix> ctm;
	getScreenCTM(&ctm);

	m_path->calculateBBox(ctm, pVal);

	return S_OK;
}

#if 0
STDMETHODIMP CPDObjectFrame::get_subObjects(IObjectMap **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_subObjects;
	(*pVal)->AddRef();
	return S_OK;
}
#endif

STDMETHODIMP CPDObjectFrame::appendSubObject(IPDObjectWithBrush *object)
{
	if (object == NULL) return E_INVALIDARG;

// TODO, remove from previous parent (if any)

	object->AddRef();

	CComQIPtr<IPDObject> o = object;
	o->put_parent(this);
	o->put_document(m_pDocument);

	/*
	{
		CPDObjectImpl<IPDObject>* pObject = static_cast<CPDObjectImpl<IPDObject>*>(o.p);
		pObject->CalculateBounds();
	}
	*/

	CComQIPtr<INotifySend> cp = object;
	DWORD cookie;
	cp->Advise(this, &cookie);

	m_subObjects->m_items.Add(o);

	CComQIPtr<IPDObjectStroke> stroke = object;
	CComQIPtr<IPDObjectFill> fill = object;
	if (stroke)
		m_activeStroke = stroke;
	else
		m_activeFill = fill;

	return FireOnChanged(NOTIFY_ADD, object, DISPID_UNKNOWN);
}

// IObjectSerializable
STDMETHODIMP CPDObjectFrame::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	HRESULT hr;

	hr = CPDObjectImpl<IPDObjectFrame>::Serialize(ar, node);
	if (FAILED(hr)) return hr;

	hr = CPDObjectTransformableImpl<CPDObjectFrame>::Serialize(ar, node);
	if (FAILED(hr)) return hr;

	CPDObjectWithOpacityMaskImpl<CPDObjectFrame>::Serialize(ar, node);
	if (FAILED(hr)) return hr;

	hr = CPDObjectWithAppearanceAndStrokeFillImpl<CPDObjectFrame>::Serialize(ar, node);
	if (FAILED(hr)) return hr;

	node->putAttribute(L"path", _variant_t(static_cast<IUnknown*>((IPDPath*)m_path)));

	node->putElement(L"content", m_content);

	node->putObjectMap(L"subObjects", m_subObjects);

	CPDObjectWrappableImpl<CPDObjectFrame>::Serialize(ar, node);
	if (FAILED(hr)) return hr;

	return S_OK;
}

STDMETHODIMP CPDObjectFrame::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	HRESULT hr;

	hr = CPDObjectImpl<IPDObjectFrame>::Deserialize(ar, node, pUnkExtra);
	if (FAILED(hr)) return hr;

	hr = CPDObjectTransformableImpl<CPDObjectFrame>::Deserialize(ar, node, pUnkExtra);
	if (FAILED(hr)) return hr;

	CPDObjectWithOpacityMaskImpl<CPDObjectFrame>::Deserialize(ar, node, NULL);
	if (FAILED(hr)) return hr;

	hr = CPDObjectWithAppearanceAndStrokeFillImpl<CPDObjectFrame>::Deserialize(ar, node, pUnkExtra);
	if (FAILED(hr)) return hr;

	CComPtr<IArchiveElement> pathNode;
	node->getAttributeNode(L"path", &pathNode);
	if (pathNode) m_path->Deserialize(ar, pathNode, NULL);

	m_subObjects->m_items.RemoveAll();

	CComObject<CObjectMap>* pMap;

	CComObject<CObjectMap>::CreateInstance(&pMap);
	if (pMap)
	{
		if (SUCCEEDED(node->getObjectMap(L"subObjects", pMap, NULL)))
		{
			for (int i = 0; i < pMap->m_items.GetSize(); i++)
			{
				IPDObjectWithBrush* p = static_cast<IPDObjectWithBrush*>(pMap->m_items[i]);
				appendSubObject(p);
			}
		}
		pMap->Release();
	}

	CPDObjectWrappableImpl<CPDObjectFrame>::Deserialize(ar, node, pUnkExtra);
	if (FAILED(hr)) return hr;

	CalculateBounds();

	return S_OK;
}

STDMETHODIMP CPDObjectFrame::GetClassID(CLSID *pClassID)
{
	*pClassID = CLSID_PDObjectFrame;
	return S_OK;
}
