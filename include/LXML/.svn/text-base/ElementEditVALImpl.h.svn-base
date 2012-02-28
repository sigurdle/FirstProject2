#ifndef __ELEMENTEDITVALIMPL_H__
#define __ELEMENTEDITVALIMPL_H__

#include "NodeEditVALImpl.h"

namespace System
{
namespace Web
{

//class Element;

class WEBEXT ElementEditVAL
{
public:

	virtual ~ElementEditVAL()
	{
	}

	bool isNodeValid(Element* element, /*[in]*/ bool deep, /*[in]*/ CheckTypeVAL wFValidityCheckLevel);

	char m_dummy;
};

template<class T> class ElementEditVALImpl :
	public NodeEditVALImpl<T>,
	public ElementEditVAL
{
public:
	System::StringW* get_defaultValue()
	{
		THROW(-1);
		return NULL;
	}

	ErrorCode get_enumeratedValues(/*[out,retval]*/ IDOMStringList* *pVal)
	{
		return Error_NotImplemented;
	}

	bool isNodeValid(/*[in]*/ bool deep, /*[in]*/ CheckTypeVAL wFValidityCheckLevel)
	{
		return ElementEditVAL::isNodeValid(static_cast<T*>(this), deep, wFValidityCheckLevel);
	}
//

	ErrorCode get_allowedChildren(/*[out,retval]*/ IDOMNameList* *pVal)
	{
		return Success;
	}

	ErrorCode get_allowedParents(/*[out,retval]*/ IDOMNameList* *pVal)
	{
		return Success;
	}

	ErrorCode get_allowedNextSiblings(/*[out,retval]*/ IDOMNameList* *pVal)
	{
		return Success;
	}

	ErrorCode get_allowedPreviousSiblings(/*[out,retval]*/ IDOMNameList* *pVal)
	{
		return Success;
	}

	ErrorCode get_allowedAttributes(/*[out,retval]*/ IDOMNameList* *pVal)
	{
		return Success;
	}

	ErrorCode get_requiredAttributes(/*[out,retval]*/ IDOMNameList* *pVal)
	{
		return Success;
	}
};

}	// w3c
}

#endif // __ELEMENTEDITVALIMPL_H__
