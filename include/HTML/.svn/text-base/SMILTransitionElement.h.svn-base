#ifndef Web_SMILTransitionElement_h
#define Web_SMILTransitionElement_h

//#include "resource.h"       // main symbols

#include "SMILElement.h"

namespace System
{
namespace Web
{

class EnumerationTransitionDirectionType :
	public CSingleObject
{
public:

	CTOR EnumerationTransitionDirectionType()
	{
		m_value = (TransitionDirection)-1;	// undefined
	}

	operator TransitionDirection () const
	{
		return m_value;
	}

	EnumerationTransitionDirectionType& operator = (TransitionDirection value)
	{
		m_value = value;
		return *this;
	}

	EnumerationTransitionDirectionType& operator += (TransitionDirection value)
	{
		m_value = value;
		return *this;
	}

	void setStringValue(StringIn str)
	{
		if (str == L"reverse")
			m_value = TRANSITION_DIRECTION_REVERSE;
		else
			m_value = TRANSITION_DIRECTION_FORWARD;
	}

	String getStringValue()
	{
		ASSERT(0);
		return NULL;
	}

	void InterpolateValue(const EnumerationTransitionDirectionType& a, const EnumerationTransitionDirectionType& b, double t)
	{
		ASSERT(0);
	}

	/*
	IUnknown* GetUnknown()
	{
		return NULL;
	}
	*/

	TransitionDirection m_value;
};

class HTMLEXT SMILTransitionElement : 
	public SMILElement,
	public ElementEditVALImpl<SMILTransitionElement>

//	public ElementEditASImpl<SMILTransitionElement>,

//	public ISMILTransitionElement,
//	public IElementEditVAL,	// INodeEditVAL

//	protected CNotifyGetImpl<SMILTransitionElement>,
//	protected CNotifySendImpl<SMILTransitionElement>
{
public:

	CTOR SMILTransitionElement(NamedNodeMap* attributes);

	TransitionDirection get_direction();
	double get_dur();
	int get_horzRepeat();
	int get_vertRepeat();

	int get_borderWidth();
	int get_animatedBorderWidth();	// ??

protected:

	/*
	// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
	*/

	int m_horzRepeat;
	int m_vertRepeat;

	int m_borderWidth;

	EnumerationTransitionDirectionType m_direction;

	Attr* m_horzRepeatAttr;
	Attr* m_vertRepeatAttr;
	Attr* m_borderWidthAttr;
	Attr* m_directionAttr;
};

}	// Web
}

#endif // Web_SMILTransitionElement_h
