#ifndef __ASDTDATTRIBUTE_H_
#define __ASDTDATTRIBUTE_H_

#include "ASDTDObjectImpl.h"

namespace System
{
namespace Web
{

class WEBEXT CASDTDAttribute :
	public CASDTDObject, public IASAttributeDeclaration
{
public:
	String m_name;
	vector<String> m_enums;

	String m_value;
	ASValueConstraint m_defaultType;

	IASObject* cloneASObject(bool deep) const
	{
		ASSERT(0);
		return NULL;
	}

#if 0
	STDMETHOD(get_localName)(/*[out, retval]*/ BSTR *pVal)
	{
		return E_FAIL;
	}

	STDMETHOD(set_localName)(/*[in]*/ BSTR newVal)
	{
		return E_FAIL;
	}

	STDMETHOD(get_prefix)(/*[out, retval]*/ BSTR *pVal)
	{
		return E_FAIL;
	}

	STDMETHOD(set_prefix)(/*[in]*/ BSTR newVal)
	{
		return E_FAIL;
	}
#endif

	String get_nodeName()
	{
		return m_name;
	}

	void set_nodeName(StringIn nodeName)
	{
		m_name = nodeName;
	}

	ASObjectType get_asNodeType() const
	{
		return AS_ATTRIBUTE_DECLARATION;
	}

// IASAttributeDeclaration
	ASValueConstraint get_defaultType() const;
	void set_defaultType(ASValueConstraint newVal);
	String get_enumAttr();
	void set_enumAttr(StringIn newVal);
	String get_dataValue();
	void set_dataValue(StringIn newVal);
	ASDataType get_dataType() const;
	void set_dataType(ASDataType newVal);
};

}	// w3c
}

#endif // __ASDTDATTRIBUTE_H_
