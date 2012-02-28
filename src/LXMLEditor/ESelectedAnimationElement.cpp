#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

//#include "EAnimationElement.h"
#include "ESelectedAnimationElement.h"

#include "ESVGPolyElement.h"
#include "ESelectedSVGPolyElement.h"

#include "ESVGPathElement.h"
#include "ESelectedSVGPathElement.h"

#if 0

STDMETHODIMP CESelectedAnimationElement::DeleteSelection()
{
	CComPtr<ILDOMElement> domElement;
	m_pElement->get_domElement(&domElement);

	CComQIPtr<ILAnimateXXX> animateXXX = domElement;

	long nvalues;
	animateXXX->GetNValues(&nvalues);

	for (int i = 0; i < nvalues; i++)
	{
		CComPtr<ILSMILAttributeValue> attribute;
		animateXXX->GetValue(m_selectedKeyTimes[i], &attribute);
		if (attribute)
		{
			CComPtr<IUnknown> object;
			attribute->getObject(&object);

			CComQIPtr<ILSVGPointList> points = object;
			CComQIPtr<ILSVGPathSegListValue> seglistvalue = object;
			if (points)
			{
				//((CESVGPolyElement*)((CESelectedSVGPolyElement*)m_selectedTargetElement.p)->m_pElement)->DrawOutline(points, pGraphics, color, matrix);
			}
			else if (seglistvalue)
			{
				CComPtr<ILSVGPathSegList> seglist;
				seglistvalue->get_pathSegList(&seglist);

				((CESelectedSVGPathElement*)m_selectedTargetElement.p)->DeleteSelection(seglist);
			}
		}
	}

	return S_OK;
}

// IESVGDrawOutline
STDMETHODIMP CESelectedAnimationElement::DrawOutline(Gdiplus::Graphics* pGraphics, Gdiplus::Color& color, ILSVGMatrix* matrix)
{
	CComPtr<ILDOMElement> domElement;
	m_pElement->get_domElement(&domElement);

	CComQIPtr<ILAnimateXXX> animateXXX = domElement;

	if (m_selectedTargetElement)
	{
		CComPtr<IEElement> eTargetElement;
		m_selectedTargetElement->get_eElement(&eTargetElement);

		CComPtr<ILDOMElement> targetElement;
		eTargetElement->get_domElement(&targetElement);

		CComQIPtr<ILSVGEllipseElement> ellipse = targetElement;
		if (ellipse)
		{
			CComBSTR attributeName;
			domElement->getAttribute(L"attributeName", &attributeName);

			double cx;
			double cy;
			double rx;
			double ry;

			// cx
			CComQIPtr<ILSVGLength> cxlength;
			{
				CComQIPtr<ILSVGAnimatedLength> alength;
				ellipse->get_cx(&alength);
				alength->get_baseVal(&cxlength);
			}
			cxlength->get_value(&cx);

			// cy
			CComQIPtr<ILSVGLength> cylength;
			{
				CComQIPtr<ILSVGAnimatedLength> alength;
				ellipse->get_cy(&alength);
				alength->get_baseVal(&cylength);
			}
			cylength->get_value(&cy);

			// rx
			CComQIPtr<ILSVGLength> rxlength;
			{
				CComQIPtr<ILSVGAnimatedLength> alength;
				ellipse->get_rx(&alength);
				alength->get_baseVal(&rxlength);
			}
			rxlength->get_value(&rx);

			// ry
			CComQIPtr<ILSVGLength> rylength;
			{
				CComQIPtr<ILSVGAnimatedLength> alength;
				ellipse->get_ry(&alength);
				alength->get_baseVal(&rylength);
			}
			rylength->get_value(&ry);

			for (int i = 0; i < m_selectedKeyTimes.GetSize(); i++)
			{
				CComPtr<ILSMILAttributeValue> attribute;
				animateXXX->GetValue(m_selectedKeyTimes[i], &attribute);
				if (attribute)
				{
					CComPtr<IUnknown> object;
					attribute->getObject(&object);

					CComQIPtr<ILSVGLength> length = object;

					if (!wcscmp(attributeName, L"cx"))
					{
						length->get_value(&cx);
					}
					else if (!wcscmp(attributeName, L"cy"))
					{
						length->get_value(&cy);
					}

					SVGPoint bpoints[13];
					SetPointsEllipse(cx-rx, cy-ry, cx+rx, cy+ry, bpoints);

					Gdiplus::PointF xpts[13];

					for (int i = 0; i < 13; i++)
					{
						xpts[i] = bpoints[i].matrixTransform(matrix);
					}

					pGraphics->DrawBeziers(&Gdiplus::Pen(color), xpts, 13);
				}
			}
		}
		else
		{
			for (int i = 0; i < m_selectedKeyTimes.GetSize(); i++)
			{
				CComPtr<ILSMILAttributeValue> attribute;
				animateXXX->GetValue(m_selectedKeyTimes[i], &attribute);
				if (attribute)
				{
					CComPtr<IUnknown> object;
					attribute->getObject(&object);

					CComQIPtr<ILSVGPointList> points = object;
					CComQIPtr<ILSVGPathSegListValue> seglistvalue = object;
					if (points)
					{
						((CESVGPolyElement*)((CESelectedSVGPolyElement*)m_selectedTargetElement.p)->m_pElement)->DrawOutline(points, pGraphics, color, matrix);
					}
					else if (seglistvalue)
					{
						CComPtr<ILSVGPathSegList> seglist;
						seglistvalue->get_pathSegList(&seglist);

						((CESVGPathElement*)((CESelectedSVGPathElement*)m_selectedTargetElement.p)->m_pElement)->DrawOutline(seglist, pGraphics, color, matrix);
					}
				}
			}
		}
	}

	return S_OK;
}

// IESVGDrawSelection
HRESULT CESelectedAnimationElement::DrawSelection(Gdiplus::Graphics* pGraphics, Gdiplus::Color& color, ILSVGMatrix* matrix)
{
	CComPtr<ILDOMElement> domElement;
	m_pElement->get_domElement(&domElement);

//	CComBSTR attributeName;
//	domElement->getAttribute(L"attributeName", &attributeName);

	CComQIPtr<ILAnimateXXX> animateXXX = domElement;

	for (int i = 0; i < m_selectedKeyTimes.GetSize(); i++)
	{
		CComPtr<ILSMILAttributeValue> attribute;
		animateXXX->GetValue(m_selectedKeyTimes[i], &attribute);

		if (attribute)
		{
			CComPtr<IUnknown> object;
			attribute->getObject(&object);

			CComQIPtr<ILSVGPointList> points = object;
			CComQIPtr<ILSVGPathSegListValue> seglistvalue = object;
			if (points)
			{
				((CESelectedSVGPolyElement*)m_selectedTargetElement.p)->DrawSelection(points, pGraphics, color, matrix);
			}
			else if (seglistvalue)
			{
				CComPtr<ILSVGPathSegList> seglist;
				seglistvalue->get_pathSegList(&seglist);

				((CESelectedSVGPathElement*)m_selectedTargetElement.p)->DrawSelection(seglist, pGraphics, color, matrix);
			}
		}
	}

	return S_OK;
}

//
STDMETHODIMP CESelectedAnimationElement::Move(ISVGView* view, double dx, double dy)
{
	CComQIPtr<IEElement> eElement = m_pElement;
	CComQIPtr<IEAnimationElement> eanimationElement = eElement;

	CComPtr<ILDOMElement> domElement;
	eElement->get_domElement(&domElement);

	CComBSTR attributeName;
	domElement->getAttribute(L"attributeName", &attributeName);

	CComQIPtr<ILAnimateXXX> animateXXX = domElement;

	for (int i = 0; i < m_selectedKeyTimes.GetSize(); i++)
	{
		CComPtr<ILSMILAttributeValue> attribute;
		animateXXX->GetValue(m_selectedKeyTimes[i], &attribute);

		CComBSTR str;
		attribute->getStringValue(&str);
		double value = getfnumber(str);

		if (!wcscmp(attributeName, L"cx"))
		{
			WCHAR str2[64];
			swprintf(str2, L"%g", value+dx);
			attribute->setStringValue(str2);
		}
		else if (!wcscmp(attributeName, L"cy"))
		{
			WCHAR str2[64];
			swprintf(str2, L"%g", value+dy);
			attribute->setStringValue(str2);
		}

		/*
		CComPtr<ILSVGLength> length;
		attribute->getSVGLength(&length);

		double value;
		length->get_value(&value);
		length->put_value(value+dx);
		*/

		//attribute->setStringValue();
	}

#if 0
	CComQIPtr<ILAnimationElement> animationElement = m_domElement;

	CComPtr<ILDOMElement> targetElement;
	animationElement->get_targetElement(&targetElement);

	CComQIPtr<ILAnimateXXX> animateXXX = animationElement;
#endif

//	animateXXX->

	/*
	CComPtr<IEElement> eTargetElement;
	m_pDocument->GetEElementFromDOMElement(targetElement, &eTargetElement);

	CComQIPtr<IESVG
	*/

	return S_OK;
}

STDMETHODIMP CESelectedAnimationElement::MoveSelectedPoints(_SVGHitData* hitdata, SVGPoint xnewpt2, SVGPoint xoldpt2)
{
//	CComQIPtr<IEElement> eElement = m_pElement;

	CComPtr<ILDOMElement> domElement;
	m_pElement->get_domElement(&domElement);

//	CComBSTR attributeName;
//	domElement->getAttribute(L"attributeName", &attributeName);

	CComQIPtr<ILAnimateXXX> animateXXX = domElement;

	for (int i = 0; i < m_selectedKeyTimes.GetSize(); i++)
	{
		CComPtr<ILSMILAttributeValue> attribute;
		animateXXX->GetValue(m_selectedKeyTimes[i], &attribute);

		CComPtr<IUnknown> object;
		attribute->getObject(&object);

		CComQIPtr<ILSVGPointList> points = object;
		CComQIPtr<ILSVGPathSegListValue> seglistvalue = object;
		if (points)
		{
			((CESelectedSVGPolyElement*)m_selectedTargetElement.p)->MoveSelectedPoints(points, hitdata, xnewpt2, xoldpt2);
		}
		else if (seglistvalue)
		{
			CComPtr<ILSVGPathSegList> seglist;
			seglistvalue->get_pathSegList(&seglist);

			((CESelectedSVGPathElement*)m_selectedTargetElement.p)->MoveSelectedPoints(seglist, hitdata, xnewpt2, xoldpt2);
		}
	}

	return S_OK;
}

//HRESULT HitTest(ILSVGPathSegList* seglist, ISVGView* view, ILSVGSVGElement* svgsvgElement, ILSVGMatrix* ctm, double ptx, double pty, /*long tool,*/ _SVGHitData* hit);

STDMETHODIMP CESelectedAnimationElement::HitTest(ISVGView* view, ILSVGSVGElement* svgsvgElement, ILSVGMatrix* ctm, double ptx, double pty, long tool, _SVGHitData* hit)
{
	CComPtr<ILDOMElement> domElement;
	m_pElement->get_domElement(&domElement);

//	CComBSTR attributeName;
//	domElement->getAttribute(L"attributeName", &attributeName);

	CComQIPtr<ILAnimateXXX> animateXXX = domElement;

	for (int i = 0; i < m_selectedKeyTimes.GetSize(); i++)
	{
		CComPtr<ILSMILAttributeValue> attribute;
		animateXXX->GetValue(m_selectedKeyTimes[i], &attribute);

		CComPtr<IUnknown> object;
		attribute->getObject(&object);

		CComQIPtr<ILSVGPointList> points = object;
		CComQIPtr<ILSVGPathSegListValue> seglistvalue = object;

		if (points)
		{
			HRESULT hr = ((CESVGPolyElement*)((CESelectedSVGPolyElement*)m_selectedTargetElement.p)->m_pElement)->HitTest(points, view, svgsvgElement, ctm, ptx, pty, hit);
			if (hr == S_OK)
			{
				hit->selectedKeyFrameIndex = i;
				return S_OK;
			}
		}
		else if (seglistvalue)
		{
			CComPtr<ILSVGPathSegList> seglist;
			seglistvalue->get_pathSegList(&seglist);

			((CESVGPathElement*)((CESelectedSVGPathElement*)m_selectedTargetElement.p)->m_pElement)->HitTest(seglist, view, svgsvgElement, ctm, ptx, pty, hit);

			SVGPoint pt(ptx, pty);

			hit->anchor = ((CESelectedSVGPathElement*)m_selectedTargetElement.p)->FindPoint(seglist, ctm, pt.X, pt.Y, hit->ctl);
			if (hit->anchor >= 0)
			{
				hit->selectedKeyFrameIndex = i;
				hit->hit = -1;

				return S_OK;
			}
		}
	}

	hit->selectedKeyFrameIndex = -1;
	return S_FALSE;
}

#endif