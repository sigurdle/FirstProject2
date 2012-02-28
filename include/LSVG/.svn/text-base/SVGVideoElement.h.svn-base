#ifndef Web_SVGVideoElement_h
#define Web_SVGVideoElement_h

namespace System
{
namespace Web
{

interface IRenderAudio
{
	virtual ErrorCode GetWaveFormat(WAVEFORMATEX* pVal) = 0;
	virtual ErrorCode RenderAudio(double start_tsp, double lent, uint8 * buffer, ULONG nSamples) = 0;
};

class SVGEXT SVGVideoElement : 

	public SVGTransformableElement,
	public SVGURIReferenceImpl<SVGVideoElement>,
	//public SVGTransformableImpl<SVGVideoElement>,
	public SVGStylableImpl<SVGVideoElement>,
	public SVGTestsImpl<SVGVideoElement>,
	public SVGLangSpaceImpl<SVGVideoElement>,
//	public ElementEditASImpl<SVGVideoElement>,
	public ElementEditVALImpl<SVGVideoElement>,
	public SMILAnimationTargetImpl<SVGVideoElement>,
	public CSVGRenderElementImpl<SVGVideoElement>,

//	public ElementTimeContainerImpl,//<SVGVideoElement>,	// ? time container

//	public ISVGTransformable,
//	public IElementEditVAL,	// ILNodeEditVAL
//	public IElementTimeContainer,	// ILElementTime,

	public IRenderAudio,

	protected CNotifyGetImpl<SVGVideoElement>,
	protected CNotifySendImpl<SVGVideoElement>
{
public:

	CTOR SVGVideoElement(NamedNodeMap* attributes);
	~SVGVideoElement();

	ErrorCode LoadMedia();

	virtual double GetIntrinsicDuration();
	virtual void Seek(double tps);

	ErrorCode GetWaveFormat(WAVEFORMATEX* pVal);
	ErrorCode RenderAudio(double start_tsp, double lent, uint8 * buffer, ULONG nSamples);

	SVGAnimatedLength* get_x();
	SVGAnimatedLength* get_y();
	SVGAnimatedLength* get_width();
	SVGAnimatedLength* get_height();
	SVGAnimatedPreserveAspectRatio* get_preserveAspectRatio();

	double getIntrinsicDuration()
	{
		return GetIntrinsicDuration();
	}
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

protected:

	friend class PSVGVideoElement;

	ElementTimeContainerImpl* m_timeContainerImpl;

	SVGAnimatedLength* m_x;
	SVGAnimatedLength* m_y;
	SVGAnimatedLength* m_width;
	SVGAnimatedLength* m_height;
	SVGAnimatedPreserveAspectRatio* m_preserveAspectRatio;

	MediaSource* m_pMedia;
	double m_intrinsicDur;
};

}	// Web
}

#endif // Web_SVGVideoElement_h
