#ifndef __SVGEnumerationMorphologyOperatorValue_h__
#define __SVGEnumerationMorphologyOperatorValue_h__

namespace System
{
namespace Web
{

class SVGEnumerationMorphologyOperatorValue :
	public CSingleObject
{
public:
	SVGEnumerationMorphologyOperatorValue* operator -> ()
	{
		return this;
	}

	CTOR SVGEnumerationMorphologyOperatorValue();

	operator SVGMorphologyOperator ();
	SVGEnumerationMorphologyOperatorValue& operator = (SVGMorphologyOperator value);
	SVGEnumerationMorphologyOperatorValue& operator += (SVGMorphologyOperator value);

	void setStringValue(StringIn str);
	String getStringValue();

	void InterpolateValue(SVGEnumerationMorphologyOperatorValue& a, SVGEnumerationMorphologyOperatorValue& b, double t);

	/*
	System::Object* GetUnknown()
	{
		return NULL;
	}
	*/

	SVGMorphologyOperator m_value;
};

}	// Web
}

#endif // __SVGEnumerationMorphologyOperatorValue_h__
