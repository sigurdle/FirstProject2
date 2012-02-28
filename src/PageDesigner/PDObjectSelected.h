/*
#define MATCHPOINT(x1, y1, x2, y2) ((fabs((x2)-(x1)) <= 3) && \
												(fabs((y2)-(y1)) <= 3))

*/

//class CPathSelection;

class CPDObjectSelected
{
public:
	IPDObjectUnknown* m_object;	// CComPtr ?

	CComPtr<IPDMatrix> m_initialMatrix;
	CPathSelection* m_wrapPath;

public:
	CPDObjectSelected(IPDObjectUnknown* object)
	{
		m_object = object;
		ATLASSERT(m_object != NULL);

		m_wrapPath = NULL;

		SetWrapPath();
	}

	virtual ~CPDObjectSelected();

	void SetWrapPath();
};

class CPDObjectGroupSelected : public CPDObjectSelected
{
public:
	CPDObjectGroupSelected(IPDObjectUnknown* object) : CPDObjectSelected(object)
	{
	}
};

class CPDObjectFrameSelected : public CPDObjectSelected
{
public:
/*	double m_topSoFar;
	double m_bottomSoFar;
	PointD m_threadPtLeft;
	PointD m_threadPtRight;
*/
	PointD m_pthreadPtLeft;
	double m_pthreadRotationLeft;

	PointD m_pthreadPtRight;
	double m_pthreadRotationRight;

	CPathSelection* m_path;

public:

	CPDObjectFrameSelected(IPDObjectUnknown* object, BOOL bSelectPoints);// : CPDObjectSelected(object);
	virtual ~CPDObjectFrameSelected();

//	void CalculateThreadRects();
//	void FindThreadPts(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3);

	void DrawThreadRects(Gdiplus::Graphics* pGraphics, Gdiplus::Color& color, IPDMatrix* matrix);
};
