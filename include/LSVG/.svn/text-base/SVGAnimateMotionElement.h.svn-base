#ifndef w3c_SVGAnimateMotionElement_h
#define w3c_SVGAnimateMotionElement_h

namespace System
{
namespace Web
{

class SVGEXT CLSVGCoordinate : 
	public CSingleObject
{
public:
	CTOR CLSVGCoordinate()
	{
		m_x = NULL;
		m_y = NULL;
	}

	/*
	int FinalConstruct()
	{
		CComObject<SVGLength>::CreateInstance(&m_x);
		m_x->AddRef();

		CComObject<SVGLength>::CreateInstance(&m_y);
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
	*/

	SVGLength* m_x;
	SVGLength* m_y;

	void operator = (const CLSVGCoordinate& value)
	{
		m_x = value.m_x;
		m_y = value.m_y;
	}

	void operator += (const CLSVGCoordinate& value)
	{
		ASSERT(0);
	}

	void setStringValue(StringIn str)
	{
		ASSERT(0);
#if 0

		const OLECHAR* p = bstr->c_str();
		sysstring s;

		while (*p && iswspace(*p)) p++;

		s = L"";
		while (*p && !iswspace(*p))
			s += *p++;

		m_x->set_valueAsString(s);

		while (*p && iswspace(*p)) p++;

		if (*p == L',') p++;

		while (*p && iswspace(*p)) p++;
		
		s = L"";
		while (*p && !iswspace(*p))
			s += *p++;

		m_y->set_valueAsString(s);
#endif
	}

	String getStringValue()
	{
		ASSERT(0);
		return NULL;
	}

	void InterpolateValue(const CLSVGCoordinate& a, const CLSVGCoordinate& b, double t)
	{
		m_x->InterpolateValue(*a.m_x, *b.m_x, t);
		m_y->InterpolateValue(*a.m_y, *b.m_y, t);
	}

	SVGLength* get_x()
	{
		return m_x;
	}
	SVGLength* get_y()
	{
		return m_y;
	}
};

class SVGEnumerationRotateType :
	public CSingleObject
{
public:

	/*
	CLSVGEnumerationRotateType& operator * ()
	{
		return *this;
	}
	*/

	SVGEnumerationRotateType* operator -> ()
	{
		return this;
	}

	/*
	operator CLSVGEnumerationRotateType* ()
	{
		return this;
	}
	*/

	CTOR SVGEnumerationRotateType()
	{
		m_value = SVG_ROTATE_UNKNOWN;
	}

	operator SVGAnimateMotionRotateType ()
	{
		return m_value;
	}

	SVGEnumerationRotateType& operator = (SVGAnimateMotionRotateType value)
	{
		m_value = value;
	}

	SVGEnumerationRotateType& operator += (SVGAnimateMotionRotateType value)
	{
		ASSERT(0);	// ???
		//m_value = value;
		return *this;
	}

	void setStringValue(StringIn str)
	{
		if (str == L"auto")
			m_value = SVG_ROTATE_AUTO;
		else if (str == L"auto-reverse")
			m_value = SVG_ROTATE_AUTO_REVERSE;
		else
			m_value = SVG_ROTATE_ANGLE;
	}

	String getStringValue()
	{
		if (m_value == SVG_ROTATE_AUTO)
			return WSTR("auto");
		else if (m_value == SVG_ROTATE_AUTO_REVERSE)
			return WSTR("auto-reverse");
		else
			return NULL;
	}

	void InterpolateValue(const SVGEnumerationRotateType& a, const SVGEnumerationRotateType& b, double t)
	{
		ASSERT(0);
	}

	/*
	IUnknown* GetUnknown()
	{
		return NULL;
	}
	*/

	SVGAnimateMotionRotateType m_value;
};

class SVGEXT SVGAnimateMotionElement : 
	public SVGAnimationElement,//<SVGAnimateMotionElement>,
//	public ElementAnimateImpl,//<SVGAnimateMotionElement>,

	public ElementEditVALImpl<SVGAnimateMotionElement>,

//	public IElementEditVAL,	// ILNodeEditVAL
//	public ElementEditASImpl<SVGAnimateMotionElement>
//	public IElementAnimate,	// ILAnimationElement,//ILElementTime,

	public ISVGPathSegListListener

//	protected CNotifyGetImpl<SVGAnimateMotionElement>,
//	protected CNotifySendImpl<SVGAnimateMotionElement>
{
public:

	CTOR SVGAnimateMotionElement(NamedNodeMap* attributes);
	~SVGAnimateMotionElement();

	SVGPathSegList* get_pathSegList();
	SVGPathSegList* get_normalizedPathSegList();
	SVGAnimateMotionRotateType get_rotateType();
	SVGAngle* get_rotateAngle();
	void setRotateToAngle(SVGAngle* angle);

public:

	CXMLAttr2T<CreateInstanceT<CValueTypeWrapper<SVGEnumerationRotateType> > >* m_rotateType;
	CXMLAttr2T<CreateInstanceT<CValueTypeWrapper<CreateInstanceT<SVGAngle> > > >* m_rotateAngle;
	CXMLAttr2T<CreateInstanceT<CValueTypeWrapper<CreateInstanceT<SVGPathSegListValue> > > >* m_path;

protected:

	virtual void OnPathSegListChange(SVGPathSegList* pSegList)
	{
		if (pSegList == m_path->m_value->m_value->m_seglist)
		{
			m_path->OnBaseValChanged();
		}
		else if (pSegList == m_path->m_value->m_value->m_normalizedseglist)
		{
		// Copy the normalized seglist to the the seglist
			m_path->m_value->m_value->m_seglist->RemoveAll();
			m_path->m_value->m_value->m_seglist->AddSegListNoUpdate(m_path->m_value->m_value->m_normalizedseglist);

			m_path->OnBaseValChanged();
		}
	}

	virtual void SetValuesFromAttributes();

	virtual void DoAnimationForElement(Element* target);
};

}	// w3c
}

#endif // w3c_SVGAnimateMotionElement_h
