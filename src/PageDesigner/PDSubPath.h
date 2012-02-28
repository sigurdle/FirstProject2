class CPDDocument;

class CBezierPoint : public BezierPoint
{
public:
	CBezierPoint()
	{
	}

	CBezierPoint(double _x, double _y, double _x1, double _y1, double _x2, double _y2)
	{
		x = _x;
		y = _y;
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;
	}

	operator = (BezierPoint& pt)
	{
		x = pt.x;
		y = pt.y;
		x1 = pt.x1;
		y1 = pt.y1;
		x2 = pt.x2;
		y2 = pt.y2;
	}

	void Move(double dx, double dy)
	{
		x += dx;
		x1 += dx;
		x2 += dx;

		y += dy;
		y1 += dy;
		y2 += dy;
	}
};

class CPDPath;

class ATL_NO_VTABLE CPDSubPath : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPDSubPath,
	public CNotifySendImpl<CPDSubPath>
{
public:
	CPDSubPath()
	{
		m_pOwnerPath = NULL;

		m_closed = VARIANT_FALSE;

		m_points.SetSize(0, 1000);
	}

	CPDPath* m_pOwnerPath;

	VARIANT_BOOL m_closed;

	CArray<CBezierPoint,CBezierPoint&> m_points;

	void RenderToGraphicsPath(Gdiplus::GraphicsPath* path);

	_bstr_t saveString();
	BSTR parseString(BSTR s);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDSubPath)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDSubPath)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

// IPDSubPath
public:
	STDMETHOD(removeAllPoints)();
	STDMETHOD(appendSubPathPoints)(/*[in]*/ IPDSubPath* subpath);
	STDMETHOD(deleteAnchorPoint)(/*[in]*/ long index);
	STDMETHOD(insertAnchorPointAt)(/*[in]*/ long segment, /*[in]*/ double t);
	STDMETHOD(setLine)(/*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2);
	STDMETHOD(getPointOnLength)(/*[in]*/ double onlength, /*[out]*/ double* px, /*[out]*/ double* py, /*[out]*/ double* angle);
	STDMETHOD(getLength)(/*[out,retval]*/ double* pVal);
	STDMETHOD(insertPoint)(/*[in]*/ long index, /*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2);
	STDMETHOD(appendPoint)(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2, /*[out,retval]*/ long *pVal);
	STDMETHOD(Move)(/*[in]*/ double dx, /*[in]*/ double dy);
	STDMETHOD(setRectangle)(/*[in]*/ double left, /*[in]*/ double top, /*[in]*/ double right, /*[in]*/ double bottom);
	STDMETHOD(setEllipse)(/*[in]*/ double left, /*[in]*/ double top, /*[in]*/ double right, /*[in]*/ double bottom);
	STDMETHOD(get_pointCount)(/*[out, retval]*/ long* pVal);
	STDMETHOD(get_closed)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_closed)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(setPoint)(/*[in]*/ long index, /*[in]*/ BezierPoint* point);
	STDMETHOD(getPoint)(/*[in]*/ long index, /*[out,retval]*/ BezierPoint* pVal);
	STDMETHOD(reverse)();
};
