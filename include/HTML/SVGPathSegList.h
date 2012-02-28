#ifndef Web_SVGPathSegList_h
#define Web_SVGPathSegList_h

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegList : public Object, ISVGList//, public ISVGPathSegList
{
public:
	CTOR SVGPathSegList()
	{
		m_bLockUpdate = 0;
		m_nChanges = 0;

		m_pListener = NULL;
	}

	~SVGPathSegList()
	{
		ASSERT(m_pListener == NULL);
	}

	void RemoveAll();
	void RemoveItem(SVGPathSeg* seg);

	void AddSegList(const SVGPathSegList* seglist);
	void AddSegListNoUpdate(const SVGPathSegList* seglist);

	bool getPointOnLength(double onlength, double *pxt, double *pyt, double *pangle);
	double getLength() const;

	bool ParsePathData(StringIn str_pathdata);
	String StringFromPathSegList();
	void NormalizePathSegList(SVGPathSegList* inseglist);

	bool InterpolateValue(SVGPathSegList* a, SVGPathSegList* b, double t);

	UINT AppendQuadBSplineToBezier(gm::PointD start, gm::PointD* lpCurve, int count);
#if 0
	UINT AppendQuadBSplineToBezier(POINTFX start, LPTTPOLYCURVE lpCurve, double offsetx, double offsety);
#endif

//	void CubicSmooth(double x, double y, double x2, double y2, double& oldx, double& oldy, double& oldx2, double& oldy2, LSVGPathSegType oldsegType);
	void QuadraticSmooth(double x, double y, double& oldx, double& oldy, double& oldx2, double& oldy2, SVGPathSegType oldsegType);

	void ChangedSeg();

	//HRESULT AddCharToSegList(MSWindows::HDC hdc, UINT ch, double offsetx, double offsety);

	void matrixTransform(const gm::matrix3d& transform);
	void matrixTransform(SVGMatrix* transform);

	void Offset(double dx, double dy);
	unsigned int get_numberOfItems() const;
	void clear();
	SVGPathSeg* appendItem(SVGPathSeg* newItem);
	SVGPathSeg* removeItem(unsigned int index);
	SVGPathSeg* replaceItem(SVGPathSeg* newItem, unsigned int index);
	SVGPathSeg* insertItemBefore(SVGPathSeg* newItem, unsigned int index);
	SVGPathSeg* getItem(unsigned int index) const;
	SVGPathSeg* initialize(SVGPathSeg* newItem);
// Extensions
	void AddEllipse(/*[in]*/ double cx, /*[in]*/ double cy, /*[in]*/ double rx, /*[in]*/ double ry);
	void AddRect(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height);
	void AddRoundRect(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height, /*[in]*/ double rx, /*[in]*/ double ry);
	void AddLine(/*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2);
	void AddMoveTo(/*[in]*/ double x, /*[in]*/ double y);
	void AddLineTo(/*[in]*/ double x, /*[in]*/ double y);
	void AddCloseFigure();

	void UnlockUpdate();	// TODO remove
	void LockUpdate();	// TODO remove

public:

	vector<SVGPathSeg*, __gc_allocator> m_items;

	ISVGPathSegListListener* m_pListener;

	int m_bLockUpdate;
	int m_nChanges;
};

}	// Web
}

#endif // Web_SVGPathSegList_h
