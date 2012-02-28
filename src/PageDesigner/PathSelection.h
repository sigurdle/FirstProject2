#pragma once

class CFlatSegment
{
public:
	DWORD m_pointCount : 30,
			m_bAltered : 1,
			m_bRecentAltered : 1;

	CFlatSegment()
	{
		m_pointCount = 0;
		m_bAltered = false;
		m_bRecentAltered = false;
	}
};

class CFlatSubPath
{
public:
	CArray<CDblPoint,CDblPoint> m_flatPoints;
	CArray<CFlatSegment,CFlatSegment> m_flatSegments;

	CFlatSubPath()
	{
		m_flatPoints.SetSize(0, 2000);
		m_flatSegments.SetSize(0, 500);
	}
};

class CPathSelection
{
protected:
	CComPtr<IPDPath> m_path;

public:
	CComPtr<IPDObject> m_object;

	CArray<int,int> m_selectedPoints;
	CArray<int,int> m_selectedSegments;

	CArray<CFlatSubPath*,CFlatSubPath*> m_flatSubPaths;

public:
	CPathSelection(IPDPath* path, IPDObject* object)
	{
		m_path = path;
		m_object = object;

		m_selectedPoints.SetSize(0, 2000);
		m_selectedSegments.SetSize(0, 2000);
	}

	CComPtr<IPDPath> GetPDPath()
	{
		return m_path;
	}

	void DeselectAllPoints()
	{
		m_selectedPoints.RemoveAll();
		m_selectedSegments.RemoveAll();
	}

	void MoreFlatDetail();
	void SetPolyPointsFromSegList();
//	void AddFlatCurve(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double& oldxt, double& oldyt, int& count);
	void ConvertFlatToCurves();
	void DrawPolyPoints(IPDMatrix* pdmatrix, Gdiplus::GraphicsPath* path);
	void DrawPolyPoints(IPDMatrix* pdmatrix, Gdiplus::Graphics* pGraphics, Gdiplus::Pen* pPen);
	void DeleteFlatData();

	void TransformSelectedPoint(IPDMatrix* pdmatrix);

	bool IsSubPathSelected(int nsubpath);

	void RotateSelectedPointIndexes(long rotate);

	void ReverseSelectedPath();
	void AddAnchorPoints();

	void DeleteSelection();

	void IsControlPointVisible(IPDSubPath* subpath, int nAnchorsSelected, int ntotalpoints, int npt, BOOL* c1, BOOL* c2);

	void DeleteAnchorPoint(int index);
	void InsertPointBefore(/*[in]*/ long index, /*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2);
	void InsertPointAfter(/*[in]*/ long index, /*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2);

	void SelectAllAnchors();
	void SelectAnchor(int index);
	void DeselectAnchor(int index);
	BOOL IsAnchorSelected(int index);

	void SelectSegment(int index);
	void DeselectSegment(int index);
	BOOL IsSegmentSelected(int index);

	void DrawPath(IPDMatrix* pdmatrix, IPDMatrix* pdmatrix2, Gdiplus::GraphicsPath* path);
	void DrawSelection(Gdiplus::Graphics* pGraphics, Gdiplus::Color& color, IPDMatrix* matrix);

	//BOOL GetPointOnPath(IPDMatrix* matrix, double mousex, double mousey, double tolerance, long* segindex, double* pt);
	int FindPoint(IPDMatrix* matrix, double mousex, double mousey, long& ctl);

	void MovePoints(double dx, double dy, Gdiplus::RectF& invalidBounds, bool bAll = true);
	void BezierBounds(long numberOfItems, long index, VARIANT_BOOL closed, BezierPoint seg, BezierPoint seg1, BezierPoint seg2, double& minx, double& miny, double& maxx, double& maxy);

	void SetControlPointsSameLength(int segindex, int ctlindex, double ctlx, double ctly, Gdiplus::RectF& invalidBounds);
	void SetPathSegControlPoints(int segindex, int ctlindex, double ctlx, double ctly, Gdiplus::RectF& invalidBounds);
};
