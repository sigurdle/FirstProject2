#ifndef Web_SVGAngle_h
#define Web_SVGAngle_h

//#include "resource.h"       // main symbols

//#include "ValueType.h"

/*
class SVGAngle;

class SVGAngleListener
{
public:
	virtual void OnSVGAngleChange(SVGAngle* pSVGLength) = 0;
};
*/

namespace System
{
namespace Web
{

class SVGAngle : 
	public CSingleObject
{
public:
	CTOR SVGAngle();
	~SVGAngle();

//	SVGAngleListener* m_pListener;

//	SVGAngle& operator = (const SVGAngle& value);
//	SVGAngle& operator += (const SVGAngle& value);
//	operator double () const;

	void setStringValue(StringIn str);
	String getStringValue();

	void convertToSpecifiedUnits(SVGAngleType unitType);
	void newValueSpecifiedUnits(SVGAngleType unitType, double valueInSpecifiedUnits);
	String get_valueAsString();
	void set_valueAsString(StringIn newVal);
	double get_valueInSpecifiedUnits() const;
	void set_valueInSpecifiedUnits(double newVal);
	double get_value() const;
	void set_value(double newVal);
	SVGAngleType get_unitType() const;

	void InterpolateValue(const SVGAngle& a, const SVGAngle& b, double t);

private:

	SVGAngleType m_unitType;
	double m_value;
	double m_valueInSpecifiedUnits;
	String m_valueAsString;
};

}	// Web
}

#endif // Web_SVGAngle_h
