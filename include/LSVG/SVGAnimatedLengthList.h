#ifndef __SVGANIMATEDLENGTHLIST_H__
#define __SVGANIMATEDLENGTHLIST_H__

#include "SVGLengthList.h"

namespace System
{
namespace Web
{

class SVGEXT SVGAnimatedLengthList : public Object
{
public:
	CTOR SVGAnimatedLengthList();
	~SVGAnimatedLengthList();

	typedef SVGLengthList t_baseType;
	typedef SVGLengthListValueHandler t_valueHandler;

	SVGLengthList* get_animVal();
	SVGLengthList* get_baseVal();

public:

	SVGLengthList* m_baseVal;
	SVGLengthList* m_animVal;

//	CATXMLAttr* m_pAttr;

	void SetAnimVal(SVGLengthList* value)
	{
		m_animVal->m_p = value->m_p;
	}

	void SetBaseValAsString(StringIn str)
	{
		m_baseVal->setStringValue(str);
	}

	IAnimatedOwner<SVGAnimatedLengthList>* m_owner;

protected:
/*
	virtual void OnChanged(CSingleObject* pLengthList)
	{
		ASSERT(m_pAttr);
		m_pAttr->OnBaseValChanged();
	}
	*/
};

}	// Web
}	// System

#endif // __SVGANIMATEDLENGTHLIST_H__
