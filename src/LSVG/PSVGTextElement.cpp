#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGTextElement.h"
#include "SVGTextElement.h"

namespace System
{
namespace Web
{

void DrawPathSegList(SVGPathSegList* seglist, LDraw::GraphicsPathF* path, SVGMatrix* matrix);
//void GetPathSegListBBox(SVGPathSegList* seglist, gmMatrix3& matrix, LDraw::RectD* bbox);

PSVGTextElement::PSVGTextElement(SVGTextElement* element) : PSVGTextPositioningElement(element)
{
}

/*
//virtual
LDraw::Matrix3d* PSVGTextElement::GetLocalAnimatedMatrix()
{
	SVGTextElement* psvgElement = static_cast<SVGTextElement*>(m_pNode);

	LDraw::Matrix3d* matrix = psvgElement->m_transform->m_animVal->consolidateToMatrix();
	matrix = *matrix * *m_animateMotionMatrix;

	return matrix;
}
*/

//virtual
gm::RectD PSVGTextElement::GetScreenBBox()
{
// TODO, could get the tightest bounding box
	gm::RectD bbox;
	PSVGElement::GetScreenBBoxFromBounds(m_bounds, &bbox);

	return bbox;
}

void PSVGTextElement::CalculateBounds()
{
	PSVGElement::FreeCachedBitmap();

	TextLayoutContext tlc;	// curpos,initialpos are set to 0,0

	LayoutText(&tlc, true, true);

	tlc.AlignChunk(this);

	TransformGlyphs();
}

// virtual
bool PSVGTextElement::HitText(gm::matrix3d matrix, gm::PointD pt, PNode** ppNode, long* poffset)
{
	double d = 99999999;
	return GetTextUnderPoint(matrix, pt, ppNode, poffset, d);
}

// virtual
bool PSVGTextElement::HitTest(double x, double y, long pointerEvents)
{
	bool bOver = false;

	PNode* pNode;
	long offset;
	bOver = PSVGTextContentElement::HitTestCharacters(gm::PointD(x, y), pointerEvents, &pNode, &offset);

	return bOver;
}

}	// Web
}	// System
