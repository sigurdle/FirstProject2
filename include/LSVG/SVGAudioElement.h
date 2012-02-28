#ifndef __SVGAUDIOELEMENT_H_
#define __SVGAUDIOELEMENT_H_

namespace System
{
namespace Web
{

class SVGEXT SVGAudioElement : 

	public SVGElement,
	public SVGURIReferenceImpl<SVGAudioElement>,
	public SVGTransformableImpl<SVGAudioElement>,
	public SVGStylableImpl<SVGAudioElement>,
	public SVGLangSpaceImpl<SVGAudioElement>,
//	public ElementEditASImpl<SVGAudioElement>,
	public ElementEditVALImpl<SVGAudioElement>,
	public SMILAnimationTargetImpl<SVGAudioElement>,

	//public ElementTimeContainerImpl,//<SVGAudioElement>,

	public IElementEditVAL,	// ILNodeEditVAL
	//public IElementTimeContainer,	// ILElementTime,

	protected CNotifyGetImpl<SVGAudioElement>,
	protected CNotifySendImpl<SVGAudioElement>
{
public:
	CTOR SVGAudioElement(NamedNodeMap* attributes);

	ErrorCode LoadMedia();

	virtual void Run();
	virtual void Seek(double tps);
	virtual double GetIntrinsicDuration();

	String get_timeContainer()
	{
		String timeContainer = getAttribute(WSTR("timeContainer"));

		if (timeContainer == NULL)
			return WSTR("par");	// TODO ???
		else
			return timeContainer;
	}
	void set_timeContainer(StringIn newVal)
	{
		if (newVal == L"none")
			removeAttribute(WSTR("timeContainer"));
		else
			setAttribute(WSTR("timeContainer"), newVal);
	}

	MediaSource* m_pMedia;

protected:

	ElementTimeContainerImpl* m_timeContainerImpl;
	double m_implicitDur;
};

}	// LSVG
}

#endif // __SVGAUDIOELEMENT_H_
