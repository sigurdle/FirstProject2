#pragma once

class CPDSubPath;
template <class T>class CPDObjectImpl;

class ATL_NO_VTABLE CPDPath : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPDPath,
	public IObjectSerializable,
	public CNotifyGetImpl<CPDPath>,
	public CNotifySendImpl<CPDPath>
{
public:
	CPDPath()
	{
	//	m_pOwnerObject = NULL;
	}

	void FinalRelease();

	//CPDObjectImpl<IPDObject>* m_pOwnerObject;

	CArray<CComObject<CPDSubPath>*, CComObject<CPDSubPath>*> m_subPaths;

	_bstr_t saveString();
	HRESULT parseString(BSTR s);

	void RenderToGraphicsPath(Gdiplus::GraphicsPath* pPath);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDPath)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDPath)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}

// IPDPath
public:
	STDMETHOD(setRectangle)(/*[in]*/ double left, /*[in]*/ double top, /*[in]*/ double right, /*[in]*/ double bottom);
	STDMETHOD(transformPoints)(/*[in]*/ IPDMatrix* matrix);
	STDMETHOD(removeSubPaths)();
	STDMETHOD(splitOnAnchor)(/*[in]*/ long index, long* pRotateVal);
	STDMETHOD(splitOnSegment)(/*[in]*/ long segindex, long* pRotateVal);
	STDMETHOD(deleteAnchorPoint)(/*[in]*/ long index);
	STDMETHOD(getSubPathFromIndex)(/*[in]*/ long index, /*[out]*/ long* pindex, /*[out, retval]*/ IPDSubPath* *psubpath);
	STDMETHOD(insertAnchorPointAt)(/*[in]*/ long segment, /*[in]*/ double t);
	STDMETHOD(IsRectangular)(/*[out,retval]*/ VARIANT_BOOL* pVal);
	STDMETHOD(getPointNearAnchorPoint)(/*[in]*/ IPDMatrix* matrix, /*[in]*/ double mousex, /*[in]*/ double mousey, /*[in]*/ double tolerance, /*[out, retval]*/ long* pIndex);
	STDMETHOD(getPointNearPath)(/*[in]*/ IPDMatrix* matrix, /*[in]*/ double mousex, /*[in]*/ double mousey, /*[in]*/ double tolerance, /*[out]*/ long* segindex, /*[out]*/ double* pt, /*[out,retval]*/ BOOL* pVal);
	STDMETHOD(offset)(/*[in]*/ double distance, /*[in]*/ double tolerance, /*[out,retval]*/ IPDPath* other);
	STDMETHOD(calculateBBox)(/*[in]*/ IPDMatrix* matrix, /*[out,retval]*/ RectD* bbox);
	STDMETHOD(insertPointAfter)(/*[in]*/ long index, /*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2);
	STDMETHOD(insertPointBefore)(/*[in]*/ long index, /*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2);
	STDMETHOD(setPoint)(/*[in]*/ long index, /*[in]*/ BezierPoint* point);
	STDMETHOD(getPoint)(/*[in]*/ long index, /*[out,retval]*/ BezierPoint* pVal);
	STDMETHOD(get_pointCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(Move)(/*[in]*/ double dx, /*[in]*/ double dy);
	STDMETHOD(createSubPath)(/*[out,retval]*/ IPDSubPath* *pVal);
	STDMETHOD(removeSubPathByIndex)(/*[in]*/ long index, /*[out,retval]*/ IPDSubPath* *pVal);
	STDMETHOD(removeSubPath)(/*[in]*/ IPDSubPath* subpath);
	STDMETHOD(insertSubPath)(/*[in]*/ long index, /*[in]*/ IPDSubPath* subPath);
	STDMETHOD(getSubPath)(/*[in]*/ long index, /*[out,retval]*/ IPDSubPath** pVal);
	STDMETHOD(get_subPathCount)(/*[out, retval]*/ long *pVal);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID);
};
