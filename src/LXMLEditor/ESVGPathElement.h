#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CBezierPoint
{
public:
	double x1;
	double y1;
	double x;
	double y;
	double x2;
	double y2;

	void matrixTransform(Web::SVGMatrix* matrix)
	{
		LDraw::PointD xpt;
		
		xpt = matrix->m_matrix.transform(LDraw::PointD(x1, y1));
		x1 = xpt.X;
		y1 = xpt.Y;

		xpt = matrix->m_matrix.transform(LDraw::PointD(x, y));
		x = xpt.X;
		y = xpt.Y;

		xpt = matrix->m_matrix.transform(LDraw::PointD(x2, y2));
		x2 = xpt.X;
		y2 = xpt.Y;
	}
};

//class CPathElement;
class CESVGPath;

class CSubPath : public System::Object
// 	public CComObjectRootEx<CComSingleThreadModel>,
//	public IESVGSubPath
{
public:
	CSubPath()
	{
		m_pPath = NULL;
		m_bClosed = false;
		m_segIndex = -1;
		m_nsegs = 0;
	}

//	CPathElement* m_pPath;
	CESVGPath* m_pPath;

	int m_segIndex;
	int m_nsegs;

	double m_firstx;
	double m_firsty;
	double m_lastx;
	double m_lasty;

	bool m_bClosed;

	void appendPoint(double x, double y, double x1, double y1, double x2, double y2, long* curveCp);

	void GetPathSeg(int segindex, CBezierPoint* _seg);
	void PutPathSeg(int segindex, CBezierPoint* _seg);

	bool get_closed()
	{
		return m_bClosed? true: false;
	}

	void set_closed(bool newVal)
	{
		ASSERT(0);
		/*
		if ((m_bClosed == 0) != (newVal == 0))
		{
			m_bClosed = newVal? true: false;
		}
		*/
	}

public:

	uint get_pointCount();
};

class CESVGPath :
// 	public CComObjectRootEx<CComSingleThreadModel>,
	public IESVGPath
{
public:
	CESVGPath()
	{
		m_segList = NULL;
		m_pathElement = NULL;
	}

	Web::SVGPathElement* m_pathElement;

	Web::SVGPathSegList* m_segList;
	Array<CSubPath*> m_subPaths;

	ErrorCode SetPathSegList(Web::SVGPathSegList *seglist);
	ErrorCode GetPathSeg(int segindex, CBezierPoint* _seg);
	ErrorCode PutPathSeg(int segindex, CBezierPoint* _seg);

	ErrorCode InsertPointAfter(/*[in]*/ long index, /*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2);
	ErrorCode InsertPointBefore(/*[in]*/ long index, /*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2);

	long GetSubPathIndex(CSubPath* pSubPath);
	void RemoveSubPath(CSubPath* pSubPath);

	/*
BEGIN_COM_MAP(CESVGPath)
	COM_INTERFACE_ENTRY(IESVGPath)
END_COM_MAP()
*/

public:
	ErrorCode GetSubPathCount(/*[out,retval]*/ long *pVal)
	{
		*pVal = m_subPaths.GetSize();
		return Success;
	}

	ErrorCode GetSubPath(/*[in]*/ long index, /*[out,retval]*/ CSubPath* *pVal)
	{
		*pVal = m_subPaths[index];
	//	(*pVal)->AddRef();
		return Success;
	}

	ErrorCode GetSubPathFromIndex(long index, long *pindex, CSubPath* *psubpath)
	{
		int nsubpath;
		for (nsubpath = 0; nsubpath < m_subPaths.GetSize(); nsubpath++)
		{
			long npoints = m_subPaths[nsubpath]->m_nsegs;//points.GetSize();
			if (index-npoints < 0) break;

			index -= npoints;
		}

		if (pindex) *pindex = index;
		if (psubpath) (*psubpath = m_subPaths[nsubpath]);//->AddRef();

		return Success;
	}

	Web::SVGPathSegList* GetPathSegList()
	{
		return m_segList;
	}

	ErrorCode AppendPath(IESVGPath* path);
	ErrorCode InsertSubPathBefore(/*[in]*/ CSubPath* path, /*[in]*/ long index);
	ErrorCode getPointNearPath(/*[in]*/ Web::SVGMatrix* matrix, /*[in]*/ double mousex, /*[in]*/ double mousey, /*[in]*/ double tolerance, /*[out]*/ long* segindex, /*[out]*/ double* pt, /*[out,retval]*/ bool* pVal);
};

class CESVGPathElement :
	public CESVGElementImpl,
	public IESVGDrawOutline
{
protected:
//	CComObject<CESVGPath>* m_pPath;

public:
	CESVGPathElement()
	{
//		m_pPath = NULL;
	}


#if 0
	ErrorCode GetPath(/*[out,retval]*/ IESVGPath* *pVal)
	{
		ATLASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;

		if (m_pPath == NULL)
		{
			CComQIPtr<ILSVGPathElement> pathElement = m_domElement;
			CComQIPtr<ILSVGAnimatedPathData> pathData = pathElement;

			CComPtr<ILSVGPathSegList> seglist;
			pathData->get_normalizedPathSegList(&seglist);

			CComObject<CESVGPath>::CreateInstance(&m_pPath);
			m_pPath->AddRef();
			m_pPath->m_pathElement = pathElement;
			m_pPath->SetPathSegList(seglist);
		}

		*pVal = m_pPath;
		(*pVal)->AddRef();

		return S_OK;
	}
#endif

	ErrorCode CreateSelectedElement(CEXMLViewGroup* viewGroup, IESelectedElement* *pVal);

	bool m_bInSubPath;
//	CArray<int,int> m_selectedPoints;
	
	Array<int> m_subPoints;
	Array<LDraw::PointD> m_flatPoints;

	void SetPolyPointsFromSegList();
	void AddFlatCurve(int i, double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double& oldxt, double& oldyt, int& count);
	void DrawPolyPoints(MSWindows::HDC hDC);

	void ConvertFlatToCurves(Web::SVGPathSegList* seglist);

//	double m_lastx;
//	double m_lasty;

//	void GetPathSeg(ILSVGPathSegList* seglist, int segindex, CBezierPoint* seg);
//	void PutPathSeg(ILSVGPathSegList* seglist, int segindex, CBezierPoint* seg);

	void DrawPathCurve(Web::SVGPathSegList* seglist, Web::SVGMatrix* addmatrix, MSWindows::HDC hDC);
//	void SetPathSegControlPointsSameLength(ILSVGPathSegList* seglist, int segindex, int ctlindex, double ctlx, double ctly);
	void SetPathSegControlPoints(Web::SVGPathSegList* seglist, int segindex, int ctlindex, double ctlx, double ctly);
	void SetPathSegControlPoint(Web::SVGPathSegList* seglist, int segindex, int ctlindex, double ctlx, double ctly);

	void SetControlPointsSameLength(int segindex, int ctlindex, double ctlx, double ctly);
	void SetPathSegControlPoints(int segindex, int ctlindex, double ctlx, double ctly);

	void ReverseSelectedSubPaths();
//	void MovePoints(ILSVGPathSegList* seglist, double dx, double dy, BOOL bAll = TRUE);
//	void ReleaseCompound();

	/*
BEGIN_COM_MAP(CESVGPathElement)
	COM_INTERFACE_ENTRY(IENode)
	COM_INTERFACE_ENTRY(IEElement)
	COM_INTERFACE_ENTRY(IESVGElement)
	COM_INTERFACE_ENTRY(IESVGPathElement)
	COM_INTERFACE_ENTRY(IESVGDrawOutline)
END_COM_MAP()
*/

	ErrorCode put_domElement(/*[in]*/ Web::Element* newVal);

	ErrorCode Move(ISVGView* view, double dx, double dy);
	ErrorCode Resize(ISVGView* view, double x, double y, double width, double height);
	long GetResizability()
	{
		return 1;
	}
//	virtual void Scale(double cx, double cy, double sx, double sy);
//	virtual void DrawPathCurve(HDC hDC, ILSVGMatrix* addmatrix);
	virtual void SelectPointsInRect(double x1, double y1, double x2, double y2);

	ErrorCode HitTest(Web::SVGPathSegList* seglist, ISVGView* view, Web::SVGSVGElement* svgsvgElement, Web::SVGMatrix* ctm, double ptx, double pty, /*long tool,*/ _SVGHitData* hit);
	ErrorCode HitTest(ISVGView* view, Web::SVGSVGElement* svgsvgElement, Web::SVGMatrix* ctm, double ptx, double pty, /*long tool,*/ _SVGHitData* hit);

// IESVGDrawOutline
	ErrorCode DrawOutline(Web::SVGPathSegList* seglist, UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);
	void DrawOutline(UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);
};

}	// LXmlEdit
}
