#ifndef __VALUETYPE_H_
#define __VALUETYPE_H_

namespace System
{
namespace Web
{

class CValueType;

interface IValueTypeListener
{
	virtual void OnValueTypeChange(CValueType* pValue) = 0;
};

class CValueType : public Object/* :
	public ILSMILAttributeValue
	*/
{
public:
	CTOR CValueType()
	{
		m_pListener = NULL;
	}

	~CValueType()
	{
		ASSERT(m_pListener == NULL);
	}

	IValueTypeListener* m_pListener;

	//virtual CValueType& operator = (const CValueType& value) = 0;
	virtual void CopyFrom(CValueType* value) = 0;
	virtual void Add(CValueType* value) = 0;
	//virtual void operator = (const System::StringW& bstr) = 0;
	//virtual operator StringW () = 0;
	virtual void InterpolateValue(CValueType* a, CValueType* b, double t) = 0;

//
	virtual String getStringValue() = 0;
	virtual void setStringValue(StringIn newVal) = 0;
};

class CAttributeType
{
public:
	virtual CValueType* NewVal() = 0;
};

template <class T> class CValueTypeWrapper :
	public CValueType,
	public ISingleObjectListener
{
public:
	T m_value;

	CTOR CValueTypeWrapper()
	{
		ASSERT(0);
		//m_value->m_pListener = this;
	}

	~CValueTypeWrapper()
	{
		ASSERT(0);
		//m_value->m_pListener = NULL;
	}
/*
	int FinalConstruct()
	{
		m_value->m_pListener = this;

		return 0;
	}

	void FinalRelease()
	{
		m_value->m_pListener = NULL;
	}
*/
	/* ??????
	T& operator * ()
	{
		return T;
	}
	*/

	T* operator -> ()
	{
		return &m_value;
	}

	virtual void CopyFrom(CValueType* value)
	{
		m_value = ((CValueTypeWrapper<T>*)value)->m_value;
	}

	virtual void Add(CValueType* value)
	{
		ASSERT(0);
		//m_value += ((CValueTypeWrapper<T>*)value)->m_value;
	}

	/*
	virtual void operator = (const StringW& str)
	{
		m_value->setString(str);
	}
	*/

	virtual void setStringValue(StringIn str)
	{
		ASSERT(0);
		//m_value->setStringValue(str);
	}

	virtual String getStringValue() /* TODO const */
	{
		ASSERT(0);
		return NULL;
	//	return StringW(m_value);
	}

	virtual void InterpolateValue(CValueType* a, CValueType* b, double t)
	{
		ASSERT(0);
		//m_value->InterpolateValue(((CValueTypeWrapper<T>*)a)->m_value, ((CValueTypeWrapper<T>*)b)->m_value, t);
	}

	virtual void OnChanged(CSingleObject* pObject)
	{
		if (m_pListener) m_pListener->OnValueTypeChange(this);
	}

	/*
BEGIN_COM_MAP(CValueTypeWrapper)
	COM_INTERFACE_ENTRY(ILSMILAttributeValue)
END_COM_MAP()
*/

	ErrorCode getObject(Object* *pVal)
	{
	//	CComPtr<IUnknown> object = m_value->GetUnknown();
	//	*pVal = object.Detach();
	ASSERT(0);
		return Success;
	}
};

}	// Web
}

/*
#include "CSSValueImpl.h"
#include "CSSPrimitiveValue.h"
#include "SVGPaint.h"
#include "SVGColor.h"
#include "CSSValueList.h"
*/

namespace System
{
namespace Web
{

template <class T> class CCSSValueType :
	public Web::CValueType,

	public ICSSValueListener,
	public ICSSPrimitiveValueListener,
	public ICSSValueListListener,
	public ISVGPaintListener,
	public ISVGColorListener
{
public:
	CTOR CCSSValueType()
	{
		m_value->m_pListener = this;
	}

	T m_value;

	/*	????
	T& operator * ()
	{
		return T;
	}
	*/

	T* operator -> ()
	{
		return &m_value;
	}

	virtual void CopyFrom(CValueType* value)
	{
		ASSERT(0);
#if 0
		*m_value = ((CCSSValueType<T>*)value)->m_value;
#endif
	}

	virtual void Add(CValueType* value)
	{
		ASSERT(0);
#if 0
		*m_value += ((CCSSValueType<T>*)value)->m_value;
#endif
	}

	String getStringValue()
	{
		return m_value->getStringValue();
	}

	virtual void setStringValue(StringIn str)
	{
		m_value->setString(str);
	}

	/*
	virtual operator StringW ()
	{
		ASSERT(0);
		return StringW();
#if 0
		return StringW(m_value);
#endif
	}
	*/

	virtual void InterpolateValue(Web::CValueType/*Wrapper<T>*/ * a, Web::CValueType/*Wrapper<T>* */ * b, double t)
	{
		ASSERT(0);
	//	m_value->InterpolateValue(a->m_value, b->m_value, t);
	//	m_value->InterpolateValue(((CCSSValueType<T>*)a)->m_value, ((CCSSValueType<T>*)b)->m_value, t);
	}

	virtual void OnCSSValueChanged(CSSValue* pValue)
	{
		if (m_pListener) m_pListener->OnValueTypeChange(this);
	}

	virtual void OnCSSValueChanged(CSSPrimitiveValue* pValue)
	{
		if (m_pListener) m_pListener->OnValueTypeChange(this);
	}

	virtual void OnCSSValueChanged(CSSValueList* pValue)
	{
		if (m_pListener) m_pListener->OnValueTypeChange(this);
	}

	virtual void OnCSSValueChanged(SVGPaint* pValue)
	{
		if (m_pListener) m_pListener->OnValueTypeChange(this);
	}

	virtual void OnCSSValueChanged(SVGColor* pValue)
	{
		if (m_pListener) m_pListener->OnValueTypeChange(this);
	}

	ErrorCode getObject(System::Object* *pVal)
	{
//		CComPtr<IUnknown> object = m_value->GetUnknown();
//		*pVal = object.Detach();
		ASSERT(0);
		return Success;
	}

	/*
	STDMETHODIMP getCSSValue(ILCSSValue* *pVal)
	{
		*pVal = m_value;
		(*pVal)->AddRef();
		return S_OK;
	}
	*/
};

}	// Web
}

#endif
