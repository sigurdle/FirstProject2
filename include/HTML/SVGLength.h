#ifndef Web_SVGLength_h
#define Web_SVGLength_h

namespace System
{
namespace Web
{

class HTMLEXT SVGLengthValueHandler : public IValueHandler
{
public:
	virtual Object* Create() const;
	virtual void ParseString(Object* value, StringIn str) const;
	virtual void InterpolateValue(Object* dest, Object* a, Object* b, double t);

	static SVGLengthValueHandler s_svgLengthValueHandler;

	static IValueHandler* GetValueHandler()
	{
		return &s_svgLengthValueHandler;
	}
};

class HTMLEXT SVGLengthValue : public Object
{
public:

	CTOR SVGLengthValue();

	CTOR SVGLengthValue(double value, double valueInSpecifiedUnits, StringIn valueAsString, SVGLengthType unitType)
	{
		m_value = value;
		m_valueInSpecifiedUnits = valueInSpecifiedUnits;
		m_valueAsString = valueAsString;
		m_unitType = unitType;

		//m_refcount = 1;
	}

	bool Equals(const SVGLengthValue* other) const;

	virtual bool Equals(const Object* other) const;

	void ParseString(StringIn str);

	String get_valueAsString();

	double m_value;
	double m_valueInSpecifiedUnits;
	String m_valueAsString;
	SVGLengthType m_unitType;
//	SVGLengthType m_unitType : 4;
//	unsigned int m_refcount : 28;

//	static SVGLengthValue s_values[4];
};

interface ISVGLengthListener
{
	virtual void OnChanged(SVGLength* pLength) = 0;
	virtual bool OnRemoveItem(SVGLength* pLength) = 0;
};

class HTMLEXT SVGLength :
	public Object,
	public ISVGLength
{
public:
	CTOR SVGLength();

	CTOR SVGLength(SVGLengthValue* p)
	{
		m_p = p;
		/*
		if (m_p)
		{
			++m_p->m_refcount;
		}
		*/
	}

	~SVGLength();

//	SVGLengthListener* m_pListener;

	void InterpolateValue(const SVGLength& a, const SVGLength& b, double t);

	void convertToSpecifiedUnits(SVGLengthType unitType);
	void newValueSpecifiedUnits(SVGLengthType unitType, double valueInSpecifiedUnits);

	String get_valueAsString();
	void set_valueAsString(StringIn newVal);

	double get_valueInSpecifiedUnits();
	void set_valueInSpecifiedUnits(double newVal);

	double get_value();
	void set_value(double newVal);

	SVGLengthType get_unitType() const
	{
		return m_p->m_unitType;
	}

	virtual bool Equals(const Object* other) const;

	SVGLengthValue* m_p;
	ISVGLengthListener* m_owner;

protected:

	friend HTMLEXT String GetAsString(SVGLength* pLength);
	friend HTMLEXT void SetAsString(SVGLength* pLength, StringIn str);

//	StringW* GetAsString();
	bool SetAsString(StringIn str);

private:

	void readOnly();
};

class HTMLEXT SVGLengthMutable : public SVGLength
{
public:

	CTOR SVGLengthMutable();

	CTOR SVGLengthMutable(SVGLengthValue* p) : SVGLength(p)
	{
	}

	virtual void set_valueAsString(StringIn newVal);
//	virtual double get_valueInSpecifiedUnits();
	virtual void set_valueInSpecifiedUnits(double newVal);
	virtual void set_value(double newVal);
	virtual void convertToSpecifiedUnits(SVGLengthType unitType);
	virtual void newValueSpecifiedUnits(SVGLengthType unitType, double valueInSpecifiedUnits);
};

}	// Web
}

#endif // Web_SVGLength_h
