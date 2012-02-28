#pragma once

#include "ESelectedElementImpl.h"

#include "ESVGPathElement.h"//class CPathElement;

namespace System
{
namespace LXmlEdit
{

class CESelectedSVGPathElement : 
	public CESelectedElementImpl<IESelectedSVGPathElement>,
	public IESelectedSVGPoints,
	public IESVGDrawSelection
{
public:
	CESelectedSVGPathElement()
	{
	}

	~CESelectedSVGPathElement()
	{
	}

protected:
	Array<int> m_selectedPoints;
	Array<int> m_selectedSegments;

public:

	CESVGPathElement* GetPath();

	void DeleteAnchorPoint(int index);
	void InsertPointBefore(/*[in]*/ long index, /*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2);
	void InsertPointAfter(/*[in]*/ long index, /*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2);

	bool IsSegmentSelected(long index);

	bool IsAnchorSelected(long index);

	void IsControlPointVisible(long nsubpathpoints, int nAnchorsSelected, int ntotalpoints, int npt, bool* c1, bool* c2);

	int FindPoint(Web::SVGMatrix* matrix, double mousex, double mousey, long& ctl);
	int FindPoint(Web::SVGPathSegList* seglist, Web::SVGMatrix* matrix, double mousex, double mousey, long& ctl);

	void MovePoints(Web::SVGPathSegList* seglist, double dx, double dy, /*LDraw::RectF& invalidBounds,*/ bool bAll /* = true */);
	void MovePoints(double dx, double dy, /*LDraw::RectF& invalidBounds,*/ bool bAll = true);

	void InsertAnchorPoint(int segindex, double t);

	ErrorCode HitTest(ISVGView* view, Web::SVGSVGElement* svgsvgElement, Web::SVGMatrix* ctm, double ptx, double pty, long tool, _SVGHitData* hit);
	virtual void MoveSelectedPoints(_SVGHitData* hitdata, LDraw::PointD xnewpt2, LDraw::PointD xoldpt2/*, LDraw::RectF& invalidBounds,*/);
	void MoveSelectedPoints(Web::SVGPathSegList* seglist, _SVGHitData* hitdata, LDraw::PointD xnewpt2, LDraw::PointD xoldpt2/*, LDraw::RectF& invalidBounds,*/);

public:
// IESelectedSVGPoints
	ErrorCode SelectAnchor(uint index);
	ErrorCode DeselectAnchor(uint index);
	ErrorCode SelectSegment(uint index);
	ErrorCode DeselectSegment(uint index);

	void DeleteSelection(Web::SVGPathSegList* seglist);
	ErrorCode DeleteSelection();

	void DeselectAllPoints()
	{
		m_selectedPoints.RemoveAll();
		m_selectedSegments.RemoveAll();
	}
// IESVGDrawSelection
	void DrawSelection(Web::SVGPathSegList* seglist, UI::Graphics* pGraphics, LDraw::Color& color, Web::SVGMatrix* matrix);
	virtual ErrorCode DrawSelection(UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);
};

}	// LXmlEdit
}
