#ifndef Web_SMILBrushElement_h
#define Web_SMILBrushElement_h

//#include "resource.h"       // main symbols

#include "LSMILElementImpl.h"
#include "LElementTimeContainerImpl.h"
//#include "LElementEditASImpl.h"
#include "LElementEditVALImpl.h"
#include "LSVGTestsImpl.h"

#include "PImage.h"

//#include "AnimationTarget.h"
//#include "ColorValue.h"
//#include "LengthValue.h"

namespace System
{
namespace Web
{

class HTMLEXT CLSMILBrushElement : 

	public CLSMILElementImpl,

/*
	SMILMediaElement inherits from ILElementTimeContainer (instead of just ILElementTime)
	(since it can have timeContainer attribute and behave as a media time container)

	The timeContainer <smil-timing.html> attribute may be applied to SMIL media
	elements (with timed children) to control the behavior of a media time
	container. 
*/

	public CLElementTimeContainerImpl<CLSMILBrushElement>,
	public CLSVGTestsImpl<CLSMILBrushElement>,

//	public CLElementEditASImpl<CLSMILBrushElement>,

	public CLSMILAnimationTargetImpl<CLSMILBrushElement>,

	public CLElementEditVALImpl<CLSMILBrushElement>,

	public ILSMILBrushElement,
	public ILElementTimeContainer,
	public ILElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<CLSMILBrushElement>,
	protected CNotifySendImpl<CLSMILBrushElement>
{
public:

	CTOR CLSMILBrushElement()
	{
	//	m_implicitDur = 0;

		m_color = NULL;
		m_left = NULL;
		m_top = NULL;
		m_right = NULL;
		m_bottom = NULL;
		m_width = NULL;
		m_height = NULL;
	}

	int FinalConstruct()
	{

		AddXMLAttribute(NewXMLAttr(&m_color, L"", L"color"));

		AddXMLAttribute(NewXMLAttr(&m_left, L"", L"left"));
		AddXMLAttribute(NewXMLAttr(&m_top, L"", L"top"));
		AddXMLAttribute(NewXMLAttr(&m_right, L"", L"right"));
		AddXMLAttribute(NewXMLAttr(&m_bottom, L"", L"bottom"));
		AddXMLAttribute(NewXMLAttr(&m_width, L"", L"width"));
		AddXMLAttribute(NewXMLAttr(&m_height, L"", L"height"));

		SetAllValues(this);	// ???

		return 0;
	}


	CATXMLAttr2T<CAnimatedClass<CValueTypeWrapper<CColorValue> >, CValueTypeWrapper<CColorValue> >* m_color;

	CATXMLAttr2T<CAnimatedClass<CValueTypeWrapper<CLengthValue> >, CValueTypeWrapper<CLengthValue> >* m_left;
	CATXMLAttr2T<CAnimatedClass<CValueTypeWrapper<CLengthValue> >, CValueTypeWrapper<CLengthValue> >* m_top;
	CATXMLAttr2T<CAnimatedClass<CValueTypeWrapper<CLengthValue> >, CValueTypeWrapper<CLengthValue> >* m_right;
	CATXMLAttr2T<CAnimatedClass<CValueTypeWrapper<CLengthValue> >, CValueTypeWrapper<CLengthValue> >* m_bottom;
	CATXMLAttr2T<CAnimatedClass<CValueTypeWrapper<CLengthValue> >, CValueTypeWrapper<CLengthValue> >* m_width;
	CATXMLAttr2T<CAnimatedClass<CValueTypeWrapper<CLengthValue> >, CValueTypeWrapper<CLengthValue> >* m_height;

//	double m_implicitDur;
//	virtual double GetImplicitDuration();

	LDraw::RectD GetSubRegion(double bbwidth, double bbheight);

	HRESULT GetWidth(long *pVal);
	HRESULT GetHeight(long *pVal);


// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown *targetObject, IUnknown *immtargetObject, DISPID dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}

/*
	virtual void InactiveToActive();
	virtual void ActiveToInactive();
	virtual void Seek(double tps);
	*/

// ILSMILBrushElement
public:
//	STDMETHOD(get_region)(/*[out, retval]*/ ILSMILRegionElement* *pVal);
//	STDMETHOD(put_region)(/*[in]*/ ILSMILRegionElement* newVal);

	StringW* get_timeContainer()
	{
		if (pVal == NULL) return E_POINTER;

		CComBSTR timeContainer;
		getAttribute(L"timeContainer", &timeContainer);

		if (timeContainer.Length() == 0)
			*pVal = SysAllocString(L"par");	// TODO ???
		else
			*pVal = timeContainer.Detach();

		return S_OK;
	}
	STDMETHOD(set_timeContainer)(/*[in]*/ BSTR newVal)
	{
		if (!wcscmp(newVal, L"none"))
			return removeAttribute(L"timeContainer");
		else
			return setAttribute(L"timeContainer", newVal);
	}
};

}	// Web
}

#endif // Web_SMILBrushElement_h
