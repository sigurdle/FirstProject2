#ifndef Web_SMILMediaElement_h
#define Web_SMILMediaElement_h

//#include "SMILElement.h"

namespace System
{
namespace Web
{

class HTMLEXT SMILMediaElement :

	public SMILElement,

/*
	SMILMediaElement inherits from IElementTimeContainer (instead of just IElementTime)
	(since it can have timeContainer attribute and behave as a media time container)

	The timeContainer <smil-timing.html> attribute may be applied to SMIL media
	elements (with timed children) to control the behavior of a media time
	container. 
*/
//	public ElementTimeContainerImpl,//<SMILMediaElement>,
	public SVGTestsImpl<SMILMediaElement>,
//	public CLElementEditASImpl<SMILMediaElement>,
	public SMILAnimationTargetImpl<SMILMediaElement>,
//	public ILElementTimeContainer,

	protected CNotifyGetImpl<SMILMediaElement>,
	protected CNotifySendImpl<SMILMediaElement>
{
public:
	typedef Web::ElementTimeContainerImpl/*<SMILMediaElement>*/ timeBase;

	CTOR SMILMediaElement(NamedNodeMap* attributes);

	virtual double GetIntrinsicDuration();

	ElementTimeContainerImpl* m_timeContainerImpl;

	Graphics::Bitmap* GetBitmap();

	gm::RectD GetSubRegion(double bbwidth, double bbheight);

	ErrorCode LoadMedia();

	int GetWidth();
	int GetHeight();

	virtual void InactiveToActive();
	virtual void ActiveToInactive();
	virtual void Seek(double tps);

	SMILRegionElement* get_region();
	void set_region(SMILRegionElement* newVal);
	String get_src();
	void set_src(StringIn newVal);

	virtual void seekElement(double seekTo);

	Web::ISVGStringList* get_transIn()
	{
		ASSERT(0);
#if 0
		if (pVal == NULL) return E_POINTER;
		*pVal = m_transIn->m_value->m_value;
		(*pVal)->AddRef();
#endif
		return NULL;
	}
	Web::ISVGStringList* get_transOut()
	{
		ASSERT(0);
#if 0
		if (pVal == NULL) return E_POINTER;
		*pVal = m_transOut->m_value->m_value;
		(*pVal)->AddRef();
#endif
		return NULL;
	}

	String get_timeContainer()
	{
		String timeContainer = getAttribute(WSTR("timeContainer"));

		if (timeContainer.GetLength() == 0)
			return WSTR("par");	// TODO ???
		else
			return timeContainer;
	}
	void set_timeContainer(StringIn timeContainer)
	{
		if (timeContainer == L"none")
			removeAttribute(WSTR("timeContainer"));
		else
			setAttribute(WSTR("timeContainer"), timeContainer);
	}

protected:

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}

public:

	MediaSource* m_pMedia;

	CATXMLAttr2T<CreateInstanceT<Web::CAnimatedClass<Web::CValueTypeWrapper<CreateInstanceT<CLengthValue> > > >, CValueTypeWrapper<CreateInstanceT<CLengthValue> > >* m_left;
	CATXMLAttr2T<CreateInstanceT<Web::CAnimatedClass<Web::CValueTypeWrapper<CreateInstanceT<CLengthValue> > > >, CValueTypeWrapper<CreateInstanceT<CLengthValue> > >* m_top;
	CATXMLAttr2T<CreateInstanceT<Web::CAnimatedClass<Web::CValueTypeWrapper<CreateInstanceT<CLengthValue> > > >, CValueTypeWrapper<CreateInstanceT<CLengthValue> > >* m_right;
	CATXMLAttr2T<CreateInstanceT<Web::CAnimatedClass<Web::CValueTypeWrapper<CreateInstanceT<CLengthValue> > > >, CValueTypeWrapper<CreateInstanceT<CLengthValue> > >* m_bottom;
	CATXMLAttr2T<CreateInstanceT<Web::CAnimatedClass<Web::CValueTypeWrapper<CreateInstanceT<CLengthValue> > > >, CValueTypeWrapper<CreateInstanceT<CLengthValue> > >* m_width;
	CATXMLAttr2T<CreateInstanceT<Web::CAnimatedClass<Web::CValueTypeWrapper<CreateInstanceT<CLengthValue> > > >, CValueTypeWrapper<CreateInstanceT<CLengthValue> > >* m_height;

	CXMLAttr2T<CreateInstanceT<CValueTypeWrapper<CreateInstanceT<SVGStringListSemicolonSeparated> > > >* m_transIn;
	CXMLAttr2T<CreateInstanceT<CValueTypeWrapper<CreateInstanceT<SVGStringListSemicolonSeparated> > > >* m_transOut;

	double m_implicitDur;

};

}	// Web
}

#endif // Web_SMILMediaElement_h
