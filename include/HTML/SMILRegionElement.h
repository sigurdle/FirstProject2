#ifndef w3c_SMILRegionElement_h
#define w3c_SMILRegionElement_h

namespace System
{
namespace Web
{

class HTMLEXT EnumerationShowBackgroundType :
	public CSingleObject
{
public:
	CTOR EnumerationShowBackgroundType()
	{
		m_value = (ShowBackgroundType)-1;	// undefined
	}

	operator ShowBackgroundType () const
	{
		return m_value;
	}

	EnumerationShowBackgroundType& operator = (ShowBackgroundType value)
	{
		m_value = value;
		return *this;
	}

	EnumerationShowBackgroundType& operator += (ShowBackgroundType value)
	{
		m_value = value;
		return *this;
	}

	void setStringValue(StringIn str)
	{
		if (str == L"always")
			m_value = SHOWBACKGROUND_ALWAYS;
		else if (str == L"whenActive")
			m_value = SHOWBACKGROUND_WHEN_ACTIVE;
		else
			m_value = SHOWBACKGROUND_ALWAYS;
	}

	String getStringValue()
	{
		ASSERT(0);
		return NULL;
	}

	void InterpolateValue(const EnumerationShowBackgroundType& a, const EnumerationShowBackgroundType& b, double t)
	{
		ASSERT(0);
	}

	System::Object* GetUnknown()
	{
		return NULL;
	}

public:

	ShowBackgroundType m_value;
};

class HTMLEXT SMILRegionElement : 
	public SMILElement,
	public SMILElementLayoutImpl<SMILRegionElement>,//ILSMILElementLayout,
	public SMILAnimationTargetImpl<SMILRegionElement>
{
public:
	CTOR SMILRegionElement(NamedNodeMap* attributes);

	void Activate(double atTime, SMILMediaElement* mediaElement);
	void Deactivate(double atTime, SMILMediaElement* mediaElement);

public:

	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<CColorValue> > > >, CValueTypeWrapper<CreateInstanceT<CColorValue> > >* m_backgroundColor;
	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<CLengthValue> > > >, CValueTypeWrapper<CreateInstanceT<CLengthValue> > >* m_left;
	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<CLengthValue> > > >, CValueTypeWrapper<CreateInstanceT<CLengthValue> > >* m_top;
	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<CLengthValue> > > >, CValueTypeWrapper<CreateInstanceT<CLengthValue> > >* m_right;
	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<CLengthValue> > > >, CValueTypeWrapper<CreateInstanceT<CLengthValue> > >* m_bottom;
	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<CLengthValue> > > >, CValueTypeWrapper<CreateInstanceT<CLengthValue> > >* m_width;
	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<CLengthValue> > > >, CValueTypeWrapper<CreateInstanceT<CLengthValue> > >* m_height;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<CreateInstanceT<SMILFitValue> > >, CValueTypeWrapper<CreateInstanceT<SMILFitValue> > >* m_fit;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<CreateInstanceT<EnumerationShowBackgroundType> > >, CValueTypeWrapper<CreateInstanceT<EnumerationShowBackgroundType> > >* m_showBackground;

	vector<SMILMediaElement*> m_mediaElements;

//	STDMETHOD(get_height)(/*[out, retval]*/ long *pVal);
//	STDMETHOD(set_height)(/*[in]*/ long newVal);
//	STDMETHOD(get_width)(/*[out, retval]*/ long *pVal);
//	STDMETHOD(set_width)(/*[in]*/ long newVal);
};

}	// Web
}

#endif // w3c_SMILRegionElement_h
