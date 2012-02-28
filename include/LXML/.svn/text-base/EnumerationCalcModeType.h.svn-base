#ifndef __LENUMERATIONCALCMODETYPE_H_
#define __LENUMERATIONCALCMODETYPE_H_

namespace System
{
namespace Web
{

class WEBEXT EnumerationCalcModeType :
	public CSingleObject
{
public:
	CTOR EnumerationCalcModeType()
	{
		m_value = (CalcModeType)-1;	// undefined
	}

	EnumerationCalcModeType* operator -> ()
	{
		return this;
	}

	operator CalcModeType ()
	{
		return m_value;
	}

	EnumerationCalcModeType& operator = (CalcModeType value)
	{
		m_value = value;
		return *this;
	}

	EnumerationCalcModeType& operator += (CalcModeType value)
	{
		m_value = value;
		return *this;
	}

	String getStringValue();
	void setStringValue(StringIn str);

	void InterpolateValue(const EnumerationCalcModeType& a, const EnumerationCalcModeType& b, double t)
	{
		ASSERT(0);
	}

	CalcModeType m_value;
};

}	// Web
}

#endif	// __LENUMERATIONCALCMODETYPE_H_
