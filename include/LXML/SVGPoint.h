#ifndef Web_SVGPoint_h
#define Web_SVGPoint_h

namespace System
{
namespace Web
{

interface ISVGPointListener
{
	virtual void OnPointChanged(SVGPoint* point, double oldx, double oldy) = 0;
	virtual bool OnRemoveItem(SVGPoint* point) = 0;
};

class WEBEXT SVGPoint : public Object, public ISVGPoint
{
public:
	CTOR SVGPoint();
	CTOR SVGPoint(gm::PointD point);
	CTOR SVGPoint(double x, double y);
	CTOR SVGPoint(ISVGPointListener* owner);

	double get_x() const;
	double get_y() const;
	void set_x(double x);
	void set_y(double y);
	SVGPoint* matrixTransform(const SVGMatrix* matrix) const;

public:

	double m_x;
	double m_y;
	ISVGPointListener* m_owner;
};

}	// Web
}	// System

#endif // Web_SVGPoint_h
