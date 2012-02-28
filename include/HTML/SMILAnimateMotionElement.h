#ifndef Web_SMILAnimateMotionElement_h
#define Web_SMILAnimateMotionElement_h

//#include "SMILAnimationElementImpl.h"

//#include "SVGPathSegList.h"
//#include "SVGPathSegListValue.h"
//#include "SVGLength.h"

#if 0
#include "LSVGAngle.h"

class CLSVGCoordinate : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ILSVGCoordinate, &IID_ILSVGCoordinate, &LIBID_LHTMLLib>,
	public CSingleObject
{
public:
	CLSVGCoordinate()
	{
		m_x = NULL;
		m_y = NULL;
	}

	int FinalConstruct()
	{
		CComObject<CLSVGLength>::CreateInstance(&m_x);
		m_x->AddRef();

		CComObject<CLSVGLength>::CreateInstance(&m_y);
		m_y->AddRef();

		return 0;
	}

	void FinalRelease()
	{
		m_x->Release();
		m_x = NULL;

		m_y->Release();
		m_y = NULL;
	}

	CComObject<CLSVGLength>* m_x;
	CComObject<CLSVGLength>* m_y;

	void operator = (CLSVGCoordinate* value)
	{
		m_x = value->m_x;
		m_y = value->m_y;
	}

	void operator += (CLSVGCoordinate* value)
	{
		ASSERT(0);
	}

	void operator = (BSTR bstr)
	{
		WCHAR* p = bstr;
		CWCharString s;

		while (*p && iswspace(*p)) p++;

		s = L"";
		while (*p && !iswspace(*p))
			s += *p++;

		m_x->put_valueAsString(s);

		while (*p && iswspace(*p)) p++;

		if (*p == L',') p++;

		while (*p && iswspace(*p)) p++;
		
		s = L"";
		while (*p && !iswspace(*p))
			s += *p++;

		m_y->put_valueAsString(s);
	}

	operator _bstr_t ()
	{
		ASSERT(0);
		return L"";
	}

	void InterpolateValue(CLSVGCoordinate* a, CLSVGCoordinate* b, double t)
	{
		m_x->InterpolateValue(a->m_x, b->m_x, t);
		m_y->InterpolateValue(a->m_y, b->m_y, t);
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLSVGCoordinate)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ILSVGCoordinate)
END_COM_MAP()

// ILSVGCoordinate
public:
	STDMETHOD(get_x)(/*[out,retval]*/ ILSVGLength* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_x;
		(*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(get_y)(/*[out,retval]*/ ILSVGLength* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_y;
		(*pVal)->AddRef();
		return S_OK;
	}
};
#endif

namespace System
{
namespace Web
{

class SMILAnimateMotionElement : 
	public SMILAnimationElement,//Impl<SMILAnimateMotionElement>,
//	public ElementAnimateImpl,//<SMILAnimateMotionElement>,

	public ElementEditVALImpl<SMILAnimateMotionElement>,

	public IElementEditVAL,	// ILNodeEditVAL
//	public CLElementEditASImpl<SMILAnimateMotionElement>
//	public IElementAnimate,	// ILAnimationElement,//ILElementTime,

	protected ISVGPathSegListListener,

	protected CNotifyGetImpl<SMILAnimateMotionElement>,
	protected CNotifySendImpl<SMILAnimateMotionElement>
{
public:

	CTOR SMILAnimateMotionElement(NamedNodeMap* attributes);
	~SMILAnimateMotionElement();

//	CComObject<CXMLAttr2T<CComObjectCreateInstance<CValueTypeWrapper<CLSVGEnumerationRotateType> > > >* m_rotateType;
//	CComObject<CXMLAttr2T<CComObjectCreateInstance<CValueTypeWrapper<CComObjectCreateInstance<CLSVGAngle> > > > >* m_rotateAngle;

	virtual void OnPathSegListChange(SVGPathSegList* pSegList);
	virtual void SetValuesFromAttributes();
	virtual void DoAnimationForElement(Element* target);

	SVGPathSegList* get_pathSegList();
	SVGPathSegList* get_normalizedPathSegList();
//	STDMETHOD(get_rotateType)(/*[out, retval]*/ LSMILAnimateMotionRotateType *pVal);
//	STDMETHOD(get_rotateAngle)(/*[out, retval]*/ ILSVGAngle* *pVal);
//	STDMETHOD(setRotateToAngle)(/*[in]*/ ILSVGAngle* angle);

	CXMLAttr2T<CreateInstanceT<CValueTypeWrapper<CreateInstanceT<SVGPathSegListValue> > > >* m_path;

protected:

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
};

}	// w3c
}

#endif // Web_SMILAnimateMotionElement_h
