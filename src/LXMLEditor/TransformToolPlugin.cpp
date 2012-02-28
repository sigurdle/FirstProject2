// TransformToolPlugin.cpp : Implementation of CTransformToolPlugin
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "TransformToolPlugin.h"

#include "ESelectedAnimationElement.h"

namespace System
{
namespace LXmlEdit
{

double GetLineAngle(double x1, double y1, double x2, double y2);

Web::Element* SVGGetLayer(Web::Element* element);
LDraw::Color GetLayerColor(Web::Element* element);

Web::SVGMatrix* GetRotateObjectMatrix(Web::SVGSVGElement* svgsvgElement, LDraw::PointD woldpt, LDraw::PointD wpt, double cx, double cy)
{
	ASSERT(0);
	return NULL;
#if 0
	double oldangleX;
	{
		double dx = woldpt.X - cx;
		double dy = woldpt.Y - cy;

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
		double dx = wpt.X - cx;
		double dy = wpt.Y - cy;

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

	CComQIPtr<ILSVGMatrix> mat0;
	svgsvgElement->createSVGMatrix(&mat0);

	CComQIPtr<ILSVGMatrix> mat1;
	mat0->translate(-cx, -cy, &mat1);

	CComQIPtr<ILSVGMatrix> mat2;
	mat1->rotate(angleX-oldangleX, &mat2);

	CComQIPtr<ILSVGMatrix> mat3;
	mat2->translate(cx, cy, &mat3);
	
	return mat3.Detach();
#endif
}

ErrorCode CalculateContentsBBox(ISVGView* view, IESelectedElement* selectedElement, LDraw::RectD* pVal)
{
	ASSERT(0);
#if 0
	/*
	PDObjectType objectType;
	object->get_objectType(&objectType);
	*/

#if 0
	if (objectType == OBJECT_GROUP)
	{
		double minx = 9999999;
		double miny = 9999999;
		double maxx = -9999999;
		double maxy = -9999999;

	//	CComPtr<IObjectMap> children;
	//	object->get_children(&children);
	//	long nchildren;
	//	children->get_length(&nchildren);

		IEElement* childElement = object->get_firstElement(&childElement);

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
#endif
	{
		/*
		CComPtr<remove> element;
		eelement->get_domElement(&element);

		CComQIPtr<ILSVGElement> svgElement = element;
		CComQIPtr<ILSVGLocatable> objectLocatable = svgElement;

		if (objectLocatable)
		{
			CComPtr<ILSVGRect> svgRect;
			window->svgGetScreenBBox(svgElement, &svgRect);

			*pVal = svgRect;
		}
		*/
		CComPtr<ILSVGRect> svgRect;
		selectedElement->GetScreenBBox(view, &svgRect);
		*pVal = svgRect;
	}
#endif
	return Success;
}

void CTransformTool::CalculateObjectsBoundingBox(ISVGView* view)
{
//	CComPtr<ILHTMLWindow> window;
//	view->GetHTMLWindow(&window);

	CEXMLViewGroup* viewGroup = view->GetViewGroup();

	long selectedCount = viewGroup->GetSelectedCount();

	if (selectedCount > 0)
	{
		double minx = 9999999;
		double miny = 9999999;
		double maxx = -9999999;
		double maxy = -9999999;

		for (int i = 0; i < selectedCount; i++)
		{
			IESelectedElement* selectedElement = viewGroup->GetSelectedElementN(i);

//			CComPtr<IEElement> eElement;
//			selectedElement->get_eElement(&eElement);

			LDraw::RectD bounds;
			CalculateContentsBBox(view, selectedElement, &bounds);

			if (bounds.X < minx) minx = bounds.X;
			if (bounds.Y < miny) miny = bounds.Y;
			if (bounds.X+bounds.Width > maxx) maxx = bounds.X+bounds.Width;
			if (bounds.Y+bounds.Height > maxy) maxy = bounds.Y+bounds.Height;
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

/////////////////////////////////////////////////////////////////////////////
// CTransformToolPlugin

Web::SVGTransform* CTransformTool::GetMatrixTransform(Web::SVGSVGElement* svgsvgElement, Web::SVGTransformList* basetransformlist)
{
#if 0
	long numberOfItems;
	basetransformlist->get_numberOfItems(&numberOfItems);
	//if (numberOfItems > 0)
	{
		for (int i = numberOfItems-1; i >= numberOfItems-1; i--)
		{
			CComPtr<ILSVGTransform> transform;
			basetransformlist->getItem(i, &transform);

			LSVGTransformType type;
			transform->get_type(&type);

			if (type == SVG_TRANSFORM_MATRIX)
			{
				return transform;
			}
		}
	}
#endif

// Create new 'matrix' transform
	Web::SVGMatrix* matrix;
	//svgsvgElement->createSVGMatrix(&matrix);
	
	Web::SVGTransform* transform = basetransformlist->createSVGTransformFromMatrix(matrix);
//	basetransformlist->appendItem(transform, NULL);
	basetransformlist->insertItemBefore(transform, 0);

	return transform;
}

Web::SVGTransform* CTransformTool::GetMatrixTransform(Web::SVGSVGElement* svgsvgElement, Web::ISVGTransformable* transformable)
{
	//CComQIPtr<ILSVGTransformable> transformable = m_domElement;

	if (transformable)
	{
		Web::SVGAnimatedTransformList* animtransformlist = transformable->get_transform();
		Web::SVGTransformList* basetransformlist = animtransformlist->get_baseVal();

		return GetMatrixTransform(svgsvgElement, basetransformlist);
#if 0
		long numberOfItems;
		basetransformlist->get_numberOfItems(&numberOfItems);
		//if (numberOfItems > 0)
		{
			for (int i = numberOfItems-1; i >= numberOfItems-1; i--)
			{
				CComPtr<ILSVGTransform> transform;
				basetransformlist->getItem(i, &transform);

				LSVGTransformType type;
				transform->get_type(&type);

				if (type == SVG_TRANSFORM_MATRIX)
				{
					return transform;
				}
			}
		}

	// Create new 'matrix' transform
		CComPtr<ILSVGMatrix> matrix;
		svgsvgElement->createSVGMatrix(&matrix);
		
		CComPtr<ILSVGTransform> transform;
		basetransformlist->createSVGTransformFromMatrix(matrix, &transform);
	// basetransformlist->appendItem(transform, NULL);
		basetransformlist->insertItemBefore(transform, 0, NULL);

		return transform;
#endif
	}

	return NULL;
}

ErrorCode CTransformTool::OnButtonDown(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse, /*[out,retval]*/ long* pdragging)
{
	ASSERT(0);
#if 0
	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<IEXMLDocument> eDocument;
	viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<IEElement> rootEElement;
	view->GetEElement(&rootEElement);

	CComPtr<remove> rootElement;
	rootEElement->get_domElement(&rootElement);

	CComQIPtr<ILSVGSVGElement> svgsvgElement = rootElement;

	CComQIPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	/*
	double translateX;
	double translateY;
	window->get_currentTranslateX(&translateX);
	window->get_currentTranslateY(&translateY);

	double magnify;
	window->get_magnify(&magnify);
	*/

	/*
	CComPtr<ILSVGMatrix> mat;
	svgsvgElement->createSVGMatrix(&mat);
	mat->scaleNonUniform(magnify, magnify, &viewMatrix);
	*/
	/*
	CComPtr<ILSVGMatrix> viewMatrix;

	CComPtr<ILSVGMatrix> mat1;
	svgsvgElement->createSVGMatrix(&mat1);
	CComPtr<ILSVGMatrix> mat;
	mat1->scaleNonUniform(magnify, magnify, &mat);
	mat->translate(translateX, translateY, &viewMatrix);
	*/

//	double m_magnify = 1;
//	int m_dragging = 0;

	SVGPoint pt(mouse->ptx, mouse->pty);
	m_startpt = pt;
	m_oldpt = pt;
//	SVGPoint wpt(mouse->wptx, mouse->wpty);
//	SVGPoint dpt(mouse->dptx+translateX, mouse->dpty+translateY);
//	SVGPoint dpt(mouse->dptx, mouse->dpty);
//	m_wstartpt = wpt;

	m_element.RemoveAll();
	m_currentTransform.RemoveAll();

	CalculateObjectsBoundingBox(view);

	switch (m_nTool)
	{
		case ID_SVGTOOL_FREETRANSFORM:
			{
				long selectedCount;
				viewGroup->GetSelectedCount(&selectedCount);

			// All objects must be transformable
				for (int i = 0; i < selectedCount; i++)
				{
					CComPtr<IESelectedElement> selectedElement;
					viewGroup->GetSelectedElementN(i, &selectedElement);

					CComPtr<IEElement> eElement;
					selectedElement->get_eElement(&eElement);

					CComPtr<remove> domElement;
					eElement->get_domElement(&domElement);

					/*
				// Account for animation
					CComQIPtr<ILAnimationElement> animationElement = domElement;
					if (animationElement)
					{
						domElement.Release();
						animationElement->get_targetElement(&domElement);
					}
					*/

					CComQIPtr<ILSVGAnimateTransformElement> animateTransform = domElement;
					CComQIPtr<ILSVGTransformable> objectTransformable = domElement;
					CComQIPtr<ILSVGGradientElement> gradient = domElement;
					CComQIPtr<ILSVGPatternElement> pattern = domElement;

					if (animateTransform || objectTransformable || gradient || pattern)
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
					m_hit = 0;

					// Remember initial matrix of all objects
					for (int i = 0; i < selectedCount; i++)
					{
						CComPtr<IESelectedElement> selectedElement;
						viewGroup->GetSelectedElementN(i, &selectedElement);

						CComPtr<IEElement> eElement;
						selectedElement->get_eElement(&eElement);

						CComPtr<remove> domElement;
						eElement->get_domElement(&domElement);

						/*
					// Account for animation
						CComQIPtr<ILAnimationElement> animationElement = domElement;
						if (animationElement)
						{
							domElement.Release();
							animationElement->get_targetElement(&domElement);

							eElement.Release();
							eDocument->GetEElementFromDOMElement(domElement, &eElement);
						}
						*/

						CComQIPtr<ILSVGAnimateTransformElement> animateTransform = domElement;
						CComQIPtr<ILSVGTransformable> objectTransformable = domElement;
						CComQIPtr<ILSVGGradientElement> gradient = domElement;
						CComQIPtr<ILSVGPatternElement> pattern = domElement;

						if (animateTransform)
						{
							CComBSTR type;
							domElement->getAttribute(L"type", &type);

							CComQIPtr<ILAnimateXXX> animateXXX = animateTransform;
							m_element.Add(selectedElement);

							if (!wcscmp(type, L"translate"))
								m_hit = -2;
							else if (!wcscmp(type, L"rotate"))
								m_hit = -1;

							for (int i = 0; i < ((CESelectedAnimationElement*)selectedElement.p)->m_selectedKeyTimes.GetSize(); i++)
							{
								CComPtr<ILSMILAttributeValue> attribute;
								animateXXX->GetValue(((CESelectedAnimationElement*)selectedElement.p)->m_selectedKeyTimes[i], &attribute);

								CComPtr<IUnknown> value;
								attribute->getObject(&value);

								CComQIPtr<ILSVGTransform> transform = value;
								ATLASSERT(transform);

								m_currentTransform.Add(transform);
							}
						}
						else if (objectTransformable)
						{
							ILSVGTransform* transform = GetMatrixTransform(svgsvgElement, objectTransformable);

							/*
							CComPtr<ILSVGMatrix> matrix;
							transform->get_matrix(&matrix);
							*/

							m_element.Add(selectedElement);
							m_currentTransform.Add(transform);

							/*
							CComPtr<ILSVGMatrix> mat;
							objectTransformable->get_transformMatrix(&mat);

							m_targetObjects[i]->m_initialMatrix.Release();
							m_targetObjects[i]->m_initialMatrix.CoCreateInstance(CLSID_PDMatrix);

							m_targetObjects[i]->m_initialMatrix->copyFrom(mat);
							*/
						}
						else if (gradient)
						{
							CComQIPtr<ILSVGAnimatedTransformList> atransformlist;
							gradient->get_gradientTransform(&atransformlist);
							
							CComPtr<ILSVGTransformList> transformlist;
							atransformlist->get_baseVal(&transformlist);

							ILSVGTransform* transform = GetMatrixTransform(svgsvgElement, transformlist);

							m_element.Add(selectedElement);
							m_currentTransform.Add(transform);
						}
						else if (pattern)
						{
							Web::CLSVGAnimatedTransformList* atransformlist = pattern->get_patternTransform();
							Web::SVGTransformList* transformlist = atransformlist->get_baseVal();
							Web::SVGTransform* transform = GetMatrixTransform(svgsvgElement, transformlist);

							m_element.Add(selectedElement);
							m_currentTransform.Add(transform);
						}
					}

					LDraw::RectD bounds = m_objectsBoundingBox;

					if (m_hit == 0)
					{
						LDraw::PointD pts[8] =
						{
							LDraw::PointD(bounds.X, bounds.Y),
							LDraw::PointD(bounds.X+bounds.Width/2, bounds.Y),
							LDraw::PointD(bounds.X+bounds.Width, bounds.Y),
							LDraw::PointD(bounds.X+bounds.Width, bounds.Y+bounds.Height/2),
							LDraw::PointD(bounds.X+bounds.Width, bounds.Y+bounds.Height),
							LDraw::PointD(bounds.X+bounds.Width/2, bounds.Y+bounds.Height),
							LDraw::PointD(bounds.X, bounds.Y+bounds.Height),
							LDraw::PointD(bounds.X, bounds.Y+bounds.Height/2),
						};

						LDraw::PointD xpts[8];
						for (int npt = 0; npt < 8; npt++)
						{
							xpts[npt] = pts[npt];//.matrixTransform(viewMatrix);
							//m_matrix->transformPoint(&pts[npt], &xpts[npt]);
							//xpts[npt] = pts[npt];
						}

						for (int i = 0; i < 8; i++)
						{
							if ((fabs(/*d*/pt.X-xpts[i].X) <= 6) && (fabs(/*d*/pt.Y-xpts[i].Y) <= 6))
							{
								m_offsetPt.X = (pt.X-xpts[i].X);//*magnify;
								m_offsetPt.Y = (pt.Y-xpts[i].Y);//*magnify;

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
						/*
						CComPtr<ILSVGMatrix> imatrix;
						m_matrix->inverse(&imatrix);
						*/

						LDraw::PointD xpt = pt;//wpt;///*dpt*/wpt.matrixTransform(imatrix);
						//imatrix->transformPoint((PointD*)&dpt, &xpt);

						if (xpt.X > bounds.X && xpt.Y > bounds.Y &&
							xpt.X < bounds.X+bounds.Width && xpt.Y < bounds.Y+bounds.Height)
						{
							m_hit = 1;	// Inside
						}
						else	// Outside (Rotate)
						{
							m_pivotPt.X = bounds.X + bounds.Width/2;	// Center
							m_pivotPt.Y = bounds.Y + bounds.Height/2;

							m_hit = 0;
						}
					}

					/*
					ATLASSERT(m_freeTransformMatrix == NULL);
					m_freeTransformMatrix.CoCreateInstance(CLSID_PDMatrix);
					*/

				//	ATLASSERT(m_oldfreeTransformMatrix == NULL);
				//	m_oldfreeTransformMatrix.CoCreateInstance(CLSID_PDMatrix);
				}
			}
			break;
	}

	m_startDragCursor = ::GetCursor();
	*pdragging = m_dragging;

	if (m_dragging)
	{
		window->captureMouse(VARIANT_TRUE);
	}

#if 0
	switch (m_nTool)
	{
		case ID_SVGTOOL_ROTATE:
		case ID_SVGTOOL_SCALE:
		case ID_SVGTOOL_SKEW:
			{
				if (fabs(pt.x-m_pivotPt.X) < 8 &&
					fabs(pt.y-m_pivotPt.Y) < 8)
				{
					m_hit = 2;
				}
				else
				{
					for (int i = 0; i < m_viewGroup->m_targetElements.GetSize(); i++)
					{
#if 0
						CElementImpl* pElement = m_viewGroup->m_targetElements[i]->GetElement();
						CComQIPtr<ISVGTransform> transform = pElement->GetMatrixTransform();

					// Remember the initial matrix
						if (pElement->m_initialMatrix == NULL)
							pElement->m_initialMatrix.CreateInstance("SVG.SVGMatrix");

						pElement->m_initialMatrix->a = transform->matrix->a;
						pElement->m_initialMatrix->b = transform->matrix->b;
						pElement->m_initialMatrix->c = transform->matrix->c;
						pElement->m_initialMatrix->d = transform->matrix->d;
						pElement->m_initialMatrix->e = transform->matrix->e;
						pElement->m_initialMatrix->f = transform->matrix->f;
#endif
					}

					m_hit = 1;
				}

				m_dragging = 1;
			}
			break;
	}
#endif
#endif
	return Success;
}

ErrorCode CTransformTool::OnMouseMove(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	ASSERT(0);
#if 0
	SVGPoint pt(mouse->ptx, mouse->pty);
	SVGPoint startpt = m_startpt;

//	SVGPoint wpt(mouse->wptx, mouse->wpty);
//	SVGPoint wstartpt = m_wstartpt;

	if (m_dragging)
	{
		CComPtr<IEXMLViewGroup> viewGroup;
		view->GetViewGroup(&viewGroup);

		CComPtr<ILHTMLWindow> window;
		view->GetHTMLWindow(&window);

		CComPtr<IEElement> rootEElement;
		view->GetEElement(&rootEElement);

		CComPtr<remove> rootElement;
		rootEElement->get_domElement(&rootElement);

		CComQIPtr<ILSVGSVGElement> svgsvgElement = rootElement;

		if (m_hit == -2)	// translate
		{
			for (int i = 0; i < m_currentTransform.GetSize(); i++)
			{
				CComPtr<ILSVGMatrix> matrix;
				m_currentTransform[i]->get_matrix(&matrix);

				double x, y;
				matrix->get_e(&x);
				matrix->get_f(&y);

				double dx = pt.X-m_oldpt.X;
				double dy = pt.Y-m_oldpt.Y;
				m_currentTransform[i]->setTranslate(x+dx, y+dy);

				MessageBeep(-1);
			}
		}
		else if (m_hit == -1)	// rotate
		{
#if 0
			for (int i = 0; i < m_currentTransform.GetSize(); i++)
			{
				CComPtr<ILSVGMatrix> matrix;
				m_currentTransform[i]->get_matrix(&matrix);

				double x, y;
				matrix->get_e(&x);
				matrix->get_f(&y);

				double dx = pt.X-m_oldpt.X;
				double dy = pt.Y-m_oldpt.Y;
				m_currentTransform[i]->setRotate(x+dx, y+dy);

				MessageBeep(-1);
			}
#endif
		}
		else
		{
			switch (m_nTool)
			{
				case ID_SVGTOOL_FREETRANSFORM:
				{
	#if 0
					ATLASSERT(m_freeTransformMatrix != NULL);
	#endif
				//	ATLASSERT(m_oldfreeTransformMatrix != NULL);

				//	m_oldfreeTransformMatrix->copyFrom(m_freeTransformMatrix);

					CComPtr<ILSVGMatrix> xMat;

					if (m_hit == 0)	// Rotate
					{
						xMat = GetRotateObjectMatrix(svgsvgElement, /*w*/startpt, /*w*/pt, m_pivotPt.X, m_pivotPt.Y);
					}
					else if (m_hit == 1)	// Move
					{
						CComPtr<ILSVGMatrix> mat;
						svgsvgElement->createSVGMatrix(&mat);
						mat->translate(/*w*/pt.X-/*w*/startpt.X, /*w*/pt.Y-/*w*/startpt.Y, &xMat);
					}
					else if (m_hit >= 2)	// Scale
					{
						double cx = 0;
						double cy = 0;
						double sx;
						double sy;

						RectD bounds = m_objectsBoundingBox;

						if (mouse->nFlags & MK_ALT)
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

						CComPtr<ILSVGMatrix> mat0;

						if (mouse->nFlags & MK_CONTROL &&
							(m_hit == 3 || m_hit == 7 || m_hit == 5 || m_hit == 9))
						{
							if (m_hit == 3 || m_hit == 7)	// Skew Y
							{
								double angle = 90 - GetLineAngle(/*w*/pt.X, /*w*/startpt.Y, cx, cy) * (180/M_PI);

								CComPtr<ILSVGMatrix> mat3;
								svgsvgElement->createSVGMatrix(&mat3);

								CComPtr<ILSVGMatrix> mat2;
								mat3->translate(0, -cy, &mat2);

								CComQIPtr<ILSVGMatrix> mat1;
								mat2->skewY(angle, &mat1);

								mat1->translate(0, cy, &mat0);
							}
							else	// SkewX
							{
								double angle = GetLineAngle(/*w*/startpt.X, /*w*/pt.Y, cx, cy) * (180/M_PI);

								CComPtr<ILSVGMatrix> mat3;
								svgsvgElement->createSVGMatrix(&mat3);

								CComPtr<ILSVGMatrix> mat2;
								mat3->translate(-cx, 0, &mat2);

								CComQIPtr<ILSVGMatrix> mat1;
								mat2->skewX(angle, &mat1);

								mat1->translate(cx, 0, &mat0);
							}
						}
						else
						{
							svgsvgElement->createSVGMatrix(&mat0);
						}

	#if 0
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
	#endif

						if (m_hit == 2 || m_hit == 4 || m_hit == 6 || m_hit == 8)
						{
							sx = (/*w*/pt.X - cx)/(/*w*/startpt.X-m_offsetPt.X - cx);
							sy = (/*w*/pt.Y - cy)/(/*w*/startpt.Y-m_offsetPt.Y - cy);
						}
						else if (m_hit == 3 || m_hit == 7)
						{
							sx = 1;
							sy = (/*w*/pt.Y - cy)/(/*w*/startpt.Y-m_offsetPt.Y - cy);
						}
						else if (m_hit == 5 || m_hit == 9)
						{
							sx = (/*w*/pt.X - cx)/(/*w*/startpt.X-m_offsetPt.X - cx);
							sy = 1;
						}

						CComPtr<ILSVGMatrix> mat1;
						mat0->translate(-cx, -cy, &mat1);

						CComQIPtr<ILSVGMatrix> mat2;
						mat1->scaleNonUniform(sx, sy, &mat2);

						mat2->translate(cx, cy, &xMat);
					}

					ATLASSERT(xMat != NULL);
	#if 0
					ATLASSERT(m_freeTransformMatrix != NULL);
	#endif

					m_freeTransformMatrix = xMat;
					for (int i = 0; i < m_currentTransform.GetSize(); i++)
					{
						CComPtr<IEElement> eElement;
						m_element[i]->get_eElement(&eElement);

						CComPtr<remove> domElement;
						eElement->get_domElement(&domElement);

						CComQIPtr<ILSVGTransformable> objectTransformable = domElement;
						if (objectTransformable)
						{
							CComPtr<ILDOMNode> parentNode;
							domElement->get_parentNode(&parentNode);

							CComPtr<ILSVGMatrix> parentCTM;
							window->svgGetScreenCTM((ILSVGElement*)parentNode.p, &parentCTM);

							CComPtr<ILSVGMatrix> iparentCTM;
							parentCTM->inverse(&iparentCTM);

							CComPtr<ILSVGMatrix> mat;
							xMat->multiply(iparentCTM, &mat);

							CComPtr<ILSVGMatrix> mat2;
							parentCTM->multiply(mat, &mat2);

							m_currentTransform[i]->setMatrix(mat2);
						}
						else
						{
							MessageBeep(-1);
							m_currentTransform[i]->setMatrix(xMat);
						}
					}
				}
				break;
			}
		}
	}
	m_oldpt = pt;
#endif
	return Success;
}

ErrorCode CTransformTool::OnButtonUp(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	ASSERT(0);
#if 0
	Web::CHTMLWindow* window = view->GetHTMLWindow();

	if (m_dragging)
	{
		window->captureMouse(VARIANT_FALSE);

		m_dragging = 0;
	#if 0		// TODO have this
		ATLASSERT(m_freeTransformMatrix != NULL);
	#endif
		m_freeTransformMatrix.Release();

	#if 1
		CalculateObjectsBoundingBox(view);
	#endif
	}
#endif
	return Success;
}

ErrorCode CTransformTool::OnSetCursor(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	ASSERT(0);
#if 0
	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<IEElement> rootEElement;
	view->GetEElement(&rootEElement);

	CComPtr<remove> rootElement;
	rootEElement->get_domElement(&rootElement);

	CComQIPtr<ILSVGSVGElement> svgsvgElement = rootElement;

	CComQIPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

#if 0
	double translateX;
	double translateY;
	window->get_currentTranslateX(&translateX);
	window->get_currentTranslateY(&translateY);

	double magnify;
	window->get_magnify(&magnify);

	CComPtr<ILSVGMatrix> viewMatrix;

	CComPtr<ILSVGMatrix> mat1;
	svgsvgElement->createSVGMatrix(&mat1);
	CComPtr<ILSVGMatrix> mat;
	mat1->scaleNonUniform(magnify, magnify, &mat);
	mat->translate(translateX, translateY, &viewMatrix);
#endif

	SVGPoint/*Gdiplus::Point*/ pt(mouse->ptx, mouse->pty);
//	SVGPoint dpt(mouse->dptx, mouse->dpty);

	HCURSOR hCursor = NULL;

	if (m_dragging)
	{
		hCursor = m_startDragCursor;

		if (mouse->nFlags & MK_CONTROL/*bCtrl*/)
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

#if 0
		if (m_targetObjects.GetSize() > 0)
#endif
		{
			RectD bounds = m_objectsBoundingBox;

			if (nResource == 0)
			{
				SVGPoint pts[8] =
				{
					SVGPoint(bounds.X, bounds.Y),
					SVGPoint(bounds.X+bounds.Width/2, bounds.Y),
					SVGPoint(bounds.X+bounds.Width, bounds.Y),
					SVGPoint(bounds.X+bounds.Width, bounds.Y+bounds.Height/2),
					SVGPoint(bounds.X+bounds.Width, bounds.Y+bounds.Height),
					SVGPoint(bounds.X+bounds.Width/2, bounds.Y+bounds.Height),
					SVGPoint(bounds.X, bounds.Y+bounds.Height),
					SVGPoint(bounds.X, bounds.Y+bounds.Height/2),
				};

				SVGPoint xpts[8];
				for (int npt = 0; npt < 8; npt++)
				{
					xpts[npt] = pts[npt];//.matrixTransform(viewMatrix);
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
					if ((fabs(/*d*/pt.X-xpts[i].X) <= 6) && (fabs(/*d*/pt.Y-xpts[i].Y) <= 6))
					{
						nResource = nCursors[i];
						break;
					}
				}
			}

			if (nResource == 0)
			{
				/*
				CComPtr<ILSVGMatrix> imatrix;
				viewMatrix->inverse(&imatrix);
				*/

				SVGPoint xpt = pt;
				//xpt = dpt.matrixTransform(imatrix);

				if (xpt.X > bounds.X && xpt.Y > bounds.Y &&
					xpt.X < bounds.X+bounds.Width && xpt.Y < bounds.Y+bounds.Height)
				{
					nResource = IDC_SELECT_SELECTED;	// Inside
				}
				else	// Outside, rotate
				{
					PointD center;
					center.X = bounds.X + bounds.Width/2;
					center.Y = bounds.Y + bounds.Height/2;

					double angle = GetLineAngle(center.X, center.Y, xpt.X, xpt.Y)  * (180/M_PI);

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

	if (hCursor)
	{
		::SetCursor(hCursor);
		return Success;
	}
#endif
	return Success_False;
}

ErrorCode CTransformTool::OnActivate(ILXMLEditorApp* app)
{
	return Success;
}

ErrorCode CTransformTool::OnDeactivate(ILXMLEditorApp* app)
{
	// TODO: Add your implementation code here

	return Success;
}

ErrorCode CTransformTool::Paint(/*[in]*/ ISVGView* view, /*[in]*/ long dragging, UI::Graphics* pGraphics)
{
	ASSERT(0);
#if 0
	if (!dragging)
	{
		CalculateObjectsBoundingBox(view);
	}

	CComPtr<IEXMLViewGroup> viewGroup;
	view->GetViewGroup(&viewGroup);

	CComPtr<IEElement> rootEElement;
	view->GetEElement(&rootEElement);

	CComPtr<remove> rootElement;
	rootEElement->get_domElement(&rootElement);

	CComQIPtr<ILSVGSVGElement> svgsvgElement = rootElement;

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	//double magnify;??
	//window->get_magnify(&magnify);??

	CComPtr<ILSVGMatrix> mat;
	svgsvgElement->createSVGMatrix(&mat);

	CComPtr<ILSVGMatrix> viewMatrix = mat;
	//mat->scaleNonUniform(magnify, magnify, &viewMatrix); ??

	long selectedCount;
	viewGroup->GetSelectedCount(&selectedCount);

	if (selectedCount > 0)
	{
		Gdiplus::Graphics graphics(hDC);

		CComPtr<IESelectedElement> selectedElement;
		viewGroup->GetSelectedElementN(0, &selectedElement);

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<remove> domElement;
		eElement->get_domElement(&domElement);

		CComPtr<remove> layer;
		SVGGetLayer(domElement, &layer);

		COLORREF layerColorRef = GetLayerColor(layer);

		Gdiplus::Color layerColor(GetRValue(layerColorRef), GetGValue(layerColorRef), GetBValue(layerColorRef));

		Gdiplus::Pen pen(layerColor);
		Gdiplus::SolidBrush brush(layerColor);

		RectD bounds = m_objectsBoundingBox;

		SVGPoint pts[8] =
		{
			SVGPoint(bounds.X, bounds.Y),
			SVGPoint(bounds.X+bounds.Width/2, bounds.Y),
			SVGPoint(bounds.X+bounds.Width, bounds.Y),
			SVGPoint(bounds.X+bounds.Width, bounds.Y+bounds.Height/2),
			SVGPoint(bounds.X+bounds.Width, bounds.Y+bounds.Height),
			SVGPoint(bounds.X+bounds.Width/2, bounds.Y+bounds.Height),
			SVGPoint(bounds.X, bounds.Y+bounds.Height),
			SVGPoint(bounds.X, bounds.Y+bounds.Height/2),
		};

		/*
		CComPtr<ILSVGMatrix> m_matrix;
		svgsvgElement->createSVGMatrix(&m_matrix);
		*/

		CComPtr<ILSVGMatrix> mat;
		if (m_freeTransformMatrix)
			m_freeTransformMatrix->multiply(viewMatrix, &mat);
		else
			mat = viewMatrix;

		Gdiplus::PointF xpts[8];

		for (int i = 0; i < 8; i++)
		{
			xpts[i] = pts[i].matrixTransform(mat);
		}

	// Outline
		graphics.DrawLine(&pen, xpts[0], xpts[2]);
		graphics.DrawLine(&pen, xpts[2], xpts[4]);
		graphics.DrawLine(&pen, xpts[4], xpts[6]);
		graphics.DrawLine(&pen, xpts[6], xpts[0]);

		if (!dragging)
		{
		// Size handles
			for (i = 0; i < 8; i++)
			{
				graphics.FillRectangle(&brush, (int)(xpts[i].X-2), (int)(xpts[i].Y-2), (4), (4));
			}
		}
	}
#endif
	return Success;
}

// Plugin
//ErrorCode CTransformToolPlugin::Startup(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app)
//{
ErrorCode CTransformToolPlugin::SetSite(ILXMLEditorPluginClass* self)
{
	ASSERT(0);
#if 0
	m_spAddinSite = self;

	if (m_spAddinSite)
	{
		CComPtr<ILXMLEditorApp> app;
		self->GetApp(&app);
		CComQIPtr<ILXAddin> lxapp = app;

		CComQIPtr<ILXAddinSite> site;
		lxapp->GetSite(&site);

		ATLASSERT(0);
#if 0
		CComPtr<IUIManager> uiManager;
		site->GetUIManager((IUnknown**)&uiManager);

		app->AddTool(self, this, NULL, ID_SVGTOOL_ROTATE, L"Rotate", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_SCALE, L"Scale", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_FREETRANSFORM, L"Free Transform", L"tool_ellipse.bmp");

		uiManager->AddToolbarCommands(_Module.GetResourceInstance(), IDR_TRANSFORMTOOLS);
#endif
	}
#endif
	return Success;
}

#if 0
ErrorCode CTransformToolPlugin::Shutdown(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app)
{
	return Success;
}
#endif

ErrorCode CTransformToolPlugin::FindTool(/*[in]*/ long id, System::Object* *pdlg, /*[out,retval]*/ ISVGTool** pVal)
{

	*pVal = NULL;
#if 0
	CComObject<CTransformTool>* pTool;
	CComObject<CTransformTool>::CreateInstance(&pTool);
	if (pTool)
	{
		pTool->AddRef();
		pTool->m_nTool = id;

		*pVal = pTool;
	}
#endif
	return Success;
}

ErrorCode CTransformTool::Options(UI::Control* hParent)
{
	// TODO: Add your implementation code here

	return Success;
}

}	// LXmlEdit
}
