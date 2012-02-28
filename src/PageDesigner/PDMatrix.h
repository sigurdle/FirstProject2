#pragma once

#include "resource.h"

class CPDDocument;

#include "..\gm\gmMat3.h"
#include "..\gm\gmVec2.h"

class ATL_NO_VTABLE CPDMatrix : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDMatrix, &CLSID_PDMatrix>,
	public IPDMatrix,
	public IObjectSerializable
{
public:
	CPDMatrix()
	{
		m_matrix = gmMatrix3::identity();
	}

	gmMatrix3	m_matrix;

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_PDMATRIX)

BEGIN_COM_MAP(CPDMatrix)
	COM_INTERFACE_ENTRY(IPDMatrix)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// IPDMatrix
public:
	STDMETHOD(setRotate)(/*[in]*/ double angle);
	STDMETHOD(transpose)(/*[out,retval]*/ IPDMatrix* *pVal);
	STDMETHOD(copyFrom)(/*[in]*/ IPDMatrix* from);
	STDMETHOD(skewY)(/*[in]*/ double angle, /*[out,retval]*/ IPDMatrix* *pVal);
	STDMETHOD(skewX)(/*[in]*/ double angle, /*[out,retval]*/ IPDMatrix* *pVal);
	STDMETHOD(getRotation)(/*[out,retval]*/ double* pVal);
	STDMETHOD(multiply)(/*[in]*/ IPDMatrix* matrix, /*[out,retval]*/ IPDMatrix* *pVal);
	STDMETHOD(setScaleNonUniform)(/*[in]*/ double sx, /*[in]*/ double sy);
	STDMETHOD(setTranslate)(/*[in]*/ double dx, /*[in]*/ double dy);
	STDMETHOD(transformPoint)(/*[in]*/ PointD* point, /*[out,retval]*/ PointD* pVal);
	STDMETHOD(inverse)(/*[out,retval]*/ IPDMatrix* *pVal);
	STDMETHOD(transformBezierPoint)(/*[in]*/ BezierPoint* point, /*[out,retval]*/ BezierPoint* pVal);
	STDMETHOD(scaleNonUniform)(/*[in]*/ double sx, /*[in]*/ double sy, /*[out,retval]*/ IPDMatrix* *pVal);
	STDMETHOD(rotate)(/*[in]*/ double angle, /*[out,retval]*/ IPDMatrix* *pVal);
	STDMETHOD(translate)(/*[in]*/ double dx, /*[in]*/ double dy, /*[out,retval]*/ IPDMatrix* *pVal);
	STDMETHOD(get_f)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_f)(/*[in]*/ double newVal);
	STDMETHOD(get_e)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_e)(/*[in]*/ double newVal);
	STDMETHOD(get_d)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_d)(/*[in]*/ double newVal);
	STDMETHOD(get_c)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_c)(/*[in]*/ double newVal);
	STDMETHOD(get_b)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_b)(/*[in]*/ double newVal);
	STDMETHOD(get_a)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_a)(/*[in]*/ double newVal);
//	STDMETHOD(saveAsXML)(/*[in]*/ IDOMDocument* document, /*[in]*/ IDOMNode* node, BOOL saveId);
//	STDMETHOD(loadXML)(/*[in]*/ IDOMNode* node);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID);
};
