#ifndef Web_SVGColorProfileElement_h
#define Web_SVGColorProfileElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGColorProfileElement : 

	public SVGElement,
	public ElementEditVALImpl<SVGColorProfileElement>,

	protected CNotifyGetImpl<SVGColorProfileElement>,
	protected CNotifySendImpl<SVGColorProfileElement>
{
public:
	CTOR SVGColorProfileElement();

	String get_local();
	void set_local(StringIn newVal);
	String get_name();
	void set_name(StringIn newVal);
	SVGRenderingIntent get_renderingIntent();
	void set_renderingIntent(SVGRenderingIntent newVal);

	ErrorCode Load();

	CColorProfile* GetColorProfile()
	{
		Load();
		return m_pProfile;
	};

	CColorProfile* m_pProfile;

private:

	bool m_bTriedLoaded;
};

}	// Web
}

#endif // Web_SVGColorProfileElement_h
