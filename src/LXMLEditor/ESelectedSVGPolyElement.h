#pragma once

#include "ESVGElementImpl.h"
#include "ESelectedElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CESelectedSVGPolyElement : 
	public CESelectedElementImpl<IESelectedSVGPolyElement>,
	public IESelectedSVGPoints,
	public IESVGDrawOutline,
	public IESVGDrawSelection
{
public:
	CTOR CESelectedSVGPolyElement()
	{
	}

	~CESelectedSVGPolyElement()
	{
	}

protected:
	Array<int> m_selectedPoints;
	Array<int> m_selectedSegments;

public:

	void MoveSelectedPoints(Web::SVGPointList* points, _SVGHitData* hitdata, LDraw::PointD xnewpt2, LDraw::PointD xoldpt2);

	void MoveSelectedPoints(_SVGHitData* hitdata, LDraw::PointD xnewpt2, LDraw::PointD xoldpt2/*, LDraw::RectF& invalidBounds,*/);

	bool IsAnchorSelected(uint index);
	bool IsSegmentSelected(uint index);


public:
	ErrorCode HitTest(ISVGView* view, Web::SVGSVGElement* svgsvgElement, Web::SVGMatrix* ctm, double ptx, double pty, long tool, _SVGHitData* hit);

// IESVGDrawSelection
	ErrorCode SelectAnchor(uint index);
	ErrorCode DeselectAnchor(uint index);
	/*
	ErrorCode IsAnchorSelected(long index, bool* pVal)
	{
		ASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;

		if (IsAnchorSelected(index))
			*pVal = true;
		else
			*pVal = false;

	
	  return S_OK;
	}
	*/
	ErrorCode SelectSegment(uint index);
	ErrorCode DeselectSegment(uint index);

	ErrorCode DeleteSelection();
	void DeselectAllPoints();

// IESVGDrawOutline
	void DrawOutline(UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);

// IESVGDrawSelection
	virtual ErrorCode DrawSelection(UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);
	ErrorCode DrawSelection(Web::SVGPointList* points, UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);
};

}	// LXmlEdit
}
