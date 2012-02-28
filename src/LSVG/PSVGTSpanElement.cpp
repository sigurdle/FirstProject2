#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGTSpanElement.h"
#include "SVGTSpanElement.h"

namespace System
{
namespace Web
{

void DrawPathSegList(SVGPathSegList* seglist, LDraw::GraphicsPathF* path, SVGMatrix* matrix);
void GetPathSegListBBox(SVGPathSegList* seglist, gm::matrix3d& matrix, gm::RectD* bbox);

PSVGTSpanElement::PSVGTSpanElement(SVGTSpanElement* element) : PSVGTextPositioningElement(element)
{
}

/*
//virtual
LDraw::Matrix3d* PSVGTSpanElement::GetLocalAnimatedMatrix()
{
	SVGTSpanElement* psvgElement = static_cast<SVGTSpanElement*>(m_pNode);

	LDraw::Matrix3d* matrix = psvgElement->m_transform->m_animVal->consolidateToMatrix();
	matrix = *matrix * *m_animateMotionMatrix;

	return matrix;
}
*/

}	// w3c
}
