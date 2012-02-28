#ifndef Web_SVGZoomEvent_h
#define Web_SVGZoomEvent_h

namespace System
{
namespace Web
{

class WEBEXT ZoomEvent : public UIEvent
{
public:
	CTOR ZoomEvent();
	~ZoomEvent();

	const SVGRect* get_zoomRectScreen() const;
	double get_previousScale() const;
	const SVGPoint* get_previousTranslate() const;
	double get_newScale() const;
	const SVGPoint* get_newTranslate() const;

protected:

	SVGRect* m_zoomRectScreen;
	SVGPoint* m_previousTranslate;
	SVGPoint* m_newTranslate;
	double m_previousScale;
	double m_newScale;
};

}	// Web
}	// System

#endif // Web_SVGZoomEvent_h
